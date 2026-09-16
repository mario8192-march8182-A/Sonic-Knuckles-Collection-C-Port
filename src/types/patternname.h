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

inline SKC_pattern_name get_pattern_name(unsigned short raw_pattern_name) {
  SKC_pattern_name name = {
    .gfx = raw_pattern_name,
    .hf = raw_pattern_name >> 11,
    .vf = raw_pattern_name >> 12,
    .pl = raw_pattern_name >> 13,
    .pr = raw_pattern_name >> 15
  };
  return name;
}
inline unsigned short get_raw_pattern_name(SKC_pattern_name pattern_name) {
  unsigned short name =
    pattern_name.gfx |
    pattern_name.hf << 11 |
    pattern_name.vf << 12 |
    pattern_name.pl << 13 |
    pattern_name.pr << 15;
  return name;
}
#endif
