#include <windows.h>
#include <dsound.h>
#include <mbstring.h>
#include "csound.h"
#include "cfile.h"

extern void initMidiInterface(HWND hWnd);
extern CFile* readInt(CFile* pFile, ULONG* pBuffer);

extern HMODULE g_hMusicDll;
extern HRESULT(*g_pDSoundCreate)(GUID*, LPDIRECTSOUND*, LPUNKNOWN*);
extern CSound* g_pSound2;


// 004097bc
CSound::CSound() {
  m_pDsound = 0;
  for (int i = 0; i < 256; ++i) {
    m_buffers[i] = 0;
  }
  m_dsoundResult = 0;
  m_message[0] = 0;
  m_hDSound = LoadLibrary("DSOUND.DLL");
  if (m_hDSound != 0) {
    g_pDSoundCreate = (HRESULT(*)(GUID*, LPDIRECTSOUND*, LPUNKNOWN*))GetProcAddress(m_hDSound, "DirectSoundCreate");
  }
  m_unknown2064 = new UCHAR[960];
  memset(m_unknown2064, 0, 960);
  g_pSound2 = this;
  m_unknown2060 = 1;
}


// 0040989b
CSound::~CSound() {
  delete[] m_unknown2064;
  resetSound();
  if (m_hDSound != 0) {
    FreeLibrary(m_hDSound);
  }
  if (g_hMusicDll != 0) {
    FreeLibrary(g_hMusicDll);
  }
}


// 00409908
int CSound::initSound(HWND hWnd) {
  m_hWnd = hWnd;
  initMidiInterface(m_hWnd);

  if (m_hDSound == 0 || g_pDSoundCreate == 0) {
    _mbscpy((UCHAR*)m_message, (const UCHAR*)"No Direct Sound");
    return 1;
  }
  m_dsoundResult = (*g_pDSoundCreate)(0, &m_pDsound, 0);
  if (m_dsoundResult != DS_OK) {
    _mbscpy((UCHAR*)m_message, (const UCHAR*)"DirectSoundCreate");
    return 1;
  }
  m_dsoundResult = m_pDsound->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
  if (m_dsoundResult != DS_OK) {
    _mbscpy((UCHAR*)m_message, (const UCHAR*)"SetCooperativeLevel DSSCL_NORMAL");
    return 1;
  }
  m_unknown2060 = 0;

  return 0;
}


// 00409a27
int CSound::createSoundBuffer(UCHAR formatFlag, ULONG size, int id) {
  WAVEFORMATEX waveFormat;
  memset(&waveFormat, 0, sizeof(waveFormat));
  waveFormat.wFormatTag = WAVE_FORMAT_PCM;
  if (formatFlag & 1) {
    waveFormat.nChannels = 2;
  }
  else {
    waveFormat.nChannels = 1;
  }
  if (formatFlag & 2) {
    waveFormat.wBitsPerSample = 16;
  }
  else {
    waveFormat.wBitsPerSample = 8;
  }

  switch (formatFlag & 12) {
    case 0:
      waveFormat.nSamplesPerSec = 11025;
      break;
    case 4:
      waveFormat.nSamplesPerSec = 22050;
      break;
    case 8:
      waveFormat.nSamplesPerSec = 32000;
      break;
    case 12:
      waveFormat.nSamplesPerSec = 44100;
      break;
  }

  waveFormat.nBlockAlign = waveFormat.nChannels * (waveFormat.wBitsPerSample / 8);
  waveFormat.nAvgBytesPerSec = waveFormat.nBlockAlign * waveFormat.nSamplesPerSec;

  DSBUFFERDESC dsBufferDesc;
  memset(&dsBufferDesc, 0, sizeof(dsBufferDesc));
  dsBufferDesc.dwSize = sizeof(dsBufferDesc);
  dsBufferDesc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
  dsBufferDesc.dwBufferBytes = size;
  dsBufferDesc.lpwfxFormat = &waveFormat;

  if (m_buffers[id] != 0) {
    m_buffers[id]->Release();
    m_buffers[id] = 0;
  }
  m_dsoundResult = m_pDsound->CreateSoundBuffer(&dsBufferDesc, &m_buffers[id], 0);
  if (m_dsoundResult != DS_OK) {
    _mbscpy((UCHAR*)m_message, (const UCHAR*)"CreateSoundBuffer");
    return 1;
  }

  return 0;
}


// 00409c9f
int CSound::resetSound() {
  for (int i = 0; i < 256; ++i) {
    if (m_buffers[i] != 0) {
      m_buffers[i]->Release();
      m_buffers[i] = 0;
    }
    if (m_pDsound != 0) {
      m_pDsound->Release();
      m_pDsound = 0;
    }
  }

  return 0;
}


