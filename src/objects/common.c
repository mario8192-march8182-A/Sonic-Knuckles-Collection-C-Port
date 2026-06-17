#include "common.h"
#include <stdbool.h>
#include "../types/point.h"
#include "../types/size.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/swdata.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../action.h"
#include "../actset.h"
#include "../coli.h"
#include "../hitchk.h"
#include "../sound.h"
#include "colichg.h"
#include "friend.h"
#include "toge.h"
static void bakuhatuinit(SKC_sprite_status* p_actwk);
static void bakuhatuinit2(SKC_sprite_status* p_actwk);
static void bakuhatuinit3(SKC_sprite_status* p_actwk);
static void bakuhatumove(SKC_sprite_status* p_actwk);
static void bakuhatumove2(SKC_sprite_status* p_actwk);
static void bakuhatumove3(SKC_sprite_status* p_actwk);
static void bakuhatumove32(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern bakuhatusp00;
static SKC_sprite_pattern bakuhatusp01;
static SKC_sprite_pattern bakuhatusp02;
static SKC_sprite_pattern bakuhatusp03;
static SKC_sprite_pattern bakuhatusp04;
static void miki00init(SKC_sprite_status* p_actwk);
static void miki00move(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern miki00sp00;
static void joint00init(SKC_sprite_status* p_actwk);
static void joint00move(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern joint00sp00;
static void rollcinit(SKC_sprite_status* p_actwk);
static void rollcmove(SKC_sprite_status* p_actwk);
static void rollcmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char* pldir);
static void ballchange(SKC_sprite_status* p_playerwk);
static void rollcmove2(SKC_sprite_status* p_actwk);
static void rollcmove2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char* pldir);
static void scopecmove(SKC_sprite_status* p_actwk);
static void frameout_(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern* scopecpatr[3];
static SKC_sprite_pattern scopecsp0r;
static SKC_sprite_pattern scopecsp0;
static SKC_sprite_pattern scopecsp1;
static SKC_sprite_pattern scopecsp2;
static void scoliinit(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern scolisp0;
static SKC_sprite_pattern scolisp1;
static SKC_sprite_pattern scolisp2;
static void scoliinit(SKC_sprite_status* p_actwk);
static void scolimove(SKC_sprite_status* p_actwk);
static void scolimove2(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern scolisp0;
static SKC_sprite_pattern scolisp1;
static SKC_sprite_pattern scolisp2;
static void barinit(SKC_sprite_status* p_actwk);
static void barmove(SKC_sprite_status* p_actwk);
static void barmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, bool* p_plholding, unsigned char* p_plnograb_timer);
static void barbreak(SKC_sprite_status* p_actwk);
static void barmove2(SKC_sprite_status* p_actwk);
static void barmoveh(SKC_sprite_status* p_actwk);
static void barmoveh__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, bool* p_plholding, unsigned char* p_plnograb_timer);
static void barbreak2(SKC_sprite_status* p_actwk);
static unsigned char bar_timertbl[24];
static SKC_point bar_positbl[16];
static SKC_point bar_positbl2[16];
static void breakgosubh(SKC_sprite_status* p_actwk, unsigned char part_cnt, SKC_point positbl[16], unsigned char* p_timertbl);
static SKC_sprite_pattern barsp00;
static SKC_sprite_pattern barsp01;
static SKC_sprite_pattern barsp02;
static SKC_sprite_pattern barsp03;
static SKC_sprite_pattern barsp04;
static SKC_sprite_pattern barsp05;
static SKC_sprite_pattern barsp06;
static SKC_sprite_pattern barsp07;
static void waterinit(SKC_sprite_status* p_actwk);
static void watermove(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern* waterpat[7];
static SKC_sprite_pattern watersp0;
static SKC_sprite_pattern watersp1;
static SKC_sprite_pattern watersp2;
static SKC_sprite_pattern watersp3;
static SKC_sprite_pattern watersp4;
static SKC_sprite_pattern watersp5;
static void blockinit(SKC_sprite_status* p_actwk);
static void blockmove(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern blocksp00;
static SKC_sprite_pattern blocksp01;
static SKC_sprite_pattern blocksp02;
static SKC_sprite_pattern blocksp03;
static void itaicoliinit(SKC_sprite_status* p_actwk);
static void itaicolimove(SKC_sprite_status* p_actwk);
static void itaicolimoveh(SKC_sprite_status* p_actwk);
static void itaicolimovev(SKC_sprite_status* p_actwk);
static void itaicolisub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void killcoliinit(SKC_sprite_status* p_actwk);
static void killcolimove(SKC_sprite_status* p_actwk);
static void killcolimoveh(SKC_sprite_status* p_actwk);
static void killcolimovev(SKC_sprite_status* p_actwk);
static void killcolisub(SKC_sprite_status* p_playerwk);

extern sonic3_ram g_ram;


void bakuhatu(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler bakuhatu_move_tbl[4] = {
    &bakuhatuinit,
    &bakuhatuinit2,
    &bakuhatumove,
    &bakuhatuinit3
  };

  bakuhatu_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void bakuhatuinit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &friend;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
    result.actwk_ptr->u.obj.actfree.friend.points = p_actwk->u.obj.actfree.bakuhatu.points;
  }
  bakuhatuinit2(p_actwk);
}


static void bakuhatuinit2(SKC_sprite_status* p_actwk) {
  soundset(61);
  p_actwk->r_no += 2;
  bakuhatuinit3(p_actwk);
}


static void bakuhatuinit3(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = bakuhatupat;
  p_actwk->sproffset = (p_actwk->sproffset & 0x8000) | 0x05A0;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->colino = 0;
  p_actwk->sprhs = 12;
  p_actwk->sprvs = 12;
  p_actwk->pattim = 3;
  p_actwk->patno = 0;
  p_actwk->r_ptr = &bakuhatumove;
  bakuhatumove(p_actwk);
}


static void bakuhatumove(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim == 7;
    ++p_actwk->patno;
    if (p_actwk->patno == 5) {
      frameout(p_actwk);
      return;
    }
  }
  actionsub(p_actwk);
}


void bakuhatu2(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = bakuhatupat;
  p_actwk->sproffset = 0x05A0;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 12;
  p_actwk->sprvs = 12;
  p_actwk->pattim = 3;
  p_actwk->patno = 1;
  p_actwk->r_ptr = &bakuhatumove2;
  bakuhatumove2(p_actwk);
}


static void bakuhatumove2(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 3;
    ++p_actwk->patno;
    if (p_actwk->patno == 5) {
      frameout(p_actwk);
      return;
    }
  }
  actionsub(p_actwk);
}


void bakuhatu3(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = bakuhatupat;
  p_actwk->sproffset = 0x85A0;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 12;
  p_actwk->sprvs = 12;
  p_actwk->patno = 0;
  p_actwk->r_ptr = &bakuhatumove3;
  bakuhatumove3(p_actwk);
}


static void bakuhatumove3(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  p_actwk->pattim = 3;
  p_actwk->r_ptr = &bakuhatumove32;
  bakuhatumove32(p_actwk);
}


static void bakuhatumove32(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 7;
    ++p_actwk->patno;
    if (p_actwk->patno == 5) {
      frameout(p_actwk);
      return;
    }
  }
  actionsub(p_actwk);
}


