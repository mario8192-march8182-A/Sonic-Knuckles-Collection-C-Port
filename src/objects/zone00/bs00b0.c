#include "bs00b0.h"
#include <string.h>
#include "../../data/cg/zone00/bs00b0.h"
#include "../../data/pat/zone00/bs00b0.h"
#include "../../types/enemyinitdata.h"
#include "../../types/setactdata.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../utils/bits.h"
#include "../../utils/fp16.h"
#include "../../utils/stageno.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../dev.h"
#include "../../etc.h"
#include "../../reloader.h"
#include "../../shared.h"
#include "../../sound.h"
#include "../eggmbl.h"
#include "../nuckle.h"
#include "../opnbox.h"
static unsigned short bs00b0_lim_tbls[3];
static unsigned short bs00b0_lim_tbln[3];
static void bs00b0_chk_scr(SKC_sprite_status* p_actwk);
static void bs00b0_move_init(SKC_sprite_status* p_actwk);
static void bs00b0_move(SKC_sprite_status* p_actwk);
static void bs00b0_init(SKC_sprite_status* p_actwk);
static void bs00b0_aper0_init(SKC_sprite_status* p_actwk);
static void bs00b0_aper0(SKC_sprite_status* p_actwk);
static void bs00b0_aper1_init(SKC_sprite_status* p_actwk);
static void bs00b0_aper1(SKC_sprite_status* p_actwk);
static void bs00b0_puka0_init0(SKC_sprite_status* p_actwk);
static void bs00b0_puka_init(SKC_sprite_status* p_actwk);
static void bs00b0_puka0(SKC_sprite_status* p_actwk);
static void bs00b0_wait0_init0(SKC_sprite_status* p_actwk);
static void bs00b0_wait0_init1(SKC_sprite_status* p_actwk);
static void bs00b0_wait0_init2(SKC_sprite_status* p_actwk);
static void bs00b0_wait0(SKC_sprite_status* p_actwk);
static void bs00b0_away0_init(SKC_sprite_status* p_actwk);
static void bs00b0_away0(SKC_sprite_status* p_actwk);
static void bs00b0_move0_init(SKC_sprite_status* p_actwk);
static void bs00b0_move0(SKC_sprite_status* p_actwk);
static void bs00b0_move1(SKC_sprite_status* p_actwk);
static void bs00b0_wait1_init(SKC_sprite_status* p_actwk);
static void bs00b0_die0(SKC_sprite_status* p_actwk);
static void bs00b0_die1_init(SKC_sprite_status* p_actwk);
static void bs00b0_die1(SKC_sprite_status* p_actwk);
static void bs00b0_die2_init(SKC_sprite_status* p_actwk);
static void set_opnbox(SKC_sprite_status* p_actwk);
static void bs00b0_die2(SKC_sprite_status* p_actwk);
static void bs00b0_die3(SKC_sprite_status* p_actwk);
static void bs00b0_die4(SKC_sprite_status* p_actwk);
static void bs00b0_die5(SKC_sprite_status* p_actwk);
static void bs00b0_die50(SKC_sprite_status* p_actwk);
static void bs00b0_die6(SKC_sprite_status* p_actwk);
static void bs00b0_die7(SKC_sprite_status* p_actwk);
static void bs00b0_arm(SKC_sprite_status* p_actwk);
static void bs00b0_arm_init(SKC_sprite_status* p_actwk);
static void bs00b0_arm_wait0(SKC_sprite_status* p_actwk);
static void bs00b0_arm_wait1(SKC_sprite_status* p_actwk);
static void arm_aper0_init(SKC_sprite_status* p_actwk);
static void bs00b0_arm_aper0(SKC_sprite_status* p_actwk);
static void arm_wait2_init(SKC_sprite_status* p_actwk);
static void bs00b0_arm_shot0(SKC_sprite_status* p_actwk);
static void bs00b0_arm_shot1(SKC_sprite_status* p_actwk);
static void bs00b0_arm_die0(SKC_sprite_status* p_actwk);
static void arm_die1_init(SKC_sprite_status* p_actwk);
static void bs00b0_fexit_init(SKC_sprite_status* p_actwk);
static void bs00b0_fexit_wait0(SKC_sprite_status* p_actwk);
static void bs00b0_fexit_wait1(SKC_sprite_status* p_actwk);
static void fexit_wait2_init(SKC_sprite_status* p_actwk);
static void fexit_wait0_init(SKC_sprite_status* p_actwk);
static void bs00b0_fexit_wait2(SKC_sprite_status* p_actwk);
static void fexit_wait1_init(SKC_sprite_status* p_actwk);
static void bs00b0_flash(SKC_sprite_status* p_actwk);
static void bs00b0_flash_wait0(SKC_sprite_status* p_actwk);
static void set_fire(SKC_sprite_status* p_actwk);
static void flash_die(SKC_sprite_status* p_actwk);
static void bs00b0_fire(SKC_sprite_status* p_actwk);
static void bs00b0_fire_move0(SKC_sprite_status* p_actwk);
static void bs00b0_fire_move1(SKC_sprite_status* p_actwk);
static void fire_move1_init(SKC_sprite_status* p_actwk);
static void bs00b0_kakera(SKC_sprite_status* p_actwk);
static void bs00b0_kakera_wait0(SKC_sprite_status* p_actwk);
static void embl_water(SKC_sprite_status* p_actwk);
static void embl_water_wait0(SKC_sprite_status* p_actwk);
static void bs00b0_water(SKC_sprite_status* p_actwk);
static void bs00b0_water_wait0(SKC_sprite_status* p_actwk);
static void water_fall0_init(SKC_sprite_status* p_actwk);
static void bs00b0_water_fall0(SKC_sprite_status* p_actwk);
static void bs00b0_break(SKC_sprite_status* p_actwk);
static void set_bs00b0_posi(SKC_sprite_status* p_actwk);
static void set_bs00b0_posi0(SKC_sprite_status* p_actwk, unsigned short direction);
static void set_fexit_posi(SKC_sprite_status* p_actwk);
static void set_flash(SKC_sprite_status* p_actwk);
static void set_fire_init(SKC_sprite_status* p_actwk);
static void chk_bs00b0_damage(SKC_sprite_status* p_actwk);
static void chg_bs00b0_cor(unsigned short index);
static void reset_bs00b0_dat(SKC_sprite_status* p_actwk);
static void chk_arm_die(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data bs00b0_init_tbl;
static SKC_enemy_init2_data bs00b0_arm_init_tbl;
static SKC_enemy_init2_data bs00b0_fexit_init_tbl;
static SKC_enemy_init2_data bs00b0_flash_init_tbl;
static SKC_enemy_init2_data bs00b0_fire_init_tbl;
static SKC_enemy_init2_data bs00b0_kakera_init_tbl;
static SKC_enemy_init1_data bs00b0_water_init_tbl;
static SKC_enemy_init0_data embl_water_init_tbl;
static SKC_enemy_init2_data bs00b0_break_init_tbl;
static SKC_set_act00_data bs00b0_set_tbl;
static SKC_set_act00_data bs00b0_fexit_set_tbl;
static SKC_set_act00_data bs00b0_water_set_tbl;
static SKC_set_act00_data embl_water_set_tbl;
static SKC_set_act00_data bs00b0_flash_set_tbl00;
static SKC_set_act00_data bs00b0_flash_set_tbl04;
static SKC_set_act00_data bs00b0_flash_set_tbl0c;
static SKC_set_act00_data bs00b0_fire_set_tbl;
static SKC_set_act00_data bs00b0_kakera_set_tbl;
static SKC_set_act00_data bs00b0_break_set_tbl;
static SKC_set_act05_data opnbox_set_tbl;
static SKC_set_act05_data nuckle_set_tbl;
static signed char bs00b0_pg00[27];
static signed char bs00b0_pg01[11];
static signed char bs00b0_arm_pg00[11];
static signed char bs00b0_flash_pg00[42];
static signed char bs00b0_flash_pg01[42];
static signed char bs00b0_fire_pg00[6];
static signed char bs00b0_fire_pg04[6];
static signed char bs00b0_fire_pg01[6];
static signed char bs00b0_kakera_pg00[9];
static signed char bs00b0_kakera_pg01[9];
static signed char embl_water_pg00[9];
static signed char bs00b0_water_pg00[27];
static signed char bs00b0_water_pg01[27];
static unsigned short boss00b0color[16];

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


static unsigned short bs00b0_lim_tbls[3] = { 0x4880, 0x48E0, 0x15A };
static unsigned short bs00b0_lim_tbln[3] = { 0x4100, 0x4160, 0x5DA };


void bs00b0(SKC_sprite_status* p_actwk) {
  unsigned short* p_lim_tbl = g_ram.actwk[0].u.play.character != KNUCKLES ? bs00b0_lim_tbls : bs00b0_lim_tbln;
  g_ram.DAT_08fffa82 = p_lim_tbl[0];
  g_ram.DAT_08fffa84 = p_lim_tbl[1];
  bs00b0_chk_scr(p_actwk);
}


static void bs00b0_chk_scr(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffa82 > g_ram.scra_h_posit >> 16) return;

  g_ram.scralim_left = g_ram.DAT_08fffa82;
  g_ram.scralim_right = g_ram.DAT_08fffa82;
  p_actwk->u.obj.timer = 120;
  p_actwk->u.obj.callback_ptr = &bs00b0_move_init;
  bgmset(-31);
  g_ram.bossstart = 1;
  g_ram.DAT_08fffaa2 = 0;
  g_ram.DAT_08fffaa3 = 0;
  divdevset(107);
  unlze_moduled(&g_vram[0x3000], bs00b0_cg);
  set_emy_cor(&boss00b0color);
}


