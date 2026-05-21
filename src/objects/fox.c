#include "fox.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../data/cg/fox.h"
#include "../data/pat/fox.h"
#include "../data/wrt/fox.h"
#include "../data/vsplaydata.h"
#include "../types/playwork.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../types/swdata.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/fp8.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../coli.h"
#include "../constants.h"
#include "../dircol.h"
#include "../edit.h"
#include "../etc.h"
#include "../fcol.h"
#include "../sound.h"
#include "player.h"
static void vsfoxinit(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsfoxmove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsfoxwalk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsfoxjump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsflychk(SKC_sprite_status* p_playerwk);
static void vsfoxballwalk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsfoxballjump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsfoxballchk(SKC_sprite_status* p_playerwk);
static void vsfoxballset(SKC_sprite_status* p_playerwk);
static bool vsfoxspinchk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00init(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00move(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxpowercnt(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxcpu_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_wait0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_appear(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_ridechk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_wait1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_worknai(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_drop_off_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_drop_off(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_fly_up0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_wait2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_carry_up_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_carry_up(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_carry_move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_fly_up1_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_fly_up1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_fly(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_land_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcpu_land(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void FUN_0043d682(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxcarrychk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxgrab(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void foxwaterchk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00walk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00jump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void flyswimchk(SKC_sprite_status* p_playerwk);
static void setflyswim(SKC_sprite_status* p_playerwk);
static void foxball00walk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxball00jump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxlevermove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxlmovecol(SKC_sprite_status* p_playerwk);
static void foxwalk_l(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxwalk_r(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxballlmove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxballwalk_l(SKC_sprite_status* p_playerwk, short plretspdwk);
static void foxballwalk_r(SKC_sprite_status* p_playerwk, short plretspdwk);
static void foxjumpmove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxlimitchk(SKC_sprite_status* p_playerwk);
static void foxlimitset(SKC_sprite_status* p_playerwk, short cal_limit);
static void foxballchk(SKC_sprite_status* p_playerwk);
static void foxballset(SKC_sprite_status* p_playerwk);
static bool foxjumpchk(SKC_sprite_status* p_playerwk);
static void foxjumpchk2(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxjumpchk3(SKC_sprite_status* p_playerwk, SKC_play_work work);
static bool foxspinchk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxjumpcolchk(SKC_sprite_status* p_playerwk);
static void foxjumpcolsub(SKC_sprite_status* p_playerwk);
static void foxjumpcolsub1(SKC_sprite_status* p_playerwk);
static void fox00damage(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00damage_sub(SKC_sprite_status* p_playerwk);
static void fox00die(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00erase(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00appear(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void fox00drown(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void foxpatchgmainwrt(SKC_sprite_status* p_playerwk);
static void foxpatchgmain(SKC_sprite_status* p_playerwk);
static void foxpatchgmain0(SKC_sprite_status* p_actwk, unsigned char** pp_chg);
static void foxpatchgmain2(SKC_sprite_status* p_actwk, unsigned char* p_chg);
static void foxrunchg(SKC_sprite_status* p_actwk, unsigned char patno);
static void foxrunchg2(SKC_sprite_status* p_actwk, unsigned char patno);
static void foxrunchg3(SKC_sprite_status* p_actwk);
static void foxrunchg4(SKC_sprite_status* p_actwk);
static unsigned char* foxchg[42];
static unsigned char foxchg00[10];
static unsigned char foxchg01[10];
static unsigned char foxchg02[5];
static unsigned char foxchg03[5];
static unsigned char foxchg04[10];
static unsigned char foxchg05[62];
static unsigned char foxchg06[24];
static unsigned char foxchg07[3];
static unsigned char foxchg08[3];
static unsigned char foxchg09[5];
static unsigned char foxchg10[3];
static unsigned char foxchg11[3];
static unsigned char foxchg12[4];
static unsigned char foxchg13[7];
static unsigned char foxchg14[3];
static unsigned char foxchg15[10];
static unsigned char foxchg16[15];
static unsigned char foxchg17[4];
static unsigned char foxchg18[6];
static unsigned char foxchg19[5];
static unsigned char foxchg20[3];
static unsigned char foxchg21[7];
static unsigned char foxchg22[3];
static unsigned char foxchg23[3];
static unsigned char foxchg24[3];
static unsigned char foxchg25[4];
static unsigned char foxchg26[3];
static unsigned char foxchg27[4];
static unsigned char foxchg28[3];
static unsigned char foxchg29[10];
static unsigned char foxchg30[10];
static unsigned char foxchg31[10];
static unsigned char foxchg32[3];
static unsigned char foxchg33[3];
static unsigned char foxchg34[3];
static unsigned char foxchg35[3];
static unsigned char foxchg36[4];
static unsigned char foxchg37[7];
static unsigned char foxchg38[7];
static unsigned char foxchg39[4];
static unsigned char foxchg40[5];
static unsigned char foxchg41[15];
static void foxtailswrt(SKC_sprite_status* p_actwk);
static void foxwrt1(unsigned short* p_wrtpat, unsigned short cnt, unsigned short vram_adr, unsigned char* p_cg);
static void vsfoxpatchgmain(SKC_sprite_status* p_playerwk);
static void vsfoxpatchgmain0(SKC_sprite_status* p_actwk, unsigned char** pp_chg);
static void vsfoxpatchgmain2(SKC_sprite_status* p_actwk, unsigned char* p_chg);
static void vsfoxrunchg(SKC_sprite_status* p_actwk, unsigned char patno);
static void vsfoxflipchg(SKC_sprite_status* p_actwk);
static void vsfoxrunchg2(SKC_sprite_status* p_actwk, unsigned char patno);
static void vsfoxrunchg3(SKC_sprite_status* p_actwk);
static void vsfoxrunchg4(SKC_sprite_status* p_actwk);
static unsigned char* vsfoxchg[33];
static unsigned char vsfoxchg00[6];
static unsigned char vsfoxchg01[6];
static unsigned char vsfoxchg02[5];
static unsigned char vsfoxchg03[5];
static unsigned char vsfoxchg04[6];
static unsigned char vsfoxchg05[27];
static unsigned char vsfoxchg06[3];
static unsigned char vsfoxchg07[4];
static unsigned char vsfoxchg08[7];
static unsigned char vsfoxchg09[3];
static unsigned char vsfoxchg10[3];
static unsigned char vsfoxchg11[4];
static unsigned char vsfoxchg12[3];
static unsigned char vsfoxchg13[3];
static unsigned char vsfoxchg14[3];
static unsigned char vsfoxchg15[3];
static unsigned char vsfoxchg16[3];
static unsigned char vsfoxchg17[3];
static unsigned char vsfoxchg18[3];
static unsigned char vsfoxchg19[3];
static unsigned char vsfoxchg20[3];
static unsigned char vsfoxchg21[3];
static unsigned char vsfoxchg22[3];
static unsigned char vsfoxchg23[3];
static unsigned char vsfoxchg24[3];
static unsigned char vsfoxchg25[6];
static unsigned char vsfoxchg26[4];
static void vsfoxtailswrt(SKC_sprite_status* p_actwk);
static void vsfoxwrt(SKC_sprite_status* p_playerwk);
static void vsfoxwrt0(unsigned short* p_wrtpat, unsigned short cnt, unsigned short vram_adr, unsigned char* p_cg);
static void foxtails(SKC_sprite_status* p_actwk);
static void foxtailsmove(SKC_sprite_status* p_actwk);
static unsigned char* foxtailschg[13];
static unsigned char foxtailschg00[3];
static unsigned char foxtailschg01[7];
static unsigned char foxtailschg02[8];
static unsigned char foxtailschg03[6];
static unsigned char foxtailschg04[6];
static unsigned char foxtailschg05[6];
static unsigned char foxtailschg06[6];
static unsigned char foxtailschg07[6];
static unsigned char foxtailschg08[6];
static unsigned char foxtailschg09[6];
static unsigned char foxtailschg10[6];
static unsigned char foxtailschg11[4];
static unsigned char foxtailschg12[4];
static void vsfoxtails(SKC_sprite_status* p_actwk);
static void vsfoxtailsmove(SKC_sprite_status* p_actwk);
static unsigned char* vsfoxtailschg[4];
static unsigned char vsfoxtailschg00[3];
static unsigned char vsfoxtailschg01[5];
static unsigned char vsfoxtailschg02[5];
static void ev0201_sub(SKC_sprite_status* p_actwk);
static void ev0201_sub0(SKC_sprite_status* p_actwk);
static void ev0201_sub1(SKC_sprite_status* p_actwk);
static void ev0201_sub2(SKC_sprite_status* p_actwk);

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void vsfox(SKC_sprite_status* p_playerwk) {
  void(*act_tbl[6])(SKC_sprite_status*, SKC_play_work) = {
    &vsfoxinit,
    &vsfoxmove,
    &fox00damage,
    &fox00die,
    &fox00erase,
    &fox00appear
  };

  if (p_playerwk == &g_ram.actwk[0]) {
    if (g_ram.actwk[1].u.play.character == p_playerwk->u.play.character) {
      p_playerwk->actflg.vspl ^= 1;
    }
    if (g_ram.editmode != 0) {
      edit(p_playerwk);
    }
    else {
      SKC_play_work work = {
        &g_ram.plmaxspdwk,
        &g_ram.pladdspdwk,
        &g_ram.plretspdwk,
        &g_ram.scra_vline,
        &g_ram.actwk[ACTWK_PL_EFFECT]
      };
      act_tbl[p_playerwk->r_no](p_playerwk, work);
    }
  }
  else {
    if (g_ram.actwk[0].u.play.character == p_playerwk->u.play.character) {
      p_playerwk->actflg.vspl2 ^= 1;
    }
    SKC_play_work work = {
      &g_ram.pl2maxspdwk,
      &g_ram.pl2addspdwk,
      &g_ram.pl2retspdwk,
      &g_ram.scra_vline2,
      &g_ram.actwk[ACTWK_PL2_EFFECT]
    };
    act_tbl[p_playerwk->r_no](p_playerwk, work);
  }
}


static void vsfoxinit(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  p_playerwk->r_no += 2;
  p_playerwk->sprvsize = 11;
  p_playerwk->sprhsize = 5;
  p_playerwk->u.play.height = 11;
  p_playerwk->u.play.width = 5;
  p_playerwk->patbase = vsfoxpat;
  p_playerwk->sprpri = PRI_2;
  p_playerwk->sprhs = 12;
  p_playerwk->sprvs = 12;
  p_playerwk->actflg.relative_coordinates = 1;
  p_playerwk->actflg.onscreen = 1;
  p_playerwk->u.play.character == MILES;
  *work.plmaxspdwk_ptr = vsplaydata[p_playerwk->u.play.character][0];
  *work.pladdspdwk_ptr = vsplaydata[p_playerwk->u.play.character][1];
  *work.plretspdwk_ptr = vsplaydata[p_playerwk->u.play.character][2];
  if (g_ram.markerno == 0) {
    p_playerwk->u.play.top_solid_bit = 12;
    p_playerwk->u.play.lrb_solid_bit = 13;
    p_playerwk->sproffset = p_playerwk == &g_ram.actwk[0] ? 0x0680 : 0x06A0;
    if (get_zone(g_ram.stageno) == ENDLESS_MINE) {
      SET_BIT(p_playerwk->sproffset, 15);
    }
    if (p_playerwk == &g_ram.actwk[0]) {
      g_ram.plxposi_s = fp16_get_integer(p_playerwk->xposi);
      g_ram.plyposi_s = fp16_get_integer(p_playerwk->yposi);
      g_ram.plsproffset_s = p_playerwk->sproffset;
      g_ram.pl_top_solid_bit_s = p_playerwk->u.play.top_solid_bit;
      g_ram.pl_lrb_solid_bit_s = p_playerwk->u.play.lrb_solid_bit;
      g_ram.actwk[ACTWK_TRAIL].r_ptr = &vsfoxtails;
      g_ram.actwk[ACTWK_TRAIL].u.obj.oya = p_playerwk - g_ram.actwk;
    }
    else {
      g_ram.plxposi_s2 = fp16_get_integer(p_playerwk->xposi);
      g_ram.plyposi_s2 = fp16_get_integer(p_playerwk->yposi);
      g_ram.plsproffset_s2 = p_playerwk->sproffset;
      g_ram.pl_top_solid_bit_s2 = p_playerwk->u.play.top_solid_bit;
      g_ram.pl_lrb_solid_bit_s2 = p_playerwk->u.play.lrb_solid_bit;
      g_ram.actwk[ACTWK_MILES_TAILS].r_ptr = &vsfoxtails;
      g_ram.actwk[ACTWK_MILES_TAILS].u.play.ride_obj = p_playerwk - g_ram.actwk;
    }
  }
  p_playerwk->u.play.flip_rev_cnt = 0;
  p_playerwk->u.play.flip_rev_frame_cnt = 4;
  p_playerwk->u.play.air_timer = 30;
  g_ram.foxcpu_rno = 0;
  g_ram.foxcpu_timer = 600;
  g_ram.fox_appear_timer = 0;
  vsfoxmove(p_playerwk, work);
}


static void vsfoxmove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  void(*act_tbl[4])(SKC_sprite_status*, SKC_play_work) = {
    &vsfoxwalk,
    &vsfoxjump,
    &vsfoxballwalk,
    &vsfoxballjump
  };

  if (g_ram.debugflag != 0 && p_playerwk == &g_ram.actwk[0] && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    if (p_playerwk == &g_ram.actwk[0]) {
      g_ram.swdata0 = g_ram.swdata;
      if (g_ram.pl_input_lock_flag == 0) {
        g_ram.swdata0 = g_ram.swdata1;
      }
    }
    else {
      if (g_ram.pl2_input_lock_flag == 0) {
        g_ram.swdata0 = g_ram.swdata2;
      }
    }
    foxpowercnt(p_playerwk, work);
    if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 0)) {
      unsigned char index = p_playerwk->u.play.cddat.jump + p_playerwk->u.play.cddat.ball * 2;
      act_tbl[index](p_playerwk, work);
    }
    if (g_ram.scralim_up == -256) {
      short yposi = (unsigned short)fp16_get_integer(p_playerwk->yposi) & g_ram.scrc_v;
      fp16_set_integer(&p_playerwk->yposi, yposi);
    }
    short xposi = ((unsigned short)fp16_get_integer(p_playerwk->xposi) & g_ram.scrc3) + 0x400;
    fp16_set_integer(&p_playerwk->xposi, xposi);
    playposiwkset(p_playerwk);
    p_playerwk->u.play.angle_front = g_ram.dirstk[0];
    p_playerwk->u.play.angle_below = g_ram.dirstk[2];
    if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 1)) {
      vsfoxpatchgmain(p_playerwk);
      vsfoxwrt(p_playerwk);
    }
    if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 5)
        && !BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) {
      vspcol(p_playerwk);
    }
  }
}


static void vsfoxwalk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (vsfoxspinchk(p_playerwk, work) || foxjumpchk(p_playerwk)) return;

  keispd(p_playerwk);
  foxlevermove(p_playerwk, work);
  vsfoxballchk(p_playerwk);
  speedset2(p_playerwk);
  fcol(p_playerwk);
  fallchk(p_playerwk);
}


static void vsfoxjump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.talent_status == 0) {
    foxjumpchk2(p_playerwk, work);
    foxjumpmove(p_playerwk, work);
    speedset(p_playerwk);
    if (p_playerwk->u.play.cddat.underwater == 1) {
      p_playerwk->yspeed -= 0x28;
    }
    direcchg(p_playerwk);
    foxjumpcolchk(p_playerwk);
  }
  else {
    vsflychk(p_playerwk);
    foxjumpmove(p_playerwk, work);
    speedset2(p_playerwk);
    direcchg(p_playerwk);
    foxjumpcolchk(p_playerwk);
  }
}


static void vsflychk(SKC_sprite_status* p_playerwk) {
  if (g_ram.gametimer & 1 && p_playerwk->pattimm != 0) {
    --p_playerwk->pattimm;
  }
  if (p_playerwk->u.play.talent_status != 1) {
    if (p_playerwk->yspeed >= -0x100) {
      p_playerwk->yspeed -= 0x20;
      ++p_playerwk->u.play.talent_status;
      if (p_playerwk->u.play.talent_status == 32) {
        p_playerwk->u.play.talent_status = 1;
      }
    }
    else {
      p_playerwk->u.play.talent_status = 1;
    }
  }
  else {
    if (are_any_trg_buttons_used(g_ram.swdata0.pressed)
        && p_playerwk->yspeed >= -0x100
        && p_playerwk->pattimm != 0
        && (p_playerwk->u.play.cddat.underwater == 0 || g_ram.miles_carry_flag == 0)) {
      p_playerwk->u.play.talent_status = 2;
    }
    p_playerwk->yspeed += 8;
  }
  if (g_ram.scralim_up + 16 >= fp16_get_integer(p_playerwk->yposi) && p_playerwk->yspeed < 0) {
    p_playerwk->yspeed = 0;
  }
  if (p_playerwk->pattimm == 0) {
    if (!(g_ram.gametimer + 8 & 0xF)) {
      soundset(-69);
    }
  }
  else {
    if (!(g_ram.gametimer + 8 & 0xF)) {
      soundset(-70);
    }
  }
}


static void vsfoxballwalk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.spindash_flag == 0 && foxjumpchk(p_playerwk)) return;

  keispd2(p_playerwk);
  foxballlmove(p_playerwk, work);
  speedset2(p_playerwk);
  fcol(p_playerwk);
  fallchk(p_playerwk);
}


static void vsfoxballjump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  foxjumpchk2(p_playerwk, work);
  foxjumpmove(p_playerwk, work);
  speedset(p_playerwk);
  if (p_playerwk->u.play.cddat.underwater == 1) {
    p_playerwk->yspeed -= 0x28;
  }
  direcchg(p_playerwk);
  foxjumpcolchk(p_playerwk);
}


static void vsfoxballchk(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.powerdat.mizuflag == 1) return;
  if (abs(p_playerwk->mspeed < 0x80)) return;
  if (g_ram.swdata0.down.l == 1 || g_ram.swdata0.down.r == 1) return;
  if (g_ram.swdata0.down.d == 0) return;

  vsfoxballset(p_playerwk);
}


static void vsfoxballset(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.ball == 1) return;

  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 7;
  p_playerwk->sprhsize = 3;
  p_playerwk->mstno = 2;
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 4);
  soundset(60);
  if (p_playerwk->mspeed == 0) {
    p_playerwk->mspeed = 0x200;
  }
}


static bool vsfoxspinchk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short spd_tbl[9] = {
    0x800, 0x880, 0x900, 0x980, 0xA00, 0xA80, 0xB00, 0xB80, 0xC00
  };

  if (p_playerwk->u.play.spindash_flag == 0) {
    if (p_playerwk->mstno == 8 && are_any_trg_buttons_used(g_ram.swdata0.pressed)) {
      p_playerwk->mstno = 9;
      soundset(-85);
      p_playerwk->u.play.spindash_flag = 1;
      p_playerwk->u.play.spindash_ctr = 0;
      if (p_playerwk->u.play.air_timer >= 12) {
        work.effectwk_ptr->mstno = 2;
      }
      foxlimitchk(p_playerwk);
      fcol(p_playerwk);
      return true;
    }
  }
  else {
    if (g_ram.swdata0.down.d == 0) {
      p_playerwk->sprvsize = 7;
      p_playerwk->sprhsize = 3;
      p_playerwk->mstno = 2;
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 4);
      p_playerwk->u.play.spindash_flag = 0;
      unsigned char index = p_playerwk->u.play.spindash_ctr >> 8;
      p_playerwk->mspeed = spd_tbl[index];
      short delay = -((p_playerwk->mspeed - 0x800) * 2 & 0x1F00) + 0x2000;
      if (p_playerwk == &g_ram.actwk[0]) {
        g_ram.DAT_08ffee24 = delay;
      }
      else {
        g_ram.DAT_08ffee28 = delay;
      }
      if (p_playerwk->u.play.cddat.left == 1) {
        p_playerwk->mspeed = -p_playerwk->mspeed;
      }
      p_playerwk->u.play.cddat.ball = 1;
      work.effectwk_ptr->mstno = 0;
      soundset(-74);
    }
    else {
      if (p_playerwk->u.play.spindash_ctr != 0) {
        p_playerwk->u.play.spindash_ctr -= p_playerwk->u.play.spindash_ctr >> 5;
        if (p_playerwk->u.play.spindash_ctr < 0) {
          p_playerwk->u.play.spindash_ctr = 0;
        }
      }
      if (are_any_trg_buttons_used(g_ram.swdata0.pressed)) {
        p_playerwk->mstno = 9;
        p_playerwk->mstrestart = 0;
        soundset(-85);
        p_playerwk->u.play.spindash_ctr += 0x200;
        if (p_playerwk->u.play.spindash_ctr >= 0x800) {
          p_playerwk->u.play.spindash_ctr = 0x800;
        }
      }
    }
    if (*work.scra_vline_ptr != 96) {
      if (*work.scra_vline_ptr < 96) {
        *work.scra_vline_ptr += 4;
      }
      *work.scra_vline_ptr -= 2;
    }
    fcol(p_playerwk);
    return true;
  }
  return false;
}


void fox00(SKC_sprite_status* p_playerwk) {
  void(*fox00_move_tbl[7])(SKC_sprite_status*, SKC_play_work) = {
    &fox00init,
    &fox00move,
    &fox00damage,
    &fox00die,
    &fox00erase,
    &fox00appear,
    &fox00drown
  };

  if (g_ram.play_type == PLAY_TYPE_MILES && g_ram.editmode != 0) {
    if (g_ram.editmode != 1) {
      if (g_ram.swdata1.pressed.b == 1) {
        g_ram.editmode = 0;
      }
      ++p_playerwk->patno;
      if (p_playerwk->patno >= 251) {
        p_playerwk->patno = 0;
      }
      foxwrt(p_playerwk);
      actionsub(p_playerwk);
    }
    else {
      edit(p_playerwk);
    }
  }
  else {
    SKC_play_work work = {
      &g_ram.pl2maxspdwk,
      &g_ram.pl2addspdwk,
      &g_ram.pl2retspdwk,
      &g_ram.scra_vline2,
      &g_ram.actwk[ACTWK_PL2_EFFECT]
    };
    fox00_move_tbl[p_playerwk->r_no / 2](p_playerwk, work);
  }
}


static void fox00init(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  p_playerwk->r_no += 2;
  p_playerwk->sprvsize = 15;
  p_playerwk->sprhsize = 9;
  p_playerwk->u.play.height = 15;
  p_playerwk->u.play.width = 9;
  p_playerwk->patbase = foxpat;
  p_playerwk->sprpri = PRI_2;
  p_playerwk->sprhs = 24;
  p_playerwk->sprvs = 24;
  p_playerwk->actflg.relative_coordinates = 1;
  p_playerwk->actflg.onscreen = 1;
  p_playerwk->u.play.character == MILES;
  *work.plmaxspdwk_ptr = 0x600;
  *work.pladdspdwk_ptr = 0xC;
  *work.plretspdwk_ptr = 0x80;
  if (g_ram.play_type == PLAY_TYPE_MILES) {
    if (g_ram.markerno == 0) {
      p_playerwk->sproffset = 0x6A0;
      p_playerwk->u.play.top_solid_bit = 12;
      p_playerwk->u.play.lrb_solid_bit = 13;
      if (g_ram.marker_flag != 2) {
        g_ram.plxposi_s = fp16_get_integer(p_playerwk->xposi);
        g_ram.plyposi_s = fp16_get_integer(p_playerwk->yposi);
        g_ram.plsproffset_s = p_playerwk->sproffset;
        g_ram.pl_top_solid_bit_s = p_playerwk->u.play.top_solid_bit;
        g_ram.pl_lrb_solid_bit_s = p_playerwk->u.play.lrb_solid_bit;
      }
    }
  }
  else {
    p_playerwk->sproffset = 0x6A0;
    p_playerwk->u.play.top_solid_bit = g_ram.actwk[0].u.play.top_solid_bit;
    p_playerwk->u.play.lrb_solid_bit = g_ram.actwk[0].u.play.lrb_solid_bit;
    if (BIT_IS_SET(g_ram.actwk[0].sproffset, 15)) {
      SET_BIT(p_playerwk->sproffset, 15);
    }
  }
  p_playerwk->u.play.flip_rev_cnt = 0;
  p_playerwk->u.play.flip_rev_frame_cnt = 4;
  g_ram.smilesflag = 0;
  p_playerwk->u.play.air_timer = 30;
  if (g_ram.foxcpu_rno != 32 && g_ram.foxcpu_rno != 18) {
    g_ram.foxcpu_rno = 0;
  }
  g_ram.foxcpu_timer = 0;
  g_ram.fox_appear_timer = 0;
  g_ram.actwk[ACTWK_MILES_TAILS].r_ptr = &foxtails;
  g_ram.actwk[ACTWK_MILES_TAILS].u.play.ride_obj = p_playerwk - g_ram.actwk;
  g_ram.markno_s = g_ram.markerno;
}


static void fox00move(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  void(*fox00_move_tbl[4])(SKC_sprite_status*, SKC_play_work) = {
    &fox00walk,
    &fox00jump,
    &foxball00walk,
    &foxball00jump
  };

  if (g_ram.play_type == PLAY_TYPE_MILES && g_ram.debugflag != 0) {
    if (g_ram.swdata1.pressed.a == 1) {
      g_ram.swdata1.pressed.a = 0;
      g_ram.reverse_gravity_flag ^= 1;
    }
    if (g_ram.swdata1.pressed.b == 1) {
      g_ram.editmode = 1;
      g_ram.pl_input_lock_flag = 0;
      if (g_ram.swdata1.down.c == 1) {
        g_ram.editmode = 2;
        p_playerwk->mstno = 0;
      }
      return;
    }
  }
  if (p_playerwk == &g_ram.actwk[0]) {
    g_ram.swdata0 = g_ram.swdata;
    if (g_ram.pl_input_lock_flag == 0) {
      g_ram.swdata0 = g_ram.swdata1;
      g_ram.swdata = g_ram.swdata1;
    }
  }
  else {
    if (g_ram.pl2_input_lock_flag == 0) {
      g_ram.swdata0 = g_ram.swdata2;
    }
    if ((g_ram.pl2_input_lock_flag == 0 || BIT_IS_SET(g_ram.pl2_input_lock_flag, 7)) && g_ram.vs_flag == 0) {
      foxcpu(p_playerwk);
    }
  }
  if (BIT_IS_SET(p_playerwk->u.play.control_bitfield, 0)) {
    p_playerwk->u.play.talent_status = 0;
    if (g_ram.miles_carry_flag != 0) {
      g_ram.actwk[0].u.play.control_bitfield = 0;
      g_ram.actwk[0].u.play.cddat.jump = 1;
      g_ram.miles_carry_flag = 0;
    }
  }
  else {
    unsigned char index = p_playerwk->u.play.cddat.jump + p_playerwk->u.play.cddat.ball * 2;
    fox00_move_tbl[index](p_playerwk, work);
  }
  if (g_ram.scralim_up == -256) {
    short yposi = (unsigned short)fp16_get_integer(p_playerwk->yposi) & g_ram.scrc_v;
    fp16_set_integer(&p_playerwk->yposi, yposi);
  }
  foxpowercnt(p_playerwk, work);
  foxsupercnt(p_playerwk, work);
  playposiwkset(p_playerwk);
  foxwaterchk(p_playerwk, work);
  p_playerwk->u.play.angle_front = g_ram.dirstk[0];
  p_playerwk->u.play.angle_below = g_ram.dirstk[2];
  if (g_ram.watercoliflag2 != 0 && p_playerwk->mstno == 0) {
    p_playerwk->mstno = p_playerwk->mstrestart;
  }
  if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 1)) {
    foxpatchgmain(p_playerwk);
    if (g_ram.reverse_gravity_flag != 0) {
      p_playerwk->actflg.vflip ^= 1;
    }
    foxwrt(p_playerwk);
  }
  if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 5)
      && !BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) {
    pcol(p_playerwk);
  }
}


