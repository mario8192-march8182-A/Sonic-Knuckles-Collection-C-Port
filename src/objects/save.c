#include "save.h"
#include <stdbool.h>
#include "../data/cg/save.h"
#include "../types/actwkchkresult.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../constants.h"
#include "../dev.h"
#include "../etc.h"
static void saveinit(SKC_sprite_status* pActwk);
static void savemove(SKC_sprite_status* pActwk);
static void savemove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char markerno);
static void savemove2(SKC_sprite_status* pActwk);
static void savemove3(SKC_sprite_status* p_actwk);
static void playsave(SKC_sprite_status* p_actwk);
static void playload2(SKC_sprite_status* p_actwk);
static signed char* savechg[3];
static signed char savechg0[3];
static signed char savechg1[3];
static signed char savechg2[4];
static SKC_sprite_pattern savesp00;
static SKC_sprite_pattern savesp01;
static SKC_sprite_pattern savesp02;
static SKC_sprite_pattern savesp03;
static SKC_sprite_pattern savesp04;
static SKC_sprite_pattern* starpat[3];
static SKC_sprite_pattern starsp00;
static SKC_sprite_pattern starsp01;
static SKC_sprite_pattern starsp02;
static void ostar00(SKC_sprite_status* p_actwk, short sin, short cos, short d1, short d2);
static void ostar02(SKC_sprite_status* p_actwk, short sin, short cos);
static void ostar03(SKC_sprite_status* p_actwk, short sin, short cos, short d1);
static void ostar04(SKC_sprite_status* p_actwk, short sin, short cos, short d1);
static void ostar06(SKC_sprite_status* p_actwk, short xoffset, short yoffset);
static void ostar08(SKC_sprite_status* p_actwk, unsigned char patno);
static void ostarend(SKC_sprite_status* p_actwk);

extern sonic3_ram g_ram;
extern bool g_sonic3_alone;

typedef enum bonus_stage_id {
  BONUS_STAGE_ROLLING_JUMP = 0,
  BONUS_STAGE_SLOT_MACHINE = 1,
  BONUS_STAGE_GUMBALL_MACHINE = 2
}
bonus_stage_id;


void save(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler save_move_tbl[5] = {
    &saveinit,
    &savemove,
    &savemove2,
    &savemove3,
    &o_star
  };

  save_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static void saveinit(SKC_sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = savepat;
  p_actwk->sproffset = 0x05EC;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 40;
  p_actwk->sprpri = PRI_5;
  if (BIT_IS_SET(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 0)
      || (g_ram.markerno & 0x7F) >= (p_actwk->u.obj.userflag & 0x7F)) {
    SET_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 0);
    p_actwk->mstno = 2;
  }
  savemove(p_actwk);
}


static void savemove(SKC_sprite_status* p_actwk) {
  if (g_ram.editmode == 0) {
    savemove__sub(p_actwk, &g_ram.actwk[0], g_ram.markerno);
  }
  savemove2(p_actwk);
}


static void savemove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char markerno) {
  if ((markerno & 0x7F) < (p_actwk->u.obj.userflag & 0x7F)) {
    short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + 8;
    if ((unsigned short)distance < 16) {
      distance = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi) + 64;
      if ((unsigned short)distance < 104) {
        soundset(99);
        SKC_actwkchk_result result = actwkchk();
        if (result.actwk_ptr != 0) {
          result.actwk_ptr->r_ptr = &save;
          result.actwk_ptr->r_no = 6;
          result.actwk_ptr->u.obj.actfree.save.oya_xposi = fp16_get_integer(p_actwk->xposi);
          result.actwk_ptr->u.obj.actfree.save.oya_yposi = fp16_get_integer(p_actwk->yposi) - 20;
          result.actwk_ptr->patbase = p_actwk->patbase;
          result.actwk_ptr->sproffset = p_actwk->sproffset;
          result.actwk_ptr->actflg.relative_coordinates = 1;
          result.actwk_ptr->sprhs = 8;
          result.actwk_ptr->sprvs = 8;
          result.actwk_ptr->sprpri = PRI_4;
          result.actwk_ptr->patno = 2;
          result.actwk_ptr->u.obj.actfree.save.counter = 32;
          result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
          if ((g_sonic3_alone && g_ram.plring >= 20) || (!g_sonic3_alone && g_ram.plring >= 50)) {
            o_starinit(p_actwk);
          }
        }
        p_actwk->mstno = 1;
        playsave(p_actwk);
        p_actwk->r_no = 4;
        SET_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 0);
      }
    }
  }
  else if (p_actwk->mstno == 0) {
    p_actwk->mstno = 2;
  }
}


