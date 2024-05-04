#ifndef SPRING_H
#define SPRING_H

#include "sprite_status.h"

void sjump(sprite_status* p_actwk);
void sjumpsub(sprite_status* p_actwk, sprite_status* p_playerwk);
signed char* sjumpchg[6];
signed char* banepat[11];
signed char* vsbanepat[7];
void sjumpmv(sprite_status* p_actwk);
void sjumpsw(sprite_status* p_actwk);

#endif
