#include "playsub.h"
#include <stdlib.h>
#include <string.h>
#include "../data/cg/baria.h"
#include "../data/cg/effect.h"
#include "../data/cg/muteki.h"
#include "../data/cg/plawa.h"
#include "../data/cg/sflicky.h"
#include "../data/cg/sstar.h"
#include "../data/pat/knuckles.h"
#include "../data/pat/play.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/direction.h"
#include "../utils/fp16.h"
#include "../utils/fp8.h"
#include "../action.h"
#include "../actset.h"
#include "../coli.h"
#include "../constants.h"
#include "../dev.h"
#include "../etc.h"
#include "../sound.h"
#include "awa.h"
#include "common.h"
#include "player.h"
static void plawainit(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawamove(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawamove2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawamove3(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawamove4(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawamove5(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawamove6(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawasub(SKC_sprite_status* p_actwk);
static void plawawrt(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void plawamaster(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static signed char* plawachg[15];
static signed char plawachg0[9];
static signed char plawachg1[9];
static signed char plawachg2[9];
static signed char plawachg3[9];
static signed char plawachg4[9];
static signed char plawachg5[9];
static signed char plawachg6[5];
static signed char plawachg7[8];
static signed char plawachg8[8];
static signed char plawachg9[8];
static signed char plawachg10[8];
static signed char plawachg11[8];
static signed char plawachg12[8];
static signed char plawachg13[2];
static signed char plawachg14[6];
static void bariainit(SKC_sprite_status* p_actwk);
static void bariamove(SKC_sprite_status* p_actwk);
static void mutekimove(SKC_sprite_status* p_actwk);
static void muteki_sub(SKC_sprite_status* p_actwk);
static signed char offset_tbl[32][2];
static signed char patno_tbl0[13];
static signed char patno_tbl1[21];
static signed char patno_tbl2[25];
static signed char patno_tbl3[25];
static signed char* bariachg[1];
static signed char bariachg00[12];
static SKC_sprite_pattern* bariapat[6];
static SKC_sprite_pattern bariasp00;
static SKC_sprite_pattern bariasp01;
static SKC_sprite_pattern bariasp02;
static SKC_sprite_pattern bariasp03;
static SKC_sprite_pattern bariasp04;
static SKC_sprite_pattern bariasp05;
static SKC_sprite_pattern* mutekipat[9];
static SKC_sprite_pattern mutekisp00;
static SKC_sprite_pattern mutekisp01;
static SKC_sprite_pattern mutekisp02;
static SKC_sprite_pattern mutekisp03;
static SKC_sprite_pattern mutekisp04;
static SKC_sprite_pattern mutekisp05;
static SKC_sprite_pattern mutekisp06;
static SKC_sprite_pattern mutekisp07;
static SKC_sprite_pattern mutekisp08;
static void effectinit(SKC_sprite_status* p_actwk);
static void effectmove(SKC_sprite_status* p_actwk);
static void effect1move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void effect4move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void effect2move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void effect3move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void effect0move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void effectmove2(SKC_sprite_status* p_actwk);
static void effectmove3(SKC_sprite_status* p_actwk);
static void effectwrt(SKC_sprite_status* p_actwk);
static void effectwrt0(SKC_sprite_status* p_actwk, unsigned char* p_cg);
static signed char* effectchg[5];
static signed char effectchg00[3];
static signed char effectchg01[12];
static signed char effectchg02[9];
static signed char effectchg03[6];
static signed char effectchg04[11];
static SKC_sprite_pattern effectsp00;
static SKC_sprite_pattern effectsp01;
static SKC_sprite_pattern effectsp02;
static SKC_sprite_pattern effectsp03;
static SKC_sprite_pattern effectsp04;
static SKC_sprite_pattern effectsp05;
static SKC_sprite_pattern effectsp06;
static SKC_sprite_pattern effectsp07;
static SKC_sprite_pattern effectsp08;
static SKC_sprite_pattern effectsp09;
static SKC_sprite_pattern effectsp10;
static SKC_sprite_pattern effectsp11;
static SKC_sprite_pattern effectsp12;
static SKC_sprite_pattern effectsp13;
static SKC_sprite_pattern effectsp14;
static SKC_sprite_pattern effectsp15;
static SKC_sprite_pattern effectsp16;
static SKC_sprite_pattern effectsp17;
static SKC_sprite_pattern effectsp18;
static SKC_sprite_pattern effectsp19;
static SKC_sprite_pattern effectsp20;
static SKC_sprite_pattern effectsp21;
static SKC_sprite_pattern effectsp22;
static void vseffectinit(SKC_sprite_status* p_actwk);
static void vseffectmove(SKC_sprite_status* p_actwk);
static void vseffect0move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void vseffect1move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void vseffect2move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void vseffectmove2(SKC_sprite_status* p_actwk);
static signed char* vseffectchg[4];
static signed char vseffectchg00[3];
static signed char vseffectchg01[4];
static signed char vseffectchg02[6];
static signed char vseffectchg03[5];
static SKC_sprite_pattern* vseffectpat[8];
static SKC_sprite_pattern vseffectsp00;
static SKC_sprite_pattern vseffectsp01;
static SKC_sprite_pattern vseffectsp02;
static SKC_sprite_pattern vseffectsp03;
static SKC_sprite_pattern vseffectsp04;
static SKC_sprite_pattern vseffectsp05;
static SKC_sprite_pattern vseffectsp06;
static SKC_sprite_pattern vseffectsp07;
static void sstartrailmove(SKC_sprite_status* p_actwk);
static void sstartrailmovesub(SKC_sprite_status* p_actwk);
static void sstar(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern* sstartrailpat[6];
static SKC_sprite_pattern sstartrailsp00;
static SKC_sprite_pattern sstartrailsp01;
static SKC_sprite_pattern sstartrailsp02;
static SKC_sprite_pattern sstartrailsp03;
static SKC_sprite_pattern* sstarpat[4];
static SKC_sprite_pattern sstarsp00;
static SKC_sprite_pattern sstarsp01;
static SKC_sprite_pattern sstarsp02;
static void hstar(SKC_sprite_status* p_actwk);
static void hstar_move0(SKC_sprite_status* p_actwk);
static void hstar_move1(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern* hstar_pt[6];
static SKC_sprite_pattern hstar_pt00;
static SKC_sprite_pattern hstar_pt01;
static SKC_sprite_pattern hstar_pt02;
static SKC_sprite_pattern hstar_pt03;
static SKC_sprite_pattern hstar_pt04;
static SKC_sprite_pattern hstar_pt05;
static void wspinmove(SKC_sprite_status* p_actwk);
static void fbariamove(SKC_sprite_status* p_actwk);
static void tbariamove(SKC_sprite_status* p_actwk);
static void tbariasub(SKC_sprite_status* p_actwk);
static void tbariasub0(SKC_sprite_status* p_actwk, unsigned char mstno);
static void tbariaspark(SKC_sprite_status* p_actwk);
static void tbariasub1(SKC_sprite_status* p_actwk);
static void abariamove(SKC_sprite_status* p_actwk);
static void bariawrt(SKC_sprite_status* p_actwk);
static signed char* wspinchg[2];
static signed char wspinchg00[3];
static signed char wspinchg01[17];
static signed char* fbariachg[2];
static signed char fbariachg00[20];
static signed char fbariachg01[15];
static signed char* tbariachg[3];
static signed char tbariachg00[44];
static signed char tbariachg01[23];
static signed char tbariachg02[6];
static signed char* abariachg[3];
static signed char abariachg00[56];
static signed char abariachg01[7];
static signed char abariachg02[6];
static SKC_sprite_pattern* fbariapat[25];
static SKC_sprite_pattern fbariasp00;
static SKC_sprite_pattern fbariasp01;
static SKC_sprite_pattern fbariasp02;
static SKC_sprite_pattern fbariasp03;
static SKC_sprite_pattern fbariasp04;
static SKC_sprite_pattern fbariasp05;
static SKC_sprite_pattern fbariasp06;
static SKC_sprite_pattern fbariasp07;
static SKC_sprite_pattern fbariasp08;
static SKC_sprite_pattern fbariasp09;
static SKC_sprite_pattern fbariasp10;
static SKC_sprite_pattern fbariasp11;
static SKC_sprite_pattern fbariasp12;
static SKC_sprite_pattern fbariasp13;
static SKC_sprite_pattern fbariasp14;
static SKC_sprite_pattern fbariasp15;
static SKC_sprite_pattern fbariasp16;
static SKC_sprite_pattern fbariasp17;
static SKC_sprite_pattern fbariasp18;
static SKC_sprite_pattern fbariasp19;
static SKC_sprite_pattern fbariasp20;
static SKC_sprite_pattern fbariasp21;
static SKC_sprite_pattern fbariasp22;
static SKC_sprite_pattern fbariasp23;
static SKC_sprite_pattern fbariasp24;
static unsigned short* fbariawrtpat[25];
static SKC_sprite_pattern* tbariapat[24];
static SKC_sprite_pattern tbariasp00;
static SKC_sprite_pattern tbariasp01;
static SKC_sprite_pattern tbariasp02;
static SKC_sprite_pattern tbariasp03;
static SKC_sprite_pattern tbariasp04;
static SKC_sprite_pattern tbariasp05;
static SKC_sprite_pattern tbariasp06;
static SKC_sprite_pattern tbariasp07;
static SKC_sprite_pattern tbariasp08;
static SKC_sprite_pattern tbariasp09;
static SKC_sprite_pattern tbariasp10;
static SKC_sprite_pattern tbariasp11;
static SKC_sprite_pattern tbariasp12;
static SKC_sprite_pattern tbariasp13;
static SKC_sprite_pattern tbariasp14;
static unsigned short* tbariawrtpat[23];
static SKC_sprite_pattern* abariapat[13];
static SKC_sprite_pattern abariasp00;
static SKC_sprite_pattern abariasp01;
static SKC_sprite_pattern abariasp02;
static SKC_sprite_pattern abariasp03;
static SKC_sprite_pattern abariasp04;
static SKC_sprite_pattern abariasp05;
static SKC_sprite_pattern abariasp06;
static SKC_sprite_pattern abariasp07;
static SKC_sprite_pattern abariasp08;
static SKC_sprite_pattern abariasp09;
static SKC_sprite_pattern abariasp10;
static SKC_sprite_pattern abariasp11;
static SKC_sprite_pattern abariasp12;
static unsigned short* abariawrtpat[13];
static SKC_sprite_pattern* wspinpat[8];
static SKC_sprite_pattern wspin00;
static SKC_sprite_pattern wspin01;
static SKC_sprite_pattern wspin02;
static SKC_sprite_pattern wspin03;
static SKC_sprite_pattern wspin04;
static SKC_sprite_pattern wspin05;
static SKC_sprite_pattern wspin06;
static unsigned short* wspinwrtpat[8];
static void sflicky(SKC_sprite_status* p_actwk);
static void sflicky_move0(SKC_sprite_status* p_actwk);
static void sflicky_move1(SKC_sprite_status* p_actwk, short xposi, short yposi);
static void sflicky_away(SKC_sprite_status* p_actwk);
static void sflicky_move0_sub(SKC_sprite_status* p_actwk, short* p_xposi, short* p_yposi);
static void sflicky_hit(SKC_sprite_status* p_actwk, SKC_sprite_status* p_emywk);
static void sflicky_move1_sub(SKC_sprite_status* p_actwk, short xposi, short yposi);
static void sflicky_scan(SKC_sprite_status* p_actwk);
static void sflicky_emy_chk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_emywk);
static SKC_sprite_pattern* sflicky_pt[3];
static SKC_sprite_pattern sflicky_pt00;
static SKC_sprite_pattern sflicky_pt01;
static SKC_sprite_pattern sflicky_pt02;
static void imagetrail_move(SKC_sprite_status* p_actwk);

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void plawa(SKC_sprite_status* p_actwk) {
  void(*plawa_move_tbl[9])(SKC_sprite_status*, SKC_sprite_status*) = {
    &plawainit,
    &plawamove,
    &plawamove2,
    &plawamove3,
    &plawamove4,
    &plawamaster,
    &plawamove5,
    &plawamove6,
    &plawamove4
  };

  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  plawa_move_tbl[p_actwk->r_no / 2](p_actwk, p_playerwk);
}


static void plawainit(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = p_playerwk == &g_ram.actwk[0] ? awapat : awapat2;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x45C;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->actflg.onscreen = 1;
  p_actwk->sprpri = PRI_1;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_actwk->r_no += 8;
    p_actwk->u.obj.actfree.plawa.digit_timer_init = p_actwk->u.obj.userflag & 0x7F;
    plawamaster(p_actwk, p_playerwk);
  }
  else {
    p_actwk->mstno = p_actwk->u.obj.userflag;
    p_actwk->u.obj.actfree.plawa.xposi_init = fp16_get_integer(p_actwk->xposi);
    p_actwk->yspeed = -0x100;
    plawamove(p_actwk, p_playerwk);
  }
}


static void plawamove(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  patchg(p_actwk, plawachg);
  plawamove2(p_actwk, p_playerwk);
}


static void plawamove2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if ((unsigned short)g_ram.waterposi >= (unsigned short)fp16_get_integer(p_actwk->yposi)) {
    p_actwk->r_no = 6;
    p_actwk->mstno += 7;
    if (p_actwk->mstno > 13) {
      p_actwk->mstno = 13;
    }
    plawamove3(p_actwk, p_playerwk);
  }
  else {
    if (g_ram.watercoliflag != 0) {
      p_actwk->u.obj.actfree.plawa.xposi_init += 4;
    }
    short xposi = awasintbl[p_actwk->direc.b.b0 & 0x7F] + p_actwk->u.obj.actfree.plawa.xposi_init;
    fp16_set_integer(&p_actwk->xposi, xposi);
    p_actwk->direc.b.b0 = direction_sum(p_actwk->direc.b.b0, 1);
    plawasub(p_actwk);
    speedset2(p_actwk);
    if (p_actwk->actflg.onscreen == 1) {
      actionsub(p_actwk);
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void plawamove3(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  plawasub(p_actwk);
  patchg(p_actwk, plawachg);
  plawawrt(p_actwk, p_playerwk);
  actionsub(p_actwk);
}


static void plawamove4(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  frameout(p_actwk);
}


static void plawamove5(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.air_timer <= 12) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      p_actwk->r_no = 14;
      p_actwk->mstno += 7;
      plawamove3(p_actwk, p_playerwk);
    }
    else {
      patchg(p_actwk, plawachg);
      plawawrt(p_actwk, p_playerwk);
      if (p_actwk->actflg.onscreen == 1) {
        actionsub(p_actwk);
      }
      else {
        frameout(p_actwk);
      }
    }
  }
  else {
    frameout(p_actwk);
  }
}


static void plawamove6(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.air_timer > 12) {
    plawamove4(p_actwk, p_playerwk);
  }
  else {
    plawasub(p_actwk);
    patchg(p_actwk, plawachg);
    actionsub(p_actwk);
  }
}


static void plawasub(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer == 0) return;

  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0 && p_actwk->mstno < 7) {
    p_actwk->u.obj.timer = 15;
    p_actwk->yspeed = 0;
    p_actwk->actflg.relative_coordinates = 0;
    p_actwk->actflg.onscreen = 1;
    short xposi = fp16_get_integer(p_actwk->xposi) - (g_ram.scra_h_posit >> 16) + 128;
    fp16_set_integer(&p_actwk->xposi, xposi);
    short yposi = fp16_get_integer(p_actwk->yposi) - (g_ram.scra_v_posit >> 16) + 128;
    fp16_set_integer(&p_actwk->yposi, yposi);
    p_actwk->r_no = 12;
  }
}


signed char awasintbl[128] = {
   0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,
   2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
   3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  2,
   2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,
   0, -1, -1, -1, -1, -1, -2, -2, -2, -2, -2, -3, -3, -3, -3, -3,
  -3, -3, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4,
  -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -3,
  -3, -3, -3, -3, -3, -3, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1
};


static void plawawrt(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_actwk->patno < 9 || p_actwk->patno >= 19) return;
  if (p_actwk->patno == p_actwk->u.obj.actfree.plawa.prev_patno) return;

  p_actwk->u.obj.wrt.prev_patno = p_actwk->patno;
  unsigned char* p_source = &plawa_cg[(p_actwk->patno - 9) * 192];
  unsigned short vram_adr = p_playerwk == &g_ram.actwk[0] ? 0xFC00 : 0xFE00;
  memcpy(&g_vram[vram_adr], p_source, 192);
}


static void plawamaster(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_actwk->u.obj.actfree.plawa.freeze_timer == 0 && p_playerwk->r_no >= 6) return;
  if (p_actwk->u.obj.actfree.plawa.freeze_timer == 0 && p_playerwk->u.play.powerdat.abaria == 1) return;
  if (p_actwk->u.obj.actfree.plawa.freeze_timer == 0 && g_ram.ssonicflag == 0xFF) return;
  if (p_actwk->u.obj.actfree.plawa.freeze_timer == 0 && p_playerwk->u.play.cddat.underwater == 0) return;

  bool make_bubble = false;
  if (p_actwk->u.obj.actfree.plawa.freeze_timer == 0) {
    if (p_actwk->u.obj.timer-- == 0) {
      p_actwk->u.obj.timer = 59;
      p_actwk->u.obj.actfree.plawa.bitfield = 1;
      p_actwk->u.obj.actfree.plawa.pending_bubble_cnt = random() & 1;

      switch (p_playerwk->u.play.air_timer) {
        case 30: break;
        case 29: break;
        case 28: break;
        case 27: break;
        case 26: break;
        case 25:
          if (p_playerwk == &g_ram.actwk[0]) {
            soundset(-87);
          }
          break;
        case 24: break;
        case 23: break;
        case 22: break;
        case 21: break;
        case 20:
          if (p_playerwk == &g_ram.actwk[0]) {
            soundset(-87);
          }
          break;
        case 19: break;
        case 18: break;
        case 17: break;
        case 16: break;
        case 15:
          if (p_playerwk == &g_ram.actwk[0]) {
            soundset(-87);
          }
          break;
        case 14: break;
        case 13: break;
        case 12:
          if (p_playerwk == &g_ram.actwk[0]) {
            bgmset(49);
          }
          // fall-through
        case 11:
        case 10:
        case  9:
        case  8:
        case  7:
        case  6:
        case  5:
        case  4:
        case  3:
        case  2:
        case  1:
        case  0:
          if (p_actwk->u.obj.actfree.plawa.digit_timer-- == 0) {
            p_actwk->u.obj.actfree.plawa.digit_timer = p_actwk->u.obj.actfree.plawa.digit_timer_init;
            SET_BIT(p_actwk->u.obj.actfree.plawa.bitfield, 7);
          }
          break;
      }

      if (p_playerwk->u.play.air_timer-- == 0) {
        p_playerwk->u.play.control_bitfield = 0x81;
        soundset(59);
        p_actwk->u.obj.actfree.plawa.pending_bubble_cnt = 10;
        p_actwk->u.obj.actfree.plawa.bitfield = 1;
        p_actwk->u.obj.actfree.plawa.freeze_timer = 120;
        plairset(p_playerwk);
        jumpcolsub0(p_playerwk);
        p_playerwk->mstno = 23;
        p_playerwk->u.play.cddat.jump = 1;
        p_playerwk->sproffset.pr = 1;
        p_playerwk->yspeed = 0;
        p_playerwk->xspeed = 0;
        p_playerwk->mspeed = 0;
        p_playerwk->r_no = 12;
        if (p_playerwk == &g_ram.actwk[0]) {
          g_ram.scroll_start = 1;
        }
        return;
      }
      else {
        make_bubble = true;
      }
    }
    else if (p_actwk->u.obj.actfree.plawa.bitfield != 0) {
      if (p_actwk->u.obj.actfree.plawa.bubble_timer-- == 0) {
        make_bubble = true;
      }
    }
  }
  else {
    p_playerwk->mstno = 23;
    --p_actwk->u.obj.actfree.plawa.freeze_timer;
    if (p_actwk->u.obj.actfree.plawa.freeze_timer == 0) {
      p_playerwk->r_no = 6;
    }
    else if (p_actwk->u.obj.actfree.plawa.bitfield != 0) {
      if (p_actwk->u.obj.actfree.plawa.bubble_timer-- == 0) {
        make_bubble = true;
      }
    }
  }
  if (make_bubble) {
    p_actwk->u.obj.actfree.plawa.bubble_timer = (random() & 0xF) + 8;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = p_actwk->r_ptr;
      fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_playerwk->xposi));
      if (p_playerwk->u.play.cddat.left == 1) {
        result.actwk_ptr->direc.b.b0 = 64;
      }
      short xoffset = p_playerwk->u.play.cddat.left == 0 ? 6 : -6;
      fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(result.actwk_ptr->xposi) + xoffset);
      fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_playerwk->yposi));
      result.actwk_ptr->u.obj.ko = p_actwk->u.obj.ko;
      result.actwk_ptr->u.obj.userflag = 6;
      if (p_actwk->u.obj.actfree.plawa.freeze_timer != 0) {
        p_actwk->u.obj.actfree.plawa.bubble_timer &= 7;
        short yposi = fp16_get_integer(p_playerwk->yposi) - 12;
        fp16_set_integer(&result.actwk_ptr->yposi, yposi);
        result.actwk_ptr->direc.b.b0 = random() & 0xFF;
        if (!(g_ram.gametimer & 3)) {
          result.actwk_ptr->u.obj.userflag = 14;
        }
      }
      else if (BIT_IS_SET(p_actwk->u.obj.actfree.plawa.bitfield, 7) && p_playerwk->u.play.air_timer < 12) {
        if (!(random() & 3) && !BIT_IS_SET(p_actwk->u.obj.actfree.plawa.bitfield, 6)) {
          SET_BIT(p_actwk->u.obj.actfree.plawa.bitfield, 6);
          result.actwk_ptr->u.obj.userflag = p_playerwk->u.play.air_timer / 2;
          p_actwk->u.obj.timer = 28;
        }
        if (p_actwk->u.obj.actfree.plawa.pending_bubble_cnt == 0
            && !BIT_IS_SET(p_actwk->u.obj.actfree.plawa.bitfield, 6)) {
          SET_BIT(p_actwk->u.obj.actfree.plawa.bitfield, 6);
          result.actwk_ptr->u.obj.userflag = p_playerwk->u.play.air_timer / 2;
          p_actwk->u.obj.timer = 28;
        }
      }
      if (p_actwk->u.obj.actfree.plawa.pending_bubble_cnt-- == 0) {
        p_actwk->u.obj.actfree.plawa.bitfield = 0;
      }
    }
  }
}


