#ifndef UNKSOUNDOBJ_H
#define UNKSOUNDOBJ_H

#include <windows.h>

class CUnkSoundObj {
  public:
  int init(int seventeen, int buffer2Id, int m_buffer1Id, ULONG unknown16);
  ULONG decreaseUnknown0();
  ULONG decreaseUnknown16();
  ULONG decreaseUnknown20();
  ULONG m_unknown0;
  ULONG m_unknown4;
  int m_buffer1Id;
  int m_buffer2Id;

  private:
  ULONG m_unknown16;
  ULONG m_unknown20;
};

#endif
