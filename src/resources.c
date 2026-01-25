signed char* titlepat[21];
signed char titlesp00[2];
signed char titlesp01[98];
signed char titlesp02[14];
signed char titlesp03[26];
signed char titlesp04[68];
signed char titlesp05[50];
signed char titlesp06[74];
signed char titlesp07[74];
signed char titlesp08[80];
signed char titlesp09[38];
signed char titlesp10[56];
signed char titlesp11[62];
signed char titlesp12[62];
signed char titlesp13[50];
signed char titlesp14[68];
signed char titlesp15[50];
signed char titlesp16[68];
signed char titlesp17[68];
signed char titlesp18[32];
signed char titlesp20[32];
unsigned short* sai00_tbl[8];
unsigned short sai00_tbl00[4];
unsigned short sai00_tbl01[4];
unsigned short sai00_tbl02[2];
unsigned short sai00_tbl03[3];
unsigned short sai00_tbl03[2];
unsigned short sai00_tbl03[2];
unsigned short sai00_tbl03[2];
unsigned short sai00_tbl03[2];
unsigned char zone_friend_data[24][2];


signed char* titlepat[21] = {
  titlesp00,
  titlesp01,
  titlesp02,
  titlesp03,
  titlesp04,
  titlesp05,
  titlesp06,
  titlesp07,
  titlesp08,
  titlesp09,
  titlesp10,
  titlesp11,
  titlesp12,
  titlesp13,
  titlesp14,
  titlesp15,
  titlesp16,
  titlesp17,
  titlesp18,
  titlesp18,
  titlesp20
};


