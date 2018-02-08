#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/math_constants.hpp>
//
// Common math constants.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/fix/math_constants_availability.hpp>

#ifndef STDLIB_NO_MATH_CONSTANTS
namespace stdlib{ namespace ext{
    inline namespace math {
        const auto e                = M_E;              // e              2.71828182845904523536
        const auto log2e            = M_LOG2E;          // log2(e)        1.44269504088896340736
        const auto log10e           = M_LOG10E;         // log10(e)       0.434294481903251827651
        const auto ln2              = M_LN2;            // ln(2)          0.693147180559945309417
        const auto ln10             = M_LN10;           // ln(10)         2.30258509299404568402
        const auto pi               = M_PI;             // pi             3.14159265358979323846
                                                        // pi/2 M_PI_2    1.57079632679489661923
                                                        // pi/4 M_PI_4    0.785398163397448309616
                                                        // 1/pi M_1_PI    0.318309886183790671538
                                                        // 2/pi M_2_PI    0.636619772367581343076
        const auto inv_sqrt_pi      = M_2_SQRTPI/2;     // 2/sqrt(pi)     1.12837916709551257390
        const auto sqrt2            = M_SQRT2;          // sqrt(2)        1.41421356237309504880
        const auto inv_sqrt2        = M_SQRT1_2;        // 1/sqrt(2)      0.707106781186547524401
    }  // namespace math                                // 
}}  // namespace stdlib::ext
#endif
