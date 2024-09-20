#include "globals.h"
#include "macros.h"
#include "util.h"
#include "types/hitchkdata.h"
#include "types/hitchkresults.h"
#include "item.h"
#include "004xxxxx.h"
#include "hitchk.h"
#include "toge.h"
static sprite_status_handler item_move_tbl[5];
static void iteminit(sprite_status* p_actwk);
static void itemmove(sprite_status* p_actwk);
static void itemmove3(sprite_status* p_actwk);
static void itemmove2(sprite_status* p_actwk);
static void itemdownsub(sprite_status* p_actwk);
static void itemsub(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char plridebit);
static void itemsub1(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char plridebit);
static hitchk_results itemsub2(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char plridebit);
static void itemget(sprite_status* p_actwk);
static sprite_status_handler item2_move_tbl[3];
static void item2init(sprite_status* p_actwk);
static void item2move(sprite_status* p_actwk);
static void item2move__sub(sprite_status* p_actwk);
static void(*item2tbl[10])(sprite_status*, sprite_status*, unsigned short*);
static void item2_00_item2_02(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_01(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_03(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_04(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_05(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_06(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_07(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_08(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_09(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter);
static void item2die(sprite_status* p_actwk);
static signed char* itemchg[11];
static signed char itemchg0[4];
static signed char itemchg1[8];
static signed char itemchg2[8];
static signed char itemchg3[8];
static signed char itemchg4[8];
static signed char itemchg5[8];
static signed char itemchg6[8];
static signed char itemchg7[8];
static signed char itemchg8[8];
static signed char itemchg9[8];
static signed char itemchg10[8];
static signed char itemsp00[8];
static signed char itemsp01[14];
static signed char itemsp02[14];
static signed char itemsp03[14];
static signed char itemsp04[14];
static signed char itemsp05[14];
static signed char itemsp06[14];
static signed char itemsp07[14];
static signed char itemsp08[14];
static signed char itemsp09[14];
static signed char itemsp10[14];
static signed char itemsp11[8];


void item(sprite_status* p_actwk) {
  item_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static sprite_status_handler item_move_tbl[5] = {
  &iteminit,
  &itemmove,
  &itemget,
  &itemmove2,
  &itemmove3
};


static void iteminit(sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->sprvsize = 15;
  p_actwk->sprhsize = 15;
  p_actwk->patbase = itempat;
  p_actwk->sproffset = 1220;
  SET_BIT(p_actwk->actflg, FLG_LEVELCOORDS);
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 14;
  p_actwk->sprvs = 16;
  if (p_actwk->actfree.item.flagwork_index != 0) {
    if (BIT_0_IS_SET(g_mdRam.flagwork[p_actwk->actfree.item.flagwork_index - 1])) {
      p_actwk->patno = 11;
      p_actwk->r_ptr = &frameoutchk;
      return;
    }
  }
  p_actwk->colino = 70;
  p_actwk->mstno = p_actwk->userflag1;
  itemmove(p_actwk);
}


static void itemmove(sprite_status* p_actwk) {
  itemdownsub(p_actwk);
  hitchk_data data = { 25, 16, 17, LONG_HIGH(p_actwk->xposi) };
  itemsub(p_actwk, &g_mdRam.actwk[0], data, 3);
  itemsub1(p_actwk, &g_mdRam.actwk[1], data, 4);
  Add_Object_To_Collision_Response_List(p_actwk);
  patchg(p_actwk, itemchg);
  itemmove3(p_actwk);
}


static void itemmove3(sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


static void itemmove2(sprite_status* p_actwk) {
  if (p_actwk->patno == 11) {
    p_actwk->r_ptr = &itemmove3;
  }
  patchg(p_actwk, itemchg);
  frameoutchk(p_actwk);
}


static void itemdownsub(sprite_status* p_actwk) {
  if (p_actwk->actfree.item.unknown == 0) return;
  if (!BIT_IS_SET(p_actwk->actflg, FLG_VFLIP)) {
    speedset(p_actwk);
    if (p_actwk->yspeed < 0) return;
    short unknown = ObjCheckFloorDist(p_actwk);
    if (unknown > 0) return;
    p_actwk->yposi += SHORT_TO_LONG_HIGH(unknown);
    p_actwk->yspeed = 0;
    p_actwk->actfree.item.unknown = 0;
  }
  else {
    speedset2(p_actwk);
    p_actwk->yspeed -= 56;
    if (p_actwk->yspeed >= 0) return;
    short unknown = ObjCheckCeilingDist(p_actwk);
    if (unknown > 0) return;
    p_actwk->yposi -= SHORT_TO_LONG_HIGH(unknown);
    p_actwk->yspeed = 0;
    p_actwk->actfree.item.unknown = 0;
  }
}


static void itemsub(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char plridebit) {
  if (BIT_IS_SET(p_actwk->cddat1, plridebit)) {
    itemsub2(p_actwk, p_playerwk, data, plridebit);
    return;
  }
  if (p_playerwk->mstno == 2) return;
  if (p_playerwk->actfree.player.character == KNUCKLES) {
    if (p_playerwk->actfree.player.talent_status == 1) return;
    if (p_playerwk->actfree.player.talent_status == 3) return;
  }
  plhitchk_chk_coli2(p_actwk, p_playerwk, data, plridebit);
}


static void itemsub1(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char plridebit) {
  if (BIT_IS_SET(p_actwk->cddat1, plridebit)) {
    itemsub2(p_actwk, p_playerwk, data, plridebit);
    return;
  }
  if (g_mdRam.vs_flag == 0 || p_actwk->mstno != 2) {
    plhitchk_chk_coli2(p_actwk, p_playerwk, data, plridebit);
  }
}


static hitchk_results itemsub2(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char plridebit) {
  unsigned char width = data.sprhs * 2;
  bool on_box = false;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0 && distance < width) {
      on_box = true;
    }
  }
  if (!on_box) {
    CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
    SET_BIT(p_playerwk->cddat1, CD_JUMP);
    CLEAR_BIT(p_playerwk->cddat1, plridebit);
  }
  else {
    MvSonicOnPtfm(data.xposi);
  }
  hitchk_results results = { 0, 0 };
  return results;
}


static void itemget(sprite_status* p_actwk) {
  if (p_actwk->cddat1 & 0x78) {
    if (p_actwk->cddat1 & 0x28) {
      g_mdRam.actwk[0].cddat1 &= 0xD7;
      SET_BIT(g_mdRam.actwk[0].cddat1, CD_JUMP);
    }
    if (p_actwk->cddat1 & 0x50) {
      g_mdRam.actwk[1].cddat1 &= 0xD7;
      SET_BIT(g_mdRam.actwk[1].cddat1, CD_JUMP);
    }
  }
  p_actwk->cddat1 &= 3;
  p_actwk->colino = 0;
  short slot_cnt;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
  if (created) {
    p_new_actwk->r_ptr = &item2;
    util__copy_high(&p_new_actwk->xposi, &p_actwk->xposi);
    util__copy_high(&p_new_actwk->yposi, &p_actwk->yposi);
    p_new_actwk->mstno = p_actwk->mstno;
    p_new_actwk->actflg = p_actwk->actflg;
    p_new_actwk->cddat1 = p_actwk->cddat1;
    p_new_actwk->actfree.item.player = p_actwk->actfree.item.player;
  }
  created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
  if (created) {
    p_new_actwk->r_ptr = &bakuhatu;
    p_new_actwk->r_no += 2;
    util__copy_high(&p_new_actwk->xposi, &p_actwk->xposi);
    util__copy_high(&p_new_actwk->yposi, &p_actwk->yposi);
  }
  if (p_actwk->actfree.item.flagwork_index != 0) {
    SET_BIT_0(g_mdRam.flagwork[p_actwk->actfree.item.flagwork_index - 1]);
  }
  p_actwk->mstno = 10;
  p_actwk->r_ptr = &itemmove2;
  actionsub(p_actwk);
}


void item2(sprite_status* p_actwk) {
  item2_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static sprite_status_handler item2_move_tbl[3] = {
  &item2init,
  &item2move,
  &item2die
};


static void item2init(sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->sproffset = 33988;
  p_actwk->actflg &= 0x24;
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 8;
  p_actwk->yspeed = -768;
  if (BIT_IS_SET(p_actwk->actflg, FLG_VFLIP)) {
    p_actwk->yspeed = -p_actwk->yspeed;
  }
  p_actwk->patno = p_actwk->mstno + 1;
  p_actwk->patbase = &itempat[p_actwk->mstno + 1];
  item2move(p_actwk);
}


static void item2move(sprite_status* p_actwk) {
  item2move__sub(p_actwk);
  actionsub(p_actwk);
}


static void item2move__sub(sprite_status* p_actwk) {
  if (!BIT_IS_SET(p_actwk->actflg, FLG_VFLIP)) {
    if (p_actwk->yspeed < 0) {
      speedset2(p_actwk);
      p_actwk->yspeed += 24;
      return;
    }
  }
  else {
    if (p_actwk->yspeed >= 0) {
      speedset2(p_actwk);
      p_actwk->yspeed -= 24;
      return;
    }
  }
  p_actwk->r_no += 2;
  p_actwk->pattim = 29;
  sprite_status* p_playerwk = &g_mdRam.actwk[p_actwk->actfree.item.player];
  unsigned short* p_counter = &g_mdRam.DAT_08fffecc;
  if (p_playerwk != &g_mdRam.actwk[0]) {
    p_counter = &g_mdRam.DAT_08fffece;
  }
  item2tbl[p_actwk->mstno](p_actwk, p_playerwk, p_counter);
}


static void(*item2tbl[10])(sprite_status*, sprite_status*, unsigned short*) = {
  &item2_00_item2_02,
  &item2_01,
  &item2_00_item2_02,
  &item2_03,
  &item2_04,
  &item2_05,
  &item2_06,
  &item2_07,
  &item2_08,
  &item2_09
};


static void item2_00_item2_02(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  togedamegesub(p_actwk, p_playerwk);
}


static void item2_01(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++g_mdRam.DAT_08fffecc;
  ++g_mdRam.pl_suu;
  ++g_mdRam.pl_suu_f;
  bgmset(42);
}


static void item2_03(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  g_mdRam.plring_act += 10;
  if (g_mdRam.plring_act >= 999) {
    g_mdRam.plring_act = 999;
  }
  g_mdRam.plring += 10;
  if (g_mdRam.plring >= 999) {
    g_mdRam.plring = 999;
  }
  SET_BIT_0(g_mdRam.plring_f);
  if (g_mdRam.plring >= 100) {
    bool bit_1_clear = !BIT_1_IS_SET(g_mdRam.plring_f2);
    SET_BIT_1(g_mdRam.plring_f2);
    if (bit_1_clear) goto jump2;
    if (g_mdRam.plring >= 200) {
      bool bit_2_clear = !BIT_2_IS_SET(g_mdRam.plring_f2);
      SET_BIT_2(g_mdRam.plring_f2);
      if (bit_2_clear) goto jump2;
    }
  }
  bgmset(51);
  return;

jump2:
  if (p_playerwk == &g_mdRam.actwk[0]) {
    item2_01(p_actwk, p_playerwk, p_counter);
  }
  else {
    item2_00_item2_02(p_actwk, p_playerwk, p_counter);
  }
}


static void item2_04(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  SET_SPEEDUP(p_playerwk->cddat2);
  p_playerwk->actfree.player.speedup_timer = 150;
  if (p_playerwk == &g_mdRam.actwk[0] && g_mdRam.plmode != TEAM_MILES) {
    g_mdRam.plmaxspdwk = 3072;
    g_mdRam.pladdspdwk = 24;
    g_mdRam.plretspdwk = 128;
  }
  else {
    g_mdRam.pl2maxspdwk = 3072;
    g_mdRam.pl2addspdwk = 24;
    g_mdRam.pl2retspdwk = 128;
  }
  SpeedUpMusic(8);
}


static void item2_05(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  p_playerwk->cddat2 &= 0x8E;
  SET_BARIA(p_playerwk->cddat2);
  SET_FLAME_BARIA(p_playerwk->cddat2);
  bgmset(62);
  if (p_actwk->actfree.item.player == 0) {
    g_mdRam.actwk[100].r_ptr = &flamebaria;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[100], 66) = p_playerwk - g_mdRam.actwk;
  }
  else {
    g_mdRam.actwk[101].r_ptr = &flamebaria;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[101], 66) = p_playerwk - g_mdRam.actwk;
  }
}


static void item2_06(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  p_playerwk->cddat2 &= 0x8E;
  SET_BARIA(p_playerwk->cddat2);
  SET_THUNDER_BARIA(p_playerwk->cddat2);
  bgmset(65);
  if (p_actwk->actfree.item.player == 0) {
    g_mdRam.actwk[100].r_ptr = &thunderbaria;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[100], 66) = p_playerwk - g_mdRam.actwk;
  }
  else {
    g_mdRam.actwk[101].r_ptr = &thunderbaria;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[101], 66) = p_playerwk - g_mdRam.actwk;
  }
}


static void item2_07(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  p_playerwk->cddat2 &= 0x8E;
  SET_BARIA(p_playerwk->cddat2);
  SET_AQUA_BARIA(p_playerwk->cddat2);
  bgmset(63);
  if (p_actwk->actfree.item.player == 0) {
    g_mdRam.actwk[100].r_ptr = &aquabaria;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[100], 66) = p_playerwk - g_mdRam.actwk;
  }
  else {
    g_mdRam.actwk[101].r_ptr = &aquabaria;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[101], 66) = p_playerwk - g_mdRam.actwk;
  }
}


static void item2_08(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  if (g_mdRam.ssonicflag != 0) return;
  if (g_mdRam.smilesflag != 0) return;
  SET_MUTEKI(p_playerwk->cddat2);
  p_playerwk->actfree.player.muteki_timer = 150;
  if (g_mdRam.bossstart == 0 && p_playerwk->userflag1 > 12) {
    bgmset(44);
  }
  if (p_actwk->actfree.item.player == 0) {
    g_mdRam.actwk[102].r_ptr = &muteki;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[100], 66) = p_playerwk - g_mdRam.actwk;
  }
  else {
    g_mdRam.actwk[106].r_ptr = &muteki;
    SPRITE_STATUS_USHORT(&g_mdRam.actwk[101], 66) = p_playerwk - g_mdRam.actwk;
  }
}


static void item2_09(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  g_mdRam.plring += 50;
  g_mdRam.ssonicpallet = 1;
  g_mdRam.ssonicpallet_next = 15;
  g_mdRam.ssonicflag = 1;
  g_mdRam.ssonicring_timer = 60;
  g_mdRam.plmaxspdwk = 2048;
  g_mdRam.pladdspdwk = 24;
  g_mdRam.plretspdwk = 192;
  g_mdRam.actwk[0].mstno = 31;
  switch (g_mdRam.plmode) {
    case TEAM_MILES:
      g_mdRam.ssonicflag = 0;
      g_mdRam.smilesflag = 1;
      g_mdRam.actwk[0].mstno = 41;
      g_mdRam.pl2maxspdwk = 2048;
      g_mdRam.pl2addspdwk = 24;
      g_mdRam.pl2retspdwk = 192;
      g_mdRam.actwk[102].r_ptr = &smilesflickies;
      break;
    case TEAM_SONIC_AND_MILES:
    case TEAM_SONIC:
      g_mdRam.actwk[0].patbase = ssonicpat;
      g_mdRam.ssonicflag = 255;
      g_mdRam.plmaxspdwk = 2560;
      g_mdRam.pladdspdwk = 48;
      g_mdRam.plretspdwk = 256;
      g_mdRam.actwk[102].r_ptr = &hsonicstars;
      g_mdRam.actwk[96].r_ptr = &hypertrail;
      break;
    case TEAM_KNUCKLES:
      g_mdRam.actwk[96].r_ptr = &hypertrail;
      break;
  }
  g_mdRam.actwk[0].actfree.player.control_bitfield = 129;
  g_mdRam.actwk[0].actfree.player.muteki_timer = 0;
  SET_MUTEKI(p_playerwk->cddat2);
  soundset(159);
  bgmset(44);
}


static void item2die(sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (util__to_signed(p_actwk->pattim) < 0) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static signed char* itemchg[11] = {
  itemchg0,
  itemchg1,
  itemchg2,
  itemchg3,
  itemchg4,
  itemchg5,
  itemchg6,
  itemchg7,
  itemchg8,
  itemchg9,
  itemchg10
};


static signed char itemchg0[4] = {
     1,    0,    1,   -1
};
static signed char itemchg1[8] = {
     1,    0,    2,    2,    1,    2,    2,   -1
};
static signed char itemchg2[8] = {
     1,    0,    3,    3,    1,    3,    3,   -1
};
static signed char itemchg3[8] = {
     1,    0,    4,    4,    1,    4,    4,   -1
};
static signed char itemchg4[8] = {
     1,    0,    5,    5,    1,    5,    5,   -1
};
static signed char itemchg5[8] = {
     1,    0,    6,    6,    1,    6,    6,   -1
};
static signed char itemchg6[8] = {
     1,    0,    7,    7,    1,    7,    7,   -1
};
static signed char itemchg7[8] = {
     1,    0,    8,    8,    1,    8,    8,   -1
};
static signed char itemchg8[8] = {
     1,    0,    9,    9,    1,    9,    9,   -1
};
static signed char itemchg9[8] = {
     1,    0,   10,   10,    1,   10,  10,   -1
};
static signed char itemchg10[8] = {
     2,    0,    1,   11,   -2,    1, -121,  -37
};


signed char* itempat[12] = {
  itemsp00,
  itemsp01,
  itemsp02,
  itemsp03,
  itemsp04,
  itemsp05,
  itemsp06,
  itemsp07,
  itemsp08,
  itemsp09,
  itemsp10,
  itemsp11
};


static signed char itemsp00[8] = {
     0,    1,  -16,   15,    0,    0,  -16,   -1
};
static signed char itemsp01[14] = {
     0,    2,  -13,    5,   24,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp02[14] = {
     0,    2,  -13,    5,   16,    3,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp03[14] = {
     0,    2,  -13,    5,   28,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp04[14] = {
     0,    2,  -13,    5,   32,   32,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp05[14] = {
     0,    2,  -13,    5,   36,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp06[14] = {
     0,    2,  -13,    5,   48,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp07[14] = {
     0,    2,  -13,    5,   44,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp08[14] = {
     0,    2,  -13,    5,   52,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp09[14] = {
     0,    2,  -13,    5,   40,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp10[14] = {
     0,    2,  -13,    5,   56,    0,   -8,   -1,  -16,   15,
     0,    0,  -16,   -1
};
static signed char itemsp11[8] = {
     0,    1,    0,   13,   16,    0,  -16,   -1
};
