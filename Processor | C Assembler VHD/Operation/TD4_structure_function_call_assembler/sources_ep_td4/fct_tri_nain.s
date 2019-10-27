/*
void tri_nain(int32_t tab[], uint32_t taille)
{
    uint32_t i = 0;
    while(i < taille - 1) {
        if (tab[i] > tab[i+1]) {
            int32_t tmp = tab[i];
            tab[i] = tab[i+1];
            tab[i + 1] = tmp;
            if (i > 0) {
                i = i - 1;
            }
        } else {
            i = i + 1;
        }
    }
}
*/
    .text
/*  void tri_nain(int32_t tab[], uint32_t taille) */
    .globl tri_nain
tri_nain:
/* Contexte : à définir */
    jr $ra
    

    .text
    .globl tri_nain_opt
/* Version du tri optimisée sans respecter la contrainte de la traduction
 * systématique*/
tri_nain_opt:
/* Contexte : 
complétez le contexte précédent en indiquant les registres qui contiendront des
variables temporaires.  */
    jr $ra

