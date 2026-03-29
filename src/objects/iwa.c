#include "iwa.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../types/iwabreakdata.h"
#include "../types/size.h"
#include "../types/sonic3ram.h"
#include "../types/speed.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../constants.h"
#include "../dircol.h"
#include "../hitchk.h"
#include "../sound.h"
static void iwainit(SKC_sprite_status* p_actwk);
static void iwamove(SKC_sprite_status* p_actwk);
static void iwamove__sub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char prev_plmstno);
static void iwamove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void iwamove__sub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void iwamove2(SKC_sprite_status* p_actwk);
static void iwamove20(SKC_sprite_status* p_actwk);
static void iwamove21(SKC_sprite_status* p_actwk);
static void iwamove22(SKC_sprite_status* p_actwk);
static void vsiwamove(SKC_sprite_status* p_actwk);
static void vsiwamove2(SKC_sprite_status* p_actwk);
static void vsiwasub(SKC_sprite_status* p_actwk);
static void vsiwamove3(SKC_sprite_status* p_actwk);
static void iwamove3(SKC_sprite_status* p_actwk);
static void iwamove3__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short prev_plxspeed);
static void iwamove3__ridechk(SKC_sprite_status* p_actwk);
static void iwamove4(SKC_sprite_status* p_actwk);
static void iwamovek(SKC_sprite_status* p_actwk);
static void iwamovek__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void iwamovepush(SKC_sprite_status* p_actwk);
static void iwamovepush__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool prev_plpush);
static void iwabreakgosub(SKC_sprite_status* p_actwk);
static void iwabreakgosub2(SKC_sprite_status* p_actwk, SKC_speed* p_speed_data, unsigned char size_type);
static void iwabreakgosub3(SKC_sprite_status* p_actwk);
static void iwabreakgosub4(SKC_sprite_status* p_actwk, SKC_speed* p_speed_data, unsigned char size_type);
static void* iwabreaktbl[8];
static SKC_iwa_break_data iwabreaktbl0;
static SKC_iwa_break_data iwabreaktbl1;
static SKC_iwa_break_data iwabreaktbl2;
static SKC_iwa_break_data iwabreaktbl3;
static SKC_lrz_iwa_break_data iwabreaktbl4;
static SKC_lrz_iwa_break_data iwabreaktbl5;
static SKC_lrz_iwa_break_data iwabreaktbl7;
static SKC_speed* iwaspdtbl[8];
static SKC_speed iwaspdtbl0[8];
static SKC_speed iwaspdtbl01[8];
static SKC_speed iwaspdtbl1[5];
static SKC_speed iwaspdtbl2[4];
static SKC_speed iwaspdtbl3[6];
static SKC_speed iwaspdtbl30[6];
static SKC_speed iwaspdtbl31[6];
static SKC_speed iwaspdtbl4[8];
static SKC_speed iwaspdtbl5[6];
static SKC_sprite_pattern iwasp00;
static SKC_sprite_pattern iwasp01;
static SKC_sprite_pattern iwasp02;
static SKC_sprite_pattern iwasp03;
static SKC_sprite_pattern iwasp04;
static SKC_sprite_pattern iwasp05;
static SKC_sprite_pattern iwasp06;
static SKC_sprite_pattern iwasp200;
static SKC_sprite_pattern iwasp201;
static SKC_sprite_pattern iwasp202;
static SKC_sprite_pattern iwasp203;
static SKC_sprite_pattern iwasp204;
static SKC_sprite_pattern iwasp205;
static SKC_sprite_pattern iwasp206;
static SKC_sprite_pattern vsiwasp00;
static SKC_sprite_pattern vsiwasp01;
static SKC_sprite_pattern vsiwasp02;
static SKC_sprite_pattern vsiwasp03;
static SKC_sprite_pattern iwasp900;
static SKC_sprite_pattern iwasp901;
static SKC_sprite_pattern iwasp902;
static SKC_sprite_pattern iwasp903;
static SKC_sprite_pattern iwasp904;
static SKC_sprite_pattern iwasp905;
static SKC_sprite_pattern iwasp906;
static SKC_sprite_pattern iwasp907;
static SKC_sprite_pattern iwasp908;
static SKC_sprite_pattern iwasp909;
static SKC_sprite_pattern iwasp920;
static SKC_sprite_pattern iwasp921;
static SKC_sprite_pattern iwasp922;
static SKC_sprite_pattern iwasp923;
static SKC_sprite_pattern iwasp928;
static SKC_sprite_pattern iwasp929;

