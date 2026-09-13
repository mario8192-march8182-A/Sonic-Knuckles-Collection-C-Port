#include "betl04.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../dircol.h"
#include "../../shared.h"
#include "../emyshot.h"
static void betl04plus6(SKC_sprite_status* p_actwk);
static void betl04_init(SKC_sprite_status* p_actwk);
static void betl04_move0(SKC_sprite_status* p_actwk);
static void betl04_wait0_init(SKC_sprite_status* p_actwk);
static void betl04_wait0(SKC_sprite_status* p_actwk);
static void betl04_move0_init(SKC_sprite_status* p_actwk);
static void betl04_move0_init0(SKC_sprite_status* p_actwk);
static void betl04_wait1(SKC_sprite_status* p_actwk);
static void betl04_shot0(SKC_sprite_status* p_actwk);
static void betl04_up0(SKC_sprite_status* p_actwk);
static void betl04_up1(SKC_sprite_status* p_actwk);
static void betl04_down0(SKC_sprite_status* p_actwk);
static void betl04_mazuru(SKC_sprite_status* p_actwk);
static void betl04_mazuru_pchg0(SKC_sprite_status* p_actwk);
static void betl04_init0(SKC_sprite_status* p_actwk);
static void betl04_jump0(SKC_sprite_status* p_actwk);
static void betl04_move0_init1(SKC_sprite_status* p_actwk);
static bool chk_magnet(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data betl04_init_tbl;
static SKC_enemy_init2_data betl04_mazuru_init_tbl;
static SKC_enemy_init0_data betl04_shot_init_tbl;
static SKC_enemy_init0_data betl04_yakyo_init_tbl;
static SKC_set_act00_data betl04_mazuru_set_tbl;
static SKC_set_act04_data betl04_shot_set_tbl;
static SKC_set_act04_data betl04_yakyo_set_tbl;
static signed char betl04_pg00[5];
static signed char betl04_pg01[5];
static signed char betl04_pg02[9];
static signed char betl04_pg03[4];
static signed char betl04_pg04[8];
static SKC_sprite_pattern betl04_pt00;
static SKC_sprite_pattern betl04_pt01;
static SKC_sprite_pattern betl04_pt02;
static SKC_sprite_pattern betl04_pt03;
static SKC_sprite_pattern betl04_pt04;
static SKC_sprite_pattern betl04_pt05;
static SKC_sprite_pattern betl04_pt06;
static SKC_sprite_pattern betl04_pt07;
static SKC_sprite_pattern betl04_pt08;
static SKC_sprite_pattern betl04_pt09;
static SKC_sprite_pattern betl04_pt10;

extern sonic3_ram g_ram;


void betl04(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &betl04plus6);
}


static void betl04plus6(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[8] = {
    &betl04_init,
    &betl04_move0,
    &betl04_wait0,
    &betl04_wait1,
    &betl04_shot0,
    &betl04_up0,
    &betl04_up1,
    &betl04_down0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void betl04_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &betl04_init_tbl);
  if (p_actwk->actflg.vflip == 0) {
    p_actwk->u.obj.actfree.betl04.upside_down = true;
  }
  p_actwk->actflg.vflip = 0;
  p_actwk->sprvsize = 14;
  p_actwk->u.obj.timer = p_actwk->u.obj.userflag * 2;
  p_actwk->u.obj.actfree.betl04.timer_init = p_actwk->u.obj.userflag * 4;
  p_actwk->u.obj.callback_ptr = &betl04_wait0_init;
  set_init_spd(p_actwk, -0x80);
}


static void betl04_move0(SKC_sprite_status* p_actwk) {
  if (chk_magnet(p_actwk)) return;

  SKC_chk_distance_result result = chk_distance(p_actwk);
  if (!result.below && (unsigned short)result.xdistance < 128) {
    if (p_actwk->actflg.hflip == 1) {
      result.right = !result.right;
    }
    if (result.right) {
      p_actwk->r_no = 6;
      p_actwk->patno = 0;
      p_actwk->u.obj.actfree.betl04.wait_shot_timer = 16;
      return;
    }
  }
  time_pg0(p_actwk, betl04_pg00);
  speedset2(p_actwk);
  emy_down_col(p_actwk);
  dec_timer(p_actwk);
}


