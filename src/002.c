#include "globals.h"
#include "macros.h"
#include "util.h"
#include "002.h"
#include "004xxxxx.h"
static int chk_tpg_next(sprite_status* p_actwk, signed char pg, signed char* p_pg_data, unsigned char patcnt);
static void chk_framein__chk(sprite_status* p_actwk);


// skdisasm label: CreateChild6_Simple
sprite_status* set_act05(sprite_status* p_actwk, set_act05_data* p_data) {
  sprite_status* p_new_actwk;
  short i = 0;
  short cnt = p_data->cnt;

  do {
    short slot_cnt;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) return 0;

    p_new_actwk->actfree.dynamic.oya = p_actwk - actwk;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->r_ptr = p_data->act;
    p_new_actwk->userflag1 = i;
    p_new_actwk->xposi = LONG_HIGH(p_actwk->xposi) + LONG_LOW(p_new_actwk->xposi);
    p_new_actwk->yposi = LONG_HIGH(p_actwk->yposi) + LONG_LOW(p_new_actwk->yposi);
    i += 2;
    --cnt;
  } while (cnt != -1);

  return p_new_actwk;
}


// skdisasm labels: Animate_RawMultiDelay, Animate_RawNoSSTMultiDelay
int time_pg(sprite_status* p_actwk, signed char* p_pg_data) {
  --p_actwk->pattim;
  signed char pattim = p_actwk->pattim; // conversion so it can be negative
  if (pattim >= 0) return 0;
  p_actwk->patcnt += 2;
  signed char pg = p_pg_data[p_actwk->patcnt];
  if (pg < 0) return chk_tpg_next(p_actwk, pg, p_pg_data, p_actwk->patcnt);
  p_actwk->patno = pg;
  p_actwk->pattim = p_pg_data[p_actwk->patcnt + 1];
  return 1;
}


static int chk_tpg_next(sprite_status* p_actwk, signed char pg, signed char* p_pg_data, unsigned char patcnt) {
  int ret = 0;
  pg = -pg;

  switch (pg) {
    case PG_CONTROL_NULL:
      break;
    case PG_CONTROL_NEXT:
      pg = p_pg_data[patcnt + 1];
      p_pg_data = &p_pg_data[pg];
      p_actwk->actfree.dynamic.pg_data_ptr = p_pg_data;
      // fall-through
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[0];
      p_actwk->pattim = p_pg_data[1];
      ret = 1;
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      p_actwk->actfree.dynamic.callback_ptr(p_actwk);
      ret = -1;
      break;
  }

  return ret;
}


void dec_timer(sprite_status* p_actwk) {
  --p_actwk->actfree.dynamic.timer;
  if (p_actwk->actfree.dynamic.timer < 0) {
    p_actwk->actfree.dynamic.callback_ptr(p_actwk);
  }
}


