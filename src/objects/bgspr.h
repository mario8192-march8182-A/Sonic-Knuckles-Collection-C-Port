#ifndef SKC_BGSPR_H
#define SKC_BGSPR_H

#include "../types/spritepattern.h"
#include "../types/spritestatus.h"

void bgspr(SKC_sprite_status* p_actwk);
void bgsprmove(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* bgsprpat[51];
void bgsprp(SKC_sprite_status* p_actwk);
extern signed char* bgsprpchg[8];
extern SKC_sprite_pattern* bgsprppat[30];
void bgsprz(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* bgsprzpat[2];

#endif
