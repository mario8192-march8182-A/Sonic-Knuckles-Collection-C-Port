#ifndef TYPES_H
#define TYPES_H

typedef struct set_act05_data set_act05_data;
typedef struct wrt_data wrt_data;
typedef struct wrt_init_data wrt_init_data;
typedef struct cg_data_entry cg_data_entry;
typedef struct cg_data cg_data;
typedef struct enemy_init0_data enemy_init0_data;
typedef struct set_act00_data_entry set_act00_data_entry;
typedef struct set_act00_data set_act00_data;
typedef struct enemy_init2_data enemy_init2_data;
typedef struct zone_act zone_act;
typedef struct act_timer act_timer;
typedef struct actclear_init_data actclear_init_data;
typedef struct set_act03_data set_act03_data;
typedef struct enemy_init1_data enemy_init1_data;
typedef struct set_act02_data set_act02_data;

#include "constants.h"
#include "sprite_status.h"

typedef struct set_act05_data {
  short cnt;
  sprite_status_handler act;
}
set_act05_data;

typedef struct wrt_data {
  unsigned char* pat;
  unsigned short** wrtpat;
}
wrt_data;

typedef struct wrt_init_data {
  unsigned short cnt;
  unsigned short sproffset;
  unsigned short offset_increase;
  unsigned short flg_index;
  signed char** patbase;
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
wrt_init_data;

typedef struct cg_data_entry {
  unsigned char* tiles_ptr;
  unsigned short offset;
}
cg_data_entry;

typedef struct cg_data {
  unsigned short cnt;
  cg_data_entry data[];
}
cg_data;

typedef struct enemy_init0_data {
  signed char** patbase;
  unsigned short sproffset;
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
enemy_init0_data;

typedef struct set_act00_data_entry {
  sprite_status_handler r_ptr;
  signed char xoffset;
  signed char yoffset;
}
set_act00_data_entry;

typedef struct set_act00_data {
  unsigned short cnt;
  set_act00_data_entry data[];
}
set_act00_data;

typedef struct enemy_init2_data {
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
enemy_init2_data;

typedef struct zone_act {
  zone_id zone;
  unsigned char act;
}
zone_act;

typedef struct act_timer {
  unsigned char hours;
  unsigned char minutes;
  unsigned char seconds;
  unsigned char frames;
}
act_timer;

typedef struct actclear_init_data {
  sprite_status_handler r_ptr;
  short x_destination;
  short xposi;
  short yposi;
  unsigned char patno;
  unsigned char sprhs;
  unsigned short exit_no;
}
actclear_init_data;

typedef struct set_act01_data_entry {
  sprite_status_handler r_ptr;
  enemy_init0_data* enemy_init0_data_ptr;
  signed char* pg_data_ptr;
  sprite_status_handler callback_ptr;
  signed char xoffset;
  signed char yoffset;
  short xspeed;
  short yspeed;
}
set_act01_data_entry;

typedef struct set_act01_data {
  unsigned short cnt;
  set_act01_data_entry data[];
}
set_act01_data;

typedef struct set_act03_data {
  unsigned short cnt;
  sprite_status_handler r_ptr;
}
set_act03_data;

typedef struct enemy_init1_data {
  unsigned short sproffset;
  unsigned short sprpri;
  unsigned char sprhs;
  unsigned char sprvs;
  unsigned char patno;
  unsigned char colino;
}
enemy_init1_data;

typedef struct set_act02_data {
  unsigned short cnt;
  sprite_status_handler r_ptr;
  signed char xoffset;
  signed char yoffset;
}
set_act02_data;

#endif
