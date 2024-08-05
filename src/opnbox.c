#include "globals.h"
#include "macros.h"
#include "util.h"
#include "opnbox.h"
#include "004xxxxx.h"
#include "002.h"
#include "091.h"
#include "actclear.h"
#include "hitchk.h"
#include "resources.h"
static void opnbox_init(sprite_status* p_actwk);
static void opnbox_wait0(sprite_status* p_actwk);
static void set_break(sprite_status* p_actwk);
static void opnbox_wait1(sprite_status* p_actwk);
static void opnbox_wait2(sprite_status* p_actwk);
static void opnbox_fly0(sprite_status* p_actwk);
static void opnbox_fly1(sprite_status* p_actwk);
static void opnbox_fly2(sprite_status* p_actwk);
static void opnbox_fly3(sprite_status* p_actwk);
static void opnbox_fly4(sprite_status* p_actwk);
static void opnbox_fly40(sprite_status* p_actwk);
static void opnbox_fly5(sprite_status* p_actwk);
static void switch_(sprite_status* p_actwk);
static void switchud(sprite_status* p_actwk);
static void switchud_wait0(sprite_status* p_actwk);
static void switchud_wait1(sprite_status* p_actwk);
static void break_(sprite_status* p_actwk);
static void propera(sprite_status* p_actwk);
static void propera_wait0(sprite_status* p_actwk);
static void friend_wait0(sprite_status* p_actwk);
static void friend_move0(sprite_status* p_actwk);
static void friend_pg(sprite_status* p_actwk);
static void friend_wait1(sprite_status* p_actwk);
static void friend_move1(sprite_status* p_actwk);
static void friend_move2(sprite_status* p_actwk);
static bool chk_pl_pausez02(sprite_status* p_actwk, unsigned char r_no);
static void get_closero(sprite_status* p_actwk, sprite_status* p_other_actwk, short x_unknown, short y_unknown, short speed_add, short xposi_add, short yposi_add);
static void chk_switchu_ride(sprite_status* p_actwk);
static void set_friend_init(sprite_status* p_actwk);
static void chk_spd_pt(sprite_status* p_actwk);
static enemy_init0_data opnbox_init_tbl;
static enemy_init0_data break_init_tbl;
static enemy_init2_data friend_init_tbl;
static enemy_init2_data propera_init_tbl;
static set_act00_data switch_set_tbl;
static set_act00_data switch_set_tblud;
static set_act00_data propera_set_tbl;
static set_act00_data friend_set_tbl;
static signed char propera_pg00[6];
static signed char openbox_pt00[62];
static signed char openbox_pt01[50];
static signed char openbox_pt02[14];
static signed char openbox_pt03[8];
static signed char openbox_pt04[8];
static signed char openbox_pt05[14];
static signed char openbox_pt06[14];
static signed char openbox_pt07[8];
static signed char openbox_pt08[8];
static signed char openbox_pt09[8];
static signed char openbox_pt10[8];
static signed char openbox_pt11[8];
static signed char openbox_pt12[14];


void opnbox(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[10] = {
    &opnbox_init,
    &opnbox_wait0,
    &opnbox_wait1,
    &opnbox_wait2,
    &opnbox_fly0,
    &opnbox_fly1,
    &opnbox_fly2,
    &opnbox_fly3,
    &opnbox_fly4,
    &opnbox_fly5
  };

  short xposi = LONG_HIGH(p_actwk->xposi);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  hitchk_data data = { 43, 24, 24, xposi };
  hitchk(p_actwk, data);
  actionsub(p_actwk);
}


static void opnbox_init(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &opnbox_init_tbl);
  if (!IS_VFLIP(p_actwk->actflg)) {
    set_act00(p_actwk, &switch_set_tbl);
  }
  else {
    p_actwk->r_no = 8;
    short xposi = LONG_HIGH(scra_h_posit) + 160;
    util__assign_high(&p_actwk->xposi, xposi);
    p_actwk->actfree.opnbox.xposi = xposi;
    short yposi = LONG_HIGH(scra_v_posit) - 64;
    util__assign_high(&p_actwk->yposi, yposi);
    p_actwk->actfree.opnbox.xspeed = 1;
    bs00m0_puka_init(p_actwk);
    set_act00(p_actwk, &switch_set_tblud);
    set_act00(p_actwk, &propera_set_tbl);
  }
}


