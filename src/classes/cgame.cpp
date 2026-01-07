#include <stdio.h>
#include <windows.h>
#include <mbstring.h>
#include "../winresource.h"
#include "cgame.h"
#include "cgraphics.h"
#include "cinifile.h"
#include "csound.h"
#include "cwinregistry.h"
#include "../vdp.h"

extern int FUN_00401000();
extern DWORD WINAPI gameThreadStartRoutine(void* pParameter);
extern int checkCd();
extern LRESULT CALLBACK thanksForPlayingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern CGraphics* getGraphicsPtr();
extern CSound* getSoundPtr();
extern int allocRamAndVram();
extern void freeRamAndVram();
extern void readSaveFile();
extern void writeSaveFile();
extern void blitGraphics();
extern void FUN_0040ac1d();
extern void resetSound();
extern void restartBgm();
extern void initSound(HWND hWnd);
extern int openSoundTestDialog(HWND hWnd);
extern void pauseBgm();
extern void resumeBgm();
extern void openKeyBindDialog(HWND hWnd);
extern void openJoyStickDialog(HWND hWnd);

extern BOOL BOOL_0082b040;
extern char* g_windowTitles[3];
extern char* g_trialWindowTitles[3];
extern char* g_demoWindowTitles[3];
extern char* g_debugWindowTitles[3];
extern char* g_pausedText[4];
extern ULONG g_lastDAT_0082b074;
extern ULONG g_lastDAT_0082b07c;
extern BOOL g_bLaunchRunSonic;
extern int g_nCmdShow;
extern int g_useModeX;
extern int g_noSoundEffect;
extern int g_midiFlag;
extern bool g_sonic3_alone;
extern int g_startGameMode;
extern BOOL g_bTrial;
extern int g_sonicGameMode;
extern int g_langMode;
extern int g_debugMode;
extern BOOL BOOL_00831198;
extern BOOL g_bDemo;
extern CGame g_game;
extern int g_seMode;
extern int g_bgmMode;
extern int g_cdCheckEnable;
extern HINSTANCE g_hInstance;
extern char* g_lpCmdLine;
extern ULONG DAT_00854de8;
extern CRITICAL_SECTION g_CriticalSectionObj;


// 00401420
HWND CGame::getWindowHandle() {
  return m_hWnd;
}


// 0040146f
LRESULT CALLBACK CGame::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  return g_game.realWndProc(hWnd, msg, wParam, lParam);
}


// 004014fa
void CGame::readConfig() {
  for (int i = 0; i < 6; ++i) {
    m_options[i] = 0;
  }

  CWinRegistry registry("Sonic3K");
  registry.openSubKey("Options");
  g_bgmMode = 1;
  registry.queryKeyDword("BGMMode", (DWORD*)&g_bgmMode);
  g_seMode = 2;
  registry.queryKeyDword("SEMode", (DWORD*)&g_seMode);
  g_noSoundEffect = 0;
  registry.queryKeyDword("NoSoundEffect", (DWORD*)&g_noSoundEffect);
  g_useModeX = 1;
  registry.queryKeyDword("UseModeX", (DWORD*)&g_useModeX);

  CIniFile iniFile("S3K.INI", 0);
  iniFile.setSection("Debug");

  m_options[OPTIONS_ENABLEFRAMEDROP] = iniFile.getInt("EnableFrameDrop", 1);
  m_options[OPTIONS_SHOWFRAMECOUNT] = iniFile.getInt("ShowFrameCount", 0);
  m_options[OPTIONS_ENABLEFRAMECAPTURE] = iniFile.getInt("EnableFrameCapture", 1);
  m_options[OPTIONS_MUKAIDROPFRAME] = iniFile.getInt("MukaiDropFrame", 1);
  g_debugMode = iniFile.getInt("DebugMode", 0);
  g_useModeX = iniFile.getInt("UseModeX", g_useModeX);
  g_noSoundEffect = iniFile.getInt("NoSoundEffect", g_noSoundEffect);
  iniFile.readInt("BGMMode", &g_bgmMode, g_bgmMode);
  iniFile.readInt("SonicGameMode", &g_sonicGameMode, 0);
  if (g_bgmMode < 0 || g_bgmMode > 2) {
    g_bgmMode = 1;
  }
  if (g_debugMode != 0) {
    g_startGameMode = 2;
  }
  else {
    g_startGameMode = 0;
  }
  if (g_noSoundEffect != 0) {
    g_seMode = 0;
  }
  else {
    g_seMode = 2;
  }

  g_cdCheckEnable = iniFile.getInt("CDCheckEnable", 1);
  iniFile.readInt("LangMode", &g_langMode, -1);
  if (g_langMode < 0 || g_langMode > 3) {
    UINT langId = GetSystemDefaultLangID() & 0x3FF;
    switch (langId) {
      case 12:
        g_langMode = 1;
        break;
      case 7:
        g_langMode = 2;
        break;
      case 10:
        g_langMode = 3;
        break;
      default:
        g_langMode = 0;
        break;
    }
  }

  iniFile.readInt("MIDIFlag", &g_midiFlag, 1);
  m_bScreenshotKeyDown = FALSE;
  m_screenshotId = 0;

  InitializeCriticalSection(&g_CriticalSectionObj);
  DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &m_hDuplicate, 0, FALSE, DUPLICATE_SAME_ACCESS);

  char buffer[256];
  _mbscpy((UCHAR*)buffer, (const UCHAR*)g_lpCmdLine);
  CharLower(buffer);
  if (strcmp(buffer, "-3") == 0) {
    g_sonicGameMode = 2;
  }
  else if (strcmp(buffer, "-k") == 0) {
    g_sonicGameMode = 1;
  }
  if (g_sonicGameMode < 0 || g_sonicGameMode > 2) {
    g_sonicGameMode = 0;
  }
  if (g_sonicGameMode == 2) {
    g_sonic3_alone = true;
  }
  else {
    g_sonic3_alone = false;
  }

  int gameMode;
  iniFile.readInt("GameMode", &gameMode, 0);
  if (gameMode == 1) {
    g_bDemo = TRUE;
    g_bTrial = FALSE;
  }
  else if (gameMode == 2) {
    g_bDemo = FALSE;
    g_bTrial = TRUE;
  }
  else {
    g_bDemo = FALSE;
    g_bTrial = FALSE;
  }
  if (g_bTrial) {
    g_sonicGameMode = 0;
    g_sonic3_alone = false;
  }
}


