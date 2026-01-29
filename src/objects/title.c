#include "title.h"
#include <stdbool.h>
#include <string.h>
#include "../data/cg/actdigits.h"
#include "../data/cg/title.h"
#include "../data/cg/zonenames.h"
#include "../data/pat/title.h"
#include "../types/actwkchkresult.h"
#include "../types/overlayelementinitdata.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../shared.h"
#include "../unlze.h"
#include "zone08/gost08.h"
static void title_init(SKC_sprite_status* p_actwk);
static void title_move0(SKC_sprite_status* p_actwk);
static void title_move1(SKC_sprite_status* p_actwk);
static void title_move2(SKC_sprite_status* p_actwk);
static void title_red_banner(SKC_sprite_status* p_actwk);
static void title_name(SKC_sprite_status* p_actwk);
static void title_element(SKC_sprite_status* p_actwk);
static void title_act(SKC_sprite_status* p_actwk);
static void title_element2(SKC_sprite_status* p_actwk);
static unsigned char* zone_name_cg_tbl[22];
static SKC_overlay_element_init_data title_init_tbl[7];

extern sonic3_ram g_ram;
extern bool g_sonic3_alone;


void title(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[4] = {
    &title_init,
    &title_move0,
    &title_move1,
    &title_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void title_init(SKC_sprite_status* p_actwk) {
  if (g_ram.stageno == ENDING) {
    frameout(p_actwk);
  }
  else if (get_zone(g_ram.stageno) >= AZURE_LAKE && get_zone(g_ram.stageno) <= ENDLESS_MINE) {
    p_actwk->u.obj.actfree.title.vs_flag = 0xFF;
    frameout(p_actwk);
  }
  unlze_moduled(&g_mdVram[0xA000], title_red_banner_cg);
  unsigned char* p_cg;
  if (!g_sonic3_alone) {
    p_cg = g_ram.cartridge != 0 ? title_sk_cg : title_s3k_cg;
    unlze_moduled(&g_mdVram[0xA200], p_cg);
  }
  if (g_ram.stageno == LAVA_REEF_BOSS || g_ram.stageno == DEATH_EGG_BOSS || get_act(g_ram.stageno_i) == ACT_1) {
    p_cg = act_digit_2_cg;
  }
  else {
    p_cg = act_digit_1_cg;
  }
  unlze_moduled(&g_mdVram[0xA7A0], p_cg);

  switch (g_ram.stageno) {
    case LAVA_REEF_BOSS:
      p_cg = zone_name_cg_tbl[LAVA_REEF];
      break;
    case HIDDEN_PALACE:
      p_cg = zone_name_cg_tbl[13];
      break;
    case DEATH_EGG_BOSS:
      p_cg = zone_name_cg_tbl[DEATH_EGG];
      break;
    default:
      p_cg = zone_name_cg_tbl[get_zone(g_ram.stageno_i)];
      break;
  }

  unlze_moduled(&g_mdVram[0xA9A0], p_cg);
  p_actwk->u.obj.timer = 90;
  p_actwk->u.obj.actfree.title.current_exit_no = 0;
  p_actwk->u.obj.actfree.title.unknown_flag = 0xFF;
  p_actwk->r_no += 2;
}


static void title_move0(SKC_sprite_status* p_actwk) {
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    SKC_overlay_element_init_data* p_data;
    int cnt;
    if (p_actwk->u.obj.actfree.title.vs_flag == 0) {
      if (get_zone(g_ram.stageno) < GUMBALL_MACHINE
          || get_zone(g_ram.stageno) == LAVA_REEF_BOSS_AND_HIDDEN_PALACE
          || g_ram.stageno == DEATH_EGG_BOSS) {
        p_data = title_init_tbl;
        cnt = 4;
      }
      else {
        p_data = &title_init_tbl[5];
        cnt = 2;
      }
    }
    else {
      p_data = &title_init_tbl[4];
      cnt = 1;
    }

    for (int i = 0; i < cnt; ++i) {
      ++p_actwk->u.obj.actfree.title.part_cnt;
      result.actwk_ptr->r_ptr = p_data->r_ptr;
      result.actwk_ptr->u.obj.actfree.title_part.xdestination = p_data->xdestination;
      fp16_set_integer(&result.actwk_ptr->xposi, p_data->xposi);
      fp16_set_integer(&result.actwk_ptr->yposi, p_data->yposi);
      result.actwk_ptr->patno = p_data->patno;
      result.actwk_ptr->sprhs = p_data->sprhs;
      result.actwk_ptr->colino = p_data->exit_no;
      result.actwk_ptr->actflg.compound = 1;
      result.actwk_ptr->patbase = titlepat;
      result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
      result.actwk_ptr = actwkchk_next(result.actwk_ptr, &result.remaining_slot_cnt);
      if (result.actwk_ptr == 0) break;
    }

    if (p_actwk->u.obj.actfree.title.act_start_flag != 0 && get_zone(g_ram.stageno) == LAUNCH_BASE) {
      Load_PLC(p_actwk, 37);
    }
    p_actwk->r_no += 2;
  }
}


static void title_move1(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.actfree.title.wait_flag != 0) {
    p_actwk->u.obj.actfree.title.wait_flag = 0;
  }
  else {
    if (p_actwk->u.obj.actfree.title.act_start_flag != 0) {
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
      g_ram.pltime_f = 0xFF;
      g_ram.plring_f = 0xFF;
      g_ram.actwk[0].u.play.air_timer = 30;
      g_ram.actwk[1].u.play.air_timer = 30;
      reset_bgm();
    }
    p_actwk->u.obj.actfree.title.unknown_flag = 0;
    p_actwk->r_no += 2;
  }
}


