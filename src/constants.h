#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum SKC_character_id {
  SONIC = 0,
  MILES = 1,
  KNUCKLES = 2
}
SKC_character_id;

typedef enum SKC_sprite_priority_id {
  PRI_0 = 0,
  PRI_1 = 128,
  PRI_2 = 256,
  PRI_3 = 384,
  PRI_4 = 512,
  PRI_5 = 640,
  PRI_6 = 768,
  PRI_7 = 896
}
SKC_sprite_priority_id;

typedef enum SKC_play_type {
  PLAY_TYPE_SONIC_AND_MILES = 0,
  PLAY_TYPE_SONIC = 1,
  PLAY_TYPE_MILES = 2,
  PLAY_TYPE_KNUCKLES = 3
}
SKC_play_type;

typedef enum start_game_modes {
  STARTGAMEMODE_NORMAL = 0,
  STARTGAMEMODE_SPECIALSTAGEMODE = 1,
  STARTGAMEMODE_DEBUG = 2
}
start_game_modes;

typedef enum sonic_game_modes {
  SONICGAMEMODE_SONIC3KNUCKLES = 0,
  SONICGAMEMODE_SONICKNUCKLES = 1,
  SONICGAMEMODE_SONIC3 = 2
}
sonic_game_modes;

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

#define RING_MAX 999
#define FLYRING_MAX 32
#define RING_EXTRA_LIFE_1 100
#define RING_EXTRA_LIFE_2 200

#endif
