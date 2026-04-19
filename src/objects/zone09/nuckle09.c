#include "nuckle09.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../data/colortbl.h"
#include "../../data/sintbl.h"
#include "../../data/cg/clen.h"
#include "../../data/cg/eggmbl.h"
#include "../../data/cg/zone09/iwa091.h"
#include "../../data/cg/zone09/nk0931.h"
#include "../../data/pat/zone09/door09.h"
#include "../../types/cgdata.h"
#include "../../types/enemyinitdata.h"
#include "../../types/setactdata.h"
#include "../../types/sonic3ram.h"
#include "../../types/spritepattern.h"
#include "../../types/spritestatus.h"
#include "../../types/spritestatushandler.h"
#include "../../utils/bits.h"
#include "../../utils/controller.h"
#include "../../utils/fp16.h"
#include "../../utils/fp8.h"
#include "../../utils/stageno.h"
#include "../../action.h"
#include "../../actset.h"
#include "../../dev.h"
#include "../../etc.h"
#include "../../dircol.h"
#include "../../hitchk.h"
#include "../../shared.h"
#include "../../sound.h"
#include "../common.h"
#include "../eggmbl.h"
#include "../explosion.h"
#include "../nuckle.h"
#include "../zone00/bs00m.h"
static void nuckle090_init(SKC_sprite_status* p_actwk);
static void nuckle090_wait0(SKC_sprite_status* p_actwk);
static void nuckle090_pnch0_init(SKC_sprite_status* p_actwk);
static void nuckle090_pnch0(SKC_sprite_status* p_actwk);
static void nuckle090_pnch1_init(SKC_sprite_status* p_actwk);
static void nuckle090_pnch1(SKC_sprite_status* p_actwk);
static void nuckle090_lagh0_init(SKC_sprite_status* p_actwk);
static void nuckle090_lagh0(SKC_sprite_status* p_actwk);
static void ev0910_wait0(SKC_sprite_status* p_actwk);
static void ev0910_wait1(SKC_sprite_status* p_actwk);
static void ev0910_wait2(SKC_sprite_status* p_actwk);
static void ev0910_wait3(SKC_sprite_status* p_actwk);
static void ev0910_wait4(SKC_sprite_status* p_actwk);
static void iwa091(SKC_sprite_status* p_actwk);
static void iwa091_wait0(SKC_sprite_status* p_actwk);
static void iwa091_move0(SKC_sprite_status* p_actwk);
static void iwa091_jump0(SKC_sprite_status* p_actwk);
static unsigned short nuckle091_lim_tbl[8];
static void nk0930(SKC_sprite_status* p_actwk);
static void nk0930_boss_set(SKC_sprite_status* p_actwk);
static void set_event_bit(SKC_sprite_status* p_actwk);
static void nk0930_move(SKC_sprite_status* p_actwk);
static void nk0930_ftwk0(SKC_sprite_status* p_actwk);
static void ftwk0_init(SKC_sprite_status* p_actwk);
static void nk0930_gurd0(SKC_sprite_status* p_actwk);
static void(*gurd0_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*);
static void gurd0_init(SKC_sprite_status* p_actwk);
static void nk0930_gurd1(SKC_sprite_status* p_actwk);
static void gurd1_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void nk0930_pnch0(SKC_sprite_status* p_actwk);
static void pnch0_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void nk0930_jump0(SKC_sprite_status* p_actwk);
static void jump1_init(SKC_sprite_status* p_actwk);
static void nk0930_jump1(SKC_sprite_status* p_actwk);
static void(*jump1_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*);
static void jump0_init(SKC_sprite_status* p_actwk);
static void nk0930_jump2(SKC_sprite_status* p_actwk);
static void jump2_init(SKC_sprite_status* p_actwk);
static void nk0930_down0(SKC_sprite_status* p_actwk);
static void down0_init(SKC_sprite_status* p_actwk);
static void nk0930_land0(SKC_sprite_status* p_actwk);
static void land0_init(SKC_sprite_status* p_actwk, short yoffset);
static void nk0930_spin0(SKC_sprite_status* p_actwk);
static void spin0_init(SKC_sprite_status* p_actwk);
static void nk0930_spin1(SKC_sprite_status* p_actwk);
static void spin1_init(SKC_sprite_status* p_actwk);
static void nk0930_damg0(SKC_sprite_status* p_actwk);
static void nk0930_die0(SKC_sprite_status* p_actwk);
static void die0_init(SKC_sprite_status* p_actwk);
static void nk0930_die1(SKC_sprite_status* p_actwk);
static void die1_init(SKC_sprite_status* p_actwk, short yoffset);
static void nk0930_die2(SKC_sprite_status* p_actwk);
static void die2_init(SKC_sprite_status* p_actwk);
static void nk0930_wake0(SKC_sprite_status* p_actwk);
static void wake0_init(SKC_sprite_status* p_actwk);
static void nk0930_run0(SKC_sprite_status* p_actwk);
static void run0_init(SKC_sprite_status* p_actwk);
static void nk0930_run1(SKC_sprite_status* p_actwk);
static void run1_init(SKC_sprite_status* p_actwk);
static void nk0930_wait0(SKC_sprite_status* p_actwk);
static void wait0_init(SKC_sprite_status* p_actwk);
static void nk0930_jump3(SKC_sprite_status* p_actwk);
static void jump3_init(SKC_sprite_status* p_actwk);
static void nk0930_wait1(SKC_sprite_status* p_actwk);
static void wait1_init(SKC_sprite_status* p_actwk, short yoffset);
static void nk0930_jump4(SKC_sprite_status* p_actwk);
static void jump4_init(SKC_sprite_status* p_actwk);
static void nk0930_angry0(SKC_sprite_status* p_actwk);
static void angry0_init(SKC_sprite_status* p_actwk);
static void nk0930_run2(SKC_sprite_status* p_actwk);
static void run2_init(SKC_sprite_status* p_actwk);
static void nk0930_wait2(SKC_sprite_status* p_actwk);
static void wait2_init(SKC_sprite_status* p_actwk);
static void nk0930_jump5(SKC_sprite_status* p_actwk);
static void jump5_init(SKC_sprite_status* p_actwk);
static void nk0930_jump6(SKC_sprite_status* p_actwk);
static void jump6_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_coliwk);
static void nk0930_run3(SKC_sprite_status* p_actwk);
static void run3_init(SKC_sprite_status* p_actwk);
static void nk0930_jump7(SKC_sprite_status* p_actwk);
static void jump7_init(SKC_sprite_status* p_actwk);
static void nk0930_cach0(SKC_sprite_status* p_actwk);
static void set_cach0_ofs(SKC_sprite_status* p_actwk);
static void cach0_init(SKC_sprite_status* p_actwk);
static void nk0930_elec0(SKC_sprite_status* p_actwk);
static void elec0_init(SKC_sprite_status* p_actwk);
static void nk0930_fall0(SKC_sprite_status* p_actwk);
static void fall0_init(SKC_sprite_status* p_actwk);
static void nk0930_land1(SKC_sprite_status* p_actwk);
static void land1_init(SKC_sprite_status* p_actwk, short yoffset);
static void nk0930_wait4(SKC_sprite_status* p_actwk);
static void wait4_init(SKC_sprite_status* p_actwk);
static void nk0930_fall1(SKC_sprite_status* p_actwk);
static void fall1_init(SKC_sprite_status* p_actwk);
static void fall1_init__set_exp(SKC_sprite_status* p_actwk);
static void nk0930_fall2(SKC_sprite_status* p_actwk);
static void fall2_init(SKC_sprite_status* p_actwk);
static void nk0930_land2(SKC_sprite_status* p_actwk);
static void land2_init(SKC_sprite_status* p_actwk, short yoffset);
static void nk0930_wake1(SKC_sprite_status* p_actwk);
static void wake1_init(SKC_sprite_status* p_actwk);
static void nk0930_wake2(SKC_sprite_status* p_actwk);
static void wake2_init(SKC_sprite_status* p_actwk);
static void nk0930_run4(SKC_sprite_status* p_actwk);
static void run4_init(SKC_sprite_status* p_actwk);
static void nk0930_comn0(SKC_sprite_status* p_actwk);
static void comn0_init(SKC_sprite_status* p_actwk);
static void nk0930_pnch1(SKC_sprite_status* p_actwk);
static void pnch1_init(SKC_sprite_status* p_actwk);
static void nk0930_run5(SKC_sprite_status* p_actwk);
static void run5_init(SKC_sprite_status* p_actwk);
static void nk0930_wait5(SKC_sprite_status* p_actwk);
static void wait5_init(SKC_sprite_status* p_actwk);
static void nk0930_jump8(SKC_sprite_status* p_actwk);
static void jump8_init(SKC_sprite_status* p_actwk);
static void nk0930_land3(SKC_sprite_status* p_actwk);
static void land3_init(SKC_sprite_status* p_actwk);
static void nk0930_ball0(SKC_sprite_status* p_actwk);
static void ball0_init(SKC_sprite_status* p_actwk);
static void nk0930_effect_wait0(SKC_sprite_status* p_actwk);
static void ev0930(SKC_sprite_status* p_actwk);
static void ev0930_wait0(SKC_sprite_status* p_actwk);
static void set_pl_stop(SKC_sprite_status* p_playerwk);
static void ev0930_wait1(SKC_sprite_status* p_actwk);
static void ev0930_wait2(SKC_sprite_status* p_actwk);
static void ev0930_move0(SKC_sprite_status* p_actwk);
static void ev0930_wait3(SKC_sprite_status* p_actwk);
static void ev0930_move1(SKC_sprite_status* p_actwk);
static void ev0930_move2(SKC_sprite_status* p_actwk);
static void ev0930_wait4(SKC_sprite_status* p_actwk);
static void ev0930_wait5(SKC_sprite_status* p_actwk);
static void ev0930_wait6(SKC_sprite_status* p_actwk);
static void ev0930_wait7(SKC_sprite_status* p_actwk);
static void embl0930(SKC_sprite_status* p_actwk);
static void embl0930_wait0(SKC_sprite_status* p_actwk);
static void embl0930_move0(SKC_sprite_status* p_actwk);
static void embl0930_wait1_init(SKC_sprite_status* p_actwk);
static void embl0930_wait1(SKC_sprite_status* p_actwk);
static void embl0930_wait2(SKC_sprite_status* p_actwk);
static void embl0930_wait3(SKC_sprite_status* p_actwk);
static void embl0930_move1(SKC_sprite_status* p_actwk);
static void clen0930_wait0(SKC_sprite_status* p_actwk);
static void clen0930_wait1(SKC_sprite_status* p_actwk);
static void clen0930_wait1__catch(SKC_sprite_status* p_actwk);
static void clen0930_cach0(SKC_sprite_status* p_actwk);
static void clen0930_cach1(SKC_sprite_status* p_actwk);
static void clenparts_wait0(SKC_sprite_status* p_actwk);
static void clenchain_wait0(SKC_sprite_status* p_actwk);
static void smok0930_wait0(SKC_sprite_status* p_actwk);
static void smok0930_pchg0(SKC_sprite_status* p_actwk);
static void smok0930_pchg1_init(SKC_sprite_status* p_actwk);
static void smok0930_pchg1(SKC_sprite_status* p_actwk);
static void caos09_frag_wait0(SKC_sprite_status* p_actwk);
static void frag_fall0_init(SKC_sprite_status* p_actwk);
static void caos09_frag_fall0(SKC_sprite_status* p_actwk);
static void nk0930_exp_wait0(SKC_sprite_status* p_actwk);
static void embl0930_handb_wait0(SKC_sprite_status* p_actwk);
static void embl0930_lhand0(SKC_sprite_status* p_actwk);
static void embl0930_lhand_wait0(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move0(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move1(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move10(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move2(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move3(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move4(SKC_sprite_status* p_actwk);
static void embl0930_lhand_wait1(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move5(SKC_sprite_status* p_actwk);
static void embl0930_lhand_move6(SKC_sprite_status* p_actwk);
static void door09_wait0(SKC_sprite_status* p_actwk);
static void door09_break_wait0(SKC_sprite_status* p_actwk);
static void piyo09_wait0(SKC_sprite_status* p_actwk);
static void piyo09_wait1(SKC_sprite_status* p_actwk);
static void piyo09_fout0_init(SKC_sprite_status* p_actwk);
static void iwa091_pg(SKC_sprite_status* p_actwk);
static void chk_iwa091_col(SKC_sprite_status* p_actwk);
static void chk_iwa091_col__chk_catch(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plbit, unsigned char* p_plangle);
static void chk_iwa091_col__chk_col(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plbit, unsigned char* p_plangle, unsigned char patno);
static void chk_nk0930_rev(SKC_sprite_status* p_actwk, bool right);
static void nk0930_pl_damage(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void nk0930_pl_damage0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void chk_nk0930_col(SKC_sprite_status* p_actwk, void(*p_handlers[4])(SKC_sprite_status*, SKC_sprite_status*));
static void chk_nk0930_col__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, void(*p_handlers[4])(SKC_sprite_status*, SKC_sprite_status*));
static void chk_nk0930_limit(SKC_sprite_status* p_actwk);
static void nk0930_effect_wrt(SKC_sprite_status* p_actwk);
static void door09_break_init(SKC_sprite_status* p_actwk);
static void chk_embl0930_damage0(SKC_sprite_status* p_actwk);
static void chk_embl0930_damage1(SKC_sprite_status* p_actwk);
static void embl_hand_ura(SKC_sprite_status* p_actwk);
static void chk_top_pt(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern iwa091_pt00;
static SKC_sprite_pattern nk0931_pt00;
static SKC_sprite_pattern nk0931_pt01;
static SKC_sprite_pattern nk0931_pt02;
static SKC_sprite_pattern nk0931_pt03;
static SKC_sprite_pattern nk0931_pt04;
static SKC_sprite_pattern nk0931_pt05;
static SKC_sprite_pattern nk0931_pt06;
static SKC_sprite_pattern nk0931_pt07;
static SKC_sprite_pattern nk0931_pt08;
static SKC_sprite_pattern nk0931_pt09;
static SKC_sprite_pattern nk0931_pt10;
static SKC_sprite_pattern nk0931_pt11;
static SKC_sprite_pattern nk0931_pt12;
static SKC_sprite_pattern nk0931_pt13;
static SKC_sprite_pattern nk0931_pt14;
static SKC_sprite_pattern nk0931_pt15;
static SKC_sprite_pattern nk0931_pt16;
static SKC_sprite_pattern nk0931_pt17;
static SKC_sprite_pattern nk0931_pt18;
static unsigned short nk0931_tbl00[3];
static unsigned short nk0931_tbl01[3];
static unsigned short nk0931_tbl02[3];
static unsigned short nk0931_tbl03[3];
static unsigned short nk0931_tbl04[3];
static unsigned short nk0931_tbl05[3];
static unsigned short nk0931_tbl06[3];
static unsigned short nk0931_tbl07[3];
static unsigned short nk0931_tbl08[3];
static unsigned short nk0931_tbl09[3];
static unsigned short nk0931_tbl10[3];
static unsigned short nk0931_tbl11[4];
static unsigned short nk0931_tbl12[4];
static unsigned short nk0931_tbl13[3];
static unsigned short nk0931_tbl14[3];
static unsigned short nk0931_tbl15[3];
static unsigned short nk0931_tbl16[4];
static unsigned short nk0931_tbl17[3];
static unsigned short nk0931_tbl18[3];
static SKC_set_act05_data nk0930_effect_set_tbl;
static SKC_set_act05_data nk0930_exp_set_tbl;
static SKC_set_act00_data clen0930_set_tbl;
static SKC_set_act05_data smok0930_set_tbl;
static SKC_set_act02_data embl0930_handb_set_tbl;
static SKC_set_act07_data embl0930_lhand_set_tbl;
static SKC_set_act07_data embl0930_rhand_set_tbl;
static SKC_set_act05_data caos09_frag_set_tbl;
static SKC_set_act05_data door09_set_tbl;
static SKC_set_act05_data piyo09_set_tbl;
static SKC_set_act05_data door09_break_set_tbl;
static SKC_enemy_init0_data nk0930_effect_init_tbl;
static SKC_enemy_init2_data clenparts_init_tbl;
static SKC_enemy_init2_data clenchain_init_tbl;
static SKC_enemy_init0_data smok0930_init_tbl;
static SKC_enemy_init0_data caos09_frag_init_tbl;
static SKC_enemy_init0_data embl0930_handb_init_tbl;
static SKC_enemy_init2_data embl0930_lhand_init_tbl;
static SKC_enemy_init0_data door09_init_tbl;
static SKC_enemy_init2_data door09_break_init_tbl;
static SKC_enemy_init0_data piyo09_init_tbl;
static SKC_enemy_init0_data iwa091_init_tbl;
static signed char smok0930_pg00[7];
static signed char smok0930_pg01[5];
static signed char piyo09_pg00[6];
static SKC_sprite_pattern* piyo09_pt[6];
static SKC_sprite_pattern piyo09_pt00;
static SKC_sprite_pattern piyo09_pt01;
static SKC_sprite_pattern piyo09_pt02;
static SKC_sprite_pattern piyo09_pt03;
static SKC_sprite_pattern piyo09_pt04;
static SKC_sprite_pattern piyo09_pt05;
static SKC_sprite_pattern emblcl_pt00;
static SKC_sprite_pattern emblcl_pt01;
static SKC_sprite_pattern emblcl_pt02;
static SKC_sprite_pattern emblcl_pt03;
static SKC_sprite_pattern emblcl_pt04;
static SKC_sprite_pattern emblcl_pt05;
static SKC_sprite_pattern emblcl_pt06;
static SKC_sprite_pattern emblcl_pt07;
static SKC_sprite_pattern emblcl_pt08;
static SKC_sprite_pattern emblcl_pt09;
static SKC_sprite_pattern emblcl_pt10;
static SKC_sprite_pattern emblcl_pt11;
static SKC_sprite_pattern emblcl_pt12;
static SKC_sprite_pattern emblcl_pt13;
static SKC_sprite_pattern emblcl_pt14;
static SKC_sprite_pattern emblcl_pt15;
static SKC_sprite_pattern emblcl_pt16;
static SKC_sprite_pattern emblcl_pt17;
static SKC_sprite_pattern emblcl_pt18;
static SKC_sprite_pattern emblcl_pt19;
static SKC_sprite_pattern emblcl_pt20;
static SKC_sprite_pattern emblcl_pt21;
static SKC_sprite_pattern emblcl_pt22;
static SKC_sprite_pattern emblcl_pt23;
static SKC_sprite_pattern emblcl_pt24;
static SKC_sprite_pattern emblcl_pt25;
static SKC_sprite_pattern emblcl_pt26;
static SKC_sprite_pattern emblcl_pt27;
static SKC_sprite_pattern emblcl_pt28;

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void nuckle090(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &nuckle090_init,
    &nuckle090_wait0,
    &nuckle090_pnch0,
    &nuckle090_pnch1,
    &nuckle090_lagh0
  };

  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    act_tbl[p_actwk->r_no / 2](p_actwk);
    nk0930_wrt(p_actwk);
    actionsub(p_actwk);
  }
}


static void nuckle090_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  p_actwk->actflg.hflip = 1;
  fp16_set_integer(&p_actwk->xposi, 0x3A38);
  fp16_set_integer(&p_actwk->yposi, 0xEC);
  set_emy_cor(&nuckle_cor_tbl);
}


static void nuckle090_wait0(SKC_sprite_status* p_actwk) {
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 1)) {
    nuckle090_pnch0_init(p_actwk);
  }
}


static void nuckle090_pnch0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->patno = 222;
  p_actwk->u.obj.callback_ptr = &nuckle090_pnch1_init;
  nuckle090_pnch0(p_actwk);
}


static void nuckle090_pnch0(SKC_sprite_status* p_actwk) {
  time_pgs0(p_actwk, panch_pg01);
}


static void nuckle090_pnch1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  SET_BIT(g_ram.DAT_08fffab8_bitfield, 2);
  p_actwk->u.obj.callback_ptr = &nuckle090_lagh0_init;
  pg_init(p_actwk, panch_pg02);
}


static void nuckle090_pnch1(SKC_sprite_status* p_actwk) {
  time_pgs0(p_actwk, panch_pg02);
}


static void nuckle090_lagh0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  nuckle090_lagh0(p_actwk);
}


