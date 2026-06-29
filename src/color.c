#include "color.h"
#include <stdbool.h>
#include <string.h>
#include "data/colortbl.h"
#include "types/sonic3ram.h"
#include "utils/stageno.h"
static void worknai(void);
static void colchg0000(void);
static void colchg0001(void);
static void colchg0100(void);
static void colchg03(void);
static void colchg04(void);
static void colchg05(void);
static void colchg0600(void);
static void colchg0601(void);
static void colchg06(unsigned short (*p_col)[3]);
static void colchg0800(void);
static void colchg0801(void);
static void colchg0900(void);
static void colchg0901(void);
static void colchg0b00(void);
static void colchg0b01(void);
static void colchg0f(void);
static void colchg11(void);
static void colchg12(void);
static void colchg14(void);
static void colchg15(void);
static void colchg1600(void);
static void colchg1601(void);
static unsigned short col000col[4][4];
static unsigned short col001col[16][4];
static unsigned short col002col[16][3];
static unsigned short col003col[8][3];
static unsigned short col004col[4][4];
static unsigned short col005col[8][3];
static unsigned short col006col[8][3];
static unsigned short col007col[26];
static unsigned short col008col[26];
static unsigned short col010col[4][4];
static unsigned short col030col[16][3];
static unsigned short col031col[30][3];
static unsigned short col032col[32];
static unsigned short col033col[16][3];
static unsigned short col034col[30][3];
static unsigned short col050col[16][2];
static unsigned short col051col[18][2];
static unsigned short col052col[6][2];
static unsigned short col053col[16][2];
static unsigned short col060col[3][3];
static unsigned short col061col[3][3];
static unsigned short col080col[5][4][4];
static unsigned short* col081col[5][2];
static unsigned short col090col[16][4];
static unsigned short col091col[9][2];
static unsigned short col092col[17];
static unsigned short col093col[32][4];
static unsigned short col0b0col[12][2];
static unsigned short col0b1col[4][5];
static unsigned short col0b2col[6][4];
static unsigned short col0f0col[3][3];
static unsigned short col0f1col[21][3];
static unsigned short col110col[10][4];
static unsigned short col120col[30];
static unsigned short col121col[14][2];
static unsigned short col150col[8][4];
static unsigned short col151col[16][4];
static unsigned short col152col[6];
static unsigned short col16000col[15][2];
static unsigned short col16010col[10][2];
static void colchgsupersub(void);
static void colchgsupersub0(unsigned short* p_colorwk, unsigned short (*p_col)[3], unsigned short* p_colorwk3, unsigned short (*p_col3)[3], unsigned short clchgcnt);
static unsigned short ssoniccolor2[10][3];
static unsigned short ssoniccolor3[10][3];
static unsigned short hsoniccolor[12][3];
static unsigned short smilescolor[6][3];
static unsigned short sknucklescolor[10][3];
static unsigned short sknucklescolor2[1][3];
static void fadein2(unsigned short* p_destination, unsigned short* p_source);
static void fadein0(void);
static void fadeout2(unsigned short* p_destination);
static void flashin0(void);
static void flashin2(unsigned short* p_destination, unsigned short* p_source);
static void flashout2(unsigned short* p_destination);

extern sonic3_ram g_ram;


void clchgctr(void) {
  void(*colchgctr_move_tbl[24][2])(void) = {
    { &colchg0000, &colchg0001 },
    { &colchg0100, &worknai },
    { &colchg03, &colchg03 },
    { &colchg04, &colchg04 },
    { &colchg05, &colchg05 },
    { &colchg0600, &colchg0601 },
    { &worknai, &worknai },
    { &colchg0800, &colchg0801 },
    { &colchg0900, &colchg0901 },
    { &worknai, &worknai },
    { &colchg0b00, &colchg0b01 },
    { &worknai, &worknai },
    { &worknai, &worknai },
    { &worknai, &worknai },
    { &colchg0f, &colchg0f },
    { &worknai, &worknai },
    { &colchg11, &colchg11 },
    { &colchg12, &colchg12 },
    { &worknai, &worknai },
    { &colchg14, &colchg14 },
    { &colchg15, &colchg15 },
    { &colchg1600, &colchg1601 },
    { &worknai, &colchg1601 }
  };

  colchgsuper();
  colchgctr_move_tbl[get_zone(g_ram.stageno)][get_act(g_ram.stageno)]();
}


static void worknai(void) {
}


static void colchg0000(void) {
  if (g_ram.DAT_08fff72e == 0) {
    if (g_ram.clchgtim-- == 0) {
      g_ram.clchgtim = 7;
      memcpy(&g_ram.colorwk[43], col000col[g_ram.clchgcnt], sizeof(col000col[g_ram.clchgcnt]));
      ++g_ram.clchgcnt;
      g_ram.clchgcnt &= 3;
      if (g_ram.clchgtim2 == 0) {
        memcpy(&g_ram.colorwk[60], col003col[g_ram.clchgcnt2], sizeof(col003col[g_ram.clchgcnt2]));
        ++g_ram.clchgcnt2;
        if (g_ram.clchgcnt2 >= 8) {
          g_ram.clchgcnt2 = 0;
        }
      }
    }
  }
  else {
    if (g_ram.clchgtim-- == 0) {
      g_ram.clchgtim = 9;
      memcpy(&g_ram.colorwk[50], col001col[g_ram.clchgcnt], sizeof(col001col[g_ram.clchgcnt]));
      ++g_ram.clchgcnt;
      if (g_ram.clchgcnt >= 16) {
        g_ram.clchgcnt = 0;
      }
      memcpy(&g_ram.colorwk[61], col002col[g_ram.clchgcnt2], sizeof(col002col[g_ram.clchgcnt2]));
      ++g_ram.clchgcnt2;
      if (g_ram.clchgcnt2 >= 16) {
        g_ram.clchgcnt2 = 0;
      }
    }
  }
}


static void colchg0001(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 5;
    memcpy(&g_ram.colorwk[60], col004col[g_ram.clchgcnt], sizeof(col004col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    g_ram.clchgcnt &= 3;
    unsigned short (*p_col)[3] = g_ram.scra_h_posit >> 16 < 0x3800 ? col005col : col006col;
    g_ram.colorwk[36] = p_col[g_ram.clchgcnt2][0];
    g_ram.colorwk[40] = p_col[g_ram.clchgcnt2][1];
    g_ram.colorwk[59] = p_col[g_ram.clchgcnt2][2];
    g_ram.colorwk[46] = g_ram.scra_h_posit >> 16 >= 448 ? 0xA0E : p_col[g_ram.clchgcnt2][2];
    ++g_ram.clchgcnt2;
    if (g_ram.clchgcnt2 >= 8) {
      g_ram.clchgcnt2 = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 1;
    unsigned short* p_col = g_ram.scra_h_posit >> 16 < 0x3800 ? col007col : col008col;
    g_ram.colorwk[49] = p_col[g_ram.clchgcnt3];
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 26) {
      g_ram.clchgcnt3 = 0;
    }
  }
}


static void colchg0100(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 7;
    if (g_ram.clchgtim2 != 0) {
      g_ram.clchgtim = 0;
    }
    memcpy(&g_ram.colorwk[35], col010col[g_ram.clchgcnt], sizeof(col010col[g_ram.clchgcnt]));
    memcpy(&g_ram.colorwk3[35], col010col[g_ram.clchgcnt], sizeof(col010col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 4) {
      g_ram.clchgcnt = 0;
    }
  }
}


static void colchg03(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 3;
    memcpy(&g_ram.colorwk[57], col030col[g_ram.clchgcnt], sizeof(col030col[g_ram.clchgcnt]));
    memcpy(&g_ram.colorwk3[57], col033col[g_ram.clchgcnt], sizeof(col033col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 16) {
      g_ram.clchgcnt = 0;
    }
  }
  memcpy(&g_ram.colorwk[41], col031col[g_ram.clchgcnt2], sizeof(col031col[g_ram.clchgcnt2]));
  memcpy(&g_ram.colorwk3[41], col034col[g_ram.clchgcnt2], sizeof(col034col[g_ram.clchgcnt2]));
  ++g_ram.clchgcnt2;
  if (g_ram.clchgcnt2 >= 16) {
    g_ram.clchgcnt2 = 0;
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 2;
    g_ram.colorwk[39] = col032col[g_ram.clchgcnt3];
    g_ram.colorwk3[39] = col032col[g_ram.clchgcnt3];
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 32) {
      g_ram.clchgcnt3 = 0;
    }
  }
}


