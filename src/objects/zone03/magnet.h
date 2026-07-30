#ifndef SKC_MAGNET_H
#define SKC_MAGNET_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void magnet(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* magnetpat[8];
void shooter3(SKC_sprite_status* p_actwk);

#endif
