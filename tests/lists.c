#include "test_suite.h"
#include <adsc.h>

enum test_result_t list_create()
{
    ads_list_t* lst = ads_list_create();
    test_assert(lst != NULL);

    ads_list_destroy(&lst);
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

    ads_list_push(lst, &ptr, sizeof(int*));
    test_assert(ads_list_top(lst) != NULL);
    test_assert(lst->size == 1);
    test_assert(!ads_list_empty(lst));

    int** top = ads_list_top(lst);
    test_assert(**top == 228);
    test_assert(lst->size == 1);

    int* back = NULL;
    ads_list_pop(lst, &back, sizeof(int*));
    test_assert(lst->size == 0);
    test_assert(ads_list_top(lst) == NULL);
    test_assert(ads_list_empty(lst));
    test_assert(back == ptr);

    free(back);
    ads_list_destroy(&lst);

    return TEST_RESULT_OK;
}

enum test_result_t list_push_top_2()
{
    ads_list_t* lst = ads_list_create();
    int ptr;

    test_assert((int*) ads_list_top(lst) == NULL);
    test_assert(ads_list_empty(lst));

    ads_list_push_value(lst, int, 4);
    test_assert(*(int*) ads_list_top(lst) == 4);
    test_assert(!ads_list_empty(lst));

    ads_list_push_value(lst, int, 8);
    test_assert(*(int*) ads_list_top(lst) == 8);

    ads_list_push_value(lst, int, 7);
    test_assert(*(int*) ads_list_top(lst) == 7);

    ads_list_pop(lst, &ptr, sizeof(int));
    test_assert(ptr == 7);
    test_assert(*(int*) ads_list_top(lst) == 8);

    ads_list_pop(lst, &ptr, sizeof(int));
    test_assert(ptr == 8);
    test_assert(*(int*) ads_list_top(lst) == 4);

    ads_list_pop(lst, &ptr, sizeof(int));
    test_assert(ptr == 4);
    test_assert((int*) ads_list_top(lst) == NULL);
    test_assert(ads_list_empty(lst));

    ads_list_push_value(lst, int, 4);
    test_assert(*(int*) ads_list_top(lst) == 4);

    ads_list_push_value(lst, int, 3);
    test_assert(*(int*) ads_list_top(lst) == 3);

    ads_list_push_value(lst, int, 2);
    test_assert(*(int*) ads_list_top(lst) == 2);

    test_assert(!ads_list_empty(lst));

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

    ads_list_destroy(&lst);
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

    ads_list_clear_base(lst);
    test_assert(lst->size == 0);
    test_assert(ads_list_empty(lst));

    ads_list_destroy(&lst);

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

    ads_list_clear_base(&lst);
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

    ads_list_clear_base(&lst);
    test_assert(lst.size == 0);
    test_assert(ads_list_empty(&lst));

    return TEST_RESULT_OK;
}

enum test_result_t list_erase()
{
    ads_list_auto lst = ads_list_create();

#ifdef __GNU__
    auto rmdeleter =
        ads_lambda(void, (void* ptr), { ads_list_erase(lst, ptr); });
#endif

    ads_list_push_value(lst, int, 7);
    ads_list_push_value(lst, int, 6);
    ads_list_push_value(lst, int, 5);
    ads_list_push_value(lst, int, 4);
    ads_list_push_value(lst, int, 3);
    ads_list_push_value(lst, int, 2);
    ads_list_push_value(lst, int, 1);
    ads_list_push_value(lst, int, 0);

    test_assert(lst->size == 8);

    {
        ads_list_auto rmlst = ads_list_create();

        ads_list_for(lst, it)
        {
            if (ads_list_val(it, int) % 2 == 0)
                ads_list_push_value(rmlst, void*, it);
        }

#ifdef __GNU__
        ads_list_clear(rmlst, rmdeleter, void*);
#else
        ads_list_for(rmlst, it)
            ads_list_erase(lst, ads_list_val(it, void*));
#endif
    }

    test_assert(lst->size == 4);

    int i = 0;
    ads_list_for(lst, it)
    {
        int val = ads_list_val(it, int);

        switch (i)
        {
        case 0:
            test_assert(val == 1);
            break;
        case 1:
            test_assert(val == 3);
            break;
        case 2:
            test_assert(val == 5);
            break;
        case 3:
            test_assert(val == 7);
            break;
        default:
            test_assert(false);
        }

        i++;
    }

