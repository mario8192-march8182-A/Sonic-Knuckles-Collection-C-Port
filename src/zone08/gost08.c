#include "../globals.h"
#include "../macros.h"
#include "../util.h"
#include "gost08.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"
#include "../opnbox.h"
#include "../resources.h"
#include "../save.h"
#include "../zone_data.h"
#include "../zone04/obox04.h"
static void gost08_ctr(sprite_status* p_actwk);
static void gost08_body(sprite_status* p_actwk);
static void gost08_body__fout0(sprite_status* p_actwk);
static void gost08_body__fout1(sprite_status* p_actwk);
static void gost08_init(sprite_status* p_actwk);
static void gost08_wait0(sprite_status* p_actwk);
static void gost08_atak_init(sprite_status* p_actwk);
static void gost08_move0(sprite_status* p_actwk);
static void gost08_chg0(sprite_status* p_actwk);
static void gost08_chg1(sprite_status* p_actwk);
static void gost08_chg2(sprite_status* p_actwk);
static void gost08_atak0(sprite_status* p_actwk);
static void gost08_atak1(sprite_status* p_actwk);
static void gost08_atak2(sprite_status* p_actwk);
static void gost08_body_fout0(sprite_status* p_actwk);
static short col_tbl_00[4];
static short col_tbl_04[4];
static void set_openbox_cg(sprite_status* p_actwk);
static void set_emy08_cg(sprite_status* p_actwk);
static void obox08_switch(sprite_status* p_actwk);
static void obox08_gost(sprite_status* p_actwk);
static void obox08_gost_init(sprite_status* p_actwk);
static void obox08_gost_move0(sprite_status* p_actwk);
static void obox08_gost_move1(sprite_status* p_actwk);
static void chk_gost08_limit(sprite_status* p_actwk);
static void set_body_init(sprite_status* p_actwk);
static short gost08_init_spd_tbl[6];
static void set_puka_init(sprite_status* p_actwk);
static void puka_init_00(sprite_status* p_actwk);
static void puka_init_01(sprite_status* p_actwk);
static void puka_init_02(sprite_status* p_actwk);
static wrt_init_data gost08_init_tbl;
static enemy_init0_data obox08_init_tbl;
static enemy_init0_data obox08_gost_init_tbl;
static set_act00_data obox08_switch_set_tbl;
static set_act00_data obox08_gost_set_tbl;
static set_act05_data gost08_body_set_tbl;
static wrt_data gost08_wrt_tbl;
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


void gost08(sprite_status* p_actwk) {
  p_actwk->r_ptr = &gost08_ctr;
  util__assign_high(&p_actwk->xposi, 288);
  util__assign_high(&p_actwk->yposi, 160);
  gost08_ctr(p_actwk);
}


static void gost08_ctr(sprite_status* p_actwk) {
  static unsigned char cnt_tbl[6] = {
    0, 1, 2, 2, 3, 3
  };

  if (actwk[0].actfree.player.character != KNUCKLES && markerno == 0) return;
  if (soz_darkness_level != 0) {
    unsigned char cnt = cnt_tbl[soz_darkness_level];
    if (soz_ghosts >= cnt) return; // unsigned
    --p_actwk->actfree.gost08_ctr.ghost_countdown;
    if (p_actwk->actfree.gost08_ctr.ghost_countdown >= 0) return;
    ++soz_ghosts;
    if (soz_ghosts <= cnt) { // unsigned
      p_actwk->actfree.gost08_ctr.ghost_countdown = 63;
    }
    set_act05(p_actwk, &gost08_body_set_tbl);
  }
  else {
    soz_ghosts = 0;
  }
}


static void gost08_body(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[9] = {
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
  if (!BIT_7_IS_SET(p_actwk->actflg)) {
    gost08_body__fout0(p_actwk);
    return;
  }
  if (soz_darkness_level == 0) {
    gost08_body__fout1(p_actwk);
    return;
  }
  sprite_status* p_coli_actwk;
  bool collision = chk_emy_col(p_actwk, &p_coli_actwk);
  if (collision) {
    bool attacked = chk_pl_attack(p_actwk, p_coli_actwk);
    if (attacked) {
      gost08_body__fout1(p_actwk);
      return;
    }
    if (p_coli_actwk->actfree.player.invulnerability_timer == 0) {
      set_pl_damage(p_actwk, p_coli_actwk);
    }
  }
  Add_Object_To_Collision_Response_List(p_actwk);
  actionsub(p_actwk);
}


static void gost08_body__fout0(sprite_status* p_actwk) {
  --soz_ghosts;
  set_wchg_fout0(p_actwk);
}


static void gost08_body__fout1(sprite_status* p_actwk) {
  p_actwk->r_ptr = &gost08_body_fout0;
  p_actwk->actfree.gost08.callback_ptr = &gost08_body_fout0;
  pg_init(p_actwk, gost08_away_pg00);
  soundset(-118);
  actionsub(p_actwk);
}


static void gost08_init(sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &gost08_init_tbl);
  CLEAR_BIT_2(p_actwk->actflg);
  SET_BIT_7(p_actwk->actflg);
  p_actwk->actfree.gost08.darkness_level = soz_darkness_level;
  p_actwk->actfree.gost08.sequence_no = soz_ghosts;
  set_body_init(p_actwk);
  soundset(-110);
  gost08_wait0(p_actwk);
}


