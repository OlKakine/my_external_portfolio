#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

// nombre d'elements dans l'arbre
#define NBR_ELEM 9

// le type d'un noeud de l'arbre
struct noeud_t {
    uint32_t val;       // valeur du noeud
    struct noeud_t *fg; // fils gauche
    struct noeud_t *fd; // fils droite
};

// fonctions implantees dans le fichier assembleur
// renvoie vrai ssi la valeur est presente dans l'argent
bool est_present(uint32_t, struct noeud_t *);
// copie les valeurs des noeuds de l'arbre dans un tableau
void abr_vers_tab(struct noeud_t *);

// cree un noeud en allouant l'espace memoire et en
//   initialisant les champs de la structure
struct noeud_t *cree_noeud(uint32_t val, struct noeud_t *fg, struct noeud_t *fd)
{
    struct noeud_t *res = malloc(sizeof(struct noeud_t));
    res->val = val; res->fg = fg; res->fd = fd;
    return res;
}

// cree l'ABR donne dans l'enonce
struct noeud_t *abr_enonce(void)
{
    return cree_noeud(8,
            cree_noeud(3,
                cree_noeud(1, NULL, NULL),
                cree_noeud(6,
                    cree_noeud(4, NULL, NULL),
                    cree_noeud(7, NULL, NULL))),
            cree_noeud(10, NULL,
                cree_noeud(14,
                    cree_noeud(13, NULL, NULL),
                    NULL)));
}

// teste la presence de valeurs dans l'arbre
void test_presence(struct noeud_t *abr)
{
    for (uint32_t i = 0; i < 15; i++) {
        printf("est_present(%" PRIu32 ", abr) ? : %s\n",
                i, est_present(i, abr) ? "oui" : "non");
    }
    puts("");
}

// une fonction d'affichage du tableau
void affiche_tab(uint32_t tab[])
{
    printf("Contenu du tableau : ");
    for (uint8_t i = 0; i < NBR_ELEM; i++) {
        printf("%" PRIu32 " ", tab[i]);
    }
    puts("");
}

// le mot cle "extern" veut dire que cette variable
//   globale est visible dans le fichier .c, mais
//   qu'elle est allouee "ailleurs"
// vous devez l'allouer dans la zone .data du
//   fichier assembleur
extern uint32_t *ptr;

#if 0
void abr_vers_tab(struct noeud_t *abr)
{
    if (abr != NULL) {
        abr_vers_tab(abr->fg);
        *ptr = abr->val;
        ptr++;
        struct noeud_t *fd = abr->fd;
        free(abr);
        abr_vers_tab(fd);
    }
}
#endif

#if 0
bool est_present(uint32_t val, struct noeud_t *abr)
{
   if (abr == NULL) {
       return false;
   } else if (val == abr->val) {
       return true;
   } else if (val < abr->val) {
       return est_present(val, abr->fg);
   } else {
       return est_present(val, abr->fd);
   }
}
#endif

int main(void)
{
    // deux arbres, un vide et un plein
    struct noeud_t *abr_vide, *abr_ex;

    // cree un arbre vide
    abr_vide = NULL;
    // teste la presence de valeurs dans cet arbre
    test_presence(abr_vide);

    //  cree l'arbre de l'enonce
    abr_ex = abr_enonce();
    // teste la presence de valeur dans cet arbre
    test_presence(abr_ex);

    // cree un tableau
    uint32_t tab[NBR_ELEM];
    // initialise le ptr sur la premiere case du tableau
    ptr = tab;
    // copie les elements de l'arbre dans le tableau
    abr_vers_tab(abr_ex);
    // affiche le tableau
    affiche_tab(tab);

    return 0;
}

