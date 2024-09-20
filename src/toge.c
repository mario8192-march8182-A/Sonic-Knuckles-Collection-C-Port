#include "globals.h"
#include "macros.h"
#include "util.h"
#include "types/hitchkdata.h"
#include "types/hitchkresults.h"
#include "toge.h"
#include "004xxxxx.h"
#include "hitchk.h"
static unsigned char togetbl[8][2];
static void togeinit(sprite_status* p_actwk, unsigned char d0);
static unsigned char vstogetbl[8][2];
static void vstogeinit(sprite_status* p_actwk, unsigned char d0);
static void togemove(sprite_status* p_actwk);
static void togemove2(sprite_status* p_actwk);
static void togemove3(sprite_status* p_actwk);
static void vstogemove(sprite_status* p_actwk);
static void vstogemove2(sprite_status* p_actwk);
static void vstogemove3(sprite_status* p_actwk);
static void togekind(sprite_status* p_actwk);
static sprite_status_handler togekindtbl[4];
static void toge_no(sprite_status* p_actwk);
static void toge_ymove(sprite_status* p_actwk);
static void toge_xmove(sprite_status* p_actwk);
static void toge_sub(sprite_status* p_actwk);
static void toge_push(sprite_status* p_actwk);
static void toge_push__sub(sprite_status* p_actwk, short xposi, unsigned char cddat1, unsigned char bit, sprite_status* p_playerwk, unsigned char plcddat1);
static void vstogekind(sprite_status* p_actwk);
static sprite_status_handler vstogekindtbl[3];
static void vstoge_ymove(sprite_status* p_actwk);
static void vstoge_xmove(sprite_status* p_actwk);
static void vstoge_sub(sprite_status* p_actwk);
static signed char togesp00[14];
static signed char togesp01[26];
static signed char togesp02[38];
static signed char togesp03[50];
static signed char togesp04[14];
static signed char togesp05[26];
static signed char togesp06[38];
static signed char togesp07[50];
static signed char vstogesp00[8];
static signed char vstogesp01[14];
static signed char vstogesp02[20];
static signed char vstogesp03[26];
static signed char vstogesp04[8];
static signed char vstogesp05[14];
static signed char vstogesp06[20];
static signed char vstogesp07[26];


static unsigned char togetbl[8][2] = {
  { 16, 16 },
  { 32, 16 },
  { 48, 16 },
  { 64, 16 },
  { 16, 16 },
  { 16, 32 },
  { 16, 48 },
  { 16, 64 }
};


void toge(sprite_status* p_actwk) {
  SET_BIT(p_actwk->actflg, FLG_LEVELCOORDS);
  p_actwk->sprpri = PRI_4;
  unsigned char userflag = (p_actwk->userflag1 & 0xF0) / 8;
  if (g_mdRam.vs_flag != 0) {
    vstogeinit(p_actwk, userflag);
  }
  else {
    togeinit(p_actwk, userflag);
  }
}


static void togeinit(sprite_status* p_actwk, unsigned char userflag) {
  unsigned char* size = &togetbl[userflag / 2][0];
  p_actwk->sprhs = size[0];
  p_actwk->sprvs = size[1];
  p_actwk->r_ptr = &togemove;
  p_actwk->patbase = togepat;
  p_actwk->sproffset = 1180;
  if (GET_ZONE(g_mdRam.stageno) == FLYING_BATTERY) {
    p_actwk->sproffset = 512;
  }
  userflag >>= 1;
  p_actwk->patno = userflag;
  if (userflag >= 4) { // unsigned
    p_actwk->r_ptr = &togemove2;
    p_actwk->sproffset = 1172;
  }
  unsigned char cddat1 = p_actwk->cddat1;
  if (g_mdRam.reverse_gravity_flag != 0) {
    cddat1 ^= 2;
  }
  if (BIT_IS_SET(cddat1, CD_DOWN)) {
    p_actwk->r_ptr = &togemove3;
  }
  p_actwk->actfree.toge.push_distance = 32;
  p_actwk->actfree.toge.orig_xposi = LONG_HIGH(p_actwk->xposi);
  p_actwk->actfree.toge.orig_yposi = LONG_HIGH(p_actwk->yposi);
  p_actwk->userflag1 = (p_actwk->userflag1 & 0xF) * 2;
}


static unsigned char vstogetbl[8][2] = {
  { 12, 12 },
  { 24, 12 },
  { 36, 12 },
  { 48, 12 },
  { 12, 12 },
  { 12, 24 },
  { 12, 36 },
  { 12, 48 }
};


