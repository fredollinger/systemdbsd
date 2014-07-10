.PHONY: all

CFLAGS=-Wall -Wextra -Werror -std=c89 
DEBUGF=-O0 -g
SRCDIR=src
INTFDIR=$(SRCDIR)/interfaces
SANITY=-Wno-unused-variable -Wno-unused-parameter # -Wno-comment

GLIBF=`pkg-config --cflags --libs glib-2.0 gobject-2.0 gio-2.0 gio-unix-2.0`

all: build

build:
	gcc -o bin/out.bin $(DEBUGF) $(GLIBF) $(SANITY) $(SRCDIR)/main.c 

build-interface-binaries:
	gcc -o bin/systemd-hostnamed-handler $(DEBUGF) $(GLIBF) $(SANITY) -D COMPILE_HOSTNAMED_BINARY $(SRCDIR)/main.c
	gcc -o bin/systemd-localed-handler $(DEBUGF) $(GLIBF) $(SANITY) -D COMPILE_LOCALED_BINARY $(SRCDIR)/main.c
	gcc -o bin/systemd-timedated-handler $(DEBUGF) $(GLIBF) $(SANITY) -D COMPILE_TIMEDATED_BINARY $(SRCDIR)/main.c
	gcc -o bin/systemd-logind-handler $(DEBUGF) $(GLIBF) $(SANITY) -D COMPILE_LOGIND_BINARY $(SRCDIR)/main.c

publish:
	gcc -o bin/out.bin $(CFLAGS) $(GLIBF) $(SANITY) $(SRCDIR)/main.c

clean:
	rm bin/*

install: _install_conf _install_interface_binaries

_install_conf:
	cp conf/*-dbus.conf /etc/dbus-1/system.d/
	cp conf/systemd_compat.conf /etc/

_install_interface_binaries:
	cp bin/systemd-hostnamed-handler /usr/local/libexec/
	cp bin/systemd-localed-handler /usr/local/libexec/
	cp bin/systemd-timedated-handler /usr/local/libexec/
	cp bin/systemd-logind-handler /usr/local/libexec/