static void foxpowercnt(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  bool show = true;
  if (p_playerwk->u.play.invulnerability_timer != 0) {
    show = p_playerwk->u.play.invulnerability_timer & 4;
    --p_playerwk->u.play.invulnerability_timer;
  }
  if (show) {
    actionsub(p_playerwk);
  }
  if (p_playerwk->u.play.powerdat.muteki == 1 && p_playerwk->u.play.muteki_timer != 0 && !(g_ram.gametimer & 7)) {
    --p_playerwk->u.play.muteki_timer;
    if (p_playerwk->u.play.muteki_timer == 0) {
      if (g_ram.bossstart == 0 && p_playerwk->u.play.air_timer >= 12) {
        bgmset(g_ram.bgm_act);
      }
      p_playerwk->u.play.powerdat.muteki = 0;
    }
  }
  if (p_playerwk->u.play.powerdat.speedup == 1 && p_playerwk->u.play.speedup_timer != 0 && !(g_ram.gametimer & 7)) {
    --p_playerwk->u.play.speedup_timer;
    if (p_playerwk->u.play.speedup_timer == 0) {
      if (g_ram.vs_flag == 0) {
        *work.plmaxspdwk_ptr = g_ram.smilesflag == 0 ? 0x600 : 0x800;
        *work.pladdspdwk_ptr = g_ram.smilesflag == 0 ? 0xC : 0x18;
        *work.plretspdwk_ptr = g_ram.smilesflag == 0 ? 0x80 : 0xC0;
        p_playerwk->u.play.powerdat.speedup = 0;
        Change_Music_Tempo(0);
      }
      else {
        *work.plmaxspdwk_ptr = vsplaydata[p_playerwk->u.play.character][0];
        *work.pladdspdwk_ptr = vsplaydata[p_playerwk->u.play.character][1];
        *work.plretspdwk_ptr = vsplaydata[p_playerwk->u.play.character][2];
        p_playerwk->u.play.powerdat.speedup = 0;
      }
    }
  }
}


void foxcpu(SKC_sprite_status* p_actwk) {
  void(*foxcpu_move_tbl[18])(SKC_sprite_status*, SKC_sprite_status*) = {
    &foxcpu_init,
    &foxcpu_wait0,
    &foxcpu_appear,
    &foxcpu_move,
    &foxcpu_wait1,
    &foxcpu_worknai,
    &foxcpu_drop_off_init,
    &foxcpu_drop_off,
    &foxcpu_fly_up0,
    &foxcpu_wait2,
    &foxcpu_carry_up_init,
    &foxcpu_carry_up,
    &foxcpu_carry_move,
    &foxcpu_fly_up1_init,
    &foxcpu_fly_up1,
    &foxcpu_fly,
    &foxcpu_land_init,
    &foxcpu_land
  };

  if (are_any_dir_buttons_used(g_ram.swdata.down) || are_any_trg_buttons_used(g_ram.swdata.down)) {
    g_ram.foxcpu_timer = 600;
  }
  foxcpu_move_tbl[g_ram.foxcpu_rno / 2](p_actwk, &g_ram.actwk[0]);
}


static void foxcpu_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (g_ram.markno_s == 0) {
    switch (g_ram.stageno) {
      case ANGEL_ISLAND_ACT_1:
      case ICECAP_ACT_1:
      case SKY_SANCTUARY_ACT_SONIC:
      case LAVA_REEF_BOSS:
        foxcpu_wait0_init(p_playerwk);
        g_ram.foxcpu_rno = 10;
        p_playerwk->u.play.control_bitfield = 0x83;
        break;
      default:
        p_playerwk->mstno = 0;
        p_playerwk->xspeed = 0;
        p_playerwk->yspeed = 0;
        p_playerwk->mspeed = 0;
        memset(&p_playerwk->u.play.cddat, 0, sizeof(p_playerwk->u.play.cddat));
        // fall-through
      case HYDROCITY_ACT_1:
      case MARBLE_GARDEN_ACT_1:
      case LAUNCH_BASE_ACT_1:
      case LAVA_REEF_ACT_1:
        p_playerwk->u.play.control_bitfield = 0;
        // fall-through
      case SANDOPOLIS_ACT_1:
      case DEATH_EGG_BOSS:
      case MASTER_EMERALD_SHRINE:
        g_ram.foxcpu_rno = 6;
        g_ram.fox_appear_timer = 0;
        break;
      case CARNIVAL_NIGHT_ACT_1:
        fp16_set_integer(&p_playerwk->xposi, 24);
        fp16_set_integer(&p_playerwk->yposi, 0x600);
        g_ram.foxcpu_timer = 0;
        g_ram.fox_appear_timer = 0;
        memset(&p_playerwk->u.play.cddat, 0, sizeof(p_playerwk->u.play.cddat));
        p_playerwk->u.play.cddat.jump = 1;
        g_ram.foxcpu_rno = 12;
        break;
      case MUSHROOM_HILL_ACT_1:
        if (g_ram.cartridge == 0) {
          fp16_set_integer(&p_playerwk->xposi, 216);
          fp16_set_integer(&p_playerwk->yposi, 0x500);
          g_ram.foxcpu_timer = 0;
          g_ram.fox_appear_timer = 0;
          p_playerwk->u.play.cddat.jump = 1;
          g_ram.foxcpu_rno = 12;
        }
        break;
    }
  }
  else {
    p_playerwk->mstno = 0;
    p_playerwk->xspeed = 0;
    p_playerwk->yspeed = 0;
    p_playerwk->mspeed = 0;
    memset(&p_playerwk->u.play.cddat, 0, sizeof(p_playerwk->u.play.cddat));
    p_playerwk->u.play.control_bitfield = 0;
    g_ram.foxcpu_rno = 6;
    g_ram.fox_appear_timer = 0;
  }
}


