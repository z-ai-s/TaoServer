#include "util.h"

namespace Tao{

pid_t getThreadId(){
    return syscall(SYS_getpid);
}

uint32_t getFiberId(){
    return 0;
}

}