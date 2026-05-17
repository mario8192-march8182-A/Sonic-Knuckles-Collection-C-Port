#ifndef SKC_PLAYWORK_H
#define SKC_PLAYWORK_H

#include "spritestatus.h"

typedef struct SKC_play_work {
  short* plmaxspdwk_ptr;
  short* pladdspdwk_ptr;
  short* plretspdwk_ptr;
  short* scra_vline_ptr;
  SKC_sprite_status* effectwk_ptr;
}
SKC_play_work;

#endif
