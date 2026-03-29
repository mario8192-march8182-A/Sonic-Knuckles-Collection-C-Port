#include "bryuka.h"
#include <stdbool.h>
#include "../types/sonic3ram.h"
#include "../types/speed.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../constants.h"
#include "../hitchk.h"
static void bryukainit(SKC_sprite_status* p_actwk);
static void bryukamove(SKC_sprite_status* p_actwk);
static void bryukamove__sub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char prev_mstno);
static void bryukamove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void bryukamove__sub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void bryukamove3(SKC_sprite_status* p_actwk);
static void bryukamove5(SKC_sprite_status* p_actwk);
static void bryukamove5__sub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short prev_mstno);
static void bryukamove5__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void bryukamove5__sub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static SKC_speed bryukaspdtbl5[14];
static SKC_speed bryukaspdtbl51[4];
static signed char bryuka05tbl[28];
static SKC_speed bryukaspdtbl2[16];
static SKC_sprite_pattern bryukasp00;
static SKC_sprite_pattern bryukasp01;
static SKC_sprite_pattern bryukasp02;
static SKC_sprite_pattern bryukasp03;
static SKC_sprite_pattern bryukasp04;
static SKC_sprite_pattern bryukasp05;
static SKC_sprite_pattern bryukasp40;
static SKC_sprite_pattern bryukasp41;
static SKC_sprite_pattern bryukasp50;
static SKC_sprite_pattern bryukasp51;
static SKC_sprite_pattern bryukasp52;
static SKC_sprite_pattern bryukasp53;
static SKC_sprite_pattern bryukasp54;
static SKC_sprite_pattern bryukasp55;
static SKC_sprite_pattern bryukasp56;
static SKC_sprite_pattern bryukasp57;
static SKC_sprite_pattern bryukasp58;
static SKC_sprite_pattern bryukasp59;
static SKC_sprite_pattern bryukasp5a;
static SKC_sprite_pattern bryukasp60;
static SKC_sprite_pattern bryukasp61;

extern sonic3_ram g_ram;


void bryuka(SKC_sprite_status* p_actwk) {
  bryukainit(p_actwk);
}


static void bryukainit(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;

  switch (get_zone(g_ram.stageno)) {
    default:
      p_actwk->patbase = get_act(g_ram.stageno) != ACT_2 ? bryukapat : bryukapat2;
      p_actwk->sproffset = 0x4001;
      p_actwk->sprhs = 16;
      p_actwk->sprvs = get_act(g_ram.stageno) != ACT_2 ? 40 : 44;
      p_actwk->u.obj.actfree.bryuka.spdtbl_ptr = bryukaspdtbl;
      break;
    case CARNIVAL_NIGHT:
      p_actwk->patbase = bryukapat3;
      p_actwk->sproffset = 0x4430;
      p_actwk->sprhs = 32;
      p_actwk->sprvs = 32;
      p_actwk->u.obj.actfree.bryuka.spdtbl_ptr = bryukaspdtbl2;
      break;
    case FLYING_BATTERY:
      p_actwk->patbase = bryukapat4;
      p_actwk->sproffset = 0x243A;
      p_actwk->sprhs = 16;
      p_actwk->sprvs = 16;
      p_actwk->u.obj.actfree.bryuka.spdtbl_ptr = bryukaspdtbl51;
      break;
    case ICECAP:
      p_actwk->patbase = bryukapat5;
      p_actwk->sproffset = !BIT_IS_SET(p_actwk->u.obj.userflag, 4) ? 0x4001 : 0x43B6;
      p_actwk->sprhs = 16;
      p_actwk->sprvs = !BIT_IS_SET(p_actwk->u.obj.userflag, 4) ? 36 : 16;
      p_actwk->patno = p_actwk->u.obj.userflag & 0x0F;
      if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
        p_actwk->r_ptr = &bryukamove5;
      }
      else {
        p_actwk->u.obj.actfree.bryuka.spdtbl_ptr = bryukaspdtbl51;
      }
      break;
    case LAUNCH_BASE:
      p_actwk->patbase = bryukapat6;
      p_actwk->sproffset = 0x4001;
      p_actwk->sprhs = 32;
      p_actwk->sprvs = 32;
      p_actwk->u.obj.actfree.bryuka.spdtbl_ptr = bryukaspdtbl2;
      break;
  }

  if (p_actwk->r_ptr == 0) {
    p_actwk->r_ptr = p_actwk->u.obj.userflag == 0 ? &bryukamove3 : &bryukamove;
  }
  p_actwk->r_ptr(p_actwk);
}


