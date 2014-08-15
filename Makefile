.PHONY: all

CC=/usr/bin/cc
CFLAGS=-Wall -Wextra -Werror -std=c89
DEBUGF=-O0 -g

LINKGN=bin/obj/hostnamed-gen.o bin/obj/localed-gen.o bin/obj/timedated-gen.o bin/obj/logind-gen.o
LINKHN=bin/systemd-hostnamed bin/systemd-localed bin/systemd-timedated bin/systemd-logind

GLIBEF=`pkg-config --cflags --libs glib-2.0 gobject-2.0 gio-2.0 gio-unix-2.0 polkit-agent-1`
GLIBOF=`pkg-config --cflags        glib-2.0 gobject-2.0 gio-2.0 gio-unix-2.0 polkit-agent-1`

SANITY=-Wno-unused-variable -Wno-unused-parameter # -Wno-comment

PREFIX=/usr/local
LIBDIR=$(PREFIX)/lib
OUR_LIBDIR=$(LIBDIR)/systemd-compat
SYSCONFDIR=/etc

SRCDIR=src
CONFDIR=conf
POLICYDIR=$(CONFDIR)/sysbus-policy
ISPECTDIR=$(CONFDIR)/introspect-xml
SERVICEFDIR=$(CONFDIR)/service-files

INTFDIR=$(SRCDIR)/interfaces

DBUS_POLICYDIR=$(SYSCONFDIR)/dbus-1/system.d
DBUS_CONFIGDIR=$(PREFIX)/share/dbus-1/system-services

INVOKE_GENFILE_SCRIPT=./scripts/gen-gdbus-interfaces.sh 

all: build

build: _build_interface_objs_debug 
	$(CC) -o bin/out.bin $(DEBUGF) $(GLIBEF) $(SANITY) $(SRCDIR)/main.c

publish: _build_interface_objs 
	$(CC) -o bin/out.bin $(CFLAGS) $(GLIBEF) $(SANITY) $(SRCDIR)/main.c

clean:
	find ./bin -type f -exec rm {} \;
	find $(INTFDIR)/ -type f -iname *-gen.* -exec rm {} \;

install: _install_conf _install_interface_binaries

_build_interface_objs: _build_genfile_objs
	$(CC) -o bin/systemd-hostnamed $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/hostnamed/hostnamed.c bin/obj/hostnamed-gen.o 
	$(CC) -o bin/systemd-localed   $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/localed/localed.c     bin/obj/localed-gen.o
	$(CC) -o bin/systemd-timedated $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/timedated/timedated.c bin/obj/timedated-gen.o
	$(CC) -o bin/systemd-logind    $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/logind/logind.c       bin/obj/logind-gen.o

_build_interface_objs_debug: _build_genfile_objs_debug
	$(CC) -o bin/systemd-hostnamed $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/hostnamed/hostnamed.c bin/obj/hostnamed-gen.o  
	$(CC) -o bin/systemd-localed   $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/localed/localed.c     bin/obj/localed-gen.o
	$(CC) -o bin/systemd-timedated $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/timedated/timedated.c bin/obj/timedated-gen.o
	$(CC) -o bin/systemd-logind    $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/logind/logind.c       bin/obj/logind-gen.o

_build_genfile_objs: _generate_genfiles
	$(CC) -o bin/obj/hostnamed-gen.o $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/hostnamed/hostnamed-gen.c
	$(CC) -o bin/obj/localed-gen.o   $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/localed/localed-gen.c
	$(CC) -o bin/obj/timedated-gen.o $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/timedated/timedated-gen.c
	$(CC) -o bin/obj/logind-gen.o    $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/logind/logind-gen.c

_build_genfile_objs_debug: _generate_genfiles
	$(CC) -o bin/obj/hostnamed-gen.o $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/hostnamed/hostnamed-gen.c
	$(CC) -o bin/obj/localed-gen.o   $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/localed/localed-gen.c
	$(CC) -o bin/obj/timedated-gen.o $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/timedated/timedated-gen.c
	$(CC) -o bin/obj/logind-gen.o    $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/logind/logind-gen.c

_generate_genfiles:
	$(INVOKE_GENFILE_SCRIPT) hostnamed
	$(INVOKE_GENFILE_SCRIPT) localed
	$(INVOKE_GENFILE_SCRIPT) timedated
	$(INVOKE_GENFILE_SCRIPT) logind

_install_conf:
	cp $(POLICYDIR)/*-dbus.conf       $(DBUS_POLICYDIR)/
	cp $(SERVICEFDIR)/*.service       $(DBUS_CONFIGDIR)/
	cp $(CONFDIR)/systemd_compat.conf $(SYSCONFDIR)/

_install_interface_binaries: $(LINKHN)
	mkdir -p $(OUR_LIBDIR)
	cp bin/systemd-* $(OUR_LIBDIR)/ 
