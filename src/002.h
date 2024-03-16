#ifndef F002_H
#define F002_H

#include <stdbool.h>

void set_act05(sprite_status* pActwk, set_act05_data* pData);
int time_pg(sprite_status* pActwk, signed char* pPgData);
int chk_tpg_next(sprite_status* pActwk, signed char pg, signed char* pPgData, unsigned char patcnt);
void emy_wrt_init(sprite_status* pActwk, wrt_init_data* pData);
void set_emy_wchg(sprite_status* pActwk, wrt_data* pData);
void chk_emy_fout0(sprite_status* pActwk);
void emy_fout(sprite_status* pActwk);
void chk_emy_foutw0(sprite_status* pActwk);
void wchg_fout(sprite_status* pActwk);
void set_wchg_fout0(sprite_status* pActwk);
void clr_wchg_bit(sprite_status* pActwk);
void set_pl_damage(sprite_status* pAttackActwk, sprite_status* pPlayerwk);
bool chk_emy_col(sprite_status* pActwk, sprite_status** ppColiActwk);
sprite_status* chk_emy_colt(sprite_status* pActwk, short* pColData);
sprite_status* chk_emy_colt__col(sprite_status* pPlayerwkChk, sprite_status* pPlayerwkPrevChk, short pl_xposi, short pl_yposi, short emy_range_left_x, short emy_range_top_y, short emy_range_right_x, short emy_range_bottom_y);

#endif
