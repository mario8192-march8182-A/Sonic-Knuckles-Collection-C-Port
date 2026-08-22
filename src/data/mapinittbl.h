#ifndef SKC_MAPINITTBL_H
#define SKC_MAPINITTBL_H

typedef struct SKC_mapinit_data {
  unsigned char ini_cg_no1;
  unsigned char ini_cg_no2;
  unsigned char* cg_data1_ptr;
  unsigned char* cg_data2_ptr;
  unsigned char colorno1;
  unsigned char colorno2;
  unsigned char* blkdata1_ptr;
  unsigned char* blkdata2_ptr;
  unsigned char* mapdata1_ptr;
  unsigned char* mapdata2_ptr;
}
SKC_mapinit_data;

extern SKC_mapinit_data mapinittbl[24][2];

#endif
