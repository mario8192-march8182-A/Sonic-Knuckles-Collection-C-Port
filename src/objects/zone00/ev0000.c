#include "ev0000.h"
#include <string.h>
#include "../../data/cg/emerald.h"
#include "../../data/cg/tornado.h"
#include "../../data/pat/play.h"
#include "../../data/pat/zone00/ev0000.h"
#include "../../types/enemyinitdata.h"
#include "../../types/setactdata.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../color.h"
#include "../../dev.h"
#include "../../shared.h"
#include "../nuckle.h"
#include "../player.h"
#include "bs00m.h"
static void ev0000_init(SKC_sprite_status* p_actwk);
static void ev0000_wait0(SKC_sprite_status* p_actwk);
static void ev0000_move0_init(SKC_sprite_status* p_actwk);
static void ev0000_move0(SKC_sprite_status* p_actwk);
static void ev0000_wait1(SKC_sprite_status* p_actwk);
static void ev0000_move1_init(SKC_sprite_status* p_actwk);
static void ev0000_move1(SKC_sprite_status* p_actwk);
static void ev0000_move2(SKC_sprite_status* p_actwk);
static void set_shibuki(SKC_sprite_status* p_actwk);
static void ev0000_wait2(SKC_sprite_status* p_actwk);
static void ev0000_move3(SKC_sprite_status* p_actwk);
static void ev0000_wait3(SKC_sprite_status* p_actwk);
static void ev0000_move4(SKC_sprite_status* p_actwk);
static void ev0000_wait4(SKC_sprite_status* p_actwk);
static void ev0000_move5(SKC_sprite_status* p_actwk);
static void ev0000_move6(SKC_sprite_status* p_actwk);
static void ev0000_move7(SKC_sprite_status* p_actwk);
static void tornado(SKC_sprite_status* p_actwk);
static void tornado_move0(SKC_sprite_status* p_actwk);
static void tornado_move1(SKC_sprite_status* p_actwk);
static void propera0(SKC_sprite_status* p_actwk);
static void propera0_move(SKC_sprite_status* p_actwk);
static void propera1(SKC_sprite_status* p_actwk);
static void propera1_move(SKC_sprite_status* p_actwk);
static void shibuki(SKC_sprite_status* p_actwk);
static void shibuki_move(SKC_sprite_status* p_actwk);
static void emerald(SKC_sprite_status* p_actwk);
static void emerald_move0(SKC_sprite_status* p_actwk);
static void emerald_move1(SKC_sprite_status* p_actwk);
static void ev0000_super(SKC_sprite_status* p_actwk);
static void ev0000_super_move(SKC_sprite_status* p_actwk);
static void ev0000_playsync(SKC_sprite_status* p_actwk);
static void ev0000_pt_chg(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data emerald_init_tbl;
static SKC_set_act00_data tornado_set_tbl;
static SKC_set_act00_data tornadoparts_set_tbl;
static SKC_set_act00_data shibuki_set_tbl;
static SKC_set_act05_data nuckle_set_tbl;
static SKC_set_act05_data emeralds_set_tbl;
static signed char ev0000_pg00[11];
static signed char propera_pg00[8];
static signed char propera_pg01[4];
static signed char shibuki_pg00[15];
static unsigned short emeraldscolor[16];

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void ev0000(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[14] = {
    &ev0000_init,
    &ev0000_wait0,
    &ev0000_move0,
    &ev0000_wait1,
    &ev0000_move1,
    &ev0000_move2,
    &ev0000_wait2,
    &ev0000_move3,
    &ev0000_wait3,
    &ev0000_move4,
    &ev0000_wait4,
    &ev0000_move5,
    &ev0000_move6,
    &ev0000_move7
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  playwrt(p_actwk);
  ev0000_playsync(p_actwk);
  actionsub(p_actwk);
}


static void ev0000_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = playpat;
  p_actwk->sproffset = 0x0680;
  p_actwk->sprpri = PRI_5;
  p_actwk->patno = 186;
  p_actwk->sprhs = 64;
  p_actwk->sprvs = 32;
  fp16_set_integer(&p_actwk->xposi, 96);
  fp16_set_integer(&p_actwk->yposi, 48);
  p_actwk->u.obj.timer = 64;
  p_actwk->u.obj.callback_ptr = &ev0000_move0_init;
  p_actwk->u.obj.actfree.ev0000.shibuki_xoffset = 8;
  g_ram.DAT_08ffeeb6 = -0x16E8;
  g_ram.playpatno = 255;
  g_ram.actwk[0].patno = 0;
  g_ram.actwk[0].u.play.control_bitfield = 0x53;
}


static void ev0000_wait0(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void ev0000_move0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->xspeed = 0x300;
  p_actwk->yspeed = 0x600;
  set_act00(p_actwk, &tornado_set_tbl);
}


static void ev0000_move0(SKC_sprite_status* p_actwk) {
  p_actwk->yspeed -= 0x18;
  if (p_actwk->yspeed != 0) {
    speedset2(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    p_actwk->xspeed = 0;
    p_actwk->u.obj.timer = 95;
    p_actwk->u.obj.callback_ptr = &ev0000_move1_init;
    bs00m0_puka_init(p_actwk);
  }
}


static void ev0000_wait1(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  dec_timer(p_actwk);
}


static void ev0000_move1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->xspeed = 0x400;
  p_actwk->yspeed = -0x400;
  p_actwk->u.obj.pg_data_ptr = ev0000_pg00;
  p_actwk->u.obj.actflg0.fura_right = 1;
}


static void ev0000_move1(SKC_sprite_status* p_actwk) {
  p_actwk->xspeed -= 0x40;
  speedset(p_actwk);
  if ((unsigned short)fp16_get_integer(p_actwk->yposi) < 304) {
    ev0000_pt_chg(p_actwk);
  }
  else {
    p_actwk->r_no = 10;
    fp16_set_integer(&p_actwk->yposi, 304);
    p_actwk->yspeed = 0;
  }
}


static void ev0000_move2(SKC_sprite_status* p_actwk) {
  p_actwk->xspeed -= 0x40;
  speedset2(p_actwk);
  if (p_actwk->xspeed < 0x40) {
    p_actwk->r_no = 12;
    fp16_set_integer(&p_actwk->xposi, 64);
    p_actwk->u.obj.timer = 5;
    p_actwk->u.obj.callback_ptr = &set_shibuki;
    p_actwk->u.obj.actfree.ev0000.timer2 = 63;
    ev0000_super(p_actwk);
  }
}


static void set_shibuki(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 5;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 128) {
    set_act00(p_actwk, &shibuki_set_tbl);
  }
}


