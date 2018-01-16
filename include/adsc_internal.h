#pragma once
#include <adsc_alloc.h>
#include <assert.h>

/**
 * File:       adsc_internal.h
 * Created by: kristen
 * Desc:       internal header
 */

#define ads_malloc(size) malloc(size)
#define ads_realloc(ptr, size) realloc(ptr, size)
#define ads_free(ptr) free(ptr)

#define ads_alloc_struct(var, type) type* var = ads_malloc(sizeof(type))

#ifdef DEBUG
#define ads_assert assert
#else
#define ads_assert(ignore) ((void) 0)
#endif

#define ads_likely(x) __builtin_expect((x), 1)
#define ads_unlikely(x) __builtin_expect((x), 0)