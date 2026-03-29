#include "break.h"
#include <stdbool.h>
#include "../types/break2initdata.h"
#include "../types/break2timerdata.h"
#include "../types/sonic3ram.h"
#include "../types/spritepattern.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../constants.h"
#include "../hitchk.h"
#include "../sound.h"
static void breakinit(SKC_sprite_status* p_actwk);
static void breakmove(SKC_sprite_status* p_actwk);
static void breakmove2(SKC_sprite_status* p_actwk);
static void breakdown(SKC_sprite_status* p_actwk);
static void breakdown2(SKC_sprite_status* p_actwk);
static void breakdown2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride);
static void breakdown3(SKC_sprite_status* p_actwk);
static void break2init(SKC_sprite_status* p_actwk);
static void break2move(SKC_sprite_status* p_actwk);
static void break2move2(SKC_sprite_status* p_actwk);
static void break2move_koma(SKC_sprite_status* p_actwk);
static void break2komamove2(SKC_sprite_status* p_actwk);
static void break2movesw(SKC_sprite_status* p_actwk);
static void break2down(SKC_sprite_status* p_actwk);
static void break2down1(SKC_sprite_status* p_actwk);
static void break2down2(SKC_sprite_status* p_actwk);
static void break2down2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, unsigned char* p_timer_data, bool* p_plride);
static void break2go(SKC_sprite_status* p_actwk, unsigned char* p_data);
static void breakgo(SKC_sprite_status* p_actwk);
static void breakgosub(SKC_sprite_status* p_actwk, unsigned char* p_data, SKC_sprite_status_handler p_handler);
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
static SKC_sprite_pattern br00sp00;
static SKC_sprite_pattern br00sp01;
static SKC_sprite_pattern br01sp00;
static SKC_sprite_pattern br01sp01;
static SKC_sprite_pattern br060sp00;
static SKC_sprite_pattern br060sp01;
static SKC_sprite_pattern br060sp02;
static SKC_sprite_pattern br061sp00;
static SKC_sprite_pattern br061sp01;
static SKC_sprite_pattern br010sp00;
static SKC_sprite_pattern br010sp01;
static SKC_sprite_pattern br010sp02;
static SKC_sprite_pattern br010sp03;
static SKC_sprite_pattern br010sp04;
static SKC_sprite_pattern br010sp05;
static SKC_sprite_pattern br010sp06;
static SKC_sprite_pattern br010sp07;
static SKC_sprite_pattern br010sp09;
static SKC_sprite_pattern br010sp10;
static SKC_sprite_pattern br010sp11;
static SKC_sprite_pattern br020sp00;
static SKC_sprite_pattern br020sp01;
static SKC_sprite_pattern br020sp02;
static SKC_sprite_pattern br020sp03;
static SKC_sprite_pattern br020sp04;
static SKC_sprite_pattern br020sp05;
static SKC_sprite_pattern br020sp06;
static SKC_sprite_pattern br020sp07;
static SKC_sprite_pattern br050sp00;
static SKC_sprite_pattern br050sp01;
static SKC_sprite_pattern br050sp02;
static SKC_sprite_pattern br050sp03;
static SKC_sprite_pattern br050sp04;
static SKC_sprite_pattern br090sp00;
static SKC_sprite_pattern br090sp01;
static SKC_sprite_pattern br090sp02;
static SKC_sprite_pattern br093sp00;
static SKC_sprite_pattern br093sp01;
static SKC_sprite_pattern br093sp02;
static SKC_sprite_pattern br040sp00;
static SKC_sprite_pattern br040sp01;
static SKC_sprite_pattern br040sp02;
static SKC_sprite_pattern br080sp00;
static SKC_sprite_pattern br080sp01;
static SKC_sprite_pattern br080sp02;

extern sonic3_ram g_ram;


void break_(SKC_sprite_status* p_actwk) {
  breakinit(p_actwk);
}


static void breakinit(SKC_sprite_status* p_actwk) {
  switch (get_zone(g_ram.stageno)) {
    default:
      p_actwk->patbase = get_act(g_ram.stageno) != ACT_2 ? break000pat : break001pat;
      p_actwk->sproffset = 0x4001;
      p_actwk->u.obj.actfree.break_.timer_data_ptr = brgotbl00;
      p_actwk->u.obj.actfree.break_.slope_data_ptr = break00tbl;
      p_actwk->sprhs = 7;
      p_actwk->sprvs = 32;
      break;
    case ICECAP:
      p_actwk->patbase = break050pat;
      p_actwk->sproffset = 0x4001;
      p_actwk->u.obj.actfree.break_.timer_data_ptr = brgotbl05;
      p_actwk->u.obj.actfree.break_.slope_data_ptr = break05tbl;
      p_actwk->sprhs = 48;
      p_actwk->sprvs = 48;
      break;
  }
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;
  p_actwk->u.obj.timer = 7;
  p_actwk->patno = p_actwk->u.obj.userflag & 0xFF;
  p_actwk->u.obj.cddat.die = 1;
  p_actwk->r_ptr = &breakmove;
  breakmove(p_actwk);
}


static void breakmove(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.break_.unknown != 0) {
    if (p_actwk->u.obj.timer == 0) {
      breakgo(p_actwk);
      return;
    }
    --p_actwk->u.obj.timer;
  }
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->u.obj.actfree.break_.unknown = 1;
  }
  breakmove2(p_actwk);
}


static void breakmove2(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { p_actwk->sprhs, 0, 0, fp16_get_integer(p_actwk->xposi) };
  ridechk_sloped(p_actwk, data, p_actwk->u.obj.actfree.break_.slope_data_ptr);
  frameoutchk(p_actwk);
}


static void breakdown(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->r_ptr = &breakdown3;
  }
  actionsub(p_actwk);
}


static void breakdown2(SKC_sprite_status* p_actwk) {
  breakmove2(p_actwk);
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->r_ptr = &breakdown3;
    bool plride = p_actwk->u.obj.cddat.plride;
    breakdown2__sub(p_actwk, &g_ram.actwk[0], &plride);
    p_actwk->u.obj.cddat.plride = plride;
    bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
    breakdown2__sub(p_actwk, &g_ram.actwk[1], &pl2ride);
    p_actwk->u.obj.cddat.pl2ride = pl2ride;
  }
}


static void breakdown2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, bool* p_plride) {
  if (!*p_plride) return;

  *p_plride = false;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->mstrestart = 1;
}


static void breakdown3(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 0) {
    frameout(p_actwk);
  }
  else {
    speedset(p_actwk);
    actionsub(p_actwk);
  }
}


void break2(SKC_sprite_status* p_actwk) {
  break2init(p_actwk);
}