signed char titlesp00[2] = {
     0,    0
};
signed char titlesp01[98] = {
     0,   16,   88,    9,   16, -123,  -24,   -1,   88,    9,
    22, -123,    0,    0, -112,   15,    0, -123,  -32,   -1,
  -112,   15,    0, -123,    0,    0,  -80,   15,    0, -123,
   -32,   -1,  -80,   15,    0, -123,    0,    0,  -48,   15,
     0, -123,  -32,   -1,  -48,   15,    0, -123,    0,    0,
   -16,   15,    0, -123,  -32,   -1,  -16,   15,    0, -123,
     0,    0,   16,   15,    0, -123,  -32,   -1,   16,   15,
     0, -123,    0,    0,   48,   15,    0, -123,  -32,   -1,
    48,   15,    0, -123,    0,    0,   80,   15,    0, -123,
   -32,   -1,   80,   15,    0, -123,    0,    0
};
signed char titlesp02[14] = {
     0,    2,   16,    9,   55, -123,  -28,   -1,    0,   15,
    61, -123,  -11,   -1
};
signed char titlesp03[26] = {
     0,    4,    0,    6,   49, -123,  -36,   -1,    0,   10,
    40, -123,  -20,   -1,    0,    6,   34, -123,    4,    0,
     0,    6,   28, -123,   20,    0
};
signed char titlesp04[68] = {
     0,   11,    0,    6,   77, -123,  -32,   -1,    0,    6,
    34, -123,  -16,   -1,    0,    6,   89, -123,    0,    0,
     0,    6,   28, -123,   16,    0,    0,    2,   98, -123,
    32,    0,    0,    2,   95, -123,   48,    0,    0,    6,
   101, -123,   56,    0,    0,    2,   98, -123,   72,    0,
     0,    6,   77, -123,   80,    0,    0,    6,   34, -123,
    96,    0,    0,    6,   83, -123,  112,    0
};
signed char titlesp05[50] = {
     0,    8,    0,    6,   89, -123,  -16,   -1,    0,    6,
   110, -123,    0,    0,    0,    6,   83, -123,   16,    0,
     0,    6,   98, -123,   32,    0,    0,   10,   40, -123,
    48,    0,    0,    6,   77, -123,   72,    0,    0,    2,
    95, -123,   88,    0,    0,   14,  104, -123,   96,    0
};
signed char titlesp06[74] = {
     0,   12,    0,   10,  104, -123,  -72,   -1,    0,    6,
    77, -123,  -48,   -1,    0,    6,  113, -123,  -32,   -1,
     0,    6,   83, -123,  -16,   -1,    0,    2,  101, -123,
     0,    0,    0,    6,   28, -123,    8,    0,    0,    6,
    95, -123,   32,    0,    0,    6,   77, -123,   48,    0,
     0,    6,  113, -123,   64,    0,    0,    6,   89, -123,
    80,    0,    0,    6,   28, -123,   96,    0,    0,    6,
    34, -123,  112,    0
};
signed char titlesp07[74] = {
     0,   12,    0,    6,   83, -123,  -64,   -1,    0,    6,
    77, -123,  -48,   -1,    0,    6,  107, -123,  -32,   -1,
     0,    6,   34, -123,  -16,   -1,    0,    2,  101, -123,
     0,    0,    0,    6,  119, -123,    8,    0,    0,    6,
    77, -123,   24,    0,    0,    2,  104, -123,   40,    0,
     0,    6,   34, -123,   56,    0,    0,    2,  101, -123,
    72,    0,    0,   14,   89, -123,   80,    0,   0,     6,
   113, -123,  112,    0
};
signed char titlesp08[80] = {
     0,   13,    0,    6,   89, -123,  -72,   -1,    0,    2,
   104, -123,  -56,   -1,    0,    6,  119, -123,  -48,   -1,
     0,    2,  101, -123,  -32,   -1,    0,    6,   34, -123,
   -24,   -1,    0,    6,   95, -123,   -8,   -1,    0,    6,
    83, -123,   16,    0,    0,    6,   77, -123,   32,    0,
     0,    6,  113, -123,   48,    0,    0,    6,  113, -123,
    64,    0,    0,    6,   28, -123,   80,    0,    0,    6,
   107, -123,   96,    0,    0,    6,  119, -123,  112,    0
};
signed char titlesp09[38] = {
     0,    6,    0,    2,   89, -123,   40,    0,    0,    6,
    83, -123,   48,    0,    0,    6,   28, -123,   64,    0,
     0,    6,   83, -123,   80,    0,    0,    6,   77, -123,
    96,    0,    0,    6,   92, -123,  112,    0
};
signed char titlesp10[56] = {
     0,    9,    0,    2,  101, -123,  -32,   -1,    0,    6,
    77, -123,  -24,   -1,    0,    6,  110, -123,   -8,   -1,
     0,    6,   34, -123,    8,    0,    0,   14,   89, -123,
    24,    0,    0,    6,   83, -123,   64,    0,    0,    6,
    77, -123,   80,    0,    0,    6,  104, -123,   96,    0,
     0,    6,   28, -123,  112,    0
};
signed char titlesp11[62] = {
     0,   10,    0,   10,   89, -123,  -80,   -1,    0,    6,
   110, -123,  -56,   -1,    0,    6,  104, -123,  -40,   -1,
     0,    6,   77, -123,  -24,   -1,    0,    6,   98, -123,
    -8,   -1,    0,   10,   40, -123,    8,    0,    0,   10,
    40, -123,   32,    0,    0,   10,   89, -123,   56,    0,
     0,   14,   77, -123,   88,    0,    0,    2,   86, -123,
   120,    0
};
signed char titlesp12[62] = {
     0,   10,    0,    6,  101, -123,  -32,   -1,    0,    6,
    77, -123,  -16,   -1,    0,    6,   34, -123,    0,    0,
     0,    6,   83, -123,   16,    0,    0,   10,   40, -123,
    32,    0,    0,    6,   95, -123,   56,    0,    0,   10,
    40, -123,   72,    0,    0,    2,   92, -123,   96,    0,
     0,    2,   89, -123,  104,    0,    0,    6,  101, -123,
   112,    0
};
signed char titlesp13[50] = {
     0,    8,    0,    2,   89, -123,    0,    0,    0,    6,
    77, -123,    8,    0,    0,    6,   98, -123,   24,    0,
     0,    6,   77, -123,   40,    0,    0,    6,   92, -123,
    64,    0,    0,    6,   28, -123,   80,    0,    0,    6,
    28, -123,   96,    0,    0,    6,   83, -123,  112,    0
};
signed char titlesp14[68] = {
     0,   11,    0,    6,  101, -123,  -72,   -1,    0,    6,
    89, -123,  -56,   -1,    0,    6,  119, -123,  -40,   -1,
     0,    6,  101, -123,  -16,   -1,    0,    6,   77, -123,
     0,    0,    0,    6,   34, -123,   16,    0,    0,    6,
    83, -123,   32,    0,    0,   14,  107, -123,   48,    0,
     0,    6,   77, -123,   80,    0,    0,    6,   95, -123,
    96,    0,    0,    6,  119, -123,  112,    0
};
signed char titlesp15[50] = {
     0,    8,    0,    6,   83, -123,   -8,   -1,    0,    6,
    28, -123,    8,    0,    0,    6,   77, -123,   24,    0,
     0,    6,  101, -123,   40,    0,    0,    6,   95, -123,
    56,    0,    0,    6,   28, -123,   80,    0,    0,    6,
    89, -123,   96,    0,    0,    6,   89, -123,  112,    0
};
signed char titlesp16[68] = {
     0,   11,    0,    6,  110, -123,  -80,   -1,    0,    6,
    89, -123,  -64,   -1,    0,    6,   28, -123,  -48,   -1,
     0,    6,   83, -123,  -24,   -1,    0,   10,   40, -123,
    -8,   -1,    0,   10,   40, -123,   16,    0,    0,   10,
    95, -123,   40,    0,    0,    6,  104, -123,   64,    0,
     0,    6,   83, -123,   80,    0,    0,    6,   77, -123,
    96,    0,    0,    6,  116, -123,  112,    0
};
signed char titlesp17[68] = {
     0,   11,    0,   10,   95, -123,  -56,   -1,    0,    6,
    89, -123,  -32,   -1,    0,    6,   89, -123,  -16,   -1,
     0,    6,   28, -123,    0,    0,    0,    6,   34, -123,
    16,    0,    0,    6,  107, -123,   40,    0,    0,    6,
    77, -123,   56,    0,    0,    2,  104, -123,   72,    0,
     0,    6,   77, -123,   80,    0,    0,    6,   83, -123,
    96,    0,    0,    6,   28, -123,  112,    0
};
signed char titlesp18[32] = {
     0,    5,    0,    6,   83, -123,    0,    0,    0,   10,
    40, -123,   16,    0,    0,    6,   95, -123,   40,    0,
     0,    6,  113, -123,   56,    0,    0,    6,  101, -123,
    72,    0
};
signed char titlesp20[32] = {
     0,    5,    0,    6,  101, -123,    0,    0,    0,    6,
   107, -123,   16,    0,    0,    6,   77, -123,   32,    0,
     0,    6,   89, -123,   48,    0,    0,    6,   28, -123,
    64,    0
};


