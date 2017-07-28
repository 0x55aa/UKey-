/*! \file lgnwin.sock.h 
*  \brief WINϵͳ��SOCKETͨѶ��
*
*  ����Ҫ�������ļ��������ļ���lgnbase.h
*
*  ����SOCKETͨѶ��CSocket
*  
*  \author ljc
*  \version 3.0.0
*  \date    2010-2012
*  \bug
*  \warning
*/

#ifndef __LGNWIN_SOCK_H__
#define __LGNWIN_SOCK_H__

#ifndef __LGN_BASE_H__
#error lgnwin.gsmem.h requires include lgnbase.h
#endif

#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")


namespace LGN
{
	//! SOCKETͨѶ��
	/*! �ڲ�����ϵͳAPIʵ��SOCKETͨѶͨѶ���ܣ�Ŀǰֻʵ����TCP�ͻ���ͨѶ����
		-# �������鿴 \ref socket_example_page
	*/
	class CSocket
	{
	public:
		//! ����SOCKETʹ�ã�����ο�WSAStartup
		static int Startup(BYTE btMajorVer=1, BYTE btMinorVer=0)
		{
			WSADATA wsaData;
			return ::WSAStartup(MAKEWORD(btMajorVer,btMinorVer), &wsaData);
		}
		//! ��ֹSOCKETʹ�ã�����ο�WSACleanup
		static int Cleanup()
		{
			return ::WSACleanup();
		}

	public:
		//! ���캯������ʼ��Ա����
		CSocket() : m_hSocket(INVALID_SOCKET)
		{
		}
		//! ��ȷ���͵Ĺ��캯������ʼ��Ա����
		explicit CSocket( SOCKET hSock ) : m_hSocket(hSock)
		{
		}

		//! ���캯�������SOCKET��Ч��ر�
		virtual ~CSocket()
		{
			Close();
		}

		//! ����SOCKET���
		operator SOCKET() const
		{
			return( m_hSocket );
		}

	public:
		/*! \brief ��������
			����SOCKET�����������ɹ�������ͨѶ�Ľ��ճ�ʱʱ��(45S)
			\param[in] pszHostIp ������IP��ַ��ANSI�ַ���
			\param[in] nPort �˿�
			\return �����
		*/
		HRESULT Connect(LPCSTR pszHostIp, UINT32 nPort)
		{
			m_hSocket = ::socket(PF_INET, SOCK_STREAM, 0);
			if (m_hSocket == INVALID_SOCKET)
			{
				return API::HResultFromError(::WSAGetLastError());
			}

			// socket addr
			SOCKADDR_IN sockAddr;
			API::memset(&sockAddr,0,sizeof(sockAddr));
			sockAddr.sin_family = AF_INET;
			sockAddr.sin_addr.s_addr = ::inet_addr(pszHostIp);
			sockAddr.sin_port = htons(nPort);
			// connects to peer
			if (::connect(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
			{		
				m_hSocket = INVALID_SOCKET;
				return API::HResultFromError(::WSAGetLastError());
			}

			// ���ý��ճ�ʱʱ��
			UINT32 nTimeOut = 45000; // 45S
			::setsockopt(m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&nTimeOut, sizeof(nTimeOut));
			
			return S_OK;
		}

		/*! \brief �ر������ӵ�SOCKET
			\return �����
		*/
		HRESULT Close()
		{
			if (m_hSocket != INVALID_SOCKET)
			{
				::closesocket(m_hSocket);
				m_hSocket = INVALID_SOCKET;
			}

			return S_OK;
		}

		/*! \brief ��SOCKET��������
			\param[in] pBuffer ���������ݵĻ�����ָ��
			\param[in] nBuffSize ����������\a pBuffer�ĳ���
			\return �����
		*/
		HRESULT Send(LPCVOID pBuffer, UINT32 nBuffSize)
		{
			if (::send(m_hSocket, (char*)pBuffer, nBuffSize, 0) == SOCKET_ERROR)
				return API::HResultFromError(::WSAGetLastError());
			return S_OK;
		}

		/*! \brief ��SOCKET��������
			\param[in] pBuffer ���������ݵĻ�����ָ��
			\param[in] nBuffSize ��������ݵĳ��ȣ������ڻ�����\a pBuffer�ķ���ռ䳤��
			\param[in] nRecvLen ���յ������ݳ���
			\return �����
		*/
		HRESULT Receive(LPVOID pBuffer, UINT32 nBuffSize, UINT32 & nRecvLen)
		{
			if ((nRecvLen = ::recv(m_hSocket, (char*)pBuffer, nBuffSize, 0)) == SOCKET_ERROR)
				return API::HResultFromError(::WSAGetLastError());
			return S_OK;
		}

	protected:
		SOCKET m_hSocket; //!< SOCKET���

	private:
		CSocket(const CSocket& other); //! ���಻�ɼ̳�
		CSocket& operator=(const CSocket& other); //!< ������󲻿ɸ�ֵ����
	};


/*! \page socket_example_page CSocketT����
<pre>	%CSocketT���ʹ������</pre>
<pre>
\#include "lgnbase.h"
\#include "lgnsock.h"

	// ...
	// ��ʹ��SOCKETǰ����ִ������һ�д���
	LGN::CSocket::Startup();
	
	LGN::CSocket socket;
	socket.Connect("127.0.0.1", 30003);
	socket.Send("123", 3);

	//
	LGN::CSocket::Cleanup();
</pre>
*/

}; // namespace LGN

#endif // __LGNWIN_SOCK_H__
