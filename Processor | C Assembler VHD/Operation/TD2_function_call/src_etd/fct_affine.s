/*
uint32_t affine(uint32_t a,uint32_t b,uint32_t x)
{
   return mult(x,a)+b;
}
*/

    .text
    .globl affine
    /* uint32_t affine(uint32_t a,uint32_t b,uint32_t x) */

/* Contexte: 
	A compléter
*/

affine:
/* A compléter */
    jr $ra


/* uint32_t mult(uint32_t x,uint32_t y) { return x*y;} */
	/* Contexte :
	Convention
	x : $a0
	y : $a1
	valeur temporaire res  :$t0
	retour dans $v0 */
mult:
    /* res = 0 */
    or $t0,$zero,$zero
    /* while (y != 0) */
while:
    beq $a1, $zero, fin_while
    /* res = res + x */
    addu $t0, $a0, $t0
    /* y-- */
    addiu $a1,$a1, -1
    /* } */
    j while
fin_while:
    /* return res; */
    or $v0,$t0,$zero
    jr $ra
