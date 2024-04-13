#include "globals.h"
#include "macros.h"
#include "emyshot.h"
#include "002.h"
#include "091.h"


void emyshot(sprite_status* p_actwk) {
  enemy_init0(p_actwk, p_actwk->actfree.enemy_uninit_0.init_data_ptr);
  p_actwk->r_ptr = &emyshot_move;
  SET_BIT_3(p_actwk->cddat2);
  emyshot_move(p_actwk);
}


void emyshot_move(sprite_status* p_actwk) {
  p_actwk->actfree.dynamic.callback_ptr(p_actwk);
  chk_emy_foutc3(p_actwk);
}
