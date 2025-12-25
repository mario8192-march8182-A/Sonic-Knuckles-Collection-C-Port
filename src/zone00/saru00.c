#include "../globals.h"
#include "../macros.h"
#include "../util.h"
#include "../types/enemyinit1data.h"
#include "../types/enemyinit2data.h"
#include "../types/setact00data.h"
#include "../types/setact01data.h"
#include "../types/setact03data.h"
#include "saru00.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"
#include "../emyshot.h"
#include "../resources.h"
static void saru00_framein(sprite_status* p_actwk);
static void saru00_init(sprite_status* p_actwk);
static void saru00_wait(sprite_status* p_actwk);
static void saru00_move_init(sprite_status* p_actwk);
static void saru00_move(sprite_status* p_actwk);
static void saru00_arm0(sprite_status* p_actwk);
static void saru00_arm_base(sprite_status* p_actwk);
static void arm_base_up(sprite_status* p_actwk);
static void ura1_init0(sprite_status* p_actwk);
static void arm_base_ura(sprite_status* p_actwk);
static void arm_base_ura1(sprite_status* p_actwk);
static void chg_add(sprite_status* p_actwk);
static void saru00_shot_init(sprite_status* p_actwk);
static void arm_base_shot0(sprite_status* p_actwk);
static void arm_base_shot1(sprite_status* p_actwk);
static void arm_base_shot2(sprite_status* p_actwk);
static void saru00_arm_other(sprite_status* p_actwk);
static void arm_other_ura(sprite_status* p_actwk);
static void arm_other_ura1(sprite_status* p_actwk);
static void arm_other_shot(sprite_status* p_actwk);
static void arm_hand_ura(sprite_status* p_actwk);
static void arm_hand_ura1(sprite_status* p_actwk);
static void arm_hand_shot(sprite_status* p_actwk);
static void banana_move(sprite_status* p_actwk);
static void land_init(sprite_status* p_actwk);
static void banana_land(sprite_status* p_actwk);
static void saru00_chk_rev(sprite_status* p_actwk);
static void saru00_chk_ofs(sprite_status* p_actwk);
static void saru00_chk_pri(sprite_status* p_actwk);
static bool saru00_chk_shot(sprite_status* p_actwk);
static void saru00_add_dir(sprite_status* p_actwk, signed char offset);
static void other_move(sprite_status* p_actwk);
static void chk_arm_shot(sprite_status* p_actwk, unsigned char r_no);
static void chk_arm_ura(sprite_status* p_actwk, unsigned char r_no);
static void chk_hand_shot(sprite_status* p_actwk);
static void set_arm_timer(sprite_status* p_actwk);
static enemy_init0_data saru00_init_tbl;
static enemy_init2_data saru00_arm_init_tbl;
static enemy_init1_data banana_init_tbl;
static enemy_init0_data yasi_init_tbl;
static set_act03_data saru00_arm_set_tbl0;
static set_act03_data saru00_arm_set_tbl1;
static set_act00_data banana_set_tbl;
static set_act01_data yasi_set_tbl;
static signed char saru00_pg00[4];
static signed char saru00_pg01[5];
static signed char banana_pg00[10];
static signed char banana_pg01[5];


void saru00(sprite_status* p_actwk) {
  chk_framein(p_actwk, &saru00_framein);
  saru00_framein(p_actwk);
}


