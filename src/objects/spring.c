#include "spring.h"
#include <stdbool.h>
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/direction.h"
#include "../utils/fp16.h"
#include "../utils/fp8.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../hitchk.h"
#include "../sound.h"
static void sjumpinit(SKC_sprite_status* p_actwk);
static void sjumpswinit(SKC_sprite_status* p_actwk);
static void sdash_init(SKC_sprite_status* p_actwk);
static void sjumpr_init(SKC_sprite_status* p_actwk);
static void sjumpr_initg(SKC_sprite_status* p_actwk);
static void sjump45_init(SKC_sprite_status* p_actwk);
static void sjump45r_init(SKC_sprite_status* p_actwk);
static void sjump_init(SKC_sprite_status* p_actwk);
static void sjump_initg(SKC_sprite_status* p_actwk);
static void sjumpinit_end(SKC_sprite_status* p_actwk);
static void sjumpmove(SKC_sprite_status* p_actwk);
static void vssjumpmove(SKC_sprite_status* p_actwk);
static void sdashmove(SKC_sprite_status* p_actwk);
static void vssdashmove(SKC_sprite_status* p_actwk);
static void vssdashsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void sdashsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void sdashsub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void sdashcolichk(SKC_sprite_status* p_actwk);
static void sjumprmove(SKC_sprite_status* p_actwk);
static void vssjumprmove(SKC_sprite_status* p_actwk);
static void sjumprsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void sjumprsub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void sjump45move(SKC_sprite_status* p_actwk);
static void sjump45move__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static void sjump45rmove(SKC_sprite_status* p_actwk);
static void sjump45rmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);
static signed char sjump45tbl[28];
static signed char sjump45tbl2[28];
static signed char sjumpchg0[3];
static signed char sjumpchg1[12];
static signed char sjumpchg2[3];
static signed char sjumpchg3[12];
static signed char sjumpchg4[3];
static signed char sjumpchg5[15];
static SKC_sprite_pattern* banepat2[11];
static SKC_sprite_pattern banevsp00;
static SKC_sprite_pattern banevsp01;
static SKC_sprite_pattern banevsp02;
static SKC_sprite_pattern banevsp00c;
static SKC_sprite_pattern banevsp01c;
static SKC_sprite_pattern banevsp02c;
static SKC_sprite_pattern banehsp00;
static SKC_sprite_pattern banehsp01;
static SKC_sprite_pattern banehsp02;
static SKC_sprite_pattern banehsp00c;
static SKC_sprite_pattern banehsp01c;
static SKC_sprite_pattern banehsp02c;
static SKC_sprite_pattern banevsp03;
static SKC_sprite_pattern banevsp03c;
static SKC_sprite_pattern bane45sp00;
static SKC_sprite_pattern bane45sp01;
static SKC_sprite_pattern bane45sp02;
static SKC_sprite_pattern bane45sp03;
static SKC_sprite_pattern bane45sp00c;
static SKC_sprite_pattern bane45sp01c;
static SKC_sprite_pattern bane45sp02c;
static SKC_sprite_pattern bane45sp03c;
static SKC_sprite_pattern* vsbanepat2[7];
static SKC_sprite_pattern vsbanevsp00;
static SKC_sprite_pattern vsbanevsp01;
static SKC_sprite_pattern vsbanevsp02;
static SKC_sprite_pattern vsbanehsp00;
static SKC_sprite_pattern vsbanehsp01;
static SKC_sprite_pattern vsbanehsp02;
static SKC_sprite_pattern vsbanevsp03;
static SKC_sprite_pattern vsbanevsp00c;
static SKC_sprite_pattern vsbanevsp01c;
static SKC_sprite_pattern vsbanevsp02c;
static SKC_sprite_pattern vsbanehsp00c;
static SKC_sprite_pattern vsbanehsp01c;
static SKC_sprite_pattern vsbanehsp02c;
static SKC_sprite_pattern vsbanevsp03c;
static void sjumpmvkind(SKC_sprite_status* p_actwk);
static void sjumpmv_ymove(SKC_sprite_status* p_actwk);
static void sjumpmv_ymove1(SKC_sprite_status* p_actwk);
static void sjumpmv_xmove(SKC_sprite_status* p_actwk);
static void sjumpmv_xmove1(SKC_sprite_status* p_actwk);
static void sjumpmv_ymove2(SKC_sprite_status* p_actwk);
static void sjumpmv_ymove3(SKC_sprite_status* p_actwk);
static void sjumpmv_xymove(SKC_sprite_status* p_actwk);
static void sjumpmv_xymove1(SKC_sprite_status* p_actwk);
static void sjumpmv_xymove2(SKC_sprite_status* p_actwk);
static void sjumpmv_xymove3(SKC_sprite_status* p_actwk);
static void sjumpmv_sub(SKC_sprite_status* p_actwk);
static void sjumpswkind(SKC_sprite_status* p_actwk);
static void sjumpsw_ymove(SKC_sprite_status* p_actwk);
static void sjumpsw_ymove1(SKC_sprite_status* p_actwk);
static void sjumpsw_xmove(SKC_sprite_status* p_actwk);
static void sjumpsw_xmove1(SKC_sprite_status* p_actwk);
static void sjumpsw_ymove2(SKC_sprite_status* p_actwk);
static void sjumpsw_ymove3(SKC_sprite_status* p_actwk);
static void sjumpsw_ymove4(SKC_sprite_status* p_actwk);
static void sjumpsw_ymove5(SKC_sprite_status* p_actwk);
static void sjumpsw_xmove2(SKC_sprite_status* p_actwk);
static void sjumpsw_xmove3(SKC_sprite_status* p_actwk);
static void sjumpsw_xmove4(SKC_sprite_status* p_actwk);
static void sjumpsw_xmove5(SKC_sprite_status* p_actwk);
static void sjumpsw_sub(SKC_sprite_status* p_actwk);
static void sjumpsw_sub2(SKC_sprite_status* p_actwk);
static void sjumpsw_sub3(SKC_sprite_status* p_actwk);
static void sjumpswmove(SKC_sprite_status* p_actwk);
static void sjumpswmove2(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern* banedaipat[4];
static SKC_sprite_pattern* banedaipat2[4];
static SKC_sprite_pattern banedaisp00;
static SKC_sprite_pattern banedaisp01;
static SKC_sprite_pattern banedaisp02;
static SKC_sprite_pattern banedaisp03;

extern sonic3_ram g_ram;


void sjump(SKC_sprite_status* p_actwk) {
  sjumpinit(p_actwk);
}


static void sjumpinit(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler sjumpinit_tbl[5] = {
    &sjump_init,
    &sdash_init,
    &sjumpr_init,
    &sjump45_init,
    &sjump45r_init
  };

  p_actwk->patbase = banepat;
  p_actwk->sproffset = 0x04A4;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 16;
  p_actwk->sprpri = PRI_4;
  p_actwk->u.obj.actfree.spring.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.actfree.spring.yposi_init = fp16_get_integer(p_actwk->yposi);
  sjumpinit_tbl[p_actwk->u.obj.userflag >> 4 & 7](p_actwk);
}


static void sjumpswinit(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler sjumpswinit_tbl[8] = {
    &sjump_init,
    &sdash_init,
    &sjumpr_init,
    &sdash_init,
    &sjump_init,
    &sjumpr_init,
    &sjump_init,
    &sjumpr_init
  };

  p_actwk->patbase = banepat;
  p_actwk->sproffset = 0x04A4;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 16;
  p_actwk->sprpri = PRI_4;
  p_actwk->u.obj.actfree.spring.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.actfree.spring.yposi_init = fp16_get_integer(p_actwk->yposi);
  sjumpswinit_tbl[p_actwk->u.obj.userflag >> 4 & 7](p_actwk);
  p_actwk->u.obj.actfree.spring.recoil = -0x800;
}


static void sdash_init(SKC_sprite_status* p_actwk) {
  p_actwk->mstno = 2;
  p_actwk->patno = 3;
  p_actwk->sproffset = 0x04B4;
  p_actwk->sprhs = 8;
  p_actwk->r_ptr = &sdashmove;
  if (g_ram.vs_flag != 0) {
    p_actwk->patbase = vsbanepat;
    p_actwk->sproffset = 0x03AD;
    p_actwk->r_ptr = &vssdashmove;
  }
  sjumpinit_end(p_actwk);
}


static void sjumpr_init(SKC_sprite_status* p_actwk) {
  if (g_ram.reverse_gravity_flag == 0) {
    p_actwk->u.obj.cddat.down = 1;
  }
  sjumpr_initg(p_actwk);
}


static void sjumpr_initg(SKC_sprite_status* p_actwk) {
  p_actwk->patno = 6;
  p_actwk->r_ptr = &sjumprmove;
  if (g_ram.vs_flag != 0) {
    p_actwk->r_ptr = &vssjumprmove;
    p_actwk->patbase = vsbanepat;
    p_actwk->sproffset = 0x0391;
  }
  sjumpinit_end(p_actwk);
}


static void sjump45_init(SKC_sprite_status* p_actwk) {
  p_actwk->mstno = 4;
  p_actwk->patno = 7;
  p_actwk->sproffset = 0x043A;
  if (get_zone(g_ram.stageno) == MARBLE_GARDEN || get_zone(g_ram.stageno) == MUSHROOM_HILL) {
    p_actwk->sproffset = 0x0478;
  }
  p_actwk->r_ptr = &sjump45move;
  sjumpinit_end(p_actwk);
}


static void sjump45r_init(SKC_sprite_status* p_actwk) {
  p_actwk->mstno = 4;
  p_actwk->patno = 10;
  p_actwk->sproffset = 0x043A;
  if (get_zone(g_ram.stageno) == MARBLE_GARDEN || get_zone(g_ram.stageno) == MUSHROOM_HILL) {
    p_actwk->sproffset = 0x0478;
  }
  p_actwk->u.obj.cddat.down = 1;
  p_actwk->r_ptr = &sjump45rmove;
  sjumpinit_end(p_actwk);
}


static void sjump_init(SKC_sprite_status* p_actwk) {
  if (g_ram.reverse_gravity_flag == 0) {
    sjumpr_initg(p_actwk);
  }
  else {
    sjump_initg(p_actwk);
  }
}


static void sjump_initg(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmove;
  if (g_ram.vs_flag != 0) {
    p_actwk->r_ptr = &vssjumpmove;
    p_actwk->patbase = vsbanepat;
    p_actwk->sproffset = 0x391;
    if (get_zone(g_ram.stageno) == ENDLESS_MINE) {
      p_actwk->sproffset |= 0x8000;
    }
  }
  sjumpinit_end(p_actwk);
}


static void sjumpinit_end(SKC_sprite_status* p_actwk) {
  short sjumptbl[2] = {
    -0x1000,
    -0xA00
  };

  p_actwk->u.obj.actfree.spring.recoil = sjumptbl[(p_actwk->u.obj.userflag & 2) / 2];
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 1)) {
    p_actwk->patbase = g_ram.vs_flag == 0 ? banepat2 : vsbanepat2;
  }
}


