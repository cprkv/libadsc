#pragma once

/**
 * @file ads_internal.h
 * @brief internal header: common functions and macro
 */

#include <ads_alloc.h>
#include <assert.h>

#ifdef DEBUG
#define ads_assert assert
#else
#define ads_assert(ignore) ((void) 0)
#endif

#define ads_likely(x) __builtin_expect((x), 1)
#define ads_unlikely(x) __builtin_expect((x), 0)