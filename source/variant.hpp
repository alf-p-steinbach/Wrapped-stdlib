#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/variant.hpp>
//
// A discriminated union, essentially a boxed value of one of N specified types.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>         // STDLIB_COMPILER_SUPPORTS_CPP17
#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#if STDLIB_USE_EXPERIMENTAL_CPP17
#   include <experimental/variant>
#elif STDLIB_COMPILER_SUPPORTS_CPP17
#   include <variant>
#else
#   ifdef _MSC_VER
#       error "<variant> is apparently not available (use option `/std:c++latest`?)."
#   else
#       error "<variant> appears not available (try define STDLIB_USE_EXPERIMENTAL_CPP17?)."
#   endif
#endif

#ifdef STDLIB_HOIST_UP_VARIANT_TEMPLATE
    namespace std {
        using experimental::variant;
    }  // namespace std;
#endif

#include <stdlib/all/non_io_fixes.hpp>
