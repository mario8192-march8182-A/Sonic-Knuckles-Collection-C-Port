#ifndef SKC_EGJR0A_H
#define SKC_EGJR0A_H

#include "../../shared.h"

typedef struct SKC_sprite_status SKC_sprite_status;

void egjr0a(SKC_sprite_status* p_actwk);
void egjr0a_puka_init(SKC_sprite_status* p_actwk);
void egjr0a_pg(SKC_sprite_status* p_actwk);
extern SKC_enemy_init0_data egjr0a_init_tbl02;
extern SKC_set_act00_data egjr0a_02_set_tbl;

#endif
