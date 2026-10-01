#include "screvt.h"
#include <stdbool.h>
#include <string.h>
#include "data/zonemaptbl.h"
#include "types/block.h"
#include "types/blockname.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "utils/bits.h"
#include "utils/fp16.h"
#include "utils/scroll.h"
#include "utils/stageno.h"
#include "coli.h"
typedef struct SKC_screvt_context {
  unsigned short* scrollbuff_ptr;
  unsigned short* screen_row_offset_ptr;
  unsigned short vram_base;
}
SKC_screvt_context;
static void scrollwrt0(unsigned short* p_buffer);
static void hblockwrt(unsigned short** pp_buffer, unsigned short vram_adr, unsigned short cnt);
static void vblockwrt(unsigned short** pp_buffer, unsigned short vram_adr, unsigned short cnt);
static void vsscrollwrt(void);

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];
extern unsigned long g_vdp_window_yposi;
extern unsigned long g_vdp_scrolla_adr;
extern unsigned long g_vdp_scrollb_adr;


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
  SKC_screvt_context context = { g_ram.scrollbuff, g_ram.zonemapwk.row_offsets, g_vdp_scrolla_adr };
  scr_evt_tbl[get_zone(g_ram.stageno)][0][get_act(g_ram.stageno)][0](&context);
  ++context.screen_row_offset_ptr;
  context.vram_base = g_vdp_scrollb_adr;
  scr_evt_tbl[get_zone(g_ram.stageno)][0][get_act(g_ram.stageno)][1](&context);
  g_ram.vscroll.a = g_ram.scra_v_posit_copy >> 16;
  g_ram.vscroll.b = g_ram.scrb_v_posit >> 16;
}


void scr_evt_move(void) {
  g_ram.scra_h_posit_copy = g_ram.scra_h_posit & 0xFFFF0000 | g_ram.scra_h_posit_copy & 0x0000FFFF;
  g_ram.scra_v_posit_copy = g_ram.scra_v_posit & 0xFFFF0000 | g_ram.scra_v_posit_copy & 0x0000FFFF;
  scr_shake2();
  SKC_screvt_context context = { g_ram.scrollbuff, g_ram.zonemapwk.row_offsets, g_vdp_scrolla_adr };
  scr_evt_tbl[get_zone(g_ram.stageno)][1][get_act(g_ram.stageno)][0](&context);
  ++context.screen_row_offset_ptr;
  context.vram_base = g_vdp_scrollb_adr;
  scr_evt_tbl[get_zone(g_ram.stageno)][1][get_act(g_ram.stageno)][1](&context);
  g_ram.vscroll.a = g_ram.scra_v_posit_copy >> 16;
  g_ram.vscroll.b = g_ram.scrb_v_posit >> 16;
}


void(*scr_evt_tbl[24][2][2][2])(SKC_screvt_context*) = {
  {
    {
      { &scr_evta_000_init, &scr_evtb_000_init }, { &scr_evta_001_init, &scr_evtb_001_init }
    },{
      { &scr_evta_000,      &scr_evtb_000 },      { &scr_evta_001,      &scr_evtb_001      }
    }
  }
};


// VInt_DrawLevel
void scrollwrt(void) {
  scrollwrt0(g_ram.scrollbuff);
  if (g_ram.DAT_08ffef74 != 0) {
    scrollwrt0(g_ram.DAT_08ffef74);
  }
}


// VInt_DrawLevel_2
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


// VInt_DrawLevel_Col
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


static void Draw_TileColumn(long* p_scr_h_posit, short* p_scr_h_posit_blk, short scr_v_posit, unsigned short wrt_cnt, SKC_screvt_context* p_context) {
  short prev_scr_h_posit_blk = *p_scr_h_posit_blk;
  short scr_h_posit_blk = *p_scr_h_posit >> 16 & 0xFFF0;
  *p_scr_h_posit_blk = scr_h_posit_blk;
  short distance = prev_scr_h_posit_blk - *p_scr_h_posit_blk;
  if (distance != 0) {
    if (distance < 0) {
      distance = -distance;
      scr_h_posit_blk = prev_scr_h_posit_blk + 336;
    }
    g_ram.DAT_08ffeea4 = distance > BLOCK_SIZE_PIXELS ? 0xFF : 0;
    Setup_TileColumnDraw(scr_h_posit_blk, scr_v_posit, wrt_cnt, p_context);
    if (g_ram.DAT_08ffeea4 != 0) {
      scr_h_posit_blk += BLOCK_SIZE_PIXELS;
      Setup_TileColumnDraw(scr_h_posit_blk, scr_v_posit, wrt_cnt, p_context);
    }
  }
}


