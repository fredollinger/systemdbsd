.PHONY: all

CFLAGS=-Wall -Wextra -Werror -std=c89 -pedantic 
DEBUGF=-O0 -v -g
SRCDIR=src
INTFDIR=$(SRCDIR)/interfaces
SANITY=-Wno-unused-variable -Wno-unused-parameter # -Wno-comment

GLIBF=`pkg-config --cflags --libs glib-2.0 gobject-2.0 gio-2.0 gio-unix-2.0`

all: build

build:
	gcc -o bin/out.bin $(DEBUGF) $(GLIBF) $(SANITY) $(SRCDIR)/main.c 

build-proper:
	gcc -o bin/out.bin $(CFLAGS) $(GLIBF) $(SANITY) $(SRCDIR)/main.c

clean:
	rm bin/*

install: _install_conf

_install_conf:
	cp conf/*-dbus.conf /etc/dbus-1/system.d/
