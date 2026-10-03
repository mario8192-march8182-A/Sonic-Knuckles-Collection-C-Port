#include "bs00m.h"
#include <string.h>
#include "../../data/pat/zone00/bs00m.h"
#include "../../data/pat/zone00/kaen00m0.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritestatus.h"
#include "../../utils/fp16.h"
#include "../../utils/stageno.h"
#include "../../action.h"
#include "../../coli.h"
#include "../../dev.h"
#include "../../reloader.h"
#include "../../shared.h"
#include "../../sound.h"
#include "../explosion.h"
static void bs00m0_body_init(SKC_sprite_status* p_actwk);
static void bs00m0_body_wait0(SKC_sprite_status* p_actwk);
static void body_wait00(SKC_sprite_status* p_actwk);
static void dummy(SKC_sprite_status* p_actwk);
static void bs00m0_dec_timer(SKC_sprite_status* p_actwk);
static void body_down_init0(SKC_sprite_status* p_actwk);
static void body_down_init00(SKC_sprite_status* p_actwk);
static void bs00m0_timer_speed(SKC_sprite_status* p_actwk);
static void body_wait1_init0(SKC_sprite_status* p_actwk);
static void body_wait1_init00(SKC_sprite_status* p_actwk);
static void bs00m0_body_wait1(SKC_sprite_status* p_actwk);
static void body_set_kaen0(SKC_sprite_status* p_actwk);
static void set_bsexp_init(SKC_sprite_status* p_actwk);
static void body_rway_init0(SKC_sprite_status* p_actwk);
static void bs00m0_die0(SKC_sprite_status* p_actwk);
static void bs00m0_jet_pchg(SKC_sprite_status* p_actwk);
static void bs00m0_exit_wait(SKC_sprite_status* p_actwk);
static void bs00m0_futa_init(SKC_sprite_status* p_actwk);
static void bs00m0_futa_wait0(SKC_sprite_status* p_actwk);
static void bs00m0_futa_wait1(SKC_sprite_status* p_actwk);
static void futa_open_init0(SKC_sprite_status* p_actwk);
static void futa_open_init00(SKC_sprite_status* p_actwk);
static void bs00m0_time_pg(SKC_sprite_status* p_actwk);
static void futa_shot_init0(SKC_sprite_status* p_actwk);
static void futa_shot_init0__dec(SKC_sprite_status* p_actwk);
static void bs00m0_futa_shot(SKC_sprite_status* p_actwk);
static void futa_wait2_init0(SKC_sprite_status* p_actwk);
static void bs00m0_napf_init(SKC_sprite_status* p_actwk);
static void bs00m0_napm_init(SKC_sprite_status* p_actwk);
static void bs00m0_napm_up(SKC_sprite_status* p_actwk);
static void napm0_wait_init(SKC_sprite_status* p_actwk);
static void napm0_down_init(SKC_sprite_status* p_actwk);
static void bs00m0_napm_down(SKC_sprite_status* p_actwk);
static void bs00m0_kaen0_init(SKC_sprite_status* p_actwk);
static void set_timer(SKC_sprite_status* p_actwk, unsigned short seconds);
static void bs00m0_kaen0_wait(SKC_sprite_status* p_actwk);
static void kaen_move_init0(SKC_sprite_status* p_actwk);
static void bs00m0_kaen0_move(SKC_sprite_status* p_actwk);
static void kaen_pg_init(SKC_sprite_status* p_actwk);
static void bs00m0_kaen1_init(SKC_sprite_status* p_actwk);
static void bs00m0_kaen1_move(SKC_sprite_status* p_actwk);
static void bs00m1_body_init(SKC_sprite_status* p_actwk);
static void bs00m1_body_wait0(SKC_sprite_status* p_actwk);
static void body_down_init1(SKC_sprite_status* p_actwk);
static void bs00m1_body_moveud(SKC_sprite_status* p_actwk);
static void body_wait1_init1(SKC_sprite_status* p_actwk);
static void bs00m1_body_wait1(SKC_sprite_status* p_actwk);
static void body_set_napm(SKC_sprite_status* p_actwk);
static void body_set_kaen1(SKC_sprite_status* p_actwk);
static void bs00m1_body_wait2(SKC_sprite_status* p_actwk);
static void body_moveud_init(SKC_sprite_status* p_actwk);
static void bs00m1_body_wait3(SKC_sprite_status* p_actwk);
static void body_wait2_init1(SKC_sprite_status* p_actwk);
static void body_wait2_init10(SKC_sprite_status* p_actwk);
static void body_movelr_init(SKC_sprite_status* p_actwk);
static void bs00m1_body_movelr(SKC_sprite_status* p_actwk);
static void body_chg_init(SKC_sprite_status* p_actwk);
static void body_wait3_init(SKC_sprite_status* p_actwk);
static void bs00m1_die0(SKC_sprite_status* p_actwk);
static void bs00m0_die1_init(SKC_sprite_status* p_actwk);
static void bs00m1_futa_wait0(SKC_sprite_status* p_actwk);
static void futa_open_init1(SKC_sprite_status* p_actwk);
static void futa_close_init1(SKC_sprite_status* p_actwk);
static void futa_wait2_init1(SKC_sprite_status* p_actwk);
static void bs00m1_napm_init(SKC_sprite_status* p_actwk);
static void bs00m1_napm_up(SKC_sprite_status* p_actwk);
static void napm_wait0_init(SKC_sprite_status* p_actwk);
static void napm_wait1_init(SKC_sprite_status* p_actwk);
static void bs00m1_napm_wait1(SKC_sprite_status* p_actwk);
static void napm_down_init(SKC_sprite_status* p_actwk);
static void bs00m1_napm_down(SKC_sprite_status* p_actwk);
static void set_napmexp_init(SKC_sprite_status* p_actwk);
static void bs00m0_napmexp_init(SKC_sprite_status* p_actwk);
static void bs00m0_napmexp_wait0(SKC_sprite_status* p_actwk);
static void napmexp_pchg_init(SKC_sprite_status* p_actwk);
static void bs00m0_napmexp_pchg(SKC_sprite_status* p_actwk);
static void bs00m2_wait(SKC_sprite_status* p_actwk);
static void move_init(SKC_sprite_status* p_actwk);
static void bs00m2_move(SKC_sprite_status* p_actwk);
static void bs00m0_break(SKC_sprite_status* p_actwk);
static void set_futa_ini_time(SKC_sprite_status* p_actwk);
static void set_napm_fall(SKC_sprite_status* p_actwk);
static void set_napm_fall0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_parentwk);
static void chk_bs00m0_damage(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data bs00m0_init_tbl;
static SKC_enemy_init1_data jet00m0_init_tbl;
static SKC_enemy_init1_data exit00m0_init_tbl;
static SKC_enemy_init1_data futa00m0_init_tbl;
static SKC_enemy_init1_data napf00m0_init_tbl;
static SKC_enemy_init1_data napm00m0_init_tbl;
static SKC_enemy_init0_data napmexp_init_tbl;
static SKC_enemy_init0_data kaen00m0_init_tbl;
static SKC_enemy_init0_data bs00m2_init_tbl;
static SKC_enemy_init2_data bs00m0_break_init_tbl;
static SKC_set_act00_data jet00m0_set_tbl;
static SKC_set_act02_data bs00m2_set_tbl;
static SKC_set_act00_data futa00m0_set_tbl;
static SKC_set_act00_data futa00m1_set_tbl;
static SKC_set_act00_data napm00m0_set_tbl;
static SKC_set_act00_data napm00m1_set_tbl;
static SKC_set_act00_data kaen00m0_set_tbl0;
static SKC_set_act00_data kaen00m0_set_tbl1;
static SKC_set_act00_data screxp01_set_tbl;
static SKC_set_act00_data bs00m0_break_set_tbl;
static signed char jet00m0_pg00[4];
static signed char futa00m0_pg00[5];
static signed char futa00m0_pg01[7];
static signed char futa00m0_pg02[9];
static signed char napm00m0_pg00[13];
static signed char napm00m0_pg01[4];
static signed char napmexp_pg00[15];
static signed char kaen00m0_pg00[5];
static signed char kaen00m0_pg01[11];
static signed char kaen00m0_pg02[13];
static unsigned short boss00m0color[16];

extern sonic3_ram g_ram;


void bs00m0_body(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &bs00m0_body_init,
    &bs00m0_body_wait0,
    &bs00m0_dec_timer,
    &bs00m0_timer_speed,
    &bs00m0_body_wait1
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_bs00m0_damage(p_actwk);
}


static void bs00m0_body_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &bs00m0_init_tbl);
  p_actwk->colicnt = 96;
  g_ram.scralim_m_right = g_ram.scralim_right;
  g_ram.bossstart = 1;
  divdevset(90);
}


