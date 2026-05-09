#include "rope.h"
#include <stdbool.h>
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/swdata.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../actset.h"
#include "../action.h"
#include "../etc.h"
#include "../sound.h"
#include "bgspr.h"
static void ropeinit(SKC_sprite_status* p_actwk);
static void ropeinit__sub(SKC_sprite_status* p_actwk);
static void ropemove(SKC_sprite_status* p_actwk);
static void ropestart(SKC_sprite_status* p_actwk);
static void ropefall(SKC_sprite_status* p_actwk);
static void roperoll(SKC_sprite_status* p_actwk);
static void ropestop(SKC_sprite_status* p_actwk);
static void ropestop2(SKC_sprite_status* p_actwk);
static void ropefoutchk(SKC_sprite_status* p_actwk);
static void ropemove2(SKC_sprite_status* p_actwk);
static void roperoll2(SKC_sprite_status* p_actwk);
static void ropemove3(SKC_sprite_status* p_actwk);
static void ropemove4(SKC_sprite_status* p_actwk);
static void ropeposiset(SKC_sprite_status* p_actwk);
static void handlemove(SKC_sprite_status* p_actwk);
static void handlesub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, unsigned char* p_plholding, unsigned char* p_plnograb_timer);
static void handlesub__rolljumpsub(SKC_sprite_status* p_playerwk);
static void handlesub__kcheck(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata);
static void ropeswinginit(SKC_sprite_status* p_actwk);
static void ropeswinginit__sub(SKC_sprite_status* p_actwk);
static void ropeswingmove(SKC_sprite_status* p_actwk);
static void ropeswingfoutchk(SKC_sprite_status* p_actwk);
static void ropeswingmove2(SKC_sprite_status* p_actwk);
static void ropeswingmove3(SKC_sprite_status* p_actwk);
static void ropeswingposiset(SKC_sprite_status* p_actwk);
static void handleswingmove(SKC_sprite_status* p_actwk);
static void hbarinit(SKC_sprite_status* p_actwk);
static void hbarinit__sub(SKC_sprite_status* p_actwk);
static void hbarmove(SKC_sprite_status* p_actwk);
static void hbarroll(SKC_sprite_status* p_actwk);
static void hbarstop(SKC_sprite_status* p_actwk);
static void hbarfoutchk(SKC_sprite_status* p_actwk);
static void hbarmove2(SKC_sprite_status* p_actwk);
static void hbarposiset(SKC_sprite_status* p_actwk);
static void hbarhandlemove(SKC_sprite_status* p_actwk);
static void hbarhandlesub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, unsigned char* p_plholding, unsigned char* p_plnograb_timer);
static void hbarhandlesub__rolljumpsub(SKC_sprite_status* p_playerwk);
static SKC_sprite_pattern ropesp00;
static SKC_sprite_pattern ropesp01;
static SKC_sprite_pattern ropesp02;
static SKC_sprite_pattern ropesp03;
static SKC_sprite_pattern ropesp04;
static SKC_sprite_pattern ropesp05;
static SKC_sprite_pattern ropesp06;
static SKC_sprite_pattern ropesp07;
static SKC_sprite_pattern ropesp08;
static SKC_sprite_pattern ropesp09;
static SKC_sprite_pattern ropesp10;
static SKC_sprite_pattern ropesp11;
static SKC_sprite_pattern ropesp12;
static SKC_sprite_pattern ropesp13;
static SKC_sprite_pattern ropesp14;
static SKC_sprite_pattern ropesp15;
static SKC_sprite_pattern ropesp16;
static SKC_sprite_pattern ropesp17;
static SKC_sprite_pattern ropesp18;
static SKC_sprite_pattern ropesp19;
static SKC_sprite_pattern ropesp20;
static SKC_sprite_pattern ropesp21;
static SKC_sprite_pattern ropesp22;
static SKC_sprite_pattern ropesp23;
static SKC_sprite_pattern ropesp24;
static SKC_sprite_pattern ropesp25;
static SKC_sprite_pattern ropesp26;
static SKC_sprite_pattern ropesp27;
static SKC_sprite_pattern ropesp28;
static SKC_sprite_pattern ropesp29;
static SKC_sprite_pattern ropesp30;
static SKC_sprite_pattern ropesp31;
static SKC_sprite_pattern ropesp32;
static SKC_sprite_pattern ropesp33;
static SKC_sprite_pattern ropesp34;
static SKC_sprite_pattern ropesp35;

extern sonic3_ram g_ram;


void rope(SKC_sprite_status* p_actwk) {
  ropeinit(p_actwk);
}


static void ropeinit(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &ropemove;
  ropeinit__sub(p_actwk);
  p_actwk->patno = 33;
  p_actwk->u.obj.actfree.rope.xdestination = fp16_get_integer(p_actwk->xposi)
                                           + ((p_actwk->u.obj.userflag & 0x7F) << 4);
  SKC_sprite_status* p_prev_actwk = p_actwk;
  SKC_actwkchk_result result;
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi);

  for (int i = 0; i < 5; ++i) {
    result = actwkchk2(p_prev_actwk);
    if (result.actwk_ptr == 0) break;
    if (i == 0) {
      result.actwk_ptr->r_ptr = &ropemove2;
    }
    else {
      result.actwk_ptr->r_ptr = &ropemove3;
    }
    result.actwk_ptr->u.obj.oya = p_prev_actwk - g_ram.actwk;
    p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
    p_prev_actwk = result.actwk_ptr;
    ropeinit__sub(result.actwk_ptr);
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
    yposi += 16;
    ++p_actwk->u.obj.actfree.rope.part_cnt;
    result.actwk_ptr->u.obj.actfree.rope.part_cnt = p_actwk->u.obj.actfree.rope.part_cnt;
  }

  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &handlemove;
    result.actwk_ptr->patno = 32;
    p_actwk->u.obj.actfree.rope.handle = result.actwk_ptr - g_ram.actwk;
  }
  ropemove(p_actwk);
}


static void ropeinit__sub(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
  p_actwk->sprpri = PRI_4;
  p_actwk->patbase = ropepat;
  p_actwk->sproffset = 0x041B;
}


static void ropemove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
  if (BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 0)
      || BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 7)
      || BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 0)
      || BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 7)) {
    p_actwk->r_ptr = &ropestart;
    SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
    p_childwk->u.obj.actfree.rope.unknown2ew = 1;
    p_childwk->u.obj.actfree.rope.unknown38w = 0;
  }
  ropefoutchk(p_actwk);
}


