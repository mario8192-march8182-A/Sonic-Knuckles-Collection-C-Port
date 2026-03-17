#include "coli.h"
#include <stdbool.h>
#include "types/actwkchkresult.h"
#include "types/size.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "types/spritestatushandler.h"
#include "utils/bits.h"
#include "utils/fp16.h"
#include "actset.h"
#include "constants.h"
#include "etc.h"
#include "shared.h"
#include "sound.h"
#include "objects/ring.h"
#include "objects/toge.h"
static void pcol0(SKC_sprite_status* p_playerwk, short xposi, short yposi, short sprhs, short sprvs);
static bool colitbl_data_xchk(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs);
static bool colitbl_data_ychk(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs);
static SKC_size colitbl[57];
static bool coli_hit_chk(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void pcolitem(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void pcolnomal(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void emydieset(SKC_sprite_status* p_coliwk);
static void pcolplay(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void bariabounce(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void pcole(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void playdieset0(SKC_sprite_status* p_playerwk, short sound_command);
static void pcolspecial(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void pcolbaria(SKC_sprite_status* p_playerwk);
static void colitbl_data_xchk2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs);
static void colitbl_data_ychk2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs);
static void coli_hit_chk2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void coli_hit_chk3(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void pcolnomal2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void pcolplay2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
static void pcolspecial2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);

extern int g_debug_mode;
extern sonic3_ram g_ram;


void vspcol(SKC_sprite_status* p_playerwk) {
  short xposi = fp16_get_integer(p_playerwk->xposi) - 4;
  short sprvs = (short)p_playerwk->sprvsize - 3;
  short yposi = fp16_get_integer(p_playerwk->yposi) - sprvs;
  pcol0(p_playerwk, xposi, yposi, 8, sprvs * 2);
}


void pcol(SKC_sprite_status* p_playerwk) {
  Test_Ring_Collisions();
  pcolbaria(p_playerwk);
  if (p_playerwk->u.play.character == SONIC
      && p_playerwk->u.play.cddat.baria == 0
      && p_playerwk->u.play.cddat.muteki == 0
      && p_playerwk->u.play.cddat.flame_baria == 0
      && p_playerwk->u.play.cddat.thunder_baria == 0
      && p_playerwk->u.play.cddat.aqua_baria == 0
      && p_playerwk->u.play.talent_status == 1) {
    bool muteki = p_playerwk->u.play.cddat.muteki;
    p_playerwk->u.play.cddat.muteki = 1;
    short xposi = fp16_get_integer(p_playerwk->xposi) - 24;
    short yposi = fp16_get_integer(p_playerwk->yposi) - 24;
    pcol0(p_playerwk, xposi, yposi, 48, 48);
    if (!muteki) {
      p_playerwk->u.play.cddat.muteki = 0;
    }
  }
  else {
    short xposi = fp16_get_integer(p_playerwk->xposi) - 8;
    short sprvs = (short)p_playerwk->sprvsize - 3;
    short yposi = fp16_get_integer(p_playerwk->yposi) - sprvs;
    pcol0(p_playerwk, xposi, yposi, 16, sprvs * 2);
  }
}


static void pcol0(SKC_sprite_status* p_playerwk, short xposi, short yposi, short sprhs, short sprvs) {
  for (int slot = 1; slot < g_ram.colibuffer[0] + 1; ++slot) {
    SKC_sprite_status* p_coliwk = &g_ram.actwk[g_ram.colibuffer[slot]];
    if (p_playerwk->colino != 0) {
      bool exit = colitbl_data_xchk(p_playerwk, p_coliwk, xposi, yposi, sprhs, sprvs);
      if (exit) break;
    }
  }
}


static bool colitbl_data_xchk(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs) {
  long wk = fp16_get_integer(p_coliwk->xposi) - (short)colitbl[p_coliwk->colino & 0x3F].w - xposi;
  if (wk < 0) {
    wk += (long)colitbl[p_coliwk->colino & 0x3F].w * 2;
    if (wk > 0xFFFF) {
      return colitbl_data_ychk(p_playerwk, p_coliwk, xposi, yposi, sprhs, sprvs);
    }
  }
  else if (wk <= (long)sprhs) {
    return colitbl_data_ychk(p_playerwk, p_coliwk, xposi, yposi, sprhs, sprvs);
  }
  return false;
}


static bool colitbl_data_ychk(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs) {
  long wk = fp16_get_integer(p_coliwk->yposi) - (short)colitbl[p_coliwk->colino & 0x3F].h - yposi;
  if (wk < 0) {
    wk += (long)colitbl[p_coliwk->colino & 0x3F].h * 2;
    if (wk > 0xFFFF) {
      return coli_hit_chk(p_playerwk, p_coliwk);
    }
  }
  else if (wk <= (long)sprvs) {
    return coli_hit_chk(p_playerwk, p_coliwk);
  }
  return false;
}


static SKC_size colitbl[57] = {
  {   4,   4 },
  {  20,  20 },
  {  12,  20 },
  {  20,  12 },
  {   4,  16 },
  {  12,  18 },
  {  16,  16 },
  {   6,   6 },
  {  24,  12 },
  {  12,  16 },
  {  16,   8 },
  {   8,   8 },
  {  20,  16 },
  {  20,   8 },
  {  14,  14 },
  {  24,  24 },
  {  40,  16 },
  {  16,  24 },
  {   8,  16 },
  {  32, 112 },
  {  64,  32 },
  { 128,  32 },
  {  32,  32 },
  {   8,   8 },
  {   4,   4 },
  {  32,   8 },
  {  12,  12 },
  {   8,   4 },
  {  24,   4 },
  {  40,   4 },
  {   4,   8 },
  {   4,  24 },
  {   4,  40 },
  {  24,  24 },
  {  24,  24 },
  {  12,  24 },
  {  72,   8 },
  {  24,  40 },
  {  16,   4 },
  {  32,   2 },
  {  16,  28 },
  {  12,  36 },
  {  16,   2 },
  {   4,  64 },
  {  24,  64 },
  {  32,  16 },
  {  28,  20 },
  {  16,   2 },
  {  16,   1 },
  {   2,   8 },
  {  16,  64 },
  {  12,   4 },
  {   8,  12 },
  {  40,  32 },
  {  64,   2 },
  {  96,   2 },
  {  40,  40 }
};


static bool coli_hit_chk(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  switch ((p_coliwk->colino & 0xC0) >> 6) {
    case 0:
      pcolnomal(p_playerwk, p_coliwk);
      break;
    case 3:
      pcolspecial(p_playerwk, p_coliwk);
      break;
    case 2:
      pcolplay(p_playerwk, p_coliwk);
      break;
    case 1:
      pcolitem(p_playerwk, p_coliwk);
      break;
  }
  return true;
}


static void pcolitem(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  if ((p_coliwk->colino & 0x3F) != 6) { // ring
    unsigned char timer = g_ram.actwk[0].u.play.invulnerability_timer;
    if (g_ram.vs_flag != 0) {
      timer = p_playerwk->u.play.invulnerability_timer;
    }
    if (timer < 90) {
      p_coliwk->r_no = 4;
    }
  }
  else { // item
    short yspeed = g_ram.reverse_gravity_flag == 0 ? p_playerwk->yspeed : -p_playerwk->yspeed;
    if ((p_coliwk->actflg.vflip == 1 && yspeed > 0)
        || (p_coliwk->actflg.vflip == 0 && yspeed < 0)
        || p_coliwk->u.obj.cddat.down == 0) {
      short yposi = fp16_get_integer(p_playerwk->yposi);
      short coli_yposi = fp16_get_integer(p_coliwk->yposi);
      if ((p_coliwk->actflg.vflip == 0 && (unsigned short)(yposi - 16) >= (unsigned short)coli_yposi)
          || (p_coliwk->actflg.vflip == 1 && (unsigned short)(yposi + 16) < (unsigned short)coli_yposi)) {
        p_playerwk->yspeed = -p_playerwk->yspeed;
        p_coliwk->yspeed = -0x180;
        if (p_coliwk->u.obj.actfree.item.r_no1 == 0) {
          p_coliwk->u.obj.actfree.item.r_no1 = 4;
        }
      }
    }
    else if (p_playerwk == &g_ram.actwk[0] || g_ram.vs_flag != 0) {
      bool gliding_or_sliding = p_playerwk->u.play.talent_status == 1 || p_playerwk->u.play.talent_status == 3;
      if (p_playerwk->mstno == 2 || (p_playerwk->u.play.character == KNUCKLES && gliding_or_sliding)) {
        p_playerwk->yspeed = -p_playerwk->yspeed;
        p_coliwk->r_no = 4;
        p_coliwk->u.obj.ko = p_playerwk - g_ram.actwk;
      }
    }
  }
}


static void pcolnomal(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  if (p_playerwk->u.play.cddat.muteki == 0 && p_playerwk->mstno != 9 && p_playerwk->mstno != 2) {
    switch (p_playerwk->u.play.character) {
      case KNUCKLES:
        if (p_playerwk->u.play.talent_status != 1 && p_playerwk->u.play.talent_status != 3) {
          pcolplay(p_playerwk, p_coliwk);
          return;
        }
        break;
      case SONIC:
      default:
        pcolplay(p_playerwk, p_coliwk);
        return;
      case MILES:
        if (p_playerwk->u.play.talent_status == 0 || p_playerwk->u.play.cddat.underwater == 1) {
          pcolplay(p_playerwk, p_coliwk);
          return;
        }
        else {
          short x = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_coliwk->xposi);
          short y = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_coliwk->yposi);
          short angle = atan(x, y) - 32;
          if ((unsigned short)angle >= 64) {
            pcolplay(p_playerwk, p_coliwk);
            return;
          }
        }
        break;
    }
  }
  if (p_coliwk->colicnt != 0) {
    p_playerwk->xspeed = -p_playerwk->xspeed;
    p_playerwk->yspeed = -p_playerwk->yspeed;
    p_playerwk->mspeed = -p_playerwk->mspeed;
    p_coliwk->pattimm = p_coliwk->colino;
    p_coliwk->mspeed = p_playerwk - g_ram.actwk;
    p_coliwk->colino = 0;
    --p_coliwk->colicnt;
    if (p_coliwk->colicnt == 0) {
      p_coliwk->u.obj.cddat.die = 1;
    }
    if (p_playerwk->u.play.character == KNUCKLES && p_playerwk->u.play.talent_status == 1) {
      p_playerwk->u.play.talent_status = 2;
      p_playerwk->mstno = 33;
      p_playerwk->u.play.cddat.left = p_playerwk->xspeed < 0 ? 0 : 1;
      p_playerwk->sprvsize = p_playerwk->u.play.height;
      p_playerwk->sprhsize = p_playerwk->u.play.width;
    }
  }
  else {
    emydieset(p_coliwk);
    if (p_playerwk->yspeed < 0) {
      p_playerwk->yspeed += 0x100;
    }
    else if (fp16_get_integer(p_playerwk->yposi) >= fp16_get_integer(p_coliwk->yposi)) {
      p_playerwk->yspeed -= 0x100;
    }
    else {
      p_playerwk->yspeed = -p_playerwk->yspeed;
    }
  }
}


static void emydieset(SKC_sprite_status* p_coliwk) {
  if (p_coliwk->u.obj.cddat.wrt == 1) {
    CLEAR_BIT(g_ram.emy_wrt_flg[p_coliwk->u.obj.wrt.flg_index], p_coliwk->u.obj.wrt.flg_bit);
  }
  set_emy_die0(p_coliwk);
}


static void pcolplay(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  bool protected = p_playerwk->u.play.cddat.baria == 1
      || p_playerwk->u.play.cddat.muteki == 1
      || p_playerwk->u.play.cddat.flame_baria == 1
      || p_playerwk->u.play.cddat.thunder_baria == 1
      || p_playerwk->u.play.cddat.aqua_baria == 1;
  bool absorbing = (p_playerwk->u.play.cddat.flame_baria == 1 && p_coliwk->u.obj.cddat.flame_baria_die == 1)
      || (p_playerwk->u.play.cddat.thunder_baria == 1 && p_coliwk->u.obj.cddat.thunder_baria_die == 1)
      || (p_playerwk->u.play.cddat.aqua_baria == 1 && p_coliwk->u.obj.cddat.aqua_baria_die == 1);
  if (protected) {
    if (absorbing) return;
    if (p_playerwk->u.play.cddat.baria == 1 && p_coliwk->u.obj.cddat.baria_bounce == 1) {
      bariabounce(p_playerwk, p_coliwk);
      return;
    }
  }
  else {
    if (p_playerwk->u.play.talent_status != 1 && p_coliwk->u.obj.cddat.baria_bounce == 1) {
      bariabounce(p_playerwk, p_coliwk);
      return;
    }
  }
  if (p_playerwk->u.play.cddat.muteki == 0) {
    pcole(p_playerwk, p_coliwk);
  }
}


static void bariabounce(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  short x = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_coliwk->xposi);
  short y = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_coliwk->yposi);
  unsigned char angle = atan(x, y) & 0xFF;
  short sin, cos;
  sinset(angle, &sin, &cos);
  p_coliwk->xspeed = cos * -0x800 / 0x100;
  p_coliwk->yspeed = sin * -0x800 / 0x100;
  p_coliwk->colino = 0;
}


static void pcole(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  if (p_playerwk->u.play.invulnerability_timer == 0) {
    playdamageset(p_playerwk, p_coliwk);
  }
}


void playdamageset(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  unsigned short plring = p_playerwk == &g_ram.actwk[0] || g_ram.vs_flag == 0 ? g_ram.plring : g_ram.pl2ring;
  if (p_playerwk == &g_ram.actwk[0] || g_ram.vs_flag == 1) {
    if (p_playerwk->u.play.cddat.baria == 0 && g_debug_mode == 0 && !BIT_IS_SET(p_playerwk->u.play.eventflag, 7)) {
      if (plring != 0) {
        SKC_actwkchk_result result = actwkchk();
        if (result.actwk_ptr != 0) {
          result.actwk_ptr->r_ptr = &flyring;
          fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_playerwk->xposi));
          fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_playerwk->yposi));
          result.actwk_ptr->u.obj.oya = p_playerwk - g_ram.actwk;
        }
      }
      else {
        bool is_toge = (int)p_coliwk->r_ptr >= (int)&toge && (int)p_coliwk->r_ptr < (int)&togedamegesub;
        short sound_command = !is_toge ? 53 : 55;
        playdieset0(p_playerwk, sound_command);
        return;
      }
    }
    if (!BIT_IS_SET(p_playerwk->u.play.eventflag, 7)) {
      p_playerwk->u.play.cddat.baria = 0;
      p_playerwk->u.play.cddat.flame_baria = 0;
      p_playerwk->u.play.cddat.thunder_baria = 0;
      p_playerwk->u.play.cddat.aqua_baria = 0;
    }
  }
  p_playerwk->r_no = 4;
  Player_TouchFloor();
  p_playerwk->u.play.cddat.muteki = 1;
  p_playerwk->xspeed = p_playerwk->u.play.cddat.underwater == 0 ? -0x200 : -0x100;
  p_playerwk->yspeed = p_playerwk->u.play.cddat.underwater == 0 ? -0x400 : -0x200;
  if ((unsigned short)fp16_get_integer(p_playerwk->xposi) >= (unsigned short)fp16_get_integer(p_coliwk->xposi)) {
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  p_playerwk->mspeed = 0;
  p_playerwk->mstno = 26;
  p_playerwk->u.play.invulnerability_timer = 126;
  bool is_toge = (int)p_coliwk->r_ptr >= (int)&toge && (int)p_coliwk->r_ptr < (int)&togedamegesub;
  short sound_command = !is_toge ? 53 : 55;
  soundset(sound_command);
}