// 00401a33
void CGame::FUN_00401a33() {
  if (m_hGameThread == 0) return;
  CGraphics* pGraphics = getGraphicsPtr();
  if (pGraphics == 0) return;
  if (pGraphics->getUnknown2168()) return;
  if (m_options[OPTIONS_FULLSCREEN] != 0) return;
  FUN_004021e0();
  if (pGraphics->initVideo(pGraphics->getVideoMode(), m_hWnd) != 0) {
    char buffer[256];
    pGraphics->readMessage(buffer);
    showMessage(buffer);
  }
  FUN_0040225a();
}


// 00401afc
LRESULT CGame::realWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_PAINT: {
      PAINTSTRUCT paintStruct;
      HDC hDc = BeginPaint(hWnd, &paintStruct);
      blitPausedMessage(hDc, &paintStruct);
      EndPaint(hWnd, &paintStruct);
      return 0;
    }
    case WM_CREATE:
      if (loadMenu(hWnd, lParam) != 0) {
        return 0;
      }
      return -1;
    case WM_CLOSE:
      freeResources(hWnd);
      return 0;
    case WM_DESTROY:
      quit(hWnd);
      return 0;
    case WM_COMMAND:
      onCommand(hWnd, LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
      return 0;
    case WM_INITMENUPOPUP:
      onInitMenuPopup(hWnd, (HMENU)wParam, LOWORD(lParam), (BOOL)HIWORD(lParam));
      return 0;
    case WM_MENUSELECT: {
      UINT flags;
      if ((short)HIWORD(wParam) == -1) {
        flags = -1;
      }
      else {
        flags = HIWORD(wParam);
      }
      HMENU hSubMenu;
      if (HIWORD(wParam) & 16) {
        hSubMenu = GetSubMenu((HMENU)lParam, LOWORD(wParam));
      }
      else {
        hSubMenu = 0;
      }
      onMenuSelect(hWnd, (HMENU)lParam, LOWORD(wParam), hSubMenu, flags);
      return 0;
    }
    case WM_QUERYNEWPALETTE:
      FUN_00401a33();
      break;
    case WM_ENDSESSION:
      if (wParam != 0) {
        PostMessage(hWnd, WM_CLOSE, 0, 0);
      }
      break;
    case WM_SYSCOMMAND:
      if ((wParam & 0xFFF0) == SC_SCREENSAVE) {
        return 0;
      }
      break;
    case WM_KEYDOWN:
      if ((HIWORD(lParam) & KF_REPEAT) == 0 && wParam == VK_F9) {
        m_bScreenshotKeyDown = TRUE;
      }
      break;
    case WM_ACTIVATEAPP:
      if (wParam == FALSE) {
        pause(TRUE);
        return 0;
      }
      break;
    case 0x464:
      ::restartBgm();
      return 0;
    case WM_WINDOWPOSCHANGING: {
      WINDOWPOS* pWindowPos = (WINDOWPOS*)lParam;
      RECT rect;
      if (pWindowPos->cx > 560 && pWindowPos->cy > 420) {
        SetRect(&rect, 0, 0, 640, 480);
      }
      else {
        SetRect(&rect, 0, 0, 320, 240);
      }
      AdjustWindowRectEx(&rect, GetWindowLong(m_hWnd, GWL_STYLE), m_options[OPTIONS_HIDEMENUBAR] == 0, GetWindowLong(m_hWnd, GWL_EXSTYLE));
      pWindowPos->cx = rect.right - rect.left;
      pWindowPos->cy = rect.bottom - rect.top;
      break;
    }
    case WM_SETCURSOR:
      if (m_options[OPTIONS_FULLSCREEN] != 0) {
        SetCursor(0);
        return TRUE;
      }
      break;
    case 0x46E:
      int fullScreenBackup = m_options[OPTIONS_FULLSCREEN];
      pause(TRUE);
      if (fullScreenBackup != 0) {
        switchToWindowed();
      }
      DialogBoxParam(g_hInstance, MAKEINTRESOURCE(122), m_hWnd, (DLGPROC)thanksForPlayingDlgProc, 0);
      if (fullScreenBackup != 0) {
        switchToFullScreen();
      }
      g_startGameMode = 0;
      restartGameThread();
      return 0;
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}


