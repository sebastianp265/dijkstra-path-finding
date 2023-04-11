#include "queue_test.h"

void test_queue()
{
    int error_code;
    int subtest_num;
    int test_num;
    // test 3
    test_num = 3;
    // subtest 1
    subtest_num = 1;
    print_subtest_start(test_num, subtest_num, "inicjalizacja kolejki");
    if ((error_code = test_queue_init()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla kolejki!", error_code);
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
    print_subtest_start(test_num, subtest_num, "inicjalizacja węzła kolejki");
    if ((error_code = test_q_node_init()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla węzła kolejki!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Następnik utworzonego węzła nie jest NULL!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Wartość w węźle jest inna niż oczekiwana!", error_code);
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

    print_subtest_start(test_num, subtest_num, "wstawianie do kolejki i zdejmowanie z niej");
    if ((error_code = test_queue_push_and_pop()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Ilość elementów w kolejce jest inna niż oczekiwana!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Wartość zdjęta z kolejki jest inna niż oczekiwana!", error_code);
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

int test_queue_init()
{
    Queue *q = queue_init();
    if (q == NULL)
    {
        return 1;
    }
    free(q);
    return 0;
}

int test_q_node_init()
{
    Q_Node *node = q_node_init(5);
    if (node == NULL)
    {
        return 1;
    }
    if (node->nextNode != NULL)
    {
        free(node);
        return 2;
    }
    if (node->vertex != 5)
    {
        free(node);
        return 3;
    }
    free(node);
    return 0;
}

int test_queue_push_and_pop()
{
    int data[8] = {0, 6, 7, 8, 9, 1, 3, 2};
    Queue *q = queue_init();
    for (int i = 0; i < 8; i++)
    {
        queue_push(q, data[i]);
    }
    int i = 0;
    while (q->size != 0)
    {
        if (i >= 8)
        {
            free(q);
            return 1;
        }
        if (q->first->vertex != data[i])
        {
            while (q->size != 0)
            {
                queue_pop(q);
            }
            free(q);
            return 2;
        }
        i++;
        queue_pop(q);
    }
    free(q);
    return 0;
}