static void bs00m0_body_wait0(SKC_sprite_status* p_actwk) {
  if (g_ram.scra_h_posit >= 0x2F10) {
    p_actwk->u.obj.callback_ptr = &body_down_init0;
    set_act02(p_actwk, &bs00m2_set_tbl);
    set_emy_cor(&boss00m0color);
    body_wait00(p_actwk);
  }
}


static void body_wait00(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.timer = 180;
  g_ram.scralim_left = 0x2F10;
  g_ram.scralim_right = 0x2F10;
  bgmset(-31);
}


static void dummy(SKC_sprite_status* p_actwk) {
}


static void bs00m0_dec_timer(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void body_down_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &body_wait1_init0;
  p_actwk->r_no = 6;
  set_act00(p_actwk, &jet00m0_set_tbl);
  set_act00(p_actwk, &futa00m0_set_tbl);
  body_down_init00(p_actwk);
}


static void body_down_init00(SKC_sprite_status* p_actwk) {
  p_actwk->yspeed = 0x100;
  p_actwk->u.obj.timer = 175;
  bgmset(24);
  g_ram.bgm_act = 24;
}


static void bs00m0_timer_speed(SKC_sprite_status* p_actwk) {
  spd2_tim_actc(p_actwk);
}


static void body_wait1_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 127;
  p_actwk->u.obj.callback_ptr = &set_bsexp_init;
  p_actwk->u.obj.puka.cnt = 3;
  p_actwk->u.obj.actflg0.unused1 = 1;
  body_wait1_init00(p_actwk);
}


