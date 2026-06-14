#ifndef SKC_SAVEDATA_H
#define SKC_SAVEDATA_H

#include "types/acttimer.h"

typedef struct SKC_vs_savedata {
  act_timer first;
  act_timer second;
  act_timer third;
  unsigned char characters[4];
}
SKC_vs_savedata;

typedef struct SKC_s3k_savedata {
  unsigned int new : 6;
  unsigned int clear_type : 2;
  unsigned int unused;
  unsigned int play_type : 4;
  unsigned int specstageno : 4;
  unsigned char zone;
  unsigned short brings;
  unsigned int specprogress0 : 2;
  unsigned int specprogress1 : 2;
  unsigned int specprogress2 : 2;
  unsigned int specprogress3 : 2;
  unsigned int specprogress4 : 2;
  unsigned int specprogress5 : 2;
  unsigned int specprogress6 : 2;
  unsigned int specprogress7 : 2;
  unsigned char pl_suu;
  unsigned char plcontinuecnt;
}
SKC_s3k_savedata;

typedef struct SKC_s3_savedata {
  unsigned char new;
  unsigned char brings1;
  unsigned char play_type;
  unsigned char zone;
  unsigned char specstageno;
  unsigned char emeraldcnt;
  unsigned int specprogress0 : 1;
  unsigned int specprogress1 : 1;
  unsigned int specprogress2 : 1;
  unsigned int specprogress3 : 1;
  unsigned int specprogress4 : 1;
  unsigned int specprogress5 : 1;
  unsigned int specprogress6 : 1;
  unsigned int specprogress7 : 1;
  unsigned char brings0;
}
SKC_s3_savedata;

typedef union SKC_savedata {
  SKC_s3k_savedata s3k;
  SKC_s3_savedata s3;
}
SKC_savedata;

void read_savedata(void);
void write_vs_savedata(void);
void write_savedata(void);
void save_game(void);
void save_game2(void);
void save_game3(void);

#endif
