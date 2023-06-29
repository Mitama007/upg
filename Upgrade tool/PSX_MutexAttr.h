#ifndef PSX_MUTEXATTR_H_
#define PSX_MUTEXATTR_H_

#include "inc_inner.h"

#ifdef WIN32
#define  PTHREAD_PRIO_NONE 0
#endif

class CPSX_MutexAttr
{
private:
	pthread_mutexattr_t m_stAttr;
	pthread_mutexattr_t *m_pstAttr;
public:
	bool Init (int iType = PTHREAD_MUTEX_NORMAL, int iProtocol = PTHREAD_PRIO_NONE, int iShared = PTHREAD_PROCESS_PRIVATE);
	bool Uninit ();
	bool SetType (int iType = PTHREAD_MUTEX_NORMAL);
	bool SetProtocol (int iProto = PTHREAD_PRIO_NONE);
	bool SetShared (int iShared = PTHREAD_PROCESS_PRIVATE);
	bool GetType (int &iType);
	bool GetProtocol (int &iProto);
	bool GetShared (int &iShared);
	
	operator const pthread_mutexattr_t *();
public:
	CPSX_MutexAttr ();
	~CPSX_MutexAttr ();
};
#endif /*PSX_MUTEXATTR_H_*/
