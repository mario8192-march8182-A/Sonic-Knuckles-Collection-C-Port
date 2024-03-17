#include "globals.h"
#include "macros.h"
#include "091.h"
#include "004xxxxx.h"
static void chk_pt_next(sprite_status* pActwk, signed char pg, signed char* pPgData, unsigned char patcnt);


// skdisasm label: SetUp_ObjAttributes
void enemy_init0(sprite_status* pActwk, enemy_init0_data* pData) {
  pActwk->patbase = pData->patbase;
  pActwk->sproffset = pData->sproffset;
  pActwk->sprpri = pData->sprpri;
  pActwk->sprhs = pData->sprhs;
  pActwk->sprvs = pData->sprvs;
  pActwk->patno = pData->patno;
  pActwk->colino = pData->colino;
  SET_BIT_2(pActwk->actflg);
  pActwk->r_no += 2;
}


// skdisasm label: SetUp_ObjAttributes3
void enemy_init2(sprite_status* pActwk, enemy_init2_data* pData) {
  pActwk->sprpri = pData->sprpri;
  pActwk->sprhs = pData->sprhs;
  pActwk->sprvs = pData->sprvs;
  pActwk->patno = pData->patno;
  pActwk->colino = pData->colino;
  SET_BIT_2(pActwk->actflg);
  pActwk->r_no += 2;
}


// skdisasm label: CreateChild1_Normal
void set_act00(sprite_status* pActwk, set_act00_data* pData) {
  sprite_status* pNewActwk;
  unsigned short i = 0;
  unsigned short cnt = pData->cnt;
  ++cnt;

  do {
    bool created = Create_New_Sprite3(pActwk, &pNewActwk);
    if (!created) return;

    SPRITE_STATUS_USHORT(pNewActwk, OYA_ADR) = actwk - pActwk;
    pNewActwk->patbase = pActwk->patbase;
    pNewActwk->sproffset = pActwk->sproffset;
    pNewActwk->r_ptr = pData->data[i / 2].r_ptr;
    pNewActwk->userflag1 = i;
    SPRITE_STATUS_SCHAR(pNewActwk, 66) = pData->data[i / 2].xoffset;
    pNewActwk->xposi = LONG_HIGH(pActwk->xposi) + LONG_LOW(pNewActwk->xposi) + SHORT_TO_LONG_HIGH(pData->data[i / 2].xoffset);
    SPRITE_STATUS_SCHAR(pNewActwk, 67) = pData->data[i / 2].yoffset;
    pNewActwk->yposi = LONG_HIGH(pActwk->yposi) + LONG_LOW(pNewActwk->yposi) + SHORT_TO_LONG_HIGH(pData->data[i / 2].yoffset);
    i += 2;
    --cnt;
  } while (cnt != 0);
}


// skdisasm label: Swing_UpAndDown
bool puka_puka(sprite_status* pActwk) {
  bool axis_dir_changed = false;
  short accel = SPRITE_STATUS_SHORT(pActwk, 64);
  short yspeed = pActwk->yspeed;
  short accel_max = SPRITE_STATUS_SHORT(pActwk, 62);
  if (!BIT_0_IS_SET(SPRITE_STATUS_UCHAR(pActwk, 56))) {
    accel = -accel;
    yspeed += accel;
    accel_max = -accel_max;
    if (yspeed <= accel_max) { // signed
      SET_BIT_0(SPRITE_STATUS_UCHAR(pActwk, 56));
      accel = -accel;
      accel_max = -accel_max;
      axis_dir_changed = true;
    }
  }
  else {
    yspeed += accel;
    if (yspeed >= accel_max) { // signed
      CLEAR_BIT_0(SPRITE_STATUS_UCHAR(pActwk, 56));
      accel = -accel;
      yspeed += accel;
      axis_dir_changed = true;
    }
  }
  pActwk->yspeed = yspeed;
  // d1 = yspeed;
  // d3 = axis_dir_changed;
  return axis_dir_changed;
}


// skdisasm label: Animate_RawNoSSTCheckResult (?)
void pt_chg0(sprite_status* pActwk, signed char* pPgData) {
  --pActwk->pattim;
  ++pActwk->patcnt;
  signed char pg = pPgData[pActwk->patcnt + 1];
  if (pg < 0) {
    chk_pt_next(pActwk, pg, pPgData, pActwk->patcnt);
  }
  else {
    pActwk->pattim = pPgData[0];
    pActwk->patno = pg;
  }
}


static void chk_pt_next(sprite_status* pActwk, signed char pg, signed char* pPgData, unsigned char patcnt) {
  pg = -pg;

  switch (pg) {
    case PG_CONTROL_NEXT:
      pg = pPgData[patcnt + 2];
      SPRITE_STATUS_PSCHAR(pActwk, 48) = &pPgData[pg];
    case PG_CONTROL_LOOP:
      pActwk->patno = pPgData[1];
      pActwk->pattim = pPgData[0];
      break;
    case PG_CONTROL_END:
      pActwk->pattim = 0;
      SPRITE_STATUS_PHANDLER(pActwk, 52)(pActwk);
      break;
  }
}


// skdisasm label: Set_Raw_Animation
void pg_init(sprite_status* pActwk, signed char* pPgData) {
  SPRITE_STATUS_PSCHAR(pActwk, 48) = pPgData;
  pActwk->patcnt = pActwk->pattim = 0;
}


// skdisasm label: Check_PlayerAttack
bool chk_pl_attack(sprite_status* pActwk, sprite_status* pPlayerwk) {
  if (BIT_1_IS_SET(pPlayerwk->cddat2)) return true;
  if (pPlayerwk->mstno == 9) return true;
  if (pPlayerwk->mstno == 2) return true;
  character_id character = SPRITE_STATUS_UCHAR(pPlayerwk, 56);

  switch (character) {
    case SONIC:
      break;
    case MILES: {
      if (SPRITE_STATUS_UCHAR(pPlayerwk, 47) == 0) return false;
      if (BIT_6_IS_SET(pPlayerwk->cddat1)) return false;
      short xposi = LONG_HIGH_TO_SHORT(pPlayerwk->xposi) - LONG_HIGH_TO_SHORT(pActwk->xposi);
      short yposi = LONG_HIGH_TO_SHORT(pPlayerwk->yposi) - LONG_HIGH_TO_SHORT(pActwk->yposi);
      unsigned short d0 = FUN_00411511(xposi, yposi) - 32;
      if (d0 >= 64) return false; // unsigned
      return true;
    }
    case KNUCKLES:
      if (SPRITE_STATUS_UCHAR(pPlayerwk, 47) == 1) return true;
      if (SPRITE_STATUS_UCHAR(pPlayerwk, 47) == 3) return true;
      break;
  }

  return false;
}
