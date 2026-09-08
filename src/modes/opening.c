#include "opening.h"
#include <string.h>
#include "../data/cg/opening.h"
#include "../data/map/opening.h"
#include "../data/pat/opening.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/direction.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../color.h"
#include "../constants.h"
#include "../dev.h"
#include "../etc.h"
#include "../io.h"
#include "../sound.h"
static void s3opening(void);
static void play_demo(void);
static void load_frames(void);
static unsigned short s3transition_color[8][7];
static unsigned short s3frame1_color[32];
static unsigned short s3frame2_color[32];
static unsigned short s3frame3_color[32];
static unsigned short s3frame4_color[32];
static unsigned short s3frame5_color[32];
static unsigned short s3frame6_color[32];
static unsigned short s3frame7_color[32];
static unsigned short s3frame8_color[32];
static unsigned short s3frame9_color[32];
static unsigned short s3frame10_color[32];
static unsigned short s3frame11_color[32];
static unsigned short s3frame12_color[32];
static unsigned short s3frame13_color[32];
static unsigned short s3frame14_color[32];
static unsigned short s3opening_color[64];
static void s3banner_init(SKC_sprite_status* p_actwk);
static void s3banner_move0(SKC_sprite_status* p_actwk);
static void s3banner_move1(SKC_sprite_status* p_actwk);
static void s3bannertm_init(SKC_sprite_status* p_actwk);
static void s3bannertm_move(SKC_sprite_status* p_actwk);
static void andknuckles_init(SKC_sprite_status* p_actwk);
static void andknuckles_move(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern* andknuckles_pt[1];
static SKC_sprite_pattern andknuckles_pt00;
static void s3copyright_init(SKC_sprite_status* p_actwk);
static void s3selection_init(SKC_sprite_status* p_actwk);
static void s3selection_move(SKC_sprite_status* p_actwk);
static void sonichand_init(SKC_sprite_status* p_actwk);
static void sonichand_move(SKC_sprite_status* p_actwk);
static signed char* s3opening_sonichand_chg[1];
static signed char s3opening_sonichand_chg0[30];
static void soniceye_init(SKC_sprite_status* p_actwk);
static void soniceye_move(SKC_sprite_status* p_actwk);
static signed char* soniceye_chg[1];
static signed char soniceye_chg0[11];
static void tornado_init(SKC_sprite_status* p_actwk);
static void tornado_move(SKC_sprite_status* p_actwk);
static signed char* tornado_chg[1];
static signed char tornado_chg0[8];
static SKC_sprite_pattern* s3selectioncopyright_pt[4];
static SKC_sprite_pattern s3selectioncopyright_pt00;
static SKC_sprite_pattern s3selectioncopyright_pt01;
static SKC_sprite_pattern s3selectioncopyright_pt02;
static SKC_sprite_pattern s3selectioncopyright_pt03;
static unsigned char text_cg[609];
static SKC_sprite_pattern* sonicparts_pt[5];
static SKC_sprite_pattern sonicparts_pt00;
static SKC_sprite_pattern sonicparts_pt01;
static SKC_sprite_pattern sonicparts_pt02;
static SKC_sprite_pattern sonicparts_pt03;
static SKC_sprite_pattern sonicparts_pt04;
static SKC_sprite_pattern* tornado_pt[6];
static SKC_sprite_pattern tornado_pt00;
static SKC_sprite_pattern tornado_pt01;
static SKC_sprite_pattern tornado_pt02;
static SKC_sprite_pattern tornado_pt03;
static SKC_sprite_pattern tornado_pt04;
static SKC_sprite_pattern tornado_pt05;
static void skopening(void);
static void demo0700_init(unsigned short stageno);
static unsigned short skopening_color[64];
static unsigned short knuckles_color[16];
static void sonicfalling_init(SKC_sprite_status* p_actwk);
static void sonicfalling_move0(SKC_sprite_status* p_actwk);
static void sonicfalling_wait0(SKC_sprite_status* p_actwk);
static void sonicfalling_wait1(SKC_sprite_status* p_actwk);
static void sonicfalling_move1(SKC_sprite_status* p_actwk);
static void dummy(SKC_sprite_status* p_actwk);
static void deathegg_init(SKC_sprite_status* p_actwk);
static void deathegg_move0(SKC_sprite_status* p_actwk);
static void deathegg_move1(SKC_sprite_status* p_actwk);
static void mountain_init(SKC_sprite_status* p_actwk);
static void mountain_move(SKC_sprite_status* p_actwk);
static void skbanner_init(SKC_sprite_status* p_actwk);
static void skbanner_move(SKC_sprite_status* p_actwk);
static void skopening_cg_chg_init(SKC_sprite_status* p_actwk);
static void skopening_cg_chg_move(SKC_sprite_status* p_actwk);
static short skopening_cg_chg_sub(signed char* p_chg, unsigned char* p_tim, unsigned char* p_cnt);
static signed char sonicmouth_chg[6];
static signed char skopening_sonichand_chg[47];
static signed char knuckleshand1_chg[17];
static signed char knuckleshand2_chg[9];
static void skselection_init(SKC_sprite_status* p_actwk);
static void skselection_move(SKC_sprite_status* p_actwk);
static void chibi_init(SKC_sprite_status* p_actwk);
static void chibi_move(SKC_sprite_status* p_actwk);
static signed char* chibi_chg[3];
static signed char chibi_chg0[6];
static signed char chibi_chg1[6];
static signed char chibi_chg2[3];
static void skbannertm_init(SKC_sprite_status* p_actwk);
static void skbannertm_move(SKC_sprite_status* p_actwk);
static void skcopyright_init(SKC_sprite_status* p_actwk);
static void copy_mapline_vram(unsigned char* p_source, unsigned short offset, short line_cnt);
static void shake_screen(void);
static void skopening_scroll(void);
static unsigned char shakeoffset_tbl[66];
static SKC_sprite_pattern* skselection_pt[9];
static SKC_sprite_pattern skselection_pt00;
static SKC_sprite_pattern skselection_pt01;
static SKC_sprite_pattern skselection_pt02;
static SKC_sprite_pattern skselection_pt03;
static SKC_sprite_pattern skselection_pt04;
static SKC_sprite_pattern skselection_pt05;
static SKC_sprite_pattern skselection_pt06;
static SKC_sprite_pattern skselection_pt07;
static SKC_sprite_pattern skselection_pt08;
static SKC_sprite_pattern* skbannertm_pt[1];
static SKC_sprite_pattern skbannertm_pt00;
static SKC_sprite_pattern* skcopyright_pt[1];
static SKC_sprite_pattern skcopyright_pt00;
static unsigned char s3copyright1997_cg[209];
static unsigned char skcopyright1997_cg[183];

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];
extern int g_sonic3_alone;
extern unsigned long g_vdp_scrolla_adr;
extern unsigned long g_vdp_scrollb_adr;
extern int g_vdp_hscroll_scanline;
extern unsigned long g_bg_color_index;
extern void v_int(void);

static unsigned char mapa[2240];
static unsigned char mapb[2240];
static unsigned char cg_chg_cg[0x29A0];


