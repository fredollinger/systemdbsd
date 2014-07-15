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

#include "localed-gen.h"

GPtrArray *localed_freeable;
GDBusNodeInfo *spect_data;
localedLocale1 *localed_interf;

/* begin method/property/signal code */

/* TODO make sure these guys only work if called by root */

/* Example:
static gboolean
on_handle_set_hostname(localedLocale1 *hn1_passed_interf,
                       GDBusMethodInvocation *invoc,
                       const gchar *greet,
                       gpointer data) {
    return FALSE;
} */

/* note: all localed/locale1's properties are read-only,
 * and do not need set_ functions, gdbus-codegen realized
 * this from the XML and handled the to-be error of trying
 * to set a read-only property's value 
 */

/* Example:

const gchar *
our_get_hostname() {

    return "TODO";
}*/

/* end method/property/signal code, begin bus/name handlers */

static void localed_on_bus_acquired(GDBusConnection *conn,
                            const gchar *name,
                            gpointer user_data) {

    g_print("got bus, name: %s\n", name);   

}

static void localed_on_name_acquired(GDBusConnection *conn,
                             const gchar *name,
                             gpointer user_data) {

    g_print("got '%s' on system bus\n", name);

    localed_interf = localed_locale1_skeleton_new();

    /* attach function pointers to generated struct's method handlers */
    /*g_signal_connect(localed_interf, "handle-set-hostname", G_CALLBACK(on_handle_set_hostname), NULL);
    g_signal_connect(localed_interf, "handle-set-static-hostname", G_CALLBACK(on_handle_set_static_hostname), NULL);
    g_signal_connect(localed_interf, "handle-set-pretty-hostname", G_CALLBACK(on_handle_set_pretty_hostname), NULL);
    g_signal_connect(localed_interf, "handle-set-chassis", G_CALLBACK(on_handle_set_chassis), NULL);
    g_signal_connect(localed_interf, "handle-set-icon-name", G_CALLBACK(on_handle_set_icon_name), NULL); */

    /* set our properties before export */
    /*localed_locale1_set_hostname(localed_interf, our_get_hostname());
    localed_locale1_set_static_hostname(localed_interf, our_get_static_hostname());
    localed_locale1_set_pretty_hostname(localed_interf, our_get_pretty_hostname());
    localed_locale1_set_chassis(localed_interf, our_get_chassis());
    localed_locale1_set_icon_name(localed_interf, our_get_icon_name());
    localed_locale1_set_kernel_name(localed_interf, our_get_kernel_name());
    localed_locale1_set_kernel_version(localed_interf, our_get_kernel_version());
    localed_locale1_set_kernel_release(localed_interf, our_get_kernel_release());
    localed_locale1_set_operating_system_cpename(localed_interf, our_get_os_cpename());
    localed_locale1_set_operating_system_pretty_name(localed_interf, our_get_os_pretty_name()); */
 
    if(!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(localed_interf),
                                                                   conn,
                                                                   "/org/freedesktop/locale1",
                                                                   NULL)) {

        g_printf("failed to export locale1's interface on system bus!");
    }

}

/* free()'s */
void localed_mem_clean() {

    g_ptr_array_foreach(localed_freeable, (GFunc) g_free, NULL);
}

static void localed_on_name_lost(GDBusConnection *conn,
                         const gchar *name,
                         gpointer user_data) {

    g_print("lost name %s, exiting...", name);

    localed_mem_clean();
    g_dbus_interface_skeleton_unexport(G_DBUS_INTERFACE_SKELETON(localed_interf));

    /* TODO exit through g_main_loop properly... */
}

/* safe call to try and start localed */
void localed_init() {

    guint bus_descriptor;
    GError *err = NULL;
    gchar **localed_ispect_xml;
    gchar  *localed_joined_xml;

    localed_freeable = g_ptr_array_new();
    localed_ispect_xml = g_malloc(3000);

    g_file_get_contents("conf/localed-ispect.xml", localed_ispect_xml, NULL, NULL);
    localed_joined_xml = g_strjoinv("\n", localed_ispect_xml);
    spect_data = g_dbus_node_info_new_for_xml(localed_joined_xml, NULL);

    g_free(localed_ispect_xml);
    g_ptr_array_add(localed_freeable, localed_joined_xml);

    bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
                                    "org.freedesktop.locale1",
                                    G_BUS_NAME_OWNER_FLAGS_NONE,
                                    localed_on_bus_acquired,
                                    localed_on_name_acquired,
                                    localed_on_name_lost,
                                    NULL,
                                    NULL);

    /* TODO: malloc and return reference as if a main() closed */
}

int main() {
	
	GMainLoop *localed_loop;
	localed_loop = g_main_loop_new(NULL, TRUE);

	/* config stuff here */

	localed_init();

	g_main_loop_run(localed_loop);
	g_main_loop_unref(localed_loop);

	return 0;
}

