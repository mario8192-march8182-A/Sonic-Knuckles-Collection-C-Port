#ifndef SKC_SWDATA_H
#define SKC_SWDATA_H

#include <stdbool.h>

typedef struct SKC_pad {
  unsigned int u : 1;
  unsigned int d : 1;
  unsigned int l : 1;
  unsigned int r : 1;
  unsigned int b : 1;
  unsigned int c : 1;
  unsigned int a : 1;
  unsigned int s : 1;
}
SKC_pad;

typedef struct SKC_swdata {
  SKC_pad down;
  SKC_pad pressed;
}
SKC_swdata;

inline bool are_any_dir_buttons_used(SKC_pad pad) {
  return pad.u == 1 || pad.d == 1 || pad.l == 1 || pad.r == 1;
}
inline bool are_any_trg_buttons_used(SKC_pad pad) {
  return pad.b == 1 || pad.c == 1 || pad.a == 1;
}
inline bool are_any_face_buttons_used(SKC_pad pad) {
  return are_any_trg_buttons_used(pad) || pad.s == 1;
}
inline bool are_any_buttons_used(SKC_pad pad) {
  return are_any_dir_buttons_used(pad) || are_any_face_buttons_used(pad);
}
inline bool are_same_buttons_used(SKC_pad pad0, SKC_pad pad1) {
  return pad0.u == pad1.u
         && pad0.d == pad1.d
         && pad0.l == pad1.l
         && pad0.r == pad1.r
         && pad0.b == pad1.b
         && pad0.c == pad1.c
         && pad0.a == pad1.a
         && pad0.s == pad1.s;
}

#endif
