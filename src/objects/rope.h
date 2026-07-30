#ifndef SKC_ROPE_H
#define SKC_ROPE_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void rope(SKC_sprite_status* p_actwk);
void ropeswing(SKC_sprite_status* p_actwk);
void hbar(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* ropepat[36];

#endif
