#include <adsc.h>

struct adslist_t* adslist_create_free()
{
    return adslist_create(NULL);
}

// linked list with custom deallocator
struct adslist_t* adslist_create_custom(remover_t remover)
{
    ads_alloc_struct(list, adslist_t);
    list->size = 0;
    list->remover = remover;
    list->data = NULL;

    return list;
}

// adds some data to linked list
void adslist_push(struct adslist_t* list, void* value)
{
    ads_alloc_struct(elem, adslist_data_t);
    elem->next = list->data;
    elem->value = value;
    list->data = elem;
}

void* adslist_top(struct adslist_t* list)
{
    return list->data;
}

void* adslist_pop(struct adslist_t* list)
{
    struct adslist_data_t* tmp = list->data;

    if (list->data)
    {
        list->data = list->data->next;

        if (list->remover)
        {
            list->remover(tmp);
            tmp = NULL;
        }
    }

    return tmp;
}