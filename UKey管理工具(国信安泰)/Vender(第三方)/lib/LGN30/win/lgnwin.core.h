/*! \file lgnwin.core.h 
 *  \brief WINϵͳ�Ļ������ܷ�װ��
 *
 *  ��lgnbase.h���������̲���ֱ�Ӱ������ļ�
 *
 *  ��Ҫʵ�����¹��ܣ�
 *  
 *  <ul>
 *  	<li> һЩȫ�ֺ���������������ATL�ļ�����Ч��
 *		<li> ���û�а���atlstr.h����ʵ��ChTraitsBase��ChTraitsOS��̬ģ����
 *  	<li> ģ��·��������ģ���� CModulePathT
 *  	<li> ����DLLģ���ģ���� CLoadModuleT
 *  	<li> �ļ������ľ�̬ģ���� FileTraitsTrace,ֻ����lgntrace.h
 *  </ul>
 *
 *  \author ljc
 *  \version 3.0.0
 *  \date    2010-2012
 *  \bug
 *  \warning
 */

#ifndef __LGNWIN_CORE_H__
#define __LGNWIN_CORE_H__

#include <shlwapi.h>

//#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
// Win32 libraries

#ifndef _ATL_NO_DEFAULT_LIBS
#if (_MSC_VER >= 1000)
#pragma comment(lib, "shlwapi.lib")
#endif
#endif  // !_ATL_NO_DEFAULT_LIBS


namespace LGN
{
////////////////////////////////////////////////////////////////////////////////////////////////////
// global function

	//! �����̰���atlconv.h��ͬ<B>ATL::_AtlGetConversionACP</B> ����ο�MSDN�����򷵻�CP_ACP
	inline UINT WINAPI _LgnGetConversionACP() throw()
	{
#ifdef __ATLCONV_H__
		return ATL::_AtlGetConversionACP();
#else
		return( CP_ACP );
#endif
	}

#ifdef __ATLCORE_H__
	inline BOOL LgnIsValidAddress(const void* p, size_t nBytes, BOOL bReadWrite = TRUE)
	{
		return ATL::AtlIsValidAddress(p, nBytes, bReadWrite);
	}

	inline BOOL LgnIsValidString(LPCSTR psz, size_t nMaxLength = UINT_MAX)
	{
		return ATL::AtlIsValidString(psz, nMaxLength);
	}

	inline BOOL LgnIsValidString(LPCWSTR psz, size_t nMaxLength = UINT_MAX)
	{
		return ATL::AtlIsValidString(psz, nMaxLength);
	}

	inline HINSTANCE LgnFindStringResourceInstance(UINT nID, WORD wLanguage = 0) throw()
	{
		return ATL::AtlFindStringResourceInstance(nID, wLanguage);
	}
#else
	//! �����̰���atlcore.h��ͬ<B>ATL::AtlIsValidAddress</B> ����ο�MSDN�����򷵻�TRUE
	inline BOOL LgnIsValidAddress(const void* p, size_t nBytes, BOOL bReadWrite = TRUE)
	{
		return TRUE;
	}

	//! �����̰���atlcore.h��ͬ<B>ATL::AtlIsValidString</B> ����ο�MSDN�����򷵻�TRUE
	inline BOOL LgnIsValidString(LPCSTR psz, size_t nMaxLength = -1)
	{
		return TRUE;
	}

	//! �����̰���atlcore.h��ͬ<B>ATL::AtlIsValidString</B> ����ο�MSDN�����򷵻�TRUE
	inline BOOL LgnIsValidString(LPCWSTR psz, size_t nMaxLength = -1)
	{
		return TRUE;
	}

	//! �����̰���atlcore.h��ͬ<B>ATL::AtlFindStringResourceInstance</B> ����ο�MSDN�����򷵻�NULL
	inline HINSTANCE LgnFindStringResourceInstance(UINT nID, WORD wLanguage = 0) throw()
	{
		return( NULL );
	}
#endif
	

////////////////////////////////////////////////////////////////////////////////////////////////////
// class ChTraitsBase, ChTraitsOS
#ifdef __ATLSTR_H__
#define LGN_CHTRAISTSBASE_NS ATL
#else
#define LGN_CHTRAISTSBASE_NS LGN
	//! ��Դ atlsimpstr.h��ͬ<B>ATL::ChTraitsBase</B>������ο�MSDN
	template< typename BaseType = CHAR >
	class ChTraitsBase
	{
	public:
		typedef CHAR XCHAR;
		typedef LPSTR PXSTR;
		typedef LPCSTR PCXSTR;
		typedef WCHAR YCHAR;
		typedef LPWSTR PYSTR;
		typedef LPCWSTR PCYSTR;
	};

	//! ��Դ atlsimpstr.h��ͬ<B>ATL::ChTraitsBase</B>������ο�MSDN
	template<>
	class ChTraitsBase< WCHAR >
	{
	public:
		typedef WCHAR XCHAR;
		typedef LPWSTR PXSTR;
		typedef LPCWSTR PCXSTR;
		typedef CHAR YCHAR;
		typedef LPSTR PYSTR;
		typedef LPCSTR PCYSTR;
	};

