#include "mous04.h"
#include "../../types/enemyinit0data.h"
#include "../../types/setact00data.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../action.h"
#include "../../constants.h"
#include "../../shared.h"
static void mous04_from_box(SKC_sprite_status* p_actwk);
static void mous04_init(SKC_sprite_status* p_actwk);
static void mous04_fura_init(SKC_sprite_status* p_actwk);
static void mous04_ud_init(SKC_sprite_status* p_actwk);
static void mous04_puka_init(SKC_sprite_status* p_actwk);
static void mous04_move0(SKC_sprite_status* p_actwk);
static void mous04_wait0_init(SKC_sprite_status* p_actwk);
static void clr_pt(SKC_sprite_status* p_actwk);
static void clr_end_bit(SKC_sprite_status* p_actwk);
static void mous04_wait0(SKC_sprite_status* p_actwk);
static void mous04_move0_init(SKC_sprite_status* p_actwk);
static void mous04_move0_init0(SKC_sprite_status* p_actwk);
static void mous04_moveu(SKC_sprite_status* p_actwk);
static void mous04_waitu_init(SKC_sprite_status* p_actwk);
static void mous04_waitu(SKC_sprite_status* p_actwk);
static void mous04_moveu_init(SKC_sprite_status* p_actwk);
static void mous04_tail(SKC_sprite_status* p_actwk);
static void mous04_tail_init(SKC_sprite_status* p_actwk);
static void mous04_tail_wait0(SKC_sprite_status* p_actwk);
static void mous04_tail_waitu(SKC_sprite_status* p_actwk);
static void mous04_init0(SKC_sprite_status* p_actwk);
static void mous04_jump0(SKC_sprite_status* p_actwk);
static void mous04_move0_init1(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data mous04_init_tbl;
static SKC_enemy_init0_data mous04_init_tblu;
static SKC_enemy_init2_data mous04_tail_init_tbl;
static SKC_set_act00_data mous04_tail_set_tbl;
static signed char mous04_pg00[11];
static signed char mous04_pg01[11];
static signed char mous04_pg02[11];
static signed char mous04_pg03[5];
static signed char mous04_pg04[11];
static signed char mous04_pg05[11];
static signed char mous04_pg06[11];
static signed char mous04_pg07[8];
static SKC_sprite_pattern mous04_pt00;
static SKC_sprite_pattern mous04_pt01;
static SKC_sprite_pattern mous04_pt02;
static SKC_sprite_pattern mous04_pt03;
static SKC_sprite_pattern mous04_pt04;
static SKC_sprite_pattern mous04_pt05;
static SKC_sprite_pattern mous04_pt06;
static SKC_sprite_pattern mous04_pt07;
static SKC_sprite_pattern mous04_pt08;
static SKC_sprite_pattern mous04_pt09;
extern sonic3_ram g_ram;


void mous04(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &mous04_from_box);
}


static void mous04_from_box(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &mous04_init,
    &mous04_move0,
    &mous04_wait0,
    &mous04_moveu,
    &mous04_waitu
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void mous04_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 2048;
  p_actwk->u.obj.callback_ptr = &clr_end_bit;
  if (p_actwk->u.obj.userflag == 4) {
    mous04_ud_init(p_actwk);
  }
  else {
    enemy_init0(p_actwk, &mous04_init_tbl);
    p_actwk->u.obj.pg_data_ptr = mous04_pg00;
    p_actwk->actflg.hflip = 1;
    if (p_actwk->u.obj.userflag == 2) {
      p_actwk->actflg.vflip = 1;
    }
    set_act00(p_actwk, &mous04_tail_set_tbl);
  }
}


static void mous04_fura_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.fura.accel_max = 0x400;
  p_actwk->xspeed = 0x400;
  p_actwk->u.obj.fura.accel = 0x20;
  p_actwk->u.obj.actflg0.fura_right = 0;
}


static void mous04_ud_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &mous04_init_tblu);
  p_actwk->r_no = 6;
  p_actwk->u.obj.pg_data_ptr = mous04_pg04;
  p_actwk->actflg.vflip = 1;
  set_act00(p_actwk, &mous04_tail_set_tbl);
  mous04_puka_init(p_actwk);
}


static void mous04_puka_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.accel_max = 0x400;
  p_actwk->yspeed = 0x400;
  p_actwk->u.obj.puka.accel = 0x20;
  p_actwk->u.obj.actflg0.puka_down = 0;
}


