#ifndef SKC_ACTWKCHKRESULT_H
#define SKC_ACTWKCHKRESULT_H

#include "spritestatus.h"

typedef struct SKC_actwkchk_result {
  SKC_sprite_status* actwk_ptr;
  int remaining_slot_cnt;
}
SKC_actwkchk_result;

#endif
