#include "friend.h"
#include "../types/actwkchkresult.h"
#include "../types/friendinitdata.h"
#include "../types/point.h"
#include "../types/setact05data.h"
#include "../types/sonic3ram.h"
#include "../types/speed.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../constants.h"
#include "../etc.h"
#include "../shared.h"
#define POCKY_RABBIT 0
#define CUCKY_CHICKEN 1
#define PECKY_PINGUIN 2
#define ROCKY_SEAL 3
#define FLICKY_FLICKY 5
#define RICKY_SQUIRREL 6
static SKC_speed spd_tbl[11];
static SKC_sprite_pattern** pat_tbl[11];
static unsigned short ofs_tbl[11];
static void friendinit(SKC_sprite_status* p_actwk);
static void friendmove(SKC_sprite_status* p_actwk);
static void friendjump(SKC_sprite_status* p_actwk);
static void friendfly(SKC_sprite_status* p_actwk);
static void chk_friend_fout(SKC_sprite_status* p_actwk);
static void friendwait(SKC_sprite_status* p_actwk);
static void tenmove(SKC_sprite_status* p_actwk);
static SKC_set_act05_data cucky_group_set_tbl;
static void cucky_init(SKC_sprite_status* p_actwk);
static SKC_point cucky_posi_tbl[4];
static void cucky_wait(SKC_sprite_status* p_actwk);
static void cucky_move(SKC_sprite_status* p_actwk);
static SKC_set_act05_data ricky_group_set_tbl;
static void ricky_init(SKC_sprite_status* p_actwk);
static SKC_point ricky_posi_tbl[4];
static void ricky_pocky_move(SKC_sprite_status* p_actwk);
static SKC_set_act05_data pocky_group_set_tbl;
static void pocky_init(SKC_sprite_status* p_actwk);
static SKC_point pocky_posi_tbl[4];
static void friend_init_sub(SKC_sprite_status* p_actwk, SKC_point posi_tbl[4]);
static void friend_patchg(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern cuckyflickysp00;
static SKC_sprite_pattern cuckyflickysp01;
static SKC_sprite_pattern cuckyflickysp02;
static SKC_sprite_pattern rickysp00;
static SKC_sprite_pattern rickysp01;
static SKC_sprite_pattern rickysp02;
static SKC_sprite_pattern pickysp00;
static SKC_sprite_pattern pickysp01;
static SKC_sprite_pattern pickysp02;
static SKC_sprite_pattern rockysp00;
static SKC_sprite_pattern rockysp01;
static SKC_sprite_pattern rockysp02;
static SKC_sprite_pattern pockypeckysp00;
static SKC_sprite_pattern pockypeckysp01;
static SKC_sprite_pattern pockypeckysp02;
static SKC_sprite_pattern* tenpat[7];
static SKC_sprite_pattern tensp00;
static SKC_sprite_pattern tensp01;
static SKC_sprite_pattern tensp02;
static SKC_sprite_pattern tensp03;
static SKC_sprite_pattern tensp04;
static SKC_sprite_pattern tensp05;
static SKC_sprite_pattern tensp06;

extern sonic3_ram g_ram;


void friend(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[15] = {
    &friendinit,
    &friendmove,
    &friendjump,
    &friendfly,
    &friendjump,
    &friendjump,
    &friendjump,
    &friendfly,
    &friendjump,
    &friendfly,
    &friendjump,
    &friendjump,
    &friendjump,
    &friendjump,
    &friendwait
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


unsigned char zone_friend_tbl[24][2] = {
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { POCKY_RABBIT, ROCKY_SEAL },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { POCKY_RABBIT, FLICKY_FLICKY },
  { RICKY_SQUIRREL, FLICKY_FLICKY },
  { PECKY_PINGUIN, ROCKY_SEAL },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { RICKY_SQUIRREL, CUCKY_CHICKEN },
  { POCKY_RABBIT, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { POCKY_RABBIT, FLICKY_FLICKY },
  { RICKY_SQUIRREL, CUCKY_CHICKEN },
  { RICKY_SQUIRREL, FLICKY_FLICKY },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN },
  { FLICKY_FLICKY, CUCKY_CHICKEN }
};


SKC_friend_init_data zone_friend_init_tbl[12] = {
  { -0x200, -0x400, pockypeckypat },
  { -0x200, -0x300, cuckyflickypat },
  { -0x180, -0x300, pockypeckypat },
  { -0x140, -0x180, rockypat },
  { -0x1C0, -0x300, pickypat },
  { -0x300, -0x400, cuckyflickypat },
  { -0x280, -0x380, rickypat },
  { -0x280, -0x300, cuckyflickypat },
  { -0x200, -0x380, rickypat },
  { -0x2C0, -0x300, rickypat },
  { -0x140, -0x200, rickypat },
  { -0x200, -0x300, rickypat }
};


static SKC_speed spd_tbl[11] = {
  { -0x440, -0x400 },
  { -0x440, -0x400 },
  { -0x440, -0x400 },
  { -0x300, -0x400 },
  { -0x300, -0x400 },
  { -0x180, -0x300 },
  { -0x180, -0x300 },
  { -0x140, -0x180 },
  { -0x1C0, -0x300 },
  { -0x200, -0x300 },
  { -0x280, -0x380 }
};


static SKC_sprite_pattern** pat_tbl[11] = {
  cuckyflickypat,
  cuckyflickypat,
  cuckyflickypat,
  pockypeckypat,
  pockypeckypat,
  pockypeckypat,
  pockypeckypat,
  rockypat,
  pickypat,
  cuckyflickypat,
  rickypat
};


static unsigned short ofs_tbl[11] = {
  0x05A5,
  0x05A5,
  0x05A5,
  0x0553,
  0x0553,
  0x0573,
  0x0573,
  0x0585,
  0x0593,
  0x0565,
  0x05B3
};


static void friendinit(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.userflag != 0) {
    p_actwk->r_no = p_actwk->u.obj.userflag * 2;
    unsigned short type = p_actwk->u.obj.userflag - 10;
    p_actwk->sproffset = ofs_tbl[type];
    p_actwk->patbase = pat_tbl[type];
    p_actwk->u.obj.actfree.friend.xspeed_init = spd_tbl[type].xspeed;
    p_actwk->xspeed = spd_tbl[type].xspeed;
    p_actwk->u.obj.actfree.friend.yspeed_init = spd_tbl[type].yspeed;
    p_actwk->yspeed = spd_tbl[type].yspeed;
    p_actwk->sprvsize = 12;
    p_actwk->actflg.relative_coordinates = 1;
    p_actwk->actflg.hflip = 1;
    p_actwk->sprpri = PRI_6;
    p_actwk->sprhs = 8;
    p_actwk->pattim = 7;
    actionsub(p_actwk);
  }
  else {
    p_actwk->r_no += 2;
    unsigned char zone_type = random() & 1;
    p_actwk->sproffset = zone_type == 0 ? 0x0580 : 0x592;
    p_actwk->u.obj.actfree.friend.type = zone_friend_tbl[g_ram.stageno][zone_type];
    p_actwk->u.obj.actfree.friend.xspeed_init = zone_friend_init_tbl[p_actwk->u.obj.actfree.friend.type].xspeed;
    p_actwk->u.obj.actfree.friend.yspeed_init = zone_friend_init_tbl[p_actwk->u.obj.actfree.friend.type].yspeed;
    p_actwk->patbase = zone_friend_init_tbl[p_actwk->u.obj.actfree.friend.type].patbase;
    p_actwk->sprvsize = 12;
    p_actwk->actflg.relative_coordinates = 1;
    p_actwk->actflg.hflip = 1;
    p_actwk->sprpri = PRI_6;
    p_actwk->sprhs = 8;
    p_actwk->pattim = 7;
    p_actwk->patno = 2;
    p_actwk->yspeed = -0x400;
    if (!p_actwk->u.obj.actfree.friend.masin) {
      SKC_actwkchk_result result = actwkchk();
      if (result.actwk_ptr != 0) {
        result.actwk_ptr->r_ptr = &ten;
        fp16_set_integer(&result.actwk_ptr->xposi, fp16_get_integer(p_actwk->xposi));
        fp16_set_integer(&result.actwk_ptr->yposi, fp16_get_integer(p_actwk->yposi));
        result.actwk_ptr->patno = p_actwk->u.obj.actfree.friend.points / 2;
      }
      actionsub(p_actwk);
    }
    else {
      p_actwk->r_no = 28;
      p_actwk->xspeed = 0;
      actionsub(p_actwk);
    }
  }
}


static void friendmove(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    speedset(p_actwk);
    if (p_actwk->yspeed >= 0) {
      short yoffset = ObjCheckFloorDist(p_actwk);
      if (yoffset < 0) {
        fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
        p_actwk->xspeed = p_actwk->u.obj.actfree.friend.xspeed_init;
        p_actwk->yspeed = p_actwk->u.obj.actfree.friend.yspeed_init;
        p_actwk->patno = 1;
        p_actwk->r_no = p_actwk->u.obj.actfree.friend.type * 2 + 4;
        if (p_actwk->u.obj.actfree.friend.masin && g_ram.systemtimer & 4) {
          p_actwk->actflg.hflip ^= 1;
        }
      }
    }
    actionsub(p_actwk);
  }
}


static void friendjump(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  p_actwk->patno = p_actwk->yspeed >= 0 ? 1 : 0;
  if (p_actwk->yspeed >= 0) {
    short yoffset = ObjCheckFloorDist(p_actwk);
    if (yoffset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
      p_actwk->yspeed = p_actwk->u.obj.actfree.friend.yspeed_init;
    }
  }
  if (p_actwk->u.obj.userflag != 0) {
    chk_friend_fout(p_actwk);
  }
  else if (p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void friendfly(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->yspeed >= 0) {
    short yoffset = ObjCheckFloorDist(p_actwk);
    if (yoffset < 0) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + yoffset);
      p_actwk->yspeed = p_actwk->u.obj.actfree.friend.yspeed_init;
      if (p_actwk->u.obj.userflag != 0 && p_actwk->u.obj.userflag != 10) {
        p_actwk->xspeed = -p_actwk->xspeed;
        p_actwk->actflg.hflip ^= 1;
      }
    }
  }
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 1;
    ++p_actwk->patno;
    p_actwk->patno &= 1;
  }
  if (p_actwk->u.obj.userflag != 0) {
    chk_friend_fout(p_actwk);
  }
  else if (p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void chk_friend_fout(SKC_sprite_status* p_actwk) {
  short xposi = fp16_get_integer(p_actwk->xposi) - fp16_get_integer(g_ram.actwk[0].xposi);
  if (xposi >= 0 && xposi - 384 < 0 && p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


static void friendwait(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 0) {
      p_actwk->r_no = 2;
      p_actwk->sprpri = PRI_1;
    }
    actionsub(p_actwk);
  }
}


void ten(SKC_sprite_status* p_actwk) {
  p_actwk->patbase = tenpat;
  p_actwk->sproffset = 0x85E4;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 8;
  p_actwk->yspeed = -0x300;
  p_actwk->r_ptr = &tenmove;
  tenmove(p_actwk);
}


static void tenmove(SKC_sprite_status* p_actwk) {
  if (p_actwk->yspeed >= 0) {
    frameout(p_actwk);
  }
  else {
    speedset2(p_actwk);
    p_actwk->yspeed += 0x18;
    actionsub(p_actwk);
  }
}


void cucky_group(SKC_sprite_status* p_actwk) {
  set_act05(p_actwk, &cucky_group_set_tbl);
  frameout(p_actwk);
}


static SKC_set_act05_data cucky_group_set_tbl = {
  3,
  &cucky_init
};


static void cucky_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &cucky_move;
  p_actwk->patbase = cuckyflickypat;
  p_actwk->sproffset = 0x22C1;
  friend_init_sub(p_actwk, cucky_posi_tbl);
  FUN_007a57db();
}


