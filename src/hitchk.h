#ifndef SKC_HITCHK_H
#define SKC_HITCHK_H

#include <stdbool.h>

typedef struct SKC_sprite_status SKC_sprite_status;

typedef enum SKC_hitchk_coli {
  HITCHK_COLI_NONE = 0,
  HITCHK_COLI_SIDE = 1,
  HITCHK_COLI_BOTTOM = -2,
  HITCHK_COLI_TOP = -1
}
SKC_hitchk_coli;

typedef struct SKC_hitchk_data {
  unsigned short sprhs;
  unsigned short sprvs_air;
  unsigned short sprvs_ground;
  short xposi;
}
SKC_hitchk_data;

typedef struct SKC_hitchk_result {
  SKC_hitchk_coli plcoli[2];
}
SKC_hitchk_result;

SKC_hitchk_result hitchk(SKC_sprite_status* p_actwk, SKC_hitchk_data data);
SKC_hitchk_coli plhitchk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
SKC_hitchk_result hitchk_skip_onscreen(SKC_sprite_status* p_actwk, SKC_hitchk_data data);
SKC_hitchk_coli plhitchk_skip_onscreen(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
SKC_hitchk_result hitchk_slope(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights);
SKC_hitchk_coli plhitchk_slope(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, signed char* p_slope_heights, bool* p_plride, bool* p_plpush);
SKC_hitchk_result hitchk_bryuka(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights);
SKC_hitchk_result hitchk_offset(SKC_sprite_status* p_actwk, SKC_hitchk_data data);
SKC_hitchk_coli plhitchk_chk_coli_skip_onscreen(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
void ride_dai(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char sprvs_ground, short xposi);
void ride_sloped_dai(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, unsigned char sprhs, short xposi, signed char* p_slope_heights);
SKC_hitchk_result ridechk(SKC_sprite_status* p_actwk, SKC_hitchk_data data);
SKC_hitchk_coli plridechk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride);
SKC_hitchk_result ridechk_sloped(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights);
SKC_hitchk_result ridechk_sloped2(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights);
void hashiridechk_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride);
void ridechk_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride);
void ridechk_chk_coli_skip_x(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride);
void ridechk_chk_coli_y(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, short yposi, bool* p_plride);
void set_ride(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride);
void clear_ride(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk);

#endif
