#ifndef _HEADER_IN_SYS_H_
#define _HEADER_IN_SYS_H_


#define OS_TYPE_LINUX_EMBEDDED  1
#define OS_TYPE_LINUX_DESKTOP   2
#define OS_TYPE_WINDOWS         3
#ifdef WIN32
#define OS_TYPE_CODE            OS_TYPE_WINDOWS
#else
#ifdef __XENO__
#define OS_TYPE_CODE            OS_TYPE_LINUX_EMBEDDED//OS_TYPE_LINUX_DESKTOP
#else
#define OS_TYPE_CODE			OS_TYPE_LINUX_DESKTOP
#endif
#endif
#include <memory.h>


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


#include <memory.h>
#ifdef WIN32
#include "./pthread_win32/Pre-built.2/include/pthread.h"
#include "./pthread_win32/Pre-built.2/include/semaphore.h"
#else
#include <pthread.h>
#include <semaphore.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/timeb.h>
#ifndef WIN32
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#else
#ifdef WIN32
typedef int _kernel_clockid_t; 
typedef _kernel_clockid_t clockid_t;

typedef int _kernel_timer_t;
typedef _kernel_timer_t timer_t;

#define CLOCK_PROCESS_CPUTIME_ID	2
#define CLOCK_THREAD_CPUTIME_ID		3
#define CLOCK_MONOTONIC_RAW			4
#define CLOCK_REALTIME				5 //Ô­Ñù£ºCLOCK_REALTIME_COARSE
#define CLOCK_MONOTONIC_COARSE		6
#endif
#endif
#include <list>

using namespace std;

#endif /*_HEADER_IN_SYS_H_*/