static void mous04_move0(SKC_sprite_status* p_actwk) {
  int ret = time_pgr(p_actwk);
  if (ret != 0 && p_actwk->patcnt == 6) {
    p_actwk->u.obj.actflg0.unused1 = 1;
  }
  fura_fura(p_actwk);
  if (p_actwk->xspeed == 0) {
    mous04_wait0_init(p_actwk);
  }
  else {
    speedset2(p_actwk);
    dec_timer(p_actwk);
  }
}


static void mous04_wait0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.pg_data_ptr = mous04_pg02;
  p_actwk->u.obj.callback_ptr = &mous04_move0_init;
  clr_pt(p_actwk);
}


static void clr_pt(SKC_sprite_status* p_actwk) {
  p_actwk->patcnt = 0;
  p_actwk->pattim = 0;
}


static void clr_end_bit(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.end = 0;
}


static void mous04_wait0(SKC_sprite_status* p_actwk) {
  pt_chgr(p_actwk);
}


static void mous04_move0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->u.obj.pg_data_ptr = mous04_pg01;
  mous04_move0_init0(p_actwk);
}


static void mous04_move0_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.unused1 = 0;
  p_actwk->u.obj.actflg0.end = 1;
  p_actwk->u.obj.timer = 16;
  p_actwk->u.obj.callback_ptr = &clr_end_bit;
  clr_pt(p_actwk);
}


static void mous04_moveu(SKC_sprite_status* p_actwk) {
  int ret = time_pgvr(p_actwk);
  if (ret != 0 && p_actwk->patcnt == 6) {
    p_actwk->u.obj.actflg0.unused1 = 1;
  }
  puka_puka(p_actwk);
  if (p_actwk->yspeed == 0) {
    mous04_waitu_init(p_actwk);
  }
  else {
    speedset2(p_actwk);
    dec_timer(p_actwk);
  }
}


static void mous04_waitu_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->u.obj.pg_data_ptr = mous04_pg06;
  p_actwk->u.obj.callback_ptr = &mous04_moveu_init;
  clr_pt(p_actwk);
}


static void mous04_waitu(SKC_sprite_status* p_actwk) {
  pt_chgvr(p_actwk);
}


static void mous04_moveu_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->u.obj.pg_data_ptr = mous04_pg05;
  mous04_move0_init0(p_actwk);
}


static void mous04_tail(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &mous04_tail_init,
    &mous04_tail_wait0,
    &mous04_tail_waitu
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die0(p_actwk);
}


static void mous04_tail_init(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &mous04_tail_init_tbl);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.userflag == 4) {
    p_actwk->r_no = 4;
  }
}


static void mous04_tail_wait0(SKC_sprite_status* p_actwk) {
  struct {
    signed char x;
    signed char y;
  }
  ofs_tbl[3] = {
    { 20, 4 },
    { 12, 4 },
    {  0, 4 }
  };

  pt_chg0(p_actwk, mous04_pg03);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  unsigned char ofs_id = p_parentwk->u.obj.actflg0.unused1 == 0 ? p_parentwk->patno : 2;
  p_actwk->u.obj.oya_offset.x = ofs_tbl[ofs_id].x;
  p_actwk->u.obj.oya_offset.y = ofs_tbl[ofs_id].y;
  if (p_parentwk->u.obj.actflg0.end == 0) {
    ko_offset1(p_actwk);
  }
}


static void mous04_tail_waitu(SKC_sprite_status* p_actwk) {
  struct {
    signed char x;
    signed char y;
  }
  ofs_tbl[3] = {
    { -4, 20 },
    { -4, 12 },
    { -4,  0 }
  };

  pt_chg0(p_actwk, mous04_pg07);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  unsigned char ofs_id = p_parentwk->u.obj.actflg0.unused1 == 0 ? p_parentwk->patno - 5 : 2;
  p_actwk->u.obj.oya_offset.x = ofs_tbl[ofs_id].x;
  p_actwk->u.obj.oya_offset.y = ofs_tbl[ofs_id].y;
  if (p_parentwk->u.obj.actflg0.end == 0) {
    ko_offset1(p_actwk);
  }
}