	//! ��Դ atlstr.h��ͬ<B>ATL::ChTraitsOS</B>������ο�MSDN
	template< typename _CharType = CHAR >
	class ChTraitsOS : public ChTraitsBase< _CharType >
	{
	public:
		static int tclen(LPCSTR p) throw()
		{
			LGNASSERT(p != NULL);
			LPCSTR pnext = CharNext(p);
			return ((pnext-p)>1) ? 2 : 1;
		}
		static LPCSTR strchr(LPCSTR p, CHAR ch) throw()
		{
			LGNASSERT(p != NULL);
			//strchr for '\0' should succeed
			do
			{
				if (*p == ch)
				{
					return p;
				}
				p = CharNext(p);
			} while( *p != 0 );

			return NULL;
		}
		static LPCSTR strchr_db(LPCSTR p, CHAR ch1, CHAR ch2) throw()
		{
			LGNASSERT(p != NULL);
			while (*p != 0)
			{
				if (*p == ch1 && *(p+1) == ch2)
				{
					return p;
				}
				p = CharNext(p);
			}
			return NULL;
		}
		static LPCSTR strrchr(LPCSTR p, CHAR ch) throw()
		{
			LGNASSERT(p != NULL);
			LPCSTR pch = NULL;
			while (*p != 0)
			{
				if (*p == ch)
					pch = p;
				p = CharNext(p);
			}
			return const_cast< LPSTR >( pch );
		}
		static LPSTR _strrev(LPSTR psz) throw()
		{
			// Optimize NULL, zero-length, and single-CHAR case.
			if ((psz == NULL) || (psz[0] == '\0') || (psz[1] == '\0'))
				return psz;

			LPSTR p = psz;

			while (p[1] != 0) 
			{
				LPSTR pNext = CharNext(p);
				if(pNext > p + 1)
				{
					CHAR p1 = *p;
					*p = *(p + 1);
					*(p + 1) = p1;
				}
				p = pNext;
			}

			LPSTR q = psz;

			while (q < p)
			{
				CHAR t = *q;
				*q = *p;
				*p = t;
				q++;
				p--;
			}
			return psz;
		}
		static LPCSTR strstr(LPCSTR pStr, LPCSTR pCharSet) throw()
		{
			LGNASSERT(pStr != NULL);
			int nLen = ::lstrlenA(pCharSet);
			if (nLen == 0)
				return pStr;

			LPCSTR pMatch;
			LPCSTR pStart = pStr;
			while ((pMatch = strchr(pStart, *pCharSet)) != NULL)
			{
				if (LGN::API::memcmp(pMatch, pCharSet, nLen*sizeof(CHAR)) == 0)
					return pMatch;
				pStart = CharNextA(pMatch);
			}

			return NULL;
		}
		static int strspn(LPCSTR pStr, LPCSTR pCharSet) throw()
		{
			LGNASSERT(pStr != NULL);
			int nRet = 0;
			LPSTR p = const_cast<LPSTR>(pStr);
			while (*p != 0)
			{
				LPSTR pNext = CharNext(p);
				if(pNext > p + 1)
				{
					if(strchr_db(pCharSet, *p, *(p+1)) == NULL)
						break;
					nRet += 2;
				}
				else
				{
					if(strchr(pCharSet, *p) == NULL)
						break;
					nRet++;
				}
				p = pNext;
			}
			return nRet;
		}
		static int strcspn(LPCSTR pStr, LPCSTR pCharSet) throw()
		{
			LGNASSERT(pStr != NULL);
			int nRet = 0;
			LPSTR p = const_cast<LPSTR>(pStr);
			while (*p != 0)
			{
				LPSTR pNext = CharNext(p);
				if(pNext > p + 1)
				{
					if(strchr_db(pCharSet, *p, *(p+1)) != NULL)
						break;
					nRet += 2;
				}
				else
				{
					if(strchr(pCharSet, *p) != NULL)
						break;
					nRet++;
				}
				p = pNext;
			}
			return nRet;
		}
		static LPCSTR strpbrk(LPCSTR p, LPCSTR lpszCharSet) throw()
		{
			LGNASSERT(p != NULL);
			while (*p != 0)
			{
				if (strchr(lpszCharSet, *p) != NULL)
				{
					return p;
				}
				p = CharNext(p);
			}
			return NULL;
		}

		static LPSTR CharNext(LPCSTR p) throw()
		{
			LGNASSERT(p != NULL);
			if (*p == '\0')  // ::CharNextA won't increment if we're at a \0 already
				return const_cast<LPSTR>(p+1);
			else
				return ::CharNextA(p);
		}

		static int IsDigit(CHAR ch) throw()
		{
			WORD type;
			::GetStringTypeExA(GetThreadLocale(), CT_CTYPE1, &ch, 1, &type);
			return (type & C1_DIGIT) == C1_DIGIT;
		}

		static int IsSpace(CHAR ch) throw()
		{
			WORD type;
			::GetStringTypeExA(GetThreadLocale(), CT_CTYPE1, &ch, 1, &type);
			return (type & C1_SPACE) == C1_SPACE;
		}

		static int StringCompare(LPCSTR pstrOne, LPCSTR pstrOther) throw()
		{
			return ::lstrcmpA((LPCSTR) pstrOne, (LPCSTR) pstrOther);
		}

		static int StringCompareIgnore(LPCSTR pstrOne, LPCSTR pstrOther) throw()
		{
			return ::lstrcmpiA((LPCSTR) pstrOne, (LPCSTR) pstrOther);
		}

		static int StringCollate(LPCSTR pstrOne, LPCSTR pstrOther) throw()
		{
			int nRet = ::CompareStringA(GetThreadLocale(), 0, (LPCSTR)pstrOne, -1, (LPCSTR)pstrOther, -1);
			LGNASSERT(nRet != 0);
			return nRet-2;  // Convert to strcmp convention.  This really is documented.
		}

		static int StringCollateIgnore(LPCSTR pstrOne, LPCSTR pstrOther) throw()
		{
			int nRet = ::CompareStringA(GetThreadLocale(), NORM_IGNORECASE, (LPCSTR)pstrOne, -1, (LPCSTR)pstrOther, -1);
			LGNASSERT(nRet != 0);
			return nRet-2;  // Convert to strcmp convention.  This really is documented.
		}

		static LPCSTR StringFindString(LPCSTR pstrBlock, LPCSTR pstrMatch) throw()
		{
			return strstr(pstrBlock, pstrMatch);
		}

		static LPSTR StringFindString(LPSTR pszBlock, LPCSTR pszMatch) throw()
		{
			return( const_cast< LPSTR >( StringFindString( const_cast< LPCSTR >( pszBlock ), pszMatch ) ) );
		}

		static LPCSTR StringFindChar(LPCSTR pszBlock, CHAR chMatch) throw()
		{
			return strchr(pszBlock, chMatch);
		}

		static LPCSTR StringFindCharRev(LPCSTR psz, CHAR ch) throw()
		{
			return strrchr(psz, ch);
		}

		static LPCSTR StringScanSet(LPCSTR pszBlock, LPCSTR pszMatch) throw()
		{
			return strpbrk(pszBlock, pszMatch);
		}

		static int StringSpanIncluding(LPCSTR pstrBlock, LPCSTR pstrSet) throw()
		{
			return strspn(pstrBlock, pstrSet);
		}

		static int StringSpanExcluding(LPCSTR pstrBlock, LPCSTR pstrSet) throw()
		{
			return strcspn(pstrBlock, pstrSet);
		}

		static LPSTR StringUppercase(LPSTR psz) throw()
		{
			return ::CharUpperA( psz );
		}

		static LPSTR StringUppercase(LPSTR psz, size_t size) throw()
		{
			DWORD dwSize = static_cast<DWORD>(size);
			::CharUpperBuffA(psz, dwSize);
			return psz;
		}

		static LPSTR StringLowercase(LPSTR psz) throw()
		{
			return ::CharLowerA( psz );
		}

		static LPSTR StringLowercase(LPSTR psz, size_t size) throw()
		{
			::CharLowerBuffA(psz, size);
			return psz;
		}

		static LPSTR StringReverse(LPSTR psz) throw()
		{
			return _strrev( psz );
		}

		static int GetFormattedLength(LPCSTR pszFormat, va_list args) throw()
		{
			CHAR szBuffer[1028];

			// wvsprintf always truncates the output to 1024 character plus
			// the '\0'.
			int nLength = ::wvsprintfA(szBuffer, pszFormat, args);
			LGNASSERT(nLength >= 0);
			LGNASSERT(nLength <= 1024);

			return nLength;
		}

