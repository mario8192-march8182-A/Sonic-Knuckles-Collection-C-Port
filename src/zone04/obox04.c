#include "../globals.h"
#include "../macros.h"
#include "../util.h"
#include "obox04.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"
#include "../opnbox.h"
#include "../resources.h"
#include "../ring.h"
#include "../zone08/gost08.h"
static void obox04_switch(sprite_status* p_actwk);
static void obox04_friend(sprite_status* p_actwk);
static void obox04_friend_wait0(sprite_status* p_actwk);
static void obox04_friend_move0(sprite_status* p_actwk);
static void obox04_ring(sprite_status* p_actwk);
static void obox04_break(sprite_status* p_actwk);
static void chk_opnbox_ride(sprite_status* p_actwk);
static void set_obox04_item(sprite_status* p_actwk);
static void set_friend(sprite_status* p_actwk);
static void set_ring(sprite_status* p_actwk);
static void set_enemy(sprite_status* p_actwk);
static void set_obox04_friend_init(sprite_status* p_actwk);
static enemy_init2_data obox04_break_init_tbl;
static enemy_init2_data obox04_friend_init_tbl;
static enemy_init0_data obox04_ring_init_tbl;
static set_act00_data obox04_switch_set_tbl;
static set_act00_data obox04_break_set_tbl;
static set_act00_data obox04_ring_set_tbl;
static set_act00_data obox04_betl_set_tbl;
static set_act00_data obox04_mous_set_tbl;


void obox04(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &obox04_init_tbl);
  p_actwk->r_ptr = &obox04_wait0;
  set_act00(p_actwk, &obox04_switch_set_tbl);
  if (p_actwk->actfree.obox04.flagwork_index != 0) {
    if (BIT_0_IS_SET(flagwork[p_actwk->actfree.obox04.flagwork_index - 1])) {
      p_actwk->r_ptr = &obox04_wait1;
      p_actwk->patno = 1;
      SET_BIT_5(p_actwk->actfree.obox04.status_bitfield);
    }
  }
}


void obox04_wait0(sprite_status* p_actwk) {
  if (BIT_1_IS_SET(p_actwk->actfree.obox04.status_bitfield)) {
    p_actwk->r_ptr = &obox04_wait1;
    p_actwk->patno = 1;
    if (p_actwk->actfree.obox04.flagwork_index != 0) {
      SET_BIT_1(flagwork[p_actwk->actfree.obox04.flagwork_index - 1]);
    }
    set_obox04_item(p_actwk);
    sprite_status* p_new_actwk = set_act05(p_actwk, &bsexp01_set_tbl);
    if (p_new_actwk) {
      p_new_actwk->userflag1 = 8;
    }
    set_act00(p_actwk, &obox04_break_set_tbl);
  }
  obox04_wait1(p_actwk);
}


void obox04_wait1(sprite_status* p_actwk) {
  chk_opnbox_ride(p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void obox04_switch(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &switch_init_tbl);
  p_actwk->r_ptr = &switch_wait0;
  sprite_status* p_parentwk = &actwk[p_actwk->actfree.obox04.oya];
  if (BIT_5_IS_SET(p_parentwk->actfree.obox04.status_bitfield)) {
    p_actwk->r_ptr = &switch_wait1;
    p_actwk->patno = 12;
  }
}


void swit04(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &swit04_init_tbl);
  swit04_wait0(p_actwk);
}


void swit04_wait0(sprite_status* p_actwk) {
  p_actwk->patno = 5;
  chk_switch_ride(p_actwk);
  if (p_actwk->cddat1 & 0x18) {
    p_actwk->patno = 6;
    if (BIT_3_IS_SET(p_actwk->cddat1)) {
      p_actwk->patno = 12;
      set_bane_jump(&actwk[0], -2560);
    }
    if (BIT_4_IS_SET(p_actwk->cddat1)) {
      p_actwk->patno = 12;
      set_bane_jump(&actwk[1], -2560);
    }
  }
  chk_emy_fout0(p_actwk);
}


static void obox04_friend(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &obox04_friend_init_tbl);
  p_actwk->r_ptr = &obox04_friend_wait0;
  p_actwk->sprvsize = 8;
  set_obox04_friend_init(p_actwk);
  actionsub(p_actwk);
}


static void obox04_friend_wait0(sprite_status* p_actwk) {
  --p_actwk->actfree.friend.move_countdown;
  if (p_actwk->actfree.friend.move_countdown < 0) {
    p_actwk->r_ptr = &obox04_friend_move0;
    p_actwk->sprpri = PRI_1;
  }
  chk_emy_fout0(p_actwk);
}


static void obox04_friend_move0(sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  short unknown = ObjCheckFloorDist(p_actwk);
  if (unknown < 0) {
    p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown);
    p_actwk->yspeed = p_actwk->actfree.friend.yspeed;
  }
  unsigned char patno = 0;
  if (!BIT_3_IS_SET(systemtimer)) {
    patno = 1;
  }
  p_actwk->patno = patno;
  chk_emy_fout0(p_actwk);
}


