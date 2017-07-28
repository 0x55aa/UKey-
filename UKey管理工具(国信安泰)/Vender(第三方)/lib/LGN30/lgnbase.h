/*! \file lgnbase.h 
 *  \brief ʹ��LGN����������ļ���
 *
 * ����ϵͳ���Ͱ���������ļ����������ܶ����Զ��ͷţ��ӿڣ�����ָ��ģ���࣬����࣬ϵͳ�������ٴη�װ��
 *  \author ljc
 *  \version 3.0.0
 *  \date    2010-2012
 *  \bug
 *  \warning
 */


#ifndef __LGN_BASE_H__
#define __LGN_BASE_H__

#include "lgndef.h"
#if (LGN_WINSYS)
#include "win\lgnwin.api.h"
#include "win\lgnwin.except.h"
#include "win\lgnwin.alloc.h"
#include "win\lgnwin.core.h"
#else
#include "unix/lgnunix.api.h"
#include "unix/lgnunix.except.h"
#include "unix/lgnunix.alloc.h"
#include "unix/lgnunix.core.h"
#endif
#include "lgntrace.h"
#include "lgnbuffer.h"
#include "lgnstr.h"
#include "lgnpath.h"
#include "lgnencoding.h"


namespace LGN //! ������ȫ�������ռ�
{
////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ���ܶ����Զ��ͷţ��ӿ�
	/*! ��Ҫ���CSmartPtr\<T\>��CSmartObject\<Base\>һ��ʹ�ã�������鹹�������Զ��ͷŶ��� 
		-# �������鿴 \ref smartptr_smartobject_example_page
	*/
	LGN_INTERFACE ISmartObject
	{
	public:
#if (!LGN_WINSYS)
		//! ��Щunixϵͳ��֧��interface����struct����������鹹����
		virtual ~ISmartObject() {};
#endif
		//! ��������������һ
		virtual ULONG AddRef() = 0;
		//! ��������������һ�����Ϊ0��ɾ���ö���
		virtual ULONG Release() = 0;
	};


////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ����ָ��ģ����
	/*! ����T��������ṩ#LGN::ISmartObject�ӿڡ�
		-# �������鿴 \ref smartptr_smartobject_example_page
	*/
	template < class T >
	class CSmartPtr
	{
	public:
		CSmartPtr() : m_pTVal(NULL)
		{
		}
		CSmartPtr(T* pTVal) : m_pTVal(pTVal)
		{
			if (pTVal != (T*)NULL)
				pTVal->AddRef();
		}
		CSmartPtr(CSmartPtr<T> & rPtr) : m_pTVal(rPtr.m_pTVal)
		{
			if (m_pTVal != (T*)NULL)
				m_pTVal->AddRef();
		}
		~CSmartPtr()
		{
			if (m_pTVal != (T*)NULL)
				m_pTVal->Release();
			m_pTVal = NULL;
		}

		operator T*() const
		{
			return m_pTVal;
		}
		T& operator*() const
		{
			LGNASSERT(m_pTVal!=NULL);
			return *m_pTVal;
		}
		//! The assert on operator& usually indicates a bug.  If this is really
		//! what is needed, however, take the address of the p member explicitly.
		T** operator&() throw()
		{
			LGNASSERT(m_pTVal==NULL);
			return &m_pTVal;
		}

		T * operator->()
		{
			return m_pTVal;
		}
		T const * operator->() const
		{
			return m_pTVal;
		}
		T &operator()()
		{
			return *m_pTVal;
		}
	     
		bool operator!() const throw()
		{
			return (m_pTVal == NULL);
		}

		CSmartPtr<T> &operator=(const CSmartPtr<T> & rPtr)
		{
			if (rPtr.m_pTVal != (T*)NULL)
				rPtr.m_pTVal->AddRef();
			if (m_pTVal != (T*)NULL)
				m_pTVal->Release();
			m_pTVal = rPtr.m_pTVal;
			return *this;
		}

		bool operator==(const CSmartPtr<T> & rPtr) const
		{
			return m_pTVal == rPtr.m_pTVal;
		}
		bool operator!=(const CSmartPtr<T> & rPtr) const
		{
			return m_pTVal != rPtr.m_pTVal;
		}

		bool operator==(const T * pTVal) const
		{
			return m_pTVal == pTVal;
		}
		bool operator!=(const T * pTVal) const
		{
			return m_pTVal != pTVal;
		}

		//! Attach to an existing interface (does not AddRef)
		void Attach(T* pTVal)
		{
			if (m_pTVal)
				m_pTVal->Release();
			m_pTVal = pTVal;
		}
		//! Detach the interface (does not Release)
		T* Detach() 
		{
			T* pTVal = m_pTVal;
			m_pTVal = NULL;
			return pTVal;
		}

	protected:
		//! ��Դ����ָ��
		T * m_pTVal;
	};


////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ���ܶ���ģ����
	/*! �̳��û���Base��ʵ�ֶ�������ֵ��/��һ�ӣ����ṩ��������ʵ���ӿڡ�
		-# �������鿴 \ref smartptr_smartobject_example_page
	*/
	template < class Base >
	class CSmartObject : public Base
	{
	public:
		//! ���캯�������ö�������Ϊ0
		CSmartObject() : m_nRefs(0)
		{
		}
		
		/*! \brief ʵ�ֶ�������ֵ��һ
			\return ��һ���ֵ
		*/
		virtual ULONG AddRef()
		{
			return LGN::API::SafeIncrement(&m_nRefs);
		}
		/*! \brief ʵ�ֶ�������ֵ��һ
			\return ��һ���ֵ
		*/
		virtual ULONG Release()
		{
			if ((LGN::API::SafeDecrement(&m_nRefs)) == 0)
				delete this;
			return m_nRefs;
		}

