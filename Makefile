CC=gcc
CFLAGS=-Wall -g -O0
CLIBS=
PRGNAME=yougotfkniced
RUN=valgrind --leak-check=full
DEBUG=gdb --args
ARGS=

all: clean build run clean

clean:
	rm -f *.o

build:
	$(CC) $(CFLAGS) $(CLIBS) -o $(PRGNAME) $(PRGNAME).c

run:
	$(RUN) ./$(PRGNAME) $(ARGS)

debug:
	$(DEBUG) ./$(PRGNAME)
	