static void body_wait1_init00(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->yspeed = 0;
  bs00m0_puka_init(p_actwk);
}


void bs00m0_puka_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.accel_max = 0xC0;
  p_actwk->yspeed = 0xC0;
  p_actwk->u.obj.puka.accel = 0x10;
  p_actwk->u.obj.actflg0.puka_down = 0;
}


static void bs00m0_body_wait1(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  spd2_tim_actc(p_actwk);
}


static void body_set_kaen0(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.puka.cnt;
  if (p_actwk->u.obj.puka.cnt < 0) {
    p_actwk->u.obj.callback_ptr = &set_bsexp_init;
  }
  p_actwk->u.obj.timer = 64;
  soundset(79);
  set_act00(p_actwk, &kaen00m0_set_tbl0);
}


static void set_bsexp_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 16;
  p_actwk->u.obj.callback_ptr = &body_rway_init0;
  set_act00(p_actwk, &screxp01_set_tbl);
}


static void body_rway_init0(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &bs00m0_die0;
  set_emy_cor(&boss00m0color);
  p_actwk->colino = 15;
  bgmset(-31);
  p_actwk->xspeed = 0x400;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.timer = g_ram.stageno != ANGEL_ISLAND_ACT_1 ? 64 : 288;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  g_ram.DAT_08ffeec6 = 0xFF;
}


static void bs00m0_die0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  if (p_actwk->u.obj.timer-- > 0) {
    actionsub(p_actwk);
  }
  else {
    g_ram.bossstart = 0;
    reset_bgm();
    divdevset2(&item_cg_tbl);
    set_emy_fout1(p_actwk);
  }
}


void bs00m0_jet(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  enemy_init1(p_actwk, &jet00m0_init_tbl);
  p_actwk->u.obj.powerdat.fbaria_die = 1;
  p_actwk->u.obj.pg_data_ptr = jet00m0_pg00;
  p_actwk->r_ptr = &bs00m0_jet_pchg;
  chk_oya_diec1(p_actwk);
}


static void bs00m0_jet_pchg(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  pt_chg(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    p_actwk->colino = 0;
  }
  chk_oya_diec1(p_actwk);
}


void bs00m0_exit(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  p_actwk->r_ptr = &bs00m0_exit_wait;
  enemy_init1(p_actwk, &exit00m0_init_tbl);
}


static void bs00m0_exit_wait(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  chk_oya_die1(p_actwk);
}


void bs00m0_futa(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[7] = {
    &bs00m0_futa_init,
    &bs00m0_futa_wait0,
    &bs00m0_futa_wait1,
    &bs00m0_time_pg,
    &bs00m0_futa_shot,
    &bs00m0_time_pg,
    &dummy
  };

  ko_offset1(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die1(p_actwk);
}


static void bs00m0_futa_init(SKC_sprite_status* p_actwk) {
  enemy_init1(p_actwk, &futa00m0_init_tbl);
}


static void bs00m0_futa_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_actwk->u.obj.actflg0.unused1 == 1) {
    p_actwk->r_no = 4;
    p_actwk->u.obj.callback_ptr = &futa_open_init0;
    set_futa_ini_time(p_actwk);
  }
}


static void bs00m0_futa_wait1(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void futa_open_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &futa_shot_init0;
  futa_open_init00(p_actwk);
}


static void futa_open_init00(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->u.obj.pg_data_ptr = futa00m0_pg01;
}


static void bs00m0_time_pg(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
}


static void futa_shot_init0(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->u.obj.puka.cnt = 3;
  p_actwk->u.obj.callback_ptr = &futa_shot_init0__dec;
  futa_shot_init0__dec(p_actwk);
}