static void savemove2(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, savechg);
  frameoutchk(p_actwk);
}


static void savemove3(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.save.counter-- == 0) {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    if (p_parentwk->r_ptr == &save) {
      p_parentwk->mstno = 2;
      p_parentwk->patno = 0;
    }
    frameout(p_actwk);
  }
  else {
    unsigned char angle = p_actwk->direc1 - 64;
    p_actwk->direc1 -= 16;
    short sin, cos;
    sinset(angle, &sin, &cos);
    long cos_l = cos * 3072;
    short xposi = fp16_get_integer(cos_l) + p_actwk->u.obj.actfree.save.oya_xposi;
    fp16_set_integer(&p_actwk->xposi, xposi);
    long sin_l = sin * 3072;
    short yposi = fp16_get_integer(sin_l) + p_actwk->u.obj.actfree.save.oya_yposi;
    fp16_set_integer(&p_actwk->yposi, yposi);
    frameoutchk(p_actwk);
  }
}


static void playsave(SKC_sprite_status* p_actwk) {
  g_ram.markerno = p_actwk->u.obj.userflag & 0xFF;
  g_ram.plxposi_s = fp16_get_integer(p_actwk->xposi);
  g_ram.plyposi_s = fp16_get_integer(p_actwk->yposi);
  playsave1(p_actwk);
}


void playsave1(SKC_sprite_status* p_actwk) {
  g_ram.markerno_s = g_ram.markerno;
  g_ram.stageno_s = g_ram.stageno;
  g_ram.stageno_is = g_ram.stageno_i;
  g_ram.plsproffset_s = g_ram.actwk[0].sproffset;
  g_ram.pl_top_solid_bit_s = g_ram.actwk[0].u.play.top_solid_bit;
  g_ram.pl_lrb_solid_bit_s = g_ram.actwk[0].u.play.lrb_solid_bit;
  g_ram.plring_s = g_ram.plring;
  g_ram.plring_f2_s = g_ram.plring_f2;
  g_ram.pltime_s = g_ram.pltime;
  g_ram.scr_resize_no_s = g_ram.scr_resize_no;
  g_ram.scralim_down_s = g_ram.scralim_down;
  g_ram.scra_h_posit_s = g_ram.scra_h_posit >> 16;
  g_ram.scra_v_posit_s = g_ram.scra_v_posit >> 16;
  g_ram.waterposi_s = g_ram.waterposi;
  g_ram.waterflag_s = g_ram.waterflag;
}


void playsave2(SKC_sprite_status* p_actwk) {
  g_ram.markerno_s2 = g_ram.markerno;
  g_ram.stageno_s2 = g_ram.stageno;
  g_ram.stageno_is2 = g_ram.stageno_i;
  g_ram.plxposi_s2 = fp16_get_integer(p_actwk->xposi);
  g_ram.plyposi_s2 = fp16_get_integer(p_actwk->yposi);
  g_ram.plsproffset_s2 = g_ram.actwk[0].sproffset;
  g_ram.pl_top_solid_bit_s2 = g_ram.actwk[0].u.play.top_solid_bit;
  g_ram.pl_lrb_solid_bit_s2 = g_ram.actwk[0].u.play.lrb_solid_bit;
  g_ram.plring_s2 = g_ram.plring;
  g_ram.plring_f2_s2 = g_ram.plring_f2;
  g_ram.pltime_s2 = g_ram.pltime;
  g_ram.scr_resize_no_s2 = g_ram.scr_resize_no;
  g_ram.scralim_down_s2 = g_ram.scralim_down;
  g_ram.scra_h_posit_s2 = g_ram.scra_h_posit >> 16;
  g_ram.scra_v_posit_s2 = g_ram.scra_v_posit >> 16;
  g_ram.waterposi_s2 = g_ram.waterposi;
  g_ram.waterflag_s2 = g_ram.waterflag;
  g_ram.plcddat2_s2 = g_ram.actwk[0].u.play.cddat.baria
      | g_ram.actwk[0].u.play.cddat.muteki << 1
      | g_ram.actwk[0].u.play.cddat.speedup << 2
      | g_ram.actwk[0].u.play.cddat.unusedb << 3
      | g_ram.actwk[0].u.play.cddat.flame_baria << 4
      | g_ram.actwk[0].u.play.cddat.thunder_baria << 5
      | g_ram.actwk[0].u.play.cddat.aqua_baria << 6
      | g_ram.actwk[0].u.play.cddat.infinite_inertia << 7;
}


