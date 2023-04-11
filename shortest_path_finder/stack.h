#ifndef STACK_H
#define STACK_H

#include "stdio.h"
#include "stdlib.h"
typedef struct Stack
{
    int number_of_node;
    double distance;
    struct Stack *prev;
} Stack;
// algoritms for putting on stack and taking from stack are needed
// we need to reverse the output from "prev" array to a "simple to print out" form

void push_stack(Stack **top_of_stack, int number_of_node, double distance);

void pop_stack(Stack **top_of_stack);

void free_stack(Stack **top_of_stack);

void print_basic_path(Stack *top_of_stack, int start, int end); // prints shortest path without printing the weights

void print_extended_answer(Stack *top_of_stack, int start, int end); // prints shortest path with weights

#endif