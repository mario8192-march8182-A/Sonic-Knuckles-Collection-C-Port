#ifndef SKC_SETACT08DATA_H
#define SKC_SETACT08DATA_H

#include "spritestatushandler.h"

typedef struct SKC_set_act08_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
  }
  data[];
}
SKC_set_act08_data;

#endif
