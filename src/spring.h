#ifndef SKC_SPRING_H
#define SKC_SPRING_H

#include "types/spritepattern.h"
#include "types/spritestatus.h"

void sjump(SKC_sprite_status* p_actwk);
void sjumpsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
signed char* sjumpchg[6];
extern SKC_sprite_pattern* banepat[11];
extern SKC_sprite_pattern* vsbanepat[7];
void sjumpmv(SKC_sprite_status* p_actwk);
void sjumpsw(SKC_sprite_status* p_actwk);

#endif