void plairset(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.air_timer <= 12 && p_playerwk == &g_ram.actwk[0]) {
    short sound_command = g_ram.bgm_act;
    if (p_playerwk->u.play.powerdat.muteki == 1 || g_ram.ssonicflag != 0) {
      sound_command = 44;
    }
    bgmset(sound_command);
  }
  p_playerwk->u.play.air_timer = 30;
}


static signed char* plawachg[15] = {
  plawachg0,
  plawachg1,
  plawachg2,
  plawachg3,
  plawachg4,
  plawachg5,
  plawachg6,
  plawachg7,
  plawachg8,
  plawachg9,
  plawachg10,
  plawachg11,
  plawachg12,
  plawachg13,
  plawachg14
};


static signed char plawachg0[9] = { 5, 0, 1, 2, 3, 4, 9, 13, -4 };
static signed char plawachg1[9] = { 5, 0, 1, 2, 3, 4, 12, 18, -4 };
static signed char plawachg2[9] = { 5, 0, 1, 2, 3, 4, 12, 17, -4 };
static signed char plawachg3[9] = { 5, 0, 1, 2, 3, 4, 11, 16, -4 };
static signed char plawachg4[9] = { 5, 0, 1, 2, 3, 4, 12, 15, -4 };
static signed char plawachg5[9] = { 5, 0, 1, 2, 3, 4, 10, 14, -4 };
static signed char plawachg6[5] = { 14, 0, 1, 2, -4 };
static signed char plawachg7[8] = { 7, 22, 13, 22, 13, 22, 13, -4 };
static signed char plawachg8[8] = { 7, 22, 18, 22, 18, 22, 18, -4 };
static signed char plawachg9[8] = { 7, 22, 17, 22, 17, 22, 17, -4 };
static signed char plawachg10[8] = { 7, 22, 16, 22, 16, 22, 16, -4 };
static signed char plawachg11[8] = { 7, 22, 15, 22, 15, 22, 15, -4 };
static signed char plawachg12[8] = { 7, 22, 14, 22, 14, 22, 14, -4 };
static signed char plawachg13[2] = { 14, -4 };
static signed char plawachg14[6] = { 14, 1, 2, 3, 4, -4 };


void baria(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler baria_move_tbl[2] = {
    &bariainit,
    &bariamove
  };

  baria_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void bariainit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = bariapat;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 24;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x79C;
  bariamove(p_actwk);
}


static void bariamove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_playerwk->u.play.powerdat.muteki == 0) {
    if (p_playerwk->u.play.powerdat.baria == 1) {
      fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
      p_actwk->u.obj.cddat.right = p_playerwk->u.play.cddat.left;
      p_actwk->u.obj.cddat.down = p_playerwk->u.play.cddat.jump;
      p_actwk->sproffset.pr = p_playerwk->sproffset.pr;
      patchg(p_actwk, bariachg);
      actionsub(p_actwk);
    }
    else {
      frameout(p_actwk);
    }
  }
}