static void ev0000_wait2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.ev0000.timer2-- > 0) return;

  p_actwk->r_no = 14;
}


static void ev0000_move3(SKC_sprite_status* p_actwk) {
  ev0000_super_move(p_actwk);
  dec_timer(p_actwk);
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 4);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 512) {
    p_actwk->r_no = 16;
    p_actwk->u.obj.actfree.ev0000.timer2 = 31;
  }
}


static void ev0000_wait3(SKC_sprite_status* p_actwk) {
  ev0000_super_move(p_actwk);
  dec_timer(p_actwk);
  if (p_actwk->u.obj.actfree.ev0000.timer2-- == 0) {
    p_actwk->r_no = 18;
    p_actwk->u.obj.actflg0.unused2 = 1;
    p_actwk->u.obj.actfree.ev0000.shibuki_xoffset = 12;
  }
}


static void ev0000_move4(SKC_sprite_status* p_actwk) {
  ev0000_super_move(p_actwk);
  dec_timer(p_actwk);
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 4);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) <= 288) {
    p_actwk->r_no = 20;
    p_actwk->u.obj.actflg0.unused2 = 1;
    p_actwk->u.obj.actfree.ev0000.timer2 = 31;
    p_actwk->u.obj.actfree.ev0000.shibuki_xoffset = 16;
  }
}


static void ev0000_wait4(SKC_sprite_status* p_actwk) {
  ev0000_super_move(p_actwk);
  dec_timer(p_actwk);
  if (p_actwk->u.obj.actfree.ev0000.timer2-- == 0) {
    p_actwk->r_no = 22;
  }
}