static void saru00_framein(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[3] = {
    &saru00_init,
    &saru00_wait,
    &saru00_move
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void saru00_init(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &saru00_init_tbl);
  p_actwk->userflag1 /= 4;
  p_actwk->actfree.saru00.wait_countdown = p_actwk->userflag1 / 2;
  p_actwk->actfree.saru00.pg_data_ptr = saru00_pg00;
  p_actwk->actfree.saru00.timer = 59;
  p_actwk->actfree.saru00.callback_ptr = &saru00_move_init;
  if (!BIT_IS_SET(p_actwk->actflg, FLG_HFLIP)) {
    set_act03(p_actwk, &saru00_arm_set_tbl0);
  }
  else {
    set_act03(p_actwk, &saru00_arm_set_tbl1);
  }
}


static void saru00_wait(sprite_status* p_actwk) {
  pt_tim(p_actwk);
}


static void saru00_move_init(sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->patcnt = 0;
  p_actwk->pattim = 0;
  p_actwk->actfree.saru00.pg_data_ptr = saru00_pg01;
}


static void saru00_move(sprite_status* p_actwk) {
  int ret = time_pg(p_actwk, p_actwk->actfree.saru00.pg_data_ptr);
  if (ret == 0) return;
  bool goto_wait = false;
  if (!BIT_2_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    if (p_actwk->patno != 0) return;
    p_actwk->yposi += SHORT_TO_LONG_HIGH(8);
    --p_actwk->actfree.saru00.wait_countdown;
    if (p_actwk->actfree.saru00.wait_countdown == 1) {
      goto_wait = true;
    }
  }
  else {
    if (p_actwk->patno != 2) return;
    --p_actwk->actfree.saru00.wait_countdown;
    if (p_actwk->actfree.saru00.wait_countdown == 0) {
      goto_wait = true;
    }
    else {
      p_actwk->yposi -= SHORT_TO_LONG_HIGH(8);
    }
  }
  if (goto_wait) {
    p_actwk->r_no = 2;
    p_actwk->actfree.saru00.wait_countdown = p_actwk->userflag1;
    TOGGLE_BIT_2(p_actwk->actfree.saru00.status_bitfield);
    p_actwk->actfree.saru00.timer = 59;
    p_actwk->actfree.saru00.pg_data_ptr = saru00_pg00;
    p_actwk->patno = 0;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
  }
}


static void saru00_arm0(sprite_status* p_actwk) {
  SET_BIT_3(p_actwk->actfree.saru00.status_bitfield);
  saru00_arm(p_actwk);
}


void saru00_arm(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &saru00_arm_init_tbl);
  p_actwk->r_no = 0;
  p_actwk->actfree.saru00.arm_other_countdown = p_actwk->userflag1 * 2;
  SPRITE_STATUS_UCHAR(p_actwk, 58) = p_actwk->userflag1 * 2;
  if (p_actwk->userflag1 == 0) {
    p_actwk->r_ptr = &saru00_arm_base;
    signed char xoffset = 14;
    if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
      xoffset = -xoffset;
    }
    p_actwk->xposi += SHORT_TO_LONG_HIGH(xoffset);
    p_actwk->yposi -= SHORT_TO_LONG_HIGH(2);
    SPRITE_STATUS_SHORT(p_actwk, 62) = LONG_HIGH(p_actwk->yposi);
    chk_oya_die0(p_actwk);
  }
  else {
    if (p_actwk->userflag1 != 8) {
      p_actwk->r_ptr = &saru00_arm_other;
      chk_oya_die0(p_actwk);
    }
    else {
      p_actwk->r_ptr = &saru00_hand;
      p_actwk->patno = 6;
      sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.saru00.oya];
      p_parentwk = &g_ram.actwk[p_actwk->actfree.dynamic.oya];
      p_actwk->actfree.saru00.arm_other = p_parentwk - g_ram.actwk;
      p_parentwk = &g_ram.actwk[p_actwk->actfree.dynamic.oya];
      p_parentwk = &g_ram.actwk[p_actwk->actfree.dynamic.oya];
      p_actwk->actfree.saru00.ko = p_parentwk - g_ram.actwk;
      chk_oya_die0(p_actwk);
    }
  }
}


static void saru00_arm_base(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[6] = {
    &arm_base_up,
    &arm_base_ura,
    &arm_base_shot0,
    &arm_base_shot1,
    &arm_base_shot2,
    &arm_base_ura1
  };

  saru00_chk_ofs(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die0(p_actwk);
}


static void arm_base_up(sprite_status* p_actwk) {
  unsigned char angle = p_actwk->actfree.saru00.arm_other_angle;
  if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    // right
    angle += 4;
    if (angle < 128) { // unsigned
      p_actwk->actfree.saru00.arm_other_angle = angle;
      return;
    }
  }
  else {
    // left
    angle -=4;
    if (angle > 128) { // unsigned
      p_actwk->actfree.saru00.arm_other_angle = angle;
      return;
    }
  }
  p_actwk->r_no = 2;
}