    return TEST_RESULT_OK;
}

#ifndef __GNU__
bool lst_erase_condition(int v)
{
    return v % 2 == 0;
}
#endif

enum test_result_t list_erase_if()
{
    ads_list_auto lst = ads_list_create();

    ads_list_push_value(lst, int, 7);
    ads_list_push_value(lst, int, 6);
    ads_list_push_value(lst, int, 5);
    ads_list_push_value(lst, int, 4);
    ads_list_push_value(lst, int, 3);
    ads_list_push_value(lst, int, 2);
    ads_list_push_value(lst, int, 1);
    ads_list_push_value(lst, int, 0);

    test_assert(lst->size == 8);

#ifndef __GNU__
    ads_list_erase_if(lst, int, lst_erase_condition);
#else
    auto condition = ads_lambda(bool, (int v), { return v % 2 == 0; });
    ads_list_erase_if(lst, int, condition);
#endif

    test_assert(lst->size == 4);

    int i = 0;
    ads_list_for(lst, it)
    {
        int val = ads_list_val(it, int);

        switch (i)
        {
        case 0:
            test_assert(val == 1);
            break;
        case 1:
            test_assert(val == 3);
            break;
        case 2:
            test_assert(val == 5);
            break;
        case 3:
            test_assert(val == 7);
            break;
        default:
            test_assert(false);
        }

        i++;
    }

    return TEST_RESULT_OK;
}


void list_contains_null_remover(void* ptr)
{
    if (ptr)
        free(ptr);
}

enum test_result_t list_contains_null()
{
    ads_list_t lst;
    ads_list_init(&lst);

    void* ptr = malloc(sizeof(int));
    ads_list_push(&lst, &ptr, sizeof(void*));
    ptr = malloc(sizeof(int));
    ads_list_push(&lst, &ptr, sizeof(void*));

    ads_list_clear(&lst, list_contains_null_remover, void*);
    test_assert(lst.size == 0);
    test_assert(ads_list_empty(&lst));

    return TEST_RESULT_OK;
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
        ads_list_t* nested = ads_list_push(lst, NULL, sizeof(ads_list_t));
        ads_list_init(nested);
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

    // first method to destroy nested lists
    /*
        while (!ads_list_empty(lst))
        {
            ads_list_clear_base(ads_list_top(lst));
            ads_list_pop(lst, NULL, 0);
        }
    */

    // second method to destroy nested lists
    /*
        ads_list_clear(lst, ads_list_clear_base, ads_list_t);
    */

    // but i used this method
    ads_list_for(lst, it) ads_list_clear_base((ads_list_t*) &it->value);

    ads_list_destroy(&lst);
    test_assert(lst == NULL);

    return TEST_RESULT_OK;
}

// -------------------------------- dlist --------------------------------

enum test_result_t dlist_create()
{
    ads_dlist_t* lst = ads_dlist_create();
    test_assert(lst != NULL);
    test_assert(ads_dlist_empty(lst));
    test_assert(lst->size == 0);

    ads_dlist_destroy(&lst);
    test_assert(lst == NULL);

    return TEST_RESULT_OK;
}

enum test_result_t dlist_push_top_1()
{
    ads_dlist_t* lst = ads_dlist_create();
    int* ptr = malloc(sizeof(int));
    *ptr = 228;

    test_assert(ads_dlist_empty(lst));
    test_assert(lst->size == 0);

    ads_dlist_push_back(lst, &ptr, sizeof(int*));
    test_assert(ads_dlist_top_front(lst) != NULL);
    test_assert(ads_dlist_top_back(lst) == ads_dlist_top_front(lst));
    test_assert(lst->size == 1);
    test_assert(!ads_dlist_empty(lst));

    int** top = ads_dlist_top_front(lst);
    test_assert(**top == 228);
    test_assert(lst->size == 1);

    int* back = NULL;
    ads_dlist_pop_back(lst, &back, sizeof(int*));
    test_assert(lst->size == 0);
    test_assert(ads_dlist_top_front(lst) == NULL);
    test_assert(ads_dlist_empty(lst));
    test_assert(back == ptr);

