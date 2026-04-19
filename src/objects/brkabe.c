#include "brkabe.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../hitchk.h"
#include "../sound.h"
static void brkabeinit(SKC_sprite_status* p_actwk);
static void brkabemove(SKC_sprite_status* p_actwk);
static void brkabemove__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short prev_xspeed);
static void brkabemove2(SKC_sprite_status* p_actwk);
static void brkabemove_koma(SKC_sprite_status* p_actwk);
static void brkabemove_koma__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void brkabemovek(SKC_sprite_status* p_actwk);
static void brkabemovek__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short prev_xspeed);
static SKC_speed brkabespdtbl[12];
static SKC_speed brkabespdtbl2[12];
static SKC_speed brkabespdtbl01[8];
static SKC_speed brkabespdtbl012[8];
static SKC_speed brkabespdtbl022[20];
static SKC_speed brkabespdtbl02[20];
static SKC_speed brkabespdtbl03[8];
static SKC_speed brkabespdtbl032[8];
static SKC_sprite_pattern brkabesp00;
static SKC_sprite_pattern brkabesp01;
static SKC_sprite_pattern brkabesp02;
static SKC_sprite_pattern brkabesp000;
static SKC_sprite_pattern brkabesp010;
static SKC_sprite_pattern brkabesp020;
static SKC_sprite_pattern brkabe03sp00;
static SKC_sprite_pattern brkabe03sp10;
static SKC_sprite_pattern brkabe03sp01;
static SKC_sprite_pattern brkabe03sp11;
static SKC_sprite_pattern brkabe03sp02;
static SKC_sprite_pattern brkabe03sp12;
static SKC_sprite_pattern brkabe02sp00;
static SKC_sprite_pattern brkabe02sp01;
static SKC_sprite_pattern brkabe01sp00;
static SKC_sprite_pattern brkabe01sp01;
static SKC_sprite_pattern brkabe01sp02;
static SKC_sprite_pattern brkabe06sp00;
static SKC_sprite_pattern brkabe06sp01;
static SKC_sprite_pattern brkabe07sp00;
static SKC_sprite_pattern brkabe07sp10;
static SKC_sprite_pattern brkabe09sp00;
static SKC_sprite_pattern brkabe09sp01;

extern sonic3_ram g_ram;


void brkabe(SKC_sprite_status* p_actwk) {
  brkabeinit(p_actwk);
}


static void brkabeinit(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->r_ptr = &brkabemove;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7) && g_ram.stage_triggers[0] != 0) {
    frameout(p_actwk);
  }
  else {
    p_actwk->patno = p_actwk->u.obj.userflag & 0x0F;

    switch(get_zone(g_ram.stageno)) {
      default:
        p_actwk->patbase = brkabepat;
        p_actwk->sproffset = 0x4001;
        p_actwk->sprhs = 16;
        p_actwk->sprvs = 40;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = brkabespdtbl;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = brkabespdtbl2;
        break;
      case HYDROCITY:
        p_actwk->patbase = brkabe01pat;
        p_actwk->sproffset = p_actwk->patno != 2 ? 0x6001 : 0x4350;
        p_actwk->sprhs = p_actwk->patno != 2 ? 16 : 24;
        p_actwk->sprvs = 32;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = brkabespdtbl01;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = brkabespdtbl012;
        if (p_actwk->patno == 2) {
          p_actwk->r_ptr = &brkabemovek;
          return;
        }
        break;
      case MARBLE_GARDEN:
        p_actwk->patbase = brkabe02pat;
        p_actwk->sproffset = 0x4001;
        p_actwk->sprhs = 32;
        p_actwk->sprvs = 40;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = brkabespdtbl02;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = brkabespdtbl022;
        if (BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
          p_actwk->r_ptr = &brkabemovek;
          return;
        }
        else if (p_actwk->patno == 2) {
          p_actwk->r_ptr = &brkabemove_koma;
          return;
        }
        break;
      case CARNIVAL_NIGHT:
        p_actwk->patbase = brkabe03pat;
        p_actwk->sproffset = 0x4420;
        p_actwk->sprhs = 16;
        p_actwk->sprvs = 32;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = brkabespdtbl03;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = brkabespdtbl032;
        if (p_actwk->patno == 2) {
          p_actwk->r_ptr = &brkabemovek;
          return;
        }
        break;
      case LAUNCH_BASE:
        p_actwk->patbase = brkabe06pat;
        p_actwk->sproffset = 0x22EA;
        p_actwk->sprhs = 16;
        p_actwk->sprvs = 32;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = brkabespdtbl01;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = brkabespdtbl012;
        p_actwk->r_ptr = &brkabemovek;
        break;
      case MUSHROOM_HILL:
        p_actwk->patbase = brkabe07pat;
        p_actwk->sproffset = 0x434B;
        p_actwk->sprhs = 16;
        p_actwk->sprvs = 32;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = brkabespdtbl03;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = brkabespdtbl032;
        p_actwk->r_ptr = &brkabemovek;
        break;
      case SANDOPOLIS:
        p_actwk->patbase = brkabe03pat;
        p_actwk->sproffset = 0x448C;
        p_actwk->sprhs = 16;
        p_actwk->sprvs = p_actwk->patno != 4 ? 32 : 48;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = p_actwk->patno != 4 ? brkabespdtbl03 : brkabespdtbl;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = p_actwk->patno != 4 ? brkabespdtbl032 : brkabespdtbl2;
        p_actwk->r_ptr = &brkabemovek;
        break;
      case LAVA_REEF:
        p_actwk->patbase = brkabe09pat;
        p_actwk->sproffset = 0x640D;
        p_actwk->sprhs = 16;
        p_actwk->sprvs = 32;
        p_actwk->u.obj.actfree.brkabe.spdtbl_ptr = brkabespdtbl03;
        p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr = brkabespdtbl032;
        break;
    }

    brkabemove(p_actwk);
  }
}


