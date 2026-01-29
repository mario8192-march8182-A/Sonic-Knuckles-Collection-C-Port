#include "ring.h"
#include "../types/actwkchkresult.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/fp8.h"
#include "../action.h"
#include "../constants.h"
#include "../etc.h"
static void ringinit(SKC_sprite_status* p_actwk);
static void ringmove(SKC_sprite_status* p_actwk);
static void ringget(SKC_sprite_status* p_actwk);
static void ringdie(SKC_sprite_status* p_actwk);
static void ringerase(SKC_sprite_status* p_actwk);
static void ringgetsub0(SKC_sprite_status* p_actwk);
static void ringgetsub1(SKC_sprite_status* p_actwk);
static void ringgetsub1__1up(void);
static void ringgetsub2__1up(void);
static void flyringg(SKC_sprite_status* p_actwk);
static void flyringinit(SKC_sprite_status* p_actwk);
static void flyringmove(SKC_sprite_status* p_actwk);
static void flyringget(SKC_sprite_status* p_actwk);
static void flyringdie(SKC_sprite_status* p_actwk);
static void flyringerase(SKC_sprite_status* p_actwk);
static void flyringmoveg(SKC_sprite_status* p_actwk);
static void tringinit(SKC_sprite_status* p_actwk);
static void tringmove(SKC_sprite_status* p_actwk);
static void tringget(SKC_sprite_status* p_actwk);
static void tringdie(SKC_sprite_status* p_actwk);
static void tringerase(SKC_sprite_status* p_actwk);
static void tringspdset(SKC_sprite_status* p_actwk);
static signed char* ringchg[1];
static signed char ringchg0[9];
static SKC_sprite_pattern ringsp0;
static SKC_sprite_pattern ringsp1;
static SKC_sprite_pattern ringsp2;
static SKC_sprite_pattern ringsp3;
static SKC_sprite_pattern ringsp4;
static SKC_sprite_pattern ringsp5;
static SKC_sprite_pattern ringsp6;
static SKC_sprite_pattern ringsp7;
static SKC_sprite_pattern ringsp8;
static SKC_sprite_status_handler slot_ring_move_tbl[3];
static void slot_ring_move(SKC_sprite_status* p_actwk);
static void slot_ring_get(SKC_sprite_status* p_actwk);
static void slot_ring_clr(SKC_sprite_status* p_actwk);
static signed char* sringchg[1];
static signed char sringchg0[9];

extern sonic3_ram g_ram;


void ring(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler ring_move_tbl[5] = {
    &ringinit,
    &ringmove,
    &ringget,
    &ringdie,
    &ringerase
  };

  ring_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void ringinit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = ringpat;
  p_actwk->sproffset = 0xA6BC;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->colino = 0x47;
  p_actwk->sprhs = 8;
  if (g_ram.vs_flag != 0) {
    p_actwk->sproffset = 0x63D2;
  }
  ringmove(p_actwk);
}


static void ringmove(SKC_sprite_status* p_actwk) {
  p_actwk->patno = g_ram.ring_patno;
  frameoutchkc(p_actwk);
}


static void ringget(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->colino = 0;
  p_actwk->sprpri = PRI_1;
  ringgetsub(p_actwk);
  ringdie(p_actwk);
}


static void ringdie(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, ringchg);
  actionsub(p_actwk);
}


