#include "../globals.h"
#include "../macros.h"
#include "../util.h"
#include "gost08.h"
#include "gost08_data.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"
static void gost08_ctr(sprite_status* pActwk);
static void gost08_body(sprite_status* pActwk);
static void gost08_body__fout0(sprite_status* pActwk);
static void gost08_body__fout1(sprite_status* pActwk);
static void gost08_init(sprite_status* pActwk);
static void gost08_wait0(sprite_status* pActwk);
static void gost08_atak_init(sprite_status* pActwk);
static void gost08_move0(sprite_status* pActwk);
static void gost08_chg0(sprite_status* pActwk);
static void gost08_chg1(sprite_status* pActwk);
static void gost08_chg2(sprite_status* pActwk);
static void gost08_atak0(sprite_status* pActwk);
static void gost08_atak1(sprite_status* pActwk);
static void gost08_atak2(sprite_status* pActwk);
static void gost08_body_fout0(sprite_status* pActwk);
static void set_openbox_cg(sprite_status* pActwk);
static void set_emy08_cg(sprite_status* pActwk);
static void obox08_switch(sprite_status* pActwk);
static void obox08_gost(sprite_status* pActwk);
static void obox08_gost_init(sprite_status* pActwk);
static void obox08_gost_move0(sprite_status* pActwk);
static void obox08_gost_move1(sprite_status* pActwk);
static void chk_gost08_limit(sprite_status* pActwk);
static void set_body_init(sprite_status* pActwk);
static void set_puka_init(sprite_status* pActwk);
static void puka_init_00(sprite_status* pActwk);
static void puka_init_01(sprite_status* pActwk);
static void puka_init_02(sprite_status* pActwk);


void gost08(sprite_status* pActwk) {
  pActwk->r_ptr = &gost08_ctr;
  pActwk->xposi = SHORT_TO_LONG_HIGH(288);
  pActwk->yposi = SHORT_TO_LONG_HIGH(160);
  gost08_ctr(pActwk);
}


static set_act05_data gost08_body_set_tbl = {
  0,
  &gost08_body
};


static void gost08_ctr(sprite_status* pActwk) {
  static unsigned char cnt_tbl[6] = {
    0, 1, 2, 2, 3, 3
  };

  if (SPRITE_STATUS_UCHAR(&actwk[0], 56) != KNUCKLES && markerno == 0) return;
  if (soz_darkness_level != 0) {
    unsigned char cnt = cnt_tbl[soz_darkness_level];
    if (soz_ghosts >= cnt) return; // unsigned
    --SPRITE_STATUS_SHORT(pActwk, 58);
    if (SPRITE_STATUS_SHORT(pActwk, 58) >= 0) return;
    ++soz_ghosts;
    if (soz_ghosts <= cnt) { // unsigned
      SPRITE_STATUS_SHORT(pActwk, 58) = 63;
    }
    set_act05(pActwk, &gost08_body_set_tbl);
  }
  else {
    soz_ghosts = 0;
  }
}


static void gost08_body(sprite_status* pActwk) {
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

  act_tbl[pActwk->r_no / 2](pActwk);
  set_emy_wchg(pActwk, &gost08_wrt_tbl);
  if (!BIT_7_IS_SET(pActwk->actflg)) {
    gost08_body__fout0(pActwk);
    return;
  }
  if (soz_darkness_level == 0) {
    gost08_body__fout1(pActwk);
    return;
  }
  sprite_status* pColiActwk;
  bool collided = chk_emy_col(pActwk, &pColiActwk);
  if (collided) {
    bool attacked = chk_pl_attack(pActwk, pColiActwk);
    if (attacked) {
      gost08_body__fout1(pActwk);
      return;
    }
    if (SPRITE_STATUS_UCHAR(pColiActwk, 52) == 0) {
      set_pl_damage(pActwk, pColiActwk);
    }
  }
  Add_Object_To_Collision_Response_List(pActwk);
  actionsub(pActwk);
}


