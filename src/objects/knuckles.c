#include "knuckles.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../data/cg/knuckles.h"
#include "../data/pat/knuckles.h"
#include "../data/wrt/knuckles.h"
#include "../types/playwork.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/direction.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../coli.h"
#include "../constants.h"
#include "../dircol.h"
#include "../edit.h"
#include "../etc.h"
#include "../sound.h"
#include "player.h"
#include "playsub.h"
static void knuckles_init(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knuckles_move(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knucklespowercnt(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void nkwaterchk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knuckleswalk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knucklesjump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void glide_move(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void glide_move_normal(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void attach_to_wall(SKC_sprite_status* p_playerwk);
static void glide_move_normal_sub(SKC_sprite_status* p_playerwk, short xposi);
static void fall_from_wall(SKC_sprite_status* p_playerwk);
static void glide_move_fall(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void glide_move_slide(SKC_sprite_status* p_playerwk);
static void glide_move_climb(SKC_sprite_status* p_playerwk);
static void surmount_wall(SKC_sprite_status* p_playerwk);
static void detach_from_wall(SKC_sprite_status* p_playerwk);
static void glide_move_surmount_sub(SKC_sprite_status* p_playerwk);
static SKC_dircol_result climbcol(SKC_sprite_status* p_playerwk, short yposi);
static void glide_move_surmount(SKC_sprite_status* p_playerwk);
static void glide_patchg(SKC_sprite_status* p_playerwk);
static void glide_chk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void ballwalk(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void balljump(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void levermove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void lmovecol(SKC_sprite_status* p_playerwk);
static void nkwalk_l(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void nkwalk_r(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void balllmove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void ballwalk_l(SKC_sprite_status* p_playerwk, short plretspdwk);
static void ballwalk_r(SKC_sprite_status* p_playerwk, short plretspdwk);
static void jumpmove(SKC_sprite_status* p_playerwk, SKC_play_work work);
static bool jumpchk(SKC_sprite_status* p_playerwk);
static void jumpchk2(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void jumpchk3(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void glidecol(SKC_sprite_status* p_playerwk);
static void jumpcolsub(SKC_sprite_status* p_playerwk);
static void jumpcolsub1(SKC_sprite_status* p_playerwk);
static void knuckles_damage(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knuckles_damage_sub(SKC_sprite_status* p_playerwk);
static void knuckles_die(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knuckles_erase(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knuckles_appear(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void knuckles_drown(SKC_sprite_status* p_playerwk, SKC_play_work work);
static void patchgmainwrt(SKC_sprite_status* p_playerwk);
static void patchgmain(SKC_sprite_status* p_playerwk);
static void patchgmain2(SKC_sprite_status* p_playerwk, unsigned char* p_chg);
static void knucklesrunchg(SKC_sprite_status* p_playerwk, unsigned char patno);
static void knucklesrunchg2(SKC_sprite_status* p_playerwk);
static void knucklesrunchg3(SKC_sprite_status* p_playerwk);
static unsigned char* knuckleschg[37];
static unsigned char nkchg00[10];
static unsigned char nkchg01[10];
static unsigned char nkchg02[10];
static unsigned char nkchg03[10];
static unsigned char nkchg04[10];
static unsigned char nkchg05[152];
static unsigned char nkchg06[42];
static unsigned char nkchg07[5];
static unsigned char nkchg08[5];
static unsigned char nkchg09[12];
static unsigned char nkchg10[23];
static unsigned char nkchg11[3];
static unsigned char nkchg12[38];
static unsigned char nkchg13[7];
static unsigned char nkchg14[3];
static unsigned char nkchg15[12];
static unsigned char nkchg16[4];
static unsigned char nkchg17[4];
static unsigned char nkchg18[6];
static unsigned char nkchg19[9];
static unsigned char nkchg20[3];
static unsigned char nkchg21[7];
static unsigned char nkchg22[3];
static unsigned char nkchg23[3];
static unsigned char nkchg24[3];
static unsigned char nkchg25[3];
static unsigned char nkchg26[3];
static unsigned char nkchg27[3];
static unsigned char nkchg28[3];
static unsigned char nkchg29[4];
static unsigned char nkchg30[8];
static unsigned char nkchg31[3];
static unsigned char nkchg32[5];
static unsigned char nkchg33[4];
static unsigned char nkchg34[4];
static unsigned char nkchg35[14];
static unsigned char nkchg36[15];

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void knuckles(SKC_sprite_status* p_playerwk) {
  void(*act_tbl[7])(SKC_sprite_status*, SKC_play_work) = {
    &knuckles_init,
    &knuckles_move,
    &knuckles_damage,
    &knuckles_die,
    &knuckles_erase,
    &knuckles_appear,
    &knuckles_drown
  };

  if (g_ram.editmode != 0) {
    if (g_ram.editmode != 1) {
      if (g_ram.swdata1.pressed.b == 1) {
        g_ram.editmode = 0;
      }
      ++p_playerwk->patno;
      if (p_playerwk->patno >= 251) {
        p_playerwk->patno = 0;
      }
      knuckleswrt(p_playerwk);
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
      &g_ram.actwk[ACTWK_PL2_EFFECT]
    };
    act_tbl[p_playerwk->r_no / 2](p_playerwk, work);
  }
}


static void knuckles_init(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  p_playerwk->r_no += 2;
  p_playerwk->sprvsize = 19;
  p_playerwk->sprhsize = 9;
  p_playerwk->u.play.height = 19;
  p_playerwk->u.play.width = 9;
  p_playerwk->patbase = knuckles_pt;
  p_playerwk->sprpri = PRI_2;
  p_playerwk->sprvs = 24;
  p_playerwk->sprhs = 24;
  p_playerwk->actflg.relative_coordinates = 1;
  p_playerwk->u.play.character = KNUCKLES;
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


static void knuckles_move(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  void(*act_tbl[4])(SKC_sprite_status*, SKC_play_work) = {
    &knuckleswalk,
    &knucklesjump,
    &ballwalk,
    &balljump
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
    act_tbl[index](p_playerwk, work);
  }
  if (g_ram.scralim_up == -256) {
    short yposi = (unsigned short)fp16_get_integer(p_playerwk->yposi) & g_ram.scrc_v;
    fp16_set_integer(&p_playerwk->yposi, yposi);
  }
  knucklespowercnt(p_playerwk, work);
  playsupercnt(p_playerwk, work);
  playposiwkset(p_playerwk);
  nkwaterchk(p_playerwk, work);
  p_playerwk->u.play.direc_front = g_ram.dirstk[0];
  p_playerwk->u.play.direc_below = g_ram.dirstk[2];
  if (g_ram.watercoliflag != 0 && p_playerwk->mstno == 0) {
    p_playerwk->mstno = p_playerwk->mstrestart;
  }
  if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 1)) {
    patchgmain(p_playerwk);
    if (g_ram.reverse_gravity_flag != 0) {
      p_playerwk->actflg.vflip ^= 1;
    }
    knuckleswrt(p_playerwk);
  }
  if (!BIT_IS_SET(p_playerwk->u.play.control_bitfield, 5)
      && !BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) {
    pcol(p_playerwk);
  }
}


static void knucklespowercnt(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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
      *work.plmaxspdwk_ptr = g_ram.ssonicflag == 0 ? 0x600 : 0x800;
      *work.pladdspdwk_ptr = g_ram.ssonicflag == 0 ? 0xC : 0x18;
      *work.plretspdwk_ptr = g_ram.ssonicflag == 0 ? 0x80 : 0xC0;
      p_playerwk->u.play.powerdat.speedup = 0;
      Change_Music_Tempo(0);
    }
  }
}


static void nkwaterchk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.watermode == 0) return;

  if (g_ram.waterposi < fp16_get_integer(p_playerwk->yposi)) {
    if (p_playerwk->u.play.cddat.underwater == 0) {
      p_playerwk->u.play.cddat.underwater = 1;
      ++g_ram.water_flag;
      plairset(p_playerwk);
      g_ram.actwk[ACTWK_PL_AWA].r_ptr = &plawa;
      g_ram.actwk[ACTWK_PL_AWA].u.obj.userflag = 129;
      g_ram.actwk[ACTWK_PL_AWA].u.obj.actfree.plawa.pl_ptr = p_playerwk;
      *work.plmaxspdwk_ptr = g_ram.ssonicflag == 0 ? 0x300 : 0x400;
      *work.pladdspdwk_ptr = g_ram.ssonicflag == 0 ? 6 : 0xC;
      *work.plretspdwk_ptr = g_ram.ssonicflag == 0 ? 0x40 : 0x60;
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
      *work.plmaxspdwk_ptr = g_ram.ssonicflag == 0 ? 0x600 : 0x800;
      *work.pladdspdwk_ptr = g_ram.ssonicflag == 0 ? 0xC : 0x18;
      *work.plretspdwk_ptr = g_ram.ssonicflag == 0 ? 0x80 : 0xC0;
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


static void knuckleswalk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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


static void knucklesjump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.talent_status == 0) {
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
  else {
    glide_chk(p_playerwk, work);
    limitchk(p_playerwk);
    speedset2_g(p_playerwk);
    glide_move(p_playerwk, work);
  }
}


static void glide_move(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  switch (p_playerwk->u.play.talent_status) {
    case 0: break;
    case 1: glide_move_normal(p_playerwk, work); break;
    case 2: glide_move_fall(p_playerwk, work); break;
    case 3: glide_move_slide(p_playerwk); break;
    case 4: glide_move_climb(p_playerwk); break;
    case 5: glide_move_surmount(p_playerwk); break;
  }
}


static void glide_move_normal(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  glidecol(p_playerwk);
  if (g_ram.glide_flag.cd.jump == 1) {
    if (g_ram.glide_flag.cd.push == 0) {
      if (!are_any_trg_buttons_used(g_ram.swdata.down)) {
        p_playerwk->u.play.talent_status = 2;
        p_playerwk->mstno = 33;
        p_playerwk->u.play.cddat.left = p_playerwk->xspeed < 0;
        p_playerwk->xspeed /= 4;
        p_playerwk->sprvsize = p_playerwk->u.play.height;
        p_playerwk->sprhsize = p_playerwk->u.play.width;
      }
      else {
        glide_patchg(p_playerwk);
      }
    }
    else {
      if (g_ram.glide_flag.power.mizuflag == 1) {
        fall_from_wall(p_playerwk);
      }
      else {
        if (p_playerwk->pattimm + 64 & 0xFF >= 128) {
          p_playerwk->u.play.cddat.left = 1;
          SKC_dircol_result result = dircol_l(p_playerwk);
          if (result.offset == 0 && result.offset2 == 0) {
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 1);
            attach_to_wall(p_playerwk);
          }
          else {
            short xposi = fp16_get_integer(p_playerwk->xposi) - (short)p_playerwk->sprvsize - 1;
            glide_move_normal_sub(p_playerwk, xposi);
          }
        }
        else {
          p_playerwk->u.play.cddat.left = 0;
          SKC_dircol_result result = dircol_r(p_playerwk);
          if (result.offset == 0 && result.offset2 == 0) {
            attach_to_wall(p_playerwk);
          }
          else {
            short xposi = fp16_get_integer(p_playerwk->xposi) + (short)p_playerwk->sprvsize + 1;
            glide_move_normal_sub(p_playerwk, xposi);
          }
        }
      }
    }
  }
  else {
    p_playerwk->u.play.cddat.left = p_playerwk->xspeed < 0;
    if (!(direction_sum(p_playerwk->direc.b.b0, 32) & 0xC0)) {
      p_playerwk->xspeed = p_playerwk->mspeed;
      p_playerwk->yspeed = 0;
      knucklesjumpcolsub0(p_playerwk);
    }
    else {
      p_playerwk->u.play.talent_status = 3;
      p_playerwk->patno = 204;
      p_playerwk->pattim = 127;
      p_playerwk->patcnt = 0;
      if (p_playerwk->u.play.air_timer >= 12) {
        work.effectwk_ptr->r_no = 6;
        work.effectwk_ptr->patno = 21;
      }
    }
  }
}


static void attach_to_wall(SKC_sprite_status* p_playerwk) {
  short sound_command = 74;
  if (g_ram.ssonicflag == 0xFF && (unsigned short)p_playerwk->mspeed >= 0x480) {
    g_ram.scr_shake_flg2 = 20;
    pcolhyper(p_playerwk);
    sound_command = 73;
  }
  soundset(sound_command);
  p_playerwk->mspeed = 0;
  p_playerwk->xspeed = 0;
  p_playerwk->yspeed = 0;
  p_playerwk->u.play.talent_status = 4;
  p_playerwk->patno = 183;
  p_playerwk->pattim = 127;
  p_playerwk->patcnt = 0;
  p_playerwk->pattimm = 3;
  fp16_set_fraction(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi));
}


static void glide_move_normal_sub(SKC_sprite_status* p_playerwk, short xposi) {
  if (g_ram.reverse_gravity_flag == 0) {
    short yposi = fp16_get_integer(p_playerwk->yposi) - 11;
    SKC_dircol_result result = edgechk_d3(p_playerwk, xposi, yposi);
    if (result.offset >= 0 && result.offset < 12) {
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
      attach_to_wall(p_playerwk);
    }
    else {
      fall_from_wall(p_playerwk);
    }
  }
  else {
    short yposi = fp16_get_integer(p_playerwk->yposi) + 11 ^ 15;
    SKC_dircol_result result = edgechk_u3(p_playerwk, xposi, yposi);
    if (result.offset >= 0 && result.offset < 12) {
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - result.offset);
      attach_to_wall(p_playerwk);
    }
    else {
      fall_from_wall(p_playerwk);
    }
  }
}


static void fall_from_wall(SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.talent_status = 2;
  p_playerwk->mstno = 33;
  p_playerwk->sprvsize = p_playerwk->u.play.height;
  p_playerwk->sprhsize = p_playerwk->u.play.width;
  g_ram.glide_flag.cd.jump = 1;
}


static void glide_move_fall(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  jumpmove(p_playerwk, work);
  p_playerwk->yspeed += 0x38;
  if (p_playerwk->u.play.cddat.underwater == 1) {
    p_playerwk->yspeed -= 0x28;
  }
  glidecol(p_playerwk);
  if (g_ram.glide_flag.cd.jump == 0) {
    p_playerwk->mspeed = 0;
    p_playerwk->xspeed = 0;
    p_playerwk->yspeed = 0;
    short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
    if (g_ram.reverse_gravity_flag != 0) {
      yoffset = -yoffset;
    }
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
    soundset(76);
    unsigned char direction = direction_sum(p_playerwk->direc.b.b0, 32);
    knucklesjumpcolsub0(p_playerwk);
    if (!(direction & 0xC0)) {
      p_playerwk->u.play.hlock_timer = 15;
      p_playerwk->mstno = 35;
    }
  }
}


static void glide_move_slide(SKC_sprite_status* p_playerwk) {
  bool stand = false;
  if (are_any_trg_buttons_used(g_ram.swdata.down)) {
    if (p_playerwk->xspeed < 0) {
      p_playerwk->xspeed += 0x20;
      if (p_playerwk->xspeed < 0) {
        stand = true;
      }
    }
    else {
      p_playerwk->xspeed -= 0x20;
      if (p_playerwk->xspeed >= 0) {
        stand = true;
      }
    }
  }
  if (!stand) {
    p_playerwk->mspeed = 0;
    p_playerwk->xspeed = 0;
    p_playerwk->yspeed = 0;
    short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
    if (g_ram.reverse_gravity_flag != 0) {
      yoffset = -yoffset;
    }
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
    knucklesjumpcolsub0(p_playerwk);
    p_playerwk->u.play.hlock_timer = 15;
    p_playerwk->mstno = 34;
  }
  else {
    glidecol(p_playerwk);
    SKC_dircol_result result = dircol_d_g(p_playerwk);
    if (result.offset < 14) {
      if (g_ram.reverse_gravity_flag != 0) {
        result.offset = -result.offset;
      }
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
      p_playerwk->direc.b.b0 = result.direction;
      if (!(g_ram.gametimer & 7)) {
        soundset(126);
      }
    }
    else {
      p_playerwk->u.play.talent_status = 2;
      p_playerwk->mstno = 33;
      p_playerwk->sprvsize = p_playerwk->u.play.height;
      p_playerwk->sprhsize = p_playerwk->u.play.width;
      g_ram.glide_flag.cd.jump = 1;
    }
  }
}


static void glide_move_climb(SKC_sprite_status* p_playerwk) {
  if (g_ram.glide_flag.power.mizuflag == 1
      || fp16_get_integer(p_playerwk->xposi) != fp16_get_integer(p_playerwk->xposi)
      || p_playerwk->u.play.cddat.ride == 1) {
    detach_from_wall(p_playerwk);
  }
  else {
    p_playerwk->mspeed = 0;
    p_playerwk->xspeed = 0;
    p_playerwk->yspeed = 0;
    g_ram.scdadr = p_playerwk->u.play.lrb_solid_bit == 13 ? g_ram.scd0adr : g_ram.scd1adr;
    signed char v_movement = 0;
    bool stopped = false;
    if (g_ram.swdata.down.u == 1) {
      if (g_ram.reverse_gravity_flag == 0) {
        SKC_dircol_result result = climbcol(p_playerwk, fp16_get_integer(p_playerwk->yposi) - 11);
        if (result.offset >= 4) {
          surmount_wall(p_playerwk);
        }
        else if (result.offset != 0) {
          stopped = true;
        }
        else {
          short yposi = fp16_get_integer(p_playerwk->yposi) - 8;
          result = vsdircol_u(p_playerwk, fp16_get_integer(p_playerwk->xposi), yposi);
          if (result.offset < 0) {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - result.offset);
          }
          else {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 1);
            if (g_ram.ssonicflag != 0) {
              fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 1);
            }
            if (g_ram.scralim_up != -256) {
              short yposi = g_ram.scralim_up + 16;
              if (yposi > fp16_get_integer(p_playerwk->yposi)) {
                fp16_set_integer(&p_playerwk->yposi, yposi);
              }
            }
          }
          v_movement = 1;
        }
      }
      else {
        SKC_dircol_result result = climbcol(p_playerwk, fp16_get_integer(p_playerwk->yposi) + 11);
        if (result.offset >= 4) {
          surmount_wall(p_playerwk);
        }
        else if (result.offset != 0) {
          stopped = true;
        }
        else {
          short yposi = fp16_get_integer(p_playerwk->yposi) + 8;
          result = vsdircol_d(p_playerwk, fp16_get_integer(p_playerwk->xposi), yposi);
          if (result.offset < 0) {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          }
          else {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
            if (g_ram.ssonicflag != 0) {
              fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
            }
            if (g_ram.scralim_up != -256) {
              short yposi = g_ram.scralim_down + 208;
              if (yposi < fp16_get_integer(p_playerwk->yposi)) {
                fp16_set_integer(&p_playerwk->yposi, yposi);
              }
            }
          }
          v_movement = 1;
        }
      }
    }
    else if (g_ram.swdata.down.d == 1) {
      if (g_ram.reverse_gravity_flag == 0) {
        if (p_playerwk->patno == 189) {
          p_playerwk->patno = 183;
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 3);
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 3);
          if (p_playerwk->u.play.cddat.left == 1) {
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 6);
          }
        }
        SKC_dircol_result result = climbcol(p_playerwk, fp16_get_integer(p_playerwk->yposi) + 11);
        if (result.offset != 0) {
          detach_from_wall(p_playerwk);
        }
        else {
          short yposi = fp16_get_integer(p_playerwk->yposi) + 9;
          result = vsdircol_d(p_playerwk, fp16_get_integer(p_playerwk->xposi), yposi);
          if (result.offset < 0) {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
            p_playerwk->direc.b.b0 = g_ram.dirstk[0];
            p_playerwk->mspeed = 0;
            p_playerwk->xspeed = 0;
            p_playerwk->yspeed = 0;
            knucklesjumpcolsub0(p_playerwk);
            p_playerwk->mstno = 5;
          }
          else {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
            if (g_ram.ssonicflag != 0) {
              fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
            }
            v_movement = -1;
          }
        }
      }
      else {
        if (p_playerwk->patno == 189) {
          p_playerwk->patno = 183;
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 3);
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 3);
          if (p_playerwk->u.play.cddat.left == 1) {
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 6);
          }
        }
        SKC_dircol_result result = climbcol(p_playerwk, fp16_get_integer(p_playerwk->yposi) - 11);
        if (result.offset != 0) {
          detach_from_wall(p_playerwk);
        }
        else {
          short yposi = fp16_get_integer(p_playerwk->yposi) - 9;
          SKC_dircol_result result = vsdircol_u(p_playerwk, fp16_get_integer(p_playerwk->xposi), yposi);
          if (result.offset < 0) {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - result.offset);
            p_playerwk->direc.b.b0 = direction_vmirror(g_ram.dirstk[0]);
            p_playerwk->mspeed = 0;
            p_playerwk->xspeed = 0;
            p_playerwk->yspeed = 0;
            knucklesjumpcolsub0(p_playerwk);
            p_playerwk->mstno = 5;
          }
          else {
            fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 1);
            if (g_ram.ssonicflag != 0) {
              fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 1);
            }
            v_movement = -1;
          }
        }
      }
    }
    if (g_ram.swdata.down.u == 0 && g_ram.swdata.down.d == 0) {
      short yposi = fp16_get_integer(p_playerwk->yposi) + 9;
      SKC_dircol_result result = vsdircol_d(p_playerwk, fp16_get_integer(p_playerwk->xposi), yposi);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
        p_playerwk->direc.b.b0 = g_ram.dirstk[0];
        p_playerwk->mspeed = 0;
        p_playerwk->xspeed = 0;
        p_playerwk->yspeed = 0;
        knucklesjumpcolsub0(p_playerwk);
        p_playerwk->mstno = 5;
        return;
      }
    }
    if (v_movement != 0) {
      if (p_playerwk->pattimm-- == 0) {
        p_playerwk->pattimm = 3;
        unsigned char patno = p_playerwk->patno + v_movement;
        if (patno < 183) {
          patno = 188;
        }
        if (patno > 188) {
          patno = 183;
        }
        p_playerwk->patno = patno;
      }
    }
    if (v_movement != 0 || stopped) {
      p_playerwk->pattim = 32;
      p_playerwk->patcnt = 0;
      if (are_any_trg_buttons_used(g_ram.swdata.pressed)) {
        p_playerwk->yspeed = -0x380;
        p_playerwk->xspeed = p_playerwk->u.play.cddat.left == 1 ? 0x400 : -0x400;
        p_playerwk->u.play.cddat.left ^= 1;
        p_playerwk->u.play.cddat.jump = 1;
        p_playerwk->u.play.jump_flag = 1;
        p_playerwk->sprvsize = 14;
        p_playerwk->sprhsize = 7;
        p_playerwk->mstno = 2;
        p_playerwk->u.play.cddat.ball = 1;
        p_playerwk->u.play.talent_status = 0;
      }
    }
  }
}


