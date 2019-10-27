#include <cpu.h>
#include <inttypes.h>
#include <string.h>

void ecrit_car(uint32_t lig, uint32_t col, char c);
void efface_ecran(void);
void place_curseur(uint32_t lig, uint32_t col);
void traite_char(char c);
void defilement(void);

const uint8_t COULEUR_FOND = 7; //gris
const uint8_t COULEUR_CARAC  = 5; //magenta
const uint8_t FORMAT = (COULEUR_FOND << 4) + COULEUR_CARAC;

void console_putbytes(char *chaine, int32_t taille)
{
	for(int i=0; i<taille; i++){
		char c = *chaine;
		traite_char(c);
		chaine++;
	}	
}

uint16_t *ptr_mem(uint32_t lig, uint32_t col){
	return (uint16_t*) (0xB8000 + 2*(lig*80 + col));
}

void ecrit_car(uint32_t lig, uint32_t col, char c){ //TODO: add format handling

	uint8_t carac = 0x0200 + c; //can be changed to handle format
	
	uint8_t* ptr = (uint8_t*) ptr_mem(lig, col);

	*ptr++ = carac;

	*ptr = FORMAT & 0b01111111; //on force le 7eme bit à 0 car clignotement non géré
}

void efface_ecran(void){
	for(int lig = 0; lig<25; lig++){
		for(int col = 0; col<80; col++){
			ecrit_car(lig,col,(char) 32);
		}
	}
	place_curseur(0,0);
}

void place_curseur(uint32_t lig, uint32_t col){
	uint16_t pos = col + lig*80;
	
	uint8_t bas = (uint8_t) (pos & 0x00FF);
	uint8_t haut = (uint8_t) (pos >> 8);
	
	outb(0x0F,(uint16_t)0x3D4);
	outb(bas, (uint16_t)0x3D5);
	outb(0x0E,(uint16_t)0x3D4);
	outb(haut, (uint16_t)0x3D5);
}

void traite_char(char c){
	static int first_time = 0;
	static uint8_t cursor_col = 0;
	static uint8_t cursor_lig = 0;
	if(first_time==0){
		efface_ecran();
		first_time++;
	}

	
	int8_t c_ascii = (int8_t) c;

	if(c>=32){
		ecrit_car(cursor_lig, cursor_col, c);
		if(cursor_col==79){
			cursor_col=0;
			cursor_lig+=1;			
		}
		else
			cursor_col+=1;		
	}

	switch(c_ascii){
	case 1: //for testing defilement
		defilement();
		break;
	case 8:
		if(cursor_col!=0)
			cursor_col-=1;
		break;
	case 9:
		if(cursor_col>=72)
			cursor_col = 79;
		else
			cursor_col += (8-cursor_col%8);
		break;
	case 10:
		cursor_col = 0;
		cursor_lig += 1;
		break;
	case 12:
		efface_ecran();
		cursor_col = 0;
		cursor_lig = 0;
		break;
	case 13:
		cursor_col = 0;
		break;
	}

    if(cursor_lig == 25){ //supposed to handle well case when last line
		defilement();
		cursor_lig=24;
	}
	
	place_curseur(cursor_lig, cursor_col);
}

void defilement(void){
	memmove((void*)(0xB8000), (void*) (0xB8000 + 160), 80*24*2); 
	for(int col = 0; col<80; col++){
		ecrit_car(24,col,(char) 32);
	}
}