static void title_move2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
  }
  else if (p_actwk->u.obj.actfree.title.part_cnt != 0) {
    ++p_actwk->u.obj.actfree.title.current_exit_no;
  }
  else {
    if (p_actwk->u.obj.actfree.title.vs_flag == 0) {
      if (g_ram.stageno == SANDOPOLIS_ACT_2) {
        SKC_actwkchk_result result = actwkchk();
        if (result.actwk_ptr != 0) {
          result.actwk_ptr->r_ptr = &gost08;
        }
      }
      else if (get_zone(g_ram.stageno) < GUMBALL_MACHINE
               || get_zone(g_ram.stageno) == LAVA_REEF_BOSS_AND_HIDDEN_PALACE
               || g_ram.stageno == DEATH_EGG_BOSS) {
        if (p_actwk->u.obj.actfree.title.act_start_flag != 0) {
          g_ram.act_start_flag = 0xFF;
        }
        else if (get_zone(g_ram.stageno) != DOOMSDAY && g_ram.stageno != DEATH_EGG_BOSS) {
          Load_PLC_Raw(p_actwk, &toge_cg_tbl);
        }
        if (g_ram.stageno != DEATH_EGG_BOSS) {
          LoadEnemyArt();
          set_friend_cg(p_actwk);
        }
      }
    }
    frameout(p_actwk);
  }
}


static void title_red_banner(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actfree.title.current_exit_no != 0) {
    if (p_actwk->actflg.onscreen == 0) {
      --p_parentwk->u.obj.actfree.title.part_cnt;
      frameout(p_actwk);
      return;
    }
    if (p_parentwk->u.obj.actfree.title.current_exit_no >= p_actwk->colino) {
      fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) - 32);
    }
  }
  else if (fp16_get_integer(p_actwk->yposi) != p_actwk->u.obj.actfree.title_part.xdestination) {
    fp16_set_integer(&p_actwk->yposi, fp16_get_integer(p_actwk->yposi) + 16);
    p_parentwk->u.obj.actfree.title.wait_flag = 0xFF;
  }
  p_actwk->sprvs = 112;
  actionsub(p_actwk);
}


