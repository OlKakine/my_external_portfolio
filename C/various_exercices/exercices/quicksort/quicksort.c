//#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NB_ETUS 7

/* Structure de données représentant un étudiant. */
struct etu {
    /* Nom de l'étudiant. */
    char *nom;
    /* Son score, sur 100. */
    float score;
};

/* Affiche le tableau d'étudiants passé en paramètre. */
static void afficher_etudiants(struct etu diants[NB_ETUS]) {
    for (size_t i = 0; i < NB_ETUS; i++) {
        printf("%s: %2.1f\n", diants[i].nom, diants[i].score);
    }
}

int comp_note (struct etu etu1, struct etu etu2){
    return etu1.score > etu2.score ? 1:0;
}

int comp_alpha(struct etu etu1, struct etu etu2){
    int comp_res = strcmp(etu1.nom, etu2.nom);
    return comp_res > 0 ? 1:0;
}

void swap(int ind1, int ind2, struct etu tab[]){
    struct etu temp = tab[ind1];
    tab[ind1]=tab[ind2];
    tab[ind2]=temp;
}

void qsort( int (*comp)(struct etu, struct etu), int taille, struct etu tab[]){ //need taille to be more than 1 on first call
    struct etu pivot = tab[taille-1];
    int ind_pivot = taille - 1;    
    int taille_inf=0, taille_sup=0;
    
    while((taille_inf + taille_sup) != (taille -1 )){
        int ind_compared=taille-2-taille_sup;
        struct etu compared = tab[ind_compared];
        if(comp(compared, pivot)==1){
            swap(ind_compared,ind_pivot,tab);
            taille_sup++;
            ind_pivot--;
        }
        else {
            swap(ind_compared,taille_inf,tab);
            taille_inf++;
        }
    }
    
    if(taille_inf>1) qsort(comp,taille_inf,tab);
    if(taille_sup>1) qsort(comp,taille_sup,tab+(taille-taille_sup));
}

int main(void)
{
    struct etu diants[NB_ETUS] = {
        { "François", 44.1 },
        { "Jean-Frédéric", 1.5 },
        { "Alain", 28.6 },
        { "Bruno", 2.4},
        { "Nicolas", 20.7 },
        { "Nathalie", 2.6 },
        { "Jean-François", 0.3 }
    };

    /* TODO : On trie les étudiants en fonction de leurs notes en utilisant qsort() */
    printf("Classés par notes croissantes :\n");
    qsort(comp_note,NB_ETUS, diants);
    afficher_etudiants(diants);

    /* TODO : On trie les étudiants par ordre alphabétique en utilisant qsort() */
    printf("\nClassés par ordre alphabétique :\n");
    qsort(comp_alpha,NB_ETUS, diants);
    afficher_etudiants(diants);

    return 0;
}