void muteki(SKC_sprite_status* p_actwk) {
  struct {
    signed char* patno_tbl_ptr;
    unsigned char offset_tbl_index0;
    unsigned char offset_tbl_index1;
  }
  tbl[4] = {
    { patno_tbl0,  4,  0 },
    { patno_tbl1, 11,  0 },
    { patno_tbl2, 13, 32 },
    { patno_tbl3, 13, 44 }
  };

  memcpy(&g_vram[0xF380], muteki_cg, sizeof(muteki_cg));
  unsigned char ko = p_actwk->u.obj.ko;

  for (int i = 0; i < 4; ++i) {
    p_actwk[i].r_ptr = &muteki_sub;
    p_actwk[i].patbase = mutekipat;
    memset(&p_actwk[i].sproffset, 0, sizeof(p_actwk[i].sproffset));
    p_actwk[i].sproffset.gfx = 0x79C;
    p_actwk[i].sprpri = PRI_1;
    p_actwk[i].actflg.relative_coordinates = 1;
    p_actwk[i].actflg.compound = 1;
    p_actwk[i].sprhs = 16;
    p_actwk[i].u.obj.compound.child_cnt = 2;
    p_actwk[i].u.obj.ko = ko;
    p_actwk[i].u.obj.actfree.muteki.id = i;
    p_actwk[i].u.obj.actfree.muteki.patno_tbl_ptr = tbl[i].patno_tbl_ptr;
    p_actwk[i].u.obj.actfree.muteki.offset_tbl_index0 = tbl[i].offset_tbl_index0;
    p_actwk[i].u.obj.actfree.muteki.offset_tbl_index1 = tbl[i].offset_tbl_index1;
  }

  p_actwk->r_ptr = &mutekimove;
  mutekimove(p_actwk);
}


static void mutekimove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (g_ram.ssonicflag != 0 || g_ram.smilesflag != 0 || p_playerwk->u.play.powerdat.muteki == 0) {
    frameout(p_actwk);
  }
  else {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
    signed char patno = patno_tbl0[p_actwk->u.obj.actfree.muteki.patno_tbl_index];
    if (patno < 0) {
      p_actwk->u.obj.actfree.muteki.patno_tbl_index = 0;
      patno = patno_tbl0[p_actwk->u.obj.actfree.muteki.patno_tbl_index];
    }
    ++p_actwk->u.obj.actfree.muteki.patno_tbl_index;
    unsigned char index = p_actwk->u.obj.actfree.muteki.offset_tbl_index0 & 0x1F;
    p_actwk->u.obj.compound.children[0].xposi = fp16_get_integer(p_actwk->xposi) + offset_tbl[index / 2][0];
    p_actwk->u.obj.compound.children[0].yposi = fp16_get_integer(p_actwk->yposi) + offset_tbl[index / 2][1];
    p_actwk->u.obj.compound.children[0].patno = patno;
    index = index + 32 & 0x3E;
    p_actwk->u.obj.compound.children[1].xposi = fp16_get_integer(p_actwk->xposi) + offset_tbl[index / 2][0];
    p_actwk->u.obj.compound.children[1].yposi = fp16_get_integer(p_actwk->yposi) + offset_tbl[index / 2][1];
    p_actwk->u.obj.compound.children[1].patno = patno;
    p_actwk->u.obj.actfree.muteki.offset_tbl_index0 += p_playerwk->u.play.cddat.left == 0 ? 18 : -18;
    actionsub(p_actwk);
  }
}


static void muteki_sub(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (g_ram.ssonicflag != 0 || g_ram.smilesflag != 0 || p_playerwk->u.play.powerdat.muteki == 0) {
    frameout(p_actwk);
  }
  else {
    unsigned short index = g_ram.plposiwkadr - p_actwk->u.obj.actfree.muteki.id * 3;
    fp16_set_integer(&p_actwk->xposi, g_ram.playposiwk[index].x);
    fp16_set_integer(&p_actwk->yposi, g_ram.playposiwk[index].y);
    signed char patno = p_actwk->u.obj.actfree.muteki.patno_tbl_ptr[p_actwk->u.obj.actfree.muteki.patno_tbl_index];
    if (patno < 0) {
      p_actwk->u.obj.actfree.muteki.patno_tbl_index = 0;
      patno = p_actwk->u.obj.actfree.muteki.patno_tbl_ptr[p_actwk->u.obj.actfree.muteki.patno_tbl_index];
    }
    index = p_actwk->u.obj.actfree.muteki.patno_tbl_index + p_actwk->u.obj.actfree.muteki.offset_tbl_index0;
    signed char patno2 = p_actwk->u.obj.actfree.muteki.patno_tbl_ptr[index];
    ++p_actwk->u.obj.actfree.muteki.patno_tbl_index;
    index = p_actwk->u.obj.actfree.muteki.offset_tbl_index1 & 0x3E;
    p_actwk->u.obj.compound.children[0].xposi = fp16_get_integer(p_actwk->xposi) + offset_tbl[index / 2][0];
    p_actwk->u.obj.compound.children[0].yposi = fp16_get_integer(p_actwk->yposi) + offset_tbl[index / 2][1];
    p_actwk->u.obj.compound.children[0].patno = patno2;
    index = index + 32 & 0x3E;
    p_actwk->u.obj.compound.children[1].xposi = fp16_get_integer(p_actwk->xposi) + offset_tbl[index / 2][0];
    p_actwk->u.obj.compound.children[1].yposi = fp16_get_integer(p_actwk->yposi) + offset_tbl[index / 2][1];
    p_actwk->u.obj.compound.children[1].patno = patno;
    p_actwk->u.obj.actfree.muteki.offset_tbl_index1 += p_playerwk->u.play.cddat.left == 0 ? 2 : -2;
    actionsub(p_actwk);
  }
}


static signed char offset_tbl[32][2] = {
  {  15,   0 },
  {  15,   3 },
  {  14,   6 },
  {  13,   8 },
  {  11,  11 },
  {   8,  13 },
  {   6,  14 },
  {   3,  15 },
  {   0,  16 },
  {  -4,  15 },
  {  -7,  14 },
  {  -9,  13 },
  { -12,  11 },
  { -14,   8 },
  { -15,   6 },
  { -16,   3 },
  { -16,   0 },
  { -16,  -4 },
  { -15,  -7 },
  { -14,  -9 },
  { -12, -12 },
  {  -9, -14 },
  {  -7, -15 },
  {  -4, -16 },
  {  -1, -16 },
  {   3, -16 },
  {   6, -15 },
  {   8, -14 },
  {  11, -12 },
  {  13,  -9 },
  {  14,  -7 },
  {  15,  -4 }
};


static signed char patno_tbl0[13] = { 8, 5, 7, 6, 6, 7, 5, 8, 6, 7, 7, 6, -1 };
static signed char patno_tbl1[21] = { 8, 7, 6, 5, 4, 3, 4, 5, 6, 7, -1, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4 };
static signed char patno_tbl2[25] = { 8, 7, 6, 5, 4, 3, 2, 3, 4, 5, 6, 7, -1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3 };
static signed char patno_tbl3[25] = { 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, -1, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2 };


static signed char* bariachg[1] = {
  bariachg00
};


static signed char bariachg00[12] = { 0, 5, 0, 5, 1, 5, 2, 5, 3, 5, 4, -1 };


static SKC_sprite_pattern* bariapat[6] = {
  &bariasp00,
  &bariasp01,
  &bariasp02,
  &bariasp03,
  &bariasp04,
  &bariasp05
};


static SKC_sprite_pattern bariasp00 = {
  4,
  {
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0800,   0 },
    {   0, 5, 0x1000, -16 },
    {   0, 5, 0x1800,   0 },
  }
};
static SKC_sprite_pattern bariasp01 = {
  4,
  {
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0804,   0 },
    {   0, 5, 0x1004, -16 },
    {   0, 5, 0x1804,   0 },
  }
};
static SKC_sprite_pattern bariasp02 = {
  4,
  {
    { -16, 5, 0x0008, -16 },
    { -16, 5, 0x0808,   0 },
    {   0, 5, 0x1008, -16 },
    {   0, 5, 0x1808,   0 },
  }
};
static SKC_sprite_pattern bariasp03 = {
  4,
  {
    { -16, 5, 0x000C, -16 },
    { -16, 5, 0x080C,   0 },
    {   0, 5, 0x100C, -16 },
    {   0, 5, 0x180C,   0 },
  }
};
static SKC_sprite_pattern bariasp04 = {
  4,
  {
    { -16, 5, 0x0010, -16 },
    { -16, 5, 0x0810,   0 },
    {   0, 5, 0x1010, -16 },
    {   0, 5, 0x1810,   0 },
  }
};
static SKC_sprite_pattern bariasp05 = {
  4,
  {
    { -32, 11, 0x0014, -24 },
    { -32, 11, 0x0814,   0 },
    {   0, 11, 0x1014, -24 },
    {   0, 11, 0x1814,   0 },
  }
};


static SKC_sprite_pattern* mutekipat[9] = {
  &mutekisp00,
  &mutekisp01,
  &mutekisp02,
  &mutekisp03,
  &mutekisp04,
  &mutekisp05,
  &mutekisp06,
  &mutekisp07,
  &mutekisp08
};


static SKC_sprite_pattern mutekisp00 = {
  0,
  {
  }
};
static SKC_sprite_pattern mutekisp01 = {
  1,
  {
    { -8, 0, 0x0000, -4 },
  }
};
static SKC_sprite_pattern mutekisp02 = {
  1,
  {
    { -8, 0, 0x0001, -4 },
  }
};
static SKC_sprite_pattern mutekisp03 = {
  1,
  {
    { -8, 1, 0x0002, -4 },
  }
};
static SKC_sprite_pattern mutekisp04 = {
  1,
  {
    { -8, 1, 0x0004, -4 },
  }
};
static SKC_sprite_pattern mutekisp05 = {
  1,
  {
    { -8, 1, 0x0006, -4 },
  }
};
static SKC_sprite_pattern mutekisp06 = {
  1,
  {
    { -8, 5, 0x0008, -8 },
  }
};
static SKC_sprite_pattern mutekisp07 = {
  1,
  {
    { -8, 5, 0x000C, -8 },
  }
};
static SKC_sprite_pattern mutekisp08 = {
  1,
  {
    { -16, 15, 0x0010, -16 },
  }
};


void effect(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler effect_move_tbl[4] = {
    &effectinit,
    &effectmove,
    &effectmove2,
    &effectmove3
  };

  effect_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void effectinit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = effectpat;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 16;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x7E0;
  p_actwk->u.obj.ko = 0;
  p_actwk->u.obj.actfree.effect.vram_offset = 0xFC00;
  if (p_actwk != &g_ram.actwk[ACTWK_PL_EFFECT]) {
    p_actwk->u.obj.actfree.effect.miles = true;
    if (g_ram.play_type != PLAY_TYPE_MILES) {
      p_actwk->sproffset.gfx = 0x7F0;
      p_actwk->u.obj.ko = 1;
      p_actwk->u.obj.actfree.effect.vram_offset = 0xFE00;
    }
  }
  effectmove(p_actwk);
}


static void effectmove(SKC_sprite_status* p_actwk) {
  void(*effect_move_tbl[5])(SKC_sprite_status*, SKC_sprite_status*) = {
    &effect0move,
    &effect1move,
    &effect2move,
    &effect3move,
    &effect4move
  };

  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  effect_move_tbl[p_actwk->mstno](p_actwk, p_playerwk);
}


static void effect1move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  fp16_set_integer(&p_actwk->yposi, g_ram.waterposi - 2);
  if (p_actwk->mstrestart == 0) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
    memset(&p_actwk->u.obj.cddat, 0, sizeof(p_actwk->u.obj.cddat));
    p_actwk->sproffset.pr = 0;
  }
  effect0move(p_actwk, p_playerwk);
}


static void effect4move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_actwk->mstrestart == 0) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
    memset(&p_actwk->u.obj.cddat, 0, sizeof(p_actwk->u.obj.cddat));
    p_actwk->sproffset.pr = 0;
  }
  patchg(p_actwk, effectchg);
  effectwrt0(p_actwk, watereffect_cg);
  actionsub(p_actwk);
}


static void effect2move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.air_timer >= 12 && p_playerwk->r_no <= 4 && p_playerwk->u.play.spindash_flag != 0) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
    p_actwk->u.obj.cddat.right = p_playerwk->u.play.cddat.left;
    p_actwk->u.obj.cddat.down = g_ram.reverse_gravity_flag;
    short yoffset = g_ram.reverse_gravity_flag == 0 ? 4 : -4;
    if (p_actwk->u.obj.actfree.effect.miles) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi) - yoffset);
    }
    if (p_actwk->mstrestart == 0) {
      p_actwk->sproffset.pr = p_playerwk->sproffset.pr;
    }
    effect0move(p_actwk, p_playerwk);
  }
  else {
    p_actwk->mstno = 0;
  }
}


static void effect3move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.air_timer >= 12 && p_playerwk->u.play.cddat.underwater == 0) {
    effect0move(p_actwk, p_playerwk);
  }
  else {
    p_actwk->mstno = 0;
  }
}


static void effect0move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  patchg(p_actwk, effectchg);
  effectwrt(p_actwk);
  actionsub(p_actwk);
}


