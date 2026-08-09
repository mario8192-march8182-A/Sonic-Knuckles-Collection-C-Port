#include "obox04.h"
#include "../../data/pat/zone04/obox04.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../utils/stageno.h"
#include "../../action.h"
#include "../../dircol.h"
#include "../../hitchk.h"
#include "../../shared.h"
#include "../../sound.h"
#include "../explosion.h"
#include "../friend.h"
#include "../opnbox.h"
#include "../ring.h"
#include "../zone04/betl04.h"
#include "../zone04/mous04.h"
#include "../zone08/gost08.h"
static void obox04_switch(SKC_sprite_status* p_actwk);
static void obox04_friend(SKC_sprite_status* p_actwk);
static void obox04_friend_wait0(SKC_sprite_status* p_actwk);
static void obox04_friend_move0(SKC_sprite_status* p_actwk);
static void obox04_ring(SKC_sprite_status* p_actwk);
static void obox04_break(SKC_sprite_status* p_actwk);
static void chk_opnbox_ride(SKC_sprite_status* p_actwk);
static void set_obox04_item(SKC_sprite_status* p_actwk);
static void set_friend(SKC_sprite_status* p_actwk);
static void set_ring(SKC_sprite_status* p_actwk);
static void set_enemy(SKC_sprite_status* p_actwk);
static void set_obox04_friend_init(SKC_sprite_status* p_actwk);
static SKC_enemy_init2_data obox04_break_init_tbl;
static SKC_enemy_init2_data obox04_friend_init_tbl;
static SKC_enemy_init0_data obox04_ring_init_tbl;
static SKC_set_act00_data obox04_switch_set_tbl;
static SKC_set_act00_data obox04_break_set_tbl;
static SKC_set_act00_data obox04_ring_set_tbl;
static SKC_set_act00_data obox04_betl_set_tbl;
static SKC_set_act00_data obox04_mous_set_tbl;

extern sonic3_ram g_ram;


void obox04(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &obox04_init_tbl);
  p_actwk->r_ptr = &obox04_wait0;
  set_act00(p_actwk, &obox04_switch_set_tbl);
  if (p_actwk->u.obj.flagwork_index != 0 && BIT_IS_SET(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 0)) {
    p_actwk->r_ptr = &obox04_wait1;
    p_actwk->patno = 1;
    p_actwk->u.obj.actflg0.end = 1;
  }
}


void obox04_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.unused1 != 0) {
    p_actwk->r_ptr = &obox04_wait1;
    p_actwk->patno = 1;
    if (p_actwk->u.obj.flagwork_index != 0) {
      SET_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 1);
    }
    set_obox04_item(p_actwk);
    SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &bsexp01_set_tbl);
    if (p_new_actwk != 0) {
      p_new_actwk->u.obj.userflag = 8;
    }
    set_act00(p_actwk, &obox04_break_set_tbl);
  }
  obox04_wait1(p_actwk);
}


void obox04_wait1(SKC_sprite_status* p_actwk) {
  chk_opnbox_ride(p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void obox04_switch(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &switch_init_tbl);
  p_actwk->r_ptr = &switch_wait0;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.end == 1) {
    p_actwk->r_ptr = &switch_wait1;
    p_actwk->patno = 12;
  }
}


void swit04(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &swit04_init_tbl);
  swit04_wait0(p_actwk);
}


void swit04_wait0(SKC_sprite_status* p_actwk) {
  p_actwk->patno = 5;
  chk_switch_ride(p_actwk);
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->patno = 6;
    if (p_actwk->u.obj.cddat.plride == 1) {
      p_actwk->patno = 12;
      set_bane_jump(&g_ram.actwk[0], -0xA00);
    }
    if (p_actwk->u.obj.cddat.pl2ride == 1) {
      p_actwk->patno = 12;
      set_bane_jump(&g_ram.actwk[1], -0xA00);
    }
  }
  chk_emy_fout0(p_actwk);
}


static void obox04_friend(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &obox04_friend_init_tbl);
  p_actwk->r_ptr = &obox04_friend_wait0;
  p_actwk->sprvsize = 8;
  set_obox04_friend_init(p_actwk);
  actionsub(p_actwk);
}


static void obox04_friend_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &obox04_friend_move0;
    p_actwk->sprpri = PRI_1;
  }
  chk_emy_fout0(p_actwk);
}


static void obox04_friend_move0(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset < 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    p_actwk->yspeed = p_actwk->u.obj.actfree.obox04_friend.yspeed_init;
  }
  p_actwk->patno = BIT_IS_SET(g_ram.systemtimer, 3) ? 0 : 1;
  chk_emy_fout0(p_actwk);
}


