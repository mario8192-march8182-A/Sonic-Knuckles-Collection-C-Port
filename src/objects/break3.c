#include "break3.h"
#include <stdbool.h>
#include "../types/break3initdata.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../action.h"
#include "../actset.h"
#include "../hitchk.h"
#include "../sound.h"
static void break3move(SKC_sprite_status* p_actwk);
static void break3move2(SKC_sprite_status* p_actwk);
static void break3down(SKC_sprite_status* p_actwk);
static void break3down__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride);
static void break3down2(SKC_sprite_status* p_actwk);
static void break3go(SKC_sprite_status* p_actwk);
static void break3gosub(SKC_sprite_status* p_actwk, SKC_break3_init_data* p_data, SKC_sprite_status_handler p_handler);
static SKC_break3_init_data break309tbl;
static SKC_sprite_pattern br090sp00;
static SKC_sprite_pattern br090sp01;
static SKC_sprite_pattern br090sp02;
static SKC_sprite_pattern br090sp03;
static SKC_sprite_pattern br090sp04;
static SKC_sprite_pattern br090sp05;
static SKC_sprite_pattern br090sp06;
static SKC_sprite_pattern br090sp07;
static SKC_sprite_pattern br090sp08;

extern sonic3_ram g_ram;


void break3(SKC_sprite_status* p_actwk) {
  struct {
    unsigned char sprhs;
    unsigned char sprvs;
    unsigned char patno;
    unsigned char userflag;
  }
  tbl09[1] = {
    { 64, 32, 8, 0 }
  };

  p_actwk->r_ptr = &break3move;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->patbase = break090pat;
  p_actwk->sproffset = 0xC0D3;
  p_actwk->u.obj.timer = (p_actwk->u.obj.userflag & 0x0F) * 16 + 8;
  unsigned char index = (p_actwk->u.obj.userflag & 0x0F) >> 4;
  p_actwk->sprhs = tbl09[index].sprhs;
  p_actwk->sprvs = tbl09[index].sprvs;
  p_actwk->patno = tbl09[index].patno;
  p_actwk->u.obj.userflag = tbl09[index].userflag;
  p_actwk->sprvsize = 28;
  break3move(p_actwk);
}


static void break3move(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.break3.unknown != 0) {
    if (p_actwk->u.obj.timer == 0) {
      break3go(p_actwk);
      return;
    }
    --p_actwk->u.obj.timer;
  }
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->u.obj.actfree.break3.unknown = 1;
  }
  break3move2(p_actwk);
}


static void break3move2(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { p_actwk->sprhs, 0, p_actwk->sprvsize, fp16_get_integer(p_actwk->xposi) };
  ridechk(p_actwk, data);
  frameoutchk(p_actwk);
}


static void break3down(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { p_actwk->sprhs, 0, p_actwk->sprvsize, fp16_get_integer(p_actwk->xposi) };
  ridechk(p_actwk, data);
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    bool plride = p_actwk->u.obj.cddat.plride;
    break3down__sub(p_actwk, &g_ram.actwk[0], &plride);
    p_actwk->u.obj.cddat.plride = plride;
    bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
    break3down__sub(p_actwk, &g_ram.actwk[1], &pl2ride);
    p_actwk->u.obj.cddat.pl2ride = pl2ride;
    frameout(p_actwk);
  }
}


static void break3down__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride) {
  if (!*p_plride) return;

  *p_plride = false;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->mstrestart = 1;
}


