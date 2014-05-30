#include <gio/gio.h>
#include "modules/hostnamed/hostnamed.c"

int main() {
	GMainLoop *loop;
	
	hostnamed_init();
	
	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	return 0;
}