static SKC_point cucky_posi_tbl[4] = {
  { 192, 160 },
  { 168, 200 },
  { 208, 184 },
  { 216, 208 }
};


static void cucky_wait(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer-- == 0) {
    p_actwk->r_ptr = &cucky_move;
  }
  friend_patchg(p_actwk);
  actionsub(p_actwk);
}


static void cucky_move(SKC_sprite_status* p_actwk) {
  friend_patchg(p_actwk);
  puka_puka(p_actwk);
  speedset2(p_actwk);
  actionsub(p_actwk);
}


void ricky_group(SKC_sprite_status* p_actwk) {
  set_act05(p_actwk, &ricky_group_set_tbl);
  frameout(p_actwk);
}


static SKC_set_act05_data ricky_group_set_tbl = {
  3,
  &ricky_init
};


static void ricky_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &ricky_pocky_move;
  p_actwk->patbase = rickypat;
  p_actwk->sproffset = 0x22CF;
  p_actwk->actflg.hflip = 1;
  p_actwk->u.obj.actfree.friend.yposi_init = fp16_get_integer(p_actwk->yposi);
}


static SKC_point ricky_posi_tbl[4] = {
  { 352, 304 },
  { 384, 288 },
  { 416, 296 },
  { 376, 312 }
};


static void ricky_pocky_move(SKC_sprite_status* p_actwk) {
  speedset(p_actwk);
  p_actwk->patno = p_actwk->yspeed >= 0 ? 1 : 0;
  if (p_actwk->yspeed >= 0) {
    if ((unsigned short)fp16_get_integer(p_actwk->yposi) >= (unsigned short)p_actwk->u.obj.actfree.friend.yposi_init) {
      fp16_set_integer(&p_actwk->yposi, p_actwk->u.obj.actfree.friend.yposi_init);
      p_actwk->yspeed = -(short)((random() & 0x1FF) + 256);
    }
  }
  actionsub(p_actwk);
}


