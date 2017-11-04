#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// ---------------- macro

/**
 * iterates with apply block of operations to iterator element.
 *
 * example for ads_list_t* lst:
 *   float sum = 0.0f;
 *   ads_list_for(lst, it)
 *   {
 *       float val = ads_list_val(lst, it, float);
 *       sum += val;
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

#define ads_max(a, b) ((a) > (b) ? (a) : (b))
#define ads_min(a, b) ((a) < (b) ? (a) : (b))

// ---------------- typedefs

typedef void (*ads_remover_t)(void*);

// ---------------- structs

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


// ---------------- extern data

// ---------------- methods

// creates linked list with default allocator (on heap)
ads_list_t* ads_list_create();

// initialises linked list without allocating memory
void ads_list_init(ads_list_t* list);

/** adds some data to linked list */
void* ads_list_push(ads_list_t* list, void* value, size_t size);

/** returns head element if list (NULL if empty) */
void* ads_list_top(ads_list_t* list);

/** returns pointer to head element (NULL if empty) */
void ads_list_pop(ads_list_t* list, void* where, size_t size);

/** returns true, if list is empty */
bool ads_list_empty(ads_list_t* list);

void ads_list_clear_base(ads_list_t* lst);

/**
 * destroys any list content using remover, and list itself;
 * sets list value to NULL
 */
void ads_list_destroy(ads_list_t** list);

ads_alloc_pool_t* ads_alloc_pool_create(size_t object_size,
                                        size_t capacity);
void ads_alloc_pool_init(ads_alloc_pool_t* self,
                         size_t object_size,
                         size_t capacity);
void ads_alloc_pool_clear(ads_alloc_pool_t* self);
void ads_alloc_pool_destroy(ads_alloc_pool_t** self);