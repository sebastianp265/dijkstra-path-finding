#include "priority_queue.h"

Priority_queue* initiate_priority_queue()
{
    Priority_queue *pq=(Priority_queue*)malloc(sizeof(Priority_queue));
    pq->size=0;
    pq->capacity=START_CAPACITY;
    pq->node=(Node**)malloc(pq->capacity*sizeof(Node*));
    return pq;
}

void free_priority_queue(Priority_queue **pq)
{
    for(int i=0;i<(*pq)->size;i++)
    {
        free_node(&(*pq)->node[i]);
    }
    free((*pq)->node);
    (*pq)->node=NULL;
    free((*pq));
    (*pq)=NULL;
}

Node* initiate_node(int node_num,double priority)
{
    Node *node=(Node*)malloc(sizeof(Node));
    node->node_num=node_num;
    node->priority=priority;
    return node;
}

void free_node(Node **node)
{
    free(*node);
    *node=NULL;
}

Node* peek_priority_queue(Priority_queue *pq)
{
    if(pq->size>0)
        return pq->node[0];
    else
        return NULL;
}

int is_empty_priority_queue(Priority_queue *pq)
{
    return !pq->size;
}

int push_priority_queue(Priority_queue *pq,Node *node)
{
    if(pq==NULL)
    {
        return 1;
    }
    if(node==NULL)
    {
        return 2;
    }
    if(pq->capacity==0)
    {
        return 3;
    }

    if(pq->size+1>pq->capacity) //not enough space in the queue -- needs expanding
    {
        pq->capacity*=2;    //double the capacity
        pq->node=(Node**)realloc(pq->node,pq->capacity*sizeof(Node*));
    }

    pq->node[pq->size]=node;    //  add node to a heap
    pq->size++;                 //  number of elements in heap increases
    int index=pq->size-1;
    while(index!=0)//heap up
    {
        if(pq->node[(index-1)/2]->priority > pq->node[index]->priority)
        {
            Node *temp=pq->node[(index-1)/2];
            pq->node[(index-1)/2]=pq->node[index];
            pq->node[index]=temp;
            index=(index-1)/2;
        }
        else break;
    }
    return 0;
}

int decrease_priority_queue(Priority_queue *pq,int v,double priority_replace)
{
    int index=-1;
    for(int i=0;i<pq->size;i++)// search for node v
    {
        if(pq->node[i]->node_num==v)
        {
            pq->node[i]->priority=priority_replace;
            index = i;
        }
    }
    if(index==-1)   // if index hasn't changed then node v wasn't in queue
    {
        return 1;
    }
    while(index!=0)//heap up
    {
        if(pq->node[(index-1)/2]->priority > pq->node[index]->priority)
        {
            Node *temp=pq->node[(index-1)/2];
            pq->node[(index-1)/2]=pq->node[index];
            pq->node[index]=temp;
            index=(index-1)/2;
        }
        else break;
    }
    return 0;
}

int pop_priority_queue(Priority_queue *pq)
{
    if(pq->size==1)
    {
        free_node(&pq->node[pq->size-1]);
        pq->node[0]=NULL;
        pq->size--;
    }
    else
    {
        free_node(&pq->node[0]);
        pq->node[0]=get_copy_of_node(pq->node[pq->size-1]);
        free_node(&pq->node[pq->size-1]);
        pq->size--;
        int index=0;
        while(index<pq->size)   //heap down
        {
            if(2*index+1<pq->size) // is there a left child
            {
                if(2*index+2<pq->size) //is there a right child
                {
                    if(pq->node[2*index+1]->priority < pq->node[2*index+2]->priority)// if left child has smaller priority than right one
                    {
                        if(pq->node[2*index+1]->priority < pq->node[index]->priority) // if smaller child is smaller than current index - swap them
                        {
                            Node* temp=pq->node[2*index+1];
                            pq->node[2*index+1]=pq->node[index];
                            pq->node[index]=temp;
                            index=2*index+1;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if(pq->node[2*index+2]->priority < pq->node[index]->priority) // if smaller child is smaller than current index - swap them
                        {
                            Node* temp=pq->node[2*index+2];
                            pq->node[2*index+2]=pq->node[index];
                            pq->node[index]=temp;
                            index=2*index+2;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if(pq->node[2*index+1]->priority < pq->node[index]->priority) // if left child is smaller than current index - swap them
                    {
                        Node* temp=pq->node[2*index+1];
                        pq->node[2*index+1]=pq->node[index];
                        pq->node[index]=temp;
                        index=2*index+1;
                    }
                    else break;
                }
            }
            else    // if there arent any children it is correct place for this element
            {
                break;
            }
        }
    }
    return 0;
}

Node *get_copy_of_node(Node* node)
{
    Node *temp=(Node*)malloc(sizeof(Node));
    temp->node_num=node->node_num;
    temp->priority=node->priority;
    return temp;
}

