#pragma once

/**
 * @file ads_list.h
 * @brief interface for linked lists
 */

#include <ads_alloc.h>
#include <ads_base.h>

#ifndef ads_list_declare
#define ads_list_declare(postfix, type, allocator)                             \
  struct ads_list_##postfix                                                    \
  {                                                                            \
    type value;                                                                \
    struct ads_list_##postfix* next;                                           \
  };                                                                           \
                                                                               \
  struct ads_list_##postfix* ads_list_push_ref_##postfix(                      \
    struct ads_list_##postfix* self, type* value)                              \
  {                                                                            \
    struct ads_list_##postfix* head =                                          \
      allocator->allocate(sizeof(struct ads_list_##postfix));                  \
    memcpy(&head->value, value, sizeof(type));                                 \
    head->next = self;                                                         \
    return head;                                                               \
  }                                                                            \
                                                                               \
#endif