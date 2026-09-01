#include "action.h"
#include <string.h>
#include "types/sonic3ram.h"
#include "types/spritedata.h"
#include "types/spritepattern.h"
#include "types/spriteplacement.h"
#include "types/spritestatus.h"
#include "utils/bits.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "coli.h"
#include "constants.h"
#include "ringact.h"
#include "score.h"
static void sprtblinit(SKC_sprite_data (*p_sprtbl)[SPRITE_COUNT_LIMIT]);
static SKC_sprite_status* action0(SKC_sprite_status* p_actwk, int cnt);
static void vsaction(SKC_sprite_status* p_actwk);
static SKC_sprite_status* vsaction0(SKC_sprite_status* p_actwk, int cnt);
static void patset_compound(SKC_sprite_status* p_actwk, SKC_patset_work* p_work);
static unsigned char xshapeoffsets[16];
static unsigned char yshapeoffsets[16];
static void spatset_compound(SKC_patset_work* p_work, SKC_actflg actflg, unsigned short sproffset);
static void vspatset(void);
static void vspatset_pl_compound(SKC_sprite_status* p_actwk, SKC_patset_work* p_work);
static void vspatset_pl2_compound(SKC_sprite_status* p_actwk, SKC_patset_work* p_work);

extern sonic3_ram g_ram;
extern unsigned long DAT_008547bc;


void sprtblinit2(void) {
  g_ram.sprhmasks = 0;
  g_ram.sprtbl_pageflip = 0;
  g_ram.sprtbl_pageready = 0;
  if (g_ram.vs_flag != 0) {
    sprtblinit(&g_ram.sprtbl);
    sprtblinit(&g_ram.vssprtbl[0]);
    sprtblinit(&g_ram.vssprtbl[1]);
    sprtblinit(&g_ram.vssprtbl[2]);
  }
  else {
    sprtblinit(&g_ram.sprtbl);
  }
}


static void sprtblinit(SKC_sprite_data (*p_sprtbl)[SPRITE_COUNT_LIMIT]) {
  for (int i = 0; i < SPRITE_COUNT_LIMIT; ++i) {
    (*p_sprtbl)[i].vp = 0;
    (*p_sprtbl)[i].next = i + 1;
  }

  (*p_sprtbl)[SPRITE_COUNT_LIMIT - 1].next = 0;
}


void action(void) {
  if (g_ram.teleport != 0) return;

  if (g_ram.vs_flag != 0 || g_ram.actwk[0].r_no == 12 || g_ram.actwk[0].r_no < 6) {
    action0(&g_ram.actwk[0], 110);
  }
  else {
    vsaction(&g_ram.actwk[0]);
  }
}


static SKC_sprite_status* action0(SKC_sprite_status* p_actwk, int cnt) {
  for (int i = 0; i < cnt; ++i) {
    if (p_actwk->r_ptr != 0) {
      p_actwk->r_ptr(p_actwk);
    }
    ++p_actwk;
  }

  return p_actwk;
}


static void vsaction(SKC_sprite_status* p_actwk) {
  p_actwk = action0(p_actwk, 4);
  p_actwk = vsaction0(p_actwk, 90);
  p_actwk = action0(p_actwk, 16);
}


static SKC_sprite_status* vsaction0(SKC_sprite_status* p_actwk, int cnt) {
  for (int i = 0; i < cnt; ++i) {
    if (p_actwk->r_ptr != 0 && p_actwk->actflg.onscreen == 1) {
      actionsub(p_actwk);
    }
    ++p_actwk;
  }

  return p_actwk;
}


short speedset(SKC_sprite_status* p_actwk) {
  short prev_yspeed = p_actwk->yspeed;
  p_actwk->xposi += p_actwk->xspeed * 0x100;
  p_actwk->yposi += p_actwk->yspeed * 0x100;
  p_actwk->yspeed += 0x38;
  return prev_yspeed;
}


