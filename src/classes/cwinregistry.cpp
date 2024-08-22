#include "cwinregistry.h"
#include <windows.h>
#include <mbstring.h>


// 00405fd0
CWinRegistry::CWinRegistry(const char* pKeyName) {
  m_hKey = m_hSubKey = 0;
  _mbscpy((UCHAR*)m_key, (const UCHAR*)pKeyName);
  m_subKey[0] = 0;

  char buffer[256];
  _mbscpy((UCHAR*)buffer, (const UCHAR*)"Software\\");
  strcat(buffer, m_key);
  m_result = RegCreateKeyEx(HKEY_CURRENT_USER, buffer, 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &m_hKey, &m_pDisposition);
}


// 0040609f
void CWinRegistry::openSubKey(const char* pSubKeyName) {
  _mbscpy((UCHAR*)m_subKey, (const UCHAR*)pSubKeyName);
  m_result = RegCreateKeyEx(m_hKey, m_subKey, 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &m_hSubKey, &m_pDisposition);
}


// 00406103
BOOL CWinRegistry::queryKeyBool(const char* pKeyName) {
  ULONG size = 4;
  BOOL buffer = TRUE;
  m_result = RegQueryValueEx(m_hSubKey, pKeyName, 0, 0, (BYTE*)&buffer, &size);

  return buffer;
}


// 0040614f
void CWinRegistry::queryKeyBytes2(const char* pKeyName, BYTE* pBuffer, ULONG size) {
  --size;
  if (size > (DWORD)-1) {
    pBuffer[0] = 0;
    m_result = RegQueryValueEx(m_hSubKey, pKeyName, 0, 0, pBuffer, &size);
  }
}


// 0040619e
void CWinRegistry::queryKeyDword(const char* pKeyName, DWORD* pBuffer) {
  ULONG size = 4;
  m_result = RegQueryValueEx(m_hSubKey, pKeyName, 0, 0, (BYTE*)pBuffer, &size);
}


// 004061e0
void CWinRegistry::queryKeyBytes(const char* pKeyName, BYTE* pBuffer, ULONG size) {
  m_result = RegQueryValueEx(m_hSubKey, pKeyName, 0, 0, pBuffer, &size);
}


// 0040621b
void CWinRegistry::setKeyString(const char* pKeyName, const char* pBuffer) {
  ULONG size = strlen(pBuffer);
  m_result = RegSetValueEx(m_hSubKey, pKeyName, 0, REG_SZ, (BYTE*)pBuffer, size);
}


// 00406260
void CWinRegistry::setKeyDword(const char* pKeyName, DWORD* pBuffer) {
  m_result = RegSetValueEx(m_hSubKey, pKeyName, 0, REG_DWORD, (BYTE*)pBuffer, sizeof(DWORD));
}


// 00406299
void CWinRegistry::setKeyBinary(const char* pKeyName, BYTE* pBuffer, ULONG size) {
  m_result = RegSetValueEx(m_hSubKey, pKeyName, 0, REG_BINARY, pBuffer, size);
}


// 004062d4
CWinRegistry::~CWinRegistry() {
  if (m_hSubKey != 0) {
    m_result = RegCloseKey(m_hSubKey);
  }
  if (m_hKey != 0) {
    m_result = RegCloseKey(m_hKey);
  }
}
