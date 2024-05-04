#include "globals.h"
#include "macros.h"
#include "util.h"
#include "spring.h"
#include "004xxxxx.h"
#include "hitchk.h"
static sprite_status_handler sjumpinit_tbl[5];
static void sjumpswinit(sprite_status* p_actwk);
static sprite_status_handler sjumpswinit_tbl[8];
static void sdash_init(sprite_status* p_actwk);
static void sjumpr_init(sprite_status* p_actwk);
static void sjumpr_initg(sprite_status* p_actwk);
static void sjump45_init(sprite_status* p_actwk);
static void sjump45r_init(sprite_status* p_actwk);
static void sjump_init(sprite_status* p_actwk);
static void sjump_initg(sprite_status* p_actwk);
static void sjumpinit_end(sprite_status* p_actwk);
static unsigned short sjumptbl[2];
static void sjumpmove(sprite_status* p_actwk);
static void vssjumpmove(sprite_status* p_actwk);
static void sdashmove(sprite_status* p_actwk);
static void vssdashmove(sprite_status* p_actwk);
static void vssdashsub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void sdashsub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void sdashsub2(sprite_status* p_actwk, sprite_status* p_playerwk);
static void sdashcolichk(sprite_status* p_actwk);
static void sjumprmove(sprite_status* p_actwk);
static void vssjumprmove(sprite_status* p_actwk);
static void sjumprsub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void sjumprsub2(sprite_status* p_actwk, sprite_status* p_playerwk);
static void sjump45move(sprite_status* p_actwk);
static void sjump45move__sub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void sjump45rmove(sprite_status* p_actwk);
static void sjump45rmove__sub(sprite_status* p_actwk, sprite_status* p_playerwk);
static signed char sjump45tbl[28];
static signed char sjump45tbl2[28];
static signed char sjumpchg0[3];
static signed char sjumpchg1[12];
static signed char sjumpchg2[3];
static signed char sjumpchg3[12];
static signed char sjumpchg4[3];
static signed char sjumpchg5[15];
static signed char* banepat2[11];
static signed char banevsp00[14];
static signed char banevsp01[8];
static signed char banevsp02[14];
static signed char banevsp00c[14];
static signed char banevsp01c[8];
static signed char banevsp02c[14];
static signed char banehsp00[14];
static signed char banehsp01[8];
static signed char banehsp02[14];
static signed char banehsp00c[14];
static signed char banehsp01c[8];
static signed char banehsp02c[14];
static signed char banevsp03[14];
static signed char banevsp03c[14];
static signed char bane45sp00[26];
static signed char bane45sp01[20];
static signed char bane45sp02[32];
static signed char bane45sp03[26];
static signed char bane45sp00c[26];
static signed char bane45sp01c[20];
static signed char bane45sp02c[32];
static signed char bane45sp03c[26];
static signed char* vsbanepat2[7];
signed char vsbanevsp00[14];
signed char vsbanevsp01[8];
signed char vsbanevsp02[20];
signed char vsbanehsp00[14];
signed char vsbanehsp01[8];
signed char vsbanehsp02[20];
signed char vsbanevsp03[14];
signed char vsbanevsp00c[14];
signed char vsbanevsp01c[8];
signed char vsbanevsp02c[20];
signed char vsbanehsp00c[14];
signed char vsbanehsp01c[8];
signed char vsbanehsp02c[20];
signed char vsbanevsp03c[14];
static void sjumpmvkind(sprite_status* p_actwk);
static sprite_status_handler sjumpmvkindtbl[5];
static void sjumpmv_ymove(sprite_status* p_actwk);
static void sjumpmv_ymove1(sprite_status* p_actwk);
static void sjumpmv_xmove(sprite_status* p_actwk);
static void sjumpmv_xmove1(sprite_status* p_actwk);
static void sjumpmv_ymove2(sprite_status* p_actwk);
static void sjumpmv_ymove3(sprite_status* p_actwk);
static void sjumpmv_xymove(sprite_status* p_actwk);
static void sjumpmv_xymove1(sprite_status* p_actwk);
static void sjumpmv_xymove2(sprite_status* p_actwk);
static void sjumpmv_xymove3(sprite_status* p_actwk);
static void sjumpmv_sub(sprite_status* p_actwk);
static unsigned char sjumpswtbl[32];
void sjumpsw(sprite_status* p_actwk);
static void sjumpswkind(sprite_status* p_actwk);
static sprite_status_handler sjumpswkindtbl[8];
static void sjumpsw_ymove(sprite_status* p_actwk);
static void sjumpsw_ymove1(sprite_status* p_actwk);
static void sjumpsw_xmove(sprite_status* p_actwk);
static void sjumpsw_xmove1(sprite_status* p_actwk);
static void sjumpsw_ymove2(sprite_status* p_actwk);
static void sjumpsw_ymove3(sprite_status* p_actwk);
static void sjumpsw_ymove4(sprite_status* p_actwk);
static void sjumpsw_ymove5(sprite_status* p_actwk);
static void sjumpsw_xmove2(sprite_status* p_actwk);
static void sjumpsw_xmove3(sprite_status* p_actwk);
static void sjumpsw_xmove4(sprite_status* p_actwk);
static void sjumpsw_xmove5(sprite_status* p_actwk);
static void sjumpsw_sub(sprite_status* p_actwk);
static void sjumpsw_sub2(sprite_status* p_actwk);
static void sjumpsw_sub3(sprite_status* p_actwk);
static void sjumpswmove(sprite_status* p_actwk);
static void sjumpswmove2(sprite_status* p_actwk);
static signed char* banedaipat[4];
static signed char* banedaipat2[4];
static signed char banedaisp00[2];
static signed char banedaisp01[8];
static signed char banedaisp02[8];
static signed char banedaisp03[8];


void sjump(sprite_status* p_actwk) {
  p_actwk->patbase = banepat;
  p_actwk->sproffset = 1188;
  SET_USE_LEVEL_COORDS(p_actwk->actflg);
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 16;
  p_actwk->sprpri = PRI_4;
  p_actwk->actfree.spring.orig_xposi = LONG_HIGH(p_actwk->xposi);
  p_actwk->actfree.spring.orig_yposi = LONG_HIGH(p_actwk->yposi);
  sjumpinit_tbl[(p_actwk->userflag1 >> 3 & 0xE) / 2](p_actwk);
}


static sprite_status_handler sjumpinit_tbl[5] = {
  &sjump_init,
  &sdash_init,
  &sjumpr_init,
  &sjump45_init,
  &sjump45r_init
};


