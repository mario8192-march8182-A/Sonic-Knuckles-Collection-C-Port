#include "globals.h"
#include "macros.h"
#include "types/animscript.h"
#include "types/levelselecttextpos.h"
#include "levelselect.h"
#include "bitdevr.h"
#include "color.h"
#include "data.h"
#include "game.h"
#include "cg/levelselectcg.h"
#include "map/levelselectmap.h"
#include "mapdevr.h"
#include "vdp.h"
static short stagenolist[33];
static void handleinput();
static void handleinput2();
static unsigned char columnchangelookup[36];
static void set_selectioncolor(unsigned short coloroffset);
static void set_plmodedigits(unsigned short coloroffset);
static void set_sounddigits(unsigned short coloroffset);
static void set_digits(unsigned short digits, unsigned short coloroffset);
static void set_digit(unsigned short digit, unsigned short coloroffset);
static levelselect_textpos textpositions[33];
static unsigned short levelselect_mapoffsets[17];
static unsigned char entriestext[202];
static short sonicmiles_wrt_cnt;
static animscript sonicmiles_wrt;
static void s3levelselect();
static short s3stagenolist[29];
static unsigned char s3columnchangelookup[30];
static void setwhoplaydigits(unsigned short coloroffset);
static void setzoneicon();
static unsigned char zoneiconoffsets[29];
static levelselect_textpos s3textpositions[29];
static unsigned short s3mapoffsets[16];
static void chk_cheats();
static unsigned char editmodecode[5];
static unsigned char allemeraldscode[5];
static unsigned char s3entriestext[168];
static unsigned short zoneicons_color[19][16];
static unsigned char soundtestpos;

extern void vInt();