static void colchg04(void) {
  if (!(g_ram.gametimer & 0xFF)) {
    g_ram.DAT_08fff7c1 ^= 1;
  }
}


static void colchg05(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 5;
    memcpy(&g_ram.colorwk[46], col050col[g_ram.clchgcnt], sizeof(col050col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 16) {
      g_ram.clchgcnt = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 9;
    if (g_ram.DAT_08ffeee8 != 0) {
      memcpy(&g_ram.colorwk[62], col051col[g_ram.clchgcnt2], sizeof(col051col[g_ram.clchgcnt2]));
    }
    ++g_ram.clchgcnt2;
    if (g_ram.clchgcnt2 >= 18) {
      g_ram.clchgcnt2 = 0;
    }
  }
  if (g_ram.clchgtim4-- == 0) {
    g_ram.clchgtim4 = 7;
    if (g_ram.DAT_08ffeee8 != 0) {
      memcpy(&g_ram.colorwk[60], col052col[g_ram.clchgcnt3], sizeof(col052col[g_ram.clchgcnt3]));
    }
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 6) {
      g_ram.clchgcnt3 = 0;
    }
    memcpy(&g_ram.colorwk[44], col053col[g_ram.clchgcnt4], sizeof(col053col[g_ram.clchgcnt4]));
    ++g_ram.clchgcnt4;
    if (g_ram.clchgcnt4 >= 16) {
      g_ram.clchgcnt4 = 0;
    }
  }
}


static void colchg0600(void) {
  colchg06(col060col);
}


static void colchg0601(void) {
  colchg06(col061col);
}


static void colchg06(unsigned short (*p_col)[3]) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 3;
    memcpy(&g_ram.colorwk[40], p_col[g_ram.clchgcnt], sizeof(p_col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 3) {
      g_ram.clchgcnt = 0;
    }
  }
}


static void colchg0800(void) {
  if (g_ram.clchgtim4-- == 0) {
    g_ram.clchgtim4 = 5;
    memcpy(&g_ram.colorwk[44], col080col[0][g_ram.clchgcnt3], sizeof(col080col[0][g_ram.clchgcnt3]));
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 4) {
      g_ram.clchgcnt3 = 0;
    }
  }
}


static void colchg0801(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 899;
    if (g_ram.soz_darkness_level < 5) {
      ++g_ram.soz_darkness_level;
      if (!(g_ram.soz_darkness_level & 1)) {
        g_ram.clchgtim2 = 3;
        g_ram.clchgtim3 = 0;
      }
    }
  }
  bool clchgtim3_change = g_ram.clchgtim2 != 1 && g_ram.clchgtim3-- == 0;
  if (clchgtim3_change) {
    g_ram.clchgtim3 = 3;
    if (g_ram.clchgtim2 > 0) {
      --g_ram.clchgtim2;
      ++g_ram.clchgcnt2;
      ++g_ram.clchgcnt4;
    }
    else {
      ++g_ram.clchgtim2;
      --g_ram.clchgcnt2;
      --g_ram.clchgcnt4;
    }
    memcpy(&g_ram.colorwk[33], col081col[g_ram.clchgcnt2][0], sizeof(unsigned short) * 11);
    memcpy(&g_ram.colorwk[49], col081col[g_ram.clchgcnt2][1], sizeof(unsigned short) * 15);
  }
  unsigned short clchgcnt3 = g_ram.clchgcnt3;
  bool clchgtim4_change = g_ram.clchgtim4-- == 0;
  if (clchgtim4_change) {
    g_ram.clchgtim4 = 5;
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 4) {
      g_ram.clchgcnt3 = 0;
    }
  }
  if (clchgtim4_change || clchgtim3_change) {
    memcpy(&g_ram.colorwk[44], col080col[g_ram.clchgcnt4][clchgcnt3], sizeof(unsigned short) * 4);
  }
}


static void colchg0900(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 15;
    memcpy(&g_ram.colorwk[33], col090col[g_ram.clchgcnt], sizeof(col090col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 16) {
      g_ram.clchgcnt = 0;
    }
    memcpy(&g_ram.colorwk[49], col091col[g_ram.clchgcnt2], sizeof(col091col[g_ram.clchgcnt2]));
    ++g_ram.clchgcnt2;
    if (g_ram.clchgcnt2 >= 9) { // originally 7?
      g_ram.clchgcnt2 = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 7;
    g_ram.colorwk[43] = col092col[g_ram.clchgcnt3];
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 17) {
      g_ram.clchgcnt3 = 0;
    }
  }
}


static void colchg0901(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 15;
    memcpy(&g_ram.colorwk[33], col090col[g_ram.clchgcnt], sizeof(col090col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 16) {
      g_ram.clchgcnt = 0;
    }
    memcpy(&g_ram.colorwk[49], col091col[g_ram.clchgcnt2], sizeof(col091col[g_ram.clchgcnt2]));
    ++g_ram.clchgcnt2;
    if (g_ram.clchgcnt2 >= 9) { // originally 7?
      g_ram.clchgcnt2 = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 15;
    memcpy(&g_ram.colorwk[59], col093col[g_ram.clchgcnt3], sizeof(col093col[g_ram.clchgcnt3]));
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 32) {
      g_ram.clchgcnt3 = 0;
    }
  }
}


static void colchg0b00(void) {
  if (g_ram.clchgtim4-- == 0) {
    g_ram.clchgtim4 = 15;
    memcpy(&g_ram.colorwk[60], col0b2col[g_ram.clchgcnt3], sizeof(col0b2col[g_ram.clchgcnt3]));
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 6) {
      g_ram.clchgcnt3 = 0;
    }
  }
  colchg0b01();
}


static void colchg0b01(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 4;
    memcpy(&g_ram.colorwk[45], col0b0col[g_ram.clchgcnt], sizeof(col0b0col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 12) {
      g_ram.clchgcnt = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 19;
    memcpy(&g_ram.colorwk[40], col0b1col[g_ram.clchgcnt2], sizeof(col0b1col[g_ram.clchgcnt2]));
    ++g_ram.clchgcnt2;
    if (g_ram.clchgcnt2 >= 4) {
      g_ram.clchgcnt2 = 0;
    }
  }
}


static void colchg0f(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 7;
    memcpy(&g_ram.colorwk[45], col0f0col[g_ram.clchgcnt], sizeof(col0f0col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 3) {
      g_ram.clchgcnt = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 17;
    memcpy(&g_ram.colorwk[50], col0f1col[g_ram.clchgcnt2], sizeof(col0f1col[g_ram.clchgcnt2]));
    ++g_ram.clchgcnt2;
    if (g_ram.clchgcnt2 >= 21) {
      g_ram.clchgcnt2 = 0;
    }
  }
}


static void colchg11(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 9;
    memcpy(&g_ram.colorwk[34], col110col[g_ram.clchgcnt], sizeof(col110col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 10) {
      g_ram.clchgcnt = 0;
    }
  }
}


static void colchg12(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.colorwk[46] = col120col[g_ram.clchgcnt];// originally g_ram.clchgcnt + 4?
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 30) {
      g_ram.clchgcnt = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 31;
    memcpy(&g_ram.colorwk[57], col121col[g_ram.clchgcnt2], sizeof(col121col[g_ram.clchgcnt2]));
    ++g_ram.clchgcnt2;
    if (g_ram.clchgcnt2 >= 14) { // originally 13?
      g_ram.clchgcnt2 = 0;
    }
  }
}


static void colchg14(void) {
  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 0;
    memcpy(&g_ram.colorwk[56], DAT_08ff7800[g_ram.clchgcnt], sizeof(DAT_08ff7800[g_ram.clchgcnt]));
    g_ram.clchgcnt += 7;
    if (g_ram.clchgcnt >= 126) {
      g_ram.clchgcnt = 0;
    }
  }
  if (g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 3;
    memcpy(&g_ram.colorwk[33], DAT_08ff78fc[g_ram.clchgcnt2 + 40], sizeof(unsigned short) * 3);
    memcpy(&g_ram.colorwk[36], DAT_08ff78fc[g_ram.clchgcnt2 + 20], sizeof(unsigned short) * 3);
    memcpy(&g_ram.colorwk[39], DAT_08ff78fc[g_ram.clchgcnt2], sizeof(unsigned short) * 3);
    g_ram.clchgcnt2 += 5;
    if (g_ram.clchgcnt2 >= 500) {
      g_ram.clchgcnt2 = 0;
    }
  }
}