static void surmount_wall(SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.talent_status = 5;
  if (p_playerwk->patno != 189) {
    p_playerwk->pattimm = 0;
    glide_move_surmount_sub(p_playerwk);
  }
}


static void detach_from_wall(SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.talent_status = 2;
  p_playerwk->mstno = 33;
  p_playerwk->mstrestart = 33;
  p_playerwk->patno = 203;
  p_playerwk->pattim = 7;
  p_playerwk->patcnt = 1;
  p_playerwk->sprvsize = p_playerwk->u.play.height;
  p_playerwk->sprhsize = p_playerwk->u.play.width;
}


static void glide_move_surmount_sub(SKC_sprite_status* p_playerwk) {
  struct {
    unsigned char patno;
    signed char xoffset;
    signed char yoffset;
    unsigned char pattim;
  }
  tbl[4] = {
    { 189,  3,  -3, 6 },
    { 190,  8, -10, 6 },
    { 191, -8, -12, 6 },
    { 210,  8,  -5, 6 }
  };

  p_playerwk->patno = tbl[p_playerwk->pattimm].patno;
  short xoffset = tbl[p_playerwk->pattimm].xoffset;
  if (p_playerwk->u.play.cddat.left == 1) {
    xoffset = -xoffset;
  }
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + xoffset);
  short yoffset = tbl[p_playerwk->pattimm].yoffset;
  if (g_ram.reverse_gravity_flag != 0) {
    yoffset = -yoffset;
  }
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
  p_playerwk->pattim = tbl[p_playerwk->pattimm].pattim;
  p_playerwk->pattimm += 4;
  p_playerwk->patcnt = 0;
}


