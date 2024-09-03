#include "globals.h"
#include "macros.h"
#include "util.h"
#include "types/spritepattern.h"
#include "types/spritestatus.h"
#include "bitdevr.h"
#include "color.h"
#include "data.h"
#include "game.h"
#include "mapdevr.h"
#include "unlze.h"
#include "vdp.h"
typedef struct codepair {
  unsigned short cnt;
  unsigned long codedigit;
}
codepair;
static void init_graphics();
static void set_palette(unsigned short* p_destination);
static unsigned short title1_color[64];
static unsigned short title2_color[64];
static unsigned char noway[44];
static unsigned char getbluespheres[51];
static void update_hscrollbuff();
static void init_specmodevars();
static void menu_init(sprite_status* p_actwk);
static void menu_wait(sprite_status* p_actwk);
static void menu_move0(sprite_status* p_actwk);
static void menu_move1(sprite_status* p_actwk);
static void header_init(sprite_status* p_actwk);
static void header_move(sprite_status* p_actwk);
static void set_stagedigits(sprite_status* p_actwk, unsigned long code);
static void set_leveldigits(sprite_status* p_actwk, unsigned long level);
static unsigned long divideby10sequence[9];
static void FUN_006a5aac(sprite_status* p_actwk, unsigned short d0, unsigned long d1);
static void FUN_006a5b93(sprite_status* p_actwk, unsigned short* p_d0, unsigned long* p_d1);
static codepair codepairs[12];
static short codedigitxposi[12];
static void codeinput_init(sprite_status* p_actwk);
static void currentcode_init(sprite_status* p_actwk);
static void init_codedigit(sprite_status* p_actwk, void(*r_ptr)(sprite_status*));
static void currentcode_move(sprite_status* p_actwk);
static void codeinput_move(sprite_status* p_actwk);
static void chk_code(sprite_status* p_actwk);
static unsigned short FUN_006a668e(unsigned char* a2, int cnt);
static void headerdigit_init(sprite_status* p_actwk);
static void init_number(sprite_status* p_actwk);
static void currentcodedigit_init(sprite_status* p_actwk);
static void currentcodedigit_move(sprite_status* p_actwk);
static void codeinputdigit_init(sprite_status* p_actwk);
static void codeinputdigit_move(sprite_status* p_actwk);
static void starttext(sprite_status* p_actwk);
static void starsphere_init(sprite_status* p_actwk);
static void starsphere_move(sprite_status* p_actwk);
static short leftstarsphereposi[3][2];
static short rightstarsphereposi[3][2];
static sprite_pattern* textpat[6];
static sprite_pattern textsp00;
static sprite_pattern textsp01;
static sprite_pattern textsp02;
static sprite_pattern textsp03;
static sprite_pattern textsp04;
static sprite_pattern textsp05;
static sprite_pattern* numberspat[12];
static sprite_pattern numberssp00;
static sprite_pattern numberssp01;
static sprite_pattern numberssp02;
static sprite_pattern numberssp03;
static sprite_pattern numberssp04;
static sprite_pattern numberssp05;
static sprite_pattern numberssp06;
static sprite_pattern numberssp07;
static sprite_pattern numberssp08;
static sprite_pattern numberssp09;
static sprite_pattern numberssp10;
static sprite_pattern numberssp11;
static sprite_pattern* starspherepat[8];
static sprite_pattern starspheresp00;
static sprite_pattern starspheresp01;
static sprite_pattern starspheresp02;
static sprite_pattern starspheresp03;
static sprite_pattern starspheresp04;
static sprite_pattern starspheresp05;
static sprite_pattern starspheresp06;
static sprite_pattern starspheresp07;
static short spriteposi[4][2];
static void character_init(sprite_status* p_actwk);
static void character_move(sprite_status* p_actwk);
static signed char* characterspriteschg[4];
static signed char characterspriteschg0[9];
static signed char characterspriteschg1[5];
static signed char characterspriteschg2[5];
static signed char characterspriteschg3[17];
static void copyright_init(sprite_status* p_actwk);
static sprite_pattern* copyrightpat[1];
static sprite_pattern copyrightsp00;
static unsigned char copyright_tiles[123];

extern void vInt();


// 006a42d4
static void init_graphics() {
  g_mdRam.unlzequeuecnt = 0;
  memset(g_mdRam.unlzequeue, 0, 108);
  g_vdpScrollPlaneAOffset = 0xC000;
  g_vdpScrollPlaneBOffset = 0xE000;
  DAT_008549d8 = 32;
  DAT_00854dec = 1;
  g_mdRam.waterflag = 0;
  g_mdRam.watermode = 0;
  clear_displaydata();
  memset(g_mdRam.pbuffer, 0, sizeof(g_mdRam.pbuffer));
  memset(g_mdRam.actwk, 0, sizeof(g_mdRam.actwk) + 52);
  init_sprlist();
  memset(g_mdRam.colorwk, 0, sizeof(g_mdRam.colorwk));
  memset(g_mdRam.colorwk2, 0, sizeof(g_mdRam.colorwk2));
  g_mdRam.stageno = 0;
  g_mdRam.vdpbuffer[0] = 0;
  g_mdRam.vdpbuffer_free = 0x8fffb00;
}


