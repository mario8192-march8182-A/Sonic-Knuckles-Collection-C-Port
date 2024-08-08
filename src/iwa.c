#include "globals.h"
#include "macros.h"
#include "util.h"
#include "types/hitchkdata.h"
#include "types/hitchkresults.h"
#include "types/iwabreakdata.h"
#include "iwa.h"
#include "004xxxxx.h"
#include "hitchk.h"
static unsigned char iwainittbl[16];
static void iwainit(sprite_status* p_actwk);
static void iwamove(sprite_status* p_actwk);
static void iwamove__end(sprite_status* p_actwk);
static void iwamove__jump(sprite_status* p_actwk);
static void iwamove__sub2(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char plmstno);
static void iwamove__sub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void iwamove__sub1(sprite_status* p_actwk, sprite_status* p_playerwk);
static void iwamove__jump2(sprite_status* p_actwk);
static void iwamove__jump3(sprite_status* p_actwk);
static void iwamove2(sprite_status* p_actwk);
static void iwamove20(sprite_status* p_actwk);
static void iwamove21(sprite_status* p_actwk);
static void iwamove22(sprite_status* p_actwk);
static void vsiwamove(sprite_status* p_actwk);
static void vsiwamove2(sprite_status* p_actwk);
static void vsiwasub(sprite_status* p_actwk);
static void vsiwamove3(sprite_status* p_actwk);
static void iwamove3(sprite_status* p_actwk);
static void iwamove3__break(sprite_status* p_actwk, sprite_status* p_playerwk, short xspeed);
static void iwamove3__ridechk(sprite_status* p_actwk);
static void iwamove4(sprite_status* p_actwk);
static void iwamovek(sprite_status* p_actwk);
static void iwamovek__sub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void iwamovek__jump3(sprite_status* p_actwk, sprite_status* p_playerwk);
static void iwamovepush(sprite_status* p_actwk);
static void iwamovepush__sub(sprite_status* p_actwk, sprite_status* p_playerwk, short xposi, unsigned char plcddat1, unsigned char plpushbit);
static void iwabreakgosub(sprite_status* p_actwk);
static void iwabreakgosub2(sprite_status* p_actwk, short* p_speed_data, unsigned char offset);
static void iwabreakgosub3(sprite_status* p_actwk);
static void iwabreakgosub4(sprite_status* p_actwk, short* p_speed_data, unsigned char offset);
static iwabreak_data* iwabreaktbl[8];
static iwabreak_data iwabreaktbl0;
static iwabreak_data iwabreaktbl1;
static iwabreak_data iwabreaktbl2;
static iwabreak_data iwabreaktbl3;
static iwabreak_data iwabreaktbl4;
static iwabreak_data iwabreaktbl5;
static iwabreak_data iwabreaktbl7;
static short* iwaspdtbl[8];
static short iwaspdtbl0[16];
static short iwaspdtbl01[16];
static short iwaspdtbl1[10];
static short iwaspdtbl2[8];
static short iwaspdtbl3[12];
static short iwaspdtbl30[12];
static short iwaspdtbl31[12];
static short iwaspdtbl4[16];
static short iwaspdtbl5[12];
static signed char iwasp00[38];
static signed char iwasp01[26];
static signed char iwasp02[26];
static signed char iwasp03[8];
static signed char iwasp04[8];
static signed char iwasp05[8];
static signed char iwasp06[8];
static signed char iwasp200[38];
static signed char iwasp201[26];
static signed char iwasp202[26];
static signed char iwasp203[8];
static signed char iwasp204[8];
static signed char iwasp205[8];
static signed char iwasp206[8];
static signed char vsiwasp00[8];
static signed char vsiwasp01[8];
static signed char vsiwasp02[8];
static signed char vsiwasp03[8];
static signed char iwasp900[8];
static signed char iwasp901[8];
static signed char iwasp902[8];
static signed char iwasp903[8];
static signed char iwasp904[8];
static signed char iwasp905[8];
static signed char iwasp906[8];
static signed char iwasp907[8];
static signed char iwasp908[38];
static signed char iwasp909[38];
static signed char iwasp920_iwasp924[14];
static signed char iwasp921_iwasp925[14];
static signed char iwasp922_iwasp926[14];
static signed char iwasp923_iwasp927[14];
static signed char iwasp928[26];
static signed char iwasp929[28];


static unsigned char iwainittbl[16] = {
  24, 39, 24, 23, 24, 15, 14, 15, 16, 40, 40, 16, 40, 16, 16, 32
};


