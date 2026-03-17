#include "toge.h"
#include <stdbool.h>
#include "../types/hitchkdata.h"
#include "../types/hitchkresult.h"
#include "../types/size.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/fp8.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../constants.h"
#include "../hitchk.h"
#include "../sound.h"
static void togeinit(SKC_sprite_status* p_actwk);
static void vstogeinit(SKC_sprite_status* p_actwk, unsigned char size_kind);
static void togemove(SKC_sprite_status* p_actwk);
static void togemove2(SKC_sprite_status* p_actwk);
static void togemove3(SKC_sprite_status* p_actwk);
static void vstogemove(SKC_sprite_status* p_actwk);
static void vstogemove2(SKC_sprite_status* p_actwk);
static void vstogemove3(SKC_sprite_status* p_actwk);
static void togekind(SKC_sprite_status* p_actwk);
static void toge_no(SKC_sprite_status* p_actwk);
static void toge_ymove(SKC_sprite_status* p_actwk);
static void toge_xmove(SKC_sprite_status* p_actwk);
static void toge_sub(SKC_sprite_status* p_actwk);
static void toge_push(SKC_sprite_status* p_actwk);
static void toge_push__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void vstogekind(SKC_sprite_status* p_actwk);
static void vstoge_ymove(SKC_sprite_status* p_actwk);
static void vstoge_xmove(SKC_sprite_status* p_actwk);
static void vstoge_sub(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern togesp00;
static SKC_sprite_pattern togesp01;
static SKC_sprite_pattern togesp02;
static SKC_sprite_pattern togesp03;
static SKC_sprite_pattern togesp04;
static SKC_sprite_pattern togesp05;
static SKC_sprite_pattern togesp06;
static SKC_sprite_pattern togesp07;
static SKC_sprite_pattern vstogesp00;
static SKC_sprite_pattern vstogesp01;
static SKC_sprite_pattern vstogesp02;
static SKC_sprite_pattern vstogesp03;
static SKC_sprite_pattern vstogesp04;
static SKC_sprite_pattern vstogesp05;
static SKC_sprite_pattern vstogesp06;
static SKC_sprite_pattern vstogesp07;

extern sonic3_ram g_ram;


void toge(SKC_sprite_status* p_actwk) {
  togeinit(p_actwk);
}


static void togeinit(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  unsigned char size_kind = (p_actwk->u.obj.userflag & 0xF0) >> 4;
  if (g_ram.vs_flag != 0) {
    vstogeinit(p_actwk, size_kind);
  }
  else {
    SKC_size togetbl[8] = {
      { 16, 16 },
      { 32, 16 },
      { 48, 16 },
      { 64, 16 },
      { 16, 16 },
      { 16, 32 },
      { 16, 48 },
      { 16, 64 }
    };

    p_actwk->sprhs = togetbl[size_kind].w;
    p_actwk->sprvs = togetbl[size_kind].h;
    p_actwk->r_ptr = &togemove;
    p_actwk->patbase = togepat;
    p_actwk->sproffset = get_zone(g_ram.stageno) != FLYING_BATTERY ? 0x049C : 0x0200;
    p_actwk->patno = size_kind;
    if (size_kind >= 4) {
      p_actwk->r_ptr = &togemove2;
      p_actwk->sproffset = 0x0494;
    }
    if ((g_ram.reverse_gravity_flag == 0 && p_actwk->u.obj.cddat.down == 1)
        || (g_ram.reverse_gravity_flag != 0 && p_actwk->u.obj.cddat.down == 0)) {
      p_actwk->r_ptr = &togemove3;
    }
    p_actwk->u.obj.actfree.toge.push_distance = 32;
    p_actwk->u.obj.actfree.toge.xposi_init = fp16_get_integer(p_actwk->xposi);
    p_actwk->u.obj.actfree.toge.yposi_init = fp16_get_integer(p_actwk->yposi);
    p_actwk->u.obj.userflag &= 0xF;
  }
}


static void vstogeinit(SKC_sprite_status* p_actwk, unsigned char size_kind) {
  SKC_size vstogetbl[8] = {
    { 12, 12 },
    { 24, 12 },
    { 36, 12 },
    { 48, 12 },
    { 12, 12 },
    { 12, 24 },
    { 12, 36 },
    { 12, 48 }
  };

  p_actwk->sprhs = vstogetbl[size_kind].w;
  p_actwk->sprvs = vstogetbl[size_kind].h;
  p_actwk->r_ptr = &vstogemove;
  p_actwk->patbase = vstogepat;
  p_actwk->sproffset = 0x0391;
  p_actwk->patno = size_kind;
  if (size_kind >= 4) {
    p_actwk->r_ptr = &vstogemove2;
  }
  if (p_actwk->u.obj.cddat.down == 1) {
    p_actwk->r_ptr = &vstogemove3;
  }
  p_actwk->u.obj.actfree.toge.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.actfree.toge.yposi_init = fp16_get_integer(p_actwk->yposi);
  p_actwk->u.obj.userflag &= 0xF;
}


static void togemove(SKC_sprite_status* p_actwk) {
  togekind(p_actwk);
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  if (p_actwk->u.obj.cddat.plride == 1) {
    togedamegesub(p_actwk, &g_ram.actwk[0]);
  }
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    togedamegesub(p_actwk, &g_ram.actwk[1]);
  }
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.toge.xposi_init);
}


