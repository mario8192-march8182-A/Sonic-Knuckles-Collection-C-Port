#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <mbstring.h>
#include "winresource.h"
#include "imidi.h"
#include "classes\cfile.h"
#include "classes\cgame.h"
#include "classes\cgraphics.h"
#include "classes\csound.h"
#include "classes\cwinregistry.h"

BOOL loadBgm(int id);
void initControls();
void playBgm();
void stopBgm();
void pauseBgm();

/* 0082b198 */ char g_s3kWindowTitle[19] = "Sonic 3 & Knuckles";
/* 0082b1ac */ char g_skWindowTitle[17] = "Sonic & Knuckles";
/* 0082b1c0 */ char g_s3WindowTitle[8] = "Sonic 3";
/* 0082b1c8 */ char g_s3kTrialWindowTitle[25] = "Sonic 3 & Knuckles Trial";
/* 0082b1e4 */ char g_skTrialWindowTitle[23] = "Sonic & Knuckles Trial";
/* 0082b1fc */ char g_s3TrialWindowTitle[14] = "Sonic 3 Trial";
/* 0082b20c */ char g_s3kDemoWindowTitle[24] = "Sonic 3 & Knuckles Demo";
/* 0082b224 */ char g_skDemoWindowTitle[22] = "Sonic & Knuckles Demo";
/* 0082b23c */ char g_s3DemoWindowTitle[13] = "Sonic 3 Demo";
/* 0082b24c */ char g_s3kDebugWindowTitle[27] = "Sonic 3 & Knuckles (Debug)";
/* 0082b268 */ char g_skDebugWindowTitle[25] = "Sonic & Knuckles (Debug)";
/* 0082b284 */ char g_s3DebugWindowTitle[16] = "Sonic 3 (Debug)";
/* 0082b2a0 */ char g_englishPausedText[26] = "<Pause> Push F3 to Resume";
/* 0082b2bc */ char g_frenchPausedText[30] = "Appuyez sur F3 pour continuer";
/* 0082b2dc */ char g_germanPausedText[25] =  "Drücke F3 für Neustart";
/* 0082b2f4 */ char g_spanishPausedText[33] = "<Pausa> Pulse F3  para Continuar";
/* 0082b318 */ char g_thanksForPlayingEnText1[58] = "Thanks for playing the The Best of Sonic Collection demo!";
/* 0082b354 */ char g_thanksForPlayingEnText2[67] = "We invite you to stop by our web-site (http://www.sega.com/segapc)";
/* 0082b398 */ char g_thanksForPlayingEnText3[66] = "to check out other Sega Entertainment demos, product information,";
/* 0082b3dc */ char g_thanksForPlayingEnText4[14] = "and contests.";
/* 0082b3ec */ char g_thanksForPlayingEnText5[1] = "";
/* 0082b3f0 */ char g_thanksForPlayingEnText6[68] = "If you have any comments or questions about this demo or other Sega";
/* 0082b434 */ char g_thanksForPlayingEnText7[67] = "Entertainment related product, please voice your opinions directly";
/* 0082b478 */ char g_thanksForPlayingEnText8[49] = "to our staff by e-mailing us at segapc@sega.com.";
/* 0082b4ac */ char g_thanksForPlayingEnText9[1] = "";
/* 0082b4b0 */ char g_thanksForPlayingEnText10[68] = "If you would like to order direct, please feel free by calling this";
/* 0082b4f4 */ char g_thanksForPlayingEnText11[67] = "toll-free number:  1-888-SEGA-SALES.  You can also find our entire";
/* 0082b538 */ char g_thanksForPlayingEnText12[60] = "PC product line at any participating software retail store.";
/* 0082b574 */ char g_thanksForPlayingEnText13[1] = "";
/* 0082b578 */ char g_thanksForPlayingEnText14[64] = "Again, thanks for playing!  Your friends at Sega Entertainment.";
/* 0082b5b8 */ UCHAR g_thanksForPlayingJpText1[28] = "SONIC & KNUCKLES COLLECTION";
/* 0082b5d4 */ UCHAR g_thanksForPlayingJpText2[1] = "";
/* 0082b5d8 */ UCHAR g_thanksForPlayingJpText3[42] = { 0x91, 0xCC, 0x8C, 0xB1, 0x94, 0xC5, 0x82, 0xC5, 0x82, 0xCC, 0x83, 0x76, 0x83, 0x8C, 0x83, 0x43, 0x82, 0xCD, 0x82, 0xA8, 0x8A, 0x79, 0x82, 0xB5, 0x82, 0xDD, 0x92, 0xB8, 0x82, 0xAF, 0x82, 0xDC, 0x82, 0xB5, 0x82, 0xBD, 0x82, 0xA9, 0x81, 0x48, 0x00 };
/* 0082b604 */ UCHAR g_thanksForPlayingJpText4[68] = { 0x90, 0xBB, 0x95, 0x69, 0x94, 0xC5, 0x82, 0xC5, 0x82, 0xCD, 0x81, 0x41, 0x82, 0xB1, 0x82, 0xCC, 0x8C, 0xE3, 0x82, 0xE0, 0x82, 0xB3, 0x82, 0xDC, 0x82, 0xB4, 0x82, 0xDC, 0x82, 0xC8, 0x83, 0x5D, 0x81, 0x5B, 0x83, 0x93, 0x82, 0xAA, 0x83, 0x5C, 0x83, 0x6A, 0x83, 0x62, 0x83, 0x4E, 0x82, 0xF0, 0x91, 0xD2, 0x82, 0xBF, 0x8E, 0xF3, 0x82, 0xAF, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x42, 0x00 };
/* 0082b648 */ UCHAR g_thanksForPlayingJpText5[73] = { 0x83, 0x4A, 0x83, 0x49, 0x83, 0x58, 0x83, 0x47, 0x83, 0x81, 0x83, 0x89, 0x83, 0x8B, 0x83, 0x68, 0x82, 0xF0, 0x82, 0xB7, 0x82, 0xD7, 0x82, 0xC4, 0x8F, 0x57, 0x82, 0xDF, 0x82, 0xC4, 0x81, 0x41, 0x44, 0x72, 0x2E, 0x83, 0x47, 0x83, 0x62, 0x83, 0x4F, 0x83, 0x7D, 0x83, 0x93, 0x82, 0xCC, 0x96, 0xEC, 0x96, 0x5D, 0x82, 0xF0, 0x91, 0x6A, 0x8E, 0x7E, 0x82, 0xB5, 0x82, 0xC4, 0x82, 0xAD, 0x82, 0xBE, 0x82, 0xB3, 0x82, 0xA2, 0x81, 0x49, 0x00 };
/* 0082b690 */ UCHAR g_thanksForPlayingJpText6[1] = "";
/* 0082b694 */ UCHAR g_thanksForPlayingJpText7[28] = { 0x81, 0xA1, 0x82, 0x50, 0x82, 0x58, 0x82, 0x58, 0x82, 0x56, 0x94, 0x4E, 0x81, 0x40, 0x82, 0x51, 0x8C, 0x8E, 0x94, 0xAD, 0x94, 0x84, 0x97, 0x5C, 0x92, 0xE8, 0x00 };
/* 0082b6b0 */ UCHAR g_thanksForPlayingJpText8[22] = { 0x81, 0xA1, 0x89, 0xBF, 0x8A, 0x69, 0x81, 0x40, 0x81, 0x8F, 0x82, 0x56, 0x81, 0x41, 0x82, 0x57, 0x82, 0x4F, 0x82, 0x4F, 0x00 };
/* 0082b6c8 */ UCHAR g_thanksForPlayingJpText9[1] = "";
/* 0082b6cc */ UCHAR g_thanksForPlayingJpText10[48] = { 0x90, 0xBB, 0x95, 0x69, 0x82, 0xCC, 0x82, 0xA8, 0x96, 0xE2, 0x82, 0xA2, 0x8D, 0x87, 0x82, 0xED, 0x82, 0xB9, 0x82, 0xCD, 0x81, 0x46, 0x82, 0x4F, 0x82, 0x53, 0x82, 0x56, 0x82, 0x52, 0x81, 0x7C, 0x82, 0x57, 0x82, 0x4F, 0x81, 0x7C, 0x82, 0x55, 0x82, 0x53, 0x82, 0x53, 0x82, 0x50, 0x00 };
/* 0082b6fc */ UCHAR g_thanksForPlayingJpText11[1] = "";
/* 0082b700 */ UCHAR g_thanksForPlayingJpText12[58] = { 0x83, 0x43, 0x83, 0x93, 0x83, 0x5E, 0x81, 0x5B, 0x83, 0x6C, 0x83, 0x62, 0x83, 0x67, 0x82, 0xE2, 0x83, 0x65, 0x83, 0x89, 0x83, 0x6C, 0x83, 0x62, 0x83, 0x67, 0x82, 0xC9, 0x82, 0xE0, 0x8F, 0xDA, 0x82, 0xB5, 0x82, 0xA2, 0x8F, 0xEE, 0x95, 0xF1, 0x82, 0xAA, 0x8D, 0xDA, 0x82, 0xC1, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x49, 0x00 };
/* 0082b73c */ UCHAR g_thanksForPlayingJpText13[55] = { 0x83, 0x43, 0x83, 0x93, 0x83, 0x5E, 0x81, 0x5B, 0x83, 0x6C, 0x83, 0x62, 0x83, 0x67, 0x81, 0x46, 0x20, 0x68, 0x74, 0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x77, 0x77, 0x77, 0x2E, 0x73, 0x65, 0x67, 0x61, 0x2E, 0x63, 0x6F, 0x2E, 0x6A, 0x70, 0x2F, 0x73, 0x65, 0x67, 0x61, 0x2F, 0x61, 0x74, 0x68, 0x6F, 0x6D, 0x65, 0x2F, 0x70, 0x63, 0x00 };
/* 0082b774 */ UCHAR g_thanksForPlayingJpText14[1] = "";
/* 0082b778 */ UCHAR g_thanksForPlayingJpText15[61] = { 0x83, 0x65, 0x83, 0x89, 0x83, 0x6C, 0x83, 0x62, 0x83, 0x67, 0x81, 0x46, 0x82, 0x4F, 0x82, 0x52, 0x81, 0x7C, 0x82, 0x54, 0x82, 0x56, 0x82, 0x4F, 0x82, 0x54, 0x81, 0x7C, 0x82, 0x56, 0x82, 0x53, 0x82, 0x52, 0x82, 0x50, 0x81, 0x60, 0x82, 0x52, 0x81, 0x40, 0x20, 0x32, 0x2C, 0x34, 0x30, 0x30, 0x81, 0x60, 0x32, 0x38, 0x2C, 0x38, 0x30, 0x30, 0x62, 0x70, 0x73, 0x00 };
/* 0082b7b4 */ UCHAR g_thanksForPlayingJpText16[43] = { 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x83, 0x5A, 0x83, 0x4B, 0x82, 0x6F, 0x82, 0x62, 0x83, 0x5C, 0x83, 0x74, 0x83, 0x67, 0x82, 0xCC, 0x95, 0x94, 0x89, 0xAE, 0x81, 0x69, 0x3B, 0x50, 0x43, 0x5F, 0x53, 0x81, 0x6A, 0x00 };
/* 0082b7e0 */ UCHAR g_thanksForPlayingJpText17[38] = { 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x81, 0x40, 0x81, 0x69, 0x83, 0x51, 0x83, 0x58, 0x83, 0x67, 0x49, 0x44, 0x81, 0x46, 0x82, 0x66, 0x82, 0x74, 0x82, 0x64, 0x82, 0x72, 0x82, 0x73, 0x81, 0x6A, 0x00 };
/* 0082b808 */ UCHAR g_thanksForPlayingJpText18[1] = "";
/* 0082b80c */ UCHAR g_thanksForPlayingJpText19[78] = { 0x83, 0x5A, 0x83, 0x4B, 0x82, 0x6F, 0x82, 0x62, 0x83, 0x5C, 0x83, 0x74, 0x83, 0x67, 0x82, 0xCD, 0x92, 0xCA, 0x94, 0xCC, 0x82, 0xC5, 0x82, 0xE0, 0x82, 0xA8, 0x8B, 0x81, 0x82, 0xDF, 0x82, 0xA2, 0x82, 0xBD, 0x82, 0xBE, 0x82, 0xAF, 0x82, 0xDC, 0x82, 0xB7, 0x81, 0x42, 0x93, 0x64, 0x98, 0x62, 0x94, 0xD4, 0x8D, 0x86, 0x81, 0x46, 0x82, 0x4F, 0x82, 0x50, 0x82, 0x51, 0x82, 0x4F, 0x81, 0x7C, 0x82, 0x54, 0x82, 0x54, 0x82, 0x55, 0x82, 0x4F, 0x82, 0x54, 0x82, 0x54, 0x00 };

