#ifndef QUEUE_H_
#define QUEUE_H_

#include "src/process.h"
#include "src/defs.h"

typedef struct Node Node;

struct Node {
    Proc* data;
    Node* next;
    unsigned int wait_time;
};

typedef struct Queue {
    Node* first;
    Node* last;
} Queue;


Queue* init_Queue();
void push_Queue(Queue* q, Proc* proc);
Proc* pop_Queue(Queue* q);
bool is_Queue_empty(Queue* q);
Proc* choice_Queue(Queue* q, int(*comp)(Node*, Node*));
void travel_Queue(Queue* q, void job(Node *));

#endif