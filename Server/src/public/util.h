#ifndef __TAO_UTIL_H__
#define __TAO_UTIL_H__

#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <pthread.h>

namespace Tao{

pid_t getThreadId();
uint32_t getFiberId();

}


#endif