/* 0082bad0 */ void* g_region8fe8000 = 0;
/* 0082bad4 */ void* g_region7ff8000 = 0;
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
/* 0082bb40 */ HRESULT(*g_pDdrawCreate)(GUID*, LPDIRECTDRAW*, IUnknown*) = 0;
/* 0082c868 */ HMODULE g_hMusicDll = 0;
/* 0082c86c */ IMidi* g_pMidiInterface = 0;
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
    0x44, /* D */
    0x58, /* X */
    0x56, /* V */
    0x43, /* C */
    0x41, /* A */
  }
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
/* 008311a0 */ CGame g_game;
/* 00831368 */ int g_seMode;
/* 0083136c */ int g_bgmMode;
/* 00831374 */ int g_cdCheckEnable;
/* 00831370 */ HINSTANCE g_hInstance;
/* 00831378 */ char* g_lpCmdLine;
/* 0085475c */ ULONG g_createFileError;
/* 008549a4 */ ULONG g_mdRegisterD0;
/* 008549d4 */ ULONG g_supplementaryMdRamAddress;
/* 008549e8 */ BYTE g_saveFile[1024];
/* 00856e0c */ CGraphics* g_pGraphics;
/* 00856e10 */ BOOL BOOL_00856e10;
/* 00856e18 */ CRITICAL_SECTION g_CriticalSectionObj;
/* 00856e30 */ ULONG g_soundTest_bgmId;
/* 00856e34 */ CSound* g_pSound;
/* 00856e38 */ ULONG g_soundTest_seId;
/* 00856e3c */ int g_bgmId;
/* 00856e40 */ CSound* g_pSound2;
/* 00856e58 */ int g_kbKeys[2][5];
/* 00856e88 */ int g_joystickId[2];
/* 00856e90 */ UINT g_joystickYCenter2[2];
/* 00856e98 */ UINT g_joystickXCenter1[2];
/* 00856ea0 */ UINT g_joystickXCenter2[2];
/* 00856ea8 */ BOOL g_joystickEnoughButtons[2];
/* 00856eb0 */ UINT g_joystickYCenter1[2];
/* 00856eb8 */ int g_selectKeyDialogCurrentKey;
/* 00856f40 */ int g_kbKeysEdit[2][5];
/* 08000000 */ BYTE g_mdVram[65536];
/* 00831758 */ BYTE g_mdSystemRam[143360];
/* 08ff0000 */ BYTE g_mdRam[65536];


