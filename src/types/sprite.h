#ifndef SPRITE_H
#define SPRITE_H

typedef struct Sprite {
  long x;
  long y;
  unsigned long w;
  unsigned long h;
  // bits 4, 5, 6: palette line
  // bit 7: priority flag
  // bit 8: vertical flip flag
  // bit 9: horizontal flip flag
  unsigned long flags;
  unsigned long vram_offset;
  unsigned long dummy1;
  unsigned long dummy2;
}
Sprite;

#endif
