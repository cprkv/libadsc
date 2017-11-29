#include <adsc.h>
#include <adsc_internal.h>

/**
 * File:       allocs.c
 * Created by: kristen
 * Desc:       allocators data type implimentation
 */

// ----------------------- private funcs

#define pool_init_blocks(start_block, free_objects_count, object_size)    \
    {                                                                     \
        char* start = start_block;                                        \
        char* end = start + (free_objects_count - 1) * object_size;       \
                                                                          \
        for (char* i = start; i != end; i += object_size)                 \
            *(void**) i = (void*) (i + object_size);                      \
    }

void* pool_alloc(void* self)
{
    ads_alloc_pool_t* this = self;
    ads_assert(this && this->pool);
    void* ptr;

    ptr = this->start;
    this->start =
        this->size >= this->capacity - 1 ? NULL : *(void**) this->start;
    if (ptr) this->size++;

    return ptr;
}

void pool_dealloc(void* self, void* ptr)
{
    ads_alloc_pool_t* this = self;
    ads_assert(this && this->pool);
    *(void**) ptr = this->start ? *(void**) this->start : NULL;
    this->start = ptr;
    this->size--;
}

// ----------------------- methods

ads_alloc_pool_t* ads_alloc_pool_create(size_t object_size,
                                        size_t capacity)
{
    ads_alloc_struct(this, ads_alloc_pool_t);
    ads_alloc_pool_init(this, object_size, capacity);
    return this;
}

void ads_alloc_pool_init(ads_alloc_pool_t* self,
                         size_t object_size,
                         size_t capacity)
{
    ads_assert(capacity > 1);
    self->alloc = pool_alloc;
    self->dealloc = pool_dealloc;
    self->object_size = ads_max(object_size, sizeof(void*)); // in bytes
    self->size = 0; // object count
    self->capacity = capacity;
    self->pool = malloc(self->capacity * self->object_size);
    self->start = self->pool;

    pool_init_blocks(self->start, self->capacity, self->object_size);
}

void ads_alloc_pool_clear(ads_alloc_pool_t* self)
{
    ads_assert(self);

    if (self->pool)
    {
        free(self->pool);
        self->size = 0;
        self->capacity = 0;
        self->pool = NULL;
        self->start = NULL;
    }
}

void ads_alloc_pool_destroy(ads_alloc_pool_t** self)
{
    ads_assert(self && *self);
    ads_alloc_pool_clear(*self);
    ads_free(*self);
    *self = NULL;
}

// ------------- alloc pool list

ads_alloc_pool_list_t* ads_alloc_pool_list_create(size_t object_size,
                                                  size_t capacity)
{
    ads_assert(object_size > 1);
    ads_assert(capacity > 0);
    ads_alloc_struct(self, ads_alloc_pool_list_t);
    ads_alloc_pool_list_init(self, object_size, capacity);

    return self;
}

void ads_alloc_pool_list_init(ads_alloc_pool_list_t* self,
                              size_t object_size,
                              size_t capacity)
{
    ads_assert(self);
    self->list = malloc(sizeof(ads_alloc_pool_list_el_t));
    self->list->next = NULL;
    ads_alloc_pool_init(&self->list->poll, object_size, capacity);
}

void ads_alloc_pool_list_clear(ads_alloc_pool_list_t* self)
{
    ads_assert(self);
}

void ads_alloc_pool_list_destroy(ads_alloc_pool_list_t** self)
{
    ads_assert(self && *self);
}

void ads_free_impl(void** ptr)
{
    free(*ptr);
}