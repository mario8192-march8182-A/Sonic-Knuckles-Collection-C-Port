#ifndef F091_H
#define F091_H

#include <stdbool.h>

void enemy_init0(sprite_status* pActwk, enemy_init0_data* pData);
void enemy_init2(sprite_status* pActwk, enemy_init2_data* pData);
void set_act00(sprite_status* pActwk, set_act00_data* pData);
bool puka_puka(sprite_status* pActwk);
void pt_chg0(sprite_status* pActwk, signed char* pPgData);
void pg_init(sprite_status* pActwk, signed char* pPgData);
bool chk_pl_attack(sprite_status* pActwk, sprite_status* pPlayerwk);

#endif