// 00401f9b
BOOL CGame::loadMenu(HWND hWnd, LPARAM lParam) {
  m_hMenu = LoadMenu(g_hInstance, MAKEINTRESOURCE(IDM_BASE + g_langMode));

  if (g_debugMode == 0) {
    HMENU hSubMenu = GetSubMenu(m_hMenu, 1);
    DeleteMenu(hSubMenu, 5, MF_BYPOSITION);
    DeleteMenu(hSubMenu, 5, MF_BYPOSITION);
    DeleteMenu(hSubMenu, 5, MF_BYPOSITION);
  }

  if (g_bDemo != 0 || g_bTrial != 0) {
    EnableMenuItem(GetSubMenu(m_hMenu, 0), ID_SPECIALSTAGEMODE, MF_GRAYED);
  }

  SetMenu(hWnd, m_hMenu);

  return TRUE;
}


// 00402070
void CGame::freeResources(HWND hWnd) {
  terminateGameThread();
  if (m_hDuplicate != 0) {
    CloseHandle(m_hDuplicate);
    m_hDuplicate = 0;
  }
  resetVideo();
  resetSound();
  ::freeRamAndVram();
  DestroyWindow(hWnd);
}


// 004020d3
void CGame::quit(HWND hWnd) {
  WinHelp(hWnd, "Sonic.hlp", HELP_QUIT, 0);
  SetMenu(hWnd, 0);
  DestroyMenu(m_hMenu);
  PostQuitMessage(0);
}


// 00402120
void CGame::pause(BOOL bPause) {
  if ((m_hEvent1 != 0 || m_hEvent2 != 0) && m_bPaused != bPause) {
    if (m_bPaused) {
      m_bPaused = FALSE;
      ::resumeBgm();
      SetEvent(m_hEvent1);
    }
    else {
      FUN_0040225a();
      ResetEvent(m_hEvent2);
      m_bPaused = TRUE;
      WaitForSingleObject(m_hEvent2, 200);
      ::pauseBgm();
      InvalidateRect(m_hWnd, 0, FALSE);
    }
  }
}


// 004021e0
void CGame::FUN_004021e0() {
  if ((m_hEvent3 != 0 || m_hEvent2 != 0) && m_bPaused == FALSE && m_unknown48 == 0) {
    ResetEvent(m_hEvent2);
    m_unknown48 = 1;
    WaitForSingleObject(m_hEvent2, -1);
  }
}


// 0040225a
void CGame::FUN_0040225a() {
  if (m_hEvent3 != 0 || m_hEvent2 != 0) {
    if (m_bPaused || m_unknown48 == 0) return;
    m_unknown48 = 0;
    SetEvent(m_hEvent3);
  }
}


