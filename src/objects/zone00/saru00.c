#include "saru00.h"
#include <stdbool.h>
#include "../../data/pat/zone00/saru00.h"
#include "../../types/enemyinitdata.h"
#include "../../types/setactdata.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../constants.h"
#include "../../etc.h"
#include "../../shared.h"
#include "../../sound.h"
#include "../emyshot.h"
static void saru00_framein(SKC_sprite_status* p_actwk);
static void saru00_init(SKC_sprite_status* p_actwk);
static void saru00_wait(SKC_sprite_status* p_actwk);
static void saru00_move_init(SKC_sprite_status* p_actwk);
static void saru00_move(SKC_sprite_status* p_actwk);
static void saru00_move__goto_wait(SKC_sprite_status* p_actwk);
static void saru00_arm0(SKC_sprite_status* p_actwk);
static void saru00_arm_base(SKC_sprite_status* p_actwk);
static void arm_base_up(SKC_sprite_status* p_actwk);
static void ura1_init0(SKC_sprite_status* p_actwk);
static void arm_base_ura(SKC_sprite_status* p_actwk);
static void arm_base_ura1(SKC_sprite_status* p_actwk);
static void chg_add(SKC_sprite_status* p_actwk);
static void saru00_shot_init(SKC_sprite_status* p_actwk);
static void arm_base_shot0(SKC_sprite_status* p_actwk);
static void arm_base_shot1(SKC_sprite_status* p_actwk);
static void arm_base_shot2(SKC_sprite_status* p_actwk);
static void saru00_arm_other(SKC_sprite_status* p_actwk);
static void arm_other_ura(SKC_sprite_status* p_actwk);
static void arm_other_ura1(SKC_sprite_status* p_actwk);
static void arm_other_shot(SKC_sprite_status* p_actwk);
static void arm_hand_ura(SKC_sprite_status* p_actwk);
static void arm_hand_ura1(SKC_sprite_status* p_actwk);
static void arm_hand_shot(SKC_sprite_status* p_actwk);
static void banana_move(SKC_sprite_status* p_actwk);
static void land_init(SKC_sprite_status* p_actwk);
static void banana_land(SKC_sprite_status* p_actwk);
static void saru00_chk_rev(SKC_sprite_status* p_actwk);
static void saru00_chk_ofs(SKC_sprite_status* p_actwk);
static void saru00_chk_pri(SKC_sprite_status* p_actwk);
static bool saru00_chk_shot(SKC_sprite_status* p_actwk);
static void saru00_add_dir(SKC_sprite_status* p_actwk, signed char offset);
static void other_move(SKC_sprite_status* p_actwk);
static void chk_arm_shot(SKC_sprite_status* p_actwk, unsigned char r_no);
static void chk_arm_ura(SKC_sprite_status* p_actwk, unsigned char r_no);
static void chk_hand_shot(SKC_sprite_status* p_actwk);
static void chk_hand_shot__set(SKC_sprite_status* p_actwk);
static void set_arm_timer(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data saru00_init_tbl;
static SKC_enemy_init2_data saru00_arm_init_tbl;
static SKC_enemy_init1_data banana_init_tbl;
static SKC_enemy_init0_data yasi_init_tbl;
static SKC_set_act03_data saru00_arm_set_tbl0;
static SKC_set_act03_data saru00_arm_set_tbl1;
static SKC_set_act00_data banana_set_tbl;
static SKC_set_act01_data yasi_set_tbl;
static signed char saru00_pg00[4];
static signed char saru00_pg01[5];
static signed char banana_pg00[10];
static signed char banana_pg01[5];

extern sonic3_ram g_ram;


void saru00(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &saru00_framein);
  saru00_framein(p_actwk);
}


