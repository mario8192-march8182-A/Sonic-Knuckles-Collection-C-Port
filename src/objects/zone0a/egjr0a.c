#include "egjr0a.h"
#include <stdbool.h>
#include "../../data/cg/zone0a/egjr0a.h"
#include "../../data/pat/zone0a/egjr0a.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../dev.h"
#include "../../etc.h"
#include "../../shared.h"
#include "../../sound.h"
#include "../friend.h"
static void egjr0a_framein(SKC_sprite_status* p_actwk);
static void egjr0a_00_move0(SKC_sprite_status* p_actwk);
static void egjr0a_02_wait0(SKC_sprite_status* p_actwk);
static void egjr0a_02_wait1(SKC_sprite_status* p_actwk);
static void egjr0a_04_wait0(SKC_sprite_status* p_actwk);
static void egjr0a_04_move0(SKC_sprite_status* p_actwk);
static void egjr0a_04_wait1(SKC_sprite_status* p_actwk);
static void egjr0a_leg(SKC_sprite_status* p_actwk);
static void egjr0a_leg_wait0(SKC_sprite_status* p_actwk);
static void egjr0a_gun(SKC_sprite_status* p_actwk);
static void egjr0a_gun_wait0(SKC_sprite_status* p_actwk);
static void egjr0a_gun_wait1(SKC_sprite_status* p_actwk);
static void egjr0a_laser(SKC_sprite_status* p_actwk);
static void egjr0a_laser_wait0(SKC_sprite_status* p_actwk);
static void egjr0a_laser_move0(SKC_sprite_status* p_actwk);
static void egjr0a_friend(SKC_sprite_status* p_actwk);
static void set_egjr0a_init(SKC_sprite_status* p_actwk);
static void egjr0a_00_init(SKC_sprite_status* p_actwk);
static void egjr0a_02_init(SKC_sprite_status* p_actwk);
static void egjr0a_04_init(SKC_sprite_status* p_actwk);
static bool chk_egjr0a_appear(SKC_sprite_status* p_actwk);
static void gun_offset1(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data egjr0a_init_tbl00;
static SKC_enemy_init0_data egjr0a_init_tbl04;
static SKC_enemy_init2_data egjr0a_leg_init_tbl;
static SKC_enemy_init2_data egjr0a_gun_init_tbl;
static SKC_enemy_init2_data egjr0a_laser_init_tbl;
static SKC_set_act09_data egjr0a_laser_set_tbl;
static SKC_set_act05_data egjr0a_friend_set_tbl;

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void egjr0a(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &egjr0a_framein);
}


static void egjr0a_framein(SKC_sprite_status* p_actwk) {
  set_egjr0a_init(p_actwk);
  p_actwk->r_ptr(p_actwk);
}


static void egjr0a_00_move0(SKC_sprite_status* p_actwk) {
  unsigned char unknown = p_actwk->u.obj.zoom.unknown - 3;
  if (unknown >= 4 && unknown != p_actwk->u.obj.zoom.unknown2) {
    p_actwk->u.obj.zoom.unknown = unknown;
    p_actwk->u.obj.zoom.unknown2 = unknown;
    wrt_zoom(p_actwk);
  }
  --p_actwk->u.obj.actfree.egjr0a.unknown3c;
  p_actwk->yspeed += p_actwk->u.obj.actfree.egjr0a.unknown3c;
  if (p_actwk->yspeed >= 0 || p_actwk->actflg.onscreen == 1) {
    speedset2_m(p_actwk);
    zoom_posi_ctr(p_actwk);
    actionsub(p_actwk);
  }
  else {
    SET_BIT(g_ram.DAT_08fffa82, (p_actwk->u.obj.userflag & 0xF0) >> 4);
    unlze_moduled(&g_vram[0xA000], egjr0a_cg);
    frameout(p_actwk);
  }
}


static void egjr0a_02_wait0(SKC_sprite_status* p_actwk) {
  egjr0a_pg(p_actwk);
  p_actwk->u.obj.actfree.egjr0a.prev_yposi = p_actwk->u.obj.actfree.egjr0a.yposi_save;
  p_actwk->u.obj.actfree.egjr0a.yposi_save = fp16_get_integer(p_actwk->yposi);
  puka_puka(p_actwk);
  speedset2(p_actwk);
  SKC_chk_distance_result result = chk_distance0(p_actwk, &g_ram.actwk[0]);
  chk_emy_rev(p_actwk, result.right);
  if ((unsigned short)result.ydistance <= 8) {
    p_actwk->r_ptr = &egjr0a_02_wait1;
    p_actwk->u.obj.actflg0.unused1 = 1;
  }
  chk_emy_foutc0(p_actwk);
}


static void egjr0a_02_wait1(SKC_sprite_status* p_actwk) {
  egjr0a_pg(p_actwk);
  if (p_actwk->u.obj.actflg0.unused1 == 0) {
    p_actwk->r_ptr = &egjr0a_02_wait0;
  }
  chk_emy_foutc0(p_actwk);
}