static void bryukamove(SKC_sprite_status* p_actwk) {
  unsigned short emyscorecnt = g_ram.emyscorecnt;
  unsigned char plmstno = g_ram.actwk[0].mstno;
  unsigned char pl2mstno = g_ram.actwk[1].mstno;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  bool sub = false;
  if (p_actwk->u.obj.cddat.plride == 1 && p_actwk->u.obj.cddat.pl2ride == 1) {
    if (plmstno == 2 || pl2mstno == 2) {
      bryukamove__sub2(p_actwk, &g_ram.actwk[0], plmstno);
      bryukamove__sub2(p_actwk, &g_ram.actwk[1], pl2mstno);
      sub = true;
    }
  }
  else if (p_actwk->u.obj.cddat.plride == 1) {
    if (plmstno == 2) {
      bryukamove__sub(p_actwk, &g_ram.actwk[0]);
      sub = true;
    }
  }
  else if (p_actwk->u.obj.cddat.pl2ride == 1) {
    if (pl2mstno == 2) {
      bryukamove__sub(p_actwk, &g_ram.actwk[0]);
      sub = true;
    }
  }
  if (!sub) {
    frameoutchk(p_actwk);
  }
  else {
    g_ram.emyscorecnt = emyscorecnt;
    p_actwk->u.obj.cddat.plride = 0;
    p_actwk->u.obj.cddat.pl2ride = 0;
    ++p_actwk->patno;
    p_actwk->r_ptr = &bryukamove2;
    breakgosubf(p_actwk, p_actwk->u.obj.actfree.bryuka.spdtbl_ptr);
    bryukamove2(p_actwk);
  }
}


static void bryukamove__sub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char prev_mstno) {
  if (prev_mstno != 2) {
    bryukamove__sub1(p_actwk, p_playerwk);
  }
  else {
    bryukamove__sub(p_actwk, p_playerwk);
  }
}


static void bryukamove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->yspeed = -0x300;
  bryukamove__sub1(p_actwk, p_playerwk);
}


static void bryukamove__sub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->r_no = 2;
  bryukamove2(p_actwk);
}


void bryukamove2(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void bryukamove3(SKC_sprite_status* p_actwk) {
  short plyspeed = g_ram.actwk[0].yspeed;
  short pl2yspeed = g_ram.actwk[1].yspeed;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (result.plcoli[0] != HITCHK_COLI_BOTTOM && result.plcoli[1] != HITCHK_COLI_BOTTOM) {
    frameoutchk(p_actwk);
  }
  else {
    if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
      g_ram.actwk[0].yspeed = plyspeed;
    }
    if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
      g_ram.actwk[1].yspeed = pl2yspeed;
    }
    if (p_actwk->u.obj.cddat.plride == 1) {
      g_ram.actwk[0].u.play.cddat.jump = 1;
      g_ram.actwk[0].u.play.cddat.ride = 0;
    }
    if (p_actwk->u.obj.cddat.pl2ride == 1) {
      g_ram.actwk[1].u.play.cddat.jump = 1;
      g_ram.actwk[1].u.play.cddat.ride = 0;
    }
    ++p_actwk->patno;
    p_actwk->r_ptr = &bryukamove2;
    breakgosubf(p_actwk, p_actwk->u.obj.actfree.bryuka.spdtbl_ptr);
    bryukamove2(p_actwk);
  }
}


