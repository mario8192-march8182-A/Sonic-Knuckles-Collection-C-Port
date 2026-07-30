#ifndef SKC_TOGE_H
#define SKC_TOGE_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void toge(SKC_sprite_status* p_actwk);
void togedamegesub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
extern SKC_sprite_pattern* togepat[8];
extern SKC_sprite_pattern* vstogepat[8];

#endif
