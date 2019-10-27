#include <cpu.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "segment.h"
#include <stdbool.h>

int QUARTZ = 0x1234DD;
int CLOCKFREQ = 50;

extern void ecrit_car(uint32_t lig, uint32_t col, char c);

void tic_PIT(void);
void print_uptime(char* chaine);
void init_traitant_IT(int32_t num_IT, void (*traitant)(void));
void masque_IRQ(uint32_t num_IRQ, bool masque);

void print_uptime(char* chaine){//could modify to efface ecran 
	size_t len = strlen(chaine);
	for(size_t i=0; i<len; i++){
		char c = *chaine;
		ecrit_car(0,80-len+i, c);
		chaine++;
	}	
}

void tic_PIT(void){
	outb(0x20,0x20);	

	static int nb_tics = 0;
	static int nb_sec = 0;
	char chaine[80];	
			
	
	if(nb_tics == 0){
		nb_sec++;
		sprintf(chaine, "%d", nb_sec); // could modify to print minutes, hour...
		print_uptime(chaine);
	}
	nb_tics++;
	if(nb_tics == 20) nb_tics = 0;
}

void init_traitant_IT(int32_t num_IT, void (*traitant)(void)){
	uint32_t first_word = (uint32_t) KERNEL_CS << 16 | ((uint32_t) traitant & 0xFFFF);
	uint32_t second_word = ((uint32_t) traitant & 0xFFFF0000) | 0x8E00;
	
	uint32_t* idt =  (uint32_t*) 0x1000;
	idt += num_IT*2;
	*idt++ = first_word;
	*idt = second_word;
}

void masque_IRQ(uint32_t num_IRQ, bool masque){
	uint8_t current_mask = inb(0x21);
	uint8_t ind_IRQ = 1<<num_IRQ;
	if((current_mask & ind_IRQ) == !masque)//si irq masquee
		outb(current_mask ^ ind_IRQ , 0x21);
}

void init_clock(){
	outb(0x34,0x43);
	outb((QUARTZ / CLOCKFREQ) % 256, 0x40);
	outb((QUARTZ / CLOCKFREQ) / 256, 0x40 );
}
