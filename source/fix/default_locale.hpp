#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/default_locale.hpp>
//
// The default locale needs to be set up
// • to make wide streams work in Unix-land, and
// • to make narrow character classification functions work in Windows.
//
// STDLIB_NO_FIX_OF_DEFAULT_C_LOCALE suppresses the C locale auto-config.
// STDLIB_NO_FIX_OF_DEFAULT_CPP_LOCALE suppresses the C++ locale auto-config.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/default_c_locale.hpp>
#include <stdlib/fix/default_cpp_locale.hpp>