void playdieset(SKC_sprite_status* p_playerwk) {
  if (g_ram.editmode != 0) return;

  playdieset0(p_playerwk, 53);
}


static void playdieset0(SKC_sprite_status* p_playerwk, short sound_command) {
  p_playerwk->u.play.cddat.baria = 0;
  p_playerwk->u.play.cddat.muteki = 0;
  p_playerwk->u.play.cddat.speedup = 0;
  p_playerwk->u.play.cddat.unusedb = 0;
  p_playerwk->u.play.cddat.flame_baria = 0;
  p_playerwk->u.play.cddat.thunder_baria = 0;
  p_playerwk->u.play.cddat.aqua_baria = 0;
  p_playerwk->u.play.cddat.infinite_inertia = 0;
  p_playerwk->u.play.eventflag = 0;
  p_playerwk->r_no = 6;
  Player_TouchFloor();
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->yspeed = -0x700;
  p_playerwk->xspeed = 0;
  p_playerwk->mspeed = 0;
  p_playerwk->mstno = 24;
  g_ram.plsproffset = p_playerwk->sproffset;
  SET_BIT(p_playerwk->sproffset, 15);
  soundset(sound_command);
}


static void pcolspecial(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  switch (p_coliwk->colino & 0x3F) {
    case 7:
    case 6:
    case 10:
    case 12:
    case 21:
    case 22:
    case 23:
    case 24:
    case 33:
      if (p_playerwk - g_ram.actwk != 0) {
        ++p_coliwk->colicnt;
      }
      ++p_coliwk->colicnt;
      break;
  }
}


