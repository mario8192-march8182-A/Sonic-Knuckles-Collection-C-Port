#include "io.h"
#include <string.h>
#include "types/sonic3ram.h"

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void vdpinit(void) {
  g_ram.vscroll.a = 0;
  g_ram.vscroll.b = 0;
  g_ram.hscroll = 0;
  memset(g_vram, 0, sizeof(g_vram));
}


void scrinit(void) {
  memset(g_vram, 0, 64);
  if (g_ram.vs_flag != 0) {
    memset(&g_vram[0x8000], 0, 0x4000);
  }
  else {
    memset(&g_vram[0xC000], 0, 0x1000);
    memset(&g_vram[0xE000], 0, 0x1000);
  }
  g_ram.vscroll.a = 0;
  g_ram.vscroll.b = 0;
  g_ram.hscroll = 0;
  memset(g_ram.sprtbl, 0, sizeof(g_ram.sprtbl));
  memset(g_ram.hscrollbuff, 0, sizeof(g_ram.hscrollbuff));
}
