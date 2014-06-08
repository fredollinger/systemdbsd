/* debugging */
#define INSTALL 1
#define NO_BUILTIN_XML 1

/* end debugging */

#include <gio/gio.h>
#include "interfaces/hostnamed/hostnamed.c"
#include "main.h"

int main() {

	#if (defined NO_BUILTIN_XML && defined INSTALL)
		if(!install_conf())
			g_printf("%s\n", "FAILED to install xml configs!");;		
	#else
	#endif

	GMainLoop *mloop = NULL;
	
	mloop = g_main_loop_new(NULL, FALSE);
	hostnamed_init();
	g_main_loop_run(mloop);

	return 0;
}
