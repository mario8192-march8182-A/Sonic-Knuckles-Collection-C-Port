#include "globals.h"
#include "macros.h"
#include <string.h>
#include "types/colortblentry.h"
#include "color.h"
#include "colortbl.h"
static void fadein1();
static void fadein2(unsigned short* p_destination, unsigned short* p_source);
static void fadein0();
static void fadeout1();
static void fadeout2(unsigned short* pPalette);
static void fadein0_alt();
static void flashin2();
static void flashout2(unsigned short* pPalette);

extern void vInt();


// 00426210
void fadein() {
  g_mdRam.colorcnt = 63;
  fadein0();

  for (int fadecount = 0; fadecount < 22; ++fadecount) {
    g_mdRam.int_flg = 18;
    vInt();
    fadein1();
  }
}


// 00426258
static void fadein1() {
  unsigned short* p_destination = &g_mdRam.colorwk[g_mdRam.startcolor / 2];
  unsigned short* p_source = &g_mdRam.colorwk2[g_mdRam.startcolor / 2];
  unsigned char cnt = g_mdRam.colorcnt;

  do {
    fadein2(p_destination, p_source);
    ++p_destination;
    ++p_source;
  } while (cnt-- != 0);

  if (g_mdRam.watermode != 0) {
    p_destination = &g_mdRam.colorwk3[g_mdRam.startcolor / 2];
    p_source = &g_mdRam.colorwk4[g_mdRam.startcolor / 2];
    cnt = g_mdRam.colorcnt;

    do {
      fadein2(p_destination, p_source);
      ++p_destination;
      ++p_source;
    } while (cnt-- != 0);
  }
}


// 0042634e
static void fadein2(unsigned short* p_destination, unsigned short* p_source) {
  if (*p_destination == *p_source) return;

  unsigned short color = *p_destination + 0x200;
  if (color <= *p_source) {
    *p_destination = color;
    return;
  }

  color = *p_destination + 0x20;
  if (color <= *p_source) {
    *p_destination = color;
    return;
  }

  *p_destination += 2;
}


// 00426447
static void fadein0() {
  if (g_mdRam.stageno == ENDING || g_mdRam.stageno == MASTER_EMERALD_SHRINE) {
    fadein0_alt();
    return;
  }

  unsigned short* p_palette = &g_mdRam.colorwk[g_mdRam.startcolor / 2];
  unsigned char cnt = g_mdRam.colorcnt * 2;
  memset(p_palette, 0, cnt);
  if (g_mdRam.watermode != 0) {
    p_palette = &g_mdRam.colorwk3[g_mdRam.startcolor / 2];
    memset(p_palette, 0, cnt);
  }
}


// 0042653f
void fadeout() {
  g_mdRam.startcolor = 0;
  g_mdRam.colorcnt = 63;

  for (int fadecount = 0; fadecount < 22; ++fadecount) {
    g_mdRam.int_flg = 18;
    vInt();
    fadeout1();
  }
}


// 00426580
static void fadeout1() {
  unsigned short* pPalette = &g_mdRam.colorwk[g_mdRam.startcolor / 2];
  for (int i = 0; g_mdRam.colorcnt >= i; ++i) {
    fadeout2(pPalette);
    ++pPalette;
  }

  pPalette = &g_mdRam.colorwk3[g_mdRam.startcolor / 2];
  for (int i = 0; g_mdRam.colorcnt >= i; ++i) {
    fadeout2(pPalette);
    ++pPalette;
  }
}


// 0042662d
static void fadeout2(unsigned short* pPalette) {
  unsigned short color = *pPalette;
  if (color == 0) return;

  unsigned short red = color & 0xE;
  if (red != 0) {
    *pPalette -= 0x2;
    return;
  }

  unsigned short green = color & 0xE0;
  if (green != 0) {
    *pPalette -= 0x20;
    return;
  }

  unsigned short blue = color & 0xE00;
  if (blue != 0) {
    *pPalette -= 0x200;
    return;
  }
}


