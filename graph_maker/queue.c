#include "queue.h"

Queue *queue_init()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        return NULL;
    }
    queue->first = NULL;
    queue->last = NULL;
    queue->size = 0;
    return queue;
}

Q_Node *q_node_init(int vertex_index)
{
    Q_Node *node = (Q_Node *)malloc(sizeof(Q_Node));
    if (node == NULL)
    {
        return NULL;
    }
    node->vertex = vertex_index;
    node->nextNode = NULL;
    return node;
}

void queue_push(Queue *queue, int vertex_index)
{
    Q_Node *new_node = q_node_init(vertex_index);

    if (queue->size == 0)
    {
        queue->first = new_node;
        queue->last = new_node;
    }
    else
    {
        queue->last->nextNode = new_node;
        queue->last = new_node;
    }
    queue->size++;
    return;
}

void queue_pop(Queue *queue)
{
    if (queue->size == 0)
    {
        free(queue);
        return;
    }

    Q_Node *taken_node = queue->first;
    queue->first = queue->first->nextNode;

    if (queue->first == NULL)
        queue->last = NULL;

    queue->size--;
    free(taken_node);
}
