#include <stdbool.h>
#include "macros.h"
#include "types/bitdevrwk.h"
#include "bitdevr.h"
static void bitdevr_decompress(bitdevrwk* p_wk, unsigned char* p_bitdevwk, void(*p_write)(unsigned long, bitdevrwk*));
static void bitdevr_decompress_inline(bitdevrwk* p_wk);
static void bitdevr_write(unsigned long pixels, bitdevrwk* p_wk);
static void bitdevr_xorwrite(unsigned long pixels, bitdevrwk* p_wk);
static unsigned char* bitdevr_codetable(unsigned char* p_source, unsigned short* p_bitdevwk);


// 00410d9c
void bitdevr(unsigned long* p_destination, unsigned char* p_source, unsigned char* p_bitdevwk) {
  bitdevrwk wk = { p_destination, p_source };
  void(*p_write)(unsigned long, bitdevrwk*) = &bitdevr_write;
  unsigned short patcnt = *((unsigned short*)wk.p_source);
  wk.p_source += 2;
  bool xor_mode = patcnt & 0x8000;
  if (xor_mode) {
    p_write = &bitdevr_xorwrite;
  }
  wk.row_cnt = patcnt << 3;
  wk.pixel_cnt = 8;
  wk.p_source = bitdevr_codetable(wk.p_source, (unsigned short*)p_bitdevwk);

  wk.data = *wk.p_source++ << 8;
  wk.data |= *wk.p_source++;
  wk.shift = 16;
  bitdevr_decompress(&wk, p_bitdevwk, p_write);
}


// 00410eaa
static void bitdevr_decompress(bitdevrwk* p_wk, unsigned char* p_bitdevwk, void(*p_write)(unsigned long, bitdevrwk*)) {
  bool done = false;

  do {
    unsigned short code = p_wk->data >> p_wk->shift - 8;
    if (code >= 252) {
      bitdevr_decompress_inline(p_wk);
    }
    else {
      code = (code & 0xFF) * 2;
      unsigned char codebits_cnt = p_bitdevwk[code + 1];
      p_wk->shift -= codebits_cnt;
      if (p_wk->shift < 9) {
        p_wk->shift += 8;
        p_wk->data <<= 8;
        p_wk->data |= *p_wk->p_source++;
      }
      p_wk->palette_index = p_bitdevwk[code] & 0xF;
      p_wk->index_repeatcnt = (p_bitdevwk[code] & 0xF0) >> 4;
    }

    unsigned long pixels = 0;
    do {
      pixels <<= 4;
      pixels |= p_wk->palette_index;
      --p_wk->pixel_cnt;
      if (p_wk->pixel_cnt == 0) {
        (*p_write)(pixels, p_wk);
        if (p_wk->row_cnt == 0) {
          done = true;
          break;
        }
        pixels = 0;
        p_wk->pixel_cnt = 8;
      }
    } while (p_wk->index_repeatcnt-- != 0);
  } while (!done);
}


static void bitdevr_decompress_inline(bitdevrwk* p_wk) {
  p_wk->shift -= 6; // inline data signal bits
  if (p_wk->shift < 9) {
    p_wk->shift += 8;
    p_wk->data <<= 8;
    p_wk->data |= *p_wk->p_source++;
  }
  p_wk->shift -= 7; // inline data bits
  p_wk->palette_index = p_wk->data >> p_wk->shift & 0xF;
  p_wk->index_repeatcnt = (p_wk->data >> p_wk->shift & 0x70) >> 4;
  if (p_wk->shift < 9) {
    p_wk->shift += 8;
    p_wk->data <<= 8;
    p_wk->data |= *p_wk->p_source++;
  }
}


// 004111cf
static void bitdevr_write(unsigned long pixels, bitdevrwk* p_wk) {
  BYTESWAP(pixels);
  *p_wk->p_destination++ = pixels;
  --p_wk->row_cnt;
}


// 0041120a
static void bitdevr_xorwrite(unsigned long pixels, bitdevrwk* p_wk) {
  p_wk->prev_pixels ^= pixels;
  BYTESWAP(pixels);
  *p_wk->p_destination++ = pixels;
  --p_wk->row_cnt;
}


// 00411257
static unsigned char* bitdevr_codetable(unsigned char* p_source, unsigned short* p_bitdevwk) {
  unsigned short data = *p_source++;
  while (data != 255) {
    unsigned short byte1 = data;
    while (!((data = *p_source++) & 0x80)) {
      unsigned char byte2 = data;
      unsigned char palette_index = byte1 & 0xF;
      unsigned char indexrepeat_cnt = (byte2 & 0x70) >> 4;
      unsigned char codebits_cnt = byte2 & 0xF;
      unsigned short codetable_entry = codebits_cnt << 8 | indexrepeat_cnt << 4 | palette_index;
      if (codebits_cnt == 8) {
        unsigned short code = *p_source++;
        p_bitdevwk[code] = codetable_entry;
      }
      else {
        unsigned short code = *p_source++ << 8 - codebits_cnt;
        unsigned short cnt = 1 << 8 - codebits_cnt;
        do {
          p_bitdevwk[code++] = codetable_entry;
        } while (--cnt != 0);
      }
    }
  }

  return p_source;
}
