/*! \file lgnwin.api.h 
 *  \brief WINϵͳ��API�򵥷�װ
 *
 *  ��lgnbase.h���������̲���ֱ�Ӱ������ļ�
 *
 *  \author ljc
 *  \version 3.0.0
 *  \date    2010-2012
 *  \bug
 *  \warning
 */

#ifndef __LGNWIN_API_H__
#define __LGNWIN_API_H__

//#pragma once


/////////////////////////////////////////////////////////////////////////////
// Win32 libraries


namespace LGN
{
	namespace API //! ϵͳAPI���������ռ�
	{
		//! ת������ţ���֤��ֵС��0
		LGN_INLINE HRESULT HResultFromError(INT32 nError)
		{
			return HRESULT_FROM_WIN32(nError);
		}

		//! memory �ڶ���_LGN_NO_DEFAULT_LIBS���ض���
		LGN_INLINE void memcpy(LPVOID pDest, LPCVOID pSrc, size_t nSize)
		{
			::memcpy(pDest, pSrc, nSize);
			//::CopyMemory(pDest, pSrc, nSize);
		}
		//! memmove �ڶ���_LGN_NO_DEFAULT_LIBS���ض���
		LGN_INLINE void memmove(LPVOID pDest, LPCVOID pSrc, size_t nSize)
		{
			::memmove(pDest, pSrc, nSize);
			//::MoveMemory(pDest, pSrc, nSize);
		}
		//! memcpy �ڶ���_LGN_NO_DEFAULT_LIBS���ض���
		LGN_INLINE int memcmp(LPCVOID pBuff1, LPCVOID pBuff2, size_t nSize)
		{
			return ::memcmp(pBuff1, pBuff2, nSize);
		}		
		//! memset �ڶ���_LGN_NO_DEFAULT_LIBS���ض���
		LGN_INLINE void memset(LPVOID pDest, BYTE btFill, size_t nSize)
		{
			::memset(pDest, btFill, nSize);
			//::FillMemory(pDest, nSize, btFill);
		}
		//! \see memset(\a pDest, 0, \a nSize)
		LGN_INLINE void memzero(LPVOID pDest, size_t nSize)
		{
			::memset(pDest, 0, nSize);
			//::ZeroMemory(pDest, nSize);
		}

		//! ��ȡANSI�ַ������ȣ�\a pszStrΪNULLʱ����0
		LGN_INLINE int SafeStringLength(LPCSTR pszStr)
		{
			return (pszStr == NULL)? 0 : ::lstrlenA(pszStr);
		}
		//! ��ȡUNICODE�ַ������ȣ�\a pszStrΪNULLʱ����0
		LGN_INLINE int SafeStringLength(LPCWSTR pszStr)
		{
			return (pszStr == NULL)? 0 : ::lstrlenW(pszStr);
		}

		//! ��һ���̰߳�ȫ�����ڲ�����<B>InterlockedIncrement</B>������ο�MSDN 
		LGN_INLINE ULONG SafeIncrement(ULONG * pVal)
		{
			return ::InterlockedIncrement((PLONG)pVal);
		}
		//! ��һ���̰߳�ȫ�����ڲ�����<B>InterlockedDecrement</B>������ο�MSDN 
		LGN_INLINE ULONG SafeDecrement(ULONG * pVal)
		{
			return ::InterlockedDecrement((PLONG)pVal);
		}
		LGN_INLINE ULONG SafeExchange(ULONG* pVal,ULONG Value)
		{
			return ::InterlockedExchange(pVal,Value);
		}

		//! �ر��ں˾�����ڲ�����<B>CloseHandle</B>������ο�MSDN 
		LGN_INLINE void CloseHandle(HANDLE hObject)
		{
			::CloseHandle(hObject);
		}

		//! ��ǰ�߳�˯�ߵȴ����ڲ�����<B>Sleep</B>������ο�MSDN 
		LGN_INLINE void Sleep(UINT32 dwMilliseconds)
		{
			::Sleep(dwMilliseconds);
		}

		//! ����ϵͳ���������ʱ�䡣�ڲ�����<B>GetTickCount</B>������ο�MSDN 
		LGN_INLINE UINT32 GetTickCount()
		{
			return ::GetTickCount();
		}

		//! ��ȡ��ǰ����ʱ�䡣�ڲ�����<B>GetLocalTime</B>������ο�MSDN 
		LGN_INLINE void GetLocalTime(LPSYSTEMTIME lpSystemTime)
		{
			::GetLocalTime(lpSystemTime);
		}

		//! ��ȡ��ǰ����ID���ڲ�����<B>GetCurrentProcessId</B>������ο�MSDN 
		LGN_INLINE PID_T GetCurrentProcessId()
		{
			return ::GetCurrentProcessId();
		}
		//! ��ȡ��ǰ�߳�ID���ڲ�����<B>GetCurrentThreadId</B>������ο�MSDN 
		LGN_INLINE TID_T GetCurrentThreadId()
		{
			return ::GetCurrentThreadId();
		}

	}; // namespace API

}; // namespace LGN

#endif
