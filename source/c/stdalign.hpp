#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/c/stdalign.hpp>
//
// Functions and macro constants for signal management.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>
#include <cstdalign>

// The <stdalign.h> isn't needed (<cstdalign.> only defines 2 macros) and is not
// provided by Visual C++ 2017, so here it's simply not included.
// -- no -- #include <stdalign.h>

#include <stdlib/all/non_io_fixes.hpp>