		//static CSmartObject<Base> * CreateInstance()
		//{
		//	CSmartObject<Base> * p = new CSmartObject<Base>();
		//	if (p)
		//		p->AddRef();
		//	return p;
		//}
		/*! ��������ʵ���ӿ�
			\param [out] pp ����ʵ��ָ���ָ�롣
			\return S_OK, S_FALSE
		*/
		static HRESULT CreateInstance( Base ** pp)
		{
			LGNASSERT(pp!=NULL);
			* pp = new CSmartObject<Base>();
			if (*pp)
			{
				(*pp)->AddRef();
				return S_OK;
			}
			return S_FALSE;
		}

	private:
		ULONG m_nRefs;
	};


/*! \page smartptr_smartobject_example_page CSmartPtr����
<pre>	%ISmartObject�ӿڡ�%CSmartPtr���%CSmartObject���ʹ������</pre>
<pre>
\#include "lgnbase.h"

	// ...
	class A : public LGN::ISmartObject
	{
	public:
		void f() {}
	};

	LGN::CSmartPtr< A > a;
	LGN::CSmartObject< A >::CreateInstance(&a);
	a->f();
</pre>
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ϵͳ�ں˶�����������
	/*! ��Ҫ���ڻ��࣬ʵ�ֶ�ϵͳ�ں˶����������࣬���鹹ʱ�رվ��������ͬ<B>ATL::CHandle</B>��(atlbase.h)������ο�MSDN�� */
	class CHandle
	{
	public:
		CHandle() throw() :
			m_h( NULL )
		{
		}
		CHandle( CHandle& h ) throw() :
			m_h( NULL )
		{
			Attach( h.Detach() );
		}
		explicit CHandle( HANDLE h ) throw() :
			m_h( h )
		{
		}
		~CHandle() throw()
		{
			if( m_h != NULL )
			{
				Close();
			}
		}

		CHandle& operator=( CHandle& h ) throw()
		{
			if( this != &h )
			{
				if( m_h != NULL )
				{
					Close();
				}
				Attach( h.Detach() );
			}

			return( *this );
		}

		operator HANDLE() const throw()
		{
			return( m_h );
		}

		//! Attach to an existing handle (takes ownership).
		void Attach( HANDLE h ) throw()
		{
			LGNASSERT( m_h == NULL );
			m_h = h;  // Take ownership
		}
		//! Detach the handle from the object (releases ownership).
		HANDLE Detach() throw()
		{
			HANDLE h = m_h;  // Release ownership
			m_h = NULL;
			return( h );
		}

		//! Close the handle.
		void Close() throw()
		{
			if( m_h != NULL )
			{
				LGN::API::CloseHandle( m_h );
				m_h = NULL;
			}
		}

	public:
		HANDLE m_h;
	};


}; // namespace LGN

// ��Ҫ�õ�CHandle
#include "lgnsync.h"


#endif // !__LGN_BASE_H__


////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _LGN_IMPL
#if (LGN_WINSYS)
#include "win\lgnwin.base.inc" //!< �����̲�֧��selectany����C���п�ʱ����Ҫ�������ļ�������һ�Σ���
#else
#include "unix/lgnunix.base.inc" //!< ����g++��֧��selectany������ȫ�ֶ���ֻ�ܱ�����һ�Σ����Ǹ��ļ�ֻ�ܱ�����һ�Ρ�
#endif
#endif


/*! \file lgnwin.base.inc
 *  \brief ȫ�ֶ������C���п�ʵ��
 *
 * �����̲�֧��selectany����C���п�ʱ��������һ��.cpp�ļ���������ļ���
 *  \author ljc
 *  \version 3.0.0
 *  \date    2010-2012
 *  \bug
 *  \warning
 */

/*! \mainpage LGN�ο��ֲ�
 *
 * \section intro_sec ����
 *
 * Ŀ�ģ���ƽ̨Դ�룬�������������⣬�ɱ������С������ִ�д��롣
 *
 * ������Window 2000�Ժ�ϵͳ��VC6-VC9��C++ Builder 4.0��linux��G++
 *
 * ���ܣ�ģ��ATLһЩģ���࣬ʵ���쳣������־�����ڴ�����ַ�����������ת����
 *
 * \section install_sec ��װ
 *
 * \subsection step1 ��һ��������LGN30Ŀ¼���Լ��Ĺ����£�����VC����·��������LGNĿ¼
 *  
 * \subsection step2 �ڶ�������stdafx.h�����lgnbase.h
 *  
 * \subsection step3 �������������̲�֧��selectany����C���п�ʱ����Ҫ��stdafx.cpp���ȶ���_LGN_IMPL����ٴΰ���lgnbase.h
 *  
 * etc...
 */

/*! \page example_page �����б�
 \subpage smartptr_smartobject_example_page 
 \subpage simplebuffer_example_page 
 \subpage buffer_example_page 
 \subpage encodingbase_example_page 
 \subpage encodingtraits_example_page 
 \subpage filewhole_example_page 
 \subpage stdiofile_example_page 
 \subpage sockwhole_example_page 
 \subpage stringex_example_page 
 \subpage tracefileandlineinfo_example_page 
 \subpage trace_example_page 
 \subpage tracemacro_example_page 
 \subpage win32heap_example_page 
 \subpage lgnbuffermgr_example_page 
 \subpage modulepath_example_page 
 \subpage loadmodule_example_page 
 \subpage lgnexception_example_page 
 \subpage file_example_page 
 \subpage temporaryfile_example_page 
 \subpage filemapping_example_page 
 \subpage socket_example_page
 \subpage thread_example_page 
*/
