#ifndef SKC_PLAYER_H
#define SKC_PLAYER_H

#include <stdbool.h>
#include "../types/playwork.h"
#include "../dircol.h"

typedef struct SKC_sprite_status SKC_sprite_status;

void vsplay(SKC_sprite_status* p_playerwk);
void play00(SKC_sprite_status* p_playerwk);
void playposiwkset(SKC_sprite_status* p_playerwk);
void playposiwkinit(SKC_sprite_status* p_playerwk);
void fcol_g(SKC_sprite_status* p_playerwk);
void limitchk(SKC_sprite_status* p_playerwk);
void ballchk(SKC_sprite_status* p_playerwk);
void foxsupercnt(SKC_sprite_status* p_playerwk, SKC_play_work work);
void playsupercnt(SKC_sprite_status* p_playerwk, SKC_play_work work);
bool spinchk(SKC_sprite_status* p_playerwk, SKC_play_work work);
void keispd(SKC_sprite_status* p_playerwk);
void keispd2(SKC_sprite_status* p_playerwk);
void fallchk(SKC_sprite_status* p_playerwk);
void direcchg(SKC_sprite_status* p_playerwk);
void jumpcolchk(SKC_sprite_status* p_playerwk);
SKC_dircol_result dircol_d_g(SKC_sprite_status* p_playerwk);
SKC_dircol_result dircol_u_g(SKC_sprite_status* p_playerwk);
SKC_dircol_result edgechk_d2_g(SKC_sprite_status* p_playerwk, short xposi);
void jumpcolsub0(SKC_sprite_status* p_playerwk);
void play00die_sub(SKC_sprite_status* p_playerwk, SKC_play_work work);
void playflipchg(SKC_sprite_status* p_playerwk);
void playwrt(SKC_sprite_status* p_playerwk);
void playwrt1(SKC_sprite_status* p_playerwk, unsigned char patno);

#endif
