#include "scrchk.h"
#include <stdbool.h>
#include <string.h>
#include "types/sonic3ram.h"
#include "utils/bits.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "color.h"
#include "constants.h"
#include "dev.h"
#include "objects/save.h"
#include "objects/zone00/bs00m.h"
static void zone000chk(void);
static void zone000chk0(void);
static void zone000chk1(void);
static void zone000chk2(void);
static void zone000chk3(void);
static void zone000chk4(void);
static unsigned short lim_tbl[6][2];
static void zone001chk(void);
static void zone001chk0(void);
static void zone001chk1(void);
static void zone001chk2(void);
static void zone001chk3(void);
static void zone001chk4(void);
static void zone001chk5(void);
static void zone001chk6(void);
static void zone001chk7(void);
static void zone001chk8(void);
static void zone001chk9(void);
static void zone001chk10(void);
static void zone001chk11(void);
static void zone001chk12(void);
static void zone001chk13(void);
static void zone001chk14(void);
static void zone010chk(void);
static void zone010chk0(void);
static void zone010chk1(void);
static void zone010chk2(void);
static void zone011chk(void);
static void zone011chk0(void);
static void zone011chk1(void);
static void zone02chk(void);
static void zone02chk0(void);
static void zone02chk1(void);
static void zone02chk2(void);
static void zone030chk(void);
static void zone050chk(void);
static void zone050chk0(void);
static void zone050chk1(void);
static void zone050chk2(void);
static void zone051chk(void);
static void zone051chk0(void);
static void zone051chk1(void);
static void zone060chk(void);
static void zone061chk(void);
static void zone061chk0(void);
static void zone061chk1(void);
static void worknai(void);
static void scrset(unsigned short (*p_tbl)[2]);

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void scrchk(void) {
  void(*zonechktbl[24][2])(void) = {
    { &zone000chk, &zone001chk },
    { &zone010chk, &zone011chk },
    { &zone02chk,  &zone02chk  },
    { &zone030chk, &zone030chk },
    { &zone030chk, &zone030chk },
    { &zone050chk, &zone051chk },
    { &zone060chk, &zone061chk },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    },
    { &worknai,    &worknai    }
  };

  zonechktbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)]();
  if (g_ram.scralim_n_down != g_ram.scralim_down) {
    short yoffset = 2;
    if (g_ram.scralim_n_down < g_ram.scralim_down) {
      yoffset = -yoffset;
      if (g_ram.scra_v_posit >> 16 > g_ram.scralim_n_down) {
        g_ram.scralim_down = g_ram.scra_v_posit >> 16 & 0xFFFE;
      }
      g_ram.scralim_down += yoffset;
      g_ram.limmoveflag = 1;
    }
    else {
      if ((g_ram.scra_v_posit >> 16) + 8 >= g_ram.scralim_down && g_ram.actwk[0].u.play.cddat.jump == 1) {
        yoffset *= 4;
      }
      g_ram.scralim_down += yoffset;
      g_ram.limmoveflag = 1;
    }
  }
}


static void zone000chk(void) {
  void(*act_tbl[5])(void) = {
    &zone000chk0,
    &zone000chk1,
    &zone000chk2,
    &zone000chk3,
    &zone000chk4
  };

  act_tbl[g_ram.zone_flag / 2]();
}


static void zone000chk0(void) {
  g_ram.DAT_08fff72e = g_ram.scra_h_posit >> 16 < 0x1000;
  if (g_ram.scra_h_posit >> 16 >= 0x1000) {
    g_ram.scralim_left = g_ram.scra_h_posit >> 16;
    if (g_ram.scra_h_posit >> 16 >= 0x1308) {
      bool play_type_is_sonic = g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC;
      if (g_ram.plflag == 0 && play_type_is_sonic) {
        divdevset(11);
      }
      colorset2(42);
      if (g_ram.play_type == PLAY_TYPE_KNUCKLES) {
        memcpy(&g_ram.colorwk[56], DAT_006b2156, sizeof(unsigned short) * 3);
      }
      g_ram.foxcpu_rno = 2;
      g_ram.zone_flag += 2;
    }
  }
}


