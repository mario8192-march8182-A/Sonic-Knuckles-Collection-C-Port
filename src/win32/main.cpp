#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <mbstring.h>
#include "globals.h"
#include "globalobjects.hpp"
#include "constants.h"
#include "winresource.h"
#include "macros.h"
#include "imidi.h"
#include "types/sprite.h"
#include "../types/spritedata.h"
#include "classes/cfile.h"
#include "classes/cgame.h"
#include "classes/cgraphics.h"
#include "classes/csound.h"
#include "classes/cwinregistry.h"
extern "C" {
  #include "../entry.h"
  #include "../ram.h"
  #include "vdp.h"
}

void vInt18();
void vInt4();
void vInt20();
void vInt2();
void vInt22();
void vInt26();
void uploadPalette();
void pollMdControllers();
BOOL loadBgm(int id);
void initControls();
void pollWindowsControllers();
USHORT getPressedController1Buttons();
USHORT getPressedController2Buttons();
void playBgm();
void stopBgm();
void pauseBgm();


// 00401000
int FUN_00401000() {
  double unknown = 0.0;
  g_systemTime = timeGetTime();
  g_elapsedTime = g_systemTime - g_lastSystemTime;
  if (DAT_0082b098 < 1) {
    if (g_elapsedTime < 17 && BOOL_0082b040) {
      if (BOOL_0082b044 == FALSE) {
        BOOL_0082b044 = TRUE;
        DAT_00831150 = g_systemTime;
      }
      return BOOL_0082b044;
    }
    if (BOOL_0082b044) {
      unknown = g_systemTime - DAT_00831150;
    }
  }
  BOOL_0082b044 = FALSE;
  g_lastSystemTime = g_systemTime;
  g_cumulativeElapsedTime += g_elapsedTime;
  if (BOOL_0082b040) {
    DAT_0082b054 = g_elapsedTime - (long)unknown;
    ++DAT_0082b070;
    ++DAT_0082b074;
  }
  ++DAT_0082b078;
  ++DAT_0082b07c;
  g_elapsedTime2 = g_systemTime - g_lastSystemTime2;
  g_elapsedTime3 = g_systemTime - g_lastSystemTime3;
  if (g_elapsedTime3 >= 1000) {
    DAT_0082b088 = 1;
    g_lastSystemTime3 = g_systemTime;
    DAT_00831140 = g_elapsedTime3;
    g_lastDAT_0082b074 = DAT_0082b074;
    g_lastDAT_0082b07c = DAT_0082b07c;
    DAT_0082b074 = DAT_0082b07c = 0;
  }
  BOOL_0082b040 = TRUE;
  if (DAT_00829058[DAT_0082b098] <= DAT_0082b078) {
    double temp = DAT_0082b078 * DAT_00829080;
    double temp2 = temp / DAT_00829088;
    if (g_elapsedTime2 < temp - temp2) {
      --DAT_0082b098;
    }
    if (g_elapsedTime2 >= temp + temp2) {
      ++DAT_0082b098;
    }
    if (DAT_0082b098 >= 8) {
      DAT_0082b098 = 7;
    }
    else if (DAT_0082b098 < 0) {
      DAT_0082b098 = 0;
    }
    g_lastSystemTime2 = g_systemTime;
    DAT_0082b070 = DAT_0082b078 = 0;
    if (DAT_0082b098 >= 1) {
      BOOL_0082b040 = FALSE;
    }
  }
  return BOOL_0082b044;
}


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
  g_hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDA_MENU));
  g_pGraphics = new CGraphics();
  g_pSound = new CSound();
  initControls();

  int errorCode = g_game.init();
  if (errorCode == 0) {
    handleMessages();
  }

  delete g_pSound;
  delete g_pGraphics;

  if (g_bLaunchRunSonic) {
    WinExec("RunSonic.exe", SW_SHOWNORMAL);
  }

  return ret;
}


// 00403d27
DWORD WINAPI gameThreadStartRoutine(void* pParameter) {
  if (g_bResetMdRam) {
    clear_game_ram();
    g_bResetMdRam = FALSE;
  }
  memset(g_vram, 0, 0x10000);

  set_region(2);

  switch (g_startGameMode) {
    case STARTGAMEMODE_NORMAL:
      if (g_sonicGameMode == SONICGAMEMODE_SONICKNUCKLES) {
        sk_entry();
      }
      else {
        s3_entry();
      }
      break;
    case STARTGAMEMODE_SPECIALSTAGEMODE:
      g_bResetMdRam = TRUE;
      bs_entry();
      break;
    case STARTGAMEMODE_DEBUG:
      debug_entry();
      break;
  }

  return 0;
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


// 004040ba
LRESULT CALLBACK thanksForPlayingDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG: {
      HWND hMessageWnd = GetDlgItem(hWnd, ID_THANKSFORPLAYING_MESSAGE);
      SendMessage(hMessageWnd, WM_SETREDRAW, FALSE, 0);
      SendMessage(hMessageWnd, LB_RESETCONTENT, 0, 0);
      FILE* pFile = fopen("thanks.txt", "r");
      if (pFile != 0 && (int)pFile != -1) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), pFile) != 0) {
          for (unsigned int i = 0; i < sizeof(buffer) && buffer[i] != 0; ++i) {
            if (buffer[i] == '\n' || buffer[i] == '\r') {
              buffer[i] = 0;
            }
          }
          SendMessage(hMessageWnd, LB_ADDSTRING, 0, (LPARAM)buffer);
        }
        fclose(pFile);
      }
      else {
        char** ppThanksForPlayingText;
        if ((GetSystemDefaultLangID() & 0x3FF) == 17) {
          ppThanksForPlayingText = (char**)g_thanksForPlayingJpText;
        }
        else {
          ppThanksForPlayingText = g_thanksForPlayingEnText;
        }
        while (*ppThanksForPlayingText != 0) {
          SendMessage(hMessageWnd, LB_ADDSTRING, 0, (LPARAM)*ppThanksForPlayingText);
          ++ppThanksForPlayingText;
        }
      }
      SendMessage(hMessageWnd, WM_SETREDRAW, TRUE, 0);
      return TRUE;
    }
    case WM_COMMAND: {
      ULONG id = LOWORD(wParam);

      switch (id) {
        case ID_THANKSFORPLAYING_OK:
        case 2:
          EndDialog(hWnd, id);
          return 1;
      }
    }
  }

  return 0;
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

  g_region7ff8000 = VirtualAlloc((void*)0x7FF8000, 0x20000, MEM_RESERVE, PAGE_READWRITE);
  if (g_region7ff8000 == 0) {
    return 1;
  }
  g_region7ff8000 = VirtualAlloc((void*)0x7FF8000, 0x20000, MEM_COMMIT, PAGE_READWRITE);
  if (g_region7ff8000 == 0) {
    return 1;
  }

  clear_game_ram();
  memset(g_vram, 0, 0x10000);
  memset(g_pixelBuffer, 0, 0x23000);

  return 0;
}


