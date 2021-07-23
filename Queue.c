#include "Queue.h"
#include <stdlib.h>

Queue* init_Queue() {
    Queue* res = (Queue*)malloc(sizeof(Queue));
    res->first = res->last = NULL;
    return res;
}

void push_Queue(Queue* q, Proc* proc) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = proc;
    n->wait_time = 0;
    n->next = NULL;

    if (q->first == NULL)
        q->last = q->first = n;
    else 
        q->last = q->last->next = n;
}

Proc* pop_Queue(Queue* q) {
    Proc* res = NULL;
    if (q->first) {
        Node *n = q->first;
        q->first = q->first->next;
        res = n->data;
        free(n);
    }
    return res;
}

bool is_Queue_empty(Queue* q) {
    return q->first == NULL;
}

Proc* choice_Queue(Queue* q, int(*comp)(Node*, Node*)){
    Proc* res = NULL;
    if (q->first) {
        Node* prev = NULL;
        Node* tmp = NULL;
        Node* n_prev = NULL;
        Node* n = q->first;

        while(n) {
            if (comp(tmp, n) == TRUE) {
                tmp = n;
                prev = n_prev;
            }
            n_prev = n;
            n = n->next;
        }
        if (tmp) {
            if (prev == NULL)
                q->first = tmp->next;
            else 
                prev->next = tmp->next;
            
            if (tmp == q->last)
                q->last = prev;

            res = tmp->data;
            free(tmp);
        }
    }
    return res;
}

void travel_Queue(Queue* q, void job(Node *)){
    Node* n = q->first;
    while(n) {
        job(n);
        n = n->next;
    }
}