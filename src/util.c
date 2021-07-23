#include "util.h"

unsigned long long current_time;

unsigned long long get_current_time() {
    return current_time;
}

void increase_current_time() {
    INC_CNT(current_time);
}

void print_progress_bar(unsigned int ratio) {
    int cnt = 0;
    printf("[");
    for (; cnt < ratio; cnt+=5)
        printf("==");
    printf(">");
    for (cnt+=5; cnt <= 100; cnt+=5)
        printf("  ");
    printf("] %d %%\n\n", ratio);
}

FILE* open_file(char *file_path) {
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) 
        PRINT_ERROR("File open fail");
    return fp;
}

void close_file(FILE* fp) {
    if (fp) {
        fclose(fp);
        fp = NULL;
    }
}