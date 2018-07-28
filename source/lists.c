/**
 * File:       lists.c
 * Created by: kristen
 * Desc:       linked lists data type implimentation
 */

#include <adsc.h>
#include <adsc_internal.h>
#include <string.h>

// -------------------------------- list --------------------------------

ads_list_t* ads_list_create_ref(size_t val_size)
{
  ads_alloc_struct(list, ads_list_t);
  ads_assert(list);
  ads_list_init(list, val_size);

  return list;
}

void* ads_list_push(ads_list_t* list, void* value)
{
  ads_assert(list);
  ads_list_data_t* elem = ads_malloc(sizeof(void*) + list->val_size);
  ads_assert(elem);
  elem->next = list->head;

  if (value)
    memcpy(&(elem->value), value, list->val_size);

  list->head = elem;
  list->size++;

  return &(elem->value);
}

void ads_list_erase(ads_list_t* list, ads_list_data_t* iter)
{
  ads_assert(list);
  ads_assert(iter);

  if (!list->head)
    return;

  if (list->head == iter)
  {
    list->head = iter->next;
    ads_free(iter);
    list->size--;
  }
  else
  {
    ads_list_data_t* i = list->head;
    for (; i->next != iter && i->next != NULL; i = i->next)
      ;

    if (i->next)
    {
      i->next = iter->next;
      ads_free(iter);
      list->size--;
    }
  }
}

void* ads_list_top(ads_list_t* list)
{
  ads_assert(list);
  return list->head ? &(list->head->value) : NULL;
}

void ads_list_pop(ads_list_t* list, void* where)
{
  ads_assert(list);

  if (list->head)
  {
    ads_list_data_t* tmp = list->head;
    list->head = tmp->next;

    if (where)
      memcpy(where, &(tmp->value), list->val_size);

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
  ads_list_clear_ref(*list, NULL);
  ads_free((*list));
  *list = NULL;
}

void ads_list_clear_ref(ads_list_t* lst, void (*remover)(void*))
{
  ads_assert(lst);
  ads_list_data_t* tmp = lst->head;
  ads_list_data_t* freed;

  while (tmp)
  {
    freed = tmp;

    if (remover)
      remover(&freed->value);

    tmp = tmp->next;
    ads_free(freed);
  }

  lst->head = NULL;
  lst->size = 0;
}

void ads_list_init(ads_list_t* list, size_t val_size)
{
  ads_assert(list);
  ads_assert(val_size >= sizeof(char));
  list->head = NULL;
  list->size = 0;
  list->val_size = val_size;
}

// -------------------------------- dlist --------------------------------

ads_dlist_t* ads_dlist_create_ref(size_t val_size)
{
  ads_alloc_struct(list, ads_dlist_t);
  ads_assert(list);
  ads_dlist_init(list, val_size);

  return list;
}

void ads_dlist_init(ads_dlist_t* list, size_t val_size)
{
  ads_assert(val_size > sizeof(char));
  list->back = NULL;
  list->front = NULL;
  list->size = 0;
  list->val_size = val_size;
}

void* ads_dlist_push_back(ads_dlist_t* list, void* value)
{
  ads_assert(list);
  ads_dlist_data_t* elem =
      ads_malloc(sizeof(void*) + sizeof(void*) + list->val_size);
  ads_assert(elem);
  elem->prev = list->back;
  elem->next = NULL;

  if (value)
    memcpy(&(elem->value), value, list->val_size);

  if (list->back)
    list->back->next = elem;
  else
    list->front = elem;

  list->back = elem;
  list->size++;

  return &(elem->value);
}

void* ads_dlist_push_front(ads_dlist_t* list, void* value)
{
  ads_assert(list);
  ads_dlist_data_t* elem =
      ads_malloc(sizeof(void*) + sizeof(void*) + list->val_size);
  ads_assert(elem);
  elem->prev = NULL;
  elem->next = list->front;

  if (value)
    memcpy(&(elem->value), value, list->val_size);

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

void ads_dlist_pop_front(ads_dlist_t* list, void* where)
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
      memcpy(where, &(tmp->value), list->val_size);

    ads_free(tmp);
    list->size--;
  }
}

void ads_dlist_pop_back(ads_dlist_t* list, void* where)
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
      memcpy(where, &(tmp->value), list->val_size);

    ads_free(tmp);
    list->size--;
  }
}

void ads_dlist_erase(ads_dlist_t* list, ads_dlist_data_t* iter)
{
  ads_assert(list && iter);
  if (!list->front)
    return;

  auto_t is_first = list->front == iter;
  auto_t is_last = list->back == iter;

  if (is_first || is_last)
  {
    if (is_first && is_last)
    {
      list->front = list->back = NULL;
    }
    else if (is_first)
    {
      list->front = iter->next;
      list->front->prev = NULL;
    }
    else // is_last
    {
      list->back = iter->prev;
      list->back->next = NULL;
    }
  }
  else
  {
    ads_dlist_data_t* p = iter->prev;
    ads_dlist_data_t* n = iter->next;
    p->next = n;
    n->prev = p;
  }

  ads_free(iter);
  list->size--;
}

bool ads_dlist_empty(ads_dlist_t* list)
{
  ads_assert(list);
  return !list->front;
}

void ads_dlist_clear_ref(ads_dlist_t* lst, void (*remover)(void*))
{
  ads_assert(lst);
  ads_dlist_data_t* tmp = lst->front;
  ads_dlist_data_t* freed;

  while (tmp)
  {
    freed = tmp;

    if (remover)
      remover(&freed->value);

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
  ads_dlist_clear_ref(*list, NULL);
  ads_free((*list));
  *list = NULL;
}