static SKC_dircol_result climbcol(SKC_sprite_status* p_playerwk, short yposi) {
  if (p_playerwk->u.play.cddat.left == 0) {
    return vsdircol_r(p_playerwk, fp16_get_integer(p_playerwk->xposi), yposi);
  }
  else {
    return vsdircol_l(p_playerwk, fp16_get_integer(p_playerwk->xposi) - 1, yposi);
  }
}


static void glide_move_surmount(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->pattim != 0) return;

  glide_move_surmount_sub(p_playerwk);
  if (p_playerwk->pattimm == 16) {
    p_playerwk->mspeed = 0;
    p_playerwk->xspeed = 0;
    p_playerwk->yspeed = 0;
    if (p_playerwk->u.play.cddat.left == 1) {
      fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 1);
    }
    knucklesjumpcolsub0(p_playerwk);
    p_playerwk->mstno = 5;
  }
}


static void glide_patchg(SKC_sprite_status* p_playerwk) {
  unsigned char patno_tbl[8] = {
    192, 193, 194, 195, 196, 195, 194, 193
  };

  p_playerwk->pattim = 32;
  p_playerwk->patcnt = 0;
  p_playerwk->mstno = 32;
  p_playerwk->mstrestart = 32;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.cddat.left = 0;
  p_playerwk->patno = patno_tbl[(p_playerwk->pattimm + 16) / 32];
  if (p_playerwk->patno == 196) {
    p_playerwk->u.play.cddat.left = 1;
    p_playerwk->patno = 192;
  }
}


