#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/STDLIB_NORETURN.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#if !defined( STDLIB_NORETURN )
#   if defined( _MSC_VER )
#       define STDLIB_NORETURN      __declspec( noreturn )
#   elif defined( __GNUC__ )
#       define STDLIB_NORETURN      __attribute__(( noreturn ))
#   else
#       define STDLIB_NORETURN      [[noreturn]]
#   endif
#endif
