#include "savedata.h"
#include <stdbool.h>
#include <string.h>
#include "types/sonic3ram.h"
#include "utils/stageno.h"
#include "constants.h"
static SKC_vs_savedata default_vs_savedata;
static SKC_s3k_savedata default_s3k_savedata;
static void read_s3k_savedata(void);
static void save_s3k_game(void);
static void save_s3k_game2(void);
static void read_s3_savedata(void);
static SKC_s3_savedata default_s3_savedata;
static void save_s3_game(void);
static void save_s3_game2(void);

extern sonic3_ram g_ram;
extern int g_sonic3_alone;


void read_savedata(void) {
  if (!g_sonic3_alone) {
    read_s3k_savedata();
  }
  else {
    read_s3_savedata();
  }
}


static void read_vs_savedata(void) {
  unsigned char buffer[84];
  if (sys_read_savedata(0, 0x60, buffer, 0, 41, 0x4C44) == 0) {
    unsigned char* p_buffer = buffer;

    for (int i = 0; i < VS_SAVEDATA_SLOTS; ++i) {
      g_ram.vs_savedata_slots[i].first.reserved = p_buffer[3];
      g_ram.vs_savedata_slots[i].first.minutes = p_buffer[2];
      g_ram.vs_savedata_slots[i].first.seconds = p_buffer[1];
      g_ram.vs_savedata_slots[i].first.frames = p_buffer[0];
      p_buffer += 4;
      g_ram.vs_savedata_slots[i].second.reserved = p_buffer[3];
      g_ram.vs_savedata_slots[i].second.minutes = p_buffer[2];
      g_ram.vs_savedata_slots[i].second.seconds = p_buffer[1];
      g_ram.vs_savedata_slots[i].second.frames = p_buffer[0];
      p_buffer += 4;
      g_ram.vs_savedata_slots[i].third.reserved = p_buffer[3];
      g_ram.vs_savedata_slots[i].third.minutes = p_buffer[2];
      g_ram.vs_savedata_slots[i].third.seconds = p_buffer[1];
      g_ram.vs_savedata_slots[i].third.frames = p_buffer[0];
      p_buffer += 4;
      g_ram.vs_savedata_slots[i].characters[0] = p_buffer[0];
      g_ram.vs_savedata_slots[i].characters[1] = p_buffer[1];
      g_ram.vs_savedata_slots[i].characters[2] = p_buffer[2];
      g_ram.vs_savedata_slots[i].characters[3] = p_buffer[3];
      p_buffer += 4;
    }
  }
  else {
    for (int i = 0; i < VS_SAVEDATA_SLOTS; ++i) {
      g_ram.vs_savedata_slots[i] = default_vs_savedata;
    }

    write_vs_savedata();
  }
}

static void read_s3k_savedata(void) {
  if (g_ram.cartridge != 0) return;

  read_vs_savedata();
  unsigned char buffer[84];
  bool active_found = false;
  if (sys_read_savedata(0x180, 0x1E0, buffer, 41, 0x4244) == 0) {
    unsigned char* p_buffer = buffer;

    for (int i = 0; i < S3K_SAVEDATA_SLOTS; ++i) {
      g_ram.savedata_slots[i].s3k.new = *p_buffer >> 2;
      g_ram.savedata_slots[i].s3k.clear_type = *p_buffer;
      ++p_buffer;
      g_ram.savedata_slots[i].s3k.unused = ++*p_buffer;
      g_ram.savedata_slots[i].s3k.play_type = *p_buffer >> 4;
      g_ram.savedata_slots[i].s3k.specstageno = *p_buffer;
      ++p_buffer;
      g_ram.savedata_slots[i].s3k.zone = *p_buffer++;
      g_ram.savedata_slots[i].s3k.brings = p_buffer[0] | p_buffer[1] << 8;
      p_buffer += 2;
      g_ram.savedata_slots[i].s3k.specprogress0 = p_buffer[1] >> 6;
      g_ram.savedata_slots[i].s3k.specprogress1 = p_buffer[1] >> 4;
      g_ram.savedata_slots[i].s3k.specprogress2 = p_buffer[1] >> 2;
      g_ram.savedata_slots[i].s3k.specprogress3 = p_buffer[1];
      g_ram.savedata_slots[i].s3k.specprogress4 = p_buffer[0] >> 6;
      g_ram.savedata_slots[i].s3k.specprogress5 = p_buffer[0] >> 4;
      g_ram.savedata_slots[i].s3k.specprogress6 = p_buffer[0] >> 2;
      g_ram.savedata_slots[i].s3k.specprogress7 = p_buffer[0];
      p_buffer += 2;
      g_ram.savedata_slots[i].s3k.pl_suu = *p_buffer++;
      g_ram.savedata_slots[i].s3k.plcontinuecnt = *p_buffer++;
      if (g_ram.savedata_slots[i].s3k.new == 0) {
        active_found = true;
      }
    }
  }
  if (!active_found) {
    for (int i = 0; i < S3K_SAVEDATA_SLOTS; ++i) {
      g_ram.savedata_slots[i].s3k = default_s3k_savedata;
    }

    write_savedata();
  }

  g_ram.nosave_play_type = PLAY_TYPE_SONIC_AND_MILES;
  g_ram.dataselect_selection = 1;
}


