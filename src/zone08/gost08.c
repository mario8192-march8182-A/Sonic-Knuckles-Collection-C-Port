#include <stdlib.h>
#include "../globals.h"
#include "../macros.h"
#include "gost08.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"

short col_tbl_00[4] = { -16, 32, -64, 128 };
short col_tbl_04[4] = { -16, 32, -128, 256 };

enemy_init0_data obox08_init_tbl = {
  openbox_pt,
  34102,
  384,
  48,
  64,
  0,
  0
};

set_act00_data obox08_switch_set_tbl = {
  0,
  { { &obox08_switch, 0, -36 } }
};

wrt_init_data gost08_init_tbl = {
  2,
  42240,
  18,
  0,
  gost08pat,
  0,
  16,
  20,
  0,
  0
};

set_act05_data gost08_body_set_tbl = {
  0,
  &gost08_body
};

signed char gost08_away_pg00[13] = { 13, 4, 13, 4, 14, 4, 15, 4, 16, 3, 17, 3, -12 };
signed char gost08_chg_pg00[8] = { 3, 7, 3, 7, 4, 7, -8, -41 };
signed char gost08_chg_pg01[8] = { 8, 7, 8, 7, 9, 7, -8, -28 };

unsigned short gost08_tbl00[2] = { 0, 8 };
unsigned short gost08_tbl01[2] = { 0, 152 };
unsigned short gost08_tbl02[2] = { 0, 296 };
unsigned short gost08_tbl03[2] = { 0, 440 };
unsigned short gost08_tbl04[2] = { 0, 584 };
unsigned short gost08_tbl05[2] = { 0, 728 };
unsigned short gost08_tbl06[2] = { 0, 872 };
unsigned short gost08_tbl07[2] = { 0, 1016 };
unsigned short gost08_tbl08[2] = { 0, 1167 };
unsigned short gost08_tbl09[3] = { 256, 1413, 1515 };
unsigned short gost08_tbl10[3] = { 256, 1701, 1803 };
unsigned short gost08_tbl11[3] = { 256, 1989, 2091 };
unsigned short gost08_tbl12[3] = { 256, 1701, 2283 };
unsigned short gost08_tbl13[2] = { 0, 2472 };
unsigned short gost08_tbl14[2] = { 0, 2616 };
unsigned short gost08_tbl15[2] = { 0, 2755 };
unsigned short gost08_tbl16[2] = { 0, 2819 };
unsigned short gost08_tbl17[2] = { 0, 2880 };
unsigned short* gost08_tbl[18] = {
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

wrt_data gost08_wrt_tbl = {
  gost08_tiles,
  gost08_tbl
};

enemy_init2_data switch_init_tbl = {
  512,
  16,
  8,
  5,
  0
};


void gost08(sprite_status* pActwk) {
  pActwk->r_ptr = &gost08_ctr;
  pActwk->xposi = SHORT_TO_LONG_HIGH(288);
  pActwk->yposi = SHORT_TO_LONG_HIGH(160);
  gost08_ctr(pActwk);
}

void gost08_ctr(sprite_status* pActwk) {
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

void gost08_body(sprite_status* pActwk) {
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

void gost08_body__fout0(sprite_status* pActwk) {
  --soz_ghosts;
  set_wchg_fout0(pActwk);
}

void gost08_body__fout1(sprite_status* pActwk) {
  pActwk->r_ptr = &gost08_body_fout0;
  SPRITE_STATUS_PHANDLER(pActwk, 52) = &gost08_body_fout0;
  pg_init(pActwk, gost08_away_pg00);
  soundset(-118);
  actionsub(pActwk);
}

void gost08_init(sprite_status* pActwk) {
  emy_wrt_init(pActwk, &gost08_init_tbl);
  CLEAR_BIT_2(pActwk->actflg);
  SET_BIT_7(pActwk->actflg);
  SPRITE_STATUS_UCHAR(pActwk, 66) = soz_darkness_level;
  SPRITE_STATUS_UCHAR(pActwk, 67) = soz_ghosts;
  set_body_init(pActwk);
  soundset(-110);
  gost08_wait0(pActwk);
}

void gost08_wait0(sprite_status* pActwk) {
  int ret = time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  if (ret == 0) return;
  if (soz_darkness_level == 5) {
    gost08_atak_init(pActwk);
  }
  else {
    pActwk->r_no = 4;
  }
}

void gost08_atak_init(sprite_status* pActwk) {
  pActwk->r_no = 12;
  set_puka_init(pActwk);
}

void gost08_move0(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  puka_puka(pActwk);
  speedset2(pActwk);
  chk_gost08_limit(pActwk);
  if (soz_darkness_level != SPRITE_STATUS_UCHAR(pActwk, 66)) {
    pActwk->r_no = 6;
  }
}

void gost08_chg0(sprite_status* pActwk) {
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

void gost08_chg1(sprite_status* pActwk) {
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

void gost08_chg2(sprite_status* pActwk) {
  puka_puka(pActwk);
  speedset2(pActwk);
  chk_gost08_limit(pActwk);
  int ret = time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  if (ret != 0) {
    pActwk->r_no = 4;
  }
}

void gost08_atak0(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  puka_puka(pActwk);
  speedset2(pActwk);
  short xposi = LONG_HIGH_TO_SHORT(pActwk->xposi);
  if (pActwk->xspeed >= 0) {
    // chk_r
    if (abs(xposi) <= 416) return; // unsigned
  }
  else {
    // chk_l
    if (abs(xposi) >= 160); return; // unsigned
  }
  pActwk->r_no = 14;
  CLEAR_BIT_0(pActwk->actflg);
  pActwk->xspeed = -pActwk->xspeed;
  SPRITE_STATUS_SHORT(pActwk, 46) = 59;
}

void gost08_atak1(sprite_status* pActwk) {
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

void gost08_atak2(sprite_status* pActwk) {
  time_pg(pActwk, SPRITE_STATUS_PSCHAR(pActwk, 48));
  speedset2(pActwk);
}

void gost08_body_fout0(sprite_status* pActwk) {
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

void set_openbox_cg(sprite_status* pActwk) {
  static cg_data opnbox_cg_tbl = {
    0,
    {
      { opnbox_tiles, 42688 }
    }
  };

  Load_PLC_Raw(pActwk, &opnbox_cg_tbl);
}

void set_emy08_cg(sprite_status* pActwk) {
  LoadEnemyArt();
}

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

void obox08_switch(sprite_status* pActwk) {
  enemy_init2(pActwk, &switch_init_tbl);
  pActwk->r_ptr = &switch_wait0;
  if (markerno != 0) {
    pActwk->r_ptr = &switch_wait1;
    pActwk->patno = 12;
  }
}
