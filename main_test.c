#include <stdio.h>
#include <malloc.h>

#include "test_src/test_graph_maker/generator_test.h"
#include "test_src/test_shortest_path_finder/path_test.h"

#include "test_src/print_tests.h"

int main()
{
    //test 1 - generator
    print_test_start(1,"generator");
    test_generator();
    //test 2 - graph
    print_test_start(2,"graph");
    test_graph();
    //test 3 - queue
    print_test_start(3,"queue");
    test_queue();
    //test 4 - path
    print_test_start(4,"path");
    test_path();
    //test 5 - priority_queue
    print_test_start(5,"priority_queue");
    test_priority_queue();
    //test 6 - stack
    print_test_start(6,"stack");
    test_stack();
    return 0;
}
