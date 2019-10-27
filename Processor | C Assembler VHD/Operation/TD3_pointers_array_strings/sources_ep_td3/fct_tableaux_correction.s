    .text
    .globl tri_min
/* void tri_min(int32_t tab[], uint32_t taille) */
/* Contexte : 
    Pas d'appel de sous-fonction, ni plus de 4 arguments,
    ni plus de 10 variables temporaires
    =>  Rien en pile
  
    * tab : registre $a0, parametre de type (int32_t [])
    * taille : registre $a1, parametre de type (uint32_t)
    * i : registre $t0, variable locale de type (uint32_t)
    * j : registre $t1, variable locale de type (uint32_t)
    * ix_min : registre $t2, variable locale de type (uint32_t)
    * tmp : registre $t3, variable locale de type (int32_t)
*/

tri_min:
/*     for (i = 0;     */
    xor $t0, $t0, $t0
for1_opt:
/*     ; i < taille - 1; */
    addiu $t4, $a1, -1      /*taille-1 dans t4*/
    sltu $t5, $t0, $t4
    beq $t5, $zero,fin_for1_opt 
    
/*         for (ix_min = i, j = i + 1;  */
    addu $t2, $t0, $zero
    addiu $t1, $t0, 1
for2_opt:
/*         ; j < taille;  */
    sltu $t5, $t1, $a1
    beq $t5, $zero, fin_for2_opt
    
/*             if (tab[j] < tab[ix_min]) { */
    sll $t5, $t1, 2 /* (indice * 4) dans t5: entier = 4! */
    addu $t5, $t5, $a0 /* adresse de tab[j] dans t5 */
    lw $t5, ($t5) /* tab[j] dans t5 */
    sll $t6, $t2, 2
    addu $t6, $t6, $a0 /*&tab[ix_min] dans t6 */
    lw $t7, ($t6) /*tab[ix_min] dans t7 */
    slt $t8, $t5, $t7
    beq $t8, $zero, fin_if_opt
    
/*                 ix_min = j; */
    addu $t2, $t1, $zero
 fin_if_opt:
/*        ; j++) {*/
    addiu $t1, $t1, 1
    j for2_opt
 fin_for2_opt:
/*         tmp = tab[i]; */
    sll $t8, $t0, 2
    addu $t8, $t8, $a0 /*&tab[i] dans t8*/
    lw $t3, ($t8) 
    
/*         tab[i] = tab[ix_min]; */
    sll $t6, $t2, 2
    addu $t6, $t6, $a0 /*&tab[ix_min] dans t6 */
    lw $t7, ($t6) /*tab[ix_min] dans t7 */
    sll $t8, $t0, 2
    addu $t8, $t8, $a0 /*&tab[i] dans t8*/
    sw $t7, ($t8) 
    
/*         tab[ix_min] = tmp; */
    sll $t6, $t2, 2
    addu $t6, $t6, $a0 /*&tab[ix_min] dans t6 */
    sw $t3, ($t6)
    
/*     }
    for ( ... ; i++) { */
    addiu $t0, $t0, 1
    j for1_opt
fin_for1_opt:
/* } */
    jr $ra

