#include <inttypes.h>

#include "cep.h"
#include "mips_invader.h"

/* Timer à 50Mhz, une irq toute les 20ms -> 50 * 1000 * 1000 * 0.02 */
#define TICKS_PER_IRQ	1000000

typedef struct Objet {
	uint32_t vivant;
	uint32_t periode;
	uint32_t echeance;
	int x,y;
	int dx, dy;
	uint32_t motif[8];
	uint32_t fond[8];
} Objet;

#define NOBJETS 9

Objet objet[NOBJETS]={
	{1,3,1, 20,29, 0,0, sprite_four},
	{0,1,1, 20,29, 0,0, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
	{1,4,1, 10,1, -1,0, sprite_two},
	{1,4,1, 26,1, -1,0, sprite_three},
#if NOBJETS > 4
	{1,4,1, 10,3, -1,0, sprite_one},
	{1,4,1, 14,3, -1,0, sprite_five},
	{1,4,1, 18,3, -1,0, sprite_six},
	{1,4,1, 22,3, -1,0, sprite_three},
	{1,4,1, 26,3, -1,0, sprite_one},
#endif
};

static void affiche_motif(uint32_t motif[8], int x, int y);
static void affiche_motif_mask(uint32_t motif[8], int x, int y);
static void sauve_motif(uint32_t motif[8], int x, int y);
static void timer_set(void);
static void timer_wait(void);
static void set_leds(uint32_t val);
static void set_7segs(uint32_t val);
static uint32_t push_button_get(void);

volatile uint32_t *img  = (volatile uint32_t *) (VRAM_BASE_ADDR);
volatile uint32_t *led  = (volatile uint32_t *) (PERIPH_LED);
volatile uint32_t *push = (volatile uint32_t *) (PERIPH_SWITCHES);
volatile uint32_t *seg  = (volatile uint32_t *) (PERIPH_7SEG);

void main(void)
{
	uint32_t i,ctr;
	Objet *vaisseau, *missile;
	uint32_t alien_etat=0, cpt=0;
	uint32_t bord;
	uint32_t led_s;
	uint32_t points=0;


	timer_set();
	vaisseau=&objet[0];
	missile=&objet[1];
	led_s=0x00;

	/* initialisation */
	for(i=0;i<NOBJETS;i++)
	{
		if (objet[i].vivant)
			sauve_motif(objet[i].fond, objet[i].x, objet[i].y);
		/* calcule les masques de fond */
#if 1
		uint32_t mg, md;
		uint32_t j,b;
		for(j=0;j<8;j++)
		{
			mg=objet[i].motif[j]<<1;
			md=objet[i].motif[j]>>1;
			for(b=0;b<8;b++)
			{
				mg|=objet[i].motif[j]>>b;
				md|=objet[i].motif[j]<<b;
			}
			mg=(mg & md) & 0xFF;
			objet[i].motif[j]|=(mg<<8);
		}
#endif
	}
	for(i=0;i<NOBJETS;i++)
	{
		if (objet[i].vivant)
			affiche_motif(objet[i].motif, objet[i].x, objet[i].y);
	}
	/*boucle affichage*/
	//  set_leds(4);
	while(1)
	{
		bord=0;
		/* décrémente l'écheance de tous les objets vivants */
		for(i=0;i<NOBJETS;i++)
		{
			if (objet[i].vivant)
				objet[i].echeance--;
		}
		/* remet tous les fonds de tous les objets vivants */
		for(i=0;i<NOBJETS;i++)
		{
			if (objet[i].vivant)
				affiche_motif(objet[i].fond, objet[i].x, objet[i].y);

		}
		/* calcule les nouvelles positions de tous les objets vivants */
		for(i=0;i<NOBJETS;i++)
		{
			/* la mise à jour se fait à la fin de l'échéance */
			if (objet[i].vivant && objet[i].echeance==0)
			{
				/* réinitialise l'échéance */
				objet[i].echeance=objet[i].periode;

				/* calcule la nouvelle position et gère les bords */
				objet[i].x+=objet[i].dx;
				if (objet[i].x<0)
					objet[i].x=0;
				if (objet[i].x>39)
					objet[i].x=39;
				objet[i].y+=objet[i].dy;

				/* test si un alien atteint un bord */
				if (i>=2 && (objet[i].x==0 || objet[i].x==39))
					bord=1;

				/* sauvegarde le fond de la prochaine position */
				sauve_motif(objet[i].fond, objet[i].x, objet[i].y);
			}
		}
		/* si le missile est vivant, teste s'il touche un alien */
		if (missile->vivant)
		{ 
			for(i=2;i<NOBJETS;i++)
				if (objet[i].vivant && 
				    missile->x == objet[i].x && 
				    missile->y == objet[i].y)

				{	
					objet[i].vivant=0;
					missile->vivant=0;
					//affiche_motif(objet[i].fond, objet[i].x, objet[i].y);
					/* si c'est le cas, gagne un point et on l'affiche */
					points++;
					set_7segs(points);
				}
		}
		/* si un alien atteint un bord, ils descendent puis changent de sens */
		if (bord)
		{  
			switch(alien_etat) {
			case 0:
				for(i=2;i<NOBJETS;i++)
				{
					objet[i].dx=0;
					objet[i].dy=1;
				}
				alien_etat=1;
				break;

			case 1:
				for(i=2;i<NOBJETS;i++)
				{
					objet[i].dx=1;
					objet[i].dy=0;
				}
				alien_etat=2;
				break;

			case 2:
				for(i=2;i<NOBJETS;i++)
				{
					objet[i].dx=0;
					objet[i].dy=1;
				}
				alien_etat=3;
				break;

			case 3:
				for(i=2;i<NOBJETS;i++)
				{
					objet[i].dx=-1;
					objet[i].dy=0;
				}
				alien_etat=1;
				break;
			};
		}
		/* le missile disparait en arrivant en haut */
		if (missile->vivant && missile->y==0)
		{
			missile->vivant=0;
			// affiche_motif(missile->fond, missile->x, missile->y);
		}
		/* gestion des boutons poussoirs */
		ctr=push_button_get();
		/* déplacement horizontal */
		vaisseau->dx=0;
		if (ctr & 0x1)
			vaisseau->dx=1;
		if (ctr & 0x2)
			vaisseau->dx=-1;
		/* lance un missile */
		if (ctr & 0x4)
		{
			if (! missile->vivant)
			{
				missile->vivant=1;
				missile->dx=0;
				missile->dy=-1;
				missile->x=vaisseau->x;
				missile->y=vaisseau->y-1;
				missile->echeance=missile->periode;
				sauve_motif(missile->fond, missile->x, missile->y);
			}
		}

		/* affiche tous les objets vivants */
		for(i=0;i<NOBJETS;i++)
		{
			if (objet[i].vivant)
				affiche_motif_mask(objet[i].motif, objet[i].x, objet[i].y);
		}
		set_leds(led_s);

		led_s++;
		timer_wait();
	}

}


#define PIX_ADDR_X 9
#define PIX_ADDR_Y 8
#define PIX_ADDR_X_SHIFT 5
#define PIX_ADDR_X_MASK ((1<<PIX_ADDR_X)-1)
#define PIX_ADDR_X_MASK_WORD ((1<<PIX_ADDR_X_SHIFT)-1)
#define PIX_ADDR_Y_SHIFT (PIX_ADDR_X-PIX_ADDR_X_SHIFT)
#define PIX_ADDR_Y_MASK ((1<<PIX_ADDR_Y)-1)


static void affiche_pixel(int pix, int x, int y)
{
	uint32_t addr;
	uint32_t d, w, mask;
	addr=((y & PIX_ADDR_Y_MASK) << PIX_ADDR_Y_SHIFT) | ((x & PIX_ADDR_X_MASK) >> PIX_ADDR_X_SHIFT);
	d=(PIX_ADDR_X_MASK_WORD & x);
	mask=1<<d;
	img[addr]=(img[addr] & ~mask) | ((pix&1) << d);
}

#define SPRITE_X_SHIFT 3
#define SPRITE_X_MASK 0x03
#define SPRITE_MASK 0xFF

#define SPRITE_ADDR_X_SHIFT (5-SPRITE_X_SHIFT)
#define SPRITE_ADDR_X_MASK 0x3F
#define SPRITE_ADDR_Y_SHIFT (6-(SPRITE_ADDR_X_SHIFT)+SPRITE_X_SHIFT)
#define SPRITE_ADDR_Y_MASK 0x1F
static void affiche_motif(uint32_t motif[8], int x, int y)
{
	uint32_t addr;
	uint32_t xshift;
	uint32_t fond_mask;
	uint32_t i;

	addr=((y & SPRITE_ADDR_Y_MASK) << SPRITE_ADDR_Y_SHIFT) | ((x & SPRITE_ADDR_X_MASK) >> SPRITE_ADDR_X_SHIFT);
	xshift= (3-(x & SPRITE_X_MASK))<<SPRITE_X_SHIFT;
	fond_mask=~(SPRITE_MASK<<xshift);
	for(i=0;i<8;i++)
	{
		img[addr]&=fond_mask;
		img[addr]|=((motif[i]&0xFF)<<xshift);
		addr+=(512>>5);
	}

}
static void affiche_motif_mask(uint32_t motif[8], int x, int y)
{
	uint32_t addr;
	uint32_t xshift;
	uint32_t fond_mask;
	uint32_t i;

	addr=((y & SPRITE_ADDR_Y_MASK) << SPRITE_ADDR_Y_SHIFT) | ((x & SPRITE_ADDR_X_MASK) >> SPRITE_ADDR_X_SHIFT);
	xshift= (3-(x & SPRITE_X_MASK))<<SPRITE_X_SHIFT;
	for(i=0;i<8;i++)
	{
		fond_mask=(motif[i]>>8) & 0xFF;
		fond_mask=~(fond_mask<<xshift);
		img[addr]&=fond_mask;
		img[addr]|=((motif[i]&0xFF)<<xshift);
		addr+=(512>>5);
	}

}

static void sauve_motif(uint32_t motif[8], int x, int y)
{
	uint32_t addr;
	uint32_t xshift;
	uint32_t fond_mask;
	uint32_t i;

	addr=((y & SPRITE_ADDR_Y_MASK) << SPRITE_ADDR_Y_SHIFT) | ((x & SPRITE_ADDR_X_MASK) >> SPRITE_ADDR_X_SHIFT);
	xshift= (3-(x & SPRITE_X_MASK))<< SPRITE_X_SHIFT;
	for(i=0;i<8;i++)
	{
		motif[i]=((img[addr]>>xshift)& SPRITE_MASK);
		addr+=(512>>5);
	}

}

static void timer_set(void)
{
	mips_set_timer(TICKS_PER_IRQ);
}

static void timer_wait(void)
{
	mips_wait();
}

static uint32_t push_button_get(void)
{
	return (*push)>>8;
}

static void set_leds(uint32_t val)
{
	*led=val;
}

static void set_7segs(uint32_t val)
{
	*seg=val;
}

void timer_irq_hdl(void)
{
	mips_ack_and_set_timer(TICKS_PER_IRQ);
}
