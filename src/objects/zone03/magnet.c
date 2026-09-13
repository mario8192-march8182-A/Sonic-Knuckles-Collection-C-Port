#include "magnet.h"
#include <string.h>
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../utils/fp8.h"
#include "../../action.h"
#include "../../sound.h"
static void magnetinit(SKC_sprite_status* p_actwk);
static void magnetmove(SKC_sprite_status* p_actwk);
static void magnetmove1(SKC_sprite_status* p_actwk);
static void magnetmove2(SKC_sprite_status* p_actwk);
static bool magnetsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static SKC_sprite_pattern magnetsp00;
static SKC_sprite_pattern magnetsp01;
static SKC_sprite_pattern magnetsp02;
static SKC_sprite_pattern magnetsp03;
static void shooter3init(SKC_sprite_status* p_actwk);
static void shooter3move(SKC_sprite_status* p_actwk);
static void shooter3move__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void shooter3move2(SKC_sprite_status* p_actwk);
static void shooter3move2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char* p_plmode, unsigned char* p_pltimer);

extern sonic3_ram g_ram;


void magnet(SKC_sprite_status* p_actwk) {
  magnetinit(p_actwk);
}


static void magnetinit(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = magnetpat;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x3E8;
  p_actwk->sproffset.pl = 2;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 16;
  p_actwk->u.obj.actfree.magnet.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.actfree.magnet.unknown36 = ((p_actwk->u.obj.userflag & 0x0F) + 4) * 16;
  p_actwk->u.obj.actfree.magnet.unknown38 = ((p_actwk->u.obj.userflag & 0x0F) + 4) * 16 + 48;
  p_actwk->u.obj.actfree.magnet.unknown32 = (p_actwk->u.obj.userflag & 0x70) + 24;
  p_actwk->u.obj.actfree.magnet.unknown34 = ((p_actwk->u.obj.userflag & 0x70) + 24) * 2;
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_actwk->r_ptr = &magnetmove2;
  }
  else {
    p_actwk->patno = (p_actwk->u.obj.userflag & 0x70) >> 4;
    p_actwk->sprhs = (p_actwk->u.obj.userflag & 0x70) + 16;
    if (p_actwk->u.obj.cddat.right == 0) {
      p_actwk->r_ptr = &magnetmove1;
    }
    else {
      p_actwk->r_ptr = &magnetmove;
    }
  }
  p_actwk->r_ptr(p_actwk);
}


static void magnetmove(SKC_sprite_status* p_actwk) {
  short xposi = fp8_get_integer(g_ram.sysdirec3) - 48 + p_actwk->u.obj.actfree.magnet.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  magnetmove1(p_actwk);
}


static void magnetmove1(SKC_sprite_status* p_actwk) {
  bool pl = magnetsub(p_actwk, &g_ram.actwk[0]);
  bool pl2 = magnetsub(p_actwk, &g_ram.actwk[1]);
  if ((pl || pl2) && !(g_ram.gametimer & 0x1F)) {
    soundset(114);
  }
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.magnet.xposi_init);
}


static void magnetmove2(SKC_sprite_status* p_actwk) {
  bool pl = magnetsub(p_actwk, &g_ram.actwk[0]);
  bool pl2 = magnetsub(p_actwk, &g_ram.actwk[1]);
  if ((pl || pl2) && !(g_ram.gametimer & 0x1F)) {
    soundset(114);
  }
  frameoutchk3(p_actwk);
}


static bool magnetsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  bool ret = false;
  short distance = fp16_get_integer(p_playerwk->xposi)
                 - fp16_get_integer(p_actwk->xposi)
                 + p_actwk->u.obj.actfree.magnet.unknown32;
  if ((unsigned short)distance < p_actwk->u.obj.actfree.magnet.unknown34) {
    distance = fp8_get_integer(g_ram.sysdirec5)
             + fp16_get_integer(p_playerwk->yposi)
             + p_actwk->u.obj.actfree.magnet.unknown36
             - fp16_get_integer(p_actwk->yposi);
    if (distance >= 0 && distance < p_actwk->u.obj.actfree.magnet.unknown38
        && p_playerwk->r_no < 4 && p_playerwk->u.play.control_bitfield == 0) {
      distance -= p_actwk->u.obj.actfree.magnet.unknown36;
      if (distance >= 0) {
        distance = (-distance - 1) * 2;
      }
      distance = -(distance + p_actwk->u.obj.actfree.magnet.unknown36) / 16;
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_playerwk->yposi) + distance);
      p_playerwk->u.play.cddat.jump = 1;
      p_playerwk->u.play.cddat.ballj = 0;
      p_playerwk->yspeed = 0;
      p_playerwk->u.play.talent_status = 0;
      p_playerwk->u.play.jump_flag = 0;
      ret = true;
      p_playerwk->mspeed = 1;
      if (p_playerwk->direc.b.b1 == 0) {
        p_playerwk->direc.b.b1 = 1;
        p_playerwk->mstno = 0;
        p_playerwk->u.play.flip_rev_cnt = 127;
        p_playerwk->u.play.flip_rev_frame_cnt = 8;
      }
    }
  }
  return ret;
}


SKC_sprite_pattern* magnetpat[8] = {
  &magnetsp00,
  &magnetsp01,
  &magnetsp02,
  &magnetsp03,
  &magnetsp03,
  &magnetsp03,
  &magnetsp03,
  &magnetsp03
};


