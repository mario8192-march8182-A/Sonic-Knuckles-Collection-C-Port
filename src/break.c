#include "globals.h"
#include "macros.h"
#include "util.h"
#include "types/hitchkdata.h"
#include "break.h"
#include "004xxxxx.h"
static void break_init(sprite_status* p_actwk);
static void breakmove(sprite_status* p_actwk);
static void breakmove2(sprite_status* p_actwk);
static void breakdown(sprite_status* p_actwk);
static void breakdown2(sprite_status* p_actwk);
static void breakdown2__sub(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char plplatformbit);
static void breakdown3(sprite_status* p_actwk);
static void break2init(sprite_status* p_actwk);
static void break2move(sprite_status* p_actwk);
static void break2move2(sprite_status* p_actwk);
static void break2move_koma(sprite_status* p_actwk);
static void break2komamove2(sprite_status* p_actwk);
static short break2komatbl[64];
static void break2movesw(sprite_status* p_actwk);
static void break2down(sprite_status* p_actwk);
static void break2down1(sprite_status* p_actwk);
static void break2down2(sprite_status* p_actwk);
static void break2down2__sub(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char* breakgo_data, unsigned char plplatformbit);
static void break2go(sprite_status* p_actwk, unsigned char* p_data);
static void breakgo(sprite_status* p_actwk);
static void breakgosub(sprite_status* p_actwk, unsigned char* p_data, sprite_status_handler p_handler);
static unsigned char brgotbl00[30];
static unsigned char brgotbl05[32];
static unsigned char br2gotbl060[16];
static unsigned char br2gotbl0601[16];
static unsigned char br2gotbl061[14];
static unsigned char br2gotbl010[16];
static unsigned char br2gotbl0101[16];
static unsigned char br2gotbl011[20];
static unsigned char br2gotbl0111[20];
static unsigned char br2gotbl012[15];
static unsigned char br2gotbl013[24];
static unsigned char br2gotbl0131[24];
static unsigned char br2gotbl020[32];
static unsigned char br2gotbl0201[32];
static unsigned char br2gotbl021[24];
static unsigned char br2gotbl0211[24];
static unsigned char br2gotbl050[44];
static unsigned char br2gotbl051[44];
static unsigned char br2gotbl081[10];
static unsigned char br2gotbl0811[10];
static unsigned char br2gotbl091[12];
static unsigned char br2gotbl0911[12];
static unsigned char break00tbl[64];
static unsigned char break05tbl[48];
static signed char br00sp00[74];
static signed char br00sp01[146];
static signed char br01sp00[80];
static signed char br01sp01[146];
static signed char br060sp00[50];
static signed char br060sp01[98];
static signed char br060sp02[98];
static signed char br061sp00[44];
static signed char br061sp01[86];
static signed char br010sp00[56];
static signed char br010sp01[98];
static signed char br010sp02[98];
static signed char br010sp03[68];
static signed char br010sp04[122];
static signed char br010sp05[122];
static signed char br010sp06[56];
static signed char br010sp07_br010sp08[92];
static signed char br010sp09[74];
static signed char br010sp10[146];
static signed char br010sp11[146];
static signed char br020sp00[98];
static signed char br020sp01[194];
static signed char br020sp02[194];
static signed char br020sp03[74];
static signed char br020sp04[146];
static signed char br020sp05[146];
static signed char br020sp06[98];
static signed char br020sp07_br020sp08[194];
static signed char br050sp00[98];
static signed char br050sp01[194];
static signed char br050sp02[134];
static signed char br050sp03[266];
static signed char br050sp04[266];
static signed char br090sp00[38];
static signed char br090sp01[74];
static signed char br090sp02[74];
static signed char br093sp00[38];
static signed char br093sp01[74];
static signed char br093sp02[74];
static signed char br040sp00[98];
static signed char br040sp01[194];
static signed char br040sp02[194];
static signed char br080sp00[32];
static signed char br080sp01[62];
static signed char br080sp02[64];


void break_(sprite_status* p_actwk) {
  break_init(p_actwk);
}


static void break_init(sprite_status* p_actwk) {
  p_actwk->patbase = break000pat;
  p_actwk->sproffset = 16385;
  if (g_mdRam.stageno.act == 1) {
    p_actwk->patbase = break001pat;
    p_actwk->sproffset = 16385;
  }
  p_actwk->actfree.break_.breakgo_data1 = brgotbl00;
  p_actwk->actfree.break_.breakmove_data = break00tbl;
  p_actwk->sprhs = 7;
  p_actwk->sprvs = 32;
  if (g_mdRam.stageno.zone == ICECAP) {
    p_actwk->patbase = break050pat;
    p_actwk->sproffset = 16385;
    p_actwk->actfree.break_.breakgo_data1 = brgotbl05;
    p_actwk->actfree.break_.breakmove_data = break05tbl;
    p_actwk->sprhs = 48;
    p_actwk->sprvs = 48;
  }
  SET_USE_LEVEL_COORDS(p_actwk->actflg);
  p_actwk->sprpri = PRI_5;
  p_actwk->actfree.break_.countdown = 7;
  p_actwk->patno = p_actwk->userflag1;
  SET_BIT(p_actwk->cddat1, CD_DIE);
  p_actwk->r_ptr = &breakmove;
  breakmove(p_actwk);
}


static void breakmove(sprite_status* p_actwk) {
  if (p_actwk->actfree.break_.break_flag != 0) {
    if (p_actwk->actfree.break_.countdown == 0) {
      breakgo(p_actwk);
      return;
    }
    --p_actwk->actfree.break_.countdown;
  }
  if (p_actwk->cddat1 & 0x18) {
    p_actwk->actfree.break_.break_flag = 1;
  }
  breakmove2(p_actwk);
}


static void breakmove2(sprite_status* p_actwk) {
  hitchk_data data = { p_actwk->sprhs, 0, 0, LONG_HIGH(p_actwk->xposi) };
  SolidObjectTopSloped2(data, p_actwk->actfree.break_.breakmove_data);
  frameoutchk(p_actwk);
}


static void breakdown(sprite_status* p_actwk) {
  --p_actwk->actfree.break_.countdown;
  if (p_actwk->actfree.break_.countdown == 0) {
    p_actwk->r_ptr = &breakdown3;
  }
  actionsub(p_actwk);
}


static void breakdown2(sprite_status* p_actwk) {
  breakmove2(p_actwk);
  --p_actwk->actfree.break_.countdown;
  if (p_actwk->actfree.break_.countdown != 0) return;
  p_actwk->r_ptr = &breakdown3;
  breakdown2__sub(p_actwk, &g_mdRam.actwk[0], 3);
  breakdown2__sub(p_actwk, &g_mdRam.actwk[1], 4);
}


static void breakdown2__sub(sprite_status* p_actwk, sprite_status* p_playerwk, unsigned char plplatformbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, plplatformbit)) return;
  CLEAR_BIT(p_actwk->cddat1, plplatformbit);
  CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
  CLEAR_BIT(p_playerwk->cddat1, CD_PUSH);
  SET_BIT(p_playerwk->cddat1, CD_JUMP);
  p_playerwk->restart = 1;
}


static void breakdown3(sprite_status* p_actwk) {
  if (!IS_ONSCREEN(p_actwk->actflg)) {
    frameout(p_actwk);
  }
  else {
    speedset(p_actwk);
    actionsub(p_actwk);
  }
}


void break2(sprite_status* p_actwk) {
  break2init(p_actwk);
}