static void break2init(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &break2move;
  p_actwk->actflg.relative_coordinates = 1;
  p_actwk->sprpri = PRI_5;

  switch (get_zone(g_ram.stageno)) {
    case LAUNCH_BASE: {
      unsigned short timer = (p_actwk->u.obj.userflag & 0x3F) * 4 + 8;
      if (timer > 255) {
        timer = 255;
      }
      p_actwk->u.obj.timer = timer;
      if (!BIT_IS_SET(p_actwk->u.obj.userflag, 6)) {
        p_actwk->patbase = break060pat;
        p_actwk->sproffset = 0x4001;
        p_actwk->sprhs = 64;
        p_actwk->sprvs = 16;
        p_actwk->u.obj.actfree.break_.timer_data_ptr = br2gotbl060;
        p_actwk->u.obj.actfree.break_.timer_data2_ptr = br2gotbl0601;
      }
      else {
        p_actwk->patbase = break061pat;
        p_actwk->sproffset = 0x4001;
        p_actwk->sprhs = 32;
        p_actwk->sprvs = 48;
        p_actwk->u.obj.actfree.break_.timer_data_ptr = br2gotbl061;
      }
      break;
    }
    case HYDROCITY: {
      SKC_break2_init_data tbl01[4] = {
        { 64, 16, 0, 128 },
        { 80, 16, 3, 128 },
        { 64, 16, 6,   0 },
        { 80, 32, 9, 128 }
      };
      SKC_break2_timer_data tbl011[4] = {
        { br2gotbl010, br2gotbl0101 },
        { br2gotbl011, br2gotbl0111 },
        { br2gotbl012, br2gotbl012 },
        { br2gotbl013, br2gotbl0131 }
      };

      p_actwk->patbase = break010pat;
      p_actwk->sproffset = 0xC001;
      unsigned short userflag = p_actwk->u.obj.userflag;
      if (BIT_IS_SET(userflag, 7)) {
        p_actwk->u.obj.actfree.break_.unknown2 = userflag & 0xF;
        p_actwk->r_ptr = &break2movesw;
        userflag &= 0x70;
      }
      p_actwk->u.obj.timer = (userflag & 0xF) * 16 + 8 & 0xFF;
      userflag = (userflag & 0xF0) >> 8;
      p_actwk->sprhs = tbl01[userflag].sprhs;
      p_actwk->sprvs = tbl01[userflag].sprvs;
      p_actwk->patno = tbl01[userflag].patno;
      p_actwk->u.obj.userflag = tbl01[userflag].userflag;
      p_actwk->u.obj.actfree.break_.timer_data_ptr = tbl011[userflag].timer_data_ptr;
      p_actwk->u.obj.actfree.break_.timer_data2_ptr = tbl011[userflag].timer_data2_ptr;
      break;
    }
    case MARBLE_GARDEN: {
      SKC_break2_init_data tbl02[3] = {
        { 64, 32, 0, 128 },
        { 48, 32, 3, 128 },
        { 64, 32, 6, 128 }
      };
      SKC_break2_timer_data tbl021[3] = {
        { br2gotbl020, br2gotbl0201 },
        { br2gotbl021, br2gotbl0211 },
        { br2gotbl020, br2gotbl0201 }
      };

      p_actwk->patbase = break020pat;
      p_actwk->sproffset = 0x4001;
      p_actwk->u.obj.timer = (p_actwk->u.obj.userflag & 0xF) * 16 + 8 & 0xFF;
      unsigned short userflag = (p_actwk->u.obj.userflag & 0xF0) >> 8;
      p_actwk->sprhs = tbl02[userflag].sprhs;
      p_actwk->sprvs = tbl02[userflag].sprvs;
      p_actwk->patno = tbl02[userflag].patno;
      p_actwk->u.obj.userflag = tbl02[userflag].userflag;
      if (userflag == 2) {
        p_actwk->r_ptr = &break2move_koma;
      }
      break;
    }
    case ICECAP: {
      unsigned short userflag = p_actwk->u.obj.userflag;
      if (BIT_IS_SET(userflag, 7)) {
        p_actwk->u.obj.actfree.break_.unknown2 = userflag & 0xF;
        p_actwk->r_ptr = &break2movesw;
        userflag &= 0x70;
      }
      p_actwk->u.obj.timer = (userflag & 0xF) * 16 + 8 & 0xFF;
      p_actwk->patbase = break050pat;
      p_actwk->sproffset = 0x4001;
      p_actwk->sprhs = 80;
      p_actwk->sprvs = 56;
      p_actwk->u.obj.actfree.break_.timer_data_ptr = br2gotbl050;
      p_actwk->u.obj.actfree.break_.timer_data2_ptr = br2gotbl051;
      p_actwk->patno = 3;
      break;
    }
    case LAVA_REEF_BOSS_AND_HIDDEN_PALACE:
      p_actwk->patbase = break093pat;
      p_actwk->sproffset = 0x4001;
      // fall-through
    case LAVA_REEF: {
      SKC_break2_init_data tbl09[1] = {
        32, 24, 0, 128
      };
      SKC_break2_timer_data tbl091[1] = {
        { br2gotbl091, br2gotbl0911 }
      };

      if (get_zone(g_ram.stageno == LAVA_REEF)) {
        p_actwk->patbase = break091pat;
        p_actwk->sproffset = 0x4090;
      }
      p_actwk->u.obj.timer = (p_actwk->u.obj.userflag & 0xF) * 16 + 8 & 0xFF;
      unsigned short userflag = (p_actwk->u.obj.userflag & 0x70) >> 8;
      p_actwk->sprhs = tbl09[userflag].sprhs;
      p_actwk->sprvs = tbl09[userflag].sprvs;
      p_actwk->patno = tbl09[userflag].patno;
      p_actwk->u.obj.userflag = tbl09[userflag].userflag;
      p_actwk->u.obj.actfree.break_.timer_data_ptr = tbl091[userflag].timer_data_ptr;
      p_actwk->u.obj.actfree.break_.timer_data2_ptr = tbl091[userflag].timer_data2_ptr;
      break;
    }
    case FLYING_BATTERY: {
      SKC_break2_init_data tbl04[1] = {
        { 64, 32, 0, 128 }
      };
      SKC_break2_timer_data tbl041[1] = {
        { br2gotbl020, br2gotbl0201 }
      };

      p_actwk->patbase = break041pat;
      p_actwk->sproffset = 0x4001;
      p_actwk->u.obj.timer = (p_actwk->u.obj.userflag & 0xF) * 16 + 8 & 0xFF;
      unsigned char userflag = (p_actwk->u.obj.userflag & 0xF0) >> 8;
      p_actwk->sprhs = tbl04[userflag].sprhs;
      p_actwk->sprvs = tbl04[userflag].sprvs;
      p_actwk->patno = tbl04[userflag].patno;
      p_actwk->u.obj.userflag = tbl04[userflag].userflag;
      p_actwk->u.obj.actfree.break_.timer_data_ptr = tbl041[userflag].timer_data_ptr;
      p_actwk->u.obj.actfree.break_.timer_data2_ptr = tbl041[userflag].timer_data2_ptr;
      break;
    }
    case SANDOPOLIS: {
      SKC_break2_init_data tbl08[1] = {
        { 32, 48, 0, 128 }
      };
      SKC_break2_timer_data tbl081[2] = {
        { br2gotbl081, br2gotbl0811 }
      };

      p_actwk->patbase = break081pat;
      p_actwk->sproffset = 0x4001;
      p_actwk->u.obj.timer = (p_actwk->u.obj.userflag & 0xF) * 16 + 8 & 0xFF;
      unsigned char userflag = (p_actwk->u.obj.userflag & 0x70) >> 8;
      p_actwk->sprhs = tbl08[userflag].sprhs;
      p_actwk->sprvs = tbl08[userflag].sprvs;
      p_actwk->patno = tbl08[userflag].patno;
      p_actwk->u.obj.actfree.break_.timer_data_ptr = tbl081[userflag].timer_data_ptr;
      p_actwk->u.obj.actfree.break_.timer_data2_ptr = tbl081[userflag].timer_data2_ptr;
      break;
    }
  }

  break2move(p_actwk);
}


static void break2move(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.break_.unknown2 != 0) {
    if (p_actwk->u.obj.timer == 0) {
      unsigned char* p_data = p_actwk->u.obj.actfree.break_.timer_data_ptr;
      if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)
          && (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1)) {
        int actid = p_actwk->u.obj.cddat.plride == 1 ? 0 : 1;
        short xposi = fp16_get_integer(g_ram.actwk[actid].xposi);
        if ((unsigned short)xposi < (unsigned short)fp16_get_integer(p_actwk->xposi)) {
          p_data = p_actwk->u.obj.actfree.break_.timer_data2_ptr;
          p_actwk->u.obj.cddat.right ^= 1;
          ++p_actwk->patno;
        }
      }
      break2go(p_actwk, p_data);
      return;
    }
    --p_actwk->u.obj.timer;
  }
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    p_actwk->u.obj.actfree.break_.unknown2 = 1;
  }
  break2move2(p_actwk);
}


static void break2move2(SKC_sprite_status* p_actwk) {
  SKC_hitchk_data data = { p_actwk->sprhs, 0, 16, fp16_get_integer(p_actwk->xposi) };
  ridechk(p_actwk, data);
  frameoutchk(p_actwk);
}


