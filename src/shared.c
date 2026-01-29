#include "shared.h"
#include <stdbool.h>
#include <string.h>
#include "types/actwkchkresult.h"
#include "types/cchgcntinfo.h"
#include "types/cchgitem.h"
#include "types/cchgwork.h"
#include "types/cgdata.h"
#include "types/chkdistanceresult.h"
#include "types/chkemycoltresult.h"
#include "types/enemyinit0data.h"
#include "types/enemyinit1data.h"
#include "types/enemyinit2data.h"
#include "types/point.h"
#include "types/setact00data.h"
#include "types/setact01data.h"
#include "types/setact02data.h"
#include "types/setact03data.h"
#include "types/setact04data.h"
#include "types/setact05data.h"
#include "types/setact06data.h"
#include "types/setact07data.h"
#include "types/setact08data.h"
#include "types/setact09data.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "types/spritestatushandler.h"
#include "types/wrtdata.h"
#include "types/wrtinitdata.h"
#include "utils/bits.h"
#include "utils/controller.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "action.h"
#include "constants.h"
#include "etc.h"
static void chk_pt_next(SKC_sprite_status* p_actwk, signed char* p_pg_data);
static int pt_chgs0__chk_pt_next(SKC_sprite_status* p_actwk, signed char* p_pg_data);
static int chk_tpg_next(SKC_sprite_status* p_actwk, signed char* p_pg_data);
static int time_pgs0__chk_tpg_next(SKC_sprite_status* p_actwk, signed char* p_pg_data);
static int pg_get_fast0__chk_flash(SKC_sprite_status* p_actwk, signed char* p_pg_data);
static void pg_get_slow0__chk_flash(SKC_sprite_status* p_actwk, signed char* p_pg_data);
static void emy_frameout(SKC_sprite_status* p_actwk);
static SKC_point get_radius_point(SKC_sprite_status* p_actwk, unsigned char* p_sin_data);
static void set_emy_fout01(SKC_sprite_status* p_actwk);
static void set_break_spd0(SKC_sprite_status* p_actwk, unsigned char index);
static void fadeout_act__fadeout(SKC_sprite_status* p_actwk);
static void fadein_act__fadein(SKC_sprite_status* p_actwk);
static void spd2_pt_tim_act(SKC_sprite_status* p_actwk);
static bool chk_emy_colt__col(SKC_sprite_status* p_playerwk, short left_x, short right_x, short top_y, short bottom_y);
static void chk_framein__chk(SKC_sprite_status* p_actwk);
static void res_bgm_act__cnt(SKC_sprite_status* p_actwk);
static void set_bgm_act__cnt(SKC_sprite_status* p_actwk);
static void midbos_die1(SKC_sprite_status* p_actwk);
static void midbos_die2_init(SKC_sprite_status* p_actwk);
static void midbos_die3(SKC_sprite_status* p_actwk);
static void chk_scr_bgm__set_v_bit(SKC_sprite_status* p_actwk);
static void chk_scr_bgm__set_h_bit(SKC_sprite_status* p_actwk);
static void flashout_act__cnt(SKC_sprite_status* p_actwk);
static void flashin_act__cnt(SKC_sprite_status* p_actwk);
static SKC_sprite_status_handler play_wrt_tbl[3];
static void get_ring__1up(void);
static void mask_spr0__wait0(SKC_sprite_status* p_actwk);
static void mask_spr0__wait1(SKC_sprite_status* p_actwk);
static void chk_pl_dir__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void fox_auto__cnt(SKC_sprite_status* p_actwk);
static void shake_se_act__cnt(SKC_sprite_status* p_actwk);

extern sonic3_ram g_ram;


void enemy_init0(SKC_sprite_status* p_actwk, SKC_enemy_init0_data* p_data) {
  p_actwk->patbase = p_data->patbase;
  p_actwk->sproffset = p_data->sproffset;
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_no += 2;
}


void enemy_init1(SKC_sprite_status* p_actwk, SKC_enemy_init1_data* p_data) {
  p_actwk->sproffset = p_data->sproffset;
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_no += 2;
}


void enemy_init2(SKC_sprite_status* p_actwk, SKC_enemy_init2_data* p_data) {
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_no += 2;
}