// Draw_TileColumn2


static void Setup_TileColumnDraw(short xposi, short yposi, unsigned short wrt_cnt, SKC_screvt_context* p_context) {
  short cnt_to_edge = PLANE_HEIGHT_BLOCKS - to_vblocks_in_plane(xposi);
  short cnt_to_edge_after_wrt = cnt_to_edge - wrt_cnt;
  if (cnt_to_edge_after_wrt >= 0) {
    unsigned short vram_adr = p_context->vram_base
                            + to_htiles_in_plane(xposi & 0xFFF0) * PLANE_HEIGHT_TILES
                            + to_vtiles_in_plane(yposi);
    vram_adr *= 2; // a tile is two bytes
    *p_context->scrollbuff_ptr++ = vram_adr;
    *p_context->scrollbuff_ptr++ = wrt_cnt;
    SET_BIT(p_context->scrollbuff_ptr[-1], 7);
    SKC_block_name* p_blk_col = Get_LevelChunkColumn(xposi, yposi, p_context);
    TileColumnDraw(p_blk_col, xposi, yposi, wrt_cnt);
  }
  else {
    wrt_cnt = cnt_to_edge;
    unsigned short vram_adr = p_context->vram_base
                            + to_htiles_in_plane(xposi & 0xFFF0) * PLANE_HEIGHT_TILES
                            + to_vtiles_in_plane(yposi);
    vram_adr *= 2; // a tile is two bytes
    *p_context->scrollbuff_ptr++ = vram_adr;
    *p_context->scrollbuff_ptr++ = wrt_cnt;
    SET_BIT(p_context->scrollbuff_ptr[-1], 7);
    SKC_block_name* p_blk_col = Get_LevelChunkColumn(xposi, yposi, p_context);
    TileColumnDraw(p_blk_col, xposi, yposi, wrt_cnt);
    yposi += wrt_cnt * TILE_SIZE_PIXELS;
    wrt_cnt = -cnt_to_edge_after_wrt;
    vram_adr = p_context->vram_base + to_htiles_in_plane(xposi & 0xFFF0) * PLANE_HEIGHT_TILES;
    vram_adr *= 2; // a tile is two bytes
    *p_context->scrollbuff_ptr++ = vram_adr;
    *p_context->scrollbuff_ptr++ = wrt_cnt;
    SET_BIT(p_context->scrollbuff_ptr[-1], 7);
    TileColumnDraw(p_blk_col, xposi, yposi, wrt_cnt);
  }
}


static void TileColumnDraw(SKC_block_name* p_blk_col, short xposi, short yposi, unsigned short wrt_cnt, SKC_screvt_context* p_context) {
  for (int i = 0; i < wrt_cnt; ++i) {
    SKC_block_name block_name = p_blk_col[to_blocks_in_screen(yposi) * SCREEN_SIZE_BLOCKS];
    SKC_block block = g_ram.blockwk[block_name.index];
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
    p_context->scrollbuff_ptr[0] = get_raw_pattern_name(block.patterns[0][0]);
    p_context->scrollbuff_ptr[1] = get_raw_pattern_name(block.patterns[1][0]);
    p_context->scrollbuff_ptr += wrt_cnt * BLOCK_SIZE_TILES;
    p_context->scrollbuff_ptr[0] = get_raw_pattern_name(block.patterns[0][1]);
    p_context->scrollbuff_ptr[1] = get_raw_pattern_name(block.patterns[1][1]);
    p_context->scrollbuff_ptr -= wrt_cnt * BLOCK_SIZE_TILES;
    p_context->scrollbuff_ptr += 2;
    yposi += TILE_SIZE_PIXELS;
    if (yposi % SCREEN_SIZE_PIXELS == 0) {
      p_blk_col = Get_LevelChunkColumn(xposi, yposi, p_context);
    }
  }
  p_context->scrollbuff_ptr += wrt_cnt * BLOCK_SIZE_TILES;
  p_context->scrollbuff_ptr[0] = 0;
}


static SKC_block_name* Get_LevelChunkColumn(short xposi, short yposi, SKC_screvt_context* p_context) {
  unsigned short yposi_wk = yposi / 32 & g_ram.scr_row;
  unsigned short offset = p_context->screen_row_offset_ptr[yposi_wk / 2];
  unsigned char* p_screen_row = &g_ram.zonemapwk.data[offset];
  unsigned char screen_no = p_screen_row[to_blocks(xposi)];
  SKC_block_name* p_blk_row = &g_ram.mapwk[screen_no].blocks[0][to_blocks_in_screen(xposi)];
  return p_blk_row;
}


// Draw_TileRow
// Draw_TileRow2


static void Setup_TileRowDraw(short xposi, short yposi, unsigned short wrt_cnt, SKC_screvt_context* p_context) {
  short cnt_to_edge = PLANE_WIDTH_BLOCKS - to_hblocks_in_plane(xposi);
  short cnt_to_edge_after_wrt = cnt_to_edge - wrt_cnt;
  if (cnt_to_edge_after_wrt >= 0) {
    unsigned short vram_adr = p_context->vram_base
                            + to_vtiles_in_plane(yposi & 0xFFF0) * PLANE_WIDTH_TILES
                            + to_htiles_in_plane(xposi);
    vram_adr *= 2; // a tile is two bytes
    *p_context->scrollbuff_ptr++ = vram_adr;
    *p_context->scrollbuff_ptr++ = wrt_cnt;
    unsigned char* p_screen_row = Get_LevelAddrChunkRow(xposi, yposi, p_context->screen_row_offset_ptr);
    SKC_block_name* p_blk_row = Get_ChunkRow(xposi, yposi, p_screen_row);
    TileRowDraw(p_blk_row, xposi, yposi, wrt_cnt, p_screen_row, p_context);
  }
  else {
    wrt_cnt = cnt_to_edge;
    unsigned short vram_adr = p_context->vram_base
                            + to_vtiles_in_plane(yposi & 0xFFF0) * PLANE_WIDTH_TILES
                            + to_htiles_in_plane(xposi);
    vram_adr *= 2; // a tile is two bytes
    *p_context->scrollbuff_ptr++ = vram_adr;
    *p_context->scrollbuff_ptr++ = wrt_cnt;
    unsigned char* p_screen_row = Get_LevelAddrChunkRow(xposi, yposi, p_context->screen_row_offset_ptr);
    SKC_block_name* p_blk_row = Get_ChunkRow(xposi, yposi, p_screen_row);
    TileRowDraw(p_blk_row, xposi, yposi, wrt_cnt, p_screen_row);
    xposi += wrt_cnt * TILE_SIZE_PIXELS;
    wrt_cnt = -cnt_to_edge_after_wrt;
    vram_adr = p_context->vram_base + to_vtiles_in_plane(yposi & 0xFFF0) * PLANE_WIDTH_TILES;
    vram_adr *= 2; // a tile is two bytes
    *p_context->scrollbuff_ptr++ = vram_adr;
    *p_context->scrollbuff_ptr++ = wrt_cnt;
    p_screen_row = Get_LevelAddrChunkRow(xposi, yposi, p_context->screen_row_offset_ptr);
    p_blk_row = Get_ChunkRow(xposi, yposi, p_screen_row);
    TileRowDraw(p_blk_row, xposi, yposi, wrt_cnt, p_screen_row, p_context);
  }
}


