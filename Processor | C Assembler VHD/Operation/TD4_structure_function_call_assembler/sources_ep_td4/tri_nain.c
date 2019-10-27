#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#define TAILLE 5000
#define STRT_in(s) #s
#define STRT(s) STRT_in(s)
/* Les tableaux sont en zone data plutôt que sur le tas, car l'espace reservé au
 * tas et à la pile et très limité sur la plateforme CEP (1Ko)  */
int32_t tab[TAILLE];
int32_t ref[TAILLE];

void tri_nain(int32_t[], uint32_t);

void tri_nain_opt(int32_t[], uint32_t);

static void afficher_tab(int32_t tab[], uint32_t taille)
{
        for (uint32_t i = 0; i < taille; i++) {
                printf("%" PRId32 " ", tab[i]);
        }
        printf("\n");
}

static void init_tabs(int32_t tab[],int32_t ref[], uint32_t taille)
{
        for (uint32_t i = 0; i < taille; i++) {
                tab[i] = (rand() % 19) - 9;
        }
        memcpy(ref, tab, sizeof(int32_t) * taille);
}

int comp(const void *a, const void *b)
{
        return (int)(*(int32_t*)a - *(int32_t*)b);
}

int main(void)
{
        printf("Test sur un tableau de petite taille (10)\n");
        uint32_t taille = 10;

        srand(time(NULL));
        init_tabs(tab,ref,taille);

        printf("Tableau initial : ");
        afficher_tab(tab, taille);

        qsort(ref, taille, sizeof(int32_t), comp);
#ifndef OPT         
        tri_nain(tab, taille);
#else
        tri_nain_opt(tab, taille);
#endif
        printf("Tableau trie par le nain : ");
        afficher_tab(tab, taille);

        if (memcmp(ref, tab, sizeof(int32_t) * taille) != 0) {
                printf("Erreur : le nain a mal trie un tableau (sale bete !)\n");
                exit(EXIT_FAILURE);
        }


        printf("Test de performance sur un tableau de grande taille\n");

        /* La taille de la mémoire ne permet pas de tester sur des tableaux
         * suffisamment grands. On réalise donc plusieurs tris pour le test de
         * performance. */
        taille=5000;
        struct timeval tv;
        suseconds_t tmp,tmp2;
        init_tabs(tab,ref,taille);
        gettimeofday(&tv,NULL);
        tmp=tv.tv_usec;
        qsort(ref, taille, sizeof(int32_t), comp);
        gettimeofday(&tv,NULL);
        tmp=tv.tv_usec-tmp;
        gettimeofday(&tv,NULL);
        tmp2=tv.tv_usec;
#ifndef OPT         
        tri_nain(tab, taille);
#else
        tri_nain_opt(tab, taille);
#endif
        gettimeofday(&tv,NULL);
        tmp2=tv.tv_usec-tmp2;
        if (memcmp(ref, tab, sizeof(int32_t) * taille) != 0) {
                printf("Erreur : le nain a mal trie un tableau (sale bete !)\n");
                exit(EXIT_FAILURE);
        }
        printf("Tri de reference : %u usec.\n", (unsigned)tmp);
        printf("Tri par le nain : %u usec.\n", (unsigned)tmp2);

        return EXIT_SUCCESS;
}