SKC_sprite_status* set_act00(SKC_sprite_status* p_actwk, SKC_set_act00_data* p_data) {
  SKC_actwkchk_result result;

  for (int i = 0; i < p_data->cnt + 1; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->data[i].r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    result.actwk_ptr->u.obj.oya_offset.x = p_data->data[i].xoffset;
    short xposi = fp16_get_integer(p_actwk->xposi) + p_data->data[i].xoffset;
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    result.actwk_ptr->u.obj.oya_offset.y = p_data->data[i].yoffset;
    short yposi = fp16_get_integer(p_actwk->yposi) + p_data->data[i].yoffset;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act01(SKC_sprite_status* p_actwk, SKC_set_act01_data* p_data) {
  SKC_actwkchk_result result;

  for (int i = 0; i < p_data->cnt; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->data[i].r_ptr;
    result.actwk_ptr->u.obj.enemy_init0_data_ptr = p_data->data[i].enemy_init0_data_ptr;
    result.actwk_ptr->u.obj.pg_data_ptr = p_data->data[i].pg_data_ptr;
    result.actwk_ptr->u.obj.callback_ptr = p_data->data[i].callback_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    result.actwk_ptr->u.obj.oya_offset.x = p_data->data[i].xoffset;
    short xposi = fp16_get_integer(p_actwk->xposi) + p_data->data[i].xoffset;
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    result.actwk_ptr->u.obj.oya_offset.y = p_data->data[i].yoffset;
    short yposi = fp16_get_integer(p_actwk->yposi) + p_data->data[i].yoffset;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
    result.actwk_ptr->xspeed = p_data->data[i].xspeed;
    result.actwk_ptr->yspeed = p_data->data[i].yspeed;
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act02(SKC_sprite_status* p_actwk, SKC_set_act02_data* p_data) {
  SKC_actwkchk_result result;

  for (int i = 0; i < p_data->cnt; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    result.actwk_ptr->u.obj.oya_offset.x = p_data->xoffset;
    short xposi = fp16_get_integer(p_actwk->xposi) + p_data->xoffset;
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    result.actwk_ptr->u.obj.oya_offset.y = p_data->yoffset;
    short yposi = fp16_get_integer(p_actwk->yposi) + p_data->yoffset;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act03(SKC_sprite_status* p_actwk, SKC_set_act03_data* p_data) {
  SKC_actwkchk_result result;
  SKC_sprite_status* p_prev_actwk = p_actwk;

  for (int i = 0; i < p_data->cnt; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_prev_actwk - g_ram.actwk;
    p_prev_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
    p_prev_actwk = result.actwk_ptr;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act04(SKC_sprite_status* p_actwk, SKC_set_act04_data* p_data) {
  SKC_actwkchk_result result;

  for (int i = 0; p_data->cnt + 1; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->data[i].r_ptr;
    result.actwk_ptr->u.obj.pg_data_ptr = p_data->data[i].pg_data_ptr;
    result.actwk_ptr->u.obj.callback_ptr = p_data->data[i].callback_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    signed char xoffset = p_data->data[i].xoffset;
    result.actwk_ptr->u.obj.oya_offset.x = xoffset;
    if (p_actwk->actflg.hflip == 1) {
      xoffset = -xoffset;
    }
    short xposi = fp16_get_integer(p_actwk->xposi) + xoffset;
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    result.actwk_ptr->u.obj.oya_offset.y = p_data->data[i].yoffset;
    short yposi = fp16_get_integer(p_actwk->yposi) + p_data->data[i].yoffset;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
    short xspeed = p_data->data[i].xspeed;
    if (p_actwk->actflg.hflip == 1) {
      xspeed = -xspeed;
    }
    result.actwk_ptr->xspeed = xspeed;
    result.actwk_ptr->yspeed = p_data->data[i].yspeed;
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act05(SKC_sprite_status* p_actwk, SKC_set_act05_data* p_data) {
  SKC_actwkchk_result result;

  for (int i = 0; p_data->cnt + 1; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act06(SKC_sprite_status* p_actwk, SKC_set_act06_data* p_data) {
  SKC_actwkchk_result result;

  for (int i = 0; p_data->cnt + 1; ++i) {
    result = actwkchk();
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->data[i].r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    result.actwk_ptr->u.obj.oya_offset.x = p_data->data[i].xoffset;
    short xposi = fp16_get_integer(p_actwk->xposi) + p_data->data[i].xoffset;
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    result.actwk_ptr->u.obj.oya_offset.y = p_data->data[i].yoffset;
    short yposi = fp16_get_integer(p_actwk->yposi) + p_data->data[i].yoffset;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act07(SKC_sprite_status* p_actwk, SKC_set_act07_data* p_data) {
  SKC_actwkchk_result result;
  SKC_sprite_status* p_prev_actwk = p_actwk;

  for (int i = 0; p_data->cnt + 1; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_prev_actwk - g_ram.actwk;
    result.actwk_ptr->u.obj.ko = p_actwk - g_ram.actwk;
    p_prev_actwk = result.actwk_ptr;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act08(SKC_sprite_status* p_actwk, SKC_set_act08_data* p_data) {
  SKC_actwkchk_result result;
  SKC_sprite_status* p_prev_actwk = p_actwk;

  for (int i = 0; p_data->cnt + 1; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_prev_actwk - g_ram.actwk;
    result.actwk_ptr->u.obj.ko = p_actwk - g_ram.actwk;
    p_prev_actwk = result.actwk_ptr;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->data[i].r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
  }

  return result.actwk_ptr;
}


SKC_sprite_status* set_act09(SKC_sprite_status* p_actwk, SKC_set_act09_data* p_data) {
  SKC_actwkchk_result result;

  for (int i = 0; p_data->cnt + 1; ++i) {
    result = actwkchk2(p_actwk);
    if (result.actwk_ptr == 0) break;

    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    result.actwk_ptr->patbase = p_actwk->patbase;
    result.actwk_ptr->sproffset = p_actwk->sproffset;
    result.actwk_ptr->r_ptr = p_data->data[i].r_ptr;
    result.actwk_ptr->u.obj.userflag = i * 2;
    signed char xoffset = p_data->data[i].xoffset;
    if (p_actwk->actflg.hflip == 1) {
      result.actwk_ptr->actflg.hflip = 1;
      xoffset = -xoffset;
    }
    result.actwk_ptr->u.obj.oya_offset.x = xoffset;
    short xposi = fp16_get_integer(p_actwk->xposi) + xoffset;
    fp16_set_integer(&result.actwk_ptr->xposi, xposi);
    result.actwk_ptr->u.obj.oya_offset.y = p_data->data[i].yoffset;
    short yposi = fp16_get_integer(p_actwk->yposi) + p_data->data[i].yoffset;
    fp16_set_integer(&result.actwk_ptr->yposi, yposi);
  }

  return result.actwk_ptr;
}


void ko_offset0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xposi = fp16_get_integer(p_parentwk->xposi) + p_actwk->u.obj.oya_offset.x;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_parentwk->yposi) + p_actwk->u.obj.oya_offset.y;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void ko_offset1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  signed char xoffset = p_actwk->u.obj.oya_offset.x;
  p_actwk->actflg.hflip = 0;
  if (p_parentwk->actflg.hflip == 1) {
    xoffset = -xoffset;
    p_actwk->actflg.hflip = 1;
  }
  short xposi = fp16_get_integer(p_parentwk->xposi) + xoffset;
  fp16_set_integer(&p_actwk->xposi, xposi);
  signed char yoffset = p_actwk->u.obj.oya_offset.y;
  p_actwk->actflg.vflip = 0;
  if (p_parentwk->actflg.vflip == 1) {
    yoffset = -yoffset;
    p_actwk->actflg.vflip = 1;
  }
  short yposi = fp16_get_integer(p_parentwk->yposi) + yoffset;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void pt_chg(SKC_sprite_status* p_actwk) {
  pt_chg0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


void pt_chg0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return;

  ++p_actwk->patcnt;
  if (p_pg_data[p_actwk->patcnt + 1] < 0) {
    chk_pt_next(p_actwk, p_pg_data);
  }
  else {
    p_actwk->pattim = p_pg_data[0];
    p_actwk->patno = p_pg_data[p_actwk->patcnt + 1];
  }
}


static void chk_pt_next(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  signed char pg = -p_pg_data[p_actwk->patcnt + 1];

  switch (pg) {
    case PG_CONTROL_NEXT:
      pg = p_pg_data[p_actwk->patcnt + 2];
      p_pg_data = &p_pg_data[pg];
      p_actwk->u.obj.pg_data_ptr = p_pg_data;
      // fall-through
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[1];
      p_actwk->pattim = p_pg_data[0];
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      p_actwk->u.obj.callback_ptr(p_actwk);
      break;
  }

  p_actwk->patcnt = 0;
}


void pt_chgr(SKC_sprite_status* p_actwk) {
  pt_chgr0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


void pt_chgr0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return;

  ++p_actwk->patcnt;
  if (p_pg_data[p_actwk->patcnt + 1] < 0) {
    chk_pt_next(p_actwk, p_pg_data);
  }
  else {
    unsigned char patno = p_pg_data[p_actwk->patcnt + 1];
    if (BIT_IS_SET(patno, 6)) {
      CLEAR_BIT(patno, 6);
      p_actwk->actflg.hflip ^= 1;
    }
    p_actwk->pattim = p_pg_data[0];
    p_actwk->patno = patno;
  }
}


void pt_chgvr(SKC_sprite_status* p_actwk) {
  pt_chgvr0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


void pt_chgvr0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return;

  ++p_actwk->patcnt;
  if (p_pg_data[p_actwk->patcnt + 1] < 0) {
    chk_pt_next(p_actwk, p_pg_data);
  }
  else {
    unsigned char patno = p_pg_data[p_actwk->patcnt + 1];
    if (BIT_IS_SET(patno, 6)) {
      CLEAR_BIT(patno, 6);
      p_actwk->actflg.vflip ^= 1;
    }
    p_actwk->pattim = p_pg_data[0];
    p_actwk->patno = patno;
  }
}


void pl_pt_chg(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, signed char* p_pg_data) {
  if (p_playerwk->pattim-- > 0) {
    wrt_player0(p_playerwk);
  }
  else {
    p_playerwk->pattim = p_pg_data[0];
    p_playerwk->patcnt += 2;
    if (p_pg_data[p_playerwk->patcnt + 1] == 0) {
      wrt_player0(p_playerwk);
      p_actwk->u.obj.callback_ptr(p_actwk);
    }
    else {
      p_playerwk->patno = p_pg_data[p_playerwk->patcnt + 1];
      p_playerwk->actflg.hflip = 0;
      if (p_pg_data[p_playerwk->patcnt + 2] != 0) {
        p_playerwk->actflg.hflip = 1;
      }
      wrt_player0(p_playerwk);
    }
  }
}


int pt_chgs(SKC_sprite_status* p_actwk) {
  return pt_chgs0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


int pt_chgs0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return 0;

  ++p_actwk->patcnt;
  if (p_pg_data[p_actwk->patcnt + 1] == -1) {
    return pt_chgs0__chk_pt_next(p_actwk, p_pg_data);
  }
  p_actwk->pattim = p_pg_data[0];
  p_actwk->patno = p_pg_data[p_actwk->patcnt + 1];
  return 1;
}


static int pt_chgs0__chk_pt_next(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  signed char pg = -p_pg_data[p_actwk->patcnt + 2];

  switch (pg) {
    case PG_CONTROL_NULL:
      break;
    case PG_CONTROL_NEXT:
      pg = p_pg_data[p_actwk->patcnt + 3];
      p_pg_data = &p_pg_data[pg];
      p_actwk->u.obj.pg_data_ptr = p_pg_data;
      // fall-through
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[1];
      p_actwk->pattim = p_pg_data[0];
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      p_actwk->u.obj.callback_ptr(p_actwk);
      return 0;
  }

  p_actwk->patcnt = 0;
  return -1;
}


void pg_init(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  p_actwk->u.obj.pg_data_ptr = p_pg_data;
  p_actwk->patcnt = 0;
  p_actwk->pattim = 0;
}


void pl_spd_clr(SKC_sprite_status* p_playerwk) {
  p_playerwk->xspeed = 0;
  p_playerwk->yspeed = 0;
  p_playerwk->mspeed = 0;
}


int time_pg(SKC_sprite_status* p_actwk) {
  return time_pg0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


int time_pg0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return 0;

  p_actwk->patcnt += 2;
  if (p_pg_data[p_actwk->patcnt] < 0) {
    return chk_tpg_next(p_actwk, p_pg_data);
  }
  p_actwk->patno = p_pg_data[p_actwk->patcnt];
  p_actwk->pattim = p_pg_data[p_actwk->patcnt + 1];
  return 1;
}


static int chk_tpg_next(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  int ret = 0;
  signed char pg = -p_pg_data[p_actwk->patcnt];

  switch (pg) {
    case PG_CONTROL_NULL:
      break;
    case PG_CONTROL_NEXT:
      pg = p_pg_data[p_actwk->patcnt + 1];
      p_pg_data = &p_pg_data[pg];
      p_actwk->u.obj.pg_data_ptr = p_pg_data;
      // fall-through
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[0];
      p_actwk->pattim = p_pg_data[1];
      ret = 1;
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      p_actwk->u.obj.callback_ptr(p_actwk);
      ret = -1;
      break;
  }

  p_actwk->patcnt = 0;
  return ret;
}


int time_pgr(SKC_sprite_status* p_actwk) {
  return time_pgr0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


int time_pgr0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return 0;

  p_actwk->patcnt += 2;
  if (p_pg_data[p_actwk->patcnt] < 0) {
    return chk_tpg_next(p_actwk, p_pg_data);
  }
  if (BIT_IS_SET(p_pg_data[p_actwk->patcnt], 6)) {
    p_actwk->actflg.hflip ^= 1;
  }
  p_actwk->patno = p_pg_data[p_actwk->patcnt];
  CLEAR_BIT(p_actwk->patno, 6);
  p_actwk->pattim = p_pg_data[p_actwk->patcnt + 1];
  return 1;
}


int time_pgvr(SKC_sprite_status* p_actwk) {
  return time_pgvr0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


int time_pgvr0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return 0;

  p_actwk->patcnt += 2;
  if (p_pg_data[p_actwk->patcnt] < 0) {
    return chk_tpg_next(p_actwk, p_pg_data);
  }
  if (BIT_IS_SET(p_pg_data[p_actwk->patcnt], 6)) {
    p_actwk->actflg.vflip ^= 1;
  }
  p_actwk->patno = p_pg_data[p_actwk->patcnt];
  CLEAR_BIT(p_actwk->patno, 6);
  p_actwk->pattim = p_pg_data[p_actwk->patcnt + 1];
  return 1;
}


int time_pgs(SKC_sprite_status* p_actwk) {
  return time_pgs0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


int time_pgs0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->pattim-- > 0) return 0;

  p_actwk->patcnt += 2;
  if (p_pg_data[p_actwk->patcnt] == -1) {
    return time_pgs0__chk_tpg_next(p_actwk, p_pg_data);
  }
  p_actwk->pattim = p_pg_data[0];
  p_actwk->patno = p_pg_data[p_actwk->patcnt + 1];
  return 1;
}


static int time_pgs0__chk_tpg_next(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  int ret = 0;
  signed char pg = -p_pg_data[p_actwk->patcnt + 1];

  switch (pg) {
    case PG_CONTROL_NULL:
      break;
    case PG_CONTROL_NEXT:
      pg = p_pg_data[p_actwk->patcnt + 2];
      p_pg_data = &p_pg_data[pg];
      p_actwk->u.obj.pg_data_ptr = p_pg_data;
      // fall-through
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[0];
      p_actwk->pattim = p_pg_data[1];
      ret = -1;
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      p_actwk->u.obj.callback_ptr(p_actwk);
      ret = -1;
      break;
  }

  p_actwk->patcnt = 0;
  return ret;
}


int pg_get_fast(SKC_sprite_status* p_actwk) {
  return pg_get_fast0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


int pg_get_fast0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  int ret = 0;
  if (p_actwk->u.obj.actflg0.flash == 0) {
    p_actwk->u.obj.actflg0.flash = 1;
    p_actwk->u.obj.get_fast_slow.pattim = *p_pg_data;
    p_actwk->u.obj.get_fast_slow.flash_duration = 0;
  }
  if (p_actwk->pattim-- == 0) {
    unsigned char patcnt = p_actwk->patcnt;
    signed char patno = p_pg_data[patcnt + 3];
    unsigned char pattim = p_actwk->u.obj.get_fast_slow.pattim;
    if (patno < 0) {
      patcnt = 0;
      patno = p_pg_data[2];
      if (pattim == 0) {
        ret = pg_get_fast0__chk_flash(p_actwk, p_pg_data);
      }
      else {
        --pattim;
        p_actwk->u.obj.get_fast_slow.pattim = pattim;
        ret = 1;
      }
    }
    p_actwk->patcnt = patcnt;
    p_actwk->patno = patno;
    p_actwk->pattim = pattim;
  }
  return ret;
}


static int pg_get_fast0__chk_flash(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  ++p_actwk->u.obj.get_fast_slow.flash_duration;
  if (p_actwk->u.obj.get_fast_slow.flash_duration >= p_pg_data[1]) {
    p_actwk->u.obj.actflg0.flash = 0;
    p_actwk->u.obj.get_fast_slow.flash_duration = 0;
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
  return -1;
}


void pg_get_slow(SKC_sprite_status* p_actwk) {
  pg_get_slow0(p_actwk, p_actwk->u.obj.pg_data_ptr);
}


void pg_get_slow0(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  if (p_actwk->u.obj.actflg0.flash == 0) {
    p_actwk->u.obj.actflg0.flash = 1;
    p_actwk->u.obj.get_fast_slow.flash_duration = 0;
  }
  if (p_actwk->pattim-- == 0) {
    unsigned char patcnt = p_actwk->patcnt + 1;
    signed char patno = p_pg_data[patcnt + 1];
    unsigned char pattim = p_actwk->u.obj.get_fast_slow.pattim;
    if (patno < 0) {
      patcnt = 0;
      patno = p_pg_data[1];
      ++pattim;
    }
    p_actwk->patcnt = patcnt;
    p_actwk->patno = patno;
    p_actwk->pattim = pattim;
    if (pattim >= p_pg_data[0]) {
      pg_get_slow0__chk_flash(p_actwk, p_pg_data);
      p_actwk->u.obj.get_fast_slow.pattim = pattim;
    }
  }
}


static void pg_get_slow0__chk_flash(SKC_sprite_status* p_actwk, signed char* p_pg_data) {
  ++p_actwk->u.obj.get_fast_slow.flash_duration;
  if (p_actwk->u.obj.get_fast_slow.flash_duration >= p_pg_data[1]) {
    p_actwk->u.obj.actflg0.flash = 0;
    p_actwk->u.obj.get_fast_slow.flash_duration = 0;
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


bool puka_puka(SKC_sprite_status* p_actwk) {
  bool puka = false;
  short yspeed = p_actwk->yspeed;
  if (p_actwk->u.obj.actflg0.puka_down == 0) {
    yspeed += -p_actwk->u.obj.puka.accel;
    if (yspeed > -p_actwk->u.obj.puka.accel_max) goto set;
    p_actwk->u.obj.actflg0.puka_down = 1;
    puka = true;
  }
  yspeed += p_actwk->u.obj.puka.accel;
  if (yspeed < p_actwk->u.obj.puka.accel_max) goto set;
  p_actwk->u.obj.actflg0.puka_down = 0;
  yspeed += -p_actwk->u.obj.puka.accel;
  puka = true;

set:
  p_actwk->yspeed = yspeed;
  return puka;
}


bool fura_fura(SKC_sprite_status* p_actwk) {
  bool fura = false;
  short xspeed = p_actwk->xspeed;
  if (p_actwk->u.obj.actflg0.fura_right == 0) {
    xspeed += -p_actwk->u.obj.fura.accel;
    if (xspeed > -p_actwk->u.obj.fura.accel_max) goto set;
    p_actwk->u.obj.actflg0.fura_right = 1;
    fura = true;
  }
  xspeed += p_actwk->u.obj.fura.accel;
  if (xspeed < p_actwk->u.obj.fura.accel_max) goto set;
  p_actwk->u.obj.actflg0.fura_right = 0;
  xspeed += -p_actwk->u.obj.fura.accel;
  fura = true;

set:
  p_actwk->xspeed = xspeed;
  return fura;
}


bool puka_count(SKC_sprite_status* p_actwk) {
  if (!puka_puka(p_actwk)) return false;
  if (p_actwk->u.obj.puka.cnt-- > 0) return false;
  return true;
}


void dec_timer(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


void emy_fall_col(SKC_sprite_status* p_actwk) {
  if (p_actwk->yspeed < 0) return;

  short yoffset = ObjCheckFloorDist(p_actwk);
  if (yoffset <= 0) {
    p_actwk->yposi += yoffset * 0x10000;
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


bool emy_down_col(SKC_sprite_status* p_actwk) {
  bool ret = false;
  long xposi = p_actwk->xposi + p_actwk->xspeed * 0x100;
  short yoffset = ObjCheckFloorDist2(p_actwk, xposi);
  if (yoffset >= -1 && yoffset < 12) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
  }
  else {
    p_actwk->u.obj.callback_ptr(p_actwk);
    ret = true;
  }
  return ret;
}


void emy_right_col(SKC_sprite_status* p_actwk) {
  short xoffset = ObjCheckRightWallDist(p_actwk);
  if (xoffset < 0) {
    p_actwk->xposi += xoffset * 0x10000;
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


void emy_left_col(SKC_sprite_status* p_actwk) {
  short xoffset = ObjCheckLeftWallDist(p_actwk);
  if (xoffset < 0) {
    p_actwk->xposi += xoffset * 0x10000;
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


void chk_actsubc(SKC_sprite_status* p_actwk) {
  colibufferchk(p_actwk);
  actionsub(p_actwk);
}


void chk_oya_die0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    set_emy_fout0(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


void chk_oya_diec0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    set_emy_fout0(p_actwk);
  }
  else {
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
}


void chk_oya_dien0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    set_emy_fout0(p_actwk);
  }
}


void chk_oya_dienc0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    set_emy_fout0(p_actwk);
  }
  else {
    colibufferchk(p_actwk);
  }
}


void chk_oya_diew0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 0) {
    actionsub(p_actwk);
  }
  else {
    clr_wchg_bit(p_actwk);
    set_emy_fout0(p_actwk);
  }
}


void chk_oya_die1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 0) {
    actionsub(p_actwk);
  }
  else {
    set_emy_fout1(p_actwk);
  }
}


void chk_oya_diec1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 0) {
    if (p_parentwk->u.obj.cddat.die == 0) {
      colibufferchk(p_actwk);
    }
    actionsub(p_actwk);
  }
  else {
    set_emy_fout1(p_actwk);
  }
}


void chk_tobi_die0(SKC_sprite_status* p_actwk, unsigned char break_type) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    set_emy_tobi(p_actwk, break_type);
  }
  else {
    actionsub(p_actwk);
  }
}


void set_emy_tobi(SKC_sprite_status* p_actwk, unsigned char break_type) {
  p_actwk->u.obj.cddat.die = 1;
  p_actwk->r_ptr = &chk_break_fout;
  p_actwk->colino = 0;
  set_break_spd(p_actwk, break_type);
  actionsub(p_actwk);
}


void chk_tobi_die1(SKC_sprite_status* p_actwk, unsigned char break_type) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 1) {
    set_emy_tobi(p_actwk, break_type);
  }
  else {
    actionsub(p_actwk);
  }
}


void chk_tobi_diec0(SKC_sprite_status* p_actwk, unsigned char break_type) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    set_emy_tobi(p_actwk, break_type);
  }
  else {
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
}


void chk_tobi_diec1(SKC_sprite_status* p_actwk, unsigned char break_type) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 1) {
    set_emy_tobi(p_actwk, break_type);
  }
  else if (p_parentwk->u.obj.cddat.die == 1) {
    p_actwk->u.obj.cddat.die = 1;
    actionsub(p_actwk);
  }
  else {
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
}


void chg_scr_lim_r(SKC_sprite_status* p_actwk) {
  unsigned short scralim_right = g_ram.scralim_right + (p_actwk->u.obj.scralim_unknown + 0x4000 >> 16);
  if (scralim_right < g_ram.scralim_m_right) {
    g_ram.scralim_right = scralim_right;
  }
  else {
    g_ram.scralim_right = g_ram.scralim_m_right;
    emy_frameout(p_actwk);
  }
}


static void emy_frameout(SKC_sprite_status* p_actwk) {
  frameout(p_actwk);
}


void chg_scr_lim_l(SKC_sprite_status* p_actwk) {
  unsigned short scralim_left = g_ram.scralim_left - (p_actwk->u.obj.scralim_unknown + 0x4000 >> 16);
  if (scralim_left > g_ram.scralim_m_left) {
    g_ram.scralim_left = scralim_left;
  }
  else {
    g_ram.scralim_left = g_ram.scralim_m_left;
    frameout(p_actwk);
  }
}


void chg_scr_lim_u(SKC_sprite_status* p_actwk) {
  short scralim_up = g_ram.scralim_up - (short)(p_actwk->u.obj.scralim_unknown + 0x4000 >> 16);
  if (scralim_up > g_ram.scralim_m_up) {
    g_ram.scralim_up = scralim_up;
  }
  else {
    g_ram.scralim_up = g_ram.scralim_m_up;
    frameout(p_actwk);
  }
}


void chg_scr_lim_d(SKC_sprite_status* p_actwk) {
  unsigned short scralim_down = g_ram.scralim_down + (p_actwk->u.obj.scralim_unknown + 0x8000 >> 16);
  if (scralim_down <= g_ram.scralim_m_down) {
    g_ram.scralim_down = scralim_down;
  }
  else {
    g_ram.scralim_down = g_ram.scralim_m_down;
    frameout(p_actwk);
  }
}


SKC_chk_distance_result chk_distance(SKC_sprite_status* p_actwk) {
  SKC_chk_distance_result result = { false, false, 0, 0 };
  result.xdistance = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(g_ram.actwk[0].xposi);
  if (result.xdistance < 0) {
    result.xdistance = -result.xdistance;
    result.right = true;
  }
  bool pl2_right = false;
  short pl2_xdistance = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(g_ram.actwk[1].xposi);
  if (pl2_xdistance < 0) {
    pl2_xdistance = -pl2_xdistance;
    pl2_right = true;
  }
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  if (result.xdistance > pl2_xdistance) {
    p_playerwk = &g_ram.actwk[1];
    result.right = pl2_right;
    result.xdistance = pl2_xdistance;
  }
  result.ydistance = fp16_get_integer(p_actwk->yposi) - fp16_get_integer(p_playerwk->yposi);
  if (result.ydistance < 0) {
    result.ydistance = -result.ydistance;
    result.below = true;
  }
  return result;
}


void chk_emy_rev(SKC_sprite_status* p_actwk, bool pl_right) {
  p_actwk->actflg.hflip = pl_right;
}


void chk_emy_revs(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.hflip = p_actwk->xspeed >= 0;
}


void chk_oya_rev(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->actflg.hflip = p_parentwk->actflg.hflip;
}


SKC_chk_distance_result chk_distance0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_otherwk) {
  SKC_chk_distance_result result = { false, false, 0, 0 };
  result.xdistance = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(p_otherwk->xposi);
  if (result.xdistance < 0) {
    result.xdistance = -result.xdistance;
    result.right = true;
  }
  result.ydistance = fp16_get_integer(p_actwk->yposi) - fp16_get_integer(p_otherwk->yposi);
  if (result.ydistance < 0) {
    result.ydistance = -result.ydistance;
    result.below = true;
  }
  return result;
}


void speedsetg20(SKC_sprite_status* p_actwk) {
  speedsetg(p_actwk, 0x20);
}


void speedsetg(SKC_sprite_status* p_actwk, short gravity) {
  p_actwk->xposi += p_actwk->xspeed * 0x100;
  p_actwk->yposi += p_actwk->yspeed * 0x100;
  p_actwk->yspeed += gravity;
}


void speedseta1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  speedseta1g(p_actwk, p_playerwk, 0x38);
}


void speedseta1g(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short gravity) {
  p_actwk->xposi += p_playerwk->xspeed * 0x100;
  p_playerwk->yposi += p_playerwk->yspeed * 0x100;
  p_playerwk->yspeed += gravity;
}


void circle_radius(SKC_sprite_status* p_actwk) {
  short sin, cos;
  sinset(p_actwk->u.obj.radius.angle, &sin, &cos);
  short d2 = p_actwk->u.obj.radius.unknown * sin % 0x10000;
  short d3 = p_actwk->u.obj.radius.unknown * cos % 0x10000;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xposi = fp16_get_integer(p_parentwk->xposi) + p_actwk->u.obj.oya_offset.x + d2;
  fp16_set_integer(&p_parentwk->xposi, xposi);
  short yposi = fp16_get_integer(p_parentwk->yposi) + p_actwk->u.obj.oya_offset.y + d3;
  fp16_set_integer(&p_parentwk->yposi, yposi);
}


void circle_move(SKC_sprite_status* p_actwk, unsigned char bit_offset) {
  short sin, cos;
  sinset(p_actwk->u.obj.radius.angle, &sin, &cos);
  long sin_l = sin * 0x10000;
  long cos_l = cos * 0x10000;
  sin_l /= 1 << bit_offset;
  cos_l /= 1 << bit_offset;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->xposi = p_parentwk->xposi + sin_l;
  p_actwk->yposi = p_parentwk->yposi + cos_l;
}


void circle_mover(SKC_sprite_status* p_actwk, unsigned char bit_offset) {
  short sin, cos;
  sinset(p_actwk->u.obj.radius.angle, &sin, &cos);
  long sin_l = sin * 0x10000;
  long cos_l = cos * 0x10000;
  sin_l /= 1 << bit_offset;
  cos_l /= 1 << bit_offset;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->actflg.hflip == 1) {
    sin_l = -sin_l;
  }
  p_actwk->xposi = p_parentwk->xposi + sin_l;
  p_actwk->yposi = p_parentwk->yposi + cos_l;
}


void circle_moveo(SKC_sprite_status* p_actwk, unsigned char bit_offset) {
  short sin, cos;
  sinset(p_actwk->u.obj.radius.angle, &sin, &cos);
  long sin_l = sin * 0x10000;
  long cos_l = cos * 0x10000;
  sin_l /= 1 << bit_offset;
  cos_l /= 1 << bit_offset;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->xposi = p_parentwk->xposi + p_actwk->u.obj.oya_offset.x * 0x10000 + sin_l;
  p_actwk->yposi = p_parentwk->yposi + p_actwk->u.obj.oya_offset.y * 0x10000 + cos_l;
}


void circle_movet(SKC_sprite_status* p_actwk, unsigned char* p_sin_data) {
  SKC_point point = get_radius_point(p_actwk, p_sin_data);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xposi = fp16_get_integer(p_parentwk->xposi) + point.x;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_parentwk->yposi) + point.y;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


static SKC_point get_radius_point(SKC_sprite_status* p_actwk, unsigned char* p_sin_data) {
  SKC_point point;
  short d0 = p_actwk->u.obj.radius.angle % 64;
  short d4 = -d0 - 1;

  switch (p_actwk->u.obj.radius.angle / 64) {
    case 0: // dir00_3f
      point.x = p_sin_data[d0];
      point.y = p_sin_data[64 + d4];
      break;
    case 1: // dir40_7f
      point.x = p_sin_data[64 + d4];
      point.y = -p_sin_data[d0];
      break;
    case 2: // dir80_bf
      point.x = -p_sin_data[d0];
      point.y = -p_sin_data[64 + d4];
      break;
    case 3: // dirc0_ff
      point.x = -p_sin_data[64 + d4];
      point.y = p_sin_data[d0];
      break;
  }

  return point;
}


void circle_moveto(SKC_sprite_status* p_actwk, unsigned char* p_sin_data) {
  SKC_point point = get_radius_point(p_actwk, p_sin_data);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xoffset = p_actwk->u.obj.oya_offset.x;
  if (p_actwk->actflg.hflip == 1) {
    xoffset = -xoffset;
  }
  short xposi = fp16_get_integer(p_parentwk->xposi) + xoffset + point.x;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_parentwk->yposi) + p_actwk->u.obj.oya_offset.y + point.y;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void sin_movety(SKC_sprite_status* p_actwk, unsigned char* p_sin_data) {
  SKC_point point = get_radius_point(p_actwk, p_sin_data);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short yposi = fp16_get_integer(p_parentwk->yposi) + point.y;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void sin_movex(SKC_sprite_status* p_actwk, unsigned char* p_sin_data) {
  short point_x;

  switch (p_actwk->u.obj.radius.angle / 64) {
    case 0: // rightdown
      point_x = p_sin_data[p_actwk->u.obj.radius.angle];
      break;
    case 1: // rightup
      point_x = p_sin_data[127 - p_actwk->u.obj.radius.angle];
      break;
    case 2: // leftup
      point_x = -p_sin_data[p_actwk->u.obj.radius.angle % 64];
      break;
    case 3: // leftdown
      point_x = -p_sin_data[255 - p_actwk->u.obj.radius.angle];
      break;
  }

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->actflg.hflip == 1) {
    point_x = -point_x;
  }
  short xposi = fp16_get_integer(p_parentwk->xposi) + p_actwk->u.obj.oya_offset.x + point_x;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_parentwk->yposi) + p_actwk->u.obj.oya_offset.y;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void sin_movey(SKC_sprite_status* p_actwk, unsigned char* p_sin_data) {
  short point_y;

  switch (p_actwk->u.obj.radius.angle / 64) {
    case 0: // rightdown
      point_y = p_sin_data[p_actwk->u.obj.radius.angle];
      break;
    case 1: // rightup
      point_y = p_sin_data[127 - p_actwk->u.obj.radius.angle];
      break;
    case 2: // leftup
      point_y = -p_sin_data[p_actwk->u.obj.radius.angle % 64];
      break;
    case 3: // leftdown
      point_y = -p_sin_data[255 - p_actwk->u.obj.radius.angle];
      break;
  }

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xposi = fp16_get_integer(p_parentwk->xposi) + p_actwk->u.obj.oya_offset.x;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_parentwk->yposi) + p_actwk->u.obj.oya_offset.y + point_y;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void time_fout(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    set_emy_fout0(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


void time_fouts(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    set_emy_fout0(p_actwk);
  }
  else {
    speedset(p_actwk);
    actionsub(p_actwk);
  }
}


void time_fouts2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    set_emy_fout0(p_actwk);
  }
  else {
    speedset(p_actwk);
    actionsub(p_actwk);
  }
}


void time_foutsg20(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    set_emy_fout0(p_actwk);
  }
  else {
    speedsetg20(p_actwk);
    chk_actsubc(p_actwk);
  }
}


void bs_time_fout(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    g_ram.bossstart = 1;
    set_emy_fout1(p_actwk);
  }
}


void boss_flash(SKC_sprite_status* p_actwk) {
  g_ram.colorwk[17] = g_ram.colorwk[17] == 0 ? 0xEEE : 0;
}


void emy_wrt_init(SKC_sprite_status* p_actwk, SKC_wrt_init_data* p_data) {
  int bit = 0;
  unsigned char flags = g_ram.emy_wrt_flg[p_data->flg_index];

  for ( ; bit < p_data->cnt + 1; ++bit) {
    if (!BIT_IS_SET(flags, 0)) goto ok;
    flags >>= 1;
  }

  p_actwk->r_ptr = 0;
  p_actwk->xposi = 0;
  p_actwk->yposi = 0;
  p_actwk->u.obj.userflag = 0;
  memset(&p_actwk->actflg, 0, sizeof(p_actwk->actflg));
  memset(&p_actwk->u.obj.cddat, 0, sizeof(p_actwk->u.obj.cddat));
  return;

ok:
  SET_BIT(g_ram.emy_wrt_flg[p_data->flg_index], bit);
  p_actwk->u.obj.wrt.flg_bit = bit;
  p_actwk->u.obj.wrt.flg_index = p_data->flg_index;
  p_actwk->sproffset = p_data->sproffset + bit * p_data->sproffset_increase;
  p_actwk->patbase = p_data->patbase;
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  p_actwk->u.obj.cddat.wrt = 1;
  p_actwk->u.obj.wrt.prev_patno = 255;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->r_no += 2;
}


void set_emy_wchg(SKC_sprite_status* p_actwk, SKC_wrt_data* p_data) {
  if (p_actwk->patno == p_actwk->u.obj.wrt.prev_patno) return;

  p_actwk->u.obj.wrt.prev_patno = p_actwk->patno;
  unsigned short vram_adr = (p_actwk->sproffset & 0x7FF) << 5;
  unsigned short* wrtpat = p_data->wrtpat[p_actwk->patno];
  unsigned short cnt = *wrtpat++;

  for (int i = 0; i < cnt + 1; ++i) {
    unsigned short instruction = *wrtpat++;
    unsigned char* source = p_data->pat + ((instruction & 0xFFF0) * 2);
    unsigned short word_cnt = ((instruction & 0xF) + 1) * 16;
    unsigned short destination = vram_adr;
    vram_adr += word_cnt * 2;
    copy_data_vram(source, destination, word_cnt);
  }
}


void chk_emy_fout0(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    emy_fout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


void emy_fout(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.flagwork_index != 0) {
    CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
  }
  p_actwk->u.obj.cddat.die = 1;
  p_actwk->r_ptr = &frameout;
}


void chk_emy_fout1(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    emy_fout1(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


void emy_fout1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.flagwork_index != 0) {
    CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
  }
  p_actwk->u.obj.actflg0.ko_die = 1;
  p_actwk->r_ptr = &frameout;
}


void chk_emy_fout3(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    set_emy_fout0(p_actwk);
  }
  else {
    short yposi = fp16_get_integer(p_actwk->yposi) - (g_ram.scra_v_posit >> 16) + 128;
    if ((unsigned short)yposi > 512) {
      set_emy_fout0(p_actwk);
    }
    else {
      actionsub(p_actwk);
    }
  }
}