unsigned short* sai00_tbl[8] = {
  sai00_tbl00,
  sai00_tbl01,
  sai00_tbl02,
  sai00_tbl03,
  sai00_tbl04,
  sai00_tbl05,
  sai00_tbl06,
  sai00_tbl07
};


unsigned short sai00_tbl00[4] = { 512, 1, 47, 290 };
unsigned short sai00_tbl01[4] = { 512, 337, 369, 411 };
unsigned short sai00_tbl02[2] = { 0, 603 };
unsigned short sai00_tbl03[3] = { 256, 799, 1041 };
unsigned short sai00_tbl04[2] = { 0, 1074 };
unsigned short sai00_tbl05[2] = { 0, 1125 };
unsigned short sai00_tbl06[2] = { 0, 1221 };
unsigned short sai00_tbl07[2] = { 0, 1314 };


#define POCKY_RABBIT 0
#define CUCKY_CHICKEN 1
#define PECKY_PINGUIN 2
#define ROCKY_SEAL 3
#define FLICKY_FLICKY 5
#define RICKY_SQUIRREL 6
unsigned char zone_friend_data[24][2] = {
  { FLICKY_FLICKY,  CUCKY_CHICKEN }, // Angel Island
  { POCKY_RABBIT,   ROCKY_SEAL    }, // Hydrocity
  { FLICKY_FLICKY,  CUCKY_CHICKEN }, // Marble Garden
  { POCKY_RABBIT,   FLICKY_FLICKY }, // Carnival Night
  { RICKY_SQUIRREL, FLICKY_FLICKY }, // Flying Battery
  { PECKY_PINGUIN,  ROCKY_SEAL    }, // Icecap
  { FLICKY_FLICKY,  CUCKY_CHICKEN }, // Launch Base
  { RICKY_SQUIRREL, CUCKY_CHICKEN }, // Mushroom Hill
  { POCKY_RABBIT,   CUCKY_CHICKEN }, // Sandopolis
  { FLICKY_FLICKY,  CUCKY_CHICKEN }, // Lava Reef
  { POCKY_RABBIT,   FLICKY_FLICKY }, // Sky Sanctuary
  { RICKY_SQUIRREL, CUCKY_CHICKEN }, // Death Egg
  { RICKY_SQUIRREL, FLICKY_FLICKY }, // Doomsdag
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
  { FLICKY_FLICKY,  CUCKY_CHICKEN },
};