static void ropestart(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 8);
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 2);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)p_actwk->u.obj.actfree.rope.xdestination) {
    if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
      p_actwk->r_ptr = &ropefall;
      p_actwk->xspeed = 0x800;
      p_actwk->yspeed = 0x200;
      p_actwk->patbase = bgsprppat;
      p_actwk->sproffset = 0x62E9;
      p_actwk->sprhs = 8;
      p_actwk->sprvs = 12;
      p_actwk->patno = 0;
      p_actwk->mstno = 0;
      p_actwk->mstrestart = 1;
      SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
      if (BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 0)
          || BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 7)) {
        SET_BIT(p_handlewk->u.obj.actfree.rope.plholding, 0);
        SET_BIT(p_handlewk->u.obj.actfree.rope.plholding, 7);
      }
      if (BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 0)
          || BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 7)) {
        SET_BIT(p_handlewk->u.obj.actfree.rope.pl2holding, 0);
        SET_BIT(p_handlewk->u.obj.actfree.rope.pl2holding, 7);
      }
    }
    else {
      p_actwk->r_ptr = &roperoll;
      SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
      p_childwk->r_ptr = &roperoll2;
      p_childwk->u.obj.actfree.rope.unknown3aw = 0;
      p_childwk->u.obj.actfree.rope.unknown30w = 1;
      p_actwk->direc.w = 0;
      p_actwk->u.obj.actfree.rope.unknown3aw = 0x400;
    }
  }
  ropefoutchk(p_actwk);
}


static void ropefall(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  if (p_actwk->actflg.onscreen == 0) {
    fp16_set_integer(&p_actwk->xposi, 0x7FF0);
  }
  patchg(p_actwk, bgsprpchg);
  ropefoutchk(p_actwk);
}


static void roperoll(SKC_sprite_status* p_actwk) {
  unsigned char angle = p_actwk->direc.w >> 8;
  if (angle > 128) {
    angle = 256 - angle;
  }
  p_actwk->direc.w -= p_actwk->u.obj.actfree.rope.unknown3aw - angle * 2;
  p_actwk->direc.w &= 0xFFFF;
  SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
  if (!BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 0)
      && !BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 7)
      && !BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 0)
      && !BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 7)
      && (p_actwk->direc.w >> 8) + 8 < 16) {
    p_actwk->r_ptr = &ropestop;
    p_actwk->u.obj.actfree.rope.unknown42w = 0;
    p_actwk->u.obj.actfree.rope.unknown44w = 0xFD00;
    p_actwk->u.obj.actfree.rope.unknown38w = 0x1000;
    p_actwk->u.obj.actfree.rope.unknown2ew = 0;
    p_handlewk->u.obj.actfree.rope.unknown30w = 2;
  }
  ropefoutchk(p_actwk);
}


static void ropestop(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.rope.unknown2ew == 0) {
    p_actwk->u.obj.actfree.rope.unknown44w += p_actwk->u.obj.actfree.rope.unknown38w >> 8;
    p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
    p_actwk->u.obj.actfree.rope.unknown42w += p_actwk->u.obj.actfree.rope.unknown44w;
    p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
    if (p_actwk->u.obj.actfree.rope.unknown42w >> 8 < 128) {
      p_actwk->u.obj.actfree.rope.unknown44w -= p_actwk->u.obj.actfree.rope.unknown44w / 16;
      p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      p_actwk->u.obj.actfree.rope.unknown2ew = 1;
      if (p_actwk->u.obj.actfree.rope.unknown38w != 0xC00) {
        p_actwk->u.obj.actfree.rope.unknown38w -= 0x40;
        p_actwk->u.obj.actfree.rope.unknown38w &= 0xFFFF;
      }
      else {
        p_actwk->r_ptr = &ropestop2;
        p_actwk->u.obj.actfree.rope.unknown38w = 0;
        SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
        p_handlewk->u.obj.actfree.rope.unknown30w = 0;
      }
    }
  }
  else {
    p_actwk->u.obj.actfree.rope.unknown44w -= p_actwk->u.obj.actfree.rope.unknown38w >> 8;
    p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
    p_actwk->u.obj.actfree.rope.unknown42w += p_actwk->u.obj.actfree.rope.unknown44w;
    p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
    if (p_actwk->u.obj.actfree.rope.unknown42w >> 8 >= 128) {
      p_actwk->u.obj.actfree.rope.unknown44w -= p_actwk->u.obj.actfree.rope.unknown44w / 16;
      p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      p_actwk->u.obj.actfree.rope.unknown2ew = 0;
      if (p_actwk->u.obj.actfree.rope.unknown38w != 0xC00) {
        p_actwk->u.obj.actfree.rope.unknown38w -= 0x40;
        p_actwk->u.obj.actfree.rope.unknown38w &= 0xFFFF;
      }
      else {
        p_actwk->r_ptr = &ropestop2;
        p_actwk->u.obj.actfree.rope.unknown38w = 0;
        SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
        p_handlewk->u.obj.actfree.rope.unknown30w = 0;
      }
    }
  }
  p_actwk->direc.w = p_actwk->u.obj.actfree.rope.unknown42w;
  p_actwk->u.obj.actfree.rope.unknown3aw = p_actwk->u.obj.actfree.rope.unknown42w / 8;
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  p_childwk->u.obj.actfree.rope.unknown3aw = p_actwk->u.obj.actfree.rope.unknown3aw;
  ropefoutchk(p_actwk);
}


static void ropestop2(SKC_sprite_status* p_actwk) {
  unsigned char angle = p_actwk->u.obj.actfree.rope.unknown38w >> 8;
  p_actwk->u.obj.actfree.rope.unknown38w += 0x200;
  p_actwk->u.obj.actfree.rope.unknown38w &= 0xFFFF;
  short sin, cos;
  sinset(angle, &sin, &cos);
  sin *= 4;
  if (sin == 0x400) {
    sin = 0x3FF;
  }
  p_actwk->direc.w = (unsigned short)sin;
  p_actwk->direc.w &= 0xFFFF;
  p_actwk->u.obj.actfree.rope.unknown3aw = (unsigned short)sin;
  p_actwk->u.obj.actfree.rope.unknown3aw &= 0xFFFF;
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  p_childwk->u.obj.actfree.rope.unknown3aw = p_actwk->u.obj.actfree.rope.unknown3aw;
  ropefoutchk(p_actwk);
}


