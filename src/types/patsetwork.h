#ifndef SKC_PATSETWORK_H
#define SKC_PATSETWORK_H

#include "spritedata.h"
#include "spriteplacement.h"

typedef struct SKC_patset_work {
  SKC_sprite_data* sprite_tbl_ptr;
  short xposi;
  short yposi;
  SKC_sprite_placement* placements_ptr;
  unsigned short placement_cnt;
  unsigned short sprite_left_cnt;
}
SKC_patset_work;

#endif
