#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H

#include "../../graph_maker/graph.h"

#include "queue_test.h"

#include "../print_tests.h"

void test_graph();
int test_bfs();
int test_initiate_and_free_graph();
int test_reverse_connections();
int test_is_graph_strongly_connected();
int test_creating_graph_from_file();

#endif