static void brkabemove(SKC_sprite_status* p_actwk) {
  short plxspeed = g_ram.actwk[0].xspeed;
  short pl2xspeed = g_ram.actwk[1].xspeed;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    if (g_ram.stage_triggers[0] != 0) {
      frameout(p_actwk);
    }
    else {
      frameoutchk(p_actwk);
    }
  }
  else {
    if (result.plcoli[0] == HITCHK_COLI_SIDE || result.plcoli[1] == HITCHK_COLI_SIDE) {
      SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
      bool can_break_by_touch = g_ram.ssonicflag != 0 || p_playerwk->u.play.character == KNUCKLES;
      bool can_break_as_ball = (p_playerwk->u.play.powerdat.flame_baria == 1 || p_playerwk->u.play.cddat.push == 1)
          && p_playerwk->mstno == 2
          && abs(plxspeed) >= 0x480;
      if (result.plcoli[0] == HITCHK_COLI_SIDE && (can_break_by_touch || can_break_as_ball)) {
        p_actwk->u.obj.cddat.plpush = 0;
        brkabemove__break(p_actwk, p_playerwk, plxspeed);
        p_playerwk = &g_ram.actwk[1];
        if (p_actwk->u.obj.cddat.pl2push == 1 && p_playerwk->mstno == 2) {
          p_playerwk->xspeed = pl2xspeed;
          p_playerwk->mspeed = p_playerwk->xspeed;
          p_actwk->u.obj.cddat.pl2push = 0;
          p_playerwk->u.play.cddat.push = 0;
        }
      }
      else {
        p_playerwk = &g_ram.actwk[1];
        if (p_actwk->u.obj.cddat.pl2push == 1 && p_playerwk->mstno == 2 && abs(pl2xspeed) >= 0x480) {
          p_actwk->u.obj.cddat.pl2push = 0;
          brkabemove__break(p_actwk, p_playerwk, pl2xspeed);
          return;
        }
      }
    }
    frameoutchk(p_actwk);
  }
}


static void brkabemove__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short prev_xspeed) {
  p_playerwk->xspeed = prev_xspeed;
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 4);
  SKC_speed* p_spdtbl = p_actwk->u.obj.actfree.brkabe.spdtbl_ptr;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 8);
    p_spdtbl = p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr;
  }
  p_playerwk->mspeed = p_playerwk->xspeed;
  p_playerwk->u.play.cddat.push = 0;
  p_actwk->r_ptr = &brkabemove2;
  ++p_actwk->patno;
  breakgosubf(p_actwk, p_spdtbl);
  brkabemove2(p_actwk);
}


