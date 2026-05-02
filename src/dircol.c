#include "dircol.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "utils/fp16.h"
#include "fcol.h"
static SKC_dircol_result dircol(SKC_sprite_status* p_actwk, unsigned char direc);
static SKC_dircol_result vsdircolm(SKC_sprite_status* p_actwk, unsigned char direc);
static SKC_dircol_result vsdircol(SKC_sprite_status* p_actwk, unsigned char direc);
static SKC_dircol_result dircolchk(signed char scd0, signed char scd1, unsigned char direc);
static SKC_dircol_result dircolchk1(signed char scd, unsigned char direc);

extern sonic3_ram g_ram;


SKC_dircol_result dircolm(SKC_sprite_status* p_actwk, unsigned char direc) {
  if (g_ram.vs_flag != 0) {
    return vsdircolm(p_actwk, direc);
  }
  return dircol(p_actwk, direc);
}


static SKC_dircol_result dircol(SKC_sprite_status* p_actwk, unsigned char direc) {
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  long xposi = p_actwk->xposi + (long)p_actwk->xspeed * 0x100;
  long yspeed = p_actwk->yspeed;
  if (g_ram.reverse_gravity_flag != 0) {
    yspeed = -yspeed;
  }
  long yposi = p_actwk->yposi + yspeed * 0x100;
  g_ram.dirstk[0] = direc;
  g_ram.dirstk[2] = direc;
  unsigned char direc_wrk = direc + 32;
  direc_wrk &= 0xFF;
  if (direc_wrk >= 128) {
    direc_wrk = direc;
    if (direc_wrk >= 128) {
      --direc_wrk;
    }
    direc_wrk += 32;
  }
  else {
    direc_wrk = direc;
    if (direc_wrk >= 128) {
      ++direc_wrk;
    }
    direc_wrk += 31;
  }
  SKC_dircol_result result;

  switch (direc_wrk & 0xC0) {
    case   0: result = dircol_d3(p_actwk, xposi, yposi);
    case 128: result = dircol_u3(p_actwk, xposi, yposi);
    default:
      if (g_ram.vs_flag == 0 && !(direc & 0x38)) {
        yposi += 8;
      }

      switch (direc_wrk & 0xC0) {
        case 64: result = dircol_l3(p_actwk, xposi, yposi);
        default: result = dircol_r3(p_actwk, xposi, yposi);
      }
      break;
  }

  return result;
}


static SKC_dircol_result vsdircolm(SKC_sprite_status* p_actwk, unsigned char direc) {
  return vsdircol(p_actwk, direc);
}


static SKC_dircol_result vsdircol(SKC_sprite_status* p_actwk, unsigned char direc) {
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  long xposi = p_actwk->xposi + (long)p_actwk->xspeed * 0x100;
  long yposi = p_actwk->yposi + (long)p_actwk->yspeed * 0x100;
  g_ram.dirstk[0] = direc;
  g_ram.dirstk[2] = direc;
  unsigned char direc_wrk = direc + 32;
  direc_wrk &= 0xFF;
  if (direc_wrk >= 128) {
    direc_wrk = direc;
    if (direc_wrk >= 128) {
      --direc_wrk;
    }
    direc_wrk += 32;
  }
  else {
    direc_wrk = direc;
    if (direc_wrk >= 128) {
      ++direc_wrk;
    }
    direc_wrk += 31;
  }
  SKC_dircol_result result;

  switch (direc_wrk & 0xC0) {
    case   0: result = vsdircol_d(p_actwk, xposi, yposi);
    case 128: result = vsdircol_u(p_actwk, xposi, yposi);
    case  64: result = vsdircol_l(p_actwk, xposi, yposi);
     default: result = vsdircol_r(p_actwk, xposi, yposi);
  }

  return result;
}


SKC_dircol_result dircol2(SKC_sprite_status* p_actwk, unsigned char direc) {
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  g_ram.dirstk[0] = direc;
  g_ram.dirstk[2] = direc;
  unsigned char direc_wrk = direc + 32;
  SKC_dircol_result result;

  switch (direc_wrk & 0xC0) {
    case  64: result = dircol_l(p_actwk); break;
    case 128: result = dircol_u(p_actwk); break;
    case 192: result = dircol_r(p_actwk); break;
     default: result = dircol_d(p_actwk); break;
  }

  return result;
}


static SKC_dircol_result dircolchk(signed char scd0, signed char scd1, unsigned char direc) {
  SKC_dircol_result result = { scd1, scd0, g_ram.dirstk[2] };
  if (scd1 > scd0) {
    result.direc = g_ram.dirstk[0];
    result.offset = scd0;
    result.offset2 = scd1;
  }
  if (result.direc & 1) {
    result.direc = direc;
  }
  return result;
}


