#include "togetree.h"
#include "../../types/actwkchkresult.h"
#include "../../types/hitchkdata.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../coli.h"
#include "../../constants.h"
#include "../../etc.h"
#include "../../hitchk.h"
static void togetreeinit(SKC_sprite_status* p_actwk);
static void togetreemove(SKC_sprite_status* p_actwk);
static void togetreemove2(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern togetreesp00;
static SKC_sprite_pattern togetreesp01;
static SKC_sprite_pattern togetreesp02;
static SKC_sprite_pattern togetreesp03;
static SKC_sprite_pattern togetreesp04;
static SKC_sprite_pattern togetreesp05;
static SKC_sprite_pattern togetreesp06;
static SKC_sprite_pattern togetreesp07;
static SKC_sprite_pattern togetreesp08;
static SKC_sprite_pattern togetreesp09;
static SKC_sprite_pattern togetreesp10;
static SKC_sprite_pattern togetreesp11;
static SKC_sprite_pattern togetreesp12;
static SKC_sprite_pattern togetreesp13;
static SKC_sprite_pattern togetreesp14;
static SKC_sprite_pattern togetreesp15;

extern sonic3_ram g_ram;


void togetree(SKC_sprite_status* p_actwk) {
  togetreeinit(p_actwk);
}


static void togetreeinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = togetreepat;
  p_actwk->sproffset = 0x42E9;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 8;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->u.obj.actfree.togetree.yposi_init = fp16_get_integer(p_actwk->yposi);
  p_actwk->u.obj.actfree.togetree.f64d_save = g_ram.DAT_08fff64d;
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &togetreemove2;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->colino = 0x9C;
    result.actwk_ptr->u.obj.ko = p_actwk - g_ram.actwk;
    p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
  }
  p_actwk->r_ptr = &togetreemove;
}


static void togetreemove(SKC_sprite_status* p_actwk) {
  signed char tbl[7] = {
    7, 8, 9, 10, 9, 8, -1
  };

  bool rideon = false;
  if (BIT_IS_SET(p_actwk->u.obj.actfree.togetree.bitfield, 7)) {
    rideon = true;
  }
  else if (p_actwk->u.obj.actfree.togetree.f64d_save != g_ram.DAT_08fff64d) {
    p_actwk->u.obj.actfree.togetree.f64d_save = g_ram.DAT_08fff64d;
    SET_BIT(p_actwk->u.obj.actfree.togetree.bitfield, 0);
    SET_BIT(p_actwk->u.obj.actfree.togetree.bitfield, 7);
    rideon = true;
  }
  else if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    rideon = true;
  }
  else if (p_actwk->u.obj.actfree.togetree.rotation != 0) {
    p_actwk->u.obj.actfree.togetree.rotation -= 4;
  }
  if (rideon) {
    if (!BIT_IS_SET(p_actwk->u.obj.actfree.togetree.bitfield, 0)
        && !BIT_IS_SET(p_actwk->u.obj.actfree.togetree.bitfield, 7)) {
      p_actwk->u.obj.actfree.togetree.patcnt_save = p_actwk->patcnt;
      p_actwk->patcnt = 0;
      p_actwk->pattim = 0;
      SET_BIT(p_actwk->u.obj.actfree.togetree.bitfield, 0);
    }
    if (p_actwk->u.obj.actfree.togetree.rotation != 64) {
      p_actwk->u.obj.actfree.togetree.rotation += 4;
    }
    else {
      CLEAR_BIT(p_actwk->u.obj.actfree.togetree.bitfield, 7);
    }
  }
  short sin, cos;
  sinset(p_actwk->u.obj.actfree.togetree.rotation, &sin, &cos);
  short yposi = sin / 32 + p_actwk->u.obj.actfree.togetree.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  if (BIT_IS_SET(p_actwk->u.obj.actfree.togetree.bitfield, 0)
      || BIT_IS_SET(p_actwk->u.obj.actfree.togetree.bitfield, 7)) {
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = 3;
      if (p_actwk->patno-- == 0) {
        p_actwk->patno = 15;
      }
      ++p_actwk->patcnt;
      if (p_actwk->patcnt >= 16) {
        p_actwk->patcnt = p_actwk->u.obj.actfree.togetree.patcnt_save;
        CLEAR_BIT(p_actwk->u.obj.actfree.togetree.bitfield, 0);
        CLEAR_BIT(p_actwk->u.obj.actfree.togetree.bitfield, 7);
      }
    }
  }
  else {
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = 23;
      ++p_actwk->patcnt;
      p_actwk->patno = tbl[p_actwk->patcnt];
      if (tbl[p_actwk->patcnt + 1] < 0) {
        p_actwk->patcnt = 0;
      }
    }
  }
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->u.obj.ko != 0) {
      frameout(&g_ram.actwk[p_actwk->u.obj.ko]);
    }
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


