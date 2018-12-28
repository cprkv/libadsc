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

#define ads_list_declare(prefix, type, allocator)                         \
  struct prefix##_value                                                   \
  {                                                                       \
    type value;                                                           \
    struct prefix##_value* next;                                          \
  };                                                                      \
                                                                          \
  struct prefix                                                           \
  {                                                                       \
    allocator alloc;                                                      \
    size_t size;                                                          \
    struct prefix##_value* head;                                          \
  };                                                                      \
                                                                          \
  void prefix##_init(struct prefix* self, allocator alloc)                \
  {                                                                       \
    self->alloc = alloc;                                                  \
    self->size = 0;                                                       \
    self->head = NULL;                                                    \
  }                                                                       \
                                                                          \
  ads_result prefix##_push_ref(struct prefix* self, type* value)          \
  {                                                                       \
    struct prefix##_value* head = self->alloc.allocate(                   \
        &self->alloc, sizeof(struct prefix##_value));                     \
    if (head == NULL)                                                     \
    {                                                                     \
      return ads_result_error;                                            \
    }                                                                     \
    memcpy(&head->value, value, sizeof(type));                            \
    head->next = self->head;                                              \
    self->head = head;                                                    \
    self->size++;                                                         \
    return ads_result_ok;                                                 \
  }                                                                       \
                                                                          \
  ads_result prefix##_push(struct prefix* self, type value)               \
  {                                                                       \
    return prefix##_push_ref(self, &value);                               \
  }
;