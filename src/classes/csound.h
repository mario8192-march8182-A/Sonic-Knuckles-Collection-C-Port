#ifndef CSOUND_H
#define CSOUND_H

#include <windows.h>
#include <dsound.h>

class CSound {
  public:
  CSound();
  ~CSound();
  int initSound(HWND hWnd);
  int createSoundBuffer(UCHAR formatFlag, ULONG size, int id);
  int resetSound();
  int lockSoundBuffer(ULONG size, void** ppAudioBlock1, ULONG *pAudioBlock1ByteCnt, void** ppAudioBlock2, ULONG *pAudioBlock2ByteCnt, int id);
  int unlockSoundBuffer(void* pAudioBlock1, ULONG audioBlock1ByteCnt, void* pAudioBlock2, ULONG audioBlock2ByteCnt, int id);
  int stopBuffer(int id);
  int loadSoundEffects(const char* pFileName, UCHAR formatFlag, int idModifier, ULONG cnt);
  BOOL isBufferPlaying(int id);
  int stopSoundEffects();
  int FUN_0040a697();

  private:
  HMODULE m_hDSound;
  LPDIRECTSOUND m_pDsound;
  LPDIRECTSOUNDBUFFER m_buffers[256];
  long m_unknown1032[256];
  HWND m_hWnd;
  ULONG m_unknown2060;
  UCHAR* m_unknown2064;
  HRESULT m_dsoundResult;
  char m_message[256];
};

#endif
