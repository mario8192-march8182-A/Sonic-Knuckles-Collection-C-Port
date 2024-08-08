#ifndef SETACT02DATA_H
#define SETACT02DATA_H

#include "spritestatushandler.h"

typedef struct set_act02_data {
  unsigned short cnt;
  sprite_status_handler r_ptr;
  signed char xoffset;
  signed char yoffset;
}
set_act02_data;

#endif
