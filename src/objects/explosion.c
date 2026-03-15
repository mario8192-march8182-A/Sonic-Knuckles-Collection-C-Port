#include "explosion.h"
#include "../types/enemyinit0data.h"
#include "../types/setact00data.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/fp16.h"
#include "../action.h"
#include "../etc.h"
#include "../shared.h"
#include "../sound.h"
#include "common.h"
static void bsexp_move(SKC_sprite_status* p_actwk);
static void set_ran_posi(SKC_sprite_status* p_actwk, SKC_sprite_status* p_new_actwk);
static void exp01_frameout(SKC_sprite_status* p_actwk);
static void set_bakuhatu(SKC_sprite_status* p_actwk);
static void set_exp01i(SKC_sprite_status* p_actwk);
static void set_exp07(SKC_sprite_status* p_actwk);
static void exp01_init(SKC_sprite_status* p_actwk);
static void exp01_init0(SKC_sprite_status* p_actwk);
static void exp01i(SKC_sprite_status* p_actwk);
static void exp07(SKC_sprite_status* p_actwk);
static void exp07_pchg(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data exp01i_init_tbl;
static SKC_set_act05_data exp01_set_tbl;
static SKC_set_act05_data exp01i_set_tbl;
static SKC_set_act05_data exp07_set_tbl;
static SKC_set_act05_data bakuhatu_set_tbl;
static SKC_sprite_pattern exp01_pt00;
static SKC_sprite_pattern exp01_pt01;
static SKC_sprite_pattern exp01_pt02;
static SKC_sprite_pattern exp01_pt03;
static SKC_sprite_pattern exp01_pt04;
static SKC_sprite_pattern exp01_pt05;

extern sonic3_ram g_ram;


void bsexp01_set(SKC_sprite_status* p_actwk) {
  struct {
    SKC_sprite_status_handler r_ptr;
    SKC_sprite_status_handler callback_ptr;
  }
  act_adr_tbl[7] = {
    { &dec_timer, &set_exp01 },
    { &bsexp_move, &set_exp01 },
    { &dec_timer, &set_bakuhatu },
    { &dec_timer, &set_exp01i },
    { &bsexp_move, &set_exp01i },
    { &bsexp_move, &set_bakuhatu },
    { &bsexp_move, &set_exp07 }
  };
  signed char data_tbl[17][4] = {
    {   32,   32,   32,  0 },
    {   40, -128, -128, 24 },
    { -128,   32,   32,  8 },
    {    4,   16,   16,  0 },
    {    8,   32,   32, 16 },
    {   32,   32,   32,  0 },
    {   64, -128,   32,  0 },
    { -128,   64,   64,  8 },
    {   32,   32,   32, 24 },
    { -128,   32,   32, 32 },
    {    8, -128,   32, 16 },
    { -128, -128, -128,  8 },
    { -128, -128, -128, 40 },
    { -128,   64,   64, 40 },
    { -128, -128,   64,  8 },
    { -128,   16,   16,  8 },
    { -128,   32,   32, 48 }
  };

  p_actwk->u.obj.actfree.explosion.unknown39 = data_tbl[p_actwk->u.obj.userflag / 2][0];
  p_actwk->u.obj.actfree.explosion.unknown3a = data_tbl[p_actwk->u.obj.userflag / 2][1];
  p_actwk->u.obj.actfree.explosion.unknown3b = data_tbl[p_actwk->u.obj.userflag / 2][2];
  unsigned char type = data_tbl[p_actwk->u.obj.userflag / 2][3];
  p_actwk->r_ptr = act_adr_tbl[type / 2].r_ptr;
  p_actwk->u.obj.callback_ptr = act_adr_tbl[type / 2].callback_ptr;
  p_actwk->r_ptr(p_actwk);
}


static void bsexp_move(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.end == 1 || p_parentwk->r_ptr == 0) {
    exp01_frameout(p_actwk);
  }
  else  {
    dec_timer(p_actwk);
  }
}


void set_exp01(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.explosion.unknown39 >= 0) {
    --p_actwk->u.obj.actfree.explosion.unknown39;
    if (p_actwk->u.obj.actfree.explosion.unknown39 == 0) {
      exp01_frameout(p_actwk);
    }
  }
  else {
    p_actwk->u.obj.timer = 2;
    set_exp01_posi(p_actwk);
  }
}


void set_exp01_posi(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &exp01_set_tbl);
  if (p_new_actwk != 0) {
    set_ran_posi(p_actwk, p_new_actwk);
  }
}


static void set_ran_posi(SKC_sprite_status* p_actwk, SKC_sprite_status* p_new_actwk) {
  long offsets = random();
  short xoffset = (offsets & 0x00FF) & p_actwk->u.obj.actfree.explosion.unknown3a * 2 - 1;
  xoffset -= p_actwk->u.obj.actfree.explosion.unknown3a;
  fp16_set_integer(&p_new_actwk->xposi, fp16_get_integer(p_new_actwk->xposi) + xoffset);
  short yoffset = ((offsets & 0xFF00) >> 16) & p_actwk->u.obj.actfree.explosion.unknown3b * 2 - 1;
  yoffset -= p_actwk->u.obj.actfree.explosion.unknown3b;
  fp16_set_integer(&p_new_actwk->yposi, fp16_get_integer(p_new_actwk->yposi) + yoffset);
}