void opening(void) {
  bgmset(-31);
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
  memset(g_ram.actwk, 0, sizeof(g_ram.actwk));
  g_ram.foxcpu_ride_obj = 0;
  g_ram.foxcpu_timer = 0;
  g_ram.fox_appear_timer = 0;
  g_ram.foxcpu_rno = 0;
  g_ram.foxcpu_movexposi = 0;
  g_ram.foxcpu_moveyposi = 0;
  g_ram.DAT_08fff70e = 0;
  g_ram.DAT_08fff70f = 0;
  g_ram.ringactset_rno = 0;
  g_ram.DAT_08fff711 = 0;
  g_ram.DAT_08fff72e = 0;
  g_ram.watermode = 0;
  g_ram.miles_carry_flag = 0;
  g_ram.miles_nograb_timer = 0;
  g_ram.zoom_pat_cnt = 0;
  g_ram.foxxspeed = 0;
  g_ram.markno_s = 0;
  // DAT_08fff748
  // DAT_08fff749
  g_ram.DAT_08fff74a = 0;
  g_ram.DAT_08fff74b = 0;
  g_ram.foxyspeed = 0;
  memset(&g_ram.glide_flag, 0, sizeof(g_ram.glide_flag));
  g_ram.plmaxspdwk = 0;
  g_ram.pladdspdwk = 0;
  g_ram.plretspdwk = 0;
  g_ram.playpatno = 0;
  memset(g_ram.dirstk, 0, sizeof(g_ram.dirstk));
  g_ram.actset_rno = 0;
  g_ram.asetposi = 0;
  g_ram.asetposi2 = 0;
  g_ram.asetadr = 0;
  g_ram.asetadr2 = 0;
  g_ram.flagworkcnt = 0;
  g_ram.flagworkcnt2 = 0;
  // DAT_08fff794
  g_ram.scdadr = 0;
  g_ram.bossstart = 0;
  // DAT_08fff7b0
  // DAT_08fff7b1
  // DAT_08fff7b2
  // DAT_08fff7b3
  g_ram.scd0adr = 0;
  g_ram.scd1adr = 0;
  // DAT_08fff7c0
  g_ram.DAT_08fff7c1 = 0;
  // DAT_08fff7c2
  g_ram.soz_darkness_level = 0;
  // DAT_08fff7c4
  // DAT_08fff7c5
  g_ram.reverse_gravity_flag = 0;
  // DAT_08fff7c7
  g_ram.watercoliflag = 0;
  g_ram.watercoliflag2 = 0;
  g_ram.pl_input_lock_flag = 0;
  g_ram.pl2_input_lock_flag = 0;
  g_ram.emyscorecnt = 0;
  g_ram.timebonus = 0;
  g_ram.ringbonus = 0;
  g_ram.sc1ahposit = 0;
  g_ram.foxpatno = 0;
  g_ram.foxtailspatno = 0;
  memset(g_ram.stage_triggers, 0, sizeof(g_ram.stage_triggers));
  memset(g_ram.cgchgtim, 0, sizeof(g_ram.cgchgtim));
  memset(g_ram.cgchgcnt, 0, sizeof(g_ram.cgchgcnt));
  memset(g_ram.waterlinecgchgcnt, 0, sizeof(g_ram.waterlinecgchgcnt));
  g_ram.cgchg14cnt = 0;
  g_ram.cgchg14cnt2 = 0;
  g_ram.scra_hz = 0;
  g_ram.scra_vz = 0;
  g_ram.scra_hz2 = 0;
  g_ram.scra_vz2 = 0;
  // DAT_08ffee08
  g_ram.pl_scr_lock_flag = 0;
  g_ram.pl2_scr_lock_flag = 0;
  g_ram.scralim_n_down = 0;
  g_ram.scralim_left = 0;
  g_ram.scralim_right = 0;
  g_ram.scralim_up = 0;
  g_ram.scralim_down = 0;
  // DAT_08ffee1c
  // DAT_08ffee1e
  // DAT_08ffee20
  // DAT_08ffee22
  g_ram.DAT_08ffee24 = 0;
  g_ram.plposiwkadr = 0;
  g_ram.DAT_08ffee28 = 0;
  g_ram.pl2posiwkadr = 0;
  g_ram.scra_vline = 0;
  g_ram.scra_vline2 = 0;
  g_ram.scroll_start = 0;
  // DAT_08ffee32
  g_ram.zone_flag = 0;
  g_ram.fast_scroll_flag = 0;
  g_ram.vs_vscroll = 0;
  g_ram.scr_h_posit_ofs = 0;
  g_ram.scr_v_posit_ofs = 0;
  memset(&g_ram.ringactadr, 0, sizeof(g_ram.ringactadr));
  memset(&g_ram.ringactadr2, 0, sizeof(g_ram.ringactadr2));
  g_ram.ringwkadr = 0;
  g_ram.stageno_i = 0;
  g_ram.fadecnt = 0;
  // DAT_08ffee52
  // DAT_08ffee56
  // DAT_08ffee5a
  // DAT_08ffee5c
  // DAT_08ffee5d
  g_ram.notitle = 0;
  g_ram.vs_scra_h_posit = 0;
  g_ram.vs_scra_v_posit = 0;
  g_ram.vs_scra_h_posit_copy = 0;
  g_ram.vs_scra_v_posit_copy = 0;
  g_ram.vs_scrb_h_posit = 0;
  g_ram.vs_scrb_v_posit = 0;
  g_ram.scra_h_posit = 0;
  g_ram.scra_v_posit = 0;
  g_ram.scra_h_posit_copy = 0;
  g_ram.scra_v_posit_copy = 0;
  // DAT_08ffee88
  // DAT_08ffee8a
  g_ram.scrb_h_posit = 0;
  g_ram.scrb_v_posit = 0;
  // DAT_08ffee94
  // DAT_08ffee96
  // DAT_08ffee98
  g_ram.DAT_08ffee9c = 0;
  // DAT_08ffeea0
  // DAT_08ffeea2
  // DAT_08ffeea3
  // DAT_08ffeea4
  g_ram.vint_rno = 0;
  g_ram.scrc3 = 0;
  g_ram.scrc_v = 0;
  // DAT_08ffeeac
  g_ram.scr_row = 0;
  // DAT_08ffeeb0
  // DAT_08ffeeb1
  // DAT_08ffeeb2
  // DAT_08ffeeb4
  g_ram.DAT_08ffeeb6 = 0;
  // DAT_08ffeeb8
  g_ram.frame_offset_x = 0;
  // DAT_08ffeebe
  // DAT_08ffeebf
  g_ram.scr_evta = 0;
  // DAT_08ffeec2
  g_ram.DAT_08ffeec4 = 0;
  g_ram.event_flag_3 = 0;
  // DAT_08ffeec8
  // DAT_08ffeeca
  g_ram.scr_shake_flg = 0;
  // DAT_08ffeece
  // DAT_08ffeed0
  g_ram.DAT_08ffeed2 = 0;
  // DAT_08ffeed4
  // DAT_08ffeed6
  // DAT_08ffeed8
  // DAT_08ffeeda
  g_ram.DAT_08ffeedb = 0;
  // DAT_08ffeedc
  // DAT_08ffeede
  // DAT_08ffeedf
  // DAT_08ffeee0
  g_ram.DAT_08ffeee2 = 0;
  g_ram.DAT_08ffeee4 = 0;
  g_ram.DAT_08ffeee6 = 0;
  g_ram.DAT_08ffeee8 = 0;
  memset(g_ram.vscrollbuff, 0, sizeof(g_ram.vscrollbuff));
  g_ram.sprhmasks = 0;
  g_ram.sprtbl_pageflip = 0;
  g_ram.sprtbl_pageready = 0;
  // DAT_08ffef40
  // DAT_08ffef44
  // DAT_08ffef48
  // DAT_08ffef49
  // DAT_08ffef4a
  g_ram.dataselect_selection = 0;
  g_ram.nosave_play_type = 0;
  // DAT_08ffef4e
  // DAT_08ffef50
  // DAT_08ffef52
  g_ram.act_tbl_ptr = 0;
  g_ram.plring_s3 = 0;
  memset(&g_ram.pltime_s3, 0, sizeof(g_ram.pltime_s3));
  g_ram.scr_y_no = 0;
  g_ram.scr_shake_flg2 = 0;
  // DAT_08ffef68
  // DAT_08ffef6a
  // DAT_08ffef6c
  // DAT_08ffef6e
  g_ram.demoid = 0;
  memset(g_ram.ringbuffer, 0, sizeof(g_ram.ringbuffer));
  sprtblinit2();
  memset(g_ram.colorwk, 0, sizeof(g_ram.colorwk));
  memset(g_ram.colorwk2, 0, sizeof(g_ram.colorwk2));
  g_ram.markerno = 0;
  g_ram.marker_flag = 0;
  g_ram.editmode = 0;
  g_ram.demoflag = 0;
  g_ram.clchgtim = 0;
  g_ram.clchgcnt = 0;
  g_ram.vs_flag = 0;
  g_ram.DAT_08fff711 = 0;
  g_ram.debugflag = 0;
  g_ram.editmodecheatcnt = 0;
  g_ram.allemeraldscheatcnt = 0;
  if (!g_sonic3_alone) {
    g_ram.bsmode = 0;
  }
  g_ram.demotimer = 359;
  if (g_ram.cartridge == 0) {
    s3opening();
  }
  else {
    skopening();
  }
}


static void s3opening(void) {
  unlze(g_vram, s3opening_frame1_cg);
  unsigned char map[2240] = { 0 };
  mapdevr(map, s3opening_frame1_map, 0);
  if (!g_sonic3_alone && !BIT_IS_SET(g_ram.mdstatus, 7)) {
    memset(&map[940], 0, 4);
  }
  copy_map_vram(map, g_vdp_scrolla_adr, 40, 28);
  memcpy(g_ram.colorwk2, s3frame1_color, sizeof(unsigned short) * 16);
  g_ram.demotimer = 240;
  fadein();
  bgmset(-1);
  g_ram.demotimer = 180;

  do {
    g_ram.int_flg = 20;
    v_int();
  }
  while (g_ram.swdata1.pressed.s == 0 && g_ram.demotimer != 0);

  bgmset(-2);
  int i = 0;

  do {
    g_ram.int_flg = 2;
    v_int();
    memcpy(&g_ram.colorwk[i * 7], s3transition_color[i], sizeof(s3transition_color[i]));
    ++i;
  }
  while (g_ram.colorwk[(i - 1) * 7] != 0);

  bgmset(37);
  load_frames();
  g_ram.demotimer = 750;

  for (int i = 0; i < 64; ++i) {
    g_ram.colorwk[i] = 0xEEE;
  }

  g_ram.int_flg = 4;
  v_int();
  unlze(g_vram, s3opening_frame13_cg);
  mapdevr(map, s3opening_frame13_map, 0x8000);
  copy_map_vram(map, g_vdp_scrolla_adr, 40, 28);
  mapdevr(map, s3opening_frame14_map, 0x4000);
  copy_map_vram(map, g_vdp_scrollb_adr, 40, 28);
  g_ram.int_flg = 4;
  v_int();
  memcpy(g_ram.colorwk2, s3opening_color, sizeof(s3opening_color));
  bitdevr(&g_vram[0xA000], s3opening_banner_cg);
  bitdevr(&g_vram[0xD000], text_cg);
  bitdevr(&g_vram[0xD4C0], s3copyright1997_cg);
  bitdevr(&g_vram[0x8000], s3opening_sonic_cg);
  if (!g_sonic3_alone) {
    bitdevr(&g_vram[0x9800], andknuckles_cg);
  }
  g_ram.actwk[0].r_ptr = &s3banner_init;
  g_ram.actwk[1].r_ptr = &s3selection_init;
  g_ram.actwk[3].r_ptr = &s3copyright_init;
  g_ram.actwk[4].r_ptr = &sonichand_init;
  g_ram.actwk[5].r_ptr = &soniceye_init;
  g_ram.actwk[6].r_ptr = &tornado_init;
  if (!g_sonic3_alone) {
    g_ram.actwk[7].r_ptr = &andknuckles_init;
  }
  if (g_sonic3_alone) {
    divdevset(0);
  }

  do {
    g_ram.int_flg = 4;
    v_int();
    action();
    patset();
    if (g_ram.actwk[2].r_ptr != 0) {
      if (g_ram.demotimer == 0) {
        play_demo();
      }
      else if (g_ram.swdata1.pressed.s == 1 || (!g_sonic3_alone && g_ram.swdata2.pressed.s == 1)) {
        g_ram.pl_suu = 3;
        g_ram.pl2_suu = 3;
        g_ram.plring = 0;
        memset(&g_ram.pltime, 0, sizeof(g_ram.pltime));
        g_ram.plscore = 0;
        g_ram.pl2ring = 0;
        memset(&g_ram.pl2time, 0, sizeof(g_ram.pl2time));
        g_ram.pl2score = 0;
        g_ram.plcontinuecnt = 0;
        g_ram.extrascore = 5000;
        g_ram.extrascore2 = 5000;
        soundset(-31);

        switch (g_ram.openingoption) {
          case 2: g_ram.gmmode = DATASELMD; break;
          case 1: g_ram.gmmode = VSMENUMD; break;
          case 0: g_ram.gmmode = STAGESELMD3; break;
        }
      }
    }
  }
  while (g_ram.gmmode == OPENINGMD);
}


static void play_demo(void) {
  unsigned short stageno_tbl[7] = {
    ANGEL_ISLAND_ACT_1,
    HYDROCITY_ACT_1,
    MARBLE_GARDEN_ACT_1,
    MUSHROOM_HILL_ACT_1,
    FLYING_BATTERY_ACT_1,
    SANDOPOLIS_ACT_1,
    0xFFFF
  };

  soundset(-31);
  g_ram.demoid = g_ram.nextdemoid;
  unsigned short stageno = stageno_tbl[g_ram.demoid & 7];
  g_ram.stageno = stageno;
  g_ram.stageno_i = stageno;
  g_ram.stageno_s = stageno;
  ++g_ram.nextdemoid;
  if (g_ram.cartridge == 0) {
    if (!g_sonic3_alone) {
      if (g_ram.nextdemoid == 3) {
        g_ram.nextdemoid = 4;
      }
      else if (g_ram.nextdemoid >= 7) {
        g_ram.nextdemoid = 0;
      }
    }
    else {
      if (g_ram.nextdemoid >= 3) {
        g_ram.nextdemoid = 0;
      }
    }
  }
  else {
    if (g_ram.nextdemoid >= 7) {
      g_ram.nextdemoid = 3;
    }
  }
  if (stageno == 0xFFFF) {
    g_ram.gmmode = SPGAMEMD;
    g_ram.specstageno = 1;
    g_ram.cartridgespec = 1;
    set_zone(&g_ram.stageno, MUSHROOM_HILL);
    g_ram.emeraldcnt = 0;
    memset(g_ram.specprogress, 0, sizeof(g_ram.specprogress));
    if (g_ram.cartridge == 0) {
      g_ram.specprogress[1] = 2;
    }
  }
  else {
    if (g_ram.cartridge == 1 && stageno == MUSHROOM_HILL_ACT_1) {
      demo0700_init(stageno);
    }
    g_ram.gmmode = DEMOMD;
  }
  g_ram.demoflag = 1;
  g_ram.pl_suu = 3;
  g_ram.pl2_suu = 3;
  g_ram.plring = 0;
  memset(&g_ram.pltime, 0, sizeof(g_ram.pltime));
  g_ram.plscore = 0;
  g_ram.pl2ring = 0;
  memset(&g_ram.pl2time, 0, sizeof(g_ram.pl2time));
  g_ram.pl2score = 0;
  g_ram.extrascore = 5000;
  g_ram.extrascore2 = 5000;
}


