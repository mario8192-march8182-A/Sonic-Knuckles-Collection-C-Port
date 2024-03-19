#include "globals.h"
#include "macros.h"
#include "util.h"
#include "002.h"
#include "004xxxxx.h"
static int chk_tpg_next(sprite_status* p_actwk, signed char pg, signed char* p_pg_data, unsigned char patcnt);


// skdisasm label: CreateChild6_Simple
void set_act05(sprite_status* p_actwk, set_act05_data* p_data) {
  sprite_status* p_new_actwk;
  short i = 0;
  short cnt = p_data->cnt;

  do {
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk);
    if (!created) return;

    SPRITE_STATUS_USHORT(p_new_actwk, OYA_ADR) = p_actwk - actwk;
    p_new_actwk->patbase = p_actwk->patbase;
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->r_ptr = p_data->act;
    p_new_actwk->userflag1 = i;
    p_new_actwk->xposi = LONG_HIGH(p_actwk->xposi) + LONG_LOW(p_new_actwk->xposi);
    p_new_actwk->yposi = LONG_HIGH(p_actwk->yposi) + LONG_LOW(p_new_actwk->yposi);
    i += 2;
    --cnt;
  } while (cnt != -1);
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
      SPRITE_STATUS_PSCHAR(p_actwk, 48) = p_pg_data;
    case PG_CONTROL_LOOP:
      p_actwk->patno = p_pg_data[0];
      p_actwk->pattim = p_pg_data[1];
      ret = 1;
      break;
    case PG_CONTROL_END:
      p_actwk->pattim = 0;
      SPRITE_STATUS_PHANDLER(p_actwk, 52)(p_actwk);
      ret = -1;
      break;
  }

  return ret;
}


// skdisasm label: Change_FlipXWithVelocity
void chk_emy_revs(sprite_status* p_actwk) {
  CLEAR_BIT_0(p_actwk->actflg);
  if (p_actwk->xspeed < 0) return;
  SET_BIT_0(p_actwk->actflg);
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
  emy_wrt_flg[p_data->flg_index] |= 1 << bit;
  SPRITE_STATUS_UCHAR(p_actwk, 59) = bit;
  SPRITE_STATUS_USHORT(p_actwk, 60) = p_data->flg_index;
  p_actwk->sproffset = sproffset;
  p_actwk->patbase = p_data->patbase;
  p_actwk->sprpri = p_data->sprpri;
  p_actwk->sprhs = p_data->sprhs;
  p_actwk->sprvs = p_data->sprvs;
  p_actwk->patno = p_data->patno;
  p_actwk->colino = p_data->colino;
  SET_BIT_2(p_actwk->cddat1);
  SPRITE_STATUS_UCHAR(p_actwk, 58) = 255;
  SET_BIT_2(p_actwk->actflg);
  p_actwk->r_no += 2;
}


// skdisasm label: Perform_DPLC
void set_emy_wchg(sprite_status* p_actwk, wrt_data* p_data) {
  if (p_actwk->patno == SPRITE_STATUS_UCHAR(p_actwk, 58)) return;
  SPRITE_STATUS_UCHAR(p_actwk, 58) = p_actwk->patno;
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
  if (SPRITE_STATUS_USHORT(p_actwk, 72) != 0) {
    CLEAR_BIT_7(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1]);
  }
  SET_BIT_7(p_actwk->cddat1);
  p_actwk->r_ptr = &frameout;
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
  if (SPRITE_STATUS_USHORT(p_actwk, 72) != 0) {
    CLEAR_BIT_7(flagwork[SPRITE_STATUS_USHORT(p_actwk, 72) - 1]);
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
  unsigned char bit_string = ~(SPRITE_STATUS_UCHAR(p_actwk, 59));
  DAT_008549d4[SPRITE_STATUS_USHORT(p_actwk, 60)] &= bit_string;
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
  SPRITE_STATUS_USHORT(p_actwk, 68) = coli_act_id;
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