static void egjr0a_04_wait0(SKC_sprite_status* p_actwk) {
  if (!(g_ram.systemtimer & 0xF) && p_actwk->actflg.onscreen == 1) {
    set_act05(p_actwk, &egjr0a_friend_set_tbl);
    if (p_actwk->u.obj.puka.cnt-- == 0) {
      p_actwk->r_ptr = &egjr0a_04_move0;
      enemy_init0(p_actwk, &egjr0a_init_tbl02);
      CLEAR_BIT(p_actwk->sproffset, 15);
      p_actwk->xspeed = p_actwk->actflg.hflip == 0 ? -0x300 : 0x300;
      set_act00(p_actwk, &egjr0a_02_set_tbl);
    }
  }
  chk_emy_foutc0(p_actwk);
}


static void egjr0a_04_move0(SKC_sprite_status* p_actwk) {
  egjr0a_pg(p_actwk);
  p_actwk->yspeed -= 0x10;
  speedset2(p_actwk);
  if (p_actwk->yspeed <= -0x200) {
    p_actwk->r_ptr = &egjr0a_04_wait1;
    p_actwk->xspeed = 0;
    SET_BIT(p_actwk->sproffset, 15);
  }
  chk_emy_foutc0(p_actwk);
}


static void egjr0a_04_wait1(SKC_sprite_status* p_actwk) {
  egjr0a_pg(p_actwk);
  p_actwk->yspeed += 0x20;
  speedset2(p_actwk);
  if (p_actwk->yspeed >= 0x100) {
    p_actwk->r_ptr = &egjr0a_02_wait0;
    egjr0a_puka_init(p_actwk);
  }
  chk_emy_foutc0(p_actwk);
}


static void egjr0a_leg(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &egjr0a_leg_init_tbl);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->actflg.relative_coordinates == 0) {
    p_actwk->actflg.relative_coordinates = 0;
  }
  p_actwk->r_ptr = &egjr0a_leg_wait0;
}


static void egjr0a_leg_wait0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->patno = p_parentwk->yspeed < 0 ? 6 : p_parentwk->yspeed < 0x20 ? 5 : 4;
  chk_oya_die0(p_actwk);
}


static void egjr0a_gun(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &egjr0a_gun_init_tbl);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->actflg.relative_coordinates == 0) {
    p_actwk->actflg.relative_coordinates = 0;
  }
  p_actwk->r_ptr = &egjr0a_gun_wait0;
}


static void egjr0a_gun_wait0(SKC_sprite_status* p_actwk) {
  gun_offset1(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 1) {
    p_actwk->r_ptr = &egjr0a_gun_wait1;
    p_actwk->u.obj.timer = 95;
    set_act09(p_actwk, &egjr0a_laser_set_tbl);
  }
  chk_oya_die0(p_actwk);
}


static void egjr0a_gun_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &egjr0a_gun_wait0;
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_parentwk->u.obj.actflg0.unused1 = 0;
  }
  chk_oya_die0(p_actwk);
}


static void egjr0a_laser(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &egjr0a_laser_init_tbl);
  p_actwk->r_ptr = &egjr0a_laser_wait0;
  p_actwk->u.obj.timer = 31;
  egjr0a_laser_wait0(p_actwk);
}


static void egjr0a_laser_wait0(SKC_sprite_status* p_actwk) {
  p_actwk->patno = !(g_ram.systemtimer & 1) ? 0 : 7;
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &egjr0a_laser_move0;
    p_actwk->patno = 7;
    p_actwk->colino = 0x9C;
    p_actwk->xspeed = p_actwk->actflg.hflip == 0 ? -0x800 : 0x800;
    soundset(94);
  }
  chk_oya_diec0(p_actwk);
}


static void egjr0a_laser_move0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  chk_emy_foutc0(p_actwk);
}


static void egjr0a_friend(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &friend;
  p_actwk->r_no += 2;
  unsigned long number = random();
  unsigned char type = number & 1;
  p_actwk->sproffset = type == 0 ? 0x0580 : 0x0592;
  p_actwk->u.obj.actfree.friend.type = type;
  short xspeed = zone_friend_init_tbl[type].xspeed;
  p_actwk->xspeed = p_actwk->actflg.hflip == 0 ? xspeed : -xspeed;
  p_actwk->u.obj.actfree.friend.yspeed_init = zone_friend_init_tbl[type].yspeed;
  p_actwk->patbase = zone_friend_init_tbl[type].patbase;
  short yspeed = number >> 16 & 0x1FF;
  if (yspeed < 0x100) {
    yspeed = 0x100;
  }
  else {
    yspeed = -yspeed;
  }
  p_actwk->yspeed = yspeed;
  p_actwk->sprvsize = 12;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->actflg.hflip = 1;
  p_actwk->sprpri = PRI_6;
  p_actwk->sprhs = 8;
  p_actwk->pattim = 7;
  p_actwk->patno = 1;
  p_actwk->r_no = p_actwk->u.obj.actfree.friend.type * 2 + 4;
  actionsub(p_actwk);
}


