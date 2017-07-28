/*! \file lgntrace.h 
 *  \brief �������������Ϣ�ļ���
 *
 *  ��lgnbase.h���������̲���ֱ�Ӱ������ļ�
 *
 *  �����������ṹCTraceCategory������������������ڵ��ļ������к���CTraceFileAndLineInfo�����������CTrace<br>
 *  һ�㲻������Щ�ֱ࣬�����䶨���һ�׸��ٺ꣬�������鿴 \ref tracemacro_example_page
 *
 *  ������̲�Ҫ�������������Ϣ���ܣ��������º꣺<br>
 *		\#define LGN_SUPPORT_TRACE 0<br>
 *
 *  �޸�Ĭ�ϵĸ����������ڰ���lgnbase.h��lgntrace.h��ǰ���������¶������º꣺<br>
 *		\#define LGN_TRACE_CATEGORY_DEF_FLAGS \<newValue\><br>
 *		\#define LGN_TRACE_CATEGORY_DEF_LEVEL \<newValue\><br>
 *		\#define LGN_TRACE_CATEGORY_DEF_NAME \<newValue\><br>
 *		\#define LGN_TRACE_CATEGORY_DEF_FILE \<newValue\><br>
 *  
 *  \author ljc
 *  \version 3.0.0
 *  \date    2010-2012
 *  \bug
 *  \warning
 */

#ifndef __LGNTRACE_H__
#define __LGNTRACE_H__

//#pragma once

#ifndef LGN_SUPPORT_TRACE
#define LGN_SUPPORT_TRACE 1 //!< ��ʾ�Ƿ�������־���ٴ��룬Ĭ��Ϊ����
#endif


namespace LGN
{
////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//! �������ı�־
	struct TraceFlag
	{
		//! �������ı�־Value
		enum _Value
		{
			CategoryNameA		= 0x00000001, //!< ��ʾpCategoryNameΪANSI�ַ�����CategoryNameA��CategoryNameWֻ��ѡ��һ��
			CategoryNameW		= 0x00000002, //!< ��ʾpCategoryNameΪUNICODE�ַ�����CategoryNameA��CategoryNameWֻ��ѡ��һ��
			DateTime			= 0x00000004, //!< ���������ǰʱ��
			FileLineInfo		= 0x00000008, //!< ������������ļ���������
			ProcessIdTreadId	= 0x00000010, //!< ���������ǰ����Id���߳�Id
			OutputFileA			= 0x01000000, //!< ��ʾpOutputFileNameΪANSI�ַ�����������־��Ϣ��������ļ���
		};
	};

	//! ������־�ļ���
	struct TraceLevel
	{
		//! �������ı�־Value
		enum _Value // LogSeverity
		{
			Emergency = 0,		//!< system is unusable
			Alert = 1,			//!< action must be taken immediately
			Critical = 2,		//!< critical conditions
			Error = 3,			//!< error conditions
			Warning = 4,		//!< warning conditions
			Notice = 5,			//!< normal but significant condition
			Informational = 6,	//!< informational
			Debug = 7			//!< debug-level messages
		};
	};

	//! �������ṹ
	/*!	��Դ atltrace.h������<B>ATL::CTraceCategory</B>������ο�MSDN
	*/
	struct CTraceCategory
	{
		UINT32 dwFlags; //!< �������ı�־ֵ LGN::TraceFlag
		UINT32 dwLevel; //!< �������ļ���ֵ LGN::TraceLevel
		LPCVOID pCategoryName; //!< �����������ƣ����dwFlags & CategoryNameA��ʾANSI�ַ��������dwFlags & CategoryNameW��ʾUNICODE�ַ���
		LPCVOID pOutputFileName; //!< ����ļ��������dwFlags & OutputFileA��ʾANSI�ַ����������������������

		//! ���캯����ֱ�ӵ���Init
		CTraceCategory(UINT32 dwFlags, UINT32 dwLevel, LPCSTR pszCategoryName, LPCSTR pszOutputFileName = NULL)
		{
			Init(dwFlags | TraceFlag::CategoryNameA, dwLevel, pszCategoryName, pszOutputFileName);
		}
		//! ���캯����ֱ�ӵ���Init
		CTraceCategory(UINT32 dwFlags, UINT32 dwLevel, LPCWSTR pszCategoryName, LPCSTR pszOutputFileName = NULL)
		{
			Init(dwFlags | TraceFlag::CategoryNameW, dwLevel, pszCategoryName, pszOutputFileName);
		}

