#include "cgchange.h"
#include <string.h>
#include "data/waterline0100tbl.h"
#include "data/waterline0601tbl.h"
#include "data/cg/zone00/cgchg.h"
#include "data/cg/zone01/cgchg.h"
#include "data/cg/zone02/cgchg.h"
#include "data/cg/zone03/cgchg.h"
#include "data/cg/zone04/cgchg.h"
#include "data/cg/zone05/cgchg.h"
#include "data/cg/zone06/cgchg.h"
#include "data/cg/zone07/cgchg.h"
#include "data/cg/zone08/cgchg.h"
#include "data/cg/zone09/cgchg.h"
#include "data/cg/zone0a/cgchg.h"
#include "data/cg/zone0b/cgchg.h"
#include "data/cg/zone0e/cgchg.h"
#include "data/cg/zone0f/cgchg.h"
#include "data/cg/zone10/cgchg.h"
#include "data/cg/zone13/cgchg.h"
#include "data/cg/zone14/bg.h"
#include "data/cg/zone14/cgchg.h"
#include "data/cg/zone16/cgchg.h"
#include "types/sonic3ram.h"
#include "utils/stageno.h"
#include "dev.h"
static void worknai(SKC_cg_chg_data* p_data);
static void cg_chg_0000(SKC_cg_chg_data* p_data);
static void cg_chg_0001(SKC_cg_chg_data* p_data);
static void cg_chg_0100(SKC_cg_chg_data* p_data);
static void waterline0100_cg_chg(SKC_cg_chg_data* p_data);
static void restore_above_waterline0100(void);
static void restore_below_waterline0100(void);
static void waterline0100_cg_chg_init(void);
static void cg_chg_0101(SKC_cg_chg_data* p_data);
static void cg_chg_02(SKC_cg_chg_data* p_data);
static void cg_chg_03(SKC_cg_chg_data* p_data);
static void cg_chg_05(SKC_cg_chg_data* p_data);
static void cg_chg_0600(SKC_cg_chg_data* p_data);
static void cg_chg_0601(SKC_cg_chg_data* p_data);
static void waterline0601_cg_chg(void);
static void restore_below_waterline0601(void);
static void restore_above_waterline0601(void);
static void waterline0601_cg_chg_init(void);
static void cg_chg_07(SKC_cg_chg_data* p_data);
static void cg_chg_0800(SKC_cg_chg_data* p_data);
static void cg_chg_0801(SKC_cg_chg_data* p_data);
static void cg_chg_1600(SKC_cg_chg_data* p_data);
static void cg_chg_0900(SKC_cg_chg_data* p_data);
static void cg_chg_0901(SKC_cg_chg_data* p_data);
static void cg_chg_09(SKC_cg_chg_data* p_data, unsigned short vram_adr0, unsigned short vram_adr1);
static void cg_chg_10(SKC_cg_chg_data* p_data);
static void cg_chg_13(SKC_cg_chg_data* p_data);
static void cg_chg_14(SKC_cg_chg_data* p_data);
static void FUN_0044c42b(void);
static void cg_chg_def(SKC_cg_chg_data* p_data);
static void cg_chg0(SKC_cg_chg_data* p_data, unsigned char* p_cgchgtim, unsigned char* p_cgchgcnt);
static void cg_chg1(SKC_cg_chg_item* p_item, unsigned char* p_cgchgtim, unsigned char* p_cgchgcnt);
static SKC_cg_chg_data cg_chg_0000_tbl;
static SKC_cg_chg_data cg_chg_0001_tbl;
static SKC_cg_chg_data cg_chg_0100_tbl;
static SKC_cg_chg_data cg_chg_0101_tbl;
static SKC_cg_chg_data cg_chg_02_tbl;
static SKC_cg_chg_data cg_chg_03_tbl;
static SKC_cg_chg_data cg_chg_0400_tbl;
static SKC_cg_chg_data cg_chg_0401_tbl;
static SKC_cg_chg_data cg_chg_05_tbl;
static SKC_cg_chg_data cg_chg_0600_00_tbl;
static SKC_cg_chg_data cg_chg_0600_01_tbl;
static SKC_cg_chg_data cg_chg_0601_tbl;
static SKC_cg_chg_data cg_chg_07_tbl;
static SKC_cg_chg_data cg_chg_0900_tbl;
static SKC_cg_chg_data cg_chg_0901_tbl;
static SKC_cg_chg_data cg_chg_0a_tbl;
static SKC_cg_chg_data cg_chg_0b_tbl;
static SKC_cg_chg_data cg_chg_0e_tbl;
static SKC_cg_chg_data cg_chg_0f_tbl;
static SKC_cg_chg_data cg_chg_10_tbl;
static SKC_cg_chg_data cg_chg_14_tbl;
static SKC_cg_chg_data cg_chg_none_tbl;
static SKC_cg_chg_data cg_chg_1601_tbl;

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void cg_change(void) {
  struct {
    void(*r_ptr)(SKC_cg_chg_data*);
    SKC_cg_chg_data* cg_chg_tbl_ptr;
  }
  tbl[24][2] = {
    { { &cg_chg_0000, &cg_chg_0000_tbl    }, { &cg_chg_0001, &cg_chg_0001_tbl } },
    { { &cg_chg_0100, &cg_chg_0100_tbl    }, { &cg_chg_0101, &cg_chg_0101_tbl } },
    { { &cg_chg_02,   &cg_chg_02_tbl      }, { &cg_chg_02,   &cg_chg_02_tbl   } },
    { { &cg_chg_03,   &cg_chg_03_tbl      }, { &cg_chg_03,   &cg_chg_03_tbl   } },
    { { &cg_chg_def,  &cg_chg_0400_tbl    }, { &cg_chg_def,  &cg_chg_0401_tbl } },
    { { &cg_chg_05,   &cg_chg_05_tbl      }, { &cg_chg_05,   &cg_chg_05_tbl   } },
    { { &cg_chg_0600, &cg_chg_0600_00_tbl }, { &cg_chg_0601, &cg_chg_0601_tbl } },
    { { &cg_chg_07,   &cg_chg_07_tbl      }, { &cg_chg_07,   &cg_chg_07_tbl   } },
    { { &cg_chg_0800, &cg_chg_0900_tbl    }, { &cg_chg_0801, &cg_chg_0900_tbl } },
    { { &cg_chg_0900, &cg_chg_0900_tbl    }, { &cg_chg_0901, &cg_chg_0901_tbl } },
    { { &cg_chg_def,  &cg_chg_0a_tbl      }, { &worknai,     &cg_chg_0a_tbl   } },
    { { &cg_chg_def,  &cg_chg_0b_tbl      }, { &cg_chg_def,  &cg_chg_0b_tbl   } },
    { { &worknai,     &cg_chg_0e_tbl      }, { &worknai,     &cg_chg_0e_tbl   } },
    { { &worknai,     &cg_chg_0e_tbl      }, { &worknai,     &cg_chg_0e_tbl   } },
    { { &cg_chg_def,  &cg_chg_0e_tbl      }, { &cg_chg_def,  &cg_chg_0e_tbl   } },
    { { &cg_chg_def,  &cg_chg_0f_tbl      }, { &cg_chg_def,  &cg_chg_0f_tbl   } },
    { { &cg_chg_10,   &cg_chg_10_tbl      }, { &cg_chg_10,   &cg_chg_10_tbl   } },
    { { &worknai,     &cg_chg_none_tbl    }, { &worknai,     &cg_chg_none_tbl } },
    { { &worknai,     &cg_chg_none_tbl    }, { &worknai,     &cg_chg_none_tbl } },
    { { &cg_chg_13,   &cg_chg_none_tbl    }, { &cg_chg_13,   &cg_chg_none_tbl } },
    { { &cg_chg_14,   &cg_chg_14_tbl      }, { &cg_chg_14,   &cg_chg_14_tbl   } },
    { { &worknai,     &cg_chg_none_tbl    }, { &worknai,     &cg_chg_none_tbl } },
    { { &cg_chg_1600, &cg_chg_none_tbl    }, { &cg_chg_def,  &cg_chg_1601_tbl } },
    { { &worknai,     0                   }, { &cg_chg_def,  &cg_chg_1601_tbl } }
  };

  SKC_cg_chg_data* p_data = tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)].cg_chg_tbl_ptr;
  tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)].r_ptr(p_data);
}


static void worknai(SKC_cg_chg_data* p_data) {
}