// skdisasm label: Child_Draw_Sprite
void chk_oya_die0(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &actwk[p_actwk->actfree.dynamic.oya];
  if (BIT_7_IS_SET(p_parentwk->cddat1)) {
    set_emy_fout0(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


// skdisasm label: Child_Remember_Draw_Sprite
void chk_oya_diew0(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &actwk[p_actwk->actfree.dynamic.oya];
  if (!BIT_7_IS_SET(p_parentwk->cddat1)) {
    actionsub(p_actwk);
  }
  else {
    clr_wchg_bit(p_actwk);
    set_emy_fout0(p_actwk);
  }
}


// skdisasm label: Find_SonicTails
void chk_distance(sprite_status* p_actwk, bool* pl_is_right, bool* pl_is_below, short* pl_x_distance, short* pl_y_distance) {
  *pl_is_right = false;
  *pl_is_below = false;
  *pl_x_distance = LONG_HIGH_TO_SHORT(p_actwk->xposi) - LONG_HIGH_TO_SHORT(actwk[0].xposi);
  if (*pl_x_distance < 0) {
    *pl_x_distance = -*pl_x_distance;
    *pl_is_right = true;
  }
  short pl2_x_distance = LONG_HIGH_TO_SHORT(p_actwk->xposi) - LONG_HIGH_TO_SHORT(actwk[1].xposi);
  bool pl2_is_right = false;
  if (pl2_x_distance < 0) {
    pl2_x_distance = -pl2_x_distance;
    pl2_is_right = true;
  }
  sprite_status* p_playerwk = &actwk[0];
  if (*pl_x_distance > pl2_x_distance) {
    p_playerwk = &actwk[1];
    *pl_is_right = pl2_is_right;
    *pl_x_distance = pl2_x_distance;
  }
  *pl_y_distance = LONG_HIGH_TO_SHORT(p_actwk->yposi) - LONG_HIGH_TO_SHORT(p_playerwk->yposi);
  if (*pl_y_distance < 0) {
    *pl_y_distance = -*pl_y_distance;
    *pl_is_below = true;
  }
}


// skdisasm label: Change_FlipXWithVelocity
void chk_emy_revs(sprite_status* p_actwk) {
  CLEAR_BIT_0(p_actwk->actflg);
  if (p_actwk->xspeed < 0) return;
  SET_BIT_0(p_actwk->actflg);
}


// skdisasm label: MoveSprite_LightGravity
void speedsetg20(sprite_status* p_actwk) {
  speedsetg(p_actwk, 32);
}


void speedsetg(sprite_status* p_actwk, short gravity) {
  p_actwk->xposi += p_actwk->xspeed * 256;
  short yspeed = p_actwk->yspeed;
  p_actwk->yspeed += gravity;
  p_actwk->yposi += yspeed * 256;
}


// skdisasm label: SetUp_ObjAttributesSlotted
void emy_wrt_init(sprite_status* p_actwk, wrt_init_data* p_data) {
  unsigned short bit = 0;
  short cnt = p_data->cnt; // this conversion from unsigned to signed should be safe
  unsigned short sproffset = p_data->sproffset;
  unsigned short offset_increase = p_data->offset_increase;
  unsigned char flags = emy_wrt_flg[p_data->flg_index];
  if (flags == 0) goto ok;

  do {
    bool bit_0_clear = !BIT_0_IS_SET(flags);
    flags >>= 1;
    if (bit_0_clear) goto ok;
    ++bit;
    sproffset += offset_increase;
    --cnt;
  } while (cnt != -1);

  p_actwk->r_ptr = 0;
  p_actwk->xposi = 0;
  p_actwk->yposi = 0;
  p_actwk->userflag1 = 0;
  p_actwk->actflg = 0;
  p_actwk->cddat1 = p_actwk->cddat2 = 0;
  return;

ok:
  SET_BIT(emy_wrt_flg[p_data->flg_index], bit);
  p_actwk->actfree.dynamic.wchg_bit = bit;
  p_actwk->actfree.dynamic.wrt_flg_index = p_data->flg_index;
  p_actwk->sproffset = sproffset;
  p_actwk->patbase = p_data->patbase;
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  SET_BIT_2(p_actwk->cddat1);
  p_actwk->actfree.dynamic.prev_patno = 255;
  SET_BIT_2(p_actwk->actflg);
  p_actwk->r_no += 2;
}


// skdisasm label: Perform_DPLC
void set_emy_wchg(sprite_status* p_actwk, wrt_data* p_data) {
  if (p_actwk->patno == p_actwk->actfree.dynamic.prev_patno) return;
  p_actwk->actfree.dynamic.prev_patno = p_actwk->patno;
  unsigned short vram_adr = (p_actwk->sproffset & 0x7FF) << 5;
  unsigned short* wrtpat = p_data->wrtpat[p_actwk->patno];
  short cnt = *wrtpat++; // this conversion from unsigned to signed should be safe

  do {
    unsigned short instruction = *wrtpat++;
    unsigned char* source = p_data->pat + ((instruction & 0xFFF0) << 1);
    unsigned short word_cnt = ((instruction & 0xF) + 1) * 16;
    unsigned short destination = vram_adr;
    vram_adr += word_cnt * 2;
    Copy_Data_To_VRAM(source, destination, word_cnt);
    --cnt;
  } while (cnt != -1);
}


// skdisasm label: Sprite_CheckDeleteTouch
void chk_emy_foutc0(sprite_status* p_actwk) {
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= scr_x_no;
  if (scr_xposi > 640) { // unsigned
    emy_fout(p_actwk);
  }
  else {
    Add_Object_To_Collision_Response_List(p_actwk);
    actionsub(p_actwk);
  }
}


void chk_emy_foutc3(sprite_status* p_actwk) {
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= scr_x_no;
  if (scr_xposi > 640) { // unsigned
    set_emy_fout0(p_actwk);
  }
  else {
    unsigned short scr_yposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->yposi));
    scr_yposi -= LONG_HIGH_TO_SHORT(scra_v_posit);
    if (scr_yposi > 512) { // unsigned
      set_emy_fout0(p_actwk);
    }
    else {
      Add_Object_To_Collision_Response_List(p_actwk);
      actionsub(p_actwk);
    }
  }
}


// skdisasm label: Sprite_CheckDelete
void chk_emy_fout0(sprite_status* p_actwk) {
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= scr_x_no;
  if (scr_xposi > 640) { // unsigned
    emy_fout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


void emy_fout(sprite_status* p_actwk) {
  if (p_actwk->actfree.dynamic.flagwork_index != 0) {
    CLEAR_BIT_7(flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
  }
  SET_BIT_7(p_actwk->cddat1);
  p_actwk->r_ptr = &frameout;
}


// skdisasm label: Obj_FlickerMove
void chk_break_fout(sprite_status* p_actwk) {
  speedset(p_actwk);
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= scr_x_no;
  if (scr_xposi > 640) {
    set_emy_fout01(p_actwk);
    return;
  }
  if (util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi) - LONG_HIGH_TO_SHORT(scra_v_posit) + 128) > 512) {
    set_emy_fout01(p_actwk);
    return;
  }
  bool bit_6_set = BIT_6_IS_SET(p_actwk->actfree.dynamic.status_bitfield);
  TOGGLE_BIT_6(p_actwk->actfree.dynamic.status_bitfield);
  if (bit_6_set) {
    actionsub(p_actwk);
  }
}


// skdisasm label: Sprite_CheckDelete2
void chk_emy_foutw0(sprite_status* p_actwk) {
  unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
  scr_xposi -= scr_x_no;
  if (scr_xposi > 640) { // unsigned
    wchg_fout(p_actwk);
  }
  else {
    actionsub(p_actwk);
  }
}


// skdisasm label: Go_Delete_SpriteSlotted
void wchg_fout(sprite_status* p_actwk) {
  if (p_actwk->actfree.dynamic.flagwork_index != 0) {
    CLEAR_BIT_7(flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
  }
  set_wchg_fout0(p_actwk);
}


// skdisasm label: Go_Delete_SpriteSlotted2
void set_wchg_fout0(sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  SET_BIT_7(p_actwk->cddat1);
  clr_wchg_bit(p_actwk);
}


// skdisasm label: Remove_From_TrackingSlot
void clr_wchg_bit(sprite_status* p_actwk) {
  CLEAR_BIT(emy_wrt_flg[p_actwk->actfree.dynamic.wrt_flg_index], p_actwk->actfree.dynamic.wchg_bit);
}


// skdisasm label: Sprite_CheckDeleteTouchSlotted
void chk_emy_foutwc0(sprite_status* p_actwk) {
  if (!BIT_7_IS_SET(p_actwk->actflg)) {
    unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
    scr_xposi -= scr_x_no;
    if (scr_xposi > 640) { // unsigned
      wchg_fout(p_actwk);
    }
    else {
      Add_Object_To_Collision_Response_List(p_actwk);
      actionsub(p_actwk);
    }
  }
  else {
    p_actwk->r_ptr = &frameout;
    clr_wchg_bit(p_actwk);
  }
}


// skdisasm label: Go_Delete_SpriteSlotted3
void wchg_die(sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  clr_wchg_bit(p_actwk);
}


// skdisasm label: Go_Delete_Sprite
void set_emy_fout0(sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  SET_BIT_7(p_actwk->cddat1);
}


// skdisasm label: Go_Delete_Sprite_3
void set_emy_fout01(sprite_status* p_actwk) {
  p_actwk->r_ptr = &frameout;
  SET_BIT_7(p_actwk->cddat1);
  SET_BIT_4(p_actwk->actfree.dynamic.status_bitfield);
}


// skdisasm label: Set_IndexedVelocity
void set_break_spd(sprite_status* p_actwk, unsigned char unknown) {
  static short speed_tbl[76] = {
     -256,  -256,
      256,  -256,
     -512,  -512,
      512,  -512,
     -768,  -512,
      768,  -512,
     -512,  -512,
        0,  -512,
    -1024,  -768,
     1024,  -768,
      768,  -768,
    -1024,  -768,
     1024,  -768,
     -512,  -512,
      512,  -512,
        0,  -256,
      -64, -1792,
     -128, -1792,
     -384, -1792,
     -256, -1792,
     -512, -1792,
     -640, -1792,
     -768, -1792,
        0,  -256,
     -256,  -256,
      256,  -256,
     -512,  -256,
      512,  -256,
     -512,  -512,
      512,  -512,
     -768,  -512,
      768,  -512,
     -768,  -768,
      768,  -768,
    -1024,  -768,
     1024,  -768,
     -512,  -768,
      512,  -768
  };

  unsigned char index = p_actwk->userflag1 * 2 + unknown;
  p_actwk->xspeed = speed_tbl[index];
  p_actwk->yspeed = speed_tbl[index + 1];
  if (BIT_0_IS_SET(p_actwk->actflg)) {
    p_actwk->xspeed = -p_actwk->xspeed;
  }
}


// skdisasm label: HurtCharacter_Directly
void set_pl_damage(sprite_status* p_attack_actwk, sprite_status* p_playerwk) {
  playdamageset(p_playerwk, p_attack_actwk);
}


unsigned short pl_wk_tbl[4] = {
  0, 0, 1, 1
};

// skdisasm label: Check_PlayerCollision
bool chk_emy_col(sprite_status* p_actwk, sprite_status** pp_coli_actwk) {
  if (p_actwk->colicnt == 0) return false;
  p_actwk->colicnt = 0;
  unsigned short coli_act_id = pl_wk_tbl[p_actwk->colicnt & 3];
  p_actwk->actfree.dynamic.ko = coli_act_id;
  *pp_coli_actwk = &actwk[coli_act_id];
  return true;
}


// skdisasm label: Check_PlayerInRange
sprite_status* chk_emy_colt(sprite_status* p_actwk, short* p_col_data) {
  sprite_status* p_playerwk = 0;
  short pl_xposi = LONG_HIGH_TO_SHORT(actwk[1].xposi);
  short pl_yposi = LONG_HIGH_TO_SHORT(actwk[1].yposi);
  short emy_range_left_x = LONG_HIGH_TO_SHORT(p_actwk->xposi);
  short emy_range_top_y = LONG_HIGH_TO_SHORT(p_actwk->yposi);
  emy_range_left_x += p_col_data[0];
  short emy_range_right_x = emy_range_left_x;
  emy_range_right_x += p_col_data[1];
  emy_range_top_y += p_col_data[2];
  short emy_range_bottom_y = emy_range_top_y;
  emy_range_bottom_y += p_col_data[3];
  p_playerwk = chk_emy_colt__col(&actwk[1], p_playerwk, pl_xposi, pl_yposi, emy_range_left_x, emy_range_top_y, emy_range_right_x, emy_range_bottom_y);
  pl_xposi = LONG_HIGH_TO_SHORT(actwk[0].xposi);
  pl_yposi = LONG_HIGH_TO_SHORT(actwk[0].yposi);
  p_playerwk = chk_emy_colt__col(&actwk[0], p_playerwk, pl_xposi, pl_yposi, emy_range_left_x, emy_range_top_y, emy_range_right_x, emy_range_bottom_y);
  return p_playerwk;
}


sprite_status* chk_emy_colt__col(sprite_status* p_playerwk_chk, sprite_status* p_playerwk_prev_chk, short pl_xposi, short pl_yposi, short emy_range_left_x, short emy_range_top_y, short emy_range_right_x, short emy_range_bottom_y) {
  if (util__to_unsigned(pl_xposi) < util__to_unsigned(emy_range_left_x)) return p_playerwk_prev_chk; // unsigned
  if (util__to_unsigned(pl_xposi) >= util__to_unsigned(emy_range_right_x)) return p_playerwk_prev_chk; // unsigned
  if (util__to_unsigned(pl_yposi) < util__to_unsigned(emy_range_top_y)) return p_playerwk_prev_chk; // unsigned
  if (util__to_unsigned(pl_yposi) >= util__to_unsigned(emy_range_bottom_y)) return p_playerwk_prev_chk; // unsigned
  return p_playerwk_chk;
}


// skdisasm: Obj_WaitOffscreen
void chk_framein(sprite_status* p_actwk, sprite_status_handler p_callback) {
  p_actwk->patbase = space_pt;
  SET_BIT_2(p_actwk->actflg);
  p_actwk->sprhs = 32;
  p_actwk->sprvs = 32;
  p_actwk->actfree.dynamic.callback_ptr = p_callback;
  p_actwk->r_ptr = &chk_framein__chk;
  chk_framein__chk(p_actwk);
}


static void chk_framein__chk(sprite_status* p_actwk) {
  if (!BIT_7_IS_SET(p_actwk->actflg)) {
    unsigned short scr_xposi = util__to_unsigned(LONG_HIGH_TO_SHORT(p_actwk->xposi)) & 0xFF80;
    scr_xposi -= scr_x_no;
    if (scr_xposi <= 640) { // unsigned
      actionsub(p_actwk);
    }
    else {
      if (p_actwk->actfree.dynamic.flagwork_index != 0) {
        CLEAR_BIT_7(flagwork[p_actwk->actfree.dynamic.flagwork_index - 1]);
      }
      frameout(p_actwk);
    }
  }
  else {
    p_actwk->r_ptr = p_actwk->actfree.dynamic.callback_ptr;
  }
}


void set_bane_jump(sprite_status* p_playerwk, short yspeed) {
  p_playerwk->yspeed = yspeed;
  CLEAR_BIT_3(p_playerwk->cddat1);
  p_playerwk->actfree.player.jump_status = 0;
  p_playerwk->actfree.player.roll_status = 0;
  p_playerwk->mstno = 16;
  p_playerwk->r_no = 2;
  soundset(177);
}
