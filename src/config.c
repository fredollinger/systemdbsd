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

	static gchar *config_path;
	int tryopen = 0;
	/* config is already good to go */
	if(config)
		return TRUE;

	/* does config file exist? if not, write one */
	else if(!g_key_file_load_from_data(config, "systemd_compat.conf", &config_path, G_KEY_FILE_KEEP_COMMENTS, NULL)) {
			
			tryopen = g_open("/etc/systemd_compat.conf", O_CREAT, 644);
			
			//TODO clean this up, use g_data_dirs and g_exit
			/* can we open it rw? */
			if(!g_access("/etc/systemd_compat.conf", W_OK) && !tryopen) {
				g_printf("%s\n", "ERROR: cannot open systemd_compat.conf as read/write!");
				return FALSE;
			}
			
			if(tryopen) {
				config_path = "/etc/systemd_compat.conf";
				g_close(tryopen, NULL);
			}

			//TODO set these properly
			config = g_key_file_new();

			g_key_file_set_string(config, "hostnamed", "PrettyHostname", "");
			g_key_file_set_string(config, "hostnamed", "IconName", "Computer");	
			g_key_file_set_string(config, "hostnamed", "ChassisType", "laptop");

			if(!g_key_file_save_to_file(config, config_path, NULL))
				return FALSE;

			return TRUE;

	/* it does it exist and was written to config var */
	} else
		return TRUE;
}
