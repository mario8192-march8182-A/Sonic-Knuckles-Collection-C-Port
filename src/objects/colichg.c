#include "colichg.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../action.h"
#include "../constants.h"
static void colichgmovev(SKC_sprite_status* p_actwk);
static void vscolichgmovev(SKC_sprite_status* p_actwk);
static void colichgmovevsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_left);
static void colichgmoveh(SKC_sprite_status* p_actwk);
static void vscolichgmoveh(SKC_sprite_status* p_actwk);
static void colichgmovehsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_up);
static SKC_sprite_pattern colichgsp00;
static SKC_sprite_pattern colichgsp01;
static SKC_sprite_pattern colichgsp02;
static SKC_sprite_pattern colichgsp04;
static SKC_sprite_pattern colichgsp05;
static SKC_sprite_pattern colichgsp06;

extern sonic3_ram g_ram;


void colichg(SKC_sprite_status* p_actwk) {
  unsigned short sizetbl[4] = {
    32, 64, 128, 256
  };

  p_actwk->patbase = colichgpat;
  p_actwk->sproffset = g_ram.vs_flag == 0 ? 0x26BC : 0x63D2;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 64;
  p_actwk->sprvs = 64;
  p_actwk->sprpri = PRI_5;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 2)) {
    p_actwk->patno = p_actwk->u.obj.userflag & 7;
    p_actwk->u.obj.actfree.colichg.hvsize = sizetbl[p_actwk->u.obj.userflag & 3];
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(g_ram.actwk[0].yposi)) {
      p_actwk->u.obj.actfree.colichg.plupleft = true;
    }
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(g_ram.actwk[1].yposi)) {
      p_actwk->u.obj.actfree.colichg.pl2upleft = true;
    }
    p_actwk->r_ptr = g_ram.vs_flag == 0 ? &colichgmoveh : vscolichgmoveh;
  }
  else {
    p_actwk->patno = p_actwk->u.obj.userflag & 3;
    p_actwk->u.obj.actfree.colichg.hvsize = sizetbl[p_actwk->u.obj.userflag & 3];
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) < (unsigned short)fp16_get_integer(g_ram.actwk[0].xposi)) {
      p_actwk->u.obj.actfree.colichg.plupleft = true;
    }
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) < (unsigned short)fp16_get_integer(g_ram.actwk[1].xposi)) {
      p_actwk->u.obj.actfree.colichg.pl2upleft = true;
    }
    p_actwk->r_ptr = g_ram.vs_flag == 0 ? &colichgmovev : &vscolichgmovev;
  }
  p_actwk->r_ptr(p_actwk);
}


static void colichgmovev(SKC_sprite_status* p_actwk) {
  if (g_ram.editmode == 0) {
    colichgmovevsub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.colichg.plupleft);
    colichgmovevsub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.colichg.pl2upleft);
    frameoutchk3(p_actwk);
  }
  else {
    frameoutchk(p_actwk);
  }
}


static void vscolichgmovev(SKC_sprite_status* p_actwk) {
  colichgmovevsub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.colichg.plupleft);
  colichgmovevsub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.colichg.pl2upleft);
  if (g_ram.debugflag == 0) {
    colichgmovevsub(p_actwk, &g_ram.actwk[94], &p_actwk->u.obj.actfree.colichg.editupleft);
  }
  else {
    colichgmovevsub(p_actwk, &g_ram.actwk[94], &p_actwk->u.obj.actfree.colichg.editupleft);
    actionsub(p_actwk);
  }
}


static void colichgmovevsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_left) {
  short yposi_above = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->u.obj.actfree.colichg.hvsize;
  short yposi_below = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->u.obj.actfree.colichg.hvsize;
  short distance = abs(fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi));
  if (!*p_left) {
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) <= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      *p_left = true;
      if ((unsigned short)fp16_get_integer(p_playerwk->yposi) >= (unsigned short)yposi_above
          && (unsigned short)fp16_get_integer(p_playerwk->yposi) < (unsigned short)yposi_below
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) || p_playerwk->u.play.cddat.jump == 0)
          && distance < 64) {
        if (p_actwk->actflg.hflip == 0) {
          p_playerwk->u.play.top_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 3) ? 12 : 14;
          p_playerwk->u.play.lrb_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 3) ? 13 : 15;
        }
        if (!BIT_IS_SET(p_actwk->u.obj.userflag, 5)) {
          CLEAR_BIT(p_playerwk->sproffset, 15);
        }
        else {
          SET_BIT(p_playerwk->sproffset, 15);
        }
      }
    }
  }
  else {
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) > (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      *p_left = false;
      if ((unsigned short)fp16_get_integer(p_playerwk->yposi) >= (unsigned short)yposi_above
          && (unsigned short)fp16_get_integer(p_playerwk->yposi) < (unsigned short)yposi_below
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) || p_playerwk->u.play.cddat.jump == 0)
          && distance < 64) {
        if (p_actwk->actflg.hflip == 0) {
          p_playerwk->u.play.top_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 4) ? 12 : 14;
          p_playerwk->u.play.lrb_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 4) ? 13 : 15;
        }
        if (!BIT_IS_SET(p_actwk->u.obj.userflag, 6)) {
          CLEAR_BIT(p_playerwk->sproffset, 15);
        }
        else {
          SET_BIT(p_playerwk->sproffset, 15);
        }
      }
    }
  }
}


