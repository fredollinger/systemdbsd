/*
 * Copyright (c) 2014 Ian Sutton <ian@kremlin.cc>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <unistd.h>
#include <limits.h>
#include <signal.h>

#include <sys/param.h>
#include <sys/sysctl.h>
#include <string.h>

#include <glib/gprintf.h>
#include <glib-unix.h>
/* #include <gtk/gtk.h> */

#include "hostnamed-gen.h"
#include "hostnamed.h"

/* add any sysctl strings that suggest virtualization here */
/* format: {
 *           (1) string to be matched against runtime machine's sysctl output.
 *               can be either the exact string or a substring contained
 *               within sysctl strings. no "guesses" here, a match should
 *               reliably indicate the chassis/icon. 
 *
 *           (2) string describing chassis type divulged by (1).
 *               must be one of "desktop", "laptop", "server",
 *               "tablet", "handset", "vm", "container" or NULL
 *               if only icon string can be ascertained. "vm" refers
 *               to operating systems running on baremetal hypervisors
 *               (hardware virtualization, like XEN) while "container"
 *               refers to OSs running on shared hypervisors like
 *               virtualbox or VMware. consider the distinction carefully
 *               as common virtualization software like KVM may share
 *               characteristics of both "vm" and "container" types.
 *
 *           (3) string specifying icon to use. follows XDG icon spec.
 *               see http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html
 *               for allowed strings.
 *
 *           (4) chassis precedence bit. TRUE if (2) is defined and
 *               we're certain it is the proper string. FALSE in the
 *               circumstance (2) may be the correct string, unless
 *               a match with this bit set to TRUE overrides it.
 *               if (2) is NULL, this bit is inconsequential.
 *
 *           (5) icon precedence bit. see previous definition.
 *         }                                               */
struct SYSCTL_LOOKUP_TABLE {
    gchar    *match_string;
    gchar    *chassis;
    gchar    *icon;
    gboolean chassis_precedence;
    gboolean icon_precedence;
};

GPtrArray *hostnamed_freeable;
Hostname1 *hostnamed_interf;

GMainLoop *hostnamed_loop;

guint bus_descriptor;
gboolean dbus_interface_exported; /* reliable because of gdbus operational guarantees */

gchar *CHASSIS, *ICON;

/* TODO no specific vm or laptop icon in gnome
 * NOTE paravirtualization on xen is only available for linuxes right now
 * dmesg on linux systems reveals xen and virtualization method (HVM or PVM) 
 * but we will worry about those later */
const struct SYSCTL_LOOKUP_TABLE chassis_indicator_table[] =
{
    { "QEMU Virtual CPU",        "container", "drive-optical",   FALSE, FALSE }, /* could be QEMU running in userspace or as part of KVM */
    { "SmartDC HVM",             "vm",        "drive-multidisk", TRUE,  TRUE  }, /* oracle solaris kvm */
    { "VirtualBox",              "container", "drive-optical",   TRUE,  TRUE  },
    { "VMware, Inc.",            "container", "drive-optical",   TRUE,  TRUE  },
    { "VMware Virtual Platform", "container", "drive-optical",   TRUE,  TRUE  },
    { "Parallels",               "container", "drive-optical",   TRUE,  TRUE  } /* need verification */
};

/*const gchar* vmstring_list[] = { 
    "QEMU Virtual CPU",
    "SmartDC HVM",
    "KVM",
    "VirtualBox"
};*/

/* --- begin method/property/dbus signal code --- */

static gboolean
on_handle_set_hostname(Hostname1 *hn1_passed_interf,
                       GDBusMethodInvocation *invoc,
                       const gchar *greet,
                       gpointer data) {
    return FALSE;
}

static gboolean
on_handle_set_static_hostname(Hostname1 *hn1_passed_interf,
                              GDBusMethodInvocation *invoc,
                              const gchar *greet,
                              gpointer data) {
    return FALSE;
}

static gboolean
on_handle_set_pretty_hostname(Hostname1 *hn1_passed_interf,
                              GDBusMethodInvocation *invoc,
                              const gchar *greet,
                              gpointer data) {
    return FALSE;
}

static gboolean
on_handle_set_chassis(Hostname1 *hn1_passed_interf,
                      GDBusMethodInvocation *invoc,
                      const gchar *greet,
                      gpointer data) {
    return FALSE;
}

static gboolean
on_handle_set_icon_name(Hostname1 *hn1_passed_interf,
                        GDBusMethodInvocation *invoc,
                        const gchar *greet,
                        gpointer data) {
    return FALSE;
}

/* note: all hostnamed/hostname1's properties are read-only,
 * and do not need set_ functions, gdbus-codegen realized
 * this from the XML and handled the to-be error of trying
 * to set a read-only property's value 
 */

const gchar *
our_get_hostname() {

    gchar *hostname_buf, *ret;
    size_t hostname_divider;

    hostname_buf = (gchar*) g_malloc0(MAXHOSTNAMELEN);
    ret          = (gchar*) g_malloc0(MAXHOSTNAMELEN);

    g_ptr_array_add(hostnamed_freeable, hostname_buf);
    g_ptr_array_add(hostnamed_freeable, ret);

    if(gethostname(hostname_buf, MAXHOSTNAMELEN) || g_strcmp0(hostname_buf, "") == 0) 
        return "localhost"; 

    hostname_divider = strcspn(hostname_buf, ".");

    return strncpy(ret, hostname_buf, hostname_divider);
}

