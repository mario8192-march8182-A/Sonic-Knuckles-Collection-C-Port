#ifndef VDP_H
#define VDP_H

#include "types/sprite.h"

void FUN_0040edec();
void FUN_0040ee9e();
void FUN_0040ef0c();
void FUN_0040f4c8();
void copy_map_vram(unsigned short* p_source, unsigned short offset, unsigned long row_cnt, unsigned long cell_cnt);
void copy_data_vram(void* p_source, unsigned short offset, unsigned short size);
void FUN_0041439c();
void FUN_0041448e();
void FUN_004145ee();
void FUN_004146ac();
void FUN_0041479e();
void FUN_00414890();
void FUN_004148fe();
void FUN_0041496c();
void FUN_00414f70();
void FUN_00415039();
void blit_sprite_noprio(Sprite* p_sprite);
void blit_sprite_hflip_noprio(Sprite* p_sprite);
void blit_sprite_vflip_noprio(Sprite* p_sprite);
void blit_sprite_hvflip_noprio(Sprite* p_sprite);
void FUN_00411a50(Sprite* p_sprite);
void blit_sprite_masked(Sprite* p_sprite);
void blit_sprite_masked_hflip(Sprite* p_sprite);
void blit_sprite_masked_vflip(Sprite* p_sprite);
void blit_sprite_masked_hvflip(Sprite* p_sprite);
void blit_sprite(Sprite* p_sprite);
void blit_sprite_hflip(Sprite* p_sprite);
void blit_sprite_vflip(Sprite* p_sprite);
void blit_sprite_hvflip(Sprite* p_sprite);

#endif
