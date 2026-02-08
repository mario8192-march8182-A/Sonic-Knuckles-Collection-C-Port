#include "opnbox.h"
#include "../types/chkdistanceresult.h"
#include "../types/chkemycoltresult.h"
#include "../types/hitchkdata.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../constants.h"
#include "../hitchk.h"
#include "../shared.h"
#include "friend.h"
#include "zone.h"
static void opnbox_init(SKC_sprite_status* p_actwk);
static void opnbox_init__set_fly(SKC_sprite_status* p_actwk);
static void opnbox_wait0(SKC_sprite_status* p_actwk);
static void set_break(SKC_sprite_status* SKC_p_actwk);
static void opnbox_wait1(SKC_sprite_status* p_actwk);
static void opnbox_wait2(SKC_sprite_status* p_actwk);
static void opnbox_fly0(SKC_sprite_status* p_actwk);
static void opnbox_fly1(SKC_sprite_status* p_actwk);
static void opnbox_fly2(SKC_sprite_status* p_actwk);
static void opnbox_fly3(SKC_sprite_status* p_actwk);
static void opnbox_fly4(SKC_sprite_status* p_actwk);
static void opnbox_fly40(SKC_sprite_status* p_actwk);
static void opnbox_fly5(SKC_sprite_status* p_actwk);
static void switch_(SKC_sprite_status* p_actwk);
static void switchud(SKC_sprite_status* p_actwk);
static void switchud_wait0(SKC_sprite_status* p_actwk);
static void switchud_wait1(SKC_sprite_status* p_actwk);
static void break_(SKC_sprite_status* p_actwk);
static void propera(SKC_sprite_status* p_actwk);
static void propera_wait0(SKC_sprite_status* p_actwk);
static void friend_wait0(SKC_sprite_status* p_actwk);
static void friend_move0(SKC_sprite_status* p_actwk);
static void friend_pg(SKC_sprite_status* p_actwk);
static void friend_wait1(SKC_sprite_status* p_actwk);
static void friend_move1(SKC_sprite_status* p_actwk);
static void friend_move2(SKC_sprite_status* p_actwk);
static void chk_pl_pausez02(SKC_sprite_status* p_actwk, unsigned char r_no);
static void get_closero(SKC_sprite_status* p_actwk, SKC_sprite_status* p_otherwk, short max_xspeed, short max_yspeed, short accel, short xoffset, short yoffset);
static void chk_switchu_ride(SKC_sprite_status* p_actwk);
static void set_friend_init(SKC_sprite_status* p_actwk);
static void chk_spd_pt(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data opnbox_init_tbl;
static SKC_enemy_init0_data break_init_tbl;
static SKC_enemy_init2_data friend_init_tbl;
static SKC_enemy_init2_data propera_init_tbl;
static SKC_set_act00_data switch_set_tbl;
static SKC_set_act00_data switch_set_tblud;
static SKC_set_act00_data propera_set_tbl;
static SKC_set_act00_data friend_set_tbl;
static signed char propera_pg00[6];
static SKC_sprite_pattern openbox_pt00;
static SKC_sprite_pattern openbox_pt01;
static SKC_sprite_pattern openbox_pt02;
static SKC_sprite_pattern openbox_pt03;
static SKC_sprite_pattern openbox_pt04;
static SKC_sprite_pattern openbox_pt05;
static SKC_sprite_pattern openbox_pt06;
static SKC_sprite_pattern openbox_pt07;
static SKC_sprite_pattern openbox_pt08;
static SKC_sprite_pattern openbox_pt09;
static SKC_sprite_pattern openbox_pt10;
static SKC_sprite_pattern openbox_pt11;
static SKC_sprite_pattern openbox_pt12;

extern sonic3_ram g_ram;


void opnbox(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[10] = {
    &opnbox_init,
    &opnbox_wait0,
    &opnbox_wait1,
    &opnbox_wait2,
    &opnbox_fly0,
    &opnbox_fly1,
    &opnbox_fly2,
    &opnbox_fly3,
    &opnbox_fly4,
    &opnbox_fly5
  };

  short xposi = fp16_get_integer(p_actwk->xposi);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  SKC_hitchk_data data = { 43, 24, 24, xposi };
  hitchk(p_actwk, data);
  actionsub(p_actwk);
}


static void opnbox_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &opnbox_init_tbl);
  if (p_actwk->actflg.vflip == 1) {
    opnbox_init__set_fly(p_actwk);
  }
  else {
    set_act00(p_actwk, &switch_set_tbl);
  }
}


