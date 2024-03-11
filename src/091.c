#include "globals.h"
#include "constants.h"
#include "macros.h"
#include "091.h"


// skdisasm label: Check_PlayerAttack
bool chk_pl_attack(sprite_status* pActwk, sprite_status* pPlayerwk) {
  if (BIT_1_IS_SET(pPlayerwk->cddat2)) return true;
  if (pPlayerwk->mstno == 9) return true;
  if (pPlayerwk->mstno == 2) return true;
  character_id character = ((unsigned char*)pPlayerwk)[56];

  switch (character) {
    case SONIC:
      break;
    case MILES: {
      if (((unsigned char*)pPlayerwk)[47] == 0) return false;
      if (BIT_6_IS_SET(pPlayerwk->cddat1)) return false;
      short xposi = pPlayerwk->xposi - pActwk->xposi;
      short yposi = pPlayerwk->yposi - pActwk->yposi;
      unsigned short d0 = FUN_00411511(xposi, yposi) - 32;
      if (d0 >= 64) return false; // unsigned
      return true;
    }
    case KNUCKLES:
      if (((unsigned char*)pPlayerwk)[47] == 1) return true;
      if (((unsigned char*)pPlayerwk)[47] == 3) return true;
      break;
  }

  return false;
}