static void sjumpmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 8, 16, fp16_get_integer(p_actwk->xposi) };
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (p_actwk->u.obj.cddat.plride == 1) {
    sjumpsub(p_actwk, &g_ram.actwk[0]);
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    sjumpsub(p_actwk, &g_ram.actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk(p_actwk);
}


static void vssjumpmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 19, 8, 16, fp16_get_integer(p_actwk->xposi) };
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (p_actwk->u.obj.cddat.plride == 1) {
    sjumpsub(p_actwk, &g_ram.actwk[0]);
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    sjumpsub(p_actwk, &g_ram.actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  actionsub(p_actwk);
}


void sjumpsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->mstno = 1;
  short yposi = fp16_get_integer(p_playerwk->yposi) + 8;
  if (g_ram.reverse_gravity_flag != 0) {
    yposi -= 16;
  }
  fp16_set_integer(&p_playerwk->yposi, yposi);
  p_playerwk->yspeed = p_actwk->u.obj.actfree.spring.recoil;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.jump_flag = 0;
  p_playerwk->u.play.spindash_flag = 0;
  p_playerwk->mstno = 16;
  p_playerwk->r_no = 2;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_playerwk->xspeed = 0;
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 0)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc.b.b1 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->u.play.flip_rev_cnt = BIT_IS_SET(p_actwk->u.obj.userflag, 1) ? 0 : 1;
    p_playerwk->u.play.flip_rev_frame_cnt = 4;
    if (p_playerwk->u.play.cddat.left == 1) {
      p_playerwk->direc.b.b1 = direction_hmirror(p_playerwk->direc.b.b1);
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 2) && !BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xC;
    p_playerwk->u.play.lrb_solid_bit = 0xD;
  }
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 2) && BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xE;
    p_playerwk->u.play.lrb_solid_bit = 0xF;
  }
  soundset(177);
}