void colibufferchk(SKC_sprite_status* p_actwk) {
  if (g_ram.colibuffer[0] == COLIBUFFER_SLOTS - 1) return;

  ++g_ram.colibuffer[0];
  g_ram.colibuffer[g_ram.colibuffer[0]] = p_actwk - g_ram.actwk;
}


static void pcolbaria(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.baria == 0
      && p_playerwk->u.play.cddat.flame_baria == 0
      && p_playerwk->u.play.cddat.thunder_baria == 0
      && p_playerwk->u.play.cddat.aqua_baria == 0) return;

  for (int slot = 1; slot < g_ram.colibuffer[0] + 1; ++slot) {
    SKC_sprite_status* p_coliwk = &g_ram.actwk[g_ram.colibuffer[slot]];
    if ((p_coliwk->colino & 0xC0) >> 6 == 2) {
      short xposi = fp16_get_integer(p_playerwk->xposi) - 24;
      short yposi = fp16_get_integer(p_playerwk->yposi) - 24;
      colitbl_data_xchk2(p_playerwk, p_coliwk, xposi, yposi, 48, 48);
    }
  }
}


static void colitbl_data_xchk2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs) {
  if (!(p_coliwk->colino & 0x3F)) return;

  long wk = fp16_get_integer(p_coliwk->xposi) - (short)colitbl[p_coliwk->colino & 0x3F].w - xposi;
  if (wk < 0) {
    wk += (long)colitbl[p_coliwk->colino & 0x3F].w * 2;
    if (wk > 0xFFFF) {
      colitbl_data_ychk2(p_playerwk, p_coliwk, xposi, yposi, sprhs, sprvs);
    }
  }
  else if (wk <= (long)sprhs) {
    colitbl_data_ychk2(p_playerwk, p_coliwk, xposi, yposi, sprhs, sprvs);
  }
}


