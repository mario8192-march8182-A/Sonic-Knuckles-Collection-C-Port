#include "globals.h"
#include "macros.h"
#include "util.h"
#include "tloop.h"
#include "004xxxxx.h"
static void tloopinit(sprite_status* p_actwk);
static void tloopmove(sprite_status* p_actwk);
static void tloopmovesub(sprite_status* p_actwk);
static void tloopmovesub__sub(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit);
static void tloopmovesub__rideon(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit);
static void tloopmovesub__jumpdown(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit);
static void tloopmovesub__jump1(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit);
static void tloopmovesub__jump11(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit);
static void tloopmovesub__jump2(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit);
static unsigned char tloopdirtbl[55];


void tloop(sprite_status* p_actwk) {
  tloopinit(p_actwk);
}


static void tloopinit(sprite_status* p_actwk) {
  p_actwk->sprhs = 208;
  p_actwk->r_ptr = &tloopmove;
  tloopmove(p_actwk);
}


static void tloopmove(sprite_status* p_actwk) {
  tloopmovesub(p_actwk);
  if (!(p_actwk->cddat1 & 0x18) && p_actwk->actfree.tloop.countdown != 0) {
    --p_actwk->actfree.tloop.countdown;
    if (p_actwk->actfree.tloop.countdown == 0) {
      scralim_left = 4864;
      scralim_right = 16384;
    }
    else {
      if (scralim_left != 4864) {
        if (LONG_HIGH(actwk[0].xposi) >= 11520) { // unsigned
          scralim_left = 4864;
        }
        else {
          scralim_left -= 4;
        }
      }
      if (scralim_right != 16384) {
        if (LONG_HIGH(actwk[0].xposi) < 11520) { // unsigned
          scralim_right = 16384;
        }
        else {
          scralim_right += 4;
        }
      }
    }
  }
  frameoutchk3(p_actwk);
}


static void tloopmovesub(sprite_status* p_actwk) {
  tloopmovesub__sub(p_actwk, &actwk[0], &p_actwk->actfree.tloop.pldir_counter, 3);
  tloopmovesub__sub(p_actwk, &actwk[1], &p_actwk->actfree.tloop.pl2dir_counter , 4);
}


static void tloopmovesub__sub(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit) {
  if (BIT_IS_SET(p_playerwk->cddat1, plridebit)) {
    tloopmovesub__rideon(p_actwk, p_playerwk, pldir_counter, plridebit);
    return;
  }
  if (BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) return;
  if (util__to_unsigned(LONG_HIGH(p_playerwk->xposi) + 16) < util__to_unsigned(LONG_HIGH(p_actwk->xposi))) return; // unsigned
  short relative_xposi = LONG_HIGH(p_playerwk->xposi) + 16 - LONG_HIGH(p_actwk->xposi);
  if (relative_xposi >= 64) return;
  short relative_yposi = LONG_HIGH(p_playerwk->yposi) - LONG_HIGH(p_actwk->yposi);
  if (relative_yposi < -90) return;
  if (relative_yposi > 160) return;
  if (actwk[0].xspeed < 1536) return;
  if (p_playerwk->actfree.player.control_bitfield != 0) return;
  RideObject_SetRide(p_actwk, p_playerwk);
  *pldir_counter = 0;
  SET_BIT_6(p_playerwk->actfree.player.control_bitfield);
  SET_BIT_1(p_playerwk->actfree.player.control_bitfield);
  p_playerwk->mstno = 0;
  if (p_playerwk == &actwk[0]) return;
  short slot_cnt;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
  if (created) {
    p_new_actwk->r_ptr = &Obj_AIZ1TreeRevealControl;
  }
  scralim_left = 11360;
  scralim_right = 11360;
  p_actwk->actfree.tloop.countdown = 60;
}


static void tloopmovesub__rideon(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit) {
  short mspeed = p_playerwk->mspeed;
  if (mspeed < 0) {
    mspeed = -mspeed;
  }
  if (mspeed < 1536) { // unsigned
    tloopmovesub__jump11(p_actwk, p_playerwk, pldir_counter, plridebit);
    return;
  }
  if (BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    tloopmovesub__jumpdown(p_actwk, p_playerwk, pldir_counter, plridebit);
    return;
  }
  short yposi = LONG_HIGH(p_playerwk->yposi) - LONG_HIGH(p_actwk->yposi) + 144;
  if (yposi >= 0 && yposi <= 304) { // unsigned
    tloopmovesub__jump2(p_actwk, p_playerwk, pldir_counter, plridebit);
  }
  else {
    tloopmovesub__jump1(p_actwk, p_playerwk, pldir_counter, plridebit);
  }
}

