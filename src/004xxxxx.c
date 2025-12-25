#include <string.h>
#include "globals.h"
#include "macros.h"
#include "util.h"
#include "004xxxxx.h"
#include "ring.h"
#include "toge.h"


// SONIC3K.EXE address: 0040a98e
void PlaySoundRegister(long id) {
  // TODO
}


// SONIC3K.EXE address: 0040b72b
void SpeedUpMusic(long tempo) {
  // TODO
}


// SONIC3K.EXE address: 00410426
// skdisasm label: Add_To_DMA_Queue
void Copy_Data_To_VRAM(unsigned char* source, unsigned short destination, unsigned short words) {
  // TODO
}


// SONIC3K.EXE address: 0041144b
// skdisasm label: Load_PLC
void Load_PLC(sprite_status* p_actwk, unsigned short id) {
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


static unsigned char atantbl[257] = {
   0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,
   3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  4,  5,  5,  5,
   5,  5,  5,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  7,
   8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9, 10, 10, 10,
  10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12,
  12, 12, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 17, 17,
  17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19,
  19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21,
  21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23,
  23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24,
  25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26,
  26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32,
  32
};


// SONIC3K.EXE address: 00411511
// skdisasm label: GetArcTan
short atan(long x, long y) {
  short angle = 64;
  if (x == 0 && y == 0) return angle;
  if (x < 0) {
    x = -x;
  }
  if (y < 0) {
    y = -y;
  }
  if (y < x) { // unsigned
    y *= 256;
    y /= x;
    angle = atantbl[y];
  }
  else {
    x *= 256;
    x /= y;
    angle = 64 - atantbl[x];
  }
  if (x < 0) {
    angle = -angle + 128;
  }
  if (y < 0) {
    angle = -angle + 256;
  }
  return angle;
}


// SONIC3K.EXE address: 00412519
// skdisasm label: HUD_AddToScore
void scoreup(unsigned int updata) {
  g_ram.plscore_f = 1;
  g_ram.plscore += updata;
  if (999999 <= g_ram.plscore) {
    g_ram.plscore = 999999;
  }
  if (g_ram.plscore >= g_ram.extrascore) {
    g_ram.extrascore += 5000;
    ++g_ram.pl_suu;
    ++g_ram.pl_suu_f;
    bgmset(42);
  }
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


// SONIC3K.EXE address: 0041e85b
// skdisasm label: MoveSprite
void speedset(sprite_status* p_actwk) {
  p_actwk->xposi += p_actwk->xspeed * 256;
  short yspeed = p_actwk->yspeed;
  p_actwk->yspeed += 56;
  p_actwk->yposi += p_actwk->yspeed * 256;
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
  if (g_ram.reverse_gravity_flag == 0) {
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
  unsigned short* pri_level = &g_ram.pbuffer[level_no][0];

  do {
    if (pri_level[0] < PBUFFER_LEVEL_MAX_SIZE) { // unsigned
      pri_level[0] += PBUFFER_LEVEL_SLOT_SIZE;
      pri_level[pri_level[0] / PBUFFER_LEVEL_SLOT_SIZE] = p_actwk - g_ram.actwk;
      return;
    }
    if (pri_level == &g_ram.pbuffer[PBUFFER_LEVELS - 1][0]) return;
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
        util__assign_high(&p_actwk->xposi, 32512);
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
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= g_ram.scr_x_no;
  if (scr_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->actfree.dynamic.flagwork_index != 0) {
      CLEAR_BIT_7(g_ram.flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
    }
    frameout(p_actwk);
  }
}


// SONIC3K.EXE address: 00421bd2
// skdisasm label: Sprite_OnScreen_Test2
void frameoutchk2(sprite_status* p_actwk, short xposi) {
  unsigned short scr_xposi = util__to_unsigned(xposi) & 0xFF80;
  scr_xposi -= g_ram.scr_x_no;
  if (scr_xposi <= 640) { // unsigned
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->actfree.dynamic.flagwork_index != 0) {
      CLEAR_BIT_7(g_ram.flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
    }
    frameout(p_actwk);
  }
}


// SONIC3K.EXE address: 00421c50
// skdisasm label: Delete_Sprite_If_Not_In_Range
void frameoutchk3(sprite_status* p_actwk) {
  unsigned short scr_xposi = util__to_unsigned(p_actwk->xposi) & 0xFF80;
  scr_xposi -= g_ram.scr_x_no;
  if (scr_xposi > 640) { // unsigned
    if (p_actwk->actfree.dynamic.flagwork_index != 0) {
      CLEAR_BIT_7(g_ram.flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
    }
    frameout(p_actwk);
  }
}


// SONIC3K.EXE address: 00421e38
// skdisasm label: Sprite_CheckDeleteTouch3
void frameoutchkc(sprite_status* p_actwk, short xposi) {
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= g_ram.scr_x_no;
  if (scr_xposi <= 640) {
    Add_Object_To_Collision_Response_List(p_actwk);
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->actfree.dynamic.flagwork_index != 0) {
      CLEAR_BIT_7(g_ram.flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
    }
    frameout(p_actwk);
  }
}


// SONIC3K.EXE address: 00422b67
// skdisasm label: HurtCharacter
bool playdamageset(sprite_status* p_playerwk, sprite_status* p_attack_actwk) {
  short ring_cnt = g_ram.plring;
  if (p_playerwk != &g_ram.actwk[0]) {
    if (g_ram.vs_flag == 0) goto jump0;
    ring_cnt = g_ram.pl2ring;
  }
  if (!BIT_0_IS_SET(p_playerwk->cddat2)) {
    if (g_debugMode == 0) {
      if (BIT_7_IS_SET(p_playerwk->actfree.player.eventflag)) goto jump0;
      if (ring_cnt == 0) goto die;
      sprite_status* p_new_actwk;
      short slot_cnt;
      bool created = Create_New_Sprite(&p_new_actwk, &slot_cnt);
      if (created) {
        p_new_actwk->r_ptr = &flyring;
        util__copy_high(&p_new_actwk->xposi, &p_playerwk->xposi);
        util__copy_high(&p_new_actwk->yposi, &p_playerwk->yposi);
        p_new_actwk->actfree.ring.player = p_playerwk - g_ram.actwk;
      }
    }
  }
  p_playerwk->cddat2 &= 0x8E;

jump0:
  p_playerwk->r_no = 4;
  Player_TouchFloor(p_playerwk);
  SET_BIT(p_playerwk->cddat1, CD_JUMP);
  p_playerwk->yspeed = -1024;
  p_playerwk->xspeed = -512;
  if (BIT_IS_SET(p_playerwk->cddat1, CD_UNDERWATER)) {
    p_playerwk->yspeed = -512;
    p_playerwk->xspeed = -256;
  }
  if (util__to_unsigned(LONG_HIGH(p_playerwk->xposi)) >= util__to_unsigned(LONG_HIGH(p_attack_actwk->xposi))) { // unsigned
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  p_playerwk->mspeed = 0;
  p_playerwk->mstno = 26;
  p_playerwk->actfree.player.invulnerability_timer = 120;
  long sound_id = 53;
  /* WHY:
    togedamegesub does not conform to the signature of sprite_status_handler,
    so we need a cast. As we don't need to call it, this is okay.
  */
  if (p_attack_actwk->r_ptr >= &toge // unsigned
      && p_attack_actwk->r_ptr < (sprite_status_handler)&togedamegesub) { // unsigned
    sound_id = 55;
  }
  soundset(sound_id);
  return true;

die:
  sound_id = 53;
  /* WHY:
    togedamegesub does not conform to the signature of sprite_status_handler,
    so we need a cast. As we don't need to call it, this is okay.
  */
  if (p_attack_actwk->r_ptr >= &toge // unsigned
      && p_attack_actwk->r_ptr < (sprite_status_handler)&togedamegesub) { // unsigned
    sound_id = 55;
  }
  return playdieset(p_playerwk, sound_id);
}


// SONIC3K.EXE address: 00422d9d
// skdisasm label: Kill_Character
bool playdieset(sprite_status* p_playerwk, long sound_id) {
  if (sound_id == 0) {
    if (g_ram.editmode != 0) return true;
    sound_id = 53;
  }
  p_playerwk->cddat2 = 0;
  p_playerwk->actfree.player.eventflag = 0;
  p_playerwk->r_no = 6;
  Player_TouchFloor(p_playerwk);
  SET_BIT(p_playerwk->cddat1, CD_JUMP);
  p_playerwk->yspeed = -1792;
  p_playerwk->xspeed = 0;
  p_playerwk->mspeed = 0;
  p_playerwk->mstno = 24;
  g_ram.plsproffset = p_playerwk->sproffset;
  SET_BIT_7(p_playerwk->sproffset);
  soundset(sound_id);
  return true;
}


// SONIC3K.EXE address: 00422f11
// skdisasm label: Add_SpriteToCollisionResponseList
void Add_Object_To_Collision_Response_List(sprite_status* p_actwk) {
  if (g_ram.colibuffer[0] >= COLBUFFER_MAX_SIZE) return; // unsigned
  g_ram.colibuffer[0] += COLBUFFER_SLOT_SIZE;
  g_ram.colibuffer[g_ram.colibuffer[0] / COLBUFFER_SLOT_SIZE] = p_actwk - g_ram.actwk;
}


// SONIC3K.EXE address: 00426f24
// skdisasm label: Random_Number
unsigned long random() {
  unsigned long d1 = g_ram.ranum;
  if (d1 == 0) {
    d1 = 711800411;
  }
  unsigned long d0 = d1;
  d1 = d1 << 2 & 0xFFFFFFFF;
  d1 = d1 + d0 & 0xFFFFFFFF;
  d1 = d1 << 3 & 0xFFFFFFFF;
  d1 = d1 + d0 & 0xFFFFFFFF;
  d0 = d0 & 0xFFFF0000 | d1 & 0x0000FFFF;
  ROTATE_RIGHT(d1, 16);
  d0 = d0 & 0xFFFF0000 | ((d0 & 0x0000FFFF) + (d1 & 0x0000FFFF) & 0x0000FFFF);
  d1 = d1 & 0xFFFF0000 | d0 & 0x0000FFFF;
  ROTATE_RIGHT(d1, 16);
  g_ram.ranum = d1;
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


// SONIC3K.EXE address: 0042b87a
// skdisasm label: CreateNewSprite4
bool Create_New_Sprite4(sprite_status** pp_new_actwk, short remaining_slot_cnt) {
  for (--remaining_slot_cnt ; remaining_slot_cnt >= 0; --remaining_slot_cnt) {
    ++*pp_new_actwk;
    if ((*pp_new_actwk)->r_ptr == 0) return true;
  }

  return false;
}


// SONIC3K.EXE address: 0042b8b8
// skdisasm label: Create_New_Sprite
bool Create_New_Sprite(sprite_status** pp_new_actwk, short* p_slot_cnt) {
  *pp_new_actwk = &g_ram.actwk[ACTWK_DYNAMIC_START];
  *p_slot_cnt = ACTWK_RESERVED_START - ACTWK_DYNAMIC_START - 1;
  return Create_New_Sprite_Int(pp_new_actwk, p_slot_cnt);
}


// SONIC3K.EXE address: 0042b8cf
// skdisasm label: Create_New_Sprite3
bool Create_New_Sprite3(sprite_status* p_actwk, sprite_status** pp_new_actwk, short* p_slot_cnt) {
  *pp_new_actwk = p_actwk;

  /* BUGFIX:
    The original code uses a lookup table to determine the amount of slots.
    However, there's a bug in the generation of this table. As a result:
    - it thinks there are no eligible slots if p_actwk is the first dynamic
      sprite
    - it considers the slot for the first reserved sprite an eligible slot
  */

  /* WHY:
    We decrement the result by one because we want to know how many slots
    there are between p_actwk and &actwk[93]. We decrement it another time
    because the amount of slots is zero-based.
  */

  *p_slot_cnt = (&g_ram.actwk[ACTWK_RESERVED_START] - p_actwk) - 1 - 1;
  if (*p_slot_cnt < 0) return false;
  return Create_New_Sprite_Int(pp_new_actwk, p_slot_cnt);
}


// Address: 0042b8ff
bool Create_New_Sprite_Int(sprite_status** pp_new_actwk, short* p_slot_cnt) {
  for ( ; *p_slot_cnt != -1; --*p_slot_cnt) {
    ++*pp_new_actwk;
    if ((*pp_new_actwk)->r_ptr == 0) return true;
  }

  return false;
}


// SONIC3K.EXE address: 0042b998
// skdisasm label: Clear_SpriteRingMem
void Clear_SpriteRingMem() {
  sprite_status* p_actwk = &g_ram.actwk[ACTWK_DYNAMIC_START];
  short cnt = ACTWK_RESERVED_START - ACTWK_DYNAMIC_START - 1;

  /* BUGFIX
    The first thing the original loop's code does is increment p_actwk.
    As a result:
    - the first dynamic sprite is skipped
    - the first reserved sprite is cleared
    This is fixed by incrementing p_actwk at the end of the loop.
  */

  do {
    if (p_actwk->r_ptr != 0) {
      if (p_actwk->actfree.dynamic.flagwork_index != 0) {
        CLEAR_BIT_7(g_ram.flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
      }
    }
    ++p_actwk;
    --cnt;
  } while (cnt != -1);

  cnt = g_ram.ringbuffer[0] - 1;
  if (cnt < 1) return;

  unsigned short* p_ringbuffer = &g_ram.ringbuffer[1];
  do {
    unsigned short ringwk_id = *p_ringbuffer++;
    if (ringwk_id == 0) continue;
    g_ram.ringwk[ringwk_id - 1] = -1;
    *(p_ringbuffer - 1) = 0;
    --g_ram.ringbuffer[0];
    --cnt;
  } while (cnt != -1);
}


// SONIC3K.EXE address: 004380ba
// skdisasm label: Player_TouchFloor
void Player_TouchFloor(sprite_status* p_actwk) {
  // TODO
}


// SONIC3K.EXE address: 00439f69
// skdisasm label: Perform_Player_DPLC
void Perform_Player_DPLC(sprite_status* p_playerwk, unsigned char patno) {
  // TODO
}


// SONIC3K.EXE address: 00451080
// skdisasm label: ObjCheckFloorDist
short ObjCheckFloorDist(sprite_status* p_actwk) {
  // TODO
}


// SONIC3K.EXE address: 00451090
// skdisasm label: ObjCheckFloorDist2
short ObjCheckFloorDist2(sprite_status* p_actwk, short xposi) {
  // TODO
}


// SONIC3K.EXE address: 004511b2
// skdisasm label: RingCheckFloorDist
short RingCheckFloorDist(sprite_status* p_actwk) {
  // TODO
}


// SONIC3K.EXE address: 00451a95
// skdisasm label: ObjCheckCeilingDist
short ObjCheckCeilingDist(sprite_status* p_actwk) {
  // TODO
}


// SONIC3K.EXE address: 00451c46
// skdisasm label: RingCheckFloorDist_ReverseGravity
short RingCheckFloorDist_ReverseGravity(sprite_status* p_actwk) {
  // TODO
}
