#include "item.h"
#include <stdbool.h>
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../action.h"
#include "../actset.h"
#include "../coli.h"
#include "../constants.h"
#include "../dircol.h"
#include "../hitchk.h"
#include "../sound.h"
#include "common.h"
#include "toge.h"
static void iteminit(SKC_sprite_status* p_actwk);
static void itemmove(SKC_sprite_status* p_actwk);
static void itemmove3(SKC_sprite_status* p_actwk);
static void itemmove2(SKC_sprite_status* p_actwk);
static void itemdownsub(SKC_sprite_status* p_actwk);
static void itemsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
static void itemsub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
static void itemsub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride);
static void itemget(SKC_sprite_status* p_actwk);
static void item2init(SKC_sprite_status* p_actwk);
static void item2move(SKC_sprite_status* p_actwk);
static void item2move__sub(SKC_sprite_status* p_actwk);
static void item2_00(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_01(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_03(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_03__1up(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_04(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_05(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_06(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_07(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_08(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2_09(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter);
static void item2die(SKC_sprite_status* p_actwk);
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
static SKC_sprite_pattern itemsp00;
static SKC_sprite_pattern itemsp01;
static SKC_sprite_pattern itemsp02;
static SKC_sprite_pattern itemsp03;
static SKC_sprite_pattern itemsp04;
static SKC_sprite_pattern itemsp05;
static SKC_sprite_pattern itemsp06;
static SKC_sprite_pattern itemsp07;
static SKC_sprite_pattern itemsp08;
static SKC_sprite_pattern itemsp09;
static SKC_sprite_pattern itemsp10;
static SKC_sprite_pattern itemsp11;

extern sonic3_ram g_ram;


void item(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler item_move_tbl[5] = {
    &iteminit,
    &itemmove,
    &itemget,
    &itemmove2,
    &itemmove3
  };

  item_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void iteminit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->sprvsize = 15;
  p_actwk->sprhsize = 15;
  p_actwk->patbase = itempat;
  p_actwk->sproffset = 0x04C4;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 14;
  p_actwk->sprvs = 16;
  if (p_actwk->u.obj.flagwork_index != 0 && BIT_IS_SET(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 0)) {
    p_actwk->patno = 11;
    p_actwk->r_ptr = &frameoutchk;
  }
  else {
    p_actwk->colino = 0x46;
    p_actwk->mstno = p_actwk->u.obj.userflag;
    itemmove(p_actwk);
  }
}


static void itemmove(SKC_sprite_status* p_actwk) {
  itemdownsub(p_actwk);
  SKC_hitchk_data data = { 25, 16, 17, fp16_get_integer(p_actwk->xposi) };
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  itemsub(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  itemsub1(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  colibufferchk(p_actwk);
  patchg(p_actwk, itemchg);
  itemmove3(p_actwk);
}


static void itemmove3(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


static void itemmove2(SKC_sprite_status* p_actwk) {
  if (p_actwk->patno == 11) {
    p_actwk->r_ptr = &itemmove3;
  }
  patchg(p_actwk, itemchg);
  frameoutchk(p_actwk);
}


static void itemdownsub(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.item.r_no1 == 0) return;

  if (p_actwk->actflg.vflip == 0) {
    speedset(p_actwk);
    if (p_actwk->yspeed >= 0) {
      SKC_dircol_result result = emycol_d(p_actwk);
      if (result.offset <= 0) {
        short yposi = fp16_get_integer(p_actwk->yposi) + result.offset;
        fp16_set_integer(&p_actwk->yposi, yposi);
        p_actwk->yspeed = 0;
        p_actwk->u.obj.actfree.item.r_no1 = 0;
      }
    }
  }
  else {
    speedset2(p_actwk);
    p_actwk->yspeed -= 0x38;
    if (p_actwk->yspeed >= 0) return;
    SKC_dircol_result result = emycol_u(p_actwk);
    if (result.offset <= 0) {
      short yposi = fp16_get_integer(p_actwk->yposi) - result.offset;
      p_actwk->yspeed = 0;
      p_actwk->u.obj.actfree.item.r_no1 = 0;
    }
  }
}


static void itemsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush) {
  if (*p_plride) {
    itemsub2(p_actwk, p_playerwk, data, p_plride);
  }
  else {
    if (p_playerwk->mstno != 2
        && (p_playerwk->u.play.character != KNUCKLES
            || (p_playerwk->u.play.talent_status != 1 && p_playerwk->u.play.talent_status != 3))) {
      plhitchk_chk_coli_skip_onscreen(p_actwk, p_playerwk, data, p_plride, p_plpush);
    }
  }
}


static void itemsub1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush) {
  if (*p_plride) {
    itemsub2(p_actwk, p_playerwk, data, p_plride);
  }
  else if (g_ram.vs_flag == 0 || p_actwk->mstno != 2) {
    plhitchk_chk_coli_skip_onscreen(p_actwk, p_playerwk, data, p_plride, p_plpush);
  }
}


static void itemsub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride) {
  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + data.sprhs;
  if (p_playerwk->u.play.cddat.jump == 0 && distance >= 0 && distance < data.sprhs * 2) {
    ride_dai(p_actwk, p_playerwk, data.sprvs_ground, data.xposi);
  }
  else {
    p_playerwk->u.play.cddat.ride = 0;
    p_playerwk->u.play.cddat.jump = 1;
    *p_plride = false;
  }
}


static void itemget(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.plpush == 1) {
    g_ram.actwk[0].u.play.cddat.ride = 0;
    g_ram.actwk[0].u.play.cddat.push = 0;
    g_ram.actwk[0].u.play.cddat.jump = 1;
  }
  if (p_actwk->u.obj.cddat.pl2ride == 1 || p_actwk->u.obj.cddat.pl2push == 1) {
    g_ram.actwk[1].u.play.cddat.ride = 0;
    g_ram.actwk[1].u.play.cddat.push = 0;
    g_ram.actwk[1].u.play.cddat.jump = 1;
  }
  p_actwk->u.obj.cddat.wrt = 0;
  p_actwk->u.obj.cddat.plride = 0;
  p_actwk->u.obj.cddat.pl2ride = 0;
  p_actwk->u.obj.cddat.plpush = 0;
  p_actwk->u.obj.cddat.pl2push = 0;
  p_actwk->u.obj.cddat.die = 0;
  p_actwk->colino = 0;
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &item2;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
    result.actwk_ptr->mstno = p_actwk->mstno;
    result.actwk_ptr->actflg = p_actwk->actflg;
    result.actwk_ptr->u.obj.cddat.right = p_actwk->u.obj.cddat.right;
    result.actwk_ptr->u.obj.cddat.down = p_actwk->u.obj.cddat.down;
    result.actwk_ptr->u.obj.cddat.wrt = p_actwk->u.obj.cddat.wrt;
    result.actwk_ptr->u.obj.cddat.plride = p_actwk->u.obj.cddat.plride;
    result.actwk_ptr->u.obj.cddat.pl2ride = p_actwk->u.obj.cddat.pl2ride;
    result.actwk_ptr->u.obj.cddat.plpush = p_actwk->u.obj.cddat.plpush;
    result.actwk_ptr->u.obj.cddat.pl2push = p_actwk->u.obj.cddat.pl2push;
    result.actwk_ptr->u.obj.cddat.die = p_actwk->u.obj.cddat.die;
    result.actwk_ptr->u.obj.ko = p_actwk->u.obj.ko;
  }
  result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &bakuhatu;
    result.actwk_ptr->r_no += 2;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
  }
  if (p_actwk->u.obj.flagwork_index != 0) {
    SET_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 0);
  }
  p_actwk->mstno = 10;
  p_actwk->r_ptr = &itemmove2;
  actionsub(p_actwk);
}


void item2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler item2_move_tbl[3] = {
    &item2init,
    &item2move,
    &item2die
  };

  item2_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void item2init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->sproffset = 0x84C4;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->actflg.static_pattern = 1;
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 8;
  p_actwk->yspeed = -0x300;
  if (p_actwk->actflg.vflip == 1) {
    p_actwk->yspeed = -p_actwk->yspeed;
  }
  p_actwk->patno = p_actwk->mstno + 1;
  p_actwk->patbase = itempat[p_actwk->mstno + 1]->spr;
  item2move(p_actwk);
}


static void item2move(SKC_sprite_status* p_actwk) {
  item2move__sub(p_actwk);
  actionsub(p_actwk);
}


static void item2move__sub(SKC_sprite_status* p_actwk) {
  void(*item2tbl[10])(SKC_sprite_status*, SKC_sprite_status*, unsigned short*) = {
    &item2_00,
    &item2_01,
    &item2_00,
    &item2_03,
    &item2_04,
    &item2_05,
    &item2_06,
    &item2_07,
    &item2_08,
    &item2_09
  };

  if (p_actwk->actflg.vflip == 0 && p_actwk->yspeed < 0) {
    speedset2(p_actwk);
    p_actwk->yspeed += 0x18;
  }
  else if (p_actwk->actflg.vflip == 1 && p_actwk->yspeed >= 0) {
    speedset2(p_actwk);
    p_actwk->yspeed -= 0x18;
  }
  else {
    p_actwk->r_no += 2;
    p_actwk->pattim = 29;
    SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
    unsigned short* p_counter = &g_ram.DAT_08fffecc;
    if (p_playerwk != &g_ram.actwk[0]) {
      p_counter = &g_ram.DAT_08fffece;
    }
    item2tbl[p_actwk->mstno](p_actwk, p_playerwk, p_counter);
  }
}


static void item2_00(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  togedamegesub(p_actwk, p_playerwk);
}


static void item2_01(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++g_ram.DAT_08fffecc;
  ++g_ram.pl_suu;
  ++g_ram.pl_suu_f;
  bgmset(42);
}


static void item2_03(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  g_ram.plring_act += 10;
  if (g_ram.plring_act >= RING_MAX) {
    g_ram.plring_act = RING_MAX;
  }
  g_ram.plring += 10;
  if (g_ram.plring >= RING_MAX) {
    g_ram.plring = RING_MAX;
  }
  SET_BIT(g_ram.plring_f, 0);
  if (g_ram.plring >= RING_EXTRA_LIFE_1) {
    if (!BIT_IS_SET(g_ram.plring_f2, 1)) {
      SET_BIT(g_ram.plring_f2, 1);
      item2_03__1up(p_actwk, p_playerwk, p_counter);
      return;
    }
    if (g_ram.plring >= RING_EXTRA_LIFE_2) {
      if (!BIT_IS_SET(g_ram.plring_f2, 2)) {
        SET_BIT(g_ram.plring_f2, 2);
        item2_03__1up(p_actwk, p_playerwk, p_counter);
        return;
      }
    }
  }
  bgmset(51);
}


static void item2_03__1up(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  if (p_playerwk == &g_ram.actwk[0]) {
    item2_01(p_actwk, p_playerwk, p_counter);
  }
  else {
    item2_00(p_actwk, p_playerwk, p_counter);
  }
}


static void item2_04(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  p_playerwk->u.play.powerdat.speedup = 1;
  p_playerwk->u.play.speedup_timer = 150;
  if (p_playerwk == &g_ram.actwk[0] && g_ram.play_type != PLAY_TYPE_MILES) {
    g_ram.plmaxspdwk = 0xC00;
    g_ram.pladdspdwk = 0x18;
    g_ram.plretspdwk = 0x80;
  }
  else {
    g_ram.pl2maxspdwk = 0xC00;
    g_ram.pl2addspdwk = 0x18;
    g_ram.pl2retspdwk = 0x80;
  }
  SpeedUpMusic(8);
}


static void item2_05(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  p_playerwk->u.play.powerdat.baria = 1;
  p_playerwk->u.play.powerdat.flame_baria = 1;
  p_playerwk->u.play.powerdat.thunder_baria = 0;
  p_playerwk->u.play.powerdat.aqua_baria = 0;
  bgmset(62);
  if (p_actwk->u.obj.ko == 0) {
    g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &flamebaria;
    g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = p_actwk->u.obj.ko;
  }
  else {
    g_ram.actwk[ACTWK_PL2_BARIA].r_ptr = &flamebaria;
    g_ram.actwk[ACTWK_PL2_BARIA].u.obj.ko = p_actwk->u.obj.ko;
  }
}


static void item2_06(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  p_playerwk->u.play.powerdat.baria = 1;
  p_playerwk->u.play.powerdat.flame_baria = 0;
  p_playerwk->u.play.powerdat.thunder_baria = 1;
  p_playerwk->u.play.powerdat.aqua_baria = 0;
  bgmset(65);
  if (p_actwk->u.obj.ko == 0) {
    g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &thunderbaria;
    g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = p_actwk->u.obj.ko;
  }
  else {
    g_ram.actwk[ACTWK_PL2_BARIA].r_ptr = &thunderbaria;
    g_ram.actwk[ACTWK_PL2_BARIA].u.obj.ko = p_actwk->u.obj.ko;
  }
}


static void item2_07(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  p_playerwk->u.play.powerdat.baria = 1;
  p_playerwk->u.play.powerdat.flame_baria = 0;
  p_playerwk->u.play.powerdat.thunder_baria = 0;
  p_playerwk->u.play.powerdat.aqua_baria = 1;
  bgmset(63);
  if (p_actwk->u.obj.ko == 0) {
    g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &aquabaria;
    g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = p_actwk->u.obj.ko;
  }
  else {
    g_ram.actwk[ACTWK_PL2_BARIA].r_ptr = &aquabaria;
    g_ram.actwk[ACTWK_PL2_BARIA].u.obj.ko = p_actwk->u.obj.ko;
  }
}


static void item2_08(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  if (g_ram.ssonicflag == 0 && g_ram.smilesflag == 0) {
    p_playerwk->u.play.powerdat.muteki = 1;
    p_playerwk->u.play.muteki_timer = 150;
    if (g_ram.bossstart == 0 && p_playerwk->u.play.air_timer > 12) {
      bgmset(44);
    }
    if (p_actwk->u.obj.ko == 0) {
      g_ram.actwk[ACTWK_PL_MUTEKI].r_ptr = &muteki;
      g_ram.actwk[ACTWK_PL_MUTEKI].u.obj.ko = p_actwk->u.obj.ko;
    }
    else {
      g_ram.actwk[ACTWK_PL2_MUTEKI].r_ptr = &muteki;
      g_ram.actwk[ACTWK_PL2_MUTEKI].u.obj.ko = p_actwk->u.obj.ko;
    }
  }
}


static void item2_09(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned short* p_counter) {
  ++*p_counter;
  g_ram.plring += 50;
  g_ram.ssonicpallet = 1;
  g_ram.ssonicpallet_next = 15;
  g_ram.ssonicring_timer = 60;

  switch (g_ram.play_type) {
    case PLAY_TYPE_SONIC_AND_MILES:
    case PLAY_TYPE_SONIC:
      g_ram.ssonicflag = 0xFF;
      g_ram.actwk[0].patbase = ssonicpat;
      g_ram.actwk[0].mstno = 31;
      g_ram.plmaxspdwk = 0xA00;
      g_ram.pladdspdwk = 0x30;
      g_ram.plretspdwk = 0x100;
      g_ram.actwk[ACTWK_PL_MUTEKI].r_ptr = &hsonicstars;
      g_ram.actwk[ACTWK_TRAIL].r_ptr = &hypertrail;
      break;
    case PLAY_TYPE_MILES:
      g_ram.smilesflag = 1;
      g_ram.actwk[0].mstno = 41;
      g_ram.pl2maxspdwk = 0x800;
      g_ram.pl2addspdwk = 0x18;
      g_ram.pl2retspdwk = 0xC0;
      g_ram.actwk[ACTWK_PL_MUTEKI].r_ptr = &smilesflickies;
      break;
    case PLAY_TYPE_KNUCKLES:
      g_ram.ssonicflag = 0xFF;
      g_ram.actwk[0].mstno = 31;
      g_ram.plmaxspdwk = 0x800;
      g_ram.pladdspdwk = 0x18;
      g_ram.plretspdwk = 0xC0;
      g_ram.actwk[ACTWK_TRAIL].r_ptr = &hypertrail;
      break;
  }

  g_ram.actwk[0].u.play.control_bitfield = 0x81;
  g_ram.actwk[0].u.play.muteki_timer = 0;
  p_playerwk->u.play.powerdat.muteki = 1;
  soundset(159);
  bgmset(44);
}


static void item2die(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- == 0) {
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


static signed char itemchg0[4] = { 1, 0, 1, -1 };
static signed char itemchg1[8] = { 1, 0, 2, 2, 1, 2, 2, -1 };
static signed char itemchg2[8] = { 1, 0, 3, 3, 1, 3, 3, -1 };
static signed char itemchg3[8] = { 1, 0, 4, 4, 1, 4, 4, -1 };
static signed char itemchg4[8] = { 1, 0, 5, 5, 1, 5, 5, -1 };
static signed char itemchg5[8] = { 1, 0, 6, 6, 1, 6, 6, -1 };
static signed char itemchg6[8] = { 1, 0, 7, 7, 1, 7, 7, -1 };
static signed char itemchg7[8] = { 1, 0, 8, 8, 1, 8, 8, -1 };
static signed char itemchg8[8] = { 1, 0, 9, 9, 1, 9, 9, -1 };
static signed char itemchg9[8] = { 1, 0, 10, 10, 1, 10, 10, -1 };
static signed char itemchg10[8] = { 2, 0, 1, 11, -2, 1, -121, -37 };


SKC_sprite_pattern* itempat[12] = {
  &itemsp00,
  &itemsp01,
  &itemsp02,
  &itemsp03,
  &itemsp04,
  &itemsp05,
  &itemsp06,
  &itemsp07,
  &itemsp08,
  &itemsp09,
  &itemsp10,
  &itemsp11
};


static SKC_sprite_pattern itemsp00 = {
  1,
  {
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp01 = {
  2,
  {
    { -13,  5, 0x0018,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp02 = {
  2,
  {
    { -13,  5, 0x0310,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp03 = {
  2,
  {
    { -13,  5, 0x001C,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp04 = {
  2,
  {
    { -13,  5, 0x2020,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp05 = {
  2,
  {
    { -13,  5, 0x0024,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp06 = {
  2,
  {
    { -13,  5, 0x0030,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp07 = {
  2,
  {
    { -13,  5, 0x002C,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp08 = {
  2,
  {
    { -13,  5, 0x0034,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp09 = {
  2,
  {
    { -13,  5, 0x0028,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp10 = {
  2,
  {
    { -13,  5, 0x0038,  -8 },
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern itemsp11 = {
  1,
  {
    { 0, 13, 0x0010, -16 }
  }
};
