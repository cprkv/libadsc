#pragma once
#include <adsc_base.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * File:       adsc_lists.h
 * Created by: kristen
 * Desc:       interface for linked lists
 */

// -------------------------------- list --------------------------------
/**
 * \defgroup List
 * @{
 */

/** @brief Linked list data. */
typedef struct
{
    void* next;
    char value;
} ads_list_data_t;

/** @brief Linked list header. */
typedef struct
{
    ads_list_data_t* head;
    size_t size;
    size_t val_size;
} ads_list_t;

#define ads_list_create(type) ads_list_create_ref(sizeof(type))

/**
 * @brief Creates linked list with default allocator (on heap).
 * @note You should use #ads_list_destroy when list is not needed.
 */
ads_list_t* ads_list_create_ref(size_t val_size);

/**
 * @brief Initialises linked list.
 * @param list  Pointer to allocated linked list.
 */
void ads_list_init(ads_list_t* list, size_t val_size);

/**
 * @brief  Inserts element in linked list (makes copy of @p value).
 *
 * @param  list  Pointer to linked list.
 * @param  value Pointer to user data which user wants to
 *               insert (may be @c NULL).
 * @return Pointer to value of created list element.
 *
 * @note   User's value will be copied from pointer's value if
 * value not @c NULL. Otherwise, this function only allocates memory
 * for list element, and returns pointer where user can store
 * actual value.
 */
void* ads_list_push(ads_list_t* list, void* value);

void ads_list_erase(ads_list_t* list, ads_list_data_t* iter);

/**
 * @brief  Shows head element of linked list.
 * @param  list  Pointer to linked list.
 * @return Pointer to value of head element, if it exists.
 *         Otherwise, @c NULL.
 */
void* ads_list_top(ads_list_t* list);

/**
 * @brief  Pops head element of linked list.
 * @param  list   Pointer to linked list.
 * @param  where  Pointer user allocated memory where head element
 *                of linked list will be copied.
 * @note   If list is empty then nothing will happend.
 */
void ads_list_pop(ads_list_t* list, void* where);

/**
 * @brief  Returns @c TRUE if list is empty.
 * @param  list   Pointer to linked list.
 */
bool ads_list_empty(ads_list_t* list);

/**
 * @brief  Clears all list data (then list will be empty).
 * @param  list   Pointer to linked list.
 * @note   All user data will be destroyed as pod values.
 */
void ads_list_clear_ref(ads_list_t* lst, void (*remover)(void*));

/**
 * @brief  Destroys list if it was allocated with #ads_list_create
 *
 * May be used instead of #ads_list_clear_base, if list itself
 * is not needed anymore.
 *
 * @param  list   Pointer to pointer of linked list.
 * @note   Makes list not able to reuse (sets @c *list to @c NULL).
 */
void ads_list_destroy(ads_list_t** list);

/**
 * @brief Iterates with apply block of operations to iterator element.
 *
 * Example for list of @c float:
 * @code
 *   ads_list_t* lst;
 *   ...
 *   float sum = 0.0f;
 *   ads_list_for(lst, it)
 *   {
 *       sum += ads_list_val(lst, it, float);
 *   }
 * @endcode
 */
#define ads_list_for(lst, iter)                                           \
    for (ads_list_data_t* iter = (lst)->head; iter != NULL;               \
         iter = iter->next)

/**
 * @brief Gets referens to list value from iterator.
 * @see ads_list_for
 */
#define ads_list_val(iter, type) (*(type*) &(iter->value))

/**
 * @brief Iterates with apply only one simple operation.
 *
 * Example for list of @c int:
 * @code
 *   ads_list_t* lst;
 *   ...
 *   int sum = 0;
 *   ads_list_for_each(
 *       lst, it,
 *       sum += ads_list_val(it, int)
 *   );
 * @endcode
 */
#define ads_list_for_each(lst, iter, op)                                  \
    for (ads_list_data_t* iter = (lst)->head; iter != NULL;               \
         iter = iter->next)                                               \
        op;

#define ads_list_erase_if(lst, type, predicate)                           \
    {                                                                     \
        for (ads_list_data_t* __list_iter = lst->head;                    \
             __list_iter != NULL;)                                        \
        {                                                                 \
            ads_list_data_t* __list_iter_next = __list_iter->next;        \
            if (predicate(ads_list_val(__list_iter, type)))               \
                ads_list_erase(lst, __list_iter);                         \
            __list_iter = __list_iter_next;                               \
        }                                                                 \
    }

#define ads_list_clear_macro_1(lst) ads_list_clear_ref(lst, NULL)
#define ads_list_clear_macro_2(lst, remover)                              \
    ads_list_clear_ref(lst, remover)
#define ads_list_clear_macro(_1, _2, NAME, ...) NAME

