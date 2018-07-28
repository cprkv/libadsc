#pragma once
#include <stdio.h>

/**
 * @file test_suite.h
 * @brief tests helper
 */

enum test_result
{
  TEST_RESULT_OK,
  TEST_RESULT_FAILED,
};

#define test_decl(name) enum test_result test_func_##name() 

#define test_add(name) #name, name

#define test_assert(cond)                                                 \
  if (!(cond))                                                            \
  {                                                                       \
    printf("   test assertion (" #cond ") failed on line %d\n   %s\n",    \
           __LINE__, __FILE__);                                           \
    return TEST_RESULT_FAILED;                                            \
  }

typedef enum test_result (*test_t)(void);

void test_run_all(void);
