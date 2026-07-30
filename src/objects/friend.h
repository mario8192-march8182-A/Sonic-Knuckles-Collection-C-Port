#ifndef SKC_FRIEND_H
#define SKC_FRIEND_H

#include "../types/friendinitdata.h"

typedef struct SKC_sprite_pattern SKC_sprite_pattern;
typedef struct SKC_sprite_status SKC_sprite_status;

void friend(SKC_sprite_status* p_actwk);
extern unsigned char zone_friend_tbl[24][2];
extern SKC_friend_init_data zone_friend_init_tbl[12];
void ten(SKC_sprite_status* p_actwk);
void cucky_group(SKC_sprite_status* p_actwk);
void ricky_group(SKC_sprite_status* p_actwk);
void pocky_group(SKC_sprite_status* p_actwk);
extern SKC_sprite_pattern* cuckyflickypat[3];
extern SKC_sprite_pattern* rickypat[3];
extern SKC_sprite_pattern* pickypat[3];
extern SKC_sprite_pattern* rockypat[3];
extern SKC_sprite_pattern* pockypeckypat[3];

#endif
