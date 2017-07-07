#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/console_io.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef STDLIB_NO_FIX_OF_CONSOLE_IO
#   ifdef _WIN32
#       include <stdlib/_impl/windows_console_io.hpp>
#   endif
#endif

#include <stdlib/fix/default_locale.hpp>
