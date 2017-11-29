#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <adsc_base.h>

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
} ads_list_t;

/**
 * @brief Creates linked list with default allocator (on heap).
 * @note You should use #ads_list_destroy when list is not needed.
 */
ads_list_t* ads_list_create();

/**
 * @brief Initialises linked list.
 * @param list  Pointer to allocated linked list.
 */
void ads_list_init(ads_list_t* list);

/**
 * @brief  Inserts element in linked list (makes copy of @p value).
 *
 * @param  list  Pointer to linked list.
 * @param  value Pointer to user data which user wants to
 *               insert (may be @c NULL).
 * @param  size  Size of user's @p value in bytes.
 * @return Pointer to value of created list element.
 *
 * @note   User's value will be copied from pointer's value if
 * value not @c NULL. Otherwise, this function only allocates memory
 * for list element, and returns pointer where user can store
 * actual value.
 */
void* ads_list_push(ads_list_t* list, void* value, size_t size);

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
 * @param  size   Size of element user wants to get.
 * @note   If list is empty then nothing will happend.
 */
void ads_list_pop(ads_list_t* list, void* where, size_t size);

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
void ads_list_clear_base(ads_list_t* lst);

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

/**
 * Example for list elements allocated with @c malloc:
 * @code
 *   ads_list_t* lst = ads_list_create();
 *   int* ptr = ads_list_push_value(lst, void*, malloc(10));
 *   ...
 *   ads_list_clear(lst, free, void*);
 * @endcode
 */
#define ads_list_clear(lst, deleter, type)                                \
    {                                                                     \
        while (!ads_list_empty(lst))                                      \
        {                                                                 \
            type val;                                                     \
            ads_list_pop(lst, &val, sizeof(type));                        \
            deleter(val);                                                 \
        }                                                                 \
    }

/**
 * Example for @c ads_list_t*:
 * @code
 *   ads_list_push_value(lst, int, 228);
 *   ads_list_push_value(lst, point2f_t, { 3.4f, 0.3f });
 *   ...
 *   ads_list_destroy(lst, free);
 * @endcode
 */
#define ads_list_push_value(lst, type, el)                                \
    *(type*) ads_list_push(lst, NULL, sizeof(type)) = el

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

/**@}*/