SKC_sprite_pattern* bakuhatupat[5] = {
  &bakuhatusp00,
  &bakuhatusp01,
  &bakuhatusp02,
  &bakuhatusp03,
  &bakuhatusp04
};


static SKC_sprite_pattern bakuhatusp00 = {
  1,
  {
    { -8, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern bakuhatusp01 = {
  1,
  {
    { -16, 15, 0x0004, -16 }
  }
};
static SKC_sprite_pattern bakuhatusp02 = {
  1,
  {
    { -16, 15, 0x0014, -16 }
  }
};
static SKC_sprite_pattern bakuhatusp03 = {
  1,
  {
    { -16, 15, 0x0024, -16 }
  }
};
static SKC_sprite_pattern bakuhatusp04 = {
  1,
  {
    { -16, 15, 0x0034, -16 }
  }
};


void miki00(SKC_sprite_status* p_actwk) {
  miki00init(p_actwk);
}


static void miki00init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = miki00pat;
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 8;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sproffset = 0x4001;
  p_actwk->r_ptr = &miki00move;
  miki00move(p_actwk);
}


static void miki00move(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


SKC_sprite_pattern* miki00pat[1] = {
  &miki00sp00
};


static SKC_sprite_pattern miki00sp00 = {
  3,
  {
    { -24, 5, 0x0038, -8 },
    {  -8, 5, 0x0038, -8 },
    {   8, 5, 0x0038, -8 }
  }
};


void joint00(SKC_sprite_status* p_actwk) {
  joint00init(p_actwk);
}


static void joint00init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = joint00pat;
  p_actwk->sprpri = PRI_7;
  p_actwk->sprhs = 32;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sproffset = 0x4324;
  p_actwk->r_ptr = &joint00move;
  joint00move(p_actwk);
}


static void joint00move(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


SKC_sprite_pattern* joint00pat[1] = {
  &joint00sp00
};


static SKC_sprite_pattern joint00sp00 = {
  3,
  {
    { -12, 12, 0x0000, -32 },
    {  -4,  4, 0x0004,  -8 },
    { -12, 10, 0x0006,   8 }
  }
};


void rollc(SKC_sprite_status* p_actwk) {
  rollcinit(p_actwk);
}


static void rollcinit(SKC_sprite_status* p_actwk) {
  unsigned short tbl[4] = {
    32, 64, 128, 256
  };

  p_actwk->patbase = colichgpat;
  p_actwk->sproffset = 0x06BC;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 128;
  p_actwk->sprvs = 128;
  p_actwk->sprpri = PRI_5;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 2)) {
    p_actwk->patno = p_actwk->u.obj.userflag & 7;
    p_actwk->u.obj.actfree.rollc.offset = tbl[p_actwk->u.obj.userflag & 3];
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(g_ram.actwk[0].yposi)) {
      p_actwk->u.obj.actfree.rollc.pldir = 1;
    }
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(g_ram.actwk[1].yposi)) {
      p_actwk->u.obj.actfree.rollc.pl2dir = 1;
    }
    p_actwk->r_ptr = &rollcmove2;
    rollcmove2(p_actwk);
  }
  else {
    p_actwk->patno = p_actwk->u.obj.userflag & 3;
    p_actwk->u.obj.actfree.rollc.offset = tbl[p_actwk->u.obj.userflag & 3];
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(g_ram.actwk[0].yposi)) {
      p_actwk->u.obj.actfree.rollc.pldir = 1;
    }
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < (unsigned short)fp16_get_integer(g_ram.actwk[1].yposi)) {
      p_actwk->u.obj.actfree.rollc.pl2dir = 1;
    }
    p_actwk->r_ptr = &rollcmove;
    rollcmove(p_actwk);
  }
}


