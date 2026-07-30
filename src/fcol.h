#ifndef SKC_FCOL_H
#define SKC_FCOL_H

#include <stdbool.h>

typedef struct SKC_sprite_status SKC_sprite_status;

bool fcol(SKC_sprite_status* p_actwk);
signed char scd2chk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk);
signed char flyringscd2chk(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk);
signed char scd2chk_r(short xposi, short yposi, short yoffset, unsigned short blk_msk, unsigned char solid_bit, unsigned char* p_dirstk);

#endif