static void gost08_wait0(sprite_status* p_actwk) {
  int ret = time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  if (ret == 0) return;
  if (soz_darkness_level == 5) {
    gost08_atak_init(p_actwk);
  }
  else {
    p_actwk->r_no = 4;
  }
}


static void gost08_atak_init(sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  set_puka_init(p_actwk);
}


static void gost08_move0(sprite_status* p_actwk) {
  time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  puka_puka(p_actwk);
  speedset2(p_actwk);
  chk_gost08_limit(p_actwk);
  if (soz_darkness_level != p_actwk->actfree.gost08.darkness_level) {
    p_actwk->r_no = 6;
  }
}


static void gost08_chg0(sprite_status* p_actwk) {
  static unsigned char chk_puka_tbl[6] = {
    0, 0, 0, 1, 0, 1
  };

  time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  bool axis_dir_changed = puka_puka(p_actwk);
  if (!axis_dir_changed) {
    speedset2(p_actwk);
    chk_gost08_limit(p_actwk);
  }
  else {
    p_actwk->r_no = 8;
    if (chk_puka_tbl[soz_darkness_level] == 0) return;
    p_actwk->actfree.gost08.darkness_level = soz_darkness_level;
    if (soz_darkness_level == 5) {
      gost08_atak_init(p_actwk);
    }
    else {
      p_actwk->r_no = 4;
      set_puka_init(p_actwk);
    }
  }
}


static void gost08_chg1(sprite_status* p_actwk) {
  static signed char* pg_tbl[3] = {
    gost08_chg_pg00,
    gost08_chg_pg00,
    gost08_chg_pg01
  };

  puka_puka(p_actwk);
  speedset2(p_actwk);
  chk_gost08_limit(p_actwk);
  int ret = time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  if (ret != 0 && p_actwk->patcnt == 2) {
    p_actwk->r_no = 10;
    p_actwk->actfree.gost08.darkness_level = soz_darkness_level;
    signed char* p_pg_data = pg_tbl[(soz_darkness_level * 2 & 12) / 4];
    p_actwk->patno = p_pg_data[0];
    pg_init(p_actwk, p_pg_data);
  }
}


static void gost08_chg2(sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  chk_gost08_limit(p_actwk);
  int ret = time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  if (ret != 0) {
    p_actwk->r_no = 4;
  }
}


static void gost08_atak0(sprite_status* p_actwk) {
  time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  puka_puka(p_actwk);
  speedset2(p_actwk);
  short xposi = LONG_HIGH_TO_SHORT(p_actwk->xposi);
  if (p_actwk->xspeed >= 0) {
    // chk_r
    if (util__to_unsigned(xposi) <= 416) return; // unsigned
  }
  else {
    // chk_l
    if (util__to_unsigned(xposi) >= 160); return; // unsigned
  }
  p_actwk->r_no = 14;
  TOGGLE_BIT_0(p_actwk->actflg);
  p_actwk->xspeed = -p_actwk->xspeed;
  p_actwk->actfree.gost08.attack_countdown = 59;
}


static void gost08_atak1(sprite_status* p_actwk) {
  time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  --p_actwk->actfree.gost08.attack_countdown;
  if (p_actwk->actfree.gost08.attack_countdown >= 0) return;
  p_actwk->r_no = 16;
  p_actwk->colino = 215;
  SET_BIT_2(p_actwk->actflg);
  short xposi = LONG_HIGH_TO_SHORT(scra_h_posit) + (LONG_HIGH_TO_SHORT(p_actwk->xposi) - 128);
  util__assign_high(&p_actwk->xposi, xposi);
  short yposi = LONG_HIGH_TO_SHORT(scra_v_posit) + (LONG_HIGH_TO_SHORT(p_actwk->yposi) - 128);
  util__assign_high(&p_actwk->yposi, yposi);
  p_actwk->yspeed = 256;
}


