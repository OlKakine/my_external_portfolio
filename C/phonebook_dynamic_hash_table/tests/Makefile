CC = clang
CFLAGS = -Wall -Wextra -g -O2 -I../include
# truc cracra pour récupérer le chemin absolu vers le répertoire lib/
LIBDIR = $(shell dirname $(shell find $(shell pwd) | head -n 1))/lib/
LDFLAGS = -Wl,-rpath=$(LIBDIR) -L$(LIBDIR) -ldirectory

TESTS =			contact-01 \
				contact-02 \
				contact-03 \
				contact-04 \
				contact-05 \
				contact-06 \
				directory-01 \
				directory-02 \
				directory-03 \
				directory-04 \
				directory-05 \
				directory-06 \
				directory-07

all: $(TESTS)

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
