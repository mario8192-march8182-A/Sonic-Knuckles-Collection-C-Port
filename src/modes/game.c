#include "game.h"
#include <stdbool.h>
#include <string.h>
#include "../data/demoswdata.h"
#include "../data/mapinittbl.h"
#include "../data/scd.h"
#include "../data/cg/friend.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../types/swdata.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/fp8.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../cgchange.h"
#include "../color.h"
#include "../constants.h"
#include "../dev.h"
#include "../io.h"
#include "../score.h"
#include "../scroll.h"
#include "../shared.h"
#include "../sound.h"
#include "../objects/common.h"
#include "../objects/fox.h"
#include "../objects/knuckles.h"
#include "../objects/player.h"
#include "../objects/playsub.h"
#include "../objects/zone.h"
#include "../objects/zone00/ev0000.h"
typedef struct SKC_watercoli_item {
  unsigned short xstart;
  unsigned short xend;
  unsigned short ystart;
  unsigned short yend;
  short xspeed;
  short yspeed;
  unsigned char movement;
}
SKC_watercoli_item;
typedef struct SKC_watercoli_data {
  unsigned short cnt;
  SKC_watercoli_item items[];
}
SKC_watercoli_data;
static void play_type_set(void);
static void stage_act_set(void);
static void play_act_set(void);
static void baria_act_set(void);
static SKC_sprite_status_handler get_vsplay_handler(SKC_character_id id);
static void colibufferclr(SKC_sprite_status* p_actwk);
static void watercnt(void);
static short waterpositbl[16][2];
static void watercntsub(void);
static void water0000chk(void);
static void water0001chk(void);
static void water0001chk2(SKC_sprite_status* p_actwk);
static void water0100chk(void);
static void water0101chk(void);
static void worknai(void);
static void water0600chk(void);
static void water0601chk(void);
static void worknai2(void);
static void water0d01chk(void);
static void waterchk(unsigned short (*p_watertbl)[2]);
static void watercoli(void);
static void watercolisub(SKC_sprite_status* p_actwk, unsigned char* p_flag, SKC_pad pad, bool pl2);
static void FUN_0041c7d2(void);
static void FUN_0041c829(SKC_sprite_status* p_actwk, SKC_pad pad);
static void FUN_0041c9b7(SKC_sprite_status* p_actwk, SKC_pad pad);
static void FUN_0041cb2f(SKC_sprite_status* p_actwk, SKC_pad pad, signed char d0);
static void FUN_0041cdca(SKC_sprite_status* p_actwk, SKC_pad pad);
static void FUN_0041cf0a(SKC_sprite_status* p_actwk);
static void FUN_0041d00a(SKC_sprite_status* p_actwk, signed char d0);
static void scdset(void);
static void sysdirinit(void);
static void sysdirchg(void);
static void syspatchg(void);
static void mapinit(void);
static void waterset(void);
static void watercolorset(void);

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];
extern int g_sonic3_alone;
extern int g_debug_mode;
extern unsigned long g_vdp_mode;
extern unsigned long g_vdp_scrolla_adr;
extern unsigned long g_vdp_scrollb_adr;
extern int g_vdp_hscroll_scanline;
extern unsigned long g_bg_color_index;
extern void v_int(void);


unsigned char bgm_tbl[24][2] = {
  {  1,  2 },
  {  3,  4 },
  {  5,  6 },
  {  7,  8 },
  {  9, 10 },
  { 11, 12 },
  { 13, 14 },
  { 15, 16 },
  { 17, 18 },
  { 19, 20 },
  { 21, 21 },
  { 22, 23 },
  { 26, 26 },
  { 28, 21 },
  { 32, 32 },
  { 33, 33 },
  { 34, 34 },
  { 35, 35 },
  { 36, 36 },
  { 30, 30 },
  { 27, 27 },
  { 29, 29 },
  { 25, 20 },
  { 23, 20 }
};