extern sonic3_ram g_ram;


void iwa(SKC_sprite_status* p_actwk) {
  iwainit(p_actwk);
}


void vsiwa(SKC_sprite_status* p_actwk) {
  iwainit(p_actwk);
}


static void iwainit(SKC_sprite_status* p_actwk) {
  SKC_size iwainittbl[8] = {
    { 24, 39 },
    { 24, 23 },
    { 24, 15 },
    { 14, 15 },
    { 16, 40 },
    { 40, 16 },
    { 40, 16 },
    { 16, 32 }
  };

  unsigned char size_type = p_actwk->u.obj.userflag >> 4 & 7;
  p_actwk->patno = size_type;
  p_actwk->sprhs = iwainittbl[size_type].w;
  p_actwk->sprvs = iwainittbl[size_type].h;
  p_actwk->sprvsize = iwainittbl[size_type].h;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->u.obj.actfree.iwa.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.actfree.iwa.push_distance = 64;

  switch (g_ram.stageno) {
    default:
      switch (get_act(g_ram.stageno)) {
        case ACT_1:
          p_actwk->patbase = iwapat;
          p_actwk->sproffset = 0x2333;
          break;
        case ACT_2:
          p_actwk->patbase = iwapat2;
          p_actwk->sproffset = 0x42E9;
          break;
      }
      break;
    case ENDLESS_MINE_ACT_1:
      p_actwk->patbase = vsiwapat;
      p_actwk->sproffset = 0xE300;
      p_actwk->patno = 0;
      break;
    case LAVA_REEF_ACT_1:
      p_actwk->patbase = iwapat9;
      p_actwk->sproffset = 0x40D3;
      p_actwk->patno += 4;
      break;
    case LAVA_REEF_ACT_2:
      p_actwk->patbase = iwapat92;
      p_actwk->sproffset = 0x640D;
      p_actwk->patno += 4;
      break;
  }

  if ((p_actwk->u.obj.userflag & 0xF) == 0xF) {
    p_actwk->r_ptr = &iwamovek;
  }
  else {
    p_actwk->r_ptr = &iwamove;
    if (BIT_IS_SET(p_actwk->u.obj.userflag, 2)) {
      p_actwk->r_ptr = &iwamove3;
    }
    else if (BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
      p_actwk->r_ptr = &iwamove4;
    }
    else if (p_actwk->u.obj.flagwork_index != 0) {
      signed char flag = g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1] & 0x7F;
      if (flag != 0) {
        fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - flag);
        p_actwk->u.obj.actfree.iwa.push_distance = -flag + 64;
        SKC_dircol_result result = emycol_d(p_actwk);
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      }
    }
  }
  p_actwk->r_ptr(p_actwk);
}


static void iwamove(SKC_sprite_status* p_actwk) {
  unsigned short emyscorecnt = g_ram.emyscorecnt;
  unsigned char plmstno = g_ram.actwk[0].mstno;
  unsigned char pl2mstno = g_ram.actwk[1].mstno;
  p_actwk->u.obj.actfree.iwa.prev_plpush = g_ram.actwk[0].u.play.cddat.push;
  p_actwk->u.obj.actfree.iwa.prev_pl2push = g_ram.actwk[1].u.play.cddat.push;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 1)) {
    iwamovepush(p_actwk);
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 0)
      || (p_actwk->u.obj.cddat.plride == 0 && p_actwk->u.obj.cddat.pl2ride == 0)
      || (p_actwk->u.obj.cddat.plride == 1 && p_actwk->u.obj.cddat.pl2ride == 1 && plmstno != 2 && pl2mstno != 2)
      || (p_actwk->u.obj.cddat.plride == 1 && p_actwk->u.obj.cddat.pl2ride == 0 && plmstno != 2)
      || (p_actwk->u.obj.cddat.plride == 0 && p_actwk->u.obj.cddat.pl2ride == 1 && pl2mstno != 2)) {
    if (g_ram.vs_flag != 0) {
      actionsub(p_actwk);
    }
    else {
      frameoutchk2(p_actwk, p_actwk->u.obj.actfree.iwa.xposi_init);
    }
  }
  else {
    if (p_actwk->u.obj.cddat.plride == 1 && p_actwk->u.obj.cddat.pl2ride == 1) {
      iwamove__sub2(p_actwk, &g_ram.actwk[0], plmstno);
      iwamove__sub2(p_actwk, &g_ram.actwk[1], pl2mstno);
    }
    else if (p_actwk->u.obj.cddat.plride == 1) {
      iwamove__sub(p_actwk, &g_ram.actwk[0]);
    }
    else if (p_actwk->u.obj.cddat.pl2ride == 1) {
      iwamove__sub(p_actwk, &g_ram.actwk[1]);
    }
    g_ram.emyscorecnt = emyscorecnt;
    p_actwk->u.obj.cddat.plpush = 0;
    p_actwk->u.obj.cddat.pl2push = 0;
    if (g_ram.vs_flag != 0) {
      vsiwamove(p_actwk);
    }
    else {
      p_actwk->r_ptr = &iwamove2;
      iwabreakgosub(p_actwk);
      iwamove2(p_actwk);
    }
  }
}


