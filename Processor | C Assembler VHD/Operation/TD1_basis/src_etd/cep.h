#ifndef _CEP_H
#define _CEP_H

#include <inttypes.h>

#include "cep_asm.h"

/* Issue a `wait' instruction that puts the cpu into sleep until the next
 * interrupt */
extern void mips_wait(void);

/* Mask the interrupts */
extern void mips_mask_irq(void);

/* Unmask the interrupts */
extern void mips_unmask_irq(void);

/* Set the timer to raise an irq in ``ticks'' ticks */
extern void mips_set_timer(uint32_t ticks);

/* Acknowledge and reset the timer to raise an irq in ``ticks'' ticks */
extern void mips_ack_and_set_timer(uint32_t ticks);

/* Acknowledge but do not reset the timer */
extern void mips_ack_timer(void);

/* Get the ticks counter current value */
extern uint32_t mips_timer_get_ticks(void);

#endif
