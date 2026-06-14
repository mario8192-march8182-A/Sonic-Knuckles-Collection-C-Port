#include "score.h"
#include <stdbool.h>
#include <string.h>
#include "data/cg/score.h"
#include "types/patsetwork.h"
#include "types/sonic3ram.h"
#include "types/spritepattern.h"
#include "types/spritestatus.h"
#include "utils/bits.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "action.h"
#include "coli.h"
#include "sound.h"
static SKC_sprite_pattern* scorepat[6];
static SKC_sprite_pattern scoresp00;
static SKC_sprite_pattern scoresp01;
static SKC_sprite_pattern scoresp02;
static SKC_sprite_pattern scoresp03;
static SKC_sprite_pattern scoresp04;
static SKC_sprite_pattern scoresp05;
static void scoreset2(void);
static void scoreset3(void);
static void ringinit(void);
static void scoreinitsub(unsigned char char_cnt, signed char* p_data, unsigned char* p_vram);
static signed char scoreinittbl[16];
static signed char* ringinittbl;
static void posiwrt(void);
static void hexwrtw(long hex, unsigned char** pp_vram);
static void ringwrt(unsigned short plring, unsigned char* p_vram);
static void scorewrt(unsigned long plscore, unsigned char* p_vram);
static void scorewrt2(unsigned long number, unsigned char* p_vram, unsigned char digit_cnt, unsigned long base);
static void timewrt1(unsigned char number, unsigned char* p_vram);
static void timewrt(unsigned char number, unsigned char* p_vram);
static void timewrt0(unsigned char number, unsigned char* p_vram, unsigned char digit_cnt, unsigned char base);
static void playsuuwrt(void);

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void vsscore(SKC_patset_work* p_work) {
  if (g_ram.debugflag == 0) return;

  score(p_work);
}


void score(SKC_patset_work* p_work) {
  bool bonus_stage = get_zone(g_ram.stageno) >= GUMBALL_MACHINE && get_zone(g_ram.stageno) <= SLOT_MACHINE;
  unsigned char patno = bonus_stage ? 8 : 0;
  if (!(g_ram.gametimer & 8) && g_ram.plring == 0) {
    patno += 2;
  }
  if (!bonus_stage && !(g_ram.gametimer & 8) && g_ram.pltime.minutes == 9) {
    patno += 4;
  }
  if (BIT_IS_SET(g_ram.DAT_08fff711, 7)) {
    g_ram.DAT_08fff711 += 8;
    g_ram.DAT_08fff711 &= 0xFF;
  }
  if (scorepat[patno]->cnt > 0) {
    p_work->xposi = (short)g_ram.DAT_08fff711 + 143;
    p_work->yposi = 264;
    p_work->placements_ptr = scorepat[patno]->spr;
    p_work->placement_cnt = scorepat[patno]->cnt;
    SKC_actflg actflg = { 0 };
    spatset(p_work, actflg, 0x86CA);
  }
}


static SKC_sprite_pattern* scorepat[6] = {
  &scoresp00,
  &scoresp01,
  &scoresp02,
  &scoresp03,
  &scoresp04,
  &scoresp05
};


static SKC_sprite_pattern scoresp00 = {
  10,
  {
    { -128, 13, 0x2000,  0 },
    { -128, 13, 0x2018, 32 },
    { -128, 13, 0x2020, 64 },
    { -112, 13, 0x2010,  0 },
    { -112, 13, 0x2028, 40 },
    {  -96, 13, 0x2008,  0 },
    {  -96,  1, 0x2000, 32 },
    {  -96,  9, 0x2030, 48 },
    {   64,  5, 0x010A,  0 },
    {   64, 13, 0x210E, 16 }
  }
};
static SKC_sprite_pattern scoresp01 = {
  8,
  {
    { -128, 13, 0x2000,  0 },
    { -128, 13, 0x2018, 32 },
    { -128, 13, 0x2020, 64 },
    { -112, 13, 0x2010,  0 },
    { -112, 13, 0x2028, 40 },
    {  -96,  9, 0x2030, 48 },
    {   64,  5, 0x010A,  0 },
    {   64, 13, 0x210E, 16 }
  }
};
static SKC_sprite_pattern scoresp02 = {
  9,
  {
    { -128, 13, 0x2000,  0 },
    { -128, 13, 0x2018, 32 },
    { -128, 13, 0x2020, 64 },
    { -112, 13, 0x2028, 40 },
    {  -96, 13, 0x2008,  0 },
    {  -96,  1, 0x2000, 32 },
    {  -96,  9, 0x2030, 48 },
    {   64,  5, 0x010A,  0 },
    {   64, 13, 0x210E, 16 }
  }
};
static SKC_sprite_pattern scoresp03 = {
  7,
  {
    { -128, 13, 0x2000,  0 },
    { -128, 13, 0x2018, 32 },
    { -128, 13, 0x2020, 64 },
    { -112, 13, 0x2028, 40 },
    {  -96,  9, 0x2030, 48 },
    {   64,  5, 0x010A,  0 },
    {   64, 13, 0x210E, 16 }
  }
};
static SKC_sprite_pattern scoresp04 = {
  5,
  {
    { -128, 13, 0x2008,  0 },
    { -128,  1, 0x2000, 32 },
    { -128,  9, 0x2030, 48 },
    {   64,  5, 0x010A,  0 },
    {   64, 13, 0x210E, 16 }
  }
};
static SKC_sprite_pattern scoresp05 = {
  3,
  {
    { -128,  9, 0x2030, 48 },
    {   64,  5, 0x010A,  0 },
    {   64, 13, 0x210E, 16 }
  }
};


