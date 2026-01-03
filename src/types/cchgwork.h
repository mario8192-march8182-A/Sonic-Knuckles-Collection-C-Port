#ifndef SKC_CCHGWORK_H
#define SKC_CCHGWORK_H

#include "cchgitem.h"

typedef struct SKC_cchg_work {
  unsigned short item_data_index;
  unsigned char timer;
  unsigned char frame_counter;
  SKC_cchg_item** items_ptr;
}
SKC_cchg_work;

#endif
