#pragma once

/**
 * @file ads_base.h
 * @brief base typedefs, macro
 */

#include <math.h>
#include <stddef.h>
#include <stdbool.h>

#define ads_max(a, b) ((a) > (b) ? (a) : (b))
#define ads_min(a, b) ((a) < (b) ? (a) : (b))
#define ads_auto_cleanup(x) __attribute__((cleanup(x)))
#define auto_t __auto_type
