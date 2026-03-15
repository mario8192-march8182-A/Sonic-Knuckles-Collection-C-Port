#include "itemug.h"
#include "../types/enemyinit0data.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../constants.h"
#include "../action.h"
#include "../shared.h"
#include "../sound.h"
#include "item.h"
static void itemug_wait0(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data itemug_init_tbl;

extern sonic3_ram g_ram;


void itemug(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &itemug_init_tbl);
  p_actwk->r_ptr = &itemug_wait0;
  p_actwk->sprvsize = 15;
  p_actwk->sprhsize = 15;
  p_actwk->colino = 0x46;
  p_actwk->mstno = p_actwk->u.obj.userflag;
}


static void itemug_wait0(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = {
    -14, 24, -128, 192
  };

  if (g_ram.save_obj != 0
      && g_ram.actwk[g_ram.save_obj].r_ptr == &kanban
      && g_ram.actwk[g_ram.save_obj].u.obj.actflg0.puka_down == 1) {
    SKC_sprite_status* p_savewk = &g_ram.actwk[g_ram.save_obj];
    short xposi = fp16_get_integer(p_actwk->xposi) + col_tbl[0];
    short yposi = fp16_get_integer(p_actwk->yposi) + col_tbl[2];
    if (fp16_get_integer(p_savewk->xposi) < xposi
        || fp16_get_integer(p_savewk->xposi) >= xposi + col_tbl[1]
        || fp16_get_integer(p_savewk->yposi) < yposi
        || fp16_get_integer(p_savewk->yposi) >= yposi + col_tbl[3]) {
      soundset(126);
      p_actwk->r_ptr = &frameoutchk;
    }
    else {
      p_savewk->u.obj.actflg0.puka_down = 0;
      p_actwk->r_ptr = &item;
      p_actwk->r_no = 2;
      p_actwk->u.obj.actfree.item.unknown = 4;
      p_actwk->yspeed = -0x500;
      soundset(68);
      if (p_actwk->actflg.hflip == 1) {
        p_actwk->actflg.hflip = 0;
        SET_BIT(p_actwk->sproffset, 15);
        p_actwk->u.obj.cddat.right = 0;
        p_actwk->u.obj.cddat.down = 0;
        p_actwk->u.obj.cddat.wrt = 0;
        p_actwk->u.obj.cddat.plride = 0;
        p_actwk->u.obj.cddat.pl2ride = 0;
        p_actwk->u.obj.cddat.plpush = 0;
        p_actwk->u.obj.cddat.pl2push = 0;
        p_actwk->u.obj.cddat.die = 0;
      }
      frameoutchk(p_actwk);
    }
  }
  else {
    frameoutchk3(p_actwk);
  }
}


static SKC_enemy_init0_data itemug_init_tbl = {
  itempat,
  0x04C4,
  PRI_5,
  14,
  16,
  0,
  0
};
