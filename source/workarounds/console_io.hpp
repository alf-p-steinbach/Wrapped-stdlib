#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/workarounds/console_io.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef STDLIB_NO_WORKAROUND_CONSOLE_IO
#   ifdef _WIN32
#       include <stdlib/workarounds/impl/windows_console_io.hpp>
#   endif
#endif
