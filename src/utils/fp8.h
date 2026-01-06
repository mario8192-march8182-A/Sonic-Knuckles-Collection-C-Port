#ifndef SKC_FP8_H
#define SKC_FP8_H

inline signed char fp8_get_fraction(short fp8) {
  short wk = (unsigned short)fp8 & 0x00FF;
  signed char result = (wk & 0x7F) - (wk & 0x80);
  return result;
}
inline signed char fp8_get_integer(short fp8) {
  short wk = (unsigned short)fp8 >> 8;
  signed char result = (wk & 0x7F) - (wk & 0x80);
  return result;
}
inline void fp8_set_fraction(short* p_fp8, signed char value) {
  long integer = (unsigned short)*p_fp8 & 0xFF00;
  long fraction = (unsigned char)value & 0xFF;
  long wk = integer | fraction;
  short result = (wk & 0x7FFF) - (wk & 0x8000);
  *p_fp8 = result;
}
inline void fp8_set_integer(short* p_fp8, signed char value) {
  long integer = ((unsigned char)value & 0xFF) << 8;
  long fraction = (unsigned short)*p_fp8 & 0x00FF;
  long wk = integer | fraction;
  short result = (wk & 0x7FFF) - (wk & 0x8000);
  *p_fp8 = result;
}

#endif
