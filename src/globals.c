#include <windows.h>
#include <ddraw.h>
#include <dsound.h>
#include "constants.h"
#include "strings.h"
#include "sprite_status.h"
#include "types.h"

/* 0082b0b0 */ char* g_windowTitles[3] = {
  g_s3kWindowTitle,
  g_skWindowTitle,
  g_s3WindowTitle
};
/* 0082b0c0 */ char* g_trialWindowTitles[3] = {
  g_s3kTrialWindowTitle,
  g_skTrialWindowTitle,
  g_s3TrialWindowTitle
};
/* 0082b0d0 */ char* g_demoWindowTitles[3] = {
  g_s3kDemoWindowTitle,
  g_skDemoWindowTitle,
  g_s3DemoWindowTitle
};
/* 0082b0e0 */ char* g_debugWindowTitles[3] = {
  g_s3kDebugWindowTitle,
  g_skDebugWindowTitle,
  g_s3DebugWindowTitle
};
/* 0082b0f0 */ char* g_pausedText[4] = {
  g_englishPausedText,
  g_frenchPausedText,
  g_germanPausedText,
  g_spanishPausedText
};
/* 0082b108 */ char* g_thanksForPlayingEnText[16] = {
  g_thanksForPlayingEnText1,
  g_thanksForPlayingEnText2,
  g_thanksForPlayingEnText3,
  g_thanksForPlayingEnText4,
  g_thanksForPlayingEnText5,
  g_thanksForPlayingEnText6,
  g_thanksForPlayingEnText7,
  g_thanksForPlayingEnText8,
  g_thanksForPlayingEnText9,
  g_thanksForPlayingEnText10,
  g_thanksForPlayingEnText11,
  g_thanksForPlayingEnText12,
  g_thanksForPlayingEnText13,
  g_thanksForPlayingEnText14,
  0,
  0
};
/* 0082b148 */ UCHAR* g_thanksForPlayingJpText[20] = {
  g_thanksForPlayingJpText1,
  g_thanksForPlayingJpText2,
  g_thanksForPlayingJpText3,
  g_thanksForPlayingJpText4,
  g_thanksForPlayingJpText5,
  g_thanksForPlayingJpText6,
  g_thanksForPlayingJpText7,
  g_thanksForPlayingJpText8,
  g_thanksForPlayingJpText9,
  g_thanksForPlayingJpText10,
  g_thanksForPlayingJpText11,
  g_thanksForPlayingJpText12,
  g_thanksForPlayingJpText13,
  g_thanksForPlayingJpText14,
  g_thanksForPlayingJpText15,
  g_thanksForPlayingJpText16,
  g_thanksForPlayingJpText17,
  g_thanksForPlayingJpText18,
  g_thanksForPlayingJpText19,
  0
};
/* 0082bad0 */ void* g_region8fe8000 = 0;
/* 0082bad4 */ void* g_region7ff8000 = 0;
/* 0082bb40 */ HRESULT(*g_pDdrawCreate)(GUID*, LPDIRECTDRAW*, IUnknown*) = 0;
/* 0082c868 */ HMODULE g_hMusicDll = 0;
/* 0082c86c */ // IMidi* g_pMidiInterface = 0;
/* 0082c870 */ HRESULT(*g_pDSoundCreate)(GUID*, LPDIRECTSOUND*, LPUNKNOWN*) = 0;
/* 0082c878 */ int g_soundBufferMapping[224] = {
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,   1,  -1,   2,   3,   4,   5,   6,   7,   8,
    9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
   19,  20,  21,  22,  23,  24,  25,  26,  27,  28,
   29,  30,  31,  32,  33,  34,  35,  36,  37,  38,
   39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
   49,  50,  51,  52,  53,  54,  55,  56,  57,  58,
   59,  60,  61,  62,  63,  64,  65,  66,  67,  68,
   69,  70,  71,  72,  73,  74,  75,  76,  77,  78,
   79,  80,  81,  82,  83,  84,  85,  86,  87,  88,
   89,  90,  91,  92,  93,  94,  95,  96,  97,  98,
   99, 100, 101, 102, 103, 104, 105, 106, 107, 108,
  109, 110, 111, 112, 113, 114, 115, 116, 117, 118,
  119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
  129, 130, 131, 132, 133, 134, 135, 136, 137, 138,
  139, 140, 141, 142, 143, 144, 145, 146, 147, 148,
  150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
   -1,  -1,  -1,   0
};
/* 0082ddd0 */ char g_kbKeyNames[4][30][32] = {
  {
    "Num0",
    "Num1",
    "Num2",
    "Num3",
    "Num4",
    "Num5",
    "Num6",
    "Num7",
    "Num8",
    "Num9",
    "Num.",
    "Num+",
    "Num-",
    "Num*",
    "Num/",
    "Up",
    "Left",
    "Right",
    "Down",
    "Ins",
    "Del",
    "Home",
    "End",
    "PUp",
    "PDown",
    "Enter",
    "BS",
    "Tab",
    "Space",
    ""
  },
  {
    "Num0",
    "Num1",
    "Num2",
    "Num3",
    "Num4",
    "Num5",
    "Num6",
    "Num7",
    "Num8",
    "Num9",
    "Num.",
    "Num+",
    "Num-",
    "Num*",
    "Num/",
    "Haut",
    "Gauche",
    "Droite",
    "Bas",
    "Inser",
    "Suppr",
    "Début",
    "Fin",
    "Mont page",
    "Desc Page",
    "Entrer",
    "Retour arrière",
    "Touche de Tabulation",
    "Barre d'espacement",
    ""
  },
  {
    "Num0",
    "Num1",
    "Num2",
    "Num3",
    "Num4",
    "Num5",
    "Num6",
    "Num7",
    "Num8",
    "Num9",
    "Num.",
    "Num+",
    "Num-",
    "Num*",
    "Num/",
    "Hoch",
    "Links",
    "Rechts",
    "Runter",
    "Einfg",
    "Entf",
    "Pos1",
    "Ende",
    "PUp",
    "PDown",
    "Enter",
    "BS",
    "Tab",
    "Leertaste",
    ""
  },
  {
    "Núm0",
    "Núm1",
    "Núm2",
    "Núm3",
    "Núm4",
    "Núm5",
    "Núm6",
    "Núm7",
    "Núm8",
    "Núm9",
    "Núm.",
    "Núm+",
    "Núm-",
    "Núm*",
    "Núm/",
    "Arriba",
    "Izquierda",
    "Derecha",
    "Abajo",
    "Insert",
    "SUPR",
    "Inicio",
    "Fin",
    "Re Pág.",
    "Av. Pág.",
    "Enter",
    "Borrar",
    "Tab",
    "Espacio",
    ""
  }
};
/* 0082ecd0 */ int g_kbKeyCodes[30] = {
  VK_NUMPAD0,
  VK_NUMPAD1,
  VK_NUMPAD2,
  VK_NUMPAD3,
  VK_NUMPAD4,
  VK_NUMPAD5,
  VK_NUMPAD6,
  VK_NUMPAD7,
  VK_NUMPAD8,
  VK_NUMPAD9,
  VK_DECIMAL,
  VK_ADD,
  VK_SUBTRACT,
  VK_MULTIPLY,
  VK_DIVIDE,
  VK_UP,
  VK_LEFT,
  VK_RIGHT,
  VK_DOWN,
  VK_INSERT,
  VK_DELETE,
  VK_HOME,
  VK_END,
  VK_PRIOR,
  VK_NEXT,
  VK_RETURN,
  VK_BACK,
  VK_TAB,
  VK_SPACE,
  -1
};
/* 0082ed48 */ int g_defaultKbKeys[2][5] = {
  {
    VK_UP,
    VK_LEFT,
    VK_RIGHT,
    VK_DOWN,
    VK_RETURN
  },
  {
    'D',
    'X',
    'V',
    'C',
    'A'
  }
};
/* 0082ed78 */ char* g_dontUseText[4] = {
  g_dontUseEnText,
  g_dontUseFrText,
  g_dontUseDeText,
  g_dontUseEsText
};
/* 00831164 */ BOOL g_bLaunchRunSonic = FALSE;
/* 00831168 */ HACCEL g_hAccel = 0;
/* 00831170 */ int g_nCmdShow = 0;
/* 00831174 */ int g_useModeX = 0;
/* 00831178 */ int g_noSoundEffect = 0;
/* 0083117c */ int g_midiFlag = 0;
/* 00831180 */ int g_sonic3Alone = 0;
/* 00831184 */ int g_startGameMode = 0;
/* 0083118c */ BOOL g_bTrial = FALSE;
/* 00831188 */ int g_sonicGameMode = 0;
/* 00831190 */ int g_langMode = 0;
/* 00831194 */ int g_debugMode = 0;
/* 00831198 */ BOOL BOOL_00831198 = FALSE;
/* 0083119c */ BOOL g_bDemo = FALSE;
/* 008311a0 */ // CGame g_game;
/* 00831368 */ int g_seMode;
/* 0083136c */ int g_bgmMode;
/* 00831374 */ int g_cdCheckEnable;
/* 00831370 */ HINSTANCE g_hInstance;
/* 00831378 */ char* g_lpCmdLine;
/* 0085475c */ ULONG g_createFileError;
/* 008549a4 */ ULONG g_mdRegisterD0;
/* 008549d4 */ ULONG g_supplementaryMdRamAddress;
/* 008549e8 */ BYTE g_saveFile[1024];
/* 00856e0c */ // CGraphics* g_pGraphics;
/* 00856e10 */ BOOL BOOL_00856e10;
/* 00856e18 */ CRITICAL_SECTION g_CriticalSectionObj;
/* 00856e30 */ ULONG g_soundTest_bgmId;
/* 00856e34 */ // CSound* g_pSound;
/* 00856e38 */ ULONG g_soundTest_seId;
/* 00856e3c */ int g_bgmId;
/* 00856e40 */ // CSound* g_pSound2;
/* 00856e58 */ int g_kbKeys[2][5];
/* 00856e88 */ int g_joystickId[2];
/* 00856e90 */ UINT g_joystickYCenter2[2];
/* 00856e98 */ UINT g_joystickXCenter1[2];
/* 00856ea0 */ UINT g_joystickXCenter2[2];
/* 00856ea8 */ BOOL g_joystickEnoughButtons[2];
/* 00856eb0 */ UINT g_joystickYCenter1[2];
/* 00856eb8 */ int g_selectKeyDialogCurrentKey;
/* 00856ec0 */ BOOL g_joystickAvailability[32];
/* 00856f40 */ int g_kbKeysEdit[2][5];
/* 00856f68 */ UINT g_joystickCnt;
/* 08000000 */ BYTE g_mdVram[0x10000];
/* 00831758 */ BYTE g_mdSystemRam[0x23000];
/* 08ff0000 */ BYTE g_mdRam[0x10000];