static void togemove2(SKC_sprite_status* p_actwk) {
  togekind(p_actwk);
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_SIDE) {
    togedamegesub(p_actwk, &g_ram.actwk[0]);
    p_actwk->u.obj.cddat.plpush = 0;
  }
  if (result.plcoli[1] == HITCHK_COLI_SIDE) {
    togedamegesub(p_actwk, &g_ram.actwk[1]);
    p_actwk->u.obj.cddat.pl2push = 0;
  }
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.toge.xposi_init);
}


static void togemove3(SKC_sprite_status* p_actwk) {
  togekind(p_actwk);
  SKC_hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
    togedamegesub(p_actwk, &g_ram.actwk[0]);
  }
  if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
    togedamegesub(p_actwk, &g_ram.actwk[1]);
  }
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.toge.xposi_init);
}


static void vstogemove(SKC_sprite_status* p_actwk) {
  vstogekind(p_actwk);
  SKC_hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  if (p_actwk->u.obj.cddat.plride == 1) {
    togedamegesub(p_actwk, &g_ram.actwk[0]);
  }
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    togedamegesub(p_actwk, &g_ram.actwk[1]);
  }
  actionsub(p_actwk);
}


static void vstogemove2(SKC_sprite_status* p_actwk) {
  vstogekind(p_actwk);
  SKC_hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_SIDE) {
    togedamegesub(p_actwk, &g_ram.actwk[0]);
    p_actwk->u.obj.cddat.plpush = 1;
  }
  if (result.plcoli[1] == HITCHK_COLI_SIDE) {
    togedamegesub(p_actwk, &g_ram.actwk[1]);
    p_actwk->u.obj.cddat.pl2push = 1;
  }
  actionsub(p_actwk);
}


static void vstogemove3(SKC_sprite_status* p_actwk) {
  vstogekind(p_actwk);
  SKC_hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  SKC_hitchk_result result = hitchk(p_actwk, data);
  if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
    togedamegesub(p_actwk, &g_ram.actwk[0]);
  }
  if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
    togedamegesub(p_actwk, &g_ram.actwk[1]);
  }
  actionsub(p_actwk);
}


void togedamegesub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.muteki == 1) return;
  if (p_playerwk->u.play.invulnerability_timer != 0) return;
  if (p_playerwk->r_no >= 4) return;

  p_playerwk->yposi -= p_playerwk->yspeed * 0x100;
  playdamageset(p_playerwk, p_actwk);
}


static void togekind(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler togekindtbl[4] = {
    &toge_no,
    &toge_ymove,
    &toge_xmove,
    &toge_push
  };

  togekindtbl[p_actwk->u.obj.userflag](p_actwk);
}


static void toge_no(SKC_sprite_status* p_actwk) {
}


static void toge_ymove(SKC_sprite_status* p_actwk) {
  toge_sub(p_actwk);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.toge.offset) + p_actwk->u.obj.actfree.toge.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static void toge_xmove(SKC_sprite_status* p_actwk) {
  toge_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.toge.offset) + p_actwk->u.obj.actfree.toge.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
}