static void foxcpu_wait0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  bool controllable = !(g_ram.gametimer & 0x3F)
                      && !BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)
                      && p_playerwk->u.play.cddat.unused7 == 0;
  if (are_any_face_buttons_used(g_ram.swdata0.down) || controllable) {
    g_ram.foxcpu_rno = 4;
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
    g_ram.foxcpu_movexposi = fp16_get_integer(p_playerwk->xposi);
    g_ram.foxcpu_moveyposi = fp16_get_integer(p_playerwk->yposi);
    short yposi = fp16_get_integer(p_playerwk->yposi) - 192;
    if (g_ram.reverse_gravity_flag != 0) {
      yposi += 384;
    }
    fp16_set_integer(&p_actwk->yposi, yposi);
    SET_BIT(p_actwk->sproffset, 15);
    p_actwk->sprpri = PRI_2;
    p_actwk->xspeed = 0;
    p_actwk->yspeed = 0;
    p_actwk->mspeed = 0;
    p_actwk->u.play.flip_mst.type = 0;
    p_actwk->u.play.flip_mst.reverse = 0;
    p_actwk->u.play.talent_status = 0;
    memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
    p_actwk->u.play.cddat.jump = 1;
    p_actwk->u.play.air_timer = 30;
    p_actwk->u.play.control_bitfield = 0x81;
    p_actwk->u.play.flip_rev_cnt = 0;
    p_actwk->u.play.flip_rev_frame_cnt = 0;
    p_actwk->u.play.hlock_timer = 0;
    p_actwk->u.play.invulnerability_timer = 0;
    p_actwk->u.play.muteki_timer = 0;
    p_actwk->u.play.speedup_timer = 0;
    p_actwk->u.play.eventflag = 0;
    p_actwk->u.play.lever_ctr = 0;
    p_actwk->u.play.angle_front = 0;
    p_actwk->u.play.angle_below = 0;
    p_actwk->u.play.convex_flag = 0;
    p_actwk->u.play.spindash_flag = 0;
    p_actwk->u.play.spindash_ctr = 0;
    p_actwk->u.play.jump_flag = 0;
    p_actwk->u.play.force_direc_up_timer = 0;
    p_actwk->pattim = 240;
    setflyswim(p_actwk);
  }
}


static void foxcpu_appear(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_actwk->actflg.onscreen == 0) {
    ++g_ram.fox_appear_timer;
    if (g_ram.fox_appear_timer >= 300) {
      g_ram.fox_appear_timer = 0;
      g_ram.foxcpu_rno = 2;
      p_actwk->u.play.control_bitfield = 0x81;
      memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
      p_actwk->u.play.cddat.jump = 1;
      fp16_set_integer(&p_actwk->xposi, 0);
      fp16_set_integer(&p_actwk->yposi, 0);
      p_actwk->pattimm = 240;
      setflyswim(p_actwk);
      return;
    }
  }
  else {
    p_actwk->pattimm = 240;
    p_actwk->u.play.cddat.jump = 1;
    setflyswim(p_actwk);
    g_ram.fox_appear_timer = 0;
  }
  g_ram.foxcpu_movexposi = g_ram.playposiwk[g_ram.plposiwkadr - 17].x;
  g_ram.foxcpu_moveyposi = g_ram.playposiwk[g_ram.plposiwkadr - 17].y;
  short xdistance = fp16_get_integer(p_actwk->xposi) - g_ram.foxcpu_movexposi;
  if (xdistance != 0) {
    short xoffset = abs(xdistance) / 16;
    if (xoffset >= 12) {
      xoffset = 12;
    }
    xoffset += fp8_get_integer(p_actwk->xspeed) + 1;
    if (xdistance >= 0) {
      p_actwk->u.play.cddat.left = 1;
      if ((unsigned short)xoffset >= (unsigned short)xdistance) {
        xoffset = xdistance;
        xdistance = 0;
      }
      xoffset = -xoffset;
    }
    else {
      p_actwk->u.play.cddat.left = 0;
      xdistance = -xdistance;
      if ((unsigned short)xoffset >= (unsigned short)xdistance) {
        xoffset = xdistance;
        xdistance = 0;
      }
    }
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
  }
  short ydistance = fp16_get_integer(p_actwk->yposi) - g_ram.foxcpu_moveyposi;
  if (ydistance != 0) {
    short yoffset = abs(ydistance);
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  }
  if (g_ram.playrecwk[g_ram.plposiwkadr - 17].cddat.unused7 == 0
      && xdistance == 0
      && ydistance == 0
      && g_ram.actwk[0].r_no < 6) {
    g_ram.foxcpu_rno = 6;
    p_actwk->u.play.control_bitfield = 0;
    p_actwk->mstno = 0;
    p_actwk->xspeed = 0;
    p_actwk->yspeed = 0;
    p_actwk->mspeed = 0;
    p_actwk->u.play.cddat.left = 0;
    p_actwk->u.play.cddat.jump = 1;
    p_actwk->u.play.cddat.ball = 0;
    p_actwk->u.play.cddat.ride = 0;
    p_actwk->u.play.cddat.ballj = 0;
    p_actwk->u.play.cddat.push = 0;
    p_actwk->u.play.cddat.unused7 = 0;
    p_actwk->u.play.hlock_timer = 0;
    CLEAR_BIT(p_actwk->sproffset, 15);
    if (BIT_IS_SET(p_playerwk->sproffset, 15)) {
      SET_BIT(p_actwk->sproffset, 15);
    }
    p_actwk->u.play.top_solid_bit = p_playerwk->u.play.top_solid_bit;
    p_actwk->u.play.lrb_solid_bit = p_playerwk->u.play.lrb_solid_bit;
  }
  else {
    p_actwk->u.play.control_bitfield = 0x81;
  }
}


static void foxcpu_move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (g_ram.actwk[0].r_no >= 6) {
    g_ram.foxcpu_rno = 4;
    p_actwk->u.play.spindash_flag = 0;
    p_actwk->u.play.spindash_ctr = 0;
    p_actwk->u.play.control_bitfield = 0x81;
    memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
    p_actwk->u.play.cddat.jump = 1;
    p_actwk->mstno = 32;
  }
  else {
    foxcpu_ridechk(p_actwk, p_playerwk);
    if (g_ram.foxcpu_timer == 0
        && !BIT_IS_SET(p_actwk->u.play.control_bitfield, 7)
        && !BIT_IS_SET(p_playerwk->u.play.eventflag, 7)) {
      if (p_actwk->u.play.hlock_timer != 0 && p_actwk->mspeed == 0) {
        g_ram.foxcpu_rno = 8;
      }
      SKC_swdata swdata = g_ram.playrecwk[g_ram.plposiwkadr - 17].swdata;
      if (p_actwk->u.play.cddat.push == 0 || g_ram.playrecwk[g_ram.plposiwkadr - 17].cddat.push == 1) {
        short xposi = g_ram.playposiwk[g_ram.plposiwkadr - 17].x;
        if (p_playerwk->u.play.cddat.ride == 0 && p_playerwk->mspeed < 0x400) {
          xposi -= 32;
        }
        short xdistance = xposi - fp16_get_integer(p_actwk->xposi);
        if (xdistance != 0) {
          if (xdistance < 0) {
            xdistance = -xdistance;
            if (xdistance >= 48) {
              swdata.down.l = 1;
              swdata.down.r = 0;
              swdata.pressed.l = 1;
              swdata.pressed.r = 0;
            }
            if (p_actwk->mspeed != 0
                && p_actwk->u.play.cddat.left == 1
                && !BIT_IS_SET(p_actwk->u.play.control_bitfield, 0)) {
              fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 1);
            }
          }
          else {
            if (xdistance >= 48) {
              swdata.down.l = 0;
              swdata.down.r = 1;
              swdata.pressed.l = 0;
              swdata.pressed.r = 1;
            }
            if (p_actwk->mspeed != 0
                && p_actwk->u.play.cddat.left == 0
                && !BIT_IS_SET(p_actwk->u.play.control_bitfield, 0)) {
              fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 1);
            }
          }
        }
        else {
          p_actwk->u.play.cddat.left = g_ram.playrecwk[g_ram.plposiwkadr - 17].cddat.left;
        }
        if (g_ram.DAT_08fff70f != 0) {
          swdata.down.a = 1;
          swdata.down.b = 1;
          swdata.down.c = 1;
          if (p_actwk->u.play.cddat.jump == 0) {
            g_ram.DAT_08fff70f = 0;
          }
        }
        if (g_ram.DAT_08fff70f == 0 || p_actwk->u.play.cddat.jump == 0) {
          if (!(g_ram.gametimer & 0xFF) || xdistance < 64) {
            short ydistance = g_ram.playposiwk[g_ram.plposiwkadr - 17].y - fp16_get_integer(p_actwk->yposi);
            if (ydistance < 0) {
              ydistance = -ydistance;
              if (ydistance >= 32 && !(g_ram.gametimer & 0x3F) && p_actwk->mstno != 8) {
                swdata.down.a = 1;
                swdata.down.b = 1;
                swdata.down.c = 1;
                swdata.pressed.a = 1;
                swdata.pressed.b = 1;
                swdata.pressed.c = 1;
                g_ram.DAT_08fff70f = 1;
              }
            }
          }
        }
      }
      else if (!(g_ram.gametimer & 0x3F) && p_actwk->mstno != 8) {
        swdata.down.a = 1;
        swdata.down.b = 1;
        swdata.down.c = 1;
        swdata.pressed.a = 1;
        swdata.pressed.b = 1;
        swdata.pressed.c = 1;
        g_ram.DAT_08fff70f = 1;
      }
      g_ram.swdata0 = swdata;
    }
    else if (g_ram.foxcpu_timer != 0) {
      --g_ram.foxcpu_timer;
    }
  }
}


void foxcpu_wait0_init(SKC_sprite_status* p_actwk) {
  g_ram.foxcpu_timer = 0;
  g_ram.fox_appear_timer = 0;
  g_ram.foxcpu_rno = 2;
  p_actwk->u.play.control_bitfield = 0x81;
  memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
  p_actwk->u.play.cddat.jump = 1;
  fp16_set_integer(&p_actwk->xposi, 0x7F00);
  fp16_set_integer(&p_actwk->yposi, 0);
  p_actwk->u.play.talent_status = 1;
}


static void foxcpu_ridechk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_actwk->actflg.onscreen == 0) {
    if (p_actwk->u.play.cddat.ride == 1 && g_ram.foxcpu_ride_obj != p_playerwk->u.play.ride_obj) {
      foxcpu_wait0_init(p_actwk);
      return;
    }
    ++g_ram.fox_appear_timer;
    if (g_ram.fox_appear_timer >= 300) {
      foxcpu_wait0_init(p_actwk);
      return;
    }
  }
  else {
    g_ram.fox_appear_timer = 0;
  }
  if (p_actwk->u.play.cddat.ride == 1) {
    g_ram.foxcpu_ride_obj == p_playerwk->u.play.ride_obj;
  }
}


static void foxcpu_wait1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  foxcpu_ridechk(p_actwk, p_playerwk);
  if (g_ram.foxcpu_timer == 0 && p_actwk->u.play.hlock_timer == 0) {
    if (p_actwk->u.play.spindash_flag == 0) {
      if (p_actwk->mspeed == 0) {
        short distance = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_playerwk->xposi);
        p_actwk->u.play.cddat.left = distance >= 0;
        memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
        g_ram.swdata0.down.d = 1;
        g_ram.swdata0.pressed.d = 1;
        if (!(g_ram.gametimer & 0x7F)) {
          memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
          g_ram.foxcpu_rno = 6;
        }
        else if (p_actwk->mstno == 8) {
          g_ram.swdata0.down.a = 1;
          g_ram.swdata0.down.b = 1;
          g_ram.swdata0.down.c = 1;
          g_ram.swdata0.pressed.a = 1;
          g_ram.swdata0.pressed.b = 1;
          g_ram.swdata0.pressed.c = 1;
        }
      }
    }
    else {
      memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
      g_ram.swdata0.down.d = 1;
      g_ram.swdata0.pressed.d = 1;
      if (!(g_ram.gametimer & 0x7F)) {
        memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
        g_ram.foxcpu_rno = 6;
      }
      else if (!(g_ram.gametimer & 0x1F)) {
        g_ram.swdata0.down.a = 1;
        g_ram.swdata0.down.b = 1;
        g_ram.swdata0.down.c = 1;
        g_ram.swdata0.pressed.a = 1;
        g_ram.swdata0.pressed.b = 1;
        g_ram.swdata0.pressed.c = 1;
      }
    }
  }
}


static void foxcpu_worknai(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
}


static void foxcpu_drop_off_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->u.play.talent_status = 1;
  p_actwk->pattimm = 240;
  memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
  p_actwk->u.play.cddat.jump = 1;
  p_actwk->xspeed = 0x100;
  p_actwk->yspeed = 0;
  p_actwk->mspeed = 0;
  foxgrab(p_actwk, p_playerwk);
  g_ram.miles_carry_flag = 1;
  g_ram.foxcpu_rno = 14;
  foxcpu_drop_off(p_actwk, p_playerwk);
}


static void foxcpu_drop_off(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  g_ram.foxcpu_timer = 0;
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  if (!(g_ram.gametimer & 0x1F)) {
    g_ram.swdata0.down.r = 1;
    g_ram.swdata0.pressed.r = 1;
  }
  if (p_playerwk->u.play.cddat.jump == 0) {
    g_ram.foxcpu_rno = 6;
    p_actwk->u.play.control_bitfield = 0;
    p_actwk->mstno = 0;
    p_actwk->xspeed = 0;
    p_actwk->yspeed = 0;
    p_actwk->mspeed = 0;
    memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
    p_actwk->u.play.cddat.jump = 1;
    p_actwk->u.play.hlock_timer = 0;
    CLEAR_BIT(p_actwk->sproffset, 15);
    if (BIT_IS_SET(p_playerwk->sproffset, 15)) {
      SET_BIT(p_actwk->sproffset, 15);
    }
    p_actwk->u.play.top_solid_bit = p_playerwk->u.play.top_solid_bit;
    p_actwk->u.play.lrb_solid_bit = p_playerwk->u.play.lrb_solid_bit;
    if (g_ram.play_type == PLAY_TYPE_SONIC) {
      g_ram.foxcpu_rno = 16;
    }
  }
  foxcarrychk(p_actwk, p_playerwk);
}


static void foxcpu_fly_up0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  g_ram.foxcpu_timer = 0;
  p_actwk->pattimm = 240;
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  if (!(g_ram.gametimer & 0xF)) {
    g_ram.swdata0.down.r = 1;
    g_ram.swdata0.down.a = 1;
    g_ram.swdata0.down.b = 1;
    g_ram.swdata0.down.c = 1;
    g_ram.swdata0.pressed.r = 1;
    g_ram.swdata0.pressed.a = 1;
    g_ram.swdata0.pressed.b = 1;
    g_ram.swdata0.pressed.c = 1;
  }
  if (p_actwk->actflg.onscreen == 0) {
    p_actwk->r_ptr = 0;
    fp16_set_integer(&p_actwk->xposi, 0);
    fp16_set_integer(&p_actwk->yposi, 0);
    g_ram.foxcpu_rno = 10;
  }
}


static void foxcpu_wait2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
}


static void foxcpu_carry_up_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->u.play.talent_status = 1;
  p_actwk->pattimm = 240;
  memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
  p_actwk->u.play.cddat.jump = 1;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->mspeed = 0;
  foxgrab(p_actwk, p_playerwk);
  g_ram.miles_carry_flag = 1;
  g_ram.foxcpu_rno = 22;
  foxcpu_carry_up(p_actwk, p_playerwk);
}


static void foxcpu_carry_up(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  g_ram.foxcpu_timer = 0;
  p_actwk->pattimm = 240;
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  if (!(g_ram.gametimer & 7)) {
    g_ram.swdata0.down.a = 1;
    g_ram.swdata0.down.b = 1;
    g_ram.swdata0.down.c = 1;
    g_ram.swdata0.pressed.a = 1;
    g_ram.swdata0.pressed.b = 1;
    g_ram.swdata0.pressed.c = 1;
  }
  if ((g_ram.scra_v_posit >> 16) + 144 >= fp16_get_integer(p_actwk->yposi)) {
    g_ram.foxcpu_rno = 24;
  }
  foxcarrychk(p_actwk, p_playerwk);
}