static void rollcmove(SKC_sprite_status* p_actwk) {
  if (g_ram.editmode != 0) {
    frameoutchk(p_actwk);
  }
  else {
    rollcmove__sub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.rollc.pldir);
    if (g_ram.foxcpu_rno != 4) {
      rollcmove__sub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.rollc.pl2dir);
    }
    frameoutchk3(p_actwk);
  }
}


static void rollcmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char* pldir) {
  short down_yposi = (unsigned short)fp16_get_integer(p_actwk->yposi) - p_actwk->u.obj.actfree.rollc.offset;
  short up_yposi = (unsigned short)fp16_get_integer(p_actwk->yposi) + p_actwk->u.obj.actfree.rollc.offset;
  if (*pldir == 0) { // rightchk
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) <= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      *pldir = 1;
      if ((unsigned short)fp16_get_integer(p_playerwk->yposi) >= (unsigned short)down_yposi
          && (unsigned short)fp16_get_integer(p_playerwk->yposi) < (unsigned short)up_yposi
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 5) || p_playerwk->u.play.cddat.jump == 0)) {
        if (p_actwk->actflg.hflip == 0) {
          if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
            p_playerwk->mspeed = 0x580;
            p_playerwk->u.play.spindash_flag = BIT_IS_SET(p_actwk->u.obj.userflag, 7) ? 1 : 0x81;
          }
          ballchange(p_playerwk);
        }
        else if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
          p_playerwk->u.play.spindash_flag = 0;
        }
      }
    }
  }
  else { // leftchk
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) > (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      *pldir = 0;
      if ((unsigned short)fp16_get_integer(p_actwk->yposi) >= (unsigned short)down_yposi
          && (unsigned short)fp16_get_integer(p_playerwk->yposi) < (unsigned short)up_yposi
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 5) || p_playerwk->u.play.cddat.jump == 0)) {
        if (p_actwk->actflg.hflip == 1) {
          if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
            p_playerwk->mspeed = -0x580;
            p_playerwk->u.play.spindash_flag = BIT_IS_SET(p_actwk->u.obj.userflag, 7) ? 1 : 0x81;
          }
          ballchange(p_playerwk);
        }
        else if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
          p_playerwk->u.play.spindash_flag = 0;
        }
      }
    }
  }
}


static void ballchange(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.ball == 1) return;

  p_playerwk->u.play.cddat.ball = 1;
  p_playerwk->sprvsize = 14;
  p_playerwk->sprhsize = 14;
  p_playerwk->mstno = 2;
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 5);
  soundset(60);
}


static void rollcmove2(SKC_sprite_status* p_actwk) {
  if (g_ram.editmode != 0) {
    frameoutchk(p_actwk);
  }
  else {
    rollcmove2__sub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.rollc.pldir);
    if (g_ram.foxcpu_rno != 4) {
      rollcmove2__sub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.rollc.pl2dir);
    }
    frameoutchk3(p_actwk);
  }
}


static void rollcmove2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char* pldir) {
  short left_xposi = (unsigned short)fp16_get_integer(p_actwk->xposi) - p_actwk->u.obj.actfree.rollc.offset;
  short right_xposi = (unsigned short)fp16_get_integer(p_actwk->xposi) + p_actwk->u.obj.actfree.rollc.offset;
  if (*pldir == 0) { // downchk
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) <= (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
      *pldir = 1;
      if ((unsigned short)fp16_get_integer(p_playerwk->xposi) >= (unsigned short)left_xposi
          && (unsigned short)fp16_get_integer(p_playerwk->xposi) < right_xposi
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 5) || p_playerwk->u.play.cddat.jump == 0)) {
        if (p_actwk->actflg.hflip == 0) {
          if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
            p_playerwk->u.play.spindash_flag = BIT_IS_SET(p_actwk->u.obj.userflag, 7) ? 1 : 0x81;
            if (BIT_IS_SET(p_actwk->u.obj.userflag, 6)) {
              p_playerwk->u.play.cddat.jump = 0;
              p_playerwk->direc.b.b0 = 64;
              p_playerwk->mspeed = p_playerwk->yspeed;
              p_playerwk->xspeed = 0;
            }
          }
          ballchange(p_playerwk);
        }
        else if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
          p_playerwk->u.play.spindash_flag = 0;
        }
      }
    }
  }
  else { // upchk
    if ((unsigned short)fp16_get_integer(p_playerwk->yposi) > (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
      *pldir = 0;
      if ((unsigned short)fp16_get_integer(p_playerwk->xposi) >= (unsigned short)left_xposi
          && (unsigned short)fp16_get_integer(p_playerwk->xposi) < right_xposi
          && (!BIT_IS_SET(p_actwk->u.obj.userflag, 5) || p_playerwk->u.play.cddat.jump == 0)) {
        if (p_actwk->actflg.hflip == 1) {
          if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
            p_playerwk->u.play.spindash_flag = BIT_IS_SET(p_actwk->u.obj.userflag, 7) ? 1 : 0x81;
            if (BIT_IS_SET(p_actwk->u.obj.userflag, 6)) {
              p_playerwk->u.play.cddat.jump = 0;
              p_playerwk->direc.b.b0 = 64;
            }
          }
          ballchange(p_playerwk);
        }
        else if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)) {
          p_playerwk->u.play.spindash_flag = 0;
        }
      }
    }
  }
}


void scopec(SKC_sprite_status* p_actwk) {
  unsigned char scopecinittbl[5] = {
    0x96, 0x94, 0x95, 0x90
  };

  p_actwk->colino = scopecinittbl[p_actwk->u.obj.userflag];
  p_actwk->patbase = g_ram.editmode == 0 ? scopecpatr : scopecpat;
  p_actwk->sproffset = 0x86BC;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->actflg.onscreen = 1;
  p_actwk->sprhs = 128;
  p_actwk->sprvs = 128;
  p_actwk->sprpri = PRI_4;
  p_actwk->patno = p_actwk->u.obj.userflag;
  p_actwk->r_ptr = &scopecmove;
  scopecmove(p_actwk);
}