static SKC_dircol_result dircolchk1(signed char scd, unsigned char direc) {
  SKC_dircol_result result = { scd, scd, g_ram.dirstk[0] };
  if (result.direc & 1) {
    result.direc = direc;
  }
  return result;
}


SKC_dircol_result dircol_d(SKC_sprite_status* p_actwk) {
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  short xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprhsize;
  short yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  signed char scd0 = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprhsize;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  signed char scd1 = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[2]);
  return dircolchk(scd0, scd1, 0);
}


SKC_dircol_result dircol_d2(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi);
  return dircol_d3(p_actwk, xposi, yposi);
}


SKC_dircol_result dircol_d3(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  signed char scd = scd2chk(xposi, yposi + 10, 16, 0x0000, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 0);
}


SKC_dircol_result vsdircol_d(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  yposi += (short)p_actwk->sprhsize;
  signed char scd = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 0);
}


SKC_dircol_result crushchk_d(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi) - 4;
  g_ram.scdadr = p_actwk->u.play.lrb_solid_bit == 13 ? g_ram.scd0adr : g_ram.scd1adr;
  g_ram.dirstk[0] = 0;
  signed char scd = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 0);
}


SKC_dircol_result edgechk_d(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  return edgechk_d2(p_actwk, xposi);
}


SKC_dircol_result edgechk_d2(SKC_sprite_status* p_actwk, short xposi) {
  short yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  return edgechk_d3(p_actwk, xposi, yposi);
}


SKC_dircol_result edgechk_d3(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  g_ram.dirstk[0] = 0;
  signed char scd = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 0);
}


SKC_dircol_result landchk_d(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  g_ram.dirstk[0] = 0;
  signed char scd = scd2chk(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 0);
}


SKC_dircol_result emycol_d(SKC_sprite_status* p_actwk) {
  return emycol_d2(p_actwk, fp16_get_integer(p_actwk->xposi));
}


SKC_dircol_result emycol_d2(SKC_sprite_status* p_actwk, short xposi) {
  short yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  return emycol_d3(p_actwk, xposi, yposi);
}


SKC_dircol_result emycol_d3(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  g_ram.dirstk[0] = 0;
  signed char scd = scd2chk(xposi, yposi, 16, 0x0000, 12, &g_ram.dirstk[0]);
  return dircolchk1(scd, 0);
}


SKC_dircol_result flyringcol_d(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  g_ram.dirstk[0] = 0;
  signed char scd = flyringscd2chk(xposi, yposi, 16, 0x0000, 12, &g_ram.dirstk[0]);
  SKC_dircol_result result = { scd, 0 };
  return result;
}


SKC_dircol_result dircol_r(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprvsize;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprhsize;
  signed char scd0 = scd2chk_r(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprvsize;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprhsize;
  signed char scd1 = scd2chk_r(xposi, yposi, 16, 0x0000, p_actwk->u.play.top_solid_bit, &g_ram.dirstk[2]);
  return dircolchk(scd0, scd1, 192);
}


SKC_dircol_result rideobjcol_r(SKC_sprite_status* p_actwk, unsigned char solid_bit) {
  short xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprhsize;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize;
  signed char scd0 = scd2chk_r(xposi, yposi, 16, 0x0000, solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprhsize;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  signed char scd1 = scd2chk_r(xposi, yposi, 16, 0x0000, solid_bit, &g_ram.dirstk[2]);
  return dircolchk(scd0, scd1, 192);
}


SKC_dircol_result dircol_r2(SKC_sprite_status* p_actwk) {
  if (g_ram.vs_flag != 0) {
    return vsdircol_r(p_actwk, fp16_get_integer(p_actwk->xposi), fp16_get_integer(p_actwk->yposi));
  }
  return dircol_r3(p_actwk, fp16_get_integer(p_actwk->xposi), fp16_get_integer(p_actwk->yposi));
}


SKC_dircol_result dircol_r3(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  signed char scd = scd2chk_r(xposi + 10, yposi, 16, 0x0000, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 192);
}


SKC_dircol_result vsdircol_r(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  signed char scd = scd2chk_r(xposi, yposi + p_actwk->sprhsize, 16, 0x0000, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 192);
}


SKC_dircol_result emycol_r(SKC_sprite_status* p_actwk, short sprhs) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi) + sprhs;
  g_ram.dirstk[0] = 0;
  signed char scd = scd2chk_r(xposi, yposi, 16, 0x0000, 13, &g_ram.dirstk[0]);
  return dircolchk1(scd, 192);
}


SKC_dircol_result dircol_u(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) + (short)p_actwk->sprhsize;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  signed char scd0 = scd2chk(xposi, yposi, -16, 0x0800, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprhsize;
  yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  signed char scd1 = scd2chk(xposi, yposi, -16, 0x0800, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[2]);
  return dircolchk(scd0, scd1, 128);
}


