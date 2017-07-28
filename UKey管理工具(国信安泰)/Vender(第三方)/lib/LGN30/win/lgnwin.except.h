/*! \file lgnwin.except.h 
 *  \brief WINϵͳ���쳣����
 *
 *  ��lgnbase.h���������̲���ֱ�Ӱ������ļ�
 *
 *  ��Ҫ�����쳣��C�쳣��LGN�쳣��ATL�쳣��AFX�쳣
 *  <ul>
 *  	<li> ����C�쳣������_LGN_NO_EXCEPTIONS
 *		<li> ����LGN�쳣��Ĭ�Ϸ�ʽ��û�ж���_LGN_NO_EXCEPTIONS����û�а���atl��û�а���afx��MFC��
 *  	<li> ����ATL�쳣��û�ж���_LGN_NO_EXCEPTIONS���Ұ���atl��û�а���afx��MFC��
 *  	<li> ����AFX�쳣��û�ж���_LGN_NO_EXCEPTIONS���Ұ���afx��MFC��
 *  </ul>
 *  \author ljc
 *  \version 3.0.0
 *  \date    2010-2012
 *  \bug
 *  \warning
 */

#ifndef __LGNWIN_EXCEPT_H__
#define __LGNWIN_EXCEPT_H__

//#pragma once


/////////////////////////////////////////////////////////////////////////////
// Win32 libraries


namespace LGN
{
////////////////////////////////////////////////////////////////////////////////////////////////////

	//! �׳�C�쳣�������з��أ����ڲ�����<B>RaiseException</B>������ο�MSDN 
	inline void LGN_NORETURN _LgnRaiseException( UINT32 dwExceptionCode, UINT32 dwExceptionFlags = EXCEPTION_NONCONTINUABLE )
	{
		::RaiseException( dwExceptionCode, dwExceptionFlags, 0, NULL );
	}


////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __ATLEXCEPT_H__
	//! �����ض��壬ʹ��ATL���쳣��
	typedef ATL::CAtlException CLgnException;
#else
	//! LGN���쳣��
	class CLgnException
	{
	public:
		CLgnException() throw() :
			m_hr( E_FAIL )
		{
		}

		CLgnException( HRESULT hr ) throw() :
			m_hr( hr )
		{
		}

		operator HRESULT() const throw()
		{
			return( m_hr );
		}

	public:
		HRESULT m_hr;
	};
#endif // #ifdef __ATLEXCEPT_H__


////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _LGN_NO_EXCEPTIONS

// Throw a CAtlException with the given HRESULT
#if defined( LgnThrow ) || defined( _LGN_CUSTOM_THROW )  // You can define your own AtlThrow to throw a custom exception.
#ifdef _AFX
#error MFC projects must use default implementation of LgnThrow()
#endif
#else
	//! �׳��쳣����
	/*! ��ʹ��AFX�Ĺ����MFC�������׳�AFX�쳣
	\param[in] hr �����루����С��0��
	*/
	LGN_NOINLINE LGN_NORETURN inline void WINAPI LgnThrow( HRESULT hr )
	{
		//LGNTRACE(LGN_TRACE_CATEGORY_DEF, TraceLevel::Emergency, TEXT("AtlThrow: hr = 0x%x\n"), hr );
#ifdef _AFX
		if( hr == E_OUTOFMEMORY )
		{
			AfxThrowMemoryException();
		}
		else
		{
			AfxThrowOleException( hr );
		}
#else
		throw CLgnException( hr );
#endif
	};
#endif

	//! �׳��쳣���󣨴����ΪGetLastError��
	/*! \see LgnThrow( API::HResultFromError(GetLastError()) ) */
	LGN_NOINLINE LGN_NORETURN inline void WINAPI LgnThrowLastWin32()
	{
		LgnThrow( API::HResultFromError( ::GetLastError() ) );
	}

#else  // no exception handling

// Throw a CLgnException with the given HRESULT
#if !defined( LgnThrow ) && !defined( _LGN_CUSTOM_THROW )  // You can define your own LgnThrow

	LGN_NOINLINE inline void WINAPI LgnThrow( HRESULT hr )
	{
		//LGNTRACE(LGN_TRACE_CATEGORY_DEF, TraceLevel::Emergency, TEXT("LgnThrow: hr = 0x%x\n"), hr );
		//LGNASSERT( false );
		UINT32 dwExceptionCode;
		switch(hr)
		{
		case E_OUTOFMEMORY:
			dwExceptionCode = STATUS_NO_MEMORY;
			break;
		default:
			dwExceptionCode = EXCEPTION_ILLEGAL_INSTRUCTION;
		}
		_LgnRaiseException(dwExceptionCode);
	}
#endif

	// Throw a CLgnException corresponding to the result of ::GetLastError
	LGN_NOINLINE inline void WINAPI LgnThrowLastWin32()
	{
		LgnThrow( API::HResultFromError( ::GetLastError() ) );
	}

#endif  // no exception handling


/*! \page lgnexception_example_page CLgnException����
<pre>	%CLgnException���ʹ������</pre>
<pre>
\#include "lgnbase.h"

	// ...
	try
	{
		LGN::LgnThrow(-1);
	}
	catch(LGN::CLgnException e)
	{
		HRESULT hr = e;
	}
</pre>
*/

};  // namespace LGN

#endif  // __LGNWIN_EXCEPT_H__