static void opnbox_wait0(sprite_status* p_actwk) {
  if (BIT_1_IS_SET(p_actwk->actfree.opnbox.status_bitfield)) {
    p_actwk->r_no = 4;
  }
}


static void set_break(sprite_status* p_actwk) {
  if (stageno.zone == MARBLE_GARDEN) {
    pl2_lock_flag = 255;
  }
  p_actwk->patno = 1;
  p_actwk->actfree.opnbox.timer = 64;
  DAT_08fffacd = 255;
  set_act00(p_actwk, &opnbox_break_set_tbl);
  set_act00(p_actwk, &friend_set_tbl);
  sprite_status* p_new_actwk = set_act00(p_actwk, &bsexp01_set_tbl);
  p_new_actwk->userflag1 = 8;
}


static void opnbox_wait1(sprite_status* p_actwk) {
  chk_pl_pause(p_actwk, 6);
}


static void opnbox_wait2(sprite_status* p_actwk) {
  chk_pl2_pause(p_actwk);
}


static void opnbox_fly0(sprite_status* p_actwk) {
  static unsigned char rno_tbl[24] = {
    10, 10, 14, 10,
    10, 10, 16, 10,
    10, 10, 10, 10,
    10, 10, 10, 10,
    10, 10, 10, 10,
    10, 10, 10, 10
  };

  short xspeed = p_actwk->actfree.opnbox.xspeed;
  bool neg = false;
  if (xspeed >= 0) {
    // p_chk
    unsigned short hposi = util__to_unsigned(LONG_HIGH(scra_h_posit) + 272);
    if (hposi < util__to_unsigned(LONG_HIGH(p_actwk->xposi))) { // unsigned
      neg = true;
    }
  }
  else {
    // m_chk
    unsigned short hposi = util__to_unsigned(LONG_HIGH(scra_h_posit) + 48);
    if (hposi >= util__to_unsigned(LONG_HIGH(p_actwk->xposi))) { // unsigned
      neg = true;
    }
  }
  if (neg) {
    xspeed = -xspeed;
  }
  p_actwk->actfree.opnbox.xspeed = xspeed;
  p_actwk->xposi += SHORT_TO_LONG_HIGH(xspeed);
  short vposi = LONG_HIGH(scra_v_posit) + 64;
  if (stageno.zone == MARBLE_GARDEN) {
    vposi -= 32;
  }
  short yspeed = 16384;
  if (vposi >= util__to_unsigned(LONG_HIGH(p_actwk->yposi))) { // unsigned
    yspeed = -yspeed;
  }
  p_actwk->yposi += yspeed;
  if (BIT_1_IS_SET(p_actwk->actfree.opnbox.status_bitfield)) {
    p_actwk->r_no = rno_tbl[stageno.zone];
    set_break(p_actwk);
  }
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly1(sprite_status* p_actwk) {
  chk_pl_pause(p_actwk, 12);
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly2(sprite_status* p_actwk) {
  chk_pl2_pause(p_actwk);
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly3(sprite_status* p_actwk) {
  chk_pl_pausez02(p_actwk, 12);
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly4(sprite_status* p_actwk) {
  chk_pl_pause(p_actwk, 18);
  opnbox_fly40(p_actwk);
}


static void opnbox_fly40(sprite_status* p_actwk) {
  puka_puka(p_actwk);
  unsigned short hposi = util__to_unsigned(LONG_HIGH(scra_h_posit) - 96);
  if (hposi >= util__to_unsigned(LONG_HIGH(p_actwk->xposi))) {
    DAT_08fffaa2 = 255;
  }
  else {
    p_actwk->xposi -= SHORT_TO_LONG_HIGH(2);
    speedset2(p_actwk);
  }
}


static void opnbox_fly5(sprite_status* p_actwk) {
  chk_pl2_pause(p_actwk);
  opnbox_fly40(p_actwk);
}


static void switch_(sprite_status* p_actwk) {
  p_actwk->r_ptr = &switch_wait0;
  enemy_init2(p_actwk, &switch_init_tbl);
}


void switch_wait0(sprite_status* p_actwk) {
  chk_switch_ride(p_actwk);
  if (p_actwk->cddat1 & 0x18) {
    p_actwk->r_ptr = &switch_wait1;
    sprite_status* p_parentwk = &actwk[p_actwk->actfree.opnbox_switch.oya];
    SET_BIT_1(p_parentwk->actfree.opnbox.status_bitfield);
    p_actwk->patno = 12;
  }
  chk_oya_die0(p_actwk);
}


void switch_wait1(sprite_status* p_actwk) {
  chk_switch_ride(p_actwk);
  chk_oya_die0(p_actwk);
}


static void switchud(sprite_status* p_actwk) {
  p_actwk->r_ptr = &switchud_wait0;
  SET_VFLIP(p_actwk->actflg);
  enemy_init2(p_actwk, &switch_init_tbl);
}


static void switchud_wait0(sprite_status* p_actwk) {
  static short col_tbl[4] = {
    -26, 52, -28, 56
  };

  ko_offset0(p_actwk);
  chk_switchu_ride(p_actwk);
  sprite_status* p_playerwk = chk_emy_colt(p_actwk, col_tbl);
  if (p_playerwk != 0) {
    bool player1 = p_playerwk->yspeed < 0 && (p_playerwk->mstno == 2 || p_playerwk->actfree.player.character == SONIC);
    if (player1 || p_playerwk->yspeed < 0) {
      p_actwk->r_ptr = switchud_wait1;
      SPRITE_STATUS_UCHAR(p_actwk, 67) -= 8;
      sprite_status* p_parentwk = &actwk[p_actwk->actfree.opnbox_switch.oya];
      SET_BIT_1(p_parentwk->actfree.opnbox.status_bitfield);
    }
  }
  chk_oya_die0(p_actwk);
}


static void switchud_wait1(sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  chk_switchu_ride(p_actwk);
  chk_oya_die0(p_actwk);
}


static void break_(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &break_init_tbl);
  if (stageno.zone == FLYING_BATTERY && stageno.act == 0) {
    p_actwk->sproffset = 1102;
  }
  p_actwk->r_ptr = chk_break_fout;
  set_obox_break_pt(p_actwk);
  set_break_spd(p_actwk, 4);
  actionsub(p_actwk);
}


static void propera(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &propera_init_tbl);
  p_actwk->r_ptr = &propera_wait0;
  propera_wait0(p_actwk);
}


static void propera_wait0(sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  pt_chg0(p_actwk, propera_pg00);
  chk_oya_die0(p_actwk);
}


void friend(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &friend_init_tbl);
  p_actwk->r_ptr = &friend_wait0;
  p_actwk->sprvsize = 8;
  set_friend_init(p_actwk);
  actionsub(p_actwk);
}


static void friend_wait0(sprite_status* p_actwk) {
  --p_actwk->actfree.friend_.move_countdown;
  if (p_actwk->actfree.friend_.move_countdown < 0) {
    p_actwk->r_ptr = &friend_move0;
    p_actwk->sprpri = PRI_1;
  }
  chk_emy_fout0(p_actwk);
}


static void friend_move0(sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  short unknown = ObjCheckFloorDist(p_actwk);
  if (unknown < 0) {
    p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown);
    p_actwk->yspeed = p_actwk->actfree.friend_.yspeed;
    bool pl_is_right, pl_is_below;
    short pl_x_distance, pl_y_distance;
    chk_distance(p_actwk, &pl_is_right, &pl_is_below, &pl_x_distance, &pl_y_distance);
    short xspeed = -512;
    if (act_clear_flag != 0 && pl_is_right) {
      xspeed = -xspeed;
    }
    p_actwk->xspeed = xspeed;
    chk_spd_pt(p_actwk);
  }
  friend_pg(p_actwk);
}


