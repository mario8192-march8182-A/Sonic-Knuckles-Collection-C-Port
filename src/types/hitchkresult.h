#ifndef SKC_HITCHKRESULT_H
#define SKC_HITCHKRESULT_H

typedef enum SKC_hitchk_coli {
  HITCHK_COLI_NONE = 0,
  HITCHK_COLI_SIDE = 1,
  HITCHK_COLI_BOTTOM = -2,
  HITCHK_COLI_TOP = -1
}
SKC_hitchk_coli;

typedef struct SKC_hitchk_result {
  SKC_hitchk_coli plcoli[2];
}
SKC_hitchk_result;

#endif
