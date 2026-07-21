#ifndef SPRITESTATUS_H
#define SPRITESTATUS_H

#include <stdbool.h>
#include "speed.h"
#include "spritestatushandler.h"
#include "swdata.h"
#include "../shared.h"

typedef struct SKC_actflg {
  unsigned int hflip : 1;
  unsigned int vflip : 1;
  unsigned int relative_coordinates : 1;
  unsigned int vspl : 1;
  unsigned int vspl2 : 1;
  unsigned int static_pattern : 1;
  unsigned int compound : 1;
  unsigned int onscreen : 1;
}
SKC_actflg;

typedef struct SKC_play_cddat {
  unsigned int left : 1;
  unsigned int jump : 1;
  unsigned int ball : 1;
  unsigned int ride : 1;
  unsigned int ballj : 1;
  unsigned int push : 1;
  unsigned int underwater : 1;
  unsigned int unused7 : 1;
}
SKC_play_cddat;

typedef struct SKC_play_powerdat {
  unsigned int baria : 1;
  unsigned int muteki : 1;
  unsigned int speedup : 1;
  unsigned int unused3 : 1;
  unsigned int fbaria : 1;
  unsigned int tbaria : 1;
  unsigned int abaria : 1;
  unsigned int mizuflag : 1;
}
SKC_play_powerdat;

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

typedef enum SKC_character_id {
  SONIC = 0,
  MILES = 1,
  KNUCKLES = 2
}
SKC_character_id;

