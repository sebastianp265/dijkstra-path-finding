#include "stack.h"

void push_stack(Stack **top_of_stack, int number_of_node,double distance)
{
    if((*top_of_stack)==NULL)
    {
        (*top_of_stack)=(Stack*)malloc(sizeof(Stack));
        (*top_of_stack)->number_of_node=number_of_node;
        (*top_of_stack)->distance=distance;
        (*top_of_stack)->prev=NULL;
    }
    else
    {
        Stack *new_stack_elem=(Stack*)malloc(sizeof(Stack));
        new_stack_elem->number_of_node=number_of_node;
        new_stack_elem->distance=distance;
        new_stack_elem->prev=NULL;
        Stack *temp=(*top_of_stack);
        (*top_of_stack)=new_stack_elem;
        (*top_of_stack)->prev=temp;
    }
}

void pop_stack(Stack **top_of_stack)
{
    if((*top_of_stack)!=NULL)
    {   
        Stack *temp;
        if((*top_of_stack)->prev!=NULL)
        {
            temp=(*top_of_stack)->prev;
        }
        else
        {
            temp=NULL;
        }
        free((*top_of_stack));
        *top_of_stack=NULL;
        *(top_of_stack)=temp;
    }
}

void free_stack(Stack **top_of_stack)
{
    Stack *temp;
    if(*top_of_stack==NULL)
        return;
    while((*top_of_stack)->prev!=NULL)
    {
        temp=(*top_of_stack)->prev;
        free((*top_of_stack));
        (*top_of_stack)=temp;
    }
    free(*top_of_stack);
    *top_of_stack=NULL;
}

void print_basic_path(Stack *top_of_stack,int start,int end)
{
    if(top_of_stack==NULL)
    {
        printf("Nie istnieje droga z wierzchołka o nr %d do wierzchołka o nr %d!\n",start,end);
        return;
    }
    printf("(%d,%d):",start,end);
    while(top_of_stack->prev!=NULL)  // while 
    {
        printf("%d->",top_of_stack->number_of_node);
        pop_stack(&top_of_stack);
    }
    printf("%d\n",top_of_stack->number_of_node);
    pop_stack(&top_of_stack);
}

void print_extended_answer(Stack *top_of_stack,int start,int end)
{
    if(top_of_stack==NULL)
    {
        printf("Nie istnieje droga z wierzchołka o nr %d do wierzchołka o nr %d!\n",start,end);
        return;
    }
    printf("(%d,%d):",start,end);
    while(top_of_stack->prev!=NULL)  // while top_of_stack is not empty
    {
        printf("%d(%.2lf)->",top_of_stack->number_of_node,top_of_stack->prev->distance);
        pop_stack(&top_of_stack);
    }
    printf("%d\n",top_of_stack->number_of_node);
    pop_stack(&top_of_stack);
}