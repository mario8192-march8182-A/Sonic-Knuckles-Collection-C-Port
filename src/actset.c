#include "actset.h"
#include <stdbool.h>
#include <string.h>
#include "data/acttbl.h"
#include "data/asettbl.h"
#include "types/aset.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "utils/bits.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "constants.h"
static void actset_worknai(void);
static void actsetinit(void);
static void actset(void);
static void actset2(void);
static void actnoset_min(SKC_sprite_status* p_actwk, SKC_aset* p_aset);
static void actnoset_ywrap(SKC_sprite_status* p_actwk, SKC_aset* p_aset, unsigned char* p_flagwork, short scra_v_up, short scra_v_down);
static void actnoset(SKC_sprite_status* p_actwk, SKC_aset* p_aset, unsigned char* p_flagwork, short scra_v_up, short scra_v_down);

extern sonic3_ram g_ram;
extern bool g_sonic3_alone;


void actsetchk(void) {
  void(*act_tbl[3])(void) = {
    &actsetinit,
    &actset,
    &actset_worknai
  };

  act_tbl[g_ram.actset_rno / 4]();
}


static void actset_worknai(void) {
}


static void actsetinit(void) {
  if (get_zone(g_ram.stageno) < LAVA_REEF_BOSS_AND_HIDDEN_PALACE
      && (get_zone(g_ram.stageno) >= AZURE_LAKE || get_zone(g_ram.stageno) < MUSHROOM_HILL)) {
    g_ram.act_tbl_ptr = s3_act_tbl;
  }
  else {
    g_ram.act_tbl_ptr = sk_act_tbl;
  }
  g_ram.actset_rno += 4;
  if (g_ram.plresetflag == 0) {
    memset(g_ram.flagwork, 0, sizeof(g_ram.flagwork));
  }
  SKC_aset* (*p_asettbl)[24][2] = !g_sonic3_alone ? &asettbl : &asettbl_3;
  SKC_aset* p_aset = (*p_asettbl)[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
  if (g_ram.stageno == MASTER_EMERALD_SHRINE
      || (get_zone(g_ram.stageno) < LAVA_REEF_BOSS_AND_HIDDEN_PALACE
          && get_zone(g_ram.stageno) != ROLLING_JUMP
          && (get_zone(g_ram.stageno) >= GUMBALL_MACHINE || g_ram.vs_flag != 0))) {
    g_ram.actset_rno += 4;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      unsigned short scra_h = g_ram.stageno != MASTER_EMERALD_SHRINE ? 0x800 : 0x1780;
      while (scra_h > p_aset->x) {
        actnoset_min(result.actwk_ptr, p_aset);
        ++p_aset;
        result = actwkchk_next(result);
        if (result.actwk_ptr == 0) break;
      }
    }
    if (g_ram.stageno != MASTER_EMERALD_SHRINE) {
      g_ram.scr_x_no = 0;
    }
    else {
      short wk = (g_ram.scra_h_posit >> 16) - 128;
      g_ram.scr_x_no = wk - wk % 128;
    }
  }
  else {
    g_ram.asetadr = p_aset;
    g_ram.asetadr2 = p_aset;
    unsigned char* p_flagwork = g_ram.flagwork;
    if (get_zone(g_ram.stageno) == ROLLING_JUMP) {
      p_flagwork = &g_ram.flagwork[FLAGWORK_ROLLING_JUMP_START];
      memset(p_flagwork, 0, FLAGWORK_ROLLING_JUMP_SLOTS);
    }
    short scra_h = (g_ram.scra_h_posit >> 16) - 128;
    if (scra_h < 0) {
      scra_h = 0;
    }
    scra_h &= 0xFF80;
    while (scra_h > g_ram.asetadr->x) {
      ++g_ram.asetadr;
      ++p_flagwork;
    }
    g_ram.flagworkcnt = p_flagwork - g_ram.flagwork;
    p_flagwork = get_zone(g_ram.stageno) != ROLLING_JUMP ? g_ram.flagwork : &g_ram.flagwork[FLAGWORK_ROLLING_JUMP_START];
    scra_h -= 128;
    if (scra_h >= 0) {
      while (scra_h > g_ram.asetadr2->x) {
        ++g_ram.asetadr2;
        ++p_flagwork;
      }
    }
    g_ram.flagworkcnt2 = p_flagwork - g_ram.flagwork;
    g_ram.asetposi = -1;
    g_ram.asetposi2 = g_ram.scra_v_posit >> 16 & 0xFF80;
    actset();
  }
}


