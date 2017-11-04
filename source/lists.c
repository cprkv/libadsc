#include <adsc.h>
#include <adsc_internal.h>
#include <string.h>

/**
 * File:       lists.c
 * Created by: kristen
 * Desc:       linked lists data type implimentation
 */

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

    if (value) memcpy(&(elem->value), value, size);
#ifdef DEBUG
    else
        memset(&(elem->value), 0, size);
#endif

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

        if (where) memcpy(where, &(tmp->value), size);

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
    if (lst->head)
        while (!ads_list_empty(lst))
            ads_list_pop(lst, NULL, 0);
}

void ads_list_init(ads_list_t* list)
{
    ads_assert(list);
    list->size = 0;
    list->head = NULL;
}