#include "print_tests.h"

void print_test_start(int test_num, char *module_name)
{
    printf(RESET_COLOR);
    printf("Rozpoczęto test nr %d - moduł %s\n", test_num, module_name);
}

void print_subtest_fail(int test_num, int subtest_num, char *message, int error_code)
{
    printf(RED);
    fprintf(stderr, "\t\tTest nr %d.%d nie przebiegł pomyślnie:\n", test_num, subtest_num);
    fprintf(stderr, "\t\t%s\n", message);
    fprintf(stderr, "\t\tFunkcja nr %d.%d zwróciła kod błędu = %d\n", test_num, subtest_num, error_code);
}

void print_subtest_success(int test_num, int subtest_num)
{
    printf(GREEN);
    printf("\t\tTest nr %d.%d przebiegł pomyślnie!\n", test_num, subtest_num);
}

void print_subtest_start(int test_num, int subtest_num, char *test_description)
{
    printf(RESET_COLOR);
    printf("\tRozpoczęto test %d.%d - %s\n", test_num, subtest_num, test_description);
}