static void zone000chk1(void) {
  g_ram.scralim_left = 0x1308;
  if (g_ram.scra_h_posit >> 16 >= 0x1400) {
    bool play_type_is_sonic = g_ram.play_type == PLAY_TYPE_SONIC_AND_MILES || g_ram.play_type == PLAY_TYPE_SONIC;
    if (g_ram.plflag == 0 && play_type_is_sonic) {
      unlze_blocks(&g_ram.blockwk[77], zone0d0blk2);
      unlze_moduled(&g_vram[0x17C0], zone0d0cg2);
      g_ram.DAT_08ffeec6 = 0xFF;
      g_ram.cgchgtim[0] = 0;
      g_ram.cgchgcnt[0] = 5;
      g_ram.cgchgtim[1] = 0;
      g_ram.cgchgcnt[1] = 5;
      g_ram.cgchgtim[2] = 0;
      g_ram.cgchgcnt[2] = 5;
    }
    g_ram.plflag = 1;
    g_ram.plxposi_s = 0x13A0;
    g_ram.plyposi_s = 0x41A;
    playsave1();
    memset(&g_ram.pltime_s, 0, sizeof(g_ram.pltime_s));
    divdevset(8);
    g_ram.zone_flag += 2;
  }
}


static void zone000chk2(void) {
  scrset(lim_tbl);
  g_ram.scralim_up = 0;
  g_ram.colorwk2[47] = 0x20E;
  if (!BIT_IS_SET(g_ram.gmmode, 7) && g_ram.fadecnt == 0) {
    g_ram.colorwk[47] = 0x20E;
  }
  if (g_ram.scra_h_posit >> 16 >= 0x2B00) {
    g_ram.colorwk[47] = 4;
  }
  if (g_ram.scra_h_posit >> 16 >= 0x2C00) {
    g_ram.scralim_up = 0x2E0;
  }
  if (g_ram.scra_h_posit >> 16 >= 0x2D80) {
    unsigned short color = g_ram.play_type != PLAY_TYPE_KNUCKLES ? 0xC02 : DAT_006b215c;
    g_ram.colorwk[47] = color;
    g_ram.scralim_left = 0x2D80;
    divdevset(90);
    g_ram.zone_flag += 2;
  }
}


static void zone000chk3(void) {
  scrset(lim_tbl);
  g_ram.scralim_left = g_ram.scra_h_posit >> 16;
  if (g_ram.scra_h_posit >> 16 >= 0x2E00) {
    unlze_moduled(&g_vram[0xA000], DAT_005fc562);
    divdevset(12);
    g_ram.zone_flag += 2;
  }
}


static void zone000chk4(void) {
  g_ram.scralim_left = g_ram.scra_h_posit >> 16;
}


static unsigned short lim_tbl[6][2] = {
  { 0x1650, 0x8390 },
  { 0x1B00, 0x83B0 },
  { 0x2000, 0x8430 },
  { 0x2B00, 0x84C0 },
  { 0x2D80, 0x83B0 },
  { 0xFFFF, 0x82E0 }
};


static void zone001chk(void) {
  void(*act_tbl[15])(void) = {
    &zone001chk0,
    &zone001chk1,
    &zone001chk2,
    &zone001chk3,
    &zone001chk4,
    &zone001chk5,
    &zone001chk6,
    &zone001chk7,
    &zone001chk8,
    &zone001chk9,
    &zone001chk10,
    &zone001chk11,
    &zone001chk12,
    &zone001chk13,
    &zone001chk14
  };

  act_tbl[g_ram.zone_flag / 2]();
}


static void zone001chk0(void) {
  if (g_ram.play_type == PLAY_TYPE_KNUCKLES) {
    g_ram.zone_flag = 18;
    zone001chk9();
  }
  else {
    g_ram.zone_flag += 2;
    zone001chk1();
  }
}


static void zone001chk1(void) {
  if (g_ram.scra_h_posit >> 16 >= 0x2E0) {
    g_ram.scralim_down = 0x590;
    g_ram.scralim_n_down = g_ram.scralim_down;
    g_ram.zone_flag += 2;
    if (g_ram.stageno_i == ANGEL_ISLAND_ACT_2) {
      g_ram.scralim_left = 0xF50;
      g_ram.zone_flag += 2;
    }
  }
}


static void zone001chk2(void) {
  g_ram.scralim_down = g_ram.scra_h_posit >> 16 < 0xED0 ? 0x590 : 0x2B8;
  g_ram.scralim_n_down = g_ram.scralim_down;
  if (g_ram.scra_h_posit >> 16 >= 0xF50) {
    g_ram.scralim_left = 0xF50;
    if (g_ram.editmode == 0) {
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &bs00m1_body;
        fp16_set_integer(&result.actwk_ptr->xposi, 0x11F0);
        fp16_set_integer(&result.actwk_ptr->yposi, 0x289);
      }
    }
    g_ram.zone_flag += 2;
  }
}


static void zone001chk3(void) {
  if (g_ram.scra_h_posit >> 16 < 0x1500) return;

  g_ram.scralim_down = 0x630;
  g_ram.scralim_n_down = g_ram.scralim_down;
  g_ram.zone_flag += 2;
}


