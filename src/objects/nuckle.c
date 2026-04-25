#include "nuckle.h"
#include <stdbool.h>
#include <string.h>
#include "../data/colortbl.h"
#include "../data/cg/nuckle.h"
#include "../data/cg/switch.h"
#include "../data/cg/zone07/egbomb07.h"
#include "../data/cg/zone07/nk0701.h"
#include "../data/cg/zone07/nkopen.h"
#include "../data/cg/zone07/sw0700.h"
#include "../data/cg/zone07/sw0701.h"
#include "../data/cg/zone0a/deth0a.h"
#include "../data/cg/zone0a/egjr0a.h"
#include "../data/cg/zone0a/kumo0a.h"
#include "../data/cg/zone0a/nk0a00.h"
#include "../data/pat/nuckle.h"
#include "../data/pat/zone06/bomb06.h"
#include "../data/wrt/nuckle.h"
#include "../types/cgdata.h"
#include "../types/enemyinitdata.h"
#include "../types/friend07initdata.h"
#include "../types/point.h"
#include "../types/setactdata.h"
#include "../types/sonic3ram.h"
#include "../types/speed.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../types/wrtdata.h"
#include "../types/wrtinitdata.h"
#include "../utils/bits.h"
#include "../utils/controller.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../dev.h"
#include "../dircol.h"
#include "../etc.h"
#include "../hitchk.h"
#include "../reloader.h"
#include "../shared.h"
#include "../sound.h"
#include "brkabe.h"
#include "bryuka.h"
#include "explosion.h"
#include "friend.h"
#include "save.h"
#include "switch.h"
#include "zone.h"
#include "zone00/bs00m.h"
#include "zone03/magnet.h"
#include "zone09/nuckle09.h"
#include "zone0a/egjr0a.h"
static void nuckle000(SKC_sprite_status* p_actwk);
static void nuckle000_init(SKC_sprite_status* p_actwk);
static void nuckle000_wait0(SKC_sprite_status* p_actwk);
static void nuckle000_jump0(SKC_sprite_status* p_actwk);
static void nuckle000_wait1(SKC_sprite_status* p_actwk);
static void nuckle000_run0_init(SKC_sprite_status* p_actwk);
static void nuckle000_run0(SKC_sprite_status* p_actwk);
static void spd_neg(SKC_sprite_status* p_actwk);
static void nuckle000_wait2_init(SKC_sprite_status* p_actwk);
static void nuckle000_wait2(SKC_sprite_status* p_actwk);
static void nuckle000_run1_init(SKC_sprite_status* p_actwk);
static void nuckle000_run1(SKC_sprite_status* p_actwk);
static void opniwa(SKC_sprite_status* p_actwk);
static void opniwa_wait0(SKC_sprite_status* p_actwk);
static void nuckle001(SKC_sprite_status* p_actwk);
static void nuckle001_init(SKC_sprite_status* p_actwk);
static void nuckle001_wait0(SKC_sprite_status* p_actwk);
static void nuckle001_run0_init(SKC_sprite_status* p_actwk);
static void nuckle001_run0(SKC_sprite_status* p_actwk);
static void nuckle001_laugh0_init(SKC_sprite_status* p_actwk);
static void laugh_pg_init(SKC_sprite_status* p_actwk);
static void nuckle001_laugh0(SKC_sprite_status* p_actwk);
static void nuckle001_jump0_init(SKC_sprite_status* p_actwk);
static void nuckle001_jump0_init0(SKC_sprite_status* p_actwk);
static void nuckle001_jump0_init1(SKC_sprite_status* p_actwk);
static void nuckle001_jump0(SKC_sprite_status* p_actwk);
static void nuckle001_wait1(SKC_sprite_status* p_actwk);
static void nuckle001_col(SKC_sprite_status* p_actwk);
static void nuckle010(SKC_sprite_status* p_actwk);
static void nuckle010_boss_set(SKC_sprite_status* p_actwk);
static void nuckle010_init(SKC_sprite_status* p_actwk);
static void nuckle010_wait0(SKC_sprite_status* p_actwk);
static void nuckle010_wait1(SKC_sprite_status* p_actwk);
static void nuckle010_run0_init(SKC_sprite_status* p_actwk);
static void nuckle010_run0(SKC_sprite_status* p_actwk);
static void nuckle010_wait2_init(SKC_sprite_status* p_actwk);
static void nuckle010_wait2(SKC_sprite_status* p_actwk);
static void nuckle010_jump0_init(SKC_sprite_status* p_actwk);
static void nuckle010_wait3(SKC_sprite_status* p_actwk);
static unsigned short nuckle030_lim_tbl[8];
static void nuckle030(SKC_sprite_status* p_actwk);
static void nuckle030_boss_set(SKC_sprite_status* p_actwk);
static void nuckle030_init(SKC_sprite_status* p_actwk);
static void nuckle030_wait0(SKC_sprite_status* p_actwk);
static void nuckle030_wait1_init0(SKC_sprite_status* p_actwk);
static void nuckle030_wait1(SKC_sprite_status* p_actwk);
static void nuckle030_jump0_init(SKC_sprite_status* p_actwk);
static void nuckle030_jump0(SKC_sprite_status* p_actwk);
static void nuckle030_wait2(SKC_sprite_status* p_actwk);
static void nuckle030_away0_init(SKC_sprite_status* p_actwk);
static void nuckle030_away0(SKC_sprite_status* p_actwk);
static void knuckles_fout(SKC_sprite_status* p_actwk);
static void nuckle030_col(SKC_sprite_status* p_actwk);
static void cchg0320_act(SKC_sprite_status* p_actwk);
static void nuckle031(SKC_sprite_status* p_actwk);
static void nuckle031_boss_set(SKC_sprite_status* p_actwk);
static void nuckle031_init(SKC_sprite_status* p_actwk);
static void nuckle031_wait0(SKC_sprite_status* p_actwk);
static void nuckle031_wait1(SKC_sprite_status* p_actwk);
static void nuckle031_wait2(SKC_sprite_status* p_actwk);
static void nuckle031_jump0_init(SKC_sprite_status* p_actwk);
static void nuckle031_wait3(SKC_sprite_status* p_actwk);
static void nuckle031_away0_init(SKC_sprite_status* p_actwk);
static void nuckle031_away0(SKC_sprite_status* p_actwk);
static void nuckle031_wait4(SKC_sprite_status* p_actwk);
static void nuckle060(SKC_sprite_status* p_actwk);
static void nuckle060_init(SKC_sprite_status* p_actwk);
static void nuckle060_wait0(SKC_sprite_status* p_actwk);
static void nuckle060_wait1(SKC_sprite_status* p_actwk);
static void nuckle060_trow0_init(SKC_sprite_status* p_actwk);
static void nuckle060_trow0(SKC_sprite_status* p_actwk);
static void nuckle060_wait2_init(SKC_sprite_status* p_actwk);
static void nuckle060_wait2(SKC_sprite_status* p_actwk);
static void nuckle060_lagh0_init(SKC_sprite_status* p_actwk);
static void nuckle060_lagh0(SKC_sprite_status* p_actwk);
static void nuckle030_wait3_init(SKC_sprite_status* p_actwk);
static void nuckle060_wait3(SKC_sprite_status* p_actwk);
static void nuckle060_away0_init(SKC_sprite_status* p_actwk);
static void nuckle060_away0(SKC_sprite_status* p_actwk);
static void nuckle060_col(SKC_sprite_status* p_actwk);
static void nuckle060_col__set_pl_data(SKC_sprite_status* p_playerwk);
static void bomb06(SKC_sprite_status* p_actwk);
static void bomb06_fall0(SKC_sprite_status* p_actwk);
static void bomb06_exp(SKC_sprite_status* p_actwk);
static void bomb06_exp_move0(SKC_sprite_status* p_actwk);
static void nuckle061(SKC_sprite_status* p_actwk);
static void nuckle061_init(SKC_sprite_status* p_actwk);
static void nuckle061_wait0(SKC_sprite_status* p_actwk);
static void nuckle061_pnch0(SKC_sprite_status* p_actwk);
static void nuckle061_wait1_init(SKC_sprite_status* p_actwk);
static void nuckle061_lagh0(SKC_sprite_status* p_actwk);
static void nuckle061_blns0(SKC_sprite_status* p_actwk);
static void nuckle061_fall0(SKC_sprite_status* p_actwk);
static void nuckle061_fall1(SKC_sprite_status* p_actwk);
static void nuckle061_dai(SKC_sprite_status* p_actwk);
static void nuckle061_dai_wait0(SKC_sprite_status* p_actwk);
static void nuckle061_dai_move0(SKC_sprite_status* p_actwk);
static void nuckle061_dai_fall0(SKC_sprite_status* p_actwk);
static void tekotu_wait0(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern* tekotu_pt[2];
static SKC_sprite_pattern tekotu_pt00;
static SKC_sprite_pattern tekotu_pt01;
static void nuckle070(SKC_sprite_status* p_actwk);
static void nuckle070_init(SKC_sprite_status* p_actwk);
static void nuckle070_wait0(SKC_sprite_status* p_actwk);
static void nuckle070_run0(SKC_sprite_status* p_actwk);
static void nuckle070_wait1(SKC_sprite_status* p_actwk);
static void nuckle070_run1(SKC_sprite_status* p_actwk);
static void nuckle070_jump0(SKC_sprite_status* p_actwk);
static void nk0700_jump1_init(SKC_sprite_status* p_actwk);
static void nuckle070_jump1(SKC_sprite_status* p_actwk);
static void nk0700_run2_init(SKC_sprite_status* p_actwk);
static void nuckle070_run2(SKC_sprite_status* p_actwk);
static void ev0700_move(SKC_sprite_status* p_actwk);
static void ev0700_init(SKC_sprite_status* p_actwk);
static void ev0700_col0(SKC_sprite_status* p_actwk);
static void ev0700_wait0(SKC_sprite_status* p_actwk);
static void ev0700_wait1(SKC_sprite_status* p_actwk);
static void ev0700_scrd0(SKC_sprite_status* p_actwk);
static void ev0700_wait2(SKC_sprite_status* p_actwk);
static void ev0700_fout0(SKC_sprite_status* p_actwk);
static void ev0700m(SKC_sprite_status* p_actwk);
static void ev0700m_wait0(SKC_sprite_status* p_actwk);
static void sw0700_wait0(SKC_sprite_status* p_actwk);
static void sw0700_wait1(SKC_sprite_status* p_actwk);
static void sw0700_wait2(SKC_sprite_status* p_actwk);
static void sw0700_wait3(SKC_sprite_status* p_actwk);
static void sw0700_wait00_init(SKC_sprite_status* p_actwk);
static void sw0700_wait00(SKC_sprite_status* p_actwk);
static void sw0700_wait01(SKC_sprite_status* p_actwk);
static void nk0700(SKC_sprite_status* p_actwk);
static void nk0700_apar0(SKC_sprite_status* p_actwk);
static void nk0700_kyoro0_init(SKC_sprite_status* p_actwk);
static void nk0700_kyoro0(SKC_sprite_status* p_actwk);
static void nk0700_away0_init(SKC_sprite_status* p_actwk);
static void nk0700_away0(SKC_sprite_status* p_actwk);
static void nk0700_fout(SKC_sprite_status* p_actwk);
static void shut07(SKC_sprite_status* p_actwk);
static void shut07_wait0(SKC_sprite_status* p_actwk);
static void shut07_move0(SKC_sprite_status* p_actwk);
static void shut07_wait0_init(SKC_sprite_status* p_actwk);
static unsigned short nuckle071_lim_tbl[8];
static void nuckle071(SKC_sprite_status* p_actwk);
static void nuckle071_boss_set(SKC_sprite_status* p_actwk);
static void nuckle071_init(SKC_sprite_status* p_actwk);
static void nuckle071_wait0(SKC_sprite_status* p_actwk);
static void nuckle071_wait1_init(SKC_sprite_status* p_actwk);
static void nuckle071_wait1(SKC_sprite_status* p_actwk);
static void nuckle071_wait1__set_flag(SKC_sprite_status* p_playerwk);
static void nuckle071_turn0(SKC_sprite_status* p_actwk);
static void nuckle071_fout0_init(SKC_sprite_status* p_actwk);
static void nuckle071_fout0(SKC_sprite_status* p_actwk);
static void sw0701(SKC_sprite_status* p_actwk);
static void sw0701_wait0(SKC_sprite_status* p_actwk);
static void housi071(SKC_sprite_status* p_actwk);
static void housi071_wait0(SKC_sprite_status* p_actwk);
static void ev0701(SKC_sprite_status* p_actwk);
static void ev0701_move0(SKC_sprite_status* p_actwk);
static void nuckle072(SKC_sprite_status* p_actwk);
static void nuckle072_move(SKC_sprite_status* p_actwk);
static void nuckle072_init(SKC_sprite_status* p_actwk);
static void nuckle072_wait0(SKC_sprite_status* p_actwk);
static void nuckle072_wait1(SKC_sprite_status* p_actwk);
static void nuckle072_jump0(SKC_sprite_status* p_actwk);
static void nuckle072_fall0(SKC_sprite_status* p_actwk);
static void nuckle072_land0(SKC_sprite_status* p_actwk);
static void nuckle072_run0_init(SKC_sprite_status* p_actwk);
static void nuckle072_run0(SKC_sprite_status* p_actwk);
static void end_open(SKC_sprite_status* p_actwk);
static void chk_pause(SKC_sprite_status* p_actwk);
static void friend07(SKC_sprite_status* p_actwk);
static void risu_move0(SKC_sprite_status* p_actwk);
static void flicky_move0(SKC_sprite_status* p_actwk);
static void egbomb07(SKC_sprite_status* p_actwk);
static void egbomb07_wait0(SKC_sprite_status* p_actwk);
static void egbomb07_wait1(SKC_sprite_status* p_actwk);
static void egbomb07_wait2(SKC_sprite_status* p_actwk);
static void egbomb07_spark(SKC_sprite_status* p_actwk);
static void egbomb07_spark_wait0(SKC_sprite_status* p_actwk);
static void egbomb07_smoke(SKC_sprite_status* p_actwk);
static void egbomb07_smoke_wait0(SKC_sprite_status* p_actwk);
static void egbomb07_exp(SKC_sprite_status* p_actwk);
static void egbomb07_exp_wait0(SKC_sprite_status* p_actwk);
static void egjr07(SKC_sprite_status* p_actwk);
static void egjr07_wait0(SKC_sprite_status* p_actwk);
static void egjr07_wait1(SKC_sprite_status* p_actwk);
static void nuckle0a0(SKC_sprite_status* p_actwk);
static void nuckle0a0_init(SKC_sprite_status* p_actwk);
static void nuckle0a0_wait0(SKC_sprite_status* p_actwk);
static void nuckle0a0_fall0(SKC_sprite_status* p_actwk);
static void nuckle0a0_wait1(SKC_sprite_status* p_actwk);
static void nuckle0a0_wait2(SKC_sprite_status* p_actwk);
static void nuckle0a0_wait3(SKC_sprite_status* p_actwk);
static void nuckle0a0_wait4(SKC_sprite_status* p_actwk);
static void nuckle0a0_jump0(SKC_sprite_status* p_actwk);
static void nuckle0a0_run0(SKC_sprite_status* p_actwk);
static void nuckle0a0_jump1(SKC_sprite_status* p_actwk);
static void nuckle0a0_wait5(SKC_sprite_status* p_actwk);
static void sw0a00_wait0(SKC_sprite_status* p_actwk);
static void deth0a(SKC_sprite_status* p_actwk);
static void deth0a_up0(SKC_sprite_status* p_actwk);
static void deth0a_up1(SKC_sprite_status* p_actwk);
static void kumo0a(SKC_sprite_status* p_actwk);
static void kumo0a_init(SKC_sprite_status* p_actwk);
static void kumo0a_wait0(SKC_sprite_status* p_actwk);
static void kumo0a_down0(SKC_sprite_status* p_actwk);
static void mask0a(SKC_sprite_status* p_actwk);
static void mask0a_wait0(SKC_sprite_status* p_actwk);
static void suji0a(SKC_sprite_status* p_actwk);
static void suji0a_wait0(SKC_sprite_status* p_actwk);
static void megj0a(SKC_sprite_status* p_actwk);
static void megj0a_wait0(SKC_sprite_status* p_actwk);
static SKC_cg_data switch_cg_tbl;
static void nucksw_wait0(SKC_sprite_status* p_actwk);
static short knuckle_col_tbl[4];
static void nucksw_wait1(SKC_sprite_status* p_actwk);
static void switchact_001(SKC_sprite_status* p_actwk);
static void switchact_010(SKC_sprite_status* p_actwk);
static void switchact_030(SKC_sprite_status* p_actwk);
static void switchact_031(SKC_sprite_status* p_actwk);
static void setbryuka_framein(SKC_sprite_status* p_actwk);
static void setbryuka_wait0(SKC_sprite_status* p_actwk);
static void cchgsw_wait0(SKC_sprite_status* p_actwk);
static void set_friend07_spd(SKC_sprite_status* p_actwk);
static void set_friend07_spd__move_l(SKC_sprite_status* p_actwk);
static void set_friend07_spd__move_r(SKC_sprite_status* p_actwk);
static void chk_shut07_ride(SKC_sprite_status* p_actwk);
static void chk_nk0720_plpt(SKC_sprite_status* p_actwk);
static void chk_nk0720_plpt__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void set_housi(SKC_sprite_status* p_actwk);
static void chk_gomen(SKC_sprite_status* p_actwk);
static void speedset0a(SKC_sprite_status* p_actwk);
static void chk_megj0a_set(SKC_sprite_status* p_actwk);
static void chk_h_scroll(SKC_sprite_status* p_actwk);
static void chk_h_scroll__chk(SKC_sprite_status* p_actwk);
static void nkmiles_wrt(SKC_sprite_status* p_actwk);
static SKC_wrt_init_data nk0701_init_tbl;
static SKC_wrt_init_data nk0702_init_tbl;
static SKC_wrt_init_data nk0931_init_tbl;
static SKC_enemy_init0_data nucksw_init_tbl;
static SKC_enemy_init0_data bomb06_init_tbl;
static SKC_enemy_init0_data nuckle061_dai_init_tbl;
static SKC_enemy_init0_data tekotu_init_tbl;
static SKC_enemy_init0_data opniwa_init_tbl;
static SKC_enemy_init0_data nk0700_init_tbl;
static SKC_enemy_init0_data sw0700_init_tbl;
static SKC_enemy_init0_data sw0701_init_tbl;
static SKC_enemy_init0_data shut07_init_tbl;
static SKC_enemy_init0_data egbomb07_init_tbl;
static SKC_enemy_init2_data egbomb07_spark_init_tbl;
static SKC_enemy_init2_data egbomb07_smoke_init_tbl;
static SKC_enemy_init0_data sw0a00_init_tbl;
static SKC_enemy_init0_data deth0a_init_tbl;
static SKC_wrt_init_data kumo0a_init_tbl;
static SKC_enemy_init0_data mask0a_init_tbl;
static SKC_enemy_init2_data suji0a_init_tbl;
static SKC_enemy_init1_data megj0a_init_tbl;
static SKC_set_act05_data nuckle001_col_set_tbl;
static SKC_set_act00_data nuckle030_col_set_tbl;
static SKC_set_act00_data limchg030_set_tbl;
static SKC_set_act00_data nuckle060_col_set_tbl;
static SKC_set_act00_data bomb06_set_tbl;
static SKC_set_act05_data bomb06_exp_set_tbl;
static SKC_set_act02_data nuckle061_dai_set_tbl;
static SKC_set_act00_data opniwa_set_tbl;
static SKC_set_act00_data nucksw_set_tbl010;
static SKC_set_act05_data nuckles_set_tbl;
static SKC_set_act05_data nk0700_set_tbl;
static SKC_set_act05_data shut07_set_tbl;
static SKC_set_act00_data sw0701_set_tbl;
static SKC_set_act00_data kumo0a_set_tbl;
static SKC_set_act05_data megj0a_set_tbl;
static SKC_set_act05_data deth0a_set_tbl;
static SKC_set_act05_data egbomb07_exp_set_tbl;
static SKC_set_act05_data friend07_set_tbl;
static SKC_set_act00_data egbomb07_spark_set_tbl;
static SKC_set_act05_data egbomb07_smoke_set_tbl;
static SKC_wrt_data nk0701_wrt_tbl;
static SKC_wrt_data nkopen_wrt_tbl;
static SKC_wrt_data kumo0a_wrt_tbl;
static signed char balance_pg00[5];
static signed char run_pg00[10];
static signed char run_pg01[6];
static signed char ball_pg00[10];
static signed char laugh_pg00[6];
static signed char laugh_pg01[4];
static signed char throw_pg00[15];
static signed char panchi_pg00[15];
static signed char nk0700_pg00[21];
static signed char turnsw_pg00[35];
static signed char tired_pg00[6];
static signed char go_pg00[10];
static signed char go_pg01[5];
static signed char kumo0a_pg00[30];
static signed char kumo0a_pg01[9];
static signed char suji0a_pg00[17];
static signed char spin_pg01[13];
static signed char die_pg01[14];
static signed char relax_pg00[4];
static signed char relax_pg01[9];
static signed char land_pg02[53];
static signed char egbomb07_spark_pg00[6];
static signed char egbomb07_smoke_pg00[7];
static unsigned short cchg0320_tbl[64];
static unsigned short deth0a_color[16];
static unsigned short egbomb_cor_tbl[16];
static SKC_sprite_pattern* nk0700_pt[5];
static SKC_sprite_pattern nk0700_pt00;
static SKC_sprite_pattern nk0700_pt01;
static SKC_sprite_pattern nk0700_pt02;
static SKC_sprite_pattern nk0700_pt03;
static SKC_sprite_pattern nk0700_pt04;
static SKC_sprite_pattern* shut07_pt[1];
static SKC_sprite_pattern shut07_pt00;
static SKC_sprite_pattern* nk0701_pt[4];
static SKC_sprite_pattern nk0701_pt00;
static SKC_sprite_pattern nk0701_pt01;
static SKC_sprite_pattern nk0701_pt02;
static SKC_sprite_pattern nk0701_pt03;
static unsigned short* nk0701_tbl[4];
static unsigned short nk0701_tbl00[3];
static unsigned short nk0701_tbl01[3];
static unsigned short nk0701_tbl02[3];
static unsigned short nk0701_tbl03[3];
static SKC_sprite_pattern* sw0701_pt[2];
static SKC_sprite_pattern sw0701_pt00;
static SKC_sprite_pattern sw0701_pt01;
static SKC_sprite_pattern* housi071_pt[1];
static SKC_sprite_pattern housi071_pt00;
static SKC_sprite_pattern nk0a00_pt00;
static SKC_sprite_pattern nk0a00_pt01;
static SKC_sprite_pattern nk0a00_pt02;
static SKC_sprite_pattern nk0a00_pt03;
static SKC_sprite_pattern nk0a00_pt04;
static SKC_sprite_pattern nk0a00_pt05;
static SKC_sprite_pattern nk0a00_pt06;
static unsigned short* nk0a00_tbl[7];
static unsigned short nk0a00_tbl00[4];
static unsigned short nk0a00_tbl01[3];
static unsigned short nk0a00_tbl02[3];
static unsigned short nk0a00_tbl03[3];
static unsigned short nk0a00_tbl04[3];
static unsigned short nk0a00_tbl05[2];
static unsigned short nk0a00_tbl06[3];
static SKC_sprite_pattern* deth0a_pt[7];
static SKC_sprite_pattern deth0a_pt00;
static SKC_sprite_pattern deth0a_pt01;
static SKC_sprite_pattern deth0a_pt02;
static SKC_sprite_pattern deth0a_pt03;
static SKC_sprite_pattern deth0a_pt04;
static SKC_sprite_pattern deth0a_pt05;
static SKC_sprite_pattern deth0a_pt06;
static SKC_sprite_pattern* kumo0a_pt[13];
static SKC_sprite_pattern kumo0a_pt00;
static SKC_sprite_pattern kumo0a_pt01;
static SKC_sprite_pattern kumo0a_pt02;
static SKC_sprite_pattern kumo0a_pt03;
static SKC_sprite_pattern kumo0a_pt04;
static SKC_sprite_pattern kumo0a_pt05;
static SKC_sprite_pattern kumo0a_pt06;
static SKC_sprite_pattern kumo0a_pt07;
static SKC_sprite_pattern kumo0a_pt08;
static SKC_sprite_pattern kumo0a_pt09;
static SKC_sprite_pattern kumo0a_pt10;
static SKC_sprite_pattern kumo0a_pt11;
static SKC_sprite_pattern kumo0a_pt12;
static unsigned short* kumo0a_tbl[13];
static unsigned short kumo0a_tbl00[2];
static unsigned short kumo0a_tbl01[3];
static unsigned short kumo0a_tbl02[4];
static unsigned short kumo0a_tbl03[4];
static unsigned short kumo0a_tbl04[4];
static unsigned short kumo0a_tbl05[4];
static unsigned short kumo0a_tbl06[4];
static unsigned short kumo0a_tbl07[4];
static unsigned short kumo0a_tbl08[4];
static unsigned short kumo0a_tbl09[4];
static unsigned short kumo0a_tbl10[4];
static unsigned short kumo0a_tbl11[4];
static unsigned short kumo0a_tbl12[4];
static SKC_sprite_pattern* nkopen_pt[5];
static SKC_sprite_pattern nkopen_pt00;
static SKC_sprite_pattern nkopen_pt01;
static SKC_sprite_pattern nkopen_pt02;
static SKC_sprite_pattern nkopen_pt03;
static SKC_sprite_pattern nkopen_pt04;
static unsigned short* nkopen_tbl[5];
static unsigned short nkopen_tbl00[5];
static unsigned short nkopen_tbl01[5];
static unsigned short nkopen_tbl02[6];
static unsigned short nkopen_tbl03[3];
static unsigned short nkopen_tbl04[5];
static SKC_sprite_pattern* egbomb_pt[9];
static SKC_sprite_pattern egbomb_pt00;
static SKC_sprite_pattern egbomb_pt01;
static SKC_sprite_pattern egbomb_pt02;
static SKC_sprite_pattern egbomb_pt03;
static SKC_sprite_pattern egbomb_pt04;
static SKC_sprite_pattern egbomb_pt05;
static SKC_sprite_pattern egbomb_pt06;
static SKC_sprite_pattern egbomb_pt07;
static SKC_sprite_pattern egbomb_pt08;

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void nuckle(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[13] = {
    &nuckle000,
    &nuckle001,
    &nuckle010,
    &nuckle030,
    &nuckle031,
    &nuckle060,
    &nuckle061,
    &nuckle070,
    &nuckle071,
    &nuckle090,
    &nuckle091,
    &nuckle0a0,
    &nuckle072
  };

  g_ram.DAT_08fffaa4_obj = p_actwk - g_ram.actwk;
  p_actwk->r_ptr = act_tbl[p_actwk->u.obj.userflag];
  p_actwk->r_ptr(p_actwk);
}


static void nuckle000(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[7] = {
    &nuckle000_init,
    &nuckle000_wait0,
    &nuckle000_jump0,
    &nuckle000_wait1,
    &nuckle000_run0,
    &nuckle000_wait2,
    &nuckle000_run1
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
  actionsub(p_actwk);
}


static void nuckle000_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  CLEAR_BIT(p_actwk->sproffset, 15);
  p_actwk->sprvsize = 19;
  p_actwk->patno = 8;
  fp16_set_integer(&p_actwk->xposi, 0x1400);
  fp16_set_integer(&p_actwk->yposi, 0x440);
  set_nuckle_bgm();
  set_act00(p_actwk, &opniwa_set_tbl);
}


static void nuckle000_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    p_actwk->r_no = 4;
    p_actwk->u.obj.cddat.die = 1;
    p_actwk->yspeed = -0x600;
    p_actwk->xspeed = 0x80;
    set_emy_cor(&nuckle_cor_tbl);
  }
}


