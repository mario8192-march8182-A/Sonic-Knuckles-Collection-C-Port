#ifndef SKC_OPNBOX_H
#define SKC_OPNBOX_H

#include "../shared.h"

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void opnbox(SKC_sprite_status* p_actwk);
void switch_wait0(SKC_sprite_status* p_actwk);
void switch_wait1(SKC_sprite_status* p_actwk);
void friend_(SKC_sprite_status* p_actwk);
void chk_pl_pause(SKC_sprite_status* p_actwk, unsigned char r_no);
void chk_pl2_pause(SKC_sprite_status* p_actwk);
void set_pl_pause(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
void chk_switch_ride(SKC_sprite_status* p_actwk);
void set_obox_break_pt(SKC_sprite_status* p_actwk);
extern SKC_enemy_init2_data switch_init_tbl;
extern SKC_set_act00_data opnbox_break_set_tbl;
extern SKC_sprite_pattern* openbox_pt[13];

#endif
