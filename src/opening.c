#include "globals.h"
#include "macros.h"
#include "types/spritestatus.h"
#include "bitdevr.h"
#include "color.h"
#include "data.h"
#include "game.h"
#include "mapdevr.h"
#include "cg/openingcg.h"
#include "map/openingmap.h"
#include "unlze.h"
#include "util.h"
#include "vdp.h"
static void load_frames();
static sprite_pattern* skopening_sonicfalling_pat[1];
static sprite_pattern skopening_sonicfalling_sp00;
static sprite_pattern* skopening_deathegg_pat[1];
static sprite_pattern skopening_deathegg_sp00;
static sprite_pattern* skopening_banner_pat[1];
static sprite_pattern skopening_banner_sp00;
static sprite_pattern* skopening_mountain_pat[1];
static sprite_pattern skopening_mountain_sp00;
static void s3kopening();
static void plays3kdemo();
static short s3kdemostagenos[7];
static unsigned short s3opening_transition_color[56];
static unsigned short s3opening_main_color[64];
static void s3banner_init(sprite_status* p_actwk);
static void s3banner_move0(sprite_status* p_actwk);
static void s3banner_move1(sprite_status* p_actwk);
static unsigned short s3opening_water_color[16];
static void s3bannertm_init(sprite_status* p_actwk);
static void s3bannertm_move(sprite_status* p_actwk);
static void andknuckles_init(sprite_status* p_actwk);
static void andknuckles_move(sprite_status* p_actwk);
static sprite_pattern* s3opening_andknuckles_pat[1];
static sprite_pattern s3opening_andknuckles_sp00;
static void s3copyright_init(sprite_status* p_actwk);
static void selection_init(sprite_status* p_actwk);
static void selection_move(sprite_status* p_actwk);
static void sonicfinger_init(sprite_status* p_actwk);
static void sonicfinger_move(sprite_status* p_actwk);
static signed char* s3opening_sonicfinger_chg[1];
static signed char s3opening_sonicfinger_chg0[30];
static void sonicwink_init(sprite_status* p_actwk);
static void sonicwink_move(sprite_status* p_actwk);
static signed char* s3opening_sonicwink_chg[1];
static signed char s3opening_sonicwink_chg0[11];
static void tornado_init(sprite_status* p_actwk);
static void tornado_move(sprite_status* p_actwk);
static signed char* s3opening_tornado_chg[1];
static signed char s3opening_tornado_chg0[8];
static sprite_pattern* s3opening_selectioncopyright_pat[4];
static sprite_pattern s3opening_selectioncopyright_sp00;
static sprite_pattern s3opening_selectioncopyright_sp01;
static sprite_pattern s3opening_selectioncopyright_sp02;
static sprite_pattern s3opening_selectioncopyright_sp03;
static sprite_pattern* s3opening_sonic_pat[5];
static sprite_pattern s3opening_sonic_sp00;
static sprite_pattern s3opening_sonic_sp01;
static sprite_pattern s3opening_sonic_sp02;
static sprite_pattern s3opening_sonic_sp03;
static sprite_pattern s3opening_sonic_sp04;
static sprite_pattern* s3opening_tornado_pat[6];
static sprite_pattern s3opening_tornado_sp00;
static sprite_pattern s3opening_tornado_sp01;
static sprite_pattern s3opening_tornado_sp02;
static sprite_pattern s3opening_tornado_sp03;
static sprite_pattern s3opening_tornado_sp04;
static sprite_pattern s3opening_tornado_sp05;
static void skopening();
static unsigned short skopening_color[64];
static unsigned short skopening_knuckles_color[16];
static void playskdemo();
static void sonicfalling_init(sprite_status* p_actwk);
static void sonicfalling_move0(sprite_status* p_actwk);
static void sonicfalling_wait0(sprite_status* p_actwk);
static void sonicfalling_wait1(sprite_status* p_actwk);
static void sonicfalling_move1(sprite_status* p_actwk);
static void deathegg_init(sprite_status* p_actwk);
static void deathegg_move0(sprite_status* p_actwk);
static void deathegg_move1(sprite_status* p_actwk);
static void mountain_init(sprite_status* p_actwk);
static void mountain_move(sprite_status* p_actwk);
static void skbanner_init(sprite_status* p_actwk);
static void skbanner_move(sprite_status* p_actwk);
static void skopeninganims_init(sprite_status* p_actwk);
static void skopeninganims_move(sprite_status* p_actwk);
static short skopening_animate(signed char* p_animdata, unsigned char* p_currentanim);
static signed char skopening_sonicsmile_anim[6];
static signed char skopening_sonicfinger_anim[47];
static signed char skopening_knuckleshand1_anim[17];
static signed char skopening_knuckleshand2_anim[9];
static void nameroulette_init(sprite_status* p_actwk);
static void nameroulette_move(sprite_status* p_actwk);
static void chibi_init(sprite_status* p_actwk);
static void chibi_move(sprite_status* p_actwk);
static signed char* chibichg[3];
static signed char chibichg0[6];
static signed char chibichg1[6];
static signed char chibichg2[3];
static void skbannertm_init(sprite_status* p_actwk);
static void skbannertm_move(sprite_status* p_actwk);
static void skcopyright_init(sprite_status* p_actwk);
static void copy_mapline_vram(unsigned char* p_destination, unsigned char* p_source, short offset);
static void copy_bgmap_vram(unsigned short* p_destination, unsigned short* p_source);
static void shake_screen();
static void deform_bg();
static unsigned char shakeoffsets[66];
static sprite_pattern* skselectionpat[9];
static sprite_pattern skselectionsp00;
static sprite_pattern skselectionsp01;
static sprite_pattern skselectionsp02;
static sprite_pattern skselectionsp03;
static sprite_pattern skselectionsp04;
static sprite_pattern skselectionsp05;
static sprite_pattern skselectionsp06;
static sprite_pattern skselectionsp07;
static sprite_pattern skselectionsp08;
static sprite_pattern* skopening_bannertm_pat[1];
static sprite_pattern skopening_bannertm_sp00;
static sprite_pattern* skopening_copyright_pat[1];
static sprite_pattern skopening_copyright_sp00;
static unsigned char DAT_006e0340[209];
static unsigned char DAT_006e0411[183];
static void plays3demo();
static short s3demostagenos[3];
static void* s3opening_datalist[42];

extern void vInt();


// 0040b900
static void load_frames() {
  unsigned char* p_decompressed = unlze(g_ram.decompressed, s3opening_frame1_cg, 0);
  copy_data_vram(g_ram.decompressed, 0, (p_decompressed - g_ram.decompressed) / 2);

  for (int i = 0; i < 14; ++i) {
    if (s3opening_datalist[i * 3] != s3opening_frame1_cg) {
      p_decompressed = unlze(g_ram.decompressed, s3opening_datalist[i * 3], 0);
      copy_data_vram(g_ram.decompressed, 0, (p_decompressed - g_ram.decompressed) / 2);
    }
    memcpy(g_ram.colorwk2, s3opening_datalist[i * 3 + 1], 64);
    mapdevr((unsigned short*)g_ram.decompressed, s3opening_datalist[i * 3 + 2], 0);
    copy_map_vram((unsigned short*)g_ram.decompressed, 0xC000, 27, 39);

    for (int j = 0; j < 4; ++j) {
      g_ram.int_flg = 4;
      vInt();
    }
  }
}


/* 00692960 */ static sprite_pattern* skopening_sonicfalling_pat[1] = {
  &skopening_sonicfalling_sp00
};


static sprite_pattern skopening_sonicfalling_sp00 = {
  32,
  {
    { -112, 15, 0x0000, -48 },
    { -112, 15, 0x0010, -16 },
    { -112, 15, 0x0020,  16 },
    { -112,  5, 0x0030, -64 },
    { -112,  4, 0x0034,  48 },
    { -104,  2, 0x0036,  48 },
    {  -80, 15, 0x0039, -48 },
    {  -80, 15, 0x0049, -16 },
    {  -80, 15, 0x0059,  16 },
    {  -80,  6, 0x0069,  48 },
    {  -72, 15, 0x006F, -80 },
    {  -64,  2, 0x007F, -88 },
    {  -48, 15, 0x0082, -16 },
    {  -48,  7, 0x0092,  16 },
    {  -48,  9, 0x009A,  32 },
    {  -32,  4, 0x00A0,  40 },
    {  -24, 14, 0x00A2,  48 },
    {  -32, 12, 0x00AE,  56 },
    {  -24,  7, 0x00B2,  80 },
    {    0,  0, 0x00BA,  72 },
    {  -48,  8, 0x00BB, -40 },
    {  -40,  5, 0x00BE, -32 },
    {  -16, 15, 0x00C2, -16 },
    {  -16,  1, 0x00D2,  16 },
    {    0,  5, 0x00D4,  16 },
    {   16,  6, 0x00D8,  -8 },
    {   16, 15, 0x00DE,   8 },
    {   48, 15, 0x00EE,   8 },
    {   40,  3, 0x00FE,  40 },
    {   72,  0, 0x0102,  40 },
    {   80, 13, 0x0103,   8 },
    {   96,  9, 0x010B,   8 }
  }
};


/* 00692a24 */ static sprite_pattern* skopening_deathegg_pat[1] = {
  &skopening_deathegg_sp00
};


static sprite_pattern skopening_deathegg_sp00 = {
  18,
  {
    { -64, 15, 0x0000, -32 },
    { -64, 15, 0x0800,   0 },
    { -56, 10, 0x0010, -56 },
    { -56, 10, 0x0810,  32 },
    { -32, 15, 0x0019, -64 },
    { -32, 15, 0x0819,  32 },
    { -32, 15, 0x0029, -32 },
    { -32, 15, 0x0829,   0 },
    {   0, 15, 0x0039, -64 },
    {   0, 15, 0x0049, -32 },
    {   0, 15, 0x0849,   0 },
    {   0, 15, 0x0839,  32 },
    {  32,  8, 0x0059, -56 },
    {  32, 15, 0x005C, -32 },
    {  40,  6, 0x006C, -48 },
    {  32, 15, 0x085C,   0 },
    {  32,  8, 0x0859,  32 },
    {  40,  6, 0x086C,  32 }
  }
};