static void load_frames(void) {
  struct {
    unsigned char* cg_ptr;
    unsigned short* color_ptr;
    unsigned char* map_ptr;
  }
  tbl[14] = {
    { s3opening_frame1_cg,  s3frame1_color,  s3opening_frame1_map  },
    { s3opening_frame1_cg,  s3frame2_color,  s3opening_frame2_map  },
    { s3opening_frame1_cg,  s3frame3_color,  s3opening_frame3_map  },
    { s3opening_frame1_cg,  s3frame4_color,  s3opening_frame4_map  },
    { s3opening_frame1_cg,  s3frame5_color,  s3opening_frame5_map  },
    { s3opening_frame1_cg,  s3frame6_color,  s3opening_frame6_map  },
    { s3opening_frame1_cg,  s3frame7_color,  s3opening_frame7_map  },
    { s3opening_frame8_cg,  s3frame8_color,  s3opening_frame8_map  },
    { s3opening_frame9_cg,  s3frame9_color,  s3opening_frame9_map  },
    { s3opening_frame10_cg, s3frame10_color, s3opening_frame10_map },
    { s3opening_frame11_cg, s3frame11_color, s3opening_frame11_map },
    { s3opening_frame12_cg, s3frame12_color, s3opening_frame12_map },
    { s3opening_frame13_cg, s3frame13_color, s3opening_frame13_map },
    { s3opening_frame13_cg, s3frame14_color, s3opening_frame14_map }
  };

  unlze(g_vram, s3opening_frame1_cg);

  for (int i = 0; i < 14; ++i) {
    if (tbl[i].cg_ptr != s3opening_frame1_cg) {
      unlze(g_vram, tbl[i].cg_ptr);
    }
    memcpy(g_ram.colorwk2, tbl[i].color_ptr, sizeof(unsigned short) * 32);
    unsigned char map[2240] = { 0 };
    mapdevr(map, tbl[i].map_ptr, 0);
    copy_map_vram(map, g_vdp_scrolla_adr, 40, 28);

    for (int j = 0; j < 4; ++j) {
      g_ram.int_flg = 4;
      v_int();
    }
  }
}


static unsigned short s3transition_color[8][7] = {
  { 0xEEE, 0xEEE, 0xECC, 0xECA, 0xEC8, 0x000, 0xEA6 },
  { 0xCCC, 0xCCC, 0xCAA, 0xEA8, 0xEA6, 0x000, 0xEA6 },
  { 0xAAA, 0xCAA, 0xC88, 0xC88, 0xCA6, 0x000, 0xE84 },
  { 0x888, 0xA88, 0xA66, 0xC66, 0xC84, 0x000, 0xC84 },
  { 0x666, 0x866, 0xA66, 0xA64, 0xC64, 0x000, 0xC62 },
  { 0x444, 0x644, 0x844, 0xA42, 0xA42, 0x000, 0xC62 },
  { 0x222, 0x622, 0x822, 0x822, 0xA42, 0x000, 0xC40 },
  { 0x000, 0x400, 0x600, 0x800, 0xA20, 0x000, 0xC40 }
};
static unsigned short s3frame1_color[32] = {
  0xEEE, 0xEEE, 0xECC, 0xECA, 0xEC8, 0x000, 0xEA6, 0x000, 0x000, 0x000, 0xE60, 0x000, 0x000, 0x000, 0x000, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame2_color[32] = {
  0x000, 0x400, 0x600, 0x800, 0xA20, 0xC20, 0xC40, 0x000, 0xE20, 0xE40, 0xE60, 0x000, 0x000, 0xEA2, 0xEC4, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame3_color[32] = {
  0x000, 0x400, 0x600, 0x800, 0xA20, 0xC20, 0xC40, 0xE00, 0xE20, 0xE40, 0xE60, 0xE62, 0xE82, 0xEA2, 0xEC4, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame4_color[32] = {
  0x000, 0x400, 0x600, 0x800, 0xA20, 0xC20, 0xC40, 0xE00, 0xE20, 0xE40, 0xE60, 0xE62, 0xE82, 0xEA2, 0xEC4, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame5_color[32] = {
  0x000, 0x400, 0x600, 0x800, 0xA20, 0xC20, 0xC40, 0xE00, 0xE20, 0xE40, 0xE60, 0xE62, 0xE82, 0xEA2, 0xEC4, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame6_color[32] = {
  0x000, 0x400, 0x600, 0x800, 0xA20, 0xC20, 0xC40, 0xE00, 0xE20, 0xE40, 0xE60, 0xE62, 0xE82, 0xEA2, 0xEC4, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame7_color[32] = {
  0x000, 0x400, 0x600, 0x800, 0xA20, 0xC20, 0xC40, 0xE00, 0xE20, 0xE40, 0xE60, 0xE62, 0xE82, 0xEA2, 0xEC4, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame8_color[32] = {
  0x000, 0x620, 0x664, 0x820, 0xA20, 0xA88, 0xC64, 0xE00, 0xE40, 0xE42, 0xE62, 0xE84, 0xE88, 0xEA8, 0xECC, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame9_color[32] = {
  0x000, 0x444, 0x800, 0x844, 0x86C, 0xA20, 0xA66, 0xA68, 0xC42, 0xC44, 0xC8A, 0xE20, 0xE84, 0xE88, 0xECA, 0xEEE,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame10_color[32] = {
  0x000, 0x204, 0xE20, 0x866, 0x600, 0xA00, 0xE64, 0x644, 0xEA6, 0xEEE, 0xCCE, 0xAAE, 0x888, 0x88E, 0x64A, 0x22C,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame11_color[32] = {
  0x000, 0x846, 0x444, 0xE20, 0x666, 0x600, 0x800, 0xE84, 0xA44, 0xEA6, 0x888, 0xCCC, 0xEEE, 0x88C, 0x8CE, 0x00E,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3frame12_color[32] = {
  0x000, 0x642, 0x024, 0xE20, 0x888, 0x600, 0xA00, 0xE82, 0xEA6, 0xECA, 0x468, 0x48C, 0xEEE, 0x446, 0x8CE, 0x00E,
  0x000, 0xEEE, 0xE84, 0xE62, 0xE40, 0xE00, 0x600, 0x8CE, 0x4AE, 0x48C, 0x46A, 0x246, 0xECA, 0x866, 0x444, 0x000
};
static unsigned short s3frame13_color[32] = {
  0x000, 0xEEE, 0xEA6, 0xE84, 0xE62, 0xE40, 0xE00, 0x600, 0x0EE, 0x2AC, 0x08C, 0x06A, 0x048, 0x026, 0x444, 0x000,
  0x000, 0xEEE, 0xE84, 0xE62, 0xE40, 0xE00, 0x600, 0x8CE, 0x4AE, 0x48C, 0x46A, 0x246, 0xECA, 0x866, 0x444, 0x000
};
static unsigned short s3frame14_color[32] = {
  0x0E0, 0xEEE, 0x0AE, 0x268, 0x246, 0x440, 0xEEA, 0xEC6, 0xE82, 0xE42, 0xE22, 0x0E6, 0x082, 0xE42, 0xEC6, 0x000,
  0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};
static unsigned short s3opening_color[64] = {
  0x000, 0xEEE, 0xEA6, 0xE84, 0xE62, 0xE40, 0xE00, 0x600, 0x0EE, 0x2AC, 0x08C, 0x06A, 0x048, 0x026, 0x444, 0x000,
  0x000, 0xEEE, 0xE84, 0xE62, 0xE40, 0xE00, 0x600, 0x8CE, 0x4AE, 0x48C, 0x46A, 0x246, 0xECA, 0x866, 0x444, 0x000,
  0x0E0, 0xEEE, 0x0AE, 0x268, 0x246, 0x440, 0xEEA, 0xEC6, 0xE82, 0xE42, 0xE22, 0x0E6, 0x082, 0xE42, 0xEC6, 0x000,
  0x000, 0xEEE, 0xA66, 0x604, 0x602, 0x200, 0xAEE, 0x4EE, 0x0AE, 0x06E, 0xCCC, 0x00E, 0x00A, 0x408, 0x206, 0x000
};


static void s3banner_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_banner_pt;
  p_actwk->sproffset = 0xE500;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 128;
  p_actwk->sprvs = 64;
  fp16_set_integer(&p_actwk->xposi, 288);
  fp16_set_integer(&p_actwk->yposi, 240);
  p_actwk->yspeed = 0x400;
  p_actwk->u.obj.actfree.opening_banner.yposiwk = -0x600000;
  p_actwk->r_ptr = &s3banner_move0;
  s3banner_move0(p_actwk);
}


static void s3banner_move0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actfree.opening_banner.yposiwk += p_actwk->yspeed * 0x100;
  signed char prev_dir = p_actwk->u.obj.actfree.opening_banner.dir;
  p_actwk->u.obj.actfree.opening_banner.dir = 0;
  short yaccel = 0x40;
  short yposi = fp16_get_integer(p_actwk->u.obj.actfree.opening_banner.yposiwk);
  if (yposi >= 0) {
    if (yposi == 0 && p_actwk->yspeed == -0x5B) {
      p_actwk->r_ptr = &s3banner_move1;
      g_ram.actwk[2].r_ptr = &s3bannertm_init;
    }
    else {
      p_actwk->u.obj.actfree.opening_banner.dir = -1;
      yaccel = -0x40;
    }
  }
  p_actwk->yspeed += yaccel;
  if (prev_dir != p_actwk->u.obj.actfree.opening_banner.dir) {
    p_actwk->yspeed /= 2;
  }
  yposi = -yposi + (!g_sonic3_alone ? 212 : 240);
  fp16_set_integer(&p_actwk->yposi, yposi);
  if (!g_sonic3_alone && g_ram.vscroll.a != 16) {
    ++g_ram.vscroll.a;
  }
  s3banner_move1(p_actwk);
}


static void s3banner_move1(SKC_sprite_status* p_actwk) {
  unsigned short water_color[8][2] = {
    { 0xE42, 0xEC6 },
    { 0xE82, 0xEC6 },
    { 0xEC6, 0xE42 },
    { 0xEC6, 0xE82 },
    { 0xEC6, 0xE42 },
    { 0xEC6, 0xEC6 },
    { 0xEC6, 0xE42 },
    { 0xE82, 0xEC6 }
  };

  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 9;
    p_actwk->patcnt += 4;
    p_actwk->patcnt &= 0x1C;
  }
  memcpy(&g_ram.colorwk2[45], water_color[p_actwk->patcnt / 4], sizeof(water_color[p_actwk->patcnt / 4]));
  actionsub(p_actwk);
}


static void s3bannertm_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = s3opening_banner_pt;
  p_actwk->sproffset = 0xE500;
  fp16_set_integer(&p_actwk->xposi, 392);
  if (!g_sonic3_alone) {
    fp16_set_integer(&p_actwk->yposi, 236);
  }
  else {
    fp16_set_integer(&p_actwk->yposi, 264);
  }
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 12;
  p_actwk->sprvs = 4;
  p_actwk->patno = 1;
  p_actwk->r_ptr = &s3bannertm_move;
  s3bannertm_move(p_actwk);
}


static void s3bannertm_move(SKC_sprite_status* p_actwk) {
  if (!g_sonic3_alone && !BIT_IS_SET(g_ram.mdstatus, 7)) return;

  actionsub(p_actwk);
}


static void andknuckles_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = andknuckles_pt;
  p_actwk->sproffset = 0xE4C0;
  fp16_set_integer(&p_actwk->xposi, 288);
  fp16_set_integer(&p_actwk->yposi, 264);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 84;
  p_actwk->sprvs = 12;
  p_actwk->r_ptr = &andknuckles_move;
  andknuckles_move(p_actwk);
}


static void andknuckles_move(SKC_sprite_status* p_actwk) {
  short yposi = fp16_get_integer(g_ram.actwk[0].yposi) + 92;
  fp16_set_integer(&p_actwk->yposi, yposi);
  actionsub(p_actwk);
}


static SKC_sprite_pattern* andknuckles_pt[1] = {
  &andknuckles_pt00
};


static SKC_sprite_pattern andknuckles_pt00 = {
  6,
  {
    { -12, 14, 0x0000, -84 },
    { -12, 14, 0x000C, -52 },
    { -12, 14, 0x0018, -20 },
    { -12, 14, 0x0024,  12 },
    { -12, 14, 0x0030,  44 },
    { -12,  2, 0x003C,  76 },
  }
};


static void s3copyright_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = s3selectioncopyright_pt;
  p_actwk->sproffset = 0xE6A6;
  fp16_set_integer(&p_actwk->xposi, 328);
  fp16_set_integer(&p_actwk->yposi, 330);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 12;
  p_actwk->sprvs = 4;
  p_actwk->patno = 3;
  p_actwk->r_ptr = &actionsub;
  actionsub(p_actwk);
}


static void s3selection_init(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, 240);
  fp16_set_integer(&p_actwk->yposi, 320);
  p_actwk->patbase = s3selectioncopyright_pt;
  p_actwk->sproffset = 0xC680;
  g_ram.openingoption &= 1;
  p_actwk->patno = g_ram.openingoption;
  p_actwk->r_ptr = &s3selection_move;
  s3selection_move(p_actwk);
}


static void s3selection_move(SKC_sprite_status* p_actwk) {
  if (g_ram.swdata1.pressed.u == 1 || (!g_sonic3_alone && g_ram.swdata2.pressed.u == 1)) {
    if (g_ram.openingoption-- == 0) {
      g_ram.openingoption = g_ram.stageselcheat != 0 ? 2 : 1;
    }
  }
  if (g_ram.swdata1.pressed.d == 1 || (!g_sonic3_alone && g_ram.swdata2.pressed.d == 1)) {
    ++g_ram.openingoption;
    if (g_ram.stageselcheat == 0) {
      g_ram.openingoption &= 1;
    }
    if (g_ram.openingoption >= 3) {
      g_ram.openingoption = 0;
    }
  }
  p_actwk->patno = g_ram.openingoption;
  if (g_ram.swdata1.pressed.u == 1 || (!g_sonic3_alone && g_ram.swdata1.pressed.d == 1)
      || g_ram.swdata2.pressed.u == 1 || (!g_sonic3_alone && g_ram.swdata2.pressed.d == 1)) {
    soundset(91);
  }
  actionsub(p_actwk);
}


static void sonichand_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = sonicparts_pt;
  p_actwk->sproffset = 0xA400;
  fp16_set_integer(&p_actwk->xposi, 328);
  fp16_set_integer(&p_actwk->yposi, 220);
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 28;
  p_actwk->r_ptr = &sonichand_move;
  sonichand_move(p_actwk);
}


static void sonichand_move(SKC_sprite_status* p_actwk) {
  if (!g_sonic3_alone) {
    short yposi = 220 - g_ram.vscroll.a;
    fp16_set_integer(&p_actwk->yposi, yposi);
  }
  patchg(p_actwk, s3opening_sonichand_chg);
  actionsub(p_actwk);
}


static signed char* s3opening_sonichand_chg[1] = {
  s3opening_sonichand_chg0
};


static signed char s3opening_sonichand_chg0[30] = {
  5, 4, 4, 4, 4, 4, 4, 0, 4, 1, 4, 0, 4, 1, 4, 0, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1
};


static void soniceye_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = sonicparts_pt;
  p_actwk->sproffset = 0xA400;
  fp16_set_integer(&p_actwk->xposi, 248);
  fp16_set_integer(&p_actwk->yposi, 200);
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 24;
  p_actwk->r_ptr = &soniceye_move;
  soniceye_move(p_actwk);
}


static void soniceye_move(SKC_sprite_status* p_actwk) {
  if (!g_sonic3_alone) {
    short yposi = 200 - g_ram.vscroll.a;
    fp16_set_integer(&p_actwk->yposi, yposi);
  }
  time_patchg(p_actwk, soniceye_chg);
  actionsub(p_actwk);
}


static signed char* soniceye_chg[1] = {
  soniceye_chg0
};


static signed char soniceye_chg0[11] = {
  2, 1, 3, 7, 2, 5, 4, 103, 4, 47, -1
};


static void tornado_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = tornado_pt;
  p_actwk->sproffset = 0x6400;
  fp16_set_integer(&p_actwk->xposi, 0);
  fp16_set_integer(&p_actwk->yposi, 192);
  p_actwk->sprpri = PRI_7;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 8;
  p_actwk->r_ptr = &tornado_move;
  tornado_move(p_actwk);
}


static void tornado_move(SKC_sprite_status* p_actwk) {
  if (!p_actwk->u.obj.actfree.tornado.reverse) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 1);
    if (fp16_get_integer(p_actwk->xposi) == 576) {
      p_actwk->u.obj.actfree.tornado.reverse = true;
      p_actwk->u.obj.cddat.right = 1;
      fp16_set_integer(&p_actwk->yposi, 208);
    }
  }
  else {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 1);
    if (fp16_get_integer(p_actwk->xposi) == 0) {
      p_actwk->u.obj.actfree.tornado.reverse = false;
      p_actwk->u.obj.cddat.right = 0;
      fp16_set_integer(&p_actwk->yposi, 192);
    }
  }
  patchg(p_actwk, tornado_chg);
  actionsub(p_actwk);
}


