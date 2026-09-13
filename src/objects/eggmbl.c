#include "eggmbl.h"
#include <string.h>
#include "../data/cg/mblmeggman.h"
#include "../data/cg/mblmsonic.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../dev.h"
#include "../shared.h"
#include "explosion.h"
#include "zone00/bs00b0.h"
#include "zone00/bs00m.h"
static void mbl_eggman0_init(SKC_sprite_status* p_actwk);
static void mbl_eggman0_wait0(SKC_sprite_status* p_actwk);
static void dummy(SKC_sprite_status* p_actwk);
static void mbl_eggman1(SKC_sprite_status* p_actwk);
static void mbl_eggman2(SKC_sprite_status* p_actwk);
static void mbl_eggman2_init(SKC_sprite_status* p_actwk);
static void mbl_eggman2_wait0(SKC_sprite_status* p_actwk);
static void mbl_eggman3_init(SKC_sprite_status* p_actwk);
static void chk_pri(SKC_sprite_status* p_actwk);
static void mbl_eggman3_wait0(SKC_sprite_status* p_actwk);
static void mbl_eggman3_die0(SKC_sprite_status* p_actwk);
static void mbl_msonic(SKC_sprite_status* p_actwk);
static void mbl_msonic_wait0(SKC_sprite_status* p_actwk);
static void eggmbl00(SKC_sprite_status* p_actwk);
static void eggmbl00_init(SKC_sprite_status* p_actwk);
static void eggmbl00_wait0(SKC_sprite_status* p_actwk);
static void eggmbl00_die0(SKC_sprite_status* p_actwk);
static void eggmbl00_die1(SKC_sprite_status* p_actwk);
static void eggmbl01_die0(SKC_sprite_status* p_actwk);
static void eggmbl02(SKC_sprite_status* p_actwk);
static void eggmbl02_init(SKC_sprite_status* p_actwk);
static void eggmbl02_wait0(SKC_sprite_status* p_actwk);
static void eggmbl02_die0(SKC_sprite_status* p_actwk);
static void eggmbl02_die1(SKC_sprite_status* p_actwk);
static void set_eggmbl_away(SKC_sprite_status* p_actwk);
static void eggmbl02_die2(SKC_sprite_status* p_actwk);
static void eggmbl04_init(SKC_sprite_status* p_actwk);
static void eggmbl04_wait0(SKC_sprite_status* p_actwk);
static void eggmbl04_die0(SKC_sprite_status* p_actwk);
static void eggmbl04_die1(SKC_sprite_status* p_actwk);
static void eggmbl04_die2_init(SKC_sprite_status* p_actwk);
static void eggmbl04_die2(SKC_sprite_status* p_actwk);
static void embl_jet(SKC_sprite_status* p_actwk);
static void embl_jet_wait0(SKC_sprite_status* p_actwk);
static void resultembl_wait0(SKC_sprite_status* p_actwk);
static void resmblegg(SKC_sprite_status* p_actwk);
static void resmblegg_wait0(SKC_sprite_status* p_actwk);
static SKC_enemy_init0_data mbl_eggman0_init_tbl;
static SKC_enemy_init0_data mbl_eggman2_init_tbl;
static SKC_enemy_init0_data eggmbl_init_tbl;
static SKC_enemy_init2_data embl_jet_init_tbl;
static SKC_enemy_init0_data mbl_msonic_init_tbl;
static SKC_set_act00_data mbl_eggman2_set_tbl;
static SKC_set_act00_data resmblegg_set_tbl;
static signed char mbl_eggman0_pg00[4];
static signed char mbl_meggman_pg00[6];
static SKC_sprite_pattern* megmbl_pt[4];
static SKC_sprite_pattern megmbl_pt00;
static SKC_sprite_pattern megmbl_pt01;
static SKC_sprite_pattern megmbl_pt02;
static SKC_sprite_pattern megmbl_pt03;
static SKC_sprite_pattern* msmbl_pt[1];
static SKC_sprite_pattern msmbl_pt00;
static SKC_sprite_pattern eggmbl_pt00;
static SKC_sprite_pattern eggmbl_pt01;
static SKC_sprite_pattern eggmbl_pt02;
static SKC_sprite_pattern eggmbl_pt03;
static SKC_sprite_pattern eggmbl_pt04;
static SKC_sprite_pattern eggmbl_pt05;
static SKC_sprite_pattern eggmbl_pt06;
static SKC_sprite_pattern eggmbl_pt07;
static SKC_sprite_pattern eggmbl_pt08;
static SKC_sprite_pattern eggmbl_pt09;
static SKC_sprite_pattern eggmbl_pt10;
static SKC_sprite_pattern eggmbl_pt11;
static SKC_sprite_pattern eggmbl_pt12;
static SKC_sprite_pattern eggrun_pt00;
static SKC_sprite_pattern eggrun_pt01;
static SKC_sprite_pattern eggrun_pt02;
static SKC_sprite_pattern eggrun_pt03;
static SKC_sprite_pattern eggrun_pt04;
static SKC_sprite_pattern eggrun_pt05;
static SKC_sprite_pattern eggrun_pt06;
static SKC_sprite_pattern egg2_pt00;
static SKC_sprite_pattern egg2_pt01;
static SKC_sprite_pattern egg2_pt02;
static SKC_sprite_pattern egg2_pt03;
static SKC_sprite_pattern egg3_pt00;
static SKC_sprite_pattern egg3_pt01;
static SKC_sprite_pattern egg3_pt02;
static SKC_sprite_pattern egg3_pt03;

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];