void playload(SKC_sprite_status* p_actwk) {
  if (g_ram.marker_flag != 0) {
    playload2(p_actwk);
  }
  else {
    g_ram.markerno = g_ram.markerno_s;
    g_ram.stageno = g_ram.stageno_s;
    g_ram.stageno_i = g_ram.stageno_is;
    fp16_set_integer(&g_ram.actwk[0].xposi, g_ram.plxposi_s);
    fp16_set_integer(&g_ram.actwk[0].yposi, g_ram.plyposi_s);
    g_ram.plring = g_ram.plring_s;
    g_ram.plring_f2 = g_ram.plring_f2_s;
    if (g_ram.plresetflag == 0) {
      g_ram.plring = 0;
      g_ram.plring_f2 = 0;
    }
    g_ram.pltime = g_ram.pltime_s;
    g_ram.pltime.frames = 59;
    --g_ram.pltime.seconds;
    g_ram.actwk[0].sproffset = g_ram.plsproffset_s;
    g_ram.actwk[0].u.play.top_solid_bit = g_ram.pl_top_solid_bit_s;
    g_ram.actwk[0].u.play.lrb_solid_bit = g_ram.pl_lrb_solid_bit_s;
    g_ram.scr_resize_no = g_ram.scr_resize_no_s;
    g_ram.scralim_down = g_ram.scralim_down_s;
    g_ram.scralim_n_down = g_ram.scralim_down_s;
    g_ram.scra_h_posit = g_ram.scra_h_posit_s << 16 | g_ram.scra_h_posit & 0x0000FFFF;
    g_ram.scra_v_posit = g_ram.scra_v_posit_s << 16 | g_ram.scra_v_posit & 0x0000FFFF;
    if (g_ram.watermode != 0) {
      g_ram.waterposi = g_ram.waterposi_s;
      g_ram.waterflag = g_ram.waterflag_s;
    }
  }
}


static void playload2(SKC_sprite_status* p_actwk) {
  g_ram.marker_flag = 0;
  g_ram.stageno = g_ram.stageno_s2;
  g_ram.stageno_i = g_ram.stageno_is2;
  fp16_set_integer(&g_ram.actwk[0].xposi, g_ram.plxposi_s2);
  fp16_set_integer(&g_ram.actwk[0].yposi, g_ram.plyposi_s2);
  g_ram.plring = g_ram.plring_s2;
  g_ram.plring_f2 = g_ram.plring_f2_s2;
  g_ram.pltime = g_ram.pltime_s2;
  g_ram.pltime.frames = 59;
  --g_ram.pltime.seconds;
  g_ram.actwk[0].sproffset = g_ram.plsproffset_s2;
  g_ram.actwk[0].u.play.top_solid_bit = g_ram.pl_top_solid_bit_s2;
  g_ram.actwk[0].u.play.lrb_solid_bit = g_ram.pl_lrb_solid_bit_s2;
  g_ram.scr_resize_no = g_ram.scr_resize_no_s2;
  g_ram.scralim_down = g_ram.scralim_down_s2;
  g_ram.scralim_n_down = g_ram.scralim_down_s2;
  g_ram.scra_h_posit = g_ram.scra_h_posit_s2 << 16 | g_ram.scra_h_posit & 0x0000FFFF;
  g_ram.scra_v_posit = g_ram.scra_v_posit_s2 << 16 | g_ram.scra_v_posit & 0x0000FFFF;
  if (g_ram.watermode != 0) {
    g_ram.waterposi = g_ram.waterposi_s2;
    g_ram.waterflag = g_ram.waterflag_s2;
  }
}


static signed char* savechg[3] = {
  savechg0,
  savechg1,
  savechg2
};


static signed char savechg0[3] = { 15, 0, -1 };
static signed char savechg1[3] = { 15, 1, -1 };
static signed char savechg2[4] = { 3, 0, 4, -1 };


SKC_sprite_pattern* savepat[5] = {
  &savesp00,
  &savesp01,
  &savesp02,
  &savesp03,
  &savesp04
};


