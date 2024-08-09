#include "globals.h"
#include "macros.h"
#include "util.h"
#include "save.h"
#include "004xxxxx.h"
#include "resources.h"
static sprite_status_handler save_move_tbl[5];
static void saveinit(sprite_status* pActwk);
static void savemove(sprite_status* pActwk);
static void savemove__sub(sprite_status* p_actwk, sprite_status* p_playerwk);
static void savemove2(sprite_status* pActwk);
static void savemove3(sprite_status* p_actwk);
static void playsave(sprite_status* p_actwk);
static void playload2(sprite_status* p_actwk);
static signed char* savechg[3];
static signed char savechg0[3];
static signed char savechg1[3];
static signed char savechg2[4];
static signed char savesp00[26];
static signed char savesp01[20];
static signed char savesp02[8];
static signed char savesp03[8];
static signed char savesp04[26];
static signed char* starpat[3];
static signed char starsp00[8];
static signed char starsp01[8];
static signed char starsp02[8];


void save(sprite_status* p_actwk) {
  save_move_tbl[p_actwk->r_no / 2](p_actwk);
}


static sprite_status_handler save_move_tbl[5] = {
  &saveinit,
  &savemove,
  &savemove2,
  &savemove3,
  &o_star
};


static void saveinit(sprite_status* p_actwk) {
  p_actwk->r_no += 2;
  p_actwk->patbase = savepat;
  p_actwk->sproffset = 1516;
  p_actwk->actflg = 4;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 40;
  p_actwk->sprpri = PRI_5;
  if (BIT_0_IS_SET(g_mdRam.flagwork[p_actwk->actfree.save.flagwork_index - 1])
      || (g_mdRam.markerno & 0x7F) >= (p_actwk->userflag1 & 0x7F)) { // unsigned
    SET_BIT_0(g_mdRam.flagwork[p_actwk->actfree.save.flagwork_index - 1]);
    p_actwk->mstno = 2;
  }
  savemove(p_actwk);
}


static void savemove(sprite_status* p_actwk) {
  if (g_mdRam.edit_r_no == 0) {
    savemove__sub(p_actwk, &g_mdRam.actwk[0]);
  }
  savemove2(p_actwk);
}


static void savemove__sub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  if ((g_mdRam.markerno & 0x7F) < (p_actwk->userflag1 & 0x7F)) {
    short distance = LONG_HIGH(p_actwk->xposi) - LONG_HIGH(p_playerwk->xposi) + 8;
    if (util__to_unsigned(distance) >= 16) return; // unsigned
    distance = LONG_HIGH(p_actwk->yposi) - LONG_HIGH(p_playerwk->yposi) + 64;
    if (util__to_unsigned(distance) >= 104) return; // unsigned
    soundset(99);
    sprite_status* p_new_actwk;
    short slot_cnt;
    bool created = Create_New_Sprite(&p_new_actwk, &slot_cnt);
    if (created) {
      p_new_actwk->r_ptr = &save;
      p_new_actwk->r_no = 6;
      p_new_actwk->actfree.save.parent_xposi = LONG_HIGH(p_actwk->xposi);
      p_new_actwk->actfree.save.parent_yposi = LONG_HIGH(p_actwk->yposi) - 20;
      p_new_actwk->patbase = p_actwk->patbase;
      p_new_actwk->sproffset = p_actwk->sproffset;
      p_new_actwk->actflg = p_actwk->actflg;
      p_new_actwk->sprhs = 8;
      p_new_actwk->sprvs = 8;
      p_new_actwk->sprpri = PRI_4;
      p_new_actwk->patno = 2;
      p_new_actwk->actfree.save.counter = 32;
      p_new_actwk->actfree.save.parent = p_actwk - g_mdRam.actwk;
      bool enough_rings = false;
      if (g_sonic3Alone != 0) {
        enough_rings = g_mdRam.plring >= 50;
      }
      else {
        enough_rings = g_mdRam.plring >= 20;
      }
      if (enough_rings) {
        o_starinit(p_actwk);
      }
    }
    p_actwk->mstno = 1;
    playsave(p_actwk);
    p_actwk->r_no = 4;
    SET_BIT_0(g_mdRam.flagwork[p_actwk->actfree.save.flagwork_index - 1]);
  }
  else if (p_actwk->mstno == 0) {
    p_actwk->mstno = 2;
  }
}


