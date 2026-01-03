#ifndef SKC_SETACT00DATA_H
#define SKC_SETACT00DATA_H

#include "spritestatushandler.h"

typedef struct SKC_set_act00_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    signed char xoffset;
    signed char yoffset;
  }
  data[];
}
SKC_set_act00_data;

#endif
