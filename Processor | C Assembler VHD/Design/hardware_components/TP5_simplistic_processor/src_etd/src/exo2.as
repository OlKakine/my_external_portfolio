xor r0,r0
xor r1,r1
not r1
xor r2,r2
xor r3,r3

attente:
 ld 0x0010, r0
 and r0,r0 #MAJ du flags z
 jz fonction 
 jmp attente 

fonction:
 and r3,r3
 jz set1
 jmp set0

set1:
 st r1,0x0001
 not r3
 jmp attente

set0:
 st r2,0x0001
 not r3
 jmp attente