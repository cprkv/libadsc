#include <adsc_internal.h>
#include <adsc_vec.h>

ads_vec_t* ads_vec_create_ref(size_t val_size, size_t size)
{
  ads_alloc_struct(vec, ads_vec_t);
  ads_assert(vec);
  ads_vec_init(vec, val_size, size);
  return vec;
}

void ads_vec_init(ads_vec_t* vec, size_t val_size, size_t size)
{
  ads_assert(vec && val_size);
  vec->capacity = ads_fast_close_2(size);
  vec->size = size;
  vec->val_size = val_size;
  vec->memory = ads_malloc(vec->capacity * val_size);
}

void ads_vec_clear_ref(ads_vec_t* vec, void (*remover)(void*))
{
  ads_assert(vec);

  for (size_t i = 0; i < vec->size; i++)
    remover(ads_vec_ptr(vec, i));

  ads_vec_resize(vec, 0);
}

void ads_vec_destroy(ads_vec_t** vec)
{
  ads_assert(vec && *vec);
  ads_free((*vec)->memory);
  ads_free((*vec));
  *vec = NULL;
}

void ads_vec_resize(ads_vec_t* vec, size_t size)
{
  ads_assert(vec);

  if (size >= vec->size && size <= vec->capacity)
  {
    vec->size = size;
  }
  else
  {
    vec->capacity = ads_fast_close_2(size);
    vec->size = size;
    vec->memory = ads_realloc(vec->memory, vec->capacity * vec->val_size);
  }
}