// 004044d4
void freeRamAndVram() {
  if (g_region8fe8000 != 0) {
    VirtualFree(g_region8fe8000, 0x20000, MEM_DECOMMIT);
    VirtualFree(g_region8fe8000, 0, MEM_RELEASE);
    g_region8fe8000 = 0;
  }
  if (g_region7ff8000 != 0) {
    VirtualFree(g_region7ff8000, 0x20000, MEM_DECOMMIT);
    VirtualFree(g_region7ff8000, 0, MEM_RELEASE);
    g_region7ff8000 = 0;
  }
}


// 00404564
void blitSprites() {
  Sprite* pSprite;
  if (g_vdp_mode == 5) {
    pSprite = &g_sprites[g_spriteCnt - 1];

    for (unsigned int i = 0; i < g_spriteCnt; ++i) {
      switch (pSprite->flags & 0x300) {
        case 0x000: blit_sprite(pSprite);        break;
        case 0x100: blit_sprite_hflip(pSprite);  break;
        case 0x200: blit_sprite_vflip(pSprite);  break;
        case 0x300: blit_sprite_hvflip(pSprite); break;
      }
      --pSprite;
    }
  }
  else if (DAT_00831750 != 0) {
    memset(g_spriteMasks, 0, 448);

    for (int i = 0; i < 112; ++i) {
      g_spriteMasks[i] = 1;
    }

    pSprite = &g_sprites[g_spriteCnt - 1];

    for (unsigned int i = 0; i < g_spriteCnt; ++i) {
      if (((UCHAR*)&pSprite->flags)[2] & 1) {
        memset(g_spriteMasks, 0, 448);
        for (int j = 112; j < 224; ++j) {
          g_spriteMasks[i] = 1;
        }
      }
      else {
        switch (pSprite->flags & 0x300) {
          case 0x000: blit_sprite_masked(pSprite);        break;
          case 0x100: blit_sprite_masked_hflip(pSprite);  break;
          case 0x200: blit_sprite_masked_vflip(pSprite);  break;
          case 0x300: blit_sprite_masked_hvflip(pSprite); break;
        }
      }
      --pSprite;
    }
  }
  else if (DAT_008547bc != 0) {
    DAT_008547bc = 0;
    memset(g_spriteMasks, 0, 448);
    pSprite = g_sprites;

    for (unsigned int i = 0; i < g_spriteCnt; ++i) {
      FUN_00411a50(pSprite);
      ++pSprite;
    }

    pSprite = &g_sprites[g_spriteCnt - 1];

    for (unsigned int i = 0; i < g_spriteCnt; ++i) {
      switch (pSprite->flags & 0x300) {
        case 0x000: blit_sprite_masked(pSprite);        break;
        case 0x100: blit_sprite_masked_hflip(pSprite);  break;
        case 0x200: blit_sprite_masked_vflip(pSprite);  break;
        case 0x300: blit_sprite_masked_hvflip(pSprite); break;
      }
      --pSprite;
    }
  }
  else {
    pSprite = &g_sprites[g_spriteCnt - 1];

    for (unsigned int i = 0; i < g_spriteCnt; ++i) {
      switch (pSprite->flags & 0x300) {
        case 0x000: blit_sprite_noprio(pSprite);        break;
        case 0x100: blit_sprite_hflip_noprio(pSprite);  break;
        case 0x200: blit_sprite_vflip_noprio(pSprite);  break;
        case 0x300: blit_sprite_hvflip_noprio(pSprite); break;
      }
      --pSprite;
    }
  }

  g_spriteCnt = 0;
}