static void bryukamove5(SKC_sprite_status* p_actwk) {
  unsigned short emyscorecnt = g_ram.emyscorecnt;
  unsigned char plmstno = g_ram.actwk[0].mstno;
  unsigned char pl2mstno = g_ram.actwk[1].mstno;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk_bryuka(p_actwk, data, bryuka05tbl);
  bool sub = false;
  if (p_actwk->u.obj.cddat.plride == 1 && p_actwk->u.obj.cddat.pl2ride == 1) {
    bool fout = false;
    if (plmstno != 2 || (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) && g_ram.actwk[0].u.play.top_solid_bit != 14)) {
      g_ram.actwk[0].u.play.top_solid_bit = 12;
      g_ram.actwk[0].u.play.lrb_solid_bit = 13;
      if (pl2mstno != 2 || (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) && g_ram.actwk[1].u.play.top_solid_bit != 14)) {
        g_ram.actwk[1].u.play.top_solid_bit = 12;
        g_ram.actwk[1].u.play.lrb_solid_bit = 13;
        fout = true;
      }
    }
    if (!fout) {
      bryukamove5__sub2(p_actwk, &g_ram.actwk[0], plmstno);
      bryukamove5__sub2(p_actwk, &g_ram.actwk[1], pl2mstno);
      sub = true;
    }
  }
  else if (p_actwk->u.obj.cddat.plride == 1) {
    if (plmstno != 2 && (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) && g_ram.actwk[0].u.play.top_solid_bit != 14)) {
      g_ram.actwk[0].u.play.top_solid_bit = 12;
      g_ram.actwk[0].u.play.lrb_solid_bit = 13;
    }
    else {
      bryukamove5__sub(p_actwk, &g_ram.actwk[0]);
      sub = true;
    }
  }
  else if (p_actwk->u.obj.cddat.pl2ride == 1) {
    if (pl2mstno != 2 || (!BIT_IS_SET(p_actwk->u.obj.userflag, 7) && g_ram.actwk[1].u.play.top_solid_bit != 14)) {
      g_ram.actwk[1].u.play.top_solid_bit = 12;
      g_ram.actwk[1].u.play.lrb_solid_bit = 13;
    }
    else {
      bryukamove5__sub(p_actwk, &g_ram.actwk[1]);
      sub = true;
    }
    frameoutchk(p_actwk);
    return;
  }
  if (!sub) {
    frameoutchk(p_actwk);
  }
  else {
    g_ram.emyscorecnt = emyscorecnt;
    p_actwk->u.obj.cddat.plride = 0;
    p_actwk->u.obj.cddat.pl2ride = 0;
    ++p_actwk->patno;
    p_actwk->r_ptr = &bryukamove2;
    breakgosubf(p_actwk, &bryukaspdtbl5[p_actwk->patno - 1]);
    bryukamove2(p_actwk);
  }
}


static void bryukamove5__sub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short prev_mstno) {
  if (prev_mstno != 2) {
    bryukamove5__sub1(p_actwk, p_playerwk);
  }
  else {
    bryukamove5__sub(p_actwk, p_playerwk);
  }
}


static void bryukamove5__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  bryukamove5__sub1(p_actwk, p_playerwk);
}


static void bryukamove5__sub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->r_no = 2;
}


static SKC_speed bryukaspdtbl5[14] = {
  { -0x140, -0xA00 },
  {  0x140, -0xA00 },
  { -0x120, -0x900 },
  {  0x120, -0x900 },
  { -0x100, -0x800 },
  {  0x100, -0x800 },
  { -0x0E0, -0x700 },
  {  0x0E0, -0x700 },
  { -0x0C0, -0x600 },
  {  0x0C0, -0x600 },
  { -0x0A0, -0x580 },
  {  0x0A0, -0x580 },
  { -0x080, -0x500 },
  {  0x080, -0x500 }
};


static SKC_speed bryukaspdtbl51[4] = {
  { -0x200, -0x200 },
  {  0x200, -0x200 },
  { -0x100, -0x100 },
  {  0x100, -0x100 }
};


