#include "mask.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../coli.h"
#include "../../hitchk.h"
#include "../../sound.h"
#include "../common.h"
static void maskinit(SKC_sprite_status* p_actwk);
static void maskmove(SKC_sprite_status* p_actwk);
static void maskarrow(SKC_sprite_status* p_actwk);
static void maskarrowmove(SKC_sprite_status* p_actwk);
static void maskflash(SKC_sprite_status* p_actwk);
static signed char* maskchg[3];
static signed char maskchg0[3];
static signed char maskchg1[14];
static signed char maskchg2[8];
static SKC_sprite_pattern masksp00;
static SKC_sprite_pattern masksp01;
static SKC_sprite_pattern masksp02;
static SKC_sprite_pattern masksp03;
static SKC_sprite_pattern masksp04;
static SKC_sprite_pattern masksp05;
static SKC_sprite_pattern masksp06;
static SKC_sprite_pattern masksp07;
static void moveyukamove(SKC_sprite_status* p_actwk);
static void moveyukamovey(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern moveyukasp00;
static SKC_sprite_pattern moveyukasp01;

extern sonic3_ram g_ram;


void mask(SKC_sprite_status* p_actwk) {
  maskinit(p_actwk);
}


static void maskinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = maskpat;
  p_actwk->sproffset = 0xA3FF;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 56;
  p_actwk->patno = 2;
  p_actwk->colino = 0x17;
  p_actwk->colicnt = 3;
  p_actwk->actflg.compound = 1;
  p_actwk->u.obj.compound.child_cnt = 1;
  p_actwk->u.obj.compound.children[0].xposi = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.compound.children[0].yposi = fp16_get_integer(p_actwk->yposi);
  p_actwk->u.obj.compound.children[0].patno = 6;
  if (p_actwk->u.obj.cddat.right == 0) {
    p_actwk->u.obj.actfree.mask.xoffset = 192;
  }
  if (g_ram.stage_triggers[p_actwk->u.obj.userflag & 0x0F] != 0) {
    p_actwk->u.obj.actfree.mask.inactive = true;
    p_actwk->patno = 0;
    p_actwk->colino = 0;
  }
  p_actwk->r_ptr = &maskmove;
  maskmove(p_actwk);
}


static void maskmove(SKC_sprite_status* p_actwk) {
  if (!p_actwk->u.obj.actfree.mask.inactive) {
    short distance = fp16_get_integer(g_ram.actwk[0].xposi) - fp16_get_integer(p_actwk->xposi);
    distance += p_actwk->u.obj.actfree.mask.xoffset;
    if ((unsigned short)distance < 192) {
      distance = fp16_get_integer(g_ram.actwk[0].yposi) - fp16_get_integer(p_actwk->yposi);
      distance += 128;
      if ((unsigned short)distance < 192 && p_actwk->mstno == 0) {
        p_actwk->mstno = 1;
      }
    }
    if (p_actwk->colino == 0) {
      if (p_actwk->u.obj.timer != 0) {
        --p_actwk->u.obj.timer;
        if (p_actwk->u.obj.timer == 0) {
          p_actwk->colino = 0x17;
        }
      }
      else {
        p_actwk->u.obj.timer = 60;
        SKC_actwkchk_result result = actwkchk2(p_actwk);
        if (result.actwk_ptr != 0) {
          result.actwk_ptr->r_ptr = p_actwk->colicnt != 0 ? &maskflash : &bakuhatu;
          if (p_actwk->colicnt == 0) {
            result.actwk_ptr->sproffset = 0x8000;
            result.actwk_ptr->r_no = 2;
            p_actwk->u.obj.actfree.mask.inactive = true;
            p_actwk->patno = 0;
            g_ram.stage_triggers[p_actwk->u.obj.userflag & 0x0F] = 1;
          }
          fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
          fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
          result.actwk_ptr->actflg = p_actwk->actflg;
          result.actwk_ptr->actflg.compound = 0;
          result.actwk_ptr->u.obj.cddat = p_actwk->u.obj.cddat;
          result.actwk_ptr->patbase = p_actwk->patbase;
          result.actwk_ptr->sproffset = p_actwk->sproffset;
          result.actwk_ptr->sprpri = PRI_4;
          result.actwk_ptr->sprhs = 8;
          result.actwk_ptr->sprvs = 8;
          result.actwk_ptr->mstno = 2;
        }
        soundset(110);
      }
    }
    patchg(p_actwk, maskchg);
    if (p_actwk->r_no != 0) {
      p_actwk->r_no = 0;
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &maskarrow;
        short xposi = fp16_get_integer(p_actwk->xposi) + 16;
        fp16_set_integer(&result.actwk_ptr->xposi, xposi);
        fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(result.actwk_ptr->xposi) + 16);
        short yposi = fp16_get_integer(p_actwk->yposi) + 32;
        fp16_set_integer(&result.actwk_ptr->yposi, yposi);
        result.actwk_ptr->actflg = p_actwk->actflg;
        result.actwk_ptr->actflg.compound = 0;
        result.actwk_ptr->patbase = p_actwk->patbase;
        result.actwk_ptr->sproffset = p_actwk->sproffset;
        CLEAR_BIT(result.actwk_ptr->sproffset, 15);
        result.actwk_ptr->sprpri = PRI_6;
        result.actwk_ptr->sprhs = 16;
        result.actwk_ptr->sprvs = 4;
        result.actwk_ptr->colino = 0x9B;
        result.actwk_ptr->xspeed = p_actwk->u.obj.cddat.right == 0 ? -0x400 : 0x400;
        if (p_actwk->u.obj.cddat.right == 1) {
          fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi) - 32);
        }
        soundset(103);
      }
    }
  }
  frameoutchkc(p_actwk);
}