		static int Format(LPSTR pszBuffer, LPCSTR pszFormat, va_list args) throw()
		{
			return ::wvsprintfA(pszBuffer, pszFormat, args);
		}

		static int Format(LPSTR pszBuffer, size_t nLength, LPCSTR pszFormat, va_list args) throw()
		{
			nLength;
			return ::wvsprintfA(pszBuffer, pszFormat, args);
		}

		static int GetBaseTypeLength(LPCSTR pszSrc) throw()
		{
			// Returns required buffer length in XCHARs
			return ::lstrlenA(pszSrc);
		}

		static int GetBaseTypeLength(LPCSTR pszSrc, int nLength) throw()
		{
			(void)pszSrc;
			// Returns required buffer length in XCHARs
			return nLength;
		}

		static int GetBaseTypeLength(LPCWSTR pszSrc) throw()
		{
			// Returns required buffer length in XCHARs
			return ::WideCharToMultiByte(_LgnGetConversionACP(), 0, pszSrc, -1, NULL, 0, NULL, NULL)-1;
		}

		static int GetBaseTypeLength(LPCWSTR pszSrc, int nLength) throw()
		{
			// Returns required buffer length in XCHARs
			return ::WideCharToMultiByte(_LgnGetConversionACP(), 0, pszSrc, nLength, NULL, 0, NULL, NULL);
		}

		static void ConvertToBaseType(LPSTR pszDest, int nDestLength, LPCSTR pszSrc, int nSrcLength = -1) throw()
		{
			(void)nSrcLength;
			// nLen is in chars
			LGN::API::memcpy(pszDest, pszSrc, nDestLength*sizeof(CHAR));
		}

		static void ConvertToBaseType(LPSTR pszDest, int nDestLength, LPCWSTR pszSrc, int nSrcLength = -1) throw()
		{
			// nLen is in XCHARs
			::WideCharToMultiByte(_LgnGetConversionACP(), 0, pszSrc, nSrcLength, pszDest, nDestLength, NULL, NULL);
		}

		static void ConvertToOem(LPSTR pstrString) throw()
		{
			::AnsiToOem(pstrString, pstrString);
		}

		static void ConvertToAnsi(LPSTR pstrString) throw()
		{
			::OemToAnsi(pstrString, pstrString);
		}

		static void FloodCharacters(CHAR ch, int nLength, LPSTR pstr) throw()
		{
			// nLength is in XCHARs
			LGN::API::memset(pstr, ch, nLength);
		}

		static BSTR AllocSysString(LPCSTR pchData, int nDataLength) throw()
		{
			int nLen = ::MultiByteToWideChar(_LgnGetConversionACP(), 0, pchData, nDataLength,NULL, NULL);
			BSTR bstr = ::SysAllocStringLen(NULL, nLen);
			if (bstr != NULL)
			{
				::MultiByteToWideChar(_LgnGetConversionACP(), 0, pchData, nDataLength, bstr, nLen);
			}

			return bstr;
		}

		static BOOL ReAllocSysString(LPCSTR pchData, BSTR* pbstr, int nDataLength) throw()
		{
			int nLen = ::MultiByteToWideChar(_LgnGetConversionACP(), 0, pchData, nDataLength, NULL, NULL);
			BOOL bSuccess =::SysReAllocStringLen(pbstr, NULL, nLen);
			if (bSuccess)
			{
				::MultiByteToWideChar(_LgnGetConversionACP(), 0, pchData, nDataLength, *pbstr, nLen);
			}

			return bSuccess;
		}

		static DWORD FormatMessage(DWORD dwFlags, LPCVOID lpSource,
			DWORD dwMessageID, DWORD dwLanguageID, LPSTR pstrBuffer,
			DWORD nSize, va_list* pArguments) throw()
		{
			return ::FormatMessageA(dwFlags, lpSource, dwMessageID, dwLanguageID, pstrBuffer, nSize, pArguments);
		}

		static int SafeStringLen(LPCSTR psz) throw()
		{
			// returns length in bytes
			return (psz != NULL) ? lstrlenA(psz) : 0;
		}

		static int SafeStringLen(LPCWSTR psz) throw()
		{
			// returns length in wchar_ts
			return (psz != NULL) ? lstrlenW(psz) : 0;
		}

		static int GetCharLen(LPCWSTR) throw()
		{
			// returns CHAR length
			return 1;
		}
		static int GetCharLen(LPCSTR psz) throw()
		{
			LPCSTR p = ::CharNextA(psz);
			return (p - psz);
		}

		static DWORD GetEnvironmentVariable(LPCSTR pstrVar, LPSTR pstrBuffer, DWORD dwSize) throw()
		{
			return ::GetEnvironmentVariableA(pstrVar, pstrBuffer, dwSize);
		}
	};

	// specialization for WCHAR
	//! ��Դ atlstr.h��ͬ<B>ATL::ChTraitsOS</B>������ο�MSDN
	template<>
	class ChTraitsOS< WCHAR > : public ChTraitsBase< WCHAR >
	{
	protected:
//#if defined(_UNICODE) && !defined(_CSTRING_ALWAYS_THUNK)
		static int CompareStringW(LCID lcid, DWORD dwFlags, LPCWSTR pszString1, int nLength1, LPCWSTR pszString2, int nLength2)
		{
			return ::CompareStringW(lcid, dwFlags, pszString1, nLength1,  pszString2, nLength2);
		}
		static BOOL GetStringTypeExW(LCID lcid, DWORD dwInfoType, LPCWSTR pszSrc, int nLength, LPWORD pwCharType)
		{
			return ::GetStringTypeExW(lcid, dwInfoType, pszSrc, nLength, pwCharType);
		}
		static int lstrcmpiW(LPCWSTR psz1, LPCWSTR psz2)
		{
			return ::lstrcmpiW(psz1, psz2);
		}
		static LPWSTR CharLowerW(LPWSTR psz)
		{
			return ::CharLowerW(psz);
		}
		static LPWSTR CharUpperW(LPWSTR psz)
		{
			return ::CharUpperW(psz);
		}
		static DWORD _GetEnvironmentVariableW(LPCWSTR pszName, LPWSTR pszBuffer, DWORD nSize)
		{
			return ::GetEnvironmentVariableW(pszName, pszBuffer, nSize);
		}
//#endif  // !_UNICODE

