#include "globals.h"
#include "macros.h"
#include "vdp.h"
static void blit_scanline_ver1(unsigned short* p_scrollplane, unsigned char vscroll_low);
static unsigned char pixeloffsets[8];
static unsigned char* blit_8pixels_ver1(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low);
static unsigned char* blit_remainingpixels_ver1(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low);
static unsigned char* blit_remainingpixels_ver2(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low);
static void blit_scanline_ver2(unsigned short* p_scrollplane, unsigned char vscroll_low);
static unsigned char pixelconversions[128];
static unsigned char* blit_8pixels_ver2(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low);
static unsigned char* blit_remainingpixels_ver3(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low);
static unsigned char* blit_remainingpixels_ver4(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low);
static void vint_handler_ver1(unsigned char* p_vscroll_high, unsigned char** pp_scrollplane, unsigned char* p_vscroll_low);
static void blit_scanline_ver3(unsigned short* p_scrollplane, unsigned char vscroll_low);
static void blit_scanline_ver4(unsigned short* p_scrollplane, unsigned char vscroll_low);
static void vint_handler_ver2(unsigned char* p_vscroll_high, unsigned char** pp_scrollplane, unsigned char* p_vscroll_low);
static void blit_scanline_ver5(unsigned short* p_scrollplane, unsigned char vscroll_low);
static void blit_scanline_ver6(unsigned short* p_scrollplane, unsigned char vscroll_low);
static void blit_scanline_ver7(unsigned short* p_scrollplane, unsigned char vscroll_low);
static unsigned char pixeloffsets2[8];
static unsigned char* blit_8pixels_ver3(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low);
static unsigned char* blit_remainingpixels_ver5(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low);
static unsigned char* blit_remainingpixels_ver6(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low);
static void blit_columnrow_ver1(int scanline, int vscroll_index, unsigned long hscroll);
static void blit_columnrow_ver2(int scanline, int vscroll_index, unsigned long hscroll);
static void FUN_00411a9e(Sprite* p_sprite);