// 004012a0
int handleAccelerator(MSG* pMsg) {
  return TranslateAccelerator(g_game.getWindowHandle(), g_hAccel, pMsg);
}


// 004012cb
BOOL stubbedFunction() {
  return TRUE;
}


// 004012e0
WPARAM handleMessages() {
  MSG msg;

  while (true) {
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) != 0) {
      if (msg.message == WM_QUIT) break;
      int result = handleAccelerator(&msg);
      if (result == 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    else {
      int result = stubbedFunction();
      if (result != 0) {
        WaitMessage();
      }
    }
  }

  return msg.wParam;
}


// 00401364
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow) {
  InitCommonControls();
  g_hInstance = hInstance;
  g_lpCmdLine = lpCmdLine;
  g_nCmdShow = nCmdShow;
  WPARAM ret = 1;
  g_hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(120));
  g_pGraphics = new CGraphics();
  g_pSound = new CSound();
  initControls();

  int errorCode = g_game.init();
  if (errorCode == 0) {
    handleMessages();
  }

  delete g_pSound;
  delete g_pGraphics;

  if (g_bLaunchRunSonic) {
    WinExec("RunSonic.exe", SW_SHOWNORMAL);
  }

  return ret;
}


// 00403d27
DWORD WINAPI gameThreadStartRoutine(void* pParameter) {
  // TODO
}


