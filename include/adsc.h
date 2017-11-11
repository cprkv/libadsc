#pragma once

/**
 * File:       adsc.h
 * Created by: kristen
 * Desc:       main interface for using ads library
 */

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// ---------------- macro

#define ads_max(a, b) ((a) > (b) ? (a) : (b))
#define ads_min(a, b) ((a) < (b) ? (a) : (b))


// -------------------------------- list --------------------------------

/** list data */
typedef struct
{
    void* next;
    char value;
} ads_list_data_t;

/** list header */
typedef struct
{
    ads_list_data_t* head;
    size_t size;
} ads_list_t;

/** creates linked list with default allocator (on heap) */
ads_list_t* ads_list_create();

/** initialises linked list without allocating memory */
void ads_list_init(ads_list_t* list);

// FIXME: what if we need to insert some element in some place in list,
//        and what if need to pop some element in some place in list?

/** adds some data to linked list */
void* ads_list_push(ads_list_t* list, void* value, size_t size);

/** returns head element if list (NULL if empty) */
void* ads_list_top(ads_list_t* list);

/** returns pointer to head element (NULL if empty) */
void ads_list_pop(ads_list_t* list, void* where, size_t size);

/** returns true, if list is empty */
bool ads_list_empty(ads_list_t* list);

/** clear list if data is pod */
void ads_list_clear_base(ads_list_t* lst);

/**
 * destroys any list content using remover, and list itself;
 * sets list value to NULL
 */
void ads_list_destroy(ads_list_t** list);

/**
 * iterates with apply block of operations to iterator element.
 *
 * example for ads_list_t* lst:
 *   float sum = 0.0f;
 *   ads_list_for(lst, it)
 *   {
 *       sum += ads_list_val(lst, it, float);
 *   }
 */
#define ads_list_for(lst, iter)                                           \
    for (ads_list_data_t* iter = (lst)->head; iter != NULL;               \
         iter = iter->next)

#define ads_list_val(iter, type) (*(type*) &(iter->value))

/**
 * iterates with apply only one simple operation.
 *
 * example for ads_list_t* lst (list of int):
 *   int sum = 0;
 *   ads_list_for_each(
 *       lst, it,
 *       sum += ads_list_val(it, int)
 *   );
 */
#define ads_list_for_each(lst, iter, op)                                  \
    for (ads_list_data_t* iter = (lst)->head; iter != NULL;               \
         iter = iter->next)                                               \
        op;

/**
 * example for ads_list_t* lst, and elements allocated with malloc:
 *   ads_list_clear(lst, free);
 */
#define ads_list_clear(lst, deleter, type)                                \
    {                                                                     \
        while (!ads_list_empty(lst))                                      \
        {                                                                 \
            type val;                                                     \
            ads_list_pop(lst, &val, sizeof(type));                        \
            deleter(&val);                                                \
        }                                                                 \
    }

/**
 * example for ads_list_t* lst:
 *   ads_list_push_value(lst, int, 228);
 *   ads_list_push_value(lst, point2f_t, { 3.4f, 0.3f });
 *   ...
 *   ads_list_destroy(lst, free);
 */
#define ads_list_push_value(lst, type, el)                                \
    *(type*) ads_list_push(lst, NULL, sizeof(type)) = el


// -------------------------------- dlist --------------------------------

/** dlist data */
typedef struct
{
    void* prev;
    void* next;
    char value;
} ads_dlist_data_t;

/** dlist header with elements from front to back */
typedef struct
{
    ads_dlist_data_t* front;
    ads_dlist_data_t* back;
    size_t size;
} ads_dlist_t;

/** creates linked list with default allocator (on heap) */
ads_dlist_t* ads_dlist_create();

/** initialises linked list without allocating memory */
void ads_dlist_init(ads_dlist_t* list);

// FIXME: what if we need to insert some element in some place in list,
//        and what if need to pop some element in some place in list?

/** adds some data to linked list */
void* ads_dlist_push_back(ads_dlist_t* list, void* value, size_t size);
void* ads_dlist_push_front(ads_dlist_t* list, void* value, size_t size);

/** returns top element if list (NULL if empty) */
void* ads_dlist_top_front(ads_dlist_t* list);
void* ads_dlist_top_back(ads_dlist_t* list);

/** returns pointer to head element (NULL if empty) */
void ads_dlist_pop_front(ads_dlist_t* list, void* where, size_t size);
void ads_dlist_pop_back(ads_dlist_t* list, void* where, size_t size);

/** returns true, if list is empty */
bool ads_dlist_empty(ads_dlist_t* list);

/** clear list if data is pod */
void ads_dlist_clear_base(ads_dlist_t* lst);

/**
 * destroys any list content using remover, and list itself;
 * sets list value to NULL
 */
void ads_dlist_destroy(ads_dlist_t** list);

#define ads_dlist_push_back_value(lst, type, el)                          \
    *(type*) ads_dlist_push_back(lst, NULL, sizeof(type)) = el

#define ads_dlist_push_front_value(lst, type, el)                         \
    *(type*) ads_dlist_push_front(lst, NULL, sizeof(type)) = el

#define ads_dlist_for(lst, iter)                                          \
    for (ads_dlist_data_t* iter = (lst)->front; iter != NULL;             \
         iter = iter->next)

#define ads_dlist_for_reverse(lst, iter)                                  \
    for (ads_dlist_data_t* iter = (lst)->back; iter != NULL;              \
         iter = iter->prev)

#define ads_dlist_val(iter, type) (*(type*) &(iter->value))

// ----------------------------- alloc pool -----------------------------

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


// ------------------------- alloc pool list ----------------------------
// FIXME: not ready to use

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
