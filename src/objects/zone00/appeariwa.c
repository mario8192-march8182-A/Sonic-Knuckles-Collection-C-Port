#include "appeariwa.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../hitchk.h"
#include "../../sound.h"
static unsigned short appeariwainittbl[16];
static void appeariwainit(SKC_sprite_status* p_actwk);
static void appeariwamove(SKC_sprite_status* p_actwk);
static void appeariwamove2(SKC_sprite_status* p_actwk);
static signed char* appeariwachg[3];
static signed char appeariwachg0[3];
static signed char appeariwachg1[12];
static signed char appeariwachg2[11];
static SKC_sprite_pattern* appeariwapat2[4];
static SKC_sprite_pattern appeariwasp00;
static SKC_sprite_pattern appeariwasp01;
static SKC_sprite_pattern appeariwasp02;
static SKC_sprite_pattern appeariwasp03;
static SKC_sprite_pattern appeariwasp04;
static SKC_sprite_pattern appeariwasp05;
static SKC_sprite_pattern appeariwasp06;
static SKC_sprite_pattern appeariwasp07;
static SKC_sprite_pattern appeariwasp08;
static SKC_sprite_pattern appeariwasp09;

extern sonic3_ram g_ram;


static unsigned short appeariwainittbl[16] = {
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


void appeariwa(SKC_sprite_status* p_actwk) {
  appeariwainit(p_actwk);
}


static void appeariwainit(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actfree.appeariwa.mask = appeariwainittbl[p_actwk->u.obj.userflag & 0x0F];
  unsigned char shift = (p_actwk->u.obj.userflag & 0x0F) >= 3 ? (p_actwk->u.obj.userflag & 0x0F) - 3 : 0;
  p_actwk->u.obj.actfree.appeariwa.delay = ((p_actwk->u.obj.userflag & 0xF0) >> 4) << shift;
  p_actwk->patbase = appeariwapat;
  p_actwk->sproffset = 0x4001;
  p_actwk->sprhs = 32;
  p_actwk->sprvs = 24;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  unsigned short time = g_ram.gametimer + p_actwk->u.obj.actfree.appeariwa.delay;
  unsigned char pattim = time & p_actwk->u.obj.actfree.appeariwa.mask;
  if (pattim != 0) {
    pattim = pattim >= 200 ? pattim - 200 : 200 - pattim;
    p_actwk->pattim = pattim;
    p_actwk->patcnt = 0;
    p_actwk->mstno = 2;
    p_actwk->mstrestart = 2;
    p_actwk->patno = 5;
  }
  p_actwk->r_ptr = &appeariwamove;
  appeariwamove(p_actwk);
}


static void appeariwamove(SKC_sprite_status* p_actwk) {
  unsigned short time = g_ram.gametimer + p_actwk->u.obj.actfree.appeariwa.delay;
  unsigned char pattim = time & p_actwk->u.obj.actfree.appeariwa.mask;
  if (pattim == 0) {
    p_actwk->mstno = 0;
    p_actwk->u.obj.actfree.appeariwa.visible = false;
    if (p_actwk->actflg.onscreen == 1) {
      soundset(75);
    }
  }
  time_patchg(p_actwk, appeariwachg);
  if (p_actwk->patno == 5 && !p_actwk->u.obj.actfree.appeariwa.visible) {
    p_actwk->u.obj.actfree.appeariwa.visible = true;
    SKC_actwkchk_result result = actwkchk2(p_actwk);
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = appeariwamove2;
      fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
      fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
      result.actwk_ptr->patbase = appeariwapat2;
      result.actwk_ptr->sproffset = 0x62E9;
      result.actwk_ptr->sprhs = 40;
      result.actwk_ptr->sprvs = 32;
      result.actwk_ptr->actflg.relative_coordinates = 1;
      result.actwk_ptr->sprpri = PRI_4;
      result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    }
  }
  frameoutchk(p_actwk);
}


static void appeariwamove2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->patno == 3) {
    fp16_set_integer(&p_actwk->xposi, 0x7FF0);
  }
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 3;
    ++p_actwk->patno;
    p_actwk->patno &= 3;
  }
  SKC_hitchk_data data = { 43, 24, 25, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
  frameoutchk(p_actwk);
}


static signed char* appeariwachg[3] = {
  appeariwachg0,
  appeariwachg1,
  appeariwachg2
};


