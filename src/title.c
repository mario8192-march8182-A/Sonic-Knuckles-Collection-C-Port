#include "globals.h"
#include "macros.h"
#include "util.h"
#include "types/titlezonesinitdata.h"
#include "title.h"
#include "004xxxxx.h"
#include "002.h"
#include "resources.h"
#include "zone08/gost08.h"
static void title_init(sprite_status* p_actwk);
static void title_move0(sprite_status* p_actwk);
static void title_move1(sprite_status* p_actwk);
static void title_move2(sprite_status* p_actwk);
static void title_red_banner(sprite_status* p_actwk);
static void title_name(sprite_status* p_actwk);
static void title_element(sprite_status* p_actwk);
static void title_act(sprite_status* p_actwk);
static void title_element2(sprite_status* p_actwk);
static unsigned char* title_zones_tiles[22];
static title_zones_init_data title_zones_init_tbl[7];


void title(sprite_status* p_actwk) {
  static sprite_status_handler act_tbl[4] = {
    &title_init,
    &title_move0,
    &title_move1,
    &title_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void title_init(sprite_status* p_actwk) {
  if (g_ram.stageno == ENDING) goto LAB_frameout;
  if (GET_ZONE(g_ram.stageno) >= AZURE_LAKE && GET_ZONE(g_ram.stageno) <= ENDLESS_MINE) { // unsigned
    p_actwk->actfree.title.vs_flag = 255;
LAB_frameout:
    frameout(p_actwk);
    return;
  }
  Queue_Kos_Module(title_red_banner_tiles, 40960);
  unsigned char* p_tiles = 0;
  if (g_sonic3Alone == 0) {
    p_tiles = title_sk_tiles;
    if (g_ram.cartridge == 0) {
      p_tiles = title_s3k_tiles;
    }
    Queue_Kos_Module(p_tiles, 41472);
  }
  p_tiles = title_act2_tiles;
  if (g_ram.stageno != LAVA_REEF_BOSS
      && g_ram.stageno != DEATH_EGG_BOSS
      && GET_ACT(g_ram.stageno_i) == ACT_1) {
    p_tiles = title_act1_tiles;
  }
  Queue_Kos_Module(p_tiles, 42912);
  unsigned char title_zones_index = LAVA_REEF;
  if (g_ram.stageno != LAVA_REEF_BOSS) {
    title_zones_index = 13;
    if (g_ram.stageno != HIDDEN_PALACE) {
      title_zones_index = DEATH_EGG;
      if (g_ram.stageno != DEATH_EGG_BOSS) {
        title_zones_index = GET_ZONE(g_ram.stageno_i);
      }
    }
  }
  Queue_Kos_Module(title_zones_tiles[title_zones_index], 43424);
  p_actwk->actfree.title.delay_timer = 90;
  p_actwk->actfree.title.current_exit_no = 0;
  p_actwk->actfree.title.unknown_flag = 255;
  p_actwk->r_no += 2;
}


static void title_move0(sprite_status* p_actwk) {
  if (g_ram.divdev_modules != 0) return;
  sprite_status* p_new_actwk;
  short slot_cnt;
  bool created = Create_New_Sprite3(p_actwk, &p_new_actwk, &slot_cnt);
  if (!created) return;
  title_zones_init_data* p_init_data = 0;
  short cnt = 0;
  if (GET_ZONE(g_ram.stageno) != LAVA_REEF_BOSS_AND_HIDDEN_PALACE && g_ram.stageno != DEATH_EGG_BOSS) {
    p_init_data = &title_zones_init_tbl[5];
    cnt = 1;
    if (GET_ZONE(g_ram.stageno) >= ZONE_GUMBALL_MACHINE) goto loop;
  }
  p_init_data = &title_zones_init_tbl[0];
  cnt = 3;
  if (p_actwk->actfree.title.vs_flag != 0) {
    p_init_data = &title_zones_init_tbl[4];
    cnt = 0;
  }

loop:
  do {
    ++p_actwk->actfree.title.part_cnt;
    p_new_actwk->r_ptr = p_init_data->r_ptr;
    p_new_actwk->actfree.title_part.x_destination = p_init_data->x_destination;
    util__assign_high(&p_new_actwk->xposi, p_init_data->xposi);
    util__assign_high(&p_new_actwk->yposi, p_init_data->yposi);
    p_new_actwk->patno = p_init_data->patno;
    p_new_actwk->sprhs = p_init_data->sprhs;
    p_new_actwk->colino = p_init_data->colino;
    p_new_actwk->actflg = 1 << FLG_COMPOUND;
    p_new_actwk->patbase = titlepat;
    p_new_actwk->actfree.title_part.oya = p_actwk - g_ram.actwk;
    bool created = Create_New_Sprite4(&p_new_actwk, slot_cnt);
    if (!created) break;
    --cnt;
  } while (cnt != -1);

  if (p_actwk->actfree.title.act_start_flag != 0) {
    if (GET_ZONE(g_ram.stageno) == LAUNCH_BASE) {
      Load_PLC(p_actwk, 37);
    }
  }
  p_actwk->r_no += 2;
}


static void title_move1(sprite_status* p_actwk) {
  if (p_actwk->actfree.title.wait_flag != 0) {
    p_actwk->actfree.title.wait_flag = 0;
    return;
  }
  if (p_actwk->actfree.title.act_start_flag != 0) {
    g_ram.pltime.hours = 0;
    g_ram.pltime.minutes = 0;
    g_ram.pltime.seconds = 0;
    g_ram.pltime.frames = 0;
    g_ram.plring = 0;
    g_ram.plring_act = 0;
    g_ram.plring_f2 = 0;
    g_ram.DAT_08fffed2 = 0;
    g_ram.pl2ring = 0;
    g_ram.pl2ring_act = 0;
    g_ram.pltime_f = 255;
    g_ram.plring_f = 255;
    g_ram.actwk[0].userflag1 = 30;
    g_ram.actwk[1].userflag1 = 30;
    reset_bgm(p_actwk);
  }
  p_actwk->actfree.title.unknown_flag = 0;
  p_actwk->r_no += 2;
}


static void title_move2(sprite_status* p_actwk) {
  if (p_actwk->actfree.title.delay_timer != 0) {
    --p_actwk->actfree.title.delay_timer;
    return;
  }
  if (p_actwk->actfree.title.part_cnt != 0) {
    ++p_actwk->actfree.title.current_exit_no;
    return;
  }
  if (p_actwk->actfree.title.vs_flag != 0) goto LAB_frameout;
  if (g_ram.stageno == SANDOPOLIS_ACT_2) {
    sprite_status* p_new_actwk;
    short slot_cnt;
    bool created = Create_New_Sprite(&p_new_actwk, &slot_cnt);
    if (created) {
      p_new_actwk->r_ptr = &gost08;
    }
  }
  if (GET_ZONE(g_ram.stageno) != LAVA_REEF_BOSS_AND_HIDDEN_PALACE
      && g_ram.stageno == DEATH_EGG_BOSS
      && GET_ZONE(g_ram.stageno) >= ZONE_GUMBALL_MACHINE) {
    goto LAB_frameout;
  }
  if (p_actwk->actfree.title.act_start_flag != 0) {
    g_ram.act_start_flag = 255;
  }
  else if (GET_ZONE(g_ram.stageno) == DOOMSDAY) goto LAB_frameout;
  else if (g_ram.stageno == DEATH_EGG_BOSS) goto LAB_frameout;
  else {
    Load_PLC_Raw(p_actwk, &toge_cg_tbl);
  }
  if (g_ram.stageno == DEATH_EGG_BOSS) goto LAB_frameout;
  LoadEnemyArt();
  set_friend_cg(p_actwk);

LAB_frameout:
  frameout(p_actwk);
}


static void title_red_banner(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.title_part.oya];
  if (p_parentwk->actfree.title.current_exit_no != 0) {
    if (!BIT_IS_SET(p_actwk->actflg, FLG_ONSCREEN)) {
      --p_parentwk->actfree.title.part_cnt;
      frameout(p_actwk);
      return;
    }
    if (p_parentwk->actfree.title.current_exit_no >= p_actwk->colino) { // unsigned
      p_actwk->yposi -= SHORT_TO_LONG_HIGH(32);
    }
  }
  else {
    if (LONG_HIGH(p_actwk->yposi) != p_actwk->actfree.title_part.x_destination) {
      p_actwk->yposi += SHORT_TO_LONG_HIGH(16);
      p_parentwk->actfree.title.wait_flag = 255;
    }
  }
  p_actwk->sprvs = 112;
  actionsub(p_actwk);
}


static void title_name(sprite_status* p_actwk) {
  p_actwk->patno += GET_ZONE(g_ram.stageno_i);
  unsigned char patno = 13;
  if (g_ram.stageno != LAVA_REEF_BOSS) {
    patno = 17;
    if (g_ram.stageno != HIDDEN_PALACE) {
      patno = 15;
      if (g_ram.stageno != DEATH_EGG_BOSS) goto LAB_00416aab;
    }
  }
  p_actwk->patno = patno;

LAB_00416aab:
  p_actwk->r_ptr = &title_element;
}


static void title_element(sprite_status* p_actwk) {
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.title_part.oya];
  if (p_parentwk->actfree.title.current_exit_no != 0) {
    if (!BIT_IS_SET(p_actwk->actflg, FLG_HFLIP)) {
      --p_parentwk->actfree.title.part_cnt;
      frameout(p_actwk);
      return;
    }
    else if (p_parentwk->actfree.title.current_exit_no >= p_actwk->colino) { // unsigned
      p_actwk->xposi += SHORT_TO_LONG_HIGH(32);
    }
  }
  else if (LONG_HIGH(p_actwk->xposi) != p_actwk->actfree.title_part.x_destination) {
    p_actwk->xposi -= SHORT_TO_LONG_HIGH(16);
    p_parentwk->actfree.title.wait_flag = 255;
  }
  actionsub(p_actwk);
}


