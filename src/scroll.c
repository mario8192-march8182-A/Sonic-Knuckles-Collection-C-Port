#include "scroll.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "data/mapinittbl.h"
#include "data/playpositbl.h"
#include "data/zonemaptbl.h"
#include "types/point.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "color.h"
#include "constants.h"
#include "dev.h"
#include "scrchk.h"
#include "objects/save.h"
typedef struct SKC_scroll_work {
  SKC_sprite_status* sprite_ptr;
  long* posit_ptr;
  short lim_min;
  short lim_max;
  short* z_ptr;
}
SKC_scroll_work;
static void playposiset(void);
static void scroll_h(SKC_scroll_work work, short* p_delay, unsigned short plposiwkadr, SKC_point* p_playposiwk);
static void scrh_move(SKC_scroll_work work, short* p_delay, unsigned short plposiwkadr, SKC_point* p_playposiwk);
static void left_check(SKC_scroll_work work, short xoffset);
static void right_check(SKC_scroll_work work, short xoffset);
static void scroll_v(SKC_scroll_work work, short scra_vline);
static void sv_move_main(SKC_scroll_work work, short scra_vline, short yoffset);
static void sv_move_main1(SKC_scroll_work work, short yoffset);
static void sv_move_main2(SKC_scroll_work work, short yoffset);
static void sv_move_sub2(SKC_scroll_work work);
static void sv_move_sub(SKC_scroll_work work, short yoffset);
static void sv_move_minus(SKC_scroll_work work, short yoffset);
static void scrv_up_ch(SKC_scroll_work work, long yposi);
static void sv_move_plus(SKC_scroll_work work, short yoffset);
static void scrv_down_ch(SKC_scroll_work work, long yposi);
static void scrv_move(SKC_scroll_work work, long yposi);
static void vs_scroll_h(SKC_scroll_work work, short* p_delay, unsigned short plposiwkadr, SKC_point* p_playposiwk);
static void vs_left_check(SKC_scroll_work work, short xoffset);
static void vs_right_check(SKC_scroll_work work, short xoffset);

extern sonic3_ram g_ram;


short scr_dir_tbl[24][2][4] = {
  { { 0x1308, 0x6000,      0, 0x0390 }, {      0, 0x4640,      0, 0x0590 } },
  { {      0, 0x6000,      0, 0x1000 }, {      0, 0x6000,      0, 0x1000 } },
  { {      0, 0x6000, -0x100, 0x1000 }, {      0, 0x6000,      0, 0x1000 } },
  { {      0, 0x6000,      0, 0x0B20 }, {      0, 0x6000,  0x580, 0x1000 } },
  { {      0, 0x2E60,      0, 0x0B00 }, {      0, 0x6000,      0, 0x0B00 } },
  { {      0, 0x7000, -0x100, 0x0800 }, {      0, 0x7000,      0, 0x0B20 } },
  { {      0, 0x6000,      0, 0x1000 }, {      0, 0x6000,      0, 0x0B20 } },
  { {      0, 0x4298,      0, 0x0AA0 }, { 0x0098, 0x3C90,  0x620, 0x09A0 } },
  { {      0, 0x4310,      0, 0x0B20 }, {      0, 0x6000, -0x100, 0x0800 } },
  { {      0, 0x2CC0,      0, 0x0B20 }, { 0x0940, 0x3EC0,      0, 0x0B20 } },
  { {      0, 0x19A0, -0x100, 0x1000 }, {      0, 0x6000,      0, 0x0400 } },
  { {      0, 0x6000,      0, 0x0B20 }, {      0, 0x6000,      0, 0x0F10 } },
  { {      0, 0x6000,      0, 0x1000 }, {      0, 0x6000,      0, 0x1000 } },
  { {      0, 0x6000,      0, 0x1000 }, {      0, 0x6000,      0, 0x1000 } },
  { {      0, 0x12C0,  0x100, 0x0190 }, {      0, 0x12C0,  0x100, 0x0190 } },
  { {      0, 0x12C0,  0x200, 0x0390 }, {      0, 0x12C0,  0x200, 0x0390 } },
  { {      0, 0x12C0,  0x100, 0x0190 }, {      0, 0x12C0,  0x100, 0x0190 } },
  { {      0, 0x12C0, -0x100, 0x1000 }, {      0, 0x12C0,      0, 0x0090 } },
  { {      0, 0x12C0,  0x100, 0x0190 }, {      0, 0x12C0,  0x100, 0x0190 } },
  { { 0x0060, 0x0060,      0, 0x0240 }, { 0x0060, 0x0060,      0, 0x0240 } },
  { {      0, 0x0140,      0, 0x0F00 }, {      0, 0x0140,      0, 0x0F00 } },
  { {      0, 0x6000,      0, 0x1000 }, {      0, 0x6000,      0, 0x1000 } },
  { {      0, 0x0EC0,      0, 0x0430 }, {      0, 0x1880,      0, 0x0B20 } },
  { {      0, 0x6000,  0x020, 0x0020 }, { 0x1500, 0x1640,  0x320, 0x0320 } }
};


