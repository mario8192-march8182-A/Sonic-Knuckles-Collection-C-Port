#ifndef UTIL_H
#define UTIL_H

void util__copy_high(long* dest, long* src);
unsigned long util__rotate(unsigned long value);
char util__to_signed(unsigned char value);
unsigned char util__to_unsigned(signed char value);
unsigned short util__to_unsigned(short value);

#endif