void game(void) {
  SET_BIT(g_ram.gmmode, 7);
  if (!BIT_IS_SET(g_ram.demoflag, 7)) {
    soundset(-31);
  }
  g_ram.nopause = 0;
  if (g_ram.vs_flag == 0) {
    if (g_ram.stageno != ENDING && g_ram.plresetflag == 0 || g_ram.stageno != MASTER_EMERALD_SHRINE) {
      fadeout();
    }
    else {
      flashout();
    }
  }
  bool play_type_is_sonic;
  if (!BIT_IS_SET(g_ram.demoflag, 7)) {
    scrinit();
    g_ram.gametimer = 0;
    if (g_ram.markerno != 0) {
      if (g_ram.marker_flag == 0) {
        g_ram.stageno = g_ram.stageno_s;
        g_ram.stageno_i = g_ram.stageno_is;
      }
      else {
        g_ram.stageno = g_ram.stageno_s2;
        g_ram.stageno_i = g_ram.stageno_is2;
      }
    }
    play_type_is_sonic = g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC;
    unsigned short stageno = g_ram.stageno;
    if (stageno == ANGEL_ISLAND_ACT_1 && (!play_type_is_sonic || g_ram.markerno != 0)) {
      stageno = ANGEL_ISLAND_ACT_1_NO_INTRO;
    }
    if (g_ram.stageno != FLYING_BATTERY_ACT_2 || g_ram.markerno != 6) {
      unsigned char ini_cg = mapinittbl[get_zone(stageno)][get_act(stageno)].ini_cg_no1;
      if (ini_cg != 0) {
        divdevset(ini_cg);
      }
    }
    play_type_set();
    play_type_is_sonic = g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC;
    if (g_ram.markerno == 0 && g_ram.stageno == ANGEL_ISLAND_ACT_1 && play_type_is_sonic) {
      divdevset(1);
      divdevset(10);
    }
    else {
      unsigned short id = 6;
      if (g_ram.vs_flag == 0) {
        id = 5;
        if (g_ram.play_type != PLAY_TYPE_KNUCKLES) {
          id = 1;
          if (g_ram.play_type == PLAY_TYPE_MILES) {
            id = BIT_IS_SET(g_ram.mdstatus, 7) ? 7 : 82;
          }
        }
      }
      divdevset(id);
    }
  }
  memset(g_ram.pbuffer, 0, sizeof(g_ram.pbuffer));
  memset(g_ram.actwk, 0, sizeof(g_ram.actwk));
  g_ram.DAT_08fff628 = 0;
  g_ram.int_flg = 0;
  g_ram.linkdata = 0;
  g_ram.clchgcnt = 0;
  g_ram.clchgtim = 0;
  g_ram.ranum = 0;
  g_ram.pauseflag = 0;
  g_ram.waterposi = 0;
  g_ram.waterposi_m = 0;
  g_ram.watermoveposi = 0;
  g_ram.waterspeed = 0;
  g_ram.water_flag = 0;
  g_ram.waterflag = 0;
  g_ram.clchgtim2 = 0;
  g_ram.clchgcnt2 = 0;
  g_ram.clchgcnt2 = 0;
  g_ram.clchgcnt3 = 0;
  g_ram.clchgcnt4 = 0;
  g_ram.clchgtim3 = 0;
  g_ram.clchgtim4 = 0;
  g_ram.ssonicclchgcnt = 0;
  g_ram.ssonicclchgtim = 0;
  g_ram.ssonicclchg = 0;
  // DAT_08fff660
  g_ram.scd_bg_flag = 0;
  g_ram.DAT_08fff665 = 0;
  g_ram.ssonicdashtim = 0;
  g_ram.smilesflag = 0;
  g_ram.smilesclchgcnt = 0;
  g_ram.smilesclchgtim = 0;
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  g_ram.colibuffer_id = 0;
  g_ram.ssonicringtim = 0;
  g_ram.custom_follow_flag = 0;
  g_ram.custom_follow_xposi = 0;
  g_ram.custom_follow_yposi = 0;
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
  g_ram.sysdirchgbits;
  g_ram.sysdirec0 = 0;
  g_ram.sysdirspd0 = 0;
  g_ram.sysdirec1 = 0;
  g_ram.sysdirspd1 = 0;
  g_ram.sysdirec2 = 0;
  g_ram.sysdirspd2 = 0;
  g_ram.sysdirec3 = 0;
  g_ram.sysdirspd3 = 0;
  g_ram.sysdirec4 = 0;
  g_ram.sysdirspd4 = 0;
  g_ram.sysdirec5 = 0;
  g_ram.sysdirspd5 = 0;
  g_ram.sysdirec6 = 0;
  g_ram.sysdirspd6 = 0;
  g_ram.sysdirec7 = 0;
  g_ram.sysdirspd7 = 0;
  g_ram.sysdirec8 = 0;
  g_ram.sysdirspd8 = 0;
  g_ram.sysdirec9 = 0;
  g_ram.sysdirspd9 = 0;
  g_ram.sysdirec10 = 0;
  g_ram.sysdirspd10 = 0;
  g_ram.sysdirec11 = 0;
  g_ram.sysdirspd11 = 0;
  g_ram.sysdirec12 = 0;
  g_ram.sysdirspd12 = 0;
  g_ram.sysdirec13 = 0;
  g_ram.sysdirspd13 = 0;
  g_ram.sysdirec14 = 0;
  g_ram.sysdirspd14 = 0;
  g_ram.sysdirec15 = 0;
  g_ram.sysdirspd15 = 0;
  g_ram.sys_pattim = 0;
  g_ram.sys_patno = 0;
  g_ram.sys_pattim2 = 0;
  g_ram.sys_patno2 = 0;
  g_ram.sys_pattim3 = 0;
  g_ram.sys_patno3 = 0;
  g_ram.sys_pattim4 = 0;
  g_ram.sys_patno4 = 0;
  g_ram.sys_ringtimer = 0;
  // DAT_08fffa80
  // DAT_08fffa82
  // DAT_08fffa84
  // DAT_08fffa86
  // DAT_08fffa88
  // DAT_08fffa8a
  g_ram.scralim_m_right = 0;
  g_ram.scralim_m_left = 0;
  g_ram.scralim_m_up = 0;
  g_ram.scralim_m_down = 0;
  memset(g_ram.emy_wrt_flg, 0, sizeof(g_ram.emy_wrt_flg));
  g_ram.DAT_08fffaa2 = 0;
  g_ram.DAT_08fffaa3 = 0;
  g_ram.DAT_08fffaa4_obj = 0;
  g_ram.save_obj = 0;
  g_ram.act_clear_flag = 0;
  g_ram.DAT_08fffaa9 = 0;
  g_ram.act_start_flag = 0;
  // DAT_08fffaab
  g_ram.DAT_08fffaac = 0;
  g_ram.gost08_count = 0;
  g_ram.DAT_08fffaae_obj = 0;
  g_ram.scralim_b_up = 0;
  g_ram.scralim_b_down = 0;
  g_ram.scralim_b_left = 0;
  g_ram.scralim_b_right = 0;
  g_ram.DAT_08fffab8_bitfield = 0;
  // DAT_08fffab9
  g_ram.DAT_08fffaba_obj = 0;
  g_ram.DAT_08fffabe = 0;
  g_ram.fade_flag = 0;
  // DAT_08fffac0
  // DAT_08fffac1
  g_ram.DAT_08fffacd = 0;
  g_ram.DAT_08ffface = 0;
  g_ram.cchg_callback_ptr = 0;
  memset(g_ram.cchg_work, 0, sizeof(g_ram.cchg_work));
  // DAT_08fffaf0
  // DAT_08fffaf4
  // DAT_08fffaf8
  // DAT_08fffafa
  // DAT_08fffafc
  sprtblinit2();
  g_vdp_scrolla_adr = 0xC000;
  g_vdp_scrollb_adr = 0xE000;
  g_bg_color_index = 48;
  g_vdp_hscroll_scanline = 1;
  if (g_ram.vs_flag == 0 && g_ram.demoflag == 0 && g_debug_mode != 0) {
    g_ram.debugflag = 1;
  }
  if (g_ram.editmodecheat != 0 && g_ram.swdata1.down.a == 1) {
    g_ram.debugflag = 1;
  }
  g_ram.vdp_hint_cache = 255;
  if (g_ram.vs_flag != 0) {
    g_vdp_scrolla_adr = 0x8000;
    g_vdp_scrollb_adr = 0xA000;
    g_vdp_mode = get_zone(g_ram.stageno) != BALLOON_PARK ? 4 : 3;
  }
  unsigned short color_no = g_ram.play_type != PLAY_TYPE_KNUCKLES ? 3 : 5;
  colorset2(color_no);
  waterset();
  memset(&g_ram.colorwk3[16], 0, sizeof(unsigned short) * 48);
  if (!BIT_IS_SET(g_ram.demoflag, 7)) {
    short id = bgm_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
    if (g_ram.stageno == ANGEL_ISLAND_ACT_2 && g_ram.markerno == 3) {
      id = 1;
    }
    bool is_knuckles_story = g_ram.stageno == MUSHROOM_HILL_ACT_1 && g_ram.play_type == PLAY_TYPE_KNUCKLES
                             && g_ram.cartridge != 0 && g_ram.markerno == 0;
    if (is_knuckles_story) {
      id = 31;
    }
    g_ram.bgm_act = id;
    bgmset(g_ram.bgm_act);
    bool angel_island_with_intro = g_ram.stageno == ANGEL_ISLAND_ACT_1 && play_type_is_sonic && g_ram.markerno == 0;
    if (is_knuckles_story) {
      bitdevr(&g_vram[0xB000], ricky_cg);
      bitdevr(&g_vram[0xB240], cucky_cg);
    }
    else if (!angel_island_with_intro && g_ram.stageno != MASTER_EMERALD_SHRINE && g_ram.notitle == 0) {
      g_ram.actwk[8].r_ptr = &title;

      do {
        g_ram.int_flg = 12;
        v_int();
        action();
        patset();
      }
      while (g_ram.actwk[8].u.obj.actfree.title.unknown_flag != 0);
    }
    g_ram.notitle = 0;
    scoreinit();
  }
  colorset(3);
  scr_set();
  scroll();
  mapinit();
  mapwrt();
  LevelSetup();
  cg_change_init();
  scdset();
  watercnt();
  memset(&g_ram.swdata, 0, sizeof(g_ram.swdata));
  memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata0));
  memset(&g_ram.swdata1, 0, sizeof(g_ram.swdata1));
  memset(&g_ram.swdata2, 0, sizeof(g_ram.swdata2));
  g_ram.pl_input_lock_flag = 1;
  g_ram.pl2_input_lock_flag = 1;
  g_ram.DAT_08fff711 = 0;
  if (g_ram.watermode != 0 && get_zone(g_ram.stageno) == HYDROCITY) {
    g_ram.actwk[109].r_ptr = &water;
    g_ram.actwk[5].r_ptr = &shibuki;
    g_ram.actwk[5].u.obj.userflag = 1;
  }
  if (g_ram.stageno == MUSHROOM_HILL) {
    g_ram.actwk[4].r_ptr = &Obj_MHZ_Pollen_Spawner;
  }
  if (g_ram.markerno == 0) {
    g_ram.plring = 0;
    memset(&g_ram.pltime, 0, sizeof(g_ram.pltime));
    g_ram.plring_f2 = 0;
    g_ram.pl2ring = 0;
    memset(&g_ram.pl2time, 0, sizeof(g_ram.pl2time));
    memset(&g_ram.plpowerdat_s, 0, sizeof(g_ram.plpowerdat_s));

    switch (g_ram.stageno) {
      default:
        memset(&g_ram.plpowerdat_s2, 0, sizeof(g_ram.plpowerdat_s2));
        // fall-through
      case LAVA_REEF_BOSS:
      case DEATH_EGG_BOSS:
        g_ram.plresetflag = 0;
        // fall-through
      case GUMBALL_MACHINE_ACT_1:
      case GUMBALL_MACHINE_ACT_2:
      case ROLLING_JUMP_ACT_1:
      case ROLLING_JUMP_ACT_2:
      case SLOT_MACHINE_ACT_1:
      case SLOT_MACHINE_ACT_2:
      case MASTER_EMERALD_SHRINE:
        break;
    }
  }
  g_ram.pltimeover_f = 0;
  g_ram.editmode = 0;
  g_ram.gameflag = 0;
  g_ram.plring_act = 0;
  g_ram.pl2ring_act = 0;
  g_ram.DAT_08fffecc = 0;
  g_ram.DAT_08fffece = 0;
  g_ram.DAT_08fffe65 = 0;
  g_ram.ssonicflag = 0;
  sysdirinit();
  g_ram.plscore_f = 1;
  g_ram.plring_f = 1;
  g_ram.pltime_f = !(g_ram.stageno == ENDING || g_ram.stageno == MASTER_EMERALD_SHRINE);
  g_ram.DAT_08fff711 = !(g_ram.stageno == ENDING || g_ram.stageno == MASTER_EMERALD_SHRINE);
  stage_act_set();
  actsetchk();
  ringactsetchk();
  Draw_LRZ_Special_Rock_Sprites();
  action();
  patset();
  cg_change();
  g_ram.demotimer = 1800;
  watercolorset();
  memset(&g_ram.colorwk3[16], 0, sizeof(unsigned short) * 48);
  g_ram.pl_input_lock_flag = 0;
  g_ram.pl2_input_lock_flag = 0;
  demoset();
  if (g_ram.vs_flag == 0) {
    if (!(g_ram.stageno == ANGEL_ISLAND_ACT_1 && g_ram.markerno == 0) && get_zone(g_ram.stageno) < AZURE_LAKE) {
      set_friend_cg();
    }
    g_ram.colorcnt = 48;
    fadein0();
    g_ram.fadecnt = 22;
    g_ram.actwk[8].u.obj.timer = 22;
    g_ram.swdata1.down.u = 1;
    g_ram.swdata1.down.d = 1;
    g_ram.swdata1.down.l = 1;
    g_ram.swdata1.down.r = 1;
    g_ram.swdata1.down.b = 1;
    g_ram.swdata1.down.c = 1;
    g_ram.swdata1.down.a = 1;
    g_ram.swdata2.down.u = 1;
    g_ram.swdata2.down.d = 1;
    g_ram.swdata2.down.l = 1;
    g_ram.swdata2.down.r = 1;
    g_ram.swdata2.down.b = 1;
    g_ram.swdata2.down.c = 1;
    g_ram.swdata2.down.a = 1;
    CLEAR_BIT(g_ram.markerno, 7);
    CLEAR_BIT(g_ram.gmmode, 7);

    do {
      g_ram.int_flg = 8;
      v_int();
      ++g_ram.gametimer;
      demoplay();
      colchg();
      SpecialEvents();
      actsetchk();
      action();
      if (g_ram.gameflag == 0) {
        scroll();
        ScreenEvents();
        watercnt();
        ringactsetchk();
        if (get_zone(g_ram.stageno) == LAVA_REEF) {
          Draw_LRZ_Special_Rock_Sprites();
        }
        cg_change();
        sysdirchg();
        syspatchg();
        patset();
        if (get_zone(g_ram.stageno) == SLOT_MACHINE) {
          Slots_RenderLayout();
          Slots_CycleOptions();
        }
      }
    }
    while (g_ram.gameflag == 0 && ((g_ram.gmmode == DEMOMD && g_ram.demotimer != 0) || g_ram.gmmode == GAMEMD));

    if (g_ram.gmmode == DEMOMD) {
      g_ram.gmmode = LOGOMD;
    }
  }
  else {
    g_ram.colorcnt = 64;
    fadein0();
    g_ram.fadecnt = 22;
    long wk = 0;
    CLEAR_BIT(g_ram.gmmode, 7);

    do {
      g_ram.int_flg = 8;
      v_int();
      ++g_ram.gametimer;
      demoplay();
      action();
      scroll();
      if (g_ram.gameflag == 0) {
        ScreenEvents();
        cg_change();
        patset();
        colchg();
      }
    }
    while (g_ram.gameflag == 0 && ((g_ram.gmmode == DEMOMD && g_ram.demotimer != 0) || g_ram.gmmode == GAMEMD));

    if (g_ram.gameflag != 0) {
      fadeout();
    }
    else if (g_ram.gmmode == DEMOMD) {
      g_ram.gmmode = LOGOMD;
    }
  }
}


