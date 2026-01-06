#include "fp8.h"


extern inline signed char fp8_get_fraction(short fp8);
extern inline signed char fp8_get_integer(short fp8);
extern inline void fp8_set_fraction(short* p_fp8, signed char value);
extern inline void fp8_set_integer(short* p_fp8, signed char value);