void chk_break_fout(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    set_emy_fout01(p_actwk);
  }
  else {
    short yposi = fp16_get_integer(p_actwk->yposi) - (g_ram.scra_v_posit >> 16) + 128;
    if ((unsigned short)yposi > 512) {
      set_emy_fout01(p_actwk);
    }
    else {
      if (p_actwk->u.obj.actflg0.flicker == 1) {
        actionsub(p_actwk);
      }
      p_actwk->u.obj.actflg0.flicker ^= 1;
    }
  }
}


void chk_emy_foutc0(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    emy_fout(p_actwk);
  }
  else {
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
}


void chk_emy_foutc1(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    emy_fout1(p_actwk);
  }
  else {
    colibufferchk(p_actwk);
    actionsub(p_actwk);
  }
}


void chk_emy_foutc3(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    set_emy_fout0(p_actwk);
  }
  else {
    short yposi = fp16_get_integer(p_actwk->yposi) - (g_ram.scra_v_posit >> 16) + 128;
    if ((unsigned short)yposi > 512) {
      set_emy_fout0(p_actwk);
    }
    else {
      colibufferchk(p_actwk);
      actionsub(p_actwk);
    }
  }
}


void chk_emy_foutw0(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    wchg_fout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


void wchg_fout(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.flagwork_index != 0) {
    CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
  }
  set_wchg_fout0(p_actwk);
}


