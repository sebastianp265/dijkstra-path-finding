#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct Q_Node
{
    int vertex;
    struct Q_Node *nextNode;
} Q_Node;

typedef struct Queue
{
    Q_Node *first;
    Q_Node *last;
    int size;
} Queue;

Queue *queue_init();

Q_Node *q_node_init(int vertex_index);

void queue_push(Queue *, int vertex);

void queue_pop(Queue *queue);

#endif