// 00403e00
int checkCd() {
  char driveStrings[256];
  char* pStrings;
  char buffer[256];
  OFSTRUCT ofStruct;

  if (GetLogicalDriveStrings(sizeof(driveStrings), driveStrings) == 0) {
    return 1;
  }

  pStrings = driveStrings;
  while (*pStrings != 0) {
    if (GetDriveType(pStrings) == DRIVE_CDROM) {
      _mbscpy((UCHAR*)buffer, (const UCHAR*)pStrings);
      strcat(buffer, "Game\\Sonic3K.exe");
      memset(&ofStruct, 0, sizeof(ofStruct));
      ofStruct.cBytes = sizeof(ofStruct);
      HFILE hFile = OpenFile(buffer, &ofStruct, OF_EXIST);
      if (hFile != HFILE_ERROR) {
        return 0;
      }
    }
    for ( ; *pStrings != 0; ++pStrings);
  }

  return 1;
}


// 004040ba
LRESULT CALLBACK thanksForPlayingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG: {
      HWND hMessageWnd = GetDlgItem(hWnd, ID_THANKSFORPLAYING_MESSAGE);
      SendMessage(hMessageWnd, WM_SETREDRAW, FALSE, 0);
      SendMessage(hMessageWnd, LB_RESETCONTENT, 0, 0);
      FILE* pFile = fopen("thanks.txt", "r");
      if (pFile != 0 && (int)pFile != -1) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), pFile) != 0) {
          for (int i = 0; i < sizeof(buffer) && buffer[i] != 0; ++i) {
            if (buffer[i] == '\n' || buffer[i] == '\r') {
              buffer[i] = 0;
            }
          }
          SendMessage(hMessageWnd, LB_ADDSTRING, 0, (LPARAM)buffer);
        }
        fclose(pFile);
      }
      else {
        char** ppThanksForPlayingText;
        if ((GetSystemDefaultLangID() & 0x3FF) == 17) {
          ppThanksForPlayingText = (char**)g_thanksForPlayingJpText;
        }
        else {
          ppThanksForPlayingText = g_thanksForPlayingEnText;
        }
        while (*ppThanksForPlayingText != 0) {
          SendMessage(hMessageWnd, LB_ADDSTRING, 0, (LPARAM)*ppThanksForPlayingText);
          ++ppThanksForPlayingText;
        }
      }
      SendMessage(hMessageWnd, WM_SETREDRAW, TRUE, 0);
      return TRUE;
    }
    case WM_COMMAND: {
      ULONG id = LOWORD(wParam);

      switch (id) {
        case ID_THANKSFORPLAYING_OK:
        case 2:
          EndDialog(hWnd, id);
          return 1;
      }
    }
  }

  return 0;
}


