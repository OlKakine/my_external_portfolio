/*
void inverse(struct cellule_t **l)
{  
   struct cellule_t *res, *suiv;
   res = NULL;
   while (*l != NULL) {
       suiv = (*l)->suiv;
       (*l)->suiv = res;
       res = *l; 
       *l = suiv;
   }   
   *l = res;
}
*/
    .text
    .globl inverse

/* void inverse(struct cellule_t **l) */
/* Contexte : 
A définir
*/
inverse:
    jr $ra

/*
struct cellule_t *decoupe(struct cellule_t *l, struct cellule_t **l1, struct cellule_t **l2)
{
    struct cellule_t fictif1, fictif2;
    *l1 = &fictif1;
    *l2 = &fictif2;
    while (l != NULL) {
        if (l->val % 2 == 1) {
            (*l1)->suiv = l;
            *l1 = l;
        } else {
            (*l2)->suiv = l;
            *l2 = l;
        }
        l = l->suiv;
    }
    (*l1)->suiv = NULL;
    (*l2)->suiv = NULL;
    *l1 = fictif1.suiv;
    *l2 = fictif2.suiv;
    return l;
}
*/
    .globl decoupe
/* Contexte : 
Fonction feuille : A priori pile inchangée, mais besoin de l'adresse des
variables locales => implantation des variables locales en pile.
Besoin de 2*2 mots de 32 bits dans la pile (PILE+16)

l  : registre $a0, paramètre de type (struct cellule_t *)
l1 : registre $a1, paramètre de type (struct cellule_t **)
l2 : registre $a2, paramètre de type (struct cellule_t **)
fictif1 : PILE à SP, variable locale de type struct cellule_t,
    champ val de type int32_t à SP,
    champ suiv de type (struct cellule_t *) à SP+4
fictif2 : PILE à SP, variable locale de type struct cellule_t,
    champ val de type int32_t à SP+8,
    champ suiv de type (struct cellule_t *) à SP+12
*/
decoupe:
    jr $ra

