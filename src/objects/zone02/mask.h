#ifndef SKC_MASK_H
#define SKC_MASK_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void mask(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* maskpat[8];
void moveyuka(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* moveyukapat[2];

#endif
