#ifndef MAPDEVRWK_H
#define MAPDEVRWK_H

typedef struct mapdevrwk {
  unsigned char* p_source;
  unsigned short data;
  unsigned char shift;
  unsigned char entry_bit_cnt;
}
mapdevrwk;

#endif
