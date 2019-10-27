#!/bin/bash
/opt/mips-toolchain/bin/mips-sde-elf-objdump -d  $1 | cut -f 3 | sed "s/^move$/addu/g;s/^nop$/sll/g;s/^li$/ori/g" | sort |  uniq | grep "^[a-z]*$" | xargs