static void iwamove__sub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char prev_plmstno) {
  if (prev_plmstno == 2) {
    iwamove__sub(p_actwk, p_playerwk);
  }
  else {
    iwamove__sub1(p_actwk, p_playerwk);
  }
}


static void iwamove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->yspeed = -0x300;
  iwamove__sub1(p_actwk, p_playerwk);
}


static void iwamove__sub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->r_no = 2;
}


static void iwamove2(SKC_sprite_status* p_actwk) {
  if (get_zone(g_ram.stageno) == LAVA_REEF) {
    iwamove21(p_actwk);
  }
  else {
    p_actwk->r_ptr = &iwamove20;
    iwamove20(p_actwk);
  }
}


static void iwamove20(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 2;
    ++p_actwk->patno;
    if (p_actwk->patno >= 7) {
      p_actwk->patno = 3;
    }
  }
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->actflg.onscreen == 1) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void iwamove21(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &iwamove22;
  iwamove22(p_actwk);
}


static void iwamove22(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 7;
    p_actwk->patno = (p_actwk->patno + 1 & 3) + p_actwk->u.obj.actfree.iwa.size_type;
  }
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->actflg.onscreen == 1) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void vsiwamove(SKC_sprite_status* p_actwk) {
  vsiwasub(p_actwk);
  p_actwk->patno = 3;
  p_actwk->r_ptr = &vsiwamove2;
  iwabreakgosub(p_actwk);
  vsiwamove2(p_actwk);
}


static void vsiwamove2(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->actflg.onscreen == 1) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void vsiwasub(SKC_sprite_status* p_actwk) {
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    *result.actwk_ptr = *p_actwk;
    result.actwk_ptr->u.obj.actfree.iwa.oya_r_ptr = p_actwk->r_ptr;
    result.actwk_ptr->r_ptr = &vsiwamove3;
    result.actwk_ptr->patno = 7;
  }
}


static void vsiwamove3(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    p_actwk->r_ptr = p_actwk->u.obj.actfree.iwa.oya_r_ptr;
    p_actwk->patno = 0;
  }
  actionsub(p_actwk);
}


static void iwamove3(SKC_sprite_status* p_actwk) {
  short plxspeed = g_ram.actwk[0].xspeed;
  short pl2xspeed = g_ram.actwk[1].xspeed;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_SIDE || result.plcoli[1] == HITCHK_COLI_SIDE) {
    bool breakable_by_knuckles = BIT_IS_SET(p_actwk->u.obj.userflag, 7);
    bool breakable = !BIT_IS_SET(p_actwk->u.obj.userflag, 7);
    bool can_break_by_touch = g_ram.ssonicflag != 0 || g_ram.actwk[0].u.play.character == KNUCKLES;
    bool can_break_as_ball = (g_ram.actwk[0].u.play.cddat.flame_baria == 1 || p_actwk->u.obj.cddat.plpush == 1)
        && g_ram.actwk[0].mstno == 2
        && abs(plxspeed) >= 0x480;
    if (result.plcoli[0] == HITCHK_COLI_SIDE
        && (breakable_by_knuckles && g_ram.actwk[0].u.play.character == KNUCKLES)
            || (breakable && (can_break_by_touch || can_break_as_ball))) {
      p_actwk->u.obj.cddat.plpush = 0;
      iwamove3__break(p_actwk, &g_ram.actwk[0], plxspeed);
      if (p_actwk->u.obj.cddat.pl2push == 1
          && (g_ram.actwk[1].u.play.character == KNUCKLES || g_ram.actwk[1].mstno == 2)) {
        g_ram.actwk[1].xspeed = pl2xspeed;
        g_ram.actwk[1].mspeed = g_ram.actwk[1].xspeed;
        p_actwk->u.obj.cddat.pl2push = 0;
        g_ram.actwk[1].u.play.cddat.push = 0;
      }
    }
    else {
      can_break_by_touch = g_ram.actwk[1].u.play.character == KNUCKLES;
      can_break_as_ball = g_ram.actwk[1].mstno == 2 && abs(pl2xspeed) >= 0x480;
      if (p_actwk->u.obj.cddat.pl2push == 1
          && ((breakable_by_knuckles && g_ram.actwk[1].u.play.character == KNUCKLES)
              || (breakable && (can_break_by_touch || can_break_as_ball)))) {
        p_actwk->u.obj.cddat.pl2push = 0;
        iwamove3__break(p_actwk, &g_ram.actwk[1], pl2xspeed);
        return;
      }
    }
  }
  if (g_ram.vs_flag == 0) {
    frameoutchk2(p_actwk, p_actwk->u.obj.actfree.iwa.xposi_init);
  }
  else {
    actionsub(p_actwk);
  }
}