static void foxcpu_carry_move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->pattimm = 240;
  if (g_ram.foxcpu_timer == 0) {
    memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  }
  if (g_ram.miles_carry_flag == 0) {
    FUN_0043d682(p_actwk, p_playerwk);
  }
  else {
    if (g_ram.foxcpu_timer == 0) {
      g_ram.DAT_08fffaac = 0;
      if (g_ram.swdata1.down.d == 1) {
        ++g_ram.DAT_08fff70e;
        if (g_ram.DAT_08fff70e >= 192) {
          g_ram.DAT_08fff70e = 0;
          g_ram.swdata0.down.a = 1;
          g_ram.swdata0.down.b = 1;
          g_ram.swdata0.down.c = 1;
          g_ram.swdata0.pressed.a = 1;
          g_ram.swdata0.pressed.b = 1;
          g_ram.swdata0.pressed.c = 1;
        }
      }
      else if (g_ram.swdata1.down.u == 1) {
        ++g_ram.DAT_08fff70e;
        if (g_ram.DAT_08fff70e >= 32) {
          g_ram.DAT_08fff70e = 0;
          g_ram.swdata0.down.a = 1;
          g_ram.swdata0.down.b = 1;
          g_ram.swdata0.down.c = 1;
          g_ram.swdata0.pressed.a = 1;
          g_ram.swdata0.pressed.b = 1;
          g_ram.swdata0.pressed.c = 1;
        }
      }
      else {
        ++g_ram.DAT_08fff70e;
        if (g_ram.DAT_08fff70e >= 88) {
          g_ram.DAT_08fff70e = 0;
          g_ram.swdata0.down.a = 1;
          g_ram.swdata0.down.b = 1;
          g_ram.swdata0.down.c = 1;
          g_ram.swdata0.pressed.a = 1;
          g_ram.swdata0.pressed.b = 1;
          g_ram.swdata0.pressed.c = 1;
        }
      }
      g_ram.swdata0.down.l = g_ram.swdata1.down.l;
      g_ram.swdata0.down.r = g_ram.swdata1.down.r;
    }
    foxcarrychk(p_actwk, p_playerwk);
  }
}


static void foxcpu_fly_up1_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->u.play.talent_status = 1;
  p_actwk->pattimm = 240;
  memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
  p_actwk->u.play.cddat.jump = 1;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->mspeed = 0;
  g_ram.foxcpu_rno = 28;
  foxcpu_fly_up1(p_actwk, p_playerwk);
}


static void foxcpu_fly_up1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  g_ram.foxcpu_timer = 0;
  p_actwk->pattimm = 240;
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  if (!(g_ram.gametimer & 7)) {
    g_ram.swdata0.down.a = 1;
    g_ram.swdata0.down.b = 1;
    g_ram.swdata0.down.c = 1;
    g_ram.swdata0.pressed.a = 1;
    g_ram.swdata0.pressed.b = 1;
    g_ram.swdata0.pressed.c = 1;
  }
  if ((g_ram.scra_v_posit >> 16) + 144 >= fp16_get_integer(p_actwk->yposi)) {
    g_ram.foxcpu_rno = 30;
  }
}


static void foxcpu_fly(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->pattimm = 240;
}


static void foxcpu_land_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->u.play.talent_status = 1;
  p_actwk->pattimm = 240;
  memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
  p_actwk->u.play.cddat.jump = 1;
  p_actwk->xspeed = 0x100;
  p_actwk->yspeed = 0;
  p_actwk->mspeed = 0;
  g_ram.foxcpu_rno = 34;
  foxcpu_land(p_actwk, p_playerwk);
}


static void foxcpu_land(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  g_ram.foxcpu_timer = 0;
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  if (!(g_ram.gametimer & 0x1F)) {
    g_ram.swdata0.down.r = 1;
    g_ram.swdata0.pressed.r = 1;
  }
  if (p_actwk->u.play.cddat.jump == 0) {
    g_ram.foxcpu_rno = 6;
    p_actwk->u.play.control_bitfield = 0;
    p_actwk->mstno = 0;
    p_actwk->xspeed = 0;
    p_actwk->yspeed = 0;
    p_actwk->mspeed = 0;
    memset(&p_actwk->u.play.cddat, 0, sizeof(p_actwk->u.play.cddat));
    p_actwk->u.play.cddat.jump = 1;
    p_actwk->u.play.hlock_timer = 0;
    CLEAR_BIT(p_actwk->sproffset, 15);
  }
}


static void FUN_0043d682(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (g_ram.DAT_08fffaac == 0) {
    if (p_playerwk->actflg.onscreen == 1 && g_ram.foxcpu_timer == 0 && p_playerwk->yspeed < 0x300) {
      p_actwk->xspeed = 0;
      memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
      if (p_playerwk->yspeed < 0x200) {
        ++g_ram.DAT_08fff70e;
        if (g_ram.DAT_08fff70e >= 88) {
          g_ram.DAT_08fff70e = 0;
          g_ram.swdata0.down.a = 1;
          g_ram.swdata0.down.b = 1;
          g_ram.swdata0.down.c = 1;
          g_ram.swdata0.pressed.a = 1;
          g_ram.swdata0.pressed.b = 1;
          g_ram.swdata0.pressed.c = 1;
        }
      }
      else {
        g_ram.swdata0.down.a = 1;
        g_ram.swdata0.down.b = 1;
        g_ram.swdata0.down.c = 1;
        g_ram.swdata0.pressed.a = 1;
        g_ram.swdata0.pressed.b = 1;
        g_ram.swdata0.pressed.c = 1;
      }
    }
    else if (p_playerwk->actflg.onscreen == 0 || (g_ram.foxcpu_timer == 0 && p_playerwk->yspeed >= 0x300)) {
      g_ram.DAT_08fffaac = 255;
      short distance = abs(fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi));
      g_ram.scralim_m_left = distance / 4 + distance / 8;
      distance = abs(fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi));
      g_ram.scralim_m_right = distance / 4;
    }
  }
  else {
    memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
    short scralim = g_ram.scralim_m_right;
    p_actwk->u.play.cddat.left = 0;
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      p_actwk->u.play.cddat.left = 1;
      scralim = -scralim;
    }
    p_actwk->xspeed += scralim;
    short yposi = fp16_get_integer(p_actwk->yposi) - 16;
    if ((unsigned short)yposi < (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
      scralim = g_ram.scralim_m_left;
      if ((unsigned short)yposi >= (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
        scralim = -scralim;
      }
      p_actwk->yspeed += scralim;
    }
  }
  foxcarrychk(p_actwk, p_playerwk);
}


static void foxcarrychk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  unsigned char patno_tbl[17] = {
    145, 145, 144, 144, 144, 144, 144, 144, 146, 146, 146, 146, 146, 146, 145, 145, 255
  };

  if (g_ram.miles_carry_flag != 0) {
    if (p_playerwk->r_no < 4) {
      if (p_playerwk->u.play.cddat.jump == 1 && g_ram.foxxspeed == p_playerwk->xspeed) {
        if (g_ram.foxyspeed == p_playerwk->yspeed) {
          if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) {
            if (are_any_trg_buttons_used(g_ram.swdata1.pressed)) {
              p_playerwk->u.play.control_bitfield = 0;
              g_ram.miles_carry_flag = 0;
              g_ram.miles_nograb_timer = !are_any_dir_buttons_used(g_ram.swdata1.down) ? 18 : 60;
              if (g_ram.swdata1.down.l == 1) {
                p_playerwk->xspeed = -0x200;
              }
              if (g_ram.swdata1.down.r == 1) {
                p_playerwk->xspeed = 0x200;
              }
              p_playerwk->yspeed = -0x380;
              p_playerwk->u.play.cddat.jump = 1;
              p_playerwk->u.play.jump_flag = 1;
              p_playerwk->sprvsize = 14;
              p_playerwk->sprhsize = 7;
              p_playerwk->mstno = 2;
              p_playerwk->u.play.cddat.ball = 1;
              p_playerwk->u.play.cddat.ballj = 0;
            }
            else {
              fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_actwk->xposi));
              fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi));
              fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 28);
              if (g_ram.reverse_gravity_flag != 0) {
                fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 56);
              }
              p_playerwk->actflg.hflip = p_actwk->u.play.cddat.left;
              p_playerwk->actflg.vflip = g_ram.reverse_gravity_flag;
              p_playerwk->u.play.cddat.left = p_actwk->u.play.cddat.left;
              if (p_playerwk->pattim-- == 0) {
                p_playerwk->pattim = 11;
                unsigned char patcnt = p_playerwk->patcnt;
                ++p_playerwk->patcnt;
                unsigned char patno = patno_tbl[patcnt];
                if (patno == 255) {
                  p_playerwk->patcnt = 0;
                  patno = patno_tbl[0];
                }
                p_playerwk->patno = patno;
                playwrt1(p_playerwk, p_playerwk->patno);
              }
              g_ram.actwk[0].xspeed = p_actwk->xspeed;
              g_ram.foxxspeed = p_actwk->xspeed;
              g_ram.actwk[0].yspeed = p_actwk->yspeed;
              g_ram.foxyspeed = p_actwk->yspeed;
              jumpcolchk(p_playerwk);
            }
          }
          else {
            g_ram.miles_carry_flag = 0;
            g_ram.miles_nograb_timer = 60;
          }
        }
        else {
          p_playerwk->u.play.jump_flag = 0;
          p_playerwk->u.play.control_bitfield = 0;
          g_ram.miles_carry_flag = 0;
          g_ram.miles_nograb_timer = 60;
        }
      }
      else {
        p_playerwk->yspeed = -0x100;
        p_playerwk->u.play.jump_flag = 0;
        p_playerwk->u.play.control_bitfield = 0;
        g_ram.miles_carry_flag = 0;
        g_ram.miles_nograb_timer = 60;
      }
    }
    else {
      p_playerwk->u.play.control_bitfield = 0;
      g_ram.miles_carry_flag = 0;
      g_ram.miles_nograb_timer = 60;
    }
  }
  else {
    if (g_ram.miles_nograb_timer != 0) {
      --g_ram.miles_nograb_timer;
    }
    if (g_ram.miles_nograb_timer == 0) {
      short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + 16;
      if ((unsigned short)distance < 32) {
        distance = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi) - 32;
        if (g_ram.reverse_gravity_flag != 0) {
          distance += 80;
        }
        if (distance < 16
            && p_playerwk->u.play.control_bitfield == 0
            && p_playerwk->r_no < 4
            && g_ram.editmode == 0
            && p_playerwk->u.play.spindash_flag == 0) {
          foxgrab(p_actwk, p_playerwk);
          soundset(74);
          g_ram.miles_carry_flag = 1;
        }
      }
    }
  }
}


static void foxgrab(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->xspeed = 0;
  p_playerwk->yspeed = 0;
  p_playerwk->mspeed = 0;
  p_playerwk->direc.b.b0 = 0;
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_actwk->xposi));
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi));
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 28);
  p_playerwk->mstno = 34;
  p_playerwk->mstrestart = 0;
  p_playerwk->pattim = 0;
  p_playerwk->patcnt = 0;
  p_playerwk->u.play.control_bitfield = 3;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ballj = 0;
  p_playerwk->u.play.spindash_flag = 0;
  p_playerwk->actflg.hflip = p_actwk->u.play.cddat.left;
  p_playerwk->u.play.cddat.left = p_actwk->u.play.cddat.left;
  g_ram.foxxspeed = p_actwk->xspeed;
  p_playerwk->xspeed = p_actwk->xspeed;
  g_ram.foxyspeed = p_actwk->yspeed;
  p_playerwk->yspeed = p_actwk->yspeed;
  if (g_ram.reverse_gravity_flag != 0) {
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 56);
  }
  p_playerwk->actflg.vflip = g_ram.reverse_gravity_flag;
}


static void foxwaterchk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.watermode == 0) return;

  if (g_ram.waterposi < fp16_get_integer(p_playerwk->yposi)) {
    if (p_playerwk->u.play.cddat.underwater == 0) {
      p_playerwk->u.play.cddat.underwater = 1;
      ++g_ram.water_flag;
      plairset(p_playerwk);
      g_ram.actwk[ACTWK_PL2_AWA].r_ptr = &plawa;
      g_ram.actwk[ACTWK_PL2_AWA].u.obj.userflag = 129;
      g_ram.actwk[ACTWK_PL2_AWA].u.obj.ko = p_playerwk - g_ram.actwk;
      *work.plmaxspdwk_ptr = g_ram.smilesflag == 0 ? 0x300 : 0x400;
      *work.pladdspdwk_ptr = g_ram.smilesflag == 0 ? 6 : 0xC;
      *work.plretspdwk_ptr = g_ram.smilesflag == 0 ? 0x40 : 0x60;
      if (g_ram.foxcpu_rno == 4 && p_playerwk->u.play.control_bitfield == 0) {
        p_playerwk->xspeed /= 2;
        p_playerwk->yspeed /= 4;
        if (p_playerwk->yspeed != 0) {
          work.effectwk_ptr->mstno = 1;
          work.effectwk_ptr->mstrestart = 0;
          soundset(57);
        }
      }
    }
  }
  else {
    if (p_playerwk->u.play.cddat.underwater != 0) {
      p_playerwk->u.play.cddat.underwater = 0;
      ++g_ram.water_flag;
      plairset(p_playerwk);
      *work.plmaxspdwk_ptr = g_ram.smilesflag == 0 ? 0x600 : 0x800;
      *work.pladdspdwk_ptr = g_ram.smilesflag == 0 ? 0xC : 0x18;
      *work.plretspdwk_ptr = g_ram.smilesflag == 0 ? 0x80 : 0xC0;
      if ((p_playerwk->r_no == 4 || g_ram.foxcpu_rno == 4 || p_playerwk->u.play.control_bitfield == 0)
          && p_playerwk->yspeed >= -0x400) {
        p_playerwk->yspeed *= 2;
      }
      if (p_playerwk->mstno != 28 && p_playerwk->yspeed != 0) {
        work.effectwk_ptr->mstno = 1;
        work.effectwk_ptr->mstrestart = 0;
        if (p_playerwk->yspeed <= -0x1000) {
          p_playerwk->yspeed = -0x1000;
        }
        soundset(57);
      }
    }
  }
}


static void fox00walk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.miles_carry_flag != 0) {
    g_ram.actwk[0].u.play.control_bitfield = 0;
    g_ram.actwk[0].u.play.cddat.jump = 1;
    g_ram.miles_carry_flag = 0;
  }
  if (!foxspinchk(p_playerwk, work) && !foxjumpchk(p_playerwk)) {
    keispd(p_playerwk);
    foxlevermove(p_playerwk, work);
    foxballchk(p_playerwk);
    foxlimitchk(p_playerwk);
    speedset2_g(p_playerwk);
    fcol_g(p_playerwk);
    fallchk(p_playerwk);
    if (g_ram.scd_bg_flag != 0) {
      SKC_dircol_result result = crushchk_d(p_playerwk);
      if (result.offset < 0) {
        playdieset(p_playerwk);
      }
      else {
        result = dircol_l2(p_playerwk);
        if (result.offset < 0) {
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        }
        result = dircol_r2(p_playerwk);
        if (result.offset < 0) {
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        }
      }
    }
  }
}


static void fox00jump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.talent_status == 0) {
    foxjumpchk2(p_playerwk, work);
    foxjumpmove(p_playerwk, work);
    foxlimitchk(p_playerwk);
    speedset_g(p_playerwk);
    if (p_playerwk->u.play.cddat.underwater == 1) {
      p_playerwk->yspeed -= 0x28;
    }
    direcchg(p_playerwk);
    foxjumpcolchk(p_playerwk);
  }
  else {
    flyswimchk(p_playerwk);
    foxjumpmove(p_playerwk, work);
    foxlimitchk(p_playerwk);
    speedset2_g(p_playerwk);
    direcchg(p_playerwk);
    foxjumpcolchk(p_playerwk);
    if (g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES) {
      foxcarrychk(p_playerwk, &g_ram.actwk[0]);
    }
  }
}


static void flyswimchk(SKC_sprite_status* p_playerwk) {
  if (g_ram.gametimer & 1 && p_playerwk->pattimm != 0) {
    --p_playerwk->pattimm;
  }
  if (p_playerwk->u.play.talent_status != 1) {
    if (p_playerwk->yspeed >= -0x100) {
      p_playerwk->yspeed -= 0x20;
      ++p_playerwk->u.play.talent_status;
      if (p_playerwk->u.play.talent_status == 32) {
        p_playerwk->u.play.talent_status = 1;
      }
    }
    else {
      p_playerwk->u.play.talent_status = 1;
    }
  }
  else {
    if (are_any_trg_buttons_used(g_ram.swdata0.pressed)
        && p_playerwk->yspeed >= -0x100
        && p_playerwk->pattimm != 0
        && (p_playerwk->u.play.cddat.underwater == 0 || g_ram.miles_carry_flag == 0)) {
      p_playerwk->u.play.talent_status = 2;
    }
    p_playerwk->yspeed += 8;
  }
  if (g_ram.scralim_up + 16 >= fp16_get_integer(p_playerwk->yposi) && p_playerwk->yspeed < 0) {
    p_playerwk->yspeed = 0;
  }
  setflyswim(p_playerwk);
}


