/* #include <glib-2.0/glib.h> */
#include <gio/gio.h>

static void on_bus_acquired(GDBusConnection *conn, const gchar *name, gpointer user_data) {
	g_print("got bus, name: %s\n", name);

	/* g_print("at %p, data @ %p\n", (void*)conn, user_data); */
}

static void on_name_acquired(GDBusConnection *conn, const gchar *name, gpointer user_data) {
	g_print("got name %s\n", name);

	/* g_print("at %p, data @ %p\n", (void*)conn, user_data); */
}

static void on_name_lost(GDBusConnection *conn, const gchar *name, gpointer user_data) {
	g_print("lost name %s\n", name);

	/* g_print("at %p, data @ %p\n", (void*)conn, user_data); */
}

void hostnamed_init() {
	guint bus_descriptor;
	GError *err = NULL;
	
	bus_descriptor = g_bus_own_name(G_BUS_TYPE_SYSTEM,
	                                (gchar *)"org.freedesktop.hostname1",
				                    G_BUS_NAME_OWNER_FLAGS_NONE,
				                    on_bus_acquired,
				                    on_name_acquired,
				                    on_name_lost,
				                    NULL,
				                    NULL);
}