void pocky_group(SKC_sprite_status* p_actwk) {
  set_act05(p_actwk, &pocky_group_set_tbl);
  frameout(p_actwk);
}


static SKC_set_act05_data pocky_group_set_tbl = {
  3,
  &pocky_init
};


static void pocky_init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &ricky_pocky_move;
  p_actwk->patbase = pockypeckypat;
  p_actwk->sproffset = 0x22E1;
  friend_init_sub(p_actwk, pocky_posi_tbl);
  p_actwk->u.obj.actfree.friend.yposi_init = fp16_get_integer(p_actwk->yposi);
}


static SKC_point pocky_posi_tbl[4] = {
  { 192, 272 },
  { 168, 296 },
  { 192, 304 },
  { 216, 312 }
};


static void friend_init_sub(SKC_sprite_status* p_actwk, SKC_point posi_tbl[4]) {
  fp16_set_integer(&p_actwk->xposi, posi_tbl[p_actwk->u.obj.userflag / 2].x);
  fp16_set_integer(&p_actwk->yposi, posi_tbl[p_actwk->u.obj.userflag / 2].y);
  p_actwk->u.obj.timer = p_actwk->u.obj.userflag * 4;
  p_actwk->sprhs = 16;
  p_actwk->sprvs = 16;
  p_actwk->sprpri = PRI_4;
}


