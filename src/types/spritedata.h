#ifndef SKC_SPRITEDATA_H
#define SKC_SPRITEDATA_H

typedef struct SKC_sprite_data {
  unsigned int vp : 16;
  unsigned int vs : 2;
  unsigned int hs : 2;
  unsigned int unused14 : 4;
  unsigned int next : 8;
  unsigned int gfx : 11;
  unsigned int hf : 1;
  unsigned int vf : 1;
  unsigned int pl : 2;
  unsigned int pr : 1;
  unsigned int hp : 16;
}
SKC_sprite_data;

#endif
