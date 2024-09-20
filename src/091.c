#include "globals.h"
#include "macros.h"
#include "util.h"
#include "091.h"
#include "004xxxxx.h"
static void chk_pt_next(sprite_status* p_actwk, signed char pg, signed char* p_pg_data, unsigned char patcnt);


// skdisasm label: SetUp_ObjAttributes
void enemy_init0(sprite_status* p_actwk, enemy_init0_data* p_data) {
  p_actwk->patbase = p_data->patbase;
  p_actwk->sproffset = p_data->sproffset;
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  SET_BIT(p_actwk->actflg, FLG_LEVELCOORDS);
  p_actwk->r_no += 2;
}


// skdisasm label: SetUp_ObjAttributes2
void enemy_init1(sprite_status* p_actwk, enemy_init1_data* p_data) {
  p_actwk->sproffset = p_data->sproffset;
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  SET_BIT(p_actwk->actflg, FLG_LEVELCOORDS);
  p_actwk->r_no += 2;
}

// skdisasm label: SetUp_ObjAttributes3
void enemy_init2(sprite_status* p_actwk, enemy_init2_data* p_data) {
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  SET_BIT(p_actwk->actflg, FLG_LEVELCOORDS);
  p_actwk->r_no += 2;
}


// skdisasm label: CreateChild1_Normal
sprite_status* set_act00(sprite_status* p_actwk, set_act00_data* p_data) {
  sprite_status* p_new_actwk;
  unsigned short i = 0;
  unsigned short cnt = p_data->cnt;
  ++cnt;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) return 0;

    p_new_actwk->actfree.dynamic.oya = p_actwk - g_mdRam.actwk;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->r_ptr = p_data->data[i / 2].r_ptr;
    p_new_actwk->userflag1 = i;
    signed char xoffset = p_data->data[i / 2].xoffset;
    p_new_actwk->actfree.dynamic.xoffset = xoffset;
    short xposi = LONG_HIGH(p_actwk->xposi) + xoffset;
    util__assign_high(&p_new_actwk->xposi, xposi);
    signed char yoffset = p_data->data[i / 2].yoffset;
    p_new_actwk->actfree.dynamic.yoffset = yoffset;
    short yposi = LONG_HIGH(p_actwk->yposi) + yoffset;
    util__assign_high(&p_new_actwk->yposi, yposi);
    i += 2;
    --cnt;
  } while (cnt != 0);

  return p_new_actwk;
}


// skdisasm label: CreateChild2_Complex
sprite_status* set_act01(sprite_status* p_actwk, set_act01_data* p_data) {
  sprite_status* p_new_actwk;
  unsigned short i = 0;
  unsigned short cnt = p_data->cnt;
  ++cnt;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) return 0;

    p_new_actwk->actfree.dynamic.oya = p_actwk - g_mdRam.actwk;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->r_ptr = p_data->data[i / 2].r_ptr;
    p_new_actwk->actfree.enemy_uninit_0.init_data_ptr = p_data->data[i / 2].enemy_init0_data_ptr;
    p_new_actwk->actfree.dynamic.pg_data_ptr = p_data->data[i / 2].pg_data_ptr;
    p_new_actwk->actfree.dynamic.callback_ptr = p_data->data[i / 2].callback_ptr;
    p_new_actwk->userflag1 = i;
    signed char xoffset = p_data->data[i / 2].xoffset;
    p_new_actwk->actfree.dynamic.xoffset = xoffset;
    short xposi = LONG_HIGH(p_actwk->xposi) + xoffset;
    util__assign_high(&p_new_actwk->xposi, xposi);
    signed char yoffset = p_data->data[i / 2].yoffset;
    p_new_actwk->actfree.dynamic.yoffset = yoffset;
    short yposi = LONG_HIGH(p_actwk->yposi) + yoffset;
    util__assign_high(&p_new_actwk->yposi, yposi);
    p_new_actwk->xspeed = p_data->data[i / 2].xspeed;
    p_new_actwk->yspeed = p_data->data[i / 2].yspeed;
    i += 2;
    --cnt;
  } while (cnt != 0);

  return p_new_actwk;
}


