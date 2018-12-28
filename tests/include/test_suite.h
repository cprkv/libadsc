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

#define test_assert_true(cond)                                                 \
  if (!(cond)) {                                                               \
    printf("   test assertion (" #cond ") failed on line %d\n   %s\n",         \
           __LINE__,                                                           \
           __FILE__);                                                          \
    return TEST_RESULT_FAILED;                                                 \
  }

#define test_assert_equals(v1, v2) test_assert_true((v1) == (v2))
#define test_assert_null(var) test_assert_true((var) == NULL)
#define test_assert_not_null(var) test_assert_true((var) != NULL)
#define test_assert_false(var) test_assert_true(!(var))
#define test_passed() return TEST_RESULT_OK; 
#define test_failed() return TEST_RESULT_FAILED; 

typedef enum test_result (*test_t)(void);

void test_run_all(void);