void scr_set(void) {
  g_ram.scroll_start = 0;
  g_ram.pl_scr_lock_flag = 0;
  g_ram.pl2_scr_lock_flag = 0;
  g_ram.fast_scroll_flag = 0;
  g_ram.zone_flag = 0;
  g_ram.DAT_08fff660 = 0;
  g_ram.scralim_left = scr_dir_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)][0];
  g_ram.scralim_right = scr_dir_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)][1];
  g_ram.scralim_n_left = g_ram.scralim_left;
  g_ram.scralim_n_right = g_ram.scralim_right;
  g_ram.scralim_left2 = g_ram.scralim_left;
  g_ram.scralim_right2 = g_ram.scralim_right;
  g_ram.scralim_up = scr_dir_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)][2];
  g_ram.scralim_down = scr_dir_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)][3];
  g_ram.scralim_n_up = g_ram.scralim_up;
  g_ram.scralim_n_down = g_ram.scralim_down;
  g_ram.scralim_up2 = g_ram.scralim_up;
  g_ram.scralim_down2 = g_ram.scralim_down;
  g_ram.scra_vline = 96;
  g_ram.scra_vline2 = 96;
  g_ram.scrc3 = 0xFFFF;
  g_ram.scrc_v = 0xFFFF;
  playposiset();
}


