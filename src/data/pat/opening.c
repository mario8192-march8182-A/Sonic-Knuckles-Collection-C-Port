#include "../../types/spritepattern.h"
static SKC_sprite_pattern s3opening_banner_pt00;
static SKC_sprite_pattern s3opening_banner_pt01;
static SKC_sprite_pattern skopening_sonicfalling_pt00;
static SKC_sprite_pattern skopening_deathegg_pt00;
static SKC_sprite_pattern skopening_banner_pt00;
static SKC_sprite_pattern skopening_mountain_pt00;

SKC_sprite_pattern* s3opening_banner_pt[2] = {
  &s3opening_banner_pt00,
  &s3opening_banner_pt01
};
static SKC_sprite_pattern s3opening_banner_pt00 = {
  21,
  {
    { 16, 15, 0x0000, -104 },
    { 16, 15, 0x0010,  -72 },
    { 16, 15, 0x0020,  -40 },
    { 16, 15, 0x0030,   -8 },
    { 16, 15, 0x0040,   24 },
    { 16, 15, 0x0050,   56 },
    { 16,  7, 0x0800,   88 },
    { 48, 15, 0x0060, -128 },
    { 48,  7, 0x0070,  -96 },
    { 48,  9, 0x0078,  -80 },
    { 48, 15, 0x007E,  -56 },
    { 48, 15, 0x008E,  -24 },
    { 48, 15, 0x009E,    8 },
    { 48,  7, 0x00AE,   40 },
    { 48,  9, 0x00B6,   56 },
    { 48, 15, 0x00BC,   80 },
    { 48,  7, 0x0860,  112 },
    { 80,  5, 0x00CC, -128 },
    { 80,  8, 0x00D0, -112 },
    { 80,  8, 0x08D0,   88 },
    { 80,  5, 0x08CC,  112 },
  }
};
static SKC_sprite_pattern s3opening_banner_pt01 = {
  1,
  {
    { -4, 8, 0x00D3, -12 },
  }
};
SKC_sprite_pattern* skopening_sonicfalling_pt[1] = {
  &skopening_sonicfalling_pt00
};
static SKC_sprite_pattern skopening_sonicfalling_pt00 = {
  32,
  {
    { -112, 15, 0x0000, -48 },
    { -112, 15, 0x0010, -16 },
    { -112, 15, 0x0020,  16 },
    { -112,  5, 0x0030, -64 },
    { -112,  4, 0x0034,  48 },
    { -104,  2, 0x0036,  48 },
    {  -80, 15, 0x0039, -48 },
    {  -80, 15, 0x0049, -16 },
    {  -80, 15, 0x0059,  16 },
    {  -80,  6, 0x0069,  48 },
    {  -72, 15, 0x006F, -80 },
    {  -64,  2, 0x007F, -88 },
    {  -48, 15, 0x0082, -16 },
    {  -48,  7, 0x0092,  16 },
    {  -48,  9, 0x009A,  32 },
    {  -32,  4, 0x00A0,  40 },
    {  -24, 14, 0x00A2,  48 },
    {  -32, 12, 0x00AE,  56 },
    {  -24,  7, 0x00B2,  80 },
    {    0,  0, 0x00BA,  72 },
    {  -48,  8, 0x00BB, -40 },
    {  -40,  5, 0x00BE, -32 },
    {  -16, 15, 0x00C2, -16 },
    {  -16,  1, 0x00D2,  16 },
    {    0,  5, 0x00D4,  16 },
    {   16,  6, 0x00D8,  -8 },
    {   16, 15, 0x00DE,   8 },
    {   48, 15, 0x00EE,   8 },
    {   40,  3, 0x00FE,  40 },
    {   72,  0, 0x0102,  40 },
    {   80, 13, 0x0103,   8 },
    {   96,  9, 0x010B,   8 },
  }
};
SKC_sprite_pattern* skopening_deathegg_pt[1] = {
  &skopening_deathegg_pt00
};
static SKC_sprite_pattern skopening_deathegg_pt00 = {
  18,
  {
    { -64, 15, 0x0000, -32 },
    { -64, 15, 0x0800,   0 },
    { -56, 10, 0x0010, -56 },
    { -56, 10, 0x0810,  32 },
    { -32, 15, 0x0019, -64 },
    { -32, 15, 0x0819,  32 },
    { -32, 15, 0x0029, -32 },
    { -32, 15, 0x0829,   0 },
    {   0, 15, 0x0039, -64 },
    {   0, 15, 0x0049, -32 },
    {   0, 15, 0x0849,   0 },
    {   0, 15, 0x0839,  32 },
    {  32,  8, 0x0059, -56 },
    {  32, 15, 0x005C, -32 },
    {  40,  6, 0x006C, -48 },
    {  32, 15, 0x085C,   0 },
    {  32,  8, 0x0859,  32 },
    {  40,  6, 0x086C,  32 },
  }
};
SKC_sprite_pattern* skopening_banner_pt[1] = {
  &skopening_banner_pt00
};
static SKC_sprite_pattern skopening_banner_pt00 = {
  30,
  {
    { -40, 15, 0x6000, -100 },
    { -40, 15, 0x6010,  -68 },
    { -40, 15, 0x6020,  -36 },
    { -40, 15, 0x6030,   -4 },
    { -40, 11, 0x6040,   28 },
    { -32, 14, 0x604C,   52 },
    {  -8, 12, 0x6058, -124 },
    {  -8, 12, 0x605C,  -92 },
    {  -8, 12, 0x6060,  -60 },
    {  -8, 12, 0x6064,  -28 },
    {  -8, 12, 0x6068,    4 },
    {  -8, 12, 0x606C,   36 },
    {  -8, 12, 0x6070,   68 },
    {  -8,  8, 0x6074,  100 },
    {   0, 15, 0x2077, -124 },
    {   0, 15, 0x2087,  -92 },
    {   0, 15, 0x2097,  -60 },
    {   0, 15, 0x20A7,  -28 },
    {   0, 15, 0x20B7,    4 },
    {   0, 15, 0x20C7,   36 },
    {   0, 15, 0x20D7,   68 },
    {   0, 11, 0x20E7,  100 },
    {  32, 12, 0x20F3, -124 },
    {  32, 12, 0x20F7,  -92 },
    {  32, 12, 0x20FB,  -60 },
    {  32, 12, 0x20FF,  -28 },
    {  32, 12, 0x2103,    4 },
    {  32, 12, 0x2107,   36 },
    {  32, 12, 0x210B,   68 },
    {  32,  8, 0x210F,  100 },
  }
};
SKC_sprite_pattern* skopening_mountain_pt[1] = {
  &skopening_mountain_pt00
};
static SKC_sprite_pattern skopening_mountain_pt00 = {
  4,
  {
    { -8,  0, 0x0000, -48 },
    {  0, 12, 0x0001, -48 },
    { -8, 13, 0x0005, -16 },
    { -8, 13, 0x000D,  16 },
  }
};
