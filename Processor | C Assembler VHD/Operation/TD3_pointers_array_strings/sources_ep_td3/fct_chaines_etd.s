/*
uint32_t taille_chaine(const char *chaine)
{
    uint32_t taille=0;
    while (chaine[taille] != '\0'){
        taille++;
    }
    return taille;
}
*/
    .text
    .globl taille_chaine
/* uint32_t taille_chaine(const char *chaine) */
/* Contexte : Fonction feuille pas de modif de pile à faire
    * chaine : registre $a0, paramètre de type (const char *)
    * taille : registre $t0, variable locale de type (uint32_t)
    */
taille_chaine:
/*    uint32_t taille=0; */
    addu $t0, $zero, $zero
/*    while (chaine[taille] != '\0'){ */
while_taille:
    addu $t1, $a0, $t0 /*&chaine[taille] dans t1*/
    lbu $t1, ($t1)  /*chaine[taille] dans t1*/
    beq $t1, $zero, fin_while_taille
/*        taille++; */
    addiu $t0, $t0, 1
/*    } */
    j while_taille
fin_while_taille:
/*    return taille; */
    move $v0, $t0
    jr $ra

/*
void inverse_chaine(char *ptr, uint32_t taille)
{
    char tmp;
    int32_t dep = taille - 1;
    while (dep > 0) {
        tmp = *ptr;
        *ptr = ptr[dep];
        ptr[dep] = tmp;
        dep = dep - 2;
        ptr++;
    }
}
*/
    .globl inverse_chaine
/*void inverse_chaine(char *ptr, uint32_t taille) */
/* Contexte fourni :
* Fonction feuille pas de modif de pile à faire
* ptr : registre $a0, paramètre de type (char *)
* taille : registre $a1, paramètre de type (uint32_t)
* tmp : registre $t0, variable locale de type (char)
* dep : registre $t1, variable locale de type (int32_t)
*/
inverse_chaine:
/*    int32_t dep = taille - 1; */
    addiu $t1, $a1, -1
/*    while (dep > 0) { */
while:
    blez $t1, fin_while
/*        tmp = *ptr; */
    lbu $t0, ($a0)
/*        *ptr = ptr[dep]; */
    addu $t2, $a0, $t1 /* &ptr[dep] dans t2 */
    lbu $t2, ($t2) /*ptr[dep] dans t2 */
    sb $t2, ($a0)
/*        ptr[dep] = tmp; */
    addu $t2, $a0, $t1 /* &ptr[dep] dans t2 */
    sb $t0, ($t2)
/*        dep = dep - 2; */
    addiu $t1, $t1, -2
/*        ptr++; */
    addiu $a0, $a0, 1
/*    } */
    j while
fin_while:
/*} */
    jr $ra
