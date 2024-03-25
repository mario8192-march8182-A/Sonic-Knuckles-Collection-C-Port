#include <string.h>
#include "globals.h"
#include "macros.h"
#include "util.h"
#include "004xxxxx.h"
#include "ring.h"


// SONIC3K.EXE address: 0040a98e
void PlaySoundRegister(long id) {
  // TODO
}


// SONIC3K.EXE address: 00410426
// skdisasm label: Add_To_DMA_Queue
void Copy_Data_To_VRAM(unsigned char* source, unsigned short destination, unsigned short words) {
  // TODO
}


// SONIC3K.EXE address: 0041149c
// skdisasm label: Load_PLC_Raw
void Load_PLC_Raw(sprite_status* p_actwk, cg_data* p_data) {
  // TODO
}


// SONIC3K.EXE address: 004114aa
// skdisasm label: Queue_Kos_Module
void Queue_Kos_Module(void* p_data, unsigned short act_id) {
  // TODO
}


// SONIC3K.EXE address: 0041a490
// skdisasm label: LoadEnemyArt
void LoadEnemyArt() {
  // TODO
}


// SONIC3K.EXE address: 0041a81b
// skdisasm label: Play_Music
void bgmset(long id) {
  // TODO
}


// SONIC3K.EXE address: 0041a82d
// skdisasm label: Play_SFX
void soundset(long id) {
  PlaySoundRegister(id);
}


// SONIC3K.EXE address: 0041e8f6
// skdisasm label: MoveSprite2
void speedset2(sprite_status* p_actwk) {
  p_actwk->xposi += p_actwk->xspeed * 256;
  p_actwk->yposi += p_actwk->yspeed * 256;
}


// SONIC3K.EXE address: 0041ea30
// skdisasm label: MoveSprite_TestGravity2
void speedset2g(sprite_status* p_actwk) {
  if (reverse_gravity_flag == 0) {
    speedset2(p_actwk);
  }
  else {
    p_actwk->xposi += p_actwk->xspeed * 256;
    p_actwk->yposi += -p_actwk->yspeed * 256;
  }
}


// SONIC3K.EXE addresses: 0041eacf, 0041ead9
// skdisasm labels: Delete_Current_Sprite, Delete_Referenced_Sprite
void frameout(sprite_status* p_actwk) {
  memset(p_actwk, 0, sizeof(*p_actwk));
}


// SONIC3K.EXE address: 0041eb34
// skdisasm label: Draw_Sprite
void actionsub(sprite_status* p_actwk) {
  unsigned char level_no = p_actwk->sprpri / (PBUFFER_LEVEL_SLOTS * PBUFFER_LEVEL_SLOT_SIZE);
  unsigned short* pri_level = &pbuffer[level_no][0];

  do {
    if (pri_level[0] < PBUFFER_LEVEL_MAX_SIZE) { // unsigned
      pri_level[0] += PBUFFER_LEVEL_SLOT_SIZE;
      pri_level[pri_level[0] / PBUFFER_LEVEL_SLOT_SIZE] = p_actwk - actwk;
      return;
    }
    if (pri_level == &pbuffer[PBUFFER_LEVELS - 1][0]) return;
    pri_level += PBUFFER_LEVEL_SLOTS;
  } while (1);
}


// SONIC3K.EXE address: 0041ebc7
// skdisasm label: Animate_Sprite
void patchg(sprite_status* p_actwk, signed char** p_chg_data) {
  if (p_actwk->mstno != p_actwk->restart) {
    p_actwk->restart = p_actwk->mstno;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
  }
  --p_actwk->pattim;
  if (p_actwk->pattim > 0) return;
  signed char* p_sp_data = p_chg_data[p_actwk->mstno];
  p_actwk->pattim = p_sp_data[0];
  signed char sp = p_sp_data[p_actwk->patcnt + 1];
  if (sp < 0) {
    switch (sp) {
      case PS_CONTROL_LOOP:
        p_actwk->patcnt = 0;
        sp = p_sp_data[1];
        break;
      case PS_CONTROL_REWIND:
        sp = p_sp_data[p_actwk->patcnt + 2];
        p_actwk->patcnt -= sp;
        sp = p_sp_data[p_actwk->patcnt - sp + 1];
        break;
      case PS_CONTROL_NEXT:
        p_actwk->mstno = p_sp_data[p_actwk->patcnt + 2];
        return;
      case PS_CONTROL_ROUTINE:
        p_actwk->r_no += 2;
        p_actwk->pattim = 0;
        ++p_actwk->patcnt;
        return;
      case PS_CONTROL_FOUT:
        p_actwk->xposi = SHORT_TO_LONG_HIGH(32512) + LONG_LOW(p_actwk->xposi);
        return;
      default:
        return;
    }
  }
  p_actwk->patno = sp;
  p_actwk->actflg &= 0xFC;
  p_actwk->actflg |= p_actwk->cddat1 & 3;
  ++p_actwk->patcnt;
}