static void obox04_ring(sprite_status* p_actwk) {
  enemy_init0(p_actwk, &obox04_ring_init_tbl);
  p_actwk->r_ptr = &flyring;
  flyring_patcnt = 255;
  p_actwk->sprvsize = 8;
  p_actwk->sprhsize = 8;
  p_actwk->actflg = 124;
  set_break_spd(p_actwk, 4);
  actionsub(p_actwk);
}


static void obox04_break(sprite_status* p_actwk) {
  enemy_init2(p_actwk, &obox04_break_init_tbl);
  p_actwk->r_ptr = &chk_break_fout;
  set_obox_break_pt(p_actwk);
  set_break_spd(p_actwk, 4);
  actionsub(p_actwk);
}


static void chk_opnbox_ride(sprite_status* p_actwk) {
  SolidObjectFull(p_actwk, 43, 24, 24, LONG_HIGH(p_actwk->xposi));
}


static void set_obox04_item(sprite_status* p_actwk) {
  switch (p_actwk->userflag1) {
    case 1:
      set_friend(p_actwk);
      break;
    case 2:
      set_ring(p_actwk);
      break;
    case 3:
      set_enemy(p_actwk);
      break;
    case 4:
      set_gost08(p_actwk);
      break;
  }
}


static void set_friend(sprite_status* p_actwk) {
  set_act00(p_actwk, &obox04_friend_set_tbl);
}


static void set_ring(sprite_status* p_actwk) {
  soundset(65465);
  set_act00(p_actwk, &obox04_ring_set_tbl);
}


static void set_enemy(sprite_status* p_actwk) {
  set_act00(p_actwk, &obox04_betl_set_tbl);
  set_act00(p_actwk, &obox04_mous_set_tbl);
}


static void set_obox04_friend_init(sprite_status* p_actwk) {
  static short spd_tbl[4] = {
    -896, -768, -640, -512
  };
  static unsigned short ofs_tbl[2] = {
    34176, 34194
  };

  unsigned char spd_index = (p_actwk->userflag1 & 6) / 2;
  p_actwk->yspeed = spd_tbl[spd_index];
  p_actwk->actfree.friend.yspeed = spd_tbl[spd_index];
  unsigned char ofs_index = (p_actwk->userflag1 & 2) / 2;
  p_actwk->sproffset = ofs_tbl[ofs_index];
  unsigned char* friends = &zone_friend_data[stageno.zone][0];
  unsigned char friend_id = friends[ofs_index];
  p_actwk->patbase = friend_data[friend_id].patbase;
  p_actwk->actfree.friend.move_countdown = p_actwk->userflag1 * 4;
  sprite_status* p_parentwk = &actwk[p_actwk->actfree.friend.oya];
  short xspeed = 512;
  if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) < util__to_unsigned(LONG_HIGH(p_parentwk->xposi))) { // unsigned
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  CLEAR_BIT_0(p_actwk->actflg);
  if (p_actwk->xspeed < 0) {
    SET_BIT_0(p_actwk->actflg);
  }
}


enemy_init0_data obox04_init_tbl = {
  obox04pat,
  0,
  PRI_4,
  32,
  40,
  0,
  0
};


enemy_init0_data swit04_init_tbl = {
  obox04pat,
  0,
  PRI_3,
  16,
  8,
  5,
  0
};


static enemy_init2_data obox04_break_init_tbl = {
  PRI_2,
  8,
  8,
  2,
  0
};


static enemy_init2_data obox04_friend_init_tbl = {
  PRI_5,
  32,
  40,
  0,
  0
};


static enemy_init0_data obox04_ring_init_tbl = {
  ringpat,
  42684,
  PRI_3,
  8,
  8,
  0,
  71
};


static set_act00_data obox04_switch_set_tbl = {
  0,
  {
    { &obox04_switch, 0, 220 }
  }
};


static set_act00_data obox04_break_set_tbl = {
  4,
  {
    { &obox04_break, 0, 248 },
    { &obox04_break, 240, 248 },
    { &obox04_break, 16, 248 },
    { &obox04_break, 232, 248 },
    { &obox04_break, 24, 248 }
  }
};


set_act00_data obox04_friend_set_tbl = {
  4,
  {
    { &obox04_friend, 0, 252 },
    { &obox04_friend, 16, 252 },
    { &obox04_friend, 240, 252 },
    { &obox04_friend, 28, 252 },
    { &obox04_friend, 228, 252 }
  }
};


static set_act00_data obox04_ring_set_tbl = {
  5,
  {
    { &obox04_ring, 248, 252 },
    { &obox04_ring, 8, 252 },
    { &obox04_ring, 16, 252 },
    { &obox04_ring, 240, 252 },
    { &obox04_ring, 24, 252 },
    { &obox04_ring, 232, 252 }
  }
};


static set_act00_data obox04_betl_set_tbl = {
  1,
  {
    { &betl04_box, 232, 252 },
    { &betl04_box, 24, 252 }
  }
};


static set_act00_data obox04_mous_set_tbl = {
  1,
  {
    { &mous04_box, 248, 252 },
    { &mous04_box, 8, 252 }
  }
};
