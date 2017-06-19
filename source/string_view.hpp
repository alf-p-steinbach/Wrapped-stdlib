#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/string_view.hpp>
//
// basic_string_view template, specializations string_view and wstring_view.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>         // STDLIB_COMPILER_SUPPORTS_CPP17

#if STDLIB_COMPILER_SUPPORTS_CPP17
#   include <string_view>
#elif STDLIB_USE_EXPERIMENTAL_CPP17
#   include <experimental/string_view>
    namespace std {
        using namespace std::experimental;
    }  // namespace std;
#else
#   error "Sorry, <string_view> is apparently not available with this compiler & options."
#endif

#include <stdlib/all/non_io_fixes.hpp>
