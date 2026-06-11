#include "awa.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/direction.h"
#include "../utils/fp16.h"
#include "../action.h"
#include "../actset.h"
#include "../etc.h"
#include "../sound.h"
#include "player.h"
#include "playsub.h"
static void awainit(SKC_sprite_status* p_actwk);
static void awamove(SKC_sprite_status* p_actwk);
static void awamove2(SKC_sprite_status* p_actwk);
static void awamove3(SKC_sprite_status* p_actwk);
static void awamove4(SKC_sprite_status* p_actwk);
static void awamaster(SKC_sprite_status* p_actwk);
static void awafoutchk(SKC_sprite_status* p_actwk);
static unsigned char awatbl[18];
static void awacoli(SKC_sprite_status* p_actwk);
static void awacoli__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static signed char* awachg[9];
static signed char awachg0[5];
static signed char awachg1[6];
static signed char awachg2[7];
static signed char awachg3[4];
static signed char awachg4[2];
static signed char awachg6[4];
static signed char awachg8[5];
static SKC_sprite_pattern awasp00;
static SKC_sprite_pattern awasp01;
static SKC_sprite_pattern awasp02;
static SKC_sprite_pattern awasp03;
static SKC_sprite_pattern awasp04;
static SKC_sprite_pattern awasp05;
static SKC_sprite_pattern awasp06;
static SKC_sprite_pattern awasp07;
static SKC_sprite_pattern awasp08;
static SKC_sprite_pattern awasp09;
static SKC_sprite_pattern awasp19;
static SKC_sprite_pattern awasp20;
static SKC_sprite_pattern awasp21;
static SKC_sprite_pattern awasp22;
static SKC_sprite_pattern awasp092;

extern sonic3_ram g_ram;


void awa(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler awa_move_tbl[6] = {
    &awainit,
    &awamove,
    &awamove2,
    &awamove3,
    &awamove4,
    &awamaster
  };

  awa_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void awainit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = awapat;
  p_actwk->sproffset = 0x045C;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->actflg.onscreen = 1;
  p_actwk->sprhs = 16;
  p_actwk->sprpri = PRI_1;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_actwk->r_no += 8;
    p_actwk->u.obj.actfree.awa.large_bubble_timer = p_actwk->u.obj.userflag & 0x7F;
    p_actwk->u.obj.actfree.awa.large_bubble_timer_init = p_actwk->u.obj.userflag & 0x7F;
    p_actwk->mstno = 8;
    awamaster(p_actwk);
  }
  else {
    p_actwk->mstno = p_actwk->u.obj.userflag;
    p_actwk->u.obj.actfree.awa.xposi_init = fp16_get_integer(p_actwk->xposi);
    p_actwk->yspeed = -0x88;
    p_actwk->direc.b.b0 = random() & 0xFF;
    awamove(p_actwk);
  }
}


static void awamove(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, awachg);
  if (p_actwk->patno != 6) {
    awamove2(p_actwk);
  }
  else {
    p_actwk->u.obj.actfree.awa.large_bubble = true;
  }
}