// 00415104
void levelselect() {
  soundtestpos = 32;
  DAT_0082ddc8 = 1;
  if (g_sonic3Alone != 0) {
    soundtestpos = 28;
    s3levelselect();
    return;
  }

  g_mdRam.stageno = ANGEL_ISLAND_ACT_1;
  fadeout();
  scrinit();
  g_vdpScrollPlaneAOffset = 0xC000;
  g_vdpScrollPlaneBOffset = 0xE000;
  DAT_008549d8 = 0;
  DAT_00854dec = 0;
  memset(g_mdRam.pbuffer, 0, sizeof(g_mdRam.pbuffer));
  memset(g_mdRam.actwk, 0, sizeof(g_mdRam.actwk) + 52);
  bitdevr((unsigned long*)&g_mdVram[512], levelselect_main_cg, g_mdRam.bitdevwk);
  mapdevr((unsigned short*)&g_mdRam.decompressed, levelselect_main_map, 0x6000);
  copy_map_vram((unsigned short*)g_mdRam.decompressed, 0xE000, 27, 39);
  memset(g_mdRam.decompressed, 0, 0x8C0);

  unsigned short* p_mapoffsets = levelselect_mapoffsets;
  unsigned char* p_text = entriestext;
  unsigned short* p_decompressed;

  for (int i = 0; i < 17; ++i) {
    p_decompressed = (unsigned short*)&g_mdRam.decompressed[*p_mapoffsets++];
    unsigned char char_cnt = *p_text++;

    for (int j = 0; j < char_cnt + 1; ++j) {
      *p_decompressed++ = *p_text++;
    }

    signed char blanks = 14 - char_cnt;
    if (blanks > 0) {
      for (int j = 0; j < blanks; ++j) {
        *p_decompressed++ = 0;
      }
    }
    *p_decompressed = 17; // act 1
    p_decompressed += 40;
    *p_decompressed = 18; // act 2
  }

  *p_decompressed = 0;
  p_decompressed -= 40;
  *p_decompressed = 26; // *
  ((unsigned short*)g_mdRam.decompressed)[197] = 19; // act 3
  ((unsigned short*)g_mdRam.decompressed)[237] = 20; // act 4
  copy_map_vram((unsigned short*)g_mdRam.decompressed, 0xC000, 27, 39);
  set_sounddigits(0);
  g_mdRam.plmode = TEAM_SONIC_AND_MILES;
  g_mdRam.DAT_08ffff02 = 0;
  g_mdRam.DAT_08fff711 = 0;
  g_mdRam.actanimcounters[0][0] = 0;
  anim_tiles(sonicmiles_wrt_cnt, (unsigned char*)&sonicmiles_wrt);

  colorset(4);
  memcpy(&g_mdRam.colorwk2[32], &g_mdRam.colorwk[32], 32);

  bgmset(47);
  g_mdRam.demotimer = 1799;
  g_mdRam.vs_flag = 0;
  g_mdRam.scra_h_posit = 0;
  g_mdRam.scra_v_posit = 0;
  g_mdRam.p_saveslot = 0;
  g_mdRam.brings = 0;
  g_mdRam.markerno = 0;
  g_mdRam.marker_flag = 0;
  g_mdRam.specmode = 0;
  g_mdRam.editmodecheatcounter = 0;
  g_mdRam.allemeraldscheatcounter = 0;
  g_mdRam.int_flg = 22;
  vInt();
  fadein();
  bool nextmode = false;

  do {
    g_mdRam.int_flg = 22;
    vInt();
    set_selectioncolor(0);
    handleinput();
    set_selectioncolor(0x6000);
    anim_tiles(sonicmiles_wrt_cnt, (unsigned char*)&sonicmiles_wrt);
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1 | g_mdRam.swdata2, PAD_S)) {
      if (g_mdRam.cartridge != 0) {
        if (g_mdRam.levelselect_plmode < TEAM_KNUCKLES) {
          g_mdRam.levelselect_plmode = TEAM_SONIC;
        }
      }
      g_mdRam.plmode = g_mdRam.levelselect_plmode;
      short chosenstageno = stagenolist[g_mdRam.levelselect_selection];
      if (chosenstageno >= 0) {
        if (chosenstageno == 0x5555) continue;
        g_mdRam.pl_suu = 3;
        g_mdRam.cartridgespec = 0;
        if (chosenstageno != 0x4000) { // Sonic 3 special stage
          if (chosenstageno == 0x4001) { // Sonic & Knuckles special stage
            g_mdRam.cartridgespec = 1;
            g_mdRam.gmmode = 52;
            if (g_mdRam.cartridge != 0 && g_mdRam.stageno != FLYING_BATTERY_ACT_1 && g_mdRam.stageno < MUSHROOM_HILL_ACT_1) {
              chosenstageno = MUSHROOM_HILL_ACT_1;
              g_mdRam.stageno = chosenstageno;
              g_mdRam.stageno_i = chosenstageno;
              g_mdRam.stageno_s = chosenstageno;
              g_mdRam.stageno_is = chosenstageno;
            }
            nextmode = true;
          }
        }
        else {
          g_mdRam.specmodemenu = 0;
          g_mdRam.gmmode = 44;
          nextmode = true;
        }
      }
      else {
        g_mdRam.gmmode = 0;
        nextmode = true;
      }
      if (!nextmode) {
        if (g_mdRam.editmodecheat == 0) {
          if (g_mdRam.plmode == TEAM_KNUCKLES) {
            if (chosenstageno == SKY_SANCTUARY_ACT_SONIC
                || chosenstageno == DOOMSDAY_ACT
                || chosenstageno == LAVA_REEF_BOSS
                || chosenstageno == DEATH_EGG_BOSS) {
denyentry:
              soundset(-78);
              continue;
            }
          }
          if (g_mdRam.plmode < TEAM_KNUCKLES) {
            if (chosenstageno == SKY_SANCTUARY_ACT_KNUCKLES) {
              goto denyentry;
            }
          }
          if (g_mdRam.plmode == TEAM_MILES) {
            if (chosenstageno == DOOMSDAY_ACT) {
              goto denyentry;
            }
          }
        }
        if (g_mdRam.cartridge != 0) {
          short chosenstagenoact1 = chosenstageno;
          SET_ACT(chosenstagenoact1, ACT_1);
          if (chosenstagenoact1 != FLYING_BATTERY_ACT_1 && chosenstagenoact1 < MUSHROOM_HILL_ACT_1) {
            chosenstageno = MUSHROOM_HILL_ACT_1;
          }
        }
        chosenstageno &= 0x3FFF;
        g_mdRam.stageno = chosenstageno;
        g_mdRam.stageno_i = chosenstageno;
        g_mdRam.stageno_s = chosenstageno;
        g_mdRam.stageno_is = chosenstageno;
        g_mdRam.scralim_down_s = 0x1000;
        g_mdRam.scralim_down_s2 = 0x1000;
        g_mdRam.gmmode = 12;
        g_mdRam.pl_suu = 3;
        g_mdRam.pl2_suu = 3;
        g_mdRam.plring = 0;
        g_mdRam.pltime.hours = 0;
        g_mdRam.pltime.minutes = 0;
        g_mdRam.pltime.seconds = 0;
        g_mdRam.pltime.frames = 0;
        g_mdRam.plscore = 0;
        g_mdRam.pl2ring = 0;
        g_mdRam.DAT_08fffed2 = 0;
        g_mdRam.DAT_08fffed6 = 0;
        g_mdRam.plcontinuecnt = 0;
        g_mdRam.demoflag = 0;
        g_mdRam.extrascore = 5000;
        g_mdRam.extrascore2 = 5000;
        soundset(-31);
        g_mdRam.vs_noitems = 0;
        g_mdRam.vs_flag = 0;
        if (GET_ZONE(g_mdRam.stageno) >= AZURE_LAKE && GET_ZONE(g_mdRam.stageno) < ZONE_GUMBALL_MACHINE) {
          g_mdRam.vs_flag = 1;
        }
        nextmode = true;
      }
    }
  } while (!nextmode);
}


/* 004156cf */ static short stagenolist[33] = {
  ANGEL_ISLAND_ACT_1,      ANGEL_ISLAND_ACT_2,
  HYDROCITY_ACT_1,         HYDROCITY_ACT_2,
  MARBLE_GARDEN_ACT_1,     MARBLE_GARDEN_ACT_2,
  CARNIVAL_NIGHT_ACT_1,    CARNIVAL_NIGHT_ACT_2,
  ICECAP_ACT_1,            ICECAP_ACT_2,
  LAUNCH_BASE_ACT_1,       LAUNCH_BASE_ACT_2,
  MUSHROOM_HILL_ACT_1,     MUSHROOM_HILL_ACT_2,
  FLYING_BATTERY_ACT_1,    FLYING_BATTERY_ACT_2,
  SANDOPOLIS_ACT_1,        SANDOPOLIS_ACT_2,
  LAVA_REEF_ACT_1,         LAVA_REEF_ACT_2,
  LAVA_REEF_BOSS,          HIDDEN_PALACE,
  SKY_SANCTUARY_ACT_SONIC, SKY_SANCTUARY_ACT_KNUCKLES,
  DEATH_EGG_ACT_1,         DEATH_EGG_ACT_2,
  DOOMSDAY_ACT,            DEATH_EGG_BOSS,
  SLOT_MACHINE_ACT,        ROLLING_JUMP_ACT,
  0x4000, 0x4001,
  -1
};


