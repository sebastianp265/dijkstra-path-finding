#include "path_test.h"

void test_path()
{
    int error_code;
    int subtest_num;
    int test_num;
    // test 4
    test_num = 4;
    // subtest 1
    subtest_num = 1;
    print_subtest_start(test_num, subtest_num, "Testowanie algorytmu dijkstry");
    if ((error_code = test_dijkstra()))
    {
        if (error_code >= 1 && error_code <= 7)
        {
            print_subtest_fail(test_num, subtest_num, "Otrzymana najkrótsza ścieżka jest inna niż oczekiwana!", error_code);
        }
        else
        {
            print_subtest_fail(test_num, subtest_num, "Niezdefiniowany błąd!", error_code);
        }
    }
    else
    {
        print_subtest_success(test_num, subtest_num);
    }
    // subtest 2
    subtest_num = 2;
    print_subtest_start(test_num, subtest_num, "Odczytywanie wierzchołków z formatu wejściowego");
    if ((error_code = test_fill_input_from_string()))
    {
        if (error_code >= 1 && error_code <= 9)
        {
            print_subtest_fail(test_num, subtest_num, "Otrzymany wynik jest inny niż oczekiwany!", error_code);
        }
    }
    else
    {
        print_subtest_success(test_num, subtest_num);
    }
}

int test_dijkstra()
{
    Graph *graph = initiate_graph(3, 3);
    /*
        graph:
              0.1    0.2
            0 ---> 1 ---> 2
         0.3|
            V 0.5    0.7
            3 ---> 4 ---> 5
         0.2|      ^      ^
            V 0.1  |0.1   |0.2
            6 ---> 7 ---> 8
                    0.1
    */
    graph->weight[0][RIGHT] = 0.1;
    graph->adjacency_matrix[0][RIGHT] = 1;

    graph->weight[0][DOWN] = 0.3;
    graph->adjacency_matrix[0][DOWN] = 1;

    graph->weight[1][RIGHT] = 0.2;
    graph->adjacency_matrix[1][RIGHT] = 1;

    graph->weight[3][RIGHT] = 0.5;
    graph->adjacency_matrix[3][RIGHT] = 1;

    graph->weight[3][DOWN] = 0.2;
    graph->adjacency_matrix[3][DOWN] = 1;

    graph->weight[4][RIGHT] = 0.7;
    graph->adjacency_matrix[4][RIGHT] = 1;

    graph->weight[6][RIGHT] = 0.1;
    graph->adjacency_matrix[6][RIGHT] = 1;

    graph->weight[7][RIGHT] = 0.1;
    graph->adjacency_matrix[7][RIGHT] = 1;

    graph->weight[7][UP] = 0.1;
    graph->adjacency_matrix[7][UP] = 1;

    graph->weight[8][UP] = 0.2;
    graph->adjacency_matrix[8][UP] = 1;

    /*
        graph:
              0.1    0.2
            0 ---> 1 ---> 2
         0.3|
            V 0.5    0.7
            3 ---> 4 ---> 5
         0.2|      ^      ^
            V      |0.1   |0.2
            6 ---> 7 ---> 8
              0.1    0.1
    */

    Dijkstra_result *result = dijkstra(graph, 0);
    Stack *path1 = fill_stack_from_dijkstra(result, 8);
    int path_from_0_to_8[5] = {0, 3, 6, 7, 8}; // best path from node 0 to node 8
    if (!(is_dijkstra_result_correct(path_from_0_to_8, 5, path1)))
        return 1;
#if DEBUG_PRINT_PATH == 1 // printing answer frees memory (we avoid freeing too many times)
    print_extended_answer(path1, 0, 8);
#else
    free_stack(&path1);
#endif

    Stack *path2 = fill_stack_from_dijkstra(result, 0);
    int path_from_0_to_0[1] = {0}; // best path from node 0 to node 0
    if (!(is_dijkstra_result_correct(path_from_0_to_0, 1, path2)))
        return 2;
#if DEBUG_PRINT_PATH == 1
    print_extended_answer(path2, 0, 0);
#else
    free_stack(&path2);
#endif

    Stack *path3 = fill_stack_from_dijkstra(result, 2);
    int path_from_0_to_2[3] = {0, 1, 2}; // best path from node 0 to node 2
    if (!(is_dijkstra_result_correct(path_from_0_to_2, 3, path3)))
        return 3;
#if DEBUG_PRINT_PATH == 1
    print_extended_answer(path3, 0, 2);
#else
    free_stack(&path3);
#endif

    Stack *path4 = fill_stack_from_dijkstra(result, 5);
    int path_from_0_to_5[6] = {0, 3, 6, 7, 8, 5}; // best path from node 0 to node 5
    if (!(is_dijkstra_result_correct(path_from_0_to_5, 6, path4)))
        return 4;
#if DEBUG_PRINT_PATH == 1
    print_extended_answer(path4, 0, 5);
#else
    free_stack(&path4);
#endif

    free_dijkstra_result(&result);
    free_graph(&graph);

    graph = initiate_graph(2, 5);

    /*
        graph:
              0.1    0.2     0.9    0.2
            0 ---> 1 ---> 2 ---> 3 ---> 4
         0.2|             ^      ^      |0.1
            V          0.3|   0.1|      V
            5 ---> 6 ---> 7 ---> 8 ---> 9
              0.2    0.3     0.1    0.8
    */

    graph->weight[0][RIGHT] = 0.1;
    graph->adjacency_matrix[0][RIGHT] = 1;

    graph->weight[0][DOWN] = 0.2;
    graph->adjacency_matrix[0][DOWN] = 1;

    graph->weight[1][RIGHT] = 0.2;
    graph->adjacency_matrix[1][RIGHT] = 1;

    graph->weight[2][RIGHT] = 0.9;
    graph->adjacency_matrix[2][RIGHT] = 1;

    graph->weight[3][RIGHT] = 0.2;
    graph->adjacency_matrix[3][RIGHT] = 1;

    graph->weight[4][DOWN] = 0.1;
    graph->adjacency_matrix[4][DOWN] = 1;

    graph->weight[5][RIGHT] = 0.2;
    graph->adjacency_matrix[5][RIGHT] = 1;

    graph->weight[6][RIGHT] = 0.3;
    graph->adjacency_matrix[6][RIGHT] = 1;

    graph->weight[7][RIGHT] = 0.1;
    graph->adjacency_matrix[7][RIGHT] = 1;

    graph->weight[7][UP] = 0.3;
    graph->adjacency_matrix[7][UP] = 1;

    graph->weight[8][RIGHT] = 0.8;
    graph->adjacency_matrix[8][RIGHT] = 1;

    graph->weight[8][UP] = 0.1;
    graph->adjacency_matrix[8][UP] = 1;

    result = dijkstra(graph, 0);

    /*
        graph:
              0.1    0.2     0.9    0.2
            0 ---> 1 ---> 2 ---> 3 ---> 4
         0.2|             ^      ^      |0.1
            V          0.3|   0.1|      V
            5 ---> 6 ---> 7 ---> 8 ---> 9
              0.2    0.3     0.1    0.8
    */

    Stack *path5 = fill_stack_from_dijkstra(result, 9);
    int path_from_0_to_9[8] = {0, 5, 6, 7, 8, 3, 4, 9};
    if (!(is_dijkstra_result_correct(path_from_0_to_9, 8, path5)))
        return 5;
#if DEBUG_PRINT_PATH == 1
    print_extended_answer(path5, 0, 9);
#else
    free_stack(&path5);
#endif

    free_dijkstra_result(&result);

    result = dijkstra(graph, 1); // filling result with paths from 1

    Stack *path6 = fill_stack_from_dijkstra(result, 0);
    if (path6 != NULL)
        return 6;
#if DEBUG_PRINT_PATH == 1
    print_extended_answer(path6, 1, 0);
#else
    free_stack(&path6);
#endif

    Stack *path7 = fill_stack_from_dijkstra(result, 6);
    if (path7 != NULL)
        return 7;
#if DEBUG_PRINT_PATH == 1
    print_extended_answer(path7, 1, 6);
#else
    free_stack(&path7);
#endif

    free_dijkstra_result(&result);

    free_graph(&graph);
    return 0;
}

