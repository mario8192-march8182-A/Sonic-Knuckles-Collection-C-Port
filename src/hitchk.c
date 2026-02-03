#include "hitchk.h"
#include <stdbool.h>
#include <stdlib.h>
#include "types/hitchkdistances.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "utils/bits.h"
#include "utils/fp16.h"
static SKC_hitchk_coli plhitchk_bryuka(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, signed char* p_slope_heights, bool* p_plride, bool* p_plpush);
static SKC_hitchk_coli plhitchk_offset(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush);
static SKC_hitchk_coli plhitchk_offset_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush);
static SKC_hitchk_coli plhitchk_slope_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, signed char* p_slope_heights, bool* p_plpush);
static SKC_hitchk_coli plhitchk_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush);
static SKC_hitchk_coli chk_bounds(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, SKC_hitchk_distances distances, bool* p_plpush);
static SKC_hitchk_coli chk_sides(SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances, bool* p_plpush);
static SKC_hitchk_coli chk_push(SKC_sprite_status* p_playerwk, bool* p_plpush);
static SKC_hitchk_coli clear_push(SKC_sprite_status* p_playerwk, bool* p_plpush);
static SKC_hitchk_coli chk_planes(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances, bool* p_plpush);
static SKC_hitchk_coli pop_down(SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances);
static SKC_hitchk_coli no_pop(SKC_sprite_status* p_playerwk);
static SKC_hitchk_coli crush(SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances, bool* p_plpush);
static SKC_hitchk_coli pop_up(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances);

extern sonic3_ram g_ram;


