#ifndef SKC_MASK_H
#define SKC_MASK_H

#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"

void mask(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* maskpat[8];
void moveyuka(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* moveyukapat[2];

#endif
