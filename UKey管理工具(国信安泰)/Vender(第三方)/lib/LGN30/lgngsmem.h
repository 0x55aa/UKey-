/*! \file lgngsmem.h 
*  \brief ȫ�ֹ����ڴ���
*
*  ����Ҫ�������ļ��������ļ���lgnbase.h
*
*  ����ϵͳ���Ͱ�����Ӧϵͳ��ȫ�ֹ����ڴ���
*
*  
*  \author ljc
*  \version 3.0.0
*  \date    2010-2012
*  \bug
*  \warning
*/

#ifndef __LGN_GSMEM_H__
#define __LGN_GSMEM_H__


#include "lgnsync.h"
#if (LGN_WINSYS)
#include "win\lgnwin.ver.h"
#include "win\lgnwin.auth.h"
#include "win\lgnwin.gsmem.h"
#else
#include "unix/lgnunix.gsmem.h"
#endif


#endif // __LGN_GSMEM_H__