// 006a4398
void specialstagemode() {
  bgmset(225);
  fadeout();
  init_graphics();
  init_specmodevars();
  set_palette(g_mdRam.colorwk2);
  bitdevr((unsigned long*)&g_mdVram[0xB7E0], largetext_tiles, g_mdRam.bitdevwk);
  bitdevr((unsigned long*)&g_mdVram[0x32E0], specialstagemode_sklogo_tiles, g_mdRam.bitdevwk);
  unsigned char* p_chunkmappings = unlze(g_mdRam.chunkmappings128, specialstagemode_characters_tiles);
  p_chunkmappings = unlze(p_chunkmappings, specialstagemode_charactersprites_tiles);
  copy_data_vram(g_mdRam.chunkmappings128, 0, (p_chunkmappings - g_mdRam.chunkmappings128) / 2);
  unlze(&g_mdRam.chunkmappings128[0x4000], specialstagemode_text_tiles);
  copy_data_vram(&g_mdRam.chunkmappings128[0x4000], 0xA9C0, 0x6D0);
  mapdevr((unsigned short*)g_mdRam.levellayout, specialstagemode_fg_map, 0x2000);
  copy_map_vram((unsigned short*)g_mdRam.levellayout, 0xC380, 15, 39);
  mapdevr((unsigned short*)g_mdRam.levellayout, specialstagemode_bg_map, 0x4197);
  copy_map_vram((unsigned short*)g_mdRam.levellayout, 0xE09C, 7, 11);
  unsigned char* p_text = getbluespheres;
  if (g_mdRam.specmodemenu == 0) {
    p_text = noway;
    g_mdRam.levelselect_plmode = TEAM_SONIC;
    g_mdRam.vscrolla = -16;
    g_mdRam.vscrollb = -8;
  }
  load_string_vram(p_text, 256, 0x5BF);
  if (g_mdRam.specmodefull == 0) {
    g_mdRam.vscrolla = -16;
    g_mdRam.vscrollb = -8;
  }
  g_mdRam.actwk[0].r_ptr = &menu_init;
  g_mdRam.actwk[1].r_ptr = &copyright_init;
  bitdevr((unsigned long*)&g_mdVram[0xB640], copyright_tiles, g_mdRam.bitdevwk);
  g_mdRam.actwk[2].r_ptr = &character_init;
  action();
  patset();
  bgmset(40);
  fadein();

  do {
    g_mdRam.int_flg = 26;
    g_mdRam.unlzequeuecnt = 0;
    vInt();
    update_hscrollbuff();
    action();
    patset();
  } while (g_mdRam.gmmode == 44);
}


// 006a461f
static void set_palette(unsigned short* p_destination) {
  unsigned short* p_source = title2_color;
  if (g_mdRam.DAT_08ffffab == 0) {
    p_source = title1_color;
  }
  memcpy(p_destination, p_source, 128);
}


/* 006a4687 */ static unsigned short title1_color[64] = {
  0x000, 0xEEE, 0x84E, 0x40C, 0x822, 0x080, 0x00E, 0x008, 0x0AE, 0x08E, 0x8AE, 0x46A, 0xECC, 0xCAA, 0x866, 0x222,
  0x000, 0x004, 0x008, 0x00E, 0x026, 0x080, 0x08E, 0x0EE, 0x424, 0x44E, 0x68C, 0x800, 0x8CE, 0xA88, 0xE20, 0xEEE,
  0x000, 0x000, 0x000, 0x000, 0x006, 0x000, 0x000, 0x204, 0x000, 0x000, 0x000, 0x600, 0x000, 0x866, 0x200, 0x222,
  0x000, 0xEEE, 0xE48, 0xC04, 0x822, 0x080, 0xE00, 0x800, 0x0AE, 0x08E, 0x8AE, 0x46A, 0xECC, 0xCAA, 0x866, 0x222
};
/* 006a4707 */ static unsigned short title2_color[64] = {
  0x000, 0xEEE, 0x84E, 0x40C, 0x822, 0x080, 0x00E, 0x008, 0x0AE, 0x08E, 0x8AE, 0x46A, 0xECC, 0xCAA, 0x866, 0x222,
  0x000, 0x200, 0x202, 0x604, 0x202, 0x000, 0x624, 0x846, 0x200, 0x624, 0x626, 0x402, 0x846, 0x624, 0x622, 0x886,
  0x000, 0x000, 0x000, 0x000, 0x006, 0x000, 0x000, 0x204, 0x000, 0x000, 0x000, 0x600, 0x000, 0x866, 0x200, 0x222,
  0x000, 0xEEE, 0xE48, 0xC04, 0x822, 0x080, 0xE00, 0x800, 0x0AE, 0x08E, 0x8AE, 0x46A, 0xECC, 0xCAA, 0x866, 0x222
};
/* 006a4787 */ static unsigned char noway[44] = "NO WAY!    NO WAY!    NO WAY!    NO WAY?   ";
/* 006a47b3 */ static unsigned char getbluespheres[51] = "GET   BLUE   SPHERES !                            ";


// 006a47e8
static void update_hscrollbuff() {
  unsigned short* p_hscrollbuff = g_mdRam.hscrollbuff;

  for (int i = 0; i < 64; ++i) {
    *p_hscrollbuff -= 2;
    p_hscrollbuff += 2;
  }
}


// 006a484f
static void init_specmodevars() {
  g_mdRam.specmodefull = 1;
  if (g_mdRam.specmodemenu == 0) {
    g_mdRam.DAT_08ffffab = 0;
    g_mdRam.specmodelevel = 0;
    g_mdRam.specmodecode = 0x3020100;
  }
}


// 006a4fba
static void menu_init(sprite_status* p_actwk) {
  if (g_mdRam.specmodemenu == 0) {
    p_actwk->r_ptr = &menu_wait;
    p_actwk->actfree.dynamic.timer = 30;
    menu_wait(p_actwk);
  }
  else {
    menu_move0(p_actwk);
  }
}


// 006a4fe2
static void menu_wait(sprite_status* p_actwk) {
  --p_actwk->actfree.dynamic.timer;
  if (p_actwk->actfree.dynamic.timer != 0) return;
  g_mdRam.swdata1 &= 0xFF00;
  g_mdRam.specspherecnt = 255;
  g_mdRam.specringcnt = 255;
  soundset(99);
  load_string_vram(getbluespheres, 256, 0x5BF);
  menu_move0(p_actwk);
}