static void bs00b0_move_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &bs00b0_move;
  bgmset(25);
  g_ram.bgm_act = 25;
}


static void bs00b0_move(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[8] = {
    &bs00b0_init,
    &bs00b0_aper0,
    &bs00b0_aper1,
    &bs00b0_puka0,
    &bs00b0_wait0,
    &bs00b0_aper0,
    &bs00b0_move0,
    &bs00b0_move1
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  if (p_actwk->u.obj.actflg0.flicker == 0) {
    chk_actsubc(p_actwk);
  }
}


static void bs00b0_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &bs00b0_init_tbl);
  p_actwk->colino = 8;
  p_actwk->actflg.hflip = 1;
  SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &eggmbl00_set_tbl);
  if (p_new_actwk != 0) {
    p_new_actwk->u.obj.userflag = 8;
  }
  set_act00(p_actwk, &bs00b0_set_tbl);
  bs00b0_aper0_init(p_actwk);
}


static void bs00b0_aper0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  soundset(75);
  p_actwk->u.obj.actflg0.fura_right = 1;
  p_actwk->u.obj.actflg0.flicker = 1;
  p_actwk->u.obj.callback_ptr = &bs00b0_aper1_init;
  p_actwk->colino = 0;
  reset_bs00b0_dat(p_actwk);
  p_actwk->actflg.hflip = p_actwk->direc.w < 8;
  set_act00(p_actwk, &bs00b0_water_set_tbl);
}


