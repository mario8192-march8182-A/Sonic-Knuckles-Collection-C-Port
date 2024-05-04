#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum character_id {
  SONIC = 0,
  MILES = 1,
  KNUCKLES = 2
}
character_id;

typedef enum bonus_stage_id {
  BONUS_STAGE_ROLLING_JUMP = 0,
  BONUS_STAGE_SLOT_MACHINE = 1,
  BONUS_STAGE_GUMBALL_MACHINE = 2
}
bonus_stage_id;

typedef enum zone_id {
  ANGEL_ISLAND = 0x00,
  HYDROCITY = 0x01,
  MARBLE_GARDEN = 0x02,
  CARNIVAL_NIGHT = 0x03,
  FLYING_BATTERY = 0x04,
  ICECAP = 0x05,
  LAUNCH_BASE = 0x06,
  MUSHROOM_HILL = 0x07,
  SANDOPOLIS = 0x08,
  LAVA_REEF = 0x09,
  SKY_SANCTUARY = 0x0A,
  DEATH_EGG = 0x0B,
  DOOMSDAY = 0x0C,
  ANGEL_ISLAND_DUMMY_AND_ENDING = 0x0D,
  AZURE_LAKE = 0x0E,
  BALLOON_PARK = 0x0F,
  DESERT_PALACE = 0x10,
  CHROME_GADGET = 0x11,
  ENDLESS_MINE = 0x12,
  ZONE_GUMBALL_MACHINE = 0x13,
  ZONE_SLOT_MACHINE = 0x14,
  ZONE_ROLLING_JUMP = 0x15,
  LAVA_REEF_BOSS_AND_HIDDEN_PALACE = 0x16,
  DEATH_EGG_BOSS_AND_MASTER_EMERALD_SHRINE = 0x17
}
zone_id;

typedef enum sprite_priority {
  PRI_0 = 0,
  PRI_1 = 128,
  PRI_2 = 256,
  PRI_3 = 384,
  PRI_4 = 512,
  PRI_5 = 640,
  PRI_6 = 768,
  PRI_7 = 896
}
sprite_priority;

typedef enum character_team_id {
  TEAM_SONIC_AND_MILES = 0,
  TEAM_SONIC = 1,
  TEAM_MILES = 2,
  TEAM_KNUCKLES = 3
}
character_team_id;

typedef enum object_cddat1_bits {
  CD_RIGHT = 0,
  CD_DOWN = 1,
  CD_WRT = 2,
  CD_PLRIDE = 3,
  CD_PL2RIDE = 4,
  CD_PLPUSH = 5,
  CD_PL2PUSH = 6,
  CD_DIE = 7
}
object_cddat1_bits;

typedef enum player_cddat1_bits {
  CD_LEFT = 0,
  CD_JUMP = 1,
  CD_BALL = 2,
  CD_RIDE = 3,
  CD_BALLJ = 4,
  CD_PUSH = 5,
  CD_UNDERWATER = 6
}
player_cddat1_bits;

#define SPEEDUPTIMER 54
#define FOOTDIR 58
#define KO_ADR 68
#define OYA_ADR 70

#define PBUFFER_LEVELS 8
#define PBUFFER_LEVEL_SLOTS 64
#define PBUFFER_LEVEL_SLOT_SIZE 2
#define PBUFFER_LEVEL_MAX_SIZE 126

#define ACTWK_SLOTS 110
#define ACTWK_DYNAMIC_START 3
#define ACTWK_RESERVED_START 93

#define COLBUFFER_SLOTS 64
#define COLBUFFER_SLOT_SIZE 2
#define COLBUFFER_MAX_SIZE 126

#define RINGWK_SLOTS 512

#define FLAGWORK_SLOTS 768

#define RINGBUFFER_SLOTS 64

#define LEVEL_TRIGGERS_SLOTS 16

#define EMY_WRT_FLG_SLOTS 8

#define PG_CONTROL_NULL 0
#define PG_CONTROL_LOOP 4
#define PG_CONTROL_NEXT 8
#define PG_CONTROL_END 12

#define PS_CONTROL_LOOP -1
#define PS_CONTROL_REWIND -2
#define PS_CONTROL_NEXT -3
#define PS_CONTROL_ROUTINE -4
#define PS_CONTROL_FOUT -5

#endif
