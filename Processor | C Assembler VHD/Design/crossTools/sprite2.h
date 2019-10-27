typedef unsigned int uint32;
typedef struct Objet {
  uint32 vivant;
  uint32 periode;
  uint32 echeance;
  int x,y;
  int dx, dy;
  uint32 * motif;
  uint32 couleur;
  uint32 fond[8][8];
  int ax,ay;
} Objet;
uint32 sprite_one[8]= {0x42, 0x24, 0x3c, 0x5a, 0xff, 0xbd, 0x81, 0x42};
uint32 sprite_two[8]={ 0xc3, 0x3c, 0x5a, 0xff, 0xff, 0x81, 0x42, 0x24};
uint32 sprite_three[8]={0xc3, 0x3c, 0x5a, 0xff, 0xff, 0xa5, 0xa5, 0x5a};
uint32 sprite_four[8]={0x00, 0x3c, 0x7e, 0xff, 0xff, 0xe7, 0xc3, 0xc3};
uint32 sprite_five[8]={0x81, 0x42, 0x3c, 0x5a, 0x5a, 0x3c, 0x42, 0x81};
uint32 sprite_six[8]={0x41, 0x22, 0x3e, 0x6b, 0x49, 0x7f, 0x3e, 0x55};
uint32 sprite_laser[8]={0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};