static void nuckle090_lagh0(SKC_sprite_status* p_actwk) {
}


void ev0910(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    p_actwk->r_ptr = &ev0910_wait0;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &fox_auto;
    }
    ev0910_wait0(p_actwk);
  }
}


static void ev0910_wait0(SKC_sprite_status* p_actwk) {
  short ev0910_col_tbl[4] = {
    -16, 16, -576, 576
  };

  if (!emy_col_a1(p_actwk, &g_ram.actwk[0], ev0910_col_tbl)) return;

  p_actwk->r_ptr = &ev0910_wait1;
  g_ram.scralim_left = g_ram.scra_h_posit >> 16;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &nuckle;
    result.actwk_ptr->u.obj.userflag = 36;
  }
  set_nuckle_bgm();
  result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &iwa091;
  }
  unlze_moduled(&g_vram[0xA000], iwa091_cg);
}


static void ev0910_wait1(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) < 0x39B0) return;

  p_actwk->r_ptr = &ev0910_wait2;
  g_ram.pl_input_lock_flag = 0xFF;
  g_ram.swdata1_auto = 0;
}


static void ev0910_wait2(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.cddat.jump == 1) return;

  p_actwk->r_ptr = &ev0910_wait3;
  SET_BIT(g_ram.DAT_08fffab8_bitfield, 0);
  g_ram.scralim_left = 0;
  g_ram.pl_scr_lock_flag = 0xFF;
  g_ram.pl_input_lock_flag = 0;
  g_ram.actwk[0].u.play.control_bitfield = 0x81;
  g_ram.actwk[0].mstno = 7;
}


static void ev0910_wait3(SKC_sprite_status* p_actwk) {
  g_ram.scra_v_posit -= 0x200;
  if (g_ram.scra_v_posit >> 16 >= 144) {
    p_actwk->r_ptr = &ev0910_wait4;
    SET_BIT(g_ram.DAT_08fffab8_bitfield, 1);
  }
}


static void ev0910_wait4(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].yposi) < 0x4C0) return;

  g_ram.notitle = 0xFF;
  g_ram.plpowerdat_s2 = g_ram.actwk[0].u.play.powerdat;
  set_stageno(LAVA_REEF_BOSS);
}


static void iwa091(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &iwa091_init_tbl);
  p_actwk->r_ptr = &iwa091_wait0;
  fp16_set_integer(&p_actwk->xposi, 0x3A08);
  fp16_set_integer(&p_actwk->yposi, 0xE2);
  p_actwk->sprvsize = 31;
  p_actwk->u.obj.oya = p_actwk - g_ram.actwk;
  iwa091_wait0(p_actwk);
}


static void iwa091_wait0(SKC_sprite_status* p_actwk) {
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 2)) {
    p_actwk->r_ptr = &iwa091_move0;
    p_actwk->xspeed = -0x200;
  }
  actionsub(p_actwk);
}


static void iwa091_move0(SKC_sprite_status* p_actwk) {
  set_cont_se(105);
  iwa091_pg(p_actwk);
  chk_iwa091_col(p_actwk);
  speedset2(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset >= 0) {
    p_actwk->r_ptr = &iwa091_jump0;
  }
  actionsub(p_actwk);
}


static void iwa091_jump0(SKC_sprite_status* p_actwk) {
  set_cont_se(105);
  iwa091_pg(p_actwk);
  chk_iwa091_col(p_actwk);
  speedsetg20(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      p_actwk->yspeed = -0x100;
      g_ram.scr_shake_flg = 20;
      soundset(89);
    }
  }
  actionsub(p_actwk);
}


static unsigned short nuckle091_lim_tbl[8] = {
  0x0180, 0x0480, 0x0FE0, 0x11E0, 0x0380, 0x0380, 0x10E0, 0x10E0
};


void nuckle091(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &nk0930;
  g_ram.DAT_08fffaa4_obj = p_actwk - g_ram.actwk;
  memcpy(&g_ram.actwk[48], p_actwk, sizeof(SKC_sprite_status));
}


static void nk0930(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    chk_boss_set(p_actwk, nuckle091_lim_tbl, &nk0930_boss_set);
    nk0930_boss_set(p_actwk);
  }
}


static void nk0930_boss_set(SKC_sprite_status* p_actwk) {
  boss_init(p_actwk, nuckle091_lim_tbl);
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &chk_scr_bgm;
    result.actwk_ptr->u.obj.callback_ptr = &set_event_bit;
    result.actwk_ptr->direc.b.b0 = 31;
    result.actwk_ptr->u.obj.timer = 120;
    result.actwk_ptr->direc.b.b1 = p_actwk->direc.b.b1;
  }
  p_actwk->r_ptr = &nk0930_move;
  p_actwk->patbase = knuckles_pt;
  p_actwk->sproffset = 0x24DA;
  p_actwk->sprpri = PRI_2;
  p_actwk->sprhs = 24;
  p_actwk->sprvs = 24;
  p_actwk->sprvsize = 19;
  p_actwk->sprhsize = 9;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->actflg.hflip = 1;
  p_actwk->patno = 216;
  p_actwk->colicnt = 8;
  p_actwk->u.obj.pg_data_ptr = footwk_pg00;
  p_actwk->u.obj.ko = 0;
  memcpy(&g_ram.colorwk2[16], &g_ram.colorwk[16], sizeof(unsigned short) * 16);
  set_emy_cor(&nuckle_cor_tbl);
  g_ram.colorwk[22] = 0x88;
}


static void set_event_bit(SKC_sprite_status* p_actwk) {
  SET_BIT(g_ram.DAT_08fffab8_bitfield, 0);
  set_emy_fout0(p_actwk);
}


