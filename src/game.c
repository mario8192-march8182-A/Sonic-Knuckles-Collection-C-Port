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
static unsigned short patset_compound(sprite_status* p_actwk, unsigned short spritesleft_cnt);
static unsigned short spatset(sprite_status* p_actwk, sprite_pattern* p_sprpat, short xposi, short yposi, unsigned short spr_cnt, unsigned short spritesleft_cnt);
static unsigned char xshapeoffsets[16];
static unsigned char yshapeoffsets[16];
static unsigned short spatset_compound(sprite_status* p_actwk, sprite_pattern* p_sprpat, short xposi, short yposi, unsigned short spr_cnt, unsigned short spritesleft_cnt);
static void patset_vs();
static short sintable[320];
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
  g_ram.cartridge = 0;
  init_vdp();
  load_savedata();
  g_ram.gmmode = 28;
  gameloop();
}


// 0040ff72
void start_specialstagemode() {
  g_ram.romheadermdflag = 0;
  init_vdp();
  g_ram.specmodemenu = 0;
  g_ram.gmmode = 44;
  gameloop();
}


// 00410095
void start_game(unsigned short cartridge) {
  g_ram.cartridge = cartridge;
  init_vdp();
  load_savedata();
  g_ram.gmmode = 4;
  gameloop();
}


