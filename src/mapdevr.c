#include "macros.h"
#include <stdbool.h>
#include "types/mapdevrwk.h"
#include "mapdevr.h"
static unsigned short mapdevr_getinline(mapdevrwk* p_wk, unsigned short offset, unsigned char bitfield, unsigned char inline_copy_bit_cnt);
static unsigned short mapdevr_masks[16];
static void mapdevr_nextbyte(mapdevrwk* p_wk);


// 00410456
void mapdevr(unsigned short* p_destination, unsigned char* p_source, unsigned short offset) {
  mapdevrwk wk = { p_source };
  unsigned char inline_copy_bit_cnt = *wk.p_source++;
  unsigned char bitfield = *wk.p_source++ << 3;
  unsigned short incremental_copy = *((unsigned short*)wk.p_source) + offset;
  wk.p_source += 2;
  unsigned short literal_copy = *((unsigned short*)wk.p_source) + offset;
  wk.p_source += 2;
  wk.data = *wk.p_source++ << 8;
  wk.data |= *wk.p_source++;
  wk.shift = 16;
  bool done = false;

  do {
    wk.entry_bit_cnt = 7;
    unsigned char entry = (wk.data >> (wk.shift - wk.entry_bit_cnt)) & 0x7F;
    unsigned char type = entry >> 4;
    if (!(entry & 0x40)) {
      wk.entry_bit_cnt = 6;
      entry >>= 1;
    }
    mapdevr_nextbyte(&wk);
    unsigned char repeat_cnt = entry & 0xF;

    switch (type) {
      case 0:
      case 1:
        do {
          *p_destination++ = incremental_copy++;
        } while (repeat_cnt-- != 0);
        break;
      case 2:
      case 3:
        do {
          *p_destination++ = literal_copy;
        } while (repeat_cnt-- != 0);
        break;
      case 4: {
        unsigned short inline_copy = mapdevr_getinline(&wk, offset, bitfield, inline_copy_bit_cnt);

        do {
          *p_destination++ = inline_copy;
        } while (repeat_cnt-- != 0);
        break;
      }
      case 5: {
        unsigned short inline_copy = mapdevr_getinline(&wk, offset, bitfield, inline_copy_bit_cnt);

        do {
          *p_destination++ = inline_copy++;
        } while (repeat_cnt-- != 0);
        break;
      }
      case 6: {
        unsigned short inline_copy = mapdevr_getinline(&wk, offset, bitfield, inline_copy_bit_cnt);

        do {
          *p_destination++ = inline_copy--;
        } while (repeat_cnt-- != 0);
        break;
      }
      case 7:
        if (repeat_cnt == 0xF) {
          done = true;
        }
        else {
          do {
            unsigned short inline_copy = mapdevr_getinline(&wk, offset, bitfield, inline_copy_bit_cnt);
            *p_destination++ = inline_copy;
          } while (repeat_cnt-- != 0);
        }
        break;
    }
  } while (!done);
}


// 004108d4
static unsigned short mapdevr_getinline(mapdevrwk* p_wk, unsigned short offset, unsigned char bitfield, unsigned char inline_copy_bit_cnt) {
  if (bitfield & 0x80) { // priority bit
    --p_wk->shift;
    if (BIT_IS_SET(p_wk->data, p_wk->shift)) {
      offset |= 0x8000;
    }
  }

  if (bitfield & 0x40) { // high palette line bit
    --p_wk->shift;
    if (BIT_IS_SET(p_wk->data, p_wk->shift)) {
      offset += 0x4000;
    }
  }

  if (bitfield & 0x20) { // low palette line bit
    --p_wk->shift;
    if (BIT_IS_SET(p_wk->data, p_wk->shift)) {
      offset += 0x2000;
    }
  }

  if (bitfield & 0x10) { // vertical flip bit
    --p_wk->shift;
    if (BIT_IS_SET(p_wk->data, p_wk->shift)) {
      offset |= 0x1000;
    }
  }

  if (bitfield & 8) { // horizontal flip bit
    --p_wk->shift;
    if (BIT_IS_SET(p_wk->data, p_wk->shift)) {
      offset |= 0x800;
    }
  }

  unsigned short result = p_wk->data;
  signed char shiftwk = p_wk->shift - inline_copy_bit_cnt;
  if (shiftwk < 0) {
    p_wk->shift = shiftwk + 16;
    shiftwk = -shiftwk;
    result <<= shiftwk;
    p_wk->data |= *p_wk->p_source++;
    p_wk->data = (p_wk->data & 0xFF00) | (p_wk->data << shiftwk & 0x00FF) | (p_wk->data & 0x00FF) >> (8 - shiftwk);
    p_wk->data &= mapdevr_masks[shiftwk - 1];
    result += p_wk->data;
LAB_00410b55:
    result &= mapdevr_masks[inline_copy_bit_cnt - 1];
    result += offset;
    p_wk->data |= *p_wk->p_source++;
    p_wk->data <<= 8;
    p_wk->data |= *p_wk->p_source++;
  }
  else if (shiftwk > 0) {
    result >>= shiftwk;
    result &= mapdevr_masks[inline_copy_bit_cnt - 1];
    result += offset;
    p_wk->entry_bit_cnt = inline_copy_bit_cnt;
    mapdevr_nextbyte(p_wk);
  }
  else {
    p_wk->shift = 16;
    goto LAB_00410b55;
  }

  return result;
}


// 00410c6c
static unsigned short mapdevr_masks[16] = {
       1,
       3,
       7,
     0xF,
    0x1F,
    0x3F,
    0x7F,
    0xFF,
   0x1FF,
   0x3FF,
   0x7FF,
   0xFFF,
  0x1FFF,
  0x3FFF,
  0x7FFF,
  0xFFFF
};


// 00410c8e
static void mapdevr_nextbyte(mapdevrwk* p_wk) {
  p_wk->shift -= p_wk->entry_bit_cnt;
  if (p_wk->shift < 9) {
    p_wk->shift += 8;
    p_wk->data <<= 8;
    p_wk->data |= *p_wk->p_source++;
  }
}