	public:
		static int tclen(LPCWSTR) throw()
		{
			return 1;
		}
		static LPCWSTR strchr(LPCWSTR p, WCHAR ch) throw()
		{
			//strchr for '\0' should succeed
			while (*p != 0)
			{
				if (*p == ch)
				{
					return p;
				}
				p++;
			}
			return (*p == ch) ? p : NULL;
		}
		static LPCWSTR strrchr(LPCWSTR p, WCHAR ch) throw()
		{
			LPCWSTR pch = p+::lstrlenW(p);
			while ((pch != p) && (*pch != ch))
			{
				pch--;
			}
			if (*pch == ch)
			{
				return pch;
			}
			else
			{
				return NULL;
			}
		}
		static LPWSTR _strrev(LPWSTR psz) throw()
		{
			// Optimize NULL, zero-length, and single-CHAR case.
			if ((psz == NULL) || (psz[0] == L'\0') || (psz[1] == L'\0'))
				return psz;

			LPWSTR p = psz+(::lstrlenW( psz )-1);
			LPWSTR q = psz;
			while(q < p)
			{
				WCHAR t = *q;
				*q = *p;
				*p = t;
				q++;
				p--;
			}
			return psz;
		}
		static LPCWSTR strstr(LPCWSTR pStr, LPCWSTR pCharSet) throw()
		{
			int nLen = ::lstrlenW(pCharSet);
			if (nLen == 0)
				return pStr;

			LPCWSTR pMatch;
			LPCWSTR pStart = pStr;
			while ((pMatch = strchr(pStart, *pCharSet)) != NULL)
			{
				if (LGN::API::memcmp(pMatch, pCharSet, nLen*sizeof(WCHAR)) == 0)
					return pMatch;
				pStart++;
			}

			return NULL;
		}
		static int strspn(LPCWSTR psz, LPCWSTR pszCharSet) throw()
		{
			int nRet = 0;
			LPCWSTR p = psz;
			while (*p != 0)
			{
				if(strchr(pszCharSet, *p) == NULL)
					break;
				nRet++;
				p++;
			}
			return nRet;
		}
		static int strcspn(LPCWSTR psz, LPCWSTR pszCharSet) throw()
		{
			int nRet = 0;
			LPCWSTR p = psz;
			while (*p != 0)
			{
				if(strchr(pszCharSet, *p) != NULL)
					break;
				nRet++;
				p++;
			}
			return nRet;
		}
		static LPCWSTR strpbrk(LPCWSTR psz, LPCWSTR pszCharSet) throw()
		{
			LPCWSTR p = psz;
			while (*p != 0)
			{
				if (strchr(pszCharSet, *p) != NULL)
					return p;
				p++;
			}
			return NULL;
		}

		static LPWSTR CharNext(LPCWSTR p) throw()
		{
			return const_cast< LPWSTR >( p+1 );
		}

		static int IsDigit(WCHAR ch) throw()
		{
			WORD type;
			::GetStringTypeExW(0, CT_CTYPE1, &ch, 1, &type);
			return (type & C1_DIGIT) == C1_DIGIT;
		}

		static int IsSpace(WCHAR ch) throw()
		{
			WORD type;
			::GetStringTypeExW(0, CT_CTYPE1, &ch, 1, &type);
			return (type & C1_SPACE) == C1_SPACE;
		}


		static int StringCompare(LPCWSTR pstrOne, LPCWSTR pstrOther) throw()
		{
			//return wcscmp(pstrOne, pstrOther); // ??
			return ::lstrcmpW(pstrOne, pstrOther);
		}

		static int StringCompareIgnore(LPCWSTR pstrOne, LPCWSTR pstrOther) throw()
		{
			return ::lstrcmpiW(pstrOne, pstrOther);
		}

		static int StringCollate(LPCWSTR pstrOne, LPCWSTR pstrOther) throw()
		{ 
			int nRet = CompareStringW(GetThreadLocale(), 0, pstrOne, -1, pstrOther, -1);
			LGNASSERT(nRet != 0);
			return nRet-2;  // Convert to strcmp convention.  This really is documented.
		}

		static int StringCollateIgnore(LPCWSTR pstrOne, LPCWSTR pstrOther) throw()
		{
			int nRet = CompareStringW(GetThreadLocale(), NORM_IGNORECASE, pstrOne, -1, pstrOther, -1);
			LGNASSERT(nRet != 0);
			return nRet-2;  // Convert to strcmp convention.  This really is documented.
		}

		static LPCWSTR StringFindString(LPCWSTR pstrBlock, LPCWSTR pstrMatch) throw()
		{
			return strstr(pstrBlock, pstrMatch);
		}

		//static LPWSTR StringFindString( LPWSTR pszBlock, LPCWSTR pszMatch ) throw()
		//{
		//	return( const_cast< LPWSTR >( StringFindString( const_cast< LPCWSTR >( pszBlock ), pszMatch ) ) );
		//}

		static LPCWSTR StringFindChar(LPCWSTR pstrBlock, WCHAR pstrMatch) throw()
		{
			return strchr(pstrBlock, pstrMatch);
		}

		static LPCWSTR StringFindCharRev(LPCWSTR pstr, WCHAR ch) throw()
		{
			return strrchr(pstr, ch);
		}

		static LPCWSTR StringScanSet(LPCWSTR pszBlock, LPCWSTR pszMatch) throw()
		{
			return strpbrk(pszBlock, pszMatch);
		}

		static int StringSpanIncluding(LPCWSTR pszBlock,
			LPCWSTR pszSet) throw()
		{
			return strspn(pszBlock, pszSet);
		}

		static int StringSpanExcluding(LPCWSTR pszBlock,
			LPCWSTR pszSet) throw()
		{
			return strcspn(pszBlock, pszSet);
		}

		static LPWSTR StringUppercase(LPWSTR psz) throw()
		{
			::CharUpperW(psz);
			return psz;
		}

		static LPWSTR StringUppercase(LPWSTR psz, size_t size) throw()
		{
			DWORD dwSize = static_cast<DWORD>(size);
			::CharUpperBuffW(psz, dwSize);
			return psz;
		}

		static LPWSTR StringLowercase(LPWSTR psz) throw()
		{
			::CharLowerW(psz);
			return psz;
		}

		static LPWSTR StringLowercase(LPWSTR psz, size_t size) throw()
		{
			DWORD dwSize = static_cast<DWORD>(size);
			::CharLowerBuffW(psz, dwSize);
			return psz;
		}

		static LPWSTR StringReverse(LPWSTR psz) throw()
		{
			return _strrev(psz);
		}

//#ifdef _UNICODE
		static int GetFormattedLength(LPCWSTR pszFormat, va_list args) throw()
		{
			WCHAR szBuffer[1028];

			// wvsprintf always truncates the output to 1024 character plus
			// the '\0'.
			int nLength = wvsprintfW(szBuffer, pszFormat, args);
			LGNASSERT(nLength >= 0);
			LGNASSERT(nLength <= 1024);

			return nLength;
		}

		static int Format(LPWSTR pszBuffer, LPCWSTR pszFormat, va_list args) throw()
		{
			return ::wvsprintfW(pszBuffer, pszFormat, args);
		}

