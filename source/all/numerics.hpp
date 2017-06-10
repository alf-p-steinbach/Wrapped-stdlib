#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/numerics.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

// The numerics headers listed by (http://en.cppreference.com/w/cpp/header),
#include <stdlib/c/fenv.hpp>        // Floating-point environment access functions.
#include <stdlib/c/math.hpp>        // Common mathematics functions, floating point overloads of `abs`.
#include <stdlib/complex.hpp>       // std::complex
#include <stdlib/numeric.hpp>       // Numeric operations on values in containers, e.g. iota.
#include <stdlib/random.hpp>        // Random number generators and distributions
#include <stdlib/ratio.hpp>         // Compile-time rational arithmetic.
#include <stdlib/valarray.hpp>      // Class for representing and manipulating arrays of values.

// Not listed in this category by cppreference, but useful/necessary:
#include <stdlib/algorithm.hpp>           // std::(min, max, accumulate, etc.)
#include <stdlib/all/numerics/integer_types.hpp>          // Various useful aliases for integer types, plus support.
#include <stdlib/all/numerics/number_range_limits.hpp>    // E.g. INT_MAX, std::numeric_limits<int>::max().
#include <stdlib/c/stdlib.hpp>            // E.g. integer overloads of `abs`.
