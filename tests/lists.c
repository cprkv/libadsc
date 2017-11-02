#include "test_suite.h"
#include <adsc.h>

enum test_result_t list_create()
{
    ads_list_t* lst = ads_list_create();
    test_assert(lst != NULL);

    ads_list_destroy(&lst, free);
    test_assert(lst == NULL);

    return TEST_RESULT_OK;
}

enum test_result_t list_push_top_1()
{
    ads_list_t* lst = ads_list_create();
    int* ptr = malloc(sizeof(int));
    *ptr = 228;

    test_assert(ads_list_empty(lst));
    test_assert(lst->size == 0);

    ads_list_push(lst, ptr);
    test_assert(ads_list_top(lst) != NULL);
    test_assert(lst->size == 1);
    test_assert(!ads_list_empty(lst));

    int* top = ads_list_top(lst);
    test_assert(*top == 228);
    test_assert(lst->size == 1);

    int* back = ads_list_pop(lst);
    test_assert(back == ptr);
    test_assert(lst->size == 0);
    test_assert(ads_list_top(lst) == NULL);
    test_assert(ads_list_empty(lst));

    free(back);
    ads_list_destroy(&lst, free);

    return TEST_RESULT_OK;
}

enum test_result_t list_push_top_2()
{
    ads_list_t* lst = ads_list_create();
    int* ptr;

    test_assert((int*) ads_list_top(lst) == NULL);

    ads_list_push_value(lst, int, 4);
    test_assert(*(int*) ads_list_top(lst) == 4);

    ads_list_push_value(lst, int, 8);
    test_assert(*(int*) ads_list_top(lst) == 8);

    ads_list_push_value(lst, int, 7);
    test_assert(*(int*) ads_list_top(lst) == 7);

    ptr = ads_list_pop(lst);
    test_assert(*ptr == 7);
    test_assert(*(int*) ads_list_top(lst) == 8);
    free(ptr);

    ptr = ads_list_pop(lst);
    test_assert(*ptr == 8);
    test_assert(*(int*) ads_list_top(lst) == 4);
    free(ptr);

    ptr = ads_list_pop(lst);
    test_assert(*ptr == 4);
    test_assert((int*) ads_list_top(lst) == NULL);
    free(ptr);

    ads_list_push_value(lst, int, 4);
    test_assert(*(int*) ads_list_top(lst) == 4);

    ads_list_push_value(lst, int, 3);
    test_assert(*(int*) ads_list_top(lst) == 3);

    ads_list_push_value(lst, int, 2);
    test_assert(*(int*) ads_list_top(lst) == 2);

    int i = 0;
    ads_list_for(lst, it)
    {
        int val = ads_list_val(it, int);

        switch (i)
        {
        case 0:
            test_assert(val == 2);
            break;
        case 1:
            test_assert(val == 3);
            break;
        case 2:
            test_assert(val == 4);
            break;
        default:
            test_assert(false);
        }

        i++;
    }

    ads_list_destroy(&lst, free);
    test_assert(lst == NULL);

    return TEST_RESULT_OK;
}

enum test_result_t list_for_value()
{
    ads_list_t* lst = ads_list_create();

    ads_list_push_value(lst, int, 10);
    ads_list_push_value(lst, int, 8);
    ads_list_push_value(lst, int, 6);
    ads_list_push_value(lst, int, 4);
    ads_list_push_value(lst, int, 2);
    ads_list_push_value(lst, int, 0);

    test_assert(lst->size == 6);
    int i = 0;

    ads_list_for(lst, it)
    {
        int val = ads_list_val(it, int);
        test_assert(val == i * 2);
        i++;
    }

    test_assert(i == 6);

    ads_list_clear(lst, free);
    test_assert(lst->size == 0);
    test_assert(ads_list_empty(lst));

    ads_list_destroy(&lst, free);

    return TEST_RESULT_OK;
}

enum test_result_t list_static()
{
    ads_list_t lst;
    ads_list_init(&lst);

    ads_list_push_value(&lst, int, 10);
    ads_list_push_value(&lst, int, 8);
    ads_list_push_value(&lst, int, 6);
    ads_list_push_value(&lst, int, 4);
    ads_list_push_value(&lst, int, 2);
    ads_list_push_value(&lst, int, 0);

    test_assert(lst.size == 6);
    int i = 0;

    ads_list_for(&lst, it)
    {
        test_assert(ads_list_val(it, int) == i * 2);
        i++;
    }

    test_assert(i == 6);

    ads_list_clear(&lst, free);
    test_assert(lst.size == 0);
    test_assert(ads_list_empty(&lst));

    return TEST_RESULT_OK;
}

enum test_result_t list_for_each()
{
    ads_list_t lst;
    ads_list_init(&lst);

    ads_list_push_value(&lst, int, 8);
    ads_list_push_value(&lst, int, 6);
    ads_list_push_value(&lst, int, -3);
    ads_list_push_value(&lst, int, 0);
    ads_list_push_value(&lst, int, 4);
    ads_list_push_value(&lst, int, 2);
    ads_list_push_value(&lst, int, 10);
    ads_list_push_value(&lst, int, -10);

    test_assert(lst.size == 8);

    int sum = 0;
    ads_list_for_each(&lst, it, sum += ads_list_val(it, int));

    test_assert(sum == 17);

    ads_list_clear(&lst, free);
    test_assert(lst.size == 0);
    test_assert(ads_list_empty(&lst));

    return TEST_RESULT_OK;
}

void list_contains_null_remover(void* ptr)
{
    if (ptr) free(ptr);
}

enum test_result_t list_contains_null()
{
    ads_list_t lst;
    ads_list_init(&lst);

    ads_list_push(&lst, malloc(sizeof(int)));
    ads_list_push(&lst, NULL);
    ads_list_push(&lst, malloc(sizeof(int)));

    ads_list_clear(&lst, list_contains_null_remover);
    test_assert(lst.size == 0);
    test_assert(ads_list_empty(&lst));

    return TEST_RESULT_OK;
}

void list_nested_remover(void* nested)
{
    ads_list_destroy((ads_list_t**) &nested, free);
}

enum test_result_t list_nested()
{
    /**
     * creating nested list matrix-like (arrows from head of list):
     *
     *     8  ->  7  ->  6  ->|
     *   |
     *   V
     *     5  ->  4  ->  3  ->|
     *   |
     *   V
     *     2  ->  1  ->  0  ->|
     *   |
     *   -
     */
    
    ads_list_t* lst = ads_list_create();

    for (int i = 0; i < 3; i++)
    {
        ads_list_t* nested = ads_list_push(lst, ads_list_create());

        ads_list_push_value(nested, int, i * 3 + 0);
        ads_list_push_value(nested, int, i * 3 + 1);
        ads_list_push_value(nested, int, i * 3 + 2);
    }

    test_assert(lst->size == 3);

    int sum = 0;
    int sum_2 = 0;

    ads_list_for(lst, m_it)
    {
        ads_list_t nested = ads_list_val(m_it, ads_list_t);

        ads_list_for_each(&nested, n_it, sum += ads_list_val(n_it, int));

        ads_list_for(&nested, n_it)
        {
            sum_2 += ads_list_val(n_it, int);
        }
    }

    test_assert(sum == 36);
    test_assert(sum_2 == 36);

    // destroys all nested lists and main list itself
    ads_list_destroy(&lst, list_nested_remover);
    test_assert(lst == NULL);

    return TEST_RESULT_OK;
}