static void iwamove3__break(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short prev_plxspeed) {
  iwamove3__ridechk(p_actwk);
  if (g_ram.vs_flag == 0) {
    p_actwk->xspeed = prev_plxspeed;
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 4);
    SKC_speed* p_speed_data = iwaspdtbl0;
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 8);
      p_speed_data = iwaspdtbl01;
    }
    p_playerwk->mspeed = p_playerwk->xspeed;
    p_playerwk->u.play.cddat.push = 0;
    if (p_playerwk->u.play.character == KNUCKLES && p_playerwk->u.play.talent_status == 1) {
      p_playerwk->u.play.talent_status = 2;
      p_playerwk->mstno = 33;
      p_playerwk->u.play.cddat.left = p_playerwk->xspeed < 0;
    }
    if (get_zone(g_ram.stageno) == LAVA_REEF) {
      p_actwk->r_ptr = &iwamove22;
      iwabreakgosub4(p_actwk, p_speed_data, p_actwk->patno - 4);
      iwamove22(p_actwk);
    }
    else {
      p_actwk->r_ptr = &iwamove2;
      iwabreakgosub2(p_actwk, p_speed_data, p_actwk->patno);
      iwamove2(p_actwk);
    }
  }
  else {
    p_actwk->xspeed = prev_plxspeed;
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 4);
    SKC_speed* p_speed_data = iwaspdtbl30;
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 8);
      p_speed_data = iwaspdtbl31;
    }
    p_playerwk->mspeed = p_playerwk->xspeed;
    p_playerwk->u.play.cddat.push = 0;
    vsiwasub(p_actwk);
    p_actwk->r_ptr = &vsiwamove2;
    p_actwk->patno = 3;
    iwabreakgosub2(p_actwk, p_speed_data, p_actwk->patno);
    vsiwamove2(p_actwk);
  }
}


static void iwamove3__ridechk(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.plride == 1) {
    g_ram.actwk[0].u.play.cddat.jump = 1;
    g_ram.actwk[0].u.play.cddat.ride = 0;
  }
  p_actwk->u.obj.cddat.plride = 0;
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    g_ram.actwk[1].u.play.cddat.jump = 1;
    g_ram.actwk[1].u.play.cddat.ride = 0;
  }
  p_actwk->u.obj.cddat.pl2ride = 0;
}


static void iwamove4(SKC_sprite_status* p_actwk) {
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
    frameoutchk2(p_actwk, p_actwk->u.obj.actfree.iwa.xposi_init);
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
    p_actwk->r_ptr = &iwamove2;
    iwabreakgosub(p_actwk);
    iwamove2(p_actwk);
  }
}


static void iwamovek(SKC_sprite_status* p_actwk) {
  short emyscorecnt = g_ram.emyscorecnt;
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  if (p_actwk->u.obj.cddat.plride == 0 || g_ram.actwk[0].u.play.character != KNUCKLES) {
    frameoutchk(p_actwk);
  }
  else {
    iwamovek__sub(p_actwk, &g_ram.actwk[0]);
    if (p_actwk->u.obj.cddat.pl2ride == 1) {
      iwamovek__sub(p_actwk, &g_ram.actwk[1]);
    }
    g_ram.emyscorecnt = emyscorecnt;
    p_actwk->u.obj.cddat.pl2ride = 0;
    p_actwk->u.obj.cddat.plride = 0;
    p_actwk->r_ptr = &iwamove2;
    iwabreakgosub(p_actwk);
    iwamove2(p_actwk);
  }
}


