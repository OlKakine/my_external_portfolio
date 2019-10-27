#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint16_t age(uint16_t);

int main(void)
{
    printf("usage: annee_naissance\n");
    uint16_t annee = 1996;
    printf("Vous avez donc %" PRIu16 " ans !\n", age(annee));
    return 0;
}

