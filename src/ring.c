#include "globals.h"
#include "macros.h"
#include "util.h"
#include "ring.h"
#include "004xxxxx.h"
static sprite_status_handler ring_move_tbl[5];
static void ringinit(sprite_status* p_actwk);
static void ringmove(sprite_status* p_actwk);
static void ringget(sprite_status* p_actwk);
static void ringdie(sprite_status* p_actwk);
static void ringerase(sprite_status* p_actwk);
static void ringgetsub1(sprite_status* p_actwk);
static sprite_status_handler flyring_move_tbl[5];
static void flyringg(sprite_status* p_actwk);
static sprite_status_handler flyring_move_tblg[5];
static void flyringinit(sprite_status* p_actwk);
static void flyringmove(sprite_status* p_actwk);
static void flyringget(sprite_status* p_actwk);
static void flyringdie(sprite_status* p_actwk);
static void flyringerase(sprite_status* p_actwk);
static void flyringmoveg(sprite_status* p_actwk);
static void tringmove(sprite_status* p_actwk);
static void tringdie(sprite_status* p_actwk);
static void tringerase(sprite_status* p_actwk);
static void tringspdset(sprite_status* p_actwk);
static signed char* ringchg[1];
static signed char ringchg0[9];
static signed char ringsp0[8];
static signed char ringsp1[8];
static signed char ringsp2[8];
static signed char ringsp3[8];
static signed char ringsp4[8];
static signed char ringsp5[8];
static signed char ringsp6[8];
static signed char ringsp7[8];
static signed char ringsp8[2];
static sprite_status_handler slot_ring_move_tbl[3];
static void slot_ring_move(sprite_status* p_actwk);
static void slot_ring_get(sprite_status* p_actwk);
static void slot_ring_clr(sprite_status* p_actwk);
static signed char* sringchg[1];
static signed char sringchg0[9];


