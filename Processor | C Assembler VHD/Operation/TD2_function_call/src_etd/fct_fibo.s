/*
uint32_t fibo(uint32_t n);
{
    uint32_t fibo_temp;
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
	fibo_temp=fibo(n-1);
        return fibo_temp+fibo(n-2);
    }
}
*/
    .text
    /* uint32_t fibo(uint32_t n) */
    .globl fibo
/* Contexte :
Fonction non feuille => besoin de sauvegarder :
- la place pour les paramètres des fonctions appelées (n) [notation np du cours, np=1] 
- la variable locale fibo_temp [notation nv du cours, nv=1] 
- le registre $ra [notation nr du cours, nr=1]

=> La fonction doit réserver dans la pile (np+nv+nr)*4 octets
=> Pile + 12

Conventions utilisées
    n : registre $a0 ou pile à SP+12 (espace réservé par l'appelant)
    fibo_temp : à l'adresse SP+4 
    adresse de retour : $ra ou pile
    PILE: 
    sp+0 : place pour permettre à la fonction appelée de sauvegarder son paramètre n si besoin (np*4 octets)
    sp+4 : place pour la variable locale fibo_temp (nv*4 octets)
    sp+8 : place de l'adresse de retour ($ra) dans la pile (nr*4 octets)
----------------------------------------------------------
    sp+12: place réservée par la fonction appelante pour sauvegarder n dans la pile.  
*/

fibo:
    /* on reserve la place nécessaire dans la pile */
    addiu $sp,$sp,-12
    /* On y sauvegarde l'adresse de retour */
    sw $ra, 8($sp)
    /* Et le paramètre n */
    sw $a0, 12($sp)
    /* if (n == 0) */
    bne $a0, $zero, elsif
    /* return 0; */
    move $v0, $zero
    j fin
elsif:
    /* else if (n == 1) */
    ori $t0, $zero, 1
    bne $a0, $t0, else
    /* return 1; */
    ori $v0, $zero, 1
    j fin
else:
    /* fibo_temp=fibo(n - 1)
    On place n-1 dans $a0
    */
    addiu $a0, $a0, -1
    jal fibo
    /* stocke la valeur retournée dans fibo_temp */
    sw $v0, 4($sp) 

    /* restauration du parametre n initial ($a0 pu être modifié dans la fonction appelée)*/
    lw $a0, 12($sp)
    /* on appelle maintenant fibo(n - 2) */
    addiu $a0, $a0, -2
    jal fibo
    /* et on calcule la somme finale
    En mettant fibo_temp dans t0 */
    lw $t0, 4($sp) 
    addu $v0, $v0, $t0
fin:
    lw $ra, 8($sp) /*On recharge ra avec l'adresse de retour de la pile*/
    addiu $sp,$sp,12 /*On libère la pile */
    jr $ra
