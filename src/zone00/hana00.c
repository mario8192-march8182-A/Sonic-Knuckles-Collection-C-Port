#include "hana00.h"
#include "../data/pat/zone00/hana00.h"
#include "../types/setact01data.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../action.h"
#include "../emyshot.h"
#include "../shared.h"
static void hana00_framein(SKC_sprite_status* p_actwk);
static void hana00_init(SKC_sprite_status* p_actwk);
static void hana00_wait(SKC_sprite_status* p_actwk);
static void hana00_shot_init(SKC_sprite_status* p_actwk);
static void hana00_shot(SKC_sprite_status* p_actwk);
static void hana00_wait_init(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data hana00_init_tbl;
static SKC_enemy_init0_data hana00_shot_init_tbl;
static SKC_set_act01_data hana00_shot_set_tbl;
static signed char hana00_pg00[19];


void hana00(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &hana00_framein);
  hana00_framein(p_actwk);
}


static void hana00_framein(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &hana00_init,
    &hana00_wait,
    &hana00_shot
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
};


static void hana00_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &hana00_init_tbl);
  p_actwk->u.obj.timer = 31;
  p_actwk->u.obj.callback_ptr = &hana00_shot_init;
}


static void hana00_wait(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) return;

  dec_timer(p_actwk);
}


static void hana00_shot_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.pg_data_ptr = hana00_pg00;
  p_actwk->u.obj.callback_ptr = &hana00_wait_init;
}


static void hana00_shot(SKC_sprite_status* p_actwk) {
  if (time_pg(p_actwk) == 0) return;
  if (p_actwk->patcnt + 2 != 6 && p_actwk->patcnt + 2 != 14) return;

  soundset(77);
  SKC_sprite_status* p_new_actwk = set_act01(p_actwk, &hana00_shot_set_tbl);
  if (p_new_actwk != 0) {
    ++p_actwk->u.obj.actfree.hana00.counter;
    if (BIT_IS_SET(p_actwk->u.obj.actfree.hana00.counter, 0)) {
      p_new_actwk->xspeed = -p_new_actwk->xspeed;
    }
  }
}


static void hana00_wait_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->u.obj.timer = 120;
  p_actwk->u.obj.callback_ptr = &hana00_shot_init;
}


static SKC_enemy_init0_data hana00_init_tbl = {
  hana00pat,
  0x252A,
  PRI_4,
  12,
  24,
  0,
  0x23
};


static SKC_enemy_init0_data hana00_shot_init_tbl = {
  hana00pat,
  0x252A,
  PRI_5,
  8,
  8,
  4,
  0x98
};


static SKC_set_act01_data hana00_shot_set_tbl = {
  0,
  {
    { &emyshot, &hana00_shot_init_tbl, 0, &speedset, 0, -16, 0x100, -0x500 }
  }
};


static signed char hana00_pg00[19] = { 0, 7, 1, 9, 2, 4, 3, 4, 0, 9, 1, 9, 2, 4, 3, 4, 0, 0, -12 };
