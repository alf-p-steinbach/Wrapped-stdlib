#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/main_arguments.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef STDLIB_NO_FIX_OF_MAIN_ARGUMENTS
#   ifdef _WIN32
#       include <stdlib/fix/impl/windows_main_arguments.hpp>
#   endif
#endif

#include <stdlib/fix/default_locale.hpp>
