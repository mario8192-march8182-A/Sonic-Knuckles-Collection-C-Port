#ifndef SKC_SPRITEPATTERN_H
#define SKC_SPRITEPATTERN_H

typedef struct SKC_sprite_placement {
  signed char yoff;
  unsigned char etc;
  unsigned short index;
  short xoff;
}
SKC_sprite_placement;

typedef struct SKC_sprite_pattern {
  unsigned short cnt;
  SKC_sprite_placement spr[];
}
SKC_sprite_pattern;

#endif