static void ropefoutchk(SKC_sprite_status* p_actwk) {
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if (chunk_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.ko];

    for (int i = 0; i < p_actwk->u.obj.actfree.rope.part_cnt; ++i) {
      SKC_sprite_status* p_childwk = &g_ram.actwk[p_parentwk->u.obj.ko];
      frameout(p_parentwk);
      p_parentwk = p_childwk;
    }

    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


static void ropemove2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.rope.unknown2ew == 0) {
    unsigned char angle = p_actwk->u.obj.actfree.rope.unknown38w >> 8;
    p_actwk->u.obj.actfree.rope.unknown38w += 0x200;
    p_actwk->u.obj.actfree.rope.unknown38w &= 0xFFFF;
    short sin, cos;
    sinset(angle, &sin, &cos);
    sin *= 4;
    if (sin == 0x400) {
      sin = 0x3FF;
    }
    p_actwk->u.obj.actfree.rope.unknown3aw = (unsigned short)sin;
    p_actwk->u.obj.actfree.rope.unknown3aw &= 0xFFFF;
  }
  else {
    unsigned char angle = p_actwk->u.obj.actfree.rope.unknown38w >> 8;
    p_actwk->u.obj.actfree.rope.unknown38w += 0x100;
    p_actwk->u.obj.actfree.rope.unknown38w &= 0xFFFF;
    short sin, cos;
    sinset(angle, &sin, &cos);
    sin *= 8;
    p_actwk->u.obj.actfree.rope.unknown3aw = (unsigned short)sin;
    p_actwk->u.obj.actfree.rope.unknown3aw &= 0xFFFF;
  }
  p_actwk->direc.w = p_actwk->u.obj.actfree.rope.unknown3aw;
  p_actwk->patno = ((p_actwk->direc.w >> 8) + 4) / 8;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_parentwk->xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_parentwk->yposi));
  actionsub(p_actwk);
}


static void roperoll2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->direc.w = p_parentwk->direc.w;
  p_actwk->patno = ((p_actwk->direc.w >> 8) + 4) / 8;
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_childwk->xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_childwk->yposi));
  actionsub(p_actwk);
}


static void ropemove3(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->u.obj.actfree.rope.unknown3aw = p_parentwk->u.obj.actfree.rope.unknown3aw;
  p_actwk->direc.w = p_parentwk->direc.w + p_actwk->u.obj.actfree.rope.unknown3aw;
  p_actwk->direc.w &= 0xFFFF;
  p_actwk->patno = ((p_actwk->direc.w >> 8) + 4) / 8;
  ropemove4(p_actwk);
}


static void ropemove4(SKC_sprite_status* p_actwk) {
  ropeposiset(p_actwk);
  actionsub(p_actwk);
}


static void ropeposiset(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  unsigned char angle = (p_actwk->direc.w >> 8) + 4;
  angle = angle - angle % 8;
  short sin, cos;
  sinset(angle, &sin, &cos);
  short xposi = (-sin + 8) / 16 + fp16_get_integer(p_parentwk->xposi);
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (cos + 8) / 16;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static void handlemove(SKC_sprite_status* p_actwk) {
  short xposi_save = fp16_get_integer(p_actwk->xposi);
  short yposi_save = fp16_get_integer(p_actwk->yposi);
  ropeposiset(p_actwk);
  if (xposi_save != fp16_get_integer(p_actwk->xposi)) {
    p_actwk->u.obj.actfree.rope_handle.prev_xposi = xposi_save;
  }
  if (yposi_save != fp16_get_integer(p_actwk->yposi)) {
    p_actwk->u.obj.actfree.rope_handle.prev_yposi = yposi_save;
  }
  handlesub(p_actwk, &g_ram.actwk[0], g_ram.swdata, &p_actwk->u.obj.actfree.rope.plholding, &p_actwk->u.obj.actfree.rope.plnograb_timer);
  handlesub(p_actwk, &g_ram.actwk[1], g_ram.swdata2_auto, &p_actwk->u.obj.actfree.rope.pl2holding, &p_actwk->u.obj.actfree.rope.pl2nograb_timer);
  bool plnoholding = !BIT_IS_SET(p_actwk->u.obj.actfree.rope.plholding, 0)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.plholding, 7)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.pl2holding, 0)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.pl2holding, 7);
  if (plnoholding || p_actwk->u.obj.actfree.rope.unknown30w == 0) {
    actionsub(p_actwk);
  }
}