static void friend_patchg(SKC_sprite_status* p_actwk) {
  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 2;
    ++p_actwk->patno;
    p_actwk->patno &= 1;
  }
}


SKC_sprite_pattern* cuckyflickypat[3] = {
  &cuckyflickysp01,
  &cuckyflickysp02,
  &cuckyflickysp00
};


static SKC_sprite_pattern cuckyflickysp00 = {
  1,
  {
    { -12, 6, 0x0000, -8 }
  }
};
static SKC_sprite_pattern cuckyflickysp01 = {
  1,
  {
    { -8, 5, 0x0006, -8 }
  }
};
static SKC_sprite_pattern cuckyflickysp02 = {
  1,
  {
    { -8, 5, 0x000A, -8 }
  }
};


SKC_sprite_pattern* rickypat[3] = {
  &rickysp01,
  &rickysp02,
  &rickysp00
};


static SKC_sprite_pattern rickysp00 = {
  1,
  {
    { -12, 6, 0x0000, -8 }
  }
};
static SKC_sprite_pattern rickysp01 = {
  1,
  {
    { -8, 9, 0x0006, -12 }
  }
};
static SKC_sprite_pattern rickysp02 = {
  1,
  {
    { -8, 9, 0x000C, -12 }
  }
};


SKC_sprite_pattern* pickypat[3] = {
  &pickysp01,
  &pickysp02,
  &pickysp00
};


