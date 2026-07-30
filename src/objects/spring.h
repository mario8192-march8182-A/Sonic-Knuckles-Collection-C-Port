#ifndef SKC_SPRING_H
#define SKC_SPRING_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void sjump(SKC_sprite_status* p_actwk);
void sjumpsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
signed char* sjumpchg[6];
extern SKC_sprite_pattern* banepat[11];
extern SKC_sprite_pattern* vsbanepat[7];
void sjumpmv(SKC_sprite_status* p_actwk);
void sjumpsw(SKC_sprite_status* p_actwk);

#endif
