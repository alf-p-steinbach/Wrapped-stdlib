#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/text/cpp_strings.hpp>
//
// The C++ library's string handling headers, collected.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/string.hpp>        // basic_string template, string and wstring.

#include <stdlib/extension/version.hpp>
#if STDLIB_HAS_CPP17_FEATURES
#   include <stdlib/string_view.hpp>            // basic_string_view template.
#endif