void speedset2(SKC_sprite_status* p_actwk) {
  p_actwk->xposi += p_actwk->xspeed * 0x100;
  p_actwk->yposi += p_actwk->yspeed * 0x100;
}


void speedset_g(SKC_sprite_status* p_actwk) {
  if (g_ram.reverse_gravity_flag == 0) {
    speedset(p_actwk);
  }
  else {
    p_actwk->xposi += p_actwk->xspeed * 0x100;
    p_actwk->yposi += -p_actwk->yspeed * 0x100;
    p_actwk->yspeed += 0x38;
  }
}


void speedset2_g(SKC_sprite_status* p_actwk) {
  if (g_ram.reverse_gravity_flag == 0) {
    speedset2(p_actwk);
  }
  else {
    p_actwk->xposi += p_actwk->xspeed * 0x100;
    p_actwk->yposi += -p_actwk->yspeed * 0x100;
  }
}


void frameout(SKC_sprite_status* p_actwk) {
  memset(p_actwk, 0, sizeof(SKC_sprite_status));
}


void actionsub(SKC_sprite_status* p_actwk) {
  for (int i = p_actwk->sprpri / 0x80; i < PBUFFER_LEVELS; ++i) {
    if (g_ram.pbuffer[i][0] < PBUFFER_LEVEL_SLOTS - 1) {
      ++g_ram.pbuffer[i][0];
      g_ram.pbuffer[i][g_ram.pbuffer[i][0]] = p_actwk - g_ram.actwk;
      break;
    }
  }
}


void patchg(SKC_sprite_status* p_actwk, signed char** p_chg_data) {
  if (p_actwk->mstno != p_actwk->mstrestart) {
    p_actwk->mstrestart = p_actwk->mstno;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
  }
  if (p_actwk->pattim-- == 0) {
    signed char* p_data = p_chg_data[p_actwk->mstno];
    p_actwk->pattim = p_data[0];
    signed char patno = p_data[p_actwk->patcnt + 1];
    if (patno < 0) {
      switch (patno) {
        case PATCHG_CONTROL_LOOP:
          p_actwk->patcnt = 0;
          patno = p_data[1];
          break;
        case PATCHG_CONTROL_REWIND:
          p_actwk->patcnt -= p_data[p_actwk->patcnt + 2];
          patno = p_data[p_actwk->patcnt + 1];
          break;
        case PATCHG_CONTROL_NEXT:
          p_actwk->mstno = p_data[p_actwk->patcnt + 2];
          return;
        case PATCHG_CONTROL_ROUTINE:
          p_actwk->r_no += 2;
          p_actwk->pattim = 0;
          ++p_actwk->patcnt;
          return;
        case PATCHG_CONTROL_FOUT:
          fp16_set_integer(&p_actwk->xposi, 0x7F00);
          return;
        default:
          return;
      }
    }
    p_actwk->patno = patno;
    p_actwk->actflg.hflip = p_actwk->u.obj.cddat.right;
    p_actwk->actflg.vflip = p_actwk->u.obj.cddat.down;
    ++p_actwk->patcnt;
  }
}


void time_patchg(SKC_sprite_status* p_actwk, signed char** p_chg_data) {
  if (p_actwk->mstno != p_actwk->mstrestart) {
    p_actwk->mstrestart = p_actwk->mstno;
    p_actwk->patcnt = 0;
    p_actwk->pattim = 0;
  }
  if (p_actwk->pattim-- == 0) {
    signed char* p_data = p_chg_data[p_actwk->mstno];
    signed char patno = p_data[p_actwk->patcnt * 2];
    if (patno < 0) {
      switch (patno) {
        case PATCHG_CONTROL_LOOP:
          p_actwk->patcnt = 0;
          patno = p_data[0];
          break;
        case PATCHG_CONTROL_REWIND:
          p_actwk->patcnt -= p_data[p_actwk->patcnt * 2 + 1];
          patno = p_data[p_actwk->patcnt * 2];
          break;
        case PATCHG_CONTROL_NEXT:
          p_actwk->mstno = p_data[p_actwk->patcnt * 2 + 1];
          return;
        case PATCHG_CONTROL_ROUTINE:
          p_actwk->r_no += 2;
          p_actwk->pattim = 0;
          ++p_actwk->patcnt;
          return;
      }
    }
    p_actwk->pattim = p_data[p_actwk->patcnt * 2 + 1];
    p_actwk->patno = patno;
    p_actwk->actflg.hflip = p_actwk->u.obj.cddat.right;
    p_actwk->actflg.vflip = p_actwk->u.obj.cddat.down;
    ++p_actwk->patcnt;
  }
}