static void break2move_koma(SKC_sprite_status* p_actwk) {
  short break2komatbl[64] = {
    -1024, -2560,  -768, -2560,  -512, -2560,  -256, -2560,
      256, -2560,   512, -2560,   768, -2560,  1024, -2560,
     -960, -2304,  -704, -2304,  -448, -2304,  -192, -2304,
      192, -2304,   448, -2304,   704, -2304,   960, -2304,
     -896, -2048,  -640, -2048,  -384, -2048,  -128, -2048,
      128, -2048,   384, -2048,   640, -2048,   896, -2048,
     -832, -1792,  -576, -1792,  -320, -1792,   -64, -1792,
       64, -1792,   320, -1792,   576, -1792,   832, -1792
  };

  SKC_hitchk_data data = { p_actwk->sprhs, 0, 16, fp16_get_integer(p_actwk->xposi) };
  ridechk(p_actwk, data);
  if (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1) {
    int actid = p_actwk->u.obj.cddat.plride == 1 ? 0 : 1;
    if (BIT_IS_SET(g_ram.actwk[actid].u.play.eventflag, 7)) {
      if (p_actwk->u.obj.cddat.plride == 1) {
        p_actwk->u.obj.cddat.plride = 0;
        g_ram.actwk[0].u.play.cddat.ride = 0;
      }
      if (p_actwk->u.obj.cddat.pl2ride == 1) {
        p_actwk->u.obj.cddat.pl2ride = 0;
        g_ram.actwk[1].u.play.cddat.ride = 0;
      }
      ++p_actwk->patno;
      p_actwk->sprpri = PRI_1;
      p_actwk->r_ptr = &break2komamove2;
      breakgosubf(p_actwk, break2komatbl);
      if (p_actwk->u.obj.flagwork_index != 0) {
        CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
        p_actwk->u.obj.flagwork_index = 0;
      }
      break2komamove2(p_actwk);
      return;
    }
  }
  frameoutchk(p_actwk);
}


static void break2komamove2(SKC_sprite_status* p_actwk) {
  speedset2(p_actwk);
  p_actwk->yspeed += 0x18;
  if (p_actwk->actflg.onscreen == 1) {
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void break2movesw(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.break_.unknown2 != 0) {
    if (p_actwk->u.obj.timer == 0) {
      unsigned char* p_data = p_actwk->u.obj.actfree.break_.timer_data_ptr;
      if (BIT_IS_SET(p_actwk->u.obj.userflag, 7)
          && (p_actwk->u.obj.cddat.plride == 1 || p_actwk->u.obj.cddat.pl2ride == 1)) {
        int actid = p_actwk->u.obj.cddat.plride == 1 ? 0 : 1;
        short xposi = fp16_get_integer(g_ram.actwk[actid].xposi);
        if ((unsigned short)xposi < (unsigned short)fp16_get_integer(p_actwk->xposi)) {
          p_data = p_actwk->u.obj.actfree.break_.timer_data2_ptr;
          p_actwk->u.obj.cddat.right ^= 1;
          ++p_actwk->patno;
        }
      }
      break2go(p_actwk, p_data);
      return;
    }
    --p_actwk->u.obj.timer;
  }
  if (g_ram.level_triggers[p_actwk->u.obj.actfree.break_.unknown2 & 0xF] != 0) {
    p_actwk->u.obj.actfree.break_.unknown = 1;
    p_actwk->u.obj.flagwork_index = 0;
  }
  break2move2(p_actwk);
}


static void break2down(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->r_ptr = &break2down1;
  }
  actionsub(p_actwk);
}


static void break2down1(SKC_sprite_status* p_actwk) {
  if (p_actwk->actflg.onscreen == 1) {
    speedset(p_actwk);
    actionsub(p_actwk);
  }
  else {
    frameout(p_actwk);
  }
}


static void break2down2(SKC_sprite_status* p_actwk) {
  --p_actwk->u.obj.timer;
  if (p_actwk->u.obj.timer == 0) {
    p_actwk->r_ptr = &break2down1;
  }
  SKC_hitchk_data data = { p_actwk->sprhs, 0, p_actwk->u.obj.timer, 0 };
  bool plride = p_actwk->u.obj.cddat.plride;
  break2down2__sub(p_actwk, &g_ram.actwk[0], data, p_actwk->u.obj.actfree.break_.timer_data_ptr, &plride);
  p_actwk->u.obj.cddat.plride = plride;
  bool pl2ride = p_actwk->u.obj.cddat.pl2ride;
  break2down2__sub(p_actwk, &g_ram.actwk[1], data, p_actwk->u.obj.actfree.break_.timer_data_ptr, &pl2ride);
  p_actwk->u.obj.cddat.pl2ride = pl2ride;
  frameoutchk(p_actwk);
}


static void break2down2__sub(SKC_sprite_status* p_actwk, SKC_sprite_status* p_playerwk, SKC_hitchk_data data, unsigned char* p_timer_data, bool* p_plride) {
  if (!*p_plride) return;

  short distance = fp16_get_integer(p_playerwk->xposi) - fp16_get_integer(p_actwk->xposi) + data.sprhs;
  if (p_playerwk->u.play.cddat.jump == 0 && distance >= 0 && distance < data.sprhs * 2) {
    if (p_actwk->u.obj.cddat.right == 1) {
      distance = -distance + (short)data.sprhs * 2;
    }
    if (data.sprvs_ground > p_timer_data[0] - p_timer_data[distance / 16]) return;
  }
  *p_plride = false;
  p_playerwk->u.play.cddat.ride = 0;
  p_playerwk->u.play.cddat.push = 0;
  p_playerwk->u.play.cddat.jump = 1;
  p_playerwk->mstrestart = 1;
}


static void break2go(SKC_sprite_status* p_actwk, unsigned char* p_data) {
  p_actwk->r_ptr = &break2down2;
  ++p_actwk->patno;
  breakgosub(p_actwk, p_data, &break2down);
}


static void breakgo(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &breakdown2;
  p_actwk->patno += 2;
  breakgosub(p_actwk, p_actwk->u.obj.actfree.break_.timer_data_ptr, &breakdown);
}