static void brkabemove2(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 0x70;
  if (p_actwk->actflg.onscreen == 1) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


void breakgosubf(SKC_sprite_status* p_actwk, SKC_speed* p_spdtbl) {
  soundset(89);
  p_actwk->sprpri = PRI_1;
  breakgosub3(p_actwk, p_spdtbl);
}


void breakgosub3(SKC_sprite_status* p_actwk, SKC_speed* p_spdtbl) {
  p_actwk->actflg.static_pattern = 1;
  SKC_sprite_pattern** pp_pattern = (SKC_sprite_pattern**)p_actwk->patbase;
  SKC_sprite_status* p_new_actwk = p_actwk;

  for (int i = 0; i < pp_pattern[p_actwk->patno]->cnt; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
      result.actwk_ptr->r_ptr = p_actwk->r_ptr;
    }
    p_new_actwk->patbase = &pp_pattern[p_actwk->patno]->spr[i];
    p_new_actwk->actflg = p_actwk->actflg;
    fp16_set_integer(&p_new_actwk->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&p_new_actwk->yposi, fp16_get_integer(p_actwk->yposi));
    p_new_actwk->sproffset = p_actwk->sproffset;
    SET_BIT(p_new_actwk->sproffset, 15);
    p_new_actwk->sprpri = p_actwk->sprpri;
    p_new_actwk->sprhs = p_actwk->sprhs;
    p_new_actwk->sprvs = p_actwk->sprvs;
    p_new_actwk->xspeed = p_spdtbl[i].xspeed;
    p_new_actwk->yspeed = p_spdtbl[i].yspeed;
  }
}


static void brkabemove_koma(SKC_sprite_status* p_actwk) {
  short plxspeed = g_ram.actwk[0].xspeed;
  short pl2xspeed = g_ram.actwk[1].xspeed;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  if (result.plcoli[0] == HITCHK_COLI_SIDE && BIT_IS_SET(p_playerwk->u.play.eventflag, 6)) {
    CLEAR_BIT(p_playerwk->u.play.eventflag, 6);
    p_playerwk->xspeed = plxspeed;
    p_playerwk->mspeed = p_playerwk->xspeed;
    p_playerwk->u.play.cddat.push = 0;
    p_actwk->u.obj.cddat.plpush = 0;
    brkabemove_koma__break(p_actwk, p_playerwk);
    p_playerwk = &g_ram.actwk[1];
    if (result.plcoli[1] == HITCHK_COLI_SIDE && BIT_IS_SET(p_playerwk->u.play.eventflag, 6)) {
      CLEAR_BIT(p_playerwk->u.play.eventflag, 6);
      p_playerwk->xspeed = pl2xspeed;
      p_playerwk->mspeed = p_playerwk->xspeed;
      p_playerwk->u.play.cddat.push = 0;
      p_actwk->u.obj.cddat.pl2push = 0;
    }
  }
  else {
    p_playerwk = &g_ram.actwk[1];
    if (result.plcoli[1] == HITCHK_COLI_SIDE && BIT_IS_SET(p_playerwk->u.play.eventflag, 6)) {
      CLEAR_BIT(p_playerwk->u.play.eventflag, 6);
      p_playerwk->xspeed = pl2xspeed;
      p_playerwk->mspeed = p_playerwk->xspeed;
      p_playerwk->u.play.cddat.push = 0;
      p_actwk->u.obj.cddat.pl2push = 0;
      brkabemove_koma__break(p_actwk, p_playerwk);
    }
  }
  frameoutchk(p_actwk);
}


static void brkabemove_koma__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  SKC_speed* p_spdtbl = p_actwk->u.obj.actfree.brkabe.spdtbl_ptr;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 8);
    p_spdtbl = p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr;
  }
  p_actwk->r_ptr = &brkabemove2;
  ++p_actwk->patno;
  breakgosubf(p_actwk, p_spdtbl);
  brkabemove2(p_actwk);
}