static void colchg15(void) {
  if (g_ram.clchgtim2 == 0xFF) return;

  if (g_ram.clchgtim2 == 0) {
    if (g_ram.clchgtim-- == 0) {
      g_ram.clchgtim = 3;
      memcpy(&g_ram.colorwk[42], col150col[g_ram.clchgcnt], sizeof(col150col[g_ram.clchgcnt]));
      g_ram.colorwk[46] = 0xE02;
      g_ram.colorwk[62] = 0xE02;
      ++g_ram.clchgcnt;
      if (g_ram.clchgcnt >= 8) {
        g_ram.clchgcnt = 0;
      }
    }
  }
  else {
    if (g_ram.clchgtim3-- == 0) {
      g_ram.clchgtim3 = 0;
      memcpy(&g_ram.colorwk[42], col151col[g_ram.clchgcnt2], sizeof(col151col[g_ram.clchgcnt2]));
      ++g_ram.clchgcnt2;
      if (g_ram.clchgcnt2 >= 16) { // originally 15?
        g_ram.clchgcnt2 = 0;
      }
      g_ram.colorwk[46] = col152col[g_ram.clchgcnt3];
      g_ram.colorwk[62] = col152col[g_ram.clchgcnt3];
      ++g_ram.clchgcnt3;
      if (g_ram.clchgcnt3 >= 6) {
        g_ram.clchgcnt3 = 0;
      }
    }
  }
}


static void colchg1600(void) {
  if (g_ram.clchgtim2 == 0xFF) return;

  if (g_ram.clchgtim-- == 0) {
    g_ram.clchgtim = 15;
    memcpy(&g_ram.colorwk[33], col090col[g_ram.clchgcnt], sizeof(col090col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 16) {
      g_ram.clchgcnt = 0;
    }
  }
  if (g_ram.clchgtim2 != 0 && g_ram.clchgtim3-- == 0) {
    g_ram.clchgtim3 = 7;
    memcpy(&g_ram.colorwk[60], col16000col[g_ram.clchgcnt3], sizeof(col16000col[g_ram.clchgcnt3]));
    ++g_ram.clchgcnt3;
    if (g_ram.clchgcnt3 >= 15) {
      g_ram.clchgcnt3 = 0;
    }
  }
}


static void colchg1601(void) {
  if (g_ram.clchgtim2 != 0) return;

  if (g_ram.clchgtim-- == 0) {
    memcpy(&g_ram.colorwk[49], col16010col[g_ram.clchgcnt], sizeof(col16010col[g_ram.clchgcnt]));
    ++g_ram.clchgcnt;
    if (g_ram.clchgcnt >= 10) {
      g_ram.clchgcnt = 0;
    }
  }
}


static unsigned short col000col[4][4] = {
  { 0xEE8, 0xEE2, 0xEA4, 0xE64 },
  { 0xEE2, 0xEA4, 0xE64, 0xEE8 },
  { 0xEA4, 0xE64, 0xEE8, 0xEE2 },
  { 0xE64, 0xEE8, 0xEE2, 0xEA4 }
};


static unsigned short col001col[16][4] = {
  { 0xEEC, 0xEEE, 0xEE8, 0xE40 },
  { 0xEEC, 0xEE8, 0xEE8, 0xEEE },
  { 0xEEA, 0xE86, 0xEE8, 0xEE8 },
  { 0xEE8, 0xE40, 0xEE8, 0xE86 },
  { 0xEE6, 0xEEE, 0xEE8, 0xE40 },
  { 0xEEA, 0xEE8, 0xEE8, 0xEEE },
  { 0xEE8, 0xE86, 0xEE8, 0xEE8 },
  { 0xEE8, 0xE40, 0xEE8, 0xE86 },
  { 0xEE6, 0xEEE, 0xEE8, 0xE40 },
  { 0xEE8, 0xEE8, 0xEE8, 0xEEE },
  { 0xEEA, 0xE86, 0xEE8, 0xEE8 },
  { 0xEEC, 0xE40, 0xEE8, 0xE86 },
  { 0xEEC, 0xEEE, 0xEE8, 0xE40 },
  { 0xEEC, 0xEE8, 0xEE8, 0xEEE },
  { 0xEEC, 0xE86, 0xEE8, 0xEE8 },
  { 0xEEC, 0xE40, 0xEE8, 0xE86 }
};


static unsigned short col002col[16][3] = {
  { 0xCEC, 0xCEE, 0xEEE },
  { 0xCEE, 0xEEE, 0xEEE },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xEE8, 0xEEE, 0xEEE },
  { 0xEE8, 0xEE8, 0xEEE },
  { 0xEE8, 0xEE8, 0xEE8 },
  { 0xEE8, 0xEE8, 0xEE8 },
  { 0xEE8, 0xEE8, 0xEE8 },
  { 0xEE8, 0xEE8, 0xEE8 },
  { 0xEE8, 0xEE8, 0xAEC },
  { 0xEE8, 0xAEC, 0xCEC },
  { 0xAEC, 0xCEC, 0xCEC }
};


static unsigned short col003col[8][3] = {
  { 0xEA4, 0xE60, 0xEE2 },
  { 0xEA4, 0xEE8, 0xEA4 },
  { 0xE60, 0xEE8, 0xEEE },
  { 0xE60, 0xEE2, 0xEE2 },
  { 0xEE8, 0xEA4, 0xEA4 },
  { 0xEE2, 0xE60, 0xE60 },
  { 0xEE2, 0xE60, 0xEEE },
  { 0xEE2, 0xE60, 0xEE8 }
};


static unsigned short col004col[4][4] = {
  { 0xEE8, 0xEE2, 0xEC4, 0xEA4 },
  { 0xEE2, 0xEC4, 0xEA4, 0xEE8 },
  { 0xEC4, 0xEA4, 0xEE8, 0xEE2 },
  { 0xEA4, 0xEE8, 0xEE2, 0xEC4 }
};


static unsigned short col005col[8][3] = {
  { 0x024, 0x044, 0x08E },
  { 0x026, 0x046, 0x0AE },
  { 0x024, 0x048, 0x08E },
  { 0x026, 0x04A, 0x0AE },
  { 0x024, 0x04C, 0x08E },
  { 0x026, 0x04A, 0x0AE },
  { 0x024, 0x048, 0x08E },
  { 0x024, 0x046, 0x08E }
};


static unsigned short col006col[8][3] = {
  { 0x024, 0x044, 0x00C },
  { 0x026, 0x046, 0x00E },
  { 0x024, 0x048, 0x00C },
  { 0x026, 0x04A, 0x00E },
  { 0x024, 0x04C, 0x00C },
  { 0x026, 0x04A, 0x00E },
  { 0x024, 0x048, 0x00C },
  { 0x024, 0x046, 0x00C }
};


static unsigned short col007col[26] = {
  0x06E, 0x06E, 0x06E, 0x06E, 0x28E, 0x4AE, 0x6AE, 0x8CE, 0x8EE, 0xAEE, 0xAEE, 0xAEE, 0xAEE, 0xAEE, 0x8EE, 0x8EE,
  0x8EE, 0x8EE, 0x8CE, 0x8CE, 0x8CE, 0x6AE, 0x6AE, 0x4AE, 0x4AE, 0x28E
};