static signed char bryuka05tbl[28] = {
  35, 35, 34, 34, 33, 33, 32, 31, 31, 30,
  30, 29, 29, 28, 27, 27, 26, 26, 25, 25,
  23, 22, 21, 21, 20, 20, 19, 19
};


SKC_speed bryukaspdtbl[12] = {
  { -0x100, -0x200 },
  {  0x100, -0x200 },
  { -0x0E0, -0x1C0 },
  {  0x0E0, -0x1C0 },
  { -0x0C0, -0x180 },
  {  0x0C0, -0x180 },
  { -0x0A0, -0x140 },
  {  0x0A0, -0x140 },
  { -0x080, -0x100 },
  {  0x080, -0x100 },
  { -0x060, -0x0C0 },
  {  0x060, -0x0C0 }
};


static SKC_speed bryukaspdtbl2[16] = {
  { -0x400, -0x400 },
  { -0x200, -0x400 },
  {  0x200, -0x400 },
  {  0x400, -0x400 },
  { -0x3C0, -0x3C0 },
  { -0x1C0, -0x3C0 },
  {  0x1C0, -0x3C0 },
  {  0x3C0, -0x3C0 },
  { -0x380, -0x380 },
  { -0x180, -0x380 },
  {  0x180, -0x380 },
  {  0x380, -0x380 },
  { -0x340, -0x340 },
  { -0x140, -0x340 },
  {  0x140, -0x340 },
  {  0x340, -0x340 }
};


SKC_sprite_pattern* bryukapat[2] = {
  &bryukasp00,
  &bryukasp01
};


static SKC_sprite_pattern bryukasp00 = {
  6,
  {
    { -48, 12, 0x0034, -16 },
    { -40, 13, 0x001C, -16 },
    { -24, 13, 0x0824, -16 },
    {  -8, 13, 0x0824, -16 },
    {   8, 13, 0x0824, -16 },
    {  24, 13, 0x002C, -16 }
  }
};
static SKC_sprite_pattern bryukasp01 = {
  12,
  {
    { -48, 4, 0x0034, -16 },
    { -48, 4, 0x0036,   0 },
    { -40, 5, 0x001C, -16 },
    { -40, 5, 0x0020,   0 },
    { -24, 5, 0x0828, -16 },
    { -24, 5, 0x0824,   0 },
    {  -8, 5, 0x0828, -16 },
    {  -8, 5, 0x0824,   0 },
    {   8, 5, 0x0828, -16 },
    {   8, 5, 0x0824,   0 },
    {  24, 5, 0x002C, -16 },
    {  24, 5, 0x0030,   0 }
  }
};


SKC_sprite_pattern* bryukapat2[2] = {
  &bryukasp02,
  &bryukasp03
};


static SKC_sprite_pattern bryukasp02 = {
  6,
  {
    { -52, 13, 0x0800, -16 },
    { -36, 13, 0x000E, -16 },
    { -20, 13, 0x0016, -16 },
    {  -4, 13, 0x0816, -16 },
    {  12, 13, 0x0016, -16 },
    {  28, 13, 0x0816, -16 }
  }
};
static SKC_sprite_pattern bryukasp03 = {
  12,
  {
    { -52, 5, 0x0804, -16 },
    { -52, 5, 0x0800,   0 },
    { -36, 5, 0x000E, -16 },
    { -36, 5, 0x0012,   0 },
    { -20, 5, 0x0016, -16 },
    { -20, 5, 0x001A,   0 },
    {  -4, 5, 0x081A, -16 },
    {  -4, 5, 0x0816,   0 },
    {  12, 5, 0x0016, -16 },
    {  12, 5, 0x001A,   0 },
    {  28, 5, 0x081A, -16 },
    {  28, 5, 0x0816,   0 }
  }
};


SKC_sprite_pattern* bryukapat3[2] = {
  &bryukasp04,
  &bryukasp05
};