void set_wchg_fout0(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  p_actwk->u.obj.cddat.die = 1;
  clr_wchg_bit(p_actwk);
}


void clr_wchg_bit(SKC_sprite_status* p_actwk) {
  CLEAR_BIT(g_ram.emy_wrt_flg[p_actwk->u.obj.wrt.flg_index], p_actwk->u.obj.wrt.flg_bit);
}


void chk_emy_foutw1(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    wchg_fout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


void chk_emy_foutwc0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.die == 1) {
    wchg_die(p_actwk);
  }
  else {
    unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
    if (chunk_xposi > 640) {
      wchg_fout(p_actwk);
    }
    else {
      colibufferchk(p_actwk);
      actionsub(p_actwk);
    }
  }
}


void wchg_die(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  clr_wchg_bit(p_actwk);
}


void chk_emy_foutwc1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.die == 1) {
    wchg_die(p_actwk);
  }
  else {
    unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
    if (chunk_xposi > 640) {
      wchg_fout(p_actwk);
    }
    else {
      colibufferchk(p_actwk);
      actionsub(p_actwk);
    }
  }
}


void chk_emy_foutn0(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    emy_fout(p_actwk);
  }
}


void chk_emy_foutn1(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    emy_fout(p_actwk);
  }
}


void chk_emy_foutnc0(SKC_sprite_status* p_actwk) {
  unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
  if (chunk_xposi > 640) {
    emy_fout(p_actwk);
  }
  else {
    colibufferchk(p_actwk);
  }
}


void set_emy_fout0(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  p_actwk->u.obj.cddat.die = 1;
}


void set_emy_fout1(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  p_actwk->u.obj.actflg0.ko_die = 1;
}


static void set_emy_fout01(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  p_actwk->u.obj.cddat.die = 1;
  p_actwk->u.obj.actflg0.ko_die = 1;
}


void set_break_spd(SKC_sprite_status* p_actwk, unsigned char type) {
  unsigned char index = p_actwk->u.obj.userflag / 2 + type / 4;
  set_break_spd0(p_actwk, index);
}


static void set_break_spd0(SKC_sprite_status* p_actwk, unsigned char index) {
  struct {
    short x;
    short y;
  }
  speed_tbl[39] = {
   { -0x100, -0x100 },
   {  0x100, -0x100 },
   { -0x200, -0x200 },
   {  0x200, -0x200 },
   { -0x300, -0x200 },
   {  0x300, -0x200 },
   { -0x200, -0x200 },
   {      0, -0x200 },
   { -0x400, -0x300 },
   {  0x400, -0x300 },
   {  0x300, -0x300 },
   { -0x400, -0x300 },
   {  0x400, -0x300 },
   { -0x200, -0x200 },
   {  0x200, -0x200 },
   {      0, -0x100 },
   {  -0x40, -0x700 },
   {  -0x80, -0x700 },
   { -0x180, -0x700 },
   { -0x100, -0x700 },
   { -0x200, -0x700 },
   { -0x280, -0x700 },
   { -0x300, -0x700 },
   {      0, -0x100 },
   { -0x100, -0x100 },
   {  0x100, -0x100 },
   { -0x200, -0x100 },
   {  0x200, -0x100 },
   { -0x200, -0x200 },
   {  0x200, -0x200 },
   { -0x300, -0x200 },
   {  0x300, -0x200 },
   { -0x300, -0x300 },
   {  0x300, -0x300 },
   { -0x400, -0x300 },
   {  0x400, -0x300 },
   { -0x200, -0x300 },
   {  0x200, -0x300 }
  };

  p_actwk->xspeed = speed_tbl[index].x;
  p_actwk->yspeed = speed_tbl[index].y;
  if (p_actwk->actflg.hflip == 1) {
    p_actwk->xspeed = -p_actwk->xspeed;
  }
}


unsigned char make_dir(SKC_sprite_status* p_actwk) {
  SKC_chk_distance_result result = chk_distance(p_actwk);
  if (result.xdistance != result.ydistance) {
    if ((unsigned short)result.ydistance <= (unsigned short)result.xdistance) {
      unsigned short distance = (unsigned short)result.ydistance * 0x10000 / (unsigned short)result.xdistance;
      if (result.right) {
        if ((unsigned short)result.xdistance < 0x8000) return 2;
        if (!result.right) return 1;
        return 3;
      }
      else {
        if ((unsigned short)result.xdistance < 0x8000) return 6;
        if (result.below) return 5;
        return 7;
      }
    }
    else {
      unsigned short distance = (unsigned short)result.xdistance * 0x10000 / (unsigned short)result.ydistance;
      if (!result.below) {
        if (distance < 0x8000) return 0;
        if (result.right) return 1;
        return 7;
      }
      else {
        if (distance < 0x8000) return 4;
        if (result.right) return 3;
        return 5;
      }
    }
  }
  else {
    if (result.right) {
      if (!result.below) return 1;
      return 3;
    }
    else {
      if (result.below) return 5;
      return 7;
    }
  }
}


void set_init_spd(SKC_sprite_status* p_actwk, short xspeed) {
  SKC_chk_distance_result result = chk_distance0(p_actwk, &g_ram.actwk[0]);
  p_actwk->actflg.hflip = 0;
  if (result.right) {
    xspeed = -xspeed;
    p_actwk->actflg.hflip = 1;
  }
  p_actwk->xspeed = xspeed;
}


