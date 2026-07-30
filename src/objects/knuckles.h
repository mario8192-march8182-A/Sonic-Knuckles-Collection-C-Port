#ifndef SKC_KNUCKLES_H
#define SKC_KNUCKLES_H

typedef struct SKC_sprite_status SKC_sprite_status;

void knuckles(SKC_sprite_status* p_playerwk);
void knucklesjumpcolsub0(SKC_sprite_status* p_playerwk);
void knuckleswrt(SKC_sprite_status* p_playerwk);
void knuckleswrt0(unsigned char patno);
void knuckleswrt1(unsigned char patno, unsigned short vram_adr);

#endif
