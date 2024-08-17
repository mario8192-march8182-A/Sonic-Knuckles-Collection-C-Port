#include "globals.h"
#include "macros.h"
#include "types/animscript.h"
#include "types/levelselecttextpos.h"
#include "levelselect.h"
#include "bitdevr.h"
#include "color.h"
#include "data.h"
#include "mapdevr.h"
static short stagenolist[33];
static void handleinput();
static void handleinput2();
static unsigned char levelselect_columnchangelookup[36];
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

extern void vInt();
extern void copy_map_vram(unsigned short* p_source, unsigned short vram_offset, unsigned long row_cnt, unsigned long cell_cnt);
extern void copy_data_vram(void* p_source, unsigned short vram_adr, unsigned short size);
extern void clear_displaydata();
extern void bgmset(signed char command);
extern void soundset(signed char command);


// 00415104
void levelselect() {
  DAT_0082ddc8 = 1;
  if (g_sonic3Alone != 0) {
    s3levelselect();
    return;
  }

  g_mdRam.stageno = ANGEL_ISLAND_ACT_1;
  fadeout();
  clear_displaydata();
  g_vdpScrollPlaneAOffset = 0xC000;
  g_vdpScrollPlaneBOffset = 0xE000;
  DAT_008549d8 = 0;
  DAT_00854dec = 0;
  memset(g_mdRam.pbuffer, 0, sizeof(g_mdRam.pbuffer));
  memset(g_mdRam.actwk, 0, sizeof(g_mdRam.actwk) + 52);
  g_mdRam.vdpbuffer[0] = 0;
  g_mdRam.vdpbuffer_free = 0;
  bitdevr((unsigned long*)&g_mdVram[512], levelselect_tiles, g_mdRam.bitdevwk);
  mapdevr((unsigned short*)&g_mdRam.chunkmappings128, levelselect_map, 0x6000);
  copy_map_vram((unsigned short*)g_mdRam.chunkmappings128, 0xE000, 27, 39);
  memset(g_mdRam.chunkmappings128, 0, 0x8C0);

  unsigned short* p_mapoffsets = levelselect_mapoffsets;
  unsigned char* p_text = entriestext;
  unsigned char entry_cnt = 16;
  unsigned short* p_chunkmappings;

  do {
    p_chunkmappings = (unsigned short*)&g_mdRam.chunkmappings128[*p_mapoffsets++];
    unsigned char char_cnt = *p_text++;
    unsigned char chars_left = char_cnt;

    do {
      *p_chunkmappings++ = *p_text++;
    } while (chars_left-- != 0);

    signed char blanks = 13 - char_cnt;
    if (blanks >= 0) {
      do {
        *p_chunkmappings++ = 0;
      } while (blanks-- != 0);
    }
    *p_chunkmappings = 17; // act 1
    p_chunkmappings += 40;
    *p_chunkmappings++ = 18; // act 2
  } while (entry_cnt-- != 0);

  *p_chunkmappings = 0;
  p_chunkmappings -= 40;
  *p_chunkmappings = 26; // *
  ((unsigned short*)g_mdRam.chunkmappings128)[197] = 19; // act 3
  ((unsigned short*)g_mdRam.chunkmappings128)[237] = 20; // act 4
  copy_map_vram((unsigned short*)g_mdRam.chunkmappings128, 0xC000, 27, 39);
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
  g_mdRam.DAT_08ffffe4 = 0;
  g_mdRam.DAT_08ffffe6 = 0;
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
    if (IS_START_PRESSED(g_mdRam.swdata1) || IS_START_PRESSED(g_mdRam.swdata2)) {
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
            g_mdRam.gamemode = 52;
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
          g_mdRam.DAT_08ffffa1 = 0;
          g_mdRam.gamemode = 44;
          nextmode = true;
        }
      }
      else {
        g_mdRam.gamemode = 0;
        nextmode = true;
      }
      if (!nextmode) {
        if (g_mdRam.debugcheat == 0) {
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
        g_mdRam.gamemode = 12;
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


// 004156cf
static short stagenolist[33] = {
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
  if (!IS_UP_PRESSED(g_mdRam.swdata1) && !IS_DOWN_PRESSED(g_mdRam.swdata1)) {
    --g_mdRam.levelselect_inputrepeattimer;
    if (g_mdRam.levelselect_inputrepeattimer >= 0) {
      handleinput2();
    }
  }
  g_mdRam.levelselect_inputrepeattimer = 11;
  if (IS_UP_DOWN(g_mdRam.swdata1) || IS_DOWN_DOWN(g_mdRam.swdata1)) {
    if (IS_UP_DOWN(g_mdRam.swdata1)) {
      if (g_mdRam.levelselect_selection-- == 0) {
        g_mdRam.levelselect_selection = 32;
      }
    }
    if (IS_DOWN_DOWN(g_mdRam.swdata1)) {
      ++g_mdRam.levelselect_selection;
      if (g_mdRam.levelselect_selection >= 33) {
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
  if (g_mdRam.levelselect_selection == 32) {
    if (IS_LEFT_PRESSED(g_mdRam.swdata1)) {
      if (g_mdRam.levelselect_sound-- == 0) {
        g_mdRam.levelselect_sound = 0;
      }
    }
    if (IS_RIGHT_PRESSED(g_mdRam.swdata1)) {
      ++g_mdRam.levelselect_sound;
      if (g_mdRam.levelselect_sound >= 256) {
        g_mdRam.levelselect_sound = 0;
      }
    }
    if (IS_A_PRESSED(g_mdRam.swdata1)) {
      g_mdRam.levelselect_sound += 16;
      g_mdRam.levelselect_sound &= 0xFF;
    }
    if (IS_C_PRESSED(g_mdRam.swdata1)) {
      bgmset(g_mdRam.levelselect_sound);
    }
    if (IS_B_PRESSED(g_mdRam.swdata1)) {
      bgmset(227);
    }
  }
  else {
    if (IS_LEFT_PRESSED(g_mdRam.swdata1) || IS_RIGHT_PRESSED(g_mdRam.swdata1)) {
      g_mdRam.levelselect_selection = levelselect_columnchangelookup[g_mdRam.levelselect_selection];
    }
    if (IS_C_PRESSED(g_mdRam.swdata1)) {
      ++g_mdRam.levelselect_plmode;
      if (g_mdRam.levelselect_plmode >= 4) {
        g_mdRam.levelselect_plmode = TEAM_SONIC_AND_MILES;
      }
    }
  }
}


/* 00415b1c */ static unsigned char levelselect_columnchangelookup[36] = {
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
  unsigned short index = pos.y1 * 80 + pos.x1;
  unsigned short* p_chunkmappings = (unsigned short*)&g_mdRam.chunkmappings128[index];
  index = (pos.y1 << 7) + pos.x1 + 0xC000;
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[index];
  unsigned char cnt = 14;

  do {
    *g_pLevelSelectVram++ = *p_chunkmappings++ + coloroffset;
  } while (cnt-- != 0);

  if (pos.y2 != 0) {
    index = pos.y2 * 80 + pos.x2;
    p_chunkmappings = (unsigned short*)&g_mdRam.chunkmappings128[index];
    index = pos.y2 << 7 + pos.x2 + 0xC000;
    g_pLevelSelectVram = (unsigned short*)&g_mdVram[index];
    *g_pLevelSelectVram++ = *p_chunkmappings++ + coloroffset;
  }
  if (g_mdRam.levelselect_selection == 32) {
    set_sounddigits(coloroffset);
  }
  else {
    set_plmodedigits(coloroffset);
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
  sonicmiles_tiles,
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
    if (--p_animcounters[0] < 0) {
      unsigned char frame = p_animcounters[1];
      if (frame >= p_script->cnt) {
        p_animcounters[1] = frame = 0;
      }
      ++p_animcounters[1];
      p_animcounters[0] = p_script->tim;
      if (p_animcounters[0] < 0) {
        frame *= 2;
        p_animcounters[0] = p_script->data[frame + 1];
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
  // TODO
}
