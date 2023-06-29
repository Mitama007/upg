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
名  称：Init
功	能：初始化互斥锁对象属性结构
参  数：
 		iType[IN]
 				互斥锁类型属性
 				PTHREAD_MUTEX_NORMAL/PTHREAD_MUTEX_ERRORCHECK/
 				PTHREAD_MUTEX_RECURSIVE/PTHREAD_MUTEX_DEFAULT

 		iProtocol[IN]
 				互斥锁协议属性
 				POSIX_THREAD_PRIO_INHERIT/POSIX_THREAD_PRIO_PROTECT
 				
 		iShared[IN]
 				互斥锁共享属性
 				PTHREAD_PROCESS_PRIVATE/PTHREAD_PROCESS_SHARED
返回值：		
		1	成功
		0	失败				
*********************************************************************/
bool CPSX_MutexAttr::Init (int iType/*= PTHREAD_MUTEX_NORMAL*/, int iProtocol/*= PTHREAD_PRIO_NONE*/, int iShared/*= PTHREAD_PROCESS_PRIVATE*/)
{
	int 			iRet 		= -1;
	
	m_pstAttr = &m_stAttr;
	//初始化互斥锁属性
	iRet = pthread_mutexattr_init (m_pstAttr);
	
	//设置互斥锁类型属性
	if (0 == iRet)
	{
		iRet = SetType (iType);
	}
	
	//设置互斥锁协议属性
	if (0 == iRet)
	{
		iRet = SetProtocol (iProtocol);
	}
	
	//设置互斥锁共享属性
	if (0 == iRet)
	{
		iRet = SetShared (iShared);
	}
	return (0 == iRet);
}

/*********************************************************************
名  称：Uninit
功	能：反初始化互斥锁对象属性
参  数：
		无
返回值：		
		1	成功
		0	失败				
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
名  称：SetType
功	能：设置互斥锁类型属性
参  数：
 		iType[IN]
 				互斥锁类型属性
 				PTHREAD_MUTEX_NORMAL/PTHREAD_MUTEX_ERRORCHECK/
 				PTHREAD_MUTEX_RECURSIVE/PTHREAD_MUTEX_DEFAULT
返回值：		
		1	成功
		0	失败				
*********************************************************************/
bool CPSX_MutexAttr::SetType (int iType)
{
	int iRet = -1;
	
	iRet = pthread_mutexattr_settype (m_pstAttr, iType);
	
	return (0 == iRet);
}

/*********************************************************************
名  称：GetType
功	能：获取互斥锁类型属性
参  数：
 		&iType[OUT]
 				互斥锁类型属性，如果函数执行成功，将返回以下结果之一
 				PTHREAD_MUTEX_NORMAL/PTHREAD_MUTEX_ERRORCHECK/
 				PTHREAD_MUTEX_RECURSIVE/PTHREAD_MUTEX_DEFAULT
返回值：		
		1	成功
		0	失败				
*********************************************************************/
bool CPSX_MutexAttr::GetType (int &iType)
{	
	int iRet = -1;
	
	iRet = pthread_mutexattr_gettype (m_pstAttr, &iType);
	
	return (0 == iRet);
}

/*********************************************************************
名  称：SetProtocol
功	能：设置互斥锁协议属性
参  数：
 		iProtocol[IN]
 				互斥锁协议属性
 				POSIX_THREAD_PRIO_INHERIT/POSIX_THREAD_PRIO_PROTECT
返回值：		
		1	成功
		0	失败				
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
名  称：GetProtocol
功	能：获取互斥锁协议属性
参  数： 		
 		&iProtocol[out]
 				互斥锁协议属性，如果函数执行成功，将填充以下结果之一
 				POSIX_THREAD_PRIO_INHERIT/POSIX_THREAD_PRIO_PROTECT
返回值：		
		1	成功
		0	失败				
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
名  称：SetShared
功	能：设置互斥互斥锁共享属性
参  数： 		
 		iShared[IN]
 				互斥锁共享属性
 				PTHREAD_PROCESS_PRIVATE/PTHREAD_PROCESS_SHARED
返回值：		
		1	成功
		0	失败				
*********************************************************************/
bool CPSX_MutexAttr::SetShared (int iShared)
{
	int iRet = -1;
	
	iRet = pthread_mutexattr_setpshared (m_pstAttr, iShared);
	
	return (0 == iRet);
}

/*********************************************************************
名  称：GetShared
功	能：获取互斥锁共享属性
参  数：
 		&iShared[out]
 				互斥锁共享属性，如果函数执行成功，将填充以下结果之一
 				PTHREAD_PROCESS_PRIVATE/PTHREAD_PROCESS_SHARED
返回值：		
		1	成功
		0	失败				
*********************************************************************/
bool CPSX_MutexAttr::GetShared (int &iShared)
{	
	int iRet = -1;
	
	iRet = pthread_mutexattr_getpshared (m_pstAttr, &iShared);
	
	return (0 == iRet);
}

