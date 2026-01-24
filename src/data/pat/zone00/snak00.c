#include "../../../spritepattern.h"
static SKC_sprite_pattern snak00sp00;
static SKC_sprite_pattern snak00sp01;
static SKC_sprite_pattern snak00sp02;
static SKC_sprite_pattern snak00sp03;
static SKC_sprite_pattern snak00sp04;
static SKC_sprite_pattern snak00sp05;

SKC_sprite_pattern* snak00pat[6] = {
  &snak00sp00,
  &snak00sp01,
  &snak00sp02,
  &snak00sp03,
  &snak00sp04,
  &snak00sp05
};


SKC_sprite_pattern snak00sp00 = {
  1,
  {
    { -8, 5, 0x0000, -8 }
  }
};
SKC_sprite_pattern snak00sp01 = {
  1,
  {
    { -12, 6, 0x0004, -8 }
  }
};
SKC_sprite_pattern snak00sp02 = {
  1,
  {
    { -8, 5, 0x000A, -8 }
  }
};
SKC_sprite_pattern snak00sp03 = {
  3,
  {
    { -20, 5, 0x000E, 0 },
    {  -4, 8, 0x0017, 0 },
    {   4, 5, 0x100E, 0 }
  }
};
SKC_sprite_pattern snak00sp04 = {
  3,
  {
    { -20, 5, 0x0012, 0 },
    {  -4, 4, 0x001A, 5 },
    {   4, 5, 0x1012, 0 }
  }
};
SKC_sprite_pattern snak00sp05 = {
  3,
  {
    { -12, 0, 0x0016,  8 },
    {  -4, 0, 0x001C, 16 },
    {   4, 0, 0x1016,  8 }
  }
};