static void actset(void) {
  short wk = (g_ram.scra_v_posit >> 16) - 128;
  g_ram.scr_y_no = wk - wk % 128;
  wk = (g_ram.scra_h_posit >> 16) - 128;
  g_ram.scr_x_no = wk - wk % 128;
  short scra_v_up = g_ram.scra_v_posit >> 16 & 0xFF80;
  short scra_v_down = (g_ram.scra_v_posit >> 16 & 0xFF80) + 512;
  void(*p_actnoset)(SKC_sprite_status*, SKC_aset*, unsigned char*, short, short);
  if (g_ram.scralim_up < 0) {
    scra_v_up -= 128;
    if (scra_v_up < 0) {
      scra_v_up = (unsigned short)scra_v_up & g_ram.scrc_v;
    }
    else if (scra_v_down > (short)g_ram.scrc_v + 1) {
      scra_v_down &= g_ram.scrc_v;
    }
    p_actnoset = &actnoset_ywrap;
  }
  else {
    scra_v_up -= 128;
    if (scra_v_up < 0) {
      scra_v_up = 0;
    }
    p_actnoset = &actnoset;
  }
  short scra_h = g_ram.scra_h_posit >> 16 & 0xFF80;
  if (scra_h != g_ram.asetposi) {
    if (scra_h < g_ram.asetposi) {
      g_ram.asetposi = scra_h;
      unsigned char* p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt2];
      scra_h -= 128;
      if (scra_h >= 0) {
        SKC_actwkchk_result result = actwkchk();
        if (result.actwk_ptr != 0) {
          while (scra_h < (g_ram.asetadr2 - 1)->x) {
            --g_ram.asetadr2;
            --p_flagwork;
            p_actnoset(result.actwk_ptr, g_ram.asetadr2, p_flagwork, scra_v_up, scra_v_down);
            result = actwkchk_next(result);
            if (result.actwk_ptr == 0) {
              g_ram.asetadr2 += 2;
              ++p_flagwork;
              break;
            }
          }
        }
      }
      g_ram.flagworkcnt2 = p_flagwork - g_ram.flagwork;
      p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt];
      scra_h += 768;
      while (scra_h <= (g_ram.asetadr2 - 1)->x) {
        --g_ram.asetadr;
        --p_flagwork;
      }
      g_ram.flagworkcnt = p_flagwork - g_ram.flagwork;
    }
    else {
      g_ram.asetposi = scra_h;
      unsigned char* p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt];
      scra_h += 640;
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        while (scra_h > g_ram.asetadr->x) {
          p_actnoset(result.actwk_ptr, g_ram.asetadr2, p_flagwork, scra_v_up, scra_v_down);
          ++g_ram.asetadr2;
          ++p_flagwork;
          result = actwkchk_next(result);
          if (result.actwk_ptr == 0) break;
        }
      }
      g_ram.flagworkcnt = p_flagwork - g_ram.flagwork;
      p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt2];
      scra_h -= 768;
      if (scra_h >= 0) {
        while (scra_h > g_ram.asetadr2->x) {
          ++g_ram.asetadr2->x;
          ++p_flagwork;
        }
      }
      g_ram.flagworkcnt2 = p_flagwork - g_ram.flagwork;
    }
  }
  actset2();
}