static void sdashmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 19, 14, 15, fp16_get_integer(p_actwk->xposi) };
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  bool plleft = fp16_get_integer(p_actwk->xposi) >= fp16_get_integer(g_ram.actwk[0].xposi);
  if (result.plcoli[0] == HITCHK_COLI_SIDE && p_actwk->u.obj.cddat.right == plleft) {
    sdashsub(p_actwk, &g_ram.actwk[0]);
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  bool pl2left = fp16_get_integer(p_actwk->xposi) >= fp16_get_integer(g_ram.actwk[1].xposi);
  if (result.plcoli[1] == HITCHK_COLI_SIDE && p_actwk->u.obj.cddat.right == pl2left) {
    sdashsub(p_actwk, &g_ram.actwk[1]);
  }
  sdashcolichk(p_actwk);
  patchg(p_actwk, sjumpchg);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.spring.xposi_init);
}


static void vssdashmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 15, 12, 13, fp16_get_integer(p_actwk->xposi) };
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (result.plcoli[0] == HITCHK_COLI_SIDE) {
    bool right = p_actwk->u.obj.cddat.right;
    if (fp16_get_integer(p_actwk->xposi) >= fp16_get_integer(g_ram.actwk[0].xposi)) {
      right = !right;
    }
    if (!right) {
      vssdashsub(p_actwk, &g_ram.actwk[0]);
    }
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  if (result.plcoli[1] == HITCHK_COLI_SIDE) {
    bool right = p_actwk->u.obj.cddat.right;
    if (fp16_get_integer(p_actwk->xposi) >= fp16_get_integer(g_ram.actwk[1].xposi)) {
      right = !right;
    }
    if (!right) {
      vssdashsub(p_actwk, &g_ram.actwk[1]);
    }
  }
  patchg(p_actwk, sjumpchg);
  actionsub(p_actwk);
}


static void vssdashsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->mstno = 3;
  p_playerwk->xspeed = p_actwk->u.obj.actfree.spring.recoil;
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 4);
  p_playerwk->u.play.cddat.left = 1;
  if (p_actwk->u.obj.cddat.right == 1) {
    p_playerwk->u.play.cddat.left = 0;
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 8);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  sdashsub2(p_actwk, p_playerwk);
}


static void sdashsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->mstno = 3;
  p_playerwk->xspeed = p_actwk->u.obj.actfree.spring.recoil;
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 8);
  p_playerwk->u.play.cddat.left = 1;
  if (p_actwk->u.obj.cddat.right == 1) {
    p_playerwk->u.play.cddat.left = 0;
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 16);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  sdashsub2(p_actwk, p_playerwk);
}


static void sdashsub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_playerwk->u.play.hlock_timer = 15;
  p_playerwk->mspeed = p_playerwk->xspeed;
  if (p_playerwk->u.play.cddat.ball == 0) {
    p_playerwk->mstno = 0;
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_playerwk->yspeed = 0;
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 0)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc.b.b1 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->u.play.flip_rev_cnt = !BIT_IS_SET(p_actwk->u.obj.userflag, 1) ? 1 : 3;
    p_playerwk->u.play.flip_rev_frame_cnt = 8;
    if (p_playerwk->u.play.cddat.left == 1) {
      p_playerwk->direc.b.b1 = direction_hmirror(p_playerwk->direc.b.b1);
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 2) && !BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xC;
    p_playerwk->u.play.lrb_solid_bit = 0xD;
  }
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 2) && BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xE;
    p_playerwk->u.play.lrb_solid_bit = 0xF;
  }
  p_actwk->u.obj.cddat.plpush = 0;
  p_actwk->u.obj.cddat.pl2push = 0;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.talent_status = 0;
  soundset(177);
}


static void sdashcolichk(SKC_sprite_status* p_actwk) {
  if (p_actwk->mstno == 3) return;

  short xposi_left = fp16_get_integer(p_actwk->xposi) - (p_actwk->u.obj.cddat.right == 0 ? 0 : 40);
  short xposi_right = fp16_get_integer(p_actwk->xposi) + (p_actwk->u.obj.cddat.right == 0 ? 40 : 0);
  short yposi_top = fp16_get_integer(p_actwk->yposi) - 24;
  short yposi_bottom = fp16_get_integer(p_actwk->yposi) + 24;
  if (g_ram.actwk[0].u.play.cddat.jump == 0) {
    short mspeed = g_ram.actwk[0].mspeed;
    if (p_actwk->u.obj.cddat.right == 1) {
      mspeed = -mspeed;
    }
    if (mspeed >= 0
        && (unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) >= (unsigned short)xposi_left
        && (unsigned short)fp16_get_integer(g_ram.actwk[0].xposi) < (unsigned short)xposi_right
        && (unsigned short)fp16_get_integer(g_ram.actwk[0].yposi) >= (unsigned short)yposi_top
        && (unsigned short)fp16_get_integer(g_ram.actwk[0].yposi) < (unsigned short)yposi_bottom) {
      sdashsub(p_actwk, &g_ram.actwk[0]);
    }
  }
  if (g_ram.actwk[1].u.play.cddat.jump == 0) {
    short mspeed = g_ram.actwk[1].mspeed;
    if (p_actwk->u.obj.cddat.right == 1) {
      mspeed = -mspeed;
    }
    if (mspeed >= 0
        && (unsigned short)fp16_get_integer(g_ram.actwk[1].xposi) >= (unsigned short)xposi_left
        && (unsigned short)fp16_get_integer(g_ram.actwk[1].xposi) < (unsigned short)xposi_right
        && (unsigned short)fp16_get_integer(g_ram.actwk[1].yposi) >= (unsigned short)yposi_top
        && (unsigned short)fp16_get_integer(g_ram.actwk[1].yposi) < (unsigned short)yposi_bottom) {
      sdashsub(p_actwk, &g_ram.actwk[1]);
    }
  }
}


