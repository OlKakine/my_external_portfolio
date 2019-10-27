#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdbool.h>

extern void traitant_IT_32();
extern void init_traitant_IT(int32_t num_IT, void (*traitant)(void));
extern void masque_IRQ(uint32_t num_IRQ, bool masque);

#endif
