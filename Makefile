CC=gcc
BINPATH=bin/
CFLAGS=-c -Wall -std=gnu99
DEVFLAGS= -g -o $(BINPATH)devel/outfile-tmp                   \
-Wextra -Werror -pedantic                                     \
-O0 $(SOURCES)

SOURCES=main.c

.PHONY: all build clean install

all: 
	$(CC) $(CFLAGS) $(DEVFLAGS)

clean:
build:
install:

