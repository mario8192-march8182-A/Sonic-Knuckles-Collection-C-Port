#include "screvt.h"
#include <stdbool.h>
#include "data/zonemaptbl.h"
#include "types/block.h"
#include "types/blockname.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "utils/bits.h"
#include "utils/fp16.h"
static void scrollwrt0(unsigned short* p_buffer);
static void hblockwrt(unsigned short** pp_buffer, unsigned short vram_adr, unsigned short cnt);
static void vblockwrt(unsigned short** pp_buffer, unsigned short vram_adr, unsigned short cnt);
static void vsscrollwrt(void);

extern sonic3_ram g_ram;
extern unsigned long g_vdp_window_yposi;


void scr_evt_init(void) {
  g_ram.scd_bg_flag = 0;
  g_ram.glide_flag.power.mizuflag = 0;
  g_ram.DAT_08ffeea4 = 0;
  g_ram.DAT_08ffeea6 = 0;
  g_ram.DAT_08ffeeb2 = 0;
  g_ram.frame_offset_x = 0;
  g_ram.scr_evta = 0;
  g_ram.DAT_08ffeec2 = 0;
  g_ram.DAT_08ffeec4 = 0;
  g_ram.event_flag_3 = 0;
  g_ram.scr_shake_flg = 0;
  g_ram.DAT_08ffeece = 0;
  g_ram.DAT_08ffeed0 = 0;
  g_ram.DAT_08ffef74 = 0;
  g_ram.scr_shakeb_flg = 0;
  g_ram.DAT_08ffef68 = 0;
  g_ram.DAT_08ffef6c = 0;
  g_ram.DAT_08fffac0 = 0;
  g_ram.specstagenohpz = 0;
  g_ram.fadecnt = 0;
  g_ram.scr_work0 = 0;
  g_ram.scr_work1 = 0;
  g_ram.DAT_08ffeed6 = 0;
  g_ram.scr_work3 = 0;
  g_ram.scr_work4 = 0;
  g_ram.scr_work5 = 0;
  g_ram.DAT_08ffeede = 0;
  g_ram.DAT_08ffeee0 = 0;
  g_ram.scrc_v = 0xFFF;
  g_ram.DAT_08ffeeac = 0xFF0;
  g_ram.scr_row = 0x7C;
  g_ram.scra_h_posit_copy = g_ram.scra_h_posit & 0xFFFF0000 | g_ram.scra_h_posit_copy & 0x0000FFFF;
  g_ram.scra_v_posit_copy = g_ram.scra_v_posit & 0xFFFF0000 | g_ram.scra_v_posit_copy & 0x0000FFFF;
  scr_evt_tbl[get_zone(g_ram.stageno)][0][get_act(g_ram.stageno)][0]();
  scr_evt_tbl[get_zone(g_ram.stageno)][0][get_act(g_ram.stageno)][1]();
  g_ram.vscroll.a = g_ram.scra_v_posit_copy >> 16;
  g_ram.vscroll.b = g_ram.scrb_v_posit >> 16;
}


void scr_evt_move(void) {
  g_ram.scra_h_posit_copy = g_ram.scra_h_posit & 0xFFFF0000 | g_ram.scra_h_posit_copy & 0x0000FFFF;
  g_ram.scra_v_posit_copy = g_ram.scra_v_posit & 0xFFFF0000 | g_ram.scra_v_posit_copy & 0x0000FFFF;
  scr_shake2();
  scr_evt_tbl[get_zone(g_ram.stageno)][1][get_act(g_ram.stageno)][0]();
  scr_evt_tbl[get_zone(g_ram.stageno)][1][get_act(g_ram.stageno)][1]();
  g_ram.vscroll.a = g_ram.scra_v_posit_copy >> 16;
  g_ram.vscroll.b = g_ram.scrb_v_posit >> 16;
}


void(*scr_evt_tbl[24][2][2][2])(void) = {
  {
    {
      { &scr_evta_000_init, &scr_evtb_000_init }, { &scr_evta_001_init, &scr_evtb_001_init }
    },{
      { &scr_evta_000,      &scr_evtb_000 },      { &scr_evta_001,      &scr_evtb_001      }
    }
  }
}


void scrollwrt(void) {
  scrollwrt0(g_ram.scrollbuff);
  if (g_ram.DAT_08ffef74 != 0) {
    scrollwrt0(g_ram.DAT_08ffef74);
  }
}


