#ifndef PATH_TEST_H
#define PATH_TEST_H

#include "../../shortest_path_finder/path.h"

#include "../test_graph_maker/graph_test.h"
#include "priority_queue_test.h"
#include "stack_test.h"

#include "../print_tests.h"

#define DEBUG_PRINT_PATH 0

void test_path();
int test_dijkstra();
int is_dijkstra_result_correct(int *best_path, int length_of_path, Stack *stack);

int test_fill_input_from_string();
#endif