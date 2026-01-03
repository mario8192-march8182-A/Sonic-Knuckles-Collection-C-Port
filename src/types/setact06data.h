#ifndef SKC_SETACT06DATA_H
#define SKC_SETACT06DATA_H

#include "spritestatushandler.h"

typedef struct SKC_set_act06_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    signed char xoffset;
    signed char yoffset;
  }
  data[];
}
SKC_set_act06_data;

#endif
