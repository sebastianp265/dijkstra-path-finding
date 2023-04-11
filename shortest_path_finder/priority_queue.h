#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int node_num;       // number of the node
    double priority;    // cost of getting to the node
}Node;

#define START_CAPACITY 4

typedef struct Priority_queue   // priority_queue using heap structure
{
    Node **node;        // array of nodes 
    int size;           // number of nodes in the array
    int capacity;       // capacity of the array
}Priority_queue;

Node* initiate_node(int node_num,double priority);
void free_node(Node **node);
void free_priority_queue(Priority_queue **pq);
Priority_queue* initiate_priority_queue();
int push_priority_queue(Priority_queue *pq,Node *node);
Node* peek_priority_queue(Priority_queue *pq);
int pop_priority_queue(Priority_queue *pq);
int is_empty_priority_queue(Priority_queue *pq);

Node *get_copy_of_node(Node* node);


int decrease_priority_queue(Priority_queue *pq,int v,double cost_replace);




#endif