		//! ���ýṹ�ı�����Աֵ
		void Init(UINT32 dwFlags, UINT32 dwLevel, LPCVOID pszCategoryName, LPCSTR pszOutputFileName)
		{
			this->dwFlags = dwFlags;
			this->dwLevel = dwLevel;
			this->pCategoryName = pszCategoryName;
			this->pOutputFileName = pszOutputFileName;
			if (pszOutputFileName != NULL)
				this->dwFlags |= (TraceFlag::OutputFileA | TraceFlag::DateTime);
		}
	};
	typedef CTraceCategory * PTRACECATEGORY; //!< �����ض��� LGN::CTraceCategoryָ������
	typedef const CTraceCategory * PCTRACECATEGORY; //!< �����ض��� LGN::CTraceCategory����ָ������


////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if (LGN_SUPPORT_TRACE)

#ifndef LGN_TRACE_CATEGORY_DEF_FLAGS
# define LGN_TRACE_CATEGORY_DEF_FLAGS LGN::TraceFlag::FileLineInfo //!< Ĭ�ϸ������ı�־ֵ  \see LGN::TraceFlag
#endif
#ifndef LGN_TRACE_CATEGORY_DEF_LEVEL
# define LGN_TRACE_CATEGORY_DEF_LEVEL LGN::TraceLevel::Warning //!< Ĭ�ϸ������ļ���ֵ  \see LGN::TraceLevel
#endif
#ifndef LGN_TRACE_CATEGORY_DEF_NAME
# define LGN_TRACE_CATEGORY_DEF_NAME LGN_TEXT("TraceGeneral") //!< Ĭ�ϸ�����������
#endif
#ifndef LGN_TRACE_CATEGORY_DEF_FILE
# define LGN_TRACE_CATEGORY_DEF_FILE NULL //!< Ĭ�ϸ�����������ļ���
#endif
#if (LGN_SUPPORT_SELECTANY)
	LGN_SELECTANY CTraceCategory lgnTraceGeneral(LGN_TRACE_CATEGORY_DEF_FLAGS, LGN_TRACE_CATEGORY_DEF_LEVEL, LGN_TRACE_CATEGORY_DEF_NAME, LGN_TRACE_CATEGORY_DEF_FILE);
#else
	//! Ĭ�ϸ���������LGN::CTraceCategory lgnTraceGeneral(LGN_TRACE_CATEGORY_DEF_FLAGS, LGN_TRACE_CATEGORY_DEF_LEVEL, LGN_TRACE_CATEGORY_DEF_NAME, LGN_TRACE_CATEGORY_DEF_FILE)
	extern LGN::CTraceCategory lgnTraceGeneral;
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ����������������ڵ��ļ������к�
	/*!	��Դ atltrace.h������<B>ATL::CTraceFileAndLineInfo</B>������ο�MSDN<br>
		���಻�ɼ̳У�����󲻿ɸ�ֵ����<br>
		�������Ų�������ʵ�������ĺ����������ܣ��������鿴 \ref tracefileandlineinfo_example_page
	*/
	class CTraceFileAndLineInfo
	{
	public:
		/*! \brief Ψһ�Ĺ��캯�����ó�Ա����ֵ
			\param [in] pszFileName �ļ�����ansi���룩
			\param [in] nLineNo �к�
		*/
		CTraceFileAndLineInfo(LPCSTR pszFileName, int nLineNo)
			: m_pszFileName(pszFileName), m_nLineNo(nLineNo)
		{}

	public:
		/*! \brief �������Ų�������printf��ʽ���������Ϣ
			\param [in] pCategory �������
			\param [in] dwLevel ������ֵС�ڵ���pCategory->dwLevel�����������Ϣ
			\param [in] pszFmt printf��ʽ�ַ���
			\see TraceVA
		*/
		void LGN_CDECL operator()(PCTRACECATEGORY pCategory, UINT32 dwLevel, LPCSTR pszFmt, ...) const
		{
			if (dwLevel <= pCategory->dwLevel)
			{
				va_list argList;
				va_start(argList, pszFmt);
				TraceVA(pCategory, m_pszFileName, m_nLineNo, pszFmt, argList);
				va_end(argList);
			}
		}
#if (LGN_SUPPORT_UNICODE)
		//! �������Ų�������printf��ʽ���������Ϣ
		void LGN_CDECL operator()(PCTRACECATEGORY pCategory, UINT32 dwLevel, LPCWSTR pszFmt, ...) const
		{
			if (dwLevel <= pCategory->dwLevel)
			{
				va_list argList;
				va_start(argList, pszFmt);
				TraceVW(pCategory, m_pszFileName, m_nLineNo, pszFmt, argList);
				va_end(argList);
			}
		}
#endif // #if (LGN_SUPPORT_UNICODE)