static SKC_sprite_pattern pickysp00 = {
  1,
  {
    { -12, 6, 0x0000, -8 }
  }
};
static SKC_sprite_pattern pickysp01 = {
  1,
  {
    { -8, 9, 0x0006, -12 }
  }
};
static SKC_sprite_pattern pickysp02 = {
  1,
  {
    { -8, 9, 0x000C, -12 }
  }
};


SKC_sprite_pattern* rockypat[3] = {
  &rockysp01,
  &rockysp02,
  &rockysp00
};


static SKC_sprite_pattern rockysp00 = {
  1,
  {
    { -8, 6, 0x0000, -8 }
  }
};
static SKC_sprite_pattern rockysp01 = {
  1,
  {
    { -4, 5, 0x0006, -8 }
  }
};
static SKC_sprite_pattern rockysp02 = {
  1,
  {
    { -4, 5, 0x000A, -8 }
  }
};


SKC_sprite_pattern* pockypeckypat[3] = {
  &pockypeckysp01,
  &pockypeckysp02,
  &pockypeckysp00
};


static SKC_sprite_pattern pockypeckysp00 = {
  1,
  {
    { -12, 6, 0x0000, -8 }
  }
};
static SKC_sprite_pattern pockypeckysp01 = {
  1,
  {
    { -12, 6, 0x0006, -8 }
  }
};
static SKC_sprite_pattern pockypeckysp02 = {
  1,
  {
    { -12, 6, 0x000C, -8 }
  }
};


static SKC_sprite_pattern* tenpat[7] = {
  &tensp00,
  &tensp01,
  &tensp02,
  &tensp03,
  &tensp04,
  &tensp05,
  &tensp06
};


static SKC_sprite_pattern tensp00 = {
  1,
  {
    { -4, 4, 0x0000, -6 }
  }
};
static SKC_sprite_pattern tensp01 = {
  1,
  {
    { -4, 4, 0x0002, -8 }
  }
};
static SKC_sprite_pattern tensp02 = {
  1,
  {
    { -4, 4, 0x0004, -8 }
  }
};
static SKC_sprite_pattern tensp03 = {
  2,
  {
    { -4, 0, 0x0000, -8 },
    { -4, 4, 0x0006, 0 }
  }
};
static SKC_sprite_pattern tensp04 = {
  1,
  {
    { -4, 0, 0x0000, -4 }
  }
};
static SKC_sprite_pattern tensp05 = {
  2,
  {
    { -4, 4, 0x0000, -8 },
    { -4, 4, 0x0006, 5 }
  }
};
static SKC_sprite_pattern tensp06 = {
  2,
  {
    { -4, 4, 0x0004, -8 },
    { -4, 4, 0x0006, 7 }
  }
};