static void scrollwrt0(unsigned short* p_buffer) {
  while (p_buffer[0] != 0) {
    unsigned short vram_adr = p_buffer[0];
    unsigned short cnt = ((p_buffer[1] & 0x7FFF) + 1) * 2;
    bool row = !BIT_IS_SET(p_buffer[1], 15);
    p_buffer[0] = 0;
    p_buffer += 2;
    if (row) {
      hblockwrt(&p_buffer, vram_adr, cnt);
      hblockwrt(&p_buffer, vram_adr + 128, cnt);
    }
    else {
      vblockwrt(&p_buffer, vram_adr, cnt);
      vblockwrt(&p_buffer, vram_adr + 2, cnt);
    }
  }
}


static void hblockwrt(unsigned short** pp_buffer, unsigned short vram_adr, unsigned short cnt) {
  unsigned char* p_vram = &g_vram[vram_adr];

  for (int i = 0; i < cnt; ++i) {
    p_vram[0] = **pp_buffer & 0x00FF;
    p_vram[1] = **pp_buffer >> 8;
    p_vram += 2;
    (*pp_buffer) += 2;
  }
}


static void vblockwrt(unsigned short** pp_buffer, unsigned short vram_adr, unsigned short cnt) {
  unsigned char* p_vram = &g_vram[vram_adr];

  for (int i = 0; i < cnt; ++i) {
    p_vram[0] = **pp_buffer & 0x00FF;
    p_vram[1] = **pp_buffer >> 8;
    p_vram += 128;
    (*pp_buffer) += 2;
  }
}


static void vsscrollwrt(void) {
  unsigned short* p_buffer = g_ram.scrollbuff;

  while (p_buffer[0] != 0) {
    unsigned short vram_adr = p_buffer[0];
    unsigned short cnt = (p_buffer[1] + 1) * 2;
    p_buffer[0] = 0;
    p_buffer += 2;
    hblockwrt(&p_buffer, vram_adr, cnt);
    hblockwrt(&p_buffer, vram_adr + g_ram.DAT_08ffeeb0, cnt);
  }
}


void SpecialVInt_LBZ2WindowCopy(void) {
  unsigned short vram_adr = 0xC000 + (g_ram.DAT_08ffeeca + 13 & 0x1F) * 128;
  memcpy(&g_vram[vram_adr + 0x8000], &g_vram[vram_adr + 100], 28);
  memcpy(&g_vram[vram_adr + 0x8000 + 28], &g_vram[vram_adr], 100);
  if (g_ram.DAT_08ffeeca-- == 0) {
    g_ram.vint_rno += 4;
  }
}


void SpecialVInt_LBZ2ScrollAClear(void) {
  memset(&g_vram[0xC900], 0, 768);
  g_vdp_window_yposi = 40;
  g_ram.vint_rno = 0;
}


void SpecialVInt_LBZ2ScrollAClear2(void) {
  memset(&g_vram[0xC600], 0, 768);
  g_ram.vint_rno += 4;
}


void SpecialVInt_LBZ2WindowClear(void) {
  unsigned char row[128];
  memcpy(&row[0], &g_vram[0x829C], 100);
  memcpy(&row[100], &g_vram[0x8280], 28);
  unsigned char* p_vram = &g_vram[0xC900];

  for (int i = 0; i < 6; ++i) {
    memcpy(&p_vram[i * 128], row, 128);
  }

  g_vdp_window_yposi = 0;
  g_ram.vint_rno = 0;
}


// Draw_TileColumn
// Draw_TileColumn2
// Setup_TileColumnDraw
// Get_LevelChunkColumn
// Draw_TileRow
// Draw_TileRow2


