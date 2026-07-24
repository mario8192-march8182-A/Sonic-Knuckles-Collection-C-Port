#include "dev.h"
#include <stdbool.h>
#include <string.h>
#include "types/bitdevrcodetableentry.h"
#include "types/bitdevrwork.h"
#include "types/mapdevrwork.h"
#include "utils/bits.h"
typedef unsigned char*(*SKC_bitdevr_write_handler)(unsigned char*, SKC_bitdevr_work*);
static unsigned char* process_inline_data(unsigned char* p_source, SKC_bitdevr_work* p_work);
static unsigned char* write_pixels(unsigned char* p_destination, SKC_bitdevr_work* p_work);
static unsigned char* write_xor_pixels(unsigned char* p_destination, SKC_bitdevr_work* p_work);
static unsigned char* build_codetable(unsigned char* p_source, SKC_bitdevr_codetable_entry (*codetable)[256]);
static unsigned short get_inline_copy(unsigned char** pp_source, SKC_mapdevr_work* p_work, unsigned short offset, unsigned char bitfield, unsigned char inline_copy_len);
static void prepare_next_entry(unsigned char** pp_source, SKC_mapdevr_work* p_work);
static unsigned char get_next_bit(unsigned char** pp_source, unsigned short* p_buffer, unsigned char* p_buffer_len);

extern unsigned char g_vram[0x10000];


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


void divdevset(unsigned short id) {
  divdevset2(divdevtbl[id]);
}


void divdevset2(SKC_cg_data* p_data) {
  for (int i = 0; i < p_data->cnt; ++i) {
    bitdevr(&g_vram[p_data->data[i].offset], p_data->data[i].cg_ptr);
  }
}


void copy_map_vram(unsigned char* p_source, unsigned short offset, unsigned short col_cnt, unsigned short row_cnt) {
  unsigned char* p_vram = &g_vram[offset];
  unsigned short size = col_cnt * sizeof(unsigned short);
  unsigned short padding = (64 - col_cnt) * 2;

  for (int row = 0; row < row_cnt; ++row) {
    memcpy(p_vram, p_source, size);
    p_source += size;
    p_vram += size + padding;
  }
}


void copy_map_vram2(unsigned char* p_source, unsigned short offset, unsigned short col_cnt, unsigned short row_cnt) {
  unsigned char* p_vram = &g_vram[offset];
  unsigned short size = col_cnt * sizeof(unsigned short);
  unsigned short padding = (128 - col_cnt) * 2;

  for (int row = 0; row < row_cnt; ++row) {
    memcpy(p_vram, p_source, size);
    p_source += size;
    p_vram += size + padding;
  }
}


void mapdevr(unsigned char* p_destination, unsigned char* p_source, unsigned short offset) {
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
    work.entry_len = 7;
    unsigned char entry = (work.buffer >> (work.shift - work.entry_len)) & 0x7F;
    unsigned char type = entry >> 4;
    if (!(entry & 0x40)) {
      work.entry_len = 6;
      entry >>= 1;
    }
    prepare_next_entry(&p_source, &work);
    unsigned char repeat_cnt = (entry & 0xF) + 1;

    switch (type) {
      case 0:
      case 1:
        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = incremental_copy & 0xFF;
          *p_destination++ = incremental_copy >> 8;
          ++incremental_copy;
        }
        break;
      case 2:
      case 3:
        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = literal_copy & 0xFF;
          *p_destination++ = literal_copy >> 8;
        }
        break;
      case 4: {
        unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);

        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = inline_copy & 0xFF;
          *p_destination++ = inline_copy >> 8;
        }
        break;
      }
      case 5: {
        unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);

        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = inline_copy & 0xFF;
          *p_destination++ = inline_copy >> 8;
          ++inline_copy;
        }
        break;
      }
      case 6: {
        unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);

        for (int i = 0; i < repeat_cnt; ++i) {
          *p_destination++ = inline_copy & 0xFF;
          *p_destination++ = inline_copy >> 8;
          --inline_copy;
        }
        break;
      }
      case 7:
        if (repeat_cnt == 16) {
          done = true;
        }
        else {
          for (int i = 0; i < repeat_cnt; ++i) {
            unsigned short inline_copy = get_inline_copy(&p_source, &work, offset, bitfield, inline_copy_len);
            *p_destination++ = inline_copy & 0xFF;
            *p_destination++ = inline_copy >> 8;
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


unsigned short unlze(unsigned char** pp_destination, unsigned char* p_source) {
  unsigned char* p_source_start = p_source;
  unsigned short buffer = p_source[0] | p_source[1] << 8;
  p_source += 2;
  unsigned char buffer_len = 16;
  bool done = false;

  do {
    unsigned char type = get_next_bit(&p_source, &buffer, &buffer_len);
    if (type == 0) {
      type |= get_next_bit(&p_source, &buffer, &buffer_len) << 1;
    }

    switch (type) {
      case 1:
        *(*pp_destination)++ = *p_source++;
        break;
      case 0: {
        unsigned char repeat_cnt = get_next_bit(&p_source, &buffer, &buffer_len);
        repeat_cnt <<= 1;
        repeat_cnt |= get_next_bit(&p_source, &buffer, &buffer_len);
        repeat_cnt += 2;
        short offset = -256 + *p_source++;

        for (int i = 0; i < repeat_cnt; ++i) {
          unsigned char value = (*pp_destination)[offset];
          *(*pp_destination)++ = value;
        }
        break;
      }
      case 2: {
        unsigned short data = p_source[0] | p_source[1] << 8;
        p_source += 2;
        short offset = (-256 + (short)(data >> 8)) * 32;
        short wk = (unsigned short)offset >> 8;
        wk = (wk & 0x7F) - (wk & 0x80);
        offset = wk * 256 + (short)(data & 0xFF);
        unsigned char repeat_cnt = (data >> 8) & 7;
        if (repeat_cnt == 0) {
          repeat_cnt = *p_source++;

          switch (repeat_cnt) {
            case 0: done = true; break;
            case 1: break;
            default: ++repeat_cnt; break;
          }
        }
        else {
          repeat_cnt += 2;
        }
        if (!done && repeat_cnt != 1) {
          for (int i = 0; i < repeat_cnt; ++i) {
            unsigned char value = (*pp_destination)[offset];
            *(*pp_destination)++ = value;
          }
        }
        break;
      }
    }
  }
  while (!done);

  unsigned short read_byte_cnt = p_source - p_source_start;
  return read_byte_cnt;
}


static unsigned char get_next_bit(unsigned char** pp_source, unsigned short* p_buffer, unsigned char* p_buffer_len) {
  unsigned char bit = *p_buffer & 1;
  *p_buffer >>= 1;
  --*p_buffer_len;
  if (*p_buffer_len == 0) {
    *p_buffer = (*pp_source)[0] | (*pp_source)[1] << 8;
    *pp_source += 2;
    *p_buffer_len = 16;
  }
  return bit;
}


void unlze_moduled(unsigned char* p_destination, unsigned char* p_source) {
  unsigned short size = p_source[0] | p_source[1] << 8;
  if (size != 0) {
    p_source += 2;
    unsigned char module_cnt = size & 0x0FFF ? (size >> 12) + 1 : size >> 12;

    for (int i = 0; i < module_cnt; ++i) {
      unsigned short read_byte_cnt = unlze(&p_destination, p_source);
      if (read_byte_cnt % 16 != 0) {
        read_byte_cnt &= 0xFFF0;
        read_byte_cnt += 16;
      }
      p_source += read_byte_cnt;
    }
  }
}
