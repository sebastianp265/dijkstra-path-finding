#ifndef GENERATOR_TEST_H
#define GENERATOR_TEST_H

#include "../../graph_maker/generator.h"

#include "graph_test.h"

#include "../print_tests.h"

void test_generator();

int test_check_if_can_be_opened();

int test_generate_graph_where_all_connections_exist();

int test_generate_graph_randomly_till_its_connected();

int test_generate_graph_randomly();

#endif