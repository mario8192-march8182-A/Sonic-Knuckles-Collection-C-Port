#ifndef SKC_BETL04_H
#define SKC_BETL04_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void betl04(SKC_sprite_status* p_actwk);
void betl04_box(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* betl04_pt[11];

#endif