static unsigned short col008col[26] = {
  0x00C, 0x00C, 0x00C, 0x00C, 0x02C, 0x00E, 0x02E, 0x04E, 0x06E, 0x08E, 0x08E, 0x08E, 0x08E, 0x08E, 0x06E, 0x04E,
  0x04E, 0x04E, 0x02E, 0x02E, 0x02E, 0x00E, 0x00E, 0x02C, 0x02C, 0x02C
};


static unsigned short col010col[4][4] = {
  { 0xEC8, 0xEC0, 0xEA0, 0xE80 },
  { 0xEC0, 0xEA0, 0xE80, 0xEC8 },
  { 0xEA0, 0xE80, 0xEC8, 0xEC0 },
  { 0xE80, 0xEC8, 0xEC0, 0xEA0 }
};


static unsigned short col030col[16][3] = {
  { 0x000, 0x066, 0x0EE },
  { 0x022, 0x044, 0x0CC },
  { 0x044, 0x022, 0x0AA },
  { 0x066, 0x000, 0x088 },
  { 0x088, 0x000, 0x066 },
  { 0x0AA, 0x022, 0x044 },
  { 0x0CC, 0x044, 0x022 },
  { 0x0EE, 0x066, 0x000 },
  { 0x0EE, 0x088, 0x000 },
  { 0x0CC, 0x0AA, 0x022 },
  { 0x0AA, 0x0CC, 0x044 },
  { 0x088, 0x0EE, 0x066 },
  { 0x066, 0x0EE, 0x088 },
  { 0x044, 0x0CC, 0x0AA },
  { 0x022, 0x0AA, 0x0CC },
  { 0x000, 0x088, 0x0EE }
};


static unsigned short col031col[30][3] = {
  { 0xE20, 0x08A, 0xC0E },
  { 0xC42, 0x06C, 0xE0E },
  { 0xA64, 0x04C, 0xE0C },
  { 0x884, 0x02E, 0xE0A },
  { 0x6A6, 0x00E, 0xE08 },
  { 0x4C6, 0x20E, 0xE06 },
  { 0x2E8, 0x40E, 0xE04 },
  { 0x0E8, 0x60E, 0xE02 },
  { 0x0C8, 0x80E, 0xE00 },
  { 0x0AA, 0xA0E, 0xE00 },
  { 0x08A, 0xC0E, 0xE20 },
  { 0x06C, 0xE0E, 0xC42 },
  { 0x04C, 0xE0C, 0xA64 },
  { 0x02E, 0xE0A, 0x884 },
  { 0x00E, 0xE08, 0x6A6 },
  { 0x20E, 0xE06, 0x4C6 },
  { 0x40E, 0xE04, 0x2E8 },
  { 0x60E, 0xE02, 0x0E8 },
  { 0x80E, 0xE00, 0x0C8 },
  { 0xA0E, 0xE00, 0x0AA },
  { 0xC0E, 0xE20, 0x08A },
  { 0xE0E, 0xC42, 0x06C },
  { 0xE0C, 0xA64, 0x04C },
  { 0xE0A, 0x884, 0x02E },
  { 0xE08, 0x6A6, 0x00E },
  { 0xE06, 0x4C6, 0x20E },
  { 0xE04, 0x2E8, 0x40E },
  { 0xE02, 0x0E8, 0x60E },
  { 0xE00, 0x0C8, 0x80E },
  { 0xE00, 0x0AA, 0xA0E }
};


static unsigned short col032col[32] = {
  0x2E0, 0xECE, 0x4E2, 0xEAC, 0x6E4, 0xE8A, 0x8E6, 0xE68, 0xAE8, 0xE46, 0xCEA, 0xE24, 0xEEC, 0xE02, 0xEEE, 0xE00,
  0xEEC, 0xE02, 0xCEA, 0xE24, 0xAE8, 0xE46, 0x8E6, 0xE68, 0x6E4, 0xE8A, 0x4E2, 0xEAC, 0x2E0, 0xECE, 0x0E0, 0xEEE
};

static unsigned short col033col[16][3] = {
  { 0x800, 0x800, 0x886 },
  { 0x800, 0x800, 0x864 },
  { 0x800, 0x800, 0x842 },
  { 0x800, 0x800, 0x820 },
  { 0x820, 0x800, 0x800 },
  { 0x842, 0x800, 0x800 },
  { 0x864, 0x800, 0x800 },
  { 0x886, 0x800, 0x800 },
  { 0x886, 0x820, 0x800 },
  { 0x864, 0x842, 0x800 },
  { 0x842, 0x864, 0x800 },
  { 0x820, 0x886, 0x800 },
  { 0x800, 0x886, 0x820 },
  { 0x800, 0x864, 0x842 },
  { 0x800, 0x842, 0x864 },
  { 0x800, 0x820, 0x886 }
};


static unsigned short col034col[30][3] = {
  { 0xE20, 0xE8A, 0xE0A },
  { 0xE42, 0xE6A, 0xE0A },
  { 0xE64, 0xE4A, 0xE0A },
  { 0xE84, 0xE2A, 0xE0A },
  { 0xEA6, 0xE0A, 0xE08 },
  { 0xEC6, 0xE0A, 0xE06 },
  { 0xEE8, 0xE0A, 0xE04 },
  { 0xEE8, 0xE0A, 0xE02 },
  { 0xEC8, 0xE0A, 0xE00 },
  { 0xEAA, 0xE0A, 0xE00 },
  { 0xE8A, 0xE0A, 0xE20 },
  { 0xE6A, 0xE0A, 0xC42 },
  { 0xE4A, 0xE0A, 0xE64 },
  { 0xE2A, 0xE0A, 0xE84 },
  { 0xE0A, 0xE08, 0xEA6 },
  { 0xE0A, 0xE06, 0xEC6 },
  { 0xE0A, 0xE04, 0xEE8 },
  { 0xE0A, 0xE02, 0xEE8 },
  { 0xE0A, 0xE00, 0xEC8 },
  { 0xE0A, 0xE00, 0xEAA },
  { 0xE0A, 0xE20, 0xE8A },
  { 0xE0A, 0xE42, 0xE6A },
  { 0xE0A, 0xE64, 0xE4A },
  { 0xE0A, 0xE84, 0xE2A },
  { 0xE08, 0xEA6, 0xE0A },
  { 0xE06, 0xEC6, 0xE0A },
  { 0xE04, 0xEE8, 0xE0A },
  { 0xE02, 0xEE8, 0xE0A },
  { 0xE00, 0xEC8, 0xE0A },
  { 0xE00, 0xEAA, 0xE0A }
};


static unsigned short col050col[16][2] = {
  { 0xE62, 0xE20 },
  { 0xE44, 0xE20 },
  { 0xE44, 0xE00 },
  { 0xE42, 0xE00 },
  { 0xE62, 0xC00 },
  { 0xE82, 0xA00 },
  { 0xEA2, 0xC00 },
  { 0xEC0, 0xE00 },
  { 0xEE0, 0xE20 },
  { 0xEE4, 0xE00 },
  { 0xEE4, 0xC00 },
  { 0xEE4, 0xA00 },
  { 0xEE0, 0x800 },
  { 0xEC2, 0xA00 },
  { 0xEA2, 0xC00 },
  { 0xE82, 0xE20 }
};


static unsigned short col051col[18][2] = {
  { 0xE06, 0xE08 },
  { 0xE04, 0xE06 },
  { 0xC04, 0xE04 },
  { 0xC02, 0xC04 },
  { 0xA02, 0xC02 },
  { 0xA00, 0xA02 },
  { 0x800, 0xA00 },
  { 0x600, 0x800 },
  { 0x600, 0x800 },
  { 0x600, 0x800 },
  { 0x600, 0x800 },
  { 0x800, 0xA00 },
  { 0xA00, 0xA02 },
  { 0xA02, 0xC02 },
  { 0xC02, 0xC04 },
  { 0xC04, 0xE04 },
  { 0xE04, 0xE06 },
  { 0xE06, 0xE08 }
};


