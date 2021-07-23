#include "host.h"

Host* g_host;

int init_host(Parser* parameters) {
    if ((g_host = (Host*)malloc(sizeof(Host))) == NULL) {
        PRINT_ERROR("INIT_HOST: FAIL");
        return -1;
    }
    if ((g_host->trace_file = open_file(parameters->trace_file_path)) == NULL) {
        free(g_host);
        PRINT_ERROR("INIT_HOST: FAIL");
        return -1;
    }
    g_host->next_process = NULL;
    g_host->finish = FALSE;
    fscanf(g_host->trace_file, " %lld", &g_host->total_request_cnt);
    g_host->request_cnt = 0;
    g_host->service_cnt = 0;
    g_host->turnaround_time = 0;
    g_host->progress_cnt = 0;
    PRINT_MSG("INIT_HOST: OK");
    return 0;
}

void terminate_host() {
    close_file(g_host->trace_file);
    free(g_host);
    PRINT_MSG("TERMINATE_HOST: OK");
}

bool is_simulation_on_going() {
    int progress = (int)(g_host->service_cnt / (double)g_host->total_request_cnt * 100);
    if (progress >= g_host->progress_cnt) {
        print_progress_bar(progress);
        while (progress >= g_host->progress_cnt)
            g_host->progress_cnt += 5;
    }    
    return (g_host->service_cnt < g_host->total_request_cnt);
}

Proc* create_if_next_process_available(){
    Proc* next_process = NULL;
    if (g_host->finish == FALSE) {
        if (g_host->next_process == NULL) {
            if ((next_process = (Proc*)malloc(sizeof(Proc))) == NULL) {
                PRINT_ERROR("malloc error");
                exit(-1);
            }
            unsigned int priority;
            if (fscanf(g_host->trace_file, " %d %d %d", &next_process->create_time, &next_process->required_time, &priority) == EOF) {
                free(next_process);
                g_host->finish = TRUE;
                return NULL;
            }
            next_process->priority = priority;
            g_host->next_process = next_process;
            next_process = NULL;
        }
        if (g_host->next_process->create_time <= get_current_time()) {
            g_host->next_process->process_time = 0;
            g_host->next_process->pid = g_host->request_cnt++;
            next_process = g_host->next_process;
            g_host->next_process = NULL;
        }
    } 
    return next_process;
}

void terminate_process(Proc* candidate_process) {
    if (candidate_process->process_time != candidate_process->required_time) {
        PRINT_ERROR("candidate_process didn't complete");
        exit(-1);
    }
    INC_CNT(g_host->service_cnt);
    g_host->turnaround_time += get_current_time() - candidate_process->create_time + 1;
    free(candidate_process);
}
