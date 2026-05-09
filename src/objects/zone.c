#include "zone.h"
#include <stdbool.h>
#include <string.h>
#include "../data/cg/actdigits.h"
#include "../data/cg/characternames.h"
#include "../data/cg/clear.h"
#include "../data/cg/title.h"
#include "../data/cg/zonenames.h"
#include "../types/overlayelementinitdata.h"
#include "../types/sonic3ram.h"
#include "../types/spritestatus.h"
#include "../types/spritestatushandler.h"
#include "../utils/bits.h"
#include "../utils/fp16.h"
#include "../utils/stageno.h"
#include "../action.h"
#include "../actset.h"
#include "../constants.h"
#include "../dev.h"
#include "../score.h"
#include "../shared.h"
#include "../sound.h"
#include "kanban.h"
#include "zone08/gost08.h"
static void over_move(SKC_sprite_status* p_actwk);
static void over_wait(SKC_sprite_status* p_actwk);
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
static void clear_init(SKC_sprite_status* p_actwk);
static void clear_move0(SKC_sprite_status* p_actwk);
static void clear_move1(SKC_sprite_status* p_actwk);
static void clear_move2(SKC_sprite_status* p_actwk);
static void clear_name(SKC_sprite_status* p_actwk);
static void clear_text(SKC_sprite_status* p_actwk);
static void clear_timebonus(SKC_sprite_status* p_actwk);
static void clear_ringbonus(SKC_sprite_status* p_actwk);
static void clear_total(SKC_sprite_status* p_actwk);
static void clear_bonus(SKC_sprite_status* p_actwk, unsigned short bonus);
static void clear_bonus_move(SKC_sprite_status* p_actwk, unsigned short bonus);
static bool clear_part_move(SKC_sprite_status* p_actwk);
static unsigned long score_to_nibbles(SKC_sprite_status* p_actwk, unsigned short points);
static unsigned long subtbl[5];
static unsigned long subtblh[5];
static unsigned short timebonustbl[8];
static SKC_overlay_element_init_data clear_init_tbl[12];
static SKC_sprite_pattern* overpat[4];
static SKC_sprite_pattern oversp00;
static SKC_sprite_pattern oversp01;
static SKC_sprite_pattern oversp02;
static SKC_sprite_pattern oversp03;
static SKC_sprite_pattern* titlepat[21];
static SKC_sprite_pattern titlesp00;
static SKC_sprite_pattern titlesp01;
static SKC_sprite_pattern titlesp02;
static SKC_sprite_pattern titlesp03;
static SKC_sprite_pattern titlesp04;
static SKC_sprite_pattern titlesp05;
static SKC_sprite_pattern titlesp06;
static SKC_sprite_pattern titlesp07;
static SKC_sprite_pattern titlesp08;
static SKC_sprite_pattern titlesp09;
static SKC_sprite_pattern titlesp10;
static SKC_sprite_pattern titlesp11;
static SKC_sprite_pattern titlesp12;
static SKC_sprite_pattern titlesp13;
static SKC_sprite_pattern titlesp14;
static SKC_sprite_pattern titlesp15;
static SKC_sprite_pattern titlesp16;
static SKC_sprite_pattern titlesp17;
static SKC_sprite_pattern titlesp18;
static SKC_sprite_pattern titlesp20;
static SKC_sprite_pattern* clearpat[59];
static SKC_sprite_pattern clearsp00;
static SKC_sprite_pattern clearsp01;
static SKC_sprite_pattern clearsp02;
static SKC_sprite_pattern clearsp03;
static SKC_sprite_pattern clearsp04;
static SKC_sprite_pattern clearsp05;
static SKC_sprite_pattern clearsp06;
static SKC_sprite_pattern clearsp07;
static SKC_sprite_pattern clearsp08;
static SKC_sprite_pattern clearsp09;
static SKC_sprite_pattern clearsp10;
static SKC_sprite_pattern clearsp11;
static SKC_sprite_pattern clearsp12;
static SKC_sprite_pattern clearsp13;
static SKC_sprite_pattern clearsp14;
static SKC_sprite_pattern clearsp15;
static SKC_sprite_pattern clearsp16;
static SKC_sprite_pattern clearsp17;
static SKC_sprite_pattern clearsp18;
static SKC_sprite_pattern clearsp19;
static SKC_sprite_pattern clearsp20;
static SKC_sprite_pattern clearsp21;
static SKC_sprite_pattern clearsp22;
static SKC_sprite_pattern clearsp23;
static SKC_sprite_pattern clearsp24;
static SKC_sprite_pattern clearsp25;
static SKC_sprite_pattern clearsp26;
static SKC_sprite_pattern clearsp27;
static SKC_sprite_pattern clearsp28;
static SKC_sprite_pattern clearsp29;
static SKC_sprite_pattern clearsp30;
static SKC_sprite_pattern clearsp31;
static SKC_sprite_pattern clearsp32;
static SKC_sprite_pattern clearsp33;
static SKC_sprite_pattern clearsp34;
static SKC_sprite_pattern clearsp35;
static SKC_sprite_pattern clearsp36;
static SKC_sprite_pattern clearsp37;
static SKC_sprite_pattern clearsp38;
static SKC_sprite_pattern clearsp39;
static SKC_sprite_pattern clearsp40;
static SKC_sprite_pattern clearsp41;
static SKC_sprite_pattern clearsp42;
static SKC_sprite_pattern clearsp43;
static SKC_sprite_pattern clearsp44;
static SKC_sprite_pattern clearsp45;
static SKC_sprite_pattern clearsp46;
static SKC_sprite_pattern clearsp47;
static SKC_sprite_pattern clearsp48;
static SKC_sprite_pattern clearsp49;
static SKC_sprite_pattern clearsp50;
static SKC_sprite_pattern clearsp51;
static SKC_sprite_pattern clearsp52;
static SKC_sprite_pattern clearsp53;
static SKC_sprite_pattern clearsp54;
static SKC_sprite_pattern clearsp55;
static SKC_sprite_pattern clearsp56;
static SKC_sprite_pattern clearsp57;
static SKC_sprite_pattern clearsp58;