void iwa_vsiwa(sprite_status* p_actwk) {
  iwainit(p_actwk);
}


static void iwainit(sprite_status* p_actwk) {
  unsigned char userflag = p_actwk->userflag1 / 16 & 7;
  p_actwk->patno = userflag;
  userflag *= 2;
  p_actwk->sprhs = iwainittbl[userflag];
  p_actwk->sprvsize = p_actwk->sprvs = iwainittbl[userflag + 1];
  p_actwk->patbase = iwapat;
  p_actwk->sproffset = 9011;
  SET_USE_LEVEL_COORDS(p_actwk->actflg);
  p_actwk->sprpri = PRI_4;
  p_actwk->actfree.iwa.orig_xposi = LONG_HIGH(p_actwk->xposi);
  p_actwk->actfree.iwa.countdown2 = 64;
  if (stageno.act == 1) {
    p_actwk->patbase = iwapat2;
    p_actwk->sproffset = 17129;
  }
  if (stageno.zone == ENDLESS_MINE && stageno.act == 0) {
    p_actwk->patbase = vsiwapat;
    p_actwk->sproffset = 58112;
    p_actwk->patno = 0;
  }
  if (stageno.zone == LAVA_REEF) {
    p_actwk->patbase = iwapat9;
    p_actwk->sproffset = 16595;
    p_actwk->patno += 4;
    if (stageno.act != 0) {
      p_actwk->patbase = iwapat92;
      p_actwk->sproffset = 25613;
    }
  }
  if ((p_actwk->userflag1 & 0xF) == 15) {
    p_actwk->r_ptr = &iwamovek;
    iwamovek(p_actwk);
  }
  else {
    p_actwk->r_ptr = &iwamove;
    if (BIT_2_IS_SET(p_actwk->userflag1)) {
      p_actwk->r_ptr = &iwamove3;
      iwamove3(p_actwk);
    }
    else if (BIT_3_IS_SET(p_actwk->userflag1)) {
      p_actwk->r_ptr = &iwamove4;
      iwamove4(p_actwk);
    }
    else {
      if (p_actwk->actfree.iwa.flagwork_index != 0) {
        unsigned char flag = flagwork[p_actwk->actfree.iwa.flagwork_index - 1];
        if (flag & 0x7F) {
          p_actwk->xposi -= SHORT_TO_LONG_HIGH(flag);
          short flag_s = flag;
          p_actwk->actfree.iwa.countdown2 = -flag_s + 64;
          short unknown = ObjCheckFloorDist(p_actwk);
          p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown);
        }
      }
      iwamove(p_actwk);
    }
  }
}


static void iwamove(sprite_status* p_actwk) {
  p_actwk->actfree.iwa.emyscorecnt = emyscorecnt;
  p_actwk->actfree.iwa.plmstno = actwk[0].mstno;
  p_actwk->actfree.iwa.pl2mstno = actwk[1].mstno;
  p_actwk->actfree.iwa.plcddat1 = actwk[0].cddat1;
  p_actwk->actfree.iwa.pl2cddat1 = actwk[1].cddat1;
  hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  if (BIT_1_IS_SET(p_actwk->userflag1)) {
    iwamovepush(p_actwk);
  }
  if (BIT_0_IS_SET(p_actwk->userflag1)) {
    if (p_actwk->cddat1 & 0x18) {
      iwamove__jump(p_actwk);
      return;
    }
  }
  iwamove__end(p_actwk);
}


static void iwamove__end(sprite_status* p_actwk) {
  if (vs_flag == 0) {
    frameoutchk2(p_actwk, p_actwk->actfree.iwa.orig_xposi);
  }
  else {
    actionsub(p_actwk);
  }
}


static void iwamove__jump(sprite_status* p_actwk) {
  if ((p_actwk->cddat1 & 0x18) == 24) {
    if (p_actwk->actfree.iwa.plmstno != 2
        && p_actwk->actfree.iwa.pl2mstno != 2) {
      iwamove__end(p_actwk);
      return;
    }
    iwamove__sub2(p_actwk, &actwk[0], p_actwk->actfree.iwa.plmstno);
    iwamove__sub2(p_actwk, &actwk[1], p_actwk->actfree.iwa.pl2mstno);
  }
  else {
    if (!BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
      iwamove__jump2(p_actwk);
      return;
    }
    if (p_actwk->actfree.iwa.plmstno != 2) {
      iwamove__end(p_actwk);
      return;
    }
    iwamove__sub(p_actwk, &actwk[0]);
  }
  iwamove__jump3(p_actwk);
}