void scoreup(unsigned short points) {
  g_ram.plscore += points;
  if (999999 <= g_ram.plscore) {
    g_ram.plscore = 999999;
  }
  if (g_ram.plscore >= g_ram.extrascore) {
    g_ram.extrascore += 5000;
    ++g_ram.pl_suu;
    ++g_ram.pl_suu_f;
    bgmset(42);
  }
}


void scoreset(void) {
  if (g_ram.vs_flag != 0) {
    scoreset3();
  }
  else if (g_ram.editmode != 0) {
    scoreset2();
  }
  else {
    if (g_ram.plscore_f != 0) {
      g_ram.plscore_f = 0;
      scorewrt(g_ram.plscore, &g_vram[0xDC80]);
    }
    if (g_ram.plring_f != 0) {
      if (BIT_IS_SET(g_ram.plring_f, 7)) {
        ringinit();
      }
      g_ram.plring_f = 0;
      ringwrt(g_ram.plring, &g_vram[0xDF40]);
    }
    if (BIT_IS_SET(g_ram.pltime_f, 7)) {
      g_ram.pltime_f = 1;
    }
    else if (g_ram.pltime_f != 0 && g_ram.pauseflag == 0) {
      if (g_ram.pltime.reserved == 0
          && g_ram.pltime.minutes == 9
          && g_ram.pltime.seconds == 59
          && g_ram.pltime.frames == 59) {
        g_ram.pltime_f = 0;
        if (g_ram.actwk[0].r_no < 6 && get_zone(g_ram.stageno) != SLOT_MACHINE) {
          playdieset(&g_ram.actwk[0]);
        }
        g_ram.pltimeover_f = 1;
      }
      else {
        ++g_ram.pltime.frames;
        if (g_ram.pltime.frames >= 60) {
          g_ram.pltime.frames = 0;
          ++g_ram.pltime.seconds;
          if (g_ram.pltime.seconds >= 60) {
            g_ram.pltime.seconds = 0;
            ++g_ram.pltime.minutes;
            if (g_ram.pltime.minutes >= 9) {
              g_ram.pltime.minutes = 9;
            }
          }
          timewrt1(g_ram.pltime.minutes, &g_vram[0xDE40]);
          timewrt(g_ram.pltime.seconds, &g_vram[0xDEC0]);
        }
      }
    }
    if (g_ram.pltimeover_f == 0 && g_ram.pl_suu_f != 0) {
      g_ram.pl_suu_f = 0;
      playsuuwrt();
    }
  }
}


static void scoreset2(void) {
  posiwrt();
  if (g_ram.plring_f != 0) {
    if (BIT_IS_SET(g_ram.plring_f, 7)) {
      ringinit();
    }
    g_ram.plring_f = 0;
    ringwrt(g_ram.plring, &g_vram[0xDF40]);
  }
  timewrt1(g_ram.DAT_08fff628, &g_vram[0xDE40]);
  timewrt(g_ram.linkdata, &g_vram[0xDEC0]);
  if (g_ram.pl_suu_f != 0) {
    g_ram.pl_suu_f = 0;
    playsuuwrt();
  }
  if (g_ram.pauseflag == 0) {
    ++g_ram.pltime.frames;
    if (g_ram.pltime.frames >= 60) {
      g_ram.pltime.frames = 0;
      ++g_ram.pltime.seconds;
      if (g_ram.pltime.seconds >= 60) {
        g_ram.pltime.seconds = 0;
        ++g_ram.pltime.minutes;
        if (g_ram.pltime.minutes >= 9) {
          g_ram.pltime.minutes = 9;
        }
      }
    }
  }
}


