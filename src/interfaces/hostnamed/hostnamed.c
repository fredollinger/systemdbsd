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

#include <glib.h>
#include <gio/gio.h>

#include "hostnamed.h"
#include "hostnamed-gen.c"

GPtrArray *hostnamed_freeable;
GDBusNodeInfo *spect_data;

static void on_bus_acquired(GDBusConnection *conn,
                            const gchar *name,
                            gpointer user_data) {

    GError *err;

    g_print("got bus, name: %s\n", name);   

}

static void on_name_acquired(GDBusConnection *conn,
                             const gchar *name,
                             gpointer user_data) {

    g_print("got name %s\n", name);
}

static void on_name_lost(GDBusConnection *conn,
                         const gchar *name,
                         gpointer user_data) {

    g_print("lost name %s, exiting...", name);

    hostnamed_mem_clean();

    /* TODO exit through g_main_loop properly... */
}

/* safe call to try and start hostnamed */
GError *hostnamed_init() {

    guint bus_descriptor;
    GError *err = NULL;
    gchar **hostnamed_ispect_xml;
    gchar  *hostnamed_joined_xml;

    hostnamed_freeable = g_ptr_array_new();
    hostnamed_ispect_xml = g_malloc(3000);

    g_file_get_contents("conf/hostnamed-ispect.xml", hostnamed_ispect_xml, NULL, NULL);
    hostnamed_joined_xml = g_strjoinv("\n", hostnamed_ispect_xml);
    spect_data = g_dbus_node_info_new_for_xml(hostnamed_joined_xml, NULL);

    g_free(hostnamed_ispect_xml);
    g_ptr_array_add(hostnamed_freeable, hostnamed_joined_xml);

    bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
                                    "org.freedesktop.hostname1",
                                    G_BUS_NAME_OWNER_FLAGS_NONE,
                                    on_bus_acquired,
                                    on_name_acquired,
                                    on_name_lost,
                                    NULL,
                                    NULL);

    /* TODO: malloc and return reference as if a main() closed */
    return err;
}

/* free()'s */
void hostnamed_mem_clean() {

    g_ptr_array_foreach(hostnamed_freeable, (GFunc) g_free, NULL);
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
