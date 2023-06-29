#ifndef PSX_MUTEX_H_
#define PSX_MUTEX_H_

#include "inc_inner.h"
#include "PSX_MutexAttr.h"

class CPSX_Mutex
{
private:
	pthread_mutex_t		m_stMutex;	
	pthread_mutex_t 	*m_pstMutex;
	CPSX_MutexAttr		m_objAttr;
private:
	int Trylock ();
	int Lock ();
	int Timedlock (unsigned long ulMs);
public:
    int Init ();
    int Destroy ();    
    int Lock (unsigned long ulMs);
    int Unlock ();
    CPSX_MutexAttr &GetAttrObj ();
    
    operator pthread_mutex_t *();
public:
	CPSX_Mutex ();
	~CPSX_Mutex ();	
};

#endif //PSX_MUTEX_H_