static void iwamove__sub2(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char plmstno) {
  if (plmstno != 2) {
    iwamove__sub1(p_actwk, p_playerwk);
  }
  else {
    iwamove__sub(p_actwk, p_playerwk);
  }
}


static void iwamove__sub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  SET_BIT(p_playerwk->cddat1, CD_BALL);
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->yspeed = -768;
  iwamove__sub1(p_actwk, p_playerwk);
}


static void iwamove__sub1(sprite_status* p_actwk, sprite_status* p_playerwk) {
  SET_BIT(p_playerwk->cddat1, CD_JUMP);
  CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
  p_playerwk->r_no = 2;
}


static void iwamove__jump2(sprite_status* p_actwk) {
  if (!BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)
      || p_actwk->actfree.iwa.pl2mstno != 2) {
    iwamove__end(p_actwk);
  }
  else {
    iwamove__sub(p_actwk, &actwk[1]);
    iwamove__jump3(p_actwk);
  }
}


static void iwamove__jump3(sprite_status* p_actwk) {
  emyscorecnt = p_actwk->actfree.iwa.emyscorecnt;
  p_actwk->cddat1 &= 0xE7;
  if (vs_flag != 0) {
    vsiwamove(p_actwk);
  }
  else {
    p_actwk->r_ptr = &iwamove2;
    iwabreakgosub(p_actwk);
    iwamove2(p_actwk);
  }
}


static void iwamove2(sprite_status* p_actwk) {
  if (stageno.zone == LAVA_REEF) {
    iwamove21(p_actwk);
  }
  else {
    p_actwk->r_ptr = &iwamove20;
    iwamove20(p_actwk);
  }
}