static signed char* tornado_chg[1] = {
  tornado_chg0
};


static signed char tornado_chg0[8] = { 1, 0, 1, 2, 3, 4, 5, -1 };


static SKC_sprite_pattern* s3selectioncopyright_pt[4] = {
  &s3selectioncopyright_pt00,
  &s3selectioncopyright_pt01,
  &s3selectioncopyright_pt02,
  &s3selectioncopyright_pt03
};


static SKC_sprite_pattern s3selectioncopyright_pt00 = {
  7,
  {
    {  0, 12, 0x2000,   0 },
    {  0, 12, 0x2004,  32 },
    {  0, 12, 0x2008,  64 },
    { 16, 12, 0x000C,   0 },
    { 16, 12, 0x0010,  32 },
    { 16, 12, 0x0014,  64 },
    {  0,  4, 0x2024, -20 },
  }
};
static SKC_sprite_pattern s3selectioncopyright_pt01 = {
  7,
  {
    {  0, 12, 0x0000,   0 },
    {  0, 12, 0x0004,  32 },
    {  0, 12, 0x0008,  64 },
    { 16, 12, 0x200C,   0 },
    { 16, 12, 0x2010,  32 },
    { 16, 12, 0x2014,  64 },
    { 16,  4, 0x2024, -20 },
  }
};
static SKC_sprite_pattern s3selectioncopyright_pt02 = {
  4,
  {
    { 8, 12, 0x2018,   0 },
    { 8, 12, 0x201C,  32 },
    { 8, 12, 0x2020,  64 },
    { 8,  4, 0x2024, -20 },
  }
};
static SKC_sprite_pattern s3selectioncopyright_pt03 = {
  4,
  {
    { 0, 12, 0x0000,  0 },
    { 0, 12, 0x0004, 32 },
    { 0, 12, 0x0008, 64 },
    { 0,  4, 0x000C, 96 },
  }
};


