#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/__BYTE_ORDER__.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef __BYTE_ORDER__
#   // The values used by the g++ compiler:
#   define __ORDER_LITTLE_ENDIAN__  1234
#   define __ORDER_BIG_ENDIAN__     4321
#   define __ORDER_PDP_ENDIAN__     3412
#
#   if defined( _WIN32 )
#       define  __BYTE_ORDER__      __ORDER_LITTLE_ENDIAN__
#   elif defined( __BIG_ENDIAN__ ) || defined( __BIG_ENDIAN ) || defined( _BIG_ENDIAN )
#       define  __BYTE_ORDER__      __ORDER_BIG_ENDIAN__
#   elif defined( _ARCH_PPC ) || defined( __PPC__ ) || defined( __PPC ) || defined( PPC ) \
         || defined( __powerpc__ ) || defined( __powerpc ) || defined( powerpc )
#       define  __BYTE_ORDER__      __ORDER_BIG_ENDIAN__
#   else
#       error Please define __BYTE_ORDER__, e.g. as __LITTLE_ENDIAN__.
#   endif
#endif
