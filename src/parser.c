#include "parser.h"

int parse_parameters(Parser* parser, int argc, char* argv[]) {
    if (argc < 3) {
        PRINT_ERROR("argc should be at least 3");
        return -1;
    }
    parser->trace_file_path = argv[1];
    printf("trace file path: %s\n", argv[1]);

    if ((parser->policy = parse_policy(argv[2])) == POLICY_ERR) {
        PRINT_ERROR("Type correct scheduling policy");
        return -1;
    }
    printf("scheduling policy: %s\n", argv[2]);
    if (parser->policy == POLICY_MLFQ) {
        if (argc != 3 + PRIORITY_CNT) {
            PRINT_ERROR("Type 4 quantums for MLFQ policy");
            return -1;
        }
        parser->quantums = (unsigned int *)malloc(sizeof(unsigned int) * PRIORITY_CNT);
        for (int i = 0; i < PRIORITY_CNT; i++) {
            parser->quantums[i] = atoi(argv[i+3]);
        }
        printf("quantums (LOW, MID, HIGH, URGENT): %d, %d, %d, %d\n",
                parser->quantums[0], parser->quantums[1], parser->quantums[2], parser->quantums[3]);
    }
    else {
        parser->quantums = (unsigned int *)malloc(sizeof(unsigned int));
        if (parser->policy == POLICY_RR || parser->policy == POLICY_GUARANTEE) {
            if (argc != 4) {
                free(parser->quantums);
                PRINT_ERROR("Type 1 quantum for RR or GUARANTEE policy");
                return -1;
            }
            parser->quantums[0] = atoi(argv[3]);
            printf("quantum: %d\n", parser->quantums[0]);
        }
        else
            parser->quantums[0] = 1;
    }
    return 0;
}

SCHEDULING_POLICY parse_policy(char *c_policy) {
    if (strcmp(c_policy, "FIFO") == 0)
        return POLICY_FIFO;
    else if (strcmp(c_policy, "SJF") == 0)
        return POLICY_SJF;
    else if (strcmp(c_policy, "RR") == 0)
        return POLICY_RR;
    else if (strcmp(c_policy, "MLFQ") == 0)
        return POLICY_MLFQ;
    else if (strcmp(c_policy, "GUARANTEE") == 0)
        return POLICY_GUARANTEE;
    else 
        return POLICY_ERR;
}