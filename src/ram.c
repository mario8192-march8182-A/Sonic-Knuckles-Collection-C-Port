#include "ram.h"
#include <string.h>
#include "types/sonic3ram.h"
#include "types/spritedata.h"
#include "types/swdata.h"

sonic3_ram g_ram;
unsigned char g_vram[0x10000];


void clear_game_ram(void) {
  memset(&g_ram, 0, sizeof(g_ram));
}


unsigned short* get_colorwk(void) {
  return g_ram.colorwk;
}


unsigned short* get_colorwk2(void) {
  return g_ram.colorwk2;
}


unsigned short* get_colorwk3(void) {
  return g_ram.colorwk3;
}


unsigned short* get_demotimer_ptr(void) {
  return &g_ram.demotimer;
}


short* get_hscrollbuff(void) {
  return g_ram.hscrollbuff;
}


unsigned char* get_int_flg_ptr(void) {
  return &g_ram.int_flg;
}


long get_scra_v_posit_copy(void) {
  return g_ram.scra_v_posit_copy;
}


SKC_sprite_data* get_sprite_table(void) {
  return g_ram.sprtbl;
}


unsigned char get_vdp_hint_cache(void) {
  return g_ram.vdp_hint_cache;
}


short get_vscrolla(void) {
  return g_ram.vscroll.a;
}


short get_vscrollb(void) {
  return g_ram.vscroll.b;
}


unsigned short* get_vscrollbuff(void) {
  return g_ram.vscrollbuff;
}


unsigned long get_vs_vscroll(void) {
  return g_ram.vs_vscroll;
}


unsigned char get_waterflag(void) {
  return g_ram.waterflag;
}


void inc_systemtimer(void) {
  ++g_ram.systemtimer;
}


void set_region(unsigned char region) {
  g_ram.mdstatus &= 0x3F;
  g_ram.mdstatus |= (region & 0x03) << 6;
}


void set_swdata1(unsigned short raw_swdata) {
  g_ram.swdata1 = get_swdata(raw_swdata);
}


void set_swdata2(unsigned short raw_swdata) {
  g_ram.swdata2 = get_swdata(raw_swdata);
}