// 004100cf
void gameloop() {
  while (1) {
    DAT_008549dc = 0;
    DAT_00854de8 = 0;
    DAT_00854758 = 0;
    DAT_0082ddc8 = 0;
    unsigned char gmmode = (g_ram.gmmode & 0x7C) / 4;
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
  g_ram.vscrolla = 0;
  g_ram.vscrollb = 0;
  g_ram.hscroll = 0;
  memset(g_mdVram, 0, sizeof(g_mdVram));
}


// 0041a75c
void scrinit() {
  memset(g_mdVram, 0, 64);

  if (g_ram.vs_flag != 0) {
    memset(&g_mdVram[0x8000], 0, 0x4000);
  }

  memset(&g_mdVram[0xC000], 0, 0x1000);
  memset(&g_mdVram[0xE000], 0, 0x1000);

  g_ram.vscrolla = 0;
  g_ram.vscrollb = 0;
  g_ram.hscroll = 0;

  /* BUGFIX:
    The original ASM cleared four bytes too many due to the loop counter
    not taking into account that the loop counts down to -1.
  */
  memset(g_ram.ramf8, 0, sizeof(g_ram.ramf8));

  /* BUGFIX:
    The original ASM cleared four bytes too many due to the loop counter
    not taking into account that the loop counts down to -1.
  */
  memset(g_ram.hscrollbuff, 0, sizeof(g_ram.hscrollbuff) + sizeof(g_ram.colibuffer));
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
  g_ram.sprhmasks = 0;
  g_ram.alt_sprlistadr = 0;
  if (g_ram.vs_flag != 0) {
    unsigned short* p_sprlist = init_sprlist_vp_linkdata(g_ram.ramf8);
    init_sprlist_first((unsigned long*)p_sprlist);
    p_sprlist = init_sprlist_vp_linkdata((unsigned short*)&g_ram.chunkmappings128[0x7880]);
    init_sprlist_first((unsigned long*)p_sprlist);
    init_sprlist_vp_linkdata((unsigned short*)&g_ram.chunkmappings128[0x7B00]);
    init_sprlist_vp_linkdata((unsigned short*)&g_ram.chunkmappings128[0x7D80]);
  }
  else {
    init_sprlist_vp_linkdata(g_ram.ramf8);
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
  if (g_ram.teleport != 0) return;

  if (g_ram.vs_flag != 0 || g_ram.actwk[0].r_no == 12 || g_ram.actwk[0].r_no < 6) {
    action2(&g_ram.actwk[0], 110);
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
  sprite_status* p_actwk = action2(&g_ram.actwk[0], 4);
  p_actwk = action4(p_actwk, 90);
  action2(p_actwk, 16);
}


// 0041e80f
static sprite_status* action4(sprite_status* p_actwk, int cnt) {
  for (int i = 0; i < cnt; ++i) {
    if (p_actwk->r_ptr != 0 && BIT_IS_SET(p_actwk->actflg, FLG_ONSCREEN)) {
      actionsub(p_actwk);
    }
    ++p_actwk;
  }

  return p_actwk;
}


// 0041eb34
void actionsub(sprite_status* p_actwk) {
  unsigned char level_no = p_actwk->sprpri / (PBUFFER_LEVEL_SLOTS * PBUFFER_LEVEL_SLOT_SIZE);
  unsigned short* pri_level = &g_ram.pbuffer[level_no][0];
  bool done = false;

  do {
    if (pri_level[0] < PBUFFER_LEVEL_MAX_SIZE) {
      pri_level[0] += PBUFFER_LEVEL_SLOT_SIZE;
      pri_level[pri_level[0] / PBUFFER_LEVEL_SLOT_SIZE] = p_actwk - g_ram.actwk;
      done = true;
    }
    else if (pri_level == &g_ram.pbuffer[PBUFFER_LEVELS - 1][0]) {
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
      case PS_CONTROL_REWIND: {
        unsigned char rewind = p_sprpat[p_actwk->patcnt + 2];
        p_actwk->patcnt -= rewind;
        patno = p_sprpat[p_actwk->patcnt + 1];
        break;
      }
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
      case PS_CONTROL_REWIND: {
        unsigned char rewind = p_sprpat[p_actwk->patcnt * 2 + 1];
        p_actwk->patcnt -= rewind;
        patno = p_sprpat[p_actwk->patcnt * 2];
        break;
      }
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
  if (g_ram.vs_flag != 0) {
    patset_vs();
    return;
  }

  unsigned short spritesleft_cnt = 80;
  g_pLevelSelectVram = g_ram.ramf8;
  if (g_ram.DAT_08fff711 != 0) {
    patset_hud();
    patset_rings();
  }

  for (int i = 0; i < PBUFFER_LEVELS; ++i) {
    if (g_ram.pbuffer[i][0] == 0) continue;

    unsigned short* p_pbufferrow = &g_ram.pbuffer[i][1];

    do {
      int act = *p_pbufferrow++;
      sprite_status* p_actwk = &g_ram.actwk[act];
      CLEAR_BIT(p_actwk->actflg, FLG_ONSCREEN);
      if (BIT_IS_SET(p_actwk->actflg, FLG_COMPOUND)) {
        spritesleft_cnt = patset_compound(p_actwk, spritesleft_cnt);
        goto next;
      }
      short xposi = LONG_HIGH(p_actwk->xposi);
      short yposi = LONG_HIGH(p_actwk->yposi);
      if (BIT_IS_SET(p_actwk->actflg, FLG_LEVELCOORDS)) {
        xposi -= LONG_HIGH(g_ram.scra_h_posit_copy);
        if (xposi + p_actwk->sprhs < 0) {
          goto next;
        }
        if (xposi - p_actwk->sprhs >= 320) {
          goto next;
        }
        xposi += 128;

        yposi -= LONG_HIGH(g_ram.scra_v_posit_copy);
        yposi += p_actwk->sprvs;
        yposi &= g_ram.scrc_v;
        if (yposi >= p_actwk->sprvs * 2 + 224) {
          goto next;
        }
        yposi += 128;
        yposi -= p_actwk->sprvs;
      }
      SET_BIT(p_actwk->actflg, FLG_ONSCREEN);
      if (spritesleft_cnt > 0 && p_actwk->patbase != 0) {
        sprite_pattern* p_sprpat;
        unsigned short spr_cnt;
        if (BIT_IS_SET(p_actwk->actflg, FLG_STATICPATTERN)) {
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
      g_ram.pbuffer[i][0] -= 2;
    } while (g_ram.pbuffer[i][0] != 0);


    if (i == 0 && GET_ZONE(g_ram.stageno) == LAVA_REEF) {
      FUN_004487b9();
    }
  }

  if (spritesleft_cnt != 0) {
    for (int i = 0; i < spritesleft_cnt; ++i) {
      *g_pLevelSelectVram = 0;
      g_pLevelSelectVram += 4;
    }
  }
  g_ram.scrsprcnt = 80 - spritesleft_cnt;
  if (g_ram.sprhmasks != 0) {
    if (g_ram.actwk[0].r_no < 6) {
      g_ram.sprhmasks = 0;
    }
    DAT_008547bc = 1;
    unsigned short* p_ramf8 = g_ram.ramf8;

    for (int i = 0; i < 79; ++i) {
      if (p_ramf8[2] == 0x7C0) {
        p_ramf8[3] = 1;
        p_ramf8[7] = 0;
      }
    }
  }
}


// 0041f577
static unsigned short patset_compound(sprite_status* p_actwk, unsigned short spritesleft_cnt) {
  compound_sprite_status* p_compoundwk = (compound_sprite_status*)p_actwk;
  short xposi = p_compoundwk->xposi;
  short yposi = p_compoundwk->yposi;
  if (!BIT_IS_SET(p_actwk->actflg, FLG_LEVELCOORDS)) {
    xposi -= 128;
    if (xposi + p_actwk->sprhs < 0) goto end;
    if (xposi - p_actwk->sprhs >= 320) goto end;
    xposi += 128;

    yposi -= 128;
    if (yposi + p_actwk->sprvs < 0) goto end;
    if (yposi - p_actwk->sprvs >= 224) goto end;
    yposi += 128;
  }
  else {
    xposi -= util__longhigh_to_short(g_ram.scra_h_posit_copy);
    if (xposi + p_actwk->sprhs < 0) goto end;
    if (xposi - p_actwk->sprhs >= 320) goto end;
    xposi += 128;

    yposi -= util__longhigh_to_short(g_ram.scra_v_posit_copy);
    yposi += p_actwk->sprvs;
    yposi &= g_ram.scrc_v;
    if (yposi >= p_actwk->sprvs * 2 + 224) goto end;
    yposi += 128;
    yposi -= p_actwk->sprvs;
  }

  SET_BIT(p_actwk->actflg, FLG_ONSCREEN);
  if (spritesleft_cnt == 0) goto end;
  if (p_actwk->patno != 0) {
    sprite_pattern* p_sprpat = p_actwk->patbase[p_actwk->patno];
    if (p_sprpat->cnt != 0) {
      spritesleft_cnt = spatset_compound(p_actwk, p_sprpat, xposi, yposi, p_sprpat->cnt, spritesleft_cnt);
      if (spritesleft_cnt == 0) goto end;
    }
  }

  for (int i = 0; i < p_compoundwk->child_cnt; ++i) {
    short xposi = p_compoundwk->children[i].xposi;
    short yposi = p_compoundwk->children[i].yposi;
    if (BIT_IS_SET(p_actwk->actflg, FLG_LEVELCOORDS)) {
      xposi = xposi - util__longhigh_to_short(g_ram.scra_h_posit_copy) + 128;
      yposi = yposi - util__longhigh_to_short(g_ram.scra_v_posit_copy) + 128;
      yposi &= g_ram.scrc_v;
    }
    sprite_pattern* p_sprpat = p_actwk->patbase[p_compoundwk->children[i].patno];
    if (p_sprpat->cnt != 0) {
      spritesleft_cnt = spatset_compound(p_actwk, p_sprpat, xposi, yposi, p_sprpat->cnt, spritesleft_cnt);
    }
    if (spritesleft_cnt == 0) goto end;
  }

end:
  return spritesleft_cnt;
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


// 004201b3
static unsigned short spatset_compound(sprite_status* p_actwk, sprite_pattern* p_sprpat, short xposi, short yposi, unsigned short spr_cnt, unsigned short spritesleft_cnt) {
  switch (p_actwk->actflg & 3) {
    case 0:
      for (int i = 0; i < spr_cnt; ++i) {
        short new_yposi = p_sprpat->spr[i].yoff + yposi;
        if (new_yposi <= 96 || new_yposi >= 352) {
          continue;
        }
        *((short*)g_pLevelSelectVram) = new_yposi;
        ++g_pLevelSelectVram;
        *((unsigned char*)g_pLevelSelectVram) = p_sprpat->spr[i].etc;
        ++g_pLevelSelectVram;
        *g_pLevelSelectVram = p_sprpat->spr[i].index + p_actwk->sproffset;
        ++g_pLevelSelectVram;
        short new_xposi = p_sprpat->spr[i].xoff + xposi;
        if (new_xposi <= 96 || new_xposi >= 448) {
          g_pLevelSelectVram -= 3;
          continue;
        }
        *((short*)g_pLevelSelectVram) = new_xposi;
        ++g_pLevelSelectVram;
        --spritesleft_cnt;
        if (spritesleft_cnt == 0) break;
      }
      break;
    case 1:
      for (int i = 0; i < spr_cnt; ++i) {
        short new_yposi = p_sprpat->spr[i].yoff + yposi;
        if (new_yposi <= 96 || new_yposi >= 352) {
          continue;
        }
        *((short*)g_pLevelSelectVram) = new_yposi;
        ++g_pLevelSelectVram;
        *((unsigned char*)g_pLevelSelectVram) = p_sprpat->spr[i].etc;
        ++g_pLevelSelectVram;
        *g_pLevelSelectVram = (p_sprpat->spr[i].index + p_actwk->sproffset) ^ 0x800;
        ++g_pLevelSelectVram;
        short new_xposi = -p_sprpat->spr[i].xoff - xshapeoffsets[p_sprpat->spr[i].etc] + xposi;
        if (new_xposi <= 96 || new_xposi >= 448) {
          g_pLevelSelectVram -= 3;
          continue;
        }
        *((short*)g_pLevelSelectVram) = new_xposi;
        ++g_pLevelSelectVram;
        --spritesleft_cnt;
        if (spritesleft_cnt == 0) break;
      }
      break;
    case 3:
      for (int i = 0; i < spr_cnt; ++i) {
        short new_yposi = -p_sprpat->spr[i].yoff - yshapeoffsets[p_sprpat->spr[i].etc] + yposi;
        if (new_yposi <= 96 || new_yposi >= 352) {
          continue;
        }
        *((short*)g_pLevelSelectVram) = new_yposi;
        ++g_pLevelSelectVram;
        *((unsigned char*)g_pLevelSelectVram) = p_sprpat->spr[i].etc;
        ++g_pLevelSelectVram;
        *g_pLevelSelectVram = (p_sprpat->spr[i].index + p_actwk->sproffset) ^ 0x1800;
        ++g_pLevelSelectVram;
        short new_xposi = -p_sprpat->spr[i].xoff - xshapeoffsets[p_sprpat->spr[i].etc] + xposi;
        if (new_xposi <= 96 || new_xposi >= 448) {
          g_pLevelSelectVram -= 3;
          continue;
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
        short new_yposi = -p_sprpat->spr[i].yoff - yshapeoffsets[p_sprpat->spr[i].etc] + yposi;
        if (new_yposi <= 96 || new_yposi >= 352) {
          continue;
        }
        *((short*)g_pLevelSelectVram) = new_yposi;
        g_pLevelSelectVram += 2;
        *g_pLevelSelectVram = (p_sprpat->spr[i].index + p_actwk->sproffset) ^ 0x1000;
        ++g_pLevelSelectVram;
        short new_xposi = p_sprpat->spr[i].xoff + xposi;
        if (new_xposi <= 96 || new_xposi >= 448) {
          g_pLevelSelectVram -= 3;
          continue;
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


// 00420a46
static void patset_vs() {
  // TODO
}


// 00426f24
unsigned long random() {
  unsigned long d1 = g_ram.ranum;
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
  g_ram.ranum = d1;
  return d0;
}


// 00426fde
void sinset(unsigned char angle, short* sin, short* cos) {
  unsigned short angle_w = angle;
  angle_w += 64;
  *cos = sintable[angle_w];
  angle_w -= 64;
  *sin = sintable[angle_w];
}


/* 00427051 */ static short sintable[320] = {
     0,    6,   12,   18,   25,   31,   37,   43,   49,   56,   62,   68,   74,   80,   86,   92,
    97,  103,  109,  115,  120,  126,  131,  136,  142,  147,  152,  157,  162,  167,  171,  176,
   181,  185,  189,  193,  197,  201,  205,  209,  212,  216,  219,  222,  225,  228,  231,  234,
   236,  238,  241,  243,  244,  246,  248,  249,  251,  252,  253,  254,  254,  255,  255,  255,
   256,  255,  255,  255,  254,  254,  253,  252,  251,  249,  248,  246,  244,  243,  241,  238,
   236,  234,  231,  228,  225,  222,  219,  216,  212,  209,  205,  201,  197,  193,  189,  185,
   181,  176,  171,  167,  162,  157,  152,  147,  142,  136,  131,  126,  120,  115,  109,  103,
    97,   92,   86,   80,   74,   68,   62,   56,   49,   43,   37,   31,   25,   18,   12,    6,
     0,   -6,  -12,  -18,  -25,  -31,  -37,  -43,  -49,  -56,  -62,  -68,  -74,  -80,  -86,  -92,
   -97, -103, -109, -117, -120, -126, -131, -136, -142, -147, -152, -157, -162, -167, -171, -176,
  -181, -185, -189, -193, -197, -201, -205, -209, -212, -216, -219, -222, -225, -228, -231, -234,
  -236, -238, -241, -243, -244, -246, -248, -249, -251, -252, -253, -254, -254, -255, -255, -255,
  -256, -255, -255, -255, -254, -254, -253, -252, -251, -249, -248, -246, -244, -243, -241, -238,
  -236, -234, -231, -228, -225, -222, -219, -216, -212, -209, -205, -201, -197, -193, -189, -185,
  -181, -176, -171, -167, -162, -157, -152, -147, -142, -136, -131, -126, -120, -117, -109, -103,
   -97,  -92,  -86,  -80,  -74,  -68,  -62,  -56,  -49,  -43,  -37,  -31,  -25,  -18,  -12,   -6,
     0,    6,   12,   18,   25,   31,   37,   43,   49,   56,   62,   68,   74,   80,   86,   92,
    97,  103,  109,  115,  120,  126,  131,  136,  142,  147,  152,  157,  162,  167,  171,  176,
   181,  185,  189,  193,  197,  201,  205,  209,  212,  216,  219,  222,  225,  228,  231,  234,
   236,  238,  241,  243,  244,  246,  248,  249,  251,  252,  253,  254,  254,  255,  255,  255
};


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
  memcpy(g_pLevelSelectVram, &g_ram.chunkmappings128[0x7000], mapping_cnt * 2);
  g_pLevelSelectVram = (unsigned short*)&g_mdVram[vramoffset + 128];
  memcpy(g_pLevelSelectVram, &g_ram.chunkmappings128[0x7080], mapping_cnt * 2);
}


// 00824b55
static unsigned short FUN_00824b55(unsigned char* p_text, unsigned short coloroffset) {
  unsigned short* p_chunkmappings1 = (unsigned short*)&g_ram.chunkmappings128[0x7000];
  unsigned short* p_chunkmappings2 = (unsigned short*)&g_ram.chunkmappings128[0x7080];
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