static void savemove2(sprite_status* p_actwk) {
  patchg(p_actwk, savechg);
  frameoutchk(p_actwk);
}


static void savemove3(sprite_status* p_actwk) {
  --p_actwk->actfree.save.counter;
  if (p_actwk->actfree.save.counter < 0) {
    sprite_status* p_sub_actwk = &g_mdRam.actwk[p_actwk->actfree.save.parent];
    if (p_sub_actwk->r_ptr == &save) {
      p_sub_actwk->mstno = 2;
      p_sub_actwk->patno = 0;
    }
    frameout(p_actwk);
  }
  else {
    p_actwk->direc1 -= 16;
    short sin, cos;
    sinset(util__char_to_unsigned(p_actwk->direc1 - 64), &sin, &cos);
    long cos_l = cos * 3072;
    cos_l = LONG_LOW(cos_l) + p_actwk->actfree.save.parent_xposi;
    util__assign_high(&p_actwk->xposi, LONG_LOW(cos_l));
    long sin_l = sin * 3072;
    sin_l = LONG_LOW(sin_l) + p_actwk->actfree.save.parent_yposi;
    util__assign_high(&p_actwk->yposi, LONG_LOW(sin_l));
    frameoutchk(p_actwk);
  }
}


static void playsave(sprite_status* p_actwk) {
  g_mdRam.markerno = p_actwk->userflag1;
  g_mdRam.plxposi_s = LONG_HIGH(p_actwk->xposi);
  g_mdRam.plyposi_s = LONG_HIGH(p_actwk->yposi);
  playsave1(p_actwk);
}


void playsave1(sprite_status* p_actwk) {
  g_mdRam.markerno_s = g_mdRam.markerno;
  g_mdRam.stageno_s = g_mdRam.stageno;
  g_mdRam.stageno_is = g_mdRam.stageno_i;
  g_mdRam.plsproffset_s = g_mdRam.actwk[0].sproffset;
  g_mdRam.plcolibits_s = g_mdRam.actwk[0].actfree.player.colibits;
  g_mdRam.plring_s = g_mdRam.plring;
  g_mdRam.plring_f2_s = g_mdRam.plring_f2;
  g_mdRam.pltime_s = g_mdRam.pltime;
  g_mdRam.scr_resize_no_s = g_mdRam.scr_resize_no;
  g_mdRam.scralim_down_s = g_mdRam.scralim_down;
  g_mdRam.scra_h_posit_s = LONG_HIGH(g_mdRam.scra_h_posit);
  g_mdRam.scra_v_posit_s = LONG_HIGH(g_mdRam.scra_v_posit);
  g_mdRam.waterposi_s = g_mdRam.waterposi;
  g_mdRam.waterflag_s = g_mdRam.waterflag;
}


void playsave2(sprite_status* p_actwk) {
  g_mdRam.markerno_s2 = g_mdRam.markerno;
  g_mdRam.stageno_s2 = g_mdRam.stageno;
  g_mdRam.stageno_is2 = g_mdRam.stageno_i;
  g_mdRam.plxposi_s2 = LONG_HIGH(p_actwk->xposi);
  g_mdRam.plyposi_s2 = LONG_HIGH(p_actwk->yposi);
  g_mdRam.plsproffset_s2 = g_mdRam.actwk[0].sproffset;
  g_mdRam.plcolibits_s2 = g_mdRam.actwk[0].actfree.player.colibits;
  g_mdRam.plring_s2 = g_mdRam.plring;
  g_mdRam.plring_f2_s2 = g_mdRam.plring_f2;
  g_mdRam.pltime_s2 = g_mdRam.pltime;
  g_mdRam.scr_resize_no_s2 = g_mdRam.scr_resize_no;
  g_mdRam.scralim_down_s2 = g_mdRam.scralim_down;
  g_mdRam.scra_h_posit_s2 = LONG_HIGH(g_mdRam.scra_h_posit);
  g_mdRam.scra_v_posit_s2 = LONG_HIGH(g_mdRam.scra_v_posit);
  g_mdRam.waterposi_s2 = g_mdRam.waterposi;
  g_mdRam.waterflag_s2 = g_mdRam.waterflag;
  g_mdRam.plcddat2_s2 = g_mdRam.actwk[0].cddat2;
}


