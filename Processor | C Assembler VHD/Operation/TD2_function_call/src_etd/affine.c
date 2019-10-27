#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// Déclaration de la fonction affine définie dans fct_affine.s
extern uint32_t affine(uint32_t a, uint32_t x,uint32_t b);

int main()
{   
  uint32_t res_as = affine(2,3,4);
  printf("affine(2,3,4) calculé en assembleur: %"
                       PRIu32 "\n", res_as);
  return 0;
}

