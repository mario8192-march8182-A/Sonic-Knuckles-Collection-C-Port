#ifndef CSCREENSHOT_H
#define CSCREENSHOT_H

#include <windows.h>

class CScreenshot {
  public:
  CScreenshot();
  int save(const char* pFileName);
  int initPalette(int bpp);
  int initHeader(int width, int height, int bpp);
  int init(int width, int height, int bpp);
  BITMAPINFOHEADER m_bitmapInfoHeader;
  RGBQUAD* m_palette;
  BYTE* m_bytes;
};

#endif
