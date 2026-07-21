#include "gost08.h"
#include <stdbool.h>
#include "../../data/cg/opnbox.h"
#include "../../data/cg/zone08/gost08.h"
#include "../../data/pat/zone08/gost08.h"
#include "../../data/playpositbl.h"
#include "../../types/cgdata.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../utils/fp16.h"
#include "../../utils/stageno.h"
#include "../../action.h"
#include "../../coli.h"
#include "../../dev.h"
#include "../../enecginit.h"
#include "../../etc.h"
#include "../../shared.h"
#include "../../sound.h"
#include "../opnbox.h"
#include "../save.h"
#include "../zone04/obox04.h"
static void gost08_ctr(SKC_sprite_status* p_actwk);
static void gost08_body(SKC_sprite_status* p_actwk);
static void gost08_body__fout0(SKC_sprite_status* p_actwk);
static void gost08_body__fout1(SKC_sprite_status* p_actwk);
static void gost08_init(SKC_sprite_status* p_actwk);
static void gost08_wait0(SKC_sprite_status* p_actwk);
static void gost08_atak_init(SKC_sprite_status* p_actwk);
static void gost08_move0(SKC_sprite_status* p_actwk);
static void gost08_chg0(SKC_sprite_status* p_actwk);
static void gost08_chg1(SKC_sprite_status* p_actwk);
static void gost08_chg2(SKC_sprite_status* p_actwk);
static void gost08_atak0(SKC_sprite_status* p_actwk);
static void gost08_atak1(SKC_sprite_status* p_actwk);
static void gost08_atak2(SKC_sprite_status* p_actwk);
static void gost08_body_fout0(SKC_sprite_status* p_actwk);
static short col_tbl_00[4];
static short col_tbl_04[4];
static void set_openbox_cg(SKC_sprite_status* p_actwk);
static void set_emy08_cg(SKC_sprite_status* p_actwk);
static void obox08_switch(SKC_sprite_status* p_actwk);
static void obox08_gost(SKC_sprite_status* p_actwk);
static void obox08_gost_init(SKC_sprite_status* p_actwk);
static void obox08_gost_move0(SKC_sprite_status* p_actwk);
static void obox08_gost_move1(SKC_sprite_status* p_actwk);
static void chk_gost08_limit(SKC_sprite_status* p_actwk);
static void set_body_init(SKC_sprite_status* p_actwk);
static short gost08_init_spd_tbl[6];
static void set_puka_init(SKC_sprite_status* p_actwk);
static void puka_init_00(SKC_sprite_status* p_actwk);
static void puka_init_01(SKC_sprite_status* p_actwk);
static void puka_init_02(SKC_sprite_status* p_actwk);
static SKC_wrt_init_data gost08_init_tbl;
static SKC_enemy_init0_data obox08_init_tbl;
static SKC_enemy_init0_data obox08_gost_init_tbl;
static SKC_set_act00_data obox08_switch_set_tbl;
static SKC_set_act00_data obox08_gost_set_tbl;
static SKC_set_act05_data gost08_body_set_tbl;
static SKC_wrt_data gost08_wrt_tbl;
static signed char gost08_apar_pg00[12];
static signed char gost08_pg00[7];
static signed char gost08_apar_pg01[14];
static signed char gost08_pg01[7];
static signed char gost08_apar_pg02[14];
static signed char gost08_pg02[7];
static signed char gost08_away_pg00[13];
static signed char gost08_chg_pg00[8];
static signed char gost08_chg_pg01[8];
static unsigned short* gost08_tbl[18];
static unsigned short gost08_tbl00[2];
static unsigned short gost08_tbl01[2];
static unsigned short gost08_tbl02[2];
static unsigned short gost08_tbl03[2];
static unsigned short gost08_tbl04[2];
static unsigned short gost08_tbl05[2];
static unsigned short gost08_tbl06[2];
static unsigned short gost08_tbl07[2];
static unsigned short gost08_tbl08[2];
static unsigned short gost08_tbl09[3];
static unsigned short gost08_tbl10[3];
static unsigned short gost08_tbl11[3];
static unsigned short gost08_tbl12[3];
static unsigned short gost08_tbl13[2];
static unsigned short gost08_tbl14[2];
static unsigned short gost08_tbl15[2];
static unsigned short gost08_tbl16[2];
static unsigned short gost08_tbl17[2];