		/*! \brief �������Ų���������Ĭ�ϸ������printf��ʽ���������Ϣ
			\param [in] pszFmt printf��ʽ�ַ���
			\see TraceVA
		*/
		void LGN_CDECL operator()(LPCSTR pszFmt, ...) const
		{
			va_list argList;
			va_start(argList, pszFmt);
			TraceVA(&lgnTraceGeneral, m_pszFileName, m_nLineNo, pszFmt, argList);
			va_end(argList);
		}
#if (LGN_SUPPORT_UNICODE)
		//! �������Ų�������printf��ʽ���������Ϣ
		void LGN_CDECL operator()(LPCWSTR pszFmt, ...) const
		{
			va_list argList; 
			va_start(argList, pszFmt);
			TraceVW(&lgnTraceGeneral, m_pszFileName, m_nLineNo, pszFmt, argList);
			va_end(argList);
		}
#endif // #if (LGN_SUPPORT_UNICODE)


		/*! \brief �������������Ϣ
			\param [in] pCategory �������
		*/
		void TraceHeadA(PCTRACECATEGORY pCategory) const
		{
			TraceHeadA(pCategory, m_pszFileName, m_nLineNo);
		}
#if (LGN_SUPPORT_UNICODE)
		//! �������������Ϣ
		void TraceHeadW(PCTRACECATEGORY pCategory) const
		{
			TraceHeadW(pCategory, m_pszFileName, m_nLineNo);
		}
#endif

		/*! \brief ���ʮ�����Ƹ�ʽ����
			\param [in] pCategory �������
			\param [in] pbData ���������
			\param [in] nLen ����\a pbData�ĳ���
			\note ���������������������Ϣ����Ҫ����������Ϣ���ȵ���TraceHeadA/TraceHeadW
		*/
		void TraceHex(PCTRACECATEGORY pCategory, LPCBYTE pbData, int nLen) const
		{
			CHAR szBuf[MAX_BUFF_SIZE];
			szBuf[0] = '\t';
			for (int i=0; i < nLen; )
			{		
				int nOffset=1;
				for (int j=0; (j<16) && (i<nLen) ; j++, i++)
				{
					nOffset += LGN::ChTraitsExA::FormatNP(szBuf+nOffset, MAX_BUFF_SIZE-nOffset, "%02X ", pbData[i]);
				}
				LGN::ChTraitsExA::StringCat(szBuf, LGN_BR);
				TraceOutputA(pCategory, szBuf);
			}
		}

	// static function
	public:
		/*! \brief ���������Ϣ
			\param [in] pCategory �������
			\param [in] pszFileName �ļ�����ansi���룩
			\param [in] nLine �к�
			\param [in] pszFmt printf��ʽ�ַ���
			\param [in] argList �����б�
			\see TraceHeadA
			\see TraceFormatA
		*/
		static void TraceVA(PCTRACECATEGORY pCategory, LPCSTR pszFileName, int nLine, LPCSTR pszFmt, va_list argList)
		{
			TraceHeadA(pCategory, pszFileName, nLine);
			TraceFormatA(pCategory, pszFmt, argList);
			TraceOutputA(pCategory, LGN_BR);
		}
#if (LGN_SUPPORT_UNICODE)
		//! ���������Ϣ
		static void TraceVW(PCTRACECATEGORY pCategory, LPCSTR pszFileName, int nLine, LPCWSTR pszFmt, va_list argList)
		{
			TraceHeadW(pCategory, pszFileName, nLine);
			TraceFormatW(pCategory, pszFmt, argList);
			TraceOutputW(pCategory, LGN_BR_W);
		}
#endif // #if (LGN_SUPPORT_UNICODE)

		enum { MAX_BUFF_SIZE = 1024};