    free(back);
    ads_dlist_destroy(&lst);

    return TEST_RESULT_OK;
}

enum test_result_t dlist_push_top_2()
{
    ads_dlist_t* lst = ads_dlist_create();
    int ptr;

    test_assert(ads_dlist_empty(lst));
    test_assert((int*) ads_dlist_top_front(lst) == NULL);

    ads_dlist_push_back_value(lst, int, 4);
    test_assert(!ads_dlist_empty(lst));
    test_assert(*(int*) ads_dlist_top_back(lst) == 4);
    test_assert(*(int*) ads_dlist_top_front(lst) == 4);

    ads_dlist_push_back_value(lst, int, 8);
    test_assert(*(int*) ads_dlist_top_back(lst) == 8);
    test_assert(*(int*) ads_dlist_top_front(lst) == 4);

    ads_dlist_push_back_value(lst, int, 7);
    test_assert(*(int*) ads_dlist_top_back(lst) == 7);
    test_assert(*(int*) ads_dlist_top_front(lst) == 4);

    ads_dlist_pop_back(lst, &ptr, sizeof(int));
    test_assert(!ads_dlist_empty(lst));
    test_assert(ptr == 7);
    test_assert(*(int*) ads_dlist_top_back(lst) == 8);
    test_assert(*(int*) ads_dlist_top_front(lst) == 4);

    ads_dlist_pop_back(lst, &ptr, sizeof(int));
    test_assert(!ads_dlist_empty(lst));
    test_assert(ptr == 8);
    test_assert(*(int*) ads_dlist_top_back(lst) == 4);
    test_assert(*(int*) ads_dlist_top_front(lst) == 4);

    ads_dlist_pop_back(lst, &ptr, sizeof(int));
    test_assert(ads_dlist_empty(lst));
    test_assert(ptr == 4);
    test_assert((int*) ads_dlist_top_back(lst) == NULL);

    ads_dlist_push_front_value(lst, int, 3);
    test_assert(!ads_dlist_empty(lst));
    test_assert(*(int*) ads_dlist_top_front(lst) == 3);
    test_assert(*(int*) ads_dlist_top_back(lst) == 3);

    ads_dlist_push_front_value(lst, int, 2);
    test_assert(!ads_dlist_empty(lst));
    test_assert(*(int*) ads_dlist_top_front(lst) == 2);
    test_assert(*(int*) ads_dlist_top_back(lst) == 3);

    ads_dlist_push_back_value(lst, int, 4);
    test_assert(!ads_dlist_empty(lst));
    test_assert(*(int*) ads_dlist_top_front(lst) == 2);
    test_assert(*(int*) ads_dlist_top_back(lst) == 4);

    int i = 0;
    ads_dlist_for_reverse(lst, it)
    {
        int val = ads_dlist_val(it, int);

        switch (i)
        {
        case 0:
            test_assert(val == 4);
            break;
        case 1:
            test_assert(val == 3);
            break;
        case 2:
            test_assert(val == 2);
            break;
        default:
            test_assert(false);
        }

        i++;
    }

    i = 0;
    ads_dlist_for(lst, it)
    {
        int val = ads_dlist_val(it, int);

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

    ads_dlist_destroy(&lst);
    test_assert(lst == NULL);

    return TEST_RESULT_OK;
}

enum test_result_t dlist_static()
{
    ads_dlist_t lst;
    ads_dlist_init(&lst);

    ads_dlist_push_front_value(&lst, int, 4);
    ads_dlist_push_back_value(&lst, int, 6);
    ads_dlist_push_front_value(&lst, int, 2);
    ads_dlist_push_back_value(&lst, int, 8);
    ads_dlist_push_front_value(&lst, int, 0);
    ads_dlist_push_back_value(&lst, int, 10);

    test_assert(lst.size == 6);
    int i = 0;

    ads_dlist_for(&lst, it)
    {
        test_assert(ads_dlist_val(it, int) == i * 2);
        i++;
    }

    test_assert(i == 6);

    ads_dlist_clear_base(&lst);
    test_assert(lst.size == 0);
    test_assert(ads_dlist_empty(&lst));

    return TEST_RESULT_OK;
}