static SKC_sprite_pattern bryukasp04 = {
  8,
  {
    { -32, 13, 0x0000, -32 },
    { -32, 13, 0x0800,   0 },
    { -16, 13, 0x0008, -32 },
    { -16, 13, 0x0808,   0 },
    {   0, 13, 0x0008, -32 },
    {   0, 13, 0x0808,   0 },
    {  16, 13, 0x0010, -32 },
    {  16, 13, 0x0810,   0 }
  }
};
static SKC_sprite_pattern bryukasp05 = {
  16,
  {
    { -32, 5, 0x0000, -32 },
    { -32, 5, 0x0004, -16 },
    { -32, 5, 0x0804,   0 },
    { -32, 5, 0x0800,  16 },
    { -16, 5, 0x0008, -32 },
    { -16, 5, 0x000C, -16 },
    { -16, 5, 0x080C,   0 },
    { -16, 5, 0x0808,  16 },
    {   0, 5, 0x0008, -32 },
    {   0, 5, 0x000C, -16 },
    {   0, 5, 0x080C,   0 },
    {   0, 5, 0x0808,  16 },
    {  16, 5, 0x0010, -32 },
    {  16, 5, 0x0014, -16 },
    {  16, 5, 0x0814,   0 },
    {  16, 5, 0x0810,  16 }
  }
};


SKC_sprite_pattern* bryukapat4[2] = {
  &bryukasp40,
  &bryukasp41
};


