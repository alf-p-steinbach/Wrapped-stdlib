#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/string.hpp>
//
// std::basic_string class template, aliases std::string and std::wstring.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>
#include <string>
#include <stdlib/all/non_io_fixes.hpp>

#ifndef NO_STDLIB_STRING_LITERALS
    using namespace std::string_literals;       // E.g., `"Hi there!"s`.
#endif
