#
# Makefile for connect four bot.
#
# aaron@duckpond.ch
#

# Tools
CC=gcc
COMPRESS=tar -czf
CFLAGS=-std=c99 -Wall -O2 -static
CLIBS=-lm
PRGNAME=connect4bot

# Files
CFILES=$(shell find . -name '*.c')
HFILES=$(shell find . -name '*.h')

# Debug
STYLE=astyle --style=1tbs
RUN=valgrind --leak-check=full
DEBUG=gdb --args
ARGS=

all: build run

clean:
	$(STYLE) $(CFILES)
	$(STYLE) $(HFILES)
	rm -f *.o
	rm -f $(PRGNAME)
	rm -f $(PRGNAME).tar.gz

build:
	$(CC) $(CFLAGS) $(CLIBS) -o $(PRGNAME) -Isrc $(CFILES)

run:
	./$(PRGNAME) $(ARGS)

memtest:
	$(RUN) ./$(PRGNAME) $(ARGS)

debug:
	$(DEBUG) ./$(PRGNAME)

tar:
	$(COMPRESS) $(PRGNAME).tar.gz *.c *.h