void patset(void) {
  if (g_ram.vs_flag != 0) {
    vspatset();
  }
  else {
    SKC_patset_work work = {
      .sprite_tbl_ptr = g_ram.sprtbl,
      .sprite_left_cnt = SPRITE_COUNT_LIMIT
    };
    if (g_ram.DAT_08fff711 != 0) {
      score(&work);
      ringpatset(&work);
    }
    for (int level = 0; level < PBUFFER_LEVELS; ++level) {
      for (int slot = 1; slot < g_ram.pbuffer[level][0] + 1; ++slot) {
        SKC_sprite_status* p_actwk = &g_ram.actwk[g_ram.pbuffer[level][slot]];
        p_actwk->actflg.onscreen = 0;
        work.xposi = fp16_get_integer(p_actwk->xposi);
        work.yposi = fp16_get_integer(p_actwk->yposi);
        if (p_actwk->actflg.compound == 1) {
          patset_compound(p_actwk, &work);
        }
        else {
          if (p_actwk->actflg.relative_coordinates == 1) {
            work.xposi -= g_ram.scra_h_posit_copy >> 16;
            if (work.xposi + (short)p_actwk->sprhs >= 0 && work.xposi - (short)p_actwk->sprhs < SCREEN_WIDTH_PX) {
              work.xposi += 128;
              work.yposi = work.yposi - (g_ram.scra_v_posit_copy >> 16) + (short)p_actwk->sprvs;
              work.yposi = (unsigned short)work.yposi & g_ram.scrc_v;
              if (work.yposi < (short)p_actwk->sprvs * 2 + SCREEN_HEIGHT_PX) {
                work.yposi = work.yposi + 128 - (short)p_actwk->sprvs;
                p_actwk->actflg.onscreen = 1;
              }
            }
          }
          else {
            p_actwk->actflg.onscreen = 1;
          }
          if (p_actwk->actflg.onscreen == 1 && work.sprite_left_cnt > 0 && p_actwk->patbase != 0) {
            if (p_actwk->actflg.static_pattern == 0) {
              SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
              work.placement_cnt = pp_patterns[p_actwk->patno]->cnt;
              work.placements_ptr = pp_patterns[p_actwk->patno]->spr;
            }
            else {
              work.placement_cnt = 1;
              work.placements_ptr = (SKC_sprite_placement*)p_actwk->patbase;
            }
            if (work.placement_cnt > 0) {
              spatset(&work, p_actwk->actflg, p_actwk->sproffset);
            }
          }
        }
      }
      g_ram.pbuffer[level][0] = 0;
      if (level != 0 && get_zone(g_ram.stageno) == LAVA_REEF) {
        FUN_004487b9();
      }
    }

    for (int i = 0; i < work.sprite_left_cnt; ++i) {
      work.sprite_tbl_ptr[i].vp = 0;
      work.sprite_tbl_ptr[i].vs = 0;
      work.sprite_tbl_ptr[i].hs = 0;
    }

    g_ram.linkdata = SPRITE_COUNT_LIMIT - work.sprite_left_cnt;
    if (g_ram.sprhmasks != 0) {
      if (g_ram.actwk[0].r_no < 6) {
        g_ram.sprhmasks = 0;
      }
      DAT_008547bc = 1;
      SKC_sprite_data* p_sprite_tbl = g_ram.sprtbl;

      for (int i = 0; i < SPRITE_COUNT_LIMIT - 1; ++i) {
        if (p_sprite_tbl->vp == 0x7C0) {
          p_sprite_tbl->vs = 1;
          p_sprite_tbl->hs = 0;
          p_sprite_tbl->next = 0;
          (p_sprite_tbl + 1)->vp = 0;
        }
        ++p_sprite_tbl;
      }
    }
  }
}


