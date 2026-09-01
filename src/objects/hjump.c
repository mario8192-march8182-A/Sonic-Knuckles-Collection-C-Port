#include "hjump.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../action.h"
static void hjumpinit(SKC_sprite_status* p_actwk);
static void hjumpmove(SKC_sprite_status* p_actwk);
static void hjumpmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);

extern sonic3_ram g_ram;


void hjump(SKC_sprite_status* p_actwk) {
  hjumpinit(p_actwk);
}


static void hjumpinit(SKC_sprite_status* p_actwk) {
  hjumpmove(p_actwk);
}


static void hjumpmove(SKC_sprite_status* p_actwk) {
  hjumpmove__sub(p_actwk, &g_ram.actwk[0]);
  hjumpmove__sub(p_actwk, &g_ram.actwk[1]);
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.sc1ahposit;
  if ((unsigned short)chunk_xposi > 640) {
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


static void hjumpmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.jump == 1) return;

  short distance = fp16_get_integer(p_playerwk->xposi) + 16 - fp16_get_integer(p_actwk->xposi);
  if (distance >= 0 && distance < 32) {
    distance = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi);
    if (distance >= -20 && distance <= 32 && p_playerwk->u.play.control_bitfield == 0) {
      bool jump = false;
      if (p_actwk->u.obj.cddat.right == 0) {
        if (p_playerwk->xspeed >= 0x400) {
          p_playerwk->xspeed += 0x400;
          jump = true;
        }
      }
      else {
        if (p_playerwk->xspeed <= -0x400) {
          p_playerwk->xspeed -= 0x400;
          jump = true;
        }
      }
      if (jump) {
        p_playerwk->yspeed = -0x700;
        p_playerwk->u.play.cddat.jump = 1;
        p_playerwk->r_no = 2;
        p_playerwk->mspeed = 1;
        p_playerwk->direc.b.b0 = 1;
        p_playerwk->mstno = 0;
        p_playerwk->u.play.flip_rev_cnt = 0;
        p_playerwk->u.play.flip_rev_frame_cnt = 4;
        p_playerwk->u.play.flip_mst.type = 5;
      }
    }
  }
}
