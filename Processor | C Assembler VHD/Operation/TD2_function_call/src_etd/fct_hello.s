/*
void hello(void)
{
	affiche_HelloWorld();
}
*/

    .text
    .globl hello
    /* void hello(void) */

/* Contexte :
	Fonction non feuille.
	Pas de paramètre, Pas de variable locale.
	$ra doit être sauvegardé dans la pile pour ne pas être écrasé lors de l appel de fonction
	$ra à l entree dans la fonction : pile à SP+0  
*/

hello:
    jr $ra