// 006a5058
static void menu_move0(sprite_status* p_actwk) {
  p_actwk->r_ptr = &menu_move1;
  g_mdRam.actwk[6].r_ptr = &header_init;
  util__assign_high(&g_mdRam.actwk[6].yposi, 192);
  g_mdRam.specmodemenu = 1;
  g_mdRam.DAT_08ffffaa = 0;
  g_mdRam.actwk[46].r_ptr = &starsphere_init;
  g_mdRam.actwk[47].r_ptr = &starsphere_init;
  SET_HFLIP(g_mdRam.actwk[47].actflg);
  if (g_mdRam.specmodefull != 0) {
    util__assign_high(&g_mdRam.actwk[6].yposi, 176);
    g_mdRam.actwk[18].r_ptr = &codeinput_init;
    util__assign_high(&g_mdRam.actwk[18].yposi, 324);
    g_mdRam.actwk[31].r_ptr = &currentcode_init;
    util__assign_high(&g_mdRam.actwk[31].yposi, 324);
    g_mdRam.actwk[45].r_ptr = &starttext;
    g_mdRam.DAT_08ffffaa = 1;
  }
  else if (g_mdRam.specspherecnt == 0 && g_mdRam.specringcnt == 0) {
    g_mdRam.actwk[31].r_ptr = &currentcode_init;
    util__assign_high(&g_mdRam.actwk[31].yposi, 324);
  }
}


// 006a5126
static void menu_move1(sprite_status* p_actwk) {
  if (g_mdRam.specmodefull != 0) {
    if (g_mdRam.vscrolla != 0 || g_mdRam.vscrollb != 0) {
      ++g_mdRam.vscrolla;
      if (g_mdRam.vscrolla % 2) {
        ++g_mdRam.vscrollb;
      }
      sprite_status* a1 = &g_mdRam.actwk[2];

      for (int i = 0; i < 4; ++i) {
        a1->yposi -= SHORT_TO_LONG_HIGH(1);
        ++a1;
      }
    }
    if (!(g_mdRam.specmodemenu & 0x80)) {
      if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_U) && g_mdRam.DAT_08ffffaa != 0) {
        --g_mdRam.DAT_08ffffaa;
        soundset(137);
      }
      if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_D) && g_mdRam.DAT_08ffffaa < 2) {
        ++g_mdRam.DAT_08ffffaa;
        soundset(137);
        if (g_mdRam.DAT_08ffffaa == 2) {
          g_mdRam.specmodemenu |= 0x80;
          g_mdRam.swdata1 &= 0xFF00;
        }
      }
    }
    if (g_mdRam.DAT_08ffffaa != 1) return;
  }
  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_B | PAD_S)) {
    g_mdRam.marker_flag = 0;
    g_mdRam.specmode = 1;
    g_mdRam.plmode = g_mdRam.levelselect_plmode;
    g_mdRam.pl_suu = 3;
    g_mdRam.cartridgespec = 0;
    g_mdRam.DAT_08fffe16 = 0;
    g_mdRam.gmmode = 52;
    if (IS_BUTTON_DOWN(g_mdRam.swdata1, PAD_A)) {
      unsigned long level = g_mdRam.specmodelevel;
      unsigned char* p_code = (unsigned char*)&g_mdRam.specmodecode;

      for (int i = 0; i < 4; ++i) {
        level &= 0x7F;
        *p_code++ = level;
        ++level;
      }
    }
  }
}


// 006a5332
static void header_init(sprite_status* p_actwk) {
  p_actwk->patbase = textpat;
  p_actwk->sproffset = 0x854E;
  util__assign_high(&p_actwk->xposi, 288);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 20;
  p_actwk->sprvs = 8;
  short yposi = LONG_HIGH(p_actwk->yposi) + 16;
  sprite_status* p_next_actwk = p_actwk;
  (p_actwk + 1)->patno = 10;
  short xposi = 247;

  for (int i = 0; i < 11; ++i) {
    ++p_next_actwk;
    p_next_actwk->r_ptr = &headerdigit_init;
    util__assign_high(&p_next_actwk->xposi, xposi);
    util__assign_high(&p_next_actwk->yposi, yposi);
    xposi += 8;
  }

  p_next_actwk->patno = 11;
  p_actwk->r_ptr = &header_move;
  header_move(p_actwk);
}


// 006a5444
static void header_move(sprite_status* p_actwk) {
  if (g_mdRam.specmodefull == 0
    || (g_mdRam.DAT_08ffffaa == 0 && g_mdRam.DAT_08ffffab == 0)
    || (g_mdRam.DAT_08ffffaa != 0 && g_mdRam.DAT_08ffffab != 0)) {
    unsigned long code = BYTESWAP(g_mdRam.specmodecode);
    // pack the four 7-bit values
    // 0AAAAAAA 0BBBBBBB 0CCCCCCC 0DDDDDDD
    code = (code & 0xFFFFFF00) | (code & 0x000000FF) << 1;
    // 0AAAAAAA 0BBBBBBB 0CCCCCCC DDDDDDD0
    code = (code & 0xFFFF0000) | (code & 0x0000FFFF) << 1;
    // 0AAAAAAA 0BBBBBBB CCCCCCCD DDDDDD00
    ROTATE_RIGHT(code, 16);
    // CCCCCCCD DDDDDD00 0AAAAAAA 0BBBBBBB
    code = (code & 0xFFFFFF00) | (code & 0x000000FF) << 1;
    // CCCCCCCD DDDDDD00 0AAAAAAA BBBBBBB0
    code = (code & 0xFFFF0000) | (code & 0x0000FFFF) >> 1;
    // CCCCCCCD DDDDDD00 00AAAAAA ABBBBBBB
    ROTATE_RIGHT(code, 16);
    // 00AAAAAA ABBBBBBB CCCCCCCD DDDDDD00
    code >>= 2;
    // 0000AAAA AAABBBBB BBCCCCCC CDDDDDDD
    code &= 0xFFFFFFF;
    set_stagedigits(p_actwk, code);
    p_actwk->patno = 1;
  }
  else {
    unsigned long level = (g_mdRam.specmodelevel + 1) & 0x7FFFFFF;
    set_leveldigits(p_actwk, level);
    p_actwk->patno = 0;
  }

  actionsub(p_actwk);
}


