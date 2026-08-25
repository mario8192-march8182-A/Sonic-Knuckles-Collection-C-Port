#include "fcol.h"
#include <stdbool.h>
#include <stdlib.h>
#include "data/scd.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "utils/fp16.h"
#include "utils/fp8.h"
#include "utils/bits.h"
#include "utils/direction.h"
#include "utils/stageno.h"
static signed char dirchk(SKC_sprite_status* p_actwk, signed char scd0, signed char scd1);
static bool fcol_d(SKC_sprite_status* p_actwk);
static bool fcol_r(SKC_sprite_status* p_actwk);
static bool fcol_u(SKC_sprite_status* p_actwk);
static bool fcol_l(SKC_sprite_status* p_actwk);
static unsigned short scramapad(short xposi, short yposi, unsigned char* p_zonemap);
static signed char scdend(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static signed char scdend2(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static signed char scdchk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static signed char scdchk2(short xposi, short yposi, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static unsigned char flyringscdchk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static signed char scdchk_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static signed char scdend_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static signed char scdend2_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);
static signed char scdchk2_r(short xposi, short yposi, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap);

extern sonic3_ram g_ram;


bool fcol(SKC_sprite_status* p_actwk) {
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  if (p_actwk->u.play.cddat.ride == 1) {
    g_ram.dirstk[0] = 0;
    g_ram.dirstk[2] = 0;
    return 0;
  }
  g_ram.dirstk[0] = 3;
  g_ram.dirstk[2] = 3;
  unsigned char direction = direction_sum(p_actwk->direc.b.b0, 32);
  if (direction >= 128) {
    direction = p_actwk->direc.b.b0;
    if (direction >= 128) {
      direction = direction_sub(direction, 1);
    }
    direction = direction_sum(direction, 32);
  }
  else {
    direction = p_actwk->direc.b.b0;
    if (direction >= 128) {
      direction = direction_sum(direction, 1);
    }
    direction = direction_sum(direction, 31);
  }
  bool coli = false;

  switch (direction & 0xC0) {
    case  64: coli = fcol_l(p_actwk); break;
    case 128: coli = fcol_u(p_actwk); break;
    case 192: coli = fcol_r(p_actwk); break;
     default: coli = fcol_d(p_actwk); break;
  }

  return coli;
}


static signed char dirchk(SKC_sprite_status* p_actwk, signed char scd0, signed char scd1) {
  unsigned char direction = g_ram.dirstk[2];
  if (scd1 > scd0) {
    direction = g_ram.dirstk[0];
    scd1 = scd0;
  }
  if (!(direction & 1)) {
    unsigned char direction_wk = direction_sub(direction, p_actwk->direc.b.b0);
    if (direction_wk >= 128) {
      direction_wk = direction_hmirror(direction_wk);
    }
    if (direction_wk < 32) {
      p_actwk->direc.b.b0 = direction;
    }
    else {
      p_actwk->direc.b.b0 = (p_actwk->direc.b.b0 + 32) & 0xC0;
    }
  }
  else {
    p_actwk->direc.b.b0 = (p_actwk->direc.b.b0 + 32) & 0xC0;
  }
  return scd1;
}


static bool fcol_d(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprhsize;
  short yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  signed char scd0 = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprhsize;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  signed char scd1 = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  scd0 = dirchk(p_actwk, scd0, scd1);
  if (scd0 == 0) {
    return false;
  }
  if (scd0 < 0) {
    if (scd0 < -14) {
      return true;
    }
  }
  if (p_actwk->u.play.convex_flag == 0) {
    signed char xspeed = abs(fp8_get_integer(p_actwk->xspeed)) + 4;
    if (xspeed >= 14) {
      xspeed = 14;
    }
    if (scd0 > xspeed) {
      p_actwk->u.play.cddat.jump = 1;
      p_actwk->u.play.cddat.push = 0;
      p_actwk->mstrestart = 1;
    }
  }
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - scd0);
  return true;
}


static bool fcol_r(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprvsize;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprhsize;
  signed char scd0 = scd2chk_r(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprvsize;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprhsize;
  signed char scd1 = scd2chk_r(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[2]);
  scd0 = dirchk(p_actwk, scd0, scd1);
  if (scd0 == 0) {
    return false;
  }
  if (scd0 < 0) {
    if (scd0 >= -14) {
      if (p_actwk->u.play.force_direc_up_timer == 0) {
        fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + scd0);
      }
      else {
        --p_actwk->u.play.force_direc_up_timer;
        p_actwk->direc.b.b0 = 192;
      }
      return true;
    }
    if (g_ram.stageno == ANGEL_ISLAND_ACT_1) {
      /* This is a workaround for the loop that can be entered from the bottom. */
      p_actwk->direc.b.b0 = 192;
      p_actwk->u.play.force_direc_up_timer = 3;
    }
    return true;
  }
  if (p_actwk->u.play.convex_flag == 0) {
    signed char yspeed = abs(fp8_get_integer(p_actwk->yspeed)) + 4;
    if (yspeed >= 14) {
      yspeed = 14;
    }
    if (scd0 > yspeed) {
      p_actwk->u.play.cddat.jump = 1;
      p_actwk->u.play.cddat.push = 0;
      p_actwk->mstrestart = 1;
    }
  }
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - scd0);
  return true;
}


