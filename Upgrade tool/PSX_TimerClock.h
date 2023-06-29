#ifndef PSX_TIMERCLOCK_H_
#define PSX_TIMERCLOCK_H_

#include "inc_inner.h"

class CPSX_TimerClock
{
private:
	timer_t 		m_stTimerId;
	clockid_t 		m_stClockId;	//CLOCK_REALTIME,CLOCK_MONOTONIC,CLOCK_HOST_REALTIME
public:
    typedef enum {EN_TM_FORMAT_SEC = 1, EN_TM_FORMAT_MSEC, EN_TM_FORMAT_USEC}EN_TM_FORMAT;
public:
	int GetRes (struct timespec *res);
	int GetTime (struct timespec *tp);
    long long GetTime (EN_TM_FORMAT const enFormat = EN_TM_FORMAT_MSEC);
    int GetTime (struct timeb &tm);
	struct timespec GetOffsetTime (unsigned long ulMs);
	int NanoSleep (int flags, const struct timespec *rqtp,	struct timespec *rmtp);
	int SetTime (const struct timespec *tp);
	int NanoSleep (const struct timespec *rqtp, struct timespec *rmtp);
	int TimerCreate (struct sigevent *restrict_evp);
	int TimerDelete ();
	int TimerGetOverrun ();
	int TimerGetTime (struct itimerspec *value);
	int TimerSetTime (int flags, const struct itimerspec *restrict_value, struct itimerspec *restrict_ovalue);	
public:
	CPSX_TimerClock (clockid_t clock_id = CLOCK_REALTIME);
	~CPSX_TimerClock ();
};
#endif /*PSX_TIMERCLOCK_H_*/