static SKC_vs_savedata default_vs_savedata = {
  .first = { 0x80, 0, 0, 0 },
  .second = { 0x80, 0, 0, 0 },
  .third = { 0x80, 0, 0, 0 },
  .characters = { SONIC, MILES, KNUCKLES, 0 }
};


static SKC_s3k_savedata default_s3k_savedata = {
  .new = 0x20,
  .clear_type = 0,
  .unused = 0,
  .play_type = PLAY_TYPE_SONIC_AND_MILES,
  .specstageno = 0,
  .zone = ANGEL_ISLAND,
  .brings = 0,
  .specprogress0 = 0,
  .specprogress1 = 0,
  .specprogress2 = 0,
  .specprogress3 = 0,
  .specprogress4 = 0,
  .specprogress5 = 0,
  .specprogress6 = 0,
  .specprogress7 = 0,
  .pl_suu = 3,
  .plcontinuecnt = 0
};


void write_vs_savedata(void) {
  unsigned char buffer[84];
  unsigned char* p_buffer = buffer;

  for (int i = 0; i < VS_SAVEDATA_SLOTS; ++i) {
    *p_buffer++ = g_ram.vs_savedata_slots[i].first.frames;
    *p_buffer++ = g_ram.vs_savedata_slots[i].first.seconds;
    *p_buffer++ = g_ram.vs_savedata_slots[i].first.minutes;
    *p_buffer++ = g_ram.vs_savedata_slots[i].first.reserved;
    *p_buffer++ = g_ram.vs_savedata_slots[i].second.frames;
    *p_buffer++ = g_ram.vs_savedata_slots[i].second.seconds;
    *p_buffer++ = g_ram.vs_savedata_slots[i].second.minutes;
    *p_buffer++ = g_ram.vs_savedata_slots[i].second.reserved;
    *p_buffer++ = g_ram.vs_savedata_slots[i].third.frames;
    *p_buffer++ = g_ram.vs_savedata_slots[i].third.seconds;
    *p_buffer++ = g_ram.vs_savedata_slots[i].third.minutes;
    *p_buffer++ = g_ram.vs_savedata_slots[i].third.reserved;
  }

  *p_buffer++ = 0x44;
  *p_buffer++ = 0x4C;
  sys_write_savedata(0, 0x60, buffer, 41);
}


