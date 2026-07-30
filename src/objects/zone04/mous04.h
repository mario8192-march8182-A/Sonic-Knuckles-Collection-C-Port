#ifndef SKC_MOUS04_H
#define SKC_MOUS04_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void mous04(SKC_sprite_status* p_actwk);
void mous04_box(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* mous04_pt[10];

#endif
