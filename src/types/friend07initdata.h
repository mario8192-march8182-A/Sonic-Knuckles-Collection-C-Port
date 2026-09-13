#ifndef SKC_FRIEND07INITDATA_H
#define SKC_FRIEND07INITDATA_H

#include "patternname.h"
#include "spritestatushandler.h"

typedef struct SKC_sprite_pattern SKC_sprite_pattern;

typedef struct SKC_friend07_init_data {
  SKC_sprite_status_handler r_ptr;
  SKC_sprite_pattern** patbase;
  SKC_pattern_name sproffset;
}
SKC_friend07_init_data;

#endif