extern sonic3_ram g_ram;


void gost08(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &gost08_ctr;
  fp16_set_integer(&p_actwk->xposi, 288);
  fp16_set_integer(&p_actwk->yposi, 160);
  gost08_ctr(p_actwk);
}


static void gost08_ctr(SKC_sprite_status* p_actwk) {
  unsigned char cnt_tbl[6] = {
    0, 1, 2, 2, 3, 3
  };

  if (g_ram.actwk[0].u.play.character != KNUCKLES && g_ram.markerno == 0) return;

  if (g_ram.soz_darkness_level != 0) {
    unsigned char max = cnt_tbl[g_ram.soz_darkness_level];
    if (g_ram.gost08_count < max) {
      if (p_actwk->u.obj.actfree.gost08_ctr.spawn_timer-- == 0) {
        ++g_ram.gost08_count;
        if (g_ram.gost08_count < max) {
          p_actwk->u.obj.actfree.gost08_ctr.spawn_timer = 63;
        }
        set_act05(p_actwk, &gost08_body_set_tbl);
      }
    }
  }
  else {
    g_ram.gost08_count = 0;
  }
}


static void gost08_body(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[9] = {
    &gost08_init,
    &gost08_wait0,
    &gost08_move0,
    &gost08_chg0,
    &gost08_chg1,
    &gost08_chg2,
    &gost08_atak0,
    &gost08_atak1,
    &gost08_atak2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &gost08_wrt_tbl);
  if (p_actwk->actflg.onscreen == 0) {
    gost08_body__fout0(p_actwk);
  }
  else if (g_ram.soz_darkness_level == 0) {
    gost08_body__fout1(p_actwk);
  }
  else {
    SKC_sprite_status* p_coli_actwk;
    bool collision = chk_emy_col(p_actwk, &p_coli_actwk);
    if (collision) {
      bool attacked = chk_pl_attack(p_actwk, p_coli_actwk);
      if (attacked) {
        gost08_body__fout1(p_actwk);
        return;
      }
      if (g_ram.actwk[0].u.play.invulnerability_timer == 0) {
        set_pl_damage(p_actwk, p_coli_actwk);
      }
    }
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
}


static void gost08_body__fout0(SKC_sprite_status* p_actwk) {
  --g_ram.gost08_count;
  set_wchg_fout0(p_actwk);
}


static void gost08_body__fout1(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &gost08_body_fout0;
  p_actwk->u.obj.callback_ptr = &gost08_body_fout0;
  pg_init(p_actwk, gost08_away_pg00);
  soundset(-118);
  actionsub(p_actwk);
}


static void gost08_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &gost08_init_tbl);
  p_actwk->actflg.relative_coordinates = 0;
  p_actwk->actflg.onscreen = 1;
  p_actwk->u.obj.actfree.gost08.darkness_level = g_ram.soz_darkness_level;
  p_actwk->u.obj.actfree.gost08.sequence_no = g_ram.gost08_count;
  set_body_init(p_actwk);
  soundset(-110);
  gost08_wait0(p_actwk);
}


static void gost08_wait0(SKC_sprite_status* p_actwk) {
  if (time_pg(p_actwk) == 0) return;

  if (g_ram.soz_darkness_level == 5) {
    gost08_atak_init(p_actwk);
  }
  else {
    p_actwk->r_no = 4;
  }
}


static void gost08_atak_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  set_puka_init(p_actwk);
}


static void gost08_move0(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  puka_puka(p_actwk);
  speedset2(p_actwk);
  chk_gost08_limit(p_actwk);
  if (g_ram.soz_darkness_level != p_actwk->u.obj.actfree.gost08.darkness_level) {
    p_actwk->r_no = 6;
  }
}


static void gost08_chg0(SKC_sprite_status* p_actwk) {
  unsigned char chk_puka_tbl[6] = {
    0, 0, 0, 1, 0, 1
  };

  time_pg(p_actwk);
  bool axis_dir_changed = puka_puka(p_actwk);
  if (!axis_dir_changed) {
    speedset2(p_actwk);
    chk_gost08_limit(p_actwk);
  }
  else {
    p_actwk->r_no = 8;
    if (chk_puka_tbl[g_ram.soz_darkness_level] != 0) {
      p_actwk->u.obj.actfree.gost08.darkness_level = g_ram.soz_darkness_level;
      if (g_ram.soz_darkness_level == 5) {
        gost08_atak_init(p_actwk);
      }
      else {
        p_actwk->r_no = 4;
        set_puka_init(p_actwk);
      }
    }
  }
}


