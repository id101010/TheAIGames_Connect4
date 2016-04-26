CC=gcc
CFLAGS=-std=c99 -Wall -O2 -static
CLIBS=-lm
PRGNAME=hatred
CFILES=$(shell find . -name '*.c')
HFILES=$(shell find . -name '*.h')
STYLE=astyle --style=1tbs
RUN=valgrind --leak-check=full
DEBUG=gdb --args
ARGS=

all: clean build run clean

clean:
	$(STYLE) $(CFILES)
	$(STYLE) $(HFILES)
	rm -f *.o
	rm -f $(PRGNAME)
build:
	$(CC) $(CFLAGS) $(CLIBS) -o $(PRGNAME) -Isrc $(CFILES)
run:
	./$(PRGNAME) $(ARGS)
memtest:
	$(RUN) ./$(PRGNAME) $(ARGS)
debug:
	$(DEBUG) ./$(PRGNAME)