static void opnbox_init__set_fly(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  short xposi = (g_ram.scra_h_posit >> 16) + 160;
  fp16_set_integer(&p_actwk->xposi, xposi);
  p_actwk->u.obj.puka.accel_max = xposi;
  short yposi = (g_ram.scra_v_posit >> 16) - 64;
  fp16_set_integer(&p_actwk->yposi, yposi);
  p_actwk->u.obj.actfree.opnbox.xspeed = 1;
  bs00m0_puka_init(p_actwk);
  set_act00(p_actwk, &switch_set_tblud);
  set_act00(p_actwk, &propera_set_tbl);
}


static void opnbox_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.unused1 == 0) return;

  p_actwk->r_no = 4;
}


static void set_break(SKC_sprite_status* p_actwk) {
  if (get_zone(g_ram.stageno) != MARBLE_GARDEN) {
    g_ram.pl2_lock_flag = 0xFF;
  }
  p_actwk->patno = 1;
  p_actwk->u.obj.timer = 64;
  g_ram.DAT_08fffacd = 0xFF;
  set_act00(p_actwk, &opnbox_break_set_tbl);
  set_act00(p_actwk, &friend_set_tbl);
  SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &bsexp01_set_tbl);
  p_new_actwk->u.obj.userflag = 8;
}


static void opnbox_wait1(SKC_sprite_status* p_actwk) {
  chk_pl_pause(p_actwk, 6);
}


static void opnbox_wait2(SKC_sprite_status* p_actwk) {
  chk_pl2_pause(p_actwk);
}


static void opnbox_fly0(SKC_sprite_status* p_actwk) {
  unsigned char rno_tbl[24] = {
    10, 10, 14, 10, 10, 10, 16, 10,
    10, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 10, 10, 10, 10, 10, 10
  };

  short xspeed = p_actwk->u.obj.actfree.opnbox.xspeed;
  if (xspeed >= 0) { // p_chk
    if ((g_ram.scra_h_posit >> 16) + 272 < (unsigned short)fp16_get_integer(p_actwk->xposi)) {
      xspeed = -xspeed;
    }
  }
  else { // m_chk
    if ((g_ram.scra_h_posit >> 16) + 48 >= (unsigned short)fp16_get_integer(p_actwk->xposi)) {
      xspeed = xspeed;
    }
  }
  p_actwk->u.obj.actfree.opnbox.xspeed = xspeed;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xspeed);
  unsigned short scr_yposi = (g_ram.scra_v_posit >> 16) + 64;
  if (get_zone(g_ram.stageno) == MARBLE_GARDEN) {
    scr_yposi -= 32;
  }
  short yspeed = 0x4000;
  if (scr_yposi <= (unsigned short)fp16_get_integer(p_actwk->yposi)) {
    yspeed = -yspeed;
  }
  p_actwk->yposi += yspeed;
  if (p_actwk->u.obj.actflg0.unused1 == 1) {
    p_actwk->r_no = rno_tbl[get_zone(g_ram.stageno)];
    set_break(p_actwk);
  }
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly1(SKC_sprite_status* p_actwk) {
  chk_pl_pause(p_actwk, 12);
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly2(SKC_sprite_status* p_actwk) {
  chk_pl2_pause(p_actwk);
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly3(SKC_sprite_status* p_actwk) {
  chk_pl_pausez02(p_actwk, 12);
  puka_puka(p_actwk);
  speedset2(p_actwk);
}


static void opnbox_fly4(SKC_sprite_status* p_actwk) {
  chk_pl_pause(p_actwk, 18);
  opnbox_fly40(p_actwk);
}


static void opnbox_fly40(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  if ((g_ram.scra_h_posit >> 16) - 96 >= (unsigned short)fp16_get_integer(p_actwk->xposi)) {
    g_ram.DAT_08fffaa2 = 0xFF;
  }
  else {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 2);
    speedset2(p_actwk);
  }
}


static void opnbox_fly5(SKC_sprite_status* p_actwk) {
  chk_pl2_pause(p_actwk);
  opnbox_fly40(p_actwk);
}


static void switch_(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &switch_wait0;
  enemy_init2(p_actwk, &switch_init_tbl);
}


void switch_wait0(SKC_sprite_status* p_actwk) {
  chk_switch_ride(p_actwk);
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->r_ptr = &switch_wait1;
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_parentwk->u.obj.actflg0.unused1 = 1;
    p_actwk->patno = 12;
  }
  chk_oya_die0(p_actwk);
}


