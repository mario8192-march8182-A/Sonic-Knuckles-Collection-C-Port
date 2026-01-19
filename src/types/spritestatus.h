#ifndef SPRITESTATUS_H
#define SPRITESTATUS_H

#include <stdbool.h>
#include "../constants.h"
#include "enemyinit0data.h"
#include "spritestatushandler.h"

typedef struct SKC_sprite_status {
  SKC_sprite_status_handler r_ptr; // 0x00
  struct {
    unsigned int hflip : 1;
    unsigned int vflip : 1;
    unsigned int relative_coordinates : 1;
    unsigned int vspl : 1;
    unsigned int vspl2 : 1;
    unsigned int static_pattern : 1;
    unsigned int compound : 1;
    unsigned int onscreen : 1;
  }
  actflg; // 0x04
  unsigned char r_no; // 0x05
  unsigned char sprvs; // 0x06
  unsigned char sprhs; // 0x07
  SKC_sprite_priority_id sprpri; // 0x08
  unsigned short sproffset; // 0x0A
  void* patbase; // 0x0C
  long xposi; // 0x10
  long yposi; // 0x14
  short xspeed; // 0x18
  short yspeed; // 0x1A
  short mspeed; // 0x1C
  unsigned char sprvsize; // 0x1E
  unsigned char sprhsize; // 0x1F
  unsigned char mstno; // 0x20
  unsigned char mstrestart; // 0x21
  unsigned char patno; // 0x22
  unsigned char patcnt; // 0x23
  unsigned char pattim; // 0x24
  unsigned char pattimm; // 0x25
  signed char direc1; // 0x26
  signed char direc2; // 0x27
  unsigned char colino; // 0x28
  unsigned char colicnt; // 0x29
  union {
    struct {
      struct { // 0x2A
        unsigned int right : 1;
        unsigned int down : 1;
        unsigned int wrt : 1;
        unsigned int plride : 1;
        unsigned int pl2ride : 1;
        unsigned int plpush : 1;
        unsigned int pl2push : 1;
        unsigned int die : 1;
        unsigned int unused8 : 1;
        unsigned int unused9 : 1;
        unsigned int unuseda : 1;
        unsigned int baria_bounce : 1;
        unsigned int flame_baria_die : 1;
        unsigned int thunder_baria_die : 1;
        unsigned int aqua_baria_die : 1;
        unsigned int unusedf : 1;
      }
      cddat;
      unsigned short userflag; // 0x2C
      unsigned short timer; // 0x2E
      struct {
        unsigned char flash_duration; // 0x2E
        unsigned char pattim; // 0x2F
      }
      get_fast_slow;
      struct {
        unsigned char pal_offset; // 0x30
        unsigned char target_pal_offset; // 0x32
        unsigned char step_cnt; // 0x39
        unsigned short timer_init; // 0x3A
        unsigned short cor_cnt; // 0x3C
      }
      fade;
      struct {
        long xposi; // 0x30
        long yposi; // 0x34
        unsigned short vram_offset; // 0x3A
        unsigned char unknown; // 0x40
      }
      zoom;
      signed char* pg_data_ptr; // 0x30
      unsigned long scralim_unknown; // 0x30;
      SKC_sprite_status_handler callback_ptr; // 0x34
      struct { // 0x38
        unsigned int puka_down : 1;
        unsigned int unused1 : 1;
        unsigned int unused2 : 1;
        unsigned int fura_right : 1;
        unsigned int ko_die : 1;
        unsigned int flash : 1;
        unsigned int flicker : 1;
        unsigned int unused7 : 1;
      }
      actflg0;
      struct {
        unsigned char cnt; // 0x39
        short accel_max; // 0x3E
        short accel; // 0x40
      }
      puka;
      struct {
        short accel_max; // 0x3A
        short accel; // 0x3C
      }
      fura;
      unsigned short scralim_unknown2; // 0x3A
      struct {
        unsigned char prev_patno; // 0x3A
        unsigned char flg_bit; // 0x3B
        unsigned short flg_index; // 0x3C;
      }
      wrt;
      struct {
        short unknown; // 0x3A
        unsigned char angle; // 0x3C
      }
      radius;
      struct {
        unsigned short prev_swdata; // 0x3A
        unsigned char lr_cnt; // 0x3C
        unsigned char timer; // 0x3D
        unsigned char pad; // 0x3E
      }
      gacha;
      struct {
        unsigned char timer; // 0x3A
        unsigned char command_index; // 0x3B
      }
      cchg;
      SKC_enemy_init0_data* enemy_init0_data_ptr; // 0x3E
      unsigned short score_id; // 0x3E
      struct {
        signed char x; // 0x42
        signed char y; // 0x43
      }
      oya_offset;
      unsigned char ko; // 0x44
      unsigned char oya; // 0x46
      unsigned short flagwork_index; // 0x48
      union {
        struct {
          unsigned char* timer_data_ptr; // 0x30
          unsigned char* timer_data2_ptr; // 0x34
          unsigned char unknown; // 0x3A;
          unsigned char* slope_data_ptr; // 0x3C
          unsigned char unknown2; // 0x40
        }
        break_;
        struct {
          short yspeed_init; // 0x3E
        }
        friend;
        struct {
          unsigned char darkness_level; // 0x42
          unsigned char sequence_no; // 0x43
        }
        gost08;
        struct {
          unsigned short spawn_timer; // 0x3A
        }
        gost08_ctr;
        struct {
          unsigned char unknown; // 0x3C
        }
        item;
        struct {
          short xposi_init; // 0x2E
          bool prev_plpush; // 0x3A
          bool prev_pl2push; // 0x3B
          unsigned char size_type; // 0x3C
          unsigned short push_timer; // 0x40
          unsigned short push_distance; // 0x42
          SKC_sprite_status_handler oya_r_ptr; // 0x44
        }
        iwa;
        struct {
          short yspeed_init; // 0x3E
        }
        obox04_friend;
        struct {
          short xspeed; // 0x3A
        }
        opnbox;
        struct {
          unsigned char player; // 0x3E
        }
        ring;
        struct {
          short oya_xposi; // 0x30
          short oya_yposi; // 0x32
          unsigned short angle; // 0x34
          unsigned short counter; // 0x36
        }
        save;
        struct {
          short* unknown2e_ptr; // 0x2E
          long angled_xposi; // 0x34
          long angled_yposi; // 0x38
          short oya_xposi; // 0x3C;
          short oya_yposi; // 0x3E;
          short unknown40; // 0x40
          short unknown42; // 0x42
        }
        slot_ring;
        struct {
          short xposi_init; // 0x30
          short yposi_init; // 0x32
          short offset; // 0x34
          bool reverse_dir; // 0x36
          unsigned short push_timer; // 0x3A
          unsigned short push_distance; // 0x3C
          bool prev_plpush; // 0x3E
          bool prev_pl2push; // 0x3F
        }
        toge;
        struct {
          unsigned short ringwk_index; // 0x30
        }
        tring;
      }
      actfree;
    }
    obj;
    struct {
      struct { // 0x2A
        unsigned int left : 1;
        unsigned int jump : 1;
        unsigned int ball : 1;
        unsigned int ride : 1;
        unsigned int ballj : 1;
        unsigned int push : 1;
        unsigned int underwater : 1;
        unsigned int unused7 : 1;
        unsigned int baria : 1;
        unsigned int muteki : 1;
        unsigned int speedup : 1;
        unsigned int unusedb : 1;
        unsigned int flame_baria : 1;
        unsigned int thunder_baria : 1;
        unsigned int aqua_baria : 1;
        unsigned int infinite_inertia : 1;
      }
      cddat;
      unsigned char air_timer; // 0x2C
      unsigned char flip_mst; // 0x2D
      unsigned char control_bitfield; // 0x2E
      unsigned char talent_status; // 0x2F
      unsigned char flip_rev_cnt; // 0x30
      unsigned char flip_rev_frame_cnt; // 0x31
      unsigned short hlock_timer; // 0x32
      unsigned char invulnerability_timer; // 0x34
      unsigned char muteki_timer; // 0x35
      unsigned char speedup_timer; // 0x36
      unsigned char eventflag; // 0x37
      SKC_character_id character; // 0x38
      unsigned char lever_ctr; // 0x39
      unsigned char angle_front; // 0x3A
      unsigned char angle_below; // 0x3B
      unsigned char convex_flag; // 0x3C
      unsigned char spindash_flag; // 0x3D
      unsigned short spindash_ctr; // 0x3E
      unsigned char jump_flag; // 0x40
      unsigned char unused41;
      unsigned short obj_index; // 0x42
      unsigned char height; // 0x44
      unsigned char width; // 0x45
      unsigned char top_solid_bit; // 0x46
      unsigned char lrb_solid_bit; // 0x47
    }
    play;
    struct {
      unsigned short child_cnt; // 0x16
      struct {
        short xposi;
        short yposi;
        unsigned char patno;
      }
      children[8]; // 0x18
    }
    compound;
  }
  u;
}
SKC_sprite_status;

