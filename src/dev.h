#ifndef SKC_DEV_H
#define SKC_DEV_H

typedef struct SKC_block SKC_block;
typedef struct SKC_cg_data SKC_cg_data;
typedef struct SKC_screen SKC_screen;

void bitdevr(unsigned char* p_destination, unsigned char* p_source);
void divdevset(unsigned short id);
void divdevset2(SKC_cg_data* p_data);
void copy_map_vram(unsigned char* p_source, unsigned short offset, unsigned short col_cnt, unsigned short row_cnt);
void copy_map_vram2(unsigned char* p_source, unsigned short offset, unsigned short col_cnt, unsigned short row_cnt);
void mapdevr(unsigned char* p_destination, unsigned char* p_source, unsigned short offset);
unsigned char* unlze(unsigned char* p_destination, unsigned char* p_source);
void unlze_moduled(unsigned char* p_destination, unsigned char* p_source);
unsigned short unlze_blocks(SKC_block* p_destination, unsigned char* p_source);
unsigned short unlze_screens(SKC_screen* p_destination, unsigned char* p_source);

#endif
