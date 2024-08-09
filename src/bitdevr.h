#ifndef BITDEVR_H
#define BITDEVR_H

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

void bitdevr(unsigned long* p_destination, unsigned char* p_source);
bool bitdevr_decompress(bitdevrwk* p_wk, unsigned char* p_bitdevwk, void(*p_write)(unsigned long, bitdevrwk*));
void bitdevr_decompress_inline(bitdevrwk* p_wk);
void bitdevr_write(unsigned long pixels, bitdevrwk* p_wk);
void bitdevr_xorwrite(unsigned long pixels, bitdevrwk* p_wk);
unsigned char* bitdevr_codetable(unsigned char* p_source, unsigned short* p_bitdevwk);

#endif