static void sjumpswinit(sprite_status* p_actwk) {
  p_actwk->patbase = banepat;
  p_actwk->sproffset = 1188;
  SET_USE_LEVEL_COORDS(p_actwk->actflg);
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 16;
  p_actwk->sprpri = PRI_4;
  p_actwk->actfree.spring.orig_xposi = LONG_HIGH(p_actwk->xposi);
  p_actwk->actfree.spring.orig_yposi = LONG_HIGH(p_actwk->yposi);
  sjumpswinit_tbl[(p_actwk->userflag1 >> 3 & 0xE) / 2](p_actwk);
  p_actwk->actfree.spring.recoil = -2048;
}


static sprite_status_handler sjumpswinit_tbl[8] = {
  &sjump_init,
  &sdash_init,
  &sjumpr_init,
  &sdash_init,
  &sjump_init,
  &sjumpr_init,
  &sjump_init,
  &sjumpr_init
};


static void sdash_init(sprite_status* p_actwk) {
  p_actwk->mstno = 2;
  p_actwk->patno = 3;
  p_actwk->sproffset = 1204;
  p_actwk->sprhs = 8;
  p_actwk->r_ptr = &sdashmove;
  if (vs_flag != 0) {
    p_actwk->patbase = vsbanepat;
    p_actwk->sproffset = 941;
    p_actwk->r_ptr = &vssdashmove;
  }
  sjumpinit_end(p_actwk);
}


static void sjumpr_init(sprite_status* p_actwk) {
  if (reverse_gravity_flag == 0) {
    SET_BIT(p_actwk->cddat1, CD_DOWN);
  }
  sjumpr_initg(p_actwk);
}


static void sjumpr_initg(sprite_status* p_actwk) {
  p_actwk->patno = 6;
  p_actwk->r_ptr = &sjumprmove;
  if (vs_flag != 0) {
    p_actwk->r_ptr = &vssjumprmove;
    p_actwk->patbase = vsbanepat;
    p_actwk->sproffset = 913;
  }
  sjumpinit_end(p_actwk);
}


static void sjump45_init(sprite_status* p_actwk) {
  p_actwk->mstno = 4;
  p_actwk->patno = 7;
  p_actwk->sproffset = 1082;

  if (stageno.zone == MARBLE_GARDEN || stageno.zone == MUSHROOM_HILL) {
    p_actwk->sproffset = 1144;
  }
  p_actwk->r_ptr = &sjump45move;
  sjumpinit_end(p_actwk);
}


static void sjump45r_init(sprite_status* p_actwk) {
  p_actwk->mstno = 4;
  p_actwk->patno = 10;
  p_actwk->sproffset = 1082;
  if (stageno.zone == MARBLE_GARDEN || stageno.zone == MUSHROOM_HILL) {
    p_actwk->sproffset = 1144;
  }
  SET_BIT(p_actwk->cddat1, CD_DOWN);
  p_actwk->r_ptr = &sjump45rmove;
  sjumpinit_end(p_actwk);
}


static void sjump_init(sprite_status* p_actwk) {
  if (reverse_gravity_flag == 0) {
    sjumpr_initg(p_actwk);
  }
  else {
    sjump_initg(p_actwk);
  }
}


static void sjump_initg(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmove;
  if (vs_flag != 0) {
    p_actwk->r_ptr = &vssjumpmove;
    p_actwk->patbase = vsbanepat;
    p_actwk->sproffset = 913;
    if (stageno.zone == ENDLESS_MINE) {
      p_actwk->sproffset |= 0x8000;
    }
  }
  sjumpinit_end(p_actwk);
}


static void sjumpinit_end(sprite_status* p_actwk) {
  p_actwk->actfree.spring.recoil = sjumptbl[(p_actwk->userflag1 & 2) / 2];
  if (BIT_1_IS_SET(p_actwk->userflag1)) {
    p_actwk->patbase = banepat2;
    if (vs_flag != 0) {
      p_actwk->patbase = vsbanepat2;
    }
  }
}


static unsigned short sjumptbl[2] = { -4096, -2560 };


static void sjumpmove(sprite_status* p_actwk) {
  hitchk_data data = { 27, 8, 16, LONG_HIGH(p_actwk->xposi) };
  plhitchk2(p_actwk, &actwk[0], data, 3);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
    sjumpsub(p_actwk, &actwk[0]);
  }
  plhitchk2(p_actwk, &actwk[1], data, 4);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)) {
    sjumpsub(p_actwk, &actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk(p_actwk);
}


static void vssjumpmove(sprite_status* p_actwk) {
  hitchk_data data = { 19, 8, 16, LONG_HIGH(p_actwk->xposi) };
  plhitchk2(p_actwk, &actwk[0], data, 3);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
    sjumpsub(p_actwk, &actwk[0]);
  }
  plhitchk2(p_actwk, &actwk[1], data, 4);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)) {
    sjumpsub(p_actwk, &actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  actionsub(p_actwk);
}


void sjumpsub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_actwk->mstno = 1;
  p_playerwk->yposi += SHORT_TO_LONG_HIGH(8);
  if (reverse_gravity_flag != 0) {
    p_playerwk->yposi -= SHORT_TO_LONG_HIGH(16);
  }
  p_playerwk->yspeed = p_actwk->actfree.spring.recoil;
  SET_BIT_1(p_playerwk->cddat1);
  CLEAR_BIT_3(p_playerwk->cddat1);
  p_playerwk->actfree.player.jump_status = 0;
  p_playerwk->actfree.player.roll_status = 0;
  p_playerwk->mstno = 16;
  p_playerwk->r_no = 2;
  if (BIT_7_IS_SET(p_actwk->userflag1)) {
    p_playerwk->xspeed = 0;
  }
  if (BIT_0_IS_SET(p_actwk->userflag1)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc2 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->actfree.player.flip_rev_cnt = 0;
    p_playerwk->actfree.player.flip_rev_frame_cnt = 4;
    if (!BIT_1_IS_SET(p_actwk->userflag1)) {
      p_playerwk->actfree.player.flip_rev_cnt = 1;
    }
    if (BIT_0_IS_SET(p_playerwk->cddat1)) {
      p_playerwk->direc2 = -p_playerwk->direc2;
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if ((p_actwk->userflag1 & 0xC) == 4) {
    p_playerwk->actfree.player.colibits.top_bit = 12;
    p_playerwk->actfree.player.colibits.not_top_bit = 13;
  }
  if ((p_actwk->userflag1 & 0xC) == 8) {
    p_playerwk->actfree.player.colibits.top_bit = 14;
    p_playerwk->actfree.player.colibits.not_top_bit = 15;
  }
  soundset(177);
}


static void sdashmove(sprite_status* p_actwk) {
  hitchk_data data = { 19, 14, 15, LONG_HIGH(p_actwk->xposi) };
  hitchk_results results = plhitchk2(p_actwk, &actwk[0], data, 3);
  if (BIT_0_IS_SET(results.plcoli)) {
    unsigned char cddat1 = p_actwk->cddat1;
    if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) < util__to_unsigned(actwk[0].xposi)) { // unsigned
      cddat1 ^= 1;
    }
    if (!BIT_IS_SET(cddat1, CD_RIGHT)) {
      sdashsub(p_actwk, &actwk[0]);
    }
  }
  results = plhitchk2(p_actwk, &actwk[1], data, 4);
  if (BIT_1_IS_SET(results.plcoli)) {
    unsigned char cddat1 = p_actwk->cddat1;
    if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) < util__to_unsigned(actwk[1].xposi)) { // unsigned
      cddat1 ^= 1;
    }
    if (!BIT_IS_SET(cddat1, CD_RIGHT)) {
      sdashsub(p_actwk, &actwk[1]);
    }
  }
  sdashcolichk(p_actwk);
  patchg(p_actwk, sjumpchg);
  frameoutchk2(p_actwk, p_actwk->actfree.spring.orig_xposi);
}