static void play_type_set(void) {
  if (g_ram.gmmode != DEMOMD_INIT && g_ram.vs_flag == 0) {
    g_ram.play_type = g_ram.stagesel_play_type;
  }
  else if (get_zone(g_ram.stageno) == MUSHROOM_HILL) {
    g_ram.play_type = PLAY_TYPE_KNUCKLES;
  }
  else {
    g_ram.play_type = g_ram.cartridge == 0 ? PLAY_TYPE_SONIC_AND_MILES : PLAY_TYPE_SONIC;
  }
}


static void stage_act_set(void) {
  g_ram.actwk[2].r_ptr = &colibufferclr;
  play_act_set();
  baria_act_set();
  if (g_ram.markerno == 0 && g_ram.marker_flag == 0) {
    switch (g_ram.stageno) {
      case ANGEL_ISLAND_ACT_1:
        if (g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC) {
          g_ram.actwk[5].r_ptr = &ev0000;
          g_ram.DAT_08fff711 = 0;
        }
        break;
      case HYDROCITY_ACT_1:
        switch (g_ram.play_type) {
          default:
            g_ram.actwk[0].mstno = 27;
            break;
          case PLAY_TYPE_KNUCKLES:
            g_ram.actwk[0].mstno = 33;
            g_ram.actwk[0].mstrestart = 33;
            g_ram.actwk[0].patcnt = 1;
            g_ram.actwk[0].pattim = 0;
            break;
        }

        g_ram.actwk[0].u.play.cddat.jump = 1;
        if (g_ram.play_type == PLAY_TYPE_MILES) {
          g_ram.actwk[0].u.play.jump_flag = 1;
        }
        if (g_ram.actwk[1].r_ptr != 0) {
          g_ram.actwk[1].mstno = 27;
          g_ram.actwk[1].u.play.cddat.jump = 1;
          g_ram.actwk[1].u.play.jump_flag = 1;
        }
        break;
      case LAVA_REEF_BOSS:
      case MARBLE_GARDEN_ACT_1:
        g_ram.actwk[0].mstno = 27;
        g_ram.actwk[0].u.play.cddat.jump = 1;
        if (g_ram.actwk[1].r_ptr != 0) {
          g_ram.actwk[1].mstno = 27;
          g_ram.actwk[1].u.play.cddat.jump = 1;
        }
        break;
      case CARNIVAL_NIGHT_ACT_1:
        switch (g_ram.play_type) {
          case PLAY_TYPE_SONIC:
            g_ram.actwk[1].r_ptr = &fox00;
            fp16_set_integer(&g_ram.actwk[1].xposi, fp16_get_integer(g_ram.actwk[0].xposi));
            fp16_set_integer(&g_ram.actwk[1].yposi, fp16_get_integer(g_ram.actwk[0].yposi));
            g_ram.foxcpu_rno = 0;
            break;
          case PLAY_TYPE_MILES:
            g_ram.foxcpu_rno = 32;
            break;
          case PLAY_TYPE_KNUCKLES:
            g_ram.actwk[5].r_ptr = &Obj_LevelIntro_PlayerRun;
            break;
        }

        break;
      case ICECAP_ACT_1:
        switch (g_ram.play_type) {
          case PLAY_TYPE_MILES:
            g_ram.actwk[5].r_ptr = &Obj_LevelIntroICZ1Tails;
            break;
          case PLAY_TYPE_SONIC_AND_MILES:
          case PLAY_TYPE_SONIC:
          default:
            g_ram.actwk[5].r_ptr = &Obj_LevelIntroICZ1;
            break;
        }

        break;
      case LAUNCH_BASE_ACT_1:
        g_ram.actwk[5].r_ptr = &Obj_LevelIntro_PlayerLaunchFromGround;
        break;
      case MUSHROOM_HILL_ACT_1:
        if (g_ram.cartridge == 0) {
          switch (g_ram.play_type) {
            case PLAY_TYPE_SONIC:
              g_ram.actwk[1].r_ptr = &fox00;
              fp16_set_integer(&g_ram.actwk[1].xposi, fp16_get_integer(g_ram.actwk[0].xposi));
              fp16_set_integer(&g_ram.actwk[1].yposi, fp16_get_integer(g_ram.actwk[0].yposi));
              g_ram.foxcpu_rno = 0;
              break;
            case PLAY_TYPE_MILES:
              g_ram.foxcpu_rno = 32;
              break;
            case PLAY_TYPE_KNUCKLES:
              g_ram.actwk[0].mstno = 27;
              g_ram.actwk[0].u.play.cddat.jump = 1;
              break;
          }
        }
        break;
      case SANDOPOLIS_ACT_1:
        g_ram.actwk[5].r_ptr = &Obj_LevelIntro_PlayerFallIntoGround;
        g_ram.actwk[0].mstno = 2;
        g_ram.actwk[0].u.play.cddat.jump = 1;
        if (g_ram.actwk[1].r_ptr != 0) {
          g_ram.actwk[1].mstno = 2;
          g_ram.actwk[1].u.play.cddat.jump = 1;
        }
        break;
      case LAVA_REEF_ACT_1:
        if (g_ram.play_type != PLAY_TYPE_KNUCKLES) {
          g_ram.actwk[0].mstno = 27;
          g_ram.actwk[0].u.play.cddat.jump = 1;
          if (g_ram.actwk[1].r_ptr != 0) {
            g_ram.actwk[1].mstno = 27;
            g_ram.actwk[1].u.play.cddat.jump = 1;
          }
        }
        else {
          g_ram.actwk[5].r_ptr = &Obj_LevelIntro_PlayerRun;
        }
        break;
      case DEATH_EGG_ACT_1:
      case HIDDEN_PALACE:
        g_ram.actwk[5].r_ptr = &Obj_LevelIntro_PlayerRun;
        break;
    }
  }
}


