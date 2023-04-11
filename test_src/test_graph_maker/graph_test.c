#include "graph_test.h"

void test_graph()
{
    int error_code;
    int subtest_num;
    int test_num;
    // test 2
    test_num = 2;
    // subtest 1
    subtest_num = 1;
    print_subtest_start(test_num, subtest_num, "algorytm bfs");
    if ((error_code = test_bfs()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Dla spójnego grafu algorytm bfs pokazał, że jest on niespójny", error_code);
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
    print_subtest_start(test_num, subtest_num, "inicjowanie pamięci dla grafu i jej uwalnianie");
    if ((error_code = test_initiate_and_free_graph()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało sie zaalokować pamięci dla grafu!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Zaainicjowany graf posiada niewłaściwą liczbę wierszy, kolumn!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Wskaźnik po uwolnieniu pamięci powinien mieć wartość NULL!", error_code);
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
    // subtest 3
    subtest_num = 3;
    print_subtest_start(test_num, subtest_num, "odwracanie połączeń pomiędzy wierzchołkami");
    if ((error_code = test_reverse_connections()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Graf po odwróceniu połączeń jest inny niż oczekiwany!", error_code);
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
    // subtest 4
    subtest_num = 4;
    print_subtest_start(test_num, subtest_num, "sprawdzanie silnej spójności");
    if ((error_code = test_is_graph_strongly_connected()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Dany w testach graf jest silnie niespójny, a wynik okazał się inny!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Dany w testach graf jest silnie spójny, a wynik okazał się inny!", error_code);
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
    // subtest 5
    subtest_num = 5;
    print_subtest_start(test_num, subtest_num, "testowanie tworzenia grafu z pliku");
    if ((error_code = test_creating_graph_from_file()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Plik o prawidłowym formacie został rozpoznany jako zły!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Plik o nieprawidłowym formacie został rozpoznany jako dobry!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Plik o nieprawidłowym formacie został rozpoznany jako dobry!", error_code);
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
}

int test_bfs()
{
    Graph *graph = initiate_graph(3, 3);

    graph->adjacency_matrix[0][RIGHT] = 1;
    graph->adjacency_matrix[1][RIGHT] = 1;

    graph->adjacency_matrix[0][DOWN] = 1;

    graph->adjacency_matrix[3][RIGHT] = 1;
    graph->adjacency_matrix[4][RIGHT] = 1;

    graph->adjacency_matrix[3][DOWN] = 1;

    graph->adjacency_matrix[6][RIGHT] = 1;
    graph->adjacency_matrix[7][RIGHT] = 1;

    if (bfs(graph, 0) != 1)
    {
        free_graph(&graph);
        return 1;
    }

    free_graph(&graph);
    return 0;
}

int test_initiate_and_free_graph()
{
    Graph *graph = initiate_graph(5, 10);
    if (graph == NULL)
    {
        return 1;
    }
    if (graph->number_of_rows != 5 || graph->number_of_columns != 10)
    {
        return 2;
    }
    free_graph(&graph);
    if (graph != NULL)
    {
        return 3;
    }
    return 0;
}

int test_reverse_connections()
{
    Graph *graph1 = initiate_graph(4, 3);
    graph1->adjacency_matrix[0][RIGHT] = true;
    graph1->adjacency_matrix[0][DOWN] = true;

    graph1->adjacency_matrix[1][RIGHT] = true;
    graph1->adjacency_matrix[2][DOWN] = true;
    graph1->adjacency_matrix[4][UP] = true;
    graph1->adjacency_matrix[5][LEFT] = true;
    graph1->adjacency_matrix[7][LEFT] = true;
    graph1->adjacency_matrix[8][UP] = true;
    graph1->adjacency_matrix[9][RIGHT] = true;
    graph1->adjacency_matrix[10][RIGHT] = true;

    Graph *expected_res1 = initiate_graph(4, 3);
    expected_res1->adjacency_matrix[1][LEFT] = true;
    expected_res1->adjacency_matrix[1][DOWN] = true;
    expected_res1->adjacency_matrix[2][LEFT] = true;
    expected_res1->adjacency_matrix[3][UP] = true;
    expected_res1->adjacency_matrix[4][RIGHT] = true;
    expected_res1->adjacency_matrix[5][UP] = true;
    expected_res1->adjacency_matrix[5][DOWN] = true;
    expected_res1->adjacency_matrix[6][RIGHT] = true;
    expected_res1->adjacency_matrix[10][LEFT] = true;
    expected_res1->adjacency_matrix[11][LEFT] = true;

    reverse_connections(graph1);

    for (int i = 0; i < 12; i++)
    {
        if (graph1->adjacency_matrix[i][RIGHT] != expected_res1->adjacency_matrix[i][RIGHT])
        {
            free_graph(&graph1);
            free_graph(&expected_res1);
            return 1;
        }
        if (graph1->adjacency_matrix[i][UP] != expected_res1->adjacency_matrix[i][UP])
        {
            free_graph(&graph1);
            free_graph(&expected_res1);
            return 1;
        }
        if (graph1->adjacency_matrix[i][LEFT] != expected_res1->adjacency_matrix[i][LEFT])
        {
            free_graph(&graph1);
            free_graph(&expected_res1);
            return 1;
        }
        if (graph1->adjacency_matrix[i][DOWN] != expected_res1->adjacency_matrix[i][DOWN])
        {
            free_graph(&graph1);
            free_graph(&expected_res1);
            return 1;
        }
    }
    free_graph(&graph1);
    free_graph(&expected_res1);
    return 0;
}

int test_is_graph_strongly_connected()
{
    Graph *graph1 = initiate_graph(4, 3);
    graph1->adjacency_matrix[0][RIGHT] = true;
    graph1->adjacency_matrix[0][DOWN] = true;
    graph1->adjacency_matrix[1][RIGHT] = true;
    graph1->adjacency_matrix[2][DOWN] = true;
    graph1->adjacency_matrix[4][UP] = true;
    graph1->adjacency_matrix[5][LEFT] = true;
    graph1->adjacency_matrix[7][LEFT] = true;
    graph1->adjacency_matrix[8][UP] = true;
    graph1->adjacency_matrix[9][RIGHT] = true;
    graph1->adjacency_matrix[10][RIGHT] = true;

    if (is_graph_strongly_connected(graph1) == 1)
    {
        free_graph(&graph1);
        return 1;
    }
    free_graph(&graph1);

    Graph *graph2 = initiate_graph(4, 3);
    graph2->adjacency_matrix[0][RIGHT] = true;
    graph2->adjacency_matrix[0][DOWN] = true;
    graph2->adjacency_matrix[1][RIGHT] = true;
    graph2->adjacency_matrix[2][DOWN] = true;
    graph2->adjacency_matrix[3][UP] = true;
    graph2->adjacency_matrix[4][LEFT] = true;
    graph2->adjacency_matrix[4][DOWN] = true;
    graph2->adjacency_matrix[4][UP] = true;
    graph2->adjacency_matrix[5][LEFT] = true;
    graph2->adjacency_matrix[6][DOWN] = true;
    graph2->adjacency_matrix[7][LEFT] = true;
    graph2->adjacency_matrix[8][UP] = true;
    graph2->adjacency_matrix[8][LEFT] = true;
    graph2->adjacency_matrix[9][RIGHT] = true;
    graph2->adjacency_matrix[9][UP] = true;
    graph2->adjacency_matrix[10][RIGHT] = true;
    graph2->adjacency_matrix[11][UP] = true;

    if (is_graph_strongly_connected(graph2) == 0)
    {
        free_graph(&graph2);
        return 2;
    }
    free_graph(&graph2);
    return 0;
}

int test_creating_graph_from_file()
{
    Graph *graph1;
    char error_code[LINE_BUFFER_SIZE];
    if (create_graph_from_file(&graph1, "test_src/test_data/test_create.txt", error_code) != 0)
    {
        return 1;
    }
    free_graph(&graph1);
    Graph *graph2;
    if (create_graph_from_file(&graph2, "test_src/test_data/test_create_fail1.txt", error_code) == 0)
    {
        free_graph(&graph2);
        return 2;
    }
    Graph *graph3;
    if (create_graph_from_file(&graph3, "test_src/test_data/test_create_fail2.txt", error_code) == 0)
    {
        free_graph(&graph3);
        return 2;
    }

    return 0;
}