static void TileRowDraw(SKC_block_name* p_blk_row, short xposi, short yposi, unsigned short wrt_cnt, unsigned char* p_screen_row, SKC_screvt_context* p_context) {
  for (int i = 0; i < wrt_cnt; ++i) {
    SKC_block_name block_name = p_blk_row[to_blocks_in_screen(xposi)];
    SKC_block block = g_ram.blockwk[block_name.index];
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
    p_context->scrollbuff_ptr[0] = get_raw_pattern_name(block.patterns[0][0]);
    p_context->scrollbuff_ptr[1] = get_raw_pattern_name(block.patterns[0][1]);
    p_context->scrollbuff_ptr += wrt_cnt * BLOCK_SIZE_TILES;
    p_context->scrollbuff_ptr[0] = get_raw_pattern_name(block.patterns[1][0]);
    p_context->scrollbuff_ptr[1] = get_raw_pattern_name(block.patterns[1][1]);
    p_context->scrollbuff_ptr -= wrt_cnt * BLOCK_SIZE_TILES;
    p_context->scrollbuff_ptr += 2;
    xposi += TILE_SIZE_PIXELS;
    if (xposi % SCREEN_SIZE_PIXELS == 0) {
      p_blk_row = Get_ChunkRow(xposi, yposi, p_screen_row);
    }
  }
  p_context->scrollbuff_ptr += wrt_cnt * BLOCK_SIZE_TILES;
  p_context->scrollbuff_ptr[0] = 0;
}


static unsigned char* Get_LevelAddrChunkRow(short xposi, short yposi, SKC_screvt_context* p_context) {
  unsigned short yposi_wk = yposi / 32 & g_ram.scr_row;
  unsigned short offset = p_context->screen_row_offset_ptr[yposi_wk / 2];
  unsigned char* p_row = &g_ram.zonemapwk.data[offset];
  return p_row;
}


static SKC_block_name* Get_ChunkRow(short xposi, short yposi, unsigned char* p_screen_row) {
  unsigned char screen_no = p_screen_row[to_blocks(xposi)];
  SKC_block_name* p_row = &g_ram.mapwk[screen_no].blocks[to_blocks_in_screen(yposi)][0];
  return p_row;
}


// Setup_TileRowDraw_Competition
// sub_4ECAA


static void Refresh_PlaneFull(short xposi, short yposi, SKC_screvt_context* p_context) {
  unsigned short* p_scrollbuff = p_context->scrollbuff_ptr;

  for (int i = 0; i < PLANE_HEIGHT_BLOCKS; ++i) {
    Setup_TileRowDraw(xposi, yposi, PLANE_WIDTH_BLOCKS, p_context);
    scrollwrt();
    p_context->scrollbuff_ptr = p_scrollbuff;
    yposi += BLOCK_SIZE_PIXELS;
  }
}


static void Refresh_PlaneTileDeform(short yposi, short* p_scr_tbl, short* p_hscrollwork, SKC_screvt_context* p_context) {
  unsigned short* p_scrollbuff = p_context->scrollbuff_ptr;
  short line_cnt = *p_scr_tbl++;

  for (int i = 0; i < PLANE_HEIGHT_BLOCKS; ++i) {
    while (yposi >= line_cnt) {
      line_cnt += *p_scr_tbl++;
      p_hscrollwork += 2;
    }

    Setup_TileRowDraw(*p_hscrollwork, yposi, PLANE_WIDTH_BLOCKS, p_context);
    scrollwrt();
    p_context->scrollbuff_ptr = p_scrollbuff;
    yposi += BLOCK_SIZE_PIXELS;
  }
}


// Refresh_PlaneDirectVScroll
// Refresh_PlaneFull_Competition
// Refresh_PlaneFullDirect
// Refresh_PlaneScreenDirect
// Refresh_PlaneDirect2
// Refresh_PlaneDirect


static void DrawTilesAsYouMove(SKC_screvt_context* p_context) {
  Draw_TileColumn(&g_ram.scra_h_posit_copy, &g_ram.scra_h_posit_blk, g_ram.scra_v_posit_copy >> 16, 16, p_context);
  Draw_TileRow(&g_ram.scra_h_posit_copy, &g_ram.scra_v_posit_copy, g_ram.scra_v_posit_blk, 22, p_context);
}


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


static void MakeFGDeformArray(short* p_hscrollwork, short* p_scr_tbl, unsigned short line_cnt, short offset) {
  for (int i = 0; i < line_cnt; ++i) {
    p_hscrollwork[i] = p_scr_tbl[i] + offset;
  }
}