static void gost08_body__fout0(sprite_status* pActwk) {
  --soz_ghosts;
  set_wchg_fout0(pActwk);
}


static void gost08_body__fout1(sprite_status* pActwk) {
  pActwk->r_ptr = &gost08_body_fout0;
  SPRITE_STATUS_PHANDLER(pActwk, 52) = &gost08_body_fout0;
  pg_init(pActwk, gost08_away_pg00);
  soundset(-118);
  actionsub(pActwk);
}


static void gost08_init(sprite_status* pActwk) {
  emy_wrt_init(pActwk, &gost08_init_tbl);
  CLEAR_BIT_2(pActwk->actflg);
  SET_BIT_7(pActwk->actflg);
  SPRITE_STATUS_UCHAR(pActwk, 66) = soz_darkness_level;
  SPRITE_STATUS_UCHAR(pActwk, 67) = soz_ghosts;
  set_body_init(pActwk);
  soundset(-110);
  gost08_wait0(pActwk);
}


static void gost08_wait0(sprite_status* pActwk) {
  int ret = time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  if (ret == 0) return;
  if (soz_darkness_level == 5) {
    gost08_atak_init(pActwk);
  }
  else {
    pActwk->r_no = 4;
  }
}


static void gost08_atak_init(sprite_status* pActwk) {
  pActwk->r_no = 12;
  set_puka_init(pActwk);
}


static void gost08_move0(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  puka_puka(pActwk);
  speedset2(pActwk);
  chk_gost08_limit(pActwk);
  if (soz_darkness_level != SPRITE_STATUS_UCHAR(pActwk, 66)) {
    pActwk->r_no = 6;
  }
}


static void gost08_chg0(sprite_status* pActwk) {
  static unsigned char chk_puka_tbl[6] = {
    0, 0, 0, 1, 0, 1
  };

  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  bool axis_dir_changed = puka_puka(pActwk);
  if (!axis_dir_changed) {
    speedset2(pActwk);
    chk_gost08_limit(pActwk);
  }
  else {
    pActwk->r_no = 8;
    if (chk_puka_tbl[soz_darkness_level] == 0) return;
    SPRITE_STATUS_UCHAR(pActwk, 66) = soz_darkness_level;
    if (soz_darkness_level == 5) {
      gost08_atak_init(pActwk);
    }
    else {
      pActwk->r_no = 4;
      set_puka_init(pActwk);
    }
  }
}


static void gost08_chg1(sprite_status* pActwk) {
  static signed char* pg_tbl[3] = {
    gost08_chg_pg00,
    gost08_chg_pg00,
    gost08_chg_pg01
  };

  puka_puka(pActwk);
  speedset2(pActwk);
  chk_gost08_limit(pActwk);
  int ret = time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  if (ret != 0 && pActwk->patcnt == 2) {
    pActwk->r_no = 10;
    SPRITE_STATUS_UCHAR(pActwk, 66) = soz_darkness_level;
    signed char* pPgData = pg_tbl[(soz_darkness_level * 2 & 12) / 4];
    pActwk->patno = pPgData[0];
    pg_init(pActwk, pPgData);
  }
}


static void gost08_chg2(sprite_status* pActwk) {
  puka_puka(pActwk);
  speedset2(pActwk);
  chk_gost08_limit(pActwk);
  int ret = time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  if (ret != 0) {
    pActwk->r_no = 4;
  }
}


static void gost08_atak0(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  puka_puka(pActwk);
  speedset2(pActwk);
  short xposi = LONG_HIGH_TO_SHORT(pActwk->xposi);
  if (pActwk->xspeed >= 0) {
    // chk_r
    if (util__to_unsigned(xposi) <= 416) return; // unsigned
  }
  else {
    // chk_l
    if (util__to_unsigned(xposi) >= 160); return; // unsigned
  }
  pActwk->r_no = 14;
  CLEAR_BIT_0(pActwk->actflg);
  pActwk->xspeed = -pActwk->xspeed;
  SPRITE_STATUS_SHORT(pActwk, 46) = 59;
}