static void handlesub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, unsigned char* p_plholding, unsigned char* p_plnograb_timer) {
  unsigned char tbl[16] = {
    145, 145, 144, 144, 144, 144, 144, 144, 146, 146, 146, 146, 146, 146, 145, 145
  };
  unsigned char tbl2[16] = {
    120, 120, 127, 127, 126, 126, 125, 125, 124, 124, 123, 123, 122, 122, 121, 121
  };
  struct {
    signed char x;
    signed char y;
  }
  offsettbl[8] = {
    {   0,  24 },
    { -18,  19 },
    { -24,   0 },
    { -18, -19 },
    {   0, -24 },
    {  18, -19 },
    {  24,   0 },
    {  18,  19 }
  };

  if (BIT_IS_SET(*p_plholding, 0) || BIT_IS_SET(*p_plholding, 7)) {
    if (!BIT_IS_SET(*p_plholding, 7)) {
      if (p_playerwk->actflg.onscreen == 1 && p_playerwk->r_no < 4) {
        if (are_any_trg_buttons_used(swdata.pressed)) {
          p_playerwk->u.play.control_bitfield = 0;
          CLEAR_BIT(*p_plholding, 0);
          if (p_actwk->u.obj.actfree.rope.unknown30w != 1) {
            p_playerwk->xspeed = fp16_get_integer(p_actwk->xposi) - p_actwk->u.obj.actfree.rope_handle.prev_xposi;
            p_playerwk->xspeed *= 128;
            p_playerwk->yspeed = fp16_get_integer(p_actwk->yposi) - p_actwk->u.obj.actfree.rope_handle.prev_yposi;
            p_playerwk->yspeed *= 128;
            *p_plnograb_timer = 60;
            if (swdata.down.l == 1) {
              p_playerwk->xspeed = -0x200;
            }
            if (swdata.down.r == 1) {
              p_playerwk->yspeed -= 0x380;
            }
            handlesub__rolljumpsub(p_playerwk);
          }
          else {
            *p_plnograb_timer = 60;
            SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
            short sin, cos;
            sinset(p_parentwk->direc.w >> 8, &sin, &cos);
            p_playerwk->xspeed = cos * 8;
            p_playerwk->yspeed = sin * 8;
            handlesub__rolljumpsub(p_playerwk);
          }
        }
        else {
          if (p_actwk->u.obj.actfree.rope.unknown30w == 0) {
            handlesub__kcheck(p_actwk, p_playerwk, swdata);
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_actwk->xposi));
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi) + 20);
            SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
            unsigned char index = p_parentwk->direc.w >> 8;
            if (p_playerwk->u.play.cddat.left == 1) {
              index = 256 - index;
            }
            index = (index + 8) / 16;
            p_playerwk->patno = tbl[index];
          }
          else {
            SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
            unsigned char index = p_parentwk->direc.w >> 8;
            if (p_playerwk->u.play.cddat.left == 1) {
              index = 256 - index;
            }
            index = (index + 16) / 32 * 2;
            p_playerwk->patno = tbl2[index];
            p_playerwk->mstno = 0;
            index &= 0xFE;
            signed char xoffset = offsettbl[index].x;
            signed char yoffset = offsettbl[index].y;
            if (p_playerwk->u.play.cddat.left == 1) {
              xoffset = -xoffset;
            }
            unsigned char angle = (p_playerwk->direc.w >> 8) + 4 & 0xF8;
            short sin, cos;
            sinset(angle, &sin, &cos);
            short xposi = (-sin + 8) / 16 + fp16_get_integer(p_parentwk->xposi) + xoffset;
            fp16_set_integer(&p_playerwk->xposi, xposi);
            short yposi = (cos + 8) / 16 + fp16_get_integer(p_parentwk->yposi) + yoffset;
            fp16_set_integer(&p_playerwk->yposi, yposi);
          }
          p_playerwk->actflg.vflip = 0;
          p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
          Perform_Player_DPLC(p_playerwk, p_playerwk->patno);
        }
      }
      else {
        p_playerwk->u.play.control_bitfield = 0;
        CLEAR_BIT(*p_plholding, 0);
        *p_plnograb_timer = 60;
      }
    }
    else {
      p_playerwk->xspeed = 0x300;
      p_playerwk->yspeed = 0x200;
      p_playerwk->u.play.cddat.jump = 1;
      p_playerwk->u.play.control_bitfield = 0;
      CLEAR_BIT(*p_plholding, 0);
      CLEAR_BIT(*p_plholding, 7);
      *p_plnograb_timer = 60;
    }
  }
  else {
    if (*p_plnograb_timer != 0) {
    --*p_plnograb_timer;
    }
    if (*p_plnograb_timer == 0) {
      short xposi = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + 16;
      short yposi = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi) + 16;
      if ((unsigned short)xposi < 32 && (unsigned short)yposi < 24
          && p_playerwk->u.play.control_bitfield == 0 && p_playerwk->r_no < 4
          && g_ram.editmode == 0) {
        p_playerwk->xspeed = 0;
        p_playerwk->yspeed = 0;
        p_playerwk->mspeed = 0;
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_actwk->xposi));
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi) + 20);
        p_playerwk->mstno = 20;
        p_playerwk->u.play.spindash_flag = 0;
        p_playerwk->u.play.control_bitfield = 3;
        p_playerwk->actflg.vflip = 0;
        SET_BIT(*p_plholding, 0);
        soundset(74);
      }
    }
  }
}


static void handlesub__rolljumpsub(SKC_sprite_status* p_playerwk) {
  p_playerwk->yspeed -= 0x380;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.jump_flag = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->u.play.cddat.ball = 1;
}


static void handlesub__kcheck(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata) {
  SKC_pad ktbl[10] = {
    { .l = 1 },
    { .l = 1 },
    { .l = 1 },
    { .r = 1 },
    { .r = 1 },
    { .r = 1 },
    { .u = 1 },
    { .u = 1 },
    { .u = 1 },
    { 0 }
  };

  if (p_playerwk != &g_ram.actwk[0]) return;
  if (!are_any_buttons_used(swdata.down) && !are_any_buttons_used(swdata.pressed)) return;

  if (are_same_buttons_used(swdata.pressed, ktbl[p_actwk->pattimm])) {
    ++p_actwk->pattimm;
    if (!are_any_buttons_used(ktbl[p_actwk->pattimm])) {
      g_ram.levelselectcheat = 1;
      g_ram.slowmotioncheat = 1;
      soundset(51);
      p_actwk->pattimm = 0;
    }
  }
  else {
    p_actwk->pattimm = 0;
  }
}


void ropeswing(SKC_sprite_status* p_actwk) {
  ropeswinginit(p_actwk);
}


static void ropeswinginit(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &ropeswingmove;
  ropeswinginit__sub(p_actwk);
  p_actwk->patno = 33;
  SKC_sprite_status* p_prev_actwk = p_actwk;
  SKC_actwkchk_result result;
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi);
  unsigned char cnt = p_actwk->u.obj.userflag & 0x0F;

  for (int i = 0; i < cnt; ++i) {
    result = actwkchk2(p_prev_actwk);
    if (result.actwk_ptr == 0) break;
    if (i == 0) {
      result.actwk_ptr->u.obj.actfree.rope.unknown44w = 0xFE50;
      result.actwk_ptr->u.obj.actfree.rope.unknown38w = 0x800;
      result.actwk_ptr->r_ptr = &ropeswingmove2;
      result.actwk_ptr->u.obj.actfree.rope.unknown42w = (p_actwk->u.obj.userflag & 0xF0) << 8;
    }
    else {
      result.actwk_ptr->r_ptr = &ropeswingmove3;
    }
    result.actwk_ptr->u.obj.oya = p_prev_actwk - g_ram.actwk;
    p_prev_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
    ropeswinginit__sub(result.actwk_ptr);
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
    yposi += 16;
    ++p_actwk->u.obj.actfree.rope.part_cnt;
    result.actwk_ptr->u.obj.actfree.rope.part_cnt = p_actwk->u.obj.actfree.rope.part_cnt;
  }

  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &handleswingmove;
    result.actwk_ptr->patno = 32;
    p_actwk->u.obj.actfree.rope.handle = result.actwk_ptr - g_ram.actwk;
  }
  ropeswingmove(p_actwk);
}


static void ropeswinginit__sub(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
  p_actwk->sprpri = PRI_4;
  p_actwk->patbase = ropepat;
  p_actwk->sproffset = 0x041B;
}


static void ropeswingmove(SKC_sprite_status* p_actwk) {
  ropeswingfoutchk(p_actwk);
}