		/*! \brief ���ݱ�־ֵ���������������Ϣ���ļ������к�
			\param [in] pCategory �������
			\param [in] pszFileName �ļ�����ansi���룩
			\param [in] nLine �к�
			\note ����Ҫ������ַ������Ȳ��ܳ���1024-1
		*/
		static void TraceHeadA(PCTRACECATEGORY pCategory, LPCSTR pszFileName, int nLine)
		{
			CHAR szBuf[MAX_BUFF_SIZE];
			int nLen = 0;

			if (pCategory->dwFlags & TraceFlag::CategoryNameA)
			{
				nLen += LGN::ChTraitsExA::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, "[%s]", (LPCSTR)(pCategory->pCategoryName));
			}

			if (pCategory->dwFlags & TraceFlag::CategoryNameW)
			{
				nLen += LGN::ChTraitsExA::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, "[%S]", (LPCWSTR)(pCategory->pCategoryName));
			}

			if (pCategory->dwFlags & TraceFlag::DateTime)
			{
				SYSTEMTIME t;
				LGN::API::GetLocalTime(&t);
				nLen += LGN::ChTraitsExA::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, "[%02d,%02d:%02d:%02d.%03d]", t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
			}

			if ((pCategory->dwFlags & TraceFlag::FileLineInfo) && (pszFileName != NULL))
			{
				nLen += LGN::ChTraitsExA::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, "[%s(%d)]", pszFileName, nLine);
			}

			if (pCategory->dwFlags & TraceFlag::ProcessIdTreadId)
			{
				nLen += LGN::ChTraitsExA::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, "[PID:%d][TID:%d] ", LGN::API::GetCurrentProcessId(), LGN::API::GetCurrentThreadId());
			}
			TraceOutputA(pCategory, szBuf);
		}
#if (LGN_SUPPORT_UNICODE)
		//! ���ݱ�־ֵ���������������Ϣ���ļ������к�
		static void TraceHeadW(PCTRACECATEGORY pCategory, LPCSTR pszFileName, int nLine)
		{
			WCHAR szBuf[MAX_BUFF_SIZE];
			int nLen = 0;

			szBuf[0] = L'\0';
			if (pCategory->dwFlags & TraceFlag::CategoryNameA)
			{
				nLen += LGN::ChTraitsExW::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, L"[%S]", (LPCSTR)(pCategory->pCategoryName));
			}

			if (pCategory->dwFlags & TraceFlag::CategoryNameW)
			{
				nLen += LGN::ChTraitsExW::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, L"[%s]", (LPCWSTR)(pCategory->pCategoryName));
			}

			if (pCategory->dwFlags & TraceFlag::DateTime)
			{
				SYSTEMTIME t;
				LGN::API::GetLocalTime(&t);
				nLen += LGN::ChTraitsExW::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, L"[%02d,%02d:%02d:%02d.%03d]", t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
			}

			if ((pCategory->dwFlags & TraceFlag::FileLineInfo) && (pszFileName != NULL))
			{
				nLen += LGN::ChTraitsExW::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, L"[%S(%d)]", pszFileName, nLine);
			}

			if (pCategory->dwFlags & TraceFlag::ProcessIdTreadId)
			{
				nLen += LGN::ChTraitsExW::FormatNP(szBuf + nLen, MAX_BUFF_SIZE - nLen, L"[PID:%d][TID:%d] ", LGN::API::GetCurrentProcessId(), LGN::API::GetCurrentThreadId());
			}
			TraceOutputW(pCategory, szBuf);
		}
#endif // #if (LGN_SUPPORT_UNICODE)

		/*! \brief ���ݲ����б�printf��ʽ�ַ������
			\param [in] pCategory �������
			\param [in] pszFmt printf��ʽ�ַ���
			\param [in] argList �����б�
			\note ���\a pszFmt���ȴ���1024����ֱ�����\a pszFmt��������ʽ���ַ������Ȳ��ܳ���1024-1
		*/
		static void TraceFormatA(PCTRACECATEGORY pCategory, LPCSTR pszFmt, va_list argList)
		{
			if (LGN::API::SafeStringLength(pszFmt) > MAX_BUFF_SIZE)
			{
				TraceOutputA(pCategory, pszFmt);
			}
			else
			{
				CHAR szBuf[MAX_BUFF_SIZE];
				szBuf[0] = '\0';
				LGN::ChTraitsExA::FormatN(szBuf, MAX_BUFF_SIZE, pszFmt, argList);
				TraceOutputA(pCategory, szBuf);
			}
		}