const gchar *
our_get_static_hostname() {

    const gchar *pretty_hostname;
    const gchar *ret;

    pretty_hostname = our_get_pretty_hostname();

    if(g_strcmp0(pretty_hostname, "") == 0)
        ret = our_get_hostname();

    else if((ret = g_hostname_to_ascii(pretty_hostname))) {

        g_ptr_array_add(hostnamed_freeable, (gpointer)ret);
        return ret;
    }

    return ret;
}

const gchar *
our_get_pretty_hostname() {

    GKeyFile *config;
    gchar *ret;

    config = g_key_file_new();

    if(g_key_file_load_from_file(config, "/etc/systemd_compat.conf", G_KEY_FILE_NONE, NULL)
        && (ret = g_key_file_get_value(config, "hostnamed", "PrettyHostname", NULL))) { /* ret might need to be freed, docs dont specify but i am suspicious */

        g_key_file_unref(config);
        return ret;
    }

    if(config)
        g_free(config);

    return "";
}

const gchar *
our_get_chassis() {

   return "asdf";

}

const gchar *
our_get_icon_name() {

    return "TODO";
}

const gchar *
our_get_kernel_name() {

    return "TODO";
}

const gchar *
our_get_kernel_version() {

    return "TODO";
}

const gchar *
our_get_kernel_release() {

    return "TODO";
}

const gchar *
our_get_os_cpename() {

    return "TODO";
}

const gchar *
our_get_os_pretty_name() {

    return "TODO";
}

/* --- end method/property/dbus signal code, begin bus/name handlers --- */

static void hostnamed_on_bus_acquired(GDBusConnection *conn,
                            const gchar *name,
                            gpointer user_data) {

    g_printf("got bus/name, exporting %s's interface...\n", name);

    hostnamed_interf = hostname1_skeleton_new();

    /* attach function pointers to generated struct's method handlers */
    g_signal_connect(hostnamed_interf, "handle-set-hostname", G_CALLBACK(on_handle_set_hostname), NULL);
    g_signal_connect(hostnamed_interf, "handle-set-static-hostname", G_CALLBACK(on_handle_set_static_hostname), NULL);
    g_signal_connect(hostnamed_interf, "handle-set-pretty-hostname", G_CALLBACK(on_handle_set_pretty_hostname), NULL);
    g_signal_connect(hostnamed_interf, "handle-set-chassis", G_CALLBACK(on_handle_set_chassis), NULL);
    g_signal_connect(hostnamed_interf, "handle-set-icon-name", G_CALLBACK(on_handle_set_icon_name), NULL);

    /* set our properties before export */
    hostname1_set_hostname(hostnamed_interf, our_get_hostname());
    hostname1_set_static_hostname(hostnamed_interf, our_get_static_hostname());
    hostname1_set_pretty_hostname(hostnamed_interf, our_get_pretty_hostname());
    hostname1_set_chassis(hostnamed_interf, our_get_chassis());
    hostname1_set_icon_name(hostnamed_interf, our_get_icon_name());
    hostname1_set_kernel_name(hostnamed_interf, our_get_kernel_name());
    hostname1_set_kernel_version(hostnamed_interf, our_get_kernel_version());
    hostname1_set_kernel_release(hostnamed_interf, our_get_kernel_release());
    hostname1_set_operating_system_cpename(hostnamed_interf, our_get_os_cpename());
    hostname1_set_operating_system_pretty_name(hostnamed_interf, our_get_os_pretty_name());
 
    if(!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(hostnamed_interf),
                                         conn,
                                         "/org/freedesktop/hostname1",
                                         NULL)) {

        g_printf("failed to export %s's interface!\n", name); /* unusual edge case, TODO check errno */
        hostnamed_mem_clean();

    } else {

        dbus_interface_exported = TRUE;
        g_printf("exported %s's interface on the system bus...\n", name);
    }
}

static void hostnamed_on_name_acquired(GDBusConnection *conn,
                                       const gchar *name,
                                       gpointer user_data) {

    g_printf("success!\n");
}

static void hostnamed_on_name_lost(GDBusConnection *conn,
                                   const gchar *name,
                                   gpointer user_data) {

    if(!conn) {

        g_printf("failed to connect to the system bus while trying to acquire name '%s': either dbus-daemon isn't running or we don't have permission to push names and/or their interfaces to it.\n", name);
        hostnamed_mem_clean();
    }

    g_printf("lost name %s, exiting...\n", name);

    hostnamed_mem_clean();
}

/* --- end bus/name handlers, begin misc unix functions --- */

/* safe call to clean and then exit
 * this stops our GMainLoop safely before letting main() return */