static void futa_shot_init0__dec(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 28;
  --p_actwk->u.obj.puka.cnt;
  if (p_actwk->u.obj.puka.cnt != 1) {
    set_act00(p_actwk, &napm00m0_set_tbl);
  }
  set_act00(p_actwk, &napm00m1_set_tbl);
}


static void bs00m0_futa_shot(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
  if (p_actwk->u.obj.puka.cnt < 0) {
    p_actwk->r_no = 10;
    p_actwk->u.obj.pg_data_ptr = futa00m0_pg02;
    p_actwk->u.obj.callback_ptr = &futa_wait2_init0;
  }
}


static void futa_wait2_init0(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
}


void bs00m0_napfire(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[2] = {
    &bs00m0_napf_init,
    &bs00m0_time_pg
  };

  ko_offset1(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  actionsub(p_actwk);
}


static void bs00m0_napf_init(SKC_sprite_status* p_actwk) {
  enemy_init1(p_actwk, &napf00m0_init_tbl);
  p_actwk->u.obj.pg_data_ptr = napm00m0_pg00;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
}


void bs00m0_napalm(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[4] = {
    &bs00m0_napm_init,
    &bs00m0_napm_up,
    &bs00m0_dec_timer,
    &bs00m0_napm_up
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void bs00m0_napm_init(SKC_sprite_status* p_actwk) {
  enemy_init1(p_actwk, &napm00m0_init_tbl);
  soundset(77);
  p_actwk->u.obj.pg_data_ptr = napm00m0_pg01;
  p_actwk->u.obj.callback_ptr = &napm0_wait_init;
  p_actwk->yspeed = -0x400;
  p_actwk->u.obj.timer = 96;
  actionsub(p_actwk);
}


static void bs00m0_napm_up(SKC_sprite_status* p_actwk) {
  spd2_pt_tim(p_actwk);
  actionsub(p_actwk);
}


static void napm0_wait_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.timer = 8;
  p_actwk->u.obj.callback_ptr = &napm0_down_init;
}


static void napm0_down_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  soundset(81);
  p_actwk->sprpri = PRI_1;
  p_actwk->actflg.vflip = 1;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  p_actwk->u.obj.timer = 96;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  set_napm_fall0(p_actwk, p_parentwk);
  short yposi = (g_ram.scra_v_posit >> 16) - 32;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void bs00m0_kaen0(SKC_sprite_status* p_actwk) {
  bs00m0_napm_down(p_actwk);
}


static void bs00m0_napm_down(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &bs00m0_kaen0_init,
    &bs00m0_dec_timer,
    &bs00m0_kaen0_move
  };

  ko_offset1(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void bs00m0_kaen0_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &kaen00m0_init_tbl);
  p_actwk->u.obj.powerdat.fbaria_die = 1;
  p_actwk->u.obj.callback_ptr = &kaen_move_init0;
  set_timer(p_actwk, 6);
}


static void set_timer(SKC_sprite_status* p_actwk, unsigned short seconds) {
  p_actwk->u.obj.timer = (seconds - p_actwk->u.obj.userflag) * 2;
}


static void bs00m0_kaen0_wait(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void kaen_move_init0(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.pg_data_ptr = kaen00m0_pg00;
  p_actwk->u.obj.callback_ptr = &kaen_pg_init;
}


static void bs00m0_kaen0_move(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  chk_actsubc(p_actwk);
}


static void kaen_pg_init(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = exp01_pt;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x4D2;
  p_actwk->sproffset.pr = 1;
  p_actwk->u.obj.pg_data_ptr = kaen00m0_pg01;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  if (p_actwk->u.obj.userflag == 6) {
    set_act00(p_actwk, &kaen00m0_set_tbl1);
  }
}


void bs00m0_kaen1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[2] = {
    &bs00m0_kaen1_init,
    &bs00m0_kaen1_move
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_actsubc(p_actwk);
}


static void bs00m0_kaen1_init(SKC_sprite_status* p_actwk) {
  bs00m0_kaen0_init(p_actwk);
  p_actwk->sprpri = PRI_2;
  p_actwk->u.obj.pg_data_ptr = kaen00m0_pg02;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_parentwk = &g_ram.actwk[p_parentwk->u.obj.oya];
  p_actwk->u.obj.oya = p_parentwk - g_ram.actwk;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_parentwk->yposi));
  short xoffset = 96;
  if (p_parentwk->actflg.hflip == 1) {
    xoffset = -xoffset;
    p_actwk->actflg.hflip = 1;
  }
  short xposi = fp16_get_integer(p_parentwk->xposi) + xoffset;
  fp16_set_integer(&p_actwk->xposi, xposi);
}