static void break2init(sprite_status* p_actwk) {
  static unsigned char tbl01[16] = {
    64, 16, 0, 128,
    80, 16, 3, 128,
    64, 16, 6,   0,
    80, 32, 9, 128
  };
  static unsigned char* tbl011[8] = {
    br2gotbl010,
    br2gotbl0101,
    br2gotbl011,
    br2gotbl0111,
    br2gotbl012,
    br2gotbl012,
    br2gotbl013,
    br2gotbl0131
  };
  static unsigned char tbl02[12] = {
    64, 32, 0, 128,
    48, 32, 3, 128,
    64, 32, 6, 128
  };
  static unsigned char* tbl021[6] = {
    br2gotbl020,
    br2gotbl0201,
    br2gotbl021,
    br2gotbl0211,
    br2gotbl020,
    br2gotbl0201
  };
  static unsigned char tbl09[4] = {
    32, 24, 0, 128
  };
  static unsigned char* tbl091[2] = {
    br2gotbl091,
    br2gotbl0911
  };
  static unsigned char tbl04[4] = {
    64, 32, 0, 128
  };
  static unsigned char* tbl041[2] = {
    br2gotbl020,
    br2gotbl0201
  };
  static unsigned char tbl08[4] = {
    32, 48, 0, 128
  };
  static unsigned char* tbl081[2] = {
    br2gotbl081,
    br2gotbl0811
  };

  p_actwk->r_ptr = &break2move;
  SET_USE_LEVEL_COORDS(p_actwk->actflg);
  p_actwk->sprpri = PRI_5;
  if (g_mdRam.stageno.zone == LAUNCH_BASE) {
    unsigned short countdown = (p_actwk->userflag1 & 0x3F) * 3;
    bool carry = util__get_add_carry(countdown, 8);
    if (!carry) {
      countdown += 8;
    }
    else {
      countdown = 255;
    }
    p_actwk->actfree.break_.countdown = countdown;
    if (!BIT_6_IS_SET(p_actwk->userflag1)) {
      p_actwk->patbase = break060pat;
      p_actwk->sproffset = 16385;
      p_actwk->sprhs = 64;
      p_actwk->sprvs = 16;
      p_actwk->actfree.break_.breakgo_data1 = br2gotbl060;
      p_actwk->actfree.break_.breakgo_data2 = br2gotbl0601;
    }
    else {
      p_actwk->patbase = break061pat;
      p_actwk->sproffset = 16385;
      p_actwk->sprhs = 32;
      p_actwk->sprvs = 48;
      p_actwk->actfree.break_.breakgo_data1 = br2gotbl061;
    }
  }
  if (g_mdRam.stageno.zone == HYDROCITY) {
    p_actwk->patbase = break010pat;
    p_actwk->sproffset = 49153;
    unsigned char userflag = p_actwk->userflag1;
    if (BIT_7_IS_SET(userflag)) {
      p_actwk->actfree.break_.level_trigger_no = userflag & 0xF;
      p_actwk->r_ptr = &break2movesw;
      userflag &= 0x70;
    }
    p_actwk->actfree.break_.countdown = (userflag & 0xF) * 16 + 8;
    userflag = (userflag & 0xF0) / 4;
    unsigned char* p_init_data = &tbl01[userflag];
    p_actwk->sprhs = p_init_data[0];
    p_actwk->sprvs = p_init_data[1];
    p_actwk->patno = p_init_data[2];
    p_actwk->userflag1 = p_init_data[3];
    userflag *= 2;
    unsigned char** p_init_data2 = &tbl011[userflag / 4];
    p_actwk->actfree.break_.breakgo_data1 = p_init_data2[0];
    p_actwk->actfree.break_.breakgo_data2 = p_init_data2[1];
  }
  if (g_mdRam.stageno.zone == MARBLE_GARDEN) {
    p_actwk->patbase = break020pat;
    p_actwk->sproffset = 16385;
    p_actwk->actfree.break_.countdown = (p_actwk->userflag1 & 0xF) * 16 + 8;
    unsigned char userflag = (p_actwk->userflag1 & 0xF0) / 4;
    unsigned char* p_init_data = &tbl02[userflag];
    p_actwk->sprhs = p_init_data[0];
    p_actwk->sprvs = p_init_data[1];
    p_actwk->patno = p_init_data[2];
    p_actwk->userflag1 = p_init_data[3];
    userflag *= 2;
    unsigned char** p_init_data2 = &tbl021[userflag / 4];
    p_actwk->actfree.break_.breakgo_data1 = p_init_data2[0];
    p_actwk->actfree.break_.breakgo_data2 = p_init_data2[1];
    if (userflag == 16) {
      p_actwk->r_ptr = &break2move_koma;
    }
    return;
  }
  if (g_mdRam.stageno.zone == ICECAP) {
    unsigned char userflag = p_actwk->userflag1;
    if (BIT_7_IS_SET(userflag)) {
      p_actwk->actfree.break_.level_trigger_no = userflag & 0xF;
      p_actwk->r_ptr = &break2movesw;
      userflag &= 0x70;
    }
    p_actwk->actfree.break_.countdown = (userflag & 0xF) * 16 + 8;
    p_actwk->patbase = break050pat;
    p_actwk->sproffset = 16385;
    p_actwk->sprhs = 80;
    p_actwk->sprvs = 56;
    p_actwk->actfree.break_.breakgo_data1 = br2gotbl050;
    p_actwk->actfree.break_.breakgo_data2 = br2gotbl051;
    p_actwk->patno = 3;
  }
  if (g_mdRam.stageno.zone == LAVA_REEF_BOSS_AND_HIDDEN_PALACE) {
    p_actwk->patbase = break093pat;
    p_actwk->sproffset = 16385;
    goto jump16;
  }
  if (g_mdRam.stageno.zone == LAVA_REEF) {
    p_actwk->patbase = break091pat;
    p_actwk->sproffset = 16528;
jump16:
    p_actwk->actfree.break_.countdown = (p_actwk->userflag1 & 0xF) * 16 + 8;
    unsigned char userflag = (p_actwk->userflag1 & 0x70) / 4;
    unsigned char* p_init_data = &tbl09[userflag];
    p_actwk->sprhs = p_init_data[0];
    p_actwk->sprvs = p_init_data[1];
    p_actwk->patno = p_init_data[2];
    userflag *= 2;
    unsigned char** p_init_data2 = &tbl091[userflag / 2];
    p_actwk->actfree.break_.breakgo_data1 = p_init_data2[0];
    p_actwk->actfree.break_.breakgo_data2 = p_init_data2[1];
  }
  if (g_mdRam.stageno.zone == FLYING_BATTERY) {
    p_actwk->patbase = break041pat;
    p_actwk->sproffset = 16385;
    p_actwk->actfree.break_.countdown = (p_actwk->userflag1 & 0xF) * 16 + 8;
    unsigned char userflag = (p_actwk->userflag1 & 0xF0) / 4;
    unsigned char* p_init_data = &tbl04[userflag];
    p_actwk->sprhs = p_init_data[0];
    p_actwk->sprvs = p_init_data[1];
    p_actwk->patno = p_init_data[2];
    p_actwk->userflag1 = p_init_data[3];
    userflag *= 2;
    unsigned char** p_init_data2 = &tbl041[userflag / 2];
    p_actwk->actfree.break_.breakgo_data1 = p_init_data2[0];
    p_actwk->actfree.break_.breakgo_data2 = p_init_data2[1];
  }
  if (g_mdRam.stageno.zone == SANDOPOLIS) {
    p_actwk->patbase = break081pat;
    p_actwk->sproffset = 16385;
    p_actwk->actfree.break_.countdown = (p_actwk->userflag1 & 0xF) * 16 + 8;
    unsigned char userflag = (p_actwk->userflag1 & 0x70) / 4;
    unsigned char* p_init_data = &tbl08[userflag];
    p_actwk->sprhs = p_init_data[0];
    p_actwk->sprvs = p_init_data[1];
    p_actwk->patno = p_init_data[2];
    userflag *= 2;
    unsigned char** p_init_data2 = &tbl081[userflag / 2];
    p_actwk->actfree.break_.breakgo_data1 = p_init_data2[0];
    p_actwk->actfree.break_.breakgo_data2 = p_init_data2[1];
  }
  break2move(p_actwk);
}


static void break2move(sprite_status* p_actwk) {
  if (p_actwk->actfree.break_.break_flag != 0) {
    if (p_actwk->actfree.break_.countdown == 0) {
      unsigned char* p_data = p_actwk->actfree.break_.breakgo_data1;
      if (BIT_7_IS_SET(p_actwk->userflag1) && p_actwk->cddat1 & 0x18) {
        short xposi = LONG_HIGH(g_mdRam.actwk[0].xposi);
        if (!BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
          xposi = LONG_HIGH(g_mdRam.actwk[1].xposi);
          if (xposi < LONG_HIGH(p_actwk->xposi)) {
            p_data = p_actwk->actfree.break_.breakgo_data2;
            TOGGLE_BIT(p_actwk->cddat1, CD_RIGHT);
            ++p_actwk->patno;
          }
        }
      }
      break2go(p_actwk, p_data);
      return;
    }
    --p_actwk->actfree.break_.countdown;
  }
  if (p_actwk->cddat1 & 0x18) {
    p_actwk->actfree.break_.break_flag = 1;
  }
  break2move2(p_actwk);
}


static void break2move2(sprite_status* p_actwk) {
  hitchk_data data = { p_actwk->sprhs, 0, 16, LONG_HIGH(p_actwk->xposi) };
  SolidObjectTop(p_actwk, data);
  frameoutchk(p_actwk);
}


static void break2move_koma(sprite_status* p_actwk) {
  hitchk_data data = { p_actwk->sprhs, 0, 16, LONG_HIGH(p_actwk->xposi) };
  SolidObjectTop(p_actwk, data);
  if (p_actwk->cddat1 & 0x18) {
    unsigned char eventflag = g_mdRam.actwk[0].actfree.player.eventflag;
    if (!BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
      eventflag = g_mdRam.actwk[1].actfree.player.eventflag;
    }
    if (BIT_7_IS_SET(eventflag)) {
      bool bit_3_clear = BIT_IS_SET(p_actwk->cddat1, CD_RIDE);
      CLEAR_BIT(p_actwk->cddat1, CD_PLRIDE);
      if (bit_3_clear) {
        CLEAR_BIT(g_mdRam.actwk[0].cddat1, CD_RIDE);
      }
      bool bit_4_clear = !BIT_IS_SET(p_actwk->cddat1, CD_PL2RIDE);
      CLEAR_BIT(p_actwk->cddat1, CD_PL2RIDE);
      if (bit_4_clear) {
        CLEAR_BIT(g_mdRam.actwk[1].cddat1, CD_RIDE);
      }
      a4 = break2komatbl;
      ++p_actwk->patno;
      p_actwk->sprpri = PRI_1;
      p_actwk->r_ptr = &break2komamove2;
      breakgosubf(p_actwk);
      if (p_actwk->actfree.break_.flagwork_index != 0) {
        CLEAR_BIT_7(g_mdRam.flagwork[p_actwk->actfree.break_.flagwork_index - 1]);
        p_actwk->actfree.break_.flagwork_index = 0;
      }
      break2komamove2(p_actwk);
      return;
    }
  }
  frameoutchk(p_actwk);
}


