#ifndef SPRITE_STATUS_H
#define SPRITE_STATUS_H

typedef struct sprite_status sprite_status;
typedef void(*sprite_status_handler)(sprite_status*);
typedef struct sprite_status_child sprite_status_child;
typedef struct sprite_family_status sprite_family_status;

#include "constants.h"
#include "types.h"

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
      unsigned char reserved1[1];
      unsigned char talent_status;
      unsigned char reserved2[4];
      unsigned char invulnerability_timer;
      unsigned char reserved3[2];
      unsigned char eventflag;
      character_id character;
      unsigned char reserved4[4];
      unsigned char roll_status;
      unsigned char reserved5[2];
      unsigned char jump_status;
      unsigned char reserved6[5];
      unsigned short colibits;
      unsigned char reserved7[2];
    } player;
    struct {
      short timer;
      signed char* pg_data_ptr;
      sprite_status_handler callback_ptr;
      unsigned char status_bitfield;
      unsigned char reserved1[1];
      unsigned char prev_patno;
      unsigned char wchg_bit;
      unsigned short wrt_flg_index;
      short accel_max;
      short accel;
      signed char xoffset;
      signed char yoffset;
      unsigned short ko;
      unsigned short oya;
      unsigned short flagwork_index;
    } dynamic;
    struct {
      unsigned char reserved1[16];
      enemy_init0_data* init_data_ptr;
      unsigned char reserved2[8];
    } enemy_uninit_0;
    struct {
      unsigned short delay_timer;
      unsigned short part_cnt;
      unsigned short current_exit_no;
      unsigned char reserved[22];
    } actclear;
    struct {
      unsigned char reserved[24];
      short x_destination;
      unsigned short oya;
    } actclear_part;
    struct {
      short move_countdown;
      unsigned char reserved1[14];
      short yspeed;
      unsigned char reserved2[6];
      unsigned short oya;
      unsigned char reserved3[2];
    } friend;
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
    struct {
      short shot_countdown;
      signed char* pg_data_ptr;
      void(*callback_ptr)(sprite_status*);
      unsigned char reserved1[5];
      unsigned char counter;
      unsigned char reserved2[17];
    } hana00;
    struct {
      unsigned char reserved1[10];
      unsigned char status_bitfield;
      unsigned char reserved2[13];
      unsigned short oya;
      unsigned short flagwork_index;
    } obox04;
    struct {
      short attack_countdown;
      unsigned char reserved1[4];
      sprite_status_handler callback_ptr;
      unsigned char status_bitfield;
      unsigned char reserved2[5];
      short accel_max;
      short accel;
      unsigned char reserved3[8];
    } sai00;
    struct {
      unsigned char reserved1[2];
      signed char* pg_data_ptr;
      sprite_status_handler callback_ptr;
      unsigned char reserved2[18];
    } sai00_kemuri;
    struct {
      short timer;
      signed char* pg_data_ptr;
      sprite_status_handler callback_ptr;
      unsigned char status_bitfield;
      unsigned char wait_countdown;
      unsigned char reserved1;
      unsigned char arm_other_countdown;
      unsigned char arm_other_angle;
      unsigned char reserved2[1];
      unsigned short arm_other;
      signed char dir;
      unsigned char reserved3[3];
      unsigned short ko;
      unsigned short oya;
      unsigned char reserved4[2];
    } saru00;
    struct {
      unsigned char reserved1[2];
      signed char* pg_data_ptr;
      sprite_status_handler callback_ptr;
      unsigned char reserved2[18];
    } saru00_banana;
    struct {
      unsigned char reserved1[2];
      short parent_xposi;
      short parent_yposi;
      unsigned short angle;
      short counter;
      unsigned char reserved3[6];
      unsigned short parent;
      unsigned char reserved4[8];
      unsigned short flagwork_index;
    } save;
  } actfree;
}
sprite_status;

typedef struct sprite_status_child {
  short xposi;
  short yposi;
  unsigned char reserved;
  unsigned char patno;
}
sprite_status_child;

typedef struct sprite_family_status {
  sprite_status_handler r_ptr;
  unsigned char actflg;
  unsigned char r_no;
  unsigned char sprvs;
  unsigned char sprhs;
  unsigned short sprpri;
  unsigned short sproffset;
  signed char** patbase;
  short eldest_xposi;
  unsigned char reserved[2];
  short eldest_yposi;
  unsigned short child_cnt;
  sprite_status_child children[8];
  unsigned char actfree[26];
}
sprite_family_status;

#endif
