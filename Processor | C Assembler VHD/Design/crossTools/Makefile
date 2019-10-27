# Pour utiliser ce Makefile, les variables suivantes doivent etre positionnées
# PATH : doit contenir le chemin du cross-compilateur
# MIPSC  : prefix des binutils ou du cross-compilateur par defaut MIPSC=mips-sde-elf-

# A l'appel du makefile : make <cible> IRQ_FLAG=irq/no_irq
# IRQ_FLAG=irq  ou no_irq pour valider/invalider l'utilisation d'IRQs
PATH+=:/opt/mips-toolchain/bin:
export PATH

ifndef MIPSC
 MIPSC=/opt/mips-toolchain/bin/mips-sde-elf-
endif
ifndef IRQ_FLAG
IRQ_FLAG=no_irq
endif
# placer le binaire obtenu dans le répertoire program du projet MMIPS.

CC=$(MIPSC)gcc
LD=$(MIPSC)ld
AS=$(MIPSC)as
DP=$(MIPSC)objdump

mips_invader_zybo.elf: IRQ_FLAG=no_irq

test_irq.elf: IRQ_FLAG=irq

MIPS_FLAG=mmips_$(IRQ_FLAG)
MSTART=$(MIPS_FLAG).o
LINK_SCR= mmips_link_$(IRQ_FLAG).scr

ASFLAGS=-mips32 -EB	 -mabi=32 -non_shared
CFLAGS=-mips32 -Xassembler -EB -Xassembler -mabi=32 -Xassembler -W -G0  -fno-delayed-branch
LDFLAGS=-G0 -mips3 --static -T  $(LINK_SCR)

.PRECIOUS : %.o %.dump

%.o : %.s
	$(AS)  $(ASFLAGS) -G0 -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c  -o $@ $<

%.elf :  %.o  $(LINK_SCR) $(MSTART)
	$(LD)  $(LDFLAGS)  -o $@ $(MSTART) $<
	cp $@ ../program
	echo "Les instructions nécessaires pour exécuter ce programme sont:"
	./instructions_necessaires.sh $@

%.dump  : %
	$(DP)  -S --section=.ini --section=__start --section=.text --section=.sdata --section=.data --section=.bss --section=.irq_vec -M no-aliases -d $< > $@

%.dump  : %.o
	$(DP)  -S --section=.ini --section=__start --section=.text --section=.sdata --section=.data --section=.bss --section=.irq_vec -M no-aliases -d $< > $@

clean:
	rm *.o *.dump *.elf