// 004049eb
Sprite* uploadSprites(SKC_sprite_data* pSource, Sprite* pSprite) {
  g_spriteCnt = 0;
  DAT_00831750 = 0;

  while (pSource->next && (pSource->vp || pSource->gfx || pSource->hf || pSource->vf || pSource->pl || pSource->pr || pSource->hp)) {
    pSprite->x = pSource->hp - 128;
    pSprite->y = pSource->vp - 128;
    pSprite->w = pSource->hs + 1;
    pSprite->h = pSource->vs * 8 + 8;
    pSprite->flags = pSource->pl + 16
                   | pSource->vf << 9
                   | pSource->hf << 8
                   | pSource->pr << 7;
    pSprite->vram_offset = pSource->gfx << 5;
    ++g_spriteCnt;
    ++pSprite;
    ++pSource;
  }

  return pSprite;
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


// 00404ece
void writeSaveFile() {
  char fileName[256];
  GetModuleFileName(0, fileName, sizeof(fileName));
  _mbscpy((UCHAR*)&fileName[strlen(fileName) - 3], (UCHAR*)"BIN");
  HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
  if (hFile == INVALID_HANDLE_VALUE) {
    MessageBox(0, "Cannot Open Save Data File", "Error", MB_OK);
    g_createFileError = GetLastError();
  }
  else {
    ULONG byteWriteCnt;
    WriteFile(hFile, g_saveFile, sizeof(g_saveFile), &byteWriteCnt, 0);
    if (byteWriteCnt != sizeof(g_saveFile)) {
      MessageBox(0, "Cannot Write Save Data File", "Error", MB_OK);
    }
    CloseHandle(hFile);
  }
}


// 00404fd5
extern "C" void write_sram(unsigned char* p_source, int savefile_offset, unsigned short word_cnt) {
  memcpy(&g_saveFile[savefile_offset], p_source, word_cnt * 2 + 2);
}


// 00405020
extern "C" int read_sram(unsigned char* p_destination, int savefile_offset, unsigned short word_cnt, unsigned short check_value) {
  ULONG size = word_cnt * 2 + 2;

  memcpy(p_destination, &g_saveFile[savefile_offset], size);
  USHORT readCheckValue = *((USHORT*)&g_saveFile[savefile_offset + size - 2 - 2]);
  if (check_value != readCheckValue) {
    return -1;
  }

  return 0;
}


// 004050c0
extern "C" void v_int(void) {
  g_pHscrollbuff2 = g_pHscrollbuff = 0;
  g_vscrollPlaneA = get_vscrolla();
  g_vscrollPlaneB = get_vscrollb();
  g_bVscrollCopy = FALSE;

  switch (*get_int_flg_ptr()) {
    case 2:
      vInt2();
      break;
    case 4:
      vInt4();
      break;
    case 18:
      vInt18();
      break;
    case 20:
      vInt20();
      break;
    case 22:
      vInt22();
      break;
    case 8:
    case 10:
    case 12:
    case 14:
      // TODO
      break;
    case 26:
      vInt26();
      break;
    case 28:
      // TODO
      break;
    case 30:
      // TODO
      break;
  }

  inc_systemtimer();
  g_game.update();
  *get_int_flg_ptr() = 0;
}


// 00405201
void vInt18() {
  g_pHscrollbuff = &get_hscrollbuff()[0];
  g_pHscrollbuff2 = &get_hscrollbuff()[1];
  uploadPalette();
  uploadSprites(get_sprite_table(), g_sprites);
  pollMdControllers();
}


// 00405237
void vInt4() {
  memcpy(get_colorwk(), get_colorwk2(), sizeof(unsigned short) * 64);
  uploadPalette();
  uploadSprites(get_sprite_table(), g_sprites);
  pollMdControllers();
  if (*get_demotimer_ptr() != 0) {
    --*get_demotimer_ptr();
  }
}


// 00405284
void vInt20() {
  uploadPalette();
  if (*get_demotimer_ptr() != 0) {
    --*get_demotimer_ptr();
  }
}


// 004052b0
void vInt2() {
  uploadPalette();
  if (*get_demotimer_ptr() != 0) {
    --*get_demotimer_ptr();
  }
}


// 004052dc
void vInt22() {
  uploadPalette();
  uploadSprites(get_sprite_table(), g_sprites);
  pollMdControllers();
  if (*get_demotimer_ptr() != 0) {
    --*get_demotimer_ptr();
  }
}


// 00405312
void vInt26() {
  g_pHscrollbuff = &get_hscrollbuff()[0];
  g_pHscrollbuff2 = &get_hscrollbuff()[1];
  uploadPalette();
  uploadSprites(get_sprite_table(), g_sprites);
  pollMdControllers();
  if (*get_demotimer_ptr() != 0) {
    --*get_demotimer_ptr();
  }
}


// 00405536
void uploadPalette() {
  RGBQUAD palette[64];
  memset(palette, 0, sizeof(palette));
  unsigned short* pColorwk;
  if (get_waterflag() != 0) {
    pColorwk = get_colorwk3();
  }
  else {
    pColorwk = get_colorwk();
  }

  for (int i = 0; i < 64; ++i) {
    palette[i].rgbRed = (pColorwk[i] & 0xF) * 17;
    palette[i].rgbGreen = (pColorwk[i] >> 4 & 0xF) * 17;
    palette[i].rgbBlue = (pColorwk[i] >> 8 & 0xF) * 17;
  }

  palette[0] = palette[g_bg_color_index];
  palette[16] = palette[0];
  palette[32] = palette[0];
  palette[48] = palette[0];

  CGraphics* pGraphics = getGraphicsPtr();
  if (g_vdp_mode == 5) {
    pGraphics->copyPaletteToWk4(palette);
    for (int i = 0; i < 64; ++i) {
      palette[i].rgbRed >>= 1;
      palette[i].rgbGreen >>= 1;
      palette[i].rgbBlue >>= 1;
    }
    pGraphics->copyPaletteToWk3(palette);
  }
  else {
    pGraphics->copyPaletteToWk3(palette);
    pGraphics->copyPaletteToWk4(palette);
  }
}


// 00405a45
void pollMdControllers() {
  pollWindowsControllers();
  set_swdata1(getPressedController1Buttons());
  set_swdata2(getPressedController2Buttons());
}


// 00405b76
void blitGraphics() {
  if (g_bVscrollCopy) {
    for (int i = 0; i < 20; ++i) {
      g_mdVsram[i] = get_vscrollbuff()[i + 1];
    }
    if (g_pHscrollbuff2 != 0) {
      for (int i = 0; i < 224; ++i) {
        g_convertedHscrollbuff[i] = -*g_pHscrollbuff2 & 0x3FF;
        g_pHscrollbuff2 += 2;
      }
    }
    else {
      memset(g_convertedHscrollbuff, 0, sizeof(g_convertedHscrollbuff));
    }
    g_pVdpReadPos = &g_vram[g_vdp_scrollb_adr];
    FUN_00415039();
    for (int i = 0; i < 20; ++i) {
      g_mdVsram[i] = get_vscrollbuff()[i];
    }
    if (g_pHscrollbuff != 0) {
      for (int i = 0; i < 224; ++i) {
        g_convertedHscrollbuff[i] = -*g_pHscrollbuff & 0x3FF;
        g_pHscrollbuff += 2;
      }
    }
    else {
      memset(g_convertedHscrollbuff, 0, sizeof(g_convertedHscrollbuff));
    }
    g_pVdpReadPos = &g_vram[g_vdp_scrolla_adr];
    FUN_00414f70();
  }
  else {
    g_vscrollCopy = g_vscrollPlaneB;
    if (g_pHscrollbuff2 != 0) {
      if (g_vdp_hscroll_scanline != 0) {
        for (int i = 0; i < 224; ++i) {
          g_convertedHscrollbuff[i] = -*g_pHscrollbuff2 & 0x3FF;
          g_pHscrollbuff2 += 2;
        }
      }
      else {
        for (int i = 0; i < 224; ++i) {
          g_convertedHscrollbuff[i] = -*g_pHscrollbuff2 & 0x3FF;
        }
      }
    }
    else {
      memset(g_convertedHscrollbuff, 0, sizeof(g_convertedHscrollbuff));
    }
    g_pVdpReadPos = &g_vram[g_vdp_scrollb_adr];

    switch (g_vdp_mode) {
      case 0:
        FUN_0040f4c8();
        break;
      case 1:
      case 5:
        FUN_004148fe();
        break;
      case 2:
        FUN_004145ee();
        break;
      case 3:
        FUN_0041479e();
        break;
      case 4:
        FUN_0041448e();
        break;
    }

    g_vscrollCopy = g_vscrollPlaneA;
    if (g_pHscrollbuff != 0) {
      if (g_vdp_hscroll_scanline != 0) {
        for (int i = 0; i < 224; ++i) {
          g_convertedHscrollbuff[i] = -*g_pHscrollbuff & 0x3FF;
          g_pHscrollbuff += 2;
        }
      }
      else {
        for (int i = 0; i < 224; ++i) {
          g_convertedHscrollbuff[i] = -*g_pHscrollbuff & 0x3FF;
        }
      }
    }
    else {
      memset(g_convertedHscrollbuff, 0, sizeof(g_convertedHscrollbuff));
    }
    g_pVdpReadPos = &g_vram[g_vdp_scrolla_adr];

    switch (g_vdp_mode) {
      case 0:
        if (g_vdp_window_height != 0) {
          FUN_0040ee9e();
          g_vscrollCopy = 0;
          memset(g_convertedHscrollbuff, 0, sizeof(g_convertedHscrollbuff));
          g_pVdpReadPos = &g_vram[0x8000];
          FUN_0040ef0c();
        }
        else {
          FUN_0040edec();
        }
        break;
      case 1:
        FUN_00414890();
        break;
      case 5:
        FUN_0041496c();
        break;
      case 2:
        FUN_0040edec();
        break;
      case 3:
        FUN_004146ac();
        break;
      case 4:
        FUN_0041439c();
        break;
    }
  }
  blitSprites();
}


// 0040632a
void saveControlsConfig(const char* pPublisherKeyName, const char* pGameKeyName, const char* pControllerKeyName, int* pConfig, ULONG size) {
  CWinRegistry registry(pPublisherKeyName);
  registry.openSubKey(pGameKeyName);
  registry.setKeyBinary(pControllerKeyName, (BYTE*)pConfig, size);
}


// 004063cd
void loadControlsConfig(const char* pPublisherKeyName, const char* pGameKeyName, const char* pControllerKeyName, int* pConfig, ULONG size) {
  CWinRegistry registry(pPublisherKeyName);
  registry.openSubKey(pGameKeyName);
  registry.queryKeyBytes(pControllerKeyName, (BYTE*)pConfig, size);
}


// 0040a98e
extern "C" void execute_sound_command(short command) {
  if (g_noSoundEffect != 0) return;

  short soundId = command;
  if (soundId < 0) {
    soundId += 256;
  }
  if (soundId < 0 || soundId > 223) return;

  int bufferId = g_soundBufferMapping[soundId];
  ULONG unknown2 = g_unknownSoundMapping[soundId];
  long unknown3 = g_unknownSoundMapping[soundId];
  ULONG unknown4 = g_unknownSoundMapping3[soundId];
  if (bufferId < 1) return;

  CSound* pSound = getSoundPtr();
  if (pSound == 0) return;
  if (pSound->getUnknown2060() != 0) return;

  int zeroBasedBufferId = bufferId - 1;
  LPDIRECTSOUNDBUFFER buffer = pSound->getSoundBuffer(zeroBasedBufferId);
  if (buffer == 0) return;

  if (zeroBasedBufferId == 119) {
    buffer->SetFrequency(g_soundFrequencies[g_unknownSoundFrequencyValue + (g_seMode == 2) * 10]);
    if (g_unknownSoundFrequencyValue < 9) {
      ++g_unknownSoundFrequencyValue;
    }
  }
  else {
    g_unknownSoundFrequencyValue = 0;
  }
  if (unknown2 >= 1) {
    if (unknown3 > 0) {
      pSound->FUN_0040a6c8(unknown2 - 1, 17, unknown3 - 1, zeroBasedBufferId, unknown4 - 1);
    }
    else {
      pSound->FUN_0040a6c8(unknown2 - 1, 17, zeroBasedBufferId, 0, 0);
    }
  }
  else {
    pSound->playBuffer(zeroBasedBufferId);
  }
}


// 0040ab4e
void playSoundEffect() {
  short mdRegisterD0 = g_mdRegisterD0 & 0xFFFF;
  if (mdRegisterD0 < 0) {
    mdRegisterD0 += 256;
  }
  if (mdRegisterD0 < 0 || mdRegisterD0 > 223) return;

  int bufferId = g_soundBufferMapping[mdRegisterD0];
  if (bufferId < 1) return;

  CSound* pSound = getSoundPtr();
  if (pSound == 0) return;
  if (pSound->getUnknown2060() != 0) return;

  int zeroBasedBufferId = bufferId - 1;
  if (pSound->getSoundBuffer(zeroBasedBufferId) == 0) return;
  pSound->playBuffer(zeroBasedBufferId);
}


// 0040ac1d
void resetSound() {
  BOOL_00856e10 = FALSE;
  g_bgmId = -1;
  getSoundPtr()->FUN_0040a697();
}


// 0040ac4d
extern "C" void execute_bgm_command(short command) {
  if (command == -31 || command == -30 || command == -2 || command == -1) {
    stopBgm();
    BOOL_00856e10 = 0;
    g_bgmId = 0;
  }
  else if (command > 50 || (command < 0 && command != -36)) {
    execute_sound_command(command);
  }
  else {
    if (command == -36) {
      command = 51;
    }
    if (command < 1 || command > 51) return;
    if (g_bgmMode == 0) return;
    EnterCriticalSection(&g_CriticalSectionObj);
    int soundId = g_soundMapping[command];
    if (!g_sonic3_alone) {
      switch (soundId) {
        case  0: soundId = 51; break;
        case 31: soundId = 50; break;
        case 40: soundId = 52; break;
        case 42: soundId = 53; break;
        case 48: soundId = 54; break;
      }
    }
    switch (soundId) {
      case 40:
      case 52:
        if (g_bgmId == 39) {
          BOOL_00856e10 = FALSE;
          g_bgmId = 0;
        }
        else {
          BOOL_00856e10 = TRUE;
        }
        break;
      default:
        g_bgmId = soundId;
        break;
    }
    if (loadBgm(soundId + 1) != 0) {
      playBgm();
    }
    LeaveCriticalSection(&g_CriticalSectionObj);
  }
}


// 0040aea5
void startBgm(char id) {
  EnterCriticalSection(&g_CriticalSectionObj);
  if (loadBgm(id + 1) != 0) {
    playBgm();
  }
  LeaveCriticalSection(&g_CriticalSectionObj);
}


// 0040aee7
void restartBgm() {
  if (BOOL_00856e10) {
    if (g_bgmId > 0) {
      EnterCriticalSection(&g_CriticalSectionObj);
      if (loadBgm((g_bgmId & 0xFF) + 1)) {
        playBgm();
      }
      LeaveCriticalSection(&g_CriticalSectionObj);
    }
    BOOL_00856e10 = FALSE;
  }
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
    IMidi*(*pGetMidiInterface)() = (IMidi*(*)())GetProcAddress(g_hMusicDll, "GetMidiInterface");
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


// 0040b099
LRESULT CALLBACK soundTestDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG: {
      g_soundTest_seId = 0;
      g_soundTest_bgmId = 0;
      POINT topLeft;
      topLeft.x = 0;
      topLeft.y = 0;
      ClientToScreen(hWnd, &topLeft);
      RECT windowRect;
      GetWindowRect(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN), &windowRect);
      DestroyWindow(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN));
      CreateUpDownControl(UDS_WRAP | UDS_ARROWKEYS | UDS_HORZ | UDS_NOTHOUSANDS | WS_VISIBLE | WS_CHILD, windowRect.left - topLeft.x,windowRect.top - topLeft.y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, hWnd, ID_SOUNDTEST_SE_UPDOWN, g_hInstance, 0, 0, 100, 0);
      GetWindowRect(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN), &windowRect);
      DestroyWindow(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN));
      CreateUpDownControl(UDS_WRAP | UDS_ARROWKEYS | UDS_HORZ | UDS_NOTHOUSANDS | WS_VISIBLE | WS_CHILD, windowRect.left - topLeft.x,windowRect.top - topLeft.y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, hWnd, ID_SOUNDTEST_BGM_UPDOWN, g_hInstance, 0, 0, 100, 0);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN), UDM_SETRANGE, 0, 168);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN), UDM_SETPOS, 0, 0);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN), UDM_SETRANGE, 0, 55);
      SendMessage(GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN), UDM_SETPOS, 0, 0);
      return TRUE;
    }
    case WM_COMMAND: {
      HWND hControlWnd = (HWND)lParam;
      ULONG id = LOWORD(wParam);
      ULONG code = HIWORD(wParam);

      switch (id) {
        case ID_SOUNDTEST_SE_PLAY:
          if (code & 0xFFFF) {
            return 0;
          }
          g_mdRegisterD0 = g_soundTest_seId + 51;
          playSoundEffect();
          return 1;
        case ID_SOUNDTEST_BGM_PLAY:
          if (code & 0xFFFF) {
            return 0;
          }
          startBgm(g_soundTest_bgmId);
          return 1;
        case ID_SOUNDTEST_BGM_STOP:
          if (code & 0xFFFF) {
            return 0;
          }
          stopBgm();
          return 1;
        case ID_SOUNDTEST_OK:
          if (code & 0xFFFF) {
            return 0;
          }
          EndDialog(hWnd, 1);
          return 1;
        case 2:
          if (code & 0xFFFF) {
            return 0;
          }
          EndDialog(hWnd, 2);
          return 1;
      }
    }
    case WM_HSCROLL: {
      ULONG request = LOWORD(wParam);
      ULONG pos = HIWORD(wParam);
      HWND hScrollBar = (HWND)lParam;
      if (GetDlgItem(hWnd, ID_SOUNDTEST_SE_UPDOWN) == hScrollBar) {
        if (request == SB_THUMBPOSITION || request == SB_THUMBTRACK) {
          g_soundTest_seId = pos;
          char buffer[64];
          wsprintf(buffer, "No. %03d", g_soundTest_seId);
          SetDlgItemText(hWnd, ID_SOUNDTEST_SE_NO, buffer);
        }
        return 1;
      }
      if (GetDlgItem(hWnd, ID_SOUNDTEST_BGM_UPDOWN) == hScrollBar) {
        if (request == SB_THUMBPOSITION || request == SB_THUMBTRACK) {
          g_soundTest_bgmId = pos;
          char buffer[64];
          wsprintf(buffer, "No. %03d", g_soundTest_bgmId);
          SetDlgItemText(hWnd, ID_SOUNDTEST_BGM_NO, buffer);
        }
        return 1;
      }
    }
  }

  return 0;
}