static void gost08_chg1(SKC_sprite_status* p_actwk) {
  static signed char* pg_tbl[3] = {
    gost08_chg_pg00,
    gost08_chg_pg00,
    gost08_chg_pg01
  };

  puka_puka(p_actwk);
  speedset2(p_actwk);
  chk_gost08_limit(p_actwk);
  int ret = time_pg(p_actwk);
  if (ret != 0 && p_actwk->patcnt == 2) {
    p_actwk->r_no = 10;
    p_actwk->u.obj.actfree.gost08.darkness_level = g_ram.soz_darkness_level;
    signed char* p_pg_data = pg_tbl[g_ram.soz_darkness_level / 2];
    p_actwk->patno = p_pg_data[0];
    pg_init(p_actwk, p_pg_data);
  }
}


static void gost08_chg2(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  chk_gost08_limit(p_actwk);
  int ret = time_pg(p_actwk);
  if (ret != 0) {
    p_actwk->r_no = 4;
  }
}


static void gost08_atak0(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  puka_puka(p_actwk);
  speedset2(p_actwk);
  if (p_actwk->xspeed >= 0) { // chk_r
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) <= 416) return;
  }
  else {// chk_l
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 160); return;
  }
  p_actwk->r_no = 14;
  p_actwk->actflg.hflip ^= 1;
  p_actwk->xspeed = -p_actwk->xspeed;
  p_actwk->u.obj.timer = 59;
}


static void gost08_atak1(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_no = 16;
    p_actwk->colino = 0xD7;
    p_actwk->actflg.relative_coordinates = 1;
    short xposi = fp16_get_integer(g_ram.scra_h_posit) + fp16_get_integer(p_actwk->xposi) - 128;
    fp16_set_integer(&p_actwk->xposi, xposi);
    short yposi = fp16_get_integer(g_ram.scra_v_posit) + fp16_get_integer(p_actwk->yposi) - 128;
    fp16_set_integer(&p_actwk->yposi, yposi);
    p_actwk->yspeed = 0x100;
  }
}


static void gost08_atak2(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  speedset2(p_actwk);
}


static void gost08_body_fout0(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  set_emy_wchg(p_actwk, &gost08_wrt_tbl);
  actionsub(p_actwk);
}


void setcg(SKC_sprite_status* p_actwk) {
  short* col_tbl[2] = {
    col_tbl_00,
    col_tbl_04
  };

  SKC_chk_emy_colt_result result = chk_emy_colt(p_actwk, col_tbl[p_actwk->u.obj.userflag / 4]);
  if (result.pl) {
    switch (p_actwk->u.obj.userflag / 4) {
      case 0:
        set_openbox_cg(p_actwk);
        break;
      case 1:
        set_emy08_cg(p_actwk);
        break;
    }

    frameout(p_actwk);
  }
}


static short col_tbl_00[4] = { -16, 32, -64, 128 };
static short col_tbl_04[4] = { -16, 32, -128, 256 };


static void set_openbox_cg(SKC_sprite_status* p_actwk) {
  SKC_cg_data opnbox_cg_tbl = {
    0,
    {
      { opnbox_cg, 0xA6C0 }
    }
  };

  divdevset2(&opnbox_cg_tbl);
}


static void set_emy08_cg(SKC_sprite_status* p_actwk) {
  enecginit();
}


void obox08(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &obox08_init_tbl);
  p_actwk->r_ptr = &obox04_wait0;
  p_actwk->u.obj.userflag = 3;
  set_act00(p_actwk, &obox08_switch_set_tbl);
  if (g_ram.markerno != 0 || g_ram.actwk[0].u.play.character == KNUCKLES) {
    p_actwk->r_ptr = &obox04_wait1;
    p_actwk->patno = 1;
    p_actwk->u.obj.actflg0.end = 1;
  }
}


static void obox08_switch(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &switch_init_tbl);
  p_actwk->r_ptr = &switch_wait0;
  if (g_ram.markerno != 0) {
    p_actwk->r_ptr = &switch_wait1;
    p_actwk->patno = 12;
  }
}


