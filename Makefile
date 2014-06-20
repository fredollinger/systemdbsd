.PHONY: all

CFLAGS=-Wall -Wextra -Werror 
DEBUGF=-O0 -v -g
SRCDIR=src
INTFDIR=$(SRCDIR)/interfaces
SANITY=-Wno-unused-variable -Wno-unused-parameter

GLIBF=`pkg-config --cflags --libs glib-2.0 gobject-2.0 gio-2.0 gio-unix-2.0`

main: 
	gcc -o bin/out.bin $(DEBUGF) $(GLIBF) $(SANITY) $(SRCDIR)/main.c 

main-publish:
	gcc -o bin/out.bin $(CFLAGS) $(GLIBF) $(SANITY) $(SRCDIR)/main.c
