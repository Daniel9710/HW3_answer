#ifndef DEFS_H_
#define DEFS_H_

#define PRINT_ERROR(s) printf("%s\n", s)
#define PRINT_MSG(s) printf("%s\n", s)

#define INC_CNT(var) var++
#define DEC_CNT(var) var--

#define TRUE 1
#define FALSE 0

typedef enum SCHEDULING_POLICY {
    POLICY_FIFO,
    POLICY_SJF,
    POLICY_RR,
    POLICY_MLFQ,
    POLICY_GUARANTEE,
    POLICY_ERR
} SCHEDULING_POLICY;

#define IS_PREEMTIVE(policy) policy >= POLICY_RR

typedef enum PROCESS_PRIORITY {
    URGENT,
    HIGH,
    MID,
    LOW,
    PRIORITY_CNT
} PROCESS_PRIORITY;

typedef unsigned int bool;


#endif