void mous04_box(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[2] = {
    &mous04_init0,
    &mous04_jump0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void mous04_init0(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &mous04_init_tbl);
  p_actwk->sprvsize = 7;
  p_actwk->u.obj.callback_ptr = &mous04_move0_init1;
  set_break_spd(p_actwk, 144);
  chk_emy_revs(p_actwk);
  p_actwk->u.obj.userflag = 0;
  set_act00(p_actwk, &mous04_tail_set_tbl);
}


static void mous04_jump0(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  if (p_actwk->yspeed >= 0) {
    emy_fall_col(p_actwk);
  }
}


static void mous04_move0_init1(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &mous04_from_box;
  p_actwk->r_no = 2;
  p_actwk->u.obj.timer = 2048;
  p_actwk->u.obj.callback_ptr = &clr_end_bit;
  p_actwk->u.obj.pg_data_ptr = mous04_pg00;
  p_actwk->u.obj.fura.accel_max = 0x400;
  p_actwk->u.obj.actflg0.fura_right = !p_actwk->actflg.hflip;
  p_actwk->xspeed = p_actwk->actflg.hflip == 1 ? 0x400 : -0x400;
  p_actwk->u.obj.fura.accel = 0x20;
  p_actwk->yspeed = 0;
}


static SKC_enemy_init0_data mous04_init_tbl = {
  mous04_pt,
  0xA52E,
  PRI_5,
  12,
  8,
  0,
  0x0B
};


static SKC_enemy_init0_data mous04_init_tblu = {
  mous04_pt,
  0xA52E,
  PRI_5,
  8,
  12,
  5,
  0x0B
};


static SKC_enemy_init2_data mous04_tail_init_tbl = {
  PRI_5,
  8,
  4,
  2,
  0
};


static SKC_set_act00_data mous04_tail_set_tbl = {
  0,
  {
    { &mous04_tail, 20, 4 }
  }
};


static signed char mous04_pg00[11] = { 0, 0, 0, 23, 1, 1, 65, 1, 0, 31, -12 };
static signed char mous04_pg01[11] = { 0, 0, 0, 55, 1, 1, 65, 1, 0, 31, -12 };
static signed char mous04_pg02[11] = { 3, 0, 0, 1, 65, 0, 0, 1, 65, 0, -12 };
static signed char mous04_pg03[5] = { 3, 2, 3, 4, -4 };
static signed char mous04_pg04[11] = { 5, 0, 5, 23, 6, 1, 70, 1, 0, 31, -12 };
static signed char mous04_pg05[11] = { 5, 0, 5, 55, 6, 1, 70, 1, 5, 31, -12 };
static signed char mous04_pg06[11] = { 3, 5, 5, 6, 70, 5, 5, 6, 70, 5, -12 };
static signed char mous04_pg07[8] = { 3, 7, 8, 9, -4, -121, -37, -112 };


SKC_sprite_pattern* mous04_pt[10] = {
  &mous04_pt00,
  &mous04_pt01,
  &mous04_pt02,
  &mous04_pt03,
  &mous04_pt04,
  &mous04_pt05,
  &mous04_pt06,
  &mous04_pt07,
  &mous04_pt08,
  &mous04_pt09
};


static SKC_sprite_pattern mous04_pt00 = {
  1,
  {
    { -8, 9, 0x0000, -12 }
  }
};
static SKC_sprite_pattern mous04_pt01 = {
  1,
  {
    { -8, 9, 0x0006, -12 }
  }
};
static SKC_sprite_pattern mous04_pt02 = {
  1,
  {
    { -4, 4, 0x000C, -8 }
  }
};
static SKC_sprite_pattern mous04_pt03 = {
  1,
  {
    { -4, 4, 0x000E, -8 }
  }
};
static SKC_sprite_pattern mous04_pt04 = {
  1,
  {
    { -4, 4, 0x0010, -8 }
  }
};
static SKC_sprite_pattern mous04_pt05 = {
  1,
  {
    { -12, 6, 0x0012, -8 }
  }
};
static SKC_sprite_pattern mous04_pt06 = {
  1,
  {
    { -12, 6, 0x0018, -8 }
  }
};
static SKC_sprite_pattern mous04_pt07 = {
  1,
  {
    { -8, 1, 0x001E, -4 }
  }
};
static SKC_sprite_pattern mous04_pt08 = {
  1,
  {
    { -8, 1, 0x0020, -4 }
  }
};
static SKC_sprite_pattern mous04_pt09 = {
  1,
  {
    { -8, 1, 0x0022, -4 }
  }
};