static void iwamove20(sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (util__to_signed(p_actwk->pattim) < 0) {
    p_actwk->pattim = 2;
    unsigned char patno = p_actwk->patno + 1;
    if (patno >= 7) {
      patno = 3;
    }
    p_actwk->patno = patno;
  }
  speedset2(p_actwk);
  p_actwk->yspeed += 24;
  if (!IS_ONSCREEN(p_actwk->actflg)) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void iwamove21(sprite_status* p_actwk) {
  p_actwk->r_ptr = &iwamove22;
  iwamove22(p_actwk);
}


static void iwamove22(sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (util__to_signed(p_actwk->pattim) < 0) {
    p_actwk->pattim = 7;
    p_actwk->patno = (p_actwk->patno + 1 & 3) + p_actwk->actfree.iwa.patno_part;
  }
  speedset2(p_actwk);
  p_actwk->yspeed += 24;
  if (!IS_ONSCREEN(p_actwk->actflg)) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void vsiwamove(sprite_status* p_actwk) {
  vsiwasub(p_actwk);
  p_actwk->patno = 3;
  p_actwk->r_ptr = &vsiwamove2;
  iwabreakgosub(p_actwk);
  vsiwamove2(p_actwk);
}


static void vsiwamove2(sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += SHORT_TO_LONG_HIGH(24);
  if (!IS_ONSCREEN(p_actwk->actflg)) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void vsiwasub(sprite_status* p_actwk) {
  short slot_cnt;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
  if (!created) return;
  *p_new_actwk = *p_actwk;
  p_new_actwk->actfree.iwa.parent_r_ptr = p_actwk->r_ptr;
  p_new_actwk->r_ptr = &vsiwamove3;
  p_new_actwk->patno = 7;
}


static void vsiwamove3(sprite_status* p_actwk) {
  if (!IS_ONSCREEN(p_actwk->actflg)) {
    p_actwk->r_ptr = p_actwk->actfree.iwa.parent_r_ptr;
    p_actwk->patno = 0;
  }
  actionsub(p_actwk);
}


static void iwamove3(sprite_status* p_actwk) {
  p_actwk->actfree.iwa.plspeed = actwk[0].xspeed;
  p_actwk->actfree.iwa.pl2speed = actwk[1].xspeed;
  hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk_results results = hitchk(p_actwk, data);
  if (results.plcoli & 3) goto jump;

end:
  if (vs_flag == 0) {
    frameoutchk2(p_actwk, p_actwk->actfree.iwa.orig_xposi);
  }
  else {
    actionsub(p_actwk);
  }
  return;

jump:
  if (!BIT_0_IS_SET(results.plcoli)) goto jump2;
  if (BIT_7_IS_SET(p_actwk->userflag1)) {
    if (actwk[0].actfree.player.character == KNUCKLES) goto brgo;
    goto jump2;
  }
  if (ssonicflag != 0 || actwk[0].actfree.player.character == KNUCKLES) {
    goto brgo;
  }
  if ((!BIT_4_IS_SET(actwk[0].cddat2) && !BIT_IS_SET(p_actwk->cddat1, CD_PLPUSH))
      || actwk[0].mstno != 2) {
    goto jump2;
  }
  short xspeed = p_actwk->actfree.iwa.plspeed;
  if (xspeed < 0) {
    xspeed = -xspeed;
  }
  if (util__to_unsigned(xspeed) < 1152) goto jump2;

brgo:
  CLEAR_BIT(p_actwk->cddat1, CD_PLPUSH);
  iwamove3__break(p_actwk, &actwk[0], p_actwk->actfree.iwa.plspeed);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PL2PUSH)
      && (actwk[1].actfree.player.character == KNUCKLES || actwk[1].mstno == 2)) {
    actwk[1].mspeed = actwk[1].xspeed = p_actwk->actfree.iwa.pl2speed;
    CLEAR_BIT(p_actwk->cddat1, CD_PL2PUSH);
    CLEAR_BIT(p_actwk->cddat1, CD_PUSH);
  }
  goto end;

jump2:
  if (!BIT_IS_SET(p_actwk->cddat1, CD_PL2PUSH)) goto end;
  if (BIT_7_IS_SET(p_actwk->userflag1)) {
    if (actwk[1].actfree.player.character != KNUCKLES) goto end;
  }
  else if (actwk[1].actfree.player.character != KNUCKLES) {
    if (actwk[1].mstno != 2) goto end;
    short xspeed = p_actwk->actfree.iwa.pl2speed;
    if (xspeed < 0) {
      xspeed = -xspeed;
    }
    if (xspeed < 1152) goto end;
  }
  CLEAR_BIT(p_actwk->cddat1, CD_PL2PUSH);
  iwamove3__break(p_actwk, &actwk[1], p_actwk->actfree.iwa.pl2speed);
}


static void iwamove3__break(sprite_status* p_actwk, sprite_status* p_playerwk, short xspeed) {
  iwamove3__ridechk(p_actwk);
  if (vs_flag == 0) {
    p_playerwk->xspeed = xspeed;
    p_playerwk->xposi += SHORT_TO_LONG_HIGH(4);
    short* p_speed_data = iwaspdtbl0;
    if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) >= util__to_unsigned(LONG_HIGH(p_playerwk->xposi))) { // unsigned
      p_playerwk->xposi -= SHORT_TO_LONG_HIGH(8);
      p_speed_data = iwaspdtbl01;
    }
    p_playerwk->mspeed = p_playerwk->xspeed;
    CLEAR_BIT(p_playerwk->cddat1, CD_PUSH);
    if (p_playerwk->actfree.player.character == KNUCKLES
        && p_playerwk->actfree.player.talent_status == 1) {
      p_playerwk->actfree.player.talent_status = 2;
      p_playerwk->mstno = 33;
      CLEAR_BIT(p_playerwk->cddat1, CD_LEFT);
      if (p_playerwk->xspeed < 0) {
        SET_BIT(p_playerwk->cddat1, CD_LEFT);
      }
    }
    if (stageno.zone == LAVA_REEF) {
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
    p_playerwk->xspeed = xspeed;
    p_playerwk->xposi += SHORT_TO_LONG_HIGH(4);
    short* p_speed_data = iwaspdtbl30;
    if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) >= util__to_unsigned(LONG_HIGH(p_playerwk->xposi))) { // unsigned
      p_playerwk->xposi -= SHORT_TO_LONG_HIGH(8);
      p_speed_data = iwaspdtbl31;
    }
    p_playerwk->mspeed = p_playerwk->xspeed;
    CLEAR_BIT(p_playerwk->cddat1, CD_PUSH);
    vsiwasub(p_actwk);
    p_actwk->r_ptr = &vsiwamove2;
    p_actwk->patno = 3;
    iwabreakgosub2(p_actwk, p_speed_data, p_actwk->patno);
    vsiwamove2(p_actwk);
  }
}


static void iwamove3__ridechk(sprite_status* p_actwk) {
  bool plride_set = BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE);
  CLEAR_BIT(p_actwk->cddat1, CD_PLRIDE);
  if (plride_set) {
    SET_BIT(actwk[0].cddat1, CD_JUMP);
    CLEAR_BIT(actwk[0].cddat1, CD_RIDE);
  }
  plride_set = BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE);
  CLEAR_BIT(p_actwk->cddat1, CD_PL2RIDE);
  if (plride_set) {
    SET_BIT(actwk[1].cddat1, CD_JUMP);
    CLEAR_BIT(actwk[1].cddat1, CD_RIDE);
  }
}