// 006a5543
static void set_stagedigits(sprite_status* p_actwk, unsigned long code) {
  code &= 0xFFFFFFF;
  sprite_status* p_next_actwk = p_actwk + 1;
  unsigned long* p_sequence = divideby10sequence;

  for (int i = 0; i < 9; ++i) {
    ++p_next_actwk;
    unsigned long d3 = *p_sequence++;
    unsigned short patno = code / d3;
    code -= patno * d3;
    p_next_actwk->patno = patno;
  }

  short xposi = 247;
  p_next_actwk = p_actwk;

  for (int i = 0; i < 11; ++i) {
    ++p_next_actwk;
    util__assign_high(&p_next_actwk->xposi, xposi);
    xposi += 8;
  }
}


// 006a5670
static void set_leveldigits(sprite_status* p_actwk, unsigned long level) {
  level &= 0x7FFFFFF;
  sprite_status* p_next_actwk = p_actwk + 1;
  unsigned long* p_sequence = divideby10sequence;
  unsigned short cnt = 8;
  unsigned short digit_cnt = 0;

  do {
    ++p_next_actwk;
    unsigned long d3 = *p_sequence++;
    unsigned short patno = level / d3;
    level -= patno * d3;
    if (patno != 0 && digit_cnt == 0) {
      digit_cnt = cnt + 1;
    }
    if (digit_cnt == 0) {
      patno = 10;
    }
    p_next_actwk->patno = patno;
  } while (cnt-- != 0);

  cnt = 9 - digit_cnt;
  short xposi = 247 + cnt * 4;
  p_next_actwk = p_actwk;

  do {
    ++p_next_actwk;
    util__assign_high(&p_next_actwk->xposi, xposi);
  } while (cnt-- != 0);

  do {
    ++p_next_actwk;
    xposi += 8;
    util__assign_high(&p_next_actwk->xposi, xposi);
  } while (digit_cnt-- != 0);
}


/* 006a5a88 */ static unsigned long divideby10sequence[9] = {
  100000000,
  10000000,
  1000000,
  100000,
  10000,
  1000,
  100,
  10,
  1
};


// 006a5aac
static void FUN_006a5aac(sprite_status* p_actwk, unsigned short d0, unsigned long d1) {
  codepair* p_pair = codepairs;

  for (int i = 0; i < 12; ++i) {
    ++p_actwk;
    unsigned short patno = 0;
    bool carry;

    do {
      carry = p_pair->codedigit > d1;
      d1 -= p_pair->codedigit;
      d1 &= 0xFFFFFFFF; // not sure if this is correct
      bool carry2 = p_pair->cnt > d0;
      d0 -= p_pair->cnt;
      if (carry) {
        carry2 = d0 == 0;
        --d0;
      }
      if (carry2) break;
      ++patno;
    } while (1);

    carry = util__get_add_long_carry(d1, p_pair->codedigit);
    d1 += p_pair->codedigit;
    d1 &= 0xFFFFFFFF;
    d0 += p_pair->cnt;
    if (carry) {
      ++d0;
    }
    p_actwk->patno = patno;
  }
}


// 006a5b93
static void FUN_006a5b93(sprite_status* p_actwk, unsigned short* p_d0, unsigned long* p_d1) {
  codepair* p_pair = codepairs;

  for (int i = 0; i < 12; ++i) {
    ++p_actwk;
    if (p_actwk->patno != 0) {
      for (int j = 0; j < p_actwk->patno - 1; ++j) {
        bool carry = util__get_add_long_carry(*p_d1, p_pair->codedigit);
        *p_d1 += p_pair->codedigit;
        *p_d1 &= 0xFFFFFFFF;
        *p_d0 += p_pair->cnt;
        if (carry) {
          ++*p_d0;
        }
      }
    }
    ++p_pair;
  }
}


/* 006a5c7f */ static codepair codepairs[12] = {
  { 23, 0x4876E800 },
  {  2, 0x540BE400 },
  {  0, 1000000000 },
  {  0,  100000000 },
  {  0,   10000000 },
  {  0,    1000000 },
  {  0,     100000 },
  {  0,      10000 },
  {  0,       1000 },
  {  0,        100 },
  {  0,         10 },
  {  0,          1 }
};


/* 006a5cc7 */ static short codedigitxposi[12] = {
  268,
  276,
  284,
  292,
  308,
  316,
  324,
  332,
  348,
  356,
  364,
  372
};


// 006a5cdf
static void codeinput_init(sprite_status* p_actwk) {
  p_actwk->r_ptr = &codeinput_move;
  init_codedigit(p_actwk, &codeinputdigit_init);
}


// 006a5cf8
static void currentcode_init(sprite_status* p_actwk) {
  p_actwk->r_ptr = &currentcode_move;
  init_codedigit(p_actwk, &currentcodedigit_init);
}


