#include <string.h>
#include "globals.h"
#include "macros.h"
#include "004xxxxx.h"


// SONIC3K.EXE address: 0040a98e
void PlaySoundRegister(long id) {
  // TODO
}

// SONIC3K.EXE address: 00410426
// skdisasm label: Add_To_DMA_Queue
void Copy_Data_To_VRAM(unsigned short d1, unsigned short d2, unsigned short d3) {
  // TODO
}

// SONIC3K.EXE address: 0041a82d
// skdisasm label: Play_SFX
void soundset(long id) {
  PlaySoundRegister(id);
}

// SONIC3K.EXE addresses: 0041eacf, 0041ead9
// skdisasm labels: Delete_Current_Sprite, Delete_Referenced_Sprite
void frameout(sprite_status* pActwk) {
  memset(pActwk, 0, sizeof(*pActwk));
}

// SONIC3K.EXE address: 0041eb34
// skdisasm label: Draw_Sprite
void actionsub(sprite_status* pActwk) {
  unsigned char level_no = pActwk->sprpri / (PBUFFER_LEVEL_SLOTS * PBUFFER_LEVEL_SLOT_SIZE);
  unsigned short* pri_level = &pbuffer[level_no][0];

  do {
    if (pri_level[0] < PBUFFER_LEVEL_MAX_SIZE) { // unsigned
      pri_level[0] += PBUFFER_LEVEL_SLOT_SIZE;
      pri_level[pri_level[0] / PBUFFER_LEVEL_SLOT_SIZE] = pActwk - actwk;
      return;
    }
    if (pri_level == &pbuffer[PBUFFER_LEVELS - 1][0]) return;
    pri_level += PBUFFER_LEVEL_SLOTS;
  } while (1);
}

// SONIC3K.EXE address: 00422b67
// skdisasm label: HurtCharacter
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

// SONIC3K.EXE address: 00422f11
// skdisasm label: Add_SpriteToCollisionResponseList
void Add_Object_To_Collision_Response_List(sprite_status* pActwk) {
  if (colibuffer[0] >= COLBUFFER_MAX_SIZE) return; // unsigned
  colibuffer[0] += COLBUFFER_SLOT_SIZE;
  colibuffer[colibuffer[0] / COLBUFFER_SLOT_SIZE] = pActwk - actwk;
}

// SONIC3K.EXE address: 0042b8b8
// skdisasm label: Create_New_Sprite
bool Create_New_Sprite(sprite_status** ppNewActwk) {
  *ppNewActwk = &actwk[ACTWK_DYNAMIC_START];
  return Create_New_Sprite_Int(ppNewActwk, ACTWK_RESERVED_START - ACTWK_DYNAMIC_START - 1);
}

// SONIC3K.EXE address: 0042b8cf
// skdisasm label: Create_New_Sprite3
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

  short slot_cnt = (&actwk[ACTWK_RESERVED_START] - pActwk) - 1 - 1;
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
