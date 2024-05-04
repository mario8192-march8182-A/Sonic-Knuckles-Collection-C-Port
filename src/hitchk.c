#include "globals.h"
#include "macros.h"
#include "util.h"
#include "hitchk.h"
#include "004xxxxx.h"
static hitchk_results plhitchk_doubleslope(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit);
static hitchk_results plhitchk_bryuka(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit);
static hitchk_results plhitchk_offset(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit);
static hitchk_results plhitchk_offset_chk_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit);
static hitchk_results plhitchk_chk_slope_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit);
static hitchk_results plhitchk_chk_doubleslope_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit);
static hitchk_results plhitchk_chk_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit);
static hitchk_results plhitchk_chk_bounds(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, hitchk_distances distances, unsigned char cddatbit);
static hitchk_results plhitchk_chk_sides(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit);
static hitchk_results plhitchk_chk_push(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char cddatbit);
static hitchk_results plhitchk_clear_push(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char cddatbit);
static hitchk_results plhitchk_no_coli(sprite_status* p_actwk);
static hitchk_results plhitchk_chk_planes(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit);
static hitchk_results plhitchk_pop_down(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit);
static hitchk_results plhitchk_no_pop(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit);
static hitchk_results plhitchk_crush(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit);
static hitchk_results plhitchk_pop_up(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit);


hitchk_results hitchk(sprite_status* p_actwk, hitchk_data data) {
  hitchk_results results = plhitchk(p_actwk, &actwk[0], data, 3);
  if (BIT_7_IS_SET(actwk[1].actflg)) {
    hitchk_results results2 = plhitchk(p_actwk, &actwk[1], data, 4);
    results.plcoli += results2.plcoli;
  }
  return results;
}


hitchk_results plhitchk(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, cddatbit)) {
    return plhitchk_chk_coli(p_actwk, p_playerwk, data, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  bool on_platform = false;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0 && distance < width) { // unsigned
      on_platform = true;
    }
  }
  if (!on_platform) {
    CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
    SET_BIT(p_playerwk->cddat1, CD_JUMP);
    CLEAR_BIT(p_actwk->cddat1, cddatbit);
  }
  else {
    MvSonicOnPtfm(data.xposi);
  }
  hitchk_results results = { 0, 0 };
  return results;
}


hitchk_results hitchk2(sprite_status* p_actwk, hitchk_data data) {
  hitchk_results results = plhitchk2(p_actwk, &actwk[0], data, 3);
  hitchk_results results2 = plhitchk2(p_actwk, &actwk[1], data, 4);
  results.plcoli += results2.plcoli;
  return results;
}


hitchk_results plhitchk2(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, cddatbit)) {
    return plhitchk_chk_coli2(p_actwk, p_playerwk, data, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  bool on_platform = false;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0 && distance < width) { // unsigned
      on_platform = true;
    }
  }
  if (!on_platform) {
    CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
    SET_BIT(p_playerwk->cddat1, CD_JUMP);
    CLEAR_BIT(p_actwk->cddat1, cddatbit);
  }
  else {
    MvSonicOnPtfm(data.xposi);
  }
  hitchk_results results = { 0, 0 };
  return results;
}


hitchk_results hitchk_slope(sprite_status* p_actwk, hitchk_data data, signed char* slope_heights) {
  hitchk_results results = plhitchk_slope(p_actwk, &actwk[0], data, slope_heights, 3);
  hitchk_results results2 = plhitchk_slope(p_actwk, &actwk[1], data, slope_heights, 4);
  results.plcoli += results2.plcoli;
  return results;
}


hitchk_results plhitchk_slope(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, cddatbit)) {
    return plhitchk_chk_slope_coli(p_actwk, p_playerwk, data, slope_heights, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  bool on_slope = false;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0 && distance < width) { // unsigned
      on_slope = true;
    }
  }
  hitchk_results results = { 0, 0 };
  if (!on_slope) {
    CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
    SET_BIT(p_playerwk->cddat1, CD_JUMP);
    CLEAR_BIT(p_actwk->cddat1, cddatbit);
  }
  else {
    MvSonicOnSlope(data.xposi);
    SET_BIT(results.plcoli, cddatbit + 1);
  }
  return results;
}


