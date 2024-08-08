#ifndef ACTCLEARINITDATA_H
#define ACTCLEARINITDATA_H

#include "spritestatushandler.h"

typedef struct actclear_init_data {
  sprite_status_handler r_ptr;
  short x_destination;
  short xposi;
  short yposi;
  unsigned char patno;
  unsigned char sprhs;
  unsigned short exit_no;
}
actclear_init_data;

#endif
