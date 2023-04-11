#include "stack_test.h"

void test_stack()
{
    int error_code;
    int subtest_num;
    int test_num;
    // test 6
    test_num = 6;
    // subtest 1
    subtest_num = 1;
    print_subtest_start(test_num, subtest_num, "dodawanie na stos");
    if ((error_code = test_push_stack()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla stosu!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Element na czubku stosu jest inny niż oczekiwany!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Wskaźnik na stos po zwolnieniu pamięci jest inny niż NULL!", error_code);
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
    print_subtest_start(test_num, subtest_num, "zdejmowanie ze stosu");
    if ((error_code = test_pop_stack()))
    {
        if (error_code == 1)
        {
            print_subtest_fail(test_num, subtest_num, "Nie udało się zaalokować pamięci dla stosu!", error_code);
        }
        else if (error_code == 2)
        {
            print_subtest_fail(test_num, subtest_num, "Element na czubku stosu jest inny niż oczekiwany!", error_code);
        }
        else if (error_code == 3)
        {
            print_subtest_fail(test_num, subtest_num, "Wskaźnik na stos po zwolnieniu pamięci jest inny niż NULL!", error_code);
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

int test_push_stack()
{
    Stack *stack = NULL;
    push_stack(&stack, 0, 0.3);
    if (stack == NULL)
    {
        return 1;
    }
    push_stack(&stack, 1, 1.2);
    if (stack->prev == NULL)
    {
        free_stack(&stack);
        return 1;
    }
    push_stack(&stack, 2, 0.6);

    if (stack->prev->prev == NULL)
    {
        free_stack(&stack);
        return 1;
    }
    push_stack(&stack, 3, 1.8);
    if (stack->prev->prev->prev == NULL)
    {
        free_stack(&stack);
        return 1;
    }
    /* stack should look like: (from top to bottom)
        3
        2
        1
        0
    */
    if (stack->number_of_node != 3)
    {
        free_stack(&stack);
        if (stack != NULL)
        {
            return 3;
        }
        return 2;
    }
    if (stack->prev->number_of_node != 2)
    {
        free_stack(&stack);
        if (stack != NULL)
        {
            return 3;
        }
        return 2;
    }
    if (stack->prev->prev->number_of_node != 1)
    {
        free_stack(&stack);
        if (stack != NULL)
        {
            return 3;
        }
        return 2;
    }
    if (stack->prev->prev->prev->number_of_node != 0)
    {
        free_stack(&stack);
        if (stack != NULL)
        {
            return 3;
        }
        return 2;
    }
    free_stack(&stack);
    if (stack != NULL)
    {
        return 3;
    }
    return 0;
}

int test_pop_stack()
{
    Stack *stack = NULL;
    push_stack(&stack, 0, 0.3);
    if (stack == NULL)
    {
        return 1;
    }
    push_stack(&stack, 1, 1.2);
    if (stack->prev == NULL)
    {
        return 1;
    }
    push_stack(&stack, 2, 0.6);
    if (stack->prev == NULL)
    {
        return 1;
    }
    push_stack(&stack, 3, 1.8);
    if (stack->prev == NULL)
    {
        return 1;
    }

    if (stack->number_of_node != 3)
    {
        return 2;
    }
    pop_stack(&stack);
    if (stack->number_of_node != 2)
    {
        return 2;
    }
    pop_stack(&stack);
    if (stack->number_of_node != 1)
    {
        return 2;
    }
    pop_stack(&stack);
    if (stack->number_of_node != 0)
    {
        return 2;
    }
    pop_stack(&stack);
    if (stack != NULL)
    {
        return 3;
    }

    return 0;
}
