#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/c/setjmp.hpp>
//
// Macro (and function) that saves (and jumps) to an execution context.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>
#include <csetjmp>
#include <setjmp.h>
#include <stdlib/all/non_io_fixes.hpp>