// 006a5d0f
static void init_codedigit(sprite_status* p_actwk, void(*r_ptr)(sprite_status*)) {
  p_actwk->patbase = textpat;
  p_actwk->sproffset = 0x854E;
  util__assign_high(&p_actwk->xposi, 212);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 20;
  p_actwk->sprvs = 8;
  p_actwk->patno = 2;
  short* p_xposi = codedigitxposi;
  sprite_status* p_next_actwk = p_actwk;

  for (int i = 0; i < 12; ++i) {
    ++p_next_actwk;
    p_next_actwk->r_ptr = r_ptr;
    util__assign_high(&p_next_actwk->xposi, *p_xposi++);
    p_next_actwk->xposi -= SHORT_TO_LONG_HIGH(12);
    util__copy_high(&p_next_actwk->yposi, &p_actwk->yposi);
  }
}


// 006a5e09
static void currentcode_move(sprite_status* p_actwk) {
  if (g_mdRam.specmodemenu & 0x80) return;

  unsigned char* a2 = g_mdRam.direc_x;
  a2[3] = (g_mdRam.specmodelevel & 0x000000FF);
  a2[2] = (g_mdRam.specmodelevel & 0x0000FF00) >> 8;
  a2[1] = (g_mdRam.specmodelevel & 0x00FF0000) >> 16;
  a2[0] = (g_mdRam.specmodelevel & 0xFF000000) >> 24;
  unsigned long* a2_long = (unsigned long*)&g_mdRam.direc_x;
  if (g_mdRam.DAT_08ffffab != 0) {
    *a2_long = BYTESWAP(*a2_long);
    *a2_long += 0x7654321;
    *a2_long = BYTESWAP(*a2_long);
  }
  *a2_long &= 0xFFFFFF07;
  unsigned short d4 = FUN_006a668e(a2, 2);
  unsigned short d0 = d4 & 0x3F;
  if (g_mdRam.DAT_08ffffab != 0) {
    d0 |= 0x40;
  }
  d0 ^= 0x55;
  unsigned long d1 = g_mdRam.specmodelevel + 0x1234567;
  d1 &= 0x7FFFFFF;
  ROTATE_RIGHT(d1, 16);
  d4 <<= 5;
  d4 &= 0xF800;
  d1 = (d1 & 0xFFFF0000) | ((d1 & 0x0000FFFF) | d4);
  ROTATE_RIGHT(d1, 16);
  ROTATE_RIGHT(d1, 6);
  d1 ^= 0xAAAAAAAA;
  FUN_006a5aac(p_actwk, d0, d1);
  actionsub(p_actwk);
}


// 006a5f81
static void codeinput_move(sprite_status* p_actwk) {
  if (!(g_mdRam.specmodemenu & 0x80)) {
    SPRITE_STATUS_USHORT(p_actwk, 48) = 0;
    return;
  }

  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_B | PAD_S)) {
    chk_code(p_actwk);
  }
  sprite_status* p_next_actwk = p_actwk + (SPRITE_STATUS_USHORT(p_actwk, 48) + 1);
  p_next_actwk->sproffset = 0x854E;
  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_U)) {
    if (p_next_actwk->patno-- == 0) {
      p_next_actwk->patno = 9;
    }
  }
  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_D)) {
    ++p_next_actwk->patno;
    if (p_next_actwk->patno >= 10) {
      p_next_actwk->patno = 0;
    }
  }
  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_L)) {
    if (SPRITE_STATUS_USHORT(p_actwk, 48)-- == 0) {
      SPRITE_STATUS_USHORT(p_actwk, 48) = 11;
    }
  }
  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_R)) {
    ++SPRITE_STATUS_USHORT(p_actwk, 48);
    if (SPRITE_STATUS_USHORT(p_actwk, 48) >= 12) {
      SPRITE_STATUS_USHORT(p_actwk, 48) = 0;
    }
  }

  if (g_mdRam.specmodemenu & 0x80) {
    p_next_actwk = p_actwk + (SPRITE_STATUS_USHORT(p_actwk, 48) + 1);
    p_next_actwk->sproffset = 0x8562;
  }
  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_U | PAD_D | PAD_L | PAD_R)) {
    soundset(137);
  }
}


// 006a61b0
static void chk_code(sprite_status* p_actwk) {
  unsigned short d0 = 0;
  unsigned long d1l = 0;
  FUN_006a5b93(p_actwk, &d0, &d1l);
  d0 ^= 0x55;
  unsigned short d2 = d0 & 0x3F;
  d1l ^= 0xAAAAAAAA;
  ROTATE_LEFT(d1l, 6);
  ROTATE_RIGHT(d1l, 16);
  unsigned short d3 = d1l & 0xFFFF;
  d3 &= 0xF800;
  d3 >>= 5;
  d3 |= d0;
  d3 &= 0x7FF;
  ROTATE_RIGHT(d1l, 16);
  d1l -= 0x1234567;
  d2 &= 0x40;
  if (d2 != 0) {
    d1l &= 0x7654321;
  }
  d1l &= 0x7FFFFFF;
  d1l = BYTESWAP(d1l);
  *((unsigned long*)&g_mdRam.direc_x) = d1l;
  unsigned short d4 = FUN_006a668e(g_mdRam.direc_x, 2);
  d4 &= 0x7FF;
  if (d3 == d4) {
    g_mdRam.DAT_08ffffab = 0;
    if (d2 != 0) {
      d1l -= 0x7654321;
      d1l &= 0x7FFFFFF;
      g_mdRam.DAT_08ffffab = 255;
    }
    g_mdRam.specmodelevel = d1l;

    unsigned char* a2 = (unsigned char*)&g_mdRam.specmodecode;
    unsigned long d0l = d1l;
    d0l &= 0xFFFFFF7F;
    *a2++ = d0l & 0xFF;

    d0l = d1l * 3;
    ++d0l;
    unsigned long d2l = (d0l & 0xFFFF0000) >> 16;
    d2l = d2l % 127 << 16 | (d0l & 0xFFFF);
    d2l = d2l % 127 << 16 | d2l / 127;
    ROTATE_RIGHT(d2l, 16);
    *a2++ = d2l & 0xFF;

    d0l = d1l * 5;
    d0l += 2;
    d2l = (d0l & 0xFFFF0000) >> 16;
    d2l = d2l % 126 << 16 | (d0l & 0xFFFF);
    d2l = d2l % 126 << 16 | d2l / 126;
    ROTATE_RIGHT(d2l, 16);
    *a2++ = d2l & 0xFF;

    d0l = d1l * 7;
    d0l += 3;
    d2l = (d0l & 0xFFFF0000) >> 16;
    d2l = d2l % 125 << 16 | (d0l & 0xFFFF);
    d2l = d2l % 125 << 16 | d2l / 125;
    ROTATE_RIGHT(d2l, 16);
    *a2++ = d2l & 0xFF;

    set_palette(g_mdRam.colorwk);
    soundset(99);
    g_mdRam.specmodemenu &= 0x7F;
    g_mdRam.DAT_08ffffaa = 1;
  }
  else {
    soundset(178);
    g_mdRam.specmodemenu &= 0x7F;
    g_mdRam.DAT_08ffffaa = 1;
  }
}


