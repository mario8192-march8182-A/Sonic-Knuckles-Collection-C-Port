#include "../../../spritepattern.h"
static SKC_sprite_pattern hana00sp00;
static SKC_sprite_pattern hana00sp01;
static SKC_sprite_pattern hana00sp02;
static SKC_sprite_pattern hana00sp03;
static SKC_sprite_pattern hana00sp04;

SKC_sprite_pattern* hana00pat[5] = {
  &hana00sp00,
  &hana00sp01,
  &hana00sp02,
  &hana00sp03,
  &hana00sp04
};
static SKC_sprite_pattern hana00sp00 = {
  6,
  {
    { -22, 6, 0x0007, -16 },
    { -22, 6, 0x0807,   0 },
    {   8, 0, 0x0000, -24 },
    {   0, 6, 0x0001, -16 },
    {   0, 6, 0x0801,   0 },
    {   8, 0, 0x0800,  16 }
  }
};
static SKC_sprite_pattern hana00sp01 = {
  6,
  {
    { -22, 6, 0x000D, -16 },
    { -22, 6, 0x080D,   0 },
    {   8, 0, 0x0000, -24 },
    {   0, 6, 0x0001, -16 },
    {   0, 6, 0x0801,   0 },
    {   8, 0, 0x0800,  16 }
  }
};
static SKC_sprite_pattern hana00sp02 = {
  8,
  {
    { -30, 0, 0x0013,  -8 },
    { -22, 6, 0x0014, -16 },
    { -30, 0, 0x0813,   0 },
    { -22, 6, 0x0814,   0 },
    {   8, 0, 0x0000, -24 },
    {   0, 6, 0x0001, -16 },
    {   0, 6, 0x0801,   0 },
    {   8, 0, 0x0800,  16 }
  }
};
static SKC_sprite_pattern hana00sp03 = {
  6,
  {
    { -20, 6, 0x0007, -16 },
    { -20, 6, 0x0807,   0 },
    {   8, 0, 0x0000, -24 },
    {   0, 6, 0x0001, -16 },
    {   0, 6, 0x0801,   0 },
    {   8, 0, 0x0800,  16 }
  }
};
static SKC_sprite_pattern hana00sp04 = {
  1,
  {
    { -8, 5, 0x001A, -8 }
  }
};
