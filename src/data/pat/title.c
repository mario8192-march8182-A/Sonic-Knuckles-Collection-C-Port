#include "../../../spritepattern.h"
static SKC_sprite_pattern titlesp00;
static SKC_sprite_pattern titlesp01;
static SKC_sprite_pattern titlesp02;
static SKC_sprite_pattern titlesp03;
static SKC_sprite_pattern titlesp04;
static SKC_sprite_pattern titlesp05;
static SKC_sprite_pattern titlesp06;
static SKC_sprite_pattern titlesp07;
static SKC_sprite_pattern titlesp08;
static SKC_sprite_pattern titlesp09;
static SKC_sprite_pattern titlesp10;
static SKC_sprite_pattern titlesp11;
static SKC_sprite_pattern titlesp12;
static SKC_sprite_pattern titlesp13;
static SKC_sprite_pattern titlesp14;
static SKC_sprite_pattern titlesp15;
static SKC_sprite_pattern titlesp16;
static SKC_sprite_pattern titlesp17;
static SKC_sprite_pattern titlesp18;
static SKC_sprite_pattern titlesp20;

SKC_sprite_pattern* titlepat[21] = {
  &titlesp00,
  &titlesp01,
  &titlesp02,
  &titlesp03,
  &titlesp04,
  &titlesp05,
  &titlesp06,
  &titlesp07,
  &titlesp08,
  &titlesp09,
  &titlesp10,
  &titlesp11,
  &titlesp12,
  &titlesp13,
  &titlesp14,
  &titlesp15,
  &titlesp16,
  &titlesp17,
  &titlesp18,
  &titlesp18,
  &titlesp20
};


