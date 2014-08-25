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

#include <sys/types.h>
#include <time.h>
#include <string.h>

#include <glib/gprintf.h>
#include <glib-unix.h>
#include <glib/gstdio.h>
#include <polkit/polkit.h>

#include "timedated-gen.h"
#include "timedated.h"

#include "../../util.h"

GPtrArray *timedated_freeable;
Timedate1 *timedated_interf;

GMainLoop *timedated_loop;

guint bus_descriptor;
gboolean dbus_interface_exported; /* reliable because of gdbus operational guarantees */

const gchar *OS_LOCALTIME     = "/etc/localtime";      /* current timezone file */
const gchar *OS_TIMEZONE_PATH = "/usr/share/zoneinfo"; /* path to system timezone files */

/* --- begin method/property/dbus signal code --- */

static gboolean
on_handle_set_time(Timedate1 *hn1_passed_interf,
                   GDBusMethodInvocation *invoc,
                   const gchar *greet,
                   gpointer data) {
    return FALSE;
}

static gboolean
on_handle_set_timezone(Timedate1 *hn1_passed_interf,
                   GDBusMethodInvocation *invoc,
                   const gchar *greet,
                   gpointer data) {
    return FALSE;
}

static gboolean
on_handle_set_local_rtc(Timedate1 *hn1_passed_interf,
                        GDBusMethodInvocation *invoc,
                        const gchar *greet,
                        gpointer data) {
    return FALSE;
}

static gboolean
on_handle_set_ntp(Timedate1 *hn1_passed_interf,
                  GDBusMethodInvocation *invoc,
                  const gchar *greet,
                  gpointer data) {
    return FALSE;
}

const gchar *
our_get_timezone() {

    GStatBuf *stat_zoneinfo;
    gchar *find_cmd, *readlink_path, *ret;
    GError *err = NULL;

    find_cmd      = (gchar *)   g_malloc0(2048);
    stat_zoneinfo = (GStatBuf*) g_malloc0(8192);

    if(g_stat(OS_LOCALTIME, stat_zoneinfo)) {

        g_printf("could not read from %s! please symlink or copy a timezone file from %s to %s!\n", OS_LOCALTIME, OS_TIMEZONE_PATH, OS_LOCALTIME);
        ret = NULL;

    } else if(g_file_test(OS_LOCALTIME, G_FILE_TEST_IS_SYMLINK)) {

        readlink_path = g_file_read_link(OS_LOCALTIME, &err);
        ret = parse_timezone_path(readlink_path);

        if(readlink_path)
            g_free(readlink_path);

    } else {

        g_printf("%s is not a symlink! attempting to match checksums in %s...\n", OS_LOCALTIME, OS_TIMEZONE_PATH);
        g_sprintf(find_cmd, "find %s -type f", OS_TIMEZONE_PATH);
        ret = NULL;
    }

    return ret;
}

gboolean
our_get_local_rtc() { 

    gboolean ret = FALSE;

    return ret;
}

gboolean
our_get_can_ntp() {
 
    const gboolean ret = FALSE;

    return ret;
}

gboolean
our_get_ntp() {
 
    const gboolean ret = FALSE;

    return ret;
}

gboolean
our_get_ntpsynchronized() {
 
    const gboolean ret = FALSE;

    return ret;
}

guint64
our_get_time_usec() {

    guint64 ret = 0;

    return ret;
}

guint64
our_get_rtc_time_usec() {

    guint64 ret = 0;

    return ret;
}

/* --- end method/property/dbus signal code, begin bus/name handlers --- */