static void bs00m0_kaen1_move(SKC_sprite_status* p_actwk) {
  short offset_tbl[6] = {
    0, 0, 0, 16, 8, 8
  };

  int ret = time_pg(p_actwk);
  if (ret > 0) {
    short xoffset = offset_tbl[p_actwk->patcnt];
    if (p_actwk->actflg.hflip == 0) {
      xoffset = -xoffset;
    }
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
  }
}


void bs00m1_body(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[8] = {
    &bs00m1_body_init,
    &bs00m1_body_wait0,
    &bs00m0_dec_timer,
    &bs00m1_body_moveud,
    &bs00m0_body_wait1,
    &bs00m1_body_wait2,
    &bs00m1_body_wait3,
    &bs00m1_body_movelr
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_bs00m0_damage(p_actwk);
}


static void bs00m1_body_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &bs00m0_init_tbl);
  p_actwk->colicnt = 6;
  g_ram.bossstart = 1;
  divdevset(90);
  set_emy_cor(&boss00m0color);
}


static void bs00m1_body_wait0(SKC_sprite_status* p_actwk) {
  short xposi = g_ram.actwk[0].u.play.character != KNUCKLES ? 0x10E0 : 0x10C0;
  if (g_ram.scra_h_posit >> 16 >= xposi) {
    p_actwk->u.obj.callback_ptr = &body_down_init1;
    body_wait00(p_actwk);
  }
}


static void body_down_init1(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &body_wait1_init1;
  p_actwk->r_no = 6;
  body_down_init00(p_actwk);
  set_act00(p_actwk, &jet00m0_set_tbl);
  set_act00(p_actwk, &futa00m1_set_tbl);
}


static void bs00m1_body_moveud(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  dec_timer(p_actwk);
  chk_actsubc(p_actwk);
}


static void body_wait1_init1(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &bs00m1_body_wait1;
  p_actwk->u.obj.timer = 20;
  body_wait1_init00(p_actwk);
}


static void bs00m1_body_wait1(SKC_sprite_status* p_actwk) {
  body_set_napm(p_actwk);

}


static void body_set_napm(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &body_set_kaen1;
  p_actwk->u.obj.timer = 18;
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    p_actwk->u.obj.actflg0.unused1 = 1;
  }
}


static void body_set_kaen1(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 10;
  p_actwk->u.obj.puka.cnt = 8;
  soundset(79);
  set_act00(p_actwk, &kaen00m0_set_tbl0);
}


static void bs00m1_body_wait2(SKC_sprite_status* p_actwk) {
  if (puka_count(p_actwk) && p_actwk->yspeed < 0) {
    speedset2(p_actwk);
    chk_actsubc(p_actwk);
  }
}


static void body_moveud_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->u.obj.timer = 95;
  p_actwk->u.obj.callback_ptr = &body_wait2_init1;
  short yspeed = -0x100;
  if (p_actwk->u.obj.actflg0.unused2 == 1) {
    yspeed = -yspeed;
    p_actwk->u.obj.callback_ptr = &body_wait1_init1;
  }
  p_actwk->u.obj.actflg0.unused2 ^= 1;
  p_actwk->yspeed = yspeed;
  chk_actsubc(p_actwk);
}


static void bs00m1_body_wait3(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
  chk_actsubc(p_actwk);
}


static void body_wait2_init1(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &body_movelr_init;
  body_wait2_init10(p_actwk);
}


static void body_wait2_init10(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.timer = 16;
}


static void body_movelr_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 14;
  p_actwk->u.obj.puka.cnt = 4;
  p_actwk->u.obj.callback_ptr = &body_chg_init;
  short xspeed = 0x100;
  if (p_actwk->u.obj.actflg0.fura_right == 0) {
    xspeed = -xspeed;
  }
  p_actwk->u.obj.actflg0.fura_right ^= 1;
  p_actwk->xspeed = xspeed;
  bs00m0_puka_init(p_actwk);
}


static void bs00m1_body_movelr(SKC_sprite_status* p_actwk) {
  if (!puka_count(p_actwk)) {
    speedset2(p_actwk);
  }
  else {
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
  chk_actsubc(p_actwk);
}


static void body_chg_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.puka.cnt = 4;
  p_actwk->u.obj.callback_ptr = &body_wait3_init;
  p_actwk->actflg.hflip ^= 1;
  speedset2(p_actwk);
}


static void body_wait3_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &body_moveud_init;
  body_wait2_init10(p_actwk);
}


static void bs00m1_die0(SKC_sprite_status* p_actwk) {
  bs00m0_die1_init(p_actwk);
}


static void bs00m0_die1_init(SKC_sprite_status* p_actwk) {
  set_midbos_die(p_actwk);
  set_act00(p_actwk, &bs00m0_break_set_tbl);
}


