#include "sai00.h"
#include "../../data/cg/zone00/sai00.h"
#include "../../data/pat/zone00/sai00.h"
#include "../../data/wrt/zone00/sai00.h"
#include "../../types/setactdata.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../types/wrtdata.h"
#include "../../types/wrtinitdata.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../utils/stageno.h"
#include "../../action.h"
#include "../../constants.h"
#include "../../dircol.h"
#include "../../shared.h"
#include "../../sound.h"
static void sai00_framein(SKC_sprite_status* p_actwk);
static void sai00_init(SKC_sprite_status* p_actwk);
static void sai00_wait(SKC_sprite_status* p_actwk);
static void sai00_atwait(SKC_sprite_status* p_actwk);
static void sai00_attack(SKC_sprite_status* p_actwk);
static void sai00_kemuri(SKC_sprite_status* p_actwk);
static void sai00_kemuri_init(SKC_sprite_status* p_actwk);
static void sai00_kemuri_wait(SKC_sprite_status* p_actwk);
static void sai00_wait_init0(SKC_sprite_status* p_actwk);
static void sai00_wait_init1(SKC_sprite_status* p_actwk);
static void sai00_turn_init(SKC_sprite_status* p_actwk);
static void sai00_atwait_init(SKC_sprite_status* p_actwk);
static void sai00_attack_init(SKC_sprite_status* p_actwk);
static void sai00_atturn_init(SKC_sprite_status* p_actwk);
static void chk_max_speed(SKC_sprite_status* p_actwk);
static void set_spd_pt(SKC_sprite_status* p_actwk);
static void set_spd_pt__move_right(SKC_sprite_status* p_actwk);
static void set_spd_pt__move_left(SKC_sprite_status* p_actwk);
static void set_spd_pt__set_kemuri(SKC_sprite_status* p_actwk);
static bool chk_attack(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_callback);
static bool sai00_down_col(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_callback);
static SKC_wrt_init_data sai00_init_tbl;
static SKC_wrt_init_data sai00_kemuri_init_tbl;
static SKC_set_act00_data sai00_kemuri_set_tbl0;
static SKC_set_act00_data sai00_kemuri_set_tbl1;
static SKC_wrt_data sai00_wrt_tbl;
static unsigned char sai00_pg01[16];
static unsigned char sai00_pg02[12];

extern sonic3_ram g_ram;


void sai00(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &sai00_framein);
  sai00_framein(p_actwk);
}


static void sai00_framein(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[4] = {
    &sai00_init,
    &sai00_wait,
    &sai00_atwait,
    &sai00_attack
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &sai00_wrt_tbl);
  chk_emy_foutwc0(p_actwk);
}


static void sai00_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &sai00_init_tbl);
  p_actwk->sprhsize = 8;
  p_actwk->sprvsize = 16;
  short accel = -16;
  short accel_max = -768;
  if (p_actwk->actflg.hflip == 1) {
    accel = -accel;
    accel_max = -accel_max;
    p_actwk->u.obj.actflg0.fura_right = 1;
    p_actwk->u.obj.actflg0.unused2 = 1;
  }
  p_actwk->u.obj.actfree.sai00.accel = accel;
  p_actwk->u.obj.actfree.sai00.accel_max = accel_max;
  p_actwk->u.obj.callback_ptr = &sai00_wait_init0;
}


static void sai00_wait(SKC_sprite_status* p_actwk) {
  if (chk_attack(p_actwk, &sai00_atwait_init)) return;
  if (sai00_down_col(p_actwk, &sai00_turn_init)) return;

  p_actwk->xspeed += p_actwk->u.obj.actfree.sai00.accel;
  speedset2(p_actwk);
  chk_max_speed(p_actwk);
  set_spd_pt(p_actwk);
}


static void sai00_atwait(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void sai00_attack(SKC_sprite_status* p_actwk) {
  if (sai00_down_col(p_actwk, &sai00_atturn_init)) return;

  speedset2(p_actwk);
}


static void sai00_kemuri(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[2] = {
    &sai00_kemuri_init,
    &sai00_kemuri_wait
  };

  if (get_act(g_ram.stageno) != ACT_2) {
    ko_offset1(p_actwk);
    act_tbl[p_actwk->r_no / 2](p_actwk);
    set_emy_wchg(p_actwk, &sai00_wrt_tbl);
    chk_oya_diew0(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void sai00_kemuri_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &sai00_kemuri_init_tbl);
  p_actwk->u.obj.callback_ptr = &wchg_die;
  sai00_kemuri_wait(p_actwk);
}


static void sai00_kemuri_wait(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
}


static void sai00_wait_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.unused2 ^= 1;
  p_actwk->u.obj.callback_ptr = &sai00_wait_init1;
  p_actwk->u.obj.actfree.sai00.accel = -p_actwk->u.obj.actfree.sai00.accel;
  p_actwk->u.obj.actfree.sai00.accel_max = -p_actwk->u.obj.actfree.sai00.accel_max;
}


static void sai00_wait_init1(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.fura_right ^= 1;
  p_actwk->actflg.hflip ^= 1;
  p_actwk->u.obj.actflg0.unused1 = 0;
  p_actwk->u.obj.callback_ptr = &sai00_wait_init0;
}


static void sai00_turn_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.unused2 = !p_actwk->u.obj.actflg0.fura_right;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  sai00_wait_init1(p_actwk);
}