static void ura1_init0(sprite_status* p_actwk) {
  set_arm_timer(p_actwk);
  p_actwk->r_ptr = &chg_add;
}


static void arm_base_ura(sprite_status* p_actwk) {
  bool shoot = saru00_chk_shot(p_actwk);
  if (shoot) {
    saru00_shot_init(p_actwk);
  }
  else {
    arm_base_ura1(p_actwk);
  }
}


static void arm_base_ura1(sprite_status* p_actwk) {
  if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    // right
    saru00_add_dir(p_actwk, p_actwk->actfree.saru00.dir);
    if (p_actwk->actfree.saru00.arm_other_angle - 32 >= 96) goto neg; // unsigned
    goto LAB_100;
  }
  else {
    // left
    saru00_add_dir(p_actwk, p_actwk->actfree.saru00.dir);
    if (p_actwk->actfree.saru00.arm_other_angle - 128 < 96) goto LAB_100; // unsigned
  }

neg:
  p_actwk->actfree.saru00.dir = -p_actwk->actfree.saru00.dir;
  saru00_add_dir(p_actwk, p_actwk->actfree.saru00.dir);

LAB_100:
  dec_timer(p_actwk);
}


static void chg_add(sprite_status* p_actwk) {
  set_arm_timer(p_actwk);
}


static void saru00_shot_init(sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  SET_BIT_1(p_actwk->actfree.saru00.status_bitfield);
}


static void arm_base_shot0(sprite_status* p_actwk) {
  if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    // right
    saru00_add_dir(p_actwk, 4);
    if (p_actwk->actfree.saru00.arm_other_angle < 192) return; // unsigned
  }
  else {
    // left
    saru00_add_dir(p_actwk, -4);
    if (p_actwk->actfree.saru00.arm_other_angle > 64) return; // unsigned
  }
  p_actwk->r_no = 6;
  SET_BIT_2(p_actwk->actfree.saru00.status_bitfield);
}


static void arm_base_shot1(sprite_status* p_actwk) {
  unsigned char angle = 0;
  if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    // right
    saru00_add_dir(p_actwk, -8);
    angle = 96;
    if (p_actwk->actfree.saru00.arm_other_angle > angle) return; // unsigned
  }
  else {
    // left
    saru00_add_dir(p_actwk, 8);
    angle = 160;
    if (p_actwk->actfree.saru00.arm_other_angle < angle) return; // unsigned
  }
  p_actwk->r_no = 8;
  p_actwk->actfree.saru00.arm_other_angle = angle;
  CLEAR_BIT_1(p_actwk->actfree.saru00.status_bitfield);
}


static void arm_base_shot2(sprite_status* p_actwk) {
  unsigned char angle = 0;
  if (!BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    // right
    saru00_add_dir(p_actwk, -2);
    angle = 128;
    if (p_actwk->actfree.saru00.arm_other_angle > angle) return; // unsigned
  }
  else {
    // left
    saru00_add_dir(p_actwk, 2);
    angle = 128;
    if (p_actwk->actfree.saru00.arm_other_angle < angle) return; // unsigned
  }
  p_actwk->r_no = 10;
  p_actwk->actfree.saru00.arm_other_angle = angle;
  ura1_init0(p_actwk);
}