static void nk0930_move(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[47] = {
    &nk0930_ftwk0,
    &nk0930_gurd0,
    &nk0930_gurd1,
    &nk0930_pnch0,
    &nk0930_jump0,
    &nk0930_jump1,
    &nk0930_jump2,
    &nk0930_down0,
    &nk0930_land0,
    &nk0930_spin0,
    &nk0930_spin1,
    &nk0930_damg0,
    &nk0930_die0,
    &nk0930_die1,
    &nk0930_die2,
    &nk0930_wake0,
    &nk0930_run0,
    &nk0930_run1,
    &nk0930_wait0,
    &nk0930_jump3,
    &nk0930_wait1,
    &nk0930_jump4,
    &nk0930_angry0,
    &nk0930_run2,
    &nk0930_wait2,
    &nk0930_jump5,
    &nk0930_jump6,
    &nk0930_run3,
    &nk0930_jump7,
    &nk0930_cach0,
    &nk0930_elec0,
    &nk0930_fall0,
    &nk0930_land1,
    &nk0930_wait4,
    &nk0930_fall1,
    &nk0930_fall2,
    &nk0930_land2,
    &nk0930_wake1,
    &nk0930_wake2,
    &nk0930_run4,
    &nk0930_comn0,
    &nk0930_pnch1,
    &nk0930_run5,
    &nk0930_wait5,
    &nk0930_jump8,
    &nk0930_land3,
    &nk0930_ball0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);

  switch (p_actwk->u.obj.actfree.nk0930.wrt_index) {
    case 0:
      nk0930_wrt(p_actwk);
      break;
    case 2:
      set_emy_wchg(p_actwk, &nk0931_wrt_tbl);
      break;
    case 4:
      set_emy_wchg(p_actwk, &nk0a00_wrt_tbl);
      break;
  }
}


static void nk0930_ftwk0(SKC_sprite_status* p_actwk) {
  int ret = time_pgs(p_actwk);
  if (ret < 0 && BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 0)) {
    unsigned char cnt = p_actwk->u.obj.actfree.nk0930.footwk_pg_loop_cnt + 1;
    if (cnt >= 2) {
      spin0_init(p_actwk);
      return;
    }
    else {
      p_actwk->u.obj.actfree.nk0930.footwk_pg_loop_cnt = cnt;
    }
  }
  SKC_chk_distance_result result = chk_distance(p_actwk);
  chk_nk0930_rev(p_actwk, result.right);
  if ((unsigned short)result.ydistance < 64 && (unsigned short)result.xdistance < 48) {
    gurd0_init(p_actwk);
  }
}


static void ftwk0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 0;
  p_actwk->u.obj.actfree.nk0930.footwk_pg_loop_cnt = 0;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  pg_init(p_actwk, footwk_pg00);
}


static void nk0930_gurd0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  SKC_chk_distance_result result = chk_distance(p_actwk);
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  chk_nk0930_rev(p_actwk, result.right);
  if ((unsigned short)result.ydistance < 16 && (unsigned short)result.xdistance < 32 && p_playerwk->mstno != 2) {
    pnch0_init(p_actwk, p_playerwk);
  }
  else if (p_actwk->u.obj.timer-- == 0) {
    jump0_init(p_actwk);
  }
  else {
    chk_nk0930_col(p_actwk, gurd0_col_tbl);
  }
}


static void(*gurd0_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*) = {
  &gurd1_init,
  &pnch0_init,
  &damg0_init,
  &nk0930_pl_damage
};


static void gurd0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 2;
  p_actwk->patno = 218;
  p_actwk->u.obj.timer = 119;
  pg_init(p_actwk, guard_pg00);
}


static void nk0930_gurd1(SKC_sprite_status* p_actwk) {
  void(*gurd1_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*) = {
    &gurd1_init,
    &nk0930_pl_damage,
    &damg0_init,
    &nk0930_pl_damage
  };

  chk_nk0930_limit(p_actwk);
  if (p_actwk->xspeed != 0) {
    p_actwk->xspeed += p_actwk->u.obj.actfree.nk0930.accel;
    speedset2(p_actwk);
  }
  int ret = time_pgs(p_actwk);
  if (ret >= 0) {
    chk_nk0930_col(p_actwk, gurd1_col_tbl);
  }
}


static void gurd1_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.callback_ptr = &ftwk0_init;
  p_actwk->xspeed = p_actwk->actflg.hflip == 1 ? 0x2C0 : -0x2C0;
  p_actwk->u.obj.actfree.nk0930.accel = p_actwk->actflg.hflip == 1 ? -0x20 : 0x20;
  if (p_playerwk->xspeed >= -0x100 && p_playerwk->xspeed < 0x100) {
    p_playerwk->xspeed = p_playerwk->xspeed < 0 ? -0x100 : 0x100;
  }
  p_playerwk->xspeed = -p_playerwk->xspeed;
  p_playerwk->yspeed = -p_playerwk->yspeed;
  p_playerwk->mspeed = -p_playerwk->mspeed;
  pg_init(p_actwk, guard_pg01);
}


static void nk0930_pnch0(SKC_sprite_status* p_actwk) {
  void(*pnch0_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*) = {
    &nk0930_pl_damage,
    &nk0930_pl_damage,
    &damg0_init,
    &nk0930_pl_damage
  };

  if (p_actwk->u.obj.timer-- == 0) {
    ftwk0_init(p_actwk);
  }
  else {
    chk_nk0930_col(p_actwk, pnch0_col_tbl);
  }
}


static void pnch0_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.invulnerability_timer != 0) return;

  p_actwk->r_no = 6;
  p_actwk->patno = 222;
  p_actwk->u.obj.timer = 7;
  nk0930_pl_damage0(p_actwk, p_playerwk);
}


static void nk0930_jump0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
}


static void jump1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 10;
  p_actwk->yspeed = -0x600;
  soundset(98);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_jump1(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed < 0) {
    jump2_init(p_actwk);
  }
  else {
    chk_nk0930_col(p_actwk, jump1_col_tbl);
  }
}


static void(*jump1_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*) = {
  &nk0930_pl_damage,
  &nk0930_pl_damage,
  &nk0930_pl_damage,
  &nk0930_pl_damage
};


static void jump0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  SKC_chk_distance_result result = chk_distance(p_actwk);
  chk_nk0930_rev(p_actwk, result.right);
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.callback_ptr = &jump1_init;
  pg_init(p_actwk, jump_pg00);
}


static void nk0930_jump2(SKC_sprite_status* p_actwk) {
  void(*jump2_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*) = {
    &nk0930_pl_damage,
    &nk0930_pl_damage,
    &damg0_init,
    &nk0930_pl_damage
  };

  chk_nk0930_limit(p_actwk);
  speedset2(p_actwk);
  if (p_actwk->xspeed == 0) {
    down0_init(p_actwk);
  }
  else {
    SKC_chk_distance_result result = chk_distance(p_actwk);
    if ((unsigned short)result.xdistance >= 48 && p_actwk->actflg.hflip == result.right) {
      down0_init(p_actwk);
    }
    else {
      chk_nk0930_col(p_actwk, jump2_col_tbl);
    }
  }
}


static void jump2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  p_actwk->patno = 192;
  p_actwk->xspeed = p_actwk->actflg.hflip == 0 ? 0x400 : -0x400;
  p_actwk->yspeed = 0x80;
}


static void nk0930_down0(SKC_sprite_status* p_actwk) {
  void(*down0_col_tbl[4])(SKC_sprite_status*, SKC_sprite_status*) = {
    &damg0_init,
    &nk0930_pl_damage,
    &damg0_init,
    &nk0930_pl_damage
  };

  time_pgs(p_actwk);
  speedset(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset < 0) {
    land0_init(p_actwk, result.offset);
  }
  else {
    chk_nk0930_col(p_actwk, down0_col_tbl);
  }
}


static void down0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 14;
  p_actwk->actflg.hflip ^= 1;
  p_actwk->xspeed = 0;
  pg_init(p_actwk, down_pg00);
}


static void nk0930_land0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  SKC_chk_distance_result result = chk_distance(p_actwk);
  chk_nk0930_rev(p_actwk, result.right);
  chk_nk0930_col(p_actwk, gurd0_col_tbl);
}


static void land0_init(SKC_sprite_status* p_actwk, short yoffset) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->r_no = 16;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.callback_ptr = &ftwk0_init;
  pg_init(p_actwk, land_pg00);
}


static void nk0930_spin0(SKC_sprite_status* p_actwk) {
  if (!(g_ram.systemtimer & 0xF)) {
    soundset(60);
    pt_chgs(p_actwk);
  }
  if (p_actwk->u.obj.timer-- == 0) {
    spin1_init(p_actwk);
  }
  else if (p_actwk->u.obj.timer == 43) {
    p_actwk->u.obj.actflg0.puka_down = 0;
    set_act05(p_actwk, &nk0930_effect_set_tbl);
  }
  chk_nk0930_col(p_actwk, jump1_col_tbl);
}


static void spin0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 18;
  SKC_chk_distance_result result = chk_distance(p_actwk);
  chk_nk0930_rev(p_actwk, result.right);
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.timer = 59;
  pg_init(p_actwk, spin_pg00);
}


static void nk0930_spin1(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  chk_nk0930_limit(p_actwk);
  if (p_actwk->xspeed == 0) {
    p_actwk->actflg.hflip ^= 1;
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 4);
    ftwk0_init(p_actwk);
  }
  else {
    p_actwk->xspeed += p_actwk->u.obj.actfree.nk0930.accel;
    speedset2(p_actwk);
    chk_nk0930_col(p_actwk, jump1_col_tbl);
  }
}


static void spin1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 20;
  p_actwk->u.obj.actflg0.puka_down = 1;
  p_actwk->xspeed = p_actwk->actflg.hflip == 0 ? 0x800 : -0x800;
  p_actwk->u.obj.actfree.nk0930.accel = p_actwk->actflg.hflip == 0 ? -0x10 : 0x10;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 4);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_damg0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  chk_nk0930_limit(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      short distance = abs((g_ram.scra_h_posit >> 16) + 160 - fp16_get_integer(p_actwk->xposi));
      if (distance < 96) {
        spin0_init(p_actwk);
      }
      else {
        jump0_init(p_actwk);
      }
    }
  }
}


void damg0_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->u.obj.actflg0.puka_down = 1;
  soundset(93);
  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi);
  p_actwk->xspeed = distance < 0 ? 0x300 : -0x300;
  p_actwk->yspeed = -0x300;
  --p_actwk->colicnt;
  if (p_actwk->colicnt == 0) {
    die0_init(p_actwk);
    p_actwk->r_no = 22;
    p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
    p_actwk->patbase = knuckles_pt;
    p_actwk->patno = 141;
    pg_init(p_actwk, damage_pg00);
  }
}


static void nk0930_die0(SKC_sprite_status* p_actwk) {
  chk_nk0930_limit(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      die1_init(p_actwk, result.offset);
    }
  }
}


static void die0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 24;
  g_ram.pltime_f = 0;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 2;
  p_actwk->patbase = nk0931_pt;
  p_actwk->patno = 2;
  p_actwk->u.obj.actflg0.ko_die = 1;
  g_ram.bgm_act = 20;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &set_bgm_act;
    result.actwk_ptr->u.obj.userflag = 20;
  }
}


static void nk0930_die1(SKC_sprite_status* p_actwk) {
  time_pgs(p_actwk);
}


static void die1_init(SKC_sprite_status* p_actwk, short yoffset) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->r_no = 26;
  p_actwk->u.obj.callback_ptr = &die2_init;
  soundset(-112);
  pg_init(p_actwk, die_pg00);
  unlze_moduled(&g_vram[0xA000], DAT_004f837c);
}


static void nk0930_die2(SKC_sprite_status* p_actwk) {
  if (g_ram.systemtimer & 0x1F) return;

  soundset(89);
  if (p_actwk->u.obj.timer-- == 0) {
    wake0_init(p_actwk);
  }
}


static void die2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 28;
  p_actwk->u.obj.timer = 127;
  g_ram.scr_shake_flg = 0xFF00 | g_ram.scr_shake_flg & 0x00FF;
  set_act05(p_actwk, &nk0930_exp_set_tbl);
}


static void nk0930_wake0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  run0_init(p_actwk);
}


static void wake0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 30;
  p_actwk->patno = 6;
  p_actwk->u.obj.timer = 15;
  SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &piyo09_set_tbl);
  p_new_actwk->u.obj.userflag = 255;
}


static void nk0930_run0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  run1_init(p_actwk);
}


static void run0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 32;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 86;
  p_actwk->actflg.hflip = 0;
  p_actwk->u.obj.timer = 7;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
}


static void nk0930_run1(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  short xspeed = p_actwk->xspeed + 16;
  if ((unsigned short)xspeed < 0x400) {
    p_actwk->xspeed = xspeed;
  }
  speedset2(p_actwk);
  short xposi = (g_ram.scra_h_posit >> 16) + 384;
  if ((unsigned short)xposi < (unsigned short)fp16_get_integer(p_actwk->xposi)) {
    wait0_init(p_actwk);
  }
}


static void run1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 34;
  pg_init(p_actwk, run_pg02);
}


