#ifndef WRTINITDATA_H
#define WRTINITDATA_H

typedef struct wrt_init_data {
  unsigned short cnt;
  unsigned short sproffset;
  unsigned short offset_increase;
  unsigned short flg_index;
  signed char** patbase;
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
wrt_init_data;

#endif
