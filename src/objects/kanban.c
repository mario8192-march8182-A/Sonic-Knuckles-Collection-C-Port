#include "kanban.h"
#include <stdbool.h>
#include "../data/cg/kanban.h"
#include "../types/enemyinitdata.h"
#include "../types/setactdata.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../types/wrtdata.h"
#include "../types/wrtinitdata.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../constants.h"
#include "../dev.h"
#include "../dircol.h"
#include "../etc.h"
#include "../score.h"
#include "../shared.h"
#include "../sound.h"
#include "friend.h"
#include "opnbox.h"
#include "ring.h"
#include "zone.h"
static void kanban_init(SKC_sprite_status* p_actwk);
static void kanban_move0(SKC_sprite_status* p_actwk);
static void kanban_move1(SKC_sprite_status* p_actwk);
static void kanban_move2(SKC_sprite_status* p_actwk);
static void kanban_move3(SKC_sprite_status* p_actwk);
static void kanban_move4(SKC_sprite_status* p_actwk);
static void kanban_move5(SKC_sprite_status* p_actwk);
static void kanbst_init(SKC_sprite_status* p_actwk);
static void kanbst_move(SKC_sprite_status* p_actwk);
static void chk_pl_coli(SKC_sprite_status* p_actwk);
static void chk_pl_coli_sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void chk_scr_lim(SKC_sprite_status* p_actwk);
static SKC_wrt_init_data kanban_init_tbl0;
static SKC_enemy_init0_data kanban_init_tbl1;
static SKC_enemy_init0_data kanban_init_tbl2;
static SKC_set_act00_data kanbst_set_tbl;
static SKC_set_act05_data kanban_set_tbl;
static SKC_set_act05_data ten_set_tbl;
static SKC_wrt_data kanban_wrt_tbl;
static signed char kanban_pg0[14];
static signed char kanban_pg1[14];
static signed char kanban_pg2[6];
static unsigned short* kanban_tbl[7];
static unsigned short kanban_tbl00[3];
static unsigned short kanban_tbl01[3];
static unsigned short kanban_tbl02[3];
static unsigned short kanban_tbl03[3];
static unsigned short kanban_tbl04[2];
static unsigned short kanban_tbl05[2];
static unsigned short kanban_tbl06[2];
static SKC_sprite_pattern* kanbanpat0[7];
static SKC_sprite_pattern kanbansp00;
static SKC_sprite_pattern kanbansp01;
static SKC_sprite_pattern kanbansp02;
static SKC_sprite_pattern kanbansp03;
static SKC_sprite_pattern kanbansp04;
static SKC_sprite_pattern kanbansp05;
static SKC_sprite_pattern kanbansp06;
static SKC_sprite_pattern* kanbanpat1[1];
static SKC_sprite_pattern kanbansp07;

extern sonic3_ram g_ram;


void kanban(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &kanban_init,
    &kanban_move0,
    &kanban_move1,
    &kanban_move2,
    &kanban_move3
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &kanban_wrt_tbl);
  actionsub(p_actwk);
}


static void kanban_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &kanban_init_tbl0);
  if (BIT_IS_SET(g_ram.actwk[0].sproffset, 15)) {
    SET_BIT(p_actwk->sproffset, 15);
  }
  g_ram.save_obj = p_actwk - g_ram.actwk;
  p_actwk->sprhsize = 24;
  p_actwk->sprvsize = 30;
  p_actwk->u.obj.pg_data_ptr = g_ram.play_type != PLAY_TYPE_KNUCKLES ? kanban_pg0 : kanban_pg1;
  short yposi = (g_ram.scra_v_posit >> 16) - 32;
  fp16_set_integer(&p_actwk->yposi, yposi);
  soundset(-72);
  set_act00(p_actwk, &kanbst_set_tbl);
}


static void kanban_move0(SKC_sprite_status* p_actwk) {
  unsigned short pri_tbl[2] = {
    PRI_3, PRI_6
  };

  if (!(g_ram.systemtimer & 3)) {
    set_act05(p_actwk, &kanban_set_tbl);
  }
  chk_pl_coli(p_actwk);
  p_actwk->yspeed += 0xC;
  speedset2(p_actwk);
  chk_scr_lim(p_actwk);
  pt_chg(p_actwk);
  short yposi = (g_ram.scra_v_posit >> 16) + 80;
  if ((unsigned short)yposi <= fp16_get_integer(p_actwk->yposi) && p_actwk->yspeed >= 0) {
    bool skip_coli_chk = false;
    if (get_zone(g_ram.stageno) == SANDOPOLIS) {
      unsigned short index = (unsigned short)fp16_get_integer(p_actwk->xposi) < 0x4210 ? 0 : 1;
      if (index != p_actwk->u.obj.actfree.kanban.tbl_index) {
        p_actwk->u.obj.actfree.kanban.tbl_index = index;
        p_actwk->sprpri = pri_tbl[index];
      }
      if ((unsigned short)fp16_get_integer(p_actwk->yposi) >= 0x9f2) {
        skip_coli_chk = true;
      }
    }
    if (!skip_coli_chk) {
      SKC_dircol_result result = emycol_d(p_actwk);
      if (result.offset >= 0) return;
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    }
    p_actwk->r_no = 4;
    p_actwk->u.obj.actflg0.puka_down = 1;
    p_actwk->u.obj.timer = 64;
  }
}