#if (LGN_SUPPORT_UNICODE)
		//! ���ݲ����б�printf��ʽ�ַ������
		static void TraceFormatW(PCTRACECATEGORY pCategory, LPCWSTR pszFmt, va_list argList)
		{
			if (LGN::API::SafeStringLength(pszFmt) > MAX_BUFF_SIZE)
			{
				TraceOutputW(pCategory, pszFmt);
			}
			else
			{
				WCHAR szBuf[MAX_BUFF_SIZE];
  				szBuf[0] = L'\0';
				LGN::ChTraitsExW::FormatN(szBuf, MAX_BUFF_SIZE, pszFmt, argList);
				TraceOutputW(pCategory, szBuf);
			}
		}
#endif // #if (LGN_SUPPORT_UNICODE)

		/*! \brief ֱ������ַ�������������
			\param [in] pCategory �������
			\param [in] pszMessage ��������ַ���
		*/
		static void TraceOutputA(PCTRACECATEGORY pCategory, LPCSTR pszMessage)
		{
			if (pCategory->dwFlags & TraceFlag::OutputFileA)
			{
				LGN::FileTraitsTraceA::Append((LPCSTR)(pCategory->pOutputFileName), pszMessage, LGN::API::SafeStringLength(pszMessage));
			}
			else
			{
				LGN::ChTraitsExA::SOutputDebugString(pszMessage);
			}
		}
#if (LGN_SUPPORT_UNICODE)
		//! ֱ������ַ�������������
		static void TraceOutputW(PCTRACECATEGORY pCategory, LPCWSTR pszMessage)
		{
			if (pCategory->dwFlags & TraceFlag::OutputFileA)
			{
				CHAR szBuf[MAX_BUFF_SIZE];
				szBuf[0] = '\0';
				LGN::ChTraitsExA::FormatNP(szBuf, MAX_BUFF_SIZE, "%S", pszMessage);
				TraceOutputA(pCategory, szBuf);
			}
			else
			{
				LGN::ChTraitsExW::SOutputDebugString(pszMessage);
			}
		}
#endif // #if (LGN_SUPPORT_UNICODE)

	private:
		const char *const m_pszFileName; //!< �ļ�����ansi���룩
		const int m_nLineNo; //!< �к�

		CTraceFileAndLineInfo(const CTraceFileAndLineInfo &other); //!< ���಻�ɼ̳�
		CTraceFileAndLineInfo operator=(const CTraceFileAndLineInfo &other); //!< ������󲻿ɸ�ֵ����
	};

/*! \page tracefileandlineinfo_example_page CTraceFileAndLineInfo����
<pre>	%CTraceFileAndLineInfo���ʹ������</pre>
<pre>
\#include "lgnbase.h"

	// �޸�Ĭ�ϸ������ı�־��������ӣ�������ǰ����Id���߳�Id��������ǰʱ��
	LGN_TRACE_CATEGORY_DEF->dwFlags |= LGN::TraceFlag::ProcessIdTreadId | LGN::TraceFlag::DateTime;

	// ʮ���������
	LGN::CTraceFileAndLineInfo trace(__FILE__, __LINE__);
	trace(LGN_TRACE_CATEGORY_DEF, LGN::TraceLevel::Error , "hex data:");
	trace.TraceHex(LGN_TRACE_CATEGORY_DEF, (LPCBYTE)"1234678901234567890", 20);

	// printf��ʽ���
	LGN::CTraceFileAndLineInfo(__FILE__, __LINE__)(LGN_TRACE_CATEGORY_DEF, LGN::TraceLevel::Error, "errno = %x\n", -1);

	// 
	// 
	// ������ݸ�ʽ���£�
	// [TraceGeneral][\<Time\>][\<FileName\>(\<LineId\>)][PID:\<pid\>][TID:\<tid\>] hex data:	31 32 33 34 36 37 38 39 30 31 32 33 34 35 36 37 
	// 	38 39 30 00 
	// [TraceGeneral][\<Time\>][\<FileName\>(\<LineId\>)][PID:\<pid\>][TID:\<tid\>] errno = ffffffff
</pre>
*/


