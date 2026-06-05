#ifndef SKC_DIRECTION_H
#define SKC_DIRECTION_H

inline unsigned char direction_sum(unsigned char direction, int value) {
  return direction + value & 0xFF;
}
inline unsigned char direction_sub(unsigned char direction, int value) {
  return direction - value & 0xFF;
}
inline unsigned char direction_hmirror(unsigned char direction) {
  return ~direction + 1 & 0xFF;
}
inline unsigned char direction_vmirror(unsigned char direction) {
  return direction_sub(direction_hmirror(direction_sum(direction, 64)), 64);
}
inline unsigned short fpdirection_sum(unsigned short direction, int value) {
  return direction + value & 0xFFFF;
}
inline unsigned short fpdirection_sub(unsigned short direction, int value) {
  return direction - value & 0xFFFF;
}
#endif
