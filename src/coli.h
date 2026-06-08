#ifndef SKC_COLI_H
#define SKC_COLI_H

#include "types/spritestatus.h"

void vspcol(SKC_sprite_status* p_playerwk);
void pcol(SKC_sprite_status* p_playerwk);
void emydieset(SKC_sprite_status* p_coliwk);
void playdamageset(SKC_sprite_status* p_playerwk, SKC_sprite_status* p_coliwk);
void playdieset(SKC_sprite_status* p_playerwk);
void colibufferchk(SKC_sprite_status* p_actwk);
void pcolhyper(SKC_sprite_status* p_playerwk);

#endif
