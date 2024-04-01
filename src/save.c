#include "globals.h"
#include "macros.h"
#include "util.h"
#include "save.h"
#include "004xxxxx.h"
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
  p_actwk->sprpri = 640;
  if (BIT_0_IS_SET(flagwork[p_actwk->actfree.save.flagwork_index - 1])
      || (markerno & 0x7F) >= (p_actwk->userflag1 & 0x7F)) { // unsigned
    SET_BIT_0(flagwork[p_actwk->actfree.save.flagwork_index - 1]);
    p_actwk->mstno = 2;
  }
  savemove(p_actwk);
}


static void savemove(sprite_status* p_actwk) {
  if (edit_r_no == 0) {
    savemove__sub(p_actwk, &actwk[0]);
  }
  savemove2(p_actwk);
}


static void savemove__sub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  if ((markerno & 0x7F) < (p_actwk->userflag1 & 0x7F)) {
    short distance = LONG_HIGH_TO_SHORT(p_actwk->xposi) - LONG_HIGH_TO_SHORT(p_playerwk->xposi) + 8;
    if (util__to_unsigned(distance) >= 16) return; // unsigned
    distance = LONG_HIGH_TO_SHORT(p_actwk->yposi) - LONG_HIGH_TO_SHORT(p_playerwk->yposi) + 64;
    if (util__to_unsigned(distance) >= 104) return; // unsigned
    soundset(99);
    sprite_status* p_new_actwk;
    bool created = Create_New_Sprite(&p_new_actwk);
    if (created) {
      p_new_actwk->r_ptr = &save;
      p_new_actwk->r_no = 6;
      p_new_actwk->actfree.save.parent_xposi = LONG_HIGH_TO_SHORT(p_actwk->xposi);
      p_new_actwk->actfree.save.parent_yposi = LONG_HIGH_TO_SHORT(p_actwk->yposi) - 20;
      p_new_actwk->patbase = p_actwk->patbase;
      p_new_actwk->sproffset = p_actwk->sproffset;
      p_new_actwk->actflg = p_actwk->actflg;
      p_new_actwk->sprhs = 8;
      p_new_actwk->sprvs = 8;
      p_new_actwk->sprpri = 512;
      p_new_actwk->patno = 2;
      p_new_actwk->actfree.save.counter = 32;
      p_new_actwk->actfree.save.parent = p_actwk - actwk;
      bool enough_rings = false;
      if (Sonic_3_alone) {
        enough_rings = plring >= 50;
      }
      else {
        enough_rings = plring >= 20;
      }
      if (enough_rings) {
        o_starinit(p_actwk);
      }
    }
    p_actwk->mstno = 1;
    playsave(p_actwk);
    p_actwk->r_no = 4;
    SET_BIT_0(flagwork[p_actwk->actfree.save.flagwork_index - 1]);
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
    sprite_status* p_sub_actwk = &actwk[p_actwk->actfree.save.parent];
    if (p_sub_actwk->r_ptr == &save) {
      p_sub_actwk->mstno = 2;
      p_sub_actwk->patno = 0;
    }
    frameout(p_actwk);
  }
  else {
    p_actwk->direc1 -= 16;
    short sin, cos;
    sinset(util__to_unsigned(p_actwk->direc1 - 64), &sin, &cos);
    long cos_l = cos * 3072;
    cos_l = LONG_LOW(cos_l) + p_actwk->actfree.save.parent_xposi;
    p_actwk->xposi = SHORT_TO_LONG_HIGH(LONG_LOW(cos_l)) + LONG_LOW(p_actwk->xposi);
    long sin_l = sin * 3072;
    sin_l = LONG_LOW(sin_l) + p_actwk->actfree.save.parent_yposi;
    p_actwk->yposi = SHORT_TO_LONG_HIGH(LONG_LOW(sin_l)) + LONG_LOW(p_actwk->yposi);
    frameoutchk(p_actwk);
  }
}


