/*! \file lgnthread.h
*  \brief �߳���
*
*  ����Ҫ�������ļ��������ļ���lgnbase.h
*
*  ����ϵͳ���ʹ����̼߳���ز�������
*  
*  \author ljc
*  \version 3.0.0
*  \date    2010-2012
*  \bug
*  \warning
*/

#ifndef __LGN_THREAD_H__
#define __LGN_THREAD_H__

#if (LGN_WINSYS)
#include "win\lgnwin.thread.h"
#else
#include "unix/lgnunix.thread.h"
#endif

#ifndef __LGN_BASE_H__
#error lgnthread.h requires include lgnbase.h
#endif


#endif // __LGN_THREAD_H__