void bs00m1_futa(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[6] = {
    &bs00m0_futa_init,
    &bs00m1_futa_wait0,
    &bs00m0_dec_timer,
    &bs00m0_time_pg,
    &bs00m0_time_pg,
    &dummy
  };

  ko_offset1(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die1(p_actwk);
}


static void bs00m1_futa_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 1) {
    p_actwk->r_no = 4;
    p_actwk->u.obj.callback_ptr = &futa_open_init1;
    set_futa_ini_time(p_actwk);
  }
}


static void futa_open_init1(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &futa_close_init1;
  futa_open_init00(p_actwk);
}


static void futa_close_init1(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->u.obj.callback_ptr = &futa_wait2_init1;
  p_actwk->u.obj.pg_data_ptr = futa00m0_pg02;
  set_act00(p_actwk, &napm00m1_set_tbl);
}


static void futa_wait2_init1(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_parentwk->u.obj.actflg0.unused1 = 0;
}


void bs00m1_napalm(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &bs00m1_napm_init,
    &bs00m1_napm_up,
    &bs00m0_dec_timer,
    &bs00m1_napm_wait1,
    &bs00m1_napm_down
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_parentwk = &g_ram.actwk[p_parentwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 0) {
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
  else {
    set_emy_fout0(p_actwk);
  }
}


static void bs00m1_napm_init(SKC_sprite_status* p_actwk) {
  bs00m0_napm_init(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->r_ptr == &bs00m0_futa) {
    p_actwk->colino = 0;
  }
  p_actwk->u.obj.callback_ptr = &napm_wait0_init;
  p_actwk->sprvsize = 8;
}


static void bs00m1_napm_up(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset2(p_actwk);
  dec_timer(p_actwk);
}


static void napm_wait0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.timer = 8;
  p_actwk->u.obj.callback_ptr = &napm_wait1_init;
}


static void napm_wait1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->u.obj.callback_ptr = &napm_down_init;
  p_actwk->actflg.vflip = 1;
  set_napm_fall(p_actwk);
  short yposi = (g_ram.scra_v_posit >> 16) - 32;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static void bs00m1_napm_wait1(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void napm_down_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->sprpri = PRI_1;
  p_actwk->u.obj.callback_ptr = &set_napmexp_init;
}


static void bs00m1_napm_down(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset2(p_actwk);
  emy_fall_col(p_actwk);
}


static void set_napmexp_init(SKC_sprite_status* p_actwk) {
  soundset(78);
  set_act00(p_actwk, &napmexp_set_tbl);
  set_emy_fout0(p_actwk);
}


void bs00m0_napmexp(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &bs00m0_napmexp_init,
    &bs00m0_napmexp_wait0,
    &bs00m0_napmexp_pchg
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void bs00m0_napmexp_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &napmexp_init_tbl);
  if (get_act(g_ram.stageno) != ACT_1) {
    memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
    p_actwk->sproffset.gfx = 0x500;
  }
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->colino == 0) {
    p_actwk->colino = 0;
  }
  p_actwk->u.obj.pg_data_ptr = exp01_pg00;
  p_actwk->u.obj.callback_ptr = &napmexp_pchg_init;
  set_timer(p_actwk, 12);
}


static void bs00m0_napmexp_wait0(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void napmexp_pchg_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
}


static void bs00m0_napmexp_pchg(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  chk_actsubc(p_actwk);
}


void bs00m2_set(SKC_sprite_status* p_actwk) {
  short hposi_tbl[6] = {
    -32, -104, -16, -88, -8, -80
  };
  short vposi_tbl[6] = {
    784, 784, 796, 796, 808, 808
  };
  short speed_tbl[6] = {
    0x200, 0x200, 0x180, 0x180, 0x100, 0x100
  };
  unsigned short timer_tbl[6] = {
    0, 0, 0, 0, 0, 0
  };
  unsigned char pt_tbl[6] = {
    0, 0, 1, 1, 2, 2
  };

  enemy_init0(p_actwk, &bs00m2_init_tbl);
  p_actwk->r_ptr = &bs00m2_wait;
  p_actwk->u.obj.callback_ptr = &move_init;
  short xposi = (g_ram.scra_h_posit >> 16) + hposi_tbl[p_actwk->u.obj.userflag / 2];
  fp16_set_integer(&p_actwk->xposi, xposi);
  fp16_set_integer(&p_actwk->yposi, vposi_tbl[p_actwk->u.obj.userflag / 2]);
  p_actwk->xspeed = speed_tbl[p_actwk->u.obj.userflag / 2];
  p_actwk->u.obj.timer = speed_tbl[p_actwk->u.obj.userflag / 2];
  p_actwk->patno = pt_tbl[p_actwk->u.obj.userflag / 2];
}


static void bs00m2_wait(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void move_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &bs00m2_move;
}


static void bs00m2_move(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  chk_oya_die1(p_actwk);
}


