#include "stdafx.h"
#include "PSX_Mutex.h"
#include "PSX_TimerClock.h"

CPSX_Mutex::CPSX_Mutex ()
{
	m_pstMutex = 0;
	memset (&m_stMutex, 0, sizeof (m_stMutex));
}

CPSX_Mutex::~CPSX_Mutex ()
{
	Destroy ();
}

CPSX_Mutex::operator pthread_mutex_t *()
{
	return &m_stMutex;
}

CPSX_MutexAttr &CPSX_Mutex::GetAttrObj ()
{
	return m_objAttr;
}

int CPSX_Mutex::Init ()
{
	m_pstMutex = &m_stMutex;
	return pthread_mutex_init (&m_stMutex, m_objAttr);
}

int CPSX_Mutex::Destroy ()
{
	int iRet = 0;
	
	if (0 != m_pstMutex)
	{
		iRet = pthread_mutex_destroy (&m_stMutex);
	}	
	m_pstMutex = 0;	
	return iRet;	
}
    
int CPSX_Mutex::Trylock ()
{
	return pthread_mutex_trylock (&m_stMutex);
}
    
int CPSX_Mutex::Lock ()
{
	return pthread_mutex_lock (&m_stMutex);
}
    
int CPSX_Mutex::Timedlock (unsigned long ulMs)
{
	CPSX_TimerClock			objClock;
	const struct timespec 	stTS = objClock.GetOffsetTime(ulMs);
	
	return pthread_mutex_timedlock (&m_stMutex, &stTS);
}
    
int CPSX_Mutex::Unlock ()
{
	return pthread_mutex_unlock (&m_stMutex);
}

int CPSX_Mutex::Lock (unsigned long ulMs)
{
	int 			iRet = 0;
		
	if (0 == ulMs)
	{
		iRet = Trylock ();
	}
	else
	{
		iRet = Timedlock (ulMs);
	}
	return iRet;
}
