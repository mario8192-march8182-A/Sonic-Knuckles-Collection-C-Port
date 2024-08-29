#ifdef __cplusplus
extern "C" {
#endif

#ifndef GAME_H
#define GAME_H

void start_debug();
void start_specialstagemode();
void gameloop();
void clear_displaydata();
void bgmset(signed char command);
void soundset(signed char command);
void init_sprlist();
void action();
void actionsub(sprite_status* p_actwk);
void patchg2(sprite_status* p_actwk, signed char** p_chg_data);
void patset();
void FUN_00824a1c(unsigned char* p_text, unsigned long vramoffset, unsigned short coloroffset);

#endif

#ifdef __cplusplus
}
#endif