static void colitbl_data_ychk2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk, short xposi, short yposi, short sprhs, short sprvs) {
  long wk = fp16_get_integer(p_coliwk->yposi) - (short)colitbl[p_coliwk->colino & 0x3F].h - yposi;
  if (wk < 0) {
    wk += (long)colitbl[p_coliwk->colino & 0x3F].h * 2;
    if (wk > 0xFFFF) {
      coli_hit_chk2(p_playerwk, p_coliwk);
    }
  }
  else if (wk <= (long)sprvs) {
    coli_hit_chk2(p_playerwk, p_coliwk);
  }
}


static void coli_hit_chk2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  if (p_coliwk->u.obj.cddat.baria_bounce == 0) return;

  bariabounce(p_playerwk, p_coliwk);
}


void pcolhyper(SKC_sprite_status* p_playerwk) {
  for (int slot = 1; slot < g_ram.colibuffer[0] + 1; ++slot) {
    SKC_sprite_status* p_coliwk = &g_ram.actwk[g_ram.colibuffer[slot]];
    if (p_coliwk->colino != 0) {
      coli_hit_chk3(p_playerwk, p_coliwk);
    }
  }
}


static void coli_hit_chk3(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  if (p_coliwk->actflg.onscreen == 0) return;

  switch ((p_coliwk->colino & 0xC0) >> 6) {
    case 0:
      pcolnomal2(p_playerwk, p_coliwk);
      break;
    case 3:
      pcolspecial2(p_playerwk, p_coliwk);
      break;
    case 2:
      pcolplay2(p_playerwk, p_coliwk);
      break;
    case 1:
      break;
  }
}


static void pcolnomal2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  if (p_coliwk->colicnt == 0) {
    emydieset(p_coliwk);
  }
}


static void pcolplay2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  if (p_coliwk->u.obj.cddat.baria_bounce == 1) {
    bariabounce(p_playerwk, p_coliwk);
  }
}


static void pcolspecial2(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk) {
  p_coliwk->colicnt |= 3;
  if (g_ram.play_type == PLAY_TYPE_KNUCKLES) {
    fp16_set_integer(&g_ram.actwk[1].xposi, fp16_get_integer(p_coliwk->xposi));
    fp16_set_integer(&g_ram.actwk[1].yposi, fp16_get_integer(p_coliwk->yposi));
  }
  g_ram.actwk[1].mstno = 2;
  g_ram.actwk[1].u.play.cddat.jump = 1;
}
