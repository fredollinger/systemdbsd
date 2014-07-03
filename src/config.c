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
#include <fcntl.h>
#include <gio/gio.h>
#include "config.h"

static GKeyFile *config;
static int config_descr;
static gchar *data_dir;

/* NULL if key doesn't exist */
gchar *get_option(gchar *key, gchar *group) {

    if(!group)
        group = "default";

    return g_key_file_get_string(config, group, key, NULL);
}

/* false if key isn't already defined or value is invalid */
gboolean set_option(gchar *key, gchar *value, gchar *group) {

    if(!group)
        group = "default";

    if(!g_key_file_get_string(config, group, key, NULL))
        return FALSE;

    /* TODO safteycheck value */
    g_key_file_set_string(config, group, key, value);
    return TRUE;
}

/* initial load/check */
gboolean config_init() {

    /* config is already set */
    if(config)
        return TRUE;
    
    config = g_key_file_new();
    
    const gchar *config_path;
    GStatBuf *config_lstat;
    int config_lstat_ret;

    config_path = "/etc/systemd_compat.conf";
    config_lstat_ret = g_lstat(config_path, config_lstat);

    if(g_access(config_path, W_OK)) {

        g_printf("%s\n", "no write permissions for /etc/! exiting..");
        return FALSE;

    } else if(g_key_file_load_from_file(config, config_path, G_KEY_FILE_KEEP_COMMENTS, NULL))
        return TRUE;

    g_printf("could not read config at %s! exiting..", config_path);
    return FALSE;
}

void clean_config() {

    /* TODO g_ptr_array all of this */
    g_free(config);
    g_free(data_dir);
    g_close(config_descr, NULL);
}
