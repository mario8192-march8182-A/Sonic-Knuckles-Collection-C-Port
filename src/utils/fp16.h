#ifndef SKC_FP16_H
#define SKC_FP16_H

inline short fp16_get_fraction(long fp16) {
  long wk = (unsigned long)fp16 & 0x0000FFFF;
  short result = (wk & 0x7FFF) - (wk & 0x8000);
  return result;
}
inline short fp16_get_integer(long fp16) {
  long wk = (unsigned long)fp16 >> 16;
  short result = (wk & 0x7FFF) - (wk & 0x8000);
  return result;
}
inline void fp16_set_fraction(long* p_fp16, short value) {
  long long integer = (unsigned long)*p_fp16 & 0xFFFF0000;
  long long fraction = (unsigned short)value & 0xFFFF;
  long long wk = integer | fraction;
  long result = (wk & 0x7FFFFFFF) - (wk & 0x80000000);
  *p_fp16 = result;
}
inline void fp16_set_integer(long* p_fp16, short value) {
  long long integer = ((unsigned short)value & 0xFFFF) << 16;
  long long fraction = (unsigned long)*p_fp16 & 0x0000FFFF;
  long long wk = integer | fraction;
  long result = (wk & 0x7FFFFFFF) - (wk & 0x80000000);
  *p_fp16 = result;
}

#endif