SKC_dircol_result rideobjcol_u(SKC_sprite_status* p_actwk, unsigned char solid_bit) {
  short xposi = fp16_get_integer(p_actwk->xposi) + ((short)p_actwk->sprhsize - 2);
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  signed char scd0 = scd2chk(xposi, yposi, -16, 0x0800, solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) - ((short)p_actwk->sprhsize - 2);
  yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  signed char scd1 = scd2chk(xposi, yposi, -16, 0x0800, solid_bit, &g_ram.dirstk[2]);
  return dircolchk(scd0, scd1, 128);
}


SKC_dircol_result dircol_u2(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi);
  return dircol_u3(p_actwk, xposi, yposi);
}


SKC_dircol_result dircol_u3(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  signed char scd = scd2chk(xposi, yposi - 10 ^ 15, -16, 0x0800, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 128);
}


SKC_dircol_result vsdircol_u(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  signed char scd = scd2chk(xposi, yposi - p_actwk->sprhsize ^ 15, -16, 0x0800, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 128);
}


SKC_dircol_result emycol_u(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  signed char scd = scd2chk(xposi, yposi, -16, 0x0800, 13, &g_ram.dirstk[0]);
  return dircolchk1(scd, 128);
}


SKC_dircol_result flyringcol_u(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi);
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize ^ 15;
  g_ram.dirstk[0] = 0;
  signed char scd = flyringscd2chk(xposi, yposi, -16, 0x0800, 12, &g_ram.dirstk[0]);
  SKC_dircol_result result = { scd, 128 };
  return result;
}


SKC_dircol_result dircol_l(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprvsize ^ 15;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprhsize;
  signed char scd0 = scd2chk_r(xposi, yposi, -16, 0x0400, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprvsize ^ 15;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprhsize;
  signed char scd1 = scd2chk_r(xposi, yposi, -16, 0x0400, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[2]);
  return dircolchk(scd0, scd1, 64);
}


SKC_dircol_result rideobjcol_l(SKC_sprite_status* p_actwk, unsigned char solid_bit) {
  short xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprhsize ^ 15;
  short yposi = fp16_get_integer(p_actwk->yposi) - (short)p_actwk->sprvsize;
  signed char scd0 = scd2chk_r(xposi, yposi, -16, 0x0400, solid_bit, &g_ram.dirstk[0]);
  xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprhsize ^ 15;
  yposi = fp16_get_integer(p_actwk->yposi) + (short)p_actwk->sprvsize;
  signed char scd1 = scd2chk_r(xposi, yposi, -16, 0x0400, solid_bit, &g_ram.dirstk[2]);
  return dircolchk(scd0, scd1, 64);
}


SKC_dircol_result dircol_l2(SKC_sprite_status* p_actwk) {
  if (g_ram.vs_flag != 0) {
    return vsdircol_l(p_actwk, fp16_get_integer(p_actwk->xposi), fp16_get_integer(p_actwk->yposi));
  }
  return dircol_l3(p_actwk, fp16_get_integer(p_actwk->xposi), fp16_get_integer(p_actwk->yposi));
}


SKC_dircol_result dircol_l3(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  signed char scd = scd2chk_r(xposi - 10 ^ 15, yposi, -16, 0x0400, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 64);
}


SKC_dircol_result vsdircol_l(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  signed char scd = scd2chk_r(xposi - p_actwk->sprhsize ^ 15, yposi, -16, 0x0400, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 64);
}


SKC_dircol_result vsdircol_l2(SKC_sprite_status* p_actwk) {
  g_ram.scdadr = p_actwk->u.play.top_solid_bit == 12 ? g_ram.scd0adr : g_ram.scd1adr;
  short xposi = fp16_get_integer(p_actwk->xposi) - (short)p_actwk->sprvsize ^ 15;
  short yposi = fp16_get_integer(p_actwk->yposi);
  g_ram.dirstk[0] = 0;
  signed char scd = scd2chk_r(xposi, yposi, -16, 0x0400, p_actwk->u.play.lrb_solid_bit, &g_ram.dirstk[0]);
  return dircolchk1(scd, 64);
}


SKC_dircol_result emycol_l(SKC_sprite_status* p_actwk, short sprhs) {
  short xposi = fp16_get_integer(p_actwk->xposi) + sprhs ^ 15;
  return emycol_l2(p_actwk, xposi);
}


SKC_dircol_result emycol_l2(SKC_sprite_status* p_actwk, short xposi) {
  short yposi = fp16_get_integer(p_actwk->yposi);
  return emycol_l3(p_actwk, xposi, yposi);
}


SKC_dircol_result emycol_l3(SKC_sprite_status* p_actwk, short xposi, short yposi) {
  g_ram.dirstk[0] = 0;
  signed char scd = scd2chk_r(xposi, yposi, -16, 0x0400, 13, &g_ram.dirstk[0]);
  return dircolchk1(scd, 64);
}