static void toge_sub(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0 && p_actwk->actflg.onscreen == 1) {
      soundset(82);
    }
  }
  else if (p_actwk->u.obj.actfree.toge.reverse_dir) {
    p_actwk->u.obj.actfree.toge.offset -= 0x800;
    if (p_actwk->u.obj.actfree.toge.offset < 0) {
      p_actwk->u.obj.actfree.toge.offset = 0;
      p_actwk->u.obj.actfree.toge.reverse_dir = false;
      p_actwk->u.obj.timer = 60;
    }
  }
  else {
    p_actwk->u.obj.actfree.toge.offset += 0x800;
    if (p_actwk->u.obj.actfree.toge.offset >= 0x2000) {
      p_actwk->u.obj.actfree.toge.offset = 0x2000;
      p_actwk->u.obj.actfree.toge.reverse_dir = true;
      p_actwk->u.obj.timer = 60;
    }
  }
}


static void toge_push(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.plpush == 1 || p_actwk->u.obj.cddat.pl2push == 1) {
    toge_push__sub(p_actwk, &g_ram.actwk[0]);
    toge_push__sub(p_actwk, &g_ram.actwk[1]);
  }
  p_actwk->u.obj.actfree.toge.prev_plpush = g_ram.actwk[0].u.play.cddat.push;
  p_actwk->u.obj.actfree.toge.prev_pl2push = g_ram.actwk[1].u.play.cddat.push;
}


static void toge_push__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk == &g_ram.actwk[0] && p_actwk->u.obj.cddat.plpush) return;
  if (p_playerwk == &g_ram.actwk[1] && p_actwk->u.obj.cddat.pl2push) return;
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) < (unsigned short)fp16_get_integer(p_playerwk->xposi)) return;
  if (p_playerwk == &g_ram.actwk[0] && !p_actwk->u.obj.actfree.toge.prev_plpush) return;
  if (p_playerwk == &g_ram.actwk[1] && !p_actwk->u.obj.actfree.toge.prev_pl2push) return;
  if (p_actwk->u.obj.actfree.toge.push_timer-- > 0) return;

  p_actwk->u.obj.actfree.toge.push_timer = 16;
  if (p_actwk->u.obj.actfree.toge.push_distance != 0) {
    --p_actwk->u.obj.actfree.toge.push_distance;
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 1);
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 1);
  }
}


static void vstogekind(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler vstogekindtbl[3] = {
    &toge_no,
    &vstoge_ymove,
    &vstoge_xmove
  };

  vstogekindtbl[p_actwk->u.obj.userflag](p_actwk);
}


static void vstoge_ymove(SKC_sprite_status* p_actwk) {
  vstoge_sub(p_actwk);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.toge.offset) + p_actwk->u.obj.actfree.toge.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static void vstoge_xmove(SKC_sprite_status* p_actwk) {
  vstoge_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.toge.offset) + p_actwk->u.obj.actfree.toge.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
}


static void vstoge_sub(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0 && p_actwk->actflg.onscreen == 1) {
      soundset(82);
    }
  }
  else if (p_actwk->u.obj.actfree.toge.reverse_dir) {
    p_actwk->u.obj.actfree.toge.offset -= 0x800;
    if (p_actwk->u.obj.actfree.toge.offset < 0) {
      p_actwk->u.obj.actfree.toge.offset = 0;
      p_actwk->u.obj.actfree.toge.reverse_dir = false;
      p_actwk->u.obj.timer = 60;
    }
  }
  else {
    p_actwk->u.obj.actfree.toge.offset += 0x800;
    if (p_actwk->u.obj.actfree.toge.offset >= 0x1800) {
      p_actwk->u.obj.actfree.toge.offset = 0x1800;
      p_actwk->u.obj.actfree.toge.reverse_dir = 1;
      p_actwk->u.obj.timer = 60;
    }
  }
}


SKC_sprite_pattern* togepat[8] = {
  &togesp00,
  &togesp01,
  &togesp02,
  &togesp03,
  &togesp04,
  &togesp05,
  &togesp06,
  &togesp07
};


