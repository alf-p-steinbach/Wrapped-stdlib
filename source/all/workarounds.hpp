#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/all/workarounds.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/workarounds/msvc_wolfcall_suppression.hpp>     // BEST IF FIRST.

#include <stdlib/workarounds/default_locale.hpp>
#include <stdlib/workarounds/console_io.hpp>
#include <stdlib/workarounds/named_boolean_operators.hpp>
#include <stdlib/workarounds/output_of_implicit_wide_c_string.hpp>
#include <stdlib/workarounds/STDLIB_BYTE_ORDER.hpp>             // Needed for std::codecvt_*.
