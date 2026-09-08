#ifndef SKC_CGCHANGE_H
#define SKC_CGCHANGE_H

typedef struct SKC_cg_chg_item {
  unsigned char tim;
  unsigned char* cg_ptr;
  unsigned short vram_adr;
  unsigned char chgcnt;
  unsigned char patcnt;
  unsigned char* data_ptr;
}
SKC_cg_chg_item;

typedef struct SKC_cg_chg_data {
  unsigned short cnt;
  SKC_cg_chg_item* items[];
}
SKC_cg_chg_data;

void cg_change(void);
void cg_chg(SKC_cg_chg_data* p_data);
void cg_change_init(void);

#endif