void mbl_eggman0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &mbl_eggman0_init,
    &mbl_eggman0_wait0,
    &dummy
  };

  ko_offset1(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die1(p_actwk);
}


static void mbl_eggman0_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &mbl_eggman0_init_tbl);
  chk_not_disp(p_actwk);
  p_actwk->u.obj.pg_data_ptr = mbl_eggman0_pg00;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->u.obj.ko = p_parentwk->u.obj.oya;
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    set_megmbl(p_actwk);
  }
}


void set_megmbl(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = megmbl_pt;
  set_megmbl0(p_actwk);
}


void set_megmbl0(SKC_sprite_status* p_actwk) {
  p_actwk->u.obj.pg_data_ptr = mbl_meggman_pg00;
  unlze_moduled(&g_vram[0xA5C0], mbl_meggman_cg);
}


static void mbl_eggman0_wait0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_childwk->u.obj.cddat.die == 0) {
    if (p_childwk->u.obj.cddat.pl2push == 1) {
      p_actwk->patno = 2;
    }
  }
  else {
    p_actwk->r_no = 4;
    p_actwk->patno = 3;
  }
}


static void dummy(SKC_sprite_status* p_actwk) {
}


static void mbl_eggman1(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &mbl_eggman0_init,
    &mbl_eggman0_wait0,
    &dummy
  };

  ko_offset1(p_actwk);
  chk_not_disp(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  if (p_actwk->u.obj.actflg0.flicker == 0) {
    chk_oya_die1(p_actwk);
  }
}


static void mbl_eggman2(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &mbl_eggman2_init,
    &mbl_eggman2_wait0,
    &dummy
  };

  ko_offset1(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_pri(p_actwk);
  chk_oya_die1(p_actwk);
}


static void mbl_eggman2_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &mbl_eggman2_init_tbl);
  p_actwk->u.obj.pg_data_ptr = mbl_eggman0_pg00;
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->u.obj.ko = p_parentwk->u.obj.oya;
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    set_megmbl(p_actwk);
  }
}


static void mbl_eggman2_wait0(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.hflip = (unsigned short)fp16_get_integer(p_actwk->xposi) < (unsigned short)fp16_get_integer(g_ram.actwk[0].xposi);
  p_actwk->patno = p_actwk->u.obj.actflg0.unused2 == 0 ? 0 : 1;
  SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
  if (p_childwk->u.obj.cddat.die == 0) {
    if (p_childwk->u.obj.cddat.pl2push == 1) {
      p_actwk->patno = 2;
    }
  }
  else {
    p_actwk->r_no = 4;
    p_actwk->patno = 3;
  }
}


void mbl_eggman3(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &mbl_eggman3_init,
    &mbl_eggman3_wait0,
    &mbl_eggman3_die0
  };

  ko_offset1(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  chk_oya_die1(p_actwk);
}


