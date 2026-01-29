#ifndef SKC_SAVE_H
#define SKC_SAVE_H

#include "../types/spritepattern.h"
#include "../types/spritestatus.h"

void save(SKC_sprite_status* p_actwk);
void playsave1(SKC_sprite_status* p_actwk);
void playsave2(SKC_sprite_status* p_actwk);
void playload(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* savepat[5];
void o_starinit(SKC_sprite_status* p_actwk);
void o_star(SKC_sprite_status* p_actwk);

#endif