static void gost08_atak2(sprite_status* p_actwk) {
  time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  speedset2(p_actwk);
}


static void gost08_body_fout0(sprite_status* p_actwk) {
  time_pg(p_actwk, p_actwk->actfree.gost08.pg_data_ptr);
  set_emy_wchg(p_actwk, &gost08_wrt_tbl);
  actionsub(p_actwk);
}


void setcg(sprite_status* p_actwk) {
  static short* col_tbl[2] = {
    col_tbl_00,
    col_tbl_04
  };

  sprite_status* p_playerwk = chk_emy_colt(p_actwk, col_tbl[p_actwk->userflag1]);
  if (p_playerwk == 0) return;

  switch (p_actwk->userflag1) {
    case 0:
      set_openbox_cg(p_actwk);
      break;
    case 4:
      set_emy08_cg(p_actwk);
      break;
  }

  frameout(p_actwk);
}


static short col_tbl_00[4] = { -16, 32, -64, 128 };
static short col_tbl_04[4] = { -16, 32, -128, 256 };


static void set_openbox_cg(sprite_status* p_actwk) {
  static cg_data opnbox_cg_tbl = {
    0,
    {
      { opnbox_tiles, 42688 }
    }
  };

  Load_PLC_Raw(p_actwk, &opnbox_cg_tbl);
}


static void set_emy08_cg(sprite_status* p_actwk) {
  LoadEnemyArt();
}


void obox08(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &obox08_init_tbl);
  p_actwk->r_ptr = &obox04_wait0;
  p_actwk->userflag1 = 3;
  set_act00(p_actwk, &obox08_switch_set_tbl);
  if (markerno == 0 && actwk[0].actfree.player.character != KNUCKLES) return;
  p_actwk->r_ptr = &obox04_wait1;
  p_actwk->patno = 1;
  SET_BIT_5(p_actwk->actfree.obox04.status_bitfield);
}


static void obox08_switch(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &switch_init_tbl);
  p_actwk->r_ptr = &switch_wait0;
  if (markerno != 0) {
    p_actwk->r_ptr = &switch_wait1;
    p_actwk->patno = 12;
  }
}


