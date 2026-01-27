#include "actclear.h"
#include <stdbool.h>
#include "data/cg/actclear.h"
#include "data/cg/actdigits.h"
#include "data/cg/characternames.h"
#include "data/pat/actclear.h"
#include "types/actwkchkresult.h"
#include "types/overlayelementinitdata.h"
#include "types/sonic3ram.h"
#include "types/spritestatus.h"
#include "types/spritestatushandler.h"
#include "utils/bits.h"
#include "utils/fp16.h"
#include "utils/stageno.h"
#include "action.h"
#include "constants.h"
#include "title.h"
#include "unlze.h"
static void actclear_init(SKC_sprite_status* p_actwk);
static void actclear_move0(SKC_sprite_status* p_actwk);
static void actclear_move1(SKC_sprite_status* p_actwk);
static void actclear_move2(SKC_sprite_status* p_actwk);
static void actclear_name(SKC_sprite_status* p_actwk);
static void actclear_text(SKC_sprite_status* p_actwk);
static void actclear_timebonus(SKC_sprite_status* p_actwk);
static void actclear_ringbonus(SKC_sprite_status* p_actwk);
static void actclear_total(SKC_sprite_status* p_actwk);
static void actclear_bonus(SKC_sprite_status* p_actwk, unsigned short bonus);
static void actclear_bonus_move(SKC_sprite_status* p_actwk, unsigned short bonus);
static bool actclear_part_move(SKC_sprite_status* p_actwk);
static unsigned long score_to_nibbles(SKC_sprite_status* p_actwk, unsigned short score);
static unsigned long subtbl[5];
static unsigned long subtblh[5];
static unsigned short timebonustbl[8];
static SKC_overlay_element_init_data actclear_init_tbl[12];

extern sonic3_ram g_ram;


void actclear(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &actclear_init,
    &actclear_move0,
    &actclear_move1,
    &actclear_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void actclear_init(SKC_sprite_status* p_actwk) {
  bgmset(225);
  unlze_moduled(&g_mdVram[0xA400], actclear_cg);
  bool is_act_1 = g_ram.stageno != LAVA_REEF_BOSS && get_act(g_ram.stageno_i) == ACT_1;
  unsigned char* p_cg = is_act_1 ? act_digit_1_cg : act_digit_2_cg;
  p_actwk->u.obj.userflag = is_act_1 ? 0 : 0xFF;
  unlze_moduled(&g_mdVram[0xAD00], p_cg);

  switch (g_ram.play_type) {
    case PLAY_TYPE_SONIC_AND_MILES:
    case PLAY_TYPE_SONIC:
    default:
      p_cg = sonic_name_cg;
      break;
    case PLAY_TYPE_MILES:
      p_cg = !BIT_IS_SET(g_ram.mdstatus, 7) ? miles_name_cg : tails_name_cg;
      break;
    case PLAY_TYPE_KNUCKLES:
      p_cg = knuckles_name_cg;
      break;
  }

  unsigned char* p_vram = p_actwk->u.obj.userflag == 0 ? &g_mdVram[0xAF00] : &g_mdVram[0xB400];
  unlze_moduled(p_vram, p_cg);
  g_ram.pltime_f = 0;
  unsigned short seconds = g_ram.pltime.minutes * 60 + g_ram.pltime.seconds;
  if (seconds == 599) {
    g_ram.timebonus = 10000;
  }
  else {
    unsigned char timebonus_id = seconds / 30;
    if (timebonus_id >= 7) {
      timebonus_id = 7;
    }
    g_ram.timebonus = timebonustbl[timebonus_id];
  }
  g_ram.ringbonus = g_ram.plring * 10;
  g_ram.bonustotal = 0;
  p_actwk->u.obj.timer = 360;
  p_actwk->u.obj.actfree.actclear.part_cnt = 12;
  p_actwk->r_no += 2;
}


static void actclear_move0(SKC_sprite_status* p_actwk) {
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    for (int i = 0; i < 12; ++i) {
      result.actwk_ptr->r_ptr = actclear_init_tbl[i].r_ptr;
      result.actwk_ptr->u.obj.actfree.actclear_part.xdestination = actclear_init_tbl[i].xdestination;
      fp16_set_integer(&result.actwk_ptr->xposi, actclear_init_tbl[i].xposi);
      p_actwk->r_no = fp16_get_integer(result.actwk_ptr->xposi) < 0 ? 0 : 0xFF;
      fp16_set_integer(&result.actwk_ptr->yposi, actclear_init_tbl[i].yposi);
      result.actwk_ptr->patno = actclear_init_tbl[i].patno;
      result.actwk_ptr->sprhs = actclear_init_tbl[i].sprhs;
      result.actwk_ptr->colino = actclear_init_tbl[i].exit_no;
      result.actwk_ptr->actflg.compound = 1;
      result.actwk_ptr->patbase = actclearpat;
      result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
      result.actwk_ptr = actwkchk_next(result.actwk_ptr, &result.remaining_slot_cnt);
      if (result.actwk_ptr == 0) break;
    }

    p_actwk->r_no += 2;
    if (get_act(g_ram.stageno_i) == ACT_1
        && get_zone(g_ram.stageno_i) != ANGEL_ISLAND
        && get_zone(g_ram.stageno_i) != ICECAP) {
      g_ram.event_flag_3 = 0xFF;
    }
  }
}