void get_closer(SKC_sprite_status* p_actwk, SKC_sprite_status* p_otherwk, short max_speed, short accel) {
  bool x_equal = fp16_get_integer(p_actwk->xposi) == fp16_get_integer(p_otherwk->xposi);
  if (!x_equal) {
    short accel_copy = accel;
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= (unsigned short)fp16_get_integer(p_otherwk->xposi)) {
      accel_copy = -accel_copy;
    }
    short new_xspeed = p_actwk->xspeed + accel_copy;
    if (new_xspeed >= -max_speed && new_xspeed <= max_speed) {
      p_actwk->xspeed = new_xspeed;
    }
  }
  if (fp16_get_integer(p_actwk->yposi) != fp16_get_integer(p_otherwk->yposi)) {
    short accel_copy = accel;
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) >= (unsigned short)fp16_get_integer(p_otherwk->yposi)) {
      accel_copy = -accel_copy;
    }
    short new_yspeed = p_actwk->yspeed + accel_copy;
    if (new_yspeed >= -max_speed && new_yspeed <= max_speed) {
      p_actwk->yspeed = new_yspeed;
    }
  }
  else if (x_equal) {
    p_actwk->xspeed = 0;
    p_actwk->yspeed = 0;
  }
}


void get_closer_x(SKC_sprite_status* p_actwk, SKC_sprite_status* p_otherwk, short max_speed, short accel) {
  short other_xposi = fp16_get_integer(p_otherwk->xposi) + p_actwk->u.obj.oya_offset.x;
  if ((unsigned short)other_xposi < fp16_get_integer(p_actwk->xposi)) {
    accel = -accel;
  }
  short new_xspeed = p_actwk->xspeed + accel;
  if (new_xspeed >= -max_speed && new_xspeed <= max_speed) {
    p_actwk->xspeed = new_xspeed;
  }
}


void get_closer_y(SKC_sprite_status* p_actwk, SKC_sprite_status* p_otherwk, short max_speed, short accel) {
  short other_yposi = fp16_get_integer(p_otherwk->yposi) + p_actwk->u.obj.oya_offset.y;
  if ((unsigned short)other_yposi < fp16_get_integer(p_actwk->yposi)) {
    accel = -accel;
  }
  short new_yspeed = p_actwk->yspeed + accel;
  if (new_yspeed >= -max_speed && new_yspeed <= max_speed) {
    p_actwk->yspeed = new_yspeed;
  }
}


void get_closer_o(SKC_sprite_status* p_actwk, SKC_sprite_status* p_otherwk, short max_speed, short accel) {
  short other_xposi = fp16_get_integer(p_otherwk->xposi) + p_actwk->u.obj.oya_offset.x;
  bool x_equal = other_xposi == fp16_get_integer(p_actwk->xposi);
  if (!x_equal) {
    short accel_copy = accel;
    if (other_xposi < fp16_get_integer(p_actwk->xposi)) {
      accel_copy = -accel_copy;
    }
    short new_xspeed = p_actwk->xspeed + accel_copy;
    if (new_xspeed >= -max_speed && new_xspeed <= max_speed) {
      p_actwk->xspeed = new_xspeed;
    }
  }
  short other_yposi = fp16_get_integer(p_otherwk->yposi) + p_actwk->u.obj.oya_offset.y;
  if (other_yposi != fp16_get_integer(p_actwk->yposi)) {
    if ((unsigned short)other_yposi < fp16_get_integer(p_actwk->yposi)) {
      accel = -accel;
    }
    short new_yspeed = p_actwk->yspeed + accel;
    if (new_yspeed >= -max_speed && new_yspeed <= max_speed) {
      p_actwk->yspeed = new_yspeed;
    }
  }
  else if (x_equal) {
    p_actwk->xspeed = 0;
    p_actwk->yspeed = 0;
  }
}


void fadeout_act(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &fadeout_act__fadeout;
  p_actwk->u.obj.fade.step_cnt = 7;
  g_ram.fade_flag = 0xFF;
  fadeout_act__fadeout(p_actwk);
}


static void fadeout_act__fadeout(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->u.obj.timer = p_actwk->u.obj.fade.timer_init;
  unsigned short* p_palette = &g_ram.colorwk[p_actwk->u.obj.fade.pal_offset];

  for (int i = 0; i < p_actwk->u.obj.fade.cor_cnt + 1; ++i) {
    fadeout_1cor(p_palette, 0x0E, 0xE0);
    ++p_palette;
  }

  if (p_actwk->u.obj.fade.step_cnt-- == 0) {
    g_ram.fade_flag = 0;
    set_emy_fout0(p_actwk);
  }
}


void fadeout_1cor(unsigned short* p_palette, unsigned char mask_low, unsigned char mask_high) {
  unsigned char blue = ((*p_palette & 0xFF00) >> 8) & mask_low;
  if (blue != 0) {
    blue -= 0x02;
  }
  *p_palette = (blue << 8) | (*p_palette & 0x00FF);
  unsigned char green = *p_palette & 0x00FF;
  unsigned char red = green;
  green &= mask_high;
  if (green != 0) {
    green -= 0x20;
  }
  red &= mask_low;
  if (red != 0) {
    red -= 0x02;
  }
  red |= green;
  *p_palette = (*p_palette & 0xFF00) | red;
}


void fadein_act(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &fadein_act__fadein;
  p_actwk->u.obj.fade.step_cnt = 7;
  g_ram.fade_flag = 0xFF;
  fadein_act__fadein(p_actwk);
}


static void fadein_act__fadein(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->u.obj.timer = p_actwk->u.obj.fade.timer_init;
  unsigned short* p_palette = &g_ram.colorwk2[p_actwk->u.obj.fade.target_pal_offset];
  unsigned short* p_target_palette = &g_ram.colorwk[p_actwk->u.obj.fade.pal_offset];

  for (int i = 0; i < p_actwk->u.obj.fade.cor_cnt + 1; ++i) {
    fadein_1cor(p_palette, p_target_palette, 0x0E, 0xE0);
    ++p_palette;
  }

  if (p_actwk->u.obj.fade.step_cnt-- == 0) {
    g_ram.fade_flag = 0;
    set_emy_fout0(p_actwk);
  }
}


void fadein_1cor(unsigned short* p_palette, unsigned short* p_target_palette, unsigned char mask_low, unsigned char mask_high) {
  unsigned char blue = ((*p_palette & 0xFF00) >> 8) & mask_low;
  unsigned char target_blue = ((*p_target_palette & 0xFF00) >> 8) & mask_low;
  if (blue < target_blue) {
    blue += 0x02;
  }
  *p_palette = (blue << 8) | (*p_palette & 0x00FF);
  unsigned char green = *p_palette & 0x00FF;
  unsigned char red = green;
  green &= mask_high;
  unsigned char green_target = *p_target_palette & 0x00FF;
  unsigned char red_target = green_target;
  green_target &= mask_high;
  if (green < green_target) {
    green += 0x20;
  }
  red &= mask_low;
  red_target &= mask_low;
  if (red < red_target) {
    red += 0x02;
  }
  red |= green;
  *p_palette = (*p_palette & 0xFF00) | red;
}


void spd_pt_chg(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  pt_chg(p_actwk);
}


void spd2_pt_chg(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  pt_chg(p_actwk);
}


void spdg20_pt_chg(SKC_sprite_status* p_actwk) {
  speedsetg20(p_actwk);
  pt_chg(p_actwk);
}


void pk_spd2_pt_tim(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  spd2_pt_tim(p_actwk);
}


void spd2_pt_tim(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  pt_tim(p_actwk);
}


void pt_tim(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  dec_timer(p_actwk);
}


void ko0_tim_act(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  tim_act(p_actwk);
}


void tim_act(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
  actionsub(p_actwk);
}


void bos_tim_act(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    actionsub(p_actwk);
  }
  else {
    p_actwk->actflg.onscreen = 0;
    p_actwk->u.obj.timer = 119;
    SKC_actwkchk_result result = actwkchk();
    if (result.actwk_ptr != 0) {
      result.actwk_ptr->r_ptr = &res_bgm_act;
    }
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


void bos_tim_act0(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    actionsub(p_actwk);
  }
  else {
    p_actwk->actflg.onscreen = 0;
    p_actwk->u.obj.timer = 119;
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


void spd2_tim_actc(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  dec_timer(p_actwk);
  chk_actsubc(p_actwk);
}


void ko0_tpg_actc(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  tim_tpg(p_actwk);
}


void tim_tpg(SKC_sprite_status* p_actwk) {
  time_pg(p_actwk);
  chk_actsubc(p_actwk);
}


void pg_spd_fout3(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  spd_fout3(p_actwk);
}


void spd_fout3(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  chk_emy_fout3(p_actwk);
}


void pg_spd_foutc3(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  spd_foutc3(p_actwk);
}


void spd_foutc3(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  chk_emy_foutc3(p_actwk);
}


void spd2_tim(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  dec_timer(p_actwk);
}


void pk_spd2_tim(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  dec_timer(p_actwk);
}


void pt_actc(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  chk_actsubc(p_actwk);
}


void pt_act(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  actionsub(p_actwk);
}


static void spd2_pt_tim_act(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  pt_chg(p_actwk);
  dec_timer(p_actwk);
  //actionsub(p_actwk);
}


void pt_tim_actc(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  dec_timer(p_actwk);
  //chk_actsubc(p_actwk);
}


void set_emy_die(SKC_sprite_status* p_actwk) {
  set_emy_die0(p_actwk);
  set_emy_die1(p_actwk);
}


void set_emy_die1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_relatedwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_relatedwk->yspeed < 0) {
    p_relatedwk->yspeed += 0x100;
  }
  else if (fp16_get_integer(p_relatedwk->yposi) >= fp16_get_integer(p_actwk->yposi)) {
    p_relatedwk->yspeed -= 0x100;
  }
  else {
    p_relatedwk->yspeed = -p_relatedwk->yspeed;
  }
}


void set_emy_die0(SKC_sprite_status* p_actwk) {
  unsigned short escoretbl[4] = {
    10, 20, 50, 100
  };

  p_actwk->u.obj.cddat.die = 1;
  p_actwk->colino = 0;
  unsigned short prev_emyscorecnt = g_ram.emyscorecnt;
  g_ram.emyscorecnt += 2;
  if (prev_emyscorecnt >= 6) {
    prev_emyscorecnt = 6;
  }
  p_actwk->u.obj.score_id = g_ram.emyscorecnt < 32 ? prev_emyscorecnt : 10;
  unsigned short score = g_ram.emyscorecnt < 32 ? escoretbl[prev_emyscorecnt / 2] : 1000;
  scoreup(score);
  p_actwk->r_ptr = &bakuhatu;
  p_actwk->r_no = 0;
}


void set_pl_damage(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  playdamageset(p_playerwk, p_actwk);
}


bool chk_pl_attack(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_playerwk->u.play.cddat.muteki == 1) return true;
  if (p_playerwk->mstno == 9 || p_playerwk->mstno == 2) return true;

  switch (p_playerwk->u.play.character) {
    case SONIC:
    default:
      break;
    case MILES:
      if (p_playerwk->u.play.talent_status != 0 && p_playerwk->u.play.cddat.underwater == 0) {
        short xposi = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi);
        short yposi = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi);
        short angle = atan(xposi, yposi) - 32;
        if (angle < 64) return true;
      }
      break;
    case KNUCKLES:
      if (p_playerwk->u.play.talent_status == 1 || p_playerwk->u.play.talent_status == 3) return true;
      break;
  }

  return false;
}


bool chk_gacha_gacha(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.gacha.timer-- == 0) {
    p_actwk->u.obj.gacha.lr_cnt = 5;
    p_actwk->u.obj.gacha.timer = 60;
  }
  unsigned short swdata = p_actwk->u.obj.gacha.pad == 0 ? g_ram.swdata1 : g_ram.swdata2;
  if (!are_buttons_pressed(swdata, PAD_L | PAD_R)) return false;
  unsigned short prev_swdata = p_actwk->u.obj.gacha.prev_swdata;
  p_actwk->u.obj.gacha.prev_swdata = swdata;
  if (are_buttons_pressed(prev_swdata, PAD_L) == are_buttons_pressed(swdata, PAD_L)) return false;
  if (are_buttons_pressed(prev_swdata, PAD_R) == are_buttons_pressed(swdata, PAD_R)) return false;
  if (p_actwk->u.obj.gacha.lr_cnt-- > 0) return false;
  return true;
}