// 00404350
CGraphics* getGraphicsPtr() {
  return g_pGraphics;
}


// 00404390
CSound* getSoundPtr() {
  return g_pSound;
}


// 004043b0
int allocRamAndVram() {
  g_region8fe8000 = VirtualAlloc((void*)0x8FE8000, 0x20000, MEM_RESERVE, PAGE_READWRITE);
  if (g_region8fe8000 == 0) {
    return 1;
  }
  g_region8fe8000 = VirtualAlloc((void*)0x8FE8000, 0x20000, MEM_COMMIT, PAGE_READWRITE);
  if (g_region8fe8000 == 0) {
    return 1;
  }

  g_supplementaryMdRamAddress = 0x9000000;

  g_region7ff8000 = VirtualAlloc((void*)0x7FF8000, 0x20000, MEM_RESERVE, PAGE_READWRITE);
  if (g_region7ff8000 == 0) {
    return 1;
  }
  g_region7ff8000 = VirtualAlloc((void*)0x7FF8000, 0x20000, MEM_COMMIT, PAGE_READWRITE);
  if (g_region7ff8000 == 0) {
    return 1;
  }

  memset(g_mdRam, 0, 65536);
  memset(g_mdVram, 0, 65536);
  memset(g_mdSystemRam, 0, 143360);

  return 0;
}


// 004044d4
void freeRamAndVram() {
  if (g_region8fe8000 != 0) {
    VirtualFree(g_region8fe8000, 0x20000, MEM_DECOMMIT);
    VirtualFree(g_region8fe8000, 0, MEM_RELEASE);
    g_region8fe8000 = 0;
  }
  if (g_region7ff8000 != 0) {
    VirtualFree(g_region7ff8000, 0x20000, MEM_DECOMMIT);
    VirtualFree(g_region7ff8000, 0, MEM_RELEASE);
    g_region7ff8000 = 0;
  }
}


// 00404e0c
void readSaveFile() {
  memset(g_saveFile, 0, sizeof(g_saveFile));
  char fileName[256];
  GetModuleFileName(0, fileName, sizeof(fileName));
  _mbscpy((UCHAR*)&fileName[strlen(fileName) - 3], (UCHAR*)"BIN");
  HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    g_createFileError = GetLastError();
  }
  else {
    ULONG byteReadCnt;
    ReadFile(hFile, g_saveFile, sizeof(g_saveFile), &byteReadCnt, 0);
    CloseHandle(hFile);
  }
}


// 00404ece
void writeSaveFile() {
  char fileName[256];
  GetModuleFileName(0, fileName, sizeof(fileName));
  _mbscpy((UCHAR*)&fileName[strlen(fileName - 3)], (UCHAR*)"BIN");
  HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    MessageBox(0, "Cannot Open Save Data File", "Error", MB_OK);
    g_createFileError = GetLastError();
  }
  else {
    ULONG byteWriteCnt;
    WriteFile(hFile, g_saveFile, sizeof(g_saveFile), &byteWriteCnt, 0);
    if (byteWriteCnt != sizeof(g_saveFile)) {
      MessageBox(0, "Cannot Write Save Data File", "Error", MB_OK);
    }
    CloseHandle(hFile);
  }
}


// 0040632a
void saveControlsConfig(const char* pPublisherKeyName, const char* pGameKeyName, const char* pControllerKeyName, int* pConfig, ULONG size) {
  CWinRegistry registry(pPublisherKeyName);
  registry.openSubKey(pGameKeyName);
  registry.setKeyBinary(pControllerKeyName, (BYTE*)pConfig, size);
}


// 004063cd
void loadControlsConfig(const char* pPublisherKeyName, const char* pGameKeyName, const char* pControllerKeyName, int* pConfig, ULONG size) {
  CWinRegistry registry(pPublisherKeyName);
  registry.openSubKey(pGameKeyName);
  registry.queryKeyBytes(pControllerKeyName, (BYTE*)pConfig, size);
}


// 0040ab4e
void playSoundEffect() {
  short mdRegisterD0 = g_mdRegisterD0 & 0xFFFF;
  if (mdRegisterD0 < 0) {
    mdRegisterD0 += 256;
  }
  if (mdRegisterD0 < 0 || mdRegisterD0 > 223) return;

  int bufferId = g_soundBufferMapping[mdRegisterD0];
  if (bufferId < 1) return;

  CSound* pSound = getSoundPtr();
  if (pSound == 0) return;
  if (pSound->getUnknown2060() != 0) return;

  int zeroBasedBufferId = bufferId - 1;
  if (pSound->getSoundBuffer(zeroBasedBufferId) == 0) return;
  pSound->playBuffer(zeroBasedBufferId);
}


