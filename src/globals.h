#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include <windows.h>
#include <ddraw.h>
#include <dsound.h>
#include "constants.h"
#include "types/sonic3ram.h"
#include "types/sprite.h"

extern ULONG DAT_00829058[10];
extern double DAT_00829080;
extern double DAT_00829088;
extern BOOL BOOL_0082b040;
extern BOOL BOOL_0082b044;
extern ULONG g_lastSystemTime;
extern ULONG g_lastSystemTime2;
extern ULONG g_lastSystemTime3;
extern ULONG DAT_0082b054;
extern ULONG g_cumulativeElapsedTime;
extern ULONG DAT_0082b070;
extern ULONG DAT_0082b074;
extern ULONG DAT_0082b078;
extern ULONG DAT_0082b07c;
extern ULONG DAT_0082b088;
extern long DAT_0082b098;
extern char* g_windowTitles[3];
extern char* g_trialWindowTitles[3];
extern char* g_demoWindowTitles[3];
extern char* g_debugWindowTitles[3];
extern char* g_pausedText[4];
extern BOOL g_bResetMdRam;
extern char* g_thanksForPlayingEnText[16];
extern UCHAR* g_thanksForPlayingJpText[20];
extern void* g_region8fe8000;
extern void* g_region7ff8000;
extern HRESULT(*g_pDdrawCreate)(GUID*, LPDIRECTDRAW*, IUnknown*);
extern HMODULE g_hMusicDll;
extern HRESULT(*g_pDSoundCreate)(GUID*, LPDIRECTSOUND*, LPUNKNOWN*);
extern int g_soundBufferMapping[224];
extern int g_unknownSoundMapping[224];
extern int g_unknownSoundMapping2[224];
extern int g_unknownSoundMapping3[224];
extern int g_soundFrequencies[20];
extern ULONG g_unknownSoundFrequencyValue;
extern int g_soundMapping[51];
extern ULONG DAT_0082ddc8;
extern UCHAR DAT_0082ddcc[4];
extern char g_kbKeyNames[4][30][32];
extern int g_kbKeyCodes[30];
extern int g_defaultKbKeys[2][5];
extern unsigned char g_prevMdButtonsP1Down;
extern unsigned char g_prevMdButtonsP2Down;
extern char* g_dontUseText[4];
extern ULONG DAT_00831140;
extern ULONG g_elapsedTime3;
extern ULONG g_systemTime;
extern ULONG g_lastDAT_0082b074;
extern double DAT_00831150;
extern ULONG g_lastDAT_0082b07c;
extern ULONG g_elapsedTime;
extern ULONG g_elapsedTime2;
extern BOOL g_bLaunchRunSonic;
extern HACCEL g_hAccel;
extern int g_nCmdShow;
extern int g_useModeX;
extern int g_noSoundEffect;
extern int g_midiFlag;
extern BOOL g_sonic3_alone;
extern int g_startGameMode;
extern BOOL g_bTrial;
extern int g_sonicGameMode;
extern int g_langMode;
extern int g_debug_mode;
extern BOOL BOOL_00831198;
extern BOOL g_bDemo;
extern int g_seMode;
extern int g_bgmMode;
extern int g_cdCheckEnable;
extern HINSTANCE g_hInstance;
extern char* g_lpCmdLine;
extern ULONG g_convertedHscrollbuff[224];
extern ULONG g_spriteCnt;
extern ULONG g_vscrollCopy;
extern ULONG DAT_00831750;
extern ULONG DAT_00854758;
extern ULONG g_createFileError;
extern ULONG g_vdpScrollPlaneBOffset;
extern ULONG g_mdVsram[20];
extern ULONG DAT_008547bc;
extern ULONG* g_pConvertedHscrollbuff;
extern UCHAR g_spriteMasks[448];
extern USHORT* g_pLevelSelectVram;
extern ULONG g_mdRegisterD0;
extern ULONG g_vdpScrollPlaneAOffset;
extern ULONG DAT_008549d8;
extern ULONG DAT_008549dc;
extern UCHAR* g_pVdpReadPos;
extern UCHAR* g_pPixelBuffer;
extern BYTE g_saveFile[1024];
extern ULONG DAT_00854de8;
extern ULONG DAT_00854dec;
extern Sprite g_sprites[80];
extern USHORT* g_pHscrollbuff;
extern ULONG g_vIntScanline;
extern ULONG DAT_00856df4;
extern USHORT* g_pHscrollbuff2;
extern ULONG g_vscrollPlaneB;
extern ULONG g_vscrollPlaneA;
extern BOOL g_bVscrollCopy;
extern BOOL BOOL_00856e10;
extern CRITICAL_SECTION g_CriticalSectionObj;
extern ULONG g_soundTest_bgmId;
extern ULONG g_soundTest_seId;
extern int g_bgmId;
extern UCHAR g_kbKeysP1Down;
extern UCHAR g_kbKeysP2Down;
extern UCHAR DAT_00856e50;
extern UCHAR DAT_00856e54;
extern int g_kbKeys[2][5];
extern UCHAR g_joystick1ButtonsDown;
extern UCHAR g_joystick2ButtonsDown;
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
extern BYTE g_vram[0x10000];
extern BYTE g_pixelBuffer[0x23000];
extern sonic3_ram g_ram;

#endif
