#ifndef SKC_BREAK3INITDATA_H
#define SKC_BREAK3INITDATA_H

typedef struct SKC_break3_init_data {
  unsigned short cnt;
  struct {
    signed char xoffset;
    signed char yoffset;
    unsigned char patno;
    unsigned char timer;
  }
  items[];
}
SKC_break3_init_data;

#endif
