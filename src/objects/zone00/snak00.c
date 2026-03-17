#include "snak00.h"
#include "../../data/pat/zone00/saru00.h"
#include "../../data/pat/zone00/snak00.h"
#include "../../types/enemyinitdata.h"
#include "../../types/setactdata.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../action.h"
#include "../../constants.h"
#include "../../shared.h"
static void snak00_framein(SKC_sprite_status* p_actwk);
static void snak00_init(SKC_sprite_status* p_actwk);
static void snak00_puka_init(SKC_sprite_status* p_actwk);
static void snak00_move0(SKC_sprite_status* p_actwk);
static void snak00_move1(SKC_sprite_status* p_actwk);
static void snak00_move2(SKC_sprite_status* p_actwk);
static void snak00_body(SKC_sprite_status* p_actwk);
static void snak00_body_init(SKC_sprite_status* p_actwk);
static void snak00_body_wait0(SKC_sprite_status* p_actwk);
static void snak00_fire(SKC_sprite_status* p_actwk);
static void snak00_fire_wait0(SKC_sprite_status* p_actwk);
static void chk_fire(SKC_sprite_status* p_actwk);
static void set_fire(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data snak00_init_tbl;
static SKC_enemy_init0_data snak00_body_init_tbl0;
static SKC_enemy_init0_data snak00_body_init_tbl1;
static SKC_enemy_init0_data snak00_body_init_tbl2;
static SKC_enemy_init2_data snak00_fire_init_tbl;
static SKC_set_act02_data snak00_set_tbl;
static SKC_set_act00_data snak00_fire_set_tbl;
static signed char snak00_pg00[12];


void snak00(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &snak00_framein);
  snak00_framein(p_actwk);
}


static void snak00_framein(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &snak00_init,
    &snak00_move0,
    &snak00_move0,
    &snak00_move1,
    &snak00_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void snak00_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &snak00_init_tbl);
  p_actwk->xspeed = -0x100;
  set_act02(p_actwk, &snak00_set_tbl);
  snak00_puka_init(p_actwk);
}


static void snak00_puka_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.puka.cnt = 3;
  p_actwk->u.obj.puka.accel_max = 0x80;
  p_actwk->yspeed = 0x80;
  p_actwk->u.obj.puka.accel = 8;
  p_actwk->u.obj.actflg0.puka_down = 0;
}


static void snak00_move0(SKC_sprite_status* p_actwk) {
  if (!puka_count(p_actwk)) {
    speedset2(p_actwk);
    chk_fire(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    p_actwk->u.obj.puka.accel_max = 0x100;
    p_actwk->yspeed = 0x100;
    p_actwk->u.obj.puka.accel = 8;
    p_actwk->u.obj.actflg0.puka_down = 0;
  }
}


static void snak00_move1(SKC_sprite_status* p_actwk) {
  if (puka_puka(p_actwk)) {
    p_actwk->r_no = 8;
    p_actwk->xspeed = -p_actwk->xspeed;
    p_actwk->actflg.hflip ^= 1;
  }
  speedset2(p_actwk);
  chk_fire(p_actwk);
}


static void snak00_move2(SKC_sprite_status* p_actwk) {
  if (puka_puka(p_actwk)) {
    snak00_puka_init(p_actwk);
  }
  else {
    speedset2(p_actwk);
    chk_fire(p_actwk);
  }
}


static void snak00_body(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[] = {
    &snak00_body_init,
    &snak00_body_wait0,
    &snak00_move0,
    &snak00_move1,
    &snak00_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_tobi_diec0(p_actwk, 0);
}


static void snak00_body_init(SKC_sprite_status* p_actwk) {
  SKC_enemy_init0_data* init_tbl[6] = {
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

  SKC_enemy_init0_data* p_data = init_tbl[p_actwk->u.obj.userflag / 2];
  p_actwk->u.obj.timer = timer_tbl[p_actwk->u.obj.userflag / 2];
  enemy_init0(p_actwk, p_data);
}


static void snak00_body_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_no = 4;
  p_actwk->u.obj.timer = 64 - (p_actwk->u.obj.userflag + 2) * 4;
  p_actwk->u.obj.callback_ptr = &set_fire;
  p_actwk->xspeed = -0x100;
  snak00_puka_init(p_actwk);
}


static void snak00_fire(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &snak00_fire_init_tbl);
  p_actwk->r_ptr = &snak00_fire_wait0;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  p_actwk->u.obj.cddat.flame_baria_die = 1;
  chk_oya_die0(p_actwk);
}


static void snak00_fire_wait0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  time_pg0(p_actwk, snak00_pg00);
  chk_oya_die0(p_actwk);
}


static void chk_fire(SKC_sprite_status* p_actwk) {
  if (p_actwk->r_ptr != &snak00_body) return;
  if (p_actwk->u.obj.userflag >= 6) return;

  dec_timer(p_actwk);
}


static void set_fire(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 26;
  set_act00(p_actwk, &snak00_fire_set_tbl);
}


static SKC_enemy_init0_data snak00_init_tbl = {
  snak00pat,
  0xA55F,
  PRI_5,
  8,
  8,
  0,
  0x17
};


static SKC_enemy_init0_data snak00_body_init_tbl0 = {
  snak00pat,
  0xA55F,
  PRI_5,
  8,
  12,
  1,
  0x97
};


static SKC_enemy_init0_data snak00_body_init_tbl1 = {
  snak00pat,
  0xA55F,
  PRI_5,
  8,
  8,
  2,
  0x97
};


static SKC_enemy_init0_data snak00_body_init_tbl2 = {
  saru00pat,
  0xA548,
  PRI_5,
  4,
  4,
  3,
  0x98
};


static SKC_enemy_init2_data snak00_fire_init_tbl = {
  PRI_4,
  16,
  16,
  3,
  0
};


static SKC_set_act02_data snak00_set_tbl = {
  5,
  &snak00_body,
  0,
  0
};


static SKC_set_act00_data snak00_fire_set_tbl = {
  0,
  {
    { &snak00_fire, 0, 0 }
  }
};


static signed char snak00_pg00[12] = { 3, 2, 3, 2, 4, 3, 5, 4, -12, -121, -37, -112 };
