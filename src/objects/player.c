#include "player.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../data/vsplaydata.h"
#include "../data/cg/knuckles.h"
#include "../data/cg/play.h"
#include "../data/pat/knuckles.h"
#include "../data/pat/play.h"
#include "../data/wrt/knuckles.h"
#include "../data/wrt/play.h"
#include "../types/playwork.h"
#include "../types/sonic3ram.h"
#include "../types/speed.h"
#include "../types/spritestatus.h"
#include "../types/swdata.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/fp8.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../coli.h"
#include "../constants.h"
#include "../dev.h"
#include "../dircol.h"
#include "../edit.h"
#include "../etc.h"
#include "../fcol.h"
#include "../sound.h"
#include "fox.h"
#include "knuckles.h"
#include "zone.h"
static void vsplayinit(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsplaymove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsplaywalk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsplayjump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsballwalk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsballjump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void vsballchk(SKC_sprite_status* p_playerwk);
static void vsballset(SKC_sprite_status* p_playerwk);
static bool vsspinchk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00init(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00move(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void playpowercnt(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void plwaterchk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00walk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00jump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void ball00walk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void ball00jump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void levermove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void lmovecol(SKC_sprite_status* p_playerwk);
static void plwalk_l(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void plwalk_r(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void balllmove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void ballwalk_l(SKC_sprite_status* p_playerwk, short plretspdwk);
static void ballwalk_r(SKC_sprite_status* p_playerwk, short plretspdwk);
static void jumpmove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void limitset(SKC_sprite_status* p_playerwk, short cal_limit);
static void ballset(SKC_sprite_status* p_playerwk);
static bool jumpchk(SKC_sprite_status* p_playerwk);
static void jumpchk2(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void jumpchk3(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void playsupercnt0(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void jumpcolsub(SKC_sprite_status* p_playerwk);
static void jumpcolsub1(SKC_sprite_status* p_playerwk);
static void aqua_baria_bounce(SKC_sprite_status* p_playerwk);
static void play00damage(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00damage_sub(SKC_sprite_status* p_playerwk);
static void play00die(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00erase(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00appear(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void play00drown(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void patchgmainwrt(SKC_sprite_status* p_playerwk);
static void patchgmain(SKC_sprite_status* p_playerwk);
static void patchgmain2(SKC_sprite_status* p_playerwk, unsigned char* p_chg);
static void playrunchg(SKC_sprite_status* p_playerwk, unsigned char patno);
static void playrunchg2(SKC_sprite_status* p_playerwk);
static void playrunchg3(SKC_sprite_status* p_playerwk);
static unsigned char* playchg[36];
static unsigned char plchg00[10];
static unsigned char plchg01[10];
static unsigned char plchg02[10];
static unsigned char plchg03[10];
static unsigned char plchg04[10];
static unsigned char plchg05[109];
static unsigned char plchg06[5];
static unsigned char plchg07[5];
static unsigned char plchg08[5];
static unsigned char plchg09[12];
static unsigned char plchg10[23];
static unsigned char plchg11[3];
static unsigned char plchg12[5];
static unsigned char plchg13[7];
static unsigned char plchg14[3];
static unsigned char plchg15[10];
static unsigned char plchg16[4];
static unsigned char plchg17[4];
static unsigned char plchg18[6];
static unsigned char plchg19[14];
static unsigned char plchg20[3];
static unsigned char plchg21[7];
static unsigned char plchg22[3];
static unsigned char plchg23[3];
static unsigned char plchg24[3];
static unsigned char plchg25[4];
static unsigned char plchg26[3];
static unsigned char plchg27[4];
static unsigned char plchg28[3];
static unsigned char plchg29[4];
static unsigned char plchg30[8];
static unsigned char plchg31[4];
static unsigned char plchg32[4];
static unsigned char plchg33[6];
static unsigned char plchg34[10];
static unsigned char* ssonicchg[32];
static unsigned char splaychg00[10];
static unsigned char splaychg01[10];
static unsigned char splaychg02[10];
static unsigned char splaychg03[4];
static unsigned char splaychg04[5];
static unsigned char splaychg05[3];
static unsigned char splaychg06[16];
static void playwrt0(unsigned char patno);
static void vspatchgmain(SKC_sprite_status* p_playerwk);
static void vspatchgmain2(SKC_sprite_status* p_playerwk, unsigned char* p_chg);
static void vsplayrunchg(SKC_sprite_status* p_playerwk, unsigned char patno);
static void vsplayflipchg(SKC_sprite_status* p_playerwk);
static void vsplayrunchg2(SKC_sprite_status* p_playerwk);
static void vsplayrunchg3(SKC_sprite_status* p_playerwk);
static unsigned char* vsplaychg[36];
static unsigned char* vsknuckleschg[36];
static unsigned char vsplchg00[6];
static unsigned char vsplchg01[6];
static unsigned char vsplchg02[6];
static unsigned char vsplchg03[6];
static unsigned char vsplchg04[6];
static unsigned char vsplchg05[6];
static unsigned char vsplchg06[27];
static unsigned char vsplchg07[3];
static unsigned char vsplchg08[4];
static unsigned char vsplchg09[7];
static unsigned char vsplchg10[3];
static unsigned char vsplchg11[3];
static unsigned char vsplchg12[4];
static unsigned char vsplchg13[3];
static unsigned char vsplchg14[3];
static unsigned char vsplchg15[3];
static unsigned char vsplchg16[3];
static unsigned char vsplchg17[3];
static unsigned char vsplchg18[3];
static unsigned char vsplchg19[3];
static unsigned char vsplchg20[3];
static unsigned char vsplchg21[3];
static unsigned char vsplchg22[3];
static unsigned char vsplchg23[3];
static unsigned char vsplchg24[3];
static unsigned char vsplchg25[4];
static unsigned char vsplchg26[3];
static unsigned char vsplchg27[4];
static void vsplaywrt(SKC_sprite_status* p_playerwk);

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void vsplay(SKC_sprite_status* p_playerwk) {
  void(*act_tbl[6])(SKC_sprite_status*, SKC_play_work) = {
    &vsplayinit,
    &vsplaymove,
    &play00damage,
    &play00die,
    &play00erase,
    &play00appear
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


static void vsplayinit(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  p_playerwk->r_no += 2;
  p_playerwk->sprvsize = 11;
  p_playerwk->sprhsize = 5;
  p_playerwk->u.play.height = 11;
  p_playerwk->u.play.width = 5;
  p_playerwk->sprpri = PRI_2;
  p_playerwk->sprhs = 12;
  p_playerwk->sprvs = 12;
  p_playerwk->actflg.relative_coordinates = 1;
  *work.plmaxspdwk_ptr = vsplaydata[p_playerwk->u.play.character][0];
  *work.pladdspdwk_ptr = vsplaydata[p_playerwk->u.play.character][1];
  *work.plretspdwk_ptr = vsplaydata[p_playerwk->u.play.character][2];
  if (g_ram.markerno == 0) {
    p_playerwk->u.play.top_solid_bit = 12;
    p_playerwk->u.play.lrb_solid_bit = 13;
    p_playerwk->sproffset = p_playerwk == &g_ram.actwk[0] ? 0x0680 : 0x06A0;
    if (p_playerwk->u.play.character != SONIC) {
      p_playerwk->sproffset += 0x2000;
    }
    if (get_zone(g_ram.stageno) == ENDLESS_MINE) {
      SET_BIT(p_playerwk->sproffset, 15);
    }
    p_playerwk->patbase = p_playerwk->u.play.character == SONIC ? vsplaypat : vsknucklespat;
    if (p_playerwk == &g_ram.actwk[0]) {
      g_ram.plxposi_s = fp16_get_integer(p_playerwk->xposi);
      g_ram.plyposi_s = fp16_get_integer(p_playerwk->yposi);
      g_ram.plsproffset_s = p_playerwk->sproffset;
      g_ram.pl_top_solid_bit_s = p_playerwk->u.play.top_solid_bit;
      g_ram.pl_lrb_solid_bit_s = p_playerwk->u.play.lrb_solid_bit;
    }
    else {
      g_ram.plxposi_s2 = fp16_get_integer(p_playerwk->xposi);
      g_ram.plyposi_s2 = fp16_get_integer(p_playerwk->yposi);
      g_ram.plsproffset_s2 = p_playerwk->sproffset;
      g_ram.pl_top_solid_bit_s2 = p_playerwk->u.play.top_solid_bit;
      g_ram.pl_lrb_solid_bit_s2 = p_playerwk->u.play.lrb_solid_bit;
    }
  }
  p_playerwk->u.play.flip_rev_cnt = 0;
  p_playerwk->u.play.flip_rev_frame_cnt = 4;
  g_ram.ssonicflag = 0;
  p_playerwk->u.play.air_timer = 30;
  playposiwkinit(p_playerwk);
  vsplaymove(p_playerwk, work);
}


static void vsplaymove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  void(*act_tbl[4])(SKC_sprite_status*, SKC_play_work) = {
    &vsplaywalk,
    &vsplayjump,
    &vsballwalk,
    &vsballjump
  };

  if (g_ram.debugflag != 0 && p_playerwk == &g_ram.actwk[0] && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    if (p_playerwk == &g_ram.actwk[0]) {
      if (g_ram.pl_input_lock_flag == 0) {
        g_ram.swdata = g_ram.swdata1;
      }
    }
    else {
      if (g_ram.pl2_input_lock_flag == 0) {
        g_ram.swdata = g_ram.swdata2;
      }
    }
    playpowercnt(p_playerwk, work);
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
      vspatchgmain(p_playerwk);
      vsplaywrt(p_playerwk);
    }
    if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 5)
        && !BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) {
      vspcol(p_playerwk);
    }
  }
}


static void vsplaywalk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  bool skip_move = false;
  if (!are_any_trg_buttons_used(g_ram.swdata.pressed)) {
    switch (p_playerwk->mstno) {
      case 10:
      case 11:
        return;
      case 5:
        if (p_playerwk->patcnt >= 30) {
          keispd(p_playerwk);
          if (are_any_dir_buttons_used(g_ram.swdata.down) || are_any_trg_buttons_used(g_ram.swdata.down)) {
            p_playerwk->mstno = p_playerwk->patcnt < 172 ? 10 : 11;
          }
          skip_move = true;
        }
        break;
    }
  }
  if (!skip_move) {
    if (vsspinchk(p_playerwk, work) || jumpchk(p_playerwk)) return;
    keispd(p_playerwk);
    levermove(p_playerwk, work);
    vsballchk(p_playerwk);
    speedset2(p_playerwk);
  }
  fcol(p_playerwk);
  fallchk(p_playerwk);
}


static void vsplayjump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  jumpchk2(p_playerwk, work);
  jumpmove(p_playerwk, work);
  speedset(p_playerwk);
  if (p_playerwk->u.play.cddat.underwater == 1) {
    p_playerwk->yspeed -= 0x28;
  }
  direcchg(p_playerwk);
  jumpcolchk(p_playerwk);
}


static void vsballwalk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.spindash_flag == 0 && jumpchk(p_playerwk)) return;

  keispd2(p_playerwk);
  balllmove(p_playerwk, work);
  speedset2(p_playerwk);
  fcol(p_playerwk);
  fallchk(p_playerwk);
}


static void vsballjump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  jumpchk2(p_playerwk, work);
  jumpmove(p_playerwk, work);
  speedset(p_playerwk);
  if (p_playerwk->u.play.cddat.underwater == 1) {
    p_playerwk->yspeed -= 0x28;
  }
  direcchg(p_playerwk);
  jumpcolchk(p_playerwk);
}


static void vsballchk(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.powerdat.mizuflag == 1) return;
  if (abs(p_playerwk->mspeed < 0x80)) return;
  if (g_ram.swdata.down.l == 1 || g_ram.swdata.down.r == 1) return;
  if (g_ram.swdata.down.d == 0) return;

  vsballset(p_playerwk);
}


static void vsballset(SKC_sprite_status* p_playerwk) {
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


static bool vsspinchk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short spd_tbl[9] = {
    0x800, 0x880, 0x900, 0x980, 0xA00, 0xA80, 0xB00, 0xB80, 0xC00
  };
  short spd_tbl2[9] = {
    0xB00, 0xB80, 0xC00, 0xC80, 0xD00, 0xD80, 0xE00, 0xE80, 0xF00
  };

  if (p_playerwk->u.play.spindash_flag == 0) {
    if (p_playerwk->mstno == 8 && are_any_trg_buttons_used(g_ram.swdata.pressed)) {
      p_playerwk->mstno = 9;
      soundset(-85);
      p_playerwk->u.play.spindash_flag = 1;
      p_playerwk->u.play.spindash_ctr = 0;
      if (p_playerwk->u.play.air_timer >= 12) {
        work.effectwk_ptr->mstno = 2;
      }
      fcol(p_playerwk);
      return true;
    }
  }
  else {
    if (g_ram.swdata.down.d == 0) {
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
        p_playerwk->u.play.spindash_ctr -= p_playerwk->u.play.spindash_ctr / 32;
        if (p_playerwk->u.play.spindash_ctr < 0) {
          p_playerwk->u.play.spindash_ctr = 0;
        }
      }
      if (are_any_trg_buttons_used(g_ram.swdata.pressed)) {
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


void play00(SKC_sprite_status* p_playerwk) {
  void(*play00_move_tbl[7])(SKC_sprite_status*, SKC_play_work) = {
    &play00init,
    &play00move,
    &play00damage,
    &play00die,
    &play00erase,
    &play00appear,
    &play00drown
  };

  if (g_ram.editmode != 0) {
    if ((g_ram.editmode & 0xFF) != 1) {
      if (g_ram.swdata1.pressed.b == 1) {
        g_ram.editmode = 0;
      }
      ++p_playerwk->patno;
      if (p_playerwk->patno >= 251) {
        p_playerwk->patno = 0;
      }
      playwrt(p_playerwk);
      actionsub(p_playerwk);
    }
    else {
      edit(p_playerwk);
    }
  }
  else {
    SKC_play_work work = {
      &g_ram.plmaxspdwk,
      &g_ram.pladdspdwk,
      &g_ram.plretspdwk,
      &g_ram.scra_vline,
      &g_ram.actwk[ACTWK_PL_EFFECT]
    };
    play00_move_tbl[p_playerwk->r_no / 2](p_playerwk, work);
  }
}


static void play00init(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  p_playerwk->r_no += 2;
  p_playerwk->sprvsize = 19;
  p_playerwk->sprhsize = 9;
  p_playerwk->u.play.height = 19;
  p_playerwk->u.play.width = 9;
  p_playerwk->patbase = playpat;
  p_playerwk->sprpri = PRI_2;
  p_playerwk->sprhs = 24;
  p_playerwk->sprvs = 24;
  p_playerwk->actflg.relative_coordinates = 1;
  p_playerwk->u.play.character = SONIC;
  *work.plmaxspdwk_ptr = 0x600;
  *work.pladdspdwk_ptr = 0xC;
  *work.plretspdwk_ptr = 0x80;
  if (g_ram.markerno == 0) {
    p_playerwk->sproffset = 0x0680;
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
  p_playerwk->u.play.flip_rev_cnt = 0;
  p_playerwk->u.play.flip_rev_frame_cnt = 4;
  g_ram.ssonicflag = 0;
  p_playerwk->u.play.air_timer = 30;
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 32);
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 4);
  playposiwkinit(p_playerwk);
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 32);
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 4);
}


static void play00move(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  void(*play00_move_tbl[4])(SKC_sprite_status*, SKC_play_work) = {
    &play00walk,
    &play00jump,
    &ball00walk,
    &ball00jump
  };

  if (g_ram.debugflag != 0) {
    if (g_ram.swdata1.pressed.a == 1) {
      g_ram.swdata1.pressed.a = 0;
      g_ram.reverse_gravity_flag ^= 1;
    }
    if (g_ram.swdata1.pressed.b == 1) {
      g_ram.editmode = 1;
      g_ram.pl_input_lock_flag = 0;
      if (g_ram.swdata1.down.c == 1) {
        g_ram.editmode = 2;
      }
      return;
    }
  }
  if (g_ram.pl_input_lock_flag == 0) {
    g_ram.swdata = g_ram.swdata1;
  }
  if (BIT_IS_SET(p_playerwk->u.play.control_bitfield, 0)) {
    p_playerwk->u.play.talent_status = 0;
  }
  else {
    unsigned char index = p_playerwk->u.play.cddat.jump + p_playerwk->u.play.cddat.ball * 2;
    play00_move_tbl[index](p_playerwk, work);
  }
  if (g_ram.scralim_up == -256) {
    short yposi = (unsigned short)fp16_get_integer(p_playerwk->yposi) & g_ram.scrc_v;
    fp16_set_integer(&p_playerwk->yposi, yposi);
  }
  playpowercnt(p_playerwk, work);
  playsupercnt(p_playerwk, work);
  playposiwkset(p_playerwk);
  plwaterchk(p_playerwk, work);
  p_playerwk->u.play.angle_front = g_ram.dirstk[0];
  p_playerwk->u.play.angle_below = g_ram.dirstk[2];
  if (g_ram.watercoliflag != 0 && p_playerwk->mstno == 0) {
    p_playerwk->mstno = p_playerwk->mstrestart;
  }
  if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 1)) {
    patchgmain(p_playerwk);
    if (g_ram.reverse_gravity_flag != 0) {
      p_playerwk->actflg.vflip ^= 1;
    }
    playwrt(p_playerwk);
  }
  if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 5)
      && !BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) {
    pcol(p_playerwk);
  }
}


static void playpowercnt(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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
        *work.plmaxspdwk_ptr = g_ram.ssonicflag == 0 ? 0x600 : 0xA00;
        *work.pladdspdwk_ptr = g_ram.ssonicflag == 0 ? 0xC : 0x30;
        *work.plretspdwk_ptr = g_ram.ssonicflag == 0 ? 0x80 : 0x100;
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


void playposiwkset(SKC_sprite_status* p_playerwk) {
  if (g_ram.vs_flag == 0 && p_playerwk == &g_ram.actwk[0]) return;

  if (g_ram.vs_flag == 0) {
    g_ram.playposiwk[g_ram.plposiwkadr].x = fp16_get_integer(p_playerwk->xposi);
    g_ram.playposiwk[g_ram.plposiwkadr].y = fp16_get_integer(p_playerwk->yposi);
    g_ram.playrecwk[g_ram.plposiwkadr].swdata = g_ram.swdata;
    g_ram.playrecwk[g_ram.plposiwkadr].cddat = p_playerwk->u.play.cddat;
    g_ram.playrecwk[g_ram.plposiwkadr].sprdat = p_playerwk->sproffset >> 8;
    ++g_ram.plposiwkadr;
  }
  else {
    if (p_playerwk == &g_ram.actwk[0]) {
      g_ram.playposiwk[g_ram.plposiwkadr].x = fp16_get_integer(p_playerwk->xposi);
      g_ram.playposiwk[g_ram.plposiwkadr].y = fp16_get_integer(p_playerwk->yposi);
      ++g_ram.plposiwkadr;
    }
    else {
      g_ram.play2posiwk[g_ram.pl2posiwkadr].x = fp16_get_integer(p_playerwk->xposi);
      g_ram.play2posiwk[g_ram.pl2posiwkadr].y = fp16_get_integer(p_playerwk->yposi);
      ++g_ram.pl2posiwkadr;
    }
  }
}


void playposiwkinit(SKC_sprite_status* p_playerwk) {
  if (p_playerwk == &g_ram.actwk[0]) {
    for (int i = 0; i < 64; ++i) {
      g_ram.playposiwk[i].x = fp16_get_integer(p_playerwk->xposi);
      g_ram.playposiwk[i].y = fp16_get_integer(p_playerwk->yposi);
    }

    memset(g_ram.playrecwk, 0, sizeof(g_ram.playrecwk));
    g_ram.plposiwkadr = 0;
  }
  if (g_ram.vs_flag != 0) {
    for (int i = 0; i < 64; ++i) {
      g_ram.play2posiwk[i].x = fp16_get_integer(p_playerwk->xposi);
      g_ram.play2posiwk[i].y = fp16_get_integer(p_playerwk->yposi);
    }

    g_ram.pl2posiwkadr = 0;
  }
}


static void plwaterchk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.watermode == 0) return;

  if (g_ram.waterposi < fp16_get_integer(p_playerwk->yposi)) {
    if (p_playerwk->u.play.cddat.underwater == 0) {
      p_playerwk->u.play.cddat.underwater = 1;
      ++g_ram.water_flag;
      plairset(p_playerwk);
      g_ram.actwk[ACTWK_PL_AWA].r_ptr = &plawa;
      g_ram.actwk[ACTWK_PL_AWA].u.obj.userflag = 129;
      g_ram.actwk[ACTWK_PL_AWA].u.obj.ko = p_playerwk - g_ram.actwk;
      *work.plmaxspdwk_ptr = g_ram.ssonicflag == 0 ? 0x300 : 0x500;
      *work.pladdspdwk_ptr = g_ram.ssonicflag == 0 ? 6 : 0x18;
      *work.plretspdwk_ptr = g_ram.ssonicflag == 0 ? 0x40 : 0x80;
      if (p_playerwk->u.play.control_bitfield == 0) {
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
      *work.plmaxspdwk_ptr = g_ram.ssonicflag == 0 ? 0x600 : 0xA00;
      *work.pladdspdwk_ptr = g_ram.ssonicflag == 0 ? 0xC : 0x30;
      *work.plretspdwk_ptr = g_ram.ssonicflag == 0 ? 0x80 : 0x100;
      if (p_playerwk->r_no != 4 && p_playerwk->u.play.control_bitfield == 0 && p_playerwk->yspeed >= -0x400) {
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


static void play00walk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (spinchk(p_playerwk, work) || jumpchk(p_playerwk)) return;

  keispd(p_playerwk);
  levermove(p_playerwk, work);
  ballchk(p_playerwk);
  limitchk(p_playerwk);
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


void fcol_g(SKC_sprite_status* p_playerwk) {
  if (g_ram.reverse_gravity_flag == 0) {
    fcol(p_playerwk);
  }
  else {
    p_playerwk->direc.b.b0 = (256 - (p_playerwk->direc.b.b0 + 64) - 64) & 0xFF;
    fcol(p_playerwk);
    p_playerwk->direc.b.b0 = (256 - (p_playerwk->direc.b.b0 + 64) - 64) & 0xFF;
  }
}


static void play00jump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  jumpchk2(p_playerwk, work);
  jumpmove(p_playerwk, work);
  limitchk(p_playerwk);
  speedset_g(p_playerwk);
  if (p_playerwk->u.play.cddat.underwater == 1) {
    p_playerwk->yspeed -= 0x28;
  }
  direcchg(p_playerwk);
  jumpcolchk(p_playerwk);
}


static void ball00walk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.spindash_flag == 0 && jumpchk(p_playerwk)) return;

  keispd2(p_playerwk);
  balllmove(p_playerwk, work);
  limitchk(p_playerwk);
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


static void ball00jump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  jumpchk2(p_playerwk, work);
  jumpmove(p_playerwk, work);
  limitchk(p_playerwk);
  speedset_g(p_playerwk);
  if (p_playerwk->u.play.cddat.underwater == 1) {
    p_playerwk->yspeed -= 0x28;
  }
  direcchg(p_playerwk);
  jumpcolchk(p_playerwk);
}


static void levermove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.powerdat.mizuflag == 0) {
    bool looking = false;
    bool skip_center = false;
    if (p_playerwk->u.play.hlock_timer == 0) {
      if (g_ram.swdata.down.l == 1) {
        plwalk_l(p_playerwk, work);
      }
      if (g_ram.swdata.down.r == 1) {
        plwalk_r(p_playerwk, work);
      }
      if (!(p_playerwk->direc.b.b0 + 32 & 0xC0) && p_playerwk->mspeed == 0) {
        p_playerwk->u.play.cddat.push = 0;
        p_playerwk->mstno = 5;
        bool balancing = false;
        if (p_playerwk->u.play.cddat.ride == 1) {
          SKC_sprite_status* p_ride_obj = &g_ram.actwk[p_playerwk->u.play.ride_obj];
          if (p_ride_obj->u.obj.cddat.die == 0) {
            unsigned char sprhs = p_ride_obj->sprhs * 2 - 2;
            short distance = (short)p_ride_obj->sprhs + fp16_get_integer(p_playerwk->xposi)
                           - fp16_get_integer(p_ride_obj->xposi);
            if (g_ram.ssonicflag == 0) {
              if (distance >= 2) {
                if (distance >= (short)sprhs) {
                  if (p_playerwk->u.play.cddat.left == 0) {
                    p_playerwk->mstno = 6;
                    sprhs += 6;
                    if (distance >= (short)sprhs) {
                      p_playerwk->mstno = 12;
                    }
                  }
                  else {
                    p_playerwk->u.play.cddat.left = 0;
                    p_playerwk->mstno = 6;
                    sprhs += 6;
                    if (distance >= (short)sprhs) {
                      p_playerwk->mstno = 12;
                    }
                  }
                  balancing = true;
                }
              }
              else {
                if (p_playerwk->u.play.cddat.left == 1) {
                  p_playerwk->mstno = 6;
                  if (distance < -4) {
                    p_playerwk->mstno = 12;
                  }
                }
                else {
                  p_playerwk->u.play.cddat.left = 1;
                  p_playerwk->mstno = 6;
                  if (distance < -4) {
                    p_playerwk->mstno = 12;
                  }
                }
                balancing = true;
              }
            }
            else {
              if (distance >= 2) {
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
        }
        else {
          SKC_dircol_result result = edgechk_d2_g(p_playerwk, fp16_get_integer(p_playerwk->xposi));
          if (result.offset >= 12) {
            if (g_ram.ssonicflag == 0) {
              if (p_playerwk->u.play.angle_front == 3) {
                if (p_playerwk->u.play.cddat.left == 0) {
                  p_playerwk->mstno = 6;
                  result = edgechk_d2_g(p_playerwk, fp16_get_integer(p_playerwk->xposi) - 6);
                  if (result.offset >= 12) {
                    p_playerwk->mstno = 12;
                  }
                }
                else {
                  p_playerwk->u.play.cddat.left = 0;
                  p_playerwk->mstno = 6;
                  result = edgechk_d2_g(p_playerwk, fp16_get_integer(p_playerwk->xposi) - 6);
                  if (result.offset >= 12) {
                    p_playerwk->mstno = 12;
                  }
                }
                balancing = true;
              }
              else if (p_playerwk->u.play.angle_below == 3) {
                if (p_playerwk->u.play.cddat.left == 1) {
                  p_playerwk->mstno = 6;
                  result = edgechk_d2_g(p_playerwk, fp16_get_integer(p_playerwk->xposi) + 6);
                  if (result.offset >= 12) {
                    p_playerwk->mstno = 12;
                  }
                }
                else {
                  p_playerwk->u.play.cddat.left = 1;
                  p_playerwk->mstno = 6;
                  result = edgechk_d2_g(p_playerwk, fp16_get_integer(p_playerwk->xposi) + 6);
                  if (result.offset >= 12) {
                    p_playerwk->mstno = 12;
                  }
                }
                balancing = true;
              }
            }
            else {
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
        }
        if (!balancing) {
          if (g_ram.swdata.down.d == 1) {
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
          else if (g_ram.swdata.down.u == 1) {
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
    if (g_ram.swdata.down.l == 0 && g_ram.swdata.down.r == 0) {
      if (p_playerwk->mspeed != 0) {
        short pladdspdwk = g_ram.ssonicflag == 0 ? *work.pladdspdwk_ptr : 0xC;
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
  lmovecol(p_playerwk);
}


static void lmovecol(SKC_sprite_status* p_playerwk) {
  if (BIT_IS_SET(p_playerwk->u.play.control_bitfield, 6)) return;
  if ((p_playerwk->direc.b.b0 & 0x3F) && (p_playerwk->direc.b.b0 + 64 & 0xFF) >= 128) return;
  if (p_playerwk->mspeed == 0) return;

  unsigned char add_dir = p_playerwk->mspeed >= 0 ? 64 : 192;
  unsigned char sonic_dir = p_playerwk->direc.b.b0 + add_dir;
  sonic_dir &= 0xFF;
  SKC_dircol_result result = dircolm(p_playerwk, sonic_dir);
  if (result.offset < 0) {
    short add_speed = result.offset * 0x100;
    if (get_zone(g_ram.stageno) == SANDOPOLIS && sonic_dir >= 128) {
      --sonic_dir;
    }
    sonic_dir += 32;

    switch (sonic_dir & 0xC0) {
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


static void plwalk_l(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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


static void plwalk_r(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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


static void balllmove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short pladdspdwk = *work.pladdspdwk_ptr / 2;
  short plretspdwk = 0x20;
  if (!BIT_IS_SET(p_playerwk->u.play.spindash_flag, 7) && p_playerwk->u.play.powerdat.mizuflag == 0) {
    if (p_playerwk->u.play.hlock_timer == 0) {
      if (g_ram.swdata.down.l == 1) {
        ballwalk_l(p_playerwk, plretspdwk);
      }
      if (g_ram.swdata.down.r == 1) {
        ballwalk_r(p_playerwk, plretspdwk);
      }
    }
    if (g_ram.ssonicflag != 0) {
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
  lmovecol(p_playerwk);
}


static void ballwalk_l(SKC_sprite_status* p_playerwk, short plretspdwk) {
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


static void ballwalk_r(SKC_sprite_status* p_playerwk, short plretspdwk) {
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


static void jumpmove(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short pladdspdwk = *work.pladdspdwk_ptr * 2;
  if (p_playerwk->u.play.cddat.ballj == 0) {
    short cal_speed = p_playerwk->xspeed;
    if (g_ram.swdata.down.l == 1) {
      p_playerwk->u.play.cddat.left = 1;
      cal_speed -= pladdspdwk;
      if (cal_speed <= -*work.plmaxspdwk_ptr) {
        cal_speed += pladdspdwk;
        if (cal_speed > -*work.plmaxspdwk_ptr) {
          cal_speed = -*work.plmaxspdwk_ptr;
        }
      }
    }
    if (g_ram.swdata.down.r == 1) {
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


void limitchk(SKC_sprite_status* p_playerwk) {
  long cal_position = p_playerwk->xposi + p_playerwk->xspeed * 0x100;
  short cal_limit_l = g_ram.scralim_left + 16;
  if (cal_limit_l > fp16_get_integer(cal_position)) {
    limitset(p_playerwk, cal_limit_l);
  }
  else {
    short cal_limit_r = g_ram.scralim_right + 296;
    if (cal_limit_r >= fp16_get_integer(cal_position)) {
      limitset(p_playerwk, cal_limit_r);
    }
  }
  if (g_ram.DAT_08fff665 == 0) {
    if ((g_ram.reverse_gravity_flag == 0 && g_ram.scralim_down + 224 < fp16_get_integer(p_playerwk->yposi))
        || (g_ram.reverse_gravity_flag != 0 && g_ram.scralim_up >= fp16_get_integer(p_playerwk->yposi))) {
      playdieset(p_playerwk);
    }
  }
}


static void limitset(SKC_sprite_status* p_playerwk, short cal_limit) {
  fp16_set_integer(&p_playerwk->xposi, cal_limit);
  fp16_set_fraction(&p_playerwk->xposi, 0);
  p_playerwk->xspeed = 0;
  p_playerwk->mspeed = 0;
}


void ballchk(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.powerdat.mizuflag == 1) return;
  if (g_ram.swdata.down.l == 1 || g_ram.swdata.down.r == 1) return;

  if (g_ram.swdata.down.d == 1) {
    if (abs(p_playerwk->mspeed) >= 0x100) {
      ballset(p_playerwk);
    }
    else if (p_playerwk->u.play.cddat.ride == 0) {
      p_playerwk->mstno = 8;
    }
  }
  else if (p_playerwk->mstno == 8) {
    p_playerwk->mstno = 0;
  }
}


static void ballset(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.ball == 1) return;

  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 5);
  if (g_ram.reverse_gravity_flag != 0) {
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 10);
  }
  soundset(60);
  if (p_playerwk->mspeed == 0) {
    p_playerwk->mspeed = 0x200;
  }
}


static bool jumpchk(SKC_sprite_status* p_playerwk) {
  if (!are_any_trg_buttons_used(g_ram.swdata.pressed)) return false;

  unsigned char cal_direc = p_playerwk->direc.b.b0;
  if (g_ram.reverse_gravity_flag != 0) {
    cal_direc = (256 - (cal_direc + 64) - 64);
  }
  cal_direc += 128;
  cal_direc &= 0xFF;
  SKC_dircol_result result = dircol2(p_playerwk, cal_direc);
  if (result.offset >= 6) {
    short cal_jump = p_playerwk->u.play.cddat.underwater == 0 ? (g_ram.ssonicflag == 0 ? 0x680 : 0x800) : 0x380;
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


static void jumpchk2(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.jump_flag != 0) {
    short cal_speed = p_playerwk->u.play.cddat.underwater == 0 ? -0x400 : -0x200;
    if (cal_speed > p_playerwk->yspeed) {
      if (!are_any_trg_buttons_used(g_ram.swdata.down)) {
        p_playerwk->yspeed = cal_speed;
      }
    }
    else {
      jumpchk3(p_playerwk, work);
    }
  }
  else if (p_playerwk->u.play.spindash_flag == 0 && p_playerwk->yspeed < -0xFC0) {
    p_playerwk->yspeed = -0xFC0;
  }
}


static void jumpchk3(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  SKC_speed spd_tbl[2][2][2][2] = {
    {{{
      {      0,      0 },
      {      0, -0x800 }
    },{
      {      0,  0x800 },
      {      0,      0 }
    }},{{
      { -0x800,      0 },
      { -0x800, -0x800 }
    },{
      { -0x800,  0x800 },
      {      0,      0 }
    }}},{{{
      {  0x800,      0 },
      {  0x800, -0x800 }
    },{
      {  0x800,  0x800 }
    }}}
  };

  if (p_playerwk->u.play.talent_status != 0) return;
  if (!are_any_trg_buttons_used(g_ram.swdata.pressed)) return;

  p_playerwk->u.play.cddat.ballj = 0;

  switch (g_ram.ssonicflag) {
    case 1:
      p_playerwk->u.play.talent_status = 1;
      break;
    case 0:
      if (p_playerwk->u.play.powerdat.muteki == 0) {
        if (p_playerwk->u.play.powerdat.flame_baria == 1) {
          g_ram.actwk[ACTWK_PL_BARIA].mstno = 1;
          p_playerwk->u.play.talent_status = 1;
          p_playerwk->xspeed = p_playerwk->u.play.cddat.left == 0 ? 0x800 : -0x800;
          p_playerwk->mspeed = p_playerwk->xspeed;
          p_playerwk->yspeed = 0;
          g_ram.DAT_08ffee24 = 0x2000;
          playposiwkinit(p_playerwk);
          soundset(67);
        }
        else if (p_playerwk->u.play.powerdat.thunder_baria == 1) {
          g_ram.actwk[ACTWK_PL_BARIA].mstno = 1;
          p_playerwk->u.play.talent_status = 1;
          p_playerwk->yspeed = -0x580;
          p_playerwk->u.play.jump_flag = 0;
          soundset(69);
        }
        else if (p_playerwk->u.play.powerdat.aqua_baria == 1) {
          g_ram.actwk[ACTWK_PL_BARIA].mstno = 1;
          p_playerwk->u.play.talent_status = 1;
          p_playerwk->xspeed = 0;
          p_playerwk->mspeed = 0;
          p_playerwk->yspeed = 0x800;
          soundset(68);
        }
        else {
          bool can_transform = g_ram.semeraldcnt >= 7 || (g_ram.emeraldcnt >= 7 && g_ram.DAT_08ffffba == 0);
          if (!can_transform || g_ram.plring < 50 || g_ram.pltime_f == 0) {
            if (p_playerwk->u.play.powerdat.baria == 0) {
              g_ram.actwk[ACTWK_PL_BARIA].mstno = 1;
              p_playerwk->u.play.talent_status = 1;
              soundset(66);
            }
          }
          else {
            g_ram.ssonicpallet = 1;
            g_ram.ssonicpallet_next = 15;
            g_ram.ssonicring_timer = 60;
            p_playerwk->patbase = splaypat;
            p_playerwk->u.play.control_bitfield = 0x81;
            p_playerwk->mstno = 31;
            if (g_ram.semeraldcnt >= 7) {
              g_ram.ssonicflag = 0xFF;
              g_ram.actwk[ACTWK_PL_MUTEKI].r_ptr = &hsonicstars;
              g_ram.actwk[ACTWK_TRAIL].r_ptr = &hypertrail;
            }
            else {
              g_ram.ssonicflag = 1;
              g_ram.actwk[ACTWK_TRAIL].r_ptr = &ssonicstars;
            }
            *work.plmaxspdwk_ptr = 0xA00;
            *work.pladdspdwk_ptr = 0x30;
            *work.plretspdwk_ptr = 0x100;
            p_playerwk->u.play.muteki_timer = 0;
            p_playerwk->u.play.powerdat.muteki = 1;
            soundset(-97);
            bgmset(44);
          }
        }
      }
      break;
    case 0xFF:
      pcolhyper(p_playerwk);
      g_ram.DAT_08ffee24 = 0x2000;
      playposiwkinit(p_playerwk);
      p_playerwk->u.play.talent_status = 1;
      g_ram.actwk[ACTWK_PL_MUTEKI].mstno = 1;
      soundset(-74);
      if (are_any_dir_buttons_used(g_ram.swdata.down)
          && g_ram.swdata.down.u != g_ram.swdata.down.d
          && g_ram.swdata.down.l != g_ram.swdata.down.r) {
        p_playerwk->xspeed = spd_tbl[g_ram.swdata.down.r][g_ram.swdata.down.l][g_ram.swdata.down.d][g_ram.swdata.down.u].xspeed;
        p_playerwk->mspeed = p_playerwk->xspeed;
        p_playerwk->yspeed = spd_tbl[g_ram.swdata.down.r][g_ram.swdata.down.l][g_ram.swdata.down.d][g_ram.swdata.down.u].yspeed;
      }
      else {
        p_playerwk->xspeed = p_playerwk->u.play.cddat.left == 0 ? 0x800 : -0x800;
        p_playerwk->mspeed = p_playerwk->xspeed;
        p_playerwk->yspeed = 0;
      }
      break;
  }
}


void foxsupercnt(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.smilesflag == 0) return;

  playsupercnt0(p_playerwk, work);
}


void playsupercnt(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.ssonicflag == 0) return;

  playsupercnt0(p_playerwk, work);
}


static void playsupercnt0(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  bool transforming = false;
  if (g_ram.pltime_f == 0) {
    transforming = true;
  }
  else if (g_ram.ssonicring_timer-- == 0) {
    g_ram.ssonicring_timer = 60;
    if (g_ram.plring != 0) {
      SET_BIT(g_ram.plring_f, 0);
      if (g_ram.plring == 1 || g_ram.plring == 10 || g_ram.plring == 100) {
        SET_BIT(g_ram.plring_f, 7);
      }
      --g_ram.plring;
      if (g_ram.plring == 0) {
        transforming = true;
      }
    }
  }
  if (transforming) {
    g_ram.ssonicpallet = 2;
    g_ram.DAT_08fff65c = 30;
    g_ram.ssonicflag = 0;
    g_ram.smilesflag = 0;
    g_ram.playpatno = 0xFF;
    if (p_playerwk->u.play.character == SONIC) {
      p_playerwk->patbase = playpat;
    }
    p_playerwk->mstrestart = 1;
    p_playerwk->u.play.muteki_timer = 1;
    *work.plmaxspdwk_ptr = p_playerwk->u.play.cddat.underwater == 0 ? 0x600 : 0x300;
    *work.pladdspdwk_ptr = p_playerwk->u.play.cddat.underwater == 0 ? 0xC : 6;
    *work.plretspdwk_ptr = p_playerwk->u.play.cddat.underwater == 0 ? 0x80 : 0x40;
  }
}


bool spinchk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  short spd_tbl[9] = {
    0x800, 0x880, 0x900, 0x980, 0xA00, 0xA80, 0xB00, 0xB80, 0xC00
  };
  short spd_tbl2[9] = {
    0xB00, 0xB80, 0xC00, 0xC80, 0xD00, 0xD80, 0xE00, 0xE80, 0xF00
  };

  if (p_playerwk->u.play.spindash_flag == 0) {
    if (p_playerwk->mstno == 8 && are_any_trg_buttons_used(g_ram.swdata.pressed)) {
      p_playerwk->mstno = 9;
      soundset(-85);
      p_playerwk->u.play.spindash_flag = 1;
      p_playerwk->u.play.spindash_ctr = 0;
      if (p_playerwk->u.play.air_timer >= 12) {
        work.effectwk_ptr->mstno = 2;
      }
      limitchk(p_playerwk);
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
    if (g_ram.swdata.down.d == 0) {
      p_playerwk->sprvsize = 14;
      p_playerwk->sprhsize = 7;
      p_playerwk->mstno = 2;
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 5);
      if (g_ram.reverse_gravity_flag != 0) {
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 10);
      }
      p_playerwk->u.play.spindash_flag = 0;
      unsigned char index = p_playerwk->u.play.spindash_ctr >> 8;
      p_playerwk->mspeed = g_ram.ssonicflag == 0 ? spd_tbl[index] : spd_tbl2[index];
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
        p_playerwk->u.play.spindash_ctr -= p_playerwk->u.play.spindash_ctr / 32;
        if (p_playerwk->u.play.spindash_ctr < 0) {
          p_playerwk->u.play.spindash_ctr = 0;
        }
      }
      if (are_any_trg_buttons_used(g_ram.swdata.pressed)) {
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
    limitchk(p_playerwk);
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


void keispd(SKC_sprite_status* p_playerwk) {
  unsigned char cal_direc = p_playerwk->direc.b.b0 + 96;
  cal_direc &= 0xFF;
  if (cal_direc < 192) {
    short sin, cos;
    sinset(p_playerwk->direc.b.b0, &sin, &cos);
    sin = sin * 0x20 / 0x100;
    if (p_playerwk->mspeed != 0) {
      if (p_playerwk->mspeed >= 0) {
        if (sin != 0) {
          p_playerwk->mspeed += sin;
        }
      }
      else {
        p_playerwk->mspeed += sin;
      }
    }
    else if (abs(sin) >= 0xD) {
      p_playerwk->mspeed += sin;
    }
  }
}


void keispd2(SKC_sprite_status* p_playerwk) {
  unsigned char cal_direc = p_playerwk->direc.b.b0 + 96;
  cal_direc &= 0xFF;
  if (cal_direc < 192) {
    short sin, cos;
    sinset(p_playerwk->direc.b.b0, &sin, &cos);
    sin = sin * 0x50 / 0x100;
    if (p_playerwk->mspeed >= 0) {
      if (sin < 0) {
        sin /= 4;
      }
      p_playerwk->mspeed += sin;
    }
    else {
      if (sin >= 0) {
        sin /= 4;
      }
      p_playerwk->mspeed += sin;
    }
  }
}


void fallchk(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.convex_flag != 0) return;

  if (p_playerwk->u.play.hlock_timer == 0) {
    unsigned char cal_direc = p_playerwk->direc.b.b0 + 24;
    cal_direc &= 0xFF;
    if (cal_direc >= 48 && abs(p_playerwk->mspeed < 0x280)) {
      p_playerwk->u.play.hlock_timer = 32;
      cal_direc = p_playerwk->direc.b.b0 + 48;
      if (cal_direc >= 96) {
        p_playerwk->u.play.cddat.jump = 1;
      }
      else if (cal_direc >= 48) {
        p_playerwk->mspeed += 0x80;
      }
      else {
        p_playerwk->mspeed -= 0x80;
      }
    }
  }
  else {
    --p_playerwk->u.play.hlock_timer;
  }
}


void direcchg(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->direc.b.b0 != 0) {
    unsigned char cal_direc = p_playerwk->direc.b.b0;
    if (p_playerwk->direc.b.b0 >= 128) {
      cal_direc += 2;
      cal_direc &= 0xFF;
      if (cal_direc < 128) {
        cal_direc = 0;
      }
    }
    else {
      cal_direc -= 2;
      cal_direc &= 0xFF;
      if (cal_direc >= 128) {
        cal_direc = 0;
      }
    }
    p_playerwk->direc.b.b0 = cal_direc;
  }
  else if (p_playerwk->direc.b.b1 != 0) {
    unsigned char cal_direc = p_playerwk->direc.b.b1;
    if (p_playerwk->mspeed >= 0 || p_playerwk->u.play.flip_mst.reverse == 1) {
      if ((short)cal_direc + (short)p_playerwk->u.play.flip_rev_frame_cnt > 255) {
        if (p_playerwk->u.play.flip_rev_cnt-- == 0) {
          p_playerwk->u.play.flip_rev_cnt = 0;
          cal_direc = 0;
        }
      }
    }
    else {
      if ((short)cal_direc - (short)p_playerwk->u.play.flip_rev_frame_cnt < 0) {
        if (p_playerwk->u.play.flip_rev_cnt-- == 0) {
          p_playerwk->u.play.flip_rev_cnt = 0;
          cal_direc = 0;
        }
      }
    }
    p_playerwk->direc.b.b1 = cal_direc;
  }
}


void jumpcolchk(SKC_sprite_status* p_playerwk) {
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
              jumpcolsub(p_playerwk);
              return;
            }
          }
          else {
            p_playerwk->xspeed = 0;
            if (p_playerwk->yspeed > 0xFC0) {
              p_playerwk->yspeed = 0xFC0;
            }
          }
          jumpcolsub(p_playerwk);
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
      else if (g_ram.watercoliflag != 0 || p_playerwk->yspeed >= 0) {
        result = dircol_d_g(p_playerwk);
        if (result.offset < 0) {
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          p_playerwk->direc.b.b0 = result.direc;
          p_playerwk->yspeed = 0;
          p_playerwk->mspeed = p_playerwk->xspeed;
          jumpcolsub(p_playerwk);
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
          jumpcolsub(p_playerwk);
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
      else if (g_ram.watercoliflag != 0 || p_playerwk->yspeed >= 0) {
        result = dircol_d_g(p_playerwk);
        if (result.offset < 0) {
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          p_playerwk->direc.b.b0 = result.direc;
          p_playerwk->yspeed = 0;
          p_playerwk->mspeed = p_playerwk->xspeed;
          jumpcolsub(p_playerwk);
        }
      }
      break;
    }
  }
}


SKC_dircol_result dircol_d_g(SKC_sprite_status* p_playerwk) {
  if (g_ram.reverse_gravity_flag == 0) {
    return dircol_d(p_playerwk);
  }
  SKC_dircol_result result = dircol_u(p_playerwk);
  result.direc = (256 - (result.direc + 64) - 64) & 0xFF;
  return result;
}


SKC_dircol_result dircol_u_g(SKC_sprite_status* p_playerwk) {
  if (g_ram.reverse_gravity_flag == 0) {
    return dircol_u(p_playerwk);
  }
  SKC_dircol_result result = dircol_d(p_playerwk);
  result.direc = (256 - (result.direc + 64) - 64) & 0xFF;
  return result;
}


SKC_dircol_result edgechk_d2_g(SKC_sprite_status* p_playerwk, short xposi) {
  if (g_ram.reverse_gravity_flag == 0) {
    return edgechk_d2(p_playerwk, xposi);
  }
  return edgechk_u2(p_playerwk, xposi);
}


static void jumpcolsub(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.spindash_flag == 0) {
    p_playerwk->mstno = 0;
    jumpcolsub0(p_playerwk);
  }
  else {
    jumpcolsub1(p_playerwk);
  }
}


void jumpcolsub0(SKC_sprite_status* p_playerwk) {
  switch (p_playerwk->u.play.character) {
    case SONIC:
    default: {
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
      jumpcolsub1(p_playerwk);
      break;
    }
    case MILES:
      foxjumpcolsub0(p_playerwk);
      break;
    case KNUCKLES:
      knucklesjumpcolsub0(p_playerwk);
      break;
  }
}


static void jumpcolsub1(SKC_sprite_status* p_playerwk) {
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
  if (p_playerwk->u.play.talent_status != 0) {
    if (p_playerwk->u.play.character == SONIC
        && g_ram.ssonicflag == 0
        && p_playerwk->u.play.powerdat.aqua_baria == 1) {
      aqua_baria_bounce(p_playerwk);
    }
    p_playerwk->u.play.talent_status = 0;
  }
}


static void aqua_baria_bounce(SKC_sprite_status* p_playerwk) {
  short speed = p_playerwk->u.play.cddat.underwater == 0 ? 0x780 : 0x400;
  unsigned char cal_direc = p_playerwk->direc.b.b0 - 64;
  cal_direc &= 0xFF;
  short sin, cos;
  sinset(cal_direc, &sin, &cos);
  p_playerwk->xspeed += cos * speed / 0x100;
  p_playerwk->yspeed += sin * speed / 0x100;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.jump_flag = 1;
  p_playerwk->u.play.convex_flag = 0;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 7;
  p_playerwk->mstno = 2;
  p_playerwk->u.play.cddat.ball = 1;
  short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
  if (g_ram.reverse_gravity_flag != 0) {
    yoffset = -yoffset;
  }
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - yoffset);
  g_ram.actwk[ACTWK_PL_BARIA].mstno = 2;
  soundset(68);
}


static void play00damage(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.debugflag != 0 && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    speedset2_g(p_playerwk);
    p_playerwk->yspeed += 0x30;
    if (p_playerwk->u.play.cddat.underwater == 1) {
      p_playerwk->yspeed -= 0x20;
    }
    if (g_ram.scralim_up == -0x100) {
      short yposi = (unsigned short)fp16_get_integer(p_playerwk->yposi) & g_ram.scrc_v;
      fp16_set_integer(&p_playerwk->yposi, yposi);
    }
    play00damage_sub(p_playerwk);
    limitchk(p_playerwk);
    playposiwkset(p_playerwk);
    patchgmainwrt(p_playerwk);
    actionsub(p_playerwk);
  }
}


static void play00damage_sub(SKC_sprite_status* p_playerwk) {
  if (g_ram.DAT_08fff665 != 0
      || (g_ram.reverse_gravity_flag == 0 && g_ram.scralim_down + 224 >= fp16_get_integer(p_playerwk->yposi))
      || (g_ram.reverse_gravity_flag != 0 && g_ram.scralim_up < fp16_get_integer(p_playerwk->yposi))) {
    jumpcolchk(p_playerwk);
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


static void play00die(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.debugflag != 0 && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    play00die_sub(p_playerwk, work);
    speedset_g(p_playerwk);
    playposiwkset(p_playerwk);
    patchgmainwrt(p_playerwk);
    actionsub(p_playerwk);
  }
}


void play00die_sub(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk == &g_ram.actwk[0]) {
    g_ram.pl_scr_lock_flag = 1;
  }
  else {
    g_ram.pl2_scr_lock_flag = 1;
  }
  p_playerwk->u.play.spindash_flag = 0;
  short scra_v = g_ram.scra_v_posit >> 16;
  bool next = false;
  if (g_ram.reverse_gravity_flag != 0) {
    scra_v -= 16;
    if (scra_v >= fp16_get_integer(p_playerwk->yposi)) {
      next = true;
    }
  }
  else {
    scra_v += 256;
    if (g_ram.vs_flag != 0) {
      scra_v -= 112;
    }
    if (scra_v < fp16_get_integer(p_playerwk->yposi)) {
      next = true;
    }
  }
  if (next) {
    if (g_ram.vs_flag == 0) {
      if (p_playerwk->u.play.character == MILES && g_ram.play_type != PLAY_TYPE_MILES) {
        p_playerwk->r_no = 2;
        foxcpu_wait0_init(p_playerwk);
      }
      else {
        p_playerwk->r_no = 8;
        p_playerwk->u.play.spindash_ctr = 60;
        g_ram.plresetflag = 0;
        ++g_ram.pl_suu_f;
        --g_ram.pl_suu;
        if (g_ram.pl_suu == 0) {
          p_playerwk->u.play.spindash_ctr = 0;
          g_ram.actwk[2].r_ptr = &over;
          g_ram.actwk[3].r_ptr = &over;
          g_ram.actwk[2].patno = 0;
          g_ram.actwk[3].patno = 1;
          g_ram.actwk[2].u.obj.oya = p_playerwk - g_ram.actwk;
          g_ram.pltimeover_f = 0;
          g_ram.pltime_f = 0;
          g_ram.DAT_08fffec7 = 0;
          p_playerwk->r_no = 8;
          bgmset(39);
          divdevset(3);
        }
        else if (g_ram.pltimeover_f != 0) {
          p_playerwk->u.play.spindash_ctr = 0;
          g_ram.actwk[2].r_ptr = &over;
          g_ram.actwk[3].r_ptr = &over;
          g_ram.actwk[2].patno = 2;
          g_ram.actwk[3].patno = 3;
          g_ram.actwk[2].u.obj.oya = p_playerwk - g_ram.actwk;
          g_ram.pltime_f = 0;
          g_ram.DAT_08fffec7 = 0;
          p_playerwk->r_no = 8;
          bgmset(39);
          divdevset(3);
        }
      }
    }
    else {
      p_playerwk->r_no = 2;
      if (p_playerwk == &g_ram.actwk[0]) {
        g_ram.pl_scr_lock_flag = 0;
        fp16_set_integer(&p_playerwk->xposi, g_ram.plxposi_s);
        fp16_set_integer(&p_playerwk->yposi, g_ram.plyposi_s);
        p_playerwk->sproffset = g_ram.plsproffset_s;
        p_playerwk->u.play.top_solid_bit = g_ram.pl_top_solid_bit_s;
        p_playerwk->u.play.lrb_solid_bit = g_ram.pl_lrb_solid_bit_s;
        g_ram.plring = 0;
        g_ram.plring_f2 = 0;
        g_ram.DAT_08fff74a = 1;
      }
      else {
        g_ram.pl2_scr_lock_flag = 0;
        fp16_set_integer(&p_playerwk->xposi, g_ram.plxposi_s2);
        fp16_set_integer(&p_playerwk->yposi, g_ram.plyposi_s2);
        p_playerwk->sproffset = g_ram.plsproffset_s2;
        p_playerwk->u.play.top_solid_bit = g_ram.pl_top_solid_bit_s2;
        p_playerwk->u.play.lrb_solid_bit = g_ram.pl_lrb_solid_bit_s2;
        g_ram.pl2ring = 0;
        g_ram.DAT_08fff74b = 1;
      }
      p_playerwk->u.play.control_bitfield = 0;
      p_playerwk->mstno = 5;
      p_playerwk->xspeed = 0;
      p_playerwk->yspeed = 0;
      p_playerwk->mspeed = 0;
      memset(&p_playerwk->u.play.cddat, 0, sizeof(p_playerwk->u.play.cddat));
      p_playerwk->u.play.cddat.jump = 1;
      p_playerwk->u.play.hlock_timer = 0;
      p_playerwk->u.play.spindash_ctr = 0;
      p_playerwk->u.play.speedup_timer = 0;
      *work.plmaxspdwk_ptr = vsplaydata[p_playerwk->u.play.character][0];
      *work.pladdspdwk_ptr = vsplaydata[p_playerwk->u.play.character][1];
      *work.plretspdwk_ptr = vsplaydata[p_playerwk->u.play.character][2];
    }
  }
}


static void play00erase(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.spindash_ctr == 0) return;

  --p_playerwk->u.play.spindash_ctr;
  if (p_playerwk->u.play.spindash_ctr == 0) {
    g_ram.gameflag = 1;
  }
}


static void play00appear(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.DAT_08ffee00 == 0 && g_ram.DAT_08ffee02 == 0) {
    p_playerwk->r_no = 2;
  }
  patchgmainwrt(p_playerwk);
  actionsub(p_playerwk);
}


static void play00drown(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.debugflag != 0 && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    speedset2_g(p_playerwk);
    p_playerwk->yspeed += 0x10;
    playposiwkset(p_playerwk);
    patchgmainwrt(p_playerwk);
    actionsub(p_playerwk);
  }
}


static void patchgmainwrt(SKC_sprite_status* p_playerwk) {
  if (g_ram.vs_flag == 0) {
    patchgmain(p_playerwk);
    if (g_ram.reverse_gravity_flag != 0) {
      p_playerwk->actflg.vflip ^= 1;
    }
    playwrt(p_playerwk);
  }
  else {
    vspatchgmain(p_playerwk);
    vsplaywrt(p_playerwk);
  }
}


static void patchgmain(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->mstno != p_playerwk->mstrestart) {
    p_playerwk->mstrestart = p_playerwk->mstno;
    p_playerwk->patcnt = 0;
    p_playerwk->pattim = 0;
    p_playerwk->u.play.cddat.push = 0;
  }
  unsigned char** pp_chg = g_ram.ssonicflag == 0 ? playchg : ssonicchg;
  unsigned char* p_chg = pp_chg[p_playerwk->mstno];
  if (p_chg[0] >= 128) {
    playrunchg(p_playerwk, p_chg[0]);
  }
  else {
    p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
    p_playerwk->actflg.vflip = 0;
    if (p_playerwk->pattim-- == 0) {
      p_playerwk->pattim = p_chg[0];
      patchgmain2(p_playerwk, p_chg);
    }
  }
}


static void patchgmain2(SKC_sprite_status* p_playerwk, unsigned char* p_chg) {
  unsigned char patno = p_chg[p_playerwk->patcnt + 1];
  if (patno < 252) {
    p_playerwk->patno = patno;
    ++p_playerwk->patcnt;
  }
  else {
    switch (patno) {
      case MAINPATCHG_CONTROL_LOOP:
        p_playerwk->patcnt = 0;
        p_playerwk->patno = p_chg[1];
        ++p_playerwk->patcnt;
        break;
      case MAINPATCHG_CONTROL_REWIND:
        p_playerwk->patno = p_chg[p_playerwk->patcnt + 1 - p_chg[p_playerwk->patcnt + 2]];
        p_playerwk->patcnt -= p_chg[p_playerwk->patcnt + 2] - 1;
        break;
      case MAINPATCHG_CONTROL_NEXT:
        p_playerwk->mstno = p_chg[p_playerwk->patcnt + 2];
        break;
    }
  }
}


static void playrunchg(SKC_sprite_status* p_playerwk, unsigned char patno) {
  if (patno != 255) {
    playrunchg2(p_playerwk);
  }
  else if (p_playerwk->u.play.flip_mst.reverse == 1 || p_playerwk->direc.b.b1 != 0) {
    playflipchg(p_playerwk);
  }
  else {
    unsigned char direction = p_playerwk->direc.b.b0;
    if (direction < 128 && direction != 0) {
      --direction;
    }
    if (p_playerwk->u.play.cddat.left == 0) {
      direction = 255 - direction;
    }
    direction += 16;
    direction &= 0xFF;
    if (direction >= 128) {
      p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left ^ 1;
      p_playerwk->actflg.vflip = 1;
    }
    else {
      p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
      p_playerwk->actflg.vflip = 0;
    }
    if (p_playerwk->u.play.cddat.push == 1) {
      playrunchg3(p_playerwk);
    }
    else {
      unsigned char patno_add = direction / 16 & 6;
      short cal_speed = abs(p_playerwk->mspeed);
      if (p_playerwk->u.play.powerdat.mizuflag == 1) {
        cal_speed *= 2;
      }
      if (g_ram.ssonicflag == 0) {
        unsigned char* p_chg = cal_speed >= 0x600 ? plchg01 : plchg00;
        patno_add = cal_speed >= 0x600 ? patno_add * 2 : patno_add * 4;
        unsigned char patno = p_chg[p_playerwk->patcnt + 1];
        if (patno == 255) {
          p_playerwk->patcnt = 0;
          patno = p_chg[1];
        }
        p_playerwk->patno = patno + patno_add;
        if (p_playerwk->pattim-- == 0) {
          cal_speed = -cal_speed + 0x800;
          if (cal_speed < 0) {
            cal_speed = 0;
          }
          p_playerwk->pattim = cal_speed / 0x100;
          ++p_playerwk->patcnt;
        }
      }
      else {
        unsigned char* p_chg = cal_speed >= 0x800 ? splaychg01 : splaychg00;
        patno_add = cal_speed >= 0x800 ? patno_add * 2 : patno_add * 4;
        unsigned char patno = p_chg[p_playerwk->patcnt + 1];
        if (patno == 255) {
          p_playerwk->patcnt = 0;
          patno = p_chg[1];
        }
        p_playerwk->patno = patno + patno_add;
        if (p_playerwk->pattim-- == 0) {
          cal_speed = -cal_speed + 0x800;
          if (cal_speed < 0) {
            cal_speed = 0;
          }
          p_playerwk->pattim = cal_speed / 0x100;
          ++p_playerwk->patcnt;
        }
      }
    }
  }
}


void playflipchg(SKC_sprite_status* p_playerwk) {
  unsigned char ofs_tbl[5] = {
    0, 64, 73, 73, 144
  };

  unsigned char direction2 = p_playerwk->direc.b.b1;
  bool reverse_gravity_zone = get_zone(g_ram.stageno) == FLYING_BATTERY || get_zone(g_ram.stageno) == DEATH_EGG;
  p_playerwk->actflg.hflip = 0;
  p_playerwk->actflg.vflip = 0;

  switch (p_playerwk->u.play.flip_mst.type) {
    case 0:
      if (p_playerwk->u.play.cddat.left == 0) {
        if (p_playerwk->u.play.flip_mst.reverse == 1) {
          if (!reverse_gravity_zone) {
            p_playerwk->actflg.vflip = 1;
            direction2 = 256 - direction2 + 143;
          }
        }
        else {
          direction2 += 11;
        }
      }
      else {
        if (p_playerwk->u.play.flip_mst.reverse == 1
            && (reverse_gravity_zone || get_zone(g_ram.stageno) == MUSHROOM_HILL)) {
          p_playerwk->actflg.hflip = 1;
          direction2 += 11;
        }
        else {
          p_playerwk->actflg.hflip = 1;
          p_playerwk->actflg.vflip = 1;
          direction2 = 256 - direction2 + 143;
        }
      }
      direction2 &= 0xFF;
      p_playerwk->patno = direction2 / 22 + 49;
      p_playerwk->pattim = 0;
      break;
    case 1:
      if (p_playerwk->u.play.cddat.left != 0) {
        p_playerwk->actflg.hflip = 1;
      }
      direction2 -= 8;
      direction2 &= 0xFF;
      p_playerwk->patno = direction2 / 22 + ofs_tbl[p_playerwk->u.play.flip_mst.type];
      p_playerwk->pattim = 0;
      break;
    case 2:
      if (p_playerwk->u.play.cddat.left == 0) {
        direction2 += 11;
      }
      else {
        p_playerwk->actflg.hflip = 1;
        p_playerwk->actflg.vflip = 1;
        direction2 = 256 - direction2 + 143;
      }
      direction2 &= 0xFF;
      p_playerwk->patno = direction2 / 22 + ofs_tbl[p_playerwk->u.play.flip_mst.type];
      p_playerwk->pattim = 0;
      break;
    case 3:
      if (p_playerwk->u.play.cddat.left == 0) {
        p_playerwk->actflg.vflip = 1;
        direction2 = 256 - direction2 + 143;
      }
      else {
        p_playerwk->actflg.hflip = 1;
        direction2 += 11;
      }
      direction2 &= 0xFF;
      p_playerwk->patno = direction2 / 22 + ofs_tbl[p_playerwk->u.play.flip_mst.type];
      p_playerwk->pattim = 0;
      break;
    case 4:
      if (p_playerwk->u.play.cddat.left == 0) {
        if (p_playerwk->u.play.flip_mst.reverse == 1) {
          direction2 += 11;
        }
        else {
          direction2 += 11;
        }
      }
      else {
        if (p_playerwk->u.play.flip_mst.reverse == 1) {
          p_playerwk->actflg.hflip = 1;
          p_playerwk->actflg.vflip = 1;
          direction2 = 256 - direction2 + 143;
        }
        else {
          p_playerwk->actflg.hflip = 1;
          p_playerwk->actflg.vflip = 1;
          direction2 = 256 - direction2 + 143;
        }
      }
      direction2 &= 0xFF;
      p_playerwk->patno = direction2 / 22 + 49;
      p_playerwk->pattim = 0;
      break;
    default:
      if (p_playerwk->u.play.cddat.left == 0) {
        p_playerwk->actflg.hflip = 1;
      }
      direction2 += 11;
      direction2 &= 0xFF;
      p_playerwk->patno = direction2 / 22 + 49;
      p_playerwk->pattim = 0;
      break;
  }
}


static void playrunchg2(SKC_sprite_status* p_playerwk) {
  p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
  p_playerwk->actflg.vflip = 0;
  if (p_playerwk->pattim-- == 0) {
    short cal_speed = abs(p_playerwk->mspeed);
    unsigned char* p_chg = cal_speed >= 0x600 ? plchg03 : plchg02;
    cal_speed = -cal_speed + 0x400;
    if (cal_speed < 0) {
      cal_speed = 0;
    }
    p_playerwk->pattim = cal_speed / 0x100;
    patchgmain2(p_playerwk, p_chg);
  }
}


static void playrunchg3(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->pattim-- > 0) return;

  short cal_speed = -abs(p_playerwk->mspeed) + 0x800;
  if (cal_speed < 0) {
    cal_speed = 0;
  }
  cal_speed /= 0x40;
  p_playerwk->pattim = cal_speed % 0x100;
  unsigned char* p_chg = g_ram.ssonicflag == 0 ? plchg04 : splaychg02;
  patchgmain2(p_playerwk, p_chg);
}


static unsigned char* playchg[36] = {
  plchg00,
  plchg01,
  plchg02,
  plchg03,
  plchg04,
  plchg05,
  plchg06,
  plchg07,
  plchg08,
  plchg09,
  plchg10,
  plchg11,
  plchg12,
  plchg13,
  plchg14,
  plchg15,
  plchg16,
  plchg17,
  plchg18,
  plchg19,
  plchg20,
  plchg21,
  plchg22,
  plchg23,
  plchg24,
  plchg25,
  plchg26,
  plchg27,
  plchg28,
  plchg29,
  plchg30,
  splaychg06,
  plchg31,
  plchg32,
  plchg33,
  plchg34
};


static unsigned char plchg00[10] = { 255, 7, 8, 1, 2, 3, 4, 5, 6, 255 };
static unsigned char plchg01[10] = { 255, 33, 34, 35, 36, 255, 255, 255, 255, 255 };
static unsigned char plchg02[10] = { 254, 150, 151, 150, 152, 150, 153, 150, 154, 255 };
static unsigned char plchg03[10] = { 254, 150, 151, 150, 152, 150, 153, 150, 154, 255 };
static unsigned char plchg04[10] = { 253, 182, 183, 184, 185, 255, 255, 255, 255, 255 };
static unsigned char plchg05[109] = {
    5, 186, 186, 186, 186, 186, 186, 186, 186, 186,
  186, 186, 186, 186, 186, 186, 186, 186, 186, 186,
  186, 186, 186, 186, 186, 186, 186, 186, 186, 186,
  186, 186, 186, 186, 186, 186, 186, 186, 186, 186,
  186, 186, 186, 186, 186, 186, 186, 186, 186, 186,
  186, 187, 188, 188, 189, 189, 190, 190, 189, 189,
  190, 190, 189, 189, 190, 190, 189, 189, 190, 190,
  189, 189, 190, 190, 189, 189, 190, 190, 189, 189,
  190, 190, 189, 189, 190, 190, 173, 173, 173, 173,
  173, 173, 174, 174, 174, 174, 174, 174, 175, 217,
  217, 217, 217, 217, 217, 175, 175, 254,  53
};
static unsigned char plchg06[5] = { 7, 164, 165, 166, 255 };
static unsigned char plchg07[5] = { 5, 195, 196, 254, 1 };
static unsigned char plchg08[5] = { 5, 155, 156, 254, 1 };
static unsigned char plchg09[12] = { 0, 134, 135, 134, 136, 134, 137, 134, 138, 134, 139, 255 };
static unsigned char plchg10[23] = {
    9, 186, 197, 198, 198, 198, 198, 198, 198, 199,
  199, 199, 199, 199, 199, 199, 199, 199, 199, 199,
  199, 253,   0
};
static unsigned char plchg11[3] = { 15, 143, 255 };
static unsigned char plchg12[5] = { 5, 161, 162, 163, 255 };
static unsigned char plchg13[7] = { 3, 157, 158, 159, 160, 253, 0 };
static unsigned char plchg14[3] = { 7, 200, 255 };
static unsigned char plchg15[10] = { 7, 200, 201, 202, 203, 204, 205, 206, 207, 255 };
static unsigned char plchg16[4] = { 47, 142, 253, 0 };
static unsigned char plchg17[4] = { 1, 170, 171, 255 };
static unsigned char plchg18[6] = { 15, 67, 67, 67, 254, 1 };
static unsigned char plchg19[14] = { 7, 176, 178, 178, 178, 178, 178, 178, 177, 178, 179, 178, 254, 4 };
static unsigned char plchg20[3] = { 19, 145, 255 };
static unsigned char plchg21[7] = { 11, 172, 172, 3, 4, 253, 0 };
static unsigned char plchg22[3] = { 32, 168, 255 };
static unsigned char plchg23[3] = { 32, 169, 255 };
static unsigned char plchg24[3] = { 32, 167, 255 };
static unsigned char plchg25[4] = { 9, 215, 216, 255 };
static unsigned char plchg26[3] = { 64, 141, 255 };
static unsigned char plchg27[4] = { 9, 140, 141, 255 };
static unsigned char plchg28[3] = { 119, 0, 255 };
static unsigned char plchg29[4] = { 19, 208, 209, 255 };
static unsigned char plchg30[8] = { 3, 207, 200, 201, 202, 203, 254, 4 };
static unsigned char plchg31[4] = { 9, 8, 9, 255 };
static unsigned char plchg32[4] = { 3, 7, 253, 0 };
static unsigned char plchg33[6] = { 11, 144, 145, 146, 145, 255 };
static unsigned char plchg34[10] = { 11, 144, 145, 146, 145, 253, 0, 135, 219, 144 };


static unsigned char* ssonicchg[32] = {
  splaychg00,
  splaychg01,
  plchg02,
  plchg03,
  splaychg02,
  splaychg03,
  splaychg04,
  plchg07,
  splaychg05,
  plchg09,
  plchg10,
  plchg11,
  plchg12,
  plchg13,
  plchg14,
  plchg15,
  plchg16,
  plchg17,
  plchg18,
  plchg19,
  plchg20,
  plchg21,
  plchg22,
  plchg23,
  plchg24,
  plchg25,
  plchg26,
  plchg27,
  plchg28,
  plchg29,
  plchg30,
  splaychg06
};


static unsigned char splaychg00[10] = { 255, 1, 2, 3, 4, 5, 6, 7, 8, 255 };
static unsigned char splaychg01[10] = { 255, 33, 34, 255, 255, 255, 255, 255, 255, 255 };
static unsigned char splaychg02[10] = { 253, 182, 183, 184, 185, 255, 255, 255, 255, 255 };
static unsigned char splaychg03[4] = { 7, 186, 187, 255 };
static unsigned char splaychg04[5] = { 9, 161, 162, 163, 255 };
static unsigned char splaychg05[3] = { 5, 155, 255 };
static unsigned char splaychg06[16] = { 2, 210, 210, 211, 211, 212, 213, 214, 213, 214, 213, 214, 213, 214, 253, 0 };


void playwrt(SKC_sprite_status* p_playerwk) {
  playwrt0(p_playerwk->patno);
}


static void playwrt0(unsigned char patno) {
  if (patno == g_ram.playpatno) return;

  g_ram.playpatno = patno;
  unsigned short* p_wrtpat = g_ram.ssonicflag == 0 ? playwrtpat[patno] : splaywrtpat[patno];
  unsigned short cnt = *p_wrtpat++;
  unsigned short vram_adr = 0xD000;
  unsigned char* p_cg = patno < 218 ? play_cg : play_cg2;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = *p_wrtpat++;
    unsigned char* p_source = &p_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


void playwrt1(SKC_sprite_status* p_playerwk, unsigned char patno) {
  switch (p_playerwk->u.play.character) {
    case SONIC:
    default:
      playwrt0(patno);
      break;
    case MILES:
      foxwrt0(patno);
      break;
    case KNUCKLES:
      knuckleswrt0(patno);
      break;
  }
}


static void vspatchgmain(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->mstno != p_playerwk->mstrestart) {
    p_playerwk->mstrestart = p_playerwk->mstno;
    p_playerwk->patcnt = 0;
    p_playerwk->pattim = 0;
    p_playerwk->u.play.cddat.push = 0;
  }
  unsigned char** pp_chg = p_playerwk->u.play.character == SONIC ? vsplaychg : vsknuckleschg;
  unsigned char* p_chg = pp_chg[p_playerwk->mstno];
  if (p_chg[0] >= 128) {
    vsplayrunchg(p_playerwk, p_chg[0]);
  }
  else {
    p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
    p_playerwk->actflg.vflip = 0;
    if (p_playerwk->pattim-- == 0) {
      p_playerwk->pattim = p_chg[0];
      vspatchgmain2(p_playerwk, p_chg);
    }
  }
}


static void vspatchgmain2(SKC_sprite_status* p_playerwk, unsigned char* p_chg) {
  unsigned char patno = p_chg[p_playerwk->patcnt + 1];
  if (patno < 252) {
    p_playerwk->patno = patno;
    ++p_playerwk->patcnt;
  }
  else {
    switch (patno) {
      case MAINPATCHG_CONTROL_LOOP:
        p_playerwk->patcnt = 0;
        p_playerwk->patno = p_chg[1];
        ++p_playerwk->patcnt;
        break;
      case MAINPATCHG_CONTROL_REWIND:
        p_playerwk->patno = p_chg[p_playerwk->patcnt + 1 - p_chg[p_playerwk->patcnt + 2]];
        p_playerwk->patcnt -= p_chg[p_playerwk->patcnt + 2] - 1;
        break;
      case MAINPATCHG_CONTROL_NEXT:
        p_playerwk->mstno = p_chg[p_playerwk->patcnt + 2];
        break;
    }
  }
}


static void vsplayrunchg(SKC_sprite_status* p_playerwk, unsigned char patno) {
  if (patno != 255) {
    vsplayrunchg2(p_playerwk);
  }
  else if (p_playerwk->direc.b.b1 != 0) {
    vsplayflipchg(p_playerwk);
  }
  else {
    unsigned char direction = p_playerwk->direc.b.b0;
    if (direction < 128 && direction != 0) {
      --direction;
    }
    if (p_playerwk->u.play.cddat.left == 0) {
      direction = 255 - direction;
    }
    direction += 16;
    direction &= 0xFF;
    if (direction >= 128) {
      p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left ^ 1;
      p_playerwk->actflg.vflip = 1;
    }
    else {
      p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
      p_playerwk->actflg.vflip = 0;
    }
    if (p_playerwk->u.play.cddat.push == 1) {
      vsplayrunchg3(p_playerwk);
    }
    else {
      unsigned char patno_add = direction / 32 & 3;
      short cal_speed = abs(p_playerwk->mspeed);
      if (p_playerwk->u.play.powerdat.mizuflag == 1) {
        cal_speed *= 2;
      }
      unsigned char* p_chg = cal_speed >= 0x600 ? vsplchg01 : vsplchg00;
      patno_add = cal_speed >= 0x600 ? patno_add * 2 : patno_add * 3;
      unsigned char patno = p_chg[p_playerwk->patcnt + 1];
      if (patno == 255) {
        p_playerwk->patcnt = 0;
        patno = p_chg[1];
      }
      p_playerwk->patno = patno + patno_add;
      if (p_playerwk->pattim-- == 0) {
        cal_speed = -cal_speed + 0x800;
        if (cal_speed < 0) {
          cal_speed = 0;
        }
        p_playerwk->pattim = cal_speed / 0x100;
        ++p_playerwk->patcnt;
      }
    }
  }
}


static void vsplayflipchg(SKC_sprite_status* p_playerwk) {
  p_playerwk->actflg.hflip = 0;
  p_playerwk->actflg.vflip = 0;
  if (p_playerwk->u.play.cddat.left == 0) {
    p_playerwk->patno = (p_playerwk->direc.b.b1 + 22 & 0xFF) / 44 + 21;
    p_playerwk->pattim = 0;
  }
  else {
    unsigned char direction2 = p_playerwk->direc.b.b1;
    if (p_playerwk->u.play.flip_mst.reverse == 1) {
      p_playerwk->actflg.hflip = 1;
      direction2 += 22;
    }
    else {
      p_playerwk->actflg.hflip = 1;
      p_playerwk->actflg.vflip = 1;
      direction2 = 256 - direction2 + 154;
    }
    direction2 &= 0xFF;
    p_playerwk->patno = direction2 / 44 + 21;
    p_playerwk->pattim = 0;
  }
}


static void vsplayrunchg2(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->pattim-- > 0) return;

  short cal_speed = abs(p_playerwk->mspeed);
  unsigned char* p_chg = cal_speed >= 0x600 ? vsplchg03 : vsplchg02;
  cal_speed = -cal_speed + 0x400;
  if (cal_speed < 0) {
    cal_speed = 0;
  }
  p_playerwk->pattim = cal_speed / 0x100;
  p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
  p_playerwk->actflg.vflip = 0;
  vspatchgmain2(p_playerwk, p_chg);
}


static void vsplayrunchg3(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->pattim-- > 0) return;

  short cal_speed = -abs(p_playerwk->mspeed) + 0x800;
  if (cal_speed < 0) {
    cal_speed = 0;
  }
  p_playerwk->pattim = cal_speed / 0x100;
  p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
  p_playerwk->actflg.vflip = 0;
  unsigned char* p_chg = p_playerwk->u.play.character == SONIC ? vsplchg04 : vsplchg05;
  vspatchgmain2(p_playerwk, p_chg);
}


static unsigned char* vsplaychg[36] = {
  vsplchg00,
  vsplchg01,
  vsplchg02,
  vsplchg03,
  vsplchg04,
  vsplchg06,
  vsplchg06,
  vsplchg06,
  vsplchg07,
  vsplchg08,
  vsplchg06,
  vsplchg06,
  vsplchg06,
  vsplchg09,
  vsplchg10,
  vsplchg11,
  vsplchg12,
  vsplchg13,
  vsplchg14,
  vsplchg15,
  vsplchg16,
  vsplchg17,
  vsplchg18,
  vsplchg19,
  vsplchg20,
  vsplchg21,
  vsplchg21,
  vsplchg22,
  vsplchg23,
  vsplchg06,
  vsplchg06,
  splaychg06,
  vsplchg24,
  vsplchg25,
  vsplchg26,
  vsplchg27
};


static unsigned char* vsknuckleschg[36] = {
  vsplchg00,
  vsplchg01,
  vsplchg02,
  vsplchg03,
  vsplchg05,
  vsplchg06,
  vsplchg06,
  vsplchg06,
  vsplchg07,
  vsplchg08,
  vsplchg06,
  vsplchg06,
  vsplchg06,
  vsplchg09,
  vsplchg10,
  vsplchg11,
  vsplchg12,
  vsplchg13,
  vsplchg14,
  vsplchg15,
  vsplchg16,
  vsplchg17,
  vsplchg18,
  vsplchg19,
  vsplchg20,
  vsplchg21,
  vsplchg21,
  vsplchg22,
  vsplchg23,
  vsplchg06,
  vsplchg06,
  splaychg06,
  vsplchg24,
  vsplchg25,
  vsplchg26,
  vsplchg27
};


static unsigned char vsplchg00[6] = { 255, 1, 2, 3, 2, 255 };
static unsigned char vsplchg01[6] = { 255, 13, 14, 255, 255, 255 };
static unsigned char vsplchg02[6] = { 254, 41, 40, 42, 40, 255 };
static unsigned char vsplchg03[6] = { 254, 41, 40, 42, 40, 255 };
static unsigned char vsplchg04[6] = { 253, 37, 38, 255, 255, 255 };
static unsigned char vsplchg05[6] = { 253, 37, 38, 39, 38, 255 };
static unsigned char vsplchg06[27] = {
   7, 27, 27, 27, 27, 27, 27, 27, 27, 28,
  28, 28, 28, 28, 28, 29, 30, 29, 30, 29,
  30, 29, 30, 29, 30, 254, 16
};
static unsigned char vsplchg07[3] = { 5, 43, 255 };
static unsigned char vsplchg08[4] = { 0, 35, 36, 255 };
static unsigned char vsplchg09[7] = { 5, 34, 34, 34, 34, 253, 0 };
static unsigned char vsplchg10[3] = { 7, 21, 255 };
static unsigned char vsplchg11[3] = { 7, 21, 255 };
static unsigned char vsplchg12[4] = { 47, 21, 253, 0 };
static unsigned char vsplchg13[3] = { 1, 21, 255 };
static unsigned char vsplchg14[3] = { 15, 21, 255 };
static unsigned char vsplchg15[3] = { 15, 31, 255 };
static unsigned char vsplchg16[3] = { 19, 21, 255 };
static unsigned char vsplchg17[3] = { 11, 21, 255 };
static unsigned char vsplchg18[3] = { 32, 32, 255 };
static unsigned char vsplchg19[3] = { 32, 32, 255 };
static unsigned char vsplchg20[3] = { 32, 32, 255 };
static unsigned char vsplchg21[3] = { 64, 33, 255 };
static unsigned char vsplchg22[3] = { 9, 33, 255 };
static unsigned char vsplchg23[3] = { 119, 0, 255 };
static unsigned char vsplchg24[3] = { 9, 27, 255 };
static unsigned char vsplchg25[4] = { 3, 27, 253, 0 };
static unsigned char vsplchg26[3] = { 11, 27, 255 };
static unsigned char vsplchg27[4] = { 11, 27, 255, 144 };


static void vsplaywrt(SKC_sprite_status* p_playerwk) {
  unsigned char patno = p_playerwk->patno;
  unsigned short* p_wrtpat = p_playerwk->u.play.character == SONIC ? vsplaywrtpat[patno] : vsknuckleswrtpat[patno];
  unsigned short cnt = *p_wrtpat++;
  unsigned short vram_adr = p_playerwk == &g_ram.actwk[0] ? 0xD000 : 0xD400;
  unsigned char* p_cg = p_playerwk->u.play.character == SONIC ? vsplay_cg : vsknuckles_cg;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = *p_wrtpat++;
    unsigned char* p_source = &p_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}
