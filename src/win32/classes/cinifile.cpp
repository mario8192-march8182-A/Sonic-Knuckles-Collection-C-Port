#include <windows.h>
#include <mbstring.h>
#include "cinifile.h"


// 00403f0f
CIniFile::CIniFile(LPCSTR pFileName, ULONG value) {
  m_value = value;
  _mbscpy((UCHAR*)m_fileName, (const UCHAR*)pFileName);
  _mbscpy((UCHAR*)m_sectionName, (const UCHAR*)"Param");
}


// 00403f5b
void CIniFile::setSection(LPCSTR pSectionName) {
  _mbscpy((UCHAR*)m_sectionName, (const UCHAR*)pSectionName);
}


// 00403f88
int CIniFile::getInt(LPCSTR pKeyName, int defaultValue) {
  return GetPrivateProfileInt(m_sectionName, pKeyName, defaultValue, (LPCSTR)m_fileName);
}


// 00403fbe
void CIniFile::readString(LPCSTR pKeyName, LPSTR pBuffer, ULONG size) {
  GetPrivateProfileString(m_sectionName, pKeyName, "", pBuffer, size, m_fileName);
}


// 00403ffd
void CIniFile::readInt(LPCSTR pKeyName, int* pReturnValue, int defaultValue) {
  *pReturnValue = GetPrivateProfileInt(m_sectionName, pKeyName, defaultValue, m_fileName);
}


// 00404038
void CIniFile::setString(LPCSTR pKeyName, LPCSTR pString) {
  WritePrivateProfileString(m_sectionName, pKeyName, pString, m_fileName);
}


// 0040406e
void CIniFile::setInt(LPCSTR pKeyName, int value) {
  char valueString[16];
  wsprintf(valueString, "%d", value);
  WritePrivateProfileString(m_sectionName, pKeyName, valueString, m_fileName);
}