static void setflyswim(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.underwater == 0) {
    if (g_ram.vs_flag == 0 && p_playerwk->pattimm == 0) {
      p_playerwk->mstno = 36;
      if (p_playerwk->actflg.onscreen == 1) {
        if (!(g_ram.gametimer + 8 & 0xF)) {
          soundset(-69);
        }
      }
    }
    else {
      unsigned char mstno = 32;
      if (g_ram.vs_flag == 0) {
        if (p_playerwk->yspeed < 0) {
          mstno = 33;
        }
        if (g_ram.miles_carry_flag != 0) {
          mstno += 2;
        }
      }
      p_playerwk->mstno = mstno;
      if (p_playerwk->actflg.onscreen == 1) {
        if (!(g_ram.gametimer + 8 & 0xF)) {
          soundset(-70);
        }
      }
    }
  }
  else {
    unsigned char mstno = 37;
    if (p_playerwk->yspeed < 0) {
      mstno = 38;
    }
    if (g_ram.miles_carry_flag != 0) {
      mstno = 39;
    }
    if (p_playerwk->pattimm == 0) {
      mstno = 40;
    }
    p_playerwk->mstno = mstno;
  }
}


static void foxball00walk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.miles_carry_flag != 0) {
    g_ram.actwk[0].u.play.control_bitfield = 0;
    g_ram.actwk[0].u.play.cddat.jump = 1;
    g_ram.miles_carry_flag = 0;
  }
  if (p_playerwk->u.play.spindash_flag != 0 || !foxjumpchk(p_playerwk)) {
    keispd2(p_playerwk);
    foxballlmove(p_playerwk, work);
    foxlimitchk(p_playerwk);
    speedset2_g(p_playerwk);
    fcol_g(p_playerwk);
    fallchk(p_playerwk);
    if (g_ram.scd_bg_flag != 0) {
      SKC_dircol_result result = crushchk_d(p_playerwk);
      if (result.offset < 0) {
        playdieset(p_playerwk);
      }
      else {
        result = dircol_l2(p_playerwk);
        if (result.offset < 0) {
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        }
        result = dircol_r2(p_playerwk);
        if (result.offset < 0) {
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        }
      }
    }
  }
}


static void foxball00jump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.miles_carry_flag != 0) {
    g_ram.actwk[0].u.play.control_bitfield = 0;
    g_ram.actwk[0].u.play.cddat.jump = 1;
    g_ram.miles_carry_flag = 0;
  }
  foxjumpchk2(p_playerwk, work);
  foxjumpmove(p_playerwk, work);
  foxlimitchk(p_playerwk);
  speedset_g(p_playerwk);
  if (p_playerwk->u.play.cddat.underwater == 1) {
    p_playerwk->yspeed -= 0x28;
  }
  direcchg(p_playerwk);
  foxjumpcolchk(p_playerwk);
}


static void foxlevermove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.powerdat.mizuflag == 0) {
    bool looking = false;
    bool skip_center = false;
    if (p_playerwk->u.play.hlock_timer == 0) {
      if (g_ram.swdata0.down.l == 1) {
        foxwalk_l(p_playerwk, work);
      }
      if (g_ram.swdata0.down.r == 1) {
        foxwalk_r(p_playerwk, work);
      }
      if (!(p_playerwk->direc.b.b0 + 32 & 0xC0) && p_playerwk->mspeed == 0) {
        p_playerwk->u.play.cddat.push = 0;
        p_playerwk->mstno = 5;
        bool balancing = false;
        if (p_playerwk->u.play.cddat.ride == 1) {
          SKC_sprite_status* p_ride_obj = &g_ram.actwk[p_playerwk->u.play.ride_obj];
          if (p_ride_obj->u.obj.cddat.die == 0) {
            unsigned char sprhs = p_ride_obj->sprhs * 2 - 4;
            short distance = (short)p_ride_obj->sprhs + fp16_get_integer(p_playerwk->xposi)
                           - fp16_get_integer(p_ride_obj->xposi);
            if (distance >= 4) {
              if (distance >= (short)sprhs) {
                p_playerwk->u.play.cddat.left = 0;
                p_playerwk->mstno = 6;
                balancing = true;
              }
            }
            else {
              p_playerwk->u.play.cddat.left = 1;
              p_playerwk->mstno = 6;
              balancing = true;
            }
          }
        }
        else {
          SKC_dircol_result result = edgechk_d2_g(p_playerwk, fp16_get_integer(p_playerwk->xposi));
          if (result.offset >= 12) {
            if (p_playerwk->u.play.angle_front == 3) {
              p_playerwk->u.play.cddat.left = 0;
              p_playerwk->mstno = 6;
              balancing = true;
            }
            else if (p_playerwk->u.play.angle_below == 3) {
              p_playerwk->u.play.cddat.left = 1;
              p_playerwk->mstno = 6;
              balancing = true;
            }
          }
        }
        if (!balancing) {
          if (g_ram.swdata0.down.d == 1) {
            p_playerwk->mstno = 8;
            ++p_playerwk->u.play.lever_ctr;
            looking = true;
            if (p_playerwk->u.play.lever_ctr >= 120) {
              p_playerwk->u.play.lever_ctr = 120;
              if (g_ram.reverse_gravity_flag == 0) {
                if (*work.scra_vline_ptr != 8) {
                  *work.scra_vline_ptr -= 2;
                }
              }
              else {
                if (*work.scra_vline_ptr != 216) {
                  *work.scra_vline_ptr += 2;
                }
              }
              skip_center = true;
            }
          }
          else if (g_ram.swdata0.down.u == 1) {
            p_playerwk->mstno = 7;
            ++p_playerwk->u.play.lever_ctr;
            looking = true;
            if (p_playerwk->u.play.lever_ctr >= 120) {
              p_playerwk->u.play.lever_ctr = 120;
              if (g_ram.reverse_gravity_flag == 0) {
                if (*work.scra_vline_ptr != 200) {
                  *work.scra_vline_ptr += 2;
                }
              }
              else {
                if (*work.scra_vline_ptr != 24) {
                  *work.scra_vline_ptr -= 2;
                }
              }
              skip_center = true;
            }
          }
        }
      }
    }
    if (!looking) {
      p_playerwk->u.play.lever_ctr = 0;
    }
    if (!skip_center && *work.scra_vline_ptr != 96) {
      if (*work.scra_vline_ptr < 96) {
        *work.scra_vline_ptr += 4;
      }
      *work.scra_vline_ptr -= 2;
    }
    if (g_ram.swdata0.down.l == 0 && g_ram.swdata0.down.r == 0) {
      if (p_playerwk->mspeed != 0) {
        short pladdspdwk = g_ram.smilesflag == 0 ? *work.pladdspdwk_ptr : 0xC;
        if (p_playerwk->mspeed >= 0) {
          p_playerwk->mspeed -= pladdspdwk;
          if (p_playerwk->mspeed < 0) {
            p_playerwk->mspeed = 0;
          }
        }
        else {
          p_playerwk->mspeed += pladdspdwk;
          if (p_playerwk->mspeed >= 0) {
            p_playerwk->mspeed = 0;
          }
        }
      }
    }
  }
  short sin, cos;
  sinset(p_playerwk->direc.b.b0, &sin, &cos);
  p_playerwk->xspeed = cos * p_playerwk->mspeed / 0x100;
  p_playerwk->yspeed = sin * p_playerwk->mspeed / 0x100;
  foxlmovecol(p_playerwk);
}


static void foxlmovecol(SKC_sprite_status* p_playerwk) {
  if (BIT_IS_SET(p_playerwk->u.play.control_bitfield, 6)) return;
  if ((p_playerwk->direc.b.b0 & 0x3F) && (p_playerwk->direc.b.b0 + 64 & 0xFF) >= 128) return;
  if (p_playerwk->mspeed == 0) return;

  unsigned char add_dir = p_playerwk->mspeed >= 0 ? 64 : 192;
  unsigned char miles_dir = p_playerwk->direc.b.b0 + add_dir;
  miles_dir &= 0xFF;
  SKC_dircol_result result = dircolm(p_playerwk, miles_dir);
  if (result.offset < 0) {
    short add_speed = result.offset * 0x100;
    if (get_zone(g_ram.stageno) == SANDOPOLIS && miles_dir >= 128) {
      --miles_dir;
    }
    miles_dir += 32;

    switch (miles_dir & 0xC0) {
      case 0:
        p_playerwk->yspeed += add_speed;
        break;
      case 64:
        p_playerwk->xspeed -= add_speed;
        p_playerwk->mspeed = 0;
        if (p_playerwk->u.play.cddat.left == 1) {
          p_playerwk->u.play.cddat.push = 1;
        }
        break;
      case 128:
        p_playerwk->yspeed -= add_speed;
        break;
      case 192:
        p_playerwk->xspeed += add_speed;
        p_playerwk->mspeed = 0;
        if (p_playerwk->u.play.cddat.left == 0) {
          p_playerwk->u.play.cddat.push = 1;
        }
        break;
    }
  }
}


static void foxwalk_l(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->mspeed <= 0) {
    if (p_playerwk->u.play.cddat.left == 0) {
      p_playerwk->u.play.cddat.left = 1;
      p_playerwk->u.play.cddat.push = 0;
      p_playerwk->mstrestart = 1;
    }
    short cal_speed = p_playerwk->mspeed - *work.pladdspdwk_ptr;
    if (cal_speed <= -*work.plmaxspdwk_ptr) {
      cal_speed += *work.pladdspdwk_ptr;
      if (cal_speed > -*work.plmaxspdwk_ptr) {
        cal_speed = -*work.plmaxspdwk_ptr;
      }
    }
    p_playerwk->mspeed = cal_speed;
    p_playerwk->mstno = 0;
  }
  else {
    short cal_speed = p_playerwk->mspeed - *work.plretspdwk_ptr;
    if (cal_speed < 0) {
      cal_speed = -0x80;
    }
    p_playerwk->mspeed = cal_speed;
    if (!(p_playerwk->direc.b.b0 + 32 & 0xC0) && cal_speed >= 0x400 && p_playerwk->u.play.flip_mst.reverse == 0) {
      soundset(54);
      p_playerwk->mstno = 13;
      p_playerwk->u.play.cddat.left = 0;
      if (p_playerwk->u.play.air_timer >= 12) {
        work.effectwk_ptr->r_no = 6;
        work.effectwk_ptr->patno = 21;
      }
    }
  }
}


static void foxwalk_r(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->mspeed >= 0) {
    if (p_playerwk->u.play.cddat.left == 1) {
      p_playerwk->u.play.cddat.left = 0;
      p_playerwk->u.play.cddat.push = 0;
      p_playerwk->mstrestart = 1;
    }
    short cal_speed = p_playerwk->mspeed + *work.pladdspdwk_ptr;
    if (cal_speed >= *work.plmaxspdwk_ptr) {
      cal_speed -= *work.pladdspdwk_ptr;
      if (cal_speed < *work.plmaxspdwk_ptr) {
        cal_speed = *work.plmaxspdwk_ptr;
      }
      p_playerwk->mspeed = cal_speed;
      p_playerwk->mstno = 0;
    }
  }
  else {
    short cal_speed = p_playerwk->mspeed + *work.plretspdwk_ptr;
    if (cal_speed >= 0) {
      cal_speed = 0x80;
    }
    p_playerwk->mspeed = cal_speed;
    if (!(p_playerwk->direc.b.b0 + 32 & 0xC0) && cal_speed <= -0x400 && p_playerwk->u.play.flip_mst.reverse == 0) {
      soundset(54);
      p_playerwk->mstno = 13;
      p_playerwk->u.play.cddat.left = 1;
      if (p_playerwk->u.play.air_timer >= 12) {
        work.effectwk_ptr->r_no = 6;
        work.effectwk_ptr->patno = 21;
      }
    }
  }
}


static void foxballlmove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short pladdspdwk = *work.pladdspdwk_ptr / 2;
  short plretspdwk = 0x20;
  if (!BIT_IS_SET(p_playerwk->u.play.spindash_flag, 7) && p_playerwk->u.play.powerdat.mizuflag == 0) {
    if (p_playerwk->u.play.hlock_timer == 0) {
      if (g_ram.swdata0.down.l == 1) {
        foxballwalk_l(p_playerwk, plretspdwk);
      }
      if (g_ram.swdata0.down.r == 1) {
        foxballwalk_r(p_playerwk, plretspdwk);
      }
    }
    if (g_ram.smilesflag != 0) {
      pladdspdwk = 6;
    }
    if (p_playerwk->mspeed != 0) {
      if (p_playerwk->mspeed >= 0) {
        p_playerwk->mspeed -= pladdspdwk;
        if (p_playerwk->mspeed < 0) {
          p_playerwk->mspeed = 0;
        }
      }
      else {
        p_playerwk->mspeed += pladdspdwk;
        if (p_playerwk->mspeed >= 0) {
          p_playerwk->mspeed = 0;
        }
      }
    }
    if (abs(p_playerwk->mspeed) < 0x80) {
      if (p_playerwk->u.play.spindash_flag == 0) {
        p_playerwk->u.play.cddat.ball = 0;
        short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
        p_playerwk->sprvsize = p_playerwk->u.play.height;
        p_playerwk->sprhsize = p_playerwk->u.play.width;
        p_playerwk->mstno = 5;
        if (g_ram.reverse_gravity_flag != 0) {
          yoffset = -yoffset;
        }
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
      }
      else {
        p_playerwk->mspeed = p_playerwk->u.play.cddat.left == 0 ? 0x400 : -0x400;
      }
    }
  }
  if (*work.scra_vline_ptr != 96) {
    if (*work.scra_vline_ptr < 96) {
      *work.scra_vline_ptr += 4;
    }
    *work.scra_vline_ptr -= 2;
  }
  short sin, cos;
  sinset(p_playerwk->direc.b.b0, &sin, &cos);
  p_playerwk->yspeed = sin * p_playerwk->mspeed / 0x100;
  p_playerwk->xspeed = cos * p_playerwk->mspeed / 0x100;
  if (p_playerwk->xspeed > 0x1000) {
    p_playerwk->xspeed = 0x1000;
  }
  if (p_playerwk->xspeed < -0x1000) {
    p_playerwk->xspeed = -0x1000;
  }
  foxlmovecol(p_playerwk);
}


static void foxballwalk_l(SKC_sprite_status* p_playerwk, short plretspdwk) {
  if (p_playerwk->mspeed <= 0) {
    p_playerwk->u.play.cddat.left = 1;
    p_playerwk->mstno = 2;
  }
  else {
    p_playerwk->mspeed -= plretspdwk;
    if (p_playerwk->mspeed < 0) {
      p_playerwk->mspeed = -0x80;
    }
  }
}


static void foxballwalk_r(SKC_sprite_status* p_playerwk, short plretspdwk) {
  if (p_playerwk->mspeed >= 0) {
    p_playerwk->u.play.cddat.left = 0;
    p_playerwk->mstno = 2;
  }
  else {
    p_playerwk->mspeed += plretspdwk;
    if (p_playerwk->mspeed >= 0) {
      p_playerwk->mspeed = 0x80;
    }
  }
}


static void foxjumpmove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short pladdspdwk = *work.pladdspdwk_ptr * 2;
  if (p_playerwk->u.play.cddat.ballj == 0) {
    short cal_speed = p_playerwk->xspeed;
    if (g_ram.swdata0.down.l == 1) {
      p_playerwk->u.play.cddat.left = 1;
      cal_speed -= pladdspdwk;
      if (cal_speed <= -*work.plmaxspdwk_ptr) {
        cal_speed += pladdspdwk;
        if (cal_speed > -*work.plmaxspdwk_ptr) {
          cal_speed = -*work.plmaxspdwk_ptr;
        }
      }
    }
    if (g_ram.swdata0.down.r == 1) {
      p_playerwk->u.play.cddat.left = 0;
      cal_speed += pladdspdwk;
      if (cal_speed >= *work.plmaxspdwk_ptr) {
        cal_speed -= pladdspdwk;
        if (cal_speed < *work.plmaxspdwk_ptr) {
          cal_speed = *work.plmaxspdwk_ptr;
        }
      }
    }
    p_playerwk->xspeed = cal_speed;
  }
  if (*work.scra_vline_ptr != 96) {
    if (*work.scra_vline_ptr < 96) {
      *work.scra_vline_ptr += 4;
    }
    *work.scra_vline_ptr -= 2;
  }
  if (p_playerwk->yspeed >= -0x400 && p_playerwk->xspeed / 32 != 0) {
    short cal_speed = p_playerwk->xspeed - p_playerwk->xspeed / 32;
    if (p_playerwk->xspeed >= 0) {
      if (cal_speed < 0) {
        cal_speed = 0;
      }
    }
    else {
      if (cal_speed >= 0) {
        cal_speed = 0;
      }
    }
    p_playerwk->xspeed = cal_speed;
  }
}


static void foxlimitchk(SKC_sprite_status* p_playerwk) {
  long cal_position = p_playerwk->xposi + p_playerwk->xspeed * 0x100;
  short cal_limit_l = g_ram.scralim_left + 16;
  if (cal_limit_l > fp16_get_integer(cal_position)) {
    foxlimitset(p_playerwk, cal_limit_l);
  }
  else {
    short cal_limit_r = g_ram.scralim_right + 296;
    if (cal_limit_r >= fp16_get_integer(cal_position)) {
      foxlimitset(p_playerwk, cal_limit_r);
    }
  }
  if (g_ram.DAT_08fff665 == 0) {
    if ((g_ram.reverse_gravity_flag == 0 && g_ram.scralim_down + 224 < fp16_get_integer(p_playerwk->yposi))
        || (g_ram.reverse_gravity_flag != 0 && g_ram.scralim_up >= fp16_get_integer(p_playerwk->yposi))) {
      playdieset(p_playerwk);
    }
  }
}