static void nk0930_wait0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 0)) {
    jump3_init(p_actwk);
  }
}


static void wait0_init(SKC_sprite_status* p_actwk) {
  SKC_cg_data cg_tbl = {
    0,
    {
      { eggmbl_cg, 0xA5C0 }
    }
  };

  p_actwk->r_no = 36;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 2;
  p_actwk->patbase = nk0931_pt;
  p_actwk->patno = 10;
  pg_init(p_actwk, wait_pg00);
  SET_BIT(p_actwk->sproffset, 15);
  fp16_set_integer(&p_actwk->xposi, 0x1620);
  fp16_set_integer(&p_actwk->yposi, 0x3AC);
  g_ram.DAT_08fffab8_bitfield = 0;
  g_ram.scr_shake_flg = 0;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &ev0930;
  }
  result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &embl0930;
  }
  result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &chg_scr_lim_r;
  }
  result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &chg_scr_lim_u;
  }
  g_ram.scralim_n_down = g_ram.scralim_m_down;
  result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &chg_scr_lim_d;
  }
  unlze_moduled(&g_vram[0x94E0], clen_cg);
  divdevset2(&cg_tbl);
}


static void nk0930_jump3(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      wait1_init(p_actwk, result.offset);
    }
  }
}


static void jump3_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 38;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 154;
  p_actwk->xspeed = 0xC0;
  p_actwk->yspeed = -0x600;
  soundset(98);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  jump4_init(p_actwk);
}


static void wait1_init(SKC_sprite_status* p_actwk, short yoffset) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->r_no = 40;
  p_actwk->patno = 214;
  p_actwk->u.obj.timer = 8;
}


static void nk0930_jump4(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0 && (unsigned short)fp16_get_integer(p_actwk->yposi) >= 0x339) {
    angry0_init(p_actwk);
  }
}


static void jump4_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 42;
  p_actwk->xspeed = -0xC0;
  p_actwk->yspeed = -0x500;
  soundset(98);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_angry0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    run2_init(p_actwk);
  }
  else {
    pt_chgs(p_actwk);
  }
}


static void angry0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 44;
  fp16_set_integer(&p_actwk->yposi, 0x339);
  p_actwk->u.obj.actfree.nk0930.wrt_index = 2;
  p_actwk->patbase = nk0931_pt;
  p_actwk->patno = 10;
  p_actwk->u.obj.timer = 127;
  pg_init(p_actwk, angry_pg00);
}


static void nk0930_run2(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  short xspeed = p_actwk->xspeed + 0xC;
  p_actwk->xspeed = (unsigned short)xspeed <= 0x300 ? xspeed : 0x300;
  speedset2(p_actwk);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 0x1660) {
    wait2_init(p_actwk);
  }
}


static void run2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 46;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  pg_init(p_actwk, run_pg03);
}


static void nk0930_wait2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  jump5_init(p_actwk);
}


static void wait2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 48;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 2;
  p_actwk->patbase = nk0931_pt;
  p_actwk->patno = 13;
  p_actwk->u.obj.timer = 29;
}


static void nk0930_jump5(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = {
    -0x20, 0x40, -0x20, 0x40
  };

  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (emy_col_a0(p_actwk, &g_ram.actwk[g_ram.DAT_08fffaae_obj], col_tbl)) {
    jump6_init(p_actwk, &g_ram.actwk[g_ram.DAT_08fffaae_obj]);
  }
}


static void jump5_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 50;
  SET_BIT(g_ram.DAT_08fffab8_bitfield, 1);
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 154;
  p_actwk->xspeed = 0x300;
  p_actwk->yspeed = -0x500;
  soundset(98);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_jump6(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = {
    -0x20, 0x40, -0x20, 0x40
  };

  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0 && (unsigned short)fp16_get_integer(p_actwk->yposi) >= 0x3AB) {
    run3_init(p_actwk);
  }
}


static void jump6_init(SKC_sprite_status* p_actwk, SKC_sprite_status* p_coliwk) {
  p_coliwk->u.obj.cddat.pl2push = 1;
  p_actwk->r_no = 52;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 154;
  p_actwk->xspeed = -0x200;
  p_actwk->yspeed = -0x200;
  soundset(98);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_run3(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  short xspeed = p_actwk->xspeed + 0xC;
  p_actwk->xspeed = (unsigned short)xspeed <= 0x300 ? xspeed : 0x300;
  speedset2(p_actwk);
  SKC_sprite_status* p_caos09wk = &g_ram.actwk[g_ram.DAT_08fffaba_obj];
  short distance = fp16_get_integer(p_caos09wk->xposi) - fp16_get_integer(p_actwk->xposi);
  if ((unsigned short)distance < 48) {
    jump7_init(p_actwk);
  }
}


static void run3_init(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, 0x3AB);
  p_actwk->r_no = 54;
  CLEAR_BIT(p_actwk->sproffset, 15);
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 7;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  pg_init(p_actwk, run_pg03);
}


static void nk0930_jump7(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = {
    -16, 96, 0, 16
  };

  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (emy_col_a0(p_actwk, &g_ram.actwk[g_ram.DAT_08fffaba_obj], col_tbl)) {
    cach0_init(p_actwk);
  }
}


static void jump7_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 56;
  p_actwk->yspeed = -0x600;
  soundset(98);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_cach0(SKC_sprite_status* p_actwk) {
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 4)) {
    elec0_init(p_actwk);
  }
}


static void set_cach0_ofs(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_caos09wk = &g_ram.actwk[g_ram.DAT_08fffaba_obj];
  short xposi = fp16_get_integer(p_caos09wk->xposi) - 12;
  fp16_set_integer(&p_actwk->xposi, xposi);
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_caos09wk->yposi));
}


static void cach0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 58;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 2;
  p_actwk->patbase = nk0931_pt;
  p_actwk->patno = 0;
  set_cach0_ofs(p_actwk);
}


static void nk0930_elec0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    fall0_init(p_actwk);
  }
  else {
    p_actwk->patno = !(g_ram.systemtimer & 1) ? 0 : 1;
    if (g_ram.systemtimer & 3) {
      soundset(120);
    }
    set_cach0_ofs(p_actwk);
  }
}


static void elec0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 60;
  p_actwk->u.obj.timer = 59;
  set_cach0_ofs(p_actwk);
}


static void nk0930_fall0(SKC_sprite_status* p_actwk) {
  p_actwk->patno = !(g_ram.systemtimer & 1) ? 0 : 1;
  speedsetg20(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset < 0) {
    land1_init(p_actwk, result.offset);
  }
}


static void fall0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 62;
  p_actwk->xspeed = -0x100;
  p_actwk->yspeed = -0x100;
}


static void nk0930_land1(SKC_sprite_status* p_actwk) {
  time_pgs(p_actwk);
}


static void land1_init(SKC_sprite_status* p_actwk, short yoffset) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->r_no = 64;
  SET_BIT(g_ram.DAT_08fffab8_bitfield, 5);
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.callback_ptr = &wait4_init;
  pg_init(p_actwk, land_pg01);
}


static void nk0930_wait4(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffaac != 0) {
    fall1_init(p_actwk);
  }
}


static void wait4_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 66;
}


static void nk0930_fall1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  fall2_init(p_actwk);
}


static void fall1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 68;
  p_actwk->u.obj.timer = 16;
  g_ram.pl_scr_lock_flag = 0;
  g_ram.scralim_n_down = 0x5C0;
  g_ram.scralim_m_down = 0x5C0;
  soundset(-52);
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &chg_scr_lim_d;
  }
  fall1_init__set_exp(p_actwk);
  fall1_init__set_exp(p_actwk);
}


static void fall1_init__set_exp(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &bsexp01_set_tbl);
  if (p_new_actwk != 0) {
    p_new_actwk->u.obj.userflag = 20;
    fp16_set_integer(&p_new_actwk->xposi, 0x1880);
    fp16_set_integer(&p_new_actwk->yposi, 0x3D0);
  }
}


static void nk0930_fall2(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset < 0) {
    land2_init(p_actwk, result.offset);
  }
}


static void fall2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 70;
  p_actwk->patno = 2;
  g_ram.DAT_08ffeec4 = 0x00FF | g_ram.DAT_08ffeec4 & 0xFF00;
  g_ram.scr_shake_flg = 20;
  set_act05(p_actwk, &door09_set_tbl);
}


static void nk0930_land2(SKC_sprite_status* p_actwk) {
  time_pgs(p_actwk);
}


static void land2_init(SKC_sprite_status* p_actwk, short yoffset) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->r_no = 72;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.callback_ptr = &wake1_init;
  pg_init(p_actwk, die_pg00);
}


static void nk0930_wake1(SKC_sprite_status* p_actwk) {
  time_pgs(p_actwk);
}


static void wake1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 74;
  p_actwk->u.obj.callback_ptr = &wake2_init;
  pg_init(p_actwk, wake_pg00);
  set_act05(p_actwk, &piyo09_set_tbl);
}


static void nk0930_wake2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  run4_init(p_actwk);
}


static void wake2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 76;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 86;
  p_actwk->u.obj.timer = 7;
}


static void nk0930_run4(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  p_actwk->xspeed -= 0xC;
  speedset2(p_actwk);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) <= 0x1810) {
    comn0_init(p_actwk);
  }
}


static void run4_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 78;
  p_actwk->actflg.hflip = 1;
  p_actwk->xspeed = 0;
  pg_init(p_actwk, run_pg03);
}


static void nk0930_comn0(SKC_sprite_status* p_actwk) {
  time_pgs(p_actwk);
}


static void comn0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 80;
  p_actwk->actflg.hflip = 0;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 2;
  p_actwk->patbase = nk0931_pt;
  p_actwk->patno = 14;
  p_actwk->u.obj.callback_ptr = &pnch1_init;
  pg_init(p_actwk, comeon_pg00);
}


static void nk0930_pnch1(SKC_sprite_status* p_actwk) {
  int ret = time_pgs(p_actwk);
  if (ret != 0 && p_actwk->patcnt == 6) {
    g_ram.DAT_08fffaa2 = 0xFF;
    soundset(89);
  }
}


static void pnch1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 82;
  p_actwk->actflg.hflip = 1;
  p_actwk->u.obj.callback_ptr = &run5_init;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 86;
  pg_init(p_actwk, panch_pg00);
}


static void nk0930_run5(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  p_actwk->xspeed -= 0xC;
  speedset2(p_actwk);
  short xposi = (g_ram.scra_h_posit >> 16) - 64;
  if ((unsigned short)xposi >= (unsigned short)fp16_get_integer(p_actwk->xposi)) {
    wait5_init(p_actwk);
  }
}


static void run5_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 84;
  p_actwk->actflg.hflip = 1;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 7;
  p_actwk->xspeed = 0;
  pg_init(p_actwk, run_pg03);
}


static void nk0930_wait5(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 6)) {
    jump8_init(p_actwk);
  }
}


static void wait5_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 86;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 4;
  p_actwk->patbase = nk0a00_pt;
  p_actwk->patno = 0;
  p_actwk->actflg.hflip = 0;
  fp16_set_integer(&p_actwk->xposi, 0x161C);
  fp16_set_integer(&p_actwk->yposi, 0x62C);
  g_ram.scralim_m_left = 0x1520;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &chg_scr_lim_l;
  }
  pg_init(p_actwk, tired_pg01);
}


static void nk0930_jump8(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  speedset(p_actwk);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) <= 0x15C0) {
    land3_init(p_actwk);
  }
}


static void jump8_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 88;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 154;
  p_actwk->xspeed = -0x1E0;
  p_actwk->yspeed = -0x600;
  soundset(98);
  pg_init(p_actwk, ball_pg01);
}


static void nk0930_land3(SKC_sprite_status* p_actwk) {
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 7)) {
    ball0_init(p_actwk);
  }
  else {
    time_pg(p_actwk);
  }
}


static void land3_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 90;
  fp16_set_integer(&p_actwk->xposi, 0x15C0);
  fp16_set_integer(&p_actwk->yposi, 0x600);
  p_actwk->u.obj.actfree.nk0930.wrt_index = 4;
  p_actwk->patbase = nk0a00_pt;
  p_actwk->patno = 0;
  p_actwk->actflg.hflip = 0;
  pg_init(p_actwk, tired_pg01);
}


static void nk0930_ball0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
}


static void ball0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 92;
  p_actwk->u.obj.actfree.nk0930.wrt_index = 0;
  p_actwk->patbase = knuckles_pt;
  p_actwk->patno = 154;
  pg_init(p_actwk, ball_pg01);
}


void nk0930_effect(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &nk0930_effect_init_tbl);
  nk0930_effect_wait0(p_actwk);
}


static void nk0930_effect_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.puka_down == 1) {
    nuckle_fout(p_actwk);
  }
  else {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_parentwk->xposi));
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_parentwk->yposi));
    p_actwk->actflg.hflip = p_parentwk->actflg.hflip;
    pt_chg0(p_actwk, effect_pg00);
    nk0930_effect_wrt(p_actwk);
    actionsub(p_actwk);
  }
}


