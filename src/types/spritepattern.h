#ifndef SKC_SPRITEPATTERN_H
#define SKC_SPRITEPATTERN_H

#include "spriteplacement.h"

typedef struct SKC_sprite_pattern {
  unsigned short cnt;
  SKC_sprite_placement spr[];
}
SKC_sprite_pattern;

#endif
