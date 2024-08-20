#ifndef CWINREGISTRY_H
#define CWINREGISTRY_H

#include <windows.h>

class CWinRegistry {
  public:
  CWinRegistry(const char* pKeyName);
  void openSubKey(const char* pSubKeyName);
  BOOL queryKeyBool(const char* pKeyName);
  void queryKeyBytes2(const char* pKeyName, BYTE* pBuffer, ULONG size);
  void queryKeyDword(const char* pKeyName, DWORD* pBuffer);
  void queryKeyBytes(const char* pKeyName, BYTE* pBuffer, ULONG size);
  void setKeyString(const char* pKeyName, const char* pBuffer);
  void setKeyDword(const char* pKeyName, DWORD* pBuffer);
  void setKeyBinary(const char* pKeyName, BYTE* pBuffer, ULONG size);
  ~CWinRegistry();

  private:
  ULONG m_pDisposition;
  long m_result;
  HKEY m_hKey;
  HKEY m_hSubKey;
  char m_key[256];
  char m_subKey[256];
};

#endif