static void sjumprmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 8, 9, fp16_get_integer(p_actwk->xposi) };
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
    sjumprsub(p_actwk, &g_ram.actwk[0]);
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
    sjumprsub(p_actwk, &g_ram.actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk(p_actwk);
}


static void vssjumprmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 19, 8, 9, fp16_get_integer(p_actwk->xposi) };
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
    fp16_set_integer(&g_ram.actwk[0].yposi, fp16_get_integer(g_ram.actwk[0].yposi) - 4);
    sjumprsub2(p_actwk, &g_ram.actwk[0]);
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
    fp16_set_integer(&g_ram.actwk[1].yposi, fp16_get_integer(g_ram.actwk[1].yposi) - 4);
    sjumprsub2(p_actwk, &g_ram.actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  actionsub(p_actwk);
}


static void sjumprsub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 8);
  if (g_ram.reverse_gravity_flag != 0) {
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 16);
  }
  sjumprsub2(p_actwk, p_playerwk);
}


static void sjumprsub2(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->mstno = 1;
  p_playerwk->yspeed = p_actwk->u.obj.actfree.spring.recoil;
  p_playerwk->yspeed = -p_playerwk->yspeed;
  if (p_playerwk->yspeed == 0x1000) {
    p_playerwk->yspeed = 0xD00;
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    p_playerwk->xspeed = 0;
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 0)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc.b.b1 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->u.play.flip_rev_cnt = BIT_IS_SET(p_actwk->u.obj.userflag, 1) ? 0 : 1;
    p_playerwk->u.play.flip_rev_frame_cnt = 4;
    if (p_playerwk->u.play.cddat.left == 1) {
      p_playerwk->direc.b.b1 = direction_hmirror(p_playerwk->direc.b.b1);
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 2) && !BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xC;
    p_playerwk->u.play.lrb_solid_bit = 0xD;
  }
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 2) && BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xE;
    p_playerwk->u.play.lrb_solid_bit = 0xF;
  }
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.jump_flag = 0;
  p_playerwk->r_no = 2;
  p_playerwk->u.play.talent_status = 0;
  soundset(177);
}


static void sjump45move(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 16, 0, fp16_get_integer(p_actwk->xposi) };
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  plhitchk_slope(p_actwk, &g_ram.actwk[0], data, sjump45tbl, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (p_actwk->u.obj.cddat.plride == 1) {
    sjump45move__sub(p_actwk, &g_ram.actwk[0]);
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  plhitchk_slope(p_actwk, &g_ram.actwk[1], data, sjump45tbl, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  if (p_actwk->u.obj.cddat.pl2ride == 1) {
    sjump45move__sub(p_actwk, &g_ram.actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.spring.xposi_init);
}


static void sjump45move__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  if (p_actwk->u.obj.cddat.right) {
    unsigned short xposi = (unsigned short)(fp16_get_integer(p_actwk->xposi) - 4);
    if (xposi >= (unsigned short)fp16_get_integer(p_playerwk->xposi)) return;
  }
  else {
    unsigned short xposi = (unsigned short)(fp16_get_integer(p_actwk->xposi) + 4);
    if (xposi < (unsigned short)fp16_get_integer(p_playerwk->xposi)) return;
  }
  p_actwk->mstno = 5;
  p_playerwk->yspeed = p_actwk->u.obj.actfree.spring.recoil;
  p_playerwk->xspeed = p_actwk->u.obj.actfree.spring.recoil;
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 6);
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 6);
  p_playerwk->u.play.cddat.left = 1;
  if (p_actwk->u.obj.cddat.right == 0) {
    p_playerwk->u.play.cddat.left = 0;
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 12);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.jump_flag = 0;
  p_playerwk->mstno = 16;
  p_playerwk->r_no = 2;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 0)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc.b.b1 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->u.play.flip_rev_cnt = BIT_IS_SET(p_actwk->u.obj.userflag, 1) ? 1 : 3;
    p_playerwk->u.play.flip_rev_frame_cnt = 8;
    if (p_playerwk->u.play.cddat.left == 1) {
      p_playerwk->direc.b.b1 = direction_hmirror(p_playerwk->direc.b.b1);
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 2) && !BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xC;
    p_playerwk->u.play.lrb_solid_bit = 0xD;
  }
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 2) && BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xE;
    p_playerwk->u.play.lrb_solid_bit = 0xF;
  }
  soundset(177);
}


static void sjump45rmove(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { 27, 16, 0, fp16_get_integer(p_actwk->xposi) };
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_slope(p_actwk, &g_ram.actwk[0], data, sjump45tbl2, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (result.plcoli[0] == HITCHK_COLI_BOTTOM) {
    sjump45rmove__sub(p_actwk, &g_ram.actwk[0]);
  }
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_slope(p_actwk, &g_ram.actwk[1], data, sjump45tbl2, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  if (result.plcoli[1] == HITCHK_COLI_BOTTOM) {
    sjump45rmove__sub(p_actwk, &g_ram.actwk[1]);
  }
  patchg(p_actwk, sjumpchg);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.spring.xposi_init);
}


static void sjump45rmove__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk) {
  p_actwk->mstno = 5;
  p_playerwk->yspeed = -p_actwk->u.obj.actfree.spring.recoil;
  p_playerwk->xspeed = p_actwk->u.obj.actfree.spring.recoil;
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 6);
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) + 6);
  p_playerwk->u.play.cddat.left = 1;
  if (p_actwk->u.obj.cddat.right == 0) {
    p_playerwk->u.play.cddat.left = 0;
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - 12);
    p_playerwk->xspeed = -p_playerwk->xspeed;
  }
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.jump_flag = 0;
  p_playerwk->r_no = 2;
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 0)) {
    p_playerwk->mspeed = 1;
    p_playerwk->direc.b.b1 = 1;
    p_playerwk->mstno = 0;
    p_playerwk->u.play.flip_rev_cnt = BIT_IS_SET(p_actwk->u.obj.userflag, 1) ? 1 : 3;
    p_playerwk->u.play.flip_rev_frame_cnt = 8;
    if (p_playerwk->u.play.cddat.left == 1) {
      p_playerwk->direc.b.b1 = direction_hmirror(p_playerwk->direc.b.b1);
      p_playerwk->mspeed = -p_playerwk->mspeed;
    }
  }
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 2) && !BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xC;
    p_playerwk->u.play.lrb_solid_bit = 0xD;
  }
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 2) && BIT_IS_SET(p_actwk->u.obj.userflag, 3)) {
    p_playerwk->u.play.top_solid_bit = 0xE;
    p_playerwk->u.play.lrb_solid_bit = 0xF;
  }
  soundset(177);
}