/**
 * Example for list elements allocated with @c malloc:
 * @code
 *   ads_list_t* lst = ads_list_create();
 *   int* ptr = ads_list_push_value(lst, void*, malloc(10));
 *   ...
 *   ads_list_clear(lst, free, void*);
 * @endcode
 */
#define ads_list_clear(...)                                               \
    ads_list_clear_macro(__VA_ARGS__,                                     \
                         ads_list_clear_macro_2,                          \
                         ads_list_clear_macro_1)(__VA_ARGS__)

/**
 * Example for @c ads_list_t*:
 * @code
 *   ads_list_push_value(lst, int, 228);
 *   ads_list_push_value(lst, point2f_t, { 3.4f, 0.3f });
 *   ...
 *   ads_list_destroy(lst, free);
 * @endcode
 */
#define ads_list_push_value(lst, el)                                      \
    *(__typeof__(el)*) ads_list_push(lst, NULL) = el

/**
 * @brief Auto destroys list.
 *
 * Example usage:
 * @code
 *  {
 *      ads_list_auto() lst = ads_list_create();
 *      ads_list_push_value(lst, int, 228);
 *      ...
 *
 *  }   // lst automaticly destroys here
 * @endcode
 */
#define ads_list_auto ads_list_t* ads_auto_cleanup(ads_list_destroy)

/**@}*/
// -------------------------------- dlist --------------------------------
/**
 * \defgroup DList
 * @{
 */

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
    size_t val_size;
} ads_dlist_t;

/** creates linked list with default allocator (on heap) */
ads_dlist_t* ads_dlist_create_ref(size_t val_size);

/** initialises linked list without allocating memory */
void ads_dlist_init(ads_dlist_t* list, size_t val_size);

/** adds some data to linked list */
void* ads_dlist_push_back(ads_dlist_t* list, void* value);
void* ads_dlist_push_front(ads_dlist_t* list, void* value);

/** returns top element if list (NULL if empty) */
void* ads_dlist_top_front(ads_dlist_t* list);
void* ads_dlist_top_back(ads_dlist_t* list);

/** returns pointer to head element (NULL if empty) */
void ads_dlist_pop_front(ads_dlist_t* list, void* where);
void ads_dlist_pop_back(ads_dlist_t* list, void* where);

void ads_dlist_erase(ads_dlist_t* list, ads_dlist_data_t* iter);

/** returns true, if list is empty */
bool ads_dlist_empty(ads_dlist_t* list);

/** clear list if data is pod */
void ads_dlist_clear_ref(ads_dlist_t* lst, void (*remover)(void*));

/**
 * destroys any list content and list itself;
 * sets list value to NULL
 */
void ads_dlist_destroy(ads_dlist_t** list);

#define ads_dlist_create(type) ads_dlist_create_ref(sizeof(type))

#define ads_dlist_push_back_value(lst, el)                                \
    *(__typeof__(el)*) ads_dlist_push_back(lst, NULL) = el

#define ads_dlist_push_front_value(lst, el)                               \
    *(__typeof__(el)*) ads_dlist_push_front(lst, NULL) = el

#define ads_dlist_for(lst, iter)                                          \
    for (ads_dlist_data_t* iter = (lst)->front; iter != NULL;             \
         iter = iter->next)

#define ads_dlist_for_reverse(lst, iter)                                  \
    for (ads_dlist_data_t* iter = (lst)->back; iter != NULL;              \
         iter = iter->prev)

#define ads_dlist_val(iter, type) (*(type*) &(iter->value))

#define ads_dlist_clear_macro_1(lst) ads_dlist_clear_ref(lst, NULL)
#define ads_dlist_clear_macro_2(lst, remover)                             \
    ads_dlist_clear_ref(lst, remover)
#define ads_dlist_clear_macro(_1, _2, NAME, ...) NAME

#define ads_dlist_clear(...)                                              \
    ads_dlist_clear_macro(__VA_ARGS__,                                    \
                          ads_dlist_clear_macro_2,                        \
                          ads_dlist_clear_macro_1)(__VA_ARGS__)

#define ads_dlist_auto ads_dlist_t* ads_auto_cleanup(ads_dlist_destroy)

#define ads_dlist_erase_if(lst, type, predicate)                          \
    {                                                                     \
        for (ads_dlist_data_t* __list_iter = lst->front;                  \
             __list_iter != NULL;)                                        \
        {                                                                 \
            ads_dlist_data_t* __list_iter_next = __list_iter->next;       \
            if (predicate(ads_dlist_val(__list_iter, type)))              \
                ads_dlist_erase(lst, __list_iter);                        \
            __list_iter = __list_iter_next;                               \
        }                                                                 \
    }

/**@}*/