static void foxlimitset(SKC_sprite_status* p_playerwk, short cal_limit) {
  fp16_set_integer(&p_playerwk->xposi, cal_limit);
  fp16_set_fraction(&p_playerwk->xposi, 0);
  p_playerwk->xspeed = 0;
  p_playerwk->mspeed = 0;
}


static void foxballchk(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.powerdat.mizuflag == 1) return;
  if (g_ram.swdata0.down.l == 1 || g_ram.swdata0.down.r == 1) return;

  if (g_ram.swdata0.down.d == 1) {
    if (abs(p_playerwk->mspeed) >= 0x100) {
      foxballset(p_playerwk);
    }
    else if (p_playerwk->u.play.cddat.ride == 0) {
      p_playerwk->mstno = 8;
    }
  }
  else if (p_playerwk->mstno == 8) {
    p_playerwk->mstno = 0;
  }
}


static void foxballset(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.ball == 1) return;

  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
  if (g_ram.reverse_gravity_flag != 0) {
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 2);
  }
  soundset(60);
  if (p_playerwk->mspeed == 0) {
    p_playerwk->mspeed = 0x200;
  }
}


static bool foxjumpchk(SKC_sprite_status* p_playerwk) {
  if (!are_any_trg_buttons_used(g_ram.swdata0.pressed)) return false;

  unsigned char cal_direc = p_playerwk->direc.b.b0;
  if (g_ram.reverse_gravity_flag != 0) {
    cal_direc = (256 - (cal_direc + 64) - 64);
  }
  cal_direc += 128;
  cal_direc &= 0xFF;
  SKC_dircol_result result = dircol2(p_playerwk, cal_direc);
  if (result.offset >= 6) {
    short cal_jump = p_playerwk->u.play.cddat.underwater == 0 ? 0x680 : 0x380;
    cal_direc = p_playerwk->direc.b.b0 - 64;
    cal_direc &= 0xFF;
    short sin, cos;
    sinset(cal_direc, &sin, &cos);
    p_playerwk->xspeed += cos * cal_jump / 0x100;
    p_playerwk->yspeed += sin * cal_jump / 0x100;
    p_playerwk->u.play.cddat.jump = 1;
    p_playerwk->u.play.cddat.push = 0;
    p_playerwk->u.play.jump_flag = 1;
    p_playerwk->u.play.convex_flag = 0;
    soundset(98);
    p_playerwk->sprvsize = p_playerwk->u.play.cddat.ball == 1 ? p_playerwk->u.play.height : 14;
    p_playerwk->sprhsize = p_playerwk->u.play.cddat.ball == 1 ? p_playerwk->u.play.width : 7;
    if (p_playerwk->u.play.cddat.ball == 0) {
      p_playerwk->mstno = 2;
      p_playerwk->u.play.cddat.ball = 1;
      short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
      if (g_ram.reverse_gravity_flag != 0) {
        yoffset = -yoffset;
      }
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - yoffset);
    }
    else {
      p_playerwk->u.play.cddat.ballj = 1;
    }
    return true;
  }
  return false;
}


static void foxjumpchk2(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.jump_flag != 0) {
    short cal_speed = p_playerwk->u.play.cddat.underwater == 0 ? -0x400 : -0x200;
    if (cal_speed > p_playerwk->yspeed) {
      if (!are_any_trg_buttons_used(g_ram.swdata0.down)) {
        p_playerwk->yspeed = cal_speed;
      }
    }
    else {
      foxjumpchk3(p_playerwk, work);
    }
  }
  else if (p_playerwk->u.play.spindash_flag == 0 && p_playerwk->yspeed < -0xFC0) {
    p_playerwk->yspeed = -0xFC0;
  }
}


static void foxjumpchk3(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.talent_status != 0) return;
  if (!are_any_trg_buttons_used(g_ram.swdata0.pressed)) return;
  if (g_ram.play_type != PLAY_TYPE_MILES && g_ram.foxcpu_timer == 0) return;

  if (g_ram.play_type != PLAY_TYPE_MILES || g_ram.semeraldcnt < 7 || g_ram.plring < 50 || g_ram.pltime_f == 0) {
    if (p_playerwk->u.play.cddat.ball == 1) {
      p_playerwk->u.play.cddat.ball = 0;
      short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
      p_playerwk->sprvsize = p_playerwk->u.play.height;
      p_playerwk->sprhsize = p_playerwk->u.play.width;
      if (g_ram.reverse_gravity_flag != 0) {
        yoffset = -yoffset;
      }
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
    }
    p_playerwk->u.play.cddat.ballj = 0;
    p_playerwk->u.play.talent_status = 1;
    p_playerwk->pattimm = 240;
    setflyswim(p_playerwk);
  }
  else {
    g_ram.ssonicpallet = 1;
    g_ram.ssonicpallet_next = 15;
    g_ram.smilesflag = 1;
    g_ram.ssonicring_timer = 60;
    p_playerwk->u.play.control_bitfield = 0x81;
    p_playerwk->mstno = 41;
    g_ram.actwk[ACTWK_PL_MUTEKI].r_ptr = &smilesflickies;
    *work.plmaxspdwk_ptr = 0x800;
    *work.pladdspdwk_ptr = 0x18;
    *work.plretspdwk_ptr = 0xC0;
    p_playerwk->u.play.muteki_timer = 0;
    p_playerwk->u.play.powerdat.muteki = 1;
    soundset(-97);
    bgmset(44);
  }
}


static bool foxspinchk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short spd_tbl[9] = {
    0x800, 0x880, 0x900, 0x980, 0xA00, 0xA80, 0xB00, 0xB80, 0xC00
  };
  short spd_tbl2[9] = {
    0xA00, 0xA80, 0xB00, 0xB80, 0xC00, 0xC80, 0xD00, 0xD80, 0xE00
  };

  if (p_playerwk->u.play.spindash_flag == 0) {
    if (p_playerwk->mstno == 8 && are_any_trg_buttons_used(g_ram.swdata0.pressed)) {
      p_playerwk->mstno = 9;
      soundset(-85);
      p_playerwk->u.play.spindash_flag = 1;
      p_playerwk->u.play.spindash_ctr = 0;
      if (p_playerwk->u.play.air_timer >= 12) {
        work.effectwk_ptr->mstno = 2;
      }
      foxlimitchk(p_playerwk);
      fcol_g(p_playerwk);
      if (g_ram.scd_bg_flag != 0) {
        SKC_dircol_result result = crushchk_d(p_playerwk);
        if (result.offset < 0) {
          playdieset(p_playerwk);
        }
        else {
          result = dircol_l2(p_playerwk);
          if (result.offset < 0) {
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
          }
          result = dircol_r2(p_playerwk);
          if (result.offset < 0) {
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
          }
        }
      }
      return true;
    }
  }
  else {
    if (g_ram.swdata0.down.d == 0) {
      p_playerwk->sprvsize = 14;
      p_playerwk->sprhsize = 7;
      p_playerwk->mstno = 2;
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
      if (g_ram.reverse_gravity_flag != 0) {
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 2);
      }
      p_playerwk->u.play.spindash_flag = 0;
      unsigned char index = p_playerwk->u.play.spindash_ctr >> 8;
      p_playerwk->mspeed = g_ram.smilesflag == 0 ? spd_tbl[index] : spd_tbl2[index];
      short delay = -((p_playerwk->mspeed - 0x800) * 2 & 0x1F00) + 0x2000;
      if (p_playerwk == &g_ram.actwk[0]) {
        g_ram.DAT_08ffee24 = delay;
      }
      else {
        g_ram.DAT_08ffee28 = delay;
      }
      if (p_playerwk->u.play.cddat.left == 1) {
        p_playerwk->mspeed = -p_playerwk->mspeed;
      }
      p_playerwk->u.play.cddat.ball = 1;
      work.effectwk_ptr->mstno = 0;
      soundset(-74);
    }
    else {
      if (p_playerwk->u.play.spindash_ctr != 0) {
        p_playerwk->u.play.spindash_ctr -= p_playerwk->u.play.spindash_ctr >> 5;
        if (p_playerwk->u.play.spindash_ctr < 0) {
          p_playerwk->u.play.spindash_ctr = 0;
        }
      }
      if (are_any_trg_buttons_used(g_ram.swdata0.pressed)) {
        p_playerwk->mstno = 9;
        p_playerwk->mstrestart = 0;
        soundset(-85);
        p_playerwk->u.play.spindash_ctr += 0x200;
        if (p_playerwk->u.play.spindash_ctr >= 0x800) {
          p_playerwk->u.play.spindash_ctr = 0x800;
        }
      }
    }
    if (*work.scra_vline_ptr != 96) {
      if (*work.scra_vline_ptr < 96) {
        *work.scra_vline_ptr += 4;
      }
      *work.scra_vline_ptr -= 2;
    }
    foxlimitchk(p_playerwk);
    fcol_g(p_playerwk);
    if (g_ram.scd_bg_flag != 0) {
      SKC_dircol_result result = crushchk_d(p_playerwk);
      if (result.offset < 0) {
        playdieset(p_playerwk);
      }
      else {
        result = dircol_l2(p_playerwk);
        if (result.offset < 0) {
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        }
        result = dircol_r2(p_playerwk);
        if (result.offset < 0) {
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        }
      }
    }
    return true;
  }
  return false;
}


static void foxjumpcolchk(SKC_sprite_status* p_playerwk) {
  g_ram.scdadr = p_playerwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  unsigned char cal_direc = atan(p_playerwk->xspeed, p_playerwk->yspeed) - 32;

  switch (cal_direc & 0xC0) {
    case 0: {
      SKC_dircol_result result = dircol_l2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        p_playerwk->xspeed = 0;
      }
      result = dircol_r2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        p_playerwk->xspeed = 0;
      }
      result = dircol_d_g(p_playerwk);
      if (result.offset < 0) {
        signed char yspeed = -(fp8_get_integer(p_playerwk->yspeed) + 8);
        if (result.offset >= yspeed || result.offset2 >= yspeed) {
          p_playerwk->direc.b.b0 = result.direc;
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          if (!(p_playerwk->direc.b.b0 + 32 & 0x40)) {
            if (p_playerwk->direc.b.b0 + 16 & 0x20) {
              p_playerwk->yspeed /= 2;
            }
            else {
              p_playerwk->yspeed = 0;
              p_playerwk->mspeed = p_playerwk->xspeed;
              foxjumpcolsub(p_playerwk);
              return;
            }
          }
          else {
            p_playerwk->xspeed = 0;
            if (p_playerwk->yspeed > 0xFC0) {
              p_playerwk->yspeed = 0xFC0;
            }
          }
          foxjumpcolsub(p_playerwk);
          p_playerwk->mspeed = p_playerwk->yspeed;
          if (p_playerwk->direc.b.b0 >= 128) {
            p_playerwk->mspeed = -p_playerwk->mspeed;
          }
        }
      }
      break;
    }
    case 64: {
      SKC_dircol_result result = dircol_l2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        p_playerwk->xspeed = 0;
        p_playerwk->mspeed = p_playerwk->yspeed;
      }
      result = dircol_u_g(p_playerwk);
      if (result.offset < 0) {
        result.offset = -result.offset;
        if (result.offset < 20) {
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          if (p_playerwk->yspeed < 0) {
            p_playerwk->yspeed = 0;
          }
        }
        else {
          result = dircol_r2(p_playerwk);
          if (result.offset < 0) {
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
            p_playerwk->xspeed = 0;
          }
        }
      }
      else if (g_ram.watercoliflag2 != 0 || p_playerwk->yspeed >= 0) {
        result = dircol_d_g(p_playerwk);
        if (result.offset < 0) {
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          p_playerwk->direc.b.b0 = result.direc;
          p_playerwk->yspeed = 0;
          p_playerwk->mspeed = p_playerwk->xspeed;
          foxjumpcolsub(p_playerwk);
        }
      }
      break;
    }
    case 128: {
      SKC_dircol_result result = dircol_l2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        p_playerwk->xspeed = 0;
      }
      result = dircol_r2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        p_playerwk->xspeed = 0;
      }
      result = dircol_u_g(p_playerwk);
      if (result.offset < 0) {
        if (g_ram.reverse_gravity_flag != 0) {
          result.offset = -result.offset;
        }
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - result.offset);
        if (!(result.direc + 32 & 0x40)) {
          p_playerwk->yspeed = 0;
        }
        else {
          p_playerwk->direc.b.b0 = result.direc;
          foxjumpcolsub(p_playerwk);
          p_playerwk->mspeed = p_playerwk->yspeed;
          if (p_playerwk->direc.b.b0 >= 128) {
            p_playerwk->mspeed = -p_playerwk->mspeed;
          }
        }
      }
      break;
    }
    case 192: {
      SKC_dircol_result result = dircol_r2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        p_playerwk->xspeed = 0;
        p_playerwk->mspeed = p_playerwk->yspeed;
      }
      result = dircol_u_g(p_playerwk);
      if (result.offset < 0) {
        if (g_ram.reverse_gravity_flag != 0) {
          result.offset = -result.offset;
        }
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - result.offset);
        if (p_playerwk->yspeed < 0) {
          p_playerwk->yspeed = 0;
        }
      }
      else if (g_ram.watercoliflag2 != 0 || p_playerwk->yspeed >= 0) {
        result = dircol_d_g(p_playerwk);
        if (result.offset < 0) {
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          p_playerwk->direc.b.b0 = result.direc;
          p_playerwk->yspeed = 0;
          p_playerwk->mspeed = p_playerwk->xspeed;
          foxjumpcolsub(p_playerwk);
        }
      }
      break;
    }
  }
}


static void foxjumpcolsub(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.spindash_flag == 0) {
    p_playerwk->mstno = 0;
    foxjumpcolsub0(p_playerwk);
  }
  else {
    foxjumpcolsub1(p_playerwk);
  }
}


void foxjumpcolsub0(SKC_sprite_status* p_playerwk) {
  short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
  p_playerwk->sprvsize = p_playerwk->u.play.height;
  p_playerwk->sprhsize = p_playerwk->u.play.width;
  if (p_playerwk->u.play.cddat.ball == 1) {
    p_playerwk->u.play.cddat.ball = 0;
    p_playerwk->mstno = 0;
    if (g_ram.reverse_gravity_flag != 0) {
      yoffset = -yoffset;
    }
    unsigned char cal_direc = p_playerwk->direc.b.b0 + 64;
    cal_direc &= 0xFF;
    if (cal_direc >= 128) {
      yoffset = -yoffset;
    }
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
  }
  foxjumpcolsub1(p_playerwk);
}


static void foxjumpcolsub1(SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.cddat.jump = 0;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.cddat.ballj = 0;
  p_playerwk->u.play.jump_flag = 0;
  g_ram.emyscorecnt = 0;
  p_playerwk->direc.b.b1 = 0;
  p_playerwk->u.play.flip_mst.type = 0;
  p_playerwk->u.play.flip_mst.reverse = 0;
  p_playerwk->u.play.flip_rev_cnt = 0;
  p_playerwk->u.play.lever_ctr = 0;
  p_playerwk->u.play.talent_status = 0;
}


static void fox00damage(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.play_type == PLAY_TYPE_MILES && g_ram.debugflag != 0 && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    if (g_ram.miles_carry_flag != 0) {
      g_ram.actwk[0].u.play.control_bitfield = 0;
      g_ram.actwk[0].u.play.cddat.jump = 1;
      g_ram.miles_carry_flag = 0;
    }
    speedset2_g(p_playerwk);
    p_playerwk->yspeed += 0x30;
    if (p_playerwk->u.play.cddat.underwater == 1) {
      p_playerwk->yspeed -= 0x20;
    }
    if (g_ram.scralim_up == -0x100) {
      short yposi = (unsigned short)fp16_get_integer(p_playerwk->yposi) & g_ram.scrc_v;
      fp16_set_integer(&p_playerwk->yposi, yposi);
    }
    fox00damage_sub(p_playerwk);
    foxlimitchk(p_playerwk);
    playposiwkset(p_playerwk);
    foxpatchgmainwrt(p_playerwk);
    actionsub(p_playerwk);
  }
}


