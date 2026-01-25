#ifndef SKC_ACTCLEARINITDATA_H
#define SKC_ACTCLEARINITDATA_H

#include "spritestatushandler.h"

typedef struct SKC_actclear_init_data {
  SKC_sprite_status_handler r_ptr;
  short xdestination;
  short xposi;
  short yposi;
  unsigned char patno;
  unsigned char sprhs;
  unsigned short exit_no;
}
SKC_actclear_init_data;

#endif