void write_savedata(void) {
  unsigned char buffer[84];
  unsigned char* p_buffer = buffer;

  if (!g_sonic3_alone) {
    for (int i = 0; i < S3K_SAVEDATA_SLOTS; ++i) {
      *p_buffer++ = g_ram.savedata_slots[i].s3k.new << 2 | g_ram.savedata_slots[i].s3k.clear_type;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.unused;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.play_type << 4 | g_ram.savedata_slots[i].s3k.specstageno;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.zone;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.brings & 0x00FF;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.brings >> 8;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.specprogress7
                  | g_ram.savedata_slots[i].s3k.specprogress6 << 2
                  | g_ram.savedata_slots[i].s3k.specprogress5 << 4
                  | g_ram.savedata_slots[i].s3k.specprogress4 << 6;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.specprogress3
                  | g_ram.savedata_slots[i].s3k.specprogress2 << 2
                  | g_ram.savedata_slots[i].s3k.specprogress1 << 4
                  | g_ram.savedata_slots[i].s3k.specprogress0 << 6;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.pl_suu;
      *p_buffer++ = g_ram.savedata_slots[i].s3k.plcontinuecnt;
    }

    *p_buffer++ = 0x44;
    *p_buffer++ = 0x42;
    sys_write_savedata(0x180, 0x1E0, buffer, 41);
  }
  else {
    for (int i = 0; i < S3_SAVEDATA_SLOTS; ++i) {
      *p_buffer++ = g_ram.savedata_slots[i].s3.new;
      *p_buffer++ = g_ram.savedata_slots[i].s3.brings1;
      *p_buffer++ = g_ram.savedata_slots[i].s3.play_type;
      *p_buffer++ = g_ram.savedata_slots[i].s3.zone;
      *p_buffer++ = g_ram.savedata_slots[i].s3.specstageno;
      *p_buffer++ = g_ram.savedata_slots[i].s3.emeraldcnt;
      *p_buffer++ = g_ram.savedata_slots[i].s3.specprogress7
                  | g_ram.savedata_slots[i].s3.specprogress6 << 1
                  | g_ram.savedata_slots[i].s3.specprogress5 << 2
                  | g_ram.savedata_slots[i].s3.specprogress4 << 3
                  | g_ram.savedata_slots[i].s3.specprogress3 << 4
                  | g_ram.savedata_slots[i].s3.specprogress2 << 5
                  | g_ram.savedata_slots[i].s3.specprogress1 << 6
                  | g_ram.savedata_slots[i].s3.specprogress0 << 7;
      *p_buffer++ = g_ram.savedata_slots[i].s3.brings0;
    }

    *p_buffer++ = 0x44;
    *p_buffer++ = 0x42;
    sys_write_savedata(0xC0, 0x120, buffer, 41);
  }
}


void save_game(void) {
  if (!g_sonic3_alone) {
    save_s3k_game();
  }
  else {
    save_s3_game();
  }
}


static void save_s3k_game(void) {
  unsigned char next_zone_tbl[24][2] = {
    { HYDROCITY, HYDROCITY },
    { MARBLE_GARDEN, MARBLE_GARDEN },
    { CARNIVAL_NIGHT, CARNIVAL_NIGHT },
    { FLYING_BATTERY, FLYING_BATTERY },
    { SANDOPOLIS, SANDOPOLIS },
    { ICECAP, ICECAP },
    { LAUNCH_BASE, LAUNCH_BASE },
    { MUSHROOM_HILL, MUSHROOM_HILL },
    { LAVA_REEF, LAVA_REEF },
    { SKY_SANCTUARY, SKY_SANCTUARY },
    { DOOMSDAY, DOOMSDAY },
    { ANGEL_ISLAND_ACT_1_AND_ENDING, ANGEL_ISLAND_ACT_1_AND_ENDING },
    { AZURE_LAKE, AZURE_LAKE },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { ANGEL_ISLAND, ANGEL_ISLAND },
    { SKY_SANCTUARY, DEATH_EGG },
    { ANGEL_ISLAND_ACT_1_AND_ENDING, ANGEL_ISLAND }
  };

  if (g_ram.cartridge == 0 && g_ram.curr_savedata_ptr != 0) {
    unsigned char next_zone = next_zone_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)];
    if ((g_ram.curr_savedata_ptr->s3k.clear_type != 0) && next_zone >= g_ram.curr_savedata_ptr->s3k.zone) {
      g_ram.curr_savedata_ptr->s3k.clear_type = 0;
    }
    if (next_zone >= g_ram.curr_savedata_ptr->s3k.zone) {
      g_ram.curr_savedata_ptr->s3k.zone = next_zone;
      bool game_clear = false;

      switch (g_ram.play_type) {
        case PLAY_TYPE_SONIC_AND_MILES:
        case PLAY_TYPE_SONIC:
        default:
          game_clear = next_zone > ANGEL_ISLAND_ACT_1_AND_ENDING;
          game_clear |= next_zone == ANGEL_ISLAND_ACT_1_AND_ENDING && g_ram.emeraldcnt < 7;
          break;
        case PLAY_TYPE_MILES:
          game_clear = next_zone >= ANGEL_ISLAND_ACT_1_AND_ENDING;
          break;
        case PLAY_TYPE_KNUCKLES:
          game_clear = next_zone >= DOOMSDAY;
          break;
      }

      if (game_clear) {
        g_ram.curr_savedata_ptr->s3k.clear_type = 1 + (g_ram.emeraldcnt >= 7) + (g_ram.semeraldcnt >= 7);
      }
      g_ram.curr_savedata_ptr->s3k.brings = 0;
    }
    g_ram.curr_savedata_ptr->s3k.pl_suu = g_ram.pl_suu <= 99 ? g_ram.pl_suu : 99;
    g_ram.pl_suu = g_ram.curr_savedata_ptr->s3k.pl_suu;
    write_savedata();
  }
  g_ram.brings = 0;
}