////////////////////////////////////////////////////////////////////////////////////////////////////

	//! �������������CTraceFileAndLineInfo
	/*!	��Դ atltrace.h������<B>ATL::CTrace</B>������ο�MSDN<br>
		���಻�ɼ̳У�����󲻿ɸ�ֵ����<br>
		�������Ų�������ʵ�������ĺ����������ܣ��������鿴 \ref trace_example_page
	*/
	class CTrace
	{
	public:
		/*! \brief Ψһ�Ĺ��캯�����ó�Ա����ֵ
			\param [in] pszFileName �ļ�����ansi���룩
			\param [in] nLineNo �к�
			\param [in] pTraceCatecory �������
		*/
		CTrace(LPCSTR pszFileName, int nLineNo, PCTRACECATEGORY pTraceCatecory = NULL)
			:m_trace(pszFileName, nLineNo)
		{
			m_pTraceCatecory = (pTraceCatecory != NULL)? pTraceCatecory : &lgnTraceGeneral;
			m_dwLevel = 0;
			m_dwErrorNo = 0;
			m_pszFuncNameA = NULL;
			m_pszFuncNameW = NULL;
		}

		//! \brief �鹹��������������ٵĺ������ƣ��ο�Entry����Ч��������亯�����ý����ĸ�����Ϣ
		~CTrace()
		{
			if (m_pszFuncNameA != NULL)
			{
				if (m_dwErrorNo == 0)
					m_trace(m_pTraceCatecory, m_dwLevel, "<Function %s Leave> OK" LGN_BR LGN_BR, m_pszFuncNameA);
				else
					m_trace(m_pTraceCatecory, m_dwLevel, "<Function %s Leave> Error!!!=0x%0x(%d)" LGN_BR LGN_BR, m_pszFuncNameA, m_dwErrorNo, m_dwErrorNo);
			}
#if (LGN_SUPPORT_UNICODE)
			if (m_pszFuncNameW != NULL)
			{
				if (m_dwErrorNo == 0)
					m_trace(m_pTraceCatecory, m_dwLevel, L"<Function %s Leave> OK" LGN_BR_W LGN_BR_W, m_pszFuncNameW);
				else
					m_trace(m_pTraceCatecory, m_dwLevel, L"<Function %s Leave> Error!!!=0x%0x(%d)" LGN_BR_W LGN_BR_W, m_pszFuncNameW, m_dwErrorNo, m_dwErrorNo);
			}
#endif
		}

		/*! \brief �ó�Ա����ֵ-����ţ����鹹�������õ�
			\param [in] dwErrorNo �����
		*/
		void SetErrorNo(UINT32 dwErrorNo)
		{
			m_dwErrorNo = dwErrorNo;
		}

		/*! \brief ��������ٵĺ������ÿ�ʼ�ĸ�����Ϣ
			\param [in] dwLevel ������ֵС�ڵ���pCategory->dwLevel�����������Ϣ
			\param [in] pszFuncName �����ٵĺ������ƣ�����ΪNULL
		*/
		void Entry(UINT32 dwLevel, LPCSTR pszFuncName)
		{
			m_dwLevel = dwLevel;
			m_pszFuncNameA = pszFuncName;
			if (m_pszFuncNameA != NULL)
				m_trace(m_pTraceCatecory, m_dwLevel, "<Function %s Entry>" LGN_BR, m_pszFuncNameA);
		}
#if (LGN_SUPPORT_UNICODE)
		//! ��������ٵĺ������ÿ�ʼ�ĸ�����Ϣ
		void Entry(UINT32 dwLevel, LPCWSTR pszFuncName)
		{
			m_dwLevel = dwLevel;
			m_pszFuncNameW = pszFuncName;
			if (m_pszFuncNameW != NULL)
				m_trace(m_pTraceCatecory, m_dwLevel, L"<Function %s Entry>" LGN_BR_W, m_pszFuncNameW);
		}
#endif

		/*! \brief �������Ų�������printf��ʽ���������Ϣ
			\param [in] pszFmt printf��ʽ�ַ���
		*/
		void LGN_CDECL operator()(LPCSTR pszFmt, ...) const
		{
			if (m_dwLevel <= m_pTraceCatecory->dwLevel)
			{
				va_list argList;
				va_start(argList, pszFmt);
				m_trace.TraceHeadA(m_pTraceCatecory);
				m_trace.TraceFormatA(m_pTraceCatecory, pszFmt, argList);
				m_trace.TraceOutputA(m_pTraceCatecory, LGN_BR);
				va_end(argList);
			}
		}
		/*! \brief �������Ų�������printf��ʽ���������Ϣ
			\param [in] dwLevel ������ֵС�ڵ��ڸ�������dwLevel�����������Ϣ
			\param [in] pszFmt printf��ʽ�ַ���
		*/
		void LGN_CDECL operator()(UINT32 dwLevel, LPCSTR pszFmt, ...) const
		{
			if (dwLevel <= m_pTraceCatecory->dwLevel)
			{
				va_list argList;
				va_start(argList, pszFmt);
				m_trace.TraceHeadA(m_pTraceCatecory);
				m_trace.TraceFormatA(m_pTraceCatecory, pszFmt, argList);
				m_trace.TraceOutputA(m_pTraceCatecory, LGN_BR);
				va_end(argList);
			}
		}
#if (LGN_SUPPORT_UNICODE)
		//! �������Ų�������printf��ʽ���������Ϣ
		void LGN_CDECL operator()(LPCWSTR pszFmt, ...) const
		{
			if (m_dwLevel <= m_pTraceCatecory->dwLevel)
			{
				va_list argList;
				va_start(argList, pszFmt);
				m_trace.TraceHeadW(m_pTraceCatecory);
				m_trace.TraceFormatW(m_pTraceCatecory, pszFmt, argList);
				m_trace.TraceOutputW(m_pTraceCatecory, LGN_BR_W);
				va_end(argList);
			}
		}
		//! �������Ų�������printf��ʽ���������Ϣ
		void LGN_CDECL operator()(UINT32 dwLevel, LPCWSTR pszFmt, ...) const
		{
			if (dwLevel <= m_pTraceCatecory->dwLevel)
			{
				va_list argList;
				va_start(argList, pszFmt);
				m_trace.TraceHeadW(m_pTraceCatecory);
				m_trace.TraceFormatW(m_pTraceCatecory, pszFmt, argList);
				m_trace.TraceOutputW(m_pTraceCatecory, LGN_BR_W);
				va_end(argList);
			}
		}
#endif // #if (LGN_SUPPORT_UNICODE)

		/*! \brief �����Ϣͷ��Ϣ��ʮ�����Ƹ�ʽ����
			\param [in] pszMsg ��Ϣ����
			\param [in] pData ���������
			\param [in] nLen ����\a pbData�ĳ���
		*/
		LGN_INLINE void WriteHex(LPCSTR pszMsg, LPCVOID pData, int nLen) const
		{
			WriteHex(m_dwLevel, pszMsg, pData, nLen);
		}
		/*! \brief �����Ϣͷ��Ϣ��ʮ�����Ƹ�ʽ����
			\param [in] dwLevel ������ֵС�ڵ��ڸ�������dwLevel�����������Ϣ
			\param [in] pszMsg ��Ϣ����
			\param [in] pData ���������
			\param [in] nLen ����\a pbData�ĳ���
		*/
		void WriteHex(UINT32 dwLevel, LPCSTR pszMsg, LPCVOID pData, int nLen) const
		{
			if (dwLevel <= m_pTraceCatecory->dwLevel)
			{
				m_trace(m_pTraceCatecory, dwLevel, "%s(0x%08X):%s", pszMsg, nLen, (nLen>0 && nLen<=16)?  "" : LGN_BR);
				m_trace.TraceHex(m_pTraceCatecory, (LPCBYTE)pData, nLen);
			}
		}
#if (LGN_SUPPORT_UNICODE)
		//! �����Ϣͷ��Ϣ��ʮ�����Ƹ�ʽ����
		LGN_INLINE void WriteHex(LPCWSTR pszMsg, LPCVOID pData, int nLen) const
		{
			WriteHex(m_dwLevel, pszMsg, pData, nLen);
		}
		//! �����Ϣͷ��Ϣ��ʮ�����Ƹ�ʽ����
		void WriteHex(UINT32 dwLevel, LPCWSTR pszMsg, LPCVOID pData, int nLen) const
		{
			if (dwLevel <= m_pTraceCatecory->dwLevel)
			{
				m_trace(m_pTraceCatecory, dwLevel, L"%s(0x%X):%s", pszMsg, nLen, (nLen>16)? LGN_BR_W : L"");
				m_trace.TraceHex(m_pTraceCatecory, (LPCBYTE)pData, nLen);
			}
		}
#endif // #if (LGN_SUPPORT_UNICODE)

	protected:
		CTraceFileAndLineInfo m_trace; //!< �����
		PCTRACECATEGORY m_pTraceCatecory; //!< �������ָ�룬����ֻ����ָ�룬�����߱�֤����󲻱��ͷ�
		UINT32 m_dwLevel; //!< �������ļ���
		UINT32 m_dwErrorNo; //!< �����
		LPCSTR m_pszFuncNameA; //!< �������ƣ�ansi���룩
		LPCWSTR m_pszFuncNameW; //!< �������ƣ�unicode���룩
	
	private:
		CTrace(const CTrace &other); //!< ���಻�ɼ̳�
		CTrace operator=(const CTrace &other); //!< ������󲻿ɸ�ֵ����
	};