static void ropeswingfoutchk(SKC_sprite_status* p_actwk) {
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if (chunk_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.ko];

    for (int i = 0; i < p_actwk->u.obj.actfree.rope.part_cnt; ++i) {
      SKC_sprite_status* p_childwk = &g_ram.actwk[p_parentwk->u.obj.ko];
      frameout(p_parentwk);
      p_parentwk = p_childwk;
    }

    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


static void ropeswingmove2(SKC_sprite_status* p_actwk) {
  if (true) {
    short sin, cos;
    sinset(g_ram.ropeswing_angle >> 8, &sin, &cos);
    p_actwk->direc.w = (unsigned short)sin * 44;
    p_actwk->direc.w &= 0xFFFF;
    p_actwk->u.obj.actfree.rope.unknown3aw = (unsigned short)sin * 44 / 8;
    p_actwk->u.obj.actfree.rope.unknown3aw &= 0xFFFF;
    p_actwk->patno = ((p_actwk->direc.w >> 8) + 4) / 8;
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->u.obj.actfree.rope.unknown2ew == 0) {
      p_actwk->u.obj.actfree.rope.unknown44w += p_actwk->u.obj.actfree.rope.unknown38w >> 8;
      p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      p_actwk->u.obj.actfree.rope.unknown42w += p_actwk->u.obj.actfree.rope.unknown44w;
      p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
      if (p_actwk->u.obj.actfree.rope.unknown42w >> 8 < 128) {
        p_actwk->u.obj.actfree.rope.unknown2ew = 1;
      }
    }
    else {
      p_actwk->u.obj.actfree.rope.unknown44w -= p_actwk->u.obj.actfree.rope.unknown38w >> 8;
      p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      p_actwk->u.obj.actfree.rope.unknown42w += p_actwk->u.obj.actfree.rope.unknown44w;
      p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
      if (p_actwk->u.obj.actfree.rope.unknown42w >> 8 >= 128) {
        p_actwk->u.obj.actfree.rope.unknown2ew = 0;
      }
    }
    p_actwk->direc.w = p_actwk->u.obj.actfree.rope.unknown42w;
    p_actwk->u.obj.actfree.rope.unknown3aw = p_actwk->u.obj.actfree.rope.unknown42w / 8;
    p_actwk->patno = ((p_actwk->direc.w >> 8) + 4) / 8;
    actionsub(p_actwk);
  }
}


static void ropeswingmove3(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->u.obj.actfree.rope.unknown3aw = p_parentwk->u.obj.actfree.rope.unknown3aw;
  p_actwk->direc.w = p_parentwk->direc.w + p_actwk->u.obj.actfree.rope.unknown3aw;
  p_actwk->direc.w &= 0xFFFF;
  p_actwk->patno = ((p_actwk->direc.w >> 8) + 4) / 8;
  ropeswingposiset(p_actwk);
  actionsub(p_actwk);
}


static void ropeswingposiset(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  unsigned char angle = (p_actwk->direc.w >> 8) + 4;
  angle = angle - angle % 8;
  short sin, cos;
  sinset(angle, &sin, &cos);
  short xposi = (-sin + 8) / 16 + fp16_get_integer(p_parentwk->xposi);
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (cos + 8) / 16 + fp16_get_integer(p_parentwk->yposi);
}


static void handleswingmove(SKC_sprite_status* p_actwk) {
  short xposi_save = fp16_get_integer(p_actwk->xposi);
  short yposi_save = fp16_get_integer(p_actwk->yposi);
  ropeswingposiset(p_actwk);
  if (xposi_save != fp16_get_integer(p_actwk->xposi)) {
    p_actwk->u.obj.actfree.rope_handle.prev_xposi = xposi_save;
  }
  if (yposi_save != fp16_get_integer(p_actwk->yposi)) {
    p_actwk->u.obj.actfree.rope_handle.prev_yposi = yposi_save;
  }
  handlesub(p_actwk, &g_ram.actwk[0], g_ram.swdata, &p_actwk->u.obj.actfree.rope.plholding, &p_actwk->u.obj.actfree.rope.plnograb_timer);
  handlesub(p_actwk, &g_ram.actwk[1], g_ram.swdata2_auto, &p_actwk->u.obj.actfree.rope.pl2holding, &p_actwk->u.obj.actfree.rope.pl2nograb_timer);
  bool plnoholding = !BIT_IS_SET(p_actwk->u.obj.actfree.rope.plholding, 0)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.plholding, 7)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.pl2holding, 0)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.pl2holding, 7);
  if (plnoholding || p_actwk->u.obj.actfree.rope.unknown30w == 0) {
    actionsub(p_actwk);
  }
}


void hbar(SKC_sprite_status* p_actwk) {
  hbarinit(p_actwk);
}


static void hbarinit(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &hbarmove;
  hbarinit__sub(p_actwk);
  p_actwk->patno = 35;
  SKC_sprite_status* p_prev_actwk = p_actwk;
  SKC_actwkchk_result result;
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi);

  for (int i = 0; i < 2; ++i) {
    result = actwkchk2(p_prev_actwk);
    if (result.actwk_ptr == 0) break;
    if (i == 0) {
      result.actwk_ptr->r_ptr = &hbarmove2;
    }
    result.actwk_ptr->u.obj.oya = p_prev_actwk - g_ram.actwk;
    p_prev_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
    hbarinit__sub(result.actwk_ptr);
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
    yposi += 16;
    ++p_actwk->u.obj.actfree.rope.part_cnt;
    result.actwk_ptr->u.obj.actfree.rope.part_cnt = p_actwk->u.obj.actfree.rope.part_cnt;
  }

  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &hbarhandlemove;
    result.actwk_ptr->patno = 34;
    result.actwk_ptr->u.obj.actfree.rope.unknown42w = (unsigned short)fp16_get_integer(result.actwk_ptr->xposi);
    result.actwk_ptr->u.obj.actfree.rope.unknown42w &= 0xFFFF;
    result.actwk_ptr->u.obj.actfree.rope.unknown44w = (unsigned short)fp16_get_integer(result.actwk_ptr->yposi);
    result.actwk_ptr->u.obj.actfree.rope.unknown44w &= 0xFFFF;
    p_actwk->u.obj.actfree.rope.handle = result.actwk_ptr - g_ram.actwk;
  }
  hbarmove(p_actwk);
}


static void hbarinit__sub(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
  p_actwk->sprpri = PRI_4;
  p_actwk->patbase = ropepat;
  p_actwk->sproffset = 0x0455;
}


