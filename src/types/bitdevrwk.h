#ifndef BITDEVRWK_H
#define BITDEVRWK_H

typedef struct bitdevrwk {
  unsigned long* p_destination;
  unsigned char* p_source;
  unsigned short data;
  unsigned short row_cnt;
  unsigned char pixel_cnt;
  unsigned char shift;
  unsigned char palette_index;
  unsigned char index_repeatcnt;
  unsigned long prev_pixels;
}
bitdevrwk;

#endif
