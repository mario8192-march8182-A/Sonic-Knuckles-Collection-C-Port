#ifndef SKC_ENEMYINITDATA_H
#define SKC_ENEMYINITDATA_H

#include "spritepattern.h"

typedef struct SKC_enemy_init0_data {
  SKC_sprite_pattern** patbase;
  unsigned short sproffset;
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
SKC_enemy_init0_data;

typedef struct SKC_enemy_init1_data {
  unsigned short sproffset;
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
SKC_enemy_init1_data;

typedef struct SKC_enemy_init2_data {
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
SKC_enemy_init2_data;

#endif
