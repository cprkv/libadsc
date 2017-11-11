/**
 * File:       lists.c
 * Created by: kristen
 * Desc:       linked lists data type implimentation
 */

#include <adsc.h>
#include <adsc_internal.h>
#include <string.h>

// -------------------------------- list --------------------------------

ads_list_t* ads_list_create()
{
    ads_alloc_struct(list, ads_list_t);
    ads_assert(list);
    ads_list_init(list);

    return list;
}

void* ads_list_push(ads_list_t* list, void* value, size_t size)
{
    ads_assert(list);
    ads_assert(size > sizeof(char));
    ads_list_data_t* elem = malloc(sizeof(void*) + size);
    ads_assert(elem);
    elem->next = list->head;

    if (value)
        memcpy(&(elem->value), value, size);
    // #ifdef DEBUG
    //     else
    //         memset(&(elem->value), 0, size);
    // #endif

    list->head = elem;
    list->size++;

    return &(elem->value);
}

void* ads_list_top(ads_list_t* list)
{
    ads_assert(list);
    return list->head ? &(list->head->value) : NULL;
}

void ads_list_pop(ads_list_t* list, void* where, size_t size)
{
    ads_assert(list);

    if (list->head)
    {
        ads_list_data_t* tmp = list->head;
        list->head = tmp->next;

        if (where)
            memcpy(where, &(tmp->value), size);

        ads_free(tmp);
        list->size--;
    }
}

bool ads_list_empty(ads_list_t* list)
{
    ads_assert(list);
    return !list->head;
}

void ads_list_destroy(ads_list_t** list)
{
    ads_assert(list && *list);
    ads_list_clear_base(*list);
    ads_free((*list));
    *list = NULL;
}

void ads_list_clear_base(ads_list_t* lst)
{
    // if (lst->head)
    //     while (!ads_list_empty(lst))
    //         ads_list_pop(lst, NULL, 0);

    ads_assert(lst);
    ads_list_data_t* tmp = lst->head;
    ads_list_data_t* freed;

    while (tmp)
    {
        freed = tmp;
        tmp = tmp->next;
        ads_free(freed);
    }

    lst->head = NULL;
    lst->size = 0;
}

void ads_list_init(ads_list_t* list)
{
    ads_assert(list);
    list->size = 0;
    list->head = NULL;
}

// -------------------------------- dlist --------------------------------

ads_dlist_t* ads_dlist_create()
{
    ads_alloc_struct(list, ads_dlist_t);
    ads_assert(list);
    ads_dlist_init(list);

    return list;
}

void ads_dlist_init(ads_dlist_t* list)
{
    list->back = NULL;
    list->front = NULL;
    list->size = 0;
}

void* ads_dlist_push_back(ads_dlist_t* list, void* value, size_t size)
{
    ads_assert(list);
    ads_assert(size > sizeof(char));
    ads_dlist_data_t* elem = malloc(sizeof(void*) + sizeof(void*) + size);
    ads_assert(elem);
    elem->prev = list->back;
    elem->next = NULL;

    if (value)
        memcpy(&(elem->value), value, size);

    if (list->back)
        list->back->next = elem;
    else 
        list->front = elem;

    list->back = elem;
    list->size++;

    return &(elem->value);
}

void* ads_dlist_push_front(ads_dlist_t* list, void* value, size_t size)
{
    ads_assert(list);
    ads_assert(size > sizeof(char));
    ads_dlist_data_t* elem = malloc(sizeof(void*) + sizeof(void*) + size);
    ads_assert(elem);
    elem->prev = NULL;
    elem->next = list->front;

    if (value)
        memcpy(&(elem->value), value, size);

    if (list->front)
        list->front->prev = elem;
    else 
        list->back = elem;

    list->front = elem;
    list->size++;

    return &(elem->value);
}

void* ads_dlist_top_front(ads_dlist_t* list)
{
    ads_assert(list);
    return list->front ? &(list->front->value) : NULL;
}

void* ads_dlist_top_back(ads_dlist_t* list)
{
    ads_assert(list);
    return list->back ? &(list->back->value) : NULL;
}

void ads_dlist_pop_front(ads_dlist_t* list, void* where, size_t size)
{
    ads_assert(list);

    if (list->front)
    {
        ads_dlist_data_t* tmp = list->front;
        list->front = tmp->next;

        if (list->front)
            list->front->prev = NULL;
        else 
            list->back = NULL;

        if (where)
            memcpy(where, &(tmp->value), size);

        ads_free(tmp);
        list->size--;
    }
}

void ads_dlist_pop_back(ads_dlist_t* list, void* where, size_t size)
{
    ads_assert(list);

    if (list->back)
    {
        ads_dlist_data_t* tmp = list->back;
        list->back = tmp->prev;

        if (list->back)
            list->back->next = NULL;
        else 
            list->front = NULL;

        if (where)
            memcpy(where, &(tmp->value), size);

        ads_free(tmp);
        list->size--;
    }
}

bool ads_dlist_empty(ads_dlist_t* list)
{
    ads_assert(list);
    return !list->front;
}

void ads_dlist_clear_base(ads_dlist_t* lst)
{
    ads_assert(lst);
    ads_dlist_data_t* tmp = lst->front;
    ads_dlist_data_t* freed;

    while (tmp)
    {
        freed = tmp;
        tmp = tmp->next;
        ads_free(freed);
    }

    lst->front = NULL;
    lst->back = NULL;
    lst->size = 0;
}

void ads_dlist_destroy(ads_dlist_t** list)
{
    ads_assert(list && *list);
    ads_dlist_clear_base(*list);
    ads_free((*list));
    *list = NULL;
}