static void mbl_eggman3_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &mbl_eggman0_init_tbl);
  p_actwk->u.obj.pg_data_ptr = mbl_eggman0_pg00;
  if (g_ram.actwk[0].u.play.character == KNUCKLES) {
    set_megmbl(p_actwk);
  }
  chk_pri(p_actwk);
}


static void chk_pri(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->sproffset.pr = p_parentwk->sproffset.pr;
}


static void mbl_eggman3_wait0(SKC_sprite_status* p_actwk) {
  pt_chg(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 0) {
    if (p_parentwk->u.obj.cddat.pl2push == 1) {
      p_actwk->patno = 2;
    }
  }
  else {
    p_actwk->r_no = 4;
    p_actwk->patno = 3;
  }
}


static void mbl_eggman3_die0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 0) {
    pt_chg0(p_actwk, mbl_eggman0_pg00);
  }
}


void mbl_eggman4(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[3] = {
    &mbl_eggman3_init,
    &mbl_eggman3_wait0,
    &mbl_eggman3_die0
  };

  ko_offset1(p_actwk);
  chk_oya_pri(p_actwk);
  act_tbl[p_actwk->r_no / 2](p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.end == 0) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void mbl_msonic(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &mbl_msonic_init_tbl);
  p_actwk->r_ptr = &mbl_msonic_wait0;
  unlze_moduled(&g_vram[0xA5C0], mbl_msonic_cg);
}


static void mbl_msonic_wait0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  if (!(g_ram.DAT_08fffa88 & 0xFF)) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void eggmbl00(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[4] = {
    &eggmbl00_init,
    &eggmbl00_wait0,
    &eggmbl00_die0,
    &eggmbl00_die1
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  if (p_actwk->u.obj.actflg0.flicker == 0) {
    actionsub(p_actwk);
  }
}


static void eggmbl00_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &eggmbl_init_tbl);
  p_actwk->patno = p_actwk->u.obj.userflag;
  set_act00(p_actwk, &mbl_eggman1_set_tbl);
}


static void eggmbl00_wait0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  chk_not_disp(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    p_actwk->r_no = 4;
    SKC_sprite_status* p_new_actwk = set_act05(p_actwk, &bsexp01_set_tbl);
    if (p_new_actwk != 0) {
      p_new_actwk->u.obj.userflag = get_zone(g_ram.stageno) != ANGEL_ISLAND ? 4 : 18;
    }
  }
}


static void eggmbl00_die0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 0) {
    chk_not_disp(p_actwk);
    ko_offset1(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    p_actwk->patno = 5;
    p_actwk->yspeed = -0x200;
    p_actwk->u.obj.timer = 127;
  }
}


static void eggmbl00_die1(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->u.obj.actflg0.end = 1;
    g_ram.bossstart = 0;
    set_emy_fout1(p_actwk);
  }
}


void eggmbl01(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &eggmbl02_init,
    &eggmbl02_wait0,
    &eggmbl01_die0,
    &eggmbl02_die1,
    &eggmbl02_die2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  actionsub(p_actwk);
};


static void eggmbl01_die0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 1) {
    p_actwk->r_no = 6;
    p_actwk->patno = 5;
  }
}


static void eggmbl02(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &eggmbl02_init,
    &eggmbl02_wait0,
    &eggmbl02_die0,
    &eggmbl02_die1,
    &eggmbl02_die2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.end == 0) {
    actionsub(p_actwk);
  }
  else {
    set_emy_fout1(p_actwk);
  }
}


static void eggmbl02_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &eggmbl_init_tbl);
  chk_not_disp(p_actwk);
  p_actwk->patno = p_actwk->u.obj.userflag;
  set_act00(p_actwk, &mbl_eggman0_set_tbl);
}


static void eggmbl02_wait0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    p_actwk->r_no = 4;
    SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &bsexp01_set_tbl);
    if (p_new_actwk != 0) {
      p_new_actwk->u.obj.userflag = 4;
    }
  }
}


static void eggmbl02_die0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 0) {
    ko_offset1(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    p_actwk->patno = 10;
  }
}


static void eggmbl02_die1(SKC_sprite_status* p_actwk) {
  short yposi = (g_ram.scra_v_posit >> 16) + 64;
  if ((unsigned short)yposi < (unsigned short)fp16_get_integer(p_actwk->yposi)) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 1);
  }
  else {
    p_actwk->r_no = 8;
    set_eggmbl_away(p_actwk);
  }
}