static bool fcol_u(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprhsize;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  signed char scd0 = scd2chk(xposi, yposi, -16, 0x0800, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprhsize;
  yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  signed char scd1 = scd2chk(xposi, yposi, -16, 0x0800, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[2]);
  scd0 = dirchk(p_actwk, scd0, scd1);
  if (scd0 == 0) {
    return false;
  }
  if (scd0 < 0) {
    if (scd0 < -14) {
      return true;
    }
  }
  else if (p_actwk->u.play.convex_flag == 0) {
    signed char xspeed = abs(fp8_get_integer(p_actwk->xspeed)) + 4;
    if (xspeed >= 14) {
      xspeed = 14;
    }
    if (scd0 > xspeed) {
      p_actwk->u.play.cddat.jump = 1;
      p_actwk->u.play.cddat.push = 0;
      p_actwk->mstrestart = 1;
    }
  }
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - scd0);
  return true;
}


static bool fcol_l(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprvsize ^ 15;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprhsize;
  signed char scd0 = scd2chk_r(xposi, yposi, -16, 0x0400, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprvsize ^ 15;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprhsize;
  signed char scd1 = scd2chk_r(xposi, yposi, -16, 0x0400, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[2]);
  scd0 = dirchk(p_actwk, scd0, scd1);
  if (scd0 == 0) {
    return false;
  }
  if (scd0 < 0) {
    if (scd0 < -14) {
      return true;
    }
  }
  else if (p_actwk->u.play.convex_flag == 0) {
    signed char yspeed = abs(fp8_get_integer(p_actwk->yspeed)) + 4;
    if (yspeed >= 14) {
      yspeed = 14;
    }
    if (scd0 > yspeed) {
      p_actwk->u.play.cddat.jump = 1;
      p_actwk->u.play.cddat.push = 0;
      p_actwk->mstrestart = 1;
    }
  }
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - scd0);
  return true;
}


static unsigned short scramapad(short xposi, short yposi, unsigned char* p_zonemap) {
  unsigned short yposi_wk = (yposi / 32) & g_ram.scr_row;
  unsigned short screen_row_offset = p_zonemap[yposi_wk] | p_zonemap[yposi_wk + 1] << 8;
  unsigned short screen_offset = screen_row_offset + xposi / 128;
  screen_offset ^= 1; /* Stage data is byte-swapped. */
  unsigned char screen_no = g_ram.mapwk[screen_offset];
  unsigned short block_offset = screen_no * 128 + (yposi & 0x0070) + (xposi / 8 & 0x000E);
  unsigned short block_no = g_ram.mapwk[block_offset] << 8 | g_ram.mapwk[block_offset + 1];
  return block_no;
}