static void vstogeinit(sprite_status* p_actwk, unsigned char userflag) {
  unsigned char* size = &togetbl[userflag / 2][0];
  p_actwk->sprhs = size[0];
  p_actwk->sprvs = size[1];
  p_actwk->r_ptr = &vstogemove;
  p_actwk->patbase = vstogepat;
  p_actwk->sproffset = 913;
  userflag >>= 1;
  p_actwk->patno = userflag;
  if (userflag >= 4) { // unsigned
    p_actwk->r_ptr = &vstogemove2;
  }
  if (BIT_IS_SET(p_actwk->cddat1, CD_DOWN)) {
    p_actwk->r_ptr = &vstogemove3;
  }
  p_actwk->actfree.toge.orig_xposi = LONG_HIGH(p_actwk->xposi);
  p_actwk->actfree.toge.orig_yposi = LONG_HIGH(p_actwk->yposi);
  p_actwk->userflag1 = (p_actwk->userflag1 & 0xF) * 2;
}


static void togemove(sprite_status* p_actwk) {
  togekind(p_actwk);
  hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  if (p_actwk->cddat1 & 0x18) {
    if (BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[0]);
    }
    if (BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[1]);
    }
  }
  frameoutchk2(p_actwk, p_actwk->actfree.toge.orig_xposi);
}


static void togemove2(sprite_status* p_actwk) {
  togekind(p_actwk);
  hitchk_data data = {
    p_actwk->sprhs,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk_results results = hitchk(p_actwk, data);
  if (results.plcoli & 3) {
    if (BIT_0_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[0]);
      CLEAR_BIT(p_actwk->cddat1, CD_PLPUSH);
    }
    if (BIT_1_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[1]);
      CLEAR_BIT(p_actwk->cddat1, CD_PL2PUSH);
    }
  }
  frameoutchk2(p_actwk, p_actwk->actfree.toge.orig_xposi);
}


static void togemove3(sprite_status* p_actwk) {
  togekind(p_actwk);
  hitchk_data data = {
    p_actwk->sprhs + 11,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk_results results = hitchk(p_actwk, data);
  if (results.plcoli & 0xC) {
    if (BIT_2_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[0]);
    }
    if (BIT_3_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[1]);
    }
  }
  frameoutchk2(p_actwk, p_actwk->actfree.toge.orig_xposi);
}


static void vstogemove(sprite_status* p_actwk) {
  vstogekind(p_actwk);
  hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk(p_actwk, data);
  if (p_actwk->cddat1 & 0x18) {
    if (BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[0]);
    }
    if (BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[1]);
    }
  }
  actionsub(p_actwk);
}


static void vstogemove2(sprite_status* p_actwk) {
  vstogekind(p_actwk);
  hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk_results results = hitchk(p_actwk, data);
  if (results.plcoli & 3) {
    if (BIT_0_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[0]);
      CLEAR_BIT(p_actwk->cddat1, CD_PLPUSH);
    }
    if (BIT_1_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[1]);
      CLEAR_BIT(p_actwk->cddat1, CD_PL2PUSH);
    }
  }
  actionsub(p_actwk);
}


static void vstogemove3(sprite_status* p_actwk) {
  vstogekind(p_actwk);
  hitchk_data data = {
    p_actwk->sprhs + 7,
    p_actwk->sprvs,
    p_actwk->sprvs + 1,
    LONG_HIGH(p_actwk->xposi)
  };
  hitchk_results results = hitchk(p_actwk, data);
  if (results.plcoli & 0xC) {
    if (BIT_2_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[0]);
    }
    if (BIT_3_IS_SET(results.plcoli)) {
      togedamegesub(p_actwk, &g_mdRam.actwk[1]);
    }
  }
  actionsub(p_actwk);
}


void togedamegesub(sprite_status* p_actwk, sprite_status* p_playerwk) {
  if (BIT_1_IS_SET(p_playerwk->cddat2)) return;
  if (p_playerwk->actfree.player.invulnerability_timer != 0) return;
  if (p_playerwk->r_no >= 4) return; // unsigned
  p_playerwk->yposi -= p_playerwk->yspeed * 256;
  playdamageset(p_playerwk, p_actwk);
}


static void togekind(sprite_status* p_actwk) {
  togekindtbl[p_actwk->userflag1 / 2](p_actwk);
}


static sprite_status_handler togekindtbl[4] = {
  &toge_no,
  &toge_ymove,
  &toge_xmove,
  &toge_push
};


static void toge_no(sprite_status* p_actwk) {
}


static void toge_ymove(sprite_status* p_actwk) {
  toge_sub(p_actwk);
  short yposi = SPRITE_STATUS_SHORT(p_actwk, 52) / 256 + p_actwk->actfree.toge.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
}