static void togetreemove2(SKC_sprite_status* p_actwk) {
  signed char tbl[16] = {
    -12, -12, 0, 0, 0, 0, 0,  12,
     12,  12, 0, 0, 0, 0, 0, -12
  };

  SKC_sprite_status* p_relatedwk = &g_ram.actwk[p_actwk->u.obj.ko];
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_relatedwk->xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_relatedwk->yposi));
  if (tbl[p_relatedwk->patno] != 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + tbl[p_relatedwk->patno]);
  }
  colibufferchk(p_actwk);
}


SKC_sprite_pattern* togetreepat[16] = {
  &togetreesp00,
  &togetreesp01,
  &togetreesp02,
  &togetreesp03,
  &togetreesp04,
  &togetreesp05,
  &togetreesp06,
  &togetreesp07,
  &togetreesp08,
  &togetreesp09,
  &togetreesp10,
  &togetreesp11,
  &togetreesp12,
  &togetreesp13,
  &togetreesp14,
  &togetreesp15
};


static SKC_sprite_pattern togetreesp00 = {
  5,
  {
    { -16, 0, 0x000B, -20 },
    { -16, 1, 0x000C,  -4 },
    { -13, 1, 0x000E,  12 },
    {  -8, 9, 0x0015, -24 },
    {  -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp01 = {
  5,
  {
    { -16, 1, 0x000C, -20 },
    { -13, 1, 0x000E,  -4 },
    { -10, 1, 0x0010,  12 },
    {  -8, 9, 0x0815,   0 },
    {  -8, 9, 0x081B, -24 }
  }
};
static SKC_sprite_pattern togetreesp02 = {
  5,
  {
    { -13, 1, 0x000E, -20 },
    { -10, 1, 0x0010,  -4 },
    {  -7, 1, 0x0012,  12 },
    {  -8, 9, 0x0015, -24 },
    {  -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp03 = {
  5,
  {
    { -10, 1, 0x0010, -20 },
    {  -7, 1, 0x0012,  -4 },
    {  -4, 0, 0x0014,  12 },
    {  -8, 9, 0x0815,   0 },
    {  -8, 9, 0x081B, -24 }
  }
};
static SKC_sprite_pattern togetreesp04 = {
  5,
  {
    { -7, 1, 0x0012, -20 },
    { -4, 0, 0x0014,  -4 },
    { -9, 1, 0x1012,  12 },
    { -8, 9, 0x0015, -24 },
    { -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp05 = {
  5,
  {
    { -4, 0, 0x0014, -20 },
    { -9, 1, 0x1012,  -4 },
    { -6, 1, 0x1010,  12 },
    { -8, 9, 0x0815,   0 },
    { -8, 9, 0x081B, -24 }
  }
};
static SKC_sprite_pattern togetreesp06 = {
  5,
  {
    { -9, 1, 0x1012, -20 },
    { -6, 1, 0x1010,  -4 },
    { -3, 1, 0x100E,  12 },
    { -8, 9, 0x0015, -24 },
    { -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp07 = {
  5,
  {
    { -6, 1, 0x1010, -20 },
    { -3, 1, 0x100E,  -4 },
    {  0, 1, 0x100C,  12 },
    { -8, 9, 0x0815,   0 },
    { -8, 9, 0x081B, -24 }
  }
};
static SKC_sprite_pattern togetreesp08 = {
  5,
  {
    { -3, 1, 0x100E, -20 },
    {  0, 1, 0x100C,  -4 },
    {  8, 0, 0x100B,  12 },
    { -8, 9, 0x0015, -24 },
    { -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp09 = {
  5,
  {
    {  0, 1, 0x100C, -20 },
    {  8, 0, 0x100B,  -4 },
    {  8, 0, 0x100A,  12 },
    { -8, 9, 0x0815,   0 },
    { -8, 9, 0x081B, -24 }
  }
};
static SKC_sprite_pattern togetreesp10 = {
  4,
  {
    {  8, 0, 0x100B, -20 },
    {  8, 0, 0x100A,  -4 },
    { -8, 9, 0x0015, -24 },
    { -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp11 = {
  3,
  {
    {  8, 0, 0x100A, -20 },
    { -8, 9, 0x0815,   0 },
    { -8, 9, 0x081B, -24 }
  }
};
static SKC_sprite_pattern togetreesp12 = {
  2,
  {
    { -8, 9, 0x0015, -24 },
    { -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp13 = {
  3,
  {
    { -16, 0, 0x000A,  12 },
    {  -8, 9, 0x0815,   0 },
    {  -8, 9, 0x081B, -24 }
  }
};
static SKC_sprite_pattern togetreesp14 = {
  4,
  {
    { -16, 0, 0x000A,  -4 },
    { -16, 0, 0x000B,  12 },
    {  -8, 9, 0x0015, -24 },
    {  -8, 9, 0x001B,   0 }
  }
};
static SKC_sprite_pattern togetreesp15 = {
  5,
  {
    { -16, 0, 0x000A, -20 },
    { -16, 0, 0x000B,  -4 },
    { -16, 1, 0x000C,  12 },
    {  -8, 9, 0x0815,   0 },
    {  -8, 9, 0x081B, -24 }
  }
};