static void bs00m0_break(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &bs00m0_break_init_tbl);
  p_actwk->r_ptr = &chk_break_fout;
  p_actwk->patno = p_actwk->u.obj.userflag / 2 + 14;
  set_break_spd(p_actwk, 8);
}


static void set_futa_ini_time(SKC_sprite_status* p_actwk) {
  unsigned short wait_tbl[3] = {
    0, 16, 32
  };

  p_actwk->u.obj.timer = wait_tbl[p_actwk->u.obj.userflag / 2];
}


static void set_napm_fall(SKC_sprite_status* p_actwk) {
  unsigned short napm_time_tbl[3] = {
    0, 32, 64
  };

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->u.obj.timer = napm_time_tbl[p_actwk->u.obj.userflag / 2];
  set_napm_fall0(p_actwk, p_parentwk);
}


static void set_napm_fall0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_parentwk) {
  unsigned char napm_l_tbl[16] = {
    2, 3, 4, 0, 0, 2, 4, 0, 1, 3, 4, 0, 0, 1, 4, 0
  };
  unsigned char napm_r_tbl[16] = {
    3, 2, 0, 0, 4, 3, 1, 0, 4, 2, 0, 0, 3, 2, 1, 0
  };
  short napm_l_posi_tbl[5] = {
    36, 76, 116, 156, 196
  };
  short napm_r_posi_tbl[5] = {
    124, 164, 204, 244, 284
  };

  p_actwk->u.obj.puka.cnt += 4;
  unsigned char (*napm_tbl)[16] = p_actwk->actflg.hflip == 0 ? &napm_l_tbl : &napm_r_tbl;
  short (*napm_posi_tbl)[5] = p_actwk->actflg.hflip == 0 ? &napm_l_posi_tbl : &napm_r_posi_tbl;
  unsigned char posi_id = (*napm_tbl)[p_parentwk->u.obj.userflag / 2 + (p_actwk->u.obj.puka.cnt & 0xC)];
  short xposi = (g_ram.scra_h_posit >> 16) + (*napm_posi_tbl)[posi_id];
  fp16_set_integer(&p_actwk->xposi, xposi);
  p_actwk->yspeed = 0x400;
}


static void chk_bs00m0_damage(SKC_sprite_status* p_actwk) {
  unsigned char adr_tbl[4] = {
    23, 26, 27, 30
  };
  unsigned short color_tbl[8] = {
    0x644, 0x240, 0x020, 0x644,
    0x888, 0xAAA, 0xEEE, 0xAAA
  };

  if (p_actwk->colino != 0) return;

  if (p_actwk->colicnt != 0) {
    if (p_actwk->mstno == 0) {
      p_actwk->mstno = 32;
      soundset(110);
      p_actwk->u.obj.cddat.pl2push = 1;
    }
    unsigned short* p_color_tbl = p_actwk->mstno & 1 ? &color_tbl[0] : &color_tbl[4];
    set_damg_cor04(adr_tbl, p_color_tbl);
    --p_actwk->mstno;
    if (p_actwk->mstno == 0) {
      p_actwk->u.obj.cddat.pl2push = 0;
      p_actwk->colino = p_actwk->pattimm;
    }
  }
  else {
    p_actwk->r_ptr = &bos_tim_act;
    p_actwk->u.obj.callback_ptr = &bs00m0_die1_init;
    p_actwk->xspeed = 0;
    p_actwk->yspeed = 0;
    SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &bsexp01_set_tbl);
    if (p_new_actwk != 0) {
      p_new_actwk->u.obj.userflag = 16;
    }
    boss_die_init(p_actwk);
  }
}


static SKC_enemy_init0_data bs00m0_init_tbl = {
  bs00m0_pt,
  { 0x41A, 0, 0, 1, 1 },
  PRI_4,
  32,
  32,
  0,
  0x0F
};


static SKC_enemy_init1_data jet00m0_init_tbl = {
  { 0x41A, 0, 0, 0, 1 },
  PRI_3,
  40,
  16,
  2,
  0x9C
};


static SKC_enemy_init1_data exit00m0_init_tbl = {
  { 0x41A, 0, 0, 1, 1 },
  PRI_4,
  4,
  8,
  6,
  0
};


static SKC_enemy_init1_data futa00m0_init_tbl = {
  { 0x41A, 0, 0, 1, 1 },
  PRI_5,
  8,
  8,
  3,
  0
};


static SKC_enemy_init1_data napf00m0_init_tbl = {
  { 0x41A, 0, 0, 0, 0 },
  PRI_4,
  8,
  8,
  7,
  0
};


static SKC_enemy_init1_data napm00m0_init_tbl = {
  { 0x41A, 0, 0, 0, 0 },
  PRI_5,
  8,
  16,
  12,
  0x98
};