// 0040ac1d
void FUN_0040ac1d() {
  BOOL_00856e10 = FALSE;
  g_bgmId = -1;
  getSoundPtr()->FUN_0040a697();
}


// 0040aea5
void startBgm(char id) {
  EnterCriticalSection(&g_CriticalSectionObj);
  if (loadBgm(id + 1) != 0) {
    playBgm();
  }
  LeaveCriticalSection(&g_CriticalSectionObj);
}


// 0040aee7
void restartBgm() {
  if (BOOL_00856e10) {
    if (g_bgmId > 0) {
      EnterCriticalSection(&g_CriticalSectionObj);
      if (loadBgm((g_bgmId & 0xFF) + 1)) {
        playBgm();
      }
      LeaveCriticalSection(&g_CriticalSectionObj);
    }
    BOOL_00856e10 = FALSE;
  }
}


// 0040af4f
void initSound(HWND hWnd) {
  if (g_midiFlag != 0) {
    g_hMusicDll = LoadLibrary("MidiOut.dll");
    if (g_hMusicDll == 0) {
      g_hMusicDll = LoadLibrary("Bgm.dll");
    }
  }
  else {
    g_hMusicDll = LoadLibrary("Bgm.dll");
    if (g_hMusicDll == 0) {
      g_hMusicDll = LoadLibrary("MidiOut.dll");
    }
  }
  if (g_hMusicDll != 0) {
    IMidi*(*pGetMidiInterface)() = (IMidi*(*)())GetProcAddress(g_hMusicDll, "GetMidiInterface");
    if (pGetMidiInterface != 0) {
      g_pMidiInterface = (*pGetMidiInterface)();
    }
  }

  CSound* pSound = getSoundPtr();
  if (pSound != 0 && pSound->initSound(hWnd) == 0) {
    char fileName[256];
    GetModuleFileName(0, fileName, sizeof(fileName));
    _mbscpy((UCHAR*)&fileName[strlen(fileName) - 3], (UCHAR*)"ds2");
    pSound->loadSoundEffects(fileName, 4, 0, 133);
  }
}


// 0040b099
LRESULT CALLBACK soundTestDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG: {
      g_soundTest_seId = 0;
      g_soundTest_bgmId = 0;
      POINT topLeft;
      topLeft.x = 0;
      topLeft.y = 0;
      ClientToScreen(hWnd, &topLeft);
      RECT windowRect;
      GetWindowRect(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN), &windowRect);
      DestroyWindow(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN));
      CreateUpDownControl(UDS_WRAP | UDS_ARROWKEYS | UDS_HORZ | UDS_NOTHOUSANDS | WS_VISIBLE | WS_CHILD, windowRect.left - topLeft.x,windowRect.top - topLeft.y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, hWnd, ID_SOUNDTEST_SE_UPDOWN, g_hInstance, 0, 0, 100, 0);
      GetWindowRect(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN), &windowRect);
      DestroyWindow(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN));
      CreateUpDownControl(UDS_WRAP | UDS_ARROWKEYS | UDS_HORZ | UDS_NOTHOUSANDS | WS_VISIBLE | WS_CHILD, windowRect.left - topLeft.x,windowRect.top - topLeft.y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, hWnd, ID_SOUNDTEST_BGM_UPDOWN, g_hInstance, 0, 0, 100, 0);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN), UDM_SETRANGE, 0, 168);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN), UDM_SETPOS, 0, 0);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN), UDM_SETRANGE, 0, 55);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN), UDM_SETPOS, 0, 0);
      return TRUE;
    }
    case WM_COMMAND: {
      HWND hControlWnd = (HWND)lParam;
      ULONG id = LOWORD(wParam);
      ULONG code = HIWORD(wParam);

      switch (id) {
        case ID_SOUNDTEST_SE_PLAY:
          if (code & 0xFFFF) {
            return 0;
          }
          g_mdRegisterD0 = g_soundTest_seId + 51;
          playSoundEffect();
          return 1;
        case ID_SOUNDTEST_BGM_PLAY:
          if (code & 0xFFFF) {
            return 0;
          }
          startBgm(g_soundTest_bgmId);
          return 1;
        case ID_SOUNDTEST_BGM_STOP:
          if (code & 0xFFFF) {
            return 0;
          }
          stopBgm();
          return 1;
        case ID_SOUNDTEST_OK:
          if (code & 0xFFFF) {
            return 0;
          }
          EndDialog(hWnd, 1);
          return 1;
        case 2:
          if (code & 0xFFFF) {
            return 0;
          }
          EndDialog(hWnd, 2);
          return 1;
      }
    }
    case WM_HSCROLL: {
      ULONG request = LOWORD(wParam);
      ULONG pos = HIWORD(wParam);
      HWND hScrollBar = (HWND)lParam;
      if (GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN) == hScrollBar) {
        if (request == SB_THUMBPOSITION || request == SB_THUMBTRACK) {
          g_soundTest_seId = pos;
          char buffer[64];
          wsprintf(buffer, "No. %03d", g_soundTest_seId);
          SetDlgItemText(hWnd, ID_SOUNDTEST_SE_NO, buffer);
        }
        return 1;
      }
      if (GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN) == hScrollBar) {
        if (request == SB_THUMBPOSITION || request == SB_THUMBTRACK) {
          g_soundTest_bgmId = pos;
          char buffer[64];
          wsprintf(buffer, "No. %03d", g_soundTest_bgmId);
          SetDlgItemText(hWnd, ID_SOUNDTEST_BGM_NO, buffer);
        }
        return 1;
      }
    }
  }

  return 0;
}