static void breakgosub(SKC_sprite_status* p_actwk, unsigned char* p_data, SKC_sprite_status_handler p_handler) {
  p_actwk->actflg.static_pattern = 1;
  SKC_sprite_pattern** pp_pattern = (SKC_sprite_pattern**)p_actwk->patbase;
  SKC_sprite_status* p_new_actwk = p_actwk;

  for (int i = 0; i < pp_pattern[p_actwk->patno]->cnt; ++i) {
    if (i != 0) {
      SKC_actwkchk_result result = actwkchk2(p_actwk);
      if (result.actwk_ptr == 0) break;
      p_new_actwk = result.actwk_ptr;
      p_new_actwk->r_ptr = p_handler;
    }
    p_new_actwk->patbase = &pp_pattern[p_actwk->patno]->spr[i];
    p_new_actwk->actflg = p_actwk->actflg;
    fp16_set_integer(&p_new_actwk->xposi, fp16_get_integer(p_actwk->xposi));
    fp16_set_integer(&p_new_actwk->yposi, fp16_get_integer(p_actwk->yposi));
    p_new_actwk->sproffset = p_actwk->sproffset;
    p_new_actwk->sprpri = p_actwk->sprpri;
    p_new_actwk->sprhs = p_actwk->sprhs;
    p_new_actwk->sprvs = p_actwk->sprvs;
    p_actwk->u.obj.timer = p_data[i];
  }

  actionsub(p_actwk);
  if (p_actwk->u.obj.flagwork_index != 0) {
    CLEAR_BIT(g_ram.flagwork[p_actwk->u.obj.flagwork_index - 1], 7);
    p_actwk->u.obj.flagwork_index = 0;
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


SKC_sprite_pattern* break000pat[4] = {
  &br00sp00,
  &br00sp00,
  &br00sp01,
  &br00sp01
};


static SKC_sprite_pattern br00sp00 = {
  12,
  {
    { -32, 13, 0x0000, -48 },
    { -32, 13, 0x0008, -16 },
    { -24, 12, 0x0010,  16 },
    { -16, 13, 0x0014, -48 },
    { -16, 13, 0x0814, -16 },
    { -16, 13, 0x001C,  16 },
    {   0, 13, 0x0024, -48 },
    {   0, 13, 0x0824, -16 },
    {   0, 13, 0x0824,  16 },
    {  16, 13, 0x002C, -48 },
    {  16, 13, 0x082C, -16 },
    {  16, 13, 0x002C,  16 }
  }
};
static SKC_sprite_pattern br00sp01 = {
  24,
  {
    { -32, 5, 0x0000, -48 },
    { -32, 5, 0x0004, -32 },
    { -32, 5, 0x0008, -16 },
    { -32, 5, 0x000C,   0 },
    { -24, 4, 0x0010,  16 },
    { -24, 4, 0x0012,  32 },
    { -16, 5, 0x0014, -48 },
    { -16, 5, 0x0018, -32 },
    { -16, 5, 0x0818, -16 },
    { -16, 5, 0x0814,   0 },
    { -16, 5, 0x001C,  16 },
    { -16, 5, 0x0020,  32 },
    {   0, 5, 0x0024, -48 },
    {   0, 5, 0x0028, -32 },
    {   0, 5, 0x0828, -16 },
    {   0, 5, 0x0824,   0 },
    {   0, 5, 0x0828,  16 },
    {   0, 5, 0x0824,  32 },
    {  16, 5, 0x002C, -48 },
    {  16, 5, 0x0030, -32 },
    {  16, 5, 0x0830, -16 },
    {  16, 5, 0x082C,   0 },
    {  16, 5, 0x002C,  16 },
    {  16, 5, 0x0030,  32 }
  }
};


SKC_sprite_pattern* break001pat[4] = {
  &br01sp00,
  &br01sp00,
  &br01sp01,
  &br01sp01
};


static SKC_sprite_pattern br01sp00 = {
  13,
  {
    { -32, 13, 0x0000, -48 },
    { -32, 13, 0x0800, -16 },
    { -32,  5, 0x0008,  16 },
    { -24,  4, 0x000C,  32 },
    { -16, 13, 0x000E, -48 },
    { -16, 13, 0x000E,  16 },
    { -16, 13, 0x080E,  16 },
    {   0, 13, 0x0016, -48 },
    {   0, 13, 0x0816, -16 },
    {   0, 13, 0x0016,  16 },
    {  16, 13, 0x001E, -48 },
    {  16, 13, 0x081E, -16 },
    {  16, 13, 0x001E,  16 }
  }
};
static SKC_sprite_pattern br01sp01 = {
  24,
  {
    { -32, 5, 0x0000, -48 },
    { -32, 5, 0x0004, -32 },
    { -32, 5, 0x0804, -16 },
    { -32, 5, 0x0800,   0 },
    { -32, 5, 0x0008,  16 },
    { -24, 4, 0x000C,  32 },
    { -16, 5, 0x000E, -48 },
    { -16, 5, 0x0012, -32 },
    { -16, 5, 0x000E, -16 },
    { -16, 5, 0x0012,   0 },
    { -16, 5, 0x0812,  16 },
    { -16, 5, 0x080E,  32 },
    {   0, 5, 0x0016, -48 },
    {   0, 5, 0x001A, -32 },
    {   0, 5, 0x081A, -16 },
    {   0, 5, 0x0816,   0 },
    {   0, 5, 0x0016,  16 },
    {   0, 5, 0x001A,  32 },
    {  16, 5, 0x001E, -48 },
    {  16, 5, 0x0022, -32 },
    {  16, 5, 0x0822, -16 },
    {  16, 5, 0x081E,   0 },
    {  16, 5, 0x001E,  16 },
    {  16, 5, 0x0022,  32 }
  }
};


SKC_sprite_pattern* break060pat[3] = {
  &br060sp00,
  &br060sp01,
  &br060sp02
};


static SKC_sprite_pattern br060sp00 = {
  8,
  {
    { -16, 13, 0x0000, -64 },
    { -16, 13, 0x0000, -32 },
    { -16, 13, 0x0000,   0 },
    { -16, 13, 0x0000,  32 },
    {   0, 13, 0x0008, -64 },
    {   0, 13, 0x0008, -32 },
    {   0, 13, 0x0008,   0 },
    {   0, 13, 0x0008,  32 }
  }
};
static SKC_sprite_pattern br060sp01 = {
  16,
  {
    { -16, 5, 0x0000, -64 },
    { -16, 5, 0x0000, -48 },
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0000,   0 },
    { -16, 5, 0x0000,  16 },
    { -16, 5, 0x0000,  32 },
    { -16, 5, 0x0000,  48 },
    {   0, 5, 0x0008, -64 },
    {   0, 5, 0x0808, -48 },
    {   0, 5, 0x0008, -32 },
    {   0, 5, 0x0808, -16 },
    {   0, 5, 0x0008,   0 },
    {   0, 5, 0x0808,  16 },
    {   0, 5, 0x0008,  32 },
    {   0, 5, 0x0808,  48 }
  }
};
static SKC_sprite_pattern br060sp02 = {
  16,
  {
    { -16, 5, 0x0000,  48 },
    { -16, 5, 0x0000, -64 },
    { -16, 5, 0x0000, -48 },
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0000,   0 },
    { -16, 5, 0x0000,  16 },
    { -16, 5, 0x0000,  32 },
    {   0, 5, 0x0008, -64 },
    {   0, 5, 0x0808, -48 },
    {   0, 5, 0x0008, -32 },
    {   0, 5, 0x0808, -16 },
    {   0, 5, 0x0008,   0 },
    {   0, 5, 0x0808,  16 },
    {   0, 5, 0x0008,  32 },
    {   0, 5, 0x0808,  48 }
  }
};


SKC_sprite_pattern* break061pat[3] = {
  &br061sp00,
  &br061sp01,
  &br061sp01
};


static SKC_sprite_pattern br061sp00 = {
  7,
  {
    { -16, 13, 0x0000, -32 },
    { -16, 13, 0x0010,   0 },
    {   0, 13, 0x0018, -32 },
    {   0, 13, 0x0020,   0 },
    {  16, 13, 0x0028, -32 },
    {  16, 13, 0x0030,   0 },
    {  32, 13, 0x0030, -32 }
  }
};
static SKC_sprite_pattern br061sp01 = {
  14,
  {
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0000,   0 },
    { -16, 5, 0x0014,  16 },
    {   0, 5, 0x0018, -32 },
    {   0, 5, 0x001C, -16 },
    {   0, 5, 0x0020,   0 },
    {   0, 5, 0x0024,  16 },
    {  16, 5, 0x0028, -32 },
    {  16, 5, 0x002C, -16 },
    {  16, 5, 0x0030,   0 },
    {  16, 5, 0x0034,  16 },
    {  32, 5, 0x0030, -32 },
    {  32, 5, 0x0034, -16 }
  }
};


SKC_sprite_pattern* break010pat[12] = {
  &br010sp00,
  &br010sp01,
  &br010sp02,
  &br010sp03,
  &br010sp04,
  &br010sp05,
  &br010sp06,
  &br010sp07,
  &br010sp07,
  &br010sp09,
  &br010sp10,
  &br010sp11
};


