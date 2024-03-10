#include "globals.h"
#include "constants.h"
#include "091.h"


bool chk_pl_attack(sprite_status* pActwk, sprite_status* pPlayerwk) {
  if (pPlayerwk->cddat2 & 2) return false;
  if (pPlayerwk->mstno == 9) return false;
  if (pPlayerwk->mstno == 2) return false;
  character_id character = ((unsigned char*)pPlayerwk)[56];

  switch (character) {
    case SONIC:
      return true;
    case MILES:
      if (((unsigned char*)pPlayerwk)[47] == 0) return true;
      pPlayerwk->cddat1 & 64;
      if (((unsigned char*)pPlayerwk)[47] != 0) return true;
      // d1 = pPlayerwk->xposi - pActwk->xposi;
      // d2 = pPlayerwk->yposi - pActwk->yposi;
      // d0 = FUN_00411511(d1, d2);
      // d0 -= 32;
      // if (d0 > 64) return true; // unsigned
      // break;
    case KNUCKLES:
      if (((unsigned char*)pPlayerwk)[47] == 1) return false;
      if (((unsigned char*)pPlayerwk)[47] == 3) return false;
      return true;
  }

  return false;
}
