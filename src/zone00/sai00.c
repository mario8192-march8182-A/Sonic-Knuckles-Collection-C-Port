#include "../globals.h"
#include "../macros.h"
#include "sai00.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"
#include "../resources.h"
static void sai00_framein(sprite_status* p_actwk);
static void sai00_init(sprite_status* p_actwk);
static void sai00_wait(sprite_status* p_actwk);
static void sai00_atwait(sprite_status* p_actwk);
static void sai00_attack(sprite_status* p_actwk);
static void sai00_kemuri(sprite_status* p_actwk);
static void sai00_kemuri_init(sprite_status* p_actwk);
static void sai00_kemuri_wait(sprite_status* p_actwk);
static void sai00_wait_init0(sprite_status* p_actwk);
static void sai00_wait_init1(sprite_status* p_actwk);
static void sai00_turn_init(sprite_status* p_actwk);
static void sai00_atwait_init(sprite_status* p_actwk);
static void sai00_attack_init(sprite_status* p_actwk);
static void sai00_atturn_init(sprite_status* p_actwk);
static void chk_max_speed(sprite_status* p_actwk);
static void set_spd_pt(sprite_status* p_actwk);
static bool chk_attack(sprite_status* p_actwk, sprite_status_handler p_callback);
static bool sai00_down_col(sprite_status* p_actwk, sprite_status_handler p_callback);
static wrt_init_data sai00_init_tbl;
static wrt_init_data sai00_kemuri_init_tbl;
static set_act00_data sai00_kemuri_set_tbl0;
static set_act00_data sai00_kemuri_set_tbl1;
static wrt_data sai00_wrt_tbl;
unsigned char sai00_pg01[16];
unsigned char sai00_pg02[12];


void sai00(sprite_status* p_actwk) {
  chk_framein(p_actwk, &sai00_framein);
  sai00_framein(p_actwk);
}


static void sai00_framein(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[4] = {
    &sai00_init,
    &sai00_wait,
    &sai00_atwait,
    &sai00_attack
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &sai00_wrt_tbl);
  chk_emy_foutwc0(p_actwk);
}


static void sai00_init(sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &sai00_init_tbl);
  p_actwk->sprhsize = 8;
  p_actwk->sprvsize = 16;
  short accel = -16;
  short accel_max = -768;
  if (IS_HFLIP(p_actwk->actflg)) {
    accel = -accel;
    accel_max = -accel_max;
    SET_BIT_3(p_actwk->actfree.sai00.status_bitfield);
  }
  p_actwk->actfree.sai00.accel = accel;
  p_actwk->actfree.sai00.accel_max = accel_max;
  p_actwk->actfree.sai00.callback_ptr = &sai00_wait_init0;
}


static void sai00_wait(sprite_status* p_actwk) {
  bool attacking = chk_attack(p_actwk, &sai00_atwait_init);
  if (!attacking) {
    bool turning = sai00_down_col(p_actwk, &sai00_turn_init);
    if (!turning) {
      p_actwk->xspeed += p_actwk->actfree.sai00.accel;
      speedset2(p_actwk);
      chk_max_speed(p_actwk);
      set_spd_pt(p_actwk);
    }
  }
}


