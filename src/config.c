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

static GKeyFile *config;

static const gchar *CONFIG_KEYS[] = {
	"PrettyHostname",
	"IconName",
	"ChassisType"
};

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

	//TODO safteycheck value
	g_key_file_set_string(config, group, key, value);
	return TRUE;
}

/* initial load/check */
gboolean config_init() {

	if(config)
		return TRUE; //already init'd

	config = g_key_file_new();
	
	const gchar *config_path;
	GStatBuf *config_lstat;

	config_path = "/etc/systemd_compat.conf";

	/* does conf exist? */
	if(g_lstat(config_path, config_lstat)) {

		/* if not, can we write it */
		if(g_access("/etc/", W_OK)) {
			g_printf("%s\n", "no write permissions for /etc/! exiting..");
			return FALSE;
		}

		int config_descr;
		config_descr = g_open(config_path, O_CREAT, 644);

		gchar *posix_hostname;
		posix_hostname = g_malloc(255); 

		gethostname(posix_hostname, 255);

		g_key_file_set_string(config, "hostnamed", "Hostname", posix_hostname);
		g_key_file_set_string(config, "hostnamed", "PrettyHostname", "");
		g_key_file_set_string(config, "hostnamed", "IconName", "Computer");	
		g_key_file_set_string(config, "hostnamed", "ChassisType", "laptop"); //TODO set these correctly

		if(!g_key_file_save_to_file(config, config_path, NULL)) {
			g_printf("failed to write config to %s!\n", config_path);
			g_free(posix_hostname);
			return FALSE;
		}

		g_printf("wrote config to %s\n", config_path);

		g_free(posix_hostname);

		return TRUE;

	/* it does exist, read it */
	} else {

		if(!g_access(config_path, W_OK)) {
			g_printf("%s\n", "no write permissions for /etc/! exiting..");
			return FALSE;
		} else if(g_key_file_load_from_file(config, config_path, G_KEY_FILE_KEEP_COMMENTS, NULL))
			return TRUE;

		g_printf("could not read config at %s! exiting..", config_path);
		return FALSE;
	}
}