void ring(sprite_status* p_actwk) {
  ring_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static sprite_status_handler ring_move_tbl[5] = {
  &ringinit,
  &ringmove,
  &ringget,
  &ringdie,
  &ringerase
};


static void ringinit(sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = ringpat;
  p_actwk->sproffset = 42684;
  p_actwk->actflg = 4;
  p_actwk->sprpri = PRI_4;
  p_actwk->colino = 71;
  p_actwk->sprhs = 8;
  if (vs_flag != 0) {
    p_actwk->sproffset = 25554;
  }
  ringmove(p_actwk);
}


static void ringmove(sprite_status* p_actwk) {
  p_actwk->patno = ring_patno;
  frameoutchkc(p_actwk, LONG_HIGH_TO_SHORT(p_actwk->xposi));
}


static void ringget(sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->colino = 0;
  p_actwk->sprpri = PRI_1;
  ringgetsub(p_actwk);
  ringdie(p_actwk);
}


static void ringdie(sprite_status* p_actwk) {
  patchg(p_actwk, ringchg);
  actionsub(p_actwk);
}


static void ringerase(sprite_status* p_actwk) {
  frameout(p_actwk);
}


void ringgetsub(sprite_status* p_actwk) {
  if (plring_act < 999) {
    ++plring_act;
  }
  ringgetsub1(p_actwk);
}


static void ringgetsub1(sprite_status* p_actwk) {
  if (plring < 999) {
    ++plring;
    SET_BIT_0(plring_f);
    if (plring >= 100) {
      bool bit_1_clear = !BIT_1_IS_SET(plring_f2);
      SET_BIT_1(plring_f2);
      if (bit_1_clear) goto LAB_1up;
      if (plring >= 200) {
        bool bit_2_clear = !BIT_2_IS_SET(plring_f2);
        SET_BIT_2(plring_f2);
        if (bit_2_clear) {
LAB_1up:
          ++pl_suu;
          ++pl_suu_f;
          bgmset(42);
          return;
        }
      }
    }
  }
  soundset(51);
}


void ringgetsub2(sprite_status* p_actwk) {
  if (pl2ring_act < 999) {
    ++pl2ring_act;
  }
  if (pl2ring < 999) {
    ++pl2ring;
  }
  if (vs_flag == 0) {
    ringgetsub1(p_actwk);
    return;
  }
  SET_BIT_0(pl2ring_f);
  if (pl2ring >= 100) {
    bool bit_1_clear = !BIT_1_IS_SET(pl2ring_f2);
    SET_BIT_1(pl2ring_f2);
    if (bit_1_clear) goto LAB_1up;
    if (pl2ring >= 200) {
      bool bit_2_clear = !BIT_2_IS_SET(pl2ring_f2);
      SET_BIT_2(pl2ring_f2);
      if (bit_2_clear) {
LAB_1up:
        ++pl2_suu;
        bgmset(42);
        return;
      }
    }
  }
  soundset(51);
}


void flyring(sprite_status* p_actwk) {
  flyring_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static sprite_status_handler flyring_move_tbl[5] = {
  &flyringinit,
  &flyringmove,
  &flyringget,
  &flyringdie,
  &flyringerase
};


static void flyringg(sprite_status* p_actwk) {
  flyring_move_tblg[p_actwk->r_no / 2](p_actwk);
}


static sprite_status_handler flyring_move_tblg[5] = {
  &flyringinit,
  &flyringmoveg,
  &flyringget,
  &flyringdie,
  &flyringerase
};


static void flyringinit(sprite_status* p_actwk) {
  sprite_status_handler p_routine = &flyring;
  if (reverse_gravity_flag != 0) {
    p_routine = flyringg;
  }
  sprite_status* p_new_actwk = p_actwk;
  short flyring_cnt = plring;
  if (p_actwk->actfree.ring.player != 0) {
    flyring_cnt = pl2ring;
  }
  if (flyring_cnt >= 32) {
    flyring_cnt = 32;
  }
  --flyring_cnt;
  short angle = 648;
  short xspeed, yspeed;
  goto jump;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) break;

jump:
    p_new_actwk->r_ptr = p_routine;
    p_new_actwk->r_no += 2;
    p_new_actwk->sprvsize = 8;
    p_new_actwk->sprhsize = 8;
    util__copy_high(&p_new_actwk->xposi, &p_actwk->xposi);
    util__copy_high(&p_new_actwk->yposi, &p_actwk->xposi);
    p_new_actwk->patbase = ringpat;
    p_new_actwk->sproffset = 42684;
    p_new_actwk->actflg = 132;
    p_new_actwk->sprpri = PRI_3;
    p_new_actwk->colino = 71;
    p_new_actwk->sprhs = 8;
    flyring_patcnt = 255;
    if (angle >= 0) {
      short sin, cos;
      sinset(angle & 0xFF, &sin, &cos);
      unsigned char exponent = angle >> 8;
      sin <<= exponent;
      cos <<= exponent;
      xspeed = sin;
      yspeed = cos;
      // The lower byte is incremented by 16 without affecting the upper byte.
      unsigned short angle_wk = (angle & 0xFF) + 16;
      angle = angle & 0xFF00 | angle_wk & 0xFF;
      if (angle_wk >= 256) { // Detect if the addition overflowed the lower byte.
        angle -= 128;
        if (angle < 128) {
          angle = 648;
        }
      }
    }
    p_new_actwk->xspeed = xspeed;
    p_new_actwk->yspeed = yspeed;
    xspeed = -xspeed;
    angle = -angle;
    --flyring_cnt;
  } while (flyring_cnt != -1);

  soundset(65465);
  plring = 0;
  plring_f = 128;
  plring_f2 = 0;
  if (reverse_gravity_flag != 0) {
    flyringmoveg(p_actwk);
  }
  else {
    flyringmove(p_actwk);
  }
}