static void betl04_wait0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.timer = 32;
  p_actwk->u.obj.callback_ptr = &betl04_move0_init;
}


static void betl04_wait0(SKC_sprite_status* p_actwk) {
  if (chk_magnet(p_actwk)) return;

  dec_timer(p_actwk);
}


static void betl04_move0_init(SKC_sprite_status* p_actwk) {
  p_actwk->xspeed = -p_actwk->xspeed;
  p_actwk->actflg.hflip ^= 1;
  p_actwk->u.obj.timer = p_actwk->u.obj.actfree.betl04.timer_init;
  betl04_move0_init0(p_actwk);
}


static void betl04_move0_init0(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->u.obj.callback_ptr = &betl04_wait0_init;
}


static void betl04_wait1(SKC_sprite_status* p_actwk) {
  if (chk_magnet(p_actwk)) return;
  if (p_actwk->u.obj.actfree.betl04.wait_shot_timer-- > 0) return;

  p_actwk->r_no = 8;
  p_actwk->u.obj.callback_ptr = &betl04_move0_init0;
  set_act00(p_actwk, &betl04_mazuru_set_tbl);
  set_act04(p_actwk, &betl04_shot_set_tbl);
}


static void betl04_shot0(SKC_sprite_status* p_actwk) {
  if (chk_magnet(p_actwk)) return;

  int ret = time_pg0(p_actwk, betl04_pg02);
  if (ret != 0 && p_actwk->patcnt == 6) {
    set_act04(p_actwk, &betl04_yakyo_set_tbl);
  }
}


static void betl04_up0(SKC_sprite_status* p_actwk) {
  p_actwk->yspeed += -0x20;
  speedset2(p_actwk);
  SKC_dircol_result result = emycol_u(p_actwk);
  if (result.offset < 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    p_actwk->r_no = 12;
    p_actwk->yspeed = 0;
  }
}


static void betl04_up1(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fff7c1 == 0) {
    p_actwk->r_no = 14;
  }
}


static void betl04_down0(SKC_sprite_status* p_actwk) {
  p_actwk->yspeed += 0x20;
  speedset2(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset < 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    p_actwk->r_no = p_actwk->u.obj.actfree.betl04.r_no_save;
    p_actwk->xspeed = p_actwk->u.obj.actfree.betl04.xspeed_save;
    p_actwk->yspeed = 0;
  }
}


static void betl04_mazuru(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &betl04_mazuru_init_tbl);
  p_actwk->r_ptr = &betl04_mazuru_pchg0;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
}


static void betl04_mazuru_pchg0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  pt_chg0(p_actwk, betl04_pg01);
  actionsub(p_actwk);
}