static signed char sjump45tbl[28] = {
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 14, 12, 10,  8,  6,  4,  2,  0,
  -2, -4, -4, -4, -4, -4, -4, -4
};


static signed char sjump45tbl2[28] = {
  -12, -16, -16, -16, -16, -16, -16, -16, -16, -16,
  -16, -16, -14, -12, -10,  -8,  -6,  -4,  -2,   0,
    2,   4,   4,   4,   4,   4,   4,   4
};


signed char* sjumpchg[6] = {
  sjumpchg0,
  sjumpchg1,
  sjumpchg2,
  sjumpchg3,
  sjumpchg4,
  sjumpchg5
};


static signed char sjumpchg0[3] = { 15, 0, -1 };
static signed char sjumpchg1[12] = { 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, -3, 0 };
static signed char sjumpchg2[3] = { 15, 3, -1 };
static signed char sjumpchg3[12] = { 0, 4, 3, 3, 5, 5, 5, 5, 5, 5, -3, 2 };
static signed char sjumpchg4[3] = { 15, 7, -1 };
static signed char sjumpchg5[15] = { 0, 8, 7, 7, 9, 9, 9, 9, 9, 9, -3, 4, -121, -37, -112 };


SKC_sprite_pattern* banepat[11] = {
  &banevsp00,
  &banevsp01,
  &banevsp02,
  &banehsp00,
  &banehsp01,
  &banehsp02,
  &banevsp03,
  &bane45sp00,
  &bane45sp01,
  &bane45sp02,
  &bane45sp03
};


static SKC_sprite_pattern* banepat2[11] = {
  &banevsp00c,
  &banevsp01c,
  &banevsp02c,
  &banehsp00c,
  &banehsp01c,
  &banehsp02c,
  &banevsp03c,
  &bane45sp00c,
  &bane45sp01c,
  &bane45sp02c,
  &bane45sp03c
};


static SKC_sprite_pattern banevsp00 = {
  2,
  {
    { -8, 12, 0x0000, -16 },
    {  0,  4, 0x0008,  -8 }
  }
};
static SKC_sprite_pattern banevsp01 = {
  1,
  {
    { 0, 12, 0x0000, -16 }
  }
};
static SKC_sprite_pattern banevsp02 = {
  2,
  {
    { -24, 12, 0x0000, -16 },
    { -16,  6, 0x000A,  -8 }
  }
};


static SKC_sprite_pattern banevsp00c = {
  2,
  {
    { -8, 12, 0x2004, -16 },
    {  0,  4, 0x0008,  -8 }
  }
};
static SKC_sprite_pattern banevsp01c = {
  1,
  {
    { 0, 12, 0x2004, -16 }
  }
};
static SKC_sprite_pattern banevsp02c = {
  2,
  {
    { -24, 12, 0x2004, -16 },
    { -16,  6, 0x000A,  -8 }
  }
};


static SKC_sprite_pattern banehsp00 = {
  2,
  {
    { -16, 3, 0x0000,  0 },
    {  -8, 1, 0x0008, -8 }
  }
};
static SKC_sprite_pattern banehsp01 = {
  1,
  {
    { -16, 3, 0x0000, -8 }
  }
};
static SKC_sprite_pattern banehsp02 = {
  2,
  {
    { -16, 3, 0x0000, 16 },
    {  -8, 9, 0x000A, -8 }
  }
};


static SKC_sprite_pattern banehsp00c = {
  2,
  {
    { -16, 3, 0x2004,  0 },
    {  -8, 1, 0x0008, -8 }
  }
};
static SKC_sprite_pattern banehsp01c = {
  1,
  {
    { -16, 3, 0x2004, -8 }
  }
};
static SKC_sprite_pattern banehsp02c = {
  2,
  {
    { -16, 3, 0x2004, 16 },
    {  -8, 9, 0x000A, -8 }
  }
};


static SKC_sprite_pattern banevsp03 = {
  2,
  {
    {  0, 12, 0x1000, -16 },
    { -8,  4, 0x1008,  -8 }
  }
};


static SKC_sprite_pattern banevsp03c = {
  2,
  {
    {  0, 12, 0x3004, -16 },
    { -8,  4, 0x1008,  -8 }
  }
};


static SKC_sprite_pattern bane45sp00 = {
  4,
  {
    { -15, 8, 0x0000, -21 },
    {  -7, 8, 0x0003, -13 },
    {   1, 5, 0x0006,  -5 },
    {  -5, 5, 0x0014, -15 }
  }
};
static SKC_sprite_pattern bane45sp01 = {
  3,
  {
    { -9, 8, 0x0000, -26 },
    { -1, 8, 0x0003, -18 },
    {  7, 5, 0x0006, -10 }
  }
};
static SKC_sprite_pattern bane45sp02 = {
  5,
  {
    { -26, 8, 0x0000, -10 },
    { -18, 8, 0x0003,  -2 },
    { -10, 5, 0x0006,   6 },
    { -11, 4, 0x0018,  -6 },
    {  -3, 4, 0x001A, -14 }
  }
};
static SKC_sprite_pattern bane45sp03 = {
  4,
  {
    {   7, 8, 0x1000, -21 },
    {  -1, 8, 0x1003, -13 },
    { -17, 5, 0x1006,  -5 },
    { -11, 5, 0x1014, -15 }
  }
};


static SKC_sprite_pattern bane45sp00c = {
  4,
  {
    { -15, 8, 0x200A, -21 },
    {  -7, 8, 0x200D, -13 },
    {   1, 5, 0x2010,  -5 },
    {  -5, 5, 0x0014, -15 }
  }
};
static SKC_sprite_pattern bane45sp01c = {
  3,
  {
    { -9, 8, 0x200A, -26 },
    { -1, 8, 0x200D, -18 },
    {  7, 5, 0x2010, -10 }
  }
};
static SKC_sprite_pattern bane45sp02c = {
  5,
  {
    { -26, 8, 0x200A, -10 },
    { -18, 8, 0x200D,  -2 },
    { -10, 5, 0x2010,   6 },
    { -11, 4, 0x0018,  -6 },
    {  -3, 4, 0x001A, -14 }
  }
};
static SKC_sprite_pattern bane45sp03c = {
  4,
  {
    {   7, 8, 0x300A, -21 },
    {  -1, 8, 0x300D, -13 },
    { -17, 5, 0x3010,  -5 },
    { -11, 5, 0x1014, -15 }
  }
};