// 0040edec
void FUN_0040edec() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ) {
    blit_scanline_ver1((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x1F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
    ++i;
    if (i == g_vIntScanline) {
      vscroll_high = g_ram.scra_v_posit_copy + g_vIntScanline;
      g_vscrollCopy = vscroll_high;
      vscroll_high >>= 3;
      vscroll_high &= 0x1F;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
      vscroll_low = g_vscrollCopy & 7;
      g_vIntScanline = 0;
    }
  }
}


// 0040ee9e
void FUN_0040ee9e() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < DAT_00854758; ++i) {
    blit_scanline_ver1((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x1F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
  }
}


// 0040ef0c
void FUN_0040ef0c() {
  g_vscrollCopy += DAT_00854758;
  g_pPixelBuffer = &g_pixelBuffer[DAT_00854758 * 320];
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver1((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x1F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
  }
}


// 0040ef8e
static void blit_scanline_ver1(unsigned short* p_scrollplane, unsigned char vscroll_low) {
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  int index = *g_pConvertedHscrollbuff >> 3 & 0x3F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = *g_pConvertedHscrollbuff & 7;

  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver1(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x3F;

  for (int i = 39; i != 0; --i) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
    ++index;
    index &= 0x3F;
  }

  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver2(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++g_pConvertedHscrollbuff;
  g_pPixelBuffer += 320;
}


/* 0040f004 */ static unsigned char pixeloffsets[8] = { 16, 32, 48, 64, -112, -96, -80, -64 };


// 0040f00c
static unsigned char* blit_8pixels_ver1(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  if (pixels != 0) {
    pixels = BYTESWAP(pixels);
    if (IS_TILE_HFLIP(tile)) {
      signed char offset = pixeloffsets[tile >> 13];
      if (offset < 0) {
        for (int i = 0; i < 8; ++i) {
          if (pixels & 0xF) {
            *p_pixelbuffer = (pixels & 0xF) + offset;
          }
          ROTATE_RIGHT(pixels, 4);
          ++p_pixelbuffer;
        }
      }
      else {
        for (int i = 0; i < 8; ++i) {
          if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
            *p_pixelbuffer = (pixels & 0xF) + offset;
          }
          ROTATE_RIGHT(pixels, 4);
          ++p_pixelbuffer;
        }
      }
    }
    else {
      signed char offset = pixeloffsets[tile >> 13];
      if (offset < 0) {
        for (int i = 0; i < 8; ++i) {
          ROTATE_LEFT(pixels, 4);
          if (pixels & 0xF) {
            *p_pixelbuffer = (pixels & 0xF) + offset;
          }
          ++p_pixelbuffer;
        }
      }
      else {
        for (int i = 0; i < 8; ++i) {
          ROTATE_LEFT(pixels, 4);
          if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
            *p_pixelbuffer = (pixels & 0xF) + offset;
          }
          ++p_pixelbuffer;
        }
      }
    }
  }
  else {
    p_pixelbuffer += 8;
  }

  return p_pixelbuffer;
}


// 0040f32d
static unsigned char* blit_remainingpixels_ver1(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  pixels = BYTESWAP(pixels);
  unsigned rotatebit_cnt = hscroll_low << 2;
  if (IS_TILE_HFLIP(tile)) {
    ROTATE_RIGHT(pixels, rotatebit_cnt);
    signed char offset = pixeloffsets[tile >> 13];
    unsigned char cnt = 8 - hscroll_low;
    if (offset < 0) {
      do {
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--cnt != 0);
    }
    else {
      do {
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--cnt != 0);
    }
  }
  else {
    ROTATE_LEFT(pixels, rotatebit_cnt);
    signed char offset = pixeloffsets[tile >> 13];
    unsigned char cnt = 8 - hscroll_low;
    if (offset < 8) {
      do {
        ROTATE_LEFT(pixels, 4);
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ++p_pixelbuffer;
      } while (--cnt != 0);
    }
    else {
      do {
        ROTATE_LEFT(pixels, 4);
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ++p_pixelbuffer;
      } while (--cnt != 0);
    }
  }

  return p_pixelbuffer;
}


// 0040f401
static unsigned char* blit_remainingpixels_ver2(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  pixels = BYTESWAP(pixels);
  if (IS_TILE_HFLIP(tile)) {
    signed char offset = pixeloffsets[tile >> 13];
    if (offset < 0) {
      do {
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
    else {
      do {
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
  }
  else {
    signed char offset = pixeloffsets[tile >> 13];
    if (offset < 0) {
      do {
        ROTATE_LEFT(pixels, 4);
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
    else {
      do {
        ROTATE_LEFT(pixels, 4);
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
  }

  return p_pixelbuffer;
}


// 0040f4c8
void FUN_0040f4c8() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver2((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x1F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
  }
}


// 0040f536
static void blit_scanline_ver2(unsigned short* p_scrollplane, unsigned char vscroll_low) {
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  int index = *g_pConvertedHscrollbuff >> 3 & 0x3F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = *g_pConvertedHscrollbuff & 7;

  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver3(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x3F;

  for (int i = 39; i != 0; --i) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
    ++index;
    index &= 0x3F;
  }

  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver4(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++g_pConvertedHscrollbuff;
  g_pPixelBuffer += 320;
}


/* 0040f5ac */ static unsigned char pixelconversions[128] = {
   16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
   16,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
   16,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
   16,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
   16, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
   16, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
   16, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
   16, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207
};


// 0040f62c
static unsigned char* blit_8pixels_ver2(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  if (IS_TILE_HFLIP(tile)) {
    ROTATE_LEFT(pixels, 8);
    unsigned char* p_pixelconversions = &pixelconversions[tile >> 9 & 0x70];

    for (int i = 0; i < 4; ++i) {
      p_pixelbuffer[1] = p_pixelconversions[(pixels & 0xFF) >> 4];
      p_pixelbuffer[0] = p_pixelconversions[pixels & 0xF];
      ROTATE_LEFT(pixels, 8);
      p_pixelbuffer += 2;
    }
  }
  else {
    unsigned char* p_pixelconversions = &pixelconversions[tile >> 9 & 0x70];

    for (int i = 0; i < 4; ++i) {
      p_pixelbuffer[0] = p_pixelconversions[(pixels & 0xFF) >> 4];
      p_pixelbuffer[1] = p_pixelconversions[pixels & 0xF];
      pixels >>= 8;
      p_pixelbuffer += 2;
    }
  }

  return p_pixelbuffer;
}


// 0040f778
static unsigned char* blit_remainingpixels_ver3(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  pixels = BYTESWAP(pixels);
  unsigned rotatebit_cnt = hscroll_low << 2;
  if (IS_TILE_HFLIP(tile)) {
    ROTATE_RIGHT(pixels, rotatebit_cnt);
    unsigned char* p_pixelconversions = &pixelconversions[tile >> 9 & 0x70];
    unsigned char cnt = 8 - hscroll_low;

    do {
      *p_pixelbuffer++ = p_pixelconversions[pixels & 0xF];
      ROTATE_RIGHT(pixels, 4);
    } while (--cnt != 0);
  }
  else {
    ROTATE_LEFT(pixels, rotatebit_cnt);
    unsigned char* p_pixelconversions = &pixelconversions[tile >> 9 & 0x70];
    unsigned char cnt = 8 - hscroll_low;

    do {
      ROTATE_LEFT(pixels, 4);
      *p_pixelbuffer++ = p_pixelconversions[pixels & 0xF];
    } while (--cnt != 0);
  }

  return p_pixelbuffer;
}


// 0040f810
static unsigned char* blit_remainingpixels_ver4(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  pixels = BYTESWAP(pixels);
  if (IS_TILE_HFLIP(tile)) {
    unsigned char* p_pixelconversions = &pixelconversions[tile >> 9 & 0x70];

    do {
      *p_pixelbuffer++ = p_pixelconversions[pixels & 0xF];
      ROTATE_RIGHT(pixels, 4);
    } while (--hscroll_low != 0);
  }
  else {
    unsigned char* p_pixelconversions = &pixelconversions[tile >> 9 & 0x70];

    do {
      ROTATE_LEFT(pixels, 4);
      *p_pixelbuffer++ = p_pixelconversions[pixels & 0xF];
    } while (--hscroll_low != 0);
  }

  return p_pixelbuffer;
}


// 0040f89b
void FUN_0040f89b(unsigned long* p_surface, long pitch) {
  unsigned long* p_pixelbuffer = (unsigned long*)g_pixelBuffer;
  pitch -= 320;
  unsigned char hint = g_ram.vdp_hint_cache;
  if (DAT_008549dc != 0) {
    hint = 255;
  }

  for (int scanline = 0; scanline < 224; ++scanline) {
    if (scanline < hint) {
      for (int i = 20; i != 0; --i) {
        *p_surface++ = *p_pixelbuffer++ & 0x7F7F7F7F;
        *p_surface++ = *p_pixelbuffer++ & 0x7F7F7F7F;
        *p_surface++ = *p_pixelbuffer++ & 0x7F7F7F7F;
        *p_surface++ = *p_pixelbuffer++ & 0x7F7F7F7F;
      }
    }
    else {
      for (int i = 20; i != 0; --i) {
        *p_surface++ = *p_pixelbuffer++ | 0x80808080;
        *p_surface++ = *p_pixelbuffer++ | 0x80808080;
        *p_surface++ = *p_pixelbuffer++ | 0x80808080;
        *p_surface++ = *p_pixelbuffer++ | 0x80808080;
      }
    }
    p_surface = (unsigned long*)((unsigned char*)p_surface + pitch);
  }
}


// 0040f96a
void FUN_0040f96a(unsigned long* p_surface, long pitch) {
  unsigned long* p_pixelbuffer = (unsigned long*)g_pixelBuffer;
  long pitch2 = pitch * 2 - 640;
  unsigned char hint = g_ram.vdp_hint_cache;
  if (DAT_008549dc != 0) {
    hint = 255;
  }

  for (int scanline = 0; scanline < 224; ++scanline) {
    if (scanline < hint) {
      for (int i = 20; i != 0; --i) {
        unsigned long pixel = *p_pixelbuffer++ & 0x7F7F7F7F;
        unsigned long pixel_mod = (pixel       & 0x000000FF)
                                | (pixel << 8  & 0x00FFFF00)
                                | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
        pixel = *p_pixelbuffer++ & 0x7F7F7F7F;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
        pixel = *p_pixelbuffer++ & 0x7F7F7F7F;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
        pixel = *p_pixelbuffer++ & 0x7F7F7F7F;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
      }
    }
    else {
      for (int i = 20; i != 0; --i) {
        unsigned long pixel = *p_pixelbuffer++ & 0x80808080;
        unsigned long pixel_mod = (pixel       & 0x000000FF)
                                | (pixel << 8  & 0x00FFFF00)
                                | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
        pixel = *p_pixelbuffer++ & 0x80808080;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
        pixel = *p_pixelbuffer++ & 0x80808080;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
        pixel = *p_pixelbuffer++ & 0x80808080;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        pixel >>= 16;
        p_surface[0] = pixel_mod;
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
        pixel_mod = (pixel       & 0x000000FF)
                  | (pixel << 8  & 0x00FFFF00)
                  | (pixel << 16 & 0xFF000000);
        ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
        p_surface[1] = pixel_mod;
        p_surface += 2;
      }
    }
    p_surface = (unsigned long*)((unsigned char*)p_surface + pitch2);
  }
}


// 0040fceb
void FUN_0040fceb(unsigned long* p_surface, long pitch) {
  unsigned long* p_pixelbuffer = (unsigned long*)g_pixelBuffer;
  pitch -= 320;
  unsigned char hint = g_ram.vdp_hint_cache;

  for (int scanline = 0; scanline < 224; ++scanline) {
    for (int i = 20; i != 0; --i) {
      *p_surface++ = *p_pixelbuffer++;
      *p_surface++ = *p_pixelbuffer++;
      *p_surface++ = *p_pixelbuffer++;
      *p_surface++ = *p_pixelbuffer++;
    }
    p_surface = (unsigned long*)((unsigned char*)p_surface + pitch);
  }
}


// 0040fd4f
void FUN_0040fd4f(unsigned long* p_surface, long pitch) {
  unsigned long* p_pixelbuffer = (unsigned long*)g_pixelBuffer;
  long pitch2 = pitch * 2 - 640;
  unsigned char hint = g_ram.vdp_hint_cache;

  for (int scanline = 0; scanline < 224; ++scanline) {
    for (int i = 20; i != 0; --i) {
      unsigned long pixel = *p_pixelbuffer++;
      unsigned long pixel_mod = (pixel       & 0x000000FF)
                              | (pixel << 8  & 0x00FFFF00)
                              | (pixel << 16 & 0xFF000000);
      pixel >>= 16;
      p_surface[0] = pixel_mod;
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
      pixel_mod = (pixel       & 0x000000FF)
                | (pixel << 8  & 0x00FFFF00)
                | (pixel << 16 & 0xFF000000);
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
      p_surface[1] = pixel_mod;
      p_surface += 2;
      pixel = *p_pixelbuffer++;
      pixel_mod = (pixel       & 0x000000FF)
                | (pixel << 8  & 0x00FFFF00)
                | (pixel << 16 & 0xFF000000);
      pixel >>= 16;
      p_surface[0] = pixel_mod;
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
      pixel_mod = (pixel       & 0x000000FF)
                | (pixel << 8  & 0x00FFFF00)
                | (pixel << 16 & 0xFF000000);
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
      p_surface[1] = pixel_mod;
      p_surface += 2;
      pixel = *p_pixelbuffer++;
      pixel_mod = (pixel       & 0x000000FF)
                | (pixel << 8  & 0x00FFFF00)
                | (pixel << 16 & 0xFF000000);
      pixel >>= 16;
      p_surface[0] = pixel_mod;
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
      pixel_mod = (pixel       & 0x000000FF)
                | (pixel << 8  & 0x00FFFF00)
                | (pixel << 16 & 0xFF000000);
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
      p_surface[1] = pixel_mod;
      p_surface += 2;
      pixel = *p_pixelbuffer++;
      pixel_mod = (pixel       & 0x000000FF)
                | (pixel << 8  & 0x00FFFF00)
                | (pixel << 16 & 0xFF000000);
      pixel >>= 16;
      p_surface[0] = pixel_mod;
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[0] = pixel_mod;
      pixel_mod = (pixel       & 0x000000FF)
                | (pixel << 8  & 0x00FFFF00)
                | (pixel << 16 & 0xFF000000);
      ((unsigned long*)&((unsigned char*)p_surface)[pitch])[1] = pixel_mod;
      p_surface[1] = pixel_mod;
      p_surface += 2;
    }
    p_surface = (unsigned long*)((unsigned char*)p_surface + pitch2);
  }
}


// 00410384
void copy_map_vram(unsigned short* p_source, unsigned short offset, unsigned long row_cnt, unsigned long cell_cnt) {
  unsigned short* p_destination = (unsigned short*)&g_mdVram[offset];
  unsigned long row_offset = (128 - (cell_cnt + 1) * 2) / 2;
  for (int row = row_cnt + 1; row != 0 ; --row) {
    for (int cell = cell_cnt + 1; cell != 0 ; --cell) {
      *p_destination++ = *p_source++;
    }
    p_destination += row_offset;
  }
}


// 00410426
void copy_data_vram(void* p_source, unsigned short offset, unsigned short size) {
  memcpy(&g_mdVram[offset], p_source, size * 2);
}


// 0041434c
static void vint_handler_ver1(unsigned char* p_vscroll_high, unsigned char** pp_scrollplane, unsigned char* p_vscroll_low) {
  if (DAT_00856df4 != 0) {
    g_vscrollCopy = g_ram.vs_vscroll >> 16;
  }
  else {
    ++DAT_00856df4;
    g_vscrollCopy = g_ram.vs_vscroll & 0xFFFF;
  }
  *p_vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  *pp_scrollplane = &g_pVdpReadPos[*p_vscroll_high << 8];
  *p_vscroll_low = g_vscrollCopy & 7;
}


// 0041439c
void FUN_0041439c() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 8];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver3((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x1F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 8];
    }
    if (i + 1 == g_vIntScanline) {
      vint_handler_ver1(&vscroll_high, &p_scrollplane, &vscroll_low);
    }
  }
}


// 00414418
static void blit_scanline_ver3(unsigned short* p_scrollplane, unsigned char vscroll_low) {
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  int index = *g_pConvertedHscrollbuff >> 3 & 0x7F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = *g_pConvertedHscrollbuff & 7;

  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver1(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x7F;

  for (int i = 39; i != 0; --i) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
    ++index;
    index &= 0x7F;
  }

  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver2(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++g_pConvertedHscrollbuff;
  g_pPixelBuffer += 320;
}


// 0041448e
void FUN_0041448e() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 8];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver4((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x1F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 8];
    }
    if (i + 1 == g_vIntScanline) {
      vint_handler_ver1(&vscroll_high, &p_scrollplane, &vscroll_low);
    }
  }
}


// 0041450a
static void blit_scanline_ver4(unsigned short* p_scrollplane, unsigned char vscroll_low) {
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  int index = *g_pConvertedHscrollbuff >> 3 & 0x7F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = *g_pConvertedHscrollbuff & 7;

  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver3(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x7F;

  for (int i = 39; i != 0; --i) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
    ++index;
    index &= 0x7F;
  }

  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver4(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++g_pConvertedHscrollbuff;
  g_pPixelBuffer += 320;
}


// 004145ee
void FUN_004145ee() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x1F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 8];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver4((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x1F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 8];
    }
  }
}


// 0041465c
static void vint_handler_ver2(unsigned char* p_vscroll_high, unsigned char** pp_scrollplane, unsigned char* p_vscroll_low) {
  if (DAT_00856df4 != 0) {
    g_vscrollCopy = g_ram.vs_vscroll >> 16;
  }
  else {
    ++DAT_00856df4;
    g_vscrollCopy = g_ram.vs_vscroll & 0xFFFF;
  }
  *p_vscroll_high = g_vscrollCopy >> 3 & 0x3F;
  *pp_scrollplane = &g_pVdpReadPos[*p_vscroll_high << 7];
  *p_vscroll_low = g_vscrollCopy & 7;
}


// 004146ac
void FUN_004146ac() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x3F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver5((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x3F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
    if (i + i == g_vIntScanline) {
      vint_handler_ver2(&vscroll_high, &p_scrollplane, &vscroll_low);
    }
  }
}


// 00414728
static void blit_scanline_ver5(unsigned short* p_scrollplane, unsigned char vscroll_low) {
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  int index = *g_pConvertedHscrollbuff >> 3 & 0x3F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = *g_pConvertedHscrollbuff & 7;

  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver1(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x3F;

  for (int i = 39; i != 0; --i) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
    ++index;
    index &= 0x3F;
  }

  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver2(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++g_pConvertedHscrollbuff;
  g_pPixelBuffer += 320;
}


// 0041479e
void FUN_0041479e() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x3F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver6((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x3F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
    if (i + i == g_vIntScanline) {
      vint_handler_ver2(&vscroll_high, &p_scrollplane, &vscroll_low);
    }
  }
}


// 0041481a
static void blit_scanline_ver6(unsigned short* p_scrollplane, unsigned char vscroll_low) {
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  int index = *g_pConvertedHscrollbuff >> 3 & 0x3F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = *g_pConvertedHscrollbuff & 7;

  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver3(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x3F;

  for (int i = 39; i != 0; --i) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
    ++index;
    index &= 0x3F;
  }

  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver4(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++g_pConvertedHscrollbuff;
  g_pPixelBuffer += 320;
}


// 00414890
void FUN_00414890() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x3F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver5((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x3F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
  }
}


// 004148fe
void FUN_004148fe() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x3F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver6((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x3F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
  }
}


// 0041496c
void FUN_0041496c() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;
  unsigned char vscroll_high = g_vscrollCopy >> 3 & 0x3F;
  unsigned char* p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
  unsigned char vscroll_low = g_vscrollCopy & 7;

  for (int i = 0; i < 224; ++i) {
    blit_scanline_ver7((unsigned short*)p_scrollplane, vscroll_low);
    ++vscroll_low;
    if (vscroll_low >= 8) {
      ++vscroll_high;
      vscroll_high &= 0x3F;
      vscroll_low = 0;
      p_scrollplane = &g_pVdpReadPos[vscroll_high << 7];
    }
  }
}


// 004149da
static void blit_scanline_ver7(unsigned short* p_scrollplane, unsigned char vscroll_low) {
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  int index = *g_pConvertedHscrollbuff >> 3 & 0x3F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = *g_pConvertedHscrollbuff & 7;

  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver3(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver5(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x3F;

  for (int i = 39; i != 0; --i) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_8pixels_ver3(p_pixelbuffer, tile, vscroll_low);
    ++index;
    index &= 0x3F;
  }

  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver6(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++g_pConvertedHscrollbuff;
  g_pPixelBuffer += 320;
}


/* 00414a50 */ static unsigned char pixeloffsets2[8] = { 16, 32, 48, 64, -112, -96, -80, -64 };


//00414a58
static unsigned char* blit_8pixels_ver3(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  pixels = BYTESWAP(pixels);
  if (IS_TILE_HFLIP(tile)) {
    signed char offset = pixeloffsets2[tile >> 13];
    if (offset < 0) {
      for (int i = 0; i < 8; ++i) {
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        else {
          *p_pixelbuffer |= 0x80;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      }
    }
    else {
      for (int i = 0; i < 8; ++i) {
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      }
    }
  }
  else {
    signed char offset = pixeloffsets2[tile >> 13];
    if (offset < 0) {
      for (int i = 0; i < 8; ++i) {
        ROTATE_LEFT(pixels, 4);
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        else {
          *p_pixelbuffer |= 0x80;
        }
        ++p_pixelbuffer;
      }
    }
    else {
      for (int i = 0; i < 8; ++i) {
        ROTATE_LEFT(pixels, 4);
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ++p_pixelbuffer;
      }
    }
  }

  return p_pixelbuffer;
}


// 00414dc1
static unsigned char* blit_remainingpixels_ver5(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  pixels = BYTESWAP(pixels);
  unsigned rotatebit_cnt = hscroll_low << 2;
  if (IS_TILE_HFLIP(tile)) {
    ROTATE_RIGHT(pixels, rotatebit_cnt);
    signed char offset = pixeloffsets2[tile >> 13];
    unsigned char cnt = 8 - hscroll_low;
    if (offset < 0) {
      do {
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        else {
          *p_pixelbuffer |= 0x80;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--cnt != 0);
    }
    else {
      do {
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--cnt != 0);
    }
  }
  else {
    ROTATE_LEFT(pixels, rotatebit_cnt);
    signed char offset = pixeloffsets2[tile >> 13];
    unsigned char cnt = 8 - hscroll_low;
    if (offset < 0) {
      do {
        ROTATE_LEFT(pixels, 4);
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        else {
          *p_pixelbuffer |= 0x80;
        }
        ++p_pixelbuffer;
      } while (--cnt != 0);
    }
    else {
      do {
        ROTATE_LEFT(pixels, 4);
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ++p_pixelbuffer;
      }
      while (--cnt != 0);
    }
  }

  return p_pixelbuffer;
}


// 00414e9f
static unsigned char* blit_remainingpixels_ver6(unsigned char* p_pixelbuffer, unsigned short tile, unsigned char vscroll_low, unsigned char hscroll_low) {
  unsigned long* p_vram = (unsigned long*)&g_mdVram[(tile & 0x7FF) << 5];
  unsigned long pixels;
  if (IS_TILE_VFLIP(tile)) {
    pixels = p_vram[7 - vscroll_low];
  }
  else {
    pixels = p_vram[vscroll_low];
  }
  pixels = BYTESWAP(pixels);
  if (IS_TILE_HFLIP(tile)) {
    signed char offset = pixeloffsets2[tile >> 13];
    if (offset < 0) {
      do {
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        else {
          *p_pixelbuffer |= 0x80;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
    else {
      do {
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ROTATE_RIGHT(pixels, 4);
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
  }
  else {
    signed char offset = pixeloffsets2[tile >> 13];
    if (offset < 0) {
      do {
        ROTATE_LEFT(pixels, 4);
        if (pixels & 0xF) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        else {
          *p_pixelbuffer |= 0x80;
        }
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
    else {
      do {
        ROTATE_LEFT(pixels, 4);
        if (!(*p_pixelbuffer & 0x80) && (pixels & 0xF)) {
          *p_pixelbuffer = (pixels & 0xF) + offset;
        }
        ++p_pixelbuffer;
      } while (--hscroll_low != 0);
    }
  }

  return p_pixelbuffer;
}


// 00414f70
void FUN_00414f70() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;

  for (int scanline = 0; scanline < 224; ++scanline) {
    for (int vscroll_index = 0; vscroll_index < 20; ++vscroll_index) {
      blit_columnrow_ver1(scanline, vscroll_index, *g_pConvertedHscrollbuff);
    }
  }
}


// 00414fb6
static void blit_columnrow_ver1(int scanline, int vscroll_index, unsigned long hscroll) {
  unsigned long vscroll_high = g_mdVsram[vscroll_index] + scanline;
  unsigned char vscroll_low = vscroll_high & 7;
  hscroll += vscroll_index << 4;
  int index = (vscroll_high >> 3 & 0x1F) << 7;
  unsigned short* p_scrollplane = (unsigned short*)&g_pVdpReadPos[index];
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  index = hscroll >> 3 & 0x3F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = hscroll & 7;
  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver1(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x3F;
  tile = p_scrollplane[index];
  p_pixelbuffer = blit_8pixels_ver1(p_pixelbuffer, tile, vscroll_low);
  ++index;
  index &= 0x3F;
  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver2(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  g_pPixelBuffer += 16;
}


// 00415039
void FUN_00415039() {
  g_pPixelBuffer = g_pixelBuffer;
  g_pConvertedHscrollbuff = g_convertedHscrollbuff;

  for (int scanline = 0; scanline < 224; ++scanline) {
    for (int vscroll_index = 0; vscroll_index < 20; ++vscroll_index) {
      blit_columnrow_ver2(scanline, vscroll_index, *g_pConvertedHscrollbuff);
    }
    ++g_pConvertedHscrollbuff;
  }
}


// 0041507f
static void blit_columnrow_ver2(int scanline, int vscroll_index, unsigned long hscroll) {
  unsigned long vscroll_high = g_mdVsram[vscroll_index] + scanline;
  unsigned char vscroll_low = vscroll_high & 7;
  hscroll += vscroll_index << 4;
  int index = (vscroll_high >> 3 & 0x1F) << 7;
  unsigned short* p_scrollplane = (unsigned short*)&g_pVdpReadPos[index];
  unsigned char* p_pixelbuffer = g_pPixelBuffer;
  index = hscroll >> 3 & 0x3F;
  unsigned short tile = p_scrollplane[index];
  unsigned char hscroll_low = hscroll & 7;
  if (hscroll_low == 0) {
    p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
  }
  else {
    p_pixelbuffer = blit_remainingpixels_ver3(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  ++index;
  index &= 0x3F;
  tile = p_scrollplane[index];
  p_pixelbuffer = blit_8pixels_ver2(p_pixelbuffer, tile, vscroll_low);
  ++index;
  index &= 0x3F;
  if (hscroll_low != 0) {
    tile = p_scrollplane[index];
    p_pixelbuffer = blit_remainingpixels_ver4(p_pixelbuffer, tile, vscroll_low, hscroll_low);
  }
  g_pPixelBuffer += 16;
}


// 00411698
void blit_sprite_noprio(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (y - p_sprite->y) * 4];

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_LEFT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          ROTATE_LEFT(pixels, 4);
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
          }
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram += p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 0041177c
void blit_sprite_hflip_noprio(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (y - p_sprite->y) * 4];
    p_vram += (p_sprite->w - 1) * p_sprite->h;

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_RIGHT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
          }
          ROTATE_RIGHT(pixels, 4);
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram -= p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 0041186d
void blit_sprite_vflip_noprio(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (p_sprite->y + p_sprite->h - y - 1) * 4];

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_LEFT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          ROTATE_LEFT(pixels, 4);
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
          }
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram += p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 00411957
void blit_sprite_hvflip_noprio(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (p_sprite->y + p_sprite->h - y - 1) * 4];
    p_vram += (p_sprite->w - 1) * p_sprite->h;

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_RIGHT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
          }
          ROTATE_RIGHT(pixels, 4);
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram -= p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 00411a50
void FUN_00411a50(Sprite* p_sprite) {
  if (p_sprite->x > -128) return;

  long y = p_sprite->y;
  long cnt = p_sprite->h;
  if (p_sprite->x < 0) {
    cnt += y;
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end > 224) {
    cnt -= y_end - 224;
  }
  if (cnt > 0) {
    unsigned char* p_spritemasks = &g_spriteMasks[y];

    do {
      ++*p_spritemasks;
      ++p_spritemasks;
    } while (--cnt != 0);
  }
}


// 00411a9e
static void FUN_00411a9e(Sprite* p_sprite) {
  long y = p_sprite->y;
  long cnt = p_sprite->h;
  if (p_sprite->y < 0) {
    cnt += y;
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end > 224) {
    y -= y_end - 224;
  }
  if (cnt > 0) {
    unsigned char* p_spritemasks = &g_spriteMasks[y];

    do {
      --*p_spritemasks;
      ++p_spritemasks;
    } while (--cnt != 0);
  }
}


// 00411add
void blit_sprite_masked(Sprite* p_sprite) {
  if (p_sprite->x <= -128) {
    FUN_00411a9e(p_sprite);
    return;
  }
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    if (g_spriteMasks[y] == 0) {
      unsigned long scanline_pixel_cnt = p_sprite->w;
      long x = p_sprite->x;
      unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (y - p_sprite->y) * 4];

      do {
        if (x >= 320) break;
        unsigned long pixels = *p_vram;
        if (x > -8) {
          pixels = BYTESWAP(pixels);
          unsigned char* p_pixelbuffer2 = p_pixelbuffer;
          unsigned char pixel_cnt;
          if (x < 0) {
            pixel_cnt = x + 8;
            unsigned char rotatebit_cnt = -x * 4;
            ROTATE_LEFT(pixels, rotatebit_cnt);
          }
          else {
            if (x > 312) {
              p_pixelbuffer2 += x;
              pixel_cnt = 320 - x;
            }
            else {
              p_pixelbuffer2 += x;
              pixel_cnt = 8;
            }
          }

          do {
            ROTATE_LEFT(pixels, 4);
            if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
              *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
            }
            ++p_pixelbuffer2;
          } while (--pixel_cnt != 0);
        }
        x += 8;
        p_vram += p_sprite->h;
      } while (--scanline_pixel_cnt != 0);
    }
    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 00411bd6
void blit_sprite_masked_hflip(Sprite* p_sprite) {
  if (p_sprite->x <= -128) {
    FUN_00411a9e(p_sprite);
    return;
  }
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    if (g_spriteMasks[y] == 0) {
      unsigned long scanline_pixel_cnt = p_sprite->w;
      long x = p_sprite->x;
      unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (y - p_sprite->y) * 4];
      p_vram += (p_sprite->w - 1) * p_sprite->h;

      do {
        if (x >= 320) break;
        unsigned long pixels = *p_vram;
        if (x > -8) {
          pixels = BYTESWAP(pixels);
          unsigned char* p_pixelbuffer2 = p_pixelbuffer;
          unsigned char pixel_cnt;
          if (x < 0) {
            pixel_cnt = x + 8;
            unsigned char rotatebit_cnt = -x * 4;
            ROTATE_RIGHT(pixels, rotatebit_cnt);
          }
          else {
            if (x > 312) {
              p_pixelbuffer2 += x;
              pixel_cnt = 320 - x;
            }
            else {
              p_pixelbuffer2 += x;
              pixel_cnt = 8;
            }
          }

          do {
            if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
              *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
            }
            ROTATE_RIGHT(pixels, 4);
            ++p_pixelbuffer2;
          } while (--pixel_cnt != 0);
        }
        x += 8;
        p_vram -= p_sprite->h;
      } while (--scanline_pixel_cnt != 0);
    }
    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 00411ce0
void blit_sprite_masked_vflip(Sprite* p_sprite) {
  if (p_sprite->x <= -128) {
    FUN_00411a9e(p_sprite);
    return;
  }
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    if (g_spriteMasks[y] == 0) {
      unsigned long scanline_pixel_cnt = p_sprite->w;
      long x = p_sprite->x;
      unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (p_sprite->y + p_sprite->h - y - 1) * 4];

      do {
        if (x >= 320) break;
        unsigned long pixels = *p_vram;
        if (x > -8) {
          pixels = BYTESWAP(pixels);
          unsigned char* p_pixelbuffer2 = p_pixelbuffer;
          unsigned char pixel_cnt;
          if (x < 0) {
            pixel_cnt = x + 8;
            unsigned char rotatebit_cnt = -x * 4;
            ROTATE_LEFT(pixels, rotatebit_cnt);
          }
          else {
            if (x > 312) {
              p_pixelbuffer2 += x;
              pixel_cnt = 320 - x;
            }
            else {
              p_pixelbuffer2 += x;
              pixel_cnt = 8;
            }
          }

          do {
            ROTATE_LEFT(pixels, 4);
            if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
              *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
            }
            ++p_pixelbuffer2;
          } while (--pixel_cnt != 0);
        }
        x += 8;
        p_vram += p_sprite->h;
      } while (--scanline_pixel_cnt != 0);
    }
    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 00411de3
void blit_sprite_masked_hvflip(Sprite* p_sprite) {
  if (p_sprite->x <= -128) {
    FUN_00411a9e(p_sprite);
    return;
  }
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    if (g_spriteMasks[y] == 0) {
      unsigned long scanline_pixel_cnt = p_sprite->w;
      long x = p_sprite->x;
      unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (p_sprite->y + p_sprite->h - y - 1) * 4];
      p_vram += (p_sprite->w - 1) * p_sprite->h;

      do {
        if (x >= 320) break;
        unsigned long pixels = *p_vram;
        if (x > -8) {
          pixels = BYTESWAP(pixels);
          unsigned char* p_pixelbuffer2 = p_pixelbuffer;
          unsigned char pixel_cnt;
          if (x < 0) {
            pixel_cnt = x + 8;
            unsigned char rotatebit_cnt = -x * 4;
            ROTATE_RIGHT(pixels, rotatebit_cnt);
          }
          else {
            if (x > 312) {
              p_pixelbuffer2 += x;
              pixel_cnt = 320 - x;
            }
            else {
              p_pixelbuffer2 += x;
              pixel_cnt = 8;
            }
          }

          do {
            if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
              *p_pixelbuffer2 = ((pixels & 0xF) + p_sprite->flags) & 0x7F;
            }
            ROTATE_RIGHT(pixels, 4);
            ++p_pixelbuffer2;
          } while (--pixel_cnt != 0);
        }
        x += 8;
        p_vram -= p_sprite->h;
      } while (--scanline_pixel_cnt != 0);
    }
    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 00411ef4
void blit_sprite(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (y - p_sprite->y) * 4];

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_LEFT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          ROTATE_LEFT(pixels, 4);
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = (pixels & 0xF) + p_sprite->flags;
          }
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram += p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 00411fd5
void blit_sprite_hflip(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (y - p_sprite->y) * 4];
    p_vram += (p_sprite->w - 1) * p_sprite->h;

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_RIGHT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = (pixels & 0xF) + p_sprite->flags;
          }
          ROTATE_RIGHT(pixels, 4);
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram -= p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 004120c3
void blit_sprite_vflip(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (p_sprite->y + p_sprite->h - y - 1) * 4];

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_LEFT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          ROTATE_LEFT(pixels, 4);
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = (pixels & 0xF) + p_sprite->flags;
          }
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram += p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}


// 004121aa
void blit_sprite_hvflip(Sprite* p_sprite) {
  if (p_sprite->y >= 224) return;

  long y = p_sprite->y;
  if (y < 0) {
    y = 0;
  }
  long y_end = p_sprite->y + p_sprite->h;
  if (y_end < 0) return;
  if (y_end > 224) {
    y_end = 224;
  }
  unsigned char* p_pixelbuffer = &g_pixelBuffer[y * 320];

  do {
    unsigned long scanline_pixel_cnt = p_sprite->w;
    long x = p_sprite->x;
    unsigned long* p_vram = (unsigned long*)&g_mdVram[p_sprite->vram_offset + (p_sprite->y + p_sprite->h - y - 1) * 4];
    p_vram += (p_sprite->w - 1) * p_sprite->h;

    do {
      if (x >= 320) break;
      unsigned long pixels = *p_vram;
      if (x > -8) {
        pixels = BYTESWAP(pixels);
        unsigned char* p_pixelbuffer2 = p_pixelbuffer;
        unsigned char pixel_cnt;
        if (x < 0) {
          pixel_cnt = x + 8;
          unsigned char rotatebit_cnt = -x * 4;
          ROTATE_RIGHT(pixels, rotatebit_cnt);
        }
        else {
          if (x > 312) {
            p_pixelbuffer2 += x;
            pixel_cnt = 320 - x;
          }
          else {
            p_pixelbuffer2 += x;
            pixel_cnt = 8;
          }
        }

        do {
          if ((pixels & 0xF) && (!(*p_pixelbuffer2 & 0x80) || (p_sprite->flags & 0x80))) {
            *p_pixelbuffer2 = (pixels & 0xF) + p_sprite->flags;
          }
          ROTATE_RIGHT(pixels, 4);
          ++p_pixelbuffer2;
        } while (--pixel_cnt != 0);
      }
      x += 8;
      p_vram -= p_sprite->h;
    } while (--scanline_pixel_cnt != 0);

    p_pixelbuffer += 320;
  } while (++y < y_end);
}