void playload(sprite_status* p_actwk) {
  if (g_mdRam.marker_flag != 0) {
    playload2(p_actwk);
    return;
  }
  g_mdRam.markerno = g_mdRam.markerno_s;
  g_mdRam.stageno = g_mdRam.stageno_s;
  g_mdRam.stageno_i = g_mdRam.stageno_is;
  util__assign_high(&g_mdRam.actwk[0].xposi, g_mdRam.plxposi_s);
  util__assign_high(&g_mdRam.actwk[0].yposi, g_mdRam.plyposi_s);
  g_mdRam.plring = g_mdRam.plring_s;
  g_mdRam.plring_f2 = g_mdRam.plring_f2_s;
  if (g_mdRam.plresetflag == 0) {
    g_mdRam.plring = 0;
    g_mdRam.plring_f2 = 0;
  }
  g_mdRam.pltime = g_mdRam.pltime_s;
  g_mdRam.pltime.frames = 59;
  --g_mdRam.pltime.seconds;
  g_mdRam.actwk[0].sproffset = g_mdRam.plsproffset_s;
  g_mdRam.actwk[0].actfree.player.colibits = g_mdRam.plcolibits_s;
  g_mdRam.scr_resize_no = g_mdRam.scr_resize_no_s;
  g_mdRam.scralim_down = g_mdRam.scralim_down_s;
  g_mdRam.scralim_n_down = g_mdRam.scralim_down_s;
  util__assign_high(&g_mdRam.scra_h_posit, g_mdRam.scra_h_posit_s);
  util__assign_high(&g_mdRam.scra_v_posit, g_mdRam.scra_v_posit_s);
  if (g_mdRam.watermode != 0) {
    g_mdRam.waterposi = g_mdRam.waterposi_s;
    g_mdRam.waterflag = g_mdRam.waterflag_s;
  }
}