static void obox08_gost(SKC_sprite_status* p_actwk) {
  static SKC_sprite_status_handler act_tbl[3] = {
    &obox08_gost_init,
    &obox08_gost_move0,
    &obox08_gost_move1
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  if (p_actwk->u.obj.userflag == 0) {
    set_emy_wchg(p_actwk, &gost08_wrt_tbl);
    chk_emy_foutw0(p_actwk);
  }
  else {
    chk_emy_fout0(p_actwk);
  }
}


static void obox08_gost_init(SKC_sprite_status* p_actwk) {
  struct {
    short xspeed;
    short accel;
  }
  spd_tbl[6] = {
    { -0x200, -0x20 },
    {  0x200, -0x20 },
    { -0x280, -0x18 },
    {  0x280, -0x18 },
    { -0x300, -0x10 },
    {  0x300, -0x10 }
  };

  p_actwk->xspeed = spd_tbl[p_actwk->u.obj.userflag / 2].xspeed;
  p_actwk->u.obj.puka.accel = spd_tbl[p_actwk->u.obj.userflag / 2].accel;
  chk_emy_revs(p_actwk);
  if (p_actwk->u.obj.userflag == 0) {
    emy_wrt_init(p_actwk, &gost08_init_tbl);
  }
  else {
    enemy_init0(p_actwk, &obox08_gost_init_tbl);
  }
}


static void obox08_gost_move0(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, gost08_pg00);
  obox08_gost_move1(p_actwk);
}


static void obox08_gost_move1(SKC_sprite_status* p_actwk) {
  p_actwk->yspeed += p_actwk->u.obj.puka.accel;
  speedset2(p_actwk);
}


static void chk_gost08_limit(SKC_sprite_status* p_actwk) {
  if (p_actwk->xspeed >= 0) { // chk_r
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) <= 416) return;
  }
  else { // chk_l
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 160) return;
  }
  p_actwk->actflg.hflip ^= 1;
  p_actwk->xspeed = -p_actwk->xspeed;
}


void set_gost08(SKC_sprite_status* p_actwk) {
  g_ram.markerno = 1;
  g_ram.plxposi_s = playpositbl[SANDOPOLIS][ACT_2].x;
  g_ram.plyposi_s = playpositbl[SANDOPOLIS][ACT_2].y;
  playsave1(p_actwk);
  set_act00(p_actwk, &obox08_gost_set_tbl);
}