void hostnamed_mem_clean() {

    g_printf("exiting...\n");

    if(dbus_interface_exported)
        g_dbus_interface_skeleton_unexport(G_DBUS_INTERFACE_SKELETON(hostnamed_interf));

    if(g_main_loop_is_running(hostnamed_loop)) 
        g_main_loop_quit(hostnamed_loop);

}

/* wrapper for glib's unix signal handling; called only once if terminatating signal is raised against us */
gboolean unix_sig_terminate_handler(gpointer data) {

    g_printf("caught SIGINT/HUP/TERM, exiting\n");

    hostnamed_mem_clean();
    return G_SOURCE_REMOVE; 
}

void set_signal_handlers() {

    /* we don't care about its descriptor, we never need to unregister these */
    g_unix_signal_add(SIGINT,  unix_sig_terminate_handler, NULL);
    g_unix_signal_add(SIGHUP,  unix_sig_terminate_handler, NULL);
    g_unix_signal_add(SIGTERM, unix_sig_terminate_handler, NULL);

    /* TODO: the "only once" guarantee only counts towards specific signals.
     *       make sure calling a SIGINT and SIGHUP doesn't cause term_handler()
     *       to be called twice */
}

int main() {
    
    set_signal_handlers();

    if(!build_chassis_table() || !determine_chassis_and_icon())
        return 1;
    
    hostnamed_loop     = g_main_loop_new(NULL, TRUE);
    hostnamed_freeable = g_ptr_array_new();

    bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
                                   "org.freedesktop.hostname1",
                                   G_BUS_NAME_OWNER_FLAGS_NONE,
                                   hostnamed_on_bus_acquired,
                                   hostnamed_on_name_acquired,
                                   hostnamed_on_name_lost,
                                   NULL,
                                   NULL);

    g_main_loop_run(hostnamed_loop);
    /* runs until single g_main_loop_quit() call is raised inside <interface>_mem_clean() */
    g_main_loop_unref(hostnamed_loop);

    /* guaranteed unownable */
    g_bus_unown_name(bus_descriptor);

    /* at this point no operations can occur with our data, it is safe to free it + its container */
    g_ptr_array_free(hostnamed_freeable, TRUE);

    return 0;
}

static gboolean build_chassis_table() {
   return TRUE; 
}

gboolean determine_chassis_and_icon() {

    char *hwproduct, *hwmodel, *hwvendor;
    size_t hwproduct_size, hwmodel_size, hwvendor_size;
    int hwproduct_name[2], hwmodel_name[2], hwvendor_name[2];
    unsigned int i;

    hwproduct_name[0] = CTL_HW;
    hwproduct_name[1] = HW_PRODUCT;

    hwmodel_name[0] = CTL_HW;
    hwmodel_name[1] = HW_MODEL;

    hwvendor_name[0] = CTL_HW;
    hwvendor_name[1] = HW_VENDOR;

    /* pass NULL buffer to check size first, then pass hw to be filled according to freshly-set hw_size */
    if(-1 == sysctl(hwproduct_name, 2, NULL, &hwproduct_size, NULL, 0) || -1 == sysctl(hwproduct_name, 2, hwproduct, &hwproduct_size, NULL, 0))
        return FALSE;

    if(-1 == sysctl(hwmodel_name, 2, NULL, &hwmodel_size, NULL, 0) || -1 == sysctl(hwmodel_name, 2, hwmodel, &hwmodel_size, NULL, 0))
        return FALSE;
 
    if(-1 == sysctl(hwvendor_name, 2, NULL, &hwvendor_size, NULL, 0) || -1 == sysctl(hwvendor_name, 2, hwvendor, &hwvendor_size, NULL, 0))
        return FALSE;

    /* TODO: test for laptop, if not, dmidecode for desktop vs. server
     *       probably move this code to vm test func and set a global after running it early, once */
 
    for(; i < G_N_ELEMENTS(chassis_indicator_table); i++)
        
        /* if(strcasestr(sysctl_string, vmstring_list[i]))
            return (CHASSIS = ) ? TRUE : FALSE; */

         return FALSE;

    return TRUE; /* temp */
}

/* TODO figure out DMI variables on obsd */
/*static gchar *guess_icon_name() {

    gchar *filebuf = NULL;
    gchar *ret = NULL;

    #if defined(__i386__) || defined(__x86_64__)
    
       Taken with a few minor changes from systemd's hostnamed.c,
       copyright 2011 Lennart Poettering.

       See the SMBIOS Specification 2.7.1 section 7.4.1 for
       details about the values listed here:

       http://www.dmtf.org/sites/default/files/standards/documents/DSP0134_2.7.1.pdf


    if (g_file_get_contents ("/sys/class/dmi/id/chassis_type", &filebuf, NULL, NULL)) {
        switch (g_ascii_strtoull (filebuf, NULL, 10)) {
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
            ret = g_strdup ("computer-desktop");
            goto out;
        case 0x9:
        case 0xA:
        case 0xE:
            ret = g_strdup ("computer-laptop");
            goto out;
        case 0x11:
        case 0x17:
        case 0x1C:
        case 0x1D:
            ret = g_strdup ("computer-server");
            goto out;
        }
    }
    #endif
    ret = g_strdup ("computer");
  out:
    g_free (filebuf);
    return ret;
}*/