static void scopecmove(SKC_sprite_status* p_actwk) {
  if (g_ram.vs_flag == 0) {
    short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
    if ((unsigned short)chunk_xposi > 640) {
      frameout_(p_actwk);
      return;
    }
  }
  if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void frameout_(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.flagwork_index != 0) {
    CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index], 7);
  }
  frameout(p_actwk);
}


static SKC_sprite_pattern* scopecpatr[3] = {
  &scopecsp0r,
  &scopecsp0r,
  &scopecsp0r
};


static SKC_sprite_pattern scopecsp0r = {
  0,
  {}
};


SKC_sprite_pattern* scopecpat[3] = {
  &scopecsp0,
  &scopecsp1,
  &scopecsp2
};


static SKC_sprite_pattern scopecsp0 = {
  4,
  {
    { -32, 5, 0x0034, -32 },
    { -32, 5, 0x0034,  16 },
    {  16, 5, 0x0034, -32 },
    {  16, 5, 0x0034,  16 }
  }
};
static SKC_sprite_pattern scopecsp1 = {
  4,
  {
    { -32, 5, 0x0034, -64 },
    { -32, 5, 0x0034,  48 },
    {  16, 5, 0x0034, -64 },
    {  16, 5, 0x0034,  48 }
  }
};
static SKC_sprite_pattern scopecsp2 = {
  4,
  {
    { -32, 5, 0x0034, -128 },
    { -32, 5, 0x0034,  112 },
    {  16, 5, 0x0034, -128 },
    {  16, 5, 0x0034,  112 }
  }
};


void scoli(SKC_sprite_status* p_actwk) {
  scoliinit(p_actwk);
}


static void scoliinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = scolipat;
  p_actwk->sproffset = 0x86BC;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->actflg.onscreen = 1;
  p_actwk->sprhs = ((p_actwk->u.obj.userflag & 0xF0) + 16) / 2;
  p_actwk->sprvs = ((p_actwk->u.obj.userflag & 0x0F) + 1) * 8;
  p_actwk->r_ptr = g_ram.vs_flag == 0 ? &scolimove2 : &scolimove;
  p_actwk->r_ptr(p_actwk);
}


static void scolimove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk_skip_onscreen(p_actwk, data);
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi > 640) {
    frameout_(p_actwk);
  }
  else if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void scolimove2(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk_skip_onscreen(p_actwk, data);
}


SKC_sprite_pattern* scolipat[3] = {
  &scolisp0,
  &scolisp1,
  &scolisp2
};


static SKC_sprite_pattern scolisp0 = {
  4,
  {
    { -16, 5, 0x001C, -16 },
    { -16, 5, 0x001C,   0 },
    {   0, 5, 0x001C, -16 },
    {   0, 5, 0x001C,   0 }
  }
};
static SKC_sprite_pattern scolisp1 = {
  4,
  {
    { -32, 5, 0x001C, -64 },
    { -32, 5, 0x001C,  48 },
    {  16, 5, 0x001C, -64 },
    {  16, 5, 0x001C,  48 }
  }
};
static SKC_sprite_pattern scolisp2 = {
  4,
  {
    { -32, 5, 0x001C, -128 },
    { -32, 5, 0x001C,  112 },
    {  16, 5, 0x001C, -128 },
    {  16, 5, 0x001C,  112 }
  }
};


void bar(SKC_sprite_status* p_actwk) {
  barinit(p_actwk);
}


static void barinit(SKC_sprite_status* p_actwk) {
  struct {
    signed char end1_offset;
    signed char end2_offset;
    unsigned char size;
    unsigned char patno;
  }
  bartbl[3] = {
    { 20,  40, 32, 0 },
    { 36,  72, 48, 1 },
    { 52, 104, 64, 2 }
  };

  p_actwk->patbase = barpat;
  p_actwk->sproffset = 0x43CA;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->u.obj.timer = (p_actwk->u.obj.userflag & 0x0F) * 60;
  unsigned char type = (p_actwk->u.obj.userflag & 0x30) >> 4;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_actwk->u.obj.actfree.bar.end1_offset = bartbl[type].end1_offset;
    p_actwk->u.obj.actfree.bar.end2_offset = bartbl[type].end2_offset;
    p_actwk->sprhs = bartbl[type].size;
    p_actwk->sprvs = 4;
    p_actwk->patno = bartbl[type].patno + 4;
    p_actwk->r_ptr = &barmoveh;
  }
  else {
    p_actwk->u.obj.actfree.bar.end1_offset = bartbl[type].end1_offset;
    p_actwk->u.obj.actfree.bar.end2_offset = bartbl[type].end2_offset;
    p_actwk->sprhs = 4;
    p_actwk->sprvs = bartbl[type].size;
    p_actwk->patno = bartbl[type].patno;
    p_actwk->r_ptr = &barmove;
  }
  p_actwk->r_ptr(p_actwk);
}


