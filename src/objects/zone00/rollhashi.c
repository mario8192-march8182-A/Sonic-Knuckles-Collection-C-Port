#include "rollhashi.h"
#include <string.h>
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../hitchk.h"
#include "../../sound.h"
static void rollhashiinit(SKC_sprite_status* p_actwk);
static void rollhashimove(SKC_sprite_status* p_actwk);
static void rollhashimove2(SKC_sprite_status* p_actwk);
static void rollhashisub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk);
static signed char rollhashitbl[128];
static signed char rollhashitbl2[128];
static void ridechksub_ts(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_hitchk_data data);
static SKC_hitchk_coli ridechksub_ts__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush, bool* p_plride);
static void rideonchk_ts(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride);
static SKC_sprite_pattern rollhashisp00;
static SKC_sprite_pattern rollhashisp01;
static SKC_sprite_pattern rollhashisp02;
static SKC_sprite_pattern rollhashisp03;
static SKC_sprite_pattern rollhashisp04;
static SKC_sprite_pattern rollhashisp05;

extern sonic3_ram g_ram;


void rollhashi(SKC_sprite_status* p_actwk) {
  rollhashiinit(p_actwk);
}


static void rollhashiinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = rollhashipat;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x2E9;
  p_actwk->sproffset.pl = 2;
  p_actwk->sprhs = 128;
  p_actwk->sprvs = 4;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_actwk->u.obj.actfree.rollhashi.slope_heights_ptr = rollhashitbl;
  }
  else {
    p_actwk->u.obj.actfree.rollhashi.slope_heights_ptr = rollhashitbl2;
  }
  p_actwk->u.obj.actfree.rollhashi.patno_max = (p_actwk->u.obj.userflag & 0x0F) + 16;
  p_actwk->pattimm = p_actwk->u.obj.userflag >> 4 & 7;
  if (p_actwk->u.obj.cddat.right == 1) {
    --p_actwk->u.obj.actfree.rollhashi.patno_max;
  }
  p_actwk->u.obj.actfree.rollhashi.patno_chg = p_actwk->u.obj.cddat.right == 1 ? 1 : -1;
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &rollhashimove2;
    result.actwk_ptr->patbase = rollhashipat;
    memset(&result.actwk_ptr->sproffset, 0, sizeof(result.actwk_ptr->sproffset));
    result.actwk_ptr->sproffset.gfx = 0x2E9;
    result.actwk_ptr->sproffset.pl = 2;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->sprhs = 128;
    result.actwk_ptr->sprvs = 64;
    result.actwk_ptr->sprpri = PRI_4;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
    result.actwk_ptr->actflg.compound = 1;
    result.actwk_ptr->u.obj.compound.child_cnt = 8;
    short yposi = fp16_get_integer(p_actwk->yposi) + 32;
    short xposi = fp16_get_integer(p_actwk->xposi) - 112;
    signed char xoffset = 8;
    if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
      yposi -= 16;
      xoffset = 4;
    }
    unsigned char patno = 0;

    for (int i = 0; i < result.actwk_ptr->u.obj.compound.child_cnt; ++i) {
      result.actwk_ptr->u.obj.compound.children[i].xposi = xposi;
      result.actwk_ptr->u.obj.compound.children[i].yposi = yposi;
      result.actwk_ptr->u.obj.compound.children[i].patno = patno;
      patno += 2;
      yposi += 32;
      xposi -= 32;
    }

    p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
  }
  p_actwk->r_ptr = &rollhashimove;
  rollhashimove(p_actwk);
}


static void rollhashimove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  rollhashisub(p_actwk, p_childwk);
  SKC_hitchk_data data = { p_actwk->sprhs, 0, 0, fp16_get_integer(p_actwk->xposi) };
  ridechksub_ts(p_actwk, p_childwk, data);
  frameoutchk3(p_actwk);
}


static void rollhashimove2(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


static void rollhashisub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk) {
  if (p_actwk->pattim-- > 0) return;

  p_actwk->pattim = p_actwk->pattimm;
  if (p_actwk->u.obj.actfree.rollhashi.patno_chg >= 0) {
    for (int i = 0; i < p_childwk->u.obj.compound.child_cnt; ++i) {
      p_childwk->u.obj.compound.children[i].patno += p_actwk->u.obj.actfree.rollhashi.patno_chg;
      if (p_actwk->u.obj.actfree.rollhashi.patno_max <= p_childwk->u.obj.compound.children[i].patno) {
        p_childwk->u.obj.compound.children[i].patno = 0;
      }
    }

    if (p_childwk->actflg.onscreen == 1 && !(g_ram.gametimer + 3 & 7)) {
      soundset(76);
    }
  }
  else {
    for (int i = 0; i < p_childwk->u.obj.compound.child_cnt; ++i) {
      short patno = p_childwk->u.obj.compound.children[i].patno;
      patno += p_actwk->u.obj.actfree.rollhashi.patno_chg;
      if (patno < 0) {
        p_childwk->u.obj.compound.children[i].patno = p_actwk->u.obj.actfree.rollhashi.patno_max;
      }
      else {
        p_childwk->u.obj.compound.children[i].patno = patno & 0xFF;
      }
    }

    if (p_childwk->actflg.onscreen == 1 && !(g_ram.gametimer + 3 & 7)) {
      soundset(76);
    }
  }
}