static unsigned char text_cg[609] = { 0x2F, 0x80, 0x80, 0x03, 0x00, 0x14, 0x06, 0x24, 0x09, 0x35, 0x14, 0x45, 0x18, 0x55, 0x19, 0x65, 0x1A, 0x73, 0x02, 0x83, 0x06, 0x3A, 0x85, 0x48, 0xF8, 0x57, 0x79, 0x87, 0x07, 0x7A, 0x88, 0x04, 0x07, 0x14, 0x08, 0x25, 0x17, 0x37, 0x7B, 0x46, 0x37, 0x58, 0xF9, 0x8E, 0x05, 0x15, 0x16, 0x36, 0x27, 0x76, 0x36, 0x39, 0x47, 0x78, 0x8F, 0x03, 0x01, 0x15, 0x16, 0x27, 0x77, 0x76, 0x38, 0xFF, 0xD1, 0x4B, 0x45, 0x70, 0x47, 0xC3, 0x1F, 0x81, 0x66, 0xFD, 0xFD, 0xF0, 0xE9, 0x29, 0xFD, 0xFA, 0x11, 0x8E, 0xE8, 0x7B, 0xCC, 0x2C, 0xC7, 0x79, 0x85, 0x48, 0x9B, 0x50, 0xB9, 0x68, 0x97, 0x2B, 0x2E, 0x70, 0xE0, 0xD0, 0xE6, 0x29, 0xEF, 0xBA, 0x17, 0x52, 0x5C, 0x38, 0x75, 0x67, 0x67, 0x67, 0x9B, 0x87, 0x11, 0x2E, 0x67, 0xBC, 0xC1, 0x05, 0xD5, 0x9C, 0x39, 0x79, 0x2E, 0x1C, 0x45, 0x96, 0x1E, 0x6E, 0x83, 0xB6, 0xF8, 0xF6, 0x66, 0xE6, 0x97, 0xB2, 0x9B, 0xCE, 0xE0, 0xA1, 0xBE, 0x21, 0x66, 0x18, 0xCB, 0xA7, 0xA4, 0x33, 0xB7, 0xF7, 0xD3, 0xAD, 0x3E, 0x9C, 0x7F, 0x7D, 0xBC, 0xB8, 0xF3, 0xC2, 0x49, 0x71, 0xFF, 0x5F, 0xFA, 0xF0, 0x92, 0x5C, 0x7F, 0xD7, 0xFE, 0xBC, 0x24, 0x97, 0xF7, 0xDB, 0xC9, 0x1E, 0x47, 0x05, 0x68, 0xA5, 0xFE, 0xF0, 0x47, 0xC3, 0x1F, 0x86, 0x33, 0xFB, 0xFF, 0x64, 0x17, 0x10, 0x1C, 0xBC, 0x98, 0x58, 0x30, 0xCE, 0x20, 0x38, 0x71, 0xED, 0x16, 0xDC, 0x87, 0x17, 0x0F, 0x42, 0xB4, 0x73, 0x70, 0xED, 0xBB, 0x38, 0xFD, 0xFC, 0xB9, 0x63, 0x0C, 0xF6, 0x7C, 0x46, 0x1D, 0x9F, 0x10, 0xA8, 0xF4, 0x8D, 0x58, 0x6E, 0x69, 0x01, 0xCA, 0x98, 0x0E, 0x66, 0xE0, 0xA1, 0x0B, 0x3B, 0xE2, 0xF8, 0xB8, 0x33, 0x74, 0x0C, 0xDE, 0x77, 0x4D, 0xF2, 0xD0, 0xD0, 0xC6, 0x96, 0x40, 0xD2, 0xCA, 0x61, 0x52, 0x1B, 0xDD, 0x23, 0x16, 0x59, 0xB2, 0x98, 0xA4, 0x68, 0xC3, 0x43, 0x46, 0x08, 0xB2, 0xCD, 0x92, 0x10, 0xC7, 0x47, 0x76, 0x71, 0x70, 0xE9, 0x20, 0xE2, 0xE1, 0xDB, 0x7A, 0x5A, 0x90, 0x5A, 0x25, 0xCE, 0x9F, 0x2E, 0x1F, 0x2E, 0x9E, 0x62, 0x60, 0x70, 0x92, 0x5F, 0xDF, 0x6F, 0x24, 0x79, 0x1C, 0x15, 0xA2, 0x97, 0xFB, 0xC1, 0x1F, 0x0C, 0x7E, 0x18, 0xE4, 0xEE, 0xCE, 0x2E, 0xCE, 0xD0, 0x1D, 0xA1, 0xA1, 0x9C, 0x46, 0x2E, 0x1C, 0x7C, 0xA9, 0xDE, 0x97, 0x0F, 0x42, 0xB4, 0x73, 0x70, 0xED, 0xBE, 0x4D, 0x22, 0x61, 0x25, 0x43, 0x47, 0x17, 0x0E, 0xDB, 0xD2, 0xD4, 0x82, 0xD1, 0x2E, 0x74, 0xF9, 0x70, 0xF9, 0x74, 0xF3, 0x13, 0x1A, 0xB7, 0xC9, 0x9B, 0x87, 0x32, 0x56, 0x8E, 0x6E, 0x1C, 0x7C, 0xB7, 0xFB, 0xD2, 0x45, 0x70, 0x92, 0xF9, 0x68, 0x68, 0x63, 0x4B, 0x20, 0x69, 0x65, 0x30, 0x9A, 0xDB, 0xE2, 0xEC, 0x5A, 0xF8, 0xBA, 0x06, 0x6F, 0x3B, 0xC9, 0xD1, 0xDD, 0x9C, 0x5F, 0x10, 0x1C, 0x18, 0x68, 0x67, 0x11, 0x24, 0x5C, 0x3B, 0x6E, 0x98, 0xFC, 0xB4, 0x34, 0x31, 0xA5, 0x90, 0x34, 0xEF, 0x8F, 0xD2, 0xB4, 0x0F, 0xD2, 0xF0, 0x92, 0x5F, 0xDF, 0x6F, 0x24, 0x79, 0x1F, 0xBF, 0xD1, 0xEB, 0xF4, 0x9D, 0x03, 0xD7, 0xA9, 0xF4, 0x7A, 0xF4, 0xB3, 0xEB, 0x5F, 0xE4, 0xE0, 0xEB, 0xAB, 0x63, 0xD5, 0x7A, 0x39, 0xFC, 0x6F, 0x56, 0xC7, 0xAF, 0xC2, 0x74, 0x73, 0xEB, 0xA3, 0xF8, 0x4D, 0xBF, 0x49, 0xD0, 0xE0, 0x1F, 0xD8, 0x90, 0x7F, 0xBC, 0x76, 0x1B, 0x0D, 0x9B, 0xB2, 0xC7, 0x69, 0xD8, 0x6C, 0x36, 0x3F, 0xDE, 0x20, 0xF2, 0x69, 0xB6, 0x6B, 0x92, 0xB4, 0x64, 0xD2, 0xA2, 0xB8, 0xED, 0x27, 0x24, 0x72, 0x08, 0xA8, 0xD8, 0x55, 0x35, 0x46, 0xD8, 0xED, 0x4E, 0x45, 0x5B, 0xC0, 0xB6, 0x88, 0xE4, 0x11, 0x51, 0xB0, 0xAA, 0x6A, 0x8D, 0xB1, 0xDA, 0x9C, 0x8A, 0xB7, 0x80, 0x69, 0xDD, 0xB6, 0x1D, 0xF1, 0xB2, 0x40, 0xCD, 0x5A, 0xAD, 0xD9, 0xAA, 0x3B, 0x8D, 0x81, 0x16, 0xC1, 0x1E, 0x08, 0xA8, 0xE5, 0xAA, 0x3B, 0x31, 0x1D, 0x85, 0x41, 0x5C, 0x8A, 0xB7, 0x81, 0x6C, 0xD8, 0x78, 0x6A, 0x8E, 0x69, 0xCD, 0x39, 0x4D, 0x51, 0xC8, 0x23, 0xC2, 0xB0, 0xF0, 0x45, 0x47, 0x38, 0xED, 0x8A, 0xAA, 0x54, 0x6D, 0x24, 0x78, 0x6B, 0x37, 0x76, 0x35, 0x55, 0x32, 0x6A, 0xAA, 0x2A, 0x69, 0x5A, 0x1A, 0x8D, 0x85, 0x48, 0xD9, 0xB6, 0x00 };


static SKC_sprite_pattern* sonicparts_pt[5] = {
  &sonicparts_pt00,
  &sonicparts_pt01,
  &sonicparts_pt02,
  &sonicparts_pt03,
  &sonicparts_pt04
};


static SKC_sprite_pattern sonicparts_pt00 = {
  4,
  {
    { -28, 11, 0x0000, -24 },
    { -28, 11, 0x000C,   0 },
    {   4, 10, 0x0018, -24 },
    {   4, 10, 0x0021,   0 },
  }
};
static SKC_sprite_pattern sonicparts_pt01 = {
  4,
  {
    { -28, 11, 0x002A, -24 },
    { -28, 11, 0x0036,   0 },
    {   4, 10, 0x0042, -24 },
    {   4, 10, 0x004B,   0 },
  }
};
static SKC_sprite_pattern sonicparts_pt02 = {
  2,
  {
    { -24, 15, 0x0054, -16 },
    {   8, 13, 0x0064, -16 },
  }
};
static SKC_sprite_pattern sonicparts_pt03 = {
  2,
  {
    { -24, 15, 0x006C, -16 },
    {   8, 13, 0x007C, -16 },
  }
};
static SKC_sprite_pattern sonicparts_pt04 = {
  0,
  {}
};


static SKC_sprite_pattern* tornado_pt[6] = {
  &tornado_pt00,
  &tornado_pt01,
  &tornado_pt02,
  &tornado_pt03,
  &tornado_pt04,
  &tornado_pt05
};


static SKC_sprite_pattern tornado_pt00 = {
  2,
  {
    { -12, 14, 0x0084, -24 },
    { -12,  6, 0x009C,   8 },
  }
};
static SKC_sprite_pattern tornado_pt01 = {
  2,
  {
    { -12, 14, 0x0090, -24 },
    { -12,  6, 0x00A2,   8 },
  }
};
static SKC_sprite_pattern tornado_pt02 = {
  2,
  {
    { -12, 14, 0x0084, -24 },
    { -12,  6, 0x00A8,   8 },
  }
};
static SKC_sprite_pattern tornado_pt03 = {
  2,
  {
    { -12, 14, 0x0090, -24 },
    { -12,  6, 0x009C,   8 },
  }
};
static SKC_sprite_pattern tornado_pt04 = {
  2,
  {
    { -12, 14, 0x0084, -24 },
    { -12,  6, 0x00A2,   8 },
  }
};
static SKC_sprite_pattern tornado_pt05 = {
  2,
  {
    { -12, 14, 0x0090, -24 },
    { -12,  6, 0x00A8,   8 },
  }
};


static void skopening(void) {
  unlze(g_vram, skopening_bg_cg);
  unlze(&g_vram[0x9380], skopening_logo_cg);
  unlze(&g_vram[0x9DE0], skopening_sonicfalling_cg);
  unlze(&g_vram[0xD000], skopening_deathegg_cg);
  unlze(&g_vram[0xF400], skopening_mountain_cg);
  mapdevr(mapa, skopening_logo_map, 0x849C);
  if (!BIT_IS_SET(g_ram.mdstatus, 7)) {
    mapa[860] = 0x9C;
    mapa[861] = 0xA4;
    mapa[862] = 0x9C;
    mapa[863] = 0xA4;
    mapa[864] = 0x9C;
    mapa[865] = 0xA4;
    mapa[940] = 0x9C;
    mapa[941] = 0xA4;
    mapa[942] = 0x9C;
    mapa[943] = 0xA4;
    mapa[944] = 0x9C;
    mapa[945] = 0xA4;
  }
  copy_map_vram(mapa, g_vdp_scrolla_adr, 40, 28);
  mapdevr(mapb, skopening_bg_map, 0);

  for (int i = 0; i < 32; ++i) {
    memcpy(&g_vram[g_vdp_scrollb_adr + i * 128], mapb, 80);
  }

  mapdevr(mapa, skopening_frame1_map, 0x80E2);
  unlze(cg_chg_cg, skopening_cg_chg_cg);

  for (int line = 0; line < 4; ++line) {
    for (int i = 0; i < 16; ++i) {
      if (i == 0) {
        g_ram.colorwk2[line * 16] = 0;
      }
      else {
        g_ram.colorwk2[line * 16 + i] = 0xEEE;
      }
    }
  }

  memcpy(&g_ram.colorwk2[16], &skopening_color[16], sizeof(unsigned short) * 16);
  g_ram.demotimer = !BIT_IS_SET(g_ram.mdstatus, 6) ? 180 : 150;
  fadein();
  bgmset(-1);

  do {
    g_ram.int_flg = 20;
    v_int();
  }
  while (g_ram.swdata1.pressed.s == 0 && g_ram.demotimer != 0);

  bgmset(-2);
  memcpy(g_ram.colorwk2, skopening_color, sizeof(skopening_color));
  unlze_moduled(&g_vram[0x1C40], skopening_sonicknuckles_cg);
  g_ram.colorcnt = 64;
  g_ram.fadecnt = 22;
  g_ram.actwk[0].r_ptr = &sonicfalling_init;
  g_ram.actwk[1].r_ptr = &deathegg_init;
  g_ram.actwk[2].r_ptr = &mountain_init;
  bgmset(37);
  g_ram.pl_suu = 3;
  g_ram.demotimer = !BIT_IS_SET(g_ram.mdstatus, 6) ? 1080 : 900;

  do {
    g_ram.int_flg = 26;
    v_int();
    if (g_ram.fadecnt != 0) {
      --g_ram.fadecnt;
      flashin1();
    }
    action();
    patset();
    skopening_scroll();
  }
  while ((g_ram.swdata1.pressed.s == 0 || g_ram.fadecnt != 0) && g_ram.actwk[3].r_ptr == 0);

  if (g_ram.swdata1.pressed.s == 1 && g_ram.fadecnt == 0) {
    skopening_cg_chg_init(&g_ram.actwk[4]);
    g_ram.actwk[1].r_ptr = &deathegg_move1;
    fp16_set_integer(&g_ram.actwk[1].u.obj.actfree.deathegg.xposiwk, 320);
    fp16_set_integer(&g_ram.actwk[1].u.obj.actfree.deathegg.yposiwk, 112);
    g_ram.scr_evta = 3;
    g_ram.scr_shake_flg = 0;
    g_ram.vscroll.a = 256;
    g_ram.vscroll.b = 256;
    g_ram.scra_v_posit = 256 << 16 | g_ram.scra_v_posit & 0x0000FFFF;
    g_ram.vs_scra_v_posit = 256 << 16 | g_ram.scra_v_posit & 0x0000FFFF;
    memcpy(&g_ram.colorwk[16], knuckles_color, sizeof(unsigned short) * 16);
    skopening_scroll();
    g_ram.int_flg = 26;
    v_int();
    copy_map_vram(mapb, g_vdp_scrollb_adr, 40, 28);
    sonicfalling_move1(&g_ram.actwk[0]);
  }

  do {
    g_ram.int_flg = 26;
    v_int();
    if (g_ram.fadecnt != 0) {
      --g_ram.fadecnt;
      flashin1();
    }
    action();
    patset();
    skopening_scroll();

    if (g_ram.actwk[5].r_ptr != 0) {
      if (g_ram.demotimer == 0) {
        play_demo();
      }
      else if (g_ram.swdata1.pressed.s == 1) {
        g_ram.gmmode = GAMEMD;
        g_ram.pl_suu = 3;
        g_ram.pl2_suu = 3;
        g_ram.plring = 0;
        memset(&g_ram.pltime, 0, sizeof(g_ram.pltime));
        g_ram.plscore = 0;
        g_ram.pl2ring = 0;
        memset(&g_ram.pl2time, 0, sizeof(g_ram.pl2time));
        g_ram.pl2score = 0;
        g_ram.plcontinuecnt = 0;
        g_ram.extrascore = 5000;
        g_ram.extrascore2 = 5000;
        soundset(-31);
        if (g_ram.openingoption < 2) {
          switch (g_ram.openingoption) {
            case 0: g_ram.stagesel_play_type = PLAY_TYPE_SONIC; break;
            case 1: g_ram.stagesel_play_type = PLAY_TYPE_KNUCKLES; break;
          }

          unsigned short stageno = MUSHROOM_HILL_ACT_1;
          g_ram.stageno = stageno;
          g_ram.stageno_i = stageno;
          g_ram.stageno_s = stageno;
          g_ram.specstageno = 0;
          g_ram.emeraldcnt = 0;
          memset(g_ram.specprogress, 0, sizeof(g_ram.specprogress));
          g_ram.brings = 0;
          g_ram.curr_savedata_ptr = 0;
          if (g_ram.stageselcheat != 0 && g_ram.swdata1.down.a == 1) {
            g_ram.gmmode = STAGESELMD3;
          }
        }
        else {
          g_ram.gmmode = STAGESELMD3;
        }
      }
    }
  }
  while (g_ram.gmmode == OPENINGMD);
}