static void set_body_init(SKC_sprite_status* p_actwk) {
  signed char* pg_tbl[3] = {
    gost08_apar_pg00,
    gost08_apar_pg01,
    gost08_apar_pg02
  };

  short number = random() & 0xFF;
  number -= 127;
  p_actwk->xposi += number * 0x10000;
  short xspeed = gost08_init_spd_tbl[g_ram.soz_darkness_level];
  if ((unsigned short)number < 288) {
    p_actwk->actflg.hflip = 1;
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  p_actwk->u.obj.pg_data_ptr = pg_tbl[g_ram.soz_darkness_level / 2];
  set_puka_init(p_actwk);
}


static short gost08_init_spd_tbl[6] = {
  -0x100, -0x100, -0x100, -0x180, -0x180, -0x200
};


static void set_puka_init(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler puka_tbl[6] = {
    &puka_init_00,
    &puka_init_00,
    &puka_init_00,
    &puka_init_01,
    &puka_init_01,
    &puka_init_02
  };

  short xspeed = gost08_init_spd_tbl[g_ram.soz_darkness_level];
  if (p_actwk->xspeed >= 0) {
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  p_actwk->u.obj.actflg0.puka_down = 0;
  puka_tbl[g_ram.soz_darkness_level](p_actwk);
  short yspeed = g_ram.soz_darkness_level * 4;
  if (p_actwk->yspeed < 0) {
    p_actwk->u.obj.actflg0.puka_down = 1;
    yspeed = -yspeed;
  }
  p_actwk->yspeed = yspeed;
}


static void puka_init_00(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.accel_max = 0x40;
  p_actwk->u.obj.puka.accel = 4;
}


static void puka_init_01(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.accel_max = 0x80;
  p_actwk->u.obj.puka.accel = 8;
  p_actwk->u.obj.actflg0.puka_down = 0;
}


static void puka_init_02(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.accel_max = 0xC0;
  p_actwk->u.obj.puka.accel = 0x10;
  p_actwk->u.obj.actflg0.puka_down = 0;
}


static SKC_wrt_init_data gost08_init_tbl = {
  2,
  0xA500,
  18,
  0,
  gost08pat,
  PRI_0,
  16,
  20,
  0,
  0
};


static SKC_enemy_init0_data obox08_init_tbl = {
  openbox_pt,
  0x8536,
  PRI_3,
  48,
  64,
  0,
  0
};


static SKC_enemy_init0_data obox08_gost_init_tbl = {
  gost08pat,
  0xA500,
  PRI_4,
  48,
  32,
  0,
  0
};


static SKC_set_act00_data obox08_switch_set_tbl = {
  0,
  {
    { &obox08_switch, 0, -36 }
  }
};


static SKC_set_act00_data obox08_gost_set_tbl = {
  5,
  {
    { &obox08_gost,  -8, -4 },
    { &obox08_gost,   8, -4 },
    { &obox08_gost,  16, -4 },
    { &obox08_gost, -16, -4 },
    { &obox08_gost,  24, -4 },
    { &obox08_gost, -24, -4 }
  }
};


static SKC_set_act05_data gost08_body_set_tbl = {
  0,
  &gost08_body
};


static SKC_wrt_data gost08_wrt_tbl = {
  gost08_cg,
  gost08_tbl
};


static signed char gost08_apar_pg00[12] = { 17,  3, 17,  3, 16,  3, 15,  4, 14,  4, -8, 12 };
static signed char gost08_pg00[7] =       {  0,  3,  1,  3,  2,  4, -4 };
static signed char gost08_apar_pg01[14] = { 17,  3, 17,  3, 16,  3, 15,  4, 14,  4, 13,  4, -8, 14 };
static signed char gost08_pg01[7] =       {  5,  3,  6,  3,  7,  4, -4 };
static signed char gost08_apar_pg02[14] = { 17,  3, 17,  3, 16,  3, 15,  4, 14,  4, 13,  4, -8, 14 };
static signed char gost08_pg02[7] =       { 10,  3, 11,  3, 12,  4, -4 };
static signed char gost08_away_pg00[13] = { 13,  4, 13,  4, 14,  4, 15,  4, 16,  3, 17,  3, -12 };
static signed char gost08_chg_pg00[8] =   {  3,  7,  3,  7,  4,  7, -8, -41 };
static signed char gost08_chg_pg01[8] =   {  8,  7,  8,  7,  9,  7, -8, -28 };


static unsigned short* gost08_tbl[18] = {
  gost08_tbl00,
  gost08_tbl01,
  gost08_tbl02,
  gost08_tbl03,
  gost08_tbl04,
  gost08_tbl05,
  gost08_tbl06,
  gost08_tbl07,
  gost08_tbl08,
  gost08_tbl09,
  gost08_tbl10,
  gost08_tbl11,
  gost08_tbl12,
  gost08_tbl13,
  gost08_tbl14,
  gost08_tbl15,
  gost08_tbl16,
  gost08_tbl17
};


static unsigned short gost08_tbl00[2] = { 0, 0x008 };
static unsigned short gost08_tbl01[2] = { 0, 0x098 };
static unsigned short gost08_tbl02[2] = { 0, 0x128 };
static unsigned short gost08_tbl03[2] = { 0, 0x1B8 };
static unsigned short gost08_tbl04[2] = { 0, 0x248 };
static unsigned short gost08_tbl05[2] = { 0, 0x2D8 };
static unsigned short gost08_tbl06[2] = { 0, 0x368 };
static unsigned short gost08_tbl07[2] = { 0, 0x3F8 };
static unsigned short gost08_tbl08[2] = { 0, 0x48F };
static unsigned short gost08_tbl09[3] = { 1, 0x585, 0x5EB };
static unsigned short gost08_tbl10[3] = { 1, 0x6A5, 0x70B };
static unsigned short gost08_tbl11[3] = { 1, 0x7C5, 0x82B };
static unsigned short gost08_tbl12[3] = { 1, 0x6A5, 0x8EB };
static unsigned short gost08_tbl13[2] = { 0, 0x9A8 };
static unsigned short gost08_tbl14[2] = { 0, 0xA38 };
static unsigned short gost08_tbl15[2] = { 0, 0xAC3 };
static unsigned short gost08_tbl16[2] = { 0, 0xB03 };
static unsigned short gost08_tbl17[2] = { 0, 0xB40 };
