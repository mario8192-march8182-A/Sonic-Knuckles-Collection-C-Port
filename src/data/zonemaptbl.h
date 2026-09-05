#ifndef SKC_ZONEMAPTBL_H
#define SKC_ZONEMAPTBL_H

typedef struct SKC_zonemap {
  unsigned short mapa_col_cnt;
  unsigned short mapb_col_cnt;
  unsigned short mapa_row_cnt;
  unsigned short mapb_row_cnt;
  unsigned short row_offsets[64];
  unsigned char data[];
}
SKC_zonemap;

extern SKC_zonemap* zonemaptbl[24][2];

#endif
