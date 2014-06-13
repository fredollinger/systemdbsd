/* debugging */
//#define INSTALL 1
//#define NO_BUILTIN_XML 1
/* end debugging */

#include <gio/gio.h>
#include <config.c>
#include "interfaces/hostnamed/hostnamed.c"
//#include "main.h"

#ifdef INSTALL
static gboolean install_conf() {
	
}
#endif

int main() {
	//TODO cleanup
	#ifdef INSTALL
		if(!install_conf()) {
			g_printf("%s\n", "FAILED to install configs in /etc/!");
			exit(1);
		}
	#endif

	//TODO cleanup
	#if (defined NO_BUILTIN_XML && defined INSTALL)
		if(!install_conf()) {
			g_printf("%s\n", "FAILED to install xml configs!");
			exit(1);
		}
	#else
	#endif

	GMainLoop *mloop = NULL;
	
	mloop = g_main_loop_new(NULL, FALSE);
	hostnamed_init();
	g_main_loop_run(mloop);

	return 0;
}