static void nuckle000_jump0(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, ball_pg00);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      p_actwk->r_no = 6;
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      p_actwk->patno = 22;
      p_actwk->u.obj.timer = 127;
      p_actwk->r_ptr = &nuckle000_run0_init;
    }
  }
}


static void nuckle000_wait1(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void nuckle000_run0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->actflg.hflip ^= 1;
  p_actwk->u.obj.pg_data_ptr = run_pg01;
  p_actwk->xspeed = -0x600;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.timer = 47;
  p_actwk->u.obj.callback_ptr = &spd_neg;
  nuckle000_run0(p_actwk);
}


static void nuckle000_run0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset2(p_actwk);
  dec_timer(p_actwk);
}


static void spd_neg(SKC_sprite_status* p_actwk) {
  p_actwk->xspeed = -p_actwk->xspeed;
  p_actwk->actflg.hflip ^= 1;
  p_actwk->u.obj.timer = 47;
  p_actwk->u.obj.callback_ptr = &nuckle000_wait2_init;
}


static void nuckle000_wait2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 10;
  p_actwk->patno = 22;
  p_actwk->u.obj.timer = 63;
  p_actwk->u.obj.callback_ptr = &nuckle000_run1_init;
  laugh_pg_init(p_actwk);
}


static void nuckle000_wait2(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  dec_timer(p_actwk);
}


static void nuckle000_run1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  p_actwk->u.obj.pg_data_ptr = run_pg01;
  p_actwk->xspeed = 0x600;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &res_bgm_act;
  }
}


static void nuckle000_run1(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 1) {
    pt_chg(p_actwk);
    speedset2(p_actwk);
  }
  else {
    g_ram.pal_anim_ctr0 = 0;
    g_ram.pl_input_lock_flag = 0;
    cg_reset();
    clr_wchg_bit(p_actwk);
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &title;
    }
    g_ram.DAT_08fff711 = 0x91;
    g_ram.pltime_f = 0x80;
    g_ram.pltime.hours = 0;
    g_ram.pltime.minutes = 0;
    g_ram.pltime.seconds = 0;
    g_ram.pltime.frames = 0;
    g_ram.pl_suu_f = 0;
    set_emy_fout0(p_actwk);
  }
}


static void opniwa(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &opniwa_init_tbl);
  p_actwk->r_ptr = &opniwa_wait0;
  opniwa_wait0(p_actwk);
}


static void opniwa_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 0) {
    actionsub(p_actwk);
  }
  else {
    ++p_actwk->patno;
    p_actwk->r_ptr = &bryukamove2;
    breakgosubf(p_actwk, bryukaspdtbl);
  }
}


static void nuckle001(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[6] = {
    &nuckle001_init,
    &nuckle001_wait0,
    &nuckle001_run0,
    &nuckle001_laugh0,
    &nuckle001_jump0,
    &nuckle001_wait1
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
  actionsub(p_actwk);
}


static void nuckle001_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  fp16_set_integer(&p_actwk->xposi, 0x4B8E);
  fp16_set_integer(&p_actwk->yposi, 0x17D);
  p_actwk->actflg.hflip = 1;
  set_nuckle_bgm();
  p_actwk->u.obj.timer = 119;
  p_actwk->u.obj.callback_ptr = &nuckle001_run0_init;
  set_emy_cor(&nuckle_cor_tbl);
  SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &nuckle001_col_set_tbl);
  if (p_new_actwk != 0) {
    fp16_set_integer(&p_new_actwk->xposi, 0x4B08);
    fp16_set_integer(&p_new_actwk->yposi, 0x178);
  }
}


static void nuckle001_wait0(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void nuckle001_run0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
}


static void nuckle001_run0(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) - 2;
  if ((unsigned short)xposi < 0x4B3C) {
    nuckle001_laugh0_init(p_actwk);
  }
  else {
    fp16_set_integer(&p_actwk->xposi, xposi);
    pt_chg0(p_actwk, run_pg00);
  }
}


static void nuckle001_laugh0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->actflg.hflip = 0;
  p_actwk->u.obj.timer = 95;
  p_actwk->u.obj.callback_ptr = &nuckle001_jump0_init;
  laugh_pg_init(p_actwk);
}


static void laugh_pg_init(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.pg_data_ptr = laugh_pg00;
  p_actwk->pattim = 0;
  p_actwk->patcnt = 0;
  p_actwk->patno = 28;
}


static void nuckle001_laugh0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  dec_timer(p_actwk);
}


static void nuckle001_jump0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  nuckle001_jump0_init0(p_actwk);
}


static void nuckle001_jump0_init0(SKC_sprite_status* p_actwk) {
  p_actwk->xspeed = -0x100;
  p_actwk->yspeed = -0x400;
  nuckle001_jump0_init1(p_actwk);
}


static void nuckle001_jump0_init1(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.pg_data_ptr = ball_pg00;
  p_actwk->pattim = 0;
  p_actwk->patcnt = 0;
  p_actwk->patno = 8;
  p_actwk->sprvsize = 19;
}


static void nuckle001_jump0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      if (p_actwk->u.obj.actflg0.unused2 == 0) {
        p_actwk->u.obj.actflg0.unused2 = 1;
        p_actwk->xspeed = -p_actwk->xspeed;
        p_actwk->yspeed = -p_actwk->yspeed;
      }
      else {
        p_actwk->r_no += 2;
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
        laugh_pg_init(p_actwk);
      }
    }
  }
}


static void nuckle001_wait1(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
}


static void nuckle001_col(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    nuckle_fout(p_actwk);
  }
  else {
    p_actwk->sprvs = 8;
    SKC_hitchk_data data = { 19, 32, 64, fp16_get_integer(p_actwk->xposi) };
    hitchk_skip_onscreen(p_actwk, data);
  }
}


static void nuckle010(SKC_sprite_status* p_actwk) {
  unsigned short lim_tbl[4] = {
    0x540, 0x600, 0x3900, 0x3940
  };

  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    chk_boss_set(p_actwk, lim_tbl, &nuckle010_boss_set);
    nuckle010_boss_set(p_actwk);
  }
}


static void nuckle010_boss_set(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[7] = {
    &nuckle010_init,
    &nuckle010_wait0,
    &nuckle001_wait0,
    &nuckle010_run0,
    &nuckle001_wait0,
    &nuckle001_jump0,
    &nuckle010_wait3
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
  chk_emy_foutwc0(p_actwk);
}


void nuckle_fout(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


static void nuckle010_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  g_ram.scralim_m_up = g_ram.scralim_up;
  g_ram.scralim_m_right = g_ram.scralim_right;
  g_ram.scralim_right = 0x3940;
  SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &nucksw_set_tbl010);
  if (p_new_actwk != 0) {
    p_new_actwk->u.obj.userflag = 2;
  }
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 158);
}


static void nuckle010_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  if (fp16_get_integer(g_ram.actwk[0].xposi) < 0x3990
      || g_ram.actwk[0].u.play.control_bitfield != 0
      || g_ram.actwk[0].u.play.cddat.ride == 0) {
    g_ram.scralim_up = g_ram.scra_v_posit >> 16;
    g_ram.scralim_left = g_ram.scra_h_posit >> 16;
  }
  else {
    p_actwk->r_no = 4;
    set_nuckle_bgm();
    p_actwk->u.obj.timer = 179;
    p_actwk->u.obj.callback_ptr = &nuckle010_wait1;
  }
}


static void nuckle010_wait1(SKC_sprite_status* p_actwk) {
  nuckle010_run0_init(p_actwk);
}


static void nuckle010_run0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->actflg.hflip = 1;
  p_actwk->u.obj.timer = 31;
  p_actwk->u.obj.callback_ptr = &nuckle010_wait2_init;
  g_ram.scralim_up = 0x5C0;
  set_emy_cor(&nuckle_cor_tbl);
}


static void nuckle010_run0(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 4);
  pt_chg0(p_actwk, run_pg00);
  dec_timer(p_actwk);
}


static void nuckle010_wait2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->patno = 32;
  p_actwk->u.obj.timer = 63;
  p_actwk->u.obj.callback_ptr = &nuckle010_wait2;
}


static void nuckle010_wait2(SKC_sprite_status* p_actwk) {
  nuckle010_jump0_init(p_actwk);
}