static void kanban_move1(SKC_sprite_status* p_actwk) {
  unsigned char patno_tbl[4] = {
    0, 0, 1, 2
  };

  if (p_actwk->u.obj.actflg0.puka_down == 1) {
    pt_chg(p_actwk);
    if (p_actwk->u.obj.timer-- == 0) {
      p_actwk->r_no = 6;
      g_ram.DAT_08fffabe = 0xFF;
      p_actwk->xspeed = 0;
      p_actwk->yspeed = 0;
      p_actwk->patno = patno_tbl[g_ram.play_type];
      g_ram.pl2_input_lock_flag = 0xFF;
    }
  }
  else {
    p_actwk->r_no = 2;
    p_actwk->mstno = 32;
    p_actwk->yspeed = -0x200;
  }
}


static void kanban_move2(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.cddat.jump == 1) return;

  p_actwk->r_no = 8;
  set_pl_pause(p_actwk, &g_ram.actwk[0]);
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &clear;
  }
}


static void kanban_move3(SKC_sprite_status* p_actwk) {
  bool skip_yspeed_zero = false;
  if (get_zone(g_ram.stageno) == DEATH_EGG) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset > 0) {
      speedset(p_actwk);
      skip_yspeed_zero = true;
    }
    else {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    }
  }
  if (!skip_yspeed_zero) {
    p_actwk->yspeed = 0;
  }
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if (chunk_xposi <= 640) {
    short yposi = fp16_get_integer(p_actwk->yposi) - (g_ram.scra_v_posit >> 16) + 128;
    if (yposi <= 512) {
      chk_pl2_pause(p_actwk);
      return;
    }
  }
  divdevset2(&toge_cg_tbl);
  clr_wchg_bit(p_actwk);
  set_emy_fout0(p_actwk);
}


SKC_cg_data toge_cg_tbl = {
  0,
  {
    { toge_cg, 0x9280 }
  }
};


static void kanban_move4(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &kanban_init_tbl2);
  if (BIT_IS_SET(g_ram.actwk[0].sproffset, 15)) {
    SET_BIT(p_actwk->sproffset, 15);
  }
  p_actwk->r_ptr = &kanban_move5;
  short yoffset = (short)(random() & 0x1F) - 16;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->u.obj.actfree.kanban.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->xspeed = 0x1000;
  p_actwk->u.obj.timer = 32;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  kanban_move5(p_actwk);
}


static void kanban_move5(SKC_sprite_status* p_actwk) {
  p_actwk->xspeed += fp16_get_integer(p_actwk->xposi) < p_actwk->u.obj.actfree.kanban.xposi_init ? 0x400 : -0x400;
  p_actwk->sprpri = p_actwk->xspeed >= 0 ? PRI_5 : PRI_7;
  speedset2(p_actwk);
  pt_chg0(p_actwk, kanban_pg2);
  dec_timer(p_actwk);
  actionsub(p_actwk);
}


static void kanbst_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &kanban_init_tbl1);
  p_actwk->r_ptr = &kanbst_move;
  if (BIT_IS_SET(g_ram.actwk[0].sproffset, 15)) {
    SET_BIT(p_actwk->sproffset, 15);
  }
}


static void kanbst_move(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  chk_oya_pri(p_actwk);
  chk_oya_die0(p_actwk);
}


static void chk_pl_coli(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = {
    -32, 64, -24, 48
  };

  if (p_actwk->mstno == 0) {
    SKC_chk_emy_colt_result result = chk_emy_colt(p_actwk, col_tbl);
    if (result.pl) {
      chk_pl_coli_sub(p_actwk, &g_ram.actwk[0]);
    }
    if (result.pl2) {
      chk_pl_coli_sub(p_actwk, &g_ram.actwk[1]);
    }
  }
  else {
    --p_actwk->mstno;
  }
}


static void chk_pl_coli_sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->mstno != 2) return;
  if (p_playerwk->yspeed < 0) return;

  p_actwk->mstno = 32;
  short distance = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_playerwk->xposi);
  if (distance == 0) {
    distance = 8;
  }
  p_actwk->xspeed = distance * 16;
  p_actwk->yspeed = -0x200;
  soundset(-72);
  set_act05(p_actwk, &ten_set_tbl);
  scoreup(10);
}


