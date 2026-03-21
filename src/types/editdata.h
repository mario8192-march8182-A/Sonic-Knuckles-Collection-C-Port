#ifndef SKC_EDITDATA_H
#define SKC_EDITDATA_H

#include "spritepattern.h"
#include "spritestatushandler.h"

typedef struct SKC_edit_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    SKC_sprite_pattern** patbase;
    unsigned short sproffset;
    unsigned char patno;
    unsigned char userflag;
  }
  items[];
}
SKC_edit_data;

#endif
