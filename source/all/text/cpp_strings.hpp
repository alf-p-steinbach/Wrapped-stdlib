#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/all/text/cpp_strings.hpp>
//
// The C++ library's string handling headers, collected.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/string.hpp>        // basic_string template, string and wstring.

#include <stdlib/extension/version.hpp>         // STDLIB_IS_CPP17
#if defined( STDLIB_USE_EXPERIMENTAL_CPP17 ) || defined( STDLIB_IS_CPP17 )
#   include <stdlib/string_view.hpp>            // basic_string_view template.
#endif