static void friend_pg(sprite_status* p_actwk) {
  unsigned char patno = 0;
  if (!BIT_3_IS_SET(systemtimer)) {
    patno = 1;
  }
  p_actwk->patno = patno;
  chk_emy_fout0(p_actwk);
}


static void friend_wait1(sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  --p_actwk->actfree.friend_.move_countdown;
  if (p_actwk->actfree.friend_.move_countdown < 0) {
    p_actwk->r_ptr = &friend_move1;
    p_actwk->sprpri = PRI_1;
  }
  chk_emy_fout0(p_actwk);
}


static void friend_move1(sprite_status* p_actwk) {
  get_closero(p_actwk, &actwk[0], 768, 256, 16, 0, -48 - p_actwk->userflag1);
  speedset2(p_actwk);
  chk_spd_pt(p_actwk);
  if (act_clear_flag == 0) {
    p_actwk->r_ptr = &friend_move2;
    SET_HFLIP(p_actwk->actflg);
  }
  friend_pg(p_actwk);
}


static void friend_move2(sprite_status* p_actwk) {
  p_actwk->xposi -= SHORT_TO_LONG_HIGH(2);
  friend_pg(p_actwk);
}


void chk_pl_pause(sprite_status* p_actwk, unsigned char r_no) {
  --p_actwk->actfree.opnbox.timer;
  if (BIT_7_IS_SET(actwk[0].cddat1)) return;
  if (BIT_1_IS_SET(actwk[0].cddat1)) return;
  if (actwk[0].r_no >= 6) return; // unsigned
  p_actwk->r_no = r_no;
  set_pl_pause(p_actwk, &actwk[0]);
  short slot_cnt;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite(&p_new_actwk, &slot_cnt);
  if (created) {
    p_new_actwk->r_ptr = &actclear;
  }
}


