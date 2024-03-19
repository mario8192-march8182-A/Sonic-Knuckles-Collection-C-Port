#ifndef F002_H
#define F002_H

#include <stdbool.h>

void set_act05(sprite_status* p_actwk, set_act05_data* p_data);
int time_pg(sprite_status* p_actwk, signed char* p_pg_data);
void chk_emy_revs(sprite_status* p_actwk);
void emy_wrt_init(sprite_status* p_actwk, wrt_init_data* p_data);
void set_emy_wchg(sprite_status* p_actwk, wrt_data* p_data);
void chk_emy_fout0(sprite_status* p_actwk);
void emy_fout(sprite_status* p_actwk);
void chk_emy_foutw0(sprite_status* p_actwk);
void wchg_fout(sprite_status* p_actwk);
void set_wchg_fout0(sprite_status* p_actwk);
void clr_wchg_bit(sprite_status* p_actwk);
void set_pl_damage(sprite_status* p_attack_actwk, sprite_status* p_playerwk);
bool chk_emy_col(sprite_status* p_actwk, sprite_status** pp_coli_actwk);
sprite_status* chk_emy_colt(sprite_status* p_actwk, short* p_col_data);
sprite_status* chk_emy_colt__col(sprite_status* p_playerwk_chk, sprite_status* p_playerwk_prev_chk, short pl_xposi, short pl_yposi, short emy_range_left_x, short emy_range_top_y, short emy_range_right_x, short emy_range_bottom_y);

#endif
