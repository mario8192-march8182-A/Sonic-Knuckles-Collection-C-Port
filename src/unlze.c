#include "unlze.h"
#include <stdbool.h>
static unsigned char get_next_bit(unsigned char** pp_source, unsigned short* p_buffer, unsigned char* p_buffer_len);


unsigned short unlze(unsigned char** pp_destination, unsigned char* p_source) {
  unsigned char* p_source_start = p_source;
  unsigned short buffer = p_source[0] | p_source[1] << 8;
  p_source += 2;
  unsigned char buffer_len = 16;
  bool done = false;

  do {
    unsigned char type = get_next_bit(&p_source, &buffer, &buffer_len);
    if (type == 0) {
      type <<= 1;
      type |= get_next_bit(&p_source, &buffer, &buffer_len);
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
        offset -= offset % 256;
        offset += (short)(data & 0x00FF);
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
