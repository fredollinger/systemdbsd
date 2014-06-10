#include <gio/gio.h>

GDBusNodeInfo *spect_data;

static gchar *hostname;
static gchar *pretty_hostname;
static gchar *static_hostname;
static gchar *icon_name;

static void handle_method_call(GDBusConnection *conn,
			   				   const gchar *sender,
							   const gchar *obj_path,
							   const gchar *interf_name,
							   const gchar *method_name,
							   GVariant *params,
							   GDBusMethodInvocation *invc,
							   gpointer usrdat) {

	if(g_strcmp0(interf_name, "org.freedesktop.DBus.Introspectable") == 0) {

		GVariant *xml_ret_gvar;
		GString  *xml_ret;
	
		g_dbus_interface_info_generate_xml(spect_data->interfaces[0], (guint)0, xml_ret);
		xml_ret_gvar = g_variant_new_string(xml_ret->str);
		g_dbus_method_invocation_return_value(invc, xml_ret_gvar);
	} 

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

	GError *err;

	g_print("got bus, name: %s\n", name);	

	//GDBusObjectSkeleton *hostnamed_dbobj = g_dbus_object_skeleton_new("/org/freedesktop/hostname1");

	g_dbus_connection_register_object(conn,
									  "/org/freedesktop/hostname1",
									  spect_data->interfaces[0],
									  &interface_vtable,
									  NULL, NULL, NULL);
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
	//TODO exit through g_main_loop properly...
	exit(0);
}

/* safe call to try and start hostnamed */
GError * hostnamed_init() {

	guint bus_descriptor;
	GError *err = NULL;
	gchar **hostnamed_ispect_xml = g_malloc(3000);
	gchar  *hostnamed_joined_xml = g_malloc(3000);

	g_file_get_contents("conf/hostnamed-ispect.xml", hostnamed_ispect_xml, NULL, err);
	hostnamed_joined_xml = g_strjoinv("\n", hostnamed_ispect_xml);
	spect_data = g_dbus_node_info_new_for_xml(hostnamed_joined_xml, NULL);
	
	bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
	                                "org.freedesktop.hostname1",
				                    G_BUS_NAME_OWNER_FLAGS_NONE,
				                    on_bus_acquired,
				                    on_name_acquired,
				                    on_name_lost,
				                    NULL,
				                    NULL);

	//TODO: malloc and return reference as if a main() closed
	return err;
}
