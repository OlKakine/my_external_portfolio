/* 
 * cep_excp.S.c - Exception handlers for the CEP Platform
 *
 * Copyright (c) 2013 The Ensimag CEP Team
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

#include "cep_asm.h"

    .set noreorder

    .global mips_mask_irq, mips_unmask_irq, mips_wait
    .global mips_set_timer, mips_ack_and_set_timer, mips_ack_timer
    .global mips_timer_get_ticks

    .macro excp_handler_begin name, msg
        .global \name\()_hdl

        .ifnb msg
            .data
        msg_\name\() : .string "\msg"
        .endif

        .text
        .set noreorder
        .ent \name\()_hdl
    \name\()_hdl :
    .endm

    .macro excp_handler_end name
        .end \name\()_hdl
    .endm


    .macro excp_error_shutdown name, msg
        excp_handler_begin \name, "\msg"

        la $a0, msg_\name
        jal printf
        nop
        j platform_shutdown
        nop

        excp_handler_end \name
    .endm



    .text

    .org 0
tlb_refill_hdl:
    j excp_hdl
    nop
    

    .org 0x180
excp_hdl:
    j mon_traitant
    nop
/* Gestionnaire d'interruption générique appelé si les étudiants n'en
 * définissent pas un */
.weak mon_traitant
mon_traitant:
    .set noat
    /* Context save */

    /* Reserve some space in the stack */
    addiu  $29, $29, -(22 * 4)

    /* GPR */
	sw     $1,   0*4($29)
	sw     $2,   1*4($29)
	sw     $3,   2*4($29)
	sw     $4,   3*4($29)
	sw     $5,   4*4($29)
	sw     $6,   5*4($29)
	sw     $7,   6*4($29)
	sw     $8,   7*4($29)
	sw     $9,   8*4($29)
	sw    $10,   9*4($29)
	sw    $11,  10*4($29)
	sw    $12,  11*4($29)
	sw    $13,  12*4($29)
	sw    $14,  13*4($29)
	sw    $15,  14*4($29)
	sw    $24,  15*4($29)
	sw    $25,  16*4($29)
	sw    $30,  17*4($29)
	sw    $31,  18*4($29)

    /* HI/LO */
	mfhi  $26
	sw    $26,  19*4($29)
	mflo  $26
	sw    $26,  20*4($29)

    /* EPC */
	mfc0  $26,       $14 
	nop
	sw    $26,  21*4($29) 
	nop
    .set at

    
    /* Fetch the exception cause */
    mfc0 $26, $12           /* CP0 Status Register : for Interrupt Mask (IM) */
    mfc0 $27, $13           /* CP0 Cause Register : for Interrupt Cause (ExcCode) and Interrupt Pending bit (IP) */
    
    /* Read the ExcCode. 0 -> interrupt. Other -> exception */
    andi $2, $27, 0x7c     /* ExcCode bits 6..2 from Cause Register */
    srl  $2, $2,  2
    bnez $2, exception_not_irq

    /* This is an IRQ. Look at Cause(IP) to know which one */
    andi $27, $27, 0xff00   /* Cause interrupt bits 15..8 from Cause Register */
    and  $27, $27, $26      /* Mask with Status(IM) bits 15..8 */

    /* Nothing? Then end */
    beq  $27, $0, excp_end
    
    /* Compute the irq number */
    clz  $27, $27           /* $27 = 23 - irq_number (in [16..23]) */
    xori $27, $27, 0x17     /* $27 = irq_number (in [7..0]) = */

    /* Load the irq handler address and call it */
    sll $27, $27, 2
    lw $2, irq_handlers_vector($27)
    jal $2
    nop

    j excp_end
    nop

    

exception_not_irq:
    /* Load the exception handler address */
    sll $2, $2, 2
    lw $3, excp_handler_vector($2)

    jr $3
    nop




excp_end:
    .set noat
    /* Context restore */
	lw     $1,    0*4($29)
	lw     $2,    1*4($29)
	lw     $3,    2*4($29)
	lw     $4,    3*4($29)
	lw     $5,    4*4($29)
	lw     $6,    5*4($29)
	lw     $7,    6*4($29)
	lw     $8,    7*4($29)
	lw     $9,    8*4($29)
	lw    $10,    9*4($29)
	lw    $11,   10*4($29)
	lw    $12,   11*4($29)
	lw    $13,   12*4($29)
	lw    $14,   13*4($29)
	lw    $15,   14*4($29)
	lw    $24,   15*4($29)
	lw    $25,   16*4($29)
	lw    $30,   17*4($29)
	lw    $31,   18*4($29)
	
	lw    $26,   19*4($29)
	mthi  $26
	lw    $27,   20*4($29)
	mtlo  $27
	
	lw    $26,   21*4($29)
    nop
    mtc0  $26,  $14

    addiu $29,  $29,  22 * 4
    .set at

    eret