// 0041591b
static void handleinput() {
  if (!IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_U | PAD_D)) {
    --g_mdRam.levelselect_inputrepeattimer;
    if (g_mdRam.levelselect_inputrepeattimer >= 0) {
      handleinput2();
      return;
    }
  }
  g_mdRam.levelselect_inputrepeattimer = 11;
  if (IS_BUTTON_DOWN(g_mdRam.swdata1, PAD_U | PAD_D)) {
    if (IS_BUTTON_DOWN(g_mdRam.swdata1, PAD_U)) {
      if (g_mdRam.levelselect_selection-- == 0) {
        g_mdRam.levelselect_selection = soundtestpos;
      }
    }
    if (IS_BUTTON_DOWN(g_mdRam.swdata1, PAD_D)) {
      ++g_mdRam.levelselect_selection;
      if (g_mdRam.levelselect_selection >= soundtestpos + 1) {
        g_mdRam.levelselect_selection = 0;
      }
    }
  }
  else {
    handleinput2();
  }
}


// 004159e3
static void handleinput2() {
  if (g_mdRam.levelselect_selection == soundtestpos) {
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_L)) {
      if (g_mdRam.levelselect_sound-- == 0) {
        g_mdRam.levelselect_sound = 0;
      }
    }
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_R)) {
      ++g_mdRam.levelselect_sound;
      if (g_mdRam.levelselect_sound >= 256) {
        g_mdRam.levelselect_sound = 0;
      }
    }
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_A)) {
      g_mdRam.levelselect_sound += 16;
      g_mdRam.levelselect_sound &= 0xFF;
    }
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_C)) {
      bgmset(g_mdRam.levelselect_sound);
      if (g_sonic3Alone != 0) {
        chk_cheats();
      }
    }
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_B)) {
      bgmset(227);
    }
  }
  else {
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_L | PAD_R)) {
      unsigned char* p_lookup = columnchangelookup;
      if (g_sonic3Alone != 0) {
        p_lookup = s3columnchangelookup;
      }
      g_mdRam.levelselect_selection = p_lookup[g_mdRam.levelselect_selection];
    }
    if (g_sonic3Alone == 0) {
      if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_C)) {
        ++g_mdRam.levelselect_plmode;
        if (g_mdRam.levelselect_plmode >= 4) {
          g_mdRam.levelselect_plmode = TEAM_SONIC_AND_MILES;
        }
      }
    }
    else {
      if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_C)) {
        ++g_mdRam.whoplay1;
        if (g_mdRam.whoplay1 >= 3) {
          g_mdRam.whoplay1 = 0;
        }
      }
      if (IS_BUTTON_PRESSED(g_mdRam.swdata2, PAD_C)) {
        ++g_mdRam.whoplay2;
        if (g_mdRam.whoplay2 >= 3) {
          g_mdRam.whoplay2 = 0;
        }
      }
    }
  }
}


/* 00415b1c */ static unsigned char columnchangelookup[36] = {
  /*  0 */ 18,
  /*  1 */ 19,
  /*  2 */ 20,
  /*  3 */ 21,
  /*  4 */ 22,
  /*  5 */ 23,
  /*  6 */ 24,
  /*  7 */ 25,
  /*  8 */ 26,
  /*  9 */ 27,
  /* 10 */ 28,
  /* 11 */ 29,
  /* 12 */ 30,
  /* 13 */ 31,
  /* 14 */ 32,
  /* 15 */ 32,
  /* 16 */ 32,
  /* 17 */ 32,
  /* 18 */  0,
  /* 19 */  1,
  /* 20 */  2,
  /* 21 */  3,
  /* 22 */  4,
  /* 23 */  5,
  /* 24 */  6,
  /* 25 */  7,
  /* 26 */  8,
  /* 27 */  9,
  /* 28 */ 10,
  /* 29 */ 11,
  /* 30 */ 12,
  /* 31 */ 13,
  /* 32 */ 14,
  /* 33 */ 15,
  /* 34 */ 16,
  /* 35 */ 17
};


// 00415b77
static void set_selectioncolor(unsigned short coloroffset) {
  levelselect_textpos pos = textpositions[g_mdRam.levelselect_selection];
  if (g_sonic3Alone != 0) {
    pos = s3textpositions[g_mdRam.levelselect_selection];
  }
  unsigned short index = pos.y1 * 80 + pos.x1;
  unsigned short* p_decompressed = (unsigned short*)&g_mdRam.decompressed[index];
  index = (pos.y1 << 7) + pos.x1 + 0xC000;
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[index];

  for (int i = 0; i < 15; ++i) {
    *g_pLevelSelectVram++ = *p_decompressed++ + coloroffset;
  }

  if (pos.y2 != 0) {
    index = pos.y2 * 80 + pos.x2;
    p_decompressed = (unsigned short*)&g_mdRam.decompressed[index];
    index = (pos.y2 << 7) + pos.x2 + 0xC000;
    g_pLevelSelectVram = (unsigned short*)&g_mdVram[index];
    *g_pLevelSelectVram++ = *p_decompressed++ + coloroffset;
  }
  unsigned char soundtest = 32;
  if (g_sonic3Alone != 0) {
    soundtest = 28;
  }
  if (g_mdRam.levelselect_selection == soundtest) {
    set_sounddigits(coloroffset);
  }
  else {
    if (g_sonic3Alone == 0) {
      set_plmodedigits(coloroffset);
    }
    else {
      setwhoplaydigits(coloroffset);
    }
  }
}


