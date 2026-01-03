#ifndef SKC_ENEMYINIT0DATA_H
#define SKC_ENEMYINIT0DATA_H

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

#endif
