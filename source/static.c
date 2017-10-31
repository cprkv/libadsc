#include <adsc.h>

// ------------------

void default_remover(void* ptr)
{
    free(ptr);
}

// ------------------

remover_t ads_default_remover = default_remover;