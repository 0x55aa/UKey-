/*! \file lgnwin.alloc.h 
 *  \brief WINϵͳ���ڴ���估����
 *
 *  ��lgnbase.h���������̲���ֱ�Ӱ������ļ�
 *
 *  �����ڴ����ӿ�ILgnMemMgr���������ӿ�ILgnBufferMgr�������ڴ������CWin32Heap�����������CLgnBufferMgr
 *  
 *  <ul>
 *  	<li> ILgnMemMgr��������atlmem.h��ָ��ATL::IAtlMemMgr
 *		<li> CWin32Heap��������atlmem.h��ָ��ATL::CWin32Heap
 *  	<li> ILgnBufferMgr��������atlsimpstr.h��ָ��ATL::IAtlStringMgr
 *  	<li> CLgnBufferMgr��������atlstr.h��ָ��ATL::CAtlStringMgr
 *  </ul>
 *
 *  \author ljc
 *  \version 3.0.0
 *  \date    2010-2012
 *  \bug
 *  \warning
 */

#ifndef __LGNWIN_ALLOC_H__
#define __LGNWIN_ALLOC_H__

//#pragma once


/////////////////////////////////////////////////////////////////////////////
// Win32 libraries


#ifndef __ATLMEM_H__
namespace ATL //! Active Template Library
{
////////////////////////////////////////////////////////////////////////////////////////////////////

	//! ģ�庯�������λ���롣��AtlAlignUp(10, 8) = 16
	/*! ��Դ atlmem.h��ͬ<B>ATL::AtlAlignUp</B>������ο�MSDN
		\param[in] n ��ģ��ָ�����͵���
		\param[in] nAlign ����ֵ
		\return ���λ������ֵ
	*/
	template< typename N >
		inline N WINAPI AtlAlignUp( N n, ULONG nAlign ) throw()
	{
		return( N( (n+(nAlign-1))&~(N( nAlign )-1) ) );
	}

	//! ģ�庯�������λ���롣��AtlAlignDown(10, 8) = 8
	/*! ��Դ atlmem.h��ͬ<B>ATL::AtlAlignDown</B>������ο�MSDN
		\param[in] n ��ģ��ָ�����͵���
		\param[in] nAlign ����ֵ
		\return ���λ������ֵ
	*/
	template< typename N >
	inline N WINAPI AtlAlignDown( N n, ULONG nAlign ) throw()
	{
		return( N( n&~(N( nAlign )-1) ) );
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// __interface IAtlMemMgr

#if (_MSC_VER >= 1300)
	__interface __declspec(uuid("654F7EF5-CFDF-4df9-A450-6C6A13C622C0")) IAtlMemMgr
	{
	public:
		void* Allocate( size_t nBytes ) throw();
		void Free( void* p ) throw();
		void* Reallocate( void* p, size_t nBytes ) throw();
		size_t GetSize( void* p ) throw();
	};

#else
#if (_MSC_VER >= 1000)
	interface __declspec(uuid("654F7EF5-CFDF-4df9-A450-6C6A13C622C0")) IAtlMemMgr
#else
	//! �ڴ����ӿ�
	/*! ��Դ atlmem.h��ͬ<B>ATL::IAtlMemMgr</B>������ο�MSDN
	*/
	struct IAtlMemMgr
#endif
	{
	public:
		//! allocate a block of memory
		virtual void* Allocate( size_t nBytes ) throw() = 0;
		//! free a block of memory
		virtual void Free( void* p ) throw() = 0;
		//! reallocate a block of memory
		virtual void* Reallocate( void* p, size_t nBytes ) throw() = 0;
		//! retrieve the size of an allocated memory block
		virtual size_t GetSize( void* p ) throw() = 0;
	};
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
// class CWin32Heap

	//! ���ڴ������
	/*! ��Դ atlmem.h��ͬ<B>ATL::CWin32Heap</B>������ο�MSDN
	 * -# �������鿴 \ref win32heap_example_page	
	*/
	class CWin32Heap :
		public IAtlMemMgr
	{
	public:
		//! The constructor
		/*! \param[in] hHeap An existing heap object
		*/
		CWin32Heap(HANDLE hHeap) throw() :
		  m_hHeap( hHeap )
		{
		}
		//! Allocates a block of memory from the heap object.
		virtual void* Allocate( size_t nBytes ) throw()
		{
			return( ::HeapAlloc( m_hHeap, 0, nBytes ) );
		}
		//! Frees memory previously allocated from the heap
		virtual void Free( void* p ) throw()
		{
			if( p != NULL )
				::HeapFree( m_hHeap, 0, p );
		}
		//! Reallocates a block of memory from the heap object
		virtual void* Reallocate( void* p, size_t nBytes ) throw()
		{
			return (p == NULL)?  Allocate( nBytes ) : ::HeapReAlloc( m_hHeap, 0, p, nBytes );
		}
		//! Returns the size of a memory block allocated from the heap object
		virtual size_t GetSize( void* p ) throw()
		{
			return( ::HeapSize( m_hHeap, 0, p ) );
		}

	public:
		HANDLE m_hHeap;
	};

}; // namespace ATL
#endif // __ATLMEM_H__


namespace LGN
{
////////////////////////////////////////////////////////////////////////////////////////////////////
//