void chk_pl2_pause(sprite_status* p_actwk) {
  if (act_clear_flag == 0) return;
  if (stageno.zone == CARNIVAL_NIGHT) {
    set_pl_pause(p_actwk, &actwk[0]);
  }
  if (BIT_7_IS_SET(p_actwk->actfree.opnbox.status_bitfield)) return;
  if (BIT_7_IS_SET(actwk[1].cddat1)) return;
  if (BIT_1_IS_SET(actwk[1].cddat1)) return;
  if (actwk[1].r_no >= 6) return; // unsigned
  SET_BIT_7(p_actwk->actfree.opnbox.status_bitfield);
  pl2_lock_flag = 0;
  set_pl_pause(p_actwk, &actwk[1]);
}


static bool chk_pl_pausez02(sprite_status* p_actwk, unsigned char r_no) {
  --p_actwk->actfree.opnbox.timer;
  if (p_actwk->actfree.opnbox.timer >= 0) return false;
  if (actwk[0].r_no >= 6) return false; // unsigned
  if (!IS_ONSCREEN(actwk[0].actflg)) return false;
  if (actwk[0].actfree.player.character != SONIC) {
    if (miles_carry_flag == 0) return false;
  }
  p_actwk->xspeed = -256;
  p_actwk->r_no = r_no;
  short slot_cnt;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite(&p_new_actwk, &slot_cnt);
  if (created) {
    p_new_actwk->r_ptr = &actclear;
  }
  return true;
}


void set_pl_pause(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_playerwk->actfree.player.control_bitfield = 129;
  p_playerwk->mstno = 19;
  p_playerwk->actfree.player.roll_status = 0;
  p_playerwk->xspeed = 0;
  p_playerwk->yspeed = 0;
  p_playerwk->mspeed = 0;
  CLEAR_BIT(p_actwk->cddat1, CD_PLPUSH);
  CLEAR_BIT(p_actwk->cddat1, CD_PL2PUSH);
  CLEAR_BIT(p_playerwk->cddat1, CD_PUSH);
}