static void patset_compound(SKC_sprite_status* p_actwk, SKC_patset_work* p_work) {
  if (p_actwk->actflg.relative_coordinates == 0) {
    p_work->xposi -= 128;
    if (p_work->xposi + (short)p_actwk->sprhs >= 0 && p_work->xposi - (short)p_actwk->sprhs < SCREEN_WIDTH_PX) {
      p_work->xposi += 128;
      p_work->yposi -= 128;
      if (p_work->yposi + (short)p_actwk->sprvs >= 0 && p_work->yposi - (short)p_actwk->sprvs < SCREEN_HEIGHT_PX) {
        p_work->yposi += 128;
        p_actwk->actflg.onscreen = 1;
      }
    }
  }
  else {
    p_work->xposi -= g_ram.scra_h_posit_copy >> 16;
    if (p_work->xposi + (short)p_actwk->sprhs >= 0 && p_work->xposi - (short)p_actwk->sprhs < SCREEN_WIDTH_PX) {
      p_work->xposi += 128;
      p_work->yposi = p_work->yposi - (g_ram.scra_v_posit_copy >> 16) + (short)p_actwk->sprvs;
      p_work->yposi = (unsigned short)p_work->yposi & g_ram.scrc_v;
      if (p_work->yposi < (short)p_actwk->sprvs * 2 + SCREEN_HEIGHT_PX) {
        p_work->yposi = p_work->yposi + 128 - (short)p_actwk->sprvs;
        p_actwk->actflg.onscreen = 1;
      }
    }
  }
  if (p_actwk->actflg.onscreen == 1 && p_work->sprite_left_cnt > 0) {
    if (p_actwk->patno != 0) {
      SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
      SKC_sprite_pattern* p_patterns = pp_patterns[p_actwk->patno];
      if (p_patterns->cnt > 0) {
        p_work->placement_cnt = p_patterns->cnt;
        p_work->placements_ptr = p_patterns->spr;
        spatset_compound(p_work, p_actwk->actflg, p_actwk->sproffset);
      }
    }
    if (p_work->sprite_left_cnt > 0) {
      for (int i = 0; i < p_actwk->u.obj.compound.child_cnt; ++i) {
        p_work->xposi = p_actwk->u.obj.compound.children[i].xposi;
        p_work->yposi = p_actwk->u.obj.compound.children[i].yposi;
        if (p_actwk->actflg.relative_coordinates == 1) {
          p_work->xposi -= (g_ram.scra_h_posit_copy >> 16) + 128;
          p_work->yposi = p_work->yposi - (g_ram.scra_v_posit_copy >> 16) + 128;
          p_work->yposi = (unsigned short)p_work->yposi & g_ram.scrc_v;
        }
        SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
        SKC_sprite_pattern* p_patterns = pp_patterns[p_actwk->u.obj.compound.children[i].patno];
        if (p_patterns->cnt > 0) {
          p_work->placement_cnt = p_patterns->cnt;
          p_work->placements_ptr = p_patterns->spr;
          spatset_compound(p_work, p_actwk->actflg, p_actwk->sproffset);
          if (p_work->sprite_left_cnt == 0) break;
        }
      }
    }
  }
}


void spatset(SKC_patset_work* p_work, SKC_actflg actflg, unsigned short sproffset) {
  for (int i = 0; i < p_work->placement_cnt; ++i) {
    SKC_sprite_data* p_data = p_work->sprite_tbl_ptr;
    SKC_sprite_placement placement = p_work->placements_ptr[i];
    unsigned char yshapeoffset = yshapeoffsets[placement.etc] * actflg.vflip;
    unsigned char xshapeoffset = xshapeoffsets[placement.etc] * actflg.hflip;
    p_data->vp = placement.yoff * (!(short)actflg.vflip * 2 - 1) - yshapeoffset + p_work->yposi;
    p_data->vs = placement.etc & 3;
    p_data->hs = (placement.etc & 0xC) >> 2;
    unsigned short wk = placement.index + sproffset;
    p_data->gfx = wk & 0x7FF;
    p_data->hf = actflg.hflip == 0 ? !!(wk & 0x800) : !!(wk ^ 0x800);
    p_data->vf = actflg.vflip == 0 ? !!(wk & 0x1000) : !!(wk ^ 0x1000);
    p_data->pl = (wk & 0x6000) >> 13;
    p_data->pr = !!(wk & 0x8000);
    p_data->hp = (placement.xoff * (!(short)actflg.hflip * 2 - 1) - xshapeoffset + p_work->xposi) & 0x1FF;
    if (p_data->hp == 0) {
      ++p_data->hp;
    }
    ++p_work->sprite_tbl_ptr;
    --p_work->sprite_left_cnt;
    if (p_work->sprite_left_cnt == 0) break;
  }
}


static unsigned char xshapeoffsets[16] = { 8, 8, 8, 8, 16, 16, 16, 16, 24, 24, 24, 24, 32, 32, 32, 32 };


static unsigned char yshapeoffsets[16] = { 8, 16, 24, 32, 8, 16, 24, 32, 8, 16, 24, 32, 8, 16, 24, 32 };


static void spatset_compound(SKC_patset_work* p_work, SKC_actflg actflg, unsigned short sproffset) {
  for (int i = 0; i < p_work->placement_cnt; ++i) {
    SKC_sprite_data* p_data = p_work->sprite_tbl_ptr;
    SKC_sprite_placement placement = p_work->placements_ptr[i];
    unsigned char yshapeoffset = yshapeoffsets[placement.etc] * actflg.vflip;
    unsigned char xshapeoffset = xshapeoffsets[placement.etc] * actflg.hflip;
    short yposi = placement.yoff * (!(short)actflg.vflip * 2 - 1) - yshapeoffset + p_work->yposi;
    short xposi = placement.xoff * (!(short)actflg.hflip * 2 - 1) - xshapeoffset + p_work->xposi;
    if (yposi > 96 && yposi < 352 && xposi > 96 && xposi < 448) {
      p_data->vp = yposi;
      p_data->vs = placement.etc & 3;
      p_data->hs = (placement.etc & 0xC) >> 2;
      unsigned short wk = placement.index + sproffset;
      p_data->gfx = wk & 0x7FF;
      p_data->hf = actflg.hflip == 0 ? !!(wk & 0x800) : !!(wk ^ 0x800);
      p_data->vf = actflg.vflip == 0 ? !!(wk & 0x1000) : !!(wk ^ 0x1000);
      p_data->pl = (wk & 0x6000) >> 13;
      p_data->pr = !!(wk & 0x8000);
      p_data->hp = xposi;
      ++p_work->sprite_tbl_ptr;
      --p_work->sprite_left_cnt;
      if (p_work->sprite_left_cnt == 0) break;
    }
  }
}


static void vspatset(void) {
  SKC_patset_work work = {
    .sprite_tbl_ptr = &g_ram.sprtbl[2],
    .sprite_left_cnt = SPRITE_COUNT_LIMIT - 2
  };
  if (g_ram.sprtbl_pageflip != 0) {
    work.sprite_tbl_ptr = &g_ram.vssprtbl[0][2];
  }
  if (g_ram.DAT_08fff711 != 0) {
    vsscore(&work);
  }

  for (int level = 0; level < PBUFFER_LEVELS; ++level) {
    for (int slot = 1; slot < g_ram.pbuffer[level][0] + 1; ++slot) {
      SKC_sprite_status* p_actwk = &g_ram.actwk[g_ram.pbuffer[level][slot]];
      p_actwk->actflg.onscreen = 0;
      if (p_actwk->actflg.vspl2 == 0) {
        work.xposi = fp16_get_integer(p_actwk->xposi);
        work.yposi = fp16_get_integer(p_actwk->yposi);
        if (p_actwk->actflg.compound == 1) {
          vspatset_pl_compound(p_actwk, &work);
        }
        else {
          if (p_actwk->actflg.relative_coordinates == 1) {
            work.xposi = work.xposi - (g_ram.scra_h_posit_copy >> 16) + (short)p_actwk->sprhs;
            work.xposi = (unsigned short)work.xposi & g_ram.scrc3;
            if (work.xposi < (short)p_actwk->sprhs * 2 + SCREEN_WIDTH_PX) {
              work.xposi = work.xposi + 128 - (short)p_actwk->sprhs;
              work.yposi = work.yposi - (g_ram.scra_v_posit_copy >> 16) + (short)p_actwk->sprvs;
              work.yposi = (unsigned short)work.yposi & g_ram.scrc_v;
              if (work.yposi < (short)p_actwk->sprvs * 2 + SCREEN_HEIGHT_PX / 2) {
                work.yposi = work.yposi + 128 - (short)p_actwk->sprvs;
                p_actwk->actflg.onscreen = 1;
              }
            }
          }
          else {
            p_actwk->actflg.onscreen = 1;
          }
          if (p_actwk->actflg.onscreen == 1 && work.sprite_left_cnt > 0 && p_actwk->patbase != 0) {
            if (p_actwk->actflg.static_pattern == 0) {
              SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
              work.placement_cnt = pp_patterns[p_actwk->patno]->cnt;
              work.placements_ptr = pp_patterns[p_actwk->patno]->spr;
            }
            else {
              work.placement_cnt = 1;
              work.placements_ptr = (SKC_sprite_placement*)p_actwk->patbase;
            }
            if (work.placement_cnt > 0) {
              spatset(&work, p_actwk->actflg, p_actwk->sproffset);
            }
          }
        }
      }
    }
    g_ram.pbuffer[level][0] = 0;
  }
  memset(work.sprite_tbl_ptr, 0, work.sprite_left_cnt * sizeof(SKC_sprite_data));
  if (g_ram.pbuffer[2][1] == 1 && g_ram.pbuffer[2][2] == 0) {
    g_ram.pbuffer[2][1] = 0;
    g_ram.pbuffer[2][2] = 1;
  }
  work.sprite_tbl_ptr = &g_ram.vssprtbl[1][0];
  work.sprite_left_cnt = SPRITE_COUNT_LIMIT;
  if (g_ram.sprtbl_pageflip != 0) {
    work.sprite_tbl_ptr = &g_ram.vssprtbl[2][0];
  }

  for (int level = 0; level < PBUFFER_LEVELS; ++level) {
    for (int slot = 1; slot < g_ram.pbuffer[level][0] + 1; ++slot) {
      SKC_sprite_status* p_actwk = &g_ram.actwk[g_ram.pbuffer[level][slot]];
      if (p_actwk->actflg.vspl == 0) {
        work.xposi = fp16_get_integer(p_actwk->xposi);
        work.yposi = fp16_get_integer(p_actwk->yposi);
        if (p_actwk->actflg.compound == 1) {
          vspatset_pl2_compound(p_actwk, &work);
        }
        else {
          if (p_actwk->actflg.relative_coordinates == 1) {
            work.xposi = work.xposi - (g_ram.vs_scra_h_posit_copy >> 16) + (short)p_actwk->sprhs;
            work.xposi = (unsigned short)work.xposi & g_ram.scrc3;
            if (work.xposi < (short)p_actwk->sprhs * 2 + SCREEN_WIDTH_PX) {
              work.xposi = work.xposi + 128 - (short)p_actwk->sprhs;
              work.yposi = work.yposi - (g_ram.vs_scra_v_posit_copy >> 16) + (short)p_actwk->sprvs;
              work.yposi = (unsigned short)work.yposi & g_ram.scrc_v;
              if (work.yposi < (short)p_actwk->sprvs * 2 + SCREEN_HEIGHT_PX / 2) {
                work.yposi = work.yposi + 128 - (short)p_actwk->sprvs;
                p_actwk->actflg.onscreen = 1;
              }
            }
          }
          else {
            p_actwk->actflg.onscreen = 1;
          }
          if (p_actwk->actflg.onscreen == 1 && work.sprite_left_cnt > 0 && p_actwk->patbase != 0) {
            if (p_actwk->actflg.static_pattern == 0) {
              SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
              work.placement_cnt = pp_patterns[p_actwk->patno]->cnt;
              work.placements_ptr = pp_patterns[p_actwk->patno]->spr;
            }
            else {
              work.placement_cnt = 1;
              work.placements_ptr = (SKC_sprite_placement*)p_actwk->patbase;
            }
            if (work.placement_cnt > 0) {
              spatset(&work, p_actwk->actflg, p_actwk->sproffset);
            }
          }
        }
      }
    }
    g_ram.pbuffer[level][0] = 0;
  }
  memset(work.sprite_tbl_ptr, 0, work.sprite_left_cnt * sizeof(SKC_sprite_data));
  g_ram.sprtbl_pageready = 0xFF;
}