static void fox00damage_sub(SKC_sprite_status* p_playerwk) {
  if (g_ram.DAT_08fff665 != 0
      || (g_ram.reverse_gravity_flag == 0 && g_ram.scralim_down + 224 >= fp16_get_integer(p_playerwk->yposi))
      || (g_ram.reverse_gravity_flag != 0 && g_ram.scralim_up < fp16_get_integer(p_playerwk->yposi))) {
    foxjumpcolchk(p_playerwk);
    if (p_playerwk->u.play.cddat.jump == 0) {
      p_playerwk->yspeed = 0;
      p_playerwk->xspeed = 0;
      p_playerwk->mspeed = 0;
      p_playerwk->u.play.control_bitfield = 0;
      p_playerwk->mstno = 0;
      p_playerwk->sprpri = PRI_2;
      p_playerwk->r_no = 2;
      p_playerwk->u.play.invulnerability_timer = 120;
      p_playerwk->u.play.spindash_flag = 0;
    }
  }
  else {
    playdieset(p_playerwk);
  }
}


static void fox00die(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.play_type == PLAY_TYPE_MILES && g_ram.debugflag != 0 && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    if (g_ram.miles_carry_flag != 0) {
      g_ram.actwk[0].u.play.control_bitfield = 0;
      g_ram.actwk[0].u.play.cddat.jump = 1;
      g_ram.miles_carry_flag = 0;
    }
    play00die_sub(p_playerwk, work);
    speedset_g(p_playerwk);
    playposiwkset(p_playerwk);
    foxpatchgmainwrt(p_playerwk);
    actionsub(p_playerwk);
  }
}


static void fox00erase(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.spindash_ctr == 0) return;

  --p_playerwk->u.play.spindash_ctr;
  if (p_playerwk->u.play.spindash_ctr == 0) {
    g_ram.gameflag = 1;
  }
}


static void fox00appear(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.DAT_08ffee04 == 0 && g_ram.DAT_08ffee06 == 0) {
    p_playerwk->r_no = 2;
  }
  foxpatchgmainwrt(p_playerwk);
  actionsub(p_playerwk);
}


static void fox00drown(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.miles_carry_flag != 0) {
    g_ram.actwk[0].u.play.control_bitfield = 0;
    g_ram.actwk[0].u.play.cddat.jump = 1;
    g_ram.miles_carry_flag = 0;
  }
  speedset2_g(p_playerwk);
  p_playerwk->yspeed += 0x10;
  playposiwkset(p_playerwk);
  foxpatchgmainwrt(p_playerwk);
  actionsub(p_playerwk);
}


static void foxpatchgmainwrt(SKC_sprite_status* p_playerwk) {
  if (g_ram.vs_flag == 0) {
    foxpatchgmain(p_playerwk);
    if (g_ram.reverse_gravity_flag != 0) {
      p_playerwk->actflg.vflip ^= 1;
    }
    foxwrt(p_playerwk);
  }
  else {
    vsfoxpatchgmain(p_playerwk);
    vsfoxwrt(p_playerwk);
  }
}


static void foxpatchgmain(SKC_sprite_status* p_playerwk) {
  foxpatchgmain0(p_playerwk, foxchg);
}


static void foxpatchgmain0(SKC_sprite_status* p_actwk, unsigned char** pp_chg) {
  if (p_actwk->mstno != p_actwk->mstrestart) {
    p_actwk->mstrestart = p_actwk->mstno;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
    p_actwk->u.play.cddat.push = 0;
  }
  unsigned char* p_chg = pp_chg[p_actwk->mstno];
  if (p_chg[0] >= 128) {
    foxrunchg(p_actwk, p_chg[0]);
  }
  else {
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
    p_actwk->actflg.vflip = 0;
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = p_chg[0];
      foxpatchgmain2(p_actwk, p_chg);
    }
  }
}


static void foxpatchgmain2(SKC_sprite_status* p_actwk, unsigned char* p_chg) {
  unsigned char patno = p_chg[p_actwk->patcnt + 1];
  if (patno < 252) {
    p_actwk->patno = patno;
    ++p_actwk->patcnt;
  }
  else {
    switch (patno) {
      case MAINPATCHG_CONTROL_LOOP:
        p_actwk->patcnt = 0;
        p_actwk->patno = p_chg[1];
        ++p_actwk->patcnt;
        break;
      case MAINPATCHG_CONTROL_REWIND:
        p_actwk->patno = p_chg[p_actwk->patcnt + 1 - p_chg[p_actwk->patcnt + 2]];
        p_actwk->patcnt -= p_chg[p_actwk->patcnt + 2] - 1;
        break;
      case MAINPATCHG_CONTROL_NEXT:
        p_actwk->mstno = p_chg[p_actwk->patcnt + 2];
        break;
    }
  }
}


static void foxrunchg(SKC_sprite_status* p_actwk, unsigned char patno) {
  if (patno != 255) {
    foxrunchg2(p_actwk, patno);
  }
  else if (p_actwk->u.play.flip_mst.reverse == 1 || p_actwk->direc.b.b1 != 0) {
    playflipchg(p_actwk);
  }
  else {
    unsigned char direction = p_actwk->direc.b.b0;
    if (direction < 128 && direction != 0) {
      --direction;
    }
    if (p_actwk->u.play.cddat.left == 0) {
      direction = 255 - direction;
    }
    direction += 16;
    direction &= 0xFF;
    if (direction >= 128) {
      p_actwk->actflg.hflip = p_actwk->u.play.cddat.left ^ 1;
      p_actwk->actflg.vflip = 1;
    }
    else {
      p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
      p_actwk->actflg.vflip = 0;
    }
    if (p_actwk->u.play.cddat.push == 1) {
      foxrunchg3(p_actwk);
    }
    else {
      unsigned char patno_add = direction / 16 & 6;
      short cal_speed = abs(p_actwk->mspeed);
      if (p_actwk->u.play.powerdat.mizuflag == 1) {
        cal_speed *= 2;
      }
      unsigned char* p_chg = cal_speed < 0x600 ? foxchg00 : cal_speed < 0x700 ? foxchg01 : foxchg31;
      patno_add = cal_speed < 0x600 ? patno_add * 4 : cal_speed < 0x700 ? patno_add * 2 : patno_add * 1;
      unsigned char patno = p_chg[p_actwk->patcnt + 1];
      if (patno == 255) {
        p_actwk->patcnt = 0;
        patno = p_chg[1];
      }
      p_actwk->patno = patno + patno_add;
      if (p_actwk->pattim-- == 0) {
        cal_speed = -cal_speed + 0x800;
        if (cal_speed < 0) {
          cal_speed = 0;
        }
        p_actwk->pattim = cal_speed / 0x100;
        ++p_actwk->patcnt;
      }
    }
  }
}


static void foxrunchg2(SKC_sprite_status* p_actwk, unsigned char patno) {
  if (patno != 254) {
    foxrunchg4(p_actwk);
  }
  else {
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
    p_actwk->actflg.vflip = 0;
    if (p_actwk->pattim-- == 0) {
      short cal_speed = abs(p_actwk->mspeed);
      unsigned char* p_chg = cal_speed >= 0x600 ? foxchg03 : foxchg02;
      cal_speed = -cal_speed + 0x400;
      if (cal_speed < 0) {
        cal_speed = 0;
      }
      p_actwk->pattim = cal_speed / 0x100;
      foxpatchgmain2(p_actwk, p_chg);
    }
  }
}


static void foxrunchg3(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  short cal_speed = -abs(p_actwk->mspeed) + 0x800;
  if (cal_speed < 0) {
    cal_speed = 0;
  }
  cal_speed /= 0x40;
  p_actwk->pattim = cal_speed % 0x100;
  foxpatchgmain2(p_actwk, foxchg04);
}


static void foxrunchg4(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.play.ride_obj];
  unsigned char angle = atan(p_playerwk->xspeed, p_playerwk->yspeed);
  if (get_zone(g_ram.stageno) == SLOT_MACHINE) {
    SKC_swdata swdata = g_ram.playrecwk[0].swdata;
    angle += swdata.pressed.d
           + swdata.pressed.u * 2
           + swdata.pressed.l * 4
           + swdata.pressed.r * 8
           + swdata.pressed.b * 16
           + swdata.pressed.c * 32
           + swdata.pressed.a * 64
           + swdata.pressed.s * 128;
    angle &= 0xFF;
  }
  if (p_actwk->u.play.cddat.left == 0) {
    angle = 255 - angle;
  }
  else {
    angle += 128;
  }
  angle += 16;
  angle &= 0xFF;
  if (angle >= 128) {
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left ^ 1;
    p_actwk->actflg.vflip = 1;
  }
  else {
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
    p_actwk->actflg.vflip = 0;
  }
  if (g_ram.reverse_gravity_flag != 0) {
    p_actwk->actflg.vflip ^= 1;
  }
  unsigned char patno_add = angle / 8 & 0xC;
  p_actwk->pattim = 3;
  foxpatchgmain2(p_actwk, foxtailschg03);
  p_actwk->patno += patno_add;
}


static unsigned char* foxchg[42] = {
  foxchg00,
  foxchg01,
  foxchg02,
  foxchg03,
  foxchg04,
  foxchg05,
  foxchg06,
  foxchg07,
  foxchg08,
  foxchg09,
  foxchg10,
  foxchg11,
  foxchg12,
  foxchg13,
  foxchg14,
  foxchg15,
  foxchg16,
  foxchg17,
  foxchg18,
  foxchg19,
  foxchg20,
  foxchg21,
  foxchg22,
  foxchg23,
  foxchg24,
  foxchg25,
  foxchg26,
  foxchg27,
  foxchg28,
  foxchg29,
  foxchg30,
  foxchg31,
  foxchg32,
  foxchg33,
  foxchg34,
  foxchg35,
  foxchg36,
  foxchg37,
  foxchg38,
  foxchg39,
  foxchg40,
  foxchg41
};


static unsigned char foxchg00[10] = { 255, 7, 8, 1, 2, 3, 4, 5, 6, 255 };
static unsigned char foxchg01[10] = { 255, 33, 34, 35, 36, 255, 255, 255, 255, 255 };
static unsigned char foxchg02[5] = { 1, 150, 151, 152, 255 };
static unsigned char foxchg03[5] = { 0, 150, 151, 152, 255 };
static unsigned char foxchg04[10] = { 253, 169, 170, 171, 172, 255, 255, 255, 255, 255 };
static unsigned char foxchg05[62] = {
    7, 173, 173, 173, 173, 173, 173, 173, 173, 173,
  173, 175, 174, 173, 173, 173, 173, 173, 173, 173,
  173, 175, 174, 173, 173, 173, 173, 173, 173, 173,
  173, 173, 177, 177, 177, 177, 177, 177, 177, 177,
  177, 177, 177, 177, 177, 177, 177, 177, 178, 179,
  180, 179, 180, 179, 180, 179, 180, 179, 180, 178,
  254, 28
};
static unsigned char foxchg06[24] = {
    9, 154, 154, 155, 155, 154, 154, 155, 155, 154,
  154, 155, 155, 154, 154, 155, 155, 154, 154, 155,
  155, 154, 155, 255
};
static unsigned char foxchg07[3] = { 63, 176, 255 };
static unsigned char foxchg08[3] = { 63, 153, 255 };
static unsigned char foxchg09[5] = { 0, 134, 135, 136, 255 };
static unsigned char foxchg10[3] = { 63, 130, 255 };
static unsigned char foxchg11[3] = { 15, 141, 255 };
static unsigned char foxchg12[4] = { 9, 164, 155, 255 };
static unsigned char foxchg13[7] = { 3, 142, 143, 142, 143, 253, 0 };
static unsigned char foxchg14[3] = { 9, 181, 255 };
static unsigned char foxchg15[10] = { 9, 181, 182, 183, 184, 185, 186, 187, 188, 255 };
static unsigned char foxchg16[15] = { 3, 139, 140, 139, 140, 139, 140, 139, 140, 139, 140, 139, 140, 253, 0 };
static unsigned char foxchg17[4] = { 1, 157, 158, 255 };
static unsigned char foxchg18[6] = { 15, 1, 2, 3, 254, 1 };
static unsigned char foxchg19[5] = { 15, 165, 166, 254, 1 };
static unsigned char foxchg20[3] = { 19, 145, 255 };
static unsigned char foxchg21[7] = { 11, 159, 159, 3, 4, 253, 0 };
static unsigned char foxchg22[3] = { 32, 156, 255 };
static unsigned char foxchg23[3] = { 47, 156, 255 };
static unsigned char foxchg24[3] = { 3, 156, 255 };
static unsigned char foxchg25[4] = { 9, 203, 204, 255 };
static unsigned char foxchg26[3] = { 64, 138, 255 };
static unsigned char foxchg27[4] = { 9, 137, 138, 255 };
static unsigned char foxchg28[3] = { 119, 0, 255 };
static unsigned char foxchg29[10] = { 3, 1, 2, 3, 4, 5, 6, 7, 8, 255 };
static unsigned char foxchg30[10] = { 3, 1, 2, 3, 4, 5, 6, 7, 8, 255 };
static unsigned char foxchg31[10] = { 255, 195, 196, 255, 255, 255, 255, 255, 255, 255 };
static unsigned char foxchg32[3] = { 31, 160, 255 };
static unsigned char foxchg33[3] = { 31, 160, 255 };
static unsigned char foxchg34[3] = { 31, 162, 255 };
static unsigned char foxchg35[3] = { 31, 161, 255 };
static unsigned char foxchg36[4] = { 11, 163, 164, 255 };
static unsigned char foxchg37[7] = { 7, 189, 190, 191, 192, 193, 255 };
static unsigned char foxchg38[7] = { 3, 189, 190, 191, 192, 193, 255 };
static unsigned char foxchg39[4] = { 4, 207, 208, 255 };
static unsigned char foxchg40[5] = { 11, 194, 205, 206, 255 };
static unsigned char foxchg41[15] = { 2, 235, 235, 236, 237, 236, 237, 236, 237, 236, 237, 236, 237, 253, 0 };


static void foxtailswrt(SKC_sprite_status* p_actwk) {
  if (p_actwk->patno == g_ram.foxtailspatno) return;

  g_ram.foxtailspatno = p_actwk->patno;
  unsigned short* p_wrtpat = foxtailswrtpat[p_actwk->patno];
  unsigned short cnt = *p_wrtpat++;
  foxwrt1(p_wrtpat, cnt, 0xD600, foxtails_cg);
}


void foxwrt(SKC_sprite_status* p_playerwk) {
  foxwrt0(p_playerwk->patno);
}


void foxwrt0(unsigned char patno) {
  if (patno == g_ram.foxpatno) return;

  g_ram.foxpatno = patno;
  unsigned short* p_wrtpat = foxwrtpat[patno];
  unsigned short cnt = *p_wrtpat++;
  unsigned char* p_cg = patno < 209 ? fox_cg : fox_cg2;
  foxwrt1(p_wrtpat, cnt, 0xD400, p_cg);
}


