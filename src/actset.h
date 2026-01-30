#ifndef SKC_ACTSET_H
#define SKC_ACTSET_H

#include "types/actwkchkresult.h"
#include "types/spritestatus.h"

void actsetchk(void);
SKC_actwkchk_result actwkchk_next(SKC_actwkchk_result result);
SKC_actwkchk_result actwkchk(void);
SKC_actwkchk_result actwkchk2(SKC_sprite_status* p_actwk);
SKC_actwkchk_result actwkchk0(SKC_sprite_status* p_actwk, int slot_cnt);
void actunset(void);
void actset_sync(void);

#endif