static short* ApplyDeformation(unsigned short* p_scr_tbl, short* p_hscrollwork) {
  return ApplyDeformation3(p_scr_tbl, p_hscrollwork, 224);
}


static short* ApplyDeformation3(unsigned short* p_scr_tbl, short* p_hscrollwork, unsigned short line_cnt) {
  return ApplyDeformation2(g_ram.hscrollbuff, p_scr_tbl, p_hscrollwork,
                           g_ram.scra_h_posit_copy >> 16, g_ram.scrb_v_posit >> 16, line_cnt);
}


static short* ApplyDeformation2(short* p_hscrollbuff, unsigned short* p_scr_tbl, short* p_hscrollwork, short xposi, short yposi, unsigned short line_cnt) {
  bool line_scr;
  unsigned short pending_line_cnt;

  do {
    line_scr = BIT_IS_SET(*p_scr_tbl, 15);
    pending_line_cnt = *p_scr_tbl++ & 0x7FFF;
    yposi -= pending_line_cnt;
    if (yposi >= 0) {
      if (!line_scr) {
        ++p_hscrollwork;
      }
      else {
        p_hscrollwork += pending_line_cnt;
      }
    }
    else if (line_scr) {
      p_hscrollwork += pending_line_cnt - -yposi;
    }
  }
  while (yposi >= 0);

  pending_line_cnt = -yposi <= line_cnt ? -yposi : line_cnt;
  unsigned short total_pending_line_cnt = line_cnt;
  goto skip_first;

  do {
    line_scr = BIT_IS_SET(*p_scr_tbl, 15);
    short wk = *p_scr_tbl++ & 0x7FFF;
    pending_line_cnt = wk <= total_pending_line_cnt ? wk : total_pending_line_cnt;

skip_first:
    if (line_scr) {
      for (int i = 0; i < pending_line_cnt; ++i) {
        *p_hscrollbuff++ = -xposi;
        *p_hscrollbuff++ = -*p_hscrollwork++;
      }
    }
    else {
      for (int i = 0; i < pending_line_cnt; ++i) {
        *p_hscrollbuff++ = -xposi;
        *p_hscrollbuff++ = -*p_hscrollwork;
      }

      ++p_hscrollwork;
    }
    total_pending_line_cnt -= pending_line_cnt;
  }
  while (total_pending_line_cnt != 0);

  return p_hscrollbuff;
}


// ApplyFGDeformation


static void ApplyFGandBGDeformation(short* p_hscrollbuff, short* p_hscrollawork, unsigned short* p_scr_tbl, short* p_hscrollbwork, short* p_ofs_tbl, short yposi, unsigned short line_cnt) {
  bool line_scr;
  unsigned short pending_line_cnt;

  do {
    line_scr = BIT_IS_SET(*p_scr_tbl, 15);
    pending_line_cnt = *p_scr_tbl++ & 0x7FFF;
    yposi -= pending_line_cnt;
    if (yposi >= 0) {
      if (!line_scr) {
        ++p_hscrollbwork;
      }
      else {
        p_hscrollbwork += pending_line_cnt;
      }
    }
    else if (line_scr) {
      p_hscrollbwork += pending_line_cnt - -yposi;
    }
  }
  while (yposi >= 0);

  pending_line_cnt = -yposi <= line_cnt ? -yposi : line_cnt;
  unsigned short total_pending_line_cnt = line_cnt;
  goto skip_first;

  do {
    line_scr = BIT_IS_SET(*p_scr_tbl, 15);
    short wk = *p_scr_tbl++ & 0x7FFF;
    pending_line_cnt = wk <= total_pending_line_cnt ? wk : total_pending_line_cnt;

skip_first:
    if (line_scr) {
      for (int i = 0; i < pending_line_cnt; ++i) {
        *p_hscrollbuff++ = *p_hscrollawork++;
        *p_hscrollbuff++ = -*p_hscrollbwork++ + *p_ofs_tbl++;
      }
    }
    else {
      for (int i = 0; i < pending_line_cnt; ++i) {
        *p_hscrollbuff++ = *p_hscrollawork++;
        *p_hscrollbuff++ = -*p_hscrollbwork + *p_ofs_tbl++;
      }

      ++p_hscrollawork;
    }
    total_pending_line_cnt -= pending_line_cnt;
  }
  while (total_pending_line_cnt != 0);
}