static void demo0700_init(unsigned short stageno) {
  g_ram.plxposi_s = 0x6F4;
  g_ram.plyposi_s = 0x9EC;
  g_ram.markerno = 1;
  g_ram.markerno_s = 1;
  g_ram.stageno_s = stageno;
  g_ram.stageno_is = stageno;
  g_ram.plsproffset_s = 0x680;
  g_ram.pl_top_solid_bit_s = 12;
  g_ram.pl_lrb_solid_bit_s = 13;
  g_ram.plring_s = 0;
  g_ram.plring_f2_s = 0;
  memset(&g_ram.pltime_s, 0, sizeof(g_ram.pltime_s));
  g_ram.zone_flag_s = 0;
  g_ram.scralim_down_s = 0xAA0;
  g_ram.scra_h_posit_s = 0x680;
  g_ram.scra_v_posit_s = 0x98C;
  g_ram.waterposi_m_s = 0x1000;
  g_ram.waterflag_s = 0;
}


static unsigned short skopening_color[64] = {
  0x000, 0x000, 0x008, 0x00E, 0x800, 0xC00, 0xE00, 0xE20, 0xE42, 0x866, 0xAAA, 0xEEE, 0x26A, 0x48C, 0x6AE, 0xACE,
  0x000, 0xEEE, 0xEEE, 0xECC, 0xECA, 0xEC8, 0xEA6, 0xE40, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
  0x000, 0xEEE, 0xECC, 0x000, 0x000, 0x000, 0x000, 0x000, 0xECC, 0xCAA, 0xA88, 0x866, 0x644, 0x422, 0x0AE, 0x000,
  0x000, 0x08E, 0x04A, 0xE20, 0x024, 0x6EE, 0x084, 0x0E6, 0x044, 0x046, 0xEA0, 0xE64, 0xEEE, 0x0CE, 0x800, 0xE42
};
static unsigned short knuckles_color[16] = {
  0x000, 0x000, 0x008, 0x00E, 0x0E0, 0x0CE, 0x00C, 0x20C, 0x22E, 0x866, 0xCA8, 0xEEE, 0x26A, 0x48C, 0x6AE, 0xACE
};


static void sonicfalling_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = skopening_sonicfalling_pt;
  p_actwk->sproffset = 0x04EF;
  fp16_set_integer(&p_actwk->xposi, 232);
  fp16_set_integer(&p_actwk->yposi, 22);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 104;
  p_actwk->sprvs = 112;
  p_actwk->r_ptr = &sonicfalling_move0;
  sonicfalling_move0(p_actwk);
}


static void sonicfalling_move0(SKC_sprite_status* p_actwk) {
  if (fp16_get_integer(p_actwk->yposi) != 240) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 1);
  }
  if (g_ram.scr_evta == 3) {
    SET_BIT(p_actwk->sproffset, 15);
    if (g_ram.scra_v_posit >> 16 < 224) {
      g_ram.scra_v_posit += 8 << 16;
      copy_mapline_vram(mapa, g_vdp_scrolla_adr, g_ram.scra_v_posit >> 16);
      actionsub(p_actwk);
    }
    else {
      if (g_ram.scra_v_posit >> 16 != 0) {
        mapdevr(mapa, skopening_frame2_map, 0x80E2);
        copy_map_vram(mapa, g_vdp_scrolla_adr, 40, 28);
        p_actwk->pattim = 6;
        unlze_moduled(&g_vram[0x8C40], skopening_soniclanding_cg);
      }
      if (g_ram.scra_v_posit >> 16 != 256) {
        g_ram.scra_v_posit += 8 << 16;
      }
      else {
        p_actwk->r_ptr = &sonicfalling_wait0;
        sonicfalling_wait0(p_actwk);
      }
    }
  }
  else {
    actionsub(p_actwk);
  }
}


static void sonicfalling_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  mapdevr(mapa, skopening_frame3_map, 0x80E2);
  copy_map_vram(mapa, g_vdp_scrolla_adr, 40, 28);
  p_actwk->pattim = 4;
  p_actwk->r_ptr = &sonicfalling_wait1;
}


static void sonicfalling_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  sonicfalling_move1(p_actwk);
}


static void sonicfalling_move1(SKC_sprite_status* p_actwk) {
  mapdevr(mapa, skopening_frame4_map, 0x80E2);
  copy_map_vram(mapa, g_vdp_scrolla_adr, 40, 28);
  unlze_moduled(&g_vram[0x9DC0], skopening_banner_cg);
  unlze_moduled(&g_vram[0x8C40], skopening_selection_cg);
  g_ram.actwk[3].r_ptr = &skbanner_init;
  g_ram.actwk[3].pattim = 30;
  p_actwk->r_ptr = &dummy;
}


static void dummy(SKC_sprite_status* p_actwk) {
}


static void deathegg_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = skopening_deathegg_pt;
  p_actwk->sproffset = 0x4680;
  fp16_set_integer(&p_actwk->xposi, 320);
  fp16_set_integer(&p_actwk->yposi, 176);
  p_actwk->sprpri = PRI_3;
  p_actwk->sprhs = 64;
  p_actwk->sprvs = 64;
  p_actwk->r_ptr = &deathegg_move0;
  deathegg_move0(p_actwk);
}


static void deathegg_move0(SKC_sprite_status* p_actwk) {
  if (fp16_get_integer(p_actwk->yposi) != 240) {
    p_actwk->yposi += 0x8000;
    if (g_ram.vs_scra_v_posit >> 16 != 256) {
      g_ram.vs_scra_v_posit += 1 << 16;
      copy_mapline_vram(mapb, g_vdp_scrollb_adr, g_ram.vs_scra_v_posit >> 16);
    }
    actionsub(p_actwk);
  }
  else {
    fp16_set_integer(&p_actwk->u.obj.actfree.deathegg.xposiwk, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&p_actwk->u.obj.actfree.deathegg.yposiwk, fp16_get_integer(p_actwk->yposi));
    g_ram.vs_scra_v_posit = g_ram.vs_scra_v_posit & 0xFFFF0000 | 0x8000;
    g_ram.DAT_08ffeed2 = 34;
    g_ram.scr_evta = 1;
    g_ram.scr_shake_flg = 30;
    p_actwk->r_ptr = &deathegg_move1;
    deathegg_move1(p_actwk);
  }
}


static void deathegg_move1(SKC_sprite_status* p_actwk) {
  shake_screen();
  if (g_ram.vs_scra_v_posit >> 16 != 256) {
    p_actwk->u.obj.actfree.deathegg.yposiwk -= 0x8000;
    g_ram.vs_scra_v_posit += 0x8000;
    copy_mapline_vram(mapb, g_vdp_scrollb_adr, g_ram.vs_scra_v_posit >> 16);
  }
  short xposi = fp16_get_integer(p_actwk->u.obj.actfree.deathegg.xposiwk);
  short yposi = fp16_get_integer(p_actwk->u.obj.actfree.deathegg.yposiwk);
  if (g_ram.scr_shake_flg != 0) {
    xposi -= g_ram.vs_scra_h_posit_copy >> 16;
    yposi -= g_ram.vs_scra_v_posit_copy >> 16;
  }
  fp16_set_integer(&p_actwk->xposi, xposi);
  fp16_set_integer(&p_actwk->yposi, yposi);
  actionsub(p_actwk);
}


static void mountain_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = skopening_mountain_pt;
  p_actwk->sproffset = 0x67A0;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 48;
  p_actwk->sprvs = 8;
  p_actwk->r_ptr = &mountain_move;
  mountain_move(p_actwk);
}


static void mountain_move(SKC_sprite_status* p_actwk) {
  short xposi = 320 - (g_ram.vs_scra_h_posit >> 16);
  short yposi = 424 - (g_ram.vs_scra_v_posit >> 16);
  if (g_ram.scr_shake_flg != 0) {
    xposi -= g_ram.vs_scra_h_posit_copy >> 16;
    yposi -= g_ram.vs_scra_v_posit_copy >> 16;
  }
  fp16_set_integer(&p_actwk->xposi, xposi);
  fp16_set_integer(&p_actwk->yposi, yposi);
  actionsub(p_actwk);
}


static void skbanner_init(SKC_sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (p_actwk->pattim == 0) {
    p_actwk->patbase = skopening_banner_pt;
    p_actwk->sproffset = 0x84EE;
    p_actwk->sprpri = PRI_0;
    p_actwk->sprhs = 124;
    p_actwk->sprvs = 40;
    fp16_set_integer(&p_actwk->xposi, 288);
    fp16_set_integer(&p_actwk->yposi, 384);
    p_actwk->yspeed = 0x400;
    p_actwk->u.obj.actfree.opening_banner.yposiwk = -0x600000;
    p_actwk->r_ptr = &skbanner_move;
    skbanner_move(p_actwk);
  }
}


