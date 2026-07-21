#ifndef SKC_NUCKLE09_H
#define SKC_NUCKLE09_H

#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../shared.h"

void nuckle090(SKC_sprite_status* p_actwk);
void ev0910(SKC_sprite_status* p_actwk);
void nuckle091(SKC_sprite_status* p_actwk);
void damg0_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
void nk0930_effect(SKC_sprite_status* p_actwk);
void clen0930(SKC_sprite_status* p_actwk);
void clenparts(SKC_sprite_status* p_actwk);
void clenchain(SKC_sprite_status* p_actwk);
void smok0930(SKC_sprite_status* p_actwk);
void caos09_frag(SKC_sprite_status* p_actwk);
void nk0930_exp(SKC_sprite_status* p_actwk);
void embl0930_handb(SKC_sprite_status* p_actwk);
void embl0930_rhand(SKC_sprite_status* p_actwk);
void embl0930_lhand(SKC_sprite_status* p_actwk);
void door09(SKC_sprite_status* p_actwk);
void door09_break(SKC_sprite_status* p_actwk);
void piyo09(SKC_sprite_status* p_actwk);
void cchg09(SKC_sprite_status* p_actwk);
void nk0930_wrt(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* iwa091_pt[1];
extern SKC_sprite_pattern* nk0931_pt[19];
extern unsigned short* nk0931_tbl[19];
extern SKC_set_act00_data clenparts_set_tbl;
extern SKC_enemy_init0_data embl0930_init_tbl;
extern SKC_enemy_init0_data clen0930_init_tbl;
extern unsigned short cor0942_dat[48];
extern SKC_wrt_data nk0931_wrt_tbl;
extern SKC_sprite_pattern* emblcl_pt[29];

#endif
