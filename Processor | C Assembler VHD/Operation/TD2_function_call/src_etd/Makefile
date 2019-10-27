BINS = pgcd mult fibo fact val_bin age droite
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

pgcd: pgcd.o fct_pgcd.o

fact: fact.o fct_fact.o

age: age.o fct_age.o

hello: hello.o fct_hello.o

affine: affine.o fct_affine.o

fibo: fibo.o fct_fibo.o

val_bin: val_bin.o fct_val_bin.o

mult: mult.o fct_mult.o

droite: droite.o
