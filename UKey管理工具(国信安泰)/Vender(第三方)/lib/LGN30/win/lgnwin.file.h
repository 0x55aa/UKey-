/*! \file lgnwin.file.h 
*  \brief WINϵͳ���ļ���������
*
*  ����Ҫ�������ļ��������ļ���lgnbase.h
*
*  �����ļ�������CFile����ʱ�ļ�����ģ����CTemporaryFileT���ļ�ӳ�����ģ����CFileMappingT
*  
*  \author ljc
*  \version 3.0.0
*  \date    2010-2012
*  \bug
*  \warning
*/

#ifndef __LGNWIN_FILE_H__
#define __LGNWIN_FILE_H__


#ifndef __LGN_BASE_H__
#error lgnwin.file.h requires include lgnbase.h
#endif


namespace LGN
{
////////////////////////////////////////////////////////////////////////////////////////////////////

	//! �ļ�������
	/*! ����ϵͳAPIʵ���ļ��򿪼���д���ܣ���Դatlfile.h����ͬ<B>ATL::CAtlFile</B>������ο�MSDN �� 
		-# �������鿴 \ref file_example_page
	*/
	class CFile : public CHandle
	{
	public:
		//! �ṩ��ʾ���еĲο����Թ����в��ҵ��ֶ�
		enum SeekOrigin {
			Begin = FILE_BEGIN, //!< ָ�����Ŀ�ͷ
			Current = FILE_CURRENT, //!< ָ�����ڵĵ�ǰλ��
			End = FILE_END //!< ָ�����Ľ�β
		};

		//! �ṩ��ʾ�ļ�����Ȩ��
		enum DesiredAccess {
			accessRead =		GENERIC_READ, //!< ��Ȩ��
			accessWrite =		GENERIC_WRITE, //!< дȨ��
			accessReadWrite =	GENERIC_READ | GENERIC_WRITE, //!< ��дȨ��
		};

		//! �ṩ��ʾ�ļ�����ģʽ
		enum ShareMode {
			shareRead =			FILE_SHARE_READ, //!< �����ģʽ
			shareWrite =		FILE_SHARE_WRITE, //!< ����дģʽ
			shareReadWrite =    FILE_SHARE_READ | FILE_SHARE_WRITE, //!< �����дģʽ
		};

		//! �ṩ��ʾ�ļ�������ʽ
		enum CreationDisposition {
			createAlways =		CREATE_ALWAYS, //!< ���Ǵ����ļ� 
			openExisting =		OPEN_EXISTING, //!< ���Ѿ����ڵ��ļ� 
			openAlways =		OPEN_ALWAYS, //!< ���ļ�������������򴴽�
		};

		//! �ṩ��ʾ�ļ�����
		enum FileAttributes {
			attributeNormal =		FILE_ATTRIBUTE_NORMAL,
		};

	public:
		//! ���캯��
		CFile()
		{
		}
		//! ���캯�����ⲿ�����ļ�����
		CFile( CFile & file ) : CHandle( file )  // Transfers ownership
		{
		}
		//! ���캯�����ⲿ�����ļ����
		explicit CFile( HANDLE hFile ) : CHandle( hFile )  // Takes ownership
		{
		}