static void ev0000_move5(SKC_sprite_status* p_actwk) {
  ev0000_super_move(p_actwk);
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) < 0x918) {
    dec_timer(p_actwk);
  }
  else {
    p_actwk->r_no = 24;
    set_act05(p_actwk, &nuckle_set_tbl);
  }
}


static void ev0000_move6(SKC_sprite_status* p_actwk) {
  ev0000_super_move(p_actwk);
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) >= 0x1240) {
    p_actwk->r_no = 26;
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 32);
  }
}


static void ev0000_move7(SKC_sprite_status* p_actwk) {
  ev0000_super_move(p_actwk);
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) >= 0x13D0) {
    g_ram.clchgtim2 = 0xFF;
    SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
    p_playerwk->r_no = 4;
    p_playerwk->u.play.cddat.jump = 1;
    p_playerwk->yspeed = -0x400;
    p_playerwk->xspeed = -0x100;
    p_playerwk->mspeed = 0;
    p_playerwk->mstno = 26;
    p_playerwk->u.play.control_bitfield = 0;
    memset(&g_ram.swdata, 0, sizeof(g_ram.swdata));
    g_ram.pl_input_lock_flag = 0xFF;
    g_ram.ssonicflag = 0;
    g_ram.ssonicclchg = 2;
    g_ram.ssonicclchgcnt = 5;
    memcpy(&g_ram.colorwk[48], emeraldscolor, sizeof(emeraldscolor));
    set_act05(p_actwk, &emeralds_set_tbl);
    set_emy_fout0(p_actwk);
  }
}


static void tornado(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &tornado_move0;
  p_actwk->patbase = tornado_pt;
  p_actwk->sproffset = 0x0529;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 64;
  p_actwk->sprvs = 32;
  bs00m0_puka_init(p_actwk);
  unlze_moduled(&g_vram[0xA520], tornado_cg);
  unlze_moduled(&g_vram[0xB620], emerald_cg);
  set_act00(p_actwk, &tornadoparts_set_tbl);
}


static void tornado_move0(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused2 == 1) {
    p_actwk->r_ptr = &tornado_move1;
  }
  if (p_parentwk->u.obj.actflg0.fura_right == 0) {
    ko_offset0(p_actwk);
  }
  actionsub(p_actwk);
}


static void tornado_move1(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 4);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 32) {
    actionsub(p_actwk);
  }
  else {
    set_emy_fout0(p_actwk);
  }
}


static void propera0(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = tornado_pt;
  p_actwk->sproffset = 0x0529;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 4;
  p_actwk->sprvs = 12;
  p_actwk->r_ptr = &propera0_move;
  propera0_move(p_actwk);
}


static void propera0_move(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, propera_pg00);
  ko_offset0(p_actwk);
  chk_oya_die0(p_actwk);
}


static void propera1(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = tornado_pt;
  p_actwk->sproffset = 0x0529;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 4;
  p_actwk->sprhs = 12;
  p_actwk->r_ptr = &propera1_move;
  propera1_move(p_actwk);
}


static void propera1_move(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, propera_pg01);
  ko_offset0(p_actwk);
  chk_oya_die0(p_actwk);
}


static void shibuki(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &shibuki_move;
  p_actwk->patbase = shibuki_pt;
  p_actwk->sproffset = 0x03D1;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 16;
  p_actwk->actflg.hflip = 1;
  p_actwk->u.obj.pg_data_ptr = shibuki_pg00;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  shibuki_move(p_actwk);
}


static void shibuki_move(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 96) {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    short xposi = fp16_get_integer(p_actwk->xposi) - p_parentwk->u.obj.actfree.ev0000.shibuki_xoffset;
    fp16_set_integer(&p_actwk->xposi, xposi);
    time_pg(p_actwk);
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void emerald(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &emerald_init_tbl);
  p_actwk->patno = p_actwk->u.obj.userflag / 2;
  p_actwk->r_ptr = &emerald_move0;
  p_actwk->sprvsize = 4;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(g_ram.actwk[0].xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(g_ram.actwk[0].yposi));
  set_break_spd(p_actwk, 64);
  emerald_move0(p_actwk);
}


static void emerald_move0(SKC_sprite_status* p_actwk) {
  short prev_yspeed = speedset(p_actwk);
  if (prev_yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      p_actwk->r_ptr = &emerald_move1;
    }
  }
  actionsub(p_actwk);
}