static void set_egjr0a_init(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler init_tbl[3] = {
    &egjr0a_00_init,
    &egjr0a_02_init,
    &egjr0a_04_init
  };

  init_tbl[p_actwk->u.obj.userflag & 0x0F](p_actwk);
}


static void egjr0a_00_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &egjr0a_init_tbl00);
  p_actwk->r_ptr = &egjr0a_00_move0;
  p_actwk->u.obj.zoom.vram_offset = 0xA000;
  p_actwk->xspeed = p_actwk->actflg.hflip == 1 ? -0x80 : 0x80;
  fp16_set_integer(&p_actwk->u.obj.zoom.xposi, fp16_get_integer(p_actwk->xposi));
  fp16_set_integer(&p_actwk->u.obj.zoom.yposi, fp16_get_integer(p_actwk->yposi));
  p_actwk->u.obj.zoom.unknown = 127;
  p_actwk->u.obj.zoom.p_cg = egjrfly0a_cg;
  p_actwk->yspeed = 0x180;
}


static void egjr0a_02_init(SKC_sprite_status* p_actwk) {
  if (!chk_egjr0a_appear(p_actwk)) return;

  enemy_init0(p_actwk, &egjr0a_init_tbl02);
  p_actwk->r_ptr = &egjr0a_02_wait0;
  set_act00(p_actwk, &egjr0a_02_set_tbl);
}


void egjr0a_puka_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.accel_max = 0x100;
  p_actwk->yspeed = 0x100;
  p_actwk->u.obj.puka.accel = 8;
  p_actwk->u.obj.actflg0.puka_down = 0;
}


static void egjr0a_04_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &egjr0a_init_tbl04);
  p_actwk->r_ptr = &egjr0a_04_wait0;
  p_actwk->u.obj.puka.cnt = 4;
}


static bool chk_egjr0a_appear(SKC_sprite_status* p_actwk) {
  if (BIT_IS_SET(g_ram.DAT_08fffa82, (p_actwk->u.obj.userflag & 0xF0) >> 4)) return false;

  emy_fout(p_actwk);
  return true;
}


static void gun_offset1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  signed char xoffset = p_actwk->u.obj.oya_offset.x;
  p_actwk->actflg.hflip = 0;
  if (p_parentwk->actflg.hflip == 1) {
    xoffset = -xoffset;
    p_actwk->actflg.hflip = 1;
  }
  short xposi = fp16_get_integer(p_parentwk->xposi) + xoffset;
  fp16_set_integer(&p_actwk->xposi, xposi);
  signed char yoffset = p_actwk->u.obj.oya_offset.y;
  p_actwk->actflg.vflip = 0;
  if (p_parentwk->actflg.vflip == 1) {
    yoffset = -yoffset;
    p_actwk->actflg.vflip = 1;
  }
  short yposi = p_actwk->u.obj.actfree.egjr0a.prev_yposi;
  if (yposi == 0) {
    yposi = fp16_get_integer(p_parentwk->yposi);
  }
  yposi += yoffset;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void egjr0a_pg(SKC_sprite_status* p_actwk) {
  p_actwk->patno = !(g_ram.systemtimer & 1) ? 0 : 3;
}


static SKC_enemy_init0_data egjr0a_init_tbl00 = {
  zoompat,
  0xA500,
  PRI_5,
  32,
  32,
  0,
  0
};


SKC_enemy_init0_data egjr0a_init_tbl02 = {
  egjr0apat,
  0x8500,
  PRI_5,
  20,
  24,
  1,
  0x06
};


static SKC_enemy_init0_data egjr0a_init_tbl04 = {
  egjr0apat,
  0x8500,
  PRI_5,
  4,
  4,
  0,
  0
};


static SKC_enemy_init2_data egjr0a_leg_init_tbl = {
  PRI_5,
  12,
  16,
  6,
  0
};


static SKC_enemy_init2_data egjr0a_gun_init_tbl = {
  PRI_5,
  16,
  12,
  2,
  0
};


static SKC_enemy_init2_data egjr0a_laser_init_tbl = {
  PRI_5,
  32,
  4,
  7,
  0
};


SKC_set_act00_data egjr0a_02_set_tbl = {
  1,
  {
    { &egjr0a_leg, -12, 28 },
    { &egjr0a_gun, -28, -4 }
  }
};


static SKC_set_act09_data egjr0a_laser_set_tbl = {
  0,
  {
    { &egjr0a_laser, 11, -4 }
  }
};


static SKC_set_act05_data egjr0a_friend_set_tbl = {
  0,
  &egjr0a_friend
};
