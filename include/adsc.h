#pragma once
#include <stdlib.h>

// ---------------- macro

// ---------------- typedefs

// ---------------- structs

struct ads_list_data_t // list data
{
    void* value;
    struct ads_list_data_t* next;
};

struct ads_list_t // list header
{
    struct ads_list_data_t* head;
    size_t size;
};

// ---------------- extern data

// ---------------- methods

// linked list without deallocator
struct ads_list_t* ads_list_create();

// adds some data to linked list
void ads_list_push(struct ads_list_t* list, void* value);

// returns head element if list (NULL if empty)
void* ads_list_top(struct ads_list_t* list);

// returns pointer to head element (NULL if empty)
void* ads_list_pop(struct ads_list_t* list);