#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int longueur_tot_chaines = 0;
    for (int i=1; i<argc; i++){
        longueur_tot_chaines+=strlen(argv[i]);
    }
    
    char * chaines_cat = malloc((longueur_tot_chaines+1) * sizeof(char));
    
    for (int i=1; i<argc; i++){
        strcat(chaines_cat, argv[i]);
    }
    
    printf("%s\n",chaines_cat);
    
    free(chaines_cat);
    
    return EXIT_SUCCESS;
}