static void actset2(void) {
  short scra_v = g_ram.scra_v_posit >> 16 & 0xFF80;
  if (scra_v != g_ram.asetposi2) {
    if (scra_v < g_ram.asetposi2) {
      if (g_ram.scralim_up < 0) {
        if (scra_v != 0 || g_ram.asetposi2 == 128) {
          scra_v -= 128;
          if (scra_v < 0) {
            scra_v = (unsigned short)scra_v & g_ram.scrc_v;
          }
        }
        else {
          scra_v += 384;
          if (scra_v >= (short)g_ram.scrc_v) {
            scra_v &= g_ram.scrc_v;
          }
        }
      }
      else {
        scra_v -= 128;
        if (scra_v < 0) {
          goto end;
        }
      }
    }
    else {
      if (g_ram.scralim_up < 0) {
        if (g_ram.asetposi2 != 0 || scra_v == 128) {
          scra_v += 384;
          if (scra_v >= (short)g_ram.scrc_v) {
            scra_v &= g_ram.scrc_v;
          }
        }
        else {
          scra_v -= 128;
          if (scra_v < 0) {
            scra_v = (unsigned short)scra_v & g_ram.scrc_v;
          }
        }
      }
      else {
        scra_v += 384;
        if (scra_v > (short)g_ram.scrc_v) {
          goto end;
        }
      }
    }
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      unsigned char* p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt2];
      int cnt = g_ram.asetadr - g_ram.asetadr2;
      for (int i = 0; i < cnt; ++i) {
        if (!BIT_IS_SET(*p_flagwork, 7)
            && (g_ram.asetadr2->y & 0x0FFF) >= scra_v
            && (g_ram.asetadr2->y & 0x0FFF) <= scra_v + 128) {
          SET_BIT(*p_flagwork, 7);
          fp16_set_integer(&result.actwk_ptr->xposi, g_ram.asetadr2->x);
          fp16_set_integer(&result.actwk_ptr->yposi, g_ram.asetadr2->y & 0x0FFF);
          result.actwk_ptr->actflg.hflip = BIT_IS_SET(g_ram.asetadr2->y, 13);
          result.actwk_ptr->actflg.vflip = BIT_IS_SET(g_ram.asetadr2->y, 14);
          result.actwk_ptr->u.obj.cddat.right = BIT_IS_SET(g_ram.asetadr2->y, 13);
          result.actwk_ptr->u.obj.cddat.down = BIT_IS_SET(g_ram.asetadr2->y, 14);
          result.actwk_ptr->r_ptr = g_ram.act_tbl_ptr[g_ram.asetadr2->id];
          result.actwk_ptr->u.obj.userflag = g_ram.asetadr2->userflag;
          result = actwkchk_next(result);
          if (result.actwk_ptr == 0) break;
        }
        ++g_ram.asetadr2;
        ++p_flagwork;
      }
    }
  }

end:
  g_ram.asetposi2 = g_ram.scra_v_posit >> 16 & 0xFF80;
}


static void actnoset_min(SKC_sprite_status* p_actwk, SKC_aset* p_aset) {
  fp16_set_integer(&p_actwk->xposi, p_aset->x);
  fp16_set_integer(&p_actwk->yposi, p_aset->y & 0x0FFF);
  p_actwk->actflg.hflip = BIT_IS_SET(p_aset->y, 13);
  p_actwk->actflg.vflip = BIT_IS_SET(p_aset->y, 14);
  p_actwk->u.obj.cddat.right = BIT_IS_SET(p_aset->y, 13);
  p_actwk->u.obj.cddat.down = BIT_IS_SET(p_aset->y, 14);
  p_actwk->r_ptr = g_ram.act_tbl_ptr[p_aset->id];
  p_actwk->u.obj.userflag = p_aset->userflag;
  p_actwk->u.obj.flagwork_index = 1;
}


static void actnoset_ywrap(SKC_sprite_status* p_actwk, SKC_aset* p_aset, unsigned char* p_flagwork, short scra_v_up, short scra_v_down) {
  if (BIT_IS_SET(*p_flagwork, 7)) return;
  if (!BIT_IS_SET(p_aset->y, 15) && (p_aset->y & 0x0FFF) < scra_v_up && (p_aset->y & 0x0FFF) > scra_v_down) return;

  SET_BIT(*p_flagwork, 7);
  fp16_set_integer(&p_actwk->xposi, p_aset->x);
  fp16_set_integer(&p_actwk->yposi, p_aset->y & 0x0FFF);
  p_actwk->actflg.hflip = BIT_IS_SET(p_aset->y, 13);
  p_actwk->actflg.vflip = BIT_IS_SET(p_aset->y, 14);
  p_actwk->u.obj.cddat.right = BIT_IS_SET(p_aset->y, 13);
  p_actwk->u.obj.cddat.down = BIT_IS_SET(p_aset->y, 14);
  p_actwk->r_ptr = g_ram.act_tbl_ptr[p_aset->id];
  p_actwk->u.obj.userflag = p_aset->userflag;
  p_actwk->u.obj.flagwork_index = p_flagwork - g_ram.flagwork + 1;
}