int is_dijkstra_result_correct(int *best_path, int length_of_path, Stack *stack)
{
    if (stack == NULL)
    {
        return 0;
    }
    int i = 0;
    while (i < length_of_path)
    {
        if (best_path[i] != stack->number_of_node) // if path differs from expected then result is not correct (0)
        {
            return 0;
        }
        i++;
        stack = stack->prev;
    }
    return 1;
}

int test_fill_input_from_string()
{
    char *str = "0-12,52-3,1-3,3-161"; // correct input
    char *ptr = str;
    Node_pair_input *pair = fill_input_from_string(&ptr);
    if (!(pair->start == 0 && pair->end == 12))
    {
        return 1;
    }
    free(pair);
    pair = fill_input_from_string(&ptr);
    if (!(pair->start == 52 && pair->end == 3))
    {
        return 2;
    }
    free(pair);
    pair = fill_input_from_string(&ptr);
    if (!(pair->start == 1 && pair->end == 3))
    {
        return 3;
    }
    free(pair);
    pair = fill_input_from_string(&ptr);
    if (!(pair->start == 3 && pair->end == 161))
    {
        return 4;
    }
    free(pair);
    if (*ptr != '\0')
    {
        return 5;
    }

    ptr = "x-12,3-9";
    pair = fill_input_from_string(&ptr);
    if (pair != NULL)
    {
        free(pair);
        return 6;
    }
    ptr = "01-2,5-2";
    pair = fill_input_from_string(&ptr);
    if (pair != NULL)
    {
        free(pair);
        return 7;
    }
    ptr = "3-2,5-";
    pair = fill_input_from_string(&ptr);
    if (!(pair->start == 3 && pair->end == 2))
    {
        return 8;
    }
    free(pair);
    pair = fill_input_from_string(&ptr);
    if (pair != NULL)
    {
        free(pair);
        return 9;
    }
    return 0;
}