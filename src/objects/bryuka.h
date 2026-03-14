#ifndef SKC_BRYUKA_H
#define SKC_BRYUKA_H

#include "../types/speed.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"

void bryuka(SKC_sprite_status* p_actwk);
void bryukamove2(SKC_sprite_status* p_actwk);
extern SKC_speed bryukaspdtbl[12];
extern SKC_sprite_pattern* bryukapat[2];
extern SKC_sprite_pattern* bryukapat2[2];
extern SKC_sprite_pattern* bryukapat3[2];
extern SKC_sprite_pattern* bryukapat4[2];
extern SKC_sprite_pattern* bryukapat5[12];
extern SKC_sprite_pattern* bryukapat6[2];

#endif
