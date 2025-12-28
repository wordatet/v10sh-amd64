# POSIX-compliant Makefile for Research Unix V10 Shell
# Compatible with both GNU Make and BSD Make

CC      ?= gcc
CFLAGS  += -g -D_GNU_SOURCE -m64
LDFLAGS += -g

OFILES = shsetbrk.o blok.o stak.o cmd.o fault.o main.o word.o string.o \
	name.o args.o xec.o service.o error.o io.o print.o macro.o expand.o \
	sctype.o msg.o defs.o pathserv.o func.o spname.o

all: v10sh

v10sh: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES) v10sh

.PHONY: all clean

# Dependencies from original mkfile
blok.o fault.o main.o stak.o: brkincr.h
cmd.o macro.o main.o msg.o name.o word.o xec.o: sym.h
main.o: timeout.h
sctype.o: sctype.h
