#include <windows.h>
#include <dsound.h>
#include "cunksoundobj.h"
#include "csound.h"

extern CSound* g_pSound2;

// 0040a5bc
int CUnkSoundObj::init(int seventeen, int buffer2Id, int m_buffer1Id, ULONG unknown16) {
  if (m_unknown0 > 0) {
    m_unknown0 = seventeen;
    return 0;
  }

  m_unknown0 = seventeen;
  m_buffer2Id = buffer2Id;
  m_buffer1Id = m_buffer1Id;
  m_unknown16 = unknown16;
  m_unknown20 = 6;
  if (m_buffer1Id != 0) {
    m_unknown4 = 0;
    g_pSound2->setBufferPosition(0, m_buffer1Id);
    return g_pSound2->playBuffer(0, m_buffer1Id);
  }

  m_unknown4 = 2;
  g_pSound2->setBufferPosition(0, m_buffer2Id);
  return g_pSound2->playBuffer(DSBPLAY_LOOPING, m_buffer2Id);
}


// 0040b830
ULONG CUnkSoundObj::decreaseUnknown0() {
  --m_unknown0;
  return m_unknown0;
}


// 0040b850
ULONG CUnkSoundObj::decreaseUnknown16() {
  --m_unknown16;
  return m_unknown16;
}


// 0040b880
ULONG CUnkSoundObj::decreaseUnknown20() {
  --m_unknown20;
  return m_unknown20;
}