static void break3down2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    actionsub(p_actwk);
  }
  else {
    if (p_actwk->pattim-- == 0) {
      p_actwk->pattim = 7;
      ++p_actwk->patno;
      p_actwk->patno &= 3;
      p_actwk->patno += p_actwk->u.obj.actfree.break3.patno_offset;
    }
    speedset(p_actwk);
    if (p_actwk->actflg.onscreen == 1) {
      actionsub(p_actwk);
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void break3go(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 42;
  p_actwk->r_ptr = &break3down;
  break3gosub(p_actwk, &break309tbl, &break3down2);
}


static void break3gosub(SKC_sprite_status* p_actwk, SKC_break3_init_data* p_data, SKC_sprite_status_handler p_handler) {
  for (int i = 0; i < p_data->cnt + 1; ++i) {
    SKC_actwkchk_result result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->r_ptr = p_handler;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->actflg = p_actwk->actflg;
    short xposi = fp16_get_integer(p_actwk->xposi) + p_data->items[i].xoffset;
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    short yposi = fp16_get_integer(p_actwk->yposi) + p_data->items[i].yoffset;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
    result.actwk_ptr->patno = p_data->items[i].patno;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->sprpri = PRI_1;
    result.actwk_ptr->sprhs = 32;
    result.actwk_ptr->sprvs = 32;
    result.actwk_ptr->u.obj.timer = p_data->items[i].timer;
    result.actwk_ptr->u.obj.actfree.break3.patno_offset = result.actwk_ptr->patno & 0xFC;
  }

  if (p_actwk->u.obj.flagwork_index != 0) {
    CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    p_actwk->u.obj.flagwork_index = 0;
  }
  soundset(89);
}


static SKC_break3_init_data break309tbl = {
  15,
  {
    { -32,   4,   7,  36 },
    {   0,   8,   6,  32 },
    {  32,   4,   6,  34 },
    { -48, -16,   7,  44 },
    { -16, -16,   6,  40 },
    {  16, -16,   7,  42 },
    {  48, -16,   6,  38 },
    { -32, -24,   0,  30 },
    {  32, -24,   1,  28 },
    { -56,   0,   0,  26 },
    {  56,   0,   1,  24 },
    { -48,  16,   0,  18 },
    {  48,  16,   1,  16 },
    { -24,  16,   0,  14 },
    {  24,  16,   1,  12 },
    { -10,  20,   0,  10 },
    {  10,  20,   1,   8 },
    {   0,  24,   0,   6 },
    { -32,  24,   0,   2 },
    {  32,  24,   1,   4 },
    { -44,  12,   4,  22 },
    {  44,  12,   5,  20 }
  }
};


SKC_sprite_pattern* break090pat[9] = {
  &br090sp00,
  &br090sp01,
  &br090sp02,
  &br090sp03,
  &br090sp04,
  &br090sp05,
  &br090sp06,
  &br090sp07,
  &br090sp08
};


static SKC_sprite_pattern br090sp00 = {
  1,
  {
    { -8, 5, 0x006D, -8 }
  }
};
static SKC_sprite_pattern br090sp01 = {
  1,
  {
    { -8, 5, 0x086D, -8 }
  }
};
static SKC_sprite_pattern br090sp02 = {
  1,
  {
    { -8, 5, 0x186D, -8 }
  }
};
static SKC_sprite_pattern br090sp03 = {
  1,
  {
    { -8, 5, 0x106D, -8 }
  }
};
static SKC_sprite_pattern br090sp04 = {
  1,
  {
    { -16, 15, 0x0071, -16 }
  }
};
static SKC_sprite_pattern br090sp05 = {
  1,
  {
    { -16, 15, 0x0871, -16 }
  }
};
static SKC_sprite_pattern br090sp06 = {
  1,
  {
    { -16, 15, 0x1871, -16 }
  }
};
static SKC_sprite_pattern br090sp07 = {
  1,
  {
    { -16, 15, 0x1071, -16 }
  }
};
static SKC_sprite_pattern br090sp08 = {
  16,
  {
    { -32, 13, 0x000C, -64 },
    { -32, 13, 0x080C, -32 },
    { -32, 13, 0x000C,   0 },
    { -32, 13, 0x080C,  32 },
    { -16, 13, 0x0014, -64 },
    { -16, 13, 0x001C, -32 },
    { -16, 13, 0x081C,   0 },
    { -16, 13, 0x0814,  32 },
    {   0, 13, 0x0024, -64 },
    {   0, 13, 0x002C, -32 },
    {   0, 13, 0x082C,   0 },
    {   0, 13, 0x0824,  32 },
    {  16, 13, 0x0034, -64 },
    {  16, 13, 0x003C, -32 },
    {  16, 13, 0x083C,   0 },
    {  16, 13, 0x0834,  32 }
  }
};
