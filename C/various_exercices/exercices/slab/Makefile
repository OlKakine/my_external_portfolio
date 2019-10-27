CC=clang
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAFS=-lm

all: slab

.PHONY: clean
clean:
	rm -f *~ *.o slab

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename $(shell pwd))