static void exp01_frameout(SKC_sprite_status* p_actwk) {
  set_emy_fout0(p_actwk);
}


static void set_bakuhatu(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.actfree.explosion.unknown39;
  if (p_actwk->u.obj.actfree.explosion.unknown39 == 0) {
    exp01_frameout(p_actwk);
  }
  else {
    p_actwk->u.obj.timer = 2;
    SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &bakuhatu_set_tbl);
    if (p_new_actwk != 0) {
      p_new_actwk->r_no = 2;
      p_new_actwk->sproffset |= 0x8000;
      set_ran_posi(p_actwk, p_new_actwk);
    }
  }
}


static void set_exp01i(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.actfree.explosion.unknown39;
  if (p_actwk->u.obj.actfree.explosion.unknown39 == 0) {
    exp01_frameout(p_actwk);
  }
  else {
    p_actwk->u.obj.timer = 2;
    SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &exp01i_set_tbl);
    if (p_new_actwk != 0) {
      set_ran_posi(p_actwk, p_new_actwk);
    }
  }
}


static void set_exp07(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.actfree.explosion.unknown39;
  if (p_actwk->u.obj.actfree.explosion.unknown39 == 0) {
    exp01_frameout(p_actwk);
  }
  else {
    p_actwk->u.obj.timer = 2;
    SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &exp07_set_tbl);
    if (p_new_actwk != 0) {
      set_ran_posi(p_actwk, p_new_actwk);
    }
  }
}


void screxp01_set(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 2;
  short xposi = (g_ram.scra_h_posit >> 16) + 160;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (g_ram.scra_v_posit >> 16) + 112;
  fp16_set_integer(&p_actwk->yposi, yposi);
  p_actwk->u.obj.userflag = 2;
  bsexp01_set(p_actwk);
}


void exp01(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &exp01_init_tbl);
  exp01_init(p_actwk);
}


static void exp01_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &exp01_pchg;
  exp01_init0(p_actwk);
}


static void exp01_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  soundset(-76);
  exp01_pchg(p_actwk);
}


void exp01_pchg(SKC_sprite_status* p_actwk) {
  time_pg0(p_actwk, exp01_pg00);
  actionsub(p_actwk);
}


static void exp01i(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &exp01i_init_tbl);
  exp01_init(p_actwk);
}


static void exp07(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &exp01_init_tbl);
  p_actwk->r_ptr = &exp07_pchg;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  soundset(-76);
  exp07_pchg(p_actwk);
}


static void exp07_pchg(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - g_ram.frame_offset_x);
  time_pg0(p_actwk, exp01_pg00);
  actionsub(p_actwk);
}


SKC_enemy_init0_data exp01_init_tbl = {
  exp01_pt,
  0x8500,
  PRI_0,
  12,
  12,
  0,
  0
};


static SKC_enemy_init0_data exp01i_init_tbl = {
  exp01_pt,
  0x84D2,
  PRI_0,
  12,
  12,
  0,
  0
};


signed char exp01_pg00[16] = { 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 4, -12, -112 };


static SKC_set_act05_data exp01_set_tbl = {
  0,
  &exp01
};


static SKC_set_act05_data exp01i_set_tbl = {
  0,
  &exp01i
};


static SKC_set_act05_data exp07_set_tbl = {
  0,
  &exp07
};


SKC_set_act00_data bsexp01_set_tbl = {
  0,
  {
    { &bsexp01_set, 0, 0 }
  }
};


static SKC_set_act05_data bakuhatu_set_tbl = {
  0,
  &bakuhatu
};


SKC_sprite_pattern* exp01_pt[6] = {
  &exp01_pt00,
  &exp01_pt01,
  &exp01_pt02,
  &exp01_pt03,
  &exp01_pt04,
  &exp01_pt05
};


static SKC_sprite_pattern exp01_pt00 = {
  1,
  {
    { -8, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern exp01_pt01 = {
  1,
  {
    { -12, 10, 0x0004, -12 }
  }
};
static SKC_sprite_pattern exp01_pt02 = {
  1,
  {
    { -12, 10, 0x000D, -12 }
  }
};
static SKC_sprite_pattern exp01_pt03 = {
  1,
  {
    { -12, 10, 0x0016, -12 }
  }
};
static SKC_sprite_pattern exp01_pt04 = {
  1,
  {
    { -13, 10, 0x001F, -12 }
  }
};
static SKC_sprite_pattern exp01_pt05 = {
  1,
  {
    { -10, 9, 0x0028, -12 }
  }
};