// 00415e32
static void set_plmodedigits(unsigned short coloroffset) {
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[0xC19C];
  set_digits(g_mdRam.levelselect_plmode, coloroffset);
}


// 00415e4f
static void set_sounddigits(unsigned short coloroffset) {
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[0xCB46];
  if (g_sonic3Alone != 0) {
    g_pLevelSelectVram = (unsigned short*)&g_mdVram[0xC846];
  }
  set_digits(g_mdRam.levelselect_sound, coloroffset);
}


// 00415e6a
static void set_digits(unsigned short digits, unsigned short coloroffset) {
  set_digit(digits >> 4, coloroffset);
  set_digit(digits, coloroffset);
}


// 00415e90
static void set_digit(unsigned short digit, unsigned short coloroffset) {
  digit &= 0xF;
  if (digit >= 10) {
    digit += 4;
  }
  digit += 16;
  *g_pLevelSelectVram++ = digit + coloroffset;
}


/* 00415ef0 */ static levelselect_textpos textpositions[33] = {
  { 0x06, 0x01, 0x24, 0x01 },
  { 0x06, 0x01, 0x24, 0x02 },
  { 0x06, 0x04, 0x24, 0x04 },
  { 0x06, 0x04, 0x24, 0x05 },
  { 0x06, 0x07, 0x24, 0x07 },
  { 0x06, 0x07, 0x24, 0x08 },
  { 0x06, 0x0A, 0x24, 0x0A },
  { 0x06, 0x0A, 0x24, 0x0B },
  { 0x06, 0x0D, 0x24, 0x0D },
  { 0x06, 0x0D, 0x24, 0x0E },
  { 0x06, 0x10, 0x24, 0x10 },
  { 0x06, 0x10, 0x24, 0x11 },
  { 0x06, 0x13, 0x24, 0x13 },
  { 0x06, 0x13, 0x24, 0x14 },
  { 0x06, 0x16, 0x24, 0x16 },
  { 0x06, 0x16, 0x24, 0x17 },
  { 0x06, 0x19, 0x24, 0x19 },
  { 0x06, 0x19, 0x24, 0x1A },
  { 0x2C, 0x01, 0x4A, 0x01 },
  { 0x2C, 0x01, 0x4A, 0x02 },
  { 0x2C, 0x04, 0x4A, 0x04 },
  { 0x2C, 0x04, 0x4A, 0x05 },
  { 0x2C, 0x07, 0x4A, 0x07 },
  { 0x2C, 0x07, 0x4A, 0x08 },
  { 0x2C, 0x0A, 0x4A, 0x0A },
  { 0x2C, 0x0A, 0x4A, 0x0B },
  { 0x2C, 0x0D, 0x4A, 0x0D },
  { 0x2C, 0x0D, 0x4A, 0x0E },
  { 0x2C, 0x10, 0x4A, 0x10 },
  { 0x2C, 0x10, 0x4A, 0x11 },
  { 0x2C, 0x13, 0x4A, 0x13 },
  { 0x2C, 0x13, 0x4A, 0x14 },
  { 0x2C, 0x16, 0x4A, 0x16 }
};
/* 00415f74 */ static unsigned short levelselect_mapoffsets[17] = { 0x056, 0x146, 0x236, 0x326, 0x416, 0x506, 0x5F6, 0x6E6, 0x7D6, 0x07C, 0x16C, 0x25C, 0x34C, 0x43C, 0x52C, 0x61C, 0x70C };
/* 00415f96 */ static unsigned char entriestext[202] = { 0x0B, 0x1E, 0x2B, 0x24, 0x22, 0x29, 0x00, 0x26, 0x30, 0x29, 0x1E, 0x2B, 0x21, 0x08, 0x25, 0x36, 0x21, 0x2F, 0x2C, 0x20, 0x26, 0x31, 0x36, 0x0C, 0x2A, 0x1E, 0x2F, 0x1F, 0x29, 0x22, 0x00, 0x24, 0x1E, 0x2F, 0x21, 0x22, 0x2B, 0x0D, 0x20, 0x1E, 0x2F, 0x2B, 0x26, 0x33, 0x1E, 0x29, 0x00, 0x2B, 0x26, 0x24, 0x25, 0x31, 0x05, 0x26, 0x20, 0x22, 0x20, 0x1E, 0x2D, 0x0A, 0x29, 0x1E, 0x32, 0x2B, 0x20, 0x25, 0x00, 0x1F, 0x1E, 0x30, 0x22, 0x0C, 0x2A, 0x32, 0x30, 0x25, 0x2F, 0x2C, 0x2C, 0x2A, 0x00, 0x25, 0x26, 0x29, 0x29, 0x0D, 0x23, 0x29, 0x36, 0x26, 0x2B, 0x24, 0x00, 0x1F, 0x1E, 0x31, 0x31, 0x22, 0x2F, 0x36, 0x09, 0x30, 0x1E, 0x2B, 0x21, 0x2C, 0x2D, 0x2C, 0x29, 0x26, 0x30, 0x08, 0x29, 0x1E, 0x33, 0x1E, 0x00, 0x2F, 0x22, 0x22, 0x23, 0x08, 0x29, 0x1E, 0x33, 0x1E, 0x00, 0x2F, 0x22, 0x22, 0x23, 0x0C, 0x30, 0x28, 0x36, 0x00, 0x30, 0x1E, 0x2B, 0x20, 0x31, 0x32, 0x1E, 0x2F, 0x36, 0x07, 0x21, 0x22, 0x1E, 0x31, 0x25, 0x22, 0x24, 0x24, 0x0B, 0x31, 0x25, 0x22, 0x00, 0x21, 0x2C, 0x2C, 0x2A, 0x30, 0x21, 0x1E, 0x36, 0x04, 0x1F, 0x2C, 0x2B, 0x32, 0x30, 0x0C, 0x30, 0x2D, 0x22, 0x20, 0x26, 0x1E, 0x29, 0x00, 0x30, 0x31, 0x1E, 0x24, 0x22, 0x0C, 0x30, 0x2C, 0x32, 0x2B, 0x21, 0x00, 0x31, 0x22, 0x30, 0x31, 0x00, 0x00, 0x1A, 0x90 };
/* 00416060 */ static short sonicmiles_wrt_cnt = 0;
/* 00416062 */ static animscript sonicmiles_wrt = {
  0,
  0,
  0,
  -1,
  levelselect_sonicmiles_cg,
  32,
  6,
  10,
  { 0x00, 0xC7, 0x0A, 0x05, 0x14, 0x05, 0x1E, 0xC7, 0x14, 0x05, 0x0A, 0x05, 0x87, 0xDB }
};


