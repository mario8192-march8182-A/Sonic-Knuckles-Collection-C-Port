#include "falltree.h"
#include <string.h>
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../utils/stageno.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../hitchk.h"
static unsigned short falltreeinittbl[16];
static void falltreeinit(SKC_sprite_status* p_actwk);
static void falltreeset(SKC_sprite_status* p_actwk);
static void falltreemove(SKC_sprite_status* p_actwk);
static void falltreemove1(SKC_sprite_status* p_actwk);
static void falltreemovesub(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern falltreesp00;
static SKC_sprite_pattern falltreesp000;
static SKC_sprite_pattern falltreesp01;
static SKC_sprite_pattern falltreesp02;
static SKC_sprite_pattern falltreesp03;
static SKC_sprite_pattern falltreesp04;
static SKC_sprite_pattern falltreesp05;
static SKC_sprite_pattern falltreesp06;
static SKC_sprite_pattern falltreesp07;
static SKC_sprite_pattern falltreesp08;

extern sonic3_ram g_ram;


static unsigned short falltreeinittbl[16] = {
  1,
  3,
  7,
  0xF,
  0x1F,
  0x3F,
  0x7F,
  0xFF,
  0x1FF,
  0x3FF,
  0x7FF,
  0xFFF,
  0x1FFF,
  0x3FFF,
  0x7FFF,
  0xFFFF
};


void falltree(SKC_sprite_status* p_actwk) {
  if ((fp16_get_integer(p_actwk->xposi) == 0x26B0 || fp16_get_integer(p_actwk->xposi) == 0x2700)
      && g_ram.stage_triggers[0] != 0) {
    frameout(p_actwk);
  }
  else {
    falltreeinit(p_actwk);
  }
}


static void falltreeinit(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actfree.falltree.unknown32 = falltreeinittbl[p_actwk->u.obj.userflag & 0x0F];
  unsigned char shift = p_actwk->u.obj.userflag & 0x0F;
  if (shift < 3) {
    shift = 0;
  }
  p_actwk->u.obj.actfree.falltree.unknown34 = (p_actwk->u.obj.userflag >> 4 & 0x0F) << shift;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_ptr = &falltreeset;
  falltreeset(p_actwk);
}


static void falltreeset(SKC_sprite_status* p_actwk) {
  if (!(g_ram.gametimer + p_actwk->u.obj.actfree.falltree.unknown34 & p_actwk->u.obj.actfree.falltree.unknown32)) {
    SKC_actwkchk_result result = actwkchk2(p_actwk);
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &falltreemove;
      fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
      fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
      result.actwk_ptr->patbase = get_act(g_ram.stageno) != ACT_1 ? falltreepat : falltreepat1;
      memset(&result.actwk_ptr->sproffset, 0, sizeof(result.actwk_ptr->sproffset));
      result.actwk_ptr->sproffset.gfx = get_act(g_ram.stageno) != ACT_1 ? 0x2E9 : 0x3CF;
      result.actwk_ptr->sproffset.pl = 2;
      result.actwk_ptr->sprhs = 24;
      result.actwk_ptr->sprvs = 8;
      result.actwk_ptr->actflg.relative_coordinates = 1;
      result.actwk_ptr->sprpri = PRI_5;
      SKC_actwkchk_result result2 = actwkchk2(p_actwk);
      if (result2.actwk_ptr != 0) {
        result2.actwk_ptr->r_ptr = &falltreemove2;
        fp16_set_integer(&result2.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
        fp16_set_integer(&result2.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
        result2.actwk_ptr->patbase = get_act(g_ram.stageno) != ACT_1 ? falltreepat2 : falltreepat3;
        result2.actwk_ptr->sproffset.gfx = get_act(g_ram.stageno) != ACT_1 ? 0x2E9 : 0x3CF;
        result2.actwk_ptr->sproffset.pl = get_act(g_ram.stageno) != ACT_1 ? 3 : 2;
        result2.actwk_ptr->sprhs = 32;
        result2.actwk_ptr->sprvs = 16;
        result2.actwk_ptr->actflg.relative_coordinates = 1;
        result2.actwk_ptr->sprpri = PRI_4;
        result2.actwk_ptr->u.obj.ko = result.actwk_ptr - g_ram.actwk;
        result.actwk_ptr->u.obj.ko = result2.actwk_ptr - g_ram.actwk;
      }
    }
  }
  frameoutchk3(p_actwk);
}


static void falltreemove(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 1);
  if ((unsigned short)fp16_get_integer(p_actwk->yposi) >= (unsigned short)g_ram.waterposi) {
    p_actwk->r_ptr = &falltreemove1;
    p_actwk->pattim = 60;
  }
  falltreemovesub(p_actwk);
}


static void falltreemove1(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- == 0) {
    fp16_set_integer(&p_actwk->xposi, 0x7FF0);
    p_actwk->pattim = 3; // avoid wrap-around value
  }
  if (!(p_actwk->pattim & 3)) {
    p_actwk->u.obj.actfree.falltree.invisible = !p_actwk->u.obj.actfree.falltree.invisible;
  }
  falltreemovesub(p_actwk);
}


