#include "globals.h"
#include "macros.h"
#include "002.h"
#include "004xxxxx.h"


// skdisasm label: CreateChild6_Simple
void set_act05(sprite_status* pActwk, set_act05_data* pData) {
  sprite_status* pNewActwk;
  short i = 0;
  short cnt = pData->cnt;

  do {
    bool created = Create_New_Sprite3(pActwk, &pNewActwk);
    if (!created) return;

    SPRITE_STATUS_USHORT(pNewActwk, OYA_ADR) = pActwk - actwk;
    pNewActwk->patbase = pActwk->patbase;
    pNewActwk->sproffset = pActwk->sproffset;
    pNewActwk->r_ptr = pData->act;
    pNewActwk->userflag1 = i;
    pNewActwk->xposi = (pActwk->xposi / 65536) * 65536;
    pNewActwk->yposi = (pActwk->yposi / 65536) * 65536;
    i += 2;
    --cnt;
  } while (cnt != -1);
}

// skdisasm labels: Animate_RawMultiDelay, Animate_RawNoSSTMultiDelay
int time_pg(sprite_status* pActwk, signed char* pg_tbl) {
  --pActwk->pattim;
  signed char pattim = pActwk->pattim; // conversion so it can be negative
  if (pattim >= 0) return 0;
  pActwk->patcnt += 2;
  signed char pg = pg_tbl[pActwk->patcnt];
  if (pg < 0) return chk_tpg_next(pActwk, pg, pg_tbl, pActwk->patcnt);
  pActwk->patno = pg;
  pActwk->pattim = pg_tbl[pActwk->patcnt + 1];
  return 1;
}

int chk_tpg_next(sprite_status* pActwk, signed char pg, signed char* pg_tbl, unsigned char patcnt) {
  int ret = 0;
  pg = -pg;

  switch (pg) {
    case 0:
      break;
    case 8:
      pg = pg_tbl[patcnt + 1];
      pg_tbl = &pg_tbl[pg];
      SPRITE_STATUS_PSCHAR(pActwk, 48) = pg_tbl;
    case 4:
      pActwk->patno = pg_tbl[0];
      pActwk->pattim = pg_tbl[1];
      ret = 1;
      break;
    case 12:
      pActwk->pattim = 0;
      SPRITE_STATUS_PHANDLER(pActwk, 52)(pActwk);
      ret = -1;
      break;
  }

  return ret;
}

// skdisasm label: SetUp_ObjAttributesSlotted
void emy_wrt_init(sprite_status* pActwk, wrt_init_data * pData) {
  unsigned char bit = 0;
  short cnt = pData->cnt; // this conversion from unsigned to signed should be safe
  unsigned short sproffset = pData->sproffset;
  unsigned short offset_increase = pData->offset_increase;
  unsigned char flags = emy_wrt_flg[pData->flg_index];
  if (flags == 0) goto ok;

  do {
    bool bit_0_clear = !BIT_0_IS_SET(flags);
    flags >>= 1;
    if (bit_0_clear) goto ok;
    ++bit;
    sproffset += offset_increase;
    --cnt;
  } while (cnt != -1);

  pActwk->r_ptr = 0;
  pActwk->xposi = 0;
  pActwk->yposi = 0;
  pActwk->userflag1 = 0;
  pActwk->actflg = 0;
  pActwk->cddat1 = pActwk->cddat2 = 0;
  return;

ok:
  emy_wrt_flg[pData->flg_index] |= 1 << bit;
  SPRITE_STATUS_UCHAR(pActwk, 59) = bit;
  SPRITE_STATUS_USHORT(pActwk, 60) = pData->flg_index;
  pActwk->sproffset = sproffset;
  pActwk->patbase = pData->patbase;
  pActwk->sprpri = pData->sprpri;
  pActwk->sprhs = pData->sprhs;
  pActwk->sprvs = pData->sprvs;
  pActwk->patno = pData->patno;
  pActwk->colino = pData->colino;
  SET_BIT_2(pActwk->cddat1);
  SPRITE_STATUS_UCHAR(pActwk, 58) = 255;
  SET_BIT_2(pActwk->actflg);
  pActwk->r_no += 2;
}

// skdisasm label: Perform_DPLC
void set_emy_wchg(sprite_status* pActwk, wrt_tbl* pTbl) {
  if (pActwk->patno == SPRITE_STATUS_UCHAR(pActwk, 58)) return;
  SPRITE_STATUS_UCHAR(pActwk, 58) = pActwk->patno;
  unsigned long* a3 = pTbl->unknown;
  unsigned short vram_adr = (pActwk->sproffset & 0x7FF) << 5;
  unsigned short* tbl = pTbl->tbl[pActwk->patno];
  short cnt = *tbl++; // this conversion from unsigned to signed should be safe
  cnt = cnt >> 8 | cnt << 8; // rotate lower and upper 8 bits
  unsigned short d3 = 0;

  do {
    d3 = *tbl++;
    unsigned short d1 = d3;
    d1 &= 0xFFF0;
    d1 += d1;
    d1 += *a3;
    unsigned short d2 = vram_adr;
    d3 &= 0xF;
    ++d3;
    d3 <<= 4;
    vram_adr += d3;
    vram_adr += d3;
    Copy_Data_To_VRAM(d1, d2, d3);
    --cnt;
  } while (cnt != -1);
}

// skdisasm label: Go_Delete_SpriteSlotted2
void set_wchg_fout0(sprite_status* pActwk) {
  pActwk->r_ptr = &frameout;
  SET_BIT_7(pActwk->cddat1);
  clr_wchg_bit(pActwk);
}

// skdisasm label: Remove_From_TrackingSlot
void clr_wchg_bit(sprite_status* pActwk) {
  unsigned char bit_string = ~(SPRITE_STATUS_UCHAR(pActwk, 59));
  DAT_008549d4[SPRITE_STATUS_USHORT(pActwk, 60)] &= bit_string;
}

// skdisasm label: HurtCharacter_Directly
void set_pl_damage(sprite_status* pAttackActwk, sprite_status* pPlayerwk) {
  playdamageset(pPlayerwk, pAttackActwk);
}

unsigned short pl_wk_tbl[4] = {
  0, 0, 1, 1
};

// skdisasm label: Check_PlayerCollision
bool chk_emy_col(sprite_status* pActwk, sprite_status** ppColiActwk) {
  if (pActwk->colicnt == 0) return false;
  pActwk->colicnt = 0;
  unsigned short coli_act_id = pl_wk_tbl[pActwk->colicnt & 3];
  SPRITE_STATUS_USHORT(pActwk, 68) = coli_act_id;
  *ppColiActwk = &actwk[coli_act_id];
  return true;
}
