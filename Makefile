SHELL := /bin/bash
CC := gcc
CFLAGS := -std=c11 -Wall -pedantic
LIBS :=

ifeq ($(DEBUG),true)
	CFLAGS +=-g
else
	CFLAGS +=-Werror
endif

CTESTFLAGS :=-g -I./

%.test.o: %.test.c
	$(CC) $(CFLAGS) $(CTESTFLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.test: %.test.o ./test/test.o
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean test

test: $(T)
	./$(T)

clean:
	rm -rf ./test/*.{o,dSYM} ./src/*.{o,test,dSYM}

