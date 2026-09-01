#include "entry.h"
#include <string.h>
#include "types/sonic3ram.h"
#include "constants.h"
#include "io.h"
#include "modes/opening.h"
#include "modes/stagesel.h"
static void entry(unsigned short cartridge);
static void mainloop(void);
static void (*gmmodetbl[21])(void);
static void logo_init(void);
static void logo(void);

extern sonic3_ram g_ram;
extern int g_vdp_hint_disabled;
extern unsigned long g_vdp_mode;
extern unsigned long g_vdp_window_yposi;
extern int g_numpad_unlocked;


void debug_entry(void) {
  g_ram.cartridge = 0;
  vdpinit();
  read_savedata();
  g_ram.gmmode = STAGESELMD1;
  mainloop();
}


void sk_entry(void) {
  entry(0xFFFF);
}


void s3_entry(void) {
  entry(0);
}


void bs_entry(void) {
  g_ram.romheadermdflag = 0;
  vdpinit();
  g_ram.bsmodemenu = 0;
  g_ram.gmmode = BSMENUMD;
  mainloop();
}


static void entry(unsigned short cartridge) {
  g_ram.cartridge = cartridge;
  vdpinit();
  read_savedata();
  g_ram.gmmode = OPENINGMD;
  mainloop();
}


static void mainloop(void) {
  while (1) {
    g_vdp_hint_disabled = 0;
    g_vdp_mode = 0;
    g_vdp_window_yposi = 0;
    g_numpad_unlocked = 0;
    gmmodetbl[g_ram.gmmode >> 2]();
  }
}


static void (*gmmodetbl[21])(void) = {
  &logo,
  &opening,
  0,
  0,
  &logo_init,
  0,
  &logo_init,
  &stagesel,
  0,
  &stagesel,
  &stagesel,
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


static void logo_init(void) {
  g_ram.gmmode = LOGOMD;
}


static void logo(void) {
  g_ram.gmmode = OPENINGMD;
}