static void vspatset_pl_compound(SKC_sprite_status* p_actwk, SKC_patset_work* p_work) {
  p_work->xposi = p_work->xposi - (g_ram.scra_h_posit_copy >> 16) + (short)p_actwk->sprhs;
  p_work->xposi = (unsigned short)p_work->xposi & g_ram.scrc3;
  if (p_work->xposi < (short)p_actwk->sprhs * 2 + SCREEN_WIDTH_PX) {
    p_work->xposi = p_work->xposi + 128 - (short)p_actwk->sprhs;
    p_work->yposi = p_work->yposi - (g_ram.scra_v_posit_copy >> 16) + (short)p_actwk->sprvs;
    p_work->yposi = (unsigned short)p_work->yposi & g_ram.scrc_v;
    if (p_work->yposi < (short)p_actwk->sprvs * 2 + SCREEN_HEIGHT_PX / 2) {
      p_work->yposi = p_work->yposi + 128 - (short)p_actwk->sprvs;
      p_actwk->actflg.onscreen = 1;
    }
  }
  if (p_actwk->actflg.onscreen == 1 && p_work->sprite_left_cnt > 0) {
    if (p_actwk->patno != 0) {
      SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
      SKC_sprite_pattern* p_patterns = pp_patterns[p_actwk->patno];
      if (p_patterns->cnt > 0) {
        p_work->placement_cnt = p_patterns->cnt;
        p_work->placements_ptr = p_patterns->spr;
        spatset_compound(p_work, p_actwk->actflg, p_actwk->sproffset);
      }
    }
    if (p_work->sprite_left_cnt > 0) {
      for (int i = 0; i < p_actwk->u.obj.compound.child_cnt; ++i) {
        p_work->xposi = p_actwk->u.obj.compound.children[i].xposi;
        p_work->xposi = p_work->xposi - (g_ram.scra_h_posit_copy >> 16) + 128;
        p_work->xposi = (unsigned short)p_work->xposi & g_ram.scrc3;
        p_work->yposi = p_actwk->u.obj.compound.children[i].yposi;
        p_work->yposi = p_work->yposi - (g_ram.scra_v_posit_copy >> 16) + 128;
        p_work->yposi = (unsigned short)p_work->yposi & g_ram.scrc_v;
        SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
        SKC_sprite_pattern* p_patterns = pp_patterns[p_actwk->u.obj.compound.children[i].patno];
        if (p_patterns->cnt > 0) {
          p_work->placement_cnt = p_patterns->cnt;
          p_work->placements_ptr = p_patterns->spr;
          spatset_compound(p_work, p_actwk->actflg, p_actwk->sproffset);
          if (p_work->sprite_left_cnt == 0) break;
        }
      }
    }
  }
}


