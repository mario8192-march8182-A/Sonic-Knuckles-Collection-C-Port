#ifndef SKC_RING_H
#define SKC_RING_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void ring(SKC_sprite_status* p_actwk);
void ringgetsub();
void ringgetsub2();
void flyring(SKC_sprite_status* p_actwk);
void tring(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* ringpat[9];
void slot_ring(SKC_sprite_status* p_actwk);

#endif