// 006a668e
static unsigned short FUN_006a668e(unsigned char* a2, int cnt) {
  unsigned short d4 = 0;

  for (int i = 0; i < cnt; ++i) {
    unsigned short d5 = *a2++;
    d5 <<= 8;
    d5 |= *a2++;
    d4 ^= d5;
    unsigned char carry = d4 & 1;
    d4 >>= 1;
    if (carry == 1) {
      d4 ^= 0x8810;
    }
  }

  return d4;
}


// 006a6721
static void headerdigit_init(sprite_status* p_actwk) {
  init_number(p_actwk);
  p_actwk->r_ptr = &actionsub;
}


// 006a6738
static void init_number(sprite_status* p_actwk) {
  p_actwk->patbase = numberspat;
  p_actwk->sproffset = 0x854E;
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
}


// 006a6779
static void currentcodedigit_init(sprite_status* p_actwk) {
  init_number(p_actwk);
  p_actwk->r_ptr = &currentcodedigit_move;
  currentcodedigit_move(p_actwk);
}


// 006a678b
static void currentcodedigit_move(sprite_status* p_actwk) {
  if (!(g_mdRam.specmodemenu & 0x80)) {
    actionsub(p_actwk);
  }
}


// 006a679a
static void codeinputdigit_init(sprite_status* p_actwk) {
  init_number(p_actwk);
  p_actwk->r_ptr = &codeinputdigit_move;
  codeinputdigit_move(p_actwk);
}


// 006a67ac
static void codeinputdigit_move(sprite_status* p_actwk) {
  if (g_mdRam.specmodemenu & 0x80) {
    actionsub(p_actwk);
  }
}


// 006a67bb
static void starttext(sprite_status* p_actwk) {
  p_actwk->patbase = textpat;
  p_actwk->sproffset = 0x854E;
  util__assign_high(&p_actwk->xposi, 288);
  util__assign_high(&p_actwk->yposi, 296);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 20;
  p_actwk->sprvs = 8;
  p_actwk->patno = 3;
  p_actwk->r_ptr = &actionsub;
}


// 006a6834
static void starsphere_init(sprite_status* p_actwk) {
  p_actwk->patbase = starspherepat;
  p_actwk->sproffset = 0xE598;
  switch (g_mdRam.levelselect_plmode) {
    case TEAM_SONIC:
      p_actwk->sproffset = 0xE598;
      break;
    case TEAM_KNUCKLES:
      p_actwk->sproffset = 0x8598;
      break;
  }
  util__assign_high(&p_actwk->xposi, 256);
  util__assign_high(&p_actwk->yposi, 294);
  if (g_mdRam.specmodefull == 0) {
    util__assign_high(&p_actwk->yposi, 190);
  }
  p_actwk->actfree.ssm_starsphere.p_posi = (short*)leftstarsphereposi;
  if (IS_HFLIP(p_actwk->actflg)) {
    util__assign_high(&p_actwk->xposi, 320);
    p_actwk->actfree.ssm_starsphere.p_posi = (short*)rightstarsphereposi;
  }
  p_actwk->sprpri = PRI_0;
  p_actwk->sprhs = 8;
  p_actwk->sprvs = 8;
  p_actwk->r_ptr = &starsphere_move;
  starsphere_move(p_actwk);
}


// 006a690c
static void starsphere_move(sprite_status* p_actwk) {
  if (g_mdRam.specmodefull != 0) {
    short* p_posi = p_actwk->actfree.ssm_starsphere.p_posi;
    p_posi += g_mdRam.DAT_08ffffaa * 2;
    short wk;

    if (p_posi[0] == LONG_HIGH(p_actwk->xposi) && p_actwk->xspeed + 128 <= 256) {
      wk = 0;
      p_actwk->xspeed = 0;
    }
    else {
      wk = 64;
      if (p_posi[0] < LONG_HIGH(p_actwk->xposi)) {
        wk = -wk;
        if (p_actwk->xspeed >= 0) {
          wk *= 4;
        }
      }
      else {
        if (p_actwk->xspeed < 0) {
          wk *= 4;
        }
      }
    }
    p_actwk->xspeed += wk;

    if (p_posi[1] == LONG_HIGH(p_actwk->yposi) && p_actwk->yspeed + 256 <= 512) {
      wk = 0;
      p_actwk->yspeed = 0;
    }
    else {
      wk = 128;
      if (p_posi[1] < LONG_HIGH(p_actwk->yposi)) {
        wk = -wk;
        if (p_actwk->yspeed >= 0) {
          wk *= 4;
        }
      }
      else {
        if (p_actwk->yspeed < 0) {
          wk *= 4;
        }
      }
    }
    p_actwk->yspeed += wk;

    p_actwk->xposi += p_actwk->xspeed * 256;
    p_actwk->yposi += p_actwk->yspeed * 256;
  }

  if (p_actwk->pattim-- == 0) {
    p_actwk->pattim = 2;
    ++p_actwk->patno;
    p_actwk->patno &= 7;
  }
  if (IS_BUTTON_PRESSED(g_mdRam.swdata1, PAD_A | PAD_C)) {
    switch (p_actwk->sproffset) {
      case 0x8598:
        g_mdRam.levelselect_plmode = TEAM_SONIC;
        p_actwk->sproffset = 0xE598;
        break;
      case 0xE598:
        g_mdRam.levelselect_plmode = TEAM_KNUCKLES;
        p_actwk->sproffset = 0x8598;
        break;
    }
  }
  actionsub(p_actwk);
}