static void brkabemovek(SKC_sprite_status* p_actwk) {
  short plxspeed = g_ram.actwk[0].xspeed;
  short pl2xspeed = g_ram.actwk[1].xspeed;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    if (g_ram.stage_triggers[0] != 0) {
      frameout(p_actwk);
    }
    else {
      frameoutchk(p_actwk);
    }
  }
  else {
    if (result.plcoli[0] == HITCHK_COLI_SIDE || result.plcoli[1] == HITCHK_COLI_SIDE) {
      SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
      if (result.plcoli[0] == HITCHK_COLI_SIDE && p_playerwk->u.play.character == KNUCKLES) {
        p_actwk->u.obj.cddat.plpush = 0;
        brkabemovek__break(p_actwk, p_playerwk, plxspeed);
        p_playerwk = &g_ram.actwk[1];
        if (p_actwk->u.obj.cddat.pl2push == 1 && p_playerwk->u.play.character == KNUCKLES) {
          p_playerwk->xspeed = pl2xspeed;
          p_playerwk->mspeed = p_playerwk->xspeed;
          p_actwk->u.obj.cddat.pl2push = 0;
          p_playerwk->u.play.cddat.push = 0;
        }
      }
      else {
        p_playerwk = &g_ram.actwk[1];
        if (p_actwk->u.obj.cddat.pl2push == 1 && p_playerwk->u.play.character == KNUCKLES) {
          p_actwk->u.obj.cddat.pl2push = 0;
          brkabemovek__break(p_actwk, p_playerwk, pl2xspeed);
          return;
        }
      }
    }
    frameoutchk(p_actwk);
  }
}


static void brkabemovek__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short prev_xspeed) {
  p_playerwk->xspeed = prev_xspeed;
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 4);
  SKC_speed* p_spdtbl = p_actwk->u.obj.actfree.brkabe.spdtbl_ptr;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 8);
    p_spdtbl = p_actwk->u.obj.actfree.brkabe.spdtbl2_ptr;
  }
  p_playerwk->mspeed = p_playerwk->xspeed;
  p_playerwk->u.play.cddat.push = 0;
  if (p_playerwk->u.play.character == KNUCKLES && p_playerwk->u.play.talent_status == 1) {
    p_playerwk->u.play.talent_status = 2;
    p_playerwk->mstno = 33;
    p_playerwk->u.play.cddat.left = p_playerwk->xspeed >= 0 ? 0 : 1;
  }
  p_actwk->r_ptr = &brkabemove2;
  ++p_actwk->patno;
  breakgosubf(p_actwk, p_spdtbl);
  brkabemove2(p_actwk);
}


static SKC_speed brkabespdtbl[12] = {
  { 0x400, -0x500 },
  { 0x600, -0x600 },
  { 0x600, -0x100 },
  { 0x800, -0x200 },
  { 0x680,      0 },
  { 0x880,      0 },
  { 0x600,  0x100 },
  { 0x800,  0x200 },
  { 0x400,  0x500 },
  { 0x600,  0x600 },
  { 0x300,  0x600 },
  { 0x500,  0x700 }
};


static SKC_speed brkabespdtbl2[12] = {
  { -0x600, -0x600 },
  { -0x400, -0x500 },
  { -0x800, -0x200 },
  { -0x600, -0x100 },
  { -0x880,      0 },
  { -0x680,      0 },
  { -0x800,  0x200 },
  { -0x600,  0x100 },
  { -0x600,  0x600 },
  { -0x400,  0x500 },
  { -0x500,  0x700 },
  { -0x300,  0x600 }
};


static SKC_speed brkabespdtbl01[8] = {
  { 0x400, -0x500 },
  { 0x600, -0x600 },
  { 0x600, -0x100 },
  { 0x800, -0x200 },
  { 0x600,  0x100 },
  { 0x800,  0x200 },
  { 0x400,  0x500 },
  { 0x600,  0x600 }
};


static SKC_speed brkabespdtbl012[8] = {
  { -0x600, -0x600 },
  { -0x400, -0x500 },
  { -0x800, -0x200 },
  { -0x600, -0x100 },
  { -0x800,  0x200 },
  { -0x600,  0x100 },
  { -0x600,  0x600 },
  { -0x400,  0x500 }
};


static SKC_speed brkabespdtbl022[20] = {
  { 0x400, -0x500 },
  { 0x500, -0x580 },
  { 0x600, -0x600 },
  { 0x700, -0x680 },
  { 0x600, -0x100 },
  { 0x700, -0x180 },
  { 0x800, -0x200 },
  { 0x900, -0x280 },
  { 0x680,      0 },
  { 0x780,      0 },
  { 0x880,      0 },
  { 0x980,      0 },
  { 0x600,  0x100 },
  { 0x700,  0x180 },
  { 0x800,  0x200 },
  { 0x900,  0x280 },
  { 0x400,  0x500 },
  { 0x500,  0x580 },
  { 0x600,  0x600 },
  { 0x700,  0x680 }
};