/*
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
      short shot_countdown;
      signed char* pg_data_ptr;
      void(*callback_ptr)(sprite_status*);
      unsigned char reserved1[5];
      unsigned char counter;
      unsigned char reserved2[17];
    } hana00;
    struct {
      unsigned char reserved1[2];
      long yposiwk;
      unsigned char dir;
    } s3opening_banner;
    struct {
      unsigned char reserved1[2];
      long yposiwk;
      unsigned char dir;
    } skopening_banner;
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
      unsigned char sonicsmile_anim[2];
      unsigned char sonicfinger_anim[2];
      unsigned char knuckleshand1_anim[2];
      unsigned char knuckleshand2_anim[2];
    } skopening_anims;
    struct {
      unsigned char reserved1[2];
      long xposi;
      long yposi;
    } skopening_deathegg;
    struct {
      unsigned char reserved[22];
      short xposi;
      short yposi;
    } skopening_nameroulette;
    struct {
      short timer;
      unsigned char reserved1[4];
      sprite_status_handler callback_ptr;
      unsigned char status_bitfield;
      signed char puka_cnt;
      unsigned char reserved2[4];
      short accel_max;
      short accel;
      unsigned char reserved3[8];
    } snak00;
    struct {
      unsigned char reserved1[2];
      short recoil;
      short orig_xposi;
      short orig_yposi;
      short offset;
      unsigned short move_dir;
      unsigned short move_countdown;
      unsigned char unknown_flag;
      unsigned char reserved2[1];
      unsigned short child;
      unsigned char reserved3[10];
    } spring;
    struct {
      unsigned char reserved1[2];
      short xoffset;
      short yoffset;
      unsigned char reserved2[10];
      unsigned short parent;
      unsigned char reserved3[10];
    } springsw;
    struct {
      unsigned char reserved1[2];
      short* p_posi;
    } ssm_starsphere;
    struct {
      short delay_timer;
      unsigned short part_cnt;
      unsigned short current_exit_no;
      unsigned char wait_flag;
      unsigned char reserved1[9];
      unsigned char act_start_flag;
      unsigned char reserved2[5];
      unsigned char vs_flag;
      unsigned char reserved3[3];
      unsigned char unknown_flag;
      unsigned char reserved4[1];
    } title;
    struct {
      unsigned char reserved[24];
      short x_destination;
      unsigned short oya;
    } title_part;
    struct {
      long pldir_counter;
      long pl2dir_counter;
      short countdown;
      unsigned char reserved1[16];
    } tloop;
  } actfree;
*/

#endif