static void nuckle010_jump0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 10;
  p_actwk->actflg.hflip ^= 1;
  nuckle001_jump0_init0(p_actwk);
}


static void nuckle010_wait3(SKC_sprite_status* p_actwk) {
  SKC_set_act00_data limchg_set_tbl = {
    1,
    {
      { &chg_scr_lim_u, 0, 0 },
      { &chg_scr_lim_r, 0, 0 }
    }
  };

  pt_chg(p_actwk);
  if (p_actwk->actflg.onscreen == 0) {
    set_emy_cor((unsigned short(*)[16])&hydrocity2_color);
    set_act00(p_actwk, &limchg_set_tbl);
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &res_bgm_act;
    }
    clr_wchg_bit(p_actwk);
    set_emy_fout0(p_actwk);
  }
}


static unsigned short nuckle030_lim_tbl[8] = { 0x0176, 0x0300, 0x1C00, 0x1E00, 0x0280, 0x0280, 0x1D00, 0x1D00 };


static void nuckle030(SKC_sprite_status* p_actwk) {
  unsigned short lim_tbl[4] = {
    0x176, 0x300, 0x1B00, 0x1D00
  };

  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    chk_boss_set(p_actwk, nuckle030_lim_tbl, &nuckle030_boss_set);
    nuckle030_boss_set(p_actwk);
  }
}


static void nuckle030_boss_set(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[6] = {
    &nuckle030_init,
    &nuckle030_wait0,
    &nuckle030_wait1,
    &nuckle030_jump0,
    &nuckle030_wait1,
    &nuckle030_away0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
  actionsub(p_actwk);
}


static void nuckle030_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  p_actwk->u.obj.pg_data_ptr = laugh_pg01;
  p_actwk->u.obj.callback_ptr = &nuckle030_wait1_init0;
  p_actwk->direc.b.b0 = 31;
  scr_bgm_init(p_actwk, &nuckle030_lim_tbl[4]);
  memcpy(&g_ram.colorwk2[16], &g_ram.colorwk[16], sizeof(unsigned short) * 16);
  set_emy_cor(&nuckle_cor_tbl);
  set_act00(p_actwk, &nuckle030_col_set_tbl);
}


static void nuckle030_wait0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  chk_scr_bgm(p_actwk);
}


static void nuckle030_wait1_init0(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 4;
  p_actwk->u.obj.timer = 63;
  p_actwk->u.obj.callback_ptr = &nuckle030_jump0_init;
}


static void nuckle030_wait1(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  dec_timer(p_actwk);
}


static void nuckle030_jump0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->actflg.hflip = 1;
  p_actwk->yspeed = -0x600;
  p_actwk->xspeed = 0x140;
  nuckle001_jump0_init1(p_actwk);
}


static void nuckle030_jump0(SKC_sprite_status* p_actwk) {
  SKC_speed spd_tbl[2] = {
    { -0x100, -0x400 },
    {  0x100, -0x400 }
  };

  pt_chg(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      if (p_actwk->u.obj.actfree.nuckle030.tbl_index < 8) {
        p_actwk->xspeed = spd_tbl[p_actwk->u.obj.actfree.nuckle030.tbl_index / 4].xspeed;
        p_actwk->yspeed = spd_tbl[p_actwk->u.obj.actfree.nuckle030.tbl_index / 4].yspeed;
        p_actwk->u.obj.actfree.nuckle030.tbl_index += 4;
        p_actwk->actflg.hflip ^= 1;
      }
      else {
        p_actwk->r_no = 8;
        p_actwk->actflg.hflip = 0;
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
        p_actwk->u.obj.timer = 63;
        p_actwk->u.obj.callback_ptr = &nuckle030_wait2;
        laugh_pg_init(p_actwk);
      }
    }
  }
}


static void nuckle030_wait2(SKC_sprite_status* p_actwk) {
  nuckle030_away0_init(p_actwk);
}


static void nuckle030_away0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 10;
  p_actwk->actflg.hflip = 1;
  p_actwk->yspeed = -0x600;
  p_actwk->xspeed = 0x400;
  nuckle001_jump0_init1(p_actwk);
}


static void nuckle030_away0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset(p_actwk);
  if (p_actwk->actflg.onscreen == 0) {
    set_act00(p_actwk, &limchg030_set_tbl);
    g_ram.scralim_n_down = g_ram.scralim_m_down;
    knuckles_fout(p_actwk);
  }
}


static void knuckles_fout(SKC_sprite_status* p_actwk) {
  memcpy(&g_ram.colorwk[16], &g_ram.colorwk2[16], sizeof(unsigned short) * 16);
  divdevset2(&item_cg_tbl);
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &res_bgm_act;
  }
  clr_wchg_bit(p_actwk);
  set_emy_fout0(p_actwk);
}


static void nuckle030_col(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    nuckle_fout(p_actwk);
  }
  else {
    p_actwk->sprvs = 8;
    SKC_hitchk_data data = { 19, 256, 512, fp16_get_integer(p_actwk->xposi) };
    hitchk_skip_onscreen(p_actwk, data);
  }
}


static void cchg0320_act(SKC_sprite_status* p_actwk) {
  unsigned short tim_tbl[7] = {
    8, 4, 3, 2, 4, 8, 8
  };

  if (p_actwk->u.obj.timer-- > 0) return;

  if (p_actwk->u.obj.actfree.cchg0320_act.tbl_index < 6) {
    ++p_actwk->u.obj.actfree.cchg0320_act.tbl_index;
    p_actwk->u.obj.timer = tim_tbl[p_actwk->u.obj.actfree.cchg0320_act.tbl_index];
    unsigned short* p_color_data = cchg0320_tbl + (!(p_actwk->u.obj.actfree.cchg0320_act.tbl_index & 2) ? 0 : 32);
    memcpy(&g_ram.colorwk[32], p_color_data, sizeof(unsigned short) * 32);
  }
  else {
    if (p_actwk->u.obj.userflag != 0) {
      memcpy(&g_ram.colorwk[32], &carnivalnight_color[16], sizeof(unsigned short) * 16);
    }
    frameout(p_actwk);
  }
}


static void nuckle031(SKC_sprite_status* p_actwk) {
  unsigned short lim_tbl[4] = {
    0x720, 0xA00, 0x45C0, 0x46E0
  };

  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    chk_boss_set(p_actwk, lim_tbl, &nuckle031_boss_set);
    nuckle031_boss_set(p_actwk);
  }
}


static void nuckle031_boss_set(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[8] = {
    &nuckle031_init,
    &nuckle031_wait0,
    &nuckle031_wait1,
    &nuckle001_wait0,
    &nuckle001_jump0,
    &nuckle031_wait3,
    &nuckle031_away0,
    &nuckle031_wait4
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
  chk_emy_foutwc0(p_actwk);
}


static void nuckle031_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  g_ram.swdata = 0;
  g_ram.pl_input_lock_flag = 0xFF;
  g_ram.actwk[0].u.play.control_bitfield = 0x80;
  set_nuckle_bgm();
  set_emy_cor(&nuckle_cor_tbl);
}


static void nuckle031_wait0(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) < 0x4728) return;

  if (g_ram.actwk[0].u.play.cddat.jump == 1) {
    p_actwk->r_no = 4;
  }
}


static void nuckle031_wait1(SKC_sprite_status* p_actwk) {
  g_ram.swdata = 0x808;
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) >= 0x4760) {
    p_actwk->r_no = 6;
    g_ram.swdata = 0;
    g_ram.actwk[0].xspeed = 0;
    g_ram.actwk[0].yspeed = 0;
    g_ram.actwk[0].mspeed = 0;
    p_actwk->u.obj.timer = 31;
    p_actwk->u.obj.callback_ptr = &nuckle031_wait2;
  }
}


static void nuckle031_wait2(SKC_sprite_status* p_actwk) {
  nuckle031_jump0_init(p_actwk);
}


static void nuckle031_jump0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->u.obj.timer = 127;
  p_actwk->u.obj.callback_ptr = &nuckle031_away0_init;
  nuckle001_jump0_init0(p_actwk);
}


static void nuckle031_wait3(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  dec_timer(p_actwk);
}


static void nuckle031_away0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  p_actwk->patcnt = 0;
  p_actwk->pattim = 0;
  p_actwk->u.obj.pg_data_ptr = run_pg00;
}


static void nuckle031_away0(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 4);
  pt_chg(p_actwk);
  if (p_actwk->actflg.onscreen == 0) {
    p_actwk->r_no = 14;
    g_ram.actwk[0].u.play.control_bitfield = 0;
    set_emy_cor((unsigned short(*)[16])&carnivalnight_color);
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &res_bgm_act;
    }
  }
}


static void nuckle031_wait4(SKC_sprite_status* p_actwk) {
  g_ram.swdata = 0x404;
  if ((g_ram.scra_v_posit >> 16) + 352 < (unsigned short)fp16_get_integer(p_actwk->yposi)) {
    g_ram.pl_input_lock_flag = 0;
    clr_wchg_bit(p_actwk);
    set_emy_fout0(p_actwk);
  }
}


static void nuckle060(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[8] = {
    &nuckle060_init,
    &nuckle060_wait0,
    &nuckle001_wait0,
    &nuckle060_trow0,
    &nuckle001_wait0,
    &nuckle030_wait1,
    &nuckle030_wait1,
    &nuckle060_away0
  };

  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    act_tbl[p_actwk->r_no / 2](p_actwk);
    set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
    chk_emy_foutwc0(p_actwk);
  }
}


static void nuckle060_init(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) < (unsigned short)fp16_get_integer(p_actwk->xposi)) {
    emy_wrt_init(p_actwk, &nuckle_init_tbl);
    p_actwk->patno = 22;
    g_ram.scralim_up = 160;
    set_emy_cor(&nuckle_cor_tbl);
    set_act00(p_actwk, &nuckle060_col_set_tbl);
  }
  else {
    set_wchg_fout0(p_actwk);
  }
}


static void nuckle060_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 1) {
    p_actwk->r_no = 4;
    set_nuckle_bgm();
    p_actwk->u.obj.timer = 59;
    p_actwk->u.obj.callback_ptr = &nuckle060_wait1;
  }
}


static void nuckle060_wait1(SKC_sprite_status* p_actwk) {
  nuckle060_trow0_init(p_actwk);
}


static void nuckle060_trow0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->u.obj.pg_data_ptr = throw_pg00;
  p_actwk->u.obj.callback_ptr = &nuckle060_wait2_init;
}


static void nuckle060_trow0(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
}


static void nuckle060_wait2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->u.obj.timer = 15;
  p_actwk->u.obj.callback_ptr = &nuckle060_wait2;
  soundset(81);
  set_act00(p_actwk, &bomb06_set_tbl);
  divdevset2(&exp01_cg_tbl);
}


static void nuckle060_wait2(SKC_sprite_status* p_actwk) {
  nuckle060_lagh0_init(p_actwk);
}


static void nuckle060_lagh0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 10;
  p_actwk->u.obj.timer = 127;
  p_actwk->u.obj.callback_ptr = &nuckle060_lagh0;
  laugh_pg_init(p_actwk);
}


static void nuckle060_lagh0(SKC_sprite_status* p_actwk) {
  nuckle030_wait3_init(p_actwk);
}


static void nuckle030_wait3_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  g_ram.scr_shake_flg = 0xFF00 | g_ram.scr_shake_flg & 0x00FF;
  p_actwk->u.obj.timer = 95;
  p_actwk->u.obj.callback_ptr = &nuckle060_wait3;
  set_act05(p_actwk, &bomb06_exp_set_tbl);
}


static void nuckle060_wait3(SKC_sprite_status* p_actwk) {
  nuckle060_away0_init(p_actwk);
}


static void nuckle060_away0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 14;
  p_actwk->u.obj.pg_data_ptr = run_pg00;
  p_actwk->pattim = 0;
  p_actwk->patcnt = 0;
}


static void nuckle060_away0(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 1) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 2);
    pt_chg(p_actwk);
  }
  else {
    g_ram.DAT_08fffaa9 = 0;
    g_ram.actwk[0].u.play.control_bitfield = 0;
    g_ram.actwk[1].u.play.control_bitfield = 0;
    g_ram.scralim_m_right = 0x3B60;
    set_act05(p_actwk, &chglimr_set_tbl);
    g_ram.scralim_n_down = 328;
    clr_wchg_bit(p_actwk);
    set_emy_cor((unsigned short(*)[16])&launchbase1_color);
    set_emy_fout0(p_actwk);
  }
}


static void nuckle060_col(SKC_sprite_status* p_actwk) {
  short col_tbl[8] = {
    -64, 128, -48, 96
  };

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    nuckle_fout(p_actwk);
  }
  else {
    SKC_chk_emy_colt_result result = chk_emy_colt(p_actwk, col_tbl);
    if (result.pl) {
      p_parentwk->u.obj.actflg0.fura_right = 1;
      nuckle060_col__set_pl_data(&g_ram.actwk[0]);
    }
    if (result.pl2) {
      nuckle060_col__set_pl_data(&g_ram.actwk[1]);
    }
  }
}


static void nuckle060_col__set_pl_data(SKC_sprite_status* p_playerwk) {
  g_ram.DAT_08fffaa9 = 0xFF;
  if (p_playerwk->r_no < 6) {
    p_playerwk->u.play.control_bitfield = 0x81;
    p_playerwk->actflg.hflip = 0;
    p_playerwk->u.play.cddat.left = 0;
  }
}


static void bomb06(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &bomb06_init_tbl);
  p_actwk->r_ptr = &bomb06_fall0;
  p_actwk->xspeed = -0x200;
  p_actwk->yspeed = -0x400;
  soundset(81);
  bomb06_fall0(p_actwk);
}


static void bomb06_fall0(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  chk_emy_fout3(p_actwk);
}


static void bomb06_exp(SKC_sprite_status* p_actwk) {
  SKC_point posi_tbl[4] = {
    { 0x3BC0, 0x1A0 },
    { 0x3B80, 0x1A0 },
    { 0x3B40, 0x1A0 },
    { 0x3B00, 0x1A0 }
  };

  p_actwk->r_ptr = &bomb06_exp_move0;
  p_actwk->u.obj.callback_ptr = &set_exp01;
  fp16_set_integer(&p_actwk->xposi, posi_tbl[p_actwk->u.obj.userflag / 2].x);
  fp16_set_integer(&p_actwk->yposi, posi_tbl[p_actwk->u.obj.userflag / 2].y);
  p_actwk->u.obj.actfree.explosion.unknown39 = 32;
  p_actwk->u.obj.actfree.explosion.unknown3a = 32;
  p_actwk->u.obj.actfree.explosion.unknown3b = 32;
}


static void bomb06_exp_move0(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 4);
  dec_timer(p_actwk);
}


static void nuckle061(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[7] = {
    &nuckle061_init,
    &nuckle061_wait0,
    &nuckle061_pnch0,
    &nuckle061_lagh0,
    &nuckle061_blns0,
    &nuckle061_fall0,
    &nuckle061_fall1
  };

  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    act_tbl[p_actwk->r_no / 2](p_actwk);
    set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
    chk_emy_foutwc0(p_actwk);
  }
}


static void nuckle061_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  p_actwk->actflg.hflip = 1;
  p_actwk->patno = 32;
  set_nuckle_bgm();
  set_emy_cor(&nuckle_cor_tbl);
  set_act02(p_actwk, &nuckle061_dai_set_tbl);
}


static void nuckle061_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.unused1 == 0) return;

  p_actwk->r_no = 4;
  p_actwk->u.obj.callback_ptr = &nuckle061_wait1_init;
}


static void nuckle061_pnch0(SKC_sprite_status* p_actwk) {
  time_pg0(p_actwk, panchi_pg00);
}


static void nuckle061_wait1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 6;
  p_actwk->actflg.hflip = 0;
  laugh_pg_init(p_actwk);
}


static void nuckle061_lagh0(SKC_sprite_status* p_actwk) {
  if (g_ram.scr_shake_flg >> 8 != 0) {
    p_actwk->r_no = 8;
    p_actwk->u.obj.pg_data_ptr = balance_pg00;
    p_actwk->pattim = 0;
    p_actwk->patcnt = 0;
  }
  pt_chg(p_actwk);
}


static void nuckle061_blns0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + g_ram.DAT_08ffeee6);
    pt_chg(p_actwk);
  }
  else {
    p_actwk->r_no = 10;
    p_actwk->actflg.hflip = 1;
    p_actwk->patno = 9;
    p_actwk->xspeed = 0x200;
    p_actwk->yspeed = -0x100;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &res_bgm_act;
    }
  }
}


static void nuckle061_fall0(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(p_actwk->yposi) >= g_ram.waterposi) {
    soundset(57);
    p_actwk->r_no = 12;
  }
  nuckle061_fall1(p_actwk);
}


static void nuckle061_fall1(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + g_ram.DAT_08ffeee6);
  speedsetg20(p_actwk);
}


static void nuckle061_dai(SKC_sprite_status* p_actwk) {
  struct {
    short init;
    short accel;
  }
  spd_tbl[4] = {
    { 0x100, 0x10 },
    {  0xC0,  0xC },
    {  0x80,  0x8 },
    {  0x40,  0x4 }
  };

  enemy_init0(p_actwk, &nuckle061_dai_init_tbl);
  p_actwk->r_ptr = &nuckle061_dai_wait0;
  p_actwk->u.obj.actfree.nuckle061_dai.xspeed_init = spd_tbl[p_actwk->u.obj.userflag / 2].init;
  p_actwk->u.obj.actfree.nuckle061_dai.xspeed_accel = spd_tbl[p_actwk->u.obj.userflag / 2].accel;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + p_actwk->u.obj.userflag * 16);
  p_actwk->u.obj.actfree.nuckle061_dai.xposi_init = fp16_get_integer(p_actwk->xposi);
}


static void nuckle061_dai_wait0(SKC_sprite_status* p_actwk) {
  if (g_ram.scr_shake_flg >> 8 != 0) {
    p_actwk->r_ptr = &nuckle061_dai_move0;
    p_actwk->xspeed = p_actwk->u.obj.actfree.nuckle061_dai.xspeed_init;
    p_actwk->u.obj.actfree.nuckle061_dai.remaining_wobbles = 6;
  }
  chk_emy_fout3(p_actwk);
}