static void awamove2(SKC_sprite_status* p_actwk) {
  if ((unsigned short)g_ram.waterposi >= (unsigned short)fp16_get_integer(p_actwk->yposi)) {
    p_actwk->r_no = 6;
    p_actwk->mstno += 4;
    awamove3(p_actwk);
  }
  else {
    short xposi = awasintbl[p_actwk->direc.b.b0 & 0x7F] + p_actwk->u.obj.actfree.awa.xposi_init;
    fp16_set_integer(&p_actwk->xposi, xposi);
    p_actwk->direc.b.b0 = direction_sum(p_actwk->direc.b.b0, 1);
    if (p_actwk->u.obj.actfree.awa.large_bubble) {
      awacoli(p_actwk);
      if (p_actwk->r_no == 6) {
        awamove3(p_actwk);
        return;
      }
    }
    speedset2(p_actwk);
    if (p_actwk->actflg.onscreen == 1) {
      actionsub(p_actwk);
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void awamove3(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, awachg);
  if (p_actwk->actflg.onscreen == 1) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void awamove4(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void awamaster(SKC_sprite_status* p_actwk) {
  bool make_bubble = false;
  if (p_actwk->u.obj.actfree.awa.bitfield == 0) {
    if ((unsigned short)g_ram.waterposi >= (unsigned short)fp16_get_integer(p_actwk->yposi)
        || p_actwk->actflg.onscreen == 0) {
      awafoutchk(p_actwk);
      return;
    }
    else if (p_actwk->u.obj.actfree.awa.small_bubble_timer-- == 0) {
      p_actwk->u.obj.actfree.awa.bitfield = 1;
      unsigned short value;

      do {
        value = random();
      }
      while ((value & 7) >= 6);

      p_actwk->u.obj.actfree.awa.pending_small_bubble_cnt = value & 7;
      p_actwk->u.obj.actfree.awa.tbl_ptr = &awatbl[(value & 0xC) / 4];
      if (p_actwk->u.obj.actfree.awa.large_bubble_timer-- == 0) {
        p_actwk->u.obj.actfree.awa.large_bubble_timer = p_actwk->u.obj.actfree.awa.large_bubble_timer_init;
        SET_BIT(p_actwk->u.obj.actfree.awa.bitfield, 7);
      }
      make_bubble = true;
    }
  }
  else if (p_actwk->u.obj.actfree.awa.small_bubble_timer-- == 0) {
    make_bubble = true;
  }
  if (make_bubble) {
    p_actwk->u.obj.actfree.awa.small_bubble_timer = random() & 0x1F;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = p_actwk->r_ptr;
      fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
      short xoffset = (short)(random() & 0xF) - 8;
      fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
      fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
      unsigned char* p_tbl = p_actwk->u.obj.actfree.awa.tbl_ptr;
      result.actwk_ptr->u.obj.userflag = p_tbl[p_actwk->u.obj.actfree.awa.pending_small_bubble_cnt];
      if (BIT_IS_SET(p_actwk->u.obj.actfree.awa.bitfield, 7)) {
        if (!(random() & 3)) {
          if (!BIT_IS_SET(p_actwk->u.obj.actfree.awa.bitfield, 6)) {
            SET_BIT(p_actwk->u.obj.actfree.awa.bitfield, 6);
            result.actwk_ptr->u.obj.userflag = 2;
          }
        }
        else if (p_actwk->u.obj.actfree.awa.pending_small_bubble_cnt == 0) {
          if (!BIT_IS_SET(p_actwk->u.obj.actfree.awa.bitfield, 6)) {
            SET_BIT(p_actwk->u.obj.actfree.awa.bitfield, 6);
            result.actwk_ptr->u.obj.userflag = 2;
          }
        }
      }
    }
    if (p_actwk->u.obj.actfree.awa.pending_small_bubble_cnt-- == 0) {
      p_actwk->u.obj.actfree.awa.small_bubble_timer += (random() & 0x7F) + 128;
      p_actwk->u.obj.actfree.awa.bitfield = 0;
    }
  }
  patchg(p_actwk, awachg);
}


static void awafoutchk(SKC_sprite_status* p_actwk) {
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi <= 640) {
    if ((unsigned short)g_ram.waterposi < (unsigned short)fp16_get_integer(p_actwk->yposi)) {
      actionsub(p_actwk);
    }
  }
  else {
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


static unsigned char awatbl[18] = { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0 };


static void awacoli(SKC_sprite_status* p_actwk) {
  awacoli__sub(p_actwk, &g_ram.actwk[0]);
  awacoli__sub(p_actwk, &g_ram.actwk[1]);
}


static void awacoli__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) return;
  if (fp16_get_integer(p_actwk->xposi) - 16 >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) return;
  if (fp16_get_integer(p_actwk->xposi) + 16 < (unsigned short)fp16_get_integer(p_playerwk->xposi)) return;
  if (fp16_get_integer(p_actwk->yposi) >= (unsigned short)fp16_get_integer(p_playerwk->yposi)) return;
  if (fp16_get_integer(p_actwk->yposi) + 16 < (unsigned short)fp16_get_integer(p_playerwk->yposi)) return;
  if (p_playerwk->u.play.powerdat.abaria == 1) return;

  plairset(p_playerwk);
  soundset(56);
  p_playerwk->xspeed = 0;
  p_playerwk->yspeed = 0;
  p_playerwk->mspeed = 0;
  p_playerwk->mstno = 21;
  p_playerwk->u.play.hlock_timer = 35;
  p_playerwk->u.play.jump_flag = 0;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.cddat.ballj = 0;
  if (p_playerwk->u.play.cddat.ball == 1) {
    if (p_playerwk->r_ptr == &play00) {
      p_playerwk->u.play.cddat.ball = 0;
      p_playerwk->sprvsize = 19;
      p_playerwk->sprhsize = 9;
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 5);
    }
    else {
      p_playerwk->sprvsize = 15;
      p_playerwk->sprhsize = 9;
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 1);
    }
  }
  if (p_actwk->r_no != 6) {
    p_actwk->r_no = 6;
    p_actwk->mstno += 4;
  }
}