static void vspatset_pl2_compound(SKC_sprite_status* p_actwk, SKC_patset_work* p_work) {
  p_work->xposi = p_work->xposi - (g_ram.vs_scra_h_posit_copy >> 16) + (short)p_actwk->sprhs;
  p_work->xposi = (unsigned short)p_work->xposi & g_ram.scrc3;
  if (p_work->xposi < (short)p_actwk->sprhs * 2 + SCREEN_WIDTH_PX) {
    p_work->xposi = p_work->xposi + 128 - (short)p_actwk->sprhs;
    p_work->yposi = p_work->yposi - (g_ram.vs_scra_v_posit_copy >> 16) + (short)p_actwk->sprvs;
    p_work->yposi = (unsigned short)p_work->yposi & g_ram.scrc_v;
    if (p_work->yposi < (short)p_actwk->sprvs * 2 + SCREEN_HEIGHT_PX / 2) {
      p_work->yposi = p_work->yposi + 128 + SCREEN_HEIGHT_PX / 2 - (short)p_actwk->sprvs;
      p_actwk->actflg.onscreen = 1;
    }
  }
  if (p_actwk->actflg.onscreen == 1 && p_work->sprite_left_cnt > 0) {
    if (p_actwk->patno != 0) {
      SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
      SKC_sprite_pattern* p_patterns = pp_patterns[p_actwk->patno];
      if (p_patterns->cnt > 0) {
        p_work->placement_cnt = p_patterns->cnt;
        p_work->placements_ptr = p_patterns->spr;
        spatset_compound(p_work, p_actwk->actflg, p_actwk->sproffset);
      }
    }
    if (p_work->sprite_left_cnt > 0) {
      for (int i = 0; i < p_actwk->u.obj.compound.child_cnt; ++i) {
        p_work->xposi = p_actwk->u.obj.compound.children[i].xposi;
        p_work->xposi = p_work->xposi - (g_ram.vs_scra_h_posit_copy >> 16) + 128;
        p_work->xposi = (unsigned short)p_work->xposi & g_ram.scrc3;
        p_work->yposi = p_actwk->u.obj.compound.children[i].yposi;
        p_work->yposi = p_work->yposi - (g_ram.vs_scra_v_posit_copy >> 16) + 128;
        p_work->yposi = (unsigned short)p_work->yposi & g_ram.scrc_v;
        p_work->yposi += SCREEN_HEIGHT_PX / 2;
        SKC_sprite_pattern** pp_patterns = (SKC_sprite_pattern**)p_actwk->patbase;
        SKC_sprite_pattern* p_patterns = pp_patterns[p_actwk->u.obj.compound.children[i].patno];
        if (p_patterns->cnt > 0) {
          p_work->placement_cnt = p_patterns->cnt;
          p_work->placements_ptr = p_patterns->spr;
          spatset_compound(p_work, p_actwk->actflg, p_actwk->sproffset);
          if (p_work->sprite_left_cnt == 0) break;
        }
      }
    }
  }
}


void frameoutchk(SKC_sprite_status* p_actwk) {
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.sc1ahposit;
  if ((unsigned short)chunk_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


void frameoutchk2(SKC_sprite_status* p_actwk, short xposi) {
  short chunk_xposi = xposi - xposi % 128 - g_ram.sc1ahposit;
  if ((unsigned short)chunk_xposi <= 640) {
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


void frameoutchk3(SKC_sprite_status* p_actwk) {
  short chunk_xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_actwk->xposi) % 128 - g_ram.sc1ahposit;
  if ((unsigned short) chunk_xposi > 640) {
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}


void frameoutchkc(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  frameoutchkc0(p_actwk, xposi);
}


void frameoutchkc0(SKC_sprite_status* p_actwk, short xposi) {
  short chunk_xposi = xposi - xposi % 128 - g_ram.sc1ahposit;
  if ((unsigned short)chunk_xposi <= 640) {
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    }
    frameout(p_actwk);
  }
}
