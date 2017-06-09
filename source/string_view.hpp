﻿#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/string_view.hpp>
//
// basic_string_view template, specializations string_view and wstring_view.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>         // STDLIB_IS_CPP17

#ifdef STDLIB_USE_EXPERIMENTAL_CPP17
#   include <experimental/string_view>
    namespace std {
        using namespace std::experimental;
    }  // namespace std;
#elif STDLIB_IS_CPP17
#   include <string_view>
#else
#   error "Sorry, <string_view> is apparently not available with this compiler."
#endif