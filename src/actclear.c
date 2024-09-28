#include "globals.h"
#include "macros.h"
#include "types/actclearinitdata.h"
#include "actclear.h"
#include "004xxxxx.h"
#include "resources.h"
#include "title.h"
static void actclear_init(sprite_status* p_actwk);
static void actclear_move0(sprite_status* p_actwk);
static void actclear_move1(sprite_status* p_actwk);
static void actclear_move2(sprite_status* p_actwk);
static void actclear_name(sprite_status* p_actwk);
static void actclear_text(sprite_status* p_actwk);
static void actclear_timebonus(sprite_status* p_actwk);
static void actclear_ringbonus(sprite_status* p_actwk);
static void actclear_total(sprite_status* p_actwk);
static void actclear_bonus(sprite_status* p_actwk, unsigned short bonus);
static void actclear_bonus_move(sprite_status* p_actwk, unsigned short bonus);
static bool actclear_part_move(sprite_status* p_actwk);
static unsigned long score_to_nibbles(sprite_status* p_actwk, unsigned short score);
static unsigned long subtbl[5];
static unsigned long subtblh[5];
static unsigned short timebonustbl[8];
static actclear_init_data actclear_init_tbl[12];


void actclear(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[5] = {
    &actclear_init,
    &actclear_move0,
    &actclear_move1,
    &actclear_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void actclear_init(sprite_status* p_actwk) {
  bgmset(225);
  Queue_Kos_Module(&actclear_tiles, 41984);
  void* p_data = &title_act2_tiles;
  unsigned char userflags = 255;
  if (g_mdRam.stageno != LAVA_REEF_BOSS && GET_ACT(g_mdRam.stageno_i) == ACT_1) {
    p_data = &title_act1_tiles;
    userflags = 0;
  }
  p_actwk->userflag1 = userflags;
  p_actwk->userflag2 = userflags;
  Queue_Kos_Module(p_data, 44288);
  p_data = &actclear_sonic_tiles;
  if (g_mdRam.plmode > 1) { // unsigned
    p_data = &actclear_knuckles_tiles;
    if (g_mdRam.plmode != 3) {
      p_data = &actclear_miles_tiles;
      if (BIT_7_IS_SET(g_mdRam.mdstatus)) {
        p_data = &actclear_tails_tiles;
      }
    }
  }
  unsigned short act_id = 44800;
  if (p_actwk->userflag1 != 0 || p_actwk->userflag2 != 0) {
    act_id = 46080;
  }
  Queue_Kos_Module(p_data, act_id);
  g_mdRam.pltime_f = 0;
  unsigned long seconds = g_mdRam.pltime.minutes * 60 + g_mdRam.pltime.seconds;
  if (seconds == 599) {
    g_mdRam.timebonus = 10000;
  }
  else {
    unsigned char bonus_id = seconds / 30;
    if (bonus_id >= 7) { // unsigned
      bonus_id = 7;
    }
    g_mdRam.timebonus = timebonustbl[bonus_id];
  }
  g_mdRam.ringbonus = g_mdRam.plring * 10;
  g_mdRam.frame_bonus = 0;
  p_actwk->actfree.actclear.delay_timer = 360;
  p_actwk->actfree.actclear.part_cnt = 12;
  p_actwk->r_no += 2;
}


static void actclear_move0(sprite_status* p_actwk) {
  if (g_mdRam.divdev_modules != 0) return;
  short slot_cnt;
  sprite_status* p_new_actwk;
  bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
  if (!created) return;
  actclear_init_data* p_data = &actclear_init_tbl[0];
  short cnt = 11;

  do {
    compound_sprite_status* p_compoundwk = (compound_sprite_status*)p_new_actwk;
    p_new_actwk->r_ptr = p_data->r_ptr;
    p_actwk->actfree.actclear_part.x_destination = p_data->x_destination;
    p_compoundwk->xposi = p_data->xposi;
    if (p_compoundwk->xposi < 0) {
      p_actwk->r_no = 0;
    }
    else {
      p_actwk->r_no = 255;
    }
    p_compoundwk->yposi = p_data->yposi;
    p_new_actwk->patno = p_data->patno;
    p_new_actwk->sprhs = p_data->sprhs;
    p_new_actwk->colino = p_data->exit_no;
    p_new_actwk->actflg = 1 << FLG_COMPOUND;
    p_new_actwk->patbase = actclearpat;
    p_new_actwk->actfree.actclear_part.oya = p_actwk - g_mdRam.actwk;
    bool created = Create_New_Sprite4(&p_new_actwk, slot_cnt);
    if (!created) break;
    --cnt;
  } while (cnt != -1);

  p_actwk->r_no += 2;
  if (GET_ACT(g_mdRam.stageno_i) == ACT_1
      && GET_ZONE(g_mdRam.stageno_i) != ANGEL_ISLAND
      && GET_ZONE(g_mdRam.stageno_i) != ICECAP) {
    g_mdRam.event_flag_3 = 255;
  }
}


static void actclear_move1(sprite_status* p_actwk) {
  if (p_actwk->actfree.actclear.delay_timer != 0) {
    --p_actwk->actfree.actclear.delay_timer;
    if (p_actwk->actfree.actclear.delay_timer == 289) {
      g_mdRam.actwk[0].userflag1 = 30;
      g_mdRam.actwk[1].userflag1 = 30;
      bgmset(41);
    }
  }
  else {
    short points = 0;
    if (g_mdRam.timebonus != 0) {
      points += 10;
    }
    if (g_mdRam.ringbonus != 0) {
      points += 10;
    }
    g_mdRam.frame_bonus += points;
    if (points != 0) {
      scoreup(points);
      if (!(g_mdRam.gametimer & 3)) {
        soundset(91);
      }
    }
    else {
      soundset(176);
      if (g_mdRam.stageno == SKY_SANCTUARY_ACT_SONIC
          || (p_actwk->userflag1 != 0 || p_actwk->userflag2 != 0)) {
        g_mdRam.disable_interrupts_sram = 255;
        SaveGame();
      }
      p_actwk->actfree.actclear.delay_timer = 90;
      p_actwk->r_no += 2;
      actclear_move2(p_actwk);
    }
  }
}


static void actclear_move2(sprite_status* p_actwk) {
  if (p_actwk->actfree.actclear.delay_timer != 0) {
    --p_actwk->actfree.actclear.delay_timer;
  }
  else if (p_actwk->actfree.actclear.part_cnt != 0) {
    ++p_actwk->actfree.actclear.current_exit_no;
  }
  else if (GET_ZONE(g_mdRam.stageno) == SKY_SANCTUARY
      || GET_ZONE(g_mdRam.stageno) == LAVA_REEF_BOSS_AND_HIDDEN_PALACE
      || GET_ACT(g_mdRam.stageno_i) != ACT_1) {
    g_mdRam.act_clear_flag = 0;
    g_mdRam.act_start_flag = 255;
    frameout(p_actwk);
  }
  else {
    SET_ACT(g_mdRam.stageno_i, ACT_2);
    g_mdRam.markerno = 0;
    g_mdRam.marker_flag = 0;
    g_mdRam.act_clear_flag = 0;
    if (GET_ZONE(g_mdRam.stageno) != SANDOPOLIS && GET_ZONE(g_mdRam.stageno) != DEATH_EGG) {
      p_actwk->r_ptr = &title;
      p_actwk->r_no = 0;
      p_actwk->actfree.title.act_start_flag = 255;
    }
    else {
      frameout(p_actwk);
    }
  }
}


static void actclear_name(sprite_status* p_actwk) {
  compound_sprite_status* p_compoundwk = (compound_sprite_status*)p_actwk;

  switch (g_mdRam.plmode) {
    case TEAM_KNUCKLES:
      p_actwk->patno += 3;
      p_compoundwk->xposi -= 48;
      p_actwk->actfree.actclear_part.x_destination -= 48;
      p_actwk->sprhs += 48;
      break;
    case TEAM_MILES:
      ++p_actwk->patno;
      if (!BIT_7_IS_SET(g_mdRam.mdstatus)) {
        ++p_actwk->patno;
        p_compoundwk->xposi += 8;
        p_actwk->actfree.actclear_part.x_destination += 8;
        p_actwk->sprhs -= 8;
      }
      break;
    case TEAM_SONIC:
    case TEAM_SONIC_AND_MILES:
      break;
  }

  unsigned short sproffset = 0;
  sprite_status* p_parentwk = &g_mdRam.actwk[p_actwk->actfree.actclear_part.oya];
  if (p_parentwk->userflag1 != 0 || p_parentwk->userflag2 != 0) {
    sproffset = 40;
  }
  p_actwk->sproffset = sproffset;
  p_actwk->r_ptr = &actclear_text;
  actclear_text(p_actwk);
}


static void actclear_text(sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actionsub(p_actwk);
  }
}


static void actclear_timebonus(sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actclear_bonus(p_actwk, g_mdRam.timebonus);
  }
}