static void glide_chk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.talent_status == 1) {
    short cal_speed = p_playerwk->mspeed;
    if ((unsigned short)cal_speed < 0x400) {
      cal_speed += 8;
    }
    else if ((unsigned short)cal_speed < 0x1800 && !(p_playerwk->pattimm & 0x7F)) {
      cal_speed += 4;
      if (g_ram.ssonicflag != 0) {
        cal_speed += 8;
      }
    }
    p_playerwk->mspeed = cal_speed;
    unsigned char pattimm = p_playerwk->pattimm;
    if (g_ram.swdata.down.l == 1 && pattimm != 128) {
      if (pattimm < 128) {
        pattimm = 256 - pattimm;
      }
      pattimm += 2;
    }
    else if (g_ram.swdata.down.r == 1 && pattimm != 0) {
      if (pattimm >= 128) {
        pattimm = 256 - pattimm;
      }
      pattimm += 2;
    }
    else if (pattimm & 0x7F) {
      pattimm += 2;
    }
    p_playerwk->pattimm = pattimm;
    short sin, cos;
    sinset(p_playerwk->pattimm, &sin, &cos);
    p_playerwk->xspeed = cos * p_playerwk->mspeed / 0x100;
    if (p_playerwk->yspeed >= 0x80) {
      p_playerwk->yspeed -= 0x20;
    }
    else {
      p_playerwk->yspeed += 0x20;
    }
    if (g_ram.scralim_up != -0x100 && g_ram.scralim_up + 16 > fp16_get_integer(p_playerwk->yposi)) {
      p_playerwk->xspeed /= 2;
      p_playerwk->mspeed /= 2;
    }
  }
  if (*work.scra_vline_ptr != 96) {
    if (*work.scra_vline_ptr < 96) {
      *work.scra_vline_ptr += 4;
    }
    *work.scra_vline_ptr -= 2;
  }
}


