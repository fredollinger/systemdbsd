.PHONY: all

CFLAGS=-Wall -Wextra -Werror -pedantic 
DEBUGF=-O0 -v -g
SRCDIR=src
MODDIR=$(SRCDIR)/modules

GLIBF=`pkg-config --cflags --libs glib-2.0 gobject-2.0`

hostnamed: 
	gcc -o bin/out.bin $(CFLAGS) $(DEBUGF) $(GLIBF) $(SRCDIR)/main.c 