		static int Format(LPWSTR pszBuffer, size_t nLength, LPCWSTR pszFormat, va_list args) throw()
		{
			nLength;
			return ::wvsprintfW(pszBuffer, pszFormat, args);
		}
//#endif

		static int GetBaseTypeLength(LPCSTR pszSrc) throw()
		{
			// Returns required buffer size in wchar_ts
			return ::MultiByteToWideChar(_LgnGetConversionACP(), 0, pszSrc, -1, NULL, 0)-1;
		}

		static int GetBaseTypeLength(LPCSTR pszSrc, int nLength) throw()
		{
			// Returns required buffer size in wchar_ts
			return ::MultiByteToWideChar(_LgnGetConversionACP(), 0, pszSrc, nLength, NULL, 0);
		}

		static int GetBaseTypeLength(LPCWSTR pszSrc) throw()
		{
			// Returns required buffer size in wchar_ts
			return ::lstrlenW(pszSrc);
		}

		static int GetBaseTypeLength(LPCWSTR pszSrc, int nLength) throw()
		{
			(void)pszSrc;
			// Returns required buffer size in wchar_ts
			return nLength;
		}

		static void ConvertToBaseType(LPWSTR pszDest, int nDestLength, LPCSTR pszSrc, int nSrcLength = -1) throw()
		{
			// nLen is in wchar_ts
			::MultiByteToWideChar(_LgnGetConversionACP(), 0, pszSrc, nSrcLength, pszDest, nDestLength);
		}

		static void ConvertToBaseType(LPWSTR pszDest, int nDestLength, LPCWSTR pszSrc, int nSrcLength = -1) throw()
		{
			(void)nSrcLength;
			// nLen is in wchar_ts
			LGN::API::memcpy(pszDest, pszSrc, nDestLength*sizeof(WCHAR));
		}

		// this conversion on Unicode strings makes no sense
		/*
		static void ConvertToOem(LPWSTR)
		{
		LGNASSERT(FALSE);
		}
		*/

		// this conversion on Unicode strings makes no sense
		/*
		static void ConvertToAnsi(LPWSTR)
		{
		LGNASSERT(FALSE);
		}
		*/

		static void FloodCharacters(WCHAR ch, int nLength, LPWSTR pstr) throw()
		{
			// nLength is in XCHARs
			for (int i = 0; i < nLength; i++)
				pstr[i] = ch;
		}

		static BSTR AllocSysString(LPCWSTR pchData, int nDataLength) throw()
		{
			BSTR bstr = ::SysAllocStringLen(pchData, nDataLength);
			return bstr;
		}

		static BOOL ReAllocSysString(LPCWSTR pchData, BSTR* pbstr, int nDataLength) throw()
		{
			return ::SysReAllocStringLen(pbstr, pchData, nDataLength);
		}

//#ifdef _UNICODE
		static DWORD FormatMessage(DWORD dwFlags, LPCVOID lpSource,
			DWORD dwMessageID, DWORD dwLanguageID, LPWSTR pstrBuffer,
			DWORD nSize, va_list* pArguments) throw()
		{
			return ::FormatMessageW(dwFlags, lpSource, dwMessageID, dwLanguageID, pstrBuffer, nSize, pArguments);
		}
//#endif
		static int SafeStringLen(const CHAR* psz) throw()
		{
			// returns length in bytes
			return (psz != NULL) ? ::lstrlenA(psz) : 0;
		}

		static int SafeStringLen(LPCWSTR psz) throw()
		{
			// returns length in wchar_ts
			return (psz != NULL) ? ::lstrlenW(psz) : 0;
		}

		static int GetCharLen(LPCWSTR) throw()
		{
			// returns CHAR length
			return 1;
		}
		static int GetCharLen(LPCSTR psz) throw()
		{
			LPCSTR p = ::CharNextA( psz );
			return int( p-psz );
		}

		static DWORD GetEnvironmentVariable(LPCWSTR pstrVar, LPWSTR pstrBuffer, DWORD dwSize) throw()
		{
			return ::GetEnvironmentVariableW(pstrVar, pstrBuffer, dwSize);
		}
	};
#endif // #ifdef __ATLSTR_H__


////////////////////////////////////////////////////////////////////////////////////////////////////
// class ChTraitsEx

	//! ANSI�ַ����������API��װ�ľ�̬ģ����
	/*! �̳���ChTraitsOS��ʵ�ֳ��õ��ַ����������API��ChTraitsOSδ�漰�� */
	template< typename _CharType = CHAR >
	class ChTraitsEx : public LGN_CHTRAISTSBASE_NS::ChTraitsOS< _CharType >
	{
	public:
		//! ��ȡָ�����ַ������ȣ���������ֹ���ַ���
		/*! ����<B>lstrlenA</B>������ο�MSDN
			\param[in] pszStr Դ�ַ���
			\return �ַ����ĳ��ȡ����pszStrΪNULL����������0��
		*/
		static int StringLength(LPCSTR pszStr)
		{
			return ::lstrlenA(pszStr);
		}

		//! ׷��һ���ַ�������һ��
		/*! ����<B>lstrcatA</B>������ο�MSDN
			\param[in,out] pszDest Ŀ�껺��������������������㹻���԰��������ַ���
			\param[in] pszSrc Դ�ַ�������׷�ӵ���\a pszDest����ָ�����ַ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣�������ʧ�ܣ�����ֵ��NULL
		*/
		static LPSTR StringCat(LPSTR pszDest, LPCSTR pszSrc)
		{
			return ::lstrcatA(pszDest, pszSrc);
		}

		//! ��һ���ַ�����������һ���ַ���������
		/*! ����<B>lstrcpyA</B>������ο�MSDN
			\param[out] pszDest Ŀ�껺���������ָ���\a pszSrc�����������������㹻���԰����ַ�����������ֹ���ַ���
			\param[in] pszSrc Դ�ַ���������������\a pszDest����ָ�����ַ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣�������ʧ�ܣ�����ֵ��NULL
			\see ��Ҫ����ָ����Ŀ���ַ� StringCopyN
		*/		
		static LPSTR StringCopy(LPSTR pszDest, LPCSTR pszSrc)
		{
			return ::lstrcpyA(pszDest, pszSrc);
		}
		//! ��һ���ַ�������ָ����Ŀ���ַ�����һ���ַ���������
		/*! ����<B>lstrcpynA</B>������ο�MSDN
			\param[out] pszDest Ŀ�껺�����������ո��Ƶ��ַ����û����������㹻���ܰ���ָ��\a iMaxLength�������ַ�������һ����ֹ���ַ���
			\param[in] pszSrc Դ�ַ���
			\param[in] iMaxLength ָ����ַ���������pszSrc���Ƶ�pszDest����󳤶ȣ�������ֹ���ַ�
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣��ʹ��\a iMaxLength��Դ�ַ������ȸ��󣬸ú�����ִ�гɹ����������ʧ�ܣ�����ֵ��NULL��
		*/		
		static LPSTR StringCopyN(LPSTR pszDest, LPCSTR pszSrc, int iMaxLength)
		{
			return ::lstrcpynA(pszDest, pszSrc, iMaxLength);
		}

