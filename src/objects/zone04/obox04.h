#ifndef SKC_OBOX04_H
#define SKC_OBOX04_H

#include "../../types/enemyinitdata.h"
#include "../../types/setactdata.h"
#include "../../types/spritestatus.h"

void obox04(SKC_sprite_status* p_actwk);
void obox04_wait0(SKC_sprite_status* p_actwk);
void obox04_wait1(SKC_sprite_status* p_actwk);
void swit04(SKC_sprite_status* p_actwk);
void swit04_wait0(SKC_sprite_status* p_actwk);
extern SKC_enemy_init0_data obox04_init_tbl;
extern SKC_enemy_init0_data swit04_init_tbl;
extern SKC_set_act00_data obox04_friend_set_tbl;

#endif