// 0042670d
static void fadein0_alt() {
  unsigned short* p_palette = &g_mdRam.colorwk[g_mdRam.startcolor / 2];

  for (int i = 0; g_mdRam.colorcnt >= i; ++i) {
    *p_palette++ = 0xEEE;
  }

  g_mdRam.DAT_08ffface = 0;
}


// 0042678c
void flashin() {
  g_mdRam.colorcnt = 63;
  fadein0_alt();

  for (int i = 0; i < 22; ++i) {
    g_mdRam.int_flg = 18;
    vInt();
    flashin1();
  }
}


// 004267d2
void flashin1() {
  if (g_mdRam.DAT_08ffface-- != 0) return;

  g_mdRam.DAT_08ffface = 2;
  unsigned short* p_destination = &g_mdRam.colorwk[g_mdRam.startcolor / 2];
  unsigned short* p_source = &g_mdRam.colorwk2[g_mdRam.startcolor / 2];

  for (int i = 0; g_mdRam.colorcnt >= i; ++i) {
    flashin2((unsigned char*)p_destination, (unsigned char*)p_source);
    ++p_destination;
    ++p_source;
  }

  if (g_mdRam.watermode != 0) {
    p_destination = &g_mdRam.colorwk3[g_mdRam.startcolor / 2];
    p_source = &g_mdRam.colorwk4[g_mdRam.startcolor / 2];

    for (int i = 0; g_mdRam.colorcnt >= i; ++i) {
      flashin2((unsigned char*)p_destination, (unsigned char*)p_source);
      ++p_destination;
      ++p_source;
    }
  }
}


// 004268e8
static void flashin2(unsigned char* p_destination, unsigned char* p_source) {
  unsigned char d1 = *p_source++;
  unsigned char d2 = d1;
  d1 &= 0xE0;
  unsigned char d3 = *p_destination;
  unsigned char d5 = d3;
  d3 &= 0xE0;
  if (d3 > d1) {
    d3 -= 0x20;
  }
  d2 &= 0xE;
  d5 &= 0xE;
  if (d5 > d2) {
    d5 -= 0x02;
  }
  d3 |= d5;
  *p_destination++ = d3;

  d2 = *p_source++;
  d2 &= 0xE;
  d3 = *p_destination;
  d3 &= 0xE;
  if (d3 > d2) {
    d3 -= 0x02;
  }
  *p_destination++ = d3;
}


// 00426a12
void flashout() {
  g_mdRam.colorcnt = 63;

  for (int fadecount = 0; fadecount < 22; ++fadecount) {
    g_mdRam.int_flg = 18;
    vInt();
    flashout1();
  }
}


// 00426a53
void flashout1() {
  unsigned short* pPalette = &g_mdRam.colorwk[g_mdRam.startcolor / 2];

  for (int i = 0; g_mdRam.colorcnt >= i; ++i) {
    flashout2(pPalette);
    ++pPalette;
  }

  pPalette = &g_mdRam.colorwk3[g_mdRam.startcolor / 2];

  for (int i = 0; g_mdRam.colorcnt >= i; ++i) {
    flashout2(pPalette);
    ++pPalette;
  }
}


// 00426b00
static void flashout2(unsigned short* pPalette) {
  unsigned short color = *pPalette;
  if (color == 0xEEE) return;

  unsigned short red = color & 0xE;
  if (red != 0) {
    *pPalette += 0x2;
    return;
  }

  unsigned short green = color & 0xE0;
  if (green != 0) {
    *pPalette += 0x20;
    return;
  }

  unsigned short blue = color & 0xE00;
  if (blue != 0) {
    *pPalette += 0x200;
    return;
  }
}


// 00426c05
void colorset(unsigned short colorno) {
  colortbl_entry* p_entry = &colortbl[colorno];
  memcpy(&g_mdRam.colorwk2[p_entry->offset / 2], p_entry->p_palette, (p_entry->cnt + 1) * 4);
}
