#include "switch.h"
#include "../types/hitchkdata.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../hitchk.h"
#include "../sound.h"
static void switchinit(SKC_sprite_status* p_actwk);
static void switchmove(SKC_sprite_status* p_actwk);
static void switchmove2(SKC_sprite_status* p_actwk);
static void vsswitch(SKC_sprite_status* p_actwk);
static void vsswitchinit(SKC_sprite_status* p_actwk);
static void vsswitchmove(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern switchsp00;
static SKC_sprite_pattern switchsp01;
static SKC_sprite_pattern switchsp02;
static SKC_sprite_pattern switch01sp00;
static SKC_sprite_pattern switch01sp01;
static SKC_sprite_pattern switch01sp02;
static SKC_sprite_pattern switch03sp00;
static SKC_sprite_pattern switch03sp01;
static SKC_sprite_pattern switch03sp02;
static SKC_sprite_pattern switch09sp00;
static SKC_sprite_pattern switch09sp01;
static SKC_sprite_pattern switch09sp02;
static SKC_sprite_pattern vsswitchsp00;
static SKC_sprite_pattern vsswitchsp01;
static SKC_sprite_pattern vsswitchsp02;

extern sonic3_ram g_ram;


void switch_(SKC_sprite_status* p_actwk) {
  switchinit(p_actwk);
}


static void switchinit(SKC_sprite_status* p_actwk) {
  if (g_ram.vs_flag != 0) {
    vsswitch(p_actwk);
  }
  else {
    switch (get_zone(g_ram.stageno)) {
      default:
        p_actwk->patbase = switchpat;
        p_actwk->sproffset = 0x0456;
        break;
      case HYDROCITY:
        p_actwk->patbase = switch01pat;
        p_actwk->sproffset = 0x2426;
        break;
      case MARBLE_GARDEN:
        p_actwk->patbase = switch03pat;
        p_actwk->sproffset = 0x441A;
        break;
      case FLYING_BATTERY:
        p_actwk->patbase = switchpat;
        p_actwk->sproffset = 0x0500;
        break;
      case LAVA_REEF:
        p_actwk->patbase = switch09pat;
        p_actwk->sproffset = get_act(g_ram.stageno) == ACT_1 ? 0x63A1 : 0x2429;
        break;
    }

    p_actwk->actflg.relative_coordinates = 1;
    p_actwk->sprhs = 16;
    p_actwk->sprvs = 8;
    p_actwk->sprpri = PRI_4;
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 4);
    p_actwk->r_ptr = !BIT_IS_SET(p_actwk->u.obj.userflag, 5) ? &switchmove : &switchmove2;
    p_actwk->r_ptr(p_actwk);
  }
}


static void switchmove(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 1) {
    SKC_hitchk_data data = { 27, 4, 5, fp16_get_integer(p_actwk->xposi) };
    hitchk(p_actwk, data);
    p_actwk->patno = 0;
    unsigned char bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 6) ? 0 : 7;
    if (p_actwk->u.obj.cddat.plride == 0 && p_actwk->u.obj.cddat.pl2ride == 0) {
      if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
        CLEAR_BIT(g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F], bit);
      }
    }
    else {
      if (g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F] == 0) {
        soundset(91);
      }
      SET_BIT(g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F], bit);
      p_actwk->patno = 1;
    }
  }
  frameoutchk(p_actwk);
}


static void switchmove2(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 1) {
    SKC_hitchk_data data = { 16, 0, 6, fp16_get_integer(p_actwk->xposi) };
    ridechk(p_actwk, data);
    p_actwk->patno = 0;
    unsigned char bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 6) ? 0 : 7;
    if (p_actwk->u.obj.cddat.plride == 0 && p_actwk->u.obj.cddat.pl2ride == 0) {
      if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
        CLEAR_BIT(g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F], bit);
      }
    }
    else {
      if (g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F] == 0) {
        soundset(91);
      }
      SET_BIT(g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F], bit);
      p_actwk->patno = 1;
    }
  }
  frameoutchk(p_actwk);
}


static void vsswitch(SKC_sprite_status* p_actwk) {
  vsswitchinit(p_actwk);
}


