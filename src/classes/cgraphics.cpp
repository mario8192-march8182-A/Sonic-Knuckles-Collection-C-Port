#include <stdio.h>
#include <windows.h>
#include <ddraw.h>
#include <mbstring.h>
#include "cgraphics.h"

extern HRESULT(*g_pDdrawCreate)(GUID*, LPDIRECTDRAW*, IUnknown*);
extern int g_useModeX;


// 0040656c
CGraphics::CGraphics() {
  m_pDdraw = 0;
  m_pFrontBuffer = 0;
  m_pBackBuffer = 0;
  m_pDdrawPalette = 0;
  m_pDdrawClipper = 0;
  m_pDibBitValues = 0;
  m_videoMode = 1;
  m_hWnd = 0;
  m_windowX = -32768;
  m_windowY = m_windowX;
  m_bUnknown2168 = FALSE;
  m_ddrawResult = 0;
  m_message[0] = 0;
  memset(&m_videoRect, 0, sizeof(m_videoRect));
  m_hBitmap = 0;
  m_hCompatibleDc = 0;
  m_hPrevBitmap = 0;

  HDC hDc = GetDC(0);
  int deviceCaps = GetDeviceCaps(hDc, RASTERCAPS);
  if (deviceCaps & RC_PALETTE) {
    m_bPaletteSupport = TRUE;
  }
  else {
    m_bPaletteSupport = FALSE;
  }
  m_unknown80 = 768;
  m_unknown82 = 256;
  memset(m_paletteEntries, 0, sizeof(m_paletteEntries));
  if (m_bPaletteSupport) {
    GetSystemPaletteEntries(hDc, 0, 256, m_paletteEntries);
  }
  for (int i = 0; i < 10; ++i) {
    m_paletteEntries[i].peFlags = 0;
  }
  for (int i = 10; i < 246; ++i) {
    m_paletteEntries[i].peFlags = PC_NOCOLLAPSE;
  }
  for (int i = 246; i < 256; ++i) {
    m_paletteEntries[i].peFlags = 0;
  }
  ReleaseDC(0, hDc);

  m_hDdraw = LoadLibrary("DDRAW.DLL");
  if (m_hDdraw != 0) {
    g_pDdrawCreate = (HRESULT(*)(GUID*, LPDIRECTDRAW*, IUnknown*))GetProcAddress(m_hDdraw, "DirectDrawCreate");
  }
}


// 004067a1
CGraphics::~CGraphics() {
  resetVideo();
  if (m_hDdraw != 0) {
    FreeLibrary(m_hDdraw);
  }
}