static void saru00_framein(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &saru00_init,
    &saru00_wait,
    &saru00_move
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void saru00_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &saru00_init_tbl);
  p_actwk->u.obj.userflag >>= 2;
  p_actwk->u.obj.actfree.saru00.move_timer = p_actwk->u.obj.userflag >> 1 & 0xFF;
  p_actwk->u.obj.pg_data_ptr = saru00_pg00;
  p_actwk->u.obj.timer = 59;
  p_actwk->u.obj.callback_ptr = &saru00_move_init;
  if (p_actwk->actflg.hflip == 0) {
    set_act03(p_actwk, &saru00_arm_set_tbl0);
  }
  else {
    set_act03(p_actwk, &saru00_arm_set_tbl1);
  }
}


static void saru00_wait(SKC_sprite_status* p_actwk) {
  pt_tim(p_actwk);
}


static void saru00_move_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->patcnt = 0;
  p_actwk->pattim = 0;
  p_actwk->u.obj.pg_data_ptr = saru00_pg01;
}


static void saru00_move(SKC_sprite_status* p_actwk) {
  if (time_pg(p_actwk) == 0) return;

  if (p_actwk->u.obj.actflg0.unused2 == 0) {
    if (p_actwk->patno == 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->xposi) + 8);
      --p_actwk->u.obj.actfree.saru00.move_timer;
      if (p_actwk->u.obj.actfree.saru00.move_timer == 0) {
        saru00_move__goto_wait(p_actwk);
      }
    }
  }
  else {
    if (p_actwk->patno == 2) {
      --p_actwk->u.obj.actfree.saru00.move_timer;
      if (p_actwk->u.obj.actfree.saru00.move_timer == 0) {
        saru00_move__goto_wait(p_actwk);
      }
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->xposi) - 8);
    }
  }
}


static void saru00_move__goto_wait(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->u.obj.actfree.saru00.move_timer = p_actwk->u.obj.userflag;
  p_actwk->u.obj.actflg0.unused2 ^= 1;
  p_actwk->u.obj.timer = 59;
  p_actwk->u.obj.pg_data_ptr = saru00_pg00;
  p_actwk->patno = 0;
  p_actwk->patcnt = 0;
  p_actwk->pattim = 0;
}


static void saru00_arm0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.fura_right = 1;
  saru00_arm(p_actwk);
}


void saru00_arm(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &saru00_arm_init_tbl);
  p_actwk->r_no = 0;
  p_actwk->u.obj.actfree.saru00_arm.unknown3b = p_actwk->u.obj.userflag * 2 & 0xFF;
  p_actwk->u.obj.actfree.saru00_arm.unknown3a = p_actwk->u.obj.userflag * 2 & 0xFF;
  if (p_actwk->u.obj.userflag == 0) {
    p_actwk->r_ptr = &saru00_arm_base;
    signed char xoffset = 14;
    if (p_actwk->u.obj.actflg0.fura_right == 0) {
      xoffset = -xoffset;
    }
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 2);
  }
  else if (p_actwk->u.obj.userflag != 8) {
    p_actwk->r_ptr = &saru00_arm_other;
  }
  else {
    p_actwk->r_ptr = &saru00_hand;
    p_actwk->patno = 6;
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_actwk->u.obj.actfree.saru00_arm.elbow = p_parentwk - g_ram.actwk;
    p_parentwk = &g_ram.actwk[p_parentwk->u.obj.oya];
    p_parentwk = &g_ram.actwk[p_parentwk->u.obj.oya];
    p_actwk->u.obj.ko = p_parentwk - g_ram.actwk;
  }
  chk_oya_die0(p_actwk);
}