static void bs00b0_aper0(SKC_sprite_status* p_actwk) {
  time_pg0(p_actwk, bs00b0_pg00);
  p_actwk->u.obj.actflg0.flicker = p_actwk->patno == 43;
}


static void bs00b0_aper1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.actflg0.flicker = 0;
  SET_BIT(p_actwk->sproffset, 15);
  p_actwk->colino = 0x16;
  p_actwk->u.obj.callback_ptr = &bs00b0_puka0_init0;
  set_act00(p_actwk, &embl_water_set_tbl);
}


static void bs00b0_aper1(SKC_sprite_status* p_actwk) {
  time_pg0(p_actwk, bs00b0_pg01);
  chk_bs00b0_damage(p_actwk);
}


static void bs00b0_puka0_init0(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->u.obj.timer = 31;
  p_actwk->u.obj.callback_ptr = &bs00b0_wait0_init0;
  bs00b0_puka_init(p_actwk);
}


static void bs00b0_puka_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.accel_max = 0xC0;
  p_actwk->yspeed = 0xC0;
  p_actwk->u.obj.puka.accel = 0x10;
  p_actwk->u.obj.actflg0.puka_down = 0;
}


static void bs00b0_puka0(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  dec_timer(p_actwk);
  chk_bs00b0_damage(p_actwk);
}


static void bs00b0_wait0_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.unused1 = 1;
  if (p_actwk->u.obj.actflg0.unused7 == 0) {
    p_actwk->direc.w = 4;
    p_actwk->u.obj.timer = 47;
    p_actwk->u.obj.callback_ptr = &bs00b0_wait0_init2;
  }
  else {
    p_actwk->u.obj.timer = g_ram.actwk[0].u.play.character != KNUCKLES ? 191 : 255;
    p_actwk->u.obj.callback_ptr = &bs00b0_wait0_init1;
  }
}


static void bs00b0_wait0_init1(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->u.obj.timer = 63;
  p_actwk->u.obj.callback_ptr = &bs00b0_away0_init;
  p_actwk->u.obj.actflg0.unused1 = 0;
  p_actwk->u.obj.actflg0.fura_right = 0;
}


static void bs00b0_wait0_init2(SKC_sprite_status* p_actwk) {
  g_ram.DAT_08fffaa2 = 0xFF;
  p_actwk->u.obj.timer = 143;
  p_actwk->u.obj.callback_ptr = &bs00b0_wait0_init1;
}


static void bs00b0_wait0(SKC_sprite_status* p_actwk) {
  chk_bs00b0_damage(p_actwk);
  dec_timer(p_actwk);
}


static void bs00b0_away0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 10;
  soundset(75);
  p_actwk->u.obj.callback_ptr = &bs00b0_away0;
  p_actwk->colino = 0;
  reset_bs00b0_dat(p_actwk);
  SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &bs00b0_water_set_tbl);
  p_new_actwk->u.obj.userflag = 2;
}


static void bs00b0_away0(SKC_sprite_status* p_actwk) {
  bs00b0_move0_init(p_actwk);
}


static void bs00b0_move0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  if (p_actwk->u.obj.actflg0.unused7 == 0) {
    p_actwk->u.obj.actflg0.unused7 = 1;
    p_actwk->r_no = 14;
  }
  p_actwk->u.obj.callback_ptr = &bs00b0_wait1_init;
  CLEAR_BIT(p_actwk->sproffset, 15);
  p_actwk->patno = 0;
  set_bs00b0_posi(p_actwk);
}


static void bs00b0_move0(SKC_sprite_status* p_actwk) {
  if (g_ram.scralim_left + 2 <= g_ram.DAT_08fffa84) {
    g_ram.scralim_left += 2;
  }
  g_ram.scralim_right += 2;
  bs00b0_move1(p_actwk);
}


static void bs00b0_move1(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  dec_timer(p_actwk);
}


static void bs00b0_wait1_init(SKC_sprite_status* p_actwk) {
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  bs00b0_aper0_init(p_actwk);
}


static void bs00b0_die0(SKC_sprite_status* p_actwk) {
  bs00b0_die1_init(p_actwk);
}


static void bs00b0_die1_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &bs00b0_die1;
  g_ram.DAT_08fffaa3 = 0xFF;
  p_actwk->r_ptr = &dec_timer;
  p_actwk->u.obj.actflg0.ko_die = 1;
  set_act00(p_actwk, &bs00b0_break_set_tbl);
}