static void baria_act_set(void) {
  if (g_ram.stageno == ENDING) return;
  if (get_zone(g_ram.stageno) != GUMBALL_MACHINE
      && get_zone(g_ram.stageno) != ROLLING_JUMP
      && get_zone(g_ram.stageno) != LAVA_REEF_BOSS_AND_HIDDEN_PALACE
      && get_zone(g_ram.stageno) >= AZURE_LAKE
      && get_zone(g_ram.stageno) < LAVA_REEF_BOSS_AND_HIDDEN_PALACE) return;

  SKC_play_powerdat plpowerdat = g_ram.plpowerdat_s;
  bool has_power = plpowerdat.fbaria == 1 || plpowerdat.tbaria || plpowerdat.abaria;
  if (!has_power) {
    plpowerdat = g_ram.plpowerdat_s2;
    has_power = plpowerdat.fbaria == 1 || plpowerdat.tbaria || plpowerdat.abaria;
  }
  if (has_power) {
    if (plpowerdat.fbaria == 1) {
      g_ram.actwk[0].u.play.powerdat.baria = 1;
      g_ram.actwk[0].u.play.powerdat.fbaria = 1;
      g_ram.actwk[0].u.play.powerdat.tbaria = 0;
      g_ram.actwk[0].u.play.powerdat.abaria = 0;
      g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &fbaria;
      g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = &g_ram.actwk[0] - g_ram.actwk;
    }
    else if (plpowerdat.tbaria == 1) {
      g_ram.actwk[0].u.play.powerdat.baria = 1;
      g_ram.actwk[0].u.play.powerdat.fbaria = 0;
      g_ram.actwk[0].u.play.powerdat.tbaria = 1;
      g_ram.actwk[0].u.play.powerdat.abaria = 0;
      g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &tbaria;
      g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = &g_ram.actwk[0] - g_ram.actwk;
    }
    else if (plpowerdat.abaria == 1) {
      g_ram.actwk[0].u.play.powerdat.baria = 1;
      g_ram.actwk[0].u.play.powerdat.fbaria = 0;
      g_ram.actwk[0].u.play.powerdat.tbaria = 0;
      g_ram.actwk[0].u.play.powerdat.abaria = 1;
      g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &tbaria;
      g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = &g_ram.actwk[0] - g_ram.actwk;
    }
  }
}


static void play_act_set(void) {
  if (g_ram.stageno >= GUMBALL_MACHINE_ACT_1 && g_ram.stageno < LAVA_REEF_BOSS) {
    g_ram.pltime_f = 0;
  }
  if (g_ram.stageno == ROLLING_JUMP_ACT_1) {
    g_ram.actwk[5].r_ptr = &Obj_PachinkoEnergyTrap;
    fp16_set_integer(&g_ram.actwk[5].xposi, 120);
    fp16_set_integer(&g_ram.actwk[5].yposi, 0xF30);
    g_ram.plring = g_ram.plring_s;
    g_ram.plring_f2 = g_ram.plring_f2_s;
    g_ram.plring_f = 1;
  }
  if (get_zone(g_ram.stageno) != SLOT_MACHINE) {
    if (g_ram.vs_flag == 0) {
      switch (g_ram.play_type) {
        case PLAY_TYPE_SONIC_AND_MILES:
        default: {
          g_ram.actwk[0].r_ptr = &play00;
          g_ram.actwk[ACTWK_PL_EFFECT].r_ptr = &effect;
          g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &wspin;
          g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = &g_ram.actwk[0] - g_ram.actwk;
          g_ram.actwk[1].r_ptr = &fox00;
          short xposi = fp16_get_integer(g_ram.actwk[0].xposi) - 32;
          fp16_set_integer(&g_ram.actwk[1].xposi, xposi);
          short yposi = fp16_get_integer(g_ram.actwk[0].yposi) + 4;
          fp16_set_integer(&g_ram.actwk[1].yposi, yposi);
          g_ram.actwk[ACTWK_PL2_EFFECT].r_ptr = &effect;
          g_ram.foxcpu_rno = 0;
          break;
        }
        case PLAY_TYPE_SONIC:
          g_ram.actwk[0].r_ptr = &play00;
          g_ram.actwk[ACTWK_PL_EFFECT].r_ptr = &effect;
          g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &wspin;
          g_ram.actwk[ACTWK_PL_BARIA].u.obj.ko = &g_ram.actwk[0] - g_ram.actwk;
          break;
        case PLAY_TYPE_MILES:
          g_ram.actwk[0].r_ptr = &fox00;
          g_ram.actwk[ACTWK_PL_EFFECT].r_ptr = &effect;
          fp16_set_integer(&g_ram.actwk[0].yposi, fp16_get_integer(g_ram.actwk[0].yposi) + 4);
          g_ram.foxcpu_rno = 0;
          break;
        case PLAY_TYPE_KNUCKLES:
          g_ram.actwk[0].r_ptr = &knuckles;
          g_ram.actwk[ACTWK_PL_BARIA].r_ptr = &effect;
          break;
      }
    }
    else {
      unsigned short vs_color[16] = {
        0xA86, 0xEEE, 0x84E, 0x40C,
        0x206, 0x080, 0x00E, 0x008,
        0x0AE, 0x08E, 0x8AE, 0x46A,
        0xECC, 0xCAA, 0x866, 0x222
      };

      g_ram.actwk[0].r_ptr = get_vsplay_handler(g_ram.whoplay1);
      g_ram.actwk[0].u.play.character = g_ram.whoplay1;
      fp16_set_integer(&g_ram.actwk[1].xposi, fp16_get_integer(g_ram.actwk[0].xposi));
      fp16_set_integer(&g_ram.actwk[1].yposi, fp16_get_integer(g_ram.actwk[0].yposi));
      g_ram.actwk[ACTWK_PL_EFFECT].r_ptr = &vseffect;
      if (g_ram.DAT_08ffef49 != 0) {
        g_ram.actwk[1].r_ptr = get_vsplay_handler(g_ram.whoplay2);
        g_ram.actwk[1].u.play.character = g_ram.whoplay2;
        g_ram.actwk[ACTWK_PL2_EFFECT].r_ptr = &vseffect;
      }
      memcpy(&g_ram.colorwk2[16], vs_color, sizeof(vs_color));
    }
  }
  else {
    DAT_08ffe408 = 0;
    DAT_08ffe406 = 0;
    g_ram.actwk[0].r_ptr = &Obj_Sonic_RotatingSlotBonus;
    FUN_006a9030();
    g_ram.scroll_start = 0xFF;
  }
}


static SKC_sprite_status_handler get_vsplay_handler(SKC_character_id id) {
  SKC_sprite_status_handler p_handler;

  switch (id) {
    case SONIC:
    case KNUCKLES:
    default:
      p_handler = &vsplay;
      break;
    case MILES:
      p_handler = &vsfox;
      break;
  }

  return p_handler;
}


static void colibufferclr(SKC_sprite_status* p_actwk) {
  g_ram.colibuffer[0] = 0;
}