SKC_sprite_pattern* vsbanepat[7] = {
  &vsbanevsp00,
  &vsbanevsp01,
  &vsbanevsp02,
  &vsbanehsp00,
  &vsbanehsp01,
  &vsbanehsp02,
  &vsbanevsp03
};


static SKC_sprite_pattern* vsbanepat2[7] = {
  &vsbanevsp00c,
  &vsbanevsp01c,
  &vsbanevsp02c,
  &vsbanehsp00c,
  &vsbanehsp01c,
  &vsbanehsp02c,
  &vsbanevsp03c
};


static SKC_sprite_pattern vsbanevsp00 = {
  2,
  {
    { -10, 8, 0x0000, -12 },
    {  -5, 8, 0x0006, -12 }
  }
};
static SKC_sprite_pattern vsbanevsp01 = {
  1,
  {
    { -5, 8, 0x0000, -12 }
  }
};
static SKC_sprite_pattern vsbanevsp02 = {
  3,
  {
    { -15, 8, 0x0000, -12 },
    { -13, 0, 0x0009,  -4 },
    {  -5, 8, 0x000A, -12 }
  }
};
static SKC_sprite_pattern vsbanehsp00 = {
  2,
  {
    { -12, 2, 0x0800,  2 },
    { -12, 2, 0x0806, -3 }
  }
};
static SKC_sprite_pattern vsbanehsp01 = {
  1,
  {
    { -12, 2, 0x0800, -3 }
  }
};
static SKC_sprite_pattern vsbanehsp02 = {
  3,
  {
    { -12, 2, 0x0800,  7 },
    {  -4, 0, 0x0809,  5 },
    { -12, 2, 0x080A, -3 }
  }
};
static SKC_sprite_pattern vsbanevsp03 = {
  2,
  {
    {  2, 8, 0x1000, -12 },
    { -3, 8, 0x1006, -12 }
  }
};


static SKC_sprite_pattern vsbanevsp00c = {
  2,
  {
    { -10, 8, 0x0003, -12 },
    {  -5, 8, 0x0006, -12 }
  }
};
static SKC_sprite_pattern vsbanevsp01c = {
  1,
  {
    { -5, 8, 0x0003, -12 }
  }
};
static SKC_sprite_pattern vsbanevsp02c = {
  3,
  {
    { -15, 8, 0x0003, -12 },
    { -13, 0, 0x0009,  -4 },
    {  -5, 8, 0x000A, -12 }
  }
};
static SKC_sprite_pattern vsbanehsp00c = {
  2,
  {
    { -12, 2, 0x0803,  2 },
    { -12, 2, 0x0806, -3 }
  }
};
static SKC_sprite_pattern vsbanehsp01c = {
  1,
  {
    { -12, 2, 0x0803, -3 }
  }
};
static SKC_sprite_pattern vsbanehsp02c = {
  3,
  {
    { -12, 2, 0x0803,  7 },
    {  -4, 0, 0x0809,  5 },
    { -12, 2, 0x080A, -3 }
  }
};
static SKC_sprite_pattern vsbanevsp03c = {
  2,
  {
    {  2, 8, 0x1003, -12 },
    { -3, 8, 0x1006, -12 }
  }
};


void sjumpmv(SKC_sprite_status* p_actwk) {
  sjumpinit(p_actwk);
  sjumpmvkind(p_actwk);
}


static void sjumpmvkind(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler sjumpmvkindtbl[5] = {
    &sjumpmv_ymove,
    &sjumpmv_xmove,
    &sjumpmv_ymove2,
    &sjumpmv_xymove,
    &sjumpmv_xymove2
  };

  sjumpmvkindtbl[(p_actwk->u.obj.userflag >> 4 & 7)](p_actwk);
}


static void sjumpmv_ymove(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_ymove1;
  sjumpmv_ymove1(p_actwk);
}


static void sjumpmv_ymove1(SKC_sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  sjumpmove(p_actwk);
}


static void sjumpmv_xmove(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_xmove1;
  sjumpmv_xmove1(p_actwk);
}


static void sjumpmv_xmove1(SKC_sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  sdashmove(p_actwk);
}


static void sjumpmv_ymove2(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_ymove3;
  sjumpmv_ymove3(p_actwk);
}


static void sjumpmv_ymove3(SKC_sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  sjumprmove(p_actwk);
}


static void sjumpmv_xymove(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_xymove1;
  sjumpmv_xymove1(p_actwk);
}


static void sjumpmv_xymove1(SKC_sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset);
  if (p_actwk->u.obj.cddat.right == 0) {
    xposi = -xposi;
  }
  xposi += p_actwk->u.obj.actfree.spring.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  yposi += p_actwk->u.obj.actfree.spring.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  sjump45move(p_actwk);
}


static void sjumpmv_xymove2(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpmv_xymove3;
  sjumpmv_xymove3(p_actwk);
}


static void sjumpmv_xymove3(SKC_sprite_status* p_actwk) {
  sjumpmv_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset);
  if (p_actwk->u.obj.cddat.right == 1) {
    xposi = -xposi;
  }
  xposi += p_actwk->u.obj.actfree.spring.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  yposi += p_actwk->u.obj.actfree.spring.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  sjump45rmove(p_actwk);
}


static void sjumpmv_sub(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0 && p_actwk->actflg.onscreen == 1) {
      soundset(82);
    }
  }
  else if (p_actwk->u.obj.actfree.spring.reverse_dir) {
    p_actwk->u.obj.actfree.spring.offset -= 0x800;
    if (p_actwk->u.obj.actfree.spring.offset < 0) {
      p_actwk->u.obj.actfree.spring.offset = 0;
      p_actwk->u.obj.actfree.spring.reverse_dir = false;
      p_actwk->u.obj.timer = 60;
    }
  }
  else {
    p_actwk->u.obj.actfree.spring.offset += 0x800;
    if (p_actwk->u.obj.actfree.spring.offset >= 0x2000) {
      p_actwk->u.obj.actfree.spring.offset = 0x2000;
      p_actwk->u.obj.actfree.spring.reverse_dir = true;
      p_actwk->u.obj.timer = 60;
    }
  }
}