static void tloopmovesub__jumpdown(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit) {
  if (util__to_unsigned(LONG_HIGH(p_playerwk->xposi)) < 11417) { // unsigned
    util__assign_high(&p_playerwk->xposi, 11417);
    p_playerwk->xspeed = 1024;
  }
  if (util__to_unsigned(LONG_HIGH(p_playerwk->xposi)) >= 11622) { // unsigned
    util__assign_high(&p_playerwk->xposi, 11622);
    p_playerwk->xspeed = -1024;
  }
  tloopmovesub__jump1(p_actwk, p_playerwk, pldir_counter, plridebit);
}


static void tloopmovesub__jump1(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit) {
  SET_BIT(p_playerwk->cddat1, CD_JUMP);
  CLEAR_BIT(p_playerwk->cddat1, CD_BALL);
  p_playerwk->sprvsize = 19;
  p_playerwk->sprhsize = 9;
  p_playerwk->mstno = 0;
  p_playerwk->restart = 1;
  CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
  CLEAR_BIT(p_playerwk->cddat1, plridebit);
  p_playerwk->actfree.player.flip_rev_cnt = 0;
  p_playerwk->actfree.player.flip_rev_frame_cnt = 4;
  CLEAR_BIT_6(p_playerwk->actfree.player.control_bitfield);
  CLEAR_BIT_1(p_playerwk->actfree.player.control_bitfield);
  p_playerwk->xspeed /= 2;
  p_playerwk->yspeed /= 2;
}

static void tloopmovesub__jump11(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit) {
  if (LONG_HIGH(*pldir_counter) >= 1024) {
    tloopmovesub__jump2(p_actwk, p_playerwk, pldir_counter, plridebit);
  }
  tloopmovesub__jump1(p_actwk, p_playerwk, pldir_counter, plridebit);
}


static void tloopmovesub__jump2(sprite_status* p_actwk, sprite_status* p_playerwk, long* pldir_counter, unsigned char plridebit) {
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_RIDE)) return;
  *pldir_counter += p_playerwk->mspeed * 256;
  if (*pldir_counter < 0) {
    tloopmovesub__jump1(p_actwk, p_playerwk, pldir_counter, plridebit);
    return;
  }
  if (LONG_HIGH(*pldir_counter) >= 1024) {
    scralim_left = 4864;
    scralim_right= 16384;
  }
  short plxposi = LONG_HIGH(p_playerwk->xposi);
  unsigned char angle = LONG_HIGH(*pldir_counter) / 2;
  short sin, cos;
  sinset(angle, &sin, &cos);
  long temp = sin * 28672;
  short new_plxposi = LONG_HIGH(temp) + LONG_HIGH(p_actwk->xposi);
  util__assign_high(&p_playerwk->xposi, new_plxposi);
  p_playerwk->xspeed = (new_plxposi - plxposi) * 256;
  short plyposi = LONG_HIGH(p_playerwk->yposi);
  short new_plyposi = -(LONG_HIGH(*pldir_counter) / 4) + 144 + LONG_HIGH(p_actwk->yposi);
  util__assign_high(&p_playerwk->yposi, new_plyposi);
  p_playerwk->yspeed = (new_plyposi - plyposi) * 256;
  p_playerwk->patno = tloopdirtbl[(*pldir_counter / 2) / 11];
  Perform_Player_DPLC(p_playerwk, p_playerwk->patno);
}


static unsigned char tloopdirtbl[55] = {
  105, 106, 107, 119, 108, 108, 109, 109, 110, 110,
  111, 111, 112, 112, 113, 113, 114, 114, 115, 115,
  116, 116, 117, 117, 118, 118, 119, 119, 108, 108,
  109, 109, 110, 110, 111, 111, 112, 112, 113, 113,
  114, 114, 115, 115, 116, 116, 117, 117, 107, 107,
  106, 106, 105, 105, 144
};