static void title_name(SKC_sprite_status* p_actwk) {
  switch (g_ram.stageno) {
    default:
      p_actwk->patno += get_zone(g_ram.stageno_i);
      break;
    case LAVA_REEF_BOSS:
      p_actwk->patno = 13;
      break;
    case HIDDEN_PALACE:
      p_actwk->patno = 17;
      break;
    case DEATH_EGG_BOSS:
      p_actwk->patno = 15;
      break;
  }

  p_actwk->r_ptr = &title_element;
}


static void title_element(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actfree.title.current_exit_no != 0) {
    if (p_actwk->actflg.onscreen == 0) {
      --p_parentwk->u.obj.actfree.title.part_cnt;
      frameout(p_actwk);
      return;
    }
    if (p_parentwk->u.obj.actfree.title.current_exit_no >= p_actwk->colino) {
      fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 32);
    }
  }
  else if (fp16_get_integer(p_actwk->xposi) != p_actwk->u.obj.actfree.title_part.xdestination) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 16);
    p_parentwk->u.obj.actfree.title.wait_flag = 0xFF;
  }
  actionsub(p_actwk);
}


static void title_act(SKC_sprite_status* p_actwk) {
  p_actwk->r_ptr = &title_element;
  if (get_zone(g_ram.stageno) != SKY_SANCTUARY
      && get_zone(g_ram.stageno) != DOOMSDAY
      && g_ram.stageno != HIDDEN_PALACE) {
    title_element(p_actwk);
  }
  else {
    SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
    --p_parentwk->u.obj.actfree.title.part_cnt;
    frameout(p_actwk);
  }
}


static void title_element2(SKC_sprite_status* p_actwk) {
  memset(&p_actwk->actflg, 0, sizeof(p_actwk->actflg));
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actfree.title.current_exit_no != 0) {
    if ((unsigned short)fp16_get_integer(p_actwk->xposi) >= 524) {
      --p_parentwk->u.obj.actfree.title.part_cnt;
      frameout(p_actwk);
      return;
    }
    if (p_parentwk->u.obj.actfree.title.current_exit_no >= p_actwk->colino) {
      fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + 32);
    }
  }
  else if (fp16_get_integer(p_actwk->xposi) != p_actwk->u.obj.actfree.title_part.xdestination) {
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) - 16);
    p_parentwk->u.obj.actfree.title.wait_flag = 0xFF;
  }
  actionsub(p_actwk);
}


static unsigned char* zone_name_cg_tbl[22] = {
  angel_island_name_cg,
  hydrocity_name_cg,
  marble_garden_name_cg,
  carnival_night_name_cg,
  flying_battery_name_cg,
  icecap_name_cg,
  launch_base_name_cg,
  mushroom_hill_name_cg,
  sandopolis_name_cg,
  lava_reef_name_cg,
  sky_sanctuary_name_cg,
  death_egg_name_cg,
  doomsday_name_cg,
  hidden_palace_name_cg,
  azure_lake_name_cg,
  balloon_park_name_cg,
  desert_palace_name_cg,
  chrome_gadget_name_cg,
  endless_mine_name_cg,
  bonus_stage_name_cg,
  bonus_stage_name_cg,
  bonus_stage_name_cg
};


static SKC_overlay_element_init_data title_init_tbl[7] = {
  { &title_name,       288, 608, 224,  4, 128, 3 },
  { &title_element,    380, 764, 256,  3,  36, 5 },
  { &title_act,        388, 836, 288,  2,  28, 7 },
  { &title_red_banner, 192, 224,  16,  1,   0, 1 },
  { &title_element2,   348, 540, 188, 18, 128, 1 },
  { &title_element,    200, 392, 232, 19, 128, 1 },
  { &title_element,    296, 488, 232, 20, 128, 1 }
};