static SKC_sprite_pattern titlesp00 = {
  0,
  {}
};
static SKC_sprite_pattern titlesp01 = {
  16,
  {
    {   88,  9, 0x8510, -24 },
    {   88,  9, 0x8516,   0 },
    { -112, 15, 0x8500, -32 },
    { -112, 15, 0x8500,   0 },
    {  -80, 15, 0x8500, -32 },
    {  -80, 15, 0x8500,   0 },
    {  -48, 15, 0x8500, -32 },
    {  -48, 15, 0x8500,   0 },
    {  -16, 15, 0x8500, -32 },
    {  -16, 15, 0x8500,   0 },
    {   16, 15, 0x8500, -32 },
    {   16, 15, 0x8500,   0 },
    {   48, 15, 0x8500, -32 },
    {   48, 15, 0x8500,   0 },
    {   80, 15, 0x8500, -32 },
    {   80, 15, 0x8500,   0 }
  }
};
static SKC_sprite_pattern titlesp02 = {
  2,
  {
    { 16,  9, 0x8537, -28 },
    {  0, 15, 0x853D, -11 }
  }
};
static SKC_sprite_pattern titlesp03 = {
  4,
  {
    { 0,  6, 0x8531, -36 },
    { 0, 10, 0x8528, -20 },
    { 0,  6, 0x8522,   4 },
    { 0,  6, 0x851C,  20 }
  }
};
static SKC_sprite_pattern titlesp04 = {
  11,
  {
    { 0, 6, 0x854D, -32 },
    { 0, 6, 0x8522, -16 },
    { 0, 6, 0x8559,   0 },
    { 0, 6, 0x851C,  16 },
    { 0, 2, 0x8562,  32 },
    { 0, 2, 0x855F,  48 },
    { 0, 6, 0x8565,  56 },
    { 0, 2, 0x8562,  72 },
    { 0, 6, 0x854D,  80 },
    { 0, 6, 0x8522,  96 },
    { 0, 6, 0x8553, 112 }
  }
};
static SKC_sprite_pattern titlesp05 = {
  8,
  {
    { 0,  6, 0x8559, -16 },
    { 0,  6, 0x856E,   0 },
    { 0,  6, 0x8553,  16 },
    { 0,  6, 0x8562,  32 },
    { 0, 10, 0x8528,  48 },
    { 0,  6, 0x854D,  72 },
    { 0,  2, 0x855F,  88 },
    { 0, 14, 0x8568,  96 }
  }
};
static SKC_sprite_pattern titlesp06 = {
  12,
  {
    { 0, 10, 0x8568, -72 },
    { 0,  6, 0x854D, -48 },
    { 0,  6, 0x8571, -32 },
    { 0,  6, 0x8553, -16 },
    { 0,  2, 0x8565,   0 },
    { 0,  6, 0x851C,   8 },
    { 0,  6, 0x855F,  32 },
    { 0,  6, 0x854D,  48 },
    { 0,  6, 0x8571,  64 },
    { 0,  6, 0x8559,  80 },
    { 0,  6, 0x851C,  96 },
    { 0,  6, 0x8522, 112 }
  }
};
static SKC_sprite_pattern titlesp07 = {
  12,
  {
    { 0,  6, 0x8553, -64 },
    { 0,  6, 0x854D, -48 },
    { 0,  6, 0x856B, -32 },
    { 0,  6, 0x8522, -16 },
    { 0,  2, 0x8565,   0 },
    { 0,  6, 0x8577,   8 },
    { 0,  6, 0x854D,  24 },
    { 0,  2, 0x8568,  40 },
    { 0,  6, 0x8522,  56 },
    { 0,  2, 0x8565,  72 },
    { 0, 14, 0x8559,  80 },
    { 0,  6, 0x8571, 112 }
  }
};
static SKC_sprite_pattern titlesp08 = {
  13,
  {
    { 0, 6, 0x8559, -72 },
    { 0, 2, 0x8568, -56 },
    { 0, 6, 0x8577, -48 },
    { 0, 2, 0x8565, -32 },
    { 0, 6, 0x8522, -24 },
    { 0, 6, 0x855F,  -8 },
    { 0, 6, 0x8553,  16 },
    { 0, 6, 0x854D,  32 },
    { 0, 6, 0x8571,  48 },
    { 0, 6, 0x8571,  64 },
    { 0, 6, 0x851C,  80 },
    { 0, 6, 0x856B,  96 },
    { 0, 6, 0x8577, 112 }
  }
};
static SKC_sprite_pattern titlesp09 = {
  6,
  {
    { 0, 2, 0x8559,  40 },
    { 0, 6, 0x8553,  48 },
    { 0, 6, 0x851C,  64 },
    { 0, 6, 0x8553,  80 },
    { 0, 6, 0x854D,  96 },
    { 0, 6, 0x855C, 112 }
  }
};
static SKC_sprite_pattern titlesp10 = {
  9,
  {
    { 0,  2, 0x8565, -32 },
    { 0,  6, 0x854D, -24 },
    { 0,  6, 0x856E,  -8 },
    { 0,  6, 0x8522,   8 },
    { 0, 14, 0x8559,  24 },
    { 0,  6, 0x8553,  64 },
    { 0,  6, 0x854D,  80 },
    { 0,  6, 0x8568,  96 },
    { 0,  6, 0x851C, 112 }
  }
};
static SKC_sprite_pattern titlesp11 = {
  10,
  {
    { 0, 10, 0x8559, -80 },
    { 0,  6, 0x856E, -56 },
    { 0,  6, 0x8568, -40 },
    { 0,  6, 0x854D, -24 },
    { 0,  6, 0x8562,  -8 },
    { 0, 10, 0x8528,   8 },
    { 0, 10, 0x8528,  32 },
    { 0, 10, 0x8559,  56 },
    { 0, 14, 0x854D,  88 },
    { 0,  2, 0x8556, 120 }
  }
};
static SKC_sprite_pattern titlesp12 = {
  10,
  {
    { 0,  6, 0x8565, -32 },
    { 0,  6, 0x854D, -16 },
    { 0,  6, 0x8522,   0 },
    { 0,  6, 0x8553,  16 },
    { 0, 10, 0x8528,  32 },
    { 0,  6, 0x855F,  56 },
    { 0, 10, 0x8528,  72 },
    { 0,  2, 0x855C,  96 },
    { 0,  2, 0x8559, 104 },
    { 0,  6, 0x8565, 112 }
  }
};
static SKC_sprite_pattern titlesp13 = {
  8,
  {
    { 0, 2, 0x8559,   0 },
    { 0, 6, 0x854D,   8 },
    { 0, 6, 0x8562,  24 },
    { 0, 6, 0x854D,  40 },
    { 0, 6, 0x855C,  64 },
    { 0, 6, 0x851C,  80 },
    { 0, 6, 0x851C,  96 },
    { 0, 6, 0x8553, 112 }
  }
};
static SKC_sprite_pattern titlesp14 = {
  11,
  {
    { 0,  6, 0x8565, -72 },
    { 0,  6, 0x8559, -56 },
    { 0,  6, 0x8577, -40 },
    { 0,  6, 0x8565, -16 },
    { 0,  6, 0x854D,   0 },
    { 0,  6, 0x8522,  16 },
    { 0,  6, 0x8553,  32 },
    { 0, 14, 0x856B,  48 },
    { 0,  6, 0x854D,  80 },
    { 0,  6, 0x855F,  96 },
    { 0,  6, 0x8577, 112 }
  }
};
static SKC_sprite_pattern titlesp15 = {
  8,
  {
    { 0, 6, 0x8553, -8 },
    { 0, 6, 0x851C,   8 },
    { 0, 6, 0x854D,  24 },
    { 0, 6, 0x8565,  40 },
    { 0, 6, 0x855F,  56 },
    { 0, 6, 0x851C,  80 },
    { 0, 6, 0x8559,  96 },
    { 0, 6, 0x8559, 112 }
  }
};
static SKC_sprite_pattern titlesp16 = {
  11,
  {
    { 0,  6, 0x856E, -80 },
    { 0,  6, 0x8559, -64 },
    { 0,  6, 0x851C, -48 },
    { 0,  6, 0x8553, -24 },
    { 0, 10, 0x8528,  -8 },
    { 0, 10, 0x8528,  16 },
    { 0, 10, 0x855F,  40 },
    { 0,  6, 0x8568,  64 },
    { 0,  6, 0x8553,  80 },
    { 0,  6, 0x854D,  96 },
    { 0,  6, 0x8574, 112 }
  }
};
static SKC_sprite_pattern titlesp17 = {
  11,
  {
    { 0, 10, 0x855F, -56 },
    { 0, 6, 0x8559, -32 },
    { 0, 6, 0x8559, -16 },
    { 0, 6, 0x851C, 0 },
    { 0, 6, 0x8522, 16 },
    { 0, 6, 0x856B, 40 },
    { 0, 6, 0x854D, 56 },
    { 0, 2, 0x8568, 72 },
    { 0, 6, 0x854D, 80 },
    { 0, 6, 0x8553, 96 },
    { 0, 6, 0x851C, 112 }
  }
};
static SKC_sprite_pattern titlesp18 = {
  5,
  {
    { 0, 6, 0x8553, 0 },
    { 0, 10, 0x8528, 16 },
    { 0, 6, 0x855F, 40 },
    { 0, 6, 0x8571, 56 },
    { 0, 6, 0x8565, 72 }
  }
};
static SKC_sprite_pattern titlesp20 = {
  5,
  {
    { 0, 6, 0x8565,  0 },
    { 0, 6, 0x856B, 16 },
    { 0, 6, 0x854D, 32 },
    { 0, 6, 0x8559, 48 },
    { 0, 6, 0x851C, 64 }
  }
};