static void ev0930(SKC_sprite_status* p_actwk) {
  if (fp16_get_integer(g_ram.actwk[0].xposi) < 0x14D0) return;

  p_actwk->r_ptr = &ev0930_wait0;
  pl_spd_clr(&g_ram.actwk[0]);
  g_ram.pl_input_lock_flag = 0xFF;
  g_ram.swdata1_auto = 0;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &fox_auto;
  }
  g_ram.scralim_n_down = 0x300;
}


static void ev0930_wait0(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.cddat.jump == 1) return;

  g_ram.swdata1_auto = PAD_R << 8 | PAD_R;
  if (fp16_get_integer(g_ram.actwk[0].xposi) >= 0x15A8) {
    p_actwk->r_ptr = &ev0930_wait1;
    g_ram.pl_scr_lock_flag = 0xFF;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &set_bgm_act;
      result.actwk_ptr->u.obj.userflag = 24;
    }
    set_pl_stop(&g_ram.actwk[0]);
  }
}


static void set_pl_stop(SKC_sprite_status* p_playerwk) {
  g_ram.pl_input_lock_flag = 0;
  p_playerwk->u.play.control_bitfield = 0x83;
  p_playerwk->patno = p_playerwk->u.play.character != SONIC ? 196 : 176;
  p_playerwk->mstno = 7;
  g_ram.swdata1_auto = 0;
  pl_spd_clr(p_playerwk);
  wrt_player();
}


static void ev0930_wait1(SKC_sprite_status* p_actwk) {
  g_ram.scra_h_posit += 0x20000;
  if (g_ram.scra_h_posit >> 16 >= 0x1580) {
    p_actwk->r_ptr = &ev0930_wait2;
    SET_BIT(g_ram.DAT_08fffab8_bitfield, 0);
  }
}


static void ev0930_wait2(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 1)) return;

  p_actwk->r_ptr = &ev0930_move0;
  g_ram.actwk[0].u.play.control_bitfield = 0;
  g_ram.pl_input_lock_flag = 0xFF;
  g_ram.swdata1_auto = PAD_R << 8 | PAD_R;
}


static void ev0930_move0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  short speed = p_playerwk->xspeed;
  if ((unsigned short)speed > 0x300) {
    speed = 0x300;
  }
  p_playerwk->xspeed = speed;
  p_playerwk->mspeed = speed;
  g_ram.scra_h_posit += speed * 0x100;
  if (0x17D0 <= g_ram.scra_h_posit >> 16) {
    p_actwk->r_ptr = &ev0930_wait3;
    g_ram.scra_h_posit = 0x17D0 << 16 | g_ram.scra_h_posit & 0x0000FFFF;
    g_ram.scralim_left = 0x17D0;
    g_ram.scralim_right = 0x17D0;
    g_ram.scralim_up = g_ram.scralim_down;
    g_ram.pl_input_lock_flag = 0;
    g_ram.pl2_input_lock_flag = 0;
  }
}


static void ev0930_wait3(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 5)) return;

  p_actwk->r_ptr = &ev0930_move1;
  g_ram.pl_input_lock_flag = 0xFF;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &fox_auto;
  }
}


static void ev0930_move1(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.cddat.jump == 1) return;

  p_actwk->r_ptr = &ev0930_move2;
}


static void ev0930_move2(SKC_sprite_status* p_actwk) {
  short distance = fp16_get_integer(g_ram.actwk[0].xposi) - 0x1892;
  g_ram.swdata1_auto = distance < 0 ? PAD_R << 8 | PAD_R : PAD_L << 8 | PAD_L;
  if (abs(distance) <= 4) {
    p_actwk->r_ptr = &ev0930_wait4;
    p_actwk->u.obj.timer = 63;
    g_ram.DAT_08fffaac = 0xFF;
    g_ram.swdata1_auto = 0;
    pl_spd_clr(&g_ram.actwk[0]);
    wrt_player();
  }
}


static void ev0930_wait4(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_ptr = &ev0930_wait5;
  g_ram.actwk[0].actflg.hflip = 1;
  g_ram.actwk[0].u.play.cddat.left = 1;
}


static void ev0930_wait5(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].yposi) < 0x580) return;
  if (g_ram.actwk[0].u.play.cddat.jump == 1) return;

  p_actwk->r_ptr = &ev0930_wait6;
  g_ram.pl_input_lock_flag = 0;
  g_ram.scralim_up = 0x5C0;
}


static void ev0930_wait6(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) >= 0x1660) return;

  p_actwk->r_ptr = &ev0930_wait7;
  g_ram.pl2_input_lock_flag = 0;
}


static void ev0930_wait7(SKC_sprite_status* p_actwk) {
}


static void embl0930(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &embl0930_init_tbl);
  g_ram.DAT_08fffaae_obj = p_actwk - g_ram.actwk;
  p_actwk->r_ptr = &embl0930_wait0;
  p_actwk->actflg.hflip = 1;
  fp16_set_integer(&p_actwk->xposi, 0x1640);
  fp16_set_integer(&p_actwk->yposi, 0x2D0);
  set_act00(p_actwk, &mbl_eggman4_set_tbl);
  set_act00(p_actwk, &clen0930_set_tbl);
  embl0930_wait0(p_actwk);
}


static void embl0930_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.unused2 == 1) {
    p_actwk->r_ptr = &embl0930_move0;
    p_actwk->xspeed = 0x100;
    p_actwk->yspeed = 0x180;
    p_actwk->u.obj.timer = 64;
    p_actwk->u.obj.callback_ptr = &embl0930_wait1_init;
  }
  actionsub(p_actwk);
}


static void embl0930_move0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  dec_timer(p_actwk);
  actionsub(p_actwk);
}


static void embl0930_wait1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &embl0930_wait1;
  p_actwk->xspeed = 0;
  bs00m0_puka_init(p_actwk);
  set_act00(p_actwk, &embl_jet_set_tbl);
}


static void embl0930_wait1(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  if (p_actwk->u.obj.cddat.pl2push == 0) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 2);
  }
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 0x1890) {
    p_actwk->r_ptr = &embl0930_wait2;
    p_actwk->u.obj.actflg0.ko_die = 1;
    p_actwk->xspeed = 0;
    p_actwk->colino = 0x0F;
    p_actwk->colicnt = 255;
    set_act02(p_actwk, &embl0930_handb_set_tbl);
  }
  chk_embl0930_damage0(p_actwk);
  actionsub(p_actwk);
}


static void embl0930_wait2(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 2) && !BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 3)) {
    p_actwk->r_ptr = &embl0930_wait3;
    SET_BIT(g_ram.DAT_08fffab8_bitfield, 4);
  }
  puka_puka(p_actwk);
  speedset2(p_actwk);
  chk_embl0930_damage1(p_actwk);
  chk_actsubc(p_actwk);
}


static void embl0930_wait3(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 5)) {
    p_actwk->r_ptr = &embl0930_move1;
    p_actwk->xspeed = 0x190;
    p_actwk->u.obj.actflg0.ko_die = 0;
    set_act00(p_actwk, &embl_jet_set_tbl);
  }
  chk_embl0930_damage1(p_actwk);
  chk_actsubc(p_actwk);
}


static void embl0930_move1(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  short xposi = (g_ram.scra_h_posit >> 16) + 512;
  if ((unsigned short)xposi >= (unsigned short)fp16_get_integer(p_actwk->xposi)) {
    chk_embl0930_damage1(p_actwk);
    chk_actsubc(p_actwk);
  }
  else {
    p_actwk->u.obj.actflg0.ko_die = 1;
    p_actwk->u.obj.actflg0.end = 1;
    frameout(&g_ram.actwk[g_ram.DAT_08fffaba_obj]);
    g_ram.DAT_08fffaba_obj = 0;
    g_ram.clchgtim = 0;
    unlze_moduled(&g_vram[0xA5C0], DAT_004f9184);
    set_emy_fout0(p_actwk);
  }
}


void clen0930(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &clen0930_init_tbl);
  p_actwk->r_ptr = &clen0930_wait0;
  set_act00(p_actwk, &clenparts_set_tbl);
}


static void clen0930_wait0(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 0)) {
    ko_offset1(p_actwk);
    chk_oya_die0(p_actwk);
  }
  else {
    p_actwk->r_ptr = &clen0930_wait1;
    p_actwk->u.obj.actfree.clen0930.yoffset_init = p_actwk->u.obj.oya_offset.y;
    clen0930_wait1(p_actwk);
  }
}


static void clen0930_wait1(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffaba_obj != 0) {
    SKC_sprite_status* p_caos09wk = &g_ram.actwk[g_ram.DAT_08fffaba_obj];
    short yposi = fp16_get_integer(p_caos09wk->yposi) - 24;
    if ((unsigned short)yposi <= (unsigned short)fp16_get_integer(p_actwk->yposi)) {
      clen0930_wait1__catch(p_actwk);
      return;
    }
    short yspeed = p_actwk->yspeed + 0x80;
    if (yspeed >= 0) {
      p_actwk->yspeed = yspeed;
    }
    p_actwk->u.obj.oya_offset.y = p_actwk->u.obj.actfree.clen0930.yoffset_init + fp8_get_integer(p_actwk->yspeed);
  }
  ko_offset1(p_actwk);
  chk_oya_die0(p_actwk);
}


static void clen0930_wait1__catch(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &clen0930_cach0;
  p_actwk->patno = 2;
  g_ram.scr_shake_flg = 20;
  soundset(-52);
  set_act05(p_actwk, &smok0930_set_tbl);
  set_act05(p_actwk, &caos09_frag_set_tbl);
  clen0930_cach0(p_actwk);
}


static void clen0930_cach0(SKC_sprite_status* p_actwk) {
  short yspeed = p_actwk->yspeed - 0x80;
  if (yspeed < 0) {
    p_actwk->r_ptr = &clen0930_cach1;
    yspeed = 0;
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_parentwk->u.obj.actflg0.unused2 = 1;
    SKC_sprite_status* p_caos09wk = &g_ram.actwk[g_ram.DAT_08fffaba_obj];
    SET_BIT(p_caos09wk->sproffset, 15);
  }
  p_actwk->yspeed = yspeed;
  p_actwk->u.obj.oya_offset.y = p_actwk->u.obj.actfree.clen0930.yoffset_init + fp8_get_integer(p_actwk->yspeed);
  clen0930_cach1(p_actwk);
}


static void clen0930_cach1(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  if (g_ram.DAT_08fffaba_obj != 0) {
    SKC_sprite_status* p_caos09wk = &g_ram.actwk[g_ram.DAT_08fffaba_obj];
    fp16_set_integer(&p_caos09wk->xposi, fp16_get_integer(p_actwk->xposi));
    short yposi = fp16_get_integer(p_actwk->yposi) + -(short)g_ram.DAT_08fffabd;
    fp16_set_integer(&p_caos09wk->yposi, yposi);
  }
  chk_oya_die0(p_actwk);
}


void clenparts(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &clenparts_init_tbl);
  p_actwk->r_ptr = &clenparts_wait0;
  clenparts_wait0(p_actwk);
}


static void clenparts_wait0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->patno = p_parentwk->patno + 1;
  chk_oya_die0(p_actwk);
}


void clenchain(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &clenchain_init_tbl);
  p_actwk->r_ptr = &clenchain_wait0;
  clenchain_wait0(p_actwk);
}


static void clenchain_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->patno = fp8_get_integer(p_actwk->yspeed) / 16 + 4;
  ko_offset0(p_actwk);
  chk_oya_die0(p_actwk);
}


void smok0930(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &smok0930_init_tbl);
  p_actwk->r_ptr = &smok0930_wait0;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 48);
  p_actwk->u.obj.timer = p_actwk->u.obj.userflag * 2;
  smok0930_wait0(p_actwk);
}


static void smok0930_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_ptr = &smok0930_pchg0;
  unsigned long number = random();
  short xoffset = (short)(number & 0x3F) - 32;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
  short yoffset = (short)((number >> 16) & 0x3F) - 32;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->u.obj.callback_ptr = &smok0930_pchg1_init;
  smok0930_pchg0(p_actwk);
}


static void smok0930_pchg0(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, smok0930_pg00);
  actionsub(p_actwk);
}


static void smok0930_pchg1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &smok0930_pchg1;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  p_actwk->patcnt = 0;
  p_actwk->patno = 0;
}


static void smok0930_pchg1(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, smok0930_pg01);
  p_actwk->yspeed -= 0x80;
  speedset2(p_actwk);
  actionsub(p_actwk);
}


void caos09_frag(SKC_sprite_status* p_actwk) {
  unsigned char pt_tbl[5] = {
    28, 27, 26, 25, 24
  };
  struct {
    signed char x;
    signed char y;
  }
  ofs_tbl[5] = {
    {  4, 44 },
    { -2, 42 },
    {  6, 34 },
    { -8, 36 },
    { -2, 28 }
  };
  unsigned short tim_tbl[5] = {
    32, 48, 64, 80, 96
  };

  enemy_init0(p_actwk, &caos09_frag_init_tbl);
  p_actwk->r_ptr = &caos09_frag_wait0;
  p_actwk->u.obj.oya_offset.x = ofs_tbl[p_actwk->u.obj.userflag / 2].x;
  p_actwk->u.obj.oya_offset.y = ofs_tbl[p_actwk->u.obj.userflag / 2].y;
  p_actwk->u.obj.timer = tim_tbl[p_actwk->u.obj.userflag / 2];
  p_actwk->patno = pt_tbl[p_actwk->u.obj.userflag / 2];
  p_actwk->u.obj.callback_ptr = &frag_fall0_init;
}