		//! �ò����б��ʽ����һ��printf�����ַ���
		/*! ����<B>wvnsprintfA(vs2003) / wvsprintfA</B>������ο�MSDN
			\param[out] lpOut һ������������������ַ���
			\param[in] cchLimitIn ����\a lpOut���������ַ���
			\param[in] lpFmt printf���ĸ�ʽ�ַ���
			\param[in] arglist �����б�
			\return ��������ɹ�������д�뵽������\a lpOut���ַ������������κ���ֹ�ַ���������ִ��󣬷���һ����ֵ��
		*/				
		static int FormatN(LPSTR lpOut, int cchLimitIn, LPCSTR lpFmt, va_list arglist)
		{
#if (_MSC_VER >= 1300)
			return ::wvnsprintfA(lpOut, cchLimitIn, lpFmt, arglist);
#else
			return ::wvsprintfA(lpOut, lpFmt, arglist);
#endif
		}
		/*! \brief ��ʽ������д�뵽ָ���Ļ�����
			\param[out] lpOut һ������������������ַ���
			\param[in] cchLimitIn ����\a lpOut���������ַ���
			\param[in] lpFmt printf���ĸ�ʽ�ַ���
			\return ��������ɹ�������ֵ�Ǵ洢��������������ַ�����������ֹ�ַ����������ʧ�ܣ�����ֵ�ǳ���Ԥ�ڵ�������ȡ�			
			\see ���������б�����FormatN
			\note �κβ���ת�������Ƶ����������������Ӧ�ĸ�ʽ�ַ�����ʽ�淶��
		*/			
		static int FormatNP(LPSTR lpOut, int cchLimitIn, LPCSTR lpFmt, ...)
		{
			va_list ptr;
			va_start(ptr, lpFmt);
			int nRet = FormatN(lpOut, cchLimitIn, lpFmt, ptr);
			va_end(ptr);
			return nRet;
		}

		//! ������������ַ���
		/*! ����<B>OutputDebugStringA</B>������ο�MSDN
			\param[in] pszOutputString �ַ���
			\note �ں�����ǰ��'S'Ϊ�˷�ֹWindow���滻
		*/
		static void SOutputDebugString(LPCSTR pszOutputString)
		{
			::OutputDebugStringA(pszOutputString);
		}

		//! ��Ϣ�ַ�����ʽ��
		/*! ����<B>FormatMessageA</B>������ο�MSDN
			\param[in] dwMessageId ������Ϣ��
			\param[out] lpBuffer Ŀ���ַ���
			\param[out] nSize �ַ���\a lpBuffer
		*/
		static UINT32 SFormatMessage(UINT32 dwMessageId, LPSTR lpBuffer, UINT32 nSize)
		{
			return ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lpBuffer, nSize, NULL);
		}

		//! ���Ǵ��ļ�����ָ���ļ�β��������ļ��������򴴽�
		/*! ����<B>CreateFileA</B>������ο�MSDN
			\param[in] pszFileName �ļ���
			\return HRESULT
		*/
		static HANDLE SOpenFileAlways(LPCSTR pszFileName)
		{
			HANDLE hFile = ::CreateFileA(pszFileName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
				::SetFilePointer(hFile, 0, NULL, FILE_END);
			return hFile;
		}

		//! ��ȡָ��ģ����������
		/*! ����<B>GetModuleFileNameA</B>������ο�MSDN
			\param[in] hModule ģ����
			\param[in] lpFileName һ������������������ַ���
			\param[in] dwSize �ַ���������\a lpFileName����󳤶�
			\return ��������ɹ�������ֵ���ַ�������
			\note ģ����\a hModule = NULLʱ����ȡ��ǰ���̵�ִ���ļ���������
		*/
		static UINT32 SGetModuleFileName(HANDLE hModule, LPSTR lpFileName, UINT32 dwSize)
		{
			return ::GetModuleFileNameA((HMODULE)hModule, lpFileName, dwSize);
		}

		//! ���·�������ļ������Ƴ���
		/*! ����<B>PathRemoveFileSpecA</B>������ο�MSDN
			\param[in,out] pszPath һ��·������󳤶�ΪMAX_PATH��������������ļ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszPath��ָ�롣�������ʧ�ܣ�����ֵ��NULL
		*/
		static LPSTR SPathRemoveFileSpec(LPSTR pszPath)
		{
			if (::PathRemoveFileSpecA(pszPath))
				return pszPath;
			return NULL;
		}

		//! �������ַ�����ϳ�һ��·��
		/*! ����<B>PathCombineA</B>������ο�MSDN
			\param[out] pszDest Ŀ�Ļ��������������pszDir��pszFile��ϵ�·���ַ���
			\param[in] pszDir һ��Ŀ¼�ַ���
			\param[in] pszFile һ���ļ����ַ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣�������ʧ�ܣ�����ֵ��NULL
		*/
		static LPSTR SPathCombine(LPSTR pszDest, LPCSTR pszDir, LPCSTR pszFile)
		{
			return ::PathCombineA(pszDest, pszDir, pszFile);
		}

		//! ��ָ����ģ����ص����ý��̵ĵ�ַ�ռ䡣
		/*! ����<B>LoadLibraryA</B>������ο�MSDN
			\param[in] lpFileName һ��ģ������ơ��������һ����ģ�飨dll�ļ�����һ����ִ��ģ�飨exe�ļ�����
			\return ��������ɹ�������ֵ��һ��ָ��ģ��ľ�����������ʧ�ܣ�����ֵ��NULL��
		*/
		static HMODULE SLoadLibrary(LPCSTR lpFileName)
		{
			return ::LoadLibraryA(lpFileName);
		}
		
	};

	//! UNICODE�ַ����������API��װ�ľ�̬ģ����
	/*! �̳���ChTraitsOS��ʵ�ֳ��õ��ַ����������API��ChTraitsOSδ�漰�� */
	template<>
	class ChTraitsEx< WCHAR > : public LGN_CHTRAISTSBASE_NS::ChTraitsOS< WCHAR >
	{
	public:
		//! ��ȡָ�����ַ������ȣ���������ֹ���ַ���
		/*! ����<B>lstrlenW</B>������ο�MSDN
			\param[in] pszStr Դ�ַ���
			\return �ַ����ĳ��ȡ����pszStrΪNULL����������0��
		*/
		static int StringLength(LPCWSTR pszStr)
		{
			return ::lstrlenW(pszStr);
		}