static void effectmove2(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void effectmove3(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  short yoffset = 16;
  bool dust = false;
  if (p_playerwk->mstno == 13) {
    dust = true;
  }
  else if (p_playerwk->u.play.character == KNUCKLES) {
    yoffset = 6;
    if (p_playerwk->u.play.talent_status == 3) {
      dust = true;
    }
  }
  if (!dust) {
    p_actwk->r_no = 2;
    p_actwk->u.obj.timer = 0;
  }
  else {
    if (p_actwk->u.obj.timer-- == 0) {
      p_actwk->u.obj.timer = 3;
      if (p_playerwk->u.play.cddat.underwater == 0) {
        SKC_actwkchk_result result = actwkchk();
        if (result.actwk_ptr != 0) {
          result.actwk_ptr->r_ptr = p_actwk->r_ptr;
          fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_playerwk->xposi));
          fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_playerwk->yposi));
          if (p_actwk->u.obj.actfree.effect.miles) {
            yoffset -= 4;
          }
          if (g_ram.reverse_gravity_flag != 0) {
            yoffset = -yoffset;
          }
          fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_playerwk->yposi) + yoffset);
          memset(&result.actwk_ptr->u.obj.cddat, 0, sizeof(result.actwk_ptr->u.obj.cddat));
          result.actwk_ptr->mstno = 3;
          result.actwk_ptr->r_no += 2;
          result.actwk_ptr->patbase = p_actwk->patbase;
          result.actwk_ptr->actflg = p_actwk->actflg;
          result.actwk_ptr->sprpri = PRI_1;
          result.actwk_ptr->sprhs = 4;
          result.actwk_ptr->sproffset = p_actwk->sproffset;
          result.actwk_ptr->u.obj.ko = p_actwk->u.obj.ko;
          result.actwk_ptr->sproffset.pr = p_playerwk->sproffset.pr;
        }
      }
    }
    effectwrt(p_actwk);
  }
}


static void effectwrt(SKC_sprite_status* p_actwk) {
  effectwrt0(p_actwk, dusteffect_cg);
}