static void zone001chk4(void) {
  if (g_ram.scra_h_posit >> 16 < 0x3C00) return;

  unlze_blocks(&g_ram.blockwk[343], DAT_005fe304);
  unlze_moduled(&g_vram[0x3F80], DAT_00601858);
  unlze_moduled(&g_vram[0xA000], DAT_0054a870);
  colorset2(48);
  g_ram.DAT_08ffeec6 = 0xFF;
  g_ram.zone_flag += 2;
}


static void zone001chk5(void) {
  if (g_ram.scra_h_posit >> 16 < 0x3F00) return;

  g_ram.scralim_up = 0x15A;
  g_ram.scralim_n_up = g_ram.scralim_up;
  g_ram.zone_flag += 2;
}


static void zone001chk6(void) {
  if (g_ram.scra_h_posit >> 16 < 0x4000) return;

  g_ram.scralim_down = 0x15A;
  g_ram.scralim_n_down = g_ram.scralim_down;
  g_ram.zone_flag += 2;
}


static void zone001chk7(void) {
  if (g_ram.scra_h_posit >> 16 < 0x4160) return;

  g_ram.DAT_08ffeec4 = 0xFF;
  g_ram.zone_flag += 2;
}


static void zone001chk8(void) {
}


static void zone001chk9(void) {
  if (g_ram.scra_h_posit >> 16 < 0x2E0) return;

  g_ram.scralim_down = 0x590;
  g_ram.scralim_n_down = g_ram.scralim_down;
  g_ram.zone_flag += 2;
  if (g_ram.stageno_i == ANGEL_ISLAND_ACT_2) {
    g_ram.scralim_left = 0x1040;
    g_ram.zone_flag += 2;
  }
}


static void zone001chk10(void) {
  g_ram.scralim_down = g_ram.scra_h_posit >> 16 < 0xE80 ? 0x590 : 0x450;
  g_ram.scralim_n_down = g_ram.scralim_down;
  if (g_ram.scra_h_posit >> 16 >= 0x1040) {
    g_ram.scralim_left = 0x1040;
    if (g_ram.editmode == 0) {
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &bs00m1_body;
        fp16_set_integer(&result.actwk_ptr->xposi, 0x11D0);
        fp16_set_integer(&result.actwk_ptr->yposi, 0x420);
      }
    }
    g_ram.watermoveposi = 0xF80;
    g_ram.zone_flag += 2;
  }
}


static void zone001chk11(void) {
  if (g_ram.scra_h_posit >> 16 < 0x11A0) return;

  g_ram.scralim_n_down = 0x820;
  g_ram.zone_flag += 2;
}


static void zone001chk12(void) {
  if (g_ram.scra_h_posit >> 16 < 0x3B80) return;

  unlze_blocks(&g_ram.blockwk[343], DAT_005fe304);
  unlze_moduled(&g_vram[0x3F80], DAT_00601858);
  colorset2(48);
  g_ram.scralim_left = 0x3B80;
  g_ram.scralim_n_down = 0x5DA;
  g_ram.DAT_08ffeec6 = 0xFF;
  g_ram.zone_flag += 2;
}


static void zone001chk13(void) {
  if (0x3F80 > g_ram.scra_h_posit >> 16) return;

  g_ram.scralim_left = 0x3F80;
  g_ram.zone_flag += 2;
}


static void zone001chk14(void) {
}


static void zone010chk(void) {
  void(*act_tbl[3])(void) = {
    &zone010chk0,
    &zone010chk1,
    &zone010chk2
  };

  act_tbl[g_ram.zone_flag / 2]();
}


static void zone010chk0(void) {
  if (g_ram.scra_h_posit >> 16 >= 0x360) return;
  if (g_ram.scra_v_posit >> 16 < 0x3E0) return;

  g_ram.colorwk[56] = 0xB80;
  g_ram.colorwk[57] = 0x240;
  g_ram.colorwk[58] = 0x220;
  g_ram.zone_flag += 2;
}


static void zone010chk1(void) {
  if (g_ram.scra_h_posit >> 16 < 0x360) {
    if (g_ram.scra_v_posit >> 16 >= 0x3E0) return;

    g_ram.zone_flag -= 2;
  }
  else {
    if (g_ram.scra_v_posit >> 16 < 0x500) return;
    if (g_ram.scra_h_posit >> 16 < 0x900) return;

    g_ram.zone_flag += 2;
  }
  g_ram.colorwk[56] = 0xCEE;
  g_ram.colorwk[57] = 0xACE;
  g_ram.colorwk[58] = 0x08A;
}


static void zone010chk2(void) {
}


static void zone011chk(void) {
  void(*act_tbl[2])(void) = {
    &zone011chk0,
    &zone011chk1
  };

  act_tbl[g_ram.zone_flag / 2];
}


