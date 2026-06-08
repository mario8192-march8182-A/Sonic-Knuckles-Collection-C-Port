#include "edit.h"
#include "edittbl.h"
#include <stdbool.h>
#include "types/editdata.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "types/spritestatushandler.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "action.h"
#include "actset.h"
#include "score.h"
#include "objects/item.h"
#include "objects/playsub.h"
static void editinit(SKC_sprite_status* p_actwk);
static void editmove(SKC_sprite_status* p_actwk);
static void editwalk(SKC_sprite_status* p_actwk, SKC_edit_data* p_data);
static void editpatchg(SKC_sprite_status* p_actwk, SKC_edit_data* p_data);
static SKC_edit_data* edittbl[24][2];
static SKC_edit_data edittbl000;
static SKC_edit_data edittbl001;
static SKC_edit_data edittbl010;
static SKC_edit_data edittbl020;
static SKC_edit_data edittbl030;
static SKC_edit_data edittbl040;
static SKC_edit_data edittbl041;
static SKC_edit_data edittbl050;
static SKC_edit_data edittbl051;
static SKC_edit_data edittbl060;
static SKC_edit_data edittbl061;
static SKC_edit_data edittbl070;
static SKC_edit_data edittbl080;
static SKC_edit_data edittbl081;
static SKC_edit_data edittbl090;
static SKC_edit_data edittbl091;
static SKC_edit_data edittbl0a0;
static SKC_edit_data edittbl0b0;
static SKC_edit_data edittbl0b1;
static SKC_edit_data edittbl0c0;
static SKC_edit_data edittbl0c1;
static SKC_edit_data edittbl0d0;
static SKC_edit_data edittbl0e0;
static SKC_edit_data edittbl0f0;
static SKC_edit_data edittbl100;
static SKC_edit_data edittbl110;
static SKC_edit_data edittbl120;
static SKC_edit_data edittbl140;
static SKC_edit_data edittbl160;
static SKC_edit_data edittbl170;

extern sonic3_ram g_ram;


void edit(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler edit_move_tbl[2] = {
    &editinit,
    &editmove
  };

  edit_move_tbl[g_ram.editmode >> 8](p_actwk);
}


static void editinit(SKC_sprite_status* p_actwk) {
  g_ram.editmode += 0x200;
  g_ram.plpatbase = p_actwk->patbase;
  if (p_actwk->r_no < 6) {
    g_ram.plsproffset = p_actwk->sproffset;
  }
  short yposi = (unsigned short)fp16_get_integer(g_ram.actwk[0].yposi) & g_ram.scrc_v;
  fp16_set_integer(&g_ram.actwk[0].yposi, yposi);
  g_ram.scra_v_posit = (g_ram.scra_v_posit >> 16 & g_ram.scrc_v) << 16 | g_ram.scra_v_posit & 0x0000FFFF;
  g_ram.pl_scr_lock_flag = 0;
  g_ram.watercoliflag = 0;
  if (p_actwk->u.play.cddat.underwater == 1) {
    p_actwk->u.play.cddat.underwater = 0;
    plairset(p_actwk);
    g_ram.plmaxspdwk = 0x600;
    g_ram.pladdspdwk = 0xC;
    g_ram.plretspdwk = 0x80;
  }
  p_actwk->patno = 0;
  p_actwk->mstno = 0;
  SKC_edit_data* p_data = edittbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
  if (p_data->cnt <= g_ram.editno) {
    g_ram.editno = 0;
  }
  editpatchg(p_actwk, p_data);
  g_ram.edittimer = 12;
  g_ram.edit_spd = 1;
  editmove(p_actwk);
}


static void editmove(SKC_sprite_status* p_actwk) {
  editwalk(p_actwk, edittbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)]);
  actionsub(p_actwk);
}


static void editwalk(SKC_sprite_status* p_actwk, SKC_edit_data* p_data) {
  if (!are_any_dir_buttons_used(g_ram.swdata1.pressed) && !are_any_dir_buttons_used(g_ram.swdata1.down)) {
    g_ram.edittimer = 12;
    g_ram.edit_spd = 15;
  }
  else {
    if (!are_any_dir_buttons_used(g_ram.swdata1.pressed) && are_any_dir_buttons_used(g_ram.swdata1.down)) {
      --g_ram.edittimer;
      if (g_ram.edittimer == 0) {
        g_ram.edittimer = 1;
        ++g_ram.edit_spd;
        if (g_ram.edit_spd == 0) {
          g_ram.edit_spd = -1;
        }
      }
    }
    long edit_spd = (g_ram.edit_spd + 1) * 0x40000;
    long xposi = p_actwk->xposi;
    long yposi = p_actwk->yposi;
    if (g_ram.swdata1.down.u == 1) {
      yposi -= edit_spd;
      long scralim_up = g_ram.scralim_up << 16;
      if (yposi < scralim_up) {
        yposi = scralim_up;
      }
    }
    if (g_ram.swdata1.down.d == 1) {
      yposi += edit_spd;
      long scralim_n_down = g_ram.scralim_n_down + 223 << 16;
      if (yposi >= scralim_n_down) {
        yposi = scralim_n_down;
      }
    }
    if (g_ram.swdata1.down.l == 1) {
      xposi -= edit_spd;
      if (xposi < 0) {
        xposi = 0;
      }
    }
    if (g_ram.swdata1.down.r == 1) {
      xposi += edit_spd;
    }
    p_actwk->xposi = xposi;
    p_actwk->yposi = yposi;
  }
  if (g_ram.swdata1.down.a == 1) {
    if (g_ram.swdata1.pressed.c == 1) {
      if (g_ram.editno-- == 0) {
        g_ram.editno = p_data->cnt - 1;
      }
    }
    else if (g_ram.swdata1.pressed.a == 1) {
      ++g_ram.editno;
      if (p_data->cnt <= g_ram.editno) {
        g_ram.editno = 0;
      }
    }
    editpatchg(p_actwk, p_data);
  }
  else {
    if (g_ram.swdata1.pressed.c == 1) {
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
        fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
        result.actwk_ptr->actflg = p_actwk->actflg;
        result.actwk_ptr->u.obj.cddat.right = p_actwk->u.play.cddat.left;
        result.actwk_ptr->u.obj.cddat.down = p_actwk->u.play.cddat.jump;
        result.actwk_ptr->u.obj.cddat.wrt = p_actwk->u.play.cddat.ball;
        result.actwk_ptr->u.obj.cddat.plride = p_actwk->u.play.cddat.ride;
        result.actwk_ptr->u.obj.cddat.pl2ride = p_actwk->u.play.cddat.ballj;
        result.actwk_ptr->u.obj.cddat.plpush = p_actwk->u.play.cddat.push;
        result.actwk_ptr->u.obj.cddat.pl2push = p_actwk->u.play.cddat.underwater;
        result.actwk_ptr->u.obj.userflag = p_data->items[g_ram.editno].userflag;
        result.actwk_ptr->r_ptr = p_data->items[g_ram.editno].r_ptr;
        if (result.actwk_ptr->r_ptr == &item) {
          result.actwk_ptr->u.obj.userflag = 9;
        }
        return;
      }
    }
    if (g_ram.swdata1.pressed.b == 1) {
      g_ram.editmode = 0;
      scoreinit();
      g_ram.plscore_f = 1;
      g_ram.plring_f = 0x80;
      g_ram.actwk[0].patbase = g_ram.plpatbase;
      g_ram.actwk[0].sproffset = g_ram.plsproffset;
      g_ram.actwk[0].mstno = 0;
      fp16_set_fraction(&g_ram.actwk[0].xposi, 0);
      fp16_set_fraction(&g_ram.actwk[0].yposi, 0);
      g_ram.actwk[0].u.play.control_bitfield = 0;
      g_ram.actwk[0].u.play.spindash_flag = 0;
      g_ram.actwk[0].xspeed = 0;
      g_ram.actwk[0].yspeed = 0;
      g_ram.actwk[0].mspeed = 0;
      g_ram.actwk[0].u.play.cddat.jump = 1;
      g_ram.actwk[0].u.play.cddat.ball = 0;
      g_ram.actwk[0].u.play.cddat.ride = 0;
      g_ram.actwk[0].u.play.cddat.ballj = 0;
      g_ram.actwk[0].u.play.cddat.push = 0;
      g_ram.actwk[0].u.play.cddat.underwater = 0;
      g_ram.actwk[0].u.play.cddat.unused7 = 0;
      g_ram.actwk[0].r_no = 2;
      g_ram.actwk[0].sprvsize = 19;
      g_ram.actwk[0].sprhsize = 9;
    }
  }
}


static void editpatchg(SKC_sprite_status* p_actwk, SKC_edit_data* p_data) {
  p_actwk->patbase = p_data->items[g_ram.editno].patbase;
  p_actwk->sproffset = p_data->items[g_ram.editno].sproffset;
  p_actwk->patno = p_data->items[g_ram.editno].patno;
}


static SKC_edit_data* edittbl[24][2] = {
  { &edittbl000, &edittbl001 },
  { &edittbl010, &edittbl010 },
  { &edittbl020, &edittbl020 },
  { &edittbl030, &edittbl030 },
  { &edittbl040, &edittbl041 },
  { &edittbl050, &edittbl051 },
  { &edittbl060, &edittbl061 },
  { &edittbl070, &edittbl070 },
  { &edittbl080, &edittbl081 },
  { &edittbl090, &edittbl091 },
  { &edittbl0a0, &edittbl0a0 },
  { &edittbl0b0, &edittbl0b1 },
  { &edittbl0c0, &edittbl0c1 },
  { &edittbl0d0, &edittbl0d0 },
  { &edittbl0e0, &edittbl0e0 },
  { &edittbl0f0, &edittbl0f0 },
  { &edittbl100, &edittbl100 },
  { &edittbl110, &edittbl110 },
  { &edittbl120, &edittbl120 },
  { &edittbl170, &edittbl170 },
  { &edittbl140, &edittbl140 },
  { &edittbl170, &edittbl170 },
  { &edittbl160, &edittbl160 },
  { &edittbl170, &edittbl170 }
};


static SKC_edit_data edittbl000 = {
  29,
  {
    { &ring,      ringpat,      0xA6BC,  0, 0x00 },
    { &item,      itempat,      0x04C4,  0, 0x06 },
    { &colichg,   colichgpat,   0x26BC,  1, 0x09 },
    { &colichg,   colichgpat,   0x26BC,  5, 0x0D },
    { &sjump,     banepat,      0x04A4,  0, 0x81 },
    { &sjump,     banepat,      0x04B4,  3, 0x90 },
    { &sjump,     banepat,      0x04A4,  6, 0xA0 },
    { &toge,      togepat,      0x049C,  0, 0x00 },
    { &iwa,       iwapat,       0x2333,  0, 0x04 },
    { &iwa,       iwapat,       0x2333,  1, 0x13 },
    { &iwa,       iwapat,       0x2333,  2, 0x23 },
    { &break_,    break000pat,  0x4001,  0, 0x00 },
    { &rope,      ropepat,      0x041B, 33, 0x08 },
    { &ropeswing, ropepat,      0x041B, 33, 0x0F },
    { &falltree,  falltreepat1, 0x43CF,  0, 0x07 },
    { &sai00,     sai00pat,     0x2500,  0, 0x00 },
    { &hana00,    hana00pat,    0x252A,  0, 0x00 },
    { &saru00,    saru00pat,    0x2548,  0, 0x10 },
    { &save,      savepat,      0x05EC,  0, 0x01 },
    //{ &awa,       awapat,       0x845C, 19, 0x81 },
    { &bryuka,    bryukapat,    0x4001,  0, 0x00 },
    { &bgsprz,    bgsprzpat,    0xC333,  0, 0x00 },
    { &bgsprz,    bgsprzpat,    0xC333,  1, 0x11 },
    { &bgsprz,    bgsprzpat,    0xC333,  0, 0x20 },
    { &bgsprz,    bgsprzpat,    0xC333,  1, 0x31 },
    { &bgsprz,    bgsprzpat,    0xC333,  0, 0x40 },
    { &bgsprz,    bgsprzpat,    0xC333,  1, 0x51 },
    { &bgsprz,    bgsprzpat,    0xC333,  0, 0x60 },
    //{ &dai,       dai00pat,     0x43F7,  0, 0x20 }
  }
};
static SKC_edit_data edittbl001 = {
  37,
  {
    { &sjump,     banepat,      0x04A4,  0, 0x81 },
    { &sjump,     banepat,      0x04B4,  3, 0x90 },
    { &sjump,     banepat,      0x04A4,  6, 0xA0 },
    { &toge,      togepat,      0x049C,  0, 0x00 },
    { &iwa,       iwapat2,      0x42E9,  0, 0x04 },
    { &iwa,       iwapat2,      0x42E9,  1, 0x13 },
    { &iwa,       iwapat2,      0x42E9,  2, 0x23 },
    { &break_,    break001pat,  0x4001,  0, 0x00 },
    { &brkabe,    brkabepat,    0x4001,  0, 0x00 },
    { &appeariwa, appeariwapat, 0x4001,  5, 0x07 },
    { &bryuka,    bryukapat2,   0x4001,  0, 0x00 },
    //{ &rollhashi, rollhashipat, 0x42E9,  5, 0x50 },
    { &brhashi,   brhashipat,   0x42E9,  0, 0x08 },
    { &falltree,  falltreepat,  0x42E9,  0, 0x07 },
    { &togetree,  togetreepat,  0x42E9,  8, 0x00 },
    { &bgspr,     bgsprpat,     0x42E9,  0, 0x00 },
    { &bgspr,     bgsprpat,     0x42E9,  1, 0x01 },
    { &bgspr,     bgsprpat,     0x42E9,  2, 0x02 },
    { &bgspr,     bgsprpat,     0x4001,  3, 0x03 },
    { &bgspr,     bgsprpat,     0x6001,  4, 0x04 },
    { &bgsprp,    bgsprppat,    0x62E9,  0, 0x00 },
    { &bgsprp,    bgsprppat,    0x62E9,  5, 0x01 },
    { &rope,      ropepat,      0x041B, 33, 0x88 },
    { &ropeswing, ropepat,      0x041B, 33, 0x0F },
    { &evhashi,   evhashipat,   0x42E9,  1, 0x00 },
    { &switch_,   switchpat,    0x0456,  2, 0x10 },
    { &sai00,     sai00pat,     0x2500,  0, 0x00 },
    { &hana00,    hana00pat,    0x252A,  0, 0x00 },
    { &saru00,    saru00pat,    0x2548,  0, 0x00 },
    { &snak00,    snak00pat,    0x255F,  0, 0x00 },
    { &save,      savepat,      0x05EC,  0, 0x01 },
    //{ &awa,       awapat,       0x845C, 19, 0x81 },
    //{ &dai,       dai00pat,     0x4440,  0, 0x20 }
  }
};
static SKC_edit_data edittbl010 = {
  54,
  {
    { &ring,      ringpat,      0xA6BC,  0, 0x00 },
    { &item,      itempat,      0x04C4,  0, 0x06 },
    { &colichg,   colichgpat,   0x26BC,  1, 0x09 },
    { &colichg,   colichgpat,   0x26BC,  5, 0x0D },
    { &sjump,     banepat,      0x04A4,  0, 0x81 },
    { &sjump,     banepat,      0x04B4,  3, 0x90 },
    { &sjump,     banepat,      0x04A4,  6, 0xA0 },
    { &toge,      togepat,      0x049C,  0, 0x00 },
    //{ &hdai01,    hdai01pat,    0x2539,  0, 0x00 },
    //{ &fugu01,    fugu01pat,    0x2559,  0, 0x20 },
    //{ &fly01,     fly01pat,     0x244C,  0, 0x00 },
    //{ &fish01,    fish01pat,    0x254D,  0, 0x00 },
    //{ &yado01,    yado01pat,    0x2500,  0, 0x00 },
    //{ &shak01,    shak01pat,    0x2539,  0, 0x00 },
    { &switch_,   switch01pat,  0x2426,  2, 0x20 },
    { &bar,       barpat,       0x43CA,  0, 0x00 },
    { &bar,       barpat,       0x43CA,  4, 0x80 },
    //{ &fan,       fanpat,       0x240B,  0, 0x16 },
    //{ &fan,       fanpat,       0x240B,  1, 0x4C },
    //{ &fan2,      fan2pat,      0x2500,  0, 0x00 },
    //{ &dashgear,  dashgearpat,  0x23E4,  0, 0x00 },
    //{ &wpillar,   wpillarpat,   0x4500,  0, 0x00 },
    //{ &wpillar,   wpillarpat,   0x4500,  1, 0x01 },
    //{ &fan,       fanpat,       0x240B,  1, 0xFC },
    //{ &door,      doorpat,      0x43D4,  0, 0x00 },
    //{ &cabletoge, cabletogepat, 0x243E,  0, 0x00 },
    { &block,     blockpat,     0x43D4,  0, 0x00 },
    { &break2,    break010pat,  0xC001,  0, 0x08 },
    { &break2,    break010pat,  0xC001,  3, 0x18 },
    { &break2,    break010pat,  0xC001,  6, 0x28 },
    { &break2,    break010pat,  0xC001,  9, 0x38 },
    { &bgspr,     bgsprpat,     0xC001,  6, 0x06 },
    { &bgspr,     bgsprpat,     0xC001,  7, 0x07 },
    { &bgspr,     bgsprpat,     0x4001,  8, 0x08 },
    { &bgspr,     bgsprpat,     0xC001,  9, 0x09 },
    { &bgspr,     bgsprpat,     0xC001, 10, 0x0A },
    //{ &awa,       awapat,       0x845C, 19, 0x81 },
    //{ &dai,       dai01pat,     0x441D,  0, 0x14 },
    //{ &dai01,     dai01pat,     0x0028,  1, 0x00 },
    //{ &dai,       dai01pat,     0x441D,  0, 0x17 },
    //{ &rolldai01, rolldai01pat, 0x4040,  0, 0x01 },
    //{ &rolldai01, rolldai01pat, 0x4040,  0, 0x02 },
    { &bgspr,     bgsprpat,     0xC368, 15, 0x0F },
    { &bgspr,     bgsprpat,     0xC379, 16, 0x10 },
    { &bgspr,     bgsprpat,     0xC399, 17, 0x11 },
    { &bgspr,     bgsprpat,     0xC3A4, 18, 0x12 },
    //{ &drip,      drippat,      0x235C,  0, 0x40 },
    //{ &shibuki,   shibukipat,   0x43B2,  0, 0x00 },
    { &bgspr,     bgsprpat,     0x4038, 19, 0x13 },
    //{ &hashi,     hashi01pat,   0x4038,  0, 0x90 },
    { &itaicoli,  scolipat,     0x86BC,  0, 0x00 },
    { &killcoli,  scolipat,     0x86BC,  0, 0x00 },
    { &brkabe,    brkabe01pat,  0x6001,  0, 0x00 },
    { &brkabe,    brkabe01pat,  0x4350,  2, 0x02 }
  }
};
static SKC_edit_data edittbl020 = {
  36,
  {
    { &ring,      ringpat,      0xA6BC,  0, 0x00 },
    { &item,      itempat,      0x04C4,  0, 0x06 },
    { &colichg,   colichgpat,   0x26BC,  1, 0x09 },
    { &colichg,   colichgpat,   0x26BC,  5, 0x0D },
    { &sjump,     banepat,      0x04A4,  0, 0x80 },
    { &sjump,     banepat,      0x04B4,  3, 0x90 },
    { &sjump,     banepat,      0x04A4,  6, 0xA0 },
    { &sjump,     banepat,      0x0478,  7, 0x30 },
    { &sjump,     banepat,      0x0478, 10, 0x40 },
    { &toge,      togepat,      0x049C,  0, 0x00 },
    { &toge,      togepat,      0x0494,  4, 0x40 },
    //{ &bs02m0,    bs02m0pat,    0x254F,  0, 0x00 },
    //{ &fugu02,    fugu02pat,    0x2500,  0, 0x00 },
    //{ &hari02,    hari02pat,    0x2530,  0, 0x00 },
    //{ &bata02,    bata02pat,    0x254F,  0, 0x00 },
    { &bgspr,     bgsprpat,     0x4451, 11, 0x0B },
    { &bgspr,     bgsprpat,     0x4451, 12, 0x0C },
    { &bgspr,     bgsprpat,     0x4451, 13, 0x0D },
    { &bgspr,     bgsprpat,     0x4451, 14, 0x0E },
    { &break2,    break020pat,  0x4001,  0, 0x08 },
    { &break2,    break020pat,  0x4001,  3, 0x18 },
    { &break2,    break020pat,  0x4001,  6, 0x28 },
    { &brkabe,    brkabe02pat,  0x4001,  0, 0x00 },
    //{ &dai,       dai02pat,     0x4001,  0, 0x04 },
    //{ &airhammer, airhammerpat, 0x4001,  0, 0x0A },
    //{ &turndai,   turndaipat,   0x435F,  1, 0x00 },
    //{ &tekyu,     tekyupat,     0x235F,  1, 0x00 },
    //{ &tekyu,     tekyupat,     0x235F,  2, 0x01 },
    //{ &Lmask,     maskpat,      0xA3FF,  6, 0x00 },
    //{ &mpillar,   mpillarpat,   0x4001,  0, 0x00 },
    //{ &moveyuka,  moveyukapat,  0x4001,  1, 0x11 },
    //{ &rswitch,   rswitchpat,   0x235F,  0, 0x01 },
    //{ &rollup,    rolluppat,    0x235F,  0, 0x20 },
    //{ &koma,      komapat,      0x235F,  0, 0x00 },
    //{ &komadai,   komapat,      0x43FF,  2, 0x00 },
    { &save,      savepat,      0x05EC,  0, 0x01 }
  }
};
static SKC_edit_data edittbl030 = {
  36,
  {
    { &ring,     ringpat,     0xA6BC,  0, 0x00 },
    { &item,     itempat,     0x04C4,  0, 0x06 },
    { &colichg,  colichgpat,  0x26BC,  1, 0x09 },
    { &colichg,  colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,    banepat,     0x04A4,  0, 0x81 },
    { &sjump,    banepat,     0x04B4,  3, 0x90 },
    { &sjump,    banepat,     0x04A4,  6, 0xA0 },
    { &toge,     togepat,     0x049C,  0, 0x00 },
    { &toge,     togepat,     0x0494,  4, 0x40 },
    //{ &shel03,   shel03pat,   0x2500,  0, 0x00 },
    //{ &elec03,   elec03pat,   0x2524,  0, 0x00 },
    //{ &bat03,    bat03pat,    0x2552,  0, 0x00 },
    //{ &door,     doorpat,     0x4416,  1, 0x01 },
    //{ &bobin,    bobinpat,    0x4364,  0, 0x00 },
    //{ &cannon,   cannonpat,   0x4374,  9, 0x00 },
    //{ &elev03,   elev03pat,   0x43BE,  0, 0x00 },
    //{ &lid,      lidpat,      0x43F0,  0, 0x00 },
    //{ &light,    lightpat,    0x4404,  0, 0x00 },
    { &magnet,   magnetpat,   0x43E8,  0, 0x80 },
    //{ &rolldai,  rolldaipat,  0x438E,  0, 0x00 },
    //{ &door,     doorhpat,    0x4416,  0, 0x80 },
    //{ &bobin,    bobinpat,    0x4364,  0, 0x80 },
    //{ &bobin,    bobinpat,    0x4364,  0, 0x2B },
    //{ &bobin,    bobinpat,    0x4364,  0, 0xD5 },
    //{ &baloon,   baloonpat,   0x0351,  0, 0x00 },
    //{ &baloon,   baloonpat,   0x0351,  5, 0x01 },
    //{ &baloon,   baloonpat,   0x0351, 10, 0x02 },
    //{ &baloon,   baloonpat,   0x0351, 15, 0x03 },
    //{ &baloon,   baloonpat,   0x0351, 20, 0x04 },
    { &switch_,  switch03pat, 0x441A,  2, 0x00 },
    { &brkabe,   brkabe03pat, 0x4420,  0, 0x00 },
    { &brkabe,   brkabe03pat, 0x4420,  2, 0x02 },
    //{ &rollpipe, ringpat,     0x86BC,  0, 0x00 },
    //{ &awa,      awapat,      0x845C, 19, 0x81 },
    { &bryuka,   bryukapat3,  0x4430,  0, 0x01 },
    //{ &rolldai,  rolldaipat,  0x438E,  0, 0x49 }
  }
};
static SKC_edit_data edittbl040 = {
  49,
  {
    { &ring,    ringpat,     0xA6BC,  0, 0x00 },
    { &item,    itempat,     0x04C4,  0, 0x06 },
    { &colichg, colichgpat,  0x26BC,  1, 0x09 },
    { &colichg, colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,   banepat,     0x04A4,  0, 0x81 },
    { &sjump,   banepat,     0x04B4,  3, 0x90 },
    { &sjump,   banepat,     0x04A4,  6, 0xA0 },
    { &toge,    togepat,     0x0200,  0, 0x03 },
    { &betl04,  betl04_pt,   0x2506,  0, 0x80 },
    { &mous04,  mous04_pt,   0x252E,  0, 0x00 },
    { &mous04,  mous04_pt,   0x252E,  0, 0x02 },
    { &mous04,  mous04_pt,   0x252E,  0, 0x04 },
    { &swit04,  obox04pat,   0x0000,  5, 0x00 },
    { &obox04,  obox04pat,   0x0000,  0, 0x00 },
    { &obox04,  obox04pat,   0x0000,  0, 0x01 },
    { &obox04,  obox04pat,   0x0000,  0, 0x02 },
    //{ &Obj_FBZFloatingPlatform, DAT_007ce88e, 0x2383, 0, 0x10 },
    //{ &Obj_FBZFloatingPlatform, DAT_007ce88e, 0x2383, 0, 0x30 },
    //{ &Obj_FBZFloatingPlatform, DAT_007ce88e, 0x2383, 0, 0x40 },
    //{ &Obj_FBZChainLink, DAT_007cfadc, 0x4379, 0, 0x1A },
    { &bgspr,   bgsprpat,    0x4379, 39, 0x27 },
    { &bgspr,   bgsprpat,    0x4379, 40, 0x28 },
    { &bgspr,   bgsprpat,    0x4379, 41, 0x29 },
    { &bgspr,   bgsprpat,    0x4379, 42, 0x2A },
    { &bgspr,   bgsprpat,    0x2443, 43, 0x2B },
    //{ &Obj_FBZMagneticSpikeBall, DAT_007d0148, 0x2443, 0, 0x00 },
    //{ &Obj_FBZMagneticSpikeBall, DAT_007d0148, 0xA443, 1, 0x80 },
    //{ &Obj_FBZMagneticSpikeBall, DAT_007d0148, 0xA442, 5, 0x81 },
    //{ &Obj_FBZMagneticPlatform, DAT_007d07e3, 0x2443, 4, 0x10 },
    { &bryuka,  bryukapat4,  0x243A,  0, 0x01 },
    //{ &Obj_FBZBentPipe, LAB_007d0f33, 0x246B, 0, 0x00 },
    //{ &Obj_FBZBentPipe, LAB_007d0f33, 0x246B, 1, 0x01 },
    //{ &Obj_FBZBentPipe, LAB_007d0f33, 0x246B, 2, 0x02 },
    //{ &Obj_FBZRotatingPlatform, DAT_007d143f, 0x246B, 0, 0x00 },
    //{ &Obj_FBZDEZPlayerLauncher, DAT_007d1820, 0x23B5, 0, 0x00 },
    //{ &Obj_FBZDisappearingPla, DAT_007d1b34, 0x23BA, 0, 0x00 },
    //{ &Obj_FBZScrewDoor, DAT_007d2014, 0x23D2, 0, 0x00 },
    //{ &Obj_FBZScrewDoor, DAT_007d2014, 0x23D2, 4, 0x20 },
    //{ &Obj_FBZScrewDoor, DAT_007d2014, 0x23D2, 8, 0x40 },
    { &switch_, switchpat,   0x0500,  2, 0x00 },
    //{ &Obj_FBZPropeller, DAT_007d2a08, 0x22E5, 0, 0x00 },
    //{ &Obj_FBZPiston, DAT_007d2cfc, 0x231B, 0, 0x34 },
    //{ &Obj_FBZPlatformBlocks, DAT_007d2fd7, 0x440D, 1, 0x14 },
    //{ &Obj_FBZMissileLauncher, DAT_007d3933, 0xA32B, 0, 0x02 },
    //{ &Obj_FBZWallMissile, DAT_007d3933, 0x232B, 4, 0x10 },
    { &break2,  break041pat, 0x4001,  0, 0x08 },
    //{ &Obj_FBZMine, DAT_007d3e52, 0x040A, 0, 0x00 },
    //{ &Obj_FBZFlamethrower, DAT_007d4cfe, 0x041D, 1, 0x00 },
    //{ &Obj_FBZFlamethrower, DAT_007d4cfe, 0x041D, 3, 0xC0 }
  }
};
static SKC_edit_data edittbl041 = {
  48,
  {
    { &ring,    ringpat,     0xA6BC,  0, 0x00 },
    { &item,    itempat,     0x04C4,  0, 0x06 },
    { &colichg, colichgpat,  0x26BC,  1, 0x09 },
    { &colichg, colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,   banepat,     0x04A4,  0, 0x81 },
    { &sjump,   banepat,     0x04B4,  3, 0x90 },
    { &sjump,   banepat,     0x04A4,  6, 0xA0 },
    { &toge,    togepat,     0x0200,  0, 0x03 },
    { &betl04,  betl04_pt,   0x2506,  0, 0x80 },
    { &mous04,  mous04_pt,   0x252E,  0, 0x00 },
    { &mous04,  mous04_pt,   0x252E,  0, 0x02 },
    { &mous04,  mous04_pt,   0x252E,  0, 0x04 },
    { &swit04,  obox04pat,   0x0000,  5, 0x00 },
    { &obox04,  obox04pat,   0x0000,  0, 0x00 },
    { &obox04,  obox04pat,   0x0000,  0, 0x01 },
    { &obox04,  obox04pat,   0x0000,  0, 0x02 },
    //{ &Obj_FBZFloatingPlatform, DAT_007ce88e, 0x2383, 0, 0x10 },
    //{ &Obj_FBZFloatingPlatform, DAT_007ce88e, 0x2383, 0, 0x30 },
    //{ &Obj_FBZFloatingPlatform, DAT_007ce88e, 0x2383, 0, 0x40 },
    //{ &Obj_FBZChainLink, DAT_007cfadc, 0x4379, 0, 0x1A },
    { &bgspr,   bgsprpat,    0x4379, 39, 0x27 },
    { &bgspr,   bgsprpat,    0x4379, 40, 0x28 },
    { &bgspr,   bgsprpat,    0x4379, 41, 0x29 },
    { &bgspr,   bgsprpat,    0x4379, 42, 0x2A },
    { &bgspr,   bgsprpat,    0x2443, 43, 0x2B },
    //{ &Obj_FBZMagneticSpikeBall, DAT_007d0148, 0x2443, 0, 0x00 },
    //{ &Obj_FBZMagneticSpikeBall, DAT_007d0148, 0xA443, 1, 0x80 },
    //{ &Obj_FBZMagneticSpikeBall, DAT_007d0148, 0xA442, 5, 0x81 },
    //{ &Obj_FBZMagneticPlatform, DAT_007d07e3, 0x2443, 4, 0x10 },
    { &bryuka, bryukapat4,   0x243A,  0, 0x01 },
    //{ &Obj_FBZRotatingPlatform, DAT_007d143f, 0x246B, 0, 0x00 },
    //{ &Obj_FBZDEZPlayerLauncher, DAT_007d1820, 0x23B5, 0, 0x00 },
    //{ &Obj_FBZDisappearingPla, DAT_007d1b34, 0x23BA, 0, 0x00 },
    //{ &Obj_FBZScrewDoor, DAT_007d2014, 0x23D2, 0, 0x00 },
    //{ &Obj_FBZScrewDoor, DAT_007d2014, 0x23D2, 4, 0x20 },
    //{ &Obj_FBZScrewDoor, DAT_007d2014, 0x23D2, 8, 0x40 },
    { &switch_, switchpat,   0x0500,  2, 0x00 },
    //{ &Obj_FBZPlatformBlocks, DAT_007d2fd7, 0x440D, 1, 0x14 },
    { &break2,  break041pat, 0x4001,  0, 0x08 },
    //{ &Obj_FBZMine, DAT_007d3e52, 0x040A, 0, 0x00 },
    //{ &Obj_FBZElevator, DAT_007d4084, 0x42D2, 0, 0x20 },
    //{ &Obj_FBZTrapSpring, LAB_007d436c, 0x030F, 0, 0x00 },
    //{ &Obj_FBZFlamethrower, DAT_007d4cfe, 0x041D, 1, 0x00 },
    //{ &Obj_FBZFlamethrower, DAT_007d4cfe, 0x041D, 3, 0xC0 },
    //{ &Obj_FBZSpiderCrane, DAT_007d5541, 0x2339, 10, 0x38 },
    { &bgspr,   bgsprpat,    0x2339, 44, 0x2C },
    //{ &Obj_FBZMagneticPendulum, DAT_007d69ea, 0x2323, 0, 0x00 },
    //{ &Obj_FBZMagneticPendulum, DAT_007d69ea, 0x2323, 1, 0x80 }
  }
};
static SKC_edit_data edittbl050 = {
  34,
  {
    { &ring,    ringpat,     0xA6BC,  0, 0x00 },
    { &item,    itempat,     0x04C4,  0, 0x06 },
    { &colichg, colichgpat,  0x26BC,  1, 0x09 },
    { &colichg, colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,   banepat,     0x04A4,  0, 0x81 },
    { &sjump,   banepat,     0x04B4,  3, 0x90 },
    { &sjump,   banepat,     0x04A4,  6, 0xA0 },
    { &toge,    togepat,     0x049C,  0, 0x00 },
    //{ &pngn05,  pngn05pat,   0x2500,  0, 0x20 },
    //{ &uni05,   uni05pat,    0x2548,  0, 0x00 },
    //{ &idai05,  idai05pat,   0x43B6,  0, 0x00 },
    //{ &idai05,  idai05pat,   0x43B6,  0, 0x02 },
    //{ &iroc05,  pilr05pat,   0x4001,  6, 0x00 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x01 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x02 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x03 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x04 },
    //{ &nozu05,  idai05pat,   0x23B6,  6, 0x00 },
    //{ &daru05,  pilr05pat,   0x4001, 10, 0x00 },
    //{ &daru05,  pilr05pat,   0x4001, 10, 0x02 },
    //{ &dash05,  idai05pat,   0x23B6,  7, 0x00 },
    //{ &dash05,  idai05pat,   0x23B6,  7, 0x02 },
    //{ &dtrr05,  pilr05pat,   0x4001,  7, 0x00 },
    //{ &ftrr05,  pilr05pat,   0x4001,  5, 0x00 },
    //{ &ftrr05,  pilr05pat,   0x4001,  5, 0x02 },
    //{ &biwa05,  idai05pat,   0x43B6,  3, 0x00 },
    //{ &toge05,  idai05pat,   0x43B6,  5, 0x00 },
    //{ &toge05,  idai05pat,   0x43B6,  4, 0x02 },
    { &break_,  break050pat, 0x4001,  0, 0x00 },
    { &break2,  break050pat, 0x4001,  3, 0x80 },
    { &bryuka,  bryukapat5,  0x4001,  0, 0x00 },
    { &bryuka,  bryukapat5,  0x43B6, 10, 0x1A },
    //{ &hashi,   hashi05pat,  0x43B6,  0, 0x10 },
    { &switch_, switchpat,   0x0456,  2, 0x10 }
  }
};
static SKC_edit_data edittbl051 = {
  35,
  {
    { &ring,    ringpat,     0xA6BC,  0, 0x00 },
    { &item,    itempat,     0x04C4,  0, 0x06 },
    { &colichg, colichgpat,  0x26BC,  1, 0x09 },
    { &colichg, colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,   banepat,     0x04A4,  0, 0x81 },
    { &sjump,   banepat,     0x04B4,  3, 0x90 },
    { &sjump,   banepat,     0x04A4,  6, 0xA0 },
    { &toge,    togepat,     0x049C,  0, 0x00 },
    //{ &pngn05,  pngn05pat,   0x2500,  0, 0x20 },
    //{ &uni05,   uni05pat,    0x2548,  0, 0x00 },
    //{ &idai05,  idai05pat,   0x43B6,  0, 0x04 },
    //{ &idai05,  idai05pat,   0x43B6,  0, 0x06 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x01 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x02 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x03 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x04 },
    //{ &pilr05,  pilr05pat,   0x4001,  2, 0x05 },
    //{ &nozu05,  idai05pat,   0x23B6,  6, 0x00 },
    //{ &daru05,  pilr05pat,   0x4001, 10, 0x00 },
    //{ &daru05,  pilr05pat,   0x4001, 10, 0x02 },
    //{ &dash05,  idai05pat,   0x23B6,  7, 0x00 },
    //{ &dash05,  idai05pat,   0x23B6,  7, 0x02 },
    //{ &ftrr05,  pilr05pat,   0x4001,  5, 0x00 },
    //{ &ftrr05,  pilr05pat,   0x4001,  5, 0x02 },
    //{ &biwa05,  idai05pat,   0x43B6,  3, 0x00 },
    //{ &toge05,  idai05pat,   0x43B6,  5, 0x02 },
    //{ &toge05,  idai05pat,   0x43B6,  4, 0x00 },
    //{ &snow05,  idai05pat,   0x4377, 32, 0x00 },
    //{ &jdai05,  idai05pat,   0x4377, 31, 0x00 },
    { &break_,  break050pat, 0x4001,  0, 0x00 },
    { &break2,  break050pat, 0x4001,  3, 0x80 },
    { &bryuka,  bryukapat5,  0x4001,  0, 0x00 },
    { &bryuka,  bryukapat5,  0x43B6, 10, 0x1A },
    //{ &hashi,   hashi05pat,  0x43B6,  0, 0x8C },
    { &switch_, switchpat,   0x0456,  2, 0x10 }
  }
};
static SKC_edit_data edittbl060 = {
  36,
  {
    { &ring,      ringpat,     0xA6BC,  0, 0x00 },
    { &item,      itempat,     0x04C4,  0, 0x06 },
    { &colichg,   colichgpat,  0x26BC,  1, 0x09 },
    { &colichg,   colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,     banepat,     0x04A4,  0, 0x81 },
    { &sjump,     banepat,     0x04B4,  3, 0x90 },
    { &sjump,     banepat,     0x04A4,  6, 0xA0 },
    { &toge,      togepat,     0x049C,  0, 0x00 },
    { &break2,    break060pat, 0x4001,  0, 0x80 },
    { &break2,    break061pat, 0x4001,  0, 0x40 },
    { &bryuka,    bryukapat6,  0x4001,  0, 0x00 },
    //{ &dai06,     dai06pat,    0x43C3,  0, 0x05 },
    //{ &dai06,     dai06pat,    0x43C3,  1, 0x11 },
    //{ &switch06,  switch06pat, 0x4433,  0, 0x00 },
    //{ &tobira06,  tobira06pat, 0x43C3,  0, 0x00 },
    //{ &dash06,    dash06pat,   0x43C3,  0, 0x00 },
    //{ &firedai,   firedaipat,  0x43AC,  0, 0x00 },
    //{ &crane,     cranepat,    0x2433,  0, 0x00 },
    //{ &rollelev,  rollelevpat, 0x440D,  0, 0x00 },
    //{ &relevprop, rollelevpat, 0x440D,  3, 0x06 },
    //{ &blade,     bladepat,    0x4455,  0, 0x10 },
    //{ &snil06,    snil06pat,   0x2524,  0, 0x00 },
    //{ &uni06,     uni06pat,    0x256E,  0, 0x00 },
    //{ &uni06,     uni06pat,    0x256E,  0, 0x02 },
    //{ &uni06,     uni06pat,    0x256E,  0, 0x04 },
    //{ &frog06,    frog06pat,   0x2547,  0, 0x00 },
    //{ &frog06,    frog06pat,   0x2547,  0, 0x02 },
    //{ &frog06,    frog06pat,   0x2547,  0, 0x04 },
    //{ &lasr06,    lasr06pat,   0x2558,  0, 0x20 },
    //{ &bird06,    bird06pat,   0x2500,  0, 0x00 },
    { &save,      savepat,     0x05EC,  0, 0x01 },
    //{ &dai06,     dai06pat,    0x43C3,  0, 0x0D },
    //{ &rshoot,    rshootpat,   0x2455,  2, 0x00 },
    { &bgspr,     bgsprpat,    0x440D, 20, 0x14 },
    { &bgspr,     bgsprpat,    0x2433, 21, 0x15 },
    { &bgspr,     bgsprpat,    0x2433, 22, 0x16 }
  }
};
static SKC_edit_data edittbl061 = {
  40,
  {
    { &ring,      ringpat,      0xA6BC,  0, 0x00 },
    { &item,      itempat,      0x04C4,  0, 0x06 },
    { &colichg,   colichgpat,   0x26BC,  1, 0x09 },
    { &colichg,   colichgpat,   0x26BC,  5, 0x0D },
    { &sjump,     banepat,      0x04A4,  0, 0x81 },
    { &sjump,     banepat,      0x04B4,  3, 0x90 },
    { &sjump,     banepat,      0x04A4,  6, 0xA0 },
    { &toge,      togepat,      0x049C,  0, 0x00 },
    { &break2,    break060pat,  0x4001,  0, 0x80 },
    { &break2,    break061pat,  0x4001,  0, 0x40 },
    { &bryuka,    bryukapat6,   0x4001,  0, 0x00 },
    //{ &dai06,     dai06pat,     0x43C3,  0, 0x05 },
    //{ &dai06,     dai06pat,     0x43C3,  1, 0x11 },
    //{ &switch06,  switch06pat,  0x4433,  0, 0x00 },
    //{ &tobira06,  tobira06pat,  0x43C3,  0, 0x00 },
    //{ &dash06,    dash06pat,    0x43C3,  0, 0x00 },
    //{ &firedai,   firedaipat,   0x43AC,  0, 0x00 },
    //{ &crane,     cranepat,     0x2433,  0, 0x00 },
    //{ &wpipe,     wpipepat,     0x42E6,  7, 0x00 },
    //{ &shooter06, shooter06pat, 0x42EA,  0, 0x00 },
    //{ &hook,      hookpat,      0x42EA,  0, 0x1A },
    //{ &laser06,   laser06pat,   0x42EA,  0, 0x0F },
    //{ &snil06,    snil06pat,    0x2524,  0, 0x00 },
    //{ &uni06,     uni06pat,     0x256E,  0, 0x00 },
    //{ &uni06,     uni06pat,     0x256E,  0, 0x02 },
    //{ &uni06,     uni06pat,     0x256E,  0, 0x04 },
    //{ &frog06,    frog06pat,    0x2547,  0, 0x00 },
    //{ &frog06,    frog06pat,    0x2547,  0, 0x02 },
    //{ &frog06,    frog06pat,    0x2547,  0, 0x04 },
    //{ &lasr06,    lasr06pat,    0x2558,  0, 0x20 },
    //{ &bird06,    bird06pat,    0x2500,  0, 0x00 },
    { &save,      savepat,      0x05EC,  0, 0x01 },
    //{ &awa,       awapat,       0x845C, 19, 0x81 },
    //{ &dai06,     dai06pat,     0x43C3,  0, 0x0D },
    //{ &rollelev,  rollelevpat,  0x440D,  0, 0x00 },
    //{ &relevprop, rollelevpat,  0x440D,  3, 0x06 },
    { &brkabe,    brkabe06pat,  0x22EA,  0, 0x00 },
    { &bgspr,     bgsprpat,     0x440D, 20, 0x14 },
    { &bgspr,     bgsprpat,     0x2433, 21, 0x15 },
    { &bgspr,     bgsprpat,     0x2433, 22, 0x16 }
  }
};
static SKC_edit_data edittbl070 = {
  34,
  {
    { &ring,    ringpat,     0xA6BC,  0, 0x00 },
    { &item,    itempat,     0x04C4,  0, 0x06 },
    { &colichg, colichgpat,  0x26BC,  1, 0x09 },
    { &colichg, colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,   banepat,     0x04A4,  0, 0x81 },
    { &sjump,   banepat,     0x04B4,  3, 0x90 },
    { &sjump,   banepat,     0x04A4,  6, 0xA0 },
    { &sjump,   banepat,     0x0478,  7, 0x30 },
    { &sjump,   banepat,     0x0478, 10, 0x40 },
    { &toge,    togepat,     0x049C,  0, 0x00 },
    { &toge,    togepat,     0x0494,  4, 0x40 },
    //{ &dfly07,  dfly07_pt,   0x2538,  0, 0x00 },
    //{ &bfly07,  bfly07_pt,   0x2514,  0, 0x00 },
    //{ &mush07,  mush07_pt,   0x456D,  0, 0x00 },
    //{ &mole07,  mole07_pt,   0x0545,  0, 0x00 },
    //{ &chkn07,  chkn07_pt,   0x2500,  0, 0x00 },
    //{ &Obj_MHZMushroomCap, DAT_007b8098, 0x4369, 0, 0x00 },
    //{ &Obj_MHZPulleyLift, LAB_007b90b2, 0x0424, 4, 0x08 },
    //{ &Obj_MHZCurledVine, LAB_007b9998, 0x4353, 0, 0x00 },
    //{ &Obj_MHZStickyVine, LAB_007ba3e2, 0x440A, 0, 0x00 },
    //{ &Obj_MHZSwingBarHorizon, DAT_007bacb3, 0x03F3, 0, 0x00 },
    //{ &Obj_MHZSwingBarVertical, DAT_007bb54c, 0x03F3, 0, 0x00 },
    //{ &Obj_MHZMushroomPlatform, DAT_007bb6f8, 0x43CD, 0, 0x00 },
    //{ &Obj_MHZMushroomParachute, DAT_007bc19e, 0x43CD, 0, 0x00 },
    //{ &Obj_MHZMushroomCatapult, DAT_007bca56, 0x43CD, 0, 0x00 },
    { &bgspr,   bgsprpat,    0xC357, 24, 0x18 },
    { &bgspr,   bgsprpat,    0xC357, 25, 0x19 },
    { &bgspr,   bgsprpat,    0xC357, 26, 0x1A },
    { &bgspr,   bgsprpat,    0xE40E, 27, 0x1B },
    { &bgspr,   bgsprpat,    0xE40E, 28, 0x1C },
    { &bgspr,   bgsprpat,    0x441E, 29, 0x1D },
    { &bgspr,   bgsprpat,    0x0347, 30, 0x1E },
    { &brkabe,  brkabe07pat, 0x434B,  0, 0x00 },
    { &hbar,    ropepat,     0x0455, 35, 0x00 }
  }
};
static SKC_edit_data edittbl080 = {
  35,
  {
    { &ring,     ringpat,     0xA6BC,  0, 0x00 },
    { &item,     itempat,     0x04C4,  0, 0x06 },
    { &colichg,  colichgpat,  0x26BC,  1, 0x09 },
    { &colichg,  colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,    banepat,     0x04A4,  0, 0x81 },
    { &sjump,    banepat,     0x04B4,  3, 0x90 },
    { &sjump,    banepat,     0x04A4,  6, 0xA0 },
    { &toge,     togepat,     0x049C,  0, 0x00 },
    //{ &scop08,   scop08pat,   0x2536,  0, 0x40 },
    //{ &narl08,   narl08pat,   0x2557,  0, 0x00 },
    //{ &rock08,   rock08_pt,   0x2500,  0, 0x00 },
    //{ &Obj_SOZSpawningSandBlo, DAT_007b189b, 0x43C0, 0, 0x16 },
    { &bgspr,    bgsprpat,    0xC001, 46, 0x2E },
    //{ &Obj_SOZPushableRock, DAT_007b22f1, 0x4455, 0, 0x00 },
    { &bgsprp,   bgsprppat,   0x440F, 14, 0x04 },
    { &bgsprp,   bgsprppat,   0x440F, 18, 0x05 },
    { &bgsprp,   bgsprppat,   0x440F, 22, 0x06 },
    { &bgsprp,   bgsprppat,   0x440F, 26, 0x07 },
    //{ &Obj_SOZSpringVine, LAB_007b2df4, 0x43C9, 0, 0x00 },
    //{ &Obj_SOZRisingSandWall, LAB_007b3448, 0x4432, 0, 0x60 },
    //{ &Obj_SOZFloatingPillar, DAT_007b4191, 0x4001, 0, 0x04 },
    //{ &Obj_SOZFloatingPillar, DAT_007b4191, 0x4001, 1, 0x15 },
    //{ &Obj_SOZFloatingPillar, DAT_007b4191, 0x4001, 2, 0x26 },
    //{ &Obj_SOZSwingingPlatform, LAB_007b4bf4, 0x4001, 2, 0x05 },
    //{ &Obj_SOZSwingingPlatform, LAB_007b4bf4, 0x4001, 2, 0x14 },
    //{ &Obj_SOZBreakableSandRock, DAT_007b4ef8, 0x43D9, 0, 0x00 },
    //{ &Obj_SOZPushSwitch, DAT_007b58a9, 0x4455, 1, 0x00 },
    //{ &Obj_SOZDoor, DAT_007b5c2f, 0x4455, 0, 0x00 },
    //{ &Obj_SOZDoor, DAT_007b5c2f, 0x4455, 1, 0x10 },
    //{ &ropedown, ropedownpat, 0x4411, 32, 0x02 },
    //{ &Obj_SOZSolidSprites, DAT_007b6341, 0x4001, 0, 0x00 },
    //{ &Obj_SOZSolidSprites, DAT_007b6341, 0x4001, 1, 0x01 },
    { &break2,   break081pat, 0x4001,  0, 0x00 },
    { &brkabe,   brkabe03pat, 0x448C,  0, 0x00 },
    { &brkabe,   brkabe03pat, 0x448C,  4, 0x04 }
  }
};
static SKC_edit_data edittbl081 = {
  37,
  {
    { &ring,     ringpat,     0xA6BC,  0, 0x00 },
    { &item,     itempat,     0x04C4,  0, 0x06 },
    { &colichg,  colichgpat,  0x26BC,  1, 0x09 },
    { &colichg,  colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,    banepat,     0x04A4,  0, 0x81 },
    { &sjump,    banepat,     0x04B4,  3, 0x90 },
    { &sjump,    banepat,     0x04A4,  6, 0xA0 },
    { &toge,     togepat,     0x049C,  0, 0x00 },
    //{ &scop08,   scop08pat,   0x2536,  0, 0x40 },
    //{ &narl08,   narl08pat,   0x2557,  0, 0x00 },
    //{ &rock08,   rock08_pt,   0x2500,  0, 0x00 },
    { &bgspr,    bgsprpat,    0xC001, 46, 0x2E },
    //{ &Obj_SOZPushableRock, DAT_007b22f1, 0x4455, 0, 0x00 },
    { &bgsprp,   bgsprppat,   0x440F, 14, 0x04 },
    { &bgsprp,   bgsprppat,   0x440F, 18, 0x05 },
    { &bgsprp,   bgsprppat,   0x440F, 22, 0x06 },
    { &bgsprp,   bgsprppat,   0x440F, 26, 0x07 },
    //{ &Obj_SOZSpringVine, LAB_007b2df4, 0x43C9, 0, 0x00 },
    //{ &Obj_SOZRisingSandWall, LAB_007b3448, 0x4432, 0, 0x60 },
    //{ &Obj_SOZFloatingPillar, DAT_007b4191, 0x4001, 0, 0x04 },
    //{ &Obj_SOZFloatingPillar, DAT_007b4191, 0x4001, 1, 0x15 },
    //{ &Obj_SOZFloatingPillar, DAT_007b4191, 0x4001, 2, 0x26 },
    //{ &Obj_SOZSwingingPlatform, LAB_007b4bf4, 0x4001, 2, 0x05 },
    //{ &Obj_SOZSwingingPlatform, LAB_007b4bf4, 0x4001, 2, 0x14 },
    //{ &Obj_SOZBreakableSandRock, DAT_007b4ef8, 0x43D9, 0, 0x00 },
    //{ &Obj_SOZPushSwitch, DAT_007b58a9, 0x4455, 1, 0x00 },
    //{ &Obj_SOZDoor, DAT_007b5c2f, 0x4455, 0, 0x00 },
    //{ &Obj_SOZDoor, DAT_007b5c2f, 0x4455, 1, 0x10 },
    //{ &ropedown, ropedownpat, 0x4411, 32, 0x02 },
    //{ &Obj_SOZSolidSprites, DAT_007b6341, 0x4001, 0, 0x00 },
    //{ &Obj_SOZSolidSprites, DAT_007b6341, 0x4001, 1, 0x01 },
    { &break2,   break081pat, 0x4001,  0, 0x00 },
    //{ &Obj_SOZLightSwitch, DAT_007b3c29, 0x03AF, 7, 0x04 },
    //{ &Obj_SOZSandCork, DAT_007b619d, 0x43BD, 0, 0x20 },
    { &bgspr,    bgsprpat,    0x03AF, 47, 0x2F },
    { &brkabe,   brkabe03pat, 0x448C,  0, 0x00 },
    { &brkabe,   brkabe03pat, 0x448C,  4, 0x04 }
  }
};
static SKC_edit_data edittbl090 = {
  38,
  {
    { &ring,    ringpat,     0xA6BC,  0, 0x00 },
    { &item,    itempat,     0x04C4,  0, 0x06 },
    { &colichg, colichgpat,  0x26BC,  1, 0x09 },
    { &colichg, colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,   banepat,     0x04A4,  0, 0x81 },
    { &sjump,   banepat,     0x04B4,  3, 0x90 },
    { &sjump,   banepat,     0x04A4,  6, 0xA0 },
    { &toge,    togepat,     0x049C,  0, 0x00 },
    //{ &gas09,   gas09_pt,    0x0562,  0, 0x00 },
    //{ &snak09,  snkf09_pt,   0x6512,  0, 0x00 },
    //{ &iwa09,   iwa09_pt,    0x0530,  0, 0x00 },
    //{ &Obj_LRZSpikeBall, DAT_007adbde, 0xA442, 0, 0x00 },
    //{ &Obj_LRZSinkingRock, LAB_007ab0ab, 0x40D3, 0, 0x00 },
    //{ &Obj_LRZFallingSpike, DAT_007ab2c9, 0x43A1, 0, 0x60 },
    //{ &Obj_LRZDoor, DAT_007ab4af, 0x43A1, 0, 0x00 },
    { &switch_, switch09pat, 0x63A1,  2, 0x00 },
    //{ &Obj_LRZBigDoor, LAB_007ab7d6, 0x43A1, 0, 0x00 },
    //{ &Obj_LRZFireballLauncher, DAT_007abae8, 0x63A1, 2, 0x10 },
    //{ &Obj_LRZButtonHorizontal, LAB_007abcd4, 0x63A1, 0, 0x00 },
    //{ &Obj_LRZShootingTrigger, DAT_007ac08e, 0x63A1, 0, 0x10 },
    //{ &Obj_LRZDashElevator, DAT_007ac53b, 0x03A1, 0, 0x36 },
    //{ &Obj_LRZSmashingSpikePl, DAT_007ac9a1, 0x43A1, 0, 0x18 },
    //{ &Obj_LRZSwingingSpikeBall, DAT_007ad175, 0x83A1, 1, 0x08 },
    //{ &Obj_LRZLavaFall, DAT_007ad3cb, 0x40D3, 0, 0x3C },
    { &bgsprp,  bgsprppat,   0xC0D3,  9, 0x02 },
    { &bgspr,   bgsprpat,    0xC3A1, 31, 0x1F },
    { &bgspr,   bgsprpat,    0xC3A1, 32, 0x20 },
    { &bgspr,   bgsprpat,    0xC3A1, 33, 0x21 },
    { &bgspr,   bgsprpat,    0xC0D3, 34, 0x22 },
    { &break3,  break090pat, 0xC0D3,  8, 0x00 },
    { &iwa,     iwapat9,     0x40D3,  8, 0x44 },
    { &iwa,     iwapat9,     0x40D3,  9, 0x51 },
    { &iwa,     iwapat9,     0x40D3, 10, 0x68 },
    //{ &hashi,   hashi01pat,  0xE113,  0, 0x0E },
    { &bgspr,   bgsprpat,    0xA3A1, 35, 0x23 },
    { &bgspr,   bgsprpat,    0xA3A1, 36, 0x24 },
    { &bgspr,   bgsprpat,    0xA3A1, 37, 0x25 },
    { &bgspr,   bgsprpat,    0xA3A1, 38, 0x26 }
  }
};
static SKC_edit_data edittbl091 = {
  38,
  {
    { &ring,    ringpat,     0xA6BC,  0, 0x00 },
    { &item,    itempat,     0x04C4,  0, 0x06 },
    { &colichg, colichgpat,  0x26BC,  1, 0x09 },
    { &colichg, colichgpat,  0x26BC,  5, 0x0D },
    { &sjump,   banepat,     0x04A4,  0, 0x81 },
    { &sjump,   banepat,     0x04B4,  3, 0x90 },
    { &sjump,   banepat,     0x04A4,  6, 0xA0 },
    { &toge,    togepat,     0x049C,  0, 0x00 },
    //{ &gas09,   gas09_pt,    0x0562,  0, 0x00 },
    //{ &snak09,  snkf09_pt,   0x6512,  0, 0x00 },
    //{ &iwa09,   iwa09_pt,    0x0530,  0, 0x00 },
    //{ &Obj_LRZSinkingRock, LAB_007ab0ab, 0x4090, 1, 0x00 },
    //{ &Obj_LRZDoor, DAT_007ab4af, 0x4090, 1, 0x00 },
    //{ &Obj_LRZSwingingSpikeBall, DAT_007ad175, 0x840D, 3, 0x88 },
    //{ &Obj_LRZButtonHorizontal, LAB_007abcd4, 0x240D, 2, 0x00 },
    { &switch_, switch09pat, 0x2429,  2, 0x00 },
    //{ &kassya,  kassyapat,   0x240D,  0, 0x80 },
    //{ &Obj_LRZOrbitingSpikeBa, DAT_007ae26f, 0x240D, 0, 0x00 },
    //{ &Obj_LRZOrbitingSpikeBa, DAT_007ae26f, 0x240D, 0, 0x00 },
    //{ &Obj_LRZFlameThrower, DAT_007aeb2e, 0x2090, 6, 0x08 },
    { &bgsprp,  bgsprppat,   0x240D, 11, 0x03 },
    //{ &dai09,   dai09pat,    0x4090,  1, 0x10 },
    //{ &dai09,   dai09pat,    0x4090,  0, 0x01 },
    //{ &dai09,   dai09pat,    0x4090,  0, 0x02 },
    //{ &dai09,   dai09pat,    0x4090,  0, 0x03 },
    //{ &dai09,   dai09pat,    0x4090,  0, 0x04 },
    //{ &dai09,   dai09pat,    0x4090,  0, 0x05 },
    //{ &dai09,   dai09pat,    0x4090,  0, 0x06 },
    //{ &Obj_LRZSolidRock, LAB_007af0a2, 0x6090, 0, 0x00 },
    //{ &Obj_LRZSolidRock, LAB_007af0a2, 0x6090, 0, 0x40 },
    { &switch_, switch09pat, 0x2429,  2, 0x40 },
    { &brkabe,  brkabe09pat, 0x640D,  0, 0x00 },
    { &break2,  break091pat, 0x4090,  0, 0x00 },
    { &iwa,     iwapat92,    0x640D,  8, 0xF4 },
    //{ &Obj_LRZTurbineSprites, DAT_007af8e0, 0xA3AD, 0, 0x00 },
    //{ &Obj_LRZTurbineSprites, DAT_007af8e0, 0xA3AD, 4, 0x01 },
    //{ &Obj_LRZFlameThrower, DAT_007aeb2e, 0x2090, 7, 0x88 },
    //{ &Obj_LRZSpikeBallLauncher, DAT_007afec4, 0x240D, 3, 0x60 }
  }
};
static SKC_edit_data edittbl0a0 = {
  22,
  {
    { &ring,    ringpat,    0xA6BC, 0, 0x00 },
    { &item,    itempat,    0x04C4, 0, 0x06 },
    { &colichg, colichgpat, 0x26BC, 1, 0x09 },
    { &colichg, colichgpat, 0x26BC, 5, 0x0D },
    { &sjump,   banepat,    0x04A4, 0, 0x81 },
    { &sjump,   banepat,    0x04B4, 3, 0x90 },
    { &sjump,   banepat,    0x04A4, 6, 0xA0 },
    { &toge,    togepat,    0x049C, 0, 0x00 },
    //{ &Obj_SSZFloatingPlatform, DAT_007c44fc, 0xC2D4, 1, 0x00 },
    //{ &Obj_SSZCollapsingColumn, DAT_007c44fc, 0xE2E4, 2, 0x00 },
    //{ &Obj_SSZCollapsingBridge, LAB_007c4554, 0xC2F4, 0, 0x00 },
    //{ &Obj_SSZCollapsingBridg, LAB_007c4554, 0xC2F4, 3, 0x00 },
    //{ &Obj_SSZBouncyCloud, DAT_007c4640, 0xE3D6, 0, 0x00 },
    //{ &Obj_SSZElevatorBar, DAT_007c46d6, 0x4348, 0, 0x00 },
    //{ &Obj_SSZHPZTeleporter, LAB_007c4738, 0x035C, 0, 0x00 },
    //{ &Obj_SSZRotatingPlatform, DAT_007c48e4, 0x437E, 0, 0x00 },
    //{ &Obj_SSZSwingingCarrier, DAT_007c46d6, 0x4348, 1, 0x00 },
    //{ &Obj_SSZSwingingCarrier, DAT_007c46d6, 0x4348, 4, 0x80 },
    //{ &Obj_SSZRetractingSpring, DAT_007c491c, 0x03A2, 3, 0x00 },
    { &egjr0a,  egjr0apat,  0x0500, 0, 0x00 },
    { &egjr0a,  egjr0apat,  0x0500, 0, 0x02 },
    { &egjr0a,  egjr0apat,  0x0500, 0, 0x04 }
  }
};
static SKC_edit_data edittbl0b0 = {
  31,
  {
    { &ring,    ringpat,    0xA6BC,  0, 0x00 },
    { &item,    itempat,    0x04C4,  0, 0x06 },
    { &colichg, colichgpat, 0x26BC,  1, 0x09 },
    { &colichg, colichgpat, 0x26BC,  5, 0x0D },
    { &sjump,   banepat,    0x04A4,  0, 0x81 },
    { &sjump,   banepat,    0x04B4,  3, 0x90 },
    { &sjump,   banepat,    0x04A4,  6, 0xA0 },
    { &toge,    togepat,    0x049C,  0, 0x00 },
    //{ &gady0b,  gady0bpat,  0x0500,  0, 0x20 },
    //{ &crou0b,  crou0bpat,  0x0542,  0, 0x00 },
    //{ &Obj_DEZTiltingBridge, DAT_007c4f4a, 0x234D, 0, 0x00 },
    //{ &Obj_DEZHangCarrier, DAT_007c54ce, 0x235D, 0, 0x08 },
    //{ &Obj_FBZDEZPlayerLauncher, DAT_007d1820, 0x22FC, 1, 0x00 },
    //{ &door,    doorpat,    0x236B,  2, 0x02 },
    //{ &Obj_DEZTorpedoLauncher, LAB_007c575b, 0x0373, 0, 0x10 },
    //{ &Obj_DEZLiftPad, DAT_007c6150, 0x2302, 2, 0x07 },
    //{ &Obj_DEZLiftPad, DAT_007c6150, 0x2302, 2, 0x27 },
    //{ &Obj_DEZLightning, DAT_007c6bbc, 0x0379, 4, 0xB4 },
    //{ &Obj_DEZConveyorPad, LAB_007c73f8, 0x2408, 0, 0x00 },
    //{ &Obj_DEZConveyorPad, LAB_007c73f8, 0x2408, 4, 0x28 },
    //{ &Obj_DEZEnergyBridge, DAT_007c7cc5, 0x23FF, 0, 0x00 },
    { &bgspr,   bgsprpat,   0x23FF, 48, 0x30 },
    { &bgspr,   bgsprpat,   0x23FF, 49, 0x31 },
    { &bgspr,   bgsprpat,   0x2385, 50, 0x32 },
    //{ &Obj_DEZTunnelLauncher, LAB_007c86bb, 0x0385, 2, 0x00 },
    //{ &Obj_DEZStaircase, DAT_007c4f4a, 0x2480, 0, 0x00 },
    //{ &Obj_DEZStaircase, DAT_007c4f4a, 0x2480, 0, 0x04 },
    //{ &Obj_DEZGravitySwitch, DAT_007c9c83, 0x2490, 0, 0x00 },
    //{ &Obj_DEZHoverMachine, DAT_007cbca9, 0x230D, 0, 0x00 },
    //{ &Obj_DEZBumperWall, LAB_007cc623, 0x232D, 0, 0x00 },
    //{ &Obj_DEZGravityPuzzle, DAT_007ccc52, 0x232D, 0, 0x00 }
  }
};
static SKC_edit_data edittbl0b1 = {
  28,
  {
    { &ring,    ringpat,    0xA6BC,  0, 0x00 },
    { &item,    itempat,    0x04C4,  0, 0x06 },
    { &colichg, colichgpat, 0x26BC,  1, 0x09 },
    { &colichg, colichgpat, 0x26BC,  5, 0x0D },
    { &sjump,   banepat,    0x04A4,  0, 0x81 },
    { &sjump,   banepat,    0x04B4,  3, 0x90 },
    { &sjump,   banepat,    0x04A4,  6, 0xA0 },
    { &toge,    togepat,    0x049C,  0, 0x00 },
    //{ &gady0b,  gady0bpat,  0x0500,  0, 0x20 },
    //{ &crou0b,  crou0bpat,  0x0542,  0, 0x00 },
    //{ &Obj_DEZTiltingBridge, DAT_007c4f4a, 0x234D, 0, 0x00 },
    //{ &Obj_DEZHangCarrier, DAT_007c54ce, 0x235D, 0, 0x08 },
    //{ &door,    doorpat,    0x236B,  2, 0x02 },
    //{ &Obj_DEZTorpedoLauncher, LAB_007c575b, 0x0373, 0, 0x10 },
    //{ &dai0b,   dai0bpat,   0x233A,  0, 0x02 },
    //{ &dai0b,   dai0bpat,   0x233A,  0, 0x05 },
    //{ &Obj_DEZStaircase, DAT_007c4f4a, 0x2480, 0, 0x00 },
    //{ &Obj_DEZStaircase, DAT_007c4f4a, 0x2480, 0, 0x04 },
    //{ &Obj_DEZLightning, DAT_007c6bbc, 0x0379, 4, 0xB4 },
    //{ &Obj_DEZConveyorPad, LAB_007c73f8, 0x2408, 0, 0x00 },
    //{ &Obj_DEZConveyorPad, LAB_007c73f8, 0x2408, 4, 0x28 },
    //{ &Obj_DEZEnergyBridge, DAT_007c7cc5, 0x23FF, 0, 0x00 },
    { &bgspr,   bgsprpat,   0x23FF, 48, 0x30 },
    { &bgspr,   bgsprpat,   0x23FF, 49, 0x31 },
    //{ &Obj_DEZRetractingSpring, DAT_007c8090, 0x2332, 0, 0x00 },
    { &bgspr,   bgsprpat,   0x2385, 50, 0x32 },
    //{ &Obj_DEZTunnelLauncher, LAB_007c86bb, 0x0385, 2, 0x00 },
    //{ &Obj_DEZGravitySwitch, DAT_007c9c83, 0x2490, 0, 0x00 }
  }
};
static SKC_edit_data edittbl0c0 = {
  12,
  {
    { &ring,    ringpat,    0xA6BC,  0, 0x00 },
    { &item,    itempat,    0x04C4,  0, 0x06 },
    { &colichg, colichgpat, 0x26BC,  1, 0x09 },
    { &colichg, colichgpat, 0x26BC,  5, 0x0D },
    { &sjump,   banepat,    0x04A4,  0, 0x81 },
    { &sjump,   banepat,    0x04B4,  3, 0x90 },
    { &sjump,   banepat,    0x04A4,  6, 0xA0 },
    { &toge,    togepat,    0x049C,  0, 0x00 },
    //{ &msil0c,  bs0cb0_pt,  0x42DB, 14, 0x00 },
    //{ &iwa0c,   bs0cb0_pt,  0x22DB, 38, 0x02 },
    //{ &iwa0c,   bs0cb0_pt,  0x22DB, 39, 0x12 },
    //{ &iwa0c,   bs0cb0_pt,  0x22DB, 40, 0x22 }
  }
};
static SKC_edit_data edittbl0c1 = {
  8,
  {
    { &ring,    ringpat,    0xA6BC, 0, 0x00 },
    { &item,    itempat,    0x04C4, 0, 0x06 },
    { &colichg, colichgpat, 0x26BC, 1, 0x09 },
    { &colichg, colichgpat, 0x26BC, 5, 0x0D },
    { &sjump,   banepat,    0x04A4, 0, 0x81 },
    { &sjump,   banepat,    0x04B4, 3, 0x90 },
    { &sjump,   banepat,    0x04A4, 6, 0xA0 },
    { &toge,    togepat,    0x049C, 0, 0x00 }
  }
};
static SKC_edit_data edittbl0d0 = {
  8,
  {
    { &ring,    ringpat,    0xA6BC, 0, 0x00 },
    { &item,    itempat,    0x04C4, 0, 0x06 },
    { &colichg, colichgpat, 0x26BC, 1, 0x09 },
    { &colichg, colichgpat, 0x26BC, 5, 0x0D },
    { &sjump,   banepat,    0x04A4, 0, 0x81 },
    { &sjump,   banepat,    0x04B4, 3, 0x90 },
    { &sjump,   banepat,    0x04A4, 6, 0xA0 },
    { &toge,    togepat,    0x049C, 0, 0x00 }
  }
};
static SKC_edit_data edittbl0e0 = {
  18,
  {
    { &ring,    ringpat,     0xE3D2, 0, 0x00 },
    //{ &vsitem,  vsitempat,   0x03C6, 0, 0x00 },
    { &colichg, colichgpat,  0x63D2, 1, 0x09 },
    { &colichg, colichgpat,  0x63D2, 5, 0x0D },
    { &sjump,   vsbanepat,   0x0391, 0, 0x81 },
    { &sjump,   vsbanepat,   0x03AD, 3, 0x90 },
    { &sjump,   vsbanepat,   0x0391, 6, 0xA0 },
    { &toge,    vstogepat,   0x0391, 0, 0x00 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0x00 },
    { &sjumpsw, vsbanepat,   0x03AD, 3, 0x10 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0x20 },
    { &sjumpsw, vsbanepat,   0x03AD, 3, 0x30 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0x40 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0x50 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0xE0 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0xF0 },
    { &switch_, vsswitchpat, 0x03AD, 2, 0x00 },
    //{ &vsspole, vsspolepat,  0x06BC, 0, 0x00 }
  }
};
static SKC_edit_data edittbl0f0 = {
  21,
  {
    { &ring,      ringpat,      0xE3D2, 0, 0x00 },
    //{ &vsitem,    vsitempat,    0x03C6, 0, 0x00 },
    { &colichg,   colichgpat,   0x63D2, 1, 0x09 },
    { &colichg,   colichgpat,   0x63D2, 5, 0x0D },
    { &sjump,     vsbanepat,    0x0391, 0, 0x81 },
    { &sjump,     vsbanepat,    0x03AD, 3, 0x90 },
    { &sjump,     vsbanepat,    0x0391, 6, 0xA0 },
    { &toge,      vstogepat,    0x0391, 0, 0x00 },
    { &sjumpsw,   vsbanepat,    0x0391, 0, 0x00 },
    { &sjumpsw,   vsbanepat,    0x03AD, 3, 0x10 },
    { &sjumpsw,   vsbanepat,    0x0391, 6, 0x20 },
    { &sjumpsw,   vsbanepat,    0x03AD, 3, 0x30 },
    { &sjumpsw,   vsbanepat,    0x0391, 0, 0x40 },
    { &sjumpsw,   vsbanepat,    0x0391, 6, 0x50 },
    { &sjumpsw,   vsbanepat,    0x0391, 0, 0xE0 },
    { &sjumpsw,   vsbanepat,    0x0391, 6, 0xF0 },
    { &switch_,   vsswitchpat,  0x03AD, 2, 0x00 },
    //{ &bobin,     vsbobinpat,   0x2300, 0, 0x00 },
    //{ &vsmdai,    vsmdaipat,    0x0300, 0, 0x00 },
    //{ &vsballoon, vsballoonpat, 0x6300, 0, 0x00 },
    //{ &vsspole,   vsspolepat,   0x06BC, 0, 0x00 }
  }
};
static SKC_edit_data edittbl100 = {
  21,
  {
    { &ring,    ringpat,     0xE3D2,  0, 0x00 },
    //{ &vsitem,  vsitempat,   0x03C6,  0, 0x00 },
    { &colichg, colichgpat,  0x63D2,  1, 0x09 },
    { &colichg, colichgpat,  0x63D2,  5, 0x0D },
    { &sjump,   vsbanepat,   0x0391,  0, 0x81 },
    { &sjump,   vsbanepat,   0x03AD,  3, 0x90 },
    { &sjump,   vsbanepat,   0x0391,  6, 0xA0 },
    { &toge,    vstogepat,   0x0391,  0, 0x00 },
    { &sjumpsw, vsbanepat,   0x0391,  0, 0x00 },
    { &sjumpsw, vsbanepat,   0x03AD,  3, 0x10 },
    { &sjumpsw, vsbanepat,   0x0391,  6, 0x20 },
    { &sjumpsw, vsbanepat,   0x03AD,  3, 0x30 },
    { &sjumpsw, vsbanepat,   0x0391,  0, 0x40 },
    { &sjumpsw, vsbanepat,   0x0391,  6, 0x50 },
    { &sjumpsw, vsbanepat,   0x0391,  0, 0xE0 },
    { &sjumpsw, vsbanepat,   0x0391,  6, 0xF0 },
    { &switch_, vsswitchpat, 0x03AD,  2, 0x00 },
    //{ &vssdai,  vssdaipat,   0x4280,  0, 0x00 },
    //{ &vssdai,  vssdaipat,   0x4280, 29, 0x01 },
    //{ &vssw,    vsswpat,     0x4280,  0, 0x00 },
    //{ &vsspole, vsspolepat,  0x06BC,  0, 0x00 }
  }
};
static SKC_edit_data edittbl110 = {
  20,
  {
    { &ring,    ringpat,     0xE3D2, 0, 0x00 },
    //{ &vsitem,  vsitempat,   0x03C6, 0, 0x00 },
    { &colichg, colichgpat,  0x63D2, 1, 0x09 },
    { &colichg, colichgpat,  0x63D2, 5, 0x0D },
    { &sjump,   vsbanepat,   0x0391, 0, 0x81 },
    { &sjump,   vsbanepat,   0x03AD, 3, 0x90 },
    { &sjump,   vsbanepat,   0x0391, 6, 0xA0 },
    { &toge,    vstogepat,   0x0391, 0, 0x00 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0x00 },
    { &sjumpsw, vsbanepat,   0x03AD, 3, 0x10 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0x20 },
    { &sjumpsw, vsbanepat,   0x03AD, 3, 0x30 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0x40 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0x50 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0xE0 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0xF0 },
    { &switch_, vsswitchpat, 0x03AD, 2, 0x00 },
    //{ &fan,     vsfanpat,    0x6300, 0, 0x00 },
    //{ &vsdai,   vsdaipat,    0x6300, 0, 0x00 },
    //{ &vsspole, vsspolepat,  0x06BC, 0, 0x00 }
  }
};
static SKC_edit_data edittbl120 = {
  22,
  {
    { &ring,    ringpat,     0xE3D2, 0, 0x00 },
    //{ &vsitem,  vsitempat,   0x03C6, 0, 0x00 },
    { &colichg, colichgpat,  0x63D2, 1, 0x09 },
    { &colichg, colichgpat,  0x63D2, 5, 0x0D },
    { &sjump,   vsbanepat,   0x0391, 0, 0x81 },
    { &sjump,   vsbanepat,   0x03AD, 3, 0x90 },
    { &sjump,   vsbanepat,   0x0391, 6, 0xA0 },
    { &toge,    vstogepat,   0x0391, 0, 0x00 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0x00 },
    { &sjumpsw, vsbanepat,   0x03AD, 3, 0x10 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0x20 },
    { &sjumpsw, vsbanepat,   0x03AD, 3, 0x30 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0x40 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0x50 },
    { &sjumpsw, vsbanepat,   0x0391, 0, 0xE0 },
    { &sjumpsw, vsbanepat,   0x0391, 6, 0xF0 },
    { &switch_, vsswitchpat, 0x03AD, 2, 0x00 },
    //{ &vsspole, vsspolepat,  0x06BC, 0, 0x00 },
    //{ &vsoil,   vsoilpat,    0x6300, 0, 0x00 },
    //{ &vsoil,   vsoilpat,    0xC300, 3, 0x00 },
    { &vsiwa,   vsiwapat,    0x6300, 0, 0x34 },
    { &vsiwa,   vsiwapat,    0x6300, 0, 0x33 }
  }
};
static SKC_edit_data edittbl140 = {
  9,
  {
    { &ring,  ringpat,    0xA6BC, 0, 0x00 },
    //{ &bobin, bobin14pat, 0x62CD, 0, 0x00 },
    //{ &Obj_PachinkoTriangleBu, DAT_007bd2c8, 0xE2EB, 1, 0x00 },
    //{ &Obj_PachinkoFlipper, DAT_007bd9d8, 0x832F, 4, 0x00 },
    //{ &Obj_PachinkoEnergyTrap, DAT_007bde89, 0x2352, 0, 0x00 },
    //{ &Obj_Pachinko_Platform, DAT_007be137, 0x2358, 0, 0x00 },
    //{ &Obj_PachinkoInvisibleU, LAB_007bdff8, 0xE364, 0, 0x00 },
    //{ &Obj_GumballItem, DAT_007be5c7, 0x6378, 0, 0x00 },
    //{ &Obj_PachinkoItemOrb, LAB_007be2d4, 0xE364, 0, 0x00 }
  }
};
static SKC_edit_data edittbl160 = {
  10,
  {
    { &ring,    ringpat,     0xA6BC, 0, 0x00 },
    { &item,    itempat,     0x04C4, 0, 0x06 },
    { &colichg, colichgpat,  0x26BC, 1, 0x09 },
    { &colichg, colichgpat,  0x26BC, 5, 0x0D },
    { &sjump,   banepat,     0x04A4, 0, 0x81 },
    { &sjump,   banepat,     0x04B4, 3, 0x90 },
    { &sjump,   banepat,     0x04A4, 6, 0xA0 },
    { &toge,    togepat,     0x049C, 0, 0x00 },
    { &break2,  break093pat, 0x4001, 0, 0x80 }
    //{ &Obj_SSZHPZTeleporter, LAB_007c4738, 0x052E, 10, 0x00 },
  }
};
static SKC_edit_data edittbl170 = {
  8,
  {
    { &ring,    ringpat,    0xA6BC, 0, 0x00 },
    { &item,    itempat,    0x04C4, 0, 0x06 },
    { &colichg, colichgpat, 0x26BC, 1, 0x09 },
    { &colichg, colichgpat, 0x26BC, 5, 0x0D },
    { &sjump,   banepat,    0x04A4, 0, 0x81 },
    { &sjump,   banepat,    0x04B4, 3, 0x90 },
    { &sjump,   banepat,    0x04A4, 6, 0xA0 },
    { &toge,    togepat,    0x049C, 0, 0x00 }
  }
};
