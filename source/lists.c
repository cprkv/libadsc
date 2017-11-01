#include <adsc.h>
#include <adsc_internal.h>

struct ads_list_t* ads_list_create()
{
    ads_alloc_struct(list, ads_list_t);
    list->size = 0;
    list->head = NULL;

    return list;
}

void ads_list_push(struct ads_list_t* list, void* value)
{
    ads_alloc_struct(elem, ads_list_data_t);
    elem->next = list->head;
    elem->value = value;
    list->head = elem;
}

void* ads_list_top(struct ads_list_t* list)
{
    return list->head ? list->head->value : NULL;
}

void* ads_list_pop(struct ads_list_t* list)
{
    void* ret = NULL;
    
    if (list->head)
    {
        struct ads_list_data_t* tmp = list->head;
        list->head = list->head->next;
        ret = tmp->value;
        ads_free(tmp);
    }

    return ret;
}