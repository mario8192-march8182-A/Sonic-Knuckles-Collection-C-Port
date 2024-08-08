#ifndef SETACT00DATA_H
#define SETACT00DATA_H

#include "spritestatushandler.h"

typedef struct set_act00_data_entry {
  sprite_status_handler r_ptr;
  signed char xoffset;
  signed char yoffset;
}
set_act00_data_entry;

typedef struct set_act00_data {
  unsigned short cnt;
  set_act00_data_entry data[];
}
set_act00_data;

#endif
