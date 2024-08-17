#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include <windows.h>
#include <ddraw.h>
#include <dsound.h>
#include "constants.h"
#include "types/sonic3ram.h"

extern char* g_windowTitles[3];
extern char* g_trialWindowTitles[3];
extern char* g_demoWindowTitles[3];
extern char* g_debugWindowTitles[3];
extern char* g_pausedText[4];
extern char* g_thanksForPlayingEnText[16];
extern UCHAR* g_thanksForPlayingJpText[20];
extern void* g_region8fe8000;
extern void* g_region7ff8000;
extern HRESULT(*g_pDdrawCreate)(GUID*, LPDIRECTDRAW*, IUnknown*);
extern HMODULE g_hMusicDll;
extern HRESULT(*g_pDSoundCreate)(GUID*, LPDIRECTSOUND*, LPUNKNOWN*);
extern int g_soundBufferMapping[224];
extern ULONG DAT_0082ddc8;
extern char g_kbKeyNames[4][30][32];
extern int g_kbKeyCodes[30];
extern int g_defaultKbKeys[2][5];
extern char* g_dontUseText[4];
extern BOOL g_bLaunchRunSonic;
extern HACCEL g_hAccel;
extern int g_nCmdShow;
extern int g_useModeX;
extern int g_noSoundEffect;
extern int g_midiFlag;
extern int g_sonic3Alone;
extern int g_startGameMode;
extern BOOL g_bTrial;
extern int g_sonicGameMode;
extern int g_langMode;
extern int g_debugMode;
extern BOOL BOOL_00831198;
extern BOOL g_bDemo;
extern int g_seMode;
extern int g_bgmMode;
extern int g_cdCheckEnable;
extern HINSTANCE g_hInstance;
extern char* g_lpCmdLine;
extern ULONG g_convertedHscrollbuff[224];
extern ULONG g_vscrollCopy;
extern ULONG DAT_00854758;
extern ULONG g_createFileError;
extern ULONG DAT_00854760;
extern ULONG g_mdVsram[20];
extern ULONG* g_pConvertedHscrollbuff;
extern USHORT* g_pLevelSelectVram;
extern ULONG g_mdRegisterD0;
extern ULONG g_supplementaryMdRamAddress;
extern ULONG DAT_008549cc;
extern ULONG DAT_008549d8;
extern UCHAR* g_pVdpReadPos;
extern UCHAR* g_pPixelBuffer;
extern BYTE g_saveFile[1024];
extern ULONG DAT_00854dec;
extern ULONG g_vIntScanline;
extern ULONG DAT_00856df4;
extern BOOL BOOL_00856e10;
extern CRITICAL_SECTION g_CriticalSectionObj;
extern ULONG g_soundTest_bgmId;
extern ULONG g_soundTest_seId;
extern int g_bgmId;
extern int g_kbKeys[2][5];
extern int g_joystickId[2];
extern UINT g_joystickYCenter2[2];
extern UINT g_joystickXCenter1[2];
extern UINT g_joystickXCenter2[2];
extern BOOL g_joystickEnoughButtons[2];
extern UINT g_joystickYCenter1[2];
extern int g_selectKeyDialogCurrentKey;
extern BOOL g_joystickAvailability[32];
extern int g_kbKeysEdit[2][5];
extern UINT g_joystickCnt;
extern BYTE g_mdVram[0x10000];
extern BYTE g_pixelBuffer[0x23000];
extern sonic3_ram g_mdRam;
extern USHORT g_systemPalette[64];

#endif