static SKC_speed brkabespdtbl02[20] = {
  { -0x700, -0x680 },
  { -0x600, -0x600 },
  { -0x500, -0x580 },
  { -0x400, -0x500 },
  { -0x900, -0x280 },
  { -0x800, -0x200 },
  { -0x700, -0x180 },
  { -0x600, -0x100 },
  { -0x980,      0 },
  { -0x880,      0 },
  { -0x780,      0 },
  { -0x680,      0 },
  { -0x900,  0x280 },
  { -0x800,  0x200 },
  { -0x700,  0x180 },
  { -0x600,  0x100 },
  { -0x700,  0x680 },
  { -0x600,  0x600 },
  { -0x500,  0x580 },
  { -0x400,  0x500 }
};


static SKC_speed brkabespdtbl03[8] = {
  { 0x400, -0x500 },
  { 0x600, -0x600 },
  { 0x600, -0x100 },
  { 0x800, -0x200 },
  { 0x600,  0x100 },
  { 0x800,  0x200 },
  { 0x400,  0x500 },
  { 0x600,  0x600 }
};


static SKC_speed brkabespdtbl032[8] = {
  { -0x600, -0x600 },
  { -0x400, -0x500 },
  { -0x800, -0x200 },
  { -0x600, -0x100 },
  { -0x800,  0x200 },
  { -0x600,  0x100 },
  { -0x600,  0x600 },
  { -0x400,  0x500 }
};


SKC_sprite_pattern* brkabepat[6] = {
  &brkabesp00,
  &brkabesp000,
  &brkabesp01,
  &brkabesp010,
  &brkabesp02,
  &brkabesp020
};


static SKC_sprite_pattern brkabesp00 = {
  5,
  {
    { -40, 13, 0x0016, -16 },
    { -24, 13, 0x1816, -16 },
    {  -8, 13, 0x0016, -16 },
    {   8, 13, 0x1816, -16 },
    {  24, 13, 0x0016, -16 }
  }
};
static SKC_sprite_pattern brkabesp01 = {
  5,
  {
    { -40, 13, 0x1016, -16 },
    { -24, 13, 0x0816, -16 },
    {  -8, 13, 0x1016, -16 },
    {   8, 13, 0x0816, -16 },
    {  24, 13, 0x1816, -16 }
  }
};
static SKC_sprite_pattern brkabesp02 = {
  5,
  {
    { -40, 13, 0x0816, -16 },
    { -24, 13, 0x1016, -16 },
    {  -8, 13, 0x0816, -16 },
    {   8, 13, 0x1016, -16 },
    {  24, 13, 0x0816, -16 }
  }
};
static SKC_sprite_pattern brkabesp000 = {
  10,
  {
    { -40, 5, 0x0016, -16 },
    { -40, 5, 0x001A,   0 },
    { -24, 5, 0x181A, -16 },
    { -24, 5, 0x1816,   0 },
    {  -8, 5, 0x0016, -16 },
    {  -8, 5, 0x001A,   0 },
    {   8, 5, 0x181A, -16 },
    {   8, 5, 0x1816,   0 },
    {  24, 5, 0x0016, -16 },
    {  24, 5, 0x001A,   0 }
  }
};
static SKC_sprite_pattern brkabesp010 = {
  10,
  {
    { -40, 5, 0x1016, -16 },
    { -40, 5, 0x101A,   0 },
    { -24, 5, 0x081A, -16 },
    { -24, 5, 0x0816,   0 },
    {  -8, 5, 0x1016, -16 },
    {  -8, 5, 0x101A,   0 },
    {   8, 5, 0x081A, -16 },
    {   8, 5, 0x0816,   0 },
    {  24, 5, 0x181A, -16 },
    {  24, 5, 0x1816,   0 }
  }
};
static SKC_sprite_pattern brkabesp020 = {
  10,
  {
    { -40, 5, 0x081A, -16 },
    { -40, 5, 0x0816,   0 },
    { -24, 5, 0x1016, -16 },
    { -24, 5, 0x101A,   0 },
    {  -8, 5, 0x081A, -16 },
    {  -8, 5, 0x0816,   0 },
    {   8, 5, 0x1016, -16 },
    {   8, 5, 0x101A,   0 },
    {  24, 5, 0x081A, -16 },
    {  24, 5, 0x0816,   0 }
  }
};