static void caos09_frag_wait0(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  dec_timer(p_actwk);
  chk_emy_fout3(p_actwk);
}


static void frag_fall0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &caos09_frag_fall0;
  SET_BIT(p_actwk->sproffset, 15);
}


static void caos09_frag_fall0(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  chk_emy_fout3(p_actwk);
}


void nk0930_exp(SKC_sprite_status* p_actwk) {
  struct {
    signed char x;
    signed char y;
  }
  ofs_tbl[16] = {
    {  -16,  -88 },
    {  -24,  -48 },
    {   -8,  -16 },
    {  -16, -112 },
    {  -32,  -96 },
    {   -8,  -56 },
    {  -32,  -16 },
    {  -32,  -64 },
    {  -64,  -88 },
    {  -48,  -48 },
    {  -64,   -8 },
    {  -72,  -56 },
    {  -56,  -32 },
    {  -96,  -64 },
    {  -88,  -32 },
    { -112,   -8 }
  };

  p_actwk->r_ptr = &nk0930_exp_wait0;
  short xposi = (g_ram.scra_h_posit >> 16) + 320 + ofs_tbl[p_actwk->u.obj.userflag / 2].x;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (g_ram.scra_v_posit >> 16) + 192 + ofs_tbl[p_actwk->u.obj.userflag / 2].y;
  fp16_set_integer(&p_actwk->yposi, yposi);
  p_actwk->u.obj.timer = p_actwk->u.obj.userflag * 4;
}


static void nk0930_exp_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_ptr = &bakuhatu;
  p_actwk->r_no = 2;
  p_actwk->r_ptr(p_actwk);
  CLEAR_BIT(p_actwk->sproffset, 15);
}


void embl0930_handb(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &embl0930_handb_init_tbl);
  p_actwk->r_ptr = &embl0930_handb_wait0;
  p_actwk->u.obj.timer = 240;
  set_act07(p_actwk, p_actwk->u.obj.userflag == 0 ? &embl0930_lhand_set_tbl : &embl0930_rhand_set_tbl);
}


static void embl0930_handb_wait0(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->u.obj.actflg0.unused7 = 1;
  }
  ko_offset1(p_actwk);
  chk_oya_die0(p_actwk);
}


void embl0930_rhand(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.fura_right = 1;
  p_actwk->u.obj.radius.angle = 64;
  p_actwk->u.obj.actfree.embl_hand.speed = 1;
  embl0930_lhand0(p_actwk);
}


void embl0930_lhand(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.radius.angle = 192;
  p_actwk->u.obj.actfree.embl_hand.speed = -1;
  embl0930_lhand0(p_actwk);
}


static void embl0930_lhand0(SKC_sprite_status* p_actwk) {
  char dir_tbl[20] = {
    208, 212, 216, 224, 232, 244, 248, 252, 0, 64, 48, 40, 32, 24, 16, 8, 240, 232, 224, 192
  };

  enemy_init2(p_actwk, &embl0930_lhand_init_tbl);
  p_actwk->r_ptr = &embl0930_lhand_wait0;
  p_actwk->direc.b.b0 = p_actwk->u.obj.radius.angle;
  unsigned char index = p_actwk->u.obj.userflag / 2 + (p_actwk->u.obj.actflg0.fura_right == 1 ? 10 : 0);
  p_actwk->u.obj.actfree.embl_hand.dir = dir_tbl[index];
  if (p_actwk->u.obj.userflag == 18) {
    p_actwk->u.obj.actflg0.unused2 = 1;
  }
  p_actwk->u.obj.actfree.embl_hand.speed_rev_timer_init = (p_actwk->u.obj.userflag + 16) * 2;
  short timer = -((short)(p_actwk->u.obj.userflag * 4) - 72);
  p_actwk->u.obj.timer = timer;
  p_actwk->u.obj.actfree.embl_hand.timer_init = timer;
}


static void embl0930_lhand_wait0(SKC_sprite_status* p_actwk) {
  if (--p_actwk->u.obj.timer > 0) {
    embl_hand_ura(p_actwk);
    circle_radius(p_actwk);
  }
  else {
    p_actwk->r_ptr = &embl0930_lhand_move0;
    embl0930_lhand_move0(p_actwk);
  }
}


static void embl0930_lhand_move0(SKC_sprite_status* p_actwk) {
  unsigned short unknown = p_actwk->u.obj.actfree.embl_hand.unknown3a + 0x20;
  if (unknown >= 0x800 && (p_actwk->u.obj.actflg0.unused2 == 0 || unknown >= 0xC00)) {
    p_actwk->r_ptr = &embl0930_lhand_move1;
    p_actwk->u.obj.timer = p_actwk->u.obj.actfree.embl_hand.timer_init;
  }
  p_actwk->u.obj.actfree.embl_hand.unknown3a = unknown;
  embl_hand_ura(p_actwk);
  circle_radius(p_actwk);
  if (p_actwk->u.obj.actflg0.unused2 == 1) {
    chk_top_pt(p_actwk);
  }
  chk_oya_die0(p_actwk);
}


static void embl0930_lhand_move1(SKC_sprite_status* p_actwk) {
  embl_hand_ura(p_actwk);
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_childwk->u.obj.actflg0.unused7 == 1) {
    if (p_actwk->u.obj.timer-- == 0) {
      p_actwk->r_ptr = &embl0930_lhand_move2;
    }
  }
}


static void embl0930_lhand_move10(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.unused2 == 0) {
    circle_move(p_actwk, 5);
    chk_oya_die0(p_actwk);
  }
  else {
    chk_top_pt(p_actwk);
    circle_movet(p_actwk, sin0c_tbl);
    chk_oya_die0(p_actwk);
  }
}


static void embl0930_lhand_move2(SKC_sprite_status* p_actwk) {
  short wk = (short)p_actwk->u.obj.actfree.embl_hand.dir - (short)p_actwk->u.obj.radius.angle;
  unsigned char angle = (unsigned short)wk & 0xFF;
  bool gt = p_actwk->u.obj.actfree.embl_hand.dir > p_actwk->u.obj.radius.angle;
  if (gt) {
    angle = 256 - angle;
  }
  if (angle >= 4) {
    p_actwk->u.obj.radius.angle += !gt ? 4 : -4;
    p_actwk->u.obj.radius.angle &= 0xFF;
  }
  else {
    p_actwk->r_ptr = &embl0930_lhand_move3;
    if (p_actwk->u.obj.userflag == 0) {
      SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
      SET_BIT(g_ram.DAT_08fffab8_bitfield, p_childwk->u.obj.userflag == 0 ? 2 : 3);
    }
  }
  embl0930_lhand_move10(p_actwk);
}


static void embl0930_lhand_move3(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 4)) {
    p_actwk->r_ptr = &embl0930_lhand_move4;
    p_actwk->u.obj.timer = 59;
  }
  embl0930_lhand_move10(p_actwk);
}


static void embl0930_lhand_move4(SKC_sprite_status* p_actwk) {
  unsigned char pt_tbl[4] = {
    21, 28, 25, 27
  };

  if (p_actwk->u.obj.actflg0.unused2 == 0) {
    circle_move(p_actwk, 5);
  }
  else {
    unsigned char index = 0;
    SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
    if (p_childwk->u.obj.userflag != 0) {
      index += 2;
    }
    if (g_ram.systemtimer & 1) {
      ++index;
    }
    p_actwk->patno = pt_tbl[index];
    circle_movet(p_actwk, sin0c_tbl);
  }
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &embl0930_lhand_wait1;
    p_actwk->u.obj.timer = p_actwk->u.obj.actfree.embl_hand.timer_init;
  }
  chk_oya_die0(p_actwk);
}


static void embl0930_lhand_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &embl0930_lhand_move5;
  }
  embl0930_lhand_move10(p_actwk);
}


static void embl0930_lhand_move5(SKC_sprite_status* p_actwk) {
  bool gt = p_actwk->direc.b.b0 > p_actwk->u.obj.radius.angle;
  unsigned char angle = (unsigned short)((short)p_actwk->direc.b.b0 - (short)p_actwk->u.obj.radius.angle) & 0xFF;
  if (gt) {
    angle = 256 - angle;
  }
  if (angle >= 2) {
    p_actwk->u.obj.radius.angle += !gt ? 2 : -2;
  }
  else {
    p_actwk->r_ptr = &embl0930_lhand_move6;
    p_actwk->u.obj.actfree.embl_hand.speed_rev_timer = 0;
    p_actwk->u.obj.actfree.embl_hand.speed = p_actwk->u.obj.actflg0.fura_right == 1 ? 1 : -1;
  }
  embl0930_lhand_move10(p_actwk);
}


static void embl0930_lhand_move6(SKC_sprite_status* p_actwk) {
  embl_hand_ura(p_actwk);
  embl0930_lhand_move10(p_actwk);
}


void door09(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &door09_init_tbl);
  p_actwk->r_ptr = &door09_wait0;
  fp16_set_integer(&p_actwk->xposi, 0x17F0);
  fp16_set_integer(&p_actwk->yposi, 0x660);
  door09_wait0(p_actwk);
}


static void door09_wait0(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = {
    -24, 48, -32, 64
  };

  SKC_hitchk_data data = { 27, 32, 32, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
  if (g_ram.DAT_08fffaa2 != 0) {
    set_act05(p_actwk, &door09_break_set_tbl);
    set_emy_fout0(p_actwk);
  }
  actionsub(p_actwk);
}


void door09_break(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &door09_break_init_tbl);
  p_actwk->r_ptr = &door09_break_wait0;
  p_actwk->actflg.onscreen = 1;
  door09_break_init(p_actwk);
}


static void door09_break_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 1) {
    speedsetg20(p_actwk);
    actionsub(p_actwk);
  }
  else {
    chk_ride_flg(p_actwk);
    frameout(p_actwk);
  }
}


void piyo09(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &piyo09_init_tbl);
  p_actwk->r_ptr = &piyo09_wait0;
  p_actwk->u.obj.timer = 99;
  if (p_actwk->u.obj.userflag != 0) {
    p_actwk->r_ptr = &tim_act;
  }
  piyo09_wait1(p_actwk);
}


static void piyo09_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) {
    pt_chg0(p_actwk, piyo09_pg00);
    actionsub(p_actwk);
  }
  else {
    p_actwk->r_ptr = &tim_act;
    p_actwk->patno = 0;
    p_actwk->u.obj.timer = 63;
    p_actwk->u.obj.callback_ptr = &piyo09_wait1;
  }
}


static void piyo09_wait1(SKC_sprite_status* p_actwk) {
  piyo09_fout0_init(p_actwk);
}


static void piyo09_fout0_init(SKC_sprite_status* p_actwk) {
  p_actwk->patno = 5;
  p_actwk->u.obj.timer = 11;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
}


void cchg09(SKC_sprite_status* p_actwk) {
  unsigned short (*cor_tbl[2])[48] = {
    &hiddenpalace_color,
    &cor0942_dat
  };

  unsigned short prev_index = p_actwk->u.obj.actfree.cchg09.tbl_index;
  unsigned char new_index = g_ram.scra_h_posit >> 16 < 0x460 ? 0 : 1;
  p_actwk->u.obj.actfree.cchg09.tbl_index = new_index;
  if (new_index != prev_index) {
    memcpy(&g_ram.colorwk[16], cor_tbl[new_index], sizeof(unsigned short) * 48);
  }
}


static void iwa091_pg(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- > 0) return;

  p_actwk->pattim = 4;
  ++p_actwk->patcnt;
  p_actwk->actflg.hflip = BIT_IS_SET(p_actwk->patcnt, 0);
  p_actwk->actflg.vflip = BIT_IS_SET(p_actwk->patcnt, 1);
}


static void chk_iwa091_col(SKC_sprite_status* p_actwk) {
  bool plbit = p_actwk->u.obj.actflg0.puka_down;
  bool pl2bit = p_actwk->u.obj.actflg0.unused1;
  chk_iwa091_col__chk_col(p_actwk, &g_ram.actwk[0], &plbit, &p_actwk->u.obj.actfree.iwa091.plangle, 141);
  chk_iwa091_col__chk_col(p_actwk, &g_ram.actwk[1], &pl2bit, &p_actwk->u.obj.actfree.iwa091.pl2angle, 138);
  chk_iwa091_col__chk_catch(p_actwk, &g_ram.actwk[0], &plbit, &p_actwk->u.obj.actfree.iwa091.plangle);
  chk_iwa091_col__chk_catch(p_actwk, &g_ram.actwk[0], &pl2bit, &p_actwk->u.obj.actfree.iwa091.pl2angle);
  p_actwk->u.obj.actflg0.puka_down = plbit;
  p_actwk->u.obj.actflg0.unused1 = pl2bit;
}