hitchk_results hitchk_doubleslope(sprite_status* p_actwk, hitchk_data data, signed char* slope_heights) {
  hitchk_results results = plhitchk_doubleslope(p_actwk, &actwk[0], data, slope_heights, 3);
  hitchk_results results2 = plhitchk_doubleslope(p_actwk, &actwk[1], data, slope_heights, 4);
  results.plcoli += results2.plcoli;
  return results;
}


static hitchk_results plhitchk_doubleslope(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, cddatbit)) {
    return plhitchk_chk_doubleslope_coli(p_actwk, p_playerwk, data, slope_heights, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  bool on_slope = false;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0 && distance < width) { // unsigned
      on_slope = true;
    }
  }
  if (!on_slope) {
    CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
    SET_BIT(p_playerwk->cddat1, CD_JUMP);
    CLEAR_BIT(p_actwk->cddat1, cddatbit);
  }
  else {
    MvSonicOnDoubleSlope(data.xposi);
  }
  hitchk_results results = { 0, 0 };
  return results;
}


hitchk_results hitchk_bryuka(sprite_status* p_actwk, hitchk_data data, signed char* slope_heights) {
  hitchk_results results = plhitchk_bryuka(p_actwk, &actwk[0], data, slope_heights, 3);
  hitchk_results results2 = plhitchk_bryuka(p_actwk, &actwk[1], data, slope_heights, 4);
  results.plcoli += results2.plcoli;
  return results;
}


static hitchk_results plhitchk_bryuka(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, cddatbit)) {
    return plhitchk_chk_slope_coli(p_actwk, p_playerwk, data, slope_heights, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  bool on_slope = false;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0 && distance < width) { // unsigned
      on_slope = true;
    }
  }
  hitchk_results results = { 0, 0 };
  if (!on_slope) {
    CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
    CLEAR_BIT(p_actwk->cddat1, cddatbit);
  }
  else {
    MvSonicOnSlope(data.xposi);
    SET_BIT(cddatbit, results.plcoli + 1);
  }
  return results;
}


hitchk_results hitchk_offset(sprite_status* p_actwk, hitchk_data data) {
  hitchk_results results = plhitchk_offset(p_actwk, &actwk[0], data, 3);
  hitchk_results results2 = plhitchk_offset(p_actwk, &actwk[0], data, 4);
  results.plcoli += results2.plcoli;
  return results;
}


static hitchk_results plhitchk_offset(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, cddatbit)) {
    return plhitchk_offset_chk_coli(p_actwk, p_playerwk, data, cddatbit);
  }
  bool on_platform = false;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0) {
      unsigned char width = data.sprhs * 2;
      if (distance < width) { // unsigned
        on_platform = true;
      }
    }
  }
  if (!on_platform) {
    CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
    SET_BIT(p_playerwk->cddat1, CD_JUMP);
    CLEAR_BIT(p_actwk->cddat1, cddatbit);
  }
  else {
    short yposi = LONG_HIGH(p_actwk->yposi) - data.sprvs_air + data.sprvs_ground - p_playerwk->sprvsize;
    util__assign_high(&p_playerwk->yposi, yposi);
    short xoffset = data.xposi - LONG_HIGH(p_actwk->xposi);
    p_playerwk->xposi -= SHORT_TO_LONG_HIGH(xoffset);
  }
  hitchk_results results = { 0, 0 };
  return results;
}