static void actclear_ringbonus(sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actclear_bonus(p_actwk, g_mdRam.ringbonus);
  }
}


static void actclear_total(sprite_status* p_actwk) {
  bool fout = actclear_part_move(p_actwk);
  if (!fout) {
    actclear_bonus(p_actwk, g_mdRam.frame_bonus);
  }
}


static void actclear_bonus(sprite_status* p_actwk, unsigned short bonus) {
  actclear_bonus_move(p_actwk, bonus);
  actionsub(p_actwk);
}


static void actclear_bonus_move(sprite_status* p_actwk, unsigned short bonus) {
  compound_sprite_status* p_compoundwk = (compound_sprite_status*)p_actwk;
  p_compoundwk->child_cnt = 7;
  unsigned long decimal_bonus = score_to_nibbles(p_actwk, bonus);
  decimal_bonus = decimal_bonus & 0x0FFFFFFF << 4 | decimal_bonus & 0xF0000000 >> 28;
  sprite_status_child* p_child = &p_compoundwk->children[0];
  short xposi = p_compoundwk->xposi - 56;
  short yposi = p_compoundwk->yposi;
  unsigned short unknown1 = 0;
  unsigned short cnt = 6;

  do {
    p_child->xposi = xposi;
    p_child->yposi = yposi;
    decimal_bonus = decimal_bonus & 0x0FFFFFFF << 4 | decimal_bonus & 0xF0000000 >> 28;
    unsigned short unknown2 = decimal_bonus & 0xF;
    if (unknown2 != 0) {
      unknown1 = 1;
    }
    unknown2 += unknown1;
    p_child->patno = unknown2;
    xposi += 8;
    ++p_child;
    --cnt;
  } while (cnt != -1);
}