static signed char appeariwachg0[3] = { 0, 31, -1 };
static signed char appeariwachg1[12] = { 1, 1, 2, 1, 3, 1, 4, 1, 5, 127, 5, 63 };
static signed char appeariwachg2[11] = { 4, 3, 3, 2, 2, 1, 1, 1, -3, 0, -112 };


SKC_sprite_pattern* appeariwapat[6] = {
  &appeariwasp00,
  &appeariwasp01,
  &appeariwasp02,
  &appeariwasp03,
  &appeariwasp04,
  &appeariwasp05
};


static SKC_sprite_pattern* appeariwapat2[4] = {
  &appeariwasp06,
  &appeariwasp07,
  &appeariwasp08,
  &appeariwasp09
};


static SKC_sprite_pattern appeariwasp00 = {
  0,
  {}
};
static SKC_sprite_pattern appeariwasp01 = {
  2,
  {
    { -24, 5, 0x031D, -16 },
    { -24, 5, 0x0B1D,   0 }
  }
};
static SKC_sprite_pattern appeariwasp02 = {
  5,
  {
    { -24, 5, 0x0B1D, -24 },
    { -24, 5, 0x031D,  -8 },
    { -24, 5, 0x031D,   8 },
    {  -8, 5, 0x131D, -16 },
    {  -8, 5, 0x131D,   0 }
  }
};
static SKC_sprite_pattern appeariwasp03 = {
  4,
  {
    { -24, 7, 0x0321, -32 },
    { -24, 7, 0x0B21, -16 },
    { -24, 7, 0x0321,   0 },
    { -24, 7, 0x0B21,  16 }
  }
};
static SKC_sprite_pattern appeariwasp04 = {
  7,
  {
    { -24, 13, 0x002A, -32 },
    { -24, 13, 0x002A,   0 },
    {  -8, 13, 0x0329, -32 },
    {  -8, 13, 0x0B29,   0 },
    {   8,  5, 0x1B1D, -24 },
    {   8,  5, 0x0B1D,  -8 },
    {   8,  5, 0x131D,   8 }
  }
};
static SKC_sprite_pattern appeariwasp05 = {
  6,
  {
    { -24, 13, 0x002A, -32 },
    {  -8, 13, 0x1016, -32 },
    {   8, 13, 0x0032, -32 },
    { -24, 13, 0x002A,   0 },
    {  -8, 13, 0x1016,   0 },
    {   8, 13, 0x0832,   0 }
  }
};
static SKC_sprite_pattern appeariwasp06 = {
  10,
  {
    { -40, 10, 0x0049, -48 },
    { -32,  9, 0x0052, -24 },
    { -32,  9, 0x0852,   0 },
    { -40, 10, 0x0849,  24 },
    { -16,  5, 0x0058, -48 },
    { -16,  5, 0x0858,  32 },
    {   0,  7, 0x005C, -40 },
    {   0,  7, 0x085C,  24 },
    {  16,  9, 0x0064, -24 },
    {  16,  9, 0x0864,   0 }
  }
};
static SKC_sprite_pattern appeariwasp07 = {
  8,
  {
    { -32, 7, 0x105C, -40 },
    { -32, 9, 0x0864, -24 },
    { -32, 9, 0x0064,   0 },
    { -32, 7, 0x185C,  24 },
    {   0, 7, 0x006A, -40 },
    {   0, 7, 0x086A,  24 },
    {  16, 9, 0x1064, -24 },
    {  16, 9, 0x1864,   0 }
  }
};
static SKC_sprite_pattern appeariwasp08 = {
  8,
  {
    { -32, 7, 0x106A, -40 },
    { -32, 9, 0x0064, -24 },
    { -32, 9, 0x0864,   0 },
    { -32, 7, 0x186A,  24 },
    {   0, 7, 0x005C, -40 },
    {   0, 7, 0x085C,  24 },
    {  16, 9, 0x0052, -24 },
    {  16, 9, 0x0852,   0 }
  }
};
static SKC_sprite_pattern appeariwasp09 = {
  8,
  {
    { -32, 7, 0x105C, -40 },
    { -32, 9, 0x1852, -24 },
    { -32, 9, 0x1052,   0 },
    { -32, 7, 0x185C,  24 },
    {   0, 7, 0x006A, -40 },
    {   0, 7, 0x086A,  24 },
    {  16, 9, 0x0852, -24 },
    {  16, 9, 0x0052,   0 }
  }
};