static SKC_enemy_init0_data napmexp_init_tbl = {
  exp01_pt,
  { 0x4D2, 0, 0, 0, 0 },
  PRI_1,
  12,
  12,
  0,
  0x97
};


static SKC_enemy_init0_data kaen00m0_init_tbl = {
  kaen00m0_pt,
  { 0x482, 0, 0, 0, 1 },
  PRI_2,
  16,
  16,
  0,
  0x8B
};


static SKC_enemy_init0_data bs00m2_init_tbl = {
  bs00m2_pt,
  { 0x474, 0, 0, 1, 0 },
  PRI_7,
  16,
  16,
  0,
  0
};


static SKC_enemy_init2_data bs00m0_break_init_tbl = {
  PRI_4,
  16,
  20,
  0,
  0
};


static SKC_set_act00_data jet00m0_set_tbl = {
  1,
  {
    { &bs00m0_jet, 0, 32 },
    { &bs00m0_exit, -36, 8 }
  }
};


static SKC_set_act02_data bs00m2_set_tbl = {
  5,
  &bs00m2_set,
  0,
  0
};


static SKC_set_act00_data futa00m0_set_tbl = {
  2,
  {
    { &bs00m0_futa, 0, -32 },
    { &bs00m0_futa, 9, -32 },
    { &bs00m0_futa, 18, -24 }
  }
};


static SKC_set_act00_data futa00m1_set_tbl = {
  2,
  {
    { &bs00m1_futa, 0, -32 },
    { &bs00m1_futa, 9, -28 },
    { &bs00m1_futa, 18, -24 }
  }
};


static SKC_set_act00_data napm00m0_set_tbl = {
  1,
  {
    { &bs00m0_napfire, 0, 4 },
    { &bs00m0_napalm, 0, 4 }
  }
};


static SKC_set_act00_data napm00m1_set_tbl = {
  1,
  {
    { &bs00m0_napfire, 0, 4 },
    { &bs00m1_napalm, 0, 4 }
  }
};


static SKC_set_act00_data kaen00m0_set_tbl0 = {
  3,
  {
    { &bs00m0_kaen0, -100, 4 },
    { &bs00m0_kaen0, -84, 4 },
    { &bs00m0_kaen0, -68, 4 },
    { &bs00m0_kaen0, -44, 3 }
  }
};


static SKC_set_act00_data kaen00m0_set_tbl1 = {
  0,
  {
    { &bs00m0_kaen1, 0, 0 }
  }
};


SKC_set_act00_data napmexp_set_tbl = {
  6,
  {
    { &bs00m0_napmexp, 0, -36 },
    { &bs00m0_napmexp, 8, -28 },
    { &bs00m0_napmexp, -8, -28 },
    { &bs00m0_napmexp, 4, -20 },
    { &bs00m0_napmexp, -4, -20 },
    { &bs00m0_napmexp, 4, -4 },
    { &bs00m0_napmexp, -4, -4 }
  }
};


static SKC_set_act00_data screxp01_set_tbl = {
  0,
  {
    { &screxp01_set, 0, 0 }
  }
};


static SKC_set_act00_data bs00m0_break_set_tbl = {
  3,
  {
    { &bs00m0_break, -16, -8 },
    { &bs00m0_break, 12, -16 },
    { &bs00m0_break, -16, 20 },
    { &bs00m0_break, 16, 12 }
  }
};


static signed char jet00m0_pg00[4] = { 1, 1, 2, -4 };


static signed char futa00m0_pg00[5] = { 7, 3, 4, 5, -12 };
static signed char futa00m0_pg01[7] = { 3, 5, 4, 5, 5, 23, -12 };
static signed char futa00m0_pg02[9] = { 5, 23, 5, 23, 4, 5, 3, 5, -12 };


static signed char napm00m0_pg00[13] = { 7, 1, 7, 1, 8, 1, 9, 3, 10, 3, 11, 3, -12 };
static signed char napm00m0_pg01[4] = { 1, 12, 13, -4 };


static signed char napmexp_pg00[15] = { 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 4, -12 };


static signed char kaen00m0_pg00[5] = { 0, 1, 0, 1, -12 };
static signed char kaen00m0_pg01[11] = { 2, 1, 2, 1, 3, 2, 4, 4, 5, 1, -12 };
static signed char kaen00m0_pg02[13] = { 0, 1, 0, 1, 1, 2, 2, 2, 3, 4, 4, 4, -12 };


static unsigned short boss00m0color[16] = {
  0x000, 0xEEE, 0xE88, 0xC66, 0xA64, 0x0EE, 0x088, 0x642, 0x020, 0x000, 0x240, 0x020, 0xECC, 0xA88, 0x644, 0x044
};
