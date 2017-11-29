#pragma once

/**
 * File:       adsc.h
 * Created by: kristen
 * Desc:       main interface for using ads library
 */

#include <math.h>

// ---------------- macro

#define ads_max(a, b) ((a) > (b) ? (a) : (b))
#define ads_min(a, b) ((a) < (b) ? (a) : (b))

#include <adsc_alloc.h>
#include <adsc_lists.h>
