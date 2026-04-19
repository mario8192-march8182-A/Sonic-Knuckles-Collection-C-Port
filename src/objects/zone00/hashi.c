#include "hashi.h"
#include <stdbool.h>
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../etc.h"
#include "../../hitchk.h"
#include "../../sound.h"
#include "../common.h"
static void brhashiinit(SKC_sprite_status* p_actwk);
static void brhashiinit2(SKC_sprite_status* p_actwk);
static void brhashimove(SKC_sprite_status* p_actwk);
static void brhashimove2(SKC_sprite_status* p_actwk);
static void brhashimove3(SKC_sprite_status* p_actwk);
static void brhashimove4(SKC_sprite_status* p_actwk);
static void brhashimove5(SKC_sprite_status* p_actwk);
static void brhashidown(SKC_sprite_status* p_actwk);
static void brhashidown__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride);
static void brhashibreakgo(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_handler);
static SKC_sprite_pattern brhashisp00;
static SKC_sprite_pattern brhashisp02;
static SKC_sprite_pattern* brhashipat2[8];
static SKC_sprite_pattern brhashisp03;
static SKC_sprite_pattern brhashisp04;
static SKC_sprite_pattern brhashisp05;
static SKC_sprite_pattern brhashisp06;
static SKC_sprite_pattern brhashisp07;
static SKC_sprite_pattern brhashisp08;
static SKC_sprite_pattern brhashisp09;
static SKC_sprite_pattern brhashisp10;
static void evhashiinit(SKC_sprite_status* p_actwk);
static void evhashimove(SKC_sprite_status* p_actwk);
static void evhashimovesw(SKC_sprite_status* p_actwk);
static void evhashimove2(SKC_sprite_status* p_actwk);
static void evhashifoutchk(SKC_sprite_status* p_actwk);
static void evhashimove3(SKC_sprite_status* p_actwk);
static void evhashiposiset(SKC_sprite_status* p_actwk);
static void evhashimove4(SKC_sprite_status* p_actwk);
static void evhashimove5(SKC_sprite_status* p_actwk);
static void evhashibreakgo(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_handler);
static void evhashibreakgo__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_sprite_status_handler p_handler);
static SKC_sprite_pattern evhashisp00;
static SKC_sprite_pattern evhashisp01;

extern sonic3_ram g_ram;


void brhashi(SKC_sprite_status* p_actwk) {
  brhashiinit(p_actwk);
}


static void brhashiinit(SKC_sprite_status* p_actwk) {
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    brhashiinit2(p_actwk);
  }
  else {
    p_actwk->u.obj.actfree.brhashi.child_timer_init = p_actwk->u.obj.userflag;
    p_actwk->u.obj.actfree.brhashi.main_timer_init = p_actwk->u.obj.userflag + 48;
    p_actwk->u.obj.actfree.brhashi.child_timer_increase = 8;
    p_actwk->patbase = brhashipat;
    p_actwk->sproffset = 0x42E9;
    p_actwk->sprhs = 90;
    p_actwk->sprvs = 8;
    p_actwk->actflg.relative_coordinates = 1;
    p_actwk->sprpri = PRI_4;
    SKC_actwkchk_result result = actwkchk2(p_actwk);
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &brhashimove2;
      result.actwk_ptr->patbase = brhashipat;
      result.actwk_ptr->sproffset = 0x42E9;
      result.actwk_ptr->actflg.relative_coordinates = 1;
      result.actwk_ptr->sprhs = 90;
      result.actwk_ptr->sprvs = 8;
      result.actwk_ptr->sprpri = PRI_4;
      fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
      fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
      result.actwk_ptr->actflg.compound = 1;
      result.actwk_ptr->u.compound.child_cnt = 6;
      result.actwk_ptr->u.compound.children[0].patno = 1;
      short xposi = fp16_get_integer(p_actwk->xposi) - 75;
      short yposi = fp16_get_integer(p_actwk->yposi);

      for (int i = 0; i < result.actwk_ptr->u.compound.child_cnt; ++i) {
        result.actwk_ptr->u.compound.children[i].xposi = xposi;
        result.actwk_ptr->u.compound.children[i].yposi = yposi;
        xposi += 30;
      }

      result.actwk_ptr->u.compound.children[5].patno = 2;
      p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
    }
    p_actwk->r_ptr = &brhashimove;
    brhashimove(p_actwk);
  }
}


