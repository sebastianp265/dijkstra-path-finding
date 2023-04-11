#include "generator_test.h"

void test_generator()
{
    int error_code;
    int subtest_num;
    int test_num;
    // test 1
    test_num = 1;
    // subtest 1
    subtest_num = 1;
    print_subtest_start(test_num, subtest_num, "sprawdzenie czy można otworzyć plik");
    if ((error_code = test_check_if_can_be_opened()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się otworzyć pliku, który istnieje!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Udało się otworzyć plik, który nie istnieje!", error_code);
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
    print_subtest_start(1, subtest_num, "generowanie grafu, gdzie istnieją wszystkie możliwe połączenia");
    if ((error_code = test_generate_graph_where_all_connections_exist()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się utworzyć grafu!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się utworzyć pliku z grafem!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się otworzyć wygenerowanego pliku z grafem!", error_code);
        }
        else if (error_code == 4)
        {
            print_subtest_fail(test_num, subtest_num, "Format wygenerowanego pliku z grafem jest niepoprawny!", error_code);
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
    print_subtest_start(test_num, subtest_num, "generowanie grafu z losowymi połączeniami, do momentu aż graf jest silnie spójny");
    if ((error_code = test_generate_graph_randomly_till_its_connected()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się utworzyć grafu!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się utworzyć pliku z grafem!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się otworzyć wygenerowanego pliku z grafem!", error_code);
        }
        else if (error_code == 4)
        {
            print_subtest_fail(test_num, subtest_num, "Format wygenerowanego pliku z grafem jest niepoprawny!", error_code);
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
    print_subtest_start(test_num, subtest_num, "generowanie grafu z losowymi połączeniami");
    if ((error_code = test_generate_graph_randomly()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się utworzyć grafu!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się utworzyć pliku z grafem!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się otworzyć wygenerowanego pliku z grafem!", error_code);
        }
        else if (error_code == 4)
        {
            print_subtest_fail(test_num, subtest_num, "Format wygenerowanego pliku z grafem jest niepoprawny!", error_code);
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

int test_check_if_can_be_opened()
{
    if (check_if_can_be_opened("test_src/test_data/file_that_exists.txt") != 1)
    {
        return 1;
    }
    if (check_if_can_be_opened("test_src/test_data/file_that_doesnt_exists.txt") != 0)
    {
        return 2;
    }
    return 0;
}

int test_generate_graph_where_all_connections_exist()
{
    Graph *graph = generate_graph_where_all_connections_exist(0, 3, 9, 20);
    if (graph == NULL)
    {
        return 1;
    }
    if (graph_to_file("test_src/test_data/test_gen_a.txt", graph))
    {
        return 2;
    }
    if (!check_if_can_be_opened("test_src/test_data/test_gen_a.txt"))
    {
        free_graph(&graph);
        return 3;
    }
    free_graph(&graph);
    Graph *graph_read;
    char error[LINE_BUFFER_SIZE];
    if (create_graph_from_file(&graph_read, "test_src/test_data/test_gen_a.txt", error) != 0) // create_graph_from_file also checks if format is correct
    {
        return 4;
    }
    free_graph(&graph_read);
    return 0;
}

int test_generate_graph_randomly_till_its_connected()
{
    Graph *graph = generate_graph_randomly_till_its_connected(0, 5, 10, 8);
    if (graph == NULL)
        return 1;
    if (graph_to_file("test_src/test_data/test_gen_b.txt", graph))
        return 2;
    if (!check_if_can_be_opened("test_src/test_data/test_gen_b.txt"))
    {
        free_graph(&graph);
        return 3;
    }
    free_graph(&graph);
    Graph *graph_read;
    char error[LINE_BUFFER_SIZE];
    if (create_graph_from_file(&graph_read, "test_src/test_data/test_gen_b.txt", error) != 0) // create_graph_from_file also checks if format is correct
    {
        return 4;
    }
    free_graph(&graph_read);
    return 0;
}

int test_generate_graph_randomly()
{
    Graph *graph = generate_graph_randomly(1, 5, 12, 6);
    if (graph == NULL)
        return 1;
    if (graph_to_file("test_src/test_data/test_gen_c.txt", graph))
        return 2;
    if (!check_if_can_be_opened("test_src/test_data/test_gen_c.txt"))
    {
        free_graph(&graph);
        return 3;
    }
    free_graph(&graph);
    Graph *graph_read;
    char error[LINE_BUFFER_SIZE];
    if (create_graph_from_file(&graph_read, "test_src/test_data/test_gen_c.txt", error) != 0) // create_graph_from_file also checks if format is correct
    {
        return 4;
    }
    free_graph(&graph_read);
    return 0;
}