static void iwamovek__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->yspeed = -0x300;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->r_no = 2;
}


static void iwamovepush(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.iwa.prev_plpush == 0 && p_actwk->u.obj.actfree.iwa.prev_pl2push == 0) return;

  iwamovepush__sub(p_actwk, &g_ram.actwk[0], p_actwk->u.obj.actfree.iwa.prev_plpush);
  iwamovepush__sub(p_actwk, &g_ram.actwk[1], p_actwk->u.obj.actfree.iwa.prev_pl2push);
}


static void iwamovepush__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool prev_plpush) {
  if (p_playerwk == &g_ram.actwk[0] && p_actwk->u.obj.cddat.plpush == 0) return;
  if (p_playerwk == &g_ram.actwk[1] && p_actwk->u.obj.cddat.pl2push == 0) return;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) return;
  if (!prev_plpush) return;
  if (p_actwk->u.obj.actfree.iwa.push_timer-- > 0) return;

  p_actwk->u.obj.actfree.iwa.push_timer = 16;
  if (p_actwk->u.obj.actfree.iwa.push_distance != 0) {
    --p_actwk->u.obj.actfree.iwa.push_distance;
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 1);
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 1);
    SKC_dircol_result result = emycol_d(p_actwk);
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    if (p_actwk->u.obj.flagwork_index != 0) {
      g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1] = -(p_actwk->u.obj.actfree.iwa.push_distance - 64);
      SET_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
  }
}


static void iwabreakgosub(SKC_sprite_status* p_actwk) {
  if (get_zone(g_ram.stageno) == LAVA_REEF) {
    iwabreakgosub3(p_actwk);
  }
  else {
    iwabreakgosub2(p_actwk, iwaspdtbl[p_actwk->patno], p_actwk->patno);
  }
}


static void iwabreakgosub2(SKC_sprite_status* p_actwk, SKC_speed* p_speed_data, unsigned char size_type) {
  SKC_iwa_break_data* p_break_data = iwabreaktbl[size_type];
  SKC_sprite_status* p_new_actwk = p_actwk;
  unsigned char patno = 3;

  for (int i = 0; i < p_break_data->cnt + 1; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
    }
    p_new_actwk->r_ptr = p_actwk->r_ptr;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->actflg = p_actwk->actflg;
    fp16_set_integer(&p_new_actwk->xposi, p_break_data->data[i].xoffset + fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&p_new_actwk->yposi, p_break_data->data[i].yoffset + fp16_get_integer(p_actwk->yposi));
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->sproffset |= 0x8000;
    p_new_actwk->sprpri = PRI_1;
    p_new_actwk->sprhs = 24;
    p_new_actwk->sprvs = 24;
    p_new_actwk->xspeed = p_speed_data[i].xspeed;
    p_new_actwk->yspeed = p_speed_data[i].yspeed;
    p_new_actwk->patno = patno;
    ++patno;
    if (patno >= 7) {
      patno = 3;
    }
  };

  soundset(89);
}


static void iwabreakgosub3(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &iwamove22;
  iwabreakgosub4(p_actwk, iwaspdtbl[p_actwk->patno - 4], p_actwk->patno - 4);
}


static void iwabreakgosub4(SKC_sprite_status* p_actwk, SKC_speed* p_speed_data, unsigned char size_type) {
  SKC_lrz_iwa_break_data* p_break_data = iwabreaktbl[size_type];
  SKC_sprite_status* p_new_actwk = p_actwk;

  for (int i = 0; i < p_break_data->cnt + 1; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
    }

    p_new_actwk->r_ptr = p_actwk->r_ptr;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->actflg = p_actwk->actflg;
    fp16_set_integer(&p_new_actwk->xposi, p_break_data->data[i].xoffset + fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&p_new_actwk->yposi, p_break_data->data[i].yoffset + fp16_get_integer(p_actwk->yposi));
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->sproffset |= 0x8000;
    p_new_actwk->sprpri = PRI_1;
    p_new_actwk->sprhs = 32;
    p_new_actwk->sprvs = 32;
    p_new_actwk->xspeed = p_speed_data[i].xspeed;
    p_new_actwk->yspeed = p_speed_data[i].yspeed;
    p_new_actwk->patno = p_break_data->data[i].patno;
    p_actwk->u.obj.actfree.iwa.size_type = p_new_actwk->patno & 0xFC;
    p_new_actwk->pattim = 7;
  }

  soundset(89);
}