bool chk_emy_col(SKC_sprite_status* p_actwk, SKC_sprite_status** pp_coliwk) {
  unsigned char pl_wk_tbl[4] = {
    0, 0, 1, 1
  };

  if (p_actwk->colicnt == 0) return false;

  unsigned char pl_wk = pl_wk_tbl[p_actwk->colicnt & 3];
  p_actwk->colicnt = 0;
  p_actwk->u.obj.ko = pl_wk;
  *pp_coliwk = &g_ram.actwk[pl_wk];
  return true;
}


bool emy_col_a0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_coliwk, short* p_col_data) {
  short coli_xposi = fp16_get_integer(p_coliwk->xposi) + p_col_data[0];
  if (fp16_get_integer(p_actwk->xposi) < coli_xposi) return false;
  coli_xposi += p_col_data[1];
  if (fp16_get_integer(p_actwk->xposi) >= coli_xposi) return false;
  short coli_yposi = fp16_get_integer(p_coliwk->yposi) + p_col_data[2];
  if (fp16_get_integer(p_actwk->yposi) < coli_yposi) return false;
  coli_yposi += p_col_data[3];
  if (fp16_get_integer(p_actwk->yposi) >= coli_yposi) return false;
  return true;
}


bool emy_col_a1(SKC_sprite_status* p_actwk, SKC_sprite_status* p_coliwk, short* p_col_data) {
  short xposi = fp16_get_integer(p_actwk->xposi) + p_col_data[0];
  if (xposi < fp16_get_integer(p_coliwk->xposi)) return false;
  xposi += p_col_data[1];
  if (fp16_get_integer(p_coliwk->xposi) >= xposi) return false;
  short yposi = fp16_get_integer(p_actwk->yposi) + p_col_data[2];
  if (fp16_get_integer(p_coliwk->yposi) < yposi) return false;
  yposi += p_col_data[3];
  if (fp16_get_integer(p_coliwk->yposi) >= yposi) return false;
  return true;
}


SKC_chk_emy_colt_result chk_emy_colt(SKC_sprite_status* p_actwk, short* p_col_data) {
  short left_x = fp16_get_integer(p_actwk->xposi) + p_col_data[0];
  short right_x = left_x + p_col_data[1];
  short top_y = fp16_get_integer(p_actwk->yposi) + p_col_data[2];
  short bottom_y = top_y + p_col_data[3];
  SKC_chk_emy_colt_result result = { false, false };
  result.pl2 = chk_emy_colt__col(&g_ram.actwk[1], left_x, right_x, top_y, bottom_y);
  result.pl = chk_emy_colt__col(&g_ram.actwk[0], left_x, right_x, top_y, bottom_y);
  return result;
}


static bool chk_emy_colt__col(SKC_sprite_status* p_playerwk, short left_x, short right_x, short top_y, short bottom_y) {
  if ((unsigned short)fp16_get_integer(p_playerwk->xposi) < (unsigned short)left_x) return false;
  if ((unsigned short)fp16_get_integer(p_playerwk->xposi) >= (unsigned short)right_x) return false;
  if ((unsigned short)fp16_get_integer(p_playerwk->yposi) < (unsigned short)top_y) return false;
  if ((unsigned short)fp16_get_integer(p_playerwk->yposi) >= (unsigned short)bottom_y) return false;
  return true;
}


void set_emy_cor(unsigned short (*p_color_data)[16]) {
  memcpy(&g_ram.colorwk[16], *p_color_data, sizeof(*p_color_data));
}


void chk_ride_flg(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.cddat.plride == 0 && p_actwk->u.obj.cddat.pl2ride == 0) return;

  if (p_actwk->u.obj.cddat.plride == 1) {
    p_actwk->u.obj.cddat.plride = 0;
    g_ram.actwk[0].u.play.cddat.ride = 0;
    g_ram.actwk[0].u.play.cddat.jump = 1;
  }
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->u.obj.cddat.pl2ride = 0;
    g_ram.actwk[1].u.play.cddat.ride = 0;
    g_ram.actwk[1].u.play.cddat.jump = 1;
  }
}


void emy_cor_chg(SKC_sprite_status* p_actwk) {
  if (g_ram.fade_flag != 0) return;

  for (int i = 0; i < 2; ++i) {
    if (g_ram.cchg_work[i].items_ptr == 0) break;
    if (g_ram.cchg_work[i].timer-- > 0) continue;

    SKC_cchg_work* p_work = &g_ram.cchg_work[i];
    SKC_cchg_item* p_item = *(p_work->items_ptr);
    unsigned short* p_palette = &g_ram.colorwk[p_item->palette_index];
    short* p_data = p_item->data + p_work->item_data_index;
    if (p_data[0] < 0) {
      if (p_item->frame_counter_max) {
        switch (-p_data[0]) {
          case 8: // next
            ++p_work->frame_counter;
            if (p_work->frame_counter >= p_item->frame_counter_max) {
              p_work->items_ptr += p_data[1];
              p_item = *(p_work->items_ptr);
              p_palette = &g_ram.colorwk[p_item->palette_index];
              p_work->timer = 0;
              p_work->frame_counter = 0;
            }
            break;
          case 12: // end
          default:
            ++p_work->frame_counter;
            if (p_work->frame_counter >= p_item->frame_counter_max) {
              g_ram.cchg_callback_ptr(p_actwk);
              continue;
            }
            break;
        }
      }
      p_data = p_item->data;
    }
    memcpy(p_palette, p_data, sizeof((p_item->color_cnt_per_chunk + 1) * sizeof(unsigned short)));
    p_data += p_item->color_cnt_per_chunk + 1;
    p_work->timer = p_data[0];
    p_work->item_data_index = &p_data[1] - p_item->data;
  }
}


void cor_chg_cnt(SKC_sprite_status* p_actwk, SKC_cchg_cnt_info* p_info, unsigned short* p_palette) {
  if (g_ram.fade_flag != 0) return;
  if (p_actwk->u.obj.cchg.timer-- > 0) return;

  ++p_actwk->u.obj.cchg.command_index;
  if (p_info->commands[p_actwk->u.obj.cchg.command_index].items_index < 0) {
    p_actwk->u.obj.cchg.command_index = 0;
  }
  SKC_cchg_cnt_command command = p_info->commands[p_actwk->u.obj.cchg.command_index];
  p_actwk->u.obj.cchg.timer = command.timer_init;
  unsigned short* p_data = p_info->items_ptr[command.items_index];
  memcpy(p_palette, p_data, (p_info->color_cnt_per_command + 1) * sizeof(unsigned short));
}


void chk_oya_pri(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  CLEAR_BIT(p_actwk->sproffset, 15);
  p_actwk->sproffset |= p_parentwk->sproffset & 1 << 15;
  p_actwk->sprpri = p_parentwk->sprpri;
}


void chk_oya_pri_1(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_return) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  CLEAR_BIT(p_actwk->sproffset, 15);
  p_actwk->sproffset |= p_parentwk->sproffset & 1 << 15;
  p_actwk->r_ptr = p_return;
}


void set_damg_cor07(unsigned char* p_pal_offset_data, unsigned short* p_color_data) {
  g_ram.colorwk[*p_pal_offset_data] = *p_color_data;
  ++p_pal_offset_data;
  ++p_color_data;
  set_damg_cor06(p_pal_offset_data, p_color_data);
}


void set_damg_cor06(unsigned char* p_pal_offset_data, unsigned short* p_color_data) {
  g_ram.colorwk[*p_pal_offset_data] = *p_color_data;
  ++p_pal_offset_data;
  ++p_color_data;
  set_damg_cor05(p_pal_offset_data, p_color_data);
}


void set_damg_cor05(unsigned char* p_pal_offset_data, unsigned short* p_color_data) {
  g_ram.colorwk[*p_pal_offset_data] = *p_color_data;
  ++p_pal_offset_data;
  ++p_color_data;
  set_damg_cor04(p_pal_offset_data, p_color_data);
}


void set_damg_cor04(unsigned char* p_pal_offset_data, unsigned short* p_color_data) {
  g_ram.colorwk[*p_pal_offset_data] = *p_color_data;
  ++p_pal_offset_data;
  ++p_color_data;
  set_damg_cor03(p_pal_offset_data, p_color_data);
}


void set_damg_cor03(unsigned char* p_pal_offset_data, unsigned short* p_color_data) {
  g_ram.colorwk[*p_pal_offset_data] = *p_color_data;
  ++p_pal_offset_data;
  ++p_color_data;
  set_damg_cor02(p_pal_offset_data, p_color_data);
}


void set_damg_cor02(unsigned char* p_pal_offset_data, unsigned short* p_color_data) {
  g_ram.colorwk[*p_pal_offset_data] = *p_color_data;
  ++p_pal_offset_data;
  ++p_color_data;
  set_damg_cor01(p_pal_offset_data, p_color_data);
}


void set_damg_cor01(unsigned char* p_pal_offset_data, unsigned short* p_color_data) {
  g_ram.colorwk[*p_pal_offset_data] = *p_color_data;
}


void chk_framein(SKC_sprite_status* p_actwk, SKC_sprite_status_handler p_return) {
  SKC_sprite_pattern* space_pt[1] = { 0 };

  p_actwk->patbase = space_pt;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 32;
  p_actwk->sprvs = 32;
  p_actwk->u.obj.callback_ptr = p_return;
  p_actwk->r_ptr = &chk_framein__chk;
  chk_framein__chk(p_actwk);
}


static void chk_framein__chk(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    unsigned short chunk_xposi = ((unsigned short)fp16_get_integer(p_actwk->xposi) & 0xFF80) - g_ram.scr_x_no;
    if (chunk_xposi <= 640) {
      actionsub(p_actwk);
    }
    else {
      if (p_actwk->u.obj.flagwork_index != 0) {
        CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
      }
      frameout(p_actwk);
    }
  }
  else {
    p_actwk->r_ptr = p_actwk->u.obj.callback_ptr;
  }
}


void res_bgm_act(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 120;
  bgmset(-31);
  p_actwk->r_ptr = &res_bgm_act__cnt;
  res_bgm_act__cnt(p_actwk);
}


static void res_bgm_act__cnt(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  reset_bgm();
  frameout(p_actwk);
}


void set_bgm_act(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 90;
  bgmset(-31);
  p_actwk->r_ptr = &set_bgm_act__cnt;
  set_bgm_act__cnt(p_actwk);
}


static void set_bgm_act__cnt(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  g_ram.bgm_act = p_actwk->u.obj.userflag;
  bgmset(p_actwk->u.obj.userflag);
  frameout(p_actwk);
}


void reset_bgm(void) {
  short bgm_id = bgm_tbl[get_zone(g_ram.stageno_i) * 2 + get_act(g_ram.stageno_i)];
  g_ram.bgm_act = bgm_id;
  if (g_ram.actwk[0].u.play.cddat.muteki == 1) {
    bgm_id = 44;
  }
  bgmset(bgm_id);
}


void reset_pl_data(void) {
  reset_pl_data0(&g_ram.actwk[0]);
}


void reset_pl_data0(SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.control_bitfield = 0;
  p_playerwk->u.play.cddat.jump = 0;
  p_playerwk->mstno = 80;
  p_playerwk->mstrestart = 5;
  p_playerwk->patcnt = 0;
  p_playerwk->pattim = 0;
}


void set_midbos_die(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &midbos_die1;
  g_ram.act_clear_flag = 0xFF;
  p_actwk->u.obj.actflg0.ko_die = 1;
  p_actwk->u.obj.timer = 119;
  p_actwk->u.obj.callback_ptr = &midbos_die2_init;
}


SKC_cg_data kanbst_cg_tbl = {
  1,
  {
    { kanbst_cg, 0xD3C0 },
    { item_cg, 0x9880 }
  }
};


static void midbos_die1(SKC_sprite_status* p_actwk) {
  dec_timer(p_actwk);
}


static void midbos_die2_init(SKC_sprite_status* p_actwk) {
  SKC_set_act05_data kanban_set_tbl = {
    0,
    &kanban
  };

  p_actwk->r_ptr = &midbos_die2;
  g_ram.bossstart = 0;
  set_act05(p_actwk, &kanban_set_tbl);
  Load_PLC_Raw(p_actwk, &kanbst_cg_tbl);
  cg_reset();
}


void midbos_die2(SKC_sprite_status* p_actwk) {
  if (g_ram.act_clear_flag != 0) return;

  p_actwk->r_ptr = &midbos_die3;
  reset_pl_data();
  reset_pl_data0(&g_ram.actwk[1]);
}


