#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

void util__assign_high(long* dest, short src);
void util__copy_high(long* dest, long* src);
bool util__get_add_carry(unsigned short a, unsigned short b);
bool util__get_add_long_carry(unsigned long a, unsigned long b);
unsigned long util__rotate(unsigned long value);
char util__to_signed(unsigned char value);
unsigned char util__char_to_unsigned(signed char value);
unsigned short util__to_unsigned(short value);
short util__longhigh_to_short(long value);

#endif