static void playposiset(void) {
  short xposi, yposi;
  if (g_ram.markerno != 0) {
    playload(0);
    xposi = fp16_get_integer(g_ram.actwk[0].xposi);
    yposi = fp16_get_integer(g_ram.actwk[0].yposi);
  }
  else {
    SKC_point (*p_playpositbl)[2] = g_ram.play_type != PLAY_TYPE_KNUCKLES ? playpositbl : playpositblk;
    xposi = p_playpositbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)].x;
    yposi = p_playpositbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)].y;
    fp16_set_integer(&g_ram.actwk[0].xposi, xposi);
    fp16_set_integer(&g_ram.actwk[0].yposi, yposi);
    if (g_ram.markerno == 0) {
      bool play_type_is_sonic = g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC;
      if (g_ram.stageno == ANGEL_ISLAND_ACT_1 && play_type_is_sonic) {
        fp16_set_integer(&g_ram.actwk[0].xposi, 64);
        yposi = 0x420;
        fp16_set_integer(&g_ram.actwk[0].yposi, yposi);
        xposi = 0;
        g_ram.scralim_left = xposi;
        g_ram.scralim_n_left = xposi;
        g_ram.scralim_left2 = xposi;
      }
      else if (g_ram.stageno == ICECAP_ACT_1 && g_ram.play_type == PLAY_TYPE_MILES) {
        g_ram.scralim_left = 0x35A0;
        g_ram.scralim_n_left = 0x35A0;
        g_ram.scralim_left2 = 0x35A0;
        fp16_set_integer(&g_ram.actwk[0].xposi, 0x3780);
        g_ram.scra_h_posit = 0x36F0 << 16 | g_ram.scra_h_posit & 0x0000FFFF;
        g_ram.vs_scra_h_posit = 0x36F0 << 16 | g_ram.scra_h_posit & 0x0000FFFF;
        fp16_set_integer(&g_ram.actwk[0].yposi, 480);
        g_ram.scralim_up = 512;
        g_ram.scralim_n_up = 512;
        g_ram.scralim_up2 = 512;
        g_ram.scra_v_posit = 512 << 16 | g_ram.scra_v_posit & 0x0000FFFF;
        g_ram.vs_scra_v_posit = 512 << 16 | g_ram.vs_scra_v_posit & 0x0000FFFF;
        return;
      }
      else if (g_ram.stageno == MUSHROOM_HILL_ACT_1 && g_ram.play_type != PLAY_TYPE_KNUCKLES && g_ram.cartridge == 0) {
        g_ram.scralim_left = 192;
        g_ram.scralim_n_left = 192;
        g_ram.scralim_left2 = 192;
        xposi = 352;
      }
      else if (g_ram.stageno == HIDDEN_PALACE
          || g_ram.stageno == DEATH_EGG_ACT_1
          || (g_ram.stageno == LAVA_REEF_ACT_1 && g_ram.play_type == PLAY_TYPE_KNUCKLES)
          || (g_ram.stageno == CARNIVAL_NIGHT_ACT_1 && g_ram.play_type == PLAY_TYPE_KNUCKLES)) {
        xposi += 176;
      }
    }
  }
  xposi -= 160;
  xposi = abs(xposi);
  if (g_ram.vs_flag == 0 && xposi >= g_ram.scralim_right) {
    xposi = g_ram.scralim_right;
  }
  g_ram.scra_h_posit = xposi << 16 | g_ram.scra_h_posit & 0x0000FFFF;
  g_ram.vs_scra_h_posit = xposi << 16 | g_ram.vs_scra_h_posit & 0x0000FFFF;
  yposi -= 96;
  yposi = abs(yposi);
  if (yposi >= g_ram.scralim_down) {
    yposi = g_ram.scralim_down;
  }
  g_ram.scra_v_posit = yposi << 16 | g_ram.scra_v_posit & 0x0000FFFF;
  g_ram.vs_scra_v_posit = yposi << 16 | g_ram.vs_scra_v_posit & 0x0000FFFF;
}


void scroll(void) {
  if (g_ram.scroll_start != 0) return;

  g_ram.scra_hz = 0;
  g_ram.scra_vz = 0;
  g_ram.scra_hz2 = 0;
  g_ram.scra_vz2 = 0;
  if (g_ram.vs_flag == 0) {
    if (g_ram.pl_scr_lock_flag == 0) {
      SKC_sprite_status custom_follow = { 0 };
      custom_follow.xposi = g_ram.custom_follow_xposi;
      custom_follow.yposi = g_ram.custom_follow_yposi;
      SKC_sprite_status* p_sprite = g_ram.custom_follow_flag == 0 ? &g_ram.actwk[0] : &custom_follow;
      if (g_ram.custom_follow_flag != 0) {
        g_ram.custom_follow_flag = 0;
        g_ram.DAT_08ffee24 = 0;
      }
      SKC_scroll_work work = {
        p_sprite,
        &g_ram.scra_h_posit,
        g_ram.scralim_left,
        g_ram.scralim_right,
        &g_ram.scra_hz
      };
      scroll_h(work, &g_ram.DAT_08ffee24, g_ram.plposiwkadr, g_ram.playposiwk);
      work.posit_ptr = &g_ram.scra_v_posit;
      work.lim_min = g_ram.scralim_up;
      work.lim_max = g_ram.scralim_down;
      work.z_ptr = &g_ram.scra_vz;
      short scra_vline = g_ram.play_type != PLAY_TYPE_MILES ? g_ram.scra_vline : g_ram.scra_vline2;
      scroll_v(work, scra_vline);
    }
    scrchk();
  }
  else {
    if (g_ram.pl_scr_lock_flag == 0) {
      SKC_scroll_work work = {
        &g_ram.actwk[0],
        &g_ram.scra_h_posit,
        g_ram.scralim_left,
        g_ram.scralim_right,
        &g_ram.scra_hz
      };
      vs_scroll_h(work, &g_ram.DAT_08ffee24, g_ram.plposiwkadr, g_ram.playposiwk);
      work.posit_ptr = &g_ram.scra_v_posit;
      work.lim_min = g_ram.scralim_up;
      work.lim_max = g_ram.scralim_down;
      work.z_ptr = &g_ram.scra_vz;
      short scra_vline = g_ram.play_type != PLAY_TYPE_MILES ? g_ram.scra_vline : g_ram.scra_vline2;
      scroll_v(work, scra_vline);
    }
    if (g_ram.pl2_scr_lock_flag == 0) {
      SKC_scroll_work work = {
        &g_ram.actwk[1],
        &g_ram.vs_scra_h_posit,
        g_ram.scralim_left2,
        g_ram.scralim_right2,
        &g_ram.scra_hz2
      };
      vs_scroll_h(work, &g_ram.DAT_08ffee28, g_ram.pl2posiwkadr, g_ram.play2posiwk);
      work.posit_ptr = &g_ram.vs_scra_v_posit;
      work.lim_min = g_ram.scralim_up2;
      work.lim_max = g_ram.scralim_down2;
      work.z_ptr = &g_ram.scra_vz2;
      short scra_vline = g_ram.play_type != PLAY_TYPE_MILES ? g_ram.scra_vline : g_ram.scra_vline2;
      scroll_v(work, scra_vline);
    }
    scrchk();
  }
}


