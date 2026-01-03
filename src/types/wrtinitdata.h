#ifndef SKC_WRTINITDATA_H
#define SKC_WRTINITDATA_H

typedef struct SKC_wrt_init_data {
  unsigned short cnt;
  unsigned short sproffset;
  unsigned short sproffset_increase;
  unsigned short flg_index;
  SKC_sprite_pattern** patbase;
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
SKC_wrt_init_data;

#endif