static hitchk_results plhitchk_offset_chk_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit) {
  short left_edge_distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
  if (left_edge_distance < 0) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  if (left_edge_distance > width) { // unsigned
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  hitchk_distances distances = { left_edge_distance, 0, 0, 0 };
  short yposi = LONG_HIGH(p_actwk->yposi) + data.sprvs_ground;
  distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
  distances.max_top_coli = LONG_HIGH(p_playerwk->yposi) - yposi + 4 + distances.max_top;
  if (distances.max_top_coli < 0) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  distances.min_bottom = distances.max_top * 2;
  if (distances.max_top_coli >= distances.min_bottom) { // unsigned
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  return plhitchk_chk_bounds(p_actwk, p_playerwk, data, distances, cddatbit);
}


static hitchk_results plhitchk_chk_slope_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit) {
  short left_edge_distance = p_playerwk->xposi - p_actwk->xposi + data.sprhs;
  if (left_edge_distance < 0) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  if (left_edge_distance > width) { // unsigned
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  hitchk_distances distances = { left_edge_distance, 0, 0, 0 };
  short unknown_distance = distances.left_edge;
  if (IS_HFLIP(p_actwk->actflg)) {
    unknown_distance = ~unknown_distance;
    unknown_distance += width;
  }
  unknown_distance /= 2;
  short shift = slope_heights[unknown_distance] - slope_heights[0];
  short yposi = LONG_HIGH(p_actwk->yposi) - shift;
  distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
  distances.max_top_coli = LONG_HIGH(p_playerwk->yposi) - yposi + 4 + distances.max_top;
  if (distances.max_top_coli < 0) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  distances.min_bottom = distances.max_top * 2;
  if (distances.max_top_coli >= distances.min_bottom) { // unsigned
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  return plhitchk_chk_bounds(p_actwk, p_playerwk, data, distances, cddatbit);
}


static hitchk_results plhitchk_chk_doubleslope_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, signed char* slope_heights, unsigned char cddatbit) {
  short left_edge_distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
  if (left_edge_distance < 0) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  unsigned char width = data.sprhs * 2;
  if (left_edge_distance > width) { // unsigned
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  hitchk_distances distances = { left_edge_distance, 0, 0, 0 };
  short unknown_distance = distances.left_edge;
  if (IS_HFLIP(p_actwk->actflg)) {
    unknown_distance = ~unknown_distance;
    unknown_distance += width;
  }
  unknown_distance &= -2;
  short yposi = LONG_HIGH(p_actwk->yposi) - slope_heights[unknown_distance];
  distances.max_top_coli = LONG_HIGH(p_playerwk->yposi) - yposi + p_playerwk->sprvsize + 4;
  if (distances.max_top_coli < 0) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  distances.max_top = slope_heights[unknown_distance + 1] + p_playerwk->sprvsize;
  distances.min_bottom = distances.max_top + p_playerwk->sprvsize;
  if (distances.max_top_coli >= util__to_unsigned(distances.min_bottom)) { // unsigned
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  return plhitchk_chk_bounds(p_actwk, p_playerwk, data, distances, cddatbit);
}


static hitchk_results plhitchk_chk_coli(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit) {
  if (!IS_ONSCREEN(p_actwk->actflg)) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  return plhitchk_chk_coli2(p_actwk, p_playerwk, data, cddatbit);
}


hitchk_results plhitchk_chk_coli2(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char cddatbit) {
  short left_edge_distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
  unsigned char width = data.sprhs * 2;
  if (util__to_unsigned(left_edge_distance) > width) { // unsigned
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  hitchk_distances distances = { left_edge_distance, 0, 0, 0 };
  unsigned char min_bottom_distance = 0;
  if (reverse_gravity_flag != 0) {
    distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
    short relative_position = LONG_HIGH(p_playerwk->yposi) - LONG_HIGH(p_actwk->yposi);
    relative_position = -relative_position;
    distances.max_top_coli = relative_position + 4 + distances.max_top;
    distances.max_top_coli %= 4096;
    distances.min_bottom = p_playerwk->actfree.player.height + data.sprvs_air + distances.max_top;
    if (util__to_unsigned(distances.max_top_coli) >= util__to_unsigned(distances.min_bottom)) { // unsigned
      return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
    }
  }
  else {
    distances.max_top = data.sprvs_air + p_playerwk->sprvsize;
    short relative_position = LONG_HIGH(p_playerwk->yposi) - LONG_HIGH(p_actwk->yposi);
    distances.max_top_coli = relative_position + 4 + distances.max_top;
    distances.max_top_coli %= 4096;
    distances.min_bottom = p_playerwk->actfree.player.height + data.sprvs_air + distances.max_top;
    if (util__to_unsigned(distances.max_top_coli) >= util__to_unsigned(distances.min_bottom)) { // unsigned
      return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
    }
  }
  return plhitchk_chk_bounds(p_actwk, p_playerwk, data, distances, cddatbit);
}


static hitchk_results plhitchk_chk_bounds(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, hitchk_distances distances, unsigned char cddatbit) {
  if (BIT_7_IS_SET(p_actwk->actfree.player.control_bitfield)) {
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  if (p_playerwk->r_no >= 6 || edit_r_no != 0) { // unsigned
    return plhitchk_no_coli(p_actwk);
  }
  hitchk_edge_distances edge_distances = {
    distances.left_edge,
    distances.left_edge,
    distances.max_top_coli,
    distances.max_top_coli
  };
  if (data.sprhs < util__to_unsigned(edge_distances.horizontal)) { // unsigned
    edge_distances.horizontal -= data.sprhs * 2;
    edge_distances.abs_horizontal = edge_distances.horizontal;
    edge_distances.abs_horizontal = -edge_distances.abs_horizontal;
  }
  if (distances.max_top < util__to_unsigned(edge_distances.vertical)) { // unsigned
    edge_distances.vertical -= 4;
    edge_distances.vertical -= distances.min_bottom;
    edge_distances.abs_vertical = edge_distances.vertical;
    edge_distances.abs_vertical = -edge_distances.abs_vertical;
  }
  if (edge_distances.abs_horizontal > edge_distances.abs_vertical || edge_distances.abs_vertical <= 4) { // unsigned
    plhitchk_chk_planes(p_actwk, p_playerwk, edge_distances, cddatbit);
  }
  return plhitchk_chk_sides(p_actwk, p_playerwk, edge_distances, cddatbit);
}


static hitchk_results plhitchk_chk_sides(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit) {
  if (edge_distances.horizontal != 0) {
    bool stop = false;
    if (edge_distances.horizontal >= 0) {
      if (p_playerwk->xspeed >= 0) {
        stop = true;
      }
    }
    else {
      if (p_playerwk->xspeed < 0) {
        stop = true;
      }
    }
    if (stop) {
      p_playerwk->mspeed = 0;
      p_playerwk->xspeed = 0;
      if (BIT_7_IS_SET(p_playerwk->actfree.player.eventflag)) {
        SET_BIT_6(p_playerwk->actfree.player.eventflag);
      }
    }
  }
  p_playerwk->xposi -= SHORT_TO_LONG_HIGH(edge_distances.horizontal);
  hitchk_results results = { 0, 0 };
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    SET_BIT(p_actwk->cddat1, cddatbit + 2);
    SET_BIT(p_playerwk->cddat1, CD_PUSH);
    SET_BIT(results.plcoli, cddatbit - 3);
    results.colitype = 1;
  }
  else {
    plhitchk_clear_push(p_actwk, p_playerwk, cddatbit);
    SET_BIT(results.plcoli, cddatbit - 3);
    results.colitype = 1;
  }
  return results;
}


static hitchk_results plhitchk_chk_push(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char cddatbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, cddatbit + 2)) {
    return plhitchk_no_coli(p_actwk);
  }
  if (p_playerwk->mstno != 2 && p_playerwk->mstno != 9) {
    p_playerwk->mstno = 0;
    p_playerwk->restart = 1;
  }
  return plhitchk_clear_push(p_actwk, p_playerwk, cddatbit);
}


static hitchk_results plhitchk_clear_push(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char cddatbit) {
  CLEAR_BIT(p_actwk->cddat1, cddatbit + 2);
  CLEAR_BIT(p_playerwk->cddat1, CD_PUSH);
  return plhitchk_no_coli(p_actwk);
}


static hitchk_results plhitchk_no_coli(sprite_status* p_actwk) {
  hitchk_results results = { 0, 0 };
  return results;
}


static hitchk_results plhitchk_chk_planes(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit) {
  if (edge_distances.vertical >= 0) {
    if (util__to_unsigned(edge_distances.vertical) < 16) { // unsigned
      return plhitchk_pop_up(p_actwk, p_playerwk, edge_distances, cddatbit);
    }
    return plhitchk_chk_push(p_actwk, p_playerwk, cddatbit);
  }
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    if (p_playerwk->yspeed == 0) {
      return plhitchk_crush(p_actwk, p_playerwk, edge_distances, cddatbit);
    }
    if (p_playerwk->yspeed >= 0 || edge_distances.vertical >= 0) {
      return plhitchk_no_pop(p_actwk, p_playerwk, edge_distances, cddatbit);
    }
  }
  else {
    p_playerwk->mspeed = 0;
  }
  return plhitchk_pop_down(p_actwk, p_playerwk, edge_distances, cddatbit);
}


static hitchk_results plhitchk_pop_down(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit) {
  if (reverse_gravity_flag != 0) {
    edge_distances.vertical = -edge_distances.vertical;
  }
  p_playerwk->yposi -= SHORT_TO_LONG_HIGH(edge_distances.vertical);
  p_playerwk->yspeed = 0;
  return plhitchk_no_pop(p_actwk, p_playerwk, edge_distances, cddatbit);
}


static hitchk_results plhitchk_no_pop(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit) {
  if (BIT_7_IS_SET(p_playerwk->actfree.player.eventflag)) {
    SET_BIT_5(p_playerwk->actfree.player.eventflag);
  }
  hitchk_results results = { 0, 0 };
  SET_BIT(results.plcoli, cddatbit - 1);
  results.colitype = -2;
  return results;
}


static hitchk_results plhitchk_crush(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit) {
  if (BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    return plhitchk_no_pop(p_actwk, p_playerwk, edge_distances, cddatbit);
  }
  if (edge_distances.abs_horizontal < 16) { // unsigned
    return plhitchk_chk_sides(p_actwk, p_playerwk, edge_distances, cddatbit);
  }
  playdieset(p_playerwk, 0);
  hitchk_results results = { 0, 0 };
  SET_BIT(results.plcoli, cddatbit - 1);
  results.colitype = -2;
  return results;
}


static hitchk_results plhitchk_pop_up(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_edge_distances edge_distances, unsigned char cddatbit) {
  hitchk_results results = { 0, 0 };
  edge_distances.vertical -= 4;
  unsigned char width = p_actwk->sprhs * 2;
  short relative_pos = p_actwk->sprhs + LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi);
  if (relative_pos >= 0 && relative_pos >= width) { // unsigned
    p_playerwk->yposi -= SHORT_TO_LONG_HIGH(1);
    if (reverse_gravity_flag != 0) {
      edge_distances.vertical = -edge_distances.vertical;
      p_playerwk->yposi += SHORT_TO_LONG_HIGH(2);
    }
    p_playerwk->yposi -= SHORT_TO_LONG_HIGH(edge_distances.vertical);
    if (p_playerwk->yspeed >= 0) {
      RideObject_SetRide(p_actwk, p_playerwk);
      SET_BIT(results.plcoli, cddatbit + 1);
      results.colitype = -1;
      return results;
    }
  }
  return results;
}
