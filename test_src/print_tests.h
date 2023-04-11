#ifndef PRINT_TESTS_H
#define PRINT_TESTS_H
#include <stdio.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET_COLOR "\033[0m"

void print_test_start(int num_of_test, char *module_name);

void print_subtest_fail(int test_num, int subtest_num, char *message, int error_code);

void print_subtest_success(int test_num, int subtest_num);

void print_subtest_start(int test_num, int subtest_num, char *test_description);

#endif