static void skbanner_move(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actfree.opening_banner.yposiwk += p_actwk->yspeed * 0x100;
  signed char prev_dir = p_actwk->u.obj.actfree.opening_banner.dir;
  p_actwk->u.obj.actfree.opening_banner.dir = 0;
  short yaccel = 0x40;
  short yposi = fp16_get_integer(p_actwk->u.obj.actfree.opening_banner.yposiwk);
  if (yposi >= 0) {
    if (yposi == 0 && p_actwk->yspeed == -0x5B) {
      p_actwk->r_ptr = &actionsub;
      g_ram.actwk[5].r_ptr = skselection_init;
      g_ram.actwk[6].r_ptr = &chibi_init;
      g_ram.actwk[7].r_ptr = &skbannertm_init;
      g_ram.actwk[8].r_ptr = skcopyright_init;
      bitdevr(&g_vram[0xD000], skcopyright1997_cg);
    }
    else {
      p_actwk->u.obj.actfree.opening_banner.dir = -1;
      yaccel = -0x40;
    }
  }
  p_actwk->yspeed += yaccel;
  if (prev_dir != p_actwk->u.obj.actfree.opening_banner.dir) {
    p_actwk->yspeed /= 2;
  }
  yposi = -yposi + 280;
  fp16_set_integer(&p_actwk->yposi, yposi);
  actionsub(p_actwk);
}


static void skopening_cg_chg_init(SKC_sprite_status* p_actwk) {
  memcpy(&g_vram[0x1C60], &cg_chg_cg[0], 96);
  memcpy(&g_vram[0x1CC0], &cg_chg_cg[1600], 1312);
  p_actwk->u.obj.actfree.skopening_cg_chg.tim[0] = 180;
  p_actwk->r_ptr = &skopening_cg_chg_move;
}


static void skopening_cg_chg_move(SKC_sprite_status* p_actwk) {
  short offset = skopening_cg_chg_sub(sonicmouth_chg,
                                      &p_actwk->u.obj.actfree.skopening_cg_chg.tim[0],
                                      &p_actwk->u.obj.actfree.skopening_cg_chg.cnt[0]);
  if (offset >= 0) {
    memcpy(&g_vram[0x1C60], &cg_chg_cg[offset], 0x60);
  }
  offset = skopening_cg_chg_sub(skopening_sonichand_chg,
                             &p_actwk->u.obj.actfree.skopening_cg_chg.tim[1],
                             &p_actwk->u.obj.actfree.skopening_cg_chg.cnt[1]);
  if (offset >= 0) {
    memcpy(&g_vram[0x1CC0], &cg_chg_cg[0x120 + offset], 0x520);
  }
  offset = skopening_cg_chg_sub(knuckleshand1_chg,
                             &p_actwk->u.obj.actfree.skopening_cg_chg.tim[2],
                             &p_actwk->u.obj.actfree.skopening_cg_chg.cnt[2]);
  if (offset >= 0) {
    memcpy(&g_vram[0x21E0], &cg_chg_cg[0x1080 + offset], 0x5E0);
  }
  offset = skopening_cg_chg_sub(knuckleshand2_chg,
                             &p_actwk->u.obj.actfree.skopening_cg_chg.tim[3],
                             &p_actwk->u.obj.actfree.skopening_cg_chg.cnt[3]);
  if (offset >= 0) {
    memcpy(&g_vram[0x27C0], &cg_chg_cg[0x2220 + offset], 0x280);
  }
}


static short skopening_cg_chg_sub(signed char* p_chg, unsigned char* p_tim, unsigned char* p_cnt) {
  short offset = -1;
  if ((*p_tim)-- == 0) {
    *p_tim = p_chg[0];
    signed char patno = p_chg[*p_cnt + 1];
    if (patno >= 0) {
      ++*p_cnt;
      offset = patno * 32;
    }
    else {
      switch (patno) {
        case PATCHG_CONTROL_LOOP:
          *p_cnt = 1;
          offset = p_chg[1] * 32;
          break;
        case PATCHG_CONTROL_REWIND:
          *p_cnt -= p_chg[*p_cnt + 2];
          offset = p_chg[*p_cnt + 1] * 32;
          break;
      }
    }
  }
  return offset;
}

static signed char sonicmouth_chg[6] = { 5, 0, 3, 6, -2, 1 };
static signed char skopening_sonichand_chg[47] = {
   3, 41, 41, 41, 41, 41, 41, 41, 41, 41,
  41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
  41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
  41, 41, 41,  0,  0, 41, 82, 41,  0, 41,
  82, 41, 0, 41, 82, 41, -1
};
static signed char knuckleshand1_chg[17] = { 3, 0, 0, 0, 0, 0, 0, 0, 0, 47, 94, 47, 0, 47, 94, 47, -1 };
static signed char knuckleshand2_chg[9] = { 3, 0, 0, 20, 40, 20, 0, 0, -1 };


static void skselection_init(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, 264);
  fp16_set_integer(&p_actwk->yposi, 336);
  p_actwk->patbase = skselection_pt;
  p_actwk->sproffset = 0x8462;
  p_actwk->actflg.compound = 1;
  p_actwk->u.obj.compound.child_cnt = 2;
  p_actwk->u.obj.compound.children[0].xposi = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.compound.children[0].yposi = fp16_get_integer(p_actwk->yposi);
  p_actwk->u.obj.compound.children[0].patno = 0;
  g_ram.openingoption &= 1;
  p_actwk->direc.b.b0 = g_ram.openingoption * 128;
  p_actwk->direc.b.b1 = 8;
  p_actwk->r_ptr = &skselection_move;
  skselection_move(p_actwk);
}


static void skselection_move(SKC_sprite_status* p_actwk) {
  if (!(p_actwk->direc.b.b0 & 0x7F)) {
    if (g_ram.swdata1.pressed.u == 1) {
      p_actwk->direc.b.b0 = direction_sub(p_actwk->direc.b.b0, 8);
      p_actwk->direc.b.b1 = 248;
      if (g_ram.openingoption-- == 0) {
        g_ram.openingoption = 1;
      }
    }
    if (g_ram.swdata1.pressed.d == 1) {
      p_actwk->direc.b.b0 = direction_sum(p_actwk->direc.b.b0, 8);
      p_actwk->direc.b.b1 = 8;
      ++g_ram.openingoption;
      g_ram.openingoption &= 1;
    }
    if (g_ram.swdata1.pressed.u == 1 || g_ram.swdata1.pressed.d == 1) {
      soundset(91);
    }
  }
  if (p_actwk->direc.b.b0 & 0x7F) {
    p_actwk->direc.b.b0 = direction_sum(p_actwk->direc.b.b0, p_actwk->direc.b.b1);
  }
  unsigned char direction = direction_sum(p_actwk->direc.b.b0, 152);
  short sin, cos;
  sinset(direction, &sin, &cos);
  short xposi1 = cos * 5 / 256;
  short yposi1 = sin * 5 / 256;
  short xposi2 = -xposi1;
  short yposi2 = -yposi1;
  xposi1 += fp16_get_integer(p_actwk->xposi);
  yposi1 += fp16_get_integer(p_actwk->yposi);
  xposi2 += fp16_get_integer(p_actwk->xposi);
  yposi2 += fp16_get_integer(p_actwk->yposi);
  direction = direction_sub(p_actwk->direc.b.b0, 160);
  p_actwk->u.obj.compound.children[0].xposi = direction < 128 ? xposi1 : xposi2;
  p_actwk->u.obj.compound.children[0].yposi = direction < 128 ? yposi1 : yposi2;
  p_actwk->u.obj.compound.children[0].patno = direction < 128 ? 0 : 2;
  p_actwk->u.obj.compound.children[1].xposi = direction < 128 ? xposi2 : xposi1;
  p_actwk->u.obj.compound.children[1].yposi = direction < 128 ? yposi2 : yposi1;
  p_actwk->u.obj.compound.children[1].patno = direction < 128 ? 3 : 1;
  actionsub(p_actwk);
}


static void chibi_init(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, 208);
  fp16_set_integer(&p_actwk->yposi, 332);
  p_actwk->patbase = skselection_pt;
  p_actwk->sproffset = 0x8462;
  p_actwk->mstno = g_ram.openingoption;
  p_actwk->mstrestart = g_ram.openingoption;
  p_actwk->patcnt = 1;
  p_actwk->r_ptr = &chibi_move;
  chibi_move(p_actwk);
}


static void chibi_move(SKC_sprite_status* p_actwk) {
  p_actwk->mstno = g_ram.openingoption;
  patchg(p_actwk, chibi_chg);
  actionsub(p_actwk);
}


static signed char* chibi_chg[3] = {
  chibi_chg0,
  chibi_chg1,
  chibi_chg2
};


static signed char chibi_chg0[6] = { 7, 4, 5, 6, -2, 2 };
static signed char chibi_chg1[6] = { 7, 4, 7, 8, -2, 2 };
static signed char chibi_chg2[3] = { 7, 4, -1 };


static void skbannertm_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = skbannertm_pt;
  p_actwk->sproffset = 0x8462;
  fp16_set_integer(&p_actwk->xposi, 418);
  fp16_set_integer(&p_actwk->yposi, 285);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 4;
  p_actwk->r_ptr = &skbannertm_move;
  skbannertm_move(p_actwk);
}


static void skbannertm_move(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.mdstatus, 7)) return;

  actionsub(p_actwk);
}


static void skcopyright_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = skcopyright_pt;
  p_actwk->sproffset = 0x8680;
  fp16_set_integer(&p_actwk->xposi, 327);
  fp16_set_integer(&p_actwk->yposi, 344);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 44;
  p_actwk->sprvs = 4;
  p_actwk->r_ptr = &actionsub;
  actionsub(p_actwk);
}


static void copy_mapline_vram(unsigned char* p_source, unsigned short offset, short line_cnt) {
  line_cnt -= 16;
  if (line_cnt >= 0 && !(line_cnt & 7)) {
    line_cnt &= 0xF8;
    memcpy(&g_vram[offset + line_cnt * 16], &p_source[line_cnt * 10], 80);
  }
}


static void shake_screen(void) {
  if (g_ram.scr_shake_flg == 0) return;

  --g_ram.scr_shake_flg;
  if (g_ram.scr_shake_flg == 0) {
    ++g_ram.scr_evta;
  }
  unsigned char* p_offsets = &shakeoffset_tbl[g_ram.systemtimer & 0x3F];
  g_ram.vs_scra_v_posit_copy = p_offsets[0] << 16 | g_ram.vs_scra_v_posit_copy & 0x0000FFFF;
  g_ram.vs_scra_h_posit_copy = p_offsets[1] << 16 | g_ram.vs_scra_h_posit_copy & 0x0000FFFF;
}


