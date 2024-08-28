#ifndef SPRITEPATTERN_H
#define SPRITEPATTERN_H

typedef struct sprite_data {
  signed char yoff;
  unsigned char etc;
  unsigned short index;
  short xoff;
}
sprite_data;

typedef struct sprite_pattern {
  unsigned short cnt;
  sprite_data spr[];
}
sprite_pattern;

#endif
