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
#include <string.h>

#include <glib/gprintf.h>
#include <glib-unix.h>

#include "hostnamed-gen.h"
#include "hostnamed.h"

GPtrArray *hostnamed_freeable;
Hostname1 *hostnamed_interf;

GMainLoop *hostnamed_loop;

guint bus_descriptor;
gboolean dbus_interface_exported; /* reliable because of gdbus operational guarantees */

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

	hostname_buf = (gchar*) g_malloc0(MAXHOSTNAMELEN); /* todo check & free */
	ret          = (gchar*) g_malloc0(MAXHOSTNAMELEN);
	g_ptr_array_add(hostnamed_freeable, hostname_buf);
	g_ptr_array_add(hostnamed_freeable, ret);

	if(gethostname(hostname_buf, MAXHOSTNAMELEN))
		return "";

	hostname_divider = strcspn(hostname_buf, ".");

	return strncpy(ret, hostname_buf, hostname_divider);
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

	hostnamed_loop = g_main_loop_new(NULL, TRUE);
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

