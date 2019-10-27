#include <stdio.h>
#include "cep.h"

extern void attente_infinie();

void erreur()
{   
        printf("Contexte de la boucle d'attente alteree par votre traitant.\n");
        attente_infinie();
}

int main(void)
{
	/* Configuration des boutons poussoirs en mode interruption */
        volatile int *pbconfig=(volatile int *)PERIPH_PUSHBTN_CTL;
        *pbconfig=PERIPH_PUSHBTN_INT; 
        attente_infinie();
        return 0;
}
    
