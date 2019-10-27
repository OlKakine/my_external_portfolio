BINS = abr tri_nain tri_nain_opt

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

abr: abr.o fct_abr.o
tri_nain: tri_nain.o fct_tri_nain.o
tri_nain_opt: tri_nain_opt.o fct_tri_nain.o

tri_nain_opt.o: tri_nain.c
	$(CC) $(CFLAGS) -DOPT -c -o $@ $<
