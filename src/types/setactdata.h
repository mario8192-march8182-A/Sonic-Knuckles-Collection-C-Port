#ifndef SKC_SETACTDATA_H
#define SKC_SETACTDATA_H

#include "enemyinitdata.h"
#include "spritestatushandler.h"

typedef struct SKC_set_act00_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    signed char xoffset;
    signed char yoffset;
  }
  data[];
}
SKC_set_act00_data;

typedef struct SKC_set_act01_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    SKC_enemy_init0_data* enemy_init0_data_ptr;
    signed char* pg_data_ptr;
    SKC_sprite_status_handler callback_ptr;
    signed char xoffset;
    signed char yoffset;
    short xspeed;
    short yspeed;
  }
  data[];
}
SKC_set_act01_data;

typedef struct SKC_set_act02_data {
  unsigned short cnt;
  SKC_sprite_status_handler r_ptr;
  signed char xoffset;
  signed char yoffset;
}
SKC_set_act02_data;

typedef struct SKC_set_act03_data {
  unsigned short cnt;
  SKC_sprite_status_handler r_ptr;
}
SKC_set_act03_data;

typedef struct SKC_set_act04_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    SKC_enemy_init0_data* enemy_init0_data_ptr;
    signed char* pg_data_ptr;
    SKC_sprite_status_handler callback_ptr;
    signed char xoffset;
    signed char yoffset;
    short xspeed;
    short yspeed;
  }
  data[];
}
SKC_set_act04_data;

typedef struct SKC_set_act05_data {
  unsigned short cnt;
  SKC_sprite_status_handler r_ptr;
}
SKC_set_act05_data;

typedef struct SKC_set_act06_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    signed char xoffset;
    signed char yoffset;
  }
  data[];
}
SKC_set_act06_data;

typedef struct SKC_set_act07_data {
  unsigned short cnt;
  SKC_sprite_status_handler r_ptr;
}
SKC_set_act07_data;

typedef struct SKC_set_act08_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
  }
  data[];
}
SKC_set_act08_data;

typedef struct SKC_set_act09_data {
  unsigned short cnt;
  struct {
    SKC_sprite_status_handler r_ptr;
    signed char xoffset;
    signed char yoffset;
  }
  data[];
}
SKC_set_act09_data;

#endif
