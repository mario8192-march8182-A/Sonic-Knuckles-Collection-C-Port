#ifndef OPNBOX_H
#define OPNBOX_H

#include "types/enemyinit2data.h"
#include "types/setact00data.h"
#include "types/spritestatus.h"

void opnbox(sprite_status* p_actwk);
void switch_wait0(sprite_status* p_actwk);
void switch_wait1(sprite_status* p_actwk);
void friend(sprite_status* p_actwk);
void chk_pl_pause(sprite_status* p_actwk, unsigned char r_no);
void chk_pl2_pause(sprite_status* p_actwk);
void set_pl_pause(sprite_status* p_actwk, sprite_status* p_playerwk);
void chk_switch_ride(sprite_status* p_actwk);
void set_obox_break_pt(sprite_status* p_actwk);
extern enemy_init2_data switch_init_tbl;
extern set_act00_data opnbox_break_set_tbl;
extern signed char* openbox_pt[13];

#endif
