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
/* Contexte :
    A remplir
* Fonction feuille pas de modif de pile à faire
* chaine: registre $a0, paramètre de type (const char*)
* taille : registre $v0, paramètre de type (uint32_t)
*/

taille_chaine:
	addu $v0, $zero, $zero

while:
	addu $t0, $a0, $v0
	lbu $t1, 0($t0)
	beq $zero, $t1, end
	addiu $v0, $v0, 1
	j while
	
end:	
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
/*} */
	addu $t0, $zero, $zero 
	addiu $t1, $a1, -1

while_inv:
	blez $t1, fin_inv
	lbu $t0, 0($a0)
	
	addu $t2, $a0, $t1
	lbu $t3, 0($t2)
	sb $t3, 0($a0)
	
	sb $t0, 0($t2)
	
	addiu $t1, $t1, -2

	addiu $a0, $a0, 1
	j while_inv

fin_inv:	 
    jr $ra