// 0040b54c
int openSoundTestDialog(HWND hWnd) {
  BOOL_00856e10 = FALSE;
  stopBgm();
  int ret = DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_SOUNDTEST_BASE + g_langMode), hWnd, (DLGPROC)soundTestDlgProc, 0);
  BOOL_00856e10 = TRUE;
  restartBgm();
  pauseBgm();

  return ret;
}


// 0040b5bb
void initMidiInterface(HWND hWnd) {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->init(hWnd);
  }
}


// 0040b5eb
BOOL loadBgm(int id) {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->loadSong(id, g_bgmMode != 1);
  }

  return TRUE;
}


// 0040b62e
void playBgm() {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->playSong();
  }
}


// 0040b65b
void stopBgm() {
  EnterCriticalSection(&g_CriticalSectionObj);
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->stopSong();
  }
  LeaveCriticalSection(&g_CriticalSectionObj);
}


// 0040b69e
void pauseBgm() {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->pauseSong();
  }
}


// 0040b6cb
void resumeBgm() {
  if (g_pMidiInterface != 0) {
    g_pMidiInterface->resumeSong();
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


// 0040bcdb
void pollWindowsControllers() {
  g_joystick1ButtonsDown = 0;
  g_joystick2ButtonsDown = 0;
  g_kbKeysP1Down = 0;
  g_kbKeysP2Down = 0;
  DAT_00856e50 = 0;
  DAT_00856e54 = 0;

  if (g_bDemo != 0) return;

  JOYINFOEX joyinfoex;
  memset(&joyinfoex, 0 , sizeof(joyinfoex));
  joyinfoex.dwSize = sizeof(joyinfoex);
  joyinfoex.dwFlags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNBUTTONS;
  if ((DAT_0082ddcc[3] & 0x80) && g_joystickId[0] != -1) {
    joyGetPosEx(g_joystickId[0],&joyinfoex);
    if (joyinfoex.dwXpos < g_joystickXCenter1[0]) {
      g_joystick1ButtonsDown |= 4;
    }
    else if (g_joystickXCenter2[0] < joyinfoex.dwXpos) {
      g_joystick1ButtonsDown |= 8;
    }
    if (joyinfoex.dwYpos < g_joystickYCenter1[0]) {
      g_joystick1ButtonsDown |= 1;
    }
    else if (g_joystickYCenter2[0] < joyinfoex.dwYpos) {
      g_joystick1ButtonsDown |= 2;
    }
    if (g_joystickEnoughButtons[0]) {
      if (g_debug_mode != 0) {
        if (joyinfoex.dwButtons & 1) {
          g_joystick1ButtonsDown |= 0x40;
        }
        if (joyinfoex.dwButtons & 2) {
          g_joystick1ButtonsDown |= 0x10;
        }
        if (joyinfoex.dwButtons & 4) {
          g_joystick1ButtonsDown |= 0x20;
        }
        if (joyinfoex.dwButtons & 8) {
          g_joystick1ButtonsDown |= 0x80;
        }
      }
      else {
        if (joyinfoex.dwButtons & 1) {
          g_joystick1ButtonsDown |= 0xa0;
        }
        if (joyinfoex.dwButtons & 2) {
          g_joystick1ButtonsDown |= 0x10;
        }
      }
    }
    else {
      if (joyinfoex.dwButtons & 1) {
        g_joystick1ButtonsDown |= 0xa0;
      }
      if (joyinfoex.dwButtons & 2) {
        g_joystick1ButtonsDown |= 0x10;
      }
    }
  }

  if ((DAT_0082ddcc[3] & 0x40) && g_joystickId[1] != -1) {
    joyGetPosEx(g_joystickId[1],&joyinfoex);
    if (joyinfoex.dwXpos < g_joystickXCenter1[1]) {
      g_joystick2ButtonsDown |= 4;
    }
    else if (g_joystickXCenter2[1] < joyinfoex.dwXpos) {
      g_joystick2ButtonsDown |= 8;
    }
    if (joyinfoex.dwYpos < g_joystickYCenter1[1]) {
      g_joystick2ButtonsDown |= 1;
    }
    else if (g_joystickYCenter2[1] < joyinfoex.dwYpos) {
      g_joystick2ButtonsDown |= 2;
    }
    if (g_joystickEnoughButtons[1]) {
      if (g_debug_mode != 0) {
        if (joyinfoex.dwButtons & 1) {
          g_joystick2ButtonsDown |= 0x40;
        }
        if (joyinfoex.dwButtons & 2) {
          g_joystick2ButtonsDown |= 0x10;
        }
        if (joyinfoex.dwButtons & 4) {
          g_joystick2ButtonsDown |= 0x20;
        }
        if (joyinfoex.dwButtons & 8) {
          g_joystick2ButtonsDown |= 0x80;
        }
      }
      else {
        if (joyinfoex.dwButtons & 1) {
          g_joystick2ButtonsDown |= 0xa0;
        }
        if (joyinfoex.dwButtons & 2) {
          g_joystick2ButtonsDown |= 0x10;
        }
      }
    }
    else {
      if (joyinfoex.dwButtons & 1) {
        g_joystick2ButtonsDown |= 0xa0;
      }
      if (joyinfoex.dwButtons & 2) {
        g_joystick2ButtonsDown |= 0x10;
      }
    }
  }

  if (DAT_0082ddcc[3] & 0x20) {
    if (GetAsyncKeyState(g_kbKeys[0][1]) < 0) {
      g_kbKeysP1Down |= 4;
    }
    else if (GetAsyncKeyState(g_kbKeys[0][2]) < 0) {
      g_kbKeysP1Down |= 8;
    }
    if (GetAsyncKeyState(g_kbKeys[0][0]) < 0) {
      g_kbKeysP1Down |= 1;
    }
    else if (GetAsyncKeyState(g_kbKeys[0][3]) < 0) {
      g_kbKeysP1Down |= 2;
    }
    if (GetAsyncKeyState(VK_RETURN) < 0) {
      g_kbKeysP1Down |= 0x80;
    }
    if (g_numpad_unlocked != 0) {
      if (GetAsyncKeyState(VK_NUMPAD1) < 0) {
        g_kbKeysP1Down |= 0x40;
      }
      if (GetAsyncKeyState(VK_NUMPAD2) < 0) {
        g_kbKeysP1Down |= 0x10;
      }
      if (GetAsyncKeyState(VK_NUMPAD3) < 0) {
        g_kbKeysP1Down |= 0x20;
      }
    }
    else {
      if (GetAsyncKeyState(g_kbKeys[0][4]) < 0) {
        g_kbKeysP1Down |= 0xa0;
      }
      if (GetAsyncKeyState(VK_ESCAPE) < 0) {
        g_kbKeysP1Down |= 0x10;
      }
      if (g_debug_mode != 0) {
        if (GetAsyncKeyState(VK_SPACE) < 0) {
          g_kbKeysP1Down |= 0x80;
        }
        if (GetAsyncKeyState(VK_NUMPAD1) < 0) {
          g_kbKeysP1Down |= 0x40;
        }
        if (GetAsyncKeyState(VK_NUMPAD2) < 0) {
          g_kbKeysP1Down |= 0x10;
        }
        if (GetAsyncKeyState(VK_NUMPAD3) < 0) {
          g_kbKeysP1Down |= 0x20;
        }
      }
    }
  }

  if (DAT_0082ddcc[3] & 0x10) {
    if (GetAsyncKeyState(g_kbKeys[1][1]) < 0) {
      g_kbKeysP2Down |= 4;
    }
    else if (GetAsyncKeyState(g_kbKeys[1][2]) < 0) {
      g_kbKeysP2Down |= 8;
    }
    if (GetAsyncKeyState(g_kbKeys[1][0]) < 0) {
      g_kbKeysP2Down |= 1;
    }
    else if (GetAsyncKeyState(g_kbKeys[1][3]) < 0) {
      g_kbKeysP2Down |= 2;
    }
    if (GetAsyncKeyState(g_kbKeys[1][4]) < 0) {
      g_kbKeysP2Down |= 0xa0;
    }
    if (GetAsyncKeyState(VK_ESCAPE) < 0) {
      g_kbKeysP2Down |= 0x10;
    }
    if (g_debug_mode != 0) {
      if (GetAsyncKeyState(VK_TAB) < 0) {
        g_kbKeysP2Down |= 0x80;
      }
      if (GetAsyncKeyState('Q') < 0) {
        g_kbKeysP2Down |= 0x40;
      }
      if (GetAsyncKeyState('Z') < 0) {
        g_kbKeysP2Down |= 0x10;
      }
    }
  }
}


// 0040c3d2
USHORT getPressedController1Buttons() {
  UCHAR buttons = 0;

  buttons |= DAT_0082ddcc[3] & 8 ? g_joystick1ButtonsDown : 0;
  buttons |= DAT_0082ddcc[3] & 4 ? g_joystick2ButtonsDown : 0;
  buttons |= DAT_0082ddcc[3] & 2 ? g_kbKeysP1Down : 0;
  buttons |= DAT_0082ddcc[3] & 1 ? g_kbKeysP2Down : 0;

  UCHAR newlyPressedButtons = (buttons ^ g_prevMdButtonsP1Down) & buttons;
  g_prevMdButtonsP1Down = buttons;
  return (buttons << 8) + newlyPressedButtons;
}


// 0040c4d0
USHORT getPressedController2Buttons() {
  UCHAR buttons = 0;

  buttons |= DAT_0082ddcc[2] & 8 ? g_joystick1ButtonsDown : 0;
  buttons |= DAT_0082ddcc[2] & 4 ? g_joystick2ButtonsDown : 0;
  buttons |= DAT_0082ddcc[2] & 2 ? g_kbKeysP1Down : 0;
  buttons |= DAT_0082ddcc[2] & 1 ? g_kbKeysP2Down : 0;

  UCHAR newlyPressedButtons = (buttons ^ g_prevMdButtonsP2Down) & buttons;
  g_prevMdButtonsP2Down = buttons;
  return (buttons << 8) + newlyPressedButtons;
}


// 0040c86d
void readKeyName(char* pKeyName, int key) {
  for (int i = 0; g_kbKeyCodes[i] >= 0; ++i) {
    if (g_kbKeyCodes[i] == key) {
      _mbscpy((UCHAR*)pKeyName, (const UCHAR*)g_kbKeyNames[g_langMode][i]);
      return;
    }
  }

  if ((key >= 48 && key <= 57) || (key >= 65 && key <= 90)) {
    pKeyName[0] = (char)key;
    pKeyName[1] = 0;
  }
  else {
    _mbscpy((UCHAR*)pKeyName, (const UCHAR*)"NoKey");
  }
}


// 0040c932
int getKey(char* pKeyName) {
  for (int i = 0; g_kbKeyNames[g_langMode][i][0] != 0; ++i) {
    if (strcmp(pKeyName, g_kbKeyNames[g_langMode][i]) == 0) {
      return g_kbKeyCodes[i];
    }
  }

  if (pKeyName[1] != 0) {
    return -1;
  }

  int key = (int)pKeyName[0];
  if ((key >= 48 && key <= 57) || (key >= 65 && key <= 90)) {
    return key;
  }

  return -1;
}


// 0040ca13
LRESULT CALLBACK selectKeyDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG: {
      ULONG listIndex = 0;
      ULONG currentKeyListIndex = 0;
      HWND hList = GetDlgItem(hWnd, ID_SELECTKEY_LIST);
      SendMessage(hList, LB_RESETCONTENT, 0, 0);
      char keyName[32];
      for (int key = 48; key < 58; ++key) {
        readKeyName(keyName, key);
        if (g_selectKeyDialogCurrentKey == key) {
          currentKeyListIndex = listIndex;
        }
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)keyName);
        ++listIndex;
      }
      for (int key = 65; key < 91; ++key) {
        readKeyName(keyName, key);
        if (g_selectKeyDialogCurrentKey == key) {
          currentKeyListIndex = listIndex;
        }
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)keyName);
        ++listIndex;
      }
      for (int i = 0; g_kbKeyCodes[i] >= 0; ++i) {
        readKeyName(keyName,g_kbKeyCodes[i]);
        if (g_kbKeyCodes[i] == g_selectKeyDialogCurrentKey) {
          currentKeyListIndex = listIndex;
        }
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)keyName);
        ++listIndex;
      }
      SendMessage(hList, LB_SETCURSEL, currentKeyListIndex, 0);
      return TRUE;
    }
    case WM_COMMAND: {
      ULONG id = LOWORD(wParam);
      ULONG code = HIWORD(wParam);
      if ((id == ID_SELECTKEY_OK && !(code & 0xFFFF)) || (id == ID_SELECTKEY_LIST && (code & 0xFFFF) == 2)) {
        HWND hList = GetDlgItem(hWnd, ID_SELECTKEY_LIST);
        long selectedIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
        char keyName[32];
        SendMessage(hList, LB_GETTEXT, selectedIndex, (LPARAM)keyName);
        int key = getKey(keyName);
        EndDialog(hWnd, key);
        return 1;
      }
      if (id == ID_SELECTKEY_CANCEL && !(code & 0xFFFF)) {
        EndDialog(hWnd, -1);
        return 1;
      }
    }
  }

  return 0;
}