static void saru00_arm_other(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[3] = {
    &arm_other_ura,
    &arm_other_shot,
    &arm_other_ura1
  };

  saru00_chk_pri(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die0(p_actwk);
}


static void arm_other_ura(sprite_status* p_actwk) {
  chk_arm_shot(p_actwk, 2);
  arm_other_ura1(p_actwk);
}


static void arm_other_ura1(sprite_status* p_actwk) {
  other_move(p_actwk);
}


static void arm_other_shot(sprite_status* p_actwk) {
  chk_arm_ura(p_actwk, 4);
  other_move(p_actwk);
}


void saru00_hand(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[3] = {
    &arm_hand_ura,
    &arm_hand_shot,
    &arm_hand_ura1
  };

  saru00_chk_pri(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die0(p_actwk);
}


static void arm_hand_ura(sprite_status* p_actwk) {
  chk_arm_shot(p_actwk, 2);
  arm_hand_ura1(p_actwk);
}


static void arm_hand_ura1(sprite_status* p_actwk) {
  other_move(p_actwk);
}


static void arm_hand_shot(sprite_status* p_actwk) {
  chk_hand_shot(p_actwk);
  chk_arm_ura(p_actwk, 4);
  other_move(p_actwk);
}


void saru00_banana(sprite_status* p_actwk) {
  enemy_init1(p_actwk, &banana_init_tbl);
  p_actwk->r_ptr = &banana_move;
  p_actwk->actfree.saru00_banana.pg_data_ptr = banana_pg00;
  p_actwk->actfree.saru00_banana.callback_ptr = &land_init;
  p_actwk->sprvsize = 8;
  p_actwk->xspeed = -512;
  p_actwk->yspeed = -1024;
  frameoutchkc(p_actwk, LONG_HIGH(p_actwk->xposi));
}


static void banana_move(sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  time_pg(p_actwk, p_actwk->actfree.saru00_banana.pg_data_ptr);
  emy_fall_col(p_actwk);
  frameoutchkc(p_actwk, LONG_HIGH(p_actwk->xposi));
}


static void land_init(sprite_status* p_actwk) {
  p_actwk->r_ptr = &banana_land;
}


static void banana_land(sprite_status* p_actwk) {
  frameoutchkc(p_actwk, LONG_HIGH(p_actwk->xposi));
}


static void saru00_chk_rev(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.saru00.oya];
  unsigned char actflg = p_parentwk->actflg;
  if (BIT_3_IS_SET(p_parentwk->actfree.saru00.status_bitfield)) {
    TOGGLE_BIT(actflg, FLG_HFLIP);
  }
  p_actwk->sprpri = PRI_4;
  if (BIT_IS_SET(actflg, FLG_HFLIP)) {
    p_actwk->sprpri = PRI_6;
  }
}


static void saru00_chk_ofs(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.saru00.oya];
  short yposi = LONG_HIGH(p_parentwk->yposi) - 2;
  if (p_parentwk->patno != 0) {
    yposi -= 2;
  }
  util__assign_high(&p_actwk->yposi, yposi);
}


static void saru00_chk_pri(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.saru00.oya];
  p_actwk->sprpri = p_parentwk->sprpri;
}


static bool saru00_chk_shot(sprite_status* p_actwk) {
  bool pl_is_right, pl_is_below;
  short pl_x_distance, pl_y_distance;
  chk_distance(p_actwk, &pl_is_right, &pl_is_below, &pl_x_distance, &pl_y_distance);
  if (pl_x_distance >= 128) return false; // unsigned
  if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    pl_is_right = !pl_is_right;
  }
  return pl_is_right;
}


static void saru00_add_dir(sprite_status* p_actwk, signed char offset) {
  p_actwk->actfree.saru00.arm_other_angle += offset;
}


static void other_move(sprite_status* p_actwk) {
  --p_actwk->actfree.saru00.arm_other_countdown;
  if (p_actwk->actfree.saru00.arm_other_countdown == 0) {
    p_actwk->actfree.saru00.arm_other_countdown = SPRITE_STATUS_UCHAR(p_actwk, 58);
    sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.saru00.oya];
    p_actwk->actfree.saru00.arm_other_angle = p_parentwk->actfree.saru00.arm_other_angle;
  }
  circle_move(p_actwk, 5);
}


static void chk_arm_shot(sprite_status* p_actwk, unsigned char r_no) {
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.saru00.oya];
  if (!BIT_1_IS_SET(p_actwk->actfree.saru00.status_bitfield)) return;
  p_actwk->r_no = r_no;
  SET_BIT_1(p_actwk->actfree.saru00.status_bitfield);
  SPRITE_STATUS_UCHAR(p_actwk, 58) /= 2;
  p_actwk->actfree.saru00.arm_other_countdown = 1;
}