// 0041607c
void anim_tiles(short script_cnt, unsigned char* p_scriptlist) {
  unsigned char* p_animcounters = g_mdRam.actanimcounters[0];

  for ( ; script_cnt != -1; --script_cnt) {
    animscript* p_script = (animscript*)p_scriptlist;
    if (p_animcounters[0]-- == 0) {
      unsigned char frame = p_animcounters[1];
      if (frame >= p_script->cnt) {
        p_animcounters[1] = frame = 0;
      }
      ++p_animcounters[1];
      if (p_script->tim < 0) {
        frame *= 2;
        p_animcounters[0] = p_script->data[frame + 1];
      }
      else {
        p_animcounters[0] = p_script->tim;
      }
      unsigned char* p_rom = p_script->p_rom + (p_script->data[frame] << 5);
      copy_data_vram(p_rom, p_script->vram_adr, p_script->size << 4);
    }
    unsigned char datasize = p_script->cnt;
    if (p_script->tim < 0) {
      datasize *= 2;
    }
    ++datasize;
    datasize &= 0xFE;
    p_scriptlist += 12 + datasize;
    p_animcounters += 2;
  }
}


// 004272d4
static void s3levelselect() {
  fadeout();
  scrinit();
  g_vdpScrollPlaneAOffset = 0xC000;
  g_vdpScrollPlaneBOffset = 0xE000;
  DAT_008549d8 = 0;
  DAT_00854dec = 0;
  memset(g_mdRam.pbuffer, 0, sizeof(g_mdRam.pbuffer));
  memset(g_mdRam.actwk, 0, sizeof(g_mdRam.actwk) + 52);
  bitdevr((unsigned long*)&g_mdVram[512], levelselect_main_cg, g_mdRam.bitdevwk);
  bitdevr((unsigned long*)&g_mdVram[0xE00], levelselect_menubox_cg, g_mdRam.bitdevwk);
  bitdevr((unsigned long*)&g_mdVram[0x1200], levelselect_zoneicons_cg, g_mdRam.bitdevwk);
  mapdevr((unsigned short*)&g_mdRam.decompressed, levelselect_main_map, 0x6000);
  copy_map_vram((unsigned short*)g_mdRam.decompressed, 0xE000, 27, 39);
  mapdevr((unsigned short*)g_mdRam.decompressed, DAT_004297e0, 0);
  memset(g_mdRam.decompressed, 0, 0x640);
  memset(&g_mdRam.decompressed[0x696], 0, 32);
  unsigned short* p_mapoffsets = s3mapoffsets;
  unsigned char* p_text = s3entriestext;
  unsigned short* p_decompressed;

  for (int i = 0; i < 15; ++i) {
    p_decompressed = (unsigned short*)&g_mdRam.decompressed[*p_mapoffsets++];
    unsigned char char_cnt = *p_text++;

    for (int j = 0; j < char_cnt + 1; ++j) {
      *p_decompressed++ = *p_text++;
    }

    signed char blanks = 14 - char_cnt;
    if (blanks > 0) {
      for (int j = 0; j < blanks; ++j) {
        *p_decompressed++ = 0;
      }
    }
    *p_decompressed = 17; // act 1
    p_decompressed += 40;
    *p_decompressed = 18; // act 2
  }

  *p_decompressed = 0;
  p_decompressed -= 40;
  *p_decompressed = 26; // *
  copy_map_vram((unsigned short*)g_mdRam.decompressed, 0xC000, 27, 39);
  set_sounddigits(0);
  mapdevr((unsigned short*)&g_mdRam.decompressed[0x8C0], DAT_00429934, 144);
  setzoneicon();
  g_mdRam.plmode = TEAM_SONIC_AND_MILES;
  g_mdRam.DAT_08ffff02 = 0;
  g_mdRam.DAT_08fff711 = 0;
  g_mdRam.actanimcounters[0][0] = 0;
  anim_tiles(sonicmiles_wrt_cnt, (unsigned char*)&sonicmiles_wrt);

  colorset(4);
  memcpy(&g_mdRam.colorwk2[32], &g_mdRam.colorwk[32], 32);

  bgmset(47);
  g_mdRam.demotimer = 1799;
  g_mdRam.vs_flag = 0;
  g_mdRam.scra_h_posit = 0;
  g_mdRam.scra_v_posit = 0;
  g_mdRam.p_saveslot = 0;
  g_mdRam.levelselectcheat = 1;
  g_mdRam.slowmotioncheat = 1;
  g_mdRam.editmodecheat = 257;
  g_mdRam.editmodecheatcounter = 0;
  g_mdRam.allemeraldscheatcounter = 0;
  g_mdRam.int_flg = 22;
  vInt();
  fadein();
  bool nextmode = false;

  do {
    g_mdRam.int_flg = 22;
    vInt();
    set_selectioncolor(0);
    handleinput();
    set_selectioncolor(0x6000);
    setzoneicon();
    anim_tiles(sonicmiles_wrt_cnt, (unsigned char*)&sonicmiles_wrt);
    if (IS_BUTTON_PRESSED(g_mdRam.swdata1 | g_mdRam.swdata2, PAD_S)) {
      short chosenstageno = s3stagenolist[g_mdRam.levelselect_selection];
      if (chosenstageno >= 0) {
        if (chosenstageno == 0x5555) continue;
        switch (chosenstageno) {
          case 0x4000: // Sonic 3 special stage
            g_mdRam.gmmode = 44;
            nextmode = true;
            break;
          case 0x4001: // Sonic & Knuckles special stage
            g_mdRam.gmmode = 52;
            nextmode = true;
            break;
        }
      }
      else {
        g_mdRam.gmmode = 0;
        nextmode = true;
      }
      if (!nextmode) {
        chosenstageno &= 0x3FFF;
        g_mdRam.stageno = chosenstageno;
        g_mdRam.stageno_i = chosenstageno;
        g_mdRam.stageno_s = chosenstageno;
        g_mdRam.gmmode = 12;
        g_mdRam.pl_suu = 3;
        g_mdRam.pl2_suu = 3;
        g_mdRam.plring = 0;
        g_mdRam.pltime.hours = 0;
        g_mdRam.pltime.minutes = 0;
        g_mdRam.pltime.seconds = 0;
        g_mdRam.pltime.frames = 0;
        g_mdRam.plscore = 0;
        g_mdRam.pl2ring = 0;
        g_mdRam.DAT_08fffed2 = 0;
        g_mdRam.DAT_08fffed6 = 0;
        g_mdRam.plcontinuecnt = 0;
        g_mdRam.extrascore = 5000;
        g_mdRam.extrascore2 = 5000;
        soundset(225);
        g_mdRam.vs_noitems = 0;
        g_mdRam.vs_flag = 0;
        if (GET_ZONE(g_mdRam.stageno) >= AZURE_LAKE && GET_ZONE(g_mdRam.stageno) < GUMBALL_MACHINE_ACT) {
          g_mdRam.vs_flag = 1;
        }
        nextmode = true;
      }
    }
  } while (!nextmode);
}