static void get_closero(sprite_status* p_actwk, sprite_status* p_other_actwk, short x_unknown, short y_unknown, short speed_add, short xposi_add, short yposi_add) {
  short xspeed_add = speed_add;
  short yspeed_add = speed_add;
  if (LONG_HIGH(p_other_actwk->xposi) + xposi_add < LONG_HIGH(p_actwk->xposi)) {
    xspeed_add = -xspeed_add;
  }
  short xspeed = p_actwk->xspeed + xspeed_add;
  if (xspeed <= x_unknown) {
    x_unknown = -x_unknown;
    if (xspeed >= x_unknown) {
      p_actwk->xspeed = xspeed;
    }
  }
  short yspeed = 0;
  do {
    if (LONG_HIGH(p_other_actwk->yposi) + yposi_add < LONG_HIGH(p_actwk->yposi)) {
      yspeed_add = -yspeed_add;
    }
    yspeed = p_actwk->yspeed + yspeed_add;
    if (yspeed <= y_unknown) {
      y_unknown = -y_unknown;
    }
  } while (yspeed < y_unknown);
  p_actwk->yspeed = yspeed;
}


void chk_switch_ride(sprite_status* p_actwk) {
  hitchk_data data = { 27, 4, 6, LONG_HIGH(p_actwk->xposi) };
  hitchk(p_actwk, data);
}


static void chk_switchu_ride(sprite_status* p_actwk) {
  hitchk_data data = { 27, 5, 9, LONG_HIGH(p_actwk->xposi) };
  hitchk(p_actwk, data);
}


void set_obox_break_pt(sprite_status* p_actwk) {
  static unsigned char pt_tbl[6] = {
    2, 3, 10, 4, 11, 144
  };

  p_actwk->patno = pt_tbl[p_actwk->userflag1 >> 1];
}


static void set_friend_init(sprite_status* p_actwk) {
  static short spd_tbl[4] = {
    -896, -768, -640, -512
  };
  static unsigned short ofs_tbl[4] = {
    34176, 34194, 33838, 33856
  };

  short yspeed = spd_tbl[(p_actwk->userflag1 & 6) / 2];
  p_actwk->yspeed = yspeed;
  p_actwk->actfree.friend_.yspeed = yspeed;
  sprite_status* p_parentwk = &actwk[p_actwk->actfree.friend_.oya];
  if (IS_VFLIP(p_parentwk->actflg)) {
    p_actwk->r_ptr = &friend_wait1;
    SPRITE_STATUS_UCHAR(p_actwk, 67) += 8;
    p_actwk->yspeed = 0;
  }
  unsigned short ofs_index = p_actwk->userflag1 & 2;
  if (stageno.zone == FLYING_BATTERY && stageno.act == 0) {
    ofs_index += 4;
  }
  p_actwk->sproffset = ofs_tbl[ofs_index * 2];
  unsigned char* friends = &zone_friend_data[stageno.zone][0];
  unsigned char friend_id = friends[(p_actwk->userflag1 & 2) / 2];
  p_actwk->patbase = friend_data[friend_id].patbase;
  p_actwk->actfree.friend_.move_countdown = p_actwk->userflag1 * 4;
  short xspeed = 512;
  if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) < util__to_unsigned(LONG_HIGH(p_parentwk->xposi))) { // unsigned
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  chk_spd_pt(p_actwk);
}


static void chk_spd_pt(sprite_status* p_actwk) {
  CLEAR_HFLIP(p_actwk->actflg);
  if (p_actwk->xspeed < 0) {
    SET_HFLIP(p_actwk->actflg);
  }
}


static enemy_init0_data opnbox_init_tbl = {
  openbox_pt,
  33940,
  PRI_4,
  32,
  32,
  0,
  0
};


enemy_init2_data switch_init_tbl = {
  PRI_4,
  16,
  8,
  5,
  0
};


static enemy_init0_data break_init_tbl = {
  openbox_pt,
  33940,
  PRI_3,
  12,
  12,
  0,
  0
};


static enemy_init2_data friend_init_tbl = {
  PRI_5,
  8,
  8,
  2,
  0
};


static enemy_init2_data propera_init_tbl = {
  PRI_4,
  20,
  4,
  6,
  0
};


static set_act00_data switch_set_tbl = {
  0,
  {
    { &switch_, 0, 220 }
  }
};


