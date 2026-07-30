#ifndef SKC_EGGMBL_H
#define SKC_EGGMBL_H

#include "../shared.h"

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void mbl_eggman0(SKC_sprite_status* p_actwk);
void set_megmbl(SKC_sprite_status* p_actwk);
void set_megmbl0(SKC_sprite_status* p_actwk);
void mbl_eggman3(SKC_sprite_status* p_actwk);
void mbl_eggman4(SKC_sprite_status* p_actwk);
void eggmbl01(SKC_sprite_status* p_actwk);
void eggmbl03(SKC_sprite_status* p_actwk);
void eggmbl04(SKC_sprite_status* p_actwk);
void resultembl(SKC_sprite_status* p_actwk);
extern SKC_set_act00_data mbl_eggman0_set_tbl;
extern SKC_set_act00_data mbl_eggman1_set_tbl;
extern SKC_set_act00_data mbl_eggman3_set_tbl;
extern SKC_set_act00_data mbl_eggman4_set_tbl;
extern SKC_set_act00_data eggmbl00_set_tbl;
extern SKC_set_act00_data eggmbl01_set_tbl;
extern SKC_set_act00_data eggmbl02_set_tbl;
extern SKC_set_act00_data eggmbl03_set_tbl;
extern SKC_set_act00_data eggmbl04_set_tbl;
extern SKC_set_act00_data embl_jet_set_tbl;
extern SKC_set_act00_data msmbl_set_tbl;
extern SKC_sprite_pattern* eggmbl_pt[13];
extern SKC_sprite_pattern* eggrun_pt[7];
extern SKC_sprite_pattern* egg2_pt[4];
extern SKC_sprite_pattern* egg3_pt[4];

#endif
