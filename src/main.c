/* debugging */
#define INSTALL 1
//#define NO_BUILTIN_XML 1
/* end debugging */

#include <gio/gio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>
#include "config.c"
#include "interfaces/hostnamed/hostnamed.c"
//#include "main/h"

gboolean systemd_utils_init() {
	#ifdef INSTALL
		if(!config_init()) {
			g_printf("%s\n", "FAILED to install configs in /etc/!");
			return FALSE; 
		}
	#endif
	return TRUE;
}

int main() {

	GMainLoop *mloop;
	
	if(!systemd_utils_init()) {
		g_printf("failed to init, are you root?\n");
		return 1; //TODO errno properly. grep for all "return 1;"s, not TODO'ing each one
	}

	hostnamed_init();

	mloop = g_main_loop_new(NULL, TRUE);

	g_main_loop_run(mloop);
	g_main_loop_unref(mloop);

	return 0;
}