/* 004288ed */ static short s3stagenolist[29] = {
  ANGEL_ISLAND_ACT_1,   ANGEL_ISLAND_ACT_2,
  HYDROCITY_ACT_1,      HYDROCITY_ACT_2,
  MARBLE_GARDEN_ACT_1,  MARBLE_GARDEN_ACT_2,
  CARNIVAL_NIGHT_ACT_1, CARNIVAL_NIGHT_ACT_2,
  0x5555,               0x5555, // Flying Battery
  ICECAP_ACT_1,         ICECAP_ACT_2,
  LAUNCH_BASE_ACT_1,    LAUNCH_BASE_ACT_2,
  0x5555,               0x5555, // Mushroom Valley
  0x5555,               0x5555, // Sandopolis
  AZURE_LAKE_ACT,
  BALLOON_PARK_ACT,
  DESERT_PALACE_ACT,
  CHROME_GADGET_ACT,
  ENDLESS_MINE_ACT,
  GUMBALL_MACHINE_ACT,
  0x5555, // Slot Machine
  0x5555, // Rolling Jump
  0x4000, 0x4001
  -1
};


/* 00428c56 */ static unsigned char s3columnchangelookup[30] = {
  /*  1 */ 18,
  /*  2 */ 19,
  /*  3 */ 20,
  /*  4 */ 21,
  /*  5 */ 22,
  /*  6 */ 23,
  /*  7 */ 24,
  /*  8 */ 25,
  /*  9 */ 26,
  /* 10 */ 27,
  /* 11 */ 28,
  /* 12 */ 28,
  /* 13 */ 28,
  /* 14 */ 28,
  /* 15 */ 28,
  /* 16 */ 28,
  /* 17 */ 28,
  /* 18 */ 28,
  /* 19 */  0,
  /* 20 */  1,
  /* 21 */  2,
  /* 22 */  3,
  /* 23 */  4,
  /* 24 */  5,
  /* 25 */  6,
  /* 26 */  7,
  /* 27 */  8,
  /* 28 */  9,
  /* 29 */ 10,
  /* 30 */ 11
};


// 00428f88
static void setwhoplaydigits(unsigned short coloroffset) {
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[0xC1B8];
  set_digits(g_mdRam.whoplay1, coloroffset);
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[0xC1C0];
  set_digits(g_mdRam.whoplay2, coloroffset);
}