static void chk_iwa091_col__chk_catch(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plbit, unsigned char* p_plangle) {
  if (!*p_plbit) return;

  if (p_playerwk->pattim-- == 0) {
    p_playerwk->pattim = 8;
    unsigned char patcnt = p_playerwk->patcnt;
    ++p_playerwk->patcnt;
    p_playerwk->actflg.hflip = BIT_IS_SET(patcnt, 0);
    p_playerwk->actflg.vflip = BIT_IS_SET(patcnt, 1);
  }
  unsigned char angle = *p_plangle;
  *p_plangle += 2;
  short sin, cos;
  sinset(angle, &sin, &cos);
  short xposi = fp16_get_integer(p_playerwk->xposi) + sin / 8;
  fp16_set_integer(&p_playerwk->xposi, xposi);
  short yposi = fp16_get_integer(p_playerwk->yposi) + cos / 8;
  fp16_set_integer(&p_playerwk->yposi, yposi);
}


static void chk_iwa091_col__chk_col(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plbit, unsigned char* p_plangle, unsigned char patno) {
  short col_tbl[4] = {
    -32, 64, -32, 64
  };

  if (*p_plbit) return;
  if (!emy_col_a1(p_actwk, p_playerwk, col_tbl)) return;

  *p_plbit = true;
  g_ram.pl_scr_lock_flag = 0;
  g_ram.pltime_f = 0;
  p_playerwk->u.play.control_bitfield = 0x83;
  p_playerwk->patno = patno;
  p_playerwk->mstno = 0;
  p_playerwk->pattim = 0;
  p_playerwk->patcnt = 0;
  wrt_player0(p_playerwk);
  *p_plangle = chk_pl_angle(p_actwk, p_playerwk);
}


static void chk_nk0930_rev(SKC_sprite_status* p_actwk, bool right) {
  p_actwk->actflg.hflip = !right;
}


static void nk0930_pl_damage(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.invulnerability_timer != 0) return;

  nk0930_pl_damage0(p_actwk, p_playerwk);
}


static void nk0930_pl_damage0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.powerdat.muteki == 1) return;

  set_pl_damage(p_actwk, p_playerwk);
}


static void chk_nk0930_col(SKC_sprite_status* p_actwk, void(*p_handlers[4])(SKC_sprite_status*, SKC_sprite_status*)) {
  short nk0930_col_tbl0[4] = {
    -24, 48, -24, 48
  };

  SKC_chk_emy_colt_result result = chk_emy_colt(p_actwk, nk0930_col_tbl0);
  if (result.pl) {
    chk_nk0930_col__sub(p_actwk, &g_ram.actwk[0], p_handlers);
  }
  if (result.pl2) {
    chk_nk0930_col__sub(p_actwk, &g_ram.actwk[1], p_handlers);
  }
}


static void chk_nk0930_col__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, void(*p_handlers[4])(SKC_sprite_status*, SKC_sprite_status*)) {
  if (p_actwk->u.obj.actflg0.ko_die == 1) return;

  bool left = (unsigned short)fp16_get_integer(p_playerwk->xposi) < (unsigned short)fp16_get_integer(p_actwk->xposi);
  short distance = abs(fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi));
  if (left == p_playerwk->actflg.hflip && distance < 16) { // front
    if (p_playerwk->mstno != 2 && p_playerwk->u.play.powerdat.muteki == 1) {
      damg0_init(p_actwk, p_playerwk);
    }
    else {
      p_handlers[0](p_actwk, p_playerwk);
      // p_handlers[1](p_actwk, p_playerwk);
    }
  }
  else { // behind
    if (p_playerwk->mstno != 2 && p_playerwk->u.play.powerdat.muteki == 1) {
      damg0_init(p_actwk, p_playerwk);
    }
    else {
      p_handlers[2](p_actwk, p_playerwk);
      // p_handlers[3](p_actwk, p_playerwk);
    }
  }
}


static void chk_nk0930_limit(SKC_sprite_status* p_actwk) {
  if (p_actwk->xspeed == 0) return;

  if (p_actwk->xspeed >= 0) { // chk_r
    short xposi = (g_ram.scra_h_posit >> 16) + 304;
    if ((unsigned short)xposi <= (unsigned short)fp16_get_integer(p_actwk->xposi)) {
      p_actwk->xspeed = 0;
    }
  }
  else { // chk_l
    short xposi = (g_ram.scra_h_posit >> 16) + 16;
    if ((unsigned short)xposi >= (unsigned short)fp16_get_integer(p_actwk->xposi)) {
      p_actwk->xspeed = 0;
    }
  }
}


void nk0930_wrt(SKC_sprite_status* p_actwk) {
  if (p_actwk->patno == p_actwk->u.obj.wrt.prev_patno) return;

  p_actwk->u.obj.wrt.prev_patno = p_actwk->patno;
  unsigned char* p_wrtpat = nkmiles_wrtpat_tbl[p_actwk->patno];
  unsigned short cnt = p_wrtpat[0] << 8 | p_wrtpat[1];
  p_wrtpat += 2;
  unsigned short vram_adr = 0x9B40;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = p_wrtpat[0] << 8 | p_wrtpat[1];
    unsigned char* p_source = &nkmiles_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


static void nk0930_effect_wrt(SKC_sprite_status* p_actwk) {
  if (p_actwk->patno == p_actwk->u.obj.wrt.prev_patno) return;

  p_actwk->u.obj.wrt.prev_patno = p_actwk->patno;
  unsigned char* p_wrtpat = effect_wrtpat_tbl[p_actwk->patno];
  unsigned short cnt = p_wrtpat[0] << 8 | p_wrtpat[1];
  p_wrtpat += 2;
  unsigned short vram_adr = 0xA000;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = p_wrtpat[0] << 8 | p_wrtpat[1];
    unsigned char* p_source = &effect_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


static void door09_break_init(SKC_sprite_status* p_actwk) {
  struct {
    signed char x;
    signed char y;
  }
  ofs_tbl[32] = {
    {   8,  -8 },
    {   8,   0 },
    {   8, -16 },
    {   8,   8 },
    {   8, -24 },
    {   8,  16 },
    {   8, -32 },
    {   8,  24 },
    {   0,  -8 },
    {   0,   0 },
    {   0, -16 },
    {   0,   8 },
    {   0, -24 },
    {   0,  16 },
    {   0, -32 },
    {   0,  24 },
    {  -8,  -8 },
    {  -8,   0 },
    {  -8, -16 },
    {  -8,   8 },
    {  -8, -24 },
    {  -8,  16 },
    {  -8, -32 },
    {  -8,  24 },
    { -16,  -8 },
    { -16,   0 },
    { -16, -16 },
    { -16,   8 },
    { -16, -24 },
    { -16,  16 },
    { -16, -32 },
    { -16,  24 }
  };

  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + ofs_tbl[p_actwk->u.obj.userflag].x);
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + ofs_tbl[p_actwk->u.obj.userflag].y);
  p_actwk->patno = (p_actwk->u.obj.userflag >> 1) + 7;
  short wk = -((short)p_actwk->u.obj.userflag * 16);
  p_actwk->xspeed = -0x200 + wk;
  short yspeed = (short)((unsigned short)(wk * 2) & 0x180) + 128;
  if (ofs_tbl[p_actwk->u.obj.userflag].y < 0) {
    yspeed = -yspeed;
  }
  p_actwk->yspeed = yspeed;
}


static void chk_embl0930_damage0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.pl2push == 0) return;

  if (p_actwk->mstno == 0) {
    p_actwk->mstno = 48;
    soundset(110);
  }
  --p_actwk->mstno;
  if (p_actwk->mstno == 0) {
    p_actwk->u.obj.cddat.pl2push = 0;
  }
}


static void chk_embl0930_damage1(SKC_sprite_status* p_actwk) {
  if (p_actwk->colino != 0) return;

  if (p_actwk->mstno == 0) {
    p_actwk->mstno = 32;
    soundset(110);
    p_actwk->u.obj.cddat.pl2push = 1;
  }
  embl_chg_cor(p_actwk->mstno & 1 ? 0 : 1);
  --p_actwk->mstno;
  if (p_actwk->mstno == 0) {
    p_actwk->u.obj.cddat.pl2push = 0;
    p_actwk->colino = p_actwk->pattimm;
  }
}


static void embl_hand_ura(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actfree.embl_hand.posi += p_actwk->u.obj.actfree.embl_hand.speed;
  if (p_actwk->u.obj.actfree.embl_hand.speed_rev_timer-- == 0) {
    p_actwk->u.obj.actfree.embl_hand.speed_rev_timer = p_actwk->u.obj.actfree.embl_hand.speed_rev_timer_init;
    p_actwk->u.obj.actfree.embl_hand.speed = -p_actwk->u.obj.actfree.embl_hand.speed;
  }
}


static void chk_top_pt(SKC_sprite_status* p_actwk) {
  p_actwk->patno = (rotate_char_left(p_actwk->u.obj.actfree.embl_hand.posi + 16, 3) & 7) + 19;
}


SKC_sprite_pattern* iwa091_pt[1] = {
  &iwa091_pt00
};


static SKC_sprite_pattern iwa091_pt00 = {
  4,
  {
    { -32, 15, 0x0000, -32 },
    { -32, 15, 0x0010,   0 },
    {   0, 15, 0x1810, -32 },
    {   0, 15, 0x1800,   0 }
  }
};


SKC_sprite_pattern* nk0931_pt[19] = {
  &nk0931_pt00,
  &nk0931_pt01,
  &nk0931_pt02,
  &nk0931_pt03,
  &nk0931_pt04,
  &nk0931_pt05,
  &nk0931_pt06,
  &nk0931_pt07,
  &nk0931_pt08,
  &nk0931_pt09,
  &nk0931_pt10,
  &nk0931_pt11,
  &nk0931_pt12,
  &nk0931_pt13,
  &nk0931_pt14,
  &nk0931_pt15,
  &nk0931_pt16,
  &nk0931_pt17,
  &nk0931_pt18
};