static void saru00_arm_base(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[6] = {
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


static void arm_base_up(SKC_sprite_status* p_actwk) {
  unsigned char angle = p_actwk->u.obj.actfree.saru00_arm.angle;
  if (p_actwk->u.obj.actflg0.fura_right == 1) { // right
    angle += 4;
    if (angle < 128) {
      p_actwk->u.obj.actfree.saru00_arm.angle = angle;
    }
    else {
      p_actwk->r_no = 2;
    }
  }
  else { // left
    angle -=4;
    if (angle > 128) {
      p_actwk->u.obj.actfree.saru00_arm.angle = angle;
    }
    else {
      p_actwk->r_no = 2;
    }
  }
}


static void ura1_init0(SKC_sprite_status* p_actwk) {
  set_arm_timer(p_actwk);
  p_actwk->u.obj.callback_ptr = &chg_add;
}


static void arm_base_ura(SKC_sprite_status* p_actwk) {
  if (saru00_chk_shot(p_actwk)) {
    saru00_shot_init(p_actwk);
  }
  else {
    arm_base_ura1(p_actwk);
  }
}


static void arm_base_ura1(SKC_sprite_status* p_actwk) {
  unsigned char angle;
  if (p_actwk->u.obj.actflg0.fura_right == 1) { // right
    saru00_add_dir(p_actwk, p_actwk->u.obj.actfree.saru00_arm.dir);
    angle = p_actwk->u.obj.actfree.saru00_arm.angle - 32;
  }
  else { // left
    saru00_add_dir(p_actwk, p_actwk->u.obj.actfree.saru00_arm.dir);
    angle = p_actwk->u.obj.actfree.saru00_arm.angle - 128;
  }
  if (angle >= 96) {
    p_actwk->u.obj.actfree.saru00_arm.dir = -p_actwk->u.obj.actfree.saru00_arm.dir;
    saru00_add_dir(p_actwk, p_actwk->u.obj.actfree.saru00_arm.dir);
  }
  dec_timer(p_actwk);
}


static void chg_add(SKC_sprite_status* p_actwk) {
  set_arm_timer(p_actwk);
}


static void saru00_shot_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.actflg0.unused1 = 1;
}


static void arm_base_shot0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 1) { // right
    saru00_add_dir(p_actwk, 4);
    if (p_actwk->u.obj.actfree.saru00_arm.angle >= 192) {
      p_actwk->r_no = 6;
      p_actwk->u.obj.actflg0.unused2 = 1;
    }
  }
  else { // left
    saru00_add_dir(p_actwk, -4);
    if (p_actwk->u.obj.actfree.saru00_arm.angle <= 64) {
      p_actwk->r_no = 6;
      p_actwk->u.obj.actflg0.unused2 = 1;
    }
  }
}


static void arm_base_shot1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 1) { // right
    saru00_add_dir(p_actwk, -8);
    if (p_actwk->u.obj.actfree.saru00_arm.angle <= 96) {
      p_actwk->r_no = 8;
      p_actwk->u.obj.actfree.saru00_arm.angle = 96;
      p_actwk->u.obj.actflg0.unused1 = 0;
    }
  }
  else { // left
    saru00_add_dir(p_actwk, 8);
    if (p_actwk->u.obj.actfree.saru00_arm.angle >= 160) {
      p_actwk->r_no = 8;
      p_actwk->u.obj.actfree.saru00_arm.angle = 160;
      p_actwk->u.obj.actflg0.unused1 = 0;
    }
  }
}


static void arm_base_shot2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 0) { // right
    saru00_add_dir(p_actwk, -2);
    if (p_actwk->u.obj.actfree.saru00_arm.angle <= 128) {
      p_actwk->r_no = 10;
      p_actwk->u.obj.actfree.saru00_arm.angle = 128;
      ura1_init0(p_actwk);
    }
  }
  else { // left
    saru00_add_dir(p_actwk, 2);
    if (p_actwk->u.obj.actfree.saru00_arm.angle >= 128) {
      p_actwk->r_no = 10;
      p_actwk->u.obj.actfree.saru00_arm.angle = 128;
      ura1_init0(p_actwk);
    }
  }
}


static void saru00_arm_other(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &arm_other_ura,
    &arm_other_shot,
    &arm_other_ura1
  };

  saru00_chk_pri(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die0(p_actwk);
}