// SONIC3K.EXE address: 00421b44
// skdisasm label: Sprite_OnScreen_Test
void frameoutchk(sprite_status* p_actwk) {
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= scr_x_no;
  if (scr_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    if (SPRITE_STATUS_USHORT(p_actwk, 72) != 0) {
      CLEAR_BIT_7(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1]);
    }
    frameout(p_actwk);
  }
}


// SONIC3K.EXE address: 00421e38
// skdisasm label: Sprite_CheckDeleteTouch3
void frameoutchkc(sprite_status* p_actwk, short xposi) {
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= scr_x_no;
  if (scr_xposi <= 640) {
    Add_Object_To_Collision_Response_List(p_actwk);
    actionsub(p_actwk);
  }
  else {
    if (SPRITE_STATUS_USHORT(p_actwk, 72) != 0) {
      CLEAR_BIT_7(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1]);
    }
    frameout(p_actwk);
  }
}


// SONIC3K.EXE address: 00422b67
// skdisasm label: HurtCharacter
void playdamageset(sprite_status* p_playerwk, sprite_status* p_attack_actwk) {
  short ring_cnt = plring;
  if (p_playerwk != &actwk[0]) {
    if (vs_flag == 0) goto LAB_00422c37;
    ring_cnt = pl2ring;
  }
  if (BIT_0_IS_SET(p_playerwk->cddat2)) goto LAB_00422c23;
  if (DAT_00831194 != 0) goto LAB_00422c23;
  if (SPRITE_STATUS_SCHAR(p_playerwk, 55) < 0) goto LAB_00422c37;
  if (ring_cnt == 0) goto LAB_00422d50;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite(&p_new_actwk);
  if (!created) goto LAB_00422c23;
  p_new_actwk->r_ptr = &flyring;
  p_new_actwk->xposi = LONG_HIGH(p_playerwk->xposi) + LONG_LOW(p_new_actwk->xposi);
  p_new_actwk->yposi = LONG_HIGH(p_playerwk->yposi) + LONG_LOW(p_new_actwk->yposi);
  SPRITE_STATUS_USHORT(p_new_actwk, 62) = p_playerwk - actwk;
LAB_00422c23:
  p_playerwk->cddat2 &= 0x8E;
LAB_00422c37:
  // TODO
}


// SONIC3K.EXE address: 00422f11
// skdisasm label: Add_SpriteToCollisionResponseList
void Add_Object_To_Collision_Response_List(sprite_status* p_actwk) {
  if (colibuffer[0] >= COLBUFFER_MAX_SIZE) return; // unsigned
  colibuffer[0] += COLBUFFER_SLOT_SIZE;
  colibuffer[colibuffer[0] / COLBUFFER_SLOT_SIZE] = p_actwk - actwk;
}


// SONIC3K.EXE address: 00426f24
// skdisasm label: Random_Number
unsigned long random() {
  unsigned long d1 = ranum;
  if (d1 == 0) {
    d1 = 711800411;
  }
  unsigned long d0 = d1;
  d1 = d1 << 2 & 0xFFFFFFFF;
  d1 = d1 + d0 & 0xFFFFFFFF;
  d1 = d1 << 3 & 0xFFFFFFFF;
  d1 = d1 + d0 & 0xFFFFFFFF;
  d0 = d0 & 0xFFFF0000 | d1 & 0x0000FFFF;
  d1 = util__rotate(d1);
  d0 = d0 & 0xFFFF0000 | ((d0 & 0x0000FFFF) + (d1 & 0x0000FFFF) & 0x0000FFFF);
  d1 = d1 & 0xFFFF0000 | d0 & 0x0000FFFF;
  d1 = util__rotate(d1);
  ranum = d1;
  return d0;
}


