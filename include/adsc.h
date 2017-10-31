#pragma once
#include <stdlib.h>

// ---------------- macro

#define ads_alloc_struct(var, type) struct type* var = malloc(sizeof(struct type))

// ---------------- typedefs

typedef void (*remover_t)(void*);

// ---------------- structs

struct adslist_data_t // list data
{
    void* value;
    struct adslist_data_t* next;
};

struct adslist_t // list header
{
    struct adslist_data_t* data;
    size_t size;
    remover_t remover;
};

// ---------------- extern data

extern remover_t ads_default_remover;

// ---------------- methods

// linked list without deallocator
struct adslist_t* adslist_create();

// linked list with custom deallocator
struct adslist_t* adslist_create_custom(remover_t remover);

// adds some data to linked list
void adslist_push(struct adslist_t* list, void* value);

// returns first element in list (NULL if empty)
void* adslist_top(struct adslist_t* list);

// if struct has deallocator returns NULL, value otherwise
void* adslist_pop(struct adslist_t* list);