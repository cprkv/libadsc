#pragma once

/**
 * @file ads_list.h
 * @brief interface for memory allocators
 */

#include <ads_base.h>

typedef void* (*ads_alloc_allocate_t)(struct ads_alloc* self, size_t size);
typedef void (*ads_alloc_free_t)(struct ads_alloc* self, void* ptr);

struct ads_alloc
{
  ads_alloc_allocate_t allocate;
  ads_alloc_free_t free;
};