static void sai00_atwait(sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void sai00_attack(sprite_status* p_actwk) {
  bool turning = sai00_down_col(p_actwk, &sai00_atturn_init);
  if (!turning) {
    speedset2(p_actwk);
  }
}


static void sai00_kemuri(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[2] = {
    &sai00_kemuri_init,
    &sai00_kemuri_wait
  };

  if (!(stageno.zone == ANGEL_ISLAND && stageno.act == 1)) {
    ko_offset1(p_actwk);
    act_tbl[p_actwk->r_no / 2](p_actwk);
    set_emy_wchg(p_actwk, &sai00_wrt_tbl);
    chk_oya_diew0(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void sai00_kemuri_init(sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &sai00_kemuri_init_tbl);
  p_actwk->actfree.sai00_kemuri.callback_ptr = &wchg_die;
  sai00_kemuri_wait(p_actwk);
}


static void sai00_kemuri_wait(sprite_status* p_actwk) {
  pt_chg(p_actwk);
}


static void sai00_wait_init0(sprite_status* p_actwk) {
  TOGGLE_BIT_2(p_actwk->actfree.sai00.status_bitfield);
  p_actwk->actfree.sai00.callback_ptr = &sai00_wait_init1;
  p_actwk->actfree.sai00.accel = -p_actwk->actfree.sai00.accel;
  p_actwk->actfree.sai00.accel_max = -p_actwk->actfree.sai00.accel_max;
}


static void sai00_wait_init1(sprite_status* p_actwk) {
  TOGGLE_BIT_3(p_actwk->actfree.sai00.status_bitfield);
  TOGGLE_HFLIP(p_actwk->actflg);
  CLEAR_BIT_1(p_actwk->actfree.sai00.status_bitfield);
  p_actwk->actfree.sai00.callback_ptr = &sai00_wait_init0;
}


static void sai00_turn_init(sprite_status* p_actwk) {
  CLEAR_BIT_2(p_actwk->actfree.sai00.status_bitfield);
  if (!BIT_3_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
    SET_BIT_2(p_actwk->actfree.sai00.status_bitfield);
  }
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  sai00_wait_init1(p_actwk);
}


static void sai00_atwait_init(sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->patno = 0;
  p_actwk->actfree.sai00.attack_countdown = 32;
  p_actwk->actfree.sai00.callback_ptr = &sai00_attack_init;
  SET_BIT_1(p_actwk->actfree.sai00.status_bitfield);
  soundset(72);
  sprite_status* p_new_actwk = set_act00(p_actwk, &sai00_kemuri_set_tbl1);
  if (p_new_actwk != 0) {
    p_new_actwk->actfree.sai00_kemuri.pg_data_ptr = sai00_pg02;
  }
}


static void sai00_attack_init(sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  short xspeed = 1024;
  if (!BIT_3_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
}


static void sai00_atturn_init(sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->patno = 0;
  sai00_turn_init(p_actwk);
}


static void chk_max_speed(sprite_status* p_actwk) {
  if (p_actwk->xspeed != 0) {
    if (BIT_2_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
      if (p_actwk->xspeed < p_actwk->actfree.sai00.accel_max) return;
    }
    else if (p_actwk->xspeed > p_actwk->actfree.sai00.accel_max) return;
  }
  p_actwk->actfree.sai00.callback_ptr(p_actwk);
}


static void set_spd_pt(sprite_status* p_actwk) {
  unsigned char patno = 0;
  if (BIT_3_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
    // move_right
    if (BIT_2_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
      patno = 1;
    }
    else {
      patno = 1;
      if (p_actwk->xspeed <= 640) {
        patno = 2;
        bool bit_1_set = BIT_1_IS_SET(p_actwk->actfree.sai00.status_bitfield);
        SET_BIT_1(p_actwk->actfree.sai00.status_bitfield);
        if (!bit_1_set) goto set_kemuri;
      }
    }
  }
  else {
    // move_left
    if (!BIT_2_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
      if (p_actwk->xspeed > -128) {
        patno = 1;
      }
      else {
        patno = 1;
        if (p_actwk->xspeed > -640) {
          patno = 2;
          bool bit_1_set = BIT_1_IS_SET(p_actwk->actfree.sai00.status_bitfield);
          SET_BIT_1(p_actwk->actfree.sai00.status_bitfield);
          if (!bit_1_set) goto set_kemuri;
        }
      }
    }
  }
  p_actwk->patno = patno;
  return;

set_kemuri:
  p_actwk->patno = patno;
  soundset(72);
  sprite_status* p_new_actwk = set_act00(p_actwk, &sai00_kemuri_set_tbl0);
  if (p_new_actwk != 0) {
    p_new_actwk->actfree.sai00_kemuri.pg_data_ptr = sai00_pg01;
  }
}


static bool chk_attack(sprite_status* p_actwk, sprite_status_handler p_callback) {
  bool pl_is_right, pl_is_below;
  short pl_x_distance, pl_y_distance;
  chk_distance(p_actwk, &pl_is_right, &pl_is_below, &pl_x_distance, &pl_y_distance);
  if (pl_y_distance > 32) return false; // unsigned
  if (pl_x_distance > 96) return false; // unsigned
  if (!BIT_3_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
    pl_is_right = !pl_is_right;
  }
  if (pl_is_right) {
    p_callback(p_actwk);
    return true;
  }
  return false;
}


static bool sai00_down_col(sprite_status* p_actwk, sprite_status_handler p_callback) {
  short offset = 4;
  if (!BIT_3_IS_SET(p_actwk->actfree.sai00.status_bitfield)) {
    offset = -offset;
  }
  short xposi = LONG_HIGH(p_actwk->xposi) + offset;
  short unknown = ObjCheckFloorDist2(p_actwk, xposi);
  if (unknown >= -1 && unknown < 12) {
    p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown);
    return false;
  }
  p_callback(p_actwk);
  return true;
}


static wrt_init_data sai00_init_tbl = {
  1,
  9472,
  21,
  0,
  sai00pat,
  PRI_5,
  20,
  16,
  0,
  11
};


static wrt_init_data sai00_kemuri_init_tbl = {
  1,
  1098,
  6,
  2,
  sai00pat,
  PRI_4,
  12,
  8,
  4,
  0
};


static set_act00_data sai00_kemuri_set_tbl0 = {
  0,
  {
    { &sai00_kemuri, 12, 8 }
  }
};


static set_act00_data sai00_kemuri_set_tbl1 = {
  0,
  {
    { &sai00_kemuri, 16, 8 }
  }
};


static wrt_data sai00_wrt_tbl = {
  sai00_tiles,
  sai00_tbl
};


unsigned char sai00_pg01[16] = { 2, 4, 4, 5, 6, 7, 4, 5, 6, 7, 4, 5, 6, 7, -12, -112 };
unsigned char sai00_pg02[12] = { 2, 4, 4, 5, 6, 7, 4, 5, 6, 7, -12, -112 };