static SKC_sprite_pattern savesp00 = {
  4,
  {
    {  -24, 1, 0x000E, -4 },
    {   -8, 3, 0x0010, -8 },
    {   -8, 3, 0x0810,  0 },
    {  -40, 5, 0x0006, -8 }
  }
};
static SKC_sprite_pattern savesp01 = {
  3,
  {
    { -24, 1, 0x000E, -4 },
    {  -8, 3, 0x0010, -8 },
    {  -8, 3, 0x0810,  0 }
  }
};
static SKC_sprite_pattern savesp02 = {
  1,
  {
    { -8, 5, 0x0006, -8 }
  }
};
static SKC_sprite_pattern savesp03 = {
  1,
  {
    { -8, 5, 0x000A, -8 }
  }
};
static SKC_sprite_pattern savesp04 = {
  4,
  {
    { -24, 1, 0x000E, -4 },
    {  -8, 3, 0x0010, -8 },
    {  -8, 3, 0x0810,  0 },
    { -40, 5, 0x000A, -8 }
  }
};


static SKC_sprite_pattern* starpat[3] = {
  &starsp00,
  &starsp01,
  &starsp02
};


static SKC_sprite_pattern starsp00 = {
  1,
  {
    { -8, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern starsp01 = {
  1,
  {
    { -4, 0, 0x0004, -4 }
  }
};
static SKC_sprite_pattern starsp02 = {
  1,
  {
    { -4, 0, 0x0005, -4 }
  }
};


void o_starinit(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_new_actwk;
  unsigned short angle = 0;

  for (int i = 0; i < 4; ++i) {
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->r_ptr = p_actwk->r_ptr;
    result.actwk_ptr->patbase = starpat;
    result.actwk_ptr->sproffset = 0x05EC;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->r_no = 8;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    result.actwk_ptr->u.obj.actfree.save.oya_xposi = fp16_get_integer(p_actwk->xposi);
    short yposi = fp16_get_integer(p_actwk->yposi) - 48;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
    result.actwk_ptr->u.obj.actfree.save.oya_yposi = yposi;
    result.actwk_ptr->sprpri = p_actwk->sprpri;
    result.actwk_ptr->sprhs = 8;
    result.actwk_ptr->patno = 1;
    result.actwk_ptr->xspeed = -0x400;
    result.actwk_ptr->yspeed = 0;
    p_actwk->u.obj.actfree.save.angle = angle;
    angle += 64;
  }

  unsigned char* p_cg;
  if (!g_sonic3_alone) {
    short bonus_stage_id = (g_ram.plring - 20) / 15;
    unsigned char bonus_stage_cnt = g_ram.cartridge != 0 ? 2 : 3;
    bonus_stage_id %= bonus_stage_cnt;

    switch (bonus_stage_id) {
      case BONUS_STAGE_ROLLING_JUMP:
        p_cg = orange_star_ring_cg;
        break;
      case BONUS_STAGE_SLOT_MACHINE:
        p_cg = red_star_ring_cg;
        break;
      case BONUS_STAGE_GUMBALL_MACHINE:
      default:
        p_cg = white_star_ring_cg;
        break;
    }
  }
  else {
    p_cg = white_star_ring_cg;
  }
  unlze_moduled(&g_mdVram[0xBD80], p_cg);
}


void o_star(SKC_sprite_status* p_actwk) {
  if (p_actwk->colicnt != 0) {
    if (p_actwk->colicnt & 1) {
      g_ram.marker_flag = 2;
      if (g_sonic3_alone) {
        g_ram.stageno = GUMBALL_MACHINE_ACT_1;
        g_ram.stageno_i = GUMBALL_MACHINE_ACT_1;
        g_ram.markerno = 0;
        g_ram.gameflag = 1;
        g_ram.plcddat2_s2 = g_ram.actwk[0].u.play.cddat.baria
            | g_ram.actwk[0].u.play.cddat.muteki << 1
            | g_ram.actwk[0].u.play.cddat.speedup << 2
            | g_ram.actwk[0].u.play.cddat.unusedb << 3
            | g_ram.actwk[0].u.play.cddat.flame_baria << 4
            | g_ram.actwk[0].u.play.cddat.thunder_baria << 5
            | g_ram.actwk[0].u.play.cddat.aqua_baria << 6
            | g_ram.actwk[0].u.play.cddat.infinite_inertia << 7;
        g_ram.plresetflag = 1;
        actunset();
      }
      else {
        short bonus_stage_id = (g_ram.plring_s - 20) / 15;
        unsigned char bonus_stage_cnt = g_ram.cartridge != 0 ? 2 : 3;
        bonus_stage_id %= bonus_stage_cnt;
        unsigned short stageno;

        switch (bonus_stage_id) {
          case BONUS_STAGE_ROLLING_JUMP:
          default:
            stageno = ROLLING_JUMP_ACT_1;
            break;
          case BONUS_STAGE_SLOT_MACHINE:
            stageno = SLOT_MACHINE_ACT_1;
            break;
          case BONUS_STAGE_GUMBALL_MACHINE:
            stageno = GUMBALL_MACHINE_ACT_1;
            break;
        }

        g_ram.stageno = stageno;
        g_ram.stageno_i = stageno;
        g_ram.plring_s = g_ram.plring;
        g_ram.plring_f2_s = g_ram.plring_f2;
        g_ram.markerno = 0;
        g_ram.gameflag = 1;
        g_ram.plcddat2_s2 = g_ram.actwk[0].u.play.cddat.baria
            | g_ram.actwk[0].u.play.cddat.flame_baria << 4
            | g_ram.actwk[0].u.play.cddat.thunder_baria << 5
            | g_ram.actwk[0].u.play.cddat.aqua_baria << 6;
        g_ram.plcddat2_s = g_ram.plcddat2_s2;
        g_ram.plresetflag = 1;
        actunset();
      }
    }
    p_actwk->colicnt = 0;
  }
  p_actwk->u.obj.actfree.save.angle += 10;
  short sin, cos;
  sinset(p_actwk->u.obj.actfree.save.angle, &sin, &cos);
  sin /= 32;
  cos /= 8;
  short d1 = cos;
  short d2 = (p_actwk->u.obj.actfree.save.angle & 0x3E0) / 32;
  if (d2 > 16) {
    d1 = -d1;
    d2 %= 16;
  }
  if (d2 > 8) {
    d2 = -d2;
    d2 %= 8;
  }
  ostar00(p_actwk, sin, cos, d1, d2);
}


static void ostar00(SKC_sprite_status* p_actwk, short sin, short cos, short d1, short d2) {
  short d4 = 0;

  for (int i = 0; i < 3; ++i) {
    d2 /= 2;
    if (d2 != 0) {
      d4 += d1;
    }
    d1 *= 2;
  }

  sin += d4 / 16;
  ++p_actwk->u.obj.actfree.save.counter;
  if (p_actwk->u.obj.actfree.save.counter == 128) {
    ostar03(p_actwk, sin, cos, d1);
  }
  else if (p_actwk->u.obj.actfree.save.counter > 128) {
    ostar04(p_actwk, sin, cos, d1);
  }
  else {
    ostar02(p_actwk, sin, cos);
  }
}


static void ostar02(SKC_sprite_status* p_actwk, short sin, short cos) {
  short yoffset = sin * p_actwk->u.obj.actfree.save.counter / 128;
  short xoffset = cos * p_actwk->u.obj.actfree.save.counter / 128;
  ostar06(p_actwk, xoffset, yoffset);
}


static void ostar03(SKC_sprite_status* p_actwk, short sin, short cos, short d1) {
  p_actwk->colino = 0xD8;
  ostar04(p_actwk, sin, cos, d1);
}


static void ostar04(SKC_sprite_status* p_actwk, short sin, short cos, short d1) {
  if (d1 <= 384) {
    ostar06(p_actwk, cos, sin);
  }
  else {
    d1 = -d1;
    d1 += 512;
    if (d1 < 0) {
      ostarend(p_actwk);
    }
    else {
      ostar02(p_actwk, sin, cos);
    }
  }
}


static void ostar06(SKC_sprite_status* p_actwk, short xoffset, short yoffset) {
  short xposi = p_actwk->u.obj.actfree.save.oya_xposi + xoffset;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = p_actwk->u.obj.actfree.save.oya_yposi + yoffset;
  fp16_set_integer(&p_actwk->yposi, yposi);
  ++p_actwk->patcnt;
  unsigned char patno = (p_actwk->patcnt & 6) >> 1;
  if (patno == 3) {
    patno = 1;
  }
  ostar08(p_actwk, patno);
}


static void ostar08(SKC_sprite_status* p_actwk, unsigned char patno) {
  p_actwk->patno = patno;
  frameoutchkc(p_actwk);
}


static void ostarend(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}
