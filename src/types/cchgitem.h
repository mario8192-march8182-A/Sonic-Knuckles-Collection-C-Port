#ifndef SKC_CCHGITEM_H
#define SKC_CCHGITEM_H

typedef struct SKC_cchg_item {
  unsigned short palette_index;
  unsigned char color_cnt_per_chunk;
  unsigned char frame_counter_max;
  short data[];
}
SKC_cchg_item;

#endif