static void watercnt(void) {
  if (g_ram.watermode!= 0) {
    if (g_ram.scroll_start == 0 || g_ram.actwk[0].r_no < 6) {
      watercoli();
      watercntsub();
    }
    g_ram.waterflag = 0;
    g_ram.waterposi = g_ram.waterposi_m;
    if (g_ram.stageno != HYDROCITY_ACT_1 || g_ram.scra_h_posit >> 16 >= 0x900) {
      short distance = g_ram.waterposi - (g_ram.scra_v_posit >> 16);
      if (distance <= 0) {
        g_ram.waterflag = 1;
        g_ram.vdp_hint_cache = 255;
      }
      else {
        if (distance >= 223) {
          distance = 255;
        }
        g_ram.vdp_hint_cache = distance & 0xFF;
        FUN_0041c7d2();
      }
    }
    else {
      g_ram.vdp_hint_cache = 255;
    }
  }
  else {
    FUN_0041c7d2();
  }
}


static short waterpositbl[16][2] = {
  { 0x504, 0x528 },
  { 0x500, 0x700 },
  { 0x600, 0x600 },
  { 0x600, 0xA90 },
  { 0x600, 0x600 },
  { 0xAD8, 0xAD8 },
  { 0xA80, 0x65E },
  { 0x600, 0x600 },
  { 0x600, 0x600 },
  { 0x600, 0x600 },
  { 0x600, 0x600 },
  { 0x600, 0x600 },
  { 0x600, 0x600 },
  { 0x600, 0x710 },
  { 0x600, 0x600 },
  { 0x410, 0x510 }
};


static void watercntsub(void) {
  void(*watertbl[16][2])(void) = {
    { &water0000chk, &water0001chk },
    { &water0100chk, &water0101chk },
    { &worknai,      &worknai      },
    { &worknai,      &worknai      },
    { &worknai,      &worknai      },
    { &worknai,      &worknai      },
    { &water0600chk, &water0601chk },
    { &worknai2,     &worknai2     },
    { &worknai2,     &worknai2     },
    { &worknai2,     &worknai2     },
    { &worknai2,     &worknai2     },
    { &worknai2,     &worknai2     },
    { &worknai2,     &worknai2     },
    { &worknai2,     &water0d01chk },
    { &worknai2,     &worknai2     },
    { &worknai2,     &worknai2     }
  };

  watertbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)]();
  short distance = g_ram.watermoveposi - g_ram.waterposi_m;
  if (distance != 0) {
    if (distance < 0) {
      distance = -distance;
    }
    g_ram.waterposi_m += distance;
  }
}


static void water0000chk(void) {
}


static void water0001chk(void) {
  if (g_ram.play_type == PLAY_TYPE_KNUCKLES
      && (g_ram.scralim_n_down == 0x820 || g_ram.scra_h_posit >> 16 >= 0x3B60)) return;

  if (g_ram.scra_h_posit >> 16 < 0x2440) {
    if (g_ram.watermoveposi == 0x618) {
      g_ram.watermoveposi = 0x528;
      g_ram.waterspeed = 2;
    }
  }
  else {
    if (g_ram.stage_triggers[0] == 0 && g_ram.scra_h_posit >> 16 >= 0x2850) {
      g_ram.stage_triggers[0] = 1;
    }
    if (g_ram.stage_triggers[0] == 1 && g_ram.watermoveposi != 0x618) {
      if (g_ram.scra_h_posit >> 16 < 0x2900) {
        g_ram.scr_shake_flg = 0xFFFF;
        SKC_actwkchk_result result = actwkchk();
        if (result.actwk_ptr != 0) {
          result.actwk_ptr->r_ptr = &water0001chk2;
          result.actwk_ptr->pattim = 180;
        }
      }
      unsigned short offset = g_ram.zonemapwk.row_offsets[14] + 78;
      g_ram.zonemapwk.data[offset] = 0;

      offset = g_ram.zonemapwk.row_offsets[16] + 78;
      g_ram.zonemapwk.data[offset] = 0;

      offset = g_ram.zonemapwk.row_offsets[18] + 78;
      g_ram.zonemapwk.data[offset] = 0;

      offset = g_ram.zonemapwk.row_offsets[20] + 78;
      g_ram.zonemapwk.data[offset] = 0;

      g_ram.watermoveposi = 0x618;
    }
  }
}


static void water0001chk2(SKC_sprite_status* p_actwk) {
  --p_actwk->pattim;
  if (p_actwk->pattim == 0) {
    g_ram.scr_shake_flg = 0;
    frameout(p_actwk);
  }
}


static void water0100chk(void) {
  unsigned short tbl[4][2] = {
    { 0x0900, 0x8500 },
    { 0x2A00, 0x8680 },
    { 0x3500, 0x8680 },
    { 0xFFFF, 0x86A0 }
  };

  waterchk(tbl);
}


static void water0101chk(void) {
  unsigned short tbl[2][2] = {
    { 0x3E00, 0x0700 },
    { 0xFFFF, 0x07E0 }
  };
  unsigned short tblk[2][2] = {
    { 0x4100, 0x0700 },
    { 0xFFFF, 0x8360 }
  };

  if (g_ram.DAT_08fffaa2 != 0) return;

  unsigned short (*p_tbl)[2] = g_ram.play_type != PLAY_TYPE_KNUCKLES ? tbl : tblk;
  waterchk(p_tbl);
}


static void worknai(void) {
}


static void water0600chk(void) {
  unsigned short tbl[5][2] = {
    { 0x0E00, 0x8B00 },
    { 0x1980, 0x8A00 },
    { 0x2340, 0x8A00 },
    { 0x2C00, 0x8AC8 },
    { 0xFFFF, 0x8FF0 }
  };

  waterchk(tbl);
}


static void water0601chk(void) {
  unsigned short tbl[2][2] = {
    { 0x0D80, 0x8FF0 },
    { 0xFFFF, 0x8B20 }
  };

  if (g_ram.play_type != PLAY_TYPE_KNUCKLES) return;

  if (g_ram.DAT_08fff7c2 == 0) {
    waterchk(tbl);
  }
  else if (g_ram.scra_v_posit >> 16 >= g_ram.waterposi_m) {
    g_ram.waterposi_m = 0x660;
  }
}


static void worknai2(void) {
}


static void water0d01chk(void) {
  if (g_ram.scra_h_posit >> 16 >= 0x1DE0) {
    g_ram.watermoveposi = 0x510;
  }
}


static void waterchk(unsigned short (*p_watertbl)[2]) {
  while ((unsigned short)g_ram.scra_h_posit >> 16 > (*p_watertbl)[0]) {
    ++p_watertbl;
  }

  if ((*p_watertbl)[1] > 0x8000) {
    g_ram.waterposi_m = (*p_watertbl)[1] & 0x7FFF;
    g_ram.watermoveposi = (*p_watertbl)[1] & 0x7FFF;
  }
  else {
    g_ram.watermoveposi = (*p_watertbl)[1];
  }
}


static void watercoli(void) {
  if (g_ram.editmode != 0) return;
  if (get_zone(g_ram.stageno) != HYDROCITY) return;

  if (g_ram.play_type != PLAY_TYPE_MILES) {
    watercolisub(&g_ram.actwk[0], &g_ram.watercoliflag, g_ram.swdata.down, false);
    watercolisub(&g_ram.actwk[1], &g_ram.watercoliflag, g_ram.swdata0.down, true);
  }
  else {
    watercolisub(&g_ram.actwk[0], &g_ram.watercoliflag2, g_ram.swdata.down, false);
  }
}


