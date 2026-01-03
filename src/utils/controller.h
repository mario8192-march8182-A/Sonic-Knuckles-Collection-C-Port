#ifndef SKC_CONTROLLER_H
#define SKC_CONTROLLER_H

#include <stdbool.h>

typedef enum pad_buttons {
  PAD_U = 0x01,
  PAD_D = 0x02,
  PAD_L = 0x04,
  PAD_R = 0x08,
  PAD_B = 0x10,
  PAD_C = 0x20,
  PAD_A = 0x40,
  PAD_S = 0x80
}
pad_buttons;

bool inline are_buttons_pressed(unsigned short swdata, unsigned char buttons) {
  return swdata & buttons;
}
bool inline are_buttons_down(unsigned short swdata, unsigned char buttons) {
  return swdata >> 8 & buttons;
}

#endif
