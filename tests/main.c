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
                 NULL);
    return 0;
}
