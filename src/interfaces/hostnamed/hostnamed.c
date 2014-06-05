#include <gio/gio.h>

GDBusNodeInfo *spect_data;

static void handle_method_call(GDBusConnection *conn,
			   				   const gchar *sender,
							   const gchar *obj_path,
							   const gchar *interf_name,
							   const gchar *method_name,
							   GVariant *params,
							   GDBusMethodInvocation *invc,
							   gpointer usrdat) {

	//if(g_strcmp0(method_name, "Introspect"

	GVariant *xml_ret_gvar;
	GString  *xml_ret;
	
	g_dbus_interface_info_generate_xml(spect_data->interfaces[0], (guint)0, xml_ret);
	xml_ret_gvar = g_variant_new_string(xml_ret->str);
	g_dbus_method_invocation_return_value(invc, xml_ret_gvar);

}

static GVariant * handle_get_property(GDBusConnection *conn,
									  const gchar *sender,
									  const gchar *obj_path,
									  const gchar *interf_name,
									  const gchar *prop_name,
									  GError **err,
									  gpointer usr_data) {
		
	GVariant *ret;

	return ret;
}

static gboolean handle_set_property(GDBusConnection *conn,
									const gchar *sender,
									const gchar *obj_path,
									const gchar *interf_name,
									const gchar *prop_name,
									GVariant *val,
									GError **err,
									gpointer usr_data) {

	g_dbus_connection_emit_signal(conn,
								  NULL,
								  obj_path,
								  "org.freedesktop.DBus.Properties",
								  "PropertiesChanged",
								  NULL, /* incorrect */
								  NULL);

	return TRUE;
}

/* "hot" functions initially passed to gdbus */
static const GDBusInterfaceVTable interface_vtable =
{
	handle_method_call,
	handle_get_property,
	handle_set_property
};

/* end method/property functions, begin bus name handlers
 * TODO: these should be intertwined as to handle edge cases
 * for when the system cannot immediately grab the name, as
 * well as cases where the system unintendedly loses the name
 */
static void on_bus_acquired(GDBusConnection *conn,
							const gchar *name,
							gpointer user_data) {
	g_print("got bus, name: %s\n", name);
	
	guint reg_id;

	reg_id = g_dbus_connection_register_object(conn,
											   "/org/freedesktop/hostname1",
											   spect_data->interfaces[0], 
											   &interface_vtable,
											   NULL,
											   NULL,
											   NULL);
}

static void on_name_acquired(GDBusConnection *conn,
							 const gchar *name,
							 gpointer user_data) {

	g_print("got name %s\n", name);
}

static void on_name_lost(GDBusConnection *conn,
						 const gchar *name,
						 gpointer user_data) {

	g_print("lost name %s, exiting...\n", name);
	//TODO exit through g_main_loop properly...
	exit(0);
}

/* safe call to try and start hostnamed */
GError * hostnamed_init() {

	guint bus_descriptor;
	GError *err = NULL;	
	gchar  **hnd_ispect_xml;
	GDir   *cur_dir;
	gchar  *dir;
	
	cur_dir = g_dir_open("./../", 0, err);

	g_sprintf(dir, "%s\n", g_dir_read_name(cur_dir));

	//g_file_get_contents("../../../../conf/hostnamed-ispect.xml", hnd_ispect_xml, NULL, err);
	//spect_data = g_dbus_node_info_new_for_xml(hnd_ispect_xml, &err);

	bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
	                                (gchar *)"org.freedesktop.hostname1",
				                    G_BUS_NAME_OWNER_FLAGS_NONE,
				                    on_bus_acquired,
				                    on_name_acquired,
				                    on_name_lost,
				                    NULL,
				                    NULL);

	//TODO: malloc and return reference as if a main() closed
	return err;
}
