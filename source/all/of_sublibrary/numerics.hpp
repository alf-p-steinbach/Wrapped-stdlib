#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/of_sublibrary/numerics.hpp>
//
// The C++ standard's section “Numerics library” (in C++14 that's §26).
// The set of headers included here are those in C++14 §26.1/2 table 114.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.


// Floating-Point Environment
#include <stdlib/c/fenv.hpp>

// Complex Numbers
#include <stdlib/complex.hpp>

// Random number generation
#include <stdlib/random.hpp>

// Numeric arrays 
#include <stdlib/valarray.hpp>

// Generalized numeric operations
#include <stdlib/numeric.hpp>

// C library
#include <stdlib/c/math.hpp>
#include <stdlib/c/tgmath.hpp>
#include <stdlib/c/stdlib.hpp>      // E.g. abs(int)