		/*! \brief ��/�����ļ�
			\param[in] pszFileName ANSI������ļ���
			\param[in] dwDesiredAccess �����ļ��Ŀ���Ȩ��DesiredAccess
			\param[in] dwShareMode �ļ�����ģʽShareMode
			\param[in] dwCreationDisposition �ļ�������ʽCreationDisposition
			\param[in] dwFlagsAndAttributes = attributeNormal ��־���ļ�����FileAttributes
			\param[in] lpsa = NULL ��ȫ������
			\param[in] hTemplateFile = NULL һ��ģ���ļ����
			\return HRESULT
		*/
		HRESULT Create(LPCSTR pszFileName, UINT32 dwDesiredAccess, UINT32 dwShareMode, UINT32 dwCreationDisposition, UINT32 dwFlagsAndAttributes = CFile::attributeNormal, LPSECURITY_ATTRIBUTES lpsa = NULL, HANDLE hTemplateFile = NULL)
		{
			HANDLE hFile = ::CreateFileA(pszFileName, dwDesiredAccess, dwShareMode, lpsa, dwCreationDisposition,	dwFlagsAndAttributes,hTemplateFile);
			if (hFile == INVALID_HANDLE_VALUE)
				return API::HResultFromError( ::GetLastError() );

			CHandle::Attach(hFile);
			return S_OK;
		}
		/*! \brief ��/�����ļ�
			\param[in] pszFileName UNICODE������ļ���
			\param[in] dwDesiredAccess �����ļ��Ŀ���Ȩ��#DesiredAccess
			\param[in] dwShareMode �ļ�����ģʽ#ShareMode
			\param[in] dwCreationDisposition �ļ�������ʽ#CreationDisposition
			\param[in] dwFlagsAndAttributes = attributeNormal ��־���ļ�����#FileAttributes
			\param[in] lpsa = NULL ��ȫ������
			\param[in] hTemplateFile = NULL һ��ģ���ļ����
			\return HRESULT
		*/
		HRESULT Create(LPCWSTR pszFileName, UINT32 dwDesiredAccess, UINT32 dwShareMode, UINT32 dwCreationDisposition, UINT32 dwFlagsAndAttributes = CFile::attributeNormal, LPSECURITY_ATTRIBUTES lpsa = NULL, HANDLE hTemplateFile = NULL)
		{
			HANDLE hFile = ::CreateFileW(pszFileName, dwDesiredAccess, dwShareMode, lpsa, dwCreationDisposition,	dwFlagsAndAttributes,hTemplateFile);
			if (hFile == INVALID_HANDLE_VALUE)
				return API::HResultFromError( ::GetLastError() );

			CHandle::Attach(hFile);
			return S_OK;
		}

		/*! \brief ���ļ���ȡָ�����ȵ�����
			\param[out] pBuffer ����������Ŷ��������ݣ�
			\param[in] nBufSize ָ�����ȣ����������ȣ�
			\return HRESULT
		*/
		HRESULT Read(LPVOID pBuffer, UINT32 nBufSize)
		{
			DWORD nBytesRead = 0;
			if (!::ReadFile(m_h, pBuffer, nBufSize, &nBytesRead, NULL) )
				return API::HResultFromError( ::GetLastError() );
			if (nBytesRead != nBufSize)
				return API::HResultFromError( ERROR_HANDLE_EOF );

			return S_OK;
		}