static SKC_sprite_pattern br010sp00 = {
  9,
  {
    { -16, 13, 0x0000, -64 },
    { -16, 13, 0x0000, -32 },
    { -16, 13, 0x0000,   0 },
    { -16, 13, 0x0000,  32 },
    {   0,  5, 0x0008, -64 },
    {   0, 13, 0x000C, -48 },
    {   0, 13, 0x000C, -16 },
    {   0, 13, 0x000C,  16 },
    {   0,  5, 0x000C,  48 }
  }
};
static SKC_sprite_pattern br010sp01 = {
  16,
  {
    { -16, 5, 0x0000, -64 },
    { -16, 5, 0x0004, -48 },
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0000,   0 },
    { -16, 5, 0x0004,  16 },
    { -16, 5, 0x0000,  32 },
    { -16, 5, 0x0004,  48 },
    {   0, 5, 0x0008, -64 },
    {   0, 5, 0x000C, -48 },
    {   0, 5, 0x0010, -32 },
    {   0, 5, 0x000C, -16 },
    {   0, 5, 0x0010,   0 },
    {   0, 5, 0x000C,  16 },
    {   0, 5, 0x0010,  32 },
    {   0, 5, 0x000C,  48 }
  }
};
static SKC_sprite_pattern br010sp02 = {
  16,
  {
    { -16, 5, 0x0004,  48 },
    { -16, 5, 0x0000, -64 },
    { -16, 5, 0x0004, -48 },
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0000,   0 },
    { -16, 5, 0x0004,  16 },
    { -16, 5, 0x0000,  32 },
    {   0, 5, 0x0008, -64 },
    {   0, 5, 0x000C, -48 },
    {   0, 5, 0x0010, -32 },
    {   0, 5, 0x000C, -16 },
    {   0, 5, 0x0010,   0 },
    {   0, 5, 0x000C,  16 },
    {   0, 5, 0x0010,  32 },
    {   0, 5, 0x000C,  48 }
  }
};
static SKC_sprite_pattern br010sp03 = {
  11,
  {
    { -16, 13, 0x0000, -80 },
    { -16, 13, 0x0000, -48 },
    { -16, 13, 0x0000, -16 },
    { -16, 13, 0x0000,  16 },
    { -16, 13, 0x0000,  48 },
    {   0,  5, 0x0008, -80 },
    {   0, 13, 0x000C, -64 },
    {   0, 13, 0x000C, -32 },
    {   0, 13, 0x000C,   0 },
    {   0, 13, 0x000C,  32 },
    {   0,  5, 0x000C,  64 }
  }
};
static SKC_sprite_pattern br010sp04 = {
  20,
  {
    { -16, 5, 0x0000, -80 },
    { -16, 5, 0x0004, -64 },
    { -16, 5, 0x0000, -48 },
    { -16, 5, 0x0004, -32 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0004,   0 },
    { -16, 5, 0x0000,  16 },
    { -16, 5, 0x0004,  32 },
    { -16, 5, 0x0000,  48 },
    { -16, 5, 0x0004,  64 },
    {   0, 5, 0x0008, -80 },
    {   0, 5, 0x000C, -64 },
    {   0, 5, 0x0010, -48 },
    {   0, 5, 0x000C, -32 },
    {   0, 5, 0x0010, -16 },
    {   0, 5, 0x000C,   0 },
    {   0, 5, 0x0010,  16 },
    {   0, 5, 0x000C,  32 },
    {   0, 5, 0x0010,  48 },
    {   0, 5, 0x000C,  64 }
  }
};
static SKC_sprite_pattern br010sp05 = {
  20,
  {
    { -16, 5, 0x0004,  64 },
    { -16, 5, 0x0000, -80 },
    { -16, 5, 0x0004, -64 },
    { -16, 5, 0x0000, -48 },
    { -16, 5, 0x0004, -32 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0004,   0 },
    { -16, 5, 0x0000,  16 },
    { -16, 5, 0x0004,  32 },
    { -16, 5, 0x0000,  48 },
    {   0, 5, 0x0008, -80 },
    {   0, 5, 0x000C, -64 },
    {   0, 5, 0x0010, -48 },
    {   0, 5, 0x000C, -32 },
    {   0, 5, 0x0010, -16 },
    {   0, 5, 0x000C,   0 },
    {   0, 5, 0x0010,  16 },
    {   0, 5, 0x000C,  32 },
    {   0, 5, 0x0010,  48 },
    {   0, 5, 0x000C,  64 }
  }
};
static SKC_sprite_pattern br010sp06 = {
  9,
  {
    { -16,  5, 0x0014, -64 },
    { -16, 13, 0x0000, -48 },
    { -16, 13, 0x0000, -16 },
    { -16, 13, 0x0000,  16 },
    {   0,  5, 0x0018, -64 },
    {   0,  5, 0x0010, -48 },
    {   0, 13, 0x000C, -32 },
    {   0, 13, 0x000C,   0 },
    {   0, 13, 0x001C,  32 }
  }
};
static SKC_sprite_pattern br010sp07 = {
  15,
  {
    { -16, 5, 0x0004,  32 },
    { -16, 5, 0x0014, -64 },
    { -16, 5, 0x0000, -48 },
    { -16, 5, 0x0004, -32 },
    { -16, 5, 0x0000, -16 },
    { -16, 5, 0x0004,   0 },
    { -16, 5, 0x0000,  16 },
    {   0, 5, 0x0018, -64 },
    {   0, 5, 0x0010, -48 },
    {   0, 5, 0x000C, -32 },
    {   0, 5, 0x0010, -16 },
    {   0, 5, 0x000C,   0 },
    {   0, 5, 0x0010,  16 },
    {   0, 5, 0x001C,  32 },
    {   0, 5, 0x0020,  48 }
  }
};
static SKC_sprite_pattern br010sp09 = {
  12,
  {
    { -16, 13, 0x0024, -64 },
    { -16, 13, 0x0024, -32 },
    { -16, 13, 0x0024,   0 },
    { -16, 13, 0x0024,  32 },
    {   0, 13, 0x002C, -64 },
    {   0, 13, 0x0034, -32 },
    {   0, 13, 0x002C,   0 },
    {   0, 13, 0x0034,  32 },
    {  16, 14, 0x003C, -64 },
    {  16, 13, 0x0048, -32 },
    {  16, 14, 0x003C,   0 },
    {  16, 13, 0x0048,  32 }
  }
};
static SKC_sprite_pattern br010sp10 = {
  24,
  {
    { -16, 5, 0x0024, -64 },
    { -16, 5, 0x0028, -48 },
    { -16, 5, 0x0024, -32 },
    { -16, 5, 0x0028, -16 },
    { -16, 5, 0x0024,   0 },
    { -16, 5, 0x0028,  16 },
    { -16, 5, 0x0024,  32 },
    { -16, 5, 0x0028,  48 },
    {   0, 5, 0x002C, -64 },
    {   0, 5, 0x0030, -48 },
    {   0, 5, 0x0034, -32 },
    {   0, 5, 0x0038, -16 },
    {   0, 5, 0x002C,   0 },
    {   0, 5, 0x0030,  16 },
    {   0, 5, 0x0034,  32 },
    {   0, 5, 0x0038,  48 },
    {  16, 6, 0x003C, -64 },
    {  16, 6, 0x0042, -48 },
    {  16, 5, 0x0048, -32 },
    {  16, 5, 0x004C, -16 },
    {  16, 6, 0x003C,   0 },
    {  16, 6, 0x0042,  16 },
    {  16, 5, 0x0048,  32 },
    {  16, 5, 0x004C,  48 }
  }
};
static SKC_sprite_pattern br010sp11 = {
  24,
  {
    { -16, 5, 0x0028,  48 },
    { -16, 5, 0x0024, -64 },
    { -16, 5, 0x0028, -48 },
    { -16, 5, 0x0024, -32 },
    { -16, 5, 0x0028, -16 },
    { -16, 5, 0x0024,   0 },
    { -16, 5, 0x0028,  16 },
    { -16, 5, 0x0024,  32 },
    {   0, 5, 0x002C, -64 },
    {   0, 5, 0x0030, -48 },
    {   0, 5, 0x0034, -32 },
    {   0, 5, 0x0038, -16 },
    {   0, 5, 0x002C,   0 },
    {   0, 5, 0x0030,  16 },
    {   0, 5, 0x0034,  32 },
    {   0, 5, 0x0038,  48 },
    {  16, 6, 0x003C, -64 },
    {  16, 6, 0x0042, -48 },
    {  16, 5, 0x0048, -32 },
    {  16, 5, 0x004C, -16 },
    {  16, 6, 0x003C,   0 },
    {  16, 6, 0x0042,  16 },
    {  16, 5, 0x0048,  32 },
    {  16, 5, 0x004C,  48 }
  }
};


SKC_sprite_pattern* break020pat[9] = {
  &br020sp00,
  &br020sp01,
  &br020sp02,
  &br020sp03,
  &br020sp04,
  &br020sp05,
  &br020sp06,
  &br020sp07,
  &br020sp07
};


