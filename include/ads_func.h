#pragma once

/**
 * @file ads_func.h
 * @brief functional macro
 */

#define ads_lambda(l_ret_type, l_body)                                    \
  ({                                                                      \
    l_ret_type l_anonymous_functions_name l_body;                         \
    &l_anonymous_functions_name;                                          \
  })
