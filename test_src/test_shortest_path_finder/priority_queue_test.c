#include "priority_queue_test.h"

void test_priority_queue()
{
    int error_code;
    int subtest_num;
    int test_num;
    // test 5
    test_num = 5;
    // subtest 1
    subtest_num = 1;
    print_subtest_start(test_num, subtest_num, "inicjowanie i uwalnianie pamięci dla węzła kolejki");
    if ((error_code = test_initiate_and_free_node()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało sie zaalokować pamięci dla węzła!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Wartość w węźle jest inna niż oczekiwana!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Wskaźnik na węzeł po zwolnieniu pamięci jest inny niż NULL!", error_code);
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
    print_subtest_start(test_num, subtest_num, "inicjowanie i uwalnianie pamięci dla kolejki");
    if ((error_code = test_initiate_and_free_priority_queue()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało sie zaalokować pamięci dla kolejki!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Wskaźnik na kolejkę po zwolnieniu pamięci jest inny niż NULL!", error_code);
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
    print_subtest_start(test_num, subtest_num, "wstawianie elementu do kolejki");
    if ((error_code = test_push_priority_queue()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla kolejki!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla zestawu danych do testu!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Drzewo binarne nie jest kompletne!", error_code);
        }
        else if (error_code == 4)
        {
            print_subtest_fail(test_num, subtest_num, "Ilość elementów testowych jest różna niż ilość w kolejce!", error_code);
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
    print_subtest_start(test_num, subtest_num, "podglądanie przodu kolejki");
    if ((error_code = test_peek_priority_queue()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla kolejki!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla zestawu danych do testu!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Podejrzany węzeł nie jest węzłem o najniższym priorytecie!", error_code);
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
    print_subtest_start(test_num, subtest_num, "zdejmowanie z kolejki");
    if ((error_code = test_pop_priority_queue()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla kolejki!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla zestawu danych do testu!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Drzewo binarne nie jest kompletne!", error_code);
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

int test_initiate_and_free_node()
{
    Node *node = initiate_node(1, 0.2);
    if (node == NULL)
    {
        return 1;
    }
    if (node->node_num != 1)
    {
        return 2;
    }
    free_node(&node);
    if (node != NULL)
    {
        return 3;
    }
    return 0;
}

int test_initiate_and_free_priority_queue()
{
    Priority_queue *pq = initiate_priority_queue();
    if (pq == NULL) // if pointer was not created corectly
    {
        return 1;
    }
    free_priority_queue(&pq);
    if (pq != NULL) // if pointer was not freed corectly
    {
        return 2;
    }
    return 0;
}

int test_push_priority_queue()
{
    Priority_queue *pq = initiate_priority_queue();
    Node **array_of_nodes = test_get_array_of_nodes();
    if (pq == NULL)
    {
        return 1;
    }
    if (array_of_nodes == NULL)
    {
        free_priority_queue(&pq);
        return 2;
    }
    for (int i = 0; i < NODE_ARRAY_SIZE; i++)
    {
        if (!test_is_heap_complete_priority_queue(pq)) // if heap is not complete
        {
            free_priority_queue(&pq);
            free(array_of_nodes);
            return 3;
        }
        push_priority_queue(pq, array_of_nodes[i]);
    }
    if (!test_is_heap_complete_priority_queue(pq)) // if heap is not complete
    {
        free_priority_queue(&pq);
        free(array_of_nodes);
        return 3;
    }
    if (!(pq->size == NODE_ARRAY_SIZE))
    {
        free_priority_queue(&pq);
        free(array_of_nodes);
        return 4;
    }

    free_priority_queue(&pq);
    free(array_of_nodes);
    return 0;
}

int test_peek_priority_queue()
{
    Priority_queue *pq = initiate_priority_queue();
    Node **array_of_nodes = test_get_array_of_nodes();
    if (pq == NULL)
    {
        return 1;
    }
    if (array_of_nodes == NULL)
    {
        free_priority_queue(&pq);
        return 2;
    }
    push_priority_queue(pq, array_of_nodes[0]);
    int min_priority_node_num = 0; // node_num of the node with the lowest priority is 0 on start (because it's first inserted)
    if (min_priority_node_num != peek_priority_queue(pq)->node_num)
    {
        free_priority_queue(&pq);
        free(array_of_nodes);
        return 3;
    }
    for (int i = 1; i < NODE_ARRAY_SIZE; i++)
    {
        push_priority_queue(pq, array_of_nodes[i]);
        if (array_of_nodes[i]->priority < array_of_nodes[min_priority_node_num]->priority) // check if node with the lowest priority has changed
        {
            min_priority_node_num = array_of_nodes[i]->node_num;
        }
        if (min_priority_node_num != peek_priority_queue(pq)->node_num) // if the element at the top of the heap is not the one with the lowest priority
        {
            free_priority_queue(&pq);
            free(array_of_nodes);
            return 3;
        }
    }

    free_priority_queue(&pq);
    free(array_of_nodes);
    return 0;
}

int test_pop_priority_queue()
{
    Priority_queue *pq = initiate_priority_queue();
    Node **array_of_nodes = test_get_array_of_nodes();

    if (pq == NULL)
    {
        return 1;
    }
    if (array_of_nodes == NULL)
    {
        free_priority_queue(&pq);
        return 2;
    }

    for (int i = 0; i < NODE_ARRAY_SIZE; i++)
    {
        push_priority_queue(pq, array_of_nodes[i]);
    }
    for (int i = 0; i < NODE_ARRAY_SIZE; i++)
    {
        pop_priority_queue(pq);
        if (!test_is_heap_complete_priority_queue(pq))
        {
            free_priority_queue(&pq);
            free(array_of_nodes);
            return 3;
        }
    }
    free_priority_queue(&pq);
    free(array_of_nodes);
    return 0;
}

/*****************************************************************
**                  functions to help testing
******************************************************************/

int test_is_heap_complete_priority_queue(Priority_queue *pq)
{
    int was_there_left_child = 0;
    for (int i = 0; i < pq->size; i++)
    {
        if (2 * i + 1 < pq->size) // if there is a left child
        {
            was_there_left_child = 1;
            if (pq->node[i]->priority > pq->node[2 * i + 1]->priority) // if parent has bigger priority than child then this isn't "min heap"
            {
                return 0;
            }
        }
        if (2 * i + 2 < pq->size) // if there is a right child
        {
            if (was_there_left_child == 0) // if there wasn't left child and there is right child, then the binary tree is not complete
            {
                return 0;
            }
            if (pq->node[i]->priority > pq->node[2 * i + 2]->priority) // if parent has bigger priority than child then this isn't "min heap"
            {
                return 0;
            }
        }
    }
    return 1;
}

Node **test_get_array_of_nodes()
{
    Node **array_of_nodes = (Node **)malloc(NODE_ARRAY_SIZE * sizeof(Node *));
    // for manual insertion only! don't add nodes to the array without increasing NODE_ARRAY_SIZE
    array_of_nodes[0] = initiate_node(0, 0.3);
    array_of_nodes[1] = initiate_node(1, 0.2);
    array_of_nodes[2] = initiate_node(2, 1.1);
    array_of_nodes[3] = initiate_node(3, 1.2);
    array_of_nodes[4] = initiate_node(4, 0.5);
    array_of_nodes[5] = initiate_node(5, 0.8);
    array_of_nodes[6] = initiate_node(6, 0.9);
    array_of_nodes[7] = initiate_node(7, 1.1);
    array_of_nodes[8] = initiate_node(8, 1.3);
    array_of_nodes[9] = initiate_node(9, 3.2);
    return array_of_nodes;
}

double test_return_priority_of_node(Priority_queue *pq, int node_num)
{
    // search for the priority with node_num
    for (int i = 0; i < pq->size; i++)
    {
        if (pq->node[i]->node_num == node_num)
        {
            return pq->node[i]->priority;
        }
    }
    return __DBL_MIN__;
}