// skdisasm: CreateChild3_NormalRepeated
sprite_status* set_act02(sprite_status* p_actwk, set_act02_data* p_data) {
  sprite_status* p_new_actwk;
  unsigned short i = 0;
  unsigned short cnt = p_data->cnt;
  ++cnt;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) return 0;

    p_new_actwk->actfree.dynamic.oya = p_actwk - g_mdRam.actwk;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->r_ptr = p_data->r_ptr;
    p_new_actwk->userflag1 = i;
    p_new_actwk->actfree.dynamic.xoffset = p_data->xoffset;
    short xposi = LONG_HIGH(p_actwk->xposi) + p_data->xoffset;
    util__assign_high(&p_new_actwk->xposi, xposi);
    p_new_actwk->actfree.dynamic.yoffset = p_data->yoffset;
    short yposi = LONG_HIGH(p_actwk->yposi) + p_data->yoffset;
    util__assign_high(&p_new_actwk->yposi, yposi);
    i += 2;
    --cnt;
  } while (cnt != 0);

  return p_new_actwk;
}


// skdisasm: CreateChild4_LinkListRepeated
sprite_status* set_act03(sprite_status* p_actwk, set_act03_data* p_data) {
  sprite_status* p_new_actwk;
  sprite_status* p_prev_actwk = p_actwk;
  unsigned short i = 0;
  unsigned short cnt = p_data->cnt;
  ++cnt;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) return 0;

    p_new_actwk->actfree.dynamic.oya = p_prev_actwk - g_mdRam.actwk;
    p_prev_actwk->actfree.dynamic.ko = p_new_actwk - g_mdRam.actwk;
    p_prev_actwk = p_new_actwk;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->r_ptr = p_data->r_ptr;
    p_new_actwk->userflag1 = i;
    util__copy_high(&p_new_actwk->xposi, &p_actwk->xposi);
    util__copy_high(&p_new_actwk->yposi, &p_actwk->yposi);
    i += 2;
    --cnt;
  } while (cnt != 0);

  return p_new_actwk;
}


// skdisasm label: Refresh_ChildPosition
void ko_offset0(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &g_mdRam.actwk[p_actwk->actfree.dynamic.oya];
  short xposi = LONG_HIGH(p_parentwk->xposi) + p_actwk->actfree.dynamic.xoffset;
  util__assign_high(&p_actwk->xposi, xposi);
  short yposi = LONG_HIGH(p_parentwk->yposi) + p_actwk->actfree.dynamic.yoffset;
  util__assign_high(&p_actwk->yposi, yposi);
}


// skdisasm label: Refresh_ChildPositionAdjusted
void ko_offset1(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &g_mdRam.actwk[p_actwk->actfree.dynamic.oya];
  signed char xoffset = p_actwk->actfree.dynamic.xoffset;
  CLEAR_BIT(p_actwk->actflg, FLG_HFLIP);
  if (BIT_IS_SET(p_parentwk->actflg, FLG_HFLIP)) {
    xoffset = -xoffset;
    SET_BIT(p_parentwk->actflg, FLG_HFLIP);
  }
  short xposi = LONG_HIGH(p_parentwk->xposi) + xoffset;
  util__assign_high(&p_actwk->xposi, xposi);
  signed char yoffset = p_actwk->actfree.dynamic.yoffset;
  CLEAR_BIT(p_actwk->actflg, FLG_VFLIP);
  if (BIT_IS_SET(p_parentwk->actflg, FLG_VFLIP)) {
    yoffset = -yoffset;
    SET_BIT(p_parentwk->actflg, FLG_VFLIP);
  }
  short yposi = LONG_HIGH(p_parentwk->yposi) + yoffset;
  util__assign_high(&p_actwk->yposi, yposi);
}


