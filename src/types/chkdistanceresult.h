#ifndef SKC_CHKDISTANCERESULT_H
#define SKC_CHKDISTANCERESULT_H

#include <stdbool.h>

typedef struct SKC_chk_distance_result {
  bool right;
  bool below;
  short xdistance;
  short ydistance;
}
SKC_chk_distance_result;

#endif
