#ifndef F091_H
#define F091_H

#include <stdbool.h>

bool puka_puka(sprite_status* pActwk);
void pg_init(sprite_status* pActwk, signed char* pg_tbl);
bool chk_pl_attack(sprite_status* pActwk, sprite_status* pPlayerwk);

#endif