static void* iwabreaktbl[8] = {
  &iwabreaktbl0,
  &iwabreaktbl1,
  &iwabreaktbl2,
  &iwabreaktbl3,
  &iwabreaktbl4,
  &iwabreaktbl5,
  &iwabreaktbl5,
  &iwabreaktbl7
};


static SKC_iwa_break_data iwabreaktbl0 = {
  7,
  {
    {  -8, -24 },
    {  11, -28 },
    {  -4, -12 },
    {  12,  -4 },
    { -12,   4 },
    {   4,  12 },
    { -12,  28 },
    {  12,  28 }
  }
};
static SKC_iwa_break_data iwabreaktbl1 = {
  4,
  {
    {  -4, -12 },
    {  11, -12 },
    {  -4,  -4 },
    { -12,  12 },
    {  12,  12 }
  }
};
static SKC_iwa_break_data iwabreaktbl2 = {
  3,
  {
    {  -4,  -4 },
    {  12,  -4 },
    { -12,   4 },
    {  12,   4 }
  }
};
static SKC_iwa_break_data iwabreaktbl3 = {
  5,
  {
    { -8,  -8 },
    {  8,  -8 },
    { -8,   0 },
    {  8,   0 },
    { -8,   8 },
    {  8,   8 }
  }
};
static SKC_lrz_iwa_break_data iwabreaktbl4 = {
  5,
  {
    {  0,  16, 6 },
    {  0,   0, 7 },
    { -8, -16, 1 },
    {  8,  32, 0 },
    {  0, -24, 6 },
    {  0,  27, 7 },
  }
};
static SKC_lrz_iwa_break_data iwabreaktbl5 = {
  5,
  {
    {   8,   3, 7 },
    {  -8,  -5, 1 },
    { -16,   8, 1 },
    { -24,   0, 7 },
    {   0,   0, 6 },
    {  24,   0, 6 }
  }
};
static SKC_lrz_iwa_break_data iwabreaktbl7 = {
  1,
  {
    { 0,  16, 1 },
    { 0, -16, 0 }
  }
};


static SKC_speed* iwaspdtbl[8] = {
  iwaspdtbl0,
  iwaspdtbl1,
  iwaspdtbl2,
  iwaspdtbl3,
  iwaspdtbl4,
  iwaspdtbl5,
  iwaspdtbl5,
  iwaspdtbl4
};


static SKC_speed iwaspdtbl0[8] = {
  { -0x300, -0x300 },
  { -0x2C0, -0x280 },
  { -0x2C0, -0x280 },
  { -0x280, -0x200 },
  { -0x280, -0x180 },
  { -0x240, -0x180 },
  { -0x240, -0x100 },
  { -0x200, -0x100 }
};
static SKC_speed iwaspdtbl01[8] = {
   { 0x2C0, -0x280 },
   { 0x300, -0x300 },
   { 0x280, -0x200 },
   { 0x2C0, -0x280 },
   { 0x240, -0x180 },
   { 0x280, -0x180 },
   { 0x200, -0x100 },
   { 0x240, -0x100 }
};
static SKC_speed iwaspdtbl1[5] = {
  { -0x200, -0x200 },
  {  0x200, -0x200 },
  { -0x100, -0x1E0 },
  { -0x1B0, -0x1C0 },
  {  0x1C0, -0x1C0 }
};
static SKC_speed iwaspdtbl2[4] = {
  { -0x100, -0x200 },
  {  0x100, -0x1E0 },
  { -0x1B0, -0x1C0 },
  {  0x1C0, -0x1C0 }
};
static SKC_speed iwaspdtbl3[6] = {
  { -0x0B0, -0x1E0 },
  {  0x0B0, -0x1D0 },
  { -0x080, -0x200 },
  {  0x080, -0x1E0 },
  { -0x0D8, -0x1C0 },
  {  0x0E0, -0x1C0 }
};
static SKC_speed iwaspdtbl30[6] = {
  { -0x2C0, -0x280 },
  { -0x280, -0x200 },
  { -0x280, -0x180 },
  { -0x240, -0x180 },
  { -0x240, -0x100 },
  { -0x200, -0x100 }
};
static SKC_speed iwaspdtbl31[6] = {
  { 0x2C0, -0x280 },
  { 0x280, -0x200 },
  { 0x280, -0x180 },
  { 0x240, -0x180 },
  { 0x240, -0x100 },
  { 0x200, -0x100 }
};
static SKC_speed iwaspdtbl4[8] = {
  { -0x300, -0x300 },
  { -0x2C0, -0x280 },
  { -0x2C0, -0x280 },
  { -0x280, -0x200 },
  { -0x280, -0x180 },
  { -0x240, -0x180 },
  { -0x240, -0x100 },
  { -0x200, -0x100 }
};
static SKC_speed iwaspdtbl5[6] = {
  {  0x0C0, -0x1E0 },
  { -0x080, -0x1A0 },
  { -0x0A0, -0x160 },
  { -0x100, -0x1E0 },
  {  0x040, -0x1C0 },
  {  0x100, -0x1E0 }
};


