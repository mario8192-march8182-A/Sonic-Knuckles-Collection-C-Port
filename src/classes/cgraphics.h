#ifndef CGRAPHICS_H
#define CGRAPHICS_H

#include <windows.h>
#include <ddraw.h>

class CGraphics {
  public:
  BOOL getUnknown2168();
  ULONG getVideoMode();
  CGraphics();
  ~CGraphics();
  BOOL canCreateDdrawInstance();
  BOOL stubbedMethod();
  void updatePalette();
  int initVideo(ULONG videoMode, HWND hWnd);
  int resetVideo();
  int clearBuffers();
  int getBackBufferDc(HDC* phDC);
  int releaseBackBufferDc(HDC hDc);
  int blit();
  int restoreBuffers();
  int updateDevicePalette(RGBQUAD* pQuads, UINT paletteStart, UINT quadCnt);
  int readMessage(char* pBuffer);
  int showMessage();
  int blitPausedMessage();

  private:
  LPDIRECTDRAW m_pDdraw;
  LPDIRECTDRAWSURFACE m_pFrontBuffer;
  LPDIRECTDRAWSURFACE m_pBackBuffer;
  LPDIRECTDRAWPALETTE m_pDdrawPalette;
  LPDIRECTDRAWCLIPPER m_pDdrawClipper;
  HMODULE m_hDdraw;
  BITMAPINFOHEADER m_bitmapInfoHeader;
  HBITMAP m_hBitmap;
  HDC m_hCompatibleDc;
  HBITMAP m_hPrevBitmap;
  void* m_pDibBitValues;
  USHORT m_unknown80;
  USHORT m_unknown82;
  PALETTEENTRY m_palette[256];
  ULONG m_videoMode;
  BOOL m_bPaletteSupport;
  HWND m_hWnd;
  int m_windowX;
  int m_windowY;
  RECT m_videoRect;
  RGBQUAD m_colorwk[64];
  RGBQUAD m_colorwk2[64];
  RGBQUAD m_colorwk3[64];
  RGBQUAD m_colorwk4[64];
  BOOL m_bUnknown2168;
  HRESULT m_ddrawResult;
  char m_message[256];
  int m_videoWidth;
  int m_videoHeight;
};

#endif