static void iwamove4(sprite_status* p_actwk) {
  p_actwk->actfree.iwa.plspeed = actwk[0].yspeed;
  p_actwk->actfree.iwa.pl2speed = actwk[1].yspeed;
  hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk_results results = hitchk(p_actwk, data);
  if (!(results.plcoli & 0xC)) {
    frameoutchk2(p_actwk, p_actwk->actfree.iwa.orig_xposi);
    return;
  }
  if (BIT_2_IS_SET(results.plcoli)) {
    actwk[0].yspeed = p_actwk->actfree.iwa.plspeed;
    if (BIT_3_IS_SET(results.plcoli)) {
      actwk[1].yspeed = p_actwk->actfree.iwa.pl2speed;
    }
  }
  else {
    if (BIT_3_IS_SET(results.plcoli)) {
      actwk[1].yspeed = p_actwk->actfree.iwa.pl2speed;
    }
    else {
      frameoutchk2(p_actwk, p_actwk->actfree.iwa.orig_xposi);
      return;
    }
  }
  if (BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
    SET_BIT(actwk[0].cddat1, CD_JUMP);
    CLEAR_BIT(actwk[0].cddat1, CD_RIDE);
  }
  if (BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)) {
    SET_BIT(actwk[1].cddat1, CD_JUMP);
    CLEAR_BIT(actwk[1].cddat1, CD_RIDE);
  }
  p_actwk->r_ptr = &iwamove2;
  iwabreakgosub(p_actwk);
  iwamove2(p_actwk);
}


static void iwamovek(sprite_status* p_actwk) {
  p_actwk->actfree.iwa.emyscorecnt = emyscorecnt;
  hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  if (!BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)
      || actwk[0].actfree.player.character != KNUCKLES) {
    frameoutchk(p_actwk);
    return;
  }
  iwamovek__sub(p_actwk, &actwk[0]);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)) {
    iwamovek__sub(p_actwk, &actwk[1]);
  }
  iwamovek__jump3(p_actwk, &actwk[1]);
}


static void iwamovek__sub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  SET_BIT(p_playerwk->cddat1, CD_BALL);
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->yspeed = -768;
  SET_BIT(p_playerwk->cddat1, CD_JUMP);
  CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
  p_playerwk->r_no = 2;
}


static void iwamovek__jump3(sprite_status* p_actwk, sprite_status* p_playerwk) {
  emyscorecnt = p_actwk->actfree.iwa.emyscorecnt;
  p_playerwk->cddat1 &= 0xE7;
  p_playerwk->r_ptr = &iwamove2;
  iwabreakgosub(p_actwk);
  iwamove2(p_actwk);
}


static void iwamovepush(sprite_status* p_actwk) {
  if (!(p_actwk->cddat1 & 0x60)) return;
  iwamovepush__sub(p_actwk, &actwk[0], LONG_HIGH(p_actwk->xposi), p_actwk->actfree.iwa.plcddat1, 5);
  iwamovepush__sub(p_actwk, &actwk[1], LONG_HIGH(p_actwk->xposi), p_actwk->actfree.iwa.pl2cddat1, 6);
}


static void iwamovepush__sub(sprite_status* p_actwk, sprite_status* p_playerwk, short xposi, unsigned char plcddat1, unsigned char plpushbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, plpushbit)) return;
  if (xposi >= LONG_HIGH(p_playerwk->xposi)) return; // unsigned
  if (!BIT_IS_SET(plcddat1, CD_PUSH)) return;
  --p_actwk->actfree.iwa.countdown;
  if (p_actwk->actfree.iwa.countdown < 0) return;
  p_actwk->actfree.iwa.countdown = 16;
  if (p_actwk->actfree.iwa.countdown2 == 0) return;
  --p_actwk->actfree.iwa.countdown2;
  p_actwk->xposi -= SHORT_TO_LONG_HIGH(1);
  p_playerwk->xposi -= SHORT_TO_LONG_HIGH(1);
  short unknown = ObjCheckFloorDist(p_actwk);
  p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown);
  if (p_actwk->actfree.iwa.flagwork_index != 0) {
    short flag_s = p_actwk->actfree.iwa.countdown2;
    flag_s = -(flag_s - 64);
    flagwork[p_actwk->actfree.iwa.flagwork_index - 1] = flag_s;
    SET_BIT_7(flagwork[p_actwk->actfree.iwa.flagwork_index - 1]);
  }
}


