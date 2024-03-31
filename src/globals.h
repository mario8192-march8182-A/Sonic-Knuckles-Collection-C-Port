#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include "constants.h"
#include "types.h"

extern bool Sonic_3_alone;
extern bool INI_DebugMode;

extern unsigned short pbuffer[PBUFFER_LEVELS][PBUFFER_LEVEL_SLOTS];
extern sprite_status actwk[ACTWK_SLOTS];
extern unsigned short colibuffer[COLBUFFER_SLOTS];
extern short ringwk[RINGWK_SLOTS];
extern unsigned char flagwork[FLAGWORK_SLOTS];
extern short scralim_n_down;
extern short scralim_down;
extern unsigned char scr_resize_no;
extern unsigned short stageno_i;
extern long scra_h_posit;
extern long scra_v_posit;
extern short frame_offset_x;
extern unsigned short ringbuffer[RINGBUFFER_SLOTS];
extern unsigned long ranum;
extern short waterposi;
extern unsigned char waterflag;
extern unsigned char watermode;
extern unsigned char miles_carry_flag;
extern unsigned char soz_darkness_level;
extern unsigned char reverse_gravity_flag;
extern unsigned char pl2_lock_flag;
extern unsigned short scr_x_no;
extern unsigned char emy_wrt_flg[EMY_WRT_FLG_SLOTS];
extern unsigned char DAT_08fffaa2;
extern unsigned char act_clear_flag;
extern unsigned long systemtimer;
extern unsigned char soz_ghosts;
extern unsigned char DAT_08fffacd;
extern unsigned short gameflag;
extern unsigned char edit_r_no;
extern unsigned short stageno;
extern unsigned char pl_suu;
extern unsigned char plring_f2;
extern unsigned char pl_suu_f;
extern unsigned char plring_f;
extern short plring;
extern unsigned long pltime;
extern unsigned char markerno;
extern unsigned char markerno_s;
extern unsigned short stageno_s;
extern short plxposi_s;
extern short plyposi_s;
extern short plring_s;
extern unsigned long pltime_s;
extern unsigned short plsproffset_s;
extern unsigned short plcolibits_s;
extern short scra_h_posit_s;
extern short scra_v_posit_s;
extern short waterposi_s;
extern unsigned char waterflag_s;
extern unsigned char plring_f2_s;
extern short scralim_down_s;
extern unsigned char scr_resize_no_s;
extern unsigned char plcddat2_s;
extern unsigned char marker_flag;
extern unsigned char markerno_s2;
extern unsigned short stageno_s2;
extern short plxposi_s2;
extern short plyposi_s2;
extern short plring_s2;
extern unsigned long pltime_s2;
extern unsigned short plsproffset_s2;
extern unsigned short plcolibits_s2;
extern short scra_h_posit_s2;
extern short scra_v_posit_s2;
extern short waterposi_s2;
extern unsigned char waterflag_s2;
extern unsigned char plring_f2_s2;
extern short scralim_down_s2;
extern unsigned char scr_resize_no_s2;
extern unsigned char ring_patno;
extern unsigned char flyring_patcnt;
extern unsigned char flyring_patno;
extern unsigned char pl2ring_f;
extern unsigned char pl2ring_f2;
extern unsigned char pl2_suu;
extern short plring_act;
extern short pl2ring_act;
extern short pl2ring;
extern short actring;
extern unsigned char plcddat2_s2;
extern unsigned char plresetflag;
extern unsigned short stageno_is;
extern unsigned short stageno_is2;
extern unsigned short cartridge;
extern unsigned short plsproffset;
extern unsigned short vs_flag;

#endif
