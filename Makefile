.PHONY: all

CFLAGS=-Wall -Wextra -Werror -std=c89 
DEBUGF=-O0 -g
SRCDIR=src
INTFDIR=$(SRCDIR)/interfaces
SANITY=-Wno-unused-variable -Wno-unused-parameter # -Wno-comment
LINKGN=bin/obj/hostnamed-gen.o bin/obj/localed-gen.o bin/obj/timedated-gen.o bin/obj/logind-gen.o
LINKHN=bin/systemd-hostnamed bin/systemd-localed bin/systemd-timedated bin/systemd-logind

GLIBEF=`pkg-config --cflags --libs glib-2.0 gobject-2.0 gio-2.0 gio-unix-2.0`
GLIBOF=`pkg-config --cflags        glib-2.0 gobject-2.0 gio-2.0 gio-unix-2.0`

all: build

build: _build_interface_objs_debug
	gcc -o bin/out.bin $(DEBUGF) $(GLIBEF) $(SANITY) $(SRCDIR)/main.c

publish: _build_interface_objs
	gcc -o bin/out.bin $(CFLAGS) $(GLIBEF) $(SANITY) $(SRCDIR)/main.c

clean:
	rm bin/*

install: _install_conf _install_interface_binaries

_build_interface_objs: _build_genfile_objs
	gcc -o bin/systemd-hostnamed $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/hostnamed/hostnamed.c bin/obj/hostnamed-gen.o 
	gcc -o bin/systemd-localed   $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/localed/localed.c     bin/obj/localed-gen.o
	gcc -o bin/systemd-timedated $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/timedated/timedated.c bin/obj/timedated-gen.o
	gcc -o bin/systemd-logind    $(CFLAGS) $(GLIBEF) $(SANITY) $(INTFDIR)/logind/logind.c       bin/obj/logind-gen.o

_build_interface_objs_debug: _build_genfile_objs_debug
	gcc -o bin/systemd-hostnamed $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/hostnamed/hostnamed.c bin/obj/hostnamed-gen.o  
	gcc -o bin/systemd-localed   $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/localed/localed.c     bin/obj/localed-gen.o
	gcc -o bin/systemd-timedated $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/timedated/timedated.c bin/obj/timedated-gen.o
	gcc -o bin/systemd-logind    $(DEBUGF) $(GLIBEF) $(SANITY) $(INTFDIR)/logind/logind.c       bin/obj/logind-gen.o

_build_genfile_objs:
	gcc -o bin/obj/hostnamed-gen.o $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/hostnamed/hostnamed-gen.c
	gcc -o bin/obj/localed-gen.o   $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/localed/localed-gen.c
	gcc -o bin/obj/timedated-gen.o $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/timedated/timedated-gen.c
	gcc -o bin/obj/logind-gen.o    $(CFLAGS) $(GLIBOF) $(SANITY) -c $(INTFDIR)/logind/logind-gen.c

_build_genfile_objs_debug:
	gcc -o bin/obj/hostnamed-gen.o $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/hostnamed/hostnamed-gen.c
	gcc -o bin/obj/localed-gen.o   $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/localed/localed-gen.c
	gcc -o bin/obj/timedated-gen.o $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/timedated/timedated-gen.c
	gcc -o bin/obj/logind-gen.o    $(DEBUGF) $(GLIBOF) $(SANITY) -c $(INTFDIR)/logind/logind-gen.c

_install_conf:
	cp conf/*-dbus.conf         /etc/dbus-1/system.d/
	cp conf/systemd_compat.conf /etc/

_install_interface_binaries: $(LINKHN)
	cp bin/systemd-hostnamed /usr/local/libexec/
	cp bin/systemd-localed   /usr/local/libexec/
	cp bin/systemd-timedated /usr/local/libexec/
	cp bin/systemd-logind    /usr/local/libexec/