static SKC_sprite_pattern br020sp00 = {
  16,
  {
    { -20, 13, 0x0018, -64 },
    { -20, 13, 0x0018, -32 },
    { -20, 13, 0x0018,   0 },
    { -20, 13, 0x0018,  32 },
    {  -4, 13, 0x0020, -64 },
    {  -4, 13, 0x0020, -32 },
    {  -4, 13, 0x0020,   0 },
    {  -4, 13, 0x0020,  32 },
    {  12, 13, 0x0028, -64 },
    {  12, 13, 0x0030, -32 },
    {  12, 13, 0x0030,   0 },
    {  12, 13, 0x0028,  32 },
    {  28, 13, 0x0010, -64 },
    {  28, 13, 0x0028, -32 },
    {  28, 13, 0x0028,   0 },
    {  28, 13, 0x0810,  32 }
  }
};
static SKC_sprite_pattern br020sp01 = {
  32,
  {
    { -20, 5, 0x0018, -64 },
    { -20, 5, 0x001C, -48 },
    { -20, 5, 0x0018, -32 },
    { -20, 5, 0x001C, -16 },
    { -20, 5, 0x0018,   0 },
    { -20, 5, 0x001C,  16 },
    { -20, 5, 0x0018,  32 },
    { -20, 5, 0x001C,  48 },
    {  -4, 5, 0x0020, -64 },
    {  -4, 5, 0x0024, -48 },
    {  -4, 5, 0x0020, -32 },
    {  -4, 5, 0x0024, -16 },
    {  -4, 5, 0x0020,   0 },
    {  -4, 5, 0x0024,  16 },
    {  -4, 5, 0x0020,  32 },
    {  -4, 5, 0x0024,  48 },
    {  12, 5, 0x000C, -64 },
    {  12, 5, 0x080C, -48 },
    {  12, 5, 0x0030, -32 },
    {  12, 5, 0x0034, -16 },
    {  12, 5, 0x0030,   0 },
    {  12, 5, 0x0034,  16 },
    {  12, 5, 0x000C,  32 },
    {  12, 5, 0x080C,  48 },
    {  28, 5, 0x0010, -64 },
    {  28, 5, 0x0014, -48 },
    {  28, 5, 0x000C, -32 },
    {  28, 5, 0x080C, -16 },
    {  28, 5, 0x000C,   0 },
    {  28, 5, 0x080C,  16 },
    {  28, 5, 0x0814,  32 },
    {  28, 5, 0x0010,  48 }
  }
};
static SKC_sprite_pattern br020sp02 = {
  32,
  {
    { -20, 5, 0x001C,  48 },
    { -20, 5, 0x0018, -64 },
    { -20, 5, 0x001C, -48 },
    { -20, 5, 0x0018, -32 },
    { -20, 5, 0x001C, -16 },
    { -20, 5, 0x0018,   0 },
    { -20, 5, 0x001C,  16 },
    { -20, 5, 0x0018,  32 },
    {  -4, 5, 0x0020, -64 },
    {  -4, 5, 0x0024, -48 },
    {  -4, 5, 0x0020, -32 },
    {  -4, 5, 0x0024, -16 },
    {  -4, 5, 0x0020,   0 },
    {  -4, 5, 0x0024,  16 },
    {  -4, 5, 0x0020,  32 },
    {  -4, 5, 0x0024,  48 },
    {  12, 5, 0x000C, -64 },
    {  12, 5, 0x080C, -48 },
    {  12, 5, 0x0030, -32 },
    {  12, 5, 0x0034, -16 },
    {  12, 5, 0x0030,   0 },
    {  12, 5, 0x0034,  16 },
    {  12, 5, 0x000C,  32 },
    {  12, 5, 0x080C,  48 },
    {  28, 5, 0x0010, -64 },
    {  28, 5, 0x0014, -48 },
    {  28, 5, 0x000C, -32 },
    {  28, 5, 0x080C, -16 },
    {  28, 5, 0x000C,   0 },
    {  28, 5, 0x080C,  16 },
    {  28, 5, 0x0814,  32 },
    {  28, 5, 0x0010,  48 }
  }
};
static SKC_sprite_pattern br020sp03 = {
  12,
  {
    { -20, 13, 0x0018, -48 },
    { -20, 13, 0x0018, -16 },
    { -20, 13, 0x0018,  16 },
    {  -4, 13, 0x0020, -48 },
    {  -4, 13, 0x0020, -16 },
    {  -4, 13, 0x0020,  16 },
    {  12, 13, 0x0028, -48 },
    {  12, 13, 0x0030, -16 },
    {  12, 13, 0x0028,  16 },
    {  28, 13, 0x0010, -48 },
    {  28, 13, 0x0028, -16 },
    {  28, 13, 0x0810,  16 }
  }
};
static SKC_sprite_pattern br020sp04 = {
  24,
  {
    { -20, 5, 0x0018, -48 },
    { -20, 5, 0x001C, -32 },
    { -20, 5, 0x0018, -16 },
    { -20, 5, 0x001C,   0 },
    { -20, 5, 0x0018,  16 },
    { -20, 5, 0x001C,  32 },
    {  -4, 5, 0x0020, -48 },
    {  -4, 5, 0x0024, -32 },
    {  -4, 5, 0x0020, -16 },
    {  -4, 5, 0x0024,   0 },
    {  -4, 5, 0x0020,  16 },
    {  -4, 5, 0x0024,  32 },
    {  12, 5, 0x000C, -48 },
    {  12, 5, 0x080C, -32 },
    {  12, 5, 0x0030, -16 },
    {  12, 5, 0x0034,   0 },
    {  12, 5, 0x000C,  16 },
    {  12, 5, 0x080C,  32 },
    {  28, 5, 0x0010, -48 },
    {  28, 5, 0x0014, -32 },
    {  28, 5, 0x000C, -16 },
    {  28, 5, 0x080C,   0 },
    {  28, 5, 0x0814,  16 },
    {  28, 5, 0x0010,  32 }
  }
};
static SKC_sprite_pattern br020sp05 = {
  24,
  {
    { -20, 5, 0x001C,  32 },
    { -20, 5, 0x0018, -48 },
    { -20, 5, 0x001C, -32 },
    { -20, 5, 0x0018, -16 },
    { -20, 5, 0x001C,   0 },
    { -20, 5, 0x0018,  16 },
    {  -4, 5, 0x0020, -48 },
    {  -4, 5, 0x0024, -32 },
    {  -4, 5, 0x0020, -16 },
    {  -4, 5, 0x0024,   0 },
    {  -4, 5, 0x0020,  16 },
    {  -4, 5, 0x0024,  32 },
    {  12, 5, 0x000C, -48 },
    {  12, 5, 0x080C, -32 },
    {  12, 5, 0x0030, -16 },
    {  12, 5, 0x0034,   0 },
    {  12, 5, 0x000C,  16 },
    {  12, 5, 0x080C,  32 },
    {  28, 5, 0x0010, -48 },
    {  28, 5, 0x0014, -32 },
    {  28, 5, 0x000C, -16 },
    {  28, 5, 0x080C,   0 },
    {  28, 5, 0x0814,  16 },
    {  28, 5, 0x0010,  32 }
  }
};
static SKC_sprite_pattern br020sp06 = {
  16,
  {
    { -20, 13, 0x0018, -64 },
    { -20, 13, 0x0018, -32 },
    { -20, 13, 0x0018,   0 },
    { -20, 13, 0x0018,  32 },
    {  -4, 13, 0x004E, -64 },
    {  -4, 13, 0x004E, -32 },
    {  -4, 13, 0x004E,   0 },
    {  -4, 13, 0x004E,  32 },
    {  12, 13, 0x0056, -64 },
    {  12, 13, 0x0056, -32 },
    {  12, 13, 0x0056,   0 },
    {  12, 13, 0x0056,  32 },
    {  28, 13, 0x005E, -64 },
    {  28, 13, 0x005E, -32 },
    {  28, 13, 0x005E,   0 },
    {  28, 13, 0x005E,  32 }
  }
};
static SKC_sprite_pattern br020sp07 = {
  32,
  {
    { -20, 5, 0x0018, -64 },
    { -20, 5, 0x001C, -48 },
    { -20, 5, 0x0018, -32 },
    { -20, 5, 0x001C, -16 },
    { -20, 5, 0x0018,   0 },
    { -20, 5, 0x001C,  16 },
    { -20, 5, 0x0018,  32 },
    { -20, 5, 0x001C,  48 },
    {  -4, 5, 0x004E, -64 },
    {  -4, 5, 0x0052, -48 },
    {  -4, 5, 0x004E, -32 },
    {  -4, 5, 0x0052, -16 },
    {  -4, 5, 0x004E,   0 },
    {  -4, 5, 0x0052,  16 },
    {  -4, 5, 0x004E,  32 },
    {  -4, 5, 0x0052,  48 },
    {  12, 5, 0x0056, -64 },
    {  12, 5, 0x005A, -48 },
    {  12, 5, 0x0056, -32 },
    {  12, 5, 0x005A, -16 },
    {  12, 5, 0x0056,   0 },
    {  12, 5, 0x005A,  16 },
    {  12, 5, 0x0056,  32 },
    {  12, 5, 0x005A,  48 },
    {  28, 5, 0x005A, -64 },
    {  28, 5, 0x0056, -48 },
    {  28, 5, 0x005A, -32 },
    {  28, 5, 0x0056, -16 },
    {  28, 5, 0x005A,   0 },
    {  28, 5, 0x0056,  16 },
    {  28, 5, 0x005A,  32 },
    {  28, 5, 0x0056,  48 }
  }
};


SKC_sprite_pattern* break050pat[6] = {
  &br050sp00,
  &br050sp01,
  &br050sp01,
  &br050sp02,
  &br050sp03,
  &br050sp04
};


