# Makefile for Research Unix V10 Shell (AMD64 Hybrid Port)
# Supports GCC for stability and PCC for historical auditing.

CC      ?= gcc
CFLAGS  += -g -O0 -I./include -D_GNU_SOURCE -m64 -fno-stack-protector -fno-builtin-malloc
LDFLAGS += -g

OFILES = shsetbrk.o blok.o stak.o cmd.o fault.o main.o word.o string.o \
	name.o args.o xec.o service.o error.o io.o print.o macro.o expand.o \
	sctype.o msg.o defs.o pathserv.o func.o spname.o

.PHONY: all clean vintage paranoid

# Default: GCC build
all: v10sh

v10sh: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

# Vintage: PCC build
vintage: clean
	$(MAKE) CC=pcc CFLAGS="-g -O0 -I./include"

# Verification: Run the Super Paranoid suite
paranoid: clean v10sh
	./super_paranoid_v10.sh

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES) v10sh

# Dependencies
blok.o fault.o main.o stak.o: brkincr.h
cmd.o macro.o main.o msg.o name.o word.o xec.o: sym.h
main.o: timeout.h
sctype.o: sctype.h
