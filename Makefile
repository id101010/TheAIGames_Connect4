CC=gcc
CFLAGS=-Wall -g -O0
CLIBS=
PRGNAME=hatred
STYLE=astyle --style=1tbs
RUN=valgrind --leak-check=full
DEBUG=gdb --args
ARGS=

all: clean build run clean

clean:
	$(STYLE) $(PRGNAME).c
	rm -f *.o
	rm -f $(PRGNAME)
build:
	$(CC) $(CFLAGS) $(CLIBS) -o $(PRGNAME) $(PRGNAME).c
run:
	$(RUN) ./$(PRGNAME) $(ARGS)
debug:
	$(DEBUG) ./$(PRGNAME)
	