static SKC_sprite_pattern br050sp00 = {
  16,
  {
    { -48, 13, 0x0000, -48 },
    { -48, 13, 0x0008, -16 },
    { -48, 13, 0x0010,  16 },
    { -32, 13, 0x0018, -48 },
    { -32, 13, 0x0018, -16 },
    { -32, 13, 0x0020,  16 },
    { -16, 13, 0x0028, -48 },
    { -16, 13, 0x1828, -16 },
    { -16, 13, 0x0030,  16 },
    {   0, 13, 0x0828, -48 },
    {   0, 13, 0x0028, -16 },
    {   0, 13, 0x0030,  16 },
    {  16, 13, 0x0038, -48 },
    {  16, 13, 0x0040, -16 },
    {  16, 12, 0x0048,  16 },
    {  32, 12, 0x0048, -48 }
  }
};
static SKC_sprite_pattern br050sp01 = {
  32,
  {
    { -48, 5, 0x0000, -48 },
    { -48, 5, 0x0004, -32 },
    { -48, 5, 0x0008, -16 },
    { -48, 5, 0x000C,   0 },
    { -48, 5, 0x0010,  16 },
    { -48, 5, 0x0014,  32 },
    { -32, 5, 0x0018, -48 },
    { -32, 5, 0x001C, -32 },
    { -32, 5, 0x0018, -16 },
    { -32, 5, 0x001C,   0 },
    { -32, 5, 0x0020,  16 },
    { -32, 5, 0x0024,  32 },
    { -16, 5, 0x0028, -48 },
    { -16, 5, 0x002C, -32 },
    { -16, 5, 0x182C, -16 },
    { -16, 5, 0x1828,   0 },
    { -16, 5, 0x0030,  16 },
    { -16, 5, 0x0034,  32 },
    {   0, 5, 0x082C, -48 },
    {   0, 5, 0x0828, -32 },
    {   0, 5, 0x0028, -16 },
    {   0, 5, 0x002C,   0 },
    {   0, 5, 0x0030,  16 },
    {   0, 5, 0x0034,  32 },
    {  16, 5, 0x0038, -48 },
    {  16, 5, 0x003C, -32 },
    {  16, 5, 0x0040, -16 },
    {  16, 5, 0x0044,   0 },
    {  16, 4, 0x0048,  16 },
    {  16, 4, 0x004A,  32 },
    {  32, 4, 0x0048, -48 },
    {  32, 4, 0x004A, -32 }
  }
};
static SKC_sprite_pattern br050sp02 = {
  22,
  {
    { -17, 13, 0x0000, -80 },
    { -17, 13, 0x0008, -48 },
    { -17, 13, 0x0808, -16 },
    { -17, 13, 0x0800,  16 },
    { -17, 13, 0x0000,  48 },
    {  -1, 13, 0x0018, -80 },
    {  -1, 13, 0x0018, -48 },
    {  -1, 13, 0x0018, -16 },
    {  -1, 13, 0x0018,  16 },
    {  -1, 13, 0x0818,  48 },
    {  15, 13, 0x0028, -80 },
    {  15, 13, 0x0028, -48 },
    {  15, 13, 0x0828, -16 },
    {  15, 13, 0x0828,  16 },
    {  15, 13, 0x0028,  48 },
    {  31, 13, 0x0840, -80 },
    {  31, 13, 0x0838, -48 },
    {  31, 13, 0x0038, -16 },
    {  31, 13, 0x0040,  16 },
    {  31, 13, 0x0840,  48 },
    {  47, 12, 0x0848, -48 },
    {  47, 12, 0x0048, -16 }
  }
};
static SKC_sprite_pattern br050sp03 = {
  44,
  {
    { -17, 5, 0x0000, -80 },
    { -17, 5, 0x0004, -64 },
    { -17, 5, 0x0008, -48 },
    { -17, 5, 0x000C, -32 },
    { -17, 5, 0x080C, -16 },
    { -17, 5, 0x0808,   0 },
    { -17, 5, 0x0804,  16 },
    { -17, 5, 0x0800,  32 },
    { -17, 5, 0x0000,  48 },
    { -17, 5, 0x0004,  64 },
    {  -1, 5, 0x0018, -80 },
    {  -1, 5, 0x001C, -64 },
    {  -1, 5, 0x0018, -48 },
    {  -1, 5, 0x001C, -32 },
    {  -1, 5, 0x0018, -16 },
    {  -1, 5, 0x001C,   0 },
    {  -1, 5, 0x0018,  16 },
    {  -1, 5, 0x001C,  32 },
    {  -1, 5, 0x081C,  48 },
    {  -1, 5, 0x0818,  64 },
    {  15, 5, 0x0028, -80 },
    {  15, 5, 0x002C, -64 },
    {  15, 5, 0x0028, -48 },
    {  15, 5, 0x002C, -32 },
    {  15, 5, 0x082C, -16 },
    {  15, 5, 0x0828,   0 },
    {  15, 5, 0x082C,  16 },
    {  15, 5, 0x0828,  32 },
    {  15, 5, 0x0028,  48 },
    {  15, 5, 0x002C,  64 },
    {  31, 5, 0x0844, -80 },
    {  31, 5, 0x0840, -64 },
    {  31, 5, 0x083C, -48 },
    {  31, 5, 0x0838, -32 },
    {  31, 5, 0x0038, -16 },
    {  31, 5, 0x003C,   0 },
    {  31, 5, 0x0040,  16 },
    {  31, 5, 0x0044,  32 },
    {  31, 5, 0x0844,  48 },
    {  31, 5, 0x0840,  64 },
    {  47, 4, 0x084A, -48 },
    {  47, 4, 0x0848, -32 },
    {  47, 4, 0x0048, -16 },
    {  47, 4, 0x004A,   0 }
  }
};
static SKC_sprite_pattern br050sp04 = {
  44,
  {
    { -17, 5, 0x0004,  64 },
    { -17, 5, 0x0000, -80 },
    { -17, 5, 0x0004, -64 },
    { -17, 5, 0x0008, -48 },
    { -17, 5, 0x000C, -32 },
    { -17, 5, 0x080C, -16 },
    { -17, 5, 0x0808,   0 },
    { -17, 5, 0x0804,  16 },
    { -17, 5, 0x0800,  32 },
    { -17, 5, 0x0000,  48 },
    {  -1, 5, 0x0018, -80 },
    {  -1, 5, 0x001C, -64 },
    {  -1, 5, 0x0018, -48 },
    {  -1, 5, 0x001C, -32 },
    {  -1, 5, 0x0018, -16 },
    {  -1, 5, 0x001C,   0 },
    {  -1, 5, 0x0018,  16 },
    {  -1, 5, 0x001C,  32 },
    {  -1, 5, 0x081C,  48 },
    {  -1, 5, 0x0818,  64 },
    {  15, 5, 0x0028, -80 },
    {  15, 5, 0x002C, -64 },
    {  15, 5, 0x0028, -48 },
    {  15, 5, 0x002C, -32 },
    {  15, 5, 0x082C, -16 },
    {  15, 5, 0x0828,   0 },
    {  15, 5, 0x082C,  16 },
    {  15, 5, 0x0828,  32 },
    {  15, 5, 0x0028,  48 },
    {  15, 5, 0x002C,  64 },
    {  31, 5, 0x0844, -80 },
    {  31, 5, 0x0840, -64 },
    {  31, 5, 0x083C, -48 },
    {  31, 5, 0x0838, -32 },
    {  31, 5, 0x0038, -16 },
    {  31, 5, 0x003C,   0 },
    {  31, 5, 0x0040,  16 },
    {  31, 5, 0x0044,  32 },
    {  31, 5, 0x0844,  48 },
    {  31, 5, 0x0840,  64 },
    {  47, 4, 0x084A, -48 },
    {  47, 4, 0x0848, -32 },
    {  47, 4, 0x0048, -16 },
    {  47, 4, 0x004A,   0 }
  }
};


SKC_sprite_pattern* break091pat[3] = {
  &br090sp00,
  &br090sp01,
  &br090sp02
};