/* 006a6d4d */ static short leftstarsphereposi[3][2] = {
  { 256, 174 },
  { 256, 294 },
  { 200, 322 }
};
/* 006a6d59 */ static short rightstarsphereposi[3][2] = {
  { 320, 174 },
  { 320, 294 },
  { 376, 322 }
};


/* 006a6d65 */ static sprite_pattern* textpat[6] = {
  &textsp00,
  &textsp01,
  &textsp02,
  &textsp03,
  &textsp04,
  &textsp05
};


static sprite_pattern textsp00 = {
  4,
  {
    { -8, 5, 0x0004, -20 },
    { -8, 1, 0x0008,  -4 },
    { -8, 1, 0x0006,   4 },
    { -8, 1, 0x0004,  12 }
  }
};
static sprite_pattern textsp01 = {
  5,
  {
    { -8, 1, 0x004A, -20 },
    { -8, 1, 0x0040, -12 },
    { -8, 1, 0x0046,  -4 },
    { -8, 1, 0x004C,   4 },
    { -8, 1, 0x0006,  12 }
  }
};
static sprite_pattern textsp02 = {
  3,
  {
    { -8, 9, 0x000A,  0 },
    { -8, 1, 0x0006, 24 },
    { -8, 1, 0x0010, 32 }
  }
};
static sprite_pattern textsp03 = {
  5,
  {
    { -8, 1, 0x004A, -20 },
    { -8, 1, 0x0040, -12 },
    { -8, 1, 0x0046,  -4 },
    { -8, 1, 0x004E,   4 },
    { -8, 1, 0x0040,  12 }
  }
};
static sprite_pattern textsp04 = {
  8,
  {
    { -8, 1, 0x000E, -40 },
    { -8, 5, 0x003A, -32 },
    { -8, 1, 0x003C, -16 },
    { -8, 1, 0x003A,  -8 },
    { -8, 1, 0x000A,   0 },
    { -8, 1, 0x003E,   8 },
    { -8, 1, 0x0004,  16 },
    { -8, 5, 0x0040,  24 }
  }

};
static sprite_pattern textsp05 = {
  11,
  {
    { -8, 1, 0x000E, -40 },
    { -8, 5, 0x003A, -32 },
    { -8, 1, 0x003C, -16 },
    { -8, 1, 0x003A,  -8 },
    { -8, 1, 0x000A,   0 },
    { -8, 1, 0x003E,   8 },
    { -8, 1, 0x0004,  16 },
    { -8, 5, 0x0040,  24 },
    {  8, 9, 0x0044, -12 },
    {  8, 5, 0x0000, -28 },
    {  8, 5, 0x0000,  12 }
  }
};


/* 006a6e55 */ static sprite_pattern* numberspat[12] = {
  &numberssp00,
  &numberssp01,
  &numberssp02,
  &numberssp03,
  &numberssp04,
  &numberssp05,
  &numberssp06,
  &numberssp07,
  &numberssp08,
  &numberssp09,
  &numberssp10,
  &numberssp11
};


static sprite_pattern numberssp00 = {
  1,
  {
    { -8, 1, 0x0012, -4 }
  }
};
static sprite_pattern numberssp01 = {
  1,
  {
    { -8, 1, 0x0014, -4 }
  }
};
static sprite_pattern numberssp02 = {
  1,
  {
    { -8, 1, 0x0016, -4 }
  }
};
static sprite_pattern numberssp03 = {
  1,
  {
    { -8, 1, 0x0018, -4 }
  }
};
static sprite_pattern numberssp04 = {
  1,
  {
    { -8, 1, 0x001A, -4 }
  }
};
static sprite_pattern numberssp05 = {
  1,
  {
    { -8, 1, 0x001C, -4 }
  }
};
static sprite_pattern numberssp06 = {
  1,
  {
    { -8, 1, 0x001E, -4 }
  }
};
static sprite_pattern numberssp07 = {
  1,
  {
    { -8, 1, 0x0020, -4 }
  }
};
static sprite_pattern numberssp08 = {
  1,
  {
    { -8, 1, 0x0022, -4 }
  }
};
static sprite_pattern numberssp09 = {
  1,
  {
    { -8, 1, 0x0024, -4 }
  }
};
static sprite_pattern numberssp10 = {
  1,
  {
    { -8, 5, 0x0000, -12 }
  }
};
static sprite_pattern numberssp11 = {
  1,
  {
    { -8, 5, 0x0000, -4 }
  }
};


/* 006a6ecd */ static sprite_pattern* starspherepat[8] = {
  &starspheresp00,
  &starspheresp01,
  &starspheresp02,
  &starspheresp03,
  &starspheresp04,
  &starspheresp05,
  &starspheresp06,
  &starspheresp07
};