static void toge_xmove(sprite_status* p_actwk) {
  toge_sub(p_actwk);
  short xposi = SPRITE_STATUS_SHORT(p_actwk, 52) / 256 + p_actwk->actfree.toge.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
}


static void toge_sub(sprite_status* p_actwk) {
  if (p_actwk->actfree.toge.move_countdown != 0) {
    --p_actwk->actfree.toge.move_countdown;
    if (p_actwk->actfree.toge.move_countdown != 0) return;
    if (!BIT_IS_SET(p_actwk->actflg, FLG_ONSCREEN)) return;
    soundset(82);
  }
  else if (p_actwk->actfree.toge.move_dir != 0) {
    bool gt_or_eq = p_actwk->actfree.toge.offset >= 0x800; // unsigned
    p_actwk->actfree.toge.offset -= 0x800;
    if (gt_or_eq) return;
    p_actwk->actfree.toge.offset = 0;
    p_actwk->actfree.toge.move_dir = 0;
    p_actwk->actfree.toge.move_countdown = 60;
  }
  else {
    p_actwk->actfree.toge.offset += 0x800;
    if (p_actwk->actfree.toge.offset < 0x2000) return; // unsigned
    p_actwk->actfree.toge.offset = 0x2000;
    p_actwk->actfree.toge.move_dir = 1;
    p_actwk->actfree.toge.move_countdown = 60;
  }
}


static void toge_push(sprite_status* p_actwk) {
  unsigned char cddat1 = p_actwk->cddat1 & 0x60;
  if (cddat1 == 0) return;
  toge_push__sub(p_actwk, LONG_HIGH(p_actwk->xposi), cddat1, 5, &g_mdRam.actwk[0], p_actwk->actfree.toge.plcddat1);
  toge_push__sub(p_actwk, LONG_HIGH(p_actwk->xposi), cddat1, 6, &g_mdRam.actwk[1], p_actwk->actfree.toge.pl2cddat1);
  p_actwk->actfree.toge.plcddat1 = g_mdRam.actwk[0].cddat1;
  p_actwk->actfree.toge.pl2cddat1 = g_mdRam.actwk[1].cddat1;
}


static void toge_push__sub(sprite_status* p_actwk, short xposi, unsigned char cddat1, unsigned char bit, sprite_status* p_playerwk, unsigned char plcddat1) {
  if (!BIT_IS_SET(cddat1, bit)) return;
  if (util__to_unsigned(xposi) < util__to_unsigned(LONG_HIGH(p_playerwk->xposi))) return;
  if (!BIT_5_IS_SET(plcddat1)) return;
  --p_actwk->actfree.toge.push_delay;
  if (p_actwk->actfree.toge.push_delay >= 0) return;
  p_actwk->actfree.toge.push_delay = 16;
  if (p_actwk->actfree.toge.push_distance == 0) return;
  --p_actwk->actfree.toge.push_distance;
  p_actwk->xposi += SHORT_TO_LONG_HIGH(1);
  p_playerwk->xposi += SHORT_TO_LONG_HIGH(1);
}


static void vstogekind(sprite_status* p_actwk) {
  vstogekindtbl[p_actwk->userflag1 / 2](p_actwk);
}


static sprite_status_handler vstogekindtbl[3] = {
  &toge_no,
  &vstoge_ymove,
  &vstoge_xmove
};


static void vstoge_ymove(sprite_status* p_actwk) {
  vstoge_sub(p_actwk);
  short yposi = p_actwk->actfree.toge.offset / 256 + p_actwk->actfree.toge.orig_yposi;
  util__assign_high(&p_actwk->yposi, yposi);
}


static void vstoge_xmove(sprite_status* p_actwk) {
  vstoge_sub(p_actwk);
  short xposi = p_actwk->actfree.toge.offset / 256 + p_actwk->actfree.toge.orig_xposi;
  util__assign_high(&p_actwk->xposi, xposi);
}


static void vstoge_sub(sprite_status* p_actwk) {
  if (p_actwk->actfree.toge.move_countdown != 0) {
    --p_actwk->actfree.toge.move_countdown;
    if (p_actwk->actfree.toge.move_countdown != 0) return;
    if (!BIT_IS_SET(p_actwk->actflg, FLG_ONSCREEN)) return;
    soundset(82);
  }
  else if (p_actwk->actfree.toge.move_dir != 0) {
    bool gt_or_eq = p_actwk->actfree.toge.offset >= 0x800; // unsigned
    p_actwk->actfree.toge.offset -= 0x800;
    if (gt_or_eq) return;
    p_actwk->actfree.toge.offset = 0;
    p_actwk->actfree.toge.move_dir = 0;
    p_actwk->actfree.toge.move_countdown = 60;
  }
  else {
    p_actwk->actfree.toge.offset += 0x800;
    if (p_actwk->actfree.toge.offset < 0x1800) return; // unsigned
    p_actwk->actfree.toge.offset = 0x1800;
    p_actwk->actfree.toge.move_dir = 1;
    p_actwk->actfree.toge.move_countdown = 60;
  }
}


