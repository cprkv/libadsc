#pragma once
#include <stddef.h>
#include <adsc_base.h>

/**
 * File:       adsc_lists.h
 * Created by: kristen
 * Desc:       interface for allocators
 */

// ----------------------------- alloc pool -----------------------------
/**
 * \defgroup AllocPool
 * @{
 */

typedef struct
{
    void* (*alloc)(void* self);
    void (*dealloc)(void* self, void* ptr);

    // private
    size_t object_size;
    size_t size;
    size_t capacity;
    void* pool;
    void* start;

} ads_alloc_pool_t;

ads_alloc_pool_t* ads_alloc_pool_create(size_t object_size,
                                        size_t capacity);
void ads_alloc_pool_init(ads_alloc_pool_t* self,
                         size_t object_size,
                         size_t capacity);
void ads_alloc_pool_clear(ads_alloc_pool_t* self);
void ads_alloc_pool_destroy(ads_alloc_pool_t** self);

/**@}*/

// ------------------------- alloc pool list ----------------------------
// FIXME: not ready to use
/**
 * \defgroup AllocPoolList
 * @{
 */

typedef struct
{
    ads_alloc_pool_t poll;
    void* next;
} ads_alloc_pool_list_el_t;

typedef struct
{
    void* (*alloc)(void* self);
    void (*dealloc)(void* self, void* ptr);
    ads_alloc_pool_list_el_t* list;
} ads_alloc_pool_list_t;

ads_alloc_pool_list_t* ads_alloc_pool_list_create(size_t object_size,
                                                  size_t capacity);
void ads_alloc_pool_list_init(ads_alloc_pool_list_t* self,
                              size_t object_size,
                              size_t capacity);
void ads_alloc_pool_list_clear(ads_alloc_pool_list_t* self);
void ads_alloc_pool_list_destroy(ads_alloc_pool_list_t** self);

/**@}*/