static void title_act(sprite_status* p_actwk) {
  p_actwk->r_ptr = &title_element;
  if (GET_ZONE(g_ram.stageno) != SKY_SANCTUARY
      && GET_ZONE(g_ram.stageno) != DOOMSDAY
      && g_ram.stageno != HIDDEN_PALACE) {
    title_element(p_actwk);
  }
  else {
    sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.title_part.oya];
    --p_parentwk->actfree.title.part_cnt;
    frameout(p_actwk);
  }
}


static void title_element2(sprite_status* p_actwk) {
  p_actwk->actflg = 0;
  sprite_status* p_parentwk = &g_ram.actwk[p_actwk->actfree.title_part.oya];
  if (p_parentwk->actfree.title.current_exit_no != 0) {
    if (LONG_HIGH(p_actwk->xposi) >= 524) { // unsigned
      --p_parentwk->actfree.title.part_cnt;
      frameout(p_actwk);
      return;
    }
    else if (p_parentwk->actfree.title.current_exit_no >= p_actwk->colino) { // unsigned
      p_actwk->xposi += SHORT_TO_LONG_HIGH(32);
    }
  }
  else if (LONG_HIGH(p_actwk->xposi) != p_actwk->actfree.title_part.x_destination) {
    p_actwk->xposi -= SHORT_TO_LONG_HIGH(16);
    p_parentwk->actfree.title.wait_flag = 255;
  }
  actionsub(p_actwk);
}