SKC_sprite_pattern* iwapat[7] = {
  &iwasp00,
  &iwasp01,
  &iwasp02,
  &iwasp03,
  &iwasp04,
  &iwasp05,
  &iwasp06
};


static SKC_sprite_pattern iwasp00 = {
  6,
  {
    { -40, 11, 0x0000, -24 },
    { -40, 11, 0x000C,   0 },
    {  -8, 11, 0x0018, -24 },
    {  -8, 11, 0x0024,   0 },
    {  24,  9, 0x0030, -24 },
    {  24,  9, 0x0036,   0 }
  }
};
static SKC_sprite_pattern iwasp01 = {
  4,
  {
    { -24, 11, 0x0000, -24 },
    { -24, 11, 0x000C,   0 },
    {   8,  9, 0x003C, -24 },
    {   8,  9, 0x0042,   0 }
  }
};
static SKC_sprite_pattern iwasp02 = {
  4,
  {
    { -16, 9, 0x0048, -16 },
    { -16, 5, 0x004E,   8 },
    {   0, 9, 0x003C, -24 },
    {   0, 9, 0x0042,   0 }
  }
};
static SKC_sprite_pattern iwasp03 = {
  1,
  {
    { -12, 10, 0x0052, -12 }
  }
};
static SKC_sprite_pattern iwasp04 = {
  1,
  {
    { -12, 10, 0x005B, -12 }
  }
};
static SKC_sprite_pattern iwasp05 = {
  1,
  {
    { -14, 10, 0x0852, -12 }
  }
};
static SKC_sprite_pattern iwasp06 = {
  1,
  {
    { -12, 10, 0x85B, -12 }
  }
};


SKC_sprite_pattern* iwapat2[7] = {
  &iwasp200,
  &iwasp201,
  &iwasp202,
  &iwasp203,
  &iwasp204,
  &iwasp205,
  &iwasp206
};


static SKC_sprite_pattern iwasp200 = {
  6,
  {
    { -40, 11, 0x0072, -24 },
    { -40, 11, 0x007E,   0 },
    {  -8, 11, 0x008A, -24 },
    {  -8, 11, 0x0096,   0 },
    {  24,  9, 0x00A2, -24 },
    {  24,  9, 0x00A8,   0 }
  }
};
static SKC_sprite_pattern iwasp201 = {
  4,
  {
    { -24, 11, 0x0072, -24 },
    { -24, 11, 0x007E,   0 },
    {   8,  9, 0x00AE, -24 },
    {   8,  9, 0x00B4,   0 }
  }
};
static SKC_sprite_pattern iwasp202 = {
  4,
  {
    { -16, 9, 0x00BA, -16 },
    { -16, 5, 0x00C0,   8 },
    {   0, 9, 0x00AE, -24 },
    {   0, 9, 0x00B4,   0 }
  }
};
static SKC_sprite_pattern iwasp203 = {
  1,
  {
    { -12, 10, 0x00C4, -12 }
  }
};
static SKC_sprite_pattern iwasp204 = {
  1,
  {
    { -12, 10, 0x00CD, -12 }
  }
};
static SKC_sprite_pattern iwasp205 = {
  1,
  {
    { -14, 10, 0x08C4, -12 }
  }
};
static SKC_sprite_pattern iwasp206 = {
  1,
  {
    { -12, 10, 0x08CD, -12 }
  }
};