void sjumpsw(SKC_sprite_status* p_actwk) {
  struct {
    unsigned char sprhs;
    unsigned char sprvs;
    unsigned char patno;
    unsigned char userflag;
  }
  sjumpswtbl[8] = {
    { 12,  8,  0,  1 },
    { 12,  8,  0,  0 },
    { 12,  8,  0,  1 },
    {  8, 12,  1,  0 },
    { 12,  8,  2,  1 },
    { 12,  8,  3,  1 },
    { 12,  8,  2,  1 },
    { 12,  8,  3,  1 }
  };

  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    result.actwk_ptr->r_ptr = &sjumpswmove;
    result.actwk_ptr->patbase = get_zone(g_ram.stageno) != ENDLESS_MINE ? banedaipat : banedaipat2;
    result.actwk_ptr->sproffset = 0x0391;
    result.actwk_ptr->u.obj.userflag = p_actwk->u.obj.userflag;
    result.actwk_ptr->sprhs = sjumpswtbl[p_actwk->u.obj.userflag >> 2 & 0x1C].sprhs;
    result.actwk_ptr->sprvs = sjumpswtbl[p_actwk->u.obj.userflag >> 2 & 0x1C].sprvs;
    result.actwk_ptr->patno = sjumpswtbl[p_actwk->u.obj.userflag >> 2 & 0x1C].patno;
    if (result.actwk_ptr->patno == 0) {
      result.actwk_ptr->r_ptr = &sjumpswmove2;
    }
    p_actwk->u.obj.userflag &= 0xF0;
    p_actwk->u.obj.userflag |= sjumpswtbl[p_actwk->u.obj.userflag >> 2 & 0x1C].userflag;
    fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
    short xoffset, yoffset;

    switch (result.actwk_ptr->patno) {
      case 1:
        xoffset = 12;
        if (p_actwk->u.obj.cddat.right == 0) {
          xoffset = -xoffset;
        }
        fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(result.actwk_ptr->xposi) + xoffset);
        break;
      case 2:
        yoffset = 11;
        fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(result.actwk_ptr->yposi) + yoffset);
        break;
      case 3:
        yoffset = -11;
        fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(result.actwk_ptr->yposi) + yoffset);
        break;
    }

    result.actwk_ptr->u.obj.actfree.springsw.xoffset = xoffset;
    result.actwk_ptr->u.obj.actfree.springsw.yoffset = yoffset;
    if (p_actwk->u.obj.cddat.down == 1) {
      p_actwk->u.obj.actfree.spring.unknown3c = 1;
    }
    p_actwk->u.obj.cddat.down = 0;
    result.actwk_ptr->u.obj.cddat = p_actwk->u.obj.cddat;
    result.actwk_ptr->actflg = p_actwk->actflg;
    result.actwk_ptr->actflg.relative_coordinates = 1;
    result.actwk_ptr->sprpri = PRI_4;
    result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
    p_actwk->u.obj.ko = result.actwk_ptr - g_ram.actwk;
  }
  sjumpswinit(p_actwk);
}


static void sjumpswkind(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler sjumpswkindtbl[8] = {
    &sjumpsw_ymove,
    &sjumpsw_xmove,
    &sjumpsw_ymove2,
    &sjumpsw_ymove4,
    &sjumpsw_xmove2,
    &sjumpsw_xmove4,
    &sjumpsw_xmove2,
    &sjumpsw_xmove4
  };

  sjumpswkindtbl[p_actwk->u.obj.userflag >> 4 & 7](p_actwk);
}


static void sjumpsw_ymove(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_ymove1;
  sjumpsw_ymove1(p_actwk);
}


static void sjumpsw_ymove1(SKC_sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  vssjumpmove(p_actwk);
}


static void sjumpsw_xmove(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_xmove1;
  sjumpsw_xmove1(p_actwk);
}


static void sjumpsw_xmove1(SKC_sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  vssdashmove(p_actwk);
}


static void sjumpsw_ymove2(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_ymove3;
  sjumpsw_ymove3(p_actwk);
}


static void sjumpsw_ymove3(SKC_sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  vssjumprmove(p_actwk);
}


static void sjumpsw_ymove4(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_ymove5;
  sjumpsw_ymove5(p_actwk);
}


static void sjumpsw_ymove5(SKC_sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short yposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  vssdashmove(p_actwk);
}


static void sjumpsw_xmove2(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_xmove3;
  sjumpsw_xmove3(p_actwk);
}


static void sjumpsw_xmove3(SKC_sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  vssjumpmove(p_actwk);
}


static void sjumpsw_xmove4(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &sjumpsw_xmove5;
  sjumpsw_xmove5(p_actwk);
}


static void sjumpsw_xmove5(SKC_sprite_status* p_actwk) {
  sjumpsw_sub(p_actwk);
  short xposi = fp8_get_integer(p_actwk->u.obj.actfree.spring.offset) + p_actwk->u.obj.actfree.spring.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  vssjumprmove(p_actwk);
}


static void sjumpsw_sub(SKC_sprite_status* p_actwk) {
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
    sjumpsw_sub2(p_actwk);
  }
  else if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0 && p_actwk->actflg.onscreen == 1) {
      soundset(82);
    }
  }
  else if (p_actwk->u.obj.actfree.spring.reverse_dir) {
    p_actwk->u.obj.actfree.spring.offset -= 0x800;
    if (p_actwk->u.obj.actfree.spring.offset < 0) {
      p_actwk->u.obj.actfree.spring.offset = 0;
      p_actwk->u.obj.actfree.spring.reverse_dir = false;
      p_actwk->u.obj.timer = 60;
    }
  }
  else {
    p_actwk->u.obj.actfree.spring.offset += 0x800;
    if (p_actwk->u.obj.actfree.spring.offset >= 0x1800) {
      p_actwk->u.obj.actfree.spring.offset = 0x1800;
      p_actwk->u.obj.actfree.spring.reverse_dir = true;
      p_actwk->u.obj.timer = 60;
    }
  }
}