static void barmove(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0 && p_actwk->u.obj.actfree.bar.plholding) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      barbreak(p_actwk);
    }
  }
  else {
    barmove__sub(p_actwk, &g_ram.actwk[0], g_ram.swdata1, &p_actwk->u.obj.actfree.bar.plholding, &p_actwk->u.obj.actfree.bar.plnograb_timer);
    barmove__sub(p_actwk, &g_ram.actwk[1], g_ram.swdata2, &p_actwk->u.obj.actfree.bar.pl2holding, &p_actwk->u.obj.actfree.bar.pl2nograb_timer);
    if (p_actwk->u.obj.actfree.bar.breakable) {
      barbreak(p_actwk);
    }
    else {
      frameoutchk(p_actwk);
    }
  }
}


static void barmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, bool* p_plholding, unsigned char* p_plnograb_timer) {
  if (*p_plholding) {
    short yposi = fp16_get_integer(p_actwk->yposi) - p_actwk->u.obj.actfree.bar.end1_offset;
    if (swdata.down.u == 1) {
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 1);
      if ((unsigned short)yposi >= (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
        fp16_set_integer(&p_playerwk->yposi, yposi);
      }
    }
    yposi += p_actwk->u.obj.actfree.bar.end2_offset;
    if (swdata.down.d == 1) {
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
      if ((unsigned short)yposi < (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
        fp16_set_integer(&p_playerwk->yposi, yposi);
      }
    }
    if (are_any_trg_buttons_used(swdata.pressed)) {
      *p_plholding = false;
      *p_plnograb_timer = 60;
      CLEAR_BIT(p_playerwk->u.play.control_bitfield, 0);
      if (!BIT_IS_SET(p_actwk->u.obj.userflag, 6)) {
        p_actwk->u.obj.actfree.bar.breakable = true;
      }
    }
  }
  else if (*p_plnograb_timer != 0) {
    --*p_plnograb_timer;
  }
  else {
    short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvs;
    if ((unsigned short)fp16_get_integer(p_playerwk->yposi) >= (unsigned short)yposi
        && (unsigned short)fp16_get_integer(p_playerwk->yposi) < (unsigned short)yposi + p_actwk->sprvs * 2) {
      short xposi = fp16_get_integer(p_actwk->xposi) + 20;
      if ((unsigned short)xposi < (unsigned short)fp16_get_integer(p_playerwk->xposi)
          && (unsigned short)xposi + 16 >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
        if (p_playerwk->r_no < 4 && p_playerwk->u.play.control_bitfield == 0) {
          yposi = fp16_get_integer(p_actwk->yposi) - p_actwk->u.obj.actfree.bar.end1_offset;
          if ((unsigned short)yposi >= (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
            fp16_set_integer(&p_playerwk->yposi, yposi);
          }
          yposi += p_actwk->u.obj.actfree.bar.end2_offset;
          if ((unsigned short)yposi < (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
            fp16_set_integer(&p_playerwk->yposi, yposi);
          }
          p_playerwk->xspeed = 0;
          p_playerwk->yspeed = 0;
          fp16_set_integer(&p_playerwk->xposi, xposi);
          p_playerwk->u.play.cddat.left = 0;
          p_playerwk->mstno = 17;
          p_playerwk->u.play.control_bitfield = 1;
          *p_plholding = true;
        }
      }
    }
  }
}


static void barbreak(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.bar.plholding) {
    CLEAR_BIT(g_ram.actwk[0].u.play.control_bitfield, 0);
  }
  if (p_actwk->u.obj.actfree.bar.pl2holding) {
    CLEAR_BIT(g_ram.actwk[0].u.play.control_bitfield, 0);
  }
  p_actwk->u.obj.timer = 0;
  p_actwk->u.obj.actfree.bar.plholding = false;
  p_actwk->u.obj.actfree.bar.pl2holding = false;
  p_actwk->r_ptr = &barmove2;
  p_actwk->patno = 3;
  p_actwk->xspeed = 0x400;
  p_actwk->yspeed = 0;
  breakgosubh(p_actwk, p_actwk->sprvs / 4, bar_positbl, bar_timertbl);
  barmove2(p_actwk);
}


static void barmove2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
  }
  else {
    speedset2(p_actwk);
    p_actwk->yspeed += 8;
  }
  if (p_actwk->actflg.onscreen == 0) {
    frameout_(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void barmoveh(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0 && p_actwk->u.obj.actfree.bar.plholding) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      barbreak2(p_actwk);
    }
  }
  else {
    barmoveh__sub(p_actwk, &g_ram.actwk[0], g_ram.swdata1, &p_actwk->u.obj.actfree.bar.plholding, &p_actwk->u.obj.actfree.bar.plnograb_timer);
    barmoveh__sub(p_actwk, &g_ram.actwk[1], g_ram.swdata2, &p_actwk->u.obj.actfree.bar.pl2holding, &p_actwk->u.obj.actfree.bar.pl2nograb_timer);
    if (p_actwk->u.obj.actfree.bar.breakable) {
      barbreak(p_actwk);
    }
    else {
      frameoutchk(p_actwk);
    }
  }
}


