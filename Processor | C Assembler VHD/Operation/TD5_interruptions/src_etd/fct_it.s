.set noat /* Pour être sûr de ne pas utiliser $at */

.text
/*
uint8_t blink;
void mon_traitant(void)
{
    *** Sauvegarde en pile des registres utilisés dans le traitant ***
    *** lecture des boutons poussoirs pour acquitter l'interruption (adresse 0x80050004) ***
    blink=~blink;
    *** ecriture de blink sur les LED (adresse 0x80050000) ***
    *** Restauration des registres sauvegardés ***
    *** Retour de traitant (instruction eret) ***
}
*/
.globl mon_traitant
	
mon_traitant:
/*** Sauvegarde en pile des registres utilisés dans le traitant ***/
    addiu $sp, $sp, -12
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    sw $t2, 8($sp)
/*** lecture des boutons poussoirs pour acquitter l'interruption (adresse 0x80050004) ***/
    lui $t1, 0x8005
    lw $t2, 4($t1) 
/*    blink=~blink; */
    la $t1,blink
    lbu $t0, ($t1)
/***	
    xori $t0, $t0, 0xFF 
	***/
	andi $t2, $t2, 0x0300
	beq $t2, $0, fin /* ne fait rien si ni le bouton 0 ou 1 est appuyé*/

	andi $t2, $t2, 0x0100
	beq $t2, $0, decr	
	
	addiu $t0, $t0, 1 /* on incr si bouton 0 appuyé*/
    sb $t0, 0($t1)
	j ecriture

decr:/*sinon on decr*/
	addiu $t0, $t0, -1
    sb $t0, 0($t1)

ecriture:	
/*** ecriture de blink sur les LED (adresse 0x80050000) ***/
    lui $t1, 0x8005
    sb $t0, ($t1) 
/*** Restauration des registres sauvegardés ***/
fin:	
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    lw $t2, 8($sp)
    addiu $sp, $sp, 12
/*** Retour de traitant (instruction eret) ***/	
    eret    

/*Fonction d'attente fournie permettant de lever certaines erreurs*/

.globl attente_infinie
attente_infinie:
    move $t0, $0
    move $t1, $0
    move $t2, $0
boucle:
    bne $t0, $t2, erreur
    addiu $t0,$t0,1
    bne $t1, $t2, erreur
    addiu $t1,$t1,1
    bne $t0, $t1, erreur
    addiu $t2,$t2,1
    j boucle

.sdata
/* uint8_t blink; */
.lcomm blink,1
