#pragma once
#include <adsc_base.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
  char* memory;
  size_t size;
  size_t capacity;
  size_t val_size;
} ads_vec_t;

ads_vec_t* ads_vec_create_ref(size_t val_size, size_t size);

void ads_vec_init(ads_vec_t* vec, size_t val_size, size_t size);

void ads_vec_resize(ads_vec_t* vec, size_t size);

void ads_vec_clear_ref(ads_vec_t* vec, void (*remover)(void*));

void ads_vec_destroy(ads_vec_t** vec);


#define ads_vec_create_macro_1(type) ads_vec_create_ref(sizeof(type), 0)
#define ads_vec_create_macro_2(type, size)                                \
  ads_vec_create_ref(sizeof(type), size)

#define ads_vec_create_macro(_1, _2, NAME, ...) NAME

#define ads_vec_create(...)                                               \
  ads_vec_create_macro(__VA_ARGS__,                                       \
                       ads_vec_create_macro_2,                            \
                       ads_vec_create_macro_1)(__VA_ARGS__)

#define ads_vec_ptr(vec, idx) (vec->memory + (vec->val_size) * (idx))
#define ads_vec_val(vec, type) ((type*) vec->memory)

#define ads_vec_auto ads_vec_t* ads_auto_cleanup(ads_vec_destroy)