static void flyringmove(sprite_status* p_actwk) {
  p_actwk->patno = flyring_patno;
  speedset2(p_actwk);
  p_actwk->yspeed += 24;
  if (p_actwk->yspeed >= 0) {
    if (!((systemtimer % 256 + (p_actwk - actwk - 1)) % 8)) {
      if (BIT_7_IS_SET(p_actwk->actflg)) {
        short unknown1 = RingCheckFloorDist(p_actwk);
        if (unknown1 < 0) {
          p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown1);
          p_actwk->yspeed -= p_actwk->yspeed / 4;
          p_actwk->yspeed = -p_actwk->yspeed;
        }
      }
      if (flyring_patcnt == 0) {
        flyringerase(p_actwk);
        return;
      }
      if (scralim_down + 224 < LONG_HIGH_TO_SHORT(p_actwk->yposi)) {
        flyringerase(p_actwk);
        return;
      }
    }
  }
  Add_Object_To_Collision_Response_List(p_actwk);
  p_actwk->xposi += SHORT_TO_LONG_HIGH(frame_offset_x);
  actionsub(p_actwk);
}


static void flyringget(sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->colino = 0;
  p_actwk->sprpri = PRI_1;
  ringgetsub(p_actwk);
  flyringdie(p_actwk);
}


static void flyringdie(sprite_status* p_actwk) {
  patchg(p_actwk, ringchg);
  actionsub(p_actwk);
}


static void flyringerase(sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void flyringmoveg(sprite_status* p_actwk) {
  p_actwk->patno = flyring_patno;
  speedset2g(p_actwk);
  p_actwk->yspeed += 24;
  if (p_actwk->yspeed >= 0) {
    if (!((systemtimer % 256 + (p_actwk - actwk - 1)) % 8)) {
      if (BIT_7_IS_SET(p_actwk->actflg)) {
        short unknown1 = RingCheckFloorDist_ReverseGravity(p_actwk);
        if (unknown1 < 0) {
          p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown1);
          p_actwk->yspeed -= p_actwk->yspeed / 4;
          p_actwk->yspeed = -p_actwk->yspeed;
        }
      }
      if (flyring_patcnt == 0) {
        flyringerase(p_actwk);
        return;
      }
      if (scralim_down + 224 < LONG_HIGH_TO_SHORT(p_actwk->yposi)) {
        flyringerase(p_actwk);
        return;
      }
    }
  }
  Add_Object_To_Collision_Response_List(p_actwk);
  p_actwk->xposi += SHORT_TO_LONG_HIGH(frame_offset_x);
  actionsub(p_actwk);
}


void tring(sprite_status* p_actwk) {
  p_actwk->patbase = ringpat;
  p_actwk->sproffset = 42684;
  p_actwk->actflg = 4;
  p_actwk->sprpri = PRI_2;
  p_actwk->colino = 71;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
  p_actwk->sprvsize = 8;
  p_actwk->sprhsize = 8;
  p_actwk->r_ptr = &tringmove;
  tringmove(p_actwk);
}


static void tringmove(sprite_status* p_actwk) {
  if (p_actwk->r_no == 0) {
    tringspdset(p_actwk);
    if (!BIT_5_IS_SET(actwk[0].cddat2)) {
      p_actwk->r_ptr = flyring;
      p_actwk->r_no = 2;
      flyring_patcnt = 255;
    }
    --p_actwk->pattim;
    if (util__to_signed(p_actwk->pattim) < 0) {
      p_actwk->pattim = 3;
      ++p_actwk->patno;
      p_actwk->patno &= 3;
    }
    unsigned short screen_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
    screen_xposi -= scr_x_no;
    if (screen_xposi <= 640) { // unsigned
      Add_Object_To_Collision_Response_List(p_actwk);
      actionsub(p_actwk);
    }
    else {
      if (p_actwk->actfree.ring.flagwork_index != 0) {
        CLEAR_BIT_7(flagwork[p_actwk->actfree.ring.flagwork_index - 1]);
      }
      if (p_actwk->actfree.ring.ringwk_index != 0) {
        ringwk[p_actwk->actfree.ring.ringwk_index - 1] = 0;
      }
      frameout(p_actwk);
    }
  }
  else {
    p_actwk->colino = 0;
    p_actwk->sprpri = PRI_1;
    --actring;
    ringgetsub(p_actwk);
    p_actwk->r_ptr = &tringdie;
    p_actwk->r_no = 0;
    tringdie(p_actwk);
  }
}


static void tringdie(sprite_status* p_actwk) {
  if (p_actwk->r_no == 0) {
    patchg(p_actwk, ringchg);
    actionsub(p_actwk);
  }
  else {
    tringerase(p_actwk);
  }
}