// skdisasm label: Swing_UpAndDown
bool puka_puka(sprite_status* p_actwk) {
  bool axis_dir_changed = false;
  short accel = p_actwk->actfree.dynamic.accel;
  short yspeed = p_actwk->yspeed;
  short accel_max = p_actwk->actfree.dynamic.accel_max;
  if (!BIT_0_IS_SET(p_actwk->actfree.dynamic.status_bitfield)) {
    accel = -accel;
    yspeed += accel;
    accel_max = -accel_max;
    if (yspeed <= accel_max) { // signed
      SET_BIT_0(p_actwk->actfree.dynamic.status_bitfield);
      accel = -accel;
      accel_max = -accel_max;
      axis_dir_changed = true;
    }
  }
  else {
    yspeed += accel;
    if (yspeed >= accel_max) { // signed
      CLEAR_BIT_0(p_actwk->actfree.dynamic.status_bitfield);
      accel = -accel;
      yspeed += accel;
      axis_dir_changed = true;
    }
  }
  p_actwk->yspeed = yspeed;
  // d1 = yspeed;
  // d3 = axis_dir_changed;
  return axis_dir_changed;
}


// skdisasm label: Animate_Raw
void pt_chg(sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (util__to_signed(p_actwk->pattim) < 0) {
    ++p_actwk->patcnt;
    signed char pg = p_actwk->actfree.dynamic.pg_data_ptr[p_actwk->patcnt + 1];
    if (pg < 0) {
      chk_pt_next(p_actwk, pg, p_actwk->actfree.dynamic.pg_data_ptr, p_actwk->patcnt);
    }
    else {
      p_actwk->pattim = p_actwk->actfree.dynamic.pg_data_ptr[0];
      p_actwk->patno = pg;
    }
  }
}


// skdisasm label: Animate_RawNoSSTCheckResult (?)
void pt_chg0(sprite_status* p_actwk, signed char* p_pg_data) {
  --p_actwk->pattim;
  ++p_actwk->patcnt;
  signed char pg = p_pg_data[p_actwk->patcnt + 1];
  if (pg < 0) {
    chk_pt_next(p_actwk, pg, p_pg_data, p_actwk->patcnt);
  }
  else {
    p_actwk->pattim = p_pg_data[0];
    p_actwk->patno = pg;
  }
}


static void chk_pt_next(sprite_status* p_actwk, signed char pg, signed char* p_pg_data, unsigned char patcnt) {
  pg = -pg;

  switch (pg) {
    case PG_CONTROL_NEXT:
      pg = p_pg_data[patcnt + 2];
      p_actwk->actfree.dynamic.pg_data_ptr = &p_pg_data[pg];
      // fall-through
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[1];
      p_actwk->pattim = p_pg_data[0];
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      p_actwk->actfree.dynamic.callback_ptr(p_actwk);
      break;
  }
}


// skdisasm label: Set_Raw_Animation
void pg_init(sprite_status* p_actwk, signed char* p_pg_data) {
  p_actwk->actfree.dynamic.pg_data_ptr = p_pg_data;
  p_actwk->patcnt = p_actwk->pattim = 0;
}


// skdisasm label: Check_PlayerAttack
bool chk_pl_attack(sprite_status* p_actwk, sprite_status* p_playerwk) {
  if (BIT_1_IS_SET(p_playerwk->cddat2)) return true;
  if (p_playerwk->mstno == 9) return true;
  if (p_playerwk->mstno == 2) return true;

  switch (p_playerwk->actfree.player.character) {
    case SONIC:
      break;
    case MILES: {
      if (p_playerwk->actfree.player.talent_status == 0) return false;
      if (BIT_IS_SET(p_playerwk->cddat1, CD_UNDERWATER)) return false;
      short xposi = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi);
      short yposi = LONG_HIGH(p_playerwk->yposi) - LONG_HIGH(p_actwk->yposi);
      unsigned short angle = util__to_unsigned(atan(xposi, yposi) - 32);
      if (angle >= 64) return false; // unsigned
      return true;
    }
    case KNUCKLES:
      if (p_playerwk->actfree.player.talent_status == 1) return true;
      if (p_playerwk->actfree.player.talent_status == 3) return true;
      break;
  }

  return false;
}