static signed char rollhashitbl[128] = {
  -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28,
  -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20,
  -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
   -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
    4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
   12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
   20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,
   28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28
};


static signed char rollhashitbl2[128] = {
  -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12, -12,
   -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,  -8,
   -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,
   12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,  12,
   16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16
};


static void ridechksub_ts(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_hitchk_data data) {
  bool plpush = p_actwk->u.obj.cddat.plpush;
  bool plride = p_actwk->u.obj.cddat.plride;
  ridechksub_ts__sub(p_actwk, p_childwk, &g_ram.actwk[0], data, &plpush, &plride);
  p_actwk->u.obj.cddat.plpush = plpush;
  p_actwk->u.obj.cddat.plride = plride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  ridechksub_ts__sub(p_actwk, p_childwk, &g_ram.actwk[1], data, &pl2push, &pl2ride);
  p_actwk->u.obj.cddat.pl2push = pl2push;
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
}


static SKC_hitchk_coli ridechksub_ts__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush, bool* p_plride) {
  if (!*p_plpush) {
    rideonchk_ts(p_actwk, p_childwk, p_playerwk, data, p_plride);
  }
  else {
    short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
    if (p_playerwk->u.play.cddat.jump == 1
        || distance >= 0
        || distance >= data.sprhs * 2
        || p_childwk->u.obj.compound.children[distance / 32].patno < 5) {
      p_playerwk->u.play.cddat.ride = 0;
      p_playerwk->u.play.cddat.jump = 1;
    }
    else {
      ride_sloped_dai(p_actwk, p_playerwk, data.sprhs, data.xposi, p_actwk->u.obj.actfree.rollhashi.slope_heights_ptr);
    }
  }
  return HITCHK_COLI_NONE;
}


static void rideonchk_ts(SKC_sprite_status* p_actwk, SKC_sprite_status* p_childwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride) {
  if (p_playerwk->yspeed < 0) return;

  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if (distance >= 0 && distance < data.sprhs * 2) {
    short slope_pos = distance;
    if (p_actwk->actflg.hflip == 1) {
      slope_pos = -slope_pos - 1 + (short)data.sprhs;
    }
    short yposi = fp16_get_integer(p_actwk->yposi) - p_actwk->u.obj.actfree.rollhashi.slope_heights_ptr[slope_pos];
    distance = yposi - (p_playerwk->sprvsize + fp16_get_integer(p_playerwk->yposi) + 4);
    if (distance <= 0 && distance >= -16
        && p_playerwk->u.play.control_bitfield == 0 && p_playerwk->r_no < 6
        && p_childwk->u.obj.compound.children[distance / 32].patno >= 5) {
      yposi = fp16_get_integer(p_playerwk->yposi) + distance + 3;
      fp16_set_integer(&p_playerwk->yposi, yposi);
      set_ride(p_actwk, p_playerwk, p_plride);
    }
  }
}


SKC_sprite_pattern* rollhashipat[32] = {
  &rollhashisp04,
  &rollhashisp05,
  &rollhashisp00,
  &rollhashisp01,
  &rollhashisp02,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03,
  &rollhashisp03
};


static SKC_sprite_pattern rollhashisp00 = {
  2,
  {
    { -16, 7, 0x00D6, -16 },
    { -16, 7, 0x08D6,   0 }
  }
};
static SKC_sprite_pattern rollhashisp01 = {
  2,
  {
    { -12, 6, 0x00DE, -16 },
    { -12, 6, 0x08DE,   0 }
  }
};
static SKC_sprite_pattern rollhashisp02 = {
  2,
  {
    { -8, 5, 0x00E4, -16 },
    { -8, 5, 0x08E4,   0 }
  }
};
static SKC_sprite_pattern rollhashisp03 = {
  2,
  {
    { -4, 4, 0x00E8, -16 },
    { -4, 4, 0x08E8,   0 }
  }
};
static SKC_sprite_pattern rollhashisp04 = {
  2,
  {
    { -8, 5, 0x10E4, -16 },
    { -8, 5, 0x18E4,   0 }
  }
};
static SKC_sprite_pattern rollhashisp05 = {
  2,
  {
    { -12, 6, 0x10DE, -16 },
    { -12, 6, 0x18DE,   0 }
  }
};
