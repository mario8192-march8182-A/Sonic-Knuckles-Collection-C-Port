#include "globals.h"
#include "macros.h"
#include "util.h"
#include "save.h"
#include "004xxxxx.h"
static sprite_status_handler save_move_tbl[5];
static void saveinit(sprite_status* pActwk);
static void savemove(sprite_status* pActwk);
static void savemove__sub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void savemove2(sprite_status* pActwk);
static void savemove3(sprite_status* p_actwk);
static void playsave(sprite_status* p_actwk);
static signed char* savechg[3];
static signed char savechg0[3];
static signed char savechg1[3];
static signed char savechg2[4];
static signed char savesp00[26];
static signed char savesp01[20];
static signed char savesp02[8];
static signed char savesp03[8];
static signed char savesp04[26];


void save(sprite_status* p_actwk) {
  save_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static sprite_status_handler save_move_tbl[5] = {
  &saveinit,
  &savemove,
  &savemove2,
  &savemove3,
  &o_star
};


static void saveinit(sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = savepat;
  p_actwk->sproffset = 1516;
  p_actwk->actflg = 4;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 40;
  p_actwk->sprpri = 640;
  if (BIT_0_IS_SET(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1])
      || (markerno & 0x7F) >= (p_actwk->userflag1 & 0x7F)) { // unsigned
    SET_BIT_0(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1]);
    p_actwk->mstno = 2;
  }
  savemove(p_actwk);
}


static void savemove(sprite_status* p_actwk) {
  if (edit_r_no == 0) {
    savemove__sub(p_actwk, &actwk[0]);
  }
  savemove2(p_actwk);
}


static void savemove__sub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  if ((markerno & 0x7F) < (p_actwk->userflag1 & 0x7F)) {
    short distance = LONG_HIGH_TO_SHORT(p_actwk->xposi) - LONG_HIGH_TO_SHORT(p_playerwk->xposi) + 8;
    if (util__to_unsigned(distance) >= 16) return; // unsigned
    distance = LONG_HIGH_TO_SHORT(p_actwk->yposi) - LONG_HIGH_TO_SHORT(p_playerwk->yposi) + 64;
    if (util__to_unsigned(distance) >= 104) return; // unsigned
    soundset(99);
    sprite_status* p_new_actwk;
    bool created = Create_New_Sprite(&p_new_actwk);
    if (created) {
      p_new_actwk->r_ptr = &save;
      p_new_actwk->r_no = 6;
      SPRITE_STATUS_SHORT(p_new_actwk, 48) = LONG_HIGH_TO_SHORT(p_actwk->xposi);
      SPRITE_STATUS_SHORT(p_new_actwk, 50) = LONG_HIGH_TO_SHORT(p_actwk->yposi) - 20;
      p_new_actwk->patbase = p_actwk->patbase;
      p_new_actwk->sproffset = p_actwk->sproffset;
      p_new_actwk->actflg = p_actwk->actflg;
      p_new_actwk->sprhs = 8;
      p_new_actwk->sprvs = 8;
      p_new_actwk->sprpri = 512;
      p_new_actwk->patno = 2;
      SPRITE_STATUS_USHORT(p_new_actwk, 54) = 32;
      SPRITE_STATUS_USHORT(p_new_actwk, 62) = p_actwk - actwk;
      bool enough_rings = false;
      if (Sonic_3_alone) {
        enough_rings = plring >= 50;
      }
      else {
        enough_rings = plring >= 20;
      }
      if (enough_rings) {
        o_starinit(p_actwk);
      }
    }
    p_actwk->mstno = 1;
    playsave(p_actwk);
    p_actwk->r_no = 4;
    SET_BIT_0(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1]);
  }
  else if (p_actwk->mstno == 0) {
    p_actwk->mstno = 2;
  }
}


static void savemove2(sprite_status* p_actwk) {
  patchg(p_actwk, savechg);
  frameoutchk(p_actwk);
}