static void set_eggmbl_away(SKC_sprite_status* p_actwk) {
  p_actwk->actflg.hflip = 1;
  p_actwk->xspeed = 0x300;
  p_actwk->yspeed = 0;
  p_actwk->u.obj.timer = 256;
  set_act00(p_actwk, &embl_jet_set_tbl);
}


static void eggmbl02_die2(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->u.obj.actflg0.end = 1;
    g_ram.bossstart = 0;
    set_emy_fout1(p_actwk);
  }
}


void eggmbl03(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &eggmbl02_init,
    &eggmbl02_wait0,
    &eggmbl02_die0,
    &eggmbl02_die1,
    &eggmbl02_die2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  actionsub(p_actwk);
}


void eggmbl04(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[6] = {
    &eggmbl04_init,
    &eggmbl04_wait0,
    &eggmbl04_die0,
    &eggmbl04_die1,
    &eggmbl04_die2,
    &eggmbl02_die2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
  actionsub(p_actwk);
}


static void eggmbl04_init(SKC_sprite_status* p_actwk) {
  enemy_init0(p_actwk, &eggmbl_init_tbl);
  p_actwk->patno = p_actwk->u.obj.userflag;
  set_act00(p_actwk, &mbl_eggman2_set_tbl);
}


static void eggmbl04_wait0(SKC_sprite_status* p_actwk) {
  ko_offset0(p_actwk);
  chk_oya_pri(p_actwk);
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.cddat.die == 1) {
    p_actwk->r_no = 4;
    SKC_sprite_status* p_new_actwk = set_act00(p_actwk, &bsexp01_set_tbl);
    if (p_new_actwk != 0) {
      p_new_actwk->u.obj.userflag = 4;
    }
  }
}


static void eggmbl04_die0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 0) {
    chk_oya_pri(p_actwk);
    ko_offset0(p_actwk);
  }
  else {
    p_actwk->r_no = 6;
    p_actwk->patno = 0;
    p_actwk->xspeed = 0;
    p_actwk->yspeed = -0x200;
    p_actwk->u.obj.timer = 47;
    p_actwk->u.obj.callback_ptr = &eggmbl04_die2_init;
  }
}


static void eggmbl04_die1(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  dec_timer(p_actwk);
};


static void eggmbl04_die2_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_no = 8;
  p_actwk->actflg.hflip = 1;
}


static void eggmbl04_die2(SKC_sprite_status* p_actwk) {
  short yposi = (g_ram.scra_v_posit >> 16) + 192;
  if ((unsigned short)yposi < (unsigned short)fp16_get_integer(p_actwk->yposi)) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 1);
  }
  else {
    p_actwk->r_no = 10;
    set_eggmbl_away(p_actwk);
  }
}


static void embl_jet(SKC_sprite_status* p_actwk) {
  enemy_init2(p_actwk, &embl_jet_init_tbl);
  p_actwk->r_ptr = &embl_jet_wait0;
}


static void embl_jet_wait0(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actflg0.ko_die == 0) {
    ko_offset1(p_actwk);
    if (!(g_ram.systemtimer & 1) && p_parentwk->xspeed != 0) {
      actionsub(p_actwk);
    }
  }
  else {
    frameout(p_actwk);
  }
}


void resultembl(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &resultembl_wait0;
  p_actwk->patbase = eggmbl_pt;
  memset(&p_actwk->sproffset, 0, sizeof(p_actwk->sproffset));
  p_actwk->sproffset.gfx = 0x26F;
  p_actwk->sproffset.pl = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 32;
  p_actwk->sprvs = 32;
  p_actwk->patno = 10;
  fp16_set_integer(&p_actwk->xposi, 0x188);
  fp16_set_integer(&p_actwk->yposi, 0xC0);
  bs00m0_puka_init(p_actwk);
  set_act00(p_actwk, &resmblegg_set_tbl);
}


static void resultembl_wait0(SKC_sprite_status* p_actwk) {
  puka_puka(p_actwk);
  speedset2(p_actwk);
  actionsub(p_actwk);
}


static void resmblegg(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &resmblegg_wait0;
  p_actwk->sprpri = PRI_5;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 8;
}