static void barmoveh__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_swdata swdata, bool* p_plholding, unsigned char* p_plnograb_timer) {
  if (*p_plholding) {
    short xposi = fp16_get_integer(p_actwk->yposi) - p_actwk->u.obj.actfree.bar.end1_offset;
    if (swdata.down.l == 1) {
      fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 1);
      if ((unsigned short)xposi >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
        fp16_set_integer(&p_playerwk->xposi, xposi);
      }
    }
    xposi += p_actwk->u.obj.actfree.bar.end2_offset;
    if (swdata.down.r == 1) {
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 1);
      if ((unsigned short)xposi < (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
        fp16_set_integer(&p_playerwk->xposi, xposi);
      }
    }
    if (are_any_trg_buttons_used(swdata.pressed)) {
      *p_plholding = false;
      *p_plnograb_timer = 60;
      CLEAR_BIT(p_playerwk->u.play.control_bitfield, 0);
      if (!BIT_IS_SET(p_actwk->u.obj.userflag, 6)) {
        p_actwk->u.obj.actfree.bar.breakable = true;
      }
    }
  }
  else if (*p_plnograb_timer != 0) {
    --*p_plnograb_timer;
  }
  else {
    short xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprhs;
    if ((unsigned short)fp16_get_integer(p_playerwk->xposi) >= (unsigned short)xposi
        && (unsigned short)fp16_get_integer(p_playerwk->xposi) < (unsigned short)xposi + p_actwk->sprhs * 2) {
      short yposi = fp16_get_integer(p_actwk->yposi) - 20;
      if ((unsigned short)yposi < (unsigned short)fp16_get_integer(p_playerwk->yposi)
          && (unsigned short)yposi + 16 >= (unsigned short)fp16_get_integer(p_playerwk->yposi)) {
        if (p_playerwk->r_no < 4 && p_playerwk->u.play.control_bitfield == 0) {
          xposi = fp16_get_integer(p_actwk->xposi) - p_actwk->u.obj.actfree.bar.end1_offset;
          if ((unsigned short)xposi >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
            fp16_set_integer(&p_playerwk->xposi, xposi);
          }
          xposi += p_actwk->u.obj.actfree.bar.end2_offset;
          if ((unsigned short)xposi < (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
            fp16_set_integer(&p_playerwk->xposi, xposi);
          }
          p_playerwk->xspeed = 0;
          p_playerwk->yspeed = 0;
          fp16_set_integer(&p_playerwk->yposi, yposi);
          p_playerwk->mstno = 20;
          p_playerwk->u.play.control_bitfield = 1;
          *p_plholding = true;
        }
      }
    }
  }
}


static void barbreak2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.bar.plholding) {
    CLEAR_BIT(g_ram.actwk[0].u.play.control_bitfield, 0);
  }
  if (p_actwk->u.obj.actfree.bar.pl2holding) {
    CLEAR_BIT(g_ram.actwk[0].u.play.control_bitfield, 0);
  }
  p_actwk->u.obj.actfree.bar.plholding = false;
  p_actwk->u.obj.actfree.bar.pl2holding = false;
  p_actwk->r_ptr = &barmove2;
  p_actwk->patno = 7;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = -0x400;
  breakgosubh(p_actwk, p_actwk->sprhs, bar_positbl2, bar_timertbl);
  barmove2(p_actwk);
}


static unsigned char bar_timertbl[24] = {
   7,  5,  2,  0,  1,  3,  4,  6,  7,  5,
   2,  0,  1,  3,  4,  6,  8,  9, 10, 11,
  12, 13, 14, 15
};


static SKC_point bar_positbl[16] = {
  { 0, -28 },
  { 0, -20 },
  { 0, -12 },
  { 0,  -4 },
  { 0,   4 },
  { 0,  12 },
  { 0,  20 },
  { 0,  28 },
  { 0,  36 },
  { 0, -36 },
  { 0,  44 },
  { 0, -44 },
  { 0,  52 },
  { 0, -52 },
  { 0,  60 },
  { 0, -60 }
};
static SKC_point bar_positbl2[16] = {
  { -28, 0 },
  { -20, 0 },
  { -12, 0 },
  {  -4, 0 },
  {   4, 0 },
  {  12, 0 },
  {  20, 0 },
  {  28, 0 },
  {  36, 0 },
  { -36, 0 },
  {  44, 0 },
  { -44, 0 },
  {  52, 0 },
  { -52, 0 },
  {  60, 0 },
  { -60, 0 }
};


static void breakgosubh(SKC_sprite_status* p_actwk, unsigned char part_cnt, SKC_point positbl[16], unsigned char* p_timertbl) {
  SKC_sprite_status* p_new_actwk = p_actwk;

  for (int i = 0; i < part_cnt; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
    }
    p_new_actwk->r_ptr = p_actwk->r_ptr;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->actflg.relative_coordinates = 1;
    p_new_actwk->actflg.onscreen = 1;
    short xposi = fp16_get_integer(p_actwk->xposi) + positbl[i].x;
    fp16_set_integer(&p_new_actwk->xposi, xposi);
    short yposi = fp16_get_integer(p_actwk->yposi) + positbl[i].y;
    p_new_actwk->sprpri = p_actwk->sprpri;
    p_new_actwk->sprhs = 4;
    p_new_actwk->sprvs = 4;
    p_new_actwk->patno = p_actwk->patno;
    p_new_actwk->xspeed = p_actwk->xspeed;
    p_new_actwk->yspeed = p_actwk->yspeed;
    p_new_actwk->u.obj.timer = p_timertbl[i];
  }

  soundset(89);
}


SKC_sprite_pattern* barpat[8] = {
  &barsp00,
  &barsp01,
  &barsp02,
  &barsp03,
  &barsp04,
  &barsp05,
  &barsp06,
  &barsp07
};