static void obox08_gost(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[3] = {
    &obox08_gost_init,
    &obox08_gost_move0,
    &obox08_gost_move1
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  if (p_actwk->userflag1 == 0) {
    set_emy_wchg(p_actwk, &gost08_wrt_tbl);
    chk_emy_foutw0(p_actwk);
  }
  else {
    chk_emy_fout0(p_actwk);
  }
}


static void obox08_gost_init(sprite_status* p_actwk) {
  static short spd_tbl[12] = {
    -512, -32,
     512, -32,
    -640, -24,
     640, -24,
    -768, -16,
     768, -16
  };

  p_actwk->xspeed = spd_tbl[p_actwk->userflag1];
  p_actwk->actfree.gost08.accel = spd_tbl[p_actwk->userflag1 + 1];
  chk_emy_revs(p_actwk);
  if (p_actwk->userflag1 == 0) {
    emy_wrt_init(p_actwk, &gost08_init_tbl);
  }
  else {
    enemy_init0(p_actwk, &obox08_gost_init_tbl);
  }
}


static void obox08_gost_move0(sprite_status* p_actwk) {
  pt_chg0(p_actwk, gost08_pg00);
  obox08_gost_move1(p_actwk);
}


static void obox08_gost_move1(sprite_status* p_actwk) {
  p_actwk->yspeed += p_actwk->actfree.gost08.accel;
  speedset2(p_actwk);
}


static void chk_gost08_limit(sprite_status* p_actwk) {
  short xposi = LONG_HIGH_TO_SHORT(p_actwk->xposi);
  if (p_actwk->xspeed >= 0) {
    // chk_r
    if (util__to_unsigned(xposi) <= 416) return; // unsigned
  }
  else {
    // chk_l
    if (util__to_unsigned(xposi) >= 160) return; // unsigned
  }
  TOGGLE_BIT_0(p_actwk->actflg);
  p_actwk->xspeed = -p_actwk->xspeed;
}


void set_gost08(sprite_status* p_actwk) {
  markerno = 1;
  plxposi_s = SOZ2_start[0];
  plyposi_s = SOZ2_start[1];
  playsave1(p_actwk);
  set_act00(p_actwk, &obox08_gost_set_tbl);
}


static void set_body_init(sprite_status* p_actwk) {
  signed char* pg_tbl[3] = {
    gost08_apar_pg00,
    gost08_apar_pg01,
    gost08_apar_pg02
  };

  short number = random() & 255;
  number -= 127;
  p_actwk->xposi += SHORT_TO_LONG_HIGH(number);
  short xspeed = gost08_init_spd_tbl[soz_darkness_level];
  if (util__to_unsigned(number) < 288) { // unsigned
    SET_BIT_0(p_actwk->actflg);
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  p_actwk->actfree.gost08.pg_data_ptr = pg_tbl[(soz_darkness_level * 2 & 12) / 4];
  set_puka_init(p_actwk);
}


static short gost08_init_spd_tbl[6] = {
  -256, -256, -256, -384, -384, -512
};


static void set_puka_init(sprite_status* p_actwk) {
  static sprite_status_handler puka_tbl[6] = {
    &puka_init_00,
    &puka_init_00,
    &puka_init_00,
    &puka_init_01,
    &puka_init_01,
    &puka_init_02
  };

  short xspeed = gost08_init_spd_tbl[soz_darkness_level];
  if (p_actwk->xspeed >= 0) {
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  CLEAR_BIT_0(p_actwk->actfree.gost08.puka_axis_dir);
  puka_tbl[soz_darkness_level](p_actwk);
  short yspeed = soz_darkness_level * 4;
  if (p_actwk->yspeed < 0) {
    SET_BIT_0(p_actwk->actfree.gost08.puka_axis_dir);
    yspeed = -yspeed;
  }
  p_actwk->yspeed = yspeed;
}


static void puka_init_00(sprite_status* p_actwk) {
  p_actwk->actfree.gost08.accel_max = 64;
  p_actwk->actfree.gost08.accel = 4;
}


static void puka_init_01(sprite_status* p_actwk) {
  p_actwk->actfree.gost08.accel_max = 128;
  p_actwk->actfree.gost08.accel = 8;
  CLEAR_BIT_0(p_actwk->actfree.gost08.puka_axis_dir);
}


static void puka_init_02(sprite_status* p_actwk) {
  p_actwk->actfree.gost08.accel_max = 192;
  p_actwk->actfree.gost08.accel = 16;
  CLEAR_BIT_0(p_actwk->actfree.gost08.puka_axis_dir);
}


static wrt_init_data gost08_init_tbl = {
  2,
  42240,
  18,
  0,
  gost08pat,
  PRI_0,
  16,
  20,
  0,
  0
};


static enemy_init0_data obox08_init_tbl = {
  openbox_pt,
  34102,
  PRI_3,
  48,
  64,
  0,
  0
};


static enemy_init0_data obox08_gost_init_tbl = {
  gost08pat,
  42240,
  PRI_4,
  48,
  32,
  0,
  0
};


static set_act00_data obox08_switch_set_tbl = {
  0,
  {
    { &obox08_switch, 0, -36 }
  }
};


static set_act00_data obox08_gost_set_tbl = {
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


static set_act05_data gost08_body_set_tbl = {
  0,
  &gost08_body
};


static wrt_data gost08_wrt_tbl = {
  gost08_tiles,
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


static unsigned short gost08_tbl00[2] = { 0,    8 };
static unsigned short gost08_tbl01[2] = { 0,  152 };
static unsigned short gost08_tbl02[2] = { 0,  296 };
static unsigned short gost08_tbl03[2] = { 0,  440 };
static unsigned short gost08_tbl04[2] = { 0,  584 };
static unsigned short gost08_tbl05[2] = { 0,  728 };
static unsigned short gost08_tbl06[2] = { 0,  872 };
static unsigned short gost08_tbl07[2] = { 0, 1016 };
static unsigned short gost08_tbl08[2] = { 0, 1167 };
static unsigned short gost08_tbl09[3] = { 1, 1413, 1515 };
static unsigned short gost08_tbl10[3] = { 1, 1701, 1803 };
static unsigned short gost08_tbl11[3] = { 1, 1989, 2091 };
static unsigned short gost08_tbl12[3] = { 1, 1701, 2283 };
static unsigned short gost08_tbl13[2] = { 0, 2472 };
static unsigned short gost08_tbl14[2] = { 0, 2616 };
static unsigned short gost08_tbl15[2] = { 0, 2755 };
static unsigned short gost08_tbl16[2] = { 0, 2819 };
static unsigned short gost08_tbl17[2] = { 0, 2880 };
