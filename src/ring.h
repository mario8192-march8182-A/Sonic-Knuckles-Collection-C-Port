#ifndef RING_H
#define RING_H

#include "types/spritestatus.h"

void ring(sprite_status* p_actwk);
void ringgetsub(sprite_status* p_actwk);
void ringgetsub2(sprite_status* p_actwk);
void flyring(sprite_status* p_actwk);
void tring(sprite_status* p_actwk);
extern signed char* ringpat[9];
void slot_ring(sprite_status* p_actwk);

#endif