static void iwabreakgosub(sprite_status* p_actwk) {
  if (stageno.zone == LAVA_REEF) {
    iwabreakgosub3(p_actwk);
  }
  else {
    iwabreakgosub2(p_actwk, iwaspdtbl[p_actwk->patno], p_actwk->patno);
  }
}


static void iwabreakgosub2(sprite_status* p_actwk, short* p_speed_data, unsigned char offset) {
  short cnt = iwabreaktbl[offset]->cnt;
  signed char* p_data = iwabreaktbl[offset]->data;
  unsigned char patno = 3;
  sprite_status* p_new_actwk = p_actwk;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) break;

jump:
    p_new_actwk->r_ptr = p_actwk->r_ptr;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->actflg = p_actwk->actflg;
    short xposi = *p_data++ + LONG_HIGH(p_actwk->xposi);
    util__assign_high(&p_new_actwk->xposi, xposi);
    short yposi = *p_data++ + LONG_HIGH(p_actwk->yposi);
    util__assign_high(&p_new_actwk->yposi, yposi);
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->sproffset |= 0x8000;
    p_new_actwk->sprpri = PRI_1;
    p_new_actwk->sprhs = 24;
    p_new_actwk->xspeed = *p_speed_data++;
    p_new_actwk->yspeed = *p_speed_data++;
    p_new_actwk->patno = patno;
    ++patno;
    if (patno >= 7) {
      patno = 3;
    }
    --cnt;
  } while (cnt != -1);
  soundset(89);
}


static void iwabreakgosub3(sprite_status* p_actwk) {
  p_actwk->r_ptr = &iwamove22;
  iwabreakgosub4(p_actwk, iwaspdtbl[p_actwk->patno - 4], p_actwk->patno - 4);
}


static void iwabreakgosub4(sprite_status* p_actwk, short* p_speed_data, unsigned char offset) {
  short cnt = iwabreaktbl[offset]->cnt;
  signed char* p_data = iwabreaktbl[offset]->data;
  unsigned char patno = 3;
  sprite_status* p_new_actwk = p_actwk;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) break;

jump:
    p_new_actwk->r_ptr = p_actwk->r_ptr;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->actflg = p_actwk->actflg;
    short xposi = *p_data++ + LONG_HIGH(p_actwk->xposi);
    util__assign_high(&p_new_actwk->xposi, xposi);
    short yposi = *p_data++ + LONG_HIGH(p_actwk->yposi);
    util__assign_high(&p_new_actwk->yposi, yposi);
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->sproffset |= 0x8000;
    p_new_actwk->sprpri = PRI_1;
    p_new_actwk->sprhs = 32;
    p_new_actwk->sprhs = 32;
    p_new_actwk->xspeed = *p_speed_data++;
    p_new_actwk->yspeed = *p_speed_data++;
    p_new_actwk->patno = *p_data++;
    p_actwk->actfree.iwa.patno_part = p_new_actwk->patno & 0xFC;
    p_new_actwk->pattim = 7;
    --cnt;
  } while (cnt != -1);
  soundset(89);
}


static iwabreak_data* iwabreaktbl[8] = {
  &iwabreaktbl0,
  &iwabreaktbl1,
  &iwabreaktbl2,
  &iwabreaktbl3,
  &iwabreaktbl4,
  &iwabreaktbl5,
  &iwabreaktbl5,

};


static iwabreak_data iwabreaktbl0 = {
  7,
  {
     -8, -24,
     11, -28,
     -4, -12,
     12,  -4,
    -12,   4,
      4,  12,
    -12,  28,
     12,  28
  }
};
static iwabreak_data iwabreaktbl1 = {
  4,
  {
     -4, -12,
     11, -12,
     -4,  -4,
    -12,  12,
     12,  12
  }
};
static iwabreak_data iwabreaktbl2 = {
  3,
  {
     -4,  -4,
     12,  -4,
    -12,   4,
     12,   4
  }
};
static iwabreak_data iwabreaktbl3 = {
  5,
  {
     -8,  -8,
      8,  -8,
     -8,   0,
      8,   0,
     -8,   8,
      8,   8
  }
};
static iwabreak_data iwabreaktbl4 = {
  5,
  {
      0,  16, 6,
      0,   0, 7,
     -8, -16, 1,
      8,  32, 0,
      0, -24, 6,
      0,  27, 7,
  }
};
static iwabreak_data iwabreaktbl5 = {
  5,
  {
      8,   3, 7,
     -8,  -5, 1,
    -16,   8, 1,
    -24,   0, 7,
      0,   0, 6,
     24,   0, 6
  }
};
static iwabreak_data iwabreaktbl7 = {
  1,
  {
      0,  16, 1,
      0, -16, 0
  }
};


