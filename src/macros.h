#ifndef MACROS_H
#define MACROS_H

#include "constants.h"

#define SET_BIT_0(value) (value |= 1)
#define SET_BIT_1(value) (value |= 2)
#define SET_BIT_2(value) (value |= 4)
#define SET_BIT_3(value) (value |= 8)
#define SET_BIT_4(value) (value |= 16)
#define SET_BIT_5(value) (value |= 32)
#define SET_BIT_6(value) (value |= 64)
#define SET_BIT_7(value) (value |= 128)
#define SET_BIT(value, bit) (value |= 1 << (bit))

#define CLEAR_BIT_0(value) (value &= 0xFE)
#define CLEAR_BIT_1(value) (value &= 0xFD)
#define CLEAR_BIT_2(value) (value &= 0xFB)
#define CLEAR_BIT_3(value) (value &= 0xF7)
#define CLEAR_BIT_4(value) (value &= 0xEF)
#define CLEAR_BIT_5(value) (value &= 0xDF)
#define CLEAR_BIT_6(value) (value &= 0xBF)
#define CLEAR_BIT_7(value) (value &= 0x7F)
#define CLEAR_BIT(value, bit) (value &= ~(bit))

#define TOGGLE_BIT_0(value) (value ^= 1)
#define TOGGLE_BIT_1(value) (value ^= 2)
#define TOGGLE_BIT_2(value) (value ^= 4)
#define TOGGLE_BIT_3(value) (value ^= 8)
#define TOGGLE_BIT_4(value) (value ^= 16)
#define TOGGLE_BIT_5(value) (value ^= 32)
#define TOGGLE_BIT_6(value) (value ^= 64)
#define TOGGLE_BIT_7(value) (value ^= 128)
#define TOGGLE_BIT(value, bit) (value ^= 1 << (bit))

#define BIT_0_IS_SET(value) (value & 1)
#define BIT_1_IS_SET(value) (value & 2)
#define BIT_2_IS_SET(value) (value & 4)
#define BIT_3_IS_SET(value) (value & 8)
#define BIT_4_IS_SET(value) (value & 16)
#define BIT_5_IS_SET(value) (value & 32)
#define BIT_6_IS_SET(value) (value & 64)
#define BIT_7_IS_SET(value) (value & 128)
#define BIT_IS_SET(value, bit) (value &= 1 << (bit))


// actflg bits

#define SET_HFLIP(value) (SET_BIT_0(value))
#define SET_VFLIP(value) (SET_BIT_1(value))
#define SET_USE_LEVEL_COORDS(value) (SET_BIT_2(value))
#define SET_STATIC_PATTERN(value) (SET_BIT_5(value))
#define SET_ONSCREEN(value) (SET_BIT_7(value))

#define CLEAR_HFLIP(value) (CLEAR_BIT_0(value))
#define CLEAR_VFLIP(value) (CLEAR_BIT_1(value))
#define SET_USE_SCREEN_COORDS(value) (CLEAR_BIT_2(value))

#define TOGGLE_HFLIP(value) (TOGGLE_BIT_0(value))
#define TOGGLE_VFLIP(value) (TOGGLE_BIT_1(value))

#define IS_HFLIP(value) (BIT_0_IS_SET(value))
#define IS_VFLIP(value) (BIT_1_IS_SET(value))
#define IS_ONSCREEN(value) (BIT_7_IS_SET(value))


// player cddat2 bits

#define SET_BARIA(value) SET_BIT_0(value)
#define SET_MUTEKI(value) SET_BIT_1(value)
#define SET_SPEEDUP(value) SET_BIT_2(value)
#define SET_FLAME_BARIA(value) SET_BIT_4(value)
#define SET_THUNDER_BARIA(value) SET_BIT_5(value)
#define SET_AQUA_BARIA(value) SET_BIT_6(value)


#define SPRITE_STATUS_UCHAR(pointer, offset) ((unsigned char*)pointer)[offset]
#define SPRITE_STATUS_SCHAR(pointer, offset) ((signed char*)pointer)[offset]
#define SPRITE_STATUS_USHORT(pointer, offset) ((unsigned short*)pointer)[offset / 2]
#define SPRITE_STATUS_SHORT(pointer, offset) ((short*)pointer)[offset / 2]
#define SPRITE_STATUS_ULONG(pointer, offset) ((unsigned long*)pointer)[offset / 4]
#define SPRITE_STATUS_LONG(pointer, offset) ((long*)pointer)[offset / 4]
#define SPRITE_STATUS_PSCHAR(pointer, offset) ((unsigned char**)pointer)[offset / 4]
#define SPRITE_STATUS_PHANDLER(pointer, offset) ((sprite_status_handler*)pointer)[offset / 4]

#define LONG_HIGH(value) (value / 65536)
#define LONG_LOW(value) (value % 65536)
#define SHORT_TO_LONG_HIGH(value) (value * 65536)

#define IS_ENDING(structure) (structure.zone == ANGEL_ISLAND_DUMMY_AND_ENDING && structure.act == 1)
#define IS_LAVA_REEF_BOSS(structure) (structure.zone == LAVA_REEF_BOSS_AND_HIDDEN_PALACE && structure.act == 0)
#define IS_HIDDEN_PALACE(structure) (structure.zone == LAVA_REEF_BOSS_AND_HIDDEN_PALACE && structure.act == 1)
#define IS_DEATH_EGG_BOSS(structure) (structure.zone == DEATH_EGG_BOSS_AND_MASTER_EMERALD_SHRINE && structure.act == 0)
#define IS_MASTER_EMERALD_SHRINE(structure) (structure.zone == DEATH_EGG_BOSS_AND_MASTER_EMERALD_SHRINE && structure.act == 1)

#endif