static void bs00b0_die1(SKC_sprite_status* p_actwk) {
  bs00b0_die2_init(p_actwk);
}


static void bs00b0_die2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &bs00b0_die2;
  set_opnbox(p_actwk);
}


static void set_opnbox(SKC_sprite_status* p_actwk) {
  g_ram.act_clear_flag = 0xFF;
  g_ram.bossstart = 0;
  divdevset2(&opnbox_cg_tbl);
  SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &opnbox_set_tbl);
  p_new_actwk->actflg.vflip = 1;
  set_friend_cg();
}


static void bs00b0_die2(SKC_sprite_status* p_actwk) {
  if (g_ram.act_clear_flag != 0) return;

  p_actwk->r_ptr = &bs00b0_die3;
  reset_pl_data();
  reset_pl_data0(&g_ram.actwk[1]);
  reset_bgm();
  g_ram.pl_input_lock_flag = 0xFF;;
  memset(&g_ram.swdata, 0, sizeof(g_ram.swdata));
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &fox_auto;
  }
  g_ram.scralim_m_right = g_ram.DAT_08fffa84 + 344;
  set_act05(p_actwk, &chglimr_set_tbl);
}


static void bs00b0_die3(SKC_sprite_status* p_actwk) {
  g_ram.miles_nograb_timer = 5;
  if (g_ram.DAT_08fffa84 + 504 > fp16_get_integer(g_ram.actwk[0].xposi)) {
    memset(&g_ram.swdata, 0, sizeof(g_ram.swdata));
    g_ram.swdata.pressed.r = 1;
    g_ram.swdata.down.r = 1;
  }
  else {
    pl_spd_clr(p_actwk);
    if (g_ram.actwk[0].u.play.character != KNUCKLES) {
      p_actwk->r_ptr = &bs00b0_die4;
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &nuckle;
        result.actwk_ptr->u.obj.userflag = 4;
      }
        divdevset2(&bakuhatu_cg_tbl);
    }
    else {
      p_actwk->r_ptr = &bs00b0_die6;
      memset(&g_ram.swdata, 0, sizeof(g_ram.swdata));
      g_ram.swdata.pressed.c = 1;
      g_ram.swdata.down.c = 1;
    }
  }
}


static void bs00b0_die4(SKC_sprite_status* p_actwk) {
  g_ram.miles_nograb_timer = 5;
  if (g_ram.pl_input_lock_flag != 0) {
    memset(&g_ram.swdata, 0, sizeof(g_ram.swdata));
    g_ram.swdata.pressed.u = 1;
    g_ram.swdata.down.u = 1;
    memset(&g_ram.swdata0, 0, sizeof(g_ram.swdata));
  }
  else {
    p_actwk->r_ptr = &bs00b0_die5;
  }
}


static void bs00b0_die5(SKC_sprite_status* p_actwk) {
  g_ram.miles_nograb_timer = 5;
  bs00b0_die50(p_actwk);
}


static void bs00b0_die50(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffa86 + 486 > fp16_get_integer(g_ram.actwk[0].yposi)) return;

  set_stageno(HYDROCITY_ACT_1);
  frameout(p_actwk);
}


static void bs00b0_die6(SKC_sprite_status* p_actwk) {
  memset(&g_ram.swdata, 0, sizeof(g_ram.swdata));
  g_ram.swdata.pressed.c = 1;
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  SET_BIT(p_playerwk->sproffset, 15);
  if (p_playerwk->yspeed >= 0) {
    p_actwk->r_ptr = &bs00b0_die7;
    p_playerwk->u.play.control_bitfield = 0x83;
    p_playerwk->patno = 203;
    wrt_player();
    g_ram.scralim_m_down = 0x1000;
    g_ram.scralim_n_down = 0x1000;
    set_act05(p_actwk, &chglimd_set_tbl);
  }
}


static void bs00b0_die7(SKC_sprite_status* p_actwk) {
  speedseta1(p_actwk, &g_ram.actwk[0]);
  bs00b0_die50(p_actwk);
}


static void bs00b0_arm(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[6] = {
    &bs00b0_arm_init,
    &bs00b0_arm_wait0,
    &bs00b0_arm_wait1,
    &bs00b0_arm_aper0,
    &bs00b0_arm_shot0,
    &bs00b0_arm_shot1
  };

  ko_offset1(p_actwk);
  chk_not_disp(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  if (p_actwk->u.obj.actflg0.flicker == 0) {
    chk_arm_die(p_actwk);
    actionsub(p_actwk);
  }
}


static void bs00b0_arm_init(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &bs00b0_arm_init_tbl);
  if (p_actwk->u.obj.userflag != 0) {
    p_actwk->patno = 42;
    p_actwk->sprpri = PRI_5;
  }
  set_act00(p_actwk, &bs00b0_fexit_set_tbl);
}


static void bs00b0_arm_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.fura_right == 1) {
    if (p_actwk->u.obj.userflag == 0) {
      p_actwk->r_no = 4;
      p_actwk->u.obj.timer = 4;
      p_actwk->u.obj.callback_ptr = &arm_aper0_init;
    }
    else {
      p_actwk->r_no = 8;
    }
  }
}


