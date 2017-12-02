#include "test_suite.h"
#include <adsc.h>

enum test_result_t vec_create()
{
    auto_t v = ads_vec_create(int);
    test_assert(v != NULL);
    test_assert(v->size == 0);
    test_assert(v->capacity == 8);

    ads_vec_destroy(&v);
    test_assert(v == NULL);

    v = ads_vec_create(int, 3);
    test_assert(v != NULL);
    test_assert(v->val_size == sizeof(int));
    test_assert(v->size == 3);
    test_assert(v->capacity == 8);

    ads_vec_destroy(&v);
    test_assert(v == NULL);

    v = ads_vec_create(char, 16);
    test_assert(v != NULL);
    test_assert(v->val_size == sizeof(char));
    test_assert(v->size == 16);
    test_assert(v->capacity == 32);

    ads_vec_destroy(&v);
    test_assert(v == NULL);

    v = ads_vec_create(double, 5);
    test_assert(v != NULL);
    test_assert(v->val_size == sizeof(double));
    test_assert(v->size == 5);
    test_assert(v->capacity == 8);

    ads_vec_destroy(&v);
    test_assert(v == NULL);

    return TEST_RESULT_OK;
}

enum test_result_t vec_resize()
{
    auto_t v = ads_vec_create(int);
    test_assert(v != NULL);
    test_assert(v->size == 0);
    test_assert(v->capacity == 8);

    ads_vec_resize(v, 128);
    test_assert(v->size == 128);
    test_assert(v->capacity == 256);

    ads_vec_resize(v, 15);
    test_assert(v->size == 15);
    test_assert(v->capacity == 16);

    ads_vec_destroy(&v);
    test_assert(v == NULL);

    return TEST_RESULT_OK;
}

enum test_result_t vec_elem()
{
    ads_vec_auto v = ads_vec_create(unsigned int);
    test_assert(v != NULL);
    test_assert(v->size == 0);
    test_assert(v->capacity == 8);

    ads_vec_resize(v, 3);
    test_assert(v->size == 3);
    test_assert(v->capacity == 8);

    ads_vec_val(v, unsigned int)[0] = 0U;
    ads_vec_val(v, unsigned int)[1] = 0xF0FAFCFD;
    ads_vec_val(v, unsigned int)[2] = 1U;

    unsigned int ptr_diff = (char*) &(ads_vec_val(v, unsigned int)[1]) -
                            (char*) &(ads_vec_val(v, unsigned int)[0]);
    test_assert(ptr_diff == sizeof(unsigned int));

    ptr_diff = ads_vec_ptr(v, 1) - ads_vec_ptr(v, 0);
    test_assert(ptr_diff == sizeof(unsigned int));

    test_assert(ads_vec_val(v, unsigned int)[0] == 0U);
    test_assert(ads_vec_val(v, unsigned int)[1] == 0xF0FAFCFD);
    test_assert(ads_vec_val(v, unsigned int)[2] == 1U);

    ads_vec_resize(v, 15);
    test_assert(v->size == 15);
    test_assert(v->capacity == 16);

    ptr_diff = (char*) &(ads_vec_val(v, unsigned int)[1]) -
               (char*) &(ads_vec_val(v, unsigned int)[0]);
    test_assert(ptr_diff == sizeof(unsigned int));

    ptr_diff = ads_vec_ptr(v, 1) - ads_vec_ptr(v, 0);
    test_assert(ptr_diff == sizeof(unsigned int));

    test_assert(ads_vec_val(v, unsigned int)[0] == 0U);
    test_assert(ads_vec_val(v, unsigned int)[1] == 0xF0FAFCFD);
    test_assert(ads_vec_val(v, unsigned int)[2] == 1U);

    return TEST_RESULT_OK;
}