// 00429059
static void setzoneicon() {
  unsigned char* p_decompressed = &g_mdRam.decompressed[0x8C0];
  unsigned short offset = zoneiconoffsets[g_mdRam.levelselect_selection];
  p_decompressed += offset * 24;
  copy_map_vram((unsigned short*)p_decompressed, 0xCB36, 2, 3);
  memcpy(&g_mdRam.colorwk[32], &zoneicons_color[offset][0], 32);
}


/* 004291b7 */ static unsigned char zoneiconoffsets[29] = {
   0,  0,
   7,  7,
   8,  8,
   6,  6,
   2,  2,
   5,  5,
   4,  4,
   1,  1,
   9,  9,
  10, 10,
   3,  3,
  11, 11,
  11, 11,
  12, 12,
  14
};


/* 004291d4 */ static levelselect_textpos s3textpositions[29] = {
  { 0x06, 0x01, 0x24, 0x01 },
  { 0x06, 0x01, 0x24, 0x02 },
  { 0x06, 0x04, 0x24, 0x04 },
  { 0x06, 0x04, 0x24, 0x05 },
  { 0x06, 0x07, 0x24, 0x07 },
  { 0x06, 0x07, 0x24, 0x08 },
  { 0x06, 0x0A, 0x24, 0x0A },
  { 0x06, 0x0A, 0x24, 0x0B },
  { 0x06, 0x0D, 0x24, 0x0D },
  { 0x06, 0x0D, 0x24, 0x0E },
  { 0x06, 0x10, 0x24, 0x10 },
  { 0x06, 0x10, 0x24, 0x11 },
  { 0x06, 0x13, 0x24, 0x13 },
  { 0x06, 0x13, 0x24, 0x14 },
  { 0x06, 0x16, 0x24, 0x16 },
  { 0x06, 0x16, 0x24, 0x17 },
  { 0x06, 0x19, 0x24, 0x19 },
  { 0x06, 0x19, 0x24, 0x1A },
  { 0x2C, 0x01, 0x4A, 0x01 },
  { 0x2C, 0x01, 0x4A, 0x02 },
  { 0x2C, 0x04, 0x4A, 0x04 },
  { 0x2C, 0x04, 0x4A, 0x05 },
  { 0x2C, 0x07, 0x4A, 0x07 },
  { 0x2C, 0x07, 0x4A, 0x08 },
  { 0x2C, 0x0A, 0x4A, 0x0A },
  { 0x2C, 0x0A, 0x4A, 0x0B },
  { 0x2C, 0x0D, 0x4A, 0x0D },
  { 0x2C, 0x0D, 0x4A, 0x0E },
  { 0x2C, 0x10, 0x4A, 0x10 }
};
/* 00429248 */ static unsigned short s3mapoffsets[16] = { 86, 326, 566, 806, 1046, 1286, 1526, 1766, 2006, 124, 364, 604, 844, 1084, 1324, 1564 };


// 00429268
static void chk_cheats() {
  if (editmodecode[g_mdRam.editmodecheatcounter] == g_mdRam.levelselect_sound) {
    ++g_mdRam.editmodecheatcounter;
    if (editmodecode[g_mdRam.editmodecheatcounter] == 0) {
      g_mdRam.editmodecheat = 257;
      soundset(51);
      g_mdRam.editmodecheatcounter = 0;
    }
  }
  else {
    g_mdRam.editmodecheatcounter = 0;
  }

  if (allemeraldscode[g_mdRam.allemeraldscheatcounter] == g_mdRam.levelselect_sound) {
    ++g_mdRam.allemeraldscheatcounter;
    if (allemeraldscode[g_mdRam.allemeraldscheatcounter] == 0) {
      g_mdRam.emeraldcnt = 7;
      bgmset(43);
      g_mdRam.allemeraldscheatcounter = 0;
    }
  }
  else {
    g_mdRam.allemeraldscheatcounter = 0;
  }
}


/* 00429397 */ static unsigned char editmodecode[5] = { 1, 3, 5, 7, 0 };
/* 0042939c */ static unsigned char allemeraldscode[5] = { 2, 4, 5, 6, 0 };


/* 004294d8 */ static unsigned char s3entriestext[168] = { 0x0b, 0x1e, 0x2b, 0x24, 0x22, 0x29, 0x00, 0x26, 0x30, 0x29, 0x1e, 0x2b, 0x21, 0x08, 0x25, 0x36, 0x21, 0x2f, 0x2c, 0x20, 0x26, 0x31, 0x36, 0x0c, 0x2a, 0x1e, 0x2f, 0x1f, 0x29, 0x22, 0x00, 0x24, 0x1e, 0x2f, 0x21, 0x22, 0x2b, 0x0d, 0x20, 0x1e, 0x2f, 0x2b, 0x26, 0x33, 0x1e, 0x29, 0x00, 0x2b, 0x26, 0x24, 0x25, 0x31, 0x0d, 0x23, 0x29, 0x36, 0x26, 0x2b, 0x24, 0x00, 0x1f, 0x1e, 0x31, 0x31, 0x22, 0x2f, 0x36, 0x05, 0x26, 0x20, 0x22, 0x20, 0x1e, 0x2d, 0x0a, 0x29, 0x1e, 0x32, 0x2b, 0x20, 0x25, 0x00, 0x1f, 0x1e, 0x30, 0x22, 0x0e, 0x2a, 0x32, 0x30, 0x25, 0x2f, 0x2c, 0x2c, 0x2a, 0x00, 0x33, 0x1e, 0x29, 0x29, 0x22, 0x36, 0x09, 0x30, 0x1e, 0x2b, 0x21, 0x2c, 0x2d, 0x2c, 0x29, 0x26, 0x30, 0x04, 0x12, 0x2d, 0x00, 0x33, 0x30, 0x04, 0x12, 0x2d, 0x00, 0x33, 0x30, 0x04, 0x12, 0x2d, 0x00, 0x33, 0x30, 0x04, 0x1f, 0x2c, 0x2b, 0x32, 0x30, 0x0c, 0x30, 0x2d, 0x22, 0x20, 0x26, 0x1e, 0x29, 0x00, 0x30, 0x31, 0x1e, 0x24, 0x22, 0x0c, 0x30, 0x2c, 0x32, 0x2b, 0x21, 0x00, 0x31, 0x22, 0x30, 0x31, 0x00, 0x00, 0x1a, 0x87, 0xdb, 0x90 };


