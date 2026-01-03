#ifndef SKC_BITS_H
#define SKC_BITS_H

#define BIT_IS_SET(value, bit) !!(value & 1 << (bit))
#define CLEAR_BIT(value, bit) ((value) &= ~(1 << (bit)))
#define SET_BIT(value, bit) ((value) |= 1 << (bit))
#define TOGGLE_BIT(value, bit) ((value) ^= 1 << (bit))

inline unsigned char rotate_char_left(unsigned char value, unsigned char bits) {
  unsigned char result = (value << bits | value >> 8 - bits) & 0xFF;
  return result;
}

#endif
