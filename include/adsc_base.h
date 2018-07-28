#pragma once

/**
 * File:       adsc_base.h
 * Created by: kristen
 * Desc:       Base typedefs, macro and functions for ADSC library.
 */

#include <math.h>
#include <stddef.h>

#define ads_max(a, b) ((a) > (b) ? (a) : (b))
#define ads_min(a, b) ((a) < (b) ? (a) : (b))

#define ads_auto_cleanup(x) __attribute__((cleanup(x)))

#define auto_t __auto_type

// ----- algo

size_t ads_fast_close_2(size_t i);