static sprite_pattern starspheresp00 = {
  1,
  {
    { -8, 5, 0x0006, -8 }
  }
};
static sprite_pattern starspheresp01 = {
  1,
  {
    { -8, 5, 0x000A, -8 }
  }
};
static sprite_pattern starspheresp02 = {
  1,
  {
    { -8, 5, 0x000E, -8 }
  }
};
static sprite_pattern starspheresp03 = {
  1,
  {
    { -8, 5, 0x0012, -8 }
  }
};
static sprite_pattern starspheresp04 = {
  1,
  {
    { -8, 5, 0x0016, -8 }
  }
};
static sprite_pattern starspheresp05 = {
  1,
  {
    { -8, 5, 0x0812, -8 }
  }
};
static sprite_pattern starspheresp06 = {
  1,
  {
    { -8, 5, 0x080E, -8 }
  }
};
static sprite_pattern starspheresp07 = {
  1,
  {
    { -8, 5, 0x080A, -8 }
  }
};


/* 006a6f1d */ static short spriteposi[4][2] = {
  { 184, 256 },
  { 268, 248 },
  { 304, 244 },
  { 376, 224 }
};


// 006a6f2d
static void character_init(sprite_status* p_actwk) {
  sprite_status* p_next_actwk = p_actwk;
  for (int i = 0; i < 4; ++i) {
    p_next_actwk->patbase = specialstagemode_characters_pat;
    p_next_actwk->sproffset = 0x20FE;
    util__assign_high(&p_next_actwk->xposi, spriteposi[i][0]);
    util__assign_high(&p_next_actwk->yposi, spriteposi[i][1]);
    if (g_mdRam.specmodemenu != 0 && g_mdRam.specmodefull != 0) {
      p_next_actwk->yposi -= SHORT_TO_LONG_HIGH(16);
    }
    p_next_actwk->sprpri = PRI_3;
    p_next_actwk->sprhs = 16;
    p_next_actwk->sprvs = 16;
    p_next_actwk->r_ptr = &character_move;
    p_next_actwk->mstno = 3 - i;
    p_next_actwk->patno = characterspriteschg[3 - i][0];
    ++p_next_actwk;
  }

  character_move(p_actwk);
}


// 006a708e
static void character_move(sprite_status* p_actwk) {
  if (g_mdRam.specmodefull != 0) {
    patchg2(p_actwk, characterspriteschg);
  }
  actionsub(p_actwk);
}


/* 006a70ab */ static signed char* characterspriteschg[4] = {
  characterspriteschg3,
  characterspriteschg2,
  characterspriteschg1,
  characterspriteschg0
};


static signed char characterspriteschg0[9] = {
  0, 63, 1, 1, 2, 7, 1, 1, -1
};
static signed char characterspriteschg1[5] = {
  3, 15, 4, 15, -1
};
static signed char characterspriteschg2[5] = {
  5, 63, 6, 15, -1
};
static signed char characterspriteschg3[17] = {
  7, 31, 8, 7, 7, 7, 8, 7, 7, 7, 8, 7, 7, 7, 8, 7, -1
};


// 006a70d8
static void copyright_init(sprite_status* p_actwk) {
  p_actwk->patbase = copyrightpat;
  p_actwk->sproffset = 0x85B2;
  util__assign_high(&p_actwk->xposi, 320);
  util__assign_high(&p_actwk->yposi, 338);
  p_actwk->sprpri = PRI_1;
  p_actwk->sprhs = 44;
  p_actwk->sprvs = 4;
  p_actwk->r_ptr = &actionsub;
  actionsub(p_actwk);
}


/* 006a7146 */ static sprite_pattern* copyrightpat[1] = {
  &copyrightsp00
};


static sprite_pattern copyrightsp00 = {
  6,
  {
    { 0,  0, 0x0000,   0 },
    { 0,  8, 0x0001,   8 },
    { 0,  4, 0x0004,  32 },
    { 0,  8, 0x0001,  48 },
    { 0, 12, 0x0006,  72 },
    { 0,  4, 0x000A, 104 }
  }
};


/* 006a826d */ static unsigned char copyright_tiles[123] = { 0x0c, 0x00, 0x80, 0x05, 0x1b, 0x13, 0x04, 0x24, 0x0a, 0x34, 0x0c, 0x45, 0x1e, 0x54, 0x0b, 0x65, 0x1a, 0x73, 0x02, 0x81, 0x03, 0x03, 0x12, 0x00, 0x27, 0x7d, 0x35, 0x1c, 0x45, 0x1d, 0x57, 0x7c, 0xff, 0x9c, 0xa7, 0x8f, 0x6e, 0x10, 0xdb, 0xc3, 0x6f, 0x08, 0x47, 0xb7, 0x8e, 0xb8, 0xb0, 0xd3, 0xd3, 0xd3, 0xd3, 0xbf, 0xa9, 0x67, 0x28, 0x84, 0x21, 0x5d, 0xb2, 0x75, 0x2c, 0xe5, 0x10, 0x84, 0x2b, 0xb6, 0x4e, 0xa5, 0x85, 0x9b, 0x28, 0xd9, 0x46, 0xca, 0xf9, 0xe1, 0x24, 0x95, 0x16, 0x69, 0xdb, 0x5a, 0xf9, 0x67, 0x8f, 0x16, 0x58, 0x92, 0x8e, 0xcd, 0x34, 0xac, 0x4b, 0x94, 0xef, 0xb4, 0x42, 0x10, 0x9d, 0xc6, 0x97, 0x29, 0xdf, 0xc8, 0x59, 0x7f, 0x29, 0xa5, 0xc5, 0xef, 0xb4, 0xe1, 0x4e, 0x15, 0xd8, 0x24, 0xf4, 0x59, 0xa3, 0xdf, 0x74, 0x2c, 0x00 };