static void cg_chg_0000(SKC_cg_chg_data* p_data) {
  if (g_ram.bossstart != 0) return;
  if (g_ram.zone_flag == 0) return;

  cg_chg(p_data);
}


static void cg_chg_0001(SKC_cg_chg_data* p_data) {
  if (g_ram.bossstart != 0) return;

  if (g_ram.scra_h_posit >> 16 >= 448) {
    cg_chg(p_data);
  }
  else {
    cg_chg1(p_data->items[0], &g_ram.cgchgtim[0], &g_ram.cgchgcnt[0]);
    g_ram.cgchgtim[0] = 0;
    g_ram.cgchgtim[2] = 0;
    memcpy(&g_vram[0x1940], cg_chg_0001_05_cg, 1120);
  }
}


static void cg_chg_0100(SKC_cg_chg_data* p_data) {
  if (g_ram.DAT_08ffeee8 != 0) return;

  waterline0100_cg_chg(p_data);
}


static void waterline0100_cg_chg(SKC_cg_chg_data* p_data) {
  if (g_ram.DAT_08ffeee2 != g_ram.waterlinecgchgcnt[0]) {
    g_ram.waterlinecgchgcnt[0] = g_ram.DAT_08ffeee2;
    if (g_ram.DAT_08ffeee2 != 0) {
      if (g_ram.DAT_08ffeee2 < 0) {
        short wk = g_ram.DAT_08ffeee2 + 96;
        if (wk >= 0) {
          for (int i = 0; i < 96; ++i) {
            unsigned char* p_vram = &g_vram[0x5B80 + i * 4];
            unsigned char* p_cg = &waterline0100_below_cg[waterline0100_tbl[wk][i] * 4];
            memcpy(&p_vram[0], &p_cg[0], 4);
            memcpy(&p_vram[0x180], &p_cg[0x600], 4);
          }

          if (g_ram.waterlinecgchgcnt[1] >= 0) {
            g_ram.waterlinecgchgcnt[1] = -1;
            restore_below_waterline0100();
          }
        }
      }
      else {
        short wk = -g_ram.DAT_08ffeee2 + 96;
        if (wk >= 0) {
          for (int i = 0; i < 96; ++i) {
            unsigned char* p_vram = &g_vram[0x5E80 + i * 4];
            unsigned char* p_cg = &waterline0100_below_cg[waterline0100_tbl[wk][i] * 4];
            memcpy(&p_vram[0], &p_cg[0], 4);
            memcpy(&p_vram[0x180], &p_cg[0x600], 4);
          }

          if (g_ram.waterlinecgchgcnt[1] != 0) {
            g_ram.waterlinecgchgcnt[1] = 0;
            restore_above_waterline0100();
          }
        }
      }
    }
    else {
      g_ram.waterlinecgchgcnt[0] = 1;
      restore_below_waterline0100();
      restore_above_waterline0100();
      return;
    }
  }
  cg_chg(p_data);
}


static void restore_above_waterline0100(void) {
  memcpy(&g_vram[0x5B80], above_waterline0100_cg, sizeof(above_waterline0100_cg));
  memcpy(&g_vram[0x5D00], above_waterline0100_cg2, sizeof(above_waterline0100_cg2));
}


static void restore_below_waterline0100(void) {
  memcpy(&g_vram[0x5E80], below_waterline0100_cg, sizeof(below_waterline0100_cg));
  memcpy(&g_vram[0x6000], below_waterline0100_cg2, sizeof(below_waterline0100_cg2));
}


static void waterline0100_cg_chg_init(void) {
  if (g_ram.DAT_08ffeee2 != 0) {
    if (g_ram.DAT_08ffeee2 < 0) {
      if (g_ram.DAT_08ffeee2 + 96 >= 0) {
        restore_below_waterline0100();
        waterline0100_cg_chg(&cg_chg_0100_tbl);
      }
      else {
        restore_below_waterline0100();
        memcpy(&g_vram[0x5B80], waterline0100_below_cg, sizeof(waterline0100_below_cg));
        memcpy(&g_vram[0x5D00], waterline0100_below_cg2, sizeof(waterline0100_below_cg2));
      }
    }
    else {
      if (-g_ram.DAT_08ffeee2 + 96 >= 0) {
        restore_above_waterline0100();
        waterline0100_cg_chg(&cg_chg_0100_tbl);
      }
      else {
        restore_above_waterline0100();
        memcpy(&g_vram[0x5E80], waterline0100_above_cg, sizeof(waterline0100_above_cg));
        memcpy(&g_vram[0x6000], waterline0100_above_cg2, sizeof(waterline0100_above_cg2));
      }
    }
  }
  else {
    g_ram.waterlinecgchgcnt[0] = 1;
    restore_below_waterline0100();
    restore_above_waterline0100();
  }
}


