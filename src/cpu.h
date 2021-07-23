#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "parser.h"
#include "util.h"


typedef struct Cpu{
    SCHEDULING_POLICY policy;
    unsigned int *quantums; 
    unsigned long long process_time;
    Proc* running_process;
    unsigned int schedule_cnt;
    unsigned int quantum_cnt;
} Cpu;

int init_cpu(Parser* parameters);
void terminate_cpu();

/* is_cpu_busy
// : cpu에 현재 schedule된 process가 있는지 알 수 있는 함수
// parameter: x
// return: 있을 경우 참(1), 없을 경우 거짓(0)
*/
bool is_cpu_busy();

/* schedule_cpu
// : cpu에 파라미터로 전달하는 process를 schedule요청할 때 사용하는 함수
// parameter: schedule하고자 하는 process의 포인터
// return: x
*/
void schedule_cpu(Proc* process);

/* run_cpu
// : cpu가 한 cycle을 소화하도록 하는 함수 (매 cycle마다 실행되어야 함)
// parameter: x
// return: 현재 cycle에 만약 schedule되어있는 process가 있고 그 process가 사용해야할 또는 사용가능한 cycle을 모두 사용한 경우 참(1)
//         아니면 거짓(0)
*/
bool run_cpu();

/* unschedule_cpu
// : cpu에 현재 schedule되어 있는 process를 unschedule하고 싶을 때 사용하는 함수
// parameter: x
// return: unschedule한 process의 pointer      
*/
Proc* unschedule_cpu();




#endif