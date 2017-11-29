#include "test_suite.h"
#include <adsc.h>

enum test_result_t alloc_pool_create()
{
    ads_alloc_pool_t* pool = ads_alloc_pool_create(sizeof(int), 8);
    test_assert(pool != NULL);

    ads_alloc_pool_clear(pool);
    test_assert(pool != NULL);

    ads_alloc_pool_destroy(&pool);
    test_assert(pool == NULL);

    pool = ads_alloc_pool_create(28, 28);
    test_assert(pool != NULL);
    ads_alloc_pool_destroy(&pool);
    test_assert(pool == NULL);

    return TEST_RESULT_OK;
}

enum test_result_t alloc_pool_create_int()
{
    ads_alloc_pool_t* pool = ads_alloc_pool_create(sizeof(int), 8);
    test_assert(pool != NULL);
    test_assert(pool->size == 0);

    int* ptr = pool->alloc(pool);
    *ptr = 228;
    test_assert(pool->size == 1);

    int* ptr2 = pool->alloc(pool);
    *ptr2 = 1488;

    test_assert(pool->size == 2);
    test_assert(*ptr == 228);
    test_assert(*ptr2 == 1488);
    test_assert((size_t)((char*) ptr2 - (char*) ptr) == sizeof(void*));

    pool->dealloc(pool, ptr2);
    test_assert(pool->size == 1);
    int* ptr3 = pool->alloc(pool);

    test_assert(ptr2 == ptr3);
    test_assert(pool->size == 2);

    ads_alloc_pool_destroy(&pool);
    test_assert(pool == NULL);

    return TEST_RESULT_OK;
}

typedef struct
{
    char a;
    float b;
    char c;
} custom_t;

enum test_result_t alloc_pool_custom()
{
    ads_alloc_pool_t pool;
    ads_alloc_pool_init(&pool, sizeof(custom_t), 3);

    custom_t* ptr = pool.alloc(&pool);
    ptr->a = 'a';
    ptr->b = 2.39f;
    ptr->c = 'c';

    test_assert(pool.size == 1);

    custom_t* ptr2 = pool.alloc(&pool);
    ptr2->a = '9';
    ptr2->b = 4.18f;
    ptr2->c = 'T';

    test_assert(ptr->a == 'a');
    test_assert(fabs(ptr->b - 2.39f) < 0.001);
    test_assert(ptr->c == 'c');
    test_assert(ptr2->a == '9');
    test_assert(fabs(ptr2->b - 4.18f) < 0.001);
    test_assert(ptr2->c == 'T');
    test_assert(pool.size == 2);

    ads_alloc_pool_clear(&pool);

    return TEST_RESULT_OK;
}

enum test_result_t alloc_pool_basic_test(ads_alloc_pool_t* pool)
{
    test_assert(pool->size == 0);

#define alloc_ptr_from_pool(num)                                          \
    int* ptr_##num = pool->alloc(pool);                                   \
    *ptr_##num = num;                                                     \
    test_assert(pool->size == num);

    alloc_ptr_from_pool(1);
    alloc_ptr_from_pool(2);
    alloc_ptr_from_pool(3);
    alloc_ptr_from_pool(4);

#undef alloc_ptr_from_pool

    test_assert(*ptr_1 == 1);
    test_assert(*ptr_2 == 2);
    test_assert(*ptr_3 == 3);
    test_assert(*ptr_4 == 4);
    test_assert(pool->alloc(pool) == NULL);

    pool->dealloc(pool, ptr_1);
    pool->dealloc(pool, ptr_3);
    test_assert(pool->size == 2);

    pool->alloc(pool);

    test_assert(*ptr_2 == 2);
    test_assert(*ptr_4 == 4);

    return TEST_RESULT_OK;
}

enum test_result_t alloc_pool_realloc()
{
    ads_alloc_pool_t pool;
    ads_alloc_pool_init(&pool, sizeof(int), 4);

    // if not ok - return result
    enum test_result_t res;
    if ((res = alloc_pool_basic_test(&pool)))
        return res;

    ads_alloc_pool_clear(&pool);

    return TEST_RESULT_OK;
}

enum test_result_t alloc_pool_reuse()
{
    ads_alloc_pool_t pool;
    ads_alloc_pool_init(&pool, sizeof(int), 4);

    test_assert(pool.size == 0);

    ads_alloc_pool_clear(&pool);
    ads_alloc_pool_init(&pool, sizeof(int), 4);
    test_assert(pool.size == 0);

    // if not ok - return result
    enum test_result_t res;
    if ((res = alloc_pool_basic_test(&pool)))
        return res;

    ads_alloc_pool_clear(&pool);
    ads_alloc_pool_init(&pool, sizeof(int), 4);

    if ((res = alloc_pool_basic_test(&pool)))
        return res;

    ads_alloc_pool_clear(&pool);

    return TEST_RESULT_OK;
}
