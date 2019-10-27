BINS = chaines tableaux struct liste palin 

AS = mips-elf-gcc
ASFLAGS = -g -c
CC = mips-elf-gcc
CFLAGS = -Wall -Wextra -g -std=c99 
LD = mips-elf-gcc
LDFLAGS = -T cep.ld


.PHONY: all

all: $(BINS)

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

OBJS = $(foreach f, $(BINS), $(addsuffix .o, $f)) \
	$(foreach f, $(BINS), $(addprefix fct_, $(addsuffix .o, $f)))

.PHONY: clean
clean:
	$(RM) $(BINS) $(OBJS)

liste: liste.o fct_liste.o

palin: palin.o fct_palin.o

chaines: chaines.o fct_chaines.o

struct: struct.o fct_struct.o

tableaux: tableaux.o fct_tableaux.o
