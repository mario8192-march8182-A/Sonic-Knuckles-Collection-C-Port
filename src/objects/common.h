#ifndef SKC_COMMON_H
#define SKC_COMMON_H

#include "../types/spritepattern.h"
#include "../types/spritestatus.h"

void bakuhatu(SKC_sprite_status* p_actwk);
void bakuhatu2(SKC_sprite_status* p_actwk);
void bakuhatu3(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* bakuhatupat[5];
void miki00(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* miki00pat[1];
void joint00(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* joint00pat[1];
void rollc(SKC_sprite_status* p_actwk);
void scopec(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* scopecpat[3];
void scoli(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* scolipat[3];
void bar(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* barpat[8];
void water(SKC_sprite_status* p_actwk);
void block(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* blockpat[4];
void itaicolit(SKC_sprite_status* p_actwk);
void itaicolif(SKC_sprite_status* p_actwk);
void itaicoli(SKC_sprite_status* p_actwk);
void killcoli(SKC_sprite_status* p_actwk);

#endif