/*! \page trace_example_page CTrace����
<pre>	%CTrace���ʹ������</pre>
<pre>
\#include "lgnbase.h"

	void func()
	{
		LGN::CTrace trace(NULL, 0);
		trace.Entry(LGN::TraceLevel::Error, "func");
		trace("---%s---", "test");
		trace.WriteHex("hex data", (LPCBYTE)"1234678901234567890", 20);
		trace.SetErrorNo(-1);
	}

	// ...
	func();

	// 
	// 
	// ������ݸ�ʽ���£�
	// [TraceGeneral]\<Function func Entry\>
	// [TraceGeneral]---test---
	// [TraceGeneral]hex data(0x00000014):
	//         31 32 33 34 36 37 38 39 30 31 32 33 34 35 36 37
	//         38 39 30 00
	// [TraceGeneral]\<Function func Leave\> Error!!!=0xffffffff(-1)
</pre>
*/


////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef LGN_TRACE_CATEGORY_DEF
#define LGN_TRACE_CATEGORY_DEF (&LGN::lgnTraceGeneral) //!< Ĭ�ϵĸ���������
#endif
#define LGNTRACE LGN::CTraceFileAndLineInfo(__FILE__, __LINE__) //!< ����ǰ�ļ������кŵĸ��������
#define LGNTRACE_ENTRY(cate, level, func) LGN::CTrace _trace(NULL, 0, cate); _trace.Entry(level, func) //!< ����ǰ�������Ƶĸ��������
#define LGNTRACE_MSG _trace //!< ��������ַ���������Ϣ
#define LGNTRACE_HEX(msg, data, len) _trace.WriteHex(msg, data, len) //!< �������ʮ�����Ƶĵ�����Ϣ
#define LGNTRACE_HEX_LV(level, msg, data, len) _trace.WriteHex(level, msg, data, len) //!< �������ʮ�����Ƶĵ�����Ϣ����ָ������
#define LGNTRACE_ERRORNO(err) _trace.SetErrorNo((UINT32)err); //!< ���ø��������Ĵ����

#else // !LGN_SUPPORT_TRACE
#define LGN_TRACE_CATEGORY_DEF 0
#define LGNTRACE LGN_NOOP
#define LGNTRACE_ENTRY(cate, level, func) LGN_NOOP
#define LGNTRACE_MSG LGN_NOOP
#define LGNTRACE_HEX(msg, data, len) LGN_NOOP
#define LGNTRACE_HEX_LV(level, msg, data, len) LGN_NOOP
#define LGNTRACE_ERRORNO(err) LGN_NOOP
#endif


/*! \page tracemacro_example_page �����������
<pre> ʹ�ø��ٺ������</pre>
<pre>
\#include "lgnbase.h"

	LGN::CTraceCategory lgnTraceTest(LGN::TraceFlag::DateTime|LGN::TraceFlag::ProcessIdTreadId, LGN::TraceLevel::Notice, "TEST", NULL);

	void func()
	{
		LGNTRACE_ENTRY(&lgnTraceTest, LGN::TraceLevel::Notice, "func");
		LGNTRACE_HEX("hex data", (LPCBYTE)"1234678901234567890", 20);
		LGNTRACE_ERRORNO(-1);
	}

	// ...
	LGNTRACE(&lgnTraceTest, LGN::TraceLevel::Error , "lgnTraceTest messageid = %d\n", 1);
	func();
	LGNTRACE("defaultTrace messageid = %d\n", 2);

	// 
	// 
	// ������ݸ�ʽ���£�
	// [TEST][02,17:50:50.906][PID:1588][TID:2948] lgnTraceTest messageid = 1
	// [TEST][02,17:50:50.906][PID:1588][TID:2948] \<Function func Entry\>
	// [TEST][02,17:50:50.906][PID:1588][TID:2948] hex data(0x00000014):
	// 	31 32 33 34 36 37 38 39 30 31 32 33 34 35 36 37 
	// 	38 39 30 00 
	// [TEST][02,17:50:50.906][PID:1588][TID:2948] \<Function func Leave\> Error!!!=0xffffffff(-1)

	// [TraceGeneral][e:\\ljc\\card_n\\tcard\\tcard.cpp(94)]defaultTrace messageid = 2

</pre>
*/

}; // namespace LGN

#endif