static SKC_sprite_pattern br090sp00 = {
  6,
  {
    { -16, 13, 0x0008, -32 },
    { -16, 13, 0x0808,   0 },
    {   0, 13, 0x2030, -32 },
    {   0, 13, 0x2830,   0 },
    {  16, 13, 0x2020, -32 },
    {  16, 13, 0x2820,   0 }
  }
};
static SKC_sprite_pattern br090sp01 = {
  12,
  {
    { -16, 5, 0x0008, -32 },
    { -16, 5, 0x000C, -16 },
    { -16, 5, 0x080C,   0 },
    { -16, 5, 0x0808,  16 },
    {   0, 5, 0x2030, -32 },
    {   0, 5, 0x2034, -16 },
    {   0, 5, 0x2834,   0 },
    {   0, 5, 0x2830,  16 },
    {  16, 5, 0x2020, -32 },
    {  16, 5, 0x2024, -16 },
    {  16, 5, 0x2824,   0 },
    {  16, 5, 0x2820,  16 }
  }
};
static SKC_sprite_pattern br090sp02 = {
  12,
  {
    { -16, 5, 0x0808,  16 },
    { -16, 5, 0x0008, -32 },
    { -16, 5, 0x000C, -16 },
    { -16, 5, 0x080C,   0 },
    {   0, 5, 0x2030, -32 },
    {   0, 5, 0x2034, -16 },
    {   0, 5, 0x2834,   0 },
    {   0, 5, 0x2830,  16 },
    {  16, 5, 0x2020, -32 },
    {  16, 5, 0x2024, -16 },
    {  16, 5, 0x2824,   0 },
    {  16, 5, 0x2820,  16 }
  }
};


SKC_sprite_pattern* break093pat[3] = {
  &br093sp00,
  &br093sp01,
  &br093sp02
};


static SKC_sprite_pattern br093sp00 = {
  6,
  {
    { -16, 13, 0x0000, -32 },
    { -16, 13, 0x0800,   0 },
    {   0, 13, 0x2008, -32 },
    {   0, 13, 0x2808,   0 },
    {  16, 13, 0x2010, -32 },
    {  16, 13, 0x2810,   0 }
  }
};
static SKC_sprite_pattern br093sp01 = {
  12,
  {
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0804,   0 },
    { -16, 5, 0x0800,  16 },
    {   0, 5, 0x2008, -32 },
    {   0, 5, 0x200C, -16 },
    {   0, 5, 0x280C,   0 },
    {   0, 5, 0x2808,  16 },
    {  16, 5, 0x2010, -32 },
    {  16, 5, 0x2014, -16 },
    {  16, 5, 0x2814,   0 },
    {  16, 5, 0x2810,  16 }
  }
};
static SKC_sprite_pattern br093sp02 = {
  12,
  {
    { -16, 5, 0x0800,  16 },
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0804,   0 },
    {   0, 5, 0x2008, -32 },
    {   0, 5, 0x200C, -16 },
    {   0, 5, 0x280C,   0 },
    {   0, 5, 0x2808,  16 },
    {  16, 5, 0x2010, -32 },
    {  16, 5, 0x2014, -16 },
    {  16, 5, 0x2814,   0 },
    {  16, 5, 0x2810,  16 }
  }
};


SKC_sprite_pattern* break041pat[3] = {
  &br040sp00,
  &br040sp01,
  &br040sp02
};


static SKC_sprite_pattern br040sp00 = {
  16,
  {
    { -16, 13, 0x0000, -64 },
    { -16, 13, 0x0000, -32 },
    { -16, 13, 0x0000,   0 },
    { -16, 13, 0x0000,  32 },
    {   0, 13, 0x0008, -64 },
    {   0, 13, 0x0808, -32 },
    {   0, 13, 0x0008,   0 },
    {   0, 13, 0x0808,  32 },
    {  16, 13, 0x0008, -64 },
    {  16, 13, 0x0808, -32 },
    {  16, 13, 0x0008,   0 },
    {  16, 13, 0x0808,  32 },
    {  32, 13, 0x0010, -64 },
    {  32, 13, 0x0810, -32 },
    {  32, 13, 0x0010,   0 },
    {  32, 13, 0x0810,  32 }
  }
};
static SKC_sprite_pattern br040sp01 = {
  32,
  {
    { -16, 5, 0x0000, -64 },
    { -16, 5, 0x0004, -48 },
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0000,   0 },
    { -16, 5, 0x0004,  16 },
    { -16, 5, 0x0000,  32 },
    { -16, 5, 0x0004,  48 },
    {   0, 5, 0x0008, -64 },
    {   0, 5, 0x000C, -48 },
    {   0, 5, 0x080C, -32 },
    {   0, 5, 0x0808, -16 },
    {   0, 5, 0x0008,   0 },
    {   0, 5, 0x000C,  16 },
    {   0, 5, 0x080C,  32 },
    {   0, 5, 0x0808,  48 },
    {  16, 5, 0x0008, -64 },
    {  16, 5, 0x000C, -48 },
    {  16, 5, 0x080C, -32 },
    {  16, 5, 0x0808, -16 },
    {  16, 5, 0x0008,   0 },
    {  16, 5, 0x000C,  16 },
    {  16, 5, 0x080C,  32 },
    {  16, 5, 0x0808,  48 },
    {  32, 5, 0x0010, -64 },
    {  32, 5, 0x0014, -48 },
    {  32, 5, 0x0814, -32 },
    {  32, 5, 0x0810, -16 },
    {  32, 5, 0x0010,   0 },
    {  32, 5, 0x0014,  16 },
    {  32, 5, 0x0814,  32 },
    {  32, 5, 0x0810,  48 }
  }
};
static SKC_sprite_pattern br040sp02 = {
  32,
  {
    { -16, 5, 0x0004,  48 },
    { -16, 5, 0x0000, -64 },
    { -16, 5, 0x0004, -48 },
    { -16, 5, 0x0000, -32 },
    { -16, 5, 0x0004, -16 },
    { -16, 5, 0x0000,   0 },
    { -16, 5, 0x0004,  16 },
    { -16, 5, 0x0000,  32 },
    {   0, 5, 0x0008, -64 },
    {   0, 5, 0x000C, -48 },
    {   0, 5, 0x080C, -32 },
    {   0, 5, 0x0808, -16 },
    {   0, 5, 0x0008,   0 },
    {   0, 5, 0x000C,  16 },
    {   0, 5, 0x080C,  32 },
    {   0, 5, 0x0808,  48 },
    {  16, 5, 0x0008, -64 },
    {  16, 5, 0x000C, -48 },
    {  16, 5, 0x080C, -32 },
    {  16, 5, 0x0808, -16 },
    {  16, 5, 0x0008,   0 },
    {  16, 5, 0x000C,  16 },
    {  16, 5, 0x080C,  32 },
    {  16, 5, 0x0808,  48 },
    {  32, 5, 0x0010, -64 },
    {  32, 5, 0x0014, -48 },
    {  32, 5, 0x0814, -32 },
    {  32, 5, 0x0810, -16 },
    {  32, 5, 0x0010,   0 },
    {  32, 5, 0x0014,  16 },
    {  32, 5, 0x0814,  32 },
    {  32, 5, 0x0810,  48 }
  }
};


SKC_sprite_pattern* break081pat[3] = {
  &br080sp00,
  &br080sp01,
  &br080sp02
};


static SKC_sprite_pattern br080sp00 = {
  5,
  {
    { -16, 13, 0x1008, -32 },
    { -16, 13, 0x1010,   0 },
    {   0, 13, 0x1000, -32 },
    {  16, 13, 0x1000, -32 },
    {  32, 13, 0x1000, -32 }
  }
};
static SKC_sprite_pattern br080sp01 = {
  10,
  {
    { -16, 5, 0x1008, -32 },
    { -16, 5, 0x100C, -16 },
    { -16, 5, 0x1010,   0 },
    { -16, 5, 0x1014,  16 },
    {   0, 5, 0x1000, -32 },
    {   0, 5, 0x1004, -16 },
    {  16, 5, 0x1000, -32 },
    {  16, 5, 0x1004, -16 },
    {  32, 5, 0x1000, -32 },
    {  32, 5, 0x1004, -16 }
  }
};
static SKC_sprite_pattern br080sp02 = {
  10,
  {
    { -16, 5, 0x1014,  16 },
    { -16, 5, 0x1008, -32 },
    { -16, 5, 0x100C, -16 },
    { -16, 5, 0x1010,   0 },
    {   0, 5, 0x1000, -32 },
    {   0, 5, 0x1004, -16 },
    {  16, 5, 0x1000, -32 },
    {  16, 5, 0x1004, -16 },
    {  32, 5, 0x1000, -32 },
    {  32, 5, 0x1004, -16 }
  }
};
