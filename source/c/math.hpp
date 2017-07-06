#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/math.hpp>
//
// Common math functions.
// Addditionally (M_*** is a de facto standard) defines the following constants:
//
//      M_E         stdlib::e               e               2.71828182845904523536
//      M_LOG2E     stdlib::log2e           log2(e)         1.44269504088896340736
//      M_LOG10E    stdlib::log10e          log10(e)        0.434294481903251827651
//      M_LN2       lstdlib::ln2            n(2)            0.693147180559945309417
//      M_LN10      stdlib::ln10            ln(10)          2.30258509299404568402
//      M_PI        stdlib::pi              pi              3.14159265358979323846
//      M_PI_2                              pi/2            1.57079632679489661923
//      M_PI_4                              pi/4            0.785398163397448309616
//      M_1_PI                              1/pi            0.318309886183790671538
//      M_2_PI                              2/pi            0.636619772367581343076
//      M_2_SQRTPI  2*stdlib::inv_sqrt_pi   2/sqrt(pi)      1.12837916709551257390
//      M_SQRT2     stdlib::sqrt2           sqrt(2)         1.41421356237309504880
//      M_SQRT1_2   stdlib::inv_sqrt2       1/sqrt(2)       0.707106781186547524401
//
// E.g. see the MSDN article on “math constants” at
// <url: https://msdn.microsoft.com/en-us/library/4hwaceh6.aspx>.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

// At least with MSVC this works for defining M_PI etc. even if <math.h> has
// been previously included - the definitions are outside the normal guard.
// But just to be on the safe safe, include the constant defs first.
#include <stdlib/extension/math_constants.hpp>
#include <cmath>
#include <math.h>
#include <stdlib/all/non_io_fixes.hpp>
