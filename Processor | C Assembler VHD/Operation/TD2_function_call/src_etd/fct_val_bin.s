/*
uint8_t val_binaire(uint8_t b7, uint8_t b6, uint8_t b5, uint8_t b4,
  uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
    return (b7 << 7) | (b6 << 6) | (b5 << 5) | (b4 << 4) |
      (b3 << 3) | (b2 << 2) | (b1 << 1) | b0;
}
*/

    .text
    .globl val_binaire
/* uint8_t val_binaire(uint8_t b7, uint8_t b6, uint8_t b5, uint8_t b4,
     uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0); */
val_binaire:
/*
Contexte ??
*/
    jr $ra