// 004022c5
void CGame::onCommand(HWND hWnd, ULONG id, HWND hControlWnd, ULONG code) {
  switch (id) {
    case ID_PAUSE:
      pause(m_bPaused == FALSE);
      break;
    case ID_EXIT:
      pause(TRUE);
      PostMessage(hWnd, WM_CLOSE, 0, 0);
      break;
    case ID_RESTARTGAME:
      g_startGameMode = 0;
      restartGameThread();
      break;
    case ID_RESET:
      pause(TRUE);
      g_bLaunchRunSonic = TRUE;
      PostMessage(hWnd, WM_CLOSE, 0, 0);
      break;
    case ID_SPECIALSTAGEMODE:
      g_startGameMode = 1;
      restartGameThread();
      break;
    case ID_OPTIONS_FULLSCREEN:
      if (m_options[OPTIONS_FULLSCREEN] != 0) {
        switchToWindowed();
      }
      else {
        switchToFullScreen();
      }
      break;
    case ID_OPTIONS_CHANGECONTROLS:
      if (m_options[OPTIONS_FULLSCREEN] == 0) {
        pause(TRUE);
        ::openKeyBindDialog(hWnd);
      }
      break;
    case ID_OPTIONS_USEJOYSTICK:
      if (m_options[OPTIONS_FULLSCREEN] == 0) {
        pause(TRUE);
        ::openJoyStickDialog(hWnd);
      }
      break;
    case ID_OPTIONS_SOUNDTEST:
      if (m_options[OPTIONS_FULLSCREEN] == 0) {
        pause(TRUE);
        openSoundTestDialog(hWnd);
      }
      break;
    case ID_OPTIONS_MENUBAR: {
      if (m_options[OPTIONS_FULLSCREEN] != 0) break;
      pause(TRUE);
      if (m_options[OPTIONS_HIDEMENUBAR] != 0) {
        m_options[OPTIONS_HIDEMENUBAR] = 0;
      }
      else {
        m_options[OPTIONS_HIDEMENUBAR] = 1;
      }
      RECT rect;
      GetClientRect(m_hWnd, &rect);
      if (m_options[OPTIONS_HIDEMENUBAR] != 0) {
        SetMenu(m_hWnd, 0);
      }
      else {
        SetMenu(m_hWnd, m_hMenu);
        DrawMenuBar(m_hWnd);
      }
      AdjustWindowRectEx(&rect, GetWindowLong(m_hWnd, GWL_STYLE), m_options[OPTIONS_HIDEMENUBAR] == 0, GetWindowLong(m_hWnd, GWL_EXSTYLE));
      SetWindowPos(m_hWnd, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
      RedrawWindow(m_hWnd, 0, 0, RDW_FRAME);
      break;
    }
    case ID_OPTIONS_ENABLEFRAMEDROP:
      if (m_options[OPTIONS_ENABLEFRAMEDROP] != 0) {
        m_options[OPTIONS_ENABLEFRAMEDROP] = 0;
      }
      else {
        m_options[OPTIONS_ENABLEFRAMEDROP] = 1;
      }
      if (m_options[OPTIONS_ENABLEFRAMEDROP] == 0) {
        m_unknown68 = 0;
      }
      break;
    case ID_OPTIONS_SHOWFRAMERATE:
      if (m_options[OPTIONS_SHOWFRAMECOUNT] != 0) {
        m_options[OPTIONS_SHOWFRAMECOUNT] = 0;
      }
      else {
        m_options[OPTIONS_SHOWFRAMECOUNT] = 1;
      }
      break;
    case ID_HELP_CONTENTS:
      WinHelp(hWnd, "Sonic.hlp", HELP_CONTENTS, 0);
      break;
    case ID_HELP_HOWTOPLAY:
      WinHelp(hWnd, "Sonic.hlp", HELP_CONTEXT, 100);
      break;
    case ID_HELP_CONTROLS:
      WinHelp(hWnd, "Sonic.hlp", HELP_CONTEXT, 101);
      break;
    case ID_HELP_HOTLINE:
      WinHelp(hWnd, "Sonic.hlp", HELP_CONTEXT, 102);
      break;
    case ID_HELP_HOWTOUSE:
      WinHelp(hWnd, "WinHelp.hlp", HELP_CONTENTS, 0);
      break;
  }
}


// 004026ac
void CGame::switchToFullScreen() {
  FUN_004021e0();
  CGraphics* pGraphics = getGraphicsPtr();
  if (pGraphics->canCreateDdrawInstance() == FALSE) return;
  if (pGraphics->initVideo(5, m_hWnd) != 0) {
    char buffer[256];
    pGraphics->readMessage(buffer);
    showMessage(buffer);
  }
  else {
    m_options[OPTIONS_FULLSCREEN] = 1;
    pGraphics->clearBuffers();
  }

  SetCursor(0);
  SetMenu(m_hWnd, 0);
  FUN_0040225a();
}


// 0040276b
void CGame::switchToWindowed() {
  FUN_004021e0();
  CGraphics* pGraphics = getGraphicsPtr();
  if (pGraphics->stubbedMethod() == 0) return;

  if (pGraphics->initVideo(1, m_hWnd) != 0) {
    char buffer[256];
    pGraphics->readMessage(buffer);
    showMessage(buffer);
  }
  else {
    m_options[OPTIONS_FULLSCREEN] = 0;
    pGraphics->clearBuffers();
  }

  if (m_options[OPTIONS_HIDEMENUBAR] != 0) {
    SetMenu(m_hWnd, 0);
  }
  else {
    SetMenu(m_hWnd, m_hMenu);
    DrawMenuBar(m_hWnd);
    RECT rect;
    AdjustWindowRectEx(&rect, GetWindowLong(m_hWnd, GWL_STYLE), m_options[OPTIONS_HIDEMENUBAR] == 0, GetWindowLongA(m_hWnd, GWL_EXSTYLE));
    SetWindowPos(m_hWnd, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
    RedrawWindow(m_hWnd, 0, 0, RDW_FRAME);
  }

  HCURSOR hCursor = LoadCursor(0, IDC_ARROW);
  SetCursor(hCursor);
  FUN_0040225a();
}


// 00402902
void CGame::onInitMenuPopup(HWND hWnd, HMENU hMenu, UINT pos, BOOL bIsWindowMenu) {
  FUN_004021e0();
  if (bIsWindowMenu) return;

  switch (pos) {
    case 0:
      CheckMenuItem(hMenu, ID_PAUSE, m_bPaused ? MF_CHECKED : MF_UNCHECKED);
      break;
    case 1:
      CheckMenuItem(hMenu, ID_OPTIONS_ENABLEFRAMEDROP, m_options[OPTIONS_ENABLEFRAMEDROP] ? MF_CHECKED : MF_UNCHECKED);
      CheckMenuItem(hMenu, ID_OPTIONS_SHOWFRAMERATE, m_options[OPTIONS_SHOWFRAMECOUNT] ? MF_CHECKED : MF_UNCHECKED);
      break;
  }
}


// 004029ca
void CGame::onMenuSelect(HWND hWnd, HMENU hMenu, UINT idOrIndex, HMENU hSubMenu, UINT flags) {
  if (hMenu == 0 && flags == (UINT)-1) {
    FUN_0040225a();
  }
}


// 004029fe
void CGame::blitPausedMessage(HDC hDc, PAINTSTRUCT *pPaintStruct) {
  if (m_bPaused == FALSE) return;

  if (m_options[OPTIONS_FULLSCREEN] != 0) {
    CGraphics* pGraphics = ::getGraphicsPtr();
    if (pGraphics != 0) {
      pGraphics->blitPausedMessage();
    }
  }
  else {
    char* pPausedText = g_pausedText[g_langMode];
    RECT rect;
    GetClientRect(m_hWnd, &rect);
    PatBlt(hDc, 0, 0, rect.right, rect.bottom, BLACKNESS);
    SIZE size;
    GetTextExtentPoint32(hDc, pPausedText, strlen(pPausedText), &size);
    SetTextColor(hDc, RGB(255, 255, 255));
    SetBkColor(hDc, RGB(0, 0, 0));
    SetBkMode(hDc, TRANSPARENT);
    TextOut(hDc, (rect.right - size.cx) / 2, (rect.bottom - size.cy) / 2, pPausedText, strlen(pPausedText));
  }
}


// 00402b06
int CGame::init() {
  if (FindWindow("SonicWndClass", 0) != 0) {
    showMessage("Already Run.");
    return 1;
  }

  if (::allocRamAndVram() != 0) {
    showMessage("Cannot Allocate Memory.");
    return 1;
  }

  readConfig();
  if (g_cdCheckEnable && !g_bDemo && !g_bTrial && ::checkCd() != 0) {
    showMessage("Please insert a Sonic & Knuckles Collection CD-ROM");
    return 1;
  }

  WNDCLASS wndClass;
  /* WS_EX_DLGMODALFRAME (0x1) | ???(0x2) | WS_EX_TOPMOST(0x8) | WS_EX_RTLREADING (0x2000) */
  wndClass.style = 0x200b;
  wndClass.lpfnWndProc = WndProc;
  wndClass.cbClsExtra = 0;
  wndClass.cbWndExtra = 0;
  wndClass.hInstance = g_hInstance;
  wndClass.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(121));
  wndClass.hCursor = LoadCursor(0, IDC_ARROW);
  wndClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
  wndClass.lpszMenuName = 0;
  wndClass.lpszClassName = "SonicWndClass";
  RegisterClass(&wndClass);

  if (g_debugMode != 0) {
    m_hWnd = CreateWindowEx(0, "SonicWndClass", g_debugWindowTitles[g_sonicGameMode], WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CAPTION, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, g_hInstance, 0);
  }
  else {
    char* pWindowTitle = g_windowTitles[g_sonicGameMode];
    if (g_bDemo) {
      pWindowTitle = g_demoWindowTitles[g_sonicGameMode];
    }
    if (g_bTrial) {
      pWindowTitle = g_trialWindowTitles[g_sonicGameMode];
    }
    m_hWnd = CreateWindowEx(0, "SonicWndClass", pWindowTitle, WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CAPTION, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, g_hInstance, 0);
  }
  if (m_hWnd != 0) {
    if (initGraphics() == 0 && initSound() == 0 && setupGameThread() == 0) {
      ShowWindow(m_hWnd, g_nCmdShow);
      UpdateWindow(m_hWnd);
      if (runGameThread() == 0) {
        return 0;
      }
    }
    DestroyWindow(m_hWnd);
  }

  return 1;
}


// 00402dbf
void CGame::showMessage(const char* pMessage) {
  MessageBox(m_hWnd, pMessage, "Sonic & Knuckles Collection", MB_ICONSTOP);
}


// 00402def
int CGame::initGraphics() {
  CGraphics* pGraphics = ::getGraphicsPtr();
  if (pGraphics->initVideo(1, m_hWnd) != 0) {
    char buffer[128];
    pGraphics->readMessage(buffer);
    showMessage(buffer);
    return 1;
  }

  pGraphics->clearBuffers();

  return 0;
}


// 00402e64
int CGame::initSound() {
  ::initSound(m_hWnd);

  return 0;
}


// 00402e8b
void CGame::resetVideo() {
  CGraphics* pGraphics = ::getGraphicsPtr();
  pGraphics->resetVideo();
}


// 00402eb1
void CGame::resetSound() {
  CSound* pSound = ::getSoundPtr();
  pSound->resetSound();
}


// 00402ed7
void CGame::restartGameThread() {
  terminateGameThread();
  if (setupGameThread() != 0) return;
  runGameThread();
}


// 00402f12
int CGame::setupGameThread() {
  m_hEvent1 = CreateEvent(0, TRUE, FALSE, 0);
  m_hEvent2 = CreateEvent(0, TRUE, FALSE, 0);
  m_hEvent3 = CreateEvent(0, TRUE, FALSE, 0);
  m_hGameThread = CreateThread(0, 0, ::gameThreadStartRoutine, 0, CREATE_SUSPENDED, &m_gameThreadId);
  if (m_hGameThread == 0) {
    showMessage("Cannot Create GameThread.");
    return 1;
  }

  m_unknown52 = 0;
  m_bPaused = m_unknown52;
  m_unknown48 = m_bPaused;
  BOOL_00831198 = FALSE;
  ::resetSound();
  ::readSaveFile();
  m_unknown68 = 0;

  return 0;
}


// 00402fea
int CGame::runGameThread() {
  if (ResumeThread(m_hGameThread) == (DWORD)-1) {
    showMessage("Cannot Run GameThread.");
    return 1;
  }

  return 0;
}


// 0040302f
void CGame::terminateGameThread() {
  if (m_hGameThread != 0) {
    FUN_0040225a();
    pause(FALSE);
    m_unknown52 = 1;
    WaitForSingleObject(m_hGameThread, -1);
    CloseHandle(m_hGameThread);
    m_hGameThread = 0;
    m_gameThreadId = 0;
  }
  if (m_hEvent1 != 0) {
    CloseHandle(m_hEvent1);
  }
  if (m_hEvent2 != 0) {
    CloseHandle(m_hEvent2);
  }
  if (m_hEvent3 != 0) {
    CloseHandle(m_hEvent3);
  }
  writeSaveFile();
  CSound* pSound = ::getSoundPtr();
  pSound->stopSoundEffects();
}


// 00403101
void CGame::update() {
  if (BOOL_00831198) {
    BOOL_00831198 = FALSE;
    if (g_bTrial != 0) {
      PostMessage(m_hWnd, 0x46E, 0, 0);
    }
  }

  if(m_unknown52 != 0) {
    ExitThread(0);
  }

  if (m_bPaused) {
    ResetEvent(m_hEvent1);
    SetEvent(m_hEvent2);
    WaitForSingleObject(m_hEvent1, -1);
  }

  if (m_unknown48 != 0) {
    ResetEvent(m_hEvent3);
    SetEvent(m_hEvent2);
    WaitForSingleObject(m_hEvent3, -1);
  }

  CSound* pSound = getSoundPtr();
  pSound->playSoundEffects();

  ULONG systemTime = timeGetTime();
  if (m_unknown68 != 0) {
    ++m_unknown68;
  }
  else {
    m_unknown68 = 1;
    m_unknown176 = 0;
    m_unknown72 = 999;
    m_systemTime = systemTime;
    m_unknown80 = m_unknown68;
  }

  if (m_options[OPTIONS_ENABLEFRAMEDROP] != 0) {
    if (m_options[OPTIONS_MUKAIDROPFRAME] != 0) {
      FUN_0040398b();
    }
    else {
      while (::FUN_00401000() != 0) {
        Sleep(1);
      }
    }
  }
  else {
    if (m_systemTime - systemTime > 1000) {
      double result = (m_unknown68 - m_unknown80) * 1000.0 / (systemTime - m_systemTime);
      if (result > 99.0) {
        result = 99.0;
      }
      result += 0.05;
      result *= 10.0;
      m_unknown72 = result;
      m_systemTime = systemTime;
      m_unknown80 = m_unknown68;
    }
    BOOL_0082b040 = TRUE;
  }

  if (m_options[OPTIONS_MUKAIDROPFRAME] != 0) {
    if (m_unknown196 == 0) {
      ::blitGraphics();
      updateScreen();
    }
  }
  else if (BOOL_0082b040) {
    ::blitGraphics();
    updateScreen();
  }
}


// 0040336e
void CGame::updateScreen() {
  CGraphics* pGraphics = getGraphicsPtr();
  BYTE* pSurface;
  long pitch;
  if (pGraphics->lockBuffer((void**)&pSurface, &pitch) != 0) return;

  if (g_debugMode != 0) {
    if (g_useModeX == 0 && pGraphics->getVideoMode() & 4) {
      for (int i = 0; i < 32; ++i) {
        memset(&pSurface[i * pitch], 0, 640);
      }
      if (DAT_00854de8 == 5) {
        ::FUN_0040fd4f((unsigned long*)&pSurface[32 * pitch], pitch);
      }
      else {
        ::FUN_0040f96a((unsigned long*)&pSurface[32 * pitch], pitch);
      }
    }
    else {
      for (int i = 0; i < 16; ++i) {
        memset(&pSurface[i * pitch], 0, 320);
      }
      if (DAT_00854de8 == 5) {
        ::FUN_0040fceb((unsigned long*)&pSurface[16 * pitch], pitch);
      }
      else {
        ::FUN_0040f89b((unsigned long*)&pSurface[16 * pitch], pitch);
      }
    }
  }
  else {
    if (g_useModeX == 0 && pGraphics->getVideoMode() & 4) {
      for (int i = 0; i < 16; ++i) {
        memset(&pSurface[i * pitch], 0, 640);
      }
      for (int i = 0; i < 16; ++i) {
        memset(&pSurface[(240 + i) * pitch], 0, 640);
      }
      if (DAT_00854de8 == 5) {
        ::FUN_0040fd4f((unsigned long*)&pSurface[16 * pitch], pitch);
      }
      else {
        ::FUN_0040f96a((unsigned long*)&pSurface[16 * pitch], pitch);
      }
    }
    else {
      for (int i = 0; i < 8; ++i) {
        memset(&pSurface[i * pitch], 0, 320);
      }
      for (int i = 0; i < 8; ++i) {
        memset(&pSurface[(232 + i) * pitch], 0, 320);
      }
      if (DAT_00854de8 == 5) {
        ::FUN_0040fceb((unsigned long*)&pSurface[8 * pitch], pitch);
      }
      else {
        ::FUN_0040f89b((unsigned long*)&pSurface[8 * pitch], pitch);
      }
    }
  }

  pGraphics->unlockBuffer();

  if (m_options[OPTIONS_ENABLEFRAMECAPTURE] != 0 && m_bScreenshotKeyDown) {
    CScreenshot screenshot;
    pGraphics->readScreenshotData(screenshot);
    char fileName[256];
    wsprintf(fileName, "Cap%05d.bmp", m_screenshotId);
    ++m_screenshotId;
    if (m_screenshotId >= 100000) {
      m_screenshotId = 0;
    }
    screenshot.save(fileName);
    m_bScreenshotKeyDown = FALSE;
  }

  if (m_options[OPTIONS_SHOWFRAMECOUNT] != 0) {
    char frameCount[128];
    if (m_options[OPTIONS_ENABLEFRAMEDROP] != 0) {
      if (m_options[OPTIONS_MUKAIDROPFRAME] != 0) {

        sprintf(frameCount, "%5.1f/%5.1f [F/s] %5.1f [%%]", m_unknown160, m_unknown168, m_unknown160 * 100.0 / m_unknown168);
      }
      else {
        long unknown = (g_lastDAT_0082b074 * 1000.0) / g_lastDAT_0082b07c;
        wsprintf(frameCount, "%03ld/%03ld [F/s] %03d.%01d [%%]", g_lastDAT_0082b074, g_lastDAT_0082b07c, unknown / 10, unknown % 10);
      }
    }
    else {
      wsprintf(frameCount, "%02ld.%01ld [F/s]", m_unknown72 / 10, m_unknown72 % 10);
    }

    HDC hDc;
    if (pGraphics->getBackBufferDc(&hDc) == 0) {
      SetTextColor(hDc, RGB(255, 255, 255));
      SetBkColor(hDc, RGB(0, 0, 0));
      SetBkMode(hDc, OPAQUE);
      SIZE size;
      GetTextExtentPoint32(hDc, frameCount, strlen(frameCount), &size);
      RECT rect;
      SetRect(&rect, 0, 0, size.cx, size.cy);
      ExtTextOut(hDc, rect.left, rect.top, ETO_OPAQUE, &rect, frameCount, strlen(frameCount), 0);
      pGraphics->releaseBackBufferDc(hDc);
    }
  }

  pGraphics->blit();
}


// 0040398b
void CGame::FUN_0040398b() {
  ULONG systemTime = timeGetTime();
  if (m_unknown176 == 0) {
    m_unknown176 = 1;
    m_unknown180 = 0;
    m_unknown184 = m_unknown180;
    m_unknown188 = 0;
    m_unknown192 = 0;

    for (int i = 0; i < 7; ++i) {
      m_unknown92[i] = systemTime;
      m_unknown120[i] = 0;
    }

    m_unknown148 = systemTime;
    m_unknown168 = 99.9;
    m_unknown160 = m_unknown168;
    m_unknown156 = m_unknown152;
  }
  else {
    ++m_unknown176;

    for (int i = 1; i < 7; ++i) {
      m_unknown92[i - 1] = m_unknown92[i];
    }

    m_unknown92[6] = systemTime;
    m_unknown120[6] = 0;
  }

  m_unknown196 = 0;
  BOOL bUnknown;
  if (m_unknown92[6] - m_unknown92[0] > 100) {
    bUnknown = TRUE;
  }
  else {
    bUnknown = FALSE;
  }
  if (bUnknown) {
    if (m_unknown192 >= 2) {
      bUnknown = FALSE;
    }
    else if (m_unknown120[5] == 1 && m_unknown120[4] == 0 && m_unknown120[3] == 1) {
      bUnknown = FALSE;
    }
  }
  if (bUnknown) {
    m_unknown188 = 1;
    ++m_unknown192;
    ++m_unknown180;
    m_unknown196 = 1;
    m_unknown120[6] = 1;
  }
  else {
    m_unknown188 = 0;
    m_unknown192 = 0;
    ++m_unknown184;
  }

  if (systemTime - m_unknown148 <= 1000) {
    m_unknown160 = (m_unknown184 - m_unknown156) * 1000.0 / (systemTime - m_unknown148);
    if (m_unknown160 > 99.0) {
      m_unknown160 = 99.0;
    }
    m_unknown168 = (m_unknown176 - m_unknown152) * 1000.0 / (systemTime - m_unknown148);
    if (m_unknown160 > 99.0) {
      m_unknown160 = 99.0;
    }
    m_unknown148 = systemTime;
    m_unknown152 = m_unknown176;
    m_unknown156 = m_unknown184;
  }
}
