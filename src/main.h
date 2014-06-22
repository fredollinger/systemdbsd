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

//TODO change this to config dir, not data dir
gboolean install_conf() {
    gchar *our_conf_uri   = "systemd-utl/xml-conf/";
    gchar **data_dir = g_get_system_data_dirs();

    if(g_strcmp0(data_dir[0], NULL)) {
        const gchar our_conf_path[256];
        g_snprintf(our_conf_path, sizeof our_conf_path, "%s%s", *data_dir, our_conf_uri);
        GError **errors;

        /*TODO permissions w/ this */
        g_mkdir_with_parents(our_conf_path, 0644);
    
        return FALSE;
        //return (errors[0] == NULL);

        } else
            return FALSE;
}