	//! �궨�� ATL::AtlAlignUp
#define LgnAlignUp ATL::AtlAlignUp 
	//! �궨�� ATL::AtlAlignDown
#define LgnAlignDown ATL::AtlAlignDown 

	//! �����ض��� ATL::IAtlMemMgr
	typedef ATL::IAtlMemMgr ILgnMemMgr;
	//! �����ض��� ATL::CWin32Heap
	typedef ATL::CWin32Heap CWin32Heap;

#if (LGN_SUPPORT_SELECTANY)
	LGN_SELECTANY CWin32Heap g_heapmgr(::GetProcessHeap()); //!< ���������ȫ�ֶѹ������
	LGN_SELECTANY ILgnMemMgr * _lgnMemoryManager = &g_heapmgr; //!< ���������ȫ�ֶѹ�������ָ��
#else
	extern LGN::CWin32Heap g_heapmgr; //!< ����ȫ�ֶѹ������
	extern LGN::ILgnMemMgr * _lgnMemoryManager; //!< ����ȫ�ֶѹ�������ָ��
#endif

/*! \page win32heap_example_page CWin32Heap����
<pre>	%CWin32Heap���ʹ������</pre>
<pre>
\#include "lgnbase.h"

	// ...
	LGN::CWin32Heap MyHeap(GetProcessHeap());
	LPBYTE pbBuff = (LPBYTE)MyHeap.Allocate(10);
	MyHeap.Free(pbBuff);

	// or
	LPBYTE pbBuff2 = (LPBYTE)LGN::_lgnMemoryManager->Allocate(10);
	LGN::_lgnMemoryManager->Free(pbBuff2);
</pre>
*/

}; // namespace LGN


// buffer alloc
namespace LGN
{
////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifdef __ATLSIMPSTR_H__
# define ILgnBufferMgr ATL::IAtlStringMgr
# define CBufferData ATL::CStringData
# define CNilBufferData ATL::CNilStringData
# define pBufferMgr pStringMgr
# define GetNilBuffer GetNilString
#else

