#include <ads.h>
#include <ads_internal.h>

void* var_alloc(struct ads_alloc* _, size_t size)
{
  return malloc(size);
}

void var_free(struct ads_alloc* _, void* ptr)
{
  free(ptr);
}

struct ads_alloc ads_alloc_default()
{
  auto_t alloc = (struct ads_alloc){
      .allocate = var_alloc,
      .free = var_free,
  };
  return alloc;
}