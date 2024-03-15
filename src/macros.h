#ifndef MACROS_H
#define MACROS_H

#define SET_BIT_0(value) (value |= 1)
#define SET_BIT_1(value) (value |= 2)
#define SET_BIT_2(value) (value |= 4)
#define SET_BIT_3(value) (value |= 8)
#define SET_BIT_4(value) (value |= 16)
#define SET_BIT_5(value) (value |= 32)
#define SET_BIT_6(value) (value |= 64)
#define SET_BIT_7(value) (value |= 128)

#define CLEAR_BIT_0(value) (value &= 0xFE)
#define CLEAR_BIT_1(value) (value &= 0xFD)
#define CLEAR_BIT_2(value) (value &= 0xFB)
#define CLEAR_BIT_3(value) (value &= 0xF7)
#define CLEAR_BIT_4(value) (value &= 0xEF)
#define CLEAR_BIT_5(value) (value &= 0xDF)
#define CLEAR_BIT_6(value) (value &= 0xBF)
#define CLEAR_BIT_7(value) (value &= 0x7F)

#define BIT_0_IS_SET(value) (value & 1)
#define BIT_1_IS_SET(value) (value & 2)
#define BIT_2_IS_SET(value) (value & 4)
#define BIT_3_IS_SET(value) (value & 8)
#define BIT_4_IS_SET(value) (value & 16)
#define BIT_5_IS_SET(value) (value & 32)
#define BIT_6_IS_SET(value) (value & 64)
#define BIT_7_IS_SET(value) (value & 128)

#define SPRITE_STATUS_UCHAR(pointer, offset) ((unsigned char*)pointer)[offset]
#define SPRITE_STATUS_SCHAR(pointer, offset) ((signed char*)pointer)[offset]
#define SPRITE_STATUS_USHORT(pointer, offset) ((unsigned short*)pointer)[offset / 2]
#define SPRITE_STATUS_SHORT(pointer, offset) ((short*)pointer)[offset / 2]
#define SPRITE_STATUS_ULONG(pointer, offset) ((unsigned long*)pointer)[offset / 4]
#define SPRITE_STATUS_LONG(pointer, offset) ((long*)pointer)[offset / 4]
#define SPRITE_STATUS_PSCHAR(pointer, offset) ((unsigned char**)pointer)[offset / 4]
#define SPRITE_STATUS_PHANDLER(pointer, offset) ((sprite_status_handler*)pointer)[offset / 4]

#define LONG_HIGH(value) (value / 65536 * 65536)
#define LONG_HIGH_TO_SHORT(value) (value / 65536)
#define LONG_LOW(value) (value % 65536)
#define SHORT_TO_LONG_HIGH(value) (value * 65536)

#endif
