CC=cc
AR=ar
RANLIB=ranlib

DEBUG=-fsanitize=address
CFLAGS=-g -Wall -Werror -Wextra -O0 -pedantic -std=c99
LDFLAGS=-Llib -Iinclude -lirclib

LIBNAME=libirclib.a

all: exec test

exec: ./lib/$(LIBNAME)
	$(CC) $(CFLAGS) ./src/main.c -o ./tmp/bin/main.out $(LDFLAGS)

test: ./lib/$(LIBNAME)
	$(CC) $(CFLAGS) $(DEBUG) ./src/main.c -o ./tmp/test/main.out $(LDFLAGS)

lib: ./lib/$(LIBNAME)

./lib/$(LIBNAME):
	$(CC) -c $(CFLAGS) ./src/irc.c -o ./obj/irc.o
	$(AR) rcs ./lib/$(LIBNAME) ./obj/irc.o
	cp ./src/irc.h ./include/irclib/

clean:
	@echo "Cleaning..."
	@rm -rf ./tmp/bin/*
	@rm -rf ./tmp/test/*
	@rm -rf ./obj/*
	@rm -rf ./lib/*
	@rm -rf ./include/irclib/*
	@echo "All clean now."

.PHONY: all clean
