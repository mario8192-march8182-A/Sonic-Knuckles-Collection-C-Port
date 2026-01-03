#ifndef SKC_SETACT04DATA_H
#define SKC_SETACT04DATA_H

#include "spritestatushandler.h"

typedef struct SKC_set_act04_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    signed char* pg_data_ptr;
    SKC_sprite_status_handler callback_ptr;
    signed char xoffset;
    signed char yoffset;
    short xspeed;
    short yspeed;
  }
  data[];
}
SKC_set_act04_data;

#endif