static void scroll_h(SKC_scroll_work work, short* p_delay, unsigned short plposiwkadr, SKC_point* p_playposiwk) {
  scrh_move(work, p_delay, plposiwkadr, p_playposiwk);
}


static void scrh_move(SKC_scroll_work work, short* p_delay, unsigned short plposiwkadr, SKC_point* p_playposiwk) {
  short xposi;
  if (*p_delay != 0) {
    *p_delay -= 0x100;
    int index = (short)plposiwkadr - ((*p_delay >> 8) + 1);
    xposi = (unsigned short)p_playposiwk[index].x & 0x7FFF;
  }
  else {
    xposi = fp16_get_integer(work.sprite_ptr->xposi);
  }
  short xoffset = xposi - *work.posit_ptr - 144;
  if (xoffset < 0) {
    left_check(work, xoffset);
  }
  else {
    xoffset -= 16;
    if (xoffset >= 0) {
      right_check(work, xoffset);
    }
    else {
      *work.z_ptr = 0;
    }
  }
}


static void left_check(SKC_scroll_work work, short xoffset) {
  if (xoffset <= -24) {
    xoffset = -24;
  }
  short xposi = xoffset + *work.posit_ptr;
  if (xposi <= work.lim_min) {
    xposi = work.lim_min;
  }
  *work.z_ptr = (xposi - *work.posit_ptr) * 0x100;
  *work.posit_ptr = xposi;
}


static void right_check(SKC_scroll_work work, short xoffset) {
  if (xoffset >= 24) {
    xoffset = 24;
  }
  short xposi = xoffset + *work.posit_ptr;
  if (xposi >= work.lim_max) {
    xposi = work.lim_max;
  }
  *work.z_ptr = (xposi - *work.posit_ptr) * 0x100;
  *work.posit_ptr = xposi;
}