static void nuckle061_dai_move0(SKC_sprite_status* p_actwk) {
  struct {
    short init;
    short accel;
  }
  spd_tbl[4] = {
    { 0x200, 0x20 },
    { 0x180, 0x18 },
    { 0x100, 0x10 },
    {  0x80,  0x8 }
  };

  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + g_ram.DAT_08ffeee6);
  short xposi_init = p_actwk->u.obj.actfree.nuckle061_dai.xposi_init;
  short accel = p_actwk->u.obj.actfree.nuckle061_dai.xspeed_accel;
  bool left = (unsigned short)fp16_get_integer(p_actwk->xposi) < (unsigned short)xposi_init;
  if (!left) {
    accel = -accel;
  }
  p_actwk->xspeed += accel;
  if (left != p_actwk->u.obj.actfree.nuckle061_dai.prev_dir) {
    p_actwk->u.obj.actfree.nuckle061_dai.prev_dir = left;
    if (p_actwk->u.obj.actfree.nuckle061_dai.remaining_wobbles == 3) {
      p_actwk->u.obj.actfree.nuckle061_dai.xspeed_init = spd_tbl[p_actwk->u.obj.userflag / 2].init;
      p_actwk->u.obj.actfree.nuckle061_dai.xspeed_accel = spd_tbl[p_actwk->u.obj.userflag / 2].accel;
      p_actwk->xspeed = p_actwk->u.obj.actfree.nuckle061_dai.xspeed_init;
    }
    --p_actwk->u.obj.actfree.nuckle061_dai.remaining_wobbles;
    if (p_actwk->u.obj.actfree.nuckle061_dai.remaining_wobbles == 0) {
      p_actwk->r_ptr = &nuckle061_dai_fall0;
      SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
      p_parentwk->u.obj.actflg0.fura_right = 1;
    }
  }
  speedset2(p_actwk);
  if (p_actwk->u.obj.userflag == 0) {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    fp16_set_integer(&p_parentwk->xposi, fp16_get_integer(p_actwk->xposi));
  }
  chk_emy_fout3(p_actwk);
}


static void nuckle061_dai_fall0(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + g_ram.DAT_08ffeee6);
  speedsetg20(p_actwk);
  chk_emy_fout3(p_actwk);
}


void tekotu(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &tekotu_init_tbl);
  if (p_actwk->actflg.vflip == 1) {
    p_actwk->actflg.vflip = 0;
    SET_BIT(p_actwk->sproffset, 15);
  }
  if (p_actwk->actflg.hflip == 1) {
    p_actwk->actflg.hflip = 0;
    p_actwk->sprpri = PRI_0;
  }
  p_actwk->r_ptr = &tekotu_wait0;
  tekotu_wait0(p_actwk);
}


static void tekotu_wait0(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + g_ram.DAT_08ffeee6);
  frameoutchk(p_actwk);
}


static SKC_sprite_pattern* tekotu_pt[2] = {
  &tekotu_pt00,
  &tekotu_pt01
};


static SKC_sprite_pattern tekotu_pt00 = {
  1,
  {
    { -16, 15, 0x0000, -16 }
  }
};
static SKC_sprite_pattern tekotu_pt01 = {
  8,
  {
    { -128, 15, 0x0000, -16 },
    {  -96, 15, 0x0000, -16 },
    {  -64, 15, 0x0000, -16 },
    {  -32, 15, 0x0000, -16 },
    {    0, 15, 0x0000, -16 },
    {   32, 15, 0x0000, -16 },
    {   64, 15, 0x0000, -16 },
    {   96, 15, 0x0000, -16 }
  }
};


static void nuckle070(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[8] = {
    &nuckle070_init,
    &nuckle070_wait0,
    &nuckle070_run0,
    &nuckle070_wait1,
    &nuckle070_run1,
    &nuckle070_jump0,
    &nuckle070_jump0,
    &nuckle070_run2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &nuckle_wrt_tbl);
  chk_emy_foutwc0(p_actwk);
}


static void nuckle070_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  CLEAR_BIT(p_actwk->sproffset, 15);
  p_actwk->u.obj.timer = 119;
  p_actwk->u.obj.pg_data_ptr = run_pg00;
  fp16_set_integer(&p_actwk->xposi, 0x2B0);
  fp16_set_integer(&p_actwk->yposi, 0x66C);
  p_actwk->xspeed = 0x200;
  memcpy(&g_ram.colorwk2[16], &g_ram.colorwk[16], sizeof(unsigned short) * 16);
  set_emy_cor(&nuckle_cor_tbl);
}


static void nuckle070_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_no = 4;
}


static void nuckle070_run0(SKC_sprite_status* p_actwk) {
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) < 0x360) {
    pt_chg(p_actwk);
    speedset2(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    set_act05(p_actwk, &nk0700_set_tbl);
    nuckle070_wait1(p_actwk);
  }
}


static void nuckle070_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 0) return;

  p_actwk->r_no = 8;
}


static void nuckle070_run1(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset2(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xposi = fp16_get_integer(p_parentwk->xposi) - 40;
  if ((unsigned short)xposi <= (unsigned short)fp16_get_integer(p_actwk->xposi)) {
    fp16_set_integer(&p_actwk->xposi, xposi);
    p_actwk->r_no = 10;
    p_actwk->sprvsize = 23;
    p_actwk->xspeed = 0x100;
    p_actwk->yspeed = -0x400;
    p_actwk->u.obj.callback_ptr = &nk0700_jump1_init;
    pg_init(p_actwk, ball_pg00);
    nuckle070_jump0(p_actwk);
  }
}


static void nuckle070_jump0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  speedset(p_actwk);
  emy_fall_col(p_actwk);
  actionsub(p_actwk);
}


static void nk0700_jump1_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  p_actwk->sprvsize = 19;
  p_actwk->yspeed = -0x300;
  p_actwk->u.obj.callback_ptr = &nuckle070_jump1;
}


static void nuckle070_jump1(SKC_sprite_status* p_actwk) {
  nk0700_run2_init(p_actwk);
}


static void nk0700_run2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 14;
  p_actwk->xspeed = 0x200;
  p_actwk->yspeed = 0;
  pg_init(p_actwk, run_pg00);
}


static void nuckle070_run2(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    knuckles_fout(p_actwk);
  }
  else {
    pt_chg(p_actwk);
    speedset2(p_actwk);
  }
}


void ev0700(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.character == KNUCKLES || g_ram.markerno != 0 || g_ram.cartridge != 0) {
    nuckle_fout(p_actwk);
  }
  else {
    ev0700_move(p_actwk);
  }
}


static void ev0700_move(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler jmp_tbl[7] = {
    &ev0700_init,
    &ev0700_col0,
    &ev0700_wait0,
    &ev0700_wait1,
    &ev0700_scrd0,
    &ev0700_wait2,
    &ev0700_fout0
  };

  jmp_tbl[g_ram.DAT_08fffab8_bitfield / 2](p_actwk);
}


static void ev0700_init(SKC_sprite_status* p_actwk) {
  g_ram.DAT_08fffab8_bitfield = 2;
  if (g_ram.actwk[1].r_ptr != 0) {
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &ev0700m;
      return;
    }
  }
  ev0700_col0(p_actwk);
}


static void ev0700_col0(SKC_sprite_status* p_actwk) {
  if (0x389 > (unsigned short)fp16_get_integer(g_ram.actwk[0].xposi)) return;

  fp16_set_integer(&g_ram.actwk[0].xposi, 0x389);
  g_ram.DAT_08fffab8_bitfield = 4;
  g_ram.actwk[0].actflg.hflip = 0;
  g_ram.actwk[0].u.play.cddat.left = 0;
  g_ram.pl_input_lock_flag = 0xFF;
  g_ram.swdata = 0;
  pl_spd_clr(&g_ram.actwk[0]);
  set_nuckle_bgm();
}


static void ev0700_wait0(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.cddat.jump == 1) return;

  g_ram.DAT_08fffab8_bitfield = 6;
  p_actwk->u.obj.timer = 32;
  ev0700_wait1(p_actwk);
}


static void ev0700_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  g_ram.DAT_08fffab8_bitfield = 8;
  g_ram.pl_scr_lock_flag = 0xFF;
  g_ram.swdata = 0x202;
  ev0700_scrd0(p_actwk);
}


static void ev0700_scrd0(SKC_sprite_status* p_actwk) {
  g_ram.scra_v_posit += 0x20000;
  if (g_ram.scra_v_posit >> 16 >= 0x5B0) {
    g_ram.DAT_08fffab8_bitfield = 10;
    ev0700_wait2(p_actwk);
  }
}


static void ev0700_wait2(SKC_sprite_status* p_actwk) {
}


static void ev0700_fout0(SKC_sprite_status* p_actwk) {
  g_ram.DAT_08fffab8_bitfield = 0;
  g_ram.pl_input_lock_flag = 0;
  g_ram.pl2_input_lock_flag = 0;
  g_ram.pl_scr_lock_flag = 0;
  g_ram.swdata = 0;
  g_ram.swdata2_auto = 0;
  g_ram.actwk[1].mstno = 5;
  g_ram.markerno = 1;
  g_ram.plxposi_s = 0x190;
  g_ram.plyposi_s = 0x56C;
  playsave1(p_actwk);
  set_emy_fout0(p_actwk);
}


static void ev0700m(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffab8_bitfield < 4 && 0x371 > (unsigned short)fp16_get_integer(g_ram.actwk[1].xposi)) return;

  fp16_set_integer(&p_actwk->xposi, 0x371);
  p_actwk->r_ptr = &ev0700m_wait0;
  g_ram.pl2_input_lock_flag = 0xFF;
  g_ram.swdata2_auto = 0;
  pl_spd_clr(&g_ram.actwk[1]);
  ev0700m_wait0(p_actwk);
}


static void ev0700m_wait0(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffab8_bitfield != 0) {
    if (g_ram.DAT_08fffab8_bitfield >= 4) {
      if (0x371 <= (unsigned short)fp16_get_integer(g_ram.actwk[1].xposi)) {
        g_ram.actwk[1].mstno = 8;
        pl_spd_clr(&g_ram.actwk[1]);
      }
    }
    else if (g_ram.actwk[1].actflg.onscreen == 1) {
      p_actwk->r_ptr = &ev0700m;
      g_ram.pl2_input_lock_flag = 0;
      g_ram.swdata2_auto = 0;
    }
  }
  else {
    g_ram.pl2_input_lock_flag = 0;
    g_ram.swdata2_auto = 0;
    frameout(p_actwk);
  }
}


void sw0700(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &sw0700_init_tbl);
  set_act05(p_actwk, &shut07_set_tbl);
  bool skip = g_ram.markerno != 0 || g_ram.actwk[0].u.play.character == KNUCKLES;
  p_actwk->r_ptr = skip ? &sw0700_wait00 : &sw0700_wait0;
  actionsub(p_actwk);
}


static void sw0700_wait0(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffab8_bitfield < 10) {
    actionsub(p_actwk);
  }
  else {
    p_actwk->r_ptr = &sw0700_wait1;
    unlze_moduled(&g_vram[0xA000], sw0700_cg);
    SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &nuckles_set_tbl);
    if (p_new_actwk != 0) {
      p_new_actwk->u.obj.userflag = 28;
    }
    sw0700_wait1(p_actwk);
  }
}


static void sw0700_wait1(SKC_sprite_status* p_actwk) {
  if (g_ram.DAT_08fffaa4_obj != 0) {
    SKC_sprite_status* p_nucklewk = &g_ram.actwk[g_ram.DAT_08fffaa4_obj];
    if (emy_col_a1(p_actwk, p_nucklewk, knuckle_col_tbl)) {
      p_actwk->r_ptr = &sw0700_wait2;
      p_actwk->u.obj.timer = 1;
      p_actwk->patno = 1;
      p_actwk->u.obj.actflg0.unused1 = 1;
      g_ram.DAT_08fffaa9 = 0xFF;
      soundset(91);
    }
  }
  actionsub(p_actwk);
}


static void sw0700_wait2(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.unused1 = 0;
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &tim_act;
    p_actwk->u.obj.timer = 95;
    p_actwk->u.obj.callback_ptr = &sw0700_wait3;
    p_actwk->patno = 0;
  }
  actionsub(p_actwk);
}


static void sw0700_wait3(SKC_sprite_status* p_actwk) {
  sw0700_wait00_init(p_actwk);
}


static void sw0700_wait00_init(SKC_sprite_status* p_actwk) {
  g_ram.DAT_08fffab8_bitfield = 12;
  p_actwk->r_ptr = &sw0700_wait00;
}


static void sw0700_wait00(SKC_sprite_status* p_actwk) {
  chk_nucksw_ride(p_actwk);
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->r_ptr = &sw0700_wait01;
    p_actwk->patno = 1;
    soundset(91);
    if (p_actwk->u.obj.actflg0.unused2 == 0) {
      p_actwk->u.obj.actflg0.unused1 = 1;
      g_ram.DAT_08fffaa9 = !g_ram.DAT_08fffaa9;
      soundset(91);
    }
  }
  chk_emy_fout0(p_actwk);
}


static void sw0700_wait01(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actflg0.unused1 = 0;
  chk_nucksw_ride(p_actwk);
  if (p_actwk->u.obj.cddat.plride == 0 && p_actwk->u.obj.cddat.pl2ride == 0) {
    p_actwk->r_ptr = &sw0700_wait00;
    p_actwk->patno = 0;
  }
  chk_emy_fout0(p_actwk);
}


static void nk0700(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &nk0700_init_tbl);
  p_actwk->r_ptr = &nk0700_apar0;
  fp16_set_integer(&p_actwk->xposi, 0x374);
  fp16_set_integer(&p_actwk->yposi, 0x66C);
  p_actwk->xspeed = 0x200;
  p_actwk->u.obj.timer = 7;
  p_actwk->u.obj.callback_ptr = &nk0700_kyoro0_init;
  nk0700_apar0(p_actwk);
}


static void nk0700_apar0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  dec_timer(p_actwk);
  actionsub(p_actwk);
}


static void nk0700_kyoro0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &nk0700_kyoro0;
  p_actwk->u.obj.callback_ptr = &nk0700_away0_init;
  SET_BIT(p_actwk->sproffset, 15);
}


static void nk0700_kyoro0(SKC_sprite_status* p_actwk) {
  time_pg0(p_actwk, nk0700_pg00);
  actionsub(p_actwk);
}


static void nk0700_away0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &nk0700_apar0;
  p_actwk->xspeed = -0x400;
  p_actwk->u.obj.timer = 15;
  p_actwk->u.obj.callback_ptr = &nk0700_away0;
  CLEAR_BIT(p_actwk->sproffset, 15);
}


static void nk0700_away0(SKC_sprite_status* p_actwk) {
  nk0700_fout(p_actwk);
}


static void nk0700_fout(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_parentwk->u.obj.actflg0.fura_right = 1;
  set_emy_fout0(p_actwk);
}


static void shut07(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &shut07_init_tbl);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_parentwk->u.obj.ko = p_actwk - g_ram.actwk;
  p_actwk->r_ptr = &shut07_wait0;
  fp16_set_integer(&p_actwk->xposi, 0x390);
  fp16_set_integer(&p_actwk->yposi, 0x620);
  if (g_ram.DAT_08fffaa9 != 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 64);
  }
  shut07_wait0(p_actwk);
}


static void shut07_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.unused1 == 0) {
    chk_shut07_ride(p_actwk);
    SKC_chk_distance_result result = chk_distance0(p_actwk, &g_ram.actwk[0]);
    if (g_ram.DAT_08fffaa9 == 0
        || result.right
        || (unsigned short)result.xdistance >= 64
        || (unsigned short)result.ydistance >= 96) {
      chk_oya_die0(p_actwk);
      return;
    }
    else { // open
      g_ram.DAT_08fffaa9 = 0;
    }
  }
  p_actwk->r_ptr = &shut07_move0;
  p_parentwk->u.obj.actflg0.unused2 = 1;
  p_actwk->yspeed = g_ram.DAT_08fffaa9 != 0 ? 0x100 : -0x100;
  p_actwk->u.obj.timer = 63;
  p_actwk->u.obj.callback_ptr = &shut07_wait0_init;
  shut07_move0(p_actwk);
}


static void shut07_move0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  chk_shut07_ride(p_actwk);
  dec_timer(p_actwk);
  chk_oya_die0(p_actwk);
}


static void shut07_wait0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &shut07_wait0;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_parentwk->u.obj.actflg0.unused2 = 0;
}


static unsigned short nuckle071_lim_tbl[8] = { 0x648, 0x848, 0x2D0, 0x4D0, 0x748, 0x748, 0x3D0, 0x3D0 };


static void nuckle071(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.character != KNUCKLES) {
    if (g_ram.markerno >= 7) {
      nuckle_fout(p_actwk);
    }
    else {
      chk_boss_set(p_actwk, nuckle071_lim_tbl, &nuckle071_boss_set);
      nuckle071_boss_set(p_actwk);
    }
  }
  else {
    set_act00(p_actwk, &sw0701_set_tbl);
    set_emy_fout0(p_actwk);
  }
}


static void nuckle071_boss_set(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &nuckle071_init,
    &nuckle071_wait0,
    &nuckle071_wait1,
    &nuckle071_turn0,
    &nuckle071_fout0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  set_emy_wchg(p_actwk, &nk0701_wrt_tbl);
  chk_emy_foutwc0(p_actwk);
}


static void nuckle071_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nk0701_init_tbl);
  p_actwk->u.obj.callback_ptr = &nuckle071_wait1_init;
  g_ram.scralim_m_left = g_ram.scralim_left;
  g_ram.scralim_b_left = nuckle071_lim_tbl[6];
  set_nuckle_bgm();
  g_ram.DAT_08ffeee8 = 0xFF;
  set_emy_cor(&nuckle_cor_tbl);
  set_act00(p_actwk, &sw0701_set_tbl);
}


