#ifndef IMIDI_H
#define IMIDI_H

#include <windows.h>

class IMidi {
  public:
  virtual BOOL init(HWND hWnd) = 0;
  virtual BOOL loadSong(short id, UINT bgmMode) = 0;
  virtual BOOL playSong() = 0;
  virtual BOOL stopSong() = 0;
  virtual BOOL pauseSong() = 0;
  virtual BOOL resumeSong() = 0;
  virtual BOOL setTempo(UINT percentage) = 0;
};

#endif