static SKC_sprite_pattern togesp00 = {
  2,
  {
    { -16, 7, 0x0000, -16 },
    { -16, 7, 0x0000,   0 }
  }
};
static SKC_sprite_pattern togesp01 = {
  4,
  {
    { -16, 7, 0x0000, -32 },
    { -16, 7, 0x0000, -16 },
    { -16, 7, 0x0000,   0 },
    { -16, 7, 0x0000,  16 }
  }
};
static SKC_sprite_pattern togesp02 = {
  6,
  {
    { -16, 7, 0x0000, -48 },
    { -16, 7, 0x0000, -32 },
    { -16, 7, 0x0000, -16 },
    { -16, 7, 0x0000,   0 },
    { -16, 7, 0x0000,  16 },
    { -16, 7, 0x0000,  32 }
  }
};
static SKC_sprite_pattern togesp03 = {
  8,
  {
    { -16, 7, 0x0000, -64 },
    { -16, 7, 0x0000, -48 },
    { -16, 7, 0x0000, -32 },
    { -16, 7, 0x0000, -16 },
    { -16, 7, 0x0000,   0 },
    { -16, 7, 0x0000,  16 },
    { -16, 7, 0x0000,  32 },
    { -16, 7, 0x0000,  48 }
  }
};
static SKC_sprite_pattern togesp04 = {
  2,
  {
    { -16, 13, 0x0800, -16 },
    {   0, 13, 0x0800, -16 }
  }
};
static SKC_sprite_pattern togesp05 = {
  4,
  {
    { -32, 13, 0x0800, -16 },
    { -16, 13, 0x0800, -16 },
    {   0, 13, 0x0800, -16 },
    {  16, 13, 0x0800, -16 }
  }
};
static SKC_sprite_pattern togesp06 = {
  6,
  {
    { -48, 13, 0x0800, -16 },
    { -32, 13, 0x0800, -16 },
    { -16, 13, 0x0800, -16 },
    {   0, 13, 0x0800, -16 },
    {  16, 13, 0x0800, -16 },
    {  32, 13, 0x0800, -16 }
  }
};
static SKC_sprite_pattern togesp07 = {
  8,
  {
    { -64, 13, 0x0800, -16 },
    { -48, 13, 0x0800, -16 },
    { -32, 13, 0x0800, -16 },
    { -16, 13, 0x0800, -16 },
    {   0, 13, 0x0800, -16 },
    {  16, 13, 0x0800, -16 },
    {  32, 13, 0x0800, -16 },
    {  48, 13, 0x0800, -16 }
  }
};


SKC_sprite_pattern* vstogepat[8] = {
  &vstogesp00,
  &vstogesp01,
  &vstogesp02,
  &vstogesp03,
  &vstogesp04,
  &vstogesp05,
  &vstogesp06,
  &vstogesp07
};


static SKC_sprite_pattern vstogesp00 = {
  1,
  {
    { -12, 10, 0x0013, -12 }
  }
};
static SKC_sprite_pattern vstogesp01 = {
  2,
  {
    { -12, 10, 0x0013, -24 },
    { -12, 10, 0x0013,   0 }
  }
};
static SKC_sprite_pattern vstogesp02 = {
  3,
  {
    { -12, 10, 0x0013, -36 },
    { -12, 10, 0x0013, -12 },
    { -12, 10, 0x0013,  12 }
  }
};
static SKC_sprite_pattern vstogesp03 = {
  4,
  {
    { -12, 10, 0x0013, -48 },
    { -12, 10, 0x0013, -24 },
    { -12, 10, 0x0013,   0 },
    { -12, 10, 0x0013,  24 }
  }
};
static SKC_sprite_pattern vstogesp04 = {
  1,
  {
    { -12, 10, 0x0013, -12 }
  }
};
static SKC_sprite_pattern vstogesp05 = {
  2,
  {
    { -24, 10, 0x0013, -12 },
    {   0, 10, 0x0013, -12 }
  }
};
static SKC_sprite_pattern vstogesp06 = {
  3,
  {
    { -36, 10, 0x0013, -12 },
    { -12, 10, 0x0013, -12 },
    {  12, 10, 0x0013, -12 }
  }
};
static SKC_sprite_pattern vstogesp07 = {
  4,
  {
    { -48, 10, 0x0013, -12 },
    { -24, 10, 0x0013, -12 },
    {   0, 10, 0x0013, -12 },
    {  24, 10, 0x0013, -12 }
  }
};