signed char* togepat[8] = {
  togesp00,
  togesp01,
  togesp02,
  togesp03,
  togesp04,
  togesp05,
  togesp06,
  togesp07
};


static signed char togesp00[14] = {
    0,   2, -16,   7,   0,   0, -16,  -1, -16,   7,
    0,   0,   0,   0
};
static signed char togesp01[26] = {
    0,   4, -16,   7,   0,   0, -32,  -1, -16,   7,
    0,   0, -16,  -1, -16,   7,   0,   0,   0,   0,
  -16,   7,   0,   0,  16,   0
};
static signed char togesp02[38] = {
    0,   6, -16,   7,   0,   0, -48,  -1, -16, 7  ,
    0,   0, -32,  -1, -16,   7,   0,   0, -16,  -1,
  -16,   7,   0,   0,   0,   0, -16,   7,   0,   0,
   16,   0, -16,   7,   0,   0,  32,   0
};
static signed char togesp03[50] = {
    0,   8, -16,   7,   0,   0, -64,  -1, -16,   7,
    0,   0, -48,  -1, -16,   7,   0,   0, -32,  -1,
  -16,   7,   0,   0, -16,  -1, -16,   7,   0,   0,
    0,   0, -16,   7,   0,   0,  16,   0, -16,   7,
    0,   0,  32,   0, -16,   7,   0,   0,  48,   0
};
static signed char togesp04[14] = {
    0,   2, -16,  13,   0,   8, -16,  -1,   0,  13,
    0,   8, -16,  -1
};
static signed char togesp05[26] = {
    0,   4, -32,  13,   0,   8, -16,  -1, -16,  13,
    0,   8, -16,  -1,   0,  13,   0,   8, -16,  -1,
   16,  13,   0,   8, -16,  -1
};
static signed char togesp06[38] = {
    0,   6, -48,  13,   0,   8, -16,  -1, -32,  13,
    0,   8, -16,  -1, -16,  13,   0,   8, -16,  -1,
    0,  13,   0,   8, -16,  -1,  16,  13,   0,   8,
  -16,  -1,  32,  13,   0,   8, -16,  -1
};
static signed char togesp07[50] = {
    0,   8, -64,  13,   0,   8, -16,  -1, -48,  13,
    0,   8, -16,  -1, -32,  13,   0,   8, -16,  -1,
  -16,  13,   0,   8, -16,  -1,   0,  13,   0,   8,
  -16,  -1,  16,  13,   0,   8, -16,  -1,  32,  13,
    0,   8, -16,  -1,  48,  13,   0,   8, -16,  -1
};


signed char* vstogepat[8] = {
  vstogesp00,
  vstogesp01,
  vstogesp02,
  vstogesp03,
  vstogesp04,
  vstogesp05,
  vstogesp06,
  vstogesp07
};


static signed char vstogesp00[8] = {
    0,   1, -12,  10,  19,   0, -12,  -1
};
static signed char vstogesp01[14] = {
    0,   2, -12,  10,  19,   0, -24,  -1, -12,  10,
   19,   0,   0,   0
};
static signed char vstogesp02[20] = {
    0,   3, -12,  10,  19,   0, -36,  -1, -12,  10,
   19,   0, -12,  -1, -12,  10,  19,   0,  12,   0
};
static signed char vstogesp03[26] = {
    0,   4, -12,  10,  19,   0, -48,  -1, -12,  10,
   19,   0, -24,  -1, -12,  10,  19,   0,   0,   0,
  -12,  10,  19,   0,  24,   0
};
static signed char vstogesp04[8] = {
    0,   1, -12,  10,  19,   0, -12,  -1
};
static signed char vstogesp05[14] = {
    0,   2, -24,  10,  19,   0, -12,  -1,   0,  10,
   19,   0, -12,  -1
};
static signed char vstogesp06[20] = {
    0,   3, -36,  10,  19,   0, -12,  -1, -12,  10,
   19,   0, -12,  -1,  12,  10,  19,   0, -12,  -1
};
static signed char vstogesp07[26] = {
    0,   4, -48,  10,  19,   0, -12,  -1, -24,  10,
   19,   0, -12,  -1,   0,  10,  19,   0, -12,  -1,
   24,  10,  19,   0, -12,  -1
};