static void zone011chk0(void) {
  if (g_ram.scra_h_posit >> 16 < 0xC00) return;

  g_ram.DAT_08ffeec6 = 0xFF;
  g_ram.zone_flag += 2;
}


static void zone011chk1(void) {
}


static void zone02chk(void) {
  void(*act_tbl[3])(void) = {
    &zone02chk0,
    &zone02chk1,
    &zone02chk2
  };

  act_tbl[g_ram.zone_flag / 2]();
}


static void zone02chk0(void) {
  if (g_ram.scra_v_posit >> 16 < 0x600) return;
  if (g_ram.scra_v_posit >> 16 >= 0x700) return;
  if (g_ram.scra_h_posit >> 16 < 0x3A00) return;

  g_ram.scralim_up = 0x6A0;
  g_ram.scralim_n_up = g_ram.scralim_up;
  g_ram.scralim_down = g_ram.scralim_n_up;
  g_ram.scralim_n_down = g_ram.scralim_down;
  g_ram.scralim_right = 0x3C80;
  g_ram.scralim_n_right = g_ram.scralim_right;
  g_ram.zone_flag += 2;
}


static void zone02chk1(void) {
  if (g_ram.scra_h_posit >> 16 >= 0x3A00) {
    if (0x3C80 <= g_ram.scra_h_posit >> 16) {
      g_ram.scralim_left = 0x3C80;
      g_ram.scralim_n_left = g_ram.scralim_left;
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &bs02b1;
        fp16_set_integer(&result.actwk_ptr->xposi, 0x3D20);
        fp16_set_integer(&result.actwk_ptr->yposi, 0x668);
      }
      g_ram.zone_flag += 2;
    }
  }
  else {
    g_ram.scralim_up = 0;
    g_ram.scralim_down = 0x1000;
    g_ram.scralim_n_up = g_ram.scralim_up;
    g_ram.scralim_n_down = g_ram.scralim_n_up;
    g_ram.scralim_right = 0x6000;
    g_ram.scralim_n_right = g_ram.scralim_right;
    g_ram.zone_flag -= 2;
  }
}


static void zone02chk2(void) {
}


static void zone030chk(void) {
}


static void zone050chk(void) {
  void(*act_tbl[3])(void) = {
    &zone050chk0,
    &zone050chk1,
    &zone050chk2
  };

  act_tbl[g_ram.zone_flag / 2]();
}


static void zone050chk0(void) {
  if (g_ram.scra_h_posit >> 16 < 0x3700) return;
  if (g_ram.scra_v_posit >> 16 < 0x68C) return;

  g_ram.DAT_08ffeec6 = 0xFF;
  g_ram.zone_flag += 2;
}


static void zone050chk1(void) {
  if (g_ram.scra_h_posit >> 16 < 0x3940) return;

  g_ram.DAT_08ffeec6 = 0xFF;
  g_ram.zone_flag += 2;
}


static void zone050chk2(void) {
}


static void zone051chk(void) {
  void(*act_tbl[2])(void) = {
    &zone051chk0,
    &zone051chk1
  };

  act_tbl[g_ram.zone_flag / 2]();
}


static void zone051chk0(void) {
  if (g_ram.scra_h_posit >> 16 < 0x740) return;
  if (g_ram.scra_v_posit >> 16 >= 0x400) return;

  g_ram.scralim_left = 0x740;
  g_ram.zone_flag += 2;
}


static void zone051chk1(void) {
}


static void zone060chk(void) {
}


static void zone061chk(void) {
  void(*act_tbl[2])(void) = {
    &zone061chk0,
    &zone061chk1
  };

  act_tbl[g_ram.zone_flag / 2]();
}


static void zone061chk0(void) {
  if (g_ram.scra_h_posit >> 16 < 0x3BC0) return;
  if (g_ram.scra_v_posit >> 16 < 0x500) return;

  g_ram.zone_flag += 2;
  unlze_blocks(g_ram.blockwk, DAT_00633942);
  unlze_screens(g_ram.mapwk, DAT_0063a366);
  unlze_moduled(&g_vram[0], DAT_00635f04);
  unlze_moduled(&g_vram[0xB400], DAT_0053025c);
}


static void zone061chk1(void) {
}


static void worknai(void) {
}


static void scrset(unsigned short (*p_tbl)[2]) {
  while (g_ram.scra_h_posit >> 16 > (*p_tbl)[0]) {
    ++p_tbl;
  }

  unsigned short yposi = (*p_tbl)[1];
  if (yposi >= 0x8000) {
    yposi &= 0x7FFF;
    g_ram.scralim_down = yposi;
  }
  g_ram.scralim_n_down = yposi;
}