static void scroll_v(SKC_scroll_work work, short scra_vline) {
  short yoffset = fp16_get_integer(work.sprite_ptr->yposi) - *work.posit_ptr;
  if (g_ram.scralim_up == -0x100) {
    yoffset = (unsigned short)yoffset & g_ram.scrc_v;
  }
  if (work.sprite_ptr->u.play.cddat.ball == 1) {
    yoffset -= 5;
  }
  short scra_vline_wk = g_ram.vs_flag == 0 ? scra_vline : scra_vline / 2;
  if (work.sprite_ptr->u.play.cddat.jump == 1) {
    yoffset = yoffset + 32 - scra_vline_wk;
    if (yoffset >= 0) {
      yoffset -= 64;
      if (yoffset < 0) {
        if (g_ram.limmoveflag != 0) {
          sv_move_sub2(work);
        }
        else {
          *work.z_ptr = 0;
        }
      }
      else {
        sv_move_main2(work, yoffset);
      }
    }
    else {
      sv_move_main2(work, yoffset);
    }
  }
  else {
    yoffset -= scra_vline_wk;
    if (yoffset == 0) {
      if (g_ram.limmoveflag != 0) {
        sv_move_sub2(work);
      }
      else {
        *work.z_ptr = 0;
      }
    }
    else {
      sv_move_main(work, scra_vline, yoffset);
    }
  }
}


static void sv_move_main(SKC_scroll_work work, short scra_vline, short yoffset) {
  if (scra_vline != 96) {
    sv_move_main1(work, yoffset);
  }
  else if (g_ram.fast_scroll_flag != 0 || abs(work.sprite_ptr->mspeed) >= 0x800) {
    sv_move_main2(work, yoffset);
  }
  else {
    if (yoffset > 6) {
      sv_move_plus(work, 6 * 0x100);
    }
    else if (yoffset < -16) {
      sv_move_minus(work, 6 * 0x100);
    }
    else {
      sv_move_sub(work, yoffset);
    }
  }
}


static void sv_move_main1(SKC_scroll_work work, short yoffset) {
  if (yoffset > 2) {
    sv_move_plus(work, 2 * 0x100);
  }
  else if (yoffset < -2) {
    sv_move_minus(work, 2 * 0x100);
  }
  else {
    sv_move_sub(work, yoffset);
  }
}


static void sv_move_main2(SKC_scroll_work work, short yoffset) {
  if (yoffset > 24) {
    sv_move_plus(work, 24 * 0x100);
  }
  else if (yoffset < -24) {
    sv_move_minus(work, 24 * 0x100);
  }
  else {
    sv_move_sub(work, yoffset);
  }
}


static void sv_move_sub2(SKC_scroll_work work) {
  g_ram.limmoveflag = 0;
  sv_move_sub(work, 0);
}


static void sv_move_sub(SKC_scroll_work work, short yoffset) {
  short yposi = yoffset + *work.posit_ptr;
  if (yoffset >= 0) {
    scrv_down_ch(work, yposi);
  }
  else {
    scrv_up_ch(work, yposi);
  }
}


static void sv_move_minus(SKC_scroll_work work, short yoffset) {
  long yposi = -yoffset * 0x100 + *work.posit_ptr;
  scrv_up_ch(work, yposi);
}


static void scrv_up_ch(SKC_scroll_work work, long yposi) {
  if (fp16_get_integer(yposi) <= work.lim_min) {
    if (fp16_get_integer(yposi) <= -0x100) {
      short wk = (unsigned short)fp16_get_integer(yposi) & g_ram.scrc_v;
      fp16_set_integer(&yposi, wk);
    }
    else {
      fp16_set_integer(&yposi, work.lim_min);
    }
  }
  scrv_move(work, yposi);
}


static void sv_move_plus(SKC_scroll_work work, short yoffset) {
  long yposi = yoffset * 0x100 + *work.posit_ptr;
  scrv_down_ch(work, yposi);
}


static void scrv_down_ch(SKC_scroll_work work, long yposi) {
  if (fp16_get_integer(yposi) >= work.lim_max) {
    short wk = fp16_get_integer(yposi) - g_ram.scrc_v + 1;
    fp16_set_integer(&yposi, wk);
    if (fp16_get_integer(yposi) >= 0) {
      *work.posit_ptr -= g_ram.scrc_v + 1;
    }
    else {
      fp16_set_integer(&yposi, work.lim_max);
    }
  }
  scrv_move(work, yposi);
}


static void scrv_move(SKC_scroll_work work, long yposi) {
  *work.z_ptr = (unsigned short)((yposi - *work.posit_ptr) / 0x100);
  *work.posit_ptr = g_ram.vs_flag == 0 ? yposi : (unsigned short)fp16_get_integer(yposi) & g_ram.scrc_v;
}