static unsigned short col052col[6][2] = {
  { 0x840, 0xEEA },
  { 0x860, 0xEE0 },
  { 0xA80, 0xEC0 },
  { 0xEC0, 0xA80 },
  { 0xA80, 0xEC0 },
  { 0x860, 0xEE0 }
};


static unsigned short col053col[16][2] = {
  { 0x0E8, 0xCEC },
  { 0x0C8, 0xAEA },
  { 0x0C8, 0xAEA },
  { 0x0A6, 0x6E8 },
  { 0x0A6, 0x6E8 },
  { 0x084, 0x0E8 },
  { 0x084, 0x0E8 },
  { 0x082, 0x0C8 },
  { 0x064, 0x0A6 },
  { 0x064, 0x0A6 },
  { 0x082, 0x0C8 },
  { 0x084, 0x0E8 },
  { 0x0A6, 0x6E8 },
  { 0x0C8, 0xAEA },
  { 0x0E8, 0xCEC },
  { 0x0E8, 0xCEC }
};


static unsigned short col060col[3][3] = {
  { 0x8E0, 0x0C0, 0x080 },
  { 0x0C0, 0x080, 0x8E0 },
  { 0x080, 0x8E0, 0x0C0 }
};


static unsigned short col061col[3][3] = {
  { 0xEEA, 0xEA4, 0xC62 },
  { 0xEA4, 0xC62, 0xEEA },
  { 0xC62, 0xEEA, 0xEA4 }
};


static unsigned short col080col[5][4][4] = {
  {
    { 0x2CE, 0x6CE, 0x0AE, 0x06C },
    { 0x06C, 0x2CE, 0x6CE, 0x0AE },
    { 0x0AE, 0x06C, 0x2CE, 0x6CE },
    { 0x6CE, 0x0AE, 0x06C, 0x2CE }
  },{
    { 0x28A, 0x6AC, 0x08A, 0x048 },
    { 0x048, 0x28A, 0x6AC, 0x08A },
    { 0x08A, 0x048, 0x28A, 0x6AC },
    { 0x6AC, 0x08A, 0x048, 0x28A }
  },{
    { 0x468, 0x668, 0x248, 0x026 },
    { 0x026, 0x468, 0x668, 0x248 },
    { 0x248, 0x026, 0x468, 0x668 },
    { 0x668, 0x248, 0x026, 0x468 }
  },{
    { 0x424, 0x846, 0x224, 0x222 },
    { 0x222, 0x424, 0x846, 0x224 },
    { 0x224, 0x222, 0x424, 0x846 },
    { 0x846, 0x224, 0x222, 0x424 }
  },{
    { 0x602, 0x824, 0x402, 0x200 },
    { 0x200, 0x602, 0x824, 0x402 },
    { 0x402, 0x200, 0x602, 0x824 },
    { 0x824, 0x402, 0x200, 0x602 }
  }
};


static unsigned short col081col_0_0[11] = {
  0xEEE, 0x8EE, 0x4EE, 0x0CE, 0x24C, 0x006, 0x000, 0xCEA, 0x886, 0x424, 0x0E0
};
static unsigned short col081col_0_1[15] = {
  0xEEE, 0xAEE, 0x6EE, 0x4AC, 0x068, 0x046, 0x022, 0x8AA, 0x468, 0x224, 0x002, 0x28E, 0x4EE, 0x08C, 0x00C
};


static unsigned short col081col_1_0[11] = {
  0x8CE, 0x6CC, 0x4AC, 0x08A, 0x248, 0x004, 0x000, 0x8A8, 0x664, 0x422, 0x080
};
static unsigned short col081col_1_1[15] = {
  0xCEE, 0xACC, 0x6CC, 0x48A, 0x266, 0x046, 0x022, 0xACC, 0x468, 0x224, 0x002, 0x28E, 0x6EE, 0x28C, 0x22C
};


static unsigned short col081col_2_0[11] = {
  0x2CE, 0x28A, 0x268, 0x246, 0x224, 0x202, 0x000, 0x464, 0x222, 0x200, 0x040
};
static unsigned short col081col_2_1[15] = {
  0xACE, 0x8AA, 0x688, 0x468, 0x244, 0x024, 0x022, 0xCCC, 0x468, 0x224, 0x002, 0x26C, 0x6EE, 0x28C, 0x24C
};


static unsigned short col081col_3_0[11] = {
  0x88A, 0x668, 0x646, 0x424, 0x224, 0x202, 0x000, 0x444, 0x222, 0x200, 0x040
};
static unsigned short col081col_3_1[15] = {
  0x8CE, 0x888, 0x666, 0x446, 0x222, 0x022, 0x022, 0xEEE, 0x468, 0x224, 0x002, 0x26A, 0x6EE, 0x48C, 0x26C
};


static unsigned short col081col_4_0[11] = {
  0xC46, 0x824, 0x804, 0x402, 0x202, 0x200, 0x000, 0x422, 0x402, 0x200, 0x040
};
static unsigned short col081col_4_1[15] = {
  0x6AE, 0x664, 0x422, 0x402, 0x200, 0x000, 0x000, 0xEEE, 0x466, 0x224, 0x000, 0x046, 0x6EE, 0x48C, 0x26A
};

static unsigned short* col081col[5][2] = {
  { col081col_0_0, col081col_0_1 },
  { col081col_1_0, col081col_1_1 },
  { col081col_2_0, col081col_2_1 },
  { col081col_3_0, col081col_3_1 },
  { col081col_4_0, col081col_4_1 }
};


static unsigned short col090col[16][4] = {
  { 0x0EE, 0x0AE, 0x06E, 0x00E },
  { 0x0AE, 0x06E, 0x00E, 0x0EE },
  { 0x06E, 0x00E, 0x0EE, 0x2CE },
  { 0x02E, 0x8EE, 0x4EE, 0x06E },
  { 0xAEE, 0x6EE, 0x08E, 0x04E },
  { 0x4EE, 0x06E, 0x02E, 0x8EE },
  { 0x06E, 0x00E, 0x0EE, 0x2CE },
  { 0x00E, 0x0EE, 0x2CE, 0x06E },
  { 0x0EE, 0x0AE, 0x06E, 0x00E },
  { 0x08E, 0x04E, 0x00C, 0x0CE },
  { 0x02E, 0x00A, 0x0AC, 0x06E },
  { 0x008, 0x08E, 0x04C, 0x00C },
  { 0x0AC, 0x06E, 0x02E, 0x00A },
  { 0x08E, 0x04E, 0x00C, 0x0CE },
  { 0x06E, 0x00E, 0x0EE, 0x0AE },
  { 0x00E, 0x0EE, 0x0AE, 0x06E }
};

static unsigned short col091col[9][2] = {
  { 0x224, 0x224 },
  { 0x224, 0x424 },
  { 0x224, 0x426 },
  { 0x426, 0x224 },
  { 0x424, 0x224 },
  { 0x224, 0x224 },
  { 0x224, 0x224 },
  { 0x224, 0x422 },
  { 0x422, 0x422 }
};


static unsigned short col092col[17] = {
  0x624, 0x624, 0x624, 0x624, 0x624, 0x624, 0x626, 0x626, 0x826, 0x826, 0x826, 0x826, 0x826, 0x826, 0x826, 0x626,
  0x626
};


