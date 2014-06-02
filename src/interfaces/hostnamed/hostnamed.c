#include <gio/gio.h>

/* testing, for now */
static GDBusNodeInfo *spect_data = NULL;
static const gchar spect_xml[] = 
		"<node>"
		" <interface name='org.freedesktop.DBus.Peer'>"
		"  <method name='Ping'/>"
		"  <method name='GetMachineId'>"
		"   <arg type='s' name='machine_uuid' direction='out'/>"
		"  </method>"
		" </interface>"
		" <interface name='org.freedesktop.DBus.Introspectable'>"
		"  <method name='Introspect'>"
		"   <arg name='data' type='s' direction='out'/>"
		"  </method>"
		" </interface>"
		" <interface name='org.freedesktop.DBus.Properties'>"
		"  <method name='Get'>"
		"   <arg name='interface' direction='in' type='s'/>"
		"   <arg name='property' direction='in' type='s'/>"
		"   <arg name='value' direction='out' type='v'/>"
		"  </method>"
		"  <method name='GetAll'>"
		"   <arg name='interface' direction='in' type='s'/>"
		"   <arg name='properties' direction='out' type='a{sv}'/>"
		"  </method>"
		"  <method name='Set'>"
		"   <arg name='interface' direction='in' type='s'/>"
		"   <arg name='property' direction='in' type='s'/>"
		"   <arg name='value' direction='in' type='v'/>"
		"  </method>"
		"  <signal name='PropertiesChanged'>"
		"   <arg type='s' name='interface'/>"
		"   <arg type='a{sv}' name='changed_properties'/>"
		"   <arg type='as' name='invalidated_properties'/>"
		"  </signal>"
		" </interface>"
		" <interface name='org.freedesktop.hostname1'>"
		"  <property name='Hostname' type='s' access='read'>"
		"   <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
		"  </property>"
		"  <property name='StaticHostname' type='s' access='read'>"
		"  </property>"
		"  <property name='PrettyHostname' type='s' access='read'>"
		"  </property>"
		"  <property name='IconName' type='s' access='read'>"
		"  </property>"
		"  <property name='Chassis' type='s' access='read'>"
		"  </property>"
		"  <property name='KernelName' type='s' access='read'>"
		"   <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
		"  </property>"
		"  <property name='KernelRelease' type='s' access='read'>"
		"   <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
		"  </property>"
		"  <property name='KernelVersion' type='s' access='read'>"
		"   <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
		"  </property>"
		"  <property name='OperatingSystemPrettyName' type='s' access='read'>"
		"   <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
		"  </property>"
		"  <property name='OperatingSystemCPEName' type='s' access='read'>"
		"   <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
		"  </property>"
		"  <method name='SetHostname'>"
		"   <arg type='s' direction='in'/>"
		"   <arg type='b' direction='in'/>"
		"  </method>"
		"  <method name='SetStaticHostname'>"
		"   <arg type='s' direction='in'/>"
		"   <arg type='b' direction='in'/>"
		"  </method>"
		"  <method name='SetPrettyHostname'>"
		"   <arg type='s' direction='in'/>"
		"   <arg type='b' direction='in'/>"
		"  </method>"
		"  <method name='SetIconName'>"
		"   <arg type='s' direction='in'/>"
		"   <arg type='b' direction='in'/>"
		"  </method>"
		"  <method name='SetChassis'>"
		"   <arg type='s' direction='in'/>"
		"   <arg type='b' direction='in'/>"
		"  </method>"
		" </interface>"
		"</node>";

static void handle_method_call(GDBusConnection *conn,
				const gchar *sender,
				const gchar *obj_path,
				const gchar *interf_name,
				const gchar *method_name,
				GVariant *params,
				GDBusMethodInvocation *invc,
				gpointer usrdat) {

		g_printf("%s wants to call %s, at %s with interface %s\n", sender, method_name, obj_path, interf_name);

		g_dbus_method_invocation_return_value(invc, &spect_xml);

}


static GVariant * handle_get_property(GDBusConnection *conn,
				const gchar *sender,
				const gchar *obj_path,
				const gchar *interf_name,
				const gchar *prop_name,
				GError **err,
				gpointer usr_data) {
		
		GVariant *ret;
		ret = g_variant_new_string("");
		g_snprintf(ret, 100, "%s touched property %s at %s", sender, prop_name, obj_path);

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

static const GDBusInterfaceVTable interface_vtable =
{
  handle_method_call,
  handle_get_property,
  handle_set_property
};



static void on_bus_acquired(GDBusConnection *conn, const gchar *name, gpointer user_data) {
	g_print("got bus, name: %s\n", name);
	
	guint reg_id;

	reg_id = g_dbus_connection_register_object (conn,
												"/org/freedesktop/hostname1",
												spect_data->interfaces[0], 
												&interface_vtable,
												NULL,
												NULL,
												NULL );
	g_assert(reg_id > 0);
}

static void on_name_acquired(GDBusConnection *conn, const gchar *name, gpointer user_data) {
	g_print("got name %s\n", name);
}

static void on_name_lost(GDBusConnection *conn, const gchar *name, gpointer user_data) {
	g_print("lost name %s, exiting...\n", name);
	exit(1);
}

void hostnamed_init() {

	guint bus_descriptor;
	GError *err = NULL;
	GMainLoop *loop;

	spect_data = g_dbus_node_info_new_for_xml(spect_xml, NULL);

	bus_descriptor = g_bus_own_name(G_BUS_TYPE_SESSION,
	                                (gchar *)"org.freedesktop.hostname1",
				                    G_BUS_NAME_OWNER_FLAGS_NONE,
				                    on_bus_acquired,
				                    on_name_acquired,
				                    on_name_lost,
				                    NULL,
				                    NULL);

	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	/* unclear */

	g_bus_unown_name(bus_descriptor);
	g_dbus_node_info_unref(spect_data);
}