// 0040ccc3
int openSelectKeyDialog(HWND hWnd, int currentKey) {
  g_selectKeyDialogCurrentKey = currentKey;
  return DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_SELECTKEY_BASE + g_langMode), hWnd, (DLGPROC)selectKeyDlgProc, 0);
}


// 0040ccfe
int validateKeyBinding() {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (g_kbKeysEdit[1][j] == g_kbKeysEdit[0][i] || g_kbKeysEdit[1][i] == g_kbKeysEdit[0][j]) {
        return 1;
      }
      if (i == j) continue;
      if (g_kbKeysEdit[0][j] == g_kbKeysEdit[0][i] || g_kbKeysEdit[1][j] == g_kbKeysEdit[1][i]) {
        return 1;
      }
    }
  }

  return 0;
}


// 0040cddc
LRESULT CALLBACK keyBindDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_INITDIALOG: {
      char keyName[32];
      for (int i = 0; i < 5; ++i) {
        g_kbKeysEdit[0][i] = g_kbKeys[0][i];
        readKeyName(keyName, g_kbKeysEdit[0][i]);
        SetDlgItemText(hWnd, ID_KEYBIND_PL1_BUTTON_FIRST + i, keyName);
        g_kbKeysEdit[1][i] = g_kbKeys[1][i];
        readKeyName(keyName, g_kbKeysEdit[1][i]);
        SetDlgItemText(hWnd, ID_KEYBIND_PL2_BUTTON_FIRST + i, keyName);
      }
      return TRUE;
    }
    case WM_COMMAND: {
      HWND hControlWnd = (HWND)lParam;
      ULONG id = LOWORD(wParam);
      ULONG code = HIWORD(wParam);

      switch (id) {
        case ID_KEYBIND_OK:
          if (code & 0xFFFF) {
            return 0;
          }
          if (validateKeyBinding() != 0) {
            MessageBox(hWnd, "Illegal Key Binding", "Key Bind", MB_OK);
            return 1;
          }
          for (int i = 0; i < 5; ++i) {
            g_kbKeys[0][i] = g_kbKeysEdit[0][i];
            g_kbKeys[1][i] = g_kbKeysEdit[1][i];
          }
          saveControlsConfig("SEGA", "Sonic3K", "KeyBind", (int*)g_kbKeys, sizeof(g_kbKeys));
          EndDialog(hWnd, ID_KEYBIND_OK);
          return 1;
        case ID_KEYBIND_CANCEL:
          if (code & 0xFFFF) {
            return 0;
          }
          EndDialog(hWnd, ID_KEYBIND_CANCEL);
          return 1;
        case ID_KEYBIND_RESTORE: {
          if (code & 0xFFFF) {
            return 0;
          }
          char keyName[32];
          for (int i = 0; i < 5; ++i) {
            g_kbKeysEdit[0][i] = g_kbKeys[0][i];
            readKeyName(keyName, g_kbKeysEdit[0][i]);
            SetDlgItemText(hWnd , ID_KEYBIND_PL1_BUTTON_FIRST + i, keyName);
            g_kbKeysEdit[1][i] = g_kbKeys[1][i];
            readKeyName(keyName, g_kbKeysEdit[1][i]);
            SetDlgItemText(hWnd, ID_KEYBIND_PL2_BUTTON_FIRST + i, keyName);
          }
          return 1;
        }
        default:
          if (id >= ID_KEYBIND_PL1_BUTTON_FIRST && id <= ID_KEYBIND_PL1_BUTTON_LAST) {
            int selectedKey = openSelectKeyDialog(hWnd, ((int*)g_kbKeysEdit)[id - 1000]);
            if (selectedKey >= 0) {
              ((int*)g_kbKeysEdit)[id - 1000] = selectedKey;
              char keyName[32];
              readKeyName(keyName, ((int*)g_kbKeysEdit)[id - 1000]);
              SetDlgItemText(hWnd, id, keyName);
            }
            return 1;
          }
          if (id >= ID_KEYBIND_PL2_BUTTON_FIRST && id <= ID_KEYBIND_PL2_BUTTON_LAST) {
            int selectedKey = openSelectKeyDialog(hWnd, ((int*)g_kbKeysEdit)[id - 1000]);
            if (selectedKey >= 0) {
              ((int*)g_kbKeysEdit)[id - 1000] = selectedKey;
              char keyName[32];
              readKeyName(keyName, ((int*)g_kbKeysEdit)[id - 1000]);
              SetDlgItemText(hWnd, id, keyName);
            }
            return 1;
          }
      }
    }
  }

  return 0;
}


