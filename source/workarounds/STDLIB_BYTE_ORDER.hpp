#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/__BYTE_ORDER__.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifdef __BYTE_ORDER__
#   define STDLIB_BYTE_ORDER            __BYTE_ORDER__
#
#   if !(   defined( __ORDER_LITTLE_ENDIAN__ ) && \
            defined( __ORDER_BIG_ENDIAN__) && \
            defined( __ORDER_PDP_ENDIAN__ )         )
#       error __BYTE_ORDER__ is defined but one or more value macros are missing.
#   endif
#
#   define STDLIB_LITTLE_ENDIAN         __ORDER_LITTLE_ENDIAN__     // 1234
#   define STDLIB_BIG_ENDIAN            __ORDER_BIG_ENDIAN__        // 4321
#   define STDLIB_MIXED_ENDIAN          __ORDER_PDP_ENDIAN__        // 3412
#else
#   // The values used by the g++ compiler:
#   define STDLIB_LITTLE_ENDIAN         1234
#   define STDLIB_BIG_ENDIAN            4321
#   define STDLIB_MIXED_ENDIAN          3412
#
#   if defined( _WIN32 )
#       define  STDLIB_BYTE_ORDER       STDLIB_LITTLE_ENDIAN
#   elif defined( __BIG_ENDIAN__ ) || defined( __BIG_ENDIAN ) || defined( _BIG_ENDIAN )
#       define  STDLIB_BYTE_ORDER       STDLIB_BIG_ENDIAN
#   else
#       error Please define STDLIB_BYTE_ORDER, e.g. as STDLIB_LITTLE_ENDIAN.
#   endif
#endif
