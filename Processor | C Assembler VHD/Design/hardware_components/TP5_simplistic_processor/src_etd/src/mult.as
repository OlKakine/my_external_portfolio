li 7, r0
li 8, r1
li 1, r2
xor r3, r3

boucle:
 add r1, r3
 sub r2, r0
 jz patate
 jmp boucle

patate:
 st r3, 0x0001
 