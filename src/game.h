#ifdef __cplusplus
extern "C" {
#endif

#ifndef GAME_H
#define GAME_H

void start_debug();
void start_specialstagemode();
void start_game(unsigned short cartridge);
void gameloop();
void clear_displaydata();
void bgmset(signed char command);
void soundset(signed char command);
void init_sprlist();
void action();
void actionsub(sprite_status* p_actwk);
void patchg(sprite_status* p_actwk, signed char** p_chg_data);
void patchg2(sprite_status* p_actwk, signed char** p_chg_data);
void patset();
unsigned long random();
void load_string_vram(unsigned char* p_text, unsigned long vramoffset, unsigned short coloroffset);

#endif

#ifdef __cplusplus
}
#endif