static void sai00_atwait_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->patno = 0;
  p_actwk->u.obj.timer = 32;
  p_actwk->u.obj.callback_ptr = &sai00_attack_init;
  p_actwk->u.obj.actflg0.unused1 = 1;
  soundset(72);
  SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &sai00_kemuri_set_tbl1);
  if (p_new_actwk != 0) {
    p_new_actwk->u.obj.pg_data_ptr = sai00_pg02;
  }
}


static void sai00_attack_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  short xspeed = 0x400;
  if (p_actwk->u.obj.actflg0.fura_right == 0) {
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
}


static void sai00_atturn_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->patno = 0;
  sai00_turn_init(p_actwk);
}


static void chk_max_speed(SKC_sprite_status* p_actwk) {
  if (p_actwk->xspeed == 0
      || (p_actwk->u.obj.actflg0.unused2 == 1 && p_actwk->xspeed >= p_actwk->u.obj.actfree.sai00.accel_max)
      || (p_actwk->u.obj.actflg0.unused2 == 0 && p_actwk->xspeed <= p_actwk->u.obj.actfree.sai00.accel_max)) {
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


static void set_spd_pt(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 0) {
    set_spd_pt__move_left(p_actwk);
  }
  else {
    set_spd_pt__move_right(p_actwk);
  }
}


static void set_spd_pt__move_right(SKC_sprite_status* p_actwk) {
  unsigned char patno = 0;
  if (p_actwk->u.obj.actflg0.unused2 == 1) {
    if (p_actwk->xspeed <= 0x80) {
      patno = 1;
    }
  }
  else {
    patno = 1;
    if (p_actwk->xspeed <= 0x280) {
      patno = 2;
      if (p_actwk->u.obj.actflg0.unused1 == 0) {
        p_actwk->u.obj.actflg0.unused1 = 1;
        set_spd_pt__set_kemuri(p_actwk);
        return;
      }
    }
  }
  p_actwk->patno = patno;
}


static void set_spd_pt__move_left(SKC_sprite_status* p_actwk) {
  unsigned char patno = 0;
  if (p_actwk->u.obj.actflg0.unused2 == 0) {
    if (p_actwk->xspeed > -0x80) {
      patno = 1;
    }
  }
  else {
    patno = 1;
    if (p_actwk->xspeed > -0x280) {
      patno = 2;
      if (p_actwk->u.obj.actflg0.unused1 == 0) {
        p_actwk->u.obj.actflg0.unused1 = 1;
        set_spd_pt__set_kemuri(p_actwk);
        return;
      }
    }
  }
  p_actwk->patno = patno;
}


static void set_spd_pt__set_kemuri(SKC_sprite_status* p_actwk) {
  soundset(72);
  SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &sai00_kemuri_set_tbl0);
  if (p_new_actwk != 0) {
    p_new_actwk->u.obj.pg_data_ptr = sai00_pg01;
  }
}


static bool chk_attack(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_callback) {
  SKC_chk_distance_result result = chk_distance(p_actwk);
  if (result.ydistance <= 32 && result.xdistance <= 96) {
    if (p_actwk->u.obj.actflg0.fura_right == 0) {
      result.right = !result.right;
    }
    if (result.right) {
      p_callback(p_actwk);
      return true;
    }
  }
  return false;
}


static bool sai00_down_col(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_callback) {
  short xoffset = 4;
  if (p_actwk->u.obj.actflg0.fura_right == 0) {
    xoffset = -xoffset;
  }
  short xposi = fp16_get_integer(p_actwk->xposi) + xoffset;
  SKC_dircol_result result = emycol_d2(p_actwk, xposi);
  if (result.offset >= -1 && result.offset < 12) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    return false;
  }
  p_callback(p_actwk);
  return true;
}


static SKC_wrt_init_data sai00_init_tbl = {
  1,
  0x2500,
  21,
  0,
  sai00pat,
  PRI_5,
  20,
  16,
  0,
  0xB
};


static SKC_wrt_init_data sai00_kemuri_init_tbl = {
  1,
  0x044A,
  6,
  2,
  sai00pat,
  PRI_4,
  12,
  8,
  4,
  0
};


static SKC_set_act00_data sai00_kemuri_set_tbl0 = {
  0,
  {
    { &sai00_kemuri, 12, 8 }
  }
};


static SKC_set_act00_data sai00_kemuri_set_tbl1 = {
  0,
  {
    { &sai00_kemuri, 16, 8 }
  }
};


static SKC_wrt_data sai00_wrt_tbl = {
  sai00_cg,
  sai00_tbl
};


static unsigned char sai00_pg01[16] = { 2, 4, 4, 5, 6, 7, 4, 5, 6, 7, 4, 5, 6, 7, -12, -112 };
static unsigned char sai00_pg02[12] = { 2, 4, 4, 5, 6, 7, 4, 5, 6, 7, -12, -112 };