signed char scd2chk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk) {
  unsigned char* p_zonemap = &g_ram.zonemapwk[8];
  if (g_ram.scd_bg_flag == 0) {
    return scdchk(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  signed char scd0 = scdchk(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  p_dirstk[1] = p_dirstk[0];
  p_zonemap += 2;
  signed char scd1 = scdchk(xposi - g_ram.scr_h_posit_ofs, yposi - g_ram.scr_v_posit_ofs, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  if (scd1 > scd0) {
    p_dirstk[0] = p_dirstk[1];
    scd1 = scd0;
  }
  return scd1;
}


static signed char scdend(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  signed char scd = scdchk2(xposi, yposi + yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  return scd + 16;
}


static signed char scdend2(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  signed char scd = scdchk2(xposi, yposi + yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  return scd - 16;
}


static signed char scdchk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  unsigned short blk_no = scramapad(xposi, yposi, p_zonemap);
  unsigned short blk_offset = blk_no & 0x3FF;
  if (blk_offset == 0 || !BIT_IS_SET(blk_no, solid_bit)) {
    return scdend(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  unsigned char scd_no = g_ram.scdadr[blk_no * 2];
  if (scd_no == 0) {
    return scdend(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  unsigned char direction_wk = scddirtbl[scd_no];
  short xposi_wk = xposi;
  if (BIT_IS_SET(blk_no, 10)) {
    xposi_wk = -xposi_wk - 1;
    direction_wk = direction_hmirror(direction_wk);
  }
  if (BIT_IS_SET(blk_no, 11)) {
    direction_wk = direction_vmirror(direction_wk);
  }
  *p_dirstk = direction_wk;
  xposi_wk = (unsigned short)xposi_wk & 0x000F;
  signed char scd_data = scdtbl[scd_no][xposi_wk];
  blk_no ^= blk_msk;
  if (BIT_IS_SET(blk_no, 11)) {
    scd_data = -scd_data;
  }
  if (scd_data == 0) {
    return scdend(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  if (scd_data >= 0) {
    if (scd_data != 16) {
      return 15 - (scd_data + (signed char)((unsigned short)yposi & 0x000F));
    }
  }
  else {
    scd_data += (signed char)((unsigned short)yposi & 0x000F);
    if (scd_data >= 0) {
      return scdend(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
    }
  }
  return scdend2(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
}


static signed char scdchk2(short xposi, short yposi, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  unsigned short blk_no = scramapad(xposi, yposi, p_zonemap);
  unsigned short blk_offset = blk_no & 0x3FF;
  if (blk_offset == 0 || !BIT_IS_SET(blk_no, solid_bit)) {
    return 15 - (signed char)((unsigned short)yposi & 0x000F);
  }
  unsigned char scd_no = g_ram.scdadr[blk_no * 2];
  if (scd_no == 0) {
    return 15 - (signed char)((unsigned short)yposi & 0x000F);
  }
  unsigned char direction_wk = scddirtbl[scd_no];
  short xposi_wk = xposi;
  if (BIT_IS_SET(blk_no, 10)) {
    xposi_wk = -xposi_wk - 1;
    direction_wk = direction_hmirror(direction_wk);
  }
  if (BIT_IS_SET(blk_no, 11)) {
    direction_wk = direction_vmirror(direction_wk);
  }
  *p_dirstk = direction_wk;
  xposi_wk = (unsigned short)xposi_wk & 0x000F;
  signed char scd_data = scdtbl[scd_no][xposi_wk];
  blk_no ^= blk_msk;
  if (BIT_IS_SET(blk_no, 11)) {
    scd_data = -scd_data;
  }
  if (scd_data == 0) {
    return 15 - (signed char)((unsigned short)yposi & 0x000F);
  }
  if (scd_data >= 0) {
    return 15 - (scd_data + (signed char)((unsigned short)yposi & 0x000F));
  }
  scd_data += (signed char)((unsigned short)yposi & 0x000F);
  if (scd_data >= 0) {
    return 15 - (signed char)((unsigned short)yposi & 0x000F);
  }
  return -scd_data - 1;
}


signed char flyringscd2chk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk) {
  unsigned char* p_zonemap = &g_ram.zonemapwk[8];
  if (g_ram.scd_bg_flag == 0) {
    return flyringscdchk(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  signed char scd0 = flyringscdchk(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  p_dirstk[1] = p_dirstk[0];
  p_zonemap += 2;
  signed char scd1 = flyringscdchk(xposi + g_ram.scr_h_posit_ofs, yposi + g_ram.scr_v_posit_ofs, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  if (scd1 > scd0) {
    p_dirstk[0] = p_dirstk[1];
    scd1 = scd0;
  }
  return scd1;
}


static unsigned char flyringscdchk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  unsigned short blk_no = scramapad(xposi, yposi, p_zonemap);
  unsigned short blk_offset = blk_no & 0x3FF;
  if (blk_offset == 0 || !BIT_IS_SET(blk_no, solid_bit)) {
    return 16;
  }
  unsigned char scd_no = g_ram.scdadr[blk_no * 2];
  if (scd_no == 0) {
    return 16;
  }
  unsigned char direction_wk = scddirtbl[scd_no];
  short xposi_wk = xposi;
  if (BIT_IS_SET(blk_no, 10)) {
    xposi_wk = -xposi_wk - 1;
    direction_wk = direction_hmirror(direction_wk);
  }
  if (BIT_IS_SET(blk_no, 11)) {
    direction_wk = direction_vmirror(direction_wk);
  }
  *p_dirstk = direction_wk;
  xposi_wk = (unsigned short)xposi_wk & 0x000F;
  signed char scd_data = scdtbl[scd_no][xposi_wk];
  blk_no ^= blk_msk;
  if (BIT_IS_SET(blk_no, 11)) {
    scd_data = -scd_data;
  }
  if (scd_data == 0) {
    return 16;
  }
  if (scd_data >= 0) {
    if (scd_data != 16) {
      return 15 - (scd_data + (signed char)((unsigned short)yposi & 0x000F));
    }
  }
  else {
    scd_data += (signed char)((unsigned short)yposi & 0x000F);
    if (scd_data >= 0) {
      return 16;
    }
  }
  return scdend2(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
}


signed char scd2chk_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk) {
  unsigned char* p_zonemap = &g_ram.zonemapwk[8];
  if (g_ram.scd_bg_flag == 0) {
    return scdchk_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  signed char scd0 = scdchk_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  p_dirstk[1] = p_dirstk[0];
  if (yoffset < 0) {
    xposi = (xposi ^ 15) - g_ram.scr_h_posit_ofs ^ 15;
  }
  else {
    xposi -= g_ram.scr_h_posit_ofs;
  }
  yposi -= g_ram.scr_v_posit_ofs;
  p_zonemap += 2;
  signed char scd1 = scdchk_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  if (scd1 > scd0) {
    p_dirstk[0] = p_dirstk[1];
    scd1 = scd0;
  }
  return scd1;
}


static signed char scdchk_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  unsigned short blk_no = scramapad(xposi, yposi, p_zonemap);
  unsigned short blk_offset = blk_no & 0x3FF;
  if (blk_offset == 0 || !BIT_IS_SET(blk_no, solid_bit)) {
    return scdend_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  unsigned char scd_no = g_ram.scdadr[blk_no * 2];
  if (scd_no == 0) {
    return scdend_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  unsigned char direction_wk = scddirtbl[scd_no];
  short yposi_wk = yposi;
  if (BIT_IS_SET(blk_no, 11)) {
    yposi_wk = -yposi_wk - 1;
    direction_wk = direction_vmirror(direction_wk);
  }
  if (BIT_IS_SET(blk_no, 10)) {
    direction_wk = direction_hmirror(direction_wk);
  }
  *p_dirstk = direction_wk;
  yposi_wk = (unsigned short)yposi_wk & 0x000F;
  signed char scd_data = scdtbl[scd_no][yposi_wk];
  blk_no ^= blk_msk;
  if (BIT_IS_SET(blk_no, 10)) {
    scd_data = -scd_data;
  }
  if (scd_data == 0) {
    return scdend_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  }
  if (scd_data >= 0) {
    if (scd_data != 16) {
      return 15 - (scd_data + (signed char)((unsigned short)xposi & 0x000F));
    }
  }
  else {
    scd_data += (signed char)((unsigned short)xposi & 0x000F);
    if (scd_data >= 0) {
      return scdend_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
    }
  }
  return scdend2_r(xposi, yposi, yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
}


static signed char scdend_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  signed char scd = scdchk2_r(xposi, yposi + yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  return scd + 16;
}


static signed char scdend2_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  signed char scd = scdchk2_r(xposi, yposi + yoffset, blk_msk, solid_bit, p_dirstk, p_zonemap);
  return scd - 16;
}


static signed char scdchk2_r(short xposi, short yposi, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk, unsigned char* p_zonemap) {
  unsigned short blk_no = scramapad(xposi, yposi, p_zonemap);
  unsigned short blk_offset = blk_no & 0x3FF;
  if (blk_offset == 0 || !BIT_IS_SET(blk_no, solid_bit)) {
    return 15 - (signed char)((unsigned short)xposi & 0x000F);
  }
  unsigned char scd_no = g_ram.scdadr[blk_no * 2];
  if (scd_no == 0) {
    return 15 - (signed char)((unsigned short)xposi & 0x000F);
  }
  unsigned char direction_wk = scddirtbl[scd_no];
  short yposi_wk = yposi;
  if (BIT_IS_SET(blk_no, 11)) {
    yposi_wk = -yposi_wk - 1;
    direction_wk = direction_vmirror(direction_wk);
  }
  if (BIT_IS_SET(blk_no, 10)) {
    direction_wk = direction_hmirror(direction_wk);
  }
  *p_dirstk = direction_wk;
  yposi_wk = (unsigned short)yposi_wk & 0x000F;
  signed char scd_data = scdtbl2[scd_no][yposi_wk];
  blk_no ^= blk_msk;
  if (BIT_IS_SET(blk_no, 10)) {
    scd_data = -scd_data;
  }
  if (scd_data == 0) {
    return 15 - (signed char)((unsigned short)xposi & 0x000F);
  }
  if (scd_data >= 0) {
    return 15 - (scd_data + (signed char)((unsigned short)xposi & 0x000F));
  }
  scd_data += (signed char)((unsigned short)xposi & 0x000F);
  if (scd_data >= 0) {
    return 15 - (signed char)((unsigned short)xposi & 0x000F);
  }
  return -scd_data - 1;
}