static void bs00b0_arm_wait1(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void arm_aper0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->u.obj.callback_ptr = &arm_wait2_init;
}


static void bs00b0_arm_aper0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.flicker = 0;
  time_pg0(p_actwk, bs00b0_arm_pg00);
}


static void arm_wait2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
}


static void bs00b0_arm_shot0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 1) {
    p_actwk->r_no = 10;
    p_actwk->u.obj.actflg0.unused1 = 1;
    p_actwk->direc.w = p_parentwk->direc.w;
  }
}


static void bs00b0_arm_shot1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 0) {
    p_actwk->r_no = 2;
    p_actwk->u.obj.actflg0.unused1 = 0;
  }
}


static void bs00b0_arm_die0(SKC_sprite_status* p_actwk) {
  arm_die1_init(p_actwk);
}


static void arm_die1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &chk_break_fout;
  p_actwk->patno = 1;
  p_actwk->colino = 0;
  set_break_spd(p_actwk, 12);
}


static void bs00b0_fexit(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[4] = {
    &bs00b0_fexit_init,
    &bs00b0_fexit_wait0,
    &bs00b0_fexit_wait1,
    &bs00b0_fexit_wait2
  };

  chk_not_disp(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  ko_offset1(p_actwk);
  if (p_actwk->u.obj.actflg0.flicker == 0) {
    chk_oya_die0(p_actwk);
  }
}


static void bs00b0_fexit_init(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &bs00b0_fexit_init_tbl);
}


static void bs00b0_fexit_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 1) {
    p_actwk->r_no = 4;
    p_actwk->patcnt = 1;
    p_actwk->u.obj.actflg0.unused1 = 1;
    p_actwk->u.obj.actfree.bs00b0_fexit.unknown3a = 1;
    p_actwk->u.obj.callback_ptr = &fexit_wait2_init;
    p_actwk->direc.w = p_parentwk->direc.w;
    p_actwk->u.obj.timer = p_parentwk->u.obj.userflag == 0 ? 0 : 79;
  }
}


static void bs00b0_fexit_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->u.obj.timer = 3;
  set_fexit_posi(p_actwk);
  if (p_actwk->patcnt-- == 0) {
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


static void fexit_wait2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  if (g_ram.actwk[0].u.play.character != KNUCKLES || p_actwk->u.obj.actfree.bs00b0_fexit.unknown3a-- == 0) {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_parentwk->u.obj.actflg0.unused1 = 0;
    p_actwk->u.obj.timer = 95;
    p_actwk->u.obj.callback_ptr = &fexit_wait1_init;
    set_flash(p_actwk);
  }
  else {
    p_actwk->u.obj.timer = 47;
    set_flash(p_actwk);
  }
}


static void fexit_wait0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->u.obj.actfree.bs00b0_fexit.tbl_index = 0;
}


static void bs00b0_fexit_wait2(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void fexit_wait1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->patcnt = 1;
  p_actwk->u.obj.actflg0.unused1 = 0;
  p_actwk->u.obj.timer = 0;
  p_actwk->u.obj.callback_ptr = &fexit_wait0_init;
}


static void bs00b0_flash(SKC_sprite_status* p_actwk) {
  signed char* pg_tbl[4] = {
    bs00b0_flash_pg00,
    bs00b0_flash_pg01,
    bs00b0_flash_pg01,
    bs00b0_flash_pg00
  };

  enemy_init2(p_actwk, &bs00b0_flash_init_tbl);
  p_actwk->r_ptr = &bs00b0_flash_wait0;
  p_actwk->u.obj.powerdat.fbaria_die = 1;
  p_actwk->u.obj.callback_ptr = &set_fire;
  SKC_sprite_status* p_parent0wk = &g_ram.actwk[p_actwk->u.obj.oya];
  SKC_sprite_status* p_parent1wk = &g_ram.actwk[p_parent0wk->u.obj.oya];
  SKC_sprite_status* p_parent2wk = &g_ram.actwk[p_parent1wk->u.obj.oya];
  p_actwk->u.obj.ko = p_parent2wk - g_ram.actwk;
  p_actwk->direc.w = p_parent0wk->direc.w;
  p_actwk->u.obj.pg_data_ptr = pg_tbl[p_parent0wk->direc.w / 4];
  if (p_parent0wk->direc.w < 8) {
    p_actwk->actflg.hflip = 1;
  }
}


static void bs00b0_flash_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_childwk->u.obj.cddat.die == 1) {
    flash_die(p_actwk);
  }
  else {
    ko_offset0(p_actwk);
    pt_chg(p_actwk);
    chk_actsubc(p_actwk);
  }
}


static void set_fire(SKC_sprite_status* p_actwk) {
  set_act00(p_actwk, &bs00b0_fire_set_tbl);
}


static void flash_die(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.flicker = 1;
  set_emy_fout0(p_actwk);
}


