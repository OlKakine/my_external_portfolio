#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define TAMPSIZE 100    // Taille maximale de la chaine tampon de
			// saisie sécurisée : 100 caractères
#define REFLUX true    // true si on veut rediriger les flux stdin,
			// stdout et stderr vers des fichiers, false
			// sinon

int main(void)
{
    char nom[20];    // Variable de stockage du nom saisi
    uint16_t age;   // Variable de stockage de l'age saisi

    if (REFLUX){
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);  
        freopen("err.txt","w",stderr);
    }
    
    fputs("Bienvenue chez les flux\n \
Saississez des couples nom age (ex : doe 35)\n \
sur une même ligne en validant par un retour chariot\n \
Tapez Q pour quitter le programme\n",stdout);
    
    char ligne[TAMPSIZE];
    
    while (fgets(ligne,TAMPSIZE-1,stdin) != NULL){
        
        switch (sscanf(ligne,"%s %hi",nom, &age)){
            case 1: 
                if (nom[0] == 'Q' && nom[1] == '\0'){
                    return EXIT_SUCCESS;
                } else {
                    fprintf(stderr,"Erreur de saisie, nom et/ou age manquant dans la chaine :%s", ligne);
                    fputs("####\n",stdout);
                }
                break;
                
            case 2:
                fprintf(stdout,"nom = %s - age = %d ans\n",nom,age);
                break;
                
            default:
                fprintf(stderr,"Erreur de saisie, nom et/ou age manquant dans la chaine :%s", ligne);
                fputs("####\n",stdout);
        }
    }

    return EXIT_SUCCESS;
}