/* 00429580 */ static unsigned short zoneicons_color[19][16] = {
  { 0x000, 0x000, 0x048, 0x06A, 0x08E, 0x0CE, 0xEEE, 0x0E0, 0x0A4, 0x082, 0x062, 0x000, 0xE86, 0x026, 0xE42, 0xC00 },
  { 0x000, 0x000, 0xCE2, 0x000, 0x480, 0x240, 0xEEE, 0x4AC, 0x06A, 0x026, 0x842, 0x620, 0x400, 0x000, 0x000, 0x000 },
  { 0x000, 0x000, 0xA26, 0xC48, 0xE8C, 0x0CE, 0x0C4, 0x080, 0xC00, 0x000, 0xEEE, 0xEEA, 0xEC8, 0x06E, 0x04A, 0x028 },
  { 0x000, 0x000, 0x048, 0x06A, 0x08E, 0x0CE, 0xEEE, 0x0E0, 0x0A4, 0x082, 0x062, 0x808, 0xA4A, 0x026, 0x626, 0x404 },
  { 0x000, 0x000, 0x048, 0x06A, 0x08E, 0x0CE, 0xEEE, 0x0E0, 0x0A4, 0x082, 0x062, 0x400, 0xE86, 0x06E, 0xE42, 0xC00 },
  { 0x000, 0x000, 0xCE2, 0x8C0, 0x480, 0x240, 0xEEE, 0x2AC, 0x06A, 0x026, 0xAA6, 0x000, 0x60A, 0x408, 0x204, 0x000 },
  { 0x000, 0x000, 0xC06, 0xC0A, 0xC6E, 0x068, 0x08A, 0x000, 0x2CE, 0x0EC, 0x0AE, 0x06E, 0xEEE, 0x000, 0x00E, 0x0C4 },
  { 0x000, 0x000, 0xEEE, 0xAAA, 0x000, 0x666, 0x444, 0xE40, 0xC00, 0x800, 0x0CE, 0x28E, 0x00E, 0x084, 0x062, 0x020 },
  { 0x000, 0x000, 0x6CE, 0x4AC, 0x28A, 0x068, 0x046, 0x0E8, 0x0C4, 0x080, 0x040, 0xEEE, 0xC00, 0xEC0, 0x860, 0x000 },
  { 0x000, 0x000, 0xEEE, 0xECA, 0xE86, 0xE64, 0xE42, 0x6AE, 0x48A, 0x268, 0x246, 0x024, 0x888, 0x444, 0x00E, 0x008 },
  { 0x000, 0x000, 0xEEE, 0xECA, 0xE86, 0xE64, 0xE42, 0x6AE, 0x48A, 0x268, 0x246, 0x024, 0x888, 0x444, 0x00E, 0x008 },
  { 0x000, 0x000, 0xE64, 0xE86, 0xEA8, 0xECA, 0xEEE, 0x000, 0x0AE, 0x06E, 0xE22, 0x0E0, 0x000, 0x000, 0x000, 0x000 },
  { 0x000, 0xE20, 0x04E, 0x06E, 0x048, 0x08C, 0x0CE, 0x8EE, 0x800, 0x400, 0x000, 0xEE8, 0xE80, 0xE60, 0x000, 0x000 },
  { 0x000, 0x000, 0xA22, 0xC42, 0x000, 0xE66, 0xEEE, 0xAAA, 0x888, 0x444, 0x8AE, 0x46A, 0x00E, 0x000, 0x0EE, 0x000 },
  { 0x000, 0x000, 0xA22, 0xC42, 0x000, 0xE66, 0xEEE, 0xAAA, 0x888, 0x444, 0x8AE, 0x46A, 0x00E, 0x000, 0x0EE, 0x000 },
  { 0x305, 0x001, 0x000, 0x006, 0xD20, 0x007, 0x857, 0x086, 0xA15, 0x821, 0x605, 0xE88, 0x301, 0x006, 0xA9E, 0x213 },
  { 0x01B, 0x154, 0xC84, 0x804, 0x086, 0xA15, 0x122, 0x00B, 0xA31, 0x821, 0xE05, 0x888, 0x842, 0xE0C, 0xE88, 0x301 },
  { 0x081, 0x308, 0xE40, 0x088, 0x066, 0x002, 0x670, 0x393, 0x7F8, 0x0DB, 0x005, 0x001, 0x000, 0x806, 0x8A0, 0x227 },
  { 0x107, 0xA5F, 0x889, 0x415, 0xBA8, 0xF81, 0x94A, 0x5B8, 0x8F4, 0xB9A, 0x2E7, 0x90C, 0x244, 0x89F, 0x173, 0x04F }
};