unsigned short pbuffer[PBUFFER_LEVELS][PBUFFER_LEVEL_SLOTS];
sprite_status actwk[ACTWK_SLOTS];
unsigned short colibuffer[COLBUFFER_SLOTS];
short ringwk[RINGWK_SLOTS];
unsigned char flagwork[FLAGWORK_SLOTS];
short scralim_n_down;
short scralim_left;
short scralim_right;
short scralim_down;
unsigned char scr_resize_no;
zone_act stageno_i;
long scra_h_posit;
long scra_v_posit;
short frame_offset_x;
unsigned char event_flag_3;
unsigned long DAT_08ffef40;
unsigned char disable_interrupts_flag;
unsigned short ringbuffer[RINGBUFFER_SLOTS];
unsigned long ranum;
short waterposi;
unsigned char waterflag;
unsigned char ssonicpallet_next;
unsigned char ssonicpallet;
unsigned char smilesflag;
unsigned short ssonicring_timer;
unsigned char watermode;
unsigned char miles_carry_flag;
short plmaxspdwk;
short pladdspdwk;
short plretspdwk;
unsigned char bossstart;
unsigned char soz_darkness_level;
unsigned char reverse_gravity_flag;
unsigned char pl2_lock_flag;
unsigned short emyscorecnt;
unsigned short timebonus;
unsigned short ringbonus;
unsigned short scr_x_no;
unsigned char level_triggers[LEVEL_TRIGGERS_SLOTS];
unsigned char emy_wrt_flg[EMY_WRT_FLG_SLOTS];
unsigned char DAT_08fffaa2;
unsigned char act_clear_flag;
unsigned char act_start_flag;
unsigned long systemtimer;
unsigned char soz_ghosts;
unsigned char DAT_08fffacd;
unsigned short gameflag;
unsigned short gametimer;
unsigned char edit_r_no;
zone_act stageno;
unsigned char pl_suu;
unsigned char ssonicflag;
unsigned char plring_f2;
unsigned char pl_suu_f;
unsigned char plring_f;
unsigned char plscore_f;
unsigned char pltime_f;
short plring;
act_timer pltime;
unsigned long plscore;
unsigned char markerno;
unsigned char markerno_s;
zone_act stageno_s;
short plxposi_s;
short plyposi_s;
short plring_s;
act_timer pltime_s;
unsigned short plsproffset_s;
block_coli_bits plcolibits_s;
short scra_h_posit_s;
short scra_v_posit_s;
short waterposi_s;
unsigned char waterflag_s;
unsigned char plring_f2_s;
short scralim_down_s;
unsigned char scr_resize_no_s;
unsigned char plcddat2_s;
unsigned char marker_flag;
unsigned char markerno_s2;
zone_act stageno_s2;
short plxposi_s2;
short plyposi_s2;
short plring_s2;
act_timer pltime_s2;
unsigned short plsproffset_s2;
block_coli_bits plcolibits_s2;
short scra_h_posit_s2;
short scra_v_posit_s2;
short waterposi_s2;
unsigned char waterflag_s2;
unsigned char plring_f2_s2;
short scralim_down_s2;
unsigned char scr_resize_no_s2;
unsigned char ring_patno;
unsigned char flyring_patcnt;
unsigned char flyring_patno;
unsigned char pl2ring_f;
unsigned char pl2ring_f2;
unsigned char pl2_suu;
short pl2maxspdwk;
short pl2addspdwk;
short pl2retspdwk;
short plring_act;
short pl2ring_act;
unsigned short DAT_08fffecc;
unsigned short DAT_08fffece;
short pl2ring;
unsigned long DAT_08fffed2;
short actring;
character_team_id plmode;
unsigned char divdev_modules;
unsigned short frame_bonus;
unsigned char plcddat2_s2;
unsigned char plresetflag;
zone_act stageno_is;
zone_act stageno_is2;
unsigned short cartridge;
unsigned long extrascore;
unsigned short plsproffset;
unsigned char mdstatus;
unsigned short vs_flag;
