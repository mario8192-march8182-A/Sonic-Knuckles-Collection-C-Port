#ifndef ANIMSCRIPT_H
#define ANIMSCRIPT_H

typedef struct animscript {
  unsigned char dummy1;
  unsigned char dummy2;
  unsigned char dummy3;
  signed char tim;
  unsigned char* p_rom;
  unsigned short vram_adr;
  unsigned char cnt;
  unsigned char size;
  signed char data[];
}
animscript;

#endif
