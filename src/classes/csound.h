#ifndef CSOUND_H
#define CSOUND_H

#include <windows.h>
#include <dsound.h>
#include "cunksoundobj.h"

class CSound {
  public:
  CSound();
  ~CSound();
  int initSound(HWND hWnd);
  int createSoundBuffer(UCHAR formatFlag, ULONG size, int id);
  int releaseBuffer(int id);
  int resetSound();
  int lockSoundBuffer(ULONG size, void** ppAudioBlock1, ULONG *pAudioBlock1ByteCnt, void** ppAudioBlock2, ULONG *pAudioBlock2ByteCnt, int id);
  int unlockSoundBuffer(void* pAudioBlock1, ULONG audioBlock1ByteCnt, void* pAudioBlock2, ULONG audioBlock2ByteCnt, int id);
  int playBuffer(UINT flags, int id);
  int stopBuffer(int id);
  int playBuffer(int id);
  int readBufferPosition(ULONG* pPlayPos, ULONG* pWritePos, int id);
  int setBufferPosition(ULONG position, int id);
  int readMessage(char* pBuffer);
  void showMessage();
  int loadSoundEffects(const char* pFileName, UCHAR formatFlag, int idModifier, ULONG cnt);
  BOOL isBufferPlaying(int id);
  int stopSoundEffects();
  int FUN_0040a697();
  void FUN_0040a6c8(int unknown2064_id, int seventeen, int buffer2Id, int buffer1Id, int unknown16);
  int playSoundEffects();
  ULONG getUnknown2060();
  LPDIRECTSOUNDBUFFER getSoundBuffer(int id);

  private:
  HMODULE m_hDSound;
  LPDIRECTSOUND m_pDsound;
  LPDIRECTSOUNDBUFFER m_buffers[256];
  long m_sampleSizes[256];
  HWND m_hWnd;
  ULONG m_unknown2060;
  CUnkSoundObj* m_unknown2064;
  HRESULT m_dsoundResult;
  char m_message[256];
};

#endif