static void falltreemovesub(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { p_actwk->sprhs, 0, 8, fp16_get_integer(p_actwk->xposi) };
  SKC_hitchk_result result = ridechk(p_actwk, data);
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.sc1ahposit;
  if ((unsigned short)chunk_xposi <= 640) {
    if (!p_actwk->u.obj.actfree.falltree.invisible) {
      actionsub(p_actwk);
    }
  }
  else {
    if (p_actwk->u.obj.ko != 0) {
      SKC_sprite_status* p_relatedwk = &g_ram.actwk[p_actwk->u.obj.ko];
      frameout(p_relatedwk);
    }
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


void falltreemove2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_relatedwk = &g_ram.actwk[p_actwk->u.obj.ko];
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_relatedwk->xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_relatedwk->yposi));
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 3;
    ++p_actwk->patno;
    p_actwk->patno &= 3;
  }
  actionsub(p_actwk);
}


SKC_sprite_pattern* falltreepat[1] = {
  &falltreesp00
};


static SKC_sprite_pattern falltreesp00 = {
  2,
  {
    { -8, 9, 0x0021, -24 },
    { -8, 9, 0x0027, 0 }
  }
};


SKC_sprite_pattern* falltreepat1[1] = {
  &falltreesp000
};


static SKC_sprite_pattern falltreesp000 = {
  2,
  {
    { -8, 9, 0x0000, -24 },
    { -8, 9, 0x0006, 0 }
  }
};


SKC_sprite_pattern* falltreepat2[4] = {
  &falltreesp01,
  &falltreesp02,
  &falltreesp03,
  &falltreesp04
};


static SKC_sprite_pattern falltreesp01 = {
  4,
  {
    { -16, 7, 0x105C, -32 },
    { -16, 9, 0x0852, -16 },
    { -16, 7, 0x185C,  16 },
    {   0, 9, 0x0864, -16 }
  }
};
static SKC_sprite_pattern falltreesp02 = {
  4,
  {
    { -16, 7, 0x085C,  16 },
    {   0, 9, 0x1052,  -8 },
    { -16, 7, 0x005C, -32 },
    { -16, 9, 0x1064,  -8 }
  }
};
static SKC_sprite_pattern falltreesp03 = {
  4,
  {
    { -16, 7, 0x106A, -32 },
    { -16, 9, 0x0064, -16 },
    { -16, 7, 0x186A,  16 },
    {   0, 9, 0x0052, -16 }
  }
};
static SKC_sprite_pattern falltreesp04 = {
  4,
  {
    { -16, 7, 0x086A, 16 },
    { 0, 9, 0x1864, -8 },
    { -16, 7, 0x006A, -32 },
    { -16, 9, 0x1852, -8 }
  }
};



SKC_sprite_pattern* falltreepat3[4] = {
  &falltreesp05,
  &falltreesp06,
  &falltreesp07,
  &falltreesp08
};


static SKC_sprite_pattern falltreesp05 = {
  4,
  {
    { -16, 7, 0x000C, -32 },
    { -16, 9, 0x0014, -16 },
    { -16, 7, 0x080C, 16 },
    { 0, 9, 0x001A, -16 }
  }
};
static SKC_sprite_pattern falltreesp06 = {
  4,
  {
    { -16, 7, 0x180C, 16 },
    { 0, 9, 0x1814, -8 },
    { -16, 7, 0x100C, -32 },
    { -16, 9, 0x181A, -8 }
  }
};
static SKC_sprite_pattern falltreesp07 = {
  4,
  {
    { -16, 7, 0x0020, -32 },
    { -16, 9, 0x081A, -16 },
    { -16, 7, 0x0820,  16 },
    {   0, 9, 0x0814, -16 }
  }
};
static SKC_sprite_pattern falltreesp08 = {
  4,
  {
    { -16, 7, 0x1820, 16 },
    { 0, 9, 0x101A, -8 },
    { -16, 7, 0x1020, -32 },
    { -16, 9, 0x1014, -8 }
  }
};
