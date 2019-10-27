#include <string.h>
#include <stdint.h>
#include "salarie.h"

struct salarie{
    char prenom[16];
    char nom[32];
    uint8_t age;
    uint8_t anciennete;
    uint32_t salaire;
};

struct salarie *allouer_salarie(void){
    return (struct salarie *) malloc(sizeof(struct salarie));
};

void init_salarie(struct salarie *s,
                         const char *prenom,
                         const char *nom,
                         uint8_t age,
                         uint8_t anciennete,
                         uint32_t salaire){
    strncpy(s->prenom,prenom,16);
    strncpy(s->nom,nom,32);
    s->age = age;
    s->anciennete = anciennete;
    s->salaire = salaire;
};

void creer_salarie(struct salarie **s,
                          const char *prenom,
                          const char *nom,
                          uint8_t age,
                          uint8_t anciennete,
                          uint32_t salaire){
    *s = allouer_salarie();
    init_salarie(*s, prenom, nom, age, anciennete, salaire);
};

/*
    Libère la mémoire associée au salarié passé en paramètre.
    En sortie, s doit valoir NULL.
*/
void plan_social(struct salarie **s){
    free(*s);
    *s = NULL;
};