static void obox04_ring(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &obox04_ring_init_tbl);
  p_actwk->r_ptr = &flyring;
  g_ram.sys_pattim4 = 255;
  p_actwk->sprvsize = 8;
  p_actwk->sprhsize = 8;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->actflg.onscreen = 1;
  set_break_spd(p_actwk, 4);
  actionsub(p_actwk);
}


static void obox04_break(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &obox04_break_init_tbl);
  p_actwk->r_ptr = &chk_break_fout;
  set_obox_break_pt(p_actwk);
  set_break_spd(p_actwk, 4);
  actionsub(p_actwk);
}


static void chk_opnbox_ride(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 43, 24, 24, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
}


static void set_obox04_item(SKC_sprite_status* p_actwk) {
  switch (p_actwk->u.obj.userflag) {
    case 1:
    default:
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


static void set_friend(SKC_sprite_status* p_actwk) {
  set_act00(p_actwk, &obox04_friend_set_tbl);
}


static void set_ring(SKC_sprite_status* p_actwk) {
  soundset(-71);
  set_act00(p_actwk, &obox04_ring_set_tbl);
}


static void set_enemy(SKC_sprite_status* p_actwk) {
  set_act00(p_actwk, &obox04_betl_set_tbl);
  set_act00(p_actwk, &obox04_mous_set_tbl);
}


static void set_obox04_friend_init(SKC_sprite_status* p_actwk) {
  static short spd_tbl[4] = {
    -0x380, -0x300, -0x280, -0x200
  };
  static unsigned short ofs_tbl[2] = {
    0x8580, 0x8592
  };

  short yspeed = spd_tbl[(p_actwk->u.obj.userflag & 6) / 2];
  p_actwk->yspeed = yspeed;
  p_actwk->u.obj.actfree.obox04_friend.yspeed_init = yspeed;
  unsigned char ofs_index = (p_actwk->u.obj.userflag & 2) / 2;
  p_actwk->sproffset = ofs_tbl[ofs_index];
  unsigned char friend_id = zone_friend_tbl[get_zone(g_ram.stageno)][ofs_index];
  p_actwk->patbase = zone_friend_init_tbl[friend_id].patbase;
  p_actwk->u.obj.timer = p_actwk->u.obj.userflag * 4;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xspeed = 0x200;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) < (unsigned short)fp16_get_integer(p_parentwk->xposi)) {
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  p_actwk->actflg.hflip = p_actwk->xspeed < 0;
}


SKC_enemy_init0_data obox04_init_tbl = {
  obox04pat,
  0,
  PRI_4,
  32,
  40,
  0,
  0
};


SKC_enemy_init0_data swit04_init_tbl = {
  obox04pat,
  0,
  PRI_3,
  16,
  8,
  5,
  0
};


static SKC_enemy_init2_data obox04_break_init_tbl = {
  PRI_2,
  8,
  8,
  2,
  0
};


static SKC_enemy_init2_data obox04_friend_init_tbl = {
  PRI_5,
  32,
  40,
  0,
  0
};


static SKC_enemy_init0_data obox04_ring_init_tbl = {
  ringpat,
  0xA6BC,
  PRI_3,
  8,
  8,
  0,
  71
};


static SKC_set_act00_data obox04_switch_set_tbl = {
  0,
  {
    { &obox04_switch, 0, 220 }
  }
};


static SKC_set_act00_data obox04_break_set_tbl = {
  4,
  {
    { &obox04_break, 0, 248 },
    { &obox04_break, 240, 248 },
    { &obox04_break, 16, 248 },
    { &obox04_break, 232, 248 },
    { &obox04_break, 24, 248 }
  }
};


SKC_set_act00_data obox04_friend_set_tbl = {
  4,
  {
    { &obox04_friend, 0, 252 },
    { &obox04_friend, 16, 252 },
    { &obox04_friend, 240, 252 },
    { &obox04_friend, 28, 252 },
    { &obox04_friend, 228, 252 }
  }
};


static SKC_set_act00_data obox04_ring_set_tbl = {
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


static SKC_set_act00_data obox04_betl_set_tbl = {
  1,
  {
    { &betl04_box, 232, 252 },
    { &betl04_box, 24, 252 }
  }
};


static SKC_set_act00_data obox04_mous_set_tbl = {
  1,
  {
    { &mous04_box, 248, 252 },
    { &mous04_box, 8, 252 }
  }
};
