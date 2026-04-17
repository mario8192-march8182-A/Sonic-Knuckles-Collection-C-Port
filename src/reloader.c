#include "reloader.h"
#include <string.h>
#include "data/colortbl.h"
#include "data/cg/friend.h"
#include "data/cg/item.h"
#include "data/cg/toge.h"
#include "types/cgdata.h"
#include "types/sonic3ram.h"
#include "utils/stageno.h"
#include "dev.h"
#include "shared.h"
static void zone0010(void);
static void zone0020(void);
static void zone0110(void);
static void zone0120(void);
static void zone0210(void);
static void zone0220(void);
static void zone0310(void);
static void zone0320(void);
static void zone0410(void);
static void zone0420(void);
static void zone0510(void);
static void zone0520(void);
static void zone0610(void);
static void zone0620(void);
static void zone0710(void);
static void zone0720(void);
static void zone0810(void);
static void zone0820(void);
static void zone0910(void);
static void zone0920(void);
static void zone0a10(void);
static void zone0a20(void);
static void zone0b10(void);
static void zone0b20(void);
static void zone0c10(void);
static void zone0c20(void);
static void zone0d10(void);
static void zone0d20(void);
static void zone0e10(void);
static void zone0e20(void);
static void zone0f10(void);
static void zone0f20(void);
static void zone1010(void);
static void zone1020(void);
static void zone1110(void);
static void zone1120(void);
static void zone1210(void);
static void zone1220(void);
static void zone1310(void);
static void zone1320(void);
static void zone1410(void);
static void zone1420(void);
static void zone1510(void);
static void zone1520(void);
static void zone1610(void);
static void zone1620(void);
static void zone1710(void);
static void zone1720(void);
static SKC_cg_data z0020_cg_tbl;
static unsigned short emy0020color[16];
static unsigned short emy0520color[16];

extern sonic3_ram g_ram;


void cg_reset(void) {
  void(*jmp_tbl[24][2])(void) = {
    { &zone0010, &zone0020 },
    { &zone0110, &zone0120 },
    { &zone0210, &zone0220 },
    { &zone0310, &zone0320 },
    { &zone0410, &zone0420 },
    { &zone0510, &zone0520 },
    { &zone0610, &zone0620 },
    { &zone0710, &zone0720 },
    { &zone0810, &zone0820 },
    { &zone0910, &zone0920 },
    { &zone0a10, &zone0a20 },
    { &zone0b10, &zone0b20 },
    { &zone0c10, &zone0c20 },
    { &zone0d10, &zone0d20 },
    { &zone0e10, &zone0e20 },
    { &zone0f10, &zone0f20 },
    { &zone1010, &zone1020 },
    { &zone1110, &zone1120 },
    { &zone1210, &zone1220 },
    { &zone1310, &zone1320 },
    { &zone1410, &zone1420 },
    { &zone1510, &zone1520 },
    { &zone1610, &zone1620 },
    { &zone1710, &zone1720 }
  };

  jmp_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)]();
}


static void zone0010(void) {
  memcpy(&g_ram.colorwk[16], angelisland12_color, sizeof(angelisland12_color));
}


static void zone0020(void) {
  set_emy_cor((unsigned short(*)[16])angelisland2_color);
  divdevset2(&z0020_cg_tbl);
}


static void zone0110(void) {
}


static void zone0120(void) {
}


static void zone0210(void) {
  divdevset2(&itembane_cg_tbl);
}


static void zone0220(void) {
  zone0210();
}


static void zone0310(void) {
}


static void zone0320(void) {
}


static void zone0410(void) {
}


static void zone0420(void) {
}


static void zone0510(void) {
}


static void zone0520(void) {
  set_emy_cor((unsigned short(*)[16])icecap2_color);
}


static void zone0610(void) {
  zone0720();
}


static void zone0620(void) {
  zone0720();
}


static void zone0710(void) {
  zone0720();
}


static void zone0720(void) {
  set_emy_cor((unsigned short(*)[16])mushroomhill2_color);
}


static void zone0810(void) {
}


static void zone0820(void) {
}


static void zone0910(void) {
}


static void zone0920(void) {
}


static void zone0a10(void) {
}


static void zone0a20(void) {
}


static void zone0b10(void) {
}


static void zone0b20(void) {
}


static void zone0c10(void) {
}


static void zone0c20(void) {
}


static void zone0d10(void) {
}


static void zone0d20(void) {
}


static void zone0e10(void) {
}


static void zone0e20(void) {
}


static void zone0f10(void) {
}


static void zone0f20(void) {
}


static void zone1010(void) {
}


static void zone1020(void) {
}


static void zone1110(void) {
}


static void zone1120(void) {
}


static void zone1210(void) {
}


static void zone1220(void) {
}


static void zone1310(void) {
}


static void zone1320(void) {
}


static void zone1410(void) {
}


static void zone1420(void) {
}


static void zone1510(void) {
}


static void zone1520(void) {
}


static void zone1610(void) {
}


static void zone1620(void) {
}


static void zone1710(void) {
}


static void zone1720(void) {
}


static SKC_cg_data z0020_cg_tbl = {
  6,
  {
    { item_cg, 0x9880 },
    { AIZMisc2, 0x5D20 },
    { ropeswing_cg, 0x8360 },
    { AIZBackgroundTree_cg, 0x8700 },
    { awa_cg, 0x8B80 },
    { switch_cg, 0x8AC0 },
    { AIZCorkFloor2_cg, 0x8800 }
  }
};


static unsigned short emy0020color[16] = {
  0x000, 0xEEE, 0xEC0, 0xE60, 0xC22, 0x0EE, 0x088, 0x60A, 0x08E, 0x02E, 0x844, 0x020, 0xEAA, 0xA66, 0xECC, 0x044
};


static unsigned short emy0520color[16] = {
  0x000, 0xEEE, 0xEC0, 0xE60, 0xC22, 0x0EE, 0x088, 0x08E, 0x02C, 0x822, 0x000, 0x020, 0xCAA, 0x866, 0x644, 0x044
};


SKC_cg_data itembane_cg_tbl = {
  1,
  {
    { item_cg, 0x9880 },
    { toge_cg, 0x9280 }
  }
};


SKC_cg_data item_cg_tbl = {
  0,
  {
    { item_cg, 0x9880 }
  }
};


SKC_cg_data friend_cg_tbl = {
  2,
  {
    { bakuhatu_cg, 0xB400 },
    { ricky_cg, 0xB000 },
    { flicky_cg, 0xB240 }
  }
};


SKC_cg_data exp01_cg_tbl = {
  0,
  {
    { exp01_cg, 0xA000 }
  }
};


SKC_cg_data bakuhatu_cg_tbl = {
  0,
  {
    { bakuhatu_cg, 0xB400 }
  }
};


SKC_cg_data opnbox_cg_tbl = {
  0,
  {
    { opnbox_cg, 0x9280 }
  }
};


SKC_cg_data eggmbl_cg_tbl = {
  0,
  {
    { eggmbl_cg, 0xA5C0 }
  }
};
