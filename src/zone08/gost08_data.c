#include "..\types.h"


short col_tbl_00[4] = { -16, 32, -64, 128 };
short col_tbl_04[4] = { -16, 32, -128, 256 };

short gost08_init_spd_tbl[6] = {
  -256, -256, -256, -384, -384, -512
};

wrt_init_data gost08_init_tbl = {
  2,
  42240,
  18,
  0,
  gost08pat,
  0,
  16,
  20,
  0,
  0
};

enemy_init0_data obox08_init_tbl = {
  openbox_pt,
  34102,
  384,
  48,
  64,
  0,
  0
};

enemy_init0_data obox08_gost_init_tbl = {
  gost08pat,
  42240,
  512,
  48,
  32,
  0,
  0
};

unsigned short gost08_tbl00[2] = {    0,    8 };
unsigned short gost08_tbl01[2] = {    0,  152 };
unsigned short gost08_tbl02[2] = {    0,  296 };
unsigned short gost08_tbl03[2] = {    0,  440 };
unsigned short gost08_tbl04[2] = {    0,  584 };
unsigned short gost08_tbl05[2] = {    0,  728 };
unsigned short gost08_tbl06[2] = {    0,  872 };
unsigned short gost08_tbl07[2] = {    0, 1016 };
unsigned short gost08_tbl08[2] = {    0, 1167 };
unsigned short gost08_tbl09[3] = {  256, 1413, 1515 };
unsigned short gost08_tbl10[3] = {  256, 1701, 1803 };
unsigned short gost08_tbl11[3] = {  256, 1989, 2091 };
unsigned short gost08_tbl12[3] = {  256, 1701, 2283 };
unsigned short gost08_tbl13[2] = {    0, 2472 };
unsigned short gost08_tbl14[2] = {    0, 2616 };
unsigned short gost08_tbl15[2] = {    0, 2755 };
unsigned short gost08_tbl16[2] = {    0, 2819 };
unsigned short gost08_tbl17[2] = {    0, 2880 };

unsigned short* gost08_tbl[18] = {
  gost08_tbl00,
  gost08_tbl01,
  gost08_tbl02,
  gost08_tbl03,
  gost08_tbl04,
  gost08_tbl05,
  gost08_tbl06,
  gost08_tbl07,
  gost08_tbl08,
  gost08_tbl09,
  gost08_tbl10,
  gost08_tbl11,
  gost08_tbl12,
  gost08_tbl13,
  gost08_tbl14,
  gost08_tbl15,
  gost08_tbl16,
  gost08_tbl17
};

wrt_data gost08_wrt_tbl = {
  gost08_tiles,
  gost08_tbl
};

signed char gost08_apar_pg00[12] = { 17,  3, 17,  3, 16,  3, 15,  4, 14,  4, -8, 12 };
signed char gost08_pg00[7] =       {  0,  3,  1,  3,  2,  4, -4 };
signed char gost08_apar_pg01[14] = { 17,  3, 17,  3, 16,  3, 15,  4, 14,  4, 13,  4, -8, 14 };
signed char gost08_pg01[7] =       {  5,  3,  6,  3,  7,  4, -4 };
signed char gost08_apar_pg02[14] = { 17,  3, 17,  3, 16,  3, 15,  4, 14,  4, 13,  4, -8, 14 };
signed char gost08_pg02[7] =       { 10,  3, 11,  3, 12,  4, -4 };
signed char gost08_away_pg00[13] = { 13,  4, 13,  4, 14,  4, 15,  4, 16,  3, 17,  3, -12 };
signed char gost08_chg_pg00[8] =   {  3,  7,  3,  7,  4,  7, -8, -41 };
signed char gost08_chg_pg01[8] =   {  8,  7,  8,  7,  9,  7, -8, -28 };
