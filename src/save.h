#ifndef SAVE_H
#define SAVE_H

#include "sprite_status.h"

void save(sprite_status* pActwk);
void playsave1(sprite_status* p_actwk);
void playsave2(sprite_status* p_actwk);
void playload(sprite_status* p_actwk);
signed char* savepat[5];
void o_starinit(sprite_status* p_actwk);

#endif