static void gost08_atak1(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  --SPRITE_STATUS_SHORT(pActwk, 46);
  if (SPRITE_STATUS_SHORT(pActwk, 46) >= 0) return;
  pActwk->r_no = 16;
  pActwk->colino = 215;
  SET_BIT_2(pActwk->actflg);
  pActwk->xposi = LONG_HIGH(scra_h_posit) + (pActwk->xposi - SHORT_TO_LONG_HIGH(128));
  pActwk->yposi = LONG_HIGH(scra_v_posit) + (pActwk->yposi - SHORT_TO_LONG_HIGH(128));
  pActwk->yspeed = 256;
}


static void gost08_atak2(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  speedset2(pActwk);
}


static void gost08_body_fout0(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  set_emy_wchg(pActwk, &gost08_wrt_tbl);
  actionsub(pActwk);
}


void setcg(sprite_status* pActwk) {
  static short* col_tbl[2] = {
    col_tbl_00,
    col_tbl_04
  };

  sprite_status* pPlayerwk = chk_emy_colt(pActwk, col_tbl[pActwk->userflag1]);
  if (pPlayerwk == 0) return;

  switch (pActwk->userflag1) {
    case 0:
      set_openbox_cg(pActwk);
      break;
    case 4:
      set_emy08_cg(pActwk);
      break;
  }

  frameout(pActwk);
}


static void set_openbox_cg(sprite_status* pActwk) {
  static cg_data opnbox_cg_tbl = {
    0,
    {
      { opnbox_tiles, 42688 }
    }
  };

  Load_PLC_Raw(pActwk, &opnbox_cg_tbl);
}


static void set_emy08_cg(sprite_status* pActwk) {
  LoadEnemyArt();
}


static set_act00_data obox08_switch_set_tbl = {
  0,
  {
    { &obox08_switch, 0, -36 }
  }
};


void obox08(sprite_status* pActwk) {
  enemy_init0(pActwk, &obox08_init_tbl);
  pActwk->r_ptr = &obox04_wait0;
  pActwk->userflag1 = 3;
  set_act00(pActwk, &obox08_switch_set_tbl);
  if (markerno == 0 && SPRITE_STATUS_UCHAR(&actwk[0], 56) != KNUCKLES) return;
  pActwk->r_ptr = &obox04_wait1;
  pActwk->patno = 1;
  SET_BIT_5(SPRITE_STATUS_UCHAR(pActwk, 56));
}


static void obox08_switch(sprite_status* pActwk) {
  enemy_init2(pActwk, &switch_init_tbl);
  pActwk->r_ptr = &switch_wait0;
  if (markerno != 0) {
    pActwk->r_ptr = &switch_wait1;
    pActwk->patno = 12;
  }
}


static void obox08_gost(sprite_status* pActwk) {
  static sprite_status_handler act_tbl[3] = {
    &obox08_gost_init,
    &obox08_gost_move0,
    &obox08_gost_move1
  };

  act_tbl[pActwk->r_no / 2](pActwk);
  if (pActwk->userflag1 == 0) {
    set_emy_wchg(pActwk, &gost08_wrt_tbl);
    chk_emy_foutw0(pActwk);
  }
  else {
    chk_emy_fout0(pActwk);
  }
}


static void obox08_gost_init(sprite_status* pActwk) {
  static short spd_tbl[12] = {
    -512, -32,
     512, -32,
    -640, -24,
     640, -24,
    -768, -16,
     768, -16
  };

  pActwk->xspeed = spd_tbl[pActwk->userflag1];
  SPRITE_STATUS_SHORT(pActwk, 64) = spd_tbl[pActwk->userflag1 + 1];
  chk_emy_revs(pActwk);
  if (pActwk->userflag1 == 0) {
    emy_wrt_init(pActwk, &gost08_init_tbl);
  }
  else {
    enemy_init0(pActwk, &obox08_gost_init_tbl);
  }
}