// 0040b54c
int openSoundTestDialog(HWND hWnd) {
  BOOL_00856e10 = FALSE;
  stopBgm();
  ULONG mdRegisterD0Backup = g_mdRegisterD0;
  int ret = DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_SOUNDTEST_BASE + g_langMode), hWnd, (DLGPROC)soundTestDlgProc, 0);
  BOOL_00856e10 = TRUE;
  restartBgm();
  pauseBgm();
  g_mdRegisterD0 = mdRegisterD0Backup;

  return ret;
}


// 0040b5bb
void initMidiInterface(HWND hWnd) {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->init(hWnd);
  }
}


// 0040b5eb
BOOL loadBgm(int id) {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->loadSong(id, g_bgmMode != 1);
  }

  return TRUE;
}


// 0040b62e
void playBgm() {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->playSong();
  }
}


// 0040b65b
void stopBgm() {
  EnterCriticalSection(&g_CriticalSectionObj);
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->stopSong();
  }
  LeaveCriticalSection(&g_CriticalSectionObj);
}


// 0040b69e
void pauseBgm() {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->pauseSong();
  }
}


// 0040b6cb
void resumeBgm() {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->resumeSong();
  }
}


// 0040b800
CFile* readInt(CFile* pFile, ULONG* pBuffer) {
  pFile->readData(pBuffer, 4);
  return pFile;
}


// 0040bacd
int configureJoystick(ULONG index) {
  JOYCAPS joycaps;

  if (g_joystickId[index] == -1) {
    return 0;
  }

  memset(&joycaps, 0, sizeof(joycaps));
  MMRESULT result = joyGetDevCaps(g_joystickId[index], &joycaps, sizeof(joycaps));
  if (result != JOYERR_NOERROR) {
    g_joystickId[index] = -1;
    return 1;
  }

  UINT stickXCenter1 = (joycaps.wXmax - joycaps.wXmin) / 2;
  UINT stickYCenter1 = (joycaps.wYmax - joycaps.wYmin) / 2;
  UINT stickXCenter2 = (joycaps.wXmax - joycaps.wXmin) / 8;
  UINT stickYCenter2 = (joycaps.wYmax - joycaps.wYmin) / 8;
  g_joystickXCenter1[index] = stickXCenter1 - stickXCenter2;
  g_joystickXCenter2[index] = stickXCenter2 + stickXCenter1;
  g_joystickYCenter1[index] = stickYCenter1 - stickYCenter2;
  if (joycaps.wMaxButtons >= 4) {
    g_joystickEnoughButtons[index] = TRUE;
  }
  else {
    g_joystickEnoughButtons[index] = FALSE;
  }

  return 0;
}


// 0040bc1e
void initControls() {
  for (int i = 0; i < 5; ++i) {
    g_kbKeys[0][i] = g_defaultKbKeys[0][i];
    g_kbKeys[1][i] = g_defaultKbKeys[1][i];
  }

  loadControlsConfig("SEGA", "Sonic3K", "KeyBind", (int*)g_kbKeys, sizeof(g_kbKeys));
  g_joystickId[0] = -1;
  g_joystickId[1] = -1;
  loadControlsConfig("SEGA", "Sonic3K", "PadBind", g_joystickId, sizeof(g_joystickId));
  configureJoystick(0);
  configureJoystick(1);
}


// 0040c86d
void readKeyName(char* pKeyName, int key) {
  for (int i = 0; g_kbKeyCodes[i] >= 0; ++i) {
    if (g_kbKeyCodes[i] == key) {
      _mbscpy((UCHAR*)pKeyName, (const UCHAR*)g_kbKeyNames[g_langMode][i]);
      return;
    }
  }

  if ((key >= 48 && key <= 57) || (key >= 65 && key <= 90)) {
    pKeyName[0] = (char)key;
    pKeyName[1] = 0;
  }
  else {
    _mbscpy((UCHAR*)pKeyName, (const UCHAR*)"NoKey");
  }
}