static void vssdashmove(sprite_status* p_actwk) {
  hitchk_data data = { 15, 12, 13, LONG_HIGH(p_actwk->xposi) };
  hitchk_results results = plhitchk2(p_actwk, &actwk[0], data, 3);
  if (BIT_0_IS_SET(results.plcoli)) {
    unsigned char cddat1 = p_actwk->cddat1;
    if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) < util__to_unsigned(LONG_HIGH(actwk[0].xposi))) { // unsigned
      cddat1 ^= 1;
    }
    if (!BIT_IS_SET(cddat1, CD_RIGHT)) {
      vssdashsub(p_actwk, &actwk[0]);
    }
  }
  results = plhitchk2(p_actwk, &actwk[1], data, 4);
  if (BIT_1_IS_SET(results.plcoli)) {
    unsigned char cddat1 = p_actwk->cddat1;
    if (util__to_unsigned(LONG_HIGH(p_actwk->xposi)) < util__to_unsigned(LONG_HIGH(actwk[1].xposi))) { // unsigned
      cddat1 ^= 1;
    }
    if (!BIT_IS_SET(cddat1, CD_RIGHT)) {
      vssdashsub(p_actwk, &actwk[1]);
    }
  }
  patchg(p_actwk, sjumpchg);
  actionsub(p_actwk);
}


static void vssdashsub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_actwk->mstno = 3;
  p_playerwk->xspeed = p_actwk->actfree.spring.recoil;
  p_playerwk->xposi += SHORT_TO_LONG_HIGH(4);
  SET_BIT_0(p_playerwk->cddat1);
  if (BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    CLEAR_BIT_0(p_playerwk->cddat1);
    p_playerwk->xposi -= SHORT_TO_LONG_HIGH(8);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  sdashsub2(p_actwk, p_playerwk);
}


static void sdashsub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_actwk->mstno = 3;
  p_playerwk->xspeed = p_actwk->actfree.spring.recoil;
  p_playerwk->xposi += SHORT_TO_LONG_HIGH(8);
  SET_BIT_0(p_playerwk->cddat1);
  if (BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    CLEAR_BIT_0(p_playerwk->cddat1);
    p_playerwk->xposi -= SHORT_TO_LONG_HIGH(16);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  sdashsub2(p_actwk, p_playerwk);
}


