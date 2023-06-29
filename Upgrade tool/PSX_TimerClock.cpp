#include "stdafx.h"
#include "PSX_TimerClock.h"

CPSX_TimerClock::CPSX_TimerClock (clockid_t clock_id /*= CLOCK_REALTIME*/)
{
    m_stTimerId = 0;
	m_stClockId = clock_id;
}

CPSX_TimerClock::~CPSX_TimerClock ()
{
	
}

int CPSX_TimerClock::GetRes (struct timespec *res)
{	
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return clock_getres (m_stClockId, res);
#else
	return 0;
#endif
}

int CPSX_TimerClock::GetTime (struct timespec *tp)
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return clock_gettime (m_stClockId, tp);
#elif (OS_TYPE_CODE == OS_TYPE_LINUX_DESKTOP)
	struct timeval now;
	
	gettimeofday(&now, NULL);
	tp->tv_sec = now.tv_sec;
	tp->tv_nsec = now.tv_usec * 1000;
	return 0;
#elif (OS_TYPE_CODE == OS_TYPE_WINDOWS)
    struct _timeb stCurSysTime;
    _ftime(&stCurSysTime);

    tp->tv_sec = stCurSysTime.time;
    tp->tv_nsec = stCurSysTime.millitm * 1000000;	
    return 0;
#endif
}

long long CPSX_TimerClock::GetTime (EN_TM_FORMAT const enFormat/* = EN_TM_FORMAT_MSEC*/)
{
    struct timespec tp = {0};

    GetTime(&tp);

    long long llRet = tp.tv_sec;

    if (EN_TM_FORMAT_USEC == enFormat)
    {
        llRet *= 1000000;
        llRet += (tp.tv_nsec + 500) / 1000;
    }
    else if (EN_TM_FORMAT_MSEC == enFormat)
    {
        llRet *= 1000;
        llRet += (tp.tv_nsec + 500000) / 1000000;
    }
    else if (EN_TM_FORMAT_SEC == enFormat)
    {
        llRet += (tp.tv_nsec + 500000000) / 1000000000;
    }
    return llRet;
}

int CPSX_TimerClock::GetTime (struct timeb &tm)
{
    struct timespec tp = {0};

    int iRet = GetTime(&tp);

    tm.time    = tp.tv_sec;
    tm.millitm = (tp.tv_nsec + 500000) / 1000000;
    return iRet;
}

struct timespec CPSX_TimerClock::GetOffsetTime (unsigned long ulMs)
{
	struct timespec stTS = {0};
	
	if (0 == GetTime (&stTS))
	{
		stTS.tv_sec += ulMs / 1000;
		ulMs = ulMs % 1000;
		stTS.tv_sec += (stTS.tv_nsec + ulMs * 1000000) / 1000000000;
		stTS.tv_nsec = (stTS.tv_nsec + ulMs * 1000000) % 1000000000;
	}
	return stTS;
}

int CPSX_TimerClock::NanoSleep (int flags, const struct timespec *rqtp,	struct timespec *rmtp)
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
    return clock_nanosleep (m_stClockId, flags, rqtp, rmtp);
#else
	return 0;
#endif
}

int CPSX_TimerClock::SetTime (const struct timespec *tp)
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return clock_settime (m_stClockId, tp);
#else
	return 0;
#endif
}
	
int CPSX_TimerClock::NanoSleep (const struct timespec *rqtp, struct timespec *rmtp)
{
#ifndef WIN32
	return nanosleep (rqtp, rmtp);
#else
    return 0;
#endif
}

int CPSX_TimerClock::TimerCreate (struct sigevent *restrict_evp)
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return timer_create (m_stClockId, restrict_evp, &m_stTimerId);
#else
	return 0;
#endif
}
	
int CPSX_TimerClock::TimerDelete ()
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return timer_delete (m_stTimerId);	
#else
	return 0;
#endif
}
	
int CPSX_TimerClock::TimerGetOverrun ()
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return timer_getoverrun (m_stTimerId);
#else
	return 0;
#endif
}

int CPSX_TimerClock::TimerGetTime (struct itimerspec *value)
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return timer_gettime (m_stTimerId, value);
#else
	return 0;
#endif
}
	
int CPSX_TimerClock::TimerSetTime (int flags, const struct itimerspec *restrict_value, struct itimerspec *restrict_ovalue)
{
#if (OS_TYPE_CODE == OS_TYPE_LINUX_EMBEDDED)
	return timer_settime (m_stTimerId, flags, restrict_value, restrict_ovalue);
#else
	return 0;
#endif
}