static void brhashiinit2(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actfree.brhashi.child_timer_init = p_actwk->u.obj.userflag & 0x7F;
  p_actwk->u.obj.actfree.brhashi.main_timer_init = (p_actwk->u.obj.userflag & 0x7F) + 48;
  p_actwk->u.obj.actfree.brhashi.child_timer_increase = 8;
  p_actwk->patbase = brhashipat2;
  p_actwk->sproffset = 0xC2E9;
  p_actwk->sprhs = 96;
  p_actwk->sprvs = 8;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &brhashimove2;
    result.actwk_ptr->patbase = brhashipat2;
    result.actwk_ptr->sproffset = 0xC2E9;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->sprhs = 96;
    result.actwk_ptr->sprvs = 8;
    result.actwk_ptr->sprpri = PRI_4;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
    result.actwk_ptr->actflg.compound = 1;
    result.actwk_ptr->u.compound.child_cnt = 6;
    result.actwk_ptr->u.compound.children[0].patno = 1;
    short xposi = fp16_get_integer(p_actwk->xposi) - 80;
    short yposi = fp16_get_integer(p_actwk->yposi);

    for (int i = 0; i < result.actwk_ptr->u.compound.child_cnt; ++i) {
      result.actwk_ptr->u.compound.children[i].xposi = xposi;
      result.actwk_ptr->u.compound.children[i].yposi = yposi;
      xposi += 32;
    }

    result.actwk_ptr->u.compound.children[5].patno = 2;
    p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
  }
  p_actwk->r_ptr = &brhashimove4;
  brhashimove4(p_actwk);
}


static void brhashimove(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->u.obj.timer = p_actwk->u.obj.actfree.brhashi.main_timer_init;
    p_actwk->r_ptr = &brhashidown;
    brhashibreakgo(p_actwk, &brhashimove3);
  }
  SKC_hitchk_data data = { p_actwk->sprhs, 0, p_actwk->sprvs, fp16_get_integer(p_actwk->xposi) };
  ridechk(p_actwk, data);
  frameoutchk3(p_actwk);
}


static void brhashimove2(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


static void brhashimove3(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    actionsub(p_actwk);
  }
  else {
    speedset(p_actwk);
    if (p_actwk->actflg.onscreen == 1) {
      actionsub(p_actwk);
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void brhashimove4(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffaa2 != 0) {
    p_actwk->u.obj.timer = p_actwk->u.obj.actfree.brhashi.main_timer_init;
    p_actwk->r_ptr = &brhashidown;
    brhashibreakgo(p_actwk, &brhashimove5);
  }
  SKC_hitchk_data data = { p_actwk->sprhs, 0, p_actwk->sprvs, fp16_get_integer(p_actwk->xposi) };
  ridechk(p_actwk, data);
  frameoutchk3(p_actwk);
}


static void brhashimove5(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      p_actwk->patno = 3;
    }
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = 3;
      ++p_actwk->patno;
      if (p_actwk->patno >= 8) {
        p_actwk->patno = 3;
      }
    }
    speedset(p_actwk);
    if (p_actwk->actflg.onscreen == 1) {
      actionsub(p_actwk);
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void brhashidown(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->r_ptr = &evhashimove5;
  }
  bool plride = p_actwk->u.obj.cddat.plride;
  brhashidown__sub(p_actwk, &g_ram.actwk[0], &plride);
  p_actwk->u.obj.cddat.plride = plride;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  brhashidown__sub(p_actwk, &g_ram.actwk[1], &pl2ride);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  frameoutchk3(p_actwk);
}


static void brhashidown__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride) {
  if (!*p_plride) return;

  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + p_actwk->sprhs;
  if (p_playerwk->u.play.cddat.jump == 0 && distance >= 0 && distance < p_actwk->sprhs * 2) {
    if (p_actwk->u.obj.cddat.right == 1) {
      distance = -distance + (short)p_actwk->sprhs * 2;
    }
    distance = distance / 32 * 8 + (short)p_actwk->u.obj.actfree.brhashi.child_timer_init;
    distance = (short)p_actwk->u.obj.actfree.brhashi.main_timer_init - distance;
    if (p_actwk->u.obj.timer > (unsigned short)distance) return;
  }
  *p_plride = false;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->mstno = 1;
}


