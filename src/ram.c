#include "ram.h"
#include <string.h>
#include "types/sonic3ram.h"
#include "types/spritedata.h"
#include "types/swdata.h"
static void set_swdata(SKC_swdata* p_swdata, unsigned short raw_swdata);

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
  return g_ram.vscrolla;
}


short get_vscrollb(void) {
  return g_ram.vscrollb;
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


void set_swdata1(unsigned short swdata) {
  set_swdata(&g_ram.swdata1, swdata);
}


void set_swdata2(unsigned short swdata) {
  set_swdata(&g_ram.swdata2, swdata);
}


static void set_swdata(SKC_swdata* p_swdata, unsigned short raw_swdata) {
  p_swdata->pressed.u = raw_swdata;
  p_swdata->pressed.d = raw_swdata >> 1;
  p_swdata->pressed.l = raw_swdata >> 2;
  p_swdata->pressed.r = raw_swdata >> 3;
  p_swdata->pressed.b = raw_swdata >> 4;
  p_swdata->pressed.c = raw_swdata >> 5;
  p_swdata->pressed.a = raw_swdata >> 6;
  p_swdata->pressed.s = raw_swdata >> 7;
  p_swdata->down.u = raw_swdata >> 8;
  p_swdata->down.d = raw_swdata >> 9;
  p_swdata->down.l = raw_swdata >> 10;
  p_swdata->down.r = raw_swdata >> 11;
  p_swdata->down.b = raw_swdata >> 12;
  p_swdata->down.c = raw_swdata >> 13;
  p_swdata->down.a = raw_swdata >> 14;
  p_swdata->down.s = raw_swdata >> 15;
}
