#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static void print_byte(uint8_t byte)
{
    char bits[9];
    bits[8]='\0';
    for(int i=0; i<8; i++){
        bits[7-i] = '0' + (0x1 & byte);
        byte = byte >> 1;
    };
    printf("%s ",bits);
}

static void print_memory(void *base, size_t size)
{
    uint8_t *norm_base = (uint8_t*) base;
    for(size_t i=0; i<size; i++){
        print_byte(*norm_base);
        norm_base++;
    }
    puts("");
}


int main(void)
{
    uint8_t un = 1;
    print_memory(&un, sizeof(uint8_t));

    uint8_t tab[4] = { 255, 0, 255, 0 };
    print_memory(tab, 4 * sizeof(uint8_t));

    uint32_t foo = 123456;
    printf("%u = ", foo);
    print_memory(&foo, sizeof(uint32_t));
    printf("\n");

    return EXIT_SUCCESS;
}