static void bs00b0_fire(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &bs00b0_fire_init_tbl);
  p_actwk->u.obj.powerdat.fbaria_die = 1;
  soundset(77);
  p_actwk->sprvsize = 12;
  p_actwk->u.obj.timer = 159;
  p_actwk->r_ptr = &bs00b0_fire_move0;
  p_actwk->u.obj.callback_ptr = &fire_move1_init;
  set_fire_init(p_actwk);
}


static void bs00b0_fire_move0(SKC_sprite_status* p_actwk) {
  if (p_actwk->xspeed != 0) {
    emy_fall_col(p_actwk);
  }
  bs00b0_fire_move1(p_actwk);
}


static void bs00b0_fire_move1(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset2(p_actwk);
  if (p_actwk->u.obj.timer-- == 0) {
    if (!(g_ram.systemtimer & 3)) {
      set_act00(p_actwk, &bs00b0_kakera_set_tbl);
    }
    chk_actsubc(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void fire_move1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &bs00b0_fire_move1;
  p_actwk->u.obj.pg_data_ptr = bs00b0_fire_pg01;
  p_actwk->yspeed = 0;
}


static void bs00b0_kakera(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &bs00b0_kakera_init_tbl);
  p_actwk->r_ptr = &bs00b0_kakera_wait0;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  p_actwk->u.obj.pg_data_ptr = p_actwk->xspeed != 0 ? bs00b0_kakera_pg00 : bs00b0_kakera_pg01;
}


static void bs00b0_kakera_wait0(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  actionsub(p_actwk);
}


static void embl_water(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &embl_water_init_tbl);
  p_actwk->r_ptr = &embl_water_wait0;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
}


static void embl_water_wait0(SKC_sprite_status* p_actwk) {
  time_pg0(p_actwk, embl_water_pg00);
  actionsub(p_actwk);
}


static void bs00b0_water(SKC_sprite_status* p_actwk) {
  enemy_init1(p_actwk, &bs00b0_water_init_tbl);
  p_actwk->r_ptr = &bs00b0_water_wait0;
  if (p_actwk->u.obj.userflag == 0) {
    p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  }
  else {
    p_actwk->u.obj.callback_ptr = &water_fall0_init;
  }
}


static void bs00b0_water_wait0(SKC_sprite_status* p_actwk) {
  time_pgr0(p_actwk, bs00b0_water_pg00);
  if (p_actwk->patno != 43) {
    actionsub(p_actwk);
  }
}


static void water_fall0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &bs00b0_water_fall0;
  p_actwk->yspeed = 0x800;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
}


static void bs00b0_water_fall0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  time_pgr0(p_actwk, bs00b0_water_pg01);
  if (p_actwk->patno != 43) {
    actionsub(p_actwk);
  }
}


static void bs00b0_break(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &bs00b0_break_init_tbl);
  p_actwk->r_ptr = &chk_break_fout;
  p_actwk->patno = (p_actwk->u.obj.userflag >> 1) + 50;
  set_break_spd(p_actwk, 0);
  actionsub(p_actwk);
}


static void set_bs00b0_posi(SKC_sprite_status* p_actwk) {
  set_bs00b0_posi0(p_actwk, random() & 0x0C);
}


static void set_bs00b0_posi0(SKC_sprite_status* p_actwk, unsigned short direction) {
  SKC_point posi_tbl[4] = {
    {  88, 118 },
    { 160,  70 },
    { 352,  70 },
    { 424, 118 }
  };

  unsigned short prev_direc = p_actwk->direc.w;
  p_actwk->direc.w = direction;
  if (p_actwk->direc.w == prev_direc) {
    set_bs00b0_posi(p_actwk);
  }
  else {
    p_actwk->xspeed = (g_ram.DAT_08fffa84 + posi_tbl[p_actwk->direc.w / 4].x - fp16_get_integer(p_actwk->xposi)) * 2;
    p_actwk->yspeed = (g_ram.DAT_08fffa86 + posi_tbl[p_actwk->direc.w / 4].y - fp16_get_integer(p_actwk->yposi)) * 2;
    if (p_actwk->xspeed != 0) {
      p_actwk->actflg.hflip = p_actwk->xspeed > 0;
    }
  }
}


static void set_fexit_posi(SKC_sprite_status* p_actwk) {
  struct {
    signed char x;
    signed char y;
    unsigned char patno;
    unsigned char unused;
  }
  ofs_tbl[8] = {
    { -24,  8, 5, 0 },
    { -24,  8, 5, 0 },
    { -28,  0, 4, 0 },
    { -28,  0, 4, 0 },
    { -24,  8, 5, 0 },
    { -16, 16, 6, 0 },
    { -24,  8, 5, 0 },
    { -28,  0, 4, 0 }
  };

  unsigned short index = 0;
  if (!(p_actwk->direc.w ^ 0x0C) && (p_actwk->direc.w ^ 0x0C) != 0x0C) {
    index += 16;
  }
  index += p_actwk->u.obj.actfree.bs00b0_fexit.tbl_index;
  p_actwk->u.obj.oya_offset.x = ofs_tbl[index / 4].x;
  p_actwk->u.obj.oya_offset.y = ofs_tbl[index / 4].y;
  p_actwk->patno = ofs_tbl[index / 4].patno;
  p_actwk->u.obj.actfree.bs00b0_fexit.tbl_index += 4;
}