		//! ׷��һ���ַ�������һ��
		/*! ����<B>lstrcatW</B>������ο�MSDN
			\param[in,out] pszDest Ŀ�껺��������������������㹻���԰��������ַ���
			\param[in] pszSrc Դ�ַ�������׷�ӵ���\a pszDest����ָ�����ַ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣�������ʧ�ܣ�����ֵ��NULL
		*/
		static LPWSTR StringCat(LPWSTR pszDest, LPCWSTR pszSrc)
		{
			return ::lstrcatW(pszDest, pszSrc);
		}

		//! ��һ���ַ�����������һ���ַ���������
		/*! ����<B>lstrcpyW</B>������ο�MSDN
			\param[out] pszDest Ŀ�껺���������ָ���\a pszSrc�����������������㹻���԰����ַ�����������ֹ���ַ���
			\param[in] pszSrc Դ�ַ���������������\a pszDest����ָ�����ַ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣�������ʧ�ܣ�����ֵ��NULL
			\see ��Ҫ����ָ����Ŀ���ַ� StringCopyN
		*/		
		static LPWSTR StringCopy(LPWSTR pszDest, LPCWSTR pszSrc)
		{
			return ::lstrcpyW(pszDest, pszSrc);
		}
		//! ��һ���ַ�������ָ����Ŀ���ַ�����һ���ַ���������
		/*! ����<B>lstrcpynW</B>������ο�MSDN
			\param[out] pszDest Ŀ�껺�����������ո��Ƶ��ַ����û����������㹻���ܰ���ָ��\a iMaxLength�������ַ�������һ����ֹ���ַ���
			\param[in] pszSrc Դ�ַ���
			\param[in] iMaxLength ָ����ַ���������pszSrc���Ƶ�pszDest����󳤶ȣ�������ֹ���ַ�
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣��ʹ��\a iMaxLength��Դ�ַ������ȸ��󣬸ú�����ִ�гɹ����������ʧ�ܣ�����ֵ��NULL��
		*/		
		static LPWSTR StringCopyN(LPWSTR pszDest, LPCWSTR pszSrc, int iMaxLength)
		{
			return ::lstrcpynW(pszDest, pszSrc, iMaxLength);
		}

		//! �ò����б��ʽ����һ��printf�����ַ���
		/*! ����<B>wvnsprintfW(vs2003) / wvsprintfW</B>������ο�MSDN
			\param[out] lpOut һ������������������ַ���
			\param[in] cchLimitIn ����\a lpOut���������ַ���
			\param[in] lpFmt printf���ĸ�ʽ�ַ���
			\param[in] arglist �����б�
			\return ��������ɹ�������д�뵽������\a lpOut���ַ������������κ���ֹ�ַ���������ִ��󣬷���һ����ֵ��
		*/				
		static int FormatN(LPWSTR lpOut, int cchLimitIn, LPCWSTR lpFmt, va_list arglist)
		{
#if (_MSC_VER >= 1300)
			return ::wvnsprintfW(lpOut, cchLimitIn, lpFmt, arglist);
#else
			return ::wvsprintfW(lpOut, lpFmt, arglist);
#endif
		}
		/*! \brief ��ʽ������д�뵽ָ���Ļ�����
			\param[out] lpOut һ������������������ַ���
			\param[in] cchLimitIn ����\a lpOut���������ַ���
			\param[in] lpFmt printf���ĸ�ʽ�ַ���
			\return ��������ɹ�������ֵ�Ǵ洢��������������ַ�����������ֹ�ַ����������ʧ�ܣ�����ֵ�ǳ���Ԥ�ڵ�������ȡ�			
			\see ���������б�����FormatN
			\note �κβ���ת�������Ƶ����������������Ӧ�ĸ�ʽ�ַ�����ʽ�淶��
		*/			
		static int FormatNP(LPWSTR lpOut, int cchLimitIn, LPCWSTR lpFmt, ...)
		{
			va_list ptr;
			va_start(ptr, lpFmt);
			int nRet = FormatN(lpOut, cchLimitIn, lpFmt, ptr);
			va_end(ptr);
			return nRet;
		}

		//! ������������ַ���
		/*! ����<B>OutputDebugStringW</B>������ο�MSDN
			\param[in] pszOutputString �ַ���
			\note �ں�����ǰ��'S'Ϊ�˷�ֹWindow���滻
		*/
		static void SOutputDebugString(LPCWSTR pszOutputString)
		{
			::OutputDebugStringW(pszOutputString);
		}

		//! ��Ϣ�ַ�����ʽ��
		/*! ����<B>FormatMessageW</B>������ο�MSDN
			\param[in] dwMessageId ������Ϣ��
			\param[out] lpBuffer Ŀ���ַ���
			\param[out] nSize �ַ���\a lpBuffer
		*/
		static UINT32 SFormatMessage(UINT32 dwMessageId, LPWSTR lpBuffer, UINT32 nSize)
		{
			return ::FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lpBuffer, nSize, NULL);
		}

		//! ���Ǵ��ļ�����ָ���ļ�β��������ļ��������򴴽�
		/*! ����<B>CreateFileW</B>������ο�MSDN
			\param[in] pszFileName �ļ���
			\return HRESULT
		*/
		static HANDLE SOpenFileAlways(LPCWSTR pszFileName)
		{
			HANDLE hFile = ::CreateFileW(pszFileName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
				::SetFilePointer(hFile, 0, NULL, FILE_END);
			return hFile;
		}

		//! ��ȡָ��ģ����������
		/*! ����<B>GetModuleFileNameW</B>������ο�MSDN
			\param[in] hModule ģ����
			\param[in] lpFileName һ������������������ַ���
			\param[in] dwSize �ַ���������\a lpFileName����󳤶�
			\return ��������ɹ�������ֵ���ַ�������
			\note ģ����\a hModule = NULLʱ����ȡ��ǰ���̵�ִ���ļ���������
		*/
		static UINT32 SGetModuleFileName(HANDLE hModule, LPWSTR lpFileName, UINT32 dwSize)
		{
			return ::GetModuleFileNameW((HMODULE)hModule, lpFileName, dwSize);
		}

		//! ���·�������ļ������Ƴ���
		/*! ����<B>PathRemoveFileSpecW</B>������ο�MSDN
			\param[in,out] pszPath һ��·������󳤶�ΪMAX_PATH��������������ļ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszPath��ָ�롣�������ʧ�ܣ�����ֵ��NULL
		*/
		static LPWSTR SPathRemoveFileSpec(LPWSTR pszPath)
		{
			if (::PathRemoveFileSpecW(pszPath))
				return pszPath;
			return NULL;
		}

		//! �������ַ�����ϳ�һ��·��
		/*! ����<B>PathCombineW</B>������ο�MSDN
			\param[out] pszDest Ŀ�Ļ��������������pszDir��pszFile��ϵ�·���ַ���
			\param[in] pszDir һ��Ŀ¼�ַ���
			\param[in] pszFile һ���ļ����ַ���
			\return ��������ɹ�������ֵ��һ��ָ�򻺳���\a pszDest��ָ�롣�������ʧ�ܣ�����ֵ��NULL
		*/
		static LPWSTR SPathCombine(LPWSTR pszDest, LPCWSTR pszDir, LPCWSTR pszFile)
		{
			return ::PathCombineW(pszDest, pszDir, pszFile);
		}

		//! ��ָ����ģ����ص����ý��̵ĵ�ַ�ռ䡣
		/*! ����<B>LoadLibraryW</B>������ο�MSDN
			\param[in] lpFileName һ��ģ������ơ��������һ����ģ�飨dll�ļ�����һ����ִ��ģ�飨exe�ļ�����
			\return ��������ɹ�������ֵ��һ��ָ��ģ��ľ�����������ʧ�ܣ�����ֵ��NULL��
		*/
		static HMODULE SLoadLibrary(LPCWSTR lpFileName)
		{
			return ::LoadLibraryW(lpFileName);
		}

	};