static void hbarmove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
  if (BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 7)
      || BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 7)) {
    p_actwk->r_ptr = &hbarroll;
    p_handlewk->u.obj.actfree.rope.unknown30w = 1;
    p_actwk->direc.w = 0;
    p_actwk->u.obj.actfree.rope.unknown3aw = 0x800;
  }
  hbarfoutchk(p_actwk);
}


static void hbarroll(SKC_sprite_status* p_actwk) {
  unsigned char angle = p_actwk->direc.w >> 8;
  if (angle > 128) {
    angle = 256 - angle;
  }
  p_actwk->direc.w -= p_actwk->u.obj.actfree.rope.unknown3aw - angle * 2;
  p_actwk->direc.w &= 0xFFFF;
  angle = (p_actwk->direc.w >> 8) - (p_actwk->direc.w >> 8) % 8;
  if (angle == 64) {
    soundset(126);
  }
  p_actwk->sprpri = p_actwk->direc.w < 128 ? PRI_4 : PRI_5;
  SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
  if (p_handlewk->u.obj.actfree.rope.plholding != 0) {
    g_ram.custom_follow_flag = 1;
    fp16_set_integer(&g_ram.custom_follow_xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&g_ram.custom_follow_yposi, fp16_get_integer(p_actwk->yposi));
  }
  if (p_handlewk->u.obj.actfree.rope.plholding == 0 && p_handlewk->u.obj.actfree.rope.pl2holding == 0) {
    if ((p_actwk->direc.w >> 8) + 8 < 16) {
      p_actwk->r_ptr = &hbarstop;
      p_actwk->u.obj.actfree.rope.unknown42w = 0;
      p_actwk->u.obj.actfree.rope.unknown44w = 0xFD00;
      p_actwk->u.obj.actfree.rope.unknown38w = 0x1000;
      p_actwk->u.obj.actfree.rope.unknown2ew = 0;
      p_handlewk->u.obj.actfree.rope.unknown30w = 2;
    }
  }
  hbarfoutchk(p_actwk);
}


static void hbarstop(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.rope.unknown2ew == 0) {
    p_actwk->u.obj.actfree.rope.unknown44w += p_actwk->u.obj.actfree.rope.unknown38w >> 8;
    p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
    p_actwk->u.obj.actfree.rope.unknown42w += p_actwk->u.obj.actfree.rope.unknown44w;
    p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
    if (p_actwk->u.obj.actfree.rope.unknown42w >> 8 < 128) {
      p_actwk->u.obj.actfree.rope.unknown44w -= p_actwk->u.obj.actfree.rope.unknown44w / 16;
      p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      p_actwk->u.obj.actfree.rope.unknown2ew = 1;
      if (p_actwk->u.obj.actfree.rope.unknown38w != 0xC00) {
        p_actwk->u.obj.actfree.rope.unknown38w -= 0x40;
        p_actwk->u.obj.actfree.rope.unknown38w &= 0xFFFF;
      }
      else {
        p_actwk->r_ptr = &hbarmove;
        p_actwk->u.obj.actfree.rope.unknown38w = 0;
        SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
        p_handlewk->u.obj.actfree.rope.unknown30w = 0;
        p_actwk->u.obj.actfree.rope.unknown42w = (unsigned short)fp16_get_integer(p_handlewk->xposi);
        p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
        p_actwk->u.obj.actfree.rope.unknown44w = (unsigned short)fp16_get_integer(p_handlewk->yposi);
        p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      }
    }
  }
  else {
    p_actwk->u.obj.actfree.rope.unknown44w -= p_actwk->u.obj.actfree.rope.unknown38w >> 8;
    p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
    p_actwk->u.obj.actfree.rope.unknown42w += p_actwk->u.obj.actfree.rope.unknown44w;
    p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
    if (p_actwk->u.obj.actfree.rope.unknown42w >> 8 >= 128) {
      p_actwk->u.obj.actfree.rope.unknown44w -= p_actwk->u.obj.actfree.rope.unknown44w / 16;
      p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      p_actwk->u.obj.actfree.rope.unknown2ew = 0;
      if (p_actwk->u.obj.actfree.rope.unknown38w != 0xC00) {
        p_actwk->u.obj.actfree.rope.unknown38w -= 0x40;
        p_actwk->u.obj.actfree.rope.unknown38w &= 0xFFFF;
      }
      else {
        p_actwk->r_ptr = &hbarmove;
        p_actwk->u.obj.actfree.rope.unknown38w = 0;
        SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
        p_handlewk->u.obj.actfree.rope.unknown30w = 0;
        p_actwk->u.obj.actfree.rope.unknown42w = (unsigned short)fp16_get_integer(p_handlewk->xposi);
        p_actwk->u.obj.actfree.rope.unknown42w &= 0xFFFF;
        p_actwk->u.obj.actfree.rope.unknown44w = (unsigned short)fp16_get_integer(p_handlewk->yposi);
        p_actwk->u.obj.actfree.rope.unknown44w &= 0xFFFF;
      }
    }
  }
  p_actwk->direc.w = p_actwk->u.obj.actfree.rope.unknown42w;
  p_actwk->sprpri = p_actwk->direc.w < 128 ? PRI_4 : PRI_5;
  p_actwk->u.obj.actfree.rope.unknown3aw = p_actwk->u.obj.actfree.rope.unknown42w / 8;
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  p_childwk->u.obj.actfree.rope.unknown3aw = p_actwk->u.obj.actfree.rope.unknown3aw;
  SKC_sprite_status* p_handlewk = &g_ram.actwk[p_actwk->u.obj.actfree.rope.handle];
  if (BIT_IS_SET(p_handlewk->u.obj.actfree.rope.plholding, 7)
      || BIT_IS_SET(p_handlewk->u.obj.actfree.rope.pl2holding, 7)) {
    p_actwk->r_ptr = &hbarroll;
    p_handlewk->u.obj.actfree.rope.unknown30w = 1;
    p_actwk->u.obj.actfree.rope.unknown3aw = 0x800;
  }
  hbarfoutchk(p_actwk);
}


static void hbarfoutchk(SKC_sprite_status* p_actwk) {
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if (chunk_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.ko];

    for (int i = 0; i < p_actwk->u.obj.actfree.rope.part_cnt; ++i) {
      SKC_sprite_status* p_childwk = &g_ram.actwk[p_parentwk->u.obj.ko];
      frameout(p_parentwk);
      p_parentwk = p_childwk;
    }

    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


static void hbarmove2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  p_actwk->direc.w = p_childwk->direc.w;
  p_actwk->patno = ((p_actwk->direc.w >> 8) + 4) / 8;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_childwk->xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_childwk->yposi));
  actionsub(p_actwk);
}


