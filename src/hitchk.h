#ifndef SKC_HITCHK_H
#define SKC_HITCHK_H

#include <stdbool.h>
#include "types/hitchkdata.h"
#include "types/hitchkresult.h"
#include "types/spritestatus.h"

SKC_hitchk_result hitchk(SKC_sprite_status* p_actwk, SKC_hitchk_data data);
SKC_hitchk_coli plhitchk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
SKC_hitchk_result hitchk_skip_onscreen(SKC_sprite_status* p_actwk, SKC_hitchk_data data);
SKC_hitchk_coli plhitchk_skip_onscreen(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
SKC_hitchk_result hitchk_slope(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights);
SKC_hitchk_coli plhitchk_slope(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, signed char* p_slope_heights, bool* p_plride, bool* p_plpush);
SKC_hitchk_result hitchk_bryuka(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights);
SKC_hitchk_result hitchk_offset(SKC_sprite_status* p_actwk, SKC_hitchk_data data);
SKC_hitchk_coli plhitchk_chk_coli_skip_onscreen(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush);

#endif
