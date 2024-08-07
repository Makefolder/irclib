CFLAGS=-g -Wall -Werror -Wextra -O0 -pedantic -std=c99
CC=cc
AR=ar
RANLIB=ranlib
LIBNAME=libirclib.a

all: lib

lib: ./lib/$(LIBNAME)

./lib/$(LIBNAME):
	$(CC) -c $(CFLAGS) ./src/irc.c -o ./obj/irc.o
	$(AR) rcs ./lib/$(LIBNAME) ./obj/irc.o
	cp ./src/irc.h ./include/irclib/

clean:
	@echo "Cleaning..."
	@rm -rf ./obj/*
	@rm -rf ./lib/*
	@rm -rf ./include/irclib/*
	@echo "All clean now."

.PHONY: all clean