// 0040d20d
void openKeyBindDialog(HWND hWnd) {
  DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_KEYBIND_BASE + g_langMode), hWnd, (DLGPROC)soundTestDlgProc, 0);
}


// 0040d240
LRESULT CALLBACK joyStickDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  char* pDontUseText = g_dontUseText[g_langMode];

  switch (msg) {
    case WM_INITDIALOG: {
      g_joystickCnt = joyGetNumDevs();
      if (g_joystickCnt > 32) {
        g_joystickCnt = 32;
      }
      HWND hJoystickP1 = GetDlgItem(hWnd, ID_JOYSTICK_P1);
      HWND hJoystickP2 = GetDlgItem(hWnd, ID_JOYSTICK_P2);
      SendMessage(hJoystickP1, CB_RESETCONTENT, 0, 0);
      SendMessage(hJoystickP2, CB_RESETCONTENT, 0, 0);
      SendMessage(hJoystickP1, CB_ADDSTRING, 0, (WPARAM)pDontUseText);
      SendMessage(hJoystickP2, CB_ADDSTRING, 0, (WPARAM)pDontUseText);
      JOYCAPS joycaps;
      char buffer[64];
      for (unsigned int i = 0; i < g_joystickCnt; ++i) {
        memset(&joycaps, 0, sizeof(joycaps));
        if (joyGetDevCaps(i, &joycaps, sizeof(joycaps)) != JOYERR_NOERROR) {
          g_joystickAvailability[i] = FALSE;
        }
        else {
          g_joystickAvailability[i] = TRUE;
          wsprintf(buffer, "Joystick%d", i + 1);
          SendMessage(hJoystickP1, CB_ADDSTRING, 0, (LPARAM)buffer);
          SendMessage(hJoystickP2, CB_ADDSTRING, 0, (LPARAM)buffer);
        }
      }
      if (g_joystickId[0] == -1) {
        SendMessage(hJoystickP1, CB_SETCURSEL, 0, 0);
      }
      else {
        ULONG comboIndex = 0;
        for (unsigned int i = 0; i < g_joystickCnt; ++i) {
          if (g_joystickAvailability[i]) {
            ++comboIndex;
            if (g_joystickId[0] == i) {
              SendMessage(hJoystickP1, CB_SETCURSEL, comboIndex, 0);
              break;
            }
          }
        }
      }
      if (g_joystickId[1] == -1) {
        SendMessage(hJoystickP2, CB_SETCURSEL, 0, 0);
      }
      else {
        ULONG comboIndex = 0;
        for (unsigned int i = 0; i < g_joystickCnt; ++i) {
          if (g_joystickAvailability[i]) {
            ++comboIndex;
            if (g_joystickId[1] == i) {
              SendMessage(hJoystickP2, CB_SETCURSEL, comboIndex, 0);
              break;
            }
          }
        }
      }
      return TRUE;
    }
    case WM_COMMAND: {
      HWND hControlWnd = (HWND)lParam;
      ULONG id = LOWORD(wParam);
      ULONG code = HIWORD(wParam);

      switch (id) {
        case ID_JOYSTICK_OK: {
          HWND hJoystickP1 = GetDlgItem(hWnd, ID_JOYSTICK_P1);
          HWND hJoystickP2 = GetDlgItem(hWnd, ID_JOYSTICK_P2);
          long selectedIndexP1 = SendMessage(hJoystickP1, CB_GETCURSEL, 0, 0);
          long selectedIndexP2 = SendMessage(hJoystickP2, CB_GETCURSEL, 0, 0);
          int newJoystickIdP1 = -1;
          if (selectedIndexP1 > 0) {
            for (unsigned int i = 0; i < g_joystickCnt; ++i) {
              if (g_joystickAvailability[i]) {
                --selectedIndexP1;
                if (selectedIndexP1 == 0) {
                  newJoystickIdP1 = i;
                  break;
                }
              }
            }
          }
          int newJoystickIdP2 = -1;
          if (selectedIndexP2 > 0) {
            for (unsigned int i = 0; i < g_joystickCnt; ++i) {
              if (g_joystickAvailability[i]) {
                --selectedIndexP1;
                if (selectedIndexP1 == 0) {
                  newJoystickIdP2 = i;
                  break;
                }
              }
            }
          }
          if ((newJoystickIdP1 != -1 || newJoystickIdP2 != -1) && newJoystickIdP1 == newJoystickIdP2) {
            MessageBox(hWnd, "Illegal Joystick Assignment", "Joystick", MB_OK);
            return 1;
          }
          g_joystickId[0] = newJoystickIdP1;
          g_joystickId[1] = newJoystickIdP2;
          saveControlsConfig("SEGA", "Sonic3K", "PadBind", g_joystickId, sizeof(g_joystickId));
          configureJoystick(0);
          configureJoystick(1);
          EndDialog(hWnd, ID_JOYSTICK_OK);
          return 1;
        }
        case ID_JOYSTICK_CANCEL:
          if (code & 0xFFFF) {
            return 0;
          }
          EndDialog(hWnd, ID_JOYSTICK_CANCEL);
          return 1;
      }
    }
  }

  return 0;
}


// 0040d802
void openJoyStickDialog(HWND hWnd) {
  DialogBoxParam(g_hInstance, MAKEINTRESOURCE(IDD_JOYSTICK_BASE + g_langMode), hWnd, (DLGPROC)joyStickDlgProc, 0);
}
