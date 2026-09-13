#ifndef SKC_PATTERNNAME_H
#define SKC_PATTERNNAME_H

typedef struct SKC_pattern_name {
  unsigned int gfx : 11;
  unsigned int hf : 1;
  unsigned int vf : 1;
  unsigned int pl : 2;
  unsigned int pr : 1;
}
SKC_pattern_name;

#endif
