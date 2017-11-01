#pragma once
#include <stdio.h>

/**
 * File:       test_suite.h
 * Created by: kristen
 * Desc:       tests helper
 */

enum test_result_t
{
    TEST_RESULT_OK,
    TEST_RESULT_FAILED,
};

#define test_add(name) #name, name

#define test_assert(cond)                                                 \
    if (!(cond))                                                          \
    {                                                                     \
        printf("   test assertion (" #cond                                \
               ") failed on line %d\n   %s\n",                            \
               __LINE__,                                                  \
               __FILE__);                                                 \
        return TEST_RESULT_FAILED;                                        \
    }


// #define test_assert(cond) if (!(cond)) { printf("test assertion (" #cond
// ") failed on " " : "); return TEST_RESULT_FAILED; }

typedef enum test_result_t (*test_t)(void);

void test_run_all(const char* st, ...);
void test_run_rtf(const char* st, ...);