static void nuckle071_wait0(SKC_sprite_status* p_actwk) {
  if (g_ram.scra_h_posit >> 16 >= g_ram.scralim_b_left) {
    nuckle071_wait1_init(p_actwk);
  }
  else {
    g_ram.scralim_left = g_ram.scra_h_posit >> 16;
  }
}


static void nuckle071_wait1_init(SKC_sprite_status* p_actwk) {
  g_ram.scralim_left = g_ram.scralim_b_left;
  p_actwk->r_no = 4;
  p_actwk->u.obj.timer = 59;
  g_ram.pl_input_lock_flag = 0xFF;
  g_ram.pl2_input_lock_flag = 0xFF;
  g_ram.swdata = 0;
  g_ram.swdata2_auto = 0;
}


static void nuckle071_wait1(SKC_sprite_status* p_actwk) {
  bool pl2_not_jumping = g_ram.actwk[1].r_ptr == 0
      || g_ram.actwk[1].actflg.onscreen == 0
      || g_ram.actwk[1].u.play.cddat.jump == 0;
  if (p_actwk->u.obj.timer-- == 0 || (g_ram.actwk[0].u.play.cddat.jump == 0 && pl2_not_jumping)) {
    p_actwk->r_no = 6;
    p_actwk->u.obj.callback_ptr = &nuckle071_fout0_init;
    p_actwk->u.obj.actfree.nuckle071.timer_init = 16;
    p_actwk->u.obj.timer = 0;
    p_actwk->u.obj.actfree.nuckle071.yspeed_mod = 1;
    nuckle071_wait1__set_flag(&g_ram.actwk[0]);
    if (g_ram.actwk[1].r_ptr != 0) {
      nuckle071_wait1__set_flag(&g_ram.actwk[1]);
    }
  }
}


static void nuckle071_wait1__set_flag(SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.control_bitfield = 0x81;
  p_playerwk->mstno = 5;
  pl_spd_clr(p_playerwk);
}


static void nuckle071_turn0(SKC_sprite_status* p_actwk) {
  chk_nk0720_plpt(p_actwk);
  if (p_actwk->patcnt >= 8) {
    set_cont_se(-38);
    set_housi(p_actwk);
  }
  int ret = time_pg0(p_actwk, turnsw_pg00);
  if (ret != 0) {
    if (p_actwk->patcnt == 12) {
      g_ram.actwk[0].mstno = 20;
      if (g_ram.actwk[1].actflg.onscreen == 1) {
        g_ram.actwk[1].mstno = 20;
      }
    }
    if (p_actwk->patno == 2) {
      ++p_actwk->u.obj.actfree.nuckle071.yspeed_mod;
      p_actwk->u.obj.actfree.nuckle071.timer_init -= 4;
      soundset(91);
    }
  }
}


static void nuckle071_fout0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &ev0701;
  }
  if (g_ram.actwk[1].actflg.onscreen == 1) {
    result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &ev0701;
      result.actwk_ptr->u.obj.userflag = 2;
    }
  }
  nuckle071_fout0(p_actwk);
}


static void nuckle071_fout0(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    knuckles_fout(p_actwk);
  }
  else {
    set_housi(p_actwk);
  }
  //set_emy_cor(mushroomhill2_color);
  //knuckles_fout(p_actwk);
}


static void sw0701(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &sw0701_init_tbl);
  p_actwk->r_ptr = &sw0701_wait0;
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    p_actwk->r_ptr = &frameoutchk;
    p_actwk->sproffset = 0x8528;
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    p_actwk->u.obj.flagwork_index = p_parentwk->u.obj.flagwork_index;
  }
  unlze_moduled(&g_vram[0xA500], sw0701_cg);
}


static void sw0701_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->patno = p_parentwk->patno != 2 ? 0 : 1;
  chk_oya_die0(p_actwk);
}


static void housi071(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &housi071_init_tbl);
  p_actwk->r_ptr = &housi071_wait0;
  short xposi = random() & 0x1FF;
  if (xposi >= 320) {
    xposi = (xposi & 0x3F) * 4;
  }
  xposi += g_ram.scra_h_posit_copy >> 16;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (g_ram.scra_v_posit_copy >> 16) + 232;
  fp16_set_integer(&p_actwk->yposi, yposi);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->yspeed = -(p_parentwk->u.obj.actfree.nuckle071.yspeed_mod * 2);
  housi071_wait0(p_actwk);
}


static void housi071_wait0(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + p_actwk->yspeed);
  if ((g_ram.scra_v_posit >> 16) - 8 >= fp16_get_integer(p_actwk->yposi)) {
    nuckle_fout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void ev0701(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &ev0701_move0;
  unsigned char actid = p_actwk->u.obj.userflag == 0 ? 0 : 1;
  p_actwk->u.obj.ko = actid;
  p_actwk->yspeed = -0x1000;
  SKC_sprite_status* p_playerwk = &g_ram.actwk[actid];
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(g_ram.actwk[actid].xposi));
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(g_ram.actwk[actid].yposi));
  g_ram.actwk[actid].u.play.control_bitfield = 0x81;
  g_ram.actwk[actid].mstno = 15;
  g_ram.actwk[actid].actflg.vflip = 0;
  SET_BIT(g_ram.actwk[actid].sproffset, 15);
  g_ram.fast_scroll_flag = 0xFF;
}


static void ev0701_move0(SKC_sprite_status* p_actwk) {
  set_cont_se(-38);
  speedsetg20(p_actwk);
  SKC_sprite_status* p_playerwk = &g_ram.actwk[p_actwk->u.obj.ko];
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_actwk->xposi));
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_actwk->yposi));
  if (p_actwk->yspeed >= 0) {
    g_ram.pl_input_lock_flag = 0;
    g_ram.pl2_input_lock_flag = 0;
    g_ram.swdata = 0;
    g_ram.swdata2_auto = 0;
    p_playerwk->u.play.control_bitfield = 0;
    CLEAR_BIT(p_playerwk->sproffset, 15);
    p_playerwk->mstno = 0;
    p_playerwk->mspeed = 16;
    g_ram.fast_scroll_flag = 0;
    g_ram.DAT_08ffeee8 = 0;
    g_ram.markerno = 7;
    g_ram.plxposi_s = 0x52A;
    g_ram.plyposi_s = 0x5AC;
    playsave1(p_actwk);
    frameout(p_actwk);
  }
}


static void nuckle072(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.character != KNUCKLES || g_ram.markerno != 0 || g_ram.cartridge == 0) {
    nuckle_fout(p_actwk);
  }
  else {
    p_actwk->r_ptr = &nuckle072_move;
    nuckle072_move(p_actwk);
  }
}


static void nuckle072_move(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[7] = {
    &nuckle072_init,
    &nuckle072_wait0,
    &nuckle072_wait1,
    &nuckle072_jump0,
    &nuckle072_fall0,
    &nuckle072_land0,
    &nuckle072_run0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);

  switch (p_actwk->u.obj.actfree.nuckle072.wrt_index) {
    case 0:
      p_actwk->patbase = nkopen_pt;
      set_emy_wchg(p_actwk, &nkopen_wrt_tbl);
      break;
    case 2:
      p_actwk->patbase = knuckles_pt;
      nkmiles_wrt(p_actwk);
      break;
    case 4:
      p_actwk->patbase = nk0931_pt;
      set_emy_wchg(p_actwk, &nk0931_wrt_tbl);
      break;
  }

  actionsub(p_actwk);
}


static void nuckle072_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nk0702_init_tbl);
  p_actwk->u.obj.timer = 239;
  g_ram.actwk[0].u.play.control_bitfield = 0x83;
  g_ram.scra_h_posit = 0x560 << 16 | g_ram.scra_h_posit & 0x0000FFFF;
  g_ram.scra_v_posit = 0x948 << 16 | g_ram.scra_v_posit & 0x0000FFFF;
  g_ram.pl_scr_lock_flag = 0xFF;
  g_ram.ranum = g_ram.systemtimer;
  g_ram.DAT_08fff711 = 0;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &chk_pause;
  }
  set_act05(p_actwk, &friend07_set_tbl);
  memcpy(&g_ram.colorwk2[16], egbomb_cor_tbl, sizeof(unsigned short) * 16);
}


static void nuckle072_wait0(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 0)) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &egbomb07;
      }
    }
    pt_chg0(p_actwk, relax_pg00);
  }
  else {
    p_actwk->r_no = 4;
    p_actwk->patno = 4;
    pg_init(p_actwk, relax_pg01);
  }
}


static void nuckle072_wait1(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 1)) {
    time_pg(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    p_actwk->u.obj.actfree.nuckle072.wrt_index = 2;
    p_actwk->patno = 141;
    p_actwk->xspeed = -0x100;
    p_actwk->yspeed = -0x100;
    nuckle072_jump0(p_actwk);
  }
}


static void nuckle072_jump0(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 2)) {
    p_actwk->yspeed += 8;
    speedset2(p_actwk);
  }
  else {
    p_actwk->r_no = 8;
    p_actwk->u.obj.actfree.nuckle072.wrt_index = 4;
    p_actwk->patno = 3;
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 8);
    p_actwk->mspeed = 19;
    p_actwk->xspeed = -0x100;
    p_actwk->yspeed = 0;
    nuckle072_fall0(p_actwk);
  }
}


static void nuckle072_fall0(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset < 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    p_actwk->r_no = 10;
    p_actwk->u.obj.callback_ptr = &nuckle072_run0_init;
    pg_init(p_actwk, land_pg02);
  }
}


static void nuckle072_land0(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
}


static void nuckle072_run0_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 12;
  p_actwk->u.obj.actfree.nuckle072.wrt_index = 2;
  p_actwk->patno = 7;
  p_actwk->xspeed = 0;
  p_actwk->yspeed = 0;
  pg_init(p_actwk, run_pg03);
}


static void nuckle072_run0(SKC_sprite_status* p_actwk) {
  short xspeed = p_actwk->xspeed + 0xC;
  if ((unsigned short)xspeed <= 0x400) {
    p_actwk->xspeed = xspeed;
  }
  speedset2(p_actwk);
  pt_chgs(p_actwk);
  if ((g_ram.scra_h_posit >> 16) + 384 < (unsigned short)fp16_get_integer(p_actwk->xposi)) {
    end_open(p_actwk);
  }
}


static void end_open(SKC_sprite_status* p_actwk) {
  g_ram.markerno = 1;
  g_ram.plxposi_s = 0x6F4;
  g_ram.plyposi_s = 0x9EC;
  playsave1(p_actwk);
  g_ram.pltime_s.hours = 0;
  g_ram.pltime_s.minutes = 0;
  g_ram.pltime_s.seconds = 0;
  g_ram.pltime_s.frames = 0;
  g_ram.stageno = MUSHROOM_HILL_ACT_1;
  g_ram.stageno_i = MUSHROOM_HILL_ACT_1;
  g_ram.gameflag = 1;
  set_emy_fout0(p_actwk);
}


static void chk_pause(SKC_sprite_status* p_actwk) {
  if (are_buttons_pressed(g_ram.swdata1, PAD_S) || are_buttons_pressed(g_ram.swdata2, PAD_S)) {
    end_open(p_actwk);
  }
}


static void friend07(SKC_sprite_status* p_actwk) {
  short posi_tbl[8] = {
    0x5F0, 0x600, 0x610, 0x620, 0x660, 0x670, 0x680, 0x690
  };
  struct {
    unsigned short left;
    unsigned short right;
  }
  lim_tbl[2] = {
    { 0x5E8, 0x628 },
    { 0x658, 0x698 }
  };
  SKC_friend07_init_data risu_tbl = {
    &risu_move0,
    rickypat,
    0x580
  };
  SKC_friend07_init_data flicky_tbl = {
    &flicky_move0,
    cuckyflickypat,
    0x592
  };

  fp16_set_integer(&p_actwk->xposi, posi_tbl[p_actwk->u.obj.userflag / 2]);
  fp16_set_integer(&p_actwk->yposi, 0x9F4);
  int index = p_actwk->u.obj.userflag < 8 ? 0 : 1;
  p_actwk->u.obj.actfree.friend07.left_limit = lim_tbl[index].left;
  p_actwk->u.obj.actfree.friend07.right_limit = lim_tbl[index].right;
  SKC_friend07_init_data* p_data = !(p_actwk->u.obj.userflag & 2) ? &risu_tbl : &flicky_tbl;
  p_actwk->sprvsize = !(p_actwk->u.obj.userflag & 2) ? 12 : 10;
  p_actwk->r_ptr = p_data->r_ptr;
  p_actwk->patbase = p_data->patbase;
  p_actwk->sproffset = p_data->sproffset;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_4;
  p_actwk->sprvs = 16;
  p_actwk->sprhs = 16;
}


static void risu_move0(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  p_actwk->patno = p_actwk->yspeed < 0 ? 1 : 0;
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      set_friend07_spd(p_actwk);
    }
  }
  actionsub(p_actwk);
}


static void flicky_move0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      set_friend07_spd(p_actwk);
    }
  }
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 1;
    ++p_actwk->patno;
    p_actwk->patno &= 1;
  }
  actionsub(p_actwk);
}


static void egbomb07(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &egbomb07_init_tbl);
  p_actwk->r_ptr = &egbomb07_wait0;
  p_actwk->sprvsize = 16;
  short xposi = (g_ram.scra_h_posit >> 16) + 160;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (g_ram.scra_v_posit >> 16) - 64;
  fp16_set_integer(&p_actwk->yposi, yposi);
  soundset(81);
  set_act00(p_actwk, &egbomb07_spark_set_tbl);
  divdevset2(&exp01_cg_tbl);
  unlze_moduled(&g_vram[0xA5C0], egbomb07_cg);
}


static void egbomb07_wait0(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  if (p_actwk->actflg.onscreen == 1 && p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      SET_BIT(g_ram.DAT_08fffab8_bitfield, 0);
      soundset(93);
      p_actwk->yspeed = -(p_actwk->yspeed / 4);
      if (p_actwk->yspeed >= -0x100) {
        p_actwk->r_ptr = &egbomb07_wait1;
        p_actwk->u.obj.timer = 119;
        bgmset(-31);
      }
    }
  }
  actionsub(p_actwk);
}


static void egbomb07_wait1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &egbomb07_wait2;
    p_actwk->u.obj.cddat.die = 1;
    SET_BIT(g_ram.DAT_08fffab8_bitfield, 1);
    soundset(78);
    memcpy(g_ram.colorwk2, g_ram.colorwk, sizeof(unsigned short) * 16);
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
      p_actwk->r_ptr = &flashout_act;
      p_actwk->u.obj.fade.timer_init = 7;
      p_actwk->u.obj.userflag = 0xFF;
      set_act05(p_actwk, &egbomb07_exp_set_tbl);
    }
  }
  actionsub(p_actwk);
}


static void egbomb07_wait2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_childwk->u.obj.actflg0.end == 1) {
    SET_BIT(g_ram.DAT_08fffab8_bitfield, 2);
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &egjr07;
      memcpy(&g_ram.colorwk2[16], skysanctuary1_color, sizeof(unsigned short) * 16);
      set_emy_fout0(p_actwk);
    }
  }
}


static void egbomb07_spark(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &egbomb07_spark_wait0;
  enemy_init2(p_actwk, &egbomb07_spark_init_tbl);
}


static void egbomb07_spark_wait0(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, egbomb07_spark_pg00);
  ko_offset0(p_actwk);
  if (!(g_ram.systemtimer & 7)) {
    set_act05(p_actwk, &egbomb07_smoke_set_tbl);
  }
  chk_oya_die0(p_actwk);
}


static void egbomb07_smoke(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &egbomb07_smoke_init_tbl);
  p_actwk->r_ptr = &egbomb07_smoke_wait0;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  p_actwk->xspeed = (short)(random() & 0x7F) - 63;
  p_actwk->yspeed = -0x100;
  egbomb07_smoke_wait0(p_actwk);
}


static void egbomb07_smoke_wait0(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  pt_chg0(p_actwk, egbomb07_smoke_pg00);
  chk_oya_die0(p_actwk);
}


static void egbomb07_exp(SKC_sprite_status* p_actwk) {
  SKC_point ofs_tbl[10] = {
    {   0,   0 },
    {   8,  -8 },
    {  -6, -12 },
    { -10,   4 },
    {   8,  10 },
    {   0,  24 },
    {   8, -24 },
    { -12, -32 },
    { -22,  -4 },
    {  24,   0 }
  };

  enemy_init0(p_actwk, &exp01_init_tbl);
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  soundset(-76);
  p_actwk->u.obj.timer = p_actwk->u.obj.userflag / 2;
  SKC_point point = ofs_tbl[p_actwk->u.obj.userflag / 2];
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + point.x);
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + point.y);
  p_actwk->r_ptr = &egbomb07_exp_wait0;
  egbomb07_exp_wait0(p_actwk);
}


static void egbomb07_exp_wait0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_ptr = &exp01_pchg;
  exp01_pchg(p_actwk);
}


static void egjr07(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &egjr0a_init_tbl02);
  p_actwk->r_ptr = &egjr07_wait0;
  short xposi = (g_ram.scra_h_posit >> 16) + 272;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (g_ram.scra_v_posit >> 16) - 96;
  fp16_set_integer(&p_actwk->yposi, yposi);
  bgmset(25);
  set_act00(p_actwk, &egjr0a_02_set_tbl);
  unlze_moduled(&g_vram[0xA000], egjr0a_cg);
}


static void egjr07_wait0(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 1);
  if ((g_ram.scra_v_posit >> 16) + 64 < fp16_get_integer(p_actwk->yposi)) {
    p_actwk->r_ptr = &egjr07_wait1;
    p_actwk->u.obj.timer = 127;
    bs00m0_puka_init(p_actwk);
  }
  egjr0a_pg(p_actwk);
  actionsub(p_actwk);
}


static void egjr07_wait1(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->xspeed = 0x400;
  }
  puka_puka(p_actwk);
  speedset2(p_actwk);
  egjr0a_pg(p_actwk);
  chk_emy_fout0(p_actwk);
}