// 00406a02
int CGraphics::initVideo(ULONG videoMode, HWND hWnd) {
  if (m_bUnknown2168) {
    return 0;
  }

  m_bUnknown2168 = TRUE;
  m_videoMode = videoMode;
  m_hWnd = hWnd;
  ULONG screenSize = videoMode & 3;

  switch (screenSize) {
    case 1:
      m_videoWidth = 320;
      m_videoHeight = 240;
      break;
    case 3:
      m_videoWidth = 640;
      m_videoHeight = 480;
      break;
  }

  if (m_hBitmap != 0) {
    SelectObject(m_hCompatibleDc, m_hPrevBitmap);
    DeleteObject(m_hBitmap);
    m_hBitmap = 0;
  }

  if (m_hCompatibleDc != 0) {
    DeleteDC(m_hCompatibleDc);
    m_hCompatibleDc = 0;
  }

retry:
  if ((((UCHAR*)m_videoMode)[1] & 16) || g_pDdrawCreate == 0) {
    m_videoMode |= 0x1000;
    m_videoMode &= 0xFFFFFFFB;
    m_bitmapInfoHeader.biSize = 40;
    m_bitmapInfoHeader.biPlanes = 1;
    m_bitmapInfoHeader.biBitCount = 8;
    m_bitmapInfoHeader.biCompression = 0;
    m_bitmapInfoHeader.biXPelsPerMeter = 0;
    m_bitmapInfoHeader.biYPelsPerMeter = 0;
    m_bitmapInfoHeader.biClrUsed = 256;
    m_bitmapInfoHeader.biClrImportant = 256;
    m_bitmapInfoHeader.biWidth = m_videoWidth;
    m_bitmapInfoHeader.biHeight = -m_videoHeight;

    RECT workAreaRect;
    SetRect(&m_videoRect, 0, 0, m_videoWidth, m_videoHeight);
    m_bitmapInfoHeader.biSizeImage = -(m_bitmapInfoHeader.biHeight * m_bitmapInfoHeader.biWidth);

    BITMAPINFO* pBitmapInfo = new BITMAPINFO;
    RGBQUAD* pRgbQuad = pBitmapInfo->bmiColors;
    memset(pBitmapInfo, 0, sizeof(*pBitmapInfo));
    memcpy(pBitmapInfo, &m_bitmapInfoHeader, sizeof(m_bitmapInfoHeader));

    for (int i = 0; i < 256; ++i) {
      pRgbQuad[i].rgbBlue = m_paletteEntries[i].peBlue;
      pRgbQuad[i].rgbGreen = m_paletteEntries[i].peGreen;
      pRgbQuad[i].rgbRed = m_paletteEntries[i].peRed;
    }

    HDC hDc = GetDC(0);
    m_hBitmap = CreateDIBSection(hDc, pBitmapInfo, 0, &m_pDibBitValues, 0, 0);
    m_hCompatibleDc = CreateCompatibleDC(hDc);
    m_hPrevBitmap = (HBITMAP)SelectObject(m_hCompatibleDc, m_hBitmap);
    delete pBitmapInfo;
    ReleaseDC(0, hDc);

    long windowStyle = GetWindowLong(hWnd, GWL_STYLE) & 0x7FFFFFFF | WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CAPTION;
    SetWindowLong(hWnd, GWL_STYLE, windowStyle);
    RECT windowRect;
    SetRect(&windowRect, 0, 0, m_videoWidth, m_videoHeight);
    AdjustWindowRectEx(&windowRect, GetWindowLong(hWnd, GWL_STYLE), GetMenu(hWnd) != 0, GetWindowLong(hWnd, GWL_EXSTYLE));
    if (m_windowX == -32768 && m_windowY == -32768) {
      SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_NOMOVE | SWP_NOACTIVATE);
    }
    else {
      SetWindowPos(hWnd, HWND_NOTOPMOST, m_windowX, m_windowY, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_NOACTIVATE);
    }
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workAreaRect, 0);
    GetWindowRect(hWnd, &windowRect);
    if (windowRect.left < workAreaRect.left) {
      windowRect.left = workAreaRect.left;
    }
    if (windowRect.top < workAreaRect.top) {
      windowRect.top = workAreaRect.top;
    }
    SetWindowPos(hWnd, 0, windowRect.left, windowRect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    m_bUnknown2168 = FALSE;

    return 0;
  }

  if (m_pDdraw == 0) {
    if (g_pDdrawCreate != 0) {
      m_ddrawResult = (*g_pDdrawCreate)(0, &m_pDdraw, 0);
      if (m_ddrawResult != DD_OK) {
        _mbscpy((UCHAR*)m_message, (const UCHAR*)"DirectDrawCreate");
        return 1;
      }
    }
    else {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"Cannot Find DirectDrawCreate");
      return 1;
    }
  }

  if (m_pDdrawPalette != 0) {
    m_pDdrawPalette->Release();
    m_pDdrawPalette = 0;
  }
  if (m_pDdrawClipper != 0) {
    m_pDdrawClipper->Release();
    m_pDdrawClipper = 0;
  }
  if (m_pBackBuffer != 0) {
    m_pBackBuffer->Release();
    m_pBackBuffer = 0;
  }
  if (m_pFrontBuffer != 0) {
    m_pFrontBuffer->Release();
    m_pFrontBuffer = 0;
  }

  if (((UCHAR*)m_videoMode)[0] & 4) {
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);
    m_windowX = windowRect.left;
    m_windowY = windowRect.top;
    long windowStyle = GetWindowLong(hWnd, GWL_STYLE) & 0xFF31FFFF | WS_POPUP;
    SetWindowLong(hWnd, GWL_STYLE, windowStyle);

    if (g_useModeX != 0) {
      m_ddrawResult = m_pDdraw->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX);
      if (m_ddrawResult != DD_OK) {
        _mbscpy((UCHAR*)m_message, (const UCHAR*)"SetCooperativeLevel DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX");
        return 1;
      }
    }
    else {
      m_ddrawResult = m_pDdraw->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
      if (m_ddrawResult != DD_OK) {
        _mbscpy((UCHAR*)m_message, (const UCHAR*)"SetCooperativeLevel DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN");
        return 1;
      }
    }

    if (g_useModeX != 0) {
      m_ddrawResult = m_pDdraw->SetDisplayMode(320, 240, 8);
      if (m_ddrawResult != DD_OK) {
        sprintf(m_message, "SetDisplayMode(320,240,8)");
        return 1;
      }
    }
    else {
      m_ddrawResult = m_pDdraw->SetDisplayMode(640, 480, 8);
      if (m_ddrawResult != DD_OK) {
        sprintf(m_message, "SetDisplayMode(640,480,8)");
        return 1;
      }
    }

    DDSURFACEDESC ddSurfaceDesc;
    memset(&ddSurfaceDesc, 0, sizeof(ddSurfaceDesc));
    ddSurfaceDesc.dwSize = sizeof(DDSURFACEDESC);
    ddSurfaceDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddSurfaceDesc.ddsCaps.dwCaps = DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_PRIMARYSURFACE;
    ddSurfaceDesc.dwBackBufferCount = 1;
    m_ddrawResult = m_pDdraw->CreateSurface(&ddSurfaceDesc, &m_pFrontBuffer, 0);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"CreateSurface");
      return 1;
    }

    DDSCAPS ddsCaps;
    ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
    m_ddrawResult = m_pFrontBuffer->GetAttachedSurface(&ddsCaps, &m_pBackBuffer);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"GetAttachedSurface");
      return 1;
    }
  }
  else {
    m_ddrawResult = m_pDdraw->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_NOWINDOWCHANGES);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"SetCooperativeLevel DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_NOWINDOWCHANGES");
      return 1;
    }
    m_ddrawResult = m_pDdraw->RestoreDisplayMode();
    if (m_ddrawResult != DD_OK) {
      sprintf(m_message, "RestoreDisplayMode");
      return 1;
    }

    long windowStyle = GetWindowLong(hWnd, GWL_STYLE) & 0x7FFFFFFF | WS_MINIMIZEBOX | WS_THICKFRAME | WS_SYSMENU | WS_CAPTION;
    RECT windowRect;
    SetRect(&windowRect, 0, 0, m_videoWidth, m_videoHeight);
    AdjustWindowRectEx(&windowRect, GetWindowLong(hWnd, GWL_STYLE), GetMenu(hWnd) != 0, GetWindowLongA(hWnd, GWL_EXSTYLE));
    if (m_windowX == -32768 && m_windowY == -32768) {
      SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_NOMOVE | SWP_NOACTIVATE);
    }
    else {
      SetWindowPos(hWnd, HWND_NOTOPMOST, m_windowX, m_windowY, windowRect.right - windowRect.left,windowRect.bottom - windowRect.top, SWP_NOACTIVATE);
    }

    RECT workAreaRect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workAreaRect, 0);
    GetWindowRect(hWnd, &windowRect);
    if (windowRect.left < workAreaRect.left) {
      windowRect.left = workAreaRect.left;
    }
    if (windowRect.top < workAreaRect.top) {
      windowRect.top = workAreaRect.top;
    }
    SetWindowPos(hWnd, 0, windowRect.left, windowRect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

    DDSURFACEDESC ddSurfaceDesc;
    memset(&ddSurfaceDesc,0, sizeof(ddSurfaceDesc));
    ddSurfaceDesc.dwSize = sizeof(ddSurfaceDesc);
    ddSurfaceDesc.dwFlags = DDSD_CAPS;
    ddSurfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    m_ddrawResult = m_pDdraw->CreateSurface(&ddSurfaceDesc, &m_pFrontBuffer, 0);
    if (m_ddrawResult != DD_OK) {
      if (((UCHAR*)m_videoMode)[1] & 64) {
        _mbscpy((UCHAR*)m_message, (const UCHAR*)"CreateSurface DDSCAPS_PRIMARYSURFACE");
        return 1;
      }
      resetVideo();
      m_videoMode |= 0x1000;
      goto retry;
    }
    m_ddrawResult = m_pDdraw->CreateClipper(0, &m_pDdrawClipper, 0);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"CreateClipper");
      return 1;
    }
    m_ddrawResult = m_pDdrawClipper->SetHWnd(0, hWnd);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"lpDDClipper->SetHWnd");
      return 1;
    }
    m_ddrawResult = m_pFrontBuffer->SetClipper(m_pDdrawClipper);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"lpFrontBuffer->SetClipper");
      return 1;
    }

    memset(&ddSurfaceDesc, 0, sizeof(ddSurfaceDesc));
    ddSurfaceDesc.dwSize = sizeof(ddSurfaceDesc);
    ddSurfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddSurfaceDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddSurfaceDesc.dwWidth = m_videoWidth;
    ddSurfaceDesc.dwHeight = m_videoHeight;
    SetRect(&m_videoRect, 0, 0, m_videoWidth, m_videoHeight);
    m_ddrawResult = m_pDdraw->CreateSurface(&ddSurfaceDesc, &m_pBackBuffer, 0);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"CreateSurface DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY");
      return 1;
    }
  }

  m_ddrawResult = m_pDdraw->CreatePalette(DDPCAPS_8BIT, m_paletteEntries, &m_pDdrawPalette, 0);
  if (m_ddrawResult != DD_OK) {
    if (((UCHAR*)m_videoMode)[1] & 64) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"CreatePalette DDPCAPS_8BIT");
      return 1;
    }
    resetVideo();
    m_videoMode |= 0x1000;
    goto retry;
  }
  m_ddrawResult = m_pFrontBuffer->SetPalette(m_pDdrawPalette);
  if (m_ddrawResult != DD_OK) {
    if (((UCHAR*)m_videoMode)[1] & 64) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"lpFrontBuffer->SetPalette");
      return 1;
    }
    resetVideo();
    m_videoMode |= 0x1000;
    goto retry;
  }

  m_bUnknown2168 = FALSE;

  return 0;
}


