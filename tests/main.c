#include "test_suite.h"

// lists.c
enum test_result_t list_create();
enum test_result_t list_push_top_1();
enum test_result_t list_push_top_2();

int main()
{
  test_run_all(test_add(list_create),
               test_add(list_push_top_1),
               test_add(list_push_top_2),

               NULL);
  return 0;
}