static SKC_sprite_pattern magnetsp00 = {
  2,
  {
    { -16, 12, 0xFF1C, -16 },
    {  -8, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern magnetsp01 = {
  4,
  {
    { -16, 12, 0xFF1C, -32 },
    {  -8, 13, 0x0000, -32 },
    { -16, 12, 0xFF1C,   0 },
    {  -8, 13, 0x0000,   0 }
  }
};
static SKC_sprite_pattern magnetsp02 = {
  6,
  {
    { -16, 12, 0xFF1C, -48 },
    {  -8, 13, 0x0000, -48 },
    { -16, 12, 0xFF1C, -16 },
    {  -8, 13, 0x0000, -16 },
    { -16, 12, 0xFF1C,  16 },
    {  -8, 13, 0x0000,  16 }
  }
};
static SKC_sprite_pattern magnetsp03 = {
  8,
  {
    { -16, 12, 0xFF1C, -64 },
    {  -8, 13, 0x0000, -64 },
    { -16, 12, 0xFF1C, -32 },
    {  -8, 13, 0x0000, -32 },
    { -16, 12, 0xFF1C,   0 },
    {  -8, 13, 0x0000,   0 },
    { -16, 12, 0xFF1C,  32 },
    {  -8, 13, 0x0000,  32 }
  }
};


void shooter3(SKC_sprite_status* p_actwk) {
  shooter3init(p_actwk);
}


static void shooter3init(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.userflag != 0) {
    p_actwk->u.obj.actfree.shooter3.timer_init = p_actwk->u.obj.userflag * 2;
  }
  p_actwk->r_ptr = p_actwk->u.obj.userflag != 0 ? &shooter3move2 : &shooter3move;
  p_actwk->r_ptr(p_actwk);
}


static void shooter3move(SKC_sprite_status* p_actwk) {
  shooter3move__sub(p_actwk, &g_ram.actwk[0]);
  shooter3move__sub(p_actwk, &g_ram.actwk[1]);
  frameoutchk3(p_actwk);
}


static void shooter3move__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  short xdistance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi);
  if (p_actwk->u.obj.cddat.right == 0) {
    xdistance = -xdistance;
  }
  xdistance += 80;
  if ((unsigned short)xdistance < 160) {
    short ydistance = fp16_get_integer(p_playerwk->yposi) + 32 - fp16_get_integer(p_actwk->yposi);
    if (ydistance >= 0 && ydistance < 64 && p_playerwk->r_no < 4 && p_playerwk->u.play.control_bitfield == 0) {
      if (xdistance < 80) {
        p_playerwk->mspeed = p_actwk->u.obj.cddat.right == 0 ? 0x1000 : -0x1000;
        p_playerwk->xspeed = p_playerwk->mspeed;
      }
      else {
        xdistance = (xdistance - 80) * 2 + 96;
        if (p_actwk->u.obj.cddat.right == 0) {
          xdistance = -xdistance;
        }
        fp8_set_fraction(&xdistance, -fp8_get_fraction(xdistance));
        xdistance /= 16;
        fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + xdistance);
        if (p_actwk->u.obj.actfree.shooter3.sound_ctr == 0) {
          soundset(116);
        }
        ++p_actwk->u.obj.actfree.shooter3.sound_ctr;
        p_actwk->u.obj.actfree.shooter3.sound_ctr &= 0x1F;
      }
    }
  }
}


static void shooter3move2(SKC_sprite_status* p_actwk) {
  shooter3move2__sub(p_actwk, &g_ram.actwk[0], &p_actwk->u.obj.actfree.shooter3.plmode, &p_actwk->u.obj.actfree.shooter3.pltimer);
  shooter3move2__sub(p_actwk, &g_ram.actwk[1], &p_actwk->u.obj.actfree.shooter3.pl2mode, &p_actwk->u.obj.actfree.shooter3.pl2timer);
  frameoutchk3(p_actwk);
}


static void shooter3move2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char* p_plmode, unsigned char* p_pltimer) {
  switch (*p_plmode) {
    case 0: {
      short xdistance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + 24;
      if ((unsigned short)xdistance < 48) {
        short ydistance = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi) + 48;
        if (ydistance < 80 && p_playerwk->r_no < 4 && p_playerwk->u.play.control_bitfield == 0) {
          ydistance = -(ydistance - 80);
          if ((unsigned short)ydistance >= 64) {
            *p_plmode = 1;
            *p_pltimer = p_actwk->u.obj.actfree.shooter3.timer_init;
            soundset(115);
          }
          ydistance /= 4;
          if (p_playerwk->u.play.character != MILES) {
            ydistance /= 2;
          }
          fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - ydistance);
          if (xdistance != 24) {
            short xoffset = (unsigned short)xdistance < 24 ? 1 : -1;
            fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + xoffset);
          }
          p_playerwk->u.play.cddat.jump = 1;
          p_playerwk->mstno = 15;
          p_playerwk->u.play.jump_flag = 0;
        }
      }
      break;
    }
    case 1:
      --*p_pltimer;
      if (*p_pltimer != 0) {
        fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 8);
        short xdistance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi);
        if (xdistance != 0) {
          short xoffset = xdistance < 0 ? 1 : -1;
          fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + xoffset);
        }
        p_playerwk->xspeed = 0;
        p_playerwk->mspeed = 0;
        p_playerwk->yspeed = 0;
      }
      else {
        p_playerwk->yspeed = -0x800;
        *p_plmode = 0;
      }
      break;
    case 2:
      break;
  }
}