static void chk_scr_lim(SKC_sprite_status* p_actwk) {
  short scra_h = g_ram.scra_h_posit >> 16;
  if (p_actwk->xspeed >= 0) {
    scra_h += 296;
    if ((unsigned short)scra_h < (unsigned short)fp16_get_integer(p_actwk->xposi)) {
      p_actwk->xspeed = -p_actwk->xspeed;
    }
    else {
      SKC_dircol_result result = emycol_r(p_actwk, 32);
      if (result.offset < 0) {
        p_actwk->xspeed = -p_actwk->xspeed;
      }
    }
  }
  else {
    scra_h += 24;
    if ((unsigned short)scra_h > (unsigned short)fp16_get_integer(p_actwk->xposi)) {
      p_actwk->xspeed = -p_actwk->xspeed;
    }
    else {
      SKC_dircol_result result = emycol_l(p_actwk, -32);
      if (result.offset < 0) {
        p_actwk->xspeed = -p_actwk->xspeed;
      }
    }
  }
}


static SKC_wrt_init_data kanban_init_tbl0 = {
  0,
  0x04AC,
  12,
  0,
  kanbanpat0,
  PRI_6,
  24,
  16,
  0,
  0
};


static SKC_enemy_init0_data kanban_init_tbl1 = {
  kanbanpat1,
  0x069E,
  PRI_6,
  4,
  8,
  0,
  0
};


static SKC_enemy_init0_data kanban_init_tbl2 = {
  ringpat,
  0x26BC,
  PRI_5,
  8,
  8,
  4,
  0
};


static SKC_set_act00_data kanbst_set_tbl = {
  0,
  {
    { &kanbst_init, 0, 24 }
  }
};


static SKC_set_act05_data kanban_set_tbl = {
  0,
  &kanban_move4
};


static SKC_set_act05_data ten_set_tbl = {
  0,
  &ten
};


static SKC_wrt_data kanban_wrt_tbl = {
  kanban_cg,
  kanban_tbl
};


static signed char kanban_pg0[14] = { 1, 0, 4, 5, 6, 1, 4, 5, 6, 3, 4, 5, 6, -4 };
static signed char kanban_pg1[14] = { 1, 1, 4, 5, 6, 2, 4, 5, 6, 3, 4, 5, 6, -4 };
static signed char kanban_pg2[6] = { 1, 4, 5, 6, 7, -4 };


static unsigned short* kanban_tbl[7] = {
  kanban_tbl00,
  kanban_tbl01,
  kanban_tbl02,
  kanban_tbl03,
  kanban_tbl04,
  kanban_tbl05,
  kanban_tbl06
};


static unsigned short kanban_tbl00[3] = { 1, 0x20B, 0x2CB };
static unsigned short kanban_tbl01[3] = { 1, 0x38B, 0x44B };
static unsigned short kanban_tbl02[3] = { 1, 0x50B, 0x5CB };
static unsigned short kanban_tbl03[3] = { 1, 0x00B, 0x00B };
static unsigned short kanban_tbl04[2] = { 0, 0x0CF };
static unsigned short kanban_tbl05[2] = { 0, 0x1C3 };
static unsigned short kanban_tbl06[2] = { 0, 0x0CF };


static SKC_sprite_pattern* kanbanpat0[7] = {
  &kanbansp00,
  &kanbansp01,
  &kanbansp02,
  &kanbansp03,
  &kanbansp04,
  &kanbansp05,
  &kanbansp06
};


static SKC_sprite_pattern kanbansp00 = {
  2,
  {
    { -16, 11, 0x0000, -24 },
    { -16, 11, 0x000C,   0 }
  }
};
static SKC_sprite_pattern kanbansp01 = {
  2,
  {
    { -16, 11, 0x0000, -24 },
    { -16, 11, 0x000C,   0 }
  }
};
static SKC_sprite_pattern kanbansp02 = {
  2,
  {
    { -16, 11, 0x0000, -24 },
    { -16, 11, 0x000C,   0 }
  }
};
static SKC_sprite_pattern kanbansp03 = {
  2,
  {
    { -16, 11, 0x0000, -24 },
    { -16, 11, 0x080C,   0 }
  }
};
static SKC_sprite_pattern kanbansp04 = {
  1,
  {
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern kanbansp05 = {
  1,
  {
    { -16, 3, 0x0000, -4 }
  }
};
static SKC_sprite_pattern kanbansp06 = {
  1,
  {
    { -16, 15, 0x0800, -16 }
  }
};


static SKC_sprite_pattern* kanbanpat1[1] = {
  &kanbansp07
};


static SKC_sprite_pattern kanbansp07 = {
  1,
  {
    { -8, 1, 0x0000, -4 }
  }
};
