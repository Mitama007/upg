#include "stdafx.h"
#include "PSX_MutexAttr.h"

CPSX_MutexAttr::CPSX_MutexAttr ()
{
	m_pstAttr = 0;
	memset (&m_stAttr, 0, sizeof (m_stAttr));	
}

CPSX_MutexAttr::~CPSX_MutexAttr ()
{
	Uninit ();
}

CPSX_MutexAttr::operator const pthread_mutexattr_t *()
{
	return m_pstAttr;
}

/*********************************************************************
��  �ƣ�Init
��	�ܣ���ʼ���������������Խṹ
��  ����
 		iType[IN]
 				��������������
 				PTHREAD_MUTEX_NORMAL/PTHREAD_MUTEX_ERRORCHECK/
 				PTHREAD_MUTEX_RECURSIVE/PTHREAD_MUTEX_DEFAULT

 		iProtocol[IN]
 				������Э������
 				POSIX_THREAD_PRIO_INHERIT/POSIX_THREAD_PRIO_PROTECT
 				
 		iShared[IN]
 				��������������
 				PTHREAD_PROCESS_PRIVATE/PTHREAD_PROCESS_SHARED
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::Init (int iType/*= PTHREAD_MUTEX_NORMAL*/, int iProtocol/*= PTHREAD_PRIO_NONE*/, int iShared/*= PTHREAD_PROCESS_PRIVATE*/)
{
	int 			iRet 		= -1;
	
	m_pstAttr = &m_stAttr;
	//��ʼ������������
	iRet = pthread_mutexattr_init (m_pstAttr);
	
	//���û�������������
	if (0 == iRet)
	{
		iRet = SetType (iType);
	}
	
	//���û�����Э������
	if (0 == iRet)
	{
		iRet = SetProtocol (iProtocol);
	}
	
	//���û�������������
	if (0 == iRet)
	{
		iRet = SetShared (iShared);
	}
	return (0 == iRet);
}

/*********************************************************************
��  �ƣ�Uninit
��	�ܣ�����ʼ����������������
��  ����
		��
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::Uninit ()
{
	int iRet = 0;
	
	if (0 != m_pstAttr)
	{
		iRet = pthread_mutexattr_destroy (m_pstAttr);
	}
	m_pstAttr = 0;
	
	return (0 == iRet);	
}

/*********************************************************************
��  �ƣ�SetType
��	�ܣ����û�������������
��  ����
 		iType[IN]
 				��������������
 				PTHREAD_MUTEX_NORMAL/PTHREAD_MUTEX_ERRORCHECK/
 				PTHREAD_MUTEX_RECURSIVE/PTHREAD_MUTEX_DEFAULT
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::SetType (int iType)
{
	int iRet = -1;
	
	iRet = pthread_mutexattr_settype (m_pstAttr, iType);
	
	return (0 == iRet);
}

/*********************************************************************
��  �ƣ�GetType
��	�ܣ���ȡ��������������
��  ����
 		&iType[OUT]
 				�������������ԣ��������ִ�гɹ������������½��֮һ
 				PTHREAD_MUTEX_NORMAL/PTHREAD_MUTEX_ERRORCHECK/
 				PTHREAD_MUTEX_RECURSIVE/PTHREAD_MUTEX_DEFAULT
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::GetType (int &iType)
{	
	int iRet = -1;
	
	iRet = pthread_mutexattr_gettype (m_pstAttr, &iType);
	
	return (0 == iRet);
}

/*********************************************************************
��  �ƣ�SetProtocol
��	�ܣ����û�����Э������
��  ����
 		iProtocol[IN]
 				������Э������
 				POSIX_THREAD_PRIO_INHERIT/POSIX_THREAD_PRIO_PROTECT
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::SetProtocol (int iProto)
{
	int iRet = -1;

#ifndef WIN32
	iRet = pthread_mutexattr_setprotocol (m_pstAttr, iProto);
#endif
	
	return (0 == iRet);
}

/*********************************************************************
��  �ƣ�GetProtocol
��	�ܣ���ȡ������Э������
��  ���� 		
 		&iProtocol[out]
 				������Э�����ԣ��������ִ�гɹ�����������½��֮һ
 				POSIX_THREAD_PRIO_INHERIT/POSIX_THREAD_PRIO_PROTECT
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::GetProtocol (int &iProtocol)
{	
	int iRet = -1;
	
#ifndef WIN32
	iRet = pthread_mutexattr_getprotocol(m_pstAttr, &iProtocol);
#endif
	
	return (0 == iRet);	
}

/*********************************************************************
��  �ƣ�SetShared
��	�ܣ����û��⻥������������
��  ���� 		
 		iShared[IN]
 				��������������
 				PTHREAD_PROCESS_PRIVATE/PTHREAD_PROCESS_SHARED
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::SetShared (int iShared)
{
	int iRet = -1;
	
	iRet = pthread_mutexattr_setpshared (m_pstAttr, iShared);
	
	return (0 == iRet);
}

/*********************************************************************
��  �ƣ�GetShared
��	�ܣ���ȡ��������������
��  ����
 		&iShared[out]
 				�������������ԣ��������ִ�гɹ�����������½��֮һ
 				PTHREAD_PROCESS_PRIVATE/PTHREAD_PROCESS_SHARED
����ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
bool CPSX_MutexAttr::GetShared (int &iShared)
{	
	int iRet = -1;
	
	iRet = pthread_mutexattr_getpshared (m_pstAttr, &iShared);
	
	return (0 == iRet);
}

