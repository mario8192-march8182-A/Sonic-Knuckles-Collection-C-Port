#include "globals.h"
#include "macros.h"
#include "types/animscript.h"
#include "game.h"
#include "bitdevr.h"
#include "color.h"
#include "data.h"
#include "mapdevr.h"
#include "opening.h"
#include "savedata.h"
#include "specialstagemode.h"
#include "util.h"
#include "vdp.h"
static void(*g_gameModes[21])();
static void patset_hud();
static void init_vdp();
static unsigned short* init_sprlist_vp_linkdata(unsigned short* p_sprlist);
static void init_sprlist_first(unsigned long* p_sprlist);
static sprite_status* action2(sprite_status* p_actwk, int cnt);
static void action3();
static sprite_status* action4(sprite_status* p_actwk, int cnt);
static void patset_compound(sprite_status* p_actwk);
static unsigned short spatset(sprite_status* p_actwk, sprite_pattern* p_sprpat, short xposi, short yposi, unsigned short spr_cnt, unsigned short spritesleft_cnt);
static unsigned char xshapeoffsets[16];
static unsigned char yshapeoffsets[16];
static void patset_vs();
static void FUN_004487b9();
static void patset_rings();
static unsigned short FUN_00824b55(unsigned char* p_text, unsigned short coloroffset);
static void FUN_00824c47(unsigned short** pp_chunkmappings1, unsigned short** pp_chunkmappings2, unsigned short* p_map, unsigned short coloroffset);
static void FUN_00824d7e(unsigned short** pp_chunkmappings1, unsigned short** pp_chunkmappings2, unsigned short* p_map, unsigned short coloroffset);

extern void levelselect();
extern void executeBgmCommand(signed char command);
extern void playSoundEffect2(signed char command);


// 0040ff14
void start_debug() {
  g_mdRam.cartridge = 0;
  init_vdp();
  load_savedata();
  g_mdRam.gmmode = 28;
  gameloop();
}


// 0040ff72
void start_specialstagemode() {
  g_mdRam.romheadermdflag = 0;
  init_vdp();
  g_mdRam.specmodemenu = 0;
  g_mdRam.gmmode = 44;
  gameloop();
}


// 00410095
void start_game(unsigned short cartridge) {
  g_mdRam.cartridge = cartridge;
  init_vdp();
  load_savedata();
  g_mdRam.gmmode = 4;
  gameloop();
}


// 004100cf
void gameloop() {
  while (1) {
    DAT_008549dc = 0;
    DAT_00854de8 = 0;
    DAT_00854758 = 0;
    DAT_0082ddc8 = 0;
    unsigned char gmmode = (g_mdRam.gmmode & 0x7C) / 4;
    g_gameModes[gmmode]();
  }
}