static void midbos_die3(SKC_sprite_status* p_actwk) {
  if (g_ram.act_start_flag == 0) return;

  reset_scrlim(p_actwk);
  frameout(p_actwk);
}


void clr_ride_flg(SKC_sprite_status* p_actwk) {
  chk_ride_flg(p_actwk);
  frameout(p_actwk);
}


void chk_boss_set(SKC_sprite_status* p_actwk, unsigned short* p_limit_data, SKC_sprite_status_handler p_return) {
  if (g_ram.scra_v_posit >> 16 < p_limit_data[0]
      || g_ram.scra_v_posit >> 16 > p_limit_data[1]
      || g_ram.scra_h_posit >> 16 < p_limit_data[2]
      || g_ram.scra_h_posit >> 16 > p_limit_data[3]) {
    frameoutchk3(p_actwk);
  }
  else {
    CLEAR_BIT(p_actwk->direc2, 7);
    if (g_ram.scra_v_posit >> 16 > p_limit_data[4]) {
      SET_BIT(p_actwk->direc2, 7);
    }
    CLEAR_BIT(p_actwk->direc2, 6);
    if (g_ram.scra_h_posit >> 16 > p_limit_data[6]) {
      SET_BIT(p_actwk->direc2, 6);
    }
    p_actwk->r_ptr = p_return;
  }
}


void fix_scr_l(SKC_sprite_status* p_actwk) {
  g_ram.scralim_left = g_ram.scra_h_posit >> 16;
  if (g_ram.scralim_n_down >= g_ram.scralim_down) {
    g_ram.scralim_up = g_ram.scralim_n_down;
    if (p_actwk->u.obj.scralim_unknown2 <= g_ram.scra_h_posit >> 16) {
      p_actwk->u.obj.callback_ptr(p_actwk);
    }
  }
}


void chk_scr_bgm(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(p_actwk->direc2, 0) && p_actwk->u.obj.timer-- == 0) {
    g_ram.bgm_act = p_actwk->direc1;
    bgmset(p_actwk->direc1);
    SET_BIT(p_actwk->direc2, 0);
  }
  if (!BIT_IS_SET(p_actwk->direc2, 1)) {
    if (!BIT_IS_SET(p_actwk->direc2, 7)) {
      if (g_ram.scra_v_posit >> 16 >= g_ram.scralim_b_up) {
        chk_scr_bgm__set_v_bit(p_actwk);
      }
      else {
        g_ram.scralim_up = g_ram.scra_v_posit >> 16;
      }
    }
    else {
      if (g_ram.scra_v_posit >> 16 <= g_ram.scralim_b_down + 96) { // chk_d
        chk_scr_bgm__set_v_bit(p_actwk);
      }
    }
  }
  if (!BIT_IS_SET(p_actwk->direc2, 2)) {
    if (!BIT_IS_SET(p_actwk->direc2, 6)) {
      if (g_ram.scra_h_posit >> 16 >= g_ram.scralim_b_left) { // chk_l
        chk_scr_bgm__set_h_bit(p_actwk);
      }
      else {
        g_ram.scralim_left = g_ram.scra_h_posit >> 16;
      }
    }
    else {
      if (g_ram.scra_h_posit >> 16 <= g_ram.scralim_b_right) { // chk_r
        chk_scr_bgm__set_h_bit(p_actwk);
      }
      else {
        g_ram.scralim_right = g_ram.scra_h_posit >> 16;
      }
    }
  }
  if ((p_actwk->direc2 & 7) == 7) {
    p_actwk->direc2 = 0;
    p_actwk->mspeed = 0;
    p_actwk->direc1 = 0;
    p_actwk->u.obj.callback_ptr(p_actwk);
  }
}


static void chk_scr_bgm__set_v_bit(SKC_sprite_status* p_actwk) {
  SET_BIT(p_actwk->direc2, 1);
  g_ram.scralim_up = g_ram.scralim_b_up;
  g_ram.scralim_n_down = g_ram.scralim_b_down;
}


static void chk_scr_bgm__set_h_bit(SKC_sprite_status* p_actwk) {
  SET_BIT(p_actwk->direc2, 2);
  g_ram.scralim_left = g_ram.scralim_b_left;
  g_ram.scralim_right = g_ram.scralim_b_right;
}


void boss_init(SKC_sprite_status* p_actwk, unsigned short* p_limit_data) {
  g_ram.bossstart = 1;
  scr_bgm_init(p_actwk, p_limit_data);
}


void scr_bgm_init(SKC_sprite_status* p_actwk, unsigned short* p_limit_data) {
  bgmset(-31);
  p_actwk->u.obj.timer = 120;
  scr_bgm_init0(p_limit_data);
}


void scr_bgm_init0(unsigned short* p_limit_data) {
  g_ram.scralim_m_up = g_ram.scralim_up;
  g_ram.scralim_m_down = g_ram.scralim_n_down;
  g_ram.scralim_m_left = g_ram.scralim_left;
  g_ram.scralim_m_right = g_ram.scralim_right;
  g_ram.scralim_b_up = p_limit_data[0];
  g_ram.scralim_b_down = p_limit_data[1];
  g_ram.scralim_b_left = p_limit_data[2];
  g_ram.scralim_b_right = p_limit_data[3];
}


void reset_scrlim(SKC_sprite_status* p_actwk) {
  if (get_zone(g_ram.stageno) == SANDOPOLIS) return;

  unsigned short stage_lim[4] = &stage_lim_tbl[get_zone(g_ram.stageno)][ACT_2][0];
  g_ram.scralim_m_left = stage_lim[0];
  g_ram.scralim_m_right = stage_lim[1];
  g_ram.scralim_m_up = stage_lim[2];
  g_ram.scralim_m_down = stage_lim[3];
  g_ram.scralim_n_down = stage_lim[3];
  if (get_zone(g_ram.stageno) != HYDROCITY) {
    set_scrlim_act(p_actwk);
  }
}


void set_scrlim_act(SKC_sprite_status* p_actwk) {
  set_act00(p_actwk, &chglimrud_set_tbl);
}


SKC_set_act00_data chglimrud_set_tbl = {
  2,
  {
    { &chg_scr_lim_r, 0, 0 },
    { &chg_scr_lim_u, 0, 0 },
    { &chg_scr_lim_d, 0, 0 }
  }
};


void reset_all_scrlim(SKC_sprite_status* p_actwk) {
  unsigned short stage_lim[4] = &stage_lim_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)][0];
  g_ram.scralim_m_left = stage_lim[0];
  g_ram.scralim_m_right = stage_lim[1];
  g_ram.scralim_m_up = stage_lim[2];
  g_ram.scralim_m_down = stage_lim[3];
  g_ram.scralim_n_down = stage_lim[3];
  set_act06(p_actwk, &all_limchg_set_tbl);
}


void set_stageno(unsigned short stageno) {
  g_ram.stageno = stageno;
  g_ram.stageno_i = stageno;
  g_ram.gameflag = 1;
  g_ram.markerno = 0;
  g_ram.marker_flag = 0;
}


void set_cont_se(signed char cont_se) {
  if (!(g_ram.systemtimer & 0xF)) {
    soundset(cont_se);
  }
}


void flashout_act(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.fade.step_cnt = 7;
  p_actwk->r_ptr = &flashout_act__cnt;
  g_ram.fade_flag = 0xFF;
  flashout_act__cnt(p_actwk);
}


static void flashout_act__cnt(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->u.obj.timer = p_actwk->u.obj.fade.timer_init;
  unsigned short* p_palette = g_ram.colorwk;

  for (int i = 0; i < 64; ++i) {
    flashout_1cor(p_palette);
    ++p_palette;
  }

  if (p_actwk->u.obj.fade.step_cnt-- == 0) {
    if (p_actwk->u.obj.userflag != 0) {
      p_actwk->r_ptr = &flashin_act;
      p_actwk->u.obj.actflg0.flash = 1;
    }
    else {
      g_ram.fade_flag = 0;
      set_emy_fout0(p_actwk);
    }
  }
}


void flashout_1cor(unsigned short* p_palette) {
  unsigned char green = *p_palette & 0x00FF;
  unsigned char red = green;
  green &= 0xE0;
  red &= 0x0E;
  if (green < 0xE0) {
    green += 0x20;
  }
  if (red < 0x0E) {
    red += 0x02;
  }
  red |= green;
  *p_palette = (*p_palette & 0xFF00) | red;
  unsigned char blue = ((*p_palette & 0xFF00) >> 8) & 0x0E;
  if (blue < 0x0E) {
    blue += 0x02;
  }
  *p_palette = (blue << 8) | (*p_palette & 0x00FF);
}


void flashin_act(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.fade.step_cnt = 7;
  p_actwk->u.obj.timer = 3;
  p_actwk->r_ptr = &flashin_act__cnt;
  flashin_act__cnt(p_actwk);
}


static void flashin_act__cnt(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- > 0) return;

  p_actwk->u.obj.timer = 3;
  unsigned short* p_palette = g_ram.colorwk;
  unsigned short* p_target_palette = g_ram.colorwk2;

  for (int i = 0; i < 64; ++i) {
    flashin_1cor(p_palette, p_target_palette);
    ++p_palette;
    ++p_target_palette;
  }

  if (p_actwk->u.obj.fade.step_cnt-- == 0) {
    g_ram.fade_flag = 0;
    set_emy_fout0(p_actwk);
  }
}


void flashin_1cor(unsigned short* p_palette, unsigned short* p_target_palette) {
  unsigned char green_target = *p_target_palette & 0x00FF;
  unsigned char red_target = green_target;
  green_target &= 0xE0;
  red_target &= 0x0E;
  unsigned char green = *p_palette & 0x00FF;
  unsigned char red = green;
  green &= 0xE0;
  red &= 0x0E;
  if (green > green_target) {
    green -= 0x20;
  }
  if (red > red_target) {
    red -= 0x02;
  }
  red |= green;
  *p_palette = (*p_palette & 0xFF00) | red;
  unsigned char blue_target = ((*p_target_palette & 0xFF00) >> 8) & 0x0E;
  unsigned char blue = ((*p_palette & 0xFF00) >> 8);
  if (blue > blue_target) {
    blue -= 0x02;
  }
  *p_palette = (blue << 8) | (*p_palette & 0x00FF);
}


int chk_play_type(void) {
  int ret;

  switch (g_ram.play_type) {
    case PLAY_TYPE_SONIC_AND_MILES:
    case PLAY_TYPE_SONIC:
    default:
      ret = 0;
      if (g_ram.emeraldcnt == 7) {
        ret = 2;
      }
      break;
    case PLAY_TYPE_MILES:
      ret = 1;
      break;
  }

  return ret;
}


void boss_die_init(SKC_sprite_status* p_actwk) {
  g_ram.pltime_f = 0;
  boss_die_init0(p_actwk);
}


void boss_die_init0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.timer = 63;
  scoreup(100);
  p_actwk->actflg.onscreen = 0;
}


void wrt_player(void) {
  SKC_sprite_status* p_playerwk = &g_ram.actwk[0];
  play_wrt_tbl[p_playerwk->u.play.character](p_playerwk);
}


static SKC_sprite_status_handler play_wrt_tbl[3] = {
  &wrt_play,
  &wrt_fox,
  &wrt_knuckles
};


void wrt_player0(SKC_sprite_status* p_playerwk) {
  if (p_playerwk->r_ptr == 0) return;

  play_wrt_tbl[p_playerwk->u.play.character](p_playerwk);
}


void set_friend_cg(SKC_sprite_status* p_actwk) {
  Load_PLC_Raw(p_actwk, &bakuhatu_cg_tbl);
  set_friend_cg0(p_actwk);
}