static void ballwalk(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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


static void balljump(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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
        nkwalk_l(p_playerwk, work);
      }
      if (g_ram.swdata.down.r == 1) {
        nkwalk_r(p_playerwk, work);
      }
      if (!(direction_sum(p_playerwk->direc.b.b0, 32) & 0xC0) && p_playerwk->mspeed == 0) {
        p_playerwk->u.play.cddat.push = 0;
        p_playerwk->mstno = 5;
        bool balancing = false;
        if (p_playerwk->u.play.cddat.ride == 1) {
          SKC_sprite_status* p_ride_obj = &g_ram.actwk[p_playerwk->u.play.ride_obj];
          if (p_ride_obj->u.obj.cddat.die == 0) {
            unsigned char sprhs = p_ride_obj->sprhs * 2 - 2;
            short distance = (short)p_ride_obj->sprhs + fp16_get_integer(p_playerwk->xposi)
                           - fp16_get_integer(p_ride_obj->xposi);
            if (distance >= 2) {
              if (distance >= (short)sprhs) {
                if (p_playerwk->u.play.cddat.left == 0) {
                  p_playerwk->mstno = 6;
                }
                else {
                  p_playerwk->u.play.cddat.left = 0;
                  p_playerwk->pattim = 0;
                  p_playerwk->patcnt = 4;
                  p_playerwk->mstno = 6;
                  p_playerwk->mstrestart = 6;
                }
                balancing = true;
              }
            }
            else {
              if (p_playerwk->u.play.cddat.left == 1) {
                p_playerwk->mstno = 6;
              }
              else {
                p_playerwk->u.play.cddat.left = 1;
                p_playerwk->pattim = 0;
                p_playerwk->patcnt = 4;
                p_playerwk->mstno = 6;
                p_playerwk->mstrestart = 6;
              }
              balancing = true;
            }
          }
        }
        else {
          SKC_dircol_result result = edgechk_d2_g(p_playerwk, fp16_get_integer(p_playerwk->xposi));
          if (result.offset >= 12) {
            if (p_playerwk->u.play.direc_front == 3) {
              if (p_playerwk->u.play.cddat.left == 0) {
                p_playerwk->mstno = 6;
              }
              else {
                p_playerwk->u.play.cddat.left = 0;
                p_playerwk->pattim = 0;
                p_playerwk->patcnt = 4;
                p_playerwk->mstno = 6;
                p_playerwk->mstrestart = 6;
              }
              balancing = true;
            }
            else if (p_playerwk->u.play.direc_below == 3) {
              if (p_playerwk->u.play.cddat.left == 1) {
                p_playerwk->mstno = 6;
              }
              else {
                p_playerwk->u.play.cddat.left = 1;
                p_playerwk->pattim = 0;
                p_playerwk->patcnt = 4;
                p_playerwk->mstno = 6;
                p_playerwk->mstrestart = 6;
              }
              balancing = true;
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
  if ((p_playerwk->direc.b.b0 & 0x3F) && direction_sum(p_playerwk->direc.b.b0, 64) >= 128) return;
  if (p_playerwk->mspeed == 0) return;

  unsigned char add_dir = p_playerwk->mspeed >= 0 ? 64 : 192;
  unsigned char knuckles_dir = direction_sum(p_playerwk->direc.b.b0, add_dir);
  SKC_dircol_result result = dircolm(p_playerwk, knuckles_dir);
  if (result.offset < 0) {
    short add_speed = result.offset * 0x100;
    if (get_zone(g_ram.stageno) == SANDOPOLIS && knuckles_dir >= 128) {
      knuckles_dir = direction_sub(knuckles_dir, 1);
    }
    knuckles_dir = direction_sum(knuckles_dir, 32);

    switch (knuckles_dir & 0xC0) {
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


static void nkwalk_l(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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
    if (!(direction_sum(p_playerwk->direc.b.b0, 32) & 0xC0)
        && cal_speed >= 0x400
        && p_playerwk->u.play.flip_mst.reverse == 0) {
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


static void nkwalk_r(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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
    if (!(direction_sum(p_playerwk->direc.b.b0, 32) & 0xC0)
        && cal_speed <= -0x400
        && p_playerwk->u.play.flip_mst.reverse == 0) {
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


static bool jumpchk(SKC_sprite_status* p_playerwk) {
  if (!are_any_trg_buttons_used(g_ram.swdata.pressed)) return false;

  unsigned char cal_direc = p_playerwk->direc.b.b0;
  if (g_ram.reverse_gravity_flag != 0) {
    cal_direc = direction_vmirror(cal_direc);
  }
  cal_direc = direction_sum(cal_direc, 128);
  SKC_dircol_result result = dircol2(p_playerwk, cal_direc);
  if (result.offset >= 6) {
    short cal_jump = p_playerwk->u.play.cddat.underwater == 0 ? 0x600 : 0x300;
    cal_direc = direction_sub(p_playerwk->direc.b.b0, 64);
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
  if (p_playerwk->u.play.talent_status != 0) return;
  if (!are_any_trg_buttons_used(g_ram.swdata.pressed)) return;

  bool can_transform = g_ram.semeraldcnt >= 7 || (g_ram.emeraldcnt >= 7 && g_ram.DAT_08ffffba == 0);
  if (g_ram.ssonicflag == 0 || !can_transform || g_ram.plring < 50 || g_ram.pltime_f == 0) {
    p_playerwk->u.play.cddat.ball = 0;
    p_playerwk->sprvsize = 10;
    p_playerwk->sprhsize = 10;
    p_playerwk->u.play.cddat.ballj = 0;
    p_playerwk->u.play.talent_status = 1;
    p_playerwk->yspeed += 0x200;
    if (p_playerwk->yspeed < 0) {
      p_playerwk->yspeed = 0;
    }
    p_playerwk->mspeed = 0x400;
    p_playerwk->xspeed = p_playerwk->u.play.cddat.left == 0 ? 0x400 : -0x400;
    p_playerwk->pattimm = p_playerwk->u.play.cddat.left == 0 ? 0 : 128;
    p_playerwk->direc.b.b0 = 0;
    memset(&g_ram.glide_flag, 0, sizeof(g_ram.glide_flag));
    g_ram.glide_flag.cd.jump = 1;
    glide_patchg(p_playerwk);
  }
  else {
    g_ram.ssonicclchg = 1;
    g_ram.ssonicclchgtim = 15;
    g_ram.ssonicringtim = 60;
    p_playerwk->u.play.control_bitfield = 0x81;
    p_playerwk->mstno = 31;
    if (g_ram.semeraldcnt >= 7) {
      g_ram.ssonicflag = 0xFF;
      g_ram.actwk[ACTWK_TRAIL].r_ptr = &imagetrail;
    }
    else {
      g_ram.ssonicflag = 1;
      g_ram.actwk[ACTWK_TRAIL].r_ptr = &sstartrail;
    }
    *work.plmaxspdwk_ptr = 0x800;
    *work.pladdspdwk_ptr = 0x18;
    *work.plretspdwk_ptr = 0xC0;
    p_playerwk->u.play.muteki_timer = 0;
    p_playerwk->u.play.powerdat.muteki = 1;
    soundset(-97);
    bgmset(44);
  }
}


static void glidecol(SKC_sprite_status* p_playerwk) {
  g_ram.scdadr = p_playerwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  unsigned char direction = direction_sub(atan(p_playerwk->xspeed, p_playerwk->yspeed), 32);

  switch (direction & 0xC0) {
    case 0: {
      SKC_dircol_result result = dircol_l2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        p_playerwk->xspeed = 0;
        g_ram.glide_flag.cd.push = 1;
      }
      result = dircol_r2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        p_playerwk->xspeed = 0;
        g_ram.glide_flag.cd.push = 1;
      }
      result = dircol_d_g(p_playerwk);
      if (result.offset < 0) {
        if (g_ram.reverse_gravity_flag != 0) {
          result.offset = -result.offset;
        }
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
        p_playerwk->direc.b.b0 = result.direction;
        p_playerwk->yspeed = 0;
        g_ram.glide_flag.cd.jump = 0;
      }
      break;
    }
    case 64: {
      SKC_dircol_result result = dircol_l2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        p_playerwk->xspeed = 0;
        g_ram.glide_flag.cd.push = 1;
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
            p_playerwk->xspeed = 0;
            g_ram.glide_flag.cd.push = 1;
          }
        }
      }
      else if (p_playerwk->yspeed >= 0) {
        result = dircol_d_g(p_playerwk);
        if (result.offset < 0) {
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          p_playerwk->direc.b.b0 = result.direction;
          p_playerwk->yspeed = 0;
          g_ram.glide_flag.cd.jump = 0;
        }
      }
      break;
    }
    case 128: {
      SKC_dircol_result result = dircol_l2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - result.offset);
        p_playerwk->xspeed = 0;
        g_ram.glide_flag.cd.push = 1;
      }
      result = dircol_r2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        p_playerwk->xspeed = 0;
        g_ram.glide_flag.cd.push = 1;
      }
      result = dircol_u_g(p_playerwk);
      if (result.offset < 0) {
        if (g_ram.reverse_gravity_flag != 0) {
          result.offset = -result.offset;
        }
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - result.offset);
        p_playerwk->yspeed = 0;
      }
      break;
    }
    case 192: {
      SKC_dircol_result result = dircol_r2(p_playerwk);
      if (result.offset < 0) {
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + result.offset);
        p_playerwk->xspeed = 0;
        g_ram.glide_flag.cd.push = 1;
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
      else if (p_playerwk->yspeed >= 0) {
        result = dircol_d_g(p_playerwk);
        if (result.offset < 0) {
          if (g_ram.reverse_gravity_flag != 0) {
            result.offset = -result.offset;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + result.offset);
          p_playerwk->direc.b.b0 = result.direction;
          p_playerwk->yspeed = 0;
          g_ram.glide_flag.cd.jump = 0;
        }
      }
      break;
    }
  }
}


static void jumpcolsub(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.spindash_flag == 0) {
    p_playerwk->mstno = 0;
    knucklesjumpcolsub0(p_playerwk);
  }
  else {
    jumpcolsub1(p_playerwk);
  }
}


void knucklesjumpcolsub0(SKC_sprite_status* p_playerwk) {
  short yoffset = (short)p_playerwk->sprvsize - (short)p_playerwk->u.play.height;
  p_playerwk->sprvsize = p_playerwk->u.play.height;
  p_playerwk->sprhsize = p_playerwk->u.play.width;
  if (p_playerwk->u.play.cddat.ball == 1) {
    p_playerwk->u.play.cddat.ball = 0;
    p_playerwk->mstno = 0;
    if (g_ram.reverse_gravity_flag != 0) {
      yoffset = -yoffset;
    }
    unsigned char cal_direc = direction_sum(p_playerwk->direc.b.b0, 64);
    if (cal_direc >= 128) {
      yoffset = -yoffset;
    }
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
  }
  jumpcolsub1(p_playerwk);
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
  p_playerwk->u.play.talent_status = 0;
  if (p_playerwk->mstno >= 32) {
    p_playerwk->mstno = 0;
  }
}


static void knuckles_damage(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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
    knuckles_damage_sub(p_playerwk);
    limitchk(p_playerwk);
    playposiwkset(p_playerwk);
    patchgmainwrt(p_playerwk);
    actionsub(p_playerwk);
  }
}


static void knuckles_damage_sub(SKC_sprite_status* p_playerwk) {
  if (g_ram.DAT_08fff665 == 0
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


static void knuckles_die(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.debugflag != 0 && g_ram.swdata1.pressed.b == 1) {
    g_ram.editmode = 1;
    g_ram.pl_input_lock_flag = 0;
  }
  else {
    play00die_sub(p_playerwk, work);
    speedset_g(p_playerwk);
    playposiwkset(p_playerwk);
    patchgmainwrt(p_playerwk);
  }
}


static void knuckles_erase(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (p_playerwk->u.play.spindash_ctr == 0) return;

  --p_playerwk->u.play.spindash_ctr;
  if (p_playerwk->u.play.spindash_ctr == 0) {
    g_ram.gameflag = 1;
  }
}


static void knuckles_appear(SKC_sprite_status* p_playerwk, SKC_play_work work) {
  if (g_ram.DAT_08ffee00 == 0 && g_ram.DAT_08ffee02 == 0) {
    p_playerwk->r_no = 2;
  }
  patchgmainwrt(p_playerwk);
  actionsub(p_playerwk);
}


static void knuckles_drown(SKC_sprite_status* p_playerwk, SKC_play_work work) {
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
  patchgmain(p_playerwk);
  if (g_ram.reverse_gravity_flag != 0) {
    p_playerwk->actflg.vflip ^= 1;
  }
  knuckleswrt(p_playerwk);
}


static void patchgmain(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->mstno != p_playerwk->mstrestart) {
    p_playerwk->mstrestart = p_playerwk->mstno;
    p_playerwk->patcnt = 0;
    p_playerwk->pattim = 0;
    p_playerwk->u.play.cddat.push = 0;
  }
  unsigned char* p_chg = knuckleschg[p_playerwk->mstno];
  if (p_chg[0] >= 128) {
    knucklesrunchg(p_playerwk, p_chg[0]);
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


static void knucklesrunchg(SKC_sprite_status* p_playerwk, unsigned char patno) {
  if (patno != 255) {
    knucklesrunchg2(p_playerwk);
  }
  else if (p_playerwk->u.play.flip_mst.reverse == 1 || p_playerwk->direc.b.b1 != 0) {
    playflipchg(p_playerwk);
  }
  else {
    unsigned char direction = p_playerwk->direc.b.b0;
    if (direction < 128 && direction != 0) {
      direction = direction_sub(direction, 1);
    }
    if (p_playerwk->u.play.cddat.left == 0) {
      direction = direction_hmirror(direction_sum(direction, 1));
    }
    direction = direction_sum(direction, 16);
    if (direction >= 128) {
      p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left ^ 1;
      p_playerwk->actflg.vflip = 1;
    }
    else {
      p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
      p_playerwk->actflg.vflip = 0;
    }
    if (p_playerwk->u.play.cddat.push == 1) {
      knucklesrunchg3(p_playerwk);
    }
    else {
      unsigned char patno_add = direction / 16 & 6;
      short cal_speed = abs(p_playerwk->mspeed);
      if (p_playerwk->u.play.powerdat.mizuflag == 1) {
        cal_speed *= 2;
      }
      unsigned char* p_chg = cal_speed >= 0x600 ? nkchg01 : nkchg00;
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
  }
}


static void knucklesrunchg2(SKC_sprite_status* p_playerwk) {
  p_playerwk->actflg.hflip = p_playerwk->u.play.cddat.left;
  p_playerwk->actflg.vflip = 0;
  if (p_playerwk->pattim-- == 0) {
    short cal_speed = abs(p_playerwk->mspeed);
    unsigned char* p_chg = cal_speed >= 0x600 ? nkchg03 : nkchg02;
    cal_speed = -cal_speed + 0x400;
    if (cal_speed < 0) {
      cal_speed = 0;
    }
    p_playerwk->pattim = cal_speed / 0x100;
    patchgmain2(p_playerwk, p_chg);
  }
}


static void knucklesrunchg3(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->pattim-- > 0) return;

  short cal_speed = -abs(p_playerwk->mspeed) + 0x800;
  if (cal_speed < 0) {
    cal_speed = 0;
  }
  p_playerwk->pattim = cal_speed / 0x100;
  patchgmain2(p_playerwk, nkchg04);
}


static unsigned char* knuckleschg[37] = {
  nkchg00,
  nkchg01,
  nkchg02,
  nkchg03,
  nkchg04,
  nkchg05,
  nkchg06,
  nkchg07,
  nkchg08,
  nkchg09,
  nkchg10,
  nkchg11,
  nkchg12,
  nkchg13,
  nkchg14,
  nkchg15,
  nkchg16,
  nkchg17,
  nkchg18,
  nkchg19,
  nkchg20,
  nkchg21,
  nkchg22,
  nkchg23,
  nkchg24,
  nkchg25,
  nkchg26,
  nkchg27,
  nkchg28,
  nkchg29,
  nkchg30,
  nkchg36,
  nkchg31,
  nkchg32,
  nkchg33,
  nkchg34,
  nkchg35
};


static unsigned char nkchg00[10] = { 255, 7, 8, 1, 2, 3, 4, 5, 6, 255 };
static unsigned char nkchg01[10] = { 255, 33, 34, 35, 36, 255, 255, 255, 255, 255 };
static unsigned char nkchg02[10] = { 254, 154, 150, 154, 151, 154, 152, 154, 153, 255 };
static unsigned char nkchg03[10] = { 254, 154, 150, 154, 151, 154, 152, 154, 153, 255 };
static unsigned char nkchg04[10] = { 253, 206, 207, 208, 209, 255, 255, 255, 255, 255 };
static unsigned char nkchg05[152] = {
    5,  86,  86,  86,  86,  86,  86,  86,  86,  86,
   86,  86,  86,  86,  86,  86,  86,  86,  86,  86,
   86,  86,  86,  86,  86,  86,  86,  86,  86,  86,
   86,  86,  86,  86,  86,  86,  86,  86,  86,  86,
   86,  86,  86,  86,  86,  86,  86,  86,  86,  86,
   86, 210, 210, 210, 211, 211, 211, 210, 210, 210,
  211, 211, 211, 210, 210, 210, 211, 211, 211, 210,
  210, 210, 211, 211, 211, 210, 210, 210, 211, 211,
  211, 210, 210, 210, 211, 211, 211, 210, 210, 210,
  211, 211, 211, 210, 210, 210, 211, 211, 211, 210,
  210, 210, 211, 211, 211, 212, 212, 212, 212, 212,
  215, 216, 217, 218, 219, 216, 217, 218, 219, 216,
  217, 218, 219, 216, 217, 218, 219, 216, 217, 218,
  219, 216, 217, 218, 219, 216, 217, 218, 219, 216,
  217, 218, 219, 220, 221, 220, 221, 222, 222, 216,
  215, 255
};
static unsigned char nkchg06[42] = {
    3, 159, 159, 160, 160, 161, 161, 162, 162, 163,
  163, 164, 164, 165, 165, 165, 165, 165, 165, 165,
  165, 165, 165, 165, 165, 165, 165, 165, 166, 166,
  166, 167, 167, 167, 168, 168, 169, 169, 170, 170,
  254,   6
};
static unsigned char nkchg07[5] = { 5, 213, 214, 254, 1 };
static unsigned char nkchg08[5] = { 5, 155, 156, 254, 1 };
static unsigned char nkchg09[12] = { 0, 134, 135, 134, 136, 134, 137, 134, 138, 134, 139, 255 };
static unsigned char nkchg10[23] = {
    9, 186, 197, 198, 198, 198, 198, 198, 198, 199,
  199, 199, 199, 199, 199, 199, 199, 199, 199, 199,
  199, 253, 0
};
static unsigned char nkchg11[3] = { 15, 143, 255 };
static unsigned char nkchg12[38] = {
    3, 161, 161, 162, 162, 163, 163, 164, 164, 165,
  165, 165, 165, 165, 165, 165, 165, 165, 165, 165,
  165, 165, 165, 165, 166, 166, 166, 167, 167, 167,
  168, 168, 169, 169, 170, 170, 254, 6
};
static unsigned char nkchg13[7] = { 3, 157, 158, 159, 160, 253, 0 };
static unsigned char nkchg14[3] = { 7, 192, 255 };
static unsigned char nkchg15[12] = { 5, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 255 };
static unsigned char nkchg16[4] = { 47, 142, 253, 0 };
static unsigned char nkchg17[4] = { 1, 174, 175, 255 };
static unsigned char nkchg18[6] = { 15, 67, 67, 67, 254, 1 };
static unsigned char nkchg19[9] = { 5, 177, 178, 178, 178, 179, 180, 254, 1 };
static unsigned char nkchg20[3] = { 19, 145, 255 };
static unsigned char nkchg21[7] = { 11, 176, 176, 3, 4, 253, 0 };
static unsigned char nkchg22[3] = { 32, 172, 255 };
static unsigned char nkchg23[3] = { 32, 173, 255 };
static unsigned char nkchg24[3] = { 32, 171, 255 };
static unsigned char nkchg25[3] = { 9, 140, 255 };
static unsigned char nkchg26[3] = { 64, 141, 255 };
static unsigned char nkchg27[3] = { 9, 140, 255 };
static unsigned char nkchg28[3] = { 119, 0, 255 };
static unsigned char nkchg29[4] = { 19, 208, 209, 255 };
static unsigned char nkchg30[8] = { 3, 207, 200, 201, 202, 203, 254, 4 };
static unsigned char nkchg31[3] = { 31, 192, 255 };
static unsigned char nkchg32[5] = { 7, 202, 203, 254, 1 };
static unsigned char nkchg33[4] = { 15, 205, 253, 0 };
static unsigned char nkchg34[4] = { 15, 156, 253, 0 };
static unsigned char nkchg35[14] = { 7, 177, 179, 179, 179, 179, 179, 179, 178, 179, 180, 179, 254, 4 };
static unsigned char nkchg36[15] = { 2, 235, 235, 236, 237, 236, 237, 236, 237, 236, 237, 236, 237, 253, 0 };


void knuckleswrt(SKC_sprite_status* p_playerwk) {
  knuckleswrt0(p_playerwk->patno);
}


void knuckleswrt0(unsigned char patno) {
  if (patno == g_ram.playpatno) return;

  g_ram.playpatno = patno;
  knuckleswrt1(patno, 0xD000);
}


void knuckleswrt1(unsigned char patno, unsigned short vram_adr) {
  unsigned short* p_wrtpat = knuckleswrtpat[patno];
  unsigned short cnt = *p_wrtpat++;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = *p_wrtpat++;
    unsigned char* p_source = &knuckles_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}
