/*
// Description en C de la fonction à traduire en langage d'assemblage
uint32_t pgcd_as(void)
{
    uint32_t i=a;
    uint32_t j=b;
    while (i != j) {
        if (i < j) {
            j = j - i;
        } else {
            i = i - j;
        }
    }
    return i;
}
*/
/*
  CONTEXTE :
  i : $t0
  j : $t1
  retour : $v0
*/
    .text
    .globl pgcd_as
pgcd_as:
/* Contexte: on propose de mettre les variables i et j, respectivement dans les
 * registres t0 (soit $8) et t1 (soit $9) */
    /* uint32_t i=a; */
    lw $t0, a
    /* uint32_t j=b; */
    lw $t1, b
    /* while (i != j) {  */
while:
    beq $t0, $t1, fin /*Saut à fin si i==j*/
    /* if (i < j) {  */
    sltu $t2, $t0, $t1 /*Le registre t2 est utilisé pour stocker le résultat du
test i<j*/
    beq $t2, $zero, else /*$zero est l'alias de $0 */
    /* j = j - i;  */
    subu $t1, $t1, $t0
    j fin_if
    /* } else {  */
else:
    /* i = i - j;  */
    subu $t0, $t0, $t1
    /*  }  */
fin_if:
    /*  }  */
    j while
    /* return i; */
fin:
    /* Par convention, le registre v0 (soit $2) contient la valeur de retour.*/
    addu $v0, $t0, $zero
    /* Par convention encore, l'adresse de retour dans la fonction appelante est
     * stockée dans le registre ra (soit $31) */
    jr $ra