static void obox08_gost_move0(sprite_status* pActwk) {
  pt_chg0(pActwk, gost08_pg00);
  obox08_gost_move1(pActwk);
}


static void obox08_gost_move1(sprite_status* pActwk) {
  pActwk->yspeed += SPRITE_STATUS_SHORT(pActwk, 64);
  speedset2(pActwk);
}


static void chk_gost08_limit(sprite_status* pActwk) {
  short xposi = LONG_HIGH_TO_SHORT(pActwk->xposi);
  if (pActwk->xspeed >= 0) {
    // chk_r
    if (util__to_unsigned(xposi) <= 416) return; // unsigned
  }
  else {
    // chk_l
    if (util__to_unsigned(xposi) >= 160) return; // unsigned
  }
  CLEAR_BIT_0(pActwk->actflg);
  pActwk->xspeed = -pActwk->xspeed;
}


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


void set_gost08(sprite_status* pActwk) {
  markerno = 1;
  plxposi_s = SOZ2_start[0];
  plyposi_s = SOZ2_start[1];
  playsave1(pActwk);
  set_act00(pActwk, &obox08_gost_set_tbl);
}


static void set_body_init(sprite_status* pActwk) {
  signed char* pg_tbl[3] = {
    gost08_apar_pg00,
    gost08_apar_pg01,
    gost08_apar_pg02
  };

  short number = random() & 255;
  number -= 127;
  pActwk->xposi += SHORT_TO_LONG_HIGH(number);
  short xspeed = gost08_init_spd_tbl[soz_darkness_level];
  if (util__to_unsigned(number) < 288) { // unsigned
    SET_BIT_0(pActwk->actflg);
    xspeed = -xspeed;
  }
  pActwk->xspeed = xspeed;
  SPRITE_STATUS_PSCHAR(pActwk, 48) = pg_tbl[(soz_darkness_level * 2 & 12) / 4];
  set_puka_init(pActwk);
}


static void set_puka_init(sprite_status* pActwk) {
  static sprite_status_handler puka_tbl[6] = {
    &puka_init_00,
    &puka_init_00,
    &puka_init_00,
    &puka_init_01,
    &puka_init_01,
    &puka_init_02
  };

  short xspeed = gost08_init_spd_tbl[soz_darkness_level];
  if (pActwk->xspeed >= 0) {
    xspeed = -xspeed;
  }
  pActwk->xspeed = xspeed;
  CLEAR_BIT_0(SPRITE_STATUS_UCHAR(pActwk, 56));
  puka_tbl[soz_darkness_level](pActwk);
  short yspeed = soz_darkness_level * 4;
  if (pActwk->yspeed < 0) {
    SET_BIT_0(SPRITE_STATUS_UCHAR(pActwk, 56));
    yspeed = -yspeed;
  }
  pActwk->yspeed = yspeed;
}


static void puka_init_00(sprite_status* pActwk) {
  SPRITE_STATUS_SHORT(pActwk, 62) = 64;
  SPRITE_STATUS_SHORT(pActwk, 64) = 4;
}


static void puka_init_01(sprite_status* pActwk) {
  SPRITE_STATUS_SHORT(pActwk, 62) = 128;
  SPRITE_STATUS_SHORT(pActwk, 64) = 8;
  CLEAR_BIT_0(SPRITE_STATUS_UCHAR(pActwk, 56));
}


static void puka_init_02(sprite_status* pActwk) {
  SPRITE_STATUS_SHORT(pActwk, 62) = 192;
  SPRITE_STATUS_SHORT(pActwk, 64) = 16;
  CLEAR_BIT_0(SPRITE_STATUS_UCHAR(pActwk, 56));
}