void save_game2(void) {
  if (!g_sonic3_alone) {
    save_s3k_game2();
  }
  else {
    save_s3_game2();
  }
}


static void save_s3k_game2(void) {
  if (g_ram.cartridge != 0) return;
  if (g_ram.curr_savedata_ptr == 0) return;

  if (g_ram.cartridgespec == 0) {
    g_ram.curr_savedata_ptr->s3k.specstageno = g_ram.specstageno;
  }
  g_ram.curr_savedata_ptr->s3k.specprogress0 = g_ram.specprogress[0];
  g_ram.curr_savedata_ptr->s3k.specprogress1 = g_ram.specprogress[1];
  g_ram.curr_savedata_ptr->s3k.specprogress2 = g_ram.specprogress[2];
  g_ram.curr_savedata_ptr->s3k.specprogress3 = g_ram.specprogress[3];
  g_ram.curr_savedata_ptr->s3k.specprogress4 = g_ram.specprogress[4];
  g_ram.curr_savedata_ptr->s3k.specprogress5 = g_ram.specprogress[5];
  g_ram.curr_savedata_ptr->s3k.specprogress6 = g_ram.specprogress[6];
  g_ram.curr_savedata_ptr->s3k.specprogress7 = g_ram.specprogress[7];
  g_ram.curr_savedata_ptr->s3k.brings = g_ram.brings;
  g_ram.curr_savedata_ptr->s3k.plcontinuecnt = g_ram.plcontinuecnt <= 99 ? g_ram.plcontinuecnt : 99;
  g_ram.plcontinuecnt = g_ram.curr_savedata_ptr->s3k.plcontinuecnt;
}


void save_game3(void) {
  if (g_sonic3_alone) return;
  if (g_ram.cartridge != 0) return;
  if (g_ram.curr_savedata_ptr == 0) return;

  g_ram.curr_savedata_ptr->s3k.pl_suu = g_ram.pl_suu <= 99 ? g_ram.pl_suu : 99;
  g_ram.pl_suu = g_ram.curr_savedata_ptr->s3k.pl_suu;
  g_ram.curr_savedata_ptr->s3k.plcontinuecnt = g_ram.plcontinuecnt <= 99 ? g_ram.plcontinuecnt : 99;
  g_ram.plcontinuecnt = g_ram.curr_savedata_ptr->s3k.plcontinuecnt;
  write_savedata();
}


