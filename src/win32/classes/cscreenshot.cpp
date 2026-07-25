#include <windows.h>
#include "cscreenshot.h"


// 0040d840
CScreenshot::CScreenshot() {
  m_palette = 0;
  m_bytes = 0;
}


// 0040dd1c
int CScreenshot::save(const char* pFileName) {
  int result = 1;
  OFSTRUCT ofstruct;
  HFILE hFile = OpenFile(pFileName, &ofstruct, OF_CREATE);
  if (hFile == HFILE_ERROR) {
    return 1;
  }

  char header[14];
  memset(header, 0, sizeof(header));
  *((USHORT*)&header) = 0x4D42;
  if (_lwrite(hFile, header, sizeof(header)) != sizeof(header)) {
    goto close;
  }

  *((ULONG*)&header[2]) += sizeof(header);
  if (_lwrite(hFile, (const char*)&m_bitmapInfoHeader, sizeof(m_bitmapInfoHeader)) != sizeof(m_bitmapInfoHeader)) {
    goto close;
  }

  *((ULONG*)&header[2]) += sizeof(m_bitmapInfoHeader);

  switch (m_bitmapInfoHeader.biBitCount) {
    case 1:
      if (_lwrite(hFile, (const char*)m_palette, 8) != 8) {
        goto close;
      }
      *((ULONG*)&header[2]) += 8;
      break;
    case 4:
      if (_lwrite(hFile, (const char*)m_palette, 64) != 64) {
        goto close;
      }
      *((ULONG*)&header[2]) += 64;
      break;
    case 8:
      if (_lwrite(hFile, (const char*)m_palette, 1024) != 1024) {
        goto close;
      }
      *((ULONG*)&header[2]) += 1024;
      break;
    case 16:
    case 32:
      if (_lwrite(hFile, (const char*)m_palette, 12) != 12) {
        goto close;
      }
      *((ULONG*)&header[2]) += 12;
      break;
    case 24:
      break;
    default:
      goto close;
  }

  long height;
  if (m_bitmapInfoHeader.biHeight >= 0) {
    height = m_bitmapInfoHeader.biHeight;
  }
  else {
    height = -m_bitmapInfoHeader.biHeight;
  }
  m_bitmapInfoHeader.biSizeImage = ((m_bitmapInfoHeader.biBitCount * (m_bitmapInfoHeader.biWidth + 31) & 0xFFFFFFE0) >> 3) * height;
  if (_lwrite(hFile, (const char*)m_bytes, m_bitmapInfoHeader.biSizeImage) != m_bitmapInfoHeader.biSizeImage) {
    goto close;
  }
  *((ULONG*)&header[10]) = *((ULONG*)&header[2]);
  *((ULONG*)&header[2]) += m_bitmapInfoHeader.biSizeImage;
  _llseek(hFile, 0, 0);
  if (_lwrite(hFile, header, sizeof(header)) != sizeof(header)) {
    goto close;
  }
  result = 0;

close:
  _lclose(hFile);
  return result;
}


// 0040e0a7
int CScreenshot::initPalette(int bpp) {
  if (m_palette != 0) {
    delete[] m_palette;
  }

  switch (bpp) {
    case 1:
      m_palette = new RGBQUAD[2];
      memset(m_palette, 0, 8);
      m_palette[1].rgbBlue = 255;
      m_palette[1].rgbGreen = 255;
      m_palette[1].rgbRed = 255;
      break;
    case 4:
      m_palette = new RGBQUAD[16];
      memset(m_palette, 0, 64);

      for (int i = 1; i < 16; ++i) {
        m_palette[i].rgbBlue = i * 16;
        m_palette[i].rgbGreen = i * 16;
        m_palette[i].rgbRed = i * 16;
      }

      break;
    case 8:
      m_palette = new RGBQUAD[256];
      memset(m_palette, 0, 1024);

      for (int i = 1; i < 16; ++i) {
        m_palette[16 + i].rgbBlue = i * 16;
        m_palette[16 + i].rgbGreen = i * 16;
        m_palette[16 + i].rgbRed = i * 16;
        m_palette[32 + i].rgbBlue = i * 16;
        m_palette[32 + i].rgbGreen = i * 16;
        m_palette[32 + i].rgbRed = i * 16;
        m_palette[48 + i].rgbBlue = i * 16;
        m_palette[48 + i].rgbGreen = i * 16;
        m_palette[48 + i].rgbRed = i * 16;
        m_palette[64 + i].rgbBlue = i * 16;
        m_palette[64 + i].rgbGreen = i * 16;
        m_palette[64 + i].rgbRed = i * 16;
      }

      break;
    case 16: {
      m_palette = new RGBQUAD[3];
      ULONG* pUnknown40 = (ULONG*)m_palette;
      pUnknown40[0] = 0x1F;
      pUnknown40[1] = 0x3E0;
      pUnknown40[2] = 0x7C00;
      break;
    }
    case 24:
      m_palette = 0;
      break;
    case 32: {
      m_palette = new RGBQUAD[4];
      ULONG* pUnknown40 = (ULONG*)m_palette;
      pUnknown40[0] = 1023;
      pUnknown40[1] = 0xFFC00;
      pUnknown40[2] = 0x3FF00000;
      break;
    }
  }

  return 0;
}


// 0040e57b
int CScreenshot::initHeader(int width, int height, int bpp) {
  m_bitmapInfoHeader.biSize = 40;
  m_bitmapInfoHeader.biWidth = width;
  m_bitmapInfoHeader.biHeight = height;
  m_bitmapInfoHeader.biPlanes = 1;
  m_bitmapInfoHeader.biBitCount = bpp;
  if (bpp == 16 || bpp == 32) {
    m_bitmapInfoHeader.biCompression = 3;
  }
  else {
    m_bitmapInfoHeader.biCompression = 0;
  }
  ULONG positiveHeight;
  if (m_bitmapInfoHeader.biHeight >= 0) {
    positiveHeight = m_bitmapInfoHeader.biHeight;
  }
  else {
    positiveHeight = -m_bitmapInfoHeader.biHeight;
  }
  m_bitmapInfoHeader.biSizeImage = ((m_bitmapInfoHeader.biBitCount * (m_bitmapInfoHeader.biWidth + 31) & 0xFFFFFFE0) >> 3) * positiveHeight;
  m_bitmapInfoHeader.biXPelsPerMeter = 0;
  m_bitmapInfoHeader.biYPelsPerMeter = 0;
  m_bitmapInfoHeader.biClrUsed = 0;
  m_bitmapInfoHeader.biClrImportant = 0;

  return 0;
}


// 0040e661
int CScreenshot::init(int width, int height, int bpp) {
  initHeader(width, height, bpp);
  initPalette(bpp);
  if (m_bytes != 0) {
    delete[] m_bytes;
  }
  m_bytes = new BYTE[m_bitmapInfoHeader.biSizeImage];
  memset(m_bytes, 0, m_bitmapInfoHeader.biSizeImage);

  return 0;
}
