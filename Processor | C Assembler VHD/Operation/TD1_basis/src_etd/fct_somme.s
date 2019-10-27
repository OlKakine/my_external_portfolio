/*


uint8_t somme8(void)
{
    uint8_t i;
    res8 = 0;
    for (i = 1; i <= 24; i++) {
        res8 = res8 + i;
    }
    return res8;
}
*/
    .text
    .globl somme

/*
uint8_t res8;
uint32_t res;

uint32_t somme(void)
{
    uint32_t i;
    uint32_t res = 0;
    for (i = 1; i <= 10; i++) {
        res = res + i;
    }
    return res;
}
*/	
somme:
/*  Contexte :
i:	 $t0
res:	$t1
retour:	 $v0
	à préciser */
	addiu $t1, $zero, 0
	addiu $t0 ,$zero ,1
	addiu $t2, $zero, 11

for:	
	beq $t0, $t2, fin
	addu $t1, $t1, $t0
	addiu $t0, $t0, 1

	j for 

fin:
	addu $v0, $t1, $zero
	jr $ra

/*
	uint32_t sommeMem(void)
{
    uint32_t i;
    for (i = 1; i <= 10; i++) {
        res = res + i;
    }
    return res;
}*/

    .globl sommeMem
sommeMem:
	/*  Contexte :
i:	$t0
	à préciser */

	addiu $t0, $zero, 1
	addiu $t2, $zero, 11

forMem:
	lw $t1, res
	beq $t0, $t2, finMem
	addu $t1, $t1, $t0
	addiu $t0, $t0, 1
	sw $t1, res

	j forMem

finMem:
	addu $v0, $t1, $zero
	jr $ra	


    .globl somme8
somme8:
/*  Contexte : à préciser */

    .data
/* uint32_t res;
 la variable globale res étant définie dans ce fichier, il est nécessaire de
 la définir dans la section .data du programme assembleur : par exemple, avec 
 la directive .comm vu qu'elle n'est pas initialisée (idem pour res8)
*/
	.comm res,1
