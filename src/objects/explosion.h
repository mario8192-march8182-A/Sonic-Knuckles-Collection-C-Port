#ifndef SKC_EXPLOSION_H
#define SKC_EXPLOSION_H

#include "../shared.h"

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void bsexp01_set(SKC_sprite_status* p_actwk);
void set_exp01(SKC_sprite_status* p_actwk);
void set_exp01_posi(SKC_sprite_status* p_actwk);
void screxp01_set(SKC_sprite_status* p_actwk);
void exp01(SKC_sprite_status* p_actwk);
void exp01_pchg(SKC_sprite_status* p_actwk);
extern SKC_enemy_init0_data exp01_init_tbl;
extern signed char exp01_pg00[16];
extern SKC_set_act00_data bsexp01_set_tbl;
extern SKC_sprite_pattern* exp01_pt[6];

#endif