static void resmblegg_wait0(SKC_sprite_status* p_actwk) {
  ko_offset1(p_actwk);
  pt_chg0(p_actwk, mbl_meggman_pg00);
  actionsub(p_actwk);
}


static SKC_enemy_init0_data mbl_eggman0_init_tbl = {
  eggmbl_pt,
  { 0x52E, 0, 0, 0, 0 },
  PRI_5,
  16,
  8,
  0,
  0
};


static SKC_enemy_init0_data mbl_eggman2_init_tbl = {
  egg2_pt,
  { 0x430, 0, 0, 0, 0 },
  PRI_5,
  16,
  8,
  0,
  0
};


static SKC_enemy_init0_data eggmbl_init_tbl = {
  eggmbl_pt,
  { 0x52E, 0, 0, 0, 0 },
  PRI_5,
  28,
  32,
  8,
  0
};


static SKC_enemy_init2_data embl_jet_init_tbl = {
  PRI_5,
  8,
  5,
  6,
  0
};


static SKC_enemy_init0_data mbl_msonic_init_tbl = {
  msmbl_pt,
  { 0x52E, 0, 0, 1, 0 },
  PRI_5,
  20,
  16,
  0,
  0
};


SKC_set_act00_data mbl_eggman0_set_tbl = {
  0,
  {
    { &mbl_eggman0, 0, -28 }
  }
};


SKC_set_act00_data mbl_eggman1_set_tbl = {
  0,
  {
    { &mbl_eggman1, 0, -28 }
  }
};


static SKC_set_act00_data mbl_eggman2_set_tbl = {
  0,
  {
    { &mbl_eggman2, 0, -28 }
  }
};


SKC_set_act00_data mbl_eggman3_set_tbl = {
  0,
  {
    { &mbl_eggman3, 0, -28 }
  }
};


SKC_set_act00_data mbl_eggman4_set_tbl = {
  0,
  {
    { &mbl_eggman4, 0, -28 }
  }
};


SKC_set_act00_data eggmbl00_set_tbl = {
  0,
  {
    { &eggmbl00, 0, -20 }
  }
};


SKC_set_act00_data eggmbl01_set_tbl = {
  0,
  {
    { &eggmbl01, 0, 0 }
  }
};


SKC_set_act00_data eggmbl02_set_tbl = {
  0,
  {
    { &eggmbl02, -6, 4 }
  }
};


SKC_set_act00_data eggmbl03_set_tbl = {
  0,
  {
    { &eggmbl03, 0, -8 }
  }
};


SKC_set_act00_data eggmbl04_set_tbl = {
  0,
  {
    { &eggmbl04, 0, 4 }
  }
};


SKC_set_act00_data embl_jet_set_tbl = {
  0,
  {
    { &embl_jet, 30, 0 }
  }
};


SKC_set_act00_data msmbl_set_tbl = {
  0,
  {
    { &mbl_msonic, 0, -32 }
  }
};


static SKC_set_act00_data resmblegg_set_tbl = {
  0,
  {
    { &resmblegg, 0, -28 }
  }
};


static signed char mbl_eggman0_pg00[4] = { 5, 0, 1, -4 };


static signed char mbl_meggman_pg00[6] = { 15, 0, 1, -4, -121, -37 };


static SKC_sprite_pattern* megmbl_pt[4] = {
  &megmbl_pt00,
  &megmbl_pt01,
  &megmbl_pt02,
  &megmbl_pt03
};


