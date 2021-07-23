#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

typedef struct Parser {
    
    char *trace_file_path;
    SCHEDULING_POLICY policy;
    unsigned int* quantums;
} Parser;


int parse_parameters(Parser* parser, int argc, char* argv[]);
SCHEDULING_POLICY parse_policy(char *c_policy);

#endif