    .text
/*
uint32_t mult_simple(void)
{
    res = 0;
    while (y != 0) {
        res = res + x;
        y--;
    }
    return res;
}
*/
    .globl mult_simple
mult_simple:

	li $t0, 0
	lw $t2, x
	lw $t1, y
	li $t3, 1

while_mult_simple:
	beq $t1, $zero, fin_mult_simple
	addu $t0, $t0, $t2
	subu $t1, $t1, $t3
	sw $t1, y
	j while_mult_simple
	
fin_mult_simple:
	addu $v0, $t0, $zero
    jr $ra


/*
uint32_t mult_egypt(void)
{
    uint32_t res = 0;
    while (y != 0) {
        if (y % 2 == 1) {
            res = res + x;
        }
        x = x << 1 ;
        y = y >> 1;
    }
    return res;
}
*/
    .globl mult_egypt
mult_egypt:
/* Contexte : ??*/
    jr $ra

/*
uint32_t mult_native(void)
{
    return x*y;
}
*/
    .globl mult_native
mult_native:
    jr $ra


    .data
/* uint32_t res; */