static short* iwaspdtbl[8] = {
  iwaspdtbl0,
  iwaspdtbl1,
  iwaspdtbl2,
  iwaspdtbl3,
  iwaspdtbl4,
  iwaspdtbl5,
  iwaspdtbl5,
  iwaspdtbl4
};


static short iwaspdtbl0[16] = {
  -768, -768,
  -704, -640,
  -704, -640,
  -640, -512,
  -640, -384,
  -576, -384,
  -576, -256,
  -512, -256
};
static short iwaspdtbl01[16] = {
   704, -640,
   768, -768,
   640, -512,
   704, -640,
   576, -384,
   640, -384,
   512, -256,
   576, -256
};
static short iwaspdtbl1[10] = {
  -512, -512,
   512, -512,
  -256, -480,
  -432, -448,
   448, -448
};
static short iwaspdtbl2[8] = {
  -256, -512,
   256, -480,
  -432, -448,
   448, -448
};
static short iwaspdtbl3[12] = {
  -176, -480,
   176, -464,
  -128, -512,
   128, -480,
  -216, -448,
   224, -448
};
static short iwaspdtbl30[12] = {
  -704, -640,
  -640, -512,
  -640, -384,
  -576, -384,
  -576, -256,
  -512, -256
};
static short iwaspdtbl31[12] = {
  704, -640,
  640, -512,
  640, -384,
  576, -384,
  576, -256,
  512, -256
};
static short iwaspdtbl4[16] = {
  -768, -768,
  -704, -640,
  -704, -640,
  -640, -512,
  -640, -384,
  -576, -384,
  -576, -256,
  -512, -256
};
static short iwaspdtbl5[12] = {
   192, -480,
  -128, -416,
  -160, -352,
  -256, -480,
    64, -448,
   256, -480
};


signed char* iwapat[7] = {
  iwasp00,
  iwasp01,
  iwasp02,
  iwasp03,
  iwasp04,
  iwasp05,
  iwasp06
};


static signed char iwasp00[38] = {
    0,   6, -40,  11,   0,   0, -24,  -1, -40,  11,
   12,   0,   0,   0,  -8,  11,  24,   0, -24,  -1,
   -8,  11,  36,   0,   0,   0,  24,   9,  48,   0,
  -24,  -1,  24,   9,  54,   0,   0,   0
};
static signed char iwasp01[26] = {
    0,   4, -24,  11,   0,   0, -24,  -1, -24,  11,
   12,   0,   0,   0,   8,   9,  60,   0, -24,  -1,
    8,   9,  66,   0,   0,   0
};
static signed char iwasp02[26] = {
    0,   4, -16,   9,  72,   0, -16,  -1, -16,   5,
   78,   0,   8,   0,   0,   9,  60,   0, -24,  -1,
    0,   9,  66,   0,   0,   0
};
static signed char iwasp03[8] = {
    0,   1, -12,  10,  82,   0, -12,  -1
};
static signed char iwasp04[8] = {
    0,   1, -12,  10,  91,   0, -12,  -1
};
static signed char iwasp05[8] = {
    0,   1, -14,  10,  82,   8, -12,  -1
};
static signed char iwasp06[8] = {
    0,   1, -12,  10,  91,   8, -12,  -1
};


signed char* iwapat2[7] = {
  iwasp200,
  iwasp201,
  iwasp202,
  iwasp203,
  iwasp204,
  iwasp205,
  iwasp206
};


static signed char iwasp200[38] = {
     0,    6,  -40,   11,  114,    0,  -24,   -1,  -40,   11,
   126,    0,    0,    0,   -8,   11, -118,    0,  -24,   -1,
    -8,   11, -106,    0,    0,    0,   24,    9,  -94,    0,
   -24,   -1,   24,    9,  -88,    0,    0,    0
};
static signed char iwasp201[26] = {
     0,    4,  -24,   11,  114,    0,  -24,   -1,  -24,   11,
   126,    0,    0,    0,    8,    9,  -82,    0,  -24,   -1,
     8,    9,  -76,    0,    0,    0
};
static signed char iwasp202[26] = {
     0,    4,  -16,    9,  -70,    0,  -16,   -1,  -16,    5,
   -64,    0,    8,    0,    0,    9,  -82,    0,  -24,   -1,
     0,    9,  -76,    0,    0,    0
};
static signed char iwasp203[8] = {
     0,    1,  -12,   10,  -60,    0,  -12,   -1
};
static signed char iwasp204[8] = {
     0,    1,  -12,   10,  -51,    0,  -12,   -1
};
static signed char iwasp205[8] = {
     0,    1,  -14,   10,  -60,    8,  -12,   -1
};
static signed char iwasp206[8] = {
     0,    1,  -12,   10,  -51,    8,  -12,   -1
};