static void playload2(sprite_status* p_actwk) {
  g_mdRam.marker_flag = 0;
  g_mdRam.stageno = g_mdRam.stageno_s2;
  g_mdRam.stageno_i = g_mdRam.stageno_is2;
  util__assign_high(&g_mdRam.actwk[0].xposi, g_mdRam.plxposi_s2);
  util__assign_high(&g_mdRam.actwk[0].yposi, g_mdRam.plyposi_s2);
  g_mdRam.plring = g_mdRam.plring_s2;
  g_mdRam.plring_f2 = g_mdRam.plring_f2_s2;
  g_mdRam.pltime = g_mdRam.pltime_s2;
  g_mdRam.pltime.frames = 59;
  --g_mdRam.pltime.seconds;
  g_mdRam.actwk[0].sproffset = g_mdRam.plsproffset_s2;
  g_mdRam.actwk[0].actfree.player.colibits = g_mdRam.plcolibits_s2;
  g_mdRam.scr_resize_no = g_mdRam.scr_resize_no_s2;
  g_mdRam.scralim_down = g_mdRam.scralim_down_s2;
  g_mdRam.scralim_n_down = g_mdRam.scralim_down_s2;
  util__assign_high(&g_mdRam.scra_h_posit, g_mdRam.scra_h_posit_s2);
  util__assign_high(&g_mdRam.scra_v_posit, g_mdRam.scra_v_posit_s2);
  if (g_mdRam.watermode != 0) {
    g_mdRam.waterposi = g_mdRam.waterposi_s2;
    g_mdRam.waterflag = g_mdRam.waterflag_s2;
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


signed char* savepat[5] = {
  savesp00,
  savesp01,
  savesp02,
  savesp03,
  savesp04
};


static signed char savesp00[26] = { 0, 4, -24, 1, 14, 0, -4, -1, -8, 3, 16, 0, -8, -1, -8, 3, 16, 8, 0, 0, -40, 5, 6, 0, -8, -1 };
static signed char savesp01[20] = { 0, 3, -24, 1, 14, 0, -4, -1, -8, 3, 16, 0, -8, -1, -8, 3, 16, 8, 0, 0 };
static signed char savesp02[8] = { 0, 1, -8, 5, 6, 0, -8, -1 };
static signed char savesp03[8] = { 0, 1, -8, 5, 10, 0, -8, -1 };
static signed char savesp04[26] = { 0, 4, -24, 1, 14, 0, -4, -1, -8, 3, 16, 0, -8, -1, -8, 3, 16, 8, 0, 0, -40, 5, 10, 0, -8, -1 };


static signed char* starpat[3] = {
  starsp00,
  starsp01,
  starsp02
};


static signed char starsp00[8] = { 0, 1, -8, 5, 0, 0, -8, -1 };
static signed char starsp01[8] = { 0, 1, -4, 0, 4, 0, -4, -1 };
static signed char starsp02[8] = { 0, 1, -4, 0, 5, 0, -4, -1 };


void o_starinit(sprite_status* p_actwk) {
  sprite_status* p_new_actwk;
  short cnt = 3;
  unsigned short angle = 0;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite(&p_new_actwk, &slot_cnt);
    if (!created) break;
    p_new_actwk->r_ptr = p_actwk->r_ptr;
    p_new_actwk->patbase = starpat;
    p_new_actwk->sproffset = 1516;
    p_new_actwk->actflg = 4;
    p_new_actwk->r_no = 8;
    short xposi = LONG_HIGH(p_actwk->xposi);
    util__assign_high(&p_new_actwk->xposi, xposi);
    p_new_actwk->actfree.save.parent_xposi = xposi;
    short yposi = LONG_HIGH(p_actwk->yposi) - 48;
    util__assign_high(&p_new_actwk->yposi, yposi);
    p_new_actwk->actfree.save.parent_yposi = yposi;
    p_new_actwk->sprpri = p_actwk->sprpri;
    p_new_actwk->sprhs = 8;
    p_new_actwk->patno = 1;
    p_new_actwk->xspeed = -1024;
    p_new_actwk->yspeed = 0;
    p_actwk->actfree.save.angle = angle;
    angle += 64;
    --cnt;
  } while (cnt != -1);

  void* p_data = &white_star_ring_tiles;
  if (g_sonic3Alone == 0) {
    p_data = &orange_star_ring_tiles;
    short bonus_stage_id = g_mdRam.plring - 20;
    bonus_stage_id /= 15;
    unsigned char bonus_stage_cnt = 2;
    if (g_mdRam.cartridge == 0) {
      bonus_stage_cnt = 3;
    }
    bonus_stage_id %= bonus_stage_cnt;

    switch (bonus_stage_id) {
      case BONUS_STAGE_ROLLING_JUMP:
        p_data = &orange_star_ring_tiles;
        break;
      case BONUS_STAGE_SLOT_MACHINE:
        p_data = &red_star_ring_tiles;
        break;
      case BONUS_STAGE_GUMBALL_MACHINE:
        p_data = &white_star_ring_tiles;
        break;
    }
  }

  Queue_Kos_Module(p_data, 46);
}


void o_star(sprite_status* p_actwk) {
  if (p_actwk->colicnt != 0) {
    if (p_actwk->colicnt & 1) {
      g_mdRam.marker_flag = 2;
      if (g_sonic3Alone != 0) {
        g_mdRam.stageno.zone = ZONE_GUMBALL_MACHINE, g_mdRam.stageno.act = 0;
        g_mdRam.stageno_i.zone = ZONE_GUMBALL_MACHINE, g_mdRam.stageno_i.act = 0;
        g_mdRam.markerno = 0;
        g_mdRam.gameflag = 1;
        g_mdRam.plcddat2_s2 = g_mdRam.actwk[0].cddat2;
        g_mdRam.plresetflag = 1;
        Clear_SpriteRingMem();
      }
      else {
        zone_act bonus_stage_no = { ZONE_ROLLING_JUMP, 0 };
        short bonus_stage_id = g_mdRam.plring_s - 20;
        bonus_stage_id /= 15;
        unsigned char bonus_stage_cnt = 2;
        if (g_mdRam.cartridge == 0) {;
          bonus_stage_cnt = 3;
        }
        bonus_stage_id %= bonus_stage_cnt;

        switch (bonus_stage_id) {
          case BONUS_STAGE_ROLLING_JUMP:
            bonus_stage_no.zone = ZONE_ROLLING_JUMP, bonus_stage_no.act = 0;
            break;
          case BONUS_STAGE_SLOT_MACHINE:
            bonus_stage_no.zone = ZONE_SLOT_MACHINE, bonus_stage_no.act = 0;
            break;
          case BONUS_STAGE_GUMBALL_MACHINE:
            bonus_stage_no.zone = ZONE_GUMBALL_MACHINE, bonus_stage_no.act = 0;
            break;
        }

        g_mdRam.stageno = bonus_stage_no;
        g_mdRam.stageno_i = bonus_stage_no;
        g_mdRam.plring_s = g_mdRam.plring;
        g_mdRam.plring_f2_s = g_mdRam.plring_f2;
        g_mdRam.markerno = 0;
        g_mdRam.gameflag = 1;
        unsigned char cddat2 = g_mdRam.actwk[0].cddat2 & 113;
        g_mdRam.plcddat2_s2 = cddat2;
        g_mdRam.plcddat2_s = cddat2;
        g_mdRam.plresetflag = 1;
        Clear_SpriteRingMem();
      }
    }
    p_actwk->colicnt = 0;
  }
  p_actwk->actfree.save.angle += 10;
  short sin, cos;
  sinset(p_actwk->actfree.save.angle & 0xFF, &sin, &cos);
  sin /= 32;
  cos /= 8;
  short cos_tmp = cos;
  short unknown1 = (p_actwk->actfree.save.angle & 0x3E0) / 32;
  short cnt = 2;
  short sin_add = 0;
  if (unknown1 > 16) {
    cos_tmp = -cos_tmp;
    unknown1 &= 0xF;
  }
  if (unknown1 > 8) {
    unknown1 = -unknown1;
    unknown1 %= 8;
  }

  do {
    unknown1 /= 2;
    if (unknown1 != 0) {
      sin_add += cos_tmp;
    }
    cos_tmp *= 2;
    --cnt;
  }
  while (cnt != -1);

  sin_add /= 16;
  sin += sin_add;
  ++p_actwk->actfree.save.counter;
  short unknown2 = p_actwk->actfree.save.counter;
  int compare_result = -1;
  if (unknown2 == 128) {
    compare_result = 0;
  }
  else if (unknown2 > 128) {
    compare_result = 1;
  }

  switch (compare_result) {
    case 0:
      p_actwk->colino = 216;
      // fall-through
    case 1:
      if (unknown2 <= 384) break;
      unknown2 = -unknown2;
      unknown2 += 512;
      if (unknown2 < 0) {
        frameout(p_actwk);
        return;
      }
      // fall-through
    case -1:
      sin = unknown2 * sin;
      cos = unknown2 * cos;
      sin /= 128;
      cos /= 128;
      break;
  }

  short xposi = p_actwk->actfree.save.parent_xposi + cos;
  util__assign_high(&p_actwk->xposi, xposi);
  short yposi = p_actwk->actfree.save.parent_yposi + sin;
  util__assign_high(&p_actwk->yposi, yposi);
  ++p_actwk->patcnt;
  unsigned char patno = (p_actwk->patcnt & 6) / 2;
  if (patno == 3) {
    patno = 1;
  }
  p_actwk->patno = patno;
  frameoutchkc(p_actwk, LONG_HIGH(p_actwk->xposi));
}