static void watercolisub(SKC_sprite_status* p_actwk, unsigned char* p_flag, SKC_pad pad, bool pl2) {
  static SKC_watercoli_data watercoli0100_tbl = {
    15,
    {
      {0x0380, 0x0580, 0x05A0, 0x05C0,  0x03F0, -0x0020, 0 },
      {0x05A0, 0x0560, 0x0A80, 0x05C0,  0x03F0, -0x0010, 0 },
      {0x1400, 0x0A80, 0x15A0, 0x0AC0,  0x0400,       0, 0 },
      {0x15A0, 0x0A40, 0x1960, 0x0AC0,  0x0400, -0x0040, 0 },
      {0x1990, 0x0780, 0x19E0, 0x07F0,       0, -0x0400, 1 },
      {0x1990, 0x07F0, 0x19F0, 0x0878, -0x0140, -0x0400, 1 },
      {0x1990, 0x0878, 0x19F0, 0x08FD,  0x0140, -0x0400, 1 },
      {0x1990, 0x08FD, 0x19F0, 0x0978, -0x0140, -0x0400, 1 },
      {0x1990, 0x0978, 0x19F0, 0x0A10,  0x0100, -0x0400, 1 },
      {0x1960, 0x0A10, 0x19D0, 0x0A80,  0x0300, -0x0280, 1 },
      {0x2B00, 0x0800, 0x2C20, 0x0840,  0x0400,       0, 0 },
      {0x2C20, 0x07C0, 0x2EE0, 0x0840,  0x0400, -0x0040, 0 },
      {0x2EE0, 0x0790, 0x2F50, 0x0800,  0x0300, -0x0300, 1 },
      {0x2F00, 0x0700, 0x2F70, 0x0790,  0x0100, -0x0400, 1 },
      {0x2F30, 0x0680, 0x2F70, 0x0700,       0, -0x0400, 1 }
    }
  };
  static SKC_watercoli_data watercoli0101_tbl = {
    2,
    {
      { 0x3980, 0x0800, 0x3AA0, 0x0840, 0x0400,       0, 0 },
      { 0x3AA0, 0x07C0, 0x3F00, 0x0840, 0x0400, -0x0040, 0 }
    }
  };

  SKC_watercoli_data* p_watercolitbl = get_act(g_ram.stageno) == ACT_1 ? &watercoli0100_tbl : &watercoli0101_tbl;

  for (int i = 0; i < p_watercolitbl->cnt; ++i) {
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) < p_watercolitbl->items[i].xstart) continue;
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= p_watercolitbl->items[i].xend) continue;
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) < p_watercolitbl->items[i].ystart) continue;
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) >= p_watercolitbl->items[i].yend) continue;
    if (p_actwk->r_no >= 4) {
      *p_flag = 0;
    }
    else if (!pl2) {
      if (p_actwk->u.play.control_bitfield != 0) {
        *p_flag = 0;
      }
      else {
        *p_flag = 1;
        p_actwk->xspeed = p_watercolitbl->items[i].xspeed;
        p_actwk->xposi += p_actwk->xspeed * 0x100;
        p_actwk->yspeed = p_watercolitbl->items[i].yspeed;
        p_actwk->yposi += p_actwk->yspeed * 0x100;
        p_actwk->mstno = 15;
        p_actwk->u.play.cddat.jump = 1;
        p_actwk->u.play.talent_status = 0;
        if (p_watercolitbl->items[i].movement == 0) {
          if (pad.u == 1) {
            fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 1);
          }
          if (pad.d == 1) {
            fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 1);
          }
        }
        else {
          if (pad.l == 1) {
            fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 1);
          }
          if (pad.r == 1) {
            fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 1);
          }
        }
      }
    }
    return;
  }

  if (*p_flag != 0) {
    p_actwk->mstno = 26;
    *p_flag = 0;
  }
}


static void FUN_0041c7d2(void) {
  switch (g_ram.stageno) {
    case HYDROCITY_ACT_2:
      FUN_0041c829(&g_ram.actwk[0], g_ram.swdata.down);
      FUN_0041c829(&g_ram.actwk[1], g_ram.swdata0.down);
      break;
    case ICECAP_ACT_1:
      FUN_0041c9b7(&g_ram.actwk[0], g_ram.swdata.down);
      FUN_0041c9b7(&g_ram.actwk[1], g_ram.swdata0.down);
      break;
    case SANDOPOLIS_ACT_1:
    case SANDOPOLIS_ACT_2:
      FUN_0041cdca(&g_ram.actwk[0], g_ram.swdata.down);
      FUN_0041cdca(&g_ram.actwk[1], g_ram.swdata0.down);
      break;
  }
}


static void FUN_0041c829(SKC_sprite_status* p_actwk, SKC_pad pad) {
  unsigned char screen_tbl[10] = {
    0x1C, 0x72, 0x83, 0x84, 0x8B, 0x91, 0x9F, 0xA0, 0xA5, 0xA6
  };

  bool found = false;
  if (p_actwk->u.play.cddat.jump == 0 && p_actwk->u.play.top_solid_bit != 12) {
    unsigned short yposi = (unsigned short)(fp16_get_integer(p_actwk->yposi) / 32) & g_ram.scr_row;
    unsigned short xposi = (unsigned short)(fp16_get_integer(p_actwk->xposi) / 128);
    unsigned short offset = g_ram.zonemapwk.row_offsets[yposi / 2] + xposi;
    unsigned char screen_no = g_ram.zonemapwk.data[offset];

    for (int i = 10; i > 0; ++i) {
      if (screen_no == screen_tbl[i - 1]) {
        found = true;
        break;
      }
    }
  }
  if (!found) {
    if (p_actwk->u.play.powerdat.mizuflag == 1) {
      p_actwk->u.play.hlock_timer = 5;
      memset(&p_actwk->u.play.powerdat, 0, sizeof(p_actwk->u.play.powerdat));
      p_actwk->u.play.powerdat.mizuflag = 1;
    }
  }
  else {
    FUN_0041cb2f(p_actwk, pad, -8);
  }
}


static void FUN_0041c9b7(SKC_sprite_status* p_actwk, SKC_pad pad) {
  unsigned char screen_tbl[10] = {
    0x2E, 0xC6, 0x33, 0xC5, 0x24, 0x2A, 0x44, 0x1F, 0x27, 0x2B
  };

  bool found = false;
  int i;
  if (p_actwk->u.play.cddat.jump == 0 && p_actwk->u.play.cddat.ride == 0) {
    unsigned short yposi = (unsigned short)(fp16_get_integer(p_actwk->yposi) / 32) & g_ram.scr_row;
    unsigned short xposi = (unsigned short)(fp16_get_integer(p_actwk->xposi) / 128);
    unsigned short offset = g_ram.zonemapwk.data[yposi / 2] + xposi;
    unsigned char screen_no = g_ram.zonemapwk.data[offset];

    for (i = 10; i > 0; ++i) {
      if (screen_no == screen_tbl[i - 1]) {
        found = true;
        break;
      }
    }
  }
  if (!found) {
    if (p_actwk->u.play.powerdat.mizuflag == 1) {
      p_actwk->u.play.hlock_timer = 5;
      memset(&p_actwk->u.play.powerdat, 0, sizeof(p_actwk->u.play.powerdat));
      p_actwk->u.play.powerdat.mizuflag = 1;
    }
  }
  else {
    unsigned char DAT_0041d2f3[10] = {
      -8, -8, 8, 8, -12, -12, -12, 12, 12, 12
    };

    FUN_0041cb2f(p_actwk, pad, DAT_0041d2f3[i - 1]);
  }
}


static void FUN_0041cb2f(SKC_sprite_status* p_actwk, SKC_pad pad, signed char d0) {
  if (d0 != 0) {
    signed char mspeed = fp8_get_integer(p_actwk->mspeed);
    if (d0 < 0) {
      if (mspeed > d0) {
        p_actwk->mspeed -= 0x40;
      }
    }
    else {
      if (mspeed < d0) {
        p_actwk->mspeed += 0x40;
      }
    }
    p_actwk->u.play.cddat.left = mspeed < 0;
    p_actwk->mstno = get_zone(g_ram.stageno) != ICECAP ? 27 : 25;
    p_actwk->u.play.powerdat.mizuflag = 1;
  }
  else {
    short mspeed = p_actwk->mspeed;
    if (pad.l == 1) {
      p_actwk->mstno = 0;
      p_actwk->u.play.cddat.left = 1;
      mspeed -= 4;
      if (mspeed < 0) {
        mspeed -= 4;
      }
    }
    if (pad.r == 1) {
      p_actwk->mstno = 0;
      p_actwk->u.play.cddat.left = 0;
      mspeed += 4;
      if (mspeed >= 0) {
        mspeed += 4;
      }
    }
    if (mspeed != 0) {
      if (mspeed >= 0) {
        mspeed -= 4;
        if (mspeed <= 0) {
          mspeed = 0;
          p_actwk->mstno = 5;
        }
      }
      else {
        mspeed += 4;
        if (mspeed >= 0) {
          mspeed = 0;
          p_actwk->mstno = 5;
        }
      }
    }
    p_actwk->mspeed = mspeed;
    p_actwk->u.play.powerdat.mizuflag = 1;
  }
}