// Apply_FGVScroll


static void Reset_TileOffsetPositionActual(void) {
  g_ram.scra_h_posit_blk = g_ram.scra_h_posit_copy >> 16 & 0xFFF0;
  g_ram.scra_v_posit_blk = g_ram.scra_v_posit_copy >> 16 & g_ram.DAT_08ffeeac;
}


static void Reset_TileOffsetPositionEff(void) {
  g_ram.scrb_h_posit_blk = g_ram.scrb_h_posit >> 16 & 0xFFF0;
  g_ram.scrb_v_posit_blk = g_ram.scrb_v_posit >> 16 & g_ram.DAT_08ffeeac;
}


// Update_CameraPositionP2
// Update_VScrollValueP2


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


static AIZ_TreeReveal(short xposi, short yposi, unsigned char* p_tbl, SKC_screvt_context* p_context) {
  p_context->scrollbuff_ptr += 2;
  unsigned char* p_screen_row = Get_LevelAddrChunkRow(xposi, yposi, p_context->screen_row_offset_ptr);
  SKC_block_name* p_blk_row = Get_ChunkRow(xposi, yposi, p_screen_row);

  for (int i = 0; i < 16; ++i) {
    SKC_block_name block_name = p_blk_row[to_blocks_in_screen(xposi)];
    SKC_block block = g_ram.blockwk[block_name.index];
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
    if (p_tbl[i] != 0) {
      p_scrollbuff[0] = get_raw_pattern_name(block.patterns[0][0]);
      p_scrollbuff[1] = get_raw_pattern_name(block.patterns[0][1]);
    }
    if (p_tbl[i + 16] != 0) {
      p_scrollbuff += 16 * BLOCK_SIZE_TILES;
      p_scrollbuff[0] = get_raw_pattern_name(block.patterns[1][0]);
      p_scrollbuff[1] = get_raw_pattern_name(block.patterns[1][1]);
      p_scrollbuff -= 16 * BLOCK_SIZE_TILES;
    }
    p_scrollbuff += 2;
    xposi += TILE_SIZE_PIXELS;
    if (xposi % SCREEN_SIZE_PIXELS == 0) {
      p_blk_row = Get_ChunkRow(xposi, yposi, p_screen_row);
    }
  }
  p_scrollbuff += 16 * BLOCK_SIZE_TILES;
  p_scrollbuff[0] = 0;
}


static void AIZ1_IntroDeform(void) {
  g_ram.scrb_v_posit = g_ram.scra_v_posit_copy & 0xFFFF0000 | g_ram.scrb_v_posit & 0x0000FFFF;
  short offset = (g_ram.DAT_08ffeeb6 < 0 ? g_ram.DAT_08ffeeb6 : g_ram.scra_h_posit_copy >> 16) / 2;
  if (offset >= 0x580) {
    for (int i = 0; i < 37; ++i) {
      g_ram.hscrollwork[20 + i] = offset;
    }
  }
  else {
    g_ram.hscrollwork[20] = offset;
    offset -= 0x580;
    long offset_wk = offset * 0x10000;
    long delta = offset * 0x800;

    for (int i = 0; i < 36; ++i) {
      offset_wk += delta;
      g_ram.hscrollwork[21 + i] = fp16_get_integer(offset_wk) - 0x580;
    }
  }

  for (int i = 0; i < 9; ++i) {
    short wk = g_ram.hscrollwork[21 + i * 4];
    g_ram.hscrollwork[2 + i * 2] = wk >= 0 ? wk : 0;
  }
}