void switch_wait1(SKC_sprite_status* p_actwk) {
  chk_switch_ride(p_actwk);
  chk_oya_die0(p_actwk);
}


static void switchud(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &switchud_wait0;
  p_actwk->actflg.vflip = 1;
  enemy_init2(p_actwk, &switch_init_tbl);
}


static void switchud_wait0(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = {
    -26, 52, -28, 56
  };

  ko_offset0(p_actwk);
  chk_switchu_ride(p_actwk);
  SKC_chk_emy_colt_result result = chk_emy_colt(p_actwk, col_tbl);
  if ((result.pl
        && g_ram.actwk[0].yspeed < 0
        && (g_ram.actwk[0].mstno == 2 || g_ram.actwk[0].u.play.character == SONIC))
      || (result.pl2 && g_ram.actwk[1].yspeed < 0)) {
    p_actwk->r_ptr = switchud_wait1;
    p_actwk->u.obj.oya_offset.y -= 8;
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_parentwk->u.obj.actflg0.unused1 = 1;
  }
  chk_oya_die0(p_actwk);
}


static void switchud_wait1(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  chk_switchu_ride(p_actwk);
  chk_oya_die0(p_actwk);
}


static void break_(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &break_init_tbl);
  if (g_ram.stageno == FLYING_BATTERY_ACT_1) {
    p_actwk->sproffset = 0x044E;
  }
  p_actwk->r_ptr = chk_break_fout;
  set_obox_break_pt(p_actwk);
  set_break_spd(p_actwk, 4);
  actionsub(p_actwk);
}


static void propera(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &propera_init_tbl);
  p_actwk->r_ptr = &propera_wait0;
  propera_wait0(p_actwk);
}


static void propera_wait0(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  pt_chg0(p_actwk, propera_pg00);
  chk_oya_die0(p_actwk);
}


void friend_(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &friend_init_tbl);
  p_actwk->r_ptr = &friend_wait0;
  p_actwk->sprvsize = 8;
  set_friend_init(p_actwk);
  actionsub(p_actwk);
}


static void friend_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &friend_move0;
    p_actwk->sprpri = PRI_1;
  }
  chk_emy_fout0(p_actwk);
}


static void friend_move0(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  short yoffset = ObjCheckFloorDist(p_actwk);
  if (yoffset < 0) {
    short yposi = fp16_get_integer(p_actwk->yposi) + yoffset;
    fp16_set_integer(&p_actwk->yposi, yposi);
    p_actwk->yspeed = p_actwk->u.obj.actfree.opnbox_friend.yspeed_init;
    SKC_chk_distance_result result = chk_distance(p_actwk);
    short xspeed = -0x200;
    if (g_ram.act_clear_flag != 0 && result.right) {
      xspeed = -xspeed;
    }
    p_actwk->xspeed = xspeed;
    chk_spd_pt(p_actwk);
  }
  friend_pg(p_actwk);
}