static void vs_scroll_h(SKC_scroll_work work, short* p_delay, unsigned short plposiwkadr, SKC_point* p_playposiwk) {
  short xposi;
  if (*p_delay != 0) {
    *p_delay -= 0x100;
    int index = (short)plposiwkadr - ((*p_delay >> 8) + 1);
    xposi = (unsigned short)p_playposiwk[index].x & 0x7FFF;
  }
  else {
    xposi = fp16_get_integer(work.sprite_ptr->xposi);
  }
  short xoffset = ((unsigned short)(xposi - *work.posit_ptr) & g_ram.scrc3) - 144;
  if (xoffset < 0) {
    vs_left_check(work, xoffset);
  }
  else {
    xoffset -= 16;
    if (xoffset >= 0) {
      vs_right_check(work, xoffset);
    }
    else {
      *work.z_ptr = 0;
    }
  }
}


static void vs_left_check(SKC_scroll_work work, short xoffset) {
  if (xoffset <= -16) {
    xoffset = -16;
  }
  short xposi = xoffset + *work.posit_ptr;
  if (xposi <= work.lim_min) {
    xposi = work.lim_min;
  }
  *work.z_ptr = (xposi - *work.posit_ptr) * 0x100;
  *work.posit_ptr = ((unsigned short)xposi & g_ram.scrc3) + 0x400;
}


static void vs_right_check(SKC_scroll_work work, short xoffset) {
  if (xoffset >= 16) {
    xoffset = 16;
  }
  short xposi = xoffset + *work.posit_ptr;
  if (xposi >= work.lim_max) {
    xposi = work.lim_max;
  }
  *work.z_ptr = (xposi - *work.posit_ptr) * 0x100;
  *work.posit_ptr = ((unsigned short)xposi & g_ram.scrc3) + 0x400;
}


void mapwrt(void) {
  bool play_type_is_sonic = g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC;
  unsigned short stageno = g_ram.stageno;
  if (stageno == ANGEL_ISLAND_ACT_1 && (play_type_is_sonic || g_ram.markerno != 0)) {
    stageno = ANGEL_ISLAND_ACT_1_NO_INTRO;
  }
  SKC_mapinit_data* p_data = &mapinittbl[get_zone(stageno)][get_act(stageno)];
  unsigned char* p_next = unlze(g_ram.blockwk, p_data->blkdata1_ptr);
  if (p_data->blkdata1_ptr != p_data->blkdata2_ptr) {
    unlze(p_next, p_data->blkdata2_ptr);
  }
  p_next = unlze(g_ram.mapwk, p_data->mapdata1_ptr);
  if (p_data->mapdata1_ptr != p_data->mapdata2_ptr) {
    unlze(p_next, p_data->mapdata2_ptr);
  }
  SKC_zonemap* p_zonemap = zonemaptbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
  g_ram.zonemapwk.mapa_col_cnt = p_zonemap->mapa_col_cnt;
  g_ram.zonemapwk.mapb_col_cnt = p_zonemap->mapb_col_cnt;
  g_ram.zonemapwk.mapa_row_cnt = p_zonemap->mapa_row_cnt;
  g_ram.zonemapwk.mapb_row_cnt = p_zonemap->mapb_row_cnt;
  memcpy(g_ram.zonemapwk.row_offsets, p_zonemap->row_offsets, sizeof(g_ram.zonemapwk.row_offsets));
  int cnt = p_zonemap->mapa_col_cnt * p_zonemap->mapa_row_cnt + p_zonemap->mapb_col_cnt * p_zonemap->mapb_row_cnt;
  memcpy(g_ram.zonemapwk.data, p_zonemap->data, cnt);
  if (p_data->ini_cg_no2 != 0 && p_data->ini_cg_no1 != p_data->ini_cg_no2) {
    divdevset(p_data->ini_cg_no2);
  }
  colorset(p_data->colorno1);
}
