#include "emyshot.h"
#include "../types/spritepattern.h"
#include "../shared.h"


void emyshot(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, p_actwk->u.obj.enemy_init0_data_ptr);
  p_actwk->r_ptr = &emyshot_move;
  p_actwk->u.obj.cddat.baria_bounce = 1;
  emyshot_move(p_actwk);
}


void emyshot_move(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr(p_actwk);
  chk_emy_foutc3(p_actwk);
}
