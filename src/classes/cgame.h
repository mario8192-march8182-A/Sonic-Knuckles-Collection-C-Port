#ifndef CGAME_H
#define CGAME_H

#include <windows.h>

class CGame {
  public:
  HWND getWindowHandle();
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  void readConfig();
  LRESULT realWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  int init();
  void showMessage(const char* pMessage);
  int initGraphics();
  int initSound();
  int setupGameThread();
  int runGameThread();

  private:
  int m_config[6];
  HWND m_hWnd;
  ULONG m_unknown28;
  HANDLE m_hGameThread;
  ULONG m_gameThreadId;
  HANDLE m_hEvent2;
  HANDLE m_hEvent3;
  ULONG m_unknown48;
  ULONG m_unknown52;
  ULONG m_unknown56;
  HANDLE m_hEvent1;
  HANDLE m_hDuplicate;
  ULONG m_unknown68;
  ULONG m_unknown84;
  ULONG m_unknown88;
  ULONG m_unknown2172;
  ULONG m_unknown2176;
};

#endif
