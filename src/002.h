#ifndef F002_H
#define F002_H

#include <stdbool.h>

sprite_status* set_act05(sprite_status* p_actwk, set_act05_data* p_data);
int time_pg(sprite_status* p_actwk, signed char* p_pg_data);
void dec_timer(sprite_status* p_actwk);
void chk_oya_die0(sprite_status* p_actwk);
void chk_oya_diew0(sprite_status* p_actwk);
void chk_distance(sprite_status* p_actwk, bool* pl_is_right, bool* pl_is_below, short* pl_x_distance, short* pl_y_distance);
void chk_emy_revs(sprite_status* p_actwk);
void speedsetg20(sprite_status* p_actwk);
void speedsetg(sprite_status* p_actwk, short gravity);
void emy_wrt_init(sprite_status* p_actwk, wrt_init_data* p_data);
void set_emy_wchg(sprite_status* p_actwk, wrt_data* p_data);
void chk_emy_foutc0(sprite_status* p_actwk);
void chk_emy_fout0(sprite_status* p_actwk);
void emy_fout(sprite_status* p_actwk);
void chk_break_fout(sprite_status* p_actwk);
void chk_emy_foutw0(sprite_status* p_actwk);
void wchg_fout(sprite_status* p_actwk);
void set_wchg_fout0(sprite_status* p_actwk);
void clr_wchg_bit(sprite_status* p_actwk);
void chk_emy_foutwc0(sprite_status* p_actwk);
void wchg_die(sprite_status* p_actwk);
void set_emy_fout0(sprite_status* p_actwk);
void set_emy_fout01(sprite_status* p_actwk);
void set_break_spd(sprite_status* p_actwk, unsigned char unknown);
void set_pl_damage(sprite_status* p_attack_actwk, sprite_status* p_playerwk);
bool chk_emy_col(sprite_status* p_actwk, sprite_status** pp_coli_actwk);
sprite_status* chk_emy_colt(sprite_status* p_actwk, short* p_col_data);
sprite_status* chk_emy_colt__col(sprite_status* p_playerwk_chk, sprite_status* p_playerwk_prev_chk, short pl_xposi, short pl_yposi, short emy_range_left_x, short emy_range_top_y, short emy_range_right_x, short emy_range_bottom_y);
void chk_framein(sprite_status* p_actwk, sprite_status_handler p_callback);
void set_bane_jump(sprite_status* p_playerwk, short yspeed);

#endif
