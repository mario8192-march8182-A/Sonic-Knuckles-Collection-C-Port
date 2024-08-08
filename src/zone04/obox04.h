#ifndef OBOX04_H
#define OBOX04_H

#include "../types/spritestatus.h"

void obox04(sprite_status* p_actwk);
void obox04_wait0(sprite_status* p_actwk);
void obox04_wait1(sprite_status* p_actwk);
void swit04(sprite_status* p_actwk);
void swit04_wait0(sprite_status* p_actwk);
extern enemy_init0_data obox04_init_tbl;
extern enemy_init0_data swit04_init_tbl;
extern set_act00_data obox04_friend_set_tbl;

#endif
