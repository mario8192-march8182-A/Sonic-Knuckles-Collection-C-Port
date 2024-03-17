#include <stdlib.h>
#include "util.h"


unsigned long util__rotate(unsigned long value) {
  unsigned long result = value << 16 & 0xFFFF0000 | value >> 16 & 0x0000FFFF;
  return result;
}


unsigned short util__to_unsigned(short value) {
  unsigned short result = 0;

  if (value < 0) {
    result = 65535 - abs(value) + 1;
  }
  else {
    result = value;
  }

  return result;
}