short sintable[320] = {
     0,    6,   12,   18,   25,   31,   37,   43,   49,   56,   62,   68,   74,   80,   86,   92,
    97,  103,  109,  115,  120,  126,  131,  136,  142,  147,  152,  157,  162,  167,  171,  176,
   181,  185,  189,  193,  197,  201,  205,  209,  212,  216,  219,  222,  225,  228,  231,  234,
   236,  238,  241,  243,  244,  246,  248,  249,  251,  252,  253,  254,  254,  255,  255,  255,
   256,  255,  255,  255,  254,  254,  253,  252,  251,  249,  248,  246,  244,  243,  241,  238,
   236,  234,  231,  228,  225,  222,  219,  216,  212,  209,  205,  201,  197,  193,  189,  185,
   181,  176,  171,  167,  162,  157,  152,  147,  142,  136,  131,  126,  120,  115,  109,  103,
    97,   92,   86,   80,   74,   68,   62,   56,   49,   43,   37,   31,   25,   18,   12,    6,
     0,   -6,  -12,  -18,  -25,  -31,  -37,  -43,  -49,  -56,  -62,  -68,  -74,  -80,  -86,  -92,
   -97, -103, -109, -117, -120, -126, -131, -136, -142, -147, -152, -157, -162, -167, -171, -176,
  -181, -185, -189, -193, -197, -201, -205, -209, -212, -216, -219, -222, -225, -228, -231, -234,
  -236, -238, -241, -243, -244, -246, -248, -249, -251, -252, -253, -254, -254, -255, -255, -255,
  -256, -255, -255, -255, -254, -254, -253, -252, -251, -249, -248, -246, -244, -243, -241, -238,
  -236, -234, -231, -228, -225, -222, -219, -216, -212, -209, -205, -201, -197, -193, -189, -185,
  -181, -176, -171, -167, -162, -157, -152, -147, -142, -136, -131, -126, -120, -117, -109, -103,
   -97,  -92,  -86,  -80,  -74,  -68,  -62,  -56,  -49,  -43,  -37,  -31,  -25,  -18,  -12,   -6,
     0,    6,   12,   18,   25,   31,   37,   43,   49,   56,   62,   68,   74,   80,   86,   92,
    97,  103,  109,  115,  120,  126,  131,  136,  142,  147,  152,  157,  162,  167,  171,  176,
   181,  185,  189,  193,  197,  201,  205,  209,  212,  216,  219,  222,  225,  228,  231,  234,
   236,  238,  241,  243,  244,  246,  248,  249,  251,  252,  253,  254,  254,  255,  255,  255
};


// SONIC3K.EXE address: 00426fde
// skdisasm label: GetSineCosine
void sinset(unsigned char angle, short* sin, short* cos) {
  unsigned short angle_w = angle * 2;
  angle_w += 128;
  *cos = sintable[angle_w];
  angle_w -= 128;
  *sin = sintable[angle_w];
}


// SONIC3K.EXE address: 0042b8b8
// skdisasm label: Create_New_Sprite
bool Create_New_Sprite(sprite_status** pp_new_actwk) {
  *pp_new_actwk = &actwk[ACTWK_DYNAMIC_START];
  return Create_New_Sprite_Int(pp_new_actwk, ACTWK_RESERVED_START - ACTWK_DYNAMIC_START - 1);
}


// SONIC3K.EXE address: 0042b8cf
// skdisasm label: Create_New_Sprite3
bool Create_New_Sprite3(sprite_status* p_actwk, sprite_status** pp_new_actwk) {
  *pp_new_actwk = p_actwk;

  /* BUGFIX:
    The original code uses a lookup table to determine the value of the
    variable 'slot_cnt'. However, there's a bug in the generation of this
    table. As a result:
    - it thinks there are no eligible slots if p_actwk is the first dynamic
      sprite
    - it considers the slot for the first reserved sprite an eligible slot
  */

  /* WHY:
    We decrement the result by one because we want to know how many slots
    there are between p_actwk and &actwk[93]. We decrement it another time
    because 'slot_cnt' is zero-based.
  */

  short slot_cnt = (&actwk[ACTWK_RESERVED_START] - p_actwk) - 1 - 1;
  if (slot_cnt < 0) return false;
  return Create_New_Sprite_Int(pp_new_actwk, slot_cnt);
}


// Address: 0042b8ff
bool Create_New_Sprite_Int(sprite_status** pp_new_actwk, short slot_cnt) {
  for ( ; slot_cnt != -1; --slot_cnt) {
    ++*pp_new_actwk;
    if ((*pp_new_actwk)->r_ptr == 0) return true;
  }

  return false;
}


// SONIC3K.EXE address: 0042b998
// skdisasm label: Clear_SpriteRingMem
void Clear_SpriteRingMem() {
  sprite_status* p_actwk = &actwk[ACTWK_DYNAMIC_START];
  short cnt = ACTWK_RESERVED_START - ACTWK_DYNAMIC_START - 1;

  do {
    ++p_actwk;
    if (p_actwk->r_ptr != 0) {
      if (SPRITE_STATUS_USHORT(p_actwk, 72) != 0) {
        CLEAR_BIT_7(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1]);
      }
    }
    --cnt;
  } while (cnt != -1);

  cnt = ringbuffer[0] - 1;
  if (cnt < 1) return;

  unsigned short* p_ringbuffer = &ringbuffer[1];
  do {
    unsigned short ringwk_id = *p_ringbuffer++;
    if (ringwk_id == 0) continue;
    ringwk[ringwk_id - 1] = -1;
    *(p_ringbuffer - 1) = 0;
    --ringbuffer[0];
    --cnt;
  } while (cnt != -1);
}


// SONIC3K.EXE address: 004511b2
// skdisasm label: RingCheckFloorDist
short RingCheckFloorDist(sprite_status* p_actwk) {
  // TODO
}


// SONIC3K.EXE address: 00451c46
// skdisasm label: RingCheckFloorDist_ReverseGravity
short RingCheckFloorDist_ReverseGravity(sprite_status* p_actwk) {
  // TODO
}
