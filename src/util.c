#include <stdbool.h>
#include <stdlib.h>
#include "util.h"
#define SCHAR_MAX 127
#define UCHAR_MAX 255
#define USHORT_MAX 65535
#define ULONG_MAX 4294967295


void util__assign_high(long* dest, short src) {
  *dest = src * 65536 + *dest % 65536;
}


void util__copy_high(long* dest, long* src) {
  *dest = *src / 65536 * 65536 + *dest % 65536;
}


bool util__get_add_carry(unsigned short a, unsigned short b) {
  bool result = a > USHORT_MAX - b;
  return result;
}


bool util__get_add_long_carry(unsigned long a, unsigned long b) {
  bool result = a > ULONG_MAX - b;
  return result;
}


unsigned long util__rotate(unsigned long value) {
  unsigned long result = (value << 16 & 0xFFFF0000) | (value >> 16 & 0x0000FFFF);
  return result;
}


char util__to_signed(unsigned char value) {
  char result = 0;

  if (value <= SCHAR_MAX) {
    result = value;
  }
  else {
    result = -(char)(UCHAR_MAX - value) - 1;
  }

  return result;
}


unsigned char util__char_to_unsigned(signed char value) {
  unsigned char result = 0;

  if (value < 0) {
    result = 255 - abs(value) + 1;
  }
  else {
    result = value;
  }

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


short util__longhigh_to_short(long value) {
  bool negative = value < 0;
  short result = value / 65536;
  if (negative && value % 65536 != 0) {
    --result;
  }

  return result;
}
