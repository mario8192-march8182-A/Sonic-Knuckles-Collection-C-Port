#ifndef SPRITE_STATUS_H
#define SPRITE_STATUS_H

#include "constants.h"

typedef struct sprite_status sprite_status;
typedef void(*sprite_status_handler)(sprite_status*);

typedef struct sprite_status {
  // 0x00
  sprite_status_handler r_ptr;
  // 0x04
  unsigned char actflg;
  // 0x05
  unsigned char r_no;
  // 0x06
  unsigned char sprvs;
  // 0x07
  unsigned char sprhs;
  // 0x08
  unsigned short sprpri;
  // 0x0A
  unsigned short sproffset;
  // 0x0C
  signed char** patbase;
  // 0x10
  long xposi;
  // 0x14
  long yposi;
  // 0x18
  short xspeed;
  // 0x1A
  short yspeed;
  // 0x1C
  short mspeed;
  // 0x1E
  unsigned char sprvsize;
  // 0x1F
  unsigned char sprhsize;
  // 0x20
  unsigned char mstno;
  // 0x21
  unsigned char restart;
  // 0x22
  unsigned char patno;
  // 0x23
  unsigned char patcnt;
  // 0x24
  unsigned char pattim;
  // 0x25
  unsigned char pattimm;
  // 0x26
  signed char direc1;
  // 0x27
  signed char direc2;
  // 0x28
  unsigned char colino;
  // 0x29
  unsigned char colicnt;
  // 0x2A
  unsigned char cddat1;
  // 0x2B
  unsigned char cddat2;
  // 0x2C
  unsigned char userflag1;
  // 0x2D
  unsigned char userflag2;
  // 0x2E
  union {
    unsigned char generic[28];
    struct {
      unsigned char reserved1[6];
      unsigned char invulnerability_timer;
      unsigned char reserved2[3];
      character_id character;
      unsigned char reserved3[17];
    } player;
    struct {
      short attack_countdown;
      signed char* pg_data_ptr;
      sprite_status_handler callback_ptr;
      unsigned char puka_axis_dir;
      unsigned char reserved1;
      unsigned char reserved2[4];
      short accel_max;
      short accel;
      unsigned char darkness_level;
      unsigned char sequence_no;
      unsigned char reserved3[6];
    } gost08;
    struct {
      unsigned char reserved1[12];
      short ghost_countdown;
      unsigned char reserved2[14];
    } gost08_ctr;
  } actfree;
}
sprite_status;

#endif