static void vsswitchinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = vsswitchpat;
  p_actwk->sproffset = 0x03AD;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 12;
  p_actwk->sprpri = PRI_4;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 4);
  p_actwk->r_ptr = &vsswitchmove;
  vsswitchmove(p_actwk);
}


static void vsswitchmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 19, 4, 5, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
  p_actwk->patno = 0;
  unsigned char bit = !BIT_IS_SET(p_actwk->u.obj.userflag, 6) ? 0 : 7;
  if (p_actwk->u.obj.cddat.plride == 0 && p_actwk->u.obj.cddat.pl2ride == 0) {
    if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
      CLEAR_BIT(g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F], bit);
    }
  }
  else {
    if (g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F] == 0) {
      soundset(91);
    }
    SET_BIT(g_ram.level_triggers[p_actwk->u.obj.userflag & 0x0F], bit);
    p_actwk->patno = 1;
  }
  actionsub(p_actwk);
}


SKC_sprite_pattern* switchpat[3] = {
  &switchsp00,
  &switchsp01,
  &switchsp02
};


static SKC_sprite_pattern switchsp00 = {
  2,
  {
    { -12, 12, 0x0000, -16 },
    {  -4,  4, 0x0004,  -8 }
  }
};
static SKC_sprite_pattern switchsp01 = {
  1,
  {
    { -4, 12, 0x0000, -16 }
  }
};
static SKC_sprite_pattern switchsp02 = {
  2,
  {
    { -8, 12, 0x0000, -16 },
    {  0,  4, 0x0004,  -8 }
  }
};


SKC_sprite_pattern* switch01pat[3] = {
  &switch01sp00,
  &switch01sp01,
  &switch01sp02
};


static SKC_sprite_pattern switch01sp00 = {
  2,
  {
    { -8, 5, 0x0000, -16 },
    { -8, 5, 0x0800,   0 }
  }
};
static SKC_sprite_pattern switch01sp01 = {
  2,
  {
    { -8, 5, 0x0004, -16 },
    { -8, 5, 0x0804,   0 }
  }
};
static SKC_sprite_pattern switch01sp02 = {
  2,
  {
    { -4, 5, 0x0000, -16 },
    { -4, 5, 0x0800,   0 }
  }
};


SKC_sprite_pattern* switch03pat[3] = {
  &switch03sp00,
  &switch03sp01,
  &switch03sp02
};


static SKC_sprite_pattern switch03sp00 = {
  2,
  {
    { -12, 5, 0x0000, -16 },
    { -12, 5, 0x0800,   0 }
  }
};
static SKC_sprite_pattern switch03sp01 = {
  2,
  {
    { -4, 4, 0x0004, -16 },
    { -4, 4, 0x0804,   0 }
  }
};
static SKC_sprite_pattern switch03sp02 = {
  2,
  {
    { -8, 5, 0x0000, -16 },
    { -8, 5, 0x0800,   0 }
  }
};


SKC_sprite_pattern* switch09pat[3] = {
  &switch09sp00,
  &switch09sp01,
  &switch09sp02
};


static SKC_sprite_pattern switch09sp00 = {
  2,
  {
    { -10, 5, 0x0000, -16 },
    { -10, 5, 0x0800,   0 }
  }
};
static SKC_sprite_pattern switch09sp01 = {
  2,
  {
    { -10, 5, 0x0004, -16 },
    { -10, 5, 0x0804,   0 }
  }
};
static SKC_sprite_pattern switch09sp02 = {
  2,
  {
    { -6, 5, 0x0000, -16 },
    { -6, 5, 0x0800,   0 }
  }
};


SKC_sprite_pattern* vsswitchpat[3] = {
  &vsswitchsp00,
  &vsswitchsp01,
  &vsswitchsp02
};


static SKC_sprite_pattern vsswitchsp00 = {
  1,
  {
    { -8, 8, 0x000D, -12 }
  }
};
static SKC_sprite_pattern vsswitchsp01 = {
  1,
  {
    { -8, 8, 0x0010, -12 }
  }
};
static SKC_sprite_pattern vsswitchsp02 = {
  1,
  {
    { -4, 8, 0x000D, -12 }
  }
};
