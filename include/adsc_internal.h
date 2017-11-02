#pragma once
#include <assert.h>

/**
 * File:       adsc_internal.h
 * Created by: kristen
 * Desc:       internal header
 */

#define ads_alloc_struct(var, type) type* var = malloc(sizeof(type))
#define ads_free(ptr) free(ptr)
#define ads_assert assert