// Setup_TileRowDraw
// 0x006ad96b
// line 102871
static void hblockwrt2(unsigned short* p_scrollbuff, short xposi, short yposi, unsigned short wrt_cnt, unsigned short* p_zonemap_row_offsets, unsigned short vram_base) {
  short cnt_to_edge = PLANE_WIDTH_BLOCKS - to_hblocks_in_plane(xposi);
  short cnt_to_edge_after_wrt = blk_cnt_to_edge - wrt_cnt;
  if (cnt_to_edge_after_wrt >= 0) {
    unsigned short vram_adr = vram_base
                            + to_vtiles_in_plane(yposi & 0xFFF0) * PLANE_WIDTH_TILES
                            + to_htiles_in_plane(xposi);
    vram_adr *= 2; // a tile is two bytes
    *p_scrollbuff++ = vram_adr;
    *p_scrollbuff++ = wrt_cnt;
    unsigned char* p_screen_row = Get_LevelAddr(xposi, yposi, p_zonemap_row_offsets);
    SKC_block_name (*p_blk_row)[8] = Get_ChunkRow(xposi, yposi, p_screen_row);
    hblockwrt2_sub(&p_scrollbuff, p_blk_row, xposi, yposi, wrt_cnt, p_screen_row);
  }
  else {
    wrt_cnt = cnt_to_edge;
    unsigned short vram_adr = vram_base
                            + to_vtiles_in_plane(yposi & 0xFFF0) * PLANE_WIDTH_TILES
                            + to_htiles_in_plane(xposi);
    vram_adr *= 2; // a tile is two bytes
    *p_scrollbuff++ = vram_adr;
    *p_scrollbuff++ = wrt_cnt;
    unsigned char* p_screen_row = Get_LevelAddr(xposi, yposi, p_zonemap_row_offsets);
    SKC_block_name (*p_blk_row)[8] = Get_ChunkRow(xposi, yposi, p_screen_row);
    hblockwrt2_sub(&p_scrollbuff, p_blk_row, xposi, yposi, wrt_cnt, p_screen_row);
    wrt_cnt = -cnt_to_edge_after_wrt;
    vram_adr = vram_base + to_vtiles_in_plane(yposi & 0xFFF0) * PLANE_WIDTH_TILES;
    vram_adr *= 2; // a tile is two bytes
    *p_scrollbuff++ = vram_adr;
    *p_scrollbuff++ = wrt_cnt;
    p_blk_row = Get_LevelAddr(xposi, yposi, p_zonemap_row_offsets);
    hblockwrt2_sub(&p_scrollbuff, p_blk_row, xposi, yposi, wrt_cnt, p_screen_row);
  }
}


static void hblockwrt2_sub(unsigned short** pp_scrollbuff, SKC_block_name (*p_blk_row)[8], short xposi, short yposi, unsigned short wrt_cnt, unsigned char* p_screen_row) {
  for (int i = 0; i < wrt_cnt; ++i) {
    SKC_block_name block_name = (*p_blk_row)[to_blocks_in_screen(xposi)];
    SKC_block block = g_ram.blockwk[block.index];
    if (block_name.vf == 1) {
      block.patterns[0][0].vf ^= 1;
      block.patterns[0][1].vf ^= 1;
      block.patterns[1][0].vf ^= 1;
      block.patterns[1][1].vf ^= 1;
      SKC_pattern_name wk = block.patterns[0][0];
      block.patterns[0][0] = block.patterns[1][0];
      block.patterns[1][0] = wk;
      wk = block.patterns[0][1];
      block.patterns[0][1] = block.patterns[1][1];
      block.patterns[1][1] = wk;
    }
    if (block_name.hf == 1) {
      block.patterns[0][0].hf ^= 1;
      block.patterns[0][1].hf ^= 1;
      block.patterns[1][0].hf ^= 1;
      block.patterns[1][1].hf ^= 1;
      SKC_pattern_name wk = block.patterns[0][0];
      block.patterns[0][0] = block.patterns[0][1];
      wk = block.patterns[1][0];
      block.patterns[1][0] = block.patterns[1][1];
      block.patterns[1][1] = wk;
    }
    (*pp_scrollbuff)[0] = get_raw_pattern_name(block.patterns[0][0]);
    (*pp_scrollbuff)[wrt_cnt * BLOCK_SIZE_TILES] = get_raw_pattern_name(block.patterns[1][0]);
    ++*pp_scrollbuff;
    (*pp_scrollbuff)[0] = get_raw_pattern_name(block.patterns[0][1]);
    (*pp_scrollbuff)[wrt_cnt * BLOCK_SIZE_TILES] = get_raw_pattern_name(block.patterns[1][1]);
    ++*pp_scrollbuff;
    xposi += TILE_SIZE_PIXELS;
    if (xposi % SCREEN_SIZE_PIXELS == 0) {
      p_blk_row = Get_ChunkRow(xposi, yposi, p_screen_row);
    }
  }
  *pp_scrollbuff += wrt_cnt * BLOCK_SIZE_TILES;
  (*pp_scrollbuff)[0] = 0;
}