	struct CBufferData;

#if (_MSC_VER >= 1300)
	__interface ILgnBufferMgr
	{
	public:
		CBufferData* Allocate( int nAllocLength, int nBaseTypeSize ) throw();
		void Free( CBufferData* pData ) throw();
		CBufferData* Reallocate( CBufferData* pData, int nAllocLength, int nBaseTypeSize ) throw();
		CBufferData* GetNilBuffer() throw();
		ILgnBufferMgr* Clone() throw();
	};
#else
	//! �������ӿ�
	/*! ��Դ atlsimpstr.h��ͬ<B>ATL::IAtlStringMgr</B>������ο�MSDN
	*/
	interface ILgnBufferMgr
	{
	public:
		//! Allocate a new CBufferData
		virtual CBufferData* Allocate( int nAllocLength, int nBaseTypeSize ) throw() = 0;
		//! Free an existing CBufferData
		virtual void Free( CBufferData* pData ) throw() = 0;
		//! Change the size of an existing CBufferData
		virtual CBufferData* Reallocate( CBufferData* pData, int nAllocLength, int nBaseTypeSize ) throw() = 0;
		//! Get the CBufferData for a Nil buffer
		virtual CBufferData* GetNilBuffer() throw() = 0;
		//!  return a pointer to a new buffer manager for use with another instance of CBufferT
		virtual ILgnBufferMgr* Clone() throw() = 0;
	};
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
// struct CBufferData

	//! �����������ݽṹ
	/*! ��Դ atlsimpstr.h��ͬ<B>ATL::CStringData</B>������ο�MSDN
	 * -# �������鿴 \ref lgnbuffermgr_example_page	
	*/
	struct CBufferData
	{
		ILgnBufferMgr* pBufferMgr;  //!< Buffer manager for this CBufferData
		int nDataLength;  //!< Length of currently used data in TYPEs
		int nAllocLength;  //!< Length of allocated data in TYPEs
		long nRefs;     //!< Reference count: negative == locked
		// TYPE data[nAllocLength+1]  // A CBufferData is always followed in memory by the actual array of character data

		void* data() throw()
		{
			return (this+1);
		}

		void AddRef() throw()
		{
			LGNASSERT(nRefs > 0);
			::InterlockedIncrement(&nRefs);
		}
		bool IsLocked() const throw()
		{
			return nRefs < 0;
		}
		bool IsShared() const throw()
		{
			return( nRefs > 1 ); 
		}
		void Lock() throw()
		{
			LGNASSERT( nRefs <= 1 );
			nRefs--;  // Locked buffers can't be shared, so no interlocked operation necessary
			if( nRefs == 0 )
			{
				nRefs = -1;
			}
		}
		void Release() throw()
		{
			LGNASSERT( nRefs != 0 );

			if( ::InterlockedDecrement( &nRefs ) <= 0 )
			{
				pBufferMgr->Free( this );
			}
		}
		void Unlock() throw()
		{
			LGNASSERT( IsLocked() );

			if(IsLocked())
			{
				nRefs++;  // Locked buffers can't be shared, so no interlocked operation necessary
				if( nRefs == 0 )
				{
					nRefs = 1;
				}
			}
		}
	};


////////////////////////////////////////////////////////////////////////////////////////////////////
// class CNilBufferData

	//! ��������<B>��</B>���ݽṹ
	/*! ��Դ atlsimpstr.h��ͬ<B>ATL::CNilStringData</B>������ο�MSDN
	*/
	class CNilBufferData :
		public CBufferData
	{
	public:
		CNilBufferData() throw()
		{
			pBufferMgr = NULL;
			nRefs = 2;  // Never gets freed by ILgnBufferMgr
			nDataLength = 0;
			nAllocLength = 0;
			awNil[0] = 0;
			awNil[1] = 0;
		}

		void SetManager( ILgnBufferMgr* pMgr ) throw()
		{
			LGNASSERT( pBufferMgr == NULL );
			pBufferMgr = pMgr;
		}

	public:
		WCHAR awNil[2];
	};
#endif // #ifndef __ATLSIMPSTR_H__


////////////////////////////////////////////////////////////////////////////////////////////////////
// class CLgnBufferMgr

#ifdef __ATLSTR_H__