static SKC_sprite_pattern barsp00 = {
  2,
  {
    { -32, 3, 0x0000, -6 },
    {   0, 3, 0x1000, -6 }
  }
};
static SKC_sprite_pattern barsp01 = {
  3,
  {
    { -48, 3, 0x0000, -6 },
    { -16, 3, 0x0001, -6 },
    {  16, 3, 0x1000, -6 }
  }
};
static SKC_sprite_pattern barsp02 = {
  4,
  {
    { -64, 3, 0x0000, -6 },
    { -32, 3, 0x0001, -6 },
    {   0, 3, 0x0001, -6 },
    {  32, 3, 0x1000, -6 }
  }
};
static SKC_sprite_pattern barsp03 = {
  1,
  {
    { -4, 0, 0x0001, -4 }
  }
};
static SKC_sprite_pattern barsp04 = {
  2,
  {
    { -6, 12, 0x0005, -32 },
    { -6, 12, 0x0805,   0 }
  }
};
static SKC_sprite_pattern barsp05 = {
  3,
  {
    { -6, 12, 0x0005, -48 },
    { -6, 12, 0x0006, -16 },
    { -6, 12, 0x0805,  16 }
  }
};
static SKC_sprite_pattern barsp06 = {
  4,
  {
    { -6, 12, 0x0005, -64 },
    { -6, 12, 0x0006, -32 },
    { -6, 12, 0x0006,   0 },
    { -6, 12, 0x0805,  32 }
  }
};
static SKC_sprite_pattern barsp07 = {
  1,
  {
    { -4, 0, 0x0006, -4 }
  }
};


void water(SKC_sprite_status* p_actwk) {
  waterinit(p_actwk);
}


static void waterinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = waterpat;
  p_actwk->sproffset = 0x842E;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 128;
  p_actwk->sprvs = 8;
  p_actwk->actflg.compound = 1;
  p_actwk->u.obj.compound.child_cnt = 1;
  p_actwk->u.obj.compound.children[0].xposi = fp16_get_integer(p_actwk->xposi) + 192;
  p_actwk->u.obj.compound.children[0].yposi = fp16_get_integer(p_actwk->yposi);
  p_actwk->r_ptr = &watermove;
  watermove(p_actwk);
}


static void watermove(SKC_sprite_status* p_actwk) {
  short xposi = (g_ram.scra_h_posit >> 16) % 32 + 96;
  if (!(g_ram.gametimer & 1)) {
    xposi += 32;
  }
  fp16_set_integer(&p_actwk->xposi, xposi);
  fp16_set_integer(&p_actwk->yposi, g_ram.waterposi);
  p_actwk->u.obj.compound.children[0].xposi = fp16_get_integer(p_actwk->xposi) + 192;
  p_actwk->u.obj.compound.children[0].yposi = fp16_get_integer(p_actwk->yposi);
  if (!p_actwk->u.obj.actfree.water.paused) {
    if (g_ram.swdata.pressed.s == 1 || g_ram.swdata0.pressed.s == 1) {
      p_actwk->patno += 3;
      p_actwk->u.obj.actfree.water.paused = true;
    }
    else {
      if (p_actwk->pattim-- == 0) {
        p_actwk->pattim = 9;
        ++p_actwk->patno;
        if (p_actwk->patno >= 4) {
          p_actwk->patno = 1;
        }
      }
    }
  }
  else {
    if (g_ram.pauseflag == 0) {
      p_actwk->u.obj.actfree.water.paused = false;
      p_actwk->patno -= 3;
      if (p_actwk->pattim-- == 0) {
        p_actwk->pattim = 9;
        ++p_actwk->patno;
        if (p_actwk->patno >= 4) {
          p_actwk->patno = 1;
        }
      }
    }
  }
  p_actwk->u.obj.compound.children[0].patno = p_actwk->patno;
  actionsub(p_actwk);
}


static SKC_sprite_pattern* waterpat[7] = {
  &watersp0,
  &watersp0,
  &watersp1,
  &watersp2,
  &watersp3,
  &watersp4,
  &watersp5
};


static SKC_sprite_pattern watersp0 = {
  3,
  {
    { -3, 13, 0x0000, -96 },
    { -3, 13, 0x0000, -32 },
    { -3, 13, 0x0000, 32 }
  }
};
static SKC_sprite_pattern watersp1 = {
  3,
  {
    { -3, 13, 0x0008, -96 },
    { -3, 13, 0x0008, -32 },
    { -3, 13, 0x0008, 32 }
  }
};
static SKC_sprite_pattern watersp2 = {
  3,
  {
    { -3, 13, 0x0800, -96 },
    { -3, 13, 0x0800, -32 },
    { -3, 13, 0x0800, 32 }
  }
};
static SKC_sprite_pattern watersp3 = {
  6,
  {
    { -3, 13, 0x0000, -96 },
    { -3, 13, 0x0000, -64 },
    { -3, 13, 0x0000, -32 },
    { -3, 13, 0x0000, 0 },
    { -3, 13, 0x0000, 32 },
    { -3, 13, 0x0000, 64 }
  }
};
static SKC_sprite_pattern watersp4 = {
  6,
  {
    { -3, 13, 0x0008, -96 },
    { -3, 13, 0x0008, -64 },
    { -3, 13, 0x0008, -32 },
    { -3, 13, 0x0008, 0 },
    { -3, 13, 0x0008, 32 },
    { -3, 13, 0x0008, 64 }
  }
};
static SKC_sprite_pattern watersp5 = {
  6,
  {
    { -3, 13, 0x0800, -96 },
    { -3, 13, 0x0800, -64 },
    { -3, 13, 0x0800, -32 },
    { -3, 13, 0x0800, 0 },
    { -3, 13, 0x0800, 32 },
    { -3, 13, 0x0800, 64 }
  }
};


void block(SKC_sprite_status* p_actwk) {
  blockinit(p_actwk);
}