// Get_LevelAddrChunkRow
// 0x006b4906
// line 102977
static unsigned char* Get_LevelAddr(short xposi, short yposi, unsigned short* p_zonemap_row_offsets) {
  unsigned short yposi_wk = yposi / 32 & g_ram.scr_row;
  unsigned short offset = p_zonemap_row_offsets[yposi_wk / 2];
  unsigned char* p_row = &zonemapwk.data[offset];
  return p_row;
}


// right below
static (SKC_block_name*)[8] Get_ChunkRow(short xposi, short yposi, unsigned char* p_screen_row) {
  unsigned char screen_no = p_zonemap_row[to_blocks(xposi)];
  SKC_block_name (*p_row)[8] = g_ram.mapwk[screen_no].blocks[to_blocks_in_screen(yposi)];
  return p_row;
}


// Setup_TileRowDraw_Competition
// sub_4ECAA


// Refresh_PlaneFull
// 0x006adfab
// line 103058
static void scr_reset(short scr_h_posit, short scr_v_posit_blk, unsigned short* p_zonemap_row_offsets, unsigned short vram_base) {
  for (int i = 0; i < 16; ++i) {
    hblockwrt2(g_ram.scrollbuff, scr_h_posit, scr_v_posit_blk, PLANE_WIDTH_BLOCKS, p_zonemap_row_offsets, vram_base);
    scrollwrt();
    scr_v_posit_blk += 16;
  }
}


// Refresh_PlaneTileDeform
// Refresh_PlaneDirectVScroll
// Refresh_PlaneFull_Competition
// Refresh_PlaneFullDirect
// Refresh_PlaneScreenDirect
// Refresh_PlaneDirect2
// Refresh_PlaneDirect
// DrawTilesAsYouMove
// DrawBGAsYouMove
// loc_4EDD8
// Draw_BG
// Get_DeformDrawPosVert
// sub_4EE8E
// DrawTilesVDeform
// DrawTilesVDeform2
// Get_XDeformRange
// sub_4EF46
// Draw_PlaneVertBottomUp
// Draw_PlaneVertSingleBottomUp
// Draw_PlaneVertTopDown
// Draw_PlaneHorzRightToLeft
// sub_4EFCA
// Draw_PlaneHorzLeftToRight
// sub_4F004
// Draw_PlaneVertBottomUpComplex
// sub_4F03E
// PlainDeformation
// PlainDeformation_Flipped
// MakeFGDeformArray
// ApplyDeformation
// ApplyDeformation3
// ApplyDeformation2
// ApplyFGDeformation
// ApplyFGandBGDeformation
// Apply_FGVScroll


// Reset_TileOffsetPositionActual
// 0x006aff3e
// line 104030
static void scra_posit_blk_set(void) {
  g_ram.scra_h_posit_blk = g_ram.scra_h_posit_copy >> 16 & 0xFFF0;
  g_ram.scra_v_posit_blk = g_ram.scra_v_posit_copy >> 16 & g_ram.DAT_08ffeeac;
}


// Reset_TileOffsetPositionEff
// Update_CameraPositionP2
// Update_VScrollValueP2


// 006b005a
// line 104081
void SpecialEvents(void) {
  void(*act_tbl[6])(void) = {
    &worknai,
    &LAB_006b34f3,
    &LAB_006c5cd1,
    &LAB_006c7860,
    &LAB_006c2367,
    &LAB_006c8ca5
  };

  if (g_ram.actwk[0].r_no >= 6) return;

  act_tbl[g_ram.DAT_08ffeeb2 / 4]();
}


static void worknai(void) {
}


// Adjust_BGDuringLoop
// Get_BGActualEffectiveDiff
// Offset_SomeObjectsDuringTransition
// Offset_ObjectsDuringTransition
// ShakeScreen_Setup

static void scr_shakeb(void) {
  if (g_ram.scr_shakeb_flg == 0) return;

  --g_ram.scr_shakeb_flg;
  g_ram.scra_h_posit_copy += shake_ofs_tbl[g_ram.scr_shakeb_flg] * 0x10000;
}


static signed char shake_ofs_tbl[20] = {
  1, -1,
  1, -1,
  2, -2,
  2, -2,
  3, -3,
  3, -3,
  4, -4,
  4, -4,
  5, -5,
  5, -5
};


static scr_evta_000_init(void) {
  Adjust_AIZ1Chunks();
  scra_posit_blk_set();
  scr_reset();
}


