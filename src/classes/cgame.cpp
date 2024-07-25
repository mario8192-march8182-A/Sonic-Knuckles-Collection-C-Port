#include <windows.h>
#include <mbstring.h>
#include "cgame.h"
#include "cgraphics.h"
#include "cinifile.h"
#include "cwinregistry.h"

extern DWORD WINAPI gameThreadStartRoutine(void* pParameter);
extern int checkCd();
extern CGraphics* getGraphicsPtr();
extern int allocRamAndVram();
extern void readSaveFile();
extern void FUN_0040ac1d();
extern void initSound(HWND hWnd);

extern char* g_windowTitles[3];
extern char* g_trialWindowTitles[3];
extern char* g_demoWindowTitles[3];
extern char* g_debugWindowTitles[3];
extern int g_nCmdShow;
extern int g_useModeX;
extern int g_noSoundEffect;
extern int g_midiFlag;
extern int g_sonic3Alone;
extern int DAT_00831184;
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
    m_config[i] = 0;
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

  m_config[2] = iniFile.getInt("EnableFrameDrop", 1);
  m_config[3] = iniFile.getInt("ShowFrameCount", 0);
  m_config[4] = iniFile.getInt("EnableFrameCapture", 1);
  m_config[5] = iniFile.getInt("MukaiDropFrame", 1);
  g_debugMode = iniFile.getInt("DebugMode", 0);
  g_useModeX = iniFile.getInt("UseModeX", g_useModeX);
  g_noSoundEffect = iniFile.getInt("NoSoundEffect", g_noSoundEffect);
  iniFile.readInt("BGMMode", &g_bgmMode, g_bgmMode);
  iniFile.readInt("SonicGameMode", &g_sonicGameMode, 0);
  if (g_bgmMode < 0 || g_bgmMode > 2) {
    g_bgmMode = 1;
  }
  if (g_debugMode != 0) {
    DAT_00831184 = 2;
  }
  else {
    DAT_00831184 = 0;
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
  m_unknown84 = 0;
  m_unknown88 = 0;

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
    g_sonic3Alone = 1;
  }
  else {
    g_sonic3Alone = 0;
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
    g_sonic3Alone = 0;
  }
}


// 00401afc
LRESULT CGame::realWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  // TODO
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
  m_unknown56 = m_unknown52;
  m_unknown48 = m_unknown56;
  BOOL_00831198 = FALSE;
  ::FUN_0040ac1d();
  ::readSaveFile();
  m_unknown68 = 0;

  return 0;
}


// 00402fea
int CGame::runGameThread() {
  if (ResumeThread(m_hGameThread) == -1) {
    showMessage("Cannot Run GameThread.");
    return 1;
  }

  return 0;
}
