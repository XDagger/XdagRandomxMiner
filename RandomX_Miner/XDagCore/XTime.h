// Implementation of operation with time
// Author: Evgeniy Sukhomlinov
// 2018

// Licensed under GNU General Public License, Version 3. See the LICENSE file.

#pragma once
#ifdef _WIN32
#include "win\sys\time.h"
#else
#include <sys/time.h>
#endif
#include <stdint.h>

#define XDAG_MAIN_ERA	0x16940000000ll
#define MAIN_TIME(t)		((t) >> 16)

typedef uint64_t xdag_time_t;

inline uint64_t get_timestamp(void)
{
    timeval tp;
    gettimeofday(&tp, 0);
    return (uint64_t)(unsigned long)tp.tv_sec << 10 | ((tp.tv_usec << 10) / 1000000);
}

inline xdag_time_t GetMainTime()
{
    return MAIN_TIME(get_timestamp());
}