static void ringerase(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


void ringgetsub(SKC_sprite_status* p_actwk) {
  ringgetsub0(p_actwk);
}


static void ringgetsub0(SKC_sprite_status* p_actwk) {
  if (g_ram.plring_act < RING_MAX) {
    ++g_ram.plring_act;
  }
  ringgetsub1(p_actwk);
}


static void ringgetsub1(SKC_sprite_status* p_actwk) {
  if (g_ram.plring < RING_MAX) {
    ++g_ram.plring;
    SET_BIT(g_ram.plring_f, 0);
    if (g_ram.plring >= RING_EXTRA_LIFE_1) {
      if (!BIT_IS_SET(g_ram.plring_f2, 1)) {
        SET_BIT(g_ram.plring_f2, 1);
        ringgetsub1__1up();
        return;
      }
      if (g_ram.plring >= RING_EXTRA_LIFE_2) {
        if (!BIT_IS_SET(g_ram.plring_f2, 2)) {
          SET_BIT(g_ram.plring_f2, 2);
          ringgetsub1__1up();
          return;
        }
      }
    }
  }
  soundset(51);
}


static void ringgetsub1__1up(void) {
  ++g_ram.pl_suu;
  ++g_ram.pl_suu_f;
  bgmset(42);
}


void ringgetsub2(SKC_sprite_status* p_actwk) {
  if (g_ram.pl2ring_act < 999) {
    ++g_ram.pl2ring_act;
  }
  if (g_ram.pl2ring < 999) {
    ++g_ram.pl2ring;
  }
  if (g_ram.vs_flag == 0) {
    ringgetsub1(p_actwk);
  }
  else {
    SET_BIT(g_ram.pl2ring_f, 0);
    if (g_ram.pl2ring >= 100) {
      if (!BIT_IS_SET(g_ram.pl2ring_f2, 1)) {
        SET_BIT(g_ram.pl2ring_f2, 1);
        ringgetsub2__1up();
        return;
      }
      if (g_ram.pl2ring >= 200) {
        if (!BIT_IS_SET(g_ram.pl2ring_f2, 2)) {
          SET_BIT(g_ram.pl2ring_f2, 1);
          ringgetsub2__1up();
          return;
        }
      }
    }
  }
  soundset(51);
}


static void ringgetsub2__1up(void) {
  ++g_ram.pl2_suu;
  bgmset(42);
}


void flyring(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler flyring_move_tbl[5] = {
    &flyringinit,
    &flyringmove,
    &flyringget,
    &flyringdie,
    &flyringerase
  };

  flyring_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void flyringg(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler flyring_move_tblg[5] = {
    &flyringinit,
    &flyringmoveg,
    &flyringget,
    &flyringdie,
    &flyringerase
  };

  flyring_move_tblg[p_actwk->r_no / 2](p_actwk);
}


static void flyringinit(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler p_routine = g_ram.reverse_gravity_flag == 0 ? &flyring : &flyringg;
  unsigned short flyring_cnt = p_actwk->u.obj.actfree.ring.player == 0 ? g_ram.plring : g_ram.pl2ring;
  if (flyring_cnt >= FLYRING_MAX) {
    flyring_cnt = FLYRING_MAX;
  }
  short angle = 648;
  short xspeed, yspeed;
  SKC_sprite_status* p_new_actwk = p_actwk;

  for (int i = 0; i < flyring_cnt; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
    }
    p_new_actwk->r_ptr = p_routine;
    p_new_actwk->r_no += 2;
    p_new_actwk->sprvsize = 8;
    p_new_actwk->sprhsize = 8;
    fp16_set_integer(&p_new_actwk->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&p_new_actwk->yposi, fp16_get_integer(p_actwk->yposi));
    p_new_actwk->patbase = ringpat;
    p_new_actwk->sproffset = 0xA6BC;
    p_new_actwk->actflg.relative_coordinates = 1;
    p_new_actwk->actflg.onscreen = 1;
    p_new_actwk->sprpri = PRI_3;
    p_new_actwk->colino = 0x47;
    p_new_actwk->sprhs = 8;
    g_ram.flyring_patcnt = 255;
    if (angle >= 0) {
      short sin, cos;
      sinset(angle, &sin, &cos);
      xspeed = sin * (1 << (angle >> 8));
      yspeed = cos * (1 << (angle >> 8));
      signed char fraction = fp8_get_fraction(angle) + 16;
      fp8_set_fraction(&angle, fraction);
      if (fraction > 0) {
        angle -= 128;
        if (angle < 0) {
          angle = 648;
        }
      }
    }
    p_new_actwk->xspeed = xspeed;
    p_new_actwk->yspeed = yspeed;
    xspeed = -xspeed;
    angle = -angle;
  }

  soundset(-71);
  g_ram.plring = 0;
  g_ram.plring_f = 0x80;
  g_ram.plring_f2 = 0;
  if (g_ram.reverse_gravity_flag == 0) {
    flyringmove(p_actwk);
  }
  else {
    flyringmoveg(p_actwk);
  }
}


static void flyringmove(SKC_sprite_status* p_actwk) {
  p_actwk->patno = g_ram.flyring_patno;
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->yspeed >= 0) {
    if (!(((g_ram.systemtimer & 0xFF) + (p_actwk - g_ram.actwk - 1)) & 7)) {
      if (p_actwk->actflg.onscreen == 1) {
        short yoffset = RingCheckFloorDist(p_actwk);
        if (yoffset < 0) {
          short yposi = fp16_get_integer(p_actwk->yposi) + yoffset;
          fp16_set_integer(&p_actwk->yposi, yposi);
          p_actwk->yspeed -= p_actwk->yspeed / 4;
          p_actwk->yspeed = -p_actwk->yspeed;
        }
      }
      if (g_ram.flyring_patcnt == 0
          || g_ram.scralim_down + 224 < (unsigned short)fp16_get_integer(p_actwk->yposi)) {
        flyringerase(p_actwk);
        return;
      }
    }
  }
  colibufferchk(p_actwk);
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + g_ram.frame_offset_x);
  actionsub(p_actwk);
}


