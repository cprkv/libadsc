#pragma once

/**
 * File:       adsc_internal.h
 * Created by: kristen
 * Desc:       internal header
 */

#define ads_alloc_struct(var, type) struct type* var = malloc(sizeof(struct type))
#define ads_free(ptr) free(ptr)