#include <windows.h>
#include <commctrl.h>
#include <mbstring.h>
#include "classes\cfile.h"
#include "classes\cgame.h"
#include "classes\cgraphics.h"
#include "classes\csound.h"
#include "classes\cwinregistry.h"

void initControls();

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
/* 0082bb40 */ HRESULT(*g_pDdrawCreate)(GUID*, LPDIRECTDRAW*, IUnknown*) = 0;
/* 0082c868 */ HMODULE g_hMusicDll = 0;
/* 0082c86c */ FARPROC g_pMidiInterface = 0;
/* 0082c870 */ HRESULT(*g_pDSoundCreate)(GUID*, LPDIRECTSOUND*, LPUNKNOWN*) = 0;
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
/* 00831164 */ BOOL BOOL_00831164 = FALSE;
/* 00831168 */ HACCEL g_hAccel = 0;
/* 00831170 */ int g_nCmdShow = 0;
/* 00831174 */ int g_useModeX = 0;
/* 00831178 */ int g_noSoundEffect = 0;
/* 0083117c */ int g_midiFlag = 0;
/* 00831180 */ int g_sonic3Alone = 0;
/* 00831184 */ int DAT_00831184 = 0;
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
/* 008549d4 */ ULONG g_supplementaryMdRamAddress;
/* 008549e8 */ BYTE g_saveFile[1024];
/* 00856e0c */ CGraphics* g_pGraphics;
/* 00856e10 */ BOOL BOOL_00856e10;
/* 00856e18 */ CRITICAL_SECTION g_CriticalSectionObj;
/* 00856e34 */ CSound* g_pSound;
/* 00856e3c */ long DAT_00856e3c;
/* 00856e40 */ CSound* g_pSound2;
/* 00856e58 */ int g_kbKeys[2][5];
/* 00856e88 */ int g_joystickId[2];
/* 00856e90 */ UINT g_joystickYCenter2[2];
/* 00856e98 */ UINT g_joystickXCenter1[2];
/* 00856ea0 */ UINT g_joystickXCenter2[2];
/* 00856ea8 */ BOOL g_joystickEnoughButtons[2];
/* 00856eb0 */ UINT g_joystickYCenter1[2];
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

  if (BOOL_00831164) {
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


// 004063cd
void loadControlsConfig(const char* pPublisherKeyName, const char* pGameKeyName, const char* pControllerKeyName, int* pConfig, ULONG size) {
  CWinRegistry registry(pPublisherKeyName);
  registry.openSubKey(pGameKeyName);
  registry.queryKeyBytes(pControllerKeyName, (BYTE*)pConfig, size);
}


// 0040ac1d
void FUN_0040ac1d() {
  BOOL_00856e10 = FALSE;
  DAT_00856e3c = -1;
  getSoundPtr()->FUN_0040a697();
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
    FARPROC pGetMidiInterface = GetProcAddress(g_hMusicDll, "GetMidiInterface");
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


// 0040b5bb
void initMidiInterface(HWND hWnd) {
  if (g_pMidiInterface != 0) {
    (*g_pMidiInterface)(hWnd);
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