static void flyringget(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->colino = 0;
  p_actwk->sprpri = PRI_1;
  ringgetsub(p_actwk);
  flyringdie(p_actwk);
}


static void flyringdie(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, ringchg);
  actionsub(p_actwk);
}


static void flyringerase(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void flyringmoveg(SKC_sprite_status* p_actwk) {
  p_actwk->patno = g_ram.flyring_patno;
  speedset2_g(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->yspeed >= 0) {
    if (!(((g_ram.systemtimer & 0xFF) + (p_actwk - g_ram.actwk - 1)) & 7)) {
      if (p_actwk->actflg.onscreen == 1) {
        short yoffset = RingCheckFloorDist_ReverseGravity(p_actwk);
        if (yoffset < 0) {
          short yposi = fp16_get_integer(p_actwk->yposi) - yoffset;
          fp16_set_integer(&p_actwk->yposi, yposi);
          p_actwk->yspeed -= p_actwk->yspeed / 4;
          p_actwk->yspeed = -p_actwk->yspeed;
        }
      }
      if (g_ram.flyring_patcnt == 0
          || g_ram.scralim_down + 224 < (unsigned short)fp16_get_integer(p_actwk->yposi)) {
        flyringerase(p_actwk);
        return;
      }
    }
  }
  colibufferchk(p_actwk);
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - g_ram.frame_offset_x);
  actionsub(p_actwk);
}


void tring(SKC_sprite_status* p_actwk) {
  tringinit(p_actwk);
}


static void tringinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = ringpat;
  p_actwk->sproffset = 0xA6BC;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_2;
  p_actwk->colino = 0x47;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
  p_actwk->sprvsize = 8;
  p_actwk->sprhsize = 8;
  p_actwk->r_ptr = &tringmove;
  tringmove(p_actwk);
}


static void tringmove(SKC_sprite_status* p_actwk) {
  if (p_actwk->r_no != 0) {
    tringget(p_actwk);
  }
  else {
    tringspdset(p_actwk);
    if (g_ram.actwk[0].u.play.cddat.thunder_baria == 0) {
      p_actwk->r_ptr = flyring;
      p_actwk->r_no = 2;
      g_ram.flyring_patcnt = 255;
    }
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = 3;
      ++p_actwk->patno;
      p_actwk->patno &= 3;
    }
    unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
    if (chunk_xposi <= 640) {
      colibufferchk(p_actwk);
      actionsub(p_actwk);
    }
    else {
      if (p_actwk->u.obj.flagwork_index != 0) {
        CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
      }
      if (p_actwk->u.obj.actfree.tring.ringwk_index != 0) {
        g_ram.ringwk[p_actwk->u.obj.actfree.tring.ringwk_index - 1] = 0;
      }
      frameout(p_actwk);
    }
  }
}


static void tringget(SKC_sprite_status* p_actwk) {
  p_actwk->colino = 0;
  p_actwk->sprpri = PRI_1;
  --g_ram.actring;
  ringgetsub(p_actwk);
  p_actwk->r_ptr = &tringdie;
  p_actwk->r_no = 0;
  tringdie(p_actwk);
}


static void tringdie(SKC_sprite_status* p_actwk) {
  if (p_actwk->r_no != 0) {
    tringerase(p_actwk);
  }
  else {
    patchg(p_actwk, ringchg);
    actionsub(p_actwk);
  }
}


