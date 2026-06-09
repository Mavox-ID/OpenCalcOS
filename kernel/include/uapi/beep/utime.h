#ifndef _BEEP_UTIME_H
#define _BEEP_UTIME_H

#include <beep/types.h>

struct utimbuf {
	__kernel_time_t actime;
	__kernel_time_t modtime;
};

#endif
