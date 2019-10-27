#include "sprite2.h"
#define NOBJETS 7
Objet objet[NOBJETS]={
  {1,3,1, 20,29, 0,0, sprite_four,0x003F},
  {0,1,1, 20,29, 0,0, sprite_laser,0xFFFF},
  {1,4,1, 10,1, -1,0, sprite_two,0x0FC0},
  {1,4,1, 26,1, -1,0, sprite_three,0xF000},
{1,4,1, 10,3, -1,0, sprite_one,0xF03F},
{1,4,1, 14,3, -1,0, sprite_five,0xFFC0},
{1,4,1, 18,3, -1,0, sprite_six,0x0FFF}
    };
uint32 nbAlien;
void affiche_sprite(Objet *objet);
extern void affiche_motif(uint32 motif[8], int x, int y,uint32 couleur);
extern void affiche_motif_mask(uint32 motif[8], int x, int y);
extern void sauve_motif(uint32 motif[8], int x, int y);
extern void timer_set(uint32 period, uint32 start);
extern void timer_wait(void);
extern void LED(uint32 val);
extern uint32 push_button_get(void);
volatile uint32 *img  = (volatile uint32 *)0x80000;
volatile uint32 *led  = (volatile uint32 *)0x4000;
volatile uint32 *push = (volatile uint32 *)0x4004;
volatile uint32 *timer= (volatile uint32 *)0x4010;
void efface_ecran(uint32 couleur){
  uint32 x,y;
  for (x=0;x<320;x++)
    for (y=0;y<240;y++)
      img[320*y+x]=couleur;
}
void initialise(){
  uint32 i,dx,dy;
  nbAlien=NOBJETS-2;
    efface_ecran(0);
    /* initialisation */
    for(i=0;i<NOBJETS;i++)
    {
      objet[i].vivant=(i==1?0:1);
      objet[i].periode=(i==1?1:i==0?3:4);
      objet[i].echeance=1;
      if (i>1) {
	objet[i].y=i>3?3:1;
	objet[i].x=((i>3)?(10+(i-4)*4):(10+(i-2)*16));
	objet[i].dx=-1;objet[i].dy=0;
      }

      objet[i].ax=-1;objet[i].ay=-1;
      for (dx=0;dx<8;dx++)
	for (dy=0;dy<8;dy++)
	  objet[i].fond[dx][dy]=lit_pixel(((objet[i].x)<<3)+dx,((objet[i].y)<<3)+dy);
    }

}
void main(void)
{
  uint32 i,ctr,dx,dy;
    Objet *vaisseau, *missile;
    uint32 alien_etat=0, cpt=0;
    uint32 bord;
    uint32 led_s;
    uint32 points=0;
    timer_set(800000, 200);
    vaisseau=&objet[0];
    missile=&objet[1];
    led_s=0x00;
    initialise();

    /*boucle affichage*/
    //  LED(4);
    while(1)
    {
        bord=0;
        /* décrémente l'écheance de tous les objets vivants */
        for(i=0;i<NOBJETS;i++)
        {
            if (objet[i].vivant)
                objet[i].echeance--;
        }
        /* affiche tous les objets vivants */
        for(i=0;i<NOBJETS;i++)
        {
            if (objet[i].vivant)
	      affiche_sprite(&objet[i]);
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
                //sauve_motif(objet[i].fond, objet[i].x, objet[i].y);
		if (i>1 && objet[i].y>=vaisseau->y){
		  efface_ecran(0x00FF);
		  initialise();
		}

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
		  nbAlien--;
		  if (nbAlien==0) efface_ecran(0xFF00);
                    objet[i].vivant=0;
                    missile->vivant=0;
		    affiche_sprite(&objet[i]);
		    affiche_sprite(missile);
                    /* si c'est le cas, gagne un point et on l'affiche */
                    points++;
                    //SEG(points);
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
	    affiche_sprite(missile);
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
            }
        }
        LED(led_s);
        led_s++;
        timer_wait();
    }
}


void affiche_pixel(int pix, int x, int y)
{
    img[y * 320 + x]=pix;
}
int lit_pixel(int x,int y){
  return img[y *320 + x];
}

void affiche_motif_ligne(uint32 m,int x,int y,uint32 couleur){
  int i;
  for (i=0;i<8;i++){
    //int pix=lit_pixel(x+i,y);
    int color = ((m & 1) == 1)?couleur:0;
    m=m>>1;
    //    pix = pix ^ color;
    affiche_pixel(color,x+i,y);
  }
}

void affiche_motif(uint32 motif[8], int x, int y,uint32 couleur)
{
  int i;
  for(i=0;i<8;i++)
    {
      affiche_motif_ligne(motif[i],x,y+i,couleur);
    }
}
void affiche_sprite(Objet *objet){
  int dx,dy;
  if ((objet->ax>-1 && objet->ay>-1 ) && (objet->x!=objet->ax || objet->y!=objet->ay || !objet->vivant))
  {
    for (dx=0;dx<8;dx++)
      for (dy=0;dy<8;dy++)
	affiche_pixel(objet->fond[dx][dy],((objet->ax)<<3)+dx,((objet->ay)<<3)+dy);
  }
  for (dx=0;dx<8;dx++)
    for (dy=0;dy<8;dy++)
      objet->fond[dx][dy]=lit_pixel(((objet->x)<<3)+dx,((objet->y)<<3)+dy);
  (objet->ax)=(objet->x);(objet->ay)=(objet->y);

  if (objet->vivant)
    affiche_motif(objet->motif,(objet->x)<<3,(objet->y)<<3,objet->couleur);
}
void timer_set(uint32 period, uint32 start)
{
    *timer=period;
    *(timer+1)=start;
}
void timer_wait(void)
{
    while(*timer!=0);
}

uint32 push_button_get(void)
{
    return (*push)>>16;
}
void LED(uint32 val)
{
    *led=val;
}