static void nuckle0a0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[11] = {
    &nuckle0a0_init,
    &nuckle0a0_wait0,
    &nuckle0a0_fall0,
    &nuckle0a0_wait1,
    &nuckle0a0_wait2,
    &nuckle0a0_wait3,
    &nuckle0a0_wait4,
    &nuckle0a0_jump0,
    &nuckle0a0_run0,
    &nuckle0a0_jump1,
    &nuckle0a0_wait5
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  if (p_actwk->u.obj.actflg0.flicker == 0) {
    p_actwk->patbase = knuckles_pt;
    nk0930_wrt(p_actwk);
    actionsub(p_actwk);
  }
  else {
    p_actwk->patbase = nk0a00_pt;
    set_emy_wchg(p_actwk, &nk0a00_wrt_tbl);
    actionsub(p_actwk);
  }
}


static void nuckle0a0_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &nuckle_init_tbl);
  g_ram.DAT_08fffab8_bitfield = 0;
  p_actwk->sprpri = PRI_1;
  memcpy(&g_ram.colorwk2[16], &g_ram.colorwk[16], sizeof(unsigned short) * 16);
  set_emy_cor(&nuckle_cor_tbl);
}


static void nuckle0a0_wait0(SKC_sprite_status* p_actwk) {
  pt_chgs0(p_actwk, ball_pg01);
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 0)) {
    p_actwk->r_no = 4;
    p_actwk->patno = 86;
    p_actwk->sprvsize = 51;
    unlze_moduled(&g_vram[0xA000], deth0a_cg);
  }
}


static void nuckle0a0_fall0(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  SKC_dircol_result result = emycol_d(p_actwk);
  if (result.offset < 0) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
    p_actwk->r_no = 6;
    p_actwk->u.obj.timer = 5;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &chk_h_scroll;
    }
    set_act05(p_actwk, &deth0a_set_tbl);
  }
}


static void nuckle0a0_wait1(SKC_sprite_status* p_actwk) {
  set_cont_se(-45);
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_no = 8;
    p_actwk->actflg.hflip = 1;
    p_actwk->u.obj.actflg0.flicker = 1;
    p_actwk->patno = 0;
    pg_init(p_actwk, tired_pg00);
  }
}


static void nuckle0a0_wait2(SKC_sprite_status* p_actwk) {
  set_cont_se(-45);
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 1)) {
    time_pg(p_actwk);
  }
  else {
    p_actwk->r_no = 10;
    p_actwk->patno = 0;
    p_actwk->u.obj.timer = 5;
  }
}


static void nuckle0a0_wait3(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_no = 12;
  p_actwk->actflg.hflip = 0;
  p_actwk->u.obj.actflg0.flicker = 0;
  p_actwk->patno = 86;
  p_actwk->u.obj.timer = 5;
}


static void nuckle0a0_wait4(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->r_no = 14;
  p_actwk->sprvsize = 19;
  p_actwk->xspeed = 0x200;
  p_actwk->yspeed = -0x300;
  pg_init(p_actwk, ball_pg01);
}


static void nuckle0a0_jump0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      p_actwk->r_no = 16;
      p_actwk->xspeed = 0x300;
      p_actwk->yspeed = 0;
      p_actwk->actflg.hflip = 0;
      pg_init(p_actwk, run_pg02);
    }
  }
}


static void nuckle0a0_run0(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  speedset2(p_actwk);
  if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 0x2A8) {
    p_actwk->r_no = 18;
    p_actwk->sprvsize = 27;
    p_actwk->xspeed = 0x480;
    p_actwk->yspeed = -0x600;
    pg_init(p_actwk, ball_pg01);
  }
}


static void nuckle0a0_jump1(SKC_sprite_status* p_actwk) {
  pt_chgs(p_actwk);
  speedset(p_actwk);
  if (p_actwk->yspeed >= 0) {
    SKC_dircol_result result = emycol_d(p_actwk);
    if (result.offset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + result.offset);
      p_actwk->r_no = 20;
      p_actwk->sprpri = PRI_4;
      p_actwk->actflg.hflip = 0;
      p_actwk->u.obj.actflg0.flicker = 1;
      p_actwk->patno = 1;
      g_ram.DAT_08ffeedb = 0xFF;
      soundset(91);
      pg_init(p_actwk, tired_pg01);
    }
  }
}


static void nuckle0a0_wait5(SKC_sprite_status* p_actwk) {
  chk_gomen(p_actwk);
  time_pg(p_actwk);
  short xposi = (g_ram.scra_h_posit >> 16) - 128;
  short yposi = fp16_get_integer(p_actwk->yposi) - (g_ram.scra_v_posit >> 16) + 128;
  if (xposi > fp16_get_integer(p_actwk->xposi) || (unsigned short)xposi > 0x200) {
    g_ram.markerno = 1;
    g_ram.plxposi_s = 0x140;
    g_ram.plyposi_s = 0xC6C;
    playsave1(p_actwk);
    memcpy(&g_ram.colorwk[16], &g_ram.colorwk2[16], sizeof(unsigned short) * 16);
    divdevset2(&item_cg_tbl);
    clr_wchg_bit(p_actwk);
    set_emy_fout0(p_actwk);
  }
}


void sw0a00(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &sw0a00_init_tbl);
  p_actwk->r_ptr = &sw0a00_wait0;
  sw0a00_wait0(p_actwk);
}


static void sw0a00_wait0(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


static void deth0a(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &deth0a_init_tbl);
  p_actwk->r_ptr = &deth0a_up0;
  fp16_set_integer(&p_actwk->xposi, 0x200);
  fp16_set_integer(&p_actwk->yposi, 0xC68);
  p_actwk->yspeed = 0xC68;
  p_actwk->u.obj.actfree.bg0a.accel = -64;
  p_actwk->u.obj.timer = 256;
  g_ram.ranum = g_ram.systemtimer;
  set_act00(p_actwk, &kumo0a_set_tbl);
  memcpy(&g_ram.colorwk2[48], &g_ram.colorwk[48], sizeof(unsigned short) * 16);
  memcpy(&g_ram.colorwk[48], deth0a_color, sizeof(unsigned short) * 16);
  deth0a_up0(p_actwk);
}


static void deth0a_up0(SKC_sprite_status* p_actwk) {
  speedset0a(p_actwk);
  actionsub(p_actwk);
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &deth0a_up1;
  }
}


static void deth0a_up1(SKC_sprite_status* p_actwk) {
  chk_megj0a_set(p_actwk);
  speedset0a(p_actwk);
  actionsub(p_actwk);
  if ((g_ram.scra_v_posit >> 16) - 56 > (unsigned short)fp16_get_integer(p_actwk->yposi)) {
    p_actwk->u.obj.actflg0.end = 1;
    SET_BIT(g_ram.DAT_08fffab8_bitfield, 1);
    memcpy(&g_ram.colorwk[48], &g_ram.colorwk2[48], sizeof(unsigned short) * 16);
    set_emy_fout0(p_actwk);
  }
}


static void kumo0a(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &kumo0a_init,
    &kumo0a_wait0,
    &kumo0a_down0
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  speedset0a(p_actwk);
  set_emy_wchg(p_actwk, &kumo0a_wrt_tbl);
  actionsub(p_actwk);
}


static void kumo0a_init(SKC_sprite_status* p_actwk) {
  emy_wrt_init(p_actwk, &kumo0a_init_tbl);
  p_actwk->u.obj.pg_data_ptr = kumo0a_pg00;
  p_actwk->yspeed = fp16_get_integer(p_actwk->yposi);
  p_actwk->u.obj.timer = 400;
  kumo0a_wait0(p_actwk);
}


static void kumo0a_wait0(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_no = 4;
    p_actwk->u.obj.actfree.bg0a.accel = 16;
    p_actwk->u.obj.timer = 384;
  }
}


static void kumo0a_down0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) {
    time_pg(p_actwk);
  }
  else {
    clr_wchg_bit(p_actwk);
    set_emy_fout0(p_actwk);
  }
}


static void mask0a(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &mask0a_init_tbl);
  p_actwk->r_ptr = &mask0a_wait0;
  p_actwk->yspeed = fp16_get_integer(p_actwk->yposi);
  mask0a_wait0(p_actwk);
}


static void mask0a_wait0(SKC_sprite_status* p_actwk) {
  g_ram.sprhmasks = 0xFF;
  if (!BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 2)) {
    speedset0a(p_actwk);
    actionsub(p_actwk);
  }
  else {
    set_emy_fout0(p_actwk);
  }
}


static void suji0a(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &suji0a_init_tbl);
  p_actwk->r_ptr = &suji0a_wait0;
  p_actwk->u.obj.callback_ptr = &set_emy_fout0;
  suji0a_wait0(p_actwk);
}


static void suji0a_wait0(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  time_pg0(p_actwk, suji0a_pg00);
  actionsub(p_actwk);
}


static void megj0a(SKC_sprite_status* p_actwk) {
  enemy_init1(p_actwk, &megj0a_init_tbl);
  p_actwk->r_ptr = &megj0a_wait0;
  unsigned long number = random();
  short xoffset = (short)(number & 0x3F) - 32;
  p_actwk->xspeed = xoffset >= 0 ? 0x100 : -0x100;
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
  short yoffset = (short)((number >> 16) & 0x1F);
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  p_actwk->yspeed = 0x100;
  megj0a_wait0(p_actwk);
}


static void megj0a_wait0(SKC_sprite_status* p_actwk) {
  p_actwk->patno = !(g_ram.systemtimer & 1) ? 4 : 5;
  p_actwk->yspeed -= 0x10;
  speedset2(p_actwk);
  chk_emy_fout3(p_actwk);
}


void nucksw(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    nuckle_fout(p_actwk);
  }
  else {
    enemy_init0(p_actwk, &nucksw_init_tbl);
    p_actwk->r_ptr = &nucksw_wait0;
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 4);
    divdevset2(&switch_cg_tbl);
  }
}


static SKC_cg_data switch_cg_tbl = {
  0,
  {
    {switch_cg , 0x8AC0 }
  }
};


static void nucksw_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler jmp_tbl[4] = {
    &switchact_001,
    &switchact_010,
    &switchact_030,
    &switchact_031
  };

  if (g_ram.DAT_08fffaa4_obj != 0) {
    SKC_sprite_status* p_nucklewk = &g_ram.actwk[g_ram.DAT_08fffaa4_obj];
    if (emy_col_a1(p_actwk, p_nucklewk, knuckle_col_tbl)) {
      p_actwk->r_ptr = &nucksw_wait1;
      p_actwk->patno = 1;
      g_ram.DAT_08fffaa9 = 0xFF;
      p_actwk->u.obj.flagwork_index = 0;
      jmp_tbl[p_actwk->u.obj.userflag / 2](p_actwk);
    }
  }
  frameoutchk(p_actwk);
}


static short knuckle_col_tbl[4] = { -24, 48, -24, 48 };


static void nucksw_wait1(SKC_sprite_status* p_actwk) {
  chk_emy_fout0(p_actwk);
}


static void switchact_001(SKC_sprite_status* p_actwk) {
  g_ram.pl_input_lock_flag = 0;
  g_ram.scralim_m_down = 0x1000;
  g_ram.scralim_n_down = 0x1000;
  set_act05(p_actwk, &chglimd_set_tbl);
}


static void switchact_010(SKC_sprite_status* p_actwk) {
  g_ram.stage_triggers[8] = 0xFF;
}


static void switchact_030(SKC_sprite_status* p_actwk) {
  g_ram.scr_shake_flg = 20;
  g_ram.waterposi = (g_ram.scra_v_posit >> 16) + 256;
  g_ram.watermoveposi = 0x350;
  g_ram.DAT_08fffaa3 = 0xFF;
  soundset(87);
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &cchg0320_act;
  }
}


static void switchact_031(SKC_sprite_status* p_actwk) {
  g_ram.scr_shake_flg = 20;
  unsigned char* p_layout = &g_ram.stage_layout[0x48];
  unsigned short screen_row_offset = p_layout[0] | p_layout[1] << 8;
  unsigned short screen_offset = screen_row_offset + 0x8E;

  screen_offset ^= 1; /* Stage data is byte-swapped. */
  g_ram.screens[screen_offset] = 20;
  screen_offset ^= 1; /* Undo adjustment. */

  screen_offset += g_ram.stage_layout[0];
  screen_offset ^= 1; /* Stage data is byte-swapped. */
  g_ram.screens[screen_offset] = 15;
  screen_offset ^= 1; /* Undo adjustment. */

  screen_offset += g_ram.stage_layout[0];
  screen_offset ^= 1; /* Stage data is byte-swapped. */
  g_ram.screens[screen_offset] = 15;
  screen_offset ^= 1; /* Undo adjustment. */

  screen_offset += g_ram.stage_layout[0];
  screen_offset ^= 1; /* Stage data is byte-swapped. */
  g_ram.screens[screen_offset] = 136;
  screen_offset ^= 1; /* Undo adjustment. */

  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &shooter3;
    fp16_set_integer(&result.actwk_ptr->xposi, 0x4740);
    fp16_set_integer(&result.actwk_ptr->yposi, 0x828);
    result.actwk_ptr->u.obj.userflag = 76;
  }
  result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &shooter3;
    fp16_set_integer(&result.actwk_ptr->xposi, 0x4740);
    fp16_set_integer(&result.actwk_ptr->yposi, 0xA28);
    result.actwk_ptr->u.obj.userflag = 32;
  }
}


void setbryuka(SKC_sprite_status* p_actwk) {
  chk_framein(p_actwk, &setbryuka_framein);
  setbryuka_framein(p_actwk);
}


static void setbryuka_framein(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &setbryuka_wait0;
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &bryuka;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
    result.actwk_ptr->u.obj.userflag = 1;
    p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
  }
  setbryuka_wait0(p_actwk);
}


static void setbryuka_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_childwk->r_ptr != &bryukamove2) {
    frameoutchk3(p_actwk);
  }
  else {
    if (g_ram.DAT_08fffaa2 == 0) {
      g_ram.DAT_08fffaa2 = 0xFF;
      g_ram.watermoveposi = 0x958;
    }
    frameout(p_actwk);
  }
}


void cchgsw(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &nucksw_init_tbl);
  p_actwk->r_ptr = &cchgsw_wait0;
  fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 4);
  divdevset2(&switch_cg_tbl);
}


static void cchgsw_wait0(SKC_sprite_status* p_actwk) {
  chk_nucksw_ride(p_actwk);
  p_actwk->patno = 0;
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->patno = 1;
    if (g_ram.DAT_08fffaa3 != 0) {
      g_ram.DAT_08fffaa3 = 0;
      g_ram.watermoveposi = 0xA58;
      soundset(87);
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &cchg0320_act;
        result.actwk_ptr->u.obj.userflag = 0xFF;
      }
    }
  }
  frameoutchk(p_actwk);
}


void set_nuckle_bgm(void) {
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &set_bgm_act;
    result.actwk_ptr->u.obj.userflag = 31;
  }
}


void chk_nucksw_ride(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 4, 5, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
}


static void set_friend07_spd(SKC_sprite_status* p_actwk) {
  unsigned long number = random();
  p_actwk->yspeed = -((short)(number & 0x1FF) + 0x100);
  if (BIT_IS_SET(g_ram.DAT_08fffab8_bitfield, 2)) {
    set_friend07_spd__move_l(p_actwk);
  }
  else if ((unsigned short)fp16_get_integer(p_actwk->xposi) < p_actwk->u.obj.actfree.friend07.left_limit) {
    set_friend07_spd__move_r(p_actwk);
  }
  else if ((unsigned short)fp16_get_integer(p_actwk->xposi) > p_actwk->u.obj.actfree.friend07.right_limit) {
    set_friend07_spd__move_l(p_actwk);
  }
  else if (!BIT_IS_SET(number >> 16, 15)) {
    set_friend07_spd__move_r(p_actwk);
  }
  else {
    set_friend07_spd__move_l(p_actwk);
  }
}


static void set_friend07_spd__move_l(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.hflip = 1;
  p_actwk->xspeed = -0x100;
}


static void set_friend07_spd__move_r(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.hflip = 0;
  p_actwk->xspeed = 0x100;
}


static void chk_shut07_ride(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 32, 32, fp16_get_integer(p_actwk->xposi) };
  hitchk(p_actwk, data);
}


static void chk_nk0720_plpt(SKC_sprite_status* p_actwk) {
  chk_nk0720_plpt__sub(p_actwk, &g_ram.actwk[0]);
  if (g_ram.actwk[1].r_ptr != 0) {
    chk_nk0720_plpt__sub(p_actwk, &g_ram.actwk[1]);
  }
}


static void chk_nk0720_plpt__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  unsigned char pt_tbl[4] = {
    180, 167, 181, 168
  };

  p_playerwk->mstno = 5;
  if (p_actwk->patcnt >= 12) {
    p_playerwk->u.play.control_bitfield = 0x83;
    p_playerwk->mstno = 0;
    p_playerwk->actflg.vflip = 1;
    int index = !(g_ram.systemtimer & 2) ? 0 : 2;
    p_playerwk->patno = pt_tbl[index + p_playerwk->u.play.character];
    wrt_player0(p_playerwk);
  }
}


static void set_housi(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->u.obj.timer = p_actwk->u.obj.actfree.nuckle071.timer_init;
  SKC_actwkchk_result result = actwkchk();
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &housi071;
    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
  }
}


static void chk_gomen(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actflg0.fura_right == 1) return;

  SKC_chk_distance_result result = chk_distance0(p_actwk, &g_ram.actwk[0]);
  if ((unsigned short)result.ydistance < 32
      && (unsigned short)(result.xdistance - 48) < 32
      && result.right
      && g_ram.actwk[0].mstno == 8) {
    pg_init(p_actwk, go_pg00);
  }
}


static void speedset0a(SKC_sprite_status* p_actwk) {
  fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + g_ram.DAT_08fffa84);
  long yspeed = 0;
  fp16_set_integer(&yspeed, p_actwk->yspeed);
  fp16_set_fraction(&yspeed, p_actwk->mspeed);
  yspeed += p_actwk->u.obj.actfree.bg0a.accel * 0x100;
  p_actwk->yspeed = fp16_get_integer(yspeed);
  p_actwk->mspeed = fp16_get_integer(yspeed);
  short yposi = fp16_get_integer(yspeed) - g_ram.DAT_08ffee9c / 4;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static void chk_megj0a_set(SKC_sprite_status* p_actwk) {
  if (g_ram.systemtimer & 0x1F) return;

  soundset(-96);
  set_act05(p_actwk, &megj0a_set_tbl);
}