static void blockinit(SKC_sprite_status* p_actwk) {
  SKC_size blocktbl[4] = {
    { 16, 16 },
    { 32, 16 },
    { 48, 16 },
    { 64, 16 }
  };

  p_actwk->patno = p_actwk->u.obj.userflag;
  p_actwk->sprhs = blocktbl[p_actwk->u.obj.userflag].w;
  p_actwk->sprvs = blocktbl[p_actwk->u.obj.userflag].h;
  p_actwk->patbase = blockpat;
  p_actwk->sproffset = 0x43D4;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->r_ptr = &blockmove;
  blockmove(p_actwk);
}


static void blockmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk_skip_onscreen(p_actwk, data);
  frameoutchk(p_actwk);
}


SKC_sprite_pattern* blockpat[4] = {
  &blocksp00,
  &blocksp01,
  &blocksp02,
  &blocksp03
};


static SKC_sprite_pattern blocksp00 = {
  1,
  {
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern blocksp01 = {
  2,
  {
    { -16, 15, 0x0000, -32 },
    { -16, 15, 0x0000, 0 }
  }
};
static SKC_sprite_pattern blocksp02 = {
  3,
  {
    { -16, 15, 0x0000, -48 },
    { -16, 15, 0x0000, -16 },
    { -16, 15, 0x0000, 16 }
  }
};
static SKC_sprite_pattern blocksp03 = {
  4,
  {
    { -16, 15, 0x0000, -64 },
    { -16, 15, 0x0000, -32 },
    { -16, 15, 0x0000, 0 },
    { -16, 15, 0x0000, 32 }
  }
};


void itaicolit(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.powerdat.tbaria_die = 1;
  itaicoli(p_actwk);
}


void itaicolif(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.powerdat.fbaria_die = 1;
  itaicoli(p_actwk);
}


void itaicoli(SKC_sprite_status* p_actwk) {
  itaicoliinit(p_actwk);
}


static void itaicoliinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = scolipat;
  p_actwk->sproffset = 0x86BC;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->u.obj.cddat.die = 1;
  p_actwk->sprhs = ((p_actwk->u.obj.userflag & 0xF0) + 16) / 2;
  p_actwk->sprvs = ((p_actwk->u.obj.userflag & 0x0F) + 1) * 8;
  if (p_actwk->u.obj.cddat.right == 1) {
    p_actwk->r_ptr = &itaicolimoveh;
  }
  else if (p_actwk->u.obj.cddat.down == 1) {
    p_actwk->r_ptr = &itaicolimovev;
  }
  else {
    p_actwk->r_ptr = &itaicolimove;
    itaicolimove(p_actwk);
  }
}


static void itaicolimove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk_skip_onscreen(p_actwk, data);
  if (p_actwk->u.obj.cddat.plride == 1) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    itaicolisub(p_actwk, &g_ram.actwk[1]);
  }
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi > 640) {
    frameout_(p_actwk);
  }
  else if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void itaicolimoveh(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk_skip_onscreen(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_SIDE) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  if (result.plcoli[1] == HITCHK_COLI_SIDE) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi > 640) {
    frameout_(p_actwk);
  }
  else if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void itaicolimovev(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk_skip_onscreen(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi > 640) {
    frameout_(p_actwk);
  }
  else if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void itaicolisub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (!((p_actwk->u.obj.powerdat.unused0 == 1 && p_playerwk->u.play.powerdat.baria == 1)
      || (p_actwk->u.obj.powerdat.unused1 == 1 && p_playerwk->u.play.powerdat.muteki == 1)
      || (p_actwk->u.obj.powerdat.fbaria_die == 1 && p_playerwk->u.play.powerdat.fbaria == 1)
      || (p_actwk->u.obj.powerdat.tbaria_die == 1 && p_playerwk->u.play.powerdat.tbaria == 1)
      || (p_actwk->u.obj.powerdat.abaria_die == 1 && p_playerwk->u.play.powerdat.abaria == 1))) {
    togedamegesub(p_actwk, p_playerwk);
  }
}


void killcoli(SKC_sprite_status* p_actwk) {
  killcoliinit(p_actwk);
}


static void killcoliinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = scolipat;
  p_actwk->sproffset = 0x86BC;
  p_actwk->actflg.relative_coordinates == 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->u.obj.cddat.die = 1;
  p_actwk->sprhs = ((p_actwk->u.obj.userflag & 0xF0) + 16) / 2;
  p_actwk->sprvs = ((p_actwk->u.obj.userflag & 0x0F) + 1) * 8;
  if (p_actwk->u.obj.cddat.right == 1) {
    p_actwk->r_ptr = &killcolimoveh;
  }
  else if (p_actwk->u.obj.cddat.down == 1) {
    p_actwk->r_ptr = &killcolimovev;
  }
  else {
    p_actwk->r_ptr = &killcolimove;
    killcolimove(p_actwk);
  }
}


static void killcolimove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk_skip_onscreen(p_actwk, data);
  if (p_actwk->u.obj.cddat.plride == 1) {
    killcolisub(&g_ram.actwk[0]);
  }
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    killcolisub(&g_ram.actwk[1]);
  }
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi > 640) {
    frameout_(p_actwk);
  }
  else if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void killcolimoveh(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk_skip_onscreen(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_SIDE) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  if (result.plcoli[1] == HITCHK_COLI_SIDE) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi > 640) {
    frameout_(p_actwk);
  }
  else if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void killcolimovev(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk_skip_onscreen(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
    itaicolisub(p_actwk, &g_ram.actwk[0]);
  }
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.scr_x_no;
  if ((unsigned short)chunk_xposi > 640) {
    frameout_(p_actwk);
  }
  else if (g_ram.editmode != 0) {
    actionsub(p_actwk);
  }
}


static void killcolisub(SKC_sprite_status* p_playerwk) {
  playdieset(p_playerwk);
}
