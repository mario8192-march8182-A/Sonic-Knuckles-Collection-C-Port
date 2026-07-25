#ifndef CINIFILE_H
#define CINIFILE_H

#include <windows.h>

class CIniFile {
  public:
  CIniFile(LPCSTR pFileName, ULONG value);
  void setSection(LPCSTR pSectionName);
  int getInt(LPCSTR pKeyName, int defaultValue);
  void readString(LPCSTR pKeyName, LPSTR pBuffer, ULONG size);
  void readInt(LPCSTR pKeyName, int* pReturnValue, int defaultValue);
  void setString(LPCSTR pKeyName, LPCSTR pString);
  void setInt(LPCSTR pKeyName, int value);

  private:
  ULONG m_value;
  char m_fileName[256];
  char m_sectionName[256];
};

#endif
