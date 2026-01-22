#include "../../../spritepattern.h"
static SKC_sprite_pattern sai00sp00;
static SKC_sprite_pattern sai00sp01;
static SKC_sprite_pattern sai00sp02;
static SKC_sprite_pattern sai00sp03;
static SKC_sprite_pattern sai00sp04;
static SKC_sprite_pattern sai00sp05;
static SKC_sprite_pattern sai00sp06;
static SKC_sprite_pattern sai00sp07;

SKC_sprite_pattern* sai00pat[8] = {
  &sai00sp00,
  &sai00sp01,
  &sai00sp02,
  &sai00sp03,
  &sai00sp04,
  &sai00sp05,
  &sai00sp06,
  &sai00sp07
};
static SKC_sprite_pattern sai00sp00 = {
  3,
  {
    {   0,  1, 0x0000, -24 },
    { -16, 15, 0x0002, -16 },
    {  -8,  2, 0x0012,  16 }
  }
};
static SKC_sprite_pattern sai00sp01 = {
  3,
  {
    {   0,  1, 0x0000, -20 },
    { -16,  4, 0x0002, -12 },
    {  -8, 14, 0x0004, -12 }
  }
};
static SKC_sprite_pattern sai00sp02 = {
  1,
  {
    { -16, 11, 0x0000, -12 }
  }
};
static SKC_sprite_pattern sai00sp03 = {
  2,
  {
    { -16, 15, 0x0000, -20 },
    {  -8,  1, 0x0010,  12 }
  }
};
static SKC_sprite_pattern sai00sp04 = {
  1,
  {
    { 0, 8, 0x0000, -12 }
  }
};
static SKC_sprite_pattern sai00sp05 = {
  1,
  {
    { -8, 9, 0x0000, -12 }
  }
};
static SKC_sprite_pattern sai00sp06 = {
  1,
  {
    { -8, 9, 0x0000, -12 }
  }
};
static SKC_sprite_pattern sai00sp07 = {
  1,
  {
    { 0, 8, 0x0000, -12 }
  }
};
