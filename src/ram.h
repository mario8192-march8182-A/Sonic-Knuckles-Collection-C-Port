#ifndef SKC_RAM_H
#define SKC_RAM_H

typedef struct SKC_sprite_data SKC_sprite_data;

extern unsigned char g_vram[0x10000];
unsigned short* get_colorwk(void);
unsigned short* get_colorwk2(void);
unsigned short* get_colorwk3(void);
void clear_game_ram(void);
unsigned short* get_demotimer_ptr(void);
short* get_hscrollbuff(void);
unsigned char* get_int_flg_ptr(void);
long get_scra_v_posit_copy(void);
SKC_sprite_data* get_sprite_table(void);
unsigned char get_hintposi(void);
short get_vscrolla(void);
short get_vscrollb(void);
unsigned short* get_vscrollbuff(void);
unsigned long get_vs_vscroll(void);
unsigned char get_waterflag(void);
void inc_systemtimer(void);
void set_int_flg(unsigned char value);
void set_region(unsigned char region);
void set_swdata1(unsigned short raw_swdata);
void set_swdata2(unsigned short raw_swdata);

#endif