static void brhashibreakgo(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_handler) {
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  p_childwk->actflg.compound = 0;
  SKC_sprite_status* p_new_actwk = p_childwk;

  for (int i = 0; i < p_childwk->u.compound.child_cnt; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
    }
    p_new_actwk->r_ptr = p_handler;
    p_new_actwk->patbase = p_childwk->patbase;
    p_new_actwk->actflg = p_childwk->actflg;
    p_new_actwk->sproffset = p_childwk->sproffset;
    p_new_actwk->sprpri = p_childwk->sprpri;
    p_new_actwk->sprhs = p_childwk->sprhs;
    p_new_actwk->sprvs = p_childwk->sprvs;
    fp16_set_integer(&p_new_actwk->xposi, p_childwk->u.compound.children[i].xposi);
    fp16_set_integer(&p_new_actwk->yposi, p_childwk->u.compound.children[i].yposi);
    p_new_actwk->patno = p_childwk->u.compound.children[i].patno;
    p_new_actwk->u.obj.timer = p_actwk->u.obj.actfree.brhashi.child_timer_init
                             + i * p_actwk->u.obj.actfree.brhashi.child_timer_increase;
  }

  p_childwk->xspeed = 0;
  p_childwk->yspeed = 0;
}


SKC_sprite_pattern* brhashipat[3] = {
  &brhashisp00,
  &brhashisp00,
  &brhashisp02
};


static SKC_sprite_pattern brhashisp00 = {
  1,
  {
    { -8, 13, 0x002D, -16 }
  }
};
static SKC_sprite_pattern brhashisp02 = {
  3,
  {
    { -8, 13, 0x002D, -16 },
    {  8,  8, 0x012D,  -8 },
    { 16,  4, 0x0130,   0 }
  }
};


static SKC_sprite_pattern* brhashipat2[8] = {
  &brhashisp03,
  &brhashisp04,
  &brhashisp05,
  &brhashisp06,
  &brhashisp07,
  &brhashisp08,
  &brhashisp09,
  &brhashisp10
};


static SKC_sprite_pattern brhashisp03 = {
  2,
  {
    { -8, 5, 0x0122, -16 },
    { -8, 5, 0x0122,   0 }
  }
};
static SKC_sprite_pattern brhashisp04 = {
  4,
  {
    { -8, 5, 0x0122, -16 },
    { -8, 5, 0x0122,   0 },
    {  8, 8, 0x092D, -16 },
    { 16, 4, 0x0930, -16 }
  }
};
static SKC_sprite_pattern brhashisp05 = {
  4,
  {
    { -8, 5, 0x0122, -16 },
    { -8, 5, 0x0122,   0 },
    {  8, 8, 0x012D,  -8 },
    { 16, 4, 0x0130,   0 }
  }
};
static SKC_sprite_pattern brhashisp06 = {
  2,
  {
    { -16, 6, 0x20EA, -16 },
    { -16, 6, 0x20EA,   0 }
  }
};
static SKC_sprite_pattern brhashisp07 = {
  2,
  {
    { -16, 6, 0x20F0, -16 },
    { -16, 6, 0x20F0,   0 }
  }
};
static SKC_sprite_pattern brhashisp08 = {
  2,
  {
    { -16, 6, 0x20F6, -16 },
    { -16, 6, 0x20F6,   0 }
  }
};
static SKC_sprite_pattern brhashisp09 = {
  2,
  {
    { -16, 6, 0x20FC, -16 },
    { -16, 6, 0x20FC,   0 }
  }
};
static SKC_sprite_pattern brhashisp10 = {
  2,
  {
    { -16, 6, 0x28F0, -16 },
    { -16, 6, 0x28F0,   0 }
  }
};