// Adjust_AIZ1Chunks
// 0x006b1f29
// line 104441
static Adjust_AIZ1Chunks(void) {
  if (g_ram.play_type == PLAY_TYPE_KNUCKLES) return;

  memcpy(&g_ram.colorwk2[56], DAT_006b2156, sizeof(unsigned short) * 4);
  SKC_block_name block = { 75, 0, 0, 0 };

  for (int i = 0; i < 8; ++i) {
    g_ram.mapwk[152].blocks[14][i] = block;
    g_ram.mapwk[153].blocks[14][i] = block;
    g_ram.mapwk[154].blocks[14][i] = block;
    g_ram.mapwk[165].blocks[14][i] = block;
    g_ram.mapwk[147].blocks[0][i] = block;
    g_ram.mapwk[155].blocks[0][i] = block;
    g_ram.mapwk[104].blocks[4][i] = block;
  }

  g_ram.mapwk[104].blocks[5][0] = (SKC_block_name){ 2, 1, 0, 0 };

  for (int i = 0; i < 6; ++i) {
    g_ram.mapwk[104].blocks[5][1 + i] = block;
  }

  g_ram.mapwk[104].blocks[5][7] = (SKC_block_name){ 2, 0, 0, 0 };

  for (int i = 0; i < 8; ++i) {
    g_ram.mapwk[127].blocks[4][i] = block;
  }

  g_ram.mapwk[127].blocks[4][2] = (SKC_block_name){ 12, 0, 0, 0 };
  g_ram.mapwk[127].blocks[4][3] = (SKC_block_name){ 6, 1, 0, 0 };
  g_ram.mapwk[127].blocks[4][4] = block;
  g_ram.mapwk[127].blocks[4][5] = block;
  g_ram.mapwk[127].blocks[4][7] = (SKC_block_name){ 10, 1, 0, 0 };
  g_ram.mapwk[176].blocks[4][0] = (SKC_block_name){ 11, 1, 0, 0 };

  for (int i = 0; i < 6; ++i) {
    g_ram.mapwk[176].blocks[4][1 + i] = block;
  }

  g_ram.mapwk[176].blocks[5][2] = (SKC_block_name){ 12, 0, 0, 0 };
  g_ram.mapwk[176].blocks[5][3] = (SKC_block_name){ 6, 1, 0, 0 };
  g_ram.mapwk[176].blocks[5][4] = block;
  g_ram.mapwk[176].blocks[5][5] = block;
}


static void LAB_006b34f3(void) {
  g_ram.frame_offset_x = 0;
  short scra_h = (g_ram.scra_h_posit >> 16) + 4;
  if (scra_h >= (short)g_ram.scr_work1) {
    g_ram.frame_offset_x = 0x200;
    fp16_set_integer(&g_ram.actwk[0].xposi, fp16_get_integer(g_ram.actwk[0].xposi) - g_ram.frame_offset_x);
    fp16_set_integer(&g_ram.actwk[1].xposi, fp16_get_integer(g_ram.actwk[1].xposi) - g_ram.frame_offset_x);
    scra_h -= g_ram.frame_offset_x;
    g_ram.scra_h_posit_blk = (scra_h & 0xFFF0) - 16;
    g_ram.DAT_08ffa9fe = g_ram.scra_h_posit_blk;
  }
  g_ram.scra_h_posit = scra_h << 16 | g_ram.scra_h_posit & 0x0000FFFF;
  g_ram.scra_h_posit_copy = scra_h << 16 | g_ram.scra_h_posit_copy & 0x0000FFFF;
  g_ram.scralim_left = scra_h;
  g_ram.scralim_right = scra_h;
  FUN_006b362a(&g_ram.actwk[0], scra_h);
  FUN_006b362a(&g_ram.actwk[1], scra_h);
}