static unsigned short col093col[32][4] = {
  { 0x824, 0xC44, 0xE2A, 0xEAE },
  { 0x824, 0xC44, 0xE2A, 0xEAE },
  { 0x824, 0xC44, 0xE2A, 0xEAE },
  { 0x824, 0xC44, 0xE48, 0xEAC },
  { 0x822, 0xC44, 0xE66, 0xEAA },
  { 0x822, 0xC44, 0xE66, 0xEAA },
  { 0x822, 0xC44, 0xE66, 0xEAA },
  { 0x842, 0xC64, 0xEA4, 0xEC6 },
  { 0x642, 0xA82, 0xCC2, 0xEE0 },
  { 0x642, 0xA82, 0xCC2, 0xEE0 },
  { 0x642, 0xA82, 0xCC2, 0xEE0 },
  { 0x642, 0x882, 0xAC2, 0xCE0 },
  { 0x642, 0x682, 0x8C2, 0x8E0 },
  { 0x642, 0x682, 0x8C2, 0x8E0 },
  { 0x642, 0x682, 0x8C2, 0x8E0 },
  { 0x642, 0x486, 0x4C8, 0x4E8 },
  { 0x442, 0x288, 0x2CA, 0x2EC },
  { 0x442, 0x288, 0x2CC, 0x2EE },
  { 0x442, 0x288, 0x2CA, 0x2EC },
  { 0x642, 0x486, 0x4C8, 0x4E8 },
  { 0x642, 0x682, 0x8C2, 0x8E0 },
  { 0x642, 0x882, 0xAC2, 0xCE0 },
  { 0x642, 0xA82, 0xCC2, 0xEE0 },
  { 0x842, 0xC64, 0xEA4, 0xEC6 },
  { 0x822, 0xC44, 0xE66, 0xEAA },
  { 0x824, 0xC44, 0xE48, 0xEAC },
  { 0x824, 0xC44, 0xE2A, 0xEAE },
  { 0x826, 0xC46, 0xE4A, 0xE8E },
  { 0x624, 0xA48, 0xC6C, 0xE6E },
  { 0x624, 0xA48, 0xC6C, 0xE6E },
  { 0x624, 0xA48, 0xC6C, 0xE6E },
  { 0x826, 0xC46, 0xE4A, 0xE8E }
};


static unsigned short col0b0col[12][2] = {
  { 0x0E0, 0x000 },
  { 0x000, 0xE0E },
  { 0xE00, 0x000 },
  { 0x000, 0x0EE },
  { 0x00E, 0x000 },
  { 0x000, 0xEE0 },
  { 0xEE0, 0x000 },
  { 0x000, 0x00E },
  { 0x0EE, 0x000 },
  { 0x000, 0xE00 },
  { 0xE0E, 0x000 },
  { 0x000, 0x0E0 }
};


static unsigned short col0b1col[4][5] = {
  { 0x08E, 0x06C, 0x04A, 0x028, 0x6AE },
  { 0x28C, 0x26A, 0x04A, 0x226, 0x4AC },
  { 0x48A, 0x468, 0x248, 0x424, 0x4AA },
  { 0x28C, 0x26A, 0x04A, 0x226, 0x4AC }
};


static unsigned short col0b2col[6][4] = {
  { 0x8AC, 0x68A, 0x468, 0x246 },
  { 0x246, 0x8AC, 0x68A, 0x468 },
  { 0x468, 0x246, 0x8AC, 0x68A },
  { 0x68A, 0x468, 0x246, 0x8AC },
  { 0x468, 0x246, 0x8AC, 0x68A },
  { 0x246, 0x8AC, 0x68A, 0x468 }
};


static unsigned short col0f0col[3][3] = {
  { 0x0EE, 0x0AE, 0x06C },
  { 0x0AE, 0x06E, 0x0EE },
  { 0x06E, 0x0EE, 0x0AE }
};


static unsigned short col0f1col[21][3] = {
  { 0xEE0, 0xE0E, 0x0EE },
  { 0xEA0, 0xA0E, 0x0EA },
  { 0xE60, 0x60E, 0x0E6 },
  { 0xE20, 0x20E, 0x0E2 },
  { 0xE02, 0x02E, 0x2E0 },
  { 0xE06, 0x06E, 0x6E0 },
  { 0xE0A, 0x0AE, 0xAE0 },
  { 0xE0E, 0x0EE, 0xEE0 },
  { 0xA0E, 0x0EA, 0xEA0 },
  { 0x60E, 0x0E6, 0xE60 },
  { 0x20E, 0x0E2, 0xE20 },
  { 0x02E, 0x2E0, 0xE02 },
  { 0x06E, 0x6E0, 0xE06 },
  { 0x0AE, 0xAE0, 0xE0A },
  { 0x0EE, 0xEE0, 0xE0E },
  { 0x0EA, 0xEA0, 0xA0E },
  { 0x0E6, 0xE60, 0x60E },
  { 0x0E2, 0xE20, 0x20E },
  { 0x2E0, 0xE02, 0x02E },
  { 0x6E0, 0xE06, 0x06E },
  { 0xAE0, 0xE0A, 0x0AE }
};


static unsigned short col110col[10][4] = {
  { 0x00E, 0x008, 0x004, 0xEEE },
  { 0x00C, 0x006, 0x002, 0xCCE },
  { 0x00A, 0x004, 0x000, 0xAAE },
  { 0x008, 0x002, 0x000, 0x88E },
  { 0x006, 0x000, 0x000, 0x66E },
  { 0x004, 0x000, 0x000, 0x44E },
  { 0x006, 0x000, 0x000, 0x66E },
  { 0x008, 0x002, 0x000, 0x88E },
  { 0x00A, 0x004, 0x002, 0xAAE },
  { 0x00C, 0x006, 0x004, 0xCCE }
};


static unsigned short col120col[30] = {
  0x006, 0x008, 0x00A, 0x00C, 0x00E, 0x00E, 0x00E, 0x00E, 0x00C, 0x00A, 0x008, 0x006, 0x006, 0x006, 0x006, 0x008,
  0x00A, 0x00C, 0x00E, 0x00E, 0x00E, 0x00C, 0x00A, 0x008, 0x006, 0x008, 0x00A, 0x00A, 0x00A, 0x008
};


static unsigned short col121col[14][2] = {
  { 0x000, 0x00E },
  { 0x002, 0x00C },
  { 0x004, 0x00A },
  { 0x006, 0x008 },
  { 0x008, 0x006 },
  { 0x00A, 0x004 },
  { 0x00C, 0x002 },
  { 0x00E, 0x000 },
  { 0x00C, 0x002 },
  { 0x00A, 0x004 },
  { 0x008, 0x006 },
  { 0x006, 0x008 },
  { 0x004, 0x00A },
  { 0x002, 0x00C }
};


static unsigned short col150col[8][4] = {
  { 0x046, 0x488, 0x2EE, 0x08A },
  { 0x068, 0x26A, 0xEEE, 0x0AC },
  { 0x08A, 0x046, 0x488, 0x2EE },
  { 0x0AC, 0x068, 0x26A, 0xEEE },
  { 0x2EE, 0x08A, 0x046, 0x488 },
  { 0xEEE, 0x0AC, 0x068, 0x26A },
  { 0x48A, 0x2EE, 0x08A, 0x046 },
  { 0x268, 0xEEE, 0x0AC, 0x068 }
};


static unsigned short col151col[16][4] = {
  { 0x268, 0xEEE, 0x0AC, 0x068 },
  { 0xEEE, 0xEEE, 0xEEE, 0xEEE },
  { 0x48A, 0x2EE, 0x08A, 0x046 },
  { 0x0EE, 0x0EE, 0x0EE, 0x0EE },
  { 0xEEE, 0x0AC, 0x068, 0x26A },
  { 0xEEE, 0xEEE, 0xEEE, 0xEEE },
  { 0x2EE, 0x08A, 0x046, 0x488 },
  { 0xE0E, 0xE0E, 0xE0E, 0xE0E },
  { 0x0AC, 0x068, 0x26A, 0xEEE },
  { 0xEEE, 0xEEE, 0xEEE, 0xEEE },
  { 0x08A, 0x046, 0x488, 0x2EE },
  { 0xEE0, 0xEE0, 0xEE0, 0xEE0 },
  { 0x068, 0x26A, 0xEEE, 0x0AC },
  { 0xEEE, 0xEEE, 0xEEE, 0xEEE },
  { 0x046, 0x488, 0x2EE, 0x08A },
  { 0x0E0, 0x0E0, 0x0E0, 0x0E0 }
};


static unsigned short col152col[6] = {
  0xE02, 0xE24, 0xE46, 0xE68, 0xE8A, 0xEAC
};


