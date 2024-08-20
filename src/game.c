#include "globals.h"
#include "macros.h"
#include "types/animscript.h"
#include "bitdevr.h"
#include "color.h"
#include "mapdevr.h"
#include "savedata.h"
#include "vdp.h"
static void(*g_gameModes[21])();

extern void levelselect();
extern void executeBgmCommand(signed char command);
extern void playSoundEffect2(signed char command);

void start_debug();
void gameloop();
void init_vdp();
void clear_displaydata();
void bgmset(signed char command);
void soundset(signed char command);


// 0040ff14
void start_debug() {
  g_mdRam.cartridge = 0;
  init_vdp();
  load_savedata();
  g_mdRam.gamemode = 28;
  gameloop();
}


// 004100cf
void gameloop() {
  while (1) {
    DAT_008549dc = 0;
    DAT_00854de8 = 0;
    DAT_00854758 = 0;
    DAT_0082ddc8 = 0;
    unsigned char gamemode = (g_mdRam.gamemode & 0x7C) / 4;
    g_gameModes[gamemode]();
  }
}


/* 00410130 */ static void(*g_gameModes[21])()  = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  &levelselect,
  0,
  &levelselect,
  &levelselect,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};


// 0041a6fe
void init_vdp() {
  g_mdRam.vscroll = 0;
  g_mdRam.hscroll = 0;
  memset(g_mdVram, 0, sizeof(g_mdVram));
}


// 0041a75c
void clear_displaydata() {
  memset(g_mdVram, 0, 64);

  if (g_mdRam.vs_flag != 0) {
    memset(&g_mdVram[0x8000], 0, 0x4000);
  }

  memset(&g_mdVram[0xC000], 0, 0x1000);
  memset(&g_mdVram[0xE000], 0, 0x1000);

  g_mdRam.vscroll = 0;
  g_mdRam.hscroll = 0;

  /* BUGFIX:
    The original ASM cleared four bytes too many due to the loop counter
    not taking into account that the loop counts down to -1.
  */
  memset(g_mdRam.ramf8, 0, sizeof(g_mdRam.ramf8));

  /* BUGFIX:
    The original ASM cleared four bytes too many due to the loop counter
    not taking into account that the loop counts down to -1.
  */
  memset(g_mdRam.hscrollbuff, 0, sizeof(g_mdRam.hscrollbuff) + sizeof(g_mdRam.colibuffer));
}


// 0041a81b
void bgmset(signed char command) {
  executeBgmCommand(command);
}


// 0041a82d
void soundset(signed char command) {
  playSoundEffect2(command);
}
