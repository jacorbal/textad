# Copyright (c) 2019, J. A. Corbal
#
# Makefile


## Directories
PWD   = $(CURDIR)
I_DIR = ${PWD}/include
S_DIR = ${PWD}/src
L_DIR = ${PWD}/lib
O_DIR = ${PWD}/obj
B_DIR = ${PWD}/bin


## Compiler & linker opts.
CC           = gcc
CSTANDARD    = gnu11 #c11
OPTIMIZATION = 3 #0:debug; 1:optimize; 2:optimize even more; 3:optimize yet more
CCFLAGS      = -Wpedantic -Werror -Wall -Wextra -I ${I_DIR} -std=${CSTANDARD}
LDFLAGS      = -L ${L_DIR}

# Use `make DEBUG=1` to add debugging information, symbol table, etc.
# When debugging the optimization level will be shut down in order to
# get better results
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CCFLAGS += -DDEBUG -g -ggdb -O0
else
	CCFLAGS += -DNDEBUG -O${OPTIMIZATION}
	LDFLAGS += -s
endif


## Makefile opts.
SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .o


## Files options
TARGET = ${B_DIR}/main
OBJS = $(patsubst ${S_DIR}/%.c, ${O_DIR}/%.o, $(wildcard ${S_DIR}/*.c))
#       $(patsubst ${S_DIR}/items/%.c, ${O_DIR}/items/%.o, $(wildcard ${S_DIR}/items/*.c))
RUN_ARGS =

## Linkage
${TARGET}: ${OBJS}
	${CC} ${LDFLAGS} -o $@ $^

## Compilation
${O_DIR}/%.o: ${S_DIR}/%.c
	${CC} ${CCFLAGS} -c -o $@ $<


## Make options
.PHONY: clean clean-obj clean-all run hard help

all:
	make ${TARGET}

clean-obj:
	rm --force ${OBJS}

clean-bin:
	rm --force ${TARGET}

clean:
	@make clean-obj
	@make clean-bin

clean-all:
	@make clean

debug:
	@make hard DEBUG=1

run:
	${TARGET} ${RUN_ARGS}

hard:
	@make clean
	@make all

hard-run:
	@make clean
	@make all
	@make run

run-hard:
	@make hard-run

help:
	@echo "Type:"
	@echo "  'make all'......................... Build project"
	@echo "  'make run'................ Run binary (if exists)"
	@echo "  'make clean-obj'.............. Clean object files"
	@echo "  'make clean'....... Clean binary and object files"
	@echo "  'make debug'................Compile in DEBUG mode"
	@echo "  'make hard'...................... Clean and build"
	@echo ""
	@echo " Binary will be placed in '${TARGET}'"