static unsigned short col16000col[15][2] = {
  { 0x424, 0x0AE },
  { 0x424, 0x0AE },
  { 0x424, 0x0AE },
  { 0x426, 0x08E },
  { 0x428, 0x06E },
  { 0x42A, 0x04E },
  { 0x42C, 0x02E },
  { 0x42E, 0x00E },
  { 0x42E, 0x00E },
  { 0x42E, 0x00E },
  { 0x42C, 0x02E },
  { 0x42A, 0x04E },
  { 0x428, 0x06E },
  { 0x426, 0x08E },
  { 0x424, 0x0AE }
};


static unsigned short col16010col[10][2] = {
  { 0x00E, 0x00A },
  { 0x00E, 0x00A },
  { 0x00E, 0x00A },
  { 0x00E, 0x00A },
  { 0x00C, 0x008 },
  { 0x00A, 0x006 },
  { 0x008, 0x004 },
  { 0x008, 0x004 },
  { 0x00A, 0x006 },
  { 0x00C, 0x008 }
};


void colchgsuper(void) {
  switch (g_ram.ssonicclchg) {
    case 0:
      break;
    case 1:
      if (g_ram.ssonicclchgtim-- == 0) {
        g_ram.ssonicclchgtim = 1;

        switch (g_ram.play_type) {
          case PLAY_TYPE_SONIC:
          case PLAY_TYPE_SONIC_AND_MILES:
          default:
            colchgsupersub();
            ++g_ram.ssonicclchgcnt;
            if (g_ram.ssonicclchgcnt >= 6) {
              g_ram.ssonicclchgcnt = 0;
              g_ram.ssonicclchg = 0xFF;
              g_ram.actwk[0].u.play.control_bitfield = 0;
            }
            break;
          case PLAY_TYPE_MILES:
          case PLAY_TYPE_KNUCKLES:
            g_ram.ssonicclchg = 0xFF;
            g_ram.ssonicclchgcnt = 0;
            g_ram.smilesclchgcnt = 0;
            g_ram.actwk[0].u.play.control_bitfield = 0;
            break;
        }
      }
      break;
    case 2:
      switch (g_ram.play_type) {
        case PLAY_TYPE_SONIC:
        case PLAY_TYPE_SONIC_AND_MILES:
        default:
          if (g_ram.ssonicclchgtim-- == 0) {
            g_ram.ssonicclchgtim = 3;
            colchgsupersub();
            if (g_ram.ssonicclchgcnt-- == 0) {
              g_ram.ssonicclchgcnt = 0;
              g_ram.ssonicclchg = 0;
            }
          }
          break;
        case PLAY_TYPE_MILES:
          g_ram.ssonicclchgcnt = 0;
          g_ram.ssonicclchg = 0;
          g_ram.smilesclchgcnt = 0;
          colchgsupersub0(&g_ram.colorwk[8], smilescolor, &g_ram.colorwk3[8], smilescolor, g_ram.smilesclchgcnt);
          colchgsupersub();
          break;
        case PLAY_TYPE_KNUCKLES:
          g_ram.ssonicclchgcnt = 0;
          g_ram.ssonicclchg = 0;
          colchgsupersub0(&g_ram.colorwk[2], sknucklescolor2, &g_ram.colorwk3[2], sknucklescolor2, g_ram.ssonicclchgcnt);
          break;
      }
      break;
    case 0xFF:
      switch (g_ram.play_type) {
        case PLAY_TYPE_SONIC:
        case PLAY_TYPE_SONIC_AND_MILES:
        default:
          if (g_ram.ssonicflag != 0xFF) {
            if (g_ram.ssonicclchgtim-- == 0) {
              g_ram.ssonicclchgtim = 6;
              colchgsupersub();
              ++g_ram.ssonicclchgcnt;
              if (g_ram.ssonicclchgcnt >= 10) {
                g_ram.ssonicclchgcnt = 6;
              }
            }
          }
          else {
            if (g_ram.ssonicclchgtim-- == 0) {
              g_ram.ssonicclchgtim = 4;
              colchgsupersub0(&g_ram.colorwk[2], hsoniccolor, &g_ram.colorwk3[2], hsoniccolor, g_ram.ssonicclchgcnt);
              ++g_ram.ssonicclchgcnt;
              if (g_ram.ssonicclchgcnt >= 12) {
                g_ram.ssonicclchgcnt = 0;
              }
            }
          }
          break;
        case PLAY_TYPE_MILES:
          if (g_ram.smilesclchgtim-- == 0) {
            g_ram.smilesclchgtim = 11;
            colchgsupersub0(&g_ram.colorwk[8], smilescolor, &g_ram.colorwk3[8], smilescolor, g_ram.smilesclchgcnt);
            ++g_ram.smilesclchgcnt;
            if (g_ram.smilesclchgcnt >= 6) {
              g_ram.smilesclchgcnt = 0;
            }
          }
          if (g_ram.ssonicclchgtim-- == 0) {
            g_ram.ssonicclchgtim = 6;
            colchgsupersub();
            ++g_ram.ssonicclchgcnt;
            if (g_ram.ssonicclchgcnt >= 10) {
              g_ram.ssonicclchgcnt = 6;
            }
          }
          break;
        case PLAY_TYPE_KNUCKLES:
          if (g_ram.ssonicclchgtim-- == 0) {
            g_ram.ssonicclchgtim = 2;
            colchgsupersub0(&g_ram.colorwk[2], sknucklescolor, &g_ram.colorwk3[2], sknucklescolor, g_ram.ssonicclchgcnt);
            ++g_ram.ssonicclchgcnt;
            if (g_ram.ssonicclchgcnt >= 10) {
              g_ram.ssonicclchgcnt = 0;
              g_ram.ssonicclchgtim = 14;
            }
          }
          break;
      }
  }
}


static void colchgsupersub(void) {
  unsigned short (*p_col3)[3];
  if (get_zone(g_ram.stageno) == ANGEL_ISLAND || get_zone(g_ram.stageno) == ICECAP) {
    p_col3 = ssoniccolor2;
  }
  else {
    p_col3 = ssoniccolor3;
  }
  colchgsupersub0(&g_ram.colorwk[2], ssoniccolor, &g_ram.colorwk3[2], p_col3, g_ram.ssonicclchgcnt);
}


static void colchgsupersub0(unsigned short* p_colorwk, unsigned short (*p_col)[3], unsigned short* p_colorwk3, unsigned short (*p_col3)[3], unsigned short clchgcnt) {
  memcpy(p_colorwk, p_col[clchgcnt], sizeof(p_col[clchgcnt]));
  if (g_ram.watermode != 0) {
    memcpy(p_colorwk3, p_col3[clchgcnt], sizeof(p_col3[clchgcnt]));
  }
}


unsigned short ssoniccolor[10][3] = {
  { 0xE66, 0xC42, 0x822 },
  { 0xE88, 0xC66, 0x844 },
  { 0xEAA, 0xC88, 0xA66 },
  { 0xECC, 0xEAA, 0xC88 },
  { 0xEEE, 0xECC, 0xEAA },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xCEE, 0xCEE, 0xAEE },
  { 0xAEE, 0x8EE, 0x6CC },
  { 0x8EE, 0x0EE, 0x0AA },
  { 0xAEE, 0x8EE, 0x6CC }
};


static unsigned short ssoniccolor2[10][3] = {
  { 0xA82, 0x860, 0x640 },
  { 0xE88, 0xC66, 0x844 },
  { 0xEAA, 0xC88, 0xA66 },
  { 0xECC, 0xEAA, 0xC88 },
  { 0xEEE, 0xECC, 0xEAA },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xCEE, 0xCEC, 0xAEC },
  { 0xAEC, 0x8EC, 0x6CA },
  { 0x8EC, 0x4EA, 0x4A8 },
  { 0xCEE, 0xCEC, 0xAEC }
};


static unsigned short ssoniccolor3[10][3] = {
  { 0xC66, 0xA44, 0x624 },
  { 0xE88, 0xC66, 0x844 },
  { 0xEAA, 0xC88, 0xA66 },
  { 0xECC, 0xEAA, 0xC88 },
  { 0xEEE, 0xECC, 0xEAA },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xCEE, 0xCEC, 0xAEC },
  { 0xAEC, 0x8EC, 0x6CA },
  { 0x8EC, 0x4EA, 0x4A8 },
  { 0xCEE, 0xCEC, 0xAEC }
};


