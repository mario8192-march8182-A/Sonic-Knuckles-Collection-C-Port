#ifndef SKC_BITDEVRCODETABLEENTRY_H
#define SKC_BITDEVRCODETABLEENTRY_H

typedef struct SKC_bitdevr_codetable_entry {
  unsigned char palette_index;
  unsigned char index_repeat_cnt;
  unsigned char code_len;
}
SKC_bitdevr_codetable_entry;

#endif