static void maskarrow(SKC_sprite_status* p_actwk) {
  maskarrowmove(p_actwk);
}


static void maskarrowmove(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 1) {
    speedset2(p_actwk);
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void maskflash(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, maskchg);
  frameoutchk(p_actwk);
}


static signed char* maskchg[3] = {
  maskchg0,
  maskchg1,
  maskchg2
};


static signed char maskchg0[3] = { 127, 2, -1 };
static signed char maskchg1[14] = { 7, 3, 4, 3, 2, 2, 2, 1, -4, 1, 1, 1, -3, 0 };
static signed char maskchg2[8] = { 1, 5, 7, 5, 7, 5, 7, -5 };


SKC_sprite_pattern* maskpat[8] = {
  &masksp00,
  &masksp01,
  &masksp02,
  &masksp03,
  &masksp04,
  &masksp05,
  &masksp06,
  &masksp07
};


static SKC_sprite_pattern masksp00 = {
  1,
  {
    { -4, 12, 0xE04E, -16 },
  }
};
static SKC_sprite_pattern masksp01 = {
  1,
  {
    { -8, 1, 0x0044, -8 },
  }
};
static SKC_sprite_pattern masksp02 = {
  1,
  {
    { -8, 1, 0x0046, -8 },
  }
};
static SKC_sprite_pattern masksp03 = {
  1,
  {
    { -8, 1, 0x0048, -8 },
  }
};
static SKC_sprite_pattern masksp04 = {
  1,
  {
    { -8, 1, 0x004A, -8 },
  }
};
static SKC_sprite_pattern masksp05 = {
  1,
  {
    { -8, 1, 0x004C, -8 },
  }
};
static SKC_sprite_pattern masksp06 = {
  3,
  {
    { -24,  9, 0x2026, -8 },
    {  -8, 11, 0x002C, -8 },
    {  24, 11, 0x0038, -8 },
  }
};
static SKC_sprite_pattern masksp07 = {
  0,
  {}
};