		/*! \brief ���ļ���ȡ����
			\param[out] pBuffer ����������Ŷ��������ݣ�
			\param[in] nBufSize ����������
			\param[out] nBytesRead �����ĳ���
			\return HRESULT
		*/
		HRESULT Read(LPVOID pBuffer, UINT32 nBufSize,UINT32& nBytesRead)
		{
			if (!::ReadFile(m_h, pBuffer, nBufSize, (LPDWORD)&nBytesRead, NULL))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief �첽��ʽ���ļ���ȡ����			
			\param[out] pBuffer ����������Ŷ��������ݣ�
			\param[in] nBufSize ����������
			\param[in] pOverlapped �첽���ص����Ľṹָ�롣
			\return HRESULT
			\note �������ͨ���᷵��API::HResultFromError��ERROR_IO_PENDING��������GetOverlappedResult��ɲ�����Ҫʹ���첽��д�������ļ���������FILE_FLAG_OVERLAPPED��־��
		*/
		HRESULT Read(LPVOID pBuffer, UINT32 nBufSize, LPOVERLAPPED pOverlapped)
		{
			if (!::ReadFile(m_h, pBuffer, nBufSize, NULL, pOverlapped))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief ������̷�ʽ���ļ���ȡ����			
			\param[out] pBuffer ����������Ŷ��������ݣ�
			\param[in] nBufSize ����������
			\param[in] pOverlapped �첽���ص����Ľṹָ�롣
			\param[in] pfnCompletionRoutine ������̵Ľṹָ�롣
			\return HRESULT
		*/		
		HRESULT Read(LPVOID pBuffer, UINT32 nBufSize, LPOVERLAPPED pOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE pfnCompletionRoutine)
		{
			if (!::ReadFileEx(m_h, pBuffer, nBufSize, pOverlapped, pfnCompletionRoutine))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief ���ļ�д������
			\param[out] pBuffer ����������Ŵ�д�����ݣ�
			\param[in] nBufSize ��д�����ݳ���
			\param[out] pnBytesWritten = NULL д�ɹ��ĳ���
			\return HRESULT
		*/
		HRESULT Write(LPCVOID pBuffer, UINT32 nBufSize, LPUINT32 pnBytesWritten = NULL)
		{
			DWORD nBytesWritten = 0;
			if (pnBytesWritten == NULL)
				pnBytesWritten = (LPUINT32)&nBytesWritten;
			if (!::WriteFile(m_h, pBuffer, nBufSize, (LPDWORD)pnBytesWritten, NULL))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief �첽��ʽ���ļ�д������	
			\param[in] pBuffer ����������Ŵ�д�����ݣ�
			\param[in] nBufSize ����������
			\param[in] pOverlapped �첽���ص����Ľṹָ�롣
			\return HRESULT
			\note �������ͨ���᷵��API::HResultFromError��ERROR_IO_PENDING��������GetOverlappedResult��ɲ�����Ҫʹ���첽��д�������ļ���������FILE_FLAG_OVERLAPPED��־��
		*/
		HRESULT Write(LPCVOID pBuffer, UINT32 nBufSize, LPOVERLAPPED pOverlapped)
		{
			if (!::WriteFile(m_h, pBuffer, nBufSize, NULL, pOverlapped))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief ������̷�ʽ���ļ�д������	
			\param[in] pBuffer ����������Ŵ�д�����ݣ�
			\param[in] nBufSize ����������
			\param[in] pOverlapped �첽���ص����Ľṹָ�롣
			\param[in] pfnCompletionRoutine ������̵Ľṹָ�롣
			\return HRESULT
		*/
		HRESULT Write(LPCVOID pBuffer, UINT32 nBufSize, LPOVERLAPPED pOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE pfnCompletionRoutine)
		{
			if (!::WriteFileEx(m_h, pBuffer, nBufSize, pOverlapped, pfnCompletionRoutine))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief ����ָ�����ļ�һ���ص������Ľ��
			\param[in] pOverlapped �첽���ص����Ľṹָ�롣
			\param[out] dwBytesTransferred ���ո�ʵ�����Ƕ���д����������ֽ���
			\param[in] bWait ����˲���Ϊtrue�����������أ�ֱ����������ɡ�����������Ϊfalse��������δ��ɣ��ú�������API::HResultFromError(ERROR_IO_INCOMPLETE)
			\return HRESULT
		*/
		HRESULT GetOverlappedResult(LPOVERLAPPED pOverlapped, UINT32& dwBytesTransferred, bool bWait)
		{
			if (!::GetOverlappedResult(m_h, pOverlapped, (LPDWORD)&dwBytesTransferred, bWait))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief �����ļ����е�λ��
			\param[in] nOffset ƫ����
			\param[in] dwFrom �ļ����еĲο���#SeekOrigin
			\return HRESULT
		*/
		HRESULT Seek(INT64 nOffset, UINT32 dwFrom = CFile::Current)
		{
			LGNASSERT(dwFrom == CFile::Begin || dwFrom == CFile::End || dwFrom == CFile::Current);

			LARGE_INTEGER liOffset;
			liOffset.QuadPart = nOffset;
			DWORD nNewPos = ::SetFilePointer(m_h, liOffset.LowPart, &liOffset.HighPart, dwFrom);
			if (nNewPos == INVALID_SET_FILE_POINTER)
			{
				HRESULT hr = API::HResultFromError( ::GetLastError() );
				if (FAILED(hr))
					return hr;
			}

			return S_OK;
		}

		/*! \brief ��ȡ�ļ����е�λ��
			\param[out] nPos �ļ����е�λ��
			\return HRESULT
		*/
		HRESULT GetPosition(UINT64& nPos) const
		{
			LARGE_INTEGER liOffset;
			liOffset.QuadPart = 0;
			liOffset.LowPart = ::SetFilePointer(m_h, 0, &liOffset.HighPart, CFile::Current);
			if (liOffset.LowPart == INVALID_SET_FILE_POINTER)
			{
				HRESULT hr = API::HResultFromError( ::GetLastError() );
				if (FAILED(hr))
					return hr;
			}
			nPos = liOffset.QuadPart;

			return S_OK;
		}

		/*! \brief �ѻ�������ˢ���ļ�ʵ����
			\return HRESULT
		*/
		HRESULT Flush()
		{
			if (!::FlushFileBuffers(m_h))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		
		/*! \brief �����ɵ��ý��̶�ռ����ָ�����ļ���
			\param[in] nPos Ҫ�����ļ�λ�õ���ʼ�ֽ�ƫ����
			\param[in] nCount Ҫ�������ֽڳ���
			\return RESULT
		*/
		HRESULT LockRange(UINT64 nPos, UINT64 nCount)
		{
			LARGE_INTEGER liPos;
			liPos.QuadPart = nPos;

			LARGE_INTEGER liCount;
			liCount.QuadPart = nCount;

			if (!::LockFile(m_h, liPos.LowPart, liPos.HighPart, liCount.LowPart, liCount.HighPart))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief �����ɵ��ý��̶�ռ����ָ�����ļ���
			\param[in] nPos Ҫ�����ļ�λ�õ���ʼ�ֽ�ƫ����
			\param[in] nCount Ҫ�������ֽڳ���
			\return RESULT
		*/
		HRESULT UnlockRange(UINT64 nPos, UINT64 nCount)
		{
			LARGE_INTEGER liPos;
			liPos.QuadPart = nPos;

			LARGE_INTEGER liCount;
			liCount.QuadPart = nCount;

			if (!::UnlockFile(m_h, liPos.LowPart, liPos.HighPart, liCount.LowPart, liCount.HighPart))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief �����ļ���С
			\param[in] nNewLen �ļ���С
			\return RESULT
		*/
		HRESULT SetSize(UINT64 nNewLen)
		{
			HRESULT hr = Seek(nNewLen, CFile::Begin);
			if (FAILED(hr))
				return hr;

			if (!::SetEndOfFile(m_h))
				return API::HResultFromError( ::GetLastError() );

			return S_OK;
		}

		/*! \brief ��ȡ�ļ���С
			\param[out] nLen �ļ���С
			\return RESULT
		*/
		HRESULT GetSize(UINT64& nLen) const
		{
			ULARGE_INTEGER liFileSize;
			liFileSize.LowPart = ::GetFileSize(m_h, &liFileSize.HighPart);
			if (liFileSize.LowPart == INVALID_FILE_SIZE)
			{
				HRESULT hr = API::HResultFromError( ::GetLastError() );
				if (FAILED(hr))
					return hr;
			}

			nLen = liFileSize.QuadPart;

			return S_OK;
		}
	};

/*! \page file_example_page CFile����
<pre>	%CFile���ʹ������</pre>
<pre>
\#include "lgnbase.h"
\#include "lgnfile.h"

	// ...
	static bool GetAllData(LPCTSTR pszFileName, LGN::CByteBuffer & buff)
	{
		bool bRet = false;
		LGN::CFile file;
		if (SUCCEEDED(file.Create(pszFileName, LGN::CFile::accessRead, LGN::CFile::shareRead, LGN::CFile::openExisting)))
		{
			UINT64 nFileSize = 0;
			file.GetSize(nFileSize);
			bRet = SUCCEEDED(file.Read(buff.GetBufferSetLength((int)nFileSize), (int)nFileSize));
			file.Close();
		}
		return bRet;
	}
</pre>
*/


////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ��ʱ�ļ�����ģ�徲̬��
	template< typename _BaseType = CHAR>
	class TemporaryFileTraits
	{
	public:
		static HRESULT GenerateFileName(LPCSTR pszDir, LPSTR pszTempFileName)
		{
			CHAR szPath[MAX_PATH]; 
			CHAR tmpFileName[MAX_PATH]; 

			if (pszDir == NULL)
			{
				DWORD dwRet = ::GetTempPathA(MAX_PATH, szPath);
				if (dwRet == 0)
				{
					// Couldn't find temporary path;
					return API::HResultFromError(::GetLastError());
				}
				else if (dwRet > MAX_PATH)
				{
					return DISP_E_BUFFERTOOSMALL;
				}
			}
			else
			{
				::lstrcpynA(szPath, pszDir, MAX_PATH);
			}

			if (!::GetTempFileNameA(szPath, "TFR", 0, tmpFileName))
			{
				// Couldn't create temporary filename;
				return API::HResultFromError(::GetLastError());
			}
			tmpFileName[MAX_PATH-1]='\0';

			::lstrcpynA(pszTempFileName, tmpFileName, MAX_PATH);
			return S_OK;
		}

		static HRESULT DeleteOrMoveFile(LPCSTR szNewName, LPCSTR pszTempFileName)
		{
			// no new name so delete it
			if (szNewName == NULL)
			{
				::DeleteFileA(pszTempFileName);
				return S_OK;
			}

			// delete any existing file and move our temp file into it's place
			if (!::DeleteFileA(szNewName))
			{
				DWORD dwError = ::GetLastError();
				if (dwError != ERROR_FILE_NOT_FOUND)
					return API::HResultFromError(dwError);
			}

			if (!::MoveFileA(pszTempFileName, szNewName))
				return API::HResultFromError(::GetLastError());

			return S_OK;
		}
	};

	//! ��ʱ�ļ�����ģ�徲̬��
	template< >
	class TemporaryFileTraits< WCHAR >
	{
	public:
		static HRESULT GenerateFileName(LPCWSTR pszDir, LPWSTR pszTempFileName)
		{
			WCHAR szPath[MAX_PATH]; 
			WCHAR tmpFileName[MAX_PATH]; 

			if (pszDir == NULL)
			{
				DWORD dwRet = ::GetTempPathW(MAX_PATH, szPath);
				if (dwRet == 0)
				{
					// Couldn't find temporary path;
					return API::HResultFromError(::GetLastError());
				}
				else if (dwRet > MAX_PATH)
				{
					return DISP_E_BUFFERTOOSMALL;
				}
			}
			else
			{
				::lstrcpynW(szPath, pszDir, MAX_PATH);
			}

			if (!::GetTempFileNameW(szPath, L"TFR", 0, tmpFileName))
			{
				// Couldn't create temporary filename;
				return API::HResultFromError(::GetLastError());
			}
			tmpFileName[MAX_PATH-1]='\0';

			::lstrcpynW(pszTempFileName, tmpFileName, MAX_PATH);
			return S_OK;
		}

		static HRESULT DeleteOrMoveFile(LPCWSTR szNewName, LPCWSTR pszTempFileName)
		{
			// no new name so delete it
			if (szNewName == NULL)
			{
				::DeleteFileW(pszTempFileName);
				return S_OK;
			}

			// delete any existing file and move our temp file into it's place
			if (!::DeleteFileW(szNewName))
			{
				DWORD dwError = ::GetLastError();
				if (dwError != ERROR_FILE_NOT_FOUND)
					return API::HResultFromError(dwError);
			}

			if (!::MoveFileW(pszTempFileName, szNewName))
				return API::HResultFromError(::GetLastError());

			return S_OK;
		}
	};

	//! ��ʱ�ļ�����ģ����
	/*! ����CFileʵ����ʱ�ļ���������д���ܣ���Դatlfile.h����ͬ<B>ATL::CAtlTemporaryFile</B>������ο�MSDN �� 
		-# �������鿴 \ref temporaryfile_example_page
	*/
	// This class allows the creation of a temporary file that is written to.
	// When the entire file has been successfully written it will be closed and given
	// it's proper file name if required.
	template< typename BaseType >
	class CTemporaryFileT
	{
	public:
		CTemporaryFileT()
		{
		}

		~CTemporaryFileT()
		{
			// Ensure that the temporary file is closed and deleted,
			// if necessary.
			if (m_file.m_h != NULL)
			{
				Close();
			}
		}
		
		HRESULT Create(const BaseType * pszDir = NULL, UINT32 dwDesiredAccess = GENERIC_WRITE)
		{
			HRESULT hr = TemporaryFileTraits< BaseType >::GenerateFileName(pszDir, m_szTempFileName);
			if (FAILED(hr))
				return hr;

			m_dwAccess = dwDesiredAccess;

			SECURITY_ATTRIBUTES secatt;
			secatt.nLength = sizeof(secatt);
			secatt.lpSecurityDescriptor = NULL;
			secatt.bInheritHandle = TRUE;

			return m_file.Create(
				m_szTempFileName,
				m_dwAccess,
				0,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NOT_CONTENT_INDEXED | FILE_ATTRIBUTE_TEMPORARY,
				&secatt);
		}

		HRESULT Close(const BaseType * szNewName = NULL)
		{
			// This routine is called when we are finished writing to the 
			// temporary file, so we now just want to close it and copy
			// it to the actual filename we want it to be called.

			// So let's close it first.
			m_file.Close();
			
			return TemporaryFileTraits< BaseType >::DeleteOrMoveFile(szNewName, m_szTempFileName);
		}

		HRESULT HandsOff()
		{
			m_file.Flush();
			m_file.Close();

			return S_OK;
		}

		HRESULT HandsOn()
		{
			HRESULT hr = m_file.Create(m_szTempFileName, m_dwAccess, 0, OPEN_EXISTING);
			if (FAILED(hr))
				return hr;

			return m_file.Seek(0, FILE_END);
		}

		HRESULT Read(LPVOID pBuffer,UINT32 nBufSize, UINT32& nBytesRead)
		{
			return m_file.Read(pBuffer, nBufSize, nBytesRead);
		}

		HRESULT Write(LPCVOID pBuffer,UINT32 nBufSize, LPUINT32 pnBytesWritten = NULL)
		{
			return m_file.Write(pBuffer, nBufSize, pnBytesWritten);
		}

		HRESULT Seek(INT64 nOffset, UINT32 dwFrom = FILE_CURRENT)
		{
			return m_file.Seek(nOffset, dwFrom);
		}

		HRESULT GetPosition(UINT64& nPos)
		{
			return m_file.GetPosition(nPos);
		}

		HRESULT Flush()
		{
			return m_file.Flush();
		}

		HRESULT LockRange(UINT64 nPos, UINT64 nCount)
		{
			return m_file.LockRange(nPos, nCount);
		}

		HRESULT UnlockRange(UINT64 nPos, UINT64 nCount)
		{
			return m_file.UnlockRange(nPos, nCount);
		}

		HRESULT SetSize(UINT64 nNewLen)
		{
			return m_file.SetSize(nNewLen);
		}

		HRESULT GetSize(UINT64& nLen)
		{
			return m_file.GetSize(nLen);
		}

		operator HANDLE()
		{
			return m_file;
		}

		const BaseType * TempFileName()
		{
			return m_szTempFileName;
		}

	private:
		CFile m_file;
		BaseType m_szTempFileName[MAX_PATH];
		DWORD m_dwAccess;
	};

	typedef CTemporaryFileT< CHAR > CTemporaryFileA;
	typedef CTemporaryFileT< WCHAR > CTemporaryFileW;
	typedef CTemporaryFileT< TCHAR > CTemporaryFile;


	
/*! \page temporaryfile_example_page CTemporaryFileT����
<pre>	%CTemporaryFileT���ʹ������</pre>
<pre>
\#include "lgnbase.h"
\#include "lgnfile.h"

	// ...
	LGN::CTemporaryFile tmpFile;

	tmpFile.Create();
	tmpFile.Write("123", 3)
</pre>
*/


////////////////////////////////////////////////////////////////////////////////////////////////////

	//! �����ڴ��ļ�����ģ�徲̬��
	template< typename _BaseType = CHAR>
	class FileMappingTraits
	{
	public:
		static HANDLE SCreateFileMapping(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, UINT32 flProtect, UINT32 dwMaximumSizeHigh, UINT32 dwMaximumSizeLow, LPCSTR lpName)
		{
			return ::CreateFileMappingA(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
		}
		static HANDLE SOpenFileMapping(UINT32 dwDesiredAccess, bool bInheritHandle, LPCSTR lpNameOpenFileMapping)
		{
			return ::OpenFileMappingA(dwDesiredAccess, bInheritHandle, lpNameOpenFileMapping);
		}
	};

	//! �����ڴ��ļ�����ģ�徲̬��
	template< >
	class FileMappingTraits< WCHAR >
	{
	public:
		static HANDLE SCreateFileMapping(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, UINT32 flProtect, UINT32 dwMaximumSizeHigh, UINT32 dwMaximumSizeLow, LPCWSTR lpName)
		{
			return ::CreateFileMappingW(hFile, lpFileMappingAttributes, flProtect, dwMaximumSizeHigh, dwMaximumSizeLow, lpName);
		}
		static HANDLE SOpenFileMapping(UINT32 dwDesiredAccess, bool bInheritHandle, LPCWSTR lpNameOpenFileMapping)
		{
			return ::OpenFileMappingW(dwDesiredAccess, bInheritHandle, lpNameOpenFileMapping);
		}
	};

	//! �����ڴ��ļ�����ģ����
	/*! ����ϵͳAPIʵ�ֹ����ڴ��ļ���������д���ܣ���Դatlfile.h����ͬ<B>ATL::CAtlFileMappingBase</B>������ο�MSDN �� 
		-# �������鿴 \ref filemapping_example_page
	*/
	template< typename BaseType >
	class CFileMappingT
	{
	public:
		CFileMappingT()
		{
			m_pData = NULL;
			m_hMapping = NULL;
		}

		~CFileMappingT()
		{
			Unmap();
		}

		HRESULT MapFile(HANDLE hFile, UINT64 nMappingSize = 0,UINT64 nOffset = 0, UINT32 dwMappingProtection = PAGE_READONLY, UINT32 dwViewDesiredAccess = FILE_MAP_READ)
		{
			LGNASSERT(hFile != INVALID_HANDLE_VALUE && hFile != NULL);

			ULARGE_INTEGER liFileSize;
			liFileSize.LowPart = ::GetFileSize(hFile, &liFileSize.HighPart);
			if (liFileSize.QuadPart < nMappingSize)
				liFileSize.QuadPart = nMappingSize;

			m_hMapping = FileMappingTraits< BaseType >::SCreateFileMapping(hFile, NULL, dwMappingProtection, liFileSize.HighPart, liFileSize.LowPart, 0);
			if (m_hMapping == NULL)
				return API::HResultFromError(::GetLastError());

			if (nMappingSize == 0)
				m_nMappingSize = (liFileSize.QuadPart - nOffset);
			else
				m_nMappingSize = nMappingSize;

			m_dwViewDesiredAccess = dwViewDesiredAccess;
			m_nOffset.QuadPart = nOffset;

			m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, m_nMappingSize, NULL);
			if (m_pData == NULL)
			{
				HRESULT hr = API::HResultFromError(::GetLastError());
				::CloseHandle(m_hMapping);
				m_hMapping = NULL;
				return hr;
			}

			return S_OK;
		}

		HRESULT MapSharedMem(const BaseType * lpszName, UINT64 nMappingSize, bool* pbAlreadyExisted = NULL, LPSECURITY_ATTRIBUTES lpsa = NULL, UINT32 dwMappingProtection = PAGE_READWRITE, UINT32 dwViewDesiredAccess = FILE_MAP_ALL_ACCESS)
		{
			LGNASSERT(nMappingSize > 0);
			LGNASSERT(lpszName != NULL); // if you just want a regular chunk of memory, use a heap allocator

			m_nMappingSize = nMappingSize;

			ULARGE_INTEGER nSize;
			nSize.QuadPart = nMappingSize;
			m_hMapping = FileMappingTraits< BaseType >::SCreateFileMapping(INVALID_HANDLE_VALUE, lpsa, dwMappingProtection, nSize.HighPart, nSize.LowPart, lpszName);
			if (m_hMapping == NULL)
				return API::HResultFromError(::GetLastError());

			if (pbAlreadyExisted != NULL)
				*pbAlreadyExisted = (::GetLastError() == ERROR_ALREADY_EXISTS);

			m_dwViewDesiredAccess = dwViewDesiredAccess;
			m_nOffset.QuadPart = 0;

			m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, (SIZE_T)m_nMappingSize, NULL);
			if (m_pData == NULL)
			{
				HRESULT hr = API::HResultFromError(::GetLastError());
				::CloseHandle(m_hMapping);
				return hr;
			}


			return S_OK;
		}

		HRESULT OpenMapping(const BaseType * lpszName, UINT64 nMappingSize, UINT64 nOffset = 0, UINT32 dwViewDesiredAccess = FILE_MAP_ALL_ACCESS)
		{
			LGNASSERT(lpszName != NULL); // if you just want a regular chunk of memory, use a heap allocator

			m_nMappingSize = nMappingSize;
			m_dwViewDesiredAccess = dwViewDesiredAccess;

			m_hMapping = FileMappingTraits< BaseType >::SOpenFileMapping(m_dwViewDesiredAccess, FALSE, lpszName);
			if (m_hMapping == NULL)
				return API::HResultFromError(::GetLastError());

			m_dwViewDesiredAccess = dwViewDesiredAccess;
			m_nOffset.QuadPart = nOffset;

			m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, (SIZE_T)m_nMappingSize, NULL);
			if (m_pData == NULL)
			{
				HRESULT hr = API::HResultFromError(::GetLastError());
				::CloseHandle(m_hMapping);
				return hr;
			}


			return S_OK;
		}

		HRESULT Unmap()
		{
			HRESULT hr = S_OK;

			if (m_pData != NULL)
			{
				if (!::UnmapViewOfFile(m_pData))
					hr = API::HResultFromError(::GetLastError());
				m_pData = NULL;
			}
			if (m_hMapping != NULL)
			{
				if (!::CloseHandle(m_hMapping) && SUCCEEDED(hr))
					hr = API::HResultFromError(::GetLastError());
				m_hMapping = NULL;
			}
			return hr;
		}

		void* GetData() const
		{
			return m_pData;
		}

		HANDLE GetHandle() const
		{
			return m_hMapping;
		}

		UINT64 GetMappingSize()
		{
			return m_nMappingSize;
		}

		HRESULT CopyFrom( CFileMappingT& orig)
		{
			if (this == &orig)
				return S_OK;
			LGNASSERT(orig.m_pData != NULL);
			LGNASSERT(orig.m_hMapping != NULL);

			m_dwViewDesiredAccess = orig.m_dwViewDesiredAccess;
			m_nOffset.QuadPart = orig.m_nOffset.QuadPart;
			m_nMappingSize = orig.m_nMappingSize;

			if (!::DuplicateHandle(::GetCurrentProcess(), orig.m_hMapping, GetCurrentProcess(),
				&m_hMapping, NULL, TRUE, DUPLICATE_SAME_ACCESS))
				return API::HResultFromError(::GetLastError());

			m_pData = ::MapViewOfFileEx(m_hMapping, m_dwViewDesiredAccess, m_nOffset.HighPart, m_nOffset.LowPart, m_nMappingSize, NULL);
			if (m_pData == NULL)
			{
				HRESULT hr = API::HResultFromError(::GetLastError());
				::CloseHandle(m_hMapping);
				m_hMapping = NULL;
				return hr;
			}

			return S_OK;
		}

		CFileMappingT(CFileMappingT& orig) throw()
		{
			m_pData = NULL;
			m_hMapping = NULL;

			HRESULT hr = CopyFrom(orig);
			if (FAILED(hr))
				LgnThrow(hr);
		}

		CFileMappingT& operator=(CFileMappingT& orig) throw()
		{
			HRESULT hr = CopyFrom(orig);
			if (FAILED(hr))
				LgnThrow(hr);

			return *this;
		}

	private:
		void* m_pData;
		UINT64 m_nMappingSize;
		HANDLE m_hMapping;
		ULARGE_INTEGER m_nOffset;
		DWORD m_dwViewDesiredAccess;
	};

	typedef CFileMappingT< CHAR > CFileMappingA;
	typedef CFileMappingT< WCHAR > CFileMappingW;
	typedef CFileMappingT< TCHAR > CFileMapping;

/*! \page filemapping_example_page CFileMappingT����
<pre>	%CFileMappingT���ʹ������</pre>
<pre>
\#include "lgnbase.h"
\#include "lgnfile.h"

	// ...
	LGN::CFileMapping fileMap, fileMap2;

	// app1
	if (fileMap.MapSharedMem("mysharedmemory", 1024) == S_OK)
	{
		LGN::API::memcpy(fileMap.GetData(), "123", 3);
	}

	// app2
	fileMap2.OpenMapping("mysharedmemory", 1024);
	void * ptr = fileMap2.GetData();
</pre>
*/
	
}; // namespace LGN

#endif // __LGNWIN_FILE_H__
