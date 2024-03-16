#include "globals.h"
#include "macros.h"
#include "091.h"


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
