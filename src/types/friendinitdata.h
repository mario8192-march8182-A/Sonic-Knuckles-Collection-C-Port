#ifndef SKC_FRIENDINITDATA_H
#define SKC_FRIENDINITDATA_H

typedef struct SKC_sprite_pattern SKC_sprite_pattern;

typedef struct SKC_friend_init_data {
  short xspeed;
  short yspeed;
  SKC_sprite_pattern** patbase;
}
SKC_friend_init_data;

#endif
