#ifndef SKC_BS00M_H
#define SKC_BS00M_H

#include "../../types/spritestatus.h"
#include "../../shared.h"

void bs00m0_body(SKC_sprite_status* p_actwk);
void bs00m0_puka_init(SKC_sprite_status* p_actwk);
void bs00m0_jet(SKC_sprite_status* p_actwk);
void bs00m0_exit(SKC_sprite_status* p_actwk);
void bs00m0_futa(SKC_sprite_status* p_actwk);
void bs00m0_napfire(SKC_sprite_status* p_actwk);
void bs00m0_napalm(SKC_sprite_status* p_actwk);
void bs00m0_kaen0(SKC_sprite_status* p_actwk);
void bs00m0_kaen1(SKC_sprite_status* p_actwk);
void bs00m1_body(SKC_sprite_status* p_actwk);
void bs00m1_futa(SKC_sprite_status* p_actwk);
void bs00m1_napalm(SKC_sprite_status* p_actwk);
void bs00m0_napmexp(SKC_sprite_status* p_actwk);
void bs00m2_set(SKC_sprite_status* p_actwk);
extern SKC_set_act00_data napmexp_set_tbl;;

#endif