// 00409d3a
int CSound::lockSoundBuffer(ULONG size, void** ppAudioBlock1, ULONG *pAudioBlock1ByteCnt, void** ppAudioBlock2, ULONG *pAudioBlock2ByteCnt, int id) {
  m_dsoundResult = m_buffers[id]->Lock(0, size, ppAudioBlock1, pAudioBlock1ByteCnt, ppAudioBlock2, pAudioBlock2ByteCnt, 0);
  if (m_dsoundResult == DSERR_BUFFERLOST) {
    m_dsoundResult = m_buffers[id]->Restore();
    if (m_dsoundResult != DS_OK) {
      _mbscpy((UCHAR*)m_message, (const UCHAR*)"CreateSoundBuffer");
      return 1;
    }
    m_dsoundResult = m_buffers[id]->Lock(0, size, ppAudioBlock1, pAudioBlock1ByteCnt, ppAudioBlock2, pAudioBlock2ByteCnt, 0);
  }
  if (m_dsoundResult != DS_OK) {
    _mbscpy((UCHAR*)m_message, (const UCHAR*)"DIRECTSOUNDBUFFER Lock");
    return 1;
  }

  return 0;
}


// 00409e43
int CSound::unlockSoundBuffer(void* pAudioBlock1, ULONG audioBlock1ByteCnt, void* pAudioBlock2, ULONG audioBlock2ByteCnt, int id) {
  m_dsoundResult = m_buffers[id]->Unlock(pAudioBlock1, audioBlock1ByteCnt, pAudioBlock2, audioBlock2ByteCnt);
  if (m_dsoundResult != DS_OK) {
    _mbscpy((UCHAR*)m_message, (const UCHAR*)"DIRECTSOUNDBUFFER Unlock");
    return 1;
  }

  return 0;
}


// 00409f33
int CSound::stopBuffer(int id) {
  m_dsoundResult = m_buffers[id]->Stop();
  if (m_dsoundResult != DS_OK) {
    _mbscpy((UCHAR*)m_message, (const UCHAR*)"DIRECTSOUNDBUFFER Stop");
    return 1;
  }

  return 0;
}


// 00409f9f
int CSound::playBuffer(int id) {
  LPDIRECTSOUNDBUFFER buffer = m_buffers[id];
  ULONG status = 0;
  long unknown = m_sampleSizes[id];
  buffer->GetStatus(&status);

  if (status & DSBSTATUS_PLAYING) {
    ULONG playPos, writePos;
    buffer->GetCurrentPosition(&playPos,&writePos);
    if (playPos > unknown) {
      buffer->Stop();
      buffer->SetCurrentPosition(0);
      buffer->Play(0, 0, 0);
    }
    else {
      buffer->SetCurrentPosition(0);
    }
  }
  else {
    buffer->SetCurrentPosition(0);
    buffer->Play(0, 0, 0);
  }

  return 0;
}


// 0040a25f
int CSound::loadSoundEffects(const char* pFileName, UCHAR formatFlag, int idModifier, ULONG cnt) {
  CFile file(pFileName);
  if (file.isFileOpen() == FALSE) {
    return 1;
  }

  ULONG sizeCnt;
  readInt(&file, &sizeCnt);
  ULONG* pSizes = new ULONG[sizeCnt];
  if (file.readData(pSizes, sizeCnt * 4) != sizeCnt * 4) {
    /* possible memory leak as pSizes is not deleted */
    return 1;
  }

  int ret = 1;
  for (int i = 0; i < sizeCnt; ++i) {
    ULONG bufferSize;
    if (i < cnt && i != 59) {
      bufferSize = pSizes[i] + 11050;
      m_sampleSizes[i + idModifier] = pSizes[i] + 5525;
    }
    else {
      bufferSize = pSizes[i];
      m_sampleSizes[i + idModifier] = -1;
    }

    if (createSoundBuffer(formatFlag, bufferSize, i + idModifier) != 0) goto end;

    BYTE* pAudioBlock1;
    ULONG audioBlock1ByteCnt;
    BYTE* pAudioBlock2;
    ULONG audioBlock2ByteCnt;
    lockSoundBuffer(bufferSize, (void**)&pAudioBlock1, &audioBlock1ByteCnt, (void**)&pAudioBlock2, &audioBlock2ByteCnt, i + idModifier);

    if (file.readData(pAudioBlock1, pSizes[i]) != pSizes[i]) {
      unlockSoundBuffer(pAudioBlock1, audioBlock1ByteCnt, pAudioBlock2, audioBlock2ByteCnt, i + idModifier);
      goto end;
    }

    if (i < cnt && i != 59) {
      memset(&pAudioBlock1[pSizes[i]], 128, 11050);
    }

    unlockSoundBuffer(pAudioBlock1, audioBlock1ByteCnt, pAudioBlock2, audioBlock2ByteCnt, i + idModifier);
  }
  ret = 0;

end:
  delete[] pSizes;

  return ret;
}


// 0040a4f8
BOOL CSound::isBufferPlaying(int id) {
  if (m_buffers[id] == 0) {
    return FALSE;
  }

  ULONG status;
  m_buffers[id]->GetStatus(&status);
  if (status & DSBSTATUS_PLAYING) {
    return TRUE;
  }

  return FALSE;
}


// 0040a563
int CSound::stopSoundEffects() {
  for (int i = 0; i < 256; ++i) {
    if (isBufferPlaying(i)) {
      stopBuffer(i);
    }
  }
  return 0;
}


// 0040a697
int CSound::FUN_0040a697() {
  memset(m_unknown2064, 0, sizeof(m_unknown2064));

  return 0;
}


// 0040b8e0
ULONG CSound::getUnknown2060() {
  return m_unknown2060;
}


// 0040b8b0
LPDIRECTSOUNDBUFFER CSound::getSoundBuffer(int id) {
  return m_buffers[id];
}
