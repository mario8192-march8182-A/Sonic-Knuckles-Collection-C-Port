#ifndef HITCHK_H
#define HITCHK_H

#include "sprite_status.h"
#include "types.h"

hitchk_results hitchk(sprite_status* p_actwk, hitchk_data data);
hitchk_results plhitchk(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit);
hitchk_results hitchk2(sprite_status* p_actwk, hitchk_data data);
hitchk_results plhitchk2(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit);
hitchk_results hitchk_slope(sprite_status* p_actwk, hitchk_data data, signed char* slope_heights);
hitchk_results plhitchk_slope(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit);
hitchk_results hitchk_doubleslope(sprite_status* p_actwk, hitchk_data data, signed char* slope_heights);
hitchk_results hitchk_bryuka(sprite_status* p_actwk, hitchk_data data, signed char* slope_heights);
hitchk_results hitchk_offset(sprite_status* p_actwk, hitchk_data data);
hitchk_results plhitchk_chk_coli2(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit);

#endif
