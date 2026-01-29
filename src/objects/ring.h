#ifndef SKC_RING_H
#define SKC_RING_H

#include "../types/spritepattern.h"
#include "../types/spritestatus.h"

void ring(SKC_sprite_status* p_actwk);
void ringgetsub(SKC_sprite_status* p_actwk);
void ringgetsub2(SKC_sprite_status* p_actwk);
void flyring(SKC_sprite_status* p_actwk);
void tring(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* ringpat[9];
void slot_ring(SKC_sprite_status* p_actwk);

#endif