static void effectwrt0(SKC_sprite_status* p_actwk, unsigned char* p_cg) {
  if (p_actwk->patno == p_actwk->u.obj.wrt.prev_patno) return;

  p_actwk->u.obj.wrt.prev_patno = p_actwk->patno;
  unsigned short* p_wrtpat = effectwrtpat[p_actwk->patno];
  unsigned short cnt = *p_wrtpat++;
  unsigned short vram_adr = p_actwk->u.obj.actfree.effect.vram_offset;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = *p_wrtpat++;
    unsigned char* p_source = &p_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


static signed char* effectchg[5] = {
  effectchg00,
  effectchg01,
  effectchg02,
  effectchg03,
  effectchg04
};


static signed char effectchg00[3] = { 31, 0, -1 };
static signed char effectchg01[12] = { 3, 1, 2, 3, 4, 5, 6, 7, 8, 9, -3, 0 };
static signed char effectchg02[9] = { 1, 10, 11, 12, 13, 14, 15, 16, -1 };
static signed char effectchg03[6] = { 3, 17, 18, 19, 20, -4 };
static signed char effectchg04[11] = { 5, 22, 23, 24, 25, 26, 27, 28, 29, -3, 0 };


SKC_sprite_pattern* effectpat[30] = {
  &effectsp00,
  &effectsp01,
  &effectsp02,
  &effectsp03,
  &effectsp04,
  &effectsp05,
  &effectsp06,
  &effectsp07,
  &effectsp08,
  &effectsp09,
  &effectsp10,
  &effectsp11,
  &effectsp12,
  &effectsp13,
  &effectsp14,
  &effectsp15,
  &effectsp16,
  &effectsp17,
  &effectsp18,
  &effectsp19,
  &effectsp20,
  &effectsp00,
  &effectsp21,
  &effectsp22,
  &effectsp22,
  &effectsp22,
  &effectsp22,
  &effectsp22,
  &effectsp22,
  &effectsp22
};


static SKC_sprite_pattern effectsp00 = {
  0,
  {}
};
static SKC_sprite_pattern effectsp01 = {
  1,
  {
    { -14, 9, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp02 = {
  1,
  {
    { -30, 15, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp03 = {
  1,
  {
    { -30, 15, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp04 = {
  1,
  {
    { -30, 15, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp05 = {
  1,
  {
    { -30, 15, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp06 = {
  1,
  {
    { -22, 14, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp07 = {
  1,
  {
    { -14, 13, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp08 = {
  1,
  {
    { -6, 12, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp09 = {
  1,
  {
    { -6, 12, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp10 = {
  1,
  {
    { 4, 13, 0x0000, -32 },
  }
};
static SKC_sprite_pattern effectsp11 = {
  1,
  {
    { 4, 13, 0x0000, -32 },
  }
};
static SKC_sprite_pattern effectsp12 = {
  1,
  {
    { 4, 13, 0x0000, -32 },
  }
};
static SKC_sprite_pattern effectsp13 = {
  1,
  {
    { -4, 14, 0x0000, -32 },
  }
};
static SKC_sprite_pattern effectsp14 = {
  1,
  {
    { -4, 14, 0x0000, -32 },
  }
};
static SKC_sprite_pattern effectsp15 = {
  1,
  {
    { -4, 14, 0x0000, -32 },
  }
};
static SKC_sprite_pattern effectsp16 = {
  1,
  {
    { -4, 14, 0x0000, -32 },
  }
};
static SKC_sprite_pattern effectsp17 = {
  1,
  {
    { -8, 5, 0x0000, -8 },
  }
};
static SKC_sprite_pattern effectsp18 = {
  1,
  {
    { -8, 5, 0x0004, -8 },
  }
};
static SKC_sprite_pattern effectsp19 = {
  1,
  {
    { -8, 5, 0x0008, -8 },
  }
};
static SKC_sprite_pattern effectsp20 = {
  1,
  {
    { -8, 5, 0x000C, -8 },
  }
};
static SKC_sprite_pattern effectsp21 = {
  1,
  {
    { -24, 14, 0x0000, -16 },
  }
};
static SKC_sprite_pattern effectsp22 = {
  1,
  {
    { -32, 15, 0x0000, -16 },
  }
};


static unsigned short effectw00[1] = { 0 };
static unsigned short effectw01[2] = { 1, 0x5000 };
static unsigned short effectw02[2] = { 1, 0xF006 };
static unsigned short effectw03[2] = { 1, 0xF016 };
static unsigned short effectw04[2] = { 1, 0xF026 };
static unsigned short effectw05[2] = { 1, 0xF036 };
static unsigned short effectw06[2] = { 1, 0xB046 };
static unsigned short effectw07[2] = { 1, 0x7052 };
static unsigned short effectw08[2] = { 1, 0x305A };
static unsigned short effectw09[2] = { 1, 0x305E };
static unsigned short effectw10[2] = { 1, 0x7062 };
static unsigned short effectw11[2] = { 1, 0x706A };
static unsigned short effectw12[2] = { 1, 0x7072 };
static unsigned short effectw13[2] = { 1, 0xB07A };
static unsigned short effectw14[2] = { 1, 0xB086 };
static unsigned short effectw15[2] = { 1, 0xB092 };
static unsigned short effectw16[2] = { 1, 0xB09E };
static unsigned short effectw17[1] = { 0 };
static unsigned short effectw18[2] = { 1, 0xF0AA };
static unsigned short effectw19[2] = { 1, 0xB000 };
static unsigned short effectw20[2] = { 1, 0xF00C };
static unsigned short effectw21[2] = { 1, 0xF01C };
static unsigned short effectw22[2] = { 1, 0xF02C };
static unsigned short effectw23[2] = { 1, 0xF03C };
static unsigned short effectw24[2] = { 1, 0xF04C };
static unsigned short effectw25[2] = { 1, 0xF05C };
static unsigned short effectw26[2] = { 1, 0xF06C };


unsigned short* effectwrtpat[30] = {
  effectw00,
  effectw01,
  effectw02,
  effectw03,
  effectw04,
  effectw05,
  effectw06,
  effectw07,
  effectw08,
  effectw09,
  effectw10,
  effectw11,
  effectw12,
  effectw13,
  effectw14,
  effectw15,
  effectw16,
  effectw17,
  effectw17,
  effectw17,
  effectw17,
  effectw18,
  effectw19,
  effectw20,
  effectw21,
  effectw22,
  effectw23,
  effectw24,
  effectw25,
  effectw26
};


void vseffect(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[4] = {
    &vseffectinit,
    &vseffectmove,

  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void vseffectinit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = vseffectpat;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 16;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x7E0;
  p_actwk->u.obj.ko = p_actwk == &g_ram.actwk[ACTWK_PL_EFFECT] ? 0 : 1;
  vseffectmove(p_actwk);
}


static void vseffectmove(SKC_sprite_status* p_actwk) {
  void(*act_tbl[4])(SKC_sprite_status*, SKC_sprite_status*) = {
    &vseffect0move,
    &vseffect0move,
    &vseffect1move,
    &vseffect2move
  };

  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  act_tbl[p_actwk->mstno](p_actwk, p_playerwk);
}


static void vseffect0move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->patno = 0;
  patchg(p_actwk, vseffectchg);
  actionsub(p_actwk);
}


static void vseffect1move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.air_timer >= 12 && p_playerwk->r_no <= 4 && p_playerwk->u.play.spindash_flag != 0) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
    p_actwk->u.obj.cddat.right = p_playerwk->u.play.cddat.left;
    p_actwk->u.obj.cddat.down = g_ram.reverse_gravity_flag;
    if (p_actwk->mstrestart == 0) {
      p_actwk->sproffset.pr = p_playerwk->sproffset.pr;
    }
    patchg(p_actwk, vseffectchg);
    actionsub(p_actwk);
  }
  else {
    p_actwk->mstno = 0;
  }
}


static void vseffect2move(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.air_timer >= 12) {
    patchg(p_actwk, vseffectchg);
    actionsub(p_actwk);
  }
  else {
    p_actwk->mstno = 0;
  }
}


static void vseffectmove2(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void vseffectmove3(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_playerwk->mstno == 13) {
    p_actwk->r_no = 2;
    p_actwk->u.obj.timer = 0;
  }
  else {
    if (p_actwk->u.obj.timer-- == 0) {
      p_actwk->u.obj.timer = 3;
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = p_actwk->r_ptr;
        fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_playerwk->xposi));
        fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_playerwk->yposi));
        fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_playerwk->yposi) + 12);
        memset(&result.actwk_ptr->u.obj.cddat, 0, sizeof(result.actwk_ptr->u.obj.cddat));
        result.actwk_ptr->mstno = 3;
        result.actwk_ptr->r_no += 2;
        result.actwk_ptr->patbase = p_actwk->patbase;
        result.actwk_ptr->actflg = p_actwk->actflg;
        result.actwk_ptr->sprpri = PRI_1;
        result.actwk_ptr->sprhs = 4;
        result.actwk_ptr->sproffset = p_actwk->sproffset;
        result.actwk_ptr->u.obj.ko = p_actwk->u.obj.ko;
        result.actwk_ptr->sproffset.pr = p_playerwk->sproffset.pr;
      }
    }
  }
}


static signed char* vseffectchg[4] = {
  vseffectchg00,
  vseffectchg01,
  vseffectchg02,
  vseffectchg03
};


static signed char vseffectchg00[3] = { 31, 0, -1 };
static signed char vseffectchg01[4] = { 3, 0, -3, 0 };
static signed char vseffectchg02[6] = { 1, 1, 2, 3, 4, -1 };
static signed char vseffectchg03[5] = { 5, 5, 6, 7, -4 };


static SKC_sprite_pattern* vseffectpat[8] = {
  &vseffectsp00,
  &vseffectsp01,
  &vseffectsp02,
  &vseffectsp03,
  &vseffectsp04,
  &vseffectsp05,
  &vseffectsp06,
  &vseffectsp07
};


static SKC_sprite_pattern vseffectsp00 = {
  0,
  {}
};
static SKC_sprite_pattern vseffectsp01 = {
  1,
  {
    { 4, 8, 0x0000, -20 },
  }
};
static SKC_sprite_pattern vseffectsp02 = {
  1,
  {
    { 4, 8, 0x0003, -20 },
  }
};
static SKC_sprite_pattern vseffectsp03 = {
  1,
  {
    { -4, 9, 0x0006, -20 },
  }
};
static SKC_sprite_pattern vseffectsp04 = {
  1,
  {
    { -4, 9, 0x000C, -20 },
  }
};
static SKC_sprite_pattern vseffectsp05 = {
  1,
  {
    { -4, 0, 0x0012, -4 },
  }
};
static SKC_sprite_pattern vseffectsp06 = {
  1,
  {
    { -4, 0, 0x0013, -4 },
  }
};
static SKC_sprite_pattern vseffectsp07 = {
  1,
  {
    { -4, 0, 0x0014, -4 },
  }
};


void sstartrail(SKC_sprite_status* p_actwk) {
  memcpy(&g_vram[0xF380], sstar_cg, sizeof(sstar_cg));
  p_actwk->patbase = sstartrailpat;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x79C;
  p_actwk->sproffset.pr = g_ram.actwk[0].sproffset.pr;
  p_actwk->r_ptr = &sstartrailmove;
}


static void sstartrailmove(SKC_sprite_status* p_actwk) {
  if (g_ram.ssonicflag != 0) {
    if (p_actwk->mstno != 0) {
      sstartrailmovesub(p_actwk);
    }
    if (p_actwk->u.obj.actfree.sstartrail.active) {
      if (p_actwk->pattim-- == 0) {
        p_actwk->pattim = 1;
        ++p_actwk->patno;
        if (p_actwk->patno >= 6) {
          p_actwk->patno = 0;
          p_actwk->u.obj.actfree.sstartrail.active = false;
          p_actwk->u.obj.actfree.sstartrail.posi_set_disabled = true;
          return;
        }
      }
      if (!p_actwk->u.obj.actfree.sstartrail.posi_set_disabled) {
        fp16_set_integer(&p_actwk->xposi, fp16_get_integer(g_ram.actwk[0].xposi));
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(g_ram.actwk[0].yposi));
      }
      actionsub(p_actwk);
    }
    else {
      if (g_ram.actwk[0].u.play.control_bitfield == 0) {
        short mspeed = abs(g_ram.actwk[0].mspeed);
        if (mspeed >= 0x800) {
          p_actwk->patno = 0;
          p_actwk->u.obj.actfree.sstartrail.active = true;
          fp16_set_integer(&p_actwk->xposi, fp16_get_integer(g_ram.actwk[0].xposi));
          fp16_set_integer(&p_actwk->yposi, fp16_get_integer(g_ram.actwk[0].yposi));
          actionsub(p_actwk);
          return;
        }
      }
      p_actwk->u.obj.actfree.sstartrail.active = false;
      p_actwk->u.obj.actfree.sstartrail.posi_set_disabled = false;
    }
  }
  else {
    frameout(p_actwk);
  }
}


static void sstartrailmovesub(SKC_sprite_status* p_actwk) {
  p_actwk->mstno = 0;
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  unsigned short direction = 0x488;
  short xspeed, yspeed;

  for (int i = 0; i < 16; ++i) {
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr == 0) break;
    result.actwk_ptr->r_ptr = &sstar;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(g_ram.actwk[0].xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(g_ram.actwk[0].yposi));
    result.actwk_ptr->patbase = &sstarpat;
    memset(&result.actwk_ptr->sproffset, 0, sizeof(result.actwk_ptr->sproffset));
    result.actwk_ptr->sproffset.gfx = 0x79C;
    result.actwk_ptr->sproffset.pr = 1;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->actflg.onscreen = 1;
    result.actwk_ptr->sprpri = PRI_7;
    result.actwk_ptr->sprhs = 8;
    result.actwk_ptr->sprvs = 8;
    if (direction < 0x8000) {
      short sin, cos;
      sinset(direction & 0xFF, &sin, &cos);
      xspeed = sin * (1 << (direction >> 8));
      yspeed = cos * (1 << (direction >> 8));
      direction = direction & 0xFF00 | direction + 16 & 0x00FF;
      if ((direction & 0xFF) < 16) {
        direction -= 128;
        direction &= 0xFFFF;
        if (direction > 0xFF80) {
          direction = 0x288;
        }
      }
    }
    result.actwk_ptr->xspeed = xspeed;
    result.actwk_ptr->yspeed = yspeed;
    xspeed = -xspeed;
    direction = ~direction + 1 & 0xFFFF;
  }
}


static void sstar(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    ++p_actwk->patno;
    p_actwk->patno &= 3;
    speedset2(p_actwk);
    actionsub(p_actwk);
  }
}


static SKC_sprite_pattern* sstartrailpat[6] = {
  &sstartrailsp00,
  &sstartrailsp01,
  &sstartrailsp02,
  &sstartrailsp03,
  &sstartrailsp02,
  &sstartrailsp01
};


static SKC_sprite_pattern* sstarpat[4] = {
  &sstarsp00,
  &sstarsp01,
  &sstarsp00,
  &sstarsp02
};


static SKC_sprite_pattern sstartrailsp00 = {
  0,
  {}
};
static SKC_sprite_pattern sstartrailsp01 = {
  1,
  {
    { -8, 5, 0x0000, -8 },
  }
};
static SKC_sprite_pattern sstartrailsp02 = {
  4,
  {
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0804,   0 },
    {   0, 5, 0x1004, -16 },
    {   0, 5, 0x1804,   0 },
  }
};
static SKC_sprite_pattern sstartrailsp03 = {
  4,
  {
    { -24, 10, 0x0008, -24 },
    { -24, 10, 0x0808,   0 },
    {   0, 10, 0x1008, -24 },
    {   0, 10, 0x1808,   0 },
  }
};
static SKC_sprite_pattern sstartrailsp04 = {
  1,
  {
    { -4, 0, 0x0011, -4 },
  }
};
static SKC_sprite_pattern sstartrailsp05 = {
  1,
  {
    { -8, 5, 0x0012, -8 },
  }
};
static SKC_sprite_pattern sstartrailsp06 = {
  1,
  {
    { -8, 5, 0x0016, -8 },
  }
};


static SKC_sprite_pattern sstarsp00 = {
  1,
  {
    { -4, 0, 0x0011, -4 },
  }
};
static SKC_sprite_pattern sstarsp01 = {
  1,
  {
    { -8, 5, 0x0012, -8 },
  }
};
static SKC_sprite_pattern sstarsp02 = {
  1,
  {
    { -8, 5, 0x0016, -8 },
  }
};


void hstars(SKC_sprite_status* p_actwk) {
  unlze_moduled(&g_vram[0xF380], hstar_cg);
  unsigned char direction = 0;

  for (int i = 0; i < 4; ++i) {
    p_actwk[i].r_ptr = &hstar;
    p_actwk[i].direc.b.b0 = direction;
    direction = direction_sum(direction, 64);
    p_actwk[i].pattim = i + 1;
  }

  hstar(p_actwk);
}


static void hstar(SKC_sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (p_actwk->pattim == 0) {
    p_actwk->patbase = hstar_pt;
    p_actwk->actflg.relative_coordinates = 1;
    p_actwk->sprpri = PRI_1;
    p_actwk->sprhs = 24;
    p_actwk->sprvs = 24;
    memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
    p_actwk->sproffset.gfx = 0x79C;
    p_actwk->patno = 6;
    if (p_actwk != &g_ram.actwk[ACTWK_PL_MUTEKI]) {
      p_actwk->r_ptr = &hstar_move1;
    }
    else {
      p_actwk->r_ptr = &hstar_move0;
    }
    p_actwk->r_ptr(p_actwk);
  }
}


static void hstar_move0(SKC_sprite_status* p_actwk) {
  if (p_actwk->mstno != 0) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(g_ram.actwk[0].xposi));
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(g_ram.actwk[0].yposi));
    tbariasub0(p_actwk, 2);
    g_ram.ssonicdashtim = 4;
  }
  hstar_move1(p_actwk);
}


static void hstar_move1(SKC_sprite_status* p_actwk) {
  if (g_ram.ssonicflag != 0) {
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = 1;
      ++p_actwk->patno;
      if (p_actwk->patno >= 3) {
        p_actwk->patno = 0;
        p_actwk->u.obj.actfree.hstar.xoffset = 0;
        p_actwk->u.obj.actfree.hstar.yoffset = 0;
      }
    }
    unsigned char direction = p_actwk->direc.b.b0;
    p_actwk->direc.b.b0 = direction_sum(p_actwk->direc.b.b0, 240);
    short sin, cos;
    sinset(p_actwk->direc.b.b0, &sin, &cos);
    p_actwk->xspeed = sin * 8;
    p_actwk->yspeed = cos * 8;
    p_actwk->u.obj.actfree.hstar.xoffset += p_actwk->xspeed;
    p_actwk->u.obj.actfree.hstar.yoffset += p_actwk->yspeed;
    short xposi = fp8_get_integer(p_actwk->u.obj.actfree.hstar.xoffset);
    if (g_ram.actwk[0].u.play.cddat.left == 1) {
      xposi = -xposi;
    }
    xposi += fp16_get_integer(g_ram.actwk[0].xposi);
    fp16_set_integer(&p_actwk->xposi, xposi);
    short yposi = fp8_get_integer(p_actwk->u.obj.actfree.hstar.yoffset);
    yposi += fp16_get_integer(g_ram.actwk[0].yposi);
    fp16_set_integer(&p_actwk->yposi, yposi);
    p_actwk->sproffset.pr = g_ram.actwk[0].sproffset.pr;
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static SKC_sprite_pattern* hstar_pt[6] = {
  &hstar_pt00,
  &hstar_pt01,
  &hstar_pt02,
  &hstar_pt03,
  &hstar_pt04,
  &hstar_pt05
};


static SKC_sprite_pattern hstar_pt00 = {
  1,
  {
    { -8, 5, 0x0000, -8 },
  }
};
static SKC_sprite_pattern hstar_pt01 = {
  1,
  {
    { -8, 5, 0x0004, -8 },
  }
};
static SKC_sprite_pattern hstar_pt02 = {
  2,
  {
    { -16, 13, 0x0008, -16 },
    {   0, 13, 0x1008, -16 },
  }
};
static SKC_sprite_pattern hstar_pt03 = {
  1,
  {
    { -8, 5, 0x0010, -8 },
  }
};
static SKC_sprite_pattern hstar_pt04 = {
  1,
  {
    { -12, 6, 0x0014, -8 },
  }
};
static SKC_sprite_pattern hstar_pt05 = {
  1,
  {
    { -12, 10, 0x001A, -12 },
  }
};


void wspin(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = wspinpat;
  p_actwk->u.obj.actfree.baria.wrtpat_ptr = wspinwrtpat;
  p_actwk->u.obj.actfree.baria.cg_ptr = wspin_cg;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x79C;
  p_actwk->u.obj.actfree.baria.vram_offset = 0xF380;
  p_actwk->sproffset.pr = g_ram.actwk[0].sproffset.pr;
  p_actwk->mstno = 0;
  p_actwk->mstrestart = 1;
  p_actwk->u.obj.wrt.prev_patno = 255;
  p_actwk->r_ptr = &wspinmove;
  p_actwk->patno = 0;
  wspinmove(p_actwk);
}


static void wspinmove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_playerwk->u.play.powerdat.muteki == 0) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
    p_actwk->u.obj.cddat.right = p_playerwk->u.play.cddat.left;
    p_actwk->u.obj.cddat.down = g_ram.reverse_gravity_flag;
    p_actwk->sproffset.pr = p_playerwk->sproffset.pr;
    patchg(p_actwk, wspinchg);
    if (p_actwk->patno == 7 && p_playerwk->u.play.talent_status != 0) {
      p_playerwk->u.play.talent_status = 2;
    }
    if (p_actwk->patno == 0 || p_actwk->patno == 3) {
      bariawrt(p_actwk);
    }
    actionsub(p_actwk);
  }
}


void fbaria(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = fbariapat;
  p_actwk->u.obj.actfree.baria.wrtpat_ptr = fbariawrtpat;
  p_actwk->u.obj.actfree.baria.cg_ptr = fbaria_cg;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x79C;
  p_actwk->u.obj.actfree.baria.vram_offset = 0xF380;
  p_actwk->sproffset.pr = g_ram.actwk[0].sproffset.pr;
  p_actwk->mstno = 0;
  p_actwk->mstrestart = 1;
  p_actwk->u.obj.wrt.prev_patno = 255;
  p_actwk->r_ptr = &fbariamove;
  fbariamove(p_actwk);
}


static void fbariamove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_playerwk->u.play.powerdat.muteki == 0 && p_playerwk->mstno != 28) {
    if (p_playerwk->u.play.powerdat.baria != 0) {
      if (p_playerwk->u.play.cddat.underwater == 0) {
        fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
        if (p_actwk->mstno == 0) {
          p_actwk->u.obj.cddat.right = p_playerwk->u.play.cddat.left;
          p_actwk->u.obj.cddat.down = g_ram.reverse_gravity_flag;
          p_actwk->sproffset.pr = p_playerwk->sproffset.pr;
        }
        patchg(p_actwk, fbariachg);
        p_actwk->sprpri = p_actwk->patno < 15 ? PRI_1 : PRI_4;
        bariawrt(p_actwk);
        actionsub(p_actwk);
      }
      else {
        p_playerwk->u.play.powerdat.baria = 0;
        p_playerwk->u.play.powerdat.fbaria = 0;
        p_playerwk->u.play.powerdat.tbaria = 0;
        p_playerwk->u.play.powerdat.abaria = 0;
        SKC_actwkchk_result result = actwkchk();
        if (result.actwk_ptr != 0) {
          result.actwk_ptr->r_ptr = &bakuhatu2;
          fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
          fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
        }
        p_actwk->r_ptr = &wspin;
      }
    }
    else {
      p_playerwk->u.play.powerdat.fbaria = 0;
      p_playerwk->u.play.powerdat.tbaria = 0;
      p_playerwk->u.play.powerdat.abaria = 0;
      p_actwk->r_ptr = &wspin;
    }
  }
}


void tbaria(SKC_sprite_status* p_actwk) {
  memcpy(&g_vram[0xF760], tbariaspark_cg, sizeof(tbariaspark_cg));
  p_actwk->patbase = tbariapat;
  p_actwk->u.obj.actfree.baria.wrtpat_ptr = tbariawrtpat;
  p_actwk->u.obj.actfree.baria.cg_ptr = tbaria_cg;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x79C;
  p_actwk->u.obj.actfree.baria.vram_offset = 0xF380;
  p_actwk->sproffset.pr = g_ram.actwk[0].sproffset.pr;
  p_actwk->mstno = 0;
  p_actwk->mstrestart = 1;
  p_actwk->u.obj.wrt.prev_patno = 255;
  p_actwk->r_ptr = &tbariamove;
  tbariamove(p_actwk);
}


static void tbariamove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_playerwk->u.play.powerdat.muteki == 0 && p_playerwk->mstno != 28) {
    if (p_playerwk->u.play.powerdat.baria != 0) {
      if (p_playerwk->u.play.cddat.underwater == 0) {
        fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
        p_actwk->u.obj.cddat.right = p_playerwk->u.play.cddat.left;
        p_actwk->u.obj.cddat.down = g_ram.reverse_gravity_flag;
        p_actwk->sproffset.pr = p_playerwk->sproffset.pr;
        if (p_actwk->mstno != 0) {
          tbariasub(p_actwk);
          p_actwk->mstno = 0;
        }
        patchg(p_actwk, tbariachg);
        p_actwk->sprpri = p_actwk->patno < 14 ? PRI_1 : PRI_4;
        bariawrt(p_actwk);
        actionsub(p_actwk);
      }
      else {
        p_playerwk->u.play.powerdat.baria = 0;
        p_playerwk->u.play.powerdat.fbaria = 0;
        p_playerwk->u.play.powerdat.tbaria = 0;
        p_playerwk->u.play.powerdat.abaria = 0;
        if (g_ram.fadecnt != 0) {
          p_actwk->r_ptr = &wspin;
        }
        else {
          p_actwk->r_ptr = &tbariasub1;
          memcpy(g_ram.colorwk4, g_ram.colorwk3, sizeof(g_ram.colorwk4));

          for (int i = 0; i < 64; ++i) {
            g_ram.colorwk3[i] = 0xEEE;
          }

          g_ram.colorwk3[0] = 0;
          p_actwk->pattim = 3;
        }
      }
    }
    else {
      p_playerwk->u.play.powerdat.fbaria = 0;
      p_playerwk->u.play.powerdat.tbaria = 0;
      p_playerwk->u.play.powerdat.abaria = 0;
      p_actwk->r_ptr = &wspin;
    }
  }
}


static void tbariasub(SKC_sprite_status* p_actwk) {
  tbariasub0(p_actwk, 1);
}


static void tbariasub0(SKC_sprite_status* p_actwk, unsigned char mstno) {
  SKC_speed spd_tbl[4] = {
    { -0x200, -0x200 },
    {  0x200, -0x200 },
    { -0x200,  0x200 },
    {  0x200,  0x200 }
  };

  for (int i = 0; i < 4; ++i) {
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr == 0) break;
    result.actwk_ptr->r_ptr = &tbariaspark;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->sprpri = PRI_1;
    result.actwk_ptr->sprhs = 8;
    result.actwk_ptr->sprvs = 8;
    result.actwk_ptr->mstno = mstno;
    result.actwk_ptr->xspeed = spd_tbl[i].xspeed;
    result.actwk_ptr->yspeed = spd_tbl[i].yspeed;
  }
}


static void tbariaspark(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  patchg(p_actwk, tbariachg);
  if (p_actwk->r_no == 0) {
    actionsub(p_actwk);
  }
}


static void tbariasub1(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  p_actwk->r_ptr = &wspin;
  memcpy(g_ram.colorwk3, g_ram.colorwk4, sizeof(g_ram.colorwk3));
}


void abaria(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = abariapat;
  p_actwk->u.obj.actfree.baria.wrtpat_ptr = abariawrtpat;
  p_actwk->u.obj.actfree.baria.cg_ptr = abaria_cg;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x79C;
  p_actwk->u.obj.actfree.baria.vram_offset = 0xF380;
  p_actwk->sproffset.pr = g_ram.actwk[0].sproffset.pr;
  p_actwk->mstno = 0;
  p_actwk->mstrestart = 1;
  p_actwk->u.obj.wrt.prev_patno = 255;
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  plairset(p_playerwk);
  p_actwk->r_ptr = &abariamove;
  abariamove(p_actwk);
}


static void abariamove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_playerwk->u.play.powerdat.muteki == 0 && p_playerwk->mstno != 28) {
    if (p_playerwk->u.play.powerdat.baria != 0) {
      fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_playerwk->xposi));
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi));
      p_actwk->u.obj.cddat.right = p_playerwk->u.play.cddat.left;
      p_actwk->u.obj.cddat.down = g_ram.reverse_gravity_flag;
      p_actwk->sproffset.pr = p_playerwk->sproffset.pr;
      patchg(p_actwk, abariachg);
      bariawrt(p_actwk);
      actionsub(p_actwk);
    }
    else {
      p_playerwk->u.play.powerdat.fbaria = 0;
      p_playerwk->u.play.powerdat.tbaria = 0;
      p_playerwk->u.play.powerdat.abaria = 0;
      p_actwk->r_ptr = &wspin;
    }
  }
}


static void bariawrt(SKC_sprite_status* p_actwk) {
  if (p_actwk->patno == p_actwk->u.obj.wrt.prev_patno) return;

  p_actwk->u.obj.wrt.prev_patno = p_actwk->patno;
  unsigned short* p_wrtpat = p_actwk->u.obj.actfree.baria.wrtpat_ptr[p_actwk->patno];
  unsigned short cnt = *p_wrtpat++;
  unsigned short vram_adr = p_actwk->u.obj.actfree.baria.vram_offset;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = *p_wrtpat++;
    unsigned char* p_source = &p_actwk->u.obj.actfree.baria.cg_ptr[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


static signed char* wspinchg[2] = {
  wspinchg00,
  wspinchg01
};


static signed char wspinchg00[3] = { 31, 6, -1 };
static signed char wspinchg01[17] = { 0, 0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, -3, 0 };


static signed char* fbariachg[2] = {
  fbariachg00,
  fbariachg01
};


static signed char fbariachg00[20] = { 1, 0, 15, 1, 16, 2, 17, 3, 18, 4, 19, 5, 20, 6, 21, 7, 22, 8, 23, -1 };
static signed char fbariachg01[15] = { 1, 9, 10, 11, 12, 13, 14, 9, 10, 11, 12, 13, 14, -3, 0 };


static signed char* tbariachg[3] = {
  tbariachg00,
  tbariachg01,
  tbariachg02
};


static signed char tbariachg00[44] = {
   1,  0,  0,  1,  1,  2,  2,  3,  3,  4,
   4,  5,  5,  6,  6,  7,  7,  8,  8,  9,
  10, 11, 22, 22, 21, 21, 20, 20, 19, 19,
  18, 18, 17, 17, 16, 16, 15, 15, 14, 14,
  9, 10, 11, -1
};
static signed char tbariachg01[23] = {
   0, 12, 13, 23, 12, 13, 23, 12, 13, 23,
  12, 13, 23, 12, 13, 23, 12, 13, 23, 12,
  13, -4, -1
};
static signed char tbariachg02[6] = { 3, 0, 1, 2, -4, -1 };


static signed char* abariachg[3] = {
  abariachg00,
  abariachg01,
  abariachg02
};


static signed char abariachg00[56] = {
   1,  0,  9,  0,  9,  0,  9,  1, 10,  1,
  10,  1, 10,  2,  9,  2,  9,  2,  9,  3,
  10,  3, 10,  3, 10,  4,  9,  4,  9,  4,
   9,  5, 10,  5, 10,  5, 10,  6,  9,  6,
   9,  6,  9,  7, 10,  7, 10,  7, 10,  8,
   9,  8,  9,  8,  9, -1
};
static signed char abariachg01[7] = { 5, 9, 11, 11, 11, -3, 0 };
static signed char abariachg02[6] = { 5, 12, 12, 11, -3, 0 };


static SKC_sprite_pattern* fbariapat[25] = {
  &fbariasp00,
  &fbariasp01,
  &fbariasp02,
  &fbariasp03,
  &fbariasp04,
  &fbariasp05,
  &fbariasp06,
  &fbariasp07,
  &fbariasp08,
  &fbariasp09,
  &fbariasp10,
  &fbariasp11,
  &fbariasp12,
  &fbariasp13,
  &fbariasp14,
  &fbariasp15,
  &fbariasp16,
  &fbariasp17,
  &fbariasp18,
  &fbariasp19,
  &fbariasp20,
  &fbariasp21,
  &fbariasp22,
  &fbariasp23,
  &fbariasp24
};


static SKC_sprite_pattern fbariasp00 = {
  3,
  {
    {  8, 0, 0x0000, -16 },
    { 16, 8, 0x0001, -24 },
    {  8, 9, 0x0004,   0 },
  }
};
static SKC_sprite_pattern fbariasp01 = {
  3,
  {
    { 0, 4, 0x0000, -16 },
    { 8, 9, 0x0002, -24 },
    { 8, 9, 0x0008,   0 },
  }
};
static SKC_sprite_pattern fbariasp02 = {
  3,
  {
    { -8,  0, 0x0000,  -8 },
    {  0, 10, 0x0001, -24 },
    {  0, 10, 0x000A,   0 },
  }
};
static SKC_sprite_pattern fbariasp03 = {
  3,
  {
    { -16,  8, 0x0000, -16 },
    {  -8, 10, 0x0003, -24 },
    {  -8, 10, 0x000C,   0 },
  }
};
static SKC_sprite_pattern fbariasp04 = {
  4,
  {
    { -16, 9, 0x0000, -24 },
    { -16, 9, 0x0006,   0 },
    {   0, 9, 0x1000, -24 },
    {   0, 9, 0x1006,   0 },
  }
};
static SKC_sprite_pattern fbariasp05 = {
  3,
  {
    {   8,  8, 0x1800,  -8 },
    { -16, 10, 0x1803,   0 },
    { -16, 10, 0x180C, -24 },
  }
};
static SKC_sprite_pattern fbariasp06 = {
  3,
  {
    {   0,  0, 0x1800,   0 },
    { -24, 10, 0x1801,   0 },
    { -24, 10, 0x180A, -24 },
  }
};
static SKC_sprite_pattern fbariasp07 = {
  3,
  {
    {  -8, 4, 0x1800,   0 },
    { -24, 9, 0x1802,   0 },
    { -24, 9, 0x1808, -24 },
  }
};
static SKC_sprite_pattern fbariasp08 = {
  3,
  {
    { -16, 0, 0x1800,   8 },
    { -24, 8, 0x1801,   0 },
    { -24, 9, 0x1804, -24 },
  }
};
static SKC_sprite_pattern fbariasp09 = {
  3,
  {
    { -24, 7, 0x0000, 12 },
    {   8, 8, 0x0008,  4 },
    {  16, 4, 0x000B, 12 },
  }
};
static SKC_sprite_pattern fbariasp10 = {
  4,
  {
    { -24, 10, 0x0000, -20 },
    { -24, 10, 0x0009,   4 },
    {   0, 10, 0x1000, -20 },
    {   0, 10, 0x1009,   4 },
  }
};
static SKC_sprite_pattern fbariasp11 = {
  4,
  {
    { -24, 14, 0x0000, -28 },
    { -24, 10, 0x000C,   4 },
    {   0, 14, 0x1015, -28 },
    {   0, 10, 0x100C,   4 },
  }
};
static SKC_sprite_pattern fbariasp12 = {
  3,
  {
    {  -8, 7, 0x1000, 12 },
    { -16, 8, 0x1008,  4 },
    { -24, 4, 0x100B, 12 },
  }
};
static SKC_sprite_pattern fbariasp13 = {
  4,
  {
    { -24, 14, 0x0000, -28 },
    { -24, 10, 0x000C,   4 },
    {   0, 14, 0x1000, -28 },
    {   0, 10, 0x100C,   4 },
  }
};
static SKC_sprite_pattern fbariasp14 = {
  4,
  {
    { -24, 14, 0x0000, -32 },
    { -24, 14, 0x000C,   0 },
    {   0, 14, 0x1000, -32 },
    {   0, 14, 0x100C,   0 },
  }
};
static SKC_sprite_pattern fbariasp15 = {
  2,
  {
    { -24, 9, 0x0000, -24 },
    { -24, 9, 0x0006,   0 },
  }
};
static SKC_sprite_pattern fbariasp16 = {
  2,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0009,   0 },
  }
};
static SKC_sprite_pattern fbariasp17 = {
  3,
  {
    { -24, 11, 0x0000, -24 },
    { -24, 10, 0x000C,   0 },
    {   0,  0, 0x0015,   8 },
  }
};
static SKC_sprite_pattern fbariasp18 = {
  3,
  {
    { -24, 11, 0x0000, -24 },
    { -24, 11, 0x000C,   0 },
    {   8,  4, 0x0018,   8 },
  }
};
static SKC_sprite_pattern fbariasp19 = {
  4,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0009,   0 },
    {   0, 10, 0x1000, -24 },
    {   0, 10, 0x1009,   0 },
  }
};
static SKC_sprite_pattern fbariasp20 = {
  3,
  {
    {  -8, 11, 0x1800,   0 },
    {  -8, 11, 0x180C, -24 },
    { -16,  4, 0x1818, -24 },
  }
};
static SKC_sprite_pattern fbariasp21 = {
  3,
  {
    { -8, 11, 0x1800,   0 },
    {  0, 10, 0x180C, -24 },
    { -8,  0, 0x1815, -16 },
  }
};
static SKC_sprite_pattern fbariasp22 = {
  2,
  {
    { 0, 10, 0x1800, -24 },
    { 0, 10, 0x1809,   0 },
  }
};
static SKC_sprite_pattern fbariasp23 = {
  2,
  {
    { 8, 9, 0x1800,   0 },
    { 8, 9, 0x1806, -24 },
  }
};
static SKC_sprite_pattern fbariasp24 = {
  0,
  {}
};


unsigned short fbariaw00[4] = { 3, 0x0000, 0x2001, 0x5004 };
unsigned short fbariaw01[4] = { 3, 0x100A, 0x500C, 0x5012 };
unsigned short fbariaw02[4] = { 3, 0x0018, 0x8019, 0x8022 };
unsigned short fbariaw03[4] = { 3, 0x202B, 0x802E, 0x8037 };
unsigned short fbariaw04[3] = { 2, 0x5040, 0x5046 };
unsigned short fbariaw05[4] = { 3, 0x202B, 0x802E, 0x8037 };
unsigned short fbariaw06[4] = { 3, 0x0018, 0x8019, 0x8022 };
unsigned short fbariaw07[4] = { 3, 0x100A, 0x500C, 0x5012 };
unsigned short fbariaw08[4] = { 3, 0x0000, 0x2001, 0x5004 };
unsigned short fbariaw09[4] = { 3, 0x704C, 0x2054, 0x1057 };
unsigned short fbariaw10[3] = { 2, 0x8059, 0x8062 };
unsigned short fbariaw11[4] = { 3, 0xB06B, 0x8077, 0xB06B };
unsigned short fbariaw12[4] = { 3, 0x704C, 0x2054, 0x1057 };
unsigned short fbariaw13[3] = { 2, 0xB080, 0x808C };
unsigned short fbariaw14[3] = { 2, 0xB095, 0xB0A1 };
unsigned short fbariaw15[3] = { 2, 0x50AD, 0x50B3 };
unsigned short fbariaw16[3] = { 2, 0x80B9, 0x80C2 };
unsigned short fbariaw17[4] = { 3, 0xB0CB, 0x80D7, 0x00E0 };
unsigned short fbariaw18[4] = { 3, 0xB0E1, 0xB0ED, 0x10F9 };
unsigned short fbariaw19[3] = { 2, 0x80FB, 0x8104 };
unsigned short fbariaw20[4] = { 3, 0xB0E1, 0xB0ED, 0x10F9 };
unsigned short fbariaw21[4] = { 3, 0xB0CB, 0x80D7, 0x00E0 };
unsigned short fbariaw22[3] = { 2, 0x80C2, 0x80B9 };
unsigned short fbariaw23[3] = { 2, 0x50AD, 0x50B3 };
unsigned short fbariaw24[1] = { 0 };


static unsigned short* fbariawrtpat[25] = {
  fbariaw00,
  fbariaw01,
  fbariaw02,
  fbariaw03,
  fbariaw04,
  fbariaw05,
  fbariaw06,
  fbariaw07,
  fbariaw08,
  fbariaw09,
  fbariaw10,
  fbariaw11,
  fbariaw12,
  fbariaw13,
  fbariaw14,
  fbariaw15,
  fbariaw16,
  fbariaw17,
  fbariaw18,
  fbariaw19,
  fbariaw20,
  fbariaw21,
  fbariaw22,
  fbariaw23,
  fbariaw24
};


static SKC_sprite_pattern* tbariapat[24] = {
  &tbariasp00,
  &tbariasp01,
  &tbariasp02,
  &tbariasp03,
  &tbariasp04,
  &tbariasp05,
  &tbariasp06,
  &tbariasp07,
  &tbariasp08,
  &tbariasp09,
  &tbariasp10,
  &tbariasp11,
  &tbariasp12,
  &tbariasp13,
  &tbariasp00,
  &tbariasp01,
  &tbariasp02,
  &tbariasp03,
  &tbariasp04,
  &tbariasp05,
  &tbariasp06,
  &tbariasp07,
  &tbariasp08,
  &tbariasp14
};


static SKC_sprite_pattern tbariasp00 = {
  3,
  {
    { -24, 12, 0x0000, -8 },
    { -16,  7, 0x0004,  8 },
    {  16, 12, 0x000C, -8 },
  }
};
static SKC_sprite_pattern tbariasp01 = {
  2,
  {
    { -24, 10, 0x0000, 0 },
    {   0, 10, 0x0009, 0 },
  }
};
static SKC_sprite_pattern tbariasp02 = {
  3,
  {
    { -24,  8, 0x0000, -8 },
    { -16, 11, 0x0003,  0 },
    {  16,  8, 0x000F, -8 },
  }
};
static SKC_sprite_pattern tbariasp03 = {
  3,
  {
    { -24,  8, 0x0000, -8 },
    { -16, 14, 0x0003, -8 },
    {   8,  9, 0x000F, -8 },
  }
};
static SKC_sprite_pattern tbariasp04 = {
  2,
  {
    { -24, 6, 0x0000, -8 },
    {   0, 6, 0x0006, -8 },
  }
};
static SKC_sprite_pattern tbariasp05 = {
  3,
  {
    { -24,  8, 0x0800, -16 },
    { -16, 14, 0x0803, -24 },
    {   8,  9, 0x080F, -16 },
  }
};
static SKC_sprite_pattern tbariasp06 = {
  3,
  {
    { -24,  8, 0x0800, -16 },
    { -16, 11, 0x0803, -24 },
    {  16,  8, 0x080F, -16 },
  }
};
static SKC_sprite_pattern tbariasp07 = {
  2,
  {
    { -24, 10, 0x0800, -24 },
    {   0, 10, 0x0809, -24 },
  }
};
static SKC_sprite_pattern tbariasp08 = {
  3,
  {
    { -24, 12, 0x0800, -24 },
    { -16,  7, 0x0804, -24 },
    {  16, 12, 0x080C, -24 },
  }
};
static SKC_sprite_pattern tbariasp09 = {
  4,
  {
    { -24, 10, 0x0000, -24 },
    {   0, 10, 0x0009, -24 },
    { -24, 10, 0x1809,   0 },
    {   0, 10, 0x1800,   0 },
  }
};
static SKC_sprite_pattern tbariasp10 = {
  4,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0009,   0 },
    {   0, 10, 0x1809, -24 },
    {   0, 10, 0x1800,   0 },
  }
};
static SKC_sprite_pattern tbariasp11 = {
  4,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0800,   0 },
    {   0, 10, 0x1000, -24 },
    {   0, 10, 0x1800,   0 },
  }
};
static SKC_sprite_pattern tbariasp12 = {
  1,
  {
    { -4, 0, 0x001F, -4 },
  }
};
static SKC_sprite_pattern tbariasp13 = {
  1,
  {
    { -8, 5, 0x0020, -8 },
  }
};
static SKC_sprite_pattern tbariasp14 = {
  0,
  {}
};


static unsigned short tbariaw00[4] = { 3, 0x3000, 0x7004, 0x300C };
static unsigned short tbariaw01[3] = { 2, 0x8010, 0x8019 };
static unsigned short tbariaw02[4] = { 3, 0x2022, 0xB025, 0x2031 };
static unsigned short tbariaw03[4] = { 3, 0x2034, 0xB037, 0x5043 };
static unsigned short tbariaw04[3] = { 2, 0x5049, 0x504F };
static unsigned short tbariaw05[4] = { 3, 0x2034, 0xB037, 0x5043 };
static unsigned short tbariaw06[4] = { 3, 0x2022, 0xB025, 0x2031 };
static unsigned short tbariaw07[3] = { 2, 0x8010, 0x8019 };
static unsigned short tbariaw08[4] = { 3, 0x3000, 0x7004, 0x300C };
static unsigned short tbariaw09[3] = { 2, 0x8055, 0x805E };
static unsigned short tbariaw10[3] = { 2, 0x8067, 0x8070 };
static unsigned short tbariaw11[2] = { 1, 0x8079 };
static unsigned short tbariaw12[2] = { 1, 0x0082 };
static unsigned short tbariaw13[2] = { 1, 0x3083 };


static unsigned short* tbariawrtpat[23] = {
  tbariaw00,
  tbariaw01,
  tbariaw02,
  tbariaw03,
  tbariaw04,
  tbariaw05,
  tbariaw06,
  tbariaw07,
  tbariaw08,
  tbariaw09,
  tbariaw10,
  tbariaw11,
  tbariaw12,
  tbariaw13,
  tbariaw00,
  tbariaw01,
  tbariaw02,
  tbariaw03,
  tbariaw04,
  tbariaw05,
  tbariaw06,
  tbariaw07,
  tbariaw08
};


static SKC_sprite_pattern* abariapat[13] = {
  &abariasp00,
  &abariasp01,
  &abariasp02,
  &abariasp03,
  &abariasp04,
  &abariasp05,
  &abariasp06,
  &abariasp07,
  &abariasp08,
  &abariasp09,
  &abariasp10,
  &abariasp11,
  &abariasp12
};


static SKC_sprite_pattern abariasp00 = {
  1,
  {
    { -24, 12, 0x0000, -16 },
  }
};
static SKC_sprite_pattern abariasp01 = {
  2,
  {
    { -24, 9, 0x0000, -24 },
    { -24, 9, 0x0800,   0 },
  }
};
static SKC_sprite_pattern abariasp02 = {
  2,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0800,   0 },
  }
};
static SKC_sprite_pattern abariasp03 = {
  2,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0800,   0 },
  }
};
static SKC_sprite_pattern abariasp04 = {
  2,
  {
    { -16, 11, 0x0000, -24 },
    { -16, 11, 0x0800,   0 },
  }
};
static SKC_sprite_pattern abariasp05 = {
  2,
  {
    { 0, 10, 0x1000, -24 },
    { 0, 10, 0x1800,   0 },
  }
};
static SKC_sprite_pattern abariasp06 = {
  2,
  {
    { 0, 10, 0x1000, -24 },
    { 0, 10, 0x1800,   0 },
  }
};
static SKC_sprite_pattern abariasp07 = {
  2,
  {
    { 8, 9, 0x1000, -24 },
    { 8, 9, 0x1800,   0 },
  }
};
static SKC_sprite_pattern abariasp08 = {
  2,
  {
    { 16, 4, 0x1000, -16 },
    { 16, 4, 0x1800,   0 },
  }
};
static SKC_sprite_pattern abariasp09 = {
  4,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0009,   0 },
    {   0, 10, 0x1000, -24 },
    {   0, 10, 0x1800,   0 },
  }
};
static SKC_sprite_pattern abariasp10 = {
  4,
  {
    { -24, 10, 0x0000, -24 },
    { -24, 10, 0x0009,   0 },
    {   0, 10, 0x1000, -24 },
    {   0, 10, 0x1800,   0 },
  }
};
static SKC_sprite_pattern abariasp11 = {
  4,
  {
    { -20, 13, 0x0000, -28 },
    { -20,  9, 0x0008,   4 },
    {  -4, 14, 0x000E, -28 },
    {  -4, 10, 0x080E,   4 },
  }
};
static SKC_sprite_pattern abariasp12 = {
  3,
  {
    { -16, 15, 0x0000, -36 },
    { -16,  3, 0x0010,  -4 },
    { -16, 15, 0x0014,   4 },
  }
};


static unsigned short abariaw00[2] = { 1, 0x3000 };
static unsigned short abariaw01[2] = { 1, 0x5004 };
static unsigned short abariaw02[2] = { 1, 0x800A };
static unsigned short abariaw03[2] = { 1, 0x8013 };
static unsigned short abariaw04[2] = { 1, 0xB01C };
static unsigned short abariaw05[2] = { 1, 0x8013 };
static unsigned short abariaw06[2] = { 1, 0x800A };
static unsigned short abariaw07[2] = { 1, 0x5004 };
static unsigned short abariaw08[2] = { 1, 0x1000 };
static unsigned short abariaw09[3] = { 2, 0x8028, 0x8031 };
static unsigned short abariaw10[3] = { 2, 0x803A, 0x8043 };
static unsigned short abariaw11[4] = { 3, 0x704C, 0x5054, 0xB05A };
static unsigned short abariaw12[4] = { 3, 0xF066, 0x3076, 0xF07A };


static unsigned short* abariawrtpat[13] = {
  abariaw00,
  abariaw01,
  abariaw02,
  abariaw03,
  abariaw04,
  abariaw05,
  abariaw06,
  abariaw07,
  abariaw08,
  abariaw09,
  abariaw10,
  abariaw11,
  abariaw12
};


static SKC_sprite_pattern* wspinpat[8] = {
  &wspin00,
  &wspin01,
  &wspin02,
  &wspin03,
  &wspin04,
  &wspin05,
  &wspin06,
  &wspin06
};


static SKC_sprite_pattern wspin00 = {
  3,
  {
    { -24, 8, 0x0000, -16 },
    { -16, 4, 0x0003,  -8 },
    {  -8, 0, 0x0005,   0 },
  }
};
static SKC_sprite_pattern wspin01 = {
  3,
  {
    { -16, 4, 0x0006, 8 },
    {  -8, 8, 0x0008, 0 },
    {   0, 4, 0x000B, 0 },
  }
};
static SKC_sprite_pattern wspin02 = {
  2,
  {
    { 0, 9, 0x000D, 0 },
    { 16, 12, 0x0013, -8 },
  }
};
static SKC_sprite_pattern wspin03 = {
  3,
  {
    { -16, 12, 0x0000, -24 },
    {  -8,  8, 0x0004, -24 },
    {   0,  6, 0x0007, -24 },
  }
};
static SKC_sprite_pattern wspin04 = {
  3,
  {
    { -24,  4, 0x000D, -16 },
    { -24, 11, 0x000F,   0 },
    {   8,  4, 0x001B,   8 },
  }
};
static SKC_sprite_pattern wspin05 = {
  3,
  {
    { -16,  4, 0x181B, -24 },
    {  -8, 11, 0x180F, -24 },
    {  16,  4, 0x180D,   0 },
  }
};
static SKC_sprite_pattern wspin06 = {
  0,
  {}
};


static unsigned short wspinw00[3] = { 0x2, 0xF000, 0x6010 };
static unsigned short wspinw01[3] = { 0x2, 0xF017, 0xC027 };


static unsigned short* wspinwrtpat[8] = {
  wspinw00,
  wspinw00,
  wspinw00,
  wspinw01,
  wspinw01,
  wspinw01,
  wspinw01,
  wspinw01
};


void sflickies(SKC_sprite_status* p_actwk) {
  unlze_moduled(&g_vram[0xD000], sflicky_cg);

  for (int i = 0; i < 4; ++i) {
    p_actwk[i].r_ptr = &sflicky;
    p_actwk[i].u.obj.actfree.sflicky.direction = i * 64;
  }

  sflicky(p_actwk);
}


static void sflicky(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = sflicky_pt;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x680;
  p_actwk->sproffset.pr = 1;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(g_ram.actwk[0].xposi));
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 192);
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(g_ram.actwk[0].yposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 192);
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->r_ptr = &sflicky_move0;
}


static void sflicky_move0(SKC_sprite_status* p_actwk) {
  if (g_ram.smilesflag == 0) {
    fp16_set_integer(&g_ram.actwk[1].xposi, 0);
    fp16_set_integer(&g_ram.actwk[1].yposi, 0);
    g_ram.actwk[1].mstno = 0;
    if (p_actwk->u.obj.actfree.sflicky.attacking) {
      SKC_sprite_status* p_emywk = &g_ram.actwk[p_actwk->u.obj.ko];
      p_emywk->u.obj.userflag &= 0x00FF;
    }
    p_actwk->u.obj.actfree.sflicky.attacking = false;
    p_actwk->u.obj.timer = 120;
    p_actwk->r_ptr = &sflicky_away;
  }
  short xposi, yposi;
  sflicky_move0_sub(p_actwk, &xposi, &yposi);
  sflicky_move1(p_actwk, xposi, yposi);
}


static void sflicky_move1(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  sflicky_move1_sub(p_actwk, xposi, yposi);
  p_actwk->u.obj.actfree.sflicky.direction = direction_sum(p_actwk->u.obj.actfree.sflicky.direction, 2);
  if (p_actwk->xspeed != 0) {
    p_actwk->actflg.hflip = p_actwk->xspeed < 0;
  }
  p_actwk->actflg.vflip = g_ram.reverse_gravity_flag;
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 1;
    ++p_actwk->patno;
    p_actwk->patno &= 1;
  }
  actionsub(p_actwk);
}


static void sflicky_away(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(g_ram.actwk[0].xposi) - 192;
  short yposi = fp16_get_integer(g_ram.actwk[0].yposi) - 192;
  sflicky_move1(p_actwk, xposi, yposi);
}


static void sflicky_move0_sub(SKC_sprite_status* p_actwk, short* p_xposi, short* p_yposi) {
  if (!p_actwk->u.obj.actfree.sflicky.attacking) {
    if (p_actwk->u.obj.timer != 0) {
      --p_actwk->u.obj.timer;
    }
    else {
      sflicky_scan(p_actwk);
    }
    if (!p_actwk->u.obj.actfree.sflicky.attacking) {
      short sin, cos;
      sinset(p_actwk->u.obj.actfree.sflicky.direction, &sin, &cos);
      *p_xposi = fp16_get_integer(g_ram.actwk[0].xposi) + sin / 8;
      *p_yposi = fp16_get_integer(g_ram.actwk[0].yposi) + cos / 16 - 32;
      if (g_ram.reverse_gravity_flag != 0) {
        *p_yposi += 64;
      }
    }
  }
  if (p_actwk->u.obj.actfree.sflicky.attacking) {
    SKC_sprite_status* p_emywk = &g_ram.actwk[p_actwk->u.obj.ko];
    *p_xposi = fp16_get_integer(p_emywk->xposi);
    *p_yposi = fp16_get_integer(p_emywk->yposi);
    bool stop = p_emywk->actflg.onscreen == 0;
    if (!stop) {
      short xdistance = fp16_get_integer(p_actwk->xposi) - *p_xposi + 12;
      if ((unsigned short)xdistance < 24) {
        short ydistance = fp16_get_integer(p_actwk->yposi) - *p_yposi + 12;
        if ((unsigned short)ydistance < 24) {
          sflicky_hit(p_actwk, p_emywk);
          stop = true;
        }
      }
    }
    if (stop) {
      p_emywk->u.obj.userflag &= 0x00FF;
      p_actwk->u.obj.actfree.sflicky.attacking = false;
      p_actwk->u.obj.timer = 120;
    }
  }
}


static void sflicky_hit(SKC_sprite_status* p_actwk, SKC_sprite_status* p_emywk) {
  if (p_emywk->colino == 0) return;

  switch (p_emywk->colino & 0xC0) {
    case 0:
      if (p_emywk->colicnt != 0) {
        p_emywk->pattimm = p_emywk->colino;
        p_emywk->mspeed = 0xB04A;
        p_emywk->colino = 0;
        --p_emywk->colicnt;
        if (p_emywk->colicnt == 0) {
          p_emywk->u.obj.cddat.die = 1;
        }
      }
      else {
        emydieset(p_emywk);
        return;
      }
      break;
    case 192:
      p_emywk->colicnt |= 2;
      break;
  }

  fp16_set_integer(&g_ram.actwk[1].xposi, p_actwk->xposi);
  fp16_set_integer(&g_ram.actwk[1].yposi, p_actwk->yposi);
  g_ram.actwk[1].mstno = 2;
}


static void sflicky_move1_sub(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  short xaccel = 0x20;
  if (xposi < fp16_get_integer(p_actwk->xposi)) {
    xaccel = -xaccel;
    if (p_actwk->xspeed >= 0) {
      xaccel *= 4;
    }
  }
  else {
    if (p_actwk->xspeed < 0) {
      xaccel *= 4;
    }
  }
  p_actwk->xspeed += xaccel;
  short ydistance = (short)((unsigned short)yposi & g_ram.scrc_v) - fp16_get_integer(p_actwk->yposi);
  short yaccel = 0x20;
  if (ydistance < 0) {
    if (ydistance > -0x500) {
      if (p_actwk->yspeed > -0x1000) {
        yaccel = -yaccel;
        if (p_actwk->yspeed >= 0) {
          yaccel *= 4;
        }
      }
      else {
        if (p_actwk->yspeed < 0) {
          yaccel *= 4;
        }
      }
    }
    else {
      if (p_actwk->yspeed < 0x1000) {
        if (p_actwk->yspeed < 0) {
          yaccel *= 4;
        }
      }
      else {
        yaccel = -yaccel;
        if (p_actwk->yspeed >= 0) {
          yaccel *= 4;
        }
      }
    }
  }
  else {
    if (ydistance < 0x500) {
      if (p_actwk->yspeed < 0x1000) {
        if (p_actwk->yspeed < 0) {
          yaccel *= 4;
        }
      }
      else {
        yaccel = -yaccel;
        if (p_actwk->yspeed >= 0) {
          yaccel *= 4;
        }
      }
    }
    else {
      if (p_actwk->yspeed > -0x1000) {
        yaccel = -yaccel;
        if (p_actwk->yspeed >= 0) {
          yaccel *= 4;
        }
      }
      else {
        if (p_actwk->yspeed < 0) {
          yaccel *= 4;
        }
      }
    }
  }
  p_actwk->yspeed += yaccel;
  speedset2(p_actwk);
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - g_ram.frame_offset_x);
  short yposi_wk = (unsigned short)fp16_get_integer(p_actwk->yposi) & g_ram.scrc_v;
  fp16_set_integer(&p_actwk->yposi, yposi_wk);
}


static void sflicky_scan(SKC_sprite_status* p_actwk) {
  if (g_ram.colibuffer[0] == 0) return;

  ++g_ram.colibuffer_id;
  if (g_ram.colibuffer[0] <= g_ram.colibuffer_id) {
    g_ram.colibuffer_id = 0;
  }

  for (int i = g_ram.colibuffer_id; i < g_ram.colibuffer[0]; ++i) {
    unsigned char actid = g_ram.colibuffer[i + 1];
    SKC_sprite_status* p_emywk = &g_ram.actwk[actid];
    if (p_emywk->colino != 0) {
      sflicky_emy_chk(p_actwk, p_emywk);
      if (p_actwk->u.obj.actfree.sflicky.attacking) break;
    }
  }
}


static void sflicky_emy_chk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_emywk) {
  if (p_emywk->actflg.onscreen == 0) return;
  if (p_emywk->u.obj.userflag & 0xFF00) return;

  switch (p_emywk->colino & 0xC0) {
    case 0:
    case 192:
      p_emywk->u.obj.userflag = 0xFF00 | p_emywk->u.obj.userflag & 0x00FF;
      p_actwk->u.obj.ko = p_emywk - g_ram.actwk;
      p_actwk->u.obj.actfree.sflicky.attacking = true;
      break;
  }
}


static SKC_sprite_pattern* sflicky_pt[3] = {
  &sflicky_pt00,
  &sflicky_pt01,
  &sflicky_pt02
};


static SKC_sprite_pattern sflicky_pt00 = {
  1,
  {
    { -8, 5, 0x0006, -8 },
  }
};
static SKC_sprite_pattern sflicky_pt01 = {
  1,
  {
    { -8, 5, 0x000A, -8 },
  }
};
static SKC_sprite_pattern sflicky_pt02 = {
  1,
  {
    { -12, 6, 0x0000, -8 },
  }
};


void imagetrail(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = g_ram.play_type == PLAY_TYPE_KNUCKLES ? knuckles_pt : splaypat;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x680;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_ptr = &imagetrail_move;
  imagetrail_move(p_actwk);
}


static void imagetrail_move(SKC_sprite_status* p_actwk) {
  if (g_ram.ssonicflag == 0) {
    frameout(p_actwk);
  }
  else {
    unsigned short offset = !(g_ram.gametimer & 1) ? 12 : 20;
    unsigned short index = g_ram.plposiwkadr - offset;
    fp16_set_integer(&p_actwk->xposi, g_ram.playposiwk[index].x);
    fp16_set_integer(&p_actwk->yposi, g_ram.playposiwk[index].y);
    p_actwk->sproffset.pl = g_ram.playrecwk[index].sprdat.pl;
    p_actwk->sproffset.pr = g_ram.playrecwk[index].sprdat.pr;
    p_actwk->patno = g_ram.actwk[0].patno;
    p_actwk->actflg = g_ram.actwk[0].actflg;
    p_actwk->sprpri = g_ram.actwk[0].sprpri;
    actionsub(p_actwk);
  }
}
