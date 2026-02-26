#include "bgspr.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/fp16.h"
#include "../action.h"
#include "../constants.h"
static void bgsprinit(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern bgsprsp00;
static SKC_sprite_pattern bgsprsp01;
static SKC_sprite_pattern bgsprsp02;
static SKC_sprite_pattern bgsprsp03;
static SKC_sprite_pattern bgsprsp04;
static SKC_sprite_pattern bgsprsp06;
static SKC_sprite_pattern bgsprsp07;
static SKC_sprite_pattern bgsprsp08;
static SKC_sprite_pattern bgsprsp09;
static SKC_sprite_pattern bgsprsp10;
static SKC_sprite_pattern bgsprsp11;
static SKC_sprite_pattern bgsprsp12;
static SKC_sprite_pattern bgsprsp13;
static SKC_sprite_pattern bgsprsp14;
static SKC_sprite_pattern bgsprsp15;
static SKC_sprite_pattern bgsprsp16;
static SKC_sprite_pattern bgsprsp17;
static SKC_sprite_pattern bgsprsp18;
static SKC_sprite_pattern bgsprsp19;
static SKC_sprite_pattern bgsprsp20;
static SKC_sprite_pattern bgsprsp21;
static SKC_sprite_pattern bgsprsp22;
static SKC_sprite_pattern bgsprsp24;
static SKC_sprite_pattern bgsprsp25;
static SKC_sprite_pattern bgsprsp26;
static SKC_sprite_pattern bgsprsp27;
static SKC_sprite_pattern bgsprsp28;
static SKC_sprite_pattern bgsprsp29;
static SKC_sprite_pattern bgsprsp30;
static SKC_sprite_pattern bgsprsp31;
static SKC_sprite_pattern bgsprsp32;
static SKC_sprite_pattern bgsprsp33;
static SKC_sprite_pattern bgsprsp34;
static SKC_sprite_pattern bgsprsp35;
static SKC_sprite_pattern bgsprsp36;
static SKC_sprite_pattern bgsprsp37;
static SKC_sprite_pattern bgsprsp38;
static SKC_sprite_pattern bgsprsp39;
static SKC_sprite_pattern bgsprsp40;
static SKC_sprite_pattern bgsprsp41;
static SKC_sprite_pattern bgsprsp42;
static SKC_sprite_pattern bgsprsp43;
static SKC_sprite_pattern bgsprsp44;
static SKC_sprite_pattern bgsprsp46;
static SKC_sprite_pattern bgsprsp47;
static SKC_sprite_pattern bgsprsp48;
static SKC_sprite_pattern bgsprsp49;
static SKC_sprite_pattern bgsprsp50;
static void bgsprpinit(SKC_sprite_status* p_actwk);
static void bgsprpmove(SKC_sprite_status* p_actwk);
static signed char bgsprpchg0[7];
static signed char bgsprpchg1[6];
static signed char bgsprpchg2[4];
static signed char bgsprpchg3[5];
static signed char bgsprpchg4[6];
static signed char bgsprpchg5[6];
static signed char bgsprpchg6[6];
static signed char bgsprpchg7[7];
static SKC_sprite_pattern bgsprpsp00;
static SKC_sprite_pattern bgsprpsp01;
static SKC_sprite_pattern bgsprpsp02;
static SKC_sprite_pattern bgsprpsp03;
static SKC_sprite_pattern bgsprpsp04;
static SKC_sprite_pattern bgsprpsp05;
static SKC_sprite_pattern bgsprpsp06;
static SKC_sprite_pattern bgsprpsp07;
static SKC_sprite_pattern bgsprpsp08;
static SKC_sprite_pattern bgsprpsp09;
static SKC_sprite_pattern bgsprpsp10;
static SKC_sprite_pattern bgsprpsp11;
static SKC_sprite_pattern bgsprpsp12;
static SKC_sprite_pattern bgsprpsp13;
static SKC_sprite_pattern bgsprpsp14;
static SKC_sprite_pattern bgsprpsp15;
static SKC_sprite_pattern bgsprpsp16;
static SKC_sprite_pattern bgsprpsp17;
static SKC_sprite_pattern bgsprpsp18;
static SKC_sprite_pattern bgsprpsp19;
static SKC_sprite_pattern bgsprpsp20;
static SKC_sprite_pattern bgsprpsp21;
static SKC_sprite_pattern bgsprpsp22;
static SKC_sprite_pattern bgsprpsp23;
static SKC_sprite_pattern bgsprpsp24;
static SKC_sprite_pattern bgsprpsp25;
static SKC_sprite_pattern bgsprpsp26;
static SKC_sprite_pattern bgsprpsp27;
static SKC_sprite_pattern bgsprpsp28;
static SKC_sprite_pattern bgsprpsp29;
static void bgsprzinit(SKC_sprite_status* p_actwk);
static void bgsprzmove(SKC_sprite_status* p_actwk);
static void bgsprzmove1(SKC_sprite_status* p_actwk);
static void bgsprzmove2(SKC_sprite_status* p_actwk);
static void bgsprzmove3(SKC_sprite_status* p_actwk);
static void bgsprzmove4(SKC_sprite_status* p_actwk);
static void bgsprzmove5(SKC_sprite_status* p_actwk);
static void bgsprzmove6(SKC_sprite_status* p_actwk);
static SKC_sprite_pattern bgsprzsp00;
static SKC_sprite_pattern bgsprzsp01;

extern sonic3_ram g_ram;


void bgspr(SKC_sprite_status* p_actwk) {
  bgsprinit(p_actwk);
}


static void bgsprinit(SKC_sprite_status* p_actwk) {
  struct {
    unsigned short sproffset;
    unsigned short sprpri;
    unsigned char sprhs;
    unsigned char sprvs;
  }
  bgsprtbl[51] = {
    { 0x42E9, PRI_6, 12,  12 },
    { 0x42E9, PRI_6, 16,   8 },
    { 0x42E9, PRI_6,  8,   4 },
    { 0x4001, PRI_6,  8,   8 },
    { 0x6001, PRI_6,  8,  32 },
    { 0xC2E9, PRI_6, 12,  12 },
    { 0xC001, PRI_0, 64,  64 },
    { 0xC001, PRI_0, 64,  32 },
    { 0x4001, PRI_6, 64,  16 },
    { 0xC001, PRI_0, 64,  64 },
    { 0xC001, PRI_0, 64,  96 },
    { 0x4451, PRI_6, 16,  24 },
    { 0x4451, PRI_6, 16,  24 },
    { 0x4451, PRI_6, 16,  24 },
    { 0x4451, PRI_6, 16,  24 },
    { 0xC368, PRI_0,  8,  48 },
    { 0xC379, PRI_0, 48,  24 },
    { 0xC399, PRI_0, 12,  16 },
    { 0xC3A4, PRI_0, 32,  52 },
    { 0x4038, PRI_6,  4,  16 },
    { 0x440D, PRI_6,  8,   8 },
    { 0x2433, PRI_6, 16,  64 },
    { 0x2433, PRI_6, 16, 128 },
    { 0x2433, PRI_1, 16,  64 },
    { 0xC357, PRI_1,  4,  16 },
    { 0xC357, PRI_1,  4,  16 },
    { 0xC357, PRI_1, 16,   4 },
    { 0xE40E, PRI_1, 16,   8 },
    { 0xE40E, PRI_1, 16,   8 },
    { 0x441E, PRI_4, 16,   8 },
    { 0x0347, PRI_5,  8,   8 },
    { 0xC3A1, PRI_3, 16,   4 },
    { 0xC3A1, PRI_3, 32,   4 },
    { 0xC3A1, PRI_3, 48,   4 },
    { 0xC0D3, PRI_1, 16,  16 },
    { 0xA3A1, PRI_3,  4,  16 },
    { 0xA3A1, PRI_3,  4,  32 },
    { 0xA3A1, PRI_3,  4,  64 },
    { 0xA3A1, PRI_3,  4,  16 },
    { 0x4379, PRI_1,  8,  20 },
    { 0x4379, PRI_1, 24,  20 },
    { 0x4379, PRI_1, 40,  20 },
    { 0x4379, PRI_1, 56,  20 },
    { 0x2443, PRI_6,  4,  16 },
    { 0x2339, PRI_0, 64,   4 },
    { 0x2339, PRI_5, 64,   4 },
    { 0xC001, PRI_2, 16,   8 },
    { 0x03AF, PRI_0, 16,   4 },
    { 0x23FF, PRI_5,  8,  12 },
    { 0x23FF, PRI_5, 12,   8 },
    { 0x2385, PRI_1, 16,  36 }
  };

  p_actwk->patbase = bgsprpat;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->patno = p_actwk->u.obj.userflag;
  p_actwk->sproffset = bgsprtbl[p_actwk->u.obj.userflag].sproffset;
  p_actwk->sprpri = bgsprtbl[p_actwk->u.obj.userflag].sprpri;
  p_actwk->sprhs = bgsprtbl[p_actwk->u.obj.userflag].sprhs;
  p_actwk->sprvs = bgsprtbl[p_actwk->u.obj.userflag].sprvs;
  p_actwk->r_ptr = &bgsprmove;
  bgsprmove(p_actwk);
}


void bgsprmove(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


SKC_sprite_pattern* bgsprpat[51] = {
  &bgsprsp00,
  &bgsprsp01,
  &bgsprsp02,
  &bgsprsp03,
  &bgsprsp04,
  &bgsprsp00,
  &bgsprsp06,
  &bgsprsp07,
  &bgsprsp08,
  &bgsprsp09,
  &bgsprsp10,
  &bgsprsp11,
  &bgsprsp12,
  &bgsprsp13,
  &bgsprsp14,
  &bgsprsp15,
  &bgsprsp16,
  &bgsprsp17,
  &bgsprsp18,
  &bgsprsp19,
  &bgsprsp20,
  &bgsprsp21,
  &bgsprsp22,
  &bgsprsp21,
  &bgsprsp24,
  &bgsprsp25,
  &bgsprsp26,
  &bgsprsp27,
  &bgsprsp28,
  &bgsprsp29,
  &bgsprsp30,
  &bgsprsp31,
  &bgsprsp32,
  &bgsprsp33,
  &bgsprsp34,
  &bgsprsp35,
  &bgsprsp36,
  &bgsprsp37,
  &bgsprsp38,
  &bgsprsp39,
  &bgsprsp40,
  &bgsprsp41,
  &bgsprsp42,
  &bgsprsp43,
  &bgsprsp44,
  &bgsprsp44,
  &bgsprsp46,
  &bgsprsp47,
  &bgsprsp48,
  &bgsprsp49,
  &bgsprsp50
};


static SKC_sprite_pattern bgsprsp00 = {
  2,
  {
    { -12, 5, 0x0126, -12 },
    {   4, 8, 0x012A, -12 }
  }
};
static SKC_sprite_pattern bgsprsp01 = {
  1,
  {
    { -8, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern bgsprsp02 = {
  1,
  {
    { -4, 4, 0x0008, -8 }
  }
};
static SKC_sprite_pattern bgsprsp03 = {
  1,
  {
    { -8, 5, 0x0026, -8 }
  }
};
static SKC_sprite_pattern bgsprsp04 = {
  2,
  {
    { -32, 7, 0x003A, -8 },
    { 0, 7, 0x0042, -8 }
  }
};
static SKC_sprite_pattern bgsprsp06 = {
  16,
  {
    { -64, 15, 0x0050, -64 },
    { -64, 15, 0x0050, -32 },
    { -64, 15, 0x0050,   0 },
    { -64, 15, 0x0050,  32 },
    { -32, 15, 0x0050, -64 },
    { -32, 15, 0x0050, -32 },
    { -32, 15, 0x0050,   0 },
    { -32, 15, 0x0050,  32 },
    {   0, 15, 0x0050, -64 },
    {   0, 15, 0x0050, -32 },
    {   0, 15, 0x0050,   0 },
    {   0, 15, 0x0050,  32 },
    {  32, 15, 0x0050, -64 },
    {  32, 15, 0x0050, -32 },
    {  32, 15, 0x0050,   0 },
    {  32, 15, 0x0050,  32 }
  }
};
static SKC_sprite_pattern bgsprsp07 = {
  8,
  {
    { -32, 15, 0x0050, -64 },
    { -32, 15, 0x0050, -32 },
    { -32, 15, 0x0050,   0 },
    { -32, 15, 0x0050,  32 },
    {   0, 15, 0x0050, -64 },
    {   0, 15, 0x0050, -32 },
    {   0, 15, 0x0050,   0 },
    {   0, 15, 0x0050,  32 }
  }
};
static SKC_sprite_pattern bgsprsp08 = {
  4,
  {
    { -16, 15, 0x0050, -64 },
    { -16, 15, 0x0050, -32 },
    { -16, 15, 0x0050,   0 },
    { -16, 15, 0x0050,  32 }
  }
};
static SKC_sprite_pattern bgsprsp09 = {
  9,
  {
    { -64, 15, 0x0050,  32 },
    { -32, 15, 0x0050,   0 },
    { -32, 15, 0x0050,  32 },
    {   0, 15, 0x0050, -32 },
    {   0, 15, 0x0050,   0 },
    {   0, 15, 0x0050,  32 },
    {  32, 15, 0x0050, -64 },
    {  32, 15, 0x0050, -32 },
    {  32, 15, 0x0050,   0 }
  }
};
static SKC_sprite_pattern bgsprsp10 = {
  12,
  {
    { -96, 15, 0x0050, -64 },
    { -64, 15, 0x0050, -64 },
    { -64, 15, 0x0050, -32 },
    { -32, 15, 0x0050, -64 },
    { -32, 15, 0x0050, -32 },
    { -32, 15, 0x0050,   0 },
    {   0, 15, 0x0050, -32 },
    {   0, 15, 0x0050,   0 },
    {   0, 15, 0x0050,  32 },
    {  32, 15, 0x0050,   0 },
    {  32, 15, 0x0050,  32 },
    {  64, 15, 0x0050,  32 }
  }
};
static SKC_sprite_pattern bgsprsp11 = {
  3,
  {
    { -16, 14, 0x0003, -16 },
    { -24,  0, 0x0000,  -4 },
    {   8,  1, 0x0001,  -4 }
  }
};
static SKC_sprite_pattern bgsprsp12 = {
  3,
  {
    { -16, 14, 0x0803, -16 },
    { -24,  0, 0x0000,  -4 },
    {   8,  1, 0x0001,  -4 }
  }
};
static SKC_sprite_pattern bgsprsp13 = {
  3,
  {
    { -20, 11, 0x000F, -12 },
    { -24,  0, 0x0000,  -4 },
    {   8,  1, 0x0001,  -4 }
  }
};
static SKC_sprite_pattern bgsprsp14 = {
  3,
  {
    { -20, 11, 0x001B, -12 },
    { -24,  0, 0x0000,  -4 },
    {   8,  1, 0x0001,  -4 }
  }
};
static SKC_sprite_pattern bgsprsp15 = {
  4,
  {
    { -48, 5, 0x0000, -8 },
    { -32, 3, 0x0004, -8 },
    {   0, 2, 0x0008, -8 },
    {  24, 6, 0x000B, -8 }
  }
};
static SKC_sprite_pattern bgsprsp16 = {
  6,
  {
    { -24,  9, 0x0000, -48 },
    {  -8, 12, 0x0006, -48 },
    {   0, 12, 0x000A, -40 },
    {   8, 13, 0x000E, -40 },
    {   8,  9, 0x0016,  -8 },
    {  16, 12, 0x001C,  16 }
  }
};
static SKC_sprite_pattern bgsprsp17 = {
  2,
  {
    { -16,  4, 0x0000,  -4 },
    {  -8, 10, 0x0002, -12 }
  }
};
static SKC_sprite_pattern bgsprsp18 = {
  8,
  {
    { -52, 7, 0x0000, -32 },
    { -20, 6, 0x0008, -32 },
    { -36, 7, 0x0000, -16 },
    {  -4, 6, 0x0008, -16 },
    { -20, 7, 0x0000,   0 },
    {  12, 6, 0x0008,   0 },
    {  -4, 7, 0x0000,  16 },
    {  28, 6, 0x0008,  16 }
  }
};
static SKC_sprite_pattern bgsprsp19 = {
  1,
  {
    { -16, 3, 0x0000, -4 }
  }
};
static SKC_sprite_pattern bgsprsp20 = {
  1,
  {
    { -8, 5, 0x0022, -8 }
  }
};
static SKC_sprite_pattern bgsprsp21 = {
  4,
  {
    { -64, 15, 0x0009, -16 },
    { -32, 15, 0x0809, -16 },
    {   0, 15, 0x0009, -16 },
    {  32, 15, 0x0809, -16 }
  }
};
static SKC_sprite_pattern bgsprsp22 = {
  8,
  {
    { -128, 15, 0x0009, -16 },
    {  -96, 15, 0x0809, -16 },
    {  -64, 15, 0x0009, -16 },
    {  -32, 15, 0x0809, -16 },
    {    0, 15, 0x0009, -16 },
    {   32, 15, 0x0809, -16 },
    {   64, 15, 0x0009, -16 },
    {   96, 15, 0x0809, -16 }
  }
};
static SKC_sprite_pattern bgsprsp24 = {
  1,
  {
    { -16, 3, 0x0004, -4 }
  }
};
static SKC_sprite_pattern bgsprsp25 = {
  1,
  {
    { -16, 3, 0x0008, -4 }
  }
};
static SKC_sprite_pattern bgsprsp26 = {
  1,
  {
    { -4, 12, 0x0000, -16 }
  }
};
static SKC_sprite_pattern bgsprsp27 = {
  1,
  {
    { -8, 13, 0x0000, -16 }
  }
};
static SKC_sprite_pattern bgsprsp28 = {
  1,
  {
    { -8, 13, 0x0008, -16 }
  }
};
static SKC_sprite_pattern bgsprsp29 = {
  2,
  {
    { -8, 1, 0x0000, -16 },
    { -8, 1, 0x0800,   8 }
  }
};
static SKC_sprite_pattern bgsprsp30 = {
  1,
  {
    { -8, 5, 0x0000, -8 }
  }
};
static SKC_sprite_pattern bgsprsp31 = {
  1,
  {
    { -4, 12, 0x108B, -16 }
  }
};
static SKC_sprite_pattern bgsprsp32 = {
  2,
  {
    { -4, 12, 0x108B, -32 },
    { -4, 12, 0x108B,   0 }
  }
};
static SKC_sprite_pattern bgsprsp33 = {
  3,
  {
    { -4, 12, 0x108B, -48 },
    { -4, 12, 0x108B, -16 },
    { -4, 12, 0x108B,  16 }
  }
};
static SKC_sprite_pattern bgsprsp34 = {
  1,
  {
    { -16, 15, 0x1071, -16 }
  }
};
static SKC_sprite_pattern bgsprsp35 = {
  1,
  {
    { -16, 3, 0x008F, -4 }
  }
};
static SKC_sprite_pattern bgsprsp36 = {
  2,
  {
    { -32, 3, 0x0091, -4 },
    {   0, 3, 0x0091, -4 }
  }
};
static SKC_sprite_pattern bgsprsp37 = {
  4,
  {
    { -64, 3, 0x0091, -4 },
    { -32, 3, 0x0091, -4 },
    {   0, 3, 0x0091, -4 },
    {  32, 3, 0x0091, -4 }
  }
};
static SKC_sprite_pattern bgsprsp38 = {
  1,
  {
    { -16, 3, 0x0093, -4 }
  }
};
static SKC_sprite_pattern bgsprsp39 = {
  2,
  {
    { -20, 5, 0x0000, -8 },
    {  -4, 6, 0x0004, -8 }
  }
};
static SKC_sprite_pattern bgsprsp40 = {
  4,
  {
    { -20, 5, 0x0000, -24 },
    {  -4, 6, 0x0004, -24 },
    { -20, 5, 0x0000,   8 },
    {  -4, 6, 0x0004,   8 }
  }
};
static SKC_sprite_pattern bgsprsp41 = {
  6,
  {
    { -20, 5, 0x0000, -40 },
    {  -4, 6, 0x0004, -40 },
    { -20, 5, 0x0000,  -8 },
    {  -4, 6, 0x0004,  -8 },
    { -20, 5, 0x0000,  24 },
    {  -4, 6, 0x0004,  24 }
  }
};
static SKC_sprite_pattern bgsprsp42 = {
  8,
  {
    { -20, 5, 0x0000, -56 },
    {  -4, 6, 0x0004, -56 },
    { -20, 5, 0x0000, -24 },
    {  -4, 6, 0x0004, -24 },
    { -20, 5, 0x0000,   8 },
    {  -4, 6, 0x0004,   8 },
    { -20, 5, 0x0000,  40 },
    {  -4, 6, 0x0004,  40 }
  }
};
static SKC_sprite_pattern bgsprsp43 = {
  1,
  {
    { -16, 3, 0x0000, -4 }
  }
};
static SKC_sprite_pattern bgsprsp44 = {
  4,
  {
    { -4, 12, 0x001E, -64 },
    { -4, 12, 0x001E, -32 },
    { -4, 12, 0x001E, 0 },
    { -4, 12, 0x001E, 32 }
  }
};
static SKC_sprite_pattern bgsprsp46 = {
  1,
  {
    { -8, 13, 0x0020, -16 }
  }
};
static SKC_sprite_pattern bgsprsp47 = {
  1,
  {
    { 0, 12, 0x0000, -16 }
  }
};
static SKC_sprite_pattern bgsprsp48 = {
  2,
  {
    { -12, 4, 0x0000, -8 },
    {  -4, 1, 0x0002, -8 }
  }
};
static SKC_sprite_pattern bgsprsp49 = {
  2,
  {
    { -8, 8, 0x0004, -12 },
    {  0, 0, 0x0007, -12 }
  }
};
static SKC_sprite_pattern bgsprsp50 = {
  4,
  {
    { -36,  6, 0x0041, -16 },
    { -36,  6, 0x0841,   0 },
    { -12, 10, 0x0047,  -8 },
    {  12, 10, 0x0047,  -8 }
  }
};


void bgsprp(SKC_sprite_status* p_actwk) {
  bgsprpinit(p_actwk);
}


static void bgsprpinit(SKC_sprite_status* p_actwk) {
  struct {
    unsigned short sproffset;
    unsigned short sprpri;
    unsigned char sprhs;
    unsigned char sprvs;
  }
  bgsprptbl[8] = {
    { 0x62E9, PRI_6, 8, 12 },
    { 0x62E9, PRI_6, 8, 12 },
    { 0xC0D3, PRI_4, 16, 4 },
    { 0x240D, PRI_6, 16, 4 },
    { 0x440F, PRI_6,  4, 4 },
    { 0x440F, PRI_6, 20, 4 },
    { 0x440F, PRI_6, 52, 4 },
    { 0x440F, PRI_6, 84, 4 }
  };

  p_actwk->patbase = bgsprppat;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->mstno = p_actwk->u.obj.userflag;
  p_actwk->sproffset = bgsprptbl[p_actwk->u.obj.userflag].sproffset;
  p_actwk->sprpri = bgsprptbl[p_actwk->u.obj.userflag].sprpri;
  p_actwk->sprhs = bgsprptbl[p_actwk->u.obj.userflag].sprhs;
  p_actwk->sprvs = bgsprptbl[p_actwk->u.obj.userflag].sprvs;
  p_actwk->r_ptr = &bgsprpmove;
  bgsprpmove(p_actwk);
}


static void bgsprpmove(SKC_sprite_status* p_actwk) {
  patchg(p_actwk, bgsprpchg);
  frameoutchk(p_actwk);
}


signed char* bgsprpchg[8] = {
  bgsprpchg0,
  bgsprpchg1,
  bgsprpchg2,
  bgsprpchg3,
  bgsprpchg4,
  bgsprpchg5,
  bgsprpchg6,
  bgsprpchg7
};


static signed char bgsprpchg0[7] = { 3, 0, 1, 2, 3, 4, -1 };
static signed char bgsprpchg1[6] = { 3, 5, 6, 7, 8, -1 };
static signed char bgsprpchg2[4] = { 7, 9, 10, -1 };
static signed char bgsprpchg3[5] = { 4, 11, 12, 13, -1 };
static signed char bgsprpchg4[6] = { 7, 14, 15, 16, 17, -1 };
static signed char bgsprpchg5[6] = { 7, 18, 19, 20, 21, -1 };
static signed char bgsprpchg6[6] = { 7, 22, 23, 24, 25, -1 };
static signed char bgsprpchg7[7] = { 7, 26, 27, 28, 29, -1, -112 };


SKC_sprite_pattern* bgsprppat[30] = {
  &bgsprpsp00,
  &bgsprpsp01,
  &bgsprpsp02,
  &bgsprpsp03,
  &bgsprpsp04,
  &bgsprpsp05,
  &bgsprpsp06,
  &bgsprpsp07,
  &bgsprpsp08,
  &bgsprpsp09,
  &bgsprpsp10,
  &bgsprpsp11,
  &bgsprpsp12,
  &bgsprpsp13,
  &bgsprpsp14,
  &bgsprpsp15,
  &bgsprpsp16,
  &bgsprpsp17,
  &bgsprpsp18,
  &bgsprpsp19,
  &bgsprpsp20,
  &bgsprpsp21,
  &bgsprpsp22,
  &bgsprpsp23,
  &bgsprpsp24,
  &bgsprpsp25,
  &bgsprpsp26,
  &bgsprpsp27,
  &bgsprpsp28,
  &bgsprpsp29
};


static SKC_sprite_pattern bgsprpsp00 = {
  1,
  {
    { -12, 6, 0x00EA, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp01 = {
  1,
  {
    { -12, 6, 0x00F0, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp02 = {
  1,
  {
    { -12, 6, 0x00F6, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp03 = {
  1,
  {
    { -12, 6, 0x00FC, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp04 = {
  1,
  {
    { -12, 6, 0x08F0, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp05 = {
  1,
  {
    { -16, 7, 0x0102, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp06 = {
  1,
  {
    { -16, 7, 0x010A, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp07 = {
  1,
  {
    { -16, 7, 0x0112, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp08 = {
  1,
  {
    { -16, 7, 0x011A, -8 }
  }
};
static SKC_sprite_pattern bgsprpsp09 = {
  2,
  {
    { -4, 4, 0x0068, -16 },
    { -4, 4, 0x0068, 0 }
  }
};
static SKC_sprite_pattern bgsprpsp10 = {
  2,
  {
    { -4, 4, 0x0868, -16 },
    { -4, 4, 0x0868,   0 }
  }
};
static SKC_sprite_pattern bgsprpsp11 = {
  2,
  {
    { -16, 7, 0x0037, -16 },
    { -16, 7, 0x003F,   0 }
  }
};
static SKC_sprite_pattern bgsprpsp12 = {
  1,
  {
    { -16, 15, 0x0047, -16 }
  }
};
static SKC_sprite_pattern bgsprpsp13 = {
  1,
  {
    { -16, 15, 0x0847, -16 }
  }
};
static SKC_sprite_pattern bgsprpsp14 = {
  1,
  {
    { -4, 0, 0x0000, -4 }
  }
};
static SKC_sprite_pattern bgsprpsp15 = {
  1,
  {
    { -4, 0, 0x0001, -4 }
  }
};
static SKC_sprite_pattern bgsprpsp16 = {
  1,
  {
    { -4, 0, 0x0801, -4 }
  }
};
static SKC_sprite_pattern bgsprpsp17 = {
  1,
  {
    { -4, 0, 0x0800, -4 }
  }
};
static SKC_sprite_pattern bgsprpsp18 = {
  2,
  {
    { -4, 0, 0x0000, -20 },
    { -4, 0, 0x0000,  12 }
  }
};
static SKC_sprite_pattern bgsprpsp19 = {
  2,
  {
    { -4, 0, 0x0001, -20 },
    { -4, 0, 0x0001,  12 }
  }
};
static SKC_sprite_pattern bgsprpsp20 = {
  2,
  {
    { -4, 0, 0x0801, -20 },
    { -4, 0, 0x0801,  12 }
  }
};
static SKC_sprite_pattern bgsprpsp21 = {
  2,
  {
    { -4, 0, 0x0800, -20 },
    { -4, 0, 0x0800,  12 }
  }
};
static SKC_sprite_pattern bgsprpsp22 = {
  4,
  {
    { -4, 0, 0x0000, -52 },
    { -4, 0, 0x0000, -20 },
    { -4, 0, 0x0000,  12 },
    { -4, 0, 0x0000,  44 }
  }
};
static SKC_sprite_pattern bgsprpsp23 = {
  4,
  {
    { -4, 0, 0x0001, -52 },
    { -4, 0, 0x0001, -20 },
    { -4, 0, 0x0001,  12 },
    { -4, 0, 0x0001,  44 }
  }
};
static SKC_sprite_pattern bgsprpsp24 = {
  4,
  {
    { -4, 0, 0x0801, -52 },
    { -4, 0, 0x0801, -20 },
    { -4, 0, 0x0801,  12 },
    { -4, 0, 0x0801,  44 }
  }
};
static SKC_sprite_pattern bgsprpsp25 = {
  4,
  {
    { -4, 0, 0x0800, -52 },
    { -4, 0, 0x0800, -20 },
    { -4, 0, 0x0800,  12 },
    { -4, 0, 0x0800,  44 }
  }
};
static SKC_sprite_pattern bgsprpsp26 = {
  6,
  {
    { -4, 0, 0x0000, -84 },
    { -4, 0, 0x0000, -52 },
    { -4, 0, 0x0000, -20 },
    { -4, 0, 0x0000,  12 },
    { -4, 0, 0x0000,  44 },
    { -4, 0, 0x0000,  76 }
  }
};
static SKC_sprite_pattern bgsprpsp27 = {
  6,
  {
    { -4, 0, 0x0001, -84 },
    { -4, 0, 0x0001, -52 },
    { -4, 0, 0x0001, -20 },
    { -4, 0, 0x0001,  12 },
    { -4, 0, 0x0001,  44 },
    { -4, 0, 0x0001,  76 }
  }
};
static SKC_sprite_pattern bgsprpsp28 = {
  6,
  {
    { -4, 0, 0x0801, -84 },
    { -4, 0, 0x0801, -52 },
    { -4, 0, 0x0801, -20 },
    { -4, 0, 0x0801,  12 },
    { -4, 0, 0x0801,  44 },
    { -4, 0, 0x0801,  76 }
  }
};
static SKC_sprite_pattern bgsprpsp29 = {
  6,
  {
    { -4, 0, 0x0800, -84 },
    { -4, 0, 0x0800, -52 },
    { -4, 0, 0x0800, -20 },
    { -4, 0, 0x0800,  12 },
    { -4, 0, 0x0800,  44 },
    { -4, 0, 0x0800,  76 }
  }
};


void bgsprz(SKC_sprite_status* p_actwk) {
  bgsprzinit(p_actwk);
}


static void bgsprzinit(SKC_sprite_status* p_actwk) {
  struct {
    unsigned short sproffset;
    unsigned short sprpri;
    unsigned char sprhs;
    unsigned char sprvs;
  }
  bgsprztbl[2] = {
    { 0xC333, PRI_0, 32, 48 },
    { 0xC333, PRI_0, 32, 60 }
  };
  SKC_sprite_status_handler bgsprzadrtbl[7] = {
    &bgsprzmove,
    &bgsprzmove1,
    &bgsprzmove2,
    &bgsprzmove3,
    &bgsprzmove4,
    &bgsprzmove5,
    &bgsprzmove6
  };

  p_actwk->patbase = bgsprzpat;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->u.obj.actfree.bgsprz.xposi_init = fp16_get_integer(p_actwk->xposi);
  p_actwk->u.obj.actfree.bgsprz.yposi_init = fp16_get_integer(p_actwk->yposi);
  p_actwk->patno = p_actwk->u.obj.userflag & 0x0F;
  p_actwk->sproffset = bgsprztbl[p_actwk->u.obj.userflag & 0x0F].sproffset;
  p_actwk->sprpri = bgsprztbl[p_actwk->u.obj.userflag & 0x0F].sprpri;
  p_actwk->sprhs = bgsprztbl[p_actwk->u.obj.userflag & 0x0F].sprhs;
  p_actwk->sprvs = bgsprztbl[p_actwk->u.obj.userflag & 0x0F].sprvs;
  p_actwk->r_ptr = bgsprzadrtbl[p_actwk->u.obj.userflag >> 4 & 0x0F];
}


static void bgsprzmove(SKC_sprite_status* p_actwk) {
  frameoutchk(p_actwk);
}


static void bgsprzmove1(SKC_sprite_status* p_actwk) {
  short xposi = (p_actwk->u.obj.actfree.bgsprz.xposi_init - 160 - (short)(g_ram.scra_h_posit >> 16)) / 16;
  xposi += p_actwk->u.obj.actfree.bgsprz.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (p_actwk->u.obj.actfree.bgsprz.yposi_init - 112 - (short)(g_ram.scra_v_posit >> 16)) / 16;
  yposi += p_actwk->u.obj.actfree.bgsprz.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.bgsprz.xposi_init);
}


static void bgsprzmove2(SKC_sprite_status* p_actwk) {
  short xposi = (p_actwk->u.obj.actfree.bgsprz.xposi_init - 160 - (short)(g_ram.scra_h_posit >> 16)) / 8;
  xposi += p_actwk->u.obj.actfree.bgsprz.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (p_actwk->u.obj.actfree.bgsprz.yposi_init - 112 - (short)(g_ram.scra_v_posit >> 16)) / 8;
  yposi += p_actwk->u.obj.actfree.bgsprz.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.bgsprz.xposi_init);
}


static void bgsprzmove3(SKC_sprite_status* p_actwk) {
  short xposi = (p_actwk->u.obj.actfree.bgsprz.xposi_init - 160 - (short)(g_ram.scra_h_posit >> 16)) / 4;
  xposi += p_actwk->u.obj.actfree.bgsprz.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (p_actwk->u.obj.actfree.bgsprz.yposi_init - 112 - (short)(g_ram.scra_v_posit >> 16)) / 4;
  yposi += p_actwk->u.obj.actfree.bgsprz.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.bgsprz.xposi_init);
}


static void bgsprzmove4(SKC_sprite_status* p_actwk) {
  short xposi = (p_actwk->u.obj.actfree.bgsprz.xposi_init - 160 - (short)(g_ram.scra_h_posit >> 16)) / 2;
  xposi += p_actwk->u.obj.actfree.bgsprz.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = (p_actwk->u.obj.actfree.bgsprz.yposi_init - 112 - (short)(g_ram.scra_v_posit >> 16)) / 2;
  yposi += p_actwk->u.obj.actfree.bgsprz.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.bgsprz.xposi_init);
}


static void bgsprzmove5(SKC_sprite_status* p_actwk) {
  short xposi = p_actwk->u.obj.actfree.bgsprz.xposi_init - 160 - (short)(g_ram.scra_h_posit >> 16);
  xposi += p_actwk->u.obj.actfree.bgsprz.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = p_actwk->u.obj.actfree.bgsprz.yposi_init - 112 - (short)(g_ram.scra_v_posit >> 16);
  yposi += p_actwk->u.obj.actfree.bgsprz.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.bgsprz.xposi_init);
}


static void bgsprzmove6(SKC_sprite_status* p_actwk) {
  short xposi = (p_actwk->u.obj.actfree.bgsprz.xposi_init - 160 - (short)(g_ram.scra_h_posit >> 16)) * 2;
  xposi += p_actwk->u.obj.actfree.bgsprz.xposi_init;
  fp16_set_integer(&p_actwk->xposi, xposi);
  short yposi = p_actwk->u.obj.actfree.bgsprz.yposi_init - 112 - (short)(g_ram.scra_v_posit >> 16);
  yposi += p_actwk->u.obj.actfree.bgsprz.yposi_init;
  fp16_set_integer(&p_actwk->yposi, yposi);
  frameoutchk2(p_actwk, p_actwk->u.obj.actfree.bgsprz.xposi_init);
}


SKC_sprite_pattern* bgsprzpat[2] = {
  &bgsprzsp00,
  &bgsprzsp01
};


static SKC_sprite_pattern bgsprzsp00 = {
  8,
  {
    { -48, 14, 0x0064, -32 },
    { -24, 15, 0x0070, -32 },
    {   8,  9, 0x0080, -24 },
    {  24,  2, 0x0086,  -8 },
    { -24,  4, 0x0089,  16 },
    { -16, 13, 0x008B,   0 },
    {   0,  9, 0x0093,   0 },
    {  16,  2, 0x0099,   0 }
  }
};
static SKC_sprite_pattern bgsprzsp01 = {
  8,
  {
    { -60, 14, 0x0864,   0 },
    { -36, 15, 0x0870,   0 },
    {  -4,  9, 0x0880,   0 },
    {  12,  2, 0x0886,   0 },
    { -36, 14, 0x0064, -32 },
    { -12, 15, 0x0070, -32 },
    {  20,  9, 0x0080, -24 },
    {  36,  2, 0x0086,  -8 }
  }
};