static void friend_pg(SKC_sprite_status* p_actwk) {
  p_actwk->patno = g_ram.systemtimer & 8 ? 0 : 1;
  chk_emy_fout0(p_actwk);
}


static void friend_wait1(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &friend_move1;
    p_actwk->sprpri = PRI_1;
  }
  chk_emy_fout0(p_actwk);
}


static void friend_move1(SKC_sprite_status* p_actwk) {
  get_closero(p_actwk, &g_ram.actwk[0], 0x300, 0x100, 0x10, 0, -0x30 - p_actwk->u.obj.userflag);
  speedset2(p_actwk);
  chk_spd_pt(p_actwk);
  if (g_ram.act_clear_flag == 0) {
    p_actwk->r_ptr = &friend_move2;
    p_actwk->actflg.hflip = 1;
  }
  friend_pg(p_actwk);
}


static void friend_move2(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 2);
  friend_pg(p_actwk);
}


void chk_pl_pause(SKC_sprite_status* p_actwk, unsigned char r_no) {
  if (p_actwk->u.obj.timer-- > 0) return;
  if (g_ram.actwk[0].u.play.cddat.unused7 == 1) return;
  if (g_ram.actwk[0].u.play.cddat.jump == 1) return;
  if (g_ram.actwk[0].r_no >= 6) return;

  p_actwk->r_no = r_no;
  set_pl_pause(p_actwk, &g_ram.actwk[0]);
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &actclear;
  }
}


void chk_pl2_pause(SKC_sprite_status* p_actwk) {
  if (g_ram.act_clear_flag == 0) return;

  if (get_zone(g_ram.stageno) == CARNIVAL_NIGHT) {
    set_pl_pause(p_actwk, &g_ram.actwk[0]);
  }
  if (p_actwk->u.obj.actflg0.unused7 == 0
      && g_ram.actwk[1].u.play.cddat.unused7 == 0
      && g_ram.actwk[1].u.play.cddat.jump == 0
      && g_ram.actwk[1].r_no < 6) {
    p_actwk->u.obj.actflg0.unused7 = 1;
    g_ram.pl2_lock_flag = 0;
    set_pl_pause(p_actwk, &g_ram.actwk[1]);
  }
}


static void chk_pl_pausez02(SKC_sprite_status* p_actwk, unsigned char r_no) {
  if (p_actwk->u.obj.timer-- > 0) return;
  if (g_ram.actwk[0].r_no >= 6) return;
  if (g_ram.actwk[0].actflg.onscreen == 0) return;
  if (g_ram.actwk[0].u.play.character != SONIC && g_ram.miles_carry_flag == 0) return;

  p_actwk->xspeed = -0x100;
  p_actwk->r_no = r_no;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &actclear;
  }
}


void set_pl_pause(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.control_bitfield = 0x81;
  p_playerwk->mstno = 19;
  p_playerwk->u.play.spindash_flag = 0;
  p_playerwk->xspeed = 0;
  p_playerwk->yspeed = 0;
  p_playerwk->mspeed = 0;
  p_actwk->u.obj.cddat.plpush = 0;
  p_actwk->u.obj.cddat.pl2push = 0;
  p_playerwk->u.play.cddat.push = 0;
}