static void foxwrt1(unsigned short* p_wrtpat, unsigned short cnt, unsigned short vram_adr, unsigned char* p_cg) {
  for (int i = 0; i < cnt; ++i) {
    unsigned short command = *p_wrtpat++;
    command = command << 8 | command >> 8;
    unsigned char* p_source = &p_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


static void vsfoxpatchgmain(SKC_sprite_status* p_playerwk) {
  vsfoxpatchgmain0(p_playerwk, vsfoxchg);
}


static void vsfoxpatchgmain0(SKC_sprite_status* p_actwk, unsigned char** pp_chg) {
  if (p_actwk->mstno != p_actwk->mstrestart) {
    p_actwk->mstrestart = p_actwk->mstno;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
    p_actwk->u.play.cddat.push = 0;
  }
  unsigned char* p_chg = pp_chg[p_actwk->mstno];
  if (p_chg[0] >= 128) {
    vsfoxrunchg(p_actwk, p_chg[0]);
  }
  else {
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
    p_actwk->actflg.vflip = 0;
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = p_chg[0];
      vsfoxpatchgmain2(p_actwk, p_chg);
    }
  }
}


static void vsfoxpatchgmain2(SKC_sprite_status* p_actwk, unsigned char* p_chg) {
  unsigned char patno = p_chg[p_actwk->patcnt + 1];
  if (patno < 240) {
    p_actwk->patno = patno;
    ++p_actwk->patcnt;
  }
  else {
    switch (patno) {
      case MAINPATCHG_CONTROL_LOOP:
        p_actwk->patcnt = 0;
        p_actwk->patno = p_chg[1];
        ++p_actwk->patcnt;
        break;
      case MAINPATCHG_CONTROL_REWIND:
        p_actwk->patno = p_chg[p_actwk->patcnt + 1 - p_chg[p_actwk->patcnt + 2]];
        p_actwk->patcnt -= p_chg[p_actwk->patcnt + 2] - 1;
        break;
      case MAINPATCHG_CONTROL_NEXT:
        p_actwk->mstno = p_chg[p_actwk->patcnt + 2];
        break;
    }
  }
}


static void vsfoxrunchg(SKC_sprite_status* p_actwk, unsigned char patno) {
  if (patno != 255) {
    vsfoxrunchg2(p_actwk, patno);
  }
  else if (p_actwk->direc.b.b1 != 0) {
    vsfoxflipchg(p_actwk);
  }
  else {
    unsigned char direction = p_actwk->direc.b.b0;
    if (direction < 128 && direction != 0) {
      --direction;
    }
    if (p_actwk->u.play.cddat.left == 0) {
      direction = 255 - direction;
    }
    direction += 16;
    direction &= 0xFF;
    if (direction >= 128) {
      p_actwk->actflg.hflip = p_actwk->u.play.cddat.left ^ 1;
      p_actwk->actflg.vflip = 1;
    }
    else {
      p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
      p_actwk->actflg.vflip = 0;
    }
    if (p_actwk->u.play.cddat.push == 1) {
      vsfoxrunchg3(p_actwk);
    }
    else {
      unsigned char patno_add = direction / 32 & 3;
      short cal_speed = abs(p_actwk->mspeed);
      if (p_actwk->u.play.powerdat.mizuflag == 1) {
        cal_speed *= 2;
      }
      unsigned char* p_chg = cal_speed >= 0x600 ? vsfoxchg01 : vsfoxchg00;
      patno_add = cal_speed >= 0x600 ? patno_add * 2 : patno_add * 3;
      unsigned char patno = p_chg[p_actwk->patcnt + 1];
      if (patno == 255) {
        p_actwk->patcnt = 0;
        patno = p_chg[1];
      }
      p_actwk->patno = patno + patno_add;
      if (p_actwk->pattim-- == 0) {
        cal_speed = -cal_speed + 0x800;
        if (cal_speed < 0) {
          cal_speed = 0;
        }
        p_actwk->pattim = cal_speed / 0x100;
        ++p_actwk->patcnt;
      }
    }
  }
}


static void vsfoxflipchg(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.hflip = 0;
  p_actwk->actflg.vflip = 0;
  if (p_actwk->u.play.cddat.left == 0) {
    p_actwk->patno = (p_actwk->direc.b.b1 + 22 & 0xFF) / 44 + 21;
    p_actwk->pattim = 0;
  }
  else {
    unsigned char direction2 = p_actwk->direc.b.b1;
    if (p_actwk->u.play.flip_mst.reverse == 1) {
      p_actwk->actflg.hflip = 1;
      direction2 += 22;
    }
    else {
      p_actwk->actflg.hflip = 1;
      p_actwk->actflg.vflip = 1;
      direction2 = 256 - direction2 + 154;
    }
    direction2 &= 0xFF;
    p_actwk->patno = direction2 / 44 + 21;
    p_actwk->pattim = 0;
  }
}


static void vsfoxrunchg2(SKC_sprite_status* p_actwk, unsigned char patno) {
  if (p_actwk->pattim-- > 0) return;

  if (patno != 254) {
    vsfoxrunchg4(p_actwk);
  }
  else {
    short cal_speed = abs(p_actwk->mspeed);
    unsigned char* p_chg = cal_speed >= 0x600 ? vsfoxchg03 : vsfoxchg02;
    cal_speed = -cal_speed + 0x400;
    if (cal_speed < 0) {
      cal_speed = 0;
    }
    p_actwk->pattim = cal_speed / 0x100;
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
    p_actwk->actflg.vflip = 0;
    vsfoxpatchgmain2(p_actwk, p_chg);
  }
}


static void vsfoxrunchg3(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  short cal_speed = -abs(p_actwk->mspeed) + 0x800;
  if (cal_speed < 0) {
    cal_speed = 0;
  }
  cal_speed /= 0x40;
  p_actwk->pattim = cal_speed % 0x100;
  p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
  p_actwk->actflg.vflip = 0;
  vsfoxpatchgmain2(p_actwk, vsfoxchg04);
}


static void vsfoxrunchg4(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.play.ride_obj];
  unsigned char angle = atan(p_playerwk->xspeed, p_playerwk->yspeed);
  if (p_actwk->u.play.cddat.left == 0) {
    angle = 255 - angle;
  }
  else {
    angle += 128;
  }
  angle += 16;
  angle &= 0xFF;
  if (angle >= 128) {
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left ^ 1;
    p_actwk->actflg.vflip = 1;
  }
  else {
    p_actwk->actflg.hflip = p_actwk->u.play.cddat.left;
    p_actwk->actflg.vflip = 0;
  }
  unsigned char patno_add = (angle / 32 & 3) * 3;
  p_actwk->pattim = 3;
  vsfoxpatchgmain2(p_actwk, vsfoxtailschg02);
  p_actwk->patno += patno_add;
}


static unsigned char* vsfoxchg[33] = {
  vsfoxchg00,
  vsfoxchg01,
  vsfoxchg02,
  vsfoxchg03,
  vsfoxchg04,
  vsfoxchg05,
  vsfoxchg05,
  vsfoxchg05,
  vsfoxchg06,
  vsfoxchg07,
  vsfoxchg05,
  vsfoxchg05,
  vsfoxchg05,
  vsfoxchg08,
  vsfoxchg09,
  vsfoxchg10,
  vsfoxchg11,
  vsfoxchg12,
  vsfoxchg13,
  vsfoxchg14,
  vsfoxchg15,
  vsfoxchg16,
  vsfoxchg17,
  vsfoxchg18,
  vsfoxchg19,
  vsfoxchg20,
  vsfoxchg20,
  vsfoxchg21,
  vsfoxchg22,
  vsfoxchg23,
  vsfoxchg24,
  vsfoxchg25,
  vsfoxchg26
};


static unsigned char vsfoxchg00[6] = { 255, 1, 2, 3, 2, 255 };
static unsigned char vsfoxchg01[6] = { 255, 13, 14, 255, 255, 255 };
static unsigned char vsfoxchg02[5] = { 1, 40, 41, 42, 255 };
static unsigned char vsfoxchg03[5] = { 1, 40, 41, 42, 255 };
static unsigned char vsfoxchg04[6] = { 253, 37, 38, 255, 255, 255 };
static unsigned char vsfoxchg05[27] = {
  7, 27, 27, 27, 27, 27, 27, 27, 27, 28,
 28, 28, 28, 28, 28, 29, 30, 29, 30, 29,
 30, 29, 30, 29, 30, 254, 16
};
static unsigned char vsfoxchg06[3] = { 5, 43, 255 };
static unsigned char vsfoxchg07[4] = { 0, 35, 36, 255 };
static unsigned char vsfoxchg08[7] = { 5, 34, 34, 34, 34, 253, 0 };
static unsigned char vsfoxchg09[3] = { 7, 21, 255 };
static unsigned char vsfoxchg10[3] = { 7, 21, 255 };
static unsigned char vsfoxchg11[4] = { 47, 21, 253, 0 };
static unsigned char vsfoxchg12[3] = { 1, 21, 255 };
static unsigned char vsfoxchg13[3] = { 15, 31, 255 };
static unsigned char vsfoxchg14[3] = { 15, 31, 255 };
static unsigned char vsfoxchg15[3] = { 19, 21, 255 };
static unsigned char vsfoxchg16[3] = { 11, 21, 255 };
static unsigned char vsfoxchg17[3] = { 32, 32, 255 };
static unsigned char vsfoxchg18[3] = { 32, 32, 255 };
static unsigned char vsfoxchg19[3] = { 32, 32, 255 };
static unsigned char vsfoxchg20[3] = { 64, 33, 255 };
static unsigned char vsfoxchg21[3] = { 9, 33, 255 };
static unsigned char vsfoxchg22[3] = { 119, 0, 255 };
static unsigned char vsfoxchg23[3] = { 3, 27, 255 };
static unsigned char vsfoxchg24[3] = { 3, 27, 255 };
static unsigned char vsfoxchg25[6] = { 255, 13, 14, 255, 255, 255 };
static unsigned char vsfoxchg26[4] = { 1, 44, 45, 255 };


static void vsfoxtailswrt(SKC_sprite_status* p_actwk) {
  unsigned short* p_wrtpat = vsfoxtailswrtpat[p_actwk->patno];
  unsigned short cnt = *p_wrtpat++;
  unsigned short vram_adr = p_actwk == &g_ram.actwk[97] ? 0xD600 : 0xD200;
  foxwrt1(p_wrtpat, cnt, vram_adr, vsfoxtails_cg);
}


static void vsfoxwrt(SKC_sprite_status* p_playerwk) {
  unsigned short* p_wrtpat = vsfoxwrtpat[p_playerwk->patno];
  unsigned short cnt = *p_wrtpat++;
  unsigned short vram_adr = p_playerwk == &g_ram.actwk[0] ? 0xD000 : 0xD400;
  foxwrt1(p_wrtpat, cnt, vram_adr, vsfox_cg);
}


static void vsfoxwrt0(unsigned short* p_wrtpat, unsigned short cnt, unsigned short vram_adr, unsigned char* p_cg) {
  for (int i = 0; i < cnt; ++i) {
    unsigned short command = *p_wrtpat++;
    command = command << 8 | command >> 8;
    unsigned char* p_source = &p_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


static void foxtails(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = foxtailspat;
  p_actwk->sproffset = 0x06B0;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_ptr = &foxtailsmove;
  foxtailsmove(p_actwk);
}


static void foxtailsmove(SKC_sprite_status* p_actwk) {
  unsigned char mstno_tbl[50] = {
     0,  0,  3,  3,  9,  1,  0,  2,  1,  7,
     0,  0,  0,  8,  0,  0,  0,  0,  0,  0,
    10,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0, 11, 12, 11, 12, 11,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  };

  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.play.ride_obj];
  p_actwk->direc.b.b0 = p_playerwk->direc.b.b0;
  p_actwk->u.play.cddat = p_playerwk->u.play.cddat;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
  p_actwk->sprpri = p_playerwk->sprpri;
  CLEAR_BIT(p_actwk->sproffset, 15);
  if (BIT_IS_SET(p_playerwk->sproffset, 15)) {
    SET_BIT(p_actwk->sproffset, 15);
  }
  unsigned char mstno = p_playerwk->mstno;
  if (p_playerwk->u.play.cddat.push == 1 && g_ram.watercoliflag2 == 0
      && p_playerwk->mstno >= 169 && p_playerwk->mstno <= 172) {
    mstno = 4;
  }
  if (mstno != p_actwk->u.play.invulnerability_timer) {
    p_actwk->u.play.invulnerability_timer = mstno;
    p_actwk->mstno = mstno_tbl[mstno];
  }
  foxpatchgmain0(p_actwk, foxtailschg);
  if (g_ram.reverse_gravity_flag != 0 && p_actwk->mstno != 3) {
    p_actwk->actflg.vflip ^= 1;
  }
  foxtailswrt(p_actwk);
  actionsub(p_actwk);
}


static unsigned char* foxtailschg[13] = {
  foxtailschg00,
  foxtailschg01,
  foxtailschg02,
  foxtailschg03,
  foxtailschg04,
  foxtailschg05,
  foxtailschg06,
  foxtailschg07,
  foxtailschg08,
  foxtailschg09,
  foxtailschg10,
  foxtailschg11,
  foxtailschg12
};


static unsigned char foxtailschg00[3] = { 32, 0, 255 };
static unsigned char foxtailschg01[7] = { 7, 34, 35, 36, 37, 38, 255 };
static unsigned char foxtailschg02[8] = { 3, 34, 35, 36, 37, 38, 253, 1 };
static unsigned char foxtailschg03[6] = { 252, 5, 6, 7, 8, 255 };
static unsigned char foxtailschg04[6] = { 3, 9, 10, 11, 12, 255 };
static unsigned char foxtailschg05[6] = { 3, 13, 14, 15, 16, 255 };
static unsigned char foxtailschg06[6] = { 3, 17, 18, 19, 20, 255 };
static unsigned char foxtailschg07[6] = { 2, 1, 2, 3, 4, 255 };
static unsigned char foxtailschg08[6] = { 2, 26, 27, 28, 29, 255 };
static unsigned char foxtailschg09[6] = { 9, 30, 31, 32, 33, 255 };
static unsigned char foxtailschg10[6] = { 9, 41, 42, 43, 44, 255 };
static unsigned char foxtailschg11[4] = { 1, 39, 40, 255 };
static unsigned char foxtailschg12[4] = { 0, 39, 40, 255 };


static void vsfoxtails(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = vsfoxtailspat;
  p_actwk->sproffset = p_actwk == &g_ram.actwk[ACTWK_MILES_TAILS] ? 0x06B0 : 0x0690;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_ptr = &vsfoxtailsmove;
}


static void vsfoxtailsmove(SKC_sprite_status* p_actwk) {
  unsigned char mstno_tbl[33] = {
    0, 0, 3, 3, 0, 1, 1, 1, 1, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0
  };

  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.play.ride_obj];
  p_actwk->direc.b.b0 = p_playerwk->direc.b.b0;
  p_actwk->u.play.cddat = p_playerwk->u.play.cddat;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
  p_actwk->sprpri = p_playerwk->sprpri;
  CLEAR_BIT(p_actwk->sproffset, 15);
  if (BIT_IS_SET(p_playerwk->sproffset, 15)) {
    SET_BIT(p_actwk->sproffset, 15);
  }
  unsigned char mstno = p_playerwk->mstno;
  if (p_playerwk->u.play.cddat.push == 1 && mstno != 5) {
    mstno = 4;
  }
  if (mstno != p_actwk->u.play.invulnerability_timer) {
    p_actwk->u.play.invulnerability_timer = mstno;
    p_actwk->mstno = mstno_tbl[mstno];
  }
  vsfoxpatchgmain0(p_actwk, vsfoxtailschg);
  vsfoxtailswrt(p_actwk);
  actionsub(p_actwk);
}


static unsigned char* vsfoxtailschg[4] = {
  vsfoxtailschg00,
  vsfoxtailschg01,
  vsfoxtailschg01,
  vsfoxtailschg02
};


static unsigned char vsfoxtailschg00[3] = { 32, 0, 255 };
static unsigned char vsfoxtailschg01[5] = { 7, 1, 2, 3, 255 };
static unsigned char vsfoxtailschg02[5] = { 252, 4, 5, 6, 255 };


void ev0201(SKC_sprite_status* p_actwk) {
  short xposi = (g_ram.scra_h_posit >> 16) + 64;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (g_ram.scra_v_posit >> 16) + 256;
  p_actwk->u.obj.timer = 360;
  fp16_set_integer(&p_actwk->yposi, yposi);
  if (g_ram.play_type != PLAY_TYPE_MILES) {
    SKC_sprite_status* p_foxwk = &g_ram.actwk[1];
    if (p_foxwk->actflg.onscreen == 0) {
      fp16_set_integer(&p_foxwk->xposi, fp16_get_integer(p_actwk->xposi));
      fp16_set_integer(&p_foxwk->yposi, fp16_get_integer(p_actwk->yposi));
      fp16_set_integer(&p_foxwk->yposi, fp16_get_integer(p_foxwk->yposi) - 1);
      g_ram.actwk[1].r_ptr = &fox00;
      g_ram.foxcpu_rno = 18;
      g_ram.miles_carry_flag = 0;
    }

    p_actwk->r_ptr = &ev0201_sub;
  }
  else {
    p_actwk->r_ptr = &ev0201_sub1;
  }
  p_actwk->r_ptr(p_actwk);
}


static void ev0201_sub(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->r_ptr = &ev0201_sub0;
  }
  ev0201_sub0(p_actwk);
}


static void ev0201_sub0(SKC_sprite_status* p_actwk) {
  if (g_ram.miles_carry_flag == 0) {
    SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi));
      p_playerwk->xspeed = 0;
      p_playerwk->yspeed = 0;
      p_playerwk->mspeed = 0;
      p_playerwk->u.play.spindash_flag = 0;
      if (g_ram.foxcpu_rno >= 20) {
        fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
      }
      p_playerwk->r_no = 2;
    }
  }
  if (g_ram.actwk[0].actflg.onscreen == 0 && g_ram.actwk[0].r_no == 2) {
    SKC_sprite_status* p_foxwk = &g_ram.actwk[1];
    if ((unsigned short)fp16_get_integer(p_foxwk->yposi) < (unsigned short)fp16_get_integer(p_actwk->yposi)) {
      g_ram.foxcpu_rno = 18;
      if (p_actwk->u.obj.timer == 0) {
        fp16_set_integer(&p_foxwk->xposi, fp16_get_integer(p_actwk->xposi));
        p_foxwk->r_no = 2;
        p_foxwk->u.play.control_bitfield = 0;
        p_foxwk->u.play.spindash_flag = 0;
        fp16_set_integer(&p_foxwk->xposi, fp16_get_integer(p_actwk->xposi));
        g_ram.foxcpu_rno = 20;
      }
    }
  }
}


static void ev0201_sub1(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->r_ptr = &ev0201_sub2;
    fp16_set_integer(&g_ram.actwk[0].xposi, fp16_get_integer(p_actwk->xposi));
  }
  ev0201_sub2(p_actwk);
}


static void ev0201_sub2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi));
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 8);
    if (p_actwk->u.obj.timer == 0) {
      p_playerwk->r_no = 2;
      p_playerwk->u.play.control_bitfield = 0;
      p_playerwk->u.play.spindash_flag = 0;
      g_ram.foxcpu_rno = 26;
    }
  }
}