static void read_s3_savedata(void) {
  read_vs_savedata();
  unsigned char buffer[82];
  if (sys_read_savedata(0xC0, 0x120, buffer, 25, 0x4244) == 0) {
    unsigned char* p_buffer = buffer;

    for (int i = 0; i < S3_SAVEDATA_SLOTS; ++i) {
      g_ram.savedata_slots[i].s3.new = *p_buffer++;
      g_ram.savedata_slots[i].s3.brings1 = ++*p_buffer;
      g_ram.savedata_slots[i].s3.play_type = *p_buffer++;
      g_ram.savedata_slots[i].s3.zone = *p_buffer++;
      g_ram.savedata_slots[i].s3.specstageno = *p_buffer++;
      g_ram.savedata_slots[i].s3.emeraldcnt = *p_buffer++;
      g_ram.savedata_slots[i].s3.specprogress0 = *p_buffer >> 7;
      g_ram.savedata_slots[i].s3.specprogress1 = *p_buffer >> 6;
      g_ram.savedata_slots[i].s3.specprogress2 = *p_buffer >> 5;
      g_ram.savedata_slots[i].s3.specprogress3 = *p_buffer >> 4;
      g_ram.savedata_slots[i].s3.specprogress4 = *p_buffer >> 3;
      g_ram.savedata_slots[i].s3.specprogress5 = *p_buffer >> 2;
      g_ram.savedata_slots[i].s3.specprogress6 = *p_buffer >> 1;
      g_ram.savedata_slots[i].s3.specprogress7 = *p_buffer;
      ++p_buffer;
      g_ram.savedata_slots[i].s3.brings0 = *p_buffer++;
    }
  }
  else {
    for (int i = 0; i < S3_SAVEDATA_SLOTS; ++i) {
      g_ram.savedata_slots[i].s3 = default_s3_savedata;
    }
    write_savedata();
  }
  g_ram.nosave_play_type = PLAY_TYPE_SONIC_AND_MILES;
  g_ram.dataselect_selection = 1;
}


static SKC_s3_savedata default_s3_savedata = {
  .new = 0x80,
  .brings1 = 0,
  .play_type = PLAY_TYPE_SONIC_AND_MILES,
  .zone = ANGEL_ISLAND,
  .specstageno = 0,
  .emeraldcnt = 0,
  .specprogress0 = 0,
  .specprogress1 = 0,
  .specprogress2 = 0,
  .specprogress3 = 0,
  .specprogress4 = 0,
  .specprogress5 = 0,
  .specprogress6 = 0,
  .specprogress7 = 0,
  .brings0 = 0
};


static void save_s3_game(void) {
  unsigned char next_stage_tbl[7] = {
    HYDROCITY, MARBLE_GARDEN, CARNIVAL_NIGHT, ICECAP, ICECAP, LAUNCH_BASE, MUSHROOM_HILL
  };

  if (get_act(g_ram.stageno_i) == 0) return;

  if (g_ram.curr_savedata_ptr != 0 && g_ram.curr_savedata_ptr->s3.zone <= LAUNCH_BASE) {
    g_ram.curr_savedata_ptr->s3.zone = next_stage_tbl[get_zone(g_ram.stageno_i)];
    g_ram.curr_savedata_ptr->s3.brings0 = 0;
    g_ram.curr_savedata_ptr->s3.brings1 = 0;
    write_savedata();
  }
  g_ram.brings = 0;
}


static void save_s3_game2(void) {
  if (g_ram.curr_savedata_ptr == 0) return;

  g_ram.curr_savedata_ptr->s3.specstageno = g_ram.specstageno;
  g_ram.curr_savedata_ptr->s3.emeraldcnt = g_ram.emeraldcnt;
  g_ram.curr_savedata_ptr->s3.specprogress0 = g_ram.specprogress[0];
  g_ram.curr_savedata_ptr->s3.specprogress1 = g_ram.specprogress[1];
  g_ram.curr_savedata_ptr->s3.specprogress2 = g_ram.specprogress[2];
  g_ram.curr_savedata_ptr->s3.specprogress3 = g_ram.specprogress[3];
  g_ram.curr_savedata_ptr->s3.specprogress4 = g_ram.specprogress[4];
  g_ram.curr_savedata_ptr->s3.specprogress5 = g_ram.specprogress[5];
  g_ram.curr_savedata_ptr->s3.specprogress6 = g_ram.specprogress[6];
  g_ram.curr_savedata_ptr->s3.specprogress7 = g_ram.specprogress[7];
  g_ram.curr_savedata_ptr->s3.brings0 = g_ram.brings & 0xFF;
  g_ram.curr_savedata_ptr->s3.brings1 = g_ram.brings >> 8;
  write_savedata();
}