/* 00692a94 */ static sprite_pattern* skopening_banner_pat[1] = {
  &skopening_banner_sp00
};


static sprite_pattern skopening_banner_sp00 = {
  30,
  {
    { -40, 15, 0x6000, -100 },
    { -40, 15, 0x6010,  -68 },
    { -40, 15, 0x6020,  -36 },
    { -40, 15, 0x6030,   -4 },
    { -40, 11, 0x6040,   28 },
    { -32, 14, 0x604C,   52 },
    {  -8, 12, 0x6058, -124 },
    {  -8, 12, 0x605C,  -92 },
    {  -8, 12, 0x6060,  -60 },
    {  -8, 12, 0x6064,  -28 },
    {  -8, 12, 0x6068,    4 },
    {  -8, 12, 0x606C,   36 },
    {  -8, 12, 0x6070,   68 },
    {  -8,  8, 0x6074,  100 },
    {   0, 15, 0x2077, -124 },
    {   0, 15, 0x2087,  -92 },
    {   0, 15, 0x2097,  -60 },
    {   0, 15, 0x20A7,  -28 },
    {   0, 15, 0x20B7,    4 },
    {   0, 15, 0x20C7,   36 },
    {   0, 15, 0x20D7,   68 },
    {   0, 11, 0x20E7,  100 },
    {  32, 12, 0x20F3, -124 },
    {  32, 12, 0x20F7,  -92 },
    {  32, 12, 0x20FB,  -60 },
    {  32, 12, 0x20FF,  -28 },
    {  32, 12, 0x2103,    4 },
    {  32, 12, 0x2107,   36 },
    {  32, 12, 0x210B,   68 },
    {  32,  8, 0x210F,  100 }
  }
};


/* 00692b4c */ static sprite_pattern* skopening_mountain_pat[1] = {
  &skopening_mountain_sp00
};


static sprite_pattern skopening_mountain_sp00 = {
  4,
  {
    { -8,  0, 0x0000, -48 },
    {  0, 12, 0x0001, -48 },
    { -8, 13, 0x0005, -16 },
    { -8, 13, 0x000D,  16 }
  }
};


// 006dbfe2
void opening() {
  bgmset(225);
  if (!g_sonic3_alone) {
    g_ram.stageno = 0;
  }
  g_vdp_scrolla_adr = 0xC000;
  g_vdp_scrollb_adr = 0xE000;
  g_bg_color_index = 0;
  g_vdp_hscroll_scanline = 1;
  g_ram.waterflag = 0;
  if (!g_sonic3_alone) {
    g_ram.watermode = 0;
  }
  scrinit();
  memset(g_ram.pbuffer, 0, sizeof(g_ram.pbuffer));
  memset(g_ram.actwk, 0, sizeof(g_ram.actwk) + 52);
  // START memset(DAT_08fff700, 0, 256)
  g_ram.DAT_08fff711 = 0;
  g_ram.watermode = 0;
  g_ram.miles_carry_flag = 0;
  g_ram.plmaxspdwk = 0;
  g_ram.pladdspdwk = 0;
  g_ram.plretspdwk = 0;
  g_ram.bossstart = 0;
  g_ram.soz_darkness_level = 0;
  g_ram.reverse_gravity_flag = 0;
  g_ram.pl2_lock_flag = 0;
  g_ram.emyscorecnt = 0;
  g_ram.timebonus = 0;
  g_ram.ringbonus = 0;
  g_ram.scr_x_no = 0;
  memset(g_ram.stage_triggers, 0, STAGE_TRIGGERS_SLOTS);
  memset(g_ram.actanimcounters, 0, 16);
  // END memset(DAT_08fff700, 0. 256)
  // START memset(DAT_08ffee00, 0, 256)
  g_ram.scralim_n_down = 0;
  g_ram.scralim_left = 0;
  g_ram.scralim_right = 0;
  g_ram.scralim_down = 0;
  g_ram.zone_flag = 0;
  g_ram.vs_vscroll = 0;
  g_ram.stageno_i = 0;
  g_ram.colorcycle = 0;
  g_ram.vs_scra_h_posit = 0;
  g_ram.vs_scra_v_posit = 0;
  g_ram.vs_scra_h_posit_copy = 0;
  g_ram.vs_scra_v_posit_copy = 0;
  g_ram.scra_h_posit = 0;
  g_ram.scra_v_posit = 0;
  g_ram.scra_h_posit_copy = 0;
  g_ram.scra_v_posit_copy = 0;
  g_ram.scrc_v = 0;
  g_ram.frame_offset_x = 0;
  g_ram.scr_evta = 0;
  g_ram.event_flag_3 = 0;
  g_ram.scr_shake_flg = 0;
  g_ram.DAT_08ffeed2 = 0;
  memset(g_ram.vscrollbuff, 0, 80);
  // END memset(DAT_08ffee00, 0, 256)
  init_sprlist();
  memset(g_ram.colorwk, 0, sizeof(g_ram.colorwk));
  g_ram.markerno = 0;
  g_ram.marker_flag = 0;
  g_ram.editmode = 0;
  g_ram.demoflag = 0;
  g_ram.clchgtim = 0;
  g_ram.vs_flag = 0;
  g_ram.DAT_08fff711 = 0;
  g_ram.DAT_08ffffda = 0;
  g_ram.vs_flag = 0;
  g_ram.editmodecheatcnt = 0;
  g_ram.allemeraldscheatcnt = 0;
  g_ram.bsmode = 0;
  g_ram.demotimer = 359;
  if (g_ram.cartridge == 0) {
    s3kopening();
  }
  else {
    skopening();
  }
}


// 006dc199
static void s3kopening() {
  unsigned char* p_decompressed = unlze(g_ram.decompressed, s3opening_frame1_cg, 0);
  copy_data_vram(g_ram.decompressed, 0, (p_decompressed - g_ram.decompressed) / 2);
  mapdevr((unsigned short*)&g_ram.decompressed[0x8000], s3opening_frame1_map, 0);
  if (!BIT_7_IS_SET(g_ram.mdstatus) && !g_sonic3_alone) {
    *((unsigned long*)&g_ram.decompressed[0x83AC]) = 0;
  }
  copy_map_vram((unsigned short*)&g_ram.decompressed[0x8000], 0xC000, 27, 39);
  memcpy(g_ram.colorwk2, s3opening_frame1_color, 32);
  g_ram.demotimer = 240;
  fadein();
  bgmset(255);
  g_ram.demotimer = 180;

  do {
    g_ram.int_flg = 20;
    vInt();
    if (IS_BUTTON_PRESSED(g_ram.swdata1, PAD_S)) break;
  } while (g_ram.demotimer != 0);

  bgmset(254);
  unsigned short* p_colorwk = g_ram.colorwk;

  for (int i = 0; i < 4; ++i) {
    g_ram.int_flg = 2;
    memcpy(p_colorwk, s3opening_transition_color, 14);
    p_colorwk += 7;
  }

  bgmset(37);
  load_frames();
  g_ram.demotimer = 750;
  g_ram.openinganimframe = 12;

  for (int i = 0; i < 64; ++i) {
    g_ram.colorwk[i] = 0xEEE;
  }

  g_ram.openinganimdelay = 3;
  g_ram.int_flg = 4;
  vInt();
  p_decompressed = unlze(g_ram.decompressed, s3opening_frame13_cg, 0);
  copy_data_vram(g_ram.decompressed, 0, (p_decompressed - g_ram.decompressed) / 2);
  mapdevr((unsigned short*)&g_ram.decompressed[0x8000], s3opening_frame13_map, 0x8000);
  copy_map_vram((unsigned short*)&g_ram.decompressed[0x8000], 0xC000, 27, 39);
  mapdevr((unsigned short*)&g_ram.decompressed[0x8000], s3opening_frame14_map, 0x4000);
  copy_map_vram((unsigned short*)&g_ram.decompressed[0x8000], 0xE000, 27, 39);
  g_ram.int_flg = 4;
  vInt();
  memcpy(g_ram.colorwk2, s3opening_main_color, sizeof(s3opening_main_color));
  bitdevr((unsigned long*)&g_vram[0xA000], s3opening_banner_cg, g_ram.bitdevwk);
  bitdevr((unsigned long*)&g_vram[0xD000], s3opening_text_cg, g_ram.bitdevwk);
  bitdevr((unsigned long*)&g_vram[0xD4C0], DAT_006e0340, g_ram.bitdevwk);
  bitdevr((unsigned long*)&g_vram[0x8000], s3opening_sonicsprites_cg, g_ram.bitdevwk);
  if (!g_sonic3_alone) {
    bitdevr((unsigned long*)&g_vram[0x9800], s3kopening_andknuckles_cg, g_ram.bitdevwk);
  }
  g_ram.actwk[0].r_ptr = &s3banner_init;
  g_ram.actwk[1].r_ptr = &selection_init;
  g_ram.actwk[3].r_ptr = &s3copyright_init;
  g_ram.actwk[4].r_ptr = &sonicfinger_init;
  g_ram.actwk[5].r_ptr = &sonicwink_init;
  g_ram.actwk[6].r_ptr = &tornado_init;
  if (!g_sonic3_alone) {
    g_ram.actwk[7].r_ptr = &andknuckles_init;
  }
  g_ram.openinganimdelay = 0;
  unsigned short swdata;

  do {
    do {
      g_ram.int_flg = 4;
      vInt();
      action();
      patset();
    } while (g_ram.actwk[2].r_ptr == 0);

    if (g_ram.demotimer == 0) {
      if (!g_sonic3_alone) {
        plays3kdemo();
      }
      else {
        plays3demo();
      }
      return;
    }
    swdata = g_ram.swdata1;
    if (!g_sonic3_alone) {
      swdata |= g_ram.swdata2;
    }
  } while (!IS_BUTTON_PRESSED(swdata, PAD_S));

  g_ram.gmmode = 12;
  g_ram.pl_suu = 3;
  g_ram.pl2_suu = 3;
  g_ram.plring = 0;
  g_ram.pltime.hours = 0;
  g_ram.pltime.minutes = 0;
  g_ram.pltime.seconds = 0;
  g_ram.pltime.frames = 0;
  g_ram.plscore = 0;
  g_ram.pl2ring = 0;
  g_ram.DAT_08fffed2 = 0;
  g_ram.DAT_08fffed6 = 0;
  g_ram.plcontinuecnt = 0;
  g_ram.extrascore = 5000;
  g_ram.extrascore2 = 5000;
  soundset(225);

  switch (g_ram.openingoption) {
    case 0:
      g_ram.gmmode = 76;
      break;
    case 1:
      g_ram.gmmode = 56;
      break;
    case 2:
      g_ram.gmmode = 40;
      break;
  }
}


// 006dc7a7
static void plays3kdemo() {
  soundset(225);
  g_ram.demoid = g_ram.nextdemoid;
  short stageno = s3kdemostagenos[g_ram.nextdemoid & 7];
  g_ram.stageno = stageno;
  g_ram.stageno_i = stageno;
  g_ram.stageno_s = stageno;
  unsigned short nextdemoid = g_ram.nextdemoid + 1;
  if (g_ram.cartridge == 0) {
    if (nextdemoid == 3) {
      nextdemoid = 4;
    }
    else if (nextdemoid >= 7) {
      nextdemoid = 0;
    }
  }
  else if (nextdemoid >= 3) {
    nextdemoid = 0;
  }
  g_ram.nextdemoid = nextdemoid;
  if (stageno < 0) {
    g_ram.gmmode = 52;
    g_ram.DAT_08fffe16 = 1;
    g_ram.cartridgespec = 1;
    SET_ACT(g_ram.stageno, 7);
    memset(g_ram.specprogress, 0, sizeof(g_ram.specprogress));
  }
  else {
    g_ram.gmmode = 8;
  }
  g_ram.demoflag = 1;
  g_ram.pl_suu = 3;
  g_ram.pl2_suu = 3;
  g_ram.plring = 0;
  g_ram.pltime.hours = 0;
  g_ram.pltime.minutes = 0;
  g_ram.pltime.seconds = 0;
  g_ram.pltime.frames = 0;
  g_ram.plscore = 0;
  g_ram.pl2ring = 0;
  g_ram.DAT_08fffed2 = 0;
  g_ram.DAT_08fffed6 = 0;
  g_ram.extrascore = 5000;
  g_ram.extrascore2 = 5000;
}


/* 006dc975 */ static short s3kdemostagenos[7] = {
  ANGEL_ISLAND_ACT_1,
  HYDROCITY_ACT_1,
  MUSHROOM_HILL_ACT_1,
  FLYING_BATTERY_ACT_1,
  SANDOPOLIS_ACT_1,
  -1
};


/* 006dce75 */ static unsigned short s3opening_transition_color[56] = {
  0xEEE, 0xEEE, 0xECC, 0xECA, 0xEC8, 0x000, 0xEA6, 0xCCC, 0xCCC, 0xCAA, 0xEA8, 0xEA6, 0x000, 0xEA6, 0xAAA, 0xCAA,
  0xC88, 0xC88, 0xCA6, 0x000, 0xE84, 0x888, 0xA88, 0xA66, 0xC66, 0xC84, 0x000, 0xC84, 0x666, 0x866, 0xA66, 0xA64,
  0xC64, 0x000, 0xC62, 0x444, 0x644, 0x844, 0xA42, 0xA42, 0x000, 0xC62, 0x222, 0x622, 0x822, 0x822, 0xA42, 0x000,
  0xC40, 0x000, 0x400, 0x600, 0x800, 0xA20, 0x000, 0xC40
};
/* 006dd085 */ static unsigned short s3opening_main_color[64] = {
  0x000, 0xEEE, 0xEA6, 0xE84, 0xE62, 0xE40, 0xE00, 0x600, 0x0EE, 0x2AC, 0x08C, 0x06A, 0x048, 0x026, 0x444, 0x000,
  0x000, 0xEEE, 0xE84, 0xE62, 0xE40, 0xE00, 0x600, 0x8CE, 0x4AE, 0x48C, 0x46A, 0x246, 0xECA, 0x866, 0x444, 0x000,
  0x0E0, 0xEEE, 0x0AE, 0x268, 0x246, 0x440, 0xEEA, 0xEC6, 0xE82, 0xE42, 0xE22, 0x0E6, 0x082, 0xE42, 0xEC6, 0x000,
  0x000, 0xEEE, 0xA66, 0x604, 0x602, 0x200, 0xAEE, 0x4EE, 0x0AE, 0x06E, 0xCCC, 0x00E, 0x00A, 0x408, 0x206, 0x000
};


// 006dd105
static void s3banner_init(sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_banner_pat;
  p_actwk->sproffset = 0xE500;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 128;
  p_actwk->sprvs = 64;
  util__assign_high(&p_actwk->xposi, 288);
  util__assign_high(&p_actwk->yposi, 240);
  p_actwk->yspeed = 1024;
  p_actwk->actfree.s3opening_banner.yposiwk = -6291456;
  p_actwk->r_ptr = &s3banner_move0;
  s3banner_move0(p_actwk);
}


// 006dd18a
static void s3banner_move0(sprite_status* p_actwk) {
  unsigned char prev_dir = p_actwk->actfree.s3opening_banner.dir;
  p_actwk->actfree.s3opening_banner.yposiwk += p_actwk->yspeed * 256;
  p_actwk->actfree.s3opening_banner.dir = 0;
  short yspeed_add = 64;
  int compare_result = 0;
  short yposiwk_integral = util__longhigh_to_short(p_actwk->actfree.s3opening_banner.yposiwk);
  if (yposiwk_integral < 0) {
    compare_result = -1;
  }
  else if (yposiwk_integral > 0) {
    compare_result = 1;
  }

  switch (compare_result) {
    case 0:
      if (p_actwk->yspeed == -91) {
        p_actwk->r_ptr = &s3banner_move1;
        g_ram.actwk[2].r_ptr = &s3bannertm_init;
        break;
      }
      // fall-through
    case 1:
      p_actwk->actfree.s3opening_banner.dir = 255;
      yspeed_add = -64;
      // fall-through
    case -1:
      p_actwk->yspeed += yspeed_add;
      if (prev_dir != p_actwk->actfree.s3opening_banner.dir) {
        p_actwk->yspeed /= 2;
      }
      break;
  }

  short yposi = -util__longhigh_to_short(p_actwk->actfree.s3opening_banner.yposiwk);
  if (!g_sonic3_alone) {
    yposi += 212;
  }
  else {
    yposi += 240;
  }
  util__assign_high(&p_actwk->yposi, yposi);
  if (!g_sonic3_alone) {
    if (g_ram.vscrolla != 16) {
      ++g_ram.vscrolla;
    }
  }
  s3banner_move1(p_actwk);
}


// 006dd2ee
static void s3banner_move1(sprite_status* p_actwk) {
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 9;
    p_actwk->patcnt += 4;
    p_actwk->patcnt &= 0x1C;
  }
  memcpy(&g_ram.colorwk2[45], &s3opening_water_color[p_actwk->patcnt], 4);
  actionsub(p_actwk);
}


/* 006dd365 */ static unsigned short s3opening_water_color[16] = {
  0xE42, 0xEC6, 0xE82, 0xEC6, 0xEC6, 0xE42, 0xEC6, 0xE82, 0xEC6, 0xE42, 0xEC6, 0xEC6, 0xEC6, 0xE42, 0xE82, 0xEC6
};


// 006dd385
static void s3bannertm_init(sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_banner_pat;
  p_actwk->sproffset = 0xE500;
  util__assign_high(&p_actwk->xposi, 392);
  util__assign_high(&p_actwk->yposi, 236);
  if (g_sonic3_alone) {
    util__assign_high(&p_actwk->yposi, 264);
  }
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 12;
  p_actwk->sprvs = 4;
  p_actwk->patno = 1;
  s3bannertm_move(p_actwk);
}


// 006dd3f9
static void s3bannertm_move(sprite_status* p_actwk) {
  if (BIT_7_IS_SET(g_ram.mdstatus) || g_sonic3_alone) {
    actionsub(p_actwk);
  }
}


// 006dd408
static void andknuckles_init(sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_andknuckles_pat;
  p_actwk->sproffset = 0xE4C0;
  util__assign_high(&p_actwk->xposi, 288);
  util__assign_high(&p_actwk->yposi, 264);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 84;
  p_actwk->sprvs = 12;
  p_actwk->r_ptr = &andknuckles_move;
}


// 006dd471
static void andknuckles_move(sprite_status* p_actwk) {
  util__assign_high(&p_actwk->yposi, LONG_HIGH(g_ram.actwk[0].yposi) + 92);
  actionsub(p_actwk);
}


// 006dd4a2
static sprite_pattern* s3opening_andknuckles_pat[1] = {
  &s3opening_andknuckles_sp00
};


static sprite_pattern s3opening_andknuckles_sp00 = {
  6,
  {
    { -12, 14, 0x0000, -84 },
    { -12, 14, 0x000C, -52 },
    { -12, 14, 0x0018, -20 },
    { -12, 14, 0x0024,  12 },
    { -12, 14, 0x0030,  44 },
    { -12,  2, 0x003C,  76 }
  }
};


// 006dd578
static void s3copyright_init(sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_selectioncopyright_pat;
  p_actwk->sproffset = 0xE6A6;
  util__assign_high(&p_actwk->xposi, 328);
  util__assign_high(&p_actwk->yposi, 330);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 12;
  p_actwk->sprvs = 4;
  p_actwk->patno = 3;
  p_actwk->r_ptr = &actionsub;
  actionsub(p_actwk);
}


// 006dd5f1
static void selection_init(sprite_status* p_actwk) {
  util__assign_high(&p_actwk->xposi, 240);
  util__assign_high(&p_actwk->yposi, 320);
  p_actwk->patbase = s3opening_selectioncopyright_pat;
  p_actwk->sproffset = 0xC680;
  g_ram.openingoption &= 1;
  p_actwk->patno = g_ram.openingoption;
  p_actwk->r_ptr = &selection_move;
  selection_move(p_actwk);
}


// 006dd650
static void selection_move(sprite_status* p_actwk) {
  unsigned char wk = g_ram.openingoption;
  unsigned short swdata = g_ram.swdata1;
  if (!g_sonic3_alone) {
    swdata |= g_ram.swdata2;
  }
  if (g_bTrial == 0 || g_sonic3_alone) {
    if (IS_BUTTON_PRESSED(swdata, PAD_U)) {
      if (wk-- == 0) {
        wk = 2;
        if (g_ram.stageselcheat == 0) {
          wk = 1;
        }
      }
    }
    if (IS_BUTTON_PRESSED(swdata, PAD_D)) {
      ++wk;
      if (g_ram.stageselcheat == 0) {
        wk &= 1;
      }
      if (wk >= 3) {
        wk = 0;
      }
    }
  }
  p_actwk->patno = wk;
  g_ram.openingoption = wk;
  if (IS_BUTTON_PRESSED(swdata, PAD_U | PAD_D)) {
    soundset(91);
  }
  actionsub(p_actwk);
}


// 006dd736
static void sonicfinger_init(sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_sonic_pat;
  p_actwk->sproffset = 0xA400;
  util__assign_high(&p_actwk->xposi, 328);
  util__assign_high(&p_actwk->yposi, 220);
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 28;
  p_actwk->r_ptr = &sonicfinger_move;
  sonicfinger_move(p_actwk);
}


// 006dd79f
static void sonicfinger_move(sprite_status* p_actwk) {
  if (!g_sonic3_alone) {
    util__assign_high(&p_actwk->yposi, 220 - g_ram.vscrolla);
  }
  patchg(p_actwk, s3opening_sonicfinger_chg);
  actionsub(p_actwk);
}


/* 006dd7e3 */ static signed char* s3opening_sonicfinger_chg[1] = {
  s3opening_sonicfinger_chg0
};


static signed char s3opening_sonicfinger_chg0[30] = {
  5, 4, 4, 4, 4, 4, 4, 0, 4, 1, 4, 0, 4, 1, 4, 0, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1
};


// 006dd804
static void sonicwink_init(sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_sonic_pat;
  p_actwk->sproffset = 0xA400;
  util__assign_high(&p_actwk->xposi, 248);
  util__assign_high(&p_actwk->yposi, 200);
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 24;
  p_actwk->r_ptr = &sonicwink_move;
  sonicwink_move(p_actwk);
}


// 006dd86d
static void sonicwink_move(sprite_status* p_actwk) {
  if (!g_sonic3_alone) {
    util__assign_high(&p_actwk->yposi, 200 - g_ram.vscrolla);
  }
  patchg2(p_actwk, s3opening_sonicwink_chg);
  actionsub(p_actwk);
}


/* 006dd8b1 */ static signed char* s3opening_sonicwink_chg[1] = {
  s3opening_sonicwink_chg0
};


static signed char s3opening_sonicwink_chg0[11] = {
  2, 1, 3, 7, 2, 5, 4, 103, 4, 47, -1
};


// 006dd8c0
static void tornado_init(sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_tornado_pat;
  p_actwk->sproffset = 0x6400;
  util__assign_high(&p_actwk->xposi, 0);
  util__assign_high(&p_actwk->yposi, 192);
  p_actwk->sprpri = PRI_7;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 8;
  p_actwk->r_ptr = &tornado_move;
  tornado_move(p_actwk);
}


// 006dd929
static void tornado_move(sprite_status* p_actwk) {
  if (SPRITE_STATUS_UCHAR(p_actwk, 48) == 0) {
    p_actwk->xposi += SHORT_TO_LONG_HIGH(1);
    if (LONG_HIGH(p_actwk->xposi) == 576) {
      SPRITE_STATUS_UCHAR(p_actwk, 48) = 1;
      SET_BIT(p_actwk->cddat1, CD_RIGHT);
      util__assign_high(&p_actwk->yposi, 208);
    }
  }
  else {
    p_actwk->xposi -= SHORT_TO_LONG_HIGH(1);
    if (LONG_HIGH(p_actwk->xposi) == 0) {
      SPRITE_STATUS_UCHAR(p_actwk, 48) = 0;
      CLEAR_BIT(p_actwk->cddat1, CD_RIGHT);
      util__assign_high(&p_actwk->yposi, 192);
    }
  }
  patchg(p_actwk, s3opening_tornado_chg);
  actionsub(p_actwk);
};


/* 006dda16 */ static signed char* s3opening_tornado_chg[1] = {
  s3opening_tornado_chg0
};


static signed char s3opening_tornado_chg0[8] = {
  1, 0, 1, 2, 3, 4, 5, -1
};


/* 006ddad4 */ static sprite_pattern* s3opening_selectioncopyright_pat[4] = {
  &s3opening_selectioncopyright_sp00,
  &s3opening_selectioncopyright_sp01,
  &s3opening_selectioncopyright_sp02,
  &s3opening_selectioncopyright_sp03
};


static sprite_pattern s3opening_selectioncopyright_sp00 = {
  7,
  {
    {  0, 12, 0x2000,   0 },
    {  0, 12, 0x2004,  32 },
    {  0, 12, 0x2008,  64 },
    { 16, 12, 0x000C,   0 },
    { 16, 12, 0x0010,  32 },
    { 16, 12, 0x0014,  64 },
    {  0,  4, 0x2024, -20 }
  }
};
static sprite_pattern s3opening_selectioncopyright_sp01 = {
  7,
  {
    {  0, 12, 0x0000,   0 },
    {  0, 12, 0x0004,  32 },
    {  0, 12, 0x0008,  64 },
    { 16, 12, 0x200C,   0 },
    { 16, 12, 0x2010,  32 },
    { 16, 12, 0x2014,  64 },
    { 16,  4, 0x2024, -20 }
  }
};
static sprite_pattern s3opening_selectioncopyright_sp02 = {
  4,
  {
    { 8, 12, 0x2018,   0 },
    { 8, 12, 0x201C,  32 },
    { 8, 12, 0x2020,  64 },
    { 8,  4, 0x2024, -20 }
  }
};
static sprite_pattern s3opening_selectioncopyright_sp03 = {
  4,
  {
    { 0, 12, 0x0000,  0 },
    { 0, 12, 0x0004, 32 },
    { 0, 12, 0x0008, 64 },
    { 0,  4, 0x000C, 96 }
  }
};


/* 006dddcc */ static sprite_pattern* s3opening_sonic_pat[5] = {
  &s3opening_sonic_sp00,
  &s3opening_sonic_sp01,
  &s3opening_sonic_sp02,
  &s3opening_sonic_sp03,
  &s3opening_sonic_sp04
};


static sprite_pattern s3opening_sonic_sp00 = {
  4,
  {
    { -28, 11, 0x0000, -24 },
    { -28, 11, 0x000C,   0 },
    {   4, 10, 0x0018, -24 },
    {   4, 10, 0x0021,   0 }
  }
};
static sprite_pattern s3opening_sonic_sp01 = {
  4,
  {
    { -28, 11, 0x002A, -24 },
    { -28, 11, 0x0036,   0 },
    {   4, 10, 0x0042, -24 },
    {   4, 10, 0x004B,   0 }
  }
};
static sprite_pattern s3opening_sonic_sp02 = {
  2,
  {
    { -24, 15, 0x0054, -16 },
    {   8, 13, 0x0064, -16 }
  }
};
static sprite_pattern s3opening_sonic_sp03 = {
  2,
  {
    { -24, 15, 0x006C, -16 },
    {   8, 13, 0x007C, -16 }
  }
};
static sprite_pattern s3opening_sonic_sp04 = {
  0,
  {}
};


/* 006dde28 */ static sprite_pattern* s3opening_tornado_pat[6] = {
  &s3opening_tornado_sp00,
  &s3opening_tornado_sp01,
  &s3opening_tornado_sp02,
  &s3opening_tornado_sp03,
  &s3opening_tornado_sp04,
  &s3opening_tornado_sp05
};


static sprite_pattern s3opening_tornado_sp00 = {
  2,
  {
    { -12, 14, 0x0084, -24 },
    { -12,  6, 0x009C,   8 }
  }
};
static sprite_pattern s3opening_tornado_sp01 = {
  2,
  {
    { -12, 14, 0x0090, -24 },
    { -12,  6, 0x00A2,   8 }
  }
};
static sprite_pattern s3opening_tornado_sp02 = {
  2,
  {
    { -12, 14, 0x0084, -24 },
    { -12,  6, 0x00A8,   8 }
  }
};
static sprite_pattern s3opening_tornado_sp03 = {
  2,
  {
    { -12, 14, 0x0090, -24 },
    { -12,  6, 0x009C,   8 }
  }
};
static sprite_pattern s3opening_tornado_sp04 = {
  2,
  {
    { -12, 14, 0x0084, -24 },
    { -12,  6, 0x00A2,   8 }
  }
};
static sprite_pattern s3opening_tornado_sp05 = {
  2,
  {
    { -12, 14, 0x0090, -24 },
    { -12, 6, 0x00A8, 8 }
  }
};


// 006dde88
static void skopening() {
  unsigned char* p_decompressed = unlze(g_ram.decompressed, skopening_bg_cg, 0);
  p_decompressed = unlze(p_decompressed, skopening_segalogo_cg, 0);
  unlze(p_decompressed, skopening_sonicfalling_cg, 0);
  copy_data_vram(g_ram.decompressed, 0, 0xE20);
  copy_data_vram(&g_ram.decompressed[0x1C40], 0x9380, 0x1640);
  unlze(&g_ram.decompressed[0x4E00], skopening_deathegg_cg, 0);
  copy_data_vram(&g_ram.decompressed[0x4E00], 0xD000, 0x720);
  unlze(&g_ram.decompressed[0x5D00], skopening_mountain_cg, 0);
  copy_data_vram(&g_ram.decompressed[0x5D00], 0xF400, 336);
  mapdevr((unsigned short*)&g_ram.decompressed[0x7400], skopening_segalogo_map, 0x849C);
  if (!(g_ram.mdstatus & 0x80)) {
    *((unsigned short*)&g_ram.decompressed[0x775C]) = 0xA49C;
    *((unsigned short*)&g_ram.decompressed[0x775E]) = 0xA49C;
    *((unsigned short*)&g_ram.decompressed[0x7760]) = 0xA49C;
    *((unsigned short*)&g_ram.decompressed[0x77AC]) = 0xA49C;
    *((unsigned short*)&g_ram.decompressed[0x77AE]) = 0xA49C;
    *((unsigned short*)&g_ram.decompressed[0x77B0]) = 0xA49C;
  }
  copy_map_vram((unsigned short*)&g_ram.decompressed[0x7400], 0xC000, 27, 39);
  mapdevr((unsigned short*)&g_ram.decompressed[0x7CC0], skopening_bg_map, 0);
  copy_bgmap_vram((unsigned short*)&g_vram[0xE000], (unsigned short*)&g_ram.decompressed[0x7CC0]);
  mapdevr((unsigned short*)&g_ram.decompressed[0x8580], skopening_frame1_map, 0x80E2);
  mapdevr((unsigned short*)&g_ram.decompressed[0x8E40], skopening_frame2_map, 0x80E2);
  mapdevr((unsigned short*)&g_ram.decompressed[0x9700], skopening_frame3_map, 0x80E2);
  mapdevr((unsigned short*)&g_ram.decompressed[0x9FC0], skopening_frame4_map, 0x80E2);
  unlze(&g_ram.decompressed[0x4800], skopening_hands_cg, 0);

  for (int line = 0; line < 4; ++line) {
    g_ram.colorwk2[line * 16] = 0;

    for (int i = 0; i < 15; ++i) {
      g_ram.colorwk2[line * 16 + i + 1] = 0xEEE;
    }
  }

  memcpy(&g_ram.colorwk2[16], &skopening_color[16], 32);
  g_ram.demotimer = 180;
  if (BIT_6_IS_SET(g_ram.mdstatus)) {
    g_ram.demotimer = 150;
  }
  fadein();
  bgmset(255);

  do {
    g_ram.int_flg = 20;
    vInt();
    if (IS_BUTTON_PRESSED(g_ram.swdata1, PAD_S)) break;
  } while (g_ram.demotimer != 0);

  bgmset(254);
  memcpy(g_ram.colorwk2, skopening_color, sizeof(skopening_color));
  unlze_moduled(&g_vram[0x1C40], skopening_sonicknuckles_cg);
  g_ram.colorcnt = 63;
  g_ram.colorcycle = 22;
  g_ram.actwk[0].r_ptr = &sonicfalling_init;
  g_ram.actwk[1].r_ptr = &deathegg_init;
  g_ram.actwk[2].r_ptr = &mountain_init;
  bgmset(37);
  g_ram.pl_suu = 3;
  g_ram.demotimer = 1080;
  if (BIT_6_IS_SET(g_ram.mdstatus)) {
    g_ram.demotimer = 900;
  }

LAB_006de36c:
  g_ram.int_flg = 26;
  vInt();
  if (g_ram.colorcycle != 0) {
    --g_ram.colorcycle;
    flashin1();
  }
  action();
  patset();
  deform_bg();
  if (!IS_BUTTON_PRESSED(g_ram.swdata1, PAD_S)) {
    if (g_ram.actwk[3].r_ptr == 0) {
      goto LAB_006de36c;
    }
    else {
      goto LAB_006de522;
    }
  }
  if (g_ram.colorcycle != 0) {
    goto LAB_006de36c;
  }

  skopeninganims_init(&g_ram.actwk[4]);
  g_ram.actwk[1].r_ptr = &deathegg_move1;
  util__assign_high(&g_ram.actwk[1].actfree.skopening_deathegg.xposi, 320);
  util__assign_high(&g_ram.actwk[1].actfree.skopening_deathegg.yposi, 112);
  g_ram.scr_evta = 3;
  g_ram.scr_shake_flg = 0;
  g_ram.vscrollb = 256;
  util__assign_high(&g_ram.scra_v_posit, 256);
  util__assign_high(&g_ram.vs_scra_v_posit, 256);
  memcpy(&g_ram.colorwk[16], skopening_knuckles_color, sizeof(skopening_knuckles_color));
  memcpy(&g_ram.colorwk2[16], skopening_knuckles_color, sizeof(skopening_knuckles_color));
  deform_bg();

LAB_006de522:
  g_ram.int_flg = 26;
  vInt();
  copy_map_vram((unsigned short*)&g_ram.decompressed[0x7CC0], 0xE000, 27, 39);
  sonicfalling_move1(&g_ram.actwk[0]);

  do {
    do {
      g_ram.int_flg = 26;
      vInt();
      if (g_ram.colorcycle != 0) {
        --g_ram.colorcycle;
        flashin1();
      }
      action();
      patset();
      deform_bg();
    } while (g_ram.actwk[5].r_ptr == 0);

    if (g_ram.demotimer == 0) {
      playskdemo();
      return;
    }
  } while (!IS_BUTTON_PRESSED(g_ram.swdata1, PAD_S));
}


/* 006de95a */ static unsigned short skopening_color[64] = {
  0x000, 0x000, 0x008, 0x00E, 0x800, 0xC00, 0xE00, 0xE20, 0xE42, 0x866, 0xAAA, 0xEEE, 0x26A, 0x48C, 0x6AE, 0xACE,
  0x000, 0xEEE, 0xEEE, 0xECC, 0xECA, 0xEC8, 0xEA6, 0xE40, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
  0x000, 0xEEE, 0xECC, 0x000, 0x000, 0x000, 0x000, 0x000, 0xECC, 0xCAA, 0xA88, 0x866, 0x644, 0x422, 0x0AE, 0x000,
  0x000, 0x08E, 0x04A, 0xE20, 0x024, 0x6EE, 0x084, 0x0E6, 0x044, 0x046, 0xEA0, 0xE64, 0xEEE, 0x0CE, 0x800, 0xE42
};
/* 006de9da */ static unsigned short skopening_knuckles_color[16] = {
  0x000, 0x000, 0x008, 0x00E, 0x0E0, 0x0CE, 0x00C, 0x20C, 0x22E, 0x866, 0xCA8, 0xEEE, 0x26A, 0x48C, 0x6AE, 0xACE
};


// 006de6f8
static void playskdemo() {
  // TODO
}


// 006de9fa
static void sonicfalling_init(sprite_status* p_actwk) {
  p_actwk->patbase = skopening_sonicfalling_pat;
  p_actwk->sproffset = 0x4EF;
  util__assign_high(&p_actwk->xposi, 232);
  util__assign_high(&p_actwk->yposi, 22);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 104;
  p_actwk->sprvs = 112;
  p_actwk->r_ptr = &sonicfalling_move0;
  sonicfalling_move0(p_actwk);
}


// 006dea63
static void sonicfalling_move0(sprite_status* p_actwk) {
  if (util__longhigh_to_short(p_actwk->yposi) != 240) {
    p_actwk->yposi += SHORT_TO_LONG_HIGH(1);
  }

  switch (g_ram.scr_evta) {
    case 3:
      p_actwk->sproffset |= 0x8000;
      if (util__longhigh_to_short(g_ram.scra_v_posit) >= 224) break;

      g_ram.scra_v_posit += SHORT_TO_LONG_HIGH(8);
      copy_mapline_vram(&g_vram[0xC000], &g_ram.decompressed[0x8580], util__longhigh_to_short(g_ram.scra_v_posit));
      // fall-through
    default:
      actionsub(p_actwk);
      return;
  }

  if (util__longhigh_to_short(g_ram.scra_v_posit) == 224) {
    copy_map_vram((unsigned short*)&g_ram.decompressed[0x8E40], 0xC000, 27, 39);
    p_actwk->pattim = 6;
    unlze_moduled(&g_vram[0x8C40], skopening_soniclanding_cg);
  }
  if (util__longhigh_to_short(g_ram.scra_v_posit) != 256) {
    g_ram.scra_v_posit += SHORT_TO_LONG_HIGH(8);
  }
  else {
    p_actwk->r_ptr = &sonicfalling_wait0;
    sonicfalling_wait0(p_actwk);
  }
}


// 006deb83
static void sonicfalling_wait0(sprite_status* p_actwk) {
  if (p_actwk->pattim-- != 0) return;

  copy_map_vram((unsigned short*)&g_ram.decompressed[0x9700], 0xC000, 27, 39);
  p_actwk->pattim = 4;
  p_actwk->r_ptr = &sonicfalling_wait1;
  sonicfalling_wait1(p_actwk);
}


// 006debdf
static void sonicfalling_wait1(sprite_status* p_actwk) {
  if (p_actwk->pattim-- != 0) return;

  sonicfalling_move1(p_actwk);
}


// 006debf9
static void sonicfalling_move1(sprite_status* p_actwk) {
  copy_map_vram((unsigned short*)&g_ram.decompressed[0x9FC0], 0xC000, 27, 39);
  unlze_moduled(&g_vram[0x9DC0], skopening_banner_cg);
  unlze_moduled(&g_vram[0x8C40], skopening_menu_cg);
  g_ram.actwk[3].r_ptr = &skbanner_init;
  g_ram.actwk[3].pattim = 30;
  p_actwk->r_ptr = 0;
}


// 006dec77
static void deathegg_init(sprite_status* p_actwk) {
  p_actwk->patbase = skopening_deathegg_pat;
  p_actwk->sproffset = 0x4680;
  util__assign_high(&p_actwk->xposi, 320);
  util__assign_high(&p_actwk->yposi, 176);
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 64;
  p_actwk->sprvs = 64;
  p_actwk->r_ptr = &deathegg_move0;
  deathegg_move0(p_actwk);
}


// 006dece0
static void deathegg_move0(sprite_status* p_actwk) {
  if (util__longhigh_to_short(p_actwk->yposi) != 240) {
    p_actwk->yposi += 0x8000;
    if (util__longhigh_to_short(g_ram.vs_scra_v_posit) != 256) {
      g_ram.vs_scra_v_posit += SHORT_TO_LONG_HIGH(1);
      copy_mapline_vram(&g_vram[0xE000], &g_ram.decompressed[0x7CC0], util__longhigh_to_short(g_ram.vs_scra_v_posit));
    }
    actionsub(p_actwk);
  }
  else {
    p_actwk->actfree.skopening_deathegg.xposi = p_actwk->xposi;
    p_actwk->actfree.skopening_deathegg.yposi = p_actwk->yposi;
    util__assign_low(&g_ram.vs_scra_v_posit, 0x8000);
    g_ram.DAT_08ffeed2 = 34;
    g_ram.scr_evta = 1;
    g_ram.scr_shake_flg = 30;
    p_actwk->r_ptr = &deathegg_move1;
    deathegg_move1(p_actwk);
  }
}


// 006dedab
static void deathegg_move1(sprite_status* p_actwk) {
  shake_screen();
  if (util__longhigh_to_short(g_ram.vs_scra_v_posit) != 256) {
    p_actwk->actfree.skopening_deathegg.yposi -= 0x8000;
    g_ram.vs_scra_v_posit += 0x8000;
    copy_mapline_vram(&g_vram[0xE000], &g_ram.decompressed[0x7CC0], util__longhigh_to_short(g_ram.vs_scra_v_posit));
  }
  short xposi = util__longhigh_to_short(p_actwk->actfree.skopening_deathegg.xposi);
  short yposi = util__longhigh_to_short(p_actwk->actfree.skopening_deathegg.yposi);
  if (g_ram.scr_shake_flg != 0) {
    xposi -= util__longhigh_to_short(g_ram.vs_scra_h_posit_copy);
    yposi -= util__longhigh_to_short(g_ram.vs_scra_v_posit_copy);
  }
  util__assign_high(&p_actwk->xposi, xposi);
  util__assign_high(&p_actwk->yposi, yposi);
  actionsub(p_actwk);
}


// 006dee8d
static void mountain_init(sprite_status* p_actwk) {
  p_actwk->patbase = skopening_mountain_pat;
  p_actwk->sproffset = 0x67A0;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 48;
  p_actwk->sprvs = 8;
  p_actwk->r_ptr = &mountain_move;
  mountain_move(p_actwk);
}


// 006deeda
static void mountain_move(sprite_status* p_actwk) {
  short xposi = 320;
  short yposi = 424;
  xposi -= util__longhigh_to_short(g_ram.vs_scra_h_posit);
  yposi -= util__longhigh_to_short(g_ram.vs_scra_v_posit);
  if (g_ram.scr_shake_flg != 0) {
    xposi -= util__longhigh_to_short(g_ram.vs_scra_h_posit_copy);
    yposi -= util__longhigh_to_short(g_ram.vs_scra_v_posit_copy);
  }
  util__assign_high(&p_actwk->xposi, xposi);
  util__assign_high(&p_actwk->yposi, yposi);
  actionsub(p_actwk);
}


// 006def76
static void skbanner_init(sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (p_actwk->pattim != 0) return;

  p_actwk->patbase = skopening_banner_pat;
  p_actwk->sproffset = 0x84EE;
  p_actwk->sprpri = PRI_0;
  p_actwk->sprhs = 124;
  p_actwk->sprvs = 40;
  util__assign_high(&p_actwk->xposi, 288);
  util__assign_high(&p_actwk->yposi, 384);
  p_actwk->yspeed = 1024;
  p_actwk->actfree.skopening_banner.yposiwk = -6291456;
  p_actwk->r_ptr = &skbanner_move;
  skbanner_move(p_actwk);
}


// 006df012
static void skbanner_move(sprite_status* p_actwk) {
  unsigned char prev_dir = p_actwk->actfree.skopening_banner.dir;
  p_actwk->actfree.skopening_banner.yposiwk += p_actwk->yspeed * 256;
  p_actwk->actfree.skopening_banner.dir = 0;
  short yspeed_add = 64;
  int compare_result = 0;
  short yposiwk_integral = util__longhigh_to_short(p_actwk->actfree.s3opening_banner.yposiwk);
  if (yposiwk_integral < 0) {
    compare_result = -1;
  }
  else if (yposiwk_integral > 0) {
    compare_result = 1;
  }

  switch (compare_result) {
    case 0:
      if (p_actwk->yspeed == -91) {
        p_actwk->r_ptr = &actionsub;
        g_ram.actwk[5].r_ptr = &nameroulette_init;
        g_ram.actwk[6].r_ptr = &chibi_init;
        g_ram.actwk[7].r_ptr = &skbannertm_init;
        g_ram.actwk[8].r_ptr = &skcopyright_init;
        bitdevr((unsigned long*)&g_vram[0xD000], DAT_006e0411, g_ram.bitdevwk);
        break;
      }
      // fall-through
    case 1:
      p_actwk->actfree.s3opening_banner.dir = 255;
      yspeed_add = -64;
      // fall-through
    case -1:
      p_actwk->yspeed += yspeed_add;
      if (prev_dir != p_actwk->actfree.s3opening_banner.dir) {
        p_actwk->yspeed /= 2;
      }
      break;
  }

  short yposi = -util__longhigh_to_short(p_actwk->actfree.s3opening_banner.yposiwk) + 280;
  util__assign_high(&p_actwk->yposi, yposi);
  actionsub(p_actwk);
}


// 006df1b3
static void skopeninganims_init(sprite_status* p_actwk) {
  copy_data_vram(&g_ram.decompressed[0x4800], 0x1C60, 48);
  copy_data_vram(&g_ram.decompressed[0x4E40], 0x1CC0, 656);
  p_actwk->actfree.skopening_anims.sonicsmile_anim[0] = 180;
  p_actwk->r_ptr = &skopeninganims_move;
  skopeninganims_move(p_actwk);
}


// 006df211
static void skopeninganims_move(sprite_status* p_actwk) {
  short offset = skopening_animate(skopening_sonicsmile_anim, p_actwk->actfree.skopening_anims.sonicsmile_anim);
  if (offset >= 0) {
    copy_data_vram(&g_ram.decompressed[0x4800 + offset], 0x1C60, 48);
  }

  offset = skopening_animate(skopening_sonicfinger_anim, p_actwk->actfree.skopening_anims.sonicfinger_anim);
  if (offset >= 0) {
    copy_data_vram(&g_ram.decompressed[0x4920 + offset], 0x1CC0, 656);
  }

  offset = skopening_animate(skopening_knuckleshand1_anim, p_actwk->actfree.skopening_anims.knuckleshand1_anim);
  if (offset >= 0) {
    copy_data_vram(&g_ram.decompressed[0x5880 + offset], 0x21E0, 752);
  }

  offset = skopening_animate(skopening_knuckleshand2_anim, p_actwk->actfree.skopening_anims.knuckleshand2_anim);
  if (offset >= 0) {
    copy_data_vram(&g_ram.decompressed[0x6A20 + offset], 0x27C0, 320);
  }
}


// 006df392
static short skopening_animate(signed char* p_animdata, unsigned char* p_currentanim) {
  if (p_currentanim[0]-- != 0) {
    return -1;
  }

  p_currentanim[0] = p_animdata[0];
  unsigned char index = p_currentanim[1];
  signed char next = p_animdata[index + 1];
  if (next < 0) {
    switch (next) {
      case -1:
        p_currentanim[1] = 0;
        next = p_animdata[1];
        break;
      case -2: {
        unsigned char rewind = p_animdata[index + 2];
        p_currentanim[1] -= rewind;
        index -= rewind;
        next = p_animdata[index + 1];
        break;
      }
      default:
        return -1;
    }
  }
  ++p_currentanim[1];
  return next * 32;
}


/* 006df4bd */ static signed char skopening_sonicsmile_anim[6] = {
  5, 0, 3, 6, -2, 1
};
/* 006df4c3 */ static signed char skopening_sonicfinger_anim[47] = {
  3, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 0, 0, 41, 82, 41, 0, 41, 82, 41, 0, 41, 82, 41, -1
};
/* 006df4f2 */ static signed char skopening_knuckleshand1_anim[17] = {
  3, 0, 0, 0, 0, 0, 0, 0, 0, 47, 94, 47, 0, 47, 94, 47, -1
};
/* 006df503 */ static signed char skopening_knuckleshand2_anim[9] = {
  3, 0, 0, 20, 40, 20, 0, 0, -1
};


// 006df50c
static void nameroulette_init(sprite_status* p_actwk) {
  compound_sprite_status* p_compoundwk = (compound_sprite_status*)p_actwk;
  p_compoundwk->xposi = 264;
  p_compoundwk->yposi = 336;
  p_actwk->actfree.skopening_nameroulette.xposi = p_compoundwk->xposi;
  p_actwk->actfree.skopening_nameroulette.yposi = p_compoundwk->yposi;
  p_actwk->patbase = skselectionpat;
  p_actwk->sproffset = 0x8462;
  SET_BIT(p_actwk->actflg, FLG_COMPOUND);

  p_compoundwk->child_cnt = 2;
  p_compoundwk->children[0].xposi = p_compoundwk->xposi;
  p_compoundwk->children[0].yposi = p_compoundwk->yposi;
  p_compoundwk->children[0].reserved = 0;
  p_compoundwk->children[0].patno = 0;
  g_ram.openingoption &= 1;
  p_actwk->direc1 = g_ram.openingoption << 7;
  p_actwk->direc2 = 8;
  p_actwk->r_ptr = &nameroulette_move;
  nameroulette_move(p_actwk);
}


// 006df638
static void nameroulette_move(sprite_status* p_actwk) {
  unsigned char optionwk = g_ram.openingoption;
  if (!(p_actwk->direc1 % 128)) {
    if (IS_BUTTON_PRESSED(g_ram.swdata1, PAD_U)) {
      p_actwk->direc1 -= 8;
      p_actwk->direc2 = -8;
      if (optionwk-- == 0) {
        optionwk = 1;
      }
    }
    if (IS_BUTTON_PRESSED(g_ram.swdata1, PAD_D)) {
      p_actwk->direc1 += 8;
      p_actwk->direc2 = 8;
      ++optionwk;
      optionwk &= 1;
      if (optionwk >= 3) {
        optionwk = 0;
      }
    }
    g_ram.openingoption = optionwk;
    if (IS_BUTTON_PRESSED(g_ram.swdata1, PAD_U | PAD_D)) {
      soundset(91);
    }
  }
  if (p_actwk->direc1 % 128) {
    p_actwk->direc1 += p_actwk->direc2;
  }
  short sin, cos;
  sinset(p_actwk->direc1 + 152, &sin, &cos);
  cos *= 5;
  sin *= 5;
  cos /= 256;
  sin /= 256;
  short cos2 = -cos, sin2 = -sin;
  cos += p_actwk->actfree.skopening_nameroulette.xposi;
  sin += p_actwk->actfree.skopening_nameroulette.yposi;
  cos2 += p_actwk->actfree.skopening_nameroulette.xposi;
  sin2 += p_actwk->actfree.skopening_nameroulette.yposi;
  unsigned char patno1 = 0;
  unsigned char patno2 = 2;
  if (p_actwk->direc1 > 64 || p_actwk->direc1 == -128) {
    short temp = cos2;
    cos2 = cos;
    cos = temp;
    temp = sin2;
    sin2 = sin;
    sin = temp;
    patno1 = 2;
    patno2 = 0;
  }
  ++patno2;
  compound_sprite_status* p_compoundwk = (compound_sprite_status*)p_actwk;
  p_compoundwk->children[0].xposi = cos;
  p_compoundwk->children[0].yposi = sin;
  p_compoundwk->children[0].patno = patno1;
  p_compoundwk->children[1].xposi = cos2;
  p_compoundwk->children[1].yposi = sin2;
  p_compoundwk->children[1].patno = patno2;
  actionsub(p_actwk);
}


// 006df99c
static void chibi_init(sprite_status* p_actwk) {
  util__assign_high(&p_actwk->xposi, 208);
  util__assign_high(&p_actwk->yposi, 332);
  p_actwk->patbase = skselectionpat;
  p_actwk->sproffset = 0x8462;
  p_actwk->mstno = g_ram.openingoption;
  p_actwk->restart = g_ram.openingoption;
  p_actwk->patcnt = 1;
  p_actwk->r_ptr = &chibi_move;
  chibi_move(p_actwk);
}


// 006dfa12
static void chibi_move(sprite_status* p_actwk) {
  p_actwk->mstno = g_ram.openingoption;
  patchg(p_actwk, chibichg);
  actionsub(p_actwk);
}


/* 006dfa34 */ static signed char* chibichg[3] = {
  chibichg0,
  chibichg1,
  chibichg2
};


static signed char chibichg0[6] = {
  7, 4, 5, 6, -2, 2
};
static signed char chibichg1[6] = {
  7, 4, 7, 8, -2, 2
};
static signed char chibichg2[3] = {
  7, 4, -1
};


// 006dfa4c
static void skbannertm_init(sprite_status* p_actwk) {
  p_actwk->patbase = skopening_bannertm_pat;
  p_actwk->sproffset = 0x8462;
  util__assign_high(&p_actwk->xposi, 418);
  util__assign_high(&p_actwk->yposi, 285);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 4;
  p_actwk->r_ptr = &skbannertm_move;
  skbannertm_move(p_actwk);
}


// 006dfab5
static void skbannertm_move(sprite_status* p_actwk) {
  if (g_ram.mdstatus & 0x80) {
    actionsub(p_actwk);
  }
}


// 006dfac4
static void skcopyright_init(sprite_status* p_actwk) {
  p_actwk->patbase = skopening_copyright_pat;
  p_actwk->sproffset = 0x8680;
  util__assign_high(&p_actwk->xposi, 327);
  util__assign_high(&p_actwk->yposi, 344);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 44;
  p_actwk->sprvs = 4;
  p_actwk->r_ptr = &actionsub;
  actionsub(p_actwk);
}


// 006dfb32
static void copy_mapline_vram(unsigned char* p_destination, unsigned char* p_source, short offset) {
  if ((offset -= 16) < 0) return;
  if (offset & 7) return;

  offset &= 0xF8;
  memcpy(&p_destination[offset * 16], &p_source[offset * 10], 80);
}


// 006dfc23
static void copy_bgmap_vram(unsigned short* p_destination, unsigned short* p_source) {
  for (int i = 0; i < 32; ++i) {
    memcpy(p_destination, p_source, 80);
    p_destination += 64;
  }
}


// 006dfd27
static void shake_screen() {
  if (g_ram.scr_shake_flg == 0) return;

  --g_ram.scr_shake_flg;
  if (g_ram.scr_shake_flg == 0) {
    ++g_ram.scr_evta;
  }
  unsigned short counter = g_ram.systemtimer & 0x3F;
  util__assign_high(&g_ram.vs_scra_v_posit_copy, shakeoffsets[counter]);
  util__assign_high(&g_ram.vs_scra_v_posit_copy, shakeoffsets[counter + 1]);
}


// 006dfddb
static void deform_bg() {
  g_ram.vscrolla = util__longhigh_to_short(g_ram.scra_v_posit);
  g_ram.vscrollb = util__longhigh_to_short(g_ram.vs_scra_v_posit);
  short scra_h_posit = 0;
  if (g_ram.scr_shake_flg != 0) {
    g_ram.vscrolla += util__longhigh_to_short(g_ram.vs_scra_v_posit_copy);
    g_ram.vscrollb += util__longhigh_to_short(g_ram.vs_scra_v_posit_copy);
    scra_h_posit = g_ram.vs_scra_h_posit_copy;
  }

  switch (g_ram.scr_evta) {
    case 1:
      scra_h_posit += g_ram.vs_scra_h_posit;
      scra_h_posit = -scra_h_posit;

      for (int i = 0; i < 112; ++i) {
        unsigned long value = random();
        g_ram.hscrollbuff[i * 4] = value & 0x00000007;
        g_ram.hscrollbuff[i * 4 + 1] = scra_h_posit;
        g_ram.hscrollbuff[i * 4 + 2] = -((value & 0x00070000) >> 16);
        g_ram.hscrollbuff[i * 4 + 3] = scra_h_posit;
      }
      break;
    case 2:
      if (--g_ram.DAT_08ffeed2 == 0) {
        ++g_ram.scr_evta;
        memset(&g_vram[0xC500], 0, 256);
        memcpy(&g_ram.colorwk[16], skopening_knuckles_color, sizeof(skopening_knuckles_color));
        g_ram.actwk[4].r_ptr = &skopeninganims_init;
        scra_h_posit = 0;
      }
      else {
        scra_h_posit = util__longhigh_to_short(g_ram.vs_scra_h_posit);
        scra_h_posit = -scra_h_posit;

        for (int i = 0; i < 112; ++i) {
          unsigned long value = random();
          g_ram.hscrollbuff[i * 4] += 8;
          g_ram.hscrollbuff[i * 4] += value & 0x00000007;
          if (g_ram.hscrollbuff[i * 4] >= 252) {
            g_ram.hscrollbuff[i * 4] = 252;
          }
          g_ram.hscrollbuff[i * 4 + 1] = scra_h_posit;
          g_ram.hscrollbuff[i * 4 + 2] -= 8;
          g_ram.hscrollbuff[i * 4 + 2] -= (value & 0x00070000) >> 16;
          if (g_ram.hscrollbuff[i * 4 + 2] <= -260) {
            g_ram.hscrollbuff[i * 4 + 2] = -260;
          }
          g_ram.hscrollbuff[i * 4 + 3] = scra_h_posit;
          break;
        }
      }
      // fall-through
    default: {
      short hscrolla = -(util__longhigh_to_short(g_ram.scra_h_posit) + scra_h_posit);
      short hscrollb = -(util__longhigh_to_short(g_ram.vs_scra_h_posit) + scra_h_posit);

      for (int i = 0; i < 224; ++i) {
        g_ram.hscrollbuff[i * 2] = hscrolla;
        g_ram.hscrollbuff[i * 2 + 1] = hscrollb;
      }
    }
  }
}


/* 006e0241 */ static unsigned char shakeoffsets[66] = {
  1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3, 1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3, 1, 2
};


/* 006e0284 */ static sprite_pattern* skselectionpat[9] = {
  &skselectionsp00,
  &skselectionsp01,
  &skselectionsp02,
  &skselectionsp03,
  &skselectionsp04,
  &skselectionsp05,
  &skselectionsp06,
  &skselectionsp07,
  &skselectionsp08
};


static sprite_pattern skselectionsp00 = {
  2,
  {
    { -8, 13, 0x0000, -36 },
    { -8, 13, 0x0008,  -4 }
  }
};
static sprite_pattern skselectionsp01 = {
  2,
  {
    { -8, 13, 0x0010, -36 },
    { -8, 13, 0x0018,  -4 }
  }
};
static sprite_pattern skselectionsp02 = {
  4,
  {
    { -9, 13, 0x2020, -37 },
    { -9, 13, 0x2028,  -5 },
    { -9, 13, 0x2030,  27 },
    { -9,  1, 0x2038,  59 }
  }
};
static sprite_pattern skselectionsp03 = {
  4,
  {
    { -9, 13, 0x203A, -37 },
    { -9, 13, 0x2042,  -5 },
    { -9, 13, 0x204A,  27 },
    { -9,  1, 0x2052,  59 }
  }
};
static sprite_pattern skselectionsp04 = {
  1,
  {
    { -12, 10, 0x0066, -12 }
  }
};
static sprite_pattern skselectionsp05 = {
  1,
  {
    { -12, 10, 0x0054, -12 }
  }
};
static sprite_pattern skselectionsp06 = {
  1,
  {
    { -12, 10, 0x005D, -12 }
  }
};
static sprite_pattern skselectionsp07 = {
  1,
  {
    { -12, 10, 0x206F, -12 }
  }
};
static sprite_pattern skselectionsp08 = {
  1,
  {
    { -12, 10, 0x2078, -12 }
  }
};


/* 006e030e */ static sprite_pattern* skopening_bannertm_pat[1] = {
  &skopening_bannertm_sp00
};


static sprite_pattern skopening_bannertm_sp00 = {
  1,
  {
    { -4, 4, 0x008A, -8 }
  }
};


/* 006e0318 */ static sprite_pattern* skopening_copyright_pat[1] = {
  &skopening_copyright_sp00
};


static sprite_pattern skopening_copyright_sp00 = {
  6,
  {
    { 0,  0, 0x0000,   0 },
    { 0,  8, 0x0001,   8 },
    { 0,  4, 0x0004,  32 },
    { 0,  8, 0x0001,  48 },
    { 0, 12, 0x0006,  72 },
    { 0,  4, 0x000A, 104 }
  }
};


/* 006e0340 */ static unsigned char DAT_006e0340[209] = { 0x0e, 0x80, 0x80, 0x02, 0x00, 0x14, 0x08, 0x24, 0x0b, 0x35, 0x1b, 0x47, 0x7c, 0x55, 0x1c, 0x74, 0x0a, 0x8e, 0x03, 0x02, 0x14, 0x09, 0x25, 0x1a, 0x34, 0x0c, 0x45, 0x1e, 0x8f, 0x03, 0x03, 0x15, 0x1d, 0x27, 0x7d, 0xff, 0x1f, 0xec, 0x58, 0xff, 0xbc, 0xe4, 0x92, 0x63, 0x55, 0xf3, 0x57, 0x24, 0x92, 0xff, 0xbc, 0xe3, 0x5f, 0x81, 0x77, 0x36, 0xe1, 0x71, 0xd7, 0xf8, 0x1d, 0xbd, 0xa1, 0x7c, 0xd5, 0xbe, 0x33, 0x0e, 0xa2, 0x45, 0x50, 0x89, 0xf9, 0xad, 0xe0, 0xa3, 0xc3, 0xa8, 0xc1, 0x88, 0x91, 0x54, 0x22, 0x7e, 0x6b, 0x78, 0x28, 0xf1, 0xdb, 0xfb, 0x12, 0x7d, 0xf9, 0x35, 0x43, 0xb5, 0x0a, 0x35, 0x0a, 0x3a, 0x48, 0xef, 0xe9, 0xde, 0x4f, 0x11, 0xfb, 0xf1, 0xdc, 0xd4, 0x38, 0x6b, 0x68, 0x72, 0xe2, 0x4f, 0xc0, 0xb1, 0xf1, 0x9a, 0xda, 0x26, 0xb6, 0x89, 0x1d, 0xe5, 0xfa, 0xf2, 0xde, 0xd1, 0xd3, 0x42, 0x84, 0x4d, 0x6d, 0x13, 0xf3, 0x42, 0x8f, 0x0c, 0xca, 0x43, 0x30, 0x51, 0x97, 0xd8, 0x5c, 0x55, 0x0b, 0x88, 0x77, 0x30, 0xe3, 0xec, 0xd7, 0xf8, 0x17, 0x10, 0xf8, 0xea, 0xb9, 0xfe, 0xf1, 0x9e, 0x62, 0x32, 0x11, 0xa8, 0x66, 0x84, 0x3a, 0xc1, 0x47, 0x8e, 0xf3, 0xa7, 0xa1, 0x19, 0xbc, 0xde, 0x54, 0x23, 0x06, 0x7a, 0xba, 0x79, 0x88, 0xcf, 0x9a, 0xf8, 0xab, 0x68, 0x9b, 0x67, 0xa3, 0xb1, 0xf6, 0x1a, 0xa4, 0xed, 0xaa, 0x42, 0x7b, 0x5b, 0x68, 0x91, 0x44, 0xc4, 0x80 };


/* 006e0411 */ static unsigned char DAT_006e0411[183] = { 0x0c, 0x80, 0x80, 0x02, 0x00, 0x14, 0x09, 0x25, 0x1b, 0x35, 0x1a, 0x44, 0x0b, 0x55, 0x1d, 0x68, 0xfb, 0x74, 0x0a, 0x81, 0x03, 0x03, 0x16, 0x3c, 0x37, 0x7c, 0x8a, 0x03, 0x02, 0x14, 0x08, 0x25, 0x1c, 0x34, 0x0c, 0x46, 0x3d, 0x58, 0xfa, 0xff, 0x1f, 0xee, 0xd8, 0xfe, 0x9c, 0x10, 0x44, 0xf2, 0xaf, 0x9b, 0x82, 0x08, 0x7f, 0x4e, 0x79, 0xf8, 0xb7, 0xb8, 0xdb, 0x95, 0xd7, 0x5f, 0x6f, 0x6f, 0x48, 0x57, 0xcd, 0xbe, 0xb3, 0x0f, 0x11, 0x02, 0xa9, 0x44, 0x5f, 0x35, 0x82, 0x9f, 0x47, 0x4c, 0xc1, 0x88, 0x81, 0x54, 0xa2, 0x2f, 0x9a, 0xc1, 0x4f, 0xa3, 0xbf, 0x37, 0x07, 0xe8, 0x6e, 0x2a, 0x87, 0xb5, 0x2a, 0x79, 0x28, 0xfd, 0x09, 0x03, 0xdf, 0xca, 0xa3, 0xe5, 0xc5, 0x5b, 0x5d, 0x70, 0xed, 0x1f, 0xc1, 0x3e, 0xa7, 0x37, 0xe4, 0xa1, 0x69, 0x08, 0x7d, 0x75, 0xa8, 0xbf, 0xe8, 0xdb, 0x17, 0x57, 0xda, 0xeb, 0x15, 0xba, 0x8e, 0xc7, 0xc1, 0xce, 0x78, 0x7b, 0x28, 0xe5, 0xc0, 0xab, 0x50, 0x29, 0x47, 0x0f, 0x05, 0xa7, 0xbc, 0x19, 0xec, 0xa3, 0x35, 0x95, 0xac, 0x94, 0x60, 0xc5, 0xa6, 0x79, 0x8e, 0x5e, 0x5f, 0x25, 0xa1, 0x57, 0x63, 0x6d, 0x19, 0x31, 0x3f, 0xd1, 0x54, 0x9d, 0x5a, 0x13, 0xd2, 0xfb, 0x81, 0x76, 0x34 };


// 006e69e7
static void plays3demo() {
  soundset(225);
  g_ram.demoid = g_ram.nextdemoid;
  short stageno = s3demostagenos[g_ram.nextdemoid & 7];
  g_ram.stageno = stageno;
  g_ram.stageno_i = stageno;
  g_ram.stageno_s = stageno;
  ++g_ram.nextdemoid;
  if (g_ram.nextdemoid >= 3) {
    g_ram.nextdemoid = 0;
  }
  g_ram.demoflag = 1;
  g_ram.gmmode = 8;
  g_ram.pl_suu = 3;
  g_ram.pl2_suu = 3;
  g_ram.plring = 0;
  g_ram.pltime.hours = 0;
  g_ram.pltime.minutes = 0;
  g_ram.pltime.seconds = 0;
  g_ram.pltime.frames = 0;
  g_ram.plscore = 0;
  g_ram.pl2ring = 0;
  g_ram.DAT_08fffed2 = 0;
  g_ram.DAT_08fffed6 = 0;
  g_ram.extrascore = 5000;
  g_ram.extrascore2 = 5000;
}


/* 006e6b0f */ static short s3demostagenos[3] = {
  ANGEL_ISLAND_ACT_1,
  HYDROCITY_ACT_1,
  MARBLE_GARDEN_ACT_1
};


/* 0082dd20 */ static void* s3opening_datalist[42] = {
  s3opening_frame1_cg,
  s3opening_frame1_color,
  &s3opening_frame1_map,
  s3opening_frame1_cg,
  s3opening_frame2_color,
  &s3opening_frame2_map,
  s3opening_frame1_cg,
  s3opening_frame3_color,
  &s3opening_frame3_map,
  s3opening_frame1_cg,
  s3opening_frame4_color,
  &s3opening_frame4_map,
  s3opening_frame1_cg,
  s3opening_frame5_color,
  &s3opening_frame5_map,
  s3opening_frame1_cg,
  s3opening_frame6_color,
  &s3opening_frame6_map,
  s3opening_frame1_cg,
  s3opening_frame7_color,
  &s3opening_frame7_map,
  s3opening_frame8_cg,
  s3opening_frame8_color,
  &s3opening_frame8_map,
  s3opening_frame9_cg,
  s3opening_frame9_color,
  &s3opening_frame9_map,
  s3opening_frame10_cg,
  s3opening_frame10_color,
  &s3opening_frame10_map,
  s3opening_frame11_cg,
  s3opening_frame11_color,
  &s3opening_frame11_map,
  s3opening_frame12_cg,
  s3opening_frame12_color,
  &s3opening_frame12_map,
  s3opening_frame13_cg,
  s3opening_frame13_color,
  &s3opening_frame13_map,
  s3opening_frame13_cg,
  s3opening_frame14_color,
  &s3opening_frame14_map
};