void set_friend_cg0(SKC_sprite_status* p_actwk) {
  static SKC_cg_data z00 = {
    1,
    {
      { flicky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z01 = {
    1,
    {
      { pocky_cg, 0xB000 },
      { rocky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z02 = {
    1,
    {
      { flicky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z03 = {
    1,
    {
      { pocky_cg, 0xB000 },
      { flicky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z04 = {
    1,
    {
      { ricky_cg, 0xB000 },
      { flicky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z05 = {
    1,
    {
      { pecky_cg, 0xB000 },
      { rocky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z06 = {
    1,
    {
      { flicky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z07 = {
    1,
    {
      { ricky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z08 = {
    1,
    {
      { pocky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z09 = {
    1,
    {
      { flicky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z0a = {
    1,
    {
      { pocky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z0b = {
    1,
    {
      { ricky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z0c = {
    1,
    {
      { ricky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  static SKC_cg_data z0d_z17 = {
    1,
    {
      { flicky_cg, 0xB000 },
      { cucky_cg, 0xB240 }
    }
  };
  SKC_cg_data* cg_tbl[24] = {
    &z00,
    &z01,
    &z02,
    &z03,
    &z04,
    &z05,
    &z06,
    &z07,
    &z08,
    &z09,
    &z0a,
    &z0b,
    &z0c,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17,
    &z0d_z17
  };

  Load_PLC_Raw(p_actwk, cg_tbl[get_zone(g_ram.stageno)]);
}


void get_ring(unsigned short cnt) {
  g_ram.plring_act += cnt;
  if (RING_MAX < g_ram.plring_act) {
    g_ram.plring_act = RING_MAX;
  }
  g_ram.plring += cnt;
  if (RING_MAX < g_ram.plring) {
    g_ram.plring = RING_MAX;
  }
  SET_BIT(g_ram.plring_f, 0);
  if (RING_EXTRA_LIFE_1 < g_ram.plring) {
    bgmset(51);
  }
  else if (!BIT_IS_SET(g_ram.plring_f2, 1)) {
    SET_BIT(g_ram.plring_f2, 1);
    get_ring__1up();
  }
  else if (RING_EXTRA_LIFE_2 < g_ram.plring) {
    bgmset(51);
  }
  else if (!BIT_IS_SET(g_ram.plring_f2, 2)) {
    SET_BIT(g_ram.plring_f2, 2);
    get_ring__1up();
  }
  else {
    bgmset(51);
  }
}


static void get_ring__1up(void) {
  ++g_ram.DAT_08fffecc;
  ++g_ram.pl_suu;
  ++g_ram.pl_suu_f;
  bgmset(42);
}


void wrt_zoom(SKC_sprite_status* p_actwk) {
  g_ram.zoom_tile_cnt = 0;
  memset(g_ram.zoombuffer, 0, sizeof(g_ram.zoombuffer));
  FUN_0082698c(p_actwk->sproffset);
  copy_data_vram(g_ram.zoombuffer, p_actwk->u.obj.zoom.vram_offset, g_ram.zoom_tile_cnt * 16);
}


void speedset2_m(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.zoom.xposi += p_actwk->xspeed * 0x100;
  p_actwk->u.obj.zoom.yposi += p_actwk->yspeed * 0x100;
}


void zoom_posi_ctr(SKC_sprite_status* p_actwk) {
  short d4 = 256 / (p_actwk->u.obj.zoom.unknown + 4);
  short xposi = fp16_get_integer(p_actwk->u.obj.zoom.xposi) - d4;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_actwk->u.obj.zoom.yposi) - d4;
  fp16_set_integer(&p_actwk->yposi, yposi);
}


void aim_emy_pl(SKC_sprite_status* p_actwk, unsigned char d5) {
  aim_emy_pl0(p_actwk, &g_ram.actwk[0], d5);
}


void aim_emy_pl0(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char d5) {
  aim_emy_pl1(p_actwk, fp16_get_integer(p_playerwk->xposi), fp16_get_integer(p_playerwk->yposi), d5);
}


void aim_emy_pl1(SKC_sprite_status* p_actwk, short xposi, short yposi, unsigned char d5) {
  xposi -= fp16_get_integer(p_actwk->xposi);
  bool neg_xposi = xposi < 0;
  if (neg_xposi) {
    xposi = -xposi;
  }
  yposi -= fp16_get_integer(p_actwk->yposi);
  bool neg_yposi = yposi < 0;
  if (neg_yposi) {
    yposi = -yposi;
  }
  bool swap = xposi < yposi;
  short xspeed, yspeed;
  if (xposi != yposi) {
    if (swap) {
      short temp = xposi;
      xposi = yposi;
      yposi = temp;
    }
    yspeed = ((unsigned short)yposi << 16) / (unsigned short)xposi;
    xspeed = 0x100 << d5;
    yspeed >>= 8 - d5;
  }
  else if (xposi == 0) {
    xspeed = 0x100 << d5;
    yspeed >>= 8 - d5;
  }
  else {
    xspeed = 0x100 << d5;
    yspeed = 0x100 << d5;
  }
  if (swap) {
    short temp = xspeed;
    xspeed = yspeed;
    yspeed = temp;
  }
  if (neg_xposi) {
    xspeed = -xspeed;
  }
  if (neg_yposi) {
    yspeed = -yspeed;
  }
  p_actwk->xspeed = xspeed;
  p_actwk->yspeed = yspeed;
}


short chk_pl_angle(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  unsigned char angle_id = 0;
  short xposi = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi);
  if (xposi < 0) {
    xposi = -xposi;
    angle_id += 4;
  }
  short yposi = fp16_get_integer(p_playerwk->yposi) - fp16_get_integer(p_actwk->yposi);
  if (yposi < 0) {
    yposi = -yposi;
    angle_id += 2;
  }
  if (yposi < xposi) {
    short temp = xposi;
    xposi = yposi;
    yposi = temp;
    angle_id += 1;
  }
  short ret = xposi;
  if (yposi != 0) {
    xposi <<= 5;
    ret = (unsigned short)xposi / (unsigned short)yposi;

    switch (angle_id) {
      case 0:
        break;
      case 1:
        ret -= 64;
        ret = -ret;
        break;
      case 2:
        ret -= 128;
        ret = -ret;
        break;
      case 3:
        ret += 64;
        break;
      case 4:
        ret = -ret;
        break;
      case 5:
        ret += 192;
        break;
      case 6:
        ret += 128;
        break;
      case 7:
        ret -= 192;
        ret = -ret;
        break;
    }
  }
  return ret;
}


void mask_spr(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.relative_coordinates = 1;
  mask_spr0(p_actwk);
}


void mask_spr0(SKC_sprite_status* p_actwk) {
  p_actwk->sproffset = 0;
  p_actwk->patbase = maskpat;
  p_actwk->sprhs = 32;
  p_actwk->r_ptr = !BIT_IS_SET(p_actwk->u.obj.userflag, 3) ? &mask_spr0__wait0 : &mask_spr0__wait1;
  p_actwk->sprvs = (p_actwk->u.obj.userflag & 0xF0) >> 2;
  p_actwk->patno = (p_actwk->u.obj.userflag & 0xF0) >> 4;
  p_actwk->sprpri = (p_actwk->u.obj.userflag & 7) * 0x80;
}


static void mask_spr0__wait0(SKC_sprite_status* p_actwk) {
  g_ram.sprhmasks = 0xFF;
  frameoutchk(p_actwk);
}


static void mask_spr0__wait1(SKC_sprite_status* p_actwk) {
  g_ram.sprhmasks = 0xFF;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_actwk->u.obj.actflg0.flash == 0) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


void pl_move_right(SKC_sprite_status* p_actwk) {
  unsigned short swdata = PAD_R << 8 | PAD_R;
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    swdata = PAD_A << 8 | PAD_R << 8 | PAD_R;
  }
  if (g_ram.actwk[0].u.play.cddat.push == 1) {
    p_actwk->u.obj.timer = 31;
    swdata = PAD_A << 8 | PAD_R << 8 | PAD_A | PAD_R;
  }
  g_ram.swdata1_auto = swdata;
}


void set_bane_jump(SKC_sprite_status* p_playerwk, short yspeed) {
  p_playerwk->yspeed = yspeed;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.jump_flag = 0;
  p_playerwk->u.play.spindash_flag = 0;
  p_playerwk->mstno = 16;
  p_playerwk->r_no = 2;
  soundset(177);
}


void chk_pl_dir(SKC_sprite_status* p_actwk) {
  chk_pl_dir__sub(p_actwk, &g_ram.actwk[0]);
  if (g_ram.actwk[1].actflg.onscreen == 1) {
    chk_pl_dir__sub(p_actwk, &g_ram.actwk[1]);
  }
}


static void chk_pl_dir__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  bool left = fp16_get_integer(p_actwk->xposi) < fp16_get_integer(p_playerwk->xposi);
  p_playerwk->actflg.hflip = left;
  p_playerwk->u.play.cddat.left = left;
}


void fox_auto(SKC_sprite_status* p_actwk) {
  if (g_ram.actwk[1].r_ptr == 0) {
    frameout(p_actwk);
  }
  else {
    g_ram.pl2_lock_flag = 1;
    g_ram.fox_auto_timer = 0;
    p_actwk->r_ptr = &fox_auto__cnt;
    fox_auto__cnt(p_actwk);
  }
}


static void fox_auto__cnt(SKC_sprite_status* p_actwk) {
  if (g_ram.pl2_lock_flag != 0) {
    g_ram.swdata2_auto = 0;
  }
  else {
    g_ram.swdata2 = 0;
    frameout(p_actwk);
  }
}


void nextst(SKC_sprite_status* p_actwk) {
  short col_tbl[4] = { -16, 32, -128, 256 };

  if (!emy_col_a1(p_actwk, &g_ram.actwk[0], col_tbl)) return;

  if (g_ram.play_type == PLAY_TYPE_KNUCKLES && get_zone(g_ram.stageno) == LAVA_REEF) {
    g_ram.disable_interrupts_sram = 0xFF;
    save_game();
  }
  unsigned short stageno = p_actwk->u.obj.userflag << 16;
  stageno >>= 1;
  stageno = stageno & 0xFF00 | rotate_char_left(stageno & 0x00FF, 1);
  set_stageno(stageno);
}


void shake_se_act(SKC_sprite_status* p_actwk) {
  g_ram.scr_shake_flg = 0xFF00;
  p_actwk->r_ptr = &shake_se_act__cnt;
  shake_se_act__cnt(p_actwk);
}


static void shake_se_act__cnt(SKC_sprite_status* p_actwk) {
  if (g_ram.scr_shake_flg == 0) {
    frameout(p_actwk);
  }
  else if (!g_ram.systemtimer & 0xF) {
    soundset(111);
  }
}


void set_many_posi(SKC_sprite_status* p_actwk, unsigned char* p_posi_data) {
  for (int i = 0; i < p_actwk->u.compound.child_cnt; ++i) {
    short xposi = *p_posi_data++;
    if (p_actwk->actflg.hflip == 1) {
      xposi = -xposi;
    }
    p_actwk->u.compound.children[i].xposi = xposi + fp16_get_integer(p_actwk->xposi);
    p_actwk->u.compound.children[i].yposi = *p_posi_data++ + fp16_get_integer(p_actwk->yposi);
  }
}


void chg_super(void) {
  g_ram.plring += 50;
  g_ram.ssonicpallet = 1;
  g_ram.ssonicpallet_next = 15;
  g_ram.ssonicflag = 1;
  g_ram.ssonicring_timer = 60;
  g_ram.plmaxspdwk = 0x800;
  g_ram.pladdspdwk = 0x18;
  g_ram.plretspdwk = 0xC0;
  g_ram.actwk[0].mstno = 31;

  switch(g_ram.play_type) {
    case PLAY_TYPE_SONIC_AND_MILES:
    case PLAY_TYPE_SONIC:
    default:
      g_ram.actwk[0].patbase = ssonicpat;
      g_ram.ssonicflag = 0xFF;
      g_ram.plmaxspdwk = 0xA00;
      g_ram.pladdspdwk = 0x30;
      g_ram.plretspdwk = 0x100;
      g_ram.actwk[102].r_ptr = &hsonicstars;
      break;
    case PLAY_TYPE_MILES:
      g_ram.ssonicflag = 0;
      g_ram.smilesflag = 1;
      g_ram.actwk[0].mstno = 41;
      g_ram.pl2maxspdwk = 800;
      g_ram.pl2addspdwk = 0x18;
      g_ram.pl2retspdwk = 0xC0;
      g_ram.actwk[102].r_ptr = &smilesflickies;
      break;
    case PLAY_TYPE_KNUCKLES:
      g_ram.actwk[96].r_ptr = &hypertrail;
      break;
  }

  g_ram.actwk[0].u.play.control_bitfield = 0x81;
  g_ram.actwk[0].u.play.muteki_timer = 0;
  g_ram.actwk[0].u.play.cddat.muteki = 1;
}