static SKC_sprite_pattern nk0931_pt00 = {
  2,
  {
    { -16,  2, 0x0000, -20 },
    { -16, 15, 0x0003, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt01 = {
  2,
  {
    { -16,  2, 0x0000, -20 },
    { -16, 15, 0x0003, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt02 = {
  2,
  {
    { -16, 15, 0x0000, -20 },
    { -16,  2, 0x0010,  12 }
  }
};
static SKC_sprite_pattern nk0931_pt03 = {
  2,
  {
    { -11,  2, 0x0000, -20 },
    { -11, 15, 0x0003, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt04 = {
  2,
  {
    { -4, 10, 0x0000, -20 },
    {  4,  5, 0x0009,   4 }
  }
};
static SKC_sprite_pattern nk0931_pt05 = {
  2,
  {
    { -4, 10, 0x0000, -20 },
    {  4,  5, 0x0009,   4 }
  }
};
static SKC_sprite_pattern nk0931_pt06 = {
  2,
  {
    { -4, 10, 0x0000, -20 },
    {  4,  5, 0x0009,   4 }
  }
};
static SKC_sprite_pattern nk0931_pt07 = {
  2,
  {
    { -4, 14, 0x0000, -20 },
    {  4,  1, 0x000C,  12 }
  }
};
static SKC_sprite_pattern nk0931_pt08 = {
  2,
  {
    { -4, 14, 0x0000, -20 },
    {  4,  1, 0x000C,  12 }
  }
};
static SKC_sprite_pattern nk0931_pt09 = {
  2,
  {
    { -20, 14, 0x0000, -12 },
    {   4, 13, 0x000C, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt10 = {
  2,
  {
    { -20, 14, 0x0000, -12 },
    {   4, 13, 0x000C, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt11 = {
  3,
  {
    { -20, 13, 0x0000, -12 },
    {  -4,  9, 0x0008, -12 },
    {  12, 12, 0x000E, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt12 = {
  3,
  {
    { -20, 13, 0x0000, -12 },
    {  -4,  9, 0x0008, -12 },
    {  12, 12, 0x000E, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt13 = {
  2,
  {
    { -12,  9, 0x0000, -12 },
    {   4, 13, 0x0006, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt14 = {
  2,
  {
    { -20, 14, 0x0000, -12 },
    {   4,  9, 0x000C, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt15 = {
  2,
  {
    { -20,  9, 0x0000, -12 },
    {  -4, 14, 0x0006, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt16 = {
  3,
  {
    { -20, 9, 0x0000, -12 },
    { -4, 10, 0x0006, -12 },
    { -4,  4, 0x000F,  12 }
  }
};
static SKC_sprite_pattern nk0931_pt17 = {
  2,
  {
    { -20, 14, 0x0000, -12 },
    {   4,  9, 0x000C, -12 }
  }
};
static SKC_sprite_pattern nk0931_pt18 = {
  2,
  {
    { -20, 14, 0x0000, -12 },
    { 4, 9, 0x000C, -12 }
  }
};


unsigned short* nk0931_tbl[19] = {
  nk0931_tbl00,
  nk0931_tbl01,
  nk0931_tbl02,
  nk0931_tbl03,
  nk0931_tbl04,
  nk0931_tbl05,
  nk0931_tbl06,
  nk0931_tbl07,
  nk0931_tbl08,
  nk0931_tbl09,
  nk0931_tbl10,
  nk0931_tbl11,
  nk0931_tbl12,
  nk0931_tbl13,
  nk0931_tbl14,
  nk0931_tbl15,
  nk0931_tbl16,
  nk0931_tbl17,
  nk0931_tbl18
};


static unsigned short nk0931_tbl00[3] = {
  1, 0x0002, 0x003F
};
static unsigned short nk0931_tbl01[3] = {
  1, 0x0132, 0x016F
};
static unsigned short nk0931_tbl02[3] = {
  1, 0x026F, 0x0362
};
static unsigned short nk0931_tbl03[3] = {
  1, 0x0392, 0x03CF
};
static unsigned short nk0931_tbl04[3] = {
  1, 0x04C8, 0x0553
};
static unsigned short nk0931_tbl05[3] = {
  1, 0x0598, 0x0623
};
static unsigned short nk0931_tbl06[3] = {
  1, 0x0668, 0x06F3
};
static unsigned short nk0931_tbl07[3] = {
  1, 0x073B, 0x0711
};
static unsigned short nk0931_tbl08[3] = {
  1, 0x07FB, 0x0711
};
static unsigned short nk0931_tbl09[3] = {
  1, 0x08BB, 0x0977
};
static unsigned short nk0931_tbl10[3] = {
  1, 0x09FB, 0x0AB7
};
static unsigned short nk0931_tbl11[4] = {
  2, 0x0B37, 0x0BB5, 0x0C13
};
static unsigned short nk0931_tbl12[4] = {
  2, 0x0C57, 0x0CD5, 0x0C13
};
static unsigned short nk0931_tbl13[3] = {
  1, 0x0D35, 0x0D97
};
static unsigned short nk0931_tbl14[3] = {
  1, 0x0E1B, 0x0ED5
};
static unsigned short nk0931_tbl15[3] = {
  1, 0x0F35, 0x0F9B
};
static unsigned short nk0931_tbl16[4] = {
  2, 0x1055, 0x10B8, 0x1141
};
static unsigned short nk0931_tbl17[3] = {
  1, 0x116B, 0x1225
};
static unsigned short nk0931_tbl18[3] = {
  1, 0x128B, 0x1225
};


static SKC_set_act05_data nk0930_effect_set_tbl = {
  0,
  &nk0930_effect
};


static SKC_set_act05_data nk0930_exp_set_tbl = {
  15,
  &nk0930_exp
};


static SKC_set_act00_data clen0930_set_tbl = {
  0,
  {
    { &clen0930, 0, 35 }
  }
};


SKC_set_act00_data clenparts_set_tbl = {
  1,
  {
    { &clenparts, 0,   0 },
    { &clenchain, 0, -48 }
  }
};


static SKC_set_act05_data smok0930_set_tbl = {
  14,
  &smok0930
};


static SKC_set_act02_data embl0930_handb_set_tbl = {
  1,
  &embl0930_handb,
  8,
  -4
};


static SKC_set_act07_data embl0930_lhand_set_tbl = {
  9,
  &embl0930_lhand
};


static SKC_set_act07_data embl0930_rhand_set_tbl = {
  9,
  &embl0930_rhand
};


static SKC_set_act05_data caos09_frag_set_tbl = {
  4,
  &caos09_frag
};


static SKC_set_act05_data door09_set_tbl = {
  0,
  &door09
};


static SKC_set_act05_data piyo09_set_tbl = {
  0,
  &piyo09
};


static SKC_set_act05_data door09_break_set_tbl = {
  31,
  &door09_break
};


static SKC_enemy_init0_data nk0930_effect_init_tbl = {
  effectpat,
  0x0500,
  PRI_1,
  16,
  16,
  10,
  0
};


SKC_enemy_init0_data embl0930_init_tbl = {
  eggmbl_pt,
  0x852E,
  PRI_0,
  28,
  32,
  10,
  0
};


SKC_enemy_init0_data clen0930_init_tbl = {
  emblcl_pt,
  0x84A7,
  PRI_3,
  20,
  20,
  0,
  0
};


static SKC_enemy_init2_data clenparts_init_tbl = {
  PRI_5,
  16,
  20,
  1,
  0
};


static SKC_enemy_init2_data clenchain_init_tbl = {
  PRI_3,
  4,
  128,
  4,
  0
};


static SKC_enemy_init0_data smok0930_init_tbl = {
  caos09_pt,
  0x83B5,
  PRI_0,
  12,
  12,
  18,
  0
};


static SKC_enemy_init0_data caos09_frag_init_tbl = {
  caos09_pt,
  0x43B5,
  PRI_3,
  4,
  8,
  24,
  0,
};


static SKC_enemy_init0_data embl0930_handb_init_tbl = {
  emblcl_pt,
  0x04A7,
  PRI_0,
  8,
  8,
  18,
  0
};


static SKC_enemy_init2_data embl0930_lhand_init_tbl = {
  PRI_0,
  8,
  8,
  18,
  0
};


static SKC_enemy_init0_data door09_init_tbl = {
  door09_pt,
  0xC001,
  PRI_0,
  16,
  32,
  6,
  0
};


static SKC_enemy_init2_data door09_break_init_tbl = {
  PRI_0,
  4,
  4,
  7,
  0
};


static SKC_enemy_init0_data piyo09_init_tbl = {
  piyo09_pt,
  0x2500,
  PRI_3,
  12,
  4,
  1,
  0
};


static SKC_enemy_init0_data iwa091_init_tbl = {
  iwa091_pt,
  0x4500,
  PRI_4,
  32,
  32,
  0,
  0
};


unsigned short cor0942_dat[48] = {
  0x000, 0xEEE, 0x84E, 0x40C, 0x206, 0x0EE, 0x088, 0x008, 0x0AE, 0x08E, 0x8AE, 0x46A, 0xECC, 0xCAA, 0x866, 0x044,
  0x000, 0xEEE, 0xEAC, 0xC6A, 0x846, 0x624, 0xCEA, 0xAC4, 0x462, 0x222, 0x422, 0x624, 0x642, 0xA62, 0x2AC, 0x068,
  0x222, 0x00E, 0x008, 0xE66, 0xC44, 0xA24, 0x822, 0xECA, 0xE88, 0x222, 0x422, 0x042, 0x064, 0x2A8, 0x6EC, 0xEEE
};


SKC_wrt_data nk0931_wrt_tbl = {
  nk0931_cg,
  nk0931_tbl
};


static signed char smok0930_pg00[7] = { 1, 18, 18, 19, 20, 21, -12 };
static signed char smok0930_pg01[5] = { 3, 22, 22, 23, -12 };


static signed char piyo09_pg00[6] = { 5, 1, 2, 3, 4, -4 };


static SKC_sprite_pattern* piyo09_pt[6] = {
  &piyo09_pt00,
  &piyo09_pt01,
  &piyo09_pt02,
  &piyo09_pt03,
  &piyo09_pt04,
  &piyo09_pt05
};


static SKC_sprite_pattern piyo09_pt00 = {
  0,
  {}
};
static SKC_sprite_pattern piyo09_pt01 = {
  1,
  {
    { -12, 8, 0x0000, -16 }
  }
};
static SKC_sprite_pattern piyo09_pt02 = {
  1,
  {
    { -12, 8, 0x0003, -16 }
  }
};
static SKC_sprite_pattern piyo09_pt03 = {
  1,
  {
    { -12, 8, 0x0006, -16 }
  }
};
static SKC_sprite_pattern piyo09_pt04 = {
  1,
  {
    { -12, 8, 0x0009, -16 }
  }
};
static SKC_sprite_pattern piyo09_pt05 = {
  1,
  {
    { -12, 8, 0x000C, -16 }
  }
};


SKC_sprite_pattern* emblcl_pt[29] = {
  &emblcl_pt00,
  &emblcl_pt01,
  &emblcl_pt02,
  &emblcl_pt03,
  &emblcl_pt04,
  &emblcl_pt05,
  &emblcl_pt06,
  &emblcl_pt07,
  &emblcl_pt08,
  &emblcl_pt09,
  &emblcl_pt10,
  &emblcl_pt11,
  &emblcl_pt12,
  &emblcl_pt13,
  &emblcl_pt14,
  &emblcl_pt15,
  &emblcl_pt16,
  &emblcl_pt17,
  &emblcl_pt18,
  &emblcl_pt19,
  &emblcl_pt20,
  &emblcl_pt21,
  &emblcl_pt22,
  &emblcl_pt23,
  &emblcl_pt24,
  &emblcl_pt25,
  &emblcl_pt26,
  &emblcl_pt27,
  &emblcl_pt28
};


static SKC_sprite_pattern emblcl_pt00 = {
  2,
  {
    { -16, 9, 0x0000, -20 },
    { -16, 7, 0x000A,   4 }
  }
};
static SKC_sprite_pattern emblcl_pt01 = {
  1,
  {
    { 0, 5, 0x0006, -20 }
  }
};
static SKC_sprite_pattern emblcl_pt02 = {
  2,
  {
    { -16, 13, 0x0012, -16 },
    {   0,  6, 0x0020,   0 }
  }
};
static SKC_sprite_pattern emblcl_pt03 = {
  1,
  {
    { 0, 6, 0x001A, -16 }
  }
};
static SKC_sprite_pattern emblcl_pt04 = {
  2,
  {
    {  0, 1, 0x0026, -4 },
    { 16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt05 = {
  3,
  {
    { -16, 1, 0x0026, -4 },
    {   0, 1, 0x0026, -4 },
    {  16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt06 = {
  4,
  {
    { -32, 1, 0x0026, -4 },
    { -16, 1, 0x0026, -4 },
    {   0, 1, 0x0026, -4 },
    {  16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt07 = {
  5,
  {
    { -48, 1, 0x0026, -4 },
    { -32, 1, 0x0026, -4 },
    { -16, 1, 0x0026, -4 },
    {   0, 1, 0x0026, -4 },
    {  16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt08 = {
  6,
  {
    { -64, 1, 0x0026, -4 },
    { -48, 1, 0x0026, -4 },
    { -32, 1, 0x0026, -4 },
    { -16, 1, 0x0026, -4 },
    {   0, 1, 0x0026, -4 },
    {  16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt09 = {
  7,
  {
    { -80, 1, 0x0026, -4 },
    { -64, 1, 0x0026, -4 },
    { -48, 1, 0x0026, -4 },
    { -32, 1, 0x0026, -4 },
    { -16, 1, 0x0026, -4 },
    {   0, 1, 0x0026, -4 },
    {  16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt10 = {
  8,
  {
    { -96, 1, 0x0026, -4 },
    { -80, 1, 0x0026, -4 },
    { -64, 1, 0x0026, -4 },
    { -48, 1, 0x0026, -4 },
    { -32, 1, 0x0026, -4 },
    { -16, 1, 0x0026, -4 },
    {   0, 1, 0x0026, -4 },
    {  16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt11 = {
  9,
  {
    { -112, 1, 0x0026, -4 },
    {  -96, 1, 0x0026, -4 },
    {  -80, 1, 0x0026, -4 },
    {  -64, 1, 0x0026, -4 },
    {  -48, 1, 0x0026, -4 },
    {  -32, 1, 0x0026, -4 },
    {  -16, 1, 0x0026, -4 },
    {    0, 1, 0x0026, -4 },
    {   16, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt12 = {
  1,
  {
    { -20, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt13 = {
  1,
  {
    { -20, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt14 = {
  1,
  {
    { -20, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt15 = {
  1,
  {
    { -20, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt16 = {
  1,
  {
    { -20, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt17 = {
  1,
  {
    { -20, 1, 0x0026, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt18 = {
  1,
  {
    { -4, 0, 0x0028, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt19 = {
  1,
  {
    { -8, 1, 0x002F, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt20 = {
  1,
  {
    { -8, 5, 0x082B, -8 }
  }
};
static SKC_sprite_pattern emblcl_pt21 = {
  1,
  {
    { -4, 4, 0x0829, -8 }
  }
};
static SKC_sprite_pattern emblcl_pt22 = {
  1,
  {
    { -8, 5, 0x182B, -8 }
  }
};
static SKC_sprite_pattern emblcl_pt23 = {
  1,
  {
    { -8, 1, 0x102F, -4 }
  }
};
static SKC_sprite_pattern emblcl_pt24 = {
  1,
  {
    { -8, 5, 0x102B, -8 }
  }
};
static SKC_sprite_pattern emblcl_pt25 = {
  1,
  {
    { -4, 4, 0x0029, -8 }
  }
};
static SKC_sprite_pattern emblcl_pt26 = {
  1,
  {
    { -8, 5, 0x002B, -8 }
  }
};
static SKC_sprite_pattern emblcl_pt27 = {
  1,
  {
    { -4, 4, 0x0031, -8 }
  }
};
static SKC_sprite_pattern emblcl_pt28 = {
  1,
  {
    { -4, 4, 0x0831, -8 }
  }
};