// 00407ae8
int CGraphics::resetVideo() {
  if (m_pDdraw != 0) {
    m_pDdraw->RestoreDisplayMode();
  }
  if (m_pDdrawPalette != 0) {
    m_pDdrawPalette->Release();
    m_pDdrawPalette = 0;
  }
  if (m_pDdrawClipper != 0) {
    m_pDdrawClipper->Release();
    m_pDdrawClipper = 0;
  }
  if (m_pBackBuffer != 0) {
    m_pBackBuffer->Release();
    m_pBackBuffer = 0;
  }
  if (m_pFrontBuffer != 0) {
    m_pFrontBuffer->Release();
    m_pFrontBuffer = 0;
  }
  if (m_pDdraw != 0) {
    m_pDdraw->Release();
    m_pDdraw = 0;
  }
  if (m_hBitmap != 0) {
    SelectObject(m_hCompatibleDc, m_hPrevBitmap);
    DeleteObject(m_hBitmap);
    m_hBitmap = 0;
  }
  if (m_hCompatibleDc != 0) {
    DeleteDC(m_hCompatibleDc);
    m_hCompatibleDc = 0;
  }

  return 0;
}


// 00407c41
int CGraphics::clearBuffers() {
  if (((UCHAR*)m_videoMode)[1] & 16) {
    RECT clientRect;
    GetClientRect(m_hWnd, &clientRect);
    HDC hDc = GetDC(m_hWnd);
    PatBlt(hDc, 0, 0, clientRect.right, clientRect.bottom, BLACKNESS);
    ReleaseDC(m_hWnd, hDc);
    PatBlt(m_hCompatibleDc, 0, 0, m_videoRect.right, m_videoRect.bottom, BLACKNESS);
    return 0;
  }

  DDBLTFX ddBltFx;
  ddBltFx.dwSize = 100;
  ddBltFx.dwFillColor = 0;
  if (((UCHAR*)m_videoMode)[0] & 4) {
    m_ddrawResult = m_pBackBuffer->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddBltFx);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"lpBackBuffer->Blt DDBLT_COLORFILL | DDBLT_WAIT");
      return 1;
    }
    m_ddrawResult = m_pFrontBuffer->Flip(0, DDFLIP_WAIT);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)" Blt1x : lpFrontBuffer->Flip");
      char buffer[256];
      readMessage(buffer);
      return 1;
    }
    m_ddrawResult = m_pBackBuffer->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddBltFx);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"lpBackBuffer->Blt DDBLT_COLORFILL | DDBLT_WAIT");
      return 1;
    }
    m_ddrawResult = m_pFrontBuffer->Flip(0, DDFLIP_WAIT);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)" Blt1x : lpFrontBuffer->Flip");
      char buffer[256];
      readMessage(buffer);
      return 1;
    }
  }
  else {
    RECT screenRect;
    GetClientRect(m_hWnd, &screenRect);
    ClientToScreen(m_hWnd, (LPPOINT)&screenRect);
    screenRect.bottom = screenRect.bottom + screenRect.top;
    screenRect.right = screenRect.right + screenRect.left;
    m_ddrawResult = m_pFrontBuffer->Blt(&screenRect, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddBltFx);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"lpFrontBuffer->Blt DDBLT_COLORFILL | DDBLT_WAIT");
      return 1;
    }
    m_ddrawResult = m_pBackBuffer->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddBltFx);
    if (m_ddrawResult != DD_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"lpBackBuffer->Blt DDBLT_COLORFILL | DDBLT_WAIT");
      return 1;
    }
  }

  return 0;
}


// 004093fa
int CGraphics::readMessage(char* pBuffer) {
  if (m_ddrawResult == DD_OK) {
    return 1;
  }

  char hResultString[128];
  sprintf(hResultString, "\nHRESULT : = %08X\n", m_ddrawResult);
  _mbscpy((UCHAR*)pBuffer, (const UCHAR*)m_message);
  strcat(pBuffer, hResultString);
  OutputDebugString(pBuffer);

  return 0;
}