static void get_closero(SKC_sprite_status* p_actwk, SKC_sprite_status* p_otherwk, short max_xspeed, short max_yspeed, short accel, short xoffset, short yoffset) {
  short other_xposi = fp16_get_integer(p_otherwk->xposi) + xoffset;
  short accel_copy = accel;
  if (other_xposi < fp16_get_integer(p_actwk->xposi)) {
    accel_copy = -accel_copy;
  }
  short new_xspeed = p_actwk->xspeed + accel_copy;
  if (new_xspeed <= max_xspeed && new_xspeed >= -max_xspeed) {
    p_actwk->xspeed = new_xspeed;
  }
  short new_yspeed;

  do {
    short other_yposi = fp16_get_integer(p_otherwk->yposi) + yoffset;
    if (other_yposi < p_actwk->yposi) {
      accel = -accel;
    }
    new_yspeed = p_actwk->yspeed + accel;
    if (new_yspeed > max_yspeed) return;
    max_yspeed = -max_yspeed;
  }
  while (new_yspeed < max_yspeed);

  p_actwk->yspeed = new_yspeed;
}


void chk_switch_ride(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 4, 6, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
}


static void chk_switchu_ride(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 5, 9, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
}


void set_obox_break_pt(SKC_sprite_status* p_actwk) {
  unsigned char pt_tbl[6] = {
    2, 3, 10, 4, 11, 144
  };

  p_actwk->patno = pt_tbl[p_actwk->u.obj.userflag / 2];
}


static void set_friend_init(SKC_sprite_status* p_actwk) {
  short spd_tbl[4] = {
    -0x380, -0x300, -0x280, -0x200
  };
  unsigned short ofs_tbl[4] = {
    0x8580, 0x8592, 0x842E, 0x8440
  };

  short yspeed = spd_tbl[(p_actwk->u.obj.userflag & 6) / 2];
  p_actwk->yspeed = yspeed;
  p_actwk->u.obj.actfree.opnbox_friend.yspeed_init = yspeed;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->actflg.vflip == 1) {
    p_actwk->r_ptr = &friend_wait1;
    p_actwk->u.obj.oya_offset.y += 8;
    p_actwk->yspeed = 0;
  }
  unsigned short ofs_index = p_actwk->u.obj.userflag & 2;
  if (g_ram.stageno == FLYING_BATTERY_ACT_1) {
    ofs_index += 4;
  }
  p_actwk->sproffset = ofs_tbl[ofs_index / 2];
  unsigned char friend_id = zone_friend_tbl[get_zone(g_ram.stageno)][ofs_index];
  p_actwk->patbase = zone_friend_init_tbl[friend_id].patbase;
  p_actwk->u.obj.timer = p_actwk->u.obj.userflag * 4;
  short xspeed = 0x200;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) < (unsigned short)fp16_get_integer(p_parentwk->xposi)) {
    xspeed = -xspeed;
  }
  p_actwk->xspeed = xspeed;
  chk_spd_pt(p_actwk);
}


static void chk_spd_pt(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.hflip = p_actwk->xspeed < 0;
}


static SKC_enemy_init0_data opnbox_init_tbl = {
  openbox_pt,
  0x8494,
  PRI_4,
  32,
  32,
  0,
  0
};


SKC_enemy_init2_data switch_init_tbl = {
  PRI_4,
  16,
  8,
  5,
  0
};


static SKC_enemy_init0_data break_init_tbl = {
  openbox_pt,
  0x8494,
  PRI_3,
  12,
  12,
  0,
  0
};


static SKC_enemy_init2_data friend_init_tbl = {
  PRI_5,
  8,
  8,
  2,
  0
};


static SKC_enemy_init2_data propera_init_tbl = {
  PRI_4,
  20,
  4,
  6,
  0
};


static SKC_set_act00_data switch_set_tbl = {
  0,
  {
    { &switch_, 0, 220 }
  }
};


static SKC_set_act00_data switch_set_tblud = {
  0,
  {
    { &switchud, 0, 36 }
  }
};


static SKC_set_act00_data propera_set_tbl = {
  1,
  {
    { &propera, 236, 220 },
    { &propera, 20, 220 }
  }
};


SKC_set_act00_data opnbox_break_set_tbl = {
  4,
  {
    { &break_, 0, 248 },
    { &break_, 240, 248 },
    { &break_, 16, 248 },
    { &break_, 232, 248 },
    { &break_, 24, 248 }
  }
};


