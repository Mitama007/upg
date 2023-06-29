#include "stdafx.h"
#include "PSX_Semaphore.h"
#include "PSX_TimerClock.h"

CPSX_Semaphore::CPSX_Semaphore ()
{
	m_pstSem 	 = (sem_t *)0;
	m_pstSemInit = (sem_t *)0;
	m_pstSemOpen = (sem_t *)0;
	memset (&m_stSem, 0, sizeof (m_stSem));
}

CPSX_Semaphore::~CPSX_Semaphore ()
{
	Destroy ();
	Close ();
}

int CPSX_Semaphore::Init (int pshared, unsigned value)
{
	m_pstSemInit = &m_stSem; 
	m_pstSem = m_pstSemInit;
	return sem_init (&m_stSem, pshared, value);
}

int CPSX_Semaphore::Destroy ()
{
	int iRet = 0;
	
	if (0 != m_pstSemInit)
	{
		sem_destroy (&m_stSem);
		m_pstSem = 0;
	}	
	m_pstSemInit = 0;
	
	return iRet;
}

bool CPSX_Semaphore::Open (const char *name, int oflags, mode_t mode, unsigned int uiInitCount)
{
	m_pstSemOpen = (sem_t *)sem_open (name, oflags, mode, uiInitCount); 
	m_pstSem = m_pstSemOpen; 
	return (0 != m_pstSem);
}

int CPSX_Semaphore::Close ()
{
	int iRet = 22;
	
	if (0 != m_pstSemOpen)
	{
		iRet = sem_close (m_pstSem);
		m_pstSem = 0;
	}
	m_pstSemOpen = 0;	
	return iRet;//EINVAL;
}

int CPSX_Semaphore::Unlink (const char *name)
{
	return sem_unlink (name);
}

int CPSX_Semaphore::TryWait ()
{
	return sem_trywait (&m_stSem);
}
	
int CPSX_Semaphore::Wait ()
{
	return sem_wait (&m_stSem);
}
	
int CPSX_Semaphore::TimedWait (unsigned long ulMs)
{
	CPSX_TimerClock			objClock;
	const struct timespec 	stTS = objClock.GetOffsetTime (ulMs);
	
	return sem_timedwait (&m_stSem, &stTS);
}
	  
int CPSX_Semaphore::Post ()
{
	return sem_post (&m_stSem);
}
	  
int CPSX_Semaphore::GetValue (int *value)
{
	return sem_getvalue (&m_stSem, value);
}

int CPSX_Semaphore::Wait (unsigned long ulMs)
{
	int 			iRet = 0;
		
	if (0 == ulMs)
	{
		iRet = TryWait ();
	}
	else
	{
		iRet = TimedWait (ulMs);
	}
	return iRet;
}