/* The specific handlers. */

/* Unknown interrupt */
unk_irq_hdl:
    # Shutdown the platform
    j platform_shutdown
    nop

/* Timer interrupt. Declared as weak to be overwritable by students */
.weak timer_irq_hdl
timer_irq_hdl:
    # Ack and reset the timer
    li $26, 0x10000000
    mtc0 $26, $11
    mtc0 $0, $9

    jr $ra
    nop

/* Pushbtn interrupt. Declared as weak to be overwritable by students */
.weak pushbtn_irq_hdl
pushbtn_irq_hdl:
    # Ack the push buttons by reading them
    lw $0, PERIPH_SWITCHES

    jr $ra
    nop


/* Unknown exception */
excp_error_shutdown unk_excp, "Unhandled exception.\n"


/* Bad address load or store (tlb unmapped, bus error) */
excp_handler_begin bad_addr, "Bad address 0x%.8x at $pc=0x%.8x.\n"
    la   $a0, msg_bad_addr
    mfc0 $a1, $8    /* BadVAddr */
    mfc0 $a2, $14   /* EPC */

    nop
    jal printf
    nop

    j platform_shutdown
    nop
excp_handler_end bad_addr



# Generic routines

platform_shutdown:
    li $2, PLATFORM_SHUTDOWN_MAGIC
    sw $2, SIM_PLATFORM_REGS

    
hang:
    nop
    wait
    nop
    b hang
    nop


mips_wait:
    nop
    wait
    nop
    jr $ra
    nop

mips_mask_irq:
    mfc0 $k0, $12
    nop

    li   $k1, 0xffff00ff
    and  $k0, $k0, $k1
    nop
    mtc0 $k0, $12
    nop

    jr $ra
    nop

mips_unmask_irq:
    mfc0 $26, $12
    nop

    ori $26, $26, 0x0000ff00
    mtc0 $26, $12
    nop

    jr $ra
    nop

mips_set_timer:
    mtc0 $zero, $9
    mtc0 $a0, $11

    jr $ra
    nop

mips_ack_and_set_timer:
    mfc0 $t0, $9
    addu $t0, $t0, $a0
    mtc0 $t0, $11

    jr $ra
    nop

mips_ack_timer:
    mtc0 $zero, $11

    jr $ra
    nop

mips_timer_get_ticks:
    mfc0 $v0, $9

    jr $ra
    nop

    .data
irq_handlers_vector:
    .long   unk_irq_hdl     /* irq0: user defined */
    .long   unk_irq_hdl     /* irq1: user defined */
    .long   uart_16550a_irq /* irq2 | HW interrupt 0: serial */
    .long   pushbtn_irq_hdl /* irq3 | HW interrupt 1: pushbtn */
    .long   unk_irq_hdl     /* irq4 | HW interrupt 2 */
    .long   unk_irq_hdl     /* irq5 | HW interrupt 3  */
    .long   unk_irq_hdl     /* irq6 | HW interrupt 4 */
    .long   timer_irq_hdl   /* irq7 | HW interrupt 5 : timer */

excp_handler_vector:
    .long   0               /* Interrupt */
    .long   unk_excp_hdl    /* TLB modification exception */
    .long   bad_addr_hdl    /* TLB exception (load or instruction fetch) */
    .long   bad_addr_hdl    /* TLB exception (store) */
    .long   bad_addr_hdl    /* Address error exception (load or instruction fetch) */
    .long   bad_addr_hdl    /* Address error exception (store) */
    .long   unk_excp_hdl    /* Bus error exception (instruction fetch) */
    .long   unk_excp_hdl    /* Bus error exception (data reference: load or store) */
    .long   unk_excp_hdl    /* Syscall exception */
    .long   unk_excp_hdl    /* Breakpoint exception */
    .long   unk_excp_hdl    /* Reserved instruction exception */
    .long   unk_excp_hdl    /* Coprocessor Unusable exception */
    .long   unk_excp_hdl    /* Arithmetic Overflow exception */
    .long   unk_excp_hdl    /* Trap exception */
    .long   unk_excp_hdl    /* Reserved */
    .long   unk_excp_hdl    /* Floating point exception */


# vim: expandtab sw=4 ts=4 sts=4
