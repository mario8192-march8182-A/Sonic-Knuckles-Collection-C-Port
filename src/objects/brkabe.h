#ifndef SKC_BRKABE_H
#define SKC_BRKABE_H

#include "../types/speed.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"

void brkabe(SKC_sprite_status* p_actwk);
void breakgosubf(SKC_sprite_status* p_actwk, SKC_speed* p_spdtbl);
void breakgosub3(SKC_sprite_status* p_actwk, SKC_speed* p_spdtbl);
extern SKC_sprite_pattern* brkabepat[6];
extern SKC_sprite_pattern* brkabe03pat[6];
extern SKC_sprite_pattern* brkabe02pat[4];
extern SKC_sprite_pattern* brkabe01pat[4];
extern SKC_sprite_pattern* brkabe06pat[2];
extern SKC_sprite_pattern* brkabe07pat[2];
extern SKC_sprite_pattern* brkabe09pat[2];

#endif