static bool actclear_part_move(sprite_status* p_actwk) {
  compound_sprite_status* p_compoundwk = (compound_sprite_status*)p_actwk;
  sprite_status* p_parentwk = &g_mdRam.actwk[p_actwk->actfree.actclear_part.oya];
  short xposi = p_parentwk->actfree.actclear.current_exit_no;
  if (p_parentwk->actfree.actclear.current_exit_no != 0) {
    if (!BIT_IS_SET(p_actwk->actflg, FLG_ONSCREEN)) {
      --p_parentwk->actfree.actclear.part_cnt;
      frameout(p_actwk);
      return true;
    }
    if (p_parentwk->actfree.actclear.current_exit_no < p_actwk->colino) return false;
    if (p_actwk->r_no != 0) {
      xposi = -xposi;
    }
    xposi += p_compoundwk->xposi;
  }
  else {
    short xspeed = 16;
    xposi = p_compoundwk->xposi;
    int compare_result = 1;
    if (xposi == p_actwk->actfree.actclear_part.x_destination) {
      compare_result = 0;
    }
    else if (xposi < p_actwk->actfree.actclear_part.x_destination) {
      compare_result = -1;
    }

    switch (compare_result) {
      case 1:
        xspeed = -xspeed;
        // fall-through
      case -1:
        xposi += xspeed;
        break;
      case 0:
        break;
    }
  }
  p_compoundwk->xposi = xposi;

  return false;
}


static unsigned long score_to_nibbles(sprite_status* p_actwk, unsigned short score) {
  g_mdRam.DAT_08ffef40 = 0;
  unsigned char pos = 0;

  do {
    g_mdRam.DAT_08ffef40 += score / subtbl[pos] * subtblh[pos];
    score %= subtbl[pos];
    ++pos;
  } while (pos < 5); // unsigned

  return g_mdRam.DAT_08ffef40;
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


static actclear_init_data actclear_init_tbl[12] = {
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
