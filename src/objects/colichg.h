#ifndef SKC_COLICHG_H
#define SKC_COLICHG_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void colichg(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* colichgpat[8];
void colichg2(SKC_sprite_status* p_actwk);

#endif