SKC_sprite_pattern* brkabe03pat[6] = {
  &brkabe03sp00,
  &brkabe03sp10,
  &brkabe03sp01,
  &brkabe03sp11,
  &brkabe03sp02,
  &brkabe03sp12
};


static SKC_sprite_pattern brkabe03sp00 = {
  4,
  {
    { -32, 13, 0x0000, -16 },
    { -16, 13, 0x0000, -16 },
    {   0, 13, 0x0000, -16 },
    {  16, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern brkabe03sp10 = {
  8,
  {
    { -32, 5, 0x0000, -16 },
    { -32, 5, 0x0004,   0 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0004,   0 },
    {   0, 5, 0x0000, -16 },
    {   0, 5, 0x0004,   0 },
    {  16, 5, 0x0000, -16 },
    {  16, 5, 0x0004,   0 }
  }
};
static SKC_sprite_pattern brkabe03sp01 = {
  4,
  {
    { -32, 13, 0x0008, -16 },
    { -16, 13, 0x0008, -16 },
    {   0, 13, 0x0008, -16 },
    {  16, 13, 0x0008, -16 }
  }
};
static SKC_sprite_pattern brkabe03sp11 = {
  8,
  {
    { -32, 5, 0x0008, -16 },
    { -32, 5, 0x000C,   0 },
    { -16, 5, 0x0008, -16 },
    { -16, 5, 0x000C,   0 },
    {   0, 5, 0x0008, -16 },
    {   0, 5, 0x000C,   0 },
    {  16, 5, 0x0008, -16 },
    {  16, 5, 0x000C,   0 }
  }
};
static SKC_sprite_pattern brkabe03sp02 = {
  6,
  {
    { -48, 13, 0x0000, -16 },
    { -32, 13, 0x0000, -16 },
    { -16, 13, 0x0000, -16 },
    {   0, 13, 0x0000, -16 },
    {  16, 13, 0x0000, -16 },
    {  32, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern brkabe03sp12 = {
  12,
  {
    { -48, 5, 0x0000, -16 },
    { -48, 5, 0x0004,   0 },
    { -32, 5, 0x0000, -16 },
    { -32, 5, 0x0004,   0 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0004,   0 },
    {   0, 5, 0x0000, -16 },
    {   0, 5, 0x0004,   0 },
    {  16, 5, 0x0000, -16 },
    {  16, 5, 0x0004,   0 },
    {  32, 5, 0x0000, -16 },
    {  32, 5, 0x0004,   0 }
  }
};


SKC_sprite_pattern* brkabe02pat[4] = {
  &brkabe02sp00,
  &brkabe02sp01,
  &brkabe02sp00,
  &brkabe02sp01
};


static SKC_sprite_pattern brkabe02sp00 = {
  10,
  {
    { -40, 13, 0x0066, -32 },
    { -40, 13, 0x0866,   0 },
    { -24, 13, 0x0066, -32 },
    { -24, 13, 0x0866,   0 },
    {  -8, 13, 0x0066, -32 },
    {  -8, 13, 0x0866,   0 },
    {   8, 13, 0x0066, -32 },
    {   8, 13, 0x0866,   0 },
    {  24, 13, 0x006E, -32 },
    {  24, 13, 0x086E,   0 }
  }
};
static SKC_sprite_pattern brkabe02sp01 = {
  20,
  {
    { -40, 5, 0x0066, -32 },
    { -40, 5, 0x006A, -16 },
    { -40, 5, 0x086A,   0 },
    { -40, 5, 0x0866,  16 },
    { -24, 5, 0x0066, -32 },
    { -24, 5, 0x006A, -16 },
    { -24, 5, 0x086A,   0 },
    { -24, 5, 0x0866,  16 },
    {  -8, 5, 0x0066, -32 },
    {  -8, 5, 0x006A, -16 },
    {  -8, 5, 0x086A,   0 },
    {  -8, 5, 0x0866,  16 },
    {   8, 5, 0x0066, -32 },
    {   8, 5, 0x006A, -16 },
    {   8, 5, 0x086A,   0 },
    {   8, 5, 0x0866,  16 },
    {  24, 5, 0x006E, -32 },
    {  24, 5, 0x0072, -16 },
    {  24, 5, 0x0872,   0 },
    {  24, 5, 0x086E,  16 }
  }
};


SKC_sprite_pattern* brkabe01pat[4] = {
  &brkabe01sp00,
  &brkabe01sp01,
  &brkabe01sp02,
  &brkabe01sp02
};


static SKC_sprite_pattern brkabe01sp00 = {
  4,
  {
    { -32, 13, 0x0060, -16 },
    { -16, 13, 0x0068, -16 },
    {   0, 13, 0x0060, -16 },
    {  16, 13, 0x0068, -16 }
  }
};
static SKC_sprite_pattern brkabe01sp01 = {
  8,
  {
    { -32, 5, 0x0060, -16 },
    { -32, 5, 0x0064,   0 },
    { -16, 5, 0x0068, -16 },
    { -16, 5, 0x006C,   0 },
    {   0, 5, 0x0060, -16 },
    {   0, 5, 0x0064,   0 },
    {  16, 5, 0x0068, -16 },
    {  16, 5, 0x006C,   0 }
  }
};
static SKC_sprite_pattern brkabe01sp02 = {
  8,
  {
    { -32, 9, 0x0000, -24 },
    { -32, 9, 0x0800,   0 },
    { -16, 9, 0x0006, -24 },
    { -16, 9, 0x0806,   0 },
    {   0, 9, 0x0000, -24 },
    {   0, 9, 0x0800,   0 },
    {  16, 9, 0x0006, -24 },
    {  16, 9, 0x0806,   0 }
  }
};


SKC_sprite_pattern* brkabe06pat[2] = {
  &brkabe06sp00,
  &brkabe06sp01
};


static SKC_sprite_pattern brkabe06sp00 = {
  4,
  {
    { -32, 13, 0x003E, -16 },
    { -16, 13, 0x0046, -16 },
    {   0, 13, 0x003E, -16 },
    {  16, 13, 0x0046, -16 }
  }
};
static SKC_sprite_pattern brkabe06sp01 = {
  8,
  {
    { -32, 5, 0x003E, -16 },
    { -32, 5, 0x0042,   0 },
    { -16, 5, 0x0046, -16 },
    { -16, 5, 0x004A,   0 },
    {   0, 5, 0x003E, -16 },
    {   0, 5, 0x0042,   0 },
    {  16, 5, 0x0046, -16 },
    {  16, 5, 0x004A,   0 }
  }
};


SKC_sprite_pattern* brkabe07pat[2] = {
  &brkabe07sp00,
  &brkabe07sp10
};


static SKC_sprite_pattern brkabe07sp00 = {
  4,
  {
    { -32, 13, 0x0000, -16 },
    { -16, 13, 0x1800, -16 },
    {   0, 13, 0x0000, -16 },
    {  16, 13, 0x1800, -16 }
  }
};
static SKC_sprite_pattern brkabe07sp10 = {
  8,
  {
    { -32, 5, 0x0000, -16 },
    { -32, 5, 0x0004,   0 },
    { -16, 5, 0x1804, -16 },
    { -16, 5, 0x1800,   0 },
    {   0, 5, 0x0000, -16 },
    {   0, 5, 0x0004,   0 },
    {  16, 5, 0x1804, -16 },
    {  16, 5, 0x1800,   0 }
  }
};


SKC_sprite_pattern* brkabe09pat[2] = {
  &brkabe09sp00,
  &brkabe09sp01
};


static SKC_sprite_pattern brkabe09sp00 = {
  4,
  {
    { -32, 13, 0x006B, -16 },
    { -16, 13, 0x106B, -16 },
    {   0, 13, 0x006B, -16 },
    {  16, 13, 0x106B, -16 }
  }
};
static SKC_sprite_pattern brkabe09sp01 = {
  8,
  {
    { -32, 5, 0x006B, -16 },
    { -32, 5, 0x006F,   0 },
    { -16, 5, 0x106B, -16 },
    { -16, 5, 0x106F,   0 },
    {   0, 5, 0x006B, -16 },
    {   0, 5, 0x006F,   0 },
    {  16, 5, 0x106B, -16 },
    {  16, 5, 0x106F,   0 }
  }
};
