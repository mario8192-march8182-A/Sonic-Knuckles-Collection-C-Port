#ifndef SKC_BGSPR_H
#define SKC_BGSPR_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void bgspr(SKC_sprite_status* p_actwk);
void bgsprmove(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* bgsprpat[51];
void bgsprp(SKC_sprite_status* p_actwk);
extern signed char* bgsprpchg[8];
extern SKC_sprite_pattern* bgsprppat[30];
void bgsprz(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* bgsprzpat[2];

#endif