static void timedated_on_bus_acquired(GDBusConnection *conn,
                                      const gchar *name,
                                      gpointer user_data) {

    g_printf("got bus/name, exporting %s's interface...\n", name);

    timedated_interf = timedate1_skeleton_new();

    /* attach function pointers to generated struct's method handlers */
    g_signal_connect(timedated_interf, "handle-set-time",     G_CALLBACK(on_handle_set_time),     NULL);
    g_signal_connect(timedated_interf, "handle-set-timezone", G_CALLBACK(on_handle_set_timezone), NULL);
    g_signal_connect(timedated_interf, "handle-set-local-rtc", G_CALLBACK(on_handle_set_local_rtc), NULL);
    g_signal_connect(timedated_interf, "handle-set-ntp",      G_CALLBACK(on_handle_set_ntp),      NULL);
    /* set our properties before export */
    timedate1_set_timezone(timedated_interf, our_get_timezone());
    timedate1_set_local_rtc(timedated_interf, our_get_local_rtc());
    timedate1_set_can_ntp(timedated_interf, our_get_can_ntp());
    timedate1_set_ntp(timedated_interf, our_get_ntp());
    timedate1_set_ntpsynchronized(timedated_interf, our_get_ntpsynchronized());
    timedate1_set_time_usec(timedated_interf, our_get_time_usec());
    timedate1_set_rtctime_usec(timedated_interf, our_get_rtc_time_usec());
    
    if(!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(timedated_interf),
                                         conn,
                                         "/org/freedesktop/timedate1",
                                         NULL)) {

        g_printf("failed to export %s's interface!\n", name);
        timedated_mem_clean();

    } else {

        dbus_interface_exported = TRUE;
        g_printf("exported %s's interface on the system bus...\n", name);
    }
}

static void timedated_on_name_acquired(GDBusConnection *conn,
                                       const gchar *name,
                                       gpointer user_data) {

   g_printf("success!\n"); 
}

static void timedated_on_name_lost(GDBusConnection *conn,
                                   const gchar *name,
                                   gpointer user_data) {

    if(!conn) {

        g_printf("failed to connect to the system bus while trying to acquire name '%s': either dbus-daemon isn't running or we don't have permission to push names and/or their interfaces to it.\n", name);
        timedated_mem_clean();
    }

    g_print("lost name %s, exiting...\n", name);

    timedated_mem_clean();
}

/* --- end bus/name handlers, begin misc unix functions --- */

/* safe call to clean and then exit
 * this stops our GMainLoop safely before letting main() return */
void timedated_mem_clean() {

    g_printf("exiting...\n");

    if(dbus_interface_exported)
        g_dbus_interface_skeleton_unexport(G_DBUS_INTERFACE_SKELETON(timedated_interf));

     if(g_main_loop_is_running(timedated_loop))
        g_main_loop_quit(timedated_loop);

}

/* wrapper for glib's unix signal handling; called only once if terminating signal is raised against us */
gboolean unix_sig_terminate_handler(gpointer data) {

    g_printf("caught SIGINT/HUP/TERM, exiting\n");

    timedated_mem_clean();
    return G_SOURCE_REMOVE;
}

void set_signal_handlers() {

    /* we don't care about its descriptor, we never need to unregister these */
    g_unix_signal_add(SIGINT,  unix_sig_terminate_handler, NULL);
    g_unix_signal_add(SIGHUP,  unix_sig_terminate_handler, NULL);
    g_unix_signal_add(SIGTERM, unix_sig_terminate_handler, NULL);
}

int main() {

    set_signal_handlers();

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
    /* runs until single g_main_loop_quit() call is raised inside <interface>_mem_clean() */
    g_main_loop_unref(timedated_loop);

    /* guaranteed unownable */
    g_bus_unown_name(bus_descriptor);

    /* at this point no operations can occur with our data, it is safe to free it + its container */
    g_ptr_array_free(timedated_freeable, TRUE);

    return 0;
}

static gchar *parse_timezone_path(gchar *full_path) {

    gchar *prefix_pattern;
    GRegex *prefix, *posix, *right;
    GError *err = NULL;

    if(!full_path)
        return NULL;

    prefix_pattern = (gchar *) g_malloc0(4096);
    g_sprintf(prefix_pattern, "^%s/$", OS_TIMEZONE_PATH);

    prefix = g_regex_new(prefix_pattern, 0, 0, &err);
    posix  = g_regex_new("^posix/$",     0, 0, &err);
    right  = g_regex_new("^right/$",     0, 0, &err);

    g_regex_unref(prefix);
    g_regex_unref(right);
    g_regex_unref(posix);

    return NULL; /* TODO temp */
}
