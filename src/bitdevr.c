#include "bitdevr.h"
#include <stdbool.h>
#include "types/bitdevrcodetableentry.h"
#include "types/bitdevrwork.h"
typedef unsigned char*(*SKC_bitdevr_write_handler)(unsigned char*, SKC_bitdevr_work*);
static unsigned char* process_inline_data(unsigned char* p_source, SKC_bitdevr_work* p_work);
static unsigned char* write_pixels(unsigned char* p_destination, SKC_bitdevr_work* p_work);
static unsigned char* write_xor_pixels(unsigned char* p_destination, SKC_bitdevr_work* p_work);
static unsigned char* build_codetable(unsigned char* p_source, SKC_bitdevr_codetable_entry (*codetable)[256]);


void bitdevr(unsigned char* p_destination, unsigned char* p_source) {
  SKC_bitdevr_write_handler p_write_handler = !(p_source[1] & 0x80) ? &write_pixels : &write_xor_pixels;
  unsigned short pat_cnt = p_source[0] | (p_source[1] & 0x7F) << 8;
  p_source += 2;
  SKC_bitdevr_codetable_entry codetable[256];
  p_source = build_codetable(p_source, &codetable);
  SKC_bitdevr_work work = {
    .buffer = p_source[0] << 8 | p_source[1],
    .row_cnt = pat_cnt * 8,
    .pixel_cnt = 8,
    .shift = 16
  };
  p_source += 2;
  bool done = false;

  do {
    unsigned char code = (work.buffer >> work.shift - 8) & 0xFF;
    if (code >= 0xFC) {
      p_source = process_inline_data(p_source, &work);
    }
    else {
      work.shift -= codetable[code].code_len;
      if (work.shift < 9) {
        work.shift += 8;
        work.buffer <<= 8;
        work.buffer |= *p_source++;
      }
      work.palette_index = codetable[code].palette_index;
      work.index_repeat_cnt = codetable[code].index_repeat_cnt;
    }

    for (int i = 0; i < work.index_repeat_cnt; ++i) {
      work.pixels <<= 4;
      work.pixels |= work.palette_index;
      --work.pixel_cnt;
      if (work.pixel_cnt == 0) {
        p_destination = (*p_write_handler)(p_destination, &work);
        if (work.row_cnt == 0) {
          done = true;
          break;
        }
        work.pixels = 0;
        work.pixel_cnt = 8;
      }
    }
  } while (!done);
}


static unsigned char* process_inline_data(unsigned char* p_source, SKC_bitdevr_work* p_work) {
  p_work->shift -= 6; // inline data signal bits
  if (p_work->shift < 9) {
    p_work->shift += 8;
    p_work->buffer <<= 8;
    p_work->buffer |= *p_source++;
  }
  p_work->shift -= 7; // inline data bits
  p_work->palette_index = p_work->buffer >> p_work->shift & 0x0F;
  p_work->index_repeat_cnt = ((p_work->buffer >> p_work->shift & 0x70) >> 4) + 1;
  if (p_work->shift < 9) {
    p_work->shift += 8;
    p_work->buffer <<= 8;
    p_work->buffer |= *p_source++;
  }
  return p_source;
}


static unsigned char* write_pixels(unsigned char* p_destination, SKC_bitdevr_work* p_work) {
  *p_destination++ = (p_work->pixels & 0xFF000000) >> 24;
  *p_destination++ = (p_work->pixels & 0x00FF0000) >> 16;
  *p_destination++ = (p_work->pixels & 0x0000FF00) >> 8;
  *p_destination++ = p_work->pixels & 0x000000FF;
  --p_work->row_cnt;
  return p_destination;
}


static unsigned char* write_xor_pixels(unsigned char* p_destination, SKC_bitdevr_work* p_work) {
  p_work->prev_pixels ^= p_work->pixels;
  *p_destination++ = (p_work->pixels & 0xFF000000) >> 24;
  *p_destination++ = (p_work->pixels & 0x00FF0000) >> 16;
  *p_destination++ = (p_work->pixels & 0x0000FF00) >> 8;
  *p_destination++ = p_work->pixels & 0x000000FF;
  --p_work->row_cnt;
  return p_destination;
}


static unsigned char* build_codetable(unsigned char* p_source, SKC_bitdevr_codetable_entry (*codetable)[256]) {
  unsigned char data = *p_source++;

  while (data != 0xFF) {
    unsigned char byte1 = data;
    while (!((data = *p_source++) & 0x80)) {
      SKC_bitdevr_codetable_entry entry = {
        .palette_index = byte1 & 0x0F,
        .index_repeat_cnt = ((data & 0x70) >> 4) + 1,
        .code_len = data & 0x0F
      };
      if (entry.code_len == 8) {
        unsigned short code = *p_source++;
        (*codetable)[code] = entry;
      }
      else {
        unsigned char code = *p_source++ << (8 - entry.code_len);
        unsigned short cnt = 1 << (8 - entry.code_len);

        for (int i = 0; i < cnt; ++i) {
          (*codetable)[code] = entry;
          ++code;
        }
      }
    }
  }

  return p_source;
}