static void savemove3(sprite_status* p_actwk) {
  --SPRITE_STATUS_SHORT(p_actwk, 54);
  if (SPRITE_STATUS_SHORT(p_actwk, 54) < 0) {
    sprite_status* p_sub_actwk = &actwk[SPRITE_STATUS_USHORT(p_actwk, 62)];
    if (p_sub_actwk->r_ptr == &save) {
      p_sub_actwk->mstno = 2;
      p_sub_actwk->patno = 0;
    }
    frameout(p_actwk);
  }
  else {
    p_actwk->direc1 -= 16;
    short sin, cos;
    sinset(util__to_unsigned(p_actwk->direc1 - 64), &sin, &cos);
    long cos_l = cos * 3072;
    cos_l = LONG_LOW(cos_l) + SPRITE_STATUS_SHORT(p_actwk, 48);
    p_actwk->xposi = SHORT_TO_LONG_HIGH(LONG_LOW(cos_l)) + LONG_LOW(p_actwk->xposi);
    long sin_l = sin * 3072;
    sin_l = LONG_LOW(sin_l) + SPRITE_STATUS_SHORT(p_actwk, 50);
    p_actwk->yposi = SHORT_TO_LONG_HIGH(LONG_LOW(sin_l)) + LONG_LOW(p_actwk->yposi);
    frameoutchk(p_actwk);
  }
}


static void playsave(sprite_status* p_actwk) {
  markerno = p_actwk->userflag1;
  plxposi_s = LONG_HIGH_TO_SHORT(p_actwk->xposi);
  plyposi_s = LONG_HIGH_TO_SHORT(p_actwk->yposi);
  playsave1(p_actwk);
}


void playsave1(sprite_status* p_actwk) {
  markerno_s = markerno;
  stageno_s = stageno;
  stageno_is = stageno_i;
  plsproffset_s = actwk[0].sproffset;
  plcolibits_s = SPRITE_STATUS_USHORT(&actwk[0], 70);
  plring_s = plring;
  plring_f2_s = plring_f2;
  pltime_s = pltime;
  scr_resize_no_s = scr_resize_no;
  scralim_down_s = scralim_down;
  scra_h_posit_s = LONG_HIGH_TO_SHORT(scra_h_posit);
  scra_v_posit_s = LONG_HIGH_TO_SHORT(scra_v_posit);
  waterposi_s = waterposi;
  waterflag_s = waterflag;
}


void playsave2(sprite_status* p_actwk) {
  markerno_s2 = markerno;
  stageno_s2 = stageno;
  stageno_is2 = stageno_i;
  plxposi_s2 = LONG_HIGH_TO_SHORT(p_actwk->xposi);
  plyposi_s2 = LONG_HIGH_TO_SHORT(p_actwk->yposi);
  plsproffset_s2 = actwk[0].sproffset;
  plcolibits_s2 = SPRITE_STATUS_USHORT(&actwk[0], 70);
  plring_s2 = plring;
  plring_f2_s2 = plring_f2;
  pltime_s2 = pltime;
  scr_resize_no_s2 = scr_resize_no;
  scralim_down_s2 = scralim_down;
  scra_h_posit_s2 = LONG_HIGH_TO_SHORT(scra_h_posit);
  scra_v_posit_s2 = LONG_HIGH_TO_SHORT(scra_v_posit);
  waterposi_s2 = waterposi;
  waterflag_s2 = waterflag;
  plcddat2_s2 = actwk[0].cddat2;
}


static signed char* savechg[3] = {
  savechg0,
  savechg1,
  savechg2
};


static signed char savechg0[3] = { 15, 0, -1 };
static signed char savechg1[3] = { 15, 1, -1 };
static signed char savechg2[4] = { 3, 0, 4, -1 };


signed char* savepat[5] = {
  savesp00,
  savesp01,
  savesp02,
  savesp03,
  savesp04
};


static signed char savesp00[26] = { 0, 4, -24, 1, 14, 0, -4, -1, -8, 3, 16, 0, -8, -1, -8, 3, 16, 8, 0, 0, -40, 5, 6, 0, -8, -1 };
static signed char savesp01[20] = { 0, 3, -24, 1, 14, 0, -4, -1, -8, 3, 16, 0, -8, -1, -8, 3, 16, 8, 0, 0 };
static signed char savesp02[8] = { 0, 1, -8, 5, 6, 0, -8, -1 };
static signed char savesp03[8] = { 0, 1, -8, 5, 10, 0, -8, -1 };
static signed char savesp04[26] = { 0, 4, -24, 1, 14, 0, -4, -1, -8, 3, 16, 0, -8, -1, -8, 3, 16, 8, 0, 0, -40, 5, 10, 0, -8, -1 };