static void AIZ1_Deform(void) {
  g_ram.scrb_v_posit = (g_ram.scra_v_posit_copy / 2) & 0xFFFF0000 | g_ram.scrb_v_posit & 0x0000FFFF;
  long offset = ((g_ram.scra_h_posit_copy >> 16) - 0x1300) * 0x800;
  long offset_wk = offset * 14;
  g_ram.hscrollwork[24] = fp16_get_integer(offset_wk);
  offset_wk += offset * 2;
  g_ram.hscrollwork[2] = fp16_get_integer(offset_wk);
  g_ram.hscrollwork[25] = fp16_get_integer(offset_wk);
  g_ram.hscrollwork[29] = fp16_get_integer(offset_wk);
  offset_wk += offset * 2;
  g_ram.hscrollwork[26] = fp16_get_integer(offset_wk);
  g_ram.hscrollwork[28] = fp16_get_integer(offset_wk);
  offset_wk += offset * 2;
  g_ram.hscrollwork[27] = fp16_get_integer(offset_wk);
  offset_wk = offset;
  g_ram.hscrollwork[10] = fp16_get_integer(offset_wk);
  short wk = g_ram.hscrollwork[30] * 0x10000;
  g_ram.hscrollwork[30] += 32;
  offset_wk /= 2;

  for (int i = 0; i < 6; ++i) {
    offset_wk += wk;
    g_ram.hscrollwork[9 - i] = fp16_get_integer(offset_wk);
    offset_wk += offset;
  }

  offset_wk = offset;

  for (int i = 0; i < 13; ++i) {
    offset_wk += offset / 8;
    g_ram.hscrollwork[11 + i] = fp16_get_integer(offset_wk);
  }
}


static void AIZ1_ApplyDeformWater(void) {
  short dry_line_cnt = g_ram.waterposi - g_ram.scra_v_posit_copy >> 16;
  if (dry_line_cnt >= 224) {
    ApplyDeformation(AIZ1_DeformArray, &g_ram.hscrollwork[4]);
  }
  else {
    short* p_hscrollbuff = ApplyDeformation3(AIZ1_DeformArray, &g_ram.hscrollwork[4], dry_line_cnt);
    short underwater_line_cnt = -(dry_line_cnt - 224);
    unsigned short d2 = g_ram.gametimer / 2 + g_ram.waterposi & 0x003F;
    MakeFGDeformArray(&g_ram.hscrollwork[32], &AIZ1_WaterFGDeformDelta[d2],
                      underwater_line_cnt, -(g_ram.scra_h_posit_copy >> 16));
    short waterposi = g_ram.waterposi - (g_ram.scra_v_posit_copy >> 16) + (g_ram.scrb_v_posit >> 16);
    d2 = g_ram.gametimer / 2 + waterposi & 0x003F;
    ApplyFGandBGDeformation(p_hscrollbuff, &g_ram.hscrollwork[32], AIZ1_DeformArray, &g_ram.hscrollwork[4],
                            &AIZ1_WaterBGDeformDelta[d2], waterposi, underwater_line_cnt);
  }
}


static void scr_evta_000_init(SKC_screvt_context* p_context) {
  Adjust_AIZ1Chunks();
  Reset_TileOffsetPositionActual();
  Refresh_PlaneFull(g_ram.scra_h_posit_copy, g_ram.scra_v_posit_blk, p_context);
}


static void scr_evta_000(SKC_screvt_context* p_context) {
  unsigned char tloop_tbl[112] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  };

  DrawTilesAsYouMove(p_context);
  if (g_ram.DAT_08ffeec4 != 0) {
    bool chg = true;
    if (g_ram.scra_h_posit >> 16 < 0x2D30 && g_ram.DAT_08ffeec4 < 57) {
      if (g_ram.DAT_08ffeec4 >= 52) {
        AIZ1SE_ChangeChunk2(p_context);
      }
      else if (g_ram.DAT_08ffeec4 >= 36) {
        AIZ1SE_ChangeChunk3(p_context);
      }
      else if (g_ram.DAT_08ffeec4 >= 20) {
        AIZ1SE_ChangeChunk4(p_context);
      }
      unsigned char* p_tbl = tloop_tbl;
      if (!(g_ram.DAT_08ffeec4 & 1)) {
        p_tbl += 16;
      }
      unsigned short wk = (g_ram.DAT_08ffeec4 - 1) / 2;
      g_ram.scr_work0 = wk;
      if (wk >= 3) {
        g_ram.scr_work0 = 2;
      }
      short yposi = -((short)wk * 16) + 1136;

      do {
        if (yposi < g_ram.scra_v_posit_blk) {
          p_tbl += 32;
          yposi += 16;
          chg = true;
        }
        else {
          unsigned short* p_scrollbuff = p_context->scrollbuff_ptr;
          Setup_TileRowDraw(0x2C80, yposi, 16, p_context);
          p_context->scrollbuff_ptr = p_scrollbuff;
          yposi -= 640;
          AIZ_TreeReveal(0, yposi, p_tbl, p_context);
          p_tbl += 16;
          yposi += 656;
          chg = false;
        }
      }
      while (g_ram.scr_work0-- > 0);
    }
    if (chg) {
      AIZ1SE_ChangeChunk1(p_context);
    }
  }
}


