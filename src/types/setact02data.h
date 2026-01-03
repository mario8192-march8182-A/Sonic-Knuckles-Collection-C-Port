#ifndef SKC_SETACT02DATA_H
#define SKC_SETACT02DATA_H

#include "spritestatushandler.h"

typedef struct SKC_set_act02_data {
  unsigned short cnt;
  SKC_sprite_status_handler r_ptr;
  signed char xoffset;
  signed char yoffset;
}
SKC_set_act02_data;

#endif
