#include "../globals.h"
#include "../macros.h"
#include "../types/enemyinit2data.h"
#include "../types/setact00data.h"
#include "../types/setact02data.h"
#include "snak00.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"
#include "../resources.h"
static void snak00_framein(sprite_status* p_actwk);
static void snak00_init(sprite_status* p_actwk);
static void snak00_puka_init(sprite_status* p_actwk);
static void snak00_move0(sprite_status* p_actwk);
static void snak00_move1(sprite_status* p_actwk);
static void snak00_move2(sprite_status* p_actwk);
static void snak00_body(sprite_status* p_actwk);
static void snak00_body_init(sprite_status* p_actwk);
static void snak00_body_wait0(sprite_status* p_actwk);
static void snak00_fire(sprite_status* p_actwk);
static void snak00_fire_wait0(sprite_status* p_actwk);
static void chk_fire(sprite_status* p_actwk);
static void set_fire(sprite_status* p_actwk);
static enemy_init0_data snak00_init_tbl;
static enemy_init0_data snak00_body_init_tbl0;
static enemy_init0_data snak00_body_init_tbl1;
static enemy_init0_data snak00_body_init_tbl2;
static enemy_init2_data snak00_fire_init_tbl;
static set_act02_data snak00_set_tbl;
static set_act00_data snak00_fire_set_tbl;
static signed char snak00_pg00[12];


void snak00(sprite_status* p_actwk) {
  chk_framein(p_actwk, &snak00_framein);
  snak00_framein(p_actwk);
}


static void snak00_framein(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[5] = {
    &snak00_init,
    &snak00_move0,
    &snak00_move0,
    &snak00_move1,
    &snak00_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void snak00_init(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &snak00_init_tbl);
  p_actwk->xspeed = -256;
  set_act02(p_actwk, &snak00_set_tbl);
  snak00_puka_init(p_actwk);
}


static void snak00_puka_init(sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->actfree.snak00.puka_cnt = 3;
  p_actwk->actfree.snak00.accel_max = 128;
  p_actwk->yspeed = 128;
  p_actwk->actfree.snak00.accel = 8;
  CLEAR_BIT_0(p_actwk->actfree.snak00.status_bitfield);
}


static void snak00_move0(sprite_status* p_actwk) {
  bool countdown_reached = puka_count(p_actwk);
  if (!countdown_reached) {
    speedset2(p_actwk);
    chk_fire(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    p_actwk->actfree.snak00.accel_max = 256;
    p_actwk->yspeed = 256;
    p_actwk->actfree.snak00.accel = 8;
    CLEAR_BIT_0(p_actwk->actfree.snak00.status_bitfield);
  }
}


static void snak00_move1(sprite_status* p_actwk) {
  bool axis_dir_changed = puka_puka(p_actwk);
  if (axis_dir_changed) {
    p_actwk->r_no = 8;
    p_actwk->xspeed = -p_actwk->xspeed;
    TOGGLE_BIT(p_actwk->actflg, FLG_HFLIP);
  }
  speedset2(p_actwk);
  chk_fire(p_actwk);
}


static void snak00_move2(sprite_status* p_actwk) {
  bool axis_dir_changed = puka_puka(p_actwk);
  if (axis_dir_changed) {
    snak00_puka_init(p_actwk);
  }
  else {
    speedset2(p_actwk);
    chk_fire(p_actwk);
  }
}


static void snak00_body(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[] = {
    &snak00_body_init,
    &snak00_body_wait0,
    &snak00_move0,
    &snak00_move1,
    &snak00_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_tobi_diec0(p_actwk, 0);
}


static void snak00_body_init(sprite_status* p_actwk) {
  enemy_init0_data* init_tbl[6] = {
    &snak00_body_init_tbl0,
    &snak00_body_init_tbl0,
    &snak00_body_init_tbl0,
    &snak00_body_init_tbl1,
    &snak00_body_init_tbl2,
    &snak00_body_init_tbl2
  };
  unsigned char timer_tbl[6] = {
    11, 23, 35, 47, 55, 63
  };

  enemy_init0_data* p_data = init_tbl[p_actwk->userflag1 / 2];
  p_actwk->actfree.snak00.timer = timer_tbl[p_actwk->userflag1 / 2];
  enemy_init0(p_actwk, p_data);
}


static void snak00_body_wait0(sprite_status* p_actwk) {
  --p_actwk->actfree.snak00.timer;
  if (p_actwk->actfree.snak00.timer >= 0) return;
  p_actwk->r_no = 4;
  p_actwk->actfree.snak00.timer = 64 - (p_actwk->userflag1 + 2) * 4;
  p_actwk->actfree.snak00.callback_ptr = &set_fire;
  p_actwk->xspeed = -256;
  snak00_puka_init(p_actwk);
}


static void snak00_fire(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &snak00_fire_init_tbl);
  p_actwk->r_ptr = &snak00_fire_wait0;
  p_actwk->actfree.snak00.callback_ptr = &set_emy_fout0;
  SET_BIT_4(p_actwk->cddat2);
  chk_oya_die0(p_actwk);
}


static void snak00_fire_wait0(sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  time_pg(p_actwk, snak00_pg00);
  chk_oya_die0(p_actwk);
}


static void chk_fire(sprite_status* p_actwk) {
  if (p_actwk->r_ptr != &snak00_body) return;
  if (p_actwk->userflag1 >= 6) return;
  dec_timer(p_actwk);
}


static void set_fire(sprite_status* p_actwk) {
  p_actwk->actfree.snak00.timer = 26;
  set_act00(p_actwk, &snak00_fire_set_tbl);
}


static enemy_init0_data snak00_init_tbl = {
  snak00pat,
  42335,
  PRI_5,
  8,
  8,
  0,
  23
};


static enemy_init0_data snak00_body_init_tbl0 = {
  snak00pat,
  42335,
  PRI_5,
  8,
  12,
  1,
  151
};


static enemy_init0_data snak00_body_init_tbl1 = {
  snak00pat,
  42335,
  PRI_5,
  8,
  8,
  2,
  151
};


static enemy_init0_data snak00_body_init_tbl2 = {
  saru00pat,
  42312,
  PRI_5,
  4,
  4,
  3,
  152
};


static enemy_init2_data snak00_fire_init_tbl = {
  PRI_4,
  16,
  16,
  3,
  0
};


static set_act02_data snak00_set_tbl = {
  5,
  &snak00_body,
  0,
  0
};


static set_act00_data snak00_fire_set_tbl = {
  0,
  {
    { &snak00_fire, 0, 0 }
  }
};


static signed char snak00_pg00[12] = { 3, 2, 3, 2, 4, 3, 5, 4, -12, -121, -37, -112 };
