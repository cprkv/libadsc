#pragma once

/**
 * @file ads_list.h
 * @brief interface for linked lists
 */

#include <ads_alloc.h>
#include <ads_base.h>
#include <string.h> 

#define ads_result int
#define ads_result_error -1
#define ads_result_ok 0

#define ads_list_declare(postfix, type, allocator)                             \
  struct ads_list_value_##postfix                                              \
  {                                                                            \
    type value;                                                                \
    struct ads_list_value_##postfix* next;                                           \
  };                                                                           \
                                                                               \
  struct ads_list_##postfix                                                    \
  {                                                                            \
    allocator alloc;                                                           \
    size_t size;                                                               \
    struct ads_list_value_##postfix* head;                                           \
  };                                                                           \
                                                                               \
  void ads_list_init_##postfix(struct ads_list_##postfix* self,                \
                               allocator alloc)                                \
  {                                                                            \
    self->alloc = alloc;                                                       \
    self->size = 0;                                                            \
    self->head = NULL;                                                         \
  }                                                                            \
                                                                               \
  ads_result ads_list_push_ref_##postfix(struct ads_list_##postfix* self,      \
                                         type* value)                          \
  {                                                                            \
    struct ads_list_value_##postfix* head = self->alloc.allocate(              \
      &self->alloc, sizeof(struct ads_list_value_##postfix));                  \
    if (head == NULL) {                                                        \
      return ads_result_error;                                                 \
    }                                                                          \
    memcpy(&head->value, value, sizeof(type));                                 \
    head->next = self->head;                                                   \
    self->head = head;                                                         \
    self->size++;                                                              \
    return ads_result_ok;                                                      \
  }                                                                            \
                                                                               \
  ads_result ads_list_push_##postfix(struct ads_list_##postfix* self,          \
                                     type value)                               \
  {                                                                            \
    return ads_list_push_ref_##postfix(self, &value);                          \
  }
;