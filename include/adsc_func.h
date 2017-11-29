#pragma once

/**
 * File:       adsc.h
 * Created by: kristen
 * Desc:       functional macro
 */

// #define ads_lambda_1(ret, in1, function_like)
//     ({
//         ret __fn__(in1 _1) function_like;
//         __fn__;
//     })

// #define ads_lambda_2(ret, in1, in2, function_like)
//     ({
//         ret __fn__(in1 _1, in2 _2) function_like;
//         __fn__;
//     })

// #define ads_lambda_3(ret, in1, in2, in3, function_like)
//     ({
//         ret __fn__(in1 _1, in2 _2, in3 _3) function_like;
//         __fn__;
//     })

// #define ads_lambda_4(ret, in1, in2, in3, in4, function_like)
//     ({
//         ret __fn__(in1 _1, in2 _2, in3 _3, in4 _4) function_like;
//         __fn__;
//     })

// #define ads_lambda_5(ret, in1, in2, in3, in4, in5, function_like)
//     ({
//         ret __fn__(in1 _1, in2 _2, in3 _3, in4 _4, in5 _5)
//         function_like;
//         __fn__;
//     })

// #define ads_lambda_6(ret, in1, in2, in3, in4, in5, in6, function_like)
//     ({
//         ret __fn__(in1 _1, in2 _2, in3 _3, in4 _4, in5 _5, in6 _6)
//             function_like;
//         __fn__;
//     })

// #define _GET_OVERRIDE(_1, _2, _3, _4, _5, NAME, ...) NAME

// #define ads_lambda(...)
//     _GET_OVERRIDE(__VA_ARGS__,
//                   ads_lambda_error,
//                   ads_lambda_error,
//                   ads_lambda_1,
//                   ads_lambda_2,
//                   ads_lambda_3,
//                   ads_lambda_4,
//                   ads_lambda_5,
//                   ads_lambda_6)
//     (__VA_ARGS__)

#ifdef ads_compiler_gnuc

#define ads_lambda(l_ret_type, l_arguments, l_body)                       \
    ({                                                                    \
        l_ret_type l_anonymous_functions_name l_arguments l_body;         \
        &l_anonymous_functions_name;                                      \
    })

#else

#define ads_lambda(...)                                                   \
    error_non_gcc_compilators_not_support_lambda_functions

#endif