static void FUN_006b362a(SKC_sprite_status p_playerwk, short scra_h) {
  if (p_playerwk->mstno == 5) {
    p_playerwk->mstno = 0;
  }
  scra_h += 24;
  if ((unsigned short)scra_h > (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
    fp16_set_integer(&p_playerwk->xposi, scra_h);
    p_playerwk->mspeed = 0x400;
  }
  else {
    scra_h += 136;
    if ((unsigned short)scra_h <= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      fp16_set_integer(&p_playerwk->xposi, scra_h);
    }
  }
}


static void LAB_006c2367(void) {
  g_ram.scd_bg_flag = 0xFF;
  g_ram.DAT_08ffee9c += 0xA000;
  g_ram.scr_v_posit_ofs = -(0x2E0 + fp16_get_integer(g_ram.DAT_08ffee9c));
  g_ram.scr_h_posit_ofs = 0x1930;
}


static void LAB_006c5cd1(void) {
  g_ram.frame_offset_x = 0;
  short scra_h = g_ram.scra_h_posit >> 16;
  if (scra_h >= 0x4400) {
    g_ram.frame_offset_x = 0x200;
    fp16_set_integer(&g_ram.actwk[0].xposi, fp16_get_integer(g_ram.actwk[0].xposi) - g_ram.frame_offset_x);
    fp16_set_integer(&g_ram.actwk[1].xposi, fp16_get_integer(g_ram.actwk[1].xposi) - g_ram.frame_offset_x);
    scra_h -= g_ram.frame_offset_x;
    g_ram.scra_h_posit_blk = (scra_h & 0xFFF0) - 16;
    g_ram.scralim_right = 0x4298;
  }
  g_ram.scralim_left = scra_h;
}


static void LAB_006c7860(void) {
  g_ram.frame_offset_x = 0;
  short scra_h = (g_ram.scra_h_posit >> 16) + (g_ram.play_type != PLAY_TYPE_KNUCKLES ? 4 : 5);
  if (scra_h >= 0x4280) {
    if (g_ram.event_flag_3 != 0) {
      g_ram.event_flag_3 = 0xFF;
      if (scra_h >= 0x4420) {
        scra_h = 0x4420;
        g_ram.scralim_right = 0x45A0;
        g_ram.pl_scr_lock_flag = 0xFF;
        g_ram.DAT_08ffeeb2 = 0;
      }
      else {
        g_ram.scralim_right = scra_h;
      }
    }
    else {
      g_ram.frame_offset_x = 0x200;
      fp16_set_integer(&g_ram.actwk[0].xposi, fp16_get_integer(g_ram.actwk[0].xposi) - g_ram.frame_offset_x);
      fp16_set_integer(&g_ram.actwk[1].xposi, fp16_get_integer(g_ram.actwk[1].xposi) - g_ram.frame_offset_x);
      scra_h -= g_ram.frame_offset_x;
      g_ram.scra_h_posit_blk = (scra_h & 0xFFF0) - 16;
      ++g_ram.scr_work4;
      a1 = g_ram.play_type != PLAY_TYPE_KNUCKLES ? DAT_006c7f91 : DAT_006c7fa1;
      g_ram.scr_work3 = g_ram.scr_work3 & 0xFF00 | a1[g_ram.scr_work4 & 0xF];
      if (g_ram.scr_work3 >> 8 != 0) {
        g_ram.scr_work5 = g_ram.scr_work5 & 0xFF00 | 0x00FF;
        g_ram.scr_work3 &= 0x00FF;
      }
      g_ram.scralim_right = scra_h;
    }
  }
  else {
    g_ram.scralim_right = scra_h;
  }
  g_ram.scra_h_posit = scra_h << 16 | g_ram.scra_h_posit & 0x0000FFFF;
  g_ram.scra_h_posit_copy = scra_h << 16 | g_ram.scra_h_posit_copy & 0x0000FFFF;
  g_ram.scralim_left = scra_h;
  FUN_006c7a66(&g_ram.actwk[0], scra_h);
  FUN_006c7a66(&g_ram.actwk[1], scra_h);
}


static void FUN_006c7a66(SKC_sprite_status p_playerwk, short scra_h) {
  if (p_playerwk->mstno == 5) {
    p_playerwk->mstno = 0;
  }
  scra_h += 24;
  if ((unsigned short)scra_h > (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
    fp16_set_integer(&p_playerwk->xposi, scra_h);
    p_playerwk->mspeed = g_ram.play_type != PLAY_TYPE_KNUCKLES ? 0x400 : 0x500;
  }
  else {
    scra_h += 168;
    if ((unsigned short)scra_h <= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      fp16_set_integer(&p_playerwk->xposi, scra_h);
    }
  }
}


static void LAB_006c8ca5(void) {
  if (g_ram.scr_work1 != 0) {
    --g_ram.scr_work1;
  }
  else {
    void(*act_tbl[7])(void) = {
      &LAB_006c8d00,
      &LAB_006c8d31,
      &LAB_006c8d71,
      &LAB_006c8da2,
      &LAB_006c8de2,
      &LAB_006c8e13,
      &LAB_006c8e47
    };

    g_ram.pl_scr_lock_flag = 0xFF;
    act_tbl[g_ram.scr_work0 / 4]();
  }
}


static void LAB_006c8d00(void) {
  if (g_ram.scra_h_posit >> 16 < 0x410) {
    LAB_006c8ebd(0x20000, 0);
  }
  else {
    g_ram.scr_work0 += 4;
    LAB_006c8d31();
  }
}


static void LAB_006c8d31(void) {
  if (g_ram.scra_v_posit >> 16 > 0x330) {
    LAB_006c8ebd(0x16A00, -0x16A00);
  }
  else {
    g_ram.scr_work0 += 4;
    LAB_006c8d71();
  }
}


static void LAB_006c8d71(void) {
  if (g_ram.scra_h_posit >> 16 < 0x650) {
    LAB_006c8ebd(0x20000, 0);
  }
  else {
    g_ram.scr_work0 += 4;
    LAB_006c8da2();
  }
}


static void LAB_006c8da2(void) {
  if (g_ram.scra_v_posit >> 16 > 0x2F0) {
    LAB_006c8ebd(0x16A00, -0x16A00);
  }
  else {
    g_ram.scr_work0 += 4;
    LAB_006c8de2();
  }
}


static void LAB_006c8de2(void) {
  if (g_ram.scra_h_posit >> 16 < 0x910) {
    LAB_006c8ebd(0x20000, 0);
  }
  else {
    g_ram.scr_work0 += 4;
    LAB_006c8e13();
  }
}


static void LAB_006c8e13(void) {
  if (g_ram.scra_v_posit >> 16 < 0x320) {
    LAB_006c8ebd(0x1D900, 0xC400);
  }
  else {
    g_ram.scr_work0 += 4;
    LAB_006c8e47();
  }
}


static void LAB_006c8e47(void) {
  if (g_ram.scra_h_posit >> 16 < 0xBBF) {
    LAB_006c8ebd(0x20000, 0);
  }
  else {
    long_d2 = 0;
    if (fp16_get_integer(g_ram.actwk[0].xposi) < 0xC50) {
      LAB_006c8ebd();
    }
    else {
      g_ram.scralim_left = 0xA00;
      g_ram.scralim_right = 0xBC0;
      g_ram.scralim_down = 0x560;
      g_ram.scralim_n_down = g_ram.scralim_down;
      g_ram.pl_scr_lock_flag = 0;
      g_ram.DAT_08ffeeb2 = 0;
    }
  }
}


static void LAB_006c8ebd(long xoffset, long yoffset) {
  g_ram.scra_v_posit += yoffset;
  g_ram.scra_v_posit_copy = g_ram.scra_v_posit & 0xFFFF0000 | g_ram.scra_v_posit_copy & 0x0000FFFF;
  g_ram.scralim_up = g_ram.scra_v_posit >> 16;
  g_ram.scralim_down = g_ram.scra_v_posit >> 16;
  g_ram.scralim_n_down = g_ram.scra_v_posit >> 16;
  g_ram.scra_h_posit += xoffset;
  g_ram.scra_h_posit_copy = g_ram.scra_h_posit & 0xFFFF0000 | g_ram.scra_h_posit_copy & 0x0000FFFF;
  g_ram.scralim_left = g_ram.scra_h_posit >> 16;
  g_ram.scralim_right = g_ram.scra_h_posit >> 16;
  FUN_006c8fa6(&g_ram.actwk[0], g_ram.scra_h_posit >> 16, xoffset);
  FUN_006c8fa6(&g_ram.actwk[1], g_ram.scra_h_posit >> 16, xoffset);
}


static void FUN_006c8fa6(SKC_sprite_status* p_playerwk, short scra_h, long xoffset) {
  if (p_playerwk->mstno == 5) {
    p_playerwk->mstno = 0;
  }
  scra_h += 16;
  if ((unsigned short)scra_h > (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
    if (p_playerwk->u.play.cddat.push == 1) {
      playdieset(p_playerwk);
    }
    else {
      fp16_set_integer(&p_playerwk->xposi, scra_h);
      p_playerwk->mspeed = xoffset / 0x10000;
    }
  }
  else {
    scra_h += 272;
    if ((unsigned short)scra_h <= (unsigned short)fp16_get_integer(p_playerwk->xposi)) {
      fp16_set_integer(&p_playerwk->xposi, scra_h);
    }
  }
}