static unsigned short hsoniccolor[12][3] = {
  { 0xEEC, 0xECA, 0xEA8 },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xCEC, 0xAEA, 0x2E0 },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xAEC, 0x4EC, 0x0CC },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xCEE, 0x8EE, 0x4CE },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xEEE, 0xCCE, 0xAAE },
  { 0xEEE, 0xEEE, 0xEEE },
  { 0xEEE, 0xECE, 0xCAC },
  { 0xEEE, 0xEEE, 0xEEE }
};


static unsigned short smilescolor[6][3] = {
  { 0x0AE, 0x08E, 0x46A },
  { 0x4CE, 0x2AE, 0x46A },
  { 0x8CE, 0x4CE, 0x46C },
  { 0xAEE, 0x8CE, 0x48E },
  { 0x8CE, 0x4CE, 0x46C },
  { 0x4CE, 0x2AE, 0x46A }
};


static unsigned short sknucklescolor[10][3] = {
  { 0xA6E, 0x64E, 0x428 },
  { 0xC8E, 0x86E, 0x64A },
  { 0xEAE, 0xA8E, 0x86C },
  { 0xECE, 0xCAE, 0xA8E },
  { 0xEEE, 0xECE, 0xCAE },
  { 0xECE, 0xCAE, 0xA8E },
  { 0xEAE, 0xA8E, 0x86C },
  { 0xC8E, 0x86E, 0x64A },
  { 0xA6E, 0x64E, 0x428 },
  { 0x84E, 0x40C, 0x206 }
};


static unsigned short sknucklescolor2[1][3] = {
  { 0x64E, 0x20C, 0x206 }
};


void fadein(void) {
  g_ram.colorcnt = 64;
  fadein0();

  for (int i = 0; i < 22; ++i) {
    g_ram.int_flg = 18;
    v_int();
    fadein1();
  }
}


void fadein1(void) {
  for (int i = 0; i < g_ram.colorcnt; ++i) {
    fadein2(&g_ram.colorwk[g_ram.startcolor + i], &g_ram.colorwk2[g_ram.startcolor + i]);
  }

  for (int i = 0; i < g_ram.colorcnt; ++i) {
    fadein2(&g_ram.colorwk3[g_ram.startcolor + i], &g_ram.colorwk4[g_ram.startcolor + i]);
  }
}


static void fadein2(unsigned short* p_destination, unsigned short* p_source) {
  if (*p_source == *p_destination) return;

  if (*p_destination + 0x200 <= *p_source) {
    *p_destination += 0x200;
  }
  else if (*p_destination + 0x20 <= *p_source) {
    *p_destination += 0x020;
  }
  else {
    *p_destination += 0x002;
  }
}


static void fadein0(void) {
  if (g_ram.stageno == ENDING || g_ram.stageno == MASTER_EMERALD_SHRINE) {
    flashin0();
  }
  else {
    memset(&g_ram.colorwk[g_ram.startcolor], 0, sizeof(unsigned short) * g_ram.colorcnt);
    if (g_ram.watermode != 0) {
      memset(&g_ram.colorwk3[g_ram.startcolor], 0, sizeof(unsigned short) * g_ram.colorcnt);
    }
  }
}


void colchg(void) {
  if (g_ram.fadecnt < 0) return;

  if (g_ram.fadecnt != 0) {
    --g_ram.fadecnt;
    if (g_ram.stageno == ENDING || g_ram.stageno == MASTER_EMERALD_SHRINE) {
      flashin1();
    }
    else {
      fadein1();
    }
  }
  else {
    clchgctr();
  }
}


void fadeout(void) {
  g_ram.colorcnt = 64;

  for (int i = 0; i < 22; ++i) {
    g_ram.int_flg = 18;
    v_int();
    fadeout1();
  }
}


void fadeout1(void) {
  for (int i = 0; i < g_ram.colorcnt; ++i) {
    fadeout2(&g_ram.colorwk[g_ram.startcolor + i]);
  }

  for (int i = 0; i < g_ram.colorcnt; ++i) {
    fadeout2(&g_ram.colorwk3[g_ram.startcolor + i]);
  }
}


static void fadeout2(unsigned short* p_destination) {
  if (*p_destination == 0) return;

  if (*p_destination & 0x00E) {
    *p_destination -= 0x002;
  }
  else if (*p_destination & 0x0E0) {
    *p_destination -= 0x020;
  }
  else if (*p_destination & 0xE00) {
    *p_destination -= 0x200;
  }
}


static void flashin0(void) {
  for (int i = 0; i < g_ram.colorcnt; ++i) {
    g_ram.colorwk[g_ram.startcolor + i] = 0xEEE;
  }

  g_ram.DAT_08ffface = 0;
}


void flashin(void) {
  g_ram.colorcnt = 64;
  flashin0();

  for (int i = 0; i < 22; ++i) {
    g_ram.int_flg = 18;
    v_int();
    flashin1();
  }
}


void flashin1(void) {
  if (g_ram.DAT_08ffface-- == 0) {
    g_ram.DAT_08ffface = 2;

    for (int i = 0; i < g_ram.colorcnt; ++i) {
      flashin2(&g_ram.colorwk[g_ram.startcolor + i], &g_ram.colorwk2[g_ram.startcolor + i]);
    }

    if (g_ram.watermode != 0) {
      for (int i = 0; i < g_ram.colorcnt; ++i) {
        flashin2(&g_ram.colorwk3[g_ram.startcolor + i], &g_ram.colorwk4[g_ram.startcolor + i]);
      }
    }
  }
}


static void flashin2(unsigned short* p_destination, unsigned short* p_source) {
  if ((*p_destination & 0x0E0) > (*p_source & 0x0E0)) {
    *p_destination -= 0x020;
  }
  if ((*p_destination & 0x00E) > (*p_source & 0x00E)) {
    *p_destination -= 0x002;
  }
  if ((*p_destination & 0xE00) > (*p_source & 0xE00)) {
    *p_destination -= 0x200;
  }
}


void flashout(void) {
  g_ram.colorcnt = 64;

  for (int i = 0; i < 22; ++i) {
    g_ram.int_flg = 18;
    v_int();
    flashout1();
  }
}


void flashout1(void) {
  for (int i = 0; i < g_ram.colorcnt; ++i) {
    flashout2(&g_ram.colorwk[g_ram.startcolor + i]);
  }

  for (int i = 0; i < g_ram.colorcnt; ++i) {
    flashout2(&g_ram.colorwk3[g_ram.startcolor + i]);
  }
}


static void flashout2(unsigned short* p_destination) {
  if (*p_destination == 0xEEE) return;

  if ((*p_destination & 0x00E) != 0x00E) {
    *p_destination += 0x002;
  }
  else if ((*p_destination & 0x0E0) != 0x0E0) {
    *p_destination += 0x020;
  }
  else if ((*p_destination & 0xE00) != 0xE00) {
    *p_destination += 0x200;
  }
}


void colorset(unsigned short color_no) {
  SKC_colortbl_entry* p_entry = &colortbl[color_no];
  memcpy(&g_ram.colorwk2[p_entry->offset], p_entry->palette_ptr, sizeof(unsigned short) * p_entry->cnt);
}


void colorset2(unsigned short color_no) {
  SKC_colortbl_entry* p_entry = &colortbl[color_no];
  memcpy(&g_ram.colorwk[p_entry->offset], p_entry->palette_ptr, sizeof(unsigned short) * p_entry->cnt);
}


void colorset3(unsigned short color_no) {
  SKC_colortbl_entry* p_entry = &colortbl[color_no];
  memcpy(&g_ram.colorwk3[p_entry->offset], p_entry->palette_ptr, sizeof(unsigned short) * p_entry->cnt);
}


void colorset4(unsigned short color_no) {
  SKC_colortbl_entry* p_entry = &colortbl[color_no];
  memcpy(&g_ram.colorwk4[p_entry->offset], p_entry->palette_ptr, sizeof(unsigned short) * p_entry->cnt);
}