static void actnoset(SKC_sprite_status* p_actwk, SKC_aset* p_aset, unsigned char* p_flagwork, short scra_v_up, short scra_v_down) {
  if (BIT_IS_SET(*p_flagwork, 7)) return;
  if (!BIT_IS_SET(p_aset->y, 15) && ((p_aset->y & 0x0FFF) < scra_v_up || (p_aset->y & 0x0FFF) > scra_v_down)) return;

  SET_BIT(*p_flagwork, 7);
  fp16_set_integer(&p_actwk->xposi, p_aset->x);
  fp16_set_integer(&p_actwk->yposi, p_aset->y & 0x0FFF);
  p_actwk->actflg.hflip = BIT_IS_SET(p_aset->y, 13);
  p_actwk->actflg.vflip = BIT_IS_SET(p_aset->y, 14);
  p_actwk->u.obj.cddat.right = BIT_IS_SET(p_aset->y, 13);
  p_actwk->u.obj.cddat.down = BIT_IS_SET(p_aset->y, 14);
  p_actwk->r_ptr = g_ram.act_tbl_ptr[p_aset->id];
  p_actwk->u.obj.userflag = p_aset->userflag;
  p_actwk->u.obj.flagwork_index = p_flagwork - g_ram.flagwork + 1;
}


SKC_actwkchk_result actwkchk_next(SKC_actwkchk_result result) {
  ++result.actwk_ptr;
  return actwkchk0(result.actwk_ptr, result.remaining_slot_cnt);
}


SKC_actwkchk_result actwkchk(void) {
  return actwkchk0(&g_ram.actwk[ACTWK_DYNAMIC_START], ACTWK_DYNAMIC_SLOTS);
}


SKC_actwkchk_result actwkchk2(SKC_sprite_status* p_actwk) {
  ++p_actwk;
  int slot_cnt = &g_ram.actwk[ACTWK_RESERVED_START] - p_actwk;
  return actwkchk0(p_actwk, slot_cnt);
}


SKC_actwkchk_result actwkchk0(SKC_sprite_status* p_actwk, int slot_cnt) {
  SKC_actwkchk_result result = { 0, 0};

  for (int i = slot_cnt; i > 0; --i) {
    if (p_actwk->r_ptr == 0) {
      result.actwk_ptr = p_actwk;
      result.remaining_slot_cnt = i - 1;
      break;
    }
  }

  return result;
}


void actunset(void) {
  for (int i = ACTWK_DYNAMIC_START; i < ACTWK_RESERVED_START; ++i) {
    SKC_sprite_status* p_actwk = &g_ram.actwk[i];
    if (p_actwk->r_ptr != 0 && p_actwk->u.obj.flagwork_index != 0) {
      CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index], 7);
    }
  }

  unsigned short* p_ringbuffer = &g_ram.ringbuffer[1];

  while (g_ram.ringbuffer[0] > 0) {
    if (*p_ringbuffer != 0) {
      g_ram.ringwk[*p_ringbuffer - 1].pattim = -1;
      g_ram.ringwk[*p_ringbuffer - 1].patno = -1;
      *p_ringbuffer = 0;
      --g_ram.ringbuffer[0];
    }
  }
}


void actset_sync(void) {
  short scra_h = (g_ram.scra_h_posit >> 16) + 1024 & 0xFF80;
  if (scra_h != g_ram.asetposi) {
    if (scra_h < g_ram.asetposi) {
      g_ram.asetposi = scra_h;
      unsigned char* p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt2];
      scra_h -= 128;
      if (scra_h >= 0) {
        while (scra_h < (g_ram.asetadr2 - 1)->x) {
          --g_ram.asetadr2;
          --p_flagwork;
        }
      }
      g_ram.flagworkcnt2 = p_flagwork - g_ram.flagwork;
      p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt];
      scra_h += 768;
      while (scra_h < (g_ram.asetadr - 1)->x) {
        --g_ram.asetadr2;
        --p_flagwork;
      }
      g_ram.flagworkcnt = p_flagwork - g_ram.flagwork;
    }
    else {
      g_ram.asetposi = scra_h;
      unsigned char* p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt];
      scra_h += 640;
      while (scra_h > g_ram.asetadr->x) {
        ++g_ram.asetadr;
        ++p_flagwork;
      }
      g_ram.flagworkcnt = p_flagwork - g_ram.flagwork;
      p_flagwork = &g_ram.flagwork[g_ram.flagworkcnt2];
      scra_h -= 768;
      if (scra_h >= 0) {
        while (scra_h > g_ram.asetadr2->x) {
          ++g_ram.asetadr2;
          ++p_flagwork;
        }
      }
      g_ram.flagworkcnt2 = p_flagwork - g_ram.flagwork;
    }
  }
}
