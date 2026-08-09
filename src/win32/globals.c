#include <windows.h>
#include <ddraw.h>
#include <dsound.h>
#include "constants.h"
#include "strings.h"
#include "types/sprite.h"

/* 00829058 */ ULONG DAT_00829058[10] = { 20, 19, 10, 7, 5, 4, 3, 2, 0, 0 };
/* 00829080 */ double DAT_00829080 = 17.0;
/* 00829088 */ double DAT_00829088 = 8.0;
/* 0082b040 */ BOOL BOOL_0082b040 = TRUE;
/* 0082b044 */ BOOL BOOL_0082b044 = FALSE;
/* 0082b048 */ ULONG g_lastSystemTime = 0;
/* 0082b04c */ ULONG g_lastSystemTime2 = 0;
/* 0082b050 */ ULONG g_lastSystemTime3 = 0;
/* 0082b054 */ ULONG DAT_0082b054 = 0;
/* 0082b05c */ ULONG g_cumulativeElapsedTime = 0;
/* 0082b070 */ ULONG DAT_0082b070 = 0;
/* 0082b074 */ ULONG DAT_0082b074 = 0;
/* 0082b078 */ ULONG DAT_0082b078 = 0;
/* 0082b07c */ ULONG DAT_0082b07c = 0;
/* 0082b088 */ ULONG DAT_0082b088 = 0;
/* 0082b098 */ long DAT_0082b098 = 1;
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
/* 0082b100 */ BOOL g_bResetMdRam = FALSE;
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
/* 0082cbf8 */ int g_unknownSoundMapping[224] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1,  0, -1,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  1,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  2,  3,  4,  5,  6,
   7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
  17, 18, 19,  0, 20, 21, 22, 23, 24, 25,
  26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
  -1, -1, -1, -1
};
/* 0082cf78 */ int g_unknownSoundMapping2[224] = {
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,   0,  -1,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0, 170, 171,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0, 172,   0,
    0,   0, 173, 174,   0,   0, 175,   0, 176, 177,
   -1,  -1,  -1,  -1
};
/* 0082d2f8 */ int g_unknownSoundMapping3[224] = {
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
   -1,   0,  -1,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,  54,  72,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0, 125,   0,
    0,   0,  60, 165,   0,   0,  67,   0, 106,  13,
   -1,  -1,  -1,  -1
};
/* 0082d678 */ int g_soundFrequencies[20] = {
  11025,
  12127,
  13230,
  14332,
  15434,
  16537,
  17640,
  18742,
  19845,
  20947,
  22050,
  24255,
  26460,
  28665,
  30869,
  33075,
  35280,
  37485,
  39690,
  41895
};
/* 0082d6c8 */ ULONG g_unknownSoundFrequencyValue = 0;
/* 0082d6d0 */ int g_soundMapping[51] = {
  -1,  1,  2,  3,  4,  5,  6,  7,  8,  9,
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
  20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
  30, 31, 32, 33, 34, 35, 36,  0, 49, 37,
  38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
  48
};
/* 0082ddc8 */ BOOL g_numpad_unlocked;
/* 0082ddcc */ UCHAR DAT_0082ddcc[4] = { 0, 0, 0x50, 0xFA };
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
/* 0082ed70 */ unsigned char g_prevMdButtonsP1Down;
/* 0082ed74 */ unsigned char g_prevMdButtonsP2Down;
/* 0082ed78 */ char* g_dontUseText[4] = {
  g_dontUseEnText,
  g_dontUseFrText,
  g_dontUseDeText,
  g_dontUseEsText
};
/* 00831140 */ ULONG DAT_00831140 = 0;
/* 00831144 */ ULONG g_elapsedTime3 = 0;
/* 00831148 */ ULONG g_systemTime = 0;
/* 0083114c */ ULONG g_lastDAT_0082b074 = 0;
/* 00831150 */ double DAT_00831150 = 0.0;
/* 00831158 */ ULONG g_lastDAT_0082b07c = 0;
/* 0083115c */ ULONG g_elapsedTime = 0;
/* 00831160 */ ULONG g_elapsedTime2 = 0;
/* 00831164 */ BOOL g_bLaunchRunSonic = FALSE;
/* 00831168 */ HACCEL g_hAccel = 0;
/* 00831170 */ int g_nCmdShow = 0;
/* 00831174 */ int g_useModeX = 0;
/* 00831178 */ int g_noSoundEffect = 0;
/* 0083117c */ int g_midiFlag = 0;
/* 00831180 */ BOOL g_sonic3_alone = 0;
/* 00831184 */ int g_startGameMode = 0;
/* 0083118c */ BOOL g_bTrial = FALSE;
/* 00831188 */ int g_sonicGameMode = 0;
/* 00831190 */ int g_langMode = 0;
/* 00831194 */ int g_debug_mode = 0;
/* 00831198 */ BOOL g_bFullGameStage = FALSE;
/* 0083119c */ BOOL g_bDemo = FALSE;
/* 008311a0 */ // CGame g_game;
/* 00831368 */ int g_seMode;
/* 0083136c */ int g_bgmMode;
/* 00831374 */ int g_cdCheckEnable;
/* 00831370 */ HINSTANCE g_hInstance;
/* 00831378 */ char* g_lpCmdLine;
/* 008313c0 */ ULONG g_convertedHscrollbuff[224];
/* 00831740 */ ULONG g_spriteCnt;
/* 0083174c */ ULONG g_vscrollCopy;
/* 00831750 */ ULONG DAT_00831750;
/* 00854758 */ ULONG g_vdp_window_height;
/* 0085475c */ ULONG g_createFileError;
/* 00854760 */ ULONG g_vdp_scrollb_adr;
/* 00854768 */ ULONG g_mdVsram[20];
/* 008547bc */ ULONG DAT_008547bc;
/* 008547c4 */ ULONG* g_pConvertedHscrollbuff;
/* 008547d8 */ UCHAR g_spriteMasks[448];
/* 0085499c */ USHORT* g_pLevelSelectVram;
/* 008549a4 */ ULONG g_mdRegisterD0;
/* 008549cc */ ULONG g_vdp_scrolla_adr;
/* 008549d8 */ ULONG g_bg_color_index;
/* 008549dc */ BOOL g_vdp_hint_disabled;
/* 008549e0 */ UCHAR* g_pVdpReadPos;
/* 008549e4 */ UCHAR* g_pPixelBuffer;
/* 008549e8 */ BYTE g_saveFile[1024];
/* 00854de8 */ ULONG g_vdp_mode;
/* 00854dec */ BOOL g_vdp_hscroll_scanline;
/* 00854df0 */ Sprite g_sprites[80];
/* 00856df8 */ SHORT* g_pHscrollbuff;
/* 00856df0 */ ULONG g_vIntScanline;
/* 00856df4 */ ULONG DAT_00856df4;
/* 00856dfc */ SHORT* g_pHscrollbuff2;
/* 00856e00 */ ULONG g_vscrollPlaneB;
/* 00856e04 */ ULONG g_vscrollPlaneA;
/* 00856e08 */ BOOL g_bVscrollCopy;
/* 00856e0c */ // CGraphics* g_pGraphics;
/* 00856e10 */ BOOL BOOL_00856e10;
/* 00856e18 */ CRITICAL_SECTION g_CriticalSectionObj;
/* 00856e30 */ ULONG g_soundTest_bgmId;
/* 00856e34 */ // CSound* g_pSound;
/* 00856e38 */ ULONG g_soundTest_seId;
/* 00856e3c */ int g_bgmId;
/* 00856e40 */ // CSound* g_pSound2;
/* 00856e48 */ UCHAR g_kbKeysP1Down;
/* 00856e4c */ UCHAR g_kbKeysP2Down;
/* 00856e50 */ UCHAR DAT_00856e50;
/* 00856e54 */ UCHAR DAT_00856e54;
/* 00856e58 */ int g_kbKeys[2][5];
/* 00856e80 */ UCHAR g_joystick1ButtonsDown;
/* 00856e84 */ UCHAR g_joystick2ButtonsDown;
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
/* 08000000 */ // BYTE g_vram[0x10000];
/* 00831758 */ BYTE g_pixelBuffer[0x23000];
/* 08ff0000 */ // BYTE g_ram[0x0x10000];
