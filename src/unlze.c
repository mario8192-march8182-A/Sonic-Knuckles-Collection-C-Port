#include <stdbool.h>


// 0041034b
unsigned char* unlze(unsigned char* p_destination, unsigned char* p_source, unsigned short* p_readbyte_cnt) {
  unsigned char* p_sourcestart = p_source;
  unsigned short desc = *((unsigned short*)p_source);
  p_source += 2;
  unsigned char descbit_cnt = 16;
  bool done = false;

  do {
    unsigned char descbit = desc & 1;
    desc >>= 1;
    --descbit_cnt;
    if (descbit_cnt == 0) {
      desc = *((unsigned short*)p_source);
      p_source += 2;
      descbit_cnt = 16;
    }

    if (descbit == 1) {
      *p_destination++ = *p_source++;
      continue;
    }

    descbit = desc & 1;
    desc >>= 1;
    --descbit_cnt;
    if (descbit_cnt == 0) {
      desc = *((unsigned short*)p_source);
      p_source += 2;
      descbit_cnt = 16;
    }

    unsigned long repeat_cnt = 0;
    short offset;
    if (descbit == 0) {
      descbit = desc & 1;
      desc >>= 1;
      --descbit_cnt;
      if (descbit_cnt == 0) {
        desc = *((unsigned short*)p_source);
        p_source += 2;
        descbit_cnt = 16;
      }

      repeat_cnt = ((repeat_cnt << 1) | descbit) & 0xFFFFFFFF;
      descbit = desc & 1;
      desc >>= 1;
      --descbit_cnt;
      if (descbit_cnt == 0) {
        desc = *((unsigned short*)p_source);
        p_source += 2;
        descbit_cnt = 16;
      }

      repeat_cnt = ((repeat_cnt << 1) | descbit) & 0xFFFFFFFF;
      repeat_cnt += 2;
      offset = -256 + *p_source++;
    }
    else {
      unsigned short byte = *((unsigned short*)p_source);
      p_source += 2;
      offset = -256 + (byte >> 8);
      offset *= 32;
      offset = (offset & 0xFF00) | (byte & 0xFF);
      repeat_cnt = (byte >> 8) & 7;
      if (repeat_cnt == 0) {
        repeat_cnt = *p_source++;
        if (repeat_cnt == 0) {
          done = true;
        }
        else if (repeat_cnt == 1) continue;
        ++repeat_cnt;
      }
      else {
        repeat_cnt += 2;
      }
    }

    if (!done) {
      do {
        unsigned char value = p_destination[offset];
        *p_destination++ = value;
      } while (--repeat_cnt != 0);
    }
  }
  while (!done);

  if (p_readbyte_cnt != 0) {
    *p_readbyte_cnt = p_source - p_sourcestart;
  }

  return p_destination;
}


// 004114aa
void unlze_moduled(unsigned char* p_destination, unsigned char* p_source) {
  unsigned short size = *((unsigned short*)p_source);
  if (size == 0) return;

  unsigned char module_cnt;
  if (size & 0xFFF) {
    module_cnt = (size >>= 12) + 1;
  }
  else {
    module_cnt = size >>= 12;
  }

  for (int i = 0; i < module_cnt; ++i) {
    unsigned short readbyte_cnt;
    p_destination = unlze(p_destination, p_source, &readbyte_cnt);
    p_source += readbyte_cnt + (16 - readbyte_cnt / 16);
  }
}
