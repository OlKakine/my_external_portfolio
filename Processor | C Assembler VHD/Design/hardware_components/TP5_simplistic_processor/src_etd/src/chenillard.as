li 1, r3
li 16, r2

attente:
 ld 0x0010, r0
 and r0,r0
 not r0
 jz attente

 st r3, 0x0001
 shl r3
 
 xor r1, r1
 or r2, r1
 and r3, r1
 jz attente
 jmp add1
 
add1:
 li 1, r1
 add r1, r3
 jmp attente
 