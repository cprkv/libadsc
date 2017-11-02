#include <adsc.h>
#include <adsc_internal.h>

ads_list_t* ads_list_create()
{
    ads_alloc_struct(list, ads_list_t);
    ads_assert(list);
    ads_list_init(list);

    return list;
}

void* ads_list_push(ads_list_t* list, void* value)
{
    ads_assert(list);
    ads_alloc_struct(elem, ads_list_data_t);
    ads_assert(elem);
    elem->next = list->head;
    elem->value = value;
    list->head = elem;
    list->size++;

    return value;
}

void* ads_list_top(ads_list_t* list)
{
    ads_assert(list);
    return list->head ? list->head->value : NULL;
}

void* ads_list_pop(ads_list_t* list)
{
    ads_assert(list);
    void* ret = NULL;

    if (list->head)
    {
        ads_list_data_t* tmp = list->head;
        list->head = tmp->next;
        ret = tmp->value;
        ads_free(tmp);
        list->size--;
    }

    return ret;
}

bool ads_list_empty(ads_list_t* list)
{
    ads_assert(list);
    return !list->head;
}

void ads_list_destroy(ads_list_t** list, ads_remover_t remover)
{
    ads_assert(list && *list);

    if ((*list)->head)
    {
        ads_list_clear((*list), remover);
    }

    ads_free((*list));
    *list = NULL;
}

void ads_list_init(ads_list_t* list)
{
    ads_assert(list);
    list->size = 0;
    list->head = NULL;
}