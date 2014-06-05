#include <gio/gio.h>
#include "interfaces/hostnamed/hostnamed.c"

int main() {
	GMainLoop *mloop = NULL;
	
	mloop = g_main_loop_new(NULL, FALSE);
	hostnamed_init();
	g_main_loop_run(mloop);

	return 0;
}