void evhashi(SKC_sprite_status* p_actwk) {
  evhashiinit(p_actwk);
}


static void evhashiinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = evhashipat;
  p_actwk->sproffset = 0xC2E9;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 96;
  p_actwk->u.obj.cddat.die = 1;
  p_actwk->u.obj.actfree.evhashi.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.actfree.evhashi.yposi_init = fp16_get_integer(p_actwk->yposi);
  short yoffset = p_actwk->u.obj.cddat.down == 0 ? -104 : 104;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->u.obj.actfree.evhashi.angle = (p_actwk->u.obj.cddat.down == 0 ? 192 : 64) << 16;
  yoffset = p_actwk->u.obj.cddat.down == 0 ? 240 : -240;
  p_actwk->u.obj.actfree.evhashi.angle_mod = p_actwk->u.obj.cddat.right == 0 ? 512 : -512;
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &evhashimove3;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->sprpri = p_actwk->sprpri;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->actflg.compound = 1;
    result.actwk_ptr->sprhs = 64;
    result.actwk_ptr->sprvs = 64;
    result.actwk_ptr->u.compound.child_cnt = 8;
    short yposi = p_actwk->u.obj.actfree.evhashi.yposi_init;

    for (int i = 0; i < result.actwk_ptr->u.compound.child_cnt; ++i) {
      yposi += yoffset;
      result.actwk_ptr->u.compound.children[i].xposi = p_actwk->u.obj.actfree.evhashi.xposi_init;
      result.actwk_ptr->u.compound.children[i].yposi = yposi;
      result.actwk_ptr->u.compound.children[i].patno = 1;
    }

    fp16_set_integer(&result.actwk_ptr->xposi, p_actwk->u.obj.actfree.evhashi.xposi_init);
    fp16_set_integer(&result.actwk_ptr->yposi, p_actwk->u.obj.actfree.evhashi.yposi_init);
    p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &evhashimove3;
      result.actwk_ptr->patbase = p_actwk->patbase;
      result.actwk_ptr->sproffset = p_actwk->sproffset;
      result.actwk_ptr->sprpri = p_actwk->sprpri;
      result.actwk_ptr->actflg.relative_coordinates = 1;
      result.actwk_ptr->actflg.compound = 1;
      result.actwk_ptr->sprhs = 64;
      result.actwk_ptr->sprvs = 64;
      result.actwk_ptr->u.compound.child_cnt = 4;

      for (int i = 0; i < result.actwk_ptr->u.compound.child_cnt; ++i) {
        yposi += yoffset;
        result.actwk_ptr->u.compound.children[i].xposi = p_actwk->u.obj.actfree.evhashi.xposi_init;
        result.actwk_ptr->u.compound.children[i].yposi = yposi;
        result.actwk_ptr->u.compound.children[i].patno = 1;
      }

      fp16_set_integer(&result.actwk_ptr->xposi, result.actwk_ptr->u.compound.children[0].xposi);
      fp16_set_integer(&result.actwk_ptr->yposi, result.actwk_ptr->u.compound.children[0].yposi);
      p_actwk->u.obj.actfree.evhashi.ko2 = result.actwk_ptr - g_ram.actwk;
    }
  }
  p_actwk->r_ptr = &evhashimove;
  evhashimove(p_actwk);
}