static void actclear_move1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
    if (p_actwk->u.obj.timer == 289) {
      g_ram.actwk[0].u.play.air_timer = 30;
      g_ram.actwk[1].u.play.air_timer = 30;
      bgmset(41);
    }
  }
  else {
    unsigned short points = 0;
    if (g_ram.timebonus != 0) {
      points += 10;
      g_ram.timebonus -= 10;
    }
    if (g_ram.ringbonus != 0) {
      points += 10;
      g_ram.ringbonus -= 10;
    }
    g_ram.bonustotal += points;
    if (points != 0) {
      scoreup(points);
      if (!(g_ram.gametimer & 3)) {
        soundset(91);
      }
    }
    else {
      soundset(176);
      if (g_ram.stageno == SKY_SANCTUARY_ACT_SONIC || p_actwk->u.obj.userflag != 0) {
        g_ram.disable_interrupts_sram = 255;
        save_game();
      }
      p_actwk->u.obj.timer = 90;
      p_actwk->r_no += 2;
      actclear_move2(p_actwk);
    }
  }
}


static void actclear_move2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
  }
  else if (p_actwk->u.obj.actfree.actclear.part_cnt != 0) {
    ++p_actwk->u.obj.actfree.actclear.current_exit_no;
  }
  else if (get_zone(g_ram.stageno) == SKY_SANCTUARY
           || get_zone(g_ram.stageno) == LAVA_REEF_BOSS_AND_HIDDEN_PALACE
           || get_act(g_ram.stageno_i) != ACT_1) {
    g_ram.act_clear_flag = 0;
    g_ram.act_start_flag = 0xFF;
    frameout(p_actwk);
  }
  else {
    set_act(&g_ram.stageno_i, ACT_2);
    g_ram.markerno = 0;
    g_ram.marker_flag = 0;
    g_ram.act_clear_flag = 0;
    if (get_zone(g_ram.stageno) != SANDOPOLIS && get_zone(g_ram.stageno) != DEATH_EGG) {
      p_actwk->r_ptr = &title;
      p_actwk->r_no = 0;
      p_actwk->u.obj.actfree.title.act_start_flag = 0xFF;
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void actclear_name(SKC_sprite_status* p_actwk) {
  switch (g_ram.play_type) {
    case PLAY_TYPE_SONIC:
    case PLAY_TYPE_SONIC_AND_MILES:
    default:
      break;
    case PLAY_TYPE_MILES:
      ++p_actwk->patno;
      if (!BIT_IS_SET(g_ram.mdstatus, 7)) {
        ++p_actwk->patno;
        fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 8);
        p_actwk->u.obj.actfree.actclear_part.xdestination += 8;
        p_actwk->sprhs -= 8;
      }
      break;
    case PLAY_TYPE_KNUCKLES:
      p_actwk->patno += 3;
      p_actwk->xposi -= 48;
      p_actwk->u.obj.actfree.actclear_part.xdestination -= 48;
      p_actwk->sprhs += 48;
      break;
  }

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->sproffset = p_parentwk->u.obj.userflag == 0 ? 0 : 40;
  p_actwk->r_ptr = &actclear_text;
  actclear_text(p_actwk);
}


static void actclear_text(SKC_sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actionsub(p_actwk);
  }
}