static signed char* awachg[9] = {
  awachg0,
  awachg1,
  awachg2,
  awachg3,
  awachg4,
  awachg4,
  awachg6,
  awachg6,
  awachg8
};


static signed char awachg0[5] = { 14, 0, 1, 2, -4 };
static signed char awachg1[6] = { 14, 1, 2, 3, 4, -4 };
static signed char awachg2[7] = { 14, 2, 3, 4, 5, 6, -4 };
static signed char awachg3[4] = { 2, 5, 6, -4 };
static signed char awachg4[2] = { 4, -4 };
static signed char awachg6[4] = { 4, 7, 8, -4 };
static signed char awachg8[5] = { 15, 19, 20, 21, -1 };


SKC_sprite_pattern* awapat[23] = {
  &awasp00,
  &awasp01,
  &awasp02,
  &awasp03,
  &awasp04,
  &awasp05,
  &awasp06,
  &awasp07,
  &awasp08,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp09,
  &awasp19,
  &awasp20,
  &awasp21,
  &awasp22
};


SKC_sprite_pattern* awapat2[23] = {
  &awasp00,
  &awasp01,
  &awasp02,
  &awasp03,
  &awasp04,
  &awasp05,
  &awasp06,
  &awasp07,
  &awasp08,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp092,
  &awasp19,
  &awasp20,
  &awasp21,
  &awasp22
};


static SKC_sprite_pattern awasp00 = {
  1,
  {
    { -4, 0, 0x0000, -4 },
  }
};
static SKC_sprite_pattern awasp01 = {
  1,
  {
    { -4, 0, 0x0001, -4 },
  }
};
static SKC_sprite_pattern awasp02 = {
  1,
  {
    { -4, 0, 0x0002, -4 },
  }
};
static SKC_sprite_pattern awasp03 = {
  1,
  {
    { -8, 5, 0x0003, -8 },
  }
};
static SKC_sprite_pattern awasp04 = {
  1,
  {
    { -8, 5, 0x0007, -8 },
  }
};
static SKC_sprite_pattern awasp05 = {
  1,
  {
    { -12, 10, 0x000B, -12 },
  }
};
static SKC_sprite_pattern awasp06 = {
  1,
  {
    { -16, 15, 0x0014, -16 },
  }
};
static SKC_sprite_pattern awasp07 = {
  4,
  {
    { -16, 5, 0x0024, -16 },
    { -16, 5, 0x0824,   0 },
    {   0, 5, 0x1024, -16 },
    {   0, 5, 0x1824,   0 },
  }
};
static SKC_sprite_pattern awasp08 = {
  4,
  {
    { -16, 5, 0x0028, -16 },
    { -16, 5, 0x0828,   0 },
    {   0, 5, 0x1028, -16 },
    {   0, 5, 0x1828,   0 },
  }
};
static SKC_sprite_pattern awasp09 = {
  1,
  {
    { -12, 6, 0x0384, -8 },
  }
};
static SKC_sprite_pattern awasp19 = {
  1,
  {
    { -8, 5, 0x002C, -8 },
  }
};
static SKC_sprite_pattern awasp20 = {
  1,
  {
    { -8, 5, 0x0030, -8 },
  }
};
static SKC_sprite_pattern awasp21 = {
  1,
  {
    { -8, 5, 0x0034, -8 },
  }
};
static SKC_sprite_pattern awasp22 = {
  0,
  {}
};
static SKC_sprite_pattern awasp092 = {
  1,
  {
    { -12, 6, 0x0394, -8 },
  }
};