static set_act00_data switch_set_tblud = {
  0,
  {
    { &switchud, 0, 36 }
  }
};


static set_act00_data propera_set_tbl = {
  1,
  {
    { &propera, 236, 220 },
    { &propera, 20, 220 }
  }
};


set_act00_data opnbox_break_set_tbl = {
  4,
  {
    { &break_, 0, 248 },
    { &break_, 240, 248 },
    { &break_, 16, 248 },
    { &break_, 232, 248 },
    { &break_, 24, 248 }
  }
};


static set_act00_data friend_set_tbl = {
  8,
  {
    { &friend, 0, 252 },
    { &friend, 248, 252 },
    { &friend, 8, 252 },
    { &friend, 16, 252 },
    { &friend, 240, 252 },
    { &friend, 232, 252 },
    { &friend, 24, 252 },
    { &friend, 252, 252 },
    { &friend, 4, 252 },
    { &friend, 12, 252 },
    { &friend, 244, 252 },
    { &friend, 236, 252 },
    { &friend, 20, 252 },
    { &friend, 28, 252 },
    { &friend, 228, 252 }
  }
};


static signed char propera_pg00[6] = { 0, 6, 7, 8, 9, -4 };


signed char* openbox_pt[13] = {
  openbox_pt00,
  openbox_pt01,
  openbox_pt02,
  openbox_pt03,
  openbox_pt04,
  openbox_pt05,
  openbox_pt06,
  openbox_pt07,
  openbox_pt08,
  openbox_pt09,
  openbox_pt10,
  openbox_pt11,
  openbox_pt12
};


static signed char openbox_pt00[62] = {
    0,  10, -32,  13,  12,   0, -32,  -1, -32,  13,
   12,   8,   0,   0, -16,   2,  20,   0,  -8,  -1,
  -16,   2,  20,   8,   0,   0, -16,   6,  23,   0,
  -24,  -1, -16,   6,  23,   8,   8,   0, -16,   2,
   29,   0, -32,  -1, -16,   2,  29,   8,  24,   0,
    8,  14,   0,   0, -32,  -1,   8,  14,   0,   8,
    0,   0
};
static signed char openbox_pt01[50] = {
    0,   8, -32,  13,  32,   0, -32,  -1, -16,   1,
   40,   0, -16,  -1,   0,  12,  42,   0, -32,  -1,
  -32,  13,  32,   8,   0,   0, -16,   1,  40,   8,
    8,   0,   0,  12,  42,   8,   0,   0,   8,  14,
    0,   0, -32,  -1,   8,  14,   0,   8,   0,   0
};
static signed char openbox_pt02[14] = {
    0,   2,  -8,   1,  46,   0,  -8,  -1,  -8,   1,
   46,   8,   0,   0
};
static signed char openbox_pt03[8] = {
    0,   1,  -8,   5,  48,   0,  -8,  -1
};
static signed char openbox_pt04[8] = {
    0,   1,  -8,   1,  52,   0,  -4,  -1
};
static signed char openbox_pt05[14] = {
    0,   2, -12,   5,  54,   0, -16,  -1, -12,   5,
   54,   8,   0,   0
};
static signed char openbox_pt06[14] = {
    0,   2,  -4,   8,  58,   0, -20,  -1,  -4,   4,
   61,   0,   4,   0
};
static signed char openbox_pt07[8] = {
    0,   1,  -4,   8,  63,   0, -12,  -1
};
static signed char openbox_pt08[8] = {
    0,   1,  -4,   0,  66,   0,  -4,  -1
};
static signed char openbox_pt09[8] = {
    0,   1,  -4,   8,  67,   0, -12,  -1
};
static signed char openbox_pt10[8] = {
    0,   1,  -8,   5,  48,   8,  -8,  -1
};
static signed char openbox_pt11[8] = {
    0,   1,  -8,   1,  52,   8,  -4,  -1
};
static signed char openbox_pt12[14] = {
    0,   2,  -5,   5,  54,   0, -16,  -1,  -5,   5,
   54,   8,   0,   0
};
