#pragma once

/**
 * File:       adsc_base.h
 * Created by: kristen
 * Desc:       Base typedefs, macro and functions for ADSC library.
 */ 

#ifdef __GNUC__
#define ads_auto_cleanup(x) __attribute__((cleanup(x)))
#else
#define ads_auto_cleanup(x) error-no-auto-cleanup
#endif