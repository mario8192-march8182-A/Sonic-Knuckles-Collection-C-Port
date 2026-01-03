#ifndef SKC_SETACT01DATA_H
#define SKC_SETACT01DATA_H

#include "enemyinit0data.h"
#include "spritestatushandler.h"

typedef struct SKC_set_act01_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    SKC_enemy_init0_data* enemy_init0_data_ptr;
    signed char* pg_data_ptr;
    SKC_sprite_status_handler callback_ptr;
    signed char xoffset;
    signed char yoffset;
    short xspeed;
    short yspeed;
  }
  data[];
}
SKC_set_act01_data;

#endif
