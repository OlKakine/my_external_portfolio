/*
void affichage(struct structure_t s)
{
    affiche(s.entier, s.ptr);
}
*/
    .text
    .globl affichage
/* void affichage(struct structure_t s) */
/* Contexte :
    Fonction non feuille : Besoin de sauvegarder $ra et de garder 2 places pour les arguments de la
fonction appelée
    => PILE + 12
    s : registres $a0 et $a1, paramètre de type (struct structure_t) dont le
champ entier de type (int32_t) est en $a0 et le champ ptr de type (char *) est
dans $a1. Adresse de sauvegarde en pile à SP+12 (champ entier) et SP+16 (champ
ptr)
    adresse de retour : registre $ra ou pile à SP+8 (sauvegarde)
*/
affichage:
    /*Prologue*/
    addiu $sp,$sp, -12
    sw $ra, 8($sp)
    /* affiche(s.entier, s.ptr); */
    /* Il est inutile de sauvegarder s, car on ne l'utilise plus après l'appel de affiche*/
    jal affiche
    /* Epilogue */
    lw $ra, 8($sp)
    addiu $sp,$sp, 12
    jr $ra

/*
void modification(int32_t entier, char *ptr, struct structure_t *s)
{
    s->entier = entier;
    s->ptr = ptr;
}
*/
    .globl modification
/* void modification(int32_t e, char *p, struct structure_t *ps) */
/* Contexte :
    Fonction feuille sans variables locales : pile inchangée
    e : registre $a0, argument de type (int32_t)
    p : registre $a1, argument de type (char *)
    ps  : registre $a2, argument de type (struct structure_t *)
*/
modification:
    /* ps->entier = e; */
    sw $a0, 0($a2)
    /* ps->ptr = p; */
    sw $a1, 4($a2)
    /*}*/
    jr $ra

