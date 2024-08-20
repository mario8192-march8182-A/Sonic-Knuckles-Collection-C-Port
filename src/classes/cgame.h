#ifndef CGAME_H
#define CGAME_H

#include <windows.h>

#define OPTIONS_FULLSCREEN 0
#define OPTIONS_HIDEMENUBAR 1
#define OPTIONS_ENABLEFRAMEDROP 2
#define OPTIONS_SHOWFRAMECOUNT 3
#define OPTIONS_ENABLEFRAMECAPTURE 4
#define OPTIONS_MUKAIDROPFRAME 5

class CGame {
  public:
  HWND getWindowHandle();
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  void readConfig();
  void FUN_00401a33();
  LRESULT realWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  BOOL loadMenu(HWND hWnd, LPARAM lParam);
  void freeResources(HWND hWnd);
  void quit(HWND hWnd);
  void FUN_00402070(HWND hWnd);
  void pause(BOOL bPause);
  void FUN_004021e0();
  void FUN_0040225a();
  void onCommand(HWND hWnd, ULONG id, HWND hControlWnd, ULONG code);
  void switchToFullScreen();
  void switchToWindowed();
  void onInitMenuPopup(HWND hWnd, HMENU hMenu, UINT pos, BOOL bIsWindowMenu);
  void onMenuSelect(HWND hWnd, HMENU hMenu, UINT idOrIndex, HMENU hSubMenu, UINT flags);
  void blitPausedMessage(HDC hDc, PAINTSTRUCT *pPaintStruct);
  int init();
  void showMessage(const char* pMessage);
  int initGraphics();
  int initSound();
  void resetVideo();
  void resetSound();
  void restartGameThread();
  int setupGameThread();
  int runGameThread();
  void terminateGameThread();
  void update();
  void updateScreen();
  void FUN_0040398b();

  private:
  int m_options[6];
  HWND m_hWnd;
  HMENU m_hMenu;
  HANDLE m_hGameThread;
  ULONG m_gameThreadId;
  HANDLE m_hEvent2;
  HANDLE m_hEvent3;
  ULONG m_unknown48;
  ULONG m_unknown52;
  BOOL m_bPaused;
  HANDLE m_hEvent1;
  HANDLE m_hDuplicate;
  ULONG m_unknown68;
  ULONG m_unknown72;
  ULONG m_systemTime;
  ULONG m_unknown80;
  BOOL m_bScreenshotKeyDown;
  ULONG m_screenshotId;
  ULONG m_unknown92[7];
  ULONG m_unknown120[7];
  ULONG m_unknown148;
  ULONG m_unknown152;
  ULONG m_unknown156;
  double m_unknown160;
  double m_unknown168;
  ULONG m_unknown176;
  ULONG m_unknown180;
  ULONG m_unknown184;
  ULONG m_unknown188;
  ULONG m_unknown192;
  ULONG m_unknown196;
  ULONG m_unknown2172;
  ULONG m_unknown2176;
};

#endif