static void cg_chg_0101(SKC_cg_chg_data* p_data) {
  unsigned char cnt = g_ram.DAT_08ffeee4 & 0x1F;
  if (cnt != g_ram.cgchgcnt[0]) {
    unsigned short size_tbl[4][2] = {
      { 64,  0 },
      { 48, 16 },
      { 32, 32 },
      { 16, 48 }
    };

    g_ram.cgchgcnt[0] = cnt;
    unsigned char* p_vram = &g_vram[0x5A40];
    unsigned char* p_source = &cg_chg_0101_01_cg[(cnt & 7) * 128 + (cnt & 0x18) * 4];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_0101_01_cg[(cnt & 7) * 128];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  if (cnt != g_ram.cgchgcnt[1]) {
    unsigned short size_tbl[4][2] = {
      { 128,  0 },
      {  96, 32 },
      {  64, 64 },
      {  32, 96 }
    };

    g_ram.cgchgcnt[1] = cnt;
    unsigned char* p_vram = &g_vram[0x5AC0];
    unsigned char* p_source = &cg_chg_0101_02_cg[(cnt & 7) * 256 + (cnt & 0x18) * 8];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_0101_02_cg[(cnt & 7) * 256];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  cnt = g_ram.DAT_08ffeee6 & 0x1F;
  if (cnt != g_ram.cgchgcnt[2]) {
    unsigned short size_tbl[4][2] = {
      { 256,   0 },
      { 192,  64 },
      { 128, 128 },
      {  64, 192 }
    };

    g_ram.cgchgcnt[2] = cnt;
    unsigned char* p_vram = &g_vram[0x5BC0];
    unsigned char* p_source = &cg_chg_0101_03_cg[(cnt & 7) * 512 + (cnt & 0x18) * 16];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_0101_03_cg[(cnt & 7) * 256];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  cnt = g_ram.DAT_08ffeee6 & 0x3F;
  if (cnt != g_ram.cgchgcnt[3]) {
    unsigned short size_tbl[8][2] = {
      { 768,   0 },
      { 672,  96 },
      { 576, 192 },
      { 480, 288 },
      { 384, 384 },
      { 288, 480 },
      { 192, 576 },
      {  96, 672 }
    };

    g_ram.cgchgcnt[3] = cnt;
    unsigned char* p_vram = &g_vram[0x5DC0];
    unsigned char* p_source = &cg_chg_0101_04_cg[((~cnt + 1) & 7) * 1536 + (cnt - 1 & 0x38) * 8];
    unsigned short* p_size = size_tbl[(cnt - 1 & 0x38) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_0101_04_cg[((~cnt + 1) & 7) * 1536];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  cg_chg0(p_data, &g_ram.cgchgtim[4], &g_ram.cgchgcnt[4]);
}


static void cg_chg_02(SKC_cg_chg_data* p_data) {
  if (g_ram.bossstart != 0) return;

  cg_chg(p_data);
}


static void cg_chg_03(SKC_cg_chg_data* p_data) {
  unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee2 - (g_ram.scrb_h_posit >> 16)) & 0x3F;
  if (cnt != g_ram.cgchgcnt[0]) {
    unsigned short size_tbl[8][2] = {
      { 512,   0 },
      { 448,  64 },
      { 384, 128 },
      { 320, 192 },
      { 256, 256 },
      { 192, 320 },
      { 128, 384 },
      {  64, 448 }
    };

    g_ram.cgchgcnt[0] = cnt;
    unsigned char* p_vram = &g_vram[0x6100];
    unsigned char* p_source = &cg_chg_03_07_cg[(cnt & 7) * 1024 + (cnt & 0x38) * 16];
    unsigned short* p_size = size_tbl[(cnt & 0x38) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_03_07_cg[(cnt & 7) * 1024];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  cg_chg0(p_data, &g_ram.cgchgtim[1], &g_ram.cgchgcnt[1]);
}


static void cg_chg_05(SKC_cg_chg_data* p_data) {
  unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee2 - (g_ram.scrb_h_posit >> 16)) & 0x1F;
  if (cnt != g_ram.cgchgcnt[0]) {
    unsigned short size_tbl[4][2] = {
      { 256,   0 },
      { 192,  64 },
      { 128, 128 },
      {  64, 192 }
    };

    g_ram.cgchgcnt[0] = cnt;
    unsigned char* p_vram = &g_vram[0x21C0];
    unsigned char* p_source = &cg_chg_05_01_cg[(cnt & 7) * 512 + (cnt & 0x18) * 16];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_05_01_cg[(cnt & 7) * 512];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  if (get_act(g_ram.stageno) == ACT_1) {
    cnt = (unsigned short)-((g_ram.scrb_v_posit >> 16) - g_ram.DAT_08ffeee4) & 0x3F;
    if (cnt != g_ram.cgchgcnt[1]) {
      g_ram.cgchgcnt[1] = cnt;
      memcpy(&g_vram[0x2440], &cg_chg_05_02_cg[cnt * 4], 256);
      cnt = (unsigned short)-((g_ram.scrb_v_posit >> 16) - g_ram.DAT_08ffeee4 / 2 - g_ram.DAT_08ffeee4 / 4) & 0x1F;
      memcpy(&g_vram[0x2540], &cg_chg_05_03_cg[cnt * 4], 128);
      cnt = (unsigned short)-((g_ram.scrb_v_posit >> 16) - g_ram.DAT_08ffeee4 / 2) & 0x0F;
      memcpy(&g_vram[0x25C0], &cg_chg_05_04_cg[cnt * 4], 64);
      cnt = (unsigned short)-((g_ram.scrb_v_posit >> 16) - g_ram.DAT_08ffeee4 / 4) & 0x07;
      memcpy(&g_vram[0x2600], &cg_chg_05_05_cg[cnt * 4], 32);
    }
  }
  cg_chg0(p_data, &g_ram.cgchgtim[2], &g_ram.cgchgcnt[2]);
}


static void cg_chg_0600(SKC_cg_chg_data* p_data) {
  if (g_ram.cgchgtim[0]-- == 0) {
    g_ram.cgchgtim[0] = 3;
    ++g_ram.cgchgcnt[0];
    g_ram.cgchgcnt[0] &= 0xF;
    memcpy(&g_vram[0x2C00], &cg_chg_0600_01_cg[g_ram.cgchgcnt[0] * 512], 512);
  }
  unsigned char cnt = g_ram.DAT_08ffeee2 - (g_ram.scrb_h_posit >> 16) & 0x1F;
  if (cnt != g_ram.cgchgcnt[1]) {
    unsigned short size_tbl[4][2] = {
      { 320,   0 },
      { 240,  80 },
      { 160, 160 },
      {  80, 240 }
    };

    g_ram.cgchgcnt[1] = cnt;
    unsigned char* p_vram = &g_vram[0x6A00];
    unsigned char* p_source = &cg_chg_0600_02_cg[(cnt & 7) * 640 + (cnt & 0x18) * 5];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_0600_02_cg[(cnt & 7) * 640];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
    p_vram += p_size[1] * 2;
    p_source = &cg_chg_0600_03_cg[(cnt & 7) * 32];
    memcpy(p_vram, p_source, 32);
  }
  unsigned char* p_cgchgtim = &g_ram.cgchgtim[3];
  unsigned char* p_cgchgcnt = &g_ram.cgchgcnt[3];
  if (g_ram.cgchgtim[2] == 0 && g_ram.cgchgcnt[2] == 0) {
    if (g_ram.cgchgcnt[3] != 1) {
      *p_cgchgtim = 0;
      *p_cgchgcnt = 0;
    }
    else {
      p_cgchgtim = &g_ram.cgchgtim[6];
      p_cgchgcnt = &g_ram.cgchgcnt[6];
      p_data = &cg_chg_0600_01_tbl;
    }
  }
  cg_chg0(p_data, &g_ram.cgchgtim[3], &g_ram.cgchgcnt[3]);
}


static void cg_chg_0601(SKC_cg_chg_data* p_data) {
  if (g_ram.cgchgcnt[7] == 0) {
    if (g_ram.cgchgtim[0]-- == 0) {
      g_ram.cgchgtim[0] = 3;
      memcpy(&g_vram[0x2C00], &cg_chg_0600_01_cg[g_ram.cgchgcnt[0] * 512], 512);
      ++g_ram.cgchgcnt[0];
      g_ram.cgchgcnt[0] &= 0xF;
    }
    unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee4 - (g_ram.scrb_h_posit >> 16)) & 0x0F;
    if (cnt != g_ram.cgchgcnt[1]) {
      g_ram.cgchgcnt[1] = cnt;
      memcpy(&g_vram[0x5C60], &cg_chg_0601_02_cg[cnt * 64], 64);
    }
    waterline0601_cg_chg();
    cg_chg0(p_data, &g_ram.cgchgtim[4], &g_ram.cgchgcnt[4]);
  }
  waterline0601_cg_chg();
}


static void waterline0601_cg_chg(void) {
  if (g_ram.DAT_08ffeee2 != g_ram.waterlinecgchgcnt[0]) {
    g_ram.waterlinecgchgcnt[0] = g_ram.DAT_08ffeee2;
    if (g_ram.DAT_08ffeee2 != 0) {
      if (g_ram.DAT_08ffeee2 < 0) {
        short wk = g_ram.DAT_08ffeee2 + 64;
        if (wk >= 0) {
          for (int i = 0; i < 64; ++i) {
            unsigned char* p_vram = &g_vram[0x5860 + i * 4];
            unsigned char* p_cg = &waterline0601_below_cg[waterline0601_tbl[wk][i] * 4];
            memcpy(&p_vram[0], &p_cg[0], 4);
            memcpy(&p_vram[0x100], &p_cg[0x100], 4);
          }

          if (g_ram.waterlinecgchgcnt[1] != 0) {
            g_ram.waterlinecgchgcnt[1] = 0;
            restore_above_waterline0601();
          }
        }
      }
      else {
        short wk = -g_ram.DAT_08ffeee2 + 64;
        if (wk >= 0) {
          for (int i = 0; i < 64; ++i) {
            unsigned char* p_vram = &g_vram[0x5E80 + i * 4];
            unsigned char* p_cg = &waterline0601_above_cg[waterline0100_tbl[wk][i] * 4];
            memcpy(&p_vram[0], &p_cg[0], 4);
            memcpy(&p_vram[0x100], &p_cg[0x100], 4);
          }

          if (g_ram.waterlinecgchgcnt[1] >= 0) {
            g_ram.waterlinecgchgcnt[1] = -1;
            restore_below_waterline0601();
          }
        }
      }
    }
    else {
      g_ram.waterlinecgchgcnt[1] = 1;
      restore_above_waterline0601();
      restore_below_waterline0601();
    }
  }
}


static void restore_below_waterline0601(void) {
  memcpy(&g_vram[0x5860], below_waterline0601_cg, sizeof(below_waterline0601_cg));
}


static void restore_above_waterline0601(void) {
  memcpy(&g_vram[0x5A60], above_waterline0601_cg, sizeof(above_waterline0601_cg));
}


static void waterline0601_cg_chg_init(void) {
  g_ram.waterlinecgchgcnt[1] = 1;
  if (g_ram.DAT_08ffeee2 != 0) {
    if (g_ram.DAT_08ffeee2 < 0) {
      restore_above_waterline0601();
      memcpy(&g_vram[0x5860], waterline0601_below_cg, sizeof(waterline0601_below_cg));
      waterline0601_cg_chg();
    }
    else {
      restore_below_waterline0601();
      waterline0601_cg_chg();
    }
  }
  else {
    g_ram.waterlinecgchgcnt[1] = 1;
    restore_above_waterline0601();
    restore_below_waterline0601();
  }
}


static void cg_chg_07(SKC_cg_chg_data* p_data) {
  unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee4 - (g_ram.scrb_h_posit >> 16)) & 0x1F;
  if (cnt != g_ram.cgchgcnt[0]) {
    unsigned short size_tbl[4][2] = {
      { 128,  0 },
      {  96, 32 },
      {  64, 64 },
      {  32, 96 }
    };

    g_ram.cgchgcnt[0] = cnt;
    unsigned char* p_vram = &g_vram[0x3700];
    unsigned char* p_source = &cg_chg_07_04_cg[(cnt & 7) * 256 + (cnt & 0x18) * 8];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_07_04_cg[(cnt & 7) * 256];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  cnt = (unsigned short)(g_ram.DAT_08ffeee2 - (g_ram.scrb_h_posit >> 16)) & 0x3F;
  if (cnt != g_ram.cgchgcnt[1]) {
    unsigned short size_tbl[8][2] = {
      { 512,   0 },
      { 448,  64 },
      { 384, 128 },
      { 320, 192 },
      { 256, 256 },
      { 192, 320 },
      { 128, 384 },
      {  64, 448 }
    };

    g_ram.cgchgcnt[1] = cnt;
    unsigned char* p_vram = &g_vram[0x3AA0];
    unsigned char* p_source = &cg_chg_07_05_cg[(cnt & 7) * 512 + (cnt & 0x38) * 16];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_07_05_cg[(cnt & 7) * 512];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  g_ram.cgchgcnt[7] += 2;
  if (g_ram.cgchgcnt[7] >= 88) {
    g_ram.cgchgcnt[7] = 0;
  }
  cg_chg0(p_data, &g_ram.cgchgtim[2], &g_ram.cgchgcnt[2]);
}


static void cg_chg_0800(SKC_cg_chg_data* p_data) {
  unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee2 - (g_ram.scrb_h_posit >> 16)) & 0x1F;
  if (cnt != g_ram.cgchgcnt[0]) {
    unsigned short size_tbl[4][2] = {
      { 192,   0 },
      { 144,  48 },
      {  96,  96 },
      {  48, 144 }
    };

    g_ram.cgchgcnt[0] = cnt;
    unsigned char* p_vram = &g_vram[0x6600];
    unsigned char* p_source = &cg_chg_08_00_cg[(cnt & 7) * 384 + (cnt & 0x18) * 12];
    unsigned short* p_size = size_tbl[(cnt & 0x18) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_08_00_cg[(cnt & 7) * 384];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
    memcpy(&g_vram[0x6780], &cg_chg_08_01_cg[g_ram.cgchgcnt[0] * 192], 192);
  }
}


static void cg_chg_0801(SKC_cg_chg_data* p_data) {
  if (g_ram.cgchgtim[0]-- == 0) {
    g_ram.cgchgtim[0] = 7;

    unsigned short cnt = (g_ram.clchgcnt4 & 6) + (g_ram.clchgcnt4 & 6) / 2;
    if (cnt != 6) {
      cnt += g_ram.cgchgcnt[0];
    }
    memcpy(&g_vram[0x6600], &cg_chg_08_02_cg[cnt * 192], 192);
    if (g_ram.cgchgcnt[0]++ >= 2) {
      g_ram.cgchgcnt[0] = 0;
    }
  }
}


static void cg_chg_1600(SKC_cg_chg_data* p_data) {
  cg_chg_09(p_data, 0x2E00, 0x3280);
}


static void cg_chg_0900(SKC_cg_chg_data* p_data) {
  cg_chg_09(p_data, 0x6400, 0x6880);
}


static void cg_chg_0901(SKC_cg_chg_data* p_data) {
  cg_chg_09(p_data, 0x6400, 0x6880);
}


static void cg_chg_09(SKC_cg_chg_data* p_data, unsigned short vram_adr0, unsigned short vram_adr1) {
  unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee4 - (g_ram.scrb_h_posit >> 16) - 1) % 48;
  if (cnt != g_ram.cgchgcnt[0]) {
    unsigned short size_tbl[6][2] = {
      { 576,   0 },
      { 480,  96 },
      { 384, 192 },
      { 288, 288 },
      { 192, 384 },
      {  96, 480 }
    };

    g_ram.cgchgcnt[0] = cnt;
    unsigned char* p_vram = &g_vram[vram_adr0];
    unsigned char* p_source = &cg_chg_09_00_cg[(cnt & 7) * 1152 + (cnt & 0x38) * 9];
    unsigned short* p_size = size_tbl[(cnt & 0x38) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_09_00_cg[(cnt & 7) * 1152];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  if (get_zone(g_ram.stageno) != LAVA_REEF_BOSS_AND_HIDDEN_PALACE) {
    cnt = (unsigned short)(g_ram.DAT_08ffeee2 - (g_ram.scrb_h_posit >> 16)) & 0x1F;
    if (cnt != g_ram.cgchgcnt[1]) {
      unsigned short size_tbl[4][2] = {
        { 192,   0 },
        { 144,  48 },
        {  96,  96 },
        {  48, 144 }
      };

      g_ram.cgchgcnt[1] = cnt;
      unsigned char* p_vram = &g_vram[vram_adr1];
      unsigned char* p_source = &cg_chg_09_01_cg[(cnt & 7) * 384 + (cnt & 0x18) * 12];
      unsigned short* p_size = size_tbl[(cnt & 0x38) >> 3];
      memcpy(p_vram, p_source, p_size[0] * 2);
      if (p_size[1] != 0) {
        p_vram += p_size[0] * 2;
        p_source = &cg_chg_09_01_cg[(cnt & 7) * 384];
        memcpy(p_vram, p_source, p_size[1] * 2);
      }
    }
    cg_chg0(p_data, &g_ram.cgchgtim[2], &g_ram.cgchgcnt[2]);
  }
}


static void cg_chg_10(SKC_cg_chg_data* p_data) {
  unsigned short size_tbl[8][2] = {
    { 512,   0 },
    { 448,  64 },
    { 384, 128 },
    { 320, 192 },
    { 256, 256 },
    { 192, 320 },
    { 128, 384 },
    {  64, 448 }
  };

  unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee2 - (g_ram.scrb_h_posit >> 16)) & 0x3F;
  if (cnt != g_ram.cgchgcnt[0]) {
    g_ram.cgchgcnt[0] = cnt;
    unsigned char* p_vram = &g_vram[0x2A60];
    unsigned char* p_source = &cg_chg_10_01_cg[(cnt & 7) * 1024 + (cnt & 0x38) * 16];
    unsigned short* p_size = size_tbl[(cnt & 0x38) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_10_01_cg[(cnt & 7) * 1024];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
  cnt = (unsigned short)(g_ram.DAT_08ffeee4 - (g_ram.vs_scrb_h_posit >> 16)) & 0x3F;
  if (cnt != g_ram.cgchgcnt[1]) {
    g_ram.cgchgcnt[1] = cnt;
    unsigned char* p_vram = &g_vram[0x2E60];
    unsigned char* p_source = &cg_chg_10_01_cg[(cnt & 7) * 1024 + (cnt & 0x38) * 16];
    unsigned short* p_size = size_tbl[(cnt & 0x38) >> 3];
    memcpy(p_vram, p_source, p_size[0] * 2);
    if (p_size[1] != 0) {
      p_vram += p_size[0] * 2;
      p_source = &cg_chg_10_01_cg[(cnt & 7) * 1024];
      memcpy(p_vram, p_source, p_size[1] * 2);
    }
  }
}


static void cg_chg_13(SKC_cg_chg_data* p_data) {
  unsigned char cnt = (unsigned short)(g_ram.DAT_08ffeee2 - (g_ram.scrb_v_posit >> 16)) & 0x1F;
  if (cnt != g_ram.cgchgcnt[0]) {
    g_ram.cgchgcnt[0] = cnt;
    memcpy(&g_vram[0x0A80], &cg_chg_13_00_cg[cnt * 4], 128);
  }
}


static void cg_chg_14(SKC_cg_chg_data* p_data) {
  if (g_ram.cgchgtim[1] == 0) {
    unsigned short offset_tbl[16] = {
      0x180, 0x120, 0x0C0, 0x060, 0x400, 0x3A0, 0x340, 0x2E0, 0x680, 0x620, 0x5C0, 0x560, 0x180, 0x120, 0x0C0, 0x060
    };

    memcpy(&g_ram.screens[0x7000], &g_ram.screens[0x6000 + g_ram.cgchg14cnt2], 0x600);
    g_ram.cgchg14cnt2 -= 4;
    g_ram.cgchg14cnt2 &= 0x7F;

    for (int i = 0; i < 3; ++i) {
      unsigned char* a3 = &g_ram.screens[0x7200 + i * 0x200];

      for (int j = 0; j < 4; ++j) {
        unsigned char* a1 = &g_ram.screens[0x7000 + offset_tbl[i * 4 + j]];
        unsigned char* a2 = &g_ram.screens[0x7000 + offset_tbl[i * 4 + j + 2]];

        for (int k = 0; k < 8; ++k) {
          unsigned long d0 = (a1[0] | a1[1] << 8 | a1[2] << 8 | a1[3] << 8) & (0x000000FF << k * 4);
          unsigned long d1 = (a2[0] | a1[1] << 8 | a1[2] << 8 | a1[3] << 8) & (0xFFFFFFFF >> 32 - k * 4);
          d0 |= d1;
          *a3++ = d0 & 0xFF;
          *a3++ = d0 >> 8 & 0xFF;
          *a3++ = d0 >> 16 & 0xFF;
          *a3++ = d0 >> 24 & 0xFF;
        }
      }
    }

    ++g_ram.cgchgtim[1];
  }
  else {
    FUN_0044c42b();
    ++g_ram.cgchgtim[1];
    if (g_ram.cgchgtim[1] >= 4) {
      g_ram.cgchgtim[1] = 0;
      g_ram.cgchg14cnt += 0x280;
      if (g_ram.cgchg14cnt >= 0x5000) {
        g_ram.cgchg14cnt = 0;
      }
      memcpy(&g_vram[0x1D20], &g_ram.screens[0x7000], 0x780);
    }
  }
  cg_chg0(p_data, &g_ram.cgchgtim[3], &g_ram.cgchgcnt[3]);
}


static void FUN_0044c42b(void) {
  unsigned char unknown_tbl[3][4] = {
    { 0x50, 0x05, 0xA0, 0x0A },
    {    0,    0,    0,    0 },
    { 0xA0, 0x0A, 0x50, 0x05 }
  };

  unsigned char* a3 = &g_ram.screens[0x7000 + (g_ram.cgchgtim[1] - 1) * 0x280];
  unsigned char d3 = unknown_tbl[g_ram.cgchgtim[1] - 1][0];
  unsigned char d4 = unknown_tbl[g_ram.cgchgtim[1] - 1][1];
  unsigned char d5 = unknown_tbl[g_ram.cgchgtim[1] - 1][2];
  unsigned char d6 = unknown_tbl[g_ram.cgchgtim[1] - 1][3];
  unsigned char* a1 = &g_ram.screens[0x1000 + g_ram.cgchg14cnt];

  for (int i = 0; i < 512; ++i) {
    if (a1[i] != 0) {
      if (a1[i] & 0xF0) {
        a3[i] = a3[i] & 0x0F | (a1[i] & 0xF0) + d3;
      }
      if (a1[i] & 0x0F) {
        a3[i] = a3[i] & 0xF0 | (a3[i] & 0x0F) + d4;
      }
      a3[i] &= 0xFF;
    }
  }

  a3 += 512;
  a1 += 512;

  for (int i = 0; i < 128; ++i) {
    if (a1[i] & 0xF0) {
      if ((a1[i] & 0xF0) < 128) {
        a3[i] = a3[i] & 0x0F | (a1[i] & 0xF0) + d3;
      }
      else {
        a3[i] = a3[i] & 0x0F | (a1[i] & 0xF0) - d5;
      }
    }
    if (a1[i] & 0x0F) {
      if ((a1[i] & 0x0F) >= 8) {
        a3[i] = a3[i] & 0xF0 | (a1[i] & 0x0F) + d4;
      }
      else {
        a3[i] = a3[i] & 0xF0 | (a1[i] & 0x0F) - d6;
      }
    }
  }
}


static void cg_chg_def(SKC_cg_chg_data* p_data) {
  cg_chg(p_data);
}


void cg_chg(SKC_cg_chg_data* p_data) {
  cg_chg0(p_data, &g_ram.cgchgtim[0], &g_ram.cgchgcnt[0]);
}


static void cg_chg0(SKC_cg_chg_data* p_data, unsigned char* p_cgchgtim, unsigned char* p_cgchgcnt) {
  for (int i = 0; i < p_data->cnt; ++i) {
    cg_chg1(p_data->items[i], &p_cgchgtim[i], &p_cgchgcnt[i]);
  }
}


static void cg_chg1(SKC_cg_chg_item* p_item, unsigned char* p_cgchgtim, unsigned char* p_cgchgcnt) {
  if (*p_cgchgtim-- == 0) {
    if (*p_cgchgcnt >= p_item->chgcnt) {
      *p_cgchgcnt = 0;
    }
    unsigned char* p_source = p_item->cg_ptr;
    if (p_item->tim == 0xFF) {
      unsigned char (*p_data)[2] = (unsigned char (*)[2])p_item->data_ptr;
      *p_cgchgtim = p_data[*p_cgchgcnt][1];
      p_source += p_data[*p_cgchgcnt][0] * 32;
    }
    else {
      *p_cgchgtim = p_item->tim;
      p_source += p_item->data_ptr[*p_cgchgcnt] * 32;
    }
    memcpy(&g_vram[p_item->vram_adr], p_source, p_item->tilecnt * 32);
    ++*p_cgchgcnt;
  }
}


static unsigned char cg_chg_0000_00_data[18] = {
  60, 79,
  48,  5,
  24,  5,
  12,  5,
   0, 79,
  12,  3,
  24,  3,
  36,  1,
  48,  1
};
static unsigned char cg_chg_0000_01_data[16] = {
  24,  5,
  36,  5,
  48,  5,
  60, 39,
   0,  5,
  12,  5,
  24,  5,
  36,  5
};
static unsigned char cg_chg_0000_02_data[16] = {
   0, 7,
   6, 3,
  12, 3,
  18, 3,
  24, 7,
  18, 3,
  12, 3,
   6, 3
};
static SKC_cg_chg_item cg_chg_0000_00 = { 0xFF, cg_chg_0000_00_cg, 0x5CC0, 9, 12, cg_chg_0000_00_data };
static SKC_cg_chg_item cg_chg_0000_01 = { 0xFF, cg_chg_0000_00_cg, 0x5E40, 8, 12, cg_chg_0000_01_data };
static SKC_cg_chg_item cg_chg_0000_02 = { 0xFF, cg_chg_0000_01_cg, 0x5FC0, 8, 6, cg_chg_0000_02_data };
static SKC_cg_chg_data cg_chg_0000_tbl = {
  3,
  {
    &cg_chg_0000_00,
    &cg_chg_0000_01,
    &cg_chg_0000_02
  }
};


static unsigned char cg_chg_0001_00_data[4] = { 0, 23, 46, 69 };
static unsigned char cg_chg_0001_01_data[18] = {
  60, 79,
  48,  5,
  24,  5,
  12,  5,
   0, 79,
  12,  3,
  24,  3,
  36,  1,
  48,  1
};
static unsigned char cg_chg_0001_02_data[16] = {
  24,  5,
  36,  5,
  48,  5,
  60, 39,
   0,  5,
  12,  5,
  24,  5,
  36,  5
};
static unsigned char cg_chg_0001_03_data[4] = { 0, 4, 8, 12 };
static unsigned char cg_chg_0001_04_data[4] = { 0, 24, 48, 72 };
static SKC_cg_chg_item cg_chg_0001_00 = { 3, cg_chg_0001_00_cg, 0x1660, 4, 23, cg_chg_0001_00_data };
static SKC_cg_chg_item cg_chg_0001_01 = { 0xFF, cg_chg_0001_01_cg, 0x1940, 9, 12, cg_chg_0001_01_data };
static SKC_cg_chg_item cg_chg_0001_02 = { 0xFF, cg_chg_0001_01_cg, 0x1AC0, 8, 12, cg_chg_0001_02_data };
static SKC_cg_chg_item cg_chg_0001_03 = { 3, cg_chg_0001_03_cg, 0x1C40, 4, 4, cg_chg_0001_03_data };
static SKC_cg_chg_item cg_chg_0001_04 = { 3, cg_chg_0001_04_cg, 0x1CC0, 4, 24, cg_chg_0001_04_data };
static SKC_cg_chg_data cg_chg_0001_tbl = {
  5,
  {
    &cg_chg_0001_00,
    &cg_chg_0001_01,
    &cg_chg_0001_02,
    &cg_chg_0001_03,
    &cg_chg_0001_04
  }
};


static unsigned char cg_chg_0100_00_data[6] = {
   0, 2,
  36, 1,
  72, 2
};
static unsigned char cg_chg_0100_01_data[32] = {
   0, 4,
   6, 3,
  12, 2,
  18, 1,
  24, 0,
  30, 1,
  36, 2,
  42, 3,
  48, 4,
  42, 3,
  36, 2,
  30, 1,
  24, 0,
  18, 1,
  12, 2,
   6, 3
};
static SKC_cg_chg_item cg_chg_0100_00 = { 0xFF, cg_chg_0100_00_cg, 0x6180, 3, 36, cg_chg_0001_00_data };
static SKC_cg_chg_item cg_chg_0100_01 = { 0xFF, cg_chg_0100_01_cg, 0x22A0, 16, 6, cg_chg_0001_01_data };
static SKC_cg_chg_data cg_chg_0100_tbl = {
  2,
  {
    &cg_chg_0100_00,
    &cg_chg_0100_01
  }
};


static unsigned char cg_chg_0101_00_data[4] = { 0, 21, 42, 63 };
static unsigned char cg_chg_0101_01_data[32] = {
   0, 4,
   6, 3,
  12, 2,
  18, 1,
  24, 0,
  30, 1,
  36, 2,
  42, 3,
  48, 4,
  42, 3,
  36, 2,
  30, 1,
  24, 0,
  18, 1,
  12, 2,
   6, 3
};
static SKC_cg_chg_item cg_chg_0101_00 = { 3, cg_chg_0101_00_cg, 0x4BC0, 4, 21, cg_chg_0101_00_data };
static SKC_cg_chg_item cg_chg_0101_01 = { 0xFF, cg_chg_0100_01_cg, 0x22A0, 16, 6, cg_chg_0101_01_data };
static SKC_cg_chg_data cg_chg_0101_tbl = {
  2,
  {
    &cg_chg_0101_00,
    &cg_chg_0101_01
  }
};


static unsigned char cg_chg_02_00_data[6] = { 0, 48, 96, 144, 192, 240 };
static unsigned char cg_chg_02_01_data[8] = {
  0,  7,
  1, 14,
  2,  7,
  1, 14
};
static SKC_cg_chg_item cg_chg_02_00 = { 9, cg_chg_02_00_cg, 0x4440, 6, 48, cg_chg_02_00_data };
static SKC_cg_chg_item cg_chg_02_01 = { 0xFF, cg_chg_02_01_cg, 0x4A40, 4, 1, cg_chg_02_01_data };
static SKC_cg_chg_data cg_chg_02_tbl = {
  2,
  {
    &cg_chg_02_00,
    &cg_chg_02_01
  }
};


static unsigned char cg_chg_03_00_data[16] = { 0, 18, 36, 54, 72, 90, 108, 126, 9, 27, 45, 63, 81, 99, 117, 135 };
static unsigned char cg_chg_03_01_data[16] = { 9, 27, 45, 63, 81, 99, 117, 135, 0, 18, 36, 54, 72, 90, 108, 126 };
static unsigned char cg_chg_03_02_data[16] = {
  0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240
};
static unsigned char cg_chg_03_03_data[8] = { 0, 32, 64, 96, 128, 160, 192, 224 };
static unsigned char cg_chg_03_04_data[8] = { 0, 16, 32, 48, 64, 80, 96, 112 };
static unsigned char cg_chg_03_05_data[6] = { 0, 4, 8, 0, 4, 8 };
static unsigned char cg_chg_03_06_data[4] = { 0, 20, 40, 60 };
static SKC_cg_chg_item cg_chg_03_00 = { 3, cg_chg_03_00_cg, 0x5640, 16, 9, cg_chg_03_00_data };
static SKC_cg_chg_item cg_chg_03_01 = { 3, cg_chg_03_00_cg, 0x5760, 16, 9, cg_chg_03_01_data };
static SKC_cg_chg_item cg_chg_03_02 = { 3, cg_chg_03_02_cg, 0x5880, 16, 16, cg_chg_03_02_data };
static SKC_cg_chg_item cg_chg_03_03 = { 3, cg_chg_03_03_cg, 0x5A80, 8, 32, cg_chg_03_03_data };
static SKC_cg_chg_item cg_chg_03_04 = { 3, cg_chg_03_04_cg, 0x5E80, 8, 16, cg_chg_03_04_data };
static SKC_cg_chg_item cg_chg_03_05 = { 3, cg_chg_03_05_cg, 0x6080, 6, 4, cg_chg_03_05_data };
static SKC_cg_chg_item cg_chg_03_06 = { 1, cg_chg_03_06_cg, 0x6500, 4, 20, };
static SKC_cg_chg_data cg_chg_03_tbl = {
  7,
  {
    &cg_chg_03_00,
    &cg_chg_03_01,
    &cg_chg_03_02,
    &cg_chg_03_03,
    &cg_chg_03_04,
    &cg_chg_03_05,
    &cg_chg_03_06
  }
};


static unsigned char cg_chg_0400_00_data[2] = { 0, 0 };
static unsigned char cg_chg_0400_01_data[6] = { 0, 8, 16, 0, 8, 16 };
static unsigned char cg_chg_0400_02_data[8] = { 0, 16, 32, 48, 64, 80, 96, 112 };
static unsigned char cg_chg_0400_03_data[2] = { 0, 8 };
static unsigned char cg_chg_0400_04_data[6] = { 0, 8, 16, 0, 8, 16 };
static SKC_cg_chg_item cg_chg_0400_00 = { 63, cg_chg_04_00_cg, 0x4200, 2, 32, cg_chg_0400_00_data };
static SKC_cg_chg_item cg_chg_0400_01 = { 7, cg_chg_04_01_cg, 0x4600, 6, 8, cg_chg_0400_01_data };
static SKC_cg_chg_item cg_chg_0400_02 = { 1, cg_chg_04_02_cg, 0x4700, 8, 16, cg_chg_0400_02_data };
static SKC_cg_chg_item cg_chg_0400_03 = { 7, cg_chg_04_03_cg, 0x4000, 2, 8, cg_chg_0400_03_data };
static SKC_cg_chg_item cg_chg_0400_04 = { 7, cg_chg_04_04_cg, 0x4100, 6, 8, cg_chg_0400_04_data };
static SKC_cg_chg_data cg_chg_0400_tbl = {
  5,
  {
    &cg_chg_0400_00,
    &cg_chg_0400_01,
    &cg_chg_0400_02,
    &cg_chg_0400_03,
    &cg_chg_0400_04
  }
};


static unsigned char cg_chg_0401_00_data[8] = { 0, 32, 64, 96, 128, 160, 192, 224 };
static unsigned char cg_chg_0401_01_data[6] = { 0, 8, 16, 0, 8, 16 };
static unsigned char cg_chg_0401_02_data[8] = { 0, 16, 32, 48, 64, 80, 96, 112 };
static unsigned char cg_chg_0401_03_data[2] = { 0, 8 };
static unsigned char cg_chg_0401_04_data[6] = { 0, 8, 16, 0, 8, 16 };
static SKC_cg_chg_item cg_chg_0401_00 = { 1, cg_chg_04_00_cg, 0x4200, 8, 32, cg_chg_0401_00_data };
static SKC_cg_chg_item cg_chg_0401_01 = { 7, cg_chg_04_01_cg, 0x4600, 6, 8, cg_chg_0401_01_data };
static SKC_cg_chg_item cg_chg_0401_02 = { 1, cg_chg_04_02_cg, 0x4700, 8, 16, cg_chg_0401_02_data };
static SKC_cg_chg_item cg_chg_0401_03 = { 7, cg_chg_04_03_cg, 0x4000, 2, 8, cg_chg_0401_03_data };
static SKC_cg_chg_item cg_chg_0401_04 = { 7, cg_chg_04_04_cg, 0x4100, 6, 8, cg_chg_0401_04_data };
static SKC_cg_chg_data cg_chg_0401_tbl = {
  5,
  {
    &cg_chg_0401_00,
    &cg_chg_0401_01,
    &cg_chg_0401_02,
    &cg_chg_0401_03,
    &cg_chg_0401_04
  }
};


static unsigned char cg_chg_05_00_data[8] = { 0, 4, 8, 12, 16, 20, 24, 28 };
static SKC_cg_chg_item cg_chg_05_00 = { 3, cg_chg_05_00_cg, 0x23C0, 8, 4, cg_chg_05_00_data };
static SKC_cg_chg_data cg_chg_05_tbl = {
  1,
  {
    &cg_chg_05_00
  }
};


static unsigned char cg_chg_0600_00_00_data[4] = { 0, 8, 16, 24 };
static SKC_cg_chg_item cg_chg_0600_00_00 = { 2, cg_chg_0600_00_00_cg, 0x6CA0, 4, 8, cg_chg_0600_00_00_data };
static SKC_cg_chg_data cg_chg_0600_00_tbl = {
  1,
  {
    &cg_chg_0600_00_00
  }
};


static unsigned char cg_chg_0600_01_00_data[4] = { 0, 5, 10, 15 };
static unsigned char cg_chg_0600_01_01_data[6] = { 0, 4, 8, 12, 16, 20 };
static SKC_cg_chg_item cg_chg_0600_01_00 = { 7, cg_chg_0601_00_cg, 0x2E00, 4, 5, cg_chg_0600_01_00_data };
static SKC_cg_chg_item cg_chg_0600_01_01 = { 7, cg_chg_0601_01_cg, 0x2EA0, 6, 4, cg_chg_0600_01_01_data };
static SKC_cg_chg_data cg_chg_0600_01_tbl = {
  2,
  {
    &cg_chg_0600_01_00,
    &cg_chg_0600_01_01
  }
};


static unsigned char cg_chg_0601_00_data[4] = { 0, 5, 10, 15 };
static unsigned char cg_chg_0601_01_data[6] = { 0, 4, 8, 12, 16, 20 };
static SKC_cg_chg_item cg_chg_0601_00 = { 7, cg_chg_0601_00_cg, 0x2E00, 4, 5, cg_chg_0601_00_data };
static SKC_cg_chg_item cg_chg_0601_01 = { 7, cg_chg_0601_01_cg, 0x2EA0, 6, 4, cg_chg_0601_01_data };
static SKC_cg_chg_data cg_chg_0601_tbl = {
  2,
  {
    &cg_chg_0601_00,
    &cg_chg_0601_01
  }
};


static unsigned char cg_chg_07_00_data[40] = {
   0, 24,
   4,  0,
   0,  0,
   4,  0,
   8,  0,
   4,  0,
   8,  0,
  12,  0,
   8,  0,
  12,  0,
   8,  0,
  12,  0,
  16,  0,
  12,  0,
  16,  0,
  20,  0,
  16,  0,
  20, 49,
   0,  0,
  20,  0
};
static unsigned char cg_chg_07_01_data[24] = {
   0, 29,
   4,  0,
   0,  0,
   4,  0,
   0,  0,
   4,  0,
   0,  0,
   4,  1,
   8, 29,
  12,  4,
  16,  4,
  20,  4
};
static unsigned char cg_chg07_02_data[16] = {
   0, 4,
   8, 4,
  16, 6,
   8, 4,
   0, 4,
  24, 4,
  32, 6,
  24, 4
};
static unsigned char cg_chg07_03_data[16] = {
  16, 6,
   8, 4,
   0, 4,
  24, 4,
  32, 6,
  24, 4,
   0, 4,
   8, 4
};
static SKC_cg_chg_item cg_chg_07_00 = { 0xFF, cg_chg_07_00_cg, 0x04A0, 20, 4, cg_chg_07_00_data };
static SKC_cg_chg_item cg_chg_07_01 = { 0xFF, cg_chg_07_01_cg, 0x0320, 12, 4, cg_chg_07_01_data };
static SKC_cg_chg_item cg_chg_07_02 = { 0xFF, cg_chg_07_02_cg, 0x0BA0, 8, 8, cg_chg07_02_data };
static SKC_cg_chg_item cg_chg_07_03 = { 0xFF, cg_chg_07_03_cg, 0x03A0, 8, 8, cg_chg07_03_data };
static SKC_cg_chg_data cg_chg_07_tbl = {
  4,
  {
    &cg_chg_07_00,
    &cg_chg_07_01,
    &cg_chg_07_02,
    &cg_chg_07_03
  }
};


static unsigned char cg_chg_0900_00_data[4] = { 0, 4, 8, 12 };
static unsigned char cg_chg_0900_01_data[4] = { 0, 4, 8, 12 };
static SKC_cg_chg_item cg_chg_0900_00 = { 5, cg_chg_0900_00_cg, 0x6A80, 4, 4, cg_chg_0900_00_data };
static SKC_cg_chg_item cg_chg_0900_01 = { 5, cg_chg_0900_01_cg, 0x6A00, 4, 4, cg_chg_0900_01_data };
static SKC_cg_chg_data cg_chg_0900_tbl = {
  2,
  {
    &cg_chg_0900_00,
    &cg_chg_0900_01
  }
};


static unsigned char cg_chg_0901_00_data[6] = {
   0, 2,
   6, 2,
  12, 1
};
static unsigned char cg_chg_0901_01_data[8] = { 0, 56, 48, 40, 32, 24, 16, 8 };
static SKC_cg_chg_item cg_chg_0901_00 = { 0xFF, cg_chg_0901_00_cg, 0x6B00, 3, 6, cg_chg_0901_00_data };
static SKC_cg_chg_item cg_chg_0901_01 = { 1, cg_chg_0901_01_cg, 0x6A00, 8, 8, cg_chg_0901_01_data };
static SKC_cg_chg_data cg_chg_0901_tbl = {
  2,
  {
    &cg_chg_0901_00,
    &cg_chg_0901_01
  }
};


static unsigned char cg_chg_0a_00_data[4] = { 0, 36, 72, 108 };
static unsigned char cg_chg_0a_01_data[4] = { 0, 8, 16, 24 };
static unsigned char cg_chg_0a_02_data[3] = { 0, 8, 16 };
static unsigned char cg_chg_0a_03_data[4] = { 0, 9, 18, 27 };
static unsigned char cg_chg_0a_04_data[4] = { 0, 4, 8, 12 };
static unsigned char cg_chg_0a_05_data[4] = { 0, 13, 26, 39 };
static SKC_cg_chg_item cg_chg_0a_00 = { 7, cg_chg_0a_00_cg, 0x3E60, 4, 36, cg_chg_0a_00_data };
static SKC_cg_chg_item cg_chg_0a_01 = { 7, cg_chg_0a_01_cg, 0x42E0, 4, 8, cg_chg_0a_01_data };
static SKC_cg_chg_item cg_chg_0a_02 = { 7, cg_chg_0a_02_cg, 0x43E0, 3, 8, cg_chg_0a_02_data };
static SKC_cg_chg_item cg_chg_0a_03 = { 2, cg_chg_0a_03_cg, 0x3B20, 4, 9, cg_chg_0a_03_data };
static SKC_cg_chg_item cg_chg_0a_04 = { 2, cg_chg_0a_04_cg, 0x3C40, 4, 4, cg_chg_0a_04_data };
static SKC_cg_chg_item cg_chg_0a_05 = { 2, cg_chg_0a_05_cg, 0x3CC0, 4, 13, cg_chg_0a_05_data };
static SKC_cg_chg_data cg_chg_0a_tbl = {
  6,
  {
    &cg_chg_0a_00,
    &cg_chg_0a_01,
    &cg_chg_0a_02,
    &cg_chg_0a_03,
    &cg_chg_0a_04,
    &cg_chg_0a_05
  }
};


static unsigned char cg_chg_0b_00_data[4] = { 0, 2 };
static unsigned char cg_chg_0b_01_data[6] = { 0, 30, 60, 0, 30, 60 };
static unsigned char cg_chg_0b_02_data[8] = { 0, 4, 8, 12, 16, 20, 24, 28 };
static unsigned char cg_chg_0b_03_data[8] = {
   0, 9,
   6, 4,
  12, 9,
   6, 4
};
static unsigned char cg_chg_0b_04_data[4] = { 0, 2, 4, 2 };
static unsigned char cg_chg_0b_05_data[6] = { 0, 3, 6, 0, 3, 6 };
static unsigned char cg_chg_0b_06_data[2] = { 0, 8 };
static unsigned char cg_chg_0b_07_data[132] = {
   0, 45,  0, 45,  0, 45,  0, 45,  0, 45,
   0, 45,  5, 45,  5, 45,  5, 45,  5, 45,
   5, 45,  5, 45, 10, 45, 10, 45, 10, 45,
  10, 45, 10, 45, 10, 45, 15, 45, 15, 45,
  15, 45, 15, 45, 15, 45, 15, 45, 20, 45,
  20, 45, 20, 45, 20, 45, 20, 45, 20, 45,
  25, 45, 25, 45, 25, 45, 25, 45, 25, 45,
  25, 45, 30, 45, 30, 45, 30, 45, 30, 45,
  30, 45, 30, 45, 35, 45, 35, 45, 35, 45,
  35, 45, 35, 45, 35, 45, 40, 45, 40, 45,
  40, 45, 40, 45, 40, 45, 40, 45, 40, 45,
  40, 45, 40, 45, 40, 45, 40, 45, 40, 45,
  40, 45, 40, 45, 40, 45, 40, 45, 40, 45,
  40, 45
};
static SKC_cg_chg_item cg_chg_0b_00 = { 0, cg_chg_0b_00_cg, 0x1C80, 2, 2, cg_chg_0b_00_data };
static SKC_cg_chg_item cg_chg_0b_01 = { 1, cg_chg_0b_01_cg, 0x3E80, 6, 30, cg_chg_0b_01_data };
static SKC_cg_chg_item cg_chg_0b_02 = { 3, cg_chg_0b_02_cg, 0x1D80, 8, 4, cg_chg_0b_02_data };
static SKC_cg_chg_item cg_chg_0b_03 = { 0xFF, cg_chg_0b_03_cg, 0x0BE0, 4, 6, cg_chg_0b_03_data };
static SKC_cg_chg_item cg_chg_0b_04 = { 4, cg_chg_0b_04_cg, 0x0960, 4, 2, cg_chg_0b_04_data };
static SKC_cg_chg_item cg_chg_0b_05 = { 4, cg_chg_0b_05_cg, 0x0D60, 6, 3, cg_chg_0b_05_data };
static SKC_cg_chg_item cg_chg_0b_06 = { 1, cg_chg_0b_06_cg, 0x0500, 2, 8, cg_chg_0b_06_data };
static SKC_cg_chg_item cg_chg_0b_07 = { 0, cg_chg_0b_07_cg, 0x4DA0, 132, 5, cg_chg_0b_07_data };
static SKC_cg_chg_data cg_chg_0b_tbl = {
  8,
  {
    &cg_chg_0b_00,
    &cg_chg_0b_01,
    &cg_chg_0b_02,
    &cg_chg_0b_03,
    &cg_chg_0b_04,
    &cg_chg_0b_05,
    &cg_chg_0b_06,
    &cg_chg_0b_07
  }
};


static unsigned char cg_chg_0e_00_data[3] = { 0, 16, 32 };
static SKC_cg_chg_item cg_chg_0e_00 = { 9, cg_chg_0e_00_cg, 0x4700, 3, 16, cg_chg_0e_00_data };
static SKC_cg_chg_data cg_chg_0e_tbl = {
  1,
  {
    &cg_chg_0e_00
  }
};


static unsigned char cg_chg_0f_00_data[6] = { 0, 7, 14, 21, 28, 35 };
static unsigned char cg_chg_0f_01_data[10] = { 0, 8, 16, 24, 32, 0, 8, 16, 24, 32 };
static unsigned char cg_chg_0f_02_data[2] = { 0, 3 };
static unsigned char cg_chg_0f_03_data[2] = { 0, 1 };
static SKC_cg_chg_item cg_chg_0f_00 = { 7, cg_chg_0f_00_cg, 0x2300, 6, 7, cg_chg_0f_00_data };
static SKC_cg_chg_item cg_chg_0f_01 = { 5, cg_chg_0f_01_cg, 0x23E0, 10, 8, cg_chg_0f_01_data };
static SKC_cg_chg_item cg_chg_0f_02 = { 2, cg_chg_0f_02_cg, 0x24E0, 2, 3, cg_chg_0f_02_data };
static SKC_cg_chg_item cg_chg_0f_03 = { 4, cg_chg_0f_03_cg, 0x2540, 2, 1, cg_chg_0f_03_data };
static SKC_cg_chg_data cg_chg_0f_tbl = {
  4,
  {
    &cg_chg_0f_00,
    &cg_chg_0f_01,
    &cg_chg_0f_02,
    &cg_chg_0f_03
  }
};


static unsigned char cg_chg_10_00_data[5] = { 0, 12, 24, 36, 48 };
static SKC_cg_chg_item cg_chg_10_00 = { 11, cg_chg_10_00_cg, 0x28E0, 5, 12, cg_chg_10_00_data };
static SKC_cg_chg_data cg_chg_10_tbl = {
  1,
  {
    &cg_chg_10_00
  }
};


static SKC_cg_chg_data cg_chg_none_tbl = {
  0,
  {}
};


static unsigned char cg_chg_14_00_data[8] = { 38, 0, 76, 0, 114, 0, 152, 0 };
static SKC_cg_chg_item cg_chg_14_00 = { 0, cg_chg_14_00_cg, 0x24A0, 8, 38, cg_chg_14_00_data };
static SKC_cg_chg_data cg_chg_14_tbl = {
  1,
  {
    &cg_chg_14_00
  }
};


static unsigned char cg_chg_1601_00_data[8] = { 0, 3, 6, 9, 12, 15, 18, 21 };
static unsigned char cg_chg_1601_01_data[6] = { 0, 2, 4, 6, 8, 10 };
static unsigned char cg_chg_1601_02_data[8] = { 0, 4, 8, 12, 16, 20, 24, 28 };
static unsigned char cg_chg_1601_03_data[6] = { 0, 3, 6, 9, 12, 15 };
static SKC_cg_chg_item cg_chg_1601_00 = { 2, cg_chg_1601_00_cg, 0x5A00, 8, 3, cg_chg_1601_00_data };
static SKC_cg_chg_item cg_chg_1601_01 = { 3, cg_chg_1601_01_cg, 0x5A60, 6, 2, cg_chg_1601_01_data };
static SKC_cg_chg_item cg_chg_1601_02 = { 2, cg_chg_1601_02_cg, 0x5AA0, 8, 4, cg_chg_1601_02_data };
static SKC_cg_chg_item cg_chg_1601_03 = { 3, cg_chg_1601_03_cg, 0x5B20, 6, 3, cg_chg_1601_03_data };
static SKC_cg_chg_data cg_chg_1601_tbl = {
  4,
  {
    &cg_chg_1601_00,
    &cg_chg_1601_01,
    &cg_chg_1601_02,
    &cg_chg_1601_03
  }
};


void cg_change_init(void) {
  switch (g_ram.stageno) {
    case HYDROCITY_ACT_1:
      waterline0100_cg_chg_init();
      break;
    case HYDROCITY_ACT_2:
      g_ram.cgchgcnt[0] = 32;
      g_ram.cgchgcnt[1] = 64;
    case MARBLE_GARDEN_ACT_1:
    case MARBLE_GARDEN_ACT_2:
      g_ram.cgchgcnt[0] = 64;
      g_ram.cgchgtim[1] = 0;
      g_ram.cgchgtim[2] = 0;
      g_ram.cgchgtim[3] = 0;
      g_ram.cgchgtim[4] = 2;
      g_ram.cgchgtim[5] = 2;
      g_ram.cgchgtim[6] = 2;
      g_ram.cgchgtim[7] = 1;
      break;
    case LAUNCH_BASE_ACT_1:
      g_ram.cgchgcnt[1] = 32;
      break;
    case LAUNCH_BASE_ACT_2:
      waterline0601_cg_chg_init();
      g_ram.cgchgcnt[0] = 16;
      break;
    case MUSHROOM_HILL_ACT_1:
    case MUSHROOM_HILL_ACT_2:
      g_ram.cgchgcnt[0] = 32;
      g_ram.cgchgcnt[1] = 64;
      break;
    case SANDOPOLIS_ACT_1:
    case SANDOPOLIS_ACT_2:
      g_ram.cgchgcnt[0] = 0;
      break;
    case LAVA_REEF_ACT_1:
      g_ram.cgchgcnt[0] = 0;
      g_ram.cgchgcnt[1] = 0;
      break;
    case DESERT_PALACE_ACT_1:
      g_ram.cgchgcnt[0] = 64;
      g_ram.cgchgcnt[1] = 64;
      break;
    case ROLLING_JUMP_ACT_1:
    case ROLLING_JUMP_ACT_2: {
      unsigned char* p_destination = &g_ram.screens[0x1000];
      unlze(&p_destination, bg_14_00_cg);
      p_destination = &g_ram.screens[0x7000];
      unlze(&p_destination, bg_14_01_cg);
      p_destination = &g_ram.screens[0x6000];
      unsigned char* p_source = &g_ram.screens[0x7000];

      for (int i = 0 ; i < 12; ++i) {
        memcpy(&p_destination[i * 2 * 128], &p_source[i * 128], 128);
        memcpy(&p_destination[(i * 2 + 1) * 128], &p_source[i * 128], 128);
      }

      p_destination = &g_ram.screens[0x7800];
      unlze(&p_destination, DAT_004db190);
      break;
    }
    case LAVA_REEF_BOSS:
      g_ram.cgchgcnt[0] = 0;
      g_ram.cgchgcnt[1] = 0;
      break;
  }
}
