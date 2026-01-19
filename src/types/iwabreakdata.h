#ifndef SKC_IWABREAKDATA_H
#define SKC_IWABREAKDATA_H

typedef struct SKC_iwa_break_data {
  unsigned short cnt;
  struct {
    signed char xoffset;
    signed char yoffset;
  }
  data[];
}
SKC_iwa_break_data;

typedef struct SKC_lrz_iwa_break_data {
  unsigned short cnt;
  struct {
    signed char xoffset;
    signed char yoffset;
    unsigned char patno;
  }
  data[];
}
SKC_lrz_iwa_break_data;

#endif