static void scoreset3(void) {
  if (g_ram.editmode != 0) {
    posiwrt();
  }
}


static void ringinit(void) {
  scoreinitsub(3, ringinittbl, &g_vram[0xDF40]);
}


void scoreinit(void) {
  playsuuwrt();
  if (g_ram.vs_flag == 0) {
    scoreinitsub(15, scoreinittbl, &g_vram[0xDC40]);
  }
}


static void scoreinitsub(unsigned char char_cnt, signed char* p_data, unsigned char* p_vram) {
  for (int i = 0; i < char_cnt; ++i) {
    if (p_data[i] < 0) {
      memset(p_vram, 0, 64);
    }
    else {
      memcpy(p_vram, &scorewrtcg[p_data[i] * 32], 64);
    }
    p_vram += 64;
  }
}


static signed char scoreinittbl[16] = { 22, -1, -1, -1, -1, -1, -1, 0, 0, 20, 0, 0, -1, -1, 0, -112 };
static signed char* ringinittbl = &scoreinittbl[12];


static void posiwrt(void) {
  unsigned char* p_vram = &g_vram[0xDC40];
  hexwrtw(g_ram.scra_h_posit & 0xFFFF0000 | fp16_get_integer(g_ram.actwk[0].xposi), &p_vram);
  hexwrtw(g_ram.scra_v_posit & 0xFFFF0000 | fp16_get_integer(g_ram.actwk[0].yposi), &p_vram);
}


static void hexwrtw(long hex, unsigned char** pp_vram) {
  for (int i = 0; i < 8; ++i) {
    hex = rotate_long_left(hex, 4);
    unsigned char nibble = hex &0x0000000F;
    if (nibble >= 10) {
      nibble += 7;
    }
    memcpy(*pp_vram, &hexwrtwcg[nibble * 32], 32);
    hex = rotate_long_right(hex, 16);
    *pp_vram += 32;
  }
}


static void ringwrt(unsigned short plring, unsigned char* p_vram) {
  scorewrt2(plring, p_vram, 3, 100);
}


static void scorewrt(unsigned long plscore, unsigned char* p_vram) {
  scorewrt2(plscore, p_vram, 6, 100000);
}


static void scorewrt2(unsigned long number, unsigned char* p_vram, unsigned char digit_cnt, unsigned long base) {
  bool zerowrt = false;
  for (int i = 0; i < digit_cnt; ++i) {
    unsigned char digit = number / base;
    if (zerowrt || digit > 0) {
      memcpy(p_vram, &scorewrtcg[digit * 64], 64);
      zerowrt = true;
    }
    number -= digit * base;
    p_vram += 64;
    base /= 10;
  }
}


static void timewrt1(unsigned char number, unsigned char* p_vram) {
  timewrt0(number, p_vram, 1, 1);
}


static void timewrt(unsigned char number, unsigned char* p_vram) {
  timewrt0(number, p_vram, 2, 10);
}


static void timewrt0(unsigned char number, unsigned char* p_vram, unsigned char digit_cnt, unsigned char base) {
  bool zerowrt = false;
  for (int i = 0; i < digit_cnt; ++i) {
    unsigned char digit = number / base;
    if (zerowrt || digit > 0) {
      memcpy(p_vram, &scorewrtcg[digit * 64], 64);
      zerowrt = true;
    }
    number -= digit * base;
    p_vram += 64;
    base /= 10;
  }
}


static void playsuuwrt(void) {
  unsigned char pl_suu = g_ram.pl_suu;
  unsigned char* p_vram = &g_vram[0xFBA0];
  unsigned char base = 10;

  for (int i = 0; i < 2; ++i) {
    unsigned char digit = pl_suu / base;
    if (i == 1 || digit > 0) {
      memcpy(p_vram, &scorewrtcg[digit * 32], 32);
    }
    else {
      memset(p_vram, 0, 32);
    }
    pl_suu -= digit * base;
    p_vram += 32;
    base /= 10;
  }
}
