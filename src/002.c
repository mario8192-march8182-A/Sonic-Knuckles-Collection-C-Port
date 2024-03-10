#include "globals.h"
#include "002.h"
#include "004xxxxx.h"


// skdisasm label: CreateChild6_Simple
void set_act05(sprite_status* pActwk, set_act05_data* data) {
  sprite_status* pNewActwk;
  short i = 0;
  short cnt = data->cnt;

  do {
    bool created = Create_New_Sprite3(pActwk, &pNewActwk);
    if (!created) return;

    ((unsigned short*)pNewActwk)[35] = pActwk - actwk; // oya (parent)
    pNewActwk->patbase = pActwk->patbase;
    pNewActwk->sproffset = pActwk->sproffset;
    pNewActwk->r_ptr = data->act;
    pNewActwk->userflag1 = i;
    pNewActwk->xposi = pActwk->xposi;
    pNewActwk->yposi = pActwk->yposi;
    i += 2;
    --cnt;
  } while (cnt != -1);
}

// skdisasm label: Perform_DPLC
void set_emy_wchg(sprite_status* pActwk, wrt_tbl* data) {
  if (pActwk->patno == ((unsigned char*)pActwk)[58]) return;
  ((unsigned char*)pActwk)[58] = pActwk->patno;
  unsigned long* a3 = data->unknown;
  unsigned short vram_adr = (pActwk->sproffset & 0x7FF) << 5;
  unsigned short* tbl = data->tbl[pActwk->patno];
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
  ((unsigned short*)pActwk)[34] = coli_act_id;
  *ppColiActwk = &actwk[coli_act_id];
  return true;
}