static void arm_other_ura(SKC_sprite_status* p_actwk) {
  chk_arm_shot(p_actwk, 2);
  arm_other_ura1(p_actwk);
}


static void arm_other_ura1(SKC_sprite_status* p_actwk) {
  other_move(p_actwk);
}


static void arm_other_shot(SKC_sprite_status* p_actwk) {
  chk_arm_ura(p_actwk, 4);
  other_move(p_actwk);
}


void saru00_hand(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &arm_hand_ura,
    &arm_hand_shot,
    &arm_hand_ura1
  };

  saru00_chk_pri(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die0(p_actwk);
}


static void arm_hand_ura(SKC_sprite_status* p_actwk) {
  chk_arm_shot(p_actwk, 2);
  arm_hand_ura1(p_actwk);
}


static void arm_hand_ura1(SKC_sprite_status* p_actwk) {
  other_move(p_actwk);
}


static void arm_hand_shot(SKC_sprite_status* p_actwk) {
  chk_hand_shot(p_actwk);
  chk_arm_ura(p_actwk, 4);
  other_move(p_actwk);
}


void saru00_banana(SKC_sprite_status* p_actwk) {
  enemy_init1(p_actwk, &banana_init_tbl);
  p_actwk->r_ptr = &banana_move;
  p_actwk->u.obj.pg_data_ptr = banana_pg00;
  p_actwk->u.obj.callback_ptr = &land_init;
  p_actwk->sprvsize = 8;
  p_actwk->xspeed = -0x200;
  p_actwk->yspeed = -0x400;
  frameoutchkc(p_actwk);
}


static void banana_move(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  time_pg(p_actwk);
  emy_fall_col(p_actwk);
  frameoutchkc(p_actwk);
}


static void land_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &banana_land;
}


static void banana_land(SKC_sprite_status* p_actwk) {
  frameoutchkc(p_actwk);
}


static void saru00_chk_rev(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  bool hflip = p_parentwk->actflg.hflip;
  if (p_parentwk->u.obj.actflg0.fura_right == 1) {
    hflip = !hflip;
  }
  p_actwk->sprpri = !hflip ? PRI_4 : PRI_6;
}


static void saru00_chk_ofs(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short yposi = fp16_get_integer(p_parentwk->yposi) - 2;
  if (p_parentwk->patno != 0) {
    yposi -= 2;
  }
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static void saru00_chk_pri(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->sprpri = p_parentwk->sprpri;
}


static bool saru00_chk_shot(SKC_sprite_status* p_actwk) {
  SKC_chk_distance_result result = chk_distance(p_actwk);
  if (result.xdistance >= 128) return false;
  if (p_actwk->u.obj.actflg0.fura_right == 1) {
    result.right = !result.right;
  }
  return result.right;
}


static void saru00_add_dir(SKC_sprite_status* p_actwk, signed char offset) {
  p_actwk->u.obj.actfree.saru00_arm.angle += offset;
}


static void other_move(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.actfree.saru00_arm.unknown3b;
  if (p_actwk->u.obj.actfree.saru00_arm.unknown3b == 0) {
    p_actwk->u.obj.actfree.saru00_arm.unknown3b = p_actwk->u.obj.actfree.saru00_arm.unknown3a;
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_actwk->u.obj.actfree.saru00_arm.angle = p_parentwk->u.obj.actfree.saru00_arm.angle;
  }
  circle_move(p_actwk, 5);
}


static void chk_arm_shot(SKC_sprite_status* p_actwk, unsigned char r_no) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 1) {
    p_actwk->r_no = r_no;
    p_actwk->u.obj.actflg0.unused1 = 1;
    p_actwk->u.obj.actfree.saru00_arm.unknown3a /= 2;
    p_actwk->u.obj.actfree.saru00_arm.unknown3b = 1;
  }
}


