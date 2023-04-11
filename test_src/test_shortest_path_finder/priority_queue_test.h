#ifndef PRIORITY_QUEUE_TEST_H
#define PRIORITY_QUEUE_TEST_H

#include "../../shortest_path_finder/priority_queue.h"

#include "../print_tests.h"

#define NODE_ARRAY_SIZE 10

void test_priority_queue();
int test_initiate_and_free_node();
int test_initiate_and_free_priority_queue();
int test_push_priority_queue();
int test_peek_priority_queue();
int test_pop_priority_queue();

/*****************************************************************
**                  functions to help testing
******************************************************************/

Node **test_get_array_of_nodes();
int test_is_heap_complete_priority_queue();
double test_return_priority_of_node(Priority_queue *pq, int node_num);

#endif