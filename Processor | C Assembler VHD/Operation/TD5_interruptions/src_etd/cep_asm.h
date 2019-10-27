#ifndef CEP_ASM_H
#define CEP_ASM_H

#define PERIPHS_BASE_ADDR   	0x80050000
#define VRAM_BASE_ADDR      	0x80051000
#define UART_BASE_ADDR     	0x80054000
#define SIM_PLATFORM_REGS	0x80055000

#define PLATFORM_SHUTDOWN_MAGIC 0xdeadbeef

#define	FRAMEBUFFER_WIDTH	512	
#define	FRAMEBUFFER_HEIGHT	240

#define FRAMEBUFFER_SIZE	(FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT)
#define VRAM_SIZE		(FRAMEBUFFER_SIZE >> 3)

#define PERIPH_LED		((volatile uint32_t *)(PERIPHS_BASE_ADDR))
#define PERIPH_SWITCHES		((volatile uint32_t *)(PERIPHS_BASE_ADDR+4))
#define PERIPH_PUSHBTN_CTL	((volatile uint32_t *)(PERIPHS_BASE_ADDR+8))
#define PERIPH_7SEG		((volatile uint32_t *)(PERIPHS_BASE_ADDR+12))
#define PERIPH_7SEG_CTL		((volatile uint32_t *)(PERIPHS_BASE_ADDR+16))

#define PERIPH_PUSHBTN_POLL	0
#define PERIPH_PUSHBTN_INT	1

#define	PERIPH_7SEG_LO		0
#define	PERIPH_7SEG_HI		1
#define	PERIPH_7SEG_RAW		2

#define TIMER_FREQ_MHZ		50
#define TIMER_FREQ		(TIMER_FREQ_MHZ * 1000 * 1000)

#endif
