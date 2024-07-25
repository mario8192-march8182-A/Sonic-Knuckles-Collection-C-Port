#include <windows.h>
#include "cfile.h"


// 0040b7d0
BOOL CFile::isFileOpen() {
  if (m_hFile == INVALID_HANDLE_VALUE) {
    return FALSE;
  }

  return TRUE;
}


// 0040ea50
CFile::CFile(const char* pFileName) {
  closeFile();
  m_hFile = CreateFile(pFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
}


// 0040ea02
CFile::~CFile() {
  closeFile();
}


// 0040ea91
void CFile::closeFile() {
  if (m_hFile != INVALID_HANDLE_VALUE) {
    CloseHandle(m_hFile);
    m_hFile = INVALID_HANDLE_VALUE;
  }
}


// 0040eac8
ULONG CFile::readData(void* pBuffer, ULONG byteCnt) {
  ULONG byteReadCnt;
  ReadFile(m_hFile, pBuffer, byteCnt, &byteReadCnt, 0);

  return byteReadCnt;
}
