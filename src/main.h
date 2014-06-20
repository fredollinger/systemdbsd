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
