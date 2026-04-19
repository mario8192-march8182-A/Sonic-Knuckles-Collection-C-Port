#include "ringact.h"
#include <stdbool.h>
#include <string.h>
#include "data/ringacttbl.h"
#include "types/patsetwork.h"
#include "types/point.h"
#include "types/ringwkentry.h"
#include "types/sonic3ram.h"
#include "types/spritedata.h"
#include "types/spritestatus.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "actset.h"
#include "constants.h"
#include "objects/ring.h"
static void ringactsetinit(void);
static void ringactset(void);
static void ringbufferchk(void);
static void ringactset2(void);
static void coli_xchk(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry, short xposi, short yposi, short sprhs, short sprvs);
static void coli_ychk(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry, short xposi, short yposi, short sprhs, short sprvs);
static void coli_hit_chk(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry);
static void ringcolplay(void);
static void ringcoltbaria(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry);
static void ringactinit2(void);

extern sonic3_ram g_ram;
extern bool g_sonic3_alone;


void ringactsetchk(void) {
  void(*act_tbl[3])(void) = {
    &ringactsetinit,
    &ringactset,
    &ringactset2
  };

  act_tbl[g_ram.ringactset_rno / 2]();
}


static void ringactsetinit(void) {
  g_ram.ringactset_rno += 2;
  ringactinit2();
  if (get_zone(g_ram.stageno) != ROLLING_JUMP) {
    g_ram.ringwkadr = g_ram.ringwk;
    short xposi = (g_ram.scra_h_posit >> 16) - 8;
    if (xposi <= 0) {
      xposi = 1;
    }

    while (xposi > g_ram.ringactadr->x) {
      ++g_ram.ringactadr;
      ++g_ram.ringwkadr;
    }

    g_ram.ringactadr2 = g_ram.ringactadr;
    xposi += 336;

    while (xposi > g_ram.ringactadr2->x) {
      ++g_ram.ringactadr2;
    }
  }
  else {
    g_ram.ringactset_rno += 2;
    g_ram.ringwkadr = &g_ram.ringwk[RINGWK_ROLLING_JUMP_START];
    short yposi = (g_ram.scra_v_posit >> 16) - 8;
    if (yposi <= 0) {
      yposi = 1;
    }

    while (yposi > g_ram.ringactadr->y) {
      ++g_ram.ringactadr;
      ++g_ram.ringwkadr;
    }

    g_ram.ringactadr2 = g_ram.ringactadr;
    yposi += 240;

    while (yposi > g_ram.ringactadr2->y) {
      ++g_ram.ringactadr2;
    }
  }
}


static void ringactset(void) {
  ringbufferchk();
  short xposi = (g_ram.scra_h_posit >> 16) - 8;
  if (xposi <= 0) {
    xposi = 1;
  }

  while (xposi > g_ram.ringactadr->x) {
    ++g_ram.ringactadr;
    ++g_ram.ringwkadr;
  }

  while (xposi <= (g_ram.ringactadr - 1)->x) {
    --g_ram.ringactadr;
    --g_ram.ringwkadr;
  }

  xposi += 336;

  while (xposi > g_ram.ringactadr2->x) {
    ++g_ram.ringactadr2;
  }

  while (xposi <= (g_ram.ringactadr2 - 1)->x) {
    --g_ram.ringactadr2;
  }
}


static void ringbufferchk(void) {
  unsigned short* p_ringbuffer = &g_ram.ringbuffer[1];
  unsigned short cnt = g_ram.ringbuffer[0];

  while (cnt > 0) {
    if (*p_ringbuffer != 0) {
      SKC_ringwk_entry* p_entry = &g_ram.ringwk[*p_ringbuffer];
      --p_entry->pattim;
      if (p_entry->pattim == 0) {
        p_entry->pattim = 6;
        ++p_entry->patno;
        if (p_entry->patno == 8) {
          p_entry->pattim = -1;
          p_entry->patno = -1;
          *p_ringbuffer = 0;
          --g_ram.ringbuffer[0];
        }
      }
      --cnt;
    }
  }
}


static void ringactset2(void) {
  ringbufferchk();
  short yposi = (g_ram.scra_v_posit >> 16) - 8;
  if (yposi <= 0) {
    yposi = 1;
  }

  while (yposi > g_ram.ringactadr->y) {
    ++g_ram.ringactadr;
    ++g_ram.ringwkadr;
  }

  while (yposi <= (g_ram.ringactadr - 1)->y) {
    --g_ram.ringactadr;
    --g_ram.ringwkadr;
  }

  yposi += 240;

  while (yposi > g_ram.ringactadr2->y) {
    ++g_ram.ringactadr2;
  }

  while (yposi <= (g_ram.ringactadr2 - 1)->y) {
    --g_ram.ringactadr2;
  }
}


void ringcol(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.invulnerability_timer >= 90) return;
  if (g_ram.ringactadr == g_ram.ringactadr2) return;

  short xposi = fp16_get_integer(p_playerwk->xposi) - (p_playerwk->u.play.powerdat.thunder_baria == 1 ? 64 : 8);
  short sprvs = p_playerwk->u.play.powerdat.thunder_baria == 1 ? 64 : p_playerwk->sprvsize - 3;
  short yposi = fp16_get_integer(p_playerwk->yposi) - (p_playerwk->u.play.powerdat.thunder_baria == 1 ? 64 : sprvs);
  short sprhs = p_playerwk->u.play.powerdat.thunder_baria == 1 ? 128 : 16;
  sprvs *= 2;
  int cnt = g_ram.ringactadr2 - g_ram.ringactadr;

  for (int i = 0; i < cnt; ++i) {
    if (g_ram.ringwkadr[i].pattim == 0 && g_ram.ringwkadr[i].patno == 0) {
      coli_xchk(p_playerwk, &g_ram.ringwkadr[i], xposi, yposi, sprhs, sprvs);
    }
  }
  while (g_ram.ringactadr != g_ram.ringactadr2);

}


