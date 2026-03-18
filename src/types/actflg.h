#ifndef SKC_ACTFLG_H
#define SKC_ACTFLG_H

typedef struct SKC_actflg {
  unsigned int hflip : 1;
  unsigned int vflip : 1;
  unsigned int relative_coordinates : 1;
  unsigned int vspl : 1;
  unsigned int vspl2 : 1;
  unsigned int static_pattern : 1;
  unsigned int compound : 1;
  unsigned int onscreen : 1;
}
SKC_actflg;

#endif
