#include "cpu.h"

Cpu* g_cpu;

int init_cpu(Parser* parameters) {
    if ((g_cpu = (Cpu*)malloc(sizeof(Cpu))) < 0) {
        PRINT_ERROR("INIT_CPU: FAIL");
        return -1;
    }
    g_cpu->policy = parameters->policy;
    g_cpu->quantums = parameters->quantums;
    g_cpu->process_time = 0;
    g_cpu->running_process = NULL;
    g_cpu->schedule_cnt = 0;
    PRINT_MSG("INIT_CPU: OK");
    return 0;
}
void terminate_cpu() {
    free(g_cpu->quantums);
    free(g_cpu);
    PRINT_MSG("TERMINATE_CPU: OK");
}

bool is_cpu_busy() {
    return (g_cpu->running_process != NULL);
}

void schedule_cpu(Proc* process) {
    if (g_cpu->running_process) {
        PRINT_ERROR("CPU already busy");
        exit(-1);
    }
    else if (process == NULL) {
        PRINT_ERROR("There is no process to schedule");
        exit(-1);
    }
    INC_CNT(g_cpu->schedule_cnt);
    g_cpu->running_process = process;

    switch (g_cpu->policy) {
        case POLICY_MLFQ:
            g_cpu->quantum_cnt = g_cpu->quantums[process->priority];
        break;
        case POLICY_RR:
        case POLICY_GUARANTEE:
            g_cpu->quantum_cnt = g_cpu->quantums[0];
        break;
        default:
            g_cpu->quantum_cnt = g_cpu->running_process->required_time;
        break;
    }
}

bool run_cpu() {
    Proc* cur_process = g_cpu->running_process;
    if (cur_process) {
        if (IS_PREEMTIVE(g_cpu->policy)) {
            if (g_cpu->quantum_cnt == 0) {
                PRINT_ERROR("The process use all quantum to process");
                exit(-1);
            }
            DEC_CNT(g_cpu->quantum_cnt);
        }
        INC_CNT(cur_process->process_time);
        INC_CNT(g_cpu->process_time);
    }
    return (cur_process && (cur_process->process_time == cur_process->required_time || g_cpu->quantum_cnt == 0));
}

Proc* unschedule_cpu() {
    Proc* res = g_cpu->running_process;
    if (res == NULL) {
        PRINT_ERROR("CPU has no process");
        exit(-1);
    }
    if (IS_PREEMTIVE(g_cpu->policy) && res->process_time != res->required_time && g_cpu->quantum_cnt > 0) {
        PRINT_ERROR("Warning: The process didn't fully use the quantum.");
    }
    g_cpu->running_process = NULL;
    return res;
}
