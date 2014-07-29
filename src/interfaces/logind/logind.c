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
#include <string.h>

#include <glib/gprintf.h>
#include <glib-unix.h>

#include "logind-gen.h"
#include "logind.h"

GPtrArray *logind_freeable;
Login1Manager *logind_interf;

/* --- begin method/property/dbus signal code --- */

/*static gboolean
on_handle_set_hostname(Login1Manager *hn1_passed_interf,
                       GDBusMethodInvocation *invoc,
                       const gchar *greet,
                       gpointer data) {
    return FALSE;
}*/

/*const gchar *
our_get_hostname() {

	gchar *hostname_buf, *ret;
	size_t hostname_divider;

	hostname_buf = (gchar*) g_malloc0(MAXHOSTNAMELEN);
	ret          = (gchar*) g_malloc0(MAXHOSTNAMELEN);
	g_ptr_array_add(logind_freeable, hostname_buf);
	g_ptr_array_add(logind_freeable, ret);

	if(gethostname(hostname_buf, MAXHOSTNAMELEN))
		return "";

	hostname_divider = strcspn(hostname_buf, ".");

	return strncpy(ret, hostname_buf, hostname_divider);
}*/

/* --- end method/property/dbus signal code, begin bus/name handlers --- */

static void logind_on_bus_acquired(GDBusConnection *conn,
                                   const gchar *name,
                                   gpointer user_data) {

    g_print("got bus, name: %s\n", name);   

}

static void logind_on_name_acquired(GDBusConnection *conn,
    		                        const gchar *name,
                                    gpointer user_data) {

    g_print("got '%s' on system bus\n", name);

    logind_interf = login1_manager_skeleton_new();

    /* attach function pointers to generated struct's method handlers
    g_signal_connect(logind_interf, "handle-set-hostname", G_CALLBACK(on_handle_set_hostname), NULL); */

    /* set our properties before export
    login1_manager_set_hostname(logind_interf, our_get_hostname()); */
 
    if(!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(logind_interf),
                                         conn,
                                         "/org/freedesktop/login1_manager",
                                         NULL)) {

        g_printf("Failed to export Login1Manager's interface!");
    }

}

static void logind_on_name_lost(GDBusConnection *conn,
                                const gchar *name,
                                gpointer user_data) {

    g_print("lost name %s, exiting...", name);

    logind_mem_clean();
    g_dbus_interface_skeleton_unexport(G_DBUS_INTERFACE_SKELETON(logind_interf));

}

/* --- end bus/name handlers, begin misc unix functions --- */

/* free()'s */
void logind_mem_clean() {

    g_ptr_array_foreach(logind_freeable, (GFunc) g_free, NULL);
	g_ptr_array_free(logind_freeable, TRUE);
}

int main() {

	guint bus_descriptor;
	GMainLoop *logind_loop;

	logind_loop = g_main_loop_new(NULL, TRUE);
	logind_freeable = g_ptr_array_new();

	 bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
                                    "org.freedesktop.login1_manager",
                                    G_BUS_NAME_OWNER_FLAGS_NONE,
                                    logind_on_bus_acquired,
                                    logind_on_name_acquired,
                                    logind_on_name_lost,
                                    NULL,
                                    NULL);

	g_main_loop_run(logind_loop);
	g_main_loop_unref(logind_loop);

	g_bus_unown_name(bus_descriptor);

	logind_mem_clean();

	return 0;
}
