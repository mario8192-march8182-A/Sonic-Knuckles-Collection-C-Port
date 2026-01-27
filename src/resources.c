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
