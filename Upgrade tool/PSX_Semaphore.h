#ifndef PSX_SEMAPHORE_H_
#define PSX_SEMAPHORE_H_

#include "inc_inner.h"

class CPSX_Semaphore
{
private:
	sem_t m_stSem;
	sem_t *m_pstSem;
	sem_t *m_pstSemInit;
	sem_t *m_pstSemOpen;
private:
	int TryWait ();
	int Wait ();
	int TimedWait (unsigned long ulMs);
public:
	int Init (int pshared, unsigned value);
	int Destroy ();
	bool Open (const char *name, int oflags, mode_t mode, unsigned int uiInitCount);
	int Close ();
	int Unlink (const char *name);	
	int Post ();
	int GetValue (int *value);
	int Wait (unsigned long ulMs);
public:
	CPSX_Semaphore ();
	~CPSX_Semaphore ();
};

#endif //PSX_SEMAPHORE_H_
