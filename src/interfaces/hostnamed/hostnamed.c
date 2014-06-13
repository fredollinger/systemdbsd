#include <unistd.h>
#include <limits.h>
#include <gio/gio.h>


GDBusNodeInfo *spect_data;

static gchar *hostname;
static gchar *pretty_hostname;
static gchar *static_hostname;
static gchar *icon_name;
static gchar *chassis;
static gchar *kernel_name;
static gchar *kernel_release;
static gchar *kernel_version;
static gchar *os_prettyname;
static gchar *os_cpe;         //common platform enumeration string

static void handle_method_call(GDBusConnection *conn,
			   				   const gchar *sender,
							   const gchar *obj_path,
							   const gchar *interf_name,
							   const gchar *method_name,
							   GVariant *params,
							   GDBusMethodInvocation *invc,
							   gpointer usrdat) {

	if(g_strcmp0(interf_name, "org.freedesktop.DBus.Introspectable") == 0
		&& g_strcmp0(method_name, "Introspect") == 0) {

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
	
	const gchar *our_interf_name = "org.freedesktop.hostname1";
	const gchar *our_obj_path    = "/org/freedesktop/hostname1";

	if(g_strcmp0(interf_name, our_interf_name) != 0
		|| g_strcmp0(obj_path, our_obj_path) != 0) {

		return NULL; //TODO error
	}

	if(g_strcmp0(prop_name, "Hostname") == 0)
		return g_variant_new_string(hostname);

	else if(g_strcmp0(prop_name, "StaticHostname") == 0)
		return g_variant_new_string(static_hostname);

	else if(g_strcmp0(prop_name, "PrettyHostname") == 0)
		return g_variant_new_string(pretty_hostname);

	else if(g_strcmp0(prop_name, "IconName") == 0)
		return g_variant_new_string(icon_name);

	else 
		return NULL; //TODO error
	
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

	if(!init_props())
		return err; //TODO error
	
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

gboolean init_props() {
	
	if(init_hostname()
		&& init_static_hostname()
		&& init_pretty_hostname()
		&& init_icon_name()
		&& init_chassis()
		&& init_kernel_name()
		&& init_kernel_version()
		&& init_os_name()
		&& init_os_cpe() )
		return TRUE;

	return FALSE;
}

//POSIX, for future ports try_hostname should be checked for null-termination
gboolean init_hostname() {

	gchar try_hostname[HOST_NAME_MAX];

	if(!gethostname(try_hostname, HOST_NAME_MAX)) {
		hostname = try_hostname;
		return TRUE;
	}

	return FALSE;
}

gboolean init_static_hostname() {
	//TODO
	return TRUE;
}

gboolean init_pretty_hostname() {
	//TODO
	return TRUE;
}

gboolean init_icon_name() {
	//TODO
	return TRUE;
}

gboolean init_chassis() {
	//TODO
	return TRUE;
}

gboolean init_kernel_name() {
	//TODO
	return TRUE;
}

gboolean init_kernel_version() {
	//TODO
	return TRUE;
}

gboolean init_os_name() {
	//TODO
	return TRUE;
}

gboolean init_os_cpe() {
	//TODO
	return TRUE;
}

//TODO figure out DMI variables on obsd
/*static gchar *guess_icon_name() {

    gchar *filebuf = NULL;
    gchar *ret = NULL;

	//TODO vm check

	#if defined(__i386__) || defined(__x86_64__)
    /*
       Taken with a few minor changes from systemd's hostnamed.c,
       copyright 2011 Lennart Poettering.

       See the SMBIOS Specification 2.7.1 section 7.4.1 for
       details about the values listed here:

       http://www.dmtf.org/sites/default/files/standards/documents/DSP0134_2.7.1.pdf
    */   /*

    if (g_file_get_contents ("/sys/class/dmi/id/chassis_type", &filebuf, NULL, NULL)) {
        switch (g_ascii_strtoull (filebuf, NULL, 10)) {
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
            ret = g_strdup ("computer-desktop");
            goto out;
        case 0x9:
        case 0xA:
        case 0xE:
            ret = g_strdup ("computer-laptop");
            goto out;
        case 0x11:
        case 0x17:
        case 0x1C:
        case 0x1D:
            ret = g_strdup ("computer-server");
            goto out;
        }
    }
	#endif
    ret = g_strdup ("computer");
  out:
    g_free (filebuf);
    return ret;
}*/
