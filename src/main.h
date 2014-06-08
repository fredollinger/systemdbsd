#include <gio/gio.h>
#include "xml_defs.h"

//expects valid input, always free() output 
const gchar **get_prefixs(gchar *path, gchar *dname) {
	gsize size = sizeof(path) + sizeof(dname) + 11; //11 extra bytes for file suffix
	const gchar **ret = (gchar**) g_malloc0(2 * size);

	g_snprintf(ret[0], size, "%s%s-ispect.xml", path, dname);
	g_snprintf(ret[1], size, "%s%s-config.xml", path, dname);

	return ret;
}

const GString *strjoin(gchar *sep, GString strings[]) {
	GString *cur;
	GString *out;
	gint n;

	while((cur = &strings[n]) != NULL) {
		g_string_append(out, cur);
		n++;
	}

	return out;
}

gboolean install_conf() {
	gchar *our_conf_uri   = "systemd-utl/xml-conf/";
	gchar **data_dir = g_get_system_data_dirs();

	if(g_strcmp0(data_dir[0], NULL)) {
		const gchar our_conf_path[256];
		g_snprintf(our_conf_path, sizeof our_conf_path, "%s%s", *data_dir, our_conf_uri);
		GError **errors;

		/*TODO permissions w/ this */
		g_mkdir_with_parents(our_conf_path, 0644);

		const gchar   **hostnamed_prefixs   = get_prefixs(our_conf_path, "hostnamed");
		const GString *hostnamed_ispect_xml = strjoin("\n", hostnamed_ispect_xml_def);
		const GString *hostnamed_config_xml = strjoin("\n", hostnamed_config_xml_def);

		const gchar   **timedated_prefixs   = get_prefixs(our_conf_path, "timedated");
		const GString *timedated_ispect_xml = strjoin("\n", timedated_ispect_xml_def);
		const GString *timedated_config_xml = strjoin("\n", timedated_config_xml_def);

		const gchar   **localed_prefixs   = get_prefixs(our_conf_path, "localed");
		const GString *localed_ispect_xml = strjoin("\n", localed_ispect_xml_def);
		const GString *localed_config_xml = strjoin("\n", localed_config_xml_def);

		const gchar   **logind_prefixs   = get_prefixs(our_conf_path, "logind");
		const GString *logind_ispect_xml = strjoin("\n", logind_ispect_xml_def);
		const GString *logind_config_xml = strjoin("\n", logind_config_xml_def);	

		g_file_set_contents(*hostnamed_prefixs[0], hostnamed_config_xml, -1, errors);
		g_file_set_contents(*hostnamed_prefixs[1], hostnamed_config_xml, -1, errors);

		g_file_set_contents(*timedated_prefixs[0], timedated_config_xml, -1, errors);
		g_file_set_contents(*timedated_prefixs[1], timedated_config_xml, -1, errors);

		g_file_set_contents(*localed_prefixs[0], localed_config_xml, -1, errors);
		g_file_set_contents(*localed_prefixs[1], localed_config_xml, -1, errors);

		g_file_set_contents(*logind_prefixs[0], logind_config_xml, -1, errors);
		g_file_set_contents(*logind_prefixs[1], logind_config_xml, -1, errors);

		/* TODO: free() strings */

		return (errors[0] == NULL);

		} else
			return FALSE;
}