SKC_hitchk_result hitchk(SKC_sprite_status* p_actwk, SKC_hitchk_data data) {
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  if (g_ram.actwk[1].actflg.onscreen == 1) {
    bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
    bool pl2push = p_actwk->u.obj.cddat.pl2push;
    result.plcoli[1] = plhitchk(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
    p_actwk->u.obj.cddat.pl2ride = pl2ride;
    p_actwk->u.obj.cddat.pl2push = pl2push;
  }
  return result;
}


SKC_hitchk_coli plhitchk(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush) {
  if (!*p_plride) {
    return plhitchk_chk_coli(p_actwk, p_playerwk, data, p_plpush);
  }
  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if (p_playerwk->u.play.cddat.jump == 1 || distance < 0 || distance >= data.sprhs * 2) {
    p_playerwk->u.play.cddat.ride = 0;
    p_playerwk->u.play.cddat.jump = 1;
    *p_plride = false;
  }
  else {
    MvSonicOnPtfm(data.xposi);
  }
  return HITCHK_COLI_NONE;
}


SKC_hitchk_result hitchk_skip_onscreen(SKC_sprite_status* p_actwk, SKC_hitchk_data data) {
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_skip_onscreen(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  return result;
}


SKC_hitchk_coli plhitchk_skip_onscreen(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush) {
  if (!*p_plride) {
    return plhitchk_chk_coli_skip_onscreen(p_actwk, p_playerwk, data, p_plpush);
  }
  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if (p_playerwk->u.play.cddat.jump == 1 || distance < 0 || distance >= data.sprhs * 2) {
    p_playerwk->u.play.cddat.ride = 0;
    p_playerwk->u.play.cddat.jump = 1;
    *p_plride = false;
  }
  else {
    MvSonicOnPtfm(data.xposi);
  }
  return HITCHK_COLI_NONE;
}


SKC_hitchk_result hitchk_slope(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights) {
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_slope(p_actwk, &g_ram.actwk[0], data, p_slope_heights, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_slope(p_actwk, &g_ram.actwk[1], data, p_slope_heights, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  return result;
}


SKC_hitchk_coli plhitchk_slope(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, signed char* p_slope_heights, bool* p_plride, bool* p_plpush) {
  if (!*p_plride) {
    return plhitchk_slope_chk_coli(p_actwk, p_playerwk, data, p_slope_heights, p_plpush);
  }
  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if (p_playerwk->u.play.cddat.jump == 1 || distance < 0 || distance >= data.sprhs * 2) {
    p_playerwk->u.play.cddat.ride = 0;
    p_playerwk->u.play.cddat.jump = 1;
    *p_plride = false;
    return HITCHK_COLI_NONE;
  }
  MvSonicOnSlope(data.xposi);
  return HITCHK_COLI_TOP;
}


SKC_hitchk_result hitchk_bryuka(SKC_sprite_status* p_actwk, SKC_hitchk_data data, signed char* p_slope_heights) {
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_bryuka(p_actwk, &g_ram.actwk[0], data, p_slope_heights, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_bryuka(p_actwk, &g_ram.actwk[1], data, p_slope_heights, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  return result;
}


static SKC_hitchk_coli plhitchk_bryuka(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, signed char* p_slope_heights, bool* p_plride, bool* p_plpush) {
  if (!*p_plride) {
    return plhitchk_slope_chk_coli(p_actwk, p_playerwk, data, p_slope_heights, p_plpush);
  }
  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if (p_playerwk->u.play.cddat.jump == 1 || distance < 0 || distance >= data.sprhs * 2) {
    p_playerwk->u.play.cddat.ride = 0;
    *p_plride = false;
    return HITCHK_COLI_NONE;
  }
  MvSonicOnSlope(data.xposi);
  return HITCHK_COLI_TOP;
}


SKC_hitchk_result hitchk_offset(SKC_sprite_status* p_actwk, SKC_hitchk_data data) {
  SKC_hitchk_result result;
  bool plride = p_actwk->u.obj.cddat.plride;
  bool plpush = p_actwk->u.obj.cddat.plpush;
  result.plcoli[0] = plhitchk_offset(p_actwk, &g_ram.actwk[0], data, &plride, &plpush);
  p_actwk->u.obj.cddat.plride = plride;
  p_actwk->u.obj.cddat.plpush = plpush;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  bool pl2push = p_actwk->u.obj.cddat.pl2push;
  result.plcoli[1] = plhitchk_offset(p_actwk, &g_ram.actwk[1], data, &pl2ride, &pl2push);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  p_actwk->u.obj.cddat.pl2push = pl2push;
  return result;
}


static SKC_hitchk_coli plhitchk_offset(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plride, bool* p_plpush) {
  if (!*p_plride) {
    return plhitchk_offset_chk_coli(p_actwk, p_playerwk, data, p_plpush);
  }
  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if (p_playerwk->u.play.cddat.jump == 1 || distance < 0 || distance >= data.sprhs * 2) {
    p_playerwk->u.play.cddat.ride = 0;
    p_playerwk->u.play.cddat.jump = 1;
    *p_plride = false;
  }
  else {
    short yposi = fp16_get_integer(p_actwk->yposi)
                - (short)data.sprvs_air + (short)data.sprvs_ground - (short)p_playerwk->sprvsize;
    fp16_set_integer(&p_playerwk->yposi, yposi);
    short xoffset = data.xposi - fp16_get_integer(p_actwk->xposi);
    fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - xoffset);
  }
  return HITCHK_COLI_NONE;
}

static SKC_hitchk_coli plhitchk_offset_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush) {
  SKC_hitchk_distances distances = { 0, 0, 0, 0, 0, 0 };
  distances.left_edge = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if (distances.left_edge < 0 || distances.left_edge > data.sprhs * 2) {
    return chk_push(p_playerwk, p_plpush);
  }
  distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
  distances.max_top_coli = fp16_get_integer(p_playerwk->yposi)
                         - (fp16_get_integer(p_actwk->yposi) + (short)data.sprvs_ground)
                         + 4
                         + distances.max_top;
  distances.min_bottom = distances.max_top * 2;
  if (distances.max_top_coli < 0 || distances.max_top_coli >= distances.max_top * 2) {
    return chk_push(p_playerwk, p_plpush);
  }
  return chk_bounds(p_actwk, p_playerwk, data, distances, p_plpush);
}


static SKC_hitchk_coli plhitchk_slope_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, signed char* p_slope_heights, bool* p_plpush) {
  SKC_hitchk_distances distances = { 0, 0, 0, 0, 0, 0 };
  distances.left_edge = p_playerwk->xposi - p_actwk->xposi + (short)data.sprhs;
  if (distances.left_edge < 0 || distances.left_edge > data.sprhs * 2) {
    return chk_push(p_playerwk, p_plpush);
  }

  short slope_pos = distances.left_edge;
  if (p_actwk->actflg.hflip == 1) {
    slope_pos = -slope_pos - 1 + (short)data.sprhs * 2;
  }
  slope_pos /= 2;
  distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
  distances.max_top_coli = fp16_get_integer(p_playerwk->yposi)
                         - (fp16_get_integer(p_actwk->yposi) - (p_slope_heights[slope_pos] - p_slope_heights[0]))
                         + 4
                         + distances.max_top;
  distances.min_bottom = distances.max_top * 2;
  if (distances.max_top_coli < 0 || distances.max_top_coli >= distances.min_bottom) {
    return chk_push(p_playerwk, p_plpush);
  }
  return chk_bounds(p_actwk, p_playerwk, data, distances, p_plpush);
}


static SKC_hitchk_coli plhitchk_chk_coli(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush) {
  if (p_actwk->actflg.onscreen == 0) {
    return chk_push(p_playerwk, p_plpush);
  }
  return plhitchk_chk_coli_skip_onscreen(p_actwk, p_playerwk, data, p_plpush);
}


SKC_hitchk_coli plhitchk_chk_coli_skip_onscreen(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, bool* p_plpush) {
  SKC_hitchk_distances distances = { 0, 0, 0, 0, 0, 0 };
  distances.left_edge = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + (short)data.sprhs;
  if ((unsigned short)distances.left_edge > data.sprhs * 2) {
    return chk_push(p_playerwk, p_plpush);
  }
  unsigned char min_bottom_distance = 0;
  if (g_ram.reverse_gravity_flag != 0) {
    distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
    distances.max_top_coli = -(fp16_get_integer(p_playerwk->yposi)
                           - fp16_get_integer(p_actwk->yposi))
                           + 4
                           + distances.max_top;
    distances.max_top_coli %= 4096;
    distances.min_bottom = p_playerwk->u.play.height + data.sprvs_air + distances.max_top;
    if ((unsigned short)distances.max_top_coli >= distances.min_bottom) {
      return chk_push(p_playerwk, p_plpush);
    }
  }
  else {
    distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
    distances.max_top_coli = fp16_get_integer(p_playerwk->yposi)
                           - fp16_get_integer(p_actwk->yposi)
                           + 4
                           + distances.max_top;
    distances.max_top_coli %= 4096;
    distances.min_bottom = p_playerwk->u.play.height + data.sprvs_air + distances.max_top;
    if ((unsigned short)distances.max_top_coli >= distances.min_bottom) {
      return chk_push(p_playerwk, p_plpush);
    }
  }
  return chk_bounds(p_actwk, p_playerwk, data, distances, p_plpush);
}


static SKC_hitchk_coli chk_bounds(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, SKC_hitchk_distances distances, bool* p_plpush) {
  if (BIT_IS_SET(p_playerwk->u.play.control_bitfield, 7)) {
    return chk_push(p_playerwk, p_plpush);
  }
  if (p_playerwk->r_no >= 6 || g_ram.editmode != 0) {
    return HITCHK_COLI_NONE;
  }
  if (data.sprhs < (unsigned short)distances.left_edge) { // Player is right of object.
    distances.nearest_edge_hori = distances.left_edge - (short)data.sprhs * 2;
  }
  else { // Player is left of object.
    distances.nearest_edge_hori = distances.left_edge;
  }
  if (distances.max_top < distances.max_top_coli) { // Player is below object.
    distances.nearest_edge_vert = distances.max_top_coli - 4 - distances.min_bottom;
  }
  else { // Player is above object.
    distances.nearest_edge_vert = distances.max_top_coli;
  }
  if (abs(distances.nearest_edge_hori) > abs(distances.nearest_edge_vert) || abs(distances.nearest_edge_vert) <= 4) {
    chk_planes(p_actwk, p_playerwk, distances, p_plpush);
  }
  return chk_sides(p_playerwk, distances, p_plpush);
}


static SKC_hitchk_coli chk_sides(SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances, bool* p_plpush) {
  if (distances.nearest_edge_hori != 0) {
    if (distances.nearest_edge_hori >= 0 && p_playerwk->xspeed >= 0 // Player is inside left side of object.
        || distances.nearest_edge_hori < 0 && p_playerwk->xspeed < 0) { // Player is inside right side of object.
      p_playerwk->mspeed = 0;
      p_playerwk->xspeed = 0;
      if (BIT_IS_SET(p_playerwk->u.play.eventflag, 7)) {
        SET_BIT(p_playerwk->u.play.eventflag, 6);
      }
    }
  }
  fp16_set_integer(&p_playerwk->xposi, fp16_get_integer(p_playerwk->xposi) - distances.nearest_edge_hori);
  if (p_playerwk->u.play.cddat.jump == 0) {
    *p_plpush = true;
    p_playerwk->u.play.cddat.push = 1;
    return HITCHK_COLI_SIDE;
  }
  else {
    clear_push(p_playerwk, p_plpush);
  }
  return HITCHK_COLI_NONE;
}


static SKC_hitchk_coli chk_push(SKC_sprite_status* p_playerwk, bool* p_plpush) {
  if (!*p_plpush) {
    return HITCHK_COLI_NONE;
  }
  if (p_playerwk->mstno != 2 && p_playerwk->mstno != 9) {
    p_playerwk->mstno = 0;
    p_playerwk->mstrestart = 1;
  }
  return clear_push(p_playerwk, p_plpush);
}


static SKC_hitchk_coli clear_push(SKC_sprite_status* p_playerwk, bool* p_plpush) {
  *p_plpush = false;
  p_playerwk->u.play.cddat.push = 0;
  return HITCHK_COLI_NONE;
}


static SKC_hitchk_coli chk_planes(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances, bool* p_plpush) {
  if (distances.nearest_edge_vert >= 0) { // Player is inside top of object.
    if ((unsigned short)distances.nearest_edge_vert < 16) {
      return pop_up(p_actwk, p_playerwk, distances);
    }
    return chk_push(p_playerwk, p_plpush);
  }
  else { // Player is inside bottom of object.
    if (p_playerwk->u.play.cddat.jump == 0) {
      if (p_playerwk->yspeed == 0) {
        return crush(p_playerwk, distances, p_plpush);
      }
      if (p_playerwk->yspeed >= 0 || distances.nearest_edge_vert >= 0) {
        return no_pop(p_playerwk);
      }
    }
    else {
      p_playerwk->mspeed = 0;
    }
    return pop_down(p_playerwk, distances);
  }
}


static SKC_hitchk_coli pop_down(SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances) {
  if (g_ram.reverse_gravity_flag != 0) {
    distances.nearest_edge_vert = -distances.nearest_edge_vert;
  }
  fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - distances.nearest_edge_vert);
  p_playerwk->yspeed = 0;
  return no_pop(p_playerwk);
}


static SKC_hitchk_coli no_pop(SKC_sprite_status* p_playerwk) {
  if (BIT_IS_SET(p_playerwk->u.play.eventflag, 7)) {
    SET_BIT(p_playerwk->u.play.eventflag, 5);
  }
  return HITCHK_COLI_NONE;
}


static SKC_hitchk_coli crush(SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances, bool* p_plpush) {
  if (p_playerwk->u.play.cddat.jump) {
    return no_pop(p_playerwk);
  }
  if (abs(distances.nearest_edge_hori) < 16) {
    return chk_sides(p_playerwk, distances, p_plpush);
  }
  playdieset(p_playerwk);
  return HITCHK_COLI_BOTTOM;
}


static SKC_hitchk_coli pop_up(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_distances distances) {
  distances.nearest_edge_vert -= 4;
  short distance = (short)p_actwk->sprhs + fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi);
  if (distance >= 0 && distance >= p_actwk->sprhs * 2) {
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - 1);
    if (g_ram.reverse_gravity_flag != 0) {
      distances.nearest_edge_vert = -distances.nearest_edge_vert;
      fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) + 2);
    }
    fp16_set_integer(&p_playerwk->yposi, fp16_get_integer(p_playerwk->yposi) - distances.nearest_edge_vert);
    if (p_playerwk->yspeed >= 0) {
      RideObject_SetRide(p_actwk, p_playerwk);
      return HITCHK_COLI_TOP;
    }
  }
  return HITCHK_COLI_NONE;
}
