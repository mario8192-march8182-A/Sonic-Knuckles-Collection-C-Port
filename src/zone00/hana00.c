#include "../globals.h"
#include "../macros.h"
#include "hana00.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"
#include "../emyshot.h"
#include "../resources.h"
static void hana00_framein(sprite_status* p_actwk);
static void hana00_init(sprite_status* p_actwk);
static void hana00_wait(sprite_status* p_actwk);
static void hana00_shot_init(sprite_status* p_actwk);
static void hana00_shot(sprite_status* p_actwk);
static void hana00_wait_init(sprite_status* p_actwk);
static enemy_init0_data hana00_init_tbl;
static enemy_init0_data hana00_shot_init_tbl;
static set_act01_data hana00_shot_set_tbl;
static signed char hana00_pg00[19];


void hana00(sprite_status* p_actwk) {
  chk_framein(p_actwk, &hana00_framein);
  hana00_framein(p_actwk);
}


static void hana00_framein(sprite_status* p_actwk) {
  static void(*act_tbl[3])(sprite_status*) = {
    &hana00_init,
    &hana00_wait,
    &hana00_shot
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
};


static void hana00_init(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &hana00_init_tbl);
  p_actwk->actfree.hana00.shot_countdown = 31;
  p_actwk->actfree.hana00.callback_ptr = &hana00_shot_init;
}


static void hana00_wait(sprite_status* p_actwk) {
  if (BIT_7_IS_SET(p_actwk->actflg)) {
    dec_timer(p_actwk);
  }
}


static void hana00_shot_init(sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->actfree.hana00.pg_data_ptr = hana00_pg00;
  p_actwk->actfree.hana00.callback_ptr = &hana00_wait_init;
}


static void hana00_shot(sprite_status* p_actwk) {
  int ret = time_pg(p_actwk, p_actwk->actfree.hana00.pg_data_ptr);
  if (ret == 0) return;
  if (p_actwk->patcnt != 6 && p_actwk->patcnt != 14) return;
  soundset(77);
  sprite_status* p_new_actwk = set_act01(p_actwk, &hana00_shot_set_tbl);
  if (p_new_actwk == 0) return;
  ++p_actwk->actfree.hana00.counter;
  if (BIT_0_IS_SET(p_actwk->actfree.hana00.counter)) {
    p_new_actwk->xspeed = -p_new_actwk->xspeed;
  }
}


static void hana00_wait_init(sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->actfree.hana00.shot_countdown = 120;
  p_actwk->actfree.hana00.callback_ptr = &hana00_shot_init;
}


static enemy_init0_data hana00_init_tbl = {
  hana00pat,
  9514,
  PRI_4,
  12,
  24,
  0,
  35
};


static enemy_init0_data hana00_shot_init_tbl = {
  hana00pat,
  9514,
  PRI_5,
  8,
  8,
  4,
  152
};


static set_act01_data hana00_shot_set_tbl = {
  0,
  {
    { &emyshot, &hana00_shot_init_tbl, 0, &speedset, 0, -16, 256, -1280 }
  }
};


static signed char hana00_pg00[19] = { 0, 7, 1, 9, 2, 4, 3, 4, 0, 9, 1, 9, 2, 4, 3, 4, 0, 0, -12 };
