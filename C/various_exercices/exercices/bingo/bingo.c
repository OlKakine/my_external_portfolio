#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include<stdio.h>

/* Alloue et initialise un tableau contenant la suite des entiers
 * naturels strictement positifs de l'intervalle [1; val_max] rangés à
 * des positions aléatoires. */
static uint32_t *generer_tab_aleatoire(uint32_t val_max)
{
    srand(time(NULL));
    
    uint32_t *tab = NULL;
    tab=calloc(val_max,sizeof(uint32_t));
    
    for(int i=1; i<=val_max; i++){
        tab[i]=0;
    }
    for(int i=1; i<=val_max; i++){
        int index=0;
        do {
            index=rand()%val_max;
        }while(tab[index]!=0);
        tab[index]=i;        
    }

    return tab;
}

int main(void)
{
    uint32_t val = 42;
    uint32_t *tab = generer_tab_aleatoire(512);

    /* A compléter */
    for(int i=0; i<512;i++){
        if (tab[i]==val){
            printf("%i",i);
            break;
        }
    }
    /* Consigne: cette ligne doit rester la dernière du programme. */
    free(tab);

    return EXIT_SUCCESS;
}
