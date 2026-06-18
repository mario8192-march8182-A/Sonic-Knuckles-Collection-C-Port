#include "../../spritepattern.h"
SKC_sprite_pattern* mask_spr_pat[17] = {
  &mask_spr_sp00,
  &mask_spr_sp01,
  &mask_spr_sp02,
  &mask_spr_sp03,
  &mask_spr_sp04,
  &mask_spr_sp05,
  &mask_spr_sp06,
  &mask_spr_sp07,
  &mask_spr_sp08,
  &mask_spr_sp09,
  &mask_spr_sp10,
  &mask_spr_sp11,
  &mask_spr_sp12,
  &mask_spr_sp13,
  &mask_spr_sp14,
  &mask_spr_sp15,
  &mask_spr_sp16
};
static SKC_sprite_pattern mask_spr_sp00 = {
  0,
  {}
};
static SKC_sprite_pattern mask_spr_sp01 = {
  2,
  {
    { -4, 0, 0x07C0, 8 },
    { -4, 0, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp02 = {
  2,
  {
    { -8, 1, 0x07C0, 8 },
    { -8, 1, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp03 = {
  2,
  {
    { -12, 2, 0x07C0, 8 },
    { -12, 2, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp04 = {
  2,
  {
    { -16, 3, 0x07C0, 8 },
    { -16, 3, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp05 = {
  4,
  {
    { -20, 3, 0x07C0, 8 },
    { -20, 3, 0x0000, 0 },
    {  12, 0, 0x07C0, 8 },
    {  12, 0, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp06 = {
  4,
  {
    { -24, 3, 0x07C0, 8 },
    { -24, 3, 0x0000, 0 },
    {   8, 1, 0x07C0, 8 },
    {   8, 1, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp07 = {
  4,
  {
    { -28, 3, 0x07C0, 8 },
    { -28, 3, 0x0000, 0 },
    {   4, 2, 0x07C0, 8 },
    {   4, 2, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp08 = {
  4,
  {
    { -32, 3, 0x07C0, 8 },
    { -32, 3, 0x0000, 0 },
    {   0, 3, 0x07C0, 8 },
    {   0, 3, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp09 = {
  6,
  {
    { -36, 3, 0x07C0, 8 },
    { -36, 3, 0x0000, 0 },
    {  -4, 3, 0x07C0, 8 },
    {  -4, 3, 0x0000, 0 },
    {  28, 0, 0x07C0, 8 },
    {  28, 0, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp10 = {
  6,
  {
    { -40, 3, 0x07C0, 8 },
    { -40, 3, 0x0000, 0 },
    {  -8, 3, 0x07C0, 8 },
    {  -8, 3, 0x0000, 0 },
    {  24, 1, 0x07C0, 8 },
    {  24, 1, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp11 = {
  6,
  {
    { -44, 3, 0x07C0, 8 },
    { -44, 3, 0x0000, 0 },
    { -12, 3, 0x07C0, 8 },
    { -12, 3, 0x0000, 0 },
    {  20, 2, 0x07C0, 8 },
    {  20, 2, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp12 = {
  6,
  {
    { -48, 3, 0x07C0, 8 },
    { -48, 3, 0x0000, 0 },
    { -16, 3, 0x07C0, 8 },
    { -16, 3, 0x0000, 0 },
    {  16, 3, 0x07C0, 8 },
    {  16, 3, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp13 = {
  8,
  {
    { -52, 3, 0x07C0, 8 },
    { -52, 3, 0x0000, 0 },
    { -20, 3, 0x07C0, 8 },
    { -20, 3, 0x0000, 0 },
    {  12, 3, 0x07C0, 8 },
    {  12, 3, 0x0000, 0 },
    {  44, 0, 0x07C0, 8 },
    {  44, 0, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp14 = {
  8,
  {
    { -56, 3, 0x07C0, 8 },
    { -56, 3, 0x0000, 0 },
    { -24, 3, 0x07C0, 8 },
    { -24, 3, 0x0000, 0 },
    {   8, 3, 0x07C0, 8 },
    {   8, 3, 0x0000, 0 },
    {  40, 1, 0x07C0, 8 },
    {  40, 1, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp15 = {
  8,
  {
    { -60, 3, 0x07C0, 8 },
    { -60, 3, 0x0000, 0 },
    { -28, 3, 0x07C0, 8 },
    { -28, 3, 0x0000, 0 },
    {   4, 3, 0x07C0, 8 },
    {   4, 3, 0x0000, 0 },
    {  36, 2, 0x07C0, 8 },
    {  36, 2, 0x0000, 0 },
  }
};
static SKC_sprite_pattern mask_spr_sp16 = {
  8,
  {
    { -64, 3, 0x07C0, 8 },
    { -64, 3, 0x0000, 0 },
    { -32, 3, 0x07C0, 8 },
    { -32, 3, 0x0000, 0 },
    {   0, 3, 0x07C0, 8 },
    {   0, 3, 0x0000, 0 },
    {  32, 3, 0x07C0, 8 },
    {  32, 3, 0x0000, 0 },
  }
};
