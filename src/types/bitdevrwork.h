#ifndef SKC_BITDEVRWORK_H
#define SKC_BITDEVRWORK_H

typedef struct SKC_bitdevr_work {
  unsigned short buffer;
  unsigned short row_cnt;
  unsigned char pixel_cnt;
  unsigned char shift;
  unsigned char palette_index;
  unsigned char index_repeat_cnt;
  unsigned long pixels;
  unsigned long prev_pixels;
}
SKC_bitdevr_work;

#endif