static SKC_sprite_pattern bryukasp40 = {
  2,
  {
    { -16, 13, 0x0000, -16 },
    {   0, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern bryukasp41 = {
  4,
  {
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0004,   0 },
    {   0, 5, 0x0000, -16 },
    {   0, 5, 0x0004,   0 }
  }
};


SKC_sprite_pattern* bryukapat5[12] = {
  &bryukasp50,
  &bryukasp51,
  &bryukasp52,
  &bryukasp53,
  &bryukasp54,
  &bryukasp55,
  &bryukasp56,
  &bryukasp57,
  &bryukasp58,
  &bryukasp59,
  &bryukasp5a,
  &bryukasp5a
};


static SKC_sprite_pattern bryukasp50 = {
  7,
  {
    { -40, 13, 0x00AC, -16 },
    { -24, 13, 0x0018, -16 },
    {  -8, 13, 0x0028, -16 },
    {   8, 13, 0x0028, -16 },
    {  24, 13, 0x0028, -16 },
    {  40, 13, 0x0038, -16 },
    {  56, 12, 0x0048, -16 }
  }
};
static SKC_sprite_pattern bryukasp51 = {
  14,
  {
    { -40, 5, 0x00AC, -16 },
    { -40, 5, 0x00B0,   0 },
    { -24, 5, 0x0018, -16 },
    { -24, 5, 0x001C,   0 },
    {  -8, 5, 0x0028, -16 },
    {  -8, 5, 0x002C,   0 },
    {   8, 5, 0x0028, -16 },
    {   8, 5, 0x002C,   0 },
    {  24, 5, 0x0028, -16 },
    {  24, 5, 0x002C,   0 },
    {  40, 5, 0x0038, -16 },
    {  40, 5, 0x003C,   0 },
    {  56, 4, 0x0048, -16 },
    {  56, 4, 0x004A,   0 }
  }
};
static SKC_sprite_pattern bryukasp52 = {
  6,
  {
    { -32, 13, 0x0018, -16 },
    { -16, 13, 0x0028, -16 },
    {   0, 13, 0x0028, -16 },
    {  16, 13, 0x0028, -16 },
    {  32, 13, 0x0038, -16 },
    {  48, 12, 0x0048, -16 }
  }
};
static SKC_sprite_pattern bryukasp53 = {
  12,
  {
    { -32, 5, 0x0018, -16 },
    { -32, 5, 0x001C,   0 },
    { -16, 5, 0x0028, -16 },
    { -16, 5, 0x002C,   0 },
    {   0, 5, 0x0028, -16 },
    {   0, 5, 0x002C,   0 },
    {  16, 5, 0x0028, -16 },
    {  16, 5, 0x002C,   0 },
    {  32, 5, 0x0038, -16 },
    {  32, 5, 0x003C,   0 },
    {  48, 4, 0x0048, -16 },
    {  48, 4, 0x004A,   0 }
  }
};
static SKC_sprite_pattern bryukasp54 = {
  5,
  {
    { -24, 13, 0x0028, -16 },
    {  -8, 13, 0x0028, -16 },
    {   8, 13, 0x0028, -16 },
    {  24, 13, 0x0038, -16 },
    {  40, 12, 0x0048, -16 }
  }
};
static SKC_sprite_pattern bryukasp55 = {
  10,
  {
    { -24, 5, 0x0028, -16 },
    { -24, 5, 0x002C,   0 },
    {  -8, 5, 0x0028, -16 },
    {  -8, 5, 0x002C,   0 },
    {   8, 5, 0x0028, -16 },
    {   8, 5, 0x002C,   0 },
    {  24, 5, 0x0038, -16 },
    {  24, 5, 0x003C,   0 },
    {  40, 4, 0x0048, -16 },
    {  40, 4, 0x004A,   0 }
  }
};
static SKC_sprite_pattern bryukasp56 = {
  4,
  {
    { -16, 13, 0x0028, -16 },
    {   0, 13, 0x0028, -16 },
    {  16, 13, 0x0038, -16 },
    {  32, 12, 0x0048, -16 }
  }
};
static SKC_sprite_pattern bryukasp57 = {
  8,
  {
    { -16, 5, 0x0028, -16 },
    { -16, 5, 0x002C,   0 },
    {   0, 5, 0x0028, -16 },
    {   0, 5, 0x002C,   0 },
    {  16, 5, 0x0038, -16 },
    {  16, 5, 0x003C,   0 },
    {  32, 4, 0x0048, -16 },
    {  32, 4, 0x004A,   0 }
  }
};
static SKC_sprite_pattern bryukasp58 = {
  3,
  {
    { -8, 13, 0x0028, -16 },
    {  8, 13, 0x0038, -16 },
    { 24, 12, 0x0048, -16 }
  }
};
static SKC_sprite_pattern bryukasp59 = {
  6,
  {
    { -8, 5, 0x0028, -16 },
    { -8, 5, 0x002C,   0 },
    {  8, 5, 0x0038, -16 },
    {  8, 5, 0x003C,   0 },
    { 24, 4, 0x0048, -16 },
    { 24, 4, 0x004A,   0 }
  }
};
static SKC_sprite_pattern bryukasp5a = {
  4,
  {
    { -16, 5, 0x0013, -16 },
    { -16, 5, 0x0013,   0 },
    {   0, 5, 0x0013, -16 },
    {   0, 5, 0x0013,   0 }
  }
};


SKC_sprite_pattern* bryukapat6[2] = {
  &bryukasp60,
  &bryukasp61
};


static SKC_sprite_pattern bryukasp60 = {
  8,
  {
    { -32, 13, 0x0000, -32 },
    { -32, 13, 0x0000,   0 },
    { -16, 13, 0x0018, -32 },
    { -16, 13, 0x0020,   0 },
    {   0, 13, 0x0038, -32 },
    {   0, 13, 0x0040,   0 },
    {  16, 13, 0x0040, -32 },
    {  16, 13, 0x0038,   0 }
  }
};
static SKC_sprite_pattern bryukasp61 = {
  16,
  {
    { -32, 5, 0x0000, -32 },
    { -32, 5, 0x0004, -16 },
    { -32, 5, 0x0000,   0 },
    { -32, 5, 0x0004,  16 },
    { -16, 5, 0x0018, -32 },
    { -16, 5, 0x001C, -16 },
    { -16, 5, 0x0020,   0 },
    { -16, 5, 0x0024,  16 },
    {   0, 5, 0x0038, -32 },
    {   0, 5, 0x003C, -16 },
    {   0, 5, 0x0040,   0 },
    {   0, 5, 0x0044,  16 },
    {  16, 5, 0x0040, -32 },
    {  16, 5, 0x0044, -16 },
    {  16, 5, 0x0038,   0 },
    {  16, 5, 0x003C,  16 }
  }
};
