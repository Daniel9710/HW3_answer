#ifndef PROCESS_H_
#define PROCESS_H_

#include "defs.h"


typedef struct Proc{
    unsigned int pid;
    unsigned int create_time;
    unsigned int required_time;
    unsigned int process_time;
    PROCESS_PRIORITY priority;
} Proc;


#endif