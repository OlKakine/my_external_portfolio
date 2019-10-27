CC=clang
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=
EXEC=test_morse

# Makefile à compléter

all: $(EXEC)

.PHONY: clean enonce
enonce:
	@echo "Complétez d'abord le Makefile pour compiler cet exercice."
	
$(EXEC): morse.c test_morse.c
	$(CC) -o $@ $^ $(CFLAGS)  $(LDFLAGS)

clean:
	rm -f *~ *.o $(EXEC)

.PHONY: progressŝ

progress:
	@../../../.progress/update $(shell basename $(shell pwd))

## Makefile à compléter
#all: $(EXEC)
#
#$(EXEC): $(EXEC).o morse.o
#	$(CC) -o $@ $^ $(LDFLAGS)
#
#morse.o: morse.h
#
#%.o: %.c
#	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
#.PHONY: clean enonce
#enonce:
#	@echo "Complétez d'abord le Makefile pour compiler cet exercice."
#
#clean:
#	rm -f *~ *.o $(EXEC)