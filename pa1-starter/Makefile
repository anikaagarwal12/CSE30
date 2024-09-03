# CSE30SP24 PA1 makefile
#
# Do not change this

# if you type 'make' without arguments, this is the default
PROG        = pa1
all:        $(PROG)

# header files and the associated object files
HEAD        =  pa1.h
SRC         =  pa1.c 
OBJ         =  ${SRC:%.c=%.o}

# special libraries
LIB         =
LIBFLAGS    = -L ./ $(LIB)

# select the compiler and flags you can over-ride on command line e.g. make DEBUG= 
CC	        = gcc
DEBUG       = -ggdb
CSTD        =
WARN        = -Wall -Wextra -Werror
CDEFS       =
CFLAGS      = -I. $(DEBUG) $(WARN) $(CSTD) $(CDEFS)

$(OBJ):     $(HEAD)

# specify how to compile/assemble the target
$(PROG):    $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

# remove binaries
.PHONY: clean clobber
clean:
	rm -f $(OBJ) $(PROG)
