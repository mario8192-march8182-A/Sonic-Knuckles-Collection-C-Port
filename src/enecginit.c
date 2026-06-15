#include "enecginit.h"
#include "data/cg/zone0a/egjr0a.h"
#include "types/cgdata.h"
#include "types/sonic3ram.h"
#include "utils/stageno.h"
#include "dev.h"
static SKC_cg_data* enecg_tbl[15][2];
static SKC_cg_data enecg_tbl00;
static SKC_cg_data enecg_tbl0100;
static SKC_cg_data enecg_tbl0101;
static SKC_cg_data enecg_tbl0200;
static SKC_cg_data enecg_tbl0201;
static SKC_cg_data enecg_tbl03;
static SKC_cg_data enecg_tbl04;
static SKC_cg_data enecg_tbl05;
static SKC_cg_data enecg_tbl06;
static SKC_cg_data enecg_tbl06;
static SKC_cg_data enecg_tbl0700;
static SKC_cg_data enecg_tbl0701;
static SKC_cg_data enecg_tbl08;
static SKC_cg_data enecg_tbl09;
static SKC_cg_data enecg_tbl0a;
static SKC_cg_data enecg_tbl0b;
static SKC_cg_data enecg_tbl0c;
static SKC_cg_data enecg_tbl0d;
static SKC_cg_data enecg_tbl0e;

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void enecginit(void) {
  unsigned short stageno = g_ram.stageno;
  if (get_zone(g_ram.stageno) == LAVA_REEF_BOSS_AND_HIDDEN_PALACE) {
    stageno = 0x0D;
    set_act(&stageno, get_act(g_ram.stageno));
  }
  else if (g_ram.stageno == DEATH_EGG_BOSS) {
    stageno = 0x0E;
    set_act(&stageno, get_act(g_ram.stageno));
  }
  SKC_cg_data* p_cg_data = enecg_tbl[get_zone(stageno)][get_act(stageno)];
  if (p_cg_data->cnt >= 0) {
    for (int i = 0; i < p_cg_data->cnt + 1; ++i) {
      unlze_moduled(&g_vram[p_cg_data->data[i].offset], p_cg_data->data[i].cg_ptr);
    }
  }
}


static SKC_cg_data* enecg_tbl[15][2] = {
  { &enecg_tbl00, &enecg_tbl00 },
  { &enecg_tbl0100, &enecg_tbl0101 },
  { &enecg_tbl0200, &enecg_tbl0201 },
  { &enecg_tbl03, &enecg_tbl03 },
  { &enecg_tbl04, &enecg_tbl04 },
  { &enecg_tbl05, &enecg_tbl05 },
  { &enecg_tbl06, &enecg_tbl06 },
  { &enecg_tbl0700, &enecg_tbl0701 },
  { &enecg_tbl08, &enecg_tbl08 },
  { &enecg_tbl09, &enecg_tbl09 },
  { &enecg_tbl0a, &enecg_tbl0a },
  { &enecg_tbl0b, &enecg_tbl0b },
  { &enecg_tbl0c, &enecg_tbl0c },
  { &enecg_tbl0d, &enecg_tbl0d },
  { &enecg_tbl0e, &enecg_tbl0e }
};


static SKC_cg_data enecg_tbl00 = {
  2,
  {
    //{ saru00_cg, 0xA900 },
    //{ hana00_cg, 0xA540 },
    //{ snak00_cg, 0xABE0 }
  }
};
static SKC_cg_data enecg_tbl0100 = {
  3,
  {
    //{ hdai01_cg, 0xA720 },
    //{ yado01_cg, 0xA000 },
    //{ fish01_cg, 0xA9A0 },
    //{ fugu01_cg, 0xAB20 }
  }
};
static SKC_cg_data enecg_tbl0101 = {
  3,
  {
    //{ shak01_cg, 0xA720 },
    //{ yado01_cg, 0xA000 },
    //{ fish01_cg, 0xA9A0 },
    //{ fugu01_cg, 0xAB20 }
  }
};
static SKC_cg_data enecg_tbl0200 = {
  2,
  {
    //{ hari02_cg, 0xA600 },
    //{ bs02m0_cg, 0xA9E0 },
    //{ bs02m0_iwa_cg, 0xAE00 }
  }
};
static SKC_cg_data enecg_tbl0201 = {
  1,
  {
    //{ hari02_cg, 0xA600 },
    //{ bata02_cg, 0xA9E0 }
  }
};
static SKC_cg_data enecg_tbl03 = {
  3,
  {
    //{ elec03_cg, 0xA480 },
    //{ bat03_cg, 0xAA40 },
    //{ shel03_shot_cg, 0xAE00 },
    //{ baloon_cg, 0xAE80 }
  }
};
static SKC_cg_data enecg_tbl04 = {
  2,
  {
    //{ betl04_cg, 0xA0C0 },
    //{ mous04_cg, 0xA5C0 },
    //{ switch04_cg, 0xA000 }
  }
};
static SKC_cg_data enecg_tbl05 = {
  1,
  {
    //{ snow05_cg, 0xAB00 },
    //{ uni05_cg, 0xA900 }
  }
};
static SKC_cg_data enecg_tbl06 = {
  3,
  {
    //{ snil06_cg, 0xA480 },
    //{ uni06_cg, 0xADC0 },
    //{ frog06_cg, 0xA8E0 },
    //{ lasr06_cg, 0xAB00 }
  }
};
static SKC_cg_data enecg_tbl0700 = {
  2,
  {
    //{ mole07_cg, 0xA8A0 },
    //{ mush07_cg, 0xADA0 },
    //{ dfly07_cg, 0xA700 }
  }
};
static SKC_cg_data enecg_tbl0701 = {
  3,
  {
    //{ chkn07_stand_cg, 0xA440 },
    //{ mole07_cg, 0xA8A0 },
    //{ mush07_cg, 0xADA0 },
    //{ dfly07_cg, 0xA700 }
  }
};
static SKC_cg_data enecg_tbl08 = {
  2,
  {
    //{ scop08_cg, 0xA6C0 },
    //{ narl08_cg, 0xAAE0 },
    //{ rock08_cg, 0xA000 }
  }
};
static SKC_cg_data enecg_tbl09 = {
  2,
  {
    //{ snak09_cg, 0xA240 },
    //{ iwa09_cg, 0xA600 },
    //{ gas09_cg, 0xAC40 }
  }
};
static SKC_cg_data enecg_tbl0a = {
  0,
  {
    { egjr0a_cg, 0xA000 }
  }
};
static SKC_cg_data enecg_tbl0b = {
  1,
  {
    //{ gady0b_cg, 0xA000 },
    //{ crou0b_cg, 0xA840 }
  }
};
static SKC_cg_data enecg_tbl0c = {
  0,
  {
    { egjr0a_cg, 0xA000 }
  }
};
static SKC_cg_data enecg_tbl0d = {
  0,
  {
    //{ HPZTeleporter, 0xA5C0 }
  }
};
static SKC_cg_data enecg_tbl0e = {
  -1,
  {}
};