static void sdashsub2(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_playerwk->actfree.player.hlock_timer = 15;
  p_playerwk->mspeed = p_playerwk->xspeed;
  if (!BIT_2_IS_SET(p_playerwk->cddat1)) {
    p_playerwk->mstno = 0;
  }
  if (BIT_7_IS_SET(p_actwk->userflag1)) {
    p_playerwk->yspeed = 0;
  }
  if (BIT_0_IS_SET(p_actwk->userflag1)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc2 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->actfree.player.flip_rev_cnt = 1;
    p_playerwk->actfree.player.flip_rev_frame_cnt = 8;
    if (BIT_1_IS_SET(p_actwk->userflag1)) {
      p_playerwk->actfree.player.flip_rev_cnt = 3;
    }
    if (BIT_0_IS_SET(p_playerwk->cddat1)) {
      p_playerwk->direc2 = -p_playerwk->direc2;
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if ((p_actwk->userflag1 & 0xC) == 4) {
    p_playerwk->actfree.player.colibits.top_bit = 12;
    p_playerwk->actfree.player.colibits.not_top_bit = 13;
  }
  if ((p_actwk->userflag1 & 0xC) == 8) {
    p_playerwk->actfree.player.colibits.top_bit = 14;
    p_playerwk->actfree.player.colibits.not_top_bit = 15;
  }
  CLEAR_BIT(p_actwk->cddat1, CD_PLPUSH);
  CLEAR_BIT(p_actwk->cddat1, CD_PL2PUSH);
  CLEAR_BIT_5(p_playerwk->cddat1);
  p_playerwk->actfree.player.talent_status = 0;
  soundset(177);
}


static void sdashcolichk(sprite_status* p_actwk) {
  if (p_actwk->mstno == 3) return;
  unsigned short xposi1 = util__to_unsigned(LONG_HIGH(p_actwk->xposi));
  unsigned short xposi2 = xposi1 + 40;
  if (BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    xposi2 = xposi1;
    xposi1 -= 40;
  }
  unsigned short yposi1 = util__to_unsigned(LONG_HIGH(p_actwk->yposi));
  unsigned short yposi2 = yposi1 + 24;
  yposi1 -= 24;
  if (!BIT_1_IS_SET(actwk[0].cddat1)) {
    short mspeed = actwk[0].mspeed;
    if (BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
      mspeed = -mspeed;
    }
    if (mspeed >= 0) {
      unsigned short plxposi = util__to_unsigned(LONG_HIGH(actwk[0].xposi));
      if (plxposi >= xposi1 // unsigned
          && plxposi < xposi2) { // unsigned
        unsigned short plyposi = util__to_unsigned(LONG_HIGH(actwk[0].yposi));
        if (plyposi >= yposi1 // unsigned
            && plyposi < yposi2) { // unsigned
          sdashsub(p_actwk, &actwk[0]);
        }
      }
    }
  }
  if (!BIT_1_IS_SET(actwk[1].cddat1)) {
    short mspeed = actwk[1].mspeed;
    if (BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
      mspeed = -mspeed;
    }
    if (mspeed >= 0) {
      unsigned short plxposi = util__to_unsigned(LONG_HIGH(actwk[1].xposi));
      if (plxposi >= xposi1 && plxposi < xposi2) { // unsigned
        unsigned short plyposi = util__to_unsigned(LONG_HIGH(actwk[1].yposi));
        if (plyposi >= yposi1 && plyposi < yposi2) { // unsigned
          sdashsub(p_actwk, &actwk[1]);
        }
      }
    }
  }
}


static void sjumprmove(sprite_status* p_actwk) {
  hitchk_data data = { 27, 8, 9, LONG_HIGH(p_actwk->xposi) };
  hitchk_results results = plhitchk2(p_actwk, &actwk[0], data, 3);
  if (results.colitype == -2) {
    sjumprsub(p_actwk, &actwk[0]);
  }
  results = plhitchk2(p_actwk, &actwk[1], data, 4);
  if (results.colitype == -2) {
    sjumprsub(p_actwk, &actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk(p_actwk);
}


static void vssjumprmove(sprite_status* p_actwk) {
  hitchk_data data = { 19, 8, 9, LONG_HIGH(p_actwk->xposi) };
  hitchk_results results = plhitchk2(p_actwk, &actwk[0], data, 3);
  if (results.colitype == -2) {
    actwk[0].yposi -= SHORT_TO_LONG_HIGH(4);
    sjumprsub2(p_actwk, &actwk[0]);
  }
  results = plhitchk2(p_actwk, &actwk[1], data, 4);
  if (results.colitype == -2) {
    actwk[1].yposi -= SHORT_TO_LONG_HIGH(4);
    sjumprsub2(p_actwk, &actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  actionsub(p_actwk);
}


static void sjumprsub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_playerwk->yposi -= SHORT_TO_LONG_HIGH(8);
  if (reverse_gravity_flag != 0) {
    p_playerwk->yposi += SHORT_TO_LONG_HIGH(16);
  }
  sjumprsub2(p_actwk, p_playerwk);
}


static void sjumprsub2(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_actwk->mstno = 1;
  p_playerwk->yspeed = p_actwk->actfree.spring.recoil;
  p_playerwk->yspeed = -p_playerwk->yspeed;
  if (p_playerwk->yspeed == 4096) {
    p_playerwk->yspeed = 3328;
  }
  if (BIT_7_IS_SET(p_actwk->userflag1)) {
    p_playerwk->xspeed = 0;
  }
  if (BIT_0_IS_SET(p_actwk->userflag1)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc2 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->actfree.player.flip_rev_cnt = 0;
    p_playerwk->actfree.player.flip_rev_frame_cnt = 4;
    if (!BIT_1_IS_SET(p_actwk->userflag1)) {
      p_playerwk->actfree.player.flip_rev_cnt = 1;
    }
    if (BIT_0_IS_SET(p_playerwk->cddat1)) {
      p_playerwk->direc2 = -p_playerwk->direc2;
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if ((p_actwk->userflag1 & 0xC) == 4) {
    p_playerwk->actfree.player.colibits.top_bit = 12;
    p_playerwk->actfree.player.colibits.not_top_bit = 13;
  }
  if ((p_actwk->userflag1 & 0xC) == 8) {
    p_playerwk->actfree.player.colibits.top_bit = 14;
    p_playerwk->actfree.player.colibits.not_top_bit = 15;
  }
  SET_BIT_1(p_playerwk->cddat1);
  CLEAR_BIT_3(p_playerwk->cddat1);
  p_playerwk->actfree.player.jump_status = 0;
  p_playerwk->r_no = 2;
  p_playerwk->actfree.player.talent_status = 0;
  soundset(177);
}


static void sjump45move(sprite_status* p_actwk) {
  hitchk_data data = { 27, 16, 0, LONG_HIGH(p_actwk->xposi) };
  plhitchk_slope(p_actwk, &actwk[0], data, sjump45tbl, 3);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
    sjump45move__sub(p_actwk, &actwk[0]);
  }
  plhitchk_slope(p_actwk, &actwk[1], data, sjump45tbl, 4);
  if (BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)) {
    sjump45move__sub(p_actwk, &actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk2(p_actwk, p_actwk->actfree.spring.orig_xposi);
}


static void sjump45move__sub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  if (!BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    if (LONG_HIGH(p_actwk->xposi) - 4 >= LONG_HIGH(p_playerwk->xposi)) return;
  }
  else {
    if (LONG_HIGH(p_actwk->xposi) + 4 < LONG_HIGH(p_playerwk->xposi)) return;
  }
  p_actwk->mstno = 5;
  p_playerwk->yspeed = p_actwk->actfree.spring.recoil;
  p_playerwk->xspeed = p_actwk->actfree.spring.recoil;
  p_playerwk->yposi += SHORT_TO_LONG_HIGH(6);
  p_playerwk->xposi += SHORT_TO_LONG_HIGH(6);
  SET_BIT_0(p_playerwk->cddat1);
  if (!BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    CLEAR_BIT_0(p_playerwk->cddat1);
    p_playerwk->xposi -= SHORT_TO_LONG_HIGH(12);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  SET_BIT_1(p_playerwk->cddat1);
  CLEAR_BIT_3(p_playerwk->cddat1);
  p_playerwk->actfree.player.jump_status = 0;
  p_playerwk->mstno = 16;
  p_playerwk->r_no = 2;
  if (BIT_0_IS_SET(p_actwk->userflag1)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc2 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->actfree.player.flip_rev_cnt = 1;
    p_playerwk->actfree.player.flip_rev_frame_cnt = 8;
    if (!BIT_1_IS_SET(p_actwk->userflag1)) {
      p_playerwk->actfree.player.flip_rev_cnt = 3;
    }
    if (BIT_0_IS_SET(p_playerwk->cddat1)) {
      p_playerwk->direc2 = -p_playerwk->direc2;
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if ((p_actwk->userflag1 & 0xC) == 4) {
    p_playerwk->actfree.player.colibits.top_bit = 12;
    p_playerwk->actfree.player.colibits.not_top_bit = 13;
  }
  if ((p_actwk->userflag1 & 0xC) == 8) {
    p_playerwk->actfree.player.colibits.top_bit = 14;
    p_playerwk->actfree.player.colibits.not_top_bit = 15;
  }
  soundset(177);
}


static void sjump45rmove(sprite_status* p_actwk) {
  hitchk_data data = { 27, 16, 0, LONG_HIGH(p_actwk->xposi) };
  hitchk_results results = plhitchk_slope(p_actwk, &actwk[0], data, sjump45tbl2, 3);
  if (results.colitype == -2) {
    sjump45rmove__sub(p_actwk, &actwk[0]);
  }
  results = plhitchk_slope(p_actwk, &actwk[1], data, sjump45tbl2, 4);
  if (results.colitype == -2) {
    sjump45rmove__sub(p_actwk, &actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk2(p_actwk, p_actwk->actfree.spring.orig_xposi);
}


static void sjump45rmove__sub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  p_actwk->mstno = 5;
  p_playerwk->yspeed = p_actwk->actfree.spring.recoil;
  p_playerwk->xspeed = p_actwk->actfree.spring.recoil;
  p_playerwk->yposi -= SHORT_TO_LONG_HIGH(6);
  p_playerwk->xposi += SHORT_TO_LONG_HIGH(6);
  SET_BIT_0(p_playerwk->cddat1);
  if (!BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    CLEAR_BIT_0(p_playerwk->cddat1);
    p_playerwk->xposi -= SHORT_TO_LONG_HIGH(12);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  SET_BIT_1(p_playerwk->cddat1);
  CLEAR_BIT_3(p_playerwk->cddat1);
  p_playerwk->actfree.player.jump_status = 0;
  p_playerwk->mstno = 16;
  p_playerwk->r_no = 2;
  if (BIT_0_IS_SET(p_actwk->userflag1)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc2 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->actfree.player.flip_rev_cnt = 1;
    p_playerwk->actfree.player.flip_rev_frame_cnt = 8;
    if (!BIT_1_IS_SET(p_actwk->userflag1)) {
      p_playerwk->actfree.player.flip_rev_cnt = 3;
    }
    if (BIT_0_IS_SET(p_playerwk->cddat1)) {
      p_playerwk->direc2 = -p_playerwk->direc2;
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if ((p_actwk->userflag1 & 0xC) == 4) {
    p_playerwk->actfree.player.colibits.top_bit = 12;
    p_playerwk->actfree.player.colibits.not_top_bit = 13;
  }
  if ((p_actwk->userflag1 & 0xC) == 8) {
    p_playerwk->actfree.player.colibits.top_bit = 14;
    p_playerwk->actfree.player.colibits.not_top_bit = 15;
  }
  soundset(177);
}


static signed char sjump45tbl[28] = {
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 14, 12, 10,  8,  6,  4,  2,  0,
  -2, -4, -4, -4, -4, -4, -4, -4
};


static signed char sjump45tbl2[28] = {
  -12, -16, -16, -16, -16, -16, -16, -16, -16, -16,
  -16, -16, -14, -12, -10,  -8,  -6,  -4,  -2,   0,
    2,   4,   4,   4,   4,   4,   4,   4
};


signed char* sjumpchg[6] = {
  sjumpchg0,
  sjumpchg1,
  sjumpchg2,
  sjumpchg3,
  sjumpchg4,
  sjumpchg5
};


static signed char sjumpchg0[3] = {
    15,    0,   -1
};
static signed char sjumpchg1[12] = {
     0,    1,    0,    0,    2,    2,    2,    2,    2,    2,
    -3,   0
};
static signed char sjumpchg2[3] = {
    15,    3,   -1
};
static signed char sjumpchg3[12] = {
     0,    4,    3,    3,    5,    5,    5,    5,    5,    5,
    -3,    2 };
static signed char sjumpchg4[3] = {
    15,    7,   -1
};
static signed char sjumpchg5[15] = {
     0,    8,    7,    7,    9,    9,    9,    9,    9,    9,
    -3,    4, -121,  -37, -112
};


signed char* banepat[11] = {
  banevsp00,
  banevsp01,
  banevsp02,
  banehsp00,
  banehsp01,
  banehsp02,
  banevsp03,
  bane45sp00,
  bane45sp01,
  bane45sp02,
  bane45sp03
};

static signed char* banepat2[11] = {
  banevsp00c,
  banevsp01c,
  banevsp02c,
  banehsp00c,
  banehsp01c,
  banehsp02c,
  banevsp03c,
  bane45sp00c,
  bane45sp01c,
  bane45sp02c,
  bane45sp03c
};


static signed char banevsp00[14] = {
    0,   2,  -8,  12,   0,   0, -16,  -1,   0,   4,
    8,   0,  -8,  -1
};
static signed char banevsp01[8] = {
    0,   1,   0,  12,   0,   0, -16,  -1
};
static signed char banevsp02[14] = {
    0,   2, -24,  12,   0,   0, -16,  -1, -16,   6,
   10,   0,  -8,  -1
};


static signed char banevsp00c[14] = {
    0,   2,  -8,  12,   4,  32, -16,  -1,   0,   4,
    8,   0,  -8,  -1
};
static signed char banevsp01c[8] = {
    0,   1,   0,  12,   4,  32, -16,  -1
};
static signed char banevsp02c[14] = {
    0,   2, -24,  12,   4,  32, -16,  -1, -16,   6,
   10,   0,  -8,  -1
};


static signed char banehsp00[14] = {
    0,   2, -16,   3,   0,   0,   0,   0,  -8,   1,
    8,   0,  -8,  -1
};
static signed char banehsp01[8] = {
    0,   1, -16,   3,   0,   0,  -8,  -1
};
static signed char banehsp02[14] = {
    0,   2, -16,   3,   0,   0,  16,   0,  -8,   9,
   10,   0,  -8,  -1
};


static signed char banehsp00c[14] = {
    0,   2, -16,   3,   4,  32,   0,   0,  -8,   1,
    8,   0,  -8,  -1
};
static signed char banehsp01c[8] = {
    0,   1, -16,   3,   4,  32,  -8,  -1
};
static signed char banehsp02c[14] = {
    0,   2, -16,   3,   4,  32,  16,   0,  -8,   9,
   10,   0,  -8,  -1
};


static signed char banevsp03[14] = {
    0,   2,   0,  12,   0,  16, -16,  -1,  -8,   4,
    8,  16,  -8,  -1
};


static signed char banevsp03c[14] = {
    0,   2,   0,  12,   4,  48, -16,  -1,  -8,   4,
    8,  16,  -8,  -1
};


static signed char bane45sp00[26] = {
    0,   4, -15,   8,   0,   0, -21,  -1,  -7,   8,
    3,   0, -13,  -1,   1,   5,   6,   0,  -5,  -1,
   -5,   5,  20,   0, -15,  -1
};
static signed char bane45sp01[20] = {
    0,   3,  -9,   8,   0,   0, -26,  -1,  -1,   8,
    3,   0, -18,  -1,   7,   5,   6,   0, -10,  -1
};
static signed char bane45sp02[32] = {
    0,   5, -26,   8,   0,   0, -10,  -1, -18,   8,
    3,   0,  -2,  -1, -10,   5,   6,   0,   6,   0,
  -11,   4,  24,   0,  -6,  -1,  -3,   4,  26,   0,
  -14,  -1
};
static signed char bane45sp03[26] = {
    0,   4,   7,   8,   0,  16, -21,  -1,  -1,   8,
    3,  16, -13,  -1, -17,   5,   6,  16,  -5,  -1,
  -11,   5,  20,  16, -15,  -1
};


static signed char bane45sp00c[26] = {
    0,   4, -15,   8,  10,  32, -21,  -1,  -7,   8,
   13,  32, -13,  -1,   1,   5,  16,  32,  -5,  -1,
   -5,   5,  20,   0, -15,  -1
};
static signed char bane45sp01c[20] = {
  0, 3, -9, 8, 10, 32, -26, -1, -1, 8,
  13, 32, -18, -1, 7, 5, 16, 32, -10, -1
};
static signed char bane45sp02c[32] = {
    0,   5, -26,   8,  10,  32, -10,  -1, -18,   8,
   13,  32,  -2,  -1, -10,   5,  16,  32,   6,   0,
  -11,   4,  24,   0,  -6,  -1,  -3,   4,  26,   0,
  -14,  -1
};
static signed char bane45sp03c[26] = {
    0,   4,   7,   8,  10,  48, -21,  -1,  -1,   8,
   13,  48, -13,  -1, -17,   5,  16,  48,  -5,  -1,
  -11,   5,  20,  16, -15,  -1
};


signed char* vsbanepat[7] = {
  vsbanevsp00,
  vsbanevsp01,
  vsbanevsp02,
  vsbanehsp00,
  vsbanehsp01,
  vsbanehsp02,
  vsbanevsp03
};


static signed char* vsbanepat2[7] = {
  vsbanevsp00c,
  vsbanevsp01c,
  vsbanevsp02c,
  vsbanehsp00c,
  vsbanehsp01c,
  vsbanehsp02c,
  vsbanevsp03c
};

signed char vsbanevsp00[14] = {
    0,   2, -10,   8,   0,   0, -12,  -1,  -5,   8,
    6,   0, -12,  -1
};
signed char vsbanevsp01[8] = {
    0,   1,  -5,   8,   0,   0, -12,  -1
};
signed char vsbanevsp02[20] = {
    0,   3, -15,   8,   0,   0, -12,  -1, -13,   0,
    9,   0,  -4,  -1,  -5,   8,  10,   0, -12,  -1
};
signed char vsbanehsp00[14] = {
    0,   2, -12,   2,   0,   8,   2,   0, -12,   2,
    6,   8,  -3,  -1
};
signed char vsbanehsp01[8] = {
    0,   1, -12,   2,   0,   8,  -3,  -1
};
signed char vsbanehsp02[20] = {
    0,   3, -12,   2,   0,   8,   7,   0,  -4,   0,
    9,   8,   5,   0, -12,   2,  10,   8,  -3,  -1
};
signed char vsbanevsp03[14] = {
    0,   2,   2,   8,   0,  16, -12,  -1,  -3,   8,
    6,  16, -12,  -1
};


signed char vsbanevsp00c[14] = {
    0,   2, -10,   8,   3,   0, -12,  -1,  -5,   8,
    6,   0, -12,  -1
};
signed char vsbanevsp01c[8] = {
    0,   1,  -5,   8,   3,   0, -12,  -1
};
signed char vsbanevsp02c[20] = {
    0,   3, -15,   8,   3,   0, -12,  -1, -13,   0,
    9,   0,  -4,  -1,  -5,   8,  10,   0, -12,  -1
};
signed char vsbanehsp00c[14] = {
    0,   2, -12,   2,   3,   8,   2,   0, -12,   2,
    6,   8,  -3,  -1
};
signed char vsbanehsp01c[8] = {
    0,   1, -12,   2,   3,   8,  -3,  -1
};
signed char vsbanehsp02c[20] = {
    0,   3, -12,   2,   3,   8,   7,   0,  -4,   0,
    9,   8,   5,   0, -12,   2,  10,   8,  -3,  -1
};
signed char vsbanevsp03c[14] = {
    0,   2,   2,   8,   3,  16, -12,  -1,  -3,   8,
    6,  16, -12,  -1
};


void sjumpmv(sprite_status* p_actwk) {
  sjump(p_actwk);
  sjumpmvkind(p_actwk);
}


static void sjumpmvkind(sprite_status* p_actwk) {
  sjumpmvkindtbl[(p_actwk->userflag1 >> 3 & 0xE) / 2](p_actwk);
}


static sprite_status_handler sjumpmvkindtbl[5] = {
  &sjumpmv_ymove,
  &sjumpmv_xmove,
  &sjumpmv_ymove2,
  &sjumpmv_xymove,
  &sjumpmv_xymove2
};


static void sjumpmv_ymove(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_ymove1;
  sjumpmv_ymove1(p_actwk);
}


static void sjumpmv_ymove1(sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short yposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
  sjumpmove(p_actwk);
}


static void sjumpmv_xmove(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_xmove1;
  sjumpmv_xmove1(p_actwk);
}


static void sjumpmv_xmove1(sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short xposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
  sdashmove(p_actwk);
}


static void sjumpmv_ymove2(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_ymove3;
  sjumpmv_ymove3(p_actwk);
}


static void sjumpmv_ymove3(sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short yposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
  sjumprmove(p_actwk);
}


static void sjumpmv_xymove(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_xymove1;
  sjumpmv_xymove1(p_actwk);
}


static void sjumpmv_xymove1(sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short xposi = p_actwk->actfree.spring.offset / 256;
  short yposi = xposi;
  if (!BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    xposi = -xposi;
  }
  xposi += p_actwk->actfree.spring.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
  yposi += p_actwk->actfree.spring.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
  sjump45move(p_actwk);
}


static void sjumpmv_xymove2(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_xymove3;
  sjumpmv_xymove3(p_actwk);
}


static void sjumpmv_xymove3(sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short xposi = p_actwk->actfree.spring.offset / 256;
  short yposi = xposi;
  if (BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
    xposi = -xposi;
  }
  xposi += p_actwk->actfree.spring.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
  yposi += p_actwk->actfree.spring.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
  sjump45rmove(p_actwk);
}


static void sjumpmv_sub(sprite_status* p_actwk) {
  if (p_actwk->actfree.spring.move_countdown != 0) {
    --p_actwk->actfree.spring.move_countdown;
    if (p_actwk->actfree.spring.move_countdown != 0) return;
    if (!IS_ONSCREEN(p_actwk->actflg)) return;
    soundset(82);
  }
  else if (p_actwk->actfree.spring.move_dir != 0) {
    bool gt_or_eq = p_actwk->actfree.spring.offset >= 0x800; // unsigned
    p_actwk->actfree.spring.offset -= 0x800;
    if (gt_or_eq) return;
    p_actwk->actfree.spring.offset = 0;
    p_actwk->actfree.spring.move_dir = 0;
    p_actwk->actfree.spring.move_countdown = 60;
  }
  else {
    p_actwk->actfree.spring.offset += 0x800;
    if (p_actwk->actfree.spring.offset < 0x2000) return;
    p_actwk->actfree.spring.offset = 0x2000;
    p_actwk->actfree.spring.move_dir = 1;
    p_actwk->actfree.spring.move_countdown = 60;
  }
}


static unsigned char sjumpswtbl[32] = {
  12,  8,  0,  1,
  12,  8,  0,  0,
  12,  8,  0,  1,
   8, 12,  1,  0,
  12,  8,  2,  1,
  12,  8,  3,  1,
  12,  8,  2,  1,
  12,  8,  3,  1
};


void sjumpsw(sprite_status* p_actwk) {
  short slot_cnt;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
  if (created) {
    p_new_actwk->r_ptr = &sjumpswmove;
    p_new_actwk->patbase = banedaipat;
    p_new_actwk->sproffset = 913;
    if (stageno.zone == ENDLESS_MINE) {
      p_new_actwk->patbase = banedaipat2;
    }
    p_new_actwk->userflag1 = p_actwk->userflag1;
    unsigned char* sjumpsw_init = &sjumpswtbl[p_actwk->userflag1 >> 2 & 0x1C];
    p_new_actwk->sprhs = sjumpsw_init[0];
    p_new_actwk->sprvs = sjumpsw_init[1];
    p_new_actwk->patno = sjumpsw_init[2];
    if (p_new_actwk->patno == 0) {
      p_new_actwk->r_ptr = &sjumpswmove2;
    }
    p_actwk->userflag1 &= 0xF0;
    p_actwk->userflag1 |= sjumpsw_init[3];
    util__copy_high(&p_new_actwk->xposi, &p_actwk->xposi);
    util__copy_high(&p_new_actwk->yposi, &p_actwk->yposi);
    short xoffset = 0, yoffset = 0;
    if (p_new_actwk->patno == 1) {
      xoffset = 12;
      if (!BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
        xoffset = -xoffset;
      }
      p_new_actwk->xposi += SHORT_TO_LONG_HIGH(xoffset);
    }
    if (p_new_actwk->patno == 2) {
      yoffset = 11;
      p_new_actwk->yposi += SHORT_TO_LONG_HIGH(yoffset);
    }
    if (p_new_actwk->patno == 3) {
      yoffset = -11;
      p_new_actwk->yposi += SHORT_TO_LONG_HIGH(yoffset);
    }
    p_new_actwk->actfree.springsw.xoffset = xoffset;
    p_new_actwk->actfree.springsw.yoffset = yoffset;
    CLEAR_BIT(p_actwk->cddat1, CD_DOWN);
    if (p_actwk->cddat1 != 0) {
      p_actwk->actfree.spring.unknown_flag = 1;
    }
    p_new_actwk->cddat1 = p_actwk->cddat1;
    p_new_actwk->actflg = p_actwk->actflg;
    SET_USE_LEVEL_COORDS(p_new_actwk->actflg);
    p_new_actwk->sprpri = PRI_4;
    p_new_actwk->actfree.springsw.parent = p_actwk - actwk;
    p_actwk->actfree.spring.child = p_new_actwk - actwk;
  }
  sjumpswinit(p_actwk);
}


static void sjumpswkind(sprite_status* p_actwk) {
  sjumpswkindtbl[(p_actwk->userflag1 >> 3 & 14) / 2](p_actwk);
}


static sprite_status_handler sjumpswkindtbl[8] = {
  &sjumpsw_ymove,
  &sjumpsw_xmove,
  &sjumpsw_ymove2,
  &sjumpsw_ymove4,
  &sjumpsw_xmove2,
  &sjumpsw_xmove4,
  &sjumpsw_xmove2,
  &sjumpsw_xmove4
};


static void sjumpsw_ymove(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_ymove1;
  sjumpsw_ymove1(p_actwk);
}


static void sjumpsw_ymove1(sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short yposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
  vssjumpmove(p_actwk);
}


static void sjumpsw_xmove(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_xmove1;
  sjumpsw_xmove1(p_actwk);
}


static void sjumpsw_xmove1(sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short xposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
  vssdashmove(p_actwk);
}


static void sjumpsw_ymove2(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_ymove3;
  sjumpsw_ymove3(p_actwk);
}


static void sjumpsw_ymove3(sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short yposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
  vssjumprmove(p_actwk);
}


static void sjumpsw_ymove4(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_ymove5;
  sjumpsw_ymove5(p_actwk);
}


static void sjumpsw_ymove5(sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short yposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
  vssdashmove(p_actwk);
}


static void sjumpsw_xmove2(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_xmove3;
  sjumpsw_xmove3(p_actwk);
}


static void sjumpsw_xmove3(sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short xposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
  vssjumpmove(p_actwk);
}


static void sjumpsw_xmove4(sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_xmove5;
  sjumpsw_xmove5(p_actwk);
}


static void sjumpsw_xmove5(sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short xposi = p_actwk->actfree.spring.offset / 256 + p_actwk->actfree.spring.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
  vssjumprmove(p_actwk);
}


static void sjumpsw_sub(sprite_status* p_actwk) {
  if (BIT_7_IS_SET(p_actwk->userflag1)) {
    sjumpsw_sub2(p_actwk);
    return;
  }
  if (p_actwk->actfree.spring.move_countdown != 0) {
    --p_actwk->actfree.spring.move_countdown;
    if (p_actwk->actfree.spring.move_countdown != 0) return;
    if (!IS_ONSCREEN(p_actwk->actflg)) return;
    soundset(82);
  }
  else if (p_actwk->actfree.spring.move_dir != 0) {
    bool gt_or_eq = p_actwk->actfree.spring.offset >= 0x800; // unsigned
    p_actwk->actfree.spring.offset -= 0x800;
    if (gt_or_eq) return;
    p_actwk->actfree.spring.offset = 0;
    p_actwk->actfree.spring.move_dir = 0;
    p_actwk->actfree.spring.move_countdown = 60;
  }
  else {
    p_actwk->actfree.spring.offset += 0x800;
    if (p_actwk->actfree.spring.offset < 0x1800) return; // unsigned
    p_actwk->actfree.spring.offset = 0x1800;
    p_actwk->actfree.spring.move_dir = 1;
    p_actwk->actfree.spring.move_countdown = 60;
  }
}


static void sjumpsw_sub2(sprite_status* p_actwk) {
  if (p_actwk->actfree.spring.unknown_flag == 0) {
    sjumpsw_sub3(p_actwk);
    return;
  }
  if (p_actwk->actfree.spring.move_countdown != 0) {
    --p_actwk->actfree.spring.move_countdown;
    if (p_actwk->actfree.spring.move_countdown != 0) return;
    p_actwk->actfree.spring.move_dir = 0;
  }
  else if (p_actwk->actfree.spring.move_dir == 0) {
    if (p_actwk->actfree.spring.offset == 0) return;
    bool gt = p_actwk->actfree.spring.offset > 0x800; // unsigned
    p_actwk->actfree.spring.offset -= 0x800;
    if (gt) return;
    p_actwk->actfree.spring.offset = 0;
    unsigned char userflag = p_actwk->userflag1 & 0xF0;
    if (userflag == 224) {
      p_actwk->yposi += SHORT_TO_LONG_HIGH(22);
      TOGGLE_BIT(p_actwk->cddat1, CD_DOWN);
      TOGGLE_VFLIP(p_actwk->actflg);
      p_actwk->userflag1 &= 0xF;
      p_actwk->userflag1 |= 0xF0;
      p_actwk->r_ptr = &sjumpswkind;
      sprite_status* p_childwk = &actwk[p_actwk->actfree.spring.child];
      p_childwk->actfree.springsw.yoffset = -p_childwk->actfree.springsw.yoffset;
    }
    if (userflag == 240) {
      p_actwk->yposi -= SHORT_TO_LONG_HIGH(22);
      TOGGLE_BIT(p_actwk->cddat1, CD_DOWN);
      TOGGLE_VFLIP(p_actwk->actflg);
      p_actwk->userflag1 &= 0xF;
      p_actwk->userflag1 |= 0xE0;
      p_actwk->r_ptr = &sjumpswkind;
      sprite_status* p_childwk = &actwk[p_actwk->actfree.spring.child];
      p_childwk->actfree.springsw.yoffset = -p_childwk->actfree.springsw.yoffset;
    }
  }
  else {
    p_actwk->actfree.spring.offset += 0x800;
    if (p_actwk->actfree.spring.offset < 0x1800) return;
    p_actwk->actfree.spring.offset = 0x1800;
    p_actwk->actfree.spring.move_countdown = 180;
  }
}


static void sjumpsw_sub3(sprite_status* p_actwk) {
  if (p_actwk->actfree.spring.move_countdown != 0) {
    --p_actwk->actfree.spring.move_countdown;
    if (p_actwk->actfree.spring.move_countdown != 0) return;
    p_actwk->actfree.spring.move_dir = 0;
  }
  else if (p_actwk->actfree.spring.move_dir != 0) {
    bool gt_or_eq = p_actwk->actfree.spring.offset >= 0x800; // unsigned
    p_actwk->actfree.spring.offset -= 0x800;
    if (gt_or_eq) return;
    p_actwk->actfree.spring.offset = 0;
    p_actwk->actfree.spring.move_countdown = 180;
  }
  else if (p_actwk->actfree.spring.offset != 0x1800) {
    p_actwk->actfree.spring.offset += 0x800;
    if (p_actwk->actfree.spring.offset < 0x1800) return;
    p_actwk->actfree.spring.offset = 0x1800;
    unsigned char userflag = p_actwk->userflag1 & 0xF0;
    if (userflag == 224) {
      p_actwk->yposi += SHORT_TO_LONG_HIGH(22);
      TOGGLE_BIT(p_actwk->cddat1, CD_DOWN);
      TOGGLE_VFLIP(p_actwk->actflg);
      p_actwk->userflag1 &= 0xF;
      p_actwk->userflag1 |= 0xF0;
      p_actwk->r_ptr = &sjumpswkind;
      sprite_status* p_childwk = &actwk[p_actwk->actfree.spring.child];
      p_childwk->actfree.springsw.yoffset = -p_childwk->actfree.springsw.yoffset;
    }
    if (userflag == 240) {
      p_actwk->yposi -= SHORT_TO_LONG_HIGH(22);
      TOGGLE_BIT(p_actwk->cddat1, CD_DOWN);
      TOGGLE_VFLIP(p_actwk->actflg);
      p_actwk->userflag1 &= 0xF;
      p_actwk->userflag1 |= 0xE0;
      p_actwk->r_ptr = &sjumpswkind;
      sprite_status* p_childwk = &actwk[p_actwk->actfree.spring.child];
      p_childwk->actfree.springsw.yoffset = -p_childwk->actfree.springsw.yoffset;
    }
  }
}


static void sjumpswmove(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &actwk[p_actwk->actfree.springsw.parent];
  short xposi = LONG_HIGH(p_parentwk->xposi) + p_actwk->actfree.springsw.xoffset;
  short yposi = LONG_HIGH(p_parentwk->yposi) + p_actwk->actfree.springsw.yoffset;
  util__assign_high(&p_actwk->xposi, xposi);
  util__assign_high(&p_actwk->yposi, yposi);
  if (BIT_7_IS_SET(p_actwk->userflag1)) {
    if (level_triggers[p_actwk->userflag1 & 0xF] != 0) {
      p_parentwk->actfree.spring.move_dir = 1;
    }
  }
  hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  actionsub(p_actwk);
}


static void sjumpswmove2(sprite_status* p_actwk) {
  if (!BIT_7_IS_SET(p_actwk->userflag1)) return;
  if (level_triggers[p_actwk->userflag1 & 0xF] != 0) {
    sprite_status* p_parentwk = &actwk[p_actwk->actfree.springsw.parent];
    p_parentwk->actfree.spring.move_dir = 1;
  }
}


static signed char* banedaipat[4] = {
  banedaisp00,
  banedaisp01,
  banedaisp02,
  banedaisp02
};


static signed char* banedaipat2[4] = {
  banedaisp00,
  banedaisp03,
  banedaisp02,
  banedaisp02
};


static signed char banedaisp00[2] = {
    0,   0
};
static signed char banedaisp01[8] = {
    0,   1, -12,   6,  47,   8,  -8,  -1
};
static signed char banedaisp02[8] = {
    0,   1,  -8,   9,  13,  96, -12,  -1
};
static signed char banedaisp03[8] = {
    0,   1, -12,  10, 116,  71, -16,  -1
};
