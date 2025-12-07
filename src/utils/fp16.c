#include "fp16.h"


extern inline short fp16_get_fraction(long p_fp16);
extern inline short fp16_get_integer(long p_fp16);
extern inline void fp16_set_fraction(long* p_fp16, short value);
extern inline void fp16_set_integer(long* p_fp16, short value);