static void AIZ1SE_ChangeChunk1(SKC_screvt_context* p_context) {
  g_ram.DAT_08ffeec4 = 0;
  unsigned short offset = p_context->screen_row_offset_ptr[10];
  unsigned char* p_row = &g_ram.zonemapwk.data[offset];
  p_row[90] = 88;
  p_row[89] = 89;
  AIZ1SE_ChangeChunk2(p_context);
}


static void AIZ1SE_ChangeChunk2(SKC_screvt_context* p_context) {
  unsigned short offset = p_context->screen_row_offset_ptr[12];
  unsigned char* p_row = &g_ram.zonemapwk.data[offset];
  p_row[88] = 92;
  p_row[91] = 90;
  AIZ1SE_ChangeChunk3(p_context);
}


static void AIZ1SE_ChangeChunk3(SKC_screvt_context* p_context) {
  unsigned short offset = p_context->screen_row_offset_ptr[14];
  unsigned char* p_row = &g_ram.zonemapwk.data[offset];
  p_row[90] = 91;
  p_row[89] = 93;
  AIZ1SE_ChangeChunk4(p_context);
}


static void AIZ1SE_ChangeChunk4(SKC_screvt_context* p_context) {
  unsigned short offset = p_context->screen_row_offset_ptr[16];
  unsigned char* p_row = &g_ram.zonemapwk.data[offset];
  p_row[88] = 94;
  p_row[91] = 95;
}


void Obj_AIZ1TreeRevealControl(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0 && g_ram.DAT_08ffeec4 == 0) {
    frameout(p_actwk);
  }
  else {
    --p_actwk->u.obj.timer;
    unsigned short wk = (unsigned short)(0x480 - fp16_get_integer(g_ram.actwk[0].yposi)) / 8 + 3;
    if (wk >= g_ram.DAT_08ffeec4 || !(p_actwk->u.obj.timer & 1)) {
      ++g_ram.DAT_08ffeec4;
    }
  }
}


static void Adjust_AIZ1Chunks(void) {
  if (g_ram.play_type != PLAY_TYPE_KNUCKLES) return;

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


static void scr_evtb_000_init(SKC_screvt_context* p_context) {
  if (g_ram.scra_h_posit >> 16 < 0x1300) {
    memset(g_ram.hscrollwork, 0, sizeof(short) * 20);
    AIZ1_IntroDeform();
    Reset_TileOffsetPositionEff();
    Refresh_PlaneFull(g_ram.scrb_h_posit, g_ram.scrb_v_posit_blk, p_context);
    ApplyDeformation(AIZ1_IntroDeformArray, &g_ram.hscrollwork[20]);
  }
  else {
    g_ram.DAT_08ffeec2 = 8;
    AIZ1_Deform();
    Reset_TileOffsetPositionEff();
    g_ram.hscrollwork[0] = 0;
    g_ram.hscrollwork[1] = 0;
    g_ram.hscrollwork[3] = g_ram.scrb_h_posit_blk;
    Refresh_PlaneTileDeform(g_ram.scrb_v_posit_blk, AIZ1_BGDrawArray, g_ram.hscrollwork, p_context);
    AIZ1_ApplyDeformWater();
  }
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


static void FUN_006b362a(SKC_sprite_status* p_playerwk, short scra_h) {
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


static void FUN_006c7a66(SKC_sprite_status* p_playerwk, short scra_h) {
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
