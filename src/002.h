#ifndef F002_H
#define F002_H

#include <stdbool.h>

void set_act05(sprite_status* pActwk, set_act05_data* data);
void set_emy_wchg(sprite_status* pActwk, wrt_tbl* data);
void set_wchg_fout0(sprite_status* pActwk);
void clr_wchg_bit(sprite_status* pActwk);
void set_pl_damage(sprite_status* pAttackActwk, sprite_status* pPlayerwk);
bool chk_emy_col(sprite_status* pActwk, sprite_status** ppColiActwk);

#endif
