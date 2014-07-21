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

#include <sys/param.h>

#include <glib/gprintf.h>

#include "hostnamed-gen.h"

GPtrArray *hostnamed_freeable;
GDBusNodeInfo *spect_data;
Hostname1 *hostnamed_interf;

/* begin method/property/signal code */

/* TODO make sure these guys only work if called by root */
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

	int hostname_try;
	gchar *hostname_buf;

	hostname_buf = (gchar*) g_malloc0(MAXHOSTNAMELEN);
	hostname_try = gethostname(hostname_buf, MAXHOSTNAMELEN);

	return hostname_buf;
}

const gchar *
our_get_static_hostname() {

    return "TODO";
}

const gchar *
our_get_pretty_hostname() {

    return "TODO";
}

const gchar *
our_get_chassis() {

    return "TODO";
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

/* end method/property/signal code, begin bus/name handlers */

static void hostnamed_on_bus_acquired(GDBusConnection *conn,
                            const gchar *name,
                            gpointer user_data) {

    g_print("got bus, name: %s\n", name);   

}

static void hostnamed_on_name_acquired(GDBusConnection *conn,
    		                           const gchar *name,
                                       gpointer user_data) {

    g_print("got '%s' on system bus\n", name);

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

        g_printf("Failed to export Hostname1's interface!");
    }

}

/* free()'s */
void hostnamed_mem_clean() {

    g_ptr_array_foreach(hostnamed_freeable, (GFunc) g_free, NULL);
}

static void hostnamed_on_name_lost(GDBusConnection *conn,
                                   const gchar *name,
                                   gpointer user_data) {

    g_print("lost name %s, exiting...", name);

    hostnamed_mem_clean();
    g_dbus_interface_skeleton_unexport(G_DBUS_INTERFACE_SKELETON(hostnamed_interf));

}

/* safe call to try and start hostnamed */
void hostnamed_init() {

    guint bus_descriptor;

    bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
                                    "org.freedesktop.hostname1",
                                    G_BUS_NAME_OWNER_FLAGS_NONE,
                                    hostnamed_on_bus_acquired,
                                    hostnamed_on_name_acquired,
                                    hostnamed_on_name_lost,
                                    NULL,
                                    NULL);

}

int main() {

	GMainLoop *hostnamed_loop;
	hostnamed_loop = g_main_loop_new(NULL, TRUE);

	/* config stuff here */


	hostnamed_init();
	g_main_loop_run(hostnamed_loop);
	g_main_loop_unref(hostnamed_loop);

	return 0;
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

