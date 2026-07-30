#ifndef SKC_IWA_H
#define SKC_IWA_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void iwa(SKC_sprite_status* p_actwk);
void vsiwa(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* iwapat[7];
extern SKC_sprite_pattern* iwapat2[7];
extern SKC_sprite_pattern* vsiwapat[8];
extern SKC_sprite_pattern* iwapat9[11];
extern SKC_sprite_pattern* iwapat92[12];

#endif
