#include "globals.h"
#include "macros.h"
#include "004xxxxx.h"


// Address: 00410426
void Copy_Data_To_VRAM(unsigned short d1, unsigned short d2, unsigned short d3) {
  // TODO
}

// Address: 0041eb34
void actionsub(sprite_status* pActwk) {
  // TODO
}

// Address: 00422b67
void playdamageset(sprite_status* pPlayerwk, sprite_status* pAttackActwk) {
  short ring_cnt = plring;
  if (pPlayerwk != &actwk[0]) {
    if (vs_flag == 0) goto LAB_00422c37;
    ring_cnt = pl2ring;
  }
  if (BIT_0_IS_SET(pPlayerwk->cddat2)) goto LAB_00422c23;
  if (DAT_00831194 != 0) goto LAB_00422c23;
  if (((signed char*)pPlayerwk)[55] < 0) goto LAB_00422c37;
  if (ring_cnt == 0) goto LAB_00422d50;
  sprite_status* pNewActwk;
  bool created = Create_New_Sprite(&pNewActwk);
  if (!created) goto LAB_00422c23;
  pNewActwk->r_ptr = &flyring;
  pNewActwk->xposi = pPlayerwk->xposi;
  pNewActwk->yposi = pPlayerwk->yposi;
  ((unsigned short*)pNewActwk)[31] = pPlayerwk - actwk;
LAB_00422c23:
  pPlayerwk->cddat2 &= 0x8E;
LAB_00422c37:
  // TODO
}

// Address: 00422f11
void Add_Object_To_Collision_Response_List(sprite_status* pActwk) {
  if (colibuffer[0] >= 126) return; // unsigned
  colibuffer[0] += 2;
  colibuffer[colibuffer[0] / 2] = pActwk - actwk;
}

// Address: 0042b8b8
bool Create_New_Sprite(sprite_status** ppNewActwk) {
  *ppNewActwk = &actwk[3];
  return Create_New_Sprite_Int(ppNewActwk, 89);
}

// Address: 0042b8cf
bool Create_New_Sprite3(sprite_status* pActwk, sprite_status** ppNewActwk) {
  *ppNewActwk = pActwk;

  /* BUGFIX:
    The original code uses a lookup table to determine the value of the
    variable 'slot_cnt'. However, there's a bug in the generation of this
    table. As a result:
    - it thinks there are no eligible slots if pActwk is the first dynamic
      sprite
    - it considers the slot for the first reserved sprite an eligible slot
  */

  /* WHY:
    We decrement the result by one because we want to know how many slots
    there are between pActwk and &actwk[93]. We decrement it another time
    because 'slot_cnt' is zero-based.
  */

  short slot_cnt = (&actwk[93] - pActwk) - 1 - 1;
  if (slot_cnt < 0) return false;
  return Create_New_Sprite_Int(ppNewActwk, slot_cnt);
}

// Address: 0042b8ff
bool Create_New_Sprite_Int(sprite_status** ppNewActwk, short slot_cnt) {
  for ( ; slot_cnt != -1; --slot_cnt) {
    ++*ppNewActwk;
    if ((*ppNewActwk)->r_ptr == 0) return true;
  }

  return false;
}