static SKC_set_act00_data friend_set_tbl = {
  8,
  {
    { &friend, 0, 252 },
    { &friend, 248, 252 },
    { &friend, 8, 252 },
    { &friend, 16, 252 },
    { &friend, 240, 252 },
    { &friend, 232, 252 },
    { &friend, 24, 252 },
    { &friend, 252, 252 },
    { &friend, 4, 252 },
    { &friend, 12, 252 },
    { &friend, 244, 252 },
    { &friend, 236, 252 },
    { &friend, 20, 252 },
    { &friend, 28, 252 },
    { &friend, 228, 252 }
  }
};


static signed char propera_pg00[6] = { 0, 6, 7, 8, 9, -4 };


SKC_sprite_pattern* openbox_pt[13] = {
  &openbox_pt00,
  &openbox_pt01,
  &openbox_pt02,
  &openbox_pt03,
  &openbox_pt04,
  &openbox_pt05,
  &openbox_pt06,
  &openbox_pt07,
  &openbox_pt08,
  &openbox_pt09,
  &openbox_pt10,
  &openbox_pt11,
  &openbox_pt12
};


static SKC_sprite_pattern openbox_pt00 = {
  10,
  {
    { -32, 13, 0x000C, -32 },
    { -32, 13, 0x080C,   0 },
    { -16,  2, 0x0014,  -8 },
    { -16,  2, 0x0814,   0 },
    { -16,  6, 0x0017, -24 },
    { -16,  6, 0x0817,   8 },
    { -16,  2, 0x001D, -32 },
    { -16,  2, 0x081D,  24 },
    {   8, 14, 0x0000, -32 },
    {   8, 14, 0x0800,   0 }
  }
};
static SKC_sprite_pattern openbox_pt01 = {
  8,
  {
    { -32, 13, 0x0020, -32 },
    { -16,  1, 0x0028, -16 },
    {   0, 12, 0x002A, -32 },
    { -32, 13, 0x0820,   0 },
    { -16,  1, 0x0828,   8 },
    {   0, 12, 0x082A,   0 },
    {   8, 14, 0x0000, -32 },
    {   8, 14, 0x0800,   0 }
  }
};
static SKC_sprite_pattern openbox_pt02 = {
  2,
  {
    { -8, 1, 0x002E, -8 },
    { -8, 1, 0x082E,  0 }
  }
};
static SKC_sprite_pattern openbox_pt03 = {
  1,
  {
    { -8, 5, 0x0030, -8 }
  }
};
static SKC_sprite_pattern openbox_pt04 = {
  1,
  {
    { -8, 1, 0x0034, -8 }
  }
};
static SKC_sprite_pattern openbox_pt05 = {
  2,
  {
    { -12, 5, 0x0036, -16 },
    { -12, 5, 0x0836,   0 }
  }
};
static SKC_sprite_pattern openbox_pt06 = {
  2,
  {
    { -12, 8, 0x003A, -20 },
    {  -4, 4, 0x003D,   4 }
  }
};
static SKC_sprite_pattern openbox_pt07 = {
  1,
  {
    { -4, 8, 0x003F, -12 }
  }
};
static SKC_sprite_pattern openbox_pt08 = {
  1,
  {
    { -4, 0, 0x0042, -4 }
  }
};
static SKC_sprite_pattern openbox_pt09 = {
  1,
  {
    { -4, 8, 0x0043, -12 }
  }
};
static SKC_sprite_pattern openbox_pt10 = {
  1,
  {
    { -8, 5, 0x0830, -8 }
  }
};
static SKC_sprite_pattern openbox_pt11 = {
  1,
  {
    { -8, 1, 0x0834, -4 }
  }
};
static SKC_sprite_pattern openbox_pt12 = {
  2,
  {
    { -5, 5, 0x0036, -16 },
    { -5, 5, 0x0836,   0 }
  }
};