static void evhashimove(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffaa3 != 0 && !p_actwk->u.obj.actfree.evhashi.dropping) {
    p_actwk->u.obj.actfree.evhashi.dropping = true;
    soundset(86);
    short xoffset = p_actwk->u.obj.cddat.right == 0 ? 104 : -104;
    fp16_set_integer(&p_actwk->xposi, p_actwk->u.obj.actfree.evhashi.xposi_init + xoffset);
    fp16_set_integer(&p_actwk->yposi, p_actwk->u.obj.actfree.evhashi.yposi_init);
    p_actwk->sprhs = 96;
    p_actwk->sprvs = 8;
  }
  if (p_actwk->u.obj.actfree.evhashi.dropping) {
    if (p_actwk->u.obj.actfree.evhashi.angle >> 8 == 0 || p_actwk->u.obj.actfree.evhashi.angle >> 8 == 128) {
      p_actwk->u.obj.actfree.evhashi.dropping = false;
      soundset(86);
      p_actwk->r_ptr = &evhashimovesw;
    }
    else {
      p_actwk->u.obj.actfree.evhashi.angle = (short)p_actwk->u.obj.actfree.evhashi.angle
                                           + p_actwk->u.obj.actfree.evhashi.angle_mod;
    }
  }
  evhashiposiset(p_actwk);
  evhashimove2(p_actwk);
}


static void evhashimovesw(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffaa9 == 0) {
    evhashimove2(p_actwk);
  }
  else {
    p_actwk->r_ptr = &evhashimove5;
    p_actwk->u.obj.timer = 14;
    evhashibreakgo(p_actwk, &evhashimove4);
  }
}


static void evhashimove2(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 19, 96, 97, fp16_get_integer(p_actwk->xposi) };
  if (p_actwk->u.obj.actfree.evhashi.angle >> 8 == 0
      || (p_actwk->u.obj.actfree.evhashi.angle >> 8 != 64 && p_actwk->u.obj.actfree.evhashi.angle >> 8 != 192)) {
    data.sprhs = 107;
    data.sprvs_air = 8;
    data.sprvs_ground = 8;
  }
  hitchk_skip_onscreen(p_actwk, data);
  evhashifoutchk(p_actwk);
}


static void evhashifoutchk(SKC_sprite_status* p_actwk) {
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->u.obj.ko != 0) {
      frameout(&g_ram.actwk[p_actwk->u.obj.ko]);
    }
    if (p_actwk->u.obj.actfree.evhashi.ko2 != 0) {
      frameout(&g_ram.actwk[p_actwk->u.obj.actfree.evhashi.ko2]);
    }
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index], 7);
    }
    frameout(p_actwk);
  }
}


static void evhashimove3(SKC_sprite_status* p_actwk) {
  actionsub(p_actwk);
}


static void evhashiposiset(SKC_sprite_status* p_actwk) {
  if (!p_actwk->u.obj.actfree.evhashi.dropping) return;

  short sin, cos;
  sinset(p_actwk->u.obj.actfree.evhashi.angle >> 8, &sin, &cos);
  long sin_l = sin * 0x1000;
  long cos_l = cos * 0x1000;
  long sin_wk = sin_l;
  long cos_wk = cos_l;
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_childwk->u.compound.child_cnt > 0) {
    for (int i = 0; i < p_childwk->u.compound.child_cnt; ++i) {
      p_childwk->u.compound.children[i].xposi = p_actwk->u.obj.actfree.evhashi.xposi_init + (cos_wk / 0x10000);
      p_childwk->u.compound.children[i].yposi = p_actwk->u.obj.actfree.evhashi.yposi_init + (sin_wk / 0x10000);
      sin_wk += sin_l;
      cos_wk += cos_l;
    }

    fp16_set_integer(&p_childwk->xposi, p_actwk->u.obj.actfree.evhashi.xposi_init);
    fp16_set_integer(&p_childwk->yposi, p_actwk->u.obj.actfree.evhashi.yposi_init);
    p_childwk = &g_ram.actwk[p_actwk->u.obj.actfree.evhashi.ko2];
    if (p_childwk->u.compound.child_cnt > 0) {
      for (int i = 0; i < p_childwk->u.compound.child_cnt; ++i) {
        p_childwk->u.compound.children[i].xposi = p_actwk->u.obj.actfree.evhashi.xposi_init + (cos_wk / 0x10000);
        p_childwk->u.compound.children[i].yposi = p_actwk->u.obj.actfree.evhashi.yposi_init + (sin_wk / 0x10000);
        sin_wk += sin_l;
        cos_wk += cos_l;
      }

      fp16_set_integer(&p_childwk->xposi, p_childwk->u.obj.actfree.evhashi.xposi_init);
      fp16_set_integer(&p_childwk->yposi, p_childwk->u.obj.actfree.evhashi.yposi_init);
    }
  }
}


