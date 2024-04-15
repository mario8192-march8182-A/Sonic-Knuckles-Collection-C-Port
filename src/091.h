#ifndef F091_H
#define F091_H

#include <stdbool.h>

void enemy_init0(sprite_status* p_actwk, enemy_init0_data* p_data);
void enemy_init1(sprite_status* p_actwk, enemy_init1_data* p_data);
void enemy_init2(sprite_status* p_actwk, enemy_init2_data* p_data);
sprite_status* set_act00(sprite_status* p_actwk, set_act00_data* p_data);
sprite_status* set_act01(sprite_status* p_actwk, set_act01_data* p_data);
sprite_status* set_act03(sprite_status* p_actwk, set_act03_data* p_data);
void ko_offset0(sprite_status* p_actwk);
void ko_offset1(sprite_status* p_actwk);
bool puka_puka(sprite_status* p_actwk);
void pt_chg(sprite_status* p_actwk);
void pt_chg0(sprite_status* p_actwk, signed char* p_pg_data);
void pg_init(sprite_status* p_actwk, signed char* p_pg_data);
bool chk_pl_attack(sprite_status* p_actwk, sprite_status* p_playerwk);

#endif