static void coli_xchk(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry, short xposi, short yposi, short sprhs, short sprvs) {
  long wk = g_ram.ringactadr->x - 6 - xposi;
  if (wk < 0) {
    wk += 12;
    if (wk > 0xFFFF) {
      coli_ychk(p_playerwk, p_entry, xposi, yposi, sprhs, sprvs);
    }
  }
  else if (wk <= sprhs) {
    coli_ychk(p_playerwk, p_entry, xposi, yposi, sprhs, sprvs);
  }
}


static void coli_ychk(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry, short xposi, short yposi, short sprhs, short sprvs) {
  long wk = g_ram.ringactadr->y - 6 - yposi;
  if (wk < 0) {
    wk += 12;
    if (wk > 0xFFFF) {
      coli_hit_chk(p_playerwk, p_entry);
    }
  }
  else if (wk <= sprvs) {
    coli_hit_chk(p_playerwk, p_entry);
  }
}


static void coli_hit_chk(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry) {
  if (p_playerwk->u.play.powerdat.thunder_baria == 1) {
    ringcoltbaria(p_playerwk, p_entry);
  }
  if (p_entry->pattim == 0 && p_entry->patno == 0) {
    p_entry->pattim = 6;
    p_entry->patno = 4;
    ringcolplay();
    unsigned short* p_ringbuffer = &g_ram.ringbuffer[1];

    while (*p_ringbuffer != 0) {
      ++p_ringbuffer;
    }

    *p_ringbuffer = p_entry - g_ram.ringwk + 1;
    ++g_ram.ringbuffer[0];
  }
}


static void ringcolplay(void) {
  --g_ram.actring;
  ringgetsub();
}


static void ringcoltbaria(SKC_sprite_status* p_playerwk, SKC_ringwk_entry* p_entry) {
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &tring;
    fp16_set_integer(&result.actwk_ptr->xposi, g_ram.ringactadr->x);
    fp16_set_integer(&result.actwk_ptr->yposi, g_ram.ringactadr->y);
    result.actwk_ptr->u.obj.actfree.tring.ringwk_index = p_entry - g_ram.ringwk + 1;
    p_entry->pattim = -1;
    p_entry->patno = -1;
  }
}


static void ringactinit2(void) {
  if (g_ram.plresetflag == 0) {
    memset(g_ram.ringwk, 0, sizeof(g_ram.ringwk));
  }
  memset(g_ram.ringbuffer, 0, sizeof(g_ram.ringbuffer));
  SKC_point* (*p_ringacttbl)[24][2] = !g_sonic3_alone ? &ringacttbl : &ringacttbl_3;
  g_ram.ringactadr = (*p_ringacttbl)[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
  unsigned short ring_cnt = 0;

  for ( ; ring_cnt < RINGWK_ROLLING_JUMP_START - 1; ++ring_cnt) {
    if (g_ram.ringactadr[ring_cnt + 1].x == -1 && g_ram.ringactadr[ring_cnt + 1].y == -1) break;
  }

  g_ram.actring = ring_cnt;
  g_ram.DAT_08ffff06 = 0;
}


void ringpatset(SKC_patset_work* p_work) {
  struct {
    short yoff;
    unsigned short etc;
    unsigned short index;
    short xoff;
  }
  pat[8] = {
    { -8, 5, 0x26BC, -8 },
    { -8, 5, 0x26C0, -8 },
    { -8, 1, 0x26C4, -4 },
    { -8, 5, 0x2EC0, -8 },
    { -8, 5, 0x26C6, -8 },
    { -8, 5, 0x3EC6, -8 },
    { -8, 5, 0x2EC6, -8 },
    { -8, 5, 0x36C6, -8 }
  };

  int cnt = g_ram.ringactadr2 - g_ram.ringactadr;

  for (int i = 0; i < cnt; ++i) {
    if (g_ram.ringwkadr[i].pattim != -1 && g_ram.ringwkadr[i].patno != -1) {
      short yposi = g_ram.ringactadr[i].y - (g_ram.scra_v_posit_copy >> 16) + 8 & g_ram.scrc_v;
      if (yposi < 240) {
        yposi += 120;
        short xposi = g_ram.ringactadr[i].x - (g_ram.scra_h_posit_copy >> 16) + 128;
        unsigned char patno = g_ram.ringwkadr[i].patno;
        if (patno == 0) {
          patno = g_ram.ring_patno;
        }
        SKC_sprite_data* p_data = p_work->sprite_tbl_ptr;
        p_data->vp = yposi + pat[patno].yoff;
        p_data->vs = pat[patno].etc & 3;
        p_data->hs = (pat[patno].etc & 0xC) >> 2;
        p_data->gfx = pat[patno].index & 0x7FF;
        p_data->hf = !!(pat[patno].index & 0x800);
        p_data->vf = !!(pat[patno].index & 0x1000);
        p_data->pl = (pat[patno].index & 0x6000) >> 13;
        p_data->pr = !!(pat[patno].index & 0x8000);
        p_data->hp = xposi + pat[patno].xoff;
        ++p_work->sprite_tbl_ptr;
        --p_work->sprite_left_cnt;
      }
    }
  }
}
