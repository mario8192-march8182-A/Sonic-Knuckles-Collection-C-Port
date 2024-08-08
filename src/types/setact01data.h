#ifndef SETACT01DATA_H
#define SETACT01DATA_H

#include "enemyinit0data.h"
#include "spritestatushandler.h"

typedef struct set_act01_data_entry {
  sprite_status_handler r_ptr;
  enemy_init0_data* enemy_init0_data_ptr;
  signed char* pg_data_ptr;
  sprite_status_handler callback_ptr;
  signed char xoffset;
  signed char yoffset;
  short xspeed;
  short yspeed;
}
set_act01_data_entry;

typedef struct set_act01_data {
  unsigned short cnt;
  set_act01_data_entry data[];
}
set_act01_data;

#endif