static void emerald_move1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_nucklewk = &g_ram.actwk[g_ram.DAT_08fffaa4_obj];
  short xposi = fp16_get_integer(p_actwk->xposi);
  if ((unsigned short)fp16_get_integer(p_nucklewk->xposi) < (unsigned short)(xposi - 8)
      || (unsigned short)fp16_get_integer(p_nucklewk->xposi) >= (unsigned short)(xposi + 8)) {
    actionsub(p_actwk);
  }
  else {
    short xspeed = !(p_actwk->u.obj.userflag & 2) ? p_nucklewk->xspeed : -p_nucklewk->xspeed;
    if (xspeed >= 0) {
      frameout(p_actwk);
    }
  }
}


static void ev0000_super(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = splaypat;
  p_actwk->patno = 33;
  g_ram.ssonicclchgtim = 0;
  g_ram.ssonicclchgcnt = 6;
  g_ram.ssonicringtim = 0x7FFF;
}


static void ev0000_super_move(SKC_sprite_status* p_actwk) {
  g_ram.ssonicflag = 1;
  p_actwk->patno = !(g_ram.systemtimer & 2) ? 33 : 34;
  if (g_ram.ssonicclchgtim-- == 0) {
    g_ram.ssonicclchgtim = 6;
    memcpy(&g_ram.colorwk[2], ssoniccolor[g_ram.ssonicclchgcnt], sizeof(ssoniccolor[g_ram.ssonicclchgcnt]));
    ++g_ram.ssonicclchgcnt;
    if (g_ram.ssonicclchgcnt >= 10) {
      g_ram.ssonicclchgcnt = 6;
    }
  }
}


static void ev0000_playsync(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08ffeeb6 < 0) {
    g_ram.DAT_08ffeeb6 += p_actwk->u.obj.actfree.ev0000.shibuki_xoffset;
  }
  else {
    short xposi = fp16_get_integer(g_ram.actwk[0].xposi) + p_actwk->u.obj.actfree.ev0000.shibuki_xoffset;
    fp16_set_integer(&g_ram.actwk[0].xposi, xposi);
  }
}


static void ev0000_pt_chg(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  p_actwk->pattim = p_actwk->u.obj.pg_data_ptr[0];
  p_actwk->patcnt = p_actwk->patcnt + 1 < (unsigned char)p_actwk->u.obj.pg_data_ptr[1] ? p_actwk->patcnt + 1 : 0;
  p_actwk->patno = p_actwk->u.obj.pg_data_ptr[p_actwk->patcnt + 2];
}


static SKC_enemy_init0_data emerald_init_tbl = {
  emerald_pt,
  0x65B1,
  PRI_5,
  4,
  4,
  1,
  0
};


static SKC_set_act00_data tornado_set_tbl = {
  0,
  {
    { &tornado, -34, 44 }
  }
};


static SKC_set_act00_data tornadoparts_set_tbl = {
  1,
  {
    { &propera0, 56,  4 },
    { &propera1, 24, 24 }
  }
};


static SKC_set_act00_data shibuki_set_tbl = {
  0,
  {
    { &shibuki, 0, 24 }
  }
};


static SKC_set_act05_data nuckle_set_tbl = {
  0,
  &nuckle
};


static SKC_set_act05_data emeralds_set_tbl = {
  6,
  &emerald
};


static signed char ev0000_pg00[11] = { 3, 8, -105, -106, -104, -106, -103, -106, -102, -106, -4 };


static signed char propera_pg00[8] = { 0, 1, 2, 3, 4, 3, 2, -4 };
static signed char propera_pg01[4] = { 0, 5, 6, -4 };


static signed char shibuki_pg00[15] = { 0, 1, 0, 0, 1, 1, 2, 2, 3, 2, 4, 1, 5, 1, -12 };


static unsigned short emeraldscolor[16] = {
  0x000, 0xEEE, 0xAAA, 0x0E4, 0x080, 0x0AE, 0x06E, 0x00E, 0x44E, 0xEE4, 0xE60, 0xE00, 0xC8E, 0xE4E, 0xC08, 0x444
};