static void actclear_timebonus(SKC_sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actclear_bonus(p_actwk, g_ram.timebonus);
  }
}


static void actclear_ringbonus(SKC_sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actclear_bonus(p_actwk, g_ram.ringbonus);
  }
}


static void actclear_total(SKC_sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actclear_bonus(p_actwk, g_ram.bonustotal);
  }
}


static void actclear_bonus(SKC_sprite_status* p_actwk, unsigned short bonus) {
  actclear_bonus_move(p_actwk, bonus);
  actionsub(p_actwk);
}


static void actclear_bonus_move(SKC_sprite_status* p_actwk, unsigned short bonus) {
  p_actwk->u.compound.child_cnt = 7;
  unsigned long decimal_bonus = rotate_long_left(score_to_nibbles(p_actwk, bonus), 4);
  short xposi = fp16_get_integer(p_actwk->xposi - 56);
  short yposi = fp16_get_integer(p_actwk->yposi);
  unsigned char unknown = 0;

  for (int i = 0; i < p_actwk->u.compound.child_cnt; ++i) {
    p_actwk->u.compound.children[i].xposi = xposi;
    p_actwk->u.compound.children[i].yposi = yposi;
    decimal_bonus = rotate_long_left(decimal_bonus, 4);
    unsigned char patno = decimal_bonus & 0xF;
    if (patno != 0) {
      unknown = 1;
    }
    p_actwk->u.compound.children[i].patno = patno + unknown;
    xposi += 8;
  }
}


static bool actclear_part_move(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actfree.actclear.current_exit_no != 0) {
    if (p_actwk->actflg.onscreen == 0) {
      --p_parentwk->u.obj.actfree.actclear.part_cnt;
      frameout(p_actwk);
      return true;
    }
    if (p_parentwk->u.obj.actfree.actclear.current_exit_no >= p_actwk->colino) {
      short xposi = -32;
      if (p_actwk->r_no != 0) {
        xposi = -xposi;
      }
      xposi += fp16_get_integer(p_actwk->xposi);
      fp16_set_integer(&p_actwk->xposi, xposi);
    }
  }
  else {
    short xspeed = 16;
    short xposi = fp16_get_integer(p_actwk->xposi);
    if (xposi != p_actwk->u.obj.actfree.actclear_part.xdestination) {
      if (xposi >= p_actwk->u.obj.actfree.actclear_part.xdestination) {
        xspeed = -xspeed;
      }
      xposi += xspeed;
    }
    fp16_set_integer(&p_actwk->xposi, xposi);
  }
  return false;
}


static unsigned long score_to_nibbles(SKC_sprite_status* p_actwk, unsigned short score) {
  unsigned long result = 0;
  unsigned long wk = score;

  for (int i = 0; i < 5; ++i) {
    unsigned long wk2 = wk % subtbl[i];
    wk /= subtbl[i];
    wk *= subtblh[i];
    result += wk;
    wk = wk2;
  }

  return result;
}


static unsigned long subtbl[5] = {
  10000, 1000, 100, 10, 1
};


static unsigned long subtblh[5] = {
  65536, 4096, 256, 16, 1
};

static unsigned short timebonustbl[8] = {
  5000, 5000, 1000, 500, 400, 300, 100, 10
};


static SKC_overlay_element_init_data actclear_init_tbl[12] = {
  { &actclear_name,      224, -544, 184, 19,  72, 1 },
  { &actclear_text,      304, -464, 184, 17,  48, 1 },
  { &actclear_text,      232, 1128, 204, 16, 112, 3 },
  { &actclear_text,      352, 1248, 188, 15,  56, 3 },
  { &actclear_text,      192, 1216, 240, 14,  32, 5 },
  { &actclear_text,      232, 1256, 240, 12,  48, 5 },
  { &actclear_timebonus, 376, 1400, 240,  1,  64, 5 },
  { &actclear_text,      192, 1280, 256, 13,  32, 7 },
  { &actclear_text,      232, 1320, 256, 12,  48, 7 },
  { &actclear_ringbonus, 376, 1464, 256,  1,  64, 7 },
  { &actclear_text,      212, 1364, 284, 11,  48, 9 },
  { &actclear_total,     376, 1528, 284,  1,  64, 9 }
};