static void playsave(sprite_status* p_actwk) {
  markerno = p_actwk->userflag1;
  plxposi_s = LONG_HIGH_TO_SHORT(p_actwk->xposi);
  plyposi_s = LONG_HIGH_TO_SHORT(p_actwk->yposi);
  playsave1(p_actwk);
}


void playsave1(sprite_status* p_actwk) {
  markerno_s = markerno;
  stageno_s = stageno;
  stageno_is = stageno_i;
  plsproffset_s = actwk[0].sproffset;
  plcolibits_s = actwk[0].actfree.player.colibits;
  plring_s = plring;
  plring_f2_s = plring_f2;
  pltime_s = pltime;
  scr_resize_no_s = scr_resize_no;
  scralim_down_s = scralim_down;
  scra_h_posit_s = LONG_HIGH_TO_SHORT(scra_h_posit);
  scra_v_posit_s = LONG_HIGH_TO_SHORT(scra_v_posit);
  waterposi_s = waterposi;
  waterflag_s = waterflag;
}


void playsave2(sprite_status* p_actwk) {
  markerno_s2 = markerno;
  stageno_s2 = stageno;
  stageno_is2 = stageno_i;
  plxposi_s2 = LONG_HIGH_TO_SHORT(p_actwk->xposi);
  plyposi_s2 = LONG_HIGH_TO_SHORT(p_actwk->yposi);
  plsproffset_s2 = actwk[0].sproffset;
  plcolibits_s2 = actwk[0].actfree.player.colibits;
  plring_s2 = plring;
  plring_f2_s2 = plring_f2;
  pltime_s2 = pltime;
  scr_resize_no_s2 = scr_resize_no;
  scralim_down_s2 = scralim_down;
  scra_h_posit_s2 = LONG_HIGH_TO_SHORT(scra_h_posit);
  scra_v_posit_s2 = LONG_HIGH_TO_SHORT(scra_v_posit);
  waterposi_s2 = waterposi;
  waterflag_s2 = waterflag;
  plcddat2_s2 = actwk[0].cddat2;
}


void playload(sprite_status* p_actwk) {
  if (marker_flag != 0) {
    playload2(p_actwk);
    return;
  }
  markerno = markerno_s;
  stageno = stageno_s;
  stageno_i = stageno_is;
  actwk[0].xposi = SHORT_TO_LONG_HIGH(plxposi_s) + LONG_LOW(actwk[0].xposi);
  actwk[0].yposi = SHORT_TO_LONG_HIGH(plyposi_s) + LONG_LOW(actwk[0].yposi);
  plring = plring_s;
  plring_f2 = plring_f2_s;
  if (plresetflag == 0) {
    plring = 0;
    plring_f2 = 0;
  }
  pltime = pltime_s;
  pltime = 59 << 24 | pltime & 0x00FFFFFF;
  pltime = (pltime & 0x00FF0000) - (1 << 16) | pltime & 0xFF00FFFF;
  actwk[0].sproffset = sproffset_s;
  actwk[0].actfree.player.colibits = colibits_s;
  scr_resize_no = scr_resize_no_s;;
  scralim_down = scralim_down_s;
  scralim_n_down = scralim_down_s;
  scra_h_posit = SHORT_TO_LONG_HIGH(scra_h_posit_s) + LONG_LOW(scra_v_posit);
  scra_v_posit = SHORT_TO_LONG_HIGH(scra_v_posit_s) + LONG_LOW(scra_h_posit);
  if (watermode != 0) {
    waterposi = waterposi_s;
    waterflag = waterflag_s;
  }
}


static void playload2(sprite_status* p_actwk) {
  marker_flag = 0;
  stageno = stageno_s2;
  stageno_i = stageno_is2;
  actwk[0].xposi = SHORT_TO_LONG_HIGH(plxposi_s2) + LONG_LOW(actwk[0].xposi);
  actwk[0].yposi = SHORT_TO_LONG_HIGH(plyposi_s2) + LONG_LOW(actwk[0].yposi);
  plring = plring_s2;
  plring_f2 = plring_f2_s2;
  pltime = pltime_s2;
  pltime = 59 << 24 | pltime & 0x00FFFFFF;
  pltime = (pltime & 0x00FF0000) - (1 << 16) | pltime & 0xFF00FFFF;
  actwk[0].sproffset = plsproffset_s2;
  actwk[0].actfree.player.colibits = plcolibits_s2;
  scr_resize_no = scr_resize_no_s2;
  scralim_down = scralim_down_s2;
  scralim_n_down = scralim_down_s2;
  scra_h_posit = SHORT_TO_LONG_HIGH(scra_h_posit_s2) + LONG_LOW(scra_v_posit);
  scra_v_posit = SHORT_TO_LONG_HIGH(scra_v_posit_s2) + LONG_LOW(scra_h_posit);
  if (watermode != 0) {
    waterposi = waterposi_s2;
    waterflag = waterflag_s2;
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
    bool created = Create_New_Sprite(&p_new_actwk);
    if (!created) break;
    p_new_actwk->r_ptr = p_actwk->r_ptr;
    p_new_actwk->patbase = starpat;
    p_new_actwk->sproffset = 1516;
    p_new_actwk->actflg = 4;
    p_new_actwk->r_no = 8;
    short xposi = LONG_HIGH_TO_SHORT(p_actwk->xposi);
    p_new_actwk->xposi = SHORT_TO_LONG_HIGH(xposi) + LONG_LOW(p_new_actwk->xposi);
    p_new_actwk->actfree.save.parent_xposi = xposi;
    short yposi = LONG_HIGH_TO_SHORT(p_actwk->yposi) - 48;
    p_new_actwk->yposi = SHORT_TO_LONG_HIGH(yposi) + LONG_LOW(p_new_actwk->yposi);
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
  if (!Sonic_3_alone) {
    p_data = &orange_star_ring_tiles;
    short bonus_stage_id = plring - 20;
    bonus_stage_id /= 15;
    unsigned char bonus_stage_cnt = 2;
    if (cartridge == 0) {
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
      marker_flag = 2;
      if (Sonic_3_alone) {
        stageno.zone = ZONE_GUMBALL_MACHINE, stageno.act = 0;
        stageno_i.zone = ZONE_GUMBALL_MACHINE, stageno_i.act = 0;
        markerno = 0;
        gameflag = 1;
        plcddat2_s2 = actwk[0].cddat2;
        plresetflag = 1;
        Clear_SpriteRingMem();
      }
      else {
        zone_act bonus_stage_no = { ZONE_ROLLING_JUMP, 0 };
        short bonus_stage_id = plring_s - 20;
        bonus_stage_id /= 15;
        unsigned char bonus_stage_cnt = 2;
        if (cartridge == 0) {;
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

        stageno = bonus_stage_no;
        stageno_i = bonus_stage_no;
        plring_s = plring;
        plring_f2_s = plring_f2;
        markerno = 0;
        gameflag = 1;
        unsigned char cddat2 = actwk[0].cddat2 & 113;
        plcddat2_s2 = cddat2;
        plcddat2_s = cddat2;
        plresetflag = 1;
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
    case 1:
      if (unknown2 <= 384) break;
      unknown2 = -unknown2;
      unknown2 += 512;
      if (unknown2 < 0) {
        frameout(p_actwk);
        return;
      }
    case -1:
      sin = unknown2 * sin;
      cos = unknown2 * cos;
      sin /= 128;
      cos /= 128;
      break;
  }

  p_actwk->xposi = SHORT_TO_LONG_HIGH(p_actwk->actfree.save.parent_xposi + cos) + LONG_LOW(p_actwk->xposi);
  p_actwk->yposi = SHORT_TO_LONG_HIGH(p_actwk->actfree.save.parent_yposi + sin) + LONG_LOW(p_actwk->yposi);
  ++p_actwk->patcnt;
  unsigned char patno = (p_actwk->patcnt & 6) / 2;
  if (patno == 3) {
    patno = 1;
  }
  p_actwk->patno = patno;
  frameoutchkc(p_actwk, LONG_HIGH_TO_SHORT(p_actwk->xposi));
}