static void chk_h_scroll(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.actfree.hscroll_chk.scra_h_posit = g_ram.scra_h_posit >> 16;
  p_actwk->r_ptr = &chk_h_scroll__chk;
  chk_h_scroll__chk(p_actwk);
}


static void chk_h_scroll__chk(SKC_sprite_status* p_actwk) {
  short prev_scra_h_posit = p_actwk->u.obj.actfree.hscroll_chk.scra_h_posit;
  p_actwk->u.obj.actfree.hscroll_chk.scra_h_posit = g_ram.scra_h_posit >> 16;
  g_ram.DAT_08fffa84 = (p_actwk->u.obj.actfree.hscroll_chk.scra_h_posit - prev_scra_h_posit) / 2;
}


static void nkmiles_wrt(SKC_sprite_status* p_actwk) {
  if (p_actwk->patno == p_actwk->u.obj.wrt.prev_patno) return;

  p_actwk->u.obj.wrt.prev_patno = p_actwk->patno;
  unsigned char* p_wrtpat = nkmiles_wrtpat_tbl[p_actwk->patno];
  unsigned short cnt = p_wrtpat[0] << 8 | p_wrtpat[1];
  p_wrtpat += 2;
  unsigned short vram_adr = 0xD400;

  for (int i = 0; i < cnt; ++i) {
    unsigned short command = p_wrtpat[0] << 8 | p_wrtpat[1];
    unsigned char* p_source = &nkmiles_cg[(command & 0x0FFF) * 32];
    unsigned short size = (((command & 0xF000) >> 12) + 1) * 32;
    memcpy(&g_vram[vram_adr], p_source, size);
    vram_adr += size;
  }
}


SKC_wrt_init_data nuckle_init_tbl = {
  0,
  0xA4DA,
  46,
  0,
  nuckle_pt,
  PRI_3,
  28,
  24,
  22,
  0
};


static SKC_wrt_init_data nk0701_init_tbl = {
  0,
  0xA4DA,
  46,
  0,
  nk0701_pt,
  PRI_3,
  28,
  24,
  3,
  0
};


static SKC_wrt_init_data nk0702_init_tbl = {
  0,
  0x06A0,
  46,
  0,
  nkopen_pt,
  PRI_3,
  28,
  24,
  0,
  0
};


static SKC_wrt_init_data nk0931_init_tbl = {
  0,
  0xA4DA,
  46,
  0,
  nk0931_pt,
  PRI_3,
  28,
  24,
  2,
  0
};


static SKC_enemy_init0_data nucksw_init_tbl = {
  switchpat,
  0x8456,
  PRI_2,
  16,
  8,
  0,
  0
};


static SKC_enemy_init0_data bomb06_init_tbl = {
  bomb06_pt,
  0xA4D6,
  PRI_1,
  8,
  8,
  0,
  0
};


static SKC_enemy_init0_data nuckle061_dai_init_tbl = {
  tekotu_pt,
  0x45A0,
  PRI_5,
  16,
  16,
  0,
  0
};


static SKC_enemy_init0_data tekotu_init_tbl = {
  tekotu_pt,
  0x45A0,
  PRI_5,
  16,
  128,
  1,
  0
};


static SKC_enemy_init0_data opniwa_init_tbl = {
  bryukapat,
  0x4001,
  PRI_3,
  16,
  24,
  0,
  0
};


static SKC_enemy_init0_data nk0700_init_tbl = {
  nk0700_pt,
  0x2500,
  PRI_3,
  16,
  16,
  4,
  0
};


static SKC_enemy_init0_data sw0700_init_tbl = {
  switchpat,
  0x0341,
  PRI_2,
  128,
  128,
  0,
  0
};


static SKC_enemy_init0_data sw0701_init_tbl = {
  sw0701_pt,
  0xA528,
  PRI_6,
  16,
  16,
  0,
  0
};


static SKC_enemy_init0_data shut07_init_tbl = {
  shut07_pt,
  0x63C9,
  PRI_1,
  16,
  32,
  0,
  0
};


SKC_enemy_init0_data housi071_init_tbl = {
  housi071_pt,
  0xE368,
  PRI_0,
  4,
  4,
  0,
  0
};


static SKC_enemy_init0_data egbomb07_init_tbl = {
  egbomb_pt,
  0x252E,
  PRI_3,
  12,
  16,
  0,
  0
};


static SKC_enemy_init2_data egbomb07_spark_init_tbl = {
  PRI_2,
  8,
  8,
  1,
  0
};


static SKC_enemy_init2_data egbomb07_smoke_init_tbl = {
  PRI_2,
  8,
  8,
  5,
  0
};


static SKC_enemy_init0_data sw0a00_init_tbl = {
  switchpat,
  PRI_3,
  0x048E,
  16,
  8,
  1,
  0
};


static SKC_enemy_init0_data deth0a_init_tbl = {
  deth0a_pt,
  0x6500,
  PRI_7,
  60,
  48,
  0,
  0
};


static SKC_wrt_init_data kumo0a_init_tbl = {
  0,
  0x64C9,
  16,
  2,
  kumo0a_pt,
  PRI_5,
  64,
  16,
  0,
  0
};


static SKC_enemy_init0_data mask0a_init_tbl = {
  maskpat,
  0x0000,
  PRI_4,
  64,
  48,
  12,
  0
};


static SKC_enemy_init2_data suji0a_init_tbl = {
  PRI_6,
  4,
  28,
  1,
  0
};


static SKC_enemy_init1_data megj0a_init_tbl = {
  0x0500,
  PRI_5,
  8,
  8,
  4,
  0
};


static SKC_set_act05_data nuckle001_col_set_tbl = {
  0,
  &nuckle001_col
};


static SKC_set_act00_data nuckle030_col_set_tbl = {
  0,
  {
    { &nuckle030_col, -32, -108 }
  }
};


static SKC_set_act00_data limchg030_set_tbl = {
  2,
  {
    { &chg_scr_lim_u, 0, 0 },
    { &chg_scr_lim_l, 0, 0 },
    { &chg_scr_lim_r, 0, 0 }
  }
};


static SKC_set_act00_data nuckle060_col_set_tbl = {
  0,
  {
    { &nuckle060_col, -64, 0 }
  }
};


static SKC_set_act00_data bomb06_set_tbl = {
  0,
  {
    { &bomb06, -8, -16 }
  }
};


static SKC_set_act05_data bomb06_exp_set_tbl = {
  3,
  &bomb06_exp
};


static SKC_set_act02_data nuckle061_dai_set_tbl = {
  3,
  &nuckle061_dai,
  2,
  36
};


static SKC_set_act00_data opniwa_set_tbl = {
  0,
  {
    { &opniwa, 0, 24 }
  }
};


static SKC_set_act00_data nucksw_set_tbl010 = {
  0,
  {
    { &nucksw, 0, 12 }
  }
};


static SKC_set_act05_data nuckles_set_tbl = {
  0,
  &nuckle
};


static SKC_set_act05_data nk0700_set_tbl = {
  0,
  &nk0700
};


static SKC_set_act05_data shut07_set_tbl = {
  0,
  &shut07
};


static SKC_set_act00_data sw0701_set_tbl = {
  0,
  {
    { &sw0701, -8, 0 }
  }
};


static SKC_set_act00_data kumo0a_set_tbl = {
  6,
  {
    { &mask0a,   0,   0 },
    { &kumo0a,   0, -51 },
    { &suji0a, -32,  29 },
    { &suji0a, -16,  29 },
    { &suji0a,   8,  29 },
    { &suji0a,  16,  29 },
    { &suji0a,  40,  29 }
  }
};


static SKC_set_act05_data megj0a_set_tbl = {
  0,
  &megj0a
};


static SKC_set_act05_data deth0a_set_tbl = {
  0,
  &deth0a
};


static SKC_set_act05_data egbomb07_exp_set_tbl = {
  9,
  &egbomb07_exp
};


static SKC_set_act05_data friend07_set_tbl = {
  7,
  &friend07
};


static SKC_set_act00_data egbomb07_spark_set_tbl = {
  0,
  {
    { &egbomb07_spark, 0, -20 }
  }
};


static SKC_set_act05_data egbomb07_smoke_set_tbl = {
  0,
  &egbomb07_smoke
};


SKC_wrt_data nuckle_wrt_tbl = {
  nuckle_cg,
  nuckle_tbl
};


static SKC_wrt_data nk0701_wrt_tbl = {
  nk0701_cg,
  nk0701_tbl
};


static SKC_wrt_data nkopen_wrt_tbl = {
  nkopen_cg,
  nkopen_tbl
};


SKC_wrt_data nk0a00_wrt_tbl = {
  nk0a00_cg,
  nk0a00_tbl
};


static SKC_wrt_data kumo0a_wrt_tbl = {
  kumo0a_cg,
  kumo0a_tbl
};


static signed char balance_pg00[5] = { 7, 1, 2, 3, -4 };


static signed char run_pg00[10] = { 4, 10, 11, 12, 13, 14, 15, 16, 17, -4 };
static signed char run_pg01[6] = { 1, 18, 19, 20, 21, -4 };


static signed char ball_pg00[10] = { 1, 8, 4, 8, 5, 8, 6, 8, 7, -4 };


static signed char laugh_pg00[6] = { 7, 28, 28, 29, -8, 6 };
static signed char laugh_pg01[4] = { 7, 30, 31, -4 };


static signed char throw_pg00[15] = { 22, 7, 22, 7, 23, 7, 24, 7, 25, 19, 26, 7, 27, 0, -12 };


static signed char panchi_pg00[15] = { 32, 5, 33, 5, 34, 20, 35, 3, 36, 15, 33, 5, 32, 5, -12 };


static signed char nk0700_pg00[21] = { 0, 4, 0, 9, 1, 29, 0, 4, 2, 4, 3, 29, 2, 4, 0, 4, 1, 29, 0, 4, -12 };


static signed char turnsw_pg00[35] = {
  3,   7, 3, 31,   0,  7, 1, 31, 2,  7,
  1, 127, 2,  7,   1, 31, 2,  7, 1, 15,
  2,   7, 1, 11,   2,  7, 1,  7, 2,  7,
  1,   7, 2,  7, -12
};


static signed char tired_pg00[6] = { 0, 7, 0, 7, -8, 6 };
signed char tired_pg01[11] = { 1, 11, 2, 5, 3, 11, 2, 11, 1, 11, -4 };


static signed char go_pg00[10] = { 4, 7, 4, 7, 5, 7, 6, 31, -8, 10 };
static signed char go_pg01[5] = { 5, 15, 6, 31, -4 };


static signed char kumo0a_pg00[30] = {
  0,  5,  0,  5,  1,  7,  2,  9,  3,  9,
  4, 11,  5, 12,  6, 13,  7, 14,  8, 15,
  9, 19, 10, 29, 11, 39, 12, 99, -8, 30
};


static signed char kumo0a_pg01[9] = { 11, 59, 10, 99, 11, 59, 12, 99, -4 };


static signed char suji0a_pg00[17] = { 6, 0, 6, 77, 1, 77, 1, 77, 1, 77, 1, 77, 2, 9, 3, 9, -12 };


signed char footwk_pg00[60] = {
  -40, 4, -39, 4, -38, 4, -37,  4, -40,  4,
  -39, 4, -38, 4, -37, 4, -40,  4, -39,  4,
  -38, 4, -37, 4, -40, 4, -39,  4, -38,  4,
  -37, 4, -40, 4, -39, 4, -38,  4, -37,  4,
  -40, 4, -39, 4, -38, 4, -37,  4, -36,  4,
  -35, 4, -36, 4, -35, 4, -34, 11,  -1, -4
};


signed char guard_pg00[7] = {   4, -40,  -39, -38,  -37, -1, -4 };
signed char guard_pg01[8] = { -38,   5, -101,   5, -100, 15, -1, -12 };


signed char damage_pg00[5] = { 1, 0, -115, -1, -4 };


signed char ball_pg01[11] = { 1, -102, -106, -102, -105, -102, -104, -102, -103, -1, -4 };


signed char jump_pg00[8] = { 3, -38, -38, -101, -100, -101, -1, -12 };


signed char down_pg00[12] = { -64, 5, -54, 5, -53, 127, -53, 127, -53, 127, -1, -4 };


signed char land_pg00[7] = { 5, -52, -101, -100, -101, -1, -12 };
signed char land_pg01[14] = { 2, 3, 3, 3, 4, 3, 5, 3, 4, 127, 4, 31, -1, -12 };


signed char spin_pg00[8] = { 3, -38, -38, -101, -100, -1, -8, 8 };
static signed char spin_pg01[13] = { 0, -122, -121, -122, -120, -122, -119, -122, -118, -122, -117, -1, -4 };


signed char die_pg00[12] = { 2, 3, 3, 3, 4, 3, 5, 3, 4, 63, -1, -12 };
static signed char die_pg01[14] = { 2, 3, 3, 3, 4, 3, 5, 3, 4, 127, 6, 3, -1, -12 };


signed char run_pg02[11] = { 4, 7, 8, 1, 2, 3, 4, 5, 6, -1, -4 };
signed char run_pg03[11] = { 3, 7, 8, 1, 2, 3, 4, 5, 6, -1, -4 };


signed char effect_pg00[9] = { 1, 10, 11, 12, 13, 14, 15, 16, -4 };


signed char wake_pg00[38] = {
  6, 63, 6, 63, 7,  2,  8,   2, 7, 2,
  6,  2, 7,  2, 8,  2,  7,   2, 6, 2,
  7,  2, 8,  2, 7,  2,  6,   2, 7, 2,
  8,  2, 7,  2, 6, 95, -1, -12
};


signed char wait_pg00[5] = { 7, 9, 10, -1, -4 };


signed char angry_pg00[5] = { 5, 11, 12, -1, -4 };


signed char panch_pg00[12] = { 86, 7, 86, 31, -34, 0, -34, 15, 86, 63, -1, -12 };
signed char panch_pg01[22] = {
  -40, 4, -39, 4, -38, 4, -37, 4, -36, 4,
  -36, 4, -35, 4, -36, 4, -35, 4, -34, 0,
  -1, -12
};
signed char panch_pg02[8] = { -34, 7, -34, 7, 86, 0, -1, -12 };


signed char comeon_pg00[20] = { 14, 89, 14, 119, 15, 7, 16, 29, 17, 7, 18, 7, 17, 7, 18, 7, 15, 7, -1, -12 };


static signed char relax_pg00[4] = { 19, 0, 1, -4 };
static signed char relax_pg01[9] = { 4, 111, 4, 111, 2, 7, 3, 127, -4 };


static signed char land_pg02[53] = {
   3,  3,   3, 3,  4, 3,  5,  3,  4, 95,
   6, 31,   7, 2,  8, 2,  7,  2,  6,  2,
   7,  2,   8, 2,  7, 2,  6, 15,  9,  7,
  10,  7,   9, 7, 10, 7,  9,  7, 10,  7,
   9,  7,  10, 7,  9, 7, 10,  7,  9,  7,
  10,  7, -12
};


static signed char egbomb07_spark_pg00[6] = { 3, 1, 2, 3, 4, -4 };


static signed char egbomb07_smoke_pg00[7] = { 5, 5, 5, 6, 7, 8, -12 };


unsigned short nuckle_cor_tbl[16] = {
  0x000, 0xEEE, 0x84E, 0x40C, 0x206, 0x0EE, 0x00E, 0x008, 0x0AE, 0x08E, 0x8AE, 0x46A, 0xECC, 0xCAA, 0x866, 0x222
};


static unsigned short cchg0320_tbl[64] = {
  0x000, 0xEEE, 0xEEE, 0x6EE, 0x6EE, 0x8AE, 0x44E, 0xEEE, 0xE02, 0xEEE, 0xEEE, 0x6EE, 0xEEE, 0xEEA, 0x668, 0x000,
  0x000, 0xC88, 0x644, 0x622, 0x400, 0x200, 0x2E4, 0x40E, 0x208, 0x0CC, 0x0AA, 0x022, 0x400, 0x200, 0x4E0, 0x000,
  0x000, 0xECC, 0x022, 0x000, 0x000, 0x006, 0x000, 0x000, 0xE02, 0x000, 0x000, 0x000, 0xA86, 0x422, 0x200, 0x000,
  0x000, 0x200, 0x000, 0x000, 0x000, 0x000, 0x000, 0x002, 0x208, 0x000, 0x000, 0x000, 0x400, 0x200, 0x660, 0x000
};


static unsigned short deth0a_color[16] = {
  0x000, 0xEEE, 0xEEA, 0xEC8, 0xEA6, 0xE84, 0x000, 0x000, 0xECC, 0xCAA, 0xA88, 0x866, 0x666, 0x444, 0x0AE, 0x000
};


static unsigned short egbomb_cor_tbl[16] = {
  0x000, 0xEEE, 0x08C, 0x04A, 0x026, 0x0EE, 0x000, 0x8AA, 0x468, 0x044, 0x0AE, 0x00E, 0x000, 0x000, 0x020, 0x000
};


static SKC_sprite_pattern* nk0700_pt[5] = {
  &nk0700_pt00,
  &nk0700_pt01,
  &nk0700_pt02,
  &nk0700_pt03,
  &nk0700_pt04
};


static SKC_sprite_pattern nk0700_pt00 = {
  2,
  {
    { -16, 6, 0x0000,  -4 },
    {   8, 4, 0x0006, -12 }
  }
};
static SKC_sprite_pattern nk0700_pt01 = {
  2,
  {
    { -16, 6, 0x0008,  -4 },
    {   8, 4, 0x0006, -12 }
  }
};
static SKC_sprite_pattern nk0700_pt02 = {
  2,
  {
    { -16, 10, 0x000E,  -4 },
    {   8,  4, 0x0006, -12 }
  }
};
static SKC_sprite_pattern nk0700_pt03 = {
  2,
  {
    { -16, 10, 0x0017,  -4 },
    {   8,  4, 0x0006, -12 }
  }
};
static SKC_sprite_pattern nk0700_pt04 = {
  1,
  {
    { -16, 6, 0x0000, -4 }
  }
};