static void chk_arm_ura(sprite_status* p_actwk, unsigned char r_no) {
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.saru00.oya];
  if (BIT_1_IS_SET(p_actwk->actfree.saru00.status_bitfield)) return;
  p_actwk->r_no = r_no;
  SPRITE_STATUS_UCHAR(p_actwk, 58) *= 2;
  p_actwk->actfree.saru00.arm_other_countdown = 1;
}


static void chk_hand_shot(sprite_status* p_actwk) {
  if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    // right
    if (BIT_0_IS_SET(p_actwk->actfree.saru00.status_bitfield)) return;
    sprite_status* p_childwk = &g_ram.actwk[p_actwk->actfree.saru00.ko];
    if (!BIT_2_IS_SET(p_childwk->actfree.saru00.status_bitfield)) return;
    sprite_status* p_arm_otherwk = &g_ram.actwk[p_actwk->actfree.saru00.arm_other];
    if (p_arm_otherwk->actfree.saru00.arm_other_angle >= 132) return; // unsigned
  }
  else {
    // left
    if (BIT_0_IS_SET(p_actwk->actfree.saru00.status_bitfield)) return;
    sprite_status* p_childwk = &g_ram.actwk[p_actwk->actfree.saru00.ko];
    if (!BIT_2_IS_SET(p_childwk->actfree.saru00.status_bitfield)) return;
    sprite_status* p_arm_otherwk = &g_ram.actwk[p_actwk->actfree.saru00.arm_other];
    if (p_arm_otherwk->actfree.saru00.arm_other_angle < 124) return; // unsigned
    p_actwk->sproffset = 9604;
  }
  SET_BIT_0(p_actwk->actfree.saru00.status_bitfield);
  p_actwk->patno = 4;
  soundset(81);
  sprite_status* p_new_actwk = set_act01(p_actwk, &yasi_set_tbl);
  if (BIT_3_IS_SET(p_actwk->actfree.saru00.status_bitfield)) {
    p_new_actwk->xspeed = -p_new_actwk->xspeed;
  }
}


static void set_arm_timer(sprite_status* p_actwk) {
  random();
  signed char dir = 1;
  if (BIT_0_IS_SET(g_ram.ranum)) {
    dir = -dir;
  }
  p_actwk->actfree.saru00.dir = dir;
  p_actwk->actfree.saru00.timer = g_ram.ranum & 60;
}


static enemy_init0_data saru00_init_tbl = {
  saru00pat,
  9544,
  PRI_5,
  32,
  32,
  0,
  11
};


static enemy_init2_data saru00_arm_init_tbl = {
  PRI_6,
  4,
  4,
  3,
  0
};


static enemy_init1_data banana_init_tbl = {
  42312,
  PRI_5,
  32,
  32,
  6,
  11
};


static enemy_init0_data yasi_init_tbl = {
  saru00pat,
  1352,
  PRI_5,
  32,
  32,
  6,
  152
};


static set_act03_data saru00_arm_set_tbl0 = {
  4,
  &saru00_arm
};


static set_act03_data saru00_arm_set_tbl1 = {
  4,
  &saru00_arm
};


/*
static ? saru00_arm_set_tbl2 = {
  0,
  &saru00_arm,
  0x2D,
  0x74,
  0x00,
  0x00,
  0x08
}
*/


static set_act00_data banana_set_tbl = {
  0,
  {
    { &saru00_banana, 0, 0 }
  }
};


static set_act01_data yasi_set_tbl = {
  0,
  {
    { &emyshot, &yasi_init_tbl, 0, &speedsetg20, 0, 0, -512, -1024 }
  }
};


static signed char saru00_pg00[4] = { 7, 0, 1, -4 };
static signed char saru00_pg01[5] = { 0, 7, 2, 7, -4 };


static signed char banana_pg00[10] = { 8, 15, 8, 15, 9, 15, 10, 15, -8, 10 };
static signed char banana_pg01[5] = { 6, 126, -4, -121, -37 };