static void chk_arm_ura(SKC_sprite_status* p_actwk, unsigned char r_no) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 0) {
    p_actwk->r_no = r_no;
    p_actwk->u.obj.actfree.saru00_arm.unknown3a *= 2;
    p_actwk->u.obj.actfree.saru00_arm.unknown3b = 1;
  }
}


static void chk_hand_shot(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 1) { // right
    if (p_actwk->u.obj.actflg0.puka_down == 0) {
      SKC_sprite_status* p_basewk = &g_ram.actwk[p_actwk->u.obj.ko];
      if (p_basewk->u.obj.actflg0.unused2 == 1) {
        SKC_sprite_status* p_elbow = &g_ram.actwk[p_actwk->u.obj.actfree.saru00_arm.elbow];
        if (p_actwk->u.obj.actfree.saru00_arm.angle < 132) {
          chk_hand_shot__set(p_actwk);
        }
      }
    }
  }
  else { // left
    if (p_actwk->u.obj.actflg0.puka_down == 0) {
      SKC_sprite_status* p_basewk = &g_ram.actwk[p_actwk->u.obj.ko];
      if (p_basewk->u.obj.actflg0.unused2 == 1) {
        SKC_sprite_status* p_elbow = &g_ram.actwk[p_actwk->u.obj.actfree.saru00_arm.elbow];
        if (p_actwk->u.obj.actfree.saru00_arm.angle >= 124) {
          p_actwk->sproffset = 0x2548;
          chk_hand_shot__set(p_actwk);
        }
      }
    }
  }
}


static void chk_hand_shot__set(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.puka_down = 1;
  p_actwk->patno = 4;
  soundset(81);
  SKC_sprite_status* p_new_actwk = set_act01(p_actwk, &yasi_set_tbl);
  if (p_new_actwk != 0 && p_actwk->u.obj.actflg0.fura_right == 1) {
    p_new_actwk->xspeed = -p_new_actwk->xspeed;
  }
}


static void set_arm_timer(SKC_sprite_status* p_actwk) {
  random();
  short dir = 1;
  if (BIT_IS_SET(g_ram.ranum, 0)) {
    dir = -dir;
  }
  p_actwk->u.obj.actfree.saru00_arm.dir = dir;
  p_actwk->u.obj.timer = g_ram.ranum & 60;
}


static SKC_enemy_init0_data saru00_init_tbl = {
  saru00pat,
  0x2548,
  PRI_5,
  32,
  32,
  0,
  0xB
};


static SKC_enemy_init2_data saru00_arm_init_tbl = {
  PRI_6,
  4,
  4,
  3,
  0
};


static SKC_enemy_init1_data banana_init_tbl = {
  0xA548,
  PRI_5,
  32,
  32,
  6,
  0xB
};


static SKC_enemy_init0_data yasi_init_tbl = {
  saru00pat,
  0x0548,
  PRI_5,
  32,
  32,
  6,
  0x98
};


static SKC_set_act03_data saru00_arm_set_tbl0 = {
  4,
  &saru00_arm
};


static SKC_set_act03_data saru00_arm_set_tbl1 = {
  4,
  &saru00_arm0
};


/*
static ? saru00_arm_set_tbl2 = {
  0,
  &saru00_arm,
  0x00,
  0x08
}
*/


static SKC_set_act00_data banana_set_tbl = {
  0,
  {
    { &saru00_banana, 0, 0 }
  }
};


static SKC_set_act01_data yasi_set_tbl = {
  0,
  {
    { &emyshot, &yasi_init_tbl, 0, &speedsetg20, 0, 0, -0x200, -0x400 }
  }
};


static signed char saru00_pg00[4] = { 7, 0, 1, -4 };
static signed char saru00_pg01[5] = { 0, 7, 2, 7, -4 };


static signed char banana_pg00[10] = { 8, 15, 8, 15, 9, 15, 10, 15, -8, 10 };
static signed char banana_pg01[5] = { 6, 126, -4, -121, -37 };