static void tringerase(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void tringspdset(SKC_sprite_status* p_actwk) {
  short accel = 0x30;
  if (fp16_get_integer(g_ram.actwk[0].xposi) < fp16_get_integer(p_actwk->xposi)) {
    accel = -accel;
    if (p_actwk->xspeed >= 0) {
      accel *= 4;
    }
  }
  else if (p_actwk->xspeed < 0) {
    accel *= 4;
  }
  p_actwk->xspeed += accel;
  accel = 0x30;
  if (fp16_get_integer(g_ram.actwk[0].yposi) < fp16_get_integer(p_actwk->yposi)) {
    accel = -accel;
    if (p_actwk->yspeed >= 0) {
      accel *= 4;
    }
  }
  else if (p_actwk->yspeed < 0) {
    accel *= 4;
  }
  p_actwk->yspeed += accel;
  speedset2(p_actwk);
}


static signed char* ringchg[1] = {
  ringchg0
};


static signed char ringchg0[9] = { 5, 4, 5, 6, 7, -4, -121, -37, -112 };


SKC_sprite_pattern* ringpat[9] = {
  &ringsp0,
  &ringsp1,
  &ringsp2,
  &ringsp3,
  &ringsp4,
  &ringsp5,
  &ringsp6,
  &ringsp7,
  &ringsp8
};


static SKC_sprite_pattern ringsp0 = {
  1,
  {
    { -8, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern ringsp1 = {
  1,
  {
    { -8, 5, 0x0004, -8 }
  }
};
static SKC_sprite_pattern ringsp2 = {
  1,
  {
    { -8, 1, 0x0008, -4 }
  }
};
static SKC_sprite_pattern ringsp3 = {
  1,
  {
    { -8, 5, 0x0804, -8 }
  }
};
static SKC_sprite_pattern ringsp4 = {
  1,
  {
    { -8, 5, 0x000A, -8 }
  }
};
static SKC_sprite_pattern ringsp5 = {
  1,
  {
    { -8, 5, 0x180A, -8 }
  }
};
static SKC_sprite_pattern ringsp6 = {
  1,
  {
    { -8, 5, 0x080A, -8 }
  }
};
static SKC_sprite_pattern ringsp7 = {
  1,
  {
    { -8, 5, 0x100A, -8 }
  }
};
static SKC_sprite_pattern ringsp8 = {
  0,
  {}
};


void slot_ring(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler slot_ring_move_tbl[3] = {
    &slot_ring_move,
    &slot_ring_get,
    &slot_ring_clr
  };

  slot_ring_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void slot_ring_move(SKC_sprite_status* p_actwk) {
  long oya_xposi = 0;
  fp16_set_integer(&oya_xposi, p_actwk->u.obj.actfree.slot_ring.oya_xposi);
  long wk = (p_actwk->u.obj.actfree.slot_ring.angled_xposi - oya_xposi) / 16;
  p_actwk->u.obj.actfree.slot_ring.angled_xposi -= wk;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->u.obj.actfree.slot_ring.angled_xposi));
  long oya_yposi = 0;
  fp16_set_integer(&oya_yposi, p_actwk->u.obj.actfree.slot_ring.oya_yposi);
  wk = (p_actwk->u.obj.actfree.slot_ring.angled_yposi - oya_yposi) / 16;
  p_actwk->u.obj.actfree.slot_ring.angled_yposi -= wk;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->u.obj.actfree.slot_ring.angled_yposi));
  patchg(p_actwk, sringchg);
  --p_actwk->u.obj.actfree.slot_ring.unknown40;
  if (p_actwk->u.obj.actfree.slot_ring.unknown40 != 0) {
    actionsub(p_actwk);
  }
  else {
    --*p_actwk->u.obj.actfree.slot_ring.unknown2e_ptr;
    ringgetsub(p_actwk);
    p_actwk->r_no += 2;
    slot_ring_get(p_actwk);
  }
}


static void slot_ring_get(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, ringchg);
  actionsub(p_actwk);
}


static void slot_ring_clr(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


static signed char* sringchg[1] = {
  sringchg0
};


static signed char sringchg0[9] = { 1, 0, 1, 2, 3, -1, -121, -37, -112 };