static SKC_sprite_pattern megmbl_pt00 = {
  1,
  {
    { -8, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern megmbl_pt01 = {
  1,
  {
    { -8, 13, 0x0008, -16 }
  }
};
static SKC_sprite_pattern megmbl_pt02 = {
  1,
  {
    { -8, 13, 0x0010, -16 }
  }
};
static SKC_sprite_pattern megmbl_pt03 = {
  1,
  {
    { -8, 13, 0x0018, -16 }
  }
};


static SKC_sprite_pattern* msmbl_pt[1] = {
  &msmbl_pt00
};


static SKC_sprite_pattern msmbl_pt00 = {
  2,
  {
    { -12, 14, 0x0000, -20 },
    {  -4,  1, 0x000C,  12 }
  }
};


SKC_sprite_pattern* eggmbl_pt[13] = {
  &eggmbl_pt00,
  &eggmbl_pt01,
  &eggmbl_pt02,
  &eggmbl_pt03,
  &eggmbl_pt04,
  &eggmbl_pt05,
  &eggmbl_pt06,
  &eggmbl_pt07,
  &eggmbl_pt08,
  &eggmbl_pt09,
  &eggmbl_pt10,
  &eggmbl_pt11,
  &eggmbl_pt12
};


static SKC_sprite_pattern eggmbl_pt00 = {
  1,
  {
    { -8, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern eggmbl_pt01 = {
  1,
  {
    { -8, 13, 0x0008, -16 }
  }
};
static SKC_sprite_pattern eggmbl_pt02 = {
  2,
  {
    { -8, 13, 0x0010, -20 },
    { -8,  1, 0x0018,  12 }
  }
};
static SKC_sprite_pattern eggmbl_pt03 = {
  1,
  {
    { -8, 13, 0x001A, -16 }
  }
};
static SKC_sprite_pattern eggmbl_pt04 = {
  1,
  {
    { -8, 5, 0x004E, 0 }
  }
};
static SKC_sprite_pattern eggmbl_pt05 = {
  12,
  {
    { -20, 12, 0x0022, -28 },
    { -20,  8, 0x0026,   4 },
    { -12, 14, 0x0029, -28 },
    { -12, 10, 0x0035,   4 },
    {  12,  8, 0x003E, -20 },
    {  12,  4, 0x0041,   4 },
    { -44,  5, 0x0043, -16 },
    { -36,  1, 0x0047, -24 },
    { -44,  5, 0x0843,   0 },
    { -36,  1, 0x0847,  16 },
    { -38,  0, 0x004B,  -2 },
    { -28,  4, 0x0049, -20 }
  }
};
static SKC_sprite_pattern eggmbl_pt06 = {
  1,
  {
    { -4, 4, 0x004C, -8 }
  }
};
static SKC_sprite_pattern eggmbl_pt07 = {
  4,
  {
    { -12, 5, 0x0043, -16 },
    {  -4, 1, 0x0047, -24 },
    { -12, 5, 0x0843,   0 },
    {  -4, 1, 0x0847,  16 }
  }
};
static SKC_sprite_pattern eggmbl_pt08 = {
  8,
  {
    { -20, 12, 0x0022, -28 },
    { -20,  8, 0x0026,   4 },
    { -44,  5, 0x0043, -16 },
    { -36,  1, 0x0047, -24 },
    { -44,  5, 0x0843,   0 },
    { -36,  1, 0x0847,  16 },
    { -38,  0, 0x004B,  -2 },
    { -28,  4, 0x0049, -20 }
  }
};
static SKC_sprite_pattern eggmbl_pt09 = {
  3,
  {
    { -20, 12, 0x0022, -28 },
    { -20, 8, 0x0026, 4 },
    { -28, 4, 0x0049, -20 }
  }
};
static SKC_sprite_pattern eggmbl_pt10 = {
  7,
  {
    { -20, 12, 0x0022, -28 },
    { -20,  8, 0x0026,   4 },
    { -12, 14, 0x0029, -28 },
    { -12, 10, 0x0035,   4 },
    {  12,  8, 0x003E, -20 },
    {  12,  4, 0x0041,   4 },
    { -28,  4, 0x0049, -20 }
  }
};
static SKC_sprite_pattern eggmbl_pt11 = {
  6,
  {
    { -20, 12, 0x0022, -28 },
    { -20,  8, 0x0026,   4 },
    { -44,  5, 0x0043, -16 },
    { -36,  1, 0x0047, -24 },
    { -44,  5, 0x0843,   0 },
    { -36,  1, 0x0847,  16 }
  }
};
static SKC_sprite_pattern eggmbl_pt12 = {
  6,
  {
    { -44, 5, 0x0043, -16 },
    { -36, 1, 0x0047, -24 },
    { -44, 5, 0x0843,   0 },
    { -36, 1, 0x0847,  16 },
    { -38, 0, 0x004B,  -2 },
    { -28, 4, 0x0049, -20 }
  }
};


SKC_sprite_pattern* eggrun_pt[7] = {
  &eggrun_pt00,
  &eggrun_pt01,
  &eggrun_pt02,
  &eggrun_pt03,
  &eggrun_pt04,
  &eggrun_pt05,
  &eggrun_pt06
};


static SKC_sprite_pattern eggrun_pt00 = {
  5,
  {
    { -24, 14, 0x0000, -16 },
    { -16,  4, 0x000C,  16 },
    {   8,  5, 0x000E, -32 },
    {   0,  5, 0x0012, -16 },
    {   0, 10, 0x0016,   0 }
  }
};
static SKC_sprite_pattern eggrun_pt01 = {
  4,
  {
    { -24, 14, 0x0000, -16 },
    { -16,  4, 0x000C,  16 },
    {   0, 13, 0x001F, -16 },
    {  16,  5, 0x0027,  -8 }
  }
};
static SKC_sprite_pattern eggrun_pt02 = {
  5,
  {
    { -24, 14, 0x0000, -16 },
    { -16,  4, 0x000C,  16 },
    {  16,  5, 0x002B, -24 },
    {   0,  5, 0x002F, -16 },
    {   0,  7, 0x0033,   0 }
  }
};
static SKC_sprite_pattern eggrun_pt03 = {
  3,
  {
    { -24, 14, 0x0000, -16 },
    { -16,  4, 0x000C,  16 },
    {   0, 14, 0x003B, -16 }
  }
};
static SKC_sprite_pattern eggrun_pt04 = {
  5,
  {
    { -24, 14, 0x0000, -16 },
    { -16,  4, 0x000C,  16 },
    {   8,  5, 0x000E, -32 },
    {   0,  5, 0x0012, -16 },
    {   0, 10, 0x0016,   0 }
  }
};
static SKC_sprite_pattern eggrun_pt05 = {
  4,
  {
    { -24, 14, 0x0000, -16 },
    { -16,  4, 0x000C,  16 },
    {   0, 13, 0x001F, -16 },
    {  16,  5, 0x0027,  -8 }
  }
};
static SKC_sprite_pattern eggrun_pt06 = {
  5,
  {
    { -24, 14, 0x0000, -16 },
    { -16,  4, 0x000C,  16 },
    {  16,  5, 0x002B, -24 },
    {   0,  5, 0x002F, -16 },
    {   0,  7, 0x0033,   0 }
  }
};


SKC_sprite_pattern* egg2_pt[4] = {
  &egg2_pt00,
  &egg2_pt01,
  &egg2_pt02,
  &egg2_pt03
};


static SKC_sprite_pattern egg2_pt00 = {
  1,
  {
    { -8, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern egg2_pt01 = {
  1,
  {
    { -8, 13, 0x0008, -16 }
  }
};
static SKC_sprite_pattern egg2_pt02 = {
  1,
  {
    { -8, 13, 0x0010, -16 }
  }
};
static SKC_sprite_pattern egg2_pt03 = {
  1,
  {
    { -8, 13, 0x0018, -16 }
  }
};


SKC_sprite_pattern* egg3_pt[4] = {
  &egg3_pt00,
  &egg3_pt01,
  &egg3_pt02,
  &egg3_pt03
};


static SKC_sprite_pattern egg3_pt00 = {
  4,
  {
    { -28, 13, 0x0000, -16 },
    { -12, 14, 0x0008, -16 },
    {  12,  4, 0x0014,  -8 },
    {  20, 12, 0x0016, -16 }
  }
};
static SKC_sprite_pattern egg3_pt01 = {
  4,
  {
    { -28,  8, 0x001A,  -8 },
    { -20, 15, 0x001D, -16 },
    {  12,  4, 0x002D,  -8 },
    {  20, 12, 0x002F, -16 }
  }
};
static SKC_sprite_pattern egg3_pt02 = {
  4,
  {
    { -28, 13, 0x0033, -16 },
    { -12, 14, 0x0008, -16 },
    {  12,  4, 0x0014,  -8 },
    {  20, 12, 0x0016, -16 }
  }
};
static SKC_sprite_pattern egg3_pt03 = {
  4,
  {
    { -28, 13, 0x003B, -16 },
    { -12, 14, 0x0008, -16 },
    {  12,  4, 0x0014,  -8 },
    {  20, 12, 0x0016, -16 }
  }
};
