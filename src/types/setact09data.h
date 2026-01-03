#ifndef SKC_SETACT09DATA_H
#define SKC_SETACT09DATA_H

#include "spritestatushandler.h"

typedef struct SKC_set_act09_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    signed char xoffset;
    signed char yoffset;
  }
  data[];
}
SKC_set_act09_data;

#endif
