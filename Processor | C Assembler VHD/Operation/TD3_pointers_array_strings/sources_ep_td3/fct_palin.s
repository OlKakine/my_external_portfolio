/*
bool palin(const char *ch)
{
    uint32_t inf, sup;
    inf = 0;
    sup = strlen(ch) - 1; 
    while ( (inf < sup) && (ch[inf] == ch[sup])) {
        inf++;
        sup--;
    }
    return inf >= sup;
}
*/
    .text
    .globl palin
    /* bool palin(char *ch) */
/* Contexte :  
    A remplir
*/
palin:
    jr $ra

