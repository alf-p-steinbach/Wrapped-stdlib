#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/optional.hpp>
//
// basic_string_view template, specializations string_view and wstring_view.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>         // STDLIB_COMPILER_SUPPORTS_CPP17
#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#if STDLIB_USE_EXPERIMENTAL_CPP17
#   include <experimental/optional>
#elif STDLIB_COMPILER_SUPPORTS_CPP17
#   include <optional>
#else
#   ifdef _MSC_VER
#       error "<optional> is apparently not available (use option `/std:c++latest`?)."
#   else
#       error "<optional> appears not available (try define STDLIB_USE_EXPERIMENTAL_CPP17?)."
#   endif
#endif

#ifdef STDLIB_HOIST_UP_OPTIONAL_TEMPLATE
    namespace std {
        using experimental::optional;
    }  // namespace std;
#endif

#include <stdlib/all/non_io_fixes.hpp>
