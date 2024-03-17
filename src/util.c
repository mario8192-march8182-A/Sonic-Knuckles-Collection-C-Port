#include <stdlib.h>
#include "util.h"


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
