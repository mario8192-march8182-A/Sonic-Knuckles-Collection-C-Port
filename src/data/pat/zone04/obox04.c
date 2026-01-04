#include "../../../spritepattern.h"
static SKC_sprite_pattern obox04sp00;
static SKC_sprite_pattern obox04sp01;
static SKC_sprite_pattern obox04sp02;
static SKC_sprite_pattern obox04sp03;
static SKC_sprite_pattern obox04sp04;
static SKC_sprite_pattern obox04sp05;

SKC_sprite_pattern* obox04pat[13] = {
  &obox04sp00,
  &obox04sp01,
  &obox04sp02,
  &obox04sp03,
  &obox04sp04,
  &obox04sp05,
  &obox04sp05,
  &obox04sp05,
  &obox04sp05,
  &obox04sp05,
  &obox04sp10,
  &obox04sp11,
  &obox04sp12
};
static SKC_sprite_pattern obox04sp00 = {
  10,
  {
    { -32, 13, 0x0025, -32 },
    { -32, 13, 0x0825,   0 },
    { -16,  2, 0x002D,  -8 },
    { -16,  2, 0x082D,   0 },
    { -16,  6, 0x0030, -24 },
    { -16,  6, 0x0830,   8 },
    { -16,  2, 0x0036, -32 },
    { -16,  2, 0x0836,  24 },
    {   8, 14, 0x0019, -32 },
    {   8, 14, 0x0819,   0 }
  }
};
static SKC_sprite_pattern obox04sp01 = {
  8,
  {
    { -32, 13, 0x035D, -32 },
    { -16,  1, 0x0365, -16 },
    {   0, 12, 0x0367, -32 },
    { -32, 13, 0x0B5D,   0 },
    { -16,  1, 0x0B65,   8 },
    {   0, 12, 0x0B67,   0 },
    {   8, 14, 0x0019, -32 },
    {   8, 14, 0x0819,   0 }
  }
};
static SKC_sprite_pattern obox04sp02 = {
  1,
  {
    { -8, 5, 0x036B, -8 }
  }
};
static SKC_sprite_pattern obox04sp03 = {
  1,
  {
    { -8, 5, 0x036F, -8 }
  }
};
static SKC_sprite_pattern obox04sp04 = {
  1,
  {
    { -8, 1, 0x0373, -4 }
  }
};
static SKC_sprite_pattern obox04sp05 = {
  2,
  {
    { -12, 5, 0x0375, -16 },
    { -12, 5, 0x0B75,   0 }
  }
};
static SKC_sprite_pattern obox04sp10 = {
  1,
  {
    { -8, 5, 0x0B6F, -8 }
  }
};
static SKC_sprite_pattern obox04sp11 = {
  1,
  {
    { -8, 1, 0x0B73, -4 }
  }
};
static SKC_sprite_pattern obox04sp12 = {
  2,
  {
    { -5, 5, 0x0375, -16 },
    { -5, 5, 0x0B75,   0 }
  }
};
