#include "entry.h"
#include <string.h>
#include "types/sonic3ram.h"
#include "constants.h"
#include "io.h"
static void entry(unsigned short cartridge);
static void mainloop(void);
static void (*gmmodetbl[21])(void);
static void logo_init(void);
static void logo(void);

extern sonic3_ram g_ram;


void debug_entry(void) {
  g_ram.cartridge = 0;
  vdpinit();
  read_savedata();
  g_ram.gmmode = STAGESELMD;
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
    DAT_008549dc = 0;
    DAT_00854de8 = 0;
    DAT_00854758 = 0;
    DAT_0082ddc8 = 0;
    gmmodetbl[g_ram.gmmode >> 2]();
  }
}


static void (*gmmodetbl[21])(void) = {
  &logo,
  0,
  0,
  0,
  &logo_init,
  0,
  &logo_init,
  0,
  0,
  0,
  0,
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
