#ifndef CFILE_H
#define CFILE_H

#include <windows.h>

class CFile {
  public:
  BOOL isFileOpen();
  CFile(const char* pFileName);
  ~CFile();
  void closeFile();
  ULONG readData(void* pBuffer, ULONG byteCnt);

  private:
  HANDLE m_hFile;
};

#endif
