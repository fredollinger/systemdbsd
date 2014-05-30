#include <gio/gio.h>
#include "modules/hostnamed/hostnamed.c"

int main() {
	hostnamed_init();
	
	return 0;
}
