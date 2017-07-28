/*! \file lgnwin.auth.h 
*  \brief WINϵͳ�İ�ȫ��֤����
*
*  ����Ҫ�������ļ��������ļ���lgnwin.ver.h
*
*  ������ȫ������CSecurityAttributes�����ڴ����ͼ���ȫ��������
*  
*  \author ljc
*  \version 3.0.0
*  \date    2010-2012
*  \bug
*  \warning
*/

#ifndef __LGNWIN_AUTH_H__
#define __LGNWIN_AUTH_H__

#include <Sddl.h>
//#include "lgnwin.ver.h"


namespace LGN
{
////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ��ȫ������
	/*! �̳���ϵͳ�ṹSECURITY_ATTRIBUTES�������ͼ���ȫ����������Ҫ���ں˶���Ĵ��� */
	class CSecurityAttributes : public SECURITY_ATTRIBUTES
	{
	public:
		//! ���캯�������Ի���ṹ��ʼ��
		CSecurityAttributes()
		{
			m_pTempSD = NULL;
		}
		//! ���캯���������ͼ���ȫ��������
		/*! \param[in] bInheritHandle �ں˶������Ƿ�ɼ̳�
			\see ����BuildLowIntegrity
		*/
		CSecurityAttributes(bool bInheritHandle)
		{
			BuildLowIntegrity(bInheritHandle);
		}
		//! ���캯�����ͷ��ѷ������Դ
		~CSecurityAttributes()
		{
			if (m_pTempSD != NULL)
				::LocalFree(m_pTempSD);
		}

		//! �����ͼ���ȫ��������
		/*! \param[in] bInheritHandle �ں˶������Ƿ�ɼ̳�
			\note �����vista���ϵͳ���ڲ�����ConvertStringSecurityDescriptorToSecurityDescriptor
		*/
		bool BuildLowIntegrity(bool bInheritHandle)
		{
			nLength					= sizeof(SECURITY_ATTRIBUTES);
			bInheritHandle			= bInheritHandle;
			lpSecurityDescriptor	= &m_pSecDesc;

			::InitializeSecurityDescriptor(lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION);
			if (!::SetSecurityDescriptorDacl(lpSecurityDescriptor, TRUE, 0, FALSE))
			{
				LGNTRACE(LGN_TRACE_CATEGORY_DEF, TraceLevel::Error, TEXT("BuildLowIntegrity.SetSecurityDescriptorDacl error=%x!!!\n"), ::GetLastError() );
				return false;
			}

			if (g_osVersionInfo.IsVistaLater())
			{
				LPCTSTR LOW_INTEGRITY_SDDL_SACL = TEXT("S:(ML;;NW;;;LW)"); 
				// (_WIN32_WINNT >= 0x0500)
				if (::ConvertStringSecurityDescriptorToSecurityDescriptor(LOW_INTEGRITY_SDDL_SACL, SDDL_REVISION_1, &m_pTempSD, NULL ))
				{
					PACL pSacl = NULL;                  // not allocated
					BOOL fSaclPresent = FALSE;
					BOOL fSaclDefaulted = FALSE;
					if (::GetSecurityDescriptorSacl(m_pTempSD, &fSaclPresent, &pSacl, &fSaclDefaulted))
					{
						if (::SetSecurityDescriptorSacl(lpSecurityDescriptor, TRUE, pSacl, FALSE))
						{
							return true;
						}
					}
				}
				LGNTRACE(LGN_TRACE_CATEGORY_DEF, TraceLevel::Error, TEXT("BuildLowIntegrity(vista) error=%x!!!\n"), ::GetLastError() );
				return false;
			}
			return true;
		}

	private:
		CHAR m_pSecDesc[SECURITY_DESCRIPTOR_MIN_LENGTH];
		PSECURITY_DESCRIPTOR m_pTempSD;

	private:
		CSecurityAttributes(const CSecurityAttributes& other); //! ���಻�ɼ̳�
		CSecurityAttributes& operator=(const CSecurityAttributes& other); //!< ������󲻿ɸ�ֵ����
	};

#if (LGN_SUPPORT_SELECTANY)
	LGN_SELECTANY CSecurityAttributes g_saLowIntegrity(false);
#else
	extern CSecurityAttributes g_saLowIntegrity; //!< ����ȫ�ֵͼ���ȫ��������
#endif

}; // namespace LGN

#endif // #ifndef __LGNWIN_AUTH_H__
