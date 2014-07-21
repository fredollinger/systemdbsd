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

#include <gio/gio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>

#include "config.c"

gboolean systemd_utils_init() {

	if(!config_init()) {

        g_printf("FAILED to open config /etc/systemd_compat.conf! did you `make install`?\n", tmp);
        return FALSE;
    }

    return TRUE;
}

int main() {

	GMainLoop *mloop;		
	mloop = g_main_loop_new(NULL, TRUE);
			
	if(!systemd_utils_init()) {
		g_printf("failed to init, are you root?\n");
		return 1; /* TODO errno properly. grep for all "return 1;"s, not TODO'ing each one */
	}

	gboolean hostnamed_init_ok, localed_init_ok;
	GPid *hostnamed_pid, *localed_pid;
	gchar *hostnamed_argv[0], *localed_argv[0];
	GSource *hostnamed_source, *localed_source, *timedated_source, *logind_source;

	hostnamed_argv[0] = "/usr/local/libexec/systemd-hostnamed-handler";
	localed_argv[0] = "/usr/local/libexec/systemd-localed-handler";

	g_main_loop_run(mloop);
	g_main_loop_unref(mloop);

	return 0;
}