/* 00410130 */ static void(*g_gameModes[21])()  = {
  0,
  &opening,
  0,
  0,
  0,
  0,
  0,
  &levelselect,
  0,
  &levelselect,
  &levelselect,
  &specialstagemode,
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


// 004122ac
static void patset_hud() {
  // TODO
}


// 0041a6fe
static void init_vdp() {
  g_mdRam.vscrolla = 0;
  g_mdRam.vscrollb = 0;
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

  g_mdRam.vscrolla = 0;
  g_mdRam.vscrollb = 0;
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


// 0041e61c
void init_sprlist() {
  g_mdRam.sprhmasks = 0;
  g_mdRam.alt_sprlistadr = 0;
  if (g_mdRam.vs_flag != 0) {
    unsigned short* p_sprlist = init_sprlist_vp_linkdata(g_mdRam.ramf8);
    init_sprlist_first((unsigned long*)p_sprlist);
    p_sprlist = init_sprlist_vp_linkdata((unsigned short*)&g_mdRam.chunkmappings128[0x7880]);
    init_sprlist_first((unsigned long*)p_sprlist);
    init_sprlist_vp_linkdata((unsigned short*)&g_mdRam.chunkmappings128[0x7B00]);
    init_sprlist_vp_linkdata((unsigned short*)&g_mdRam.chunkmappings128[0x7D80]);
  }
  else {
    init_sprlist_vp_linkdata(g_mdRam.ramf8);
  }
}


// 0041e683
static unsigned short* init_sprlist_vp_linkdata(unsigned short* p_sprlist) {
  unsigned char linkdata = 1;

  for (int i = 0; i < 80; ++i) {
    *p_sprlist = 0;
    ((unsigned char*)p_sprlist)[3] = linkdata;
    ++linkdata;
    p_sprlist += 4;
  }

  ((unsigned char*)p_sprlist)[-5] = 0;

  return p_sprlist;
}


// 0041e700
static void init_sprlist_first(unsigned long* p_sprlist) {
  p_sprlist -= 160;
  *p_sprlist++ = 0x1000000;
  *p_sprlist++ = 0;
  *p_sprlist++ = 0x2000000;
  *p_sprlist = 0;
}


// 0041e760
void action() {
  if (g_mdRam.teleport != 0) return;

  if (g_mdRam.vs_flag != 0 || g_mdRam.actwk[0].r_no == 12 || g_mdRam.actwk[0].r_no < 6) {
    action2(&g_mdRam.actwk[0], 110);
  }
  else {
    action3();
  }
}


// 0041e79a
static sprite_status* action2(sprite_status* p_actwk, int cnt) {
  for (int i = 0; i < cnt; ++i) {
    if (p_actwk->r_ptr != 0) {
      p_actwk->r_ptr(p_actwk);
    }
    ++p_actwk;
  }

  return p_actwk;
}


// 0041e7e5
static void action3() {
  sprite_status* p_actwk = action2(&g_mdRam.actwk[0], 4);
  p_actwk = action4(p_actwk, 90);
  action2(p_actwk, 16);
}


// 0041e80f
static sprite_status* action4(sprite_status* p_actwk, int cnt) {
  for (int i = 0; i < cnt; ++i) {
    if (p_actwk->r_ptr != 0 && IS_ONSCREEN(p_actwk->actflg)) {
      actionsub(p_actwk);
    }
    ++p_actwk;
  }

  return p_actwk;
}


// 0041eb34
void actionsub(sprite_status* p_actwk) {
  unsigned char level_no = p_actwk->sprpri / (PBUFFER_LEVEL_SLOTS * PBUFFER_LEVEL_SLOT_SIZE);
  unsigned short* pri_level = &g_mdRam.pbuffer[level_no][0];
  bool done = false;

  do {
    if (pri_level[0] < PBUFFER_LEVEL_MAX_SIZE) {
      pri_level[0] += PBUFFER_LEVEL_SLOT_SIZE;
      pri_level[pri_level[0] / PBUFFER_LEVEL_SLOT_SIZE] = p_actwk - g_mdRam.actwk;
      done = true;
    }
    else if (pri_level == &g_mdRam.pbuffer[PBUFFER_LEVELS - 1][0]) {
      done = true;
    }
    else {
      pri_level += PBUFFER_LEVEL_SLOTS;
    }
  } while (!done);
}


// 0041ebc7
void patchg(sprite_status* p_actwk, signed char** p_chg_data) {
  if (p_actwk->mstno != p_actwk->restart) {
    p_actwk->restart = p_actwk->mstno;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
  }
  if (p_actwk->pattim-- != 0) return;

  signed char* p_sprpat = p_chg_data[p_actwk->mstno];
  p_actwk->pattim = p_sprpat[0];
  signed char patno = p_sprpat[p_actwk->patcnt + 1];
  if (patno < 0) {
    switch (patno) {
      case PS_CONTROL_LOOP:
        p_actwk->patcnt = 0;
        patno = p_sprpat[1];
        break;
      case PS_CONTROL_REWIND:
        patno = p_sprpat[p_actwk->patcnt + 2];
        p_actwk->patcnt -= patno;
        patno = p_sprpat[p_actwk->patcnt - patno + 1];
        break;
      case PS_CONTROL_NEXT:
        p_actwk->mstno = p_sprpat[p_actwk->patcnt + 2];
        return;
      case PS_CONTROL_ROUTINE:
        p_actwk->r_no += 2;
        p_actwk->pattim = 0;
        ++p_actwk->patcnt;
        return;
      case PS_CONTROL_FOUT:
        util__assign_high(&p_actwk->xposi, 0x7F00);
        return;
      default:
        return;
    }
  }
  p_actwk->patno = patno;
  p_actwk->actflg &= 0xFC;
  p_actwk->actflg |= p_actwk->cddat1 & 3;
  ++p_actwk->patcnt;
}


// 0041ee2d
void patchg2(sprite_status* p_actwk, signed char** p_chg_data) {
  if (p_actwk->mstno != p_actwk->restart) {
    p_actwk->restart = p_actwk->mstno;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
  }
  if (p_actwk->pattim-- != 0) return;

  signed char* p_sprpat = p_chg_data[p_actwk->mstno];
  signed char patno = p_sprpat[p_actwk->patcnt * 2];
  if (patno < 0) {
    switch (patno) {
      case PS_CONTROL_LOOP:
        p_actwk->patcnt = 0;
        patno = p_sprpat[p_actwk->patcnt * 2];
        break;
      case PS_CONTROL_REWIND:
        patno = p_sprpat[p_actwk->patcnt * 2 + 1];
        p_actwk->patcnt -= patno;
        patno = p_sprpat[p_actwk->patcnt * 2 - patno * 2];
        break;
      case PS_CONTROL_NEXT:
        p_actwk->mstno = p_sprpat[p_actwk->patcnt * 2 + 1];
        return;
      case PS_CONTROL_ROUTINE:
        p_actwk->r_no += 2;
        p_actwk->pattim = 0;
        ++p_actwk->patcnt;
        return;
    }
  }
  p_actwk->pattim = p_sprpat[p_actwk->patcnt * 2 + 1];
  p_actwk->patno = patno;
  p_actwk->actflg &= 0xFC; // clear HFLIP and VFLIP
  p_actwk->actflg |= p_actwk->cddat1 & 3;
  ++p_actwk->patcnt;
}


// 0041f0b6
void patset() {
  if (g_mdRam.vs_flag != 0) {
    patset_vs();
    return;
  }

  unsigned short spritesleft_cnt = 80;
  g_pLevelSelectVram = g_mdRam.ramf8;
  if (g_mdRam.DAT_08fff711 != 0) {
    patset_hud();
    patset_rings();
  }

  for (int i = 0; i < PBUFFER_LEVELS; ++i) {
    if (g_mdRam.pbuffer[i][0] == 0) continue;

    unsigned short* p_pbufferrow = &g_mdRam.pbuffer[i][1];

    do {
      int act = *p_pbufferrow++;
      sprite_status* p_actwk = &g_mdRam.actwk[act];
      CLEAR_ONSCREEN(p_actwk->actflg);
      if (IS_COMPOUND(p_actwk->actflg)) {
        patset_compound(p_actwk);
        goto next;
      }
      short xposi = LONG_HIGH(p_actwk->xposi);
      short yposi = LONG_HIGH(p_actwk->yposi);
      if (USES_LEVEL_COORDS(p_actwk->actflg)) {
        xposi -= LONG_HIGH(g_mdRam.scra_h_posit_copy);
        if (xposi + p_actwk->sprhs < 0) {
          goto next;
        }
        if (xposi - p_actwk->sprhs >= 320) {
          goto next;
        }
        xposi += 128;

        yposi -= LONG_HIGH(g_mdRam.scra_v_posit_copy);
        yposi += p_actwk->sprvs;
        yposi &= g_mdRam.scrc_v;
        if (yposi >= p_actwk->sprvs * 2 + 224) {
          goto next;
        }
        yposi += 128;
        yposi -= p_actwk->sprvs;
      }
      SET_ONSCREEN(p_actwk->actflg);
      if (spritesleft_cnt > 0 && p_actwk->patbase != 0) {
        sprite_pattern* p_sprpat;
        unsigned short spr_cnt;
        if (HAS_STATIC_PATTERN(p_actwk->actflg)) {
          p_sprpat = (sprite_pattern*)p_actwk->patbase;
          spr_cnt = 1;
        }
        else {
          p_sprpat = p_actwk->patbase[p_actwk->patno];
          if (p_sprpat->cnt == 0) {
            goto next;
          }
          spr_cnt = p_sprpat->cnt;
        }
        spritesleft_cnt = spatset(p_actwk, p_sprpat, xposi, yposi, spr_cnt, spritesleft_cnt);
      }

next:
      g_mdRam.pbuffer[i][0] -= 2;
    } while (g_mdRam.pbuffer[i][0] != 0);


    if (i == 0 && GET_ZONE(g_mdRam.stageno) == LAVA_REEF) {
      FUN_004487b9();
    }
  }

  if (spritesleft_cnt != 0) {
    for (int i = 0; i < spritesleft_cnt; ++i) {
      *g_pLevelSelectVram = 0;
      g_pLevelSelectVram += 4;
    }
  }
  g_mdRam.scrsprcnt = 80 - spritesleft_cnt;
  if (g_mdRam.sprhmasks != 0) {
    if (g_mdRam.actwk[0].r_no < 6) {
      g_mdRam.sprhmasks = 0;
    }
    DAT_008547bc = 1;
    unsigned short* p_ramf8 = g_mdRam.ramf8;

    for (int i = 0; i < 79; ++i) {
      if (p_ramf8[2] == 0x7C0) {
        p_ramf8[3] = 1;
        p_ramf8[7] = 0;
      }
    }
  }
}


// 0041f577
static void patset_compound(sprite_status* p_actwk) {
  // TODO
}


// 0041fac8
static unsigned short spatset(sprite_status* p_actwk, sprite_pattern* p_sprpat, short xposi, short yposi, unsigned short spr_cnt, unsigned short spritesleft_cnt) {
  switch (p_actwk->actflg & 3) {
    case 0:
      for (int i = 0; i < spr_cnt; ++i) {
        *((short*)g_pLevelSelectVram) = p_sprpat->spr[i].yoff + yposi;
        ++g_pLevelSelectVram;
        *((unsigned char*)g_pLevelSelectVram) = p_sprpat->spr[i].etc;
        ++g_pLevelSelectVram;
        *g_pLevelSelectVram = p_sprpat->spr[i].index + p_actwk->sproffset;
        ++g_pLevelSelectVram;
        short new_xposi = p_sprpat->spr[i].xoff + xposi;
        new_xposi &= 0x1FF;
        if (new_xposi == 0) {
          ++new_xposi;
        }
        *((short*)g_pLevelSelectVram) = new_xposi;
        ++g_pLevelSelectVram;
        --spritesleft_cnt;
        if (spritesleft_cnt == 0) break;
      }
      break;
    case 1:
      for (int i = 0; i < spr_cnt; ++i) {
        *((short*)g_pLevelSelectVram) = p_sprpat->spr[i].yoff + yposi;
        ++g_pLevelSelectVram;
        *((unsigned char*)g_pLevelSelectVram) = p_sprpat->spr[i].etc;
        ++g_pLevelSelectVram;
        *g_pLevelSelectVram = (p_sprpat->spr[i].index + p_actwk->sproffset) ^ 0x800;
        ++g_pLevelSelectVram;
        short new_xposi = -p_sprpat->spr[i].xoff - xshapeoffsets[p_sprpat->spr[i].etc] + xposi;
        new_xposi &= 0x1FF;
        if (new_xposi == 0) {
          ++new_xposi;
        }
        *((short*)g_pLevelSelectVram) = new_xposi;
        ++g_pLevelSelectVram;
        --spritesleft_cnt;
        if (spritesleft_cnt == 0) break;
      }
      break;
    case 3:
      for (int i = 0; i < spr_cnt; ++i) {
        *((short*)g_pLevelSelectVram) = -p_sprpat->spr[i].yoff - yshapeoffsets[p_sprpat->spr[i].etc] + yposi;
        ++g_pLevelSelectVram;
        *((unsigned char*)g_pLevelSelectVram) = p_sprpat->spr[i].etc;
        ++g_pLevelSelectVram;
        *g_pLevelSelectVram = (p_sprpat->spr[i].index + p_actwk->sproffset) ^ 0x1800;
        ++g_pLevelSelectVram;
        short new_xposi = -p_sprpat->spr[i].xoff - xshapeoffsets[p_sprpat->spr[i].etc] + xposi;
        new_xposi &= 0x1FF;
        if (new_xposi == 0) {
          ++new_xposi;
        }
        *((short*)g_pLevelSelectVram) = new_xposi;
        ++g_pLevelSelectVram;
        --spritesleft_cnt;
        if (spritesleft_cnt == 0) break;
      }
      break;
    case 2:
      for (int i = 0; i < spr_cnt; ++i) {
        ((unsigned char*)g_pLevelSelectVram)[2] = p_sprpat->spr[i].etc;
        *((short*)g_pLevelSelectVram) = -p_sprpat->spr[i].yoff - yshapeoffsets[p_sprpat->spr[i].etc] + yposi;
        g_pLevelSelectVram += 2;
        *g_pLevelSelectVram = (p_sprpat->spr[i].index + p_actwk->sproffset) ^ 0x1000;
        ++g_pLevelSelectVram;
        short new_xposi = p_sprpat->spr[i].xoff + xposi;
        new_xposi &= 0x1FF;
        if (new_xposi == 0) {
          ++new_xposi;
        }
        *((short*)g_pLevelSelectVram) = new_xposi;
        ++g_pLevelSelectVram;
        --spritesleft_cnt;
        if (spritesleft_cnt == 0) break;
      }
      break;
  }

  return spritesleft_cnt;
}


// 0041fdff
static unsigned char xshapeoffsets[16] = {
  8, 8, 8, 8, 16, 16, 16, 16, 24, 24, 24, 24, 32, 32, 32, 32
};


// 0041ffff
static unsigned char yshapeoffsets[16] = {
  8, 16, 24, 32, 8, 16, 24, 32, 8, 16, 24, 32, 8, 16, 24, 32
};


// 00420a46
static void patset_vs() {
  // TODO
}


// 00426f24
unsigned long random() {
  unsigned long d1 = g_mdRam.ranum;
  if (d1 == 0) {
    d1 = 711800411;
  }
  unsigned long d0 = d1;
  d1 = d1 << 2 & 0xFFFFFFFF;
  d1 = (d1 + d0) & 0xFFFFFFFF;
  d1 = d1 << 3 & 0xFFFFFFFF;
  d1 = (d1 + d0) & 0xFFFFFFFF;
  d0 = (d0 & 0xFFFF0000) | (d1 & 0x0000FFFF);
  ROTATE_RIGHT(d1, 16);
  d0 = (d0 & 0xFFFF0000) | (((d0 & 0x0000FFFF) + (d1 & 0x0000FFFF)) & 0x0000FFFF);
  d1 = (d1 & 0xFFFF0000) | (d0 & 0x0000FFFF);
  ROTATE_RIGHT(d1, 16);
  g_mdRam.ranum = d1;
  return d0;
}


// 004487b9
static void FUN_004487b9() {
  // TODO
}


// 0044da9c
static void patset_rings() {
  // TODO
}


// 00824a1c
void load_string_vram(unsigned char* p_text, unsigned long vramoffset, unsigned short coloroffset) {
  unsigned short mapping_cnt = FUN_00824b55(p_text, coloroffset);
  vramoffset += 0xC000;
  vramoffset &= 0xFFFF;
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[vramoffset];
  memcpy(g_pLevelSelectVram, &g_mdRam.chunkmappings128[0x7000], mapping_cnt * 2);
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[vramoffset + 128];
  memcpy(g_pLevelSelectVram, &g_mdRam.chunkmappings128[0x7080], mapping_cnt * 2);
}


// 00824b55
static unsigned short FUN_00824b55(unsigned char* p_text, unsigned short coloroffset) {
  unsigned short* p_chunkmappings1 = (unsigned short*)&g_mdRam.chunkmappings128[0x7000];
  unsigned short* p_chunkmappings2 = (unsigned short*)&g_mdRam.chunkmappings128[0x7080];
  unsigned short mapping_cnt = 0;
  bool end = false;

  do {
    unsigned char letter = *p_text++;
    if (letter == 0) {
      end = true;
    }
    else {
      switch (letter) {
        case ' ':
          ++mapping_cnt;
          *p_chunkmappings1++ = 0;
          *p_chunkmappings2++ = 0;
          break;
        case '?':
          mapping_cnt += 2;
          FUN_00824c47(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[116], coloroffset);
          break;
        case '!':
          ++mapping_cnt;
          FUN_00824d7e(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[114], coloroffset);
          break;
        case '&':
          mapping_cnt += 2;
          FUN_00824c47(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[110], coloroffset);
          break;
        case ')':
          ++mapping_cnt;
          FUN_00824d7e(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[108], coloroffset);
          break;
        case '(':
          ++mapping_cnt;
          FUN_00824d7e(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[106], coloroffset);
          break;
        case '.':
          ++mapping_cnt;
          FUN_00824d7e(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[104], coloroffset);
          break;
        case 'I':
          ++mapping_cnt;
          FUN_00824d7e(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[32], coloroffset);
          break;
        default:
          mapping_cnt += 2;
          FUN_00824c47(&p_chunkmappings1, &p_chunkmappings2, &largetext_map[(letter - 65) * 4], coloroffset);
          break;
      }
    }
  } while (!end);

  return mapping_cnt;
}


// 00824c47
static void FUN_00824c47(unsigned short** pp_chunkmappings1, unsigned short** pp_chunkmappings2, unsigned short* p_map, unsigned short coloroffset) {
  *(*pp_chunkmappings1)++ = *p_map++ + coloroffset;
  *(*pp_chunkmappings1)++ = *p_map++ + coloroffset;
  *(*pp_chunkmappings2)++ = *p_map++ + coloroffset;
  *(*pp_chunkmappings2)++ = *p_map++ + coloroffset;
}


// 00824d7e
static void FUN_00824d7e(unsigned short** pp_chunkmappings1, unsigned short** pp_chunkmappings2, unsigned short* p_map, unsigned short coloroffset) {
  *(*pp_chunkmappings1)++ = *p_map++ + coloroffset;
  *(*pp_chunkmappings2)++ = *p_map++ + coloroffset;
}
