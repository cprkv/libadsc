#pragma once
#include <assert.h>

/**
 * File:       adsc_internal.h
 * Created by: kristen
 * Desc:       internal header
 */

#define ads_alloc_struct(var, type) type* var = malloc(sizeof(type))
#define ads_free(ptr) free(ptr)

#ifdef DEBUG
#define ads_assert assert
#else
#define ads_assert(ignore) ((void) 0)
#endif

#define ads_likely(x) __builtin_expect((x), 1)
#define ads_unlikely(x) __builtin_expect((x), 0)