static void FUN_0041cdca(SKC_sprite_status* p_actwk, SKC_pad pad) {
  unsigned char screen_tbl[17] = {
    0x0F, 0x13, 0x14, 0x15, 0x16, 0x17, 0x35, 0x6C, 0x6D, 0x76, 0x77, 0x7E, 0x7F, 0x85, 0x8A, 0x8C, 0x90
  };

  bool found = false;
  int i;
  if (p_actwk->u.play.cddat.jump == 0 && p_actwk->u.play.cddat.ride == 0) {
    unsigned short yposi = (unsigned short)(fp16_get_integer(p_actwk->yposi + 20) / 32) & g_ram.scr_row;
    unsigned short xposi = (unsigned short)(fp16_get_integer(p_actwk->xposi) / 128);
    unsigned short offset = g_ram.zonemapwk.data[yposi / 2] + xposi;
    unsigned char screen_no = g_ram.zonemapwk.data[offset];

    for (i = 17; i > 0; ++i) {
      if (screen_no == screen_tbl[i - 1]) {
        found = true;
        break;
      }
    }
  }
  if (!found) {
    FUN_0041cf0a(p_actwk);
  }
  else {
    signed char unknown_tbl[17][2] = {
      { -8,  0 },
      { -8,  0 },
      { -6,  1 },
      { -6,  2 },
      { -8,  0 },
      { -8,  0 },
      { -8,  0 },
      {  6,  1 },
      {  0,  3 },
      {  6,  2 },
      {  8,  0 },
      {  8,  0 },
      {  8,  0 },
      {  8,  0 },
      {  8,  0 },
      {  0,  3 },
      { -8,  0 }
    };

    switch (unknown_tbl[i][1]) {
      case 0:
        FUN_0041d00a(p_actwk, unknown_tbl[i][0]);
        break;
      case 1: {
        unsigned short xposi = (unsigned short)fp16_get_integer(p_actwk->xposi) & 0x7F;
        if (xposi < 64) {
          FUN_0041d00a(p_actwk, unknown_tbl[i][0]);
        }
        else {
          FUN_0041cf0a(p_actwk);
        }
        break;
      }
      case 2: {
        unsigned short xposi = (unsigned short)fp16_get_integer(p_actwk->xposi) & 0x7F;
        if (xposi >= 64) {
          FUN_0041d00a(p_actwk, unknown_tbl[i][0]);
        }
        else {
          FUN_0041cf0a(p_actwk);
        }
        break;
      }
      default:
        if (p_actwk->u.play.top_solid_bit == 12) {
          FUN_0041d00a(p_actwk, -8);
        }
        else {
          FUN_0041d00a(p_actwk, 8);
        }
        break;
    }
  }
}


static void FUN_0041cf0a(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.play.powerdat.mizuflag == 0) return;

  p_actwk->u.play.hlock_timer = 5;
  memset(&p_actwk->u.play.powerdat, 0, sizeof(p_actwk->u.play.powerdat));
  p_actwk->u.play.powerdat.mizuflag = 1;
  if (p_actwk->u.play.cddat.jump == 0) {
    p_actwk->sprvsize = p_actwk->u.play.height;
    p_actwk->sprhsize = p_actwk->u.play.width;
    p_actwk->u.play.cddat.ball = 0;
    p_actwk->u.play.cddat.ballj = 0;
    p_actwk->mstno = 0;
  }
}


static void FUN_0041d00a(SKC_sprite_status* p_actwk, signed char d0) {
  signed char mspeed = fp8_get_integer(p_actwk->mspeed);
  if (d0 < 0) {
    if (mspeed > d0) {
      p_actwk->mspeed -= 0x40;
      if (p_actwk->u.play.powerdat.mizuflag == 0 && p_actwk->mspeed >= 0) {
        p_actwk->mspeed /= 2;
        if (d0 == -8) {
          p_actwk->mspeed = 0;
        }
      }
    }
  }
  else {
    if (mspeed < d0) {
      p_actwk->mspeed += 0x40;
      if (p_actwk->u.play.powerdat.mizuflag == 0 && p_actwk->mspeed < 0) {
        p_actwk->mspeed /= 2;
        if (d0 == 8) {
          p_actwk->mspeed = 0;
        }
      }
    }
  }
  if (mspeed != 0) {
    p_actwk->u.play.cddat.left = mspeed < 0;
  }
  p_actwk->mstno = 25;
  short yoffset = (short)p_actwk->sprvsize - 14;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->sprvsize = 14;
  p_actwk->sprhsize = 7;
  p_actwk->u.play.cddat.ball = 0;
  p_actwk->u.play.cddat.ballj = 0;
  p_actwk->u.play.powerdat.mizuflag = 1;
  if (!(g_ram.systemtimer & 0xF)) {
    soundset(-56);
  }
}


void demoset(void) {
  unsigned char* tbl[7] = {
    demo0000_swdata,
    demo0100_swdata,
    demo0200_swdata,
    demo0700_swdata,
    demo0400_swdata,
    demo0800_swdata,
    demospec_swdata
  };

  g_ram.swbufcnt = tbl[g_ram.demoid][0];
  g_ram.demo_adr = &tbl[g_ram.demoid][1];
  g_ram.DAT_08ffef79 = 0;
  memset(&g_ram.swdata1, 0, sizeof(g_ram.swdata1));
  g_ram.swdata1.down.s = 1;
  memset(&g_ram.swdata2, 0, sizeof(g_ram.swdata2));
  g_ram.swdata2.down.s = 1;
  g_ram.DAT_08ffef50 = 0xFF;
}


void demoplay(void) {
  if (g_ram.demoflag == 0) return;

  if (g_ram.swdata1.pressed.s == 1) {
    g_ram.gmmode = OPENINGMD;
  }
  unsigned char down, pressed;
  if (get_zone(g_ram.stageno) != FLYING_BATTERY && get_zone(g_ram.stageno) < MUSHROOM_HILL) {
    pressed = g_ram.DAT_08ffef50 & 0x80 | g_ram.demo_adr[-1];
    down = g_ram.swdata1.down.s == 1 ? 0x80 : 0;
    g_ram.DAT_08ffef50 = down != 0 ? 0xFF : 0;
    down |= *g_ram.demo_adr++;
  }
  else {
    pressed = g_ram.DAT_08ffef50 & 0x80 | g_ram.DAT_08ffef79;
    g_ram.DAT_08ffef79 = *g_ram.demo_adr;
    if (g_ram.swbufcnt-- == 0) {
      g_ram.demo_adr += 2;
      g_ram.swbufcnt = g_ram.demo_adr[-1];
    }
    down = g_ram.swdata1.down.s == 1 ? 0x80 : 0;
    g_ram.DAT_08ffef50 = down != 0 ? 0xFF : 0;
    down |= g_ram.DAT_08ffef79;
  }
  g_ram.swdata1.down = get_pad(down);
  pressed ^= down;
  pressed &= down;
  g_ram.swdata1.pressed = get_pad(pressed);
  g_ram.swdata2.pressed.u = 0;
  g_ram.swdata2.pressed.d = 0;
  g_ram.swdata2.pressed.l = 0;
  g_ram.swdata2.pressed.r = 0;
  g_ram.swdata2.pressed.b = 0;
  g_ram.swdata2.pressed.c = 0;
  g_ram.swdata2.pressed.a = 0;
  g_ram.swdata2.down.u = 0;
  g_ram.swdata2.down.d = 0;
  g_ram.swdata2.down.l = 0;
  g_ram.swdata2.down.r = 0;
  g_ram.swdata2.down.b = 0;
  g_ram.swdata2.down.c = 0;
  g_ram.swdata2.down.a = 0;
}


static void scdset(void) {
  g_ram.scd0adr = zonescdtbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
  g_ram.scd1adr = &g_ram.scd0adr[1];
  g_ram.scdadr = g_ram.scd0adr;
}