void moveyuka(SKC_sprite_status* p_actwk) {
  struct {
    unsigned char sprhs;
    unsigned char sprvs;
    unsigned char patno;
    unsigned char timer_init;
  }
  moveyukatbl[3] = {
    64, 30, 0, 64,
    32, 64, 1, 64,
    32, 64, 1, 64
  };

  unsigned char index = (p_actwk->u.obj.userflag & 0xF0) >> 4;
  p_actwk->sprhs = moveyukatbl[index].sprhs;
  p_actwk->sprvs = moveyukatbl[index].sprvs;
  p_actwk->patno = moveyukatbl[index].patno;
  p_actwk->u.obj.timer = moveyukatbl[index].timer_init;
  p_actwk->u.obj.actfree.moveyuka.yoffset = index;
  p_actwk->patbase = moveyukapat;
  p_actwk->sproffset = 0x4001;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->u.obj.actfree.moveyuka.xposi_init = fp16_get_integer(p_actwk->xposi);
  if (index != 0) {
    if (g_ram.stage_triggers[p_actwk->u.obj.userflag & 0x0F] != 0) {
      short yoffset = p_actwk->u.obj.actfree.moveyuka.yoffset;
      if (p_actwk->u.obj.cddat.right == 1) {
        yoffset = -yoffset;
      }

      do {
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
        --p_actwk->u.obj.timer;
      }
      while (p_actwk->u.obj.timer != 0);

      p_actwk->u.obj.actfree.moveyuka.side = -1;
    }
    p_actwk->r_ptr = &moveyukamovey;
  }
  else {
    p_actwk->r_ptr = &moveyukamove;
  }
  p_actwk->r_ptr(p_actwk);
}


static void moveyukamove(SKC_sprite_status* p_actwk) {
  if (g_ram.stage_triggers[p_actwk->u.obj.userflag & 0x0F] != 0) {
    short xoffset = p_actwk->u.obj.cddat.right == 0 ? 2 : -2;
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
    g_ram.scr_shake_flg = 0xFFFF;
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      fp16_set_integer(&p_actwk->xposi, 0x7F00);
      p_actwk->u.obj.actfree.moveyuka.xposi_init = 0x7F00;
      p_actwk->u.obj.flagwork_index = 0;
      g_ram.scr_shake_flg = 0;
    }
  }
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.moveyuka.xposi_init);
}


static void moveyukamovey(SKC_sprite_status* p_actwk) {
  bool open = false;
  if (g_ram.stage_triggers[p_actwk->u.obj.userflag & 0x0F] == 0) {
    open = true;
  }
  else if (p_actwk->u.obj.actfree.moveyuka.side >= 0) {
    p_actwk->u.obj.actfree.moveyuka.side = 1;
    open = true;
  }
  if (open && p_actwk->u.obj.actfree.moveyuka.side > 0) {
    short yoffset = p_actwk->u.obj.actfree.moveyuka.yoffset;
    if (p_actwk->u.obj.cddat.right == 1) {
      yoffset = -yoffset;
    }
    g_ram.scr_shake_flg = 0xFFFF;
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      p_actwk->u.obj.actfree.moveyuka.side = -1;
      g_ram.scr_shake_flg = 0;
    }
  }
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  frameoutchk(p_actwk);
}


SKC_sprite_pattern* moveyukapat[2] = {
  &moveyukasp00,
  &moveyukasp01
};


static SKC_sprite_pattern moveyukasp00 = {
  16,
  {
    { -36, 13, 0x0018, -64 },
    { -36, 13, 0x0018, -32 },
    { -36, 13, 0x0018,   0 },
    { -36, 13, 0x0018,  32 },
    { -20, 13, 0x0020, -64 },
    { -20, 13, 0x0020, -32 },
    { -20, 13, 0x0020,   0 },
    { -20, 13, 0x0020,  32 },
    {  -4, 13, 0x0028, -64 },
    {  -4, 13, 0x0030, -32 },
    {  -4, 13, 0x0030,   0 },
    {  -4, 13, 0x0028,  32 },
    {  12, 13, 0x0010, -64 },
    {  12, 13, 0x0028, -32 },
    {  12, 13, 0x0028,   0 },
    {  12, 13, 0x0810,  32 },
  }
};
static SKC_sprite_pattern moveyukasp01 = {
  16,
  {
    { -68, 13, 0x0018, -32 },
    { -68, 13, 0x0018,   0 },
    { -52, 13, 0x0020, -32 },
    { -52, 13, 0x0020,   0 },
    { -36, 13, 0x0030, -32 },
    { -36, 13, 0x0030,   0 },
    { -20, 13, 0x007C, -32 },
    { -20, 13, 0x087C,   0 },
    {  -4, 13, 0x0084, -32 },
    {  -4, 13, 0x0884,   0 },
    {  12, 13, 0x0084, -32 },
    {  12, 13, 0x0884,   0 },
    {  28, 13, 0x0084, -32 },
    {  28, 13, 0x0884,   0 },
    {  44, 13, 0x008C, -32 },
    {  44, 13, 0x088C,   0 },
  }
};
