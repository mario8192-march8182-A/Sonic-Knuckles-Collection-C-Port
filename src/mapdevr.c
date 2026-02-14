#include "mapdevr.h"
#include <stdbool.h>
#include "types/mapdevrwork.h"
#include "utils/bits.h"
static unsigned short get_inline_copy(unsigned char** pp_source, SKC_mapdevr_work* p_work, unsigned short offset, unsigned char bitfield, unsigned char inline_copy_len);
static void prepare_next_entry(unsigned char** pp_source, SKC_mapdevr_work* p_work);


void mapdevr(unsigned short* p_destination, unsigned char* p_source, unsigned short offset) {
  unsigned char inline_copy_len = *p_source++;
  unsigned char bitfield = *p_source++ << 3;
  unsigned short incremental_copy = (p_source[0] | p_source[1] << 8) + offset;
  p_source += 2;
  unsigned short literal_copy = (p_source[0] | p_source[1] << 8) + offset;
  p_source += 2;
  SKC_mapdevr_work work = {
    .buffer = p_source[0] << 8 | p_source[1],
    .shift = 16
  };
  p_source += 2;
  bool done = false;

  do {
    unsigned char entry = work.buffer >> work.shift - work.entry_len & 0x7F;
    unsigned char type = entry & 0x40 ? (entry & 0x70) >> 4 : (entry & 0x60) >> 5;
    unsigned char repeat_cnt = entry & 0x40 ? (entry & 0x0F) + 1 : ((entry & 0x1E) >> 1) + 1;
    work.entry_len = entry & 0x40 ? 7 : 6;
    prepare_next_entry(&p_source, &work);

    switch (type) {
      case 0:
        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = incremental_copy++;
        }
        break;
      case 1:
        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = literal_copy;
        }
        break;
      case 4: {
        unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);

        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = inline_copy;
        }
        break;
      }
      case 5: {
        unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);

        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = inline_copy++;
        }
        break;
      }
      case 6: {
        unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);

        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = inline_copy--;
        }
        break;
      }
      case 7:
        if (repeat_cnt == 0xF) {
          done = true;
        }
        else {
          for (int i = 0; i < repeat_cnt; ++i) {
            unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);
            *p_destination++ = inline_copy;
          }
        }
        break;
    }
  } while (!done);
}


static unsigned short get_inline_copy(unsigned char** pp_source, SKC_mapdevr_work* p_work, unsigned short offset, unsigned char bitfield, unsigned char inline_copy_len) {
#define PRIORITY_BIT 7
#define HIGH_PALETTE_LINE_BIT 6
#define LOW_PALETTE_LINE_BIT 5
#define VERTICAL_FLIP_BIT 4
#define HORIZONTAL_FLIP_BIT 3

  if (BIT_IS_SET(bitfield, PRIORITY_BIT)) {
    --p_work->shift;
    if (BIT_IS_SET(p_work->buffer, p_work->shift)) {
      SET_BIT(offset, 8 + PRIORITY_BIT);
    }
  }
  if (BIT_IS_SET(bitfield, HIGH_PALETTE_LINE_BIT)) {
    --p_work->shift;
    if (BIT_IS_SET(p_work->buffer, p_work->shift)) {
      SET_BIT(offset, 8 + HIGH_PALETTE_LINE_BIT);
    }
  }
  if (BIT_IS_SET(bitfield, LOW_PALETTE_LINE_BIT)) {
    --p_work->shift;
    if (BIT_IS_SET(p_work->buffer, p_work->shift)) {
      SET_BIT(offset, 8 + LOW_PALETTE_LINE_BIT);
    }
  }
  if (BIT_IS_SET(bitfield, VERTICAL_FLIP_BIT)) {
    --p_work->shift;
    if (BIT_IS_SET(p_work->buffer, p_work->shift)) {
      SET_BIT(offset, 8 + VERTICAL_FLIP_BIT);
    }
  }
  if (BIT_IS_SET(bitfield, HORIZONTAL_FLIP_BIT)) {
    --p_work->shift;
    if (BIT_IS_SET(p_work->buffer, p_work->shift)) {
      SET_BIT(offset, 8 + HORIZONTAL_FLIP_BIT);
    }
  }
  unsigned short result = p_work->buffer;
  if (inline_copy_len > p_work->shift) {
    unsigned char shiftwk = inline_copy_len - p_work->shift;
    p_work->shift = 16 - shiftwk;
    result <<= shiftwk;
    p_work->buffer = (p_work->buffer & 0xFF00) | **pp_source;
    p_work->buffer = (p_work->buffer & 0xFF00) | rotate_char_left(p_work->buffer & 0x00FF, shiftwk);
    p_work->buffer &= (1 << shiftwk) - 1;
    result += p_work->buffer;
    result &= (1 << inline_copy_len) - 1;
    result += offset;
    p_work->buffer = *(*pp_source)++;
    p_work->buffer <<= 8;
    p_work->buffer |= *(*pp_source)++;
  }
  else if (p_work->shift > inline_copy_len) {
    unsigned char shiftwk = p_work->shift - inline_copy_len;
    result >>= shiftwk;
    result &= (1 << inline_copy_len) - 1;
    result += offset;
    p_work->entry_len = inline_copy_len;
    prepare_next_entry(pp_source, p_work);
  }
  else {
    p_work->shift = 16;
    result &= (1 << inline_copy_len) - 1;
    result += offset;
    p_work->buffer = *(*pp_source)++;
    p_work->buffer <<= 8;
    p_work->buffer |= *(*pp_source)++;
  }
  return result;
}


static void prepare_next_entry(unsigned char** pp_source, SKC_mapdevr_work* p_work) {
  p_work->shift -= p_work->entry_len;
  if (p_work->shift < 9) {
    p_work->shift += 8;
    p_work->buffer <<= 8;
    p_work->buffer |= *(*pp_source)++;
  }
}