static void break2komamove2(sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 24;
  if (IS_ONSCREEN(p_actwk->actflg)) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static short break2komatbl[64] = {
  -1024, -2560,  -768, -2560,  -512, -2560,  -256, -2560,
    256, -2560,   512, -2560,   768, -2560,  1024, -2560,
   -960, -2304,  -704, -2304,  -448, -2304,  -192, -2304,
    192, -2304,   448, -2304,   704, -2304,   960, -2304,
   -896, -2048,  -640, -2048,  -384, -2048,  -128, -2048,
    128, -2048,   384, -2048,   640, -2048,   896, -2048,
   -832, -1792,  -576, -1792,  -320, -1792,   -64, -1792,
     64, -1792,   320, -1792,   576, -1792,   832, -1792
};


static void break2movesw(sprite_status* p_actwk) {
  if (p_actwk->actfree.break_.break_flag != 0) {
    if (p_actwk->actfree.break_.countdown == 0) {
      unsigned char* p_data = p_actwk->actfree.break_.breakgo_data1;
      if (BIT_7_IS_SET(p_actwk->userflag1) && p_actwk->cddat1 & 0x18) {
        short xposi = LONG_HIGH(g_mdRam.actwk[0].xposi);
        if (!BIT_IS_SET(p_actwk->cddat1, CD_PLRIDE)) {
          xposi = LONG_HIGH(g_mdRam.actwk[1].xposi);
        }
        if (xposi < LONG_HIGH(p_actwk->xposi)) { // unsigned
          p_data = p_actwk->actfree.break_.breakgo_data2;
          TOGGLE_BIT(p_actwk->cddat1, CD_RIGHT);
          ++p_actwk->patno;
        }
      }
      break2go(p_actwk, p_data);
      return;
    }
    --p_actwk->actfree.break_.countdown;
  }
  unsigned char trigger = g_mdRam.level_triggers[p_actwk->actfree.break_.level_trigger_no & 0xF];
  if (trigger != 0) {
    p_actwk->actfree.break_.break_flag = 1;
  }
  break2move2(p_actwk);
}


static void break2down(sprite_status* p_actwk) {
  --p_actwk->actfree.break_.countdown;
  if (p_actwk->actfree.break_.countdown == 0) {
    p_actwk->r_ptr = &break2down1;
  }
  actionsub(p_actwk);
}


static void break2down1(sprite_status* p_actwk) {
  if (IS_ONSCREEN(p_actwk->actflg)) {
    speedset(p_actwk);
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void break2down2(sprite_status* p_actwk) {
  --p_actwk->actfree.break_.countdown;
  if (p_actwk->actfree.break_.countdown == 0) {
    p_actwk->r_ptr = &break2down1;
  }
  hitchk_data data = {
    p_actwk->sprhs,
    0,
    p_actwk->actfree.break_.countdown,
    0
  };
  break2down2__sub(p_actwk, &g_mdRam.actwk[0], data, p_actwk->actfree.break_.breakgo_data1, 3);
  break2down2__sub(p_actwk, &g_mdRam.actwk[1], data, p_actwk->actfree.break_.breakgo_data1, 4);
  frameoutchk(p_actwk);
}


static void break2down2__sub(sprite_status* p_actwk, sprite_status* p_playerwk, hitchk_data data, unsigned char* breakgo_data, unsigned char plplatformbit) {
  if (!BIT_IS_SET(p_actwk->cddat1, plplatformbit)) return;
  unsigned char width = data.sprhs * 2;
  if (!BIT_IS_SET(p_playerwk->cddat1, CD_JUMP)) {
    short distance = LONG_HIGH(p_playerwk->xposi) - LONG_HIGH(p_actwk->xposi) + data.sprhs;
    if (distance >= 0 && distance < width) { // unsigned
      if (BIT_IS_SET(p_actwk->cddat1, CD_RIGHT)) {
        distance = -distance;
        distance += width;
      }
      distance /= 16;
      unsigned char unknown = breakgo_data[0] - breakgo_data[distance];
      if (data.sprvs_ground > unknown) return; // unsigned
    }
  }
  CLEAR_BIT(p_actwk->cddat1, plplatformbit);
  CLEAR_BIT(p_playerwk->cddat1, CD_RIDE);
  CLEAR_BIT(p_playerwk->cddat1 ,CD_PUSH);
  SET_BIT(p_playerwk->cddat1, CD_JUMP);
  p_actwk->restart = 1;
}


static void break2go(sprite_status* p_actwk, unsigned char* p_data) {
  p_actwk->r_ptr = &break2down2;
  ++p_actwk->patno;
  breakgosub(p_actwk, p_data, &break2down);
}


static void breakgo(sprite_status* p_actwk) {
  p_actwk->r_ptr = &breakdown2;
  p_actwk->patno += 2;
  breakgosub(p_actwk, p_actwk->actfree.break_.breakgo_data1, &breakdown);
}


static void breakgosub(sprite_status* p_actwk, unsigned char* p_data, sprite_status_handler p_handler) {
  signed char* p_sp = p_actwk->patbase[p_actwk->patno];
  signed char cnt = *p_sp;
  p_sp += 2;
  --cnt;
  SET_STATIC_PATTERN(p_actwk->actflg);
  unsigned char actflg = p_actwk->actflg;
  sprite_status* p_new_actwk = p_actwk;
  goto jump;

  do {
    short slot_cnt;
    sprite_status* p_new_actwk;
    bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
    if (!created) break;
    p_sp += 6;
    p_new_actwk->r_ptr = p_handler;

jump:
    p_new_actwk->patbase = p_sp;
    p_new_actwk->actflg = actflg;
    util__copy_high(&p_new_actwk->xposi, &p_actwk->xposi);
    util__copy_high(&p_new_actwk->yposi, &p_actwk->yposi);
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->sprpri = p_actwk->sprpri;
    p_new_actwk->sprhs = p_actwk->sprhs;
    p_new_actwk->sprvs = p_actwk->sprvs;
    p_actwk->actfree.break_.countdown = *p_data++;
    --cnt;
  } while (cnt != -1);

  actionsub(p_actwk);
  if (p_actwk->actfree.break_.flagwork_index != 0) {
    CLEAR_BIT_7(g_mdRam.flagwork[p_actwk->actfree.break_.flagwork_index - 1]);
    p_actwk->actfree.break_.flagwork_index = 0;
  }
  soundset(89);
}


static unsigned char brgotbl00[30] = {
  48, 44, 40, 36, 32, 28, 46, 42, 38, 34,
  30, 26, 44, 40, 36, 32, 28, 24, 42, 38,
  34, 30, 26, 22, 40, 36, 32, 28, 24, 20
};
static unsigned char brgotbl05[32] = {
  48, 44, 40, 36, 32, 28, 46, 42, 38, 34,
  30, 26, 44, 40, 36, 32, 28, 24, 42, 38,
  34, 30, 26, 22, 40, 36, 32, 28, 24, 20,
  18, 16
};
static unsigned char br2gotbl060[16] = {
  32, 28, 24, 20, 16, 12,  8,  4, 30, 26,
  22, 18, 14, 10,  6,  2
};
static unsigned char br2gotbl0601[16] = {
  32,  4,  8, 12, 16, 20, 24, 28,  2,  6,
  10, 14, 18, 22, 26, 30
};
static unsigned char br2gotbl061[14] = {
  32, 24, 16,  8, 30, 22, 14,  6, 28, 20,
  12,  4, 26, 18
};
static unsigned char br2gotbl010[16] = {
  32, 28, 24, 20, 16, 12,  8,  4, 30, 26,
  22, 18, 14, 10,  6,  2
};
static unsigned char br2gotbl0101[16] = {
  32,  4,  8, 12, 16, 20, 24, 28,  2,  6,
  10, 14, 18, 22, 26, 30
};
static unsigned char br2gotbl011[20] = {
  40, 36, 32, 28, 24, 20, 16, 12,  8,  4,
  38, 34, 30, 26, 22, 18, 14, 10,  6,  2
};
static unsigned char br2gotbl0111[20] = {
  40,  4,  8, 12, 16, 20, 24, 28, 32, 36,
   2,  6, 10, 14, 18, 22, 26, 30, 34, 38
};
static unsigned char br2gotbl012[15] = {
  28,  4,  8, 12, 16, 20, 24,  2,  6, 10,
  14, 18, 22, 26, 30
};
static unsigned char br2gotbl013[24] = {
  48, 42, 36, 30, 24, 18, 12,  6, 46, 40,
  34, 28, 22, 16, 10,  4, 44, 38, 32, 26,
  20, 14,  8,  2
};
static unsigned char br2gotbl0131[24] = {
  48,  6, 12, 18, 24, 30, 36, 42,  4, 10,
  16, 22, 28, 34, 40, 46,  2,  8, 14, 20,
  26, 32, 38, 44
};
static unsigned char br2gotbl020[32] = {
  64, 56, 48, 40, 32, 24, 16, 8, 62, 54,
  46, 38, 30, 22, 14, 6, 60, 52, 44, 36,
  28, 20, 12, 4, 58, 50, 42, 34, 26, 18,
  10, 2
};
static unsigned char br2gotbl0201[32] = {
  64, 8, 16, 24, 32, 40, 48, 56, 6, 14,
  22, 30, 38, 46, 54, 62, 4, 12, 20, 28,
  36, 44, 52, 60, 2, 10, 18, 26, 34, 42,
  50, 58
};
static unsigned char br2gotbl021[24] = {
  48, 40, 32, 24, 16,  8, 46, 38, 30, 22,
  14,  6, 44, 36, 28, 20, 12,  4, 42, 34,
  26, 18, 10,  2
};
static unsigned char br2gotbl0211[24] = {
  48, 8, 16, 24, 32, 40, 6, 14, 22, 30,
  38, 46, 4, 12, 20, 28, 36, 44, 2, 10,
  18, 26, 34, 42
};
static unsigned char br2gotbl050[44] = {
  40, 36, 32, 28, 24, 20, 16, 12,  8,  4,
  39, 35, 31, 27, 23, 19, 15, 11,  7,  3,
  38, 34, 30, 26, 22, 18, 14, 10,  6,  2,
  37, 33, 29, 25, 21, 17, 13,  9,  5,  1,
   4,  3,  2,  1
};
static unsigned char br2gotbl051[44] = {
  40, 4, 8, 12, 16, 20, 24, 28, 32, 36,
  3, 7, 11, 15, 19, 23, 27, 31, 35, 39,
  2, 6, 10, 14, 18, 22, 26, 30, 34, 38,
  1, 5, 9, 13, 17, 21, 25, 29, 33, 37,
  1, 2, 3, 4
};
static unsigned char br2gotbl081[10] = {
  32, 24, 16,  8, 30, 22, 28, 20, 26, 18
};
static unsigned char br2gotbl0811[10] = {
  32,  8, 16, 24,  6, 14,  4, 12,  2, 10
};
static unsigned char br2gotbl091[12] = {
  24, 18, 12,  6, 22, 16, 10,  4, 20, 14,
   8,  2
};
static unsigned char br2gotbl0911[12] = {
  24,  6, 12, 18,  4, 10, 16, 22,  2,  8,
  14, 20
};
static unsigned char break00tbl[64] = {
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 30, 30, 29, 29, 28, 28, 27, 27,
  26, 26, 25, 25, 24, 24, 23, 23, 22, 22,
  21, 21, 20, 20, 19, 19, 18, 18, 17, 17,
  16, 16, 15, 15, 14, 14, 14, 14, 14, 14,
  14, 14, 14, 14
};
static unsigned char break05tbl[48] = {
  48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
  48, 48, 47, 47, 47, 47, 47, 47, 47, 47,
  47, 47, 47, 47, 46, 46, 46, 46, 46, 46,
  46, 46, 45, 45, 45, 45, 45, 45, 45, 45,
  45, 45, 45, 45, 45, 44, 43, 42
};


signed char* break000pat[4] = {
  br00sp00,
  br00sp00,
  br00sp01,
  br00sp01
};


static signed char br00sp00[74] = {
    0,  12, -32,  13,   0,   0, -48,  -1, -32,  13,
    8,   0, -16,  -1, -24,  12,  16,   0,  16,   0,
  -16,  13,  20,   0, -48,  -1, -16,  13,  20,   8,
  -16,  -1, -16,  13,  28,   0,  16,   0,   0,  13,
   36,   0, -48,  -1,   0,  13,  36,   8, -16,  -1,
    0,  13,  36,   8,  16,   0,  16,  13,  44,   0,
  -48,  -1,  16,  13,  44,   8, -16,  -1,  16,  13,
   44,   0,  16,   0
};
static signed char br00sp01[146] = {
    0,  24, -32,   5,   0,   0, -48,  -1, -32,   5,
    4,   0, -32,  -1, -32,   5,   8,   0, -16,  -1,
  -32,   5,  12,   0,   0,   0, -24,   4,  16,   0,
   16,   0, -24,   4,  18,   0,  32,   0, -16,   5,
   20,   0, -48,  -1, -16,   5,  24,   0, -32,  -1,
  -16,   5,  24,   8, -16,  -1, -16,   5,  20,   8,
    0,   0, -16,   5,  28,   0,  16,   0, -16,   5,
   32,   0,  32,   0,   0,   5,  36,   0, -48,  -1,
    0,   5,  40,   0, -32,  -1,   0,   5,  40,   8,
  -16,  -1,   0,   5,  36,   8,   0,   0,   0,   5,
   40,   8,  16,   0,   0,   5,  36,   8,  32,   0,
   16,   5,  44,   0, -48,  -1,  16,   5,  48,   0,
  -32,  -1,  16,   5,  48,   8, -16,  -1,  16,   5,
   44,   8,   0,   0,  16,   5,  44,   0,  16,   0,
   16,   5,  48,   0,  32,   0
};


signed char* break001pat[4] = {
  br01sp00,
  br01sp00,
  br01sp01,
  br01sp01
};


static signed char br01sp00[80] = {
    0,  13, -32,  13,   0,   0, -48,  -1, -32,  13,
    0,   8, -16,  -1, -32,   5,   8,   0,  16,   0,
  -24,   4,  12,   0,  32,   0, -16,  13,  14,   0,
  -48,  -1, -16,  13,  14,   0, -16,  -1, -16,  13,
   14,   8,  16,   0,   0,  13,  22,   0, -48,  -1,
    0,  13,  22,   8, -16,  -1,   0,  13,  22,   0,
   16,   0,  16,  13,  30,   0, -48,  -1,  16,  13,
   30,   8, -16,  -1,  16,  13,  30,   0,  16,   0
};
static signed char br01sp01[146] = {
    0,  24, -32,   5,   0,   0, -48,  -1, -32,   5,
    4,   0, -32,  -1, -32,   5,   4,   8, -16,  -1,
  -32,   5,   0,   8,   0,   0, -32,   5,   8,   0,
   16,   0, -24,   4,  12,   0,  32,   0, -16,   5,
   14,   0, -48,  -1, -16,   5,  18,   0, -32,  -1,
  -16,   5,  14,   0, -16,  -1, -16,   5,  18,   0,
    0,   0, -16,   5,  18,   8,  16,   0, -16,   5,
   14,   8,  32,   0,   0,   5,  22,   0, -48,  -1,
    0,   5,  26,   0, -32,  -1,   0,   5,  26,   8,
  -16,  -1,   0,   5,  22,   8,   0,   0,   0,   5,
   22,   0,  16,   0,   0,   5,  26,   0,  32,   0,
   16,   5,  30,   0, -48,  -1,  16,   5,  34,   0,
  -32,  -1,  16,   5,  34,   8, -16,  -1,  16,   5,
   30,   8,   0,   0,  16,   5,  30,   0,  16,   0,
   16,   5,  34,   0,  32,   0
};


signed char* break060pat[3] = {
  br060sp00,
  br060sp01,
  br060sp02
};


static signed char br060sp00[50] = {
    0,   8, -16,  13,   0,   0, -64,  -1, -16,  13,
    0,   0, -32,  -1, -16,  13,   0,   0,   0,   0,
  -16,  13,   0,   0,  32,   0,   0,  13,   8,   0,
  -64,  -1,   0,  13,   8,   0, -32,  -1,   0,  13,
    8,   0,   0,   0,   0,  13,   8,   0,  32,   0
};
static signed char br060sp01[98] = {
    0,  16, -16,   5,   0,   0, -64,  -1, -16,   5,
    0,   0, -48,  -1, -16,   5,   0,   0, -32,  -1,
  -16,   5,   0,   0, -16,  -1, -16,   5,   0,   0,
    0,   0, -16,   5,   0,   0,  16,   0, -16,   5,
    0,   0,  32,   0, -16,   5,   0,   0,  48,   0,
    0,   5,   8,   0, -64,  -1,   0,   5,   8,   8,
  -48,  -1,   0,   5,   8,   0, -32,  -1,   0,   5,
    8,   8, -16,  -1,   0,   5,   8,   0,   0,   0,
    0,   5,   8,   8,  16,   0,   0,   5,   8,   0,
   32,   0,   0,   5,   8,   8,  48,   0
};
static signed char br060sp02[98] = {
    0,  16, -16,   5,   0,   0,  48,   0, -16,   5,
    0,   0, -64,  -1, -16,   5,   0,   0, -48,  -1,
  -16,   5,   0,   0, -32,  -1, -16,   5,   0,   0,
  -16,  -1, -16,   5,   0,   0,   0,   0, -16,   5,
    0,   0,  16,   0, -16,   5,   0,   0,  32,   0,
    0,   5,   8,   0, -64,  -1,   0,   5,   8,   8,
  -48,  -1,   0,   5,   8,   0, -32,  -1,   0,   5,
    8,   8, -16,  -1,   0,   5,   8,   0,   0,   0,
    0,   5,   8,   8,  16,   0,   0,   5,   8,   0,
   32,   0,   0,   5,   8,   8,  48,   0
};


signed char* break061pat[3] = {
  br061sp00,
  br061sp01,
  br061sp01
};


static signed char br061sp00[44] = {
    0,   7, -16,  13,   0,   0, -32,  -1, -16,  13,
   16,   0,   0,   0,   0,  13,  24,   0, -32,  -1,
    0,  13,  32,   0,   0,   0,  16,  13,  40,   0,
  -32,  -1,  16,  13,  48,   0,   0,   0,  32,  13,
   48,   0, -32,  -1
};
static signed char br061sp01[86] = {
    0,  14, -16,   5,   0,   0, -32,  -1, -16,   5,
    0,   0, -16,  -1, -16,   5,   0,   0,   0,   0,
  -16,   5,  20,   0,  16,   0,   0,   5,  24,   0,
  -32,  -1,   0,   5,  28,   0, -16,  -1,   0,   5,
   32,   0,   0,   0,   0,   5,  36,   0,  16,   0,
   16,   5,  40,   0, -32,  -1,  16,   5,  44,   0,
  -16,  -1,  16,   5,  48,   0,   0,   0,  16,   5,
   52,   0,  16,   0,  32,   5,  48,   0, -32,  -1,
   32,   5,  52,   0, -16,  -1
};


signed char* break010pat[12] = {
  br010sp00,
  br010sp01,
  br010sp02,
  br010sp03,
  br010sp04,
  br010sp05,
  br010sp06,
  br010sp07_br010sp08,
  br010sp07_br010sp08,
  br010sp09,
  br010sp10,
  br010sp11
};


static signed char br010sp00[56] = {
    0,   9, -16,  13,   0,   0, -64,  -1, -16,  13,
    0,   0, -32,  -1, -16,  13,   0,   0,   0,   0,
  -16,  13,   0,   0,  32,   0,   0,   5,   8,   0,
  -64,  -1,   0,  13,  12,   0, -48,  -1,   0,  13,
   12,   0, -16,  -1,   0,  13,  12,   0,  16,   0,
    0,   5,  12,   0,  48,   0
};
static signed char br010sp01[98] = {
    0,  16, -16,   5,   0,   0, -64,  -1, -16,   5,
    4,   0, -48,  -1, -16,   5,   0,   0, -32,  -1,
  -16,   5,   4,   0, -16,  -1, -16,   5,   0,   0,
    0,   0, -16,   5,   4,   0,  16,   0, -16,   5,
    0,   0,  32,   0, -16,   5,   4,   0,  48,   0,
    0,   5,   8,   0, -64,  -1,   0,   5,  12,   0,
  -48,  -1,   0,   5,  16,   0, -32,  -1,   0,   5,
   12,   0, -16,  -1,   0,   5,  16,   0,   0,   0,
    0,   5,  12,   0,  16,   0,   0,   5,  16,   0,
   32,   0,   0,   5,  12,   0,  48,   0
};
static signed char br010sp02[98] = {
    0,  16, -16,   5,   4,   0,  48,   0, -16,   5,
    0,   0, -64,  -1, -16,   5,   4,   0, -48,  -1,
  -16,   5,   0,   0, -32,  -1, -16,   5,   4,   0,
  -16,  -1, -16,   5,   0,   0,   0,   0, -16,   5,
    4,   0,  16,   0, -16,   5,   0,   0,  32,   0,
    0,   5,   8,   0, -64,  -1,   0,   5,  12,   0,
  -48,  -1,   0,   5,  16,   0, -32,  -1,   0,   5,
   12,   0, -16,  -1,   0,   5,  16,   0,   0,   0,
    0,   5,  12,   0,  16,   0,   0,   5,  16,   0,
   32,   0,   0,   5,  12,   0,  48,   0
};
static signed char br010sp03[68] = {
    0,  11, -16,  13,   0,   0, -80,  -1, -16,  13,
    0,   0, -48,  -1, -16,  13,   0,   0, -16,  -1,
  -16,  13,   0,   0,  16,   0, -16,  13,   0,   0,
   48,   0,   0,   5,   8,   0, -80,  -1,   0,  13,
   12,   0, -64,  -1,   0,  13,  12,   0, -32,  -1,
    0,  13,  12,   0,   0,   0,   0,  13,  12,   0,
   32,   0,   0,   5,  12,   0,  64,   0
};
static signed char br010sp04[122] = {
    0,  20, -16,   5,   0,   0, -80,  -1, -16,   5,
    4,   0, -64,  -1, -16,   5,   0,   0, -48,  -1,
  -16,   5,   4,   0, -32,  -1, -16,   5,   0,   0,
  -16,  -1, -16,   5,   4,   0,   0,   0, -16,   5,
    0,   0,  16,   0, -16,   5,   4,   0,  32,   0,
  -16,   5,   0,   0,  48,   0, -16,   5,   4,   0,
   64,   0,   0,   5,   8,   0, -80,  -1,   0,   5,
   12,   0, -64,  -1,   0,   5,  16,   0, -48,  -1,
    0,   5,  12,   0, -32,  -1,   0,   5,  16,   0,
  -16,  -1,   0,   5,  12,   0,   0,   0,   0,   5,
   16,   0,  16,   0,   0,   5,  12,   0,  32,   0,
    0,   5,  16,   0,  48,   0,   0,   5,  12,   0,
   64,   0
};
static signed char br010sp05[122] = {
    0,  20, -16,   5,   4,   0,  64,   0, -16,   5,
    0,   0, -80,  -1, -16,   5,   4,   0, -64,  -1,
  -16,   5,   0,   0, -48,  -1, -16,   5,   4,   0,
  -32,  -1, -16,   5,   0,   0, -16,  -1, -16,   5,
    4,   0,   0,   0, -16,   5,   0,   0,  16,   0,
  -16,   5,   4,   0,  32,   0, -16,   5,   0,   0,
   48,   0,   0,   5,   8,   0, -80,  -1,   0,   5,
   12,   0, -64,  -1,   0,   5,  16,   0, -48,  -1,
    0,   5,  12,   0, -32,  -1,   0,   5,  16,   0,
  -16,  -1,   0,   5,  12,   0,   0,   0,   0,   5,
   16,   0,  16,   0,   0,   5,  12,   0,  32,   0,
    0,   5,  16,   0,  48,   0,   0,   5,  12,   0,
   64,   0
};
static signed char br010sp06[56] = {
    0,   9, -16,   5,  20,   0, -64,  -1, -16,  13,
    0,   0, -48,  -1, -16,  13,   0,   0, -16,  -1,
  -16,  13,   0,   0,  16,   0,   0,   5,  24,   0,
  -64,  -1,   0,   5,  16,   0, -48,  -1,   0,  13,
   12,   0, -32,  -1,   0,  13,  12,   0,   0,   0,
    0,  13,  28,   0,  32,   0
};
static signed char br010sp07_br010sp08[92] = {
    0,  15, -16,   5,   4,   0,  32,   0, -16,   5,
   20,   0, -64,  -1, -16,   5,   0,   0, -48,  -1,
  -16,   5,   4,   0, -32,  -1, -16,   5,   0,   0,
  -16,  -1, -16,   5,   4,   0,   0,   0, -16,   5,
    0,   0,  16,   0,   0,   5,  24,   0, -64,  -1,
    0,   5,  16,   0, -48,  -1,   0,   5,  12,   0,
  -32,  -1,   0,   5,  16,   0, -16,  -1,   0,   5,
   12,   0,   0,   0,   0,   5,  16,   0,  16,   0,
    0,   5,  28,   0,  32,   0,   0,   5,  32,   0,
   48,   0
};
static signed char br010sp09[74] = {
    0,  12, -16,  13,  36,   0, -64,  -1, -16,  13,
   36,   0, -32,  -1, -16,  13,  36,   0,   0,   0,
  -16,  13,  36,   0,  32,   0,   0,  13,  44,   0,
  -64,  -1,   0,  13,  52,   0, -32,  -1,   0,  13,
   44,   0,   0,   0,   0,  13,  52,   0,  32,   0,
   16,  14,  60,   0, -64,  -1,  16,  13,  72,   0,
  -32,  -1,  16,  14,  60,   0,   0,   0,  16,  13,
   72,   0,  32,   0
};
static signed char br010sp10[146] = {
    0,  24, -16,   5,  36,   0, -64,  -1, -16,   5,
   40,   0, -48,  -1, -16,   5,  36,   0, -32,  -1,
  -16,   5,  40,   0, -16,  -1, -16,   5,  36,   0,
    0,   0, -16,   5,  40,   0,  16,   0, -16,   5,
   36,   0,  32,   0, -16,   5,  40,   0,  48,   0,
    0,   5,  44,   0, -64,  -1,   0,   5,  48,   0,
  -48,  -1,   0,   5,  52,   0, -32,  -1,   0,   5,
   56,   0, -16,  -1,   0,   5,  44,   0,   0,   0,
    0,   5,  48,   0,  16,   0,   0,   5,  52,   0,
   32,   0,   0,   5,  56,   0,  48,   0,  16,   6,
   60,   0, -64,  -1,  16,   6,  66,   0, -48,  -1,
   16,   5,  72,   0, -32,  -1,  16,   5,  76,   0,
  -16,  -1,  16,   6,  60,   0,   0,   0,  16,   6,
   66,   0,  16,   0,  16,   5,  72,   0,  32,   0,
   16,   5,  76,   0,  48,   0
};
static signed char br010sp11[146] = {
    0,  24, -16,   5,  40,   0,  48,   0, -16,   5,
   36,   0, -64,  -1, -16,   5,  40,   0, -48,  -1,
  -16,   5,  36,   0, -32,  -1, -16,   5,  40,   0,
  -16,  -1, -16,   5,  36,   0,   0,   0, -16,   5,
   40,   0,  16,   0, -16,   5,  36,   0,  32,   0,
    0,   5,  44,   0, -64,  -1,   0,   5,  48,   0,
  -48,  -1,   0,   5,  52,   0, -32,  -1,   0,   5,
   56,   0, -16,  -1,   0,   5,  44,   0,   0,   0,
    0,   5,  48,   0,  16,   0,   0,   5,  52,   0,
   32,   0,   0,   5,  56,   0,  48,   0,  16,   6,
   60,   0, -64,  -1,  16,   6,  66,   0, -48,  -1,
   16,   5,  72,   0, -32,  -1,  16,   5,  76,   0,
  -16,  -1,  16,   6,  60,   0,   0,   0,  16,   6,
   66,   0,  16,   0,  16,   5,  72,   0,  32,   0,
   16,   5,  76,   0,  48,   0
};


signed char* break020pat[9] = {
  br020sp00,
  br020sp01,
  br020sp02,
  br020sp03,
  br020sp04,
  br020sp05,
  br020sp06,
  br020sp07_br020sp08,
  br020sp07_br020sp08
};


static signed char br020sp00[98] = {
    0,  16, -20,  13,  24,   0, -64,  -1, -20,  13,
   24,   0, -32,  -1, -20,  13,  24,   0,   0,   0,
  -20,  13,  24,   0,  32,   0,  -4,  13,  32,   0,
  -64,  -1,  -4,  13,  32,   0, -32,  -1,  -4,  13,
   32,   0,   0,   0,  -4,  13,  32,   0,  32,   0,
   12,  13,  40,   0, -64,  -1,  12,  13,  48,   0,
  -32,  -1,  12,  13,  48,   0,   0,   0,  12,  13,
   40,   0,  32,   0,  28,  13,  16,   0, -64,  -1,
   28,  13,  40,   0, -32,  -1,  28,  13,  40,   0,
    0,   0,  28,  13,  16,   8,  32,   0
};
static signed char br020sp01[194] = {
    0,  32, -20,   5,  24,   0, -64,  -1, -20,   5,
   28,   0, -48,  -1, -20,   5,  24,   0, -32,  -1,
  -20,   5,  28,   0, -16,  -1, -20,   5,  24,   0,
    0,   0, -20,   5,  28,   0,  16,   0, -20,   5,
   24,   0,  32,   0, -20,   5,  28,   0,  48,   0,
   -4,   5,  32,   0, -64,  -1,  -4,   5,  36,   0,
  -48,  -1,  -4,   5,  32,   0, -32,  -1,  -4,   5,
   36,   0, -16,  -1,  -4,   5,  32,   0,   0,   0,
   -4,   5,  36,   0,  16,   0,  -4,   5,  32,   0,
   32,   0,  -4,   5,  36,   0,  48,   0,  12,   5,
   12,   0, -64,  -1,  12,   5,  12,   8, -48,  -1,
   12,   5,  48,   0, -32,  -1,  12,   5,  52,   0,
  -16,  -1,  12,   5,  48,   0,   0,   0,  12,   5,
   52,   0,  16,   0,  12,   5,  12,   0,  32,   0,
   12,   5,  12,   8,  48,   0,  28,   5,  16,   0,
  -64,  -1,  28,   5,  20,   0, -48,  -1,  28,   5,
   12,   0, -32,  -1,  28,   5,  12,   8, -16,  -1,
   28,   5,  12,   0,   0,   0,  28,   5,  12,   8,
   16,   0,  28,   5,  20,   8,  32,   0,  28,   5,
   16,   0,  48,   0
};
static signed char br020sp02[194] = {
    0,  32, -20,   5,  28,   0,  48,   0, -20,   5,
   24,   0, -64,  -1, -20,   5,  28,   0, -48,  -1,
  -20,   5,  24,   0, -32,  -1, -20,   5,  28,   0,
  -16,  -1, -20,   5,  24,   0,   0,   0, -20,   5,
   28,   0,  16,   0, -20,   5,  24,   0,  32,   0,
   -4,   5,  32,   0, -64,  -1,  -4,   5,  36,   0,
  -48,  -1,  -4,   5,  32,   0, -32,  -1,  -4,   5,
   36,   0, -16,  -1,  -4,   5,  32,   0,   0,   0,
   -4,   5,  36,   0,  16,   0,  -4,   5,  32,   0,
   32,   0,  -4,   5,  36,   0,  48,   0,  12,   5,
   12,   0, -64,  -1,  12,   5,  12,   8, -48,  -1,
   12,   5,  48,   0, -32,  -1,  12,   5,  52,   0,
  -16,  -1,  12,   5,  48,   0,   0,   0,  12,   5,
   52,   0,  16,   0,  12,   5,  12,   0,  32,   0,
   12,   5,  12,   8,  48,   0,  28,   5,  16,   0,
  -64,  -1,  28,   5,  20,   0, -48,  -1,  28,   5,
   12,   0, -32,  -1,  28,   5,  12,   8, -16,  -1,
   28,   5,  12,   0,   0,   0,  28,   5,  12,   8,
   16,   0,  28,   5,  20,   8,  32,   0,  28,   5,
   16,   0,  48,   0
};
static signed char br020sp03[74] = {
    0,  12, -20,  13,  24,   0, -48,  -1, -20,  13,
   24,   0, -16,  -1, -20,  13,  24,   0,  16,   0,
   -4,  13,  32,   0, -48,  -1,  -4,  13,  32,   0,
  -16,  -1,  -4,  13,  32,   0,  16,   0,  12,  13,
   40,   0, -48,  -1,  12,  13,  48,   0, -16,  -1,
   12,  13,  40,   0,  16,   0,  28,  13,  16,   0,
  -48,  -1,  28,  13,  40,   0, -16,  -1,  28,  13,
   16,   8,  16,   0
};
static signed char br020sp04[146] = {
    0,  24, -20,   5,  24,   0, -48,  -1, -20,   5,
   28,   0, -32,  -1, -20,   5,  24,   0, -16,  -1,
  -20,   5,  28,   0,   0,   0, -20,   5,  24,   0,
   16,   0, -20,   5,  28,   0,  32,   0,  -4,   5,
   32,   0, -48,  -1,  -4,   5,  36,   0, -32,  -1,
   -4,   5,  32,   0, -16,  -1,  -4,   5,  36,   0,
    0,   0,  -4,   5,  32,   0,  16,   0,  -4,   5,
   36,   0,  32,   0,  12,   5,  12,   0, -48,  -1,
   12,   5,  12,   8, -32,  -1,  12,   5,  48,   0,
  -16,  -1,  12,   5,  52,   0,   0,   0,  12,   5,
   12,   0,  16,   0,  12,   5,  12,   8,  32,   0,
   28,   5,  16,   0, -48,  -1,  28,   5,  20,   0,
  -32,  -1,  28,   5,  12,   0, -16,  -1,  28,   5,
   12,   8,   0,   0,  28,   5,  20,   8,  16,   0,
   28,   5,  16,   0,  32,   0
};
static signed char br020sp05[146] = {
    0,  24, -20,   5,  28,   0,  32,   0, -20,   5,
   24,   0, -48,  -1, -20,   5,  28,   0, -32,  -1,
  -20,   5,  24,   0, -16,  -1, -20,   5,  28,   0,
    0,   0, -20,   5,  24,   0,  16,   0,  -4,   5,
   32,   0, -48,  -1,  -4,   5,  36,   0, -32,  -1,
   -4,   5,  32,   0, -16,  -1,  -4,   5,  36,   0,
    0,   0,  -4,   5,  32,   0,  16,   0,  -4,   5,
   36,   0,  32,   0,  12,   5,  12,   0, -48,  -1,
   12,   5,  12,   8, -32,  -1,  12,   5,  48,   0,
  -16,  -1,  12,   5,  52,   0,   0,   0,  12,   5,
   12,   0,  16,   0,  12,   5,  12,   8,  32,   0,
   28,   5,  16,   0, -48,  -1,  28,   5,  20,   0,
  -32,  -1,  28,   5,  12,   0, -16,  -1,  28,   5,
   12,   8,   0,   0,  28,   5,  20,   8,  16,   0,
   28,   5,  16,   0,  32,   0
};
static signed char br020sp06[98] = {
    0,  16, -20,  13,  24,   0, -64,  -1, -20,  13,
   24,   0, -32,  -1, -20,  13,  24,   0,   0,   0,
  -20,  13,  24,   0,  32,   0,  -4,  13,  78,   0,
  -64,  -1,  -4,  13,  78,   0, -32,  -1,  -4,  13,
   78,   0,   0,   0,  -4,  13,  78,   0,  32,   0,
   12,  13,  86,   0, -64,  -1,  12,  13,  86,   0,
  -32,  -1,  12,  13,  86,   0,   0,   0,  12,  13,
   86,   0,  32,   0,  28,  13,  94,   0, -64,  -1,
   28,  13,  94,   0, -32,  -1,  28,  13,  94,   0,
    0,   0,  28,  13,  94,   0,  32,   0
};
static signed char br020sp07_br020sp08[194] = {
    0,  32, -20,   5,  24,   0, -64,  -1, -20,   5,
   28,   0, -48,  -1, -20,   5,  24,   0, -32,  -1,
  -20,   5,  28,   0, -16,  -1, -20,   5,  24,   0,
    0,   0, -20,   5,  28,   0,  16,   0, -20,   5,
   24,   0,  32,   0, -20,   5,  28,   0,  48,   0,
   -4,   5,  78,   0, -64,  -1,  -4,   5,  82,   0,
  -48,  -1,  -4,   5,  78,   0, -32,  -1,  -4,   5,
   82,   0, -16,  -1,  -4,   5,  78,   0,   0,   0,
   -4,   5,  82,   0,  16,   0,  -4,   5,  78,   0,
   32,   0,  -4,   5,  82,   0,  48,   0,  12,   5,
   86,   0, -64,  -1,  12,   5,  90,   0, -48,  -1,
   12,   5,  86,   0, -32,  -1,  12,   5,  90,   0,
  -16,  -1,  12,   5,  86,   0,   0,   0,  12,   5,
   90,   0,  16,   0,  12,   5,  86,   0,  32,   0,
   12,   5,  90,   0,  48,   0,  28,   5,  90,   0,
  -64,  -1,  28,   5,  86,   0, -48,  -1,  28,   5,
   90,   0, -32,  -1,  28,   5,  86,   0, -16,  -1,
   28,   5,  90,   0,   0,   0,  28,   5,  86,   0,
   16,   0,  28,   5,  90,   0,  32,   0,  28,   5,
   86,   0,  48,   0
};


signed char* break050pat[6] = {
  br050sp00,
  br050sp01,
  br050sp01,
  br050sp02,
  br050sp03,
  br050sp04
};


static signed char br050sp00[98] = {
    0,  16, -48,  13,   0,   0, -48,  -1, -48,  13,
    8,   0, -16,  -1, -48,  13,  16,   0,  16,   0,
  -32,  13,  24,   0, -48,  -1, -32,  13,  24,   0,
  -16,  -1, -32,  13,  32,   0,  16,   0, -16,  13,
   40,   0, -48,  -1, -16,  13,  40,  24, -16,  -1,
  -16,  13,  48,   0,  16,   0,   0,  13,  40,   8,
  -48,  -1,   0,  13,  40,   0, -16,  -1,   0,  13,
   48,   0,  16,   0,  16,  13,  56,   0, -48,  -1,
   16,  13,  64,   0, -16,  -1,  16,  12,  72,   0,
   16,   0,  32,  12,  72,   0, -48,  -1
};
static signed char br050sp01[194] = {
    0,  32, -48,   5,   0,   0, -48,  -1, -48,   5,
    4,   0, -32,  -1, -48,   5,   8,   0, -16,  -1,
  -48,   5,  12,   0,   0,   0, -48,   5,  16,   0,
   16,   0, -48,   5,  20,   0,  32,   0, -32,   5,
   24,   0, -48,  -1, -32,   5,  28,   0, -32,  -1,
  -32,   5,  24,   0, -16,  -1, -32,   5,  28,   0,
    0,   0, -32,   5,  32,   0,  16,   0, -32,   5,
   36,   0,  32,   0, -16,   5,  40,   0, -48,  -1,
  -16,   5,  44,   0, -32,  -1, -16,   5,  44,  24,
  -16,  -1, -16,   5,  40,  24,   0,   0, -16,   5,
   48,   0,  16,   0, -16,   5,  52,   0,  32,   0,
    0,   5,  44,   8, -48,  -1,   0,   5,  40,   8,
  -32,  -1,   0,   5,  40,   0, -16,  -1,   0,   5,
   44,   0,   0,   0,   0,   5,  48,   0,  16,   0,
    0,   5,  52,   0,  32,   0,  16,   5,  56,   0,
  -48,  -1,  16,   5,  60,   0, -32,  -1,  16,   5,
   64,   0, -16,  -1,  16,   5,  68,   0,   0,   0,
   16,   4,  72,   0,  16,   0,  16,   4,  74,   0,
   32,   0,  32,   4,  72,   0, -48,  -1,  32,   4,
   74,   0, -32,  -1
};
static signed char br050sp02[134] = {
    0,  22, -17,  13,   0,   0, -80,  -1, -17,  13,
    8,   0, -48,  -1, -17,  13,   8,   8, -16,  -1,
  -17,  13,   0,   8,  16,   0, -17,  13,   0,   0,
   48,   0,  -1,  13,  24,   0, -80,  -1,  -1,  13,
   24,   0, -48,  -1,  -1,  13,  24,   0, -16,  -1,
   -1,  13,  24,   0,  16,   0,  -1,  13,  24,   8,
   48,   0,  15,  13,  40,   0, -80,  -1,  15,  13,
   40,   0, -48,  -1,  15,  13,  40,   8, -16,  -1,
   15,  13,  40,   8,  16,   0,  15,  13,  40,   0,
   48,   0,  31,  13,  64,   8, -80,  -1,  31,  13,
   56,   8, -48,  -1,  31,  13,  56,   0, -16,  -1,
   31,  13,  64,   0,  16,   0,  31,  13,  64,   8,
   48,   0,  47,  12,  72,   8, -48,  -1,  47,  12,
   72,   0, -16,  -1
};
static signed char br050sp03[266] = {
    0,  44, -17,   5,   0,   0, -80,  -1, -17,   5,
    4,   0, -64,  -1, -17,   5,   8,   0, -48,  -1,
  -17,   5,  12,   0, -32,  -1, -17,   5,  12,   8,
  -16,  -1, -17,   5,   8,   8,   0,   0, -17,   5,
    4,   8,  16,   0, -17,   5,   0,   8,  32,   0,
  -17,   5,   0,   0,  48,   0, -17,   5,   4,   0,
   64,   0,  -1,   5,  24,   0, -80,  -1,  -1,   5,
   28,   0, -64,  -1,  -1,   5,  24,   0, -48,  -1,
   -1,   5,  28,   0, -32,  -1,  -1,   5,  24,   0,
  -16,  -1,  -1,   5,  28,   0,   0,   0,  -1,   5,
   24,   0,  16,   0,  -1,   5,  28,   0,  32,   0,
   -1,   5,  28,   8,  48,   0,  -1,   5,  24,   8,
   64,   0,  15,   5,  40,   0, -80,  -1,  15,   5,
   44,   0, -64,  -1,  15,   5,  40,   0, -48,  -1,
   15,   5,  44,   0, -32,  -1,  15,   5,  44,   8,
  -16,  -1,  15,   5,  40,   8,   0,   0,  15,   5,
   44,   8,  16,   0,  15,   5,  40,   8,  32,   0,
   15,   5,  40,   0,  48,   0,  15,   5,  44,   0,
   64,   0,  31,   5,  68,   8, -80,  -1,  31,   5,
   64,   8, -64,  -1,  31,   5,  60,   8, -48,  -1,
   31,   5,  56,   8, -32,  -1,  31,   5,  56,   0,
  -16,  -1,  31,   5,  60,   0,   0,   0,  31,   5,
   64,   0,  16,   0,  31,   5,  68,   0,  32,   0,
   31,   5,  68,   8,  48,   0,  31,   5,  64,   8,
   64,   0,  47,   4,  74,   8, -48,  -1,  47,   4,
   72,   8, -32,  -1,  47,   4,  72,   0, -16,  -1,
   47,   4,  74,   0,   0,   0
};
static signed char br050sp04[266] = {
    0,  44, -17,   5,   4,   0,  64,   0, -17,   5,
    0,   0, -80,  -1, -17,   5,   4,   0, -64,  -1,
  -17,   5,   8,   0, -48,  -1, -17,   5,  12,   0,
  -32,  -1, -17,   5,  12,   8, -16,  -1, -17,   5,
    8,   8,   0,   0, -17,   5,   4,   8,  16,   0,
  -17,   5,   0,   8,  32,   0, -17,   5,   0,   0,
   48,   0,  -1,   5,  24,   0, -80,  -1,  -1,   5,
   28,   0, -64,  -1,  -1,   5,  24,   0, -48,  -1,
   -1,   5,  28,   0, -32,  -1,  -1,   5,  24,   0,
  -16,  -1,  -1,   5,  28,   0,   0,   0,  -1,   5,
   24,   0,  16,   0,  -1,   5,  28,   0,  32,   0,
   -1,   5,  28,   8,  48,   0,  -1,   5,  24,   8,
   64,   0,  15,   5,  40,   0, -80,  -1,  15,   5,
   44,   0, -64,  -1,  15,   5,  40,   0, -48,  -1,
   15,   5,  44,   0, -32,  -1,  15,   5,  44,   8,
  -16,  -1,  15,   5,  40,   8,   0,   0,  15,   5,
   44,   8,  16,   0,  15,   5,  40,   8,  32,   0,
   15,   5,  40,   0,  48,   0,  15,   5,  44,   0,
   64,   0,  31,   5,  68,   8, -80,  -1,  31,   5,
   64,   8, -64,  -1,  31,   5,  60,   8, -48,  -1,
   31,   5,  56,   8, -32,  -1,  31,   5,  56,   0,
  -16,  -1,  31,   5,  60,   0,   0,   0,  31,   5,
   64,   0,  16,   0,  31,   5,  68,   0,  32,   0,
   31,   5,  68,   8,  48,   0,  31,   5,  64,   8,
   64,   0,  47,   4,  74,   8, -48,  -1,  47,   4,
   72,   8, -32,  -1,  47,   4,  72,   0, -16,  -1,
   47,   4,  74,   0,   0,   0
};


signed char* break091pat[3] = {
  br090sp00,
  br090sp01,
  br090sp02
};


static signed char br090sp00[38] = {
    0,   6, -16,  13,   8,   0, -32,  -1, -16,  13,
    8,   8,   0,   0,   0,  13,  48,  32, -32,  -1,
    0,  13,  48,  40,   0,   0,  16,  13,  32,  32,
  -32,  -1,  16,  13,  32,  40,   0,   0
};
static signed char br090sp01[74] = {
    0,  12, -16,   5,   8,   0, -32,  -1, -16,   5,
   12,   0, -16,  -1, -16,   5,  12,   8,   0,   0,
  -16,   5,   8,   8,  16,   0,   0,   5,  48,  32,
  -32,  -1,   0,   5,  52,  32, -16,  -1,   0,   5,
   52,  40,   0,   0,   0,   5,  48,  40,  16,   0,
   16,   5,  32,  32, -32,  -1,  16,   5,  36,  32,
  -16,  -1,  16,   5,  36,  40,   0,   0,  16,   5,
   32,  40,  16,   0
};
static signed char br090sp02[74] = {
    0,  12, -16,   5,   8,   8,  16,   0, -16,   5,
    8,   0, -32,  -1, -16,   5,  12,   0, -16,  -1,
  -16,   5,  12,   8,   0,   0,   0,   5,  48,  32,
  -32,  -1,   0,   5,  52,  32, -16,  -1,   0,   5,
   52,  40,   0,   0,   0,   5,  48,  40,  16,   0,
   16,   5,  32,  32, -32,  -1,  16,   5,  36,  32,
  -16,  -1,  16,   5,  36,  40,   0,   0,  16,   5,
   32,  40,  16,   0
};


signed char* break093pat[3] = {
  br093sp00,
  br093sp01,
  br093sp02
};


static signed char br093sp00[38] = {
    0,   6, -16,  13,   0,   0, -32,  -1, -16,  13,
    0,   8,   0,   0,   0,  13,   8,  32, -32,  -1,
    0,  13,   8,  40,   0,   0,  16,  13,  16,  32,
  -32,  -1,  16,  13,  16,  40,   0,   0
};
static signed char br093sp01[74] = {
    0,  12, -16,   5,   0,   0, -32,  -1, -16,   5,
    4,   0, -16,  -1, -16,   5,   4,   8,   0,   0,
  -16,   5,   0,   8,  16,   0,   0,   5,   8,  32,
  -32,  -1,   0,   5,  12,  32, -16,  -1,   0,   5,
   12,  40,   0,   0,   0,   5,   8,  40,  16,   0,
   16,   5,  16,  32, -32,  -1,  16,   5,  20,  32,
  -16,  -1,  16,   5,  20,  40,   0,   0,  16,   5,
   16,  40,  16,   0
};
static signed char br093sp02[74] = {
    0,  12, -16,   5,   0,   8,  16,   0, -16,   5,
    0,   0, -32,  -1, -16,   5,   4,   0, -16,  -1,
  -16,   5,   4,   8,   0,   0,   0,   5,   8,  32,
  -32,  -1,   0,   5,  12,  32, -16,  -1,   0,   5,
   12,  40,   0,   0,   0,   5,   8,  40,  16,   0,
   16,   5,  16,  32, -32,  -1,  16,   5,  20,  32,
  -16,  -1,  16,   5,  20,  40,   0,   0,  16,   5,
   16,  40,  16,   0
};


signed char* break041pat[3] = {
  br040sp00,
  br040sp01,
  br040sp02
};


static signed char br040sp00[98] = {
    0,  16, -16,  13,   0,   0, -64,  -1, -16,  13,
    0,   0, -32,  -1, -16,  13,   0,   0,   0,   0,
  -16,  13,   0,   0,  32,   0,   0,  13,   8,   0,
  -64,  -1,   0,  13,   8,   8, -32,  -1,   0,  13,
    8,   0,   0,   0,   0,  13,   8,   8,  32,   0,
   16,  13,   8,   0, -64,  -1,  16,  13,   8,   8,
  -32,  -1,  16,  13,   8,   0,   0,   0,  16,  13,
    8,   8,  32,   0,  32,  13,  16,   0, -64,  -1,
   32,  13,  16,   8, -32,  -1,  32,  13,  16,   0,
    0,   0,  32,  13,  16,   8,  32,   0
};
static signed char br040sp01[194] = {
    0,  32, -16,   5,   0,   0, -64,  -1, -16,   5,
    4,   0, -48,  -1, -16,   5,   0,   0, -32,  -1,
  -16,   5,   4,   0, -16,  -1, -16,   5,   0,   0,
    0,   0, -16,   5,   4,   0,  16,   0, -16,   5,
    0,   0,  32,   0, -16,   5,   4,   0,  48,   0,
    0,   5,   8,   0, -64,  -1,   0,   5,  12,   0,
  -48,  -1,   0,   5,  12,   8, -32,  -1,   0,   5,
    8,   8, -16,  -1,   0,   5,   8,   0,   0,   0,
    0,   5,  12,   0,  16,   0,   0,   5,  12,   8,
   32,   0,   0,   5,   8,   8,  48,   0,  16,   5,
    8,   0, -64,  -1,  16,   5,  12,   0, -48,  -1,
   16,   5,  12,   8, -32,  -1,  16,   5,   8,   8,
  -16,  -1,  16,   5,   8,   0,   0,   0,  16,   5,
   12,   0,  16,   0,  16,   5,  12,   8,  32,   0,
   16,   5,   8,   8,  48,   0,  32,   5,  16,   0,
  -64,  -1,  32,   5,  20,   0, -48,  -1,  32,   5,
   20,   8, -32,  -1,  32,   5,  16,   8, -16,  -1,
   32,   5,  16,   0,   0,   0,  32,   5, 20,   0,
   16,   0,  32,   5, 20,   8,  32,   0,  32,   5,
   16,   8,  48,   0
};
static signed char br040sp02[194] = {
    0,  32, -16,   5,   4,   0,  48,   0, -16,   5,
    0,   0, -64,  -1, -16,   5,   4,   0, -48,  -1,
  -16,   5,   0,   0, -32,  -1, -16,   5,   4,   0,
  -16,  -1, -16,   5,   0,   0,   0,   0, -16,   5,
    4,   0,  16,   0, -16,   5,   0,   0,  32,   0,
    0,   5,   8,   0, -64,  -1,   0,   5,  12,   0,
  -48,  -1,   0,   5,  12,   8, -32,  -1,   0,   5,
    8,   8, -16,  -1,   0,   5,   8,   0,   0,   0,
    0,   5,  12,   0,  16,   0,   0,   5,  12,   8,
   32,   0,   0,   5,   8,   8,  48,   0,  16,   5,
    8,   0, -64,  -1,  16,   5,  12,   0, -48,  -1,
   16,   5,  12,   8, -32,  -1,  16,   5,   8,   8,
  -16,  -1,  16,   5,   8,   0,   0,   0,  16,   5,
   12,   0,  16,   0,  16,   5,  12,   8,  32,   0,
   16,   5,   8,   8,  48,   0,  32,   5,  16,   0,
  -64,  -1,  32,   5,  20,   0, -48,  -1,  32,   5,
   20,   8, -32,  -1,  32,   5,  16,   8, -16,  -1,
   32,   5,  16,   0,   0,   0,  32,   5,  20,   0,
   16,   0,  32,   5,  20,   8,  32,   0,  32,   5,
   16,   8,  48,   0
};


signed char* break081pat[3] = {
  br080sp00,
  br080sp01,
  br080sp02
};


static signed char br080sp00[32] = {
    0,   5, -16,  13,   8,  16, -32, -1, -16, 13,
   16,  16,   0,   0,   0, 13,   0,  16, -32, -1,
   16,  13,   0,  16, -32, -1,  32, 13,   0,  16,
  -32,  -1
};
static signed char br080sp01[62] = {
    0,  10, -16,   5,   8,  16, -32,  -1, -16,   5,
   12,  16, -16,  -1, -16,   5,  16,  16,   0,   0,
  -16,   5,  20,  16,  16,   0,   0,   5,   0,  16,
  -32,  -1,   0,   5,   4,  16, -16,  -1,  16,   5,
    0,  16, -32,  -1,  16,   5,   4,  16, -16,  -1,
   32,   5,   0,  16, -32,  -1,  32,   5,   4,  16,
  -16,  -1
};
static signed char br080sp02[64] = {
    0,  10, -16,   5,  20,  16,  16,   0, -16,   5,
    8,  16, -32,  -1, -16,   5,  12,  16, -16,  -1,
  -16,   5,  16,  16,   0,   0,   0,   5,   0,  16,
  -32,  -1,   0,   5,   4,  16, -16,  -1,  16,   5,
    0,  16, -32,  -1,  16,   5,   4,  16, -16,  -1,
   32,   5,   0,  16, -32,  -1,  32,   5,   4,  16,
  -16,  -1, -121, -37
};