static void hbarposiset(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  unsigned char angle = (p_actwk->direc.w >> 8) + 4;
  angle = angle - angle % 8;
  short sin, cos;
  sinset(angle, &sin, &cos);
  short xposi = (-sin + 8) / 16 + fp16_get_integer(p_parentwk->xposi);
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (cos + 8) / 16 + fp16_get_integer(p_parentwk->yposi);
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static void hbarhandlemove(SKC_sprite_status* p_actwk) {
  short xposi_save = fp16_get_integer(p_actwk->xposi);
  short yposi_save = fp16_get_integer(p_actwk->yposi);
  hbarposiset(p_actwk);
  if (xposi_save != fp16_get_integer(p_actwk->xposi)) {
    p_actwk->u.obj.actfree.rope_handle.prev_xposi = xposi_save;
  }
  if (yposi_save != fp16_get_integer(p_actwk->yposi)) {
    p_actwk->u.obj.actfree.rope_handle.prev_yposi = yposi_save;
  }
  hbarhandlesub(p_actwk, &g_ram.actwk[0], g_ram.swdata, &p_actwk->u.obj.actfree.rope.plholding, &p_actwk->u.obj.actfree.rope.plnograb_timer);
  hbarhandlesub(p_actwk, &g_ram.actwk[1], g_ram.swdata2_auto, &p_actwk->u.obj.actfree.rope.pl2holding, &p_actwk->u.obj.actfree.rope.pl2nograb_timer);
  bool plnoholding = !BIT_IS_SET(p_actwk->u.obj.actfree.rope.plholding, 0)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.plholding, 7)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.pl2holding, 0)
                  && !BIT_IS_SET(p_actwk->u.obj.actfree.rope.pl2holding, 7);
  if (plnoholding || p_actwk->u.obj.actfree.rope.unknown30w == 0) {
    actionsub(p_actwk);
  }
}


static void hbarhandlesub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, unsigned char* p_plholding, unsigned char* p_plnograb_timer) {
  unsigned char tbl[16] = {
    145, 145, 144, 144, 144, 144, 144, 144, 146, 146, 146, 146, 146, 146, 145, 145
  };
  unsigned char tbl2[16] = {
    120, 120, 127, 127, 126, 126, 125, 125, 124, 124, 123, 123, 122, 122, 121, 121
  };
  struct {
    signed char x;
    signed char y;
  }
  offsettbl[8] = {
    {   0,  24 },
    { -18,  19 },
    { -24,   0 },
    { -18, -19 },
    {   0, -24 },
    {  18, -19 },
    {  24,   0 },
    {  18,  19 }
  };

  if (BIT_IS_SET(*p_plholding, 0) || BIT_IS_SET(*p_plholding, 7)) {
    if (p_playerwk->actflg.onscreen == 1 && p_playerwk->r_no < 4 && g_ram.editmode == 0) {
      if (are_any_trg_buttons_used(swdata.pressed)) {
        p_playerwk->u.play.control_bitfield = 0;
        CLEAR_BIT(*p_plholding, 0);
        CLEAR_BIT(*p_plholding, 7);
        if (p_actwk->u.obj.actfree.rope.unknown30w != 1) {
          p_playerwk->xspeed = (fp16_get_integer(p_actwk->xposi) - p_actwk->u.obj.actfree.rope_handle.prev_xposi);
          p_playerwk->xspeed *= 128;
          p_playerwk->yspeed = (fp16_get_integer(p_actwk->yposi) - p_actwk->u.obj.actfree.rope_handle.prev_yposi);
          p_playerwk->yspeed *= 128;
          *p_plnograb_timer = 60;
          if (swdata.down.l == 1) {
            p_playerwk->xspeed = -0x200;
          }
          if (swdata.down.r == 1) {
            p_playerwk->yspeed -= 0x380;
          }
          hbarhandlesub__rolljumpsub(p_playerwk);
        }
        else {
          *p_plnograb_timer = 60;
          SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
          short sin, cos;
          sinset(p_parentwk->direc.w >> 8, &sin, &cos);
          p_playerwk->xspeed = cos * 12;
          p_playerwk->yspeed = sin * 12;
          hbarhandlesub__rolljumpsub(p_playerwk);
        }
      }
      else {
        if (p_actwk->u.obj.actfree.rope.unknown30w == 0) {
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_actwk->xposi));
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi) + 20);
          SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
          unsigned char index = p_parentwk->direc.w >> 8;
          if (p_playerwk->u.play.cddat.left == 1) {
            index = 256 - index;
          }
          index = (index + 8) / 16;
          p_playerwk->patno = tbl[index];
        }
        else {
          SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
          unsigned char index = p_parentwk->direc.w >> 8;
          if (p_playerwk->u.play.cddat.left == 1) {
            index = 256 - index;
          }
          index = (index + 16) / 32 * 2;
          p_playerwk->patno = tbl2[index];
          p_playerwk->mstno = 0;
          index &= 0xFE;
          signed char xoffset = offsettbl[index].x;
          signed char yoffset = offsettbl[index].y;
          if (p_playerwk->u.play.cddat.left == 1) {
            xoffset = -xoffset;
          }
          unsigned char angle = (p_playerwk->direc.w >> 8) + 4 & 0xF8;
          short sin, cos;
          sinset(angle, &sin, &cos);
          short xposi = (-sin + 8) / 16 + fp16_get_integer(p_parentwk->xposi) + xoffset;
          fp16_set_integer(&p_playerwk->xposi, xposi);
          short yposi = (cos + 8) / 16 + fp16_get_integer(p_parentwk->yposi) + yoffset;
          fp16_set_integer(&p_playerwk->yposi, yposi);
        }
        p_playerwk->actflg.vflip = 0;
        p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
        Perform_Player_DPLC(p_playerwk, p_playerwk->patno);
      }
    }
    else {
      p_playerwk->u.play.control_bitfield = 0;
      CLEAR_BIT(*p_plholding, 0);
      CLEAR_BIT(*p_plholding, 7);
      *p_plnograb_timer = 60;
    }
  }
  else {
    if (*p_plnograb_timer != 0) {
    --*p_plnograb_timer;
    }
    if (*p_plnograb_timer == 0) {
      short xposi = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + 16;
      short yposi = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi) + 16;
      if ((unsigned short)xposi < 32 && (unsigned short)yposi < 40
          && (p_playerwk->xspeed >= 0x400 || yposi < 24)) {
        short xspeed = p_playerwk->xspeed;

        do {
          if (p_playerwk->u.play.control_bitfield == 0 && p_playerwk->r_no < 4 && g_ram.editmode == 0) {
            p_playerwk->xspeed = 0;
            p_playerwk->yspeed = 0;
            p_playerwk->mspeed = 0;
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_actwk->xposi));
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi) + 20);
            p_playerwk->mstno = 20;
            p_playerwk->u.play.spindash_flag = 0;
            p_playerwk->u.play.control_bitfield = 3;
            p_playerwk->actflg.vflip = 0;
            SET_BIT(*p_plholding, 0);
          }
        }
        while (xspeed < 0x400);

        SET_BIT(*p_plholding, 7);
        soundset(74);
      }
    }
  }
}