void chk_not_disp(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.flicker == 0) {
    p_actwk->u.obj.actflg0.flicker = 0;
    SET_BIT(p_actwk->sproffset, 15);
    if (!BIT_IS_SET(p_parentwk->sproffset, 15)) {
      CLEAR_BIT(p_actwk->sproffset, 15);
    }
  }
  else {
    p_actwk->u.obj.actflg0.flicker = 1;
  }
}


static void set_flash(SKC_sprite_status* p_actwk) {
  SKC_set_act00_data* set_tbl[4] = {
    &bs00b0_flash_set_tbl00,
    &bs00b0_flash_set_tbl04,
    &bs00b0_flash_set_tbl04,
    &bs00b0_flash_set_tbl0c
  };

  set_act00(p_actwk, set_tbl[p_actwk->direc.w / 4]);
}


static void set_fire_init(SKC_sprite_status* p_actwk) {
  signed char* pg_tbl[4] = {
    bs00b0_fire_pg00,
    bs00b0_fire_pg04,
    bs00b0_fire_pg04,
    bs00b0_fire_pg00
  };
  SKC_point ofs_tbl[4] = {
    {  20, 20 },
    {   0, 24 },
    {   0, 24 },
    { -20, 20 }
  };
  SKC_speed spd_tbl[4] = {
    {  0x0300, 0x300 },
    {       0, 0x400 },
    {       0, 0x400 },
    { -0x0300, 0x300 }
  };

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->direc.w < 8) {
    p_actwk->actflg.hflip = 1;
  }
  p_actwk->u.obj.pg_data_ptr = pg_tbl[p_parentwk->direc.w / 4];
  short xposi = fp16_get_integer(p_actwk->xposi) + ofs_tbl[p_parentwk->direc.w / 4].x;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_actwk->yposi) + ofs_tbl[p_parentwk->direc.w / 4].y;
  fp16_set_integer(&p_actwk->yposi, yposi);
  p_actwk->xspeed = spd_tbl[p_parentwk->direc.w / 4].xspeed;
  p_actwk->yspeed = spd_tbl[p_parentwk->direc.w / 4].yspeed;
}


static void chk_bs00b0_damage(SKC_sprite_status* p_actwk) {
  if (p_actwk->colino != 0) return;

  if (p_actwk->colicnt != 0) {
    if (p_actwk->mstno == 0) {
      p_actwk->mstno = 32;
      soundset(110);
    }
    p_actwk->u.obj.cddat.pl2push = 1;
    unsigned short index = 0;
    if (!BIT_IS_SET(p_actwk->mstno, 0)) {
      index += 14;
    }
    chg_bs00b0_cor(index);
    --p_actwk->mstno;
    if (p_actwk->mstno == 0) {
      p_actwk->u.obj.cddat.pl2push = 0;
      if (p_actwk->patno == 0) {
        p_actwk->colino = p_actwk->pattimm;
      }
    }
  }
  else {
    p_actwk->r_ptr = &bos_tim_act;
    p_actwk->u.obj.actflg0.flicker = 0;
    SET_BIT(p_actwk->sproffset, 15);
    p_actwk->patno = 0;
    p_actwk->u.obj.callback_ptr = &bs00b0_die0;
    boss_die_init(p_actwk);
  }
}


static void chg_bs00b0_cor(unsigned short index) {
  unsigned char adr_tbl[7] = {
    20, 23, 25, 26, 27, 29, 30
  };
  unsigned short color_tbl[14] = {
    0x222, 0x008, 0x04C, 0x006, 0x020, 0xA24, 0x622, 0xAAA, 0xAAA, 0xAAA, 0xCCC, 0xEEE, 0x666, 0x888
  };

  set_damg_cor07(adr_tbl, &color_tbl[index / 2]);
}


static void reset_bs00b0_dat(SKC_sprite_status* p_actwk) {
  chg_bs00b0_cor(0);
  p_actwk->u.obj.actflg0.flicker = 0;
  p_actwk->mstno = 0;
}


static void chk_arm_die(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    p_actwk->r_ptr = &tim_act;
    p_actwk->u.obj.cddat.die = 1;
    p_actwk->patno = 1;
    p_actwk->u.obj.timer = 31;
    p_actwk->u.obj.callback_ptr = &bs00b0_arm_die0;
  }
}


static SKC_enemy_init0_data bs00b0_init_tbl = {
  bs00b0_pt,
  0xA180,
  PRI_5,
  40,
  32,
  0,
  0x10
};


static SKC_enemy_init2_data bs00b0_arm_init_tbl = {
  PRI_4,
  36,
  20,
  1,
  0
};


static SKC_enemy_init2_data bs00b0_fexit_init_tbl = {
  PRI_3,
  12,
  12,
  4,
  0
};


static SKC_enemy_init2_data bs00b0_flash_init_tbl = {
  PRI_2,
  8,
  4,
  11,
  0x97
};


static SKC_enemy_init2_data bs00b0_fire_init_tbl = {
  PRI_2,
  20,
  24,
  15,
  0x9A
};


static SKC_enemy_init2_data bs00b0_kakera_init_tbl = {
  PRI_2,
  8,
  8,
  24,
  0
};