SKC_sprite_pattern* vsiwapat[8] = {
  &vsiwasp00,
  &vsiwasp01,
  &vsiwasp02,
  &vsiwasp01,
  &vsiwasp02,
  &vsiwasp01,
  &vsiwasp02,
  &vsiwasp03
};


static SKC_sprite_pattern vsiwasp00 = {
  1,
  {
    { -16, 15, 0x000E, -16 }
  }
};
static SKC_sprite_pattern vsiwasp01 = {
  1,
  {
    { -8, 5, 0x001E, -8 }
  }
};
static SKC_sprite_pattern vsiwasp02 = {
  1,
  {
    { -8, 5, 0x0022, -5 }
  }
};
static SKC_sprite_pattern vsiwasp03 = {
  1,
  {
    { -4, 0, 0xFD00, -4 }
  }
};


SKC_sprite_pattern* iwapat9[11] = {
  &iwasp900,
  &iwasp901,
  &iwasp902,
  &iwasp903,
  &iwasp904,
  &iwasp905,
  &iwasp906,
  &iwasp907,
  &iwasp908,
  &iwasp909,
  &iwasp909
};


static SKC_sprite_pattern iwasp900 = {
  1,
  {
    { -8, 5, 0x006D, -8 }
  }
};
static SKC_sprite_pattern iwasp901 = {
  1,
  {
    { -8, 5, 0x086D, -8 }
  }
};
static SKC_sprite_pattern iwasp902 = {
  1,
  {
    { -8, 5, 0x186D, -8 }
  }
};
static SKC_sprite_pattern iwasp903 = {
  1,
  {
    { -8, 5, 0x106D, -8 }
  }
};
static SKC_sprite_pattern iwasp904 = {
  1,
  {
    { -16, 15, 0x0071, -16 }
  }
};
static SKC_sprite_pattern iwasp905 = {
  1,
  {
    { -16, 15, 0x0871, -16 }
  }
};
static SKC_sprite_pattern iwasp906 = {
  1,
  {
    { -16, 15, 0x1871, -16 }
  }
};
static SKC_sprite_pattern iwasp907 = {
  1,
  {
    { -16, 15, 0x1071, -16 }
  }
};
static SKC_sprite_pattern iwasp908 = {
  6,
  {
    {   0, 15, 0x1871, -16 },
    { -16, 15, 0x1071, -16 },
    { -24,  5, 0x086D, -16 },
    { -40, 15, 0x1871, -16 },
    {  24,  5, 0x006D,   0 },
    {  11, 15, 0x1071, -16 }
  }
};
static SKC_sprite_pattern iwasp909 = {
  6,
  {
    { -13, 15, 0x1071,  -8 },
    { -13,  5, 0x086D, -16 },
    {   0,  5, 0x086D, -24 },
    { -16, 15, 0x1071, -40 },
    { -16, 15, 0x1871, -16 },
    { -16, 15, 0x1871,   8 }
  }
};


SKC_sprite_pattern* iwapat92[12] = {
  &iwasp920,
  &iwasp921,
  &iwasp922,
  &iwasp923,
  &iwasp920,
  &iwasp921,
  &iwasp922,
  &iwasp923,
  &iwasp928,
  &iwasp929,
  &iwasp929,
  &iwasp928
};


static SKC_sprite_pattern iwasp920_iwasp924 = {
  2,
  {
    { -16, 13, 0x0000, -16 },
    {   0, 13, 0x0008, -16 }
  }
};
static SKC_sprite_pattern iwasp921 = {
  2,
  {
    { -16, 13, 0x0800, -16 },
    {   0, 13, 0x0808, -16 }
  }
};
static SKC_sprite_pattern iwasp922 = {
  2,
  {
    { -16, 13, 0x1808, -16 },
    {   0, 13, 0x1800, -16 }
  }
};
static SKC_sprite_pattern iwasp923 = {
  2,
  {
    { -16, 13, 0x1008, -16 },
    {   0, 13, 0x1000, -16 }
  }
};
static SKC_sprite_pattern iwasp928 = {
  4,
  {
    { -32, 13, 0x0000, -16 },
    { -16, 13, 0x0008, -16 },
    {   0, 13, 0x0800, -16 },
    {  16, 13, 0x0808, -16 }
  }
};
static SKC_sprite_pattern iwasp929 = {
  4,
  {
    { -16, 13, 0x0000, -32 },
    { -16, 13, 0x1008,   0 },
    {   0, 13, 0x0008, -32 },
    {   0, 13, 0x1000,   0 }
  }
};
