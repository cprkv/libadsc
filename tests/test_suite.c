#include "test_suite.h"
#include <stdarg.h>
#include <stdio.h>

void test_run_all(const char* st, ...)
{
  printf("--- tests run all ---\n");
  const char* test_desc = st;
  test_t test;
  va_list args;
  va_start(args, st);
  test = va_arg(args, test_t);

  for (int i = 0;; i++)
  {
    enum test_result_t res = test();
    printf("[%d] %s: %s\n",
           (i + 1),
           test_desc,
           (res == TEST_RESULT_OK ? "OK" : "FAILED"));

    test_desc = va_arg(args, const char*);
    if (!test_desc)
      break;
    test = va_arg(args, test_t);
  }

  printf("--- tests ended ---\n");
  va_end(args);
}

void test_run_rtf(const char* st, ...)
{
  printf("--- tests run to failure ---\n");
  const char* test_desc = st;
  test_t test;
  va_list args;
  va_start(args, st);
  test = va_arg(args, test_t);

  for (int i = 0;; i++)
  {
    enum test_result_t res = test();
    printf("[%d] %s: %s\n",
           (i + 1),
           test_desc,
           (res == TEST_RESULT_OK ? "OK" : "FAILED"));

    if (res == TEST_RESULT_FAILED)
      break;

    test_desc = va_arg(args, const char*);

    if (!test_desc)
      break;

    test = va_arg(args, test_t);
  }

  printf("--- tests ended ---\n");
  va_end(args);
}