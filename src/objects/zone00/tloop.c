#include "tloop.h"
#include <stdbool.h>
#include "../../types/actwkchkresult.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../actset.h"
#include "../../etc.h"
static void tloopinit(SKC_sprite_status* p_actwk);
static void tloopmove(SKC_sprite_status* p_actwk);
static void tloopmovesub(SKC_sprite_status* p_actwk);
static void tloopmovesub__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, long* p_plspeed, bool* p_plride);
static void tloopmovesub__rideon(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, long* p_plspeed, bool* p_plride);
static void tloopmovesub__jumpdown(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride);
static void tloopmovesub__jump1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride);
static void tloopmovesub__jump2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, long* p_plspeed, bool* p_plride);
static unsigned char tloopdirtbl[55];

extern sonic3_ram g_ram;


void tloop(SKC_sprite_status* p_actwk) {
  tloopinit(p_actwk);
}


static void tloopinit(SKC_sprite_status* p_actwk) {
  p_actwk->sprhs = 208;
  p_actwk->r_ptr = &tloopmove;
  tloopmove(p_actwk);
}


static void tloopmove(SKC_sprite_status* p_actwk) {
  tloopmovesub(p_actwk);
  if (p_actwk->u.obj.cddat.plride == 0
      && p_actwk->u.obj.cddat.pl2ride == 0
      && p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      g_ram.scralim_left = 0x1300;
      g_ram.scralim_right = 0x4000;
    }
    else {
      if (g_ram.scralim_left != 0x1300) {
        if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) >= 0x2D00) {
          g_ram.scralim_left = 0x1300;
        }
        else {
          g_ram.scralim_left -= 4;
        }
      }
      if (g_ram.scralim_right != 0x4000) {
        if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) < 0x2D00) {
          g_ram.scralim_right = 0x4000;
        }
        else {
          g_ram.scralim_right += 4;
        }
      }
    }
  }
  frameoutchk3(p_actwk);
}


static void tloopmovesub(SKC_sprite_status* p_actwk) {
  bool plride = p_actwk->u.obj.cddat.plride;
  tloopmovesub__sub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.tloop.plspeed, &plride);
  p_actwk->u.obj.cddat.plride = plride;
  plride = p_actwk->u.obj.cddat.pl2ride;
  tloopmovesub__sub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.tloop.pl2speed, &plride);
  p_actwk->u.obj.cddat.pl2ride = plride;
}


static void tloopmovesub__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, long* p_plspeed, bool* p_plride) {
  if (*p_plride) {
    tloopmovesub__rideon(p_actwk, p_playerwk, p_plspeed, p_plride);
  }
  else if (p_playerwk->u.play.cddat.jump == 0) {
    short xposi = fp16_get_integer(p_playerwk->xposi) + 16 - fp16_get_integer(p_actwk->xposi);
    if (xposi >= 0 && xposi < 64) {
      short yposi = fp16_get_integer(p_playerwk->yposi - fp16_get_integer(p_actwk->yposi));
      if (yposi >= -90 && yposi <= 160) {
        if (p_playerwk->xspeed >= 0x600 && p_playerwk->u.play.control_bitfield == 0) {
          RideObject_SetRide(p_actwk, p_playerwk, p_plride);
          *p_plspeed = 0;
          SET_BIT(p_playerwk->u.play.control_bitfield, 6);
          SET_BIT(p_playerwk->u.play.control_bitfield, 1);
          p_playerwk->mstno = 0;
          if (p_playerwk == &g_ram.actwk[0]) {
            SKC_actwkchk_result result = actwkchk2(p_actwk);
            if (result.actwk_ptr != 0) {
              result.actwk_ptr->r_ptr = &Obj_AIZ1TreeRevealControl;
            }
            g_ram.scralim_left = 0x2C60;
            g_ram.scralim_right = 0x2C60;
            p_actwk->u.obj.timer = 60;
          }
        }
      }
    }
  }
}