static void tringerase(sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void tringspdset(sprite_status* p_actwk) {
  short accel = 48;
  if (LONG_HIGH_TO_SHORT(actwk[0].xposi) < LONG_HIGH_TO_SHORT(p_actwk->xposi)) {
    accel = -accel;
    if (p_actwk->xspeed < 0) goto jump2;
    accel *= 3;
  }
  if (p_actwk->xspeed < 0) {
    accel *= 3;
  }
jump2:
  p_actwk->xspeed += accel;
  accel = 48;
  if (LONG_HIGH_TO_SHORT(actwk[0].yposi) < LONG_HIGH_TO_SHORT(p_actwk->yposi)) {
    accel = -accel;
    if (p_actwk->yspeed < 0) goto jump4;
    accel *= 3;
  }
  if (p_actwk->yspeed < 0) {
    accel *= 3;
  }
jump4:
  p_actwk->yspeed += accel;
  speedset2(p_actwk);
}


static signed char* ringchg[1] = {
  ringchg0
};


static signed char ringchg0[9] = { 5, 4, 5, 6, 7, -4, -121, -37, -112 };


signed char* ringpat[9] = {
  ringsp0,
  ringsp1,
  ringsp2,
  ringsp3,
  ringsp4,
  ringsp5,
  ringsp6,
  ringsp7,
  ringsp8
};


static signed char ringsp0[8] = { 0, 1, -8, 5, 0, 0, -8, -1 };
static signed char ringsp1[8] = { 0, 1, -8, 5, 4, 0, -8, -1 };
static signed char ringsp2[8] = { 0, 1, -8, 1, 8, 0, -4, -1 };
static signed char ringsp3[8] = { 0, 1, -8, 5, 4, 8, -8, -1 };
static signed char ringsp4[8] = { 0, 1, -8, 5, 10, 0, -8, -1 };
static signed char ringsp5[8] = { 0, 1, -8, 5, 10, 24, -8, -1 };
static signed char ringsp6[8] = { 0, 1, -8, 5, 10, 8, -8, -1 };
static signed char ringsp7[8] = { 0, 1, -8, 5, 10, 16, -8, -1 };
static signed char ringsp8[2] = { 0, 0 };


void slot_ring(sprite_status* p_actwk) {
  slot_ring_move_tbl[p_actwk->r_no / 2];
}


static sprite_status_handler slot_ring_move_tbl[3] = {
  &slot_ring_move,
  &slot_ring_get,
  &slot_ring_clr
};


static void slot_ring_move(sprite_status* p_actwk) {
  long xposi = p_actwk->actfree.slotring.xposi;
  xposi -= SHORT_TO_LONG_HIGH(p_actwk->actfree.slotring.xspeed);
  xposi /= 16;
  p_actwk->actfree.slotring.xposi -= xposi;
  util__copy_high(&p_actwk->xposi, &p_actwk->actfree.slotring.xposi);
  long yposi = p_actwk->actfree.slotring.yposi;
  yposi -= SHORT_TO_LONG_HIGH(p_actwk->actfree.slotring.yspeed);
  yposi /= 16;
  p_actwk->actfree.slotring.yposi -= yposi;
  util__copy_high(&p_actwk->yposi, &p_actwk->actfree.slotring.yposi);
  patchg(p_actwk, sringchg);
  --p_actwk->actfree.slotring.countdown;
  if (p_actwk->actfree.slotring.countdown != 0) {
    actionsub(p_actwk);
  }
  else {
    --p_actwk->actfree.slotring.unknown;
    ringgetsub(p_actwk);
    p_actwk->r_no += 2;
    slot_ring_get(p_actwk);
  }
}


static void slot_ring_get(sprite_status* p_actwk) {
  patchg(p_actwk, ringchg);
  actionsub(p_actwk);
}


static void slot_ring_clr(sprite_status* p_actwk) {
  frameout(p_actwk);
}


static signed char* sringchg[1] = {
  sringchg0
};


static signed char sringchg0[9] = { 1, 0, 1, 2, 3, -1, -121, -37, -112 };
