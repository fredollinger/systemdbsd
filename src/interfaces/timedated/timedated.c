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

#include "timedated-gen.h"

GPtrArray *timedated_freeable;
Timedate1 *timedated_interf;

/* --- begin method/property/dbus signal code --- */

/*static gboolean
on_handle_set_hostname(Timedate1 *hn1_passed_interf,
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
	g_ptr_array_add(timedated_freeable, hostname_buf);
	g_ptr_array_add(timedated_freeable, ret);

	if(gethostname(hostname_buf, MAXHOSTNAMELEN))
		return "";

	hostname_divider = strcspn(hostname_buf, ".");

	return strncpy(ret, hostname_buf, hostname_divider);
}*/

/* --- end method/property/dbus signal code, begin bus/name handlers --- */

static void timedated_on_bus_acquired(GDBusConnection *conn,
                                      const gchar *name,
                                      gpointer user_data) {

    g_print("got bus, name: %s\n", name);   

}

static void timedated_on_name_acquired(GDBusConnection *conn,
    		                           const gchar *name,
                                       gpointer user_data) {

    g_print("got '%s' on system bus\n", name);

    timedated_interf = timedate1_skeleton_new();

    /* attach function pointers to generated struct's method handlers
    g_signal_connect(timedated_interf, "handle-set-hostname", G_CALLBACK(on_handle_set_hostname), NULL);*/

    /* set our properties before export
    timedate1_set_hostname(timedated_interf, our_get_hostname()); */
 
    if(!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(timedated_interf),
                                         conn,
                                         "/org/freedesktop/timedate1",
                                         NULL)) {

        g_printf("Failed to export Timedate1's interface!");
    }

}

/* --- end bus/name handlers, begin misc functions --- */

/* free()'s */
void timedated_mem_clean() {

    g_ptr_array_foreach(timedated_freeable, (GFunc) g_free, NULL);
	g_ptr_array_free(timedated_freeable, TRUE);
}

static void timedated_on_name_lost(GDBusConnection *conn,
                                   const gchar *name,
                                   gpointer user_data) {

    g_print("lost name %s, exiting...", name);

    timedated_mem_clean();
    g_dbus_interface_skeleton_unexport(G_DBUS_INTERFACE_SKELETON(timedated_interf));

}

int main() {

	guint bus_descriptor;
	GMainLoop *timedated_loop;

	timedated_loop = g_main_loop_new(NULL, TRUE);
	timedated_freeable = g_ptr_array_new();

	 bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
                                    "org.freedesktop.timedate1",
                                    G_BUS_NAME_OWNER_FLAGS_NONE,
                                    timedated_on_bus_acquired,
                                    timedated_on_name_acquired,
                                    timedated_on_name_lost,
                                    NULL,
                                    NULL);

	g_main_loop_run(timedated_loop);
	g_main_loop_unref(timedated_loop);

	g_bus_unown_name(bus_descriptor);

	timedated_mem_clean();

	return 0;
}
