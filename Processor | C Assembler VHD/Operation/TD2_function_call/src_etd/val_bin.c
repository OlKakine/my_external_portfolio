#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

uint8_t val_binaire(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

uint8_t chiffre(char c)
{
    if (c == '0') {
        return 0;
    } else if (c == '1') {
        return 1;
    } else {
        fprintf(stderr, "Erreur : %c n'est pas un chiffre en binaire\n", c);
        exit(2);
    }
}

int main(void)
{
    char titi[9]= "01011011";
    uint8_t toto[8]= {0,1,0,1,1,0,1,1};
    uint8_t val = val_binaire(
   toto[0],toto[1],toto[2],toto[3],toto[4],toto[5],toto[6],toto[7]); 
    printf("Valeur du nombre binaire %s = %" PRIu8 "\n", titi, val);
    return 0;
}

