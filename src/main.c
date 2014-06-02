#include <gio/gio.h>
#include "interfaces/hostnamed/hostnamed.c"

int main() {
	hostnamed_init();
	
	return 0;
}