static void hbarhandlesub__rolljumpsub(SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.jump_flag = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->u.play.cddat.ball = 1;
}


SKC_sprite_pattern* ropepat[36] = {
  &ropesp00,
  &ropesp01,
  &ropesp02,
  &ropesp03,
  &ropesp04,
  &ropesp05,
  &ropesp06,
  &ropesp07,
  &ropesp08,
  &ropesp09,
  &ropesp10,
  &ropesp11,
  &ropesp12,
  &ropesp13,
  &ropesp14,
  &ropesp15,
  &ropesp16,
  &ropesp17,
  &ropesp18,
  &ropesp19,
  &ropesp20,
  &ropesp21,
  &ropesp22,
  &ropesp23,
  &ropesp24,
  &ropesp25,
  &ropesp26,
  &ropesp27,
  &ropesp28,
  &ropesp29,
  &ropesp30,
  &ropesp31,
  &ropesp32,
  &ropesp33,
  &ropesp34,
  &ropesp35
};


static SKC_sprite_pattern ropesp00 = {
  1,
  {
    { 0, 1, 0x001B, -8 }
  }
};
static SKC_sprite_pattern ropesp01 = {
  1,
  {
    { 0, 1, 0x0019, -8 }
  }
};
static SKC_sprite_pattern ropesp02 = {
  1,
  {
    { 0, 1, 0x0017, -8 }
  }
};
static SKC_sprite_pattern ropesp03 = {
  1,
  {
    { 0, 5, 0x0013, -16 }
  }
};
static SKC_sprite_pattern ropesp04 = {
  1,
  {
    { 0, 5, 0x000F, -16 }
  }
};
static SKC_sprite_pattern ropesp05 = {
  1,
  {
    { 0, 5, 0x000B, -16 }
  }
};
static SKC_sprite_pattern ropesp06 = {
  1,
  {
    { 0, 4, 0x0009, -16 }
  }
};
static SKC_sprite_pattern ropesp07 = {
  1,
  {
    { 0, 4, 0x0007, -16 }
  }
};
static SKC_sprite_pattern ropesp08 = {
  1,
  {
    { 0, 4, 0x0005, -16 }
  }
};
static SKC_sprite_pattern ropesp09 = {
  1,
  {
    { -7, 4, 0x1007, -16 }
  }
};
static SKC_sprite_pattern ropesp10 = {
  1,
  {
    { -7, 4, 0x1009, -16 }
  }
};
static SKC_sprite_pattern ropesp11 = {
  1,
  {
    { -15, 5, 0x100B, -16 }
  }
};
static SKC_sprite_pattern ropesp12 = {
  1,
  {
    { -15, 5, 0x100F, -16 }
  }
};
static SKC_sprite_pattern ropesp13 = {
  1,
  {
    { -15, 5, 0x1013, -16 }
  }
};
static SKC_sprite_pattern ropesp14 = {
  1,
  {
    { -15, 1, 0x1017, -8 }
  }
};
static SKC_sprite_pattern ropesp15 = {
  1,
  {
    { -15, 1, 0x1019, -8 }
  }
};
static SKC_sprite_pattern ropesp16 = {
  1,
  {
    { -15, 1, 0x101B, -8 }
  }
};
static SKC_sprite_pattern ropesp17 = {
  1,
  {
    { -15, 1, 0x1819, -1 }
  }
};
static SKC_sprite_pattern ropesp18 = {
  1,
  {
    { -15, 1, 0x1817, -1 }
  }
};
static SKC_sprite_pattern ropesp19 = {
  1,
  {
    { -15, 5, 0x1813, -1 }
  }
};
static SKC_sprite_pattern ropesp20 = {
  1,
  {
    { -15, 5, 0x180F, -1 }
  }
};
static SKC_sprite_pattern ropesp21 = {
  1,
  {
    { -15, 5, 0x180B, -1 }
  }
};
static SKC_sprite_pattern ropesp22 = {
  1,
  {
    { -7, 4, 0x1809, -1 }
  }
};
static SKC_sprite_pattern ropesp23 = {
  1,
  {
    { -7, 4, 0x1807, -1 }
  }
};
static SKC_sprite_pattern ropesp24 = {
  1,
  {
    { 0, 4, 0x0805, -1 }
  }
};
static SKC_sprite_pattern ropesp25 = {
  1,
  {
    { 0, 4, 0x0807, -1 }
  }
};
static SKC_sprite_pattern ropesp26 = {
  1,
  {
    { 0, 4, 0x0809, -1 }
  }
};
static SKC_sprite_pattern ropesp27 = {
  1,
  {
    { 0, 5, 0x080B, -1 }
  }
};
static SKC_sprite_pattern ropesp28 = {
  1,
  {
    { 0, 5, 0x080F, -1 }
  }
};
static SKC_sprite_pattern ropesp29 = {
  1,
  {
    { 0, 5, 0x0813, -1 }
  }
};
static SKC_sprite_pattern ropesp30 = {
  1,
  {
    { 0, 1, 0x0817, -1 }
  }
};
static SKC_sprite_pattern ropesp31 = {
  1,
  {
    { 0, 1, 0x0819, -1 }
  }
};
static SKC_sprite_pattern ropesp32 = {
  1,
  {
    { -4, 8, 0x0000, -12 }
  }
};
static SKC_sprite_pattern ropesp33 = {
  1,
  {
    { -4, 4, 0x0003, -8 }
  }
};
static SKC_sprite_pattern ropesp34 = {
  1,
  {
    { -4, 8, 0x0020, -12 }
  }
};
static SKC_sprite_pattern ropesp35 = {
  1,
  {
    { -4, 8, 0x001D, -9 }
  }
};
