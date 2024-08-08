#ifndef TITLEZONESINITDATA_H
#define TITLEZONESINITDATA_H

#include "spritestatushandler.h"

typedef struct title_zones_init_data {
  sprite_status_handler r_ptr;
  short x_destination;
  short xposi;
  short yposi;
  unsigned char patno;
  unsigned char sprhs;
  unsigned short colino;
}
title_zones_init_data;

#endif
