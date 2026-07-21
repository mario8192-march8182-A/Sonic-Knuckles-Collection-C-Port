#ifndef SKC_NUCKLE_H
#define SKC_NUCKLE_H

#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../shared.h"

void nuckle(SKC_sprite_status* p_actwk);
void nuckle_fout(SKC_sprite_status* p_actwk);
void tekotu(SKC_sprite_status* p_actwk);
void ev0700(SKC_sprite_status* p_actwk);
void sw0700(SKC_sprite_status* p_actwk);
void sw0a00(SKC_sprite_status* p_actwk);
void nucksw(SKC_sprite_status* p_actwk);
void setbryuka(SKC_sprite_status* p_actwk);
void cchgsw(SKC_sprite_status* p_actwk);
void set_nuckle_bgm(void);
void chk_nucksw_ride(SKC_sprite_status* p_actwk);
extern SKC_wrt_init_data nuckle_init_tbl;
extern SKC_enemy_init0_data housi071_init_tbl;
extern SKC_wrt_data nuckle_wrt_tbl;
extern SKC_wrt_data nk0a00_wrt_tbl;
extern signed char tired_pg01[11];
extern signed char footwk_pg00[60];
extern signed char guard_pg00[7];
extern signed char guard_pg01[8];
extern signed char damage_pg00[5];
extern signed char ball_pg01[11];
extern signed char jump_pg00[8];
extern signed char down_pg00[12];
extern signed char land_pg00[7];
extern signed char land_pg01[14];
extern signed char spin_pg00[8];
extern signed char die_pg00[12];
extern signed char run_pg02[11];
extern signed char run_pg03[11];
extern signed char effect_pg00[9];
extern signed char wake_pg00[38];
extern signed char wait_pg00[5];
extern signed char angry_pg00[5];
extern signed char panch_pg00[12];
extern signed char panch_pg01[22];
extern signed char panch_pg02[8];
extern signed char comeon_pg00[20];
extern unsigned short nuckle_cor_tbl[16];
extern SKC_sprite_pattern* nk0a00_pt[7];

#endif