typedef struct SKC_sprite_status {
  SKC_sprite_status_handler r_ptr; // 0x00
  SKC_actflg actflg; // 0x04
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
  union {
    struct {
      unsigned char b0; // 0x26
      unsigned char b1; // 0x27
    }
    b;
    unsigned short w; // 0x26
  }
  direc;
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
      }
      cddat;
      struct { // 0x2B
        unsigned int unused0 : 1;
        unsigned int unused1 : 1;
        unsigned int unused2 : 1;
        unsigned int baria_bounce : 1;
        unsigned int fbaria_die : 1;
        unsigned int tbaria_die : 1;
        unsigned int abaria_die : 1;
        unsigned int unused7 : 1;
      }
      powerdat;
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
        unsigned char unknown2; // 0x41
        unsigned char* p_cg; // 0x42
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
        unsigned int end : 1;
        unsigned int flicker : 1;
        unsigned int unused7 : 1;
      }
      actflg0;
      struct {
        signed char cnt; // 0x39
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
        unsigned char direction; // 0x3C
      }
      radius;
      struct {
        SKC_swdata prev_swdata; // 0x3A
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
          unsigned short mask; // 0x32
          unsigned short delay; // 0x34
          bool visible; // 0x36
        }
        appeariwa;
        struct {
          bool large_bubble; // 0x2E
          short xposi_init; // 0x30
          unsigned char large_bubble_timer; // 0x32
          unsigned char large_bubble_timer_init; // 0x33
          unsigned char pending_small_bubble_cnt; // 0x34
          unsigned short bitfield; // 0x36
          unsigned short small_bubble_timer; // 0x38
          unsigned char* tbl_ptr ; // 0x3C
        }
        awa;
        struct {
          bool plholding; // 0x32
          bool pl2holding; // 0x33
          unsigned char plnograb_timer; // 0x34
          unsigned char pl2nograb_timer; // 0x35
          short end1_offset; // 0x36
          short end2_offset; // 0x38
          bool breakable; // 0x3A
        }
        bar;
        struct {
          unsigned char* cg_ptr; // 0x38
          unsigned short** wrtpat_ptr; // 0x3C
          unsigned short vram_offset; // 0x40
        }
        baria;
        struct {
          unsigned short points; // 0x3E
        }
        bakuhatu;
        struct {
          unsigned char wait_shot_timer; // 0x39
          unsigned short timer_init; // 0x3A
          bool upside_down; // 0x3C
          unsigned char r_no_save; // 0x3D
          short xspeed_save; // 0x3E
        }
        betl04;
        struct {
          short accel; // 0x40
        }
        bg0a;
        struct {
          short xposi_init; // 0x30
          short yposi_init; // 0x32
        }
        bgsprz;
        struct {
          unsigned char* timer_data_ptr; // 0x30
          unsigned char* timer_data2_ptr; // 0x34
          unsigned char unknown; // 0x3A;
          unsigned char* slope_data_ptr; // 0x3C
          unsigned char unknown2; // 0x40
        }
        break_;
        struct {
          unsigned char unknown; // 0x32
          unsigned char patno_offset; // 0x34
        }
        break3;
        struct {
          unsigned char main_timer_init; // 0x35
          unsigned char child_timer_init; // 0x36
          unsigned char child_timer_increase; // 0x37
        }
        brhashi;
        struct {
          SKC_speed* spdtbl_ptr; // 0x34
          SKC_speed* spdtbl2_ptr; // 0x38
        }
        brkabe;
        struct {
          SKC_speed* spdtbl_ptr; // 0x3C
        }
        bryuka;
        struct {
          unsigned char tbl_index; // 0x39
          unsigned char unknown3a; // 0x3A
        }
        bs00b0_fexit;
        struct {
          unsigned char tbl_index; // 0x39
        }
        cchg0320_act;
        struct {
          unsigned char tbl_index; // 0x3A
        }
        cchg09;
        struct {
          unsigned short part_cnt; // 0x30
          unsigned short current_exit_no; // 0x32
        }
        clear;
        struct {
          unsigned short hvsize; // 0x32
          bool plupleft; // 0x34
          bool pl2upleft; // 0x35
          bool editupleft; // 0x36
        }
        colichg;
        struct {
          unsigned short hvsize; // 0x32
          bool plupleft; // 0x34
          bool pl2upleft; // 0x35
          unsigned char plcnt; // 0x36
          unsigned char pl2cnt; // 0x37
        }
        colichg2;
        struct {
          short xdestination; // 0x46
        }
        clear_part;
        struct {
          signed char yoffset_init;
        }
        clen0930;
        struct {
          bool miles; // 0x38
          unsigned short vram_offset; // 0x40
        }
        effect;
        struct {
          short prev_yposi; // 0x30
          short yposi_save; // 0x32
          short unknown3c; // 0x3C;
        }
        egjr0a;
        struct {
          unsigned short timer_init; // 0x30
          unsigned char direction; // 0x32
          unsigned char speed_rev_timer_init; // 0x33
          unsigned char speed_rev_timer; // 0x39
          unsigned short unknown3a; // 0x3A
          unsigned char posi; // 0x3C
          signed char speed; // 0x41
        }
        embl_hand;
        struct {
          unsigned short timer2; // 0x3A
          short shibuki_xoffset; // 0x40
        }
        ev0000;
        struct {
          short xposi_init; // 0x30
          short yposi_init; // 0x32
          short direc_mod; // 0x34
          bool dropping; // 0x36
          unsigned short direction; // 0x38
          unsigned char ko2; // 0x3E
        }
        evhashi;
        struct {
          signed char unknown39; // 0x39
          signed char unknown3a; // 0x3A
          signed char unknown3b; // 0x3B
        }
        explosion;
        struct {
          unsigned short unknown32; // 0x32
          unsigned short unknown34; // 0x34
          bool invisible; // 0x36
        }
        falltree;
        struct {
          unsigned char type; // 0x30
          short xspeed_init; // 0x32
          short yspeed_init; // 0x34
          bool masin; // 0x38
          short yposi_init; // 0x3A
          unsigned short points; // 0x3E
        }
        friend;
        struct {
          unsigned short left_limit;
          unsigned short right_limit;
        }
        friend07;
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
          unsigned char counter; // 0x39
        }
        hana00;
        struct {
          short scra_h_posit; // 0x3A
        }
        hscroll_chk;
        struct {
          short xoffset; // 0x30
          short yoffset; // 0x34
        }
        hstar;
        struct {
          unsigned char r_no1; // 0x3C
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
          unsigned char pldirec; // 0x3C
          unsigned char pl2direc; // 0x3D
        }
        iwa091;
        struct {
          short xposi_init; // 0x3A
          unsigned short tbl_index; // 0x3E
        }
        kanban;
        struct {
          short xposi_init; // 0x30
          short unknown32; // 0x32
          short unknown34; // 0x34
          short unknown36; // 0x36
          short unknown38; // 0x38
        }
        magnet;
        struct {
          short xoffset; // 0x30
          bool inactive; // 0x34
        }
        mask;
        struct {
          signed char side; // 0x32
          short yoffset; // 0x34
          short xposi_init; // 0x36
        }
        moveyuka;
        struct {
          signed char* patno_tbl_ptr; // 0x30
          unsigned char offset_tbl_index0; // 0x34
          unsigned char offset_tbl_index1; // 0x35
          unsigned char id; // 0x36
          unsigned char patno_tbl_index; // 0x38
        }
        muteki;
        struct {
          unsigned char footwk_pg_loop_cnt; // 0x39
          short accel; // 0x40
          unsigned short wrt_index; // 0x44
        }
        nk0930;
        struct {
          unsigned char tbl_index; // 0x39
        }
        nuckle030;
        struct {
          short xposi_init; // 0x3A
          bool prev_dir; // 0x3C
          unsigned char remaining_wobbles; // 0x39
          short xspeed_init; // 0x3E
          short xspeed_accel; // 0x40
        }
        nuckle061_dai;
        struct {
          signed char yspeed_mod; // 0x39
          unsigned short timer_init; // 0x3E;
        }
        nuckle071;
        struct {
          unsigned short wrt_index; // 0x42
        }
        nuckle072;
        struct {
          short yspeed_init; // 0x3E
        }
        obox04_friend;
        struct {
          short xspeed; // 0x3A
        }
        opnbox;
        struct {
          short yspeed_init; // 0x3E
        }
        opnbox_friend;
        struct {
          unsigned short freeze_timer; // 0x30
          unsigned char prev_patno; // 0x32
          short xposi_init; // 0x34
          unsigned char digit_timer; // 0x36
          unsigned char digit_timer_init; // 0x37
          unsigned char pending_bubble_cnt; // 0x38
          unsigned short bitfield; // 0x3A
          unsigned short bubble_timer; // 0x3E
          SKC_sprite_status* pl_ptr; // 0x40
        }
        plawa;
        struct {
          unsigned char player; // 0x3E
        }
        ring;
        struct {
          short offset; // 0x32
          unsigned char pldir; // 0x34
          unsigned char pl2dir; // 0x35
        }
        rollc;
        struct {
          signed char* slope_heights_ptr; // 0x32
          signed char patno_chg; // 0x36
          unsigned char patno_max; // 0x37
        }
        rollhashi;
        struct {
          unsigned short unknown2ew; // 0x2E
          unsigned short unknown30w; // 0x30
          unsigned char plholding; // 0x32
          unsigned char pl2holding; // 0x33
          unsigned char plnograb_timer; // 0x34
          unsigned char pl2nograb_timer; // 0x35
          unsigned short part_cnt; // 0x36
          unsigned short unknown38w; // 0x38
          unsigned short unknown3aw; // 0x3A
          unsigned char handle; // 0x40
          unsigned short unknown42w; // 0x42
          unsigned short unknown44w; // 0x44
          short xdestination; // 0x46
        }
        rope;
        struct {
          short prev_xposi; // 0x42
          short prev_yposi; // 0x44
        }
        rope_handle;
        struct {
          unsigned char move_timer; // 0x39
        }
        saru00;
        struct {
          unsigned char unknown3a; // 0x3A
          unsigned char unknown3b; // 0x3B
          unsigned char direction; // 0x3C
          unsigned char elbow; // 0x3E
          signed char side; // 0x40
        }
        saru00_arm;
        struct {
          short oya_xposi; // 0x30
          short oya_yposi; // 0x32
          unsigned short direction; // 0x34
          unsigned short counter; // 0x36
        }
        save;
        struct {
          short accel_max; // 0x3E
          short accel; // 0x40
        }
        sai00;
        struct {
          bool attacking; // 0x30
          unsigned char direction; // 0x34
        }
        sflicky;
        struct {
          unsigned char plmode; // 0x30
          unsigned char pl2mode; // 0x31
          unsigned char pltimer; // 0x32
          unsigned char pl2timer; // 0x33
          unsigned char timer_init; // 0x34
          unsigned short sound_ctr; // 0x36
        }
        shooter3;
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
          short recoil; // 0x30
          short xposi_init; // 0x32
          short yposi_init; // 0x34
          short offset; // 0x36
          bool reverse_dir; // 0x38
          unsigned char unknown3c; // 0x3C
        }
        spring;
        struct {
          short xoffset; // 0x30
          short yoffset; // 0x32
          unsigned short unknown38; // 0x38
        }
        springsw;
        struct {
          bool active; // 0x34
          bool posi_set_disabled; // 0x35
        }
        sstartrail;
        struct {
          unsigned short part_cnt; // 0x30
          unsigned short current_exit_no; // 0x32
          unsigned char wait_flag; // 0x34
          unsigned char act_start_flag; // 0x3E
          unsigned char vs_flag; // 0x44
          unsigned char unknown_flag; // 0x48
        }
        title;
        struct {
          short xdestination; // 0x46
        }
        title_part;
        struct {
          long plspeed; // 0x30
          long pl2speed; // 0x34
        }
        tloop;
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
          short yposi_init; // 0x30
          unsigned char rotation; // 0x32
          unsigned char bitfield; // 0x34
          unsigned char patcnt_save; // 0x35
          unsigned char water_flag_save; // 0x36
        }
        togetree;
        struct {
          unsigned short ringwk_index; // 0x30
        }
        tring;
        struct {
          bool paused;
        }
        water;
      }
      actfree;
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
    obj;
    struct {
      SKC_play_cddat cddat; // 0x2A
      SKC_play_powerdat powerdat; // 0x2B
      unsigned char air_timer; // 0x2C
      struct { // 0x2D
        unsigned int type : 7;
        unsigned int reverse : 1;
      }
      flip_mst;
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
      unsigned char direc_front; // 0x3A
      unsigned char direc_below; // 0x3B
      unsigned char convex_flag; // 0x3C
      unsigned char spindash_flag; // 0x3D
      short spindash_ctr; // 0x3E
      unsigned char jump_flag; // 0x40
      unsigned char force_direc_up_timer; // 0x41
      unsigned short ride_obj; // 0x42
      unsigned char height; // 0x44
      unsigned char width; // 0x45
      unsigned char top_solid_bit; // 0x46
      unsigned char lrb_solid_bit; // 0x47
    }
    play;
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
      unsigned char reserved1[2];
      short* p_posi;
    } ssm_starsphere;
  } actfree;
*/

#endif
