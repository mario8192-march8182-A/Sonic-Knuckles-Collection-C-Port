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
  SET_BIT_2(p_actwk->actflg);
  p_actwk->r_no += 2;
}


// skdisasm label: SetUp_ObjAttributes3
void enemy_init2(sprite_status* p_actwk, enemy_init2_data* p_data) {
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  SET_BIT_2(p_actwk->actflg);
  p_actwk->r_no += 2;
}


// skdisasm label: CreateChild1_Normal
sprite_status* set_act00(sprite_status* p_actwk, set_act00_data* p_data) {
  sprite_status* p_new_actwk;
  unsigned short i = 0;
  unsigned short cnt = p_data->cnt;
  ++cnt;

  do {
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk);
    if (!created) return 0;

    SPRITE_STATUS_USHORT(p_new_actwk, OYA_ADR) = actwk - p_actwk;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->r_ptr = p_data->data[i / 2].r_ptr;
    p_new_actwk->userflag1 = i;
    SPRITE_STATUS_SCHAR(p_new_actwk, 66) = p_data->data[i / 2].xoffset;
    p_new_actwk->xposi = LONG_HIGH(p_actwk->xposi) + LONG_LOW(p_new_actwk->xposi) + SHORT_TO_LONG_HIGH(p_data->data[i / 2].xoffset);
    SPRITE_STATUS_SCHAR(p_new_actwk, 67) = p_data->data[i / 2].yoffset;
    p_new_actwk->yposi = LONG_HIGH(p_actwk->yposi) + LONG_LOW(p_new_actwk->yposi) + SHORT_TO_LONG_HIGH(p_data->data[i / 2].yoffset);
    i += 2;
    --cnt;
  } while (cnt != 0);

  return p_new_actwk;
}


// skdisasm label: Refresh_ChildPosition
void ko_offset0(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &actwk[SPRITE_STATUS_USHORT(p_actwk, 70)];
  p_actwk->xposi = LONG_HIGH(p_parentwk->xposi) + SHORT_TO_LONG_HIGH(SPRITE_STATUS_SCHAR(p_actwk, 66)) + LONG_LOW(p_actwk->xposi);
  p_actwk->yposi = LONG_HIGH(p_parentwk->yposi) + SHORT_TO_LONG_HIGH(SPRITE_STATUS_SCHAR(p_actwk, 67)) + LONG_LOW(p_actwk->yposi);
}


// skdisasm label: Swing_UpAndDown
bool puka_puka(sprite_status* p_actwk) {
  bool axis_dir_changed = false;
  short accel = SPRITE_STATUS_SHORT(p_actwk, 64);
  short yspeed = p_actwk->yspeed;
  short accel_max = SPRITE_STATUS_SHORT(p_actwk, 62);
  if (!BIT_0_IS_SET(SPRITE_STATUS_UCHAR(p_actwk, 56))) {
    accel = -accel;
    yspeed += accel;
    accel_max = -accel_max;
    if (yspeed <= accel_max) { // signed
      SET_BIT_0(SPRITE_STATUS_UCHAR(p_actwk, 56));
      accel = -accel;
      accel_max = -accel_max;
      axis_dir_changed = true;
    }
  }
  else {
    yspeed += accel;
    if (yspeed >= accel_max) { // signed
      CLEAR_BIT_0(SPRITE_STATUS_UCHAR(p_actwk, 56));
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
      SPRITE_STATUS_PSCHAR(p_actwk, 48) = &p_pg_data[pg];
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[1];
      p_actwk->pattim = p_pg_data[0];
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      SPRITE_STATUS_PHANDLER(p_actwk, 52)(p_actwk);
      break;
  }
}


// skdisasm label: Set_Raw_Animation
void pg_init(sprite_status* p_actwk, signed char* p_pg_data) {
  SPRITE_STATUS_PSCHAR(p_actwk, 48) = p_pg_data;
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
      if (SPRITE_STATUS_UCHAR(p_playerwk, 47) == 0) return false;
      if (BIT_6_IS_SET(p_playerwk->cddat1)) return false;
      short xposi = LONG_HIGH_TO_SHORT(p_playerwk->xposi) - LONG_HIGH_TO_SHORT(p_actwk->xposi);
      short yposi = LONG_HIGH_TO_SHORT(p_playerwk->yposi) - LONG_HIGH_TO_SHORT(p_actwk->yposi);
      unsigned short angle = util__to_unsigned(atan(xposi, yposi) - 32);
      if (angle >= 64) return false; // unsigned
      return true;
    }
    case KNUCKLES:
      if (SPRITE_STATUS_UCHAR(p_playerwk, 47) == 1) return true;
      if (SPRITE_STATUS_UCHAR(p_playerwk, 47) == 3) return true;
      break;
  }

  return false;
}