static SKC_sprite_pattern* shut07_pt[1] = {
  &shut07_pt00
};


static SKC_sprite_pattern shut07_pt00 = {
  8,
  {
    { -32, 5, 0x0000, -16 },
    { -32, 5, 0x0000,   0 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0000,   0 },
    {   0, 5, 0x0000, -16 },
    {   0, 5, 0x0000,   0 },
    {  16, 5, 0x0000, -16 },
    {  16, 5, 0x0000,   0 }
  }
};


static SKC_sprite_pattern* nk0701_pt[4] = {
  &nk0701_pt00,
  &nk0701_pt01,
  &nk0701_pt02,
  &nk0701_pt03
};


static SKC_sprite_pattern nk0701_pt00 = {
  2,
  {
    { -20,  9, 0x0000,  -8 },
    {  -4, 14, 0x0006, -16 }
  }
};
static SKC_sprite_pattern nk0701_pt01 = {
  2,
  {
    { -20,  8, 0x0000,  -8 },
    { -12, 15, 0x0003, -16 }
  }
};
static SKC_sprite_pattern nk0701_pt02 = {
  2,
  {
    { -20,  4, 0x0000,  -8 },
    { -12, 15, 0x0002, -16 }
  }
};
static SKC_sprite_pattern nk0701_pt03 = {
  2,
  {
    { -20,  9, 0x0000,  -8 },
    {  -4, 14, 0x0006, -16 }
  }
};


static unsigned short* nk0701_tbl[4] = {
  nk0701_tbl00,
  nk0701_tbl01,
  nk0701_tbl02,
  nk0701_tbl03
};


static unsigned short nk0701_tbl00[3] = { 1, 0x005, 0x06B };
static unsigned short nk0701_tbl01[3] = { 1, 0x122, 0x15F };
static unsigned short nk0701_tbl02[3] = { 1, 0x251, 0x27F };
static unsigned short nk0701_tbl03[3] = { 1, 0x005, 0x37B };


static SKC_sprite_pattern* sw0701_pt[2] = {
  &sw0701_pt00,
  &sw0701_pt01
};


static SKC_sprite_pattern sw0701_pt00 = {
  1,
  {
    { -12, 6, 0x0000, -8 }
  }
};
static SKC_sprite_pattern sw0701_pt01 = {
  1,
  {
    { -12, 6, 0x0006, -8 }
  }
};


static SKC_sprite_pattern* housi071_pt[1] = {
  &housi071_pt00
};


static SKC_sprite_pattern housi071_pt00 = {
  1,
  {
    { -4, 0, 0x0000, -4 }
  }
};


SKC_sprite_pattern* nk0a00_pt[7] = {
  &nk0a00_pt00,
  &nk0a00_pt01,
  &nk0a00_pt02,
  &nk0a00_pt03,
  &nk0a00_pt04,
  &nk0a00_pt05,
  &nk0a00_pt06
};


static SKC_sprite_pattern nk0a00_pt00 = {
  3,
  {
    {   4,  0, 0x0000, -26 },
    { -12,  9, 0x0001, -18 },
    {   4, 13, 0x0007, -18 }
  }
};
static SKC_sprite_pattern nk0a00_pt01 = {
  2,
  {
    { -12,  4, 0x0000, -11 },
    {  -4, 14, 0x0002, -19 }
  }
};
static SKC_sprite_pattern nk0a00_pt02 = {
  2,
  {
    { -12,  9, 0x0000, -19 },
    {   4, 13, 0x0006, -19 }
  }
};
static SKC_sprite_pattern nk0a00_pt03 = {
  2,
  {
    { -4,  8, 0x0000, -19 },
    {  4, 13, 0x0003, -19 }
  }
};
static SKC_sprite_pattern nk0a00_pt04 = {
  2,
  {
    { -4,  8, 0x0000, -19 },
    {  4, 13, 0x0003, -19 }
  }
};
static SKC_sprite_pattern nk0a00_pt05 = {
  1,
  {
    { -4, 14, 0x0000, -19 }
  }
};
static SKC_sprite_pattern nk0a00_pt06 = {
  2,
  {
    { -4, 14, 0x0000, -18 },
    {  4,  0, 0x000C,  14 }
  }
};


static unsigned short* nk0a00_tbl[7] = {
  nk0a00_tbl00,
  nk0a00_tbl01,
  nk0a00_tbl02,
  nk0a00_tbl03,
  nk0a00_tbl04,
  nk0a00_tbl05,
  nk0a00_tbl06
};


static unsigned short nk0a00_tbl00[4] = { 2, 0x000, 0x015, 0x077 };
static unsigned short nk0a00_tbl01[3] = { 1, 0x0F1, 0x11B };
static unsigned short nk0a00_tbl02[3] = { 1, 0x1D5, 0x237 };
static unsigned short nk0a00_tbl03[3] = { 1, 0x2B2, 0x2E7 };
static unsigned short nk0a00_tbl04[3] = { 1, 0x362, 0x397 };
static unsigned short nk0a00_tbl05[2] = { 0, 0x41B };
static unsigned short nk0a00_tbl06[3] = { 1, 0x4DB, 0x590 };


static SKC_sprite_pattern* deth0a_pt[7] = {
  &deth0a_pt00,
  &deth0a_pt01,
  &deth0a_pt02,
  &deth0a_pt03,
  &deth0a_pt04,
  &deth0a_pt05,
  &deth0a_pt06
};


static SKC_sprite_pattern deth0a_pt00 = {
  16,
  {
    { -40, 10, 0x0000, -48 },
    { -16, 13, 0x0009, -56 },
    { -48, 15, 0x0011, -24 },
    { -16, 13, 0x0021, -24 },
    { -48,  5, 0x0029,   8 },
    { -40,  4, 0x002D,  24 },
    { -32, 15, 0x002F,   8 },
    { -32,  3, 0x003F,  40 },
    {   0, 14, 0x0043, -48 },
    {  24,  9, 0x004F, -40 },
    {  40,  0, 0x0055, -24 },
    {   0, 15, 0x0056, -16 },
    {  32, 13, 0x0066, -16 },
    {   0, 14, 0x0843,  16 },
    {  24,  9, 0x084F,  16 },
    {  40,  0, 0x0855,  16 }
  }
};
static SKC_sprite_pattern deth0a_pt01 = {
  3,
  {
    { -28, 0, 0x006E, -4 },
    { -20, 2, 0x006F, -4 },
    {   4, 2, 0x006F, -4 }
  }
};
static SKC_sprite_pattern deth0a_pt02 = {
  3,
  {
    { -28, 0, 0x0072, -4 },
    { -20, 2, 0x0073, -4 },
    {   4, 2, 0x0073, -4 }
  }
};
static SKC_sprite_pattern deth0a_pt03 = {
  3,
  {
    { -28, 0, 0x0076, -4 },
    { -20, 2, 0x0077, -4 },
    {   4, 2, 0x0077, -4 }
  }
};
static SKC_sprite_pattern deth0a_pt04 = {
  1,
  {
    { -4, 0, 0x007A, -4 }
  }
};
static SKC_sprite_pattern deth0a_pt05 = {
  2,
  {
    { -4, 0, 0x007A, -4 },
    { -7, 4, 0x007B, -8 }
  }
};
static SKC_sprite_pattern deth0a_pt06 = {
  0,
  {}
};


static SKC_sprite_pattern* kumo0a_pt[13] = {
  &kumo0a_pt00,
  &kumo0a_pt01,
  &kumo0a_pt02,
  &kumo0a_pt03,
  &kumo0a_pt04,
  &kumo0a_pt05,
  &kumo0a_pt06,
  &kumo0a_pt07,
  &kumo0a_pt08,
  &kumo0a_pt09,
  &kumo0a_pt10,
  &kumo0a_pt11,
  &kumo0a_pt12
};


static SKC_sprite_pattern kumo0a_pt00 = {
  2,
  {
    { -4, 4, 0x0000, -16 },
    { -4, 4, 0x0800,   0 }
  }
};
static SKC_sprite_pattern kumo0a_pt01 = {
  4,
  {
    { -4, 4, 0x0000, -32 },
    { -12, 5, 0x0002, -16 },
    { -12, 5, 0x0802, 0 },
    { -4, 4, 0x0800, 16 }
  }
};
static SKC_sprite_pattern kumo0a_pt02 = {
  6,
  {
    {  -4, 8, 0x0000, -48 },
    { -12, 5, 0x0003, -24 },
    { -20, 2, 0x0007,  -8 },
    { -20, 2, 0x0807,   0 },
    { -12, 5, 0x0803,   8 },
    {  -4, 8, 0x0800,  24 }
  }
};
static SKC_sprite_pattern kumo0a_pt03 = {
  6,
  {
    {  -4, 8, 0x0000, -48 },
    { -12, 5, 0x0003, -24 },
    { -20, 2, 0x0007,  -8 },
    { -20, 2, 0x0807,   0 },
    { -12, 5, 0x0803,   8 },
    {  -4, 8, 0x0800,  24 }
  }
};
static SKC_sprite_pattern kumo0a_pt04 = {
  6,
  {
    {  -4, 4, 0x0000, -48 },
    { -12, 5, 0x0002, -32 },
    { -20, 6, 0x0006, -16 },
    { -20, 6, 0x0806,   0 },
    { -12, 5, 0x0802,  16 },
    {  -4, 4, 0x0800,  32 }
  }
};
static SKC_sprite_pattern kumo0a_pt05 = {
  6,
  {
    {  -4,  4, 0x0000, -56 },
    { -12,  1, 0x0002, -40 },
    { -20, 14, 0x0004, -32 },
    { -20, 14, 0x0804,   0 },
    { -12,  1, 0x0802,  32 },
    {  -4,  4, 0x0800,  40 }
  }
};
static SKC_sprite_pattern kumo0a_pt06 = {
  6,
  {
    {  -4,  8, 0x0000, -64 },
    { -12,  1, 0x0003, -40 },
    { -20, 14, 0x0005, -32 },
    { -20, 14, 0x0805,   0 },
    { -12,  1, 0x0803,  32 },
    {  -4,  8, 0x0800,  40 }
  }
};
static SKC_sprite_pattern kumo0a_pt07 = {
  6,
  {
    {  -4, 8, 0x0000, -64 },
    { -12, 9, 0x0003, -40 },
    { -20, 6, 0x0009, -16 },
    { -20, 6, 0x0809,   0 },
    { -12, 9, 0x0803,  16 },
    {  -4, 8, 0x0800,  40 }
  }
};
static SKC_sprite_pattern kumo0a_pt08 = {
  6,
  {
    {  -4, 8, 0x0000, -64 },
    { -12, 9, 0x0003, -40 },
    { -20, 6, 0x0009, -16 },
    { -20, 6, 0x0809,   0 },
    { -12, 9, 0x0803,  16 },
    {  -4, 8, 0x0800,  40 }
  }
};
static SKC_sprite_pattern kumo0a_pt09 = {
  6,
  {
    {  -4, 8, 0x0000, -64 },
    { -12, 9, 0x0003, -40 },
    { -20, 6, 0x0009, -16 },
    { -20, 6, 0x0809,   0 },
    { -12, 9, 0x0803,  16 },
    {  -4, 8, 0x0800,  40 }
  }
};
static SKC_sprite_pattern kumo0a_pt10 = {
  6,
  {
    {  -4, 8, 0x0000, -64 },
    { -12, 9, 0x0003, -40 },
    { -20, 6, 0x0009, -16 },
    { -20, 6, 0x0809,   0 },
    { -12, 9, 0x0803,  16 },
    {  -4, 8, 0x0800,  40 }
  }
};
static SKC_sprite_pattern kumo0a_pt11 = {
  6,
  {
    { -4, 8, 0x0000, -64 },
    { -12, 9, 0x0003, -40 },
    { -20, 6, 0x0009, -16 },
    { -20, 6, 0x0809, 0 },
    { -12, 9, 0x0803, 16 },
    { -4, 8, 0x0800, 40 }
  }
};
static SKC_sprite_pattern kumo0a_pt12 = {
  6,
  {
    {  -4,  8, 0x0000, -64 },
    { -12,  1, 0x0003, -40 },
    { -12, 13, 0x0005, -32 },
    { -12, 13, 0x0805,   0 },
    { -12,  1, 0x0803,  32 },
    {  -4,  8, 0x0800,  40 }
  }
};


static unsigned short* kumo0a_tbl[13] = {
  kumo0a_tbl00,
  kumo0a_tbl01,
  kumo0a_tbl02,
  kumo0a_tbl03,
  kumo0a_tbl04,
  kumo0a_tbl05,
  kumo0a_tbl06,
  kumo0a_tbl07,
  kumo0a_tbl08,
  kumo0a_tbl09,
  kumo0a_tbl10,
  kumo0a_tbl11,
  kumo0a_tbl12
};


static unsigned short kumo0a_tbl00[2] = { 0, 0x001 };
static unsigned short kumo0a_tbl01[3] = { 1, 0x021, 0x043 };
static unsigned short kumo0a_tbl02[4] = { 2, 0x082, 0x0B3, 0x0F2 };
static unsigned short kumo0a_tbl03[4] = { 2, 0x122, 0x153, 0x192 };
static unsigned short kumo0a_tbl04[4] = { 2, 0x1C1, 0x1E3, 0x225 };
static unsigned short kumo0a_tbl05[4] = { 2, 0x281, 0x2A1, 0x2CB };
static unsigned short kumo0a_tbl06[4] = { 2, 0x382, 0x3B1, 0x3DB };
static unsigned short kumo0a_tbl07[4] = { 2, 0x492, 0x4C5, 0x525 };
static unsigned short kumo0a_tbl08[4] = { 2, 0x582, 0x5B5, 0x615 };
static unsigned short kumo0a_tbl09[4] = { 2, 0x672, 0x6A5, 0x705 };
static unsigned short kumo0a_tbl10[4] = { 2, 0x672, 0x765, 0x7C5 };
static unsigned short kumo0a_tbl11[4] = { 2, 0x822, 0x855, 0x8B5 };
static unsigned short kumo0a_tbl12[4] = { 2, 0x912, 0x941, 0x967 };


static SKC_sprite_pattern* nkopen_pt[5] = {
  &nkopen_pt00,
  &nkopen_pt01,
  &nkopen_pt02,
  &nkopen_pt03,
  &nkopen_pt04
};


static SKC_sprite_pattern nkopen_pt00 = {
  4,
  {
    { -12, 2, 0x0000, -20 },
    { -12, 5, 0x0003, -12 },
    {   4, 4, 0x0007, -12 },
    {  -4, 5, 0x0009,   4 }
  }
};
static SKC_sprite_pattern nkopen_pt01 = {
  4,
  {
    { -12, 2, 0x0000, -20 },
    { -12, 5, 0x0003, -12 },
    {   4, 4, 0x0007, -12 },
    {  -4, 5, 0x0009,   4 }
  }
};
static SKC_sprite_pattern nkopen_pt02 = {
  5,
  {
    { -12, 2, 0x0000, -20 },
    { -12, 5, 0x0003, -12 },
    {   4, 4, 0x0007, -12 },
    { -12, 0, 0x0009,   4 },
    {  -4, 5, 0x000A,   4 }
  }
};
static SKC_sprite_pattern nkopen_pt03 = {
  2,
  {
    { -12, 10, 0x0000, -12 },
    {   4,  0, 0x0009,  12 }
  }
};
static SKC_sprite_pattern nkopen_pt04 = {
  4,
  {
    { -12, 2, 0x0000, -20 },
    { -12, 5, 0x0003, -12 },
    {   4, 4, 0x0007, -12 },
    {  -4, 5, 0x0009,   4 }
  }
};


static unsigned short* nkopen_tbl[5] = {
  nkopen_tbl00,
  nkopen_tbl01,
  nkopen_tbl02,
  nkopen_tbl03,
  nkopen_tbl04
};


static unsigned short nkopen_tbl00[5] = { 3, 0x002, 0x033, 0x071, 0x093 };
static unsigned short nkopen_tbl01[5] = { 3, 0x002, 0x0D3, 0x111, 0x133 };
static unsigned short nkopen_tbl02[6] = { 4, 0x172, 0x1A3, 0x1E1, 0x200, 0x213 };
static unsigned short nkopen_tbl03[3] = { 1, 0x258, 0x2E0 };
static unsigned short nkopen_tbl04[5] = { 3, 0x002, 0x2F3, 0x071, 0x093 };


static SKC_sprite_pattern* egbomb_pt[9] = {
  &egbomb_pt00,
  &egbomb_pt01,
  &egbomb_pt02,
  &egbomb_pt03,
  &egbomb_pt04,
  &egbomb_pt05,
  &egbomb_pt06,
  &egbomb_pt07,
  &egbomb_pt08
};


static SKC_sprite_pattern egbomb_pt00 = {
  2,
  {
    { -16, 7, 0x0000, -16 },
    { -16, 7, 0x0800,   0 }
  }
};
static SKC_sprite_pattern egbomb_pt01 = {
  1,
  {
    { -8, 5, 0x0008, -8 }
  }
};
static SKC_sprite_pattern egbomb_pt02 = {
  1,
  {
    { -8, 5, 0x0808, -8 }
  }
};
static SKC_sprite_pattern egbomb_pt03 = {
  1,
  {
    { -8, 5, 0x1808, -8 }
  }
};
static SKC_sprite_pattern egbomb_pt04 = {
  1,
  {
    { -8, 5, 0x1008, -8 }
  }
};
static SKC_sprite_pattern egbomb_pt05 = {
  1,
  {
    { -4, 0, 0x000C, -4 }
  }
};
static SKC_sprite_pattern egbomb_pt06 = {
  1,
  {
    { -8, 5, 0x000D, -8 }
  }
};
static SKC_sprite_pattern egbomb_pt07 = {
  1,
  {
    { -8, 5, 0x0011, -8 }
  }
};
static SKC_sprite_pattern egbomb_pt08 = {
  1,
  {
    { -8, 5, 0x0015, -8 }
  }
};
