#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "cep.h"

#define TICK_ALARM 10000000

enum display_mode {NONE,VGA,SEG,BOTH};

extern struct compt {
        uint32_t count;           // valeur actuelle du compteur
        void (*way)(void);        // pointeur de fonction de type void funcname(void)
        enum display_mode mode;   // mode d'affichage, voir l'enum ligne 15
} *param; // variable globale de type pointeur sur struct compt


/*
 * PARTIE DU CODE NÉCESSAIRE À L'AFFICHAGE DES CHIFFRES SUR L'ÉCRAN
 * IL N'EST PAS UTILE QUE VOUS REGARDIEZ/COMPRENIEZ CETTE PARTIE
 * POUR FAIRE L'EXERCICE
 * Mais si vous avez envie de comprendre, faites le reste et
 * revenez ici après !
 */

/* Bitmap 8x8 pour les numéros de 0 à 9
 * Un bit par pixel */
static uint8_t numberbitmap[10][8]={
{0x38,0x44,0x44,0x44,0x44,0x44,0x44,0x38}, //0
{0x10,0x30,0x50,0x10,0x10,0x10,0x10,0x10}, //1
{0x3c,0x44,0x02,0x04,0x08,0x10,0x20,0x7e}, //2 
{0x3c,0x42,0x02,0x1c,0x02,0x02,0x42,0x3c}, //3
{0x08,0x18,0x28,0x48,0xfe,0x08,0x08,0x08}, //4
{0x7e,0x40,0x40,0x78,0x06,0x02,0x06,0x78}, //5
{0x0e,0x30,0x60,0x7c,0x42,0x42,0x42,0x3c}, //6
{0x7e,0x02,0x04,0x08,0x08,0x10,0x20,0x40}, //7
{0x3c,0x42,0x42,0x3c,0x42,0x42,0x42,0x3c}, //8
{0x3c,0x66,0x42,0x66,0x3e,0x02,0x06,0x7c}  //9
};

static void display_digit(uint8_t digit, uint32_t offset)
{
        uint8_t *fb = (uint8_t *) VRAM_BASE_ADDR;
        for(uint8_t i= 0;i<8;i++){
                fb[offset+i*(FRAMEBUFFER_WIDTH >> 3)]=numberbitmap[digit][i];
        }
}

static void display_erase(uint32_t offset)
{
        uint8_t *fb = (uint8_t *) VRAM_BASE_ADDR;
        for(uint8_t i= 0;i<8;i++){
                fb[offset+i*(FRAMEBUFFER_WIDTH >> 3)]=0;
        }
}

static void displayVGA(uint32_t digit)
{
        
        uint8_t taille=0;
        uint32_t tmp=digit;
        do{
                tmp/=10;
                taille++;
        } while (tmp);
        /*offset du MSD */
        tmp = 4819 + taille;
        for(uint8_t i=0; i< taille; i++){
                display_digit(digit%10, tmp);
                display_erase(tmp-1);
                tmp-=2;
                digit/=10;
        }
}

static void display7seg(uint32_t digit)
{
        /*Affichage des entiers décimaux jusqu'à 9999*/
        uint32_t *periph= (uint32_t *)PERIPH_7SEG;
        uint32_t tmp=0;
        for(uint8_t i=0;i<4;i++){
                tmp>>=4;
                tmp|=(digit%10)<<12;
                digit/=10;
        } 
        *periph=tmp;
}


static void nettoyage(void)
{
        /*Nettoyage complet de la zone d'affichage du VGA */
        for(uint32_t i=4817; i<4824; i++){
                display_erase(i);
        }
}

void display(void)
{
        nettoyage();
        if(param->mode==VGA ||param->mode==BOTH) { displayVGA(param->count); }
        if(param->mode==SEG ||param->mode==BOTH) { display7seg(param->count); }
}

/*
 * PARTIE CONCERNANT L'EXERCICE, QU'IL FAUT DONC LIRE ET COMPRENDRE
 */
extern void set_alarm(uint32_t tick); // À écrire en assembleur


void upcounter(void)
{
        param->count++;
}

void downcounter(void)
{
        param->count--;
}

void timer_irq_hdl(void)
{       
        printf("Traitant d'interruption. Appel n° %" PRIu32 "\n", param->count);       
        set_alarm(TICK_ALARM);
        param->way();
        display();
}

int main(void)
{
        struct compt inst={.count=0,.way=upcounter,.mode=VGA};
        param=&inst;

        /* Configuration des boutons poussoirs en mode interruption */
        *(volatile uint32_t *)PERIPH_PUSHBTN_CTL = PERIPH_PUSHBTN_INT;

        /*Démarrage du timer */
        set_alarm(TICK_ALARM);

        while(param->count<=100);
        return 0;
}
    
