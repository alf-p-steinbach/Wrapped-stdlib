#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/c/wctype.hpp>
//
// Functions for determining the type of wide character data.
// In special cases (e.g. Turkey) it can be necessary to use `setlocale` first.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>
#include <cwctype>
#include <wctype.h>
#include <stdlib/all/non_io_fixes.hpp>
