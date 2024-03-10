#include "../globals.h"
#include "../constants.h"
#include "gost08.h"
#include "../004xxxxx.h"
#include "../002.h"
#include "../091.h"


set_act05_data gost08_body_set_tbl = {
  0,
  &gost08_body
};

unsigned short gost08_tbl00[2] = { 0, 8 };
unsigned short gost08_tbl01[2] = { 0, 152 };
unsigned short gost08_tbl02[2] = { 0, 296 };
unsigned short gost08_tbl03[2] = { 0, 440 };
unsigned short gost08_tbl04[2] = { 0, 584 };
unsigned short gost08_tbl05[2] = { 0, 728 };
unsigned short gost08_tbl06[2] = { 0, 872 };
unsigned short gost08_tbl07[2] = { 0, 1016 };
unsigned short gost08_tbl08[2] = { 0, 1167 };
unsigned short gost08_tbl09[3] = { 256, 1413, 1515 };
unsigned short gost08_tbl10[3] = { 256, 1701, 1803 };
unsigned short gost08_tbl11[3] = { 256, 1989, 2091 };
unsigned short gost08_tbl12[3] = { 256, 1701, 2283 };
unsigned short gost08_tbl13[2] = { 0, 2472 };
unsigned short gost08_tbl14[2] = { 0, 2616 };
unsigned short gost08_tbl15[2] = { 0, 2755 };
unsigned short gost08_tbl16[2] = { 0, 2819 };
unsigned short gost08_tbl17[2] = { 0, 2880 };
unsigned short* gost08_tbl[18] = {
  gost08_tbl00,
  gost08_tbl01,
  gost08_tbl02,
  gost08_tbl03,
  gost08_tbl04,
  gost08_tbl05,
  gost08_tbl06,
  gost08_tbl07,
  gost08_tbl08,
  gost08_tbl09,
  gost08_tbl10,
  gost08_tbl11,
  gost08_tbl12,
  gost08_tbl13,
  gost08_tbl14,
  gost08_tbl15,
  gost08_tbl16,
  gost08_tbl17
};

wrt_tbl gost08_wrt_tbl = {
  gost08_tiles,
  gost08_tbl
};


void gost08(sprite_status* pActwk) {
  pActwk->r_ptr = &gost08_ctr;
  pActwk->xposi = 288;
  pActwk->yposi = 160;
  gost08_ctr(pActwk);
}

void gost08_ctr(sprite_status* pActwk) {
  static unsigned char cnt_tbl[6] = {
    0, 1, 2, 2, 3, 3
  };

  if (actwk[0].actfree[10] != KNUCKLES && markerno == 0) return;
  if (soz_darkness_level != 0) {
    unsigned char cnt = cnt_tbl[soz_darkness_level];
    if (soz_ghosts > cnt) return; // unsigned
    --((short*)pActwk)[29];
    if (((short*)pActwk)[29] >= 0) return;
    ++soz_ghosts;
    if (soz_ghosts <= cnt) { // unsigned
      ((short*)pActwk)[29] = 63;
    }
    set_act05(pActwk, &gost08_body_set_tbl);
  }
  else {
    soz_ghosts = 0;
  }
}

void gost08_body(sprite_status* pActwk) {
  static void(*act_tbl[9])(sprite_status*) = {
    &gost08_init,
    &gost08_wait0,
    &gost08_move0,
    &gost08_chg0,
    &gost08_chg1,
    &gost08_chg2,
    &gost08_atak0,
    &gost08_atak1,
    &gost08_atak2
  };

  act_tbl[pActwk->r_no / 2](pActwk);
  set_emy_wchg(pActwk, &gost08_wrt_tbl);
  if (pActwk->actflg >= 0) {
    gost08_body__fout0(pActwk);
    return;
  }
  if (soz_darkness_level == 0) {
    gost08_body__fout1(pActwk);
    return;
  }
  sprite_status* pColiActwk;
  bool collided = chk_emy_col(pActwk, &pColiActwk);
  if (collided) {
    bool attacked = chk_pl_attack(pActwk, pColiActwk);
    if (attacked) {
      gost08_body__fout1(pActwk);
      return;
    }
    if (((unsigned char*)pColiActwk)[52] == 0) {
      set_pl_damage(pActwk, pColiActwk);
    }
  }
  Add_Object_To_Collision_Response_List(pActwk);
  actionsub(pActwk);
}