static void colichgmoveh(SKC_sprite_status* p_actwk) {
  if (g_ram.editmode == 0) {
    colichgmovehsub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.colichg.plupleft);
    colichgmovehsub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.colichg.pl2upleft);
    frameoutchk3(p_actwk);
  }
  else {
    frameoutchk(p_actwk);
  }
}


static void vscolichgmoveh(SKC_sprite_status* p_actwk) {
  colichgmovehsub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.colichg.plupleft);
  colichgmovehsub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.colichg.pl2upleft);
  if (g_ram.debugflag == 0) {
    colichgmovehsub(p_actwk, &g_ram.actwk[94], &p_actwk->u.obj.actfree.colichg.editupleft);
  }
  else {
    colichgmovehsub(p_actwk, &g_ram.actwk[94], &p_actwk->u.obj.actfree.colichg.editupleft);
    actionsub(p_actwk);
  }
}


static void colichgmovehsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_up) {
  short xposi_left = fp16_get_integer(p_actwk->xposi) - p_actwk->u.obj.actfree.colichg.hvsize;
  short xposi_right = fp16_get_integer(p_actwk->xposi) + p_actwk->u.obj.actfree.colichg.hvsize;
  short distance = abs(fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi));
  if (!*p_up) {
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) <= (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
      *p_up = true;
      if ((unsigned short)fp16_get_integer(p_playerwk->xposi) >= (unsigned short)xposi_left
          && (unsigned short)fp16_get_integer(p_playerwk->xposi) < (unsigned short)xposi_right
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) || p_playerwk->u.play.cddat.jump == 0)
          && distance < 64) {
        if (p_actwk->actflg.hflip == 0) {
          p_playerwk->u.play.top_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 3) ? 12 : 14;
          p_playerwk->u.play.lrb_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 3) ? 13 : 15;
        }
        if (!BIT_IS_SET(p_actwk->u.obj.userflag, 5)) {
          CLEAR_BIT(p_playerwk->sproffset, 15);
        }
        else {
          SET_BIT(p_playerwk->sproffset, 15);
        }
      }
    }
  }
  else {
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) > (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
      *p_up = false;
      if ((unsigned short)fp16_get_integer(p_playerwk->xposi) >= (unsigned short)xposi_left
          && (unsigned short)fp16_get_integer(p_playerwk->xposi) < (unsigned short)xposi_right
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) || p_playerwk->u.play.cddat.jump == 0)
          && distance < 64) {
        if (p_actwk->actflg.hflip == 0) {
          p_playerwk->u.play.top_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 4) ? 12 : 14;
          p_playerwk->u.play.lrb_solid_bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 4) ? 13 : 15;
        }
        if (!BIT_IS_SET(p_actwk->u.obj.userflag, 6)) {
          CLEAR_BIT(p_playerwk->sproffset, 15);
        }
        else {
          SET_BIT(p_playerwk->sproffset, 15);
        }
      }
    }
  }
}


SKC_sprite_pattern* colichgpat[8] = {
  &colichgsp00,
  &colichgsp01,
  &colichgsp02,
  &colichgsp02,
  &colichgsp04,
  &colichgsp05,
  &colichgsp06,
  &colichgsp06
};


static SKC_sprite_pattern colichgsp00 = {
  4,
  {
    { -32, 5, 0x0000, -8 },
    { -16, 5, 0x0000, -8 },
    {   0, 5, 0x0000, -8 },
    {  16, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern colichgsp01 = {
  4,
  {
    { -64, 5, 0x0000, -8 },
    { -32, 5, 0x0000, -8 },
    {   0, 5, 0x0000, -8 },
    {  48, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern colichgsp02 = {
  4,
  {
    { -128, 5, 0x0000, -8 },
    {  -32, 5, 0x0000, -8 },
    {    0, 5, 0x0000, -8 },
    {  112, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern colichgsp04 = {
  4,
  {
    { -8, 5, 0x0000, -32 },
    { -8, 5, 0x0000, -16 },
    { -8, 5, 0x0000,   0 },
    { -8, 5, 0x0000,  16 }
  }
};
static SKC_sprite_pattern colichgsp05 = {
  4,
  {
    { -8, 5, 0x0000, -64 },
    { -8, 5, 0x0000, -32 },
    { -8, 5, 0x0000,   0 },
    { -8, 5, 0x0000,  48 }
  }
};
static SKC_sprite_pattern colichgsp06 = {
  4,
  {
    { -8, 5, 0x0000, -128 },
    { -8, 5, 0x0000,  -32 },
    { -8, 5, 0x0000,   0 },
    { -8, 5, 0x0000,  112 }
  }
};