extern sonic3_ram g_ram;
extern unsigned char g_vram[0x10000];
extern bool g_sonic3_alone;


void over(SKC_sprite_status* p_actwk) {
  if (p_actwk->patno == 0) {
    save_game_lives_continues();
  }
  short xposi = !BIT_IS_SET(p_actwk->patno, 0) ? 80 : 496;
  fp16_set_integer(&p_actwk->xposi, xposi);
  fp16_set_integer(&p_actwk->yposi, 240);
  p_actwk->patbase = overpat;
  p_actwk->sproffset = 0x879C;
  p_actwk->sprpri = PRI_0;
  p_actwk->r_ptr = &over_move;
  over_move(p_actwk);
}


static void over_move(SKC_sprite_status* p_actwk) {
  if (fp16_get_integer(p_actwk->xposi) != 288) {
    short xoffset = (unsigned short)fp16_get_integer(p_actwk->xposi) < 288 ? 16 : -16;
    fp16_set_integer(&p_actwk->xposi, fp16_get_integer(p_actwk->xposi) + xoffset);
    actionsub(p_actwk);
  }
  else {
    p_actwk->u.obj.timer = 480;
    p_actwk->r_ptr = &over_wait;
  }
}


static void over_wait(SKC_sprite_status* p_actwk) {
  g_ram.colibuffer[0] = 0;
  if (!BIT_IS_SET(p_actwk->patno, 0)) {
    if (!are_any_face_buttons_used(g_ram.swdata1.pressed)
        && !are_any_face_buttons_used(g_ram.swdata2.pressed)
        && p_actwk->u.obj.timer != 0) {
      --p_actwk->u.obj.timer;
    }
    else if (g_ram.pltimeover_f == 0) {
      g_ram.gmmode = g_ram.plcontinuecnt != 0 ? 20 : 0;
    }
    else {
      memset(&g_ram.pltime_s, 0, sizeof(g_ram.pltime_s));
      g_ram.gameflag = 1;
    }
  }
  actionsub(p_actwk);
}


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
  unlze_moduled(&g_vram[0xA000], title_red_banner_cg);
  unsigned char* p_cg;
  if (!g_sonic3_alone) {
    p_cg = g_ram.cartridge != 0 ? title_sk_cg : title_s3k_cg;
    unlze_moduled(&g_vram[0xA200], p_cg);
  }
  if (g_ram.stageno == LAVA_REEF_BOSS || g_ram.stageno == DEATH_EGG_BOSS || get_act(g_ram.stageno_i) == ACT_1) {
    p_cg = act_digit_2_cg;
  }
  else {
    p_cg = act_digit_1_cg;
  }
  unlze_moduled(&g_vram[0xA7A0], p_cg);

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

  unlze_moduled(&g_vram[0xA9A0], p_cg);
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
      result = actwkchk_next(result);
      if (result.actwk_ptr == 0) break;
    }

    if (p_actwk->u.obj.actfree.title.act_start_flag != 0 && get_zone(g_ram.stageno) == LAUNCH_BASE) {
      divdevset(37);
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
          divdevset2(&toge_cg_tbl);
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


void clear(SKC_sprite_status* p_actwk) {
  SKC_sprite_status_handler act_tbl[5] = {
    &clear_init,
    &clear_move0,
    &clear_move1,
    &clear_move2
  };

  act_tbl[p_actwk->r_no / 2](p_actwk);
}


static void clear_init(SKC_sprite_status* p_actwk) {
  bgmset(225);
  unlze_moduled(&g_vram[0xA400], clear_cg);
  bool is_act_1 = g_ram.stageno != LAVA_REEF_BOSS && get_act(g_ram.stageno_i) == ACT_1;
  unsigned char* p_cg = is_act_1 ? act_digit_1_cg : act_digit_2_cg;
  p_actwk->u.obj.userflag = is_act_1 ? 0 : 0xFF;
  unlze_moduled(&g_vram[0xAD00], p_cg);

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

  unsigned char* p_vram = p_actwk->u.obj.userflag == 0 ? &g_vram[0xAF00] : &g_vram[0xB400];
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
  p_actwk->u.obj.actfree.clear.part_cnt = 12;
  p_actwk->r_no += 2;
}


static void clear_move0(SKC_sprite_status* p_actwk) {
  SKC_actwkchk_result result = actwkchk2(p_actwk);
  if (result.actwk_ptr != 0) {
    for (int i = 0; i < 12; ++i) {
      result.actwk_ptr->r_ptr = clear_init_tbl[i].r_ptr;
      result.actwk_ptr->u.obj.actfree.clear_part.xdestination = clear_init_tbl[i].xdestination;
      fp16_set_integer(&result.actwk_ptr->xposi, clear_init_tbl[i].xposi);
      p_actwk->r_no = fp16_get_integer(result.actwk_ptr->xposi) < 0 ? 0 : 0xFF;
      fp16_set_integer(&result.actwk_ptr->yposi, clear_init_tbl[i].yposi);
      result.actwk_ptr->patno = clear_init_tbl[i].patno;
      result.actwk_ptr->sprhs = clear_init_tbl[i].sprhs;
      result.actwk_ptr->colino = clear_init_tbl[i].exit_no;
      result.actwk_ptr->actflg.compound = 1;
      result.actwk_ptr->patbase = clearpat;
      result.actwk_ptr->u.obj.oya = p_actwk - g_ram.actwk;
      result = actwkchk_next(result);
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


static void clear_move1(SKC_sprite_status* p_actwk) {
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
      clear_move2(p_actwk);
    }
  }
}


static void clear_move2(SKC_sprite_status* p_actwk) {
  if (p_actwk->u.obj.timer != 0) {
    --p_actwk->u.obj.timer;
  }
  else if (p_actwk->u.obj.actfree.clear.part_cnt != 0) {
    ++p_actwk->u.obj.actfree.clear.current_exit_no;
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


static void clear_name(SKC_sprite_status* p_actwk) {
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
        p_actwk->u.obj.actfree.clear_part.xdestination += 8;
        p_actwk->sprhs -= 8;
      }
      break;
    case PLAY_TYPE_KNUCKLES:
      p_actwk->patno += 3;
      p_actwk->xposi -= 48;
      p_actwk->u.obj.actfree.clear_part.xdestination -= 48;
      p_actwk->sprhs += 48;
      break;
  }

  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  p_actwk->sproffset = p_parentwk->u.obj.userflag == 0 ? 0 : 40;
  p_actwk->r_ptr = &clear_text;
  clear_text(p_actwk);
}


static void clear_text(SKC_sprite_status* p_actwk) {
  bool fout = clear_part_move(p_actwk);
  if (!fout) {
    actionsub(p_actwk);
  }
}


static void clear_timebonus(SKC_sprite_status* p_actwk) {
  bool fout = clear_part_move(p_actwk);
  if (!fout) {
    clear_bonus(p_actwk, g_ram.timebonus);
  }
}


static void clear_ringbonus(SKC_sprite_status* p_actwk) {
  bool fout = clear_part_move(p_actwk);
  if (!fout) {
    clear_bonus(p_actwk, g_ram.ringbonus);
  }
}


static void clear_total(SKC_sprite_status* p_actwk) {
  bool fout = clear_part_move(p_actwk);
  if (!fout) {
    clear_bonus(p_actwk, g_ram.bonustotal);
  }
}


static void clear_bonus(SKC_sprite_status* p_actwk, unsigned short bonus) {
  clear_bonus_move(p_actwk, bonus);
  actionsub(p_actwk);
}


static void clear_bonus_move(SKC_sprite_status* p_actwk, unsigned short bonus) {
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


static bool clear_part_move(SKC_sprite_status* p_actwk) {
  SKC_sprite_status* p_parentwk = &g_ram.actwk[p_actwk->u.obj.oya];
  if (p_parentwk->u.obj.actfree.clear.current_exit_no != 0) {
    if (p_actwk->actflg.onscreen == 0) {
      --p_parentwk->u.obj.actfree.clear.part_cnt;
      frameout(p_actwk);
      return true;
    }
    if (p_parentwk->u.obj.actfree.clear.current_exit_no >= p_actwk->colino) {
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
    if (xposi != p_actwk->u.obj.actfree.clear_part.xdestination) {
      if (xposi >= p_actwk->u.obj.actfree.clear_part.xdestination) {
        xspeed = -xspeed;
      }
      xposi += xspeed;
    }
    fp16_set_integer(&p_actwk->xposi, xposi);
  }
  return false;
}


static unsigned long score_to_nibbles(SKC_sprite_status* p_actwk, unsigned short points) {
  unsigned long result = 0;
  unsigned long wk = points;

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


static SKC_overlay_element_init_data clear_init_tbl[12] = {
  { &clear_name,      224, -544, 184, 19,  72, 1 },
  { &clear_text,      304, -464, 184, 17,  48, 1 },
  { &clear_text,      232, 1128, 204, 16, 112, 3 },
  { &clear_text,      352, 1248, 188, 15,  56, 3 },
  { &clear_text,      192, 1216, 240, 14,  32, 5 },
  { &clear_text,      232, 1256, 240, 12,  48, 5 },
  { &clear_timebonus, 376, 1400, 240,  1,  64, 5 },
  { &clear_text,      192, 1280, 256, 13,  32, 7 },
  { &clear_text,      232, 1320, 256, 12,  48, 7 },
  { &clear_ringbonus, 376, 1464, 256,  1,  64, 7 },
  { &clear_text,      212, 1364, 284, 11,  48, 9 },
  { &clear_total,     376, 1528, 284,  1,  64, 9 }
};


static SKC_sprite_pattern* overpat[4] = {
  &oversp00,
  &oversp01,
  &oversp02,
  &oversp03
};


static SKC_sprite_pattern oversp00 = {
  2,
  {
    { -8, 13, 0x0000, -72 },
    { -8, 13, 0x0008, -40 }
  }
};
static SKC_sprite_pattern oversp01 = {
  2,
  {
    { -8, 13, 0x0014, 8 },
    { -8, 13, 0x000C, 40 }
  }
};
static SKC_sprite_pattern oversp02 = {
  2,
  {
    { -8,  9, 0x001C, -60 },
    { -8, 13, 0x0008, -36 }
  }
};
static SKC_sprite_pattern oversp03 = {
  2,
  {
    { -8, 13, 0x0014, 12 },
    { -8, 13, 0x000C, 44 }
  }
};


static SKC_sprite_pattern* titlepat[21] = {
  &titlesp00,
  &titlesp01,
  &titlesp02,
  &titlesp03,
  &titlesp04,
  &titlesp05,
  &titlesp06,
  &titlesp07,
  &titlesp08,
  &titlesp09,
  &titlesp10,
  &titlesp11,
  &titlesp12,
  &titlesp13,
  &titlesp14,
  &titlesp15,
  &titlesp16,
  &titlesp17,
  &titlesp18,
  &titlesp18,
  &titlesp20
};


static SKC_sprite_pattern titlesp00 = {
  0,
  {}
};
static SKC_sprite_pattern titlesp01 = {
  16,
  {
    {   88,  9, 0x8510, -24 },
    {   88,  9, 0x8516,   0 },
    { -112, 15, 0x8500, -32 },
    { -112, 15, 0x8500,   0 },
    {  -80, 15, 0x8500, -32 },
    {  -80, 15, 0x8500,   0 },
    {  -48, 15, 0x8500, -32 },
    {  -48, 15, 0x8500,   0 },
    {  -16, 15, 0x8500, -32 },
    {  -16, 15, 0x8500,   0 },
    {   16, 15, 0x8500, -32 },
    {   16, 15, 0x8500,   0 },
    {   48, 15, 0x8500, -32 },
    {   48, 15, 0x8500,   0 },
    {   80, 15, 0x8500, -32 },
    {   80, 15, 0x8500,   0 }
  }
};
static SKC_sprite_pattern titlesp02 = {
  2,
  {
    { 16,  9, 0x8537, -28 },
    {  0, 15, 0x853D, -11 }
  }
};
static SKC_sprite_pattern titlesp03 = {
  4,
  {
    { 0,  6, 0x8531, -36 },
    { 0, 10, 0x8528, -20 },
    { 0,  6, 0x8522,   4 },
    { 0,  6, 0x851C,  20 }
  }
};
static SKC_sprite_pattern titlesp04 = {
  11,
  {
    { 0, 6, 0x854D, -32 },
    { 0, 6, 0x8522, -16 },
    { 0, 6, 0x8559,   0 },
    { 0, 6, 0x851C,  16 },
    { 0, 2, 0x8562,  32 },
    { 0, 2, 0x855F,  48 },
    { 0, 6, 0x8565,  56 },
    { 0, 2, 0x8562,  72 },
    { 0, 6, 0x854D,  80 },
    { 0, 6, 0x8522,  96 },
    { 0, 6, 0x8553, 112 }
  }
};
static SKC_sprite_pattern titlesp05 = {
  8,
  {
    { 0,  6, 0x8559, -16 },
    { 0,  6, 0x856E,   0 },
    { 0,  6, 0x8553,  16 },
    { 0,  6, 0x8562,  32 },
    { 0, 10, 0x8528,  48 },
    { 0,  6, 0x854D,  72 },
    { 0,  2, 0x855F,  88 },
    { 0, 14, 0x8568,  96 }
  }
};
static SKC_sprite_pattern titlesp06 = {
  12,
  {
    { 0, 10, 0x8568, -72 },
    { 0,  6, 0x854D, -48 },
    { 0,  6, 0x8571, -32 },
    { 0,  6, 0x8553, -16 },
    { 0,  2, 0x8565,   0 },
    { 0,  6, 0x851C,   8 },
    { 0,  6, 0x855F,  32 },
    { 0,  6, 0x854D,  48 },
    { 0,  6, 0x8571,  64 },
    { 0,  6, 0x8559,  80 },
    { 0,  6, 0x851C,  96 },
    { 0,  6, 0x8522, 112 }
  }
};
static SKC_sprite_pattern titlesp07 = {
  12,
  {
    { 0,  6, 0x8553, -64 },
    { 0,  6, 0x854D, -48 },
    { 0,  6, 0x856B, -32 },
    { 0,  6, 0x8522, -16 },
    { 0,  2, 0x8565,   0 },
    { 0,  6, 0x8577,   8 },
    { 0,  6, 0x854D,  24 },
    { 0,  2, 0x8568,  40 },
    { 0,  6, 0x8522,  56 },
    { 0,  2, 0x8565,  72 },
    { 0, 14, 0x8559,  80 },
    { 0,  6, 0x8571, 112 }
  }
};
static SKC_sprite_pattern titlesp08 = {
  13,
  {
    { 0, 6, 0x8559, -72 },
    { 0, 2, 0x8568, -56 },
    { 0, 6, 0x8577, -48 },
    { 0, 2, 0x8565, -32 },
    { 0, 6, 0x8522, -24 },
    { 0, 6, 0x855F,  -8 },
    { 0, 6, 0x8553,  16 },
    { 0, 6, 0x854D,  32 },
    { 0, 6, 0x8571,  48 },
    { 0, 6, 0x8571,  64 },
    { 0, 6, 0x851C,  80 },
    { 0, 6, 0x856B,  96 },
    { 0, 6, 0x8577, 112 }
  }
};
static SKC_sprite_pattern titlesp09 = {
  6,
  {
    { 0, 2, 0x8559,  40 },
    { 0, 6, 0x8553,  48 },
    { 0, 6, 0x851C,  64 },
    { 0, 6, 0x8553,  80 },
    { 0, 6, 0x854D,  96 },
    { 0, 6, 0x855C, 112 }
  }
};
static SKC_sprite_pattern titlesp10 = {
  9,
  {
    { 0,  2, 0x8565, -32 },
    { 0,  6, 0x854D, -24 },
    { 0,  6, 0x856E,  -8 },
    { 0,  6, 0x8522,   8 },
    { 0, 14, 0x8559,  24 },
    { 0,  6, 0x8553,  64 },
    { 0,  6, 0x854D,  80 },
    { 0,  6, 0x8568,  96 },
    { 0,  6, 0x851C, 112 }
  }
};
static SKC_sprite_pattern titlesp11 = {
  10,
  {
    { 0, 10, 0x8559, -80 },
    { 0,  6, 0x856E, -56 },
    { 0,  6, 0x8568, -40 },
    { 0,  6, 0x854D, -24 },
    { 0,  6, 0x8562,  -8 },
    { 0, 10, 0x8528,   8 },
    { 0, 10, 0x8528,  32 },
    { 0, 10, 0x8559,  56 },
    { 0, 14, 0x854D,  88 },
    { 0,  2, 0x8556, 120 }
  }
};
static SKC_sprite_pattern titlesp12 = {
  10,
  {
    { 0,  6, 0x8565, -32 },
    { 0,  6, 0x854D, -16 },
    { 0,  6, 0x8522,   0 },
    { 0,  6, 0x8553,  16 },
    { 0, 10, 0x8528,  32 },
    { 0,  6, 0x855F,  56 },
    { 0, 10, 0x8528,  72 },
    { 0,  2, 0x855C,  96 },
    { 0,  2, 0x8559, 104 },
    { 0,  6, 0x8565, 112 }
  }
};
static SKC_sprite_pattern titlesp13 = {
  8,
  {
    { 0, 2, 0x8559,   0 },
    { 0, 6, 0x854D,   8 },
    { 0, 6, 0x8562,  24 },
    { 0, 6, 0x854D,  40 },
    { 0, 6, 0x855C,  64 },
    { 0, 6, 0x851C,  80 },
    { 0, 6, 0x851C,  96 },
    { 0, 6, 0x8553, 112 }
  }
};
static SKC_sprite_pattern titlesp14 = {
  11,
  {
    { 0,  6, 0x8565, -72 },
    { 0,  6, 0x8559, -56 },
    { 0,  6, 0x8577, -40 },
    { 0,  6, 0x8565, -16 },
    { 0,  6, 0x854D,   0 },
    { 0,  6, 0x8522,  16 },
    { 0,  6, 0x8553,  32 },
    { 0, 14, 0x856B,  48 },
    { 0,  6, 0x854D,  80 },
    { 0,  6, 0x855F,  96 },
    { 0,  6, 0x8577, 112 }
  }
};
static SKC_sprite_pattern titlesp15 = {
  8,
  {
    { 0, 6, 0x8553, -8 },
    { 0, 6, 0x851C,   8 },
    { 0, 6, 0x854D,  24 },
    { 0, 6, 0x8565,  40 },
    { 0, 6, 0x855F,  56 },
    { 0, 6, 0x851C,  80 },
    { 0, 6, 0x8559,  96 },
    { 0, 6, 0x8559, 112 }
  }
};
static SKC_sprite_pattern titlesp16 = {
  11,
  {
    { 0,  6, 0x856E, -80 },
    { 0,  6, 0x8559, -64 },
    { 0,  6, 0x851C, -48 },
    { 0,  6, 0x8553, -24 },
    { 0, 10, 0x8528,  -8 },
    { 0, 10, 0x8528,  16 },
    { 0, 10, 0x855F,  40 },
    { 0,  6, 0x8568,  64 },
    { 0,  6, 0x8553,  80 },
    { 0,  6, 0x854D,  96 },
    { 0,  6, 0x8574, 112 }
  }
};
static SKC_sprite_pattern titlesp17 = {
  11,
  {
    { 0, 10, 0x855F, -56 },
    { 0, 6, 0x8559, -32 },
    { 0, 6, 0x8559, -16 },
    { 0, 6, 0x851C, 0 },
    { 0, 6, 0x8522, 16 },
    { 0, 6, 0x856B, 40 },
    { 0, 6, 0x854D, 56 },
    { 0, 2, 0x8568, 72 },
    { 0, 6, 0x854D, 80 },
    { 0, 6, 0x8553, 96 },
    { 0, 6, 0x851C, 112 }
  }
};
static SKC_sprite_pattern titlesp18 = {
  5,
  {
    { 0, 6, 0x8553, 0 },
    { 0, 10, 0x8528, 16 },
    { 0, 6, 0x855F, 40 },
    { 0, 6, 0x8571, 56 },
    { 0, 6, 0x8565, 72 }
  }
};
static SKC_sprite_pattern titlesp20 = {
  5,
  {
    { 0, 6, 0x8565,  0 },
    { 0, 6, 0x856B, 16 },
    { 0, 6, 0x854D, 32 },
    { 0, 6, 0x8559, 48 },
    { 0, 6, 0x851C, 64 }
  }
};


static SKC_sprite_pattern* clearpat[59] = {
  &clearsp00,
  &clearsp01,
  &clearsp02,
  &clearsp03,
  &clearsp04,
  &clearsp05,
  &clearsp06,
  &clearsp07,
  &clearsp08,
  &clearsp09,
  &clearsp10,
  &clearsp11,
  &clearsp12,
  &clearsp13,
  &clearsp14,
  &clearsp15,
  &clearsp16,
  &clearsp17,
  &clearsp18,
  &clearsp19,
  &clearsp20,
  &clearsp21,
  &clearsp22,
  &clearsp23,
  &clearsp24,
  &clearsp25,
  &clearsp26,
  &clearsp27,
  &clearsp28,
  &clearsp29,
  &clearsp30,
  &clearsp31,
  &clearsp32,
  &clearsp33,
  &clearsp34,
  &clearsp35,
  &clearsp36,
  &clearsp37,
  &clearsp38,
  &clearsp39,
  &clearsp41,
  &clearsp42,
  &clearsp43,
  &clearsp44,
  &clearsp52,
  &clearsp53,
  &clearsp45,
  &clearsp46,
  &clearsp47,
  &clearsp48,
  &clearsp49,
  &clearsp50,
  &clearsp51,
  &clearsp54,
  &clearsp55,
  &clearsp56,
  &clearsp57,
  &clearsp58,
  &clearsp40
};
static SKC_sprite_pattern clearsp00 = {
   0,
   {}
};
static SKC_sprite_pattern clearsp01 = {
  1,
  {
    { 0, 1, 0xA520, 0 }
  }
};
static SKC_sprite_pattern clearsp02 = {
  1,
  {
    { 0, 1, 0xA522, 0 }
  }
};
static SKC_sprite_pattern clearsp03 = {
  1,
  {
    { 0, 1, 0xA524, 0 }
  }
};
static SKC_sprite_pattern clearsp04 = {
  1,
  {
    { 0, 1, 0xA526, 0 }
  }
};
static SKC_sprite_pattern clearsp05 = {
  1,
  {
    { 0, 1, 0xA528, 0 }
  }
};
static SKC_sprite_pattern clearsp06 = {
  1,
  {
    { 0, 1, 0xA52A, 0 }
  }
};
static SKC_sprite_pattern clearsp07 = {
  1,
  {
    { 0, 1, 0xA52C, 0 }
  }
};
static SKC_sprite_pattern clearsp08 = {
  1,
  {
    { 0, 1, 0xA52E, 0 }
  }
};
static SKC_sprite_pattern clearsp09 = {
  1,
  {
    { 0, 1, 0xA530, 0 }
  }
};
static SKC_sprite_pattern clearsp10 = {
  1,
  {
    { 0, 1, 0xA532, 0 }
  }
};
static SKC_sprite_pattern clearsp11 = {
  3,
  {
    {   0,  1, 0xA544,  0 },
    {   0, 13, 0xA542,  8 },
    { -10,  6, 0x8534, 36 }
  }
};
static SKC_sprite_pattern clearsp12 = {
  3,
  {
    {   0, 13, 0xA53A,  0 },
    {   0,  1, 0xA6CA, 32 },
    { -10,  6, 0x8534, 36 }
  }
};
static SKC_sprite_pattern clearsp13 = {
  1,
  {
    { 0, 13, 0xA6D2, 0 }
  }
};
static SKC_sprite_pattern clearsp14 = {
  1,
  {
    { 0, 13, 0xA6DA, 0 }
  }
};
static SKC_sprite_pattern clearsp15 = {
  2,
  {
    { 16,  9, 0x854A,  0 },
    {  0, 15, 0x8568, 17 }
  }
};
static SKC_sprite_pattern clearsp16 = {
  6,
  {
    { 0,  5, 0x8560,  0 },
    { 0,  5, 0x8554, 16 },
    { 0,  5, 0x855C, 32 },
    { 0,  5, 0x8558, 48 },
    { 0,  5, 0x8564, 64 },
    { 0, 13, 0x8550, 80 }
  }
};
static SKC_sprite_pattern clearsp17 = {
  3,
  {
    { 0, 5, 0x8550,  0 },
    { 0, 5, 0x8558, 16 },
    { 0, 5, 0x8560, 30 }
  }
};
static SKC_sprite_pattern clearsp18 = {
  3,
  {
    { 0, 13, 0x850F,  0 },
    { 0, 13, 0x8517, 32 },
    { 0,  5, 0x851F, 64 }
  }
};
static SKC_sprite_pattern clearsp19 = {
  3,
  {
    { 0, 13, 0x8578,  1 },
    { 0, 13, 0x8580, 33 },
    { 0,  1, 0x8588, 65 }
  }
};
static SKC_sprite_pattern clearsp20 = {
  3,
  {
    { 0, 13, 0x8578,  6 },
    { 0, 13, 0x8580, 38 },
    { 0,  1, 0x8588, 70 }
  }
};
static SKC_sprite_pattern clearsp21 = {
  2,
  {
    { 0, 13, 0x8578,  1 },
    { 0, 13, 0x8580, 33 }
  }
};
static SKC_sprite_pattern clearsp22 = {
  4,
  {
    { 0, 13, 0x8578,   4 },
    { 0, 13, 0x8580,  36 },
    { 0, 13, 0x8588,  68 },
    { 0,  9, 0x8590, 100 }
  }
};
static SKC_sprite_pattern clearsp23 = {
  5,
  {
    {   0, 13, 0xE6CA, -96 },
    {   0,  1, 0xE6E2, -64 },
    {   0,  9, 0xA6E4,  40 },
    {   0, 13, 0xA6EA,  64 },
    { -10,  6, 0x85CC, -60 }
  }
};
static SKC_sprite_pattern clearsp24 = {
  4,
  {
    {   0, 13, 0xE6D2,  0 },
    {   0, 13, 0xE5D2, 40 },
    {   0,  1, 0xE6CA, 72 },
    { -10,  6, 0x85CC, 76 }
  }
};
static SKC_sprite_pattern clearsp25 = {
  3,
  {
    {   0, 13, 0xE57F,  0 },
    {   0,  9, 0xE587, 32 },
    { -10,  6, 0x85CC, 52 }
  }
};
static SKC_sprite_pattern clearsp26 = {
  3,
  {
    {   0, 13, 0xE58D,  0 },
    {   0, 13, 0xE595, 32 },
    { -10,  6, 0x85CC, 60 }
  }
};
static SKC_sprite_pattern clearsp27 = {
  1,
  {
    { -8, 5, 0xC56F, -8 }
  }
};
static SKC_sprite_pattern clearsp28 = {
  1,
  {
    { -8, 5, 0xC56B, -8 }
  }
};
static SKC_sprite_pattern clearsp29 = {
  1,
  {
    { -8, 5, 0xC573, -8 }
  }
};
static SKC_sprite_pattern clearsp30 = {
  1,
  {
    { -8, 5, 0xA56B, -8 }
  }
};
static SKC_sprite_pattern clearsp31 = {
  1,
  {
    { -8, 5, 0x857B, -8 }
  }
};
static SKC_sprite_pattern clearsp32 = {
  1,
  {
    { -8, 5, 0x8577, -8 }
  }
};
static SKC_sprite_pattern clearsp33 = {
  1,
  {
    { -8, 5, 0xA56F, -8 }
  }
};
static SKC_sprite_pattern clearsp34 = {
  12,
  {
    { 0, 5, 0x8559, -96 },
    { 0, 5, 0x8551, -80 },
    { 0, 5, 0x8533, -64 },
    { 0, 5, 0x852B, -48 },
    { 0, 1, 0x853F, -32 },
    { 0, 5, 0x8523, -24 },
    { 0, 5, 0x8541,  -8 },
    { 0, 5, 0x8559,  16 },
    { 0, 5, 0x855D,  32 },
    { 0, 5, 0x8523,  48 },
    { 0, 5, 0x8537,  64 },
    { 0, 5, 0x8533,  80 }
  }
};
static SKC_sprite_pattern clearsp35 = {
  4,
  {
    { 0, 5, 0x8537,  0 },
    { 0, 5, 0x854D, 17 },
    { 0, 5, 0x855D, 32 },
    { 0, 5, 0x8523, 56 }
  }
};
static SKC_sprite_pattern clearsp36 = {
  12,
  {
    { 0, 5, 0x852B, -100 },
    { 0, 5, 0x853B,  -84 },
    { 0, 5, 0x8523,  -68 },
    { 0, 5, 0x854D,  -52 },
    { 0, 5, 0x8559,  -36 },
    { 0, 5, 0x8533,  -12 },
    { 0, 5, 0x8545,    4 },
    { 0, 5, 0x8533,   20 },
    { 0, 5, 0x8555,   36 },
    { 0, 5, 0x8523,   52 },
    { 0, 5, 0x8541,   68 },
    { 0, 5, 0x852F,   84 }
  }
};
static SKC_sprite_pattern clearsp37 = {
  2,
  {
    { 0, 5, 0x8541, 72 },
    { 0, 5, 0x8541, 86 }
  }
};
static SKC_sprite_pattern clearsp38 = {
  1,
  {
    { 0, 5, 0x8559, 100 }
  }
};
static SKC_sprite_pattern clearsp39 = {
  3,
  {
    { 0, 5, 0xE549,  0 },
    { 0, 5, 0xE54D, 17 },
    { 0, 9, 0xE565, 32 }
  }
};
static SKC_sprite_pattern clearsp40 = {
  3,
  {
    { 0, 5, 0xE52B,  0 },
    { 0, 5, 0xE523, 16 },
    { 0, 5, 0xE549, 32 }
  }
};
static SKC_sprite_pattern clearsp41 = {
  2,
  {
    { 0, 5, 0xE527,  0 },
    { 0, 5, 0xE533, 15 }
  }
};
static SKC_sprite_pattern clearsp42 = {
  1,
  {
    { -24, 10, 0x859D, -12 }
  }
};
static SKC_sprite_pattern clearsp43 = {
  1,
  {
    { -24, 10, 0x85A6, -12 }
  }
};
static SKC_sprite_pattern clearsp44 = {
  1,
  {
    { -24, 10, 0x85AF, -12 }
  }
};
static SKC_sprite_pattern clearsp45 = {
  7,
  {
    { 0, 5, 0xE52B, -64 },
    { 0, 5, 0xE523, -48 },
    { 0, 5, 0xE549, -32 },
    { 0, 5, 0xE537,  -8 },
    { 0, 5, 0xE54D,   9 },
    { 0, 5, 0xE55D,  32 },
    { 0, 5, 0xE54D,  48 }
  }
};
static SKC_sprite_pattern clearsp46 = {
  12,
  {
    { 0, 5, 0xE53B, -96 },
    { 0, 1, 0xE53F, -80 },
    { 0, 5, 0xE52F, -71 },
    { 0, 5, 0xE52F, -54 },
    { 0, 5, 0xE533, -38 },
    { 0, 5, 0xE549, -23 },
    { 0, 5, 0xE551,   1 },
    { 0, 5, 0xE523,  16 },
    { 0, 5, 0xE541,  32 },
    { 0, 5, 0xE523,  48 },
    { 0, 5, 0xE52B,  64 },
    { 0, 5, 0xE533,  80 }
  }
};
static SKC_sprite_pattern clearsp47 = {
  12,
  {
    { 0, 5, 0x8559, -100 },
    { 0, 5, 0x8561,  -84 },
    { 0, 5, 0x8551,  -68 },
    { 0, 5, 0x8533,  -52 },
    { 0, 5, 0x8555,  -36 },
    { 0, 5, 0x8533,  -12 },
    { 0, 5, 0x8545,    4 },
    { 0, 5, 0x8533,   20 },
    { 0, 5, 0x8555,   36 },
    { 0, 5, 0x8523,   52 },
    { 0, 5, 0x8541,   68 },
    { 0, 5, 0x852F,   84 }
  }
};
static SKC_sprite_pattern clearsp48 = {
  5,
  {
    {   0, 13, 0xA6CA, -96 },
    {   0,  1, 0xA6E2, -64 },
    {   0,  9, 0xA6E4,  40 },
    {   0, 13, 0xA6EA,  64 },
    { -10,  6, 0x85CC, -60 }
  }
};
static SKC_sprite_pattern clearsp49 = {
  4,
  {
    {   0, 13, 0xA6D2,  0 },
    {   0, 13, 0xA5D2, 40 },
    {   0,  1, 0x26CA, 72 },
    { -10,  6, 0x85CC, 76 }
  }
};
static SKC_sprite_pattern clearsp50 = {
  3,
  {
    {   0, 13, 0xA57F,  0 },
    {   0,  9, 0xA587, 32 },
    { -10,  6, 0x85CC, 52 }
  }
};
static SKC_sprite_pattern clearsp51 = {
  3,
  {
    {   0, 13, 0xA58D,  0 },
    {   0, 13, 0xA595, 32 },
    { -10,  6, 0x85CC, 60 }
  }
};
static SKC_sprite_pattern clearsp52 = {
  3,
  {
    { 0, 5, 0x8549,  0 },
    { 0, 5, 0x854D, 17 },
    { 0, 9, 0x8565, 32 }
  }
};
static SKC_sprite_pattern clearsp53 = {
  3,
  {
    { 0, 5, 0x852B,  0 },
    { 0, 5, 0x8523, 16 },
    { 0, 5, 0x8549, 32 }
  }
};
static SKC_sprite_pattern clearsp54 = {
  2,
  {
    { 0, 5, 0x8527,  0 },
    { 0, 5, 0x8533, 15 }
  }
};
static SKC_sprite_pattern clearsp55 = {
  5,
  {
    {   0, 13, 0x86CA, -96 },
    {   0,  1, 0x86E2, -64 },
    {   0,  9, 0x86E4,  40 },
    {   0, 13, 0x86EA,  64 },
    { -10,  6, 0x85CC, -60 }
  }
};
static SKC_sprite_pattern clearsp56 = {
  4,
  {
    {   0, 13, 0x86D2,  0 },
    {   0, 13, 0x85D2, 40 },
    {   0,  1, 0x06CA, 72 },
    { -10,  6, 0x85CC, 76 }
  }
};
static SKC_sprite_pattern clearsp57 = {
  3,
  {
    {   0, 13, 0x857F,  0 },
    {   0,  9, 0x8587, 32 },
    { -10,  6, 0x85CC, 52 }
  }
};
static SKC_sprite_pattern clearsp58 = {
  3,
  {
    {   0, 13, 0x858D,  0 },
    {   0, 13, 0x8595, 32 },
    { -10,  6, 0x85CC, 60 }
  }
};
