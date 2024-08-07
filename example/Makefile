CC=cc
CFLAGS=-g -Wall -Werror -Wextra -O2 -pedantic -std=c99
LFLAGS=-Llib -Iinclude -lirclib

all: main

main:
	$(CC) $(CFLAGS) ./src/main.c -o ./tmp/main $(LFLAGS)

clean:
	@echo "Cleaning..."
	@rm -rf ./tmp/*
	@echo "All clean now."

.PHONY: all clean