static void tloopmovesub__rideon(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, long* p_plspeed, bool* p_plride) {
  short mspeed = p_playerwk->mspeed;
  if (mspeed < 0) {
    mspeed = -mspeed;
  }
  if (mspeed >= 0x600) {
    if (p_playerwk->u.play.cddat.jump == 1) {
      tloopmovesub__jumpdown(p_actwk, p_playerwk, p_plride);
    }
    else {
      short yposi = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->xposi) + 144;
      if (yposi >= 0 && yposi <= 304) {
        tloopmovesub__jump2(p_actwk, p_playerwk, p_plspeed, p_plride);
      }
      else {
        tloopmovesub__jump1(p_actwk, p_playerwk, p_plride);
      }
    }
  }
  else {
    if (fp16_get_integer(*p_plspeed) < 0x400) {
      tloopmovesub__jump2(p_actwk, p_playerwk, p_plspeed, p_plride);
    }
    tloopmovesub__jump1(p_actwk, p_playerwk, p_plride);
  }
}


static void tloopmovesub__jumpdown(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride) {
  if (fp16_get_integer(p_playerwk->xposi) < 0x2C99) {
    fp16_set_integer(&p_playerwk->xposi, 0x2C99);
    p_playerwk->xspeed = 0x400;
  }
  if (fp16_get_integer(p_playerwk->xposi) >= 0x2D66) {
    fp16_set_integer(&p_playerwk->xposi, 0x2D66);
    p_playerwk->xspeed = -0x400;
  }
  tloopmovesub__jump1(p_actwk, p_playerwk, p_plride);
}


static void tloopmovesub__jump1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride) {
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ball = 0;
  p_playerwk->sprvsize = 19;
  p_playerwk->sprhsize = 9;
  p_playerwk->mstno = 0;
  p_playerwk->mstrestart = 1;
  p_playerwk->u.play.cddat.ride = 0;
  *p_plride = false;
  p_playerwk->u.play.flip_rev_cnt = 0;
  p_playerwk->u.play.flip_rev_frame_cnt = 4;
  CLEAR_BIT(p_playerwk->u.play.control_bitfield, 6);
  CLEAR_BIT(p_playerwk->u.play.control_bitfield, 1);
  p_playerwk->xspeed /= 2;
  p_playerwk->yspeed /= 2;
}


static void tloopmovesub__jump2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, long* p_plspeed, bool* p_plride) {
  if (p_playerwk->u.play.cddat.ride == 0) return;

  *p_plspeed += p_playerwk->mspeed * 0x100;
  if (*p_plspeed < 0) {
    tloopmovesub__jump1(p_actwk, p_playerwk, p_plride);
  }
  else {
    g_ram.scralim_left = 0x1300;
    g_ram.scralim_right = 0x4000;
    short sin, cos;
    sinset(fp16_get_integer(*p_plspeed) / 2, &sin, &cos);
    long wk = sin * 0x7000;
    short xposi_save = fp16_get_integer(p_playerwk->xposi);
    short xposi = fp16_get_integer(wk) + fp16_get_integer(p_actwk->xposi);
    fp16_set_integer(&p_playerwk->xposi, xposi);
    p_playerwk->xspeed = (xposi - xposi_save) * 0x100;
    short yposi_save = fp16_get_integer(p_playerwk->yposi);
    short yposi = -(fp16_get_integer(*p_plspeed) / 4) + 144 + fp16_get_integer(p_actwk->yposi);
    fp16_set_integer(&p_playerwk->yposi, yposi);
    p_playerwk->yspeed = (yposi - yposi_save) * 0x100;
    short dir = fp16_get_integer(*p_plspeed) / 2 / 11;
    p_playerwk->patno = tloopdirtbl[dir];
    Perform_Player_DPLC(p_playerwk, p_playerwk->patno);
  }
}


static unsigned char tloopdirtbl[55] = {
  105, 106, 107, 119, 108, 108, 109, 109, 110, 110,
  111, 111, 112, 112, 113, 113, 114, 114, 115, 115,
  116, 116, 117, 117, 118, 118, 119, 119, 108, 108,
  109, 109, 110, 110, 111, 111, 112, 112, 113, 113,
  114, 114, 115, 115, 116, 116, 117, 117, 107, 107,
  106, 106, 105, 105, 144
};