static void sysdirinit(void) {
  g_ram.sysdirchgbits = 0xBE00;
  g_ram.sysdirec0 = 0x80;
  g_ram.sysdirspd0 = 0;
  g_ram.sysdirec1 = 0x80;
  g_ram.sysdirspd1 = 0;
  g_ram.sysdirec2 = 0x80;
  g_ram.sysdirspd2 = 0;
  g_ram.sysdirec3 = 0x80;
  g_ram.sysdirspd3 = 0;
  g_ram.sysdirec4 = 0x80;
  g_ram.sysdirspd4 = 0;
  g_ram.sysdirec5 = 0x80;
  g_ram.sysdirspd5 = 0;
  g_ram.sysdirec6 = 0x80;
  g_ram.sysdirspd6 = 0;
  g_ram.sysdirec7 = 0x80;
  g_ram.sysdirspd7 = 0;
  g_ram.sysdirec8 = 0x80;
  g_ram.sysdirspd8 = 0;
  g_ram.sysdirec9 = 0x3848;
  g_ram.sysdirspd9 = 0xEE;
  g_ram.sysdirec10 = 0x2080;
  g_ram.sysdirspd10 = 0xB4;
  g_ram.sysdirec11 = 0x3080;
  g_ram.sysdirspd11 = 0x10E;
  g_ram.sysdirec12 = 0x5080;
  g_ram.sysdirspd12 = 0x1C2;
  g_ram.sysdirec13 = 0x7080;
  g_ram.sysdirspd13 = 0x276;
  g_ram.sysdirec14 = 0x80;
  g_ram.sysdirspd14 = 0;
  g_ram.sysdirec15 = 0x4000;
  g_ram.sysdirspd15 = 0xFE;
}


static void sysdirchg(void) {
  short sysdirchg_tbl[16][2] = {
    { 2, 0x10 },
    { 2, 0x18 },
    { 2, 0x20 },
    { 2, 0x30 },
    { 4, 0x20 },
    { 8, 0x08 },
    { 8, 0x40 },
    { 4, 0x40 },
    { 2, 0x38 },
    { 2, 0x38 },
    { 2, 0x20 },
    { 3, 0x30 },
    { 5, 0x50 },
    { 7, 0x70 },
    { 2, 0x40 },
    { 2, 0x40 }
  };

  if (g_ram.vs_flag == 0 && g_ram.actwk[0].r_no >= 6) return;

  unsigned short sysdirchgbits = g_ram.sysdirchgbits;
  short* sysdirec_tbl[16] = {
    &g_ram.sysdirec0,
    &g_ram.sysdirec1,
    &g_ram.sysdirec2,
    &g_ram.sysdirec3,
    &g_ram.sysdirec4,
    &g_ram.sysdirec5,
    &g_ram.sysdirec6,
    &g_ram.sysdirec7,
    &g_ram.sysdirec8,
    &g_ram.sysdirec9,
    &g_ram.sysdirec10,
    &g_ram.sysdirec11,
    &g_ram.sysdirec12,
    &g_ram.sysdirec13,
    &g_ram.sysdirec14,
    &g_ram.sysdirec15
  };
  short* sysdirspd_tbl[16] = {
    &g_ram.sysdirspd0,
    &g_ram.sysdirspd1,
    &g_ram.sysdirspd2,
    &g_ram.sysdirspd3,
    &g_ram.sysdirspd4,
    &g_ram.sysdirspd5,
    &g_ram.sysdirspd6,
    &g_ram.sysdirspd7,
    &g_ram.sysdirspd8,
    &g_ram.sysdirspd9,
    &g_ram.sysdirspd10,
    &g_ram.sysdirspd11,
    &g_ram.sysdirspd12,
    &g_ram.sysdirspd13,
    &g_ram.sysdirspd14,
    &g_ram.sysdirspd15
  };

  for (int i = 0; i < 16; ++i) {
    if (!BIT_IS_SET(sysdirchgbits, i)) {
      *sysdirspd_tbl[i] += sysdirchg_tbl[i][0];
      *sysdirec_tbl[i] += *sysdirspd_tbl[i];
      if (sysdirchg_tbl[i][1] <= fp8_get_integer(*sysdirec_tbl[i])) {
        SET_BIT(sysdirchgbits, i);
      }
    }
    else {
      *sysdirspd_tbl[i] -= sysdirchg_tbl[i][0];
      *sysdirec_tbl[i] += *sysdirspd_tbl[i];
      if (sysdirchg_tbl[i][1] > fp8_get_integer(*sysdirec_tbl[i])) {
        CLEAR_BIT(sysdirchgbits, i);
      }
    }
  }

  g_ram.sysdirchgbits = sysdirchgbits;
}


static void syspatchg(void) {
  if (g_ram.sys_pattim2-- == 0) {
    g_ram.sys_pattim2 = 7;
    ++g_ram.sys_patno2;
    g_ram.sys_patno2 &= 3;
  }
  if (g_ram.sys_pattim4 != 0) {
    g_ram.sys_ringtimer += g_ram.sys_pattim4;
    g_ram.sys_patno4 = g_ram.sys_ringtimer >> 9 & 3;
    --g_ram.sys_pattim4;
  }
  g_ram.sys_ropetimer += 0x180;
}


static void mapinit(void) {
  unsigned short stageno = g_ram.stageno;
  bool play_type_is_sonic = g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC;
  if (stageno == ANGEL_ISLAND_ACT_1 && (!play_type_is_sonic || g_ram.markerno != 0)) {
    stageno = ANGEL_ISLAND_ACT_1_NO_INTRO;
  }
  SKC_mapinit_data* p_data = &mapinittbl[get_zone(stageno)][get_act(stageno)];
  unlze_moduled(g_vram, p_data->cg_data1_ptr);
  if (p_data->cg_data1_ptr != p_data->cg_data2_ptr) {
    unsigned short size = p_data->cg_data1_ptr[0] | p_data->cg_data1_ptr[1] << 8;
    unlze_moduled(&g_vram[size], p_data->cg_data2_ptr);
  }
}


static void waterset(void) {
  if (g_ram.stageno == ANGEL_ISLAND_ACT_1
      || (g_ram.stageno == ANGEL_ISLAND_ACT_2
          && (g_ram.stageno_i != ANGEL_ISLAND_ACT_2 || g_ram.play_type != PLAY_TYPE_KNUCKLES))
      || get_zone(g_ram.stageno) == HYDROCITY
      || (g_ram.stageno == CARNIVAL_NIGHT_ACT_2 && g_ram.play_type != PLAY_TYPE_KNUCKLES)
      || g_ram.stageno == ICECAP_ACT_2
      || g_ram.stageno == LAUNCH_BASE_ACT_2) {
    g_ram.watermode = 1;
    g_ram.vs_flag = 0;
    g_ram.waterposi = waterpositbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
    g_ram.waterposi_m = waterpositbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
    g_ram.watermoveposi = waterpositbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
    g_ram.water_flag = 0;
    g_ram.waterflag = 0;
    g_ram.waterspeed = 1;
  }
  else {
    g_ram.waterposi = 0x1000;
    g_ram.waterposi_m = 0x1000;
    g_ram.watermoveposi = 0x1000;
    g_ram.watermode = 0;
  }
}


static void watercolorset(void) {
  if (g_ram.watermode == 0) return;

  unsigned char color_no;

  switch (g_ram.stageno) {
    case ANGEL_ISLAND_ACT_1:   color_no = 43; break;
    case ANGEL_ISLAND_ACT_2:   color_no = 44; break;
    case HYDROCITY_ACT_1:      color_no = 49; break;
    case HYDROCITY_ACT_2:      color_no = 50; break;
    case CARNIVAL_NIGHT_ACT_2: color_no = 58; break;
    case ICECAP_ACT_2:         color_no = 57; break;
    case LAUNCH_BASE_ACT_1:    color_no = 45; break;
    case LAUNCH_BASE_ACT_2:
    default:                   color_no = 46; break;
  }

  colorset3(color_no);
  colorset4(color_no);
  if (g_ram.markerno != 0) {
    g_ram.waterflag = g_ram.waterflag_s;
  }
  if (g_ram.play_type == PLAY_TYPE_KNUCKLES) {
    unsigned short knuckles_color[7][3] = {
      { 0xA6A, 0xA2A, 0x624 },
      { 0xE2A, 0xC0A, 0xA06 },
      { 0xC48, 0xA06, 0x604 },
      { 0x64C, 0x628, 0x624 },
      { 0xC48, 0xA06, 0x604 },
      { 0xA4C, 0xA28, 0x428 },
      { 0x64C, 0x628, 0x624 }
    };

    unsigned short zone = get_zone(g_ram.stageno);
    memcpy(&g_ram.colorwk3[2], knuckles_color[zone], sizeof(knuckles_color[zone]));
    memcpy(&g_ram.colorwk4[2], knuckles_color[zone], sizeof(knuckles_color[zone]));
  }
}