signed char* vsiwapat[8] = {
  vsiwasp00,
  vsiwasp01,
  vsiwasp02,
  vsiwasp01,
  vsiwasp02,
  vsiwasp01,
  vsiwasp02,
  vsiwasp03
};


static signed char vsiwasp00[8] = {
    0,   1, -16,  15,  14,   0, -16,  -1
};
static signed char vsiwasp01[8] = {
    0,   1,  -8,   5,  30,   0,  -8,  -1
};
static signed char vsiwasp02[8] = {
    0,   1,  -8,   5,  34,   0,  -8,  -1
};
static signed char vsiwasp03[8] = {
    0,   1,  -4,   0,   0,  -3,  -4,  -1
};


signed char* iwapat9[11] = {
  iwasp900,
  iwasp901,
  iwasp902,
  iwasp903,
  iwasp904,
  iwasp905,
  iwasp906,
  iwasp907,
  iwasp908,
  iwasp909,
  iwasp909
};


static signed char iwasp900[8] = {
    0,   1,  -8,   5, 109,   0,  -8,  -1
};
static signed char iwasp901[8] = {
    0,   1,  -8,   5, 109,   8,  -8,  -1
};
static signed char iwasp902[8] = {
    0,   1,  -8,   5, 109,  24,  -8,  -1
};
static signed char iwasp903[8] = {
    0,   1,  -8,   5, 109,  16,  -8,  -1
};
static signed char iwasp904[8] = {
    0,   1, -16,  15, 113,   0, -16,  -1
};
static signed char iwasp905[8] = {
    0,   1, -16,  15, 113,   8, -16,  -1
};
static signed char iwasp906[8] = {
    0,   1, -16,  15, 113,  24, -16,  -1
};
static signed char iwasp907[8] = {
    0,   1, -16,  15, 113,  16, -16,  -1
};
static signed char iwasp908[38] = {
    0,   6,   0,  15, 113,  24, -16,  -1, -16,  15,
  113,  16, -16,  -1, -24,   5, 109,   8, -16,  -1,
  -40,  15, 113,  24, -16,  -1,  24,   5, 109,   0,
    0,   0,  11,  15, 113,  16, -16,  -1
};
static signed char iwasp909[38] = {
    0,   6, -13,  15, 113,  16,  -8,  -1, -13,   5,
  109,   8, -16,  -1,   0,   5, 109,   8, -24,  -1,
  -16,  15, 113,  16, -40,  -1, -16,  15, 113,  24,
  -16,  -1, -16,  15, 113,  24,   8,   0
};


signed char* iwapat92[12] = {
  iwasp920_iwasp924,
  iwasp921_iwasp925,
  iwasp922_iwasp926,
  iwasp923_iwasp927,
  iwasp920_iwasp924,
  iwasp921_iwasp925,
  iwasp922_iwasp926,
  iwasp923_iwasp927,
  iwasp928,
  iwasp929,
  iwasp929,
  iwasp928
};


static signed char iwasp920_iwasp924[14] = {
  0, 2, -16, 13, 0, 0, -16, -1, 0, 13,
  8, 0, -16, -1
};
static signed char iwasp921_iwasp925[14] = {
  0, 2, -16, 13, 0, 8, -16, -1, 0, 13,
  8, 8, -16, -1
};
static signed char iwasp922_iwasp926[14] = {
  0, 2, -16, 13, 8, 24, -16, -1, 0, 13,
  0, 24, -16, -1
};
static signed char iwasp923_iwasp927[14] = {
  0, 2, -16, 13, 8, 16, -16, -1, 0, 13,
  0, 16, -16, -1
};
static signed char iwasp928[26] = {
  0, 4, -32, 13, 0, 0, -16, -1, -16, 13,
  8, 0, -16, -1, 0, 13, 0, 8, -16, -1,
  16, 13, 8, 8, -16, -1
};
static signed char iwasp929[28] = {
  0, 4, -16, 13, 0, 0, -32, -1, -16, 13,
  8, 16, 0, 0, 0, 13, 8, 0, -32, -1,
  0, 13, 0, 16, 0, 0, -121, -37
};