static SKC_enemy_init1_data bs00b0_water_init_tbl = {
  0x8180,
  PRI_2,
  48,
  48,
  36,
  0
};


static SKC_enemy_init0_data embl_water_init_tbl = {
  bs00b0_pt,
  0x8180,
  PRI_2,
  24,
  16,
  33,
  0
};


static SKC_enemy_init2_data bs00b0_break_init_tbl = {
  PRI_3,
  16,
  16,
  0,
  0
};


static SKC_set_act00_data bs00b0_set_tbl = {
  1,
  {
    { &bs00b0_arm,  20, -4 },
    { &bs00b0_arm, -20, -4 }
  }
};


static SKC_set_act00_data bs00b0_fexit_set_tbl = {
  0,
  {
    { &bs00b0_fexit, -28, 0 }
  }
};


static SKC_set_act00_data bs00b0_water_set_tbl = {
  0,
  {
    { &bs00b0_water, 0, 0 }
  }
};


static SKC_set_act00_data embl_water_set_tbl = {
  0,
  {
    { &embl_water, 0, -48 }
  }
};


static SKC_set_act00_data bs00b0_flash_set_tbl00 = {
  0,
  {
    { &bs00b0_flash, 3, 5 }
  }
};


static SKC_set_act00_data bs00b0_flash_set_tbl04 = {
  0,
  {
    { &bs00b0_flash, 0, 7 }
  }
};


static SKC_set_act00_data bs00b0_flash_set_tbl0c = {
  0,
  {
    { &bs00b0_flash, -3, 5 }
  }
};


static SKC_set_act00_data bs00b0_fire_set_tbl = {
  0,
  {
    { &bs00b0_fire, 0, 0 }
  }
};


static SKC_set_act00_data bs00b0_kakera_set_tbl = {
  0,
  {
    { &bs00b0_kakera, 0, 0 }
  }
};


static SKC_set_act00_data bs00b0_break_set_tbl = {
  5,
  {
    { &bs00b0_break, -16, -16 },
    { &bs00b0_break,  16, -16 },
    { &bs00b0_break, -16,   8 },
    { &bs00b0_break,  16,   8 },
    { &bs00b0_break, -12,  24 },
    { &bs00b0_break,  12,  24 }
  }
};


static SKC_set_act05_data opnbox_set_tbl = {
  0,
  &opnbox
};


static SKC_set_act05_data nuckle_set_tbl = {
  0,
  &nuckle
};


static signed char bs00b0_pg00[27] = {
   43,   0,  43,   0,  43,   0,   0,   0,  43,   0,
   43,   0,   0,   0,  43,   0,  43,   0,   0,   0,
   43,   0,  43,   0,   0,   0, -12
};
static signed char bs00b0_pg01[11] = { 27, 0, 27, 4, 28, 5, 29, 6, 0, 0, -12 };


static signed char bs00b0_arm_pg00[11] = { 30, 0, 30, 4, 31, 5, 32, 6, 1, 0, -12 };


static signed char bs00b0_flash_pg00[42] = {
    0,   7,  43,   7,  43,   8,  43,   8,  43,   9,
   43,   9,  43,  10,  43,  10,  43,  10,  43,  10,
   43,  10,  43,  10,  43,  10,  43,  10,  43,  10,
   43,  10,  43,  10,  43,  10,  43,  10,  43,  10,
   43, -12
};
static signed char bs00b0_flash_pg01[42] = {
    0,  11,  43,  11,  43,  12,  43,  12,  43,  13,
   43,  13,  43,  14,  43,  14,  43,  14,  43,  14,
   43,  14,  43,  14,  43,  14,  43,  14,  43,  14,
   43,  14,  43,  14,  43,  14,  43,  14,  43,  14,
   43, -12
};


static signed char bs00b0_fire_pg00[6] = { 1, 38, 39, 40, 41, -4 };
static signed char bs00b0_fire_pg04[6] = { 1, 22, 23, 47, 48, -4 };
static signed char bs00b0_fire_pg01[6] = { 1, 16, 17, 45, 46, -4 };


static signed char bs00b0_kakera_pg00[9] = { 18, 0, 18, 9, 19, 2, 20, 2, -12 };
static signed char bs00b0_kakera_pg01[9] = { 24, 0, 24, 9, 25, 2, 26, 2, -12 };


static signed char embl_water_pg00[9] = { 33, 0, 33, 4, 34, 5, 35, 6, -12 };


static signed char bs00b0_water_pg00[27] = {
   43,   0,  36,   0, 100,   0, 107,   0,  44,   0,
  108,   0, 107,   0,  36,   0, 100,   0, 107,   0,
   44,   0, 108,   0, 107,   0, -12
};
static signed char bs00b0_water_pg01[27] = {
   43,   0,  36,   0, 100,   0, 107,   0,  44,   0,
  108,   0, 107,   0,  49,   0, 113,   0, 107,   0,
   49,   0, 113,   0, 107,   0, -12
};


static unsigned short boss00b0color[16] = {
  0x000, 0xEEE, 0xCAA, 0xE26, 0x222, 0x0EE, 0x088, 0x008, 0x2AE, 0x04C, 0x006, 0x020, 0xC68, 0xA24, 0x622, 0x044
};