static void evhashimove4(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    actionsub(p_actwk);
  }
  else {
    speedset(p_actwk);
    if (p_actwk->actflg.onscreen == 1) {
      actionsub(p_actwk);
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void evhashimove5(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
  }
  else {
    if (p_actwk->u.obj.cddat.plride == 1) {
      p_actwk->u.obj.cddat.plride = 0;
      g_ram.actwk[0].u.play.cddat.ride = 0;
      g_ram.actwk[0].u.play.cddat.jump = 1;
      g_ram.actwk[0].mstno = 27;
    }
    if (p_actwk->u.obj.cddat.pl2ride == 1) {
      p_actwk->u.obj.cddat.pl2ride = 0;
      g_ram.actwk[1].u.play.cddat.ride = 0;
      g_ram.actwk[1].u.play.cddat.jump = 1;
      g_ram.actwk[1].mstno = 27;
    }
    frameout(p_actwk);
  }
}


static void evhashibreakgo(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_handler) {
  if (p_actwk->u.obj.ko != 0) {
    evhashibreakgo__sub(p_actwk, &g_ram.actwk[p_actwk->u.obj.ko], p_handler);
  }
  if (p_actwk->u.obj.actfree.evhashi.ko2 != 0) {
    evhashibreakgo__sub(p_actwk, &g_ram.actwk[p_actwk->u.obj.actfree.evhashi.ko2], p_handler);
  }
}


static void evhashibreakgo__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_sprite_status_handler p_handler) {
  unsigned char tbl[16] = {
    8, 16, 12, 14, 6, 10, 4, 2, 8, 16, 12, 14, 6, 10, 4, 2
  };

  p_childwk->actflg.compound = 0;
  SKC_sprite_status* p_new_actwk = p_childwk;

  for (int i = 0; i < p_childwk->u.compound.child_cnt; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
    }
    p_new_actwk->r_ptr = p_handler;
    p_new_actwk->patbase = p_childwk->patbase;
    p_new_actwk->actflg = p_childwk->actflg;
    p_new_actwk->sproffset = p_childwk->sproffset;
    p_new_actwk->sprpri = p_childwk->sprpri;
    p_new_actwk->sprhs = p_childwk->sprhs;
    p_new_actwk->sprvs = p_childwk->sprvs;
    fp16_set_integer(&p_new_actwk->xposi, p_childwk->u.compound.children[i].xposi);
    fp16_set_integer(&p_new_actwk->yposi, p_childwk->u.compound.children[i].yposi);
    p_new_actwk->patno = p_childwk->u.compound.children[i].patno;
    p_new_actwk->u.obj.timer = tbl[i];
    SKC_actwkchk_result result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;
    result.actwk_ptr->r_ptr = &bakuhatu3;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_new_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_new_actwk->yposi));
    result.actwk_ptr->pattim = tbl[i];
  }

  p_childwk->xspeed = 0;
  p_childwk->yspeed = 0;
  soundset(131);
}


SKC_sprite_pattern* evhashipat[2] = {
  &evhashisp00,
  &evhashisp01
};


static SKC_sprite_pattern evhashisp00 = {
  0,
  {}
};
static SKC_sprite_pattern evhashisp01 = {
  1,
  {
    { -8, 5, 0x0122, -8 }
  }
};
