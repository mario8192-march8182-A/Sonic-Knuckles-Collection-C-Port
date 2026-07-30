#ifndef SKC_ZONE00HASHI_H
#define SKC_ZONE00HASHI_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void brhashi(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* brhashipat[3];
void evhashi(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* evhashipat[2];

#endif