// 0040ccc3
int openSelectKeyDialog(HWND hWnd, int currentKey) {
  g_selectKeyDialogCurrentKey = currentKey;
  return DialogBoxParam(g_hInstance, 116 + g_langMode, hWnd, FUN_0040ca13, 0);
}


// 0040ccfe
int validateKeyBinding() {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (g_kbKeysEdit[1][j] == g_kbKeysEdit[0][i] || g_kbKeysEdit[1][i] == g_kbKeysEdit[0][j]) {
        return 1;
      }
      if (i == j) continue;
      if (g_kbKeysEdit[0][j] == g_kbKeysEdit[0][i] || g_kbKeysEdit[1][j] == g_kbKeysEdit[1][i]) {
        return 1;
      }
    }
  }

  return 0;
}


// 0040cddc
LRESULT CALLBACK keyBindDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG: {
      char keyName[32];
      for (int i = 0; i < 5; ++i) {
        g_kbKeysEdit[0][i] = g_kbKeys[0][i];
        readKeyName(keyName, g_kbKeysEdit[0][i]);
        SetDlgItemText(hWnd, ID_KEYBIND_PL1_BUTTON_FIRST + i, keyName);
        g_kbKeysEdit[1][i] = g_kbKeys[1][i];
        readKeyName(keyName, g_kbKeysEdit[1][i]);
        SetDlgItemText(hWnd, ID_KEYBIND_PL2_BUTTON_FIRST + i, keyName);
      }
      return TRUE;
    }
    case WM_COMMAND: {
      HWND hControlWnd = (HWND)lParam;
      ULONG id = LOWORD(wParam);
      ULONG code = HIWORD(wParam);

      switch (id) {
        case ID_KEYBIND_OK:
          if (code & 0xFFFF) {
            return 0;
          }
          if (validateKeyBinding() != 0) {
            MessageBox(hWnd, "Illegal Key Binding", "Key Bind", MB_OK);
            return 1;
          }
          for (int i = 0; i < 5; ++i) {
            g_kbKeys[0][i] = g_kbKeysEdit[0][i];
            g_kbKeys[1][i] = g_kbKeysEdit[1][i];
          }
          saveControlsConfig("SEGA", "Sonic3K", "KeyBind", (int*)g_kbKeys, sizeof(g_kbKeys));
          EndDialog(hWnd, ID_KEYBIND_OK);
          return 1;
        case ID_KEYBIND_CANCEL:
          if (code & 0xFFFF) {
            return 0;
          }
          EndDialog(hWnd, ID_KEYBIND_CANCEL);
          return 1;
        case ID_KEYBIND_RESTORE: {
          if (code & 0xFFFF) {
            return 0;
          }
          char keyName[32];
          for (int i = 0; i < 5; ++i) {
            g_kbKeysEdit[0][i] = g_kbKeys[0][i];
            readKeyName(keyName, g_kbKeysEdit[0][i]);
            SetDlgItemText(hWnd , ID_KEYBIND_PL1_BUTTON_FIRST + i, keyName);
            g_kbKeysEdit[1][i] = g_kbKeys[1][i];
            readKeyName(keyName, g_kbKeysEdit[1][i]);
            SetDlgItemText(hWnd, ID_KEYBIND_PL2_BUTTON_FIRST + i, keyName);
          }
          return 1;
        }
        default:
          if (id >= ID_KEYBIND_PL1_BUTTON_FIRST && id <= ID_KEYBIND_PL1_BUTTON_LAST) {
            int selectedKey = openSelectKeyDialog(hWnd, ((int*)g_kbKeysEdit)[id - 1000]);
            if (selectedKey >= 0) {
              ((int*)g_kbKeysEdit)[id - 1000] = selectedKey;
              char keyName[32];
              readKeyName(keyName, ((int*)g_kbKeysEdit)[id - 1000]);
              SetDlgItemText(hWnd, id, keyName);
            }
            return 1;
          }
          if (id >= ID_KEYBIND_PL2_BUTTON_FIRST && id <= ID_KEYBIND_PL2_BUTTON_LAST) {
            int selectedKey = openSelectKeyDialog(hWnd, ((int*)g_kbKeysEdit)[id - 1000]);
            if (selectedKey >= 0) {
              ((int*)g_kbKeysEdit)[id - 1000] = selectedKey;
              char keyName[32];
              readKeyName(keyName, ((int*)g_kbKeysEdit)[id - 1000]);
              SetDlgItemText(hWnd, id, keyName);
            }
            return 1;
          }
      }
    }
  }

  return 0;
}


// 0040d20d
void openKeyBindDialog(HWND hWnd) {
  DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_KEYBIND_BASE + g_langMode), hWnd, (DLGPROC)soundTestDlgProc, 0);
}

// 0040d802
void openUseJoyStickDialog(HWND hWnd) {
  DialogBoxParam(g_hInstance, MAKEINTRESOURCE(108 + g_langMode), hWnd, FUN_0040d240, 0);
}
