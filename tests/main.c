#include "test_suite.h"
#include <adsc.h>

enum test_result_t list_create()
{
    struct ads_list_t* lst = ads_list_create();
    test_assert(lst != NULL);

    return TEST_RESULT_OK;
}

enum test_result_t list_push_pop_1()
{
    struct ads_list_t* lst = ads_list_create();
    int* ptr = malloc(sizeof(int));
    *ptr = 228;
    ads_list_push(lst, ptr);

    test_assert(ads_list_top(lst) != NULL);

    int* top = ads_list_top(lst);
    test_assert(*top == 228);

    int* back = ads_list_pop(lst);

    test_assert(back == ptr);

    free(back);

    test_assert(ads_list_top(lst) == NULL);

    return TEST_RESULT_OK;
}

int main()
{
    test_run_rtf(test_add(list_create), test_add(list_push_pop_1), NULL);
    return 0;
}
