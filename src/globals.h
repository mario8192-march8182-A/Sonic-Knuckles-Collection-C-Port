#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include "constants.h"
#include "types.h"

extern bool Sonic_3_alone;

extern unsigned short pbuffer[PBUFFER_LEVELS][PBUFFER_LEVEL_SLOTS];
extern sprite_status actwk[ACTWK_SLOTS];
extern unsigned short colibuffer[COLBUFFER_SLOTS];
extern unsigned char flagwork[FLAGWORK_SLOTS];
extern long scra_h_posit;
extern long scra_v_posit;
extern unsigned long ranum;
extern unsigned char soz_darkness_level;
extern unsigned short scr_x_no;
extern unsigned char emy_wrt_flg[EMY_WRT_FLG_SLOTS];
extern unsigned char soz_ghosts;
extern unsigned char edit_r_no;
extern short plring;
extern unsigned char markerno;
extern short plxposi_s;
extern short plyposi_s;
extern short pl2ring;
extern unsigned short vs_flag;

#endif