void betl04_box(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[2] = {
    &betl04_init0,
    &betl04_jump0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void betl04_init0(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &betl04_init_tbl);
  p_actwk->u.obj.callback_ptr = &betl04_move0_init1;
  p_actwk->sprvsize = 14;
  set_break_spd(p_actwk, 8);
  chk_emy_revs(p_actwk);
}


static void betl04_jump0(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  if (p_actwk->yspeed >= 0) {
    emy_fall_col(p_actwk);
  }
}


static void betl04_move0_init1(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &betl04plus6;
  p_actwk->r_no = 2;
  p_actwk->u.obj.timer = 63;
  p_actwk->u.obj.actfree.betl04.timer_init = 127;
  p_actwk->u.obj.callback_ptr = &betl04_wait0_init;
  p_actwk->xspeed = p_actwk->actflg.hflip == 1 ? -0x80 : 0x80;
  p_actwk->yspeed = 0;
}


static bool chk_magnet(SKC_sprite_status* p_actwk) {
  if (!p_actwk->u.obj.actfree.betl04.upside_down) return false;
  if (g_ram.DAT_08fff7c1 == 0) return false;

  p_actwk->u.obj.actfree.betl04.r_no_save = p_actwk->r_no;
  p_actwk->r_no = 10;
  p_actwk->u.obj.actfree.betl04.xspeed_save = p_actwk->xspeed;
  p_actwk->xspeed = 0;
  return true;
}


static SKC_enemy_init0_data betl04_init_tbl = {
  betl04_pt,
  { 0x506, 0, 0, 1, 1 },
  PRI_5,
  24,
  16,
  0,
  0x0A
};


static SKC_enemy_init2_data betl04_mazuru_init_tbl = {
  PRI_4,
  8,
  8,
  4,
  0
};


static SKC_enemy_init0_data betl04_shot_init_tbl = {
  betl04_pt,
  { 0x506, 0, 0, 1, 1 },
  PRI_5,
  4,
  4,
  5,
  0x98
};


static SKC_enemy_init0_data betl04_yakyo_init_tbl = {
  betl04_pt,
  { 0x506, 0, 0, 1, 1 },
  PRI_4,
  4,
  4,
  7,
  0
};


static SKC_set_act00_data betl04_mazuru_set_tbl = {
  0,
  {
    { &betl04_mazuru, -27, -22 }
  }
};


static SKC_set_act04_data betl04_shot_set_tbl = {
  0,
  {
    { &emyshot, &betl04_shot_init_tbl, betl04_pg03, &spd_pt_chg, -32, -32, -0x200, -0x400 }
  }
};


static SKC_set_act04_data betl04_yakyo_set_tbl = {
  0,
  {
    { &emyshot, &betl04_yakyo_init_tbl, betl04_pg04, &spd_pt_chg, -12, -4, 0x100, -0x200 }
  }
};


static signed char betl04_pg00[5] = { 0, 23, 1, 2, -4 };
static signed char betl04_pg01[5] = { 0, 4, 4, 5, -12 };
static signed char betl04_pg02[9] = { 0, 1, 0, 1, 2, 5, 0, 31, -12 };
static signed char betl04_pg03[4] = { 1, 5, 6, -4 };
static signed char betl04_pg04[8] = { 2, 7, 8, 9, 10, -4, -121, -37 };


SKC_sprite_pattern* betl04_pt[11] = {
  &betl04_pt00,
  &betl04_pt01,
  &betl04_pt02,
  &betl04_pt03,
  &betl04_pt04,
  &betl04_pt05,
  &betl04_pt06,
  &betl04_pt07,
  &betl04_pt08,
  &betl04_pt09,
  &betl04_pt10
};


static SKC_sprite_pattern betl04_pt00 = {
  4,
  {
    {   4,  0, 0x0000, -20 },
    { -12, 14, 0x0001, -12 },
    {   7, 12, 0x000D, -16 },
    { -20,  6, 0x0011, -28 }
  }
};
static SKC_sprite_pattern betl04_pt01 = {
  4,
  {
    {   3,  0, 0x0000, -20 },
    { -13, 14, 0x0001, -12 },
    {   7, 12, 0x000D, -16 },
    { -21,  6, 0x0011, -28 }
  }
};
static SKC_sprite_pattern betl04_pt02 = {
  4,
  {
    {   4,  0, 0x0000, -20 },
    { -12, 14, 0x0001, -12 },
    {   7, 12, 0x000D, -16 },
    { -20,  6, 0x0017, -28 }
  }
};
static SKC_sprite_pattern betl04_pt03 = {
  1,
  {
    { -8, 5, 0x001D, -8 }
  }
};
static SKC_sprite_pattern betl04_pt04 = {
  1,
  {
    { -8, 5, 0x0021, -8 }
  }
};
static SKC_sprite_pattern betl04_pt05 = {
  1,
  {
    { -4, 0, 0x0025, -4 }
  }
};
static SKC_sprite_pattern betl04_pt06 = {
  1,
  {
    { -4, 0, 0x0026, -4 }
  }
};
static SKC_sprite_pattern betl04_pt07 = {
  1,
  {
    { -4, 0, 0x0027, -4 }
  }
};
static SKC_sprite_pattern betl04_pt08 = {
  1,
  {
    { -4, 0, 0x0827, -4 }
  }
};
static SKC_sprite_pattern betl04_pt09 = {
  1,
  {
    { -4, 0, 0x1827, -4 }
  }
};
static SKC_sprite_pattern betl04_pt10 = {
  1,
  {
    { -4, 0, 0x1027, -4 }
  }
};