static void sjumpsw_sub2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.spring.unknown3c == 0) {
    sjumpsw_sub3(p_actwk);
  }
  else if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      p_actwk->u.obj.actfree.spring.reverse_dir = false;
    }
  }
  else if (!p_actwk->u.obj.actfree.spring.reverse_dir) {
    if (p_actwk->u.obj.actfree.spring.offset != 0) {
      p_actwk->u.obj.actfree.spring.offset -= 0x800;
      if (p_actwk->u.obj.actfree.spring.offset <= 0) {
        p_actwk->u.obj.actfree.spring.offset = 0;
        if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)
            && BIT_IS_SET(p_actwk->u.obj.userflag, 5)
            && BIT_IS_SET(p_actwk->u.obj.userflag, 6)
            && BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
          fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 22);
          p_actwk->u.obj.cddat.down ^= 1;
          p_actwk->actflg.vflip ^= 1;
          SET_BIT(p_actwk->u.obj.userflag, 4);
          p_actwk->r_ptr = &sjumpswkind;
          SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
          p_childwk->u.obj.actfree.springsw.yoffset = -p_childwk->u.obj.actfree.springsw.yoffset;
        }
        else if (BIT_IS_SET(p_actwk->u.obj.userflag, 4)
            && BIT_IS_SET(p_actwk->u.obj.userflag, 5)
            && BIT_IS_SET(p_actwk->u.obj.userflag, 6)
            && BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
          fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 22);
          p_actwk->u.obj.cddat.down ^= 1;
          p_actwk->actflg.vflip ^= 1;
          CLEAR_BIT(p_actwk->u.obj.userflag, 4);
          p_actwk->r_ptr = &sjumpswkind;
          SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
          p_childwk->u.obj.actfree.springsw.yoffset = -p_childwk->u.obj.actfree.springsw.yoffset;
        }
      }
    }
  }
  else {
    p_actwk->u.obj.actfree.spring.offset += 0x800;
    if (p_actwk->u.obj.actfree.spring.offset >= 0x1800) {
      p_actwk->u.obj.actfree.spring.offset = 0x1800;
      p_actwk->u.obj.timer = 180;
    }
  }
}


static void sjumpsw_sub3(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      p_actwk->u.obj.actfree.spring.reverse_dir = false;
    }
  }
  else if (p_actwk->u.obj.actfree.spring.reverse_dir) {
    p_actwk->u.obj.actfree.spring.offset -= 0x800;
    if (p_actwk->u.obj.actfree.spring.offset < 0) {
      p_actwk->u.obj.actfree.spring.offset = 0;
      p_actwk->u.obj.timer = 180;
    }
  }
  else if (p_actwk->u.obj.actfree.spring.offset != 0x1800) {
    p_actwk->u.obj.actfree.spring.offset += 0x800;
    if (p_actwk->u.obj.actfree.spring.offset >= 0x1800) {
      p_actwk->u.obj.actfree.spring.offset = 0x1800;
      if (!BIT_IS_SET(p_actwk->u.obj.userflag, 4)
          && BIT_IS_SET(p_actwk->u.obj.userflag, 5)
          && BIT_IS_SET(p_actwk->u.obj.userflag, 6)
          && BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 22);
        p_actwk->u.obj.cddat.down ^= 1;
        p_actwk->actflg.vflip ^= 1;
        SET_BIT(p_actwk->u.obj.userflag, 4);
        p_actwk->r_ptr = &sjumpswkind;
        SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
        p_childwk->u.obj.actfree.springsw.yoffset = -p_childwk->u.obj.actfree.springsw.yoffset;
      }
      else if (BIT_IS_SET(p_actwk->u.obj.userflag, 4)
          && BIT_IS_SET(p_actwk->u.obj.userflag, 5)
          && BIT_IS_SET(p_actwk->u.obj.userflag, 6)
          && BIT_IS_SET(p_actwk->u.obj.userflag, 7)) {
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 22);
        p_actwk->u.obj.cddat.down ^= 1;
        p_actwk->actflg.vflip ^= 1;
        CLEAR_BIT(p_actwk->u.obj.userflag, 4);
        p_actwk->r_ptr = &sjumpswkind;
        SKC_sprite_status* p_childwk = &g_ram.actwk[p_actwk->u.obj.ko];
        p_childwk->u.obj.actfree.springsw.yoffset = -p_childwk->u.obj.actfree.springsw.yoffset;
      }
    }
  }
}


static void sjumpswmove(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  short xposi = fp16_get_integer(p_parentwk->xposi) + p_actwk->u.obj.actfree.springsw.xoffset;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = fp16_get_integer(p_parentwk->yposi) + p_actwk->u.obj.actfree.springsw.yoffset;
  fp16_set_integer(&p_actwk->yposi, yposi);
  if (BIT_IS_SET(p_actwk->u.obj.userflag, 7) && g_ram.stage_triggers[p_actwk->u.obj.userflag & 0xF] != 0) {
    p_parentwk->u.obj.actfree.spring.reverse_dir = true;
  }
  SKC_hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    fp16_get_integer(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  actionsub(p_actwk);
}


static void sjumpswmove2(SKC_sprite_status* p_actwk) {
  if (!BIT_IS_SET(p_actwk->u.obj.userflag, 7)) return;
  if (g_ram.stage_triggers[p_actwk->u.obj.userflag & 0xF] == 0) return;

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_parentwk->u.obj.actfree.spring.reverse_dir = true;
}


static SKC_sprite_pattern* banedaipat[4] = {
  &banedaisp00,
  &banedaisp01,
  &banedaisp02,
  &banedaisp02
};


static SKC_sprite_pattern* banedaipat2[4] = {
  &banedaisp00,
  &banedaisp03,
  &banedaisp02,
  &banedaisp02
};


static SKC_sprite_pattern banedaisp00 = {
  0,
  {}
};
static SKC_sprite_pattern banedaisp01 = {
  1,
  {
    { -12, 6, 0x082F, -8 }
  }
};
static SKC_sprite_pattern banedaisp02 = {
  1,
  {
    { -8, 9, 0x600D, -12 }
  }
};
static SKC_sprite_pattern banedaisp03 = {
  1,
  {
    { -12, 10, 0x4774, -16 }
  }
};