	typedef ChTraitsEx< CHAR > ChTraitsExA; //!< ���Ͷ��� LGN::ChTraitsEx< CHAR >
	typedef ChTraitsEx< WCHAR > ChTraitsExW; //!< ���Ͷ��� LGN::ChTraitsEx< WCHAR >
	typedef ChTraitsEx< TCHAR > ChTraitsExT; //!< ���Ͷ��� LGN::ChTraitsEx< TCHAR >



////////////////////////////////////////////////////////////////////////////////////////////////////
// class CLoadModuleT

	//! ����DLLģ���ģ����
	/*! ���಻�̳У�����󲻿ɸ��� 
		-# �������鿴 \ref loadmodule_example_page
	*/
	template< typename _BaseType>
	class CLoadModuleT
	{
	public:
		/*! \brief ���캯��������ģ����ΪNULL						
		*/
		CLoadModuleT() : m_hMod(NULL)
		{
		}
		/*! \brief ���캯������ָ����ģ����ص����ý��̵ĵ�ַ�ռ䡣				
			\param[in] pszModuleName һ��ģ������ơ��������һ����ģ�飨dll�ļ�����һ����ִ��ģ�飨exe�ļ�����
		*/
		CLoadModuleT(const _BaseType * pszModuleName)
		{
			m_hMod = ChTraitsEx< _BaseType >::LoadLibraryHandle(pszModuleName);
		}
		//! �鹹����
		~CLoadModuleT()
		{
			//Free();
		}

		/*! \brief ��ָ����ģ����ص����ý��̵ĵ�ַ�ռ䡣				
			\param[in] pszModuleName һ��ģ������ơ��������һ����ģ�飨dll�ļ�����һ����ִ��ģ�飨exe�ļ�����
		*/
		bool Load(const _BaseType * pszModuleName)
		{
			m_hMod = ChTraitsEx< _BaseType >::SLoadLibrary(pszModuleName);
			return (m_hMod != NULL);
		}

		/*! \brief �ͷ��Ѽ��صĶ�̬���ӿ�ģ��
		*/
		void Free()
		{
			if (m_hMod != NULL)
			{
				::FreeLibrary(m_hMod);
				m_hMod = NULL;
			}
		}

		/*! \brief ��ȡ�Ѽ��ص�ģ�������������ڲ����ΪNULL
		*/
		HMODULE Detach()
		{
			HMODULE hMod = m_hMod;
			m_hMod= NULL;
			return hMod;
		}

		/*! \brief ����������					
			\return ��ȡ�Ѽ��ص�ģ����
		*/
		operator const HMODULE()
		{
			return m_hMod;
		}

		/*! \brief �ӱ����ص�ģ���������һ����������������ĵ�ַ��			
			\param[in] pszProcName һ������������������������ֵ��
			\return ��������ɹ�������ֵ��һ����������������ĵ�ַ���������ʧ�ܣ�����ֵ��NULL��
		*/
		LPVOID GetAddress(LPCSTR pszProcName)
		{
			return ::GetProcAddress(m_hMod, pszProcName);
		}

	protected:
		//! ģ����
		HMODULE m_hMod;

	private:
		CLoadModuleT( const CLoadModuleT& ) throw();
		CLoadModuleT& operator=( const CLoadModuleT& ) throw();
	};

	typedef CLoadModuleT< CHAR > CLoadModuleA; //!< ���Ͷ��� LGN::CLoadModuleT< CHAR >
	typedef CLoadModuleT< WCHAR > CLoadModuleW; //!< ���Ͷ��� LGN::CLoadModuleT< WCHAR >
	typedef CLoadModuleT< TCHAR > CLoadModule; //!< ���Ͷ��� LGN::CLoadModuleT< TCHAR >

/*! \page loadmodule_example_page CLoadModuleT����
<pre>	%CLoadModuleT���ʹ������</pre>
<pre>
\#include "lgnbase.h"

	// ...
	LGN::CLoadModule loadMod(TEXT("user32.dll"));
	LPVOID pfn = loadMod.GetAddress("SetWindowTextA");
</pre>
*/


////////////////////////////////////////////////////////////////////////////////////////////////////
// class FileTraitsTrace

	//! �ļ������ľ�̬ģ����
	/*! ֻ��ʵ���ļ�β���������ݵĹ��ܣ�ֻ������lgntrace.h�� 
	*/
	template< typename BaseType >
	class FileTraitsTrace
	{
	public:

		/*! \brief ���ļ������ļ�β����������
			\param[in] pszFileName �ļ���
			\param[in] pData ��д������
			\param[in] unLength ����\a pData�ĳ���
			\return HRESULT
		*/
		static HRESULT Append(const BaseType * pszFileName, LPCVOID pData, UINT32 unLength)
		{
			HANDLE hFile = ChTraitsEx< BaseType >::SOpenFileAlways(pszFileName);
			if (hFile == INVALID_HANDLE_VALUE)
				return API::HResultFromError( ::GetLastError() );

			DWORD dwBytesWritten;
			::WriteFile(hFile, pData, unLength, &dwBytesWritten, NULL);

			::CloseHandle(hFile);
			return S_OK;
		}
	};

	typedef FileTraitsTrace< CHAR > FileTraitsTraceA; //!< ���Ͷ��� LGN::FileTraitsTrace< CHAR >
	typedef FileTraitsTrace< WCHAR > FileTraitsTraceW; //!< ���Ͷ��� LGN::FileTraitsTrace< WCHAR >
	typedef FileTraitsTrace< TCHAR > FileTraitsTraceT; //!< ���Ͷ��� LGN::FileTraitsTrace< TCHAR >

}; // namespace LGN

#endif // #ifndef __LGNWIN_CORE_H__