static unsigned char* title_zones_tiles[22] = {
  title_angel_island_tiles,
  title_hydrocity_tiles,
  title_marble_garden_tiles,
  title_carnival_night_tiles,
  title_flying_battery_tiles,
  title_icecap_tiles,
  title_launch_base_tiles,
  title_mushroom_hill_tiles,
  title_sandopolis_tiles,
  title_lava_reef_tiles,
  title_sky_sanctuary_tiles,
  title_death_egg_tiles,
  title_doomsday_tiles,
  title_hidden_palace_tiles,
  title_azure_lake_tiles,
  title_balloon_park_tiles,
  title_desert_palace_tiles,
  title_chrome_gadget_tiles,
  title_endless_mine_tiles,
  title_bonus_stage_tiles,
  title_bonus_stage_tiles,
  title_bonus_stage_tiles
};


static title_zones_init_data title_zones_init_tbl[7] = {
  { &title_name,       288, 608, 224,  4, 128, 3 },
  { &title_element,    380, 764, 256,  3,  36, 5 },
  { &title_act,        388, 836, 288,  2,  28, 7 },
  { &title_red_banner, 192, 224,  16,  1,   0, 1 },
  { &title_element2,   348, 540, 188, 18, 128, 1 },
  { &title_element,    200, 392, 232, 19, 128, 1 },
  { &title_element,    296, 488, 232, 20, 128, 1 }
};
