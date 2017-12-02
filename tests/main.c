#include "test_suite.h"
#include <adsc.h>

// lists.c
enum test_result_t list_create();
enum test_result_t list_push_top_1();
enum test_result_t list_push_top_2();
enum test_result_t list_for_value();
enum test_result_t list_static();
enum test_result_t list_for_each();
enum test_result_t list_contains_null();
enum test_result_t list_nested();
enum test_result_t list_erase();
enum test_result_t list_erase_if();

enum test_result_t dlist_create();
enum test_result_t dlist_push_top_1();
enum test_result_t dlist_push_top_2();
enum test_result_t dlist_static();
enum test_result_t dlist_erase();

// alloc.c
enum test_result_t alloc_pool_create();
enum test_result_t alloc_pool_create_int();
enum test_result_t alloc_pool_custom();
enum test_result_t alloc_pool_realloc();
enum test_result_t alloc_pool_reuse();

int main()
{
    test_run_rtf(test_add(list_create),
                 test_add(list_push_top_1),
                 test_add(list_push_top_2),
                 test_add(list_for_value),
                 test_add(list_static),
                 test_add(list_for_each),
                 test_add(list_contains_null),
                 test_add(list_nested),
                 test_add(list_erase),
                 test_add(list_erase_if),

                 test_add(dlist_create),
                 test_add(dlist_push_top_1),
                 test_add(dlist_push_top_2),
                 test_add(dlist_static),
                 test_add(dlist_erase),

                 test_add(alloc_pool_create),
                 test_add(alloc_pool_create_int),
                 test_add(alloc_pool_custom),
                 test_add(alloc_pool_realloc),
                 test_add(alloc_pool_reuse),

                 NULL);
    return 0;
}