static void skopening_scroll(void) {
  g_ram.vscroll.a = g_ram.scra_v_posit >> 16;
  g_ram.vscroll.b = g_ram.vs_scra_v_posit >> 16;
  if (g_ram.scr_shake_flg != 0) {
    g_ram.vscroll.a += g_ram.vs_scra_v_posit_copy >> 16;
    g_ram.vscroll.b += g_ram.vs_scra_v_posit_copy >> 16;
  }
  short offset = g_ram.scr_shake_flg == 0 ? 0 : g_ram.vs_scra_h_posit_copy >> 16;

  switch (g_ram.scr_evta) {
    case 0:
    case 3:
      for (int i = 0; i < 224; ++i) {
        g_ram.hscrollbuff[i * 2] = -((g_ram.scra_h_posit >> 16) + offset);
        g_ram.hscrollbuff[i * 2 + 1] = -((g_ram.vs_scra_h_posit >> 16) + offset);
      }
      break;
    case 1:
      for (int i = 0; i < 112; ++i) {
        long value = random();
        g_ram.hscrollbuff[i * 4] = (short)(value & 7);
        g_ram.hscrollbuff[i * 4 + 1] = -(offset + (g_ram.vs_scra_h_posit >> 16));
        g_ram.hscrollbuff[i * 4 + 2] = -(short)(value >> 16 & 7);
        g_ram.hscrollbuff[i * 4 + 3] = -(offset + (g_ram.vs_scra_h_posit >> 16));
      }
      break;
    case 2:
      --g_ram.DAT_08ffeed2;
      if (g_ram.DAT_08ffeed2 == 0) {
        ++g_ram.scr_evta;
        memset(&g_vram[0xC500], 0, 1024);
        memcpy(&g_ram.colorwk[16], knuckles_color, sizeof(unsigned short) * 16);
        g_ram.actwk[4].r_ptr = &skopening_cg_chg_init;

        for (int i = 0; i < 224; ++i) {
          g_ram.hscrollbuff[i * 2] = -(g_ram.scra_h_posit >> 16);
          g_ram.hscrollbuff[i * 2 + 1] = -(g_ram.vs_scra_h_posit >> 16);
        }
      }
      else {
        for (int i = 0; i < 112; ++i) {
          long value = random();
          g_ram.hscrollbuff[i * 4] += 8;
          g_ram.hscrollbuff[i * 4] += value & 7;
          if (g_ram.hscrollbuff[i * 4] >= 252) {
            g_ram.hscrollbuff[i * 4] = 252;
          }
          g_ram.hscrollbuff[i * 4 + 1] = -(g_ram.vs_scra_h_posit >> 16);
          g_ram.hscrollbuff[i * 4 + 2] -= 8;
          g_ram.hscrollbuff[i * 4 + 2] -= (short)(value >> 16 & 7);
          if (g_ram.hscrollbuff[i * 4 + 2] <= -260) {
            g_ram.hscrollbuff[i * 4 + 2] = -260;
          }
          g_ram.hscrollbuff[i * 4 + 3] = -(g_ram.vs_scra_h_posit >> 16);
        }
      }
      break;
  }
}


static unsigned char shakeoffset_tbl[66] = {
  1, 2, 1, 3, 1, 2, 2, 1, 2, 3,
  1, 2, 1, 2, 0, 0, 2, 0, 3, 2,
  2, 3, 2, 2, 1, 3, 0, 0, 1, 0,
  1, 3, 1, 2, 1, 3, 1, 2, 2, 1,
  2, 3, 1, 2, 1, 2, 0, 0, 2, 0,
  3, 2, 2, 3, 2, 2, 1, 3, 0, 0,
  1, 0, 1, 3, 1, 2
};


static SKC_sprite_pattern* skselection_pt[9] = {
  &skselection_pt00,
  &skselection_pt01,
  &skselection_pt02,
  &skselection_pt03,
  &skselection_pt04,
  &skselection_pt05,
  &skselection_pt06,
  &skselection_pt07,
  &skselection_pt08
};


static SKC_sprite_pattern skselection_pt00 = {
  2,
  {
    { -8, 13, 0x0000, -36 },
    { -8, 13, 0x0008,  -4 },
  }
};
static SKC_sprite_pattern skselection_pt01 = {
  2,
  {
    { -8, 13, 0x0010, -36 },
    { -8, 13, 0x0018,  -4 },
  }
};
static SKC_sprite_pattern skselection_pt02 = {
  4,
  {
    { -9, 13, 0x2020, -37 },
    { -9, 13, 0x2028,  -5 },
    { -9, 13, 0x2030,  27 },
    { -9,  1, 0x2038,  59 },
  }
};
static SKC_sprite_pattern skselection_pt03 = {
  4,
  {
    { -9, 13, 0x203A, -37 },
    { -9, 13, 0x2042,  -5 },
    { -9, 13, 0x204A,  27 },
    { -9,  1, 0x2052,  59 },
  }
};
static SKC_sprite_pattern skselection_pt04 = {
  1,
  {
    { -12, 10, 0x0066, -12 },
  }
};
static SKC_sprite_pattern skselection_pt05 = {
  1,
  {
    { -12, 10, 0x0054, -12 },
  }
};
static SKC_sprite_pattern skselection_pt06 = {
  1,
  {
    { -12, 10, 0x005D, -12 },
  }
};
static SKC_sprite_pattern skselection_pt07 = {
  1,
  {
    { -12, 10, 0x206F, -12 },
  }
};
static SKC_sprite_pattern skselection_pt08 = {
  1,
  {
    { -12, 10, 0x2078, -12 },
  }
};


static SKC_sprite_pattern* skbannertm_pt[1] = {
  &skbannertm_pt00
};


static SKC_sprite_pattern skbannertm_pt00 = {
  1,
  {
    { -4, 4, 0x008A, -8 },
  }
};


static SKC_sprite_pattern* skcopyright_pt[1] = {
  &skcopyright_pt00
};


static SKC_sprite_pattern skcopyright_pt00 = {
  6,
  {
    { 0,  0, 0x0000,   0 },
    { 0,  8, 0x0001,   8 },
    { 0,  4, 0x0004,  32 },
    { 0,  8, 0x0001,  48 },
    { 0, 12, 0x0006,  72 },
    { 0,  4, 0x000A, 104 },
  }
};

static unsigned char s3copyright1997_cg[209] = { 0x0E, 0x80, 0x80, 0x02, 0x00, 0x14, 0x08, 0x24, 0x0B, 0x35, 0x1B, 0x47, 0x7C, 0x55, 0x1C, 0x74, 0x0A, 0x8E, 0x03, 0x02, 0x14, 0x09, 0x25, 0x1A, 0x34, 0x0C, 0x45, 0x1E, 0x8F, 0x03, 0x03, 0x15, 0x1D, 0x27, 0x7D, 0xFF, 0x1F, 0xEC, 0x58, 0xFF, 0xBC, 0xE4, 0x92, 0x63, 0x55, 0xF3, 0x57, 0x24, 0x92, 0xFF, 0xBC, 0xE3, 0x5F, 0x81, 0x77, 0x36, 0xE1, 0x71, 0xD7, 0xF8, 0x1D, 0xBD, 0xA1, 0x7C, 0xD5, 0xBE, 0x33, 0x0E, 0xA2, 0x45, 0x50, 0x89, 0xF9, 0xAD, 0xE0, 0xA3, 0xC3, 0xA8, 0xC1, 0x88, 0x91, 0x54, 0x22, 0x7E, 0x6B, 0x78, 0x28, 0xF1, 0xDB, 0xFB, 0x12, 0x7D, 0xF9, 0x35, 0x43, 0xB5, 0x0A, 0x35, 0x0A, 0x3A, 0x48, 0xEF, 0xE9, 0xDE, 0x4F, 0x11, 0xFB, 0xF1, 0xDC, 0xD4, 0x38, 0x6B, 0x68, 0x72, 0xE2, 0x4F, 0xC0, 0xB1, 0xF1, 0x9A, 0xDA, 0x26, 0xB6, 0x89, 0x1D, 0xE5, 0xFA, 0xF2, 0xDE, 0xD1, 0xD3, 0x42, 0x84, 0x4D, 0x6D, 0x13, 0xF3, 0x42, 0x8F, 0x0C, 0xCA, 0x43, 0x30, 0x51, 0x97, 0xD8, 0x5C, 0x55, 0x0B, 0x88, 0x77, 0x30, 0xE3, 0xEC, 0xD7, 0xF8, 0x17, 0x10, 0xF8, 0xEA, 0xB9, 0xFE, 0xF1, 0x9E, 0x62, 0x32, 0x11, 0xA8, 0x66, 0x84, 0x3A, 0xC1, 0x47, 0x8E, 0xF3, 0xA7, 0xA1, 0x19, 0xBC, 0xDE, 0x54, 0x23, 0x06, 0x7A, 0xBA, 0x79, 0x88, 0xCF, 0x9A, 0xF8, 0xAB, 0x68, 0x9B, 0x67, 0xA3, 0xB1, 0xF6, 0x1A, 0xA4, 0xED, 0xAA, 0x42, 0x7B, 0x5B, 0x68, 0x91, 0x44, 0xC4, 0x80 };
static unsigned char skcopyright1997_cg[183] = { 0x0C, 0x80, 0x80, 0x02, 0x00, 0x14, 0x09, 0x25, 0x1B, 0x35, 0x1A, 0x44, 0x0B, 0x55, 0x1D, 0x68, 0xFB, 0x74, 0x0A, 0x81, 0x03, 0x03, 0x16, 0x3C, 0x37, 0x7C, 0x8A, 0x03, 0x02, 0x14, 0x08, 0x25, 0x1C, 0x34, 0x0C, 0x46, 0x3D, 0x58, 0xFA, 0xFF, 0x1F, 0xEE, 0xD8, 0xFE, 0x9C, 0x10, 0x44, 0xF2, 0xAF, 0x9B, 0x82, 0x08, 0x7F, 0x4E, 0x79, 0xF8, 0xB7, 0xB8, 0xDB, 0x95, 0xD7, 0x5F, 0x6F, 0x6F, 0x48, 0x57, 0xCD, 0xBE, 0xB3, 0x0F, 0x11, 0x02, 0xA9, 0x44, 0x5F, 0x35, 0x82, 0x9F, 0x47, 0x4C, 0xC1, 0x88, 0x81, 0x54, 0xA2, 0x2F, 0x9A, 0xC1, 0x4F, 0xA3, 0xBF, 0x37, 0x07, 0xE8, 0x6E, 0x2A, 0x87, 0xB5, 0x2A, 0x79, 0x28, 0xFD, 0x09, 0x03, 0xDF, 0xCA, 0xA3, 0xE5, 0xC5, 0x5B, 0x5D, 0x70, 0xED, 0x1F, 0xC1, 0x3E, 0xA7, 0x37, 0xE4, 0xA1, 0x69, 0x08, 0x7D, 0x75, 0xA8, 0xBF, 0xE8, 0xDB, 0x17, 0x57, 0xDA, 0xEB, 0x15, 0xBA, 0x8E, 0xC7, 0xC1, 0xCE, 0x78, 0x7B, 0x28, 0xE5, 0xC0, 0xAB, 0x50, 0x29, 0x47, 0x0F, 0x05, 0xA7, 0xBC, 0x19, 0xEC, 0xA3, 0x35, 0x95, 0xAC, 0x94, 0x60, 0xC5, 0xA6, 0x79, 0x8E, 0x5E, 0x5F, 0x25, 0xA1, 0x57, 0x63, 0x6D, 0x19, 0x31, 0x3F, 0xD1, 0x54, 0x9D, 0x5A, 0x13, 0xD2, 0xFB, 0x81, 0x76, 0x34 };
