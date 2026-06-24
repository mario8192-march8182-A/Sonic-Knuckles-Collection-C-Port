#include "../../../spritepattern.h"
SKC_sprite_pattern tornado_pt00;
SKC_sprite_pattern tornado_pt01;
SKC_sprite_pattern tornado_pt02;
SKC_sprite_pattern tornado_pt03;
SKC_sprite_pattern tornado_pt04;
SKC_sprite_pattern tornado_pt05;
SKC_sprite_pattern tornado_pt06;
SKC_sprite_pattern tornado_pt07;
SKC_sprite_pattern tornado_pt08;
SKC_sprite_pattern tornado_pt09;
SKC_sprite_pattern tornado_pt10;
SKC_sprite_pattern emerald_pt00;
SKC_sprite_pattern emerald_pt01;
SKC_sprite_pattern emerald_pt02;
SKC_sprite_pattern emerald_pt03;
SKC_sprite_pattern emerald_pt04;
SKC_sprite_pattern emerald_pt05;
SKC_sprite_pattern emerald_pt06;
SKC_sprite_pattern shibuki_pt00;
SKC_sprite_pattern shibuki_pt01;
SKC_sprite_pattern shibuki_pt02;
SKC_sprite_pattern shibuki_pt03;
SKC_sprite_pattern shibuki_pt04;
SKC_sprite_pattern shibuki_pt05;

SKC_sprite_pattern* tornado_pt[11] = {
  &tornado_pt00,
  &tornado_pt01,
  &tornado_pt02,
  &tornado_pt03,
  &tornado_pt04,
  &tornado_pt05,
  &tornado_pt06,
  &tornado_pt07,
  &tornado_pt08,
  &tornado_pt09,
  &tornado_pt10
};
static SKC_sprite_pattern tornado_pt00 = {
  9,
  {
    { -32,  9, 0x0000, -60 },
    { -16, 14, 0x0006, -60 },
    { -16,  7, 0x0012, -28 },
    { -24, 15, 0x001A, -12 },
    {   8, 12, 0x002A, -12 },
    { -24, 12, 0x002E,  20 },
    { -16, 11, 0x0032,  20 },
    {  16,  5, 0x003E,  28 },
    {  -8,  2, 0x0042,  44 },
  }
};
static SKC_sprite_pattern tornado_pt01 = {
  1,
  {
    { -12, 2, 0x0045, -4 },
  }
};
static SKC_sprite_pattern tornado_pt02 = {
  1,
  {
    { -12, 2, 0x0048, -4 },
  }
};
static SKC_sprite_pattern tornado_pt03 = {
  1,
  {
    { -12, 2, 0x004B, -4 },
  }
};
static SKC_sprite_pattern tornado_pt04 = {
  1,
  {
    { -12, 2, 0x004E, -4 },
  }
};
static SKC_sprite_pattern tornado_pt05 = {
  3,
  {
    { -8, 13, 0x0051, -28 },
    { -8,  9, 0x0059,   4 },
    { -8, 13, 0x005F, -60 },
  }
};
static SKC_sprite_pattern tornado_pt06 = {
  3,
  {
    { -8, 13, 0x0051, -28 },
    { -8,  9, 0x0059,   4 },
    { -8,  5, 0x0067, -44 },
  }
};
static SKC_sprite_pattern tornado_pt07 = {
  5,
  {
    { -8, 13, 0x006B, -60 },
    { -8, 13, 0x086B,  28 },
    { -8,  9, 0x0073, -28 },
    { -8,  9, 0x006F,   4 },
    { -8,  1, 0x006F,  -4 },
  }
};
static SKC_sprite_pattern tornado_pt08 = {
  4,
  {
    { -8, 13, 0x0079, -48 },
    { -8, 13, 0x0879,  16 },
    { -8,  5, 0x007D, -16 },
    { -8,  5, 0x007D,   0 },
  }
};
static SKC_sprite_pattern tornado_pt09 = {
  3,
  {
    { -4, 12, 0x0081, -36 },
    { -4, 12, 0x0881,   4 },
    { -4,  0, 0x0082,  -4 },
  }
};
static SKC_sprite_pattern tornado_pt10 = {
  2,
  {
    { -4, 8, 0x0085, -24 },
    { -4, 8, 0x0885,   0 },
  }
};
SKC_sprite_pattern* emerald_pt[7] = {
  &emerald_pt00,
  &emerald_pt01,
  &emerald_pt02,
  &emerald_pt03,
  &emerald_pt04,
  &emerald_pt05,
  &emerald_pt06
};
static SKC_sprite_pattern emerald_pt00 = {
  1,
  {
    { -4, 0, 0x0000, -4 },
  }
};
static SKC_sprite_pattern emerald_pt01 = {
  1,
  {
    { -4, 0, 0x0001, -4 },
  }
};
static SKC_sprite_pattern emerald_pt02 = {
  1,
  {
    { -4, 0, 0x0002, -4 },
  }
};
static SKC_sprite_pattern emerald_pt03 = {
  1,
  {
    { -4, 0, 0x0003, -4 },
  }
};
static SKC_sprite_pattern emerald_pt04 = {
  1,
  {
    { -4, 0, 0x0004, -4 },
  }
};
static SKC_sprite_pattern emerald_pt05 = {
  1,
  {
    { -4, 0, 0x0005, -4 },
  }
};
static SKC_sprite_pattern emerald_pt06 = {
  1,
  {
    { -4, 0, 0x0006, -4 },
  }
};
SKC_sprite_pattern* shibuki_pt[6] = {
  &shibuki_pt00,
  &shibuki_pt01,
  &shibuki_pt02,
  &shibuki_pt03,
  &shibuki_pt04,
  &shibuki_pt05
};
static SKC_sprite_pattern shibuki_pt00 = {
  2,
  {
    { -64, 11, 0x0000, 8 },
    { -32, 15, 0x000C, 0 },
  }
};
static SKC_sprite_pattern shibuki_pt01 = {
  5,
  {
    { -96, 15, 0x001C, 19 },
    { -64, 11, 0x002C,  8 },
    { -64, 11, 0x0038, 32 },
    { -32, 15, 0x0044,  0 },
    { -32, 15, 0x0054, 32 },
  }
};
static SKC_sprite_pattern shibuki_pt02 = {
  5,
  {
    { -96, 15, 0x0064, 24 },
    { -64, 15, 0x0074,  8 },
    { -64, 11, 0x0084, 40 },
    { -32, 15, 0x0090,  0 },
    { -32, 15, 0x00A0, 32 },
  }
};
static SKC_sprite_pattern shibuki_pt03 = {
  5,
  {
    { -80, 13, 0x00B0, 24 },
    { -64, 15, 0x00B8,  8 },
    { -64, 11, 0x00C8, 40 },
    { -32, 15, 0x00D4,  0 },
    { -32, 15, 0x00E4, 32 },
  }
};
static SKC_sprite_pattern shibuki_pt04 = {
  4,
  {
    { -64, 15, 0x00F4,  0 },
    { -64, 11, 0x0104, 32 },
    { -32, 15, 0x0110,  0 },
    { -32, 15, 0x0120, 32 },
  }
};
static SKC_sprite_pattern shibuki_pt05 = {
  3,
  {
    { -48, 13, 0x0130, 16 },
    { -32, 15, 0x0138,  0 },
    { -32, 15, 0x0148, 32 },
  }
};