	LGN_SELECTANY ILgnBufferMgr * _lgnBufferManager = &(ATL::g_strmgr);

#else
	//! ���������
	/*! ��Դ atlstr.h��ͬ<B>ATL::CAtlStringMgr</B>������ο�MSDN
	 * -# �������鿴 \ref lgnbuffermgr_example_page	
	*/
	class CLgnBufferMgr :
		public ILgnBufferMgr
	{
	public:
		CLgnBufferMgr( ILgnMemMgr* pMemMgr = NULL ) throw() :
		  m_pMemMgr( pMemMgr )
		  {
			  m_nil.SetManager( this );
		  }
		  virtual ~CLgnBufferMgr() throw()
		  {
		  }

		  void SetMemoryManager( ILgnMemMgr* pMemMgr ) throw()
		  {
			  LGNASSERT( m_pMemMgr == NULL );
			  m_pMemMgr = pMemMgr;
		  }

		  // ILgnBufferMgr
	public:
		virtual CBufferData* Allocate( int nBaseTypes, int nBaseTypeSize ) throw()
		{
			nBaseTypes = LgnAlignUp( nBaseTypes + 1, 8 );  // Prevent excessive reallocation.  The heap will usually round up anyway.

			size_t nDataBytes = nBaseTypes * nBaseTypeSize;
			size_t nTotalSize = sizeof( CBufferData ) + nDataBytes;
			CBufferData* pData = static_cast< CBufferData* >( m_pMemMgr->Allocate( nTotalSize ) );
			if( pData == NULL )
			{
				return( NULL );
			}
			pData->pBufferMgr = this;
			pData->nRefs = 1;
			pData->nAllocLength = nBaseTypes - 1;
			pData->nDataLength = 0;

			return( pData );
		}
		virtual void Free( CBufferData* pData ) throw()
		{
			LGNASSERT( pData->pBufferMgr == this );
			m_pMemMgr->Free( pData );
		}
		virtual CBufferData* Reallocate( CBufferData* pData, int nBaseTypes, int nBaseTypeSize ) throw()
		{
			LGNASSERT( pData->pBufferMgr == this );
			nBaseTypes = LgnAlignUp( nBaseTypes+1, 8 );  // Prevent excessive reallocation.  The heap will usually round up anyway.

			ULONG nDataBytes = nBaseTypes * nBaseTypeSize;
			ULONG nTotalSize = sizeof( CBufferData ) + nDataBytes;
			CBufferData* pNewData = static_cast< CBufferData* >( m_pMemMgr->Reallocate( pData, nTotalSize ) );
			if( pNewData == NULL )
			{
				return NULL;
			}
			pNewData->nAllocLength = nBaseTypes - 1;

			return pNewData;
		}
		virtual CBufferData* GetNilBuffer() throw()
		{
			m_nil.AddRef();
			return &m_nil;
		}
		virtual ILgnBufferMgr* Clone() throw()
		{
			return this;
		}

	protected:
		ILgnMemMgr* m_pMemMgr;
		CNilBufferData m_nil;
	};

#if (LGN_SUPPORT_SELECTANY)
	LGN_SELECTANY CLgnBufferMgr g_bufmgr(_lgnMemoryManager); //!< ���������ȫ�ֻ�����������
	LGN_SELECTANY ILgnBufferMgr * _lgnBufferManager = &g_bufmgr; //!< ���������ȫ�ֻ������������ָ��
#else
	extern CLgnBufferMgr g_bufmgr; //!< ����ȫ�ֻ�����������
	extern ILgnBufferMgr * _lgnBufferManager; //!< ����ȫ�ֻ������������ָ��
#endif

#endif // #ifdef __ATLSTR_H__

/*! \page lgnbuffermgr_example_page CLgnBufferMgr����
<pre>	%CLgnBufferMgr���ʹ������</pre>
<pre>
\#include "lgnbase.h"

	// ...
	LGN::CLgnBufferMgr MyBuff(LGN::_lgnMemoryManager);
	LGN::CBufferData  * data = MyBuff.Allocate(1, 10);
	MyBuff.Free(data);

	// or
	LGN::CBufferData  * data2 = LGN::_lgnBufferManager->Allocate(1, 10);
	LGN::_lgnBufferManager->Free(data2);